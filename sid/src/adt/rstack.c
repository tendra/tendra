/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * rstack.c - Renaming stack ADT.
 *
 * This file implements the renaming stack routines.  They are mainly used by
 * the output routines to do scoping of inlined rules.
 */

#include <assert.h>

#include <shared/bool.h>
#include <shared/check.h>

#include "rstack.h"
#include "action.h"
#include "basic.h"
#include "name.h"
#include "rule.h"
#include "type.h"

void
rstack_init(RStackT *rstack)
{
	rstack->head = NULL;
}

void
rstack_push_frame(RStackT *rstack)
{
	TransStackEntryT *frame = ALLOCATE(TransStackEntryT);

	frame->next = rstack->head;
	rtrans_init(&frame->translator);
	rstack->head = frame;
}

void
rstack_compute_formal_renaming(RStackT *rstack, TypeTupleT *names)
{
	assert(rstack->head);
	types_compute_formal_renaming(names, &rstack->head->translator);
}

void
rstack_compute_formal_inlining(RStackT *rstack, TypeTupleT *names, TypeTupleT *renames)
{
	SaveRStackT state;

	assert(rstack->head);
	state.head = rstack->head->next;
	types_compute_formal_inlining(names, renames, &rstack->head->translator, &state);
}

void
rstack_compute_local_renaming(RStackT *rstack, TypeTupleT *names,
	TypeTupleT *exclude, TableT *table)
{
	SaveRStackT state;

	assert(rstack->head);
	state.head = rstack->head->next;
	types_compute_local_renaming(names, exclude, &rstack->head->translator,
		&state, table);
}

void
rstack_add_translation(RStackT *rstack, EntryT *from, EntryT *to, EntryT *type,
	bool reference)
{
	assert(rstack->head);
	rtrans_add_translation(&rstack->head->translator, from, to, type, reference);
}

void
rstack_save_state(RStackT *rstack, SaveRStackT *state)
{
	state->head = rstack->head;
}

EntryT *
rstack_get_translation(SaveRStackT *state, EntryT *entry, EntryT **type_ref,
	bool *reference_ref)
{
	TransStackEntryT *frame;

	for (frame = state->head; frame; frame = frame->next) {
		EntryT *translation;

		translation = rtrans_get_translation(&frame->translator, entry,
			type_ref, reference_ref);
		if (translation) {
			return translation;
		}
	}

	return NULL;
}

void
rstack_apply_for_non_locals(RStackT *non_local_stack, SaveRStackT *state,
	void (*proc)(EntryT *, EntryT *, void *), void *closure)
{
	TransStackEntryT *frame = non_local_stack->head;

	if (frame != NULL && state->head) {
		TransStackEntryT *limit = state->head->next;

		for ( ; frame != limit; frame = frame->next) {
			rtrans_apply_for_non_locals(&frame->translator, proc, closure);
		}
	}
}

void
rstack_pop_frame(RStackT *rstack)
{
	TransStackEntryT *frame = rstack->head;

	rstack->head = frame->next;
	rtrans_destroy(&frame->translator);
	DEALLOCATE(frame);
}

void
rstack_destroy(RStackT *rstack)
{
	while (rstack->head) {
		rstack_pop_frame(rstack);
	}
}
