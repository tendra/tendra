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

	code_init(&act->code);
	typetuple_init(&act->in);
	typetuple_init(&act->out);

	act->defined = false;

	return act;
}

void
action_set_inputs(struct action *act, struct TypeTupleT *tuple)
{
	typetuple_assign(&act->in,tuple);
}

void
action_set_outputs(struct action *act, struct TypeTupleT *tuple)
{
	typetuple_assign(&act->out, tuple);
}

struct TypeTupleT *
action_get_inputs(struct action *act)
{
	return &act->in;
}

struct TypeTupleT *
action_get_outputs(struct action *act)
{
	return &act->out;
}

struct code *
action_get_code(struct action *act)
{
	return &act->code;
}

void
action_set_code(struct action *act, struct code *code)
{
	code_assign(&act->code, code);
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

