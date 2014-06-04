/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef WEIGHTS_INCLUDED
#define WEIGHTS_INCLUDED

#include <reader/exp.h>

#include <construct/installtypes.h>

#include "procrec.h"

extern weights add_weights(weights *, weights *);
extern weights add_wlist(double, exp);
extern weights mult_weights(double, weights *);
extern weights weightsv(double, exp);
extern wp max_weights(double, weights *, bool);

#endif /* WEIGHTS_INCLUDED */
