/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef PEEPHOLE_INCLUDED
#define PEEPHOLE_INCLUDED

#include <construct/installtypes.h>

extern bitpattern callmsk;
extern void peephole(void);
extern bool post_inc_refactor(mach_ins *, bitpattern);

#endif
