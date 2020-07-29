/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef OPS_H
#define OPS_H

int comm_op(exp e, space sp, where d, char *rins);
int non_comm_op(exp e, space sp, where dest, char *ins);
int monop(exp e, space sp, where dest, char *ins);
int fop(exp e, space sp, where dest, char *ins);
int fmop(exp e, space sp, where dest, char *ins);

#endif

