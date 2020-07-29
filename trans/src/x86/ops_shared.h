/*
 * Copyright 2016, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef OPS_SHARED_H
#define OPS_SHARED_H

extern exp smaxe;
extern exp sllmaxe;
extern exp dlongmaxe;

extern where firstlocal;

extern int contop_level;
extern int reg0_in_use;
extern int contop_dopop;

void test_exception(int test_no, shape sha);
void contop(exp a, int r0inuse, where dest);
int flinmem(where w);

/* ops_float.c */
void fl_comp(shape sha, where pos, where neg, exp e);
int in_fl_reg(exp e);
int w_islastuse(where w);
void longc_mult(where a1, where a2, where dest, int inc);

/* ops_move.c */
int count_regs(int mask);

#endif

