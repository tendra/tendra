/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef EVAL_H
#define EVAL_H

void evaluate(exp c, int cname, char *s, int isconst, int global,
#ifdef TDF_DIAG4
	struct dg_name_t *d
#else
	diag_descriptor *d
#endif
	);

#endif

