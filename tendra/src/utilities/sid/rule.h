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


/*** rule.h --- Rule ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file specifies the interface to the SID rule, alternative and item
 * handling routines.  The actual implementations are spread across a number
 * of files, but are all logically part of the same file.  See the files named
 * in the declarations for more information.
 */

#ifndef H_RULE
#define H_RULE

#include "os-interface.h"
#include "bitvec.h"
#include "dalloc.h"
#include "entry.h"
#include "entry-list.h"
#include "non-local.h"
#include "ostream.h"
#include "rstack.h"
#include "table.h"
#include "types.h"

/*--------------------------------------------------------------------------*/

typedef enum {
	DFS_UNTRACED,
	DFS_TRACING,
	DFS_CYCLING,
	DFS_TRACED
} DFSStateT, *DFSStateP;

typedef enum {
	CT_LEFT,
	CT_TAIL,
	CT_ALL,
	CT_MUTATE
} CycleTypeT, *CycleTypeP;

typedef struct ItemT {
	struct ItemT	       *next;
	TypeTupleT		param;
	TypeTupleT		result;
	EntryTypeT		type;
	EntryP			entry;
	BoolT			inlinable;
	BoolT			tail_call;
} ItemT, *ItemP;

typedef struct AltT {
	struct AltT		*next;
	TypeTupleT		names;
	BitVecT			first_set;
	ItemP			item_head;
	ItemP		       *item_tail;
} AltT, *AltP;

typedef struct RuleT {
	EntryP			entry;
	TypeTupleT		param;
	TypeTupleT		result;
	NonLocalListT		non_locals;
	NStringT		maximum_scope;
	BoolT			defined;
	BoolT			has_empty_alt;
	BoolT			required;
	EntryListT		reverse_list;
	DFSStateT		dfs_state;
	struct RuleT	       *next_in_root_list;
	struct RuleT	       *next_in_dfs;
	struct RuleT	       *next_in_reverse_dfs;
	BoolT			no_cycles;
	unsigned		cycle_index;
	BoolT			computed_first_set;
	BoolT			computing_first_set;
	BitVecT			first_set;
	EntryListT		predicate_first;
	BoolT			see_through;
	unsigned		priority;
	BoolT			factored;
	struct RuleT	       *tail_group;
	BoolT			being_inlined;
	BoolT			checked_for_inlining;
	EntryListT		call_list;
	struct RuleT	       *next_in_table;
	BitVecT			follow_set;
	EntryListT		predicate_follow;
	BoolT			started_follows;
	AltP			see_through_alt;
	BoolT			needs_function;
	BoolT			all_basics;
	SaveRStackT		rstack_state;
	SaveRStackT		non_local_state;
	BoolT			being_output;
	unsigned		start_label;
	unsigned		call_count;
	unsigned		end_label;
	BoolT			used_end_label;
	unsigned		next_label;
	unsigned		handler_label;
	BoolT			used_handler_label;
	AltP			handler;
	AltP			alt_head;
	AltP		       *alt_tail;
} RuleT, *RuleP;

typedef struct RuleListT {
	RuleP			head;
	RuleP		       *tail;
} RuleListT, *RuleListP;

typedef struct FactorClosureT {
	BitVecT			bitvec1;
	BitVecT			bitvec2;
	TableP			table;
	EntryP			predicate_id;
} FactorClosureT, *FactorClosureP;

typedef struct SimpClosureT {
	BoolT			did_inline;
	TableP			table;
} SimpClosureT, *SimpClosureP;

typedef struct ClashListT {
	struct ClashListT	       *next;
	RuleP			rule;
	AltP			alt;
	ItemP			item;
} ClashListT, *ClashListP;

/*--------------------------------------------------------------------------*/

/* Defined in "rule.c": */
RuleP	rule_create(EntryP);
void	rule_reinit(RuleP);
EntryP	rule_entry(RuleP);
TypeTupleP	rule_param(RuleP);
TypeTupleP	rule_result(RuleP);
NonLocalListP	rule_non_locals(RuleP);
NStringP	rule_maximum_scope(RuleP);
BoolT	rule_is_defined(RuleP);
void	rule_defined(RuleP);
void	rule_add_alt(RuleP, AltP);
BoolT	rule_has_empty_alt(RuleP);
void	rule_add_empty_alt(RuleP);
BoolT	rule_has_one_alt(RuleP);
void	rule_compute_result_intersect(RuleP);
void	rule_compute_minimal_dataflow(RuleP, TypeTupleP);
BoolT	rule_is_required(RuleP);
void	rule_required(RuleP);
void	rule_compute_reverse_list(RuleP, CycleTypeT);
void	rule_reinit_reverse_list(RuleP);
EntryListP	rule_reverse_list(RuleP);
void	rule_set_dfs_state(RuleP, DFSStateT);
RuleP	rule_next_in_root_list(RuleP);
void	rule_build_root_list(EntryP, GenericP);
RuleP	rule_get_next_in_dfs(RuleP);
void	rule_compute_dfs(RuleP, CycleTypeT, RuleP *);
RuleP	rule_get_next_in_reverse_dfs(RuleP);
RuleP *	rule_next_in_reverse_dfs_ref(RuleP);
void	rule_compute_reverse_dfs(RuleP, RuleP, RuleP *);
BoolT	rule_has_no_cycles(RuleP);
void	rule_no_cycles(RuleP);
unsigned	rule_get_cycle_index(RuleP);
void	rule_set_cycle_index(RuleP, unsigned);
void	rule_reset_cycle_index(RuleP);
BoolT	rule_has_computed_first_set(RuleP);
void	rule_computed_first_set(RuleP);
BoolT	rule_is_computing_first_set(RuleP);
void	rule_computing_first_set(RuleP);
BitVecP	rule_first_set(RuleP);
EntryListP	rule_predicate_first(RuleP);
BoolT	rule_is_see_through(RuleP);
void	rule_see_through(RuleP);
unsigned	rule_get_priority(RuleP);
void	rule_set_priority(RuleP, unsigned);
BoolT	rule_is_factored(RuleP);
void	rule_factored(RuleP);
RuleP	rule_get_tail_group(RuleP);
void	rule_set_tail_group(RuleP, RuleP);
BoolT	rule_is_being_inlined(RuleP);
void	rule_being_inlined(RuleP);
BoolT	rule_is_checked_for_inlining(RuleP);
void	rule_checked_for_inlining(RuleP);
EntryListP	rule_call_list(RuleP);
RuleP	rule_get_next_in_table(RuleP);
RuleP *	rule_get_next_in_table_ref(RuleP);
void	rule_set_next_in_table(RuleP, RuleP);
BitVecP	rule_follow_set(RuleP);
EntryListP	rule_predicate_follow(RuleP);
BoolT	rule_has_started_follows(RuleP);
void	rule_started_follows(RuleP);
void	rule_set_see_through_alt(RuleP, AltP);
AltP	rule_see_through_alt(RuleP);
BoolT	rule_needs_function(RuleP);
void	rule_will_need_function(RuleP);
BoolT	rule_is_all_basics(RuleP);
void	rule_all_basics(RuleP);
SaveRStackP	rule_rstack_state(RuleP);
SaveRStackP	rule_non_local_state(RuleP);
BoolT	rule_is_being_output(RuleP);
void	rule_being_output(RuleP);
void	rule_not_being_output(RuleP);
unsigned	rule_get_start_label(RuleP);
void	rule_set_start_label(RuleP, unsigned);
unsigned rule_get_call_count(RuleP);
void	rule_inc_call_count(RuleP);
unsigned rule_get_end_label(RuleP);
void	rule_set_end_label(RuleP, unsigned);
BoolT	rule_used_end_label(RuleP);
unsigned rule_get_next_label(RuleP);
void	rule_set_next_label(RuleP, unsigned);
unsigned rule_get_handler_label(RuleP);
void	rule_set_handler_label(RuleP, unsigned);
BoolT	rule_used_handler_label(RuleP);
AltP	rule_get_handler(RuleP);
void	rule_set_handler(RuleP, AltP);
AltP	rule_alt_head(RuleP);
void	rule_renumber(RuleP, BoolT, EntryP);
void	rule_iter_for_table(RuleP, BoolT,
		void (*) (EntryP, GenericP), GenericP);
void	rule_deallocate(RuleP);

void	write_rule_lhs(OStreamP, RuleP);
void	write_rule(OStreamP, RuleP);

void	rule_list_init(RuleListP);
void	rule_list_append(RuleListP, RuleP, RuleP *);
void	rule_list_terminate(RuleListP);
RuleP	rule_list_head(RuleListP);

/* Defined in "rule-check.c": */
void	rule_check_first_set(EntryP, GenericP);
void	rule_compute_follow_set(EntryP, GenericP);
void	rule_compute_see_through_alt(EntryP, GenericP);
void	rule_compute_alt_first_sets(EntryP, GenericP);

void	write_clashes(OStreamP, ClashListP);

/* Defined in "rule-error.c": */
void	rule_compute_error_list(EntryP, GenericP);

/* Defined in "rule-factor.c": */
void	rule_factor(EntryP, GenericP);
void	rule_set_factor_limit(unsigned);

/* Defined in "rule-firsts.c": */
void	rule_compute_first_set_1(RuleP);
void	rule_compute_first_set(EntryP, GenericP);

/* Defined in "rule-lre.c": */
void	rule_remove_left_cycle(RuleP, EntryP, TableP);

/* Defined in "rule-mutate.c": */
void	rule_compute_mutations(EntryP, GenericP);

/* Defined in "rule-name.c": */
void	rule_recompute_alt_names(EntryP, GenericP);

/* Defined in "rule-simp.c": */
void	rule_remove_duplicates(TableP, EntryP);

/* Defined in "rule-tail.c": */
void	rule_handle_tails(RuleP);
void	rule_compute_all_basics(EntryP, GenericP);
void	rule_compute_inlining(EntryP, GenericP);
void	rule_compute_needed_functions(EntryP, GenericP);
void	rule_handle_need_functions(RuleP);
BoolT	rule_get_inline_tail_calls(void);
void	rule_set_inline_tail_calls(BoolT);
void	rule_set_inline_all_basics(BoolT);
void	rule_set_inline_singles(BoolT);
void	rule_set_inline_non_tail_calls(BoolT);
void	rule_set_multiple_inlining(BoolT);

/* Defined in "alt.c": */
AltP	alt_create(void);
AltP	alt_create_merge(ItemP, ItemP, TypeTransP, TableP);
AltP	alt_duplicate(AltP);
BoolT	alt_less_than(AltP, AltP);
BoolT	alt_equal(AltP, AltP);
AltP	alt_next(AltP);
AltP *	alt_next_ref(AltP);
void	alt_set_next(AltP, AltP);
TypeTupleP	alt_names(AltP);
BitVecP	alt_first_set(AltP);
ItemP	alt_item_head(AltP);
ItemP	alt_unlink_item_head(AltP);
void	alt_add_item(AltP, ItemP);
AltP	alt_deallocate(AltP);

void	write_alt(OStreamP, AltP);
void	write_alt_highlighting(OStreamP, AltP, ItemP);

/* Defined in "item.c": */
ItemP	item_create(EntryP);
ItemP	item_duplicate(ItemP);
ItemP	item_duplicate_and_translate(ItemP, TypeTransP, TableP);
void	item_translate_list(ItemP, TypeBTransP);
void	item_to_predicate(ItemP);
ItemP	item_next(ItemP);
ItemP *	item_next_ref(ItemP);
void	item_set_next(ItemP, ItemP);
EntryP	item_entry(ItemP);
void	item_set_entry(ItemP, EntryP);
EntryTypeT item_type(ItemP);
BoolT	item_is_rule(ItemP);
BoolT	item_is_action(ItemP);
BoolT	item_is_predicate(ItemP);
BoolT	item_is_basic(ItemP);
BoolT	item_is_rename(ItemP);
TypeTupleP item_param(ItemP);
void	item_add_param(ItemP, TypeTupleP);
TypeTupleP item_result(ItemP);
void	item_add_result(ItemP, TypeTupleP);
BoolT	item_is_inlinable(ItemP);
void	item_inlinable(ItemP);
BoolT	item_is_tail_call(ItemP);
void	item_tail_call(ItemP);
BoolT	item_names_used_in_list(ItemP, TypeTupleP);
void	item_compute_minimal_dataflow(ItemP, TypeTupleP);
ItemP	item_deallocate(ItemP);

void	write_item(OStreamP, ItemP);

/*--------------------------------------------------------------------------*/

#ifdef FS_FAST
#define rule_entry(r) ((r)->entry)
#define rule_param(r) (&((r)->param))
#define rule_result(r) (&((r)->result))
#define rule_non_locals(r) (&((r)->non_locals))
#define rule_maximum_scope(r) (&((r)->maximum_scope))
#define rule_is_defined(r) ((r)->defined)
#define rule_defined(r) ((r)->defined = TRUE)
#define rule_has_empty_alt(r) ((r)->has_empty_alt)
#define rule_add_empty_alt(r) ((r)->has_empty_alt = TRUE)
#define rule_is_required(r) ((r)->required)
#define rule_required(r) ((r)->required = TRUE)
#define rule_reverse_list(r) (&((r)->reverse_list))
#define rule_set_dfs_state(r, s) ((r)->dfs_state = (s))
#define rule_next_in_root_list(r) ((r)->next_in_root_list)
#define rule_get_next_in_dfs(r) ((r)->next_in_dfs)
#define rule_get_next_in_reverse_dfs(r) ((r)->next_in_reverse_dfs)
#define rule_next_in_reverse_dfs_ref(r) (&((r)->next_in_reverse_dfs))
#define rule_has_no_cycles(r) ((r)->no_cycles)
#define rule_no_cycles(r) ((r)->no_cycles = TRUE)
#define rule_get_cycle_index(r) ((r)->cycle_index)
#define rule_set_cycle_index(r, i) ((r)->cycle_index = (i))
#define rule_reset_cycle_index(r) ((r)->cycle_index = 0)
#define rule_has_computed_first_set(r) ((r)->computed_first_set)
#define rule_computed_first_set(r) ((r)->computed_first_set = TRUE)
#define rule_is_computing_first_set(r) ((r)->computing_first_set)
#define rule_computing_first_set(r) ((r)->computing_first_set = TRUE)
#define rule_first_set(r) (&((r)->first_set))
#define rule_predicate_first(r) (&((r)->predicate_first))
#define rule_is_see_through(r) ((r)->see_through)
#define rule_see_through(r) ((r)->see_through = TRUE)
#define rule_get_priority(r) ((r)->priority)
#define rule_set_priority(r, p) ((r)->priority = (p))
#define rule_is_factored(r) ((r)->factored)
#define rule_factored(r) ((r)->factored = TRUE)
#define rule_get_tail_group(r) ((r)->tail_group)
#define rule_set_tail_group(r1, r2) ((r1)->tail_group = (r2))
#define rule_is_being_inlined(r) ((r)->being_inlined)
#define rule_being_inlined(r) ((r)->being_inlined = TRUE)
#define rule_is_checked_for_inlining(r) ((r)->checked_for_inlining)
#define rule_checked_for_inlining(r) ((r)->checked_for_inlining = TRUE)
#define rule_call_list(r) (&((r)->call_list))
#define rule_get_next_in_table(r) ((r)->next_in_table)
#define rule_get_next_in_table_ref(r) (&((r)->next_in_table))
#define rule_set_next_in_table(r1, r2) ((r1)->next_in_table = (r2))
#define rule_follow_set(r) (&((r)->follow_set))
#define rule_predicate_follow(r) (&((r)->predicate_follow))
#define rule_has_started_follows(r) ((r)->started_follows)
#define rule_started_follows(r) ((r)->started_follows = TRUE)
#define rule_set_all_action_alt(r, a) ((r)->all_action_alt = (a))
#define rule_all_action_alt(r) ((r)->all_action_alt)
#define rule_needs_function(r) ((r)->needs_function)
#define rule_will_need_function(r) ((r)->needs_function = TRUE)
#define rule_is_all_basics(r) ((r)->all_basics)
#define rule_all_basics(r) ((r)->all_basics = TRUE)
#define rule_rstack_state(r) (&((r)->rstack_state))
#define rule_non_local_state(r) (&((r)->non_local_state))
#define rule_is_being_output(r) ((r)->being_output)
#define rule_being_output(r) ((r)->being_output = TRUE)
#define rule_not_being_output(r) ((r)->being_output = FALSE)
#define rule_get_start_label(r) ((r)->start_label)
#define rule_set_start_label(r, l) ((r)->start_label = (l))
#define rule_get_call_count(r) ((r)->call_count)
#define rule_inc_call_count(r) ((r)->call_count ++)
#define rule_used_end_label(r) ((r)->used_end_label)
#define rule_get_next_label(r) ((r)->next_label)
#define rule_set_next_label(r, l) ((r)->next_label = (l))
#define rule_used_handler_label(r) ((r)->used_handler_label)
#define rule_get_handler(r) ((r)->handler)
#define rule_set_handler(r, a) ((r)->handler = (a))
#define rule_alt_head(r) ((r)->alt_head)

#define rule_list_terminate(r) ((*((r)->tail)) = NIL (RuleP))
#define rule_list_head(r) ((r)->head)

#define alt_next(a) ((a)->next)
#define alt_next_ref(a) (&((a)->next))
#define alt_set_next(a1, a2) ((a1)->next = (a2))
#define alt_names(a) (&((a)->names))
#define alt_first_set(a) (&((a)->first_set))
#define alt_item_head(a) ((a)->item_head)

#define item_next(i) ((i)->next)
#define item_next_ref(i) (&((i)->next))
#define item_set_next(i1, i2) ((i1)->next = (i2))
#define item_entry(i) ((i)->entry)
#define item_set_entry(i, e) ((i)->entry = (e))
#define item_type(i) ((i)->type)
#define item_is_rule(i) ((i)->type == ET_RULE)
#define item_is_action(i) ((i)->type == ET_ACTION)
#define item_is_predicate(i) ((i)->type == ET_PREDICATE)
#define item_is_basic(i) ((i)->type == ET_BASIC)
#define item_is_rename(i) ((i)->type == ET_RENAME)
#define item_param(i) (&((i)->param))
#define item_add_param(i, t) (types_assign (&((i)->param), (t)))
#define item_result(i) (&((i)->result))
#define item_add_result(i, t) (types_assign (&((i)->result), (t)))
#define item_is_inlinable(i) ((i)->inlinable)
#define item_inlinable(i) ((i)->inlinable = TRUE)
#define item_is_tail_call(i) ((i)->tail_call)
#define item_tail_call(i) ((i)->tail_call = TRUE)
#endif /* defined (FS_FAST) */

#endif /* !defined (H_RULE) */
