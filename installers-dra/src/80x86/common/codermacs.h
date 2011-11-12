/* $Id$ */

/*
 * Copyright 2008-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CODERMACS_H
#define CODERMACS_H

#define local_pl 1
#define callstack_pl 2
#define par_pl 3
#define reg_pl 4
#define ext_pl 5
#define nowhere_pl 6
#define ferr_pl 7

#define no_fixed_regs 7
#define no_low_fixed_regs 3

#define check_stack_max if (max_extra_stack < extra_stack - stack_dec) \
	max_extra_stack = extra_stack - stack_dec

#endif /* CODERMACS_H */
