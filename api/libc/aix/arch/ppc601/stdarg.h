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


#ifndef __BUILDING_TDF_ANSI_STDARG_H_VA_ARGS


/*
    DEFINITION OF VA_LIST

    The definition of va_list is copied from the system header.
*/

#ifndef _VA_LIST
#define _VA_LIST
typedef void *va_list ;
#endif


/*
    TOKEN DECLARATIONS

    The tokens __va_t, __va_start, va_arg and va_end are as in the
    c89:stdarg header.  The only difference is that va_list is defined
    as its implementation type, rather than being a tokenised type.
*/

#pragma token TYPE __va_t # ~__va_t
#pragma token PROC ( EXP rvalue : __va_t : ) EXP rvalue : va_list : __va_start # c89.stdarg.__va_start
#pragma token PROC ( EXP lvalue : va_list : e , TYPE t ) EXP rvalue : t : va_arg # c89.stdarg.va_arg
#pragma token PROC ( EXP lvalue : va_list : ) EXP rvalue : void : va_end # c89.stdarg.va_end
#pragma interface __va_t __va_start va_arg va_end


/*
    DEFINITION OF VA_START

    How va_start is defined in terms of __va_start depends on whether
    this is stdarg.h or varargs.h.
*/

#pragma TenDRA ident ... allow

#ifdef __HACKED_VARARGS
#define va_alist		...
#define va_dcl
#define va_start( l )		( ( void ) ( l = __va_start ( ... ) ) )
#else
#define va_start( l, i )	( ( void ) ( l = __va_start ( ... ) ) )
#endif


#else /* __BUILDING_TDF_ANSI_STDARG_H_VA_ARGS */


/*
    IMPLEMENTATION OF STDARG

    This implementation basically works, and avoids the built-in
    operators defined in the system header.
*/

#define va_start(__list,__parmN) __list = (char *)((unsigned int)&(__parmN) + (((sizeof(__parmN)+3)/4)*4))
#define va_end(__list) (__list)=(char *)0
#define va_arg(__list, __mode) ((__mode *)( (((__list)+=(((sizeof(__mode)+3)/4)*4))-sizeof(__mode)) ))[0]

#endif /* __BUILDING_TDF_ANSI_STDARG_H_VA_ARGS */


#endif /* _STDARG_H */
