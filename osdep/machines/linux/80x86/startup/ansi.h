/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* TODO: move to -Ymakelib */
#pragma TenDRA begin
#pragma TenDRA no external declaration allow
#pragma TenDRA directive include_next allow

/* TODO: split these by os/cpu, and move up to common/ directories */
#ifndef __NO_BUILTIN_ASSERTIONS
#pragma TenDRA directive assert allow
#pragma TenDRA directive unassert allow
#assert machine(i386)
#assert cpu(i386)
#assert system(unix)
#assert system(posix)
#unassert lint
#endif

#ifdef _GLIBC2_12
#define __STRICT_ANSI__
#endif

#ifdef _GLIBC2_12
#define __WRONG_ANSI_STDIO_H	/* i don't know what to do about va_list */
#define __WRONG_ANSI_STDARG_H_VA_ARGS	/* i don't know what to do about va_list */
#endif

