/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * action.c - Action ADT.
 *
 * This file implements the action manipulation routines.
 */

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>

#include <shared/check.h>

#include "action.h"
#include "basic.h"
#include "name.h"
#include "rule.h"
#include "type.h"

ActionT *
action_create(BoolT ignored)
{
	ActionT *action = ALLOCATE(ActionT);

	types_init(action_param(action));
	types_init(action_result(action));
	action->code = NULL;
	action->ignored = ignored;

	return action;
}

/* TODO some of these could become macros or inlined functions */
TypeTupleT *
action_param(ActionT *action)
{
	return &action->param;
}

TypeTupleT *
action_result(ActionT *action)
{
	return &action->result;
}

void *
action_get_code(ActionT *action)
{
	return action->code;
}

void
action_set_code(ActionT *action, void *code)
{
	action->code = code;
}

BoolT
action_get_ignored(ActionT *action)
{
	return action->ignored;
}

void
action_iter_for_table(ActionT *action, BoolT full,
	void (*proc) WEAK (EntryT *, void *), void *closure)
{
	if (!full) {
		return;
	}

	types_iter_for_table(action_param(action), proc, closure);
	types_iter_for_table(action_result(action), proc, closure);
}
