/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org/>
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


/*** scope.c --- Scope stack ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the scope stack manipulation routines.
 *
 *** Change Log:*/

/****************************************************************************/

#include "scope.h"
#include "gen-errors.h"
#include "rule.h"

/*--------------------------------------------------------------------------*/

void
scope_stack_init PROTO_N ((stack))
		 PROTO_T (ScopeStackP stack)
{
    stack->head = NIL (ScopeStackFrameP);
}

void
scope_stack_push PROTO_N ((stack, scope))
		 PROTO_T (ScopeStackP stack X
			  NStringP    scope)
{
    ScopeStackFrameP frame = ALLOCATE (ScopeStackFrameT);
    DStringT         dstring;

    dstring_init (&dstring);
    if (frame->head) {
	dstring_append_nstring (&dstring, &(stack->head->scope));
    }
    dstring_append_nstring (&dstring, scope);
    dstring_append_cstring (&dstring, "::");
    dstring_to_nstring (&dstring, &(frame->scope));
    dstring_destroy (&dstring);
    frame->next = stack->head;
    frame->head = NIL (ScopeMapEntryP);
    frame->tail = &(frame->head);
    stack->head = frame;
}
		       
void
scope_stack_pop PROTO_N ((stack))
		PROTO_T (ScopeStackP stack)
{
    ScopeStackFrameP frame = stack->head;
    ScopeMapEntryP   entry;
    ScopeMapEntryP   next;

    ASSERT (frame);
    stack->head = frame->next;
    nstring_destroy (&(frame->scope));
    for (entry = frame->head; entry; entry = next) {
	next = entry->next;
	DEALLOCATE (entry);
    }
    DEALLOCATE (frame);
}

EntryP
scope_stack_add_rule PROTO_N ((stack, table, key, rule, found_ref))
		     PROTO_T (ScopeStackP stack X
			      TableP      table X
			      NStringP    key X
			      RuleP       rule X
			      BoolT      *found_ref)
{
    *found_ref = FALSE;
    if (stack->head) {
	DStringT dstring;
	NStringT nstring;
	EntryP   entry;

	dstring_init (&dstring);
	dstring_append_nstring (&dstring, &(stack->head->scope));
	dstring_append_nstring (&dstring, key);
	dstring_to_nstring (&dstring, &nstring);
	dstring_destroy (&dstring);
	if ((entry = table_get_rule (table, &nstring)) != NIL (EntryP)) {
	    *found_ref = TRUE;
	    nstring_destroy (&nstring);
	    return (entry);
	} else if ((entry = table_add_rule (table, &nstring)) !=
		   NIL (EntryP)) {
	    EntryP         from = table_add_name (table, key);
	    ScopeMapEntryP map  = ALLOCATE (ScopeMapEntryT);

	    (void) scope_stack_check_shadowing (stack, from, rule);
	    map->next            = NIL (ScopeMapEntryP);
	    map->from            = from;
	    map->to              = entry;
	    *(stack->head->tail) = map;
	    stack->head->tail    = &(map->next);
	    return (entry);
	} else {
	    nstring_destroy (&nstring);
	    return (NIL (EntryP));
	}
    } else {
	if (table_get_rule (table, key)) {
	    *found_ref = TRUE;
	}
	return (table_add_rule (table, key));
    }
}

EntryP
scope_stack_add_action PROTO_N ((stack, table, key, rule, found_ref))
		       PROTO_T (ScopeStackP stack X
				TableP      table X
				NStringP    key X
				RuleP       rule X
				BoolT      *found_ref)
{
    *found_ref = FALSE;
    if (stack->head) {
	DStringT dstring;
	NStringT nstring;
	EntryP   entry;

	dstring_init (&dstring);
	dstring_append_nstring (&dstring, &(stack->head->scope));
	dstring_append_nstring (&dstring, key);
	dstring_to_nstring (&dstring, &nstring);
	dstring_destroy (&dstring);
	if ((entry = table_get_action (table, &nstring)) != NIL (EntryP)) {
	    *found_ref = TRUE;
	    nstring_destroy (&nstring);
	    return (entry);
	} else if ((entry = table_add_action (table, &nstring)) !=
		   NIL (EntryP)) {
	    EntryP         from = table_add_name (table, key);
	    ScopeMapEntryP map  = ALLOCATE (ScopeMapEntryT);

	    (void) scope_stack_check_shadowing (stack, from, rule);
	    map->next            = NIL (ScopeMapEntryP);
	    map->from            = from;
	    map->to              = entry;
	    *(stack->head->tail) = map;
	    stack->head->tail    = &(map->next);
	    return (entry);
	} else {
	    nstring_destroy (&nstring);
	    return (NIL (EntryP));
	}
    } else {
	if (table_get_action (table, key)) {
	    *found_ref = TRUE;
	}
	return (table_add_action (table, key));
    }
}

EntryP
scope_stack_add_non_local PROTO_N ((stack, table, key, type, rule))
			  PROTO_T (ScopeStackP stack X
				   TableP      table X
				   NStringP    key X
				   EntryP      type X
				   RuleP       rule)
{
    DStringT dstring;
    NStringT nstring;
    EntryP   entry;

    ASSERT (stack->head);
    dstring_init (&dstring);
    dstring_append_nstring (&dstring, &(stack->head->scope));
    dstring_append_nstring (&dstring, key);
    dstring_to_nstring (&dstring, &nstring);
    dstring_destroy (&dstring);
    if ((entry = table_add_non_local (table, &nstring, type)) !=
	NIL (EntryP)) {
	EntryP         from = table_add_name (table, key);
	ScopeMapEntryP map  = ALLOCATE (ScopeMapEntryT);

	(void) scope_stack_check_shadowing (stack, from, rule);
	map->next            = NIL (ScopeMapEntryP);
	map->from            = from;
	map->to              = entry;
	*(stack->head->tail) = map;
	stack->head->tail    = &(map->next);
	return (entry);
    } else {
	nstring_destroy (&nstring);
	return (NIL (EntryP));
    }
}

EntryP
scope_stack_get_rule PROTO_N ((stack, table, key))
		     PROTO_T (ScopeStackP stack X
			      TableP      table X
			      NStringP    key)
{
    EntryP entry = table_get_entry (table, key);

    if (entry) {
	ScopeStackFrameP frame = stack->head;

	for (; frame; frame = frame->next) {
	    ScopeMapEntryP map = frame->head;

	    for (; map; map = map->next) {
		if (map->from == entry) {
		    if (entry_is_rule (map->to)) {
			return (map->to);
		    } else {
			return (NIL (EntryP));
		    }
		}
	    }
	}
	if (entry_is_rule (entry)) {
	    return (entry);
	}
    }
    return (NIL (EntryP));
}

EntryP
scope_stack_get_action PROTO_N ((stack, table, key))
		       PROTO_T (ScopeStackP stack X
				TableP      table X
				NStringP    key)
{
    EntryP entry = table_get_entry (table, key);

    if (entry) {
	ScopeStackFrameP frame = stack->head;

	for (; frame; frame = frame->next) {
	    ScopeMapEntryP map = frame->head;

	    for (; map; map = map->next) {
		if (map->from == entry) {
		    if (entry_is_action (map->to)) {
			return (map->to);
		    } else {
			return (NIL (EntryP));
		    }
		}
	    }
	}
	if (entry_is_action (entry)) {
	    return (entry);
	}
    }
    return (NIL (EntryP));
}

EntryP
scope_stack_get_non_local PROTO_N ((stack, table, key, scope))
			  PROTO_T (ScopeStackP stack X
				   TableP      table X
				   NStringP    key X
				   NStringP    scope)
{
    EntryP entry = table_get_entry (table, key);

    if (entry) {
	ScopeStackFrameP frame = stack->head;

	for (; frame; frame = frame->next) {
	    ScopeMapEntryP map = frame->head;

	    for (; map; map = map->next) {
		if (map->from == entry) {
		    if (entry_is_non_local (map->to)) {
			nstring_copy (scope, &(frame->scope));
			return (map->to);
		    } else {
			return (NIL (EntryP));
		    }
		}
	    }
	}
    }
    return (NIL (EntryP));
}

BoolT
scope_stack_check_shadowing PROTO_N ((stack, from, rule))
			    PROTO_T (ScopeStackP stack X
				     EntryP      from X
				     RuleP       rule)
{
    ScopeStackFrameP frame = stack->head;

    for (; frame; frame = frame->next) {
	ScopeMapEntryP entry;

	for (entry = frame->head; entry; entry = entry->next) {
	    if (entry->from == from) {
		E_shadows_non_local (entry_key (from), entry_key (entry->to),
				     rule);
		return (TRUE);
	    }
	}
    }
    if (entry_is_rule (from) || entry_is_action (from) ||
	entry_is_basic (from)) {
	E_shadows_global (entry_key (from), rule);
	return (TRUE);
    }
    return (FALSE);
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
**/
