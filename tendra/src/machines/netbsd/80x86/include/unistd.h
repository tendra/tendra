/* $Id$ */

#ifndef __HACKED_UNISTD_H
#define __HACKED_UNISTD_H

#ifdef _NETBSD5
#include "_rename.h"
#endif

#ifdef _NETBSD5
#ifdef __BUILDING_TDF_UNIX95_UNISTD_H
#ifndef _SC_XOPEN_UNIX
#define _SC_XOPEN_UNIX	/* missing */
#endif
#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED	/* for F_LOCK et al. */
#endif
#endif
#endif

#ifdef _NETBSD5
#ifdef __BUILDING_TDF_XPG3_UNISTD_H_U_PLUS
#ifndef _SC_XOPEN_VERSION
#define _SC_XOPEN_VERSION	3  /* missing */
#endif
#endif
#endif


#include_next <unistd.h>

#endif

