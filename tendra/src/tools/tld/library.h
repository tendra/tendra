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


/*** library.h --- TDF library ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "library.c" for more information.
 *
 *** Change Log:
 * $Log: library.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:18  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1995/09/22  08:39:20  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 * Fixed some problems in "name-key.c" (no real problems, but rewritten to
 * reduce the warnings that were output by "tcc" and "gcc").
 * Fixed bug CR95_354.tld-common-id-problem (library capsules could be loaded
 * more than once).
 *
 * Revision 1.3  1995/07/07  15:32:28  smf
 * Updated to support TDF specification 4.0.
 *
 * Revision 1.2  1994/12/12  11:46:25  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:32  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_LIBRARY
#define H_LIBRARY

#include "os-interface.h"
#include "capsule.h"
#include "dalloc.h"
#include "shape-table.h"
#include "tdf-read.h"
#include "tdf-write.h"

/*--------------------------------------------------------------------------*/

#ifdef FS_NO_ENUM
typedef int LibraryTypeT, *LibraryTypeP;
#define LT_INPUT		(0)
#define LT_OUTPUT		(1)
#else
typedef enum {
    LT_INPUT,
    LT_OUTPUT
} LibraryTypeT, *LibraryTypeP;
#endif /* defined (FS_NO_ENUM) */

struct LibraryT;

typedef struct LibCapsuleT {
    struct LibraryT	       *library;
    CStringP			name;
    NStringT			contents;
    BoolT			loaded;
} LibCapsuleT, *LibCapsuleP;

typedef struct LibraryT {
    LibraryTypeT		type;
    union {
	TDFReaderT		reader;
	TDFWriterT		writer;
    } u;
    CStringP			name;
    unsigned			num_capsules;
    LibCapsuleP			capsules;
    unsigned			major;
    unsigned			minor;
    BoolT			complete;
} LibraryT, *LibraryP;

/*--------------------------------------------------------------------------*/

extern CStringP			lib_capsule_name
	PROTO_S ((LibCapsuleP));
extern CStringP			lib_capsule_full_name
	PROTO_S ((LibCapsuleP));
extern NStringP			lib_capsule_contents
	PROTO_S ((LibCapsuleP));
extern BoolT			lib_capsule_is_loaded
	PROTO_S ((LibCapsuleP));
extern void			lib_capsule_loaded
	PROTO_S ((LibCapsuleP));

extern void			write_lib_capsule_full_name
	PROTO_S ((OStreamP, LibCapsuleP));

extern LibraryP			library_create_stream_input
	PROTO_S ((CStringP));
extern LibraryP			library_create_stream_output
	PROTO_S ((CStringP));
extern CStringP			library_name
	PROTO_S ((LibraryP));
extern unsigned			library_num_capsules
	PROTO_S ((LibraryP));
extern LibCapsuleP		library_get_capsule
	PROTO_S ((LibraryP, unsigned));
extern unsigned			library_byte
	PROTO_S ((LibraryP));
extern void			library_content
	PROTO_S ((LibraryP, BoolT, BoolT, BoolT));
extern void			library_extract_all
	PROTO_S ((LibraryP, BoolT));
extern void			library_extract
	PROTO_S ((LibraryP, BoolT, BoolT, unsigned, CStringP *));
extern void			library_read
	PROTO_S ((LibraryP, ShapeTableP));
extern void			library_write
	PROTO_S ((LibraryP, ShapeTableP, unsigned, CapsuleP *));
extern void			library_close
	PROTO_S ((LibraryP));

#endif /* !defined (H_LIBRARY) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
