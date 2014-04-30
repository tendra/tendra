/* $Id$ */

/*
 * Copyright 2002-2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdlib.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/xalloc.h>

#include <adt/action.h>

struct action *
action_create(struct param *in, struct param *out)
{
	struct action *act;

	act = xmalloc(sizeof *act);
	act->code    = NULL;
	act->defined = 0;

	act->in  = in;
	act->out = out;

	return act;
}

