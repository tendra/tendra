/* $Id$ */

#ifndef __HACKED_LIBC_WORDEXP_H
#define __HACKED_LIBC_WORDEXP_H

#ifdef _GLIBC2_14
#ifdef __BUILDING_TDF_POSIX2_WORDEXP_H
enum {
	WRDE_NOSYS = -1
};
#endif
#endif

#include_next <wordexp.h>

#endif

