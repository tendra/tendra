/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef _STDARG_H_
#define _STDARG_H_


/*
    DEFINITION OF VA_LIST

    The definition of va_list is copied from the system header.
*/

#ifndef _VA_LIST_
#define _VA_LIST_
typedef char *va_list ;
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
#define va_start( l )		( ( void ) ( l = __va_start ( ... ) ) )
#endif
#endif


/*
    IMPLEMENTATION OF STDARG

    This implementation basically works, and avoids the built-in
    operators defined in the system header.
*/

#ifdef __BUILDING_TDF_C89_STDARG_H_VA_ARGS

#define va_end( VL )	((void)0)
#define va_start( VL, VP ) (VL = \
	(va_list) (sizeof(VP)?(sizeof(VP) > 4 ? ((int)&VP + 2*8 - 1) & -8 \
				    : ((int)&VP + 2*4 - 1) & -4):(int)&VP))
#define va_arg( VL, VM ) ((VM *)(VL = \
	(va_list) (sizeof(VM)?(sizeof(VM) > 4 ? ((int)VL + 2*8 - 1) & -8 \
				   : ((int)VL + 2*4 - 1) & -4):(int)VL)))[-1]

#endif


#endif /* _STDARG_H */
