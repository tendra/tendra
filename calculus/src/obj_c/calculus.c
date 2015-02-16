/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdlib.h>

#include <shared/check.h>
#include <shared/error.h>
#include <shared/xalloc.h>

#define calculus_IO_ROUTINES
#include "calculus.h"
#include "../extra.h"


/*
 * CHECK FOR CORRECT HEADERS
 *
 * The functions defined in this file give the implementations of various
 * support functions used by the calculus implementation.  They should
 * therefore be compiled with the calculus implementation rather than the
 * specification.
 */

#if calculus_SPECIFICATION
!!!error Implementation specific functions compiled with token specifications
#endif


/*
 * FREE OBJECTS
 *
 * These variables indicate the free calculi.  There is an array containing
 * lists of small blocks, plus a single larger block.
 */

static calculus *free_calculi = NULL;
static unsigned free_calculi_left = 0;
static calculus *free_calculus_array[] = {
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL
};


/*
 * GENERATE A NEW OBJECT BLOCK
 *
 * This routine generates a new blcok of calculi of size sz.  Small blocks
 * are allocated from the calculus array, others from the main calculus list.
 */

calculus *
gen_calculus(unsigned sz)
{
    calculus *p;
    unsigned n = sz;
    assert(sizeof free_calculus_array / sizeof *free_calculus_array == calculus_GEN_MAX);
    assert(n != 0);

    if (n < calculus_GEN_MAX) {
	/* Allocate from small block array */
	p = free_calculus_array[n];
	if (p) {
	    free_calculus_array[n] = TAIL_list(p);
	    return p;
	}
    }

    /* Allocate from large block */
    if (n > free_calculi_left) {
	free_calculi_left = 1000;
	free_calculi = xmalloc_nof(calculus, free_calculi_left);
    }
    p = free_calculi;
    free_calculi += sz;
    free_calculi_left -= sz;
    return p;
}


/*
 * DESTROY AN OBJECT BLOCK
 *
 * This routine destroys the block of calculi p of size sz.  Only small
 * blocks are recycled.
 */

void
destroy_calculus(calculus *p, unsigned sz)
{
    unsigned n = sz;
    assert(n != 0);
    if (p && n < calculus_GEN_MAX) {
	TAIL_list(p) = free_calculus_array[n];
	free_calculus_array[n] = p;
    }
    return;
}


/*
 *  DUMMY OBJECT BLOCK DESTRUCTOR
 *
 *  This routine is a dummy destructor which does nothing.
 */

void
dummy_destroy_calculus(calculus *p, unsigned sz)
{
    UNUSED(p);
    UNUSED(sz);
    return;
}


/*
 * DESTROY A LIST OF OBJECT BLOCKS
 *
 * This routine destroys the list p of blocks of calculi of size sz.  The
 * list is added to the appropriate entry of the free calculus array.
 */

void
destroy_calculus_list(calculus *p, unsigned sz)
{
    unsigned n = sz + 1;
    if (p && n < calculus_GEN_MAX) {
	calculus *q = p;
	while (TAIL_list(p)) {
		p = TAIL_list(p);
	}
	TAIL_list(p) = free_calculus_array[n];
	free_calculus_array[n] = q;
    }
    return;
}


/*
 * FIND THE LENGTH OF A LIST
 *
 * This routine calculates the length of the list p.
 */

unsigned
length_calculus_list(calculus *p)
{
    calculus *q;
    unsigned n = 0;
    for (q = p; q != NULL; q = TAIL_list(q)) {
	    n++;
    }
    return n;
}


/*
 * REVERSE A LIST
 *
 * This routine reverses the order of the list p.
 */

calculus *
reverse_calculus_list(calculus *p)
{
    calculus *r = NULL;
    calculus *q = p;
    while (q != NULL) {
	calculus *nq = TAIL_list(q);
	TAIL_list(q) = r;
	r = q;
	q = nq;
    }
    return r;
}


/*
 * APPEND TWO LISTS
 *
 * This routine appends the lists of calculus blocks p and q.
 */

calculus *
append_calculus_list(calculus *p, calculus *q)
{
    calculus *r = p;
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
 * FIND THE LAST MEMBER OF A LIST
 *
 * This routine returns the last member of the list of calculus blocks p.
 */

calculus *
end_calculus_list(calculus *p)
{
    calculus *r = p;
    if (r == NULL) {
	    return NULL;
    }
    while (TAIL_list(r)) {
	    r = TAIL_list(r);
    }
    return r;
}


/*
 * EMPTY VECTOR
 *
 * This calculus represents the generic empty vector.  It is only defined
 * if vector operations have been enabled.  Note that the element field
 * of a vector is not be NULL, even if the vector is empty.
 */

#ifdef VEC
static calculus dummy_elem;
calculus_VEC empty_calculus_vec = {0, {&dummy_elem, &dummy_elem}};
#endif


/*
 * ALIASING VARIABLES
 *
 * These variables give respectively the current alias number and the
 * list of all aliases.
 */

unsigned crt_calculus_alias = 0;
static calculus *crt_alias_list = NULL;


/*
 * SET AN ALIAS
 *
 * This routine sets up an alias of p to n.
 */

void
set_calculus_alias(calculus *p, unsigned n)
{
    calculus *q;
    assert(p != NULL);
    q = gen_calculus((unsigned)2);
    TAIL_list(q) = crt_alias_list;
    HEAD_list(q)->ag_ptr = p;
    p->ag_tag = n;
    crt_alias_list = q;
    return;
}


/*
 * FIND AN ALIAS
 *
 * This routine searches for alias number n.
 */

calculus *
find_calculus_alias(unsigned n)
{
    calculus *p = crt_alias_list;
    while (p != NULL) {
	calculus *q = HEAD_list(p)->ag_ptr;
	if (q->ag_tag == n) {
		return q;
	}
	p = TAIL_list(p);
    }
    error(ERR_FATAL, "Can't find alias %u", n);
    return NULL;
}


/*
 * CLEAR ALL ALIASES
 *
 * This routine clears all aliases.  Each alias in the list is reset to
 * zero, and the list itself is freed.
 */

void
clear_calculus_alias(void)
{
    calculus *p = crt_alias_list;
    calculus *q = NULL;
    while (p != NULL) {
	HEAD_list(p) ->ag_ptr->ag_tag = 0;
	q = p;
	p = TAIL_list(p);
    }
    if (q) {
	TAIL_list(q) = free_calculus_array[2];
	free_calculus_array[2] = crt_alias_list;
    }
    crt_calculus_alias = 0;
    crt_alias_list = NULL;
    return;
}


/*
 * ADD TWO LISTS
 *
 * This routine copies the list of blocks of calculi p and adds the list
 * q to the end.  sz gives the size of the blocks in the list.  This is
 * used for the user defined tokens in extra.h.
 */

calculus *
add_calculus_list(calculus *p, calculus *q, int sz)
{
    int i;
    calculus *r;
    if (p == NULL) {
	    return q;
    }
    r = gen_calculus((unsigned)(sz + 1));
    for (i = 1; i <= sz; i++) {
	    r[i] = p[i];
    }
    TAIL_list(r) = add_calculus_list(TAIL_list(p), q, sz);
    return r;
}


#ifndef NDEBUG
#include "assert_def.h"
#endif
