/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * dstring.c - String manipulation.
 *
 * This file implements the string manipulation facility specified in the file
 * "dstring.h".  See that file for more details.
 */

#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <string.h>

#include <shared/check.h>

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/ostream.h>
#include <exds/dalloc.h>
#include <exds/dstring.h>

#define DSTRING_CHUNK_SIZE 32

/*
 * Functions for manipulating nstrings.
 */

void
nstring_init(NStringT *nstring)
{
	nstring->length   = 0;
	nstring->contents = NULL;
}

void
nstring_init_length(NStringT *nstring, size_t length)
{
	nstring->length   = length;
	nstring->contents = ALLOCATE_VECTOR(char, length);
}

void
nstring_assign(NStringT *to, NStringT *from)
{
	to->length     = nstring_length(from);
	to->contents   = from->contents;
}

void
nstring_copy_cstring(NStringT *nstring, const char *cstring)
{
	size_t length = strlen(cstring);

	if (length > 0) {
		nstring->length   = length;
		nstring->contents = ALLOCATE_VECTOR(char, length);
		IGNORE memcpy(nstring->contents, cstring, (size_t) length);
	} else {
		nstring->length   = 0;
		nstring->contents = NULL;
	}
}

void
nstring_insert_cstring(NStringT *nstring, const char *cstring)
{
	size_t length = nstring_length(nstring);

	if (length > 0) {
		IGNORE memcpy(nstring->contents, cstring, (size_t) length);
	}
}

void
nstring_copy(NStringT *to, NStringT *from)
{
	size_t length = nstring_length(from);

	if (length > 0) {
		to->length   = length;
		to->contents = ALLOCATE_VECTOR(char, length);
		IGNORE memcpy(to->contents, from->contents, (size_t) length);
	} else {
		to->length   = 0;
		to->contents = NULL;
	}
}

char *
nstring_to_cstring(NStringT *nstring)
{
	size_t length = nstring_length(nstring);
	char *tmp       = ALLOCATE_VECTOR(char, length + 1);

	if (length > 0) {
		IGNORE memcpy(tmp, nstring->contents, (size_t) length);
	}
	tmp[length] = '\0';
	return tmp;
}

unsigned
nstring_hash_value(NStringT *nstring)
{
	unsigned value     = 0;
	char *tmp_contents = (nstring->contents);
	size_t tmp_length  = nstring_length(nstring);

	while (tmp_length--) {
		value += (unsigned) *tmp_contents++;
	}

	return value;
}

size_t
nstring_length(NStringT *nstring)
{
	return nstring->length;
}

char *
nstring_contents(NStringT *nstring)
{
	return nstring->contents;
}

CmpT
nstring_compare(NStringT *nstring1, NStringT *nstring2)
{
	size_t length = nstring_length(nstring1);
	int    status;

	if (length > nstring_length(nstring2)) {
		length = nstring_length(nstring2);
	}

	status = memcmp(nstring1->contents, nstring2->contents, (size_t) length);
	if (status < 0) {
		return CMP_LT;
	} else if (status > 0) {
		return CMP_GT;
	} else if (nstring_length(nstring1) < nstring_length(nstring2)) {
		return CMP_LT;
	} else if (nstring_length(nstring1) > nstring_length(nstring2)) {
		return CMP_GT;
	} else {
		return CMP_EQ;
	}
}

BoolT
nstring_equal(NStringT *nstring1, NStringT *nstring2)
{
	size_t length = nstring_length(nstring1);

	return length == nstring_length(nstring2) &&
		memcmp(nstring1->contents, nstring2->contents, (size_t) length) == 0;
}

BoolT
nstring_ci_equal(NStringT *nstring1, NStringT *nstring2)
{
	size_t length = nstring_length(nstring1);

	if (length == nstring_length(nstring2)) {
		char *tmp1 = nstring1->contents;
		char *tmp2 = nstring2->contents;
		char c1;
		char c2;

		do {
			c1 = toupper((unsigned char) *tmp1++);
			c2 = toupper((unsigned char) *tmp2++);
			if (length-- == 0) {
				return TRUE;
			}
		} while (c1 == c2);
	}

	return FALSE;
}

BoolT
nstring_contains(NStringT *nstring, char c)
{
	char *contents = nstring_contents(nstring);
	size_t length  = nstring_length(nstring);

	return memchr(contents, c, (size_t) length) != NULL;
}

BoolT
nstring_is_prefix(NStringT *nstring1, NStringT *nstring2)
{
	char *contents1 = nstring_contents(nstring1);
	char *contents2 = nstring_contents(nstring2);
	size_t length   = nstring_length(nstring2);

	return length < nstring_length(nstring1) &&
		memcmp(contents1, contents2, (size_t) length) == 0;
}

void
nstring_destroy(NStringT *nstring)
{
	DEALLOCATE(nstring->contents);
}

void
write_nstring(OStreamT *ostream, NStringT *nstring)
{
	size_t length = nstring_length(nstring);

	if (length > 0) {
		write_chars(ostream, nstring->contents, length);
	}
}


/*
 * Functions for manipulating dstrings.
 */

void
dstring_init(DStringT *dstring)
{
	dstring->length     = 0;
	dstring->max_length = DSTRING_CHUNK_SIZE;
	dstring->contents   = ALLOCATE_VECTOR(char, dstring->max_length);
}

size_t
dstring_length(DStringT *dstring)
{
	return dstring->length;
}

void
dstring_assign(DStringT *to, DStringT *from)
{
	to->length     = dstring_length(from);
	to->max_length = from->max_length;
	to->contents   = from->contents;
}

void
dstring_append_char(DStringT *dstring, char c)
{
	if (dstring->length >= dstring->max_length) {
		char * tmp;

		dstring->max_length += DSTRING_CHUNK_SIZE;
		tmp                  = ALLOCATE_VECTOR(char, dstring->max_length);

		IGNORE memcpy(tmp, dstring->contents, (size_t) dstring->length);
		DEALLOCATE(dstring->contents);
		dstring->contents = tmp;
	}

	dstring->contents[dstring->length++] = c;
}

void
dstring_append_cstring(DStringT *dstring, const char *cstring)
{
	size_t clength = strlen(cstring);
	size_t length  = clength + dstring->length;

	if (length > dstring->max_length) {
		char *tmp;

		while (dstring->max_length < length) {
			dstring->max_length += DSTRING_CHUNK_SIZE;
		}

		tmp = ALLOCATE_VECTOR(char, dstring->max_length);
		IGNORE memcpy(tmp, dstring->contents, (size_t) dstring->length);
		DEALLOCATE(dstring->contents);
		dstring->contents = tmp;
	}

	IGNORE memcpy(&dstring->contents[dstring->length], cstring,
		(size_t) clength);
	dstring->length = length;
}

void
dstring_append_nstring(DStringT *dstring, NStringT *nstring)
{
	size_t nlength = nstring_length(nstring);
	size_t length  = nlength + (dstring->length);

	if (length > dstring->max_length) {
		char * tmp;

		while ((dstring->max_length) < length) {
			dstring->max_length += DSTRING_CHUNK_SIZE;
		}
		tmp = ALLOCATE_VECTOR(char, dstring->max_length);
		IGNORE memcpy(tmp, dstring->contents, (size_t) dstring->length);
		DEALLOCATE(dstring->contents);
		dstring->contents = tmp;
	}

	IGNORE memcpy(&dstring->contents[dstring->length], nstring_contents(nstring),
		(size_t) nlength);
	dstring->length = length;
}

BoolT
dstring_last_char_equal(DStringT *dstring, char c)
{
	return dstring->length && dstring->contents[dstring->length - 1] == c;
}

void
dstring_to_nstring(DStringT *dstring, NStringT *nstring)
{
	if (dstring->length > 0) {
		nstring->length   = dstring->length;
		nstring->contents = ALLOCATE_VECTOR(char, dstring->length);
		IGNORE memcpy(nstring->contents, dstring->contents,
			(size_t) dstring->length);
	} else {
		nstring->length   = 0;
		nstring->contents = NULL;
	}
}

char *
dstring_to_cstring(DStringT *dstring)
{
	char *tmp = ALLOCATE_VECTOR(char, dstring->length + 1);

	if (dstring->length > 0) {
		IGNORE memcpy(tmp, (dstring->contents),
		(size_t) dstring->length);
	}

	tmp[dstring->length] = '\0';
	return tmp;
}

char *
dstring_destroy_to_cstring(DStringT *dstring)
{
	char *tmp;

	if (dstring->length >= dstring->max_length) {
		tmp = ALLOCATE_VECTOR(char, dstring->length + 1);
		IGNORE memcpy(tmp, dstring->contents, (size_t) dstring->length);
		DEALLOCATE(dstring->contents);
	} else {
		tmp = dstring->contents;
	}

	tmp[dstring->length]  = '\0';
	dstring->length       = 0;
	dstring->max_length   = 0;
	dstring->contents     = NULL;

	return tmp;
}

void
dstring_destroy(DStringT *dstring)
{
	DEALLOCATE(dstring->contents);
}
