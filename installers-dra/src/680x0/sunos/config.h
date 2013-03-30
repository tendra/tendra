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

#define have_diagnostics	0	/* Have diagnostics */
#define use_long_double		0	/* Not yet anyway */
#define remove_unused_counters	0	/* for foralls optimisation */
#define remove_unused_index_counters\
				0	/* for foralls optimisation */
#define good_index_factor( f )	0	/* for foralls optimisation */
#define good_pointer_factor(f)\
				((f) != 1 && (f) != 2 && \
				 (f) != 4 && (f) != 8)


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
