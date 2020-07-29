/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * rule-mutate.c - Compute mutation effects.
 *
 * This file implements the functions that compute the propogation of mutation
 * effects from actions that mutate their parameters.
 */

#include <shared/bool.h>
#include <shared/check.h>

#include "../adt/rule.h"
#include "../adt/action.h"
#include "../adt/types.h"

static void rule_compute_mutations_3(EntryT *, void *);

static void
rule_compute_mutations_4(RuleT *rule, AltT *alt, RuleT *from_rule)
{
	bool  propogate = false;
	ItemT *item;

	for (item = alt_item_head(alt); item; item = item_next(item)) {
		switch (item_type(item)) EXHAUSTIVE {
		case ET_RULE:
			if (entry_get_rule(item_entry(item)) != from_rule) {
				break;
			}

			if (types_compute_mutations(rule_param(rule), item_param(item),
				rule_param(from_rule))) {
				propogate = true;
			}
			break;

		case ET_ACTION:
		case ET_PREDICATE:
		case ET_RENAME:
		case ET_BASIC:
			break;

		case ET_NON_LOCAL:
		case ET_TYPE:
		case ET_NAME:
			UNREACHED;
		}
	}

	if (!propogate) {
		return;
	}

	entry_list_iter(rule_reverse_list(rule), rule_compute_mutations_3, rule);
}

static void
rule_compute_mutations_3(EntryT *entry, void *gclosure)
{
	RuleT *rule      = entry_get_rule(entry);
	RuleT *from_rule = gclosure;
	AltT  *alt;

	alt = rule_get_handler(rule);
	if (alt != NULL) {
		rule_compute_mutations_4(rule, alt, from_rule);
	}

	for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
		rule_compute_mutations_4(rule, alt, from_rule);
	}
}

static void
rule_compute_mutations_2(RuleT *rule, AltT *alt)
{
	bool    propogate = false;
	ItemT   *item;
	ActionT *action;

	for (item = alt_item_head(alt); item; item = item_next(item)) {
		switch (item_type(item)) EXHAUSTIVE {
		case ET_ACTION:
		case ET_PREDICATE:
			action = entry_get_action(item_entry(item));
			if (types_compute_mutations(rule_param(rule), item_param(item),
				action_param(action))) {
				propogate = true;
			}
			break;

		case ET_RENAME:
		case ET_BASIC:
		case ET_RULE:
			break;

		case ET_NON_LOCAL:
		case ET_TYPE:
		case ET_NAME:
			UNREACHED;
		}

		if (types_compute_assign_mutations(rule_param(rule),
			item_param(item))) {
			propogate = true;
		}
	}

	if (!propogate) {
		return;
	}

	entry_list_iter(rule_reverse_list(rule), rule_compute_mutations_3, rule);
}

static void
rule_compute_mutations_1(RuleT *rule)
{
	AltT *alt;

	alt = rule_get_handler(rule);
	if (alt != NULL) {
		rule_compute_mutations_2(rule, alt);
	}

	for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
		rule_compute_mutations_2(rule, alt);
	}
}


/*
 * Externally visible functions
 */

void
rule_compute_mutations(EntryT *entry, void *gclosure)
{
	RuleT *rule;

	UNUSED(gclosure);
	if (!entry_is_rule(entry)) {
		return;
	}

	rule = entry_get_rule(entry);
	rule_compute_mutations_1(rule);
}
