/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * cstring.c - C string manipulation.
 *
 * This file implements the C string manipulation facility specified in the
 * file "cstring.h".  See that file for more details.
 */

#include <stddef.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#include <shared/check.h>

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dalloc.h>
#include <exds/cstring.h>

#include "syntax.h"

char *
cstring_duplicate(const char *cstring)
{
	size_t length = strlen(cstring);
	char *tmp    = ALLOCATE_VECTOR(char, length + 1);

	IGNORE strcpy(tmp, cstring);
	return tmp;
}

char *
cstring_duplicate_prefix(const char *cstring, size_t prefix)
{
	size_t length = strlen(cstring);

	if (length <= prefix) {
		char *tmp = ALLOCATE_VECTOR(char, length + 1);

		IGNORE strcpy(tmp, cstring);
		return tmp;
	} else {
		char *tmp = ALLOCATE_VECTOR(char, prefix + 1);

		IGNORE memcpy(tmp, cstring, prefix);
		tmp[prefix] = '\0';
		return tmp;
	}
}

unsigned
cstring_hash_value(const char *cstring)
{
	unsigned value = 0;

	while (*cstring) {
		value += (unsigned) *cstring++;
	}

	return value;
}

BoolT
cstring_ci_equal(const char *cstring1, const char *cstring2)
{
	char c1;
	char c2;

	do {
		c1 = toupper((unsigned char) *cstring1++);
		c2 = toupper((unsigned char) *cstring2++);
	} while (c1 && c2 && c1 == c2);

	return c1 == c2;
}

BoolT
cstring_to_unsigned(const char *cstring, unsigned *num_ref)
{
	unsigned number = 0;

	if (*cstring == '\0') {
		return FALSE;
	}

	do {
		/* TODO this would be better served by strtol */
		int value = syntax_value(*cstring);

		if (value == SYNTAX_NO_VALUE || value >= 10 ||
			((UINT_MAX - (unsigned)value) / (unsigned)10) < number) {
		return FALSE;
		}

		number *= (unsigned) 10;
		number += (unsigned) value;
	} while (*++cstring);

	*num_ref = number;

	return TRUE;
}

BoolT
cstring_starts(const char *cstring, const char *s)
{
	return strncmp(cstring, s, strlen(s)) == 0;
}

const char *
cstring_find_basename(const char *cstring)
{
	const char *bstring = strrchr(cstring, '/');

	if (bstring != NULL) {
		return bstring + 1;
	}

	return cstring;
}
