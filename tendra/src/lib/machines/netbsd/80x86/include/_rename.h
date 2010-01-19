/* $Id$ */

#ifndef __HACKED__RENAME
#define __HACKED__RENAME

/*
 * This is included first, since it also attempts to define __RENAME.
 */
#ifdef _NETBSD5
#include <sys/cdefs.h>
#endif


/* to elide __RENAME() where it is not possible to avoid */
#ifdef _NETBSD5
#if defined(__RENAME)
#undef __RENAME
#endif
#define __RENAME(x)	/* empty */
#endif


#endif

