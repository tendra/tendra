#ifndef __HACKED_LIBC_SYS_STAT_H
#define __HACKED_LIBC_SYS_STAT_H

#ifdef _GLIBC2_14
#ifdef __BUILDING_TDF_UNIX95_SYS_STAT_H_ST_PROTO
#define _BSD_SOURCE 1 /* for S_IFSOCK */
#endif
#endif

#include_next <sys/stat.h>

#endif

