/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LOCATEDECS_INCLUDED
#define LOCATEDECS_INCLUDED

#include <reader/exptypes.h>

#include "proctypes.h"

extern baseoff boff(exp);
extern int boff_env_offset(exp);
extern where locate(exp, space, shape, int);
extern where locate1(exp, space, shape, int);

#endif /* LOCATEDECS_INCLUDED */
