#ifndef __HACKED_LIBC_STDARG_H
#define __HACKED_LIBC_STDARG_H

#if defined(_OPENBSD5_1) || defined(_OPENBSD5_2) || defined(_OPENBSD5_3) \
	|| defined(_OPENBSD5_4) || defined(_OPENBSD5_5) || defined(_OPENBSD5_6)

#ifndef __BUILDING_TDF_C89_STDARG_H_VA_ARGS
#if defined(_ARCH_x86_32) || defined(_ARCH_sparc)
typedef char * va_list;
#endif
#endif

#include <proxy/include/stdarg.h>

/*
 * Implementation of stdarg
 */
#ifdef __BUILDING_TDF_C89_STDARG_H_VA_ARGS

#if defined(_ARCH_x86_32)
#include_next <machine/stdarg.h>
#endif

#if defined(_ARCH_sparc)

/*
 * OpenBSD's machine/stdarg.h says:
 *
 *   Gcc-2.x tries to use ldd/std for double and quad_t values, but Sun's
 *   brain-damaged calling convention does not quad-align these.  Thus, for
 *   8-byte arguments, we have to pick up the actual value four bytes at a
 *   time, and use type punning (i.e., a union) to produce the result.
 *
 * Its implementation of va_arg uses __builtin_classify_type to determine when
 * to do this. We're attempting to simulate the same effect on the assumption
 * that any 8-byte argument is treated as above. This is probably wrong.
 *
 * The following is adapted from lcc's implementation.
 * It is probably not what we want.
 */

typedef char * va_list;

#define va_start(__ap, __arg) \
	((void) ((__ap) = (sizeof (__arg) < 4 \
		? (char *) ((int *) &(__arg) + 1) \
		: (char *) (&(__arg) + 1))))

#define __va_arg(__ap, __T, n) \
	(* (__T *) (&(__ap += ((sizeof (__T) + n) & ~n))[- (int) ((sizeof (__T) + n) & ~n)]))

#define __bigendian_va_arg(__ap, __T, n) (\
	sizeof (__T) == 1 ? * (__T *) (&(__ap += 4)[-1]) : \
	sizeof (__T) == 2 ? * (__T *) (&(__ap += 4)[-2]) : __va_arg(__ap, __T, n))

#define __littleendian_va_arg(__ap, __T, n) __va_arg(__ap, __T, n)

#define va_end(__ap) ((void) 0)

#define va_arg(__ap, __T) \
	(sizeof (__T) > 8 \
		? ** (__T **) (&(__ap += 4)[-4]) \
		: __bigendian_va_arg(__ap, __T, 3U))

#endif

#endif


#endif

#endif

