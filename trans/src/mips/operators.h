/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <reader/exp.h>

#include "addrtypes.h"

extern int comm_op(exp e, space sp, where d, char *rins);
extern int non_comm_op(exp e, space sp, where dest, char *ins);
extern int monop(exp e, space sp, where dest, char *ins);
extern int fop(exp e, space sp, where dest, char *ins);
extern int fmop(exp e, space sp, where dest, char *ins);
