/* $Id$ */

#ifndef __HACKED_LIBC_STDARG_H
#define __HACKED_LIBC_STDARG_H

/*
 * eglibc does not provide this header; it is expected to be provided by gcc.
 * The definitions here must be compatible.
 */
#if defined(_EGLIBC2_11) || defined(_EGLIBC2_15) || defined(_EGLIBC2_19)

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

