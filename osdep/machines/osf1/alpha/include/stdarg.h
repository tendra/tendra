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

#endif

#endif


#endif /* _STDARG_H */
