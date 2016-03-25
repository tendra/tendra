/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * key.c - Key ADT.
 *
 * This file implements the identifier key routines used by SID.
 */

#include <assert.h>

#include <shared/bool.h>
#include <shared/check.h>

#include "key.h"

void
key_init_from_string(KeyT *key, NStringT *string, unsigned number)
{
	key->type   = KT_STRING;
	nstring_assign(&key->string, string);
	key->number = number;
}

void
key_init_from_number(KeyT *key, unsigned number)
{
	key->type   = KT_NUMERIC;
	key->number = number;
}

CmpT
key_compare(KeyT *key1, KeyT *key2)
{
	if (key1->type < key2->type) {
		return CMP_LT;
	} else if (key1->type > key2->type) {
		return CMP_GT;
	}

	switch (key1->type)EXHAUSTIVE {
	case KT_STRING:
		return nstring_compare(&key1->string, &key2->string);

	case KT_NUMERIC:
		if (key1->number < key2->number) {
			return CMP_LT;
		} else if (key1->number > key2->number) {
			return CMP_GT;
		} else {
			return CMP_EQ;
		}
	}

	UNREACHED;
}

bool
key_is_string(KeyT *key)
{
	return key->type == KT_STRING;
}

NStringT *
key_get_string(KeyT *key)
{
	assert(key->type == KT_STRING);
	return &key->string;
}

unsigned
key_get_number(KeyT *key)
{
	return key->number;
}

unsigned
key_hash_value(KeyT *key)
{
	switch (key->type) EXHAUSTIVE {
	case KT_NUMERIC:
		return key->number;

	case KT_STRING:
		return nstring_hash_value(&key->string);
	}

	UNREACHED;
}

void
write_key(OStreamT *ostream, KeyT *key)
{
	switch (key->type) EXHAUSTIVE {
	case KT_STRING:
		write_nstring(ostream, &key->string);
		break;

	case KT_NUMERIC:
		write_unsigned(ostream, key->number);
		break;
	}
}
