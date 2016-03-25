/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * entry-list.h - Identifier table entry list ADT.
 *
 * See the file "entry-list.h" for more information.
 */

#ifndef H_ENTRY_LIST
#define H_ENTRY_LIST

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include "entry.h"
#include <exds/ostream.h>

typedef struct EntryListEntryT {
    struct EntryListEntryT     *next;
    EntryT *			entry;
} EntryListEntryT;

typedef struct EntryListT {
    EntryListEntryT *		head;
    EntryListEntryT *	       *tail;
} EntryListT;

typedef struct SaveListT {
    struct EntryListEntryT    **last_ref;
} SaveListT;

void	entry_list_init(EntryListT *);
void	entry_list_copy(EntryListT *, EntryListT *);
void	entry_list_add(EntryListT *, EntryT *);
void	entry_list_add_if_missing(EntryListT *, EntryT *);
bool	entry_list_contains(EntryListT *, EntryT *);
bool	entry_list_includes(EntryListT *, EntryListT *);
void	entry_list_intersection(EntryListT *, EntryListT *, EntryListT *);
void	entry_list_unlink_used(EntryListT *, EntryListT *);
void	entry_list_append(EntryListT *, EntryListT *);
bool	entry_list_is_empty(EntryListT *);
void	entry_list_save_state(EntryListT *, SaveListT *);
void	entry_list_restore_state(EntryListT *, SaveListT *);
void	entry_list_iter(EntryListT *, void(*)(EntryT *, void *),
				void *);
void	entry_list_iter_table(EntryListT *, bool,
				      void(*)(EntryT *, void *), void *);
void	entry_list_destroy(EntryListT *);

void	write_entry_list(OStreamT *, EntryListT *);

#endif /* !defined (H_ENTRY_LIST) */
