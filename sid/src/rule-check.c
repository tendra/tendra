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


/*** rule-check.c --- Checks for grammar validity.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the routines that check to see if the grammar is
 * valid.  There are for checks that are made:
 *
 *	- The first sets of all alternatives in a rule are checked to ensure
 *	that they are disjoint (this includes the predicate first sets).  This
 *	also includes checking that there is only one see through alternative.
 *
 *	- The follow set of each rule is computed, and checked to ensure that
 *	if the rule is see through, its follow set does not intersect with its
 *	first set (this includes predicate follow and first sets).
 *
 *	- If there is a see through alternative, this is computed.
 *
 *	- The first set of each alternative is computed.
 *
 *** Change Log:
 * $Log: rule-check.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1994/12/15  09:58:35  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.2  1994/08/22  09:37:22  smf
 * Fixed bug DR114:ids-too-long.
 *
 * Revision 1.1.1.1  1994/07/25  16:04:38  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#include "rule.h"
#include "basic.h"
#include "bitvec.h"
#include "gen-errors.h"

/*--------------------------------------------------------------------------*/

static void
rule_check_first_set_1 PROTO_N ((rule, grammar))
		       PROTO_T (RuleP    rule X
				GrammarP grammar)
{
    BoolT         is_empty            = rule_has_empty_alt (rule);
    BoolT         is_empty_mesg_shown = FALSE;
    BitVecT       test;
    EntryListT    predicate_list;
    AltP          alt;
    BasicClosureT closure;

    closure.grammar = grammar;
    bitvec_init (&test);
    entry_list_init (&predicate_list);
    for (alt = rule_alt_head (rule); alt; alt = alt_next (alt)) {
	ItemP item        = alt_item_head (alt);
	ItemP initial     = item;
	BoolT see_through = TRUE;

	for (; see_through && item; item = item_next (item)) {
	    EntryP entry = item_entry (item);

	    switch (item_type (item)) EXHAUSTIVE {
	      case ET_PREDICATE:
		ASSERT (item == initial);
		if (entry_list_contains (&predicate_list, entry)) {
		    E_predicate_collision (rule, entry_key (entry));
		} else {
		    entry_list_add (&predicate_list, entry);
		}
		see_through = FALSE;
		break;
	      case ET_ACTION:
	      case ET_RENAME:
		break;
	      case ET_BASIC: {
		  unsigned terminal = basic_terminal (entry_get_basic (entry));

		  see_through = FALSE;
		  if (bitvec_is_set (&test, terminal)) {
		      BitVecT tmp;

		      bitvec_init (&tmp);
		      bitvec_set (&tmp, terminal);
		      bitvec_and (&tmp, &test);
		      closure.bitvec = &tmp;
		      E_first_set_collision (rule, &closure);
		      bitvec_destroy (&tmp);
		  } else {
		      bitvec_set (&test, terminal);
		  }
	      }
		break;
	      case ET_RULE: {
		  RuleP      item_rule  = entry_get_rule (entry);
		  EntryListP item_preds = rule_predicate_first (item_rule);
		  EntryListT tmp_list;
		  BitVecP    bitvec;

		  entry_list_intersection (&tmp_list, &predicate_list,
					   item_preds);
		  if (!entry_list_is_empty (&tmp_list)) {
		      E_predicate_list_collision (rule, &tmp_list);
		  }
		  entry_list_destroy (&tmp_list);
		  entry_list_append (&predicate_list, item_preds);
		  bitvec      = rule_first_set (item_rule);
		  see_through = rule_is_see_through (item_rule);
		  if (bitvec_intersects (&test, bitvec)) {
		      BitVecT tmp;

		      bitvec_copy (&tmp, bitvec);
		      bitvec_and (&tmp, &test);
		      closure.bitvec = &tmp;
		      E_first_set_collision (rule, &closure);
		      bitvec_destroy (&tmp);
		  } else {
		      bitvec_or (&test, bitvec);
		  }
	      }
		break;
	      case ET_NON_LOCAL:
	      case ET_TYPE:
	      case ET_NAME:
		UNREACHED;
	    }
	}
	if (see_through) {
	    if (is_empty) {
		if (!is_empty_mesg_shown) {
		    E_multiple_see_through_alts (rule);
		    is_empty_mesg_shown = TRUE;
		}
	    } else {
		is_empty = TRUE;
	    }
	}
    }
    bitvec_destroy (&test);
}

static void			rule_compute_follow_set_1
	PROTO_S ((RuleP, GrammarP, BitVecP, EntryListP, ClashListP));

static void
rule_compute_follow_set_3 PROTO_N ((grammar, item, context, pred_context,
				    clashes))
			  PROTO_T (GrammarP   grammar X
				   ItemP      item X
				   BitVecP    context X
				   EntryListP pred_context X
				   ClashListP clashes)
{
    if (item != NIL (ItemP)) {
	EntryP entry;

	rule_compute_follow_set_3 (grammar, item_next (item), context,
				   pred_context, clashes);
	entry = item_entry (item);
	switch (item_type (item)) EXHAUSTIVE {
	  case ET_PREDICATE:
	    entry_list_destroy (pred_context);
	    entry_list_init (pred_context);
	    entry_list_add (pred_context, entry);
	    clashes->next = NIL (ClashListP);
	    break;
	  case ET_ACTION:
	  case ET_RENAME:
	    break;
	  case ET_RULE: {
	      RuleP rule = entry_get_rule (entry);

	      clashes->item = item;
	      rule_compute_follow_set_1 (rule, grammar, context, pred_context,
					 clashes);
	      if (rule_is_see_through (rule)) {
		  bitvec_or (context, rule_first_set (rule));
		  entry_list_append (pred_context,
				     rule_predicate_first (rule));
	      } else {
		  bitvec_replace (context, rule_first_set (rule));
		  entry_list_destroy (pred_context);
		  entry_list_init (pred_context);
		  entry_list_append (pred_context,
				     rule_predicate_first (rule));
		  clashes->next = NIL (ClashListP);
	      }
	  }
	    break;
	  case ET_BASIC: {
	      BasicP basic = entry_get_basic (entry);

	      bitvec_empty (context);
	      bitvec_set (context, basic_terminal (basic));
	      clashes->next = NIL (ClashListP);
	  }
	    break;
	  case ET_NON_LOCAL:
	  case ET_NAME:
	  case ET_TYPE:
	    UNREACHED;
	}
    }
}

static void
rule_compute_follow_set_2 PROTO_N ((rule, grammar, alt, context, pred_context,
				    clashes))
			  PROTO_T (RuleP      rule X
				   GrammarP   grammar X
				   AltP       alt X
				   BitVecP    context X
				   EntryListP pred_context X
				   ClashListP clashes)
{
    BitVecT    tmp;
    EntryListT tmp_list;
    ClashListT clash;

    clash.next = clashes;
    clash.rule = rule;
    clash.alt  = alt;
    bitvec_copy (&tmp, context);
    entry_list_copy (&tmp_list, pred_context);
    rule_compute_follow_set_3 (grammar, alt_item_head (alt), &tmp, &tmp_list,
			       &clash);
    bitvec_destroy (&tmp);
    entry_list_destroy (&tmp_list);
}

static void
rule_compute_follow_set_1 PROTO_N ((rule, grammar, context, pred_context,
				    clashes))
			  PROTO_T (RuleP      rule X
				   GrammarP   grammar X
				   BitVecP    context X
				   EntryListP pred_context X
				   ClashListP clashes)
{
    BitVecP       follow      = rule_follow_set (rule);
    EntryListP    pred_follow = rule_predicate_follow (rule);
    BitVecP       first       = rule_first_set (rule);
    EntryListP    pred_first  = rule_predicate_first (rule);
    BitVecT       test;
    AltP          alt;
    BasicClosureT closure;

    if (rule_has_started_follows (rule)) {
	bitvec_copy (&test, follow);
	bitvec_or (follow, context);
	if (bitvec_equal (&test, follow) &&
	    entry_list_includes (pred_follow, pred_context)) {
	    bitvec_destroy (&test);
	    return;
	}
	entry_list_append (pred_follow, pred_context);
	bitvec_destroy (&test);
    } else {
	bitvec_replace (follow, context);
	entry_list_append (pred_follow, pred_context);
	rule_started_follows (rule);
    }
    closure.grammar = grammar;
    if (rule_is_see_through (rule)) {
	EntryListT tmp_list;

	if (bitvec_intersects (follow, first)) {
	    bitvec_copy (&test, follow);
	    bitvec_and (&test, first);
	    closure.bitvec = &test;
	    E_follow_set_collision (rule, &closure, clashes);
	    bitvec_not (&test);
	    bitvec_and (first, &test);
	    bitvec_destroy (&test);
	}
	entry_list_intersection (&tmp_list, pred_follow, pred_first);
	if (!entry_list_is_empty (&tmp_list)) {
	    E_predicate_follow_set_coll (rule, &tmp_list, clashes);
	    entry_list_unlink_used (pred_first, &tmp_list);
	}
	entry_list_destroy (&tmp_list);
    }
    if ((alt = rule_get_handler (rule)) != NIL (AltP)) {
	rule_compute_follow_set_2 (rule, grammar, alt, follow, pred_follow,
				   clashes);
    }
    for (alt = rule_alt_head (rule); alt; alt = alt_next (alt)) {
	rule_compute_follow_set_2 (rule, grammar, alt, follow, pred_follow,
				   clashes);
    }
}

static void
rule_compute_see_through_alt_1 PROTO_N ((rule))
			       PROTO_T (RuleP rule)
{
    if (!rule_has_empty_alt (rule)) {
	AltP alt;

	for (alt = rule_alt_head (rule); alt; alt = alt_next (alt)) {
	    ItemP item;

	    for (item = alt_item_head (alt); item; item = item_next (item)) {
		RuleP item_rule;

		if ((!item_is_action (item)) && (!item_is_rename (item)) &&
		    ((!item_is_rule (item)) ||
		     ((item_rule = entry_get_rule (item_entry (item))),
		      (!rule_is_see_through (item_rule))))) {
		    goto next_alt;
		}
	    }
	    rule_set_see_through_alt (rule, alt);
	    return;
	  next_alt:;
	}
    }
}

static void
rule_compute_alt_first_sets_1 PROTO_N ((rule))
			      PROTO_T (RuleP rule)
{
    AltP alt;

    for (alt = rule_alt_head (rule); alt; alt = alt_next (alt)) {
	BitVecP alt_firsts  = alt_first_set (alt);
	ItemP   item        = alt_item_head (alt);
	ItemP   initial     = item;
	BoolT   see_through = TRUE;

	for (; see_through && item; item = item_next (item)) {
	    EntryP entry = item_entry (item);

	    switch (item_type (item)) EXHAUSTIVE {
	      case ET_PREDICATE:
		ASSERT (item == initial);
		see_through = FALSE;
		break;
	      case ET_ACTION:
	      case ET_RENAME:
		break;
	      case ET_BASIC:
		see_through = FALSE;
		bitvec_set (alt_firsts,
			    basic_terminal (entry_get_basic (entry)));
		break;
	      case ET_RULE: {
		  RuleP item_rule = entry_get_rule (entry);

		  see_through = rule_is_see_through (item_rule);
		  bitvec_or (alt_firsts, rule_first_set (item_rule));
	      }
		break;
	      case ET_NON_LOCAL:
	      case ET_TYPE:
	      case ET_NAME:
		UNREACHED;
	    }
	}
	if (see_through) {
	    bitvec_or (alt_firsts, rule_follow_set (rule));
	}
    }
}

/*--------------------------------------------------------------------------*/

void
rule_check_first_set PROTO_N ((entry, gclosure))
		     PROTO_T (EntryP   entry X
			      GenericP gclosure)
{
    GrammarP grammar = (GrammarP) gclosure;

    if (entry_is_rule (entry)) {
	RuleP rule = entry_get_rule (entry);

	rule_check_first_set_1 (rule, grammar);
    }
}

void
rule_compute_follow_set PROTO_N ((entry, gclosure))
			PROTO_T (EntryP   entry X
				 GenericP gclosure)
{
    GrammarP grammar = (GrammarP) gclosure;

    if (entry_is_rule (entry)) {
	RuleP   rule = entry_get_rule (entry);
	BitVecT    outer;
	EntryListT pred_outer;

	bitvec_init (&outer);
	entry_list_init (&pred_outer);
	rule_compute_follow_set_1 (rule, grammar, &outer, &pred_outer,
				   NIL (ClashListP));
	bitvec_destroy (&outer);
	entry_list_destroy (&pred_outer);
    }
}

void
rule_compute_see_through_alt PROTO_N ((entry, gclosure))
			     PROTO_T (EntryP   entry X
				      GenericP gclosure)
{
    UNUSED (gclosure);
    if (entry_is_rule (entry)) {
	RuleP rule = entry_get_rule (entry);

	rule_compute_see_through_alt_1 (rule);
    }
}

void
rule_compute_alt_first_sets PROTO_N ((entry, gclosure))
			    PROTO_T (EntryP   entry X
				     GenericP gclosure)
{
    UNUSED (gclosure);
    if (entry_is_rule (entry)) {
	RuleP rule = entry_get_rule (entry);

	rule_compute_alt_first_sets_1 (rule);
    }
}

void
write_clashes PROTO_N ((ostream, clashes))
	      PROTO_T (OStreamP   ostream X
		       ClashListP clashes)
{
    write_newline (ostream);
    while (clashes) {
	write_rule_lhs (ostream, clashes->rule);
	write_alt_highlighting (ostream, clashes->alt, clashes->item);
	write_cstring (ostream, "};");
	write_newline (ostream);
	clashes = clashes->next;
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
