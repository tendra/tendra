/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * c-check.c - Routines to check grammar.
 *
 * This file contains routines to check that all actions and basic result
 * extraction functions are defined.
 */

#include <shared/check.h>
#include <shared/error.h>

#include "c-check.h"
#include "../adt/action.h"
#include "../adt/basic.h"
#include "../adt/entry.h"
#include "../adt/table.h"
#include "../adt/type.h"

static void
c_check_grammar_1(EntryT *entry, void *gclosure)
{
	TypeT *type;

	UNUSED(gclosure);
	switch (entry_type(entry))EXHAUSTIVE {
	case ET_RULE:
		break;

	case ET_BASIC: {
			BasicT *basic = entry_get_basic(entry);

			if (!types_equal_zero_tuple(basic_result(basic)) &&
				basic_get_result_code(basic) == NULL) {
				error(ERR_SERIOUS, "result code not defined for basic '%K'",
					(void *) entry_key(entry));
			}
		}
		break;

	case ET_ACTION:
		if (action_get_code(entry_get_action(entry)) == NULL) {
			error(ERR_SERIOUS, "definition code not defined for action '%K'",
				(void *) entry_key(entry));
		}
		break;

	case ET_TYPE:
		type = entry_get_type(entry);
		if ((type_get_assign_code(type) != NULL
				|| type_get_param_assign_code(type) != NULL
				|| type_get_result_assign_code(type) != NULL)
			&& (type_get_assign_code(type) == NULL
				|| type_get_param_assign_code(type) == NULL
				|| type_get_result_assign_code(type) == NULL)) {
			error(ERR_SERIOUS, "some but not all assignment operators defined for type '%K'",
				(void *) entry_key(entry));
		}
		break;

	case ET_NON_LOCAL:
	case ET_NAME:
	case ET_RENAME:
		break;

	case ET_PREDICATE:
		UNREACHED;
	}
}

void
c_check_grammar(GrammarT *grammar)
{
	table_iter(grammar_table(grammar), c_check_grammar_1, NULL);
}
