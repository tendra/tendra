/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#pragma TenDRA begin
#pragma TenDRA directive assert allow
#pragma TenDRA directive unassert allow
#pragma TenDRA directive include_next allow
#pragma TenDRA longlong type allow
#pragma TenDRA anonymous union allow
#pragma TenDRA extra type definition allow
#pragma TenDRA no external declaration allow
#pragma TenDRA incompatible type qualifier allow
#pragma TenDRA unknown directive allow

/* Put target-dependent macro definitions here */

#ifndef __NO_BUILTIN_ASSERTIONS
#assert machine(i386)
#assert cpu(i386)
#assert system(unix)
#assert system(posix)
#unassert lint
#endif

#define unix		1
#define i386		1
#define linux		1
#define __unix		1
#define __i386		1
#define __linux		1
#define __unix__	1
#define __i386__	1
#define __linux__	1
#define __i486__	1

#ifdef _GLIBC2_12
#define __STRICT_ANSI__
#endif

#ifdef _GLIBC2_12
#define __WRONG_ANSI_STDIO_H	/* i don't know what to do about va_list */
#define __WRONG_ANSI_STDARG_H_VA_ARGS	/* i don't know what to do about va_list */
#endif

