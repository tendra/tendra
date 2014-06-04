/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef NEEDSCAN_INCLUDED
#define NEEDSCAN_INCLUDED

#include <reader/exp.h>

#include "proctypes.h"

extern needs scan(exp *, exp **);
extern needs likeplus(exp *, exp **);
extern needs likediv(exp *, exp **);

extern int maxfix, maxfloat;

int hppabuiltin;

#endif /* NEEDSCAN_INCLUDED */
