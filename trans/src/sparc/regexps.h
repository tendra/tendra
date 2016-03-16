/* $Id$ */

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

#include "addrtypes.h"

typedef struct {
	ans inans;
	exp keptexp;
	bool iscont;
} regpeep;

regpeep regexps[48];

ans iskept(exp);
bool sim_exp(exp, exp);
void clear_all(void);
void clear_dep_reg(exp);
void clear_reg(int);
void keepcont(exp, int);
void keepexp(exp, ans);
void keepreg(exp, int);

#define clear_freg(r) clear_reg(((r) >> 1) + 32)

#endif

