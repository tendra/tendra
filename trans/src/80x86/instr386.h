/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * Declares the higher level routines which output 80x86 instructions.
 */

#ifndef INSTR386_H
#define INSTR386_H

#include <reader/exptypes.h>
#include <local/localtypes.h>

void add(shape sha, where a1, where a2, where dest);
void absop(shape sha, where a1, where dest);
void maxop(shape sha, where a1, where a2, where dest);
void minop(shape sha, where a1, where a2, where dest);
void sub(shape sha, where min, where from, where dest);
void mult(shape sha, where a1, where a2, where dest);
void multiply(shape sha, where a1, where a2, where dest);
void div0(shape sha, where bottom, where top, where dest);
void div1(shape sha, where bottom, where top, where dest);
void div2(shape sha, where bottom, where top, where dest);
int cmp(shape sha, where from, where min, int nt, exp e);
void negate(shape sha, where a, where dest);
void move(shape sha, where from, where to);
void mova(where from, where to);
void and(shape sha, where a1, where a2, where dest);
void or(shape sha, where a1, where a2, where dest);
void xor(shape sha, where a1, where a2, where dest);
void not(shape sha, where a, where dest);
void change_var(shape sha, where from, where to);
void change_var_refactor(shape sha, where from, where to);
void change_var_sh(shape sha, shape fsh, where from, where to);
void floater(shape sha, where from, where to);
void frnd0(shape sha, where from, where to);
void frnd1(shape sha, where from, where to);
void frnd2(shape sha, where from, where to);
void frnd3(shape sha, where from, where to);
void frnd4(shape sha, where from, where to);
void changefl(shape sha, where from, where to);
void shiftl(shape sha, where wshift, where from, where to);
void shiftr(shape sha, where wshift, where from, where to);
void rotatel(shape sha, where wshift, where from, where to);
void rotater(shape sha, where wshift, where from, where to);
void mod(shape sha, where bottom, where top, where dest);
void rem2(shape sha, where bottom, where top, where dest);
void rem0(shape sha, where bottom, where top, where dest);
void long_jump(exp e);
void initzeros(void);

extern where zero;
extern where fzero;
extern where dzero;
extern exp zeroe;
extern where ind_reg0;
extern where ind_reg1;
extern where ind_sp;
extern where sp;
extern where bp;
extern where reg0;
extern where reg1;
extern where reg2;
extern where reg3;
extern where reg4;
extern where reg5;
extern where reg_wheres[7];
extern where pushdest;
extern where cond1;
extern where cond2a;
extern where cond2b;
extern int cond1_set;
extern int cond2_set;

void decstack(int longs);
void callins(int longs, exp ind, int ret_stack_dec);
void jumpins(exp ind);
void retins(void);
int inmem(where w);
void fl_binop (unsigned char op, shape sha, where arg1, where arg2, where dest, exp last_arg);
void fl_multop(unsigned char op, shape sha, exp arglist, where dest);
void fl_neg(shape sha, where from, where to);
void fl_abs(shape sha, where from, where to);
void test(shape sha, where a, where b);
void fl_comp(shape sha, where pos, where neg, exp e);

extern where flstack;

int in_fl_reg(exp e);
int in_fstack(exp e);
void movecont(where from, where to, where length, int nooverlap);
void load_stack0(void);
int in_reg(exp e);
void end_contop(void);

extern int top_regsinuse;
extern int lsmask[33];
extern int first_fl_reg;
extern int fstack_pos;
extern exp overflow_e;

void stack_return(int longs);
int bad_from_reg(where f);

void bits_to_mem(exp e, exp d, ash stack);
void mem_to_bits(exp e, shape sha, where dest, ash stack);

void setup_fl_ovfl(exp e);
void test_fl_ovfl(exp e, where dest);
void reset_fpucon(void);
exp find_stlim_var(void);
void checkalloc_stack(where sz, int b);	/* uses reg1 */
void special_ins(char * id, exp args, where dest);

extern exp ferrmem;
extern int ferrsize;
extern int fpucon;
extern int cmp_64hilab;

void save_stack(void);
void restore_stack(void);

void start_asm(void);
void end_asm(void);
void asm_ins(exp e);

#endif /* INSTR386_H */
