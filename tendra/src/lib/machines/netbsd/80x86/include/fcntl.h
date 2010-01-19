/* $Id$ */

#ifndef __HACKED_FCNTL_H
#define __HACKED_FCNTL_H


#ifdef _NETBSD5
#ifdef __BUILDING_TDF_UNIX95_FCNTL_H
#ifndef _NETBSD_SOURCE
#define _NETBSD_SOURCE  /* for F_GETOWN/F_SETOWN */
#endif
#endif
#endif

#ifdef _NETBSD5
#ifdef __BUILDING_TDF_XPG3_FCNTL_H
#ifndef _NETBSD_SOURCE
#define _NETBSD_SOURCE	/* for O_SYNC */
#endif
#endif
#endif

#ifdef _NETBSD5
#ifdef __BUILDING_TDF_XPG3_FCNTL_H_O_SYNC
#ifndef _NETBSD_SOURCE
#define _NETBSD_SOURCE	/* for O_SYNC */
#endif
#endif
#endif

#ifdef _NETBSD5
#ifdef __BUILDING_TDF_SVID3_FCNTL_H
#ifndef _NETBSD_SOURCE
#define _NETBSD_SOURCE	/* for O_NDELAY */
#endif
#endif
#endif


#include_next <fcntl.h>

#endif

