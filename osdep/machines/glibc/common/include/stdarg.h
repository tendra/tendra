/* $Id$ */

#ifndef __HACKED_LIBC_STDARG_H
#define __HACKED_LIBC_STDARG_H

#if defined(_GLIBC2_5) || defined(_GLIBC2_7) || defined(_GLIBC2_11) \
	|| defined(_GLIBC2_12) || defined(_GLIBC2_14) || defined(_GLIBC2_15) \
	|| defined(_GLIBC2_17) || defined(_GLIBC2_18) || defined(_GLIBC2_19)

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

#endif

#endif

