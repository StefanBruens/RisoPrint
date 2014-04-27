#include "ImageLine.h"
#include <iostream>

void
ImageLine::writeRaw(std::ostream& os, size_t len)
{
	if( !m_Coded && (m_Raw.isValid() ) ) {
		size_t outPos;
		//assert( m_Raw.m_Len >= len/8 );
		unsigned char* data = (unsigned char*)m_Raw.m_Data;

		for(outPos = 0; outPos < len; outPos+=8)
			os.put(*data++);

		return;
	}

	if(! m_Coded ) {
		size_t outPos;
		for(outPos = 0; outPos < len; outPos+=8)
			os.put(0);
		return;
	}

	for(int offset = 7; offset < m_HPos; offset+=8)
		 os.put(0);

	int shift = 8 - m_HPos%8;

	unsigned short out = 0;
	unsigned char* data = (unsigned char*)m_Coded->m_Data;
	size_t pos = 0;
	size_t outPos = m_HPos-(m_HPos%8);

	while(pos < m_Coded->m_Len) {
		char c = data[pos++];
		int count = abs(c)+1;
		if(count*8 > (signed)(len-outPos)) count = (len-outPos)/8;
		outPos += count*8;
		//assert(outPos <= len);
		if(c<0) {
			while(count-- > 0) {
				out = (out<<8) | data[pos]<<shift;
				os.put(out>>8);
			}
			pos++;
		} else {
			while(count-- > 0) {
				out = (out<<8) | data[pos++]<<shift;
				os.put(out>>8);
			}
		}
	}

	if(outPos < len) {
		os.put(out&0xff);
		outPos += 8;
	}

	while(outPos < len) {
		 os.put(0);
		 outPos += 8;
	}
}

void
ImageLine::encode()
{
	//assert(m_Coded == 0);
	//assert(m_Raw.isValid());

	unsigned char* inData = (unsigned char*)m_Raw.m_Data;
	size_t inLen = m_Raw.m_Len;
	size_t pos = m_HPos/8;
	int shift = m_HPos%8;
	int len = -pos;
	int run = 0;
	Encoder* enc;

	if( (inData[pos++]<<shift) == 0) {
		while( pos < inLen && inData[pos] == 0 )
			pos++;
		if( pos >= inLen )
			return;
	}
	pos--;

	enc = new Encoder(inData[pos-1], shift);
	len += pos;
	run = len;

	int remaining = inLen - pos;
	remaining = (remaining*129)/128;
	m_Coded = new CodedLine(0, remaining);
	m_Coded->allocate();
	unsigned char* outData = (unsigned char*)m_Coded->m_Data;

	int counterPos = 0; int outPos = 1;
	enum runstate_t { FIRST, COPY, RUN } state;
	if(run > 2) {
		state = RUN;
	} else {
		state = COPY;
	}
	if(run == 2) outPos = 3;

	unsigned char next = enc->next(inData[pos++]);
	unsigned char last = next;

	while(pos < inLen) {
		switch (state) {
		case FIRST:
			while( run > 1 ) {
				outData[counterPos] = +1 - (run>128?128:run);
				outData[outPos] = last ;
				counterPos += 2; outPos = counterPos + 1;
				run -= 128;
			}

			if( run != 1 ) {
				last = next;
				next = enc->next(inData[pos++]);
			}
			outData[outPos++] = last;
			outData[outPos++] = next;

			len = 2, run = 1;
			if(last==next) run++;
			state = COPY;
			break;

		case COPY:
			last = next;
			next = enc->next(inData[pos++]);
			len++;
			outData[outPos++] = next;

			if( len == 126 ) {
				if (pos < inLen) {
					next = enc->next(inData[pos++]);
				}
				outData[counterPos] = len - 1;
				counterPos += len + 1; outPos = counterPos+1;
				run = 0;
				state = FIRST; break;
			}

			if( last == next )
				run++;
			else
				run = 1;

			if( run >= 3 ) {
				if( len > 3 ) {
					outData[counterPos] = (len-3) - 1;
					counterPos += (len-3) + 1;
					outPos = counterPos + 1;
					len = 3;
				}
				state = RUN;
				break;
			}

			break;

		case RUN:
			last = next;
			next = enc->next(inData[pos++]);
			len++;
			if( last != next ) {
				state = FIRST;
				break;
			} else
				run++;
		}
	}

	if( state == COPY ) {
		outData[counterPos] = len - 1;
		counterPos += len+1;
	}
	if( state == RUN || state == FIRST ) { // && (last != 0) ) {
		while( run > 0 ) {
			outData[counterPos] = +1 - (run>127?127:run);
			outData[outPos] = last ;
			counterPos += 2; outPos = counterPos + 1;
			run -= 127;
		}
		if(last != next) {
			outData[counterPos] = 0;
			outData[outPos] = next;
			counterPos += 2;
		}
	}

	//for(int i = 0; i < counterPos ; i++)
		//std::cout << (int)outData[i] << " ";
	//std::cout << std::endl;
	m_Coded->m_Len = counterPos;
	delete enc;
}

void
ImageLine::CodedLine::allocate()
{
	m_Data = new char[m_Len];
	// FIXME
}

void
ImageLine::writeCoded(std::ostream& os) {
		unsigned char* data = (unsigned char*)m_Coded->m_Data;

		for(unsigned outPos = 0; outPos < m_Coded->m_Len; outPos++)
			os.put(*data++);
}
