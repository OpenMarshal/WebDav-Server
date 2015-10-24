#include "HttpResponse.h"
#include "General.h"

#include <sstream>
#include <iostream>

HttpResponse::HttpResponse()
	: msg("OK"),
	code(200)
{ }


HttpResponse* HttpResponse::parseClone(const char* data, int len) throw(ParsingException)
{
	char* ndata = new char[len];
	memcpy(ndata, data, len);
	
	return HttpResponse::parse(ndata, len);
}

HttpResponse* HttpResponse::parse(char* data, int len) throw(ParsingException)
{
	HttpResponse* req = new HttpResponse();
	
	std::istringstream stream(data);
	std::string line;
	int index;
	
	// request line
	std::getline(stream, line);
	std::istringstream head(line);
	head >> req->version >> req->code >> req->msg;
	
	
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





const std::string HttpResponse::toString()
{
	std::ostringstream stream;
	
	stream << this->version << " " << this->code << " " << this->msg << std::endl;
	
	for(auto x : headers)
		stream << x.first << ": " << x.second << std::endl;
	
	stream << std::endl;
	stream.write(this->body, this->bodySize);
	
	stream.flush();
	
	return stream.str();
}


uint HttpResponse::getHeadSize()
{
	int codeSize;
	int codeTemp = code;
	for(codeSize = 0; codeTemp > 0; codeSize++)
		codeTemp = codeTemp / 10;
	
	return msg.size() + codeSize + version.size() + 2;
}







HttpResponse* HttpResponseBuilder::buildAndKeep()
{
	HttpResponse* req = new HttpResponse();
	
	super::build(req);
	
	req->code = this->code;
	req->msg = this->msg;
	
	return req;
}
HttpResponse* HttpResponseBuilder::build()
{
	HttpResponse* req = this->buildAndKeep();
	
	delete(this);
	
	return req;
}

HttpResponseBuilder& HttpResponseBuilder::setMessage(std::string msg)
{
	this->msg = msg;
	
	return *this;
}
HttpResponseBuilder& HttpResponseBuilder::setMessage(const char* msg)
{
	return setMessage(std::string(msg));
}

HttpResponseBuilder& HttpResponseBuilder::setCode(int code)
{
	this->code = code;
	
	return *this;
}



