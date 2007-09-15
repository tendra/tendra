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

#include "../os-interface.h"
#include "../eds/dstring.h"
#include "entry-list.h"
#include "../eds/ostream.h"
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
extern void		types_init(TypeTupleT *);
extern void		types_copy(TypeTupleT *, TypeTupleT *);
extern void		types_copy_and_translate(TypeTupleT *, TypeTupleT *,
						 TypeTransT *, TableT *);
extern void		types_append_copy(TypeTupleT *, TypeTupleT *);
extern void		types_translate(TypeTupleT *, TypeBTransT *);
extern void		types_renumber(TypeTupleT *, TypeNTransT *);
extern void		types_assign(TypeTupleT *, TypeTupleT *);
extern EntryT *		types_find_name_type(TypeTupleT *, EntryT *, BoolT *);
extern BoolT		types_mutated(TypeTupleT *, EntryT *);
extern BoolT		types_compute_mutations(TypeTupleT *, TypeTupleT *,
						TypeTupleT *);
extern BoolT		types_compute_assign_mutations(TypeTupleT *, TypeTupleT *);
extern void		types_propogate_mutations(TypeTupleT *, TypeTupleT *);
extern BoolT		types_contains(TypeTupleT *, EntryT *);
extern BoolT		types_contains_names(TypeTupleT *);
extern BoolT		types_contains_references(TypeTupleT *);
extern void		types_make_references(TypeTupleT *, TypeTupleT *);
extern BoolT		types_intersect(TypeTupleT *, TypeTupleT *);
extern void		types_inplace_intersection(TypeTupleT *, TypeTupleT *);
extern void		types_compute_intersection(TypeTupleT *, TypeTupleT *,
						   TypeTupleT *);
extern CmpT		types_compare(TypeTupleT *, TypeTupleT *);
extern BoolT		types_equal(TypeTupleT *, TypeTupleT *);
extern BoolT		types_equal_zero_tuple(TypeTupleT *);
extern BoolT		types_equal_names(TypeTupleT *, TypeTupleT *);
extern BoolT		types_equal_numbers(TypeTupleT *, TypeTupleT *);
extern void		types_add_name_and_type(TypeTupleT *, EntryT *, EntryT *,
						BoolT);
extern void		types_add_name_and_type_var(TypeTupleT *, EntryT *, EntryT *);
extern BoolT		types_add_type(TypeTupleT *, TableT *, NStringT *, BoolT);
extern void		types_add_name(TypeTupleT *, TableT *, NStringT *, BoolT);
extern BoolT		types_add_typed_name(TypeTupleT *, TableT *, NStringT *,
					     NStringT *, BoolT);
extern void		types_add_name_entry(TypeTupleT *, EntryT *);
extern void		types_add_type_entry(TypeTupleT *, EntryT *, BoolT);
extern void		types_add_new_names(TypeTupleT *, TypeTupleT *, EntryT *);
extern BoolT		types_disjoint_names(TypeTupleT *);
extern BoolT		types_resolve(TypeTupleT *, TypeTupleT *, TypeTupleT *,
				      void(*)(KeyT *, KeyT *, unsigned), KeyT *,
				      unsigned);
extern BoolT		types_check_undefined(TypeTupleT *, TypeTupleT *,
					      TypeTupleT *,
					      void(*)(KeyT *, KeyT *, unsigned),
					      KeyT *, unsigned);
extern BoolT		types_fillin_types(TypeTupleT *, TypeTupleT *);
extern BoolT		types_fillin_names(TypeTupleT *, TypeTupleT *);
extern BoolT		types_check_names(TypeTupleT *, TypeTupleT *);
extern void		types_check_used(TypeTupleT *, void(*)(void *, EntryT *),
					 void *);
extern void		types_unlink_used(TypeTupleT *, TypeTupleT *);
extern void		types_unlink_unused(TypeTupleT *, struct AltT *);
extern void		types_compute_formal_renaming(TypeTupleT *, TypeRTransT *);
extern void		types_compute_formal_inlining(TypeTupleT *, TypeTupleT *,
						      TypeRTransT *,
						      struct SaveRStackT *);
extern void		types_compute_local_renaming(TypeTupleT *, TypeTupleT *,
						     TypeRTransT *,
						     struct SaveRStackT *,
						     TableT *);
extern void		types_compute_param_from_trans(TypeTupleT *, TypeNTransT *,
						       TypeNTransT *, TypeTupleT *);
extern BoolT		types_check_shadowing(TypeTupleT *, ScopeStackT *,
					      struct RuleT *);
extern void		types_iter_for_table(TypeTupleT *,
					     void(*)(EntryT *, void *),
					     void *);
extern void		types_destroy(TypeTupleT *);

extern void		write_type_types(OStreamT *, TypeTupleT *);
extern void		write_type_names(OStreamT *, TypeTupleT *, BoolT);


extern void		btrans_init(TypeBTransT *);
extern void		btrans_add_translations(TypeBTransT *, TypeTupleT *,
						TypeTupleT *);
extern void		btrans_add_translation(TypeBTransT *, EntryT *, EntryT *);
extern void		btrans_generate_names(TypeBTransT *, TypeTupleT *, TableT *);
extern void		btrans_regenerate_names(TypeBTransT *, TypeTupleT *);
extern struct ItemT    *btrans_generate_non_pred_names(TypeBTransT *, TypeTupleT *,
						       TypeTupleT *, EntryT *,
						       TableT *);
extern struct ItemT    *btrans_regen_non_pred_names(TypeBTransT *, TypeTupleT *,
						    TypeTupleT *, TableT *);
extern EntryT *		btrans_get_translation(TypeBTransT *, EntryT *);
extern void		btrans_destroy(TypeBTransT *);


extern void	rtrans_init(TypeRTransT *);
extern void	rtrans_add_translation(TypeRTransT *, EntryT *, EntryT *, EntryT *,
				       BoolT);
extern EntryT *	rtrans_get_translation(TypeRTransT *, EntryT *, EntryT * *, BoolT *);
extern void	rtrans_apply_for_non_locals(TypeRTransT *,
					    void(*)(EntryT *, EntryT *, void *),
					    void *);
extern void	rtrans_destroy(TypeRTransT *);


extern void	trans_init(TypeTransT *, TypeTupleT *, TypeTupleT *, struct AltT *);
extern void	trans_add_translations(TypeTransT *, TypeTupleT *, TypeTupleT *);
extern void	trans_add_translation(TypeTransT *, EntryT *, EntryT *);
extern void	trans_save_state(TypeTransT *, SaveTransT *);
extern EntryT *	trans_get_translation(TypeTransT *, EntryT *);
extern void	trans_restore_state(TypeTransT *, SaveTransT *);
extern void	trans_destroy(TypeTransT *);


extern void	ntrans_init(TypeNTransT *);
extern void	ntrans_save_state(TypeNTransT *, SaveNTransT *);
extern unsigned	ntrans_get_translation(TypeNTransT *, EntryT *);
extern EntryT *	ntrans_get_indirect_translation(TypeNTransT *, TypeNTransT *,
						EntryT *);
extern void	ntrans_restore_state(TypeNTransT *, SaveNTransT *);
extern void	ntrans_destroy(TypeNTransT *);

#endif /* !defined (H_TYPES) */
