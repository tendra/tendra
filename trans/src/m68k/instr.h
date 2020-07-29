/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef INSTR_INCLUDED
#define INSTR_INCLUDED

extern mach_op * operand(long, where);
extern bitpattern regs_changed(mach_op *, int);
extern void ins0(int);
extern void ins1(int, long, where, int);
extern void ins2(int, long, long, where, where, int);
extern void ins2n(int, long, long, where, int);
extern void ins2h(int, long, long, where, int);
extern void save_stack(void);
extern void restore_stack(void);

#endif
