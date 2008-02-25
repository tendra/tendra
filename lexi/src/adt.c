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

#include "adt.h"
#include "xalloc.h"
#include <stdlib.h>

static ActionT* action_create(void)
{
	ActionT* action = xmalloc_nof (ActionT, 1);
	return action ;
}

static void action_set_inputs(ActionT* action, TypeTupleT* tuple)
{
	typetuple_assign(&action->inputs,tuple) ;
}

static void action_set_outputs(ActionT* action, TypeTupleT* tuple)
{
	typetuple_assign(&action->outputs,tuple) ;
}

NStringT* entry_key(EntryT* entry) 
{
	return &entry->key;
}

int entry_is_type(EntryT* entry) 
{
	if(entry->entry_kind==entry_type)
		return 1;
	else
		return 0;
}

int entry_is_action (EntryT* entry) 
{
	if(entry->entry_kind==entry_action)
		return 1;
	else
		return 0;
}


static void entry_set_kind_type ( EntryT* entry)
{
	entry->entry_kind=entry_type;
}

static void entry_set_kind_action(EntryT* entry) 
{
	entry->entry_kind=entry_action;
}


static ActionT* entry_get_action(EntryT* entry)
{
	/*TODO assert entry_is_action */
	return entry->u.action;
}


void table_init(TableT table) 
{
	int i = 0 ;
	for( i=0 ; i < TABLE_SIZE ; ++i)
		table[i] = NULL ;
}


EntryT* table_get_entry(TableT table, NStringT* key ) 
{
	unsigned int hash = nstring_hash_value(key)%TABLE_SIZE ;
	EntryT* entry ; 

	for ( entry = table[hash] ; entry != NULL ; entry = entry->next) 
		if(nstring_equal(&entry->key,key))
			return entry ;
        return NULL ;
}

EntryT* table_get_type(TableT table, NStringT* key ) 
{
  EntryT* entry = table_get_entry(table, key);

  if(entry_is_type(entry))
    return entry;
  return NULL ;
}


static void table_add_entry(TableT table, EntryT* entry)
{
	unsigned int hash=nstring_hash_value(entry_key(entry))%TABLE_SIZE;
	entry->next=table[hash];
	table[hash]=entry;
}

EntryT* entry_create(NStringT* name) 
{
	EntryT* entry = xmalloc_nof(EntryT, 1);
	nstring_assign(entry_key(entry), name);
	return entry;
}

static TypeT* type_create(void)
{
	TypeT* type = xmalloc_nof(TypeT,1);
	return type;
}

EntryT* table_add_type(TableT table, NStringT* type_name) 
{
	EntryT* entry = entry_create(type_name);
	entry_set_kind_type(entry);
	table_add_entry(table, entry);
	return entry;
}

EntryT* table_add_action(TableT table, NStringT* name, TypeTupleT* inputs, TypeTupleT* outputs) 
{
	EntryT* entry = entry_create(name);
	entry_set_kind_action(entry);
	table_add_entry(table, entry);
	action_set_inputs(entry_get_action(entry),inputs) ;
	action_set_outputs(entry_get_action(entry),inputs) ;
	return entry;
}


TypeTupleEntryT* typetupleentry_create(NStringT* str, EntryT* type)
{
	TypeTupleEntryT* p; /*= using xmalloc_nof*/
	nstring_assign((p->local_name), str);
	p->type=type;
	return p;
}


void typetuple_init(TypeTupleT* ttlist) 
{
	ttlist->head = NULL ;
	ttlist->tail = &(ttlist->head) ;
}

void typetuple_append(TypeTupleT* ttlist, TypeTupleEntryT* tt) 
{
	*(ttlist->tail) = tt ;
	ttlist->tail = &(tt->next) ;
}

void typetuple_assign(TypeTupleT* to, TypeTupleT* from)
{
	if((to->head=from->head)==NULL) 
		to->tail = &(to->head);
	else 
		to->tail= from->tail ;
}
