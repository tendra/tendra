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


/*** scope.c --- Scope stack ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the scope stack manipulation routines.
 *
 *** Change Log:
 * $Log: scope.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:59:02  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:04:42  smf
 * Initial import of SID 1.8 non shared files.
 *
**/

/****************************************************************************/

#include <assert.h>

#include "scope.h"
#include "gen-errors.h"
#include "rule.h"

/*--------------------------------------------------------------------------*/

void
scope_stack_init(ScopeStackP stack)
{
    stack->head = NULL;
}

void
scope_stack_push(ScopeStackP stack, NStringP scope)
{
    ScopeStackFrameP frame = ALLOCATE(ScopeStackFrameT);
    DStringT         dstring;

    dstring_init(&dstring);
    if (frame->head) {
	dstring_append_nstring(&dstring, &(stack->head->scope));
    }
    dstring_append_nstring(&dstring, scope);
    dstring_append_cstring(&dstring, "::");
    dstring_to_nstring(&dstring, &(frame->scope));
    dstring_destroy(&dstring);
    frame->next = stack->head;
    frame->head = NULL;
    frame->tail = &(frame->head);
    stack->head = frame;
}

void
scope_stack_pop(ScopeStackP stack)
{
    ScopeStackFrameP frame = stack->head;
    ScopeMapEntryP   entry;
    ScopeMapEntryP   next;

    assert(frame);
    stack->head = frame->next;
    nstring_destroy(&(frame->scope));
    for (entry = frame->head; entry; entry = next) {
	next = entry->next;
	DEALLOCATE(entry);
    }
    DEALLOCATE(frame);
}

EntryP
scope_stack_add_rule(ScopeStackP stack, TableP table, NStringP key, RuleP rule,
		     BoolT *found_ref)
{
    *found_ref = FALSE;
    if (stack->head) {
	DStringT dstring;
	NStringT nstring;
	EntryP   entry;

	dstring_init(&dstring);
	dstring_append_nstring(&dstring, &(stack->head->scope));
	dstring_append_nstring(&dstring, key);
	dstring_to_nstring(&dstring, &nstring);
	dstring_destroy(&dstring);
	if ((entry = table_get_rule(table, &nstring)) != NULL) {
	    *found_ref = TRUE;
	    nstring_destroy(&nstring);
	    return(entry);
	} else if ((entry = table_add_rule(table, &nstring)) !=
		   NULL) {
	    EntryP         from = table_add_name(table, key);
	    ScopeMapEntryP map  = ALLOCATE(ScopeMapEntryT);

	   (void)scope_stack_check_shadowing(stack, from, rule);
	    map->next            = NULL;
	    map->from            = from;
	    map->to              = entry;
	    *(stack->head->tail) = map;
	    stack->head->tail    = &(map->next);
	    return(entry);
	} else {
	    nstring_destroy(&nstring);
	    return(NULL);
	}
    } else {
	if (table_get_rule(table, key)) {
	    *found_ref = TRUE;
	}
	return(table_add_rule(table, key));
    }
}

EntryP
scope_stack_add_action(ScopeStackP stack, TableP table, NStringP key,
		       RuleP rule, BoolT *found_ref)
{
    *found_ref = FALSE;
    if (stack->head) {
	DStringT dstring;
	NStringT nstring;
	EntryP   entry;

	dstring_init(&dstring);
	dstring_append_nstring(&dstring, &(stack->head->scope));
	dstring_append_nstring(&dstring, key);
	dstring_to_nstring(&dstring, &nstring);
	dstring_destroy(&dstring);
	if ((entry = table_get_action(table, &nstring)) != NULL) {
	    *found_ref = TRUE;
	    nstring_destroy(&nstring);
	    return(entry);
	} else if ((entry = table_add_action(table, &nstring)) !=
		   NULL) {
	    EntryP         from = table_add_name(table, key);
	    ScopeMapEntryP map  = ALLOCATE(ScopeMapEntryT);

	   (void)scope_stack_check_shadowing(stack, from, rule);
	    map->next            = NULL;
	    map->from            = from;
	    map->to              = entry;
	    *(stack->head->tail) = map;
	    stack->head->tail    = &(map->next);
	    return(entry);
	} else {
	    nstring_destroy(&nstring);
	    return(NULL);
	}
    } else {
	if (table_get_action(table, key)) {
	    *found_ref = TRUE;
	}
	return(table_add_action(table, key));
    }
}

EntryP
scope_stack_add_non_local(ScopeStackP stack, TableP table, NStringP key,
			  EntryP type, RuleP rule)
{
    DStringT dstring;
    NStringT nstring;
    EntryP   entry;

    assert(stack->head);
    dstring_init(&dstring);
    dstring_append_nstring(&dstring, &(stack->head->scope));
    dstring_append_nstring(&dstring, key);
    dstring_to_nstring(&dstring, &nstring);
    dstring_destroy(&dstring);
    if ((entry = table_add_non_local(table, &nstring, type)) !=
	NULL) {
	EntryP         from = table_add_name(table, key);
	ScopeMapEntryP map  = ALLOCATE(ScopeMapEntryT);

	(void)scope_stack_check_shadowing(stack, from, rule);
	map->next            = NULL;
	map->from            = from;
	map->to              = entry;
	*(stack->head->tail) = map;
	stack->head->tail    = &(map->next);
	return(entry);
    } else {
	nstring_destroy(&nstring);
	return(NULL);
    }
}

EntryP
scope_stack_get_rule(ScopeStackP stack, TableP table, NStringP key)
{
    EntryP entry = table_get_entry(table, key);

    if (entry) {
	ScopeStackFrameP frame = stack->head;

	for (; frame; frame = frame->next) {
	    ScopeMapEntryP map = frame->head;

	    for (; map; map = map->next) {
		if (map->from == entry) {
		    if (entry_is_rule(map->to)) {
			return(map->to);
		    } else {
			return(NULL);
		    }
		}
	    }
	}
	if (entry_is_rule(entry)) {
	    return(entry);
	}
    }
    return(NULL);
}

EntryP
scope_stack_get_action(ScopeStackP stack, TableP table, NStringP key)
{
    EntryP entry = table_get_entry(table, key);

    if (entry) {
	ScopeStackFrameP frame = stack->head;

	for (; frame; frame = frame->next) {
	    ScopeMapEntryP map = frame->head;

	    for (; map; map = map->next) {
		if (map->from == entry) {
		    if (entry_is_action(map->to)) {
			return(map->to);
		    } else {
			return(NULL);
		    }
		}
	    }
	}
	if (entry_is_action(entry)) {
	    return(entry);
	}
    }
    return(NULL);
}

EntryP
scope_stack_get_non_local(ScopeStackP stack, TableP table, NStringP key,
			  NStringP scope)
{
    EntryP entry = table_get_entry(table, key);

    if (entry) {
	ScopeStackFrameP frame = stack->head;

	for (; frame; frame = frame->next) {
	    ScopeMapEntryP map = frame->head;

	    for (; map; map = map->next) {
		if (map->from == entry) {
		    if (entry_is_non_local(map->to)) {
			nstring_copy(scope, &(frame->scope));
			return(map->to);
		    } else {
			return(NULL);
		    }
		}
	    }
	}
    }
    return(NULL);
}

BoolT
scope_stack_check_shadowing(ScopeStackP stack, EntryP from, RuleP rule)
{
    ScopeStackFrameP frame = stack->head;

    for (; frame; frame = frame->next) {
	ScopeMapEntryP entry;

	for (entry = frame->head; entry; entry = entry->next) {
	    if (entry->from == from) {
		E_shadows_non_local(entry_key(from), entry_key(entry->to),
				     rule);
		return(TRUE);
	    }
	}
    }
    if (entry_is_rule(from) || entry_is_action(from) ||
	entry_is_basic(from)) {
	E_shadows_global(entry_key(from), rule);
	return(TRUE);
    }
    return(FALSE);
}
