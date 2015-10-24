#include "Socket.h"
#include "_libs/error/ErrorManager.h"
#include "../_all/Sock.h"


Socket::Socket(INetAddress addr, int timeout) throw(SocketCreationException)
{
    this->addr = addr;

    sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock == -1)
	{
		int error = ::getErrorNo();
		throw SocketCreationException("socket", error);
	}
    
	if(timeout > 0)
		::setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));

    if(::bind(sock, addr.toPtrSockAddr(), addr.getLength()) == -1)
	{
		int error = ::getErrorNo();
		throw SocketCreationException("bind", error);
	}
}

Socket::Socket(INetAddress addr) throw(SocketCreationException)
	: Socket(addr, 0)
{ }

Socket::Socket(struct sockaddr_in addr, int sock)
	: addr(addr),
	sock(sock)
{ }


void Socket::send(const char* data, uint len) throw(int)
{
	this->send(data, 0, len);
}
void Socket::send(const char* data, uint start, uint len) throw(int)
{
    if(::sendto(sock, data + start, len, start, addr.toPtrSockAddr(), addr.getLength()) < 0)
        throw ::getErrorNo();
}


uint Socket::receive(char* data, uint maxLen) throw(int)
{
	return this->receive(data, 0, maxLen);
}
uint Socket::receive(char* data, uint start, uint maxLen) throw(int)
{
	int read;
	
	#if OS == WIN
		read = ::recvfrom(sock, data + start, maxLen, 0, addr.toPtrSockAddr(), (int*)addr.getPtrLength());
	#elif OS == LINUX
		read = ::recvfrom(sock, data + start, maxLen, 0, addr.toPtrSockAddr(), addr.getPtrLength());
	#endif

    if(read < 0)
        throw ::getErrorNo();
	
	return (uint)read;
}



int Socket::close()
{
	#if OS == WIN
		return ::closesocket(sock);
	#elif OS == LINUX
		return ::close(sock);
	#endif
}
