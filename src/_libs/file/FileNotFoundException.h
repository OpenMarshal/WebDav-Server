#ifndef _LIBS_FILENOTFOUNDEXCEPTION_H
#define	_LIBS_FILENOTFOUNDEXCEPTION_H

#include "_libs/exception/exception.h"
#include <string>

class FileNotFoundException : public Exception
{
public:
	FileNotFoundException(const char* filePath)
		: filePath(filePath)
	{ }
	FileNotFoundException(std::string filePath)
		: filePath(filePath)
	{ }
	
	std::string getFilePath()
	{
		return filePath;
	}
	
private:
	std::string filePath;
};

#endif	/* _LIBS_FILENOTFOUNDEXCEPTION_H */

