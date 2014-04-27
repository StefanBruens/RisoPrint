#include "JobOptions.h"
#include "JobPages.h"

#include "MMapFile.h"

class JobFile : public MMapFile {
	JobOptions m_Options;
	JobPages m_Pages;

	bool seekJobSep();

	// FIXME: split off
	off_t parseOption();
	bool isVarLen(char id);

public:
	JobFile() : m_Options(this), m_Pages(this) {};

	bool parse();

	JobPages& pages() { return m_Pages; }

};
