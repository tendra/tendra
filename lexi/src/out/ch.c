/* $Id$ */

/*
 * Copyright 2002-2014, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stddef.h>

#include <out/c.h>
#include <out/h.h>

void
ch_out_all(struct options *opt, struct ast *ast)
{
	assert(opt != NULL);
	assert(ast != NULL);

	c_out_all(opt, ast);
	h_out_all(opt, ast);
}

