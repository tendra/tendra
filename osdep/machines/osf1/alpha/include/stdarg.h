/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/

#ifndef _STDARG_H
#define _STDARG_H

#ifndef __BUILDING_TDF_ANSI_STDARG_H_VA_ARGS

#include <standards.h>
#include <va_list.h>


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

#pragma token PROC ( TYPE t ) EXP rvalue : int : __builtin_isfloat #
#pragma no_def __builtin_isfloat

#define _VA_LIST
#define __COMPLEX_VA_LIST
typedef struct {
    char *_a0;		/* pointer to first homed integer arg */
    int _offset;	/* byte offset of next param */
} va_list;

static va_list _v ;
typedef char *__va_t ;

#define __va_start(X)   (_v._a0 = ( X ), _v._offset = 0, _v)
#define va_end(X)	( ( void ) 0 )

#define va_arg(list, mode) \
	(*(((list)._offset += ((int)sizeof(mode) + 7) & -8), \
	    (mode *)((list)._a0 + (list)._offset - \
		((__builtin_isfloat(mode) && (list)._offset <= (6 * 8)) ? \
		(6 * 8) + 8 : ((int)sizeof(mode) + 7) & -8))))

#endif /* __BUILDING_TDF_ANSI_STDARG_H_VA_ARGS */


#endif /* _STDARG_H */
