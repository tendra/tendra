/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * entry.h - Identifier table entry ADT.
 *
 * See the file "entry.c" for more information.
 */

#ifndef H_ENTRY
#define H_ENTRY

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include <exds/dstring.h>
#include <exds/ostream.h>
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

typedef enum {
    ET_TYPE,
    ET_BASIC,
    ET_RULE,
    ET_ACTION,
    ET_NAME,
    ET_RENAME,
    ET_PREDICATE,
    ET_NON_LOCAL
} EntryTypeT;

/*
 * An EntryT is a structure designed to go in a hash map that contains
 * one of the following: a rule, a type, an action, a terminal, a non-local,
 * a local or base name, or a rename instruction.
 *
 * In the two latter cases the EntryT contains almost no information in itself.
 */
typedef struct EntryT {
	/*
	 * A pointer to the next EntryT in the table. It is NULL if there is no
	 * next entry. By "next", we mean that if two or more EntryT entries share
	 * the same hash in a TableT, then they are stored as a singly linked list,
	 * so it is next in the sense of the hash table.
	 */
    struct EntryT	       *next;

	/*
	 * Either a string (the name of a rule, action, type or terminal) or a
	 * number (the number of an anonymous rule e.g.).  Rules may be scoped:
	 * .key begins with "scope::". Non-locals must be scoped.
	 */
    KeyT			key;

	/*
	 * A boolean that is set to true if this entry is mapped in the %maps%
	 * section of the .act file. It is only valid for types, terminals and
	 * rules.
	 */
    bool			mapped;

	/*
	 * The value of the C identifier to which the entry must be mapped in the
	 * outputted code. It corresponds to the value found in the %maps%
	 * section of the .act file.
	 */
    NStringT			mapping;

	/*
	 * The type to which the pointer stored in .u refers.
	 *
	 * ET_TYPE, ET_BASIC, ET_RULE, ET_ACTION and ET_NON_LOCAL are self-
	 * explanatory. ET_PREDICATE is an invalid value for an EntryT.
	 *
	 * ET_RENAME indicates an identity in the .sid file, e.g. (a, b) = (c, d)
	 * See the ItemT type for more details.
	 *
	 * ET_NAME only indicates a local name that has been declared somewhere
	 * with .key containing the name of the local name. They may indicate
	 * something else: a scoped rule, scoped action or scoped non-local (the
	 * latters are always scoped) have their base name (without the scope)
	 * declared as an ET_NAME in table. Whether the local name is used in a
	 * rule or in an identity is stored in the rule itself (more exactly in
	 * each alternate of the rule). As we can see an EntryT with values
	 * ET_NAME or ET_RENAME contain very few information in themselves:
	 * nothing for ET_RENAME, only the name of the local variable (or of a
	 * rule, action, non-local base name) in ET_NAME.
	 *
	 * A non-local is an EntryT whose type is ET_NON_LOCAL and whose
	 * member u is also an EntryT*: the target of this pointer is a
	 * type giving the type of the non-local. The key member is the
	 * name of the non-local but also contains its scope. IE,
	 * non-locals are accessible to all rules contained in the rule
	 * for which the non-local is defined.  The scope is indicated in
	 * the key string by
	 * outer-enclosing-rule::inner-enclosing-rule::name-of-non-local.
	 */
    EntryTypeT			type;

	/*
	 * This field serves to iterate on entries. It marks the entries from
	 * which we have already decided to iterate on the child to avoid infinite
	 * recursion. For example, beginning with the starting points (entry
	 * points) of the grammar, we can iterate on all the called rules and
	 * verify that there are no unused rule by checking that all rules
 	 * have been traced. This is done by grammar_check_complete() in
	 * grammar.h.
	 *
	 * Just after SID has parsed the .sid file, all .traced entries are set
	 * to false. To use .traced, you must first untrace everything. This is
	 * done with the function table_untrace(). To see how traced can be used,
	 * just grep for that.
	 */
    bool			traced;

	/*
	 * A pointer as indicated by the .type field.
	 */
    union {
	struct BasicT	       *basic;
	struct RuleT	       *rule;
	struct ActionT	       *action;
	struct TypeT	       *type;
	struct EntryT	       *non_local;
    } u;

	/*
	 * TODO: I haven't succeeded yet in understanding what NameT is used for,
	 * but it is only used in c-code.c and types.c. See name.h.
	 */
    struct NameT	       *name;
} EntryT;

EntryT *		entry_create_from_string(NStringT *, unsigned,
						 EntryTypeT);
EntryT *		entry_create_from_number(unsigned, EntryTypeT, bool,
						 EntryT *);
void		entry_set_basic(EntryT *, struct BasicT *);
void		entry_set_rule(EntryT *, struct RuleT *);
void		entry_set_action(EntryT *, struct ActionT *);
void		entry_set_type(EntryT *, struct TypeT *);
void		entry_set_non_local(EntryT *, EntryT *);
EntryT *		entry_next(EntryT *);
EntryT *	       *entry_next_ref(EntryT *);
KeyT *		entry_key(EntryT *);
EntryTypeT	entry_type(EntryT *);
void		entry_change_type(EntryT *, EntryTypeT);
bool		entry_is_basic(EntryT *);
bool		entry_is_action(EntryT *);
bool		entry_is_rule(EntryT *);
bool		entry_is_type(EntryT *);
bool		entry_is_non_local(EntryT *);
struct BasicT   *entry_get_basic(EntryT *);
struct ActionT  *entry_get_action(EntryT *);
struct RuleT    *entry_get_rule(EntryT *);
struct NameT    *entry_get_name(EntryT *);
struct TypeT    *entry_get_type(EntryT *);
EntryT *		entry_get_non_local(EntryT *);
void		entry_set_mapping(EntryT *, NStringT *);
NStringT *		entry_get_mapping(EntryT *);
void		entry_iter(EntryT *, bool, void(*)(EntryT *, void *),
				   void *);
void		entry_not_traced(EntryT *);
bool		entry_is_traced(EntryT *);

#endif /* !defined (H_ENTRY) */
