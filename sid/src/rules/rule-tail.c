/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * rule-tail.c - Tail recursion elimination routines.
 *
 * This file implements the SID inlining routines.
 *
 * There are five separate phases implemented in this file.
 *
 * The first phase is to find and eliminate all tail recursive cycles that
 * each rule is involved in.  The cycles are detected by the
 * grammar_compute_inlining() function in the file "grammar.c".  For each
 * cyclic group that is found, the rule_handle_tails() function is called to
 * remove the cycle.  All rules in the cycle are marked as being cyclic, and
 * are given a unique identification that is the same for all members of the
 * cycle (but different for members of different cycles).  The tail recursive
 * calls are marked as inlinable and tail recursive, and the rules' call
 * graphs are computed (this is the set of rules that will make tail calls).
 * This phase is only performed if tail recursion inlining is enabled.
 *
 * The second phase is implemented by the rule_compute_all_basics() function.
 * This marks a rule that only contains basics as such.  This phase is only
 * performed if all basic inlining is enabled.
 *
 * The third phase is implemented by the rule_compute_inlining() function.
 * This marks all calls to all basic rules as inlinable.  If single
 * alternative rule inlining is enabled, then all calls to single alternative
 * rules are marked as inlinable.  If non tail recursion inlining is enabled,
 * it also marks all other calls as inlinable, and computes their call count
 * if functions that are called more than once are not to be inlined (the
 * output routines won't inline rules with a call count greater than one).
 *
 * The fourth phase is implemented by the rule_compute_needed_functions()
 * function.  It marks all required functions, and functions that are called
 * from a non-inlinable position as requiring function implementations.
 *
 * The final phase is implemented by the rule_handle_need_functions()
 * function.  The cycle detection routines are used in the
 * grammar_compute_inlining() function to find cycles in the function call
 * graph.  If any such cycles are found, then all of the rules in the cycle
 * are marked as needing a function implementation.
 */

#include <shared/bool.h>
#include <shared/check.h>

#include "../adt/rule.h"
#include "../adt/action.h"
#include "../adt/basic.h"
#include "../adt/entry-list.h"
#include "../adt/name.h"
#include "../adt/type.h"

typedef struct CycleHeadT {
	RuleT  *head;
	RuleT *	*tail;
} CycleHeadT;

typedef struct RuleStackT {
	struct RuleStackT *next;
	RuleT *rule;
} RuleStackT;

static bool rule_do_inline_tail_calls     = true;
static bool rule_do_inline_all_basics     = true;
static bool rule_do_inline_singles        = false;
static bool rule_do_inline_non_tail_calls = false;
static bool rule_do_multiple_inlining     = false;

static void
rule_inline_tail_calls_1(RuleT *rule, AltT *alt, RuleT *tail_group)
{
	ItemT *item = alt_item_head(alt);
	ItemT *next;
	RuleT *item_rule;

	while ((next = item_next(item)) != NULL) {
		item = next;
	}

	if (!item_is_rule(item)) {
		return;
	}

	item_rule = entry_get_rule(item_entry(item));
	if (rule_get_tail_group(item_rule) == tail_group
		&& types_equal_names(rule_result(rule), item_result(item))) {
		item_inlinable(item);
		item_tail_call(item);
	}
}

static void
rule_inline_tail_calls(RuleT *rule)
{
	RuleT *tail_group = rule_get_tail_group(rule);
	AltT  *alt;

	alt = rule_get_handler(rule);
	if (alt != NULL) {
		rule_inline_tail_calls_1(rule, alt, tail_group);
	}

	for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
		rule_inline_tail_calls_1(rule, alt, tail_group);
	}
}

static void	rule_compute_call_graph(RuleT *, EntryListT *, RuleStackT *);

static void
rule_compute_call_graph_1(AltT *alt, EntryListT *call_list, RuleStackT *next)
{
	ItemT *item = alt_item_head(alt);
	ItemT *next_item;

	while ((next_item = item_next(item)) != NULL) {
		item = next_item;
	}

	if (item_is_tail_call(item)) {
		EntryT *entry     = item_entry(item);
		RuleT  *item_rule = entry_get_rule(entry);

		rule_compute_call_graph(item_rule, call_list, next);
	}
}

static void
rule_compute_call_graph(RuleT *rule, EntryListT *call_list, RuleStackT *next)
{
	RuleStackT  stack;
	AltT       *alt;

	stack.rule = rule;
	stack.next = next;
	for ( ; next; next = next->next) {
		if (next->rule == rule) {
			entry_list_add_if_missing(call_list, rule_entry(rule));
			return;
		}
	}

	alt = rule_get_handler(rule);
	if (alt != NULL) {
		rule_compute_call_graph_1(alt, call_list, &stack);
	}

	for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
		rule_compute_call_graph_1(alt, call_list, &stack);
	}
}

static void
rule_compute_all_basics_1(RuleT *rule)
{
	AltT *alt;

	if (rule_has_empty_alt(rule) || rule_get_handler(rule) != NULL) {
		return;
	}

	for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
		ItemT *item;

		for (item = alt_item_head(alt); item; item = item_next(item)) {
			if (!item_is_basic(item)) {
				return;
			}
		}
	}

	rule_all_basics(rule);
}

static void	rule_compute_inlining_1(RuleT *);

static void
rule_compute_inlining_2(AltT *alt)
{
	ItemT *item;

	for (item = alt_item_head(alt); item; item = item_next(item)) {
		EntryT *entry;
		RuleT  *item_rule;

		if (!item_is_rule(item) || item_is_tail_call(item)) {
			continue;
		}

		entry     = item_entry(item);
		item_rule = entry_get_rule(entry);

		if (rule_is_all_basics(item_rule)) {
			item_inlinable(item);
		} else if (rule_do_inline_singles && rule_has_one_alt(item_rule)) {
			item_inlinable(item);
		} else if (!rule_do_multiple_inlining) {
			rule_inc_call_count(item_rule);
		}

		if (rule_do_inline_non_tail_calls) {
			item_inlinable(item);
		}

		rule_compute_inlining_1(item_rule);
	}
}

static void
rule_compute_inlining_1(RuleT *rule)
{
	AltT *alt;

	if (rule_is_checked_for_inlining(rule)) {
		return;
	}

	if (rule_is_being_inlined(rule)) {
		return;
	}

	rule_being_inlined(rule);
	alt = rule_get_handler(rule);
	if (alt != NULL) {
		rule_compute_inlining_2(alt);
	}

	for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
		rule_compute_inlining_2(alt);
	}

	rule_checked_for_inlining(rule);
}

static void
rule_compute_needed_functions_2(AltT *alt)
{
	ItemT *item;

	for (item = alt_item_head(alt); item; item = item_next(item)) {
		RuleT *item_rule;

		if (!item_is_rule(item)) {
			continue;
		}

		item_rule = entry_get_rule(item_entry(item));
		if (!item_is_inlinable(item) || rule_get_call_count(item_rule) > 1) {
			rule_will_need_function(item_rule);
		}
	}
}

static void
rule_compute_needed_functions_1(RuleT *rule)
{
	AltT *alt;

	alt = rule_get_handler(rule);
	if (alt != NULL) {
		rule_compute_needed_functions_2(alt);
	}

	for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
		rule_compute_needed_functions_2(alt);
	}
}


/*
 * Externally visible functions
 */

void
rule_handle_tails(RuleT *rule_list)
{
	RuleT *rule;

	for (rule = rule_list; rule; rule = rule_get_next_in_reverse_dfs(rule)) {
		rule_set_tail_group(rule, rule_list);
		rule_no_cycles(rule);
	}

	for (rule = rule_list; rule; rule = rule_get_next_in_reverse_dfs(rule)) {
		rule_inline_tail_calls(rule);
	}

	for (rule = rule_list; rule; rule = rule_get_next_in_reverse_dfs(rule)) {
		rule_compute_call_graph(rule, rule_call_list(rule), NULL);
	}
}

void
rule_compute_all_basics(EntryT *entry, void *gclosure)
{
	UNUSED(gclosure);
	if (rule_do_inline_all_basics && entry_is_rule(entry)) {
		RuleT *rule = entry_get_rule(entry);

		rule_compute_all_basics_1(rule);
	}
}

void
rule_compute_inlining(EntryT *entry, void *gclosure)
{
	RuleT *rule;

	UNUSED(gclosure);
	if (!entry_is_rule(entry)) {
		return;
	}

	rule = entry_get_rule(entry);
	rule_compute_inlining_1(rule);
}

void
rule_compute_needed_functions(EntryT *entry, void *gclosure)
{
	RuleT *rule;

	UNUSED(gclosure);
	if (!entry_is_rule(entry)) {
		return;
	}

	rule = entry_get_rule(entry);
	rule_compute_needed_functions_1(rule);
}

void
rule_handle_need_functions(RuleT *rule_list)
{
	RuleT *rule;

	for (rule = rule_list; rule; rule = rule_get_next_in_reverse_dfs(rule)) {
		rule_will_need_function(rule);
	}
}

bool
rule_get_inline_tail_calls(void)
{
	return rule_do_inline_tail_calls;
}

void
rule_set_inline_tail_calls(bool enable)
{
	rule_do_inline_tail_calls = enable;
}

void
rule_set_inline_all_basics(bool enable)
{
	rule_do_inline_all_basics = enable;
}

void
rule_set_inline_singles(bool enable)
{
	rule_do_inline_singles = enable;
}

void
rule_set_inline_non_tail_calls(bool enable)
{
	if (enable) {
		rule_do_inline_non_tail_calls = true;
	} else {
		rule_do_inline_non_tail_calls = false;
		rule_do_multiple_inlining     = false;
	}
}

void
rule_set_multiple_inlining(bool enable)
{
	if (enable) {
		rule_do_inline_non_tail_calls = true;
		rule_do_multiple_inlining     = true;
	} else {
		rule_do_multiple_inlining     = false;
	}
}
