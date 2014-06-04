/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef misc_c_key
#define misc_c_key 1

#include <reader/exp.h>

extern int invariant_to_apply(exp e);
extern int take_out_of_line(exp first, exp alt, int in_repeat, double scale);
extern int take_out_by_prob(exp first, exp alt);
extern int is_maxop(exp x, exp *t);
extern int is_minop(exp x, exp *t);
extern int is_tester(exp e, int eq);
extern int is_condassign(exp e, exp *to_test, exp *to_ass);

#endif
