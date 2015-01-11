/* $Id$ */

#ifndef __HACKED_MACHINE__TYPES_H
#define __HACKED_MACHINE__TYPES_H

#if defined(_FREEBSD9_0) || defined(_FREEBSD9_1) || defined(_FREEBSD9_2) || defined(_FREEBSD10_1)
#define __extension__
#endif

#include_next <machine/_types.h>

#if defined(_FREEBSD9_0) || defined(_FREEBSD9_1) || defined(_FREEBSD9_2) || defined(_FREEBSD10_1)
#undef __extension__
#endif

#if defined(_FREEBSD10_1)

/* to correspond to the built-in __va_list for the system compiler (clang) */
typedef char * __va_list;

#endif

#endif

