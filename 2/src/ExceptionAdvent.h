#ifndef EXCEPTIONADVENT_H
#define EXCEPTIONADVENT_H

#include <string>
#include <iostream>
#include <exception>

class ExceptionAdvent : public std::exception {
public:
	ExceptionAdvent( std::string p_error ) throw() : exception() {
		m_error = p_error;
	}
	virtual ~ExceptionAdvent() throw() {
		// Do nothing.
	}

	virtual const char* what() const throw() {
		std::string what = "ADVENT: " + m_error;
		return what.c_str();
	}
private:
	std::string m_error;
};

#endif // EXCEPTIONADVENT_H