#include "ImageFile.h"
#include <iostream>
#include <cstdlib>

bool
ImageFile::read(PageSptr& page)
{
	if( m_FilePos >= m_FileLen) return false;

	char* buf = &(m_FileMapping)[m_FilePos];
	if( buf[0] != 'P' || buf[1] != '4' ) {
		std::cout << "File not in raw PBM format";
		return false;
	}
	buf += 2;

	int width; int height;

	while( *buf < '0' || *buf > '9' )
		buf++;

	width = strtol(buf, &buf, 10);
	height = strtol(buf, &buf, 10);
	std::cout << "PBM: " << width << "x" << height << std::endl;
	buf++; // single NL/WS

	page = std::make_shared<Page>(m_PageNr++);
	page->setSize(width, height);

	int lineWidth = (width+7)/8;
	for( int v = 0; v < height; v++ ) {
		page->setVPos(v);
		page->setHPos(35);
		page->setLineData(buf, lineWidth, true);
		buf += lineWidth;
	}

	m_FilePos = buf - m_FileMapping;

	return true;
}

