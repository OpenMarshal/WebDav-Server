#ifndef _LIBS_INETADDRESS_H
#define	_LIBS_INETADDRESS_H

#include <iostream>
#include "Sock.h"

class INetAddress
{
public:
    INetAddress(char* ip, uint port);
    INetAddress(char* ip);
	
    INetAddress(struct sockaddr_in addr);
    
    INetAddress(uint port);
    INetAddress();
    
    bool isErroneous()
    {
        return error != 0;
    }
    sint getError()
    {
        return error;
    }
    
	const char* getIP() const
	{
		#if OS == WIN
			return inet_ntoa(addr.sin_addr);
		#elif OS == LINUX
			inet_ntop(AF_INET, &addr.sin_addr, ip, 16);
			return ip;
		#endif
	}
	
    struct sockaddr_in toSockAddrIn() const
    {
        return addr;
    }
    struct sockaddr_in* toPtrSockAddrIn()
    {
        return &addr;
    }
    struct sockaddr* toPtrSockAddr() const
    {
        return (struct sockaddr*)&addr;
    }
    sint getLength() const
    {
        return size;
    }
    uint* getPtrLength() const
    {
        return (uint*)&size;
    }
    
    uint getPort() const
    {
        return port;
    }
	
	
	friend std::ostream& operator << (std::ostream& out, const INetAddress& addr);
    
private:
    struct sockaddr_in addr;
    sint size;
    
    uint port;
    
    sint error;
};

#endif	/* _LIBS_INETADDRESS_H */

