#ifndef INCLUDE_HELPER
#define INCLUDE_HELPER

#include <ostream>

std::ostream& outVarLen(
	std::ostream& os, const unsigned char* buffer, int len, char id);
std::ostream& outVarLen(
	std::ostream& os, const std::string option, char id);

std::ostream& outFixedLen(
	std::ostream& os, const unsigned char* buffer, int len, char id);
std::ostream& outFixedLen(
	std::ostream& os, const std::string option, char id);

#endif // INCLUDE_HELPER
