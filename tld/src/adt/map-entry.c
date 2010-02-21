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
 * map-entry.c - Mapping table entry ADT.
 *
 * This file implements the mapping table entry routines used by the TDF
 * linker.
 */

#include <assert.h>

#include "map-entry.h"
#include "shape-table.h"
#include "solve-cycles.h"

MapEntryT *
map_entry_create(NStringT * key,			  MapEntryT *next, 
			  unsigned  count)
{
    MapEntryT *entry = ALLOCATE(MapEntryT);

    entry->next  = next;
    nstring_copy(& (entry->key), key);
    entry->count = count;
    return(entry);
}

MapEntryT *
map_entry_next(MapEntryT *entry)
{
    return(entry->next);
}

NStringT *
map_entry_key(MapEntryT *entry)
{
    return(& (entry->key));
}

void
map_entry_set_num_links(MapEntryT *entry,				 unsigned  num_links)
{
    entry->num_links = num_links;
    entry->links     = ALLOCATE_VECTOR(MapLinkT, num_links);
}

void
map_entry_set_link(MapEntryT *entry,			    unsigned  link, 
			    unsigned  internal, 
			    unsigned  external)
{
    assert(link < entry->num_links);
    entry->links[link].internal = internal;
    entry->links[link].external = external;
}

unsigned
map_entry_get_count(MapEntryT *entry)
{
    return(entry->count);
}

unsigned
map_entry_get_num_links(MapEntryT *entry)
{
    return(entry->num_links);
}

void
map_entry_get_link(MapEntryT *entry,			    unsigned  link, 
			    unsigned *internal_ref, 
			    unsigned *external_ref)
{
    assert(link < entry->num_links);
    *internal_ref = entry->links[link].internal;
    *external_ref = entry->links[link].external;
}

void
map_entry_check_non_empty(MapEntryT *entry,				   void *  gclosure)
{
    ShapeTableT *table = (ShapeTableT *)gclosure;

    if (entry->count > 0) {
	NStringT *   key         = map_entry_key(entry);
	ShapeEntryT *shape_entry = shape_table_get(table, key);

	shape_entry_set_non_empty(shape_entry);
    }
}

