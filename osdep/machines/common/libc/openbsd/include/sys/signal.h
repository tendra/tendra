/* $Id$ */

#ifndef __HACKED_LIBC_SYS_SIGNAL_H
#define __HACKED_LIBC_SYS_SIGNAL_H

/* for SIG_IGN and SIG_ERR */
#if defined(_OPENBSD5_1) || defined(_OPENBSD5_2)
#pragma TenDRA begin
#pragma TenDRA conversion analysis ( int-pointer explicit ) off
#endif

#include_next <sys/signal.h>

#if defined(_OPENBSD5_1) || defined(_OPENBSD5_2)
#pragma TenDRA end
#endif

#endif

