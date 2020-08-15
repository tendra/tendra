#ifndef __HACKED_LIBC_MATH_H
#define __HACKED_LIBC_MATH_H

/*
 * glibc only defines MAXFLOAT under _XOPEN_SOURCE 500 or above,
 * but XPG3 is _XOPEN_SOURCE 1. So I'm just defining it here
 * rather than attempting to trick glibc into defining it.
 */
#ifdef _GLIBC2_14
#ifdef __BUILDING_TDF_XPG3_MATH_H
#define MAXFLOAT 3.40282347e+38F
#endif
#endif

#if defined(_GLIBC2_27) || defined(_GLIBC2_31)
#pragma TenDRA begin
#pragma TenDRA directive warning allow
#endif

#include_next <math.h>

#if defined(_GLIBC2_27) || defined(_GLIBC2_31)
#pragma TenDRA end
#endif

#endif

