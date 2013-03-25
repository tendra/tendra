/* $Id$ */

#ifndef __HACKED_LIBC_FTW_H
#define __HACKED_LIBC_FTW_H

#ifdef _GLIBC2_14
#ifdef __BUILDING_TDF_XPG3_FTW_H
#pragma TenDRA extra , allow
#endif
#endif

#ifdef _GLIBC2_14
#ifdef __BUILDING_TDF_SVID3_FTW_H
#define _XOPEN_SOURCE 500 /* for FTW_PHYS */
#endif
#endif

#include_next <ftw.h>

#endif

