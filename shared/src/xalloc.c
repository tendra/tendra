/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>

#include <shared/error.h>
#include <shared/xalloc.h>

/* SIZE_MAX is not in C90 */
#ifndef SIZE_MAX
# define SIZE_MAX ((size_t) -1)
#endif

/*
 * CONTROLLED VERSION OF MALLOC
 *
 * This routine allocates sz bytes of memory and bails out on error.
*/
void *
xmalloc(size_t sz)
{
	void *p;

	assert(sz != 0);

	p = malloc(sz);
	if (p == NULL) {
		error(ERROR_FATAL, "malloc");
	}

	return p;
}

/*
 * CONTROLLED VERSION OF CALLOC
 *
 * This routine allocates and initializes n objects of size sz bytes.
 */
void *
xcalloc(size_t n, size_t sz)
{
	void *p;

	assert(n != 0);
	assert(sz != 0);

	if (SIZE_MAX / n < sz) {
		error(ERROR_FATAL, "xcalloc: size_t overflow");
	}

	p = calloc(sz, n);
	if (p == NULL) {
		error(ERROR_FATAL, "calloc");
	}

	return p;
}

/*
 * CONTROLLED VERSION OF REALLOC
 *
 * This routine reallocates the block of memory p to contain sz bytes.
 * p can be the result of a previous memory allocation routine, or NULL.
 */
void *
xrealloc(void *p, size_t sz)
{
	void *q;

	assert(p != NULL || sz != 0);

	/* This is legal and frees p, but confusing; use xfree() instead */
	assert(sz != 0);

	q = realloc(p, sz);
	if (q == NULL) {
		error(ERROR_FATAL, "realloc");
	}

	return q;
}

/*
 * CONTROLLED VERSION OF FREE
 *
 * This routine frees the block of memory p.  p can be the result of a
 * previous memory allocation routine, or NULL.
 */
void
xfree(void *p)
{
	free(p);
}

