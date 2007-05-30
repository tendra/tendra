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


/*** rule.c --- Rule ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the rule manipulation routines specified.
 *
 *** Change Log:
 * $Log: rule.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1995/02/10  16:29:44  smf
 * Fixed bugs "CR95_111.sid-inline-no-var-check" and "CR95_112.sid-lre-var-call".
 *
 * Revision 1.3  1994/12/15  09:58:56  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.2  1994/08/22  09:37:27  smf
 * Fixed bug DR114:ids-too-long.
 *
 * Revision 1.1.1.1  1994/07/25  16:04:41  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#include "rule.h"
#include "action.h"
#include "basic.h"
#include "name.h"
#include "type.h"

/*--------------------------------------------------------------------------*/

typedef struct DFSClosureT {
    RuleP			root;
    RuleP		       *list;
} DFSClosureT, *DFSClosureP;

/*--------------------------------------------------------------------------*/

static void
rule_compute_minimal_dataflow_1(RuleP rule, AltP alt, TypeTupleP all_used)
{
    TypeTupleT used;

    types_copy(&used, rule_result(rule));
    item_compute_minimal_dataflow(alt_item_head(alt), &used);
    types_add_new_names(all_used, &used, NULL);
    types_destroy(&used);
}

static void
rule_compute_reverse_list_1(AltP alt, EntryP entry, CycleTypeT type)
{
    ItemP item    = alt_item_head(alt);
    ItemP initial = item;
    ItemP next;

    while (item) {
	next = item_next(item);
	if (item_is_rule(item)) {
	    RuleP item_rule = entry_get_rule(item_entry(item));

	    if (((type == CT_LEFT) && (item == initial)) ||
		((type == CT_TAIL) && (next == NULL)) ||
		((type == CT_ALL) && (item_is_inlinable(item)) &&
		 (rule_get_call_count(item_rule) <= 1) &&
		 (!item_is_tail_call(item))) || (type == CT_MUTATE)) {
		entry_list_add_if_missing(rule_reverse_list(item_rule), entry);
	    }
	}
	item = next;
    }
}

static void
rule_compute_dfs_1(AltP alt, CycleTypeT type, RuleP *list)
{
    ItemP item    = alt_item_head(alt);
    ItemP initial = item;
    ItemP next;

    ASSERT(type != CT_MUTATE);
    while (item) {
	next = item_next(item);
	if (item_is_rule(item)) {
	    RuleP item_rule = entry_get_rule(item_entry(item));

	    if (((type == CT_LEFT) && (item == initial)) ||
		((type == CT_TAIL) && (next == NULL)) ||
		((type == CT_ALL) && (item_is_inlinable(item)) &&
		(rule_get_call_count(item_rule) <= 1) &&
		(!item_is_tail_call(item)))) {
		rule_compute_dfs(item_rule, type, list);
	    }
	}
	item = next;
    }
}

static void
rule_compute_reverse_dfs_1(EntryP entry, void * gclosure)
{
    DFSClosureP closure = (DFSClosureP)gclosure;
    RuleP       rule    = entry_get_rule(entry);

    rule_compute_reverse_dfs(rule, closure->root, closure->list);
}

static void
rule_renumber_1(AltP alt, TypeNTransP translator, SaveNTransP state)
{
    ItemP item;

    for (item = alt_item_head(alt); item; item = item_next(item)) {
	types_renumber(item_param(item), translator);
	types_renumber(item_result(item), translator);
    }
    ntrans_restore_state(translator, state);
}

static DFSStateT
rule_get_dfs_state(RuleP rule)
{
    return(rule->dfs_state);
}

static RuleP *
rule_next_in_root_list_ref(RuleP rule)
{
    return(&(rule->next_in_root_list));
}

static void
rule_set_next_in_dfs(RuleP rule1, RuleP rule2)
{
    rule1->next_in_dfs = rule2;
}

static void
rule_set_next_in_reverse_dfs(RuleP rule1,				      RuleP rule2)
{
    rule1->next_in_reverse_dfs = rule2;
}

/*--------------------------------------------------------------------------*/

RuleP
rule_create(EntryP entry)
{
    RuleP rule = ALLOCATE(RuleT);

    rule->entry                 = entry;
    types_init(rule_param(rule));
    types_init(rule_result(rule));
    non_local_list_init(rule_non_locals(rule));
    nstring_init(rule_maximum_scope(rule));
    rule->defined               = FALSE;
    rule->has_empty_alt         = FALSE;
    rule->required              = FALSE;
    entry_list_init(rule_reverse_list(rule));
    rule->dfs_state             = DFS_UNTRACED;
    rule->next_in_reverse_dfs   = NULL;
    rule->no_cycles             = FALSE;
    rule->computed_first_set    = FALSE;
    rule->computing_first_set   = FALSE;
    bitvec_init(rule_first_set(rule));
    entry_list_init(rule_predicate_first(rule));
    rule->see_through           = FALSE;
    rule->priority              = 0;
    rule->factored              = FALSE;
    rule->tail_group		= NULL;
    rule->being_inlined		= FALSE;
    rule->checked_for_inlining	= FALSE;
    entry_list_init(rule_call_list(rule));
    bitvec_init(rule_follow_set(rule));
    entry_list_init(rule_predicate_follow(rule));
    rule->see_through_alt       = NULL;
    rule->needs_function	= FALSE;
    rule->all_basics            = FALSE;
    rule->being_output		= FALSE;
    rule->handler		= NULL;
    rule->alt_head              = NULL;
    rule->alt_tail              = &(rule->alt_head);
    return(rule);
}

void
rule_reinit(RuleP rule)
{
    rule->has_empty_alt         = FALSE;
    rule->alt_head              = NULL;
    rule->alt_tail              = &(rule->alt_head);
}

EntryP
rule_entry(RuleP rule)
{
    return(rule->entry);
}

TypeTupleP
rule_param(RuleP rule)
{
    return(&(rule->param));
}

TypeTupleP
rule_result(RuleP rule)
{
    return(&(rule->result));
}

NonLocalListP
rule_non_locals(RuleP rule)
{
    return(&(rule->non_locals));
}

NStringP
rule_maximum_scope(RuleP rule)
{
    return(&(rule->maximum_scope));
}

BoolT
rule_is_defined(RuleP rule)
{
    return(rule->defined);
}

void
rule_defined(RuleP rule)
{
    rule->defined = TRUE;
}

BoolT
rule_is_required(RuleP rule)
{
    return(rule->required);
}

void
rule_required(RuleP rule)
{
    rule->required = TRUE;
}

void
rule_add_alt(RuleP rule, AltP alt)
{
    *(rule->alt_tail) = alt;
    rule->alt_tail    = alt_next_ref(alt);
}

BoolT
rule_has_empty_alt(RuleP rule)
{
    return(rule->has_empty_alt);
}

void
rule_add_empty_alt(RuleP rule)
{
    rule->has_empty_alt = TRUE;
}

BoolT
rule_has_one_alt(RuleP rule)
{
    return(((rule_has_empty_alt(rule)) && (rule->alt_head == NULL)) ||
	   ((!rule_has_empty_alt(rule)) && (rule->alt_head) &&
	    (alt_next(rule->alt_head) == NULL)));
}

void
rule_compute_result_intersect(RuleP rule)
{
    TypeTupleP result = rule_result(rule);
    BoolT      inited = FALSE;
    AltP       alt;

    if (rule_has_empty_alt(rule)) {
	types_init(result);
    } else {
	if ((alt = rule_get_handler(rule)) != NULL) {
	    types_copy(result, alt_names(alt));
	    inited = TRUE;
	}
	for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
	    if (inited) {
		types_inplace_intersection(result, alt_names(alt));
	    } else {
		types_copy(result, alt_names(alt));
		inited = TRUE;
	    }
	}
	types_unlink_used(result, rule_param(rule));
    }
}

void
rule_compute_minimal_dataflow(RuleP rule, TypeTupleP param)
{
    TypeTupleT all_used;
    AltP       alt;

    types_init(&all_used);
    if ((alt = rule_get_handler(rule)) != NULL) {
	rule_compute_minimal_dataflow_1(rule, alt, &all_used);
    }
    for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
	rule_compute_minimal_dataflow_1(rule, alt, &all_used);
    }
    types_inplace_intersection(rule_param(rule), &all_used);
    types_inplace_intersection(param, &all_used);
    types_destroy(&all_used);
}

void
rule_compute_reverse_list(RuleP rule, CycleTypeT type)
{
    EntryP entry = rule_entry(rule);
    AltP   alt;

    if ((type != CT_LEFT) && (alt = rule_get_handler(rule))) {
	rule_compute_reverse_list_1(alt, entry, type);
    }
    for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
	rule_compute_reverse_list_1(alt, entry, type);
    }
}

void
rule_reinit_reverse_list(RuleP rule)
{
    entry_list_destroy(rule_reverse_list(rule));
    entry_list_init(rule_reverse_list(rule));
    rule_set_dfs_state(rule, DFS_UNTRACED);
    rule->next_in_reverse_dfs = NULL;
    rule->no_cycles           = FALSE;
}

EntryListP
rule_reverse_list(RuleP rule)
{
    return(&(rule->reverse_list));
}

void
rule_set_dfs_state(RuleP rule, DFSStateT state)
{
    rule->dfs_state = state;
}

RuleP
rule_next_in_root_list(RuleP rule)
{
    return(rule->next_in_root_list);
}

void
rule_build_root_list(EntryP entry, void * gclosure)
{
    if (entry_is_rule(entry)) {
	RuleListP list = (RuleListP)gclosure;
	RuleP     rule = entry_get_rule(entry);

	rule_list_append(list, rule, rule_next_in_root_list_ref(rule));
    }
}

RuleP
rule_get_next_in_dfs(RuleP rule)
{
    return(rule->next_in_dfs);
}

void
rule_compute_dfs(RuleP rule, CycleTypeT type, RuleP *list)
{
    AltP      alt;

    switch (rule_get_dfs_state(rule))EXHAUSTIVE {
      case DFS_UNTRACED:
	rule_set_dfs_state(rule, DFS_TRACING);
	if ((type != CT_LEFT) && (alt = rule_get_handler(rule))) {
	    rule_compute_dfs_1(alt, type, list);
	}
	for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
	    rule_compute_dfs_1(alt, type, list);
	}
	rule_set_dfs_state(rule, DFS_TRACED);
	rule_set_next_in_dfs(rule, *list);
	*list = rule;
	break;
      case DFS_TRACING:
      case DFS_TRACED:
	break;
      case DFS_CYCLING:
	UNREACHED;
    }
}

RuleP
rule_get_next_in_reverse_dfs(RuleP rule)
{
    return(rule->next_in_reverse_dfs);
}

RuleP *
rule_next_in_reverse_dfs_ref(RuleP rule)
{
    return(&(rule->next_in_reverse_dfs));
}

void
rule_compute_reverse_dfs(RuleP rule, RuleP root, RuleP *list)
{
    DFSClosureT closure;

    switch (rule_get_dfs_state(rule))EXHAUSTIVE {
      case DFS_UNTRACED:
	closure.root = root;
	closure.list = list;
	rule_set_dfs_state(rule, DFS_TRACING);
	entry_list_iter(rule_reverse_list(rule), rule_compute_reverse_dfs_1,
			(void *)&closure);
	if (((rule == root) && (rule_get_dfs_state(rule) == DFS_CYCLING)) ||
	    (rule != root)) {
	    rule_set_next_in_reverse_dfs(rule, *list);
	    *list = rule;
	}
	rule_set_dfs_state(rule, DFS_TRACED);
	break;
      case DFS_CYCLING:
      case DFS_TRACED:
	break;
      case DFS_TRACING:
	rule_set_dfs_state(rule, DFS_CYCLING);
	break;
    }
}

BoolT
rule_has_no_cycles(RuleP rule)
{
    return(rule->no_cycles);
}

void
rule_no_cycles(RuleP rule)
{
    rule->no_cycles = TRUE;
}

unsigned
rule_get_cycle_index(RuleP rule)
{
    return(rule->cycle_index);
}

void
rule_set_cycle_index(RuleP rule, unsigned cycle_index)
{
    rule->cycle_index = cycle_index;
}

void
rule_reset_cycle_index(RuleP rule)
{
    rule->cycle_index = 0;
}

BoolT
rule_has_computed_first_set(RuleP rule)
{
    return(rule->computed_first_set);
}

void
rule_computed_first_set(RuleP rule)
{
    rule->computed_first_set = TRUE;
}

BoolT
rule_is_computing_first_set(RuleP rule)
{
    return(rule->computing_first_set);
}

void
rule_computing_first_set(RuleP rule)
{
    rule->computing_first_set = TRUE;
}

BitVecP
rule_first_set(RuleP rule)
{
    return(&(rule->first_set));
}

EntryListP
rule_predicate_first(RuleP rule)
{
    return(&(rule->predicate_first));
}

BoolT
rule_is_see_through(RuleP rule)
{
    return(rule->see_through);
}

void
rule_see_through(RuleP rule)
{
    rule->see_through = TRUE;
}

unsigned
rule_get_priority(RuleP rule)
{
    return(rule->priority);
}

void
rule_set_priority(RuleP rule, unsigned priority)
{
    ASSERT(priority > 0);
    rule->priority = priority;
}

BoolT
rule_is_factored(RuleP rule)
{
    return(rule->factored);
}

void
rule_factored(RuleP rule)
{
    rule->factored = TRUE;
}

RuleP
rule_get_tail_group(RuleP rule)
{
    return(rule->tail_group);
}

void
rule_set_tail_group(RuleP rule1, RuleP rule2)
{
    rule1->tail_group = rule2;
}

BoolT
rule_is_being_inlined(RuleP rule)
{
    return(rule->being_inlined);
}

void
rule_being_inlined(RuleP rule)
{
    rule->being_inlined = TRUE;
}

BoolT
rule_is_checked_for_inlining(RuleP rule)
{
    return(rule->checked_for_inlining);
}

void
rule_checked_for_inlining(RuleP rule)
{
    rule->checked_for_inlining = TRUE;
}

EntryListP
rule_call_list(RuleP rule)
{
    return(&(rule->call_list));
}

RuleP
rule_get_next_in_table(RuleP rule)
{
    return(rule->next_in_table);
}

RuleP *
rule_get_next_in_table_ref(RuleP rule)
{
    return(&(rule->next_in_table));
}

void
rule_set_next_in_table(RuleP rule1, RuleP rule2)
{
    rule1->next_in_table = rule2;
}

BitVecP
rule_follow_set(RuleP rule)
{
    return(&(rule->follow_set));
}

EntryListP
rule_predicate_follow(RuleP rule)
{
    return(&(rule->predicate_follow));
}

BoolT
rule_has_started_follows(RuleP rule)
{
    return(rule->started_follows);
}

void
rule_started_follows(RuleP rule)
{
    rule->started_follows = TRUE;
}

void
rule_set_see_through_alt(RuleP rule, AltP alt)
{
    rule->see_through_alt = alt;
}

AltP
rule_see_through_alt(RuleP rule)
{
    return(rule->see_through_alt);
}

BoolT
rule_needs_function(RuleP rule)
{
    return(rule->needs_function);
}

void
rule_will_need_function(RuleP rule)
{
    rule->needs_function = TRUE;
}

BoolT
rule_is_all_basics(RuleP rule)
{
    return(rule->all_basics);
}

void
rule_all_basics(RuleP rule)
{
    rule->all_basics = TRUE;
}

SaveRStackP
rule_rstack_state(RuleP rule)
{
    return(&(rule->rstack_state));
}

SaveRStackP
rule_non_local_state(RuleP rule)
{
    return(&(rule->non_local_state));
}

BoolT
rule_is_being_output(RuleP rule)
{
    return(rule->being_output);
}

void
rule_being_output(RuleP rule)
{
    rule->being_output = TRUE;
}

void
rule_not_being_output(RuleP rule)
{
    rule->being_output = FALSE;
}

unsigned
rule_get_start_label(RuleP rule)
{
    return(rule->start_label);
}

void
rule_set_start_label(RuleP rule, unsigned label)
{
    rule->start_label = label;
}

unsigned
rule_get_call_count(RuleP rule)
{
    return(rule->call_count);
}

void
rule_inc_call_count(RuleP rule)
{
    rule->call_count++;
}

unsigned
rule_get_end_label(RuleP rule)
{
    rule->used_end_label = TRUE;
    return(rule->end_label);
}

void
rule_set_end_label(RuleP rule, unsigned label)
{
    rule->used_end_label = FALSE;
    rule->end_label      = label;
}

BoolT
rule_used_end_label(RuleP rule)
{
    return(rule->used_end_label);
}

unsigned
rule_get_next_label(RuleP rule)
{
    return(rule->next_label);
}

void
rule_set_next_label(RuleP rule, unsigned label)
{
    rule->next_label = label;
}

unsigned
rule_get_handler_label(RuleP rule)
{
    rule->used_handler_label = TRUE;
    return(rule->handler_label);
}

void
rule_set_handler_label(RuleP rule, unsigned label)
{
    rule->used_handler_label = FALSE;
    rule->handler_label      = label;
}

BoolT
rule_used_handler_label(RuleP rule)
{
    return(rule->used_handler_label);
}

AltP
rule_get_handler(RuleP rule)
{
    return(rule->handler);
}

void
rule_set_handler(RuleP rule, AltP handler)
{
    rule->handler = handler;
}

AltP
rule_alt_head(RuleP rule)
{
    return(rule->alt_head);
}

void
rule_renumber(RuleP rule, BoolT do_result, EntryP predicate_id)
{
    TypeNTransT translator;
    SaveNTransT state;
    AltP        alt;

    ntrans_init(&translator);
    (void)ntrans_get_translation(&translator, predicate_id);
    types_renumber(rule_param(rule), &translator);
    if (do_result) {
	types_renumber(rule_result(rule), &translator);
    }
    ntrans_save_state(&translator, &state);
    if ((alt = rule_get_handler(rule)) != NULL) {
	rule_renumber_1(alt, &translator, &state);
    }
    for (alt = rule->alt_head; alt; alt = alt_next(alt)) {
	rule_renumber_1(alt, &translator, &state);
    }
    ntrans_destroy(&translator);
}

void
rule_iter_for_table(RuleP rule, BoolT full, void (*proc)(EntryP, void *),
		    void * closure)
{
    AltP alt;

    if ((alt = rule_get_handler(rule)) != NULL) {
	ItemP item;

	for (item = alt_item_head(alt); item; item = item_next(item)) {
	    entry_iter(item_entry(item), full, proc, closure);
	    if (full) {
		types_iter_for_table(item_param(item), proc, closure);
		types_iter_for_table(item_result(item), proc, closure);
	    }
	}
    }
    for (alt = rule->alt_head; alt; alt = alt_next(alt)) {
	ItemP item;

	for (item = alt_item_head(alt); item; item = item_next(item)) {
	    entry_iter(item_entry(item), full, proc, closure);
	    if (full) {
		types_iter_for_table(item_param(item), proc, closure);
		types_iter_for_table(item_result(item), proc, closure);
	    }
	}
    }
    if (full) {
	non_local_list_iter_for_table(rule_non_locals(rule), proc, closure);
	types_iter_for_table(rule_param(rule), proc, closure);
	types_iter_for_table(rule_result(rule), proc, closure);
    }
}

void
rule_deallocate(RuleP rule)
{
    AltP alt;

    types_destroy(rule_param(rule));
    types_destroy(rule_result(rule));
    non_local_list_destroy(rule_non_locals(rule));
    nstring_destroy(rule_maximum_scope(rule));
    entry_list_destroy(rule_reverse_list(rule));
    bitvec_destroy(rule_first_set(rule));
    entry_list_destroy(rule_predicate_first(rule));
    bitvec_destroy(rule_follow_set(rule));
    entry_list_destroy(rule_predicate_follow(rule));
    entry_list_destroy(rule_call_list(rule));
    if ((alt = rule_get_handler(rule)) != NULL) {
	(void)alt_deallocate(alt);
    }
    for (alt = rule_alt_head(rule); alt; alt = alt_deallocate(alt)) {
	/*NOTHING*/
    }
}

void
write_rule_lhs(OStreamP ostream, RuleP rule)
{
    KeyP key = entry_key(rule_entry(rule));

    write_key(ostream, key);
    write_cstring(ostream, ": ");
    write_type_names(ostream, rule_param(rule), FALSE);
    write_cstring(ostream, " -> ");
    write_type_names(ostream, rule_result(rule), FALSE);
    if (!non_local_list_is_empty(rule_non_locals(rule))) {
	write_cstring(ostream, " [");
	write_newline(ostream);
	write_non_locals(ostream, rule_non_locals(rule));
	write_char(ostream, ']');
    }
    write_cstring(ostream, " = {");
    write_newline(ostream);
}

void
write_rule(OStreamP ostream, RuleP rule)
{
    BoolT need_sep = FALSE;
    AltP  alt;

    write_rule_lhs(ostream, rule);
    if (rule_has_empty_alt(rule)) {
	write_tab(ostream);
	write_cstring(ostream, "$;");
	write_newline(ostream);
	need_sep = TRUE;
    }
    for (alt = rule->alt_head; alt; alt = alt_next(alt)) {
	if (need_sep) {
	    write_cstring(ostream, "    ||");
	    write_newline(ostream);
	}
	write_alt(ostream, alt);
	need_sep = TRUE;
    }
    if ((alt = rule_get_handler(rule)) != NULL) {
	write_cstring(ostream, "    ##");
	write_newline(ostream);
	write_alt(ostream, alt);
    }
    write_cstring(ostream, "};");
    write_newline(ostream);
}

/*--------------------------------------------------------------------------*/

void
rule_list_init(RuleListP list)
{
    list->tail = &(list->head);
}

void
rule_list_append(RuleListP list, RuleP next, RuleP *tail)
{
    *(list->tail) = next;
    list->tail    = tail;
}

void
rule_list_terminate(RuleListP list)
{
    *(list->tail) = NULL;
}

RuleP
rule_list_head(RuleListP list)
{
    return(list->head);
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
