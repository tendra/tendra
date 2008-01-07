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


/*** rstack.c --- Renaming stack ADT.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 *** Commentary:
 *
 * This file implements the renaming stack routines.  They are mainly used by
 * the output routines to do scoping of inlined rules.
 */

#include "rstack.h"
#include "action.h"
#include "basic.h"
#include "msgcat.h"
#include "name.h"
#include "rule.h"
#include "type.h"

/*--------------------------------------------------------------------------*/

void
rstack_init(RStackP rstack)
{
	rstack->head = NIL (TransStackEntryP);
}

void
rstack_push_frame(RStackP rstack)
{
	TransStackEntryP frame = ALLOCATE (TransStackEntryT);
	
	frame->next = rstack->head;
	rtrans_init (&(frame->translator));
	rstack->head = frame;
}

void
rstack_compute_formal_renaming(RStackP rstack,
							   TypeTupleP names)
{
	ASSERT (rstack->head);
	types_compute_formal_renaming (names, &(rstack->head->translator));
}

void
rstack_compute_formal_inlining(RStackP rstack,
							   TypeTupleP names,
							   TypeTupleP renames)
{
	SaveRStackT state;
	
	ASSERT (rstack->head);
	state.head = rstack->head->next;
	types_compute_formal_inlining (names, renames, &(rstack->head->translator),
								   &state);
}

void
rstack_compute_local_renaming(RStackP rstack,
							  TypeTupleP names,
							  TypeTupleP exclude,
							  TableP table)
{
	SaveRStackT state;
	
	ASSERT (rstack->head);
	state.head = rstack->head->next;
	types_compute_local_renaming (names, exclude, &(rstack->head->translator),
								  &state, table);
}

void
rstack_add_translation(RStackP rstack, EntryP from,
					   EntryP to, EntryP type,
					   BoolT reference)
{
	ASSERT (rstack->head);
	rtrans_add_translation (&(rstack->head->translator), from, to, type,
							reference);
}

void
rstack_save_state(RStackP rstack, SaveRStackP state)
{
	state->head = rstack->head;
}

EntryP
rstack_get_translation(SaveRStackP state,
					   EntryP entry, EntryP *type_ref,
					   BoolT *reference_ref)
{
	TransStackEntryP frame = state->head;
	
	while (frame) {
		EntryP translation;
		
		translation = rtrans_get_translation (&(frame->translator), entry,
											  type_ref, reference_ref);
		if (translation) {
			return (translation);
		}
		frame = frame->next;
	}
	return (NIL (EntryP));
}

void
rstack_apply_for_non_locals(RStackP non_local_stack,
	SaveRStackP state, void (*proc)(EntryP, EntryP, void *),
	void *closure)
{
	TransStackEntryP frame = non_local_stack->head;
	
	if ((frame != NIL (TransStackEntryP)) && (state->head)) {
		TransStackEntryP limit = state->head->next;
		
		for (; frame != limit; frame = frame->next) {
			rtrans_apply_for_non_locals (&(frame->translator), proc, closure);
		}
	}
}

void
rstack_pop_frame(RStackP rstack)
{
	TransStackEntryP frame = rstack->head;
	
	rstack->head = frame->next;
	rtrans_destroy (&(frame->translator));
	DEALLOCATE (frame);
}

void
rstack_destroy(RStackP rstack)
{
	while (rstack->head) {
		rstack_pop_frame (rstack);
	}
}
