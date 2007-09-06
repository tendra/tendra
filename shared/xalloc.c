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

#include <errno.h>
/* XXX: #include <stdint.h> for SIZE_MAX */
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "xalloc.h"


/*
    CONTROLLED VERSION OF MALLOC

    All the program's memory allocation is through the routines defined in
    this file.  This routine allocates sz bytes of memory.
*/

void *
xmalloc(size_t sz)
{
	void *p = malloc(sz);

	if (p == NULL)
		error(ERROR_FATAL, "malloc: %s", strerror(errno));

	return (p);
}


/*
    CONTROLLED VERSION OF CALLOC

    This routine allocates and initializes n objects of size sz bytes.
*/

void *
xcalloc(size_t n, size_t sz)
{
	void *p;

	if (n == 0 || sz == 0)
		error(ERROR_FATAL, "xcalloc: zero size allocation");

	/* XXX: if (SIZE_MAX / n < sz)
		error(ERROR_FATAL, "xcalloc: size_t overflow"); */

	if ((p = calloc(sz, n)) == NULL)
		error(ERROR_FATAL, "calloc: %s", strerror(errno));

	return (p);
}


/*
    CONTROLLED VERSION OF REALLOC

    This routine reallocates the block of memory p to contain sz bytes.
    p can be the result of a previous memory allocation routine, or NULL.
*/

void *
xrealloc(void *p, size_t sz)
{
	void *q;

	if (p == NULL && sz == 0)
		error(ERROR_FATAL, "xrealloc: both arguments zero is unspecified");

	/* This is legal and frees p, but confusing */
	if (sz == 0)
		error(ERROR_FATAL, "xrealloc: size is zero, use xfree()");

	if ((q = realloc(p, sz)) == NULL)
		error(ERROR_FATAL, "realloc: %s", strerror(errno));

	return (q);
}


/*
    CONTROLLED VERSION OF FREE

    This routine frees the block of memory p.  p can be the result of a
    previous memory allocation routine, or NULL.
*/

void
xfree(void *p)
{
	/* safe a function call if p is NULL */
	if (p)
		free(p);
}


char *
xstrdup(const char *s1)
{
	size_t len;
	char *s2;

	len = strlen(s1) + 1;
	s2 = xmalloc(len);
	(void) strcpy(s2, s1);

	return (s2);
}


/*
    ALLOCATE SPACE FOR A STRING

    This routine allocates space for n characters.  The memory allocation
    is buffered except for very long strings.
*/

char *
xstr(size_t n)
{
    char *r;
    if (n >= 1000) {
	r = xmalloc_nof(char, n);
    } else {
	static size_t chars_left = 0;
	static char *chars_free = 0;

	if (n >= chars_left) {
	    chars_left = 5000;
	    chars_free = xmalloc_nof(char, chars_left);
	}
	r = chars_free;
	chars_free += n;
	chars_left -= n;
    }
    return(r);
}


/*
    COPY A STRING

    This routine allocates space for a persistent copy of the string s.
*/

char *
xstrcpy(const char *s)
{
    return(xstrdup(s));
}


/*
    CONCATENATE TWO STRINGS

    This routine allocates space for a persistent copy of the string s
    followed by the string t.
*/

char *
xstrcat(const char *s, const char *t)
{
    char *r;
    size_t n, m;

    if (s == NULL) return(xstrcpy(t));
    if (t == NULL) return(xstrcpy(s));

    n = strlen(s);
    m = n + strlen(t) + 1;
    r = xstr(m);
    (void) strcpy(r, s);
    (void) strcpy(r + n, t);
    return(r);
}
