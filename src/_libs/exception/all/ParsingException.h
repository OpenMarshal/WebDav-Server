#ifndef _LIBS_PARSINGEXCEPTION_H
#define	_LIBS_PARSINGEXCEPTION_H

#include "_libs/exception/exception.h"

class ParsingException : public Exception
{
public:
	ParsingException(const char* message, int charNo)
	{
		this->message = message;
		this->charNo = charNo;
	}
	
	const char* getMessage()
	{
		return message;
	}
	
	int getCharNo()
	{
		return charNo;
	}
	
private:
	const char* message;
	int charNo;
};

#endif	/* _LIBS_PARSINGEXCEPTION_H */

