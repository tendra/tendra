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


/*** table.h --- Identifier table ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "table.c" for more information.
 *
 *** Change Log:
 * $Log: table.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:59:07  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:43  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_TABLE
#define H_TABLE

#include "os-interface.h"
#include "dstring.h"
#include "entry.h"
#include "ostream.h"
#include "key.h"

/* To avoid cicularity: */
struct GrammarT;

/*--------------------------------------------------------------------------*/

#define TABLE_SIZE (127)

/*--------------------------------------------------------------------------*/

typedef struct TableT {
    EntryP			contents [TABLE_SIZE];
} TableT, *TableP;

/*--------------------------------------------------------------------------*/

extern void			table_init
	PROTO_S ((TableP));
extern EntryP			table_add_type
	PROTO_S ((TableP, NStringP));
extern EntryP			table_add_basic
	PROTO_S ((TableP, NStringP, struct GrammarT *, BoolT));
extern EntryP			table_add_action
	PROTO_S ((TableP, NStringP));
extern EntryP			table_add_rule
	PROTO_S ((TableP, NStringP));
extern EntryP			table_add_generated_rule
	PROTO_S ((TableP, BoolT));
extern EntryP			table_add_name
	PROTO_S ((TableP, NStringP));
extern EntryP			table_add_generated_name
	PROTO_S ((TableP));
extern EntryP			table_add_rename
	PROTO_S ((TableP));
extern EntryP			table_add_non_local
	PROTO_S ((TableP, NStringP, EntryP));
extern EntryP			table_get_entry
	PROTO_S ((TableP, NStringP));
extern EntryP			table_get_type
	PROTO_S ((TableP, NStringP));
extern EntryP			table_get_basic
	PROTO_S ((TableP, NStringP));
extern EntryP			table_get_basic_by_number
	PROTO_S ((TableP, unsigned));
extern EntryP			table_get_action
	PROTO_S ((TableP, NStringP));
extern EntryP			table_get_rule
	PROTO_S ((TableP, NStringP));
extern void			table_iter
	PROTO_S ((TableP, void (*) (EntryP, GenericP), GenericP));
extern void			table_untrace
	PROTO_S ((TableP));
extern void			table_unlink_untraced_rules
	PROTO_S ((TableP));

#endif /* !defined (H_TABLE) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
