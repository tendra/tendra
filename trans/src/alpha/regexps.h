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
  int alignment;
};

typedef struct regpeept regpeep;

extern  void clear_all(void);
extern  void clear_reg(int);
extern  ans iskept(exp);
extern  void keepexp(exp, ans);
extern  void clear_dep_reg(exp);
extern  void keepcont(exp, int);
extern  void keepreg(exp, int);
extern bool dependson(exp, bool, exp);
extern bool eq_sze(shape,shape);
extern void clear_freg(int);

extern  regpeep regexps[64];


