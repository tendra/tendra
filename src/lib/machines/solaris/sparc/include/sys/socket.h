#ifndef __HACKED_SYS_SOCKET_INCLUDED
#define __HACKED_SYS_SOCKET_INCLUDED

#ifdef __BUILDING_LIBS
struct sockaddr ;
#pragma TenDRA argument struct sockaddr * as caddr_t
#endif

#include_next <sys/socket.h>

#endif
