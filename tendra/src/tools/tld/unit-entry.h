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


/*** unit-entry.h --- Unit set table entry ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * See the file "unit-entry.c" for more information.
 *
 *** Change Log:*/

/****************************************************************************/

#ifndef H_UNIT_ENTRY
#define H_UNIT_ENTRY

#include "os-interface.h"
#include "dalloc.h"
#include "dstring.h"
#include "map-table.h"
#include "shape-table.h"
#include "tdf-write.h"

/*--------------------------------------------------------------------------*/

typedef struct UnitT {
    struct UnitT	       *next;
    MapTableP			map_table;
    NStringT			contents;
} UnitT, *UnitP;

typedef struct UnitEntryT {
    struct UnitEntryT	       *next;
    NStringT			key;
    unsigned			order;
    UnitP			head;
    UnitP		       *tail;
} UnitEntryT, *UnitEntryP;

typedef struct UnitSetClosureT {
    unsigned			num_unit_sets;
    ShapeTableP			shapes;
} UnitSetClosureT, *UnitSetClosureP;

/*--------------------------------------------------------------------------*/

extern void			unit_set_contents(UnitP, NStringP);
extern MapTableP		unit_map_table(UnitP);

extern UnitEntryP		unit_entry_create(NStringP, UnitEntryP, unsigned);
extern UnitEntryP		unit_entry_next(UnitEntryP);
extern NStringP			unit_entry_key(UnitEntryP);
extern unsigned			unit_entry_order(UnitEntryP);
extern UnitP			unit_entry_add_unit(UnitEntryP, unsigned);

extern void			unit_entry_do_count(UnitEntryP, GenericP);
extern void			unit_entry_write_unit_set(UnitEntryP, UnitEntryP, TDFWriterP);
extern void			unit_entry_write_tld_unit(UnitEntryP, ShapeTableP, TDFWriterP);
extern void			unit_entry_write_units(UnitEntryP, ShapeTableP, unsigned, TDFWriterP);

#endif /* !defined (H_UNIT_ENTRY) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
 **/
