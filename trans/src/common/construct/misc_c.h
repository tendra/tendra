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

extern bool take_out_of_line(exp first, exp alt, int in_repeat, double scale);
extern bool take_out_by_prob(exp first, exp alt);

extern bool is_maxop(exp x, exp *t);
extern bool is_minop(exp x, exp *t);
extern bool is_tester(exp e, int eq);
extern bool is_condassign(exp e, exp *to_test, exp *to_ass);

#endif
