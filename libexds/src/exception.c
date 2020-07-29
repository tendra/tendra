/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * exception.c - Exception handling.
 *
 * This file implements the exception handling facility specified in the file
 * "exception.h".  See that file for more details.
 */

#include <stdlib.h>
#include <setjmp.h>

#include <shared/bool.h>
#include <shared/check.h>

#include <exds/common.h>
#include <exds/exception.h>

void (*unhandled)(ExceptionT *e, const char *file, unsigned line);
void (*corrupt_handler)(const char *file, unsigned line);

HandlerT *X__exception_handler_stack = NULL;
ThrowDataT X__exception_throw_data;

void
exception_unhandled(void (*handler)(ExceptionT *e, const char *file, unsigned line))
{
	unhandled = handler;
}

void
exception_corrupt_handler(void (*handler)(const char *file, unsigned line))
{
	corrupt_handler = handler;
}

NORETURN
X__exception_throw(void)
{
	static bool failing = false;
	HandlerT *stack      = X__exception_handler_stack;

	if (failing) {
		abort();
		UNREACHED;
	} else if (stack == NULL) {
		failing = true;
		if (unhandled) {
			unhandled(X__exception_throw_data.exception,
			X__exception_throw_data.file,
			X__exception_throw_data.line);
		}
		abort();
		UNREACHED;
	}

#ifdef PO_EXCEPTION_STACK_DIRECTION
	if (stack->magic_start != X__EXCEPTION_MAGIC ||
		stack->magic_end != X__EXCEPTION_MAGIC ||
#if PO_EXCEPTION_STACK_DIRECTION > 0
		stack > &stack ||
#endif /* PO_EXCEPTION_STACK_DIRECTION > 0 */
#if PO_EXCEPTION_STACK_DIRECTION < 0
		stack < &stack ||
#endif /* PO_EXCEPTION_STACK_DIRECTION < 0 */
		stack->next == stack) {

		failing = true;

		if (corrupt_handler) {
			corrupt_handler(stack->file, stack->line);
		}

		abort();
		UNREACHED;
	}
#endif /* defined (PO_EXCEPTION_STACK_DIRECTION) */

	longjmp(X__exception_handler_stack->buffer, 1);
	UNREACHED;
}

const char *
exception_name(ExceptionT *exc)
{
	return exc;
}
