/*
 * Copyright (c) 2002-2006 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
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


/*** capsule.c --- TDF capsule ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the TDF capsule routines used by the TDF linker.
 *
 *** Change Log:
 * $Log: capsule.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:18  release
 * First version to be checked into rolling release.
 *
 * Revision 1.5  1997/11/05  14:40:06  smf
 * capsule.c:
 * 	- Added "dgcompunit" for DDCI work (TDF 4.1).
 *
 * Revision 1.4  1995/09/22  08:39:10  smf
 * Fixed problems with incomplete structures (to shut "tcc" up).
 * Fixed some problems in "name-key.c" (no real problems, but rewritten to
 * reduce the warnings that were output by "tcc" and "gcc").
 * Fixed bug CR95_354.tld-common-id-problem (library capsules could be loaded
 * more than once).
 *
 * Revision 1.3  1995/07/07  15:32:15  smf
 * Updated to support TDF specification 4.0.
 *
 * Revision 1.2  1994/12/12  11:46:13  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:29  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#include <assert.h>
#include <limits.h>

#include "capsule.h"
#include "../debug.h"
#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dstring.h>
#include "../gen-errors.h"
#include <exds/istream.h>
#include "name-key.h"
#include "library.h"
#include "../syntax.h"
#include "../tdf.h"
#include "unit-entry.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

typedef struct UnitSetListEntryT {
    struct UnitSetListEntryT   *next;
    NStringT			name;
} UnitSetListEntryT;

typedef struct UnitSetT {
    NStringT			name;
    UnitEntryT *		entry;
} UnitSetT;

typedef struct ShapeDataT {
    ShapeEntryT *		entry;
    unsigned			num_ids;
    unsigned		       *id_maps;
} ShapeDataT;

typedef struct NameDataT {
    NameEntryT *	       *names_vec;
    unsigned			num_names;
} NameDataT;

/*--------------------------------------------------------------------------*/

#define NUM_DEFAULT_UNIT_SETS	(12)

/*--------------------------------------------------------------------------*/

static char * capsule_default_unit_set_names[NUM_DEFAULT_UNIT_SETS] = {
    "tld",
    "tld2",
    "versions",
    "tokdec",
    "tokdef",
    "aldef",
    "diagtype",
    "tagdec",
    "diagdef",
    "dgcompunit",
    "tagdef",
    "linkinfo"
};
static UnitSetT   capsule_default_unit_sets[NUM_DEFAULT_UNIT_SETS];
static unsigned   capsule_num_unit_sets;
static UnitSetT *  capsule_unit_sets     = NULL;
static unsigned   capsule_tld_index     = 0;
static unsigned   capsule_tld2_index    = 1;
static unsigned   capsule_unit_length;
static unsigned   capsule_unit_offset;
static ExceptionT *XX_capsule_error      = EXCEPTION("error in TDF capsule");
static unsigned   capsule_major_version = 0;
static unsigned   capsule_minor_version = 0;

/*--------------------------------------------------------------------------*/

static void
capsule_setup_defaults(void)
{
    if (capsule_unit_sets == NULL) {
	unsigned i;

	for (i = 0; i < NUM_DEFAULT_UNIT_SETS; i++) {
	    nstring_copy_cstring(& (capsule_default_unit_sets[i].name),
				  capsule_default_unit_set_names[i]);
	}
	capsule_num_unit_sets = NUM_DEFAULT_UNIT_SETS;
	capsule_unit_sets     = capsule_default_unit_sets;
    }
}

static void
capsule_setup(UnitTableT * units)
{
    static BoolT need_setup = TRUE;

    if (need_setup) {
	unsigned i;

	capsule_setup_defaults();
	for (i = 0; i < capsule_num_unit_sets; i++) {
	    NStringT *  name = & (capsule_unit_sets[i].name);
	    UnitEntryT *entry;

	    entry = unit_table_add(units, name, i);
	    capsule_unit_sets[i].entry = entry;
	    debug_info_u_name(name);
	}
	need_setup = FALSE;
    }
}

static BoolT
capsule_read_unit_set_name(IStreamT *istream,				    DStringT *dstring)
{
    char c;

    do {
	if (!istream_read_char(istream, &c)) {
	    return(FALSE);
	}
    } while (syntax_is_white_space(c));
    if (c != '"') {
	E_unit_set_expected_quote(istream);
	UNREACHED;
    }
    dstring_init(dstring);
    while (istream_read_char(istream, &c)) {
	if (c == '"') {
	    return(TRUE);
	} else if (c == '\\') {
	    switch (istream_read_escaped_char(istream, &c))EXHAUSTIVE {
	      case ISTREAM_STAT_READ_CHAR:
		dstring_append_char(dstring, c);
		break;
	      case ISTREAM_STAT_NO_CHAR:
		break;
	      case ISTREAM_STAT_SYNTAX_ERROR:
		E_unit_set_illegal_escape(istream);
		UNREACHED;
	    }
	} else {
	    dstring_append_char(dstring, c);
	}
    }
    E_unit_set_eof_in_name(istream);
    UNREACHED;
}

static void
capsule_check_unit_sets(IStreamT *istream)
{
    static BoolT    inited    = FALSE;
    static NStringT tld;
    static NStringT tld2;
    BoolT           tld_found = FALSE;
    unsigned        i;

    if (!inited) {
	nstring_copy_cstring(&tld, "tld");
	nstring_copy_cstring(&tld2, "tld2");
	inited = TRUE;
    }
    capsule_tld_index  = UINT_MAX;
    capsule_tld2_index = UINT_MAX;
    for (i = 0; i < capsule_num_unit_sets; i++) {
	NStringT *name = & (capsule_unit_sets[i].name);
	unsigned j;

	for (j = 0; j < i; j++) {
	    if (nstring_equal(name, & (capsule_unit_sets[j].name))) {
		E_unit_set_duplicate_name(istream_name(istream), name);
		UNREACHED;
	    }
	}
	if (nstring_equal(name, &tld)) {
	    capsule_tld_index = i;
	    tld_found         = TRUE;
	} else if (nstring_equal(name, &tld2)) {
	    capsule_tld2_index = i;
	}
    }
    if (!tld_found) {
	E_unit_set_no_tld_name(istream_name(istream));
	UNREACHED;
    }
}

static void
capsule_read_unit_set_file_1(IStreamT *istream)
{
    UnitSetListEntryT * head          = NULL;
    UnitSetListEntryT **tail          = &head;
    unsigned           num_unit_sets = 0;
    UnitSetListEntryT * entry;
    UnitSetT *          unit_sets;
    unsigned           i;

    for (;;) {
	DStringT dstring;

	if (!capsule_read_unit_set_name(istream, &dstring)) {
	    goto done;
	}
	entry       = ALLOCATE(UnitSetListEntryT);
	entry->next = NULL;
	dstring_to_nstring(&dstring, & (entry->name));
	*tail       = entry;
	tail        = & (entry->next);
	dstring_destroy(&dstring);
	num_unit_sets++;
    }
  done:
    unit_sets = ALLOCATE_VECTOR(UnitSetT, num_unit_sets);
    i         = 0;
    entry     = head;
    while (entry) {
	UnitSetListEntryT *tmp = entry->next;

	nstring_assign(& (unit_sets[i].name), & (entry->name));
	DEALLOCATE(entry);
	entry = tmp;
	i++;
    }
    capsule_num_unit_sets = num_unit_sets;
    capsule_unit_sets     = unit_sets;
    capsule_check_unit_sets(istream);
}

/*--------------------------------------------------------------------------*/

static TDFReaderT *
capsule_reader(CapsuleT *capsule)
{
    assert(capsule->type == CT_INPUT);
    return(& (capsule->u.reader));
}

static TDFWriterT *
capsule_writer(CapsuleT *capsule)
{
    assert(capsule->type == CT_OUTPUT);
    return(& (capsule->u.writer));
}

static NStringT *
capsule_magic(void)
{
    static NStringT const_magic;
    static BoolT    inited = FALSE;

    if (!inited) {
	nstring_copy_cstring(&const_magic, "TDFC");
	inited = TRUE;
    }
    return(&const_magic);
}

/*--------------------------------------------------------------------------*/

static void
capsule_read_header(CapsuleT *capsule)
{
    TDFReaderT *reader      = capsule_reader(capsule);
    NStringT *  const_magic = capsule_magic();
    NStringT   magic;
    unsigned   major;
    unsigned   minor;

    nstring_init_length(&magic,(unsigned)4);
    tdf_read_bytes(reader, &magic);
    if (!nstring_equal(&magic, const_magic)) {
	E_capsule_bad_magic(capsule, &magic, const_magic);
	THROW(XX_capsule_error);
	UNREACHED;
    }
    nstring_destroy(&magic);
    major = tdf_read_int(reader);
    minor = tdf_read_int(reader);
    debug_info_r_versions(major, minor);
    if (major < 4) {
	E_capsule_bad_version(capsule, major);
	THROW(XX_capsule_error);
	UNREACHED;
    } else if (capsule_major_version == 0) {
	capsule_major_version = major;
	capsule_minor_version = minor;
    } else if (capsule_major_version != major) {
	E_capsule_version_mismatch(capsule, capsule_major_version, major);
	THROW(XX_capsule_error);
	UNREACHED;
    } else if (capsule_minor_version < minor) {
	capsule_minor_version = minor;
    }
    tdf_read_align(reader);
}

static UnitEntryT **
capsule_read_unit_set_names(CapsuleT *  capsule,				     UnitTableT *units, 
				     unsigned  *num_unit_sets_ref)
{
    TDFReaderT * reader        = capsule_reader(capsule);
    unsigned    num_unit_sets = tdf_read_int(reader);
    UnitEntryT **units_vec     = ALLOCATE_VECTOR(UnitEntryT *, num_unit_sets);
    UnitEntryT * tld_entry     = capsule_unit_sets[capsule_tld_index].entry;
    UnitEntryT * tld2_entry    = ((capsule_tld2_index == UINT_MAX)?
				 NULL:
				 capsule_unit_sets[capsule_tld2_index].entry);
    BoolT       has_tld_unit  = FALSE;
    unsigned    i;

    debug_info_r_start_unit_decs(num_unit_sets);
    for (i = 0; i < num_unit_sets; i++) {
	NStringT   nstring;
	UnitEntryT *entry;

	tdf_read_string(reader, &nstring);
	if ((entry = unit_table_get(units, &nstring)) != NULL) {
	    unsigned order = unit_entry_order(entry);
	    unsigned j;

	    for (j = 0; j < i; j++) {
		if (entry == units_vec[j]) {
		    E_duplicate_unit_set_name(capsule, &nstring);
		    THROW(XX_capsule_error);
		    UNREACHED;
		} else if (order < unit_entry_order(units_vec[j])) {
		    E_out_of_order_unit_set_name(capsule, &nstring);
		    THROW(XX_capsule_error);
		    UNREACHED;
		}
	    }
	    if (entry == tld2_entry) {
		E_tld2_unit_set_type_obsolete(capsule);
	    }
	    if ((entry == tld_entry) || (entry == tld2_entry)) {
		if (has_tld_unit) {
		    E_extra_tld_unit_set(capsule);
		    THROW(XX_capsule_error);
		    UNREACHED;
		}
		has_tld_unit = TRUE;
	    }
	    units_vec[i] = entry;
	} else {
	    E_unknown_unit_set_name(capsule, &nstring);
	    THROW(XX_capsule_error);
	    UNREACHED;
	}
	debug_info_r_unit_dec(&nstring);
	nstring_destroy(&nstring);
    }
    if (!has_tld_unit) {
	E_missing_tld_unit_set(tdf_reader_name(reader));
    }
    *num_unit_sets_ref = num_unit_sets;
    return(units_vec);
}

static ShapeDataT *
capsule_read_shapes(CapsuleT *   capsule,			     ShapeTableT *shapes, 
			     unsigned   *num_shapes_ref)
{
    TDFReaderT *reader     = capsule_reader(capsule);
    unsigned   num_shapes = tdf_read_int(reader);
    ShapeDataT *shapes_vec = ALLOCATE_VECTOR(ShapeDataT, num_shapes);
    unsigned   i;

    debug_info_r_start_shapes(num_shapes);
    for (i = 0; i < num_shapes; i++) {
	NStringT    nstring;
	unsigned    num_ids;
	ShapeEntryT *entry;
	unsigned    j;

	tdf_read_string(reader, &nstring);
	num_ids = tdf_read_int(reader);
	entry   = shape_table_add(shapes, &nstring);
	for (j = 0; j < i; j++) {
	    if (entry == shapes_vec[j].entry) {
		E_duplicate_shape_name(capsule, &nstring);
		THROW(XX_capsule_error);
		UNREACHED;
	    }
	}
	debug_info_r_shape(&nstring, num_ids);
	nstring_destroy(&nstring);
	shapes_vec[i].entry   = entry;
	shapes_vec[i].num_ids = num_ids;
	shapes_vec[i].id_maps = ALLOCATE_VECTOR(unsigned, num_ids);
	for (j = 0; j < num_ids; j++) {
	    shapes_vec[i].id_maps[j] = UINT_MAX;
	}
    }
    *num_shapes_ref = num_shapes;
    return(shapes_vec);
}

static NameEntryT **
capsule_read_external_names_1(CapsuleT *  capsule,				       ShapeDataT *shape, 
				       unsigned  *num_ref)
{
    TDFReaderT * reader         = capsule_reader(capsule);
    unsigned    num_this_shape = tdf_read_int(reader);
    ShapeEntryT *entry          = shape->entry;
    NStringT *   key            = shape_entry_key(entry);
    NameTableT * table          = shape_entry_name_table(entry);
    unsigned    num_ids        = shape->num_ids;
    unsigned   *id_maps        = shape->id_maps;
    NameEntryT **names_vec      = ALLOCATE_VECTOR(NameEntryT *, num_this_shape);
    unsigned    i;

    debug_info_r_start_shape_names(key, num_this_shape);
    for (i = 0; i < num_this_shape; i++) {
	unsigned   id = tdf_read_int(reader);
	NameKeyT   name;
	NameEntryT *name_entry;

	tdf_read_name(reader, &name);
	if (id >= num_ids) {
	    E_name_id_out_of_range(capsule, key, &name, id, num_ids);
	    THROW(XX_capsule_error);
	    UNREACHED;
	}
	name_entry = name_table_add(table, &name, entry);
	if (id_maps[id]!= UINT_MAX) {
	    E_name_id_used_multiple_times(capsule, key, &name, id);
	    THROW(XX_capsule_error);
	    UNREACHED;
	}
	names_vec[i] = name_entry;
	id_maps[id] = name_entry_id(name_entry);
	debug_info_r_name(&name, id, id_maps[id],
			   name_entry_key(name_entry));
	name_key_destroy(&name);
    }
    *num_ref = num_this_shape;
    return(names_vec);
}

static NameDataT *
capsule_read_external_names(CapsuleT *  capsule,				     unsigned   num_shapes, 
				     ShapeDataT *shapes_vec)
{
    TDFReaderT *reader = capsule_reader(capsule);
    NameDataT *names_vec_vec;
    unsigned   num_names;
    unsigned   i;

    if ((num_names = tdf_read_int(reader)) != num_shapes) {
	E_shape_and_name_count_mismatch(capsule, num_shapes, num_names);
	THROW(XX_capsule_error);
	UNREACHED;
    }
    debug_info_r_start_names(num_names);
    names_vec_vec = ALLOCATE_VECTOR(NameDataT, num_names);
    for (i = 0; i < num_names; i++) {
	ShapeDataT * shape = & (shapes_vec[i]);
	NameEntryT **names_vec;
	unsigned    num_this_shape;

	names_vec = capsule_read_external_names_1(capsule, shape,
						   &num_this_shape);
	names_vec_vec[i].names_vec = names_vec;
	names_vec_vec[i].num_names = num_this_shape;
    }
    return(names_vec_vec);
}

/*--------------------------------------------------------------------------*/

static unsigned
capsule_get_token_index(ShapeTableT *shapes,				 unsigned    num_shapes, 
				 ShapeDataT * shapes_vec)
{
    ShapeEntryT *token_entry = shape_table_get_token_entry(shapes);
    unsigned    i;

    for (i = 0; i < num_shapes; i++) {
	if (shapes_vec[i].entry == token_entry) {
	    return(i);
	}
    }
    return(UINT_MAX);
}

static unsigned
capsule_get_tag_index(ShapeTableT *shapes,			       unsigned    num_shapes, 
			       ShapeDataT * shapes_vec)
{
    ShapeEntryT *tag_entry = shape_table_get_tag_entry(shapes);
    unsigned    i;

    for (i = 0; i < num_shapes; i++) {
	if (shapes_vec[i].entry == tag_entry) {
	    return(i);
	}
    }
    return(UINT_MAX);
}

static void
capsule_read_usage(CapsuleT * capsule,			    NameDataT *entry, 
			    BoolT     need_dec, 
			    BoolT     no_mult, 
			    NStringT * shape_key)
{
    TDFReaderT * reader    = capsule_reader(capsule);
    unsigned    num_names = entry->num_names;
    NameEntryT **names_vec = entry->names_vec;
    unsigned    i;

    debug_info_r_start_usages(shape_key, num_names);
    for (i = 0; i < num_names; i++) {
	unsigned   use        = tdf_read_int(reader);
	NameEntryT *name_entry = names_vec[i];
	unsigned   name_use   = name_entry_get_use(name_entry);
	NameKeyT *  key        = name_entry_key(name_entry);

	if (use & ~(U_USED | U_DECD | U_DEFD | U_MULT)) {
	    E_bad_usage(capsule, shape_key, key, use);
	    THROW(XX_capsule_error);
	    UNREACHED;
	} else if (no_mult && (use & U_MULT)) {
	    E_illegally_multiply_defined(capsule, shape_key, key);
	    THROW(XX_capsule_error);
	    UNREACHED;
	} else if (need_dec &&
		  (((use & (U_DEFD | U_DECD)) == U_DEFD) ||
		   ((use & (U_MULT | U_DECD)) == U_MULT))) {
	    E_defined_but_not_declared(capsule, shape_key, key);
	    THROW(XX_capsule_error);
	    UNREACHED;
	}
	if ((use & U_DEFD) && (name_use & U_DEFD)) {
	    CapsuleT *definition = name_entry_get_definition(name_entry);
	    char * prev_name  = capsule_name(definition);

	    E_multiply_defined(capsule, shape_key, key, prev_name);
	} else if ((use & U_MULT) && (name_use & U_MULT) &&
		  (!(use & U_DEFD)) && (!(name_use & U_DEFD))) {
	    name_entry_set_definition(name_entry, NULL);
	} else if ((use & U_DEFD) ||
		  ((use & U_MULT) && (!(name_use & (U_MULT | U_DEFD))))) {
	    name_entry_set_definition(name_entry, capsule);
	}
	debug_info_r_usage(use, name_use, key);
	name_entry_merge_use(name_entry, use);
    }
}

static void
capsule_read_tld_type_0_unit(CapsuleT *capsule, ShapeTableT *shapes,
			     unsigned num_shapes, ShapeDataT *shapes_vec,
			     NameDataT *names_vec_vec)
{
    unsigned i;

    i = capsule_get_token_index(shapes, num_shapes, shapes_vec);
    if (i != UINT_MAX) {
	NStringT *key = shape_entry_key(shapes_vec[i].entry);

	capsule_read_usage(capsule, & (names_vec_vec[i]), FALSE, TRUE, key);
    }
    i = capsule_get_tag_index(shapes, num_shapes, shapes_vec);
    if (i != UINT_MAX) {
	NStringT *key = shape_entry_key(shapes_vec[i].entry);

	capsule_read_usage(capsule, & (names_vec_vec[i]), TRUE, FALSE, key);
    }
}

static void
capsule_read_tld_type_1_unit(CapsuleT *capsule, ShapeTableT *shapes,
			     unsigned num_shapes, ShapeDataT *shapes_vec,
			     NameDataT *names_vec_vec)
{
    unsigned i;
    unsigned token = capsule_get_token_index(shapes, num_shapes, shapes_vec);
    unsigned tag   = capsule_get_tag_index(shapes, num_shapes, shapes_vec);

    for (i = 0; i < num_shapes; i++) {
	NStringT *key = shape_entry_key(shapes_vec[i].entry);

	capsule_read_usage(capsule, & (names_vec_vec[i]), i == tag,
			    i == token, key);
    }
}

/*--------------------------------------------------------------------------*/

typedef void(*UnitTypeProcP)
(CapsuleT *, ShapeTableT *, unsigned, ShapeDataT *, NameDataT *);

static UnitTypeProcP capsule_type_jump_table[] = {
    capsule_read_tld_type_0_unit,
    capsule_read_tld_type_1_unit
};

#define CAPSULE_TYPE_JUMP_TABLE_SIZE \
	((unsigned)(sizeof(capsule_type_jump_table) / \
		     sizeof(UnitTypeProcP)))

/*--------------------------------------------------------------------------*/

static void
capsule_read_tld_unit_header(CapsuleT *capsule,				      NStringT *unit_set)
{
    TDFReaderT *reader = capsule_reader(capsule);

    if (tdf_read_int(reader) != 1) {
	E_too_many_tld_units(capsule);
	THROW(XX_capsule_error);
	UNREACHED;
    }
    debug_info_r_start_units(unit_set,(unsigned)1);
    debug_info_r_start_unit(unit_set,(unsigned)1,(unsigned)1);
    if (tdf_read_int(reader) != 0) {
	E_too_many_tld_unit_counts(capsule);
	THROW(XX_capsule_error);
	UNREACHED;
    }
    debug_info_r_start_counts((unsigned)0);
    if (tdf_read_int(reader) != 0) {
	E_too_many_tld_unit_mappings(capsule);
	THROW(XX_capsule_error);
	UNREACHED;
    }
    debug_info_r_start_maps((unsigned)0);
    capsule_unit_length = tdf_read_int(reader);
    debug_info_r_unit_body(capsule_unit_length);
    tdf_read_align(reader);
    capsule_unit_offset = tdf_reader_byte(reader);
}

static void
capsule_read_tld_unit_trailer(CapsuleT *capsule)
{
    TDFReaderT *reader  = capsule_reader(capsule);
    unsigned   offset  = tdf_reader_byte(reader);
    unsigned   correct = (capsule_unit_offset + capsule_unit_length);

    tdf_read_align(reader);
    if (correct != offset) {
	E_tld_unit_wrong_size(capsule, correct, offset);
	THROW(XX_capsule_error);
	UNREACHED;
    }
}

static void
capsule_read_tld2_units(CapsuleT *capsule, ShapeTableT *shapes,
			unsigned num_shapes, ShapeDataT *shapes_vec,
			NameDataT *names_vec_vec)
{
    UnitEntryT *tld2_entry = capsule_unit_sets[capsule_tld2_index].entry;
    NStringT *  key        = unit_entry_key(tld2_entry);

    assert(capsule_tld2_index != UINT_MAX);
    capsule_read_tld_unit_header(capsule, key);
    debug_info_r_tld_version((unsigned)0);
    capsule_read_tld_type_0_unit(capsule, shapes, num_shapes, shapes_vec,
				  names_vec_vec);
    capsule_read_tld_unit_trailer(capsule);
}

static void
capsule_read_tld_units(CapsuleT *capsule, ShapeTableT *shapes,
		       unsigned num_shapes, ShapeDataT *shapes_vec,
		       NameDataT *names_vec_vec)
{
    TDFReaderT *reader    = capsule_reader(capsule);
    UnitEntryT *tld_entry = capsule_unit_sets[capsule_tld_index].entry;
    NStringT *  key       = unit_entry_key(tld_entry);
    unsigned   unit_type;

    capsule_read_tld_unit_header(capsule, key);
    unit_type = tdf_read_int(reader);
    if (unit_type >= CAPSULE_TYPE_JUMP_TABLE_SIZE) {
	E_unknown_tld_unit_type(capsule, unit_type);
	THROW(XX_capsule_error);
	UNREACHED;
    }
    debug_info_r_tld_version(unit_type);
   (*(capsule_type_jump_table[unit_type]))(capsule, shapes, num_shapes,
					      shapes_vec, names_vec_vec);
    capsule_read_tld_unit_trailer(capsule);
}

static MapEntryT **
capsule_read_unit_counts(CapsuleT *capsule, unsigned num_shapes,
			 ShapeDataT *shapes_vec, unsigned num_counts,
			 UnitEntryT *unit_entry, UnitT *unit, unsigned unit_num)
{
    if ((num_counts != 0) && (num_counts != num_shapes)) {
	E_unit_count_num_mismatch(capsule, num_counts, num_shapes, unit_num,
				   unit_entry_key(unit_entry));
	THROW(XX_capsule_error);
	UNREACHED;
    }
    debug_info_r_start_counts(num_counts);
    if (num_counts != 0) {
	TDFReaderT *reader  = capsule_reader(capsule);
	MapTableT * table   = unit_map_table(unit);
	MapEntryT **entries = ALLOCATE_VECTOR(MapEntryT *, num_counts);
	unsigned   i;

	for (i = 0; i < num_counts; i++) {
	    unsigned  count = tdf_read_int(reader);
	    NStringT * key   = shape_entry_key(shapes_vec[i].entry);
	    MapEntryT *entry = map_table_add(table, key, count);

	    debug_info_r_count(count, key);
	    entries[i] = entry;
	}
	return(entries);
    } else {
	return(NULL);
    }
}

static void
capsule_read_unit_maps(CapsuleT *capsule, unsigned num_counts,
		       ShapeDataT *shapes_vec, UnitEntryT *unit_entry,
		       unsigned unit_num, MapEntryT **entries)
{
    TDFReaderT *reader          = capsule_reader(capsule);
    unsigned   num_link_shapes = tdf_read_int(reader);
    unsigned   i;

    if (num_link_shapes != num_counts) {
	E_unit_mapping_num_mismatch(capsule, num_link_shapes, num_counts,
				     unit_num, unit_entry_key(unit_entry));
	THROW(XX_capsule_error);
	UNREACHED;
    }
    debug_info_r_start_maps(num_link_shapes);
    for (i = 0; i < num_link_shapes; i++) {
	unsigned    num_links   = tdf_read_int(reader);
	ShapeEntryT *shape_entry = (shapes_vec[i].entry);
	NStringT *   key         = shape_entry_key(shape_entry);
	unsigned    j;

	map_entry_set_num_links(entries[i], num_links);
	debug_info_r_start_shape_maps(key, num_links);
	for (j = 0; j < num_links; j++) {
	    unsigned  internal = tdf_read_int(reader);
	    unsigned  external = tdf_read_int(reader);
	    unsigned  num_ids  = shapes_vec[i].num_ids;
	    unsigned *id_maps  = shapes_vec[i].id_maps;

	    if (external >= num_ids) {
		E_id_out_of_range(capsule, external, num_ids, key, unit_num,
				   unit_entry_key(unit_entry));
		THROW(XX_capsule_error);
		UNREACHED;
	    }
	    if (id_maps[external] == UINT_MAX) {
		unsigned id = shape_entry_next_id(shape_entry);

		id_maps[external] = id;
	    }
	    debug_info_r_map(internal, external, id_maps[external]);
	    external = id_maps[external];
	    map_entry_set_link(entries[i], j, internal, external);
	}
    }
}

static void
capsule_read_unit(CapsuleT *capsule, unsigned num_shapes, ShapeDataT *shapes_vec,
		  UnitEntryT *unit_entry, unsigned unit_num)
{
    TDFReaderT *reader     = capsule_reader(capsule);
    unsigned   num_counts = tdf_read_int(reader);
    UnitT *     unit       = unit_entry_add_unit(unit_entry, num_counts);
    MapEntryT **entries;
    unsigned   size;
    NStringT   nstring;

    entries = capsule_read_unit_counts(capsule, num_shapes, shapes_vec,
					num_counts, unit_entry, unit,
					unit_num);
    capsule_read_unit_maps(capsule, num_counts, shapes_vec, unit_entry,
			    unit_num, entries);
    size = tdf_read_int(reader);
    debug_info_r_unit_body(size);
    nstring_init_length(&nstring, size);
    tdf_read_bytes(reader, &nstring);
    unit_set_contents(unit, &nstring);
    DEALLOCATE(entries);
}

static void
capsule_read_units(CapsuleT *  capsule,			    unsigned   num_shapes, 
			    ShapeDataT *shapes_vec, 
			    UnitEntryT *unit_entry)
{
    TDFReaderT *reader    = capsule_reader(capsule);
    unsigned   num_units = tdf_read_int(reader);
    unsigned   i;

    debug_info_r_start_units(unit_entry_key(unit_entry), num_units);
    for (i = 0; i < num_units; i++) {
	debug_info_r_start_unit(unit_entry_key(unit_entry), i + 1,
				 num_units);
	capsule_read_unit(capsule, num_shapes, shapes_vec, unit_entry, i);
    }
}

static void
capsule_read_unit_sets(CapsuleT *capsule, unsigned num_unit_sets,
		       UnitEntryT **units_vec, ShapeTableT *shapes,
		       unsigned num_shapes, ShapeDataT *shapes_vec,
		       NameDataT *names_vec_vec)
{
    TDFReaderT *reader       = capsule_reader(capsule);
    UnitEntryT *tld_entry    = capsule_unit_sets[capsule_tld_index].entry;
    UnitEntryT *tld2_entry   = ((capsule_tld2_index == UINT_MAX)?
			       NULL:
			       capsule_unit_sets[capsule_tld2_index].entry);
    unsigned   num_units;
    unsigned   i;

    if ((num_units = tdf_read_int(reader)) != num_unit_sets) {
	E_unit_set_count_mismatch(capsule, num_unit_sets, num_units);
	THROW(XX_capsule_error);
	UNREACHED;
    }
    debug_info_r_start_unit_sets(num_units);
    for (i = 0; i < num_units; i++) {
	if (units_vec[i] == tld_entry) {
	    capsule_read_tld_units(capsule, shapes, num_shapes, shapes_vec,
				    names_vec_vec);
	} else if (units_vec[i] == tld2_entry) {
	    capsule_read_tld2_units(capsule, shapes, num_shapes, shapes_vec,
				     names_vec_vec);
	} else {
	    capsule_read_units(capsule, num_shapes, shapes_vec,
				units_vec[i]);
	}
    }
}

/*--------------------------------------------------------------------------*/

static void
capsule_write_header(CapsuleT *capsule)
{
    TDFWriterT *writer      = capsule_writer(capsule);
    NStringT *  const_magic = capsule_magic();

    tdf_write_bytes(writer, const_magic);
    assert(capsule_major_version >= 4);
    tdf_write_int(writer, capsule_major_version);
    tdf_write_int(writer, capsule_minor_version);
    debug_info_w_versions(capsule_major_version, capsule_minor_version);
    tdf_write_align(writer);
}

/*--------------------------------------------------------------------------*/

void
capsule_read_unit_set_file(char * name)
{
    IStreamT istream;

    assert(capsule_unit_sets == NULL);
    if (!istream_open(&istream, name)) {
	E_cannot_open_unit_set_file(name);
	UNREACHED;
    }
    capsule_read_unit_set_file_1(&istream);
    istream_close(&istream);
}

CapsuleT *
capsule_create_stream_input(char * name)
{
    CapsuleT *capsule = ALLOCATE(CapsuleT);

    capsule->type = CT_INPUT;
    if (!tdf_reader_open(capsule_reader(capsule), name)) {
	DEALLOCATE(capsule);
	return(NULL);
    }
    capsule->name     = name;
    capsule->complete = FALSE;
    return(capsule);
}

CapsuleT *
capsule_create_string_input(char * name,				     NStringT *contents)
{
    CapsuleT *capsule = ALLOCATE(CapsuleT);

    capsule->type     = CT_INPUT;
    tdf_reader_open_string(capsule_reader(capsule), name, contents);
    capsule->name     = name;
    capsule->complete = FALSE;
    return(capsule);
}

CapsuleT *
capsule_create_stream_output(char * name)
{
    CapsuleT *capsule = ALLOCATE(CapsuleT);

    capsule->type = CT_OUTPUT;
    if (!tdf_writer_open(capsule_writer(capsule), name)) {
	DEALLOCATE(capsule);
	return(NULL);
    }
    capsule->name = name;
    return(capsule);
}

char *
capsule_name(CapsuleT *capsule)
{
    return(capsule->name);
}

unsigned
capsule_byte(CapsuleT *capsule)
{
    return(tdf_reader_byte(capsule_reader(capsule)));
}

void
capsule_read(CapsuleT *   capsule,		      UnitTableT * units, 
		      ShapeTableT *shapes)
{
    assert(capsule->type == CT_INPUT);
    capsule_setup(units);
    HANDLE {
	UnitEntryT **units_vec;
	unsigned    num_unit_sets;
	ShapeDataT * shapes_vec;
	unsigned    num_shapes;
	NameDataT *  names_vec_vec;
	unsigned    i;

	debug_info_r_start_capsule(capsule_name(capsule));
	capsule_read_header(capsule);
	units_vec     = capsule_read_unit_set_names(capsule, units,
						     &num_unit_sets);
	shapes_vec    = capsule_read_shapes(capsule, shapes, &num_shapes);
	names_vec_vec = capsule_read_external_names(capsule, num_shapes,
						     shapes_vec);
	capsule_read_unit_sets(capsule, num_unit_sets, units_vec, shapes,
				num_shapes, shapes_vec, names_vec_vec);
	tdf_read_eof(capsule_reader(capsule));
	debug_info_r_end_capsule();
	DEALLOCATE(units_vec);
	for (i = 0; i < num_shapes; i++) {
	    DEALLOCATE(shapes_vec[i].id_maps);
	    DEALLOCATE(names_vec_vec[i].names_vec);
	}
	DEALLOCATE(shapes_vec);
	DEALLOCATE(names_vec_vec);
	capsule->complete = TRUE;
    } WITH {
	ExceptionT *exception = EXCEPTION_EXCEPTION();

	debug_info_r_abort_capsule();
	if ((exception != XX_capsule_error) &&
	   (exception != XX_tdf_read_error)) {
	    RETHROW();
	}
    } END_HANDLE
}

void
capsule_store_contents(CapsuleT *capsule)
{
    if (capsule->complete) {
	TDFReaderT *reader = capsule_reader(capsule);
	unsigned   length = tdf_reader_byte(reader);

	nstring_init_length(& (capsule->contents), length);
	tdf_reader_rewind(reader);
	tdf_read_bytes(reader, & (capsule->contents));
	tdf_read_eof(reader);
    }
}

NStringT *
capsule_contents(CapsuleT *capsule)
{
    return(& (capsule->contents));
}

void
capsule_set_index(CapsuleT *capsule,			   unsigned i)
{
    capsule->capsule_index = i;
}

unsigned
capsule_get_index(CapsuleT *capsule)
{
    return(capsule->capsule_index);
}

void
capsule_write(CapsuleT *   capsule,		       UnitTableT * units, 
		       ShapeTableT *shapes)
{
    TDFWriterT *     writer     = capsule_writer(capsule);
    UnitEntryT *     tld_entry  = capsule_unit_sets[capsule_tld_index].entry;
    unsigned        num_shapes = 0;
    UnitSetClosureT unit_set_closure;
    unsigned        i;

    debug_info_w_start_capsule(capsule_name(capsule));
    capsule_write_header(capsule);
    unit_set_closure.num_unit_sets = 1;
    unit_set_closure.shapes        = shapes;
    unit_table_iter(units, unit_entry_do_count,(void *) &unit_set_closure);
    debug_info_w_start_unit_decs(unit_set_closure.num_unit_sets);
    tdf_write_int(writer, unit_set_closure.num_unit_sets);
    for (i = 0; i < capsule_num_unit_sets; i++) {
	UnitEntryT *entry = capsule_unit_sets[i].entry;

	unit_entry_write_unit_set(entry, tld_entry, writer);
    }
    shape_table_iter(shapes, shape_entry_do_count,(void *) &num_shapes);
    debug_info_w_start_shapes(num_shapes);
    tdf_write_int(writer, num_shapes);
    shape_table_iter(shapes, shape_entry_write_shape,(void *)writer);
    debug_info_w_start_names(num_shapes);
    tdf_write_int(writer, num_shapes);
    shape_table_iter(shapes, shape_entry_write_externs,(void *)writer);
    debug_info_w_start_unit_sets(unit_set_closure.num_unit_sets);
    tdf_write_int(writer, unit_set_closure.num_unit_sets);
    for (i = 0; i < capsule_num_unit_sets; i++) {
	UnitEntryT *entry = capsule_unit_sets[i].entry;

	if (entry == tld_entry) {
	    unit_entry_write_tld_unit(entry, shapes, writer);
	} else {
	    unit_entry_write_units(entry, shapes, num_shapes, writer);
	}
    }
    debug_info_w_end_capsule();
}

void
capsule_close(CapsuleT *capsule)
{
    switch (capsule->type)EXHAUSTIVE {
      case CT_INPUT:
	tdf_reader_close(capsule_reader(capsule));
	break;
      case CT_OUTPUT:
	tdf_writer_close(capsule_writer(capsule));
	break;
    }
}

unsigned
capsule_get_major_version(void)
{
    return(capsule_major_version);
}

void
capsule_set_major_version(unsigned major)
{
    capsule_major_version = major;
}

unsigned
capsule_get_minor_version(void)
{
    return(capsule_minor_version);
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
