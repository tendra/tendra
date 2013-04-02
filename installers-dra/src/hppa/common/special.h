/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef SPECIAL_INCLUDED
#define SPECIAL_INCLUDED

#include <construct/installtypes.h>
#include <construct/exp.h>

#include "proctypes.h"
#include "addrtypes.h"

extern int specialfn(exp);
extern char *special_call_name(int);
extern needs specialneeds(int, exp, exp);
extern int specialmake(int, exp, space, where, int);
extern void call_millicode(int, int, char*, bool);
extern void import_millicode(void);

#endif /* SPECIAL_INCLUDED */
