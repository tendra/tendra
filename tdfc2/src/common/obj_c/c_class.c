/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdio.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include <utility/config.h>
#include "c_types.h"

#include <utility/error.h>
#include <utility/xalloc.h>


/*
    The functions defined in this file give the implementations of various
    support functions used by the c_class implementation.  They should
    therefore be compiled with the c_class implementation rather than the
    specification.
*/

#if c_class_SPECIFICATION
#error Implementation functions compiled with token specifications
#endif


/*
    These variables indicate the free c_classes.  There is an array
    containing lists of small blocks, plus a single larger block.
*/

#define SMALL_BLOCK		24
#define ALLOC_BLOCK		2048

#if (c_class_GEN_MAX > SMALL_BLOCK)
#error Free block array is too small
#endif

static c_class *free_c_classes = NULL;
static unsigned free_c_classes_left = 0;
unsigned total_c_classes = 0;

static c_class *free_c_class_array[SMALL_BLOCK] = {
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};


/*
    This routine generates a new block of c_classes of size sz.  Small
    blocks are allocated from the c_class array, others from the main
    c_class list.
*/

c_class *
gen_c_class(unsigned sz)
{
	c_class *p;
	unsigned n = sz;
	if (n < SMALL_BLOCK) {
		/* Allocate from small block array */
		if (n == 0) {
			return NULL;
		}
		p = free_c_class_array[n];
		if (p) {
			free_c_class_array[n] = TAIL_list(p);
			return p;
		}
	}
	if (n > free_c_classes_left) {
		/* Allocate new blocks */
		unsigned m = ALLOC_BLOCK;
		if (n > m) {
			m = n;
		}
		free_c_classes = xmalloc_nof(c_class, m);
		free_c_classes_left = m;
	}
	p = free_c_classes;
	free_c_classes += n;
	free_c_classes_left -= n;
	return p;
}


/*
    This routine is used in the object destruction routines to mark an
    object as having been freed.  This only has any effect in conjunction
    with the debugging routine below.
*/

#ifndef NDEBUG
#define clean_c_class(P, Z)\
    {\
	assert(TYPEID(P) != TYPEID_free);\
	TYPEID(P) = TYPEID_free ;\
	total_c_classes -= (Z);\
    }
#else
#define clean_c_class(P, Z)	/* empty */
#endif


/*
    This routine is identical to gen_c_class except that it includes the
    run-time type information t in the allocated block.
*/

#ifndef NDEBUG

c_class *
debug_c_class(unsigned sz, unsigned t)
{
	c_class *p;
	unsigned n = sz;
	total_c_classes += n;
	if (n < SMALL_BLOCK) {
		/* Allocate from small block array */
		if (n == 0) {
			return NULL;
		}
		p = free_c_class_array[n];
		if (p) {
			free_c_class_array[n] = TAIL_list(p);
			assert(TYPEID(p) == TYPEID_free);
			TYPEID(p) = t;
			return p;
		}
	}
	n += 1;
	if (n > free_c_classes_left) {
		/* Allocate new blocks */
		unsigned m = ALLOC_BLOCK;
		if (n > m) {
			m = n;
		}
		free_c_classes = xmalloc_nof(c_class, m);
		free_c_classes_left = m;
	}
	p = free_c_classes + 1;
	TYPEID(p) = t;
	free_c_classes += n;
	free_c_classes_left -= n;
	return p;
}

#endif /* !NDEBUG */


/*
    This routine destroys the block of c_classes p of size sz.
*/

void
destroy_c_class(c_class *p, unsigned sz)
{
	if (p) {
		unsigned n = sz;
		c_class **r = free_c_class_array;
		if (n < SMALL_BLOCK) {
			r += n;
		}
		clean_c_class(p, n);
		TAIL_list(p) = *r;
		*r = p;
	}
	return;
}


/*
    This routine is a dummy destructor which does nothing.
*/

void
dummy_destroy_c_class(c_class *p, unsigned sz)
{
	UNUSED(p);
	UNUSED(sz);
	return;
}


/*
    This routine destroys the list p of blocks of c_classes of size sz.
    The list is added to the appropriate entry of the free c_class array.
*/

void
destroy_c_class_list(c_class *p, unsigned sz)
{
	if (p) {
		c_class *q = p;
		unsigned n = sz + 1;
		c_class **r = free_c_class_array;
		if (n < SMALL_BLOCK) {
			r += n;
		}
		while (TAIL_list(p)) {
			clean_c_class(p, n);
			p = TAIL_list(p);
		}
		clean_c_class(p, n);
		TAIL_list(p) = *r;
		*r = q;
	}
	return;
}


/*
    This routine calculates the length of the list p.
*/

unsigned
length_c_class_list(c_class *p)
{
	unsigned n = 0;
	c_class *q = p;
	while (q) {
		n++;
		q = TAIL_list(q);
	}
	return n;
}


/*
    This routine reverses the order of the list p.
*/

c_class *
reverse_c_class_list(c_class *p)
{
	c_class *r = NULL;
	c_class *q = p;
	while (q) {
		c_class *nq = TAIL_list(q);
		TAIL_list(q) = r;
		r = q;
		q = nq;
	}
	return r;
}


/*
    This routine appends the lists of c_class blocks p and q.
*/

c_class *
append_c_class_list(c_class *p, c_class *q)
{
	c_class *r = p;
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
    This routine returns the last member of the list of c_class blocks p.
*/

c_class *
end_c_class_list(c_class *p)
{
	c_class *r = p;
	if (r == NULL) {
		return NULL;
	}
	while (TAIL_list(r)) {
		r = TAIL_list(r);
	}
	return r;
}


/*
   GENERIC EMPTY VECTOR

   This c_class represents the generic empty vector.  It is only defined
   if vector operations have been enabled.  Note that the element field
   of a vector is not be NULL, even if the vector is empty.
 */

#ifdef VEC
static c_class dummy_elem;
c_class_VEC empty_c_class_vec = {0, {&dummy_elem, &dummy_elem}};
#endif


#ifdef c_class_IO_ROUTINES

/*
   ALIASING VARIABLES

   These variables give respectively the current alias number and the
   list of all aliases.
 */

unsigned crt_c_class_alias = 0;
static c_class *crt_alias_list = NULL;


/*
   SET AN ALIAS

   This routine sets up an alias of p to n.
 */

void
set_c_class_alias(c_class *p, unsigned n)
{
	c_class *q = GEN_c_class(2, TYPEID_list);
	TAIL_list(q) = crt_alias_list;
	HEAD_list(q) ->ag_ptr = p;
	assert(p != NULL);
	p->ag_tag = n;
	crt_alias_list = q;
	return;
}


/*
    This routine searches for alias number n.
*/

c_class *
find_c_class_alias(unsigned n)
{
	c_class *p = crt_alias_list;
	while (p) {
		c_class *q = HEAD_list(p) ->ag_ptr;
		if (q->ag_tag == n) {
			return q;
		}
		p = TAIL_list(p);
	}
	error(ERR_INTERNAL, "Can't find alias %u", n);
	return NULL;
}


/*
    This routine clears all aliases.  Each alias in the list is reset to
    zero, and the list itself is freed.
*/

void
clear_c_class_alias(void)
{
	c_class *p = crt_alias_list;
	c_class *q = NULL;
	while (p) {
		HEAD_list(p)->ag_ptr->ag_tag = 0;
		q = p;
		p = TAIL_list(p);
	}
	if (q) {
		TAIL_list(q) = free_c_class_array[2];
		free_c_class_array[2] = crt_alias_list;
	}
	crt_c_class_alias = 0;
	crt_alias_list = NULL;
	return;
}

#endif /* c_class_IO_ROUTINES */


/*
    These routine implement the assertion checks.
*/

#ifndef NDEBUG
#include "assert_def.h"
#endif
