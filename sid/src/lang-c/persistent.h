/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* persistent.h Persistent variables
 *
 * 
 */

#ifndef H_PERSISTENT 
#define H_PERSISTENT

#include "../adt/entry.h" 
#include <exds/dstring.h>

typedef struct PersistentT_tag {
	/*
	 * TODO: its name out to be a NameT(?) inside an EntryT. can we check for
	 * clashes against other arguments? using a persistent ought to then say
	 * @persistent inside actions. if it's not used, output a cast to (void) to
	 * quell warnings. Likewise the type ought to be a TypeT inside an EntryT.
	 */
	NStringT ctype ;
	NStringT name ;
	struct PersistentT_tag* next ;
} PersistentT ; 

typedef struct PersistentListT_tag {
	PersistentT* head ;
	PersistentT** tail ;
} PersistentListT ;

PersistentT* persistent_create (NStringT* name, NStringT* ctype) ;
void persistent_list_init (PersistentListT* list) ;
void persistent_list_append (PersistentListT* list, PersistentT* persistent) ;
PersistentT* persistent_list_find (PersistentListT* list, NStringT* name) ;
#endif
