#ifndef _COMMAND_COMMAND_H
#define	_COMMAND_COMMAND_H

#include "_libs/protocol/http.h"
#include "ConnectionEnv.h"

class Command
{
public:
	Command()
	{ }
	
	virtual std::string getName() = 0;
	virtual HttpResponseBuilder* compute(ConnectionEnv* env, HttpRequest* request) = 0;
	
	virtual void continueRcv(ConnectionEnv* env, const char* data)
	{ }
};

#endif	/* _COMMAND_COMMAND_H */

