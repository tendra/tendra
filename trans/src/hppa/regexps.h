/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef REGEXPS_H
#define REGEXPS_H

#include <reader/exp.h>

#include <construct/installtypes.h>

typedef struct {
	ans inans;
	exp keptexp;
	bool iscont;
} regpeep;

bool eq_sze(shape, shape);
bool dependson(exp, bool, exp);
void clear_all(void);
void clear_reg(int);
ans iskept(exp);
void keepexp(exp, ans);
void clear_dep_reg(exp);
void keepcont(exp, int);
void keepreg(exp, int);

#define clear_freg(r) clear_reg(((r) >> 1) + 32)

#endif

