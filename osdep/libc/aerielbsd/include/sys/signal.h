/* $Id$ */

#ifndef __HACKED_LIBC_SYS_SIGNAL_H
#define __HACKED_LIBC_SYS_SIGNAL_H

/* for SIG_IGN and SIG_ERR */
#ifdef _AERIELBSD1
#pragma TenDRA begin
#pragma TenDRA conversion analysis ( int-pointer explicit ) off
#endif

#include_next <sys/signal.h>

#ifdef _AERIELBSD1
#pragma TenDRA end
#endif

#endif

