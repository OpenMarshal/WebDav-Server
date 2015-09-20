#ifndef _LIBS_SERVERSOCKET_H
#define	_LIBS_SERVERSOCKET_H

#include "General.h"
#include "../_all/INetAddress.h"
#include "../_all/SocketCreationException.h"
#include "Socket.h"

class ServerSocket
{
public:
	ServerSocket(INetAddress addr, int timeout) throw(SocketCreationException);
    ServerSocket(INetAddress addr) throw(SocketCreationException);
	ServerSocket(int timeout) throw(SocketCreationException);
    ServerSocket() throw(SocketCreationException);
	
	Socket* accept();
	
	void listen();
	void listen(int maxConnections);
	
	void close();
    
    INetAddress getAddress()
    {
        return addr;
    }
    
private:
    INetAddress addr;
    
    sint sock;
};


#endif	/* _LIBS_SERVERSOCKET_H */

