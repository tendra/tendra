/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef misc_c_key
#define misc_c_key 1

bool is_maxop(exp x, exp *t);
bool is_minop(exp x, exp *t);
bool is_tester(exp e, int eq); /* XXX: enum for eq? */
bool is_condassign(exp e, exp *to_test, exp *to_ass);

bool comp_eq_exp(exp a, exp b, exp laba, exp labb);

bool oddtest(exp, exp *, exp *, exp *);
bool is_maxlike(exp, exp *);
bool is_minlike(exp, exp *);
bool is_abslike(exp, exp *);
bool is_fabs(exp, exp *);

#endif
