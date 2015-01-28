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
#define va_start( l )		( ( void ) ( l = __va_start ( ... ) ) )
#endif
#endif


#endif

