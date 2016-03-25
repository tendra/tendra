/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * common.h - Primitive definitions common to several interfaces.
 *
 * This file specifies an interface to the host system's C library, compiler
 * and operating system.  It provides definitions of basic types, constants
 * and macros, and declarations of functions, that can be used by other
 * components of programs.
 *
 * This file used to provide portability abstractions; now all that remains
 * are definitions for semantic purposes, such as CmpT.
 *
 * This is seperate from exception.h as some APIs provided by the library
 * may not neccessary make use of the exception mechanism (for example, a
 * memory pool allocation system). However, that would be built upon to
 * provide an exception-throwing interface as an additional layer.
 *
 * Any compiler-specific or standard-specific features should be in this file.
 */

#ifndef H_COMMON
#define H_COMMON

#if __STDC_VERSION__ >= 199901L
# include <stdint.h>
#endif

/*
 * This is the return type of a function that doesn't return (e.g.
 * ``longjmp'').  Normally this is just ``void'', however the GNU C compiler
 * can produce better code if this is declared as ``__volatile__ void''.  The
 * TenDRA compiler can be told that a function doesn't return as well.
 */
#ifdef __GNUC__
typedef void NoReturnT;
#else
# ifdef __TenDRA__
#  pragma TenDRA type NoReturnT for bottom
# else
#  define NoReturnT void
# endif /* defined (__TenDRA__) */
#endif /* defined (__GNUC__) */

/*
 * An unsigned byte. This may be larger than an octet.
 */
#if __STDC_VERSION__ >= 199901L
typedef uint8_t ByteT;
#else
typedef unsigned char ByteT;
#endif

/*
 * This is the type returned by comparison functions.  The values represent
 * the fact that the first argument is less than, equal to, or greater than
 * the second argument respectively.
 */
typedef enum {
	CMP_LT,
	CMP_EQ,
	CMP_GT
} CmpT;

#endif /* !defined (H_COMMON) */
