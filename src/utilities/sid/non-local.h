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


/**** non-local.h --- Non local name ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * See the file "non-local.c" for more information.
 *
 **** Change Log:
 * $Log: non-local.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:58:28  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:36  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_NON_LOCAL
#define H_NON_LOCAL

#include "os-interface.h"
#include "dalloc.h"
#include "entry.h"
#include "ostream.h"

/*--------------------------------------------------------------------------*/

typedef struct NonLocalEntryT {
    struct NonLocalEntryT      *next;
    EntryP			name;
    EntryP			type;
    EntryP			initialiser;
} NonLocalEntryT, *NonLocalEntryP;

typedef struct NonLocalListT {
    NonLocalEntryP		head;
    NonLocalEntryP	       *tail;
} NonLocalListT, *NonLocalListP;

/*--------------------------------------------------------------------------*/

extern void			non_local_list_init
	PROTO_S ((NonLocalListP));
extern NonLocalEntryP		non_local_list_add
	PROTO_S ((NonLocalListP, EntryP, EntryP));
extern BoolT			non_local_list_is_empty
	PROTO_S ((NonLocalListP));
extern void			non_local_list_iter_for_table
	PROTO_S ((NonLocalListP, void (*) (EntryP, GenericP), GenericP));
extern void			non_local_list_destroy
	PROTO_S ((NonLocalListP));

extern void			write_non_locals
	PROTO_S ((OStreamP, NonLocalListP));

extern void			non_local_entry_set_initialiser
	PROTO_S ((NonLocalEntryP, EntryP));
extern EntryP			non_local_entry_get_initialiser
	PROTO_S ((NonLocalEntryP));
extern EntryP			non_local_entry_get_type
	PROTO_S ((NonLocalEntryP));
extern EntryP			non_local_entry_get_name
	PROTO_S ((NonLocalEntryP));

#endif /* !defined (H_NON_LOCAL) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
