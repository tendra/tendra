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


/*** rule-tail.c --- Tail recursion elimination routines.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the SID inlining routines.
 *
 * There are five separate phases implemented in this file.
 *
 * The first phase is to find and eliminate all tail recursive cycles that
 * each rule is involved in.  The cycles are detected by the
 * ``grammar_compute_inlining'' function in the file "grammar.c".  For each
 * cyclic group that is found, the ``rule_handle_tails'' function is called to
 * remove the cycle.  All rules in the cycle are marked as being cyclic, and
 * are given a unique identification that is the same for all members of the
 * cycle (but different for members of different cycles).  The tail recursive
 * calls are marked as inlinable and tail recursive, and the rules' call
 * graphs are computed (this is the set of rules that will make tail calls).
 * This phase is only performed if tail recursion inlining is enabled.
 *
 * The second phase is implemented by the ``rule_compute_all_basics''
 * function.  This marks a rule that only contains basics as such.  This phase
 * is only performed if all basic inlining is enabled.
 *
 * The third phase is implemented by the ``rule_compute_inlining'' function.
 * This marks all calls to all basic rules as inlinable.  If single
 * alternative rule inlining is enabled, then all calls to single alternative
 * rules are marked as inlinable.  If non tail recursion inlining is enabled,
 * it also marks all other calls as inlinable, and computes their call count
 * if functions that are called more than once are not to be inlined (the
 * output routines won't inline rules with a call count greater than one).
 *
 * The fourth phase is implemented by the ``rule_compute_needed_functions''
 * function.  It marks all required functions, and functions that are called
 * from a non-inlinable position as requiring function implementations.
 *
 * The final phase is implemented by the ``rule_handle_need_functions''
 * function.  The cycle detection routines are used in the
 * ``grammar_compute_inlining'' function to find cycles in the function call
 * graph.  If any such cycles are found, then all of the rules in the cycle
 * are marked as needing a function implementation.
 *
 *** Change Log:
 * $Log: rule-tail.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1994/12/15  09:58:53  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.2  1994/11/11  11:47:09  smf
 * Fixed a bug in the tail recursion elimination, for bug fix
 * CR94_127.sid-tail-rec.
 * There was a problem with tail calls that had reference parameters in an
 * earlier version of SID, and they had been disabled.  This should have been
 * fixed when the output routines were fixed to do references properly, but the
 * check wasn't removed.  It has been now.
 *
 * Revision 1.1.1.1  1994/07/25  16:04:41  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#include "rule.h"
#include "action.h"
#include "basic.h"
#include "entry-list.h"
#include "name.h"
#include "type.h"

/*--------------------------------------------------------------------------*/

typedef struct CycleHeadT {
    RuleP			head;
    RuleP		       *tail;
} CycleHeadT, *CycleHeadP;

typedef struct RuleStackT {
    struct RuleStackT	       *next;
    RuleP			rule;
} RuleStackT, *RuleStackP;

/*--------------------------------------------------------------------------*/

static BoolT	rule_do_inline_tail_calls     = TRUE;
static BoolT	rule_do_inline_all_basics     = TRUE;
static BoolT	rule_do_inline_singles        = FALSE;
static BoolT	rule_do_inline_non_tail_calls = FALSE;
static BoolT	rule_do_multiple_inlining     = FALSE;

/*--------------------------------------------------------------------------*/

static void
rule_inline_tail_calls_1(RuleP rule, AltP alt, RuleP tail_group)
{
    ItemP item = alt_item_head(alt);
    ItemP next;

    while ((next = item_next(item)) != NULL) {
	item = next;
    }
    if (item_is_rule(item)) {
	RuleP item_rule = entry_get_rule(item_entry(item));

	if ((rule_get_tail_group(item_rule) == tail_group) &&
	    (types_equal_names(rule_result(rule), item_result(item)))) {
	    item_inlinable(item);
	    item_tail_call(item);
	}
    }
}

static void
rule_inline_tail_calls(RuleP rule)
{
    RuleP tail_group = rule_get_tail_group(rule);
    AltP  alt;

    if ((alt = rule_get_handler(rule)) != NULL) {
	rule_inline_tail_calls_1(rule, alt, tail_group);
    }
    for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
	rule_inline_tail_calls_1(rule, alt, tail_group);
    }
}

static void	rule_compute_call_graph(RuleP, EntryListP, RuleStackP);

static void
rule_compute_call_graph_1(AltP alt, EntryListP call_list, RuleStackP next)
{
    ItemP item = alt_item_head(alt);
    ItemP next_item;

    while ((next_item = item_next(item)) != NULL) {
	item = next_item;
    }
    if (item_is_tail_call(item)) {
	EntryP entry     = item_entry(item);
	RuleP  item_rule = entry_get_rule(entry);

	rule_compute_call_graph(item_rule, call_list, next);
    }
}

static void
rule_compute_call_graph(RuleP rule, EntryListP call_list, RuleStackP next)
{
    RuleStackT stack;
    AltP       alt;

    stack.rule = rule;
    stack.next = next;
    while (next) {
	if (next->rule == rule) {
	    entry_list_add_if_missing(call_list, rule_entry(rule));
	    return;
	}
	next = next->next;
    }
    if ((alt = rule_get_handler(rule)) != NULL) {
	rule_compute_call_graph_1(alt, call_list, &stack);
    }
    for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
	rule_compute_call_graph_1(alt, call_list, &stack);
    }
}

static void
rule_compute_all_basics_1(RuleP rule)
{
    if ((!rule_has_empty_alt(rule)) &&
	(rule_get_handler(rule) == NULL)) {
	AltP alt;

	for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
	    ItemP item;

	    for (item = alt_item_head(alt); item; item = item_next(item)) {
		if (!item_is_basic(item)) {
		    return;
		}
	    }
	}
	rule_all_basics(rule);
    }
}

static void	rule_compute_inlining_1(RuleP);

static void
rule_compute_inlining_2(AltP alt)
{
    ItemP item;

    for (item = alt_item_head(alt); item; item = item_next(item)) {
	if ((item_is_rule(item)) && (!item_is_tail_call(item))) {
	    EntryP entry     = item_entry(item);
	    RuleP  item_rule = entry_get_rule(entry);

	    if (rule_is_all_basics(item_rule)) {
		item_inlinable(item);
	    } else if (rule_do_inline_singles &&
		       rule_has_one_alt(item_rule)) {
		item_inlinable(item);
	    } else if (!rule_do_multiple_inlining) {
		rule_inc_call_count(item_rule);
	    }
	    if (rule_do_inline_non_tail_calls) {
		item_inlinable(item);
	    }
	    rule_compute_inlining_1(item_rule);
	}
    }
}

static void
rule_compute_inlining_1(RuleP rule)
{
    if (!rule_is_checked_for_inlining(rule)) {
	if (!rule_is_being_inlined(rule)) {
	    AltP alt;

	    rule_being_inlined(rule);
	    if ((alt = rule_get_handler(rule)) != NULL) {
		rule_compute_inlining_2(alt);
	    }
	    for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
		rule_compute_inlining_2(alt);
	    }
	    rule_checked_for_inlining(rule);
	}
    }
}

static void
rule_compute_needed_functions_2(AltP alt)
{
    ItemP item;

    for (item = alt_item_head(alt); item; item = item_next(item)) {
	if (item_is_rule(item)) {
	    RuleP item_rule = entry_get_rule(item_entry(item));

	    if ((!item_is_inlinable(item)) ||
		(rule_get_call_count(item_rule) > 1)) {
		rule_will_need_function(item_rule);
	    }
	}
    }
}

static void
rule_compute_needed_functions_1(RuleP rule)
{
    AltP     alt;

    if ((alt = rule_get_handler(rule)) != NULL) {
	rule_compute_needed_functions_2(alt);
    }
    for (alt = rule_alt_head(rule); alt; alt = alt_next(alt)) {
	rule_compute_needed_functions_2(alt);
    }
}

/*--------------------------------------------------------------------------*/

void
rule_handle_tails(RuleP rule_list)
{
    RuleP rule;

    for (rule = rule_list; rule; rule = rule_get_next_in_reverse_dfs(rule)) {
	rule_set_tail_group(rule, rule_list);
	rule_no_cycles(rule);
    }
    for (rule = rule_list; rule; rule = rule_get_next_in_reverse_dfs(rule)) {
	rule_inline_tail_calls(rule);
    }
    for (rule = rule_list; rule; rule = rule_get_next_in_reverse_dfs(rule)) {
	rule_compute_call_graph(rule, rule_call_list(rule),
				 NULL);
    }
}

void
rule_compute_all_basics(EntryP entry, void * gclosure)
{
    UNUSED(gclosure);
    if (rule_do_inline_all_basics && entry_is_rule(entry)) {
	RuleP rule = entry_get_rule(entry);

	rule_compute_all_basics_1(rule);
    }
}

void
rule_compute_inlining(EntryP entry, void * gclosure)
{
    UNUSED(gclosure);
    if (entry_is_rule(entry)) {
	RuleP rule = entry_get_rule(entry);

	rule_compute_inlining_1(rule);
    }
}

void
rule_compute_needed_functions(EntryP entry, void * gclosure)
{
    UNUSED(gclosure);
    if (entry_is_rule(entry)) {
	RuleP rule = entry_get_rule(entry);

	rule_compute_needed_functions_1(rule);
    }
}

void
rule_handle_need_functions(RuleP rule_list)
{
    RuleP rule;

    for (rule = rule_list; rule; rule = rule_get_next_in_reverse_dfs(rule)) {
	rule_will_need_function(rule);
    }
}

BoolT
rule_get_inline_tail_calls(void)
{
    return(rule_do_inline_tail_calls);
}

void
rule_set_inline_tail_calls(BoolT enable)
{
    rule_do_inline_tail_calls = enable;
}

void
rule_set_inline_all_basics(BoolT enable)
{
    rule_do_inline_all_basics = enable;
}

void
rule_set_inline_singles(BoolT enable)
{
    rule_do_inline_singles = enable;
}

void
rule_set_inline_non_tail_calls(BoolT enable)
{
    if (enable) {
	rule_do_inline_non_tail_calls = TRUE;
    } else {
	rule_do_inline_non_tail_calls = FALSE;
	rule_do_multiple_inlining     = FALSE;
    }
}

void
rule_set_multiple_inlining(BoolT enable)
{
    if (enable) {
	rule_do_inline_non_tail_calls = TRUE;
	rule_do_multiple_inlining     = TRUE;
    } else {
	rule_do_multiple_inlining     = FALSE;
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
