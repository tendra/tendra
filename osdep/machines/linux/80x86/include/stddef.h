/* $Id$ */

#ifndef __HACKED_STDDEF_H
#define __HACKED_STDDEF_H

/*
 * glibc does not provide this header; it is expected to be provided by gcc.
 * The definitions here must be compatible.
 */
#ifdef _GLIBC2_14

#define NULL 0

typedef unsigned int size_t;

typedef int ptrdiff_t;

typedef long int wchar_t;

#pragma TenDRA keyword __literal for keyword literal
#define offsetof(s, m) (__literal (size_t) &(((s *) 0)->m))

#endif

#endif

