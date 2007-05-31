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
 *
 *** Change Log:
 * $Log: rule.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1994/12/15  09:58:58  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.2  1994/08/22  09:37:29  smf
 * Fixed bug DR114:ids-too-long.
 *
 * Revision 1.1.1.1  1994/07/25  16:04:42  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

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
    TypeTupleT			param;
    TypeTupleT			result;
    EntryTypeT			type;
    EntryP			entry;
    BoolT			inlinable;
    BoolT			tail_call;
} ItemT, *ItemP;

typedef struct AltT {
    struct AltT		       *next;
    TypeTupleT			names;
    BitVecT			first_set;
    ItemP			item_head;
    ItemP		       *item_tail;
} AltT, *AltP;

typedef struct RuleT {
    EntryP			entry;
    TypeTupleT			param;
    TypeTupleT			result;
    NonLocalListT		non_locals;
    NStringT			maximum_scope;
    BoolT			defined;
    BoolT			has_empty_alt;
    BoolT			required;
    EntryListT			reverse_list;
    DFSStateT			dfs_state;
    struct RuleT	       *next_in_root_list;
    struct RuleT	       *next_in_dfs;
    struct RuleT	       *next_in_reverse_dfs;
    BoolT			no_cycles;
    unsigned			cycle_index;
    BoolT			computed_first_set;
    BoolT			computing_first_set;
    BitVecT			first_set;
    EntryListT			predicate_first;
    BoolT			see_through;
    unsigned			priority;
    BoolT			factored;
    struct RuleT	       *tail_group;
    BoolT			being_inlined;
    BoolT			checked_for_inlining;
    EntryListT			call_list;
    struct RuleT	       *next_in_table;
    BitVecT			follow_set;
    EntryListT			predicate_follow;
    BoolT			started_follows;
    AltP			see_through_alt;
    BoolT			needs_function;
    BoolT			all_basics;
    SaveRStackT			rstack_state;
    SaveRStackT			non_local_state;
    BoolT			being_output;
    unsigned			start_label;
    unsigned			call_count;
    unsigned			end_label;
    BoolT			used_end_label;
    unsigned			next_label;
    unsigned			handler_label;
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
extern RuleP		rule_create(EntryP);
extern void		rule_reinit(RuleP);
extern EntryP		rule_entry(RuleP);
extern TypeTupleP	rule_param(RuleP);
extern TypeTupleP	rule_result(RuleP);
extern NonLocalListP	rule_non_locals(RuleP);
extern NStringP		rule_maximum_scope(RuleP);
extern BoolT		rule_is_defined(RuleP);
extern void		rule_defined(RuleP);
extern void		rule_add_alt(RuleP, AltP);
extern BoolT		rule_has_empty_alt(RuleP);
extern void		rule_add_empty_alt(RuleP);
extern BoolT		rule_has_one_alt(RuleP);
extern void		rule_compute_result_intersect(RuleP);
extern void		rule_compute_minimal_dataflow(RuleP, TypeTupleP);
extern BoolT		rule_is_required(RuleP);
extern void		rule_required(RuleP);
extern void		rule_compute_reverse_list(RuleP, CycleTypeT);
extern void		rule_reinit_reverse_list(RuleP);
extern EntryListP	rule_reverse_list(RuleP);
extern void		rule_set_dfs_state(RuleP, DFSStateT);
extern RuleP		rule_next_in_root_list(RuleP);
extern void		rule_build_root_list(EntryP, void *);
extern RuleP		rule_get_next_in_dfs(RuleP);
extern void		rule_compute_dfs(RuleP, CycleTypeT, RuleP *);
extern RuleP		rule_get_next_in_reverse_dfs(RuleP);
extern RuleP	       *rule_next_in_reverse_dfs_ref(RuleP);
extern void		rule_compute_reverse_dfs(RuleP, RuleP, RuleP *);
extern BoolT		rule_has_no_cycles(RuleP);
extern void		rule_no_cycles(RuleP);
extern unsigned		rule_get_cycle_index(RuleP);
extern void		rule_set_cycle_index(RuleP, unsigned);
extern void		rule_reset_cycle_index(RuleP);
extern BoolT		rule_has_computed_first_set(RuleP);
extern void		rule_computed_first_set(RuleP);
extern BoolT		rule_is_computing_first_set(RuleP);
extern void		rule_computing_first_set(RuleP);
extern BitVecP		rule_first_set(RuleP);
extern EntryListP	rule_predicate_first(RuleP);
extern BoolT		rule_is_see_through(RuleP);
extern void		rule_see_through(RuleP);
extern unsigned		rule_get_priority(RuleP);
extern void		rule_set_priority(RuleP, unsigned);
extern BoolT		rule_is_factored(RuleP);
extern void		rule_factored(RuleP);
extern RuleP		rule_get_tail_group(RuleP);
extern void		rule_set_tail_group(RuleP, RuleP);
extern BoolT		rule_is_being_inlined(RuleP);
extern void		rule_being_inlined(RuleP);
extern BoolT		rule_is_checked_for_inlining(RuleP);
extern void		rule_checked_for_inlining(RuleP);
extern EntryListP	rule_call_list(RuleP);
extern RuleP		rule_get_next_in_table(RuleP);
extern RuleP	       *rule_get_next_in_table_ref(RuleP);
extern void		rule_set_next_in_table(RuleP, RuleP);
extern BitVecP		rule_follow_set(RuleP);
extern EntryListP	rule_predicate_follow(RuleP);
extern BoolT		rule_has_started_follows(RuleP);
extern void		rule_started_follows(RuleP);
extern void		rule_set_see_through_alt(RuleP, AltP);
extern AltP		rule_see_through_alt(RuleP);
extern BoolT		rule_needs_function(RuleP);
extern void		rule_will_need_function(RuleP);
extern BoolT		rule_is_all_basics(RuleP);
extern void		rule_all_basics(RuleP);
extern SaveRStackP	rule_rstack_state(RuleP);
extern SaveRStackP	rule_non_local_state(RuleP);
extern BoolT		rule_is_being_output(RuleP);
extern void		rule_being_output(RuleP);
extern void		rule_not_being_output(RuleP);
extern unsigned		rule_get_start_label(RuleP);
extern void		rule_set_start_label(RuleP, unsigned);
extern unsigned		rule_get_call_count(RuleP);
extern void		rule_inc_call_count(RuleP);
extern unsigned		rule_get_end_label(RuleP);
extern void		rule_set_end_label(RuleP, unsigned);
extern BoolT		rule_used_end_label(RuleP);
extern unsigned		rule_get_next_label(RuleP);
extern void		rule_set_next_label(RuleP, unsigned);
extern unsigned		rule_get_handler_label(RuleP);
extern void		rule_set_handler_label(RuleP, unsigned);
extern BoolT		rule_used_handler_label(RuleP);
extern AltP		rule_get_handler(RuleP);
extern void		rule_set_handler(RuleP, AltP);
extern AltP		rule_alt_head(RuleP);
extern void		rule_renumber(RuleP, BoolT, EntryP);
extern void		rule_iter_for_table(RuleP, BoolT,
					    void(*)(EntryP, void *),
					    void *);
extern void		rule_deallocate(RuleP);

extern void		write_rule_lhs(OStreamP, RuleP);
extern void		write_rule(OStreamP, RuleP);

extern void		rule_list_init(RuleListP);
extern void		rule_list_append (RuleListP, RuleP, RuleP *);
extern void		rule_list_terminate(RuleListP);
extern RuleP		rule_list_head(RuleListP);

/* Defined in "rule-check.c": */
extern void		rule_check_first_set(EntryP, void *);
extern void		rule_compute_follow_set(EntryP, void *);
extern void		rule_compute_see_through_alt(EntryP, void *);
extern void		rule_compute_alt_first_sets(EntryP, void *);

extern void		write_clashes(OStreamP, ClashListP);

/* Defined in "rule-error.c": */
extern void		rule_compute_error_list(EntryP, void *);

/* Defined in "rule-factor.c": */
extern void		rule_factor(EntryP, void *);
extern void		rule_set_factor_limit(unsigned);

/* Defined in "rule-firsts.c": */
extern void		rule_compute_first_set_1(RuleP);
extern void		rule_compute_first_set(EntryP, void *);

/* Defined in "rule-lre.c": */
extern void		rule_remove_left_cycle(RuleP, EntryP, TableP);

/* Defined in "rule-mutate.c": */
extern void		rule_compute_mutations(EntryP, void *);

/* Defined in "rule-name.c": */
extern void		rule_recompute_alt_names(EntryP, void *);

/* Defined in "rule-simp.c": */
extern void		rule_remove_duplicates(TableP, EntryP);

/* Defined in "rule-tail.c": */
extern void		rule_handle_tails(RuleP);
extern void		rule_compute_all_basics(EntryP, void *);
extern void		rule_compute_inlining(EntryP, void *);
extern void		rule_compute_needed_functions(EntryP, void *);
extern void		rule_handle_need_functions(RuleP);
extern BoolT		rule_get_inline_tail_calls(void);
extern void		rule_set_inline_tail_calls(BoolT);
extern void		rule_set_inline_all_basics(BoolT);
extern void		rule_set_inline_singles(BoolT);
extern void		rule_set_inline_non_tail_calls(BoolT);
extern void		rule_set_multiple_inlining(BoolT);

/* Defined in "alt.c": */
extern AltP		alt_create(void);
extern AltP		alt_create_merge(ItemP, ItemP, TypeTransP, TableP);
extern AltP		alt_duplicate(AltP);
extern BoolT		alt_less_than(AltP, AltP);
extern BoolT		alt_equal(AltP, AltP);
extern AltP		alt_next(AltP);
extern AltP	       *alt_next_ref(AltP);
extern void		alt_set_next(AltP, AltP);
extern TypeTupleP	alt_names(AltP);
extern BitVecP		alt_first_set(AltP);
extern ItemP		alt_item_head(AltP);
extern ItemP		alt_unlink_item_head(AltP);
extern void		alt_add_item(AltP, ItemP);
extern AltP		alt_deallocate(AltP);

extern void		write_alt(OStreamP, AltP);
extern void		write_alt_highlighting(OStreamP, AltP, ItemP);

/* Defined in "item.c": */
extern ItemP		item_create(EntryP);
extern ItemP		item_duplicate(ItemP);
extern ItemP		item_duplicate_and_translate(ItemP, TypeTransP, TableP);
extern void		item_translate_list(ItemP, TypeBTransP);
extern void		item_to_predicate(ItemP);
extern ItemP		item_next (ItemP);
extern ItemP	       *item_next_ref(ItemP);
extern void		item_set_next(ItemP, ItemP);
extern EntryP		item_entry(ItemP);
extern void		item_set_entry(ItemP, EntryP);
extern EntryTypeT	item_type(ItemP);
extern BoolT		item_is_rule(ItemP);
extern BoolT		item_is_action(ItemP);
extern BoolT		item_is_predicate(ItemP);
extern BoolT		item_is_basic(ItemP);
extern BoolT		item_is_rename(ItemP);
extern TypeTupleP	item_param(ItemP);
extern void		item_add_param(ItemP, TypeTupleP);
extern TypeTupleP	item_result(ItemP);
extern void		item_add_result(ItemP, TypeTupleP);
extern BoolT		item_is_inlinable(ItemP);
extern void		item_inlinable(ItemP);
extern BoolT		item_is_tail_call(ItemP);
extern void		item_tail_call(ItemP);
extern BoolT		item_names_used_in_list(ItemP, TypeTupleP);
extern void		item_compute_minimal_dataflow(ItemP, TypeTupleP);
extern ItemP		item_deallocate(ItemP);

extern void		write_item(OStreamP, ItemP);

#endif /* !defined (H_RULE) */
