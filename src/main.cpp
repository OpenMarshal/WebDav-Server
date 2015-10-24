#include "General.h"
#include "_libs/string/ExString.h"
#include "_libs/socket/tcp.h"
#include "_libs/protocol/http.h"
#include "_libs/thread/thread.h"
#include "_libs/file/file.h"
#include "commands/CommandManager.h"

#include <fstream>
#include <time.h>


HttpResponse* computeRequest(HttpRequest* req, CommandManager* cmdMng)
{
	HttpResponseBuilder* res;
	
	std::string resDataString(req->toBytes(), req->getSize());
	::getOutputMutex().lock();
	getOutput() << std::endl << "************IN**************" << std::endl;
	getOutput() << resDataString << std::endl;
	
	getOutput() << " :: " << req->getCommand() << std::endl;
	::getOutputMutex().unlock();
	
	try
	{
		Command* cmd = cmdMng->getCommand(req->getCommand());
		
		ConnectionEnv env("root");
		res = cmd->compute(&env, req);
	}
	catch(FileNotFoundException ex)
	{
		::getOutputMutex().lock();
		getOutput() << " ** NOT FOUND : " << ex.getFilePath() << std::endl;
		::getOutputMutex().unlock();
		res = &HttpResponse::create()
			.setMessage("Not Found")
			.setCode(404);
	}
	catch(CommandNotFoundException ex)
	{
		res = &HttpResponse::create()
			.setMessage("Not Implemented")
			.setCode(501);
	}
	
	time_t rawtime;
	struct tm* timeinfo;
	char date[100];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	
	strftime(date, 100, "%a, %d %b %Y %X GMT", timeinfo);
	
	return (*res)
			.addHeader("Connection", "keep-alive")
			.addHeader("Date", date)
			.addHeader("Server", "WebDav Server Master")
			.addHeader("Keep-Alive", "timeout=5, max=100")
			.build();
}

struct server_runtime_data
{
	Socket* client;
	CommandManager* cmdMng;
};

static void server_runtime(server_runtime_data* _data)
{
	Socket* client = _data->client;
	
	char data[2000 + 1];
	uint nb = client->receive(data, 2000);

	HttpRequest* req = HttpRequest::parse(data, nb);

	HttpResponse* res = ::computeRequest(req, _data->cmdMng);

	std::string resDataString(res->toBytes(), res->getSize());

	::getOutputMutex().lock();
	getOutput() << std::endl << "****************************" << std::endl;
	getOutput() << res->getMessage() << std::endl;
	getOutput() << "*********" << std::endl;
	getOutput() << resDataString;
	getOutput() << std::endl << "****************************" << std::endl;
	::getOutputMutex().unlock();

	client->send(res->toBytes(), res->getSize());

	delete(res);

	client->close();
	
	delete(client);
	delete(_data);
}

int main(int argc, char* argv[])
{
	initSockets();
	
	CommandManager cmdMng;
	cmdMng.addCommand(new cmds::Options())
		.addCommand(new cmds::Propfind());
	
	try
	{
		ServerSocket sock(INetAddress(1900));
		
		sock.listen();
		
		do
		{
			Socket* client = sock.accept();
			
			struct server_runtime_data* _data = new struct server_runtime_data;
			_data->client = client;
			_data->cmdMng = &cmdMng;
			
			(new Thread((thread_method)server_runtime))->start(_data);
			
		} while(true);
	}
	catch(SocketCreationException& ex)
	{
		::getOutputMutex().lock();
		getOutput() << " ERROR! " << ex.getFunctionName() << " - " << ex.getErrorNo();
		::getOutputMutex().unlock();
	}
	
	stopSockets();
	
	return 0;
}