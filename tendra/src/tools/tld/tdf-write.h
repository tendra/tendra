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


/*** tdf-write.h --- TDF writer ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "tdf-write.c" for more information.
 *
 *** Change Log:
 * $Log: tdf-write.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:20  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:47:00  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:39  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_TDF_WRITE
#define H_TDF_WRITE

#include "os-interface.h"
#include "bostream.h"
#include "dstring.h"
#include "name-key.h"

/*--------------------------------------------------------------------------*/

typedef struct TDFWriterT {
    BOStreamT			bostream;
    ByteT			byte;
    BoolT			new_byte;
} TDFWriterT, *TDFWriterP;

/*--------------------------------------------------------------------------*/

extern BoolT			tdf_writer_open
	PROTO_S ((TDFWriterP, CStringP));
extern CStringP			tdf_writer_name
	PROTO_S ((TDFWriterP));
extern void			tdf_write_int
	PROTO_S ((TDFWriterP, unsigned));
extern void			tdf_write_align
	PROTO_S ((TDFWriterP));
extern void			tdf_write_bytes
	PROTO_S ((TDFWriterP, NStringP));
extern void			tdf_write_string
	PROTO_S ((TDFWriterP, NStringP));
extern void			tdf_write_name
	PROTO_S ((TDFWriterP, NameKeyP));
extern void			tdf_writer_close
	PROTO_S ((TDFWriterP));

#endif /* !defined (H_TDF_WRITE) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
