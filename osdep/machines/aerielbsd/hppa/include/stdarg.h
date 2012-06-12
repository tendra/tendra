/* $Id$ */

#ifndef __HACKED_STDARG_H
#define __HACKED_STDARG_H

#ifdef _AERIELBSD1
#ifndef __BUILDING_TDF_ANSI_STDARG_H_VA_ARGS

typedef double * va_list;

#include_next <stdarg.h>

#else

/* for va_arg() */
#ifdef _AERIELBSD1
#pragma TenDRA begin
#pragma TenDRA conversion analysis ( int-pointer explicit ) off
#endif

#include_next <stdarg.h>

#ifdef _AERIELBSD1
#pragma TenDRA end
#endif

#endif
#endif

#endif

