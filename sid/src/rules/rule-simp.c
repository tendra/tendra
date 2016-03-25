/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * rule-simp.c - Rule simplification routines.
 *
 * This file implements the SID elimination of identical rules routines.
 *
 * In order to optimise the elimination of identical rules the following is
 * done:
 *
 * 	- name flow through each rule is numbered, so that differences in
 *	  names do not affect the comparisons;
 *
 *	- alternatives are reordered so that they will appear in the same
 *	  order in identical rules;
 *
 *	- rules are placed in a hash table, so that identical rules will be in
 *	  the same slot in the table.
 *
 * The first two of these make comparisons between two rules quicker.  The
 * third reduces the number of comparisons that are made.
 *
 * One important thing to remember is that the hash value of a rule should not
 * depend upon the names of any rules that it calls.  If this was the case,
 * and one of the rules was replaced then it would be possible to have two
 * identical rules in different slots in the hash table!
 *
 * If two identical rules are found, one is substituted for the other.  If
 * one of the rules is a required rule, then it becomes the used rule.
 */

#include <shared/bool.h>

#include "../adt/rule.h"
#include "../adt/action.h"
#include "../adt/basic.h"
#include "../adt/entry-list.h"
#include "../adt/name.h"
#include "../adt/type.h"

#define EQUALITY_TABLE_SIZE	(127)

typedef struct RuleSortListT {
	AltT  *head;
	AltT **tail;
} RuleSortListT;

typedef struct ReplaceClosureT {
	EntryT *from;
	EntryT *to;
} ReplaceClosureT;

static RuleT *equality_table[EQUALITY_TABLE_SIZE];

static void
rule_sort_alts(RuleSortListT *sort_list)
{
	AltT *alt      = sort_list->head;
	AltT *scan_alt = alt_next(alt);
	RuleSortListT lower;
	RuleSortListT higher;

	if (!scan_alt) {
		return;
	}

	lower.tail  = &lower.head;
	higher.tail = &higher.head;
	for (; scan_alt; scan_alt = alt_next(scan_alt)) {
		if (alt_less_than(scan_alt, alt)) {
			*lower.tail = scan_alt;
			lower.tail  = alt_next_ref(scan_alt);
		} else {
			*higher.tail = scan_alt;
			higher.tail  = alt_next_ref(scan_alt);
		}
	}
	*lower.tail  = NULL;
	*higher.tail = NULL;

	if (lower.head) {
		rule_sort_alts(&lower);
		sort_list->head = lower.head;
		sort_list->tail = lower.tail;
	} else {
		sort_list->tail = &sort_list->head;
	}
	*sort_list->tail = alt;
	sort_list->tail  = alt_next_ref(alt);

	if (higher.head) {
		rule_sort_alts(&higher);
		*sort_list->tail = higher.head;
		sort_list->tail  = higher.tail;
	}
	*sort_list->tail = NULL;
}

static void
rule_reorder(RuleT *rule)
{
	RuleSortListT sort_list;

	sort_list.head = rule_alt_head(rule);
	if (sort_list.head  == NULL) {
		return;
	}

	sort_list.tail = rule->alt_tail;
	rule_sort_alts(&sort_list);
	rule->alt_head = sort_list.head;
	rule->alt_tail = sort_list.tail;
}

static void
rule_hash_1(RuleT *rule, EntryT *predicate_id)
{
	unsigned  hash_value = rule_has_empty_alt(rule) ? 3 : 0;
	AltT     *alt;

	rule_renumber(rule, true, predicate_id);
	rule_reorder(rule);

	for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
		ItemT *item;
		KeyT  *key = NULL;

		hash_value += 5;
		for (item = alt_item_head(alt); item; item = item_next(item)) {
			hash_value++;
			if (!item_is_rule(item)) {
				key = entry_key(item_entry(item));
			}
		}

		if (key) {
			hash_value += key_hash_value(key);
		}
	}

	hash_value %= EQUALITY_TABLE_SIZE;
	rule_set_next_in_table(rule, equality_table[hash_value]);
	equality_table[hash_value] = rule;
}

static void
rule_hash_for_comparison(EntryT *entry, void *gclosure)
{
	RuleT  *rule;
	EntryT *predicate_id = gclosure;

	if (!entry_is_rule(entry)) {
		return;
	}

	rule         = entry_get_rule(entry);
	rule_hash_1(rule, predicate_id);
}

static bool
rule_equal(RuleT *rule1, RuleT *rule2)
{
	AltT *alt1;
	AltT *alt2;

	if (!types_equal_numbers(rule_param(rule1), rule_param(rule2))
		|| !types_equal_numbers(rule_result(rule1), rule_result(rule2))
		|| rule_has_empty_alt(rule1) != rule_has_empty_alt(rule2)
		|| !alt_equal(rule_get_handler(rule1), rule_get_handler(rule2))
		|| !non_local_list_is_empty(rule_non_locals(rule1))
		|| !non_local_list_is_empty(rule_non_locals(rule2))) {
		return false;
	}

	for (alt1 = rule_alt_head(rule1), alt2 = rule_alt_head(rule2);
		alt1 && alt2; alt1 = alt_next(alt1), alt2 = alt_next(alt2)) {
		ItemT *item1;
		ItemT *item2;

		for (item1 = alt_item_head(alt1), item2 = alt_item_head(alt2);
			item1 && item2; item1 = item_next(item1), item2 = item_next(item2)) {
			if (item_entry(item1) != item_entry(item2)
				|| !types_equal_numbers(item_param(item1), item_param(item2))
				|| !types_equal_numbers(item_result(item1), item_result(item2))) {
				return false;
			}
		}

		if (item1 || item2) {
			return false;
		}
	}

	if (alt1 || alt2) {
		return false;
	}

	return true;
}

static bool
rule_do_replacements_1(AltT *alt, ReplaceClosureT *closure)
{
	bool changed = false;
	ItemT *item;

	for (item = alt_item_head(alt); item; item = item_next(item)) {
		if (item_entry(item) == closure->from) {
			item_set_entry(item, closure->to);
			changed = true;
		}
	}

	return changed;
}

static void
rule_do_replacements(EntryT *entry, void *gclosure)
{
	ReplaceClosureT *closure = gclosure;
	RuleT *rule;
	bool  changed;
	AltT  *alt;

	if (!entry_is_rule(entry)) {
		return;
	}

	changed = false;
	rule = entry_get_rule(entry);
	alt = rule_get_handler(rule);
	if (alt != NULL) {
		if (rule_do_replacements_1(alt, closure)) {
			changed = true;
		}
	}

	for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
		if (rule_do_replacements_1(alt, closure)) {
			changed = true;
		}
	}

	if (changed) {
		rule_reorder(rule);
	}
}

static bool
rule_remove_duplicates_1(RuleT **rule_ref, TableT *table)
{
	bool  did_remove = false;
	RuleT *rule;

	while ((rule = *rule_ref) != NULL) {
		RuleT **inner_rule_ref = rule_get_next_in_table_ref(rule);
		RuleT  *inner_rule;

		while ((inner_rule = *inner_rule_ref) != NULL) {
			ReplaceClosureT closure;

			if (!rule_equal(rule, inner_rule)) {
				inner_rule_ref = rule_get_next_in_table_ref(inner_rule);
				continue;
			}

			if (rule_is_required(inner_rule)) {
				closure.from = rule_entry(rule);
				closure.to   = rule_entry(inner_rule);
				*rule_ref    = rule_get_next_in_table(rule);
			} else {
				closure.from    = rule_entry(inner_rule);
				closure.to      = rule_entry(rule);
				*inner_rule_ref = rule_get_next_in_table(inner_rule);
			}

			table_iter(table, rule_do_replacements, &closure);
			did_remove = true;
			if (rule != *rule_ref) {
				goto removed_rule;
			}
		}
		rule_ref = rule_get_next_in_table_ref(rule);

removed_rule:
		;
	}

	return did_remove;
}


/*
 * Externally visible functions
 */

void
rule_remove_duplicates(TableT *table, EntryT *predicate_id)
{
	bool    did_remove;
	unsigned i;

	for (i = 0; i < EQUALITY_TABLE_SIZE; i++) {
		equality_table[i] = NULL;
	}

	table_iter(table, rule_hash_for_comparison, predicate_id);
	do {
		did_remove = false;
		for (i = 0; i < EQUALITY_TABLE_SIZE; i++) {
			if (rule_remove_duplicates_1(&equality_table[i], table)) {
				did_remove = true;
			}
		}
	} while (did_remove);
}
