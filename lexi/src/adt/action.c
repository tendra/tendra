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

struct ActionT *
action_create(void)
{
	struct ActionT *action;

	action = xmalloc(sizeof *action);

	ccode_init(&action->code);
	typetuple_init(&action->inputs);
	typetuple_init(&action->outputs);

	action->defined = false;

	return action;
}

void
action_set_inputs(struct ActionT *action, struct TypeTupleT *tuple)
{
	typetuple_assign(&action->inputs,tuple);
}

void
action_set_outputs(struct ActionT *action, struct TypeTupleT *tuple)
{
	typetuple_assign(&action->outputs, tuple);
}

struct TypeTupleT *
action_get_inputs(struct ActionT *action)
{
	return &action->inputs;
}

struct TypeTupleT *
action_get_outputs(struct ActionT *action)
{
	return &action->outputs;
}

struct CcodeT *
action_get_code(struct ActionT *action)
{
	return &action->code;
}

void
action_set_code(struct ActionT *action, struct CcodeT *code)
{
	ccode_assign(&action->code, code);
}

void
action_set_define(struct ActionT *action)
{
	action->defined = true;
}

int
action_is_defined(struct ActionT *action)
{
	return action->defined;
}

