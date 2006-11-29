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


/*** types.h --- Type ADTs.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "types.c" for more information.
 *
 *** Change Log:
 * $Log: types.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:59:17  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:45  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/


#ifndef H_TYPES
#define H_TYPES

#include "os-interface.h"
#include "dstring.h"
#include "entry-list.h"
#include "ostream.h"
#include "scope.h"
#include "table.h"

/* To avoid circularity: */
struct AltT;
struct ItemT;
struct SaveRStackT;
struct RuleT;

/*--------------------------------------------------------------------------*/

typedef struct TypeTupleEntryT {
    struct TypeTupleEntryT     *next;
    EntryP			type;
    EntryP			name;
    unsigned			number;
    BoolT			reference;
    BoolT			mutated;
    BoolT			assign;
} TypeTupleEntryT, *TypeTupleEntryP;

typedef struct TransT {
    struct TransT	       *next;
    EntryP			from;
    EntryP			to;
} TransT, *TransP;

typedef struct RTransT {
    struct RTransT	       *next;
    EntryP			from;
    EntryP			to;
    EntryP			type;
    BoolT			reference;
} RTransT, *RTransP;

typedef struct NTransT {
    struct NTransT	       *next;
    EntryP			from;
    unsigned			to;
} NTransT, *NTransP;

typedef struct TypeTupleT {
    TypeTupleEntryP		head;
    TypeTupleEntryP	       *tail;
} TypeTupleT, *TypeTupleP;

typedef struct TypeBTransT {
    TransP			head;
    TransP		       *tail;
} TypeBTransT, *TypeBTransP;

typedef struct SaveBTransT {
    TransP		       *last_ref;
} SaveBTransT, *SaveBTransP;

typedef struct TypeTransT {
    TransP			head;
    TransP		       *tail;
    EntryListT			used_names;
} TypeTransT, *TypeTransP;

typedef struct SaveTransT {
    TransP		       *last_ref;
} SaveTransT, *SaveTransP;

typedef struct TypeRTransT {
    RTransP			head;
    RTransP		       *tail;
} TypeRTransT, *TypeRTransP;

typedef struct TypeNTransT {
    unsigned			count;
    NTransP			head;
    NTransP		       *tail;
} TypeNTransT, *TypeNTransP;

typedef struct SaveNTransT {
    unsigned			last_count;
    NTransP		       *last_ref;
} SaveNTransT, *SaveNTransP;

/*--------------------------------------------------------------------------*/

/* Defined in "types.c": */
extern void		types_init(TypeTupleP);
extern void		types_copy(TypeTupleP, TypeTupleP);
extern void		types_copy_and_translate(TypeTupleP, TypeTupleP,
						 TypeTransP, TableP);
extern void		types_append_copy(TypeTupleP, TypeTupleP);
extern void		types_translate(TypeTupleP, TypeBTransP);
extern void		types_renumber(TypeTupleP, TypeNTransP);
extern void		types_assign(TypeTupleP, TypeTupleP);
extern EntryP		types_find_name_type(TypeTupleP, EntryP, BoolT *);
extern BoolT		types_mutated(TypeTupleP, EntryP);
extern BoolT		types_compute_mutations(TypeTupleP, TypeTupleP,
						TypeTupleP);
extern BoolT		types_compute_assign_mutations(TypeTupleP, TypeTupleP);
extern void		types_propogate_mutations(TypeTupleP, TypeTupleP);
extern BoolT		types_contains(TypeTupleP, EntryP);
extern BoolT		types_contains_names(TypeTupleP);
extern BoolT		types_contains_references(TypeTupleP);
extern void		types_make_references(TypeTupleP, TypeTupleP);
extern BoolT		types_intersect(TypeTupleP, TypeTupleP);
extern void		types_inplace_intersection(TypeTupleP, TypeTupleP);
extern void		types_compute_intersection(TypeTupleP, TypeTupleP,
						   TypeTupleP);
extern CmpT		types_compare(TypeTupleP, TypeTupleP);
extern BoolT		types_equal(TypeTupleP, TypeTupleP);
extern BoolT		types_equal_zero_tuple(TypeTupleP);
extern BoolT		types_equal_names(TypeTupleP, TypeTupleP);
extern BoolT		types_equal_numbers(TypeTupleP, TypeTupleP);
extern void		types_add_name_and_type(TypeTupleP, EntryP, EntryP,
						BoolT);
extern void		types_add_name_and_type_var(TypeTupleP, EntryP, EntryP);
extern BoolT		types_add_type(TypeTupleP, TableP, NStringP, BoolT);
extern void		types_add_name(TypeTupleP, TableP, NStringP, BoolT);
extern BoolT		types_add_typed_name(TypeTupleP, TableP, NStringP,
					     NStringP, BoolT);
extern void		types_add_name_entry(TypeTupleP, EntryP);
extern void		types_add_type_entry(TypeTupleP, EntryP, BoolT);
extern void		types_add_new_names(TypeTupleP, TypeTupleP, EntryP);
extern BoolT		types_disjoint_names(TypeTupleP);
extern BoolT		types_resolve(TypeTupleP, TypeTupleP, TypeTupleP,
				      void(*)(KeyP, KeyP, unsigned), KeyP,
				      unsigned);
extern BoolT		types_check_undefined(TypeTupleP, TypeTupleP,
					      TypeTupleP,
					      void(*)(KeyP, KeyP, unsigned),
					      KeyP, unsigned);
extern BoolT		types_fillin_types(TypeTupleP, TypeTupleP);
extern BoolT		types_fillin_names(TypeTupleP, TypeTupleP);
extern BoolT		types_check_names(TypeTupleP, TypeTupleP);
extern void		types_check_used(TypeTupleP, void(*)(GenericP, EntryP),
					 GenericP);
extern void		types_unlink_used(TypeTupleP, TypeTupleP);
extern void		types_unlink_unused(TypeTupleP, struct AltT *);
extern void		types_compute_formal_renaming(TypeTupleP, TypeRTransP);
extern void		types_compute_formal_inlining(TypeTupleP, TypeTupleP,
						      TypeRTransP,
						      struct SaveRStackT *);
extern void		types_compute_local_renaming(TypeTupleP, TypeTupleP,
						     TypeRTransP,
						     struct SaveRStackT *,
						     TableP);
extern void		types_compute_param_from_trans(TypeTupleP, TypeNTransP,
						       TypeNTransP, TypeTupleP);
extern BoolT		types_check_shadowing(TypeTupleP, ScopeStackP,
					      struct RuleT *);
extern void		types_iter_for_table(TypeTupleP,
					     void(*)(EntryP, GenericP),
					     GenericP);
extern void		types_destroy(TypeTupleP);

extern void		write_type_types(OStreamP, TypeTupleP);
extern void		write_type_names(OStreamP, TypeTupleP, BoolT);

/*--------------------------------------------------------------------------*/

extern void		btrans_init(TypeBTransP);
extern void		btrans_add_translations(TypeBTransP, TypeTupleP,
						TypeTupleP);
extern void		btrans_add_translation(TypeBTransP, EntryP, EntryP);
extern void		btrans_generate_names(TypeBTransP, TypeTupleP, TableP);
extern void		btrans_regenerate_names(TypeBTransP, TypeTupleP);
extern struct ItemT    *btrans_generate_non_pred_names(TypeBTransP, TypeTupleP,
						       TypeTupleP, EntryP,
						       TableP);
extern struct ItemT    *btrans_regen_non_pred_names(TypeBTransP, TypeTupleP,
						    TypeTupleP, TableP);
extern EntryP		btrans_get_translation(TypeBTransP, EntryP);
extern void		btrans_destroy(TypeBTransP);

/*--------------------------------------------------------------------------*/

extern void	rtrans_init(TypeRTransP);
extern void	rtrans_add_translation(TypeRTransP, EntryP, EntryP, EntryP,
				       BoolT);
extern EntryP	rtrans_get_translation(TypeRTransP, EntryP, EntryP *, BoolT *);
extern void	rtrans_apply_for_non_locals(TypeRTransP,
					    void(*)(EntryP, EntryP, GenericP),
					    GenericP);
extern void	rtrans_destroy(TypeRTransP);

/*--------------------------------------------------------------------------*/

extern void	trans_init(TypeTransP, TypeTupleP, TypeTupleP, struct AltT *);
extern void	trans_add_translations(TypeTransP, TypeTupleP, TypeTupleP);
extern void	trans_add_translation(TypeTransP, EntryP, EntryP);
extern void	trans_save_state(TypeTransP, SaveTransP);
extern EntryP	trans_get_translation(TypeTransP, EntryP);
extern void	trans_restore_state(TypeTransP, SaveTransP);
extern void	trans_destroy(TypeTransP);

/*--------------------------------------------------------------------------*/

extern void	ntrans_init(TypeNTransP);
extern void	ntrans_save_state(TypeNTransP, SaveNTransP);
extern unsigned	ntrans_get_translation(TypeNTransP, EntryP);
extern EntryP	ntrans_get_indirect_translation(TypeNTransP, TypeNTransP,
						EntryP);
extern void	ntrans_restore_state(TypeNTransP, SaveNTransP);
extern void	ntrans_destroy(TypeNTransP);

/*--------------------------------------------------------------------------*/

#ifdef FS_FAST
#define types_equal_zero_tuple(t)	((t)->head == NIL(TypeTupleEntryP))
#endif /* defined (FS_FAST) */

#endif /* !defined (H_TYPES) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
