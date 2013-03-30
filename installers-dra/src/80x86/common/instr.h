/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef INSTR_H
#define INSTR_H

#include "config.h"
#include "exptypes.h"
#include "localtypes.h"
#include <construct/installtypes.h>

void ins0(char *i);
void ins1(char *i, int s1, where a1);
void ins1lit(char *i, int s1, where a1);
void ins1ind(char *i, int s1, where a1);
void ins2(char *i, int s1, int s2, where a1, where a2);
void ins3 (char *i, int s1, int s2, int s3, where a1, where a2, where a3);
void set_label(exp jr);
void simplest_set_lab(int labno);
void simple_set_label(int labno);
void jump(exp jr, int with_fl_reg);
void branch(int test_no, exp jr, int sg, int shnm);
void simple_branch(char * j, int labno);
void jmp_overflow(exp jr, int sg, int inv);
void trap_overflow(int sg, int inv);
void test_trap(int test_no, int sg, int shnm);
void trap_ins(int s);
void set_env_off(int stack_pos, exp id);
void envoff_operand(exp id, int off);
void envsize_operand(exp id);
void ldisp(void);

extern char *margin;
extern char *spx;
extern char *sep;

void outreal(exp e);
void rel_sp(int i, int b);
void rel_cp(int i, int b);
void rel_ap(int i, int b);
void rel_ap1(int i, int b);
void regn(int regs, int rdisp, exp ldname, int le);
void ind_reg (int regs, int rdisp, int offset, exp ldname, int b);
void extn(exp id, int off, int b);
void int_operand(int k, int le);
void const_extn(exp ident, int noff);
void proc_extn(exp ident, int noff);
void label_operand(exp e);
void index_opnd(where whmain, where wh, int scale);
void mult_op (int inc, where rmain, where rind, int scale, where dest);
void caseins (int sz, exp arg, int min, int max, int *v, int exhaustive, int in_eax, exp case_exp);
int get_reg_no(int regs);

extern int extra_stack;
extern int max_extra_stack;

void const_intnl(int addr, int lab, int off);
void discard_fstack(void);
void discard_st1(void);
void load_stack0(void);

extern int no_frame;
int last_jump_label;
extern int avoid_intov;

void outbp(void);
void set_stack_from_bp(void);
void set_lv_label(exp e);
void setcc(int test_no, int sg, int shnm);

void testah(int mask);
exp make_extn(char *n, shape s, int v);

void rotshift64(int shft, int sig, where wshift);

/* temporary */
void temp_push_fl(void);
void temp_pop_fl(void);

#endif /* INSTR_H */
