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


/*** library.c --- TDF library ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the TDF library routines used by the TDF linker.
 *
 *** Change Log:
 * $Log: library.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:18  release
 * First version to be checked into rolling release.
 *
 * Revision 1.5  1995/09/22  08:39:17  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 * Fixed some problems in "name-key.c" (no real problems, but rewritten to
 * reduce the warnings that were output by "tcc" and "gcc").
 * Fixed bug CR95_354.tld-common-id-problem (library capsules could be loaded
 * more than once).
 *
 * Revision 1.4  1995/07/07  15:32:25  smf
 * Updated to support TDF specification 4.0.
 *
 * Revision 1.3  1994/12/12  11:46:24  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.2  1994/08/23  09:40:08  smf
 * Fixed bug DR114:ids-too-long.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:31  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#include "library.h"
#include "capsule.h"
#include "debug.h"
#include "exception.h"
#include "file-name.h"
#include "gen-errors.h"
#include "tdf.h"
#include "tdf-write.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

static ExceptionP XX_library_error   = EXCEPTION ("error in TDF library");

/*--------------------------------------------------------------------------*/

static TDFReaderP
library_reader PROTO_N ((library))
	       PROTO_T (LibraryP library)
{
    ASSERT (library->type == LT_INPUT);
    return (&(library->u.reader));
}

static TDFWriterP
library_writer PROTO_N ((library))
	       PROTO_T (LibraryP library)
{
    ASSERT (library->type == LT_OUTPUT);
    return (&(library->u.writer));
}

/*--------------------------------------------------------------------------*/

static void
library_check_index_entry PROTO_N ((library, entry, need_dec, no_mult,
				    shape_key, key, use, lib_capsule, table))
                          PROTO_T (LibraryP    library X
				   ShapeEntryP entry X
				   BoolT       need_dec X
				   BoolT       no_mult X
				   NStringP    shape_key X
				   NameKeyP    key X
				   unsigned    use X
				   LibCapsuleP lib_capsule X
				   NameTableP  table)
{
    NameEntryP  name_entry  = name_table_add (table, key, entry);
    unsigned    name_use    = name_entry_get_use (name_entry);

    if (use & ~(U_USED | U_DECD | U_DEFD | U_MULT)) {
	E_lib_bad_usage (library, shape_key, key, use);
	THROW (XX_library_error);
	UNREACHED;
    } else if (no_mult && (use & U_MULT)) {
	E_lib_illegally_mult_defined (library, shape_key, key);
	THROW (XX_library_error);
	UNREACHED;
    } else if (need_dec &&
	       (((use & (U_DEFD | U_DECD)) == U_DEFD) ||
		((use & (U_MULT | U_DECD)) == U_MULT))) {
	E_lib_defined_but_not_declared (library, shape_key, key);
	THROW (XX_library_error);
	UNREACHED;
    }
    if ((use & U_DEFD) && (name_use & U_DEFD)) {
	LibCapsuleP definition = name_entry_get_lib_definition (name_entry);

	E_lib_multiply_defined (library, shape_key, key, definition);
    } else if ((use & U_MULT) && (name_use & U_MULT) &&
	       (!(use & U_DEFD)) && (!(name_use & U_DEFD))) {
	name_entry_set_lib_definition (name_entry, NIL (LibCapsuleP));
    } else if ((use & U_DEFD) ||
	       ((use & U_MULT) && (!(name_use & (U_MULT | U_DEFD))))) {
	name_entry_set_lib_definition (name_entry, lib_capsule);
    }
    debug_info_r_index_entry (key, use, name_use, name_entry_key (name_entry),
			      lib_capsule_name (lib_capsule));
    name_entry_merge_use (name_entry, use);
}

static unsigned
library_read_version_0_capsules PROTO_N ((library))
				PROTO_T (LibraryP library)
{
    TDFReaderP reader       = library_reader (library);
    unsigned   num_capsules = tdf_read_int (reader);
    unsigned   i;

    debug_info_r_start_capsules (num_capsules);
    library->num_capsules = num_capsules;
    library->capsules     = ALLOCATE_VECTOR (LibCapsuleT, num_capsules);
    for (i = 0; i < num_capsules; i ++) {
	NStringP contents = &(library->capsules [i].contents);
	NStringT nstring;
	unsigned length;

	tdf_read_string (reader, &nstring);
	if (nstring_contains (&nstring, '\0')) {
	    E_null_in_file_name (library, &nstring);
	    THROW (XX_library_error);
	    UNREACHED;
	}
	library->capsules [i].name    = nstring_to_cstring (&nstring);
	library->capsules [i].library = library;
	library->capsules [i].loaded  = FALSE;
	length = tdf_read_int (reader);
	nstring_init_length (contents, length);
	tdf_read_bytes (reader, contents);
	debug_info_r_capsule (&nstring, length);
	nstring_destroy (&nstring);
    }
    return (num_capsules);
}

static void
library_read_version_0 PROTO_N ((library, shapes))
		       PROTO_T (LibraryP    library X
				ShapeTableP shapes)
{
    TDFReaderP  reader       = library_reader (library);
    unsigned    num_capsules = library_read_version_0_capsules (library);
    ShapeEntryP token_entry  = shape_table_get_token_entry (shapes);
    ShapeEntryP tag_entry    = shape_table_get_tag_entry (shapes);
    unsigned    num_shapes   = tdf_read_int (reader);
    unsigned    i;

    debug_info_r_start_index (num_shapes);
    for (i = 0; i < num_shapes; i ++) {
	NStringT    name;
	ShapeEntryP entry;
	BoolT       need_dec;
	BoolT       no_mult;
	NameTableP  table;
	unsigned    num_names;
	unsigned    j;

	tdf_read_string (reader, &name);
	entry     = shape_table_add (shapes, &name);
	need_dec  = (entry == tag_entry);
	no_mult   = (entry == token_entry);
	table     = shape_entry_name_table (entry);
	num_names = tdf_read_int (reader);
	debug_info_r_start_shape_index (&name, num_names);
	for (j = 0; j < num_names; j ++) {
	    NameKeyT    external_name;
	    unsigned    use;
	    unsigned    capsule_index;
	    LibCapsuleP lib_capsule;

	    tdf_read_name (reader, &external_name);
	    use           = tdf_read_int (reader);
	    capsule_index = tdf_read_int (reader);
	    if (capsule_index >= num_capsules) {
		E_capsule_index_too_big (library, &name, &external_name,
					 capsule_index, num_capsules);
		THROW (XX_library_error);
		UNREACHED;
	    }
	    lib_capsule = &(library->capsules [capsule_index]);
	    library_check_index_entry (library, entry, need_dec, no_mult,
				       &name, &external_name, use, lib_capsule,
				       table);
	    name_key_destroy (&external_name);
	}
	nstring_destroy (&name);
    }
    tdf_read_eof (reader);
}

static void
library_extract_1 PROTO_N ((capsule, use_basename))
		  PROTO_T (LibCapsuleP capsule X
			   BoolT       use_basename)
{
    CStringP   old_name = lib_capsule_name (capsule);
    CStringP   name     = old_name;
    NStringP   contents = lib_capsule_contents (capsule);
    TDFWriterT writer;

    if (use_basename) {
	name = file_name_basename (name);
    }
    file_name_populate (name);
    if (tdf_writer_open (&writer, name)) {
	E_extracting_capsule (old_name, name);
	tdf_write_bytes (&writer, contents);
	tdf_writer_close (&writer);
    } else {
	E_cannot_open_output_file (name);
    }
    if (use_basename) {
	DEALLOCATE (name);
    }
}

/*--------------------------------------------------------------------------*/

typedef void (*LibTypeProcP)
	PROTO_S ((LibraryP, ShapeTableP));

static LibTypeProcP library_type_jump_table [] = {
    library_read_version_0
};

#define LIBRARY_TYPE_JUMP_TABLE_SIZE \
	((unsigned) (sizeof (library_type_jump_table) / sizeof (LibTypeProcP)))

/*--------------------------------------------------------------------------*/

static NStringP
library_magic PROTO_Z ()
{
    static NStringT const_magic;
    static BoolT    inited = FALSE;

    if (!inited) {
	nstring_copy_cstring (&const_magic, "TDFL");
	inited = TRUE;
    }
    return (&const_magic);
}

/*--------------------------------------------------------------------------*/

static void
library_read_header PROTO_N ((library))
    		    PROTO_T (LibraryP library)
{
    TDFReaderP reader        = library_reader (library);
    NStringP   const_magic   = library_magic ();
    unsigned   capsule_major = capsule_get_major_version ();
    NStringT   magic;
    unsigned   major;
    unsigned   minor;

    nstring_init_length (&magic, (unsigned) 4);
    tdf_read_bytes (reader, &magic);
    if (!nstring_equal (&magic, const_magic)) {
	E_library_bad_magic (library, &magic, const_magic);
	THROW (XX_library_error);
	UNREACHED;
    }
    nstring_destroy (&magic);
    major = tdf_read_int (reader);
    minor = tdf_read_int (reader);
    debug_info_r_lib_versions (major, minor);
    if (major < 4) {
	E_library_bad_version (library, major);
	THROW (XX_library_error);
	UNREACHED;
    } else if (capsule_major == 0) {
	capsule_set_major_version (major);
    } else if (capsule_major != major) {
	E_library_version_mismatch (library, capsule_major, major);
	THROW (XX_library_error);
	UNREACHED;
    }
    library->major = major;
    library->minor = minor;
    tdf_read_align (reader);
}

/*--------------------------------------------------------------------------*/

static void
library_write_header PROTO_N ((library))
    		     PROTO_T (LibraryP library)
{
    TDFWriterP writer      = library_writer (library);
    NStringP   const_magic = library_magic ();
    unsigned   major       = capsule_get_major_version ();
    unsigned   minor       = capsule_get_minor_version ();

    tdf_write_bytes (writer, const_magic);
    ASSERT (major >= 4);
    tdf_write_int (writer, major);
    tdf_write_int (writer, minor);
    debug_info_w_lib_versions (major, minor);
    tdf_write_align (writer);
}


/*--------------------------------------------------------------------------*/

CStringP
lib_capsule_name PROTO_N ((capsule))
		 PROTO_T (LibCapsuleP capsule)
{
    return (capsule->name);
}

CStringP
lib_capsule_full_name PROTO_N ((capsule))
		      PROTO_T (LibCapsuleP capsule)
{
    CStringP lib_name   = library_name (capsule->library);
    unsigned lib_length = cstring_length (lib_name);
    CStringP name       = lib_capsule_name (capsule);
    unsigned length     = cstring_length (name);
    CStringP full_name  = ALLOCATE_VECTOR (char, lib_length + length + 3);
    CStringP tmp        = full_name;

    (void) memcpy ((GenericP) tmp, (GenericP) lib_name, (SizeT) lib_length);
    tmp += lib_length;
    *tmp = '(';
    tmp ++;
    (void) memcpy ((GenericP) tmp, (GenericP) name, (SizeT) length);
    tmp += length;
    *tmp = ')';
    tmp ++;
    *tmp = '\0';
    return (full_name);
}

NStringP
lib_capsule_contents PROTO_N ((capsule))
		     PROTO_T (LibCapsuleP capsule)
{
    return (&(capsule->contents));
}

BoolT
lib_capsule_is_loaded PROTO_N ((capsule))
    		      PROTO_T (LibCapsuleP capsule)
{
    return (capsule->loaded);
}

void
lib_capsule_loaded PROTO_N ((capsule))
    		   PROTO_T (LibCapsuleP capsule)
{
    capsule->loaded = TRUE;
}

/*--------------------------------------------------------------------------*/

void
write_lib_capsule_full_name PROTO_N ((ostream, capsule))
			    PROTO_T (OStreamP    ostream X
				     LibCapsuleP capsule)
{
    write_cstring (ostream, library_name (capsule->library));
    write_char (ostream, '(');
    write_cstring (ostream, lib_capsule_name (capsule));
    write_char (ostream, ')');
}

/*--------------------------------------------------------------------------*/

LibraryP
library_create_stream_input PROTO_N ((name))
			    PROTO_T (CStringP name)
{
    LibraryP library = ALLOCATE (LibraryT);

    library->type = LT_INPUT;
    if (!tdf_reader_open (library_reader (library), name)) {
	DEALLOCATE (library);
	return (NIL (LibraryP));
    }
    library->name     = name;
    library->complete = FALSE;
    return (library);
}

LibraryP
library_create_stream_output PROTO_N ((name))
			     PROTO_T (CStringP name)
{
    LibraryP library = ALLOCATE (LibraryT);

    library->type = LT_OUTPUT;
    if (!tdf_writer_open (library_writer (library), name)) {
	DEALLOCATE (library);
	return (NIL (LibraryP));
    }
    library->name     = name;
    library->complete = FALSE;
    return (library);
}

CStringP
library_name PROTO_N ((library))
	     PROTO_T (LibraryP library)
{
    return (library->name);
}

unsigned
library_num_capsules PROTO_N ((library))
		     PROTO_T (LibraryP library)
{
    return (library->num_capsules);
}

LibCapsuleP
library_get_capsule PROTO_N ((library, capsule_index))
		    PROTO_T (LibraryP library X
			     unsigned capsule_index)
{
    ASSERT (capsule_index < library->num_capsules);
    return (&(library->capsules [capsule_index]));
}

unsigned
library_byte PROTO_N ((library))
	     PROTO_T (LibraryP library)
{
    return (tdf_reader_byte (library_reader (library)));
}

void
library_content PROTO_N ((library, want_index, want_size, want_version))
		PROTO_T (LibraryP library X
			 BoolT    want_index X
			 BoolT    want_size X
		         BoolT    want_version)
{
    ShapeTableP shapes = shape_table_create ();

    library_read (library, shapes);
    if (library->complete) {
	unsigned i;

	if (want_version) {
	    write_char     (ostream_output, '[');
	    write_unsigned (ostream_output, library->major);
	    write_cstring  (ostream_output, ", ");
	    write_unsigned (ostream_output, library->minor);
	    write_char     (ostream_output, ']');
	    write_newline  (ostream_output);
	}
	for (i = 0; i < library->num_capsules; i ++) {
	    LibCapsuleP capsule = &(library->capsules [i]);

	    write_cstring (ostream_output, lib_capsule_name (capsule));
	    if (want_size) {
		NStringP body = lib_capsule_contents (capsule);

		write_cstring (ostream_output, " (");
		write_unsigned (ostream_output, nstring_length (body));
		write_char (ostream_output, ')');
	    }
	    write_newline (ostream_output);
	}
	if (want_index) {
	    shape_table_iter (shapes, shape_entry_show_content,
			      NIL (GenericP));
	}
    }
}

void
library_extract_all PROTO_N ((library, use_basename))
		    PROTO_T (LibraryP library X
			     BoolT    use_basename)
{
    ShapeTableP shapes = shape_table_create ();

    library_read (library, shapes);
    if (library->complete) {
	unsigned i;

	for (i = 0; i < library->num_capsules; i ++) {
	    LibCapsuleP capsule = &(library->capsules [i]);

	    library_extract_1 (capsule, use_basename);
	}
    }
}

void
library_extract PROTO_N ((library, use_basename, match_basename, num_files,
			  files))
		PROTO_T (LibraryP  library X
			 BoolT     use_basename X
			 BoolT     match_basename X
			 unsigned  num_files X
			 CStringP *files)
{
    ShapeTableP shapes = shape_table_create ();

    library_read (library, shapes);
    if (library->complete) {
	unsigned i;

	for (i = 0; i < num_files; i ++) {
	    BoolT    matched = FALSE;
	    unsigned j;

	    for (j = 0; j < library->num_capsules; j ++) {
		LibCapsuleP capsule   = &(library->capsules [j]);
		CStringP    file_name = (files [i]);
		CStringP    lib_name  = lib_capsule_name (capsule);
		CStringP    base_name = NIL (CStringP);

		if (match_basename) {
		    base_name = file_name_basename (lib_name);
		}
		if ((cstring_equal (file_name, lib_name)) ||
		    (match_basename && cstring_equal (file_name, base_name))) {
		    library_extract_1 (capsule, use_basename);
		    matched = TRUE;
		}
		if (match_basename) {
		    DEALLOCATE (base_name);
		}
	    }
	    if (!matched) {
		E_capsule_not_found (files [i], library_name (library));
	    }
	}
    }
}

void
library_read PROTO_N ((library, shapes))
	     PROTO_T (LibraryP    library X
		      ShapeTableP shapes)
{
    HANDLE {
	TDFReaderP reader = library_reader (library);
	unsigned   library_type;

	debug_info_r_start_library (library_name (library));
	library_read_header (library);
	library_type = tdf_read_int (reader);
	if (library_type >= LIBRARY_TYPE_JUMP_TABLE_SIZE) {
	    E_lib_unknown_type (library, library_type);
	    THROW (XX_library_error);
	    UNREACHED;
	}
	debug_info_r_library_version (library_type);
	(*(library_type_jump_table [library_type])) (library, shapes);
	debug_info_r_end_library ();
	library->complete = TRUE;
    } WITH {
	ExceptionP exception = EXCEPTION_EXCEPTION ();

	debug_info_r_abort_library ();
	if ((exception != XX_tdf_read_error) &&
	    (exception != XX_library_error)) {
	    RETHROW ();
	}
    } END_HANDLE
}

void
library_write PROTO_N ((library, shapes, num_capsules, capsules))
	      PROTO_T (LibraryP    library X
		       ShapeTableP shapes X
		       unsigned    num_capsules X
		       CapsuleP   *capsules)
{
    TDFWriterP writer     = library_writer (library);
    unsigned   num_shapes = 0;
    unsigned   i;

    debug_info_w_start_library (library_name (library));
    library_write_header (library);
    debug_info_w_library_version ((unsigned) 0);
    tdf_write_int (writer, (unsigned) 0);
    debug_info_w_start_capsules (num_capsules);
    tdf_write_int (writer, num_capsules);
    for (i = 0; i < num_capsules; i ++) {
	CapsuleP capsule  = capsules [i];
	CStringP name     = capsule_name (capsule);
	NStringP contents = capsule_contents (capsule);
	unsigned length   = nstring_length (contents);
	NStringT nstring;

	debug_info_w_capsule (name, length);
	nstring_copy_cstring (&nstring, name);
	tdf_write_string (writer, &nstring);
	nstring_destroy (&nstring);
	tdf_write_int (writer, length);
	tdf_write_bytes (writer, contents);
    }
    shape_table_iter (shapes, shape_entry_do_lib_count,
		      (GenericP) &num_shapes);
    debug_info_w_start_index (num_shapes);
    tdf_write_int (writer, num_shapes);
    shape_table_iter (shapes, shape_entry_do_lib_write, (GenericP) writer);
    debug_info_w_end_library ();
}

void
library_close PROTO_N ((library))
	      PROTO_T (LibraryP library)
{
    switch (library->type) EXHAUSTIVE {
      case CT_INPUT:
	tdf_reader_close (library_reader (library));
	break;
      case CT_OUTPUT:
	tdf_writer_close (library_writer (library));
	break;
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
