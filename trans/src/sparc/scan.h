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

#include <construct/installtypes.h>

#include "proctypes.h"

/* condition for shape to be treated as a struct */
#define sparccpd(s) (name(s) == cpdhd || name(s) == nofhd || \
                     name(s) == shcomplexhd || shape_size(s) >64 || \
                     name(s) == u64hd || name(s) == s64hd)

extern bool subvar_use(exp);
extern needs likediv(exp *, exp **);
extern needs likeplus(exp *, exp **);
extern needs scan(exp *, exp **);

extern int maxfix, maxfloat;

#endif /* NEEDSCAN_INCLUDED */
