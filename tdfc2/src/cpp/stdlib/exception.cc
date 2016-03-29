/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>

#include "implement.h"

#include <cstdio>
#include <exception>

using namespace std;

/*
 * This value gives information on the current exception.
 * This implementation, with a single current exception variable,
 * will need to be modified for a multi-threaded environment.
 * Basically there needs to be one current exception per thread.
 */

static JUMP_BUFFER top_level = {
	&top_level, NULL
};

EXCEPTION __TCPPLUS_except = {
	NULL, NULL, { NULL, NULL }, { &top_level, NULL, NULL }, false
};

/*
 * Throw an exception with value v and type corresponding
 * to the type information structure p and the destructor d.  p is the
 * null pointer to indicating the re-throwing of the current exception.
 */

void
__TCPPLUS_throw(void *v, TYPE_INFO *p, DESTRUCTOR d)
{
#ifdef NO_EXCEPTIONS
	// Allow suppression of exception routines
	terminate();
#else
	EXCEPTION &ex;
	TYPE_INFO *q;

	ex = __TCPPLUS_except;
	q = ex.type;

	if (p) {
		// Throwing new exception
		if (q) {
			// Check existing exception
			if (ex.unwinding) {
				// Still in stack unwinding
				terminate();
				return;
			}
			__TCPPLUS_handled();
		}

		ex.value[0] = v;
		ex.type = p;
		ex.dtor = d;
	} else {
		// Re-throwing current exception
		if (q == NULL) {
			// No exception to re-throw
			terminate();
			return;
		}
		p = q;
	}

	JUMP_BUFFER *jmp = ex.buf[0];
	assert(jmp != NULL);
	ex.unwinding = true;
	ex.allocated = false;
	ex.buf[0] = jmp->next;
	ex.buf[1] = jmp;
	DTOR_LIST *dtors = jmp->dtors;

	for (jmp->dtors = NULL; dtors; dtors = dtors->next) {
		// Perform stack unwinding
		assert(dtors->func != NULL && dtors->arg != NULL);
		dtors->func(dtors->arg, 2);
	}

	if (jmp == &top_level) {
		// No further handlers
		terminate();
		return;
	}

	long_jump(jmp->frame, jmp->label);
#endif
}

/*
 * Catch an exception
 *
 * This routine checks whether the current exception can be caught by a
 * handler with type corresponding to the type information structure p.
 */
int
__TCPPLUS_catch(TYPE_INFO *p)
{
	EXCEPTION &ex;
	void *r;

	ex = __TCPPLUS_except;
	r = ex.value[0];
	r = __TCPPLUS_catch_cast(r, ex.type, p, 1, 0);
	if (r) {
		ex.value[1] = r;
		ex.buf[2]   = NULL;
		return 1;
	}

	return 0;
}

/*
 * Exception value buffers
 *
 * Whenever possible one of these buffers is used to hold the value
 * thrown by an exception(this is to avoid the mess which would arise
 * by dynamically allocating space for the value if the exception was
 * raised to indicated memory exhaustion).  There are two buffers
 * because when a handler throws an exception the new value is
 * created before the old one is destroyed.
 */

static char ebuff1[100];
static char ebuff2[100];
static bool ebuff1_used = false;
static bool ebuff2_used = false;

/*
 * Allocate sz bytes of space to store an exception value.
 * If sz is sufficiently small one of the buffers above is used, otherwise
 * the memory is dynamically allocated.
 */
void *
__TCPPLUS_alloc_except(size_t sz)
{
	if (__TCPPLUS_except.allocated) {
		// Two allocates without a throw
		terminate();
	}

	__TCPPLUS_except.allocated = true;
	if (sz <= sizeof( ebuff1) ) {
		if (!ebuff1_used) {
			ebuff1_used = true;
			return ( void *) &ebuff1 ;
		}
		if (!ebuff2_used) {
			ebuff2_used = true;
			return ( void *) &ebuff2 ;
		}
	}

	void *p = malloc(sz);
	if (p == NULL) {
		terminate();
	}

	return p;
}

/*
 * Complete an exception
 *
 * This routine is called when the current exception has been completely
 * handled.  It calls the destructor for the current exception value and
 * frees the space it used.
 */
void
__TCPPLUS_handled()
{
	EXCEPTION &ex;
	DESTRUCTOR dtor;
	void *p;

	ex = __TCPPLUS_except;
	dtor = ex.dtor;
	ex.unwinding = false;
	ex.type = NULL;
	ex.dtor = NULL;

	p = ex.value[0];
	if (p) {
		if (dtor) {
			dtor(( CLASS *) p , 2 );
		}

		if (p == (void *) &ebuff1 ) {
			ebuff1_used = false;
		} else if (p == (void *) &ebuff2 ) {
			ebuff2_used = false;
		} else {
			free(p);
		}

		ex.value[0] = NULL;
	}

	return;
}

/*
 * The default terminate handler function.
 * TODO: can this be marked noreturn?
 */
static void
terminator()
{
	abort();
}

/*
 * The current terminate handler function.
 */
static terminate_handler crt_terminate_handler = terminator;

/*
 * Set the current terminate handler to f, returning the old value.
 */
terminate_handler
std::set_terminate(terminate_handler f) throw()
{
	terminate_handler g;

	g = crt_terminate_handler;
	if (f == NULL) {
		f =(terminate_handler) abort;
	}

	crt_terminate_handler = f;
	return g;
}

/*
 * This routine calls the current terminate handler.
 */
void
std::terminate()
{
	__TCPPLUS_except.unwinding = false;
	crt_terminate_handler();
	return;
}

/*
 * This variable gives the current unexpected handler function.
 */
static unexpected_handler crt_unexpected_handler = terminate;

/*
 * This routine sets the current unexpected handler to f, returning the
 * old value.
 */
unexpected_handler
std::set_unexpected(unexpected_handler f) throw()
{
	unexpected_handler g;

	g = crt_unexpected_handler;
	if (f == NULL) {
		f = terminate;
	}

	crt_unexpected_handler = f;
	return g;
}

/*
 * This routine calls the current unexpected handler.
 */
void
std::unexpected()
{
	__TCPPLUS_except.unwinding = false;
	crt_unexpected_handler();
	return;
}

/*
 * Handle an unexpected exception
 *
 * This routine is called if a thrown exception does not match the
 * exception specification of an enclosing function.  Note that the
 * jump buffer stack is hacked so that any exception thrown by
 * unexpected will be re-examined by the exception specification.
 * If it is still does not match then either terminate is called
 * or a bad_exception is thrown.
 */
void
__TCPPLUS_unexpected(int have_bad)
{
	EXCEPTION &ex = __TCPPLUS_except;

	ex.unwinding = false;

	JUMP_BUFFER *jmp = ex.buf[1];
	if (jmp == ex.buf[2]) {
		if (have_bad) {
			throw bad_exception();
		}
		terminate();
		return;
	}

	ex.buf[2] = jmp;
	ex.buf[0] = jmp;
	unexpected();

	return;
}

/*
 * This routine returns true if an exception has been thrown but not yet caught.
 */
bool
std::uncaught_exception()
{
	return __TCPPLUS_except.unwinding;
}

/*
 * This routine prints an error message if an assertion has failed.
 */
void
__TCPPLUS_assert(const char *fn, int ln)
{
	/* TODO: call guts behind C's assert(), so we share the formatting */
	printf("Assertion failed, %s, line %d.\n", fn, ln);
	abort();
}

