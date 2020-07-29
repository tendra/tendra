/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * type.c - Type ADT.
 *
 * This file implements the type ADT manipulation routines.
 */

#include <assert.h>

#include <shared/bool.h>
#include <shared/check.h>

#include "type.h"

TypeT *
type_create(bool ignored)
{
	TypeT *type = ALLOCATE(TypeT);

	type->assign_code        = NULL;
	type->param_assign_code  = NULL;
	type->result_assign_code = NULL;
	type->ignored            = ignored;

	return type;
}

void *
type_get_assign_code(TypeT *type)
{
	return type->assign_code;
}

void
type_set_assign_code(TypeT *type, void *code)
{
	assert(type->assign_code == NULL);
	type->assign_code = code;
}

void *
type_get_param_assign_code(TypeT *type)
{
	return type->param_assign_code;
}

void
type_set_param_assign_code(TypeT *type, void *code)
{
	assert(type->param_assign_code == NULL);
	type->param_assign_code = code;
}

void *
type_get_result_assign_code(TypeT *type)
{
	return type->result_assign_code;
}

void
type_set_result_assign_code(TypeT *type, void *code)
{
	assert(type->result_assign_code == NULL);
	type->result_assign_code = code;
}

bool
type_get_ignored(TypeT *type)
{
	return type->ignored;
}
