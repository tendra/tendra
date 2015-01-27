/* $Id$ */

#ifndef __HACKED_X86_STDARG_H
#define __HACKED_X86_STDARG_H

#if defined(_FREEBSD10_1)

#ifndef __BUILDING_TDF_C89_STDARG_H_VA_ARGS

#include <sys/cdefs.h>
#include <machine/_types.h>
#include <machine/stdarg.h>

typedef __va_list va_list;

#endif


/*
 * Implementation of stdarg.
 *
 * The system header does not provide an implementation; it just wraps compiler builtins.
 * There is a "fake" implementation "for lint's benefit", which matches ours here.
 */
#ifdef __BUILDING_TDF_C89_STDARG_H_VA_ARGS

#include <sys/cdefs.h>
#include <machine/_types.h>

#define __va_round(__T)       (((sizeof (__T) + 3) / 4) * 4)
#define va_start(__ap, __arg) ((__ap) = &(__arg) + __va_round((__arg)))
#define va_end(__ap)          ((void) 0)
#define va_arg(__ap, __T)     ((__ap += __va_round(__T), *((__T *) ((__ap) - __va_round(__T)))))

typedef __va_list va_list;

#endif

#endif

#endif

