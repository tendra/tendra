/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
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

/*
 * types.h - Type ADTs.
 *
 * See the file "types.c" for more information.
 */

#ifndef H_TYPES
#define H_TYPES

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dstring.h>
#include "entry-list.h"
#include <exds/ostream.h>
#include "scope.h"
#include "table.h"

/* To avoid circularity: */
struct AltT;
struct ItemT;
struct SaveRStackT;
struct RuleT;

typedef struct TypeTupleEntryT {
    struct TypeTupleEntryT     *next;
    EntryT *			type;
    EntryT *			name;
    unsigned			number;
    BoolT			reference;
    BoolT			mutated;
    BoolT			assign;
} TypeTupleEntryT;

typedef struct TransT {
    struct TransT	       *next;
    EntryT *			from;
    EntryT *			to;
} TransT;

typedef struct RTransT {
    struct RTransT	       *next;
    EntryT *			from;
    EntryT *			to;
    EntryT *			type;
    BoolT			reference;
} RTransT;

typedef struct NTransT {
    struct NTransT	       *next;
    EntryT *			from;
    unsigned			to;
} NTransT;

typedef struct TypeTupleT {
    TypeTupleEntryT *		head;
    TypeTupleEntryT *	       *tail;
} TypeTupleT;

typedef struct TypeBTransT {
    TransT *			head;
    TransT *		       *tail;
} TypeBTransT;

typedef struct SaveBTransT {
    TransT *		       *last_ref;
} SaveBTransT;

typedef struct TypeTransT {
    TransT *			head;
    TransT *		       *tail;
    EntryListT			used_names;
} TypeTransT;

typedef struct SaveTransT {
    TransT *		       *last_ref;
} SaveTransT;

typedef struct TypeRTransT {
    RTransT *			head;
    RTransT *		       *tail;
} TypeRTransT;

typedef struct TypeNTransT {
    unsigned			count;
    NTransT *			head;
    NTransT *		       *tail;
} TypeNTransT;

typedef struct SaveNTransT {
    unsigned			last_count;
    NTransT *		       *last_ref;
} SaveNTransT;

/* Defined in "types.c": */
void		types_init(TypeTupleT *);
void		types_copy(TypeTupleT *, TypeTupleT *);
void		types_copy_and_translate(TypeTupleT *, TypeTupleT *,
						 TypeTransT *, TableT *);
void		types_append_copy(TypeTupleT *, TypeTupleT *);
void		types_translate(TypeTupleT *, TypeBTransT *);
void		types_renumber(TypeTupleT *, TypeNTransT *);
void		types_assign(TypeTupleT *, TypeTupleT *);
EntryT *		types_find_name_type(TypeTupleT *, EntryT *, BoolT *);
BoolT		types_mutated(TypeTupleT *, EntryT *);
BoolT		types_compute_mutations(TypeTupleT *, TypeTupleT *,
						TypeTupleT *);
BoolT		types_compute_assign_mutations(TypeTupleT *, TypeTupleT *);
void		types_propogate_mutations(TypeTupleT *, TypeTupleT *);
BoolT		types_contains(TypeTupleT *, EntryT *);
BoolT		types_contains_names(TypeTupleT *);
BoolT		types_contains_references(TypeTupleT *);
EntryT *	types_find_ignored(TypeTupleT *tuple);
void		types_make_references(TypeTupleT *, TypeTupleT *);
BoolT		types_intersect(TypeTupleT *, TypeTupleT *);
void		types_inplace_intersection(TypeTupleT *, TypeTupleT *);
void		types_compute_intersection(TypeTupleT *, TypeTupleT *,
						   TypeTupleT *);
CmpT		types_compare(TypeTupleT *, TypeTupleT *);
BoolT		types_equal(TypeTupleT *, TypeTupleT *);
BoolT		types_equal_zero_tuple(TypeTupleT *);
BoolT		types_equal_names(TypeTupleT *, TypeTupleT *);
BoolT		types_equal_numbers(TypeTupleT *, TypeTupleT *);
void		types_add_name_and_type(TypeTupleT *, EntryT *, EntryT *,
						BoolT);
void		types_add_name_and_type_var(TypeTupleT *, EntryT *, EntryT *);
BoolT		types_add_type(TypeTupleT *, TableT *, NStringT *, BoolT);
void		types_add_name(TypeTupleT *, TableT *, NStringT *, BoolT);
BoolT		types_add_typed_name(TypeTupleT *, TableT *, NStringT *,
					     NStringT *, BoolT);
void		types_add_name_entry(TypeTupleT *, EntryT *);
void		types_add_type_entry(TypeTupleT *, EntryT *, BoolT);
void		types_add_new_names(TypeTupleT *, TypeTupleT *, EntryT *);
BoolT		types_disjoint_names(TypeTupleT *);
BoolT		types_resolve(TypeTupleT *, TypeTupleT *, TypeTupleT *,
				      void(*)(KeyT *, KeyT *, unsigned), KeyT *,
				      unsigned);
BoolT		types_check_undefined(TypeTupleT *, TypeTupleT *,
					      TypeTupleT *,
					      void(*)(KeyT *, KeyT *, unsigned),
					      KeyT *, unsigned);
BoolT		types_fillin_types(TypeTupleT *, TypeTupleT *);
BoolT		types_fillin_names(TypeTupleT *, TypeTupleT *);
BoolT		types_check_names(TypeTupleT *, TypeTupleT *);
void		types_check_used(TypeTupleT *, void(*)(void *, EntryT *),
					 void *);
void		types_unlink_used(TypeTupleT *, TypeTupleT *);
void		types_unlink_unused(TypeTupleT *, struct AltT *);
void		types_compute_formal_renaming(TypeTupleT *, TypeRTransT *);
void		types_compute_formal_inlining(TypeTupleT *, TypeTupleT *,
						      TypeRTransT *,
						      struct SaveRStackT *);
void		types_compute_local_renaming(TypeTupleT *, TypeTupleT *,
						     TypeRTransT *,
						     struct SaveRStackT *,
						     TableT *);
void		types_compute_param_from_trans(TypeTupleT *, TypeNTransT *,
						       TypeNTransT *, TypeTupleT *);
BoolT		types_check_shadowing(TypeTupleT *, ScopeStackT *,
					      struct RuleT *);
void		types_iter_for_table(TypeTupleT *,
					     void(*)(EntryT *, void *),
					     void *);
void		types_destroy(TypeTupleT *);

void		write_type_types(OStreamT *, TypeTupleT *);
void		write_type_names(OStreamT *, TypeTupleT *, BoolT);


void		btrans_init(TypeBTransT *);
void		btrans_add_translations(TypeBTransT *, TypeTupleT *,
						TypeTupleT *);
void		btrans_add_translation(TypeBTransT *, EntryT *, EntryT *);
void		btrans_generate_names(TypeBTransT *, TypeTupleT *, TableT *);
void		btrans_regenerate_names(TypeBTransT *, TypeTupleT *);
struct ItemT    *btrans_generate_non_pred_names(TypeBTransT *, TypeTupleT *,
						       TypeTupleT *, EntryT *,
						       TableT *);
struct ItemT    *btrans_regen_non_pred_names(TypeBTransT *, TypeTupleT *,
						    TypeTupleT *, TableT *);
EntryT *		btrans_get_translation(TypeBTransT *, EntryT *);
void		btrans_destroy(TypeBTransT *);


void	rtrans_init(TypeRTransT *);
void	rtrans_add_translation(TypeRTransT *, EntryT *, EntryT *, EntryT *,
				       BoolT);
EntryT *	rtrans_get_translation(TypeRTransT *, EntryT *, EntryT * *, BoolT *);
void	rtrans_apply_for_non_locals(TypeRTransT *,
					    void(*)(EntryT *, EntryT *, void *),
					    void *);
void	rtrans_destroy(TypeRTransT *);


void	trans_init(TypeTransT *, TypeTupleT *, TypeTupleT *, struct AltT *);
void	trans_add_translations(TypeTransT *, TypeTupleT *, TypeTupleT *);
void	trans_add_translation(TypeTransT *, EntryT *, EntryT *);
void	trans_save_state(TypeTransT *, SaveTransT *);
EntryT *	trans_get_translation(TypeTransT *, EntryT *);
void	trans_restore_state(TypeTransT *, SaveTransT *);
void	trans_destroy(TypeTransT *);


void	ntrans_init(TypeNTransT *);
void	ntrans_save_state(TypeNTransT *, SaveNTransT *);
unsigned	ntrans_get_translation(TypeNTransT *, EntryT *);
EntryT *	ntrans_get_indirect_translation(TypeNTransT *, TypeNTransT *,
						EntryT *);
void	ntrans_restore_state(TypeNTransT *, SaveNTransT *);
void	ntrans_destroy(TypeNTransT *);

#endif /* !defined (H_TYPES) */
