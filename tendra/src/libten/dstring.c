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


/**** dstring.c --- String manipulation.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the string manipulation facility specified in the file
 * "dstring.h".  See that file for more details.
 */

/****************************************************************************/

#include <ctype.h>
#include <string.h>

#include "dstring.h"
#include "fmm.h"

/*--------------------------------------------------------------------------*/

#define DSTRING_CHUNK_SIZE 32

struct fmm_type *memtype_nstr;
struct fmm_type *memtype_dstr;

/*** Functions for manipulating nstrings.
 **/

/*
 * Allocate n characters for a nstring.
 */
static char*
nstring_alloc(size_t n)
{
	char *s;

	if (memtype_nstr == NULL)
		memtype_nstr = fmm_type_add ("NStrings", "Character strings");
	s = fmm_malloc (n, memtype_nstr);
	return s;
}

void
nstring_init(NStringP nstring)
{
	nstring->ns_length   = 0;
	nstring->ns_contents = NULL;
}

void
nstring_init_length(NStringP nstring, size_t length)
{
	nstring->ns_length   = length;
	nstring->ns_contents = nstring_alloc (length);
}

void
nstring_assign(NStringP to, NStringP from)
{
	to->ns_length     = nstring_length (from);
	to->ns_contents   = (from->ns_contents);
}

void
nstring_copy_cstring(NStringP nstring, const char *cstring)
{
	size_t length = strlen (cstring);
	
	if (length > 0) {
		nstring->ns_length   = length;
		nstring->ns_contents = nstring_alloc (length);
		(void) memcpy (nstring->ns_contents, cstring, length);
	} else {
		nstring->ns_length   = 0;
		nstring->ns_contents = NULL;
	}
}

void
nstring_insert_cstring(NStringP nstring, const char *cstring)
{
	size_t length = nstring_length (nstring);
	
	if (length > 0) {
		(void) memcpy (nstring->ns_contents, cstring, length);
	}
}

void
nstring_copy(NStringP to, NStringP from)
{
	size_t length = nstring_length (from);
	
	if (length > 0) {
		to->ns_length   = length;
		to->ns_contents =  nstring_alloc(length);
		(void) memcpy (to->ns_contents, from->ns_contents, length);
	} else {
		to->ns_length   = 0;
		to->ns_contents = NULL;
	}
}

char *
nstring_to_cstring(NStringP nstring)
{
	size_t length = nstring_length (nstring);
	char *tmp = string_alloc(length + 1);
	
	if (length > 0) {
		(void) memcpy (tmp, nstring->ns_contents, length);
	}
	tmp [length] = '\0';
	return (tmp);
}

unsigned
nstring_hash_value(NStringP nstring)
{
	unsigned value        = 0;
	const char *tmp_contents = (nstring->ns_contents);
	size_t tmp_length   = nstring_length (nstring);
	
	while (tmp_length--) {
		value += (unsigned) (*tmp_contents++);
	}
	return (value);
}

CmpT
nstring_compare(NStringP nstring1, NStringP nstring2)
{
	size_t length = nstring_length (nstring1);
	int      status;
	
	if (length > nstring_length (nstring2)) {
		length = nstring_length (nstring2);
	}
	status = memcmp (nstring1->ns_contents, nstring2->ns_contents, length);
	if (status < 0) {
		return (CMP_LT);
	} else if (status > 0) {
		return (CMP_GT);
	} else if (nstring_length (nstring1) < nstring_length (nstring2)) {
		return (CMP_LT);
	} else if (nstring_length (nstring1) > nstring_length (nstring2)) {
		return (CMP_GT);
	} else {
		return (CMP_EQ);
	}
}

BoolT
nstring_equal(NStringP nstring1, NStringP nstring2)
{
	size_t length = nstring_length (nstring1);
	
	return ((length == nstring_length (nstring2)) &&
			(memcmp (nstring1->ns_contents, nstring2->ns_contents, length) == 0));
}

BoolT
nstring_ci_equal(NStringP nstring1, NStringP nstring2)
{
	size_t length = nstring_length (nstring1);
	
	if (length == nstring_length (nstring2)) {
		const char *tmp1 = (nstring1->ns_contents);
		const char *tmp2 = (nstring2->ns_contents);
		char c1;
		char c2;
		
		do {
			c1 = toupper (*tmp1++);
			c2 = toupper (*tmp2++);
			if (length-- == 0) {
				return (TRUE);
			}
		} while (c1 == c2);
	}
	return (FALSE);
}

BoolT
nstring_contains(NStringP nstring, char c)
{
	const char *contents = nstring_contents (nstring);
	size_t length   = nstring_length (nstring);
	
	return (memchr (contents, c, length) != NULL);
}

BoolT
nstring_is_prefix(NStringP nstring1, NStringP nstring2)
{
	const char *contents1 = nstring_contents (nstring1);
	const char *contents2 = nstring_contents (nstring2);
	size_t length    = nstring_length (nstring2);
	
	return ((length < nstring_length (nstring1)) &&
			(memcmp (contents1, contents2, length) == 0));
}

void
nstring_destroy(NStringP nstring)
{
	fmm_free (nstring->ns_contents, memtype_nstr);
}

void
write_nstring(OStreamP ostream, NStringP nstring)
{
	size_t length = nstring_length (nstring);
	
	if (length > 0) {
		write_chars (ostream, nstring->ns_contents, length);
	}
}

/*** Functions for manipulating dstrings.
 **/

/*
 * Allocate n characters for a dstring.
 */
static char*
dstring_alloc(size_t n)
{
	char *s;

	if (memtype_dstr == NULL)
		memtype_dstr = fmm_type_add ("DStrings", "Binary strings");
	s = fmm_malloc (n, memtype_dstr);
	return s;
}

void
dstring_init(DStringP dstring)
{
	dstring->ds_length     = 0;
	dstring->ds_max_length = DSTRING_CHUNK_SIZE;
	dstring->ds_contents   = dstring_alloc (dstring->ds_max_length);
}

void
dstring_append_char(DStringP dstring, char c)
{
	if ((dstring->ds_length) >= (dstring->ds_max_length)) {
		dstring->ds_max_length += DSTRING_CHUNK_SIZE;
		dstring->ds_contents = fmm_realloc (dstring->ds_contents,
			dstring->ds_max_length, memtype_dstr);
	}
	dstring->ds_contents[dstring->ds_length++] = c;
}

void
dstring_append_cstring(DStringP dstring, const char *cstring)
{
	size_t clength = strlen (cstring);
	size_t length  = (clength + (dstring->ds_length));
	
	if (length > (dstring->ds_max_length)) {
		while ((dstring->ds_max_length) < length) {
			dstring->ds_max_length += DSTRING_CHUNK_SIZE;
		}
		dstring->ds_contents = fmm_realloc (dstring->ds_contents,
			dstring->ds_max_length, memtype_dstr);
	}
	(void) memcpy (dstring->ds_contents + dstring->ds_length, cstring, clength);
	dstring->ds_length = length;
}

void
dstring_append_nstring(DStringP dstring, NStringP nstring)
{
	size_t nlength = nstring_length (nstring);
	size_t length  = nlength + dstring->ds_length;
	
	if (length > dstring->ds_max_length) {
		while (dstring->ds_max_length < length) {
			dstring->ds_max_length += DSTRING_CHUNK_SIZE;
		}
		dstring->ds_contents = fmm_realloc (dstring->ds_contents,
			dstring->ds_max_length, memtype_dstr);
	}
	(void) memcpy (dstring->ds_contents + dstring->ds_length,
				   nstring_contents (nstring), nlength);
	dstring->ds_length = length;
}

BoolT
dstring_last_char_equal(DStringP dstring, char c)
{
	return (dstring->ds_length &&
			(dstring->ds_contents[dstring->ds_length - 1] == c));
}

void
dstring_to_nstring(DStringP dstring, NStringP nstring)
{
	if (dstring->ds_length > 0) {
		nstring->ns_length   = dstring->ds_length;
 		nstring->ns_contents = nstring_alloc(dstring->ds_length);
		(void) memcpy (nstring->ns_contents, dstring->ds_contents,
					   dstring->ds_length);
	} else {
		nstring->ns_length   = 0;
		nstring->ns_contents = NULL;
	}
}

char *
dstring_to_cstring(DStringP dstring)
{
	char *tmp = string_alloc(dstring->ds_length + 1);
	
	if (dstring->ds_length > 0) {
		(void) memcpy (tmp, dstring->ds_contents, dstring->ds_length);
	}
	tmp[dstring->ds_length] = '\0';
	return (tmp);
}

char *
dstring_destroy_to_cstring(DStringP dstring)
{
	char *tmp;
	
	tmp = dstring_to_cstring (dstring);
	dstring_destroy (dstring);
	dstring->ds_length       = 0;
	dstring->ds_max_length   = 0;
	dstring->ds_contents     = NULL;
	return (tmp);
}

void
dstring_destroy(DStringP dstring)
{
	fmm_free (dstring->ds_contents, memtype_dstr);
}
