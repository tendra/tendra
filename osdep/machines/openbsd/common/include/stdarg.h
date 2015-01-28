/* $Id$ */

#ifndef __HACKED_LIBC_STDARG_H
#define __HACKED_LIBC_STDARG_H

#if defined(_OPENBSD5_1) || defined(_OPENBSD5_2) || defined(_OPENBSD5_3) \
	|| defined(_OPENBSD5_4) || defined(_OPENBSD5_5) || defined(_OPENBSD5_6)

#ifndef __BUILDING_TDF_C89_STDARG_H_VA_ARGS
#if defined(_ARCH_x86_32) || defined(_ARCH_sparc)
typedef char * va_list;
#endif
#endif

#include <proxy/include/stdarg.h>

/*
 * Implementation of stdarg
 */
#ifdef __BUILDING_TDF_C89_STDARG_H_VA_ARGS
#include_next <machine/stdarg.h>
#endif

#endif

#endif

