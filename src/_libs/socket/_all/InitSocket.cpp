#include "InitSocket.h"

int initSockets()
{
#if OS == WIN
    WSADATA wsaData;
    return ::WSAStartup(MAKEWORD(2, 2), &wsaData);
#else
	return 0;
#endif
}