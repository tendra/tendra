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


/*** types.c --- Type ADTs.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the type manipulation routines specified.
 *
 *** Change Log:
 * $Log: types.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:59:13  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:44  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#include "types.h"
#include "dalloc.h"
#include "gen-errors.h"
#include "name.h"
#include "rstack.h"
#include "rule.h"
#include "table.h"

/*==========================================================================*\
|| Type tuple handling fuctions.
\*==========================================================================*/

static void
types_add_name_and_type_1 PROTO_N ((to, name, type, reference, assign))
			  PROTO_T (TypeTupleP  to X
				   EntryP      name X
				   EntryP      type X
				   BoolT       reference X
				   BoolT       assign)
{
    TypeTupleEntryP link = ALLOCATE (TypeTupleEntryT);

    link->next      = NIL (TypeTupleEntryP);
    link->type      = type;
    link->name      = name;
    link->reference = reference;
    link->mutated   = FALSE;
    link->assign    = assign;
    *(to->tail)     = link;
    to->tail        = &(link->next);
}

static void
types_iter_alt_item_type_names PROTO_N ((alts, proc))
			       PROTO_T (AltP   alts X
					void (*proc) PROTO_S ((NameP)))
{
    AltP            alt;
    TypeTupleEntryP type;

    for (alt = alts; alt; alt = alt_next (alt)) {
	ItemP item;

	for (item = alt_item_head (alt); item; item = item_next (item)) {
	    TypeTupleP param  = item_param (item);
	    TypeTupleP result = item_result (item);

	    for (type = param->head; type; type = type->next) {
		(*proc) (entry_get_name (type->name));
	    }
	    for (type = result->head; type; type = type->next) {
		(*proc) (entry_get_name (type->name));
	    }
	}
    }
}

/*--------------------------------------------------------------------------*/

void
types_init PROTO_N ((tuple))
	   PROTO_T (TypeTupleP tuple)
{
    tuple->head = NIL (TypeTupleEntryP);
    tuple->tail = &(tuple->head);
}

void
types_copy PROTO_N ((to, from))
	   PROTO_T (TypeTupleP to X
		    TypeTupleP from)
{
    TypeTupleEntryP from_ptr;

    to->head = NIL (TypeTupleEntryP);
    to->tail = &(to->head);
    for (from_ptr = from->head; from_ptr; from_ptr = from_ptr->next) {
	types_add_name_and_type_1 (to, from_ptr->name, from_ptr->type,
				   from_ptr->reference, from_ptr->assign);
    }
}

void
types_copy_and_translate PROTO_N ((to, from, translator, table))
			 PROTO_T (TypeTupleP to X
				  TypeTupleP from X
				  TypeTransP translator X
				  TableP     table)
{
    TypeTupleEntryP from_ptr;

    to->head = NIL (TypeTupleEntryP);
    to->tail = &(to->head);
    for (from_ptr = from->head; from_ptr; from_ptr = from_ptr->next) {
	EntryP new_name;

	new_name = trans_get_translation (translator, from_ptr->name);
	if (new_name == NIL (EntryP)) {
	    new_name = table_add_generated_name (table);
	    trans_add_translation (translator, from_ptr->name, new_name);
	}
	types_add_name_and_type_1 (to, new_name, from_ptr->type,
				   from_ptr->reference, from_ptr->assign);
    }
}

void
types_append_copy PROTO_N ((to, from))
		  PROTO_T (TypeTupleP to X
			   TypeTupleP from)
{
    TypeTupleEntryP from_ptr;

    for (from_ptr = from->head; from_ptr; from_ptr = from_ptr->next) {
	types_add_name_and_type_1 (to, from_ptr->name, from_ptr->type,
				   from_ptr->reference, from_ptr->assign);
    }
}

void
types_translate PROTO_N ((tuple, translator))
		PROTO_T (TypeTupleP  tuple X
			 TypeBTransP translator)
{
    TypeTupleEntryP tuple_ptr;

    for (tuple_ptr = tuple->head; tuple_ptr; tuple_ptr = tuple_ptr->next) {
	EntryP new_name;

	new_name = btrans_get_translation (translator, tuple_ptr->name);
	if (new_name != NIL (EntryP)) {
	    tuple_ptr->name = new_name;
	}
    }
}

void
types_renumber PROTO_N ((tuple, translator))
	       PROTO_T (TypeTupleP  tuple X
			TypeNTransP translator)
{
    TypeTupleEntryP tuple_ptr;

    for (tuple_ptr = tuple->head; tuple_ptr; tuple_ptr = tuple_ptr->next) {
	if (!entry_is_non_local (tuple_ptr->name)) {
	    tuple_ptr->number = ntrans_get_translation (translator,
							tuple_ptr->name);
	}
    }
}

void
types_assign PROTO_N ((to, from))
	     PROTO_T (TypeTupleP to X
		      TypeTupleP from)
{
    if ((to->head = from->head) != NIL (TypeTupleEntryP)) {
	to->tail = from->tail;
    } else {
	to->tail = &(to->head);
    }
}

EntryP
types_find_name_type PROTO_N ((tuple, name, reference_ref))
		     PROTO_T (TypeTupleP tuple X
			      EntryP     name X
			      BoolT     *reference_ref)
{
    TypeTupleEntryP type;

    for (type = tuple->head; type; type = type->next) {
	if (type->name == name) {
	    *reference_ref = type->reference;
	    return (type->type);
	}
    }
    return (NIL (EntryP));
}

BoolT
types_mutated PROTO_N ((tuple, name))
	      PROTO_T (TypeTupleP tuple X
		       EntryP     name)
{
    TypeTupleEntryP type;

    for (type = tuple->head; type; type = type->next) {
	if (type->name == name) {
	    type->mutated = TRUE;
	    return (TRUE);
	}
    }
    return (FALSE);
}

BoolT
types_compute_mutations PROTO_N ((rule, item, action))
			PROTO_T (TypeTupleP rule X
				 TypeTupleP item X
				 TypeTupleP action)
{
    BoolT           propogate  = FALSE;
    TypeTupleEntryP item_ptr   = item->head;
    TypeTupleEntryP action_ptr = action->head;

    while (action_ptr) {
	ASSERT (item_ptr);
	if (action_ptr->mutated) {
	    TypeTupleEntryP rule_ptr = rule->head;

	    while (rule_ptr) {
		if ((rule_ptr->name == item_ptr->name) &&
		    (!(rule_ptr->mutated))) {
		    rule_ptr->mutated = TRUE;
		    if (rule_ptr->reference) {
			propogate = TRUE;
		    }
		    break;
		}
		rule_ptr = rule_ptr->next;
	    }
	}
	item_ptr   = item_ptr->next;
	action_ptr = action_ptr->next;
    }
    ASSERT (item_ptr == NIL (TypeTupleEntryP));
    return (propogate);
}

BoolT
types_compute_assign_mutations PROTO_N ((rule, item))
			       PROTO_T (TypeTupleP rule X
					TypeTupleP item)
{
    BoolT           propogate  = FALSE;
    TypeTupleEntryP item_ptr   = item->head;

    while (item_ptr) {
	if (item_ptr->assign) {
	    TypeTupleEntryP rule_ptr = rule->head;

	    while (rule_ptr) {
		if ((rule_ptr->name == item_ptr->name) &&
		    (!(rule_ptr->mutated))) {
		    rule_ptr->mutated = TRUE;
		    if (rule_ptr->reference) {
			propogate = TRUE;
		    }
		    break;
		}
		rule_ptr = rule_ptr->next;
	    }
	}
	item_ptr = item_ptr->next;
    }
    return (propogate);
}

void
types_propogate_mutations PROTO_N ((to, from))
			  PROTO_T (TypeTupleP to X
				   TypeTupleP from)
{
    TypeTupleEntryP to_ptr   = to->head;
    TypeTupleEntryP from_ptr = from->head;

    while (to_ptr) {
	ASSERT (from_ptr);
	to_ptr->mutated = from_ptr->mutated;
	to_ptr          = to_ptr->next;
	from_ptr        = from_ptr->next;
    }
    ASSERT (from_ptr == NIL (TypeTupleEntryP));
}

BoolT
types_contains PROTO_N ((tuple, name))
	       PROTO_T (TypeTupleP tuple X
			EntryP     name)
{
    TypeTupleEntryP type;

    for (type = tuple->head; type; type = type->next) {
	if (type->name == name) {
	    return (TRUE);
	}
    }
    return (FALSE);
}

BoolT
types_contains_names PROTO_N ((tuple))
		     PROTO_T (TypeTupleP tuple)
{
    TypeTupleEntryP type;

    for (type = tuple->head; type; type = type->next) {
	if (type->name) {
	    return (TRUE);
	}
    }
    return (FALSE);
}

BoolT
types_contains_references PROTO_N ((tuple))
			  PROTO_T (TypeTupleP tuple)
{
    TypeTupleEntryP type;

    for (type = tuple->head; type; type = type->next) {
	if (type->reference) {
	    return (TRUE);
	}
    }
    return (FALSE);
}

void
types_make_references PROTO_N ((param, args))
		      PROTO_T (TypeTupleP param X
			       TypeTupleP args)
{
    TypeTupleEntryP ptr;

    for (ptr = param->head; ptr; ptr = ptr->next) {
	ptr->reference = TRUE;
    }
    for (ptr = args->head; ptr; ptr = ptr->next) {
	ptr->reference = TRUE;
    }
}

BoolT
types_intersect PROTO_N ((tuple1, tuple2))
		PROTO_T (TypeTupleP tuple1 X
			 TypeTupleP tuple2)
{
    TypeTupleEntryP type;

    for (type = tuple1->head; type; type = type->next) {
	if (types_contains (tuple2, type->name)) {
	    return (TRUE);
	}
    }
    return (FALSE);
}

void
types_inplace_intersection PROTO_N ((to, from))
			   PROTO_T (TypeTupleP to X
				    TypeTupleP from)
{
    TypeTupleEntryP type;

    to->tail = &(to->head);
    while ((type = *(to->tail)) != NIL (TypeTupleEntryP)) {
	if (!types_contains (from, type->name)) {
	    *(to->tail) = type->next;
	    DEALLOCATE (type);
	} else {
	    to->tail = &(type->next);
	}
    }
}

void
types_compute_intersection PROTO_N ((to, tuple1, tuple2))
			   PROTO_T (TypeTupleP to X
				    TypeTupleP tuple1 X
				    TypeTupleP tuple2)
{
    TypeTupleEntryP type;

    for (type = tuple1->head; type; type = type->next) {
	if ((types_contains (tuple2, type->name)) &&
	    (!types_contains (to, type->name))) {
	    types_add_name_and_type_1 (to, type->name, type->type,
				       type->reference, type->assign);
	}
    }
}

CmpT
types_compare PROTO_N ((tuple1, tuple2))
	      PROTO_T (TypeTupleP tuple1 X
		       TypeTupleP tuple2)
{
    TypeTupleEntryP tuple1_ptr = (tuple1->head);
    TypeTupleEntryP tuple2_ptr = (tuple2->head);

    while (tuple1_ptr && tuple2_ptr) {
	if (tuple1_ptr->number < tuple2_ptr->number) {
	    return (CMP_LT);
	} else if (tuple1_ptr->number > tuple2_ptr->number) {
	    return (CMP_GT);
	}
	switch (key_compare (entry_key (tuple1_ptr->type),
			     entry_key (tuple2_ptr->type))) EXHAUSTIVE {
	  case CMP_LT:
	    return (CMP_LT);
	  case CMP_GT:
	    return (CMP_GT);
	  case CMP_EQ:
	    break;
	}
	if (tuple1_ptr->reference != tuple2_ptr->reference) {
	    return ((CmpT) ((tuple1_ptr->reference) ? CMP_GT : CMP_LT));
	} else if (tuple1_ptr->assign != tuple2_ptr->assign) {
	    return ((CmpT) ((tuple1_ptr->assign) ? CMP_GT : CMP_LT));
	}
	tuple1_ptr = tuple1_ptr->next;
	tuple2_ptr = tuple2_ptr->next;
    }
    if (tuple1_ptr != NIL (TypeTupleEntryP)) {
	return (CMP_GT);
    } else if (tuple2_ptr != NIL (TypeTupleEntryP)) {
	return (CMP_LT);
    } else {
	return (CMP_EQ);
    }
}

BoolT
types_equal PROTO_N ((tuple1, tuple2))
	    PROTO_T (TypeTupleP tuple1 X
		     TypeTupleP tuple2)
{
    TypeTupleEntryP tuple1_ptr = (tuple1->head);
    TypeTupleEntryP tuple2_ptr = (tuple2->head);

    while ((tuple1_ptr) && (tuple2_ptr)) {
	if (((tuple1_ptr->type) != (tuple2_ptr->type)) ||
	    ((tuple1_ptr->reference) != (tuple2_ptr->reference)) ||
	    ((tuple1_ptr->assign) != (tuple2_ptr->assign))) {
	    return (FALSE);
	}
	tuple1_ptr = (tuple1_ptr->next);
	tuple2_ptr = (tuple2_ptr->next);
    }
    return ((tuple1_ptr == NIL (TypeTupleEntryP)) &&
	    (tuple2_ptr == NIL (TypeTupleEntryP)));
}

#ifdef FS_FAST
#undef types_equal_zero_tuple
#endif /* defined (FS_FAST) */
BoolT
types_equal_zero_tuple PROTO_N ((tuple))
		       PROTO_T (TypeTupleP tuple)
{
    return (tuple->head == NIL (TypeTupleEntryP));
}
#ifdef FS_FAST
#define types_equal_zero_tuple(t) ((t)->head == NIL (TypeTupleEntryP))
#endif /* defined (FS_FAST) */

BoolT
types_equal_names PROTO_N ((tuple1, tuple2))
		  PROTO_T (TypeTupleP tuple1 X
			   TypeTupleP tuple2)
{
    TypeTupleEntryP tuple1_ptr = (tuple1->head);
    TypeTupleEntryP tuple2_ptr = (tuple2->head);

    while ((tuple1_ptr) && (tuple2_ptr)) {
	if (((tuple1_ptr->type) != (tuple2_ptr->type)) ||
	    ((tuple1_ptr->reference) != (tuple2_ptr->reference)) ||
	    ((tuple1_ptr->assign) != (tuple2_ptr->assign)) ||
	    ((tuple1_ptr->name) != (tuple2_ptr->name))) {
	    return (FALSE);
	}
	tuple1_ptr = (tuple1_ptr->next);
	tuple2_ptr = (tuple2_ptr->next);
    }
    return ((tuple1_ptr == NIL (TypeTupleEntryP)) &&
	    (tuple2_ptr == NIL (TypeTupleEntryP)));
}

BoolT
types_equal_numbers PROTO_N ((tuple1, tuple2))
		    PROTO_T (TypeTupleP tuple1 X
			     TypeTupleP tuple2)
{
    TypeTupleEntryP tuple1_ptr = (tuple1->head);
    TypeTupleEntryP tuple2_ptr = (tuple2->head);

    while ((tuple1_ptr) && (tuple2_ptr)) {
	if ((tuple1_ptr->type != tuple2_ptr->type) ||
	    (tuple1_ptr->reference != tuple2_ptr->reference) ||
	    (tuple1_ptr->assign != tuple2_ptr->assign)) {
	    return (FALSE);
	} else if (entry_is_non_local (tuple1_ptr->name) ||
		   entry_is_non_local (tuple2_ptr->name)) {
	    if (tuple1_ptr->name != tuple2_ptr->name) {
		return (FALSE);
	    }
	} else if (tuple1_ptr->number != tuple2_ptr->number) {
	    return (FALSE);
	}
	tuple1_ptr = (tuple1_ptr->next);
	tuple2_ptr = (tuple2_ptr->next);
    }
    return ((tuple1_ptr == NIL (TypeTupleEntryP)) &&
	    (tuple2_ptr == NIL (TypeTupleEntryP)));
}

void
types_add_name_and_type PROTO_N ((to, name, type, reference))
			PROTO_T (TypeTupleP  to X
				 EntryP      name X
				 EntryP      type X
				 BoolT       reference)
{
    types_add_name_and_type_1 (to, name, type, reference, FALSE);
}

void
types_add_name_and_type_var PROTO_N ((to, name, type))
			    PROTO_T (TypeTupleP  to X
				     EntryP      name X
				     EntryP      type)
{
    types_add_name_and_type_1 (to, name, type, FALSE, TRUE);
}

BoolT
types_add_type PROTO_N ((tuple, table, name, reference))
	       PROTO_T (TypeTupleP tuple X
			TableP     table X
			NStringP   name X
			BoolT      reference)
{
    EntryP entry = table_get_type (table, name);

    if (entry) {
	types_add_name_and_type (tuple, NIL (EntryP), entry, reference);
	return (TRUE);
    }
    return (FALSE);
}

void
types_add_name PROTO_N ((tuple, table, name, reference))
	       PROTO_T (TypeTupleP tuple X
			TableP     table X
			NStringP   name X
			BoolT      reference)
{
    EntryP entry = table_add_name (table, name);

    types_add_name_and_type (tuple, entry, NIL (EntryP), reference);
}

BoolT
types_add_typed_name PROTO_N ((tuple, table, name, type, reference))
		     PROTO_T (TypeTupleP tuple X
			      TableP     table X
			      NStringP   name X
			      NStringP   type X
			      BoolT      reference)
{
    EntryP type_entry = table_get_type (table, type);
    EntryP name_entry = table_add_name (table, name);

    if (type_entry) {
	types_add_name_and_type (tuple, name_entry, type_entry, reference);
	return (TRUE);
    }
    return (FALSE);
}

void
types_add_name_entry PROTO_N ((tuple, entry))
		     PROTO_T (TypeTupleP tuple X
			      EntryP     entry)
{
    types_add_name_and_type (tuple, entry, NIL (EntryP), FALSE);
}

void
types_add_type_entry PROTO_N ((tuple, entry, reference))
		     PROTO_T (TypeTupleP tuple X
			      EntryP     entry X
			      BoolT      reference)
{
    types_add_name_and_type (tuple, NIL (EntryP), entry, reference);
}

void
types_add_new_names PROTO_N ((to, from, exclude))
		    PROTO_T (TypeTupleP to X
			     TypeTupleP from X
			     EntryP     exclude)
{
    TypeTupleEntryP from_ptr;

    for (from_ptr = from->head; from_ptr; from_ptr = from_ptr->next) {
	if ((from_ptr->name != exclude) &&
	    (!(from_ptr->assign)) &&
	    (!types_contains (to, from_ptr->name))) {
	    types_add_name_and_type (to, from_ptr->name, from_ptr->type,
				     from_ptr->reference);
	}
    }
}

BoolT
types_disjoint_names PROTO_N ((tuple))
		     PROTO_T (TypeTupleP tuple)
{
    BoolT           disjoint = TRUE;
    TypeTupleEntryP ptr;

    for (ptr = tuple->head; ptr; ptr = ptr->next) {
	if (ptr->name) {
	    if (name_test_and_set_clash (entry_get_name (ptr->name))) {
		disjoint = FALSE;
		goto done;
	    }
	} else {
	    disjoint = FALSE;
	    goto done;
	}
    }
  done:
    for (ptr = tuple->head; ptr; ptr = ptr->next) {
	if (ptr->name) {
	    name_reset_clash (entry_get_name (ptr->name));
	}
    }
    return (disjoint);
}

BoolT
types_resolve PROTO_N ((to, args, locals, unknown_proc, rule, alt))
	      PROTO_T (TypeTupleP to X
		       TypeTupleP args X
		       TypeTupleP locals X
		       void     (*unknown_proc) PROTO_S ((KeyP, KeyP,
							  unsigned)) X
		       KeyP       rule X
		       unsigned   alt)
{
    BoolT           ok = TRUE;
    TypeTupleEntryP name;

    for (name = to->head; name; name = name->next) {
	BoolT reference;

	if (entry_is_non_local (name->name)) {
	    name->type = entry_get_non_local (name->name);
	} else if (((name->type = types_find_name_type (args, name->name,
							&reference)) ==
		    NIL (EntryP)) &&
		   ((name->type = types_find_name_type (locals, name->name,
							&reference)) ==
		    NIL (EntryP))) {
	    (*unknown_proc) (entry_key (name->name), rule, alt);
	    ok = FALSE;
	}
    }
    return (ok);
}

BoolT
types_check_undefined PROTO_N ((to, args, locals, error_proc, rule, alt))
		      PROTO_T (TypeTupleP to X
			       TypeTupleP args X
			       TypeTupleP locals X
			       void     (*error_proc) PROTO_S ((KeyP, KeyP,
								unsigned)) X
			       KeyP       rule X
			       unsigned   alt)
{
    BoolT           ok = TRUE;
    TypeTupleEntryP name;

    for (name = to->head; name; name = name->next) {
	if ((!(name->assign)) &&
	    (entry_is_non_local (name->name) ||
	     types_contains (args, name->name) ||
	     types_contains (locals, name->name))) {
	    (*error_proc) (entry_key (name->name), rule, alt);
	    ok = FALSE;
	}
    }
    return (ok);
}

BoolT
types_fillin_types PROTO_N ((to, from))
		   PROTO_T (TypeTupleP to X
			    TypeTupleP from)
{
    TypeTupleEntryP to_ptr   = to->head;
    TypeTupleEntryP from_ptr = from->head;

    while ((to_ptr) && (from_ptr)) {
	if (to_ptr->type == NIL (EntryP)) {
	    to_ptr->type      = from_ptr->type;
	    to_ptr->reference = from_ptr->reference;
	} else if ((to_ptr->type != from_ptr->type) ||
		   (to_ptr->reference != from_ptr->reference)) {
	    return (FALSE);
	}
	to_ptr   = to_ptr->next;
	from_ptr = from_ptr->next;
    }
    return ((to_ptr == NIL (TypeTupleEntryP)) &&
	    (from_ptr == NIL (TypeTupleEntryP)));
}

BoolT
types_fillin_names PROTO_N ((to, from))
		   PROTO_T (TypeTupleP to X
			    TypeTupleP from)
{
    TypeTupleEntryP to_ptr   = to->head;
    TypeTupleEntryP from_ptr = from->head;

    while ((to_ptr) && (from_ptr)) {
	ASSERT (to_ptr->name == NIL (EntryP));
	to_ptr->name = from_ptr->name;
	if ((from_ptr->type) &&
	    ((to_ptr->type != from_ptr->type) ||
	     (to_ptr->reference != from_ptr->reference))) {
	    return (FALSE);
	}
	to_ptr   = to_ptr->next;
	from_ptr = from_ptr->next;
    }
    return ((to_ptr == NIL (TypeTupleEntryP)) &&
	    (from_ptr == NIL (TypeTupleEntryP)));
}

BoolT
types_check_names PROTO_N ((to, from))
		  PROTO_T (TypeTupleP to X
			   TypeTupleP from)
{
    TypeTupleEntryP to_ptr;

    for (to_ptr = to->head; to_ptr; to_ptr = to_ptr->next) {
	BoolT reference;

	if ((types_find_name_type (from, to_ptr->name, &reference) !=
	     to_ptr->type) ||
	    (reference != to_ptr->reference)) {
	    return (FALSE);
	}
    }
    return (TRUE);
}

void
types_check_used PROTO_N ((tuple, error_proc, gclosure))
		 PROTO_T (TypeTupleP tuple X
			  void     (*error_proc) PROTO_S ((GenericP, EntryP)) X
			  GenericP   gclosure)
{
    TypeTupleEntryP ptr;

    for (ptr = tuple->head; ptr; ptr = ptr->next) {
	ASSERT (!entry_is_non_local (ptr->name));
	if (!name_is_used (entry_get_name (ptr->name))) {
	    (*error_proc) (gclosure, ptr->name);
	}
    }
}

void
types_unlink_used PROTO_N ((to, from))
		  PROTO_T (TypeTupleP to X
			   TypeTupleP from)
{
    TypeTupleEntryP type;

    to->tail = &(to->head);
    while ((type = *(to->tail)) != NIL (TypeTupleEntryP)) {
	if (types_contains (from, type->name)) {
	    *(to->tail) = type->next;
	    DEALLOCATE (type);
	} else {
	    to->tail = &(type->next);
	}
    }
}

void
types_unlink_unused PROTO_N ((tuple, alts))
		    PROTO_T (TypeTupleP tuple X
			     AltP       alts)
{
    TypeTupleEntryP type;

    types_iter_alt_item_type_names (alts, name_used);
    tuple->tail = &(tuple->head);
    while ((type = *(tuple->tail)) != NIL (TypeTupleEntryP)) {
	ASSERT (!entry_is_non_local (type->name));
	if (name_is_used (entry_get_name (type->name))) {
	    tuple->tail = &(type->next);
	} else {
	    *(tuple->tail) = type->next;
	    DEALLOCATE (type);
	}
    }
    types_iter_alt_item_type_names (alts, name_not_used);
}

void
types_compute_formal_renaming PROTO_N ((names, translator))
			      PROTO_T (TypeTupleP  names X
				       TypeRTransP translator)
{
    TypeTupleEntryP ptr;

    for (ptr = names->head; ptr; ptr = ptr->next) {
	rtrans_add_translation (translator, ptr->name, ptr->name, ptr->type,
				ptr->reference);
    }
}

void
types_compute_formal_inlining PROTO_N ((names, renames, translator, state))
			      PROTO_T (TypeTupleP  names X
				       TypeTupleP  renames X
				       TypeRTransP translator X
				       SaveRStackP state)
{
    TypeTupleEntryP ptr   = names->head;
    TypeTupleEntryP reptr = renames->head;

    while (ptr) {
	EntryP entry;
	EntryP type;
	BoolT  reference;

	ASSERT (reptr);
	entry = rstack_get_translation (state, reptr->name, &type, &reference);
	ASSERT (entry);
	rtrans_add_translation (translator, ptr->name, entry, type, reference);
	ptr   = ptr->next;
	reptr = reptr->next;
    }
    ASSERT (reptr == NIL (TypeTupleEntryP));
}

void
types_compute_local_renaming PROTO_N ((names, exclude, translator, state,
				       table))
			     PROTO_T (TypeTupleP  names X
				      TypeTupleP  exclude X
				      TypeRTransP translator X
				      SaveRStackP state X
				      TableP      table)
{
    TypeTupleEntryP ptr;

    for (ptr = names->head; ptr; ptr = ptr->next) {
	if (!types_contains (exclude, ptr->name)) {
	    EntryP type;
	    BoolT  reference;

	    if (rstack_get_translation (state, ptr->name, &type,
					&reference) != NIL (EntryP)) {
		EntryP entry = table_add_generated_name (table);

		rtrans_add_translation (translator, ptr->name, entry,
					ptr->type, ptr->reference);
	    } else {
		rtrans_add_translation (translator, ptr->name, ptr->name,
					ptr->type, ptr->reference);
	    }
	}
    }
}

void
types_compute_param_from_trans PROTO_N ((new_param, from_translator,
					 to_translator, old_param))
			       PROTO_T (TypeTupleP  new_param X
					TypeNTransP from_translator X
					TypeNTransP to_translator X
					TypeTupleP  old_param)
{
    TypeTupleEntryP ptr;

    types_init (new_param);
    for (ptr = old_param->head; ptr; ptr = ptr->next) {
	EntryP entry = ntrans_get_indirect_translation (from_translator,
							to_translator,
							ptr->name);

	if (entry) {
	    types_add_name_and_type (new_param, entry, ptr->type,
				     ptr->reference);
	}
    }
}

BoolT
types_check_shadowing PROTO_N ((tuple, stack, rule))
		      PROTO_T (TypeTupleP  tuple X
			       ScopeStackP stack X
			       RuleP       rule)
{
    BoolT           errored = FALSE;
    TypeTupleEntryP ptr;

    for (ptr = tuple->head; ptr; ptr = ptr->next) {
	if (scope_stack_check_shadowing (stack, ptr->name, rule)) {
	    errored = TRUE;
	}
    }
    return (errored);
}

void
types_iter_for_table PROTO_N ((tuple, proc, closure))
		     PROTO_T (TypeTupleP tuple X
			      void     (*proc) PROTO_S ((EntryP, GenericP)) X
			      GenericP   closure)
{
    TypeTupleEntryP ptr;

    for (ptr = tuple->head; ptr; ptr = ptr->next) {
	if (ptr->type) {
	    entry_iter (ptr->type, TRUE, proc, closure);
	}
	if (ptr->name) {
	    entry_iter (ptr->name, TRUE, proc, closure);
	}
    }
}

void
types_destroy PROTO_N ((tuple))
	      PROTO_T (TypeTupleP tuple)
{
    TypeTupleEntryP tuple_ptr = (tuple->head);

    while (tuple_ptr) {
	TypeTupleEntryP tmp_ptr = (tuple_ptr->next);

	DEALLOCATE (tuple_ptr);
	tuple_ptr = tmp_ptr;
    }
}

void
write_type_types PROTO_N ((ostream, tuple))
		 PROTO_T (OStreamP   ostream X
			  TypeTupleP tuple)
{
    TypeTupleEntryP type;

    write_char (ostream, '(');
    for (type = tuple->head; type; type = type->next) {
	if (type->type) {
	    write_cstring (ostream, ": ");
	    write_key (ostream, entry_key (type->type));
	    if (type->reference) {
		write_cstring (ostream, " &");
	    }
	} else {
	    write_cstring (ostream, ": <unknown>");
	}
	if (type->next) {
	    write_cstring (ostream, ", ");
	}
    }
    write_char (ostream, ')');
}

void
write_type_names PROTO_N ((ostream, tuple, call))
		 PROTO_T (OStreamP   ostream X
			  TypeTupleP tuple X
			  BoolT      call)
{
    TypeTupleEntryP type;

    write_char (ostream, '(');
    for (type = tuple->head; type; type = type->next) {
	if (type->name) {
	    if ((call && type->reference) || (type->assign)) {
		write_char (ostream, '&');
	    }
	    write_key (ostream, entry_key (type->name));
	}
	if (type->type) {
	    write_cstring (ostream, ": ");
	    write_key (ostream, entry_key (type->type));
	    if (type->reference) {
		write_cstring (ostream, " &");
	    }
	}
	if (type->next) {
	    write_cstring (ostream, ", ");
	}
    }
    write_char (ostream, ')');
}

/*==========================================================================*\
|| Basic name translator handling functions.
\*==========================================================================*/

void
btrans_init PROTO_N ((translator))
	    PROTO_T (TypeBTransP translator)
{
    translator->head = NIL (TransP);
    translator->tail = &(translator->head);
}

void
btrans_add_translations PROTO_N ((translator, from, to))
			PROTO_T (TypeBTransP translator X
				 TypeTupleP  from X
				 TypeTupleP  to)
{
    TypeTupleEntryP from_ptr = from->head;
    TypeTupleEntryP to_ptr   = to->head;

    while (from_ptr) {
	ASSERT (to_ptr != NIL (TypeTupleEntryP));
	btrans_add_translation (translator, from_ptr->name, to_ptr->name);
	from_ptr = from_ptr->next;
	to_ptr   = to_ptr->next;
    }
    ASSERT (to_ptr == NIL (TypeTupleEntryP));
}

void
btrans_add_translation PROTO_N ((translator, from, to))
		       PROTO_T (TypeBTransP translator X
				EntryP      from X
				EntryP      to)
{
    TransP link = ALLOCATE (TransT);

    link->to            = to;
    link->from          = from;
    link->next          = NIL (TransP);
    *(translator->tail) = link;
    translator->tail    = &(link->next);
}

void
btrans_generate_names PROTO_N ((translator, tuple, table))
		      PROTO_T (TypeBTransP translator X
			       TypeTupleP  tuple X
			       TableP      table)
{
    TypeTupleEntryP tuple_ptr = tuple->head;

    while (tuple_ptr) {
	btrans_add_translation (translator, tuple_ptr->name,
				table_add_generated_name (table));
	tuple_ptr = tuple_ptr->next;
    }
}

void
btrans_regenerate_names PROTO_N ((translator, tuple))
			PROTO_T (TypeBTransP translator X
				 TypeTupleP  tuple)
{
    TypeTupleEntryP  tuple_ptr = tuple->head;
    TransP           trans_ptr = translator->head;

    while (tuple_ptr) {
	ASSERT (trans_ptr != NIL (TransP));
	trans_ptr->from = tuple_ptr->name;
	trans_ptr       = trans_ptr->next;
	tuple_ptr       = tuple_ptr->next;
    }
    ASSERT (trans_ptr == NIL (TransP));
}

ItemP
btrans_generate_non_pred_names PROTO_N ((translator, tuple, result,
					 predicate_id, table))
			       PROTO_T (TypeBTransP translator X
					TypeTupleP  tuple X
					TypeTupleP  result X
					EntryP      predicate_id X
					TableP      table)
{
    TypeTupleEntryP ptr = tuple->head;
    TypeTupleT      from;
    TypeTupleT      to;

    types_init (&from);
    types_init (&to);
    while (ptr) {
	if (ptr->name == predicate_id) {
	    btrans_add_translation (translator, predicate_id, predicate_id);
	} else {
	    EntryP entry = table_add_generated_name (table);

	    btrans_add_translation (translator, ptr->name, entry);
	    if (types_contains (result, ptr->name)) {
		types_add_name_and_type (&from, entry, ptr->type,
					 ptr->reference);
		types_add_name_and_type (&to, ptr->name, ptr->type,
					 ptr->reference);
	    }
	}
	ptr = ptr->next;
    }
    if (types_equal_zero_tuple (&from)) {
	types_destroy (&from);
	types_destroy (&to);
	return (NIL (ItemP));
    } else {
	ItemP item = item_create (table_add_rename (table));

	types_assign (item_param (item), &from);
	types_assign (item_result (item), &to);
	return (item);
    }
}

ItemP
btrans_regen_non_pred_names PROTO_N ((translator, tuple, result, table))
			    PROTO_T (TypeBTransP translator X
				     TypeTupleP  tuple X
				     TypeTupleP  result X
				     TableP      table)
{
    TypeTupleEntryP tuple_ptr = tuple->head;
    TransP          trans_ptr = translator->head;
    TypeTupleT      from;
    TypeTupleT      to;

    types_init (&from);
    types_init (&to);
    while (tuple_ptr) {
	ASSERT (trans_ptr != NIL (TransP));
	trans_ptr->from = tuple_ptr->name;
	if (types_contains (result, tuple_ptr->name)) {
	    types_add_name_and_type (&from, trans_ptr->to, tuple_ptr->type,
				     tuple_ptr->reference);
	    types_add_name_and_type (&to, trans_ptr->from, tuple_ptr->type,
				     tuple_ptr->reference);
	}
	trans_ptr       = trans_ptr->next;
	tuple_ptr       = tuple_ptr->next;
    }
    ASSERT (trans_ptr == NIL (TransP));
    if (types_equal_zero_tuple (&from)) {
	types_destroy (&from);
	types_destroy (&to);
	return (NIL (ItemP));
    } else {
	ItemP item = item_create (table_add_rename (table));

	types_assign (item_param (item), &from);
	types_assign (item_result (item), &to);
	return (item);
    }
}

EntryP
btrans_get_translation PROTO_N ((translator, entry))
		       PROTO_T (TypeBTransP translator X
				EntryP      entry)
{
    EntryP translation = NIL (EntryP);
    TransP ptr;

    for (ptr = translator->head; ptr; ptr = ptr->next) {
	if (ptr->from == entry) {
	    translation = ptr->to;
	}
    }
    return (translation);
}

void
btrans_destroy PROTO_N ((translator))
	       PROTO_T (TypeBTransP translator)
{
    TransP ptr = (translator->head);
    TransP tmp;

    while ((tmp = ptr) != NIL (TransP)) {
	ptr = ptr->next;
	DEALLOCATE (tmp);
    }
}

/*==========================================================================*\
|| Rename stack name translator handling functions.
\*==========================================================================*/

void
rtrans_init PROTO_N ((translator))
	    PROTO_T (TypeRTransP translator)
{
    translator->head = NIL (RTransP);
    translator->tail = &(translator->head);
}

void
rtrans_add_translation PROTO_N ((translator, from, to, type, reference))
		       PROTO_T (TypeRTransP translator X
				EntryP      from X
				EntryP      to X
				EntryP      type X
				BoolT       reference)
{
    RTransP link = ALLOCATE (RTransT);

    link->next          = NIL (RTransP);
    link->to            = to;
    link->from          = from;
    link->type          = type;
    link->reference     = reference;
    *(translator->tail) = link;
    translator->tail    = &(link->next);
}

EntryP
rtrans_get_translation PROTO_N ((translator, entry, type_ref, reference_ref))
		       PROTO_T (TypeRTransP translator X
				EntryP      entry X
				EntryP     *type_ref X
				BoolT      *reference_ref)
{
    RTransP ptr;

    for (ptr = translator->head; ptr; ptr = ptr->next) {
	if (ptr->from == entry) {
	    *type_ref      = ptr->type;
	    *reference_ref = ptr->reference;
	    return (ptr->to);
	}
    }
    return (NIL (EntryP));
}

void
rtrans_apply_for_non_locals PROTO_N ((translator, proc, closure))
			    PROTO_T (TypeRTransP translator X
				     void      (*proc) PROTO_S ((EntryP,
								 EntryP,
								 GenericP)) X
				     GenericP    closure)
{
    RTransP ptr;

    for (ptr = translator->head; ptr; ptr = ptr->next) {
	(*proc) (ptr->from, ptr->to, closure);
    }
}

void
rtrans_destroy PROTO_N ((translator))
	       PROTO_T (TypeRTransP translator)
{
    RTransP ptr = (translator->head);
    RTransP tmp;

    while ((tmp = ptr) != NIL (RTransP)) {
	ptr = ptr->next;
	DEALLOCATE (tmp);
    }
}

/*==========================================================================*\
|| Name translator handling functions.
\*==========================================================================*/

void
trans_init PROTO_N ((translator, param, result, alt))
	   PROTO_T (TypeTransP translator X
		    TypeTupleP param X
		    TypeTupleP result X
		    AltP       alt)
{
    TypeTupleEntryP ptr;
    ItemP           item;

    translator->head = NIL (TransP);
    translator->tail = &(translator->head);
    entry_list_init (&(translator->used_names));
    for (ptr = param->head; ptr; ptr = ptr->next) {
        entry_list_add_if_missing (&(translator->used_names), ptr->name);
    }
    for (ptr = result->head; ptr; ptr = ptr->next) {
	entry_list_add_if_missing (&(translator->used_names), ptr->name);
    }
    for (item = alt_item_head (alt); item; item = item_next (item)) {
        TypeTupleP type = item_result (item);

	for (ptr = type->head; ptr; ptr = ptr->next) {
	    entry_list_add_if_missing (&(translator->used_names), ptr->name);
	}
    }
}

void
trans_add_translation PROTO_N ((translator, from, to))
		      PROTO_T (TypeTransP translator X
			       EntryP     from X
			       EntryP     to)
{
    TransP link = ALLOCATE (TransT);

    link->to            = to;
    link->from          = from;
    link->next          = NIL (TransP);
    *(translator->tail) = link;
    translator->tail    = &(link->next);
}

void
trans_add_translations PROTO_N ((translator, from, to))
		       PROTO_T (TypeTransP translator X
				TypeTupleP from X
				TypeTupleP to)
{
    TypeTupleEntryP from_ptr = from->head;
    TypeTupleEntryP to_ptr   = to->head;

    while (from_ptr) {
	ASSERT (to_ptr != NIL (TypeTupleEntryP));
	trans_add_translation (translator, from_ptr->name, to_ptr->name);
	from_ptr = from_ptr->next;
	to_ptr   = to_ptr->next;
    }
    ASSERT (to_ptr == NIL (TypeTupleEntryP));
}

void
trans_save_state PROTO_N ((translator, state))
		 PROTO_T (TypeTransP translator X
			  SaveTransP state)
{
    state->last_ref = translator->tail;
}

EntryP
trans_get_translation PROTO_N ((translator, entry))
		      PROTO_T (TypeTransP translator X
			       EntryP     entry)
{
    EntryP translation = NIL (EntryP);
    TransP      ptr;

    for (ptr = translator->head; ptr; ptr = ptr->next) {
	if (ptr->from == entry) {
	    translation = ptr->to;
	}
    }
    if (translation) {
	return (translation);
    }
    if (!entry_list_contains (&(translator->used_names), entry)) {
        return (entry);
    }
    return (NIL (EntryP));
}

void
trans_restore_state PROTO_N ((translator, state))
		    PROTO_T (TypeTransP translator X
			     SaveTransP state)
{
    TransP ptr = (*(state->last_ref));
    TransP tmp;

    *(state->last_ref) = NIL (TransP);
    while ((tmp = ptr) != NIL (TransP)) {
	ptr = ptr->next;
	DEALLOCATE (tmp);
    }
    translator->tail = state->last_ref;
}

void
trans_destroy PROTO_N ((translator))
	      PROTO_T (TypeTransP translator)
{
    TransP ptr = (translator->head);
    TransP tmp;

    while ((tmp = ptr) != NIL (TransP)) {
	ptr = ptr->next;
	DEALLOCATE (tmp);
    }
    entry_list_destroy (&(translator->used_names));
}

/*==========================================================================*\
|| Numeric translator handling functions.
\*==========================================================================*/

static unsigned
ntrans_add_translation PROTO_N ((translator, from))
		       PROTO_T (TypeNTransP translator X
				EntryP      from)
{
    NTransP link = ALLOCATE (NTransT);

    if (translator->count == UINT_MAX) {
	E_too_many_generated_names ();
	UNREACHED;
    }
    link->to            = (translator->count) ++;
    link->from          = from;
    link->next          = NIL (NTransP);
    *(translator->tail) = link;
    translator->tail    = &(link->next);
    return (link->to);
}

/*--------------------------------------------------------------------------*/

void
ntrans_init PROTO_N ((translator))
	    PROTO_T (TypeNTransP translator)
{
    translator->count      = 0;
    translator->head       = NIL (NTransP);
    translator->tail       = &(translator->head);
}

void
ntrans_save_state PROTO_N ((translator, state))
		  PROTO_T (TypeNTransP translator X
			   SaveNTransP state)
{
    state->last_count = translator->count;
    state->last_ref   = translator->tail;
}

unsigned
ntrans_get_translation PROTO_N ((translator, entry))
		       PROTO_T (TypeNTransP translator X
				EntryP      entry)
{
    NTransP ptr;

    for (ptr = translator->head; ptr; ptr = ptr->next) {
	if (ptr->from == entry) {
	    return (ptr->to);
	}
    }
    return (ntrans_add_translation (translator, entry));
}

EntryP
ntrans_get_indirect_translation PROTO_N ((from_translator, to_translator,
					  entry))
				PROTO_T (TypeNTransP from_translator X
					 TypeNTransP to_translator X
					 EntryP      entry)
{
    NTransP  ptr;
    unsigned name;

    for (ptr = from_translator->head; ptr; ptr = ptr->next) {
	if (ptr->from == entry) {
	    name = ptr->to;
	    goto found;
	}
    }
    return (NIL (EntryP));
  found:
    for (ptr = to_translator->head; ptr; ptr = ptr->next) {
	if (ptr->to == name) {
	    return (ptr->from);
	}
    }
    UNREACHED;
}

void
ntrans_restore_state PROTO_N ((translator, state))
		     PROTO_T (TypeNTransP translator X
			      SaveNTransP state)
{
    NTransP ptr = (*(state->last_ref));
    NTransP tmp;

    *(state->last_ref) = NIL (NTransP);
    translator->count  = state->last_count;
    while ((tmp = ptr) != NIL (NTransP)) {
	ptr = ptr->next;
	DEALLOCATE (tmp);
    }
    translator->tail = state->last_ref;
}

void
ntrans_destroy PROTO_N ((translator))
	       PROTO_T (TypeNTransP translator)
{
    NTransP ptr = (translator->head);
    NTransP tmp;

    while ((tmp = ptr) != NIL (NTransP)) {
	ptr = ptr->next;
	DEALLOCATE (tmp);
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
