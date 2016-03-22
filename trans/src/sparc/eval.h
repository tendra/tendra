/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef EVAL_H
#define EVAL_H

#include <construct/installtypes.h>

#include <flpt/flpt.h>

#include "addr.h"

bool is_zero(exp);
instore evaluated(exp, long, bool);
int next_data_lab(void);
long *realrep(exp);
mm maxmin(shape);
void outlab(int);

#endif

