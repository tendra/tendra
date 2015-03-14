/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * This file declares the routines which detect constant expressions and
 * extract them from loops.
 *
 * The type maxconst returns information about the expression under
 * consideration. The field self is true if the expression as a whole is
 * constant within the program fragment under consideration. If the entire
 * expression is not constant (self is false) then the field cont is a list
 * of the sub-expressions which are constant within the specified region.
 *
 * The type maxconst is defined in consttypes.h
 *
 * The principal procedures declared here are mc_list and repeat_const.
 * They are decribed in const.c
 */

#include <reader/exp.h>

#include <construct/const.h>

extern void repeat_consts(void);
extern int intnl_to(exp whole, exp part);
extern exp get_repeats(void);
