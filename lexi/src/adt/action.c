/* $Id$ */

/*
 * Copyright 2002-2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdlib.h>
#include <stdbool.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include <adt/action.h>

struct action *
action_create(void)
{
	struct action *act;

	act = xmalloc(sizeof *act);
	act->code    = NULL;
	act->defined = false;

	act->in  = NULL;
	act->out = NULL;

	return act;
}

void
action_set_inputs(struct action *act, struct param *p)
{
	act->in = p;
}

void
action_set_outputs(struct action *act, struct param *p)
{
	act->out = p;
}

struct param *
action_get_inputs(struct action *act)
{
	return act->in;
}

struct param *
action_get_outputs(struct action *act)
{
	return act->out;
}

struct code *
action_get_code(struct action *act)
{
	return act->code;
}

void
action_set_code(struct action *act, struct code *code)
{
	act->code = code;
}

void
action_set_define(struct action *act)
{
	act->defined = true;
}

int
action_is_defined(struct action *act)
{
	return act->defined;
}

