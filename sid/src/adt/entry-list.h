/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
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
BoolT	entry_list_contains(EntryListT *, EntryT *);
BoolT	entry_list_includes(EntryListT *, EntryListT *);
void	entry_list_intersection(EntryListT *, EntryListT *, EntryListT *);
void	entry_list_unlink_used(EntryListT *, EntryListT *);
void	entry_list_append(EntryListT *, EntryListT *);
BoolT	entry_list_is_empty(EntryListT *);
void	entry_list_save_state(EntryListT *, SaveListT *);
void	entry_list_restore_state(EntryListT *, SaveListT *);
void	entry_list_iter(EntryListT *, void(*)(EntryT *, void *),
				void *);
void	entry_list_iter_table(EntryListT *, BoolT,
				      void(*)(EntryT *, void *), void *);
void	entry_list_destroy(EntryListT *);

void	write_entry_list(OStreamT *, EntryListT *);

#endif /* !defined (H_ENTRY_LIST) */
