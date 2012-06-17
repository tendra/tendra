/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef NEEDSCANDECS_H
#define NEEDSCANDECS_H

#include "config.h"

#include <construct/installtypes.h>
#include "exptypes.h"


extern int maxfix, maxfloat;
extern long callee_size;
extern long max_callees;
extern bool gen_call;
extern long no_of_returns;

extern needs likeplus(exp *, exp **);
extern needs likeminus(exp *, exp **);
extern needs scan(exp *, exp **);

#endif /* needscandecs.h */
