/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef OPTIMISE_H
#define OPTIMISE_H

enum optim {
	OPTIM_UNROLL       = 1 <<  0, /* Unroll loops */
	OPTIM_INLINE_PROCS = 1 <<  1, /* Inlining of proc tokens */
	OPTIM_INLINE_EXPS  = 1 <<  2, /* Inlining of exp tokens */
	OPTIM_LOOPCONSTS   = 1 <<  3, /* Hoist constants out of loops */
	OPTIM_FORALLS      = 1 <<  4, /* Replace loop indexes by incremented pointers */
	OPTIM_DUMP         = 1 <<  5, /* Avoid register dumping */
	OPTIM_TAIL         = 1 <<  6, /* Tail recursion */
	OPTIM_PEEPHOLE     = 1 <<  7, /* Peephole substitions */
	OPTIM_CASE         = 1 <<  8, /* Perform case transforms */
	OPTIM_JUMPS        = 1 <<  9, /* Follow gotos and tests to their final destination */
	OPTIM_TEMPDEC      = 1 << 10  /* Use temporary registers for local values */
};

extern enum optim optim;

extern void opt_all_exps(void);
extern enum optim optim_flags(const char *);

#endif

