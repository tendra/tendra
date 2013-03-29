/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    CONFIGURATION FILE

    This file contains the basic information required by all files and
    the macros controlling the selection of target-dependent optimizations.
*/

#ifndef CONFIG_INCLUDED
#define CONFIG_INCLUDED


/*
    DEFINE BASIC TYPES
*/

typedef unsigned long bitpattern;


/*
    SHOULD WE USE ALLOCA?
*/

#define NO_ALLOCA


#ifdef EBUG
#define debug_warning(X)	error(ERROR_WARNING, X)
#else
#define debug_warning(X)
#endif


#define SUN


/*
    DEFINE COMPILATION OPTIONS
*/

#define convert_floats		1	/* Convert floating constants */
#define dont_unpad_apply	1	/* Careful with procedure results */
#define dynamic_diag_test	1	/* Test diagnostics format */
#define has64bits		0	/* Doesn't have 64 bits */
#define have_diagnostics	0	/* Have diagnostics */
#define load_ptr_pars		1	/* Inline ptr parameters */
#define no_bitfield_ops		1	/* Do have bitfield operations */
#ifdef SUN
#define promote_pars		1	/* Parameters are 32 bit */
#endif
#define no_trap_on_nil_contents	1	/* Let common code detect nil access */
#define replace_compound	1	/* Replace compounds by externals */
#define temp_mips		0	/* Don't need a mips hack */
#define use_long_double		0	/* Not yet anyway */
#define remove_unused_counters	0	/* for foralls optimisation */
#define remove_unused_index_counters\
				0	/* for foralls optimisation */
#define good_index_factor( f )	0	/* for foralls optimisation */
#define good_pointer_factor(f)\
				((f) != 1 && (f) != 2 && \
				 (f) != 4 && (f) != 8)


/*
    HACKS FOR CROSS-COMPILATION

    Some routines are target-dependent and may not work properly when
    cross-compiling.  This section should take care of this.
*/

#ifdef CROSS_COMPILE
#undef convert_floats
#define convert_floats		0	/* Just to be on the safe side */
#endif

#ifdef SUN /* The SunOS 68k assembler whinges about align directives */
#define no_align_directives
#endif


/*
    EXTRA TAGS

    These are target-specific tags.  Strictly speaking they belong in
    tags.h.
*/

#define dummy_tag		100
#define internal_tag		101
#define regpair_tag		102


#endif
