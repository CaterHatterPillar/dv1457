#ifndef UTIL_H
#define UTIL_H

#include <string>

class Util {
public:
	static std::string toString( int p_int );
	static std::string toString( unsigned p_uint );

	static const char* toStringC( int p_int );
	static const char* toStringC( unsigned p_uint );

	static int toInt( std::string p_string );
};

#endif // UTIL_H