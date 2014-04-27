#include <string>
#include <vector>

#include "MMapFile.h"
#include "JobPages.h"

class ImageFile : public MMapFile {
	int m_PageNr;

public:
	ImageFile() : m_PageNr(0) {};

	bool read(PageSptr& page);

};
