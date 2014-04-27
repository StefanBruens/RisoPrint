#ifndef INCLUDE_JOB
#define INCLUDE_JOB

#include "Page.h"
#include <vector>

class Job {
	std::vector<PageSptr> m_Pages;

public:
	void addPage(PageSptr& page) { m_Pages.push_back(page); }
	void dump(std::string outfile);

};

#endif // INCLUDE_JOB
