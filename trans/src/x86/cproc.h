/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CPROC_H
#define CPROC_H

#ifdef NEWDIAGS
int cproc (exp p, char *pname, int cname, int global, struct dg_name_t *diag_props);
#else
int cproc (exp p, char *pname, int cname, int global, diag_global *diag_props);
#endif
void restore_callregs(int untidy);

extern  unsigned normal_fpucon;
extern  int stack_aligned_8byte;
extern  int permit_8byte_align;
extern  int useful_double;
extern  int keep_short;
extern  int always_use_frame;   /* always use %ebp as a frame pointer */
extern  outofline *odd_bits;

#endif /* CPROC_H */
