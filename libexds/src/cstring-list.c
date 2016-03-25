/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * cstring-list.c - String list ADT.
 *
 * This file implements the string list facility specified in the file
 * "cstring-list.h".  See that file for more details.
 */

/*
 * TODO two thoughts: 1. linked lists are a recursive type; this implementation
 * is not. 2. Lists are common and could be centralised.
 */

#include <stddef.h>
#include <string.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/string.h>

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/cstring.h>
#include <exds/dalloc.h>
#include <exds/cstring-list.h>

void
cstring_list_init(CStringListT *list)
{
	list->head = NULL;
	list->tail = &list->head;
}

void
cstring_list_append(CStringListT *list, const char *string)
{
	CStringListEntryT *entry = ALLOCATE(CStringListEntryT);

	entry->next   = NULL;
	entry->string = string;
	*list->tail   = entry;
	list->tail    = &entry->next;
}

bool
cstring_list_contains(CStringListT *list, const char *string)
{
	CStringListEntryT *entry = list->head;

	while (entry != NULL) {
		if (streq(string, entry->string)) {
			return true;
		}
		entry = entry->next;
	}

	return false;
}

CStringListEntryT *
cstring_list_head(CStringListT *list)
{
	return list->head;
}

const char *
cstring_list_entry_string(CStringListEntryT *entry)
{
	return entry->string;
}

CStringListEntryT *
cstring_list_entry_deallocate(CStringListEntryT *entry)
{
	CStringListEntryT *next = entry->next;

	DEALLOCATE(entry);
	return next;
}
