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


/*** c-out-types.h --- Output type objects.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "c-out-types.c" for more information.
 *
 *** Change Log:
 * $Log: c-out-types.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:43  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:56:42  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:20  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_C_OUT_TYPES
#define H_C_OUT_TYPES

#include "os-interface.h"
#include "c-output.h"
#include "rstack.h"
#include "rule.h"
#include "table.h"
#include "types.h"

/*--------------------------------------------------------------------------*/

extern void			c_output_assign
	PROTO_S ((COutputInfoP, EntryP, EntryP, SaveRStackP, SaveRStackP,
		  unsigned));
extern void			c_output_type_decl
	PROTO_S ((COutputInfoP, TypeTupleP, TypeTupleP));
extern void			c_output_type_defn
	PROTO_S ((COutputInfoP, TypeTupleP, TypeTupleP));
extern void			c_output_result_assign
	PROTO_S ((COutputInfoP, TypeTupleP, unsigned));
extern void			c_output_alt_names
	PROTO_S ((COutputInfoP, TypeTupleP, TypeTupleP, SaveRStackP,
		  unsigned));
extern void			c_output_rule_params
	PROTO_S ((COutputInfoP, TypeTupleP, TypeTupleP, SaveRStackP));
extern void			c_output_rename
	PROTO_S ((COutputInfoP, TypeTupleP, TypeTupleP, SaveRStackP,
		  unsigned));
extern void			c_output_tail_decls
	PROTO_S ((COutputInfoP, TypeTupleP, SaveRStackP, TypeTupleP,
		  SaveRStackP, unsigned));
extern BoolT			c_output_required_copies
	PROTO_S ((COutputInfoP, TypeTupleP, TypeTupleP, RStackP, SaveRStackP,
		  unsigned, TableP));
	      
#endif /* !defined (H_C_OUT_TYPES) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../transforms" "../output" "../generated")
 * end:
**/
