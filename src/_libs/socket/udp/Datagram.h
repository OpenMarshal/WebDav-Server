#ifndef _LIBS_DATAGRAM_H
#define	_LIBS_DATAGRAM_H

#include "General.h"
#include "../_all/INetAddress.h"

class DatagramSocket;

class Datagram
{
public:
    Datagram();
    Datagram(char* data, uint maxLen);
    Datagram(char* data, sint len, uint maxLen);

    char* getData()
    {
        return data;
    }
    sint getLength()
    {
        return len;
    }
    uint getMaxLength()
    {
        return maxLen;
    }
    
    INetAddress getINetAddress()
    {
        return addr;
    }
    INetAddress* getPtrINetAddress()
    {
        return &addr;
    }

    char* getStrAddress()
    {
        return inet_ntoa(addr.toPtrSockAddrIn()->sin_addr);
    }
    struct in_addr getAddress()
    {
        return addr.toPtrSockAddrIn()->sin_addr;
    }
    ushort getPort()
    {
        return addr.toPtrSockAddrIn()->sin_port;
    }

    void dispose()
    {
        if(homemadeData)
            delete(data);
        delete(this);
    }

private:
    char* data;
    uint maxLen;
    sint len;
    
    bool homemadeData;

    INetAddress addr;
    
    
    friend class DatagramSocket;
};

#endif	/* _LIBS_DATAGRAM_H */

