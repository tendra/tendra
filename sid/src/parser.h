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


/*** parser.h --- SID parser.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file specifies the interface to the SID file parser that is produced
 * from the file "parser.sid".
 *
 *** Change Log:
 * $Log: parser.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:42  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:57:33  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:25  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_PARSER
#define H_PARSER

#include "os-interface.h"
#include "entry-list.h"
#include "grammar.h"
#include "lexer.h"
#include "table.h"

/*--------------------------------------------------------------------------*/

extern LexerStreamP		sid_current_stream;
extern GrammarP			sid_current_grammar;
extern void			sid_parse_grammar
	PROTO_S ((void));

#endif /* !defined (H_PARSER) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../transforms" "../generated")
 * end:
**/
