/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/xalloc.h>

#include <symtab/bstack.h>

void
push(long symval, long strval, BSTACK *stack)
{
	while (stack->nextspace != 0) {
		stack = stack->nextspace;
	}

	if (stack->pos < STACKSIZE) {
		stack->symind[stack->pos] = symval;
		stack->strind[stack->pos] = strval;

		stack->pos++;
	} else {
		stack->nextspace = xcalloc(1, sizeof *stack->nextspace);

		stack->nextspace->symind[0] = symval;
		stack->nextspace->strind[0] = strval;

		stack->nextspace->pos = 1;
	}
}

SYMSTR
pop(BSTACK *stack)
{
	BSTACK *oldstack;
	SYMSTR retval;

	oldstack = stack;
	while (stack->nextspace != 0) {
		oldstack = stack;
		stack = stack->nextspace;
	}

	if (stack->pos == 0) {
		stack = oldstack;
		xfree(stack->nextspace);

		retval.sym = stack->symind[STACKSIZE - 1];
		retval.str = stack->strind[STACKSIZE - 1];

		stack->nextspace = NULL;
		stack->pos = STACKSIZE - 1;
	} else {
		retval.sym = stack->symind[stack->pos - 1];
		retval.str = stack->strind[stack->pos - 1];

		stack->pos--;
	}

	return retval;
}

