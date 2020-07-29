/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * rule-names.c - Recompute alternative names.
 *
 * This file implements the functions that recompute the names defined in each
 * alternative of a rule (including the exception handler alternative).
 */

#include <shared/bool.h>
#include <shared/check.h>

#include "../adt/rule.h"
#include "../adt/action.h"
#include "../adt/basic.h"
#include "../adt/name.h"
#include "../adt/type.h"
#include "../adt/types.h"

static void
rule_recompute_alt_names_2(AltT *alt, EntryT *predicate_id)
{
	TypeTupleT *names = alt_names(alt);
	ItemT      *item;

	types_destroy(names);
	types_init(names);
	for (item = alt_item_head(alt); item; item = item_next(item)) {
		types_add_new_names(names, item_result(item), predicate_id);
	}
}

static void
rule_recompute_alt_names_1(RuleT *rule, EntryT *predicate_id)
{
	AltT *alt;

	if ((alt = rule_get_handler(rule)) != NULL) {
		rule_recompute_alt_names_2(alt, predicate_id);
	}

	for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
		rule_recompute_alt_names_2(alt, predicate_id);
	}
}


/*
 * Externally visible functions
 */

void
rule_recompute_alt_names(EntryT *entry, void *gclosure)
{

	RuleT  *rule;
	EntryT *predicate_id;

	if (!entry_is_rule(entry)) {
		return;
	}

	rule = entry_get_rule(entry);
	predicate_id = gclosure;

	rule_recompute_alt_names_1(rule, predicate_id);
}
