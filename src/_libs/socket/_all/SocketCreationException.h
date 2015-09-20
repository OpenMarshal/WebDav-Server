#ifndef _LIBS_SOCKETCREATIONEXCEPTION_H
#define	_LIBS_SOCKETCREATIONEXCEPTION_H

#include "_libs/exception/exception.h"

class SocketCreationException : public Exception
{
public:
	SocketCreationException(const char* functionName, int errorNo)
	{
		this->functionName = functionName;
		this->errorNo = errorNo;
	}
	
	const char* getFunctionName()
	{
		return functionName;
	}
	
	int getErrorNo()
	{
		return errorNo;
	}
	
private:
	const char* functionName;
	int errorNo;
};

#endif	/* _LIBS_SOCKETCREATIONEXCEPTION_H */

