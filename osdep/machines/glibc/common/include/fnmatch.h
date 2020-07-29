#ifndef __HACKED_LIBC_FNMATCH_H
#define __HACKED_LIBC_FNMATCH_H

/*
 * glibc says:
 *
 *   This value is returned if the implementation does not support `fnmatch'.
 *   Since this is not the case here it will never be returned but the
 *   conformance test suites still require the symbol to be defined.
 */
#if defined(_GLIBC2_12) || defined(_GLIBC2_14)
#ifdef __BUILDING_TDF_POSIX2_FNMATCH_H
#define FNM_NOSYS (-1)
#endif
#endif

#include_next <fnmatch.h>

#endif

