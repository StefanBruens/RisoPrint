#ifndef INCLUDE_PAGE
#define INCLUDE_PAGE

#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include "ImageLine.h"

class PageThumbNail {
	char* m_Buffer;
	size_t m_Len;
public:
	PageThumbNail(char* buffer, size_t len) :
		m_Buffer(buffer), m_Len(len) {};
	void dump(std::ostream &os);
};

class Page;
typedef std::shared_ptr<Page> PageSptr;

class Page {
	std::unique_ptr<PageThumbNail> m_Thumb;
	std::vector<ImageLineSptr> m_PageLines;
	ImageLineSptr m_CurrentLine;
	int m_PageNr;
	int m_Width;
	int m_Height;

public:
	Page(int page) : m_PageNr(page) {};

	void setThumb(char* buffer, size_t len);

	void setHPos(int h);
	void setVPos(int v);
	void setLineData(char* buffer, size_t len, bool raw);
	void setSize(int width, int height) {
		// std::cout << "Pagesize: " << height << "x" << width << std::endl;
		m_Width = width;
		m_Height = height;
		m_PageLines.resize(height);
		auto emptyLine = std::make_shared<ImageLine>();
		for (auto& line : m_PageLines)
			line = emptyLine;
	}

	void encode();

	void dump();
	//void dumpThumbNail(std::ostream& os);
	void dumpRiso(std::ostream& os);
	void dumpThumbNail();
	void dumpImage(std::string prefix = std::string("/tmp/P") );
};


#endif // INCLUDE_PAGE
