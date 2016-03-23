/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * library.c - TDF library ADT.
 *
 * This file implements the TDF library routines used by the TDF linker.
 */

#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

#include <exds/exception.h>

#include <shared/check.h>
#include <shared/error.h>
#include <shared/string.h>

#include <tdf/magic.h>

#include "library.h"
#include "capsule.h"
#include "tdf-write.h"
#include "solve-cycles.h"
#include "debug.h"
#include "file-name.h"
#include "tdf.h"


static ExceptionT *XX_library_error   = EXCEPTION("error in TDF library");

static TDFReaderT *
library_reader(LibraryT *library)
{
    assert(library->type == LT_INPUT);
    return &library->u.reader;
}

static TDFWriterT *
library_writer(LibraryT *library)
{
    assert(library->type == LT_OUTPUT);
    return &library->u.writer;
}

static void
library_check_index_entry(LibraryT *library, ShapeEntryT *entry, BoolT need_dec,
			  BoolT no_mult, NStringT *shape_key, NameKeyT *key,
			  unsigned use, LibCapsuleT *lib_capsule,
			  NameTableT *table)
{
    NameEntryT * name_entry  = name_table_add(table, key, entry);
    unsigned    name_use    = name_entry_get_use(name_entry);

    if (use & ~(U_USED | U_DECD | U_DEFD | U_MULT)) {
	error(ERR_SERIOUS, "%s: #%u: external %S '%K' has usage %u "
		"which has no meaning in this implementation",
		library_name(library), library_byte(library),
		(void *) shape_key, (void *) key, use);
	THROW(XX_library_error);
	UNREACHED;
    } else if (no_mult && (use & U_MULT)) {
	error(ERR_SERIOUS, "%s: #%u: external %S '%K' has the "
		"multiply defined bit set illegally", 
		library_name(library), library_byte(library), 
		(void *) shape_key, (void *) key);
	THROW(XX_library_error);
	UNREACHED;
    } else if (need_dec &&
	      (((use & (U_DEFD | U_DECD)) == U_DEFD) ||
		((use & (U_MULT | U_DECD)) == U_MULT))) {
	error(ERR_SERIOUS, "%s: #%u: external %S '%K' is "
		"defined but not declared", 
		library_name(library), library_byte(library),
		(void *) shape_key, (void *) key);
	THROW(XX_library_error);
	UNREACHED;
    }
    if ((use & U_DEFD) && (name_use & U_DEFD)) {
	LibCapsuleT *definition = name_entry_get_lib_definition(name_entry);

	error(ERR_SERIOUS, "%s: #%u: external %S '%K' is defined "
		"more than once in libraries (previous definition in '%N')", 
		library_name(library), library_byte(library),
		(void *) shape_key, (void *) key, (void *) definition);
    } else if ((use & U_MULT) && (name_use & U_MULT) &&
	      (!(use & U_DEFD)) && (!(name_use & U_DEFD))) {
	name_entry_set_lib_definition(name_entry, NULL);
    } else if ((use & U_DEFD) ||
	      ((use & U_MULT) && (!(name_use & (U_MULT | U_DEFD))))) {
	name_entry_set_lib_definition(name_entry, lib_capsule);
    }
    debug_info_r_index_entry(key, use, name_use, name_entry_key(name_entry),
			      lib_capsule_name(lib_capsule));
    name_entry_merge_use(name_entry, use);
}

static unsigned
library_read_version_0_capsules(LibraryT *library)
{
    TDFReaderT *reader       = library_reader(library);
    unsigned   num_capsules = tdf_read_int(reader);
    unsigned   i;

    debug_info_r_start_capsules(num_capsules);
    library->num_capsules = num_capsules;
    library->capsules     = ALLOCATE_VECTOR(LibCapsuleT, num_capsules);
    for (i = 0; i < num_capsules; i++) {
	NStringT *contents = & (library->capsules[i].contents);
	NStringT nstring;
	size_t length;

	tdf_read_string(reader, &nstring);
	if (nstring_contains(&nstring, '\0')) {
		error(ERR_SERIOUS, "%s: #%u:  capsule name '%S' "
			"contains null character", 
			library_name(library), library_byte(library),
			(void *) &nstring);
	    THROW(XX_library_error);
	    UNREACHED;
	}
	library->capsules[i].name    = nstring_to_cstring(&nstring);
	library->capsules[i].library = library;
	library->capsules[i].loaded  = FALSE;
	length = (size_t) tdf_read_int(reader);
	nstring_init_length(contents, length);
	tdf_read_bytes(reader, contents);
	debug_info_r_capsule(&nstring, length);
	nstring_destroy(&nstring);
    }
    return num_capsules;
}

static void
library_read_version_0(LibraryT *   library,				ShapeTableT *shapes)
{
    TDFReaderT * reader       = library_reader(library);
    unsigned    num_capsules = library_read_version_0_capsules(library);
    ShapeEntryT *token_entry  = shape_table_get_token_entry(shapes);
    ShapeEntryT *tag_entry    = shape_table_get_tag_entry(shapes);
    unsigned    num_shapes   = tdf_read_int(reader);
    unsigned    i;

    debug_info_r_start_index(num_shapes);
    for (i = 0; i < num_shapes; i++) {
	NStringT    name;
	ShapeEntryT *entry;
	BoolT       need_dec;
	BoolT       no_mult;
	NameTableT * table;
	unsigned    num_names;
	unsigned    j;

	tdf_read_string(reader, &name);
	entry     = shape_table_add(shapes, &name);
	need_dec  = (entry == tag_entry);
	no_mult   = (entry == token_entry);
	table     = shape_entry_name_table(entry);
	num_names = tdf_read_int(reader);
	debug_info_r_start_shape_index(&name, num_names);
	for (j = 0; j < num_names; j++) {
	    NameKeyT    external_name;
	    unsigned    use;
	    unsigned    capsule_index;
	    LibCapsuleT *lib_capsule;

	    tdf_read_name(reader, &external_name);
	    use           = tdf_read_int(reader);
	    capsule_index = tdf_read_int(reader);
	    if (capsule_index >= num_capsules) {
		error(ERR_SERIOUS, "%s: #%u: external %S '%K' "
			"has capsule index %u (should be less than %u)", 
			library_name(library), library_byte(library),
			(void *) &name, (void *) &external_name, 
			capsule_index, num_capsules);
		THROW(XX_library_error);
		UNREACHED;
	    }
	    lib_capsule = & (library->capsules[capsule_index]);
	    library_check_index_entry(library, entry, need_dec, no_mult,
				       &name, &external_name, use, lib_capsule,
				       table);
	    name_key_destroy(&external_name);
	}
	nstring_destroy(&name);
    }
    tdf_read_eof(reader);
}

static void
library_extract_1(LibCapsuleT *capsule,			   BoolT       use_basename)
{
    char *   old_name = lib_capsule_name(capsule);
    char *   name     = old_name;
    NStringT *  contents = lib_capsule_contents(capsule);
    TDFWriterT writer;

    if (use_basename) {
	name = file_name_basename(name);
    }
    file_name_populate(name);
    if (tdf_writer_open(&writer, name)) {
	/* TODO: ERROR_INFO
	error(ERROR_INFO, "extracted capsule '${cap name}' into '${file name}'", old_name, name);
	*/
	tdf_write_bytes(&writer, contents);
	tdf_writer_close(&writer);
    } else {
	error(ERR_FATAL, "cannot open output file '%s': %s", 
		name, strerror(errno));
    }
    if (use_basename) {
	DEALLOCATE(name);
    }
}

typedef void(*LibTypeProcP)
(LibraryT *, ShapeTableT *);

static LibTypeProcP library_type_jump_table[] = {
    library_read_version_0
};

#define LIBRARY_TYPE_JUMP_TABLE_SIZE \
	((unsigned)(sizeof(library_type_jump_table) / sizeof(LibTypeProcP)))

static NStringT *
library_magic(void)
{
    static NStringT const_magic;
    static BoolT    inited = FALSE;

    if (!inited) {
	nstring_copy_cstring(&const_magic, MAGIC_LINK_NUMBER);
	inited = TRUE;
    }
    return &const_magic;
}

static void
library_read_header(LibraryT *library)
{
    TDFReaderT *reader        = library_reader(library);
    NStringT *  const_magic   = library_magic();
    unsigned   capsule_major = capsule_get_major_version();
    NStringT   magic;
    unsigned   major;
    unsigned   minor;

    nstring_init_length(&magic,(unsigned)4);
    tdf_read_bytes(reader, &magic);
    if (!nstring_equal(&magic, const_magic)) {
	error(ERR_SERIOUS, "bad magic number '%S' should be '%S'",
		(void *) &magic, (void *) const_magic);
	THROW(XX_library_error);
	UNREACHED;
    }
    nstring_destroy(&magic);
    major = tdf_read_int(reader);
    minor = tdf_read_int(reader);
    debug_info_r_lib_versions(major, minor);
    if (major < 4) {
	error(ERR_SERIOUS, "illegal major version number %u", major);
	THROW(XX_library_error);
	UNREACHED;
    } else if (capsule_major == 0) {
	capsule_set_major_version(major);
    } else if (capsule_major != major) {
	error(ERR_SERIOUS, "major version number mismatch (%u should be %u)", 
		capsule_major, major);
	THROW(XX_library_error);
	UNREACHED;
    }
    library->major = major;
    library->minor = minor;
    tdf_read_align(reader);
}

static void
library_write_header(LibraryT *library)
{
    TDFWriterT *writer      = library_writer(library);
    NStringT *  const_magic = library_magic();
    unsigned   major       = capsule_get_major_version();
    unsigned   minor       = capsule_get_minor_version();

    tdf_write_bytes(writer, const_magic);
    assert(major >= 4);
    tdf_write_int(writer, major);
    tdf_write_int(writer, minor);
    debug_info_w_lib_versions(major, minor);
    tdf_write_align(writer);
}

char *
lib_capsule_name(LibCapsuleT *capsule)
{
    return capsule->name;
}

char *
lib_capsule_full_name(LibCapsuleT *capsule)
{
    const char * lib_name   = library_name(capsule->library);
    size_t lib_length = strlen(lib_name);
    char * name       = lib_capsule_name(capsule);
    size_t length     = strlen(name);
    char * full_name  = ALLOCATE_VECTOR(char, lib_length + length + 3);
    char * tmp        = full_name;

    IGNORE memcpy((void *)tmp,(void *)lib_name, lib_length);
    tmp += lib_length;
    *tmp = '(';
    tmp++;
    IGNORE memcpy((void *)tmp,(void *)name, length);
    tmp += length;
    *tmp = ')';
    tmp++;
    *tmp = '\0';
    return full_name;
}

NStringT *
lib_capsule_contents(LibCapsuleT *capsule)
{
    return &capsule->contents;
}

BoolT
lib_capsule_is_loaded(LibCapsuleT *capsule)
{
    return capsule->loaded;
}

void
lib_capsule_loaded(LibCapsuleT *capsule)
{
    capsule->loaded = TRUE;
}

void
write_lib_capsule_full_name(OStreamT *   ostream,				     LibCapsuleT *capsule)
{
    write_cstring(ostream, library_name(capsule->library));
    write_char(ostream, '(');
    write_cstring(ostream, lib_capsule_name(capsule));
    write_char(ostream, ')');
}

LibraryT *
library_create_stream_input(const char * name)
{
    LibraryT *library = ALLOCATE(LibraryT);

    library->type = LT_INPUT;
    if (!tdf_reader_open(library_reader(library), name)) {
	DEALLOCATE(library);
	return NULL;
    }
    library->name     = name;
    library->complete = FALSE;
    return library;
}

LibraryT *
library_create_stream_output(char * name)
{
    LibraryT *library = ALLOCATE(LibraryT);

    library->type = LT_OUTPUT;
    if (!tdf_writer_open(library_writer(library), name)) {
	DEALLOCATE(library);
	return NULL;
    }
    library->name     = name;
    library->complete = FALSE;
    return library;
}

const char *
library_name(LibraryT *library)
{
    return library->name;
}

unsigned
library_num_capsules(LibraryT *library)
{
    return library->num_capsules;
}

LibCapsuleT *
library_get_capsule(LibraryT *library,			     unsigned capsule_index)
{
    assert(capsule_index < library->num_capsules);
    return &library->capsules[capsule_index];
}

size_t
library_byte(LibraryT *library)
{
    return tdf_reader_byte(library_reader(library));
}

void
library_content(LibraryT *library,			 BoolT    want_index, 
			 BoolT    want_size, 
		         BoolT    want_version)
{
    ShapeTableT *shapes = shape_table_create();

    library_read(library, shapes);
    if (library->complete) {
	unsigned i;

	if (want_version) {
	    write_char    (ostream_output, '[');
	    write_unsigned(ostream_output, library->major);
	    write_cstring (ostream_output, ", ");
	    write_unsigned(ostream_output, library->minor);
	    write_char    (ostream_output, ']');
	    write_newline (ostream_output);
	}
	for (i = 0; i < library->num_capsules; i++) {
	    LibCapsuleT *capsule = & (library->capsules[i]);

	    write_cstring(ostream_output, lib_capsule_name(capsule));
	    if (want_size) {
		NStringT *body = lib_capsule_contents(capsule);

		write_cstring(ostream_output, " (");
		write_unsigned(ostream_output, (unsigned) nstring_length(body));
		write_char(ostream_output, ')');
	    }
	    write_newline(ostream_output);
	}
	if (want_index) {
	    shape_table_iter(shapes, shape_entry_show_content,
			      NULL);
	}
    }
}

void
library_extract_all(LibraryT *library,			     BoolT    use_basename)
{
    ShapeTableT *shapes = shape_table_create();

    library_read(library, shapes);
    if (library->complete) {
	unsigned i;

	for (i = 0; i < library->num_capsules; i++) {
	    LibCapsuleT *capsule = & (library->capsules[i]);

	    library_extract_1(capsule, use_basename);
	}
    }
}

void
library_extract(LibraryT *library, BoolT use_basename, BoolT match_basename,
		unsigned num_files, char * *files)
{
    ShapeTableT *shapes = shape_table_create();

    library_read(library, shapes);
    if (library->complete) {
	unsigned i;

	for (i = 0; i < num_files; i++) {
	    BoolT    matched = FALSE;
	    unsigned j;

	    for (j = 0; j < library->num_capsules; j++) {
		LibCapsuleT *capsule   = & (library->capsules[j]);
		char *    file_name = (files[i]);
		char *    lib_name  = lib_capsule_name(capsule);
		char *    base_name = NULL;

		if (match_basename) {
		    base_name = file_name_basename(lib_name);
		}
		if ((streq(file_name, lib_name)) ||
		   (match_basename && streq(file_name, base_name))) {
		    library_extract_1(capsule, use_basename);
		    matched = TRUE;
		}
		if (match_basename) {
		    DEALLOCATE(base_name);
		}
	    }
	    if (!matched) {
		error(ERR_SERIOUS, "capsule '%s' is not contained "
			"in library '%s'", 
			files[i], library_name(library));
	    }
	}
    }
}

void
library_read(LibraryT *   library,		      ShapeTableT *shapes)
{
    HANDLE {
	TDFReaderT *reader = library_reader(library);
	unsigned   library_type;

	debug_info_r_start_library(library_name(library));
	library_read_header(library);
	library_type = tdf_read_int(reader);
	if (library_type >= LIBRARY_TYPE_JUMP_TABLE_SIZE) {
		error(ERR_SERIOUS, "library version number %u "
			"is not supported in this implementation", 
			library_type);	
	    THROW(XX_library_error);
	    UNREACHED;
	}
	debug_info_r_library_version(library_type);
	(*(library_type_jump_table[library_type]))(library, shapes);
	debug_info_r_end_library();
	library->complete = TRUE;
    } WITH {
	ExceptionT *exception = EXCEPTION_EXCEPTION();

	debug_info_r_abort_library();
	if ((exception != XX_tdf_read_error) &&
	   (exception != XX_library_error)) {
	    RETHROW();
	}
    } END_HANDLE
}

void
library_write(LibraryT *   library,		       ShapeTableT *shapes, 
		       unsigned    num_capsules, 
		       CapsuleT *  *capsules)
{
    TDFWriterT *writer     = library_writer(library);
    unsigned   num_shapes = 0;
    unsigned   i;

    debug_info_w_start_library(library_name(library));
    library_write_header(library);
    debug_info_w_library_version((unsigned)0);
    tdf_write_int(writer,(unsigned)0);
    debug_info_w_start_capsules(num_capsules);
    tdf_write_int(writer, num_capsules);
    for (i = 0; i < num_capsules; i++) {
	CapsuleT *capsule  = capsules[i];
	char * name     = capsule_name(capsule);
	NStringT *contents = capsule_contents(capsule);
	size_t length   = nstring_length(contents);
	NStringT nstring;

	debug_info_w_capsule(name, length);
	nstring_copy_cstring(&nstring, name);
	tdf_write_string(writer, &nstring);
	nstring_destroy(&nstring);
	tdf_write_int(writer, (unsigned) length);
	tdf_write_bytes(writer, contents);
    }
    shape_table_iter(shapes, shape_entry_do_lib_count,
		     (void *) &num_shapes);
    debug_info_w_start_index(num_shapes);
    tdf_write_int(writer, num_shapes);
    shape_table_iter(shapes, shape_entry_do_lib_write,(void *)writer);
    debug_info_w_end_library();
}

void
library_close(LibraryT *library)
{
    switch (library->type) {
      case CT_INPUT:
	tdf_reader_close(library_reader(library));
	break;
      case CT_OUTPUT:
	tdf_writer_close(library_writer(library));
	break;
    }
}
