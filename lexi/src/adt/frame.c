/* $Id$ */

/*
 * Copyright 2002-2014, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/xalloc.h>

#include <adt/frame.h>

struct frame *
add_frame(void)
{
	struct frame *p;

	p = xmalloc(sizeof *p);
	p->cmds   = NULL;
	p->locals = NULL;

	return p;
}

