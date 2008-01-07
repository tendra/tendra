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


/*** rule-simp.c --- Rule simplification routines.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the SID elimination of identical rules routines.
 *
 * In order to optimise the elimination of identical rules the following is
 * done:
 *
 * 	- name flow through each rule is numbered, so that differences in
 *	  names do not affect the comparisons;
 *
 *	- alternatives are reordered so that they will appear in the same
 *	  order in identical rules;
 *
 *	- rules are placed in a hash table, so that identical rules will be in
 *	  the same slot in the table.
 *
 * The first two of these make comparisons between two rules quicker.  The
 * third reduces the number of comparisons that are made.
 *
 * One important thing to remember is that the hash value of a rule should not
 * depend upon the names of any rules that it calls.  If this was the case,
 * and one of the rules was replaced then it would be possible to have two
 * identical rules in different slots in the hash table!
 *
 * If two identical rules are found, one is substituted for the other.  If
 * one of the rules is a required rule, then it becomes the used rule.
 */

/****************************************************************************/

#include "rule.h"
#include "action.h"
#include "basic.h"
#include "entry-list.h"
#include "name.h"
#include "type.h"

/*--------------------------------------------------------------------------*/

#define EQUALITY_TABLE_SIZE (127)

/*--------------------------------------------------------------------------*/

typedef struct RuleSortListT {
    AltP			head;
    AltP		       *tail;
} RuleSortListT, *RuleSortListP;

typedef struct ReplaceClosureT {
    EntryP			from;
    EntryP			to;
} ReplaceClosureT, *ReplaceClosureP;

/*--------------------------------------------------------------------------*/

static RuleP			equality_table [EQUALITY_TABLE_SIZE];

/*--------------------------------------------------------------------------*/

static void
rule_sort_alts(RuleSortListP sort_list)
{
    AltP alt      = sort_list->head;
    AltP scan_alt = alt_next (alt);
	
    if (scan_alt) {
		RuleSortListT lower;
		RuleSortListT higher;
		
		lower.tail  = &(lower.head);
		higher.tail = &(higher.head);
		for (; scan_alt; scan_alt = alt_next (scan_alt)) {
			if (alt_less_than (scan_alt, alt)) {
				*(lower.tail)  = scan_alt;
				lower.tail     = alt_next_ref (scan_alt);
			} else {
				*(higher.tail) = scan_alt;
				higher.tail    = alt_next_ref (scan_alt);
			}
		}
		*(lower.tail)  = NIL (AltP);
		*(higher.tail) = NIL (AltP);
		if (lower.head) {
			rule_sort_alts (&lower);
			sort_list->head = lower.head;
			sort_list->tail = lower.tail;
		} else {
			sort_list->tail = &(sort_list->head);
		}
		*(sort_list->tail) = alt;
		sort_list->tail    = alt_next_ref (alt);
		if (higher.head) {
			rule_sort_alts (&higher);
			*(sort_list->tail) = higher.head;
			sort_list->tail    = higher.tail;
		}
		*(sort_list->tail) = NIL (AltP);
    }
}

static void
rule_reorder(RuleP rule)
{
    RuleSortListT sort_list;
	
    if ((sort_list.head = rule_alt_head (rule)) != NIL (AltP)) {
		sort_list.tail = rule->alt_tail;
		rule_sort_alts (&sort_list);
		rule->alt_head = sort_list.head;
		rule->alt_tail = sort_list.tail;
    }
}

static void
rule_hash_1(RuleP rule, EntryP predicate_id)
{
    unsigned hash_value = (unsigned) (rule_has_empty_alt (rule) ? 3 : 0);
    AltP     alt;
	
    rule_renumber (rule, TRUE, predicate_id);
    rule_reorder (rule);
    for (alt = rule_alt_head (rule); alt; alt = alt_next (alt)) {
		ItemP item;
		KeyP  key = NIL (KeyP);
		
		hash_value += 5;
		for (item = alt_item_head (alt); item; item = item_next (item)) {
			hash_value ++;
			if (!item_is_rule (item)) {
				key = entry_key (item_entry (item));
			}
		}
		if (key) {
			hash_value += key_hash_value (key);
		}
    }
    hash_value %= EQUALITY_TABLE_SIZE;
    rule_set_next_in_table (rule, equality_table [hash_value]);
    equality_table [hash_value] = rule;
}

static void
rule_hash_for_comparison(EntryP entry, void *gclosure)
{
    if (entry_is_rule (entry)) {
		RuleP  rule         = entry_get_rule (entry);
		EntryP predicate_id = (EntryP) gclosure;
		
		rule_hash_1 (rule, predicate_id);
    }
}

static BoolT
rule_equal(RuleP rule1, RuleP rule2)
{
    AltP alt1;
    AltP alt2;
	
    if ((!types_equal_numbers (rule_param (rule1), rule_param (rule2))) ||
		(!types_equal_numbers (rule_result (rule1), rule_result (rule2))) ||
		(rule_has_empty_alt (rule1) != rule_has_empty_alt (rule2)) ||
		(!alt_equal (rule_get_handler (rule1), rule_get_handler (rule2))) ||
		(!non_local_list_is_empty (rule_non_locals (rule1))) ||
		(!non_local_list_is_empty (rule_non_locals (rule2)))) {
		return (FALSE);
    }
    for (alt1 = rule_alt_head (rule1), alt2 = rule_alt_head (rule2);
		 alt1 && alt2; alt1 = alt_next (alt1), alt2 = alt_next (alt2)) {
		ItemP item1;
		ItemP item2;
		
		for (item1 = alt_item_head (alt1), item2 = alt_item_head (alt2);
			 item1 && item2;
			 item1 = item_next (item1), item2 = item_next (item2)) {
			if ((item_entry (item1) != item_entry (item2)) ||
				(!types_equal_numbers (item_param (item1),
									   item_param (item2))) ||
				(!types_equal_numbers (item_result (item1),
									   item_result (item2)))) {
				return (FALSE);
			}
		}
		if (item1 || item2) {
			return (FALSE);
		}
    }
    if (alt1 || alt2) {
		return (FALSE);
    }
    return (TRUE);
}

static BoolT
rule_do_replacements_1(AltP alt, ReplaceClosureP closure)
{
    BoolT changed = FALSE;
    ItemP item;
	
    for (item = alt_item_head (alt); item; item = item_next (item)) {
		if (item_entry (item) == closure->from) {
			item_set_entry (item, closure->to);
			changed = TRUE;
		}
    }
    return (changed);
}

static void
rule_do_replacements(EntryP entry, void *gclosure)
{
    ReplaceClosureP closure = (ReplaceClosureP) gclosure;
	
    if (entry_is_rule (entry)) {
		RuleP rule    = entry_get_rule (entry);
		BoolT changed = FALSE;
		AltP  alt;
		
		if ((alt = rule_get_handler (rule)) != NIL (AltP)) {
			if (rule_do_replacements_1 (alt, closure)) {
				changed = TRUE;
			}
		}
		for (alt = rule_alt_head (rule); alt; alt = alt_next (alt)) {
			if (rule_do_replacements_1 (alt, closure)) {
				changed = TRUE;
			}
		}
		if (changed) {
			rule_reorder (rule);
		}
    }
}

static BoolT
rule_remove_duplicates_1(RuleP *rule_ref,
						 TableP table)
{
    BoolT did_remove = FALSE;
    RuleP rule;
	
    while ((rule = *rule_ref) != NIL (RuleP)) {
		RuleP *inner_rule_ref = rule_get_next_in_table_ref (rule);
		RuleP  inner_rule;
		
		while ((inner_rule = *inner_rule_ref) != NIL (RuleP)) {
			if (rule_equal (rule, inner_rule)) {
				ReplaceClosureT closure;
				
				if (rule_is_required (inner_rule)) {
					closure.from = rule_entry (rule);
					closure.to   = rule_entry (inner_rule);
					*rule_ref    = rule_get_next_in_table (rule);
				} else {
					closure.from    = rule_entry (inner_rule);
					closure.to      = rule_entry (rule);
					*inner_rule_ref = rule_get_next_in_table (inner_rule);
				}
				table_iter (table, rule_do_replacements, (void *) &closure);
				did_remove = TRUE;
				if (rule != *rule_ref) {
					goto removed_rule;
				}
			} else {
				inner_rule_ref = rule_get_next_in_table_ref (inner_rule);
			}
		}
		rule_ref = rule_get_next_in_table_ref (rule);
      removed_rule:;
    }
    return (did_remove);
}

/*--------------------------------------------------------------------------*/

void
rule_remove_duplicates(TableP table, EntryP predicate_id)
{
    BoolT    did_remove;
    unsigned i;
	
    for (i = 0; i < EQUALITY_TABLE_SIZE; i ++) {
		equality_table [i] = NIL (RuleP);
    }
    table_iter (table, rule_hash_for_comparison, (void *) predicate_id);
    do {
		did_remove = FALSE;
		for (i = 0; i < EQUALITY_TABLE_SIZE; i ++) {
			if (rule_remove_duplicates_1 (&(equality_table [i]), table)) {
				did_remove = TRUE;
			}
		}
    } while (did_remove);
}
