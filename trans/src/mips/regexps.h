/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <reader/exp.h>

#include <construct/installtypes.h>

#include "addrtypes.h"

struct regpeept {
  ans inans;
  exp keptexp;
  bool iscont;
};

typedef struct regpeept regpeep;

extern void clear_all(void);
extern void clear_reg(int i);
extern ans iskept(exp e);
extern void keepexp(exp e, ans loc);
extern void clear_dep_reg(exp lhs);
extern void keepcont(exp e, int reg);
extern void keepreg(exp e, int reg);
extern regpeep regexps[48];
extern bool eq_sze(shape, shape);
extern bool dependson(exp, bool, exp);
