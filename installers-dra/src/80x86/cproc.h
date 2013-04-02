/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CPROC_H
#define CPROC_H

int cproc (exp p, char *pname, int cname, int global, diag_global *diag_props);
void restore_callregs(int untidy);

extern  outofline *odd_bits;

#endif /* CPROC_H */
