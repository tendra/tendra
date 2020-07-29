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

#include "addr.h"

struct regpeept {
	ans inans;
	exp keptexp;
	bool iscont;
};

typedef struct regpeept regpeep;

void clear_all(void);
void clear_reg(int i);
ans iskept(exp e);
void keepexp(exp e, ans loc);
void clear_dep_reg(exp lhs);
void keepcont(exp e, int reg);
void keepreg(exp e, int reg);
bool eq_sze(shape, shape);
bool dependson(exp, bool, exp);

#endif

