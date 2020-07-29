/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * This file contains C #pragma statements which act as the interface
 * to the tokens defined in the file abstract.tpl.
 */

#if !defined(__INT64_API_h)
#define __INT64_API_h

/*
 * Define the generic 32-bit signed and unsigned types
 */
#ifdef NATIVE_INT64
typedef int INT32;
typedef unsigned int UINT32;
#else
typedef long INT32;
typedef unsigned long UINT32;
#endif

/*
 * Define the widest floating variety - not possible in C
 * The C Producer can't tokenise FLOATING_VARIETIES.
 */

/*
 * Define the new types for 64-bit integers
 */

#pragma token TYPE INT64 #
#pragma token TYPE UINT64 #
#pragma no_def INT64
#pragma no_def UINT64

/* Are 64-bit integers are conceptually hi-word first? */
#if BIGENDIAN_INT64

struct _s {
	INT32  hi32;
	UINT32 lo32;
};

struct _u {
	UINT32 hi32;
	UINT32 lo32;
} u;

#else

struct _s {
	UINT32 lo32;
	INT32  hi32;
};

struct _u {
	UINT32 lo32;
	UINT32 hi32;
} u;

#endif


typedef union {
	struct _s s;
	struct _u u;
	INT64     s64;
	UINT64    u64;
} TDF_INT64;

/*
 * Macros for extracting the high- and low-32 bits
 */

#define hi_32(X)  ((X).s.hi32)
#define lo_32(X)  ((X).s.lo32)

#define hi_u32(X) ((X).u.hi32)
#define lo_u32(X) ((X).u.lo32)

#define  PARAM(X) ((X).s64)
#define UPARAM(X) ((X).u64)

/*
 * 64-bit constants used in the implementation
 */
#pragma token EXP rvalue : TDF_INT64 : const_0  #
#pragma token EXP rvalue : TDF_INT64 : const_u0 #
#pragma token EXP rvalue : TDF_INT64 : const_1  #
#pragma token EXP rvalue : TDF_INT64 : const_u1 #

#endif

