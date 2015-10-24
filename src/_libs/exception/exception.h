#ifndef _LIBS_EXCEPTION_H
#define	_LIBS_EXCEPTION_H

#include <exception>

class Exception : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Unexpected exception happened.";
	}
};

class RuntimeException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Unexpected runtime exception happened.";
	}
};



#include "all/ParsingException.h"



#endif	/* _LIBS_EXCEPTION_H */

