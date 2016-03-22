/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CODEHEREDECS_H
#define CODEHEREDECS_H

#include "procrec.h"
#include "addr.h"

extern int regofval(exp);
extern void reg_operand_here(exp, space, int);
extern int reg_operand(exp, space);
extern int freg_operand(exp, space, int);
extern int code_here(exp, space, where);

#endif
