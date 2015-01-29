/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef _H_STDARG
#define _H_STDARG

#ifndef __BUILDING_TDF_C89_STDARG_H_VA_ARGS
#include_next <stdarg.h>
#endif

/*
    IMPLEMENTATION OF STDARG

    This implementation basically works, and avoids the built-in
    operators defined in the system header.
*/

#ifdef __BUILDING_TDF_C89_STDARG_H_VA_ARGS

#define va_start(__ap, __arg) \
	__ap = (char *) ((unsigned int) & (__arg) + (((sizeof (__arg) + 3) / 4) * 4))

#define va_end(__ap) \
	(__ap) = (char *) 0

#define va_arg(__ap, __T) \
	((__T *) ((((__ap) += (((sizeof (__T) + 3) / 4) * 4)) - sizeof (__T))))[0]

#endif



#endif /* _STDARG_H */
