#include <sstream>
#include <cstdlib> // atoi

#include "Util.h"

std::string Util::toString( int p_int ) {
	std::stringstream ss;
	ss << p_int;
	return ss.str();
}
std::string Util::toString( unsigned p_uint ) {
	std::stringstream ss;
	ss << p_uint;
	return ss.str();
}

const char* Util::toStringC( int p_int ) {
	return toString( p_int ).c_str();
}
const char* Util::toStringC( unsigned p_uint ) {
	return toString( p_uint ).c_str();
}

int Util::toInt( std::string p_string ) {
	return atoi( p_string.c_str() );
}