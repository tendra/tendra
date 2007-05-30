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


/*** table.c --- Identifier table ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the identifier table routines used by SID.
 *
 *** Change Log:
 * $Log: table.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1994/12/15  09:59:05  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.2  1994/08/22  09:37:32  smf
 * Fixed bug DR114:ids-too-long.
 *
 * Revision 1.1.1.1  1994/07/25  16:04:43  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#include <limits.h>

#include "table.h"
#include "action.h"
#include "basic.h"
#include "gen-errors.h"
#include "grammar.h"
#include "name.h"
#include "rule.h"
#include "type.h"

/*--------------------------------------------------------------------------*/

static unsigned
table_next_generated_key(void)
{
    static unsigned sequence = 0;

    if (sequence == UINT_MAX) {
	E_too_many_generated_ids();
	UNREACHED;
    }
    return(sequence++);
}

static EntryP
table_add_entry(TableP table, NStringP key, EntryTypeT type, BoolT *found_ref)
{
    unsigned hash   = (nstring_hash_value(key)% TABLE_SIZE);
    EntryP  *entryp = &(table->contents[hash]);
    EntryP   entry;
    unsigned number;

    *found_ref = FALSE;
    while ((entry = *entryp) != NULL) {
	KeyP ent_key = entry_key(entry);

	if ((key_is_string(ent_key)) &&
	   (nstring_equal(key_get_string(ent_key), key))) {
	    if (type == ET_NAME) {
		nstring_destroy(key);
		return(entry);
	    } else if (entry_type(entry) == ET_NAME) {
		nstring_destroy(key);
		entry_change_type(entry, type);
		return(entry);
	    } else if ((entry_type(entry) == type) &&
		      ((type == ET_ACTION) || (type == ET_RULE))) {
		*found_ref = TRUE;
		nstring_destroy(key);
		return(entry);
	    } else {
		return(NULL);
	    }
	}
	entryp = entry_next_ref(entry);
    }
    number  = table_next_generated_key();
    entry   = entry_create_from_string(key, number, type);
    *entryp = entry;
    return(entry);
}

/*--------------------------------------------------------------------------*/

void
table_init(TableP table)
{
    unsigned i;

    for (i = 0; i < TABLE_SIZE; i++) {
	table->contents[i] = NULL;
    }
}

EntryP
table_add_type(TableP table, NStringP key)
{
    BoolT  found;
    EntryP entry = table_add_entry(table, key, ET_TYPE, &found);

    if (entry) {
	entry_set_type(entry, type_create());
    }
    return(entry);
}

EntryP
table_add_basic(TableP table, NStringP key, GrammarP grammar, BoolT ignored)
{
    BoolT  found;
    EntryP entry = table_add_entry(table, key, ET_BASIC, &found);

    if (entry) {
	entry_set_basic(entry, basic_create(grammar, ignored));
    }
    return(entry);
}

EntryP
table_add_action(TableP table, NStringP key)
{
    BoolT  found;
    EntryP entry = table_add_entry(table, key, ET_ACTION, &found);

    if ((entry != NULL) && (!found)) {
	entry_set_action(entry, action_create());
    }
    return(entry);
}

EntryP
table_add_rule(TableP table, NStringP key)
{
    BoolT  found;
    EntryP entry = table_add_entry(table, key, ET_RULE, &found);

    if ((entry != NULL) && (!found)) {
	entry_set_rule(entry, rule_create(entry));
    }
    return(entry);
}

EntryP
table_add_generated_rule(TableP table, BoolT traced)
{
    unsigned sequence = table_next_generated_key();
    unsigned hash     = (sequence % TABLE_SIZE);
    EntryP  *entryp   = &(table->contents[hash]);
    EntryP   entry;

    entry = entry_create_from_number(sequence, ET_RULE, traced, *entryp);
    entry_set_rule(entry, rule_create(entry));
    *entryp = entry;
    return(entry);
}

EntryP
table_add_name(TableP table, NStringP key)
{
    BoolT found;

    return(table_add_entry(table, key, ET_NAME, &found));
}

EntryP
table_add_generated_name(TableP table)
{
    unsigned sequence = table_next_generated_key();
    unsigned hash     = (sequence % TABLE_SIZE);
    EntryP  *entryp   = &(table->contents[hash]);
    EntryP   entry;

    entry = entry_create_from_number(sequence, ET_NAME, FALSE, *entryp);
    *entryp = entry;
    return(entry);
}

EntryP
table_add_rename(TableP table)
{
    unsigned sequence = table_next_generated_key();
    unsigned hash     = (sequence % TABLE_SIZE);
    EntryP  *entryp   = &(table->contents[hash]);
    EntryP   entry;

    entry = entry_create_from_number(sequence, ET_RENAME, TRUE, *entryp);
    *entryp = entry;
    return(entry);
}

EntryP
table_add_non_local(TableP table, NStringP key, EntryP type)
{
    BoolT  found;
    EntryP entry = table_add_entry(table, key, ET_NON_LOCAL, &found);

    if (entry) {
	entry_set_non_local(entry, type);
    }
    return(entry);
}

EntryP
table_get_entry(TableP table, NStringP key)
{
    unsigned hash  = (nstring_hash_value(key)% TABLE_SIZE);
    EntryP   entry = (table->contents[hash]);

    while (entry) {
	KeyP ent_key = entry_key(entry);

	if ((key_is_string(ent_key)) &&
	   (nstring_equal(key_get_string(ent_key), key))) {
	    return(entry);
	}
	entry = entry->next;
    }
    return(NULL);
}

EntryP
table_get_type(TableP table, NStringP key)
{
    EntryP entry = table_get_entry(table, key);

    if ((entry) && (entry_is_type(entry))) {
	return(entry);
    } else {
	return(NULL);
    }
}

EntryP
table_get_basic(TableP table, NStringP key)
{
    EntryP entry = table_get_entry(table, key);

    if ((entry) && (entry_is_basic(entry))) {
	return(entry);
    } else {
	return(NULL);
    }
}

EntryP
table_get_basic_by_number(TableP table, unsigned number)
{
    unsigned i;

    for (i = 0; i < TABLE_SIZE; i++) {
	EntryP entry;

	for (entry = table->contents[i]; entry; entry = entry_next(entry)) {
	    if (entry_is_basic(entry)) {
		BasicP basic = entry_get_basic(entry);

		if (basic_terminal(basic) == number) {
		    return(entry);
		}
	    }
	}
    }
    return(NULL);
}

EntryP
table_get_action(TableP table, NStringP key)
{
    EntryP entry = table_get_entry(table, key);

    if ((entry) && (entry_is_action(entry))) {
	return(entry);
    } else {
	return(NULL);
    }
}

EntryP
table_get_rule(TableP table, NStringP key)
{
    EntryP entry = table_get_entry(table, key);

    if ((entry) && (entry_is_rule(entry))) {
	return(entry);
    } else {
	return(NULL);
    }
}

void
table_iter(TableP table, void (*proc)(EntryP, void *),
	   void * closure)
{
    unsigned i;

    for (i = 0; i < TABLE_SIZE; i++) {
	EntryP entry;

	for (entry = table->contents[i]; entry; entry = entry_next(entry)) {
	   (*proc)(entry, closure);
	}
    }
}

void
table_untrace(TableP table)
{
    unsigned i;

    for (i = 0; i < TABLE_SIZE; i++) {
	EntryP entry;

	for (entry = table->contents[i]; entry; entry = entry_next(entry)) {
	    entry_not_traced(entry);
	}
    }
}

void
table_unlink_untraced_rules(TableP table)
{
    unsigned i;

    for (i = 0; i < TABLE_SIZE; i++) {
	EntryP entry = (table->contents[i]);

	while (entry) {
	    if (entry_is_rule(entry) && (!entry_is_traced(entry))) {
		rule_deallocate(entry_get_rule(entry));
		entry_change_type(entry, ET_NAME);
	    }
	    entry = entry_next(entry);
	}
    }
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
