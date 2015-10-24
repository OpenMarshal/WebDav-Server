#include "ServerSocket.h"
#include "_libs/error/ErrorManager.h"
#include "_libs/thread/thread.h"
#include "../_all/Sock.h"
#include <thread>

ServerSocket::ServerSocket(INetAddress addr, int timeout) throw(SocketCreationException)
{
    this->addr = addr;

    sock = ::socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1)
	{
		int error = ::getErrorNo();
		throw SocketCreationException("socket", error);
	}
    
	if(timeout > 0)
		::setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
	
	int on = 1;
	if(::setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on)) < 0)
	{
		int error = ::getErrorNo();
		throw SocketCreationException("setsockopt.SO_REUSEADDR", error);
	}

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

struct s_accept
{
	ServerSocket* _this;
	Socket** csock;
};
static void* acceptBlocking(struct s_accept* data)
{
	struct sockaddr_in addr;
	int addrLen = sizeof(addr);
	
	int clientSock = ::accept(data->_this->getSocketID(), (struct sockaddr*)&addr, &addrLen);
	
	(*data->csock) = new Socket(addr, clientSock);
	
	void* xd = new int(30);
	return xd;
}
Socket* ServerSocket::accept()
{
	Socket* csock;
	struct s_accept data = { this, &csock };
	
	Thread t_accept((thread_method)::acceptBlocking);
	t_accept.start(&data);
	t_accept.join();
	
	return csock;
}
void ServerSocket::accept(Socket* csock)
{
	csock = 0;
	struct s_accept data = { this, &csock };
	
	Thread t_accept((thread_method)::acceptBlocking);
	t_accept.start(&data);
	t_accept.join();
}

void ServerSocket::listen() throw(SocketCreationException)
{
	this->listen(SOMAXCONN);
}
void ServerSocket::listen(int maxConnections) throw(SocketCreationException)
{
	if(::listen(sock, maxConnections) < 0)
	{
		int error = ::getErrorNo();
		throw SocketCreationException("listen", error);
	}
}
int ServerSocket::close()
{
	#if OS == WIN
		return ::closesocket(sock);
	#elif OS == LINUX
		return ::close(sock);
	#endif
}
