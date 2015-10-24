#ifndef _LIBS_HTTP_MESSAGE_H
#define	_LIBS_HTTP_MESSAGE_H

#include "General.h"
#include "_libs/exception/exception.h"
#include "_libs/string/ExString.h"

#include <string>
#include <map>


template<class T>
class HttpMessageBuilder;


class HttpMessage
{
public:
	~HttpMessage()
	{
		delete(body);
	}
	
	bool containsHeader(const char* name);
	bool containsHeader(std::string name);
	
	std::string getHeader(const char* name, const char* defaultValue);
	std::string getHeader(std::string name, std::string defaultValue);
	
	uint getHeaderCount()
	{
		return this->headers.size();
	}
	
	std::string getVersion()
	{
		return version;
	}
	const char* getContent()
	{
		return body;
	}
	uint getContentLength()
	{
		return bodySize;
	}
	
	virtual uint getHeadSize() = 0;
	uint getSize();
	
protected:
	std::map<std::string, std::string> headers;
	
	std::string version;
	
	const char* body;
	uint bodySize;
	
	template<class T>
	friend class HttpMessageBuilder;
};


#include "HttpMessageBuilder.tpp"

#endif	/* _LIBS_HTTP_MESSAGE_H */

