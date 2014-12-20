/* $Id$ */

#ifndef __HACKED_LIBC_STDDEF_H
#define __HACKED_LIBC_STDDEF_H

/*
 * We're providing this primarily for offsetof(), because the system header
 * has the typical implementation which gives a non-constant expression.
 * Unfortunately it's not in an #ifndef guard, and so we can't override
 * just that macro.
 */
#if defined(_OPENBSD5_1) || defined(_OPENBSD5_2) || defined(_OPENBSD5_3) || defined(_OPENBSD5_4)

#define NULL 0

/* for other headers which will define size_t unless we set this */
#ifndef __BUILDING_TDF_C89_STDDEF_H
#define _SIZE_T_DEFINED_
#endif

typedef unsigned long size_t;

typedef long ptrdiff_t;

typedef int wchar_t;

#pragma TenDRA begin
#pragma TenDRA keyword __literal for keyword literal
#pragma TenDRA conversion analysis (pointer-int) off
#define offsetof(__s, __m) (__literal (size_t) &(((__s *) 0)->__m))
#pragma TenDRA end

#endif

#endif

