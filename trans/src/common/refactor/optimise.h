/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef OPTIMISE_H
#define OPTIMISE_H

#include <reader/exp.h>

#include <construct/installtypes.h>

extern void opt_all_exps(void);
extern  void forall_opt(void);
extern exp case_optimisation(exp body, exp id, shape shape_of_case,
	exp control_expression);
extern void unroller(void);

extern void inline_exp(exp e);
extern void normalised_inlining(void);
extern int inlinechoice(exp, exp, int);

#endif

