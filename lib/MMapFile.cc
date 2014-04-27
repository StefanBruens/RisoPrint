#include "MMapFile.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <cstring>
#include <iostream>

int
MMapFile::openFile(std::string filename)
{
	std::cout << "Opening \"" << filename << "\" ...";

	int fd = open(filename.c_str(), O_RDONLY);
	if( fd < 0 ) {
		std::cout << " failed!\n";
		return fd;
	}

	struct stat statbuf;
	int ret = fstat(fd, &statbuf); // FIXME: ret val
	if( ret < 0 ) return -1;

	m_FileLen = statbuf.st_size;

	std::cout << "\nmmaping " << m_FileLen << " bytes ...";
	m_FileMapping = (char*)
		mmap(0, m_FileLen, PROT_READ, MAP_POPULATE | MAP_PRIVATE, fd, 0);

	if( m_FileMapping == MAP_FAILED ) {
		int errsv = errno;
		std::cout << " failed: " << strerror(errsv) << "\n";
		return -1;
	}

	std::cout << " done!\n";

	return m_FileLen;
}

