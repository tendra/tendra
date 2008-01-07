/*
 * Copyright (c) 2002-2004, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


/*** rule.c --- Rule ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the rule manipulation routines specified.
 */

#include "rule.h"
#include "action.h"
#include "basic.h"
#include "msgcat.h"
#include "name.h"
#include "type.h"

/*--------------------------------------------------------------------------*/

typedef struct DFSClosureT {
	RuleP			root;
	RuleP		       *list;
} DFSClosureT, *DFSClosureP;

/*--------------------------------------------------------------------------*/

static void
rule_compute_minimal_dataflow_1(RuleP rule,
								AltP alt,
								TypeTupleP all_used)
{
	TypeTupleT used;
	
	types_copy (&used, rule_result (rule));
	item_compute_minimal_dataflow (alt_item_head (alt), &used);
	types_add_new_names (all_used, &used, NIL (EntryP));
	types_destroy (&used);
}

static void
rule_compute_reverse_list_1(AltP alt, EntryP entry,
							CycleTypeT type)
{
	ItemP item    = alt_item_head (alt);
	ItemP initial = item;
	ItemP next;
	
	while (item) {
		next = item_next (item);
		if (item_is_rule (item)) {
			RuleP item_rule = entry_get_rule (item_entry (item));
			
			if (((type == CT_LEFT) && (item == initial)) ||
				((type == CT_TAIL) && (next == NIL (ItemP))) ||
				((type == CT_ALL) && (item_is_inlinable (item)) &&
				 (rule_get_call_count (item_rule) <= 1) &&
				 (!item_is_tail_call (item))) ||
				(type == CT_MUTATE)) {
				entry_list_add_if_missing (rule_reverse_list (item_rule),
										   entry);
			}
		}
		item = next;
	}
}

static void
rule_compute_dfs_1(AltP alt, CycleTypeT type,
				   RuleP *list)
{
	ItemP item    = alt_item_head (alt);
	ItemP initial = item;
	ItemP next;
	
	ASSERT (type != CT_MUTATE);
	while (item) {
		next = item_next (item);
		if (item_is_rule (item)) {
			RuleP item_rule = entry_get_rule (item_entry (item));
			
			if (((type == CT_LEFT) && (item == initial)) ||
				((type == CT_TAIL) && (next == NIL (ItemP))) ||
				((type == CT_ALL) && (item_is_inlinable (item)) &&
				 (rule_get_call_count (item_rule) <= 1) &&
				 (!item_is_tail_call (item)))) {
				rule_compute_dfs (item_rule, type, list);
			}
		}
		item = next;
	}
}

static void
rule_compute_reverse_dfs_1(EntryP entry, void *gclosure)
{
	DFSClosureP closure = (DFSClosureP) gclosure;
	RuleP       rule    = entry_get_rule (entry);
	
	rule_compute_reverse_dfs (rule, closure->root, closure->list);
}

static void
rule_renumber_1(AltP alt, TypeNTransP translator,
				SaveNTransP state)
{
	ItemP item;
	
	for (item = alt_item_head (alt); item; item = item_next (item)) {
		types_renumber (item_param (item), translator);
		types_renumber (item_result (item), translator);
	}
	ntrans_restore_state (translator, state);
}

#ifdef FS_FAST
#undef rule_get_dfs_state
#endif /* defined (FS_FAST) */
static DFSStateT
rule_get_dfs_state(RuleP rule)
{
	return (rule->dfs_state);
}
#ifdef FS_FAST
#define rule_get_dfs_state(r) ((r)->dfs_state)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_next_in_root_list_ref
#endif /* defined (FS_FAST) */
static RuleP *
rule_next_in_root_list_ref(RuleP rule)
{
	return (&(rule->next_in_root_list));
}
#ifdef FS_FAST
#define rule_next_in_root_list_ref(r) (&((r)->next_in_root_list))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_set_next_in_dfs
#endif /* defined (FS_FAST) */
static void
rule_set_next_in_dfs(RuleP rule1, RuleP rule2)
{
	rule1->next_in_dfs = rule2;
}
#ifdef FS_FAST
#define rule_set_next_in_dfs(r1, r2) ((r1)->next_in_dfs = (r2))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_set_next_in_reverse_dfs
#endif /* defined (FS_FAST) */
static void
rule_set_next_in_reverse_dfs(RuleP rule1,
							 RuleP rule2)
{
	rule1->next_in_reverse_dfs = rule2;
}
#ifdef FS_FAST
#define rule_set_next_in_reverse_dfs(r1, r2) ((r1)->next_in_reverse_dfs = (r2))
#endif /* defined (FS_FAST) */

/*--------------------------------------------------------------------------*/

RuleP
rule_create(EntryP entry)
{
	RuleP rule = ALLOCATE (RuleT);
	
	rule->entry                 = entry;
	types_init (rule_param (rule));
	types_init (rule_result (rule));
	non_local_list_init (rule_non_locals (rule));
	nstring_init (rule_maximum_scope (rule));
	rule->defined               = FALSE;
	rule->has_empty_alt         = FALSE;
	rule->required              = FALSE;
	entry_list_init (rule_reverse_list (rule));
	rule->dfs_state             = DFS_UNTRACED;
	rule->next_in_reverse_dfs   = NIL (RuleP);
	rule->no_cycles             = FALSE;
	rule->computed_first_set    = FALSE;
	rule->computing_first_set   = FALSE;
	bitvec_init (rule_first_set (rule));
	entry_list_init (rule_predicate_first (rule));
	rule->see_through           = FALSE;
	rule->priority              = 0;
	rule->factored              = FALSE;
	rule->tail_group		= NIL (RuleP);
	rule->being_inlined		= FALSE;
	rule->checked_for_inlining	= FALSE;
	entry_list_init (rule_call_list (rule));
	bitvec_init (rule_follow_set (rule));
	entry_list_init (rule_predicate_follow (rule));
	rule->see_through_alt       = NIL (AltP);
	rule->needs_function	= FALSE;
	rule->all_basics            = FALSE;
	rule->being_output		= FALSE;
	rule->handler		= NIL (AltP);
	rule->alt_head              = NIL (AltP);
	rule->alt_tail              = &(rule->alt_head);
	return (rule);
}

void
rule_reinit(RuleP rule)
{
	rule->has_empty_alt         = FALSE;
	rule->alt_head              = NIL (AltP);
	rule->alt_tail              = &(rule->alt_head);
}

#ifdef FS_FAST
#undef rule_table_entry
#endif /* defined (FS_FAST) */
EntryP
rule_entry(RuleP rule)
{
	return (rule->entry);
}
#ifdef FS_FAST
#define rule_entry(r) ((r)->entry)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_param
#endif /* defined (FS_FAST) */
TypeTupleP
rule_param(RuleP rule)
{
	return (&(rule->param));
}
#ifdef FS_FAST
#define rule_param(r) (&((r)->param))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_result
#endif /* defined (FS_FAST) */
TypeTupleP
rule_result(RuleP rule)
{
	return (&(rule->result));
}
#ifdef FS_FAST
#define rule_result(r) (&((r)->result))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_non_locals
#endif /* defined (FS_FAST) */
NonLocalListP
rule_non_locals(RuleP rule)
{
	return (&(rule->non_locals));
}
#ifdef FS_FAST
#define rule_non_locals(r) (&((r)->non_locals))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_maximum_scope
#endif /* defined (FS_FAST) */
NStringP
rule_maximum_scope(RuleP rule)
{
	return (&(rule->maximum_scope));
}
#ifdef FS_FAST
#define rule_maximum_scope(r) (&((r)->maximum_scope))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_is_defined
#endif /* defined (FS_FAST) */
BoolT
rule_is_defined(RuleP rule)
{
	return (rule->defined);
}
#ifdef FS_FAST
#define rule_is_defined(r) ((r)->defined)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_defined
#endif /* defined (FS_FAST) */
void
rule_defined(RuleP rule)
{
	rule->defined = TRUE;
}
#ifdef FS_FAST
#define rule_defined(r) ((r)->defined = TRUE)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_is_required
#endif /* defined (FS_FAST) */
BoolT
rule_is_required(RuleP rule)
{
	return (rule->required);
}
#ifdef FS_FAST
#define rule_is_required(r) ((r)->required)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_required
#endif /* defined (FS_FAST) */
void
rule_required(RuleP rule)
{
	rule->required = TRUE;
}
#ifdef FS_FAST
#define rule_required(r) ((r)->required = TRUE)
#endif /* defined (FS_FAST) */

void
rule_add_alt(RuleP rule, AltP alt)
{
	*(rule->alt_tail) = alt;
	rule->alt_tail    = alt_next_ref (alt);
}

#ifdef FS_FAST
#undef rule_has_empty_alt
#endif /* defined (FS_FAST) */
BoolT
rule_has_empty_alt(RuleP rule)
{
	return (rule->has_empty_alt);
}
#ifdef FS_FAST
#define rule_has_empty_alt(r) ((r)->has_empty_alt)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_add_empty_alt
#endif /* defined (FS_FAST) */
void
rule_add_empty_alt(RuleP rule)
{
	rule->has_empty_alt = TRUE;
}
#ifdef FS_FAST
#define rule_add_empty_alt(r) ((r)->has_empty_alt = TRUE)
#endif /* defined (FS_FAST) */

BoolT
rule_has_one_alt(RuleP rule)
{
	return (((rule_has_empty_alt (rule)) && (rule->alt_head == NIL (AltP))) ||
			((!rule_has_empty_alt (rule)) && (rule->alt_head) &&
			 (alt_next (rule->alt_head) == NIL (AltP))));
}

void
rule_compute_result_intersect(RuleP rule)
{
	TypeTupleP result = rule_result (rule);
	BoolT      inited = FALSE;
	AltP       alt;
	
	if (rule_has_empty_alt (rule)) {
		types_init (result);
	} else {
		if ((alt = rule_get_handler (rule)) != NIL (AltP)) {
			types_copy (result, alt_names (alt));
			inited = TRUE;
		}
		for (alt = rule_alt_head (rule); alt; alt = alt_next (alt)) {
			if (inited) {
				types_inplace_intersection (result, alt_names (alt));
			} else {
				types_copy (result, alt_names (alt));
				inited = TRUE;
			}
		}
		types_unlink_used (result, rule_param (rule));
	}
}

void
rule_compute_minimal_dataflow(RuleP rule,
							  TypeTupleP param)
{
	TypeTupleT all_used;
	AltP       alt;
	
	types_init (&all_used);
	if ((alt = rule_get_handler (rule)) != NIL (AltP)) {
		rule_compute_minimal_dataflow_1 (rule, alt, &all_used);
	}
	for (alt = rule_alt_head (rule); alt; alt = alt_next (alt)) {
		rule_compute_minimal_dataflow_1 (rule, alt, &all_used);
	}
	types_inplace_intersection (rule_param (rule), &all_used);
	types_inplace_intersection (param, &all_used);
	types_destroy (&all_used);
}

void
rule_compute_reverse_list(RuleP rule, CycleTypeT type)
{
	EntryP entry = rule_entry (rule);
	AltP   alt;
	
	if ((type != CT_LEFT) && (alt = rule_get_handler (rule))) {
		rule_compute_reverse_list_1 (alt, entry, type);
	}
	for (alt = rule_alt_head (rule); alt; alt = alt_next (alt)) {
		rule_compute_reverse_list_1 (alt, entry, type);
	}
}

void
rule_reinit_reverse_list(RuleP rule)
{
	entry_list_destroy (rule_reverse_list (rule));
	entry_list_init (rule_reverse_list (rule));
	rule_set_dfs_state (rule, DFS_UNTRACED);
	rule->next_in_reverse_dfs = NIL (RuleP);
	rule->no_cycles           = FALSE;
}

#ifdef FS_FAST
#undef rule_reverse_list
#endif /* defined (FS_FAST) */
EntryListP
rule_reverse_list(RuleP rule)
{
	return (&(rule->reverse_list));
}
#ifdef FS_FAST
#define rule_reverse_list(r) ((r)->reverse_list)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_set_dfs_state
#endif /* defined (FS_FAST) */
void
rule_set_dfs_state(RuleP rule, DFSStateT state)
{
	rule->dfs_state = state;
}
#ifdef FS_FAST
#define rule_set_dfs_state(r, s) ((r)->dfs_state = (s))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_next_in_root_list
#endif /* defined (FS_FAST) */
RuleP
rule_next_in_root_list(RuleP rule)
{
	return (rule->next_in_root_list);
}
#ifdef FS_FAST
#define rule_next_in_root_list(r) ((r)->next_in_root_list)
#endif /* defined (FS_FAST) */

void
rule_build_root_list(EntryP entry, void *gclosure)
{
	if (entry_is_rule (entry)) {
		RuleListP list = (RuleListP) gclosure;
		RuleP     rule = entry_get_rule (entry);
		
		rule_list_append (list, rule, rule_next_in_root_list_ref (rule));
	}
}

#ifdef FS_FAST
#undef rule_get_next_in_dfs
#endif /* defined (FS_FAST) */
RuleP
rule_get_next_in_dfs(RuleP rule)
{
	return (rule->next_in_dfs);
}
#ifdef FS_FAST
#define rule_get_next_in_dfs(r) ((r)->next_in_dfs)
#endif /* defined (FS_FAST) */

void
rule_compute_dfs(RuleP rule, CycleTypeT type,
				 RuleP *list)
{
	AltP      alt;
	
	switch (rule_get_dfs_state (rule)) EXHAUSTIVE {
	case DFS_UNTRACED:
		rule_set_dfs_state (rule, DFS_TRACING);
		if ((type != CT_LEFT) && (alt = rule_get_handler (rule))) {
			rule_compute_dfs_1 (alt, type, list);
		}
		for (alt = rule_alt_head (rule); alt; alt = alt_next (alt)) {
			rule_compute_dfs_1 (alt, type, list);
		}
		rule_set_dfs_state (rule, DFS_TRACED);
		rule_set_next_in_dfs (rule, *list);
		*list = rule;
		break;
	case DFS_TRACING:
	case DFS_TRACED:
		break;
	case DFS_CYCLING:
		UNREACHED;
	}
}

#ifdef FS_FAST
#undef rule_get_next_in_reverse_dfs
#endif /* defined (FS_FAST) */
RuleP
rule_get_next_in_reverse_dfs(RuleP rule)
{
	return (rule->next_in_reverse_dfs);
}
#ifdef FS_FAST
#define rule_get_next_in_reverse_dfs(r) ((r)->next_in_reverse_dfs)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_next_in_reverse_dfs_ref
#endif /* defined (FS_FAST) */
RuleP *
rule_next_in_reverse_dfs_ref(RuleP rule)
{
	return (&(rule->next_in_reverse_dfs));
}
#ifdef FS_FAST
#define rule_next_in_reverse_dfs_ref(r) (&((r)->next_in_reverse_dfs))
#endif /* defined (FS_FAST) */

void
rule_compute_reverse_dfs(RuleP rule, RuleP root,
						 RuleP *list)
{
	DFSClosureT closure;
	
	switch (rule_get_dfs_state (rule)) EXHAUSTIVE {
	case DFS_UNTRACED:
		closure.root = root;
		closure.list = list;
		rule_set_dfs_state (rule, DFS_TRACING);
		entry_list_iter (rule_reverse_list (rule),
						 rule_compute_reverse_dfs_1, (void *) &closure);
		if (((rule == root) && (rule_get_dfs_state (rule) == DFS_CYCLING)) ||
			(rule != root)) {
			rule_set_next_in_reverse_dfs (rule, *list);
			*list = rule;
		}
		rule_set_dfs_state (rule, DFS_TRACED);
		break;
	case DFS_CYCLING:
	case DFS_TRACED:
		break;
	case DFS_TRACING:
		rule_set_dfs_state (rule, DFS_CYCLING);
		break;
	}
}

#ifdef FS_FAST
#undef rule_has_no_cycles
#endif /* defined (FS_FAST) */
BoolT
rule_has_no_cycles(RuleP rule)
{
	return (rule->no_cycles);
}
#ifdef FS_FAST
#define rule_has_no_cycles(r) ((r)->no_cycles)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_no_cycles
#endif /* defined (FS_FAST) */
void
rule_no_cycles(RuleP rule)
{
	rule->no_cycles = TRUE;
}
#ifdef FS_FAST
#define rule_no_cycles(r) ((r)->no_cycles = TRUE)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_get_cycle_index
#endif /* defined (FS_FAST) */
unsigned
rule_get_cycle_index(RuleP rule)
{
	return (rule->cycle_index);
}
#ifdef FS_FAST
#define rule_get_cycle_index(r) ((r)->cycle_index)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_set_cycle_index
#endif /* defined (FS_FAST) */
void
rule_set_cycle_index(RuleP rule, unsigned cycle_index)
{
	rule->cycle_index = cycle_index;
}
#ifdef FS_FAST
#define rule_set_cycle_index(r, i) ((r)->cycle_index = (i))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_reset_cycle_index
#endif /* defined (FS_FAST) */
void
rule_reset_cycle_index(RuleP rule)
{
	rule->cycle_index = 0;
}
#ifdef FS_FAST
#define rule_reset_cycle_index(r) ((r)->cycle_index = 0)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_has_computed_first_set
#endif /* defined (FS_FAST) */
BoolT
rule_has_computed_first_set(RuleP rule)
{
	return (rule->computed_first_set);
}
#ifdef FS_FAST
#define rule_has_computed_first_set(r) ((r)->computed_first_set)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_computed_first_set
#endif /* defined (FS_FAST) */
void
rule_computed_first_set(RuleP rule)
{
	rule->computed_first_set = TRUE;
}
#ifdef FS_FAST
#define rule_computed_first_set(r) ((r)->computed_first_set)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_is_computing_first_set
#endif /* defined (FS_FAST) */
BoolT
rule_is_computing_first_set(RuleP rule)
{
	return (rule->computing_first_set);
}
#ifdef FS_FAST
#define rule_is_computing_first_set(r) ((r)->computing_first_set)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_computing_first_set
#endif /* defined (FS_FAST) */
void
rule_computing_first_set(RuleP rule)
{
	rule->computing_first_set = TRUE;
}
#ifdef FS_FAST
#define rule_computing_first_set(r) ((r)->computing_first_set = TRUE)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_first_set
#endif /* defined (FS_FAST) */
BitVecP
rule_first_set(RuleP rule)
{
	return (&(rule->first_set));
}
#ifdef FS_FAST
#define rule_first_set(r) (&((r)->first_set))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_predicate_first
#endif /* defined (FS_FAST) */
EntryListP
rule_predicate_first(RuleP rule)
{
	return (&(rule->predicate_first));
}
#ifdef FS_FAST
#define rule_predicate_first(r) (&((r)->predicate_first))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_is_see_through
#endif /* defined (FS_FAST) */
BoolT
rule_is_see_through(RuleP rule)
{
	return (rule->see_through);
}
#ifdef FS_FAST
#define rule_is_see_through(r) ((r)->see_through)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_see_through
#endif /* defined (FS_FAST) */
void
rule_see_through(RuleP rule)
{
	rule->see_through = TRUE;
}
#ifdef FS_FAST
#define rule_see_through(r) ((r)->see_through = TRUE)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_get_priority
#endif /* defined (FS_FAST) */
unsigned
rule_get_priority(RuleP rule)
{
	return (rule->priority);
}
#ifdef FS_FAST
#define rule_get_priority(r) ((r)->priority)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_set_priority
#endif /* defined (FS_FAST) */
void
rule_set_priority(RuleP rule, unsigned priority)
{
	ASSERT (priority > 0);
	rule->priority = priority;
}
#ifdef FS_FAST
#define rule_set_priority(r, p) ((r)->priority = (p))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_is_factored
#endif /* defined (FS_FAST) */
BoolT
rule_is_factored(RuleP rule)
{
	return (rule->factored);
}
#ifdef FS_FAST
#define rule_is_factored(r) ((r)->factored)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_factored
#endif /* defined (FS_FAST) */
void
rule_factored(RuleP rule)
{
	rule->factored = TRUE;
}
#ifdef FS_FAST
#define rule_factored(r) ((r)->factored = TRUE)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_get_tail_group
#endif /* defined (FS_FAST) */
RuleP
rule_get_tail_group(RuleP rule)
{
	return (rule->tail_group);
}
#ifdef FS_FAST
#define rule_get_tail_group(r) ((r)->tail_group)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_set_tail_group
#endif /* defined (FS_FAST) */
void
rule_set_tail_group(RuleP rule1, RuleP rule2)
{
	rule1->tail_group = rule2;
}
#ifdef FS_FAST
#define rule_set_tail_group(r1, r2) ((r1)->tail_group = (r2))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_is_being_inlined
#endif /* defined (FS_FAST) */
BoolT
rule_is_being_inlined(RuleP rule)
{
	return (rule->being_inlined);
}
#ifdef FS_FAST
#define rule_is_being_inlined(r) ((r)->being_inlined)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_being_inlined
#endif /* defined (FS_FAST) */
void
rule_being_inlined(RuleP rule)
{
	rule->being_inlined = TRUE;
}
#ifdef FS_FAST
#define rule_being_inlined(r) ((r)->being_inlined = TRUE)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_is_checked_for_inlining
#endif /* defined (FS_FAST) */
BoolT
rule_is_checked_for_inlining(RuleP rule)
{
	return (rule->checked_for_inlining);
}
#ifdef FS_FAST
#define rule_is_checked_for_inlining(r) ((r)->checked_for_inlining)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_checked_for_inlining
#endif /* defined (FS_FAST) */
void
rule_checked_for_inlining(RuleP rule)
{
	rule->checked_for_inlining = TRUE;
}
#ifdef FS_FAST
#define rule_checked_for_inlining(r) ((r)->checked_for_inlining = TRUE)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_call_list
#endif /* defined (FS_FAST) */
EntryListP
rule_call_list(RuleP rule)
{
	return (&(rule->call_list));
}
#ifdef FS_FAST
#define rule_call_list(r) (&((r)->call_list))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_get_next_in_table
#endif /* defined (FS_FAST) */
RuleP
rule_get_next_in_table(RuleP rule)
{
	return (rule->next_in_table);
}
#ifdef FS_FAST
#define rule_get_next_in_table(r) ((r)->next_in_table)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_get_next_in_table_ref
#endif /* defined (FS_FAST) */
RuleP *
rule_get_next_in_table_ref(RuleP rule)
{
	return (&(rule->next_in_table));
}
#ifdef FS_FAST
#define rule_get_next_in_table_ref(r) (&((r)->next_in_table))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_set_next_in_table
#endif /* defined (FS_FAST) */
void
rule_set_next_in_table(RuleP rule1, RuleP rule2)
{
	rule1->next_in_table = rule2;
}
#ifdef FS_FAST
#define rule_set_next_in_table(r1, r2) ((r1)->next_in_table = (r2))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_follow_set
#endif /* defined (FS_FAST) */
BitVecP
rule_follow_set(RuleP rule)
{
	return (&(rule->follow_set));
}
#ifdef FS_FAST
#define rule_follow_set(r) (&((r)->follow_set))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_predicate_follow
#endif /* defined (FS_FAST) */
EntryListP
rule_predicate_follow(RuleP rule)
{
	return (&(rule->predicate_follow));
}
#ifdef FS_FAST
#define rule_predicate_follow(r) (&((r)->predicate_follow))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_has_started_follows
#endif /* defined (FS_FAST) */
BoolT
rule_has_started_follows(RuleP rule)
{
	return (rule->started_follows);
}
#ifdef FS_FAST
#define rule_has_started_follows(r) ((r)->started_follows)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_started_follows
#endif /* defined (FS_FAST) */
void
rule_started_follows(RuleP rule)
{
	rule->started_follows = TRUE;
}
#ifdef FS_FAST
#define rule_started_follows(r) ((r)->started_follows = TRUE)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_set_see_through_alt
#endif /* defined (FS_FAST) */
void
rule_set_see_through_alt(RuleP rule, AltP alt)
{
	rule->see_through_alt = alt;
}
#ifdef FS_FAST
#define rule_set_see_through_alt(r, a) ((r)->see_through_alt = (a))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_see_through_alt
#endif /* defined (FS_FAST) */
AltP
rule_see_through_alt(RuleP rule)
{
	return (rule->see_through_alt);
}
#ifdef FS_FAST
#define rule_see_through_alt(r) ((r)->see_through_alt)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_needs_function
#endif /* defined (FS_FAST) */
BoolT
rule_needs_function(RuleP rule)
{
	return (rule->needs_function);
}
#ifdef FS_FAST
#define rule_needs_function(r) ((r)->needs_function)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_will_need_function
#endif /* defined (FS_FAST) */
void
rule_will_need_function(RuleP rule)
{
	rule->needs_function = TRUE;
}
#ifdef FS_FAST
#define rule_will_need_function(r) ((r)->needs_function = TRUE)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_is_all_basics
#endif /* defined (FS_FAST) */
BoolT
rule_is_all_basics(RuleP rule)
{
	return (rule->all_basics);
}
#ifdef FS_FAST
#define rule_is_all_basics(r) ((r)->all_basics)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_all_basics
#endif /* defined (FS_FAST) */
void
rule_all_basics(RuleP rule)
{
	rule->all_basics = TRUE;
}
#ifdef FS_FAST
#define rule_all_basics(r) ((r)->all_basics = TRUE)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_rstack_state
#endif /* defined (FS_FAST) */
SaveRStackP
rule_rstack_state(RuleP rule)
{
	return (&(rule->rstack_state));
}
#ifdef FS_FAST
#define rule_rstack_state(r) (&((r)->rstack_state))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_non_local_state
#endif /* defined (FS_FAST) */
SaveRStackP
rule_non_local_state(RuleP rule)
{
	return (&(rule->non_local_state));
}
#ifdef FS_FAST
#define rule_non_local_state(r) (&((r)->non_local_state))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_is_being_output
#endif /* defined (FS_FAST) */
BoolT
rule_is_being_output(RuleP rule)
{
	return (rule->being_output);
}
#ifdef FS_FAST
#define rule_is_being_output(r) ((r)->being_output)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_being_output
#endif /* defined (FS_FAST) */
void
rule_being_output(RuleP rule)
{
	rule->being_output = TRUE;
}
#ifdef FS_FAST
#define rule_being_output(r) ((r)->being_output = TRUE)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_not_being_output
#endif /* defined (FS_FAST) */
void
rule_not_being_output(RuleP rule)
{
	rule->being_output = FALSE;
}
#ifdef FS_FAST
#define rule_not_being_output(r) ((r)->being_output = FALSE)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_get_start_label
#endif /* defined (FS_FAST) */
unsigned
rule_get_start_label(RuleP rule)
{
	return (rule->start_label);
}
#ifdef FS_FAST
#define rule_get_start_label(r) ((r)->start_label)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_set_start_label
#endif /* defined (FS_FAST) */
void
rule_set_start_label(RuleP rule, unsigned label)
{
	rule->start_label = label;
}
#ifdef FS_FAST
#define rule_set_start_label(r, l) ((r)->start_label = (l))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_get_call_count
#endif /* defined (FS_FAST) */
unsigned
rule_get_call_count(RuleP rule)
{
	return (rule->call_count);
}
#ifdef FS_FAST
#define rule_get_call_count(r) ((r)->call_count)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_inc_call_count
#endif /* defined (FS_FAST) */
void
rule_inc_call_count(RuleP rule)
{
	rule->call_count ++;
}
#ifdef FS_FAST
#define rule_inc_call_count(r) ((r)->call_count ++)
#endif /* defined (FS_FAST) */

unsigned
rule_get_end_label(RuleP rule)
{
	rule->used_end_label = TRUE;
	return (rule->end_label);
}

void
rule_set_end_label(RuleP rule, unsigned label)
{
	rule->used_end_label = FALSE;
	rule->end_label      = label;
}

#ifdef FS_FAST
#undef rule_used_end_label
#endif /* defined (FS_FAST) */
BoolT
rule_used_end_label(RuleP rule)
{
	return (rule->used_end_label);
}
#ifdef FS_FAST
#define rule_used_end_label(r) ((r)->used_end_label)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_get_next_label
#endif /* defined (FS_FAST) */
unsigned
rule_get_next_label(RuleP rule)
{
	return (rule->next_label);
}
#ifdef FS_FAST
#define rule_get_next_label(r) ((r)->next_label)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_set_next_label
#endif /* defined (FS_FAST) */
void
rule_set_next_label(RuleP rule, unsigned label)
{
	rule->next_label = label;
}
#ifdef FS_FAST
#define rule_set_next_label(r, l) ((r)->next_label = (l))
#endif /* defined (FS_FAST) */

unsigned
rule_get_handler_label(RuleP rule)
{
	rule->used_handler_label = TRUE;
	return (rule->handler_label);
}

void
rule_set_handler_label(RuleP rule, unsigned label)
{
	rule->used_handler_label = FALSE;
	rule->handler_label      = label;
}

#ifdef FS_FAST
#undef rule_used_handler_label
#endif /* defined (FS_FAST) */
BoolT
rule_used_handler_label(RuleP rule)
{
	return (rule->used_handler_label);
}
#ifdef FS_FAST
#define rule_used_handler_label(r) ((r)->used_handler_label)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_get_handler
#endif /* defined (FS_FAST) */
AltP
rule_get_handler(RuleP rule)
{
	return (rule->handler);
}
#ifdef FS_FAST
#define rule_get_handler(r) ((r)->handler)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_set_handler
#endif /* defined (FS_FAST) */
void
rule_set_handler(RuleP rule, AltP handler)
{
	rule->handler = handler;
}
#ifdef FS_FAST
#define rule_set_handler(r, a) ((r)->handler = (a))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_alt_head
#endif /* defined (FS_FAST) */
AltP
rule_alt_head(RuleP rule)
{
	return (rule->alt_head);
}
#ifdef FS_FAST
#define rule_alt_head(r) ((r)->alt_head)
#endif /* defined (FS_FAST) */

void
rule_renumber(RuleP rule, BoolT do_result,
			  EntryP predicate_id)
{
	TypeNTransT translator;
	SaveNTransT state;
	AltP        alt;
	
	ntrans_init (&translator);
	(void) ntrans_get_translation (&translator, predicate_id);
	types_renumber (rule_param (rule), &translator);
	if (do_result) {
		types_renumber (rule_result (rule), &translator);
	}
	ntrans_save_state (&translator, &state);
	if ((alt = rule_get_handler (rule)) != NIL (AltP)) {
		rule_renumber_1 (alt, &translator, &state);
	}
	for (alt = rule->alt_head; alt; alt = alt_next (alt)) {
		rule_renumber_1 (alt, &translator, &state);
	}
	ntrans_destroy (&translator);
}

void
rule_iter_for_table(RuleP rule, BoolT full,
	void (*proc) (EntryP, void *), void *closure)
{
	AltP alt;
	
	if ((alt = rule_get_handler (rule)) != NIL (AltP)) {
		ItemP item;
		
		for (item = alt_item_head (alt); item; item = item_next (item)) {
			entry_iter (item_entry (item), full, proc, closure);
			if (full) {
				types_iter_for_table (item_param (item), proc, closure);
				types_iter_for_table (item_result (item), proc, closure);
			}
		}
	}
	for (alt = rule->alt_head; alt; alt = alt_next (alt)) {
		ItemP item;
		
		for (item = alt_item_head (alt); item; item = item_next (item)) {
			entry_iter (item_entry (item), full, proc, closure);
			if (full) {
				types_iter_for_table (item_param (item), proc, closure);
				types_iter_for_table (item_result (item), proc, closure);
			}
		}
	}
	if (full) {
		non_local_list_iter_for_table (rule_non_locals (rule), proc, closure);
		types_iter_for_table (rule_param (rule), proc, closure);
		types_iter_for_table (rule_result (rule), proc, closure);
	}
}

void
rule_deallocate(RuleP rule)
{
	AltP alt;
	
	types_destroy (rule_param (rule));
	types_destroy (rule_result (rule));
	non_local_list_destroy (rule_non_locals (rule));
	nstring_destroy (rule_maximum_scope (rule));
	entry_list_destroy (rule_reverse_list (rule));
	bitvec_destroy (rule_first_set (rule));
	entry_list_destroy (rule_predicate_first (rule));
	bitvec_destroy (rule_follow_set (rule));
	entry_list_destroy (rule_predicate_follow (rule));
	entry_list_destroy (rule_call_list (rule));
	if ((alt = rule_get_handler (rule)) != NIL (AltP)) {
		(void) alt_deallocate (alt);
	}
	for (alt = rule_alt_head (rule); alt; alt = alt_deallocate (alt)) {
		/*NOTHING*/
	}
}

void
write_rule_lhs(OStreamP ostream, RuleP rule)
{
	KeyP key = entry_key (rule_entry (rule));
	
	write_key (ostream, key);
	write_cstring (ostream, ": ");
	write_type_names (ostream, rule_param (rule), FALSE);
	write_cstring (ostream, " -> ");
	write_type_names (ostream, rule_result (rule), FALSE);
	if (!non_local_list_is_empty (rule_non_locals (rule))) {
		write_cstring (ostream, " [");
		write_newline (ostream);
		write_non_locals (ostream, rule_non_locals (rule));
		write_char (ostream, ']');
	}
	write_cstring (ostream, " = {");
	write_newline (ostream);
}

void
write_rule(OStreamP ostream, RuleP rule)
{
	BoolT need_sep = FALSE;
	AltP  alt;
	
	write_rule_lhs (ostream, rule);
	if (rule_has_empty_alt (rule)) {
		write_tab (ostream);
		write_cstring (ostream, "$;");
		write_newline (ostream);
		need_sep = TRUE;
	}
	for (alt = rule->alt_head; alt; alt = alt_next (alt)) {
		if (need_sep) {
			write_cstring (ostream, "    ||");
			write_newline (ostream);
		}
		write_alt (ostream, alt);
		need_sep = TRUE;
	}
	if ((alt = rule_get_handler (rule)) != NIL (AltP)) {
		write_cstring (ostream, "    ##");
		write_newline (ostream);
		write_alt (ostream, alt);
	}
	write_cstring (ostream, "};");
	write_newline (ostream);
}

/*--------------------------------------------------------------------------*/

void
rule_list_init(RuleListP list)
{
	list->tail = &(list->head);
}

void
rule_list_append(RuleListP list, RuleP next,
				 RuleP *tail)
{
	*(list->tail) = next;
	list->tail    = tail;
}

#ifdef FS_FAST
#undef rule_list_terminate
#endif /* defined (FS_FAST) */
void
rule_list_terminate(RuleListP list)
{
	*(list->tail) = NIL (RuleP);
}
#ifdef FS_FAST
#define rule_list_terminate(r) ((*((r)->tail)) = NIL (RuleP))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef rule_list_head
#endif /* defined (FS_FAST) */
RuleP
rule_list_head(RuleListP list)
{
	return (list->head);
}
#ifdef FS_FAST
#define rule_list_head(r) ((r)->head)
#endif /* defined (FS_FAST) */
