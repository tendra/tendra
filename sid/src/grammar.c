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
 * See the file "grammar.h" for more information.
 */

#include <exds/common.h>
#include <limits.h>
#include <stddef.h>

#include "shared/check/check.h"
#include "shared/error/error.h"
#include "grammar.h"
#include "adt/action.h"
#include "adt/basic.h"
#include "adt/name.h"
#include "adt/rule.h"
#include "adt/type.h"

static void
grammar_trace_ignored(EntryT *entry, void *gclosure)
{
	UNUSED(gclosure);
	switch (entry_type(entry)) EXHAUSTIVE {
	case ET_BASIC: {
			BasicT *basic = entry_get_basic(entry);

			if (basic_get_ignored(basic)) {
				entry_iter(entry, TRUE, NULL, NULL);
			}
		}
		break;

	case ET_ACTION: {
			ActionT *action = entry_get_action(entry);

			if (action_get_ignored(action)) {
				entry_iter(entry, TRUE, NULL, NULL);
			}
		}
		break;

	case ET_TYPE:
	case ET_RULE:
	case ET_NAME:
	case ET_RENAME:
	case ET_PREDICATE:
	case ET_NON_LOCAL:
		break;
	}
}

static void
grammar_check_1(EntryT *entry, void *gclosure)
{
	UNUSED(gclosure);
	switch (entry_type(entry)) EXHAUSTIVE {
	case ET_RULE:
		if (!rule_is_defined(entry_get_rule(entry))) {
			error(ERROR_SERIOUS, "rule '%K' is never defined",
				(void *) entry_key(entry));
		}

		if (!entry_is_traced(entry)) {
			error(ERROR_SERIOUS, "rule '%K' is never used",
				(void *) entry_key(entry));
		}
		break;

	case ET_BASIC:
		/*
		 * Note that we do not consider use of basics in action blocks (that is
		 * by the @$basic-name construct) as "used", since that is a language-
		 * specific construct. Usage in the grammatical sense must still hold
		 * true even with no action file.
		 */
		if (!entry_is_traced(entry)) {
			error(ERROR_SERIOUS, "basic '%K' is never used",
				(void *) entry_key(entry));
		}
		break;

	case ET_ACTION:
		if (!entry_is_traced(entry)) {
			error(ERROR_SERIOUS, "action '%K' is never used",
				(void *) entry_key(entry));
		}
		break;

	case ET_TYPE:
		if (!entry_is_traced(entry) && !type_get_ignored(entry_get_type(entry))) {
			error(ERROR_SERIOUS, "type '%K' is never used",
				(void *) entry_key(entry));
		}
		break;

	case ET_NON_LOCAL:
		if (!entry_is_traced(entry)) {
			error(ERROR_SERIOUS, "non-local name '%K' is never used",
				(void *) entry_key(entry));
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
grammar_find_cycles(GrammarT *grammar, CycleTypeT type)
{
	TableT *table         = grammar_table(grammar);
	EntryT *predicate_id  = grammar_get_predicate_id(grammar);
	RuleT  *dfs_list_head = NULL;
	RuleListT  root_list;
	RuleT  *rule;

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
		RuleT *reverse_dfs_list_head;

		if (rule_has_no_cycles(rule)) {
			continue;
		}

		reverse_dfs_list_head = NULL;

		rule_compute_reverse_dfs(rule, rule, &reverse_dfs_list_head);
		if (!reverse_dfs_list_head) {
			continue;
		}

		switch (type) EXHAUSTIVE {
		case CT_LEFT:
			rule_remove_left_cycle(reverse_dfs_list_head, predicate_id, table);
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

	for (rule = rule_list_head(&root_list); rule;
		rule = rule_next_in_root_list(rule)) {
		rule_reinit_reverse_list(rule);
	}
}

static void
write_grammar_1(EntryT *entry, void *gclosure)
{
	OStreamT *ostream = (OStreamT *) gclosure;

	if (entry_is_rule(entry)) {
		write_rule(ostream, entry_get_rule(entry));
		write_newline(ostream);
	}
}


/*
 * Externally visible functions
 */

void
grammar_init(GrammarT *grammar)
{
	TableT *table = grammar_table(grammar);

	table_init(table);
	entry_list_init(grammar_entry_list(grammar));
	grammar->terminal       = 0;
	grammar->predicate_type = NULL;
	grammar->predicate_id   = table_add_generated_name(table);
}

TableT *
grammar_table(GrammarT *grammar)
{
	return &grammar->table;
}

EntryListT *
grammar_entry_list(GrammarT *grammar)
{
	return &grammar->entry_list;
}

unsigned
grammar_max_terminal(GrammarT *grammar)
{
	return grammar->terminal;
}

unsigned
grammar_next_terminal(GrammarT *grammar)
{
	if (grammar->terminal == UINT_MAX) {
		error(ERROR_FATAL, "too many terminals in grammar");
		UNREACHED;
	}

	return grammar->terminal++;
}

EntryT *
grammar_get_predicate_type(GrammarT *grammar)
{
	return grammar->predicate_type;
}

void
grammar_set_predicate_type(GrammarT *grammar, EntryT *type)
{
	grammar->predicate_type = type;
}

EntryT *
grammar_get_predicate_id(GrammarT *grammar)
{
	return grammar->predicate_id;
}

void
grammar_check_complete(GrammarT *grammar)
{
	TableT     *table      = grammar_table(grammar);
	EntryListT *entry_list = grammar_entry_list(grammar);

	table_untrace(table);
	entry_list_iter_table(entry_list, TRUE, NULL, NULL);
	table_iter(table, grammar_trace_ignored, NULL);
	table_iter(table, grammar_check_1, NULL);
}

void
grammar_remove_left_recursion(GrammarT *grammar)
{
	grammar_find_cycles(grammar, CT_LEFT);
}

void
grammar_compute_first_sets(GrammarT *grammar)
{
	TableT *table = grammar_table(grammar);

	table_iter(table, rule_compute_first_set, NULL);
}

void
grammar_factor(GrammarT *grammar)
{
	TableT     *table      = grammar_table(grammar);
	EntryListT *entry_list = grammar_entry_list(grammar);
	FactorClosureT closure;

	bitvec_init(&closure.bitvec1);
	bitvec_init(&closure.bitvec2);
	closure.table = table;
	closure.predicate_id = grammar_get_predicate_id(grammar);
	table_untrace(table);
	entry_list_iter_table(entry_list, FALSE, rule_factor, &closure);
	table_unlink_untraced_rules(table);
	bitvec_destroy(&closure.bitvec1);
	bitvec_destroy(&closure.bitvec2);
}

void
grammar_simplify(GrammarT *grammar)
{
	TableT     *table        = grammar_table(grammar);
	EntryListT *entry_list   = grammar_entry_list(grammar);
	EntryT     *predicate_id = grammar_get_predicate_id(grammar);

	rule_remove_duplicates(table, predicate_id);
	table_untrace(table);
	entry_list_iter_table(entry_list, FALSE, NULL, NULL);
	table_unlink_untraced_rules(table);
}

void
grammar_compute_inlining(GrammarT *grammar)
{
	TableT *table         = grammar_table(grammar);

	if (rule_get_inline_tail_calls()) {
		grammar_find_cycles(grammar, CT_TAIL);
	}

	table_iter(table, rule_compute_all_basics, NULL);
	table_iter(table, rule_compute_inlining, NULL);
	table_iter(table, rule_compute_needed_functions, NULL);
	grammar_find_cycles(grammar, CT_ALL);
}

void
grammar_check_collisions(GrammarT *grammar)
{
	TableT *table = grammar_table(grammar);

	table_iter(table, rule_check_first_set, grammar);
	table_iter(table, rule_compute_follow_set, grammar);
	table_iter(table, rule_compute_see_through_alt, NULL);
	table_iter(table, rule_compute_alt_first_sets, NULL);
}

void
grammar_recompute_alt_names(GrammarT *grammar)
{
	TableT *table        = grammar_table(grammar);
	EntryT *predicate_id = grammar_get_predicate_id(grammar);

	table_iter(table, rule_recompute_alt_names, predicate_id);
}

void
grammar_compute_mutations(GrammarT *grammar)
{
	TableT    *table = grammar_table(grammar);
	RuleListT  root_list;
	RuleT     *rule;

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
write_grammar(OStreamT *ostream, GrammarT *grammar)
{
	TableT     *table      = grammar_table(grammar);
	EntryListT *entry_list = grammar_entry_list(grammar);

	table_untrace(table);
	entry_list_iter_table(entry_list, FALSE, write_grammar_1, ostream);
}

