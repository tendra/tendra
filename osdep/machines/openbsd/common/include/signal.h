/* $Id$ */

#ifndef __HACKED_LIBC_SIGNAL_H
#define __HACKED_LIBC_SIGNAL_H

/* to avoid __only_inline int sigaddset */
#if defined(_OPENBSD5_1) || defined(_OPENBSD5_3) || defined(_OPENBSD5_4) \
	|| defined(_OPENBSD5_5) || defined(_OPENBSD5_6)
#define _ANSI_LIBRARY
#endif

#include_next <signal.h>

#endif

