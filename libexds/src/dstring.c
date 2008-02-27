/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
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

#include "common.h"
#include "exception.h"
#include "ostream.h"
#include "dalloc.h"
#include "dstring.h"

#define DSTRING_CHUNK_SIZE 32

/*
 * Functions for manipulating nstrings.
 */

void
nstring_init(NStringT * nstring)
{
    nstring->length   = 0;
    nstring->contents = NULL;
}

void
nstring_init_length(NStringT * nstring, unsigned length)
{
    nstring->length   = length;
    nstring->contents = ALLOCATE_VECTOR(char, length);
}

void
nstring_assign(NStringT * to, NStringT * from)
{
    to->length     = nstring_length(from);
    to->contents   = (from->contents);
}

void
nstring_copy_cstring(NStringT * nstring, char * cstring)
{
    unsigned length = strlen(cstring);

    if (length > 0) {
	nstring->length   = length;
	nstring->contents = ALLOCATE_VECTOR(char, length);
	(void)memcpy((nstring->contents), cstring,
		     (size_t)length);
    } else {
	nstring->length   = 0;
	nstring->contents = NULL;
    }
}

void
nstring_insert_cstring(NStringT * nstring, char * cstring)
{
    unsigned length = nstring_length(nstring);

    if (length > 0) {
	(void)memcpy((nstring->contents), cstring,
		     (size_t)length);
    }
}

void
nstring_copy(NStringT * to, NStringT * from)
{
    unsigned length = nstring_length(from);

    if (length > 0) {
	to->length   = length;
	to->contents = ALLOCATE_VECTOR(char, length);
	(void)memcpy((to->contents),
		     (from->contents), (size_t)length);
    } else {
	to->length   = 0;
	to->contents = NULL;
    }
}

char *
nstring_to_cstring(NStringT * nstring)
{
    unsigned length = nstring_length(nstring);
    char * tmp    = ALLOCATE_VECTOR(char, length + 1);

    if (length > 0) {
	(void)memcpy(tmp, (nstring->contents),
		     (size_t)length);
    }
    tmp[length] = '\0';
    return(tmp);
}

unsigned
nstring_hash_value(NStringT * nstring)
{
    unsigned value        = 0;
    char * tmp_contents = (nstring->contents);
    unsigned tmp_length   = nstring_length(nstring);

    while (tmp_length--) {
	value += ((unsigned)(*tmp_contents++));
    }
    return(value);
}

unsigned
nstring_length(NStringT * nstring)
{
    return(nstring->length);
}

char *
nstring_contents(NStringT * nstring)
{
    return(nstring->contents);
}

CmpT
nstring_compare(NStringT * nstring1, NStringT * nstring2)
{
    unsigned length = nstring_length(nstring1);
    int      status;

    if (length > nstring_length(nstring2)) {
	length = nstring_length(nstring2);
    }
    status = memcmp((nstring1->contents),
		    (nstring2->contents), (size_t)length);
    if (status < 0) {
	return(CMP_LT);
    } else if (status > 0) {
	return(CMP_GT);
    } else if (nstring_length(nstring1) < nstring_length(nstring2)) {
	return(CMP_LT);
    } else if (nstring_length(nstring1) > nstring_length(nstring2)) {
	return(CMP_GT);
    } else {
	return(CMP_EQ);
    }
}

BoolT
nstring_equal(NStringT * nstring1, NStringT * nstring2)
{
    unsigned length = nstring_length(nstring1);

    return((length == nstring_length(nstring2)) &&
	   (memcmp((nstring1->contents),
		   (nstring2->contents), (size_t)length) == 0));
}

BoolT
nstring_ci_equal(NStringT * nstring1, NStringT * nstring2)
{
    unsigned length = nstring_length(nstring1);

    if (length == nstring_length(nstring2)) {
	char * tmp1 = (nstring1->contents);
	char * tmp2 = (nstring2->contents);
	char c1;
	char c2;

	do {
	    c1 = toupper((unsigned char)*tmp1++);
	    c2 = toupper((unsigned char)*tmp2++);
	    if (length-- == 0) {
		return(TRUE);
	    }
	} while (c1 == c2);
    }
    return(FALSE);
}

BoolT
nstring_contains(NStringT * nstring, char c)
{
    char * contents = nstring_contents(nstring);
    unsigned length   = nstring_length(nstring);

    return(memchr(contents, c, (size_t)length) != NULL);
}

BoolT
nstring_is_prefix(NStringT * nstring1,			   NStringT * nstring2)
{
    char * contents1 = nstring_contents(nstring1);
    char * contents2 = nstring_contents(nstring2);
    unsigned length    = nstring_length(nstring2);

    return((length < nstring_length(nstring1)) &&
	   (memcmp(contents1, contents2,
		   (size_t)length) == 0));
}

void
nstring_destroy(NStringT * nstring)
{
    DEALLOCATE(nstring->contents);
}

void
write_nstring(OStreamT * ostream, NStringT * nstring)
{
    unsigned length = nstring_length(nstring);

    if (length > 0) {
	write_chars(ostream, nstring->contents, length);
    }
}


/*
 * Functions for manipulating dstrings.
 */

void
dstring_init(DStringT * dstring)
{
    dstring->length     = 0;
    dstring->max_length = DSTRING_CHUNK_SIZE;
    dstring->contents   = ALLOCATE_VECTOR(char, dstring->max_length);
}

unsigned
dstring_length(DStringT * dstring)
{
    return(dstring->length);
}

void
dstring_assign(DStringT * to, DStringT * from)
{
    to->length     = dstring_length(from);
    to->max_length = from->max_length;
    to->contents   = (from->contents);
}

void
dstring_append_char(DStringT * dstring, char c)
{
    if ((dstring->length) >= (dstring->max_length)) {
	char * tmp;

	dstring->max_length += DSTRING_CHUNK_SIZE;
	tmp                  = ALLOCATE_VECTOR(char, dstring->max_length);
	(void)memcpy(tmp, (dstring->contents),
		     (size_t)(dstring->length));
	DEALLOCATE(dstring->contents);
	dstring->contents = tmp;
    }
    dstring->contents[dstring->length++] = c;
}

void
dstring_append_cstring(DStringT * dstring, char * cstring)
{
    unsigned clength = strlen(cstring);
    unsigned length  = (clength + (dstring->length));

    if (length > (dstring->max_length)) {
	char * tmp;

	while ((dstring->max_length) < length) {
	    dstring->max_length += DSTRING_CHUNK_SIZE;
	}
	tmp = ALLOCATE_VECTOR(char, dstring->max_length);
	(void)memcpy(tmp, (dstring->contents),
		     (size_t)(dstring->length));
	DEALLOCATE(dstring->contents);
	dstring->contents = tmp;
    }
  (void)memcpy( & (dstring->contents[dstring->length]),
	       cstring, (size_t)clength);
    dstring->length = length;
}

void
dstring_append_nstring(DStringT * dstring, NStringT * nstring)
{
    unsigned nlength = nstring_length(nstring);
    unsigned length  = (nlength + (dstring->length));

    if (length > (dstring->max_length)) {
	char * tmp;

	while ((dstring->max_length) < length) {
	    dstring->max_length += DSTRING_CHUNK_SIZE;
	}
	tmp = ALLOCATE_VECTOR(char, dstring->max_length);
	(void)memcpy(tmp, (dstring->contents),
		     (size_t)(dstring->length));
	DEALLOCATE(dstring->contents);
	dstring->contents = tmp;
    }
  (void)memcpy( & (dstring->contents[dstring->length]),
	       nstring_contents(nstring), (size_t)nlength);
    dstring->length = length;
}

BoolT
dstring_last_char_equal(DStringT * dstring, char c)
{
    return((dstring->length) &&
	   ((dstring->contents[dstring->length - 1]) == c));
}

void
dstring_to_nstring(DStringT * dstring, NStringT * nstring)
{
    if (dstring->length > 0) {
	nstring->length   = (dstring->length);
	nstring->contents = ALLOCATE_VECTOR(char, dstring->length);
	(void)memcpy((nstring->contents),
		     (dstring->contents),
		     (size_t)(dstring->length));
    } else {
	nstring->length   = 0;
	nstring->contents = NULL;
    }
}

char *
dstring_to_cstring(DStringT * dstring)
{
    char * tmp = ALLOCATE_VECTOR(char, dstring->length + 1);

    if (dstring->length > 0) {
	(void)memcpy(tmp, (dstring->contents),
		     (size_t)(dstring->length));
    }
    tmp[dstring->length] = '\0';
    return(tmp);
}

char *
dstring_destroy_to_cstring(DStringT * dstring)
{
    char * tmp;

    if ((dstring->length) >= (dstring->max_length)) {
	tmp = ALLOCATE_VECTOR(char, (dstring->length) + 1);
	(void)memcpy(tmp, (dstring->contents),
		     (size_t)(dstring->length));
	DEALLOCATE(dstring->contents);
    } else {
	tmp = (dstring->contents);
    }
    tmp[dstring->length] = '\0';
    dstring->length       = 0;
    dstring->max_length   = 0;
    dstring->contents     = NULL;
    return(tmp);
}

void
dstring_destroy(DStringT * dstring)
{
    DEALLOCATE(dstring->contents);
}
