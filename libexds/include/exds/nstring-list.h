/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * nstring-list.h - String list ADT.
 *
 * This file specifies the interface to a string list facility.  This
 * particular facility allows lists of nstrings (defined in the files
 * "dstring.[ch]") to be created.
 */

#ifndef H_NSTRING_LIST
#define H_NSTRING_LIST

#include <exds/dstring.h>


/*
 * This is the nstring list entry type. Its representation is private.
 */
typedef struct NStringListEntryT NStringListEntryT;

/*
 * This is the nstring list type. Its representation is private.
 */
typedef struct NStringListT NStringListT;
struct NStringListT {
	NStringListEntryT *head;
	NStringListEntryT **tail;
};

/*
 * This function initialises the specified nstring list to be an empty list.
 */
void
nstring_list_init (NStringListT *);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function appends the specified nstring onto the specified list.
 */
void
nstring_list_append (NStringListT *, NStringT *);

/*
 * This function returns a pointer to the first entry in the specified list.
 */
NStringListEntryT *
nstring_list_head (NStringListT *);

/*
 * This function returns a pointer to the nstring stored in the specified
 * list entry.
 */
NStringT *
nstring_list_entry_string (NStringListEntryT *);

/*
 * This function deallocates the specified list entry (without deallocating
 * the string - this must be done by the calling function) and returns a
 * pointer to the next entry in the list.  Once this function has been called,
 * the state of the list that the entry is a member of is undefined.  It is
 * only useful for deallocating the entire list in a loop.
 */
NStringListEntryT *
nstring_list_entry_deallocate (NStringListEntryT *);

#endif /* !defined (H_NSTRING_LIST) */
