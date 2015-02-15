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
#include "errors.h"


/*
    These variables indicate the free errors.  There is an array containing
    lists of small blocks, plus a single larger block.
*/

#define free_errors_max	16
static errors *free_errors = NULL;
static size_t free_errors_left = 0;
static errors *free_errors_array[free_errors_max] = {
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};


/*
    This routine generates a new blcok of errors of size sz.  Small blocks
    are allocated from the errors array, others from the main errors list.
*/

errors *
gen_errors(unsigned sz)
{
    errors *p;
    size_t n = sz;

    if (n < free_errors_max) {
	/* Allocate from small block array */
	p = free_errors_array[n];
	if (p) {
	    free_errors_array[n] = TAIL_list(p);
	    return p;
	}
    }

    /* Allocate from large block */
    if (n > free_errors_left) {
	free_errors_left = 1000;
	free_errors = xmalloc_nof(errors, free_errors_left);
    }
    p = free_errors;
    free_errors += sz;
    free_errors_left -= sz;
    return p;
}


/*
    This routine destroys the block of errors p of size sz.  Only small
    blocks are recycled.
*/

void
destroy_errors(errors *p, unsigned sz)
{
    size_t n = sz;
    if (p && n < free_errors_max) {
	TAIL_list(p) = free_errors_array[n];
	free_errors_array[n] = p;
    }
    return;
}


/*
    This routine is a dummy destructor which does nothing.
*/

void
dummy_destroy_errors(errors *p, unsigned sz)
{
	(void) p;
	(void) sz;

    return;
}


/*
    This routine destroys the list p of blocks of errors of size sz.  The
    list is added to the appropriate entry of the free errors array.
*/

void
destroy_errors_list(errors *p, unsigned sz)
{
    size_t n = sz + 1;
    if (p && n < free_errors_max) {
	errors *q = p;
	while (TAIL_list(p)) {
	    p = TAIL_list(p);
	}
	TAIL_list(p) = free_errors_array[n];
	free_errors_array[n] = q;
    }
    return;
}


/*
    This routine calculates the length of the list p.
*/

unsigned
length_errors_list(errors *p)
{
    errors *q;
    size_t n = 0;
    for (q = p; q != NULL; q = TAIL_list(q)) {
	n++;
    }
    return n;
}


/*
    This routine reverses the order of the list p.
*/

errors *
reverse_errors_list(errors *p)
{
    errors *r = NULL;
    errors *q = p;
    while (q != NULL) {
	errors *nq = TAIL_list(q);
	TAIL_list(q) = r;
	r = q;
	q = nq;
    }
    return r;
}


/*
    This routine appends the lists of errors blocks p and q.
*/

errors *
append_errors_list(errors *p, errors *q)
{
    errors *r = p;
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
    This routine returns the last member of the list of errors blocks p.
*/

errors *
end_errors_list(errors *p)
{
    errors *r = p;
    if (r == NULL) {
	return NULL;
    }
    while (TAIL_list(r)) {
	r = TAIL_list(r);
    }
    return r;
}


/*
    These routine implement the assertion checks.
*/

#ifndef NDEBUG
#include "assert_def.h"
#endif
