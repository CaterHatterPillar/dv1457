#ifndef EXCEPTIONADVENTNOTYETIMPLEMENTED_H
#define EXCEPTIONADVENTNOTYETIMPLEMENTED_H

#include <string>
#include <iostream>
#include <exception>

class ExceptionAdventNotYetImplemented : public std::exception {
public:
	ExceptionAdventNotYetImplemented( std::string p_func ) throw() : exception() {
		m_func = p_func;
	}
	virtual ~ExceptionAdventNotYetImplemented() throw() {
		// Do nothing.
	}

	virtual const char* what() const throw() {
		std::string what = "ADVENT: Not yet implemented: " + m_func;
		return what.c_str();
	}
private:
	std::string m_func;
};

#endif // EXCEPTIONADVENTNOTYETIMPLEMENTED_H