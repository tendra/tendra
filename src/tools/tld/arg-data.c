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


/**** arg-data.c --- Command line argument data ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the ADT that stores the information on the various
 * command line options that were given to the TDF linker.
 *
 **** Change Log:
 * $Log: arg-data.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:16  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1995/09/22  08:36:58  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 *
 * Revision 1.3  1995/07/07  15:31:54  smf
 * Updated to support TDF specification 4.0.
 *
 * Revision 1.2  1994/12/12  11:43:52  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:22  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#include "arg-data.h"
#include "capsule.h"
#include "gen-errors.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

static void
shape_control_init PROTO_N ((control))
		   PROTO_T (ShapeControlP control)
{
    control->head = NIL (ShapeControlEntryP);
}

static ShapeControlEntryP
shape_control_find PROTO_N ((control, shape))
		   PROTO_T (ShapeControlP control X
			    CStringP      shape)
{
    NStringT           nstring;
    ShapeControlEntryP entry;

    nstring_copy_cstring (&nstring, shape);
    for (entry = control->head; entry; entry = entry->next) {
	if (nstring_equal (&nstring, &(entry->shape))) {
	    nstring_destroy (&nstring);
	    return (entry);
	}
    }
    entry             = ALLOCATE (ShapeControlEntryT);
    entry->next       = control->head;
    nstring_assign (&(entry->shape), &nstring);
    entry->all        = FALSE;
    name_key_list_init (&(entry->names));
    control->head     = entry;
    return (entry);
}

static void
shape_control_entry_add_name PROTO_N ((entry, name))
			     PROTO_T (ShapeControlEntryP entry X
				      CStringP           name)
{
    NameKeyT key;

    if (name_key_parse_cstring (&key, name)) {
	name_key_list_add (&(entry->names), &key);
    } else {
	E_illegal_external_name (name);
    }
}

static void
shape_control_entry_set PROTO_N ((entry))
			PROTO_T (ShapeControlEntryP entry)
{
    entry->all = TRUE;
}

/*--------------------------------------------------------------------------*/

static void
rename_control_init PROTO_N ((control))
		    PROTO_T (RenameControlP control)
{
    control->head = NIL (RenameControlEntryP);
}

static RenameControlEntryP
rename_control_find PROTO_N ((control, shape))
		    PROTO_T (RenameControlP control X
			     NStringP       shape)
{
    RenameControlEntryP entry;

    for (entry = control->head; entry; entry = entry->next) {
	if (nstring_equal (shape, &(entry->shape))) {
	    return (entry);
	}
    }
    entry             = ALLOCATE (RenameControlEntryT);
    entry->next       = control->head;
    nstring_copy (&(entry->shape), shape);
    name_key_pair_list_init (&(entry->names));
    control->head     = entry;
    return (entry);
}

static NameKeyPairListP
rename_control_entry_names PROTO_N ((entry))
			   PROTO_T (RenameControlEntryP entry)
{
    return (&(entry->names));
}

static void
rename_control_entry_parse_pair PROTO_N ((entry, from, to))
				PROTO_T (RenameControlEntryP entry X
					 CStringP            from X
					 CStringP            to)
{
    NStringP shape = &(entry->shape);
    NameKeyT from_key;
    NameKeyT to_key;

    if (!name_key_parse_cstring (&from_key, from)) {
	E_illegal_external_name (from);
    } else if (!name_key_parse_cstring (&to_key, to)) {
	E_illegal_external_name (to);
    } else if (!name_key_pair_list_add (&(entry->names), &from_key, &to_key)) {
	E_multiply_renamed_name (shape, &from_key);
	name_key_destroy (&from_key);
	name_key_destroy (&to_key);
    }
}

/*--------------------------------------------------------------------------*/

void
shape_control_iter PROTO_N ((control, proc, closure))
		   PROTO_T (ShapeControlP control X
			    void        (*proc) PROTO_S ((NStringP, BoolT,
							  NameKeyListP,
							  GenericP)) X
			    GenericP      closure)
{
    ShapeControlEntryP entry;

    for (entry = control->head; entry; entry = entry->next) {
	(*proc) (&(entry->shape), entry->all, &(entry->names), closure);
    }
}

void
rename_control_iter PROTO_N ((control, proc, closure))
		    PROTO_T (RenameControlP control X
			     void         (*proc) PROTO_S ((NStringP,
							    NameKeyPairListP,
							    GenericP)) X
			     GenericP       closure)
{
    RenameControlEntryP entry;

    for (entry = control->head; entry; entry = entry->next) {
	(*proc) (&(entry->shape), &(entry->names), closure);
    }
}

/*--------------------------------------------------------------------------*/

void
arg_data_init PROTO_N ((arg_data, default_output_file))
	      PROTO_T (ArgDataP arg_data X
		       CStringP default_output_file)
{
    arg_data->all_hide_defined    = FALSE;
    arg_data->suppress_mult       = FALSE;
    shape_control_init (&(arg_data->hides));
    shape_control_init (&(arg_data->keeps));
    shape_control_init (&(arg_data->suppresses));
    rename_control_init (&(arg_data->renames));
    arg_data->extract_all         = FALSE;
    arg_data->extract_basename    = FALSE;
    arg_data->extract_match_base  = FALSE;
    arg_data->content_index       = FALSE;
    arg_data->content_size        = FALSE;
    arg_data->content_version     = FALSE;
    ostream_init (&(arg_data->debug_file));
    arg_data->default_output_file = default_output_file;
    arg_data->output_file         = NIL (CStringP);
    arg_data->num_library_files   = 0;
    arg_data->num_library_paths   = 0;
    cstring_list_init (&arg_data->library.list.file);
    cstring_list_init (&(arg_data->library.list.path));
    arg_data->unit_file           = NIL (CStringP);
    arg_data->num_files           = 0;
}

void
arg_data_set_all_hide_defd PROTO_N ((arg_data, enable))
			   PROTO_T (ArgDataP arg_data X
				    BoolT    enable)
{
    arg_data->all_hide_defined = enable;
}

BoolT
arg_data_get_all_hide_defd PROTO_N ((arg_data))
			   PROTO_T (ArgDataP arg_data)
{
    return (arg_data->all_hide_defined);
}

void
arg_data_set_suppress_mult PROTO_N ((arg_data, enable))
			   PROTO_T (ArgDataP arg_data X
				    BoolT    enable)
{
    arg_data->suppress_mult = enable;
}

BoolT
arg_data_get_suppress_mult PROTO_N ((arg_data))
			   PROTO_T (ArgDataP arg_data)
{
    return (arg_data->suppress_mult);
}

void
arg_data_add_hide PROTO_N ((arg_data, shape, name))
		  PROTO_T (ArgDataP arg_data X
			   CStringP shape X
			   CStringP name)
{
    ShapeControlEntryP entry = shape_control_find (&(arg_data->hides), shape);

    shape_control_entry_add_name (entry, name);
}

void
arg_data_add_hide_defined PROTO_N ((arg_data, shape))
			  PROTO_T (ArgDataP arg_data X
				   CStringP shape)
{
    ShapeControlEntryP entry = shape_control_find (&(arg_data->hides), shape);

    shape_control_entry_set (entry);
}

ShapeControlP
arg_data_get_hides PROTO_N ((arg_data))
		   PROTO_T (ArgDataP arg_data)
{
    return (&(arg_data->hides));
}

void
arg_data_add_keep PROTO_N ((arg_data, shape, name))
		  PROTO_T (ArgDataP arg_data X
			   CStringP shape X
			   CStringP name)
{
    ShapeControlEntryP entry = shape_control_find (&(arg_data->keeps), shape);

    shape_control_entry_add_name (entry, name);
}

void
arg_data_add_keep_all PROTO_N ((arg_data, shape))
		      PROTO_T (ArgDataP arg_data X
			       CStringP shape)
{
    ShapeControlEntryP entry = shape_control_find (&(arg_data->keeps), shape);

    shape_control_entry_set (entry);
}

ShapeControlP
arg_data_get_keeps PROTO_N ((arg_data))
		   PROTO_T (ArgDataP arg_data)
{
    return (&(arg_data->keeps));
}

void
arg_data_add_suppress PROTO_N ((arg_data, shape, name))
		      PROTO_T (ArgDataP arg_data X
			       CStringP shape X
			       CStringP name)
{
    ShapeControlEntryP entry = shape_control_find (&(arg_data->suppresses),
						   shape);

    shape_control_entry_add_name (entry, name);
}

void
arg_data_add_suppress_all PROTO_N ((arg_data, shape))
			  PROTO_T (ArgDataP arg_data X
				   CStringP shape)
{
    ShapeControlEntryP entry = shape_control_find (&(arg_data->suppresses),
						   shape);

    shape_control_entry_set (entry);
}

ShapeControlP
arg_data_get_suppresses PROTO_N ((arg_data))
			PROTO_T (ArgDataP arg_data)
{
    return (&(arg_data->suppresses));
}

void
arg_data_add_rename PROTO_N ((arg_data, shape, from, to))
		    PROTO_T (ArgDataP arg_data X
			     NStringP shape X
			     NameKeyP from X
			     NameKeyP to)
{
    RenameControlEntryP entry;
    NameKeyPairListP    names;

    entry = rename_control_find (&(arg_data->renames), shape);
    names = rename_control_entry_names (entry);
    if (!name_key_pair_list_add (names, from, to)) {
	E_multiply_renamed_name (shape, from);
	name_key_destroy (from);
	name_key_destroy (to);
    }
}

void
arg_data_parse_rename PROTO_N ((arg_data, shape, from, to))
		      PROTO_T (ArgDataP arg_data X
			       CStringP shape X
			       CStringP from X
			       CStringP to)
{
    NStringT            nstring;
    RenameControlEntryP entry;

    nstring_copy_cstring (&nstring, shape);
    entry = rename_control_find (&(arg_data->renames), &nstring);
    nstring_destroy (&nstring);
    rename_control_entry_parse_pair (entry, from, to);
}

RenameControlP
arg_data_get_renames PROTO_N ((arg_data))
		     PROTO_T (ArgDataP arg_data)
{
    return (&(arg_data->renames));
}

void
arg_data_set_extract_all PROTO_N ((arg_data, enable))
			 PROTO_T (ArgDataP arg_data X
				  BoolT    enable)
{
    arg_data->extract_all = enable;
}

BoolT
arg_data_get_extract_all PROTO_N ((arg_data))
			 PROTO_T (ArgDataP arg_data)
{
    return (arg_data->extract_all);
}

void
arg_data_set_extract_basename PROTO_N ((arg_data, enable))
			      PROTO_T (ArgDataP arg_data X
				       BoolT    enable)
{
    arg_data->extract_basename = enable;
}

BoolT
arg_data_get_extract_basename PROTO_N ((arg_data))
			      PROTO_T (ArgDataP arg_data)
{
    return (arg_data->extract_basename);
}

void
arg_data_set_extract_match_base PROTO_N ((arg_data, enable))
				PROTO_T (ArgDataP arg_data X
					 BoolT    enable)
{
    arg_data->extract_match_base = enable;
}

BoolT
arg_data_get_extract_match_base PROTO_N ((arg_data))
				PROTO_T (ArgDataP arg_data)
{
    return (arg_data->extract_match_base);
}

void
arg_data_set_content_index PROTO_N ((arg_data, enable))
			   PROTO_T (ArgDataP arg_data X
				    BoolT    enable)
{
    arg_data->content_index = enable;
}

BoolT
arg_data_get_content_index PROTO_N ((arg_data))
			   PROTO_T (ArgDataP arg_data)
{
    return (arg_data->content_index);
}

void
arg_data_set_content_size PROTO_N ((arg_data, enable))
			  PROTO_T (ArgDataP arg_data X
				   BoolT    enable)
{
    arg_data->content_size = enable;
}

BoolT
arg_data_get_content_size PROTO_N ((arg_data))
			  PROTO_T (ArgDataP arg_data)
{
    return (arg_data->content_size);
}

void
arg_data_set_content_version PROTO_N ((arg_data, enable))
    			     PROTO_T (ArgDataP arg_data X
				      BoolT    enable)
{
    arg_data->content_version = enable;
}

BoolT
arg_data_get_content_version PROTO_N ((arg_data))
    			     PROTO_T (ArgDataP arg_data)
{
    return (arg_data->content_version);
}

void
arg_data_set_debug_file PROTO_N ((arg_data, debug_file))
			PROTO_T (ArgDataP arg_data X
				 CStringP debug_file)
{
    if (ostream_is_open (&(arg_data->debug_file))) {
	E_tld_multiple_debug_files ();
	UNREACHED;
    }
    if (!ostream_open (&(arg_data->debug_file), debug_file)) {
	E_tld_cannot_open_debug_file (debug_file);
	UNREACHED;
    }
}

OStreamP
arg_data_get_debug_file PROTO_N ((arg_data))
			PROTO_T (ArgDataP arg_data)
{
    return (&(arg_data->debug_file));
}

void
arg_data_set_output_file PROTO_N ((arg_data, output_file))
			 PROTO_T (ArgDataP arg_data X
				  CStringP output_file)
{
    if (arg_data->output_file) {
	E_tld_multiple_output_files ();
	UNREACHED;
    }
    arg_data->output_file = output_file;
}

CStringP
arg_data_get_output_file PROTO_N ((arg_data))
			 PROTO_T (ArgDataP arg_data)
{
    if (arg_data->output_file) {
	return (arg_data->output_file);
    } else {
	return (arg_data->default_output_file);
    }
}

void
arg_data_add_library_file PROTO_N ((arg_data, library_file))
			  PROTO_T (ArgDataP arg_data X
				   CStringP library_file)
{
    CStringListP libraries = &(arg_data->library.list.file);
    if (!cstring_list_contains (libraries, library_file)) {
	arg_data->num_library_files ++;
	cstring_list_append (libraries, library_file);
    }
}

void
arg_data_add_library_path PROTO_N ((arg_data, directory))
			  PROTO_T (ArgDataP arg_data X
				   CStringP directory)
{
    arg_data->num_library_paths ++;
    cstring_list_append (&(arg_data->library.list.path), directory);
}

void
arg_data_vector_libraries PROTO_N ((arg_data))
			  PROTO_T (ArgDataP arg_data)
{
    unsigned          num_files = arg_data->num_library_files;
    unsigned          num_paths = arg_data->num_library_paths;
    CStringP         *files     = ALLOCATE_VECTOR (CStringP, num_files);
    CStringP         *paths     = ALLOCATE_VECTOR (CStringP, num_paths);
    CStringListEntryP entry;
    unsigned          i;

    for (i = 0, entry = cstring_list_head (&(arg_data->library.list.file));
	 i < num_files; i ++, entry = cstring_list_entry_deallocate (entry)) {
	files [i] = cstring_list_entry_string (entry);
    }
    for (i = 0, entry = cstring_list_head (&(arg_data->library.list.path));
	 i < num_paths; i ++, entry = cstring_list_entry_deallocate (entry)) {
	paths [i] = cstring_list_entry_string (entry);
    }
    arg_data->library.vector.file = files;
    arg_data->library.vector.path = paths;
}

unsigned
arg_data_num_library_files PROTO_N ((arg_data))
			   PROTO_T (ArgDataP arg_data)
{
    return (arg_data->num_library_files);
}

unsigned
arg_data_num_library_paths PROTO_N ((arg_data))
			   PROTO_T (ArgDataP arg_data)
{
    return (arg_data->num_library_paths);
}

CStringP *
arg_data_library_files PROTO_N ((arg_data))
		       PROTO_T (ArgDataP arg_data)
{
    return (arg_data->library.vector.file);
}

CStringP *
arg_data_library_paths PROTO_N ((arg_data))
		       PROTO_T (ArgDataP arg_data)
{
    return (arg_data->library.vector.path);
}

void
arg_data_set_unit_file PROTO_N ((arg_data, unit_file))
		       PROTO_T (ArgDataP arg_data X
				CStringP unit_file)
{
    if (arg_data->unit_file) {
	E_tld_multiple_unit_files ();
	UNREACHED;
    }
    arg_data->unit_file = unit_file;
    capsule_read_unit_set_file (unit_file);
}

void
arg_data_set_files PROTO_N ((arg_data, num_files, files))
		   PROTO_T (ArgDataP  arg_data X
			    int       num_files X
			    CStringP *files)
{
    arg_data->num_files = (unsigned) num_files;
    arg_data->files     = files;
}

unsigned
arg_data_get_num_files PROTO_N ((arg_data))
		       PROTO_T (ArgDataP arg_data)
{
    return (arg_data->num_files);
}

CStringP *
arg_data_get_files PROTO_N ((arg_data))
		   PROTO_T (ArgDataP arg_data)
{
    return (arg_data->files);
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library" "../tdf")
 * eval: (include::add-path-entry "../generated")
 * End:
**/
