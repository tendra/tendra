/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef MACH_INS_INCLUDED
#define MACH_INS_INCLUDED

#include <construct/installtypes.h>

extern void make_instr_aux(int, mach_op *, mach_op *, bitpattern, int);

#define  make_instr(A, B, C, D)\
    make_instr_aux((A), (B), (C), (D), 0)

extern bool output_immediately;
extern mach_ins *all_mach_ins;
extern mach_ins *current_ins;
extern void free_all_ins(void);
extern void reclaim_ins(mach_ins *);

extern long last_jump;
extern bitpattern last_jump_regs;

extern void make_external_label(char *);
extern void make_jump(int, long);
extern void make_label(long);
extern void set_special(char *, mach_op *);

#endif











