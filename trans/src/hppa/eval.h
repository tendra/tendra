/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef EVAL_H
#define EVAL_H

#include "addr.h"

#include <flpt/flpt.h>

int next_data_lab(void);
int next_PIC_pcrel_lab(void);
mm maxmin(shape);
instore evaluated(exp, long);
void set_align(int);
void evalone(exp, int);

#endif

