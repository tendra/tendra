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


/**** arg-data.h --- Command line argument data ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * See the file "arg-data.c" for more information.
 *
 **** Change Log:
 * $Log: arg-data.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:16  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/07/07  15:31:55  smf
 * Updated to support TDF specification 4.0.
 *
 * Revision 1.2  1994/12/12  11:43:54  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:22  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_ARG_DATA
#define H_ARG_DATA

#include "os-interface.h"
#include "cstring.h"
#include "cstring-list.h"
#include "dalloc.h"
#include "dstring.h"
#include "name-key.h"
#include "ostream.h"

/*--------------------------------------------------------------------------*/

typedef struct ShapeControlEntryT {
    struct ShapeControlEntryT  *next;
    NStringT			shape;
    BoolT			all;
    NameKeyListT		names;
} ShapeControlEntryT, *ShapeControlEntryP;

typedef struct ShapeControlT {
    ShapeControlEntryP		head;
} ShapeControlT, *ShapeControlP;

typedef struct RenameControlEntryT {
    struct RenameControlEntryT *next;
    NStringT			shape;
    NameKeyPairListT		names;
} RenameControlEntryT, *RenameControlEntryP;

typedef struct RenameControlT {
    RenameControlEntryP		head;
} RenameControlT, *RenameControlP;

typedef struct ArgDataT {
    BoolT			all_hide_defined;
    BoolT			suppress_mult;
    ShapeControlT		hides;
    ShapeControlT		keeps;
    ShapeControlT		suppresses;
    RenameControlT		renames;
    BoolT			extract_all;
    BoolT			extract_basename;
    BoolT			extract_match_base;
    BoolT			content_index;
    BoolT			content_size;
    BoolT			content_version;
    OStreamT			debug_file;
    CStringP			default_output_file;
    CStringP			output_file;
    unsigned			num_library_files;
    unsigned			num_library_paths;
    union {
	struct {
	    CStringListT	file;
	    CStringListT	path;
	} list;
	struct {
	    CStringP	       *file;
	    CStringP	       *path;
	} vector;
    } library;
    CStringP			unit_file;
    unsigned			num_files;
    CStringP		       *files;
} ArgDataT, *ArgDataP;

/*--------------------------------------------------------------------------*/

extern void			shape_control_iter
	PROTO_S ((ShapeControlP, void (*) (NStringP, BoolT, NameKeyListP,
					   GenericP), GenericP));
extern void			rename_control_iter
	PROTO_S ((RenameControlP, void (*) (NStringP, NameKeyPairListP,
					    GenericP), GenericP));

extern void			arg_data_init
	PROTO_S ((ArgDataP, CStringP));
extern void			arg_data_set_all_hide_defd
	PROTO_S ((ArgDataP, BoolT));
extern BoolT			arg_data_get_all_hide_defd
	PROTO_S ((ArgDataP));
extern void			arg_data_set_suppress_mult
	PROTO_S ((ArgDataP, BoolT));
extern BoolT			arg_data_get_suppress_mult
	PROTO_S ((ArgDataP));
extern void			arg_data_add_hide
	PROTO_S ((ArgDataP, CStringP, CStringP));
extern void			arg_data_add_hide_defined
	PROTO_S ((ArgDataP, CStringP));
extern ShapeControlP		arg_data_get_hides
	PROTO_S ((ArgDataP));
extern void			arg_data_add_keep
	PROTO_S ((ArgDataP, CStringP, CStringP));
extern void			arg_data_add_keep_all
	PROTO_S ((ArgDataP, CStringP));
extern ShapeControlP		arg_data_get_keeps
	PROTO_S ((ArgDataP));
extern void			arg_data_add_suppress
	PROTO_S ((ArgDataP, CStringP, CStringP));
extern void			arg_data_add_suppress_all
	PROTO_S ((ArgDataP, CStringP));
extern ShapeControlP		arg_data_get_suppresses
	PROTO_S ((ArgDataP));
extern void			arg_data_add_rename
	PROTO_S ((ArgDataP, NStringP, NameKeyP, NameKeyP));
extern void			arg_data_parse_rename
	PROTO_S ((ArgDataP, CStringP, CStringP, CStringP));
extern RenameControlP		arg_data_get_renames
	PROTO_S ((ArgDataP));
extern void			arg_data_set_extract_all
	PROTO_S ((ArgDataP, BoolT));
extern BoolT			arg_data_get_extract_all
	PROTO_S ((ArgDataP));
extern void			arg_data_set_extract_basename
	PROTO_S ((ArgDataP, BoolT));
extern BoolT			arg_data_get_extract_basename
	PROTO_S ((ArgDataP));
extern void			arg_data_set_extract_match_base
	PROTO_S ((ArgDataP, BoolT));
extern BoolT			arg_data_get_extract_match_base
	PROTO_S ((ArgDataP));
extern void			arg_data_set_content_index
	PROTO_S ((ArgDataP, BoolT));
extern BoolT			arg_data_get_content_index
	PROTO_S ((ArgDataP));
extern void			arg_data_set_content_size
	PROTO_S ((ArgDataP, BoolT));
extern BoolT			arg_data_get_content_size
	PROTO_S ((ArgDataP));
extern void			arg_data_set_content_version
	PROTO_S ((ArgDataP, BoolT));
extern BoolT			arg_data_get_content_version
	PROTO_S ((ArgDataP));
extern void			arg_data_set_debug_file
	PROTO_S ((ArgDataP, CStringP));
extern OStreamP			arg_data_get_debug_file
	PROTO_S ((ArgDataP));
extern void			arg_data_set_output_file
	PROTO_S ((ArgDataP, CStringP));
extern CStringP			arg_data_get_output_file
	PROTO_S ((ArgDataP));
extern void			arg_data_add_library_file
	PROTO_S ((ArgDataP, CStringP));
extern void			arg_data_add_library_path
	PROTO_S ((ArgDataP, CStringP));
extern void			arg_data_vector_libraries
	PROTO_S ((ArgDataP));
extern unsigned			arg_data_num_library_files
	PROTO_S ((ArgDataP));
extern unsigned			arg_data_num_library_paths
	PROTO_S ((ArgDataP));
extern CStringP		       *arg_data_library_files
	PROTO_S ((ArgDataP));
extern CStringP		       *arg_data_library_paths
	PROTO_S ((ArgDataP));
extern void			arg_data_set_unit_file
	PROTO_S ((ArgDataP, CStringP));
extern void			arg_data_set_files
	PROTO_S ((ArgDataP, int, CStringP *));
extern unsigned			arg_data_get_num_files
	PROTO_S ((ArgDataP));
extern CStringP		       *arg_data_get_files
	PROTO_S ((ArgDataP));

#endif /* !defined (H_ARG_DATA) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library" "../tdf")
 * eval: (include::add-path-entry "../generated")
 * End:
**/
