/* $Id$ */

#ifndef __HACKED_LIBC_STDLIB_H
#define __HACKED_LIBC_STDLIB_H

#ifdef _GLIBC2_14
#ifdef __BUILDING_TDF_XPG3_STDLIB_H_PUTENV
#pragma TenDRA incompatible type qualifier allow /* for putenv */
#endif
#endif

#ifdef _GLIBC2_14
#ifdef __BUILDING_TDF_SVID3_STDLIB_H
#pragma TenDRA incompatible type qualifier allow /* for putenv */
#endif
#endif

#include_next <stdlib.h>

#endif

