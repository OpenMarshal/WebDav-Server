#ifndef _LIBS_HTTP_RESPONSE_H
#define	_LIBS_HTTP_RESPONSE_H

#include "_libs/exception/exception.h"
#include "_libs/string/ExString.h"
#include "HttpMessage.h"

#include <iostream>
#include <sstream>
#include <string>
#include <map>

class HttpResponse;

class HttpResponseBuilder : public HttpMessageBuilder<HttpResponseBuilder>
{
private:
	HttpResponseBuilder()
	{ }

	typedef HttpMessageBuilder<HttpResponseBuilder> super;
	
	friend class HttpResponse;
	
public:
	
	HttpResponseBuilder& setMessage(std::string cmd);
	HttpResponseBuilder& setMessage(const char* cmd);
	
	HttpResponseBuilder& setCode(int code);
	
	HttpResponse* buildAndKeep();
	HttpResponse* build();
	
protected:
	std::string msg;
	int code;
};

class HttpResponse : public HttpMessage
{
public:

	static HttpResponse* parse(char* data, int len) throw(ParsingException);
	static HttpResponse* parseClone(const char* data, int len) throw(ParsingException);
	
	std::string getMessage()
	{
		return msg;
	}
	int getCode()
	{
		return code;
	}
	
	static HttpResponseBuilder& create()
	{
		return *new HttpResponseBuilder();
	}
	
	const char* toBytes()
	{
		std::string str = toString();
		int size = getSize();
		char* data = new char[size + 1];
		memcpy(data, str.c_str(), size);
		data[size] = '\0';
		return data;
	}
	const std::string toString();
	
	uint getHeadSize();
	
private:
	HttpResponse();
	
	std::string msg;
	int code;
	
	friend class HttpResponseBuilder;
};

#endif	/* _LIBS_HTTP_RESPONSE_H */

