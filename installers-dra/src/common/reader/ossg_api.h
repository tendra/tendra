/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef OSSG_API_INCLUDED
#define OSSG_API_INCLUDED


/*
    STANDARD API HEADER

    This header contains the basic API headers used by the program
    software.  Some likely values for objects which are not defined by
    all systems are provided.
*/

#define __math_h
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS		0
#define EXIT_FAILURE		1
#endif

#ifndef SEEK_SET
#define SEEK_SET		0
#define SEEK_CUR		1
#define SEEK_END		2
#endif

#ifdef __TenDRA__
#ifndef CROSS_INCLUDE
#define CROSS_INCLUDE		</usr/include
#endif
#endif


#endif
