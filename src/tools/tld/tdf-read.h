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


/*** tdf-read.h --- TDF reader ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "tdf-read.c" for more information.
 *
 *** Change Log:
 * $Log: tdf-read.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:20  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:46:57  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:39  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_TDF_READ
#define H_TDF_READ

#include "os-interface.h"
#include "bistream.h"
#include "dstring.h"
#include "exception.h"
#include "name-key.h"

/*--------------------------------------------------------------------------*/

#ifdef FS_NO_ENUM
typedef int ReaderTypeT, *ReaderTypeP;
#define RT_STREAM	(0)
#define RT_STRING	(1)
#else
typedef enum {
    RT_STREAM,
    RT_STRING
} ReaderTypeT, *ReaderTypeP;
#endif /* defined (FS_NO_ENUM) */

typedef struct TDFReaderT {
    ReaderTypeT			type;
    union {
	BIStreamT		bistream;
	struct {
	    CStringP		contents;
	    CStringP		current;
	    CStringP		limit;
	    CStringP            name;
	    unsigned		byte;
	} string;
    } u;
    ByteT			byte;
    BoolT			new_byte;
} TDFReaderT, *TDFReaderP;

/*--------------------------------------------------------------------------*/

extern ExceptionP		XX_tdf_read_error;

/*--------------------------------------------------------------------------*/

extern BoolT			tdf_reader_open
	PROTO_S ((TDFReaderP, CStringP));
extern void			tdf_reader_open_string
	PROTO_S ((TDFReaderP, CStringP, NStringP));
extern CStringP			tdf_reader_name
	PROTO_S ((TDFReaderP));
extern unsigned			tdf_reader_byte
	PROTO_S ((TDFReaderP));
extern unsigned			tdf_read_int
	PROTO_S ((TDFReaderP));
extern void			tdf_read_align
	PROTO_S ((TDFReaderP));
extern void			tdf_read_bytes
	PROTO_S ((TDFReaderP, NStringP));
extern void			tdf_read_string
	PROTO_S ((TDFReaderP, NStringP));
extern void			tdf_read_name
	PROTO_S ((TDFReaderP, NameKeyP));
extern void			tdf_read_eof
	PROTO_S ((TDFReaderP));
extern void			tdf_reader_rewind
	PROTO_S ((TDFReaderP));
extern void			tdf_reader_close
	PROTO_S ((TDFReaderP));

#endif /* !defined (H_TDF_READ) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
