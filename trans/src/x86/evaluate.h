/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef EVALUATE_H
#define EVALUATE_H

#ifdef TDF_DIAG4
extern  void evaluate(exp c, int cname, char *s, int isconst, int global, struct dg_name_t *d);
#else
extern  void evaluate(exp c, int cname, char *s, int isconst, int global, diag_descriptor *d);
#endif

#endif /* EVALUATE_H */
