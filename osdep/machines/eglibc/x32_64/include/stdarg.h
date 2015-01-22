/* $Id$ */

#ifndef __HACKED_STDARG_H
#define __HACKED_STDARG_H

/*
 * eglibc does not provide this header; it is expected to be provided by gcc.
 * The definitions here must be compatible.
 */
#if defined(_EGLIBC2_15) || defined(_EGLIBC2_19)
#ifndef __BUILDING_TDF_C89_STDARG_H_VA_ARGS

/*
 * The definition of va_list is compatible with the system header.
 * We define __gnuc_va_list because various headers rely on it.
 */

#ifndef __GNUC_VA_LIST
#define __GNUC_VA_LIST
#define __gnuc_va_list void *
typedef __gnuc_va_list va_list;
#endif

/*
 * The tokens __va_t, __va_start, va_arg and va_end are as in the
 * c89:stdarg header. The only difference is that va_list is defined
 * as its implementation type, rather than being a tokenised type.
 */

#pragma token TYPE __va_t # ~__va_t
#pragma token PROC ( EXP rvalue : __va_t : ) EXP rvalue : va_list : __va_start # c89.stdarg.__va_start
#pragma token PROC ( EXP lvalue : va_list : e , TYPE t ) EXP rvalue : t : va_arg # c89.stdarg.va_arg
#pragma token PROC ( EXP lvalue : va_list : ) EXP rvalue : void : va_end # c89.stdarg.va_end
#pragma interface __va_t __va_start va_arg va_end

#pragma TenDRA ident ... allow

#define va_start(__ap, __arg) ((void) ((__ap) = __va_start(...)))

#else

/*
 * Implementation of stdarg
 */

/* note char * is compatible to void * above */
typedef char *va_list;

#define __va_round(__T)       (((sizeof (__T) + 3) / 4) * 4)
#define va_start(__ap, __arg) ((__ap) = &(__arg) + __va_round((__arg)))
#define va_end(__ap)          ((void) 0)
#define va_arg(__ap, __T)     ((__ap += __va_round(__T), *((__T *) ((__ap) - __va_round(__T)))))

#endif
#endif

#endif

