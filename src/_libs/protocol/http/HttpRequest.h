#ifndef _LIBS_HTTP_REQUEST_H
#define	_LIBS_HTTP_REQUEST_H

#include "_libs/exception/exception.h"
#include "_libs/string/ExString.h"
#include "HttpMessage.h"

#include <string>
#include <map>

class HttpRequest;

class HttpRequestBuilder : public HttpMessageBuilder<HttpRequestBuilder>
{
private:
	HttpRequestBuilder()
	{ }

	typedef HttpMessageBuilder<HttpRequestBuilder> super;
	
	friend class HttpRequest;
	
public:
	
	HttpRequestBuilder& setCommand(std::string cmd);
	HttpRequestBuilder& setCommand(const char* cmd);
	
	HttpRequestBuilder& setFile(std::string file);
	HttpRequestBuilder& setFile(const char* file);
	
	HttpRequest* buildAndKeep();
	HttpRequest* build();
	
protected:
	std::string file;
	std::string cmd;
};

class HttpRequest : public HttpMessage
{
public:

	static HttpRequest* parse(char* data, int len) throw(ParsingException);
	static HttpRequest* parseClone(const char* data, int len) throw(ParsingException);
	
	std::string getCommand()
	{
		return cmd;
	}
	std::string getFile()
	{
		return file;
	}
	
	static HttpRequestBuilder& create()
	{
		return *new HttpRequestBuilder();
	}
	
	const char* toBytes()
	{
		return (toString().c_str());
	}
	const std::string toString();
	
	uint getHeadSize();
	
private:
	HttpRequest();
	
	std::string file;
	std::string cmd;
	
	friend class HttpRequestBuilder;
};

#endif	/* _LIBS_HTTP_REQUEST_H */

