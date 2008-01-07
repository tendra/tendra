/*
 * Copyright (c) 2005, The Tendra Project <http://www.ten15.org/>
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

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "fmm.h"

#include "str_array.h"


/*
 * INIT A STR_ARRAY OBJECT
 *
 * This function must be called to initialise a string array object.
 */

void
str_array_init(struct str_array *sa)
{
	sa->p = xalloc (32 * sizeof (*sa->p));
	sa->used = 0;
	sa->reserved = 32;
}


/*
 * ADD A STRING
 *
 * This function adds a string to the end of the array.
 */

void
str_array_add(struct str_array *sa, char *s)
{
	if (sa->used >= sa->reserved) {
		sa->reserved *= 2;
		sa->p = xrealloc (sa->p, sa->reserved * sizeof (sa->p [0]));
	}
	sa->p [sa->used++] = s;
}


/*
 * GET A STRING
 *
 * This function returns the string with the index idx.
 */

char *
str_array_get(const struct str_array *sa, int idx)
{
	assert (idx >= 0 && idx < sa->used);

	return (sa->p [idx]);
}


/*
 * COMPARE FUNCTION
 *
 * This is a helper function for str_array_sort.
 */

static int
str_array_cmp(const void *a, const void *b)
{
	char * const *pa = a;
	char * const *pb = b;

	return (strcmp (*pa, *pb));
}


/*
 * SORT FUNCTION
 *
 * This function sorts the strings in the array alphabetically.
 */

void
str_array_sort(struct str_array *sa)
{
	qsort (sa->p, sa->used, sizeof (sa->p [0]), str_array_cmp);
}


/*
 * GET THE ARRAY SIZE
 *
 * This function returns the number of entries in the array.
 */

int
str_array_size(const struct str_array *sa)
{
	return (sa->used);
}


/*
 * CLEAR FUNCTION
 *
 * This functions clear all strings in the array.
 */

void
str_array_clear(struct str_array *sa)
{
	sa->used = 0;
}


/*
 * DESTROY FUNCTION
 *
 * This function should be called after the last usage of the string array.
 */

void
str_array_destroy(struct str_array *sa)
{
	sa->p = NULL;
	xfree (sa->p);
}
