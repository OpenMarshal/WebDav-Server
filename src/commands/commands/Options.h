#ifndef _CMDS_CMD_OPTIONS_H
#define	_CMDS_CMD_OPTIONS_H

#include "_libs/protocol/http.h"
#include "Command.h"

namespace cmds
{
	class Options : public Command
	{
	public:
		Options()
		{ }
		
		std::string getName()
		{
			return "OPTIONS";
		}
		
		HttpResponseBuilder* compute(ConnectionEnv* env, HttpRequest* request);
	};
}

#endif	/* _CMDS_CMD_OPTIONS_H */

