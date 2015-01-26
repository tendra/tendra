/* $Id$ */

#ifndef __HACKED_STDDEF_H
#define __HACKED_STDDEF_H

/*
 * glibc does not provide this header; it is expected to be provided by gcc.
 * The definitions here must be compatible.
 */

#if defined(_EGLIBC2_11)

typedef unsigned int size_t;

typedef int ptrdiff_t;

typedef int wchar_t;

#include <proxy/include/offsetof.h>

#endif

#endif

