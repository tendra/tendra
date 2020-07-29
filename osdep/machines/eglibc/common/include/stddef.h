#ifndef __HACKED_STDDEF_H
#define __HACKED_STDDEF_H

/*
 * eglibc does not provide this header; it is expected to be provided by gcc.
 * The definitions here must be compatible.
 */

#if defined(_EGLIBC2_11) || defined(_EGLIBC2_15) || defined(_EGLIBC2_19)

#if defined(_ARCH_mips) || defined(_ARCH_x86_32) || defined(_ARCH_x32_64)
typedef unsigned int size_t;
typedef int ptrdiff_t;
typedef int wchar_t;
#endif

#include <proxy/include/offsetof.h>

#endif

#endif

