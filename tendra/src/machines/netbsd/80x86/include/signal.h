/* $Id$ */

#ifndef __HACKED_SIGNAL_H
#define __HACKED_SIGNAL_H

#ifdef _NETBSD5
#include <machine/signal.h>	/* for sig_atomic_t */
#endif

#ifdef _NETBSD5
#include "_rename.h"
#endif

#ifdef _NETBSD5
#ifdef __BUILDING_TDF_UNIX95_SIGNAL_H_SIGINFO_T
#include <sys/siginfo.h>	/* for siginfo_t */
#endif
#endif


#include_next <signal.h>

#endif

