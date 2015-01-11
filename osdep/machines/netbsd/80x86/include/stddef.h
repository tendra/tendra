/* $Id$ */

#ifndef __HACKED_STDDEF_H
#define __HACKED_STDDEF_H

/*
 * We're providing this primarily for offsetof(), because the system header
 * has the typical implementation which gives a non-constant expression.
 * Unfortunately it's not in an #ifndef guard, and so we can't override
 * just that macro.
 */
#ifdef _NETBSD5_1

#include <sys/cdefs.h>
#include <sys/featuretest.h>
#include <machine/c89.h>

typedef _BSD_PTRDIFF_T_ ptrdiff_t;

#ifdef  _BSD_SIZE_T_
typedef _BSD_SIZE_T_    size_t;
#undef  _BSD_SIZE_T_
#endif

#ifdef  _BSD_WCHAR_T_
typedef _BSD_WCHAR_T_   wchar_t;
#undef  _BSD_WCHAR_T_
#endif

#pragma TenDRA begin
#pragma TenDRA keyword __literal for keyword literal
#pragma TenDRA conversion analysis (pointer-int) off
#define offsetof(__s, __m) (__literal (size_t) &(((__s *) 0)->__m))
#pragma TenDRA end

#endif

#endif

