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
extern void			types_init
	PROTO_S ((TypeTupleP));
extern void			types_copy
	PROTO_S ((TypeTupleP, TypeTupleP));
extern void			types_copy_and_translate
	PROTO_S ((TypeTupleP, TypeTupleP, TypeTransP, TableP));
extern void			types_append_copy
	PROTO_S ((TypeTupleP, TypeTupleP));
extern void			types_translate
	PROTO_S ((TypeTupleP, TypeBTransP));
extern void			types_renumber
	PROTO_S ((TypeTupleP, TypeNTransP));
extern void			types_assign
	PROTO_S ((TypeTupleP, TypeTupleP));
extern EntryP			types_find_name_type
	PROTO_S ((TypeTupleP, EntryP, BoolT *));
extern BoolT			types_mutated
	PROTO_S ((TypeTupleP, EntryP));
extern BoolT			types_compute_mutations
	PROTO_S ((TypeTupleP, TypeTupleP, TypeTupleP));
extern BoolT			types_compute_assign_mutations
	PROTO_S ((TypeTupleP, TypeTupleP));
extern void			types_propogate_mutations
	PROTO_S ((TypeTupleP, TypeTupleP));
extern BoolT			types_contains
	PROTO_S ((TypeTupleP, EntryP));
extern BoolT			types_contains_names
	PROTO_S ((TypeTupleP));
extern BoolT			types_contains_references
	PROTO_S ((TypeTupleP));
extern void			types_make_references
	PROTO_S ((TypeTupleP, TypeTupleP));
extern BoolT			types_intersect
	PROTO_S ((TypeTupleP, TypeTupleP));
extern void			types_inplace_intersection
	PROTO_S ((TypeTupleP, TypeTupleP));
extern void			types_compute_intersection
	PROTO_S ((TypeTupleP, TypeTupleP, TypeTupleP));
extern CmpT			types_compare
	PROTO_S ((TypeTupleP, TypeTupleP));
extern BoolT			types_equal
	PROTO_S ((TypeTupleP, TypeTupleP));
extern BoolT			types_equal_zero_tuple
	PROTO_S ((TypeTupleP));
extern BoolT			types_equal_names
	PROTO_S ((TypeTupleP, TypeTupleP));
extern BoolT			types_equal_numbers
	PROTO_S ((TypeTupleP, TypeTupleP));
extern void			types_add_name_and_type
	PROTO_S ((TypeTupleP, EntryP, EntryP, BoolT));
extern void			types_add_name_and_type_var
	PROTO_S ((TypeTupleP, EntryP, EntryP));
extern BoolT			types_add_type
	PROTO_S ((TypeTupleP, TableP, NStringP, BoolT));
extern void			types_add_name
	PROTO_S ((TypeTupleP, TableP, NStringP, BoolT));
extern BoolT			types_add_typed_name
	PROTO_S ((TypeTupleP, TableP, NStringP, NStringP, BoolT));
extern void			types_add_name_entry
	PROTO_S ((TypeTupleP, EntryP));
extern void			types_add_type_entry
	PROTO_S ((TypeTupleP, EntryP, BoolT));
extern void			types_add_new_names
	PROTO_S ((TypeTupleP, TypeTupleP, EntryP));
extern BoolT			types_disjoint_names
	PROTO_S ((TypeTupleP));
extern BoolT			types_resolve
	PROTO_S ((TypeTupleP, TypeTupleP, TypeTupleP,
		  void (*) (KeyP, KeyP, unsigned), KeyP, unsigned));
extern BoolT			types_check_undefined
	PROTO_S ((TypeTupleP, TypeTupleP, TypeTupleP,
		  void (*) (KeyP, KeyP, unsigned), KeyP, unsigned));
extern BoolT			types_fillin_types
	PROTO_S ((TypeTupleP, TypeTupleP));
extern BoolT			types_fillin_names
	PROTO_S ((TypeTupleP, TypeTupleP));
extern BoolT			types_check_names
	PROTO_S ((TypeTupleP, TypeTupleP));
extern void			types_check_used
	PROTO_S ((TypeTupleP, void (*) (GenericP, EntryP), GenericP));
extern void			types_unlink_used
	PROTO_S ((TypeTupleP, TypeTupleP));
extern void			types_unlink_unused
	PROTO_S ((TypeTupleP, struct AltT *));
extern void			types_compute_formal_renaming
	PROTO_S ((TypeTupleP, TypeRTransP));
extern void			types_compute_formal_inlining
	PROTO_S ((TypeTupleP, TypeTupleP, TypeRTransP, struct SaveRStackT *));
extern void			types_compute_local_renaming
	PROTO_S ((TypeTupleP, TypeTupleP, TypeRTransP, struct SaveRStackT *,
		  TableP));
extern void			types_compute_param_from_trans
	PROTO_S ((TypeTupleP, TypeNTransP, TypeNTransP, TypeTupleP));
extern BoolT			types_check_shadowing
	PROTO_S ((TypeTupleP, ScopeStackP, struct RuleT *));
extern void			types_iter_for_table
	PROTO_S ((TypeTupleP, void (*) (EntryP, GenericP), GenericP));
extern void			types_destroy
	PROTO_S ((TypeTupleP));

extern void			write_type_types
	PROTO_S ((OStreamP, TypeTupleP));
extern void			write_type_names
	PROTO_S ((OStreamP, TypeTupleP, BoolT));

/*--------------------------------------------------------------------------*/

extern void			btrans_init
	PROTO_S ((TypeBTransP));
extern void			btrans_add_translations
	PROTO_S ((TypeBTransP, TypeTupleP, TypeTupleP));
extern void			btrans_add_translation
	PROTO_S ((TypeBTransP, EntryP, EntryP));
extern void			btrans_generate_names
	PROTO_S ((TypeBTransP, TypeTupleP, TableP));
extern void			btrans_regenerate_names
	PROTO_S ((TypeBTransP, TypeTupleP));
extern struct ItemT	       *btrans_generate_non_pred_names
	PROTO_S ((TypeBTransP, TypeTupleP, TypeTupleP, EntryP, TableP));
extern struct ItemT	       *btrans_regen_non_pred_names
	PROTO_S ((TypeBTransP, TypeTupleP, TypeTupleP, TableP));
extern EntryP			btrans_get_translation
	PROTO_S ((TypeBTransP, EntryP));
extern void			btrans_destroy
	PROTO_S ((TypeBTransP));

/*--------------------------------------------------------------------------*/

extern void			rtrans_init
	PROTO_S ((TypeRTransP));
extern void			rtrans_add_translation
	PROTO_S ((TypeRTransP, EntryP, EntryP, EntryP, BoolT));
extern EntryP			rtrans_get_translation
	PROTO_S ((TypeRTransP, EntryP, EntryP *, BoolT *));
extern void			rtrans_apply_for_non_locals
	PROTO_S ((TypeRTransP, void (*) (EntryP, EntryP, GenericP), GenericP));
extern void			rtrans_destroy
	PROTO_S ((TypeRTransP));

/*--------------------------------------------------------------------------*/

extern void			trans_init
	PROTO_S ((TypeTransP, TypeTupleP, TypeTupleP, struct AltT *));
extern void			trans_add_translations
	PROTO_S ((TypeTransP, TypeTupleP, TypeTupleP));
extern void			trans_add_translation
	PROTO_S ((TypeTransP, EntryP, EntryP));
extern void			trans_save_state
	PROTO_S ((TypeTransP, SaveTransP));
extern EntryP			trans_get_translation
	PROTO_S ((TypeTransP, EntryP));
extern void			trans_restore_state
	PROTO_S ((TypeTransP, SaveTransP));
extern void			trans_destroy
	PROTO_S ((TypeTransP));

/*--------------------------------------------------------------------------*/

extern void			ntrans_init
	PROTO_S ((TypeNTransP));
extern void			ntrans_save_state
	PROTO_S ((TypeNTransP, SaveNTransP));
extern unsigned			ntrans_get_translation
	PROTO_S ((TypeNTransP, EntryP));
extern EntryP			ntrans_get_indirect_translation
	PROTO_S ((TypeNTransP, TypeNTransP, EntryP));
extern void			ntrans_restore_state
	PROTO_S ((TypeNTransP, SaveNTransP));
extern void			ntrans_destroy
	PROTO_S ((TypeNTransP));

/*--------------------------------------------------------------------------*/

#ifdef FS_FAST
#define types_equal_zero_tuple(t) ((t)->head == NIL (TypeTupleEntryP))
#endif /* defined (FS_FAST) */

#endif /* !defined (H_TYPES) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
