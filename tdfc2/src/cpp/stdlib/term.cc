/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdlib.h>

#include "implement.h"

/*
 * This list represents all the termination functions which are to be
 * called at the end of a program.
 */
DTOR_LIST *__TCPPLUS_dtors = 0;

/*
 * CALL ALL TERMINATION FUNCTIONS
 *
 * This routine scans down the list of all termination functions calling
 * each in turn.
 */
void
__TCPPLUS_term()
{
	DTOR_LIST *p;

	p = __TCPPLUS_dtors;
	__TCPPLUS_dtors = 0;

	for ( ; p; p = p->next) {
		CLASS *q = p->arg;
		if (q) {
			// Destructor call
			p->func(q, 2);
		} else {
			// atexit function call
			((EXITER) p->func)();
		}
	}

	return;
}

/*
 * INITIALISE TERMINATION FUNCTIONS
 *
 * This routine uses the system atexit to register the function
 * __TCPPLUS_term as being called at the end of the program.
 */
void
__TCPPLUS_init()
{
	static int started = 0;

	if (!started) {
		atexit(__TCPPLUS_term);
		started = 1;
	}

	return;
}

/*
 * REPLACEMENT ATEXIT FUNCTION
 *
 * This routine is a replacement for the system atexit function which
 * works in conjunction with the destructor lists.
 */
int
__TCPPLUS_atexit(EXITER f)
{
	DTOR_LIST *p;

	p = (DTOR_LIST *) malloc(sizeof (DTOR_LIST));
	if (p == NULL) {
		return -1;
	}

	p->next = __TCPPLUS_dtors;
	p->arg  = NULL;
	p->func = (DESTRUCTOR) f;

	__TCPPLUS_dtors = p;
	__TCPPLUS_init();

	return 0;
}

