/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef PRINT_INCLUDED
#define PRINT_INCLUDED

#ifndef CONFIG_INCLUDED
#include "config.h"
#endif
#ifndef OBJECT_INCLUDED
#include "object.h"
#endif
#ifndef TYPE_INCLUDED
#include "type.h"
#endif

/*
    PROCEDURE DECLARATIONS

    These routines are concerned with printing objects to the output file.
*/

extern void print_set(object *, int);
extern void print_type(FILE *, type *, char *, int);
extern char *copyright;


#endif
