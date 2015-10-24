#ifndef _LIBS_ERRORMANAGER_H
#define	_LIBS_ERRORMANAGER_H

#include "General.h"

#if OS == WIN
    #include <winsock2.h>
#elif OS == LINUX
    #include <errno.h>
#endif

#ifdef	__cplusplus
extern "C" {
#endif

inline sint getErrorNo()
{
    #if OS == WIN
        return WSAGetLastError();
    #endif
    #if OS == LINUX
        return errno;
    #endif
}


#ifdef	__cplusplus
}
#endif

#endif	/* _LIBS_ERRORMANAGER_H */

