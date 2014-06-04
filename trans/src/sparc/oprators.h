/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef OPRATORS_INCLUDED
#define OPRATORS_INCLUDED

#include <construct/installtypes.h>

#include <reader/exp.h>

#include "addrtypes.h"

extern bool regremoved(exp *, int);
extern int comm_op(exp, space, where, ins_p);
extern int fop(exp, space, where, ins_p);
extern int monop(exp, space, where, ins_p);
extern int absop(exp, space, where);
extern int non_comm_op(exp, space, where, ins_p);
extern void do_comm(exp, space, int, ins_p);
extern void tidyshort(int, shape);

extern void quad_op(exp, exp, space, where, int);

#endif /* OPRATORS_INCLUDED */
