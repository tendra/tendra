/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef TEMPDECS_INCLUDED
#define TEMPDECS_INCLUDED

#include <reader/exp.h>

#include <construct/installtypes.h>

extern bool simple_seq(exp, exp);
extern bool tempdec(exp, bool);
extern int trace_uses(exp, exp);
extern void after_a(exp, exp);

#endif /* TEMPDECS_INCLUDED */
