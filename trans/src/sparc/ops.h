/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef OPS_H
#define OPS_H

extern int comm_op(exp, space, where, ins_p);
extern int fop(exp, space, where, ins_p);
extern int monop(exp, space, where, ins_p);
extern int absop(exp, space, where);
extern int non_comm_op(exp, space, where, ins_p);
extern void quad_op(exp, exp, space, where, int);

#endif

