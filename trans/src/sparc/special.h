/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef SPECIAL_INCLUDED
#define SPECIAL_INCLUDED

#include <construct/exp.h>
#include "proctypes.h"
#include "addrtypes.h"

extern char *special_call_name(int);
extern int specialfn(exp);
extern int specialmake(int, exp, space, where, int);
extern int specialopt(exp);
extern needs specialneeds(int, exp, exp);

extern int library_key;
extern void call_special_routine(int);
extern void output_special_routines(void);

#define SPECIAL_MUL	0
#define SPECIAL_UMUL	1
#define SPECIAL_DIV2	2
#define SPECIAL_UDIV2	3
#define SPECIAL_REM2	4
#define SPECIAL_UREM2	5
#define SPECIAL_DIV1	6
#define SPECIAL_REM1	7

#endif /* SPECIAL_INCLUDED */
