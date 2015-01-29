/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef _STDARG_H
#define _STDARG_H

#ifndef __BUILDING_TDF_C89_STDARG_H_VA_ARGS
#include_next <stdarg.h>
#endif

#ifdef __BUILDING_TDF_C89_STDARG_H_VA_ARGS

/*
    IMPLEMENTATION OF STDARG

    This implementation basically works, and avoids the built-in
    operators defined in the system header.
*/

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


#endif /* _STDARG_H */
