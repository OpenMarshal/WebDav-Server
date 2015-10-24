#ifndef _COMMAND_MANAGER_H
#define	_COMMAND_MANAGER_H

#include "commands/CommandNotFoundException.h"

#include "commands/Command.h"
#include <list>

#include "commands/Options.h"
//#include "commands/Get.h"
#include "commands/Propfind.h"
#include <string>


class CommandManager
{
public:
	CommandManager();
	
	Command* getCommand(std::string cmd) throw(CommandNotFoundException);
	
	CommandManager& addCommand(Command* cmd);
	
private:
	std::list<Command*> cmds;
};

#endif	/* _COMMAND_MANAGER_H */

