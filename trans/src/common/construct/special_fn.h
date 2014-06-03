/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CONSTRUCT_SPECIAL_FN_H
#define CONSTRUCT_SPECIAL_FN_H

#include <reader/exptypes.h>

/*
 * STRUCTURE REPRESENTING SPECIAL FUNCTIONS
 */
typedef struct {
    bool is_special;
    exp special_exp;
} special;

/*
 * a1 is the function, a2 is the arguments, s is the shape of the result.
 * result.is_special is true if a special case has been recognised.
 * result.special_exp is the transformed exp if is_special is true.
 */
special special_fn(exp a1, exp a2, shape s);

#endif

