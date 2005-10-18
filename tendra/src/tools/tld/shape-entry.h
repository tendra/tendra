/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


/*** shape-entry.h --- Shape table entry ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "shape-entry.c" for more information.
 *
 *** Change Log:*/

/****************************************************************************/

#ifndef H_SHAPE_ENTRY
#define H_SHAPE_ENTRY

#include "config.h"
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
	NameTableP			names;
	unsigned			id_count;
	BoolT			non_empty;
	unsigned			num_lib_names;
	NameEntryP			head;
	NameEntryP		       *tail;
} ShapeEntryT, *ShapeEntryP;

typedef struct ShapeClosureT {
	MapTableP			table;
	TDFWriterP			writer;
} ShapeClosureT, *ShapeClosureP;

typedef struct ShapeLibClosureT {
	BoolT			did_define;
	struct ShapeTableT	       *lib_shapes;
	struct UnitTableT	       *units;
	struct ShapeTableT	       *shapes;
} ShapeLibClosureT, *ShapeLibClosureP;

/*--------------------------------------------------------------------------*/

extern ShapeEntryP		shape_entry_create(NStringP);
extern ShapeEntryP		shape_entry_next(ShapeEntryP);
extern ShapeEntryP	       *shape_entry_next_ref(ShapeEntryP);
extern NStringP			shape_entry_key(ShapeEntryP);
extern NameTableP		shape_entry_name_table(ShapeEntryP);
extern unsigned			shape_entry_next_id(ShapeEntryP);
extern void			shape_entry_set_non_empty(ShapeEntryP);
extern BoolT			shape_entry_get_non_empty(ShapeEntryP);
extern void			shape_entry_add_to_list(ShapeEntryP, NameEntryP);
extern NameEntryP		shape_entry_get_from_list(ShapeEntryP);
extern ShapeEntryP		shape_entry_deallocate(ShapeEntryP);

extern void			shape_entry_do_count(ShapeEntryP, void *);
extern void			shape_entry_write_shape(ShapeEntryP, void *);
extern void			shape_entry_write_externs(ShapeEntryP, void *);
extern void			shape_entry_compute_tld_size(ShapeEntryP, void *);
extern void			shape_entry_write_tld(ShapeEntryP, void *);
extern void			shape_entry_write_count(ShapeEntryP, void *);
extern void			shape_entry_write_links(ShapeEntryP, void *);
extern void			shape_entry_check_multi_defs(ShapeEntryP, void *);
extern void			shape_entry_do_lib_count(ShapeEntryP, void *);
extern void			shape_entry_do_lib_write(ShapeEntryP, void *);
extern void			shape_entry_resolve_undefined(ShapeEntryP, void *);
extern void			shape_entry_hide_all_defd(ShapeEntryP, void *);
extern void			shape_entry_suppress_mult(ShapeEntryP, void *);
extern void			shape_entry_lib_suppress_mult(ShapeEntryP, void *);
extern void			shape_entry_show_content(ShapeEntryP, void *);

#endif /* !defined (H_SHAPE_ENTRY) */
