#include "HttpRequest.h"
#include "General.h"

#include <sstream>
#include <iostream>

HttpRequest::HttpRequest()
	: cmd("GET"),
	file("/")
{ }

HttpRequest* HttpRequest::parseClone(const char* data, int len) throw(ParsingException)
{
	char* ndata = new char[len];
	memcpy(ndata, data, len);
	
	return HttpRequest::parse(ndata, len);
}

HttpRequest* HttpRequest::parse(char* data, int len) throw(ParsingException)
{
	HttpRequest* req = new HttpRequest();
	
	std::istringstream stream(data);
	std::string line;
	int index;
	
	// request line
	std::getline(stream, line);
	std::istringstream head(line);
	head >> req->cmd >> req->file >> req->version;
	
	
	// headers
    while(std::getline(stream, line) && !ltrim(line).empty())
	{
		index = line.find(':');
		if(index != -1)
			req->headers.emplace(::toLowerCase(line.substr(0, index)), ::trim(line.substr(index + 1)));
    }
	
	// body
	req->body = data + stream.tellg();
    req->bodySize = len - stream.tellg();
	
	
	return req;
}





const std::string HttpRequest::toString()
{
	std::ostringstream stream;
	
	stream << this->cmd << " " << this->file << " " << this->version << std::endl;
	
	for(auto x : headers)
		stream << x.first << ": " << x.second << std::endl;
	
	stream << std::endl;
	stream.write(this->body, this->bodySize);
	
	stream.flush();
	
	return stream.str();
}


uint HttpRequest::getHeadSize()
{
	return file.size() + cmd.size() + version.size() + 2;
}





HttpRequest* HttpRequestBuilder::buildAndKeep()
{
	HttpRequest* req = new HttpRequest();
	
	super::build(req);
	
	req->cmd = this->cmd;
	req->file = this->file;
	
	return req;
}
HttpRequest* HttpRequestBuilder::build()
{
	HttpRequest* req = this->buildAndKeep();
	
	delete(this);
	
	return req;
}

HttpRequestBuilder& HttpRequestBuilder::setCommand(std::string cmd)
{
	this->cmd = cmd;
	
	return *this;
}
HttpRequestBuilder& HttpRequestBuilder::setCommand(const char* cmd)
{
	return setCommand(std::string(cmd));
}

HttpRequestBuilder& HttpRequestBuilder::setFile(std::string file)
{
	this->cmd = cmd;
	
	return *this;
}
HttpRequestBuilder& HttpRequestBuilder::setFile(const char* file)
{
	return setFile(std::string(file));
}



