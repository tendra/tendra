#ifndef __HACKED_LIBC_WORDEXP_H
#define __HACKED_LIBC_WORDEXP_H

/*
 * glibc says:
 *
 *   Never used since we support `wordexp'.
 */
#if defined(_GLIBC2_12) || defined(_GLIBC2_14)
#ifdef __BUILDING_TDF_POSIX2_WORDEXP_H
enum {
	WRDE_NOSYS = -1
};
#endif
#endif

#include_next <wordexp.h>

#endif

