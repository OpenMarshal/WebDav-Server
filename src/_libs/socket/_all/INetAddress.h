#ifndef _LIBS_INETADDRESS_H
#define	_LIBS_INETADDRESS_H

#include <iostream>
#include "Sock.h"

class INetAddress
{
public:
    INetAddress(char* ip, uint port) throw(int);
    INetAddress(char* ip) throw(int);
	
    INetAddress(struct sockaddr_in addr);
    
    INetAddress(uint port);
    INetAddress();
    
	const char* getIP() const;
	
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
};

#endif	/* _LIBS_INETADDRESS_H */

