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


/*** item.c --- Item ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the item manipulation routines.  These are specified
 * in the file "rule.h".
 *
 *** Change Log:
 * $Log: item.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:58:17  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:34  smf
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

ItemP
item_create PROTO_N ((entry))
	    PROTO_T (EntryP entry)
{
    ItemP item = ALLOCATE (ItemT);

    item->next         = NIL (ItemP);
    types_init (item_param (item));
    types_init (item_result (item));
    item->type         = entry_type (entry);
    item->entry        = entry;
    item->inlinable    = FALSE;
    item->tail_call    = FALSE;
    return (item);
}

ItemP
item_duplicate PROTO_N ((item))
	       PROTO_T (ItemP item)
{
    ItemP new_item = ALLOCATE (ItemT);

    new_item->next         = NIL (ItemP);
    types_copy (item_param (new_item), item_param (item));
    types_copy (item_result (new_item), item_result (item));
    new_item->type         = item->type;
    new_item->entry        = item->entry;
    new_item->inlinable    = item->inlinable;
    new_item->tail_call    = item->tail_call;
    return (new_item);
}

ItemP
item_duplicate_and_translate PROTO_N ((item, translator, table))
			     PROTO_T (ItemP      item X
				      TypeTransP translator X
				      TableP     table)
{
    ItemP new_item = ALLOCATE (ItemT);

    new_item->next         = NIL (ItemP);
    types_copy_and_translate (item_param (new_item), item_param (item),
			      translator, table);
    types_copy_and_translate (item_result (new_item), item_result (item),
			      translator, table);
    new_item->type         = item->type;
    new_item->entry        = item->entry;
    new_item->inlinable    = item->inlinable;
    new_item->tail_call    = item->tail_call;
    return (new_item);
}

void
item_translate_list PROTO_N ((item, translator))
		    PROTO_T (ItemP       item X
			     TypeBTransP translator)
{
    for (; item; item = item_next (item)) {
	types_translate (item_param (item), translator);
	types_translate (item_result (item), translator);
    }
}

void
item_to_predicate PROTO_N ((item))
		  PROTO_T (ItemP item)
{
    ASSERT (item_is_action (item));
    item->type = ET_PREDICATE;
}

#ifdef FS_FAST
#undef item_next
#endif /* defined (FS_FAST) */
ItemP
item_next PROTO_N ((item))
	  PROTO_T (ItemP item)
{
    return (item->next);
}
#ifdef FS_FAST
#define item_next(i) ((i)->next)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef item_next_ref
#endif /* defined (FS_FAST) */
ItemP *
item_next_ref PROTO_N ((item))
	      PROTO_T (ItemP item)
{
    return (&(item->next));
}
#ifdef FS_FAST
#define item_next_ref(i) (&((i)->next))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef item_set_next
#endif /* defined (FS_FAST) */
void
item_set_next PROTO_N ((item1, item2))
	      PROTO_T (ItemP item1 X
		       ItemP item2)
{
    item1->next = item2;
}
#ifdef FS_FAST
#define item_set_next(i1, i2) ((i1)->next = (i2))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef item_entry
#endif /* defined (FS_FAST) */
EntryP
item_entry PROTO_N ((item))
	   PROTO_T (ItemP item)
{
    return (item->entry);
}
#ifdef FS_FAST
#define item_entry(i) ((i)->entry)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef item_set_entry
#endif /* defined (FS_FAST) */
void
item_set_entry PROTO_N ((item, entry))
	       PROTO_T (ItemP  item X
			EntryP entry)
{
    item->entry = entry;
}
#ifdef FS_FAST
#define item_set_entry(i, e) ((i)->entry = (e))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef item_type
#endif /* defined (FS_FAST) */
EntryTypeT
item_type PROTO_N ((item))
	  PROTO_T (ItemP item)
{
    return (item->type);
}
#ifdef FS_FAST
#define item_type(i) ((i)->type)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef item_is_rule
#endif /* defined (FS_FAST) */
BoolT
item_is_rule PROTO_N ((item))
	     PROTO_T (ItemP item)
{
    return (item->type == ET_RULE);
}
#ifdef FS_FAST
#define item_is_rule(i) ((i)->type == ET_RULE)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef item_is_action
#endif /* defined (FS_FAST) */
BoolT
item_is_action PROTO_N ((item))
	       PROTO_T (ItemP item)
{
    return (item->type == ET_ACTION);
}
#ifdef FS_FAST
#define item_is_action(i) ((i)->type == ET_ACTION)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef item_is_predicate
#endif /* defined (FS_FAST) */
BoolT
item_is_predicate PROTO_N ((item))
		  PROTO_T (ItemP item)
{
    return (item->type == ET_PREDICATE);
}
#ifdef FS_FAST
#define item_is_predicate(i) ((i)->type == ET_PREDICATE)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef item_is_basic
#endif /* defined (FS_FAST) */
BoolT
item_is_basic PROTO_N ((item))
	      PROTO_T (ItemP item)
{
    return (item->type == ET_BASIC);
}
#ifdef FS_FAST
#define item_is_basic(i) ((i)->type == ET_BASIC)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef item_is_rename
#endif /* defined (FS_FAST) */
BoolT
item_is_rename PROTO_N ((item))
	       PROTO_T (ItemP item)
{
    return (item->type == ET_RENAME);
}
#ifdef FS_FAST
#define item_is_rename(i) ((i)->type == ET_RENAME)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef item_param
#endif /* defined (FS_FAST) */
TypeTupleP
item_param PROTO_N ((item))
	   PROTO_T (ItemP item)
{
    return (&(item->param));
}
#ifdef FS_FAST
#define item_param(i) (&((i)->param))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef item_add_param
#endif /* defined (FS_FAST) */
void
item_add_param PROTO_N ((item, param))
	       PROTO_T (ItemP      item X
			TypeTupleP param)
{
    types_assign (item_param (item), param);
}
#ifdef FS_FAST
#define item_add_param(i, t) (types_assign (&((i)->param), (t)))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef item_result
#endif /* defined (FS_FAST) */
TypeTupleP
item_result PROTO_N ((item))
	    PROTO_T (ItemP item)
{
    return (&(item->result));
}
#ifdef FS_FAST
#define item_result(i) (&((i)->result))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef item_add_result
#endif /* defined (FS_FAST) */
void
item_add_result PROTO_N ((item, result))
		PROTO_T (ItemP      item X
			 TypeTupleP result)
{
    types_assign (item_result (item), result);
}
#ifdef FS_FAST
#define item_add_result(i, t) (types_assign (&((i)->result), (t)))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef item_is_inlinable
#endif /* defined (FS_FAST) */
BoolT
item_is_inlinable PROTO_N ((item))
		  PROTO_T (ItemP item)
{
    return (item->inlinable);
}
#ifdef FS_FAST
#define item_is_inlinable(i) ((i)->inlinable)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef item_inlinable
#endif /* defined (FS_FAST) */
void
item_inlinable PROTO_N ((item))
	       PROTO_T (ItemP item)
{
    item->inlinable = TRUE;
}
#ifdef FS_FAST
#define item_inlinable(i) ((i)->inlinable = TRUE)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef item_is_tail_call
#endif /* defined (FS_FAST) */
BoolT
item_is_tail_call PROTO_N ((item))
		  PROTO_T (ItemP item)
{
    return (item->tail_call);
}
#ifdef FS_FAST
#define item_is_tail_call(i) ((i)->tail_call)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef item_tail_call
#endif /* defined (FS_FAST) */
void
item_tail_call PROTO_N ((item))
	       PROTO_T (ItemP item)
{
    item->tail_call = TRUE;
}
#ifdef FS_FAST
#define item_tail_call(i) ((i)->tail_call = TRUE)
#endif /* defined (FS_FAST) */

BoolT
item_names_used_in_list PROTO_N ((item, names))
			PROTO_T (ItemP      item X
				 TypeTupleP names)
{
    while (item) {
	if ((types_intersect (item_param (item), names)) ||
	    (types_intersect (item_result (item), names))) {
	    return (TRUE);
	}
	item = item_next (item);
    }
    return (FALSE);
}

void
item_compute_minimal_dataflow PROTO_N ((item, used))
			      PROTO_T (ItemP      item X
				       TypeTupleP used)
{
    if (item) {
	ItemP next = item_next (item);

	if (next) {
	    item_compute_minimal_dataflow (next, used);
	}
	if (item_is_inlinable (item)) {
	    RuleP rule = entry_get_rule (item_entry (item));

	    types_inplace_intersection (item_result (item), used);
	    types_inplace_intersection (rule_result (rule), used);
	    rule_compute_minimal_dataflow (rule, item_param (item));
	}
	types_add_new_names (used, item_param (item), NIL (EntryP));
    }
}

ItemP
item_deallocate PROTO_N ((item))
		PROTO_T (ItemP item)
{
    ItemP next = item_next (item);

    types_destroy (item_param (item));
    types_destroy (item_result (item));
    DEALLOCATE (item);
    return (next);
}

void
write_item PROTO_N ((ostream, item))
	   PROTO_T (OStreamP ostream X
		    ItemP    item)
{
    EntryP entry = item_entry (item);

    write_type_names (ostream, item_result (item), TRUE);
    if (item_is_predicate (item)) {
	write_cstring (ostream, " ?");
    }
    write_cstring (ostream, " = ");
    switch (item_type (item)) EXHAUSTIVE {
      case ET_ACTION:
      case ET_PREDICATE:
	write_char (ostream, '<');
	write_key (ostream, entry_key (entry));
	write_cstring (ostream, "> ");
	break;
      case ET_RULE:
	if (item_is_inlinable (item)) {
	    if (item_is_tail_call (item)) {
		write_char (ostream, '*');
	    } else {
		write_char (ostream, '+');
	    }
	}
	FALL_THROUGH;
      case ET_BASIC:
	write_key (ostream, entry_key (item_entry (item)));
	write_char (ostream, ' ');
	break;
      case ET_RENAME:
	break;
      case ET_NON_LOCAL:
      case ET_NAME:
      case ET_TYPE:
	UNREACHED;
    }
    write_type_names (ostream, item_param (item), TRUE);
    write_char (ostream, ';');
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
