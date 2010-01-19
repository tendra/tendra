/* $Id$ */

#ifndef __HACKED_LIMITS_H
#define __HACKED_LIMITS_H

#ifdef _NETBSD5
#ifdef __BUILDING_TDF_UNIX95_LIMITS_H
#ifndef ATEXIT_MAX
#define ATEXIT_MAX 32	/* NetBSD has no hard limit. This is the minimum maximum for UNIX95 */
#endif
#endif
#endif

#ifdef _NETBSD5
#ifdef __BUILDING_TDF_UNIX95_LIMITS_H
#define _NETBSD_SOURCE	/* for vaddr_t for <machine/vmparam.h> */
#include <machine/vmparam.h>	/* for PAGE_SIZE, missing */
#ifndef PAGESIZE
#define PAGESIZE PAGE_SIZE	/* missing */
#endif
#endif
#endif


#include_next <limits.h>

#endif

