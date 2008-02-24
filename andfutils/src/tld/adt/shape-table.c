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


/*
 * shape-table.c - Shape table ADT.
 *
 * This file implements the shape table routines used by the TDF linker.
 */

#include "shape-table.h"

#include "solve-cycles.h"

ShapeTableT *
shape_table_create(void)
{
    ShapeTableT *table = ALLOCATE(ShapeTableT);
    unsigned    i;

    for (i = 0; i < SHAPE_TABLE_SIZE; i++) {
	table->contents[i] = NULL;
    }
    table->token_entry = NULL;
    table->tag_entry   = NULL;
    return(table);
}

ShapeEntryT *
shape_table_add(ShapeTableT *table,			 NStringT *   key)
{
    unsigned     hash_value = (nstring_hash_value(key)% SHAPE_TABLE_SIZE);
    ShapeEntryT **entryp     = & (table->contents[hash_value]);
    ShapeEntryT * entry;

    while ((entry = *entryp) != NULL) {
	if (nstring_equal(key, shape_entry_key(entry))) {
	    return(entry);
	}
	entryp = shape_entry_next_ref(entry);
    }
    entry   = shape_entry_create(key);
    *entryp = entry;
    return(entry);
}

ShapeEntryT *
shape_table_get(ShapeTableT *table,			 NStringT *   key)
{
    unsigned    hash_value = (nstring_hash_value(key)% SHAPE_TABLE_SIZE);
    ShapeEntryT *entry      = (table->contents[hash_value]);

    while (entry) {
	if (nstring_equal(key, shape_entry_key(entry))) {
	    return(entry);
	}
	entry = shape_entry_next(entry);
    }
    return(NULL);
}

ShapeEntryT *
shape_table_get_token_entry(ShapeTableT *table)
{
    if (table->token_entry == NULL) {
	NStringT nstring;

	nstring_copy_cstring(&nstring, "token");
	table->token_entry = shape_table_get(table, &nstring);
	nstring_destroy(&nstring);
    }
    return(table->token_entry);
}

ShapeEntryT *
shape_table_get_tag_entry(ShapeTableT *table)
{
    if (table->tag_entry == NULL) {
	NStringT nstring;

	nstring_copy_cstring(&nstring, "tag");
	table->tag_entry = shape_table_get(table, &nstring);
	nstring_destroy(&nstring);
    }
    return(table->tag_entry);
}

void
shape_table_iter(ShapeTableT *table, void (*proc)(ShapeEntryT *, void *),
		 void * closure)
{
    unsigned i;

    for (i = 0; i < SHAPE_TABLE_SIZE; i++) {
	ShapeEntryT *entry = (table->contents[i]);

	while (entry) {
	   (*proc)(entry, closure);
	    entry = shape_entry_next(entry);
	}
    }
}

void
shape_table_deallocate(ShapeTableT *table)
{
    unsigned i;

    for (i = 0; i < SHAPE_TABLE_SIZE; i++) {
	ShapeEntryT *entry = (table->contents[i]);

	while (entry) {
	    entry = shape_entry_deallocate(entry);
	}
    }
}

