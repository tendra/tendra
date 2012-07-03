/* $Id$ */

#ifndef __HACKED_LIBC_BITS_SIGNUM_H
#define __HACKED_LIBC_BITS_SIGNUM_H

#if defined(_GLIBC2_3) || defined(_GLIBC2_11)
#pragma TenDRA begin
#pragma TenDRA conversion analysis (pointer-int) off
#endif

#include_next <bits/signum.h>

#if defined(_GLIBC2_3) || defined(_GLIBC2_11)
#pragma TenDRA end
#endif

#endif

