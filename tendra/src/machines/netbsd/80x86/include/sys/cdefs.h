/* $Id$ */

#ifndef __HACKED_SYS_CDEFS_H
#define __HACKED_SYS_CDEFS_H


/* to avoid requiring __RENAME() where possible */
#ifdef _NETBSD5
#define _STANDALONE
#endif


#include_next <sys/cdefs.h>

#endif

