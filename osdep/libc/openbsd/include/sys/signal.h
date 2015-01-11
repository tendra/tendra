/* $Id$ */

#ifndef __HACKED_LIBC_SYS_SIGNAL_H
#define __HACKED_LIBC_SYS_SIGNAL_H

/* for SIG_IGN and SIG_ERR */
#if defined(_OPENBSD5_1) || defined(_OPENBSD5_2) || defined(_OPENBSD5_3) \
	|| defined(_OPENBSD5_4) || defined(_OPENBSD5_5) || defined(_OPENBSD5_6)
#pragma TenDRA begin
#pragma TenDRA conversion analysis ( int-pointer explicit ) off
#endif

#include_next <sys/signal.h>

#if defined(_OPENBSD5_1) || defined(_OPENBSD5_2) || defined(_OPENBSD5_3) \
	|| defined(_OPENBSD5_4) || defined(_OPENBSD5_5) || defined(_OPENBSD5_6)
#pragma TenDRA end
#endif

#endif

