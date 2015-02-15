/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * rule-lre.c - Left recursion elimination routines.
 *
 * This file implements the SID left recursion elimination routines.
 *
 * The generic cycle detection functions defined in the file ``rule.c'' are
 * used to find left cycles in the grammar (this is done by the function
 * grammar_remove_left_recursion() in the file "grammar.c").  If the
 * functions find any such cycles, the function ``rule_remove_left_cycle'' is
 * called on the group of productions to remove the left recursion.  Left
 * recursion is transformed into right recursion in the manner described
 * below.
 *
 * Given a set of productions, expressed as
 *
 *	Ai = Aj Bji, Ci;
 *
 * this can be transformed into
 *
 *	Ai  = Cj Xji;
 *	Xij = Yij, Bik Xkj;
 *
 * Where the rules "Xij" are generated automatically, and Yij is the identity
 * operation if i = j, or an error otherwise.  The generated rule has the same
 * parameters and results, which are the results of "Ai" augmented with those
 * parameters of "Ai" that are used by "Bji".
 *
 * In order for the transform to work, all of the "Ai" must have the same
 * parameter and result types, and the same exception handler.  Also, the
 * initial call to "Aj" must take exactly the formals of "Ai" as parameters.
 * This is checked by the ``rule_check_cycle_types'' function, which also
 * ensures that names are consistent throughout all of the rules.  The
 * transform is performed by the function ``rule_left_cycle_general_case''.
 *
 * In addition to the general case, two special cases are looked for.  The
 * first of these transforms:
 *
 *	A = A B, $;
 *
 * into
 *
 *	A = B A, $;
 *
 * whilst the second transforms:
 *
 *	A = A C B, B;
 *
 * into
 *
 *	A = B X;
 *	X = C A;
 *
 * These special cases are handled by the ``rule_left_cycle_special_case''
 * function.
 */

#include <assert.h>

#include <shared/check.h>
#include <shared/error.h>

#include <exds/dstring.h>

#include "../adt/rule.h"

typedef struct MatrixEntryT {
	AltT        *alt;
	BoolT        inited;
	TypeTupleT   param;
} MatrixEntryT;

typedef struct VectorEntryT {
	BoolT       empty_alt;
	AltT       *alt;
	BoolT       inited;
	TypeTupleT  param;
} VectorEntryT;

static MatrixEntryT *
rule_left_cycle_matrix(unsigned size)
{
	static MatrixEntryT *array      = NULL;
	static unsigned      array_size = 0;
	unsigned             i;

	if (size > array_size) {
		DEALLOCATE(array);
		array      = ALLOCATE_VECTOR(MatrixEntryT, size);
		array_size = size;
	}

	for (i = 0; i < size; i++) {
		array[i].alt    = NULL;
		array[i].inited = FALSE;
	}

	return array;
}

static VectorEntryT *
rule_left_cycle_vector(unsigned size)
{
	static VectorEntryT *array      = NULL;
	static unsigned      array_size = 0;
	unsigned             i;

	if (size > array_size) {
		DEALLOCATE(array);
		array      = ALLOCATE_VECTOR(VectorEntryT, size);
		array_size = size;
	}

	for (i = 0; i < size; i++) {
		array[i].empty_alt = FALSE;
		array[i].alt       = NULL;
		array[i].inited    = FALSE;
	}

	return array;
}

static void
rule_destroy_cycle_matrix(MatrixEntryT *matrix, unsigned size)
{
	unsigned i;

	for (i = 0; i < size; i++) {
		AltT *alt;

		if (!matrix[i].inited) {
			continue;
		}

		alt = matrix[i].alt;
		while (alt) {
			alt = alt_deallocate(alt);
		}

		types_destroy(&matrix[i].param);
	}
}

static void
rule_destroy_cycle_vector(VectorEntryT *vector, unsigned size)
{
	unsigned i;

	for (i = 0; i < size; i++) {
		AltT *alt;

		if (!vector[i].inited) {
			continue;
		}

		alt = vector[i].alt;
		while (alt) {
			alt = alt_deallocate(alt);
		}

		types_destroy(&vector[i].param);
	}
}

static ItemT *
rule_find_suffix(ItemT *rec_item, ItemT *non_rec_item)
{
	ItemT *tmp_rec_item     = rec_item;
	ItemT *tmp_non_rec_item = non_rec_item;
	unsigned diff           = 0;

	while (tmp_rec_item && tmp_non_rec_item) {
		tmp_rec_item     = item_next(tmp_rec_item);
		tmp_non_rec_item = item_next(tmp_non_rec_item);
	}

	while (tmp_rec_item) {
		diff++;
		tmp_rec_item = item_next(tmp_rec_item);
	}

	if (diff == 0) {
		return NULL;
	}

	do {
		rec_item = item_next(rec_item);
	} while (--diff);

	tmp_rec_item = rec_item;
	tmp_non_rec_item = non_rec_item;
	while (tmp_rec_item && tmp_non_rec_item) {
		if (item_entry(tmp_rec_item) != item_entry(tmp_non_rec_item)) {
			return NULL;
		}

		tmp_rec_item     = item_next(tmp_rec_item);
		tmp_non_rec_item = item_next(tmp_non_rec_item);
	}

	assert(tmp_rec_item == NULL && tmp_non_rec_item == NULL);

	return rec_item;
}

static void
rule_renumber_item_list(ItemT *item, TypeNTransT *translator)
{
	ntrans_init(translator);
	for (; item; item = item_next(item)) {
		types_renumber(item_param(item), translator);
		types_renumber(item_result(item), translator);
	}
}

static BoolT
rule_compare_item_lists(ItemT *rec_suffix, ItemT *non_rec_item)
{
	for ( ; rec_suffix;
		rec_suffix = item_next(rec_suffix), non_rec_item = item_next(non_rec_item)) {

		assert(non_rec_item);
		if (!types_equal_numbers(item_param(rec_suffix), item_param(non_rec_item))
			|| !types_equal_numbers(item_result(rec_suffix), item_result(non_rec_item))) {
			return FALSE;
		}
	}
	assert(non_rec_item == NULL);

	return TRUE;
}

static void
rule_left_cycle_special_case_2(RuleT *rule, TableT *table, AltT *non_rec_alt,
	AltT *rec_alt, TypeTupleT *param, ItemT *rec_suffix)
{
	EntryT      *entry    = table_add_generated_rule(table, TRUE);
	RuleT       *new_rule = entry_get_rule(entry);
	ItemT       *new_item = item_create(entry);
	ItemT       *rec_item = alt_unlink_item_head(rec_alt);
	AltT        *new_alt  = alt_create();
	AltT        *handler;
	ItemT       *item;
	TypeBTransT  tmp_trans;
	TypeTupleT   result;

	rule_reinit(rule);
	alt_set_next(non_rec_alt, NULL);
	btrans_init(&tmp_trans);
	types_copy(&result, rule_result(rule));
	btrans_generate_names(&tmp_trans, &result, table);
	types_translate(&result, &tmp_trans);

	handler = rule_get_handler(rule);
	if (handler != NULL) {
		ItemT *handler_items = alt_item_head(handler);

		item_translate_list(handler_items, &tmp_trans);
	}

	btrans_destroy(&tmp_trans);
	types_assign(item_param(new_item), rule_result(rule));
	types_copy(item_result(new_item), &result);
	types_copy(rule_result(rule), &result);
	alt_add_item(non_rec_alt, new_item);
	rule_add_alt(rule, non_rec_alt);
	types_copy(rule_param(new_rule), item_result(rec_item));
	types_copy(rule_result(new_rule), &result);
	IGNORE item_deallocate(rec_item);

	while (item = alt_item_head(rec_alt), item != rec_suffix) {
		alt_add_item(new_alt, alt_unlink_item_head(rec_alt));
	}
	IGNORE alt_deallocate(rec_alt);

	new_item = item_create(rule_entry(rule));
	if (param) {
		types_assign(item_param(new_item), param);
	} else {
		types_copy(item_param(new_item), rule_param(new_rule));
	}

	types_assign(item_result(new_item), &result);
	alt_add_item(new_alt, new_item);
	rule_add_alt(new_rule, new_alt);

	if (types_equal_zero_tuple(rule_param(new_rule))) {
		rule_add_empty_alt(new_rule);
		return;
	}

	new_alt = alt_create();
	new_item = item_create(table_add_rename(table));
	types_copy(item_param(new_item), rule_param(new_rule));
	types_copy(item_result(new_item), rule_result(new_rule));
	alt_add_item(new_alt, new_item);
	rule_add_alt(new_rule, new_alt);
}

static BoolT
rule_left_cycle_special_case_1(RuleT * rule, TableT * table)
{
	AltT        *rec_alt = rule_alt_head(rule);
	AltT        *non_rec_alt;
	ItemT       *rec_item;
	ItemT       *rec_next;
	ItemT       *rec_suffix;
	ItemT       *non_rec_item;
	TypeTupleT   param;
	TypeNTransT  rec_translator;
	TypeNTransT  non_rec_translator;

	non_rec_alt = alt_next(rec_alt);
	if (non_rec_alt == NULL || alt_next(non_rec_alt)) {
		return FALSE;
	}

	if (item_is_rule(non_rec_item = alt_item_head(non_rec_alt))
		&& entry_get_rule(item_entry(non_rec_item)) == rule) {

		non_rec_alt  = rec_alt;
		rec_alt      = alt_next(rec_alt);
		non_rec_item = alt_item_head(non_rec_alt);
	}

	if (item_is_rule(non_rec_item) &&
		entry_get_rule(item_entry(non_rec_item)) == rule) {
		return FALSE;
	}

	rec_item = alt_item_head(rec_alt);
	if (!types_equal_names(rule_param(rule), item_param(rec_item))
		|| !types_equal(rule_param(rule), rule_result(rule))) {
		return FALSE;
	}

	rec_next = item_next(rec_item);
	if (item_names_used_in_list(rec_next, rule_param(rule))) {
		return FALSE;
	}

	rec_suffix = rule_find_suffix(rec_item, non_rec_item);
	if (rec_suffix == NULL) {
		return FALSE;
	}

	if (rec_suffix != rec_next && item_names_used_in_list(rec_suffix, item_result(rec_item))) {
		return FALSE;
	}

	rule_renumber_item_list(non_rec_item, &non_rec_translator);
	rule_renumber_item_list(rec_suffix, &rec_translator);
	if (!rule_compare_item_lists(rec_suffix, non_rec_item)) {
		ntrans_destroy(&non_rec_translator);
		ntrans_destroy(&rec_translator);
		return FALSE;
	}

	if (rec_suffix == rec_next) {
		ntrans_destroy(&non_rec_translator);
		ntrans_destroy(&rec_translator);
		rule_left_cycle_special_case_2(rule, table, non_rec_alt, rec_alt,
			NULL, rec_suffix);
	} else {
		types_compute_param_from_trans(&param, &non_rec_translator,
			&rec_translator, rule_param(rule));
		ntrans_destroy(&non_rec_translator);
		ntrans_destroy(&rec_translator);
		rule_left_cycle_special_case_2(rule, table, non_rec_alt, rec_alt,
			&param, rec_suffix);
	}

	return TRUE;
}

static BoolT
rule_left_cycle_special_case(RuleT *rule, TableT *table)
{
	AltT  *alt;
	ItemT *item;

	if (!rule_has_empty_alt(rule)) {
		return rule_left_cycle_special_case_1(rule, table);
	}

	alt = rule_alt_head(rule);
	if (alt == NULL || alt_next(alt) != NULL) {
		return FALSE;
	}

	item = alt_unlink_item_head(alt);
	alt_add_item(alt, item);

	return TRUE;
}

static BoolT
rule_check_non_locals(RuleT *this_rule, RuleT *rule_list, unsigned real_size)
{
	NStringT *scope  = rule_maximum_scope(this_rule);
	unsigned  length = nstring_length(scope);
	RuleT    *rule;

	for (rule = rule_list; rule; rule = rule_get_next_in_reverse_dfs(rule)) {
		KeyT *key = entry_key(rule_entry(rule));

		if (rule != this_rule && key_is_string(key)) {
			NStringT *string = key_get_string(key);

			if (nstring_is_prefix(string, scope)) {
				continue;
			}

			if (!nstring_is_prefix(scope, string)
				|| !nstring_length(string) + 2 == length) {

				error(ERR_SERIOUS, "a non local name in the rule '%N' is not "
					"in scope in the rule '%N' in the left recursive cycle "
					"involving the following productions:\n%P",
					(void *) this_rule, (void *) rule, (void *) rule_list);

				return FALSE;
			}
		}
	}

	if (non_local_list_is_empty(rule_non_locals(this_rule)) || real_size == 1) {
		return TRUE;
	}

	error(ERR_SERIOUS, "the rule '%N' declares non local names in the left "
		"recursive cycle with more than one entry point involving the "
		"following productions:\n%P", (void *) this_rule, (void *) rule_list);

	return FALSE;
}

static BoolT
rule_check_alt_cycle_types(RuleT *rule, RuleT *rule_list, AltT *alt,
	BoolT need_check, TypeBTransT *translator1, TypeBTransT *translator2,
	TableT *table, BoolT *generate_ref)
{
	ItemT *item = alt_item_head(alt);
	RuleT *item_rule;
	TypeTupleT result_intersect;

	item_translate_list(item, translator1);
	if (!item_is_rule(item)) {
		return TRUE;
	}

	item_rule = entry_get_rule(item_entry(item));
	if (rule_get_cycle_index(item_rule) == 0) {
		return TRUE;
	}

	if (need_check && !types_equal_names(rule_param(rule), item_param(item))) {
		btrans_destroy(translator1);
		btrans_destroy(translator2);

		error(ERR_SERIOUS, "the argument names of the left recursive calls "
			"in the following productions do not match:\n%P",
			(void *) rule_list);

		return FALSE;
	}

	/*
	 * If a result identifier is returned by the left recursive call, it is
	 * necessary to rename that return value, and use an identity afterwards to
	 * rename it.
	 */
	types_init(&result_intersect);
	types_compute_intersection(&result_intersect, rule_result(rule),
		item_result(item));

	if (!types_equal_zero_tuple(&result_intersect)) {
		EntryT      *new_entry = table_add_rename(table);
		ItemT       *new_item  = item_create(new_entry);
		TypeBTransT  tmp_trans;
		TypeTupleT   tmp_tuple;

		btrans_init(&tmp_trans);
		types_copy(&tmp_tuple, &result_intersect);
		btrans_generate_names(&tmp_trans, &tmp_tuple, table);
		types_translate(&tmp_tuple, &tmp_trans);
		types_translate(item_result(item), &tmp_trans);
		btrans_destroy(&tmp_trans);
		types_assign(item_param(new_item), &tmp_tuple);
		types_assign(item_result(new_item), &result_intersect);
		item_set_next(new_item, item_next(item));
		item_set_next(item, new_item);
	} else {
		types_destroy(&result_intersect);
	}

	if (*generate_ref) {
		btrans_generate_names(translator2, item_result(item), table);
		*generate_ref = FALSE;
	} else {
		btrans_regenerate_names(translator2, item_result(item));
	}

	types_translate(item_result(item), translator2);
	item_translate_list(item_next(item), translator2);

	return TRUE;
}

static BoolT
rule_check_cycle_types(RuleT *rule_list, EntryT *predicate_id,
	unsigned real_size, TableT *table)
{
	TypeTupleT  *param    = rule_param(rule_list);
	TypeTupleT  *result   = rule_result(rule_list);
	AltT        *handler  = rule_get_handler(rule_list);
	BoolT        generate = TRUE;
	RuleT       *rule;
	TypeBTransT  translator1;
	TypeBTransT  translator2;

	rule_renumber(rule_list, TRUE, predicate_id);
	if (!rule_check_non_locals(rule_list, rule_list, real_size)) {
		return FALSE;
	}

	for (rule = rule_get_next_in_reverse_dfs(rule_list); rule;
		rule = rule_get_next_in_reverse_dfs(rule)) {
		if (!types_equal(param, rule_param(rule))
			|| !types_equal(result, rule_result(rule))) {
			error(ERR_SERIOUS, "the parameter or result types of the left "
				"recursive calls in the following productions do not match:\n%P",
				(void *) rule_list);
			return FALSE;
		}

		rule_renumber(rule, TRUE, predicate_id);
		if (!alt_equal(handler, rule_get_handler(rule))) {
			error(ERR_SERIOUS, "the exception handlers in the left recursion "
				"involving the following productions do not match:\n%P",
				(void *) rule_list);
			return FALSE;
		}

		if (!rule_check_non_locals(rule, rule_list, real_size)) {
			return FALSE;
		}
	}

	btrans_init(&translator1);
	btrans_init(&translator2);
	for (rule = rule_list; rule; rule = rule_get_next_in_reverse_dfs(rule)) {
		AltT *alt;

		if (rule == rule_list) {
			btrans_generate_names(&translator1, rule_param(rule), table);
		} else {
			btrans_regenerate_names(&translator1, rule_param(rule));
		}
		types_translate(rule_param(rule), &translator1);

		alt = rule_get_handler(rule);
		if (alt != NULL) {
			IGNORE rule_check_alt_cycle_types(rule, rule_list, alt, FALSE,
				&translator1, &translator2, table, &generate);
		}

		for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
			if (!rule_check_alt_cycle_types(rule, rule_list, alt, TRUE,
				&translator1, &translator2, table, &generate)) {
				return FALSE;
			}
		}
	}

	btrans_destroy(&translator1);
	btrans_destroy(&translator2);

	return TRUE;
}

static void
rule_compute_param_subset(RuleT *rule_list, TypeTupleT *subset)
{
	RuleT *rule;

	types_init(subset);
	for (rule = rule_list; rule; rule = rule_get_next_in_reverse_dfs(rule)) {
		TypeTupleT *param = rule_param(rule);
		AltT       *alt;

		for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
			ItemT *item = alt_item_head(alt);
			RuleT *item_rule;

			if (!item_is_rule(item)) {
				continue;
			}

			item_rule = entry_get_rule(item_entry(item));

			if (rule_get_cycle_index(item_rule) == 0) {
				continue;
			}

			for (item = item_next(item); item; item = item_next(item)) {
				types_compute_intersection(subset, param, item_param(item));
			}
		}
	}
}

static void
rule_left_cycle_general_case_1(RuleT *rule_list, unsigned size,
	MatrixEntryT *matrix, VectorEntryT *vector, TableT *table,
	TypeTupleT *gen_param, TypeTupleT *gen_result)
{
	unsigned     i               = 0;
	BoolT        generate        = TRUE;
	BoolT        generate_param  = TRUE;
	BoolT        generate_result = TRUE;
	RuleT       *rule;
	TypeBTransT  translator;
	TypeBTransT  tmp_trans;
	TypeTupleT   dummy;
	TypeTupleT   param_subset;

	btrans_init(&translator);
	rule_compute_param_subset(rule_list, &param_subset);
	btrans_init(&tmp_trans);
	types_copy(&dummy, &param_subset);
	btrans_generate_names(&tmp_trans, &dummy, table);
	types_translate(&dummy, &tmp_trans);
	btrans_destroy(&tmp_trans);

	for (rule = rule_list; rule;
		rule = rule_get_next_in_reverse_dfs(rule), i++) {
		AltT       *alt = rule_alt_head(rule);
		AltT       *handler;
		TypeTupleT  old_result;

		types_copy(&old_result, rule_result(rule));
		if (generate) {
			btrans_generate_names(&translator, rule_result(rule), table);
			generate = FALSE;
		} else {
			btrans_regenerate_names(&translator, rule_result(rule));
		}

		types_translate(rule_result(rule), &translator);
		if ((handler = rule_get_handler(rule)) != NULL) {
			ItemT *handler_items = alt_item_head(handler);

			item_translate_list(handler_items, &translator);
		}

		if (rule_has_empty_alt(rule)) {
			vector[i].empty_alt = TRUE;
		}

		while (alt) {
			ItemT    *item    = alt_item_head(alt);
			AltT     *tmp_alt = alt;
			RuleT    *item_rule;
			unsigned item_index;

			alt = alt_next(alt);
			if (item_is_rule(item)) {
				item_rule = entry_get_rule(item_entry(item));
				item_index = rule_get_cycle_index(item_rule);

				if (item_index != 0) {
					unsigned matrix_index = size * (item_index - 1) + i;

					if (!matrix[matrix_index].inited) {
						TypeTupleT *param = &matrix[matrix_index].param;

						types_copy(param, &param_subset);
						types_append_copy(param, &old_result);
						matrix[matrix_index].inited = TRUE;
					}

					if (generate_param) {
						ItemT *item_head = alt_item_head(tmp_alt);

						types_copy(gen_param, &param_subset);
						types_append_copy(gen_param, item_result(item_head));
						generate_param = FALSE;
					}

					IGNORE item_deallocate(alt_unlink_item_head(tmp_alt));
					alt_set_next(tmp_alt, matrix[matrix_index].alt);
					matrix[matrix_index].alt = tmp_alt;
					continue;
				}
			}

			if (!vector[i].inited) {
				TypeTupleT *param = &vector[i].param;

				types_copy(param, &param_subset);
				types_append_copy(param, &old_result);
				vector[i].inited = TRUE;
			}

			if (generate_result) {
				types_copy(gen_result, &dummy);
				types_append_copy(gen_result, rule_result(rule));
				generate_result = FALSE;
			}

			alt_set_next(tmp_alt, vector[i].alt);
			vector[i].alt = tmp_alt;
		}

		rule_reinit(rule);
		types_destroy(&old_result);
	}

	types_destroy(&param_subset);
	btrans_destroy(&translator);
}

static BoolT
rule_left_cycle_general_case_2(RuleT *rule_list, unsigned size,
	VectorEntryT *vector)
{
	BoolT    not_found = TRUE;
	unsigned i;

	for (i = 0; i < size; i++) {
		if (vector[i].empty_alt || vector[i].alt) {
			not_found = FALSE;
		}
	}

	if (not_found) {
		error(ERR_SERIOUS, "no cycle termination for the left recursive set "
			"involving the following rules: %W", (void *) rule_list);

		return FALSE;
	}

	return TRUE;
}

static void
rule_left_cycle_general_case_3(RuleT *rule, unsigned size, VectorEntryT *vector,
	TableT *table, RuleT **new_rule_list_tail, TypeTupleT *param,
	TypeTupleT *result)
{
	unsigned j;

	for (j = 0; j < size; j++) {
		EntryT *entry    = table_add_generated_rule(table, TRUE);
		RuleT  *new_rule = entry_get_rule(entry);
		AltT   *alt;

		types_copy(rule_param(new_rule), param);
		types_copy(rule_result(new_rule), result);
		*new_rule_list_tail = new_rule;
		new_rule_list_tail  = rule_next_in_reverse_dfs_ref(new_rule);

		if (vector[j].empty_alt) {
			AltT  *new_alt  = alt_create();
			ItemT *new_item = item_create(entry);

			types_copy(item_param(new_item), &vector[j].param);
			types_copy(item_result(new_item), result);
			alt_add_item(new_alt, new_item);
			rule_add_alt(rule, new_alt);
		}

		for (alt = vector[j].alt; alt; alt = alt_next(alt)) {
			AltT  *new_alt  = alt_duplicate(alt);
			ItemT *new_item = item_create(entry);

			types_copy(item_param(new_item), &vector[j].param);
			types_copy(item_result(new_item), result);
			alt_add_item(new_alt, new_item);
			rule_add_alt(rule, new_alt);
		}
	}
}

static void
rule_left_cycle_general_case_4(RuleT *new_rule_list, unsigned i, unsigned size,
	MatrixEntryT *matrix, TableT *table)
{
	unsigned  j;
	RuleT    *rule;

	for (rule = new_rule_list, j = 0; j < size;
		rule = rule_get_next_in_reverse_dfs(rule), j++) {
		RuleT    *inner_rule;
		unsigned  k = 0;

		if (i == j) {
			if (types_equal_zero_tuple(rule_param(rule))) {
				rule_add_empty_alt(rule);
			} else {
				AltT   *new_alt  = alt_create();
				EntryT *entry    = table_add_rename(table);
				ItemT  *new_item = item_create(entry);

				types_copy(item_param(new_item), rule_param(rule));
				types_copy(item_result(new_item), rule_result(rule));
				alt_add_item(new_alt, new_item);
				rule_add_alt(rule, new_alt);
			}
		}

		for (inner_rule = new_rule_list; inner_rule;
			inner_rule = rule_get_next_in_reverse_dfs(inner_rule), k++) {
			AltT *alt;

			for (alt = matrix[k].alt; alt; alt = alt_next(alt)) {
				AltT  *new_alt  = alt_duplicate(alt);
				ItemT *new_item = item_create(rule_entry(inner_rule));

				types_copy(item_param(new_item), &matrix[k].param);
				types_copy(item_result(new_item), rule_result(rule));
				alt_add_item(new_alt, new_item);
				rule_add_alt(rule, new_alt);
			}
		}
	}
}

static void
rule_left_cycle_general_case(RuleT *rule_list, unsigned size, TableT *table)
{
	unsigned      matrix_size = size * size;
	MatrixEntryT *matrix      = rule_left_cycle_matrix(matrix_size);
	VectorEntryT *vector      = rule_left_cycle_vector(size);
	TypeTupleT    param;
	TypeTupleT    result;

	rule_left_cycle_general_case_1(rule_list, size, matrix, vector, table,
		&param, &result);
	if (rule_left_cycle_general_case_2(rule_list, size, vector)) {
		unsigned  i = 0;
		RuleT    *rule;

		for (rule = rule_list; rule;
			rule = rule_get_next_in_reverse_dfs(rule), i++) {
			RuleT *new_rule_list;

			rule_left_cycle_general_case_3(rule, size, vector, table,
				&new_rule_list, &param, &result);
			rule_left_cycle_general_case_4(new_rule_list, i, size, matrix,
				table);
		}
	}

	types_destroy(&param);
	types_destroy(&result);
	rule_destroy_cycle_matrix(matrix, matrix_size);
	rule_destroy_cycle_vector(vector, size);
}


/*
 * Externally visible functions
 */

void
rule_remove_left_cycle(RuleT *rule_list, EntryT *predicate_id, TableT *table)
{
	unsigned size      = 0;
	unsigned real_size = 0;
	RuleT *rule;

	for (rule = rule_list; rule; rule = rule_get_next_in_reverse_dfs(rule)) {
		size++;
		if (key_is_string(entry_key(rule_entry(rule)))) {
			real_size++;
		}
		rule_set_cycle_index(rule, size);
	}

	if ((size != 1 || !rule_left_cycle_special_case(rule_list, table))
		&& rule_check_cycle_types(rule_list, predicate_id, real_size, table)) {
		rule_left_cycle_general_case(rule_list, size, table);
	}

	for (rule = rule_list; rule; rule = rule_get_next_in_reverse_dfs(rule)) {
		rule_reset_cycle_index(rule);
		rule_no_cycles(rule);
	}
}
