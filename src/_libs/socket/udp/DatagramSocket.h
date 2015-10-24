#ifndef _LIBS_DATAGRAMSOCKET_H
#define	_LIBS_DATAGRAMSOCKET_H

#include "../_all/INetAddress.h"
#include "../_all/SocketCreationException.h"
#include "Datagram.h"

class DatagramSocket
{
public:
	DatagramSocket(INetAddress addr, int timeout) throw(SocketCreationException);
    DatagramSocket(INetAddress addr) throw(SocketCreationException);
	DatagramSocket(int timeout) throw(SocketCreationException);
    DatagramSocket() throw(SocketCreationException);
    
    void receive(Datagram* dtg) const throw(int);
    Datagram* receive(uint dataLen) const throw(int);
    
    void send(Datagram* dtg) const throw(int);
    void send(const Datagram* dtg, INetAddress dest) const throw(int);
    void send(char* data, uint len, struct sockaddr* addr, uint addrLen) const throw(int);
    void send(char* data, uint len, INetAddress dest) const throw(int);
	
	int close();
    
    INetAddress getAddress()
    {
        return addr;
    }
    
private:
    INetAddress addr;
    
    sint sock;
};


#endif	/* _LIBS_DATAGRAMSOCKET_H */

