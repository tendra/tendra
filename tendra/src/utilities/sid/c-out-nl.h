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


/*** c-out-nl.h --- Output non local name list ADT objects.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "c-out-nl.c" for more information.
 *
 *** Change Log:
 * $Log: c-out-nl.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:43  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:56:36  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:20  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_C_OUT_NL
#define H_C_OUT_NL

#include "os-interface.h"
#include "c-output.h"
#include "non-local.h"
#include "rule.h"

/*--------------------------------------------------------------------------*/

extern void			c_output_non_locals
	PROTO_S ((COutputInfoP, NonLocalListP));
extern void			c_output_declare_non_locals
	PROTO_S ((COutputInfoP, NonLocalListP));
extern void			c_output_save_non_locals
	PROTO_S ((COutputInfoP, RuleP, unsigned, RStackP, RStackP, RuleP,
		  TableP));
extern void			c_output_restore_non_locals
	PROTO_S ((COutputInfoP, RuleP, unsigned, RStackP, RStackP));

#endif /* !defined (H_C_OUT_NL) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../transforms" "../output" "../generated")
 * end:
**/
