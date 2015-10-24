#include "INetAddress.h"
#include "_libs/error/ErrorManager.h"


INetAddress::INetAddress(char* ip, uint port) throw(int)
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
		throw ::getErrorNo();

    addr.sin_family = AF_INET;
    addr.sin_port = ::htons(port);
}

INetAddress::INetAddress(char* ip) throw(int)
	: INetAddress(ip, 0)
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


const char* INetAddress::getIP() const
{
	#if OS == WIN
		// No need to free the result :
		//   It is located in a reserved memory area
		//   and this area is overrided each time
		//   this function is called.
		return inet_ntoa(addr.sin_addr);
	#elif OS == LINUX
		// To work like Windows do, we need to
		// allocate a reserved area for ip.
		// Each time this function is called,
		// this area is overrided.
		static char ip[16];
		inet_ntop(AF_INET, &addr.sin_addr, ip, 16);
		return ip;
	#endif
}


std::ostream& operator << (std::ostream& out, const INetAddress& addr)
{
	const char* ip = addr.getIP();
	out << ip << ":" << addr.getPort();
	
	return out;
}