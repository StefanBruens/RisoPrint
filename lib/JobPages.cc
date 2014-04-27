#include "JobPages.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>

bool
JobPages::saveOption(char id, char* value, int len)
{
	switch(id) {
	case 'i':
		m_CurrentPage->setLineData(value, len, false);
		return true;
	case 'H':
		m_CurrentPage->setHPos(atoi(value));
		return true;
	case 'V':
		m_CurrentPage->setVPos(atoi(value));
		return true;
	case 'M':
		m_CurrentPage = std::make_shared<Page>(m_Pages.size());
		m_Pages.push_back(m_CurrentPage);
		m_CurrentPage->setSize(m_PageWidth, m_PageHeight);
		return true;
	case 'n':
		break;

	default:
		return false;
	}

	if(id == 'n') {
		char* end;
		int len = strtol(&value[5], &end, 10) + 1;
		if(0 == memcmp("\37THUM", value, 5) ) {
			m_CurrentPage->setThumb(end+1, len-1);
			return true;
		}
	}

	return false;
}

void
JobPages::dump() {
	std::cout << "----------" << std::endl;
	std::cout << "Pages: " << m_Pages.size() << std::endl;
	for( unsigned int i = 0; i < m_Pages.size(); i++ ) {
		std::cout << (i+1) << ": ";
		m_Pages[i]->dump();
		m_Pages[i]->dumpThumbNail();
		m_Pages[i]->dumpImage();
	}
}

