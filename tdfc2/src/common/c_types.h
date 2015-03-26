/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef C_TYPES_INCLUDED
#define C_TYPES_INCLUDED


/*
 * BASIC TYPES
 *
 * All characters and strings within the program are represented in terms of
 * the type character. In particular, the type string is defined to be
 * chararacter *. ulong is defined as a macro to avoid duplicate definitions
 * in the system headers.
 */

typedef unsigned char character;


/*
 *  MAIN TYPE SYSTEM
 *
 *  The main type system is generated using the calculus tool. See c_class.alg
 *  for more details.
 */

#include "c_class.h"


/*
 * DEBUG MEMORY ALLOCATION ROUTINES
 *
 * In debug mode an alternative memory allocation scheme allowing for run-time
 * type information is implemented.
 */

#ifndef NDEBUG
#if c_class_IMPLEMENTATION
extern c_class *debug_c_class(unsigned, unsigned);
#undef GEN_c_class
#define GEN_c_class(A, B)	debug_c_class((unsigned)(A), (B))
#define TYPEID(A)		((A)[-1].ag_tag)
#define TYPEID_free		((unsigned)42)
#endif
#endif


/*
 * SYNONYMS FOR CALCULUS CONSTRUCTS
 *
 * These macros give synonyms for various constructs defined within the
 * calculus plus some other useful constructs.
 */

#define ulong			ulong_type
#define btype_struct		btype_struct_
#define btype_union		btype_union_
#define btype_enum		btype_enum_
#define cinfo_struct		cinfo_struct_
#define cinfo_union		cinfo_union_
#define destroy			destroy_c_class
#define null_tag		((unsigned)0xffff)
#define NULL_string		((string)NULL)

#if LANGUAGE_C
#define cv_lang			cv_c
#define dspec_lang		dspec_c
#define btype_lang		btype_struct
#define ERR_ALTERNATE		1
#else
#define cv_lang			cv_cpp
#define dspec_lang		dspec_cpp
#define btype_lang		btype_class
#endif


/*
 * DISTINGUISHED LINKAGE VALUES
 *
 * These values are used as distinguished linkage numbers for use in the
 * output routines. Unassigned linkage numbers are given the value LINK_NONE.
 * External linkage numbers are or-ed with the value LINK_EXTERN to
 * distinguish them from internal linkage numbers.
 */

#define LINK_NONE		((ulong)0xffffffffUL)
#define LINK_EXTERN		((ulong)0x80000000UL)
#define LINK_ZERO		((ulong)0xfffffffeUL)
#define LINK_TOKDEF		((ulong)0xfffffffdUL)


#endif
