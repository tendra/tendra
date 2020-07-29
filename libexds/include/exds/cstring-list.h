/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * cstring-list.h - String list ADT.
 *
 * This file specifies the interface to a string list facility.  This
 * particular facility allows lists of cstrings (defined in the files
 * "cstring.[ch]") to be created.
 */

#ifndef H_CSTRING_LIST
#define H_CSTRING_LIST

#include <exds/common.h>


/*
 * This is the cstring list entry type. Its representation is private.
 */
typedef struct CStringListEntryT CStringListEntryT;
struct CStringListEntryT {
	CStringListEntryT *next;
	const char *string;
};

/*
 * This is the cstring list type. Its representation is private.
 */
typedef struct CStringListT CStringListT;
struct CStringListT {
	CStringListEntryT *head;
	CStringListEntryT **tail;
};

/*
 * This function initialises the specified cstring list to be an empty list.
 */
void
cstring_list_init(CStringListT *);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function appends the specified cstring onto the specified list.
 */
void
cstring_list_append(CStringListT *, const char *);

bool
cstring_list_contains(CStringListT *, const char *);

/*
 * This function returns a pointer to the first entry in the specified list.
 */
CStringListEntryT *
cstring_list_head(CStringListT *);

/*
 * This function returns a pointer to the cstring stored in the specified
 * list entry.
 */
const char *
cstring_list_entry_string(CStringListEntryT *);

/*
 * This function deallocates the specified list entry (without deallocating
 * the string - this must be done by the calling function) and returns a
 * pointer to the next entry in the list.  Once this function has been called,
 * the state of the list that the entry is a member of is undefined.  It is
 * only useful for deallocating the entire list in a loop.
 */
CStringListEntryT *
cstring_list_entry_deallocate(CStringListEntryT *);

#endif /* !defined (H_CSTRING_LIST) */
