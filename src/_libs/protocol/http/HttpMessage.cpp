#include "HttpMessage.h"
#include "General.h"

#include <sstream>
#include <iostream>

bool HttpMessage::containsHeader(const char* name)
{
	std::string str(name);
	return containsHeader(str);
}
bool HttpMessage::containsHeader(std::string name)
{
	return headers.find(name) != headers.end();
}

std::string HttpMessage::getHeader(const char* name, const char* defaultValue)
{
	std::string str(name);
	std::string strDef(defaultValue);
	return getHeader(str, strDef);
}
std::string HttpMessage::getHeader(std::string name, std::string defaultValue)
{
	std::map<std::string, std::string>::iterator it;
	
	it = headers.find(::toLowerCase(name));
	if(it == headers.end())
		return defaultValue;
	else
		return it->second;
}

uint HttpMessage::getSize()
{
	int lineReturnSize = 1;
	
	int headersSize = 0;
	for(auto x : headers)
		headersSize += x.first.size() + x.second.size() + 2 + lineReturnSize;
	
	return getHeadSize() + getContentLength() + headersSize + lineReturnSize * 2;
}


