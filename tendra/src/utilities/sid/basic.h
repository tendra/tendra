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


/*** basic.h --- Basic ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "basic.c" for more information.
 *
 *** Change Log:
 * $Log: basic.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:45  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:58:02  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:32  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_BASIC
#define H_BASIC

#include "os-interface.h"
#include "bitvec.h"
#include "dalloc.h"
#include "dstring.h"
#include "entry.h"
#include "grammar.h"
#include "ostream.h"
#include "types.h"

/*--------------------------------------------------------------------------*/

typedef struct BasicT {
    unsigned			terminal;
    TypeTupleT			result;
    GenericP			result_code;
    BoolT			ignored;
} BasicT, *BasicP;

typedef struct BasicClosureT {
    BitVecP			bitvec;
    GrammarP			grammar;
} BasicClosureT, *BasicClosureP;

/*--------------------------------------------------------------------------*/

extern BasicP			basic_create
	PROTO_S ((GrammarP, BoolT));
extern unsigned			basic_terminal
	PROTO_S ((BasicP));
extern TypeTupleP		basic_result
	PROTO_S ((BasicP));
extern GenericP			basic_get_result_code
	PROTO_S ((BasicP));
extern void			basic_set_result_code
	PROTO_S ((BasicP, GenericP));
extern BoolT			basic_get_ignored
	PROTO_S ((BasicP));
extern void			basic_iter_for_table
	PROTO_S ((BasicP, BoolT, void (*) (EntryP, GenericP), GenericP));

extern void			write_basics
	PROTO_S ((OStreamP, BasicClosureP));

/*--------------------------------------------------------------------------*/

#ifdef FS_FAST
#define basic_terminal(b) ((b)->terminal)
#define basic_result(b) (&((b)->result))
#define basic_get_result_code(b) ((b)->result_code)
#define basic_set_result_code(b, c) ((b)->result_code = (c))
#define basic_get_ignored(b) ((b)->ignored)
#endif /* defined (FS_FAST) */

#endif /* !defined (H_BASIC) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
