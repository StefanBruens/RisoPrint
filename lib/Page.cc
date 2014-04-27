#include "Page.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Helper.h" 

void
Page::setThumb(char* buffer, size_t len)
{
	m_Thumb = std::unique_ptr<PageThumbNail>(new PageThumbNail(buffer, len));
};

void
Page::setHPos(int h)
{
	m_CurrentLine->setHPos(h);
}

void
Page::setVPos(int v)
{
	m_CurrentLine = std::make_shared<ImageLine>();
	m_PageLines.at(v) = m_CurrentLine;
}

void
Page::setLineData(char* buffer, size_t len, bool raw)
{
	if( raw ) 
		m_CurrentLine->setRaw(buffer, len);
	else
		m_CurrentLine->setCoded(buffer, len);
	m_CurrentLine = 0;
}

void
Page::dump()
{
	std::cout << "\tLines: " << m_PageLines.size() << std::endl;
	std::cout << "\tThumbNail : " << (m_Thumb?"yes":"no") << std::endl;
}

void
Page::dumpThumbNail()
{
	if(m_Thumb) {
		std::stringstream fn;
		fn << "/tmp/p" << (m_PageNr+1) << ".bmp";
		std::ofstream outfile (fn.str().c_str());
		m_Thumb->dump(outfile);
		outfile.close();
	}
}

void
Page::dumpImage(std::string prefix)
{
	std::stringstream fn;
	fn << prefix << (m_PageNr+1) << ".pbm";
	std::ofstream outfile (fn.str().c_str());

	outfile << "P4\n" << m_Width << " " << m_Height << "\n";

	for(int h = 0; h < m_Height; h++) {
		// std::cout << h << " ";
		m_PageLines[h]->writeRaw(outfile, m_Width);
	}
	// std::cout << std::endl;

	outfile.close();
}

void
PageThumbNail::dump(std::ostream &os)
{
	os.write(m_Buffer, m_Len);
}

void
Page::encode()
{
	for(int h = 0; h < m_Height; h++) {
		// std::cout << h << " ";
		m_PageLines[h]->encode();
	}
	std::cout << std::endl;
}

void
Page::dumpRiso(std::ostream &os) {
	for(int v = 0; v < m_Height; v++) {
		int len = m_PageLines[v]->codedLen();
		if (len == 0) continue;

		if(v<10) continue;
		if(v>(m_Height-10)) continue;

		//if(v<119) continue;
		//if(v>9724) continue;

		//std::cout << "v: " << v << " " << len << std::endl;

		std::stringstream s, l;
		s << v;
		outFixedLen(os, s.str(), 'V');
		outFixedLen(os, "35", 'H');
		l << len;
		outFixedLen(os, l.str(), 'i');
		m_PageLines[v]->writeCoded(os);
	}
}


