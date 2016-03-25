/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * nstring-list.c - String list ADT.
 *
 * This file implements the string list facility specified in the file
 * "nstring-list.h".  See that file for more details.
 */

#include <stddef.h>

#include <shared/bool.h>

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include <exds/ostream.h>
#include <exds/dstring.h>
#include <exds/nstring-list.h>

struct NStringListEntryT {
	NStringListEntryT *next;
	NStringT          string;
};

void
nstring_list_init(NStringListT *list)
{
	list->head = NULL;
	list->tail = &list->head;
}

void
nstring_list_append(NStringListT *list, NStringT *string)
{
	NStringListEntryT *entry = ALLOCATE(NStringListEntryT);

	entry->next   = NULL;
	nstring_assign(&entry->string, string);
	*list->tail   = entry;
	list->tail    = &entry->next;
}

NStringListEntryT *
nstring_list_head(NStringListT *list)
{
	return list->head;
}

NStringT *
nstring_list_entry_string(NStringListEntryT *entry)
{
	return &entry->string;
}

NStringListEntryT *
nstring_list_entry_deallocate(NStringListEntryT *entry)
{
	NStringListEntryT *next = entry->next;

	DEALLOCATE(entry);
	return next;
}
