/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef SPECIAL_H
#define SPECIAL_H

#include <construct/exp.h>

#include "addrtypes.h"

needs specialneeds(int i);
char *special_call_name(int);
int specialfn(exp);
int specialmake(int, exp, space, where, int);
int specialopt(exp);

extern int library_key;
void call_special_routine(int);
void output_special_routines(void);

enum {
	SPECIAL_MUL   = 0,
	SPECIAL_UMUL  = 1,
	SPECIAL_DIV2  = 2,
	SPECIAL_UDIV2 = 3,
	SPECIAL_REM2  = 4,
	SPECIAL_UREM2 = 5,
	SPECIAL_DIV1  = 6,
	SPECIAL_REM1  = 7
};

#endif

