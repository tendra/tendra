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


/*** rule-names.c --- Recompute alternative names.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the functions that recompute the names defined in each
 * alternative of a rule (including the exception handler alternative).
 *
 *** Change Log:
 * $Log: rule-names.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:58:50  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
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
#include "types.h"

/*--------------------------------------------------------------------------*/

static void
rule_recompute_alt_names_2 PROTO_N ((alt, predicate_id))
			   PROTO_T (AltP   alt X
				    EntryP predicate_id)
{
    TypeTupleP names = alt_names (alt);
    ItemP      item;

    types_destroy (names);
    types_init (names);
    for (item = alt_item_head (alt); item; item = item_next (item)) {
	types_add_new_names (names, item_result (item), predicate_id);
    }
}

static void
rule_recompute_alt_names_1 PROTO_N ((rule, predicate_id))
			   PROTO_T (RuleP  rule X
				    EntryP predicate_id)
{
    AltP alt;

    if ((alt = rule_get_handler (rule)) != NIL (AltP)) {
	rule_recompute_alt_names_2 (alt, predicate_id);
    }
    for (alt = rule_alt_head (rule); alt; alt = alt_next (alt)) {
	rule_recompute_alt_names_2 (alt, predicate_id);
    }
}

/*--------------------------------------------------------------------------*/

void
rule_recompute_alt_names PROTO_N ((entry, gclosure))
			 PROTO_T (EntryP   entry X
				  GenericP gclosure)
{
    if (entry_is_rule (entry)) {
	RuleP  rule         = entry_get_rule (entry);
	EntryP predicate_id = (EntryP) gclosure;

	rule_recompute_alt_names_1 (rule, predicate_id);
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
