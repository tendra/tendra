/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * scope.c - Scope stack ADT.
 *
 * This file implements the scope stack manipulation routines.
 */

#include <assert.h>

#include <shared/check.h>
#include <shared/error.h>

#include "scope.h"
#include "rule.h"

void
scope_stack_init(ScopeStackT *stack)
{
	stack->head = NULL;
}

void
scope_stack_push(ScopeStackT *stack, NStringT *scope)
{
	ScopeStackFrameT *frame = ALLOCATE(ScopeStackFrameT);
	DStringT          dstring;

	dstring_init(&dstring);
	if (frame->head) {
		dstring_append_nstring(&dstring, &stack->head->scope);
	}

	dstring_append_nstring(&dstring, scope);
	dstring_append_cstring(&dstring, "::");
	dstring_to_nstring(&dstring, &frame->scope);
	dstring_destroy(&dstring);
	frame->next = stack->head;
	frame->head = NULL;
	frame->tail = &frame->head;
	stack->head = frame;
}

void
scope_stack_pop(ScopeStackT *stack)
{
	ScopeStackFrameT *frame = stack->head;
	ScopeMapEntryT   *entry;
	ScopeMapEntryT   *next;

	assert(frame);
	stack->head = frame->next;
	nstring_destroy(&frame->scope);

	for (entry = frame->head; entry; entry = next) {
		next = entry->next;
		DEALLOCATE(entry);
	}

	DEALLOCATE(frame);
}

EntryT *
scope_stack_add_rule(ScopeStackT *stack, TableT *table, NStringT *key,
	RuleT *rule, BoolT *found_ref)
{
	DStringT        dstring;
	NStringT        nstring;
	EntryT         *entry;
	EntryT         *from;
	ScopeMapEntryT *map;

	*found_ref = FALSE;
	if (!stack->head) {
		if (table_get_rule(table, key)) {
			*found_ref = TRUE;
		}

		return table_add_rule(table, key);
	}

	dstring_init(&dstring);
	dstring_append_nstring(&dstring, &stack->head->scope);
	dstring_append_nstring(&dstring, key);
	dstring_to_nstring(&dstring, &nstring);
	dstring_destroy(&dstring);

	entry = table_get_rule(table, &nstring);
	if (entry != NULL) {
		*found_ref = TRUE;
		nstring_destroy(&nstring);
		return entry;
	}

	entry = table_add_rule(table, &nstring);
	if (entry == NULL) {
		nstring_destroy(&nstring);
		return NULL;
	}

	from = table_add_name(table, key);
	map  = ALLOCATE(ScopeMapEntryT);

	IGNORE scope_stack_check_shadowing(stack, from, rule);
	map->next          = NULL;
	map->from          = from;
	map->to            = entry;
	*stack->head->tail = map;
	stack->head->tail  = &map->next;

	return entry;
}

EntryT *
scope_stack_add_action(ScopeStackT *stack, TableT *table, NStringT *key,
	RuleT *rule, BoolT *found_ref, BoolT ignored)
{
	DStringT        dstring;
	NStringT        nstring;
	EntryT         *entry;
	EntryT         *from;
	ScopeMapEntryT *map;

	*found_ref = FALSE;
	if (!stack->head) {
		if (table_get_action(table, key)) {
			*found_ref = TRUE;
		}

		return table_add_action(table, key, ignored);
	}

	dstring_init(&dstring);
	dstring_append_nstring(&dstring, &stack->head->scope);
	dstring_append_nstring(&dstring, key);
	dstring_to_nstring(&dstring, &nstring);
	dstring_destroy(&dstring);

	entry = table_get_action(table, &nstring);
	if (entry != NULL) {
		*found_ref = TRUE;
		nstring_destroy(&nstring);
		return entry;
	}

	entry = table_add_action(table, &nstring, ignored);
	if (entry == NULL) {
		nstring_destroy(&nstring);
		return NULL;
	}

	from = table_add_name(table, key);
	map  = ALLOCATE(ScopeMapEntryT);

	IGNORE scope_stack_check_shadowing(stack, from, rule);
	map->next          = NULL;
	map->from          = from;
	map->to            = entry;
	*stack->head->tail = map;
	stack->head->tail  = &map->next;

	return entry;
}

EntryT *
scope_stack_add_non_local(ScopeStackT *stack, TableT *table, NStringT *key,
	EntryT *type, RuleT *rule)
{
	DStringT        dstring;
	NStringT        nstring;
	EntryT         *entry;
	EntryT         *from;
	ScopeMapEntryT *map;

	assert(stack->head);
	dstring_init(&dstring);
	dstring_append_nstring(&dstring, &stack->head->scope);
	dstring_append_nstring(&dstring, key);
	dstring_to_nstring(&dstring, &nstring);
	dstring_destroy(&dstring);


	entry = table_add_non_local(table, &nstring, type);
	if (entry == NULL) {
		nstring_destroy(&nstring);
		return NULL;
	}

	from = table_add_name(table, key);
	map  = ALLOCATE(ScopeMapEntryT);

	IGNORE scope_stack_check_shadowing(stack, from, rule);
	map->next          = NULL;
	map->from          = from;
	map->to            = entry;
	*stack->head->tail = map;
	stack->head->tail  = &map->next;

	return entry;
}

EntryT *
scope_stack_get_rule(ScopeStackT *stack, TableT *table, NStringT *key)
{
	EntryT *entry = table_get_entry(table, key);
	ScopeStackFrameT *frame;

	if (!entry) {
		return NULL;
	}

	for (frame = stack->head; frame; frame = frame->next) {
		ScopeMapEntryT *map;

		for (map = frame->head; map; map = map->next) {
			if (map->from != entry) {
				continue;
			}

			if (entry_is_rule(map->to)) {
				return map->to;
			} else {
				return NULL;
			}
		}
	}

	if (entry_is_rule(entry)) {
		return entry;
	}

	return NULL;
}

EntryT *
scope_stack_get_action(ScopeStackT *stack, TableT *table, NStringT *key)
{
	EntryT *entry = table_get_entry(table, key);
	ScopeStackFrameT *frame;

	if (!entry) {
		return NULL;
	}

	for (frame = stack->head; frame; frame = frame->next) {
		ScopeMapEntryT *map;

		for (map = frame->head ; map; map = map->next) {
			if (map->from != entry) {
				continue;
			}

			if (entry_is_action(map->to)) {
				return map->to;
			} else {
				return NULL;
			}
		}
	}

	if (entry_is_action(entry)) {
		return entry;
	}

	return NULL;
}

EntryT *
scope_stack_get_non_local(ScopeStackT *stack, TableT *table, NStringT *key,
	NStringT *scope)
{
	EntryT * entry = table_get_entry(table, key);
	ScopeStackFrameT *frame;

	if (!entry) {
		return NULL;
	}

	for (frame = stack->head ; frame; frame = frame->next) {
		ScopeMapEntryT *map;

		for (map = frame->head; map; map = map->next) {
			if (map->from != entry) {
				continue;
			}

			if (entry_is_non_local(map->to)) {
				nstring_copy(scope, &frame->scope);
				return map->to;
			} else {
				return NULL;
			}
		}
	}

	return NULL;
}

BoolT
scope_stack_check_shadowing(ScopeStackT *stack, EntryT *from, RuleT *rule)
{
	ScopeStackFrameT *frame;

	for (frame = stack->head; frame; frame = frame->next) {
		ScopeMapEntryT *entry;

		for (entry = frame->head; entry; entry = entry->next) {
			if (entry->from == from) {
				error(ERR_SERIOUS, "the name '%K' shadows the non local name '%K' in rule '%N'",
					(void *) entry_key(from), (void *) entry_key(entry->to), rule);
				return TRUE;
			}
		}
	}

	if (entry_is_rule(from) || entry_is_action(from) || entry_is_basic(from)) {
		error(ERR_SERIOUS, "the name '%K' shadows a global name in rule '%N'",
			(void *) entry_key(from), (void *) rule);
		return TRUE;
	}

	return FALSE;
}
