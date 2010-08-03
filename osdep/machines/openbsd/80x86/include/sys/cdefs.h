/* $Id$ */

#ifndef __HACKED_SYS_CDEFS_H
#define __HACKED_SYS_CDEFS_H


#ifdef _OPENBSD4
#ifdef __restrict
#undef __restrict
#endif
#define __restrict	/* empty */
#endif


#include_next <sys/cdefs.h>

#endif

