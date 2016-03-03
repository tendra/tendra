/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef EVAL_H
#define EVAL_H

#include "addrtypes.h"

#include <flpt/flpt.h>

int next_dlab_sym(void);
mm maxmin(shape s);
instore evaluated(exp e, long l, dec * dc);
int outfloat(flpt f);
char *fltrepr;
int data_lab;

#endif

