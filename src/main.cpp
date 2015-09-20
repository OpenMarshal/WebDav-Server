#include "General.h"
#include "_libs/string/ExString.h"
#include "_libs/socket/tcp.h"

#include <fstream>

int main(int argc, char* argv[])
{
	initSockets();
	
	try
	{
		ServerSocket sock(INetAddress(1900));
		getOutput() << "CREATED! : ";
		
		sock.listen();
		getOutput() << " LISTENING!";
		Socket* client = sock.accept();
		
		getOutput() << " DONE! " << client->getAddress();
	}
	catch(SocketCreationException& ex)
	{
		getOutput() << " ERROR! " << ex.getFunctionName() << " - " << ex.getErrorNo();
	}
	
	return 0;
}