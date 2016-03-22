/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef OPS_H
#define OPS_H

int comm_op(exp, space, where, instruction);
int non_comm_op(exp, space, where, instruction);
int monop(exp, space, where, instruction);
int fop(exp, space, where, instruction);
int fmop(exp, space, where, instruction);
void tidyshort(int, shape);

#endif

