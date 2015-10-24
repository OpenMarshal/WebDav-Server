//#ifndef _LIBS_SOCK_H
//#define	_LIBS_SOCK_H

#include "General.h"

#if	defined(__cplusplus)
extern "C" {
#endif

#if OS == WIN
    #include <winsock2.h>
    #include <io.h>
#endif
#if OS == LINUX
    #include <arpa/inet.h>
    #include <sys/socket.h>
#endif

#if	defined(__cplusplus)
}
#endif

//#endif	/* _LIBS_SOCK_H */

