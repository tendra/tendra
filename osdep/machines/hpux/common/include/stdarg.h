/* $Id$ */

/*
 * Copyright 2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef __HACKED_LIBC_STDARG_H
#define __HACKED_LIBC_STDARG_H

#ifndef _SYS_STDSYMS_INCLUDED
#include <sys/stdsyms.h>
#endif

#ifndef _VA_LIST
#define _VA_LIST
typedef double *va_list ;
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
#if defined(_ARCH_hppa)

#define __COMPLEX_VA_LIST

typedef va_list __va_t;

#define __va_start(__ap) ((va_list) ((char *) (__ap) + 4))

#define __WORD_MASK 0xFFFFFFFC
#define __DW_MASK   0xFFFFFFF8

 /* the `+4' is a hack to compensate for extra TDF `parameter' */
#define va_start(__ap, __arg) ((__ap) = (&(__arg) + 4)

#define va_arg(__ap,__T) \
    (__ap = sizeof (__T) > 8 \
		? ((double *) ((long) ((char *) (__ap) - sizeof (int)))) \
		: (sizeof (__T) > 4 \
			? ((double *) ((long) ((char *) (__ap) - sizeof(__T)) & __DW_MASK)) \
			: ((double *) ((long) ((char *) (__ap) - 4)))), sizeof(__T) > 8 \
				? (* ((__T *) (* ((int *) (__ap))))) \
				: (* ((__T *) ((char *) (__ap) + ((8 - sizeof(__T)) % 4)))))

#define va_end(__ap)	((void) 0)

#endif
#endif


#endif

