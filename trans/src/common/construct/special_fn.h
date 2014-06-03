/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CONSTRUCT_SPECIAL_FN_H
#define CONSTRUCT_SPECIAL_FN_H

/*
 * a1 is the function, a2 is the arguments, s is the shape of the result.
 *
 * Returns true if a special case has been recognised,
 * in which case *e will be populated with the transformed exp.
 */
bool
special_fn(exp a1, exp a2, shape s, exp *e);

#endif

