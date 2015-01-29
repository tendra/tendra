/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef _STDARG_H
#define _STDARG_H

#if defined(_SUNOS510) || defined(_SUNOS511)

#ifndef __BUILDING_TDF_C89_STDARG_H_VA_ARGS
#include_next <stdarg.h>
#endif


#ifdef __BUILDING_TDF_C89_STDARG_H_VA_ARGS

/*
    IMPLEMENTATION OF STDARG

    This implementation basically works, and avoids the built-in
    operators defined in the system header.
*/

typedef char *va_list;

#define __va_round(__T) \
	(((sizeof (__T) + 3) / 4) * 4)

#define va_start(__ap, __arg) \
	(__ap = &(__arg) + __va_round(__arg))

#define va_end(__ap) \
	((void) 0)

#define va_arg(__ap, __T) \
	(__ap += __va_round(__T), \
		* ((__T *) ((__ap) - __va_round(__T))))

#endif

#endif


#endif /* _STDARG_H */
