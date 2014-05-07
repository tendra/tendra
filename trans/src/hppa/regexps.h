/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef REGEXPS_INCLUDED
#define REGEXPS_INCLUDED

#include <local/exptypes.h>

#include <construct/installtypes.h>

typedef struct {
    ans inans;
    exp keptexp;
    bool iscont;
} regpeep;

extern bool eq_sze(shape, shape);
extern bool dependson(exp, bool, exp);
extern void clear_all(void);
extern void clear_reg(int);
extern ans iskept(exp);
extern void keepexp(exp, ans);
extern void clear_dep_reg(exp);
extern void keepcont(exp, int);
extern void keepreg(exp, int);

#define clear_freg(R)clear_reg(((R) >> 1) + 32)

#endif /* REGEXPS_INCLUDED */
