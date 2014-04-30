/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include <shared/error.h>
#include <shared/xalloc.h>
#include <shared/string.h>

/* SIZE_MAX is not in C90 */
#ifndef SIZE_MAX
# define SIZE_MAX ((size_t) -1)
#endif

/*
 * Custom error function for xalloc to prevent a dependency on
 * the error library. All errors in this library are fatal and
 * result in the application exiting with EXIT_FAILURE.
 *
 * XXX: but we depend on error/ for progname anyway, so this makes no sense.
 */
static void
xalloc_fatal(const char *s, ...)
{
	va_list args;

	if (progname != NULL) {
		(void) fprintf(stderr, "%s: ", progname);
	}

	(void) fprintf(stderr, "Fatal: ");

	va_start(args, s);
	(void) vfprintf(stderr, s, args);
	va_end(args);

	exit(EXIT_FAILURE);
}

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
		xalloc_fatal("malloc: %s", strerror(errno));
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
		xalloc_fatal("xcalloc: size_t overflow");
	}

	p = calloc(sz, n);
	if (p == NULL) {
		xalloc_fatal("calloc: %s", strerror(errno));
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
		xalloc_fatal("realloc: %s", strerror(errno));
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

