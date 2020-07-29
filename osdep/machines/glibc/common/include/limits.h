#ifndef __HACKED_LIBC_LIMITS_H
#define __HACKED_LIBC_LIMITS_H

#ifdef _GLIBC2_12
#ifdef __BUILDING_TDF_POSIX_LIMITS_H
#include <linux/limits.h>	/* for NGROUPS_MAX */
#endif
#endif

#include_next <limits.h>

#endif

