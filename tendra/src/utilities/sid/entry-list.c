/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
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


/*** entry-list.c --- Identifier table entry list ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the SID table entry list routines.
 *
 *** Change Log:*/

/****************************************************************************/

#include "entry-list.h"
#include "action.h"
#include "basic.h"
#include "name.h"
#include "rule.h"
#include "type.h"

/*--------------------------------------------------------------------------*/

typedef struct EntrySortListT {
    EntryListEntryP		head;
    EntryListEntryP	       *tail;
} EntrySortListT, *EntrySortListP;

/*--------------------------------------------------------------------------*/

static EntryListEntryP
entry_list_find PROTO_N ((list, entry))
		PROTO_T (EntryListP list X
			 EntryP     entry)
{
    EntryListEntryP link = list->head;

    while (link) {
	if (link->entry == entry) {
	    return (link);
	}
	link = link->next;
    }
    return (NIL (EntryListEntryP));
}

/*--------------------------------------------------------------------------*/

void
entry_list_init PROTO_N ((list))
		PROTO_T (EntryListP list)
{
    list->head = NIL (EntryListEntryP);
    list->tail = &(list->head);
}

void
entry_list_copy PROTO_N ((to, from))
		PROTO_T (EntryListP to X
			 EntryListP from)
{
    EntryListEntryP ptr;

    to->head = NIL (EntryListEntryP);
    to->tail = &(to->head);
    for (ptr = from->head; ptr; ptr = ptr->next) {
	entry_list_add (to, ptr->entry);
    }
}

void
entry_list_add PROTO_N ((list, entry))
	       PROTO_T (EntryListP list X
			EntryP     entry)
{
    EntryListEntryP link = ALLOCATE (EntryListEntryT);

    link->next    = NIL (EntryListEntryP);
    link->entry   = entry;
    *(list->tail) = link;
    list->tail    = &(link->next);
}

void
entry_list_add_if_missing PROTO_N ((list, entry))
			  PROTO_T (EntryListP list X
				   EntryP     entry)
{
    if (entry_list_find (list, entry) == NIL (EntryListEntryP)) {
	entry_list_add (list, entry);
    }
}

BoolT
entry_list_contains PROTO_N ((list, entry))
		    PROTO_T (EntryListP list X
			     EntryP     entry)
{
    return (entry_list_find (list, entry) != NIL (EntryListEntryP));
}

BoolT
entry_list_includes PROTO_N ((list1, list2))
		    PROTO_T (EntryListP list1 X
			     EntryListP list2)
{
    EntryListEntryP ptr;

    for (ptr = list2->head; ptr; ptr = ptr->next) {
	if (entry_list_find (list1, ptr->entry) == NIL (EntryListEntryP)) {
	    return (FALSE);
	}
    }
    return (TRUE);
}

void
entry_list_intersection PROTO_N ((to, list1, list2))
			PROTO_T (EntryListP to X
				 EntryListP list1 X
				 EntryListP list2)
{
    EntryListEntryP ptr;

    entry_list_init (to);
    for (ptr = list1->head; ptr; ptr = ptr->next) {
	if (entry_list_find (list2, ptr->entry) != NIL (EntryListEntryP)) {
	    entry_list_add_if_missing (to, ptr->entry);
	}
    }
}

void
entry_list_unlink_used PROTO_N ((to, from))
		       PROTO_T (EntryListP to X
				EntryListP from)
{
    EntryListEntryP ptr;

    to->tail = &(to->head);
    while ((ptr = *(to->tail)) != NIL (EntryListEntryP)) {
	if (entry_list_find (from, ptr->entry) != NIL (EntryListEntryP)) {
	    *(to->tail) = ptr->next;
	    DEALLOCATE (ptr);
	} else {
	    to->tail = &(ptr->next);
	}
    }
}

void
entry_list_append PROTO_N ((to, from))
		  PROTO_T (EntryListP to X
			   EntryListP from)
{
    EntryListEntryP ptr;

    for (ptr = from->head; ptr; ptr = ptr->next) {
	entry_list_add_if_missing (to, ptr->entry);
    }
}

#ifdef FS_FAST
#undef entry_list_is_empty
#endif /* defined (FS_FAST) */
BoolT
entry_list_is_empty PROTO_N ((list))
		    PROTO_T (EntryListP list)
{
    return (list->head == NIL (EntryListEntryP));
}
#ifdef FS_FAST
#define entry_list_is_empty(e) ((e)->head == NIL (EntryListEntryP))
#endif /* defined (FS_FAST) */

void
entry_list_save_state PROTO_N ((list, state))
		      PROTO_T (EntryListP list X
			       SaveListP  state)
{
    state->last_ref = list->tail;
}

void
entry_list_restore_state PROTO_N ((list, state))
			 PROTO_T (EntryListP list X
				  SaveListP  state)
{
    EntryListEntryP ptr = *(state->last_ref);

    *(state->last_ref) = NIL (EntryListEntryP);
    list->tail         = state->last_ref;
    while (ptr) {
	EntryListEntryP tmp = ptr;

	ptr = ptr->next;
	DEALLOCATE (tmp);
    }
}

void
entry_list_iter PROTO_N ((list, proc, closure))
		PROTO_T (EntryListP list X
			 void     (*proc) PROTO_S ((EntryP, GenericP)) X
			 GenericP   closure)
{
    EntryListEntryP ptr;

    for (ptr = list->head; ptr; ptr = ptr->next) {
	(*proc) (ptr->entry, closure);
    }
}

void
entry_list_iter_table PROTO_N ((list, full, proc, closure))
		      PROTO_T (EntryListP list X
			       BoolT      full X
			       void     (*proc) PROTO_S ((EntryP, GenericP)) X
			       GenericP   closure)
{
    EntryListEntryP ptr;

    for (ptr = list->head; ptr; ptr = ptr->next) {
	entry_iter (ptr->entry, full, proc, closure);
    }
}

void
entry_list_destroy PROTO_N ((list))
		   PROTO_T (EntryListP list)
{
    EntryListEntryP ptr = list->head;

    while (ptr) {
	EntryListEntryP tmp = ptr;

	ptr = ptr->next;
	DEALLOCATE (tmp);
    }
}

void
write_entry_list PROTO_N ((ostream, list))
		 PROTO_T (OStreamP   ostream X
			  EntryListP list)
{
    EntryListEntryP ptr = list->head;
    CStringP        sep = "";

    while (ptr) {
	write_cstring (ostream, sep);
	write_char (ostream, '\'');
	write_key (ostream, entry_key (ptr->entry));
	write_char (ostream, '\'');
	if ((ptr = ptr->next) && (ptr->next)) {
	    sep = " & ";
	} else {
	    sep = ", ";
	}
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
