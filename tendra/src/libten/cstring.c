/*
 * Copyright (c) 2003-2004, by Boris Popov
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
 * $TenDRA$
 */

#include <ctype.h>
#include <limits.h>
#include <string.h>
#include "fmm.h"

struct fmm_type *memtype_str;

/*
 * Allocate n characters for a string.
 */
char*
string_alloc(size_t n)
{
	char *s;

	if (memtype_str == NULL)
		memtype_str = fmm_type_add("Strings", "Character strings");
	s = fmm_malloc(n, memtype_str);
	return s;
}

void
string_free(char *s)
{
	fmm_free(s, memtype_str);
}


/*
 * Duplicate a string by allocating a new one.
 */
char*
string_copy(const char *src)
{
	size_t n;

	if (src == NULL)
		return NULL;
	n = strlen(src);
	return strcpy(string_alloc(n + 1), src);
}

/*
 * Duplicate only n characters from a string.
 */
char*
string_ncopy(const char *src, size_t n)
{
	char *dst;

	dst = string_alloc(n + 1);
	strncpy(dst, src, n);
	dst[n] = 0;
	return dst;
}


/*
 * Concatenate two strings, the result placed into its own memory.
 */
char*
string_concat(const char *s1, const char *s2)
{
	size_t l1, l2;
	char *dst;

	if (s1 == NULL)
		return string_copy(s2);
	if (s2 == NULL)
		return string_copy(s1);
	l1 = strlen(s1);
	l2 = strlen(s2);
	dst = string_alloc(l1 + l2 + 1);
	strcpy(dst, s1);
	strcpy(dst + l1, s2);
	return dst;
}

/*
 * Join two strings using delimiter.
 * The result placed in its own memory.
 */

char*
string_join(const char *s1, const char *s2, char delimeter)
{
	size_t l1, l2;
	char *dst;

	l1 = strlen(s1);
	l2 = strlen(s2);
	dst = string_alloc(l1 + l2 + 2);

	strcpy(dst, s1);
	dst[l1] = delimeter;
	strcpy(dst + l1 + 1, s2);
	return dst;
}

int
string_to_unsigned(const char *cp, unsigned *rp)
{
	unsigned result, digit;
	
	if (*cp == '\0')
		return (0);
	result = 0;
	for (; *cp; cp++) {
		if (*cp < '0' || *cp > '9')
			return (0);
		digit = *cp - '0';

		if (((UINT_MAX - digit) / 10) < result) {
			return (0);
		}
		result = result * 10 + digit;
	}
	*rp = result;
	return (1);
}

/*
 * Do a case-insensitive string comparison.
 */
int
string_casecmp(const char *s1, const char *s2)
{
	for (; *s1 != '\0'; s1++, s2++)
		if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2))
			break;
	return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}
