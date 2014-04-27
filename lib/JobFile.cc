#include "JobFile.h"
#include <iostream>

bool
JobFile::parse()
{
	if(0 == m_FileMapping)
		return false;

	if( !seekJobSep() )
		return false;

	while( !seekJobSep() ) { // EOJ
		if( ((char*)m_FileMapping)[m_FilePos] == 0xc ) {
			; // nextpage
			m_FilePos++;
		} else {
			off_t optionlen;
			while( (optionlen = parseOption() ) > 0 ) {
				// std::cout << "OptionLen: " << optionlen << "\n";
				m_FilePos += optionlen;
			}
		}
	}

	m_Options.dump();
	m_Pages.dump();
	return true;
}

bool
JobFile::seekJobSep()
{
	char* content = (char*)m_FileMapping;
	content += m_FilePos;

	if(content[0] == 0x1e && content[1] == 0x52) {
		m_FilePos += 2;
		std::cout << "Found JobSep\n";
		return true;
	}
	return false;
}

off_t
JobFile::parseOption() {
	char* content = (char*)m_FileMapping;
	content += m_FilePos;

	off_t o = 2;
	if(content[0] == 0x1e && content[1] == 0x26) {
		while( content[o] != 0x26 ) o++;
		char id = content[o+1];
		// std::cout << id << ": ";
		if(isVarLen(id)) {
			int len = atoi(&content[2]);
			//std::cout << len << std::endl;
			if( ! m_Options.saveOption(id,&content[o+2],len) )
				m_Pages.saveOption(id,&content[o+2],len);
			return len+o+2;
		}
		if( ! m_Options.saveOption(id,&content[2],o-2) )
			m_Pages.saveOption(id,&content[2],o-2);
		return o+2;
	}
	return 0;
}

bool
JobFile::isVarLen(char id) {
	switch(id) {
	case 'i':
	case 'e':
	case 'n':
		return true;
	default:
		return false;
	}
}

