/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* guarddecs.h
    defines extenals given in guard.c
*/

#include "procrecs.h"
#include "addresstypes.h"

extern  space guardreg(int r, space sp);
extern  space guardfreg(int r, space sp);
extern  space guard(where w, space sp);
