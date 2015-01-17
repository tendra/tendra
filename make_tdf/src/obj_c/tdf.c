/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdlib.h>

#include <shared/error.h>
#include <shared/xalloc.h>
#include "tdf.h"


/*
    These variables indicate the free tdf.  There is an array containing
    lists of small blocks, plus a single larger block.
*/

#define free_tdf_max	16
static tdf *free_tdf = NULL;
static size_t free_tdf_left = 0;
static tdf *free_tdf_array[free_tdf_max] = {
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};


/*
    This routine generates a new blcok of tdf of size sz.  Small blocks
    are allocated from the tdf array, others from the main tdf list.
*/

tdf *
gen_tdf(unsigned sz)
{
    tdf *p;
    size_t n = sz;

    if (n < free_tdf_max) {
	/* Allocate from small block array */
	p = free_tdf_array[n];
	if (p) {
	    free_tdf_array[n] = TAIL_list(p);
	    return p;
	}
    }

    /* Allocate from large block */
    if (n > free_tdf_left) {
	free_tdf_left = 1000;
	free_tdf = xmalloc_nof(tdf, free_tdf_left);
    }
    p = free_tdf;
    free_tdf += sz;
    free_tdf_left -= sz;
    return p;
}


/*
    This routine destroys the block of tdf p of size sz.  Only small
    blocks are recycled.
*/

void
destroy_tdf(tdf *p, unsigned sz)
{
    size_t n = sz;
    if (p && n < free_tdf_max) {
	TAIL_list(p) = free_tdf_array[n];
	free_tdf_array[n] = p;
    }
    return;
}


/*
    This routine is a dummy destructor which does nothing.
*/

void
dummy_destroy_tdf(tdf *p, unsigned sz)
{
    (void) p;
    (void) sz;

    return;
}


/*
    This routine destroys the list p of blocks of tdf of size sz.  The
    list is added to the appropriate entry of the free tdf array.
*/

void
destroy_tdf_list(tdf *p, unsigned sz)
{
    size_t n = sz + 1;
    if (p && n < free_tdf_max) {
	tdf *q = p;
	while (TAIL_list(p)) {
	    p = TAIL_list(p);
	}
	TAIL_list(p) = free_tdf_array[n];
	free_tdf_array[n] = q;
    }
    return;
}


/*
    This routine calculates the length of the list p.
*/

unsigned
length_tdf_list(tdf *p)
{
    tdf *q;
    size_t n = 0;
    for (q = p; q != NULL; q = TAIL_list(q)) {
	n++;
    }
    return n;
}


/*
    This routine reverses the order of the list p.
*/

tdf *
reverse_tdf_list(tdf *p)
{
    tdf *r = NULL;
    tdf *q = p;
    while (q != NULL) {
	tdf *nq = TAIL_list(q);
	TAIL_list(q) = r;
	r = q;
	q = nq;
    }
    return r;
}


/*
    This routine appends the lists of tdf blocks p and q.
*/

tdf *
append_tdf_list(tdf *p, tdf *q)
{
    tdf *r = p;
    if (r == NULL) {
	return q;
    }
    while (TAIL_list(r)) {
	r = TAIL_list(r);
    }
    TAIL_list(r) = q;
    return p;
}


/*
    This routine returns the last member of the list of tdf blocks p.
*/

tdf *
end_tdf_list(tdf *p)
{
    tdf *r = p;
    if (r == NULL) {
	return NULL;
    }
    while (TAIL_list(r))r = TAIL_list(r);
    return r;
}


/*
    These routine implement the assertion checks.
*/

#ifdef ASSERTS
#define assert_calculus assertion
#include "assert_def.h"
#endif
