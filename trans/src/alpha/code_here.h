/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "procrectypes.h"
#include "addresstypes.h"

extern int  regofval(exp e);
extern int  fregofval(exp e);
extern int  reg_operand(exp e, space sp);
extern int  freg_operand(exp e, space sp);
extern int  code_here(exp e, space sp, where dest);
