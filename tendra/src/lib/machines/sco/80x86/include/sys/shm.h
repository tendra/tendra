#ifndef __HACKED_SYS_SHM_INCLUDED
#define __HACKED_SYS_SHM_INCLUDED

#ifdef __BUILDING_LIBS
#undef _XOPEN_SOURCE
typedef unsigned short ushort ;
#endif

#include_next <sys/shm.h>

#endif
