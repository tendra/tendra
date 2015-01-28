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
#define va_start(__list,__parmN) __list = (char *)((unsigned int)&(__parmN) + (((sizeof(__parmN)+3)/4)*4))
#define va_end(__list) (__list)=(char *)0
#define va_arg(__list, __mode) ((__mode *)( (((__list)+=(((sizeof(__mode)+3)/4)*4))-sizeof(__mode)) ))[0]
#endif



#endif /* _STDARG_H */
