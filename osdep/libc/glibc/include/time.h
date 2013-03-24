/* $Id$ */

#ifndef __HACKED_LIBC_TIME_H
#define __HACKED_LIBC_TIME_H

#if defined(_GLIBC2_15)
#ifdef __BUILDING_TDF_POSIX_TIME_H
#define CLK_TCK CLOCKS_PER_SEC
#endif
#endif

#include_next <time.h>

#endif

