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


/**** cstring-list.c --- String list ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the string list facility specified in the file
 * "cstring-list.h".  See that file for more details.
 *
 **** Change Log:
 * $Log: cstring-list.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:45  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:44:30  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:05:48  smf
 * Initial import of library shared files.
 *
**/

/****************************************************************************/

#include "cstring-list.h"

/*--------------------------------------------------------------------------*/

void
cstring_list_init PROTO_N ((list))
		  PROTO_T (CStringListP list)
{
    list->head = NIL (CStringListEntryP);
    list->tail = &(list->head);
}

void
cstring_list_append PROTO_N ((list, string))
		    PROTO_T (CStringListP list X
			     CStringP     string)
{
    CStringListEntryP entry = ALLOCATE (CStringListEntryT);

    entry->next   = NIL (CStringListEntryP);
    entry->string = string;
    *(list->tail) = entry;
    list->tail    = &(entry->next);
}

CStringListEntryP
cstring_list_head PROTO_N ((list))
		  PROTO_T (CStringListP list)
{
    return (list->head);
}

CStringP
cstring_list_entry_string PROTO_N ((entry))
			  PROTO_T (CStringListEntryP entry)
{
    return (entry->string);
}

CStringListEntryP
cstring_list_entry_deallocate PROTO_N ((entry))
			      PROTO_T (CStringListEntryP entry)
{
    CStringListEntryP next = entry->next;

    DEALLOCATE (entry);
    return (next);
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../generated")
 * end:
**/
