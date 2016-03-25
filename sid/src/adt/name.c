/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * name.c - Name ADT.
 *
 * This file implements the name manipulation routines.
 */

#include <assert.h>

#include <shared/bool.h>
#include <shared/check.h>

#include "name.h"

NameT *
name_create(void)
{
	NameT *name = ALLOCATE(NameT);

	name->clash    = false;
	name->used     = false;
	name->labelled = false;

	return name;
}

bool
name_test_and_set_clash(NameT *name)
{
	bool clash = name->clash;

	name->clash = true;
	return clash;
}

void
name_reset_clash(NameT *name)
{
	name->clash = false;
}

bool
name_is_used(NameT *name)
{
	return name->used;
}

void
name_used(NameT *name)
{
	name->used = true;
}

void
name_not_used(NameT *name)
{
	name->used = false;
}

unsigned
name_get_label(NameT *name)
{
	assert(name->labelled);
	return name->label;
}

void
name_set_label(NameT *name, unsigned label)
{
	name->labelled = true;
	name->label    = label;
}

void
name_reset_label(NameT *name)
{
	name->labelled = false;
}

bool
name_has_label(NameT *name)
{
	return name->labelled;
}
