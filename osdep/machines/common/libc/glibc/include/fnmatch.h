/* $Id$ */

#ifndef __HACKED_LIBC_FNMATCH_H
#define __HACKED_LIBC_FNMATCH_H

#ifdef _GLIBC2_14
#ifdef __BUILDING_TDF_POSIX2_FNMATCH_H
#define FNM_NOSYS (-1)
#endif
#endif

#include_next <fnmatch.h>

#endif

