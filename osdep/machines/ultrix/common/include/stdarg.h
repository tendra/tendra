/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef _STDARG_H
#define _STDARG_H


#include <ansi_compat.h>

/*
    DEFINITION OF VA_LIST

    The definition of va_list is copied from the system header.
*/

#ifndef _VA_LIST_
#define _VA_LIST_
typedef char *va_list ;
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
#define va_start(__ap) ((void) (__ap = __va_start(...)))
#endif
#endif


/*
    IMPLEMENTATION OF STDARG

    This implementation avoids the built-in
    operators defined in the system header.
*/

#ifdef __BUILDING_TDF_C89_STDARG_H_VA_ARGS
#if defined(_ARCH_mips)

#define va_end(__ap) \
	((void) 0)

#define va_start(__ap, __arg ) \
	(__ap = (va_list) (sizeof (__arg) \
		? (sizeof (__arg) > 4 \
			? ((int) &__arg + 2 * 8 - 1) & -8 \
			: ((int) &__arg + 2 * 4 - 1) & -4) \
		: (int) &__arg))

#define va_arg( __ap, __T ) \
	((__T *) (__ap = (va_list) (sizeof (__T) \
		? (sizeof (__T) > 4 \
			? ((int) __ap + 2 * 8 - 1) & -8 \
			: ((int) __ap + 2 * 4 - 1) & -4) \
		: (int) __ap)))[-1]

#endif
#endif


#endif /* _STDARG_H */
