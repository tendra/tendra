#ifndef __HACKED_LIBC_REGEX_H
#define __HACKED_LIBC_REGEX_H

/*
 * glibc says:
 *
 *   This will never happen for this implementation.
 */
#if defined(_GLIBC2_12) || defined(_GLIBC2_14)
#ifdef __BUILDING_TDF_POSIX2_REGEX_H
enum {
	REG_ENOSYS = -1
};
#endif
#endif

#include_next <regex.h>

#endif

