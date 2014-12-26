/* $Id$ */

#ifndef __HACKED_LIBC_SYS_CDEFS_H
#define __HACKED_LIBC_SYS_CDEFS_H

#if defined(_OPENBSD5_1) || defined(_OPENBSD5_2) || defined(_OPENBSD5_3) \
	|| defined(_OPENBSD5_4) || defined(_OPENBSD5_5)
#define __restrict
#endif

#include_next <sys/cdefs.h>

#endif

