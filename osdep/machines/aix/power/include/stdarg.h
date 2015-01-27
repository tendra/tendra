/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef _H_STDARG
#define _H_STDARG


#ifndef _H_STANDARDS
#include <standards.h>
#endif

#include <va_list.h>


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
#ifdef __HACKED_VARARGS
#pragma TenDRA ident ... allow
#define va_alist		...
#define va_dcl
#undef va_start
#define va_start( l )		( ( void ) ( l = __va_start ( ... ) ) )
#endif
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
