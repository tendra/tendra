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


/*** rstack.h --- Renaming stack ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "rstack.c" for more information.
 *
 *** Change Log:
 * $Log: rstack.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:58:33  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:37  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_RSTACK
#define H_RSTACK

#include "os-interface.h"
#include "table.h"
#include "types.h"

/*--------------------------------------------------------------------------*/

typedef struct TransStackEntryT {
    struct TransStackEntryT    *next;
    TypeRTransT			translator;
} TransStackEntryT, *TransStackEntryP;

typedef struct RStackT {
    TransStackEntryP		head;
} RStackT, *RStackP;

typedef struct SaveRStackT {
    TransStackEntryP		head;
} SaveRStackT, *SaveRStackP;

/*--------------------------------------------------------------------------*/

extern void			rstack_init
	PROTO_S ((RStackP));
extern void			rstack_push_frame
	PROTO_S ((RStackP));
extern void			rstack_compute_formal_renaming
	PROTO_S ((RStackP, TypeTupleP));
extern void			rstack_compute_formal_inlining
	PROTO_S ((RStackP, TypeTupleP, TypeTupleP));
extern void			rstack_compute_local_renaming
	PROTO_S ((RStackP, TypeTupleP, TypeTupleP, TableP));
extern void			rstack_add_translation
	PROTO_S ((RStackP, struct EntryT *, struct EntryT *, struct EntryT *,
		  BoolT));
extern void			rstack_save_state
	PROTO_S ((RStackP, SaveRStackP));
extern struct EntryT	       *rstack_get_translation
	PROTO_S ((SaveRStackP, struct EntryT *, struct EntryT **, BoolT *));
extern void			rstack_apply_for_non_locals
	PROTO_S ((RStackP, SaveRStackP, void (*) (struct EntryT *,
						  struct EntryT *, GenericP),
		  GenericP));
extern void			rstack_pop_frame
	PROTO_S ((RStackP));
extern void			rstack_destroy
	PROTO_S ((RStackP));

#endif /* !defined (H_RSTACK) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
