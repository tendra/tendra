/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdlib.h>
#include <stdbool.h>

#include <shared/check.h>

#include <shared/xalloc.h>

#include "adt/instruction.h"

#include "adt.h"

static ActionT* action_create(void)
{
	ActionT* action = xmalloc_nof (ActionT, 1);
	ccode_init(&action->code); 
	typetuple_init(&action->inputs);
	typetuple_init(&action->outputs);
	action->defined=false;
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

TypeTupleT* action_get_inputs(ActionT* action)
{
	return &action->inputs;
}

TypeTupleT* action_get_outputs(ActionT* action)
{
	return &action->outputs;
}

CcodeT* action_get_code(ActionT* action)
{
	return &action->code;
}

void action_set_code(ActionT* action, CcodeT* code)
{
	ccode_assign(&action->code,code) ;
}

void action_set_define(ActionT* action)
{
	action->defined=true;
}

int action_is_defined(ActionT* action)
{
	return action->defined;
}

NStringT* entry_key(EntryT* entry) 
{
	return &entry->key;
}

int entry_is_type(EntryT* entry) 
{
  return entry->entry_kind==entry_type;
}

int entry_is_action (EntryT* entry) 
{
  return entry->entry_kind==entry_action;
}

int entry_is_localname(EntryT* entry) 
{
	return entry->entry_kind==entry_local_name;
}


static void entry_set_kind_type ( EntryT* entry)
{
	entry->entry_kind=entry_type;
}

static void entry_set_kind_action(EntryT* entry) 
{
	entry->entry_kind=entry_action;
}

static void entry_set_kind_local_name(EntryT* entry) 
{
	entry->entry_kind=entry_local_name;
}


ActionT* entry_get_action(EntryT* entry)
{
	/*TODO assert entry_is_action */
	return entry->u.action;
}

void entry_set_type(EntryT* entry, TypeT* type)
{
	/*TODO assert entry_is_type */
	entry->u.type = type;
}

void entry_set_action(EntryT* entry, ActionT* action)
{
	/*TODO assert entry_is_action */
	entry->u.action = action;
}



TypeT* entry_get_type(EntryT* entry)
{
	/*TODO assert entry_is_type */
	return entry->u.type;
}

TypeT* type_create(bool predefined) 
{
	TypeT* type = xmalloc_nof(TypeT,1);
	nstring_init(&(type->mapping));
	type->mapped = false;
	type->predefined = predefined;
	return type;
}

void type_map(TypeT* t, NStringT* mapping)
{
	nstring_assign(&t->mapping,mapping);
	t->mapped=true;
}


EntryT *table_get_entry(EntryT **table, NStringT* key)
{
	EntryT *entry;

	assert(table != NULL);

	for (entry = *table; entry != NULL; entry = entry->next) {
		if (nstring_equal(&entry->key, key)) {
			return entry;
		}
	}

	return NULL;
}

EntryT* table_get_type(EntryT **table, NStringT* key ) 
{
	EntryT *entry;

	assert(table != NULL);

	entry = table_get_entry(table, key);

	if (entry_is_type(entry)) {
		return entry;
	}

	return NULL;
}


static void table_add_entry(EntryT **table, EntryT *entry)
{
	assert(table != NULL);
	assert(entry != NULL);
	assert(entry->next == NULL);

	entry->next = *table;
	*table = entry;
}

EntryT* entry_create(NStringT* name) 
{
	EntryT* entry = xmalloc_nof(EntryT, 1);
	nstring_assign(entry_key(entry), name);
	entry->next = NULL;
	return entry;
}

EntryT* table_add_type(EntryT **table, NStringT* type_name, bool predefined) 
{
	EntryT* entry = entry_create(type_name);
	entry_set_kind_type(entry);
	entry_set_type(entry, type_create(predefined));
	table_add_entry(table, entry);
	return entry;
}

EntryT* table_add_action(EntryT **table, NStringT* name, TypeTupleT* inputs, TypeTupleT* outputs) 
{
	EntryT* entry = entry_create(name);
	entry_set_kind_action(entry);
	table_add_entry(table, entry);
	entry_set_action(entry, action_create());
	action_set_inputs(entry_get_action(entry),inputs) ;
	action_set_outputs(entry_get_action(entry),outputs) ;
	return entry;
}

EntryT* 
table_add_local_name(EntryT **table, NStringT* name) 
{
	EntryT* entry = entry_create(name);
	entry_set_kind_local_name(entry);
	table_add_entry(table, entry);
	return entry;
}



TypeTupleEntryT* typetupleentry_create(NStringT* str, EntryT* type, bool isref)
{
	TypeTupleEntryT* p = xmalloc_nof(TypeTupleEntryT, 1);
	nstring_assign(&(p->local_name), str);
	p->type=type;
	p->is_reference=isref;
	p->next = NULL;
	return p;
}

void typetupleentry_destroy(TypeTupleEntryT* p)
{
	if(p) {
		nstring_destroy(&(p->local_name));
	}
	 xfree(p);
}

void typetuple_init(TypeTupleT* ttlist) 
{
	ttlist->head = NULL ;
	ttlist->tail = &(ttlist->head) ;
	ttlist->length = 0;
}

TypeTupleEntryT* typetuple_name_is_in(TypeTupleT* tt, NStringT* id) 
{
	TypeTupleEntryT* it;
	for(it=tt->head; it!=NULL;it=it->next) {
		if(nstring_equal(&it->local_name,id))
			return it;
	}

	return NULL;
}


void typetuple_append(TypeTupleT* ttlist, TypeTupleEntryT* tt) 
{
	*(ttlist->tail) = tt ;
	ttlist->tail = &(tt->next) ;
	++ttlist->length;
}

void typetuple_assign(TypeTupleT* to, TypeTupleT* from)
{
	to->length=from->length;
	if((to->head=from->head)==NULL) 
		to->tail = &(to->head);
	else 
		to->tail = from->tail ;
}

int typetuple_length(TypeTupleT* tuple)
{
	return tuple->length;
}

int typetuple_match(TypeTupleT* t1, TypeTupleT* t2) 
{
	TypeTupleEntryT *p, *q;
	for(p=t1->head, q=t2->head; p!=NULL && q!=NULL; p=p->next, q=q->next) {
		if((p->type!=q->type) || (p->is_reference!=q->is_reference))
			return 0;
	}
	if(!p && !q)
		return 1;
	else
		return 0;
}


int typetuple_assign_names(TypeTupleT* to, TypeTupleT* from) 
{
	int allhavenames=1;
	TypeTupleEntryT *p, *q;
	for(p=from->head, q=to->head; p!=NULL && q!=NULL; p=p->next, q=q->next) {
		if(nstring_length(&(p->local_name))==0)
			allhavenames=0;
		else {
			nstring_assign(&q->local_name,&p->local_name);
			nstring_init(&p->local_name);
		}
	}
	/* assert(!(p||q))*/
	return allhavenames;
}

void typetuple_destroy(TypeTupleT* tuple)
{
	TypeTupleEntryT* p;
	for(p=tuple->head; p!=NULL; p=p->next) {
		typetupleentry_destroy(p);
	}
}


static int
cmp_tuples_names(void const* p, void const* q)
{
	switch(nstring_compare((NStringT*)p, (NStringT*) q)) EXHAUSTIVE {
	case CMP_LT:
		return -1;
	case CMP_EQ:
		return 0;
	case CMP_GT:
		return 1;
	}
	UNREACHED;
}
/*
  This helper function returns true if all names in params and results
  are unique. It returns false otherewise.
*/
int typetuple_unique_names(TypeTupleT* params, TypeTupleT* results) 
{
	int total_length=typetuple_length(params)+typetuple_length(results);
	NStringT** tab = xmalloc_nof(NStringT*,typetuple_length(params)+typetuple_length(results));
	TypeTupleEntryT* p;
	int i = 0;
	for(p=params->head;p!=NULL;p=p->next, ++i) {
		tab[i]=&p->local_name;
	}
	for(p=results->head;p!=NULL;p=p->next, ++i) {
		tab[i]=&p->local_name;
	}
	qsort(tab, total_length, sizeof(NStringT**), &cmp_tuples_names);
	for(i=0;i<total_length-1;++i) {
		if(nstring_equal(tab[i],tab[i+1])) {
			xfree(tab);
			return false;
		}
	}
	xfree(tab);
	return true;
}

void nametrans_init(NameTransT* p, unsigned int s)
{
	p->tab = s == 0 ? NULL : xmalloc_nof(NameTransT,s);
	p->size=0;
	p->capacity=s;
}

void nametrans_destroy(NameTransT* p)
{
	xfree(p->tab);
}

static int nametrans_cmp(const void* p, const void* q) 
{
	switch(nstring_compare(&(((NameTransEntryT*)p)->from),&(((NameTransEntryT*)q)->from))) EXHAUSTIVE {
	case CMP_LT:
		return -1;
	case CMP_EQ:
		return 0;
	case CMP_GT:
		return 1;
	}
	UNREACHED;
}

void nametrans_sort(NameTransT* p)
{
	qsort(p->tab,p->size,sizeof(NameTransEntryT),&nametrans_cmp); 
}

static void nametrans_append(NameTransT* tr, NStringT* from, arg* to)
{
	/* TODO when debugging : Checking tr->size<tr->capacity */
	nstring_assign(&(tr->tab[tr->size].from), from);
	tr->tab[tr->size].to = to;
	++(tr->size);
}

void nametrans_append_tuple(NameTransT* tr, TypeTupleT* tuple, args_list* l)
{
	TypeTupleEntryT* p;
	arg* q;
	for(p=tuple->head,q=l->head;p!=NULL&&q!=NULL;p=p->next,q=q->next) {
		nametrans_append(tr, &p->local_name, q);
	}
	/*TODO  assert(!p&&!q) */
}

arg* nametrans_translate(NameTransT* trans, NStringT* key)
{
	int i=0;
	int j=trans->size-1;
	/* TODO assert(i<j) */
	int mid = (i+j)/2;
	while(i<j) {
		switch(nstring_compare(&trans->tab[mid].from,key)) {
		case CMP_LT:
			i=mid+1;
			mid=(i+j)/2;
			break;
		case CMP_EQ:
			return trans->tab[mid].to;
			break;
		case CMP_GT:
			j=mid-1;
			mid=(i+j+1)/2;
			break;
		}
	}
	if(nstring_compare(&trans->tab[i].from,key)==CMP_EQ)
		return trans->tab[i].to;
	else
		return NULL;
}
