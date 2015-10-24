#ifndef _LIBS_SOCKET_H
#define	_LIBS_SOCKET_H

#include "General.h"
#include "../_all/INetAddress.h"
#include "../_all/SocketCreationException.h"

class Socket
{
public:
	Socket(INetAddress addr, int timeout) throw(SocketCreationException);
    Socket(INetAddress addr) throw(SocketCreationException);
	Socket(struct sockaddr_in, int sock);
	
	void send(const char* data, uint len) throw(int);
	void send(const char* data, uint start, uint len) throw(int);
	
	uint receive(char* data, uint maxLen) throw(int);
	uint receive(char* data, uint start, uint len) throw(int);
	
	int close();
    
    INetAddress getAddress()
    {
        return addr;
    }
    
private:
    INetAddress addr;
    sint sock;
};


#endif	/* _LIBS_SOCKET_H */

