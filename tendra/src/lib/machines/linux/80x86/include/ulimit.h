#ifndef __HACKED_ULIMIT_INCLUDED
#define __HACKED_ULIMIT_INCLUDED

#ifdef __BUILDING_LIBS
#define UL_GETFSIZE	1
#define UL_SETFSIZE	1
extern long ulimit ( int, ... ) ;
#else
#include_next <ulimit.h>
#endif

#endif
