#ifndef __HACKED_LIBC_GLOB_H
#define __HACKED_LIBC_GLOB_H

#ifdef _GLIBC2_14
#ifdef __BUILDING_TDF_POSIX2_GLOB_H
#include <stddef.h>
typedef size_t __SIZE_TYPE__;
#endif
#endif

#include_next <glob.h>

#endif

