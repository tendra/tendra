/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef _STDARG_INCLUDED
#define _STDARG_INCLUDED

#ifndef _SYS_STDSYMS_INCLUDED
#include <sys/stdsyms.h>
#endif

#ifndef _VA_LIST
#define _VA_LIST
typedef double *va_list ;
#endif


#ifndef __BUILDING_TDF_ANSI_STDARG_H_VA_ARGS


/*
    TOKEN DECLARATIONS

    The tokens __va_t, __va_start, va_arg and va_end are as in the
    ansi:stdarg header.  The only difference is that va_list is defined
    as its implementation type, rather than being a tokenised type.
*/

#pragma token TYPE __va_t # ~__va_t
#pragma token PROC ( EXP rvalue : __va_t : ) EXP rvalue : va_list : __va_start # ansi.stdarg.__va_start
#pragma token PROC ( EXP lvalue : va_list : e , TYPE t ) EXP rvalue : t : va_arg # ansi.stdarg.va_arg
#pragma token PROC ( EXP lvalue : va_list : ) EXP rvalue : void : va_end # ansi.stdarg.va_end
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

#define __COMPLEX_VA_LIST

typedef va_list __va_t ;
#define __va_start( X ) ( ( va_list ) ( ( char * ) ( X ) +4) )

#define __WORD_MASK 0xFFFFFFFC
#define __DW_MASK   0xFFFFFFF8

#define va_start(AP,ARG) ((AP)=(&(ARG)+4)
	 /* the `+4' is a hack to compensate for extra TDF `parameter' */

#define va_arg(AP,T)\
    (AP = sizeof(T)>8 ? ((double *) ((long)((char*)(AP)-sizeof(int)))) :\
    (sizeof(T) >4 ? ((double *) ((long)((char *)(AP)-sizeof(T)) & __DW_MASK))\
    : ((double *) ((long)((char *)(AP) -4)))), sizeof(T)>8 ?\
    ( *((T*) (*((int*) (AP))))) :\
    (*((T *) ((char *)(AP) + ((8-sizeof(T)) % 4)))))

#define va_end(AP)	((void) 0)

#endif /* __BUILDING_TDF_ANSI_STDARG_H_VA_ARGS */


#endif /* _STDARG_H */
