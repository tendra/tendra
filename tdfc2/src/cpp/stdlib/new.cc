/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "implement.h"

/*
 * The default new handler throws a bad_alloc exception.
 */
static void
default_new_handler()
{
	throw bad_alloc();
}

/*
 * This value gives the current new handler function.
 */
static new_handler crt_new_handler = default_new_handler;

/*
 * Set the current new handler function to fn, returning
 * the previous value.
 */
new_handler
std::set_new_handler(new_handler f) throw ()
{
	new_handler g = crt_new_handler;
	crt_new_handler = f;
	return g;
}

/*
 * Standard memory allocation function
 *
 * Allocate sz bytes of memory, throwing an exception if this is not possible.
 */
void *
__TCPPLUS_new(size_t sz) throw (bad_alloc)
{
	void *p;

	if (sz == 0) {
		sz = 1;
	}

	while (p = malloc(sz), p == NULL) {
		new_handler f = crt_new_handler;
		if (f == NULL) {
			throw bad_alloc();
		}

		f();
	}

	return p;
}

/*
 * No-exception memory allocation function
 *
 * This routine allocates sz bytes of memory, returning a null pointer if
 * this is not possible.
 */
void *
__TCPPLUS_new_nothrow(size_t sz) throw ()
{
	void *p;

	if (sz == 0) {
		sz = 1;
	}

	while (p = malloc(sz), p == NULL) {
		try {
			new_handler f = crt_new_handler;
			if (f == NULL) {
				return NULL;
			}

			f();
		} catch (const bad_alloc &) {
			// Return null if handler throws an exception
			return NULL;
		}
	}

	return p;
}

/*
 * Deallocate the memory given by p.
 */
void
__TCPPLUS_delete(void *p) throw ()
{
	if (p) {
		free(p);
	}

	return;
}

/*
 * The standard nothrow object
 *
 * This object is used in the no-exception memory allocation routines.
 */
const nothrow_t std::nothrow = { };

