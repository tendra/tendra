/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


/* 80x86/instrdecs.h */


#ifndef indecs_key
#define indecs_key 1



extern  void ins0(char *i);
extern  void ins1(char *i, int s1, where a1);
extern  void ins1lit(char *i, int s1, where a1);
extern  void ins1ind(char *i, int s1, where a1);
extern  void ins2(char *i, int s1, int s2, where a1, where a2);
extern  void ins3(char *i, int s1, int s2, int s3, where a1,
				  where a2, where a3);
extern  void set_label(exp jr);
extern  void simplest_set_lab(int labno);
extern  void simple_set_label(int labno);
extern  void jump(exp jr, int with_fl_reg);
extern  void branch(int test_no, exp jr, int sg, int shnm);
extern  void simple_branch(char * j, int labno);
extern  void jmp_overflow(exp jr, int sg, int inv);
extern  void trap_overflow(int sg, int inv);
extern  void test_trap(int test_no, int sg, int shnm);
extern  void trap_ins(int s);
extern  void set_env_off(int stack_pos, exp id);
extern  void envoff_operand(exp id, int off);
extern  void envsize_operand(exp id);
extern  void ldisp(void);
extern  char *margin;
extern  char *spx;
extern  char *sep;
extern  void outreal(exp e);
extern  void rel_sp(int i, int b);
extern  void rel_cp(int i, int b);
extern  void rel_ap(int i, int b);
extern  void rel_ap1(int i, int b);
extern  void regn(int regs, int rdisp, exp ldname, int le);
extern  void ind_reg(int regs, int rdisp, int offset,
					 exp ldname, int b);
extern  void extn(exp id, int off, int b);
extern  void int_operand(int k, int le);
extern  void const_extn(exp ident, int noff);
extern  void proc_extn(exp ident, int noff);
extern  void label_operand(exp e);
extern  void index_opnd(where whmain, where wh, int scale);
extern  void mult_op(int inc, where rmain,
					 where rind, int scale, where dest);
extern  void caseins(int sz, exp arg, int min, int max, int *v,
					 int exhaustive, int in_eax, exp case_exp);
extern int get_reg_no(int regs);
extern int extra_stack;
extern int max_extra_stack;
extern  void const_intnl(int addr, int lab, int off);
extern  void discard_fstack(void);
extern  void discard_st1(void);
extern  void load_stack0(void);
extern  int no_frame;
extern  void outbp(void);
extern  void set_stack_from_bp(void);
extern  int last_jump_label;
extern  void set_lv_label(exp e);
extern void setcc(int test_no, int sg, int shnm);

extern void testah(int mask);
extern exp make_extn(char * n, shape s, int v);

extern void rotshift64(int shft, int sig, where wshift);

/* temporary */
extern  void temp_push_fl(void);
extern  void temp_pop_fl(void);


#endif

