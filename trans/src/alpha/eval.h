/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef EVAL_H
#define EVAL_H

#include <local/ash.h>

#include <flpt/flpt.h>

#include "addrtypes.h"

int next_dlab_sym(void);
int data_lab;

mm maxmin(shape);

instore evaluated(exp, int);

#endif

