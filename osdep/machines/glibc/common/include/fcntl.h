/* $Id$ */

#ifndef __HACKED_LIBC_FCNTL_H
#define __HACKED_LIBC_FCNTL_H

#ifdef _GLIBC2_14
#ifdef __BUILDING_TDF_UNIX95_FCNTL_H
#define _BSD_SOURCE /* for F_GETOWN */
#define FNM_NOSYS (-1)
#endif
#endif

#include_next <fcntl.h>

#endif

