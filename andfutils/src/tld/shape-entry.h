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


/*** shape-entry.h --- Shape table entry ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "shape-entry.c" for more information.
 *
 *** Change Log:
 * $Log: shape-entry.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:20  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:46:48  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:03:38  smf
 * Initial import of TDF linker 3.5 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_SHAPE_ENTRY
#define H_SHAPE_ENTRY

#include "os-interface.h"
#include "dalloc.h"
#include "dstring.h"
#include "map-table.h"
#include "name-entry.h"
#include "name-table.h"
#include "tdf-write.h"

struct ShapeTableT;
struct UnitTableT;

/*--------------------------------------------------------------------------*/

typedef struct ShapeEntryT {
    struct ShapeEntryT	       *next;
    NStringT			key;
    NameTableT *		names;
    unsigned			id_count;
    BoolT			non_empty;
    unsigned			num_lib_names;
    NameEntryT *		head;
    NameEntryT *	       *tail;
} ShapeEntryT;

typedef struct ShapeClosureT {
    MapTableT *		table;
    TDFWriterT *		writer;
} ShapeClosureT;

typedef struct ShapeLibClosureT {
    BoolT			did_define;
    struct ShapeTableT	       *lib_shapes;
    struct UnitTableT	       *units;
    struct ShapeTableT	       *shapes;
} ShapeLibClosureT;

/*--------------------------------------------------------------------------*/

extern ShapeEntryT *	shape_entry_create
(NStringT *);
extern ShapeEntryT *	shape_entry_next
(ShapeEntryT *);
extern ShapeEntryT *       *shape_entry_next_ref
(ShapeEntryT *);
extern NStringT *		shape_entry_key
(ShapeEntryT *);
extern NameTableT *	shape_entry_name_table
(ShapeEntryT *);
extern unsigned			shape_entry_next_id
(ShapeEntryT *);
extern void			shape_entry_set_non_empty
(ShapeEntryT *);
extern BoolT			shape_entry_get_non_empty
(ShapeEntryT *);
extern void			shape_entry_add_to_list
(ShapeEntryT *, NameEntryT *);
extern NameEntryT *	shape_entry_get_from_list
(ShapeEntryT *);
extern ShapeEntryT *	shape_entry_deallocate
(ShapeEntryT *);

extern void			shape_entry_do_count
(ShapeEntryT *, void *);
extern void			shape_entry_write_shape
(ShapeEntryT *, void *);
extern void			shape_entry_write_externs
(ShapeEntryT *, void *);
extern void			shape_entry_compute_tld_size
(ShapeEntryT *, void *);
extern void			shape_entry_write_tld
(ShapeEntryT *, void *);
extern void			shape_entry_write_count
(ShapeEntryT *, void *);
extern void			shape_entry_write_links
(ShapeEntryT *, void *);
extern void			shape_entry_check_multi_defs
(ShapeEntryT *, void *);
extern void			shape_entry_do_lib_count
(ShapeEntryT *, void *);
extern void			shape_entry_do_lib_write
(ShapeEntryT *, void *);
extern void			shape_entry_resolve_undefined
(ShapeEntryT *, void *);
extern void			shape_entry_hide_all_defd
(ShapeEntryT *, void *);
extern void			shape_entry_suppress_mult
(ShapeEntryT *, void *);
extern void			shape_entry_lib_suppress_mult
(ShapeEntryT *, void *);
extern void			shape_entry_show_content
(ShapeEntryT *, void *);

#endif /* !defined (H_SHAPE_ENTRY) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
