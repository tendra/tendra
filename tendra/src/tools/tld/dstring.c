/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
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
 *
 **** Change Log:*/

/****************************************************************************/

#include "dstring.h"
#include "syntax.h"

/*--------------------------------------------------------------------------*/

#define DSTRING_CHUNK_SIZE 32

/*** Functions for manipulating nstrings.
 **/

void
nstring_init(NStringP nstring)
{
    nstring->length   = 0;
    nstring->contents = NIL (CStringP);
}

void
nstring_init_length(NStringP nstring, unsigned length)
{
    nstring->length   = length;
    nstring->contents = ALLOCATE_VECTOR (char, length);
}

void
nstring_assign(NStringP to, NStringP from)
{
    to->length     = nstring_length (from);
    to->contents   = (from->contents);
}

void
nstring_copy_cstring(NStringP nstring, CStringP cstring)
{
    unsigned length = cstring_length (cstring);

    if (length > 0) {
		nstring->length   = length;
		nstring->contents = ALLOCATE_VECTOR (char, length);
		(void) memcpy ((GenericP) (nstring->contents), (GenericP) cstring,
					   (SizeT) length);
    } else {
		nstring->length   = 0;
		nstring->contents = NIL (CStringP);
    }
}

void
nstring_insert_cstring(NStringP nstring, CStringP cstring)
{
    unsigned length = nstring_length (nstring);

    if (length > 0) {
		(void) memcpy ((GenericP) (nstring->contents), (GenericP) cstring,
					   (SizeT) length);
    }
}

void
nstring_copy(NStringP to, NStringP from)
{
    unsigned length = nstring_length (from);

    if (length > 0) {
		to->length   = length;
		to->contents = ALLOCATE_VECTOR (char, length);
		(void) memcpy ((GenericP) (to->contents),
					   (GenericP) (from->contents), (SizeT) length);
    } else {
		to->length   = 0;
		to->contents = NIL (CStringP);
    }
}

CStringP
nstring_to_cstring(NStringP nstring)
{
    unsigned length = nstring_length (nstring);
    CStringP tmp    = ALLOCATE_VECTOR (char, length + 1);

    if (length > 0) {
		(void) memcpy ((GenericP) tmp, (GenericP) (nstring->contents),
					   (SizeT) length);
    }
    tmp [length] = '\0';
    return (tmp);
}

unsigned
nstring_hash_value(NStringP nstring)
{
    unsigned value        = 0;
    CStringP tmp_contents = (nstring->contents);
    unsigned tmp_length   = nstring_length (nstring);

    while (tmp_length --) {
		value += ((unsigned) (*tmp_contents ++));
    }
    return (value);
}

#ifdef FS_FAST
#undef nstring_length
#endif /* defined (FS_FAST) */
unsigned
nstring_length(NStringP nstring)
{
    return (nstring->length);
}
#ifdef FS_FAST
#define nstring_length(s) ((s)->length)
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef nstring_contents
#endif /* defined (FS_FAST) */
CStringP
nstring_contents(NStringP nstring)
{
    return (nstring->contents);
}
#ifdef FS_FAST
#define nstring_contents(s) ((s)->contents)
#endif /* defined (FS_FAST) */

CmpT
nstring_compare(NStringP nstring1, NStringP nstring2)
{
    unsigned length = nstring_length (nstring1);
    int      status;

    if (length > nstring_length (nstring2)) {
		length = nstring_length (nstring2);
    }
    status = memcmp ((GenericP) (nstring1->contents),
					 (GenericP) (nstring2->contents), (SizeT) length);
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
    unsigned length = nstring_length (nstring1);

    return ((length == nstring_length (nstring2)) &&
			(memcmp ((GenericP) (nstring1->contents),
					 (GenericP) (nstring2->contents), (SizeT) length) == 0));
}

BoolT
nstring_ci_equal(NStringP nstring1, NStringP nstring2)
{
    unsigned length = nstring_length (nstring1);

    if (length == nstring_length (nstring2)) {
		CStringP tmp1 = (nstring1->contents);
		CStringP tmp2 = (nstring2->contents);
		char c1;
		char c2;

		do {
			c1 = syntax_upcase (*tmp1 ++);
			c2 = syntax_upcase (*tmp2 ++);
			if (length -- == 0) {
				return (TRUE);
			}
		} while (c1 == c2);
    }
    return (FALSE);
}

BoolT
nstring_contains(NStringP nstring, char c)
{
    CStringP contents = nstring_contents (nstring);
    unsigned length   = nstring_length (nstring);

    return (memchr ((GenericP) contents, c, (SizeT) length) != NIL (GenericP));
}

BoolT
nstring_is_prefix(NStringP nstring1, NStringP nstring2)
{
    CStringP contents1 = nstring_contents (nstring1);
    CStringP contents2 = nstring_contents (nstring2);
    unsigned length    = nstring_length (nstring2);

    return ((length < nstring_length (nstring1)) &&
			(memcmp ((GenericP) contents1, (GenericP) contents2,
					 (SizeT) length) == 0));
}

void
nstring_destroy(NStringP nstring)
{
    DEALLOCATE (nstring->contents);
}

void
write_nstring(OStreamP ostream, NStringP nstring)
{
    unsigned length = nstring_length (nstring);

    if (length > 0) {
		write_chars (ostream, nstring->contents, length);
    }
}

/*** Functions for manipulating dstrings.
 **/

void
dstring_init(DStringP dstring)
{
    dstring->length     = 0;
    dstring->max_length = DSTRING_CHUNK_SIZE;
    dstring->contents   = ALLOCATE_VECTOR (char, dstring->max_length);
}

#ifdef FS_FAST
#undef dstring_length
#endif /* defined (FS_FAST) */
unsigned
dstring_length(DStringP dstring)
{
    return (dstring->length);
}
#ifdef FS_FAST
#define dstring_length(s) ((s)->length)
#endif /* defined (FS_FAST) */

void
dstring_append_char(DStringP dstring, char c)
{
    if ((dstring->length) >= (dstring->max_length)) {
		CStringP tmp;

		dstring->max_length += DSTRING_CHUNK_SIZE;
		tmp                  = ALLOCATE_VECTOR (char, dstring->max_length);
		(void) memcpy ((GenericP) tmp, (GenericP) (dstring->contents),
					   (SizeT) (dstring->length));
		DEALLOCATE (dstring->contents);
		dstring->contents = tmp;
    }
    dstring->contents [dstring->length ++] = c;
}

void
dstring_append_cstring(DStringP dstring, CStringP cstring)
{
    unsigned clength = cstring_length (cstring);
    unsigned length  = (clength + (dstring->length));

    if (length > (dstring->max_length)) {
		CStringP tmp;

		while ((dstring->max_length) < length) {
			dstring->max_length += DSTRING_CHUNK_SIZE;
		}
		tmp = ALLOCATE_VECTOR (char, dstring->max_length);
		(void) memcpy ((GenericP) tmp, (GenericP) (dstring->contents),
					   (SizeT) (dstring->length));
		DEALLOCATE (dstring->contents);
		dstring->contents = tmp;
    }
    (void) memcpy ((GenericP) &(dstring->contents [dstring->length]),
				   (GenericP) cstring, (SizeT) clength);
    dstring->length = length;
}

void
dstring_append_nstring(DStringP dstring, NStringP nstring)
{
    unsigned nlength = nstring_length (nstring);
    unsigned length  = (nlength + (dstring->length));

    if (length > (dstring->max_length)) {
		CStringP tmp;

		while ((dstring->max_length) < length) {
			dstring->max_length += DSTRING_CHUNK_SIZE;
		}
		tmp = ALLOCATE_VECTOR (char, dstring->max_length);
		(void) memcpy ((GenericP) tmp, (GenericP) (dstring->contents),
					   (SizeT) (dstring->length));
		DEALLOCATE (dstring->contents);
		dstring->contents = tmp;
    }
    (void) memcpy ((GenericP) &(dstring->contents [dstring->length]),
				   (GenericP) nstring_contents (nstring), (SizeT) nlength);
    dstring->length = length;
}

BoolT
dstring_last_char_equal(DStringP dstring,
						char c)
{
    return ((dstring->length) &&
			((dstring->contents [dstring->length - 1]) == c));
}

void
dstring_to_nstring(DStringP dstring, NStringP nstring)
{
    if (dstring->length > 0) {
		nstring->length   = (dstring->length);
		nstring->contents = ALLOCATE_VECTOR (char, dstring->length);
		(void) memcpy ((GenericP) (nstring->contents),
					   (GenericP) (dstring->contents),
					   (SizeT) (dstring->length));
    } else {
		nstring->length   = 0;
		nstring->contents = NIL (CStringP);
    }
}

CStringP
dstring_to_cstring(DStringP dstring)
{
    CStringP tmp = ALLOCATE_VECTOR (char, dstring->length + 1);

    if (dstring->length > 0) {
		(void) memcpy ((GenericP) tmp, (GenericP) (dstring->contents),
					   (SizeT) (dstring->length));
    }
    tmp [dstring->length] = '\0';
    return (tmp);
}

CStringP
dstring_destroy_to_cstring(DStringP dstring)
{
    CStringP tmp;

    if ((dstring->length) >= (dstring->max_length)) {
		tmp = ALLOCATE_VECTOR (char, (dstring->length) + 1);
		(void) memcpy ((GenericP) tmp, (GenericP) (dstring->contents),
					   (SizeT) (dstring->length));
		DEALLOCATE (dstring->contents);
    } else {
		tmp = (dstring->contents);
    }
    tmp [dstring->length] = '\0';
    dstring->length       = 0;
    dstring->max_length   = 0;
    dstring->contents     = NIL (CStringP);
    return (tmp);
}

void
dstring_destroy(DStringP dstring)
{
    DEALLOCATE (dstring->contents);
}

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../generated")
 * end:
 **/
