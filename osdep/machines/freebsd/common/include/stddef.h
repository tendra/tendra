/* $Id$ */

#ifndef __HACKED_LIBC_STDDEF_H
#define __HACKED_LIBC_STDDEF_H

/*
 * FreeBSD 10.1 moved to using three underscores; rather than make a mess below,
 * we can provide this for compatibility.
 */
#if defined(_FREEBSD10_1)
#define __wchar_t ___wchar_t
#endif

/*
 * We're providing this primarily for offsetof(), because the system header
 * has the typical implementation which gives a non-constant expression.
 * Unfortunately it's not in an #ifndef guard, and so we can't override
 * just that macro.
 */
#if defined(_FREEBSD8_3) || defined(_FREEBSD9_0) || defined(_FREEBSD9_1) || defined(_FREEBSD9_2) || defined(_FREEBSD10_1)

#include_next <sys/cdefs.h>
#include_next <sys/_null.h>
#include_next <sys/_types.h>

typedef __ptrdiff_t ptrdiff_t;

#ifndef _SIZE_T_DECLARED
typedef __size_t size_t;
#define _SIZE_T_DECLARED
#endif

#ifndef _WCHAR_T_DECLARED
typedef __wchar_t wchar_t;
#define _WCHAR_T_DECLARED
#endif

#pragma TenDRA begin
#pragma TenDRA keyword __literal for keyword literal
#pragma TenDRA conversion analysis (pointer-int) off
#define offsetof(__s, __m) (__literal (size_t) &(((__s *) 0)->__m))
#pragma TenDRA end

#endif

#if defined(_FREEBSD10_1)
#undef __wchar_t
#endif

#endif

