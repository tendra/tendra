/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
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


/*** map-table.c --- Mapping table ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the mapping table routines used by the TDF linker.
 *
 *** Change Log:*/

/****************************************************************************/

#include "map-table.h"

#include "solve-cycles.h"

/*--------------------------------------------------------------------------*/

MapTableP
map_table_create()
{
    MapTableP table = ALLOCATE (MapTableT);
    unsigned  i;
	
    for (i = 0; i < MAP_TABLE_SIZE; i ++) {
		table->contents [i] = NIL (MapEntryP);
    }
    return (table);
}

MapEntryP
map_table_add(MapTableP table, NStringP key,
			  unsigned count)
{
    unsigned  hash_value = (nstring_hash_value (key) % MAP_TABLE_SIZE);
    MapEntryP next       = (table->contents [hash_value]);
    MapEntryP entry      = map_entry_create (key, next, count);
	
    table->contents [hash_value] = entry;
    return (entry);
}

MapEntryP
map_table_get(MapTableP table, NStringP key)
{
    unsigned  hash_value = (nstring_hash_value (key) % MAP_TABLE_SIZE);
    MapEntryP entry      = (table->contents [hash_value]);
	
    while (entry) {
		if (nstring_equal (key, map_entry_key (entry))) {
			return (entry);
		}
		entry = map_entry_next (entry);
    }
    return (NIL (MapEntryP));
}

void
map_table_iter(MapTableP table, void (*proc)(MapEntryP, GenericP),
			   GenericP closure)
{
    unsigned i;
	
    for (i = 0; i < MAP_TABLE_SIZE; i ++) {
		MapEntryP entry = (table->contents [i]);
		
		while (entry) {
			(*proc) (entry, closure);
			entry = map_entry_next (entry);
		}
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
 **/
