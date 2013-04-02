/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef WEIGHTS_H
#define WEIGHTS_H

#include "exptypes.h"

void init_weights(void);
void comp_weights(exp e);
int regable(exp e);
int no_side(exp e);

#endif /* WEIGHTS_H */
