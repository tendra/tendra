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


/*** c-output.h --- Output routines.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "c-output.c" for more information.
 *
 *** Change Log:
 * $Log: c-output.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:43  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:56:46  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:21  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_C_OUTPUT
#define H_C_OUTPUT

#include "os-interface.h"
#include "cstring.h"
#include "entry-list.h"
#include "grammar.h"
#include "key.h"
#include "ostream.h"
#include "c-out-info.h"

/*--------------------------------------------------------------------------*/

#define C_INDENT_STEP ((unsigned) 4)
#define C_INDENT_FOR_ERROR C_INDENT_STEP
#define C_INDENT_FOR_PARAM ((unsigned) 2)
#define C_INDENT_FOR_CASE ((unsigned) 2)
#define C_INDENT_FOR_LABEL ((unsigned) 2)

/*--------------------------------------------------------------------------*/

extern void			c_output_parser
	PROTO_S ((COutputInfoP, GrammarP));
extern void			c_output_header
	PROTO_S ((COutputInfoP, GrammarP));
extern void			c_output_location
	PROTO_S ((COutputInfoP, CStringP, unsigned));
extern void			c_output_key_message
	PROTO_S ((COutputInfoP, CStringP, KeyP, CStringP, unsigned));
extern unsigned			c_out_next_label
	PROTO_S ((void));
extern void			c_output_open
	PROTO_S ((COutputInfoP, unsigned));
extern void			c_output_close
	PROTO_S ((COutputInfoP, unsigned));

#endif /* !defined (H_C_OUTPUT) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../transforms" "../output" "../generated")
 * end:
**/
