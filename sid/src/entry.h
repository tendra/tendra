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


/*** entry.h --- Identifier table entry ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "entry.c" for more information.
 *
 *** Change Log:
 * $Log: entry.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:58:11  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:34  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#ifndef H_ENTRY
#define H_ENTRY

#include "os-interface.h"
#include "dalloc.h"
#include "dstring.h"
#include "ostream.h"
#include "key.h"

/* To avoid circularity: */
#ifdef __TenDRA__
#pragma TenDRA begin
#pragma TenDRA complete struct/union analysis off
#endif
struct ActionT;
struct BasicT;
struct NameT;
struct RuleT;
struct TypeT;

/*--------------------------------------------------------------------------*/

#ifdef FS_NO_ENUM
typedef int EntryTypeT, *EntryTypeP;
#define ET_TYPE		(0)
#define ET_BASIC	(1)
#define ET_RULE		(2)
#define ET_ACTION	(3)
#define ET_NAME		(4)
#define ET_RENAME	(5)
#define ET_PREDICATE	(6)
#define ET_NON_LOCAL	(7)
#else
typedef enum {
    ET_TYPE,
    ET_BASIC,
    ET_RULE,
    ET_ACTION,
    ET_NAME,
    ET_RENAME,
    ET_PREDICATE,
    ET_NON_LOCAL
} EntryTypeT, *EntryTypeP;
#endif /* defined (FS_NO_ENUM) */

typedef struct EntryT {
    struct EntryT	       *next;
    KeyT			key;
    BoolT			mapped;
    NStringT			mapping;
    EntryTypeT			type;
    BoolT			traced;
    union {
	struct BasicT	       *basic;
	struct RuleT	       *rule;
	struct ActionT	       *action;
	struct TypeT	       *type;
	struct EntryT	       *non_local;
    } u;
    struct NameT	       *name;
} EntryT, *EntryP;

/*--------------------------------------------------------------------------*/

extern EntryP			entry_create_from_string
	PROTO_S ((NStringP, unsigned, EntryTypeT));
extern EntryP			entry_create_from_number
	PROTO_S ((unsigned, EntryTypeT, BoolT, EntryP));
extern void			entry_set_basic
	PROTO_S ((EntryP, struct BasicT *));
extern void			entry_set_rule
	PROTO_S ((EntryP, struct RuleT *));
extern void			entry_set_action
	PROTO_S ((EntryP, struct ActionT *));
extern void			entry_set_type
	PROTO_S ((EntryP, struct TypeT *));
extern void			entry_set_non_local
	PROTO_S ((EntryP, EntryP));
extern EntryP			entry_next
	PROTO_S ((EntryP));
extern EntryP		       *entry_next_ref
	PROTO_S ((EntryP));
extern KeyP			entry_key
	PROTO_S ((EntryP));
extern EntryTypeT		entry_type
	PROTO_S ((EntryP));
extern void			entry_change_type
	PROTO_S ((EntryP, EntryTypeT));
extern BoolT			entry_is_basic
	PROTO_S ((EntryP));
extern BoolT			entry_is_action
	PROTO_S ((EntryP));
extern BoolT			entry_is_rule
	PROTO_S ((EntryP));
extern BoolT			entry_is_type
	PROTO_S ((EntryP));
extern BoolT			entry_is_non_local
	PROTO_S ((EntryP));
extern struct BasicT	       *entry_get_basic
	PROTO_S ((EntryP));
extern struct ActionT	       *entry_get_action
	PROTO_S ((EntryP));
extern struct RuleT	       *entry_get_rule
	PROTO_S ((EntryP));
extern struct NameT	       *entry_get_name
	PROTO_S ((EntryP));
extern struct TypeT	       *entry_get_type
	PROTO_S ((EntryP));
extern EntryP			entry_get_non_local
	PROTO_S ((EntryP));
extern void			entry_set_mapping
	PROTO_S ((EntryP, NStringP));
extern NStringP			entry_get_mapping
	PROTO_S ((EntryP));
extern void			entry_iter
	PROTO_S ((EntryP, BoolT, void (*) (EntryP, GenericP), GenericP));
extern void			entry_not_traced
	PROTO_S ((EntryP));
extern BoolT			entry_is_traced
	PROTO_S ((EntryP));

/*--------------------------------------------------------------------------*/

#ifdef FS_FAST
#define entry_set_basic(e, b)  ((e)->u.basic = (b))
#define entry_set_rule(e, r)  ((e)->u.rule = (r))
#define entry_set_action(e, a)  ((e)->u.action = (a))
#define entry_set_type(e, t)  ((e)->u.type = (t))
#define entry_next(e) ((e)->next)
#define entry_next_ref(e) (&((e)->next))
#define entry_key(e) (&((e)->key))
#define entry_type(e) ((e)->type)
#define entry_change_type(e, t) ((e)->type = (t))
#define entry_is_basic(e) ((e)->type == ET_BASIC)
#define entry_is_action(e) ((e)->type == ET_ACTION)
#define entry_is_rule(e) ((e)->type == ET_RULE)
#define entry_is_type(e) ((e)->type == ET_TYPE)
#define entry_is_non_local(e) ((e)->type == ET_NON_LOCAL)
#define entry_get_basic(e) ((e)->u.basic)
#define entry_get_action(e) ((e)->u.action)
#define entry_get_rule(e) ((e)->u.rule)
#define entry_get_name(e) ((e)->name)
#define entry_get_type(e) ((e)->u.type)
#define entry_not_traced(e) ((e)->traced = FALSE)
#define entry_is_traced(e) ((e)->traced)
#endif /* defined (FS_FAST) */

#endif /* !defined (H_ENTRY) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
