#ifndef INCLUDE_JOB_PAGES
#define INCLUDE_JOB_PAGES

#include <vector>
#include "Page.h"

class JobFile;

class JobPages {
	JobFile* m_parent;
	PageSptr m_CurrentPage;
	std::vector<PageSptr> m_Pages;

	int m_PageWidth;
	int m_PageHeight;

public:
	JobPages(JobFile* parent = 0) :
		m_parent(parent) {};

	bool saveOption(char id, char* value, int len);
	void dump();

	void addPage(PageSptr& page) { m_Pages.push_back(page); }

	void setPageSize(int width, int height) {
		m_PageWidth = width;
		m_PageHeight = height;
	}
};

#endif // INCLUDE_JOB_PAGES
