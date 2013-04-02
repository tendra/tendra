/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef OPRATORS_INCLUDED
#define OPRATORS_INCLUDED

#include "exptypes.h"
#include "addrtypes.h"

extern int comm_op(exp, space, where, ins_p);
extern int non_comm_op(exp, space, where, ins_p);
extern int monop(exp, space, where, ins_p);
extern int fop(exp, space, where, ins_p);
extern int fmop(exp, space, where, char *);
extern void logical_op(const char*, long, int, int);
extern void quad_op(exp, space, where);
extern void tidyshort(int, shape);
extern void import_long_double_lib(void);
#endif /* OPRATORS_INCLUDED */
