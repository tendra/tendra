/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef REGALLOC_H
#define REGALLOC_H

#include <reader/exp.h>

spacereq regalloc(exp, int, int, long);
int real_reg[16];

#endif

