/* $Id$ */

#ifndef __HACKED_LIBC_STDARG_H
#define __HACKED_LIBC_STDARG_H

#if defined(_FREEBSD10_1)

#ifndef __BUILDING_TDF_C89_STDARG_H_VA_ARGS

#include <sys/cdefs.h>
#include <machine/_types.h>
#include <machine/stdarg.h>
typedef __va_list va_list;
#endif

#ifndef __BUILDING_TDF_C89_STDARG_H_VA_ARGS
#include_next <stdarg.h>
#include <proxy/include/stdarg.h>
#endif

/*
 * Implementation of stdarg
 */
#ifdef __BUILDING_TDF_C89_STDARG_H_VA_ARGS
#include_next <stdarg.h>
#endif

#else

/* no hacks */
#include_next <stdarg.h>

#endif

#endif

