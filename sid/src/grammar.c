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
 * grammar.c - Grammar transforms frontend.
 *
 * This file implements the SID transformation front-end routines.
 *
 * Before any of these routines are called, the grammar should have been read
 * in by the parser.  The functions should be called in the following order.
 *
 *	``grammar_check_complete''
 *
 * This function traces the grammar that is accessible from the entry points,
 * and ensures that there are no unused rules, basics, actions or types, and
 * that all of the rules are defined.
 *
 *	``grammar_remove_left_recursion''
 *
 * This function applies several functions from the file "rule.c" to the rules
 * in the grammar, to detect left cycles (this is done by the
 * "grammar_find_cycles" function).  When such a cycle is found, it calls
 * ``rule_remove_left_cycle'' (defined in the file "rule-lre.c") to remove the
 * cycle.  The function removes any left recursion from the rules, replacing
 * it with a right recursive equivalent.  See the file "rule-lre.c" for more
 * details.
 *
 * The cycle detection algorithm works as follows: firstly a list of rules is
 * built by the function ``rule_build_root_list''; this list acts as the root
 * node of the graph.  The remainder of the graph is built up from the
 * leftmost rule invocations (if any) in each alternative of each production.
 * This graph is depth first searched by the function ``rule_compute_dfs'', to
 * produce an ordered list of productions.  The reverse graph (which is
 * computed by applying the function ``rule_compute_reverse_list'' to each
 * production, at the same time as the dfs is being performed) is then depth
 * first searched in the order specified by the list, using the function
 * ``rule_compute_reverse_dfs''.  The result of this is the set of left
 * cycles.  The algorithm is explained fully in {"Data Structures and
 * Algorithms"; Aho, Hopcroft, Ullman; Addison Wesley; ISBN 0-201-00023-7;
 * page 222}.
 *
 *	``grammar_compute_first_sets''
 *
 * This function applies the ``rule_compute_first_set'' function to all rules
 * in the grammar.  The function computes the first set for each rule.  It
 * also computes a priority for the rule, and whether the rule is see through
 * or not.  See the file "rule-first.c" for more details.
 *
 *	``grammar_factor''
 *
 * This function applies the ``rule_factor'' function to all of the rules in
 * the grammar.  The function does a number of transformations on the rules to
 * make them more likely to be LL(1).  See the file "rule-factor.c" for more
 * details.
 *
 *	``grammar_simplify''
 *
 * This function calls the ``rule_remove_duplicates'' function on the grammar,
 * to remove any rules that have identical form.  See the file "rule-simp.c"
 * for more details.
 *
 *	``grammar_compute_inlining''
 *
 * This function applies a number of functions to the rules in the grammar in
 * order to indicate which rules should be inlined during the output phase.
 * See the file "rule-tail.c" for more details.
 *
 *	``grammar_check_collisions''
 *
 * This function applies a number of functions to the rules in the grammar in
 * order to check that the grammar is valid.  It also causes the first sets
 * for all of the alternatives within a rule to be calculated, and if there is
 * a see through alternative.  See the file "rule-check.c" for more details.
 *
 *	``grammar_recompute_alt_names''
 *
 * This function applies the ``rule_recompute_alt_names'' function to all
 * rules in the grammar.  The function recomputes the identifier names that
 * are used within each alternative of the rule.  See the file "rule-names.c"
 * for more details.
 *
 *	``grammar_compute_mutations''
 *
 * This function applies the ``rule_compute_mutations'' function to all rules
 * in the grammar.  The function computes the mutation effects from actions
 * that mutate their parameters.  See the file "rule-mutate.c" for more
 * details.
 */

#include <limits.h>
#include <stddef.h>

#include "grammar.h"
#include "action.h"
#include "basic.h"
#include "gen-errors.h"
#include "name.h"
#include "rules/rule.h"
#include "type.h"

static void
grammar_trace_ignored(EntryT * entry, void * gclosure)
{
    UNUSED(gclosure);
    if (entry_is_basic(entry)) {
	BasicT * basic = entry_get_basic(entry);

	if (basic_get_ignored(basic)) {
	    entry_iter(entry, TRUE, NULL, NULL);
	}
    }
}

static void
grammar_check_1(EntryT * entry, void * gclosure)
{
    UNUSED(gclosure);
    switch (entry_type(entry))EXHAUSTIVE {
      case ET_RULE:
	if (!rule_is_defined(entry_get_rule(entry))) {
	    E_rule_not_defined(entry_key(entry));
	}
	if (!entry_is_traced(entry)) {
	    E_rule_not_used(entry_key(entry));
	}
	break;
      case ET_BASIC:
	if (!entry_is_traced(entry)) {
	    E_basic_not_used(entry_key(entry));
	}
	break;
      case ET_ACTION:
	if (!entry_is_traced(entry)) {
	    E_action_not_used(entry_key(entry));
	}
	break;
      case ET_TYPE:
	if (!entry_is_traced(entry)) {
	    E_type_not_used(entry_key(entry));
	}
	break;
      case ET_NON_LOCAL:
	if (!entry_is_traced(entry)) {
	    E_non_local_not_used(entry_key(entry));
	}
	break;
      case ET_NAME:
      case ET_RENAME:
	break;
      case ET_PREDICATE:
	UNREACHED;
    }
}

static void
grammar_find_cycles(GrammarT * grammar, CycleTypeT type)
{
    TableT *     table         = grammar_table(grammar);
    EntryT *     predicate_id  = grammar_get_predicate_id(grammar);
    RuleT *      dfs_list_head = NULL;
    RuleListT  root_list;
    RuleT *      rule;

    rule_list_init(&root_list);
    table_iter(table, rule_build_root_list, &root_list);
    rule_list_terminate(&root_list);
    for (rule = rule_list_head(&root_list); rule;
	 rule = rule_next_in_root_list(rule)) {
	rule_compute_reverse_list(rule, type);
	rule_compute_dfs(rule, type, &dfs_list_head);
    }
    for (rule = rule_list_head(&root_list); rule;
	 rule = rule_next_in_root_list(rule)) {
	rule_set_dfs_state(rule, DFS_UNTRACED);
    }
    for (rule = dfs_list_head; rule; rule = rule_get_next_in_dfs(rule)) {
	if (!rule_has_no_cycles(rule)) {
	    RuleT * reverse_dfs_list_head = NULL;

	    rule_compute_reverse_dfs(rule, rule, &reverse_dfs_list_head);
	    if (reverse_dfs_list_head) {
		switch (type)EXHAUSTIVE {
		  case CT_LEFT:
		    rule_remove_left_cycle(reverse_dfs_list_head,
					    predicate_id, table);
		    break;
		  case CT_TAIL:
		    rule_handle_tails(reverse_dfs_list_head);
		    break;
		  case CT_ALL:
		    rule_handle_need_functions(reverse_dfs_list_head);
		    break;
		  case CT_MUTATE:
		    UNREACHED;
		}
	    }
	}
    }
    for (rule = rule_list_head(&root_list); rule;
	 rule = rule_next_in_root_list(rule)) {
	rule_reinit_reverse_list(rule);
    }
}

static void
write_grammar_1(EntryT * entry, void * gclosure)
{
    OStreamT * ostream = (OStreamT *)gclosure;

    if (entry_is_rule(entry)) {
	write_rule(ostream, entry_get_rule(entry));
	write_newline(ostream);
    }
}

/*
 * Externally visible functions
 */

void
grammar_init(GrammarT * grammar)
{
    TableT * table = grammar_table(grammar);

    table_init(table);
    entry_list_init(grammar_entry_list(grammar));
    grammar->terminal       = 0;
    grammar->predicate_type = NULL;
    grammar->predicate_id   = table_add_generated_name(table);
}

TableT *
grammar_table(GrammarT * grammar)
{
    return(&(grammar->table));
}

EntryListT *
grammar_entry_list(GrammarT * grammar)
{
    return(&(grammar->entry_list));
}

unsigned
grammar_max_terminal(GrammarT * grammar)
{
    return(grammar->terminal);
}

unsigned
grammar_next_terminal(GrammarT * grammar)
{
    if (grammar->terminal == UINT_MAX) {
	E_too_many_terminals();
	UNREACHED;
    }
    return(grammar->terminal++);
}

EntryT *
grammar_get_predicate_type(GrammarT * grammar)
{
    return(grammar->predicate_type);
}

void
grammar_set_predicate_type(GrammarT * grammar, EntryT * type)
{
    grammar->predicate_type = type;
}

EntryT *
grammar_get_predicate_id(GrammarT * grammar)
{
    return(grammar->predicate_id);
}

void
grammar_check_complete(GrammarT * grammar)
{
    TableT *     table      = grammar_table(grammar);
    EntryListT * entry_list = grammar_entry_list(grammar);

    table_untrace(table);
    entry_list_iter_table(entry_list, TRUE, NULL, NULL);
    table_iter(table, grammar_trace_ignored, NULL);
    table_iter(table, grammar_check_1, NULL);
}

void
grammar_remove_left_recursion(GrammarT * grammar)
{
    grammar_find_cycles(grammar, CT_LEFT);
}

void
grammar_compute_first_sets(GrammarT * grammar)
{
    TableT * table = grammar_table(grammar);

    table_iter(table, rule_compute_first_set, NULL);
}

void
grammar_factor(GrammarT * grammar)
{
    TableT *         table      = grammar_table(grammar);
    EntryListT *     entry_list = grammar_entry_list(grammar);
    FactorClosureT closure;

    bitvec_init(&(closure.bitvec1));
    bitvec_init(&(closure.bitvec2));
    closure.table        = table;
    closure.predicate_id = grammar_get_predicate_id(grammar);
    table_untrace(table);
    entry_list_iter_table(entry_list, FALSE, rule_factor, &closure);
    table_unlink_untraced_rules(table);
    bitvec_destroy(&(closure.bitvec1));
    bitvec_destroy(&(closure.bitvec2));
}

void
grammar_simplify(GrammarT * grammar)
{
    TableT *       table        = grammar_table(grammar);
    EntryListT *   entry_list   = grammar_entry_list(grammar);
    EntryT *       predicate_id = grammar_get_predicate_id(grammar);

    rule_remove_duplicates(table, predicate_id);
    table_untrace(table);
    entry_list_iter_table(entry_list, FALSE, NULL, NULL);
    table_unlink_untraced_rules(table);
}

void
grammar_compute_inlining(GrammarT * grammar)
{
    TableT *     table         = grammar_table(grammar);

    if (rule_get_inline_tail_calls()) {
	grammar_find_cycles(grammar, CT_TAIL);
    }
    table_iter(table, rule_compute_all_basics, NULL);
    table_iter(table, rule_compute_inlining, NULL);
    table_iter(table, rule_compute_needed_functions, NULL);
    grammar_find_cycles(grammar, CT_ALL);
}

void
grammar_check_collisions(GrammarT * grammar)
{
    TableT * table = grammar_table(grammar);

    table_iter(table, rule_check_first_set, grammar);
    table_iter(table, rule_compute_follow_set, grammar);
    table_iter(table, rule_compute_see_through_alt, NULL);
    table_iter(table, rule_compute_alt_first_sets, NULL);
}

void
grammar_recompute_alt_names(GrammarT * grammar)
{
    TableT * table        = grammar_table(grammar);
    EntryT * predicate_id = grammar_get_predicate_id(grammar);

    table_iter(table, rule_recompute_alt_names, predicate_id);
}

void
grammar_compute_mutations(GrammarT * grammar)
{
    TableT *    table = grammar_table(grammar);
    RuleListT root_list;
    RuleT *     rule;

    rule_list_init(&root_list);
    table_iter(table, rule_build_root_list, &root_list);
    rule_list_terminate(&root_list);
    for (rule = rule_list_head(&root_list); rule;
	 rule = rule_next_in_root_list(rule)) {
	rule_compute_reverse_list(rule, CT_MUTATE);
    }
    table_iter(table, rule_compute_mutations, NULL);
    for (rule = rule_list_head(&root_list); rule;
	 rule = rule_next_in_root_list(rule)) {
	rule_reinit_reverse_list(rule);
    }
}

void
write_grammar(OStreamT * ostream, GrammarT * grammar)
{
    TableT *     table      = grammar_table(grammar);
    EntryListT * entry_list = grammar_entry_list(grammar);

    table_untrace(table);
    entry_list_iter_table(entry_list, FALSE, write_grammar_1,
			  ostream);
}
