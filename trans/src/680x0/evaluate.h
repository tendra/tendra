/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef EVALUATE_INCLUDED
#define EVALUATE_INCLUDED

#include "mach.h"

extern int convert_floats;

extern exp const_list;
extern long * realrep(exp);
extern void evaluate(exp, long, char *, int, int, diag_global *);
extern void eval_op(long sz, mach_op* op);

#define  make_constant(X, Y)\
    const_list = getexp(botsh, const_list, 0,(Y), nilexp, 0,(X), 0)

#endif
