/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


/**** nstring-list.h --- String list ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 ***=== INTRODUCTION =========================================================
 *
 * This file specifies the interface to a string list facility.  This
 * particular facility allows lists of nstrings (defined in the files
 * "dstring.[ch]") to be created.
 *
 ***=== TYPES ================================================================
 *
 ** Type:	NStringListEntryT
 ** Type:	NStringListEntryP
 ** Repr:	<private>
 *
 * This is the nstring list entry type.
 *
 ** Type:	NStringListT
 ** Type:	NStringListP
 ** Repr:	<private>
 *
 * This is the nstring list type.
 *
 ***=== FUNCTIONS ============================================================
 *
 ** Function:	void			nstring_list_init(NStringListP list)
 ** Exceptions:
 *
 * This function initialises the specified nstring list to be an empty list.
 *
 ** Function:	void			nstring_list_append(NStringListP list,
 *					    NStringP nstring)
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function appends the specified nstring onto the specified list.
 *
 ** Function:	NStringListEntryP	nstring_list_head(NStringListP list)
 ** Exceptions:
 *
 * This function returns a pointer to the first entry in the specified list.
 *
 ** Function:	NStringP		nstring_list_entry_string(
 *					    NStringListEntryP entry)
 ** Exceptions:
 *
 * This function returns a pointer to the nstring stored in the specified
 * list entry.
 *
 ** Function:	NStringListEntryP	nstring_list_entry_deallocate(
 *					    NStringListEntryP entry)
 ** Exceptions:
 *
 * This function deallocates the specified list entry (without deallocating
 * the string - this must be done by the calling function) and returns a
 * pointer to the next entry in the list.  Once this function has been called,
 * the state of the list that the entry is a member of is undefined.  It is
 * only useful for deallocating the entire list in a loop.
 *
 **** Change log:*/

/****************************************************************************/

#ifndef H_NSTRING_LIST
#define H_NSTRING_LIST

#include "config.h"
#include "dalloc.h"
#include "dstring.h"

/*--------------------------------------------------------------------------*/

typedef struct NStringListEntryT {
    struct NStringListEntryT   *next;
    NStringT			string;
} NStringListEntryT, *NStringListEntryP;

typedef struct NStringListT {
    NStringListEntryP		head;
    NStringListEntryP	       *tail;
} NStringListT, *NStringListP;

/*--------------------------------------------------------------------------*/

extern void			nstring_list_init(NStringListP);
extern void			nstring_list_append(NStringListP, NStringP);
extern NStringListEntryP	nstring_list_head(NStringListP);
extern NStringP			nstring_list_entry_string(NStringListEntryP);
extern NStringListEntryP	nstring_list_entry_deallocate(NStringListEntryP);

#endif /* !defined (H_NSTRING_LIST) */
