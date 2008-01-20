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
 * entry.c - Identifier table entry ADT.
 *
 * This file implements the identifier table routines used by SID.
 */

#include <assert.h>

#include "entry.h"
#include "action.h"
#include "basic.h"
#include "../gen-errors.h"
#include "name.h"
#include "rule.h"
#include "type.h"

static void
entry_traced(EntryT * entry)
{
    entry->traced = TRUE;
}

/*
 * Externally visible functions
 */

EntryT *
entry_create_from_string(NStringT * key, unsigned number, EntryTypeT type)
{
    EntryT * entry = ALLOCATE(EntryT);

    entry->next   = NULL;
    key_init_from_string(entry_key(entry), key, number);
    entry->mapped = FALSE;
    nstring_init(&(entry->mapping));
    entry->type   = type;
    entry->name   = name_create();
    entry->traced = FALSE;
    return(entry);
}

EntryT *
entry_create_from_number(unsigned key, EntryTypeT type, BoolT traced,
			 EntryT * next)
{
    EntryT * entry = ALLOCATE(EntryT);

    entry->next   = next;
    key_init_from_number(entry_key(entry), key);
    entry->mapped = FALSE;
    nstring_init(&(entry->mapping));
    entry->type   = type;
    entry->name   = name_create();
    entry->traced = traced;
    return(entry);
}

void
entry_set_basic(EntryT * entry, BasicT * basic)
{
    assert(entry_is_basic(entry));
    entry->u.basic = basic;
}

void
entry_set_rule(EntryT * entry, RuleT * rule)
{
    assert(entry_is_rule(entry));
    entry->u.rule = rule;
}

void
entry_set_action(EntryT * entry, ActionT * action)
{
    assert(entry_is_action(entry));
    entry->u.action = action;
}

void
entry_set_type(EntryT * entry, TypeT * type)
{
    assert(entry_is_type(entry));
    entry->u.type = type;
}

void
entry_set_non_local(EntryT * entry, EntryT * type)
{
    assert(entry_is_non_local(entry));
    entry->u.non_local = type;
}

EntryT *
entry_next(EntryT * entry)
{
    return(entry->next);
}

EntryT * *
entry_next_ref(EntryT * entry)
{
    return(&(entry->next));
}

KeyT *
entry_key(EntryT * entry)
{
    return(&(entry->key));
}

EntryTypeT
entry_type(EntryT * entry)
{
    return(entry->type);
}

void
entry_change_type(EntryT * entry, EntryTypeT type)
{
    entry->type = type;
}

BoolT
entry_is_basic(EntryT * entry)
{
    return(entry->type == ET_BASIC);
}

BoolT
entry_is_action(EntryT * entry)
{
    return(entry->type == ET_ACTION);
}

BoolT
entry_is_rule(EntryT * entry)
{
    return(entry->type == ET_RULE);
}

BoolT
entry_is_type(EntryT * entry)
{
    return(entry->type == ET_TYPE);
}

BoolT
entry_is_non_local(EntryT * entry)
{
    return(entry->type == ET_NON_LOCAL);
}

BasicT *
entry_get_basic(EntryT * entry)
{
    assert(entry_is_basic(entry));
    return(entry->u.basic);
}

ActionT *
entry_get_action(EntryT * entry)
{
    assert(entry_is_action(entry));
    return(entry->u.action);
}

RuleT *
entry_get_rule(EntryT * entry)
{
    assert(entry_is_rule(entry));
    return(entry->u.rule);
}

NameT *
entry_get_name(EntryT * entry)
{
    return(entry->name);
}

TypeT *
entry_get_type(EntryT * entry)
{
    assert(entry_is_type(entry));
    return(entry->u.type);
}

EntryT *
entry_get_non_local(EntryT * entry)
{
    assert(entry_is_non_local(entry));
    return(entry->u.non_local);
}

void
entry_set_mapping(EntryT * entry, NStringT * mapping)
{
    if (entry->mapped) {
	nstring_destroy(&(entry->mapping));
    }
    nstring_assign(&(entry->mapping), mapping);
    entry->mapped = TRUE;
}

NStringT *
entry_get_mapping(EntryT * entry)
{
    if (entry->mapped) {
	return(&(entry->mapping));
    }
    return(NULL);
}

void
entry_iter(EntryT * entry, BoolT full, void (*proc)(EntryT *, void *),
	   void * closure)
{
    if (!entry_is_traced(entry)) {
	entry_traced(entry);
	if (proc) {
	   (*proc)(entry, closure);
	}
	switch (entry_type(entry))EXHAUSTIVE {
	  case ET_RULE: {
	      RuleT * rule = entry_get_rule(entry);

	      rule_iter_for_table(rule, full, proc, closure);
	  }
	    break;
	  case ET_ACTION: {
	      ActionT * action = entry_get_action(entry);

	      action_iter_for_table(action, full, proc, closure);
	  }
	    break;
	  case ET_BASIC: {
	      BasicT * basic = entry_get_basic(entry);

	      basic_iter_for_table(basic, full, proc, closure);
	  }
	    break;
	  case ET_NON_LOCAL:
	    if (full) {
		entry_iter(entry_get_non_local(entry), TRUE, proc, closure);
	    }
	    break;
	  case ET_NAME:
	  case ET_TYPE:
	  case ET_RENAME:
	    /*NOTHING*/
	    break;
	  case ET_PREDICATE:
	    UNREACHED;
	}
    }
}

void
entry_not_traced(EntryT * entry)
{
    entry->traced = FALSE;
}

BoolT
entry_is_traced(EntryT * entry)
{
    return(entry->traced);
}
