/* $Id$ */

#ifndef __HACKED_LIBC_REGEX_H
#define __HACKED_LIBC_REGEX_H

#ifdef _GLIBC2_14
#ifdef __BUILDING_TDF_POSIX2_REGEX_H
enum {
	REG_ENOSYS = -1
};
#endif
#endif

#include_next <regex.h>

#endif

