/* $Id$ */

#ifndef __HACKED_NETINET_IN_H
#define __HACKED_NETINET_IN_H

#ifdef _NETBSD5
#include <sys/cdefs.h>
#endif


#ifdef _NETBSD5
#ifdef __packed
#undef __packed
#endif
#define __packed	/* empty */
#endif


#include_next <netinet/in.h>

#endif

