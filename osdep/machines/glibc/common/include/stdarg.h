#ifndef __HACKED_LIBC_STDARG_H
#define __HACKED_LIBC_STDARG_H

#if defined(_GLIBC2_5) || defined(_GLIBC2_7) || defined(_GLIBC2_11) \
	|| defined(_GLIBC2_12) || defined(_GLIBC2_14) || defined(_GLIBC2_15) \
	|| defined(_GLIBC2_17) || defined(_GLIBC2_18) || defined(_GLIBC2_19) \
	|| defined(_GLIBC2_27) || defined(_GLIBC2_31)

/*
 * The definition of va_list is compatible with the system header.
 * We define __gnuc_va_list because various headers rely on it.
 */
#ifndef __BUILDING_TDF_C89_STDARG_H_VA_ARGS
#ifndef __GNUC_VA_LIST
#define __GNUC_VA_LIST
#define __gnuc_va_list void *
typedef __gnuc_va_list va_list;
#endif
#endif

#include <proxy/include/stdarg.h>


/*
 * Implementation of stdarg
 */
#ifdef __BUILDING_TDF_C89_STDARG_H_VA_ARGS
#if defined(_ARCH_x86_32) || defined(_ARCH_x32_64)

/* note char * is compatible to void * above */
typedef char *va_list;

#define __va_round(__T) \
	(((sizeof (__T) + 3) / 4) * 4)

#define va_start(__ap, __arg) \
	((__ap) = &(__arg) + __va_round((__arg)))

#define va_end(__ap) \
	((void) 0)

#define va_arg(__ap, __T) \
	((__ap += __va_round(__T), * ((__T *) ((__ap) - __va_round(__T)))))

#endif
#endif


#endif

#endif

