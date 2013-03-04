/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * rule-factor.c - Factorisation of rules.
 *
 * This file implements the SID factorisation routines.
 *
 * The factorisation process consists of the following phases:
 *
 * 1. The rule is reordered so that alternatives with the same initial item
 * are grouped together, for example the rule:
 *
 * 	A = x A,
 * 	    x B,
 * 	    y A,
 * 	    z A,
 * 	    y B;
 *
 * would be reordered to:
 *
 * 	A = x A,
 * 	    x B,
 * 	    y A,
 * 	    y B,
 * 	    z A;
 *
 * and three groups would have been created:
 *
 * 	x A, x B
 *
 * 	y A, y B
 *
 * 	z A
 *
 * Each group has its first set calculated (this is the union of the first
 * sets of each of the alternatives in the group), and its priority.  The
 * priority of a group is one more than the priority of the rule with the
 * highest priority in any of the group's alternatives, which is not preceded
 * by an action.  If there is no such rule, then the group's priority is one.
 *
 * The rule_group_by_initial_item() function is responsible for this
 * re-ordering.  It uses the rule's alternative tail pointer (alt_tail) to
 * indicate where in the rule it should start the grouping from.  Nothing
 * before this point is modified (it is assumed that it is already grouped).
 * The pointer will always be restored to the end of the alternative list by
 * the time this function returns.
 *
 * 2. Having split the rule up into groups, it then looks at each group to see
 * if there are alternatives of the form:
 *
 * 	B C ...
 *
 * where "B" is a see through rule, and the first set of "B" contains some
 * terminals from the first set of "C ...".  If it finds any, it removes the
 * group from the rule, and expands "B" in all alternatives in the group,
 * putting the new alternatives at the end of the rule.  It also looks for
 * alternatives that begin with a rule which has a predicate in its first set,
 * in which case it also expands the rule in all alternatives in the group.
 * It then recomputes the groups for the new alternatives, and tries again.
 * This phase and the next phase are implemented by the function
 * ``rule_expand_item_clashes''.  It is not possible to expand a rule that has
 * an exception handler into another rule that has an exception handler
 * (unless the exception handlers are identical).
 *
 * 3. The next phase is to check to see if any of the groups have common
 * terminals in their first sets.  If this is the case (and the first item in
 * each alternative in at least one of the groups is a rule), then the group
 * with the highest priority is removed from the rule, and the first item is
 * expanded in all alternatives in the group, putting the new alternatives at
 * the end of the rule.  It then recalculates the groups for the new
 * alternatives, and tries again.
 *
 * 4. The last stage is to change a group of the form:
 *
 * 	  B C
 * 	| B D
 *
 * into
 *
 * 	  B X
 *
 * 	X = C
 * 	  | D
 *
 * where "X" is a newly created rule.  The algorithm actually removes all
 * initial items that are the same for all members of the group.  It also
 * performs renaming of the result names of the final item in the group of
 * identical items if necessary.
 *
 * It is possible that this final stage of the factorization process will go
 * on forever.  To prevent this, there is a limit on the number of new rules
 * that can be created.  This stage of the factorisation process is
 * implemented by the functions rule_factor_2(), rule_factor_3(), and
 * rule_factor_4().
 *
 * When the new rule is created, the ``rule_compute_first_set_1'' function is
 * called to calculate its first set, whether or not it is see through and its
 * priority.  The new rules are created untraced, to ensure that the
 * factorisation process will be applied to them as well.
 */

#include <assert.h>

#include <shared/check.h>
#include <shared/error.h>

#include <exds/bitvec.h>

#include "../adt/rule.h"
#include "../adt/basic.h"
#include "../adt/entry-list.h"
#include "../adt/types.h"

typedef struct AltGroupT {
	struct AltGroupT *next;
	BitVecT           first_set;
	EntryListT        predicate_first;
	unsigned          priority;
	AltT             **alt_ref;
} AltGroupT;

typedef struct AltGroupListT {
	AltGroupT  *head;
	AltGroupT **tail;
} AltGroupListT;

static unsigned rule_factor_limit = 1000;

static unsigned rule_overlaps(ItemT *, BitVecT *, EntryListT *);


static AltGroupT *
group_create(ItemT *item, AltT **alt_ref)
{
	AltGroupT *group = ALLOCATE(AltGroupT);

	group->next = NULL;
	bitvec_init(&group->first_set);
	entry_list_init(&group->predicate_first);
	group->priority = rule_overlaps(item, &group->first_set,
		&group->predicate_first);
	group->alt_ref = alt_ref;

	return group;
}

static AltGroupT *
group_deallocate(AltGroupT *group)
{
	AltGroupT *next = group->next;

	bitvec_destroy(&group->first_set);
	entry_list_destroy(&group->predicate_first);
	DEALLOCATE(group);

	return next;
}

static unsigned
rule_overlaps(ItemT *initial_item, BitVecT *first_set, EntryListT *predicate_first)
{
	unsigned  priority    = 0;
	BoolT     see_through = TRUE;
	BoolT     no_action   = TRUE;
	ItemT    *item;

	for (item = initial_item; see_through && item != NULL;
		item = item_next(item)) {
		switch (item_type(item)) EXHAUSTIVE {
		case ET_PREDICATE:
			assert(item == initial_item);
			entry_list_add_if_missing(predicate_first, item_entry(item));
			see_through = FALSE;
			break;

		case ET_RENAME:
		case ET_ACTION:
			no_action = FALSE;
			break;

		case ET_RULE: {
				EntryT   *entry         = item_entry(item);
				RuleT    *item_rule     = entry_get_rule(entry);
				unsigned  item_priority = rule_get_priority(item_rule);

				bitvec_or(first_set, rule_first_set(item_rule));
				entry_list_append(predicate_first,
				rule_predicate_first(item_rule));
				see_through = rule_is_see_through(item_rule);
				if (item_priority > priority && no_action) {
					priority = item_priority;
				}
			}
			break;

		case ET_BASIC: {
				BasicT *basic = entry_get_basic(item_entry(item));

				see_through = FALSE;
				bitvec_set(first_set, basic_terminal(basic));
			}
			break;

		case ET_NON_LOCAL:
		case ET_NAME:
		case ET_TYPE:
			UNREACHED;
		}
	}

	return priority + 1;
}

static void
rule_group_by_initial_item(RuleT *rule, AltGroupListT *groups)
{
	AltT **alt_ref = rule->alt_tail;
	AltT  *alt;

next_alt:
	while ((alt = *alt_ref) != NULL) {
		ItemT     *item = alt_item_head(alt);
		AltGroupT *group;

		/* This error occurs for p: () -> () = { x(); || $; }; where p is an entry point. */
		if (item == NULL) {
			error(ERROR_FATAL, "the rule '%N' cannot be grouped by initial items as an alt is empty",
				(void *) rule);
		}

		for (group = groups->head; group; group = group->next) {
			AltT  **group_alt_ref = group->alt_ref;
			ItemT  *alt_item      = alt_item_head(*group_alt_ref);

			/* TODO: simplify */
			if ((item_entry(item) == item_entry(alt_item)
					&& types_equal_numbers(item_param(item), item_param(alt_item))
					&& types_equal_numbers(item_result(item), item_result(alt_item)))
				|| (item_is_rename(item) && item_is_rename(alt_item)
					&& types_equal_names(item_param(item), item_param(alt_item))
					&& types_equal_names(item_result(item), item_result(alt_item)))) {
				unsigned priority;

				*alt_ref        = alt_next(alt);
				alt_set_next(alt, *group_alt_ref);
				*group_alt_ref  = alt;
				priority        = rule_overlaps(item, &group->first_set,
					&group->predicate_first);

				if (priority > group->priority) {
					group->priority = priority;
				}

				goto next_alt;
			}
		}

		group         = group_create(item, alt_ref);
		*groups->tail = group;
		groups->tail  = &group->next;
		alt_ref       = alt_next_ref(alt);
	}
	rule->alt_tail = alt_ref;
}

static void rule_factor_1(RuleT *, FactorClosureT *);

static void
rule_expand(RuleT *rule, FactorClosureT *closure, AltGroupT *group,
	AltGroupListT *groups)
{
	AltT        *alt       = *group->alt_ref;
	ItemT       *item      = alt_item_head(alt);
	RuleT       *item_rule = entry_get_rule(item_entry(item));
	AltT        *handler   = rule_get_handler(item_rule);
	AltGroupT  **last;
	AltT       **tail;
	TypeTransT   translator;

	rule_factor_1(item_rule, closure);
	if (handler && !alt_equal(handler, rule_get_handler(rule))) {
		error(ERROR_SERIOUS, "the rule '%N' cannot be expanded into '%N' as the exception handlers don't match",
			(void *) item_rule, (void *) rule);
	}

	if (!non_local_list_is_empty(rule_non_locals(item_rule))) {
		error(ERROR_SERIOUS, "the rule '%N' cannot be expanded into '%N' as it contains non local name definitions",
			(void *) item_rule, (void *) rule);
	}

	for (last = &groups->head; *last != group; last = &(*last)->next) {
		/*NOTHING*/
	}

	*last = group->next;
	if (*last != NULL) {
		*group->alt_ref       = *group->next->alt_ref;
		*group->next->alt_ref = NULL;
		group->next->alt_ref  = group->alt_ref;
	} else {
		groups->tail          = last;
		*group->alt_ref       = NULL;
		rule->alt_tail        = group->alt_ref;
	}

	(void) group_deallocate(group);

	tail = rule->alt_tail;
	while (alt) {
		AltT *item_alt = rule_alt_head(item_rule);
		SaveTransT state;

		trans_init(&translator, rule_param(rule), rule_result(rule), alt);
		trans_add_translations(&translator, rule_param(item_rule),
			item_param(alt_item_head(alt)));
		trans_add_translations(&translator, rule_result(item_rule),
			item_result(alt_item_head(alt)));
		trans_save_state(&translator, &state);

		if (rule_has_empty_alt(item_rule)) {
			AltT *new_alt;

			new_alt = alt_create_merge(NULL, item_next(alt_item_head(alt)),
				&translator, closure->table);

			*tail = new_alt;
			tail  = alt_next_ref(new_alt);
			trans_restore_state(&translator, &state);
		}

		for (; item_alt; item_alt = alt_next(item_alt)) {
			AltT *new_alt;

			new_alt = alt_create_merge(alt_item_head(item_alt),
				item_next(alt_item_head(alt)), &translator, closure->table);

			*tail = new_alt;
			tail = alt_next_ref(new_alt);
			trans_restore_state(&translator, &state);
		}

		trans_destroy(&translator);
		alt = alt_deallocate(alt);
	}
}

static BoolT
rule_expand_item_clashes(RuleT *rule, FactorClosureT *closure,
	AltGroupListT *groups)
{
	BitVecT   *bitvec1 = &closure->bitvec1;
	BitVecT   *bitvec2 = &closure->bitvec2;
	AltGroupT *group;

	for (group = groups->head; group; group = group->next) {
		AltGroupT *group2;
		AltT      *first_alt = *group->alt_ref;
		ItemT     *item      = alt_item_head(first_alt);
		RuleT     *item_rule;

		if (!item_is_rule(item)) {
			continue;
		}

		item_rule = entry_get_rule(item_entry(item));

		if (!entry_list_is_empty(rule_predicate_first(item_rule))) {
			rule_expand(rule, closure, group, groups);

			return TRUE;
		} else if (rule_is_see_through(item_rule)) {
			AltT       *alt = first_alt;
			AltT       *end = NULL;
			EntryListT  predicate_first;

			if (group->next) {
				end = *group->next->alt_ref;
			}
			bitvec_replace(bitvec1, rule_first_set(item_rule));

			do {
				bitvec_empty(bitvec2);
				entry_list_init(&predicate_first);
				(void) rule_overlaps(item_next(alt_item_head(alt)),
					bitvec2, &predicate_first);

				if (bitvec_intersects(bitvec1, bitvec2)
					|| !entry_list_is_empty(&predicate_first)) {
					entry_list_destroy(&predicate_first);
					rule_expand(rule, closure, group, groups);

					return TRUE;
				}

				entry_list_destroy(&predicate_first);
			} while ((alt = alt_next(alt)) != end);
		}

		for (group2 = groups->head; group2; group2 = group2->next) {
			if (group2 != group
				&& bitvec_intersects(&group2->first_set, &group->first_set)) {
				if (group->priority > group2->priority) {
					rule_expand(rule, closure, group, groups);
				} else {
					rule_expand(rule, closure, group2, groups);
				}

				return TRUE;
			}
		}
	}

	return FALSE;
}

static ItemT *
rule_create_factored(TypeTupleT *params, TypeTupleT *result, AltT *alt,
	TableT *table)
{
	static  unsigned factorised_rules = 0;
	EntryT *new_entry;
	ItemT  *new_item;
	RuleT  *new_rule;

	if (factorised_rules == rule_factor_limit) {
		error(ERROR_FATAL, "too many productions (%u) created during factorisation",
			rule_factor_limit);
		UNREACHED;
	}

	factorised_rules++;
	new_entry = table_add_generated_rule(table, FALSE);
	new_rule  = entry_get_rule(new_entry);
	types_copy(rule_param(new_rule), params);
	types_copy(rule_result(new_rule), result);

	while (alt) {
		AltT *tmp_alt = alt;

		alt = alt_next(alt);
		alt_set_next(tmp_alt, NULL);
		if (alt_item_head(tmp_alt)) {
			rule_add_alt(new_rule, tmp_alt);
		} else {
			rule_add_empty_alt(new_rule);
			(void) alt_deallocate(tmp_alt);
		}
	}

	rule_compute_first_set_1(new_rule);
	new_item  = item_create(new_entry);
	types_assign(item_param(new_item), params);
	types_assign(item_result(new_item), result);
	types_make_references(rule_param(new_rule), item_param(new_item));

	return new_item;
}

static BoolT
rule_factor_4(RuleT *rule, AltT *old_alt, AltT *new_alt, TableT *table,
	EntryT *predicate_id, TypeTupleT *params, BoolT *items_equal_ref)
{
	ItemT *old_item     = alt_item_head(old_alt);
	BoolT  result_equal = TRUE;
	AltT  *alt;
	TypeBTransT translator;

	for (alt = alt_next(old_alt); alt; alt = alt_next(alt)) {
		ItemT *item = alt_item_head(alt);

		/* TODO: XOR might read more nicely here! */
		if ((item == NULL && old_item != NULL) || (item != NULL && old_item == NULL)) {
			*items_equal_ref = FALSE;
			return TRUE;
		} else if (item == NULL && old_item == NULL) {
			/*NOTHING*/
		} else if ((item_entry(old_item) == item_entry(item)
				&& types_equal_numbers(item_param(old_item), item_param(item))
				&& types_equal_numbers(item_result(old_item), item_result(item)))
			|| (item_is_rename(item)
				&& item_is_rename(old_item)
				&& types_equal_names(item_param(item), item_param(old_item))
				&& types_equal_names(item_result(item), item_result(old_item)))) {
			/* TODO can we centralise chunks of these expressions? (and elsewhere, too) */

			if (result_equal) {
				result_equal = types_equal_names(item_result(old_item),
					item_result(item));
			}
		} else {
			*items_equal_ref = FALSE;
			return TRUE;
		}
	}

	if (old_item == NULL) {
		*items_equal_ref = FALSE;
		return FALSE;
	}

	btrans_init(&translator);
	for (alt = old_alt; alt; alt = alt_next(alt)) {
		ItemT *item = alt_unlink_item_head(alt);

		if (!result_equal) {
			ItemT *new_item;

			if (alt == old_alt) {
				new_item = btrans_generate_non_pred_names(&translator,
					item_result(item), rule_result(rule), predicate_id, table);
			types_translate(item_result(item), &translator);
			} else {
				new_item = btrans_regen_non_pred_names(&translator,
					item_result(item), rule_result(rule), table);
			}
			item_translate_list(alt_item_head(alt), &translator);
			if (new_item) {
				alt_add_item(alt, new_item);
			}
		}

		if (alt == old_alt) {
			types_add_new_names(params, item_result(item), predicate_id);
			alt_add_item(new_alt, item);
		} else {
			(void) item_deallocate(item);
		}
	}

	btrans_destroy(&translator);
	return TRUE;
}

static void
rule_factor_3(RuleT *rule, TableT *table, EntryT *predicate_id, AltT *old_alt,
	AltT *new_alt)
{
	BoolT       items_equal = TRUE;
	BoolT       found_items;
	TypeTupleT  params;
	TypeTupleT  result;

	types_copy(&params, rule_param(rule));
	types_copy(&result, rule_result(rule));

	do {
		found_items = rule_factor_4(rule, old_alt, new_alt, table,
			predicate_id, &params, &items_equal);
	} while (items_equal);

	if (found_items) {
		ItemT *new_item;

		types_unlink_used(&result, &params);
		types_unlink_unused(&params, old_alt);
		new_item = rule_create_factored(&params, &result, old_alt, table);
		alt_add_item(new_alt, new_item);
		return;
	}

	types_destroy(&params);

	while (old_alt) {
		AltT *tmp_alt = old_alt;

		old_alt = alt_next(old_alt);
		assert(alt_item_head(tmp_alt) == NULL);
		(void) alt_deallocate(tmp_alt);
	}
}

static void
rule_factor_2(RuleT *rule, TableT *table, EntryT *predicate_id,
	AltGroupListT *groups)
{
	AltGroupT *group;

	for (group = groups->head; group; group = group_deallocate(group)) {
		AltT *alt = *group->alt_ref;
		AltT *new_alt;

		if (group->next) {
			if (group->next->alt_ref == alt_next_ref(*group->alt_ref)) {
				goto done;
			}

			new_alt = alt_create();
			alt_set_next(new_alt, *group->next->alt_ref);
			*group->next->alt_ref = NULL;
			group->next->alt_ref    = alt_next_ref(new_alt);
		} else {
			if (alt_next(*group->alt_ref) == NULL) {
				goto done;
			}
			new_alt        = alt_create();
			rule->alt_tail = alt_next_ref(new_alt);
		}

		*group->alt_ref = new_alt;
		rule_factor_3(rule, table, predicate_id, alt, new_alt);
done:
		;
	}
}

static void
rule_factor_1(RuleT *rule, FactorClosureT *closure)
{
	AltGroupListT groups;

	groups.head = NULL;
	groups.tail = &groups.head;
	if (rule_is_factored(rule)) {
		return;
	}

	rule_factored(rule);
	rule->alt_tail = &rule->alt_head;

	do {
		rule_renumber(rule, FALSE, closure->predicate_id);
		rule_group_by_initial_item(rule, &groups);
	} while (rule_expand_item_clashes(rule, closure, &groups));

	rule_factor_2(rule, closure->table, closure->predicate_id, &groups);
}


/*
 * Externally visible functions
 */

void
rule_factor(EntryT *entry, void *gclosure)
{
	FactorClosureT *closure = gclosure;

	if (entry_is_rule(entry)) {
		RuleT *rule = entry_get_rule(entry);

		rule_factor_1(rule, closure);
	}
}

void
rule_set_factor_limit(unsigned limit)
{
	rule_factor_limit = limit;
}
