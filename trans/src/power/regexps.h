/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef	REGEXPS_H
#define	REGEXPS_H

/* number to add to floating point reg number for these functions */
#define	KEPT_FREG_OFFSET 32

void clear_all(void);
void clear_reg(int);

#define clear_freg(r) clear_reg((r) + KEPT_FREG_OFFSET)

bool keep_eq_size(shape, shape);

ans iskept(exp);
ans iskept_reg(exp);
ans iskept_inreg(exp, int);

int ans_reg(ans);

void keepexp(exp, ans);
void keepcont(exp, int);
void keepreg(exp, int);

bool dependson(exp, bool, exp);
void clear_dep_reg(exp);

#endif

