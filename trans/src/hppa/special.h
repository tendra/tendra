/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef SPECIAL_H
#define SPECIAL_H

#include <construct/installtypes.h>
#include <construct/exp.h>

#include "addr.h"

int specialfn(exp);
char *special_call_name(int);
needs specialneeds(int i);
int specialmake(int, exp, space, where, int);
void call_millicode(int, int, char*, bool);
void import_millicode(void);

#endif

