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


/*** entry-list.h --- Identifier table entry list ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "entry-list.h" for more information.
 *
 *** Change Log:
 * $Log: entry-list.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:58:06  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:33  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_ENTRY_LIST
#define H_ENTRY_LIST

#include "os-interface.h"
#include "dalloc.h"
#include "entry.h"
#include "ostream.h"

/*--------------------------------------------------------------------------*/

typedef struct EntryListEntryT {
    struct EntryListEntryT     *next;
    EntryP			entry;
} EntryListEntryT, *EntryListEntryP;

typedef struct EntryListT {
    EntryListEntryP		head;
    EntryListEntryP	       *tail;
} EntryListT, *EntryListP;

typedef struct SaveListT {
    struct EntryListEntryT    **last_ref;
} SaveListT, *SaveListP;

/*--------------------------------------------------------------------------*/

extern void			entry_list_init
	PROTO_S ((EntryListP));
extern void			entry_list_copy
	PROTO_S ((EntryListP, EntryListP));
extern void			entry_list_add
	PROTO_S ((EntryListP, EntryP));
extern void			entry_list_add_if_missing
	PROTO_S ((EntryListP, EntryP));
extern BoolT			entry_list_contains
	PROTO_S ((EntryListP, EntryP));
extern BoolT			entry_list_includes
	PROTO_S ((EntryListP, EntryListP));
extern void			entry_list_intersection
	PROTO_S ((EntryListP, EntryListP, EntryListP));
extern void			entry_list_unlink_used
	PROTO_S ((EntryListP, EntryListP));
extern void			entry_list_append
	PROTO_S ((EntryListP, EntryListP));
extern BoolT			entry_list_is_empty
	PROTO_S ((EntryListP));
extern void			entry_list_save_state
	PROTO_S ((EntryListP, SaveListP));
extern void			entry_list_restore_state
	PROTO_S ((EntryListP, SaveListP));
extern void			entry_list_iter
	PROTO_S ((EntryListP, void (*) (EntryP, GenericP), GenericP));
extern void			entry_list_iter_table
	PROTO_S ((EntryListP, BoolT, void (*) (EntryP, GenericP), GenericP));
extern void			entry_list_destroy
	PROTO_S ((EntryListP));

extern void			write_entry_list
	PROTO_S ((OStreamP, EntryListP));

/*--------------------------------------------------------------------------*/

#ifdef FS_FAST
#define entry_list_is_empty(e) ((e)->head == NIL (EntryListEntryP))
#endif /* defined (FS_FAST) */

#endif /* !defined (H_ENTRY_LIST) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
