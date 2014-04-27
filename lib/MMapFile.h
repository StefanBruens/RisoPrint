#ifndef INCLUDE_MMAP_FILE
#define INCLUDE_MMAP_FILE

#include <string>

class MMapFile {
protected:
	char* m_FileMapping;
	size_t m_FilePos;
	size_t m_FileLen;

public:
	MMapFile() : m_FileMapping(0), m_FilePos(0),
		m_FileLen(0) {}
	int openFile(std::string filename);

};

#endif // INCLUDE_MMAP_FILE
