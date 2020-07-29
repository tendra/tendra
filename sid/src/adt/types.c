/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * types.c - Type ADTs.
 *
 * This file implements the type manipulation routines specified.
 */

#include <assert.h>
#include <stddef.h>
#include <limits.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <exds/dalloc.h>

#include "types.h"
#include "type.h"
#include "name.h"
#include "rstack.h"
#include "rule.h"
#include "table.h"

/*
 * Type tuple handling fuctions
 */

static void
types_add_name_and_type_1(TypeTupleT *to, EntryT *name, EntryT *type,
	bool reference, bool assign)
{
	TypeTupleEntryT *link = ALLOCATE(TypeTupleEntryT);

	link->next      = NULL;
	link->type      = type;
	link->name      = name;
	link->reference = reference;
	link->mutated   = false;
	link->assign    = assign;
	*to->tail       = link;
	to->tail        = &link->next;
}

static void
types_iter_alt_item_type_names(AltT *alts, void(*proc)(NameT *))
{
	AltT            *alt;
	TypeTupleEntryT *type;

	for (alt = alts; alt; alt = alt_next(alt)) {
		ItemT *item;

		for (item = alt_item_head(alt); item; item = item_next(item)) {
			TypeTupleT *param  = item_param(item);
			TypeTupleT *result = item_result(item);

			for (type = param->head; type; type = type->next) {
				proc(entry_get_name(type->name));
			}

			for (type = result->head; type; type = type->next) {
				proc(entry_get_name(type->name));
			}
		}
	}
}

void
types_init(TypeTupleT *tuple)
{
	tuple->head = NULL;
	tuple->tail = &tuple->head;
}

void
types_copy(TypeTupleT *to, TypeTupleT *from)
{
	TypeTupleEntryT *from_ptr;

	to->head = NULL;
	to->tail = &to->head;
	for (from_ptr = from->head; from_ptr; from_ptr = from_ptr->next) {
		types_add_name_and_type_1(to, from_ptr->name, from_ptr->type,
			from_ptr->reference, from_ptr->assign);
	}
}

void
types_copy_and_translate(TypeTupleT *to, TypeTupleT *from, TypeTransT *translator,
	TableT *table)
{
	TypeTupleEntryT *from_ptr;

	to->head = NULL;
	to->tail = &to->head;
	for (from_ptr = from->head; from_ptr; from_ptr = from_ptr->next) {
		EntryT *new_name;

		new_name = trans_get_translation(translator, from_ptr->name);
		if (new_name == NULL) {
			new_name = table_add_generated_name(table);
			trans_add_translation(translator, from_ptr->name, new_name);
		}

		types_add_name_and_type_1(to, new_name, from_ptr->type,
			from_ptr->reference, from_ptr->assign);
	}
}

void
types_append_copy(TypeTupleT *to, TypeTupleT *from)
{
	TypeTupleEntryT *from_ptr;

	for (from_ptr = from->head; from_ptr; from_ptr = from_ptr->next) {
		types_add_name_and_type_1(to, from_ptr->name, from_ptr->type,
			from_ptr->reference, from_ptr->assign);
	}
}

void
types_translate(TypeTupleT *tuple, TypeBTransT *translator)
{
	TypeTupleEntryT *tuple_ptr;

	for (tuple_ptr = tuple->head; tuple_ptr; tuple_ptr = tuple_ptr->next) {
		EntryT *new_name;

		new_name = btrans_get_translation(translator, tuple_ptr->name);
		if (new_name != NULL) {
			tuple_ptr->name = new_name;
		}
	}
}

void
types_renumber(TypeTupleT *tuple, TypeNTransT *translator)
{
	TypeTupleEntryT *tuple_ptr;

	for (tuple_ptr = tuple->head; tuple_ptr; tuple_ptr = tuple_ptr->next) {
		if (!entry_is_non_local(tuple_ptr->name)) {
			tuple_ptr->number = ntrans_get_translation(translator,
				tuple_ptr->name);
		}
	}
}

void
types_assign(TypeTupleT *to, TypeTupleT *from)
{
	to->head = from->head;
	if (to->head != NULL) {
		to->tail = from->tail;
	} else {
		to->tail = &to->head;
	}
}

EntryT *
types_find_name_type(TypeTupleT *tuple, EntryT *name, bool *reference_ref)
{
	TypeTupleEntryT *type;

	for (type = tuple->head; type; type = type->next) {
		if (type->name == name) {
			*reference_ref = type->reference;
			return type->type;
		}
	}

	return NULL;
}

bool
types_mutated(TypeTupleT *tuple, EntryT *name)
{
	TypeTupleEntryT *type;

	for (type = tuple->head; type; type = type->next) {
		if (type->name == name) {
			type->mutated = true;
			return true;
		}
	}

	return false;
}

bool
types_compute_mutations(TypeTupleT *rule, TypeTupleT *item, TypeTupleT *action)
{
	bool            propogate  = false;
	TypeTupleEntryT *item_ptr;
	TypeTupleEntryT *action_ptr;

	for (item_ptr = item->head, action_ptr = action->head;
		action_ptr; item_ptr = item_ptr->next, action_ptr = action_ptr->next) {
		TypeTupleEntryT *rule_ptr;

		assert(item_ptr);
		if (!action_ptr->mutated) {
			continue;
		}

		for (rule_ptr = rule->head; rule_ptr; rule_ptr = rule_ptr->next) {
			if (rule_ptr->name == item_ptr->name && !rule_ptr->mutated) {
				rule_ptr->mutated = true;
				if (rule_ptr->reference) {
					propogate = true;
				}
				break;
			}
		}
	}
	assert(item_ptr == NULL);

	return propogate;
}

bool
types_compute_assign_mutations(TypeTupleT *rule, TypeTupleT *item)
{
	bool            propogate  = false;
	TypeTupleEntryT *item_ptr;

	for (item_ptr = item->head; item_ptr; item_ptr = item_ptr->next) {
		TypeTupleEntryT *rule_ptr;

		if (!item_ptr->assign) {
			continue;
		}

		for (rule_ptr = rule->head; rule_ptr; rule_ptr = rule_ptr->next) {
			if (rule_ptr->name == item_ptr->name && !rule_ptr->mutated) {
				rule_ptr->mutated = true;
				if (rule_ptr->reference) {
					propogate = true;
				}
				break;
			}
		}
	}

	return propogate;
}

void
types_propogate_mutations(TypeTupleT *to, TypeTupleT *from)
{
	TypeTupleEntryT *to_ptr;
	TypeTupleEntryT *from_ptr;

	for (to_ptr = to->head, from_ptr = from->head;
		to_ptr; to_ptr = to_ptr->next, from_ptr = from_ptr->next) {
		assert(from_ptr);
		to_ptr->mutated = from_ptr->mutated;
	}
	assert(from_ptr == NULL);
}

bool
types_contains(TypeTupleT *tuple, EntryT *name)
{
	TypeTupleEntryT *type;

	for (type = tuple->head; type; type = type->next) {
		if (type->name == name) {
			return true;
		}
	}

	return false;
}

bool
types_contains_names(TypeTupleT *tuple)
{
	TypeTupleEntryT *type;

	for (type = tuple->head; type; type = type->next) {
		if (type->name) {
			return true;
		}
	}

	return false;
}

bool
types_contains_references(TypeTupleT *tuple)
{
	TypeTupleEntryT *type;

	for (type = tuple->head; type; type = type->next) {
		if (type->reference) {
			return true;
		}
	}

	return false;
}

EntryT *
types_find_ignored(TypeTupleT *tuple)
{
	TypeTupleEntryT *type;

	for (type = tuple->head; type; type = type->next) {
		if (type_get_ignored(entry_get_type(type->type))) {
			return type->type;
		}
	}

	return NULL;
}

void
types_make_references(TypeTupleT *param, TypeTupleT *args)
{
	TypeTupleEntryT *ptr;

	for (ptr = param->head; ptr; ptr = ptr->next) {
		ptr->reference = true;
	}

	for (ptr = args->head; ptr; ptr = ptr->next) {
		ptr->reference = true;
	}
}

bool
types_intersect(TypeTupleT *tuple1, TypeTupleT *tuple2)
{
	TypeTupleEntryT *type;

	for (type = tuple1->head; type; type = type->next) {
		if (types_contains(tuple2, type->name)) {
			return true;
		}
	}

	return false;
}

void
types_inplace_intersection(TypeTupleT *to, TypeTupleT *from)
{
	TypeTupleEntryT *type;

	to->tail = &to->head;
	while ((type = *to->tail) != NULL) {
		if (!types_contains(from, type->name)) {
			*to->tail = type->next;
			DEALLOCATE(type);
		} else {
			to->tail = &type->next;
		}
	}
}

void
types_compute_intersection(TypeTupleT *to, TypeTupleT *tuple1, TypeTupleT *tuple2)
{
	TypeTupleEntryT *type;

	for (type = tuple1->head; type; type = type->next) {
		if (types_contains(tuple2, type->name)
			&& !types_contains(to, type->name)) {
			types_add_name_and_type_1(to, type->name, type->type,
				type->reference, type->assign);
		}
	}
}

CmpT
types_compare(TypeTupleT *tuple1, TypeTupleT *tuple2)
{
	TypeTupleEntryT *tuple1_ptr = tuple1->head;
	TypeTupleEntryT *tuple2_ptr = tuple2->head;

	for (tuple1_ptr = tuple1->head, tuple2_ptr = tuple2->head;
		tuple1_ptr && tuple2_ptr;
		tuple1_ptr = tuple1_ptr->next, tuple2_ptr = tuple2_ptr->next) {

		if (tuple1_ptr->number < tuple2_ptr->number) {
			return CMP_LT;
		} else if (tuple1_ptr->number > tuple2_ptr->number) {
			return CMP_GT;
		}

		switch (key_compare(entry_key(tuple1_ptr->type),
			entry_key(tuple2_ptr->type))) EXHAUSTIVE {
		case CMP_LT:
			return CMP_LT;

		case CMP_GT:
			return CMP_GT;

		case CMP_EQ:
			break;
		}

		if (tuple1_ptr->reference != tuple2_ptr->reference) {
			return tuple1_ptr->reference ? CMP_GT : CMP_LT;
		} else if (tuple1_ptr->assign != tuple2_ptr->assign) {
			return tuple1_ptr->assign ? CMP_GT : CMP_LT;
		}
	}

	if (tuple1_ptr != NULL) {
		return CMP_GT;
	} else if (tuple2_ptr != NULL) {
		return CMP_LT;
	} else {
		return CMP_EQ;
	}
}

bool
types_equal(TypeTupleT *tuple1, TypeTupleT *tuple2)
{
	TypeTupleEntryT *tuple1_ptr;
	TypeTupleEntryT *tuple2_ptr;

	for (tuple1_ptr = tuple1->head, tuple2_ptr = tuple2->head;
		tuple1_ptr && tuple2_ptr;
		tuple1_ptr = tuple1_ptr->next, tuple2_ptr = tuple2_ptr->next) {

		if (tuple1_ptr->type != tuple2_ptr->type
			|| tuple1_ptr->reference != tuple2_ptr->reference
			|| tuple1_ptr->assign != tuple2_ptr->assign) {
			return false;
		}
	}

	return tuple1_ptr == NULL && tuple2_ptr == NULL;
}

bool
types_equal_zero_tuple(TypeTupleT *tuple)
{
	return tuple->head == NULL;
}

bool
types_equal_names(TypeTupleT *tuple1, TypeTupleT *tuple2)
{
	TypeTupleEntryT *tuple1_ptr;
	TypeTupleEntryT *tuple2_ptr;

	for (tuple1_ptr = tuple1->head, tuple2_ptr = tuple2->head;
		tuple1_ptr && tuple2_ptr;
		tuple1_ptr = tuple1_ptr->next, tuple2_ptr = tuple2_ptr->next) {

		if (tuple1_ptr->type != tuple2_ptr->type
			|| tuple1_ptr->reference != tuple2_ptr->reference
			|| tuple1_ptr->assign != tuple2_ptr->assign
			|| tuple1_ptr->name != tuple2_ptr->name) {
			return false;
		}
	}

	return tuple1_ptr == NULL && tuple2_ptr == NULL;
}

bool
types_equal_numbers(TypeTupleT *tuple1, TypeTupleT *tuple2)
{
	TypeTupleEntryT *tuple1_ptr;
	TypeTupleEntryT *tuple2_ptr;

	for (tuple1_ptr = tuple1->head, tuple2_ptr = tuple2->head;
		tuple1_ptr && tuple2_ptr;
		tuple1_ptr = tuple1_ptr->next, tuple2_ptr = tuple2_ptr->next) {

		if (tuple1_ptr->type != tuple2_ptr->type
		  	|| tuple1_ptr->reference != tuple2_ptr->reference
			|| tuple1_ptr->assign != tuple2_ptr->assign) {
			return false;
		} else if (entry_is_non_local(tuple1_ptr->name)
			|| entry_is_non_local(tuple2_ptr->name)) {
			if (tuple1_ptr->name != tuple2_ptr->name) {
				return false;
			}
		} else if (tuple1_ptr->number != tuple2_ptr->number) {
			return false;
		}
	}

	return tuple1_ptr == NULL && tuple2_ptr == NULL;
}

void
types_add_name_and_type(TypeTupleT *to, EntryT *name, EntryT *type,
	bool reference)
{
	types_add_name_and_type_1(to, name, type, reference, false);
}

void
types_add_name_and_type_var(TypeTupleT *to, EntryT *name, EntryT *type)
{
	types_add_name_and_type_1(to, name, type, false, true);
}

bool
types_add_type(TypeTupleT *tuple, TableT *table, NStringT *name, bool reference)
{
	EntryT *entry = table_get_type(table, name);

	if (entry) {
		types_add_name_and_type(tuple, NULL, entry, reference);
		return true;
	}

	return false;
}

void
types_add_name(TypeTupleT *tuple, TableT *table, NStringT *name, bool reference)
{
	EntryT *entry = table_add_name(table, name);

	types_add_name_and_type(tuple, entry, NULL, reference);
}

bool
types_add_typed_name(TypeTupleT *tuple, TableT *table, NStringT *name,
	NStringT *type, bool reference)
{
	EntryT *type_entry = table_get_type(table, type);
	EntryT *name_entry = table_add_name(table, name);

	if (type_entry) {
		types_add_name_and_type(tuple, name_entry, type_entry, reference);
		return true;
	}

	return false;
}

void
types_add_name_entry(TypeTupleT *tuple, EntryT *entry)
{
	types_add_name_and_type(tuple, entry, NULL, false);
}

void
types_add_type_entry(TypeTupleT *tuple, EntryT *entry, bool reference)
{
	types_add_name_and_type(tuple, NULL, entry, reference);
}

void
types_add_new_names(TypeTupleT *to, TypeTupleT *from, EntryT *exclude)
{
	TypeTupleEntryT *from_ptr;

	for (from_ptr = from->head; from_ptr; from_ptr = from_ptr->next) {
		if (from_ptr->name != exclude
		&& !from_ptr->assign
		&& !types_contains(to, from_ptr->name)) {
			types_add_name_and_type(to, from_ptr->name, from_ptr->type,
				from_ptr->reference);
		}
	}
}

bool
types_disjoint_names(TypeTupleT * tuple)
{
	bool            disjoint = true;
	TypeTupleEntryT *ptr;

	for (ptr = tuple->head; ptr; ptr = ptr->next) {
		if (ptr->name) {
			if (name_test_and_set_clash(entry_get_name(ptr->name))) {
				disjoint = false;
				goto done;	/* XXX why not break? */
			}
		} else {
			disjoint = false;
			goto done;
		}
	}

done:
	for (ptr = tuple->head; ptr; ptr = ptr->next) {
		if (ptr->name) {
			name_reset_clash(entry_get_name(ptr->name));
		}
	}

	return disjoint;
}

bool
types_resolve(TypeTupleT * to, TypeTupleT * args, TypeTupleT * locals,
	void (*unknown_proc)(KeyT *, KeyT *, unsigned), KeyT * rule, unsigned alt)
{
	bool            ok;
	TypeTupleEntryT *name;

	ok = true;
	for (name = to->head; name; name = name->next) {
		bool reference;

		if (entry_is_non_local(name->name)) {
			name->type = entry_get_non_local(name->name);
			continue;
		}

		name->type = types_find_name_type(args, name->name, &reference);
		if (name->type) {
			continue;
		}

		name->type = types_find_name_type(locals, name->name, &reference);
		if (!name->type) {
			unknown_proc(entry_key(name->name), rule, alt);
			ok = false;
		}
	}

	return ok;
}

bool
types_check_undefined(TypeTupleT *to, TypeTupleT *args, TypeTupleT *locals,
	void (*error_proc)(KeyT *, KeyT *, unsigned), KeyT *rule, unsigned alt)
{
	bool            ok;
	TypeTupleEntryT *name;

	ok = true;
	for (name = to->head; name; name = name->next) {
		if (!name->assign
			&& (entry_is_non_local(name->name)
				|| types_contains(args, name->name)
				|| types_contains(locals, name->name))) {
			error_proc(entry_key(name->name), rule, alt);
			ok = false;
		}
	}

	return ok;
}

bool
types_fillin_types(TypeTupleT *to, TypeTupleT *from)
{
	TypeTupleEntryT *to_ptr;
	TypeTupleEntryT *from_ptr;

	for (to_ptr = to->head, from_ptr = from->head;
		to_ptr && from_ptr; to_ptr = to_ptr->next, from_ptr = from_ptr->next) {

		if (to_ptr->type == NULL) {
			to_ptr->type      = from_ptr->type;
			to_ptr->reference = from_ptr->reference;
		} else if (to_ptr->type != from_ptr->type
			|| to_ptr->reference != from_ptr->reference) {
			return false;
		}
	}

	return to_ptr == NULL && from_ptr == NULL;
}

bool
types_fillin_names(TypeTupleT * to, TypeTupleT * from)
{
	TypeTupleEntryT *to_ptr;
	TypeTupleEntryT *from_ptr;

	for (to_ptr = to->head, from_ptr = from->head;
		to_ptr && from_ptr;
		to_ptr = to_ptr->next, from_ptr = from_ptr->next) {

		assert(to_ptr->name == NULL);
		to_ptr->name = from_ptr->name;
		if (from_ptr->type
			&& (to_ptr->type != from_ptr->type
				|| to_ptr->reference != from_ptr->reference)) {
			return false;
		}
	}

	return to_ptr == NULL && from_ptr == NULL;
}

bool
types_check_names(TypeTupleT *to, TypeTupleT *from)
{
	TypeTupleEntryT *to_ptr;

	for (to_ptr = to->head; to_ptr; to_ptr = to_ptr->next) {
		bool reference;

		if (types_find_name_type(from, to_ptr->name, &reference) != to_ptr->type
			|| reference != to_ptr->reference) {
			return false;
		}
	}

	return true;
}

void
types_check_used(TypeTupleT *tuple, void (*error_proc)(void *, EntryT *),
	void *gclosure)
{
	TypeTupleEntryT *ptr;

	for (ptr = tuple->head; ptr; ptr = ptr->next) {
		assert(!entry_is_non_local(ptr->name));
		if (!name_is_used(entry_get_name(ptr->name))) {
			error_proc(gclosure, ptr->name);
		}
	}
}

void
types_unlink_used(TypeTupleT *to, TypeTupleT *from)
{
	TypeTupleEntryT *type;

	to->tail = &to->head;
	while ((type = *to->tail) != NULL) {
		if (types_contains(from, type->name)) {
			*to->tail = type->next;
			DEALLOCATE(type);
		} else {
			to->tail = &type->next;
		}
	}
}

void
types_unlink_unused(TypeTupleT *tuple, AltT *alts)
{
	TypeTupleEntryT *type;

	types_iter_alt_item_type_names(alts, name_used);
	tuple->tail = &tuple->head;

	while ((type = *tuple->tail) != NULL) {
		assert(!entry_is_non_local(type->name));
		if (name_is_used(entry_get_name(type->name))) {
			tuple->tail = &type->next;
		} else {
			*tuple->tail = type->next;
			DEALLOCATE(type);
		}
	}

	types_iter_alt_item_type_names(alts, name_not_used);
}

void
types_compute_formal_renaming(TypeTupleT *names, TypeRTransT *translator)
{
	TypeTupleEntryT *ptr;

	for (ptr = names->head; ptr; ptr = ptr->next) {
		rtrans_add_translation(translator, ptr->name, ptr->name, ptr->type,
			ptr->reference);
	}
}

void
types_compute_formal_inlining(TypeTupleT *names, TypeTupleT *renames,
	TypeRTransT *translator, SaveRStackT *state)
{
	TypeTupleEntryT *ptr;
	TypeTupleEntryT *reptr;

	for (ptr = names->head, reptr = renames->head;
		ptr; ptr = ptr->next, reptr = reptr->next) {

		EntryT *entry;
		EntryT *type;
		bool   reference;

		assert(reptr);
		entry = rstack_get_translation(state, reptr->name, &type, &reference);
			assert(entry);
		rtrans_add_translation(translator, ptr->name, entry, type, reference);
	}

	assert(reptr == NULL);
}

void
types_compute_local_renaming(TypeTupleT *names, TypeTupleT *exclude,
	TypeRTransT *translator, SaveRStackT *state, TableT *table)
{
	TypeTupleEntryT *ptr;

	for (ptr = names->head; ptr; ptr = ptr->next) {
		EntryT *type;
		bool   reference;

		if (types_contains(exclude, ptr->name)) {
			continue;
		}

		if (rstack_get_translation(state, ptr->name, &type, &reference) != NULL) {
			EntryT *entry = table_add_generated_name(table);

			rtrans_add_translation(translator, ptr->name, entry,
				ptr->type, ptr->reference);
		} else {
			rtrans_add_translation(translator, ptr->name, ptr->name,
				ptr->type, ptr->reference);
		}
	}
}

void
types_compute_param_from_trans(TypeTupleT *new_param,
	TypeNTransT *from_translator, TypeNTransT *to_translator,
	TypeTupleT *old_param)
{
	TypeTupleEntryT *ptr;

	types_init(new_param);
	for (ptr = old_param->head; ptr; ptr = ptr->next) {
		EntryT *entry = ntrans_get_indirect_translation(from_translator,
			to_translator, ptr->name);

		if (entry) {
			types_add_name_and_type(new_param, entry, ptr->type,
				ptr->reference);
		}
	}
}

bool
types_check_shadowing(TypeTupleT *tuple, ScopeStackT *stack, RuleT *rule)
{
	bool            errored = false;
	TypeTupleEntryT *ptr;

	for (ptr = tuple->head; ptr; ptr = ptr->next) {
		if (scope_stack_check_shadowing(stack, ptr->name, rule)) {
			errored = true;
		}
	}

	return errored;
}

void
types_iter_for_table(TypeTupleT *tuple, void (*proc)(EntryT *, void *),
	void *closure)
{
	TypeTupleEntryT *ptr;

	for (ptr = tuple->head; ptr; ptr = ptr->next) {
		if (ptr->type) {
			entry_iter(ptr->type, true, proc, closure);
		}

		if (ptr->name) {
			entry_iter(ptr->name, true, proc, closure);
		}
	}
}

void
types_destroy(TypeTupleT *tuple)
{
	TypeTupleEntryT *tuple_ptr;
	TypeTupleEntryT *tmp_ptr;

	for (tuple_ptr = tuple->head; tuple_ptr; tuple_ptr = tmp_ptr) {
		tmp_ptr = tuple_ptr->next;
		DEALLOCATE(tuple_ptr);
	}
}

void
write_type_types(OStreamT *ostream, TypeTupleT *tuple)
{
	TypeTupleEntryT *type;

	write_char(ostream, '(');
	for (type = tuple->head; type; type = type->next) {
		if (type->type) {
			write_cstring(ostream, ": ");
			write_key(ostream, entry_key(type->type));
			if (type->reference) {
				write_cstring(ostream, " &");
			}
		} else {
			write_cstring(ostream, ": <unknown>");
		}

		if (type->next) {
			write_cstring(ostream, ", ");
		}
	}
	write_char(ostream, ')');
}

void
write_type_names(OStreamT *ostream, TypeTupleT *tuple, bool call)
{
	TypeTupleEntryT *type;

	write_char(ostream, '(');
	for (type = tuple->head; type; type = type->next) {
		if (type->name) {
			if ((call && type->reference) || (type->assign)) {
				write_char(ostream, '&');
			}
			write_key(ostream, entry_key(type->name));
		}

		if (type->type) {
			write_cstring(ostream, ": ");
			write_key(ostream, entry_key(type->type));
			if (type->reference) {
				write_cstring(ostream, " &");
			}
		}

		if (type->next) {
			write_cstring(ostream, ", ");
		}
	}
	write_char(ostream, ')');
}


/*
 * Basic name translator handling functions
 */

void
btrans_init(TypeBTransT *translator)
{
	translator->head = NULL;
	translator->tail = &translator->head;
}

void
btrans_add_translations(TypeBTransT *translator, TypeTupleT *from, TypeTupleT *to)
{
	TypeTupleEntryT *from_ptr;
	TypeTupleEntryT *to_ptr;

	for (from_ptr = from->head, to_ptr = to->head;
		from_ptr; from_ptr = from_ptr->next, to_ptr = to_ptr->next) {

		assert(to_ptr != NULL);
		btrans_add_translation(translator, from_ptr->name, to_ptr->name);
	}

	assert(to_ptr == NULL);
}

void
btrans_add_translation(TypeBTransT *translator, EntryT *from, EntryT *to)
{
	TransT *link = ALLOCATE(TransT);

	link->to          = to;
	link->from        = from;
	link->next        = NULL;
	*translator->tail = link;
	translator->tail  = &link->next;
}

void
btrans_generate_names(TypeBTransT *translator, TypeTupleT *tuple, TableT *table)
{
	TypeTupleEntryT *tuple_ptr;

	for (tuple_ptr = tuple->head; tuple_ptr; tuple_ptr = tuple_ptr->next) {
		btrans_add_translation(translator, tuple_ptr->name,
		table_add_generated_name(table));
	}
}

void
btrans_regenerate_names(TypeBTransT *translator, TypeTupleT *tuple)
{
	TypeTupleEntryT *tuple_ptr;
	TransT *trans_ptr;

	for (tuple_ptr = tuple->head, trans_ptr = translator->head;
		tuple_ptr; trans_ptr = trans_ptr->next, tuple_ptr = tuple_ptr->next) {
		assert(trans_ptr != NULL);
		trans_ptr->from = tuple_ptr->name;
	}

	assert(trans_ptr == NULL);
}

ItemT *
btrans_generate_non_pred_names(TypeBTransT *translator, TypeTupleT *tuple,
	TypeTupleT *result, EntryT *predicate_id, TableT *table)
{
	TypeTupleEntryT *ptr;
	TypeTupleT       from;
	TypeTupleT       to;

	types_init(&from);
	types_init(&to);
	for (ptr = tuple->head; ptr; ptr = ptr->next) {
		EntryT *entry;

		if (ptr->name == predicate_id) {
			btrans_add_translation(translator, predicate_id, predicate_id);
			continue;
		}

		entry = table_add_generated_name(table);
		btrans_add_translation(translator, ptr->name, entry);
		if (types_contains(result, ptr->name)) {
			types_add_name_and_type(&from, entry, ptr->type, ptr->reference);
			types_add_name_and_type(&to, ptr->name, ptr->type, ptr->reference);
		}
	}

	if (types_equal_zero_tuple(&from)) {
		types_destroy(&from);
		types_destroy(&to);
		return NULL;
	} else {
		ItemT *item = item_create(table_add_rename(table));

		types_assign(item_param(item), &from);
		types_assign(item_result(item), &to);
		return item;
	}
}

ItemT *
btrans_regen_non_pred_names(TypeBTransT *translator, TypeTupleT *tuple,
	TypeTupleT *result, TableT *table)
{
	TypeTupleEntryT *tuple_ptr;
	TransT          *trans_ptr;
	TypeTupleT       from;
	TypeTupleT       to;

	types_init(&from);
	types_init(&to);
	for (tuple_ptr = tuple->head, trans_ptr = translator->head;
		tuple_ptr; trans_ptr = trans_ptr->next, tuple_ptr = tuple_ptr->next) {

		assert(trans_ptr != NULL);
		trans_ptr->from = tuple_ptr->name;
		if (types_contains(result, tuple_ptr->name)) {
			types_add_name_and_type(&from, trans_ptr->to, tuple_ptr->type,
				tuple_ptr->reference);
			types_add_name_and_type(&to, trans_ptr->from, tuple_ptr->type,
				tuple_ptr->reference);
		}
	}

	assert(trans_ptr == NULL);
	if (types_equal_zero_tuple(&from)) {
		types_destroy(&from);
		types_destroy(&to);
		return NULL;
	} else {
		ItemT *item = item_create(table_add_rename(table));

		types_assign(item_param(item), &from);
		types_assign(item_result(item), &to);
		return item;
	}
}

EntryT *
btrans_get_translation(TypeBTransT *translator, EntryT *entry)
{
	EntryT *translation = NULL;
	TransT *ptr;

	for (ptr = translator->head; ptr; ptr = ptr->next) {
		if (ptr->from == entry) {
			translation = ptr->to;
		}
	}

	return translation;
}

void
btrans_destroy(TypeBTransT *translator)
{
	TransT *ptr = translator->head;
	TransT *tmp;

	while ((tmp = ptr) != NULL) {
		ptr = ptr->next;
		DEALLOCATE(tmp);
	}
}


/*
 * Rename stack name translator handling functions
 */

void
rtrans_init(TypeRTransT *translator)
{
	translator->head = NULL;
	translator->tail = &translator->head;
}

void
rtrans_add_translation(TypeRTransT *translator, EntryT *from, EntryT *to,
	EntryT *type, bool reference)
{
	RTransT *link = ALLOCATE(RTransT);

	link->next        = NULL;
	link->to          = to;
	link->from        = from;
	link->type        = type;
	link->reference   = reference;
	*translator->tail = link;
	translator->tail  = &link->next;
}

EntryT *
rtrans_get_translation(TypeRTransT *translator, EntryT *entry, EntryT **type_ref,
	bool *reference_ref)
{
	RTransT *ptr;

	for (ptr = translator->head; ptr; ptr = ptr->next) {
		if (ptr->from == entry) {
			*type_ref      = ptr->type;
			*reference_ref = ptr->reference;
			return ptr->to;
		}
	}

	return NULL;
}

void
rtrans_apply_for_non_locals(TypeRTransT *translator,
	void (*proc)(EntryT *, EntryT *, void *), void *closure)
{
	RTransT *ptr;

	for (ptr = translator->head; ptr; ptr = ptr->next) {
		proc(ptr->from, ptr->to, closure);
	}
}

void
rtrans_destroy(TypeRTransT *translator)
{
	RTransT *ptr = translator->head;
	RTransT *tmp;

	while ((tmp = ptr) != NULL) {
		ptr = ptr->next;
		DEALLOCATE(tmp);
	}
}


/*
 * Name translator handling functions
 */

void
trans_init(TypeTransT *translator, TypeTupleT *param, TypeTupleT *result,
	AltT *alt)
{
	TypeTupleEntryT *ptr;
	ItemT           *item;

	translator->head = NULL;
	translator->tail = &translator->head;
	entry_list_init(&translator->used_names);

	for (ptr = param->head; ptr; ptr = ptr->next) {
		entry_list_add_if_missing(&translator->used_names, ptr->name);
	}

	for (ptr = result->head; ptr; ptr = ptr->next) {
		entry_list_add_if_missing(&translator->used_names, ptr->name);
	}

	for (item = alt_item_head(alt); item; item = item_next(item)) {
		TypeTupleT *type = item_result(item);

		for (ptr = type->head; ptr; ptr = ptr->next) {
			entry_list_add_if_missing(&translator->used_names, ptr->name);
		}
	}
}

void
trans_add_translation(TypeTransT *translator, EntryT *from, EntryT *to)
{
	TransT *link = ALLOCATE(TransT);

	link->to          = to;
	link->from        = from;
	link->next        = NULL;
	*translator->tail = link;
	translator->tail  = &link->next;
}

void
trans_add_translations(TypeTransT *translator, TypeTupleT *from, TypeTupleT *to)
{
	TypeTupleEntryT *from_ptr = from->head;
	TypeTupleEntryT *to_ptr   = to->head;

	while (from_ptr) {
		assert(to_ptr != NULL);
		trans_add_translation(translator, from_ptr->name, to_ptr->name);
		from_ptr = from_ptr->next;
		to_ptr   = to_ptr->next;
	}

	assert(to_ptr == NULL);
}

void
trans_save_state(TypeTransT *translator, SaveTransT *state)
{
	state->last_ref = translator->tail;
}

EntryT *
trans_get_translation(TypeTransT *translator, EntryT *entry)
{
	EntryT *translation = NULL;
	TransT *ptr;

	for (ptr = translator->head; ptr; ptr = ptr->next) {
		if (ptr->from == entry) {
			translation = ptr->to;
		}
	}

	if (translation) {
		return translation;
	}

	if (!entry_list_contains(&translator->used_names, entry)) {
		return entry;
	}

	return NULL;
}

void
trans_restore_state(TypeTransT *translator, SaveTransT *state)
{
	TransT *ptr = *state->last_ref;
	TransT *tmp;

	*state->last_ref = NULL;
	while ((tmp = ptr) != NULL) {
		ptr = ptr->next;
		DEALLOCATE(tmp);
	}
	translator->tail = state->last_ref;
}

void
trans_destroy(TypeTransT *translator)
{
	TransT *ptr = translator->head;
	TransT *tmp;

	while ((tmp = ptr) != NULL) {
		ptr = ptr->next;
		DEALLOCATE(tmp);
	}
	entry_list_destroy(&translator->used_names);
}

/*
 * Numeric translator handling functions
 */

static unsigned
ntrans_add_translation(TypeNTransT *translator, EntryT *from)
{
	NTransT *link = ALLOCATE(NTransT);

	if (translator->count == UINT_MAX) {
		error(ERR_FATAL, "too many automatically generated names required");
		UNREACHED;
	}

	link->to          = translator->count++;
	link->from        = from;
	link->next        = NULL;
	*translator->tail = link;
	translator->tail  = &link->next;

	return link->to;
}

void
ntrans_init(TypeNTransT *translator)
{
	translator->count = 0;
	translator->head  = NULL;
	translator->tail  = &translator->head;
}

void
ntrans_save_state(TypeNTransT *translator, SaveNTransT *state)
{
	state->last_count = translator->count;
	state->last_ref   = translator->tail;
}

unsigned
ntrans_get_translation(TypeNTransT *translator, EntryT *entry)
{
	NTransT *ptr;

	for (ptr = translator->head; ptr; ptr = ptr->next) {
		if (ptr->from == entry) {
			return ptr->to;
		}
	}

	return ntrans_add_translation(translator, entry);
}

EntryT *
ntrans_get_indirect_translation(TypeNTransT *from_translator,
	TypeNTransT *to_translator, EntryT *entry)
{
	NTransT  *ptr;
	unsigned  name;

	for (ptr = from_translator->head; ptr; ptr = ptr->next) {
		if (ptr->from == entry) {
			name = ptr->to;
			goto found;
		}
	}

	return NULL;

found:
	for (ptr = to_translator->head; ptr; ptr = ptr->next) {
		if (ptr->to == name) {
			return ptr->from;
		}
	}

	UNREACHED;
}

void
ntrans_restore_state(TypeNTransT *translator, SaveNTransT *state)
{
	NTransT *ptr = *state->last_ref;
	NTransT *tmp;

	*state->last_ref   = NULL;
	translator->count  = state->last_count;

	while ((tmp = ptr) != NULL) {
		ptr = ptr->next;
		DEALLOCATE(tmp);
	}

	translator->tail = state->last_ref;
}

void
ntrans_destroy(TypeNTransT *translator)
{
	NTransT *ptr = translator->head;
	NTransT *tmp;

	while ((tmp = ptr) != NULL) {
		ptr = ptr->next;
		DEALLOCATE(tmp);
	}
}
