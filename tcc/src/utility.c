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


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "xalloc.h"

#include "config.h"
#include "list.h"
#include "environ.h"
#include "flags.h"
#include "main.h"
#include "options.h"
#include "suffix.h"
#include "utility.h"


/*
 * PRINT A COMMENT
 *
 * This routine prints the comments (a printf-style string, which may be
 * followed by any number of arguments) to the standard output.
 */
void
comment(int e, char *s, ...)
{
	FILE *f;
	va_list args;

	va_start(args, s);
	f = (e ? stdout : stderr);
	IGNORE fflush(f);
	IGNORE vfprintf(f, s, args);
	IGNORE fflush(f);
	va_end(args);
}


/*
 * ALLOCATE SPACE FOR A STRING
 *
 * This routine allocates n characters of memory for use in the string memory
 * allocation routines.
 */
/* TODO: this is an unneccessary optimisation */
static char *
string_alloc(int n)
{
	char *r;
	if (n >= 1000) {
		/* Long strings are allocated space by alloc_nof */
		r = xmalloc_nof(char, n);
	} else {
		/* Short strings are allocated space from a buffer */
		static int no_free;
		static char *free_chars;

		no_free = 0;
		free_chars = NULL;
		if (n >= no_free) {
			no_free = 4000;
			free_chars = xmalloc_nof(char, no_free);
		}
		r = free_chars;
		no_free -= n;
		free_chars += n;
	}

	return r;
}


/*
 * COPY A STRING
 *
 * This routine allocates space for a copy of the string s and copies the
 * string into this space. This copy is returned.
 */
/* TODO rename to xstrdup(), move to shared/ */
char *
string_copy(const char *s)
{
	size_t n;
	char *r;

	n = strlen(s);
	r = string_alloc(n + 1);
	IGNORE strcpy(r, s);

	return r;
}


/*
 * COPY TWO STRINGS
 *
 * This routine allocates space for a copy of the string s followed by a copy
 * of the string t and concatenates the strings into this space. This copy is
 * returned.
 */
char *
string_concat(const char *s, const char *t)
{
	size_t n, m;
	char *r;

	n = strlen(s);
	m = strlen(t);

	r = string_alloc(n + m + 1);
	IGNORE strcpy(r, s);
	IGNORE strcpy(r + n, t);

	return r;
}


/*	
 * APPEND TWO STRINGS	
 *   
 * This routine allocates space for a copy of the string s followed by a copy
 * of the string t and concatenates the strings into this space, placing the
 * delimiter character between them. The copy is returned.  E.g.,:	
 *   
 * Given:    "foo" + "bar" + ':'	
 * Returns:  "foo:bar"	
 */	
 	 	
char *	
string_append(const char *s, const char *t, char delimeter)	
{	
	int n = (int)strlen(s);	
	int m = (int)strlen(t);	
	char *r = string_alloc(n + m + 2);	
	IGNORE strcpy(r, s);	
	*(r + n) = delimeter;	
	IGNORE strcpy(r + n + 1, t);	
	return r;
}


/*
 * TEMPORARY WORK SPACE
 *
 * This variable gives a temporary work space of size buffer_size (see
 * utility.h) which is used as a scratch work area.
 */
char *buffer;

