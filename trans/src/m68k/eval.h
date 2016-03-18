/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef EVAL_H
#define EVAL_H

#include "mach.h"

bool convert_floats;

exp const_list;
long *realrep(exp);
void evaluate(exp, long, char *, int, int, diag_descriptor *);

#define make_constant(X, Y) \
    const_list = getexp(botsh, const_list, 0, (Y), NULL, 0, (X), 0)

#endif

