/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CODEHERE_INCLUDED
#define CODEHERE_INCLUDED

#include "addrtypes.h"

extern int regofval(exp);
extern void reg_operand_here(exp, space, int);
extern int reg_operand(exp, space);
extern int freg_operand(exp, space, int);
extern int code_here(exp, space, where);

#endif /* CODEHERE_INCLUDED */
