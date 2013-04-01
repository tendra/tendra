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


#ifdef EBUG
#define debug_warning(X)	error(ERROR_WARNING, X)
#else
#define debug_warning(X)
#endif


#define SUN



#endif
