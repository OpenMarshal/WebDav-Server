#ifndef _CMDS_CMD_PROPFIND_H
#define	_CMDS_CMD_PROPFIND_H

#include "_libs/file/file.h"
#include "_libs/string/ExString.h"
#include "_libs/protocol/http.h"
#include "Command.h"

#include <sstream>

namespace cmds
{
	class Propfind : public Command
	{
	public:
		Propfind()
		{ }
		
		std::string getName()
		{
			return "PROPFIND";
		}
		
		HttpResponseBuilder* compute(ConnectionEnv* env, HttpRequest* request) throw(FileNotFoundException);
		
	protected:
		static void getResourceInfo(::IFile* rsFile, int rootPathSize, std::string host, std::ostringstream& stream);
	};
}

#endif	/* _CMDS_CMD_PROPFIND_H */

