#include "ServerSocket.h"
#include "../_all/ErrorManager.h"
#include "../_all/Sock.h"


ServerSocket::ServerSocket(INetAddress addr, int timeout) throw(SocketCreationException)
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

ServerSocket::ServerSocket(INetAddress addr) throw(SocketCreationException) : ServerSocket(addr, 0)
{ }

ServerSocket::ServerSocket(int timeout) throw(SocketCreationException) : ServerSocket(INetAddress(), timeout)
{ }

ServerSocket::ServerSocket() throw(SocketCreationException) : ServerSocket(INetAddress())
{ }

Socket* ServerSocket::accept()
{
	struct sockaddr_in addr;
	int addrLen = sizeof(addr);
	
	int clientSock = ::accept(sock, (struct sockaddr*)&addr, &addrLen);
	
	return new Socket(addr, clientSock);
}

void ServerSocket::listen()
{
	this->listen(SOMAXCONN);
}
void ServerSocket::listen(int maxConnections)
{
	::listen(sock, maxConnections);
}
void ServerSocket::close()
{
	::close(sock);
}
