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


/*** name-table.h --- Name table ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "name-table.c" for more information.
 *
 *** Change Log:
 * $Log: name-table.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:19  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:46:44  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:36  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_NAME_TABLE
#define H_NAME_TABLE

#include "os-interface.h"
#include "dalloc.h"
#include "dstring.h"
#include "name-entry.h"
#include "name-key.h"

struct ShapeEntryT;

/*--------------------------------------------------------------------------*/

#define NAME_TABLE_SIZE (31)

/*--------------------------------------------------------------------------*/

typedef struct NameTableT {
    NameEntryP			contents [NAME_TABLE_SIZE];
} NameTableT, *NameTableP;

/*--------------------------------------------------------------------------*/

extern NameTableP		name_table_create
	PROTO_S ((void));
extern void			name_table_add_rename
	PROTO_S ((NameTableP, NameKeyP, NameKeyP));
extern void			name_table_resolve_renames
	PROTO_S ((NameTableP, NStringP, BoolT));
extern NameEntryP		name_table_add
	PROTO_S ((NameTableP, NameKeyP, struct ShapeEntryT *));
extern NameEntryP		name_table_get
	PROTO_S ((NameTableP, NameKeyP));
extern void			name_table_iter
	PROTO_S ((NameTableP, void (*) (NameEntryP, GenericP), GenericP));
extern void			name_table_deallocate
	PROTO_S ((NameTableP));

#endif /* !defined (H_NAME_TABLE) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
