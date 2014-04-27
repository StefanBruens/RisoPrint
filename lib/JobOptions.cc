#include "JobOptions.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include "JobOptions.h"
#include "JobFile.h"
#include "Page.h"

extern unsigned const char risoInit[64];

bool
JobOptions::saveOption(char id, char* value, int len)
{
	int dummy;

	switch(id) {
	case 'i':
	case 'H':
	case 'V':
		return false;

	case 'C': m_Copies   = atoi(value); return true;
	case 'D': m_Density  = atoi(value); return true;
	case 'S': m_Speed    = atoi(value); return true;
	case 'G': m_GenSteps = atoi(value); return true;
	case 'r': return (
		2 == sscanf(value, "%i;%i", &m_HRes, &m_VRes));
	case 'z': return (
		3 == sscanf(value, "%i;%i;%i", &dummy, &m_HSize, &m_VSize));

	case 'M':
		m_parent->pages().setPageSize(
			0.5 + m_HRes*m_HSize/25.4, 0.5 + m_VRes*m_VSize/25.4);
		return false;

	case 'O':
	case 'Q':
	case 'o':
	case 's':
	default:
		m_Unknown.push_back(
			verbatim_option(id, value, len));
		return true;

	case 'n':
	case 'e':
		break;
	}

	if(id == 'n') {
		char* end;
		int len = strtol(&value[5], &end, 10) + 1;
		if(0 == memcmp("\37FILE", value, 5) ) {
			m_File = std::string(end, len);
			return true;
		}
		if(0 == memcmp("\37HOST", value, 5) ) {
			m_Host = std::string(end, len);
			return true;
		}
		if(0 == memcmp("\37TIME", value, 5) ) {
			m_Time = std::string(end, len);
			return true;
		}
	}
	if(id == 'e') {
		if(0 == memcmp(&risoInit, value, 64))
			return true;
		std::cerr << "Unknown init sequence!" << std::endl;
		return false;
	}
	return false;
}

void
JobOptions::dump() {
	std::cout << "Copies: " << m_Copies << std::endl;
	if (m_Speed >= 0) std::cout << "Speed: " << m_Speed << std::endl;
	if (m_Density >= 0) std::cout << "Density: " << m_Density << std::endl;
	std::cout << "GenSteps: " << m_GenSteps << std::endl;
	std::cout << "----------" << std::endl;
	std::cout << m_HRes << "x" << m_VRes << "dpi, " <<
		m_HSize << "x" << m_VSize << "mm" << std::endl;
	std::cout << "Info: " << "File " << m_File << " by "
		<< m_Host << ", " << m_Time << std::endl;
	std::cout << "----------" << std::endl;
		std::for_each(m_Unknown.begin(), m_Unknown.end(), std::mem_fun_ref(&verbatim_option::dump ));

}
