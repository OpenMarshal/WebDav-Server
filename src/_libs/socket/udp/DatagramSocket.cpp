#include "DatagramSocket.h"
#include "../_all/ErrorManager.h"
#include "../_all/Sock.h"


DatagramSocket::DatagramSocket(INetAddress addr, int timeout) throw(SocketCreationException)
{
    this->addr = addr;

    sock = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
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

DatagramSocket::DatagramSocket(INetAddress addr) throw(SocketCreationException) : DatagramSocket(addr, 0)
{ }

DatagramSocket::DatagramSocket(int timeout) throw(SocketCreationException) : DatagramSocket(INetAddress(), timeout)
{ }

DatagramSocket::DatagramSocket() throw(SocketCreationException) : DatagramSocket(INetAddress())
{ }

void DatagramSocket::receive(Datagram* dtg) const throw(int)
{
    INetAddress* addr = dtg->getPtrINetAddress();

#if OS == WIN
    dtg->len = ::recvfrom(sock, dtg->data, dtg->maxLen, 0, addr->toPtrSockAddr(), (int*)addr->getPtrLength());
#elif OS == LINUX
    dtg->len = ::recvfrom(sock, dtg->data, dtg->maxLen, 0, addr->toPtrSockAddr(), addr->getPtrLength());
#endif

    if(dtg->len < 0)
        throw ::getErrorNo();
}
Datagram* DatagramSocket::receive(uint dataLen) const throw(int)
{
    Datagram* dtg = new Datagram();
    dtg->data = new char[dataLen];
    dtg->maxLen = dataLen;
    dtg->homemadeData = true;

	try
	{
		receive(dtg);
	}
	catch(int ex)
	{
		delete(dtg);
		throw ex;
	}

    return dtg;
}

void DatagramSocket::send(Datagram* dtg) const throw(int)
{
    return this->send(dtg, dtg->getINetAddress());
}
void DatagramSocket::send(const Datagram* dtg, INetAddress dest) const throw(int)
{
    return this->send(dtg->data, dtg->len, dest.toPtrSockAddr(), dest.getLength());
}
void DatagramSocket::send(char* data, uint len, INetAddress dest) const throw(int)
{
    return this->send(data, len, dest.toPtrSockAddr(), dest.getLength());
}
void DatagramSocket::send(char* data, uint len, struct sockaddr* addr, uint addrLen) const throw(int)
{
    if(::sendto(sock, data, len, 0, addr, addrLen) < 0)
        throw ::getErrorNo();
}