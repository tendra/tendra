#ifndef __HACKED_STDDEF_H
#define __HACKED_STDDEF_H

/*
 * glibc does not provide this header; it is expected to be provided by gcc.
 * The definitions here must be compatible.
 */

#if defined(_GLIBC2_5) || defined(_GLIBC2_7) || defined(_GLIBC2_11) \
	|| defined(_GLIBC2_12) || defined(_GLIBC2_14) || defined(_GLIBC2_15) \
	|| defined(_GLIBC2_17) || defined(_GLIBC2_18) || defined(_GLIBC2_19) \
	|| defined(_GLIBC2_27) || defined(_GLIBC2_31)

#if defined(_ARCH_x86_32) || defined(_ARCH_x32_64)
typedef unsigned int size_t;
typedef int ptrdiff_t;
typedef long int wchar_t;
#endif

#include <proxy/include/offsetof.h>

#endif

#endif

