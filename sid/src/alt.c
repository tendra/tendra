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


/*** alt.c --- Alternative ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the alternative manipulation routines.  They are
 * specified in the file "rule.h".
 *
 *** Change Log:
 * $Log: alt.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:42  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:57:59  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:31  smf
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

AltP
alt_create PROTO_Z ()
{
    AltP alt = ALLOCATE (AltT);

    alt->next      = NIL (AltP);
    types_init (alt_names (alt));
    bitvec_init (alt_first_set (alt));
    alt->item_head = NIL (ItemP);
    alt->item_tail = &(alt->item_head);
    return (alt);
}

AltP
alt_create_merge PROTO_N ((initial_item, trailing_item, translator, table))
		 PROTO_T (ItemP      initial_item X
			  ItemP      trailing_item X
			  TypeTransP translator X
			  TableP     table)
{
    AltP alt = alt_create ();

    for (; initial_item; initial_item = item_next (initial_item)) {
	ItemP new_item = item_duplicate_and_translate (initial_item,
						       translator,
						       table);

	alt_add_item (alt, new_item);
    }
    for (; trailing_item; trailing_item = item_next (trailing_item)) {
	ItemP new_item = item_duplicate (trailing_item);

	alt_add_item (alt, new_item);
    }
    return (alt);
}

AltP
alt_duplicate PROTO_N ((alt))
	      PROTO_T (AltP alt)
{
    AltP  new_alt = alt_create ();
    ItemP item;

    for (item = alt_item_head (alt); item; item = item_next (item)) {
	ItemP new_item = item_duplicate (item);

	alt_add_item (new_alt, new_item);
    }
    return (new_alt);
}

BoolT
alt_less_than PROTO_N ((alt1, alt2))
	      PROTO_T (AltP alt1 X
		       AltP alt2)
{
    ItemP      item1 = alt_item_head (alt1);
    ItemP      item2 = alt_item_head (alt2);
    KeyP       key1;
    KeyP       key2;
    TypeTupleP type1;
    TypeTupleP type2;

    if (item_type (item1) < item_type (item2)) {
	return (TRUE);
    } else if (item_type (item1) > item_type (item2)) {
	return (FALSE);
    }
    key1 = entry_key (item_entry (item1));
    key2 = entry_key (item_entry (item2));
    switch (key_compare (key1, key2)) EXHAUSTIVE {
      case CMP_LT:
	return (TRUE);
      case CMP_GT:
	return (FALSE);
      case CMP_EQ:
	break;
    }
    type1 = item_param (item1);
    type2 = item_param (item2);
    switch (types_compare (type1, type2)) EXHAUSTIVE {
      case CMP_LT:
	return (TRUE);
      case CMP_GT:
	return (FALSE);
      case CMP_EQ:
	break;
    }
    type1 = item_result (item1);
    type2 = item_result (item2);
    switch (types_compare (type1, type2)) EXHAUSTIVE {
      case CMP_LT:
	return (TRUE);
      case CMP_GT:
	return (FALSE);
      case CMP_EQ:
	break;
    }
    UNREACHED;
}

BoolT
alt_equal PROTO_N ((alt1, alt2))
	  PROTO_T (AltP alt1 X
		   AltP alt2)
{
    ItemP item1;
    ItemP item2;

    if ((alt1 == NIL (AltP)) && (alt2 == NIL (AltP))) {
	return (TRUE);
    } else if ((alt1 == NIL (AltP)) || (alt2 == NIL (AltP))) {
	return (FALSE);
    }
    item1 = alt_item_head (alt1);
    item2 = alt_item_head (alt2);
    while (item1 && item2) {
	if ((item_entry (item1) == item_entry (item2)) &&
	    (types_equal_numbers (item_param (item1), item_param (item2))) &&
	    (types_equal_numbers (item_result (item1), item_result (item2)))) {
	    item1 = item_next (item1);
	    item2 = item_next (item2);
	} else {
	    return (FALSE);
	}
    }
    return (item1 == item2);
}

#ifdef FS_FAST
#undef alt_next
#endif /* defined (FS_FAST) */
AltP
alt_next PROTO_N ((alt))
	 PROTO_T (AltP alt)
{
    return (alt->next);
}
#ifdef FS_FAST
#define alt_next(a) ((a)->next)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef alt_next_ref
#endif /* defined (FS_FAST) */
AltP *
alt_next_ref PROTO_N ((alt))
	     PROTO_T (AltP alt)
{
    return (&(alt->next));
}
#ifdef FS_FAST
#define alt_next_ref(a) (&((a)->next))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef alt_set_next
#endif /* defined (FS_FAST) */
void
alt_set_next PROTO_N ((alt1, alt2))
	     PROTO_T (AltP alt1 X
		      AltP alt2)
{
    alt1->next = alt2;
}
#ifdef FS_FAST
#define alt_set_next(a1, a2) ((a1)->next = (a2))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef alt_names
#endif /* defined (FS_FAST) */
TypeTupleP
alt_names PROTO_N ((alt))
	  PROTO_T (AltP alt)
{
    return (&(alt->names));
}
#ifdef FS_FAST
#define alt_names(a) (&((a)->names))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef alt_first_set
#endif /* defined (FS_FAST) */
BitVecP
alt_first_set PROTO_N ((alt))
	      PROTO_T (AltP alt)
{
    return (&(alt->first_set));
}
#ifdef FS_FAST
#define alt_first_set(a) (&((a)->first_set))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef alt_item_head
#endif /* defined (FS_FAST) */
ItemP
alt_item_head PROTO_N ((alt))
	      PROTO_T (AltP alt)
{
    return (alt->item_head);
}
#ifdef FS_FAST
#define alt_item_head(a) ((a)->item_head)
#endif /* defined (FS_FAST) */

ItemP
alt_unlink_item_head PROTO_N ((alt))
		     PROTO_T (AltP alt)
{
    ItemP item = alt_item_head (alt);

    alt->item_head = item_next (item);
    item_set_next (item, NIL (ItemP));
    if (alt->item_tail == item_next_ref (item)) {
	alt->item_tail = &(alt->item_head);
    }
    return (item);
}

void
alt_add_item PROTO_N ((alt, item))
	     PROTO_T (AltP  alt X
		      ItemP item)
{
    *(alt->item_tail) = item;
    alt->item_tail    = item_next_ref (item);
}

AltP
alt_deallocate PROTO_N ((alt))
	       PROTO_T (AltP alt)
{
    AltP  next = alt_next (alt);
    ItemP item;

    for (item = alt_item_head (alt); item; item = item_deallocate (item)) {
	/*NOTHING*/
    }
    types_destroy (alt_names (alt));
    bitvec_destroy (alt_first_set (alt));
    DEALLOCATE (alt);
    return (next);
}

void
write_alt PROTO_N ((ostream, alt))
	  PROTO_T (OStreamP ostream X
		   AltP     alt)
{
    ItemP item;

    for (item = alt_item_head (alt); item; item = item_next (item)) {
	write_tab (ostream);
	write_item (ostream, item);
	write_newline (ostream);
    }
}

void
write_alt_highlighting PROTO_N ((ostream, alt, highlight))
		       PROTO_T (OStreamP ostream X
				AltP     alt X
				ItemP    highlight)
{
    ItemP item;

    for (item = alt_item_head (alt); item; item = item_next (item)) {
	if (item == highlight) {
	    write_cstring (ostream, "==>>");
	}
	write_tab (ostream);
	write_item (ostream, item);
	write_newline (ostream);
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
