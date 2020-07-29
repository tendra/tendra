/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef __HACKED_LIBC_STDARG_H
#define __HACKED_LIBC_STDARG_H

#ifndef __BUILDING_TDF_C89_STDARG_H_VA_ARGS
#include <standards.h>
#include <va_list.h>
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
#if defined(_ARCH_alpha)

#pragma token PROC ( TYPE t ) EXP rvalue : int : __builtin_isfloat #
#pragma no_def __builtin_isfloat

#define _VA_LIST
#define __COMPLEX_VA_LIST
typedef struct {
    char *_a0;		/* pointer to first homed integer arg */
    int _offset;	/* byte offset of next param */
} va_list;

static va_list _v;
typedef char *__va_t;

#define __va_start(__ap) \
	(_v._a0 = ( __ap ), _v._offset = 0, _v)

#define va_end(__ap) \
	((void) 0)

#define va_arg(__ap, __T) \
	(* (((__ap)._offset += ((int) sizeof (__T) + 7) & - 8),
		(__T *) ((__ap)._a0 + (__ap)._offset - \
			((__builtin_isfloat(__T) && (__ap)._offset <= (6 * 8)) \
				? (6 * 8) + 8 \
				: ((int) sizeof(__T) + 7) & -8))))

#endif
#endif


#endif /* _STDARG_H */
