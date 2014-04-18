/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_ADT_H
#define LEXI_ADT_H

#include <stdbool.h>
#include "exds/common.h"
#include "exds/dstring.h"
#include "ccode.h"

struct ActionT;
struct TypeT;

struct arg_tag;
struct args_list_tag;

typedef struct EntryT {
	NStringT key;
	enum { entry_action, entry_type, entry_local_name } entry_kind;
	union {
	      struct ActionT *action;
	      struct TypeT *type;
	} u;
	struct EntryT *next;
} EntryT;

typedef struct TypeT {
	bool mapped;
	bool predefined;
	NStringT mapping;
} TypeT;

typedef struct TypeTupleEntryT {
	EntryT *type;
	NStringT local_name; /* The type NSTringT* will probably not be the final type */
	bool is_reference;
	struct TypeTupleEntryT *next;
} TypeTupleEntryT;

typedef struct TypeTupleT {
	TypeTupleEntryT *head;
	TypeTupleEntryT **tail;
	unsigned int length;
} TypeTupleT;

typedef struct NameTransEntryT {
	NStringT from;
	struct arg_tag *to;
} NameTransEntryT;

typedef struct NameTransT {
	NameTransEntryT *tab;
	unsigned int size;
	unsigned int capacity;
} NameTransT;

typedef struct ActionT {
	struct TypeTupleT inputs;
	struct TypeTupleT outputs;
	CcodeT code;
	BoolT defined;
} ActionT;


TypeTupleT *action_get_inputs(ActionT *);
TypeTupleT *action_get_outputs(ActionT *);
CcodeT *action_get_code(ActionT *);
void action_set_code(ActionT *, CcodeT *);
int action_is_defined(ActionT *);
void action_set_define(ActionT *);

EntryT *entry_create(NStringT *);
int entry_is_type(EntryT *);
int entry_is_action(EntryT *);
int entry_is_localname(EntryT *);
NStringT *entry_key(EntryT *);
void entry_set_type(EntryT *, TypeT *);
void entry_set_action(EntryT * , ActionT *);
TypeT *entry_get_type(EntryT *);
ActionT *entry_get_action(EntryT *);

TypeT *type_create(bool);
void type_map(TypeT *, NStringT *);

EntryT *table_get_entry(EntryT **, NStringT *);
EntryT *table_add_local_name(EntryT **, NStringT *);
EntryT *table_get_type(EntryT **, NStringT *);
EntryT *table_add_type(EntryT **, NStringT *, bool);
EntryT *table_add_action(EntryT **, NStringT *, TypeTupleT *, TypeTupleT *);

TypeTupleEntryT *typetupleentry_create(NStringT *, EntryT *, bool);
void typetupleentry_destroy(TypeTupleEntryT *);

void typetuple_init(TypeTupleT *);
TypeTupleEntryT *typetuple_name_is_in(TypeTupleT *, NStringT *);
void typetuple_append(TypeTupleT *, TypeTupleEntryT *);
void typetuple_assign(TypeTupleT *, TypeTupleT *);
int typetuple_length(TypeTupleT *);
int typetuple_assign_names(TypeTupleT *, TypeTupleT *);
int typetuple_match(TypeTupleT *, TypeTupleT *);
void typetuple_destroy(TypeTupleT *);

void nametrans_init(NameTransT *, unsigned int);
void nametrans_destroy(NameTransT *);
void nametrans_sort(NameTransT *);
void nametrans_append_tuple(NameTransT *, TypeTupleT *, struct args_list_tag *);
struct arg_tag *nametrans_translate(NameTransT *, NStringT *);

#endif

