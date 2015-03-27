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
 * All characters and strings within the program are represented in terms of
 * the type character. In particular, the type string is defined to be
 * chararacter *.
 *
 * This represents a value in the C and C++ execution character set.
 *
 * An execution character set value is not the same as a character value in
 * TDFSTRING. The TDF spec does not define a particular character encoding,
 * and leaves that to producers and installers to agree upon amongst
 * themselves. tdfc2 uses ASCII values for TDFSTRING, which is output by calling
 * to_ascii() for each value in the execution character set.
 *
 * However, the character type is used for quite a few things where it is not
 * neccessarily appropriate, including the portability table (which shares its
 * lexer with the C and C++ lexer).
 *
 * Must it be an unsigned type for all the situations where it is used?
 * Probably not. However I think it does make sense to use an unsigned
 * types for the execution character set and for TDFSTRING character values.
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


#endif
