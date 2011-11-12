/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef LANGUAGE_INCLUDED
#define LANGUAGE_INCLUDED


/*
    SOURCE LANGUAGE FLAGS

    These flags control whether the producer is configured for C or C++.
    This configuration indicates C.
*/

#ifdef LANGUAGE_CPP
#undef LANGUAGE_CPP
#endif

#ifdef LANGUAGE_C
#undef LANGUAGE_C
#endif

#define LANGUAGE_CPP		0
#define LANGUAGE_C		1

#define LANGUAGE_NAME		"C"
#define LANGUAGE_VERSION	ISOC_VERSION


#endif
