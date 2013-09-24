#ifndef EXCEPTIONADVENTNOTYETIMPLEMENTED_H
#define EXCEPTIONADVENTNOTYETIMPLEMENTED_H

#include <iostream>
#include <exception>

class ExceptionAdventNotYetImplemented : public std::exception {
  virtual const char* what() const throw() {
    return "ADVENT: Not yet implemented:";
  }
};

#endif // EXCEPTIONADVENTNOTYETIMPLEMENTED_H