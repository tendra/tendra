#ifndef __HACKED_SYS_WAIT_INCLUDED
#define __HACKED_SYS_WAIT_INCLUDED

#include_next <sys/wait.h>

#ifdef WSTOPSIG
#undef WSTOPSIG
#define WSTOPSIG( w )	WEXITSTATUS ( w )
#endif

#endif
