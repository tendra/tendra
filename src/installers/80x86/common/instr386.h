/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


/* 80x86/instr386decs.h */

/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:51 $
$Revision: 1.1.1.1 $
$Log: instr386.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:51  release
 * First version to be checked into rolling release.
 *
 * Revision 1.17  1997/10/10  18:25:22  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.16  1996/11/08  16:19:19  pwe
 * check_stack to check before modifying stack
 *
 * Revision 1.15  1996/07/31  12:57:19  pwe
 * restore alloca stack after longjump
 *
 * Revision 1.14  1996/05/20  14:30:33  pwe
 * improved 64-bit handling
 *
 * Revision 1.13  1996/05/13  12:51:59  pwe
 * undo premature commit
 *
 * Revision 1.11  1996/01/10  14:00:01  pwe
 * apply with varcallees within postlude
 *
 * Revision 1.10  1995/09/26  16:47:00  pwe
 * compare with zero to ignore previous overflow
 *
 * Revision 1.9  1995/09/13  14:25:17  pwe
 * tidy for gcc
 *
 * Revision 1.8  1995/09/08  12:51:22  pwe
 * exceptions improved
 *
 * Revision 1.7  1995/09/05  16:25:03  pwe
 * specials and exception changes
 *
 * Revision 1.6  1995/08/30  16:06:45  pwe
 * prepare exception trapping
 *
 * Revision 1.5  1995/08/23  09:42:53  pwe
 * track fpu control word for trap etc
 *
 * Revision 1.4  1995/08/14  13:53:51  pwe
 * several corrections, tail calls and error jumps
 *
 * Revision 1.3  1995/08/04  08:29:35  pwe
 * 4.0 general procs implemented
 *
 * Revision 1.2  1995/01/30  12:56:25  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  14:15:22  jmf
 * Initial revision
 *
 * Revision 1.1  1994/07/12  14:34:48  jmf
 * Initial revision
 *
**********************************************************************/


/**********************************************************************
                        instr386decs.h

   declares the higher level routines which output 80x86 instructions.

**********************************************************************/

#ifndef i386_key
#define i386_key 1


extern  void add PROTO_S ((shape sha, where a1, where a2, where dest));
extern  void absop PROTO_S ((shape sha, where a1, where dest));
extern  void maxop PROTO_S ((shape sha, where a1, where a2, where dest));
extern  void minop PROTO_S ((shape sha, where a1, where a2, where dest));
extern  void sub PROTO_S ((shape sha, where min, where from, where dest));
extern  void mult PROTO_S ((shape sha, where a1, where a2, where dest));
extern  void multiply PROTO_S ((shape sha, where a1, where a2, where dest));
extern  void div0 PROTO_S ((shape sha, where bottom, where top, where dest));
extern  void div1 PROTO_S ((shape sha, where bottom, where top, where dest));
extern  void div2 PROTO_S ((shape sha, where bottom, where top, where dest));
extern  int cmp PROTO_S ((shape sha, where from, where min, int nt, exp e));
extern  void negate PROTO_S ((shape sha, where a, where dest));
extern  void move PROTO_S ((shape sha, where from, where to));
extern  void mova PROTO_S ((where from, where to));
extern  void and PROTO_S ((shape sha, where a1, where a2, where dest));
extern  void or PROTO_S ((shape sha, where a1, where a2, where dest));
extern  void xor PROTO_S ((shape sha, where a1, where a2, where dest));
extern  void not PROTO_S ((shape sha, where a, where dest));
extern  void change_var PROTO_S ((shape sha, where from, where to));
extern  void change_var_check PROTO_S ((shape sha, where from, where to));
extern  void change_var_sh PROTO_S ((shape sha, shape fsh, where from, where to));
extern  void floater PROTO_S ((shape sha, where from, where to));
extern  void frnd0 PROTO_S ((shape sha, where from, where to));
extern  void frnd1 PROTO_S ((shape sha, where from, where to));
extern  void frnd2 PROTO_S ((shape sha, where from, where to));
extern  void frnd3 PROTO_S ((shape sha, where from, where to));
extern  void frnd4 PROTO_S ((shape sha, where from, where to));
extern  void changefl PROTO_S ((shape sha, where from, where to));
extern  void shiftl PROTO_S ((shape sha, where wshift, where from, where to));
extern  void shiftr PROTO_S ((shape sha, where wshift, where from, where to));
extern  void rotatel PROTO_S ((shape sha, where wshift, where from, where to));
extern  void rotater PROTO_S ((shape sha, where wshift, where from, where to));
extern  void mod PROTO_S ((shape sha, where bottom, where top, where dest));
extern  void rem2 PROTO_S ((shape sha, where bottom, where top, where dest));
extern  void rem0 PROTO_S ((shape sha, where bottom, where top, where dest));
extern  void long_jump PROTO_S ((exp e));
extern  void initzeros PROTO_S ((void));
extern  where zero;
extern  where fzero;
extern  where dzero;
extern  exp zeroe;
extern  where ind_reg0;
extern  where ind_reg1;
extern  where ind_sp;
extern  where sp;
extern  where bp;
extern  where reg0;
extern  where reg1;
extern  where reg2;
extern  where reg3;
extern  where reg4;
extern  where reg5;
extern  where reg_wheres[7];
extern  where pushdest;
extern  where cond1;
extern  where cond2a;
extern  where cond2b;
extern  int cond1_set;
extern  int cond2_set;
extern  void decstack PROTO_S ((int longs));
extern  void callins PROTO_S ((int longs, exp ind, int ret_stack_dec));
extern  void jumpins PROTO_S ((exp ind));
extern  void retins PROTO_S ((void));
extern  int inmem PROTO_S ((where w));
extern  void fl_binop PROTO_S((unsigned char op, shape sha, where arg1, where arg2,
          where dest, exp last_arg));
extern  void fl_multop PROTO_S ((unsigned char op, shape sha, exp arglist, where dest));
extern  void fl_neg PROTO_S ((shape sha, where from, where to));
extern  void fl_abs PROTO_S ((shape sha, where from, where to));
extern  void test PROTO_S ((shape sha, where a, where b));
extern  void fl_comp PROTO_S ((shape sha, where pos, where neg, exp e));
extern  where flstack;
extern  int in_fl_reg PROTO_S ((exp e));
extern  int in_fstack PROTO_S ((exp e));
extern  void movecont PROTO_S ((where from, where to, where length, int nooverlap));
extern  void load_stack0 PROTO_S ((void));
extern  int in_reg PROTO_S ((exp e));
extern  void end_contop PROTO_S ((void));
extern  int top_regsinuse;
extern  int lsmask[33];
extern  int first_fl_reg;
extern  int fstack_pos;
extern  exp overflow_e;
extern  void stack_return PROTO_S ((int longs));
extern  int bad_from_reg PROTO_S ((where f));

extern  void bits_to_mem PROTO_S ((exp e, exp d, ash stack));
extern  void mem_to_bits PROTO_S ((exp e, shape sha, where dest, ash stack));

extern  void setup_fl_ovfl PROTO_S ((exp e));
extern  void test_fl_ovfl PROTO_S ((exp e, where dest));
extern void reset_fpucon PROTO_S ((void));
extern exp find_stlim_var PROTO_S ((void));
extern void checkalloc_stack PROTO_S ((where sz, int b));	/* uses reg1 */
extern void special_ins PROTO_S ((char * id, exp args, where dest));

extern exp ferrmem;
extern int ferrsize;
extern int fpucon;
extern int cmp_64hilab;

extern void save_stack PROTO_S ((void));
extern void restore_stack PROTO_S ((void));

extern void start_asm PROTO_S ((void));
extern void end_asm PROTO_S ((void));
extern void asm_ins PROTO_S ((exp e));


#endif

