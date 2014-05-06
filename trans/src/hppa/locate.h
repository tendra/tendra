/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LOCATEDECS_INCLUDED
#define LOCATEDECS_INCLUDED

#include <local/exptypes.h>
#include "proctypes.h"

extern parpair *getparpair(exp);
extern baseoff boff(exp);
extern where locate(exp, space, shape, int);
extern where locate1(exp, space, shape, int);

#endif /* LOCATEDECS_INCLUDED */
