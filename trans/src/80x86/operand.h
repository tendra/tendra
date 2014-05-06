/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef OPERAND_H
#define OPERAND_H

#include <local/exptypes.h>
#include <local/localtypes.h>

void operand(int sz, where wh, int b, int addr);

extern int stack_dec;

int eq_where(where a, where b);
int eq_where_exp(exp a, exp b, int first, int overlap);
where mw(exp e, int off);

extern int crt_proc_id;
extern exp const_list;

frr first_reg(int r);

#endif /* OPERAND_H */
