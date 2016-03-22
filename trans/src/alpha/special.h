/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef SPECIAL_H
#define SPECIAL_H

#include <reader/exp.h>

#include <construct/exp.h>

#include "procrec.h"
#include "addr.h"

needs specialneeds(int i);
int specialfn(exp fn);
int specialmake(int n, exp par, space sp, where dest, int exitlab);

#endif

