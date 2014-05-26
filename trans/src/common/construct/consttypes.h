/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef constkey
#define constkey 1

/*
 * The type maxconst returns information about the expression under
 * consideration. The field self is true if the expression as a whole is
 * constant within the program fragment under consideration. If the
 * entire expression is not constant (self is false) then the field cont
 * is a list of the sub-expressions which are constant within the
 * specified region.
 *
 * If no sub-expressions are constant, cont has the value nilexp.
 *
 * If cont is not empty, its son is a list of elements, each of which
 * has a son which is a constant within the specified program fragment.
 * The pointer of cont points to the last element of the list.
 */
typedef struct {
	int self;
	exp cont;
} maxconst;

#endif
