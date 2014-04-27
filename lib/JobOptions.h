#ifndef INCLUDE_JOB_OPTIONS
#define INCLUDE_JOB_OPTIONS

#include <list>
#include <string>
#include <iostream>

class verbatim_option;
class JobFile;

class JobOptions {
public:
	JobOptions(JobFile* parent) :
		m_parent(parent), m_Density(-1), m_Speed(-1) {};

	bool saveOption(char id, char* value, int len);
	void dump();

private:
	JobFile* m_parent;

	int m_HRes;
	int m_VRes;

	int m_HSize;
	int m_VSize;

	int m_Copies;
	int m_Density; // fixme, enum
	int m_Speed; // fixme, enum
	int m_GenSteps; // fixme, enum

	std::string m_File;
	std::string m_Host;
	std::string m_Time;

	std::list<verbatim_option> m_Unknown;
};

class verbatim_option {
public:
	verbatim_option(char id, char* value, int len) :
		m_Id(id), m_Value(value), m_len(len) {};

	void dump() { std::cout << m_Id << ": " << std::string(m_Value, m_len) << std::endl;}

private:
	char m_Id;
	char* m_Value;
	int m_len;
};

#endif // INCLUDE_JOB_OPTIONS
