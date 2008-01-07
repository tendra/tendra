#ifndef __HACKED_LINUX_SIGNAL_INCLUDED
#define __HACKED_LINUX_SIGNAL_INCLUDED

#ifdef __BUILDING_LIBS
#define sigaction	sigaction_wrong
#endif

#include_next <linux/signal.h>

#ifdef __BUILDING_LIBS
#undef sigaction
struct sigaction {
    __sighandler_t sa_handler ;
    sigset_t sa_mask ;
    int sa_flags ;		/* This is what it should be */
    void ( *sa_restorer ) ( void ) ;
} ;
#endif

#endif
