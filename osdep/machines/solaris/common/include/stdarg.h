/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef __HACKED_LIBC_STDARG_H
#define __HACKED_LIBC_STDARG_H


/*
    DEFINITION OF VA_LIST

    The definition of va_list is copied from the system header.
*/
#ifndef __BUILDING_TDF_C89_STDARG_H_VA_ARGS
#ifndef _VA_LIST
#define _VA_LIST
typedef void *va_list ;
#endif
#endif

#include <proxy/include/stdarg.h>


/*
    DEFINITION OF VA_START

    How va_start is defined in terms of __va_start depends on whether
    this is stdarg.h or varargs.h.
*/
#ifndef __BUILDING_TDF_C89_STDARG_H_VA_ARGS
#pragma TenDRA ident ... allow
#ifdef __HACKED_VARARGS
#define va_alist		...
#define va_dcl
#undef va_start
#define va_start(__ap)	((void) (__ap = __va_start(...)))
#endif
#endif


/*
    IMPLEMENTATION OF STDARG

    This implementation avoids the built-in
    operators defined in the system header.
*/

#ifdef __BUILDING_TDF_C89_STDARG_H_VA_ARGS
#if defined(_ARCH_sparc) || defined(_ARCH_x86_32)

typedef char *va_list;

#define __va_round(__T) \
	(((sizeof (__T) + 3) / 4) * 4)

#define va_start(__ap, __arg) \
	(__ap = &(__arg) + __va_round(__arg))

#define va_end(__ap) \
	((void) 0)

#define va_arg(__ap, __T) \
	( __ap += __va_round(__T), \
		* ((__T * ) ((__ap) - __va_round(__T))))

#endif
#endif


#endif

