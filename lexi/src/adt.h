/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef H_LEXI_ADT_INCLUDED
#define H_LEXI_ADT_INCLUDED

#include <stdbool.h>
#include "exds/common.h"
#include "exds/dstring.h"
#include "ccode.h"

struct ActionT ;
struct TypeT ;

struct arg_tag;
struct args_list_tag;

typedef struct EntryT {
	NStringT key ;
	enum { entry_action, entry_type, entry_local_name } entry_kind ;
	union {
	      struct ActionT* action ;
	      struct TypeT* type ;
	} u;
	struct EntryT* next ;
} EntryT;

typedef struct TypeT {
	bool mapped;
	bool predefined;
	NStringT mapping;
} TypeT;

typedef struct TypeTupleEntryT {
	EntryT*  type;
	NStringT  local_name; /*The type NSTringT* will probably not be the final type */
	bool is_reference;
	struct TypeTupleEntryT* next;
} TypeTupleEntryT;

typedef struct TypeTupleT {
	TypeTupleEntryT*  head;
	TypeTupleEntryT** tail;
	unsigned int length;
} TypeTupleT;

typedef struct NameTransEntryT {
	NStringT from;
	struct arg_tag* to;
} NameTransEntryT;

typedef struct NameTransT {
	NameTransEntryT* tab;
	unsigned int size;
	unsigned int capacity;
} NameTransT;

typedef struct ActionT {
	struct TypeTupleT inputs ;
	struct TypeTupleT outputs ;
	CcodeT code; 
	BoolT defined;
} ActionT;


extern TypeTupleT* action_get_inputs(ActionT*);
extern TypeTupleT* action_get_outputs(ActionT*);
extern CcodeT* action_get_code(ActionT*);
extern void action_set_code(ActionT*, CcodeT*);
extern int action_is_defined(ActionT*);
extern void action_set_define(ActionT*);

extern EntryT* entry_create(NStringT*) ;
extern int entry_is_type(EntryT*) ;
extern int entry_is_action(EntryT*) ;
extern int entry_is_localname(EntryT*) ;
extern NStringT* entry_key(EntryT*) ;
extern void entry_set_type(EntryT*, TypeT*) ;
extern void entry_set_action(EntryT* , ActionT*) ;
extern TypeT* entry_get_type(EntryT*) ;
extern ActionT* entry_get_action(EntryT*) ;

extern TypeT* type_create(bool);
extern void type_map(TypeT*, NStringT*);

extern EntryT* table_get_entry(EntryT **, NStringT*) ;
extern EntryT* table_add_local_name(EntryT **, NStringT*) ;
extern EntryT* table_get_type(EntryT **, NStringT*) ;
extern EntryT* table_add_type(EntryT **, NStringT*, bool) ;
extern EntryT* table_add_action(EntryT **, NStringT*, TypeTupleT*, TypeTupleT*) ;

extern TypeTupleEntryT* typetupleentry_create(NStringT*, EntryT*, bool);
extern void typetupleentry_destroy(TypeTupleEntryT*);

extern void typetuple_init(TypeTupleT*);
extern TypeTupleEntryT* typetuple_name_is_in(TypeTupleT*, NStringT*);
extern void typetuple_append(TypeTupleT*, TypeTupleEntryT*);
extern void typetuple_assign(TypeTupleT*, TypeTupleT*);
extern int typetuple_length(TypeTupleT*);
extern int typetuple_assign_names(TypeTupleT*, TypeTupleT*);
extern int typetuple_match(TypeTupleT*, TypeTupleT*);
extern void typetuple_destroy(TypeTupleT*);

extern void nametrans_init(NameTransT*, unsigned int);
extern void nametrans_destroy(NameTransT*);
extern void nametrans_sort(NameTransT*);
extern void nametrans_append_tuple(NameTransT*, TypeTupleT*, struct args_list_tag*);
extern struct arg_tag* nametrans_translate(NameTransT*, NStringT*);

#endif
