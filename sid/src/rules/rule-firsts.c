/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * rule-firsts.c - Computation of rule first sets.
 *
 * This file implements the SID first set calculation routines.
 *
 * The first set of a rule is the set of all terminals that may start that
 * rule.  As well as computing the first set of a rule, its priority and
 * whether or not it is see through are also computed.  A rule is see through
 * if there is an expansion of the rule that does not involve a basic or
 * predicate.  The priority is used during the factorisation phase to work out
 * which rules to expand.  The rule's priority is one more than the priority
 * of the rule with the highest priority in any of the rule's alternatives
 * that is not preceded by an action.  If there is no such rule, then the
 * rule's priority is one.
 *
 * As well as computing the first sets, these routines check that there are no
 * recursive calls that are not preceded by a basic or predicate.  They also
 * check that predicates are either the first item in an alternative, or are
 * preceded by a basic (or another predicate).  The same check is also made
 * for rules that start with a predicate.
 */

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include "../adt/rule.h"
#include "../adt/basic.h"
#include "../adt/table.h"

void
rule_compute_first_set_1(RuleT *rule)
{
    AltT     *alt;
    unsigned  priority = 0;

	if (rule_has_computed_first_set(rule)) {
		return;
	} else if (rule_is_computing_first_set(rule)) {
		error(ERR_SERIOUS, "cannot compute first set for production\n%R",
			(void *) rule);
		return;
	}

	rule_computing_first_set(rule);
	for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
		bool  see_through = true;
		bool  no_action   = true;
		ItemT *item        = alt_item_head(alt);
		ItemT *initial     = item;

		for ( ; see_through && item != NULL; item = item_next(item)) {
			switch (item_type(item)) EXHAUSTIVE {
			case ET_PREDICATE:
				if (item != initial) {
					error(ERR_FATAL, "can see through to predicate '%K' in production\n%R",
						(void *) entry_key(item_entry(item)), (void *) rule);
					UNREACHED;
				}
				entry_list_add_if_missing(rule_predicate_first(rule),
					item_entry(item));
				see_through = false;
				break;

			case ET_RENAME:
			case ET_ACTION:
				no_action = false;
				break;

			case ET_RULE: {
					EntryT     *entry      = item_entry(item);
					RuleT      *item_rule  = entry_get_rule(entry);
					EntryListT *pred_first = rule_predicate_first(item_rule);
					unsigned   item_priority;

					rule_compute_first_set_1(item_rule);
					if (item != initial && !entry_list_is_empty(pred_first)) {
						error(ERR_FATAL, "can see through to predicates in rule '%N' in production\n%R",
							(void *) item_rule, (void *) rule);
						UNREACHED;
					}

					bitvec_or(rule_first_set(rule), rule_first_set(item_rule));
					entry_list_append(rule_predicate_first(rule), pred_first);
					see_through   = rule_is_see_through(item_rule);
					item_priority = rule_get_priority(item_rule);

					if (item_priority > priority && no_action) {
						priority = item_priority;
					}
				}
				break;

			case ET_BASIC: {
					BasicT *basic = entry_get_basic(item_entry(item));

					bitvec_set(rule_first_set(rule), basic_terminal(basic));
					see_through = false;
				}
				break;

			case ET_NON_LOCAL:
			case ET_NAME:
			case ET_TYPE:
				UNREACHED;
			}
		}

		if (see_through) {
			rule_see_through(rule);
		}
    }

    if (rule_has_empty_alt(rule)) {
		rule_see_through(rule);
    }

    rule_set_priority(rule, priority + 1);
    if (rule_is_see_through(rule) && bitvec_is_full(rule_first_set(rule))) {
		error(ERR_FATAL, "the rule '%N' has all terminals in its first set and has a redundant see through alternative",
			(void *) rule);
		UNREACHED;
    }

    rule_computed_first_set(rule);
}

void
rule_compute_first_set(EntryT *entry, void *gclosure)
{
    UNUSED(gclosure);
    if (entry_is_rule(entry)) {
		RuleT *rule = entry_get_rule(entry);

		rule_compute_first_set_1(rule);
    }
}
