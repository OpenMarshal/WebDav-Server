#include "CommandManager.h"


CommandManager::CommandManager()
{ }

Command* CommandManager::getCommand(std::string cmd) throw(CommandNotFoundException)
{
	for(auto c : cmds)
		if(c->getName().compare(cmd) == 0)
			return c;
	
	throw CommandNotFoundException(cmd);
}

CommandManager& CommandManager::addCommand(Command* cmd)
{
	cmds.push_front(cmd);
	
	return *this;
}

