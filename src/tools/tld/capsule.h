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


/*** capsule.h --- TDF capsule ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "capsule.c" for more information.
 *
 *** Change Log:
 * $Log: capsule.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:18  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/07/07  15:32:20  smf
 * Updated to support TDF specification 4.0.
 *
 * Revision 1.2  1994/12/12  11:46:15  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:30  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_CAPSULE
#define H_CAPSULE

#include "os-interface.h"
#include "dalloc.h"
#include "dstring.h"
#include "shape-table.h"
#include "tdf-read.h"
#include "tdf-write.h"
#include "unit-table.h"

struct LibCapsuleT;

/*--------------------------------------------------------------------------*/

#ifdef FS_NO_ENUM
typedef int CapsuleTypeT, *CapsuleTypeP;
#define CT_INPUT		(0)
#define CT_OUTPUT		(1)
#else
typedef enum {
    CT_INPUT,
    CT_OUTPUT
} CapsuleTypeT, *CapsuleTypeP;
#endif /* defined (FS_NO_ENUM) */

typedef struct CapsuleT {
    CapsuleTypeT		type;
    union {
	TDFReaderT		reader;
	TDFWriterT		writer;
    } u;
    NStringT			contents;
    unsigned			capsule_index;
    CStringP			name;
    BoolT			complete;
} CapsuleT, *CapsuleP;

/*--------------------------------------------------------------------------*/

extern void			capsule_read_unit_set_file
	PROTO_S ((CStringP));
extern CapsuleP			capsule_create_stream_input
	PROTO_S ((CStringP));
extern CapsuleP			capsule_create_string_input
	PROTO_S ((CStringP, NStringP));
extern CapsuleP			capsule_create_stream_output
	PROTO_S ((CStringP));
extern CStringP			capsule_name
	PROTO_S ((CapsuleP));
extern unsigned			capsule_byte
	PROTO_S ((CapsuleP));
extern void			capsule_read
	PROTO_S ((CapsuleP, UnitTableP, ShapeTableP));
extern void			capsule_store_contents
	PROTO_S ((CapsuleP));
extern NStringP			capsule_contents
	PROTO_S ((CapsuleP));
extern void			capsule_set_index
	PROTO_S ((CapsuleP, unsigned));
extern unsigned			capsule_get_index
	PROTO_S ((CapsuleP));
extern void			capsule_write
	PROTO_S ((CapsuleP, UnitTableP, ShapeTableP));
extern void			capsule_close
	PROTO_S ((CapsuleP));
extern unsigned			capsule_get_major_version
	PROTO_S ((void));
extern void			capsule_set_major_version
	PROTO_S ((unsigned));
extern unsigned			capsule_get_minor_version
	PROTO_S ((void));

#endif /* !defined (H_CAPSULE) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
