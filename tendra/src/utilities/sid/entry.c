/*
 * Copyright (c) 2002-2004, The Tendra Project <http://www.ten15.org/>
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


/*** entry.c --- Identifier table entry ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the identifier table routines used by SID.
 */

/****************************************************************************/

#include "entry.h"
#include "action.h"
#include "basic.h"
#include "msgcat.h"
#include "name.h"
#include "rule.h"
#include "type.h"

/*--------------------------------------------------------------------------*/

#ifdef FS_FAST
#undef entry_traced
#endif /* defined (FS_FAST) */
static void
entry_traced(EntryP entry)
{
    entry->traced = TRUE;
}
#ifdef FS_FAST
#define entry_traced(e) ((e)->traced = TRUE)
#endif /* defined (FS_FAST) */

/*--------------------------------------------------------------------------*/

EntryP
entry_create_from_string(NStringP key, unsigned number,
						 EntryTypeT type)
{
    EntryP entry = ALLOCATE (EntryT);
	
    entry->next   = NIL (EntryP);
    key_init_from_string (entry_key (entry), key, number);
    entry->mapped = FALSE;
    nstring_init (&(entry->mapping));
    entry->type   = type;
    entry->name   = name_create ();
    entry->traced = FALSE;
    return (entry);
}

EntryP
entry_create_from_number(unsigned key, EntryTypeT type,
						 BoolT traced, EntryP next)
{
    EntryP entry = ALLOCATE (EntryT);
	
    entry->next   = next;
    key_init_from_number (entry_key (entry), key);
    entry->mapped = FALSE;
    nstring_init (&(entry->mapping));
    entry->type   = type;
    entry->name   = name_create ();
    entry->traced = traced;
    return (entry);
}

#ifdef FS_FAST
#undef entry_set_basic
#endif /* defined (FS_FAST) */
void
entry_set_basic(EntryP entry, BasicP basic)
{
    ASSERT (entry_is_basic (entry));
    entry->u.basic = basic;
}
#ifdef FS_FAST
#define entry_set_basic(e, b) ((e)->u.basic = (b))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_set_rule
#endif /* defined (FS_FAST) */
void
entry_set_rule(EntryP entry, RuleP rule)
{
    ASSERT (entry_is_rule (entry));
    entry->u.rule = rule;
}
#ifdef FS_FAST
#define entry_set_rule(e, r) ((e)->u.rule = (r))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_set_action
#endif /* defined (FS_FAST) */
void
entry_set_action(EntryP entry, ActionP action)
{
    ASSERT (entry_is_action (entry));
    entry->u.action = action;
}
#ifdef FS_FAST
#define entry_set_action(e, a) ((e)->u.action = (a))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_set_type
#endif /* defined (FS_FAST) */
void
entry_set_type(EntryP entry, TypeP type)
{
    ASSERT (entry_is_type (entry));
    entry->u.type = type;
}
#ifdef FS_FAST
#define entry_set_type(e, t) ((e)->u.type = (t))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_set_non_local
#endif /* defined (FS_FAST) */
void
entry_set_non_local(EntryP entry, EntryP type)
{
    ASSERT (entry_is_non_local (entry));
    entry->u.non_local = type;
}
#ifdef FS_FAST
#define entry_set_non_local(e, t) ((e)->u.non_local = (t))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_next
#endif /* defined (FS_FAST) */
EntryP
entry_next(EntryP entry)
{
    return (entry->next);
}
#ifdef FS_FAST
#define entry_next(e) ((e)->next)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_next_ref
#endif /* defined (FS_FAST) */
EntryP *
entry_next_ref(EntryP entry)
{
    return (&(entry->next));
}
#ifdef FS_FAST
#define entry_next_ref(e) (&((e)->next))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_key
#endif /* defined (FS_FAST) */
KeyP
entry_key(EntryP entry)
{
    return (&(entry->key));
}
#ifdef FS_FAST
#define entry_key(e) (&((e)->key))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_type
#endif /* defined (FS_FAST) */
EntryTypeT
entry_type(EntryP entry)
{
    return (entry->type);
}
#ifdef FS_FAST
#define entry_type(e) ((e)->type)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_change_type
#endif /* defined (FS_FAST) */
void
entry_change_type(EntryP entry, EntryTypeT type)
{
    entry->type = type;
}
#ifdef FS_FAST
#define entry_change_type(e, t) ((e)->type= (t))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_is_basic
#endif /* defined (FS_FAST) */
BoolT
entry_is_basic(EntryP entry)
{
    return (entry->type == ET_BASIC);
}
#ifdef FS_FAST
#define entry_is_basic(e) ((e)->type == ET_BASIC)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_is_action
#endif /* defined (FS_FAST) */
BoolT
entry_is_action(EntryP entry)
{
    return (entry->type == ET_ACTION);
}
#ifdef FS_FAST
#define entry_is_action(e) ((e)->type == ET_ACTION)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_is_rule
#endif /* defined (FS_FAST) */
BoolT
entry_is_rule(EntryP entry)
{
    return (entry->type == ET_RULE);
}
#ifdef FS_FAST
#define entry_is_rule(e) ((e)->type == ET_RULE)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_is_type
#endif /* defined (FS_FAST) */
BoolT
entry_is_type(EntryP entry)
{
    return (entry->type == ET_TYPE);
}
#ifdef FS_FAST
#define entry_is_type(e) ((e)->type == ET_TYPE)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_is_non_local
#endif /* defined (FS_FAST) */
BoolT
entry_is_non_local(EntryP entry)
{
    return (entry->type == ET_NON_LOCAL);
}
#ifdef FS_FAST
#define entry_is_non_local(e) ((e)->type == ET_NON_LOCAL)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_get_basic
#endif /* defined (FS_FAST) */
BasicP
entry_get_basic(EntryP entry)
{
    ASSERT (entry_is_basic (entry));
    return (entry->u.basic);
}
#ifdef FS_FAST
#define entry_get_basic(e) ((e)->u.basic)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_get_action
#endif /* defined (FS_FAST) */
ActionP
entry_get_action(EntryP entry)
{
    ASSERT (entry_is_action (entry));
    return (entry->u.action);
}
#ifdef FS_FAST
#define entry_get_action(e) ((e)->u.action)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_get_rule
#endif /* defined (FS_FAST) */
RuleP
entry_get_rule(EntryP entry)
{
    ASSERT (entry_is_rule (entry));
    return (entry->u.rule);
}
#ifdef FS_FAST
#define entry_get_rule(e) ((e)->u.rule)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_get_name
#endif /* defined (FS_FAST) */
NameP
entry_get_name(EntryP entry)
{
    return (entry->name);
}
#ifdef FS_FAST
#define entry_get_name(e) ((e)->name)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_get_type
#endif /* defined (FS_FAST) */
TypeP
entry_get_type(EntryP entry)
{
    ASSERT (entry_is_type (entry));
    return (entry->u.type);
}
#ifdef FS_FAST
#define entry_get_type(e) ((e)->u.type)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_get_non_local
#endif /* defined (FS_FAST) */
EntryP
entry_get_non_local(EntryP entry)
{
    ASSERT (entry_is_non_local (entry));
    return (entry->u.non_local);
}
#ifdef FS_FAST
#define entry_get_non_local(e) ((e)->u.non_local)
#endif /* defined (FS_FAST) */

void
entry_set_mapping(EntryP entry, NStringP mapping)
{
    if (entry->mapped) {
		nstring_destroy (&(entry->mapping));
    }
    nstring_assign (&(entry->mapping), mapping);
    entry->mapped = TRUE;
}

NStringP
entry_get_mapping(EntryP entry)
{
    if (entry->mapped) {
		return (&(entry->mapping));
    }
    return (NIL (NStringP));
}

void
entry_iter(EntryP entry, BoolT full, void (*proc)(EntryP, GenericP),
		   GenericP closure)
{
    if (!entry_is_traced (entry)) {
		entry_traced (entry);
		if (proc) {
			(*proc) (entry, closure);
		}
		switch (entry_type (entry)) EXHAUSTIVE {
		case ET_RULE: {
			RuleP rule = entry_get_rule (entry);
			
			rule_iter_for_table (rule, full, proc, closure);
		}
			break;
		case ET_ACTION: {
			ActionP action = entry_get_action (entry);
			
			action_iter_for_table (action, full, proc, closure);
		}
			break;
		case ET_BASIC: {
			BasicP basic = entry_get_basic (entry);
			
			basic_iter_for_table (basic, full, proc, closure);
		}
			break;
		case ET_NON_LOCAL:
			if (full) {
				entry_iter (entry_get_non_local (entry), TRUE, proc, closure);
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

#ifdef FS_FAST
#undef entry_not_traced
#endif /* defined (FS_FAST) */
void
entry_not_traced(EntryP entry)
{
    entry->traced = FALSE;
}
#ifdef FS_FAST
#define entry_not_traced(e) ((e)->traced = FALSE)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef entry_is_traced
#endif /* defined (FS_FAST) */
BoolT
entry_is_traced(EntryP entry)
{
    return (entry->traced);
}
#ifdef FS_FAST
#define entry_is_traced(e) ((e)->traced)
#endif /* defined (FS_FAST) */

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../library")
 * eval: (include::add-path-entry "../generated")
 * end:
 **/
