/* $Id$ */

#ifndef __HACKED_LIBC_SIGNAL_H
#define __HACKED_LIBC_SIGNAL_H

/* to avoid __only_inline int sigaddset */
#ifdef _OPENBSD5_1
#define _ANSI_LIBRARY
#endif

#include_next <signal.h>

#endif

