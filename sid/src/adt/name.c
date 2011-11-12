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

#include "name.h"

NameT *
name_create(void)
{
	NameT *name = ALLOCATE(NameT);

	name->clash    = FALSE;
	name->used     = FALSE;
	name->labelled = FALSE;

	return name;
}

BoolT
name_test_and_set_clash(NameT *name)
{
	BoolT clash = name->clash;

	name->clash = TRUE;
	return clash;
}

void
name_reset_clash(NameT *name)
{
	name->clash = FALSE;
}

BoolT
name_is_used(NameT *name)
{
	return name->used;
}

void
name_used(NameT *name)
{
	name->used = TRUE;
}

void
name_not_used(NameT *name)
{
	name->used = FALSE;
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
	name->labelled = TRUE;
	name->label    = label;
}

void
name_reset_label(NameT *name)
{
	name->labelled = FALSE;
}

BoolT
name_has_label(NameT *name)
{
	return name->labelled;
}
