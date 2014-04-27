#include "Helper.h"

std::ostream&
outVarLen(std::ostream& os, const unsigned char* buffer, int len, char id) {
	os << "\x1e\x26" << len << "\x26" << id;
	for( int i = 0; i < len; i++ )
		os << buffer[i];

	return os;
}

std::ostream&
outVarLen(std::ostream& os, const std::string option, char id) {
	os << "\x1e\x26" << option.size() << "\x26" << id << option;

	return os;
}

std::ostream&
outFixedLen(std::ostream& os, const unsigned char* buffer, int len, char id) {
	os << "\x1e\x26";
	for( int i = 0; i < len; i++ )
		os << buffer[i];
	os << "\x26" << id;

	return os;
}

std::ostream&
outFixedLen(std::ostream& os, const std::string option, char id) {
	os << "\x1e\x26" << option << "\x26" << id;

	return os;
}
