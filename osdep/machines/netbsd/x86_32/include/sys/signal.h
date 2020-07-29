#ifndef __HACKED_SIGNAL_H
#define __HACKED_SIGNAL_H

/* for SIG_IGN and friends */
#if defined(_NETBSD5_1)
#pragma TenDRA begin
#pragma TenDRA conversion analysis (pointer-int) off
#endif

#include_next <sys/signal.h>

#if defined(_NETBSD5_1)
#pragma TenDRA end
#endif

/* for sig_atomic_t */
#if defined(_NETBSD5_1)
#include_next <machine/signal.h>
#endif

#endif

