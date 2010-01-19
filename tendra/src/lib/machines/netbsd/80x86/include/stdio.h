/* $Id$ */

#ifndef __HACKED_STDIO_H
#define __HACKED_STDIO_H

#ifdef _NETBSD5
#include "_rename.h"
#endif


#ifdef _NETBSD5
#ifdef __BUILDING_TDF_SVID3_STDIO_H
#ifndef _NETBSD_SOURCE
#define _NETBSD_SOURCE	/* for P_tmpdir */
#endif
#endif
#endif


#include_next <stdio.h>

#endif

