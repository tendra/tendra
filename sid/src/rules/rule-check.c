/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * rule-check.c - Checks for grammar validity.
 *
 * This file implements the routines that check to see if the grammar is
 * valid.  There are for checks that are made:
 *
 *	- The first sets of all alternatives in a rule are checked to ensure
 *	that they are disjoint (this includes the predicate first sets).  This
 *	also includes checking that there is only one see through alternative.
 *
 *	- The follow set of each rule is computed, and checked to ensure that
 *	if the rule is see through, its follow set does not intersect with its
 *	first set (this includes predicate follow and first sets).
 *
 *	- If there is a see-through alternative, this is computed.
 *
 *	- The first set of each alternative is computed.
 */

#include <assert.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <exds/bitvec.h>

#include "../adt/rule.h"
#include "../adt/basic.h"

static void
rule_check_first_set_1(RuleT *rule, GrammarT *grammar)
{
	bool         is_empty            = rule_has_empty_alt(rule);
	bool         is_empty_mesg_shown = false;
	BitVecT       test;
	EntryListT    predicate_list;
	AltT          *alt;
	BasicClosureT closure;

	closure.grammar = grammar;
	bitvec_init(&test);
	entry_list_init(&predicate_list);
	for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
		ItemT *item        = alt_item_head(alt);
		bool see_through = true;
#ifndef NDEBUG
		ItemT *initial     = item;
#endif

		for ( ; see_through && item; item = item_next(item)) {
			EntryT *entry = item_entry(item);

			switch (item_type(item)) EXHAUSTIVE {
			case ET_PREDICATE:
				assert(item == initial);
				if (entry_list_contains(&predicate_list, entry)) {
					error(ERR_SERIOUS, "collision of predicate '%K', in rule '%N'",
						(void *) rule, (void *) entry_key(entry));
				} else {
					entry_list_add(&predicate_list, entry);
				}
				see_through = false;
				break;

			case ET_ACTION:
			case ET_RENAME:
				break;

			case ET_BASIC: {
					unsigned terminal = basic_terminal(entry_get_basic(entry));
					BitVecT tmp;

					see_through = false;
					if (!bitvec_is_set(&test, terminal)) {
						bitvec_set(&test, terminal);
						break;
					}

					bitvec_init(&tmp);
					bitvec_set(&tmp, terminal);
					bitvec_and(&tmp, &test);
					closure.bitvec = &tmp;
					error(ERR_SERIOUS, "collision of terminal(s) %B in rule '%N'",
						(void *) &closure, (void *) rule);
					bitvec_destroy(&tmp);
				}
				break;

			case ET_RULE: {
					RuleT      *item_rule  = entry_get_rule(entry);
					EntryListT *item_preds = rule_predicate_first(item_rule);
					EntryListT  tmp_list;
					BitVecT    *bitvec;
					BitVecT     tmp;

					entry_list_intersection(&tmp_list, &predicate_list,
					item_preds);

					if (!entry_list_is_empty(&tmp_list)) {
						error(ERR_SERIOUS, "collision of predicates %L in rule '%N'",
							(void *) &tmp_list, (void *) rule);
					}

					entry_list_destroy(&tmp_list);
					entry_list_append(&predicate_list, item_preds);
					bitvec      = rule_first_set(item_rule);
					see_through = rule_is_see_through(item_rule);

					if (!bitvec_intersects(&test, bitvec)) {
						bitvec_or(&test, bitvec);
						break;
					}

					bitvec_copy(&tmp, bitvec);
					bitvec_and(&tmp, &test);
					closure.bitvec = &tmp;
					error(ERR_SERIOUS, "collision of terminal(s) %B in rule '%N'",
						(void *) &closure, (void *) rule);
					bitvec_destroy(&tmp);
				}
				break;

			case ET_NON_LOCAL:
			case ET_TYPE:
			case ET_NAME:
				UNREACHED;
			}

		}

		if (!see_through) {
			continue;
		}

		if (is_empty) {
			if (!is_empty_mesg_shown) {
				error(ERR_SERIOUS, "the rule '%N' contains more than one see through alternative",
					(void *) rule);
				is_empty_mesg_shown = true;
			}
		} else {
			is_empty = true;
		}
	}
	bitvec_destroy(&test);
}

static void rule_compute_follow_set_1(RuleT *, GrammarT *, BitVecT *, EntryListT *,
	ClashListT *);

static void
rule_compute_follow_set_3(GrammarT *grammar, ItemT *item, BitVecT *context,
	EntryListT *pred_context, ClashListT *clashes)
{
	EntryT * entry;

	if (item == NULL) {
		return;
	}

	rule_compute_follow_set_3(grammar, item_next(item), context,
		pred_context, clashes);
	entry = item_entry(item);

	switch (item_type(item)) EXHAUSTIVE {
	case ET_PREDICATE:
		entry_list_destroy(pred_context);
		entry_list_init(pred_context);
		entry_list_add(pred_context, entry);
		clashes->next = NULL;
		break;

	case ET_ACTION:
	case ET_RENAME:
		break;

	case ET_RULE: {
			RuleT *rule = entry_get_rule(entry);

			clashes->item = item;
			rule_compute_follow_set_1(rule, grammar, context, pred_context,
				clashes);

			if (rule_is_see_through(rule)) {
				bitvec_or(context, rule_first_set(rule));
				entry_list_append(pred_context, rule_predicate_first(rule));
			} else {
				bitvec_replace(context, rule_first_set(rule));
				entry_list_destroy(pred_context);
				entry_list_init(pred_context);
				entry_list_append(pred_context, rule_predicate_first(rule));
				clashes->next = NULL;
			}
		}
		break;

	case ET_BASIC: {
			BasicT *basic = entry_get_basic(entry);

			bitvec_empty(context);
			bitvec_set(context, basic_terminal(basic));
			clashes->next = NULL;
		}
		break;

	case ET_NON_LOCAL:
	case ET_NAME:
	case ET_TYPE:
		UNREACHED;
	}
}

static void
rule_compute_follow_set_2(RuleT *rule, GrammarT *grammar, AltT *alt,
	BitVecT *context, EntryListT *pred_context, ClashListT *clashes)
{
	BitVecT    tmp;
	EntryListT tmp_list;
	ClashListT clash;

	clash.next = clashes;
	clash.rule = rule;
	clash.alt  = alt;
	bitvec_copy(&tmp, context);
	entry_list_copy(&tmp_list, pred_context);
	rule_compute_follow_set_3(grammar, alt_item_head(alt), &tmp, &tmp_list,
		&clash);
	bitvec_destroy(&tmp);
	entry_list_destroy(&tmp_list);
}

static void
rule_compute_follow_set_1(RuleT *rule, GrammarT *grammar, BitVecT *context,
	EntryListT *pred_context, ClashListT *clashes)
{
	BitVecT    *follow      = rule_follow_set(rule);
	EntryListT *pred_follow = rule_predicate_follow(rule);
	BitVecT    *first       = rule_first_set(rule);
	EntryListT *pred_first  = rule_predicate_first(rule);
	BitVecT     test;
	AltT       *alt;
	BasicClosureT closure;

	if (rule_has_started_follows(rule)) {
		bitvec_copy(&test, follow);
		bitvec_or(follow, context);
		if (bitvec_equal(&test, follow) &&
			entry_list_includes(pred_follow, pred_context)) {
			bitvec_destroy(&test);
			return;
		}

		entry_list_append(pred_follow, pred_context);
		bitvec_destroy(&test);
	} else {
		bitvec_replace(follow, context);
		entry_list_append(pred_follow, pred_context);
		rule_started_follows(rule);
	}

	closure.grammar = grammar;
	if (rule_is_see_through(rule)) {
		EntryListT tmp_list;

		if (bitvec_intersects(follow, first)) {
			bitvec_copy(&test, follow);
			bitvec_and(&test, first);
			closure.bitvec = &test;
			error(ERR_SERIOUS, "the terminal(s) %B can start rule '%N' which "
				"is see through, and the same terminal(s) may appear in the "
				"following situations:\n%A",
				(void *) &closure, (void *) rule, (void *) clashes);
			bitvec_not(&test);
			bitvec_and(first, &test);
			bitvec_destroy(&test);
		}

		entry_list_intersection(&tmp_list, pred_follow, pred_first);
		if (!entry_list_is_empty(&tmp_list)) {
			error(ERR_SERIOUS, "the predicate(s) %L can start rule '%N' which "
				"is see through, and the same predicate(s) may appear in the "
				"following situations:\n%A",
				(void *) &tmp_list, (void *) rule, (void *) clashes);
			entry_list_unlink_used(pred_first, &tmp_list);
		}
		entry_list_destroy(&tmp_list);
	}

	alt = rule_get_handler(rule);
	if (alt != NULL) {
		rule_compute_follow_set_2(rule, grammar, alt, follow, pred_follow,
			clashes);
	}

	for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
		rule_compute_follow_set_2(rule, grammar, alt, follow, pred_follow,
			clashes);
	}
}

static void
rule_compute_see_through_alt_1(RuleT *rule)
{
	AltT *alt;

	if (rule_has_empty_alt(rule)) {
		return;
	}

	for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
		ItemT *item;

		for (item = alt_item_head(alt); item; item = item_next(item)) {
			RuleT *item_rule;

			if (item_is_action(item) || item_is_rename(item)) {
				continue;
			}

			if (!item_is_rule(item)) {
				goto next_alt;
			}

			/* TODO: assert item is entry? */
			item_rule = entry_get_rule(item_entry(item));
			if (!rule_is_see_through(item_rule)) {
				goto next_alt;
			}
		}

		rule_set_see_through_alt(rule, alt);
		return;

next_alt:
			;
	}
}

static void
rule_compute_alt_first_sets_1(RuleT *rule)
{
	AltT *alt;

	for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
		BitVecT *alt_firsts  = alt_first_set(alt);
		ItemT   *item        = alt_item_head(alt);
		bool    see_through = true;
#ifndef NDEBUG
		ItemT   *initial     = item;
#endif

		for (; see_through && item; item = item_next(item)) {
			EntryT *entry = item_entry(item);

			switch (item_type(item)) EXHAUSTIVE {
			case ET_PREDICATE:
				assert(item == initial);
				see_through = false;
				break;

			case ET_ACTION:
			case ET_RENAME:
				break;

			case ET_BASIC:
				see_through = false;
				bitvec_set(alt_firsts, basic_terminal(entry_get_basic(entry)));
				break;

			case ET_RULE: {
					RuleT *item_rule = entry_get_rule(entry);

					see_through = rule_is_see_through(item_rule);
					bitvec_or(alt_firsts, rule_first_set(item_rule));
				}
				break;

			case ET_NON_LOCAL:
			case ET_TYPE:
			case ET_NAME:
				UNREACHED;
			}
		}

		if (see_through) {
			bitvec_or(alt_firsts, rule_follow_set(rule));
		}
	}
}


/*
 * Externally visible functions
 */

void
rule_check_first_set(EntryT * entry, void * gclosure)
{
	GrammarT *grammar = gclosure;

	if (entry_is_rule(entry)) {
		RuleT *rule = entry_get_rule(entry);

		rule_check_first_set_1(rule, grammar);
	}
}

void
rule_compute_follow_set(EntryT *entry, void *gclosure)
{
	GrammarT   *grammar = gclosure;
	RuleT      *rule;
	BitVecT     outer;
	EntryListT  pred_outer;

	if (!entry_is_rule(entry)) {
		return;
	}

	rule = entry_get_rule(entry);
	bitvec_init(&outer);
	entry_list_init(&pred_outer);
	rule_compute_follow_set_1(rule, grammar, &outer, &pred_outer, NULL);
	bitvec_destroy(&outer);
	entry_list_destroy(&pred_outer);
}

void
rule_compute_see_through_alt(EntryT *entry, void *gclosure)
{
	UNUSED(gclosure);
	if (entry_is_rule(entry)) {
		RuleT *rule = entry_get_rule(entry);

		rule_compute_see_through_alt_1(rule);
	}
}

void
rule_compute_alt_first_sets(EntryT *entry, void *gclosure)
{
	UNUSED(gclosure);
	if (entry_is_rule(entry)) {
		RuleT *rule = entry_get_rule(entry);

		rule_compute_alt_first_sets_1(rule);
	}
}

void
write_clashes(OStreamT *ostream, ClashListT *clashes)
{
	write_newline(ostream);

	for (; clashes; clashes = clashes->next) {
		write_rule_lhs(ostream, clashes->rule);
		write_alt_highlighting(ostream, clashes->alt, clashes->item);
		write_cstring(ostream, "};");
		write_newline(ostream);
	}
}
