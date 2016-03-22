/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef OPS_H
#define OPS_H

int comm_op(exp, space, where, ins_p);
int non_comm_op(exp, space, where, ins_p);
int monop(exp, space, where, ins_p);
int fop(exp, space, where, ins_p);
int fmop(exp, space, where, char *);
void logical_op(const char*, long, int, int);
void quad_op(exp, space, where);
void tidyshort(int, shape);
void import_long_double_lib(void);

#endif

