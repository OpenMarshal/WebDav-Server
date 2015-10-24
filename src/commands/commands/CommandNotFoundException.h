#ifndef _LIBS_COMMANDNOTFOUNDEXCEPTION_H
#define	_LIBS_COMMANDNOTFOUNDEXCEPTION_H

#include "_libs/exception/exception.h"

#include <string>

class CommandNotFoundException : public Exception
{
public:
	CommandNotFoundException(std::string commandName)
		: commandName(commandName)
	{ }
	CommandNotFoundException(const char* commandName)
		: commandName(commandName)
	{ }
	
	std::string getCommandName()
	{
		return commandName;
	}
	
private:
	std::string commandName;
};

#endif	/* _LIBS_COMMANDNOTFOUNDEXCEPTION_H */

