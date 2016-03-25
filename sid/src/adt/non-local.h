/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * non-local.h - Non local name ADT.
 *
 * See the file "non-local.c" for more information.
 */

#ifndef H_NON_LOCAL
#define H_NON_LOCAL

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include "entry.h"
#include <exds/ostream.h>

typedef struct NonLocalEntryT {
    struct NonLocalEntryT      *next;
    EntryT *			name;
    EntryT *			type;
    EntryT *			initialiser;
} NonLocalEntryT;

typedef struct NonLocalListT {
    NonLocalEntryT *		head;
    NonLocalEntryT *	       *tail;
} NonLocalListT;

void		non_local_list_init(NonLocalListT *);
NonLocalEntryT *	non_local_list_add(NonLocalListT *, EntryT *, EntryT *);
bool		non_local_list_is_empty(NonLocalListT *);
void		non_local_list_iter_for_table(NonLocalListT *,
						      void(*)(EntryT *, void *),
						      void *);
void		non_local_list_destroy(NonLocalListT *);

void		write_non_locals(OStreamT *, NonLocalListT *);

void		non_local_entry_set_initialiser(NonLocalEntryT *, EntryT *);
EntryT *		non_local_entry_get_initialiser(NonLocalEntryT *);
EntryT *		non_local_entry_get_type(NonLocalEntryT *);
EntryT *		non_local_entry_get_name(NonLocalEntryT *);

#endif /* !defined (H_NON_LOCAL) */
