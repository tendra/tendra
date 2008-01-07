#ifndef __HACKED_SYS_SOCKET_INCLUDED
#define __HACKED_SYS_SOCKET_INCLUDED

#ifdef __BUILDING_LIBS
#define u_int	int
#endif

#include_next <sys/socket.h>

#endif
