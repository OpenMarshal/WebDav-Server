#ifndef _CONNECTION_ENV_H
#define	_CONNECTION_ENV_H

#include "_libs/file/file.h"
#include "_libs/protocol/http.h"

class ConnectionEnv
{
public:
	ConnectionEnv(const char* root)
		: root(root)
	{ }
	
	std::string getRoot()
	{
		return root;
	}
	
	::IFile* getFileFromPath(HttpRequest* request)
	{
		return getFileFromPath(request->getFile());
	}
	
	::IFile* getFileFromPath(std::string path)
	{
		std::string fullPath(this->getRoot());
		fullPath += path;
		return new ::File(fullPath);
	}
	
	::IFile* getFileFromPath(const char* path)
	{
		return getFileFromPath(std::string(path));
	}
	
protected:
	std::string root;
};

#endif	/* _CONNECTION_ENV_H */

