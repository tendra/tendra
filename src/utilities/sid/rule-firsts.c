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


/*** rule-firsts.c --- Computation of rule first sets.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the SID first set calculation routines.
 *
 * The first set of a rule is the set of all terminals that may start that
 * rule.  As well as computing the first set of a rule, its priority and
 * whether or not it is see through are also computed.  A rule is see through
 * if there is an expansion of the rule that does not involve a basic or
 * predicate.  The priority is used during the factorisation phase to work out
 * which rules to expand.  The rule's priority is one more than the priority
 * of the rule with the highest priority in any of the rule's alternatives
 * that is not preceded by an action.  If there is no such rule, then the
 * rule's priority is one.
 *
 * As well as computing the first sets, these routines check that there are no
 * recursive calls that are not preceded by a basic or predicate.  They also
 * check that predicates are either the first item in an alternative, or are
 * preceded by a basic (or another predicate).  The same check is also made
 * for rules that start with a predicate.
 *
 *** Change Log:
 * $Log: rule-firsts.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:58:39  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:38  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#include "rule.h"
#include "basic.h"
#include "gen-errors.h"
#include "table.h"

/*--------------------------------------------------------------------------*/

void
rule_compute_first_set_1 PROTO_N ((rule))
			 PROTO_T (RuleP rule)
{
    AltP     alt;
    unsigned priority = 0;

    if (rule_has_computed_first_set (rule)) {
	return;
    } else if (rule_is_computing_first_set (rule)) {
	E_cannot_compute_first_set (rule);
	return;
    }
    rule_computing_first_set (rule);
    for (alt = rule_alt_head (rule); alt; alt = alt_next (alt)) {
	BoolT see_through = TRUE;
	BoolT no_action   = TRUE;
	ItemP item        = alt_item_head (alt);
	ItemP initial     = item;

	for (; see_through && (item != NIL (ItemP)); item = item_next (item)) {
	    switch (item_type (item)) EXHAUSTIVE {
	      case ET_PREDICATE:
		if (item != initial) {
		    E_see_to_predicate (entry_key (item_entry (item)), rule);
		}
		entry_list_add_if_missing (rule_predicate_first (rule),
					   item_entry (item));
		see_through = FALSE;
		break;
	      case ET_RENAME:
	      case ET_ACTION:
		no_action = FALSE;
		break;
	      case ET_RULE: {
		  EntryP     entry      = item_entry (item);
		  RuleP      item_rule  = entry_get_rule (entry);
		  EntryListP pred_first = rule_predicate_first (item_rule);
		  unsigned   item_priority;

		  rule_compute_first_set_1 (item_rule);
		  if ((item != initial) &&
		      (!entry_list_is_empty (pred_first))) {
		      E_see_to_rule_predicate (item_rule, rule);
		  }
		  bitvec_or (rule_first_set (rule),
			     rule_first_set (item_rule));
		  entry_list_append (rule_predicate_first (rule), pred_first);
		  see_through   = rule_is_see_through (item_rule);
		  item_priority = rule_get_priority (item_rule);
		  if ((item_priority > priority) && no_action) {
		      priority = item_priority;
		  }
	      }
		break;
	      case ET_BASIC: {
		  BasicP basic = entry_get_basic (item_entry (item));

		  bitvec_set (rule_first_set (rule), basic_terminal (basic));
		  see_through = FALSE;
	      }
		break;
	      case ET_NON_LOCAL:
	      case ET_NAME:
	      case ET_TYPE:
		UNREACHED;
	    }
	}
	if (see_through) {
	    rule_see_through (rule);
	}
    }
    if (rule_has_empty_alt (rule)) {
	rule_see_through (rule);
    }
    rule_set_priority (rule, priority + 1);
    if (rule_is_see_through (rule) && bitvec_is_full (rule_first_set (rule))) {
	E_redundant_see_through_alt (rule);
    }
    rule_computed_first_set (rule);
}

void
rule_compute_first_set PROTO_N ((entry, gclosure))
		       PROTO_T (EntryP   entry X
				GenericP gclosure)
{
    UNUSED (gclosure);
    if (entry_is_rule (entry)) {
	RuleP rule = entry_get_rule (entry);

	rule_compute_first_set_1 (rule);
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
