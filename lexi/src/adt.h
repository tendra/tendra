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

#ifndef H_LEXI_ADT_INCLUDED
#define H_LEXI_ADT_INCLUDED

#include <stdbool.h>
#include "exds/common.h"
#include "exds/dstring.h"
#include "ccode.h"

#define TABLE_SIZE 256 

struct ActionT ;
struct TypeT ;

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

typedef struct ActionT {
	struct TypeTupleT inputs ;
	struct TypeTupleT outputs ;
	CcodeT code; 
	BoolT defined;
} ActionT;


typedef EntryT* TableT[TABLE_SIZE];

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

extern void table_init(TableT);
extern EntryT* table_get_entry(TableT, NStringT*) ;
extern EntryT* table_add_local_name(TableT, NStringT*) ;
extern EntryT* table_get_type(TableT, NStringT*) ;
extern EntryT* table_add_type(TableT, NStringT*, bool) ;
extern EntryT* table_add_action(TableT, NStringT*, TypeTupleT*, TypeTupleT*) ;

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

#endif
