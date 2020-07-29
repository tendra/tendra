#ifndef __HACKED_BITS_PTHREADTYPES_H
#define __HACKED_BITS_PTHREADTYPES_H

#if defined(_GLIBC2_5) || defined(_GLIBC2_7) || defined(_GLIBC2_11) \
	|| defined(_GLIBC2_14) || defined(_GLIBC2_15) || defined(_GLIBC2_18)
#pragma TenDRA begin
#pragma TenDRA anonymous union allow
#endif

#include_next <bits/pthreadtypes.h>

#if defined(_GLIBC2_5) || defined(_GLIBC2_7) || defined(_GLIBC2_11) \
	|| defined(_GLIBC2_14) || defined(_GLIBC2_15) || defined(_GLIBC2_18)
#pragma TenDRA end
#endif

#endif

