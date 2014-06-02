/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef REGALLOC_INCLUDED
#define REGALLOC_INCLUDED

#include <reader/exptypes.h>

#include <construct/installtypes.h>

#include "proctypes.h"

extern bool avoid_L7;
extern spacereq maxspace(spacereq, spacereq);
extern spacereq regalloc(exp, int, int, long);

#endif /* REGALLOC_INCLUDED */
