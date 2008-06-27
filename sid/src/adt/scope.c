/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/

/*
 * scope.c - Scope stack ADT.
 *
 * This file implements the scope stack manipulation routines.
 */

#include <assert.h>

#include "scope.h"
#include "../gen-errors.h"
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

	(void) scope_stack_check_shadowing(stack, from, rule);
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
	dstring_append_nstring(&dstring, &(stack->head->scope));
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
		return(NULL);
	}

	from = table_add_name(table, key);
	map  = ALLOCATE(ScopeMapEntryT);

	(void) scope_stack_check_shadowing(stack, from, rule);
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
	dstring_append_nstring(&dstring, &(stack->head->scope));
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

	(void) scope_stack_check_shadowing(stack, from, rule);
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
				E_shadows_non_local(entry_key(from), entry_key(entry->to), rule);
				return TRUE;
			}
		}
	}

	if (entry_is_rule(from) || entry_is_action(from) || entry_is_basic(from)) {
		E_shadows_global(entry_key(from), rule);
		return TRUE;
	}

	return FALSE;
}

