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


/**** cstring-list.h --- String list ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 ***=== INTRODUCTION =========================================================
 *
 * This file specifies the interface to a string list facility.  This
 * particular facility allows lists of cstrings (defined in the files
 * "cstring.[ch]") to be created.
 *
 ***=== TYPES ================================================================
 *
 ** Type:	CStringListEntryT
 ** Type:	CStringListEntryP
 ** Repr:	<private>
 *
 * This is the cstring list entry type.
 *
 ** Type:	CStringListT
 ** Type:	CStringListP
 ** Repr:	<private>
 *
 * This is the cstring list type.
 *
 ***=== FUNCTIONS ============================================================
 *
 ** Function:	void			cstring_list_init
 *			PROTO_S ((CStringListP list))
 ** Exceptions:
 *
 * This function initialises the specified cstring list to be an empty list.
 *
 ** Function:	void			cstring_list_append
 *			PROTO_S ((CStringListP list, CStringP cstring))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function appends the specified cstring onto the specified list.
 *
 ** Function:	CStringListEntryP	cstring_list_head
 *			PROTO_S ((CStringListP list))
 ** Exceptions:
 *
 * This function returns a pointer to the first entry in the specified list.
 *
 ** Function:	CStringP		cstring_list_entry_string
 *			PROTO_S ((CStringListEntryP entry))
 ** Exceptions:
 *
 * This function returns a pointer to the cstring stored in the specified
 * list entry.
 *
 ** Function:	CStringListEntryP	cstring_list_entry_deallocate
 *			PROTO_S ((CStringListEntryP entry))
 ** Exceptions:
 *
 * This function deallocates the specified list entry (without deallocating
 * the string - this must be done by the calling function) and returns a
 * pointer to the next entry in the list.  Once this function has been called,
 * the state of the list that the entry is a member of is undefined.  It is
 * only useful for deallocating the entire list in a loop.
 *
 **** Change log:
 * $Log: cstring-list.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:45  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:44:32  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:05:48  smf
 * Initial import of library shared files.
 *
**/

/****************************************************************************/

#ifndef H_CSTRING_LIST
#define H_CSTRING_LIST

#include "os-interface.h"
#include "cstring.h"
#include "dalloc.h"

/*--------------------------------------------------------------------------*/

typedef struct CStringListEntryT {
    struct CStringListEntryT   *next;
    CStringP			string;
} CStringListEntryT, *CStringListEntryP;

typedef struct CStringListT {
    CStringListEntryP		head;
    CStringListEntryP	       *tail;
} CStringListT, *CStringListP;

/*--------------------------------------------------------------------------*/

extern void			cstring_list_init
	PROTO_S ((CStringListP));
extern void			cstring_list_append
	PROTO_S ((CStringListP, CStringP));
extern CStringListEntryP	cstring_list_head
	PROTO_S ((CStringListP));
extern CStringP			cstring_list_entry_string
	PROTO_S ((CStringListEntryP));
extern CStringListEntryP	cstring_list_entry_deallocate
	PROTO_S ((CStringListEntryP));

#endif /* !defined (H_CSTRING_LIST) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../generated")
 * end:
**/
