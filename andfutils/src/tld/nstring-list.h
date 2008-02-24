/*
 * Copyright (c) 2002-2006 The TenDRA Project <http://www.tendra.org/>.
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
/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
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
 ** Type:	NStringListEntryT *
 ** Repr:	<private>
 *
 * This is the nstring list entry type.
 *
 ** Type:	NStringListT
 ** Type:	NStringListT *
 ** Repr:	<private>
 *
 * This is the nstring list type.
 *
 ***=== FUNCTIONS ============================================================
 *
 ** Function:	void nstring_list_init(NStringListT *list)
 ** Exceptions:
 *
 * This function initialises the specified nstring list to be an empty list.
 *
 ** Function:	void nstring_list_append(NStringListT *list, NStringT *nstring)
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function appends the specified nstring onto the specified list.
 *
 ** Function:	NStringListEntryT *nstring_list_head(NStringListT *list)
 ** Exceptions:
 *
 * This function returns a pointer to the first entry in the specified list.
 *
 ** Function:	NStringT *nstring_list_entry_string(NStringListEntryT *entry)
 ** Exceptions:
 *
 * This function returns a pointer to the nstring stored in the specified
 * list entry.
 *
 ** Function:	NStringListEntryT *
 *		    nstring_list_entry_deallocate(NStringListEntryT *entry)
 ** Exceptions:
 *
 * This function deallocates the specified list entry (without deallocating
 * the string - this must be done by the calling function) and returns a
 * pointer to the next entry in the list.  Once this function has been called,
 * the state of the list that the entry is a member of is undefined.  It is
 * only useful for deallocating the entire list in a loop.
 *
 **** Change log:
 * $Log: nstring-list.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:17  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:44:49  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:05:53  smf
 * Initial import of library shared files.
 *
**/

/****************************************************************************/

#ifndef H_NSTRING_LIST
#define H_NSTRING_LIST

#include "os-interface.h"
#include "dalloc.h"
#include "dstring.h"

/*--------------------------------------------------------------------------*/

typedef struct NStringListEntryT {
    struct NStringListEntryT   *next;
    NStringT			string;
} NStringListEntryT;

typedef struct NStringListT {
    NStringListEntryT *	head;
    NStringListEntryT *       *tail;
} NStringListT;

/*--------------------------------------------------------------------------*/

extern void			nstring_list_init
(NStringListT *);
extern void			nstring_list_append
(NStringListT *, NStringT *);
extern NStringListEntryT *nstring_list_head
(NStringListT *);
extern NStringT *		nstring_list_entry_string
(NStringListEntryT *);
extern NStringListEntryT *nstring_list_entry_deallocate
(NStringListEntryT *);

#endif /* !defined (H_NSTRING_LIST) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../generated")
 * end:
**/
