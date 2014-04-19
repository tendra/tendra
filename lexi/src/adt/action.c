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

ActionT *
action_create(void)
{
	ActionT *action;

	action = xmalloc_nof(ActionT, 1);

	ccode_init(&action->code);
	typetuple_init(&action->inputs);
	typetuple_init(&action->outputs);

	action->defined = false;

	return action;
}

void
action_set_inputs(ActionT *action, TypeTupleT *tuple)
{
	typetuple_assign(&action->inputs,tuple);
}

void
action_set_outputs(ActionT *action, TypeTupleT *tuple)
{
	typetuple_assign(&action->outputs, tuple);
}

TypeTupleT *
action_get_inputs(ActionT *action)
{
	return &action->inputs;
}

TypeTupleT *
action_get_outputs(ActionT *action)
{
	return &action->outputs;
}

CcodeT *
action_get_code(ActionT *action)
{
	return &action->code;
}

void
action_set_code(ActionT *action, CcodeT *code)
{
	ccode_assign(&action->code, code);
}

void
action_set_define(ActionT *action)
{
	action->defined = true;
}

int
action_is_defined(ActionT *action)
{
	return action->defined;
}

