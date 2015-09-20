#include "INetAddress.h"
#include "ErrorManager.h"


INetAddress::INetAddress(char* ip, uint port)
    : size(sizeof(struct sockaddr_in)),
    port(port)
{
    if(
    #if OS == WIN
        ::WSAStringToAddress(ip, AF_INET, NULL, (struct sockaddr*)&addr, &size)
    #elif OS == LINUX
        ::inet_pton(AF_INET, ip, &addr.sin_addr)
    #endif
                != 0)
        error = ::getErrorNo();
    else
        error = 0;

    addr.sin_family = AF_INET;
    addr.sin_port = ::htons(port);
}

INetAddress::INetAddress(char* ip) : INetAddress(ip, 0)
{ }

INetAddress::INetAddress(struct sockaddr_in addr)
    : size(sizeof(struct sockaddr_in)),
	addr(addr)
{
	port = ::ntohs(addr.sin_port);
}

INetAddress::INetAddress(uint port)
    : size(sizeof(struct sockaddr_in)),
    port(port)
{
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = ::htons(port);
}

INetAddress::INetAddress() : INetAddress((uint)0)
{ }




std::ostream& operator << (std::ostream& out, const INetAddress& addr)
{
	const char* ip = addr.getIP();
	out << ip << ":" << addr.getPort();
	delete(ip);
	
	return out;
}