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


/*** rstack.c --- Renaming stack ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the renaming stack routines.  They are mainly used by
 * the output routines to do scoping of inlined rules.
 *
 *** Change Log:
 * $Log: rstack.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:58:31  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:37  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#include "rstack.h"
#include "action.h"
#include "basic.h"
#include "name.h"
#include "rule.h"
#include "type.h"

/*--------------------------------------------------------------------------*/

void
rstack_init PROTO_N ((rstack))
	    PROTO_T (RStackP rstack)
{
    rstack->head = NIL (TransStackEntryP);
}

void
rstack_push_frame PROTO_N ((rstack))
		  PROTO_T (RStackP rstack)
{
    TransStackEntryP frame = ALLOCATE (TransStackEntryT);

    frame->next = rstack->head;
    rtrans_init (&(frame->translator));
    rstack->head = frame;
}

void
rstack_compute_formal_renaming PROTO_N ((rstack, names))
			       PROTO_T (RStackP    rstack X
					TypeTupleP names)
{
    ASSERT (rstack->head);
    types_compute_formal_renaming (names, &(rstack->head->translator));
}

void
rstack_compute_formal_inlining PROTO_N ((rstack, names, renames))
			       PROTO_T (RStackP    rstack X
					TypeTupleP names X
					TypeTupleP renames)
{
    SaveRStackT state;

    ASSERT (rstack->head);
    state.head = rstack->head->next;
    types_compute_formal_inlining (names, renames, &(rstack->head->translator),
				   &state);
}

void
rstack_compute_local_renaming PROTO_N ((rstack, names, exclude, table))
			      PROTO_T (RStackP    rstack X
				       TypeTupleP names X
				       TypeTupleP exclude X
				       TableP     table)
{
    SaveRStackT state;

    ASSERT (rstack->head);
    state.head = rstack->head->next;
    types_compute_local_renaming (names, exclude, &(rstack->head->translator),
				  &state, table);
}

void
rstack_add_translation PROTO_N ((rstack, from, to, type, reference))
		       PROTO_T (RStackP rstack X
				EntryP  from X
				EntryP  to X
				EntryP  type X
				BoolT   reference)
{
    ASSERT (rstack->head);
    rtrans_add_translation (&(rstack->head->translator), from, to, type,
			    reference);
}

void
rstack_save_state PROTO_N ((rstack, state))
		  PROTO_T (RStackP     rstack X
			   SaveRStackP state)
{
    state->head = rstack->head;
}

EntryP
rstack_get_translation PROTO_N ((state, entry, type_ref, reference_ref))
		       PROTO_T (SaveRStackP state X
				EntryP      entry X
				EntryP     *type_ref X
				BoolT      *reference_ref)
{
    TransStackEntryP frame = state->head;

    while (frame) {
	EntryP translation;

	translation = rtrans_get_translation (&(frame->translator), entry,
					      type_ref, reference_ref);
	if (translation) {
	    return (translation);
	}
	frame = frame->next;
    }
    return (NIL (EntryP));
}

void
rstack_apply_for_non_locals PROTO_N ((non_local_stack, state, proc, closure))
			    PROTO_T (RStackP     non_local_stack X
				     SaveRStackP state X
				     void      (*proc) PROTO_S ((EntryP,
								 EntryP,
								 GenericP)) X
				     GenericP    closure)
{
    TransStackEntryP frame = non_local_stack->head;

    if ((frame != NIL (TransStackEntryP)) && (state->head)) {
	TransStackEntryP limit = state->head->next;

	for (; frame != limit; frame = frame->next) {
	    rtrans_apply_for_non_locals (&(frame->translator), proc, closure);
	}
    }
}

void
rstack_pop_frame PROTO_N ((rstack))
		 PROTO_T (RStackP rstack)
{
    TransStackEntryP frame = rstack->head;

    rstack->head = frame->next;
    rtrans_destroy (&(frame->translator));
    DEALLOCATE (frame);
}

void
rstack_destroy PROTO_N ((rstack))
	       PROTO_T (RStackP rstack)
{
    while (rstack->head) {
	rstack_pop_frame (rstack);
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
