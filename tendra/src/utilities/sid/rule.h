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


/*** rule.h --- Rule ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file specifies the interface to the SID rule, alternative and item
 * handling routines.  The actual implementations are spread across a number
 * of files, but are all logically part of the same file.  See the files named
 * in the declarations for more information.
 *
 *** Change Log:
 * $Log: rule.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1994/12/15  09:58:58  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.2  1994/08/22  09:37:29  smf
 * Fixed bug DR114:ids-too-long.
 *
 * Revision 1.1.1.1  1994/07/25  16:04:42  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_RULE
#define H_RULE

#include "os-interface.h"
#include "bitvec.h"
#include "dalloc.h"
#include "entry.h"
#include "entry-list.h"
#include "non-local.h"
#include "ostream.h"
#include "rstack.h"
#include "table.h"
#include "types.h"

/*--------------------------------------------------------------------------*/

#ifdef FS_NO_ENUM
typedef int DFSStateT, *DFSStateP;
#define DFS_UNTRACED	(0)
#define DFS_TRACING	(1)
#define DFS_CYCLING	(2)
#define DFS_TRACED	(3)
#else
typedef enum {
    DFS_UNTRACED,
    DFS_TRACING,
    DFS_CYCLING,
    DFS_TRACED
} DFSStateT, *DFSStateP;
#endif /* defined (FS_NO_ENUM) */

#ifdef FS_NO_ENUM
typedef int CycleTypeT, *CycleTypeP;
#define CT_LEFT		(0)
#define CT_TAIL		(1)
#define CT_ALL		(2)
#define CT_MUTATE	(3)
#else
typedef enum {
    CT_LEFT,
    CT_TAIL,
    CT_ALL,
    CT_MUTATE
} CycleTypeT, *CycleTypeP;
#endif /* defined (FS_NO_ENUM) */

typedef struct ItemT {
    struct ItemT	       *next;
    TypeTupleT			param;
    TypeTupleT			result;
    EntryTypeT			type;
    EntryP			entry;
    BoolT			inlinable;
    BoolT			tail_call;
} ItemT, *ItemP;

typedef struct AltT {
    struct AltT		       *next;
    TypeTupleT			names;
    BitVecT			first_set;
    ItemP			item_head;
    ItemP		       *item_tail;
} AltT, *AltP;

typedef struct RuleT {
    EntryP			entry;
    TypeTupleT			param;
    TypeTupleT			result;
    NonLocalListT		non_locals;
    NStringT			maximum_scope;
    BoolT			defined;
    BoolT			has_empty_alt;
    BoolT			required;
    EntryListT			reverse_list;
    DFSStateT			dfs_state;
    struct RuleT	       *next_in_root_list;
    struct RuleT	       *next_in_dfs;
    struct RuleT	       *next_in_reverse_dfs;
    BoolT			no_cycles;
    unsigned			cycle_index;
    BoolT			computed_first_set;
    BoolT			computing_first_set;
    BitVecT			first_set;
    EntryListT			predicate_first;
    BoolT			see_through;
    unsigned			priority;
    BoolT			factored;
    struct RuleT	       *tail_group;
    BoolT			being_inlined;
    BoolT			checked_for_inlining;
    EntryListT			call_list;
    struct RuleT	       *next_in_table;
    BitVecT			follow_set;
    EntryListT			predicate_follow;
    BoolT			started_follows;
    AltP			see_through_alt;
    BoolT			needs_function;
    BoolT			all_basics;
    SaveRStackT			rstack_state;
    SaveRStackT			non_local_state;
    BoolT			being_output;
    unsigned			start_label;
    unsigned			call_count;
    unsigned			end_label;
    BoolT			used_end_label;
    unsigned			next_label;
    unsigned			handler_label;
    BoolT			used_handler_label;
    AltP			handler;
    AltP			alt_head;
    AltP		       *alt_tail;
} RuleT, *RuleP;

typedef struct RuleListT {
    RuleP			head;
    RuleP		       *tail;
} RuleListT, *RuleListP;

typedef struct FactorClosureT {
    BitVecT			bitvec1;
    BitVecT			bitvec2;
    TableP			table;
    EntryP			predicate_id;
} FactorClosureT, *FactorClosureP;

typedef struct SimpClosureT {
    BoolT			did_inline;
    TableP			table;
} SimpClosureT, *SimpClosureP;

typedef struct ClashListT {
    struct ClashListT	       *next;
    RuleP			rule;
    AltP			alt;
    ItemP			item;
} ClashListT, *ClashListP;

/*--------------------------------------------------------------------------*/

/* Defined in "rule.c": */
extern RuleP			rule_create
	PROTO_S ((EntryP));
extern void			rule_reinit
	PROTO_S ((RuleP));
extern EntryP			rule_entry
	PROTO_S ((RuleP));
extern TypeTupleP		rule_param
	PROTO_S ((RuleP));
extern TypeTupleP		rule_result
	PROTO_S ((RuleP));
extern NonLocalListP		rule_non_locals
	PROTO_S ((RuleP));
extern NStringP			rule_maximum_scope
	PROTO_S ((RuleP));
extern BoolT			rule_is_defined
	PROTO_S ((RuleP));
extern void			rule_defined
	PROTO_S ((RuleP));
extern void			rule_add_alt
	PROTO_S ((RuleP, AltP));
extern BoolT			rule_has_empty_alt
	PROTO_S ((RuleP));
extern void			rule_add_empty_alt
	PROTO_S ((RuleP));
extern BoolT			rule_has_one_alt
	PROTO_S ((RuleP));
extern void			rule_compute_result_intersect
	PROTO_S ((RuleP));
extern void			rule_compute_minimal_dataflow
	PROTO_S ((RuleP, TypeTupleP));
extern BoolT			rule_is_required
	PROTO_S ((RuleP));
extern void			rule_required
	PROTO_S ((RuleP));
extern void			rule_compute_reverse_list
	PROTO_S ((RuleP, CycleTypeT));
extern void			rule_reinit_reverse_list
	PROTO_S ((RuleP));
extern EntryListP		rule_reverse_list
	PROTO_S ((RuleP));
extern void			rule_set_dfs_state
	PROTO_S ((RuleP, DFSStateT));
extern RuleP			rule_next_in_root_list
	PROTO_S ((RuleP));
extern void			rule_build_root_list
	PROTO_S ((EntryP, GenericP));
extern RuleP			rule_get_next_in_dfs
	PROTO_S ((RuleP));
extern void			rule_compute_dfs
	PROTO_S ((RuleP, CycleTypeT, RuleP *));
extern RuleP			rule_get_next_in_reverse_dfs
	PROTO_S ((RuleP));
extern RuleP		       *rule_next_in_reverse_dfs_ref
	PROTO_S ((RuleP));
extern void			rule_compute_reverse_dfs
	PROTO_S ((RuleP, RuleP, RuleP *));
extern BoolT			rule_has_no_cycles
	PROTO_S ((RuleP));
extern void			rule_no_cycles
	PROTO_S ((RuleP));
extern unsigned			rule_get_cycle_index
	PROTO_S ((RuleP));
extern void			rule_set_cycle_index
	PROTO_S ((RuleP, unsigned));
extern void			rule_reset_cycle_index
	PROTO_S ((RuleP));
extern BoolT			rule_has_computed_first_set
	PROTO_S ((RuleP));
extern void			rule_computed_first_set
	PROTO_S ((RuleP));
extern BoolT			rule_is_computing_first_set
	PROTO_S ((RuleP));
extern void			rule_computing_first_set
	PROTO_S ((RuleP));
extern BitVecP			rule_first_set
	PROTO_S ((RuleP));
extern EntryListP		rule_predicate_first
	PROTO_S ((RuleP));
extern BoolT			rule_is_see_through
	PROTO_S ((RuleP));
extern void			rule_see_through
	PROTO_S ((RuleP));
extern unsigned			rule_get_priority
	PROTO_S ((RuleP));
extern void			rule_set_priority
	PROTO_S ((RuleP, unsigned));
extern BoolT			rule_is_factored
	PROTO_S ((RuleP));
extern void			rule_factored
	PROTO_S ((RuleP));
extern RuleP			rule_get_tail_group
	PROTO_S ((RuleP));
extern void			rule_set_tail_group
	PROTO_S ((RuleP, RuleP));
extern BoolT			rule_is_being_inlined
	PROTO_S ((RuleP));
extern void			rule_being_inlined
	PROTO_S ((RuleP));
extern BoolT			rule_is_checked_for_inlining
	PROTO_S ((RuleP));
extern void			rule_checked_for_inlining
	PROTO_S ((RuleP));
extern EntryListP		rule_call_list
	PROTO_S ((RuleP));
extern RuleP			rule_get_next_in_table
	PROTO_S ((RuleP));
extern RuleP		       *rule_get_next_in_table_ref
	PROTO_S ((RuleP));
extern void			rule_set_next_in_table
	PROTO_S ((RuleP, RuleP));
extern BitVecP			rule_follow_set
	PROTO_S ((RuleP));
extern EntryListP		rule_predicate_follow
	PROTO_S ((RuleP));
extern BoolT			rule_has_started_follows
	PROTO_S ((RuleP));
extern void			rule_started_follows
	PROTO_S ((RuleP));
extern void			rule_set_see_through_alt
	PROTO_S ((RuleP, AltP));
extern AltP			rule_see_through_alt
	PROTO_S ((RuleP));
extern BoolT			rule_needs_function
	PROTO_S ((RuleP));
extern void			rule_will_need_function
	PROTO_S ((RuleP));
extern BoolT			rule_is_all_basics
	PROTO_S ((RuleP));
extern void			rule_all_basics
	PROTO_S ((RuleP));
extern SaveRStackP		rule_rstack_state
	PROTO_S ((RuleP));
extern SaveRStackP		rule_non_local_state
	PROTO_S ((RuleP));
extern BoolT			rule_is_being_output
	PROTO_S ((RuleP));
extern void			rule_being_output
	PROTO_S ((RuleP));
extern void			rule_not_being_output
	PROTO_S ((RuleP));
extern unsigned			rule_get_start_label
	PROTO_S ((RuleP));
extern void			rule_set_start_label
	PROTO_S ((RuleP, unsigned));
extern unsigned			rule_get_call_count
	PROTO_S ((RuleP));
extern void			rule_inc_call_count
	PROTO_S ((RuleP));
extern unsigned			rule_get_end_label
	PROTO_S ((RuleP));
extern void			rule_set_end_label
	PROTO_S ((RuleP, unsigned));
extern BoolT			rule_used_end_label
	PROTO_S ((RuleP));
extern unsigned			rule_get_next_label
	PROTO_S ((RuleP));
extern void			rule_set_next_label
	PROTO_S ((RuleP, unsigned));
extern unsigned			rule_get_handler_label
	PROTO_S ((RuleP));
extern void			rule_set_handler_label
	PROTO_S ((RuleP, unsigned));
extern BoolT			rule_used_handler_label
	PROTO_S ((RuleP));
extern AltP			rule_get_handler
	PROTO_S ((RuleP));
extern void			rule_set_handler
	PROTO_S ((RuleP, AltP));
extern AltP			rule_alt_head
	PROTO_S ((RuleP));
extern void			rule_renumber
	PROTO_S ((RuleP, BoolT, EntryP));
extern void			rule_iter_for_table
	PROTO_S ((RuleP, BoolT, void (*) (EntryP, GenericP), GenericP));
extern void			rule_deallocate
	PROTO_S ((RuleP));

extern void			write_rule_lhs
	PROTO_S ((OStreamP, RuleP));
extern void			write_rule
	PROTO_S ((OStreamP, RuleP));

extern void			rule_list_init
	PROTO_S ((RuleListP));
extern void			rule_list_append
	PROTO_S ((RuleListP, RuleP, RuleP *));
extern void			rule_list_terminate
	PROTO_S ((RuleListP));
extern RuleP			rule_list_head
	PROTO_S ((RuleListP));

/* Defined in "rule-check.c": */
extern void			rule_check_first_set
	PROTO_S ((EntryP, GenericP));
extern void			rule_compute_follow_set
	PROTO_S ((EntryP, GenericP));
extern void			rule_compute_see_through_alt
	PROTO_S ((EntryP, GenericP));
extern void			rule_compute_alt_first_sets
	PROTO_S ((EntryP, GenericP));

extern void			write_clashes
	PROTO_S ((OStreamP, ClashListP));

/* Defined in "rule-error.c": */
extern void			rule_compute_error_list
	PROTO_S ((EntryP, GenericP));

/* Defined in "rule-factor.c": */
extern void			rule_factor
	PROTO_S ((EntryP, GenericP));
extern void			rule_set_factor_limit
	PROTO_S ((unsigned));

/* Defined in "rule-firsts.c": */
extern void			rule_compute_first_set_1
	PROTO_S ((RuleP));
extern void			rule_compute_first_set
	PROTO_S ((EntryP, GenericP));

/* Defined in "rule-lre.c": */
extern void			rule_remove_left_cycle
	PROTO_S ((RuleP, EntryP, TableP));

/* Defined in "rule-mutate.c": */
extern void			rule_compute_mutations
	PROTO_S ((EntryP, GenericP));

/* Defined in "rule-name.c": */
extern void			rule_recompute_alt_names
	PROTO_S ((EntryP, GenericP));

/* Defined in "rule-simp.c": */
extern void			rule_remove_duplicates
	PROTO_S ((TableP, EntryP));

/* Defined in "rule-tail.c": */
extern void			rule_handle_tails
	PROTO_S ((RuleP));
extern void			rule_compute_all_basics
	PROTO_S ((EntryP, GenericP));
extern void			rule_compute_inlining
	PROTO_S ((EntryP, GenericP));
extern void			rule_compute_needed_functions
	PROTO_S ((EntryP, GenericP));
extern void			rule_handle_need_functions
	PROTO_S ((RuleP));
extern BoolT			rule_get_inline_tail_calls
	PROTO_S ((void));
extern void			rule_set_inline_tail_calls
	PROTO_S ((BoolT));
extern void			rule_set_inline_all_basics
	PROTO_S ((BoolT));
extern void			rule_set_inline_singles
	PROTO_S ((BoolT));
extern void			rule_set_inline_non_tail_calls
	PROTO_S ((BoolT));
extern void			rule_set_multiple_inlining
	PROTO_S ((BoolT));

/* Defined in "alt.c": */
extern AltP			alt_create
	PROTO_S ((void));
extern AltP			alt_create_merge
	PROTO_S ((ItemP, ItemP, TypeTransP, TableP));
extern AltP			alt_duplicate
	PROTO_S ((AltP));
extern BoolT			alt_less_than
	PROTO_S ((AltP, AltP));
extern BoolT			alt_equal
	PROTO_S ((AltP, AltP));
extern AltP			alt_next
	PROTO_S ((AltP));
extern AltP		       *alt_next_ref
	PROTO_S ((AltP));
extern void			alt_set_next
	PROTO_S ((AltP, AltP));
extern TypeTupleP		alt_names
	PROTO_S ((AltP));
extern BitVecP			alt_first_set
	PROTO_S ((AltP));
extern ItemP			alt_item_head
	PROTO_S ((AltP));
extern ItemP			alt_unlink_item_head
	PROTO_S ((AltP));
extern void			alt_add_item
	PROTO_S ((AltP, ItemP));
extern AltP			alt_deallocate
	PROTO_S ((AltP));

extern void			write_alt
	PROTO_S ((OStreamP, AltP));
extern void			write_alt_highlighting
	PROTO_S ((OStreamP, AltP, ItemP));

/* Defined in "item.c": */
extern ItemP			item_create
	PROTO_S ((EntryP));
extern ItemP			item_duplicate
	PROTO_S ((ItemP));
extern ItemP			item_duplicate_and_translate
	PROTO_S ((ItemP, TypeTransP, TableP));
extern void			item_translate_list
	PROTO_S ((ItemP, TypeBTransP));
extern void			item_to_predicate
	PROTO_S ((ItemP));
extern ItemP			item_next
	PROTO_S ((ItemP));
extern ItemP		       *item_next_ref
	PROTO_S ((ItemP));
extern void			item_set_next
	PROTO_S ((ItemP, ItemP));
extern EntryP			item_entry
	PROTO_S ((ItemP));
extern void			item_set_entry
	PROTO_S ((ItemP, EntryP));
extern EntryTypeT		item_type
	PROTO_S ((ItemP));
extern BoolT			item_is_rule
	PROTO_S ((ItemP));
extern BoolT			item_is_action
	PROTO_S ((ItemP));
extern BoolT			item_is_predicate
	PROTO_S ((ItemP));
extern BoolT			item_is_basic
	PROTO_S ((ItemP));
extern BoolT			item_is_rename
	PROTO_S ((ItemP));
extern TypeTupleP		item_param
	PROTO_S ((ItemP));
extern void			item_add_param
	PROTO_S ((ItemP, TypeTupleP));
extern TypeTupleP		item_result
	PROTO_S ((ItemP));
extern void			item_add_result
	PROTO_S ((ItemP, TypeTupleP));
extern BoolT			item_is_inlinable
	PROTO_S ((ItemP));
extern void			item_inlinable
	PROTO_S ((ItemP));
extern BoolT			item_is_tail_call
	PROTO_S ((ItemP));
extern void			item_tail_call
	PROTO_S ((ItemP));
extern BoolT			item_names_used_in_list
	PROTO_S ((ItemP, TypeTupleP));
extern void			item_compute_minimal_dataflow
	PROTO_S ((ItemP, TypeTupleP));
extern ItemP			item_deallocate
	PROTO_S ((ItemP));

extern void			write_item
	PROTO_S ((OStreamP, ItemP));

/*--------------------------------------------------------------------------*/

#ifdef FS_FAST
#define rule_entry(r) ((r)->entry)
#define rule_param(r) (&((r)->param))
#define rule_result(r) (&((r)->result))
#define rule_non_locals(r) (&((r)->non_locals))
#define rule_maximum_scope(r) (&((r)->maximum_scope))
#define rule_is_defined(r) ((r)->defined)
#define rule_defined(r) ((r)->defined = TRUE)
#define rule_has_empty_alt(r) ((r)->has_empty_alt)
#define rule_add_empty_alt(r) ((r)->has_empty_alt = TRUE)
#define rule_is_required(r) ((r)->required)
#define rule_required(r) ((r)->required = TRUE)
#define rule_reverse_list(r) (&((r)->reverse_list))
#define rule_set_dfs_state(r, s) ((r)->dfs_state = (s))
#define rule_next_in_root_list(r) ((r)->next_in_root_list)
#define rule_get_next_in_dfs(r) ((r)->next_in_dfs)
#define rule_get_next_in_reverse_dfs(r) ((r)->next_in_reverse_dfs)
#define rule_next_in_reverse_dfs_ref(r) (&((r)->next_in_reverse_dfs))
#define rule_has_no_cycles(r) ((r)->no_cycles)
#define rule_no_cycles(r) ((r)->no_cycles = TRUE)
#define rule_get_cycle_index(r) ((r)->cycle_index)
#define rule_set_cycle_index(r, i) ((r)->cycle_index = (i))
#define rule_reset_cycle_index(r) ((r)->cycle_index = 0)
#define rule_has_computed_first_set(r) ((r)->computed_first_set)
#define rule_computed_first_set(r) ((r)->computed_first_set = TRUE)
#define rule_is_computing_first_set(r) ((r)->computing_first_set)
#define rule_computing_first_set(r) ((r)->computing_first_set = TRUE)
#define rule_first_set(r) (&((r)->first_set))
#define rule_predicate_first(r) (&((r)->predicate_first))
#define rule_is_see_through(r) ((r)->see_through)
#define rule_see_through(r) ((r)->see_through = TRUE)
#define rule_get_priority(r) ((r)->priority)
#define rule_set_priority(r, p) ((r)->priority = (p))
#define rule_is_factored(r) ((r)->factored)
#define rule_factored(r) ((r)->factored = TRUE)
#define rule_get_tail_group(r) ((r)->tail_group)
#define rule_set_tail_group(r1, r2) ((r1)->tail_group = (r2))
#define rule_is_being_inlined(r) ((r)->being_inlined)
#define rule_being_inlined(r) ((r)->being_inlined = TRUE)
#define rule_is_checked_for_inlining(r) ((r)->checked_for_inlining)
#define rule_checked_for_inlining(r) ((r)->checked_for_inlining = TRUE)
#define rule_call_list(r) (&((r)->call_list))
#define rule_get_next_in_table(r) ((r)->next_in_table)
#define rule_get_next_in_table_ref(r) (&((r)->next_in_table))
#define rule_set_next_in_table(r1, r2) ((r1)->next_in_table = (r2))
#define rule_follow_set(r) (&((r)->follow_set))
#define rule_predicate_follow(r) (&((r)->predicate_follow))
#define rule_has_started_follows(r) ((r)->started_follows)
#define rule_started_follows(r) ((r)->started_follows = TRUE)
#define rule_set_all_action_alt(r, a) ((r)->all_action_alt = (a))
#define rule_all_action_alt(r) ((r)->all_action_alt)
#define rule_needs_function(r) ((r)->needs_function)
#define rule_will_need_function(r) ((r)->needs_function = TRUE)
#define rule_is_all_basics(r) ((r)->all_basics)
#define rule_all_basics(r) ((r)->all_basics = TRUE)
#define rule_rstack_state(r) (&((r)->rstack_state))
#define rule_non_local_state(r) (&((r)->non_local_state))
#define rule_is_being_output(r) ((r)->being_output)
#define rule_being_output(r) ((r)->being_output = TRUE)
#define rule_not_being_output(r) ((r)->being_output = FALSE)
#define rule_get_start_label(r) ((r)->start_label)
#define rule_set_start_label(r, l) ((r)->start_label = (l))
#define rule_get_call_count(r) ((r)->call_count)
#define rule_inc_call_count(r) ((r)->call_count ++)
#define rule_used_end_label(r) ((r)->used_end_label)
#define rule_get_next_label(r) ((r)->next_label)
#define rule_set_next_label(r, l) ((r)->next_label = (l))
#define rule_used_handler_label(r) ((r)->used_handler_label)
#define rule_get_handler(r) ((r)->handler)
#define rule_set_handler(r, a) ((r)->handler = (a))
#define rule_alt_head(r) ((r)->alt_head)

#define rule_list_terminate(r) ((*((r)->tail)) = NIL (RuleP))
#define rule_list_head(r) ((r)->head)

#define alt_next(a) ((a)->next)
#define alt_next_ref(a) (&((a)->next))
#define alt_set_next(a1, a2) ((a1)->next = (a2))
#define alt_names(a) (&((a)->names))
#define alt_first_set(a) (&((a)->first_set))
#define alt_item_head(a) ((a)->item_head)

#define item_next(i) ((i)->next)
#define item_next_ref(i) (&((i)->next))
#define item_set_next(i1, i2) ((i1)->next = (i2))
#define item_entry(i) ((i)->entry)
#define item_set_entry(i, e) ((i)->entry = (e))
#define item_type(i) ((i)->type)
#define item_is_rule(i) ((i)->type == ET_RULE)
#define item_is_action(i) ((i)->type == ET_ACTION)
#define item_is_predicate(i) ((i)->type == ET_PREDICATE)
#define item_is_basic(i) ((i)->type == ET_BASIC)
#define item_is_rename(i) ((i)->type == ET_RENAME)
#define item_param(i) (&((i)->param))
#define item_add_param(i, t) (types_assign (&((i)->param), (t)))
#define item_result(i) (&((i)->result))
#define item_add_result(i, t) (types_assign (&((i)->result), (t)))
#define item_is_inlinable(i) ((i)->inlinable)
#define item_inlinable(i) ((i)->inlinable = TRUE)
#define item_is_tail_call(i) ((i)->tail_call)
#define item_tail_call(i) ((i)->tail_call = TRUE)
#endif /* defined (FS_FAST) */

#endif /* !defined (H_RULE) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
