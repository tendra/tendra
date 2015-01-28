/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef _STDARG_H_
#define _STDARG_H_

#ifndef __BUILDING_TDF_C89_STDARG_H_VA_ARGS
#include_next <stdarg.h>
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
