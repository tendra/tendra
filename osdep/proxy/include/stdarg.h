#ifndef __PROXY_STDARG_H
#define __PROXY_STDARG_H

#ifndef __BUILDING_TDF_C89_STDARG_H_VA_ARGS

/*
 * The tokens __va_t, __va_start, va_arg and va_end are as in the
 * c89:stdarg header. The only difference is that va_list is defined
 * as its implementation type, rather than being a tokenised type.
 *
 * va_list is expected to be defined by $os/$arch/include/stdarg.h
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

#endif

#endif

