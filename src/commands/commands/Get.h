#ifndef _CMDS_CMD_GET_H
#define	_CMDS_CMD_GET_H

#include "_libs/protocol/http.h"
#include "Command.h"

namespace cmds
{
	class Get : public Command
	{
	public:
		Get()
		{ }
		
		std::string getName()
		{
			return "GET";
		}
		
		HttpResponseBuilder* compute(ConnectionEnv* env, HttpRequest* request)
		{
			return &HttpResponse::create()
					.setCode(200)
					.setMessage("OK")
					.addHeader("Allow", "OPTIONS, GET")
					.addHeader("Content-type", "httpd/unix-directory");
		}
	};
}

#endif	/* _CMDS_CMD_GET_H */

