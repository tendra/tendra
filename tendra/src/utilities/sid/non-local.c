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


/**** non-local.c --- Non local name ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the non local name list manipulation routines.
 *
 **** Change Log:*/

/****************************************************************************/

#include "non-local.h"

/*--------------------------------------------------------------------------*/

void
non_local_list_init PROTO_N ((non_locals))
		    PROTO_T (NonLocalListP non_locals)
{
    non_locals->head = NIL (NonLocalEntryP);
    non_locals->tail = &(non_locals->head);
}

NonLocalEntryP
non_local_list_add PROTO_N ((non_locals, name, type))
		   PROTO_T (NonLocalListP non_locals X
			    EntryP        name X
			    EntryP        type)
{
    NonLocalEntryP entry = ALLOCATE (NonLocalEntryT);

    entry->next         = NIL (NonLocalEntryP);
    entry->name         = name;
    entry->type         = type;
    entry->initialiser  = NIL (EntryP);
    *(non_locals->tail) = entry;
    non_locals->tail    = &(entry->next);
    return (entry);
}

BoolT
non_local_list_is_empty PROTO_N ((non_locals))
			PROTO_T (NonLocalListP non_locals)
{
    return (non_locals->head == NIL (NonLocalEntryP));
}

void
non_local_list_iter_for_table PROTO_N ((non_locals, proc, closure))
			      PROTO_T (NonLocalListP non_locals X
				       void        (*proc) PROTO_S ((EntryP,
								     GenericP))
				       X
				       GenericP      closure)
{
    NonLocalEntryP non_local;

    for (non_local = non_locals->head; non_local;
	 non_local = non_local->next) {
	entry_iter (non_local->type, TRUE, proc, closure);
	if (non_local->initialiser) {
	    entry_iter (non_local->initialiser, TRUE, proc, closure);
	}
    }
}

void
non_local_list_destroy PROTO_N ((non_locals))
		       PROTO_T (NonLocalListP non_locals)
{
    NonLocalEntryP entry = non_locals->head;

    while (entry) {
	NonLocalEntryP tmp = entry->next;

	DEALLOCATE (entry);
	entry = tmp;
    }
}

void
write_non_locals PROTO_N ((ostream, non_locals))
		 PROTO_T (OStreamP      ostream X
			  NonLocalListP non_locals)
{
    NonLocalEntryP non_local;

    for (non_local = non_locals->head; non_local;
	 non_local = non_local->next) {
	ASSERT (non_local->type);
	ASSERT (non_local->name);
	write_tab (ostream);
	write_key (ostream, entry_key (non_local->name));
	write_cstring (ostream, ": ");
	write_key (ostream, entry_key (non_local->type));
	if (non_local->initialiser) {
	    write_cstring (ostream, " = <");
	    write_key (ostream, entry_key (non_local->initialiser));
	    write_char (ostream, '>');
	}
	write_char (ostream, ';');
	write_newline (ostream);
    }
}

void
non_local_entry_set_initialiser PROTO_N ((non_local, init))
				PROTO_T (NonLocalEntryP non_local X
					 EntryP         init)
{
    non_local->initialiser = init;
}

EntryP
non_local_entry_get_initialiser PROTO_N ((non_local))
				PROTO_T (NonLocalEntryP non_local)
{
    return (non_local->initialiser);
}

EntryP
non_local_entry_get_name PROTO_N ((non_local))
			 PROTO_T (NonLocalEntryP non_local)
{
    return (non_local->name);
}

EntryP
non_local_entry_get_type PROTO_N ((non_local))
			 PROTO_T (NonLocalEntryP non_local)
{
    return (non_local->type);
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
