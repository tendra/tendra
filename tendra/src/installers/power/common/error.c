/*
    Copyright (c) 1993 Open Software Foundation, Inc.


    All Rights Reserved


    Permission to use, copy, modify, and distribute this software
    and its documentation for any purpose and without fee is hereby
    granted, provided that the above copyright notice appears in all
    copies and that both the copyright notice and this permission
    notice appear in supporting documentation.


    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING
    ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE.


    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
    WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

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



/**********************************************************************
$Author: release $
$Date: 1998/02/04 15:48:44 $
$Revision: 1.2 $
$Log: error.c,v $
 * Revision 1.2  1998/02/04  15:48:44  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:56  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:00:25  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#include "config.h"
#include <limits.h>
#include "memtdf.h"
#include "codegen.h"
#include "comment.h"
#include "translat.h"
#include "makecode.h"
#include "stack.h"
#include "instruct.h"
#include "externs.h"
#include "error.h"
#include "myassert.h"
#include "flpttypes.h"
#include "me_fns.h"

/* Labels to call the error handler */
/* NOTE there are three one for each ERROR_CODE */
/* nil_access,overflow,stack_overflow */

static long nil_access_lab=0;
static long overflow_lab=0;
static long stack_overflow_lab=0;

void init_proc_errors PROTO_S ((exp));
void output_error_labels PROTO_S ((void));
long get_nil_access_lab PROTO_S ((void));
long get_overflow_lab PROTO_S ((void));
long get_stack_overflow_lab PROTO_S ((void));


void test_signed PROTO_S ((int,long,long,long));
void test_unsigned PROTO_S ((int,long,long));
static long trap_label PROTO_S ((exp));
static void do_exception PROTO_S ((int));
static void call_TDFhandler PROTO_S ((void));


/* integer error treatments */
int abs_error_treatment PROTO_S ((exp,space,where));
int chvar_error_treatment PROTO_S ((exp,space,where));
void div_error_treatment PROTO_S ((int,int,exp));
int minus_error_treatment PROTO_S ((exp,space,where));
int mult_error_treatment PROTO_S ((exp,space,where));
int plus_error_treatment PROTO_S ((exp,space,where));
int neg_error_treatment PROTO_S ((exp,space,where));
void rem_error_treatment PROTO_S ((int,int,exp));
void round_error_treatment PROTO_S ((exp *));

/* floating error treatments */
void chfl_error_treatment PROTO_S ((exp,int));
void do_fmop_error_jump PROTO_S ((exp,int,int));
void do_fop_error_jump PROTO_S ((exp,int,int,int));


/*
 * init_proc_errors: initialises variables used
 */
void init_proc_errors PROTO_N ((e)) PROTO_T (exp e)
{
  /* clear the error code labels */
  nil_access_lab = 0;
  overflow_lab = 0;
  stack_overflow_lab = 0;
  
  if (proc_has_checkstack(e))
  {
    baseoff b;
    int cr = next_creg();
    long err_lab = get_stack_overflow_lab();
    
    b = find_tg("__TDFstacklim");
    ld_ins(i_l,b,R_TMP0);
    cmp_rr_ins(i_cmp,R_SP,R_TMP0,cr);
    long_bc_ins(i_blt,cr,err_lab,UNLIKELY_TO_JUMP);
  }
  return;
}
/*
 * output_error_labels:
 * Sets up the labels at the end of the proc to handle
 * the three error codes
 */
void output_error_labels PROTO_Z ()
{
  if (nil_access_lab != 0)
  {
    set_label(nil_access_lab);
    do_exception(f_nil_access);
  }
  if (overflow_lab != 0)
  {
    set_label(overflow_lab);
    do_exception(f_overflow);
  }
  if (stack_overflow_lab!=0)
  {
    set_label(stack_overflow_lab);
    rir_ins(i_a,R_SP,p_frame_size,R_SP); /* collapse stack frame */
    do_exception(f_stack_overflow);
  }
  return;
}
/*
 * get_nil_access_lab returns the label to jump to
 * when a nil_access error_code is created
 * or sets it if it is un-initialized
 */
long get_nil_access_lab PROTO_Z ()
{
  if (nil_access_lab == 0)
  {
    nil_access_lab = new_label();
  }
  return nil_access_lab;
}
/*
 * get_overflow_lab returns the label to jump to
 * when an overflow error_code is created
 * or sets it if it is un-initialized
 */
long get_overflow_lab PROTO_Z ()
{
  if (overflow_lab == 0)
  {
    overflow_lab = new_label();
  }
  return overflow_lab;
}
/*
 * get_stack_overflow_lab returns the label to jump to
 * when a stack_overflow error_code is created
 * or sets it if it is un-initialized
 */
long get_stack_overflow_lab PROTO_Z ()
{
  if (stack_overflow_lab == 0)
  {
    stack_overflow_lab = new_label();
  }
  return stack_overflow_lab;
}
/*
 * do_trap is called from make_code and branches to
 * the corresponding error label depending on which
 * error code needs to be invoked
 */
void do_trap PROTO_N ((e)) PROTO_T (exp e )
{
  int err_code = no(e);
  long err_lab;
  
  if (err_code == f_nil_access)
  {
    err_lab = get_nil_access_lab();
  }
  else if (err_code == f_overflow)
  {
    err_lab = get_overflow_lab();
  }
  else if (err_code == f_stack_overflow)
  {
    err_lab = get_stack_overflow_lab();
  }
  else
  {
    fail("do_trap::Unknown error code");
  }
  uncond_ins(i_b,err_lab);
  clear_all();
  return;
}

/*
 * test_signed: tests whether a register lies
 * between two values and
 * jumps to label if it does not 
 */
void test_signed PROTO_N ((r,lower,upper,lab)) 
    PROTO_T (int r X long lower X long upper X long lab)
{
  int creg1=next_creg();
  int creg2=next_creg();
  cmp_ri_ins(i_cmp,r,lower,creg1);
  long_bc_ins(i_blt,creg1,lab,UNLIKELY_TO_JUMP);
  cmp_ri_ins(i_cmp,r,upper,creg2);
  long_bc_ins(i_bgt,creg2,lab,UNLIKELY_TO_JUMP);
  return;
}
/*
 * test_unsigned: tests whether a register is greater than an unsigned number
 */
void test_unsigned PROTO_N ((r,maxval,lab)) PROTO_T (int r X long maxval X long lab)
{
  int creg=next_creg();
  cmp_ri_ins(i_cmpl,r,maxval,creg);
  long_bc_ins(i_bgt,creg,lab,UNLIKELY_TO_JUMP);
  return;
}

/*
 * trap_label: Gives a label for the destination of the error
 */
static long trap_label PROTO_N ((e)) PROTO_T (exp e)
{
  if (NO_ERROR_TREATMENT(e))
  {
    fail("No error treatment");
    return 0;
  }
  else if (ERROR_TREATMENT_IS_TRAP(e))
  {
    return get_overflow_lab();
  }
  else
  {
    /* Error jump to destination */
    return no(son(pt(e)));
  }
}
/* 
 * Generates a call to the TDFhandler for exceptions
 */
static void do_exception PROTO_N ((ex)) PROTO_T (int ex)
{
  ld_const_ins(ex,R_FIRST_PARAM);/* __TDFhandler takes as its first parameter, the error code */
  call_TDFhandler();
  return;
}
static void call_TDFhandler PROTO_Z ()
{
  baseoff b;
  b = find_tg("__TDFhandler");
  ld_ins(i_l,b,R_TMP0);
  
  b.base = R_TMP0;
  b.offset = 0;
  ld_ro_ins(i_l,b,R_TMP0);comment("Jump to error handler");
  /* We don't come back from calling error handler */
  mt_ins(i_mtctr,R_TMP0);
  z_ins(i_bctr);
  return;
}



/*****************************/
/*                           */
/* INTEGER  error treatments */
/*                           */
/*****************************/

/*
 * ABS
 */
int abs_error_treatment PROTO_N ((e,sp,dest))
    PROTO_T (exp e X space sp X where dest)
{
  int r = reg_operand(son(e),sp);
  int destr = regfrmdest(&dest,sp);
  long trap = trap_label(e);
  ans aa;
  int cr;
  space nsp;
  nsp = guardreg(destr,sp);
  switch(name(sh(e)))
  {
   case ucharhd:
   case uwordhd:
   case ulonghd:
    break;
   case scharhd:	
    cr = next_creg();
    cmp_ri_ins(i_cmp,r,0xffffff80,cr);
    long_bc_ins(i_beq,cr,trap,UNLIKELY_TO_JUMP);
    break;
   case swordhd:
    cr = next_creg();
    cmp_ri_ins(i_cmp,r,0xffff8000,cr);
    long_bc_ins(i_beq,cr,trap,UNLIKELY_TO_JUMP);
    break;
   case slonghd:
    cr = next_creg();
    cmp_ri_ins(i_cmp,r,0x80000000,cr);
    long_bc_ins(i_beq,cr,trap,UNLIKELY_TO_JUMP);
    break;
   default:
    fail("Unknown Integer shape for abs_tag\n");
  }
  rr_ins(i_abs,r,destr);
  setregalt(aa,destr);
  return move(aa,dest,nsp.fixed,1);
}

/*
 * CHVAR
 */
int chvar_error_treatment PROTO_N ((e,sp,dest))
    PROTO_T (exp e X space sp X where dest)
{
  int r = reg_operand(son(e),sp);
  ans aa;
  int new_shpe = name(sh(e));
  long trap = trap_label(e);
  bool sgned = is_signed(sh(son(e)));
  
  setregalt(aa,r);
  switch(new_shpe)		/* switch on the new shape */
  {
   case scharhd:
    {
      if(sgned)
      {
	test_signed(r,-128,127,trap);
      }
      else
      {
	test_unsigned(r,127,trap);
      }
      break;
    }
   case ucharhd:
    {
      test_unsigned(r,255,trap);
    }
    break;
   case swordhd:
    {
      if(sgned)
      {
	test_signed(r,-0x8000,0x7fff,trap);
      }
      else
      {
	test_unsigned(r,0x7fff,trap);
      }
    }
    break;
   case uwordhd:
    {
      test_unsigned(r,0xffff,trap);
    }
    break;
   case slonghd:
    if(!sgned)
    {
      test_unsigned(r,0x7fffffff,trap);
    }
    break;
   case ulonghd:
    if(sgned)
    {
      test_unsigned(r,0x7fffffff,trap);
    }
    break;
   default:
    fail("Unknown integer shape in chvar_tag");
  }
  return move(aa,dest,sp.fixed,1);
}
/*
 * DIV0,DIV1,DIV2
 */
void div_error_treatment PROTO_N ((l,r,e))
    PROTO_T (int l X int r X exp e )
{
  int creg  = next_creg();
  int creg2 = next_creg();
  int creg3 = next_creg();
  
  long trap = trap_label(e);
  long lab ;
  
  long minus_infinity=0;
  
  /* First test for division by zero */
  cmp_ri_ins(i_cmp,r,0,creg);  
  long_bc_ins(i_beq,creg,trap,UNLIKELY_TO_JUMP);
  
  /* Test for -(infinity)/-1 for signed*/
  if (is_signed(sh(e)))
  {
    lab=new_label();
    cmp_ri_ins(i_cmp,r,-1,creg2);
    bc_ins(i_bne,creg2,lab,LIKELY_TO_JUMP);
    switch(name(sh(e)))
    {
     case slonghd:minus_infinity = 0x80000000;break;
     case swordhd:minus_infinity = 0xffff8000;break;
     case scharhd:minus_infinity = 0xffffff80;break;
     default:fail("Should not get here\n");
    }
    cmp_ri_ins(i_cmp,l,minus_infinity,creg3);
    long_bc_ins(i_beq,creg3,trap,UNLIKELY_TO_JUMP);
    set_label(lab);
  }
  return;
}



/*
 * MINUS_TAG
 */
int minus_error_treatment PROTO_N ((e,sp,dest)) 
    PROTO_T (exp e X space sp X where dest)
{
  int lhs_reg=reg_operand(son(e),sp);
  int rhs_reg;
  int destr;
  long trap = trap_label(e);
  ans aa;
  rhs_reg=reg_operand(bro(son(e)),guardreg(lhs_reg,sp));
  destr=regfrmdest(&dest,sp);
  setregalt(aa,destr);
  /* Both sides evaluated lhs in lhs_reg ,rhs in rhs_reg*/
  switch(name(sh(e)))
  {
   case slonghd:
    {
      rrr_ins(i_sfo,rhs_reg,lhs_reg,destr);
      mf_ins(i_mcrxr,0);
      long_bc_ins(i_bgt,0,trap,UNLIKELY_TO_JUMP);
      break;
    }
   case ulonghd:
    {
      rrr_ins(i_sfo,rhs_reg,lhs_reg,destr);
      mf_ins(i_mcrxr,0);
      long_bc_ins(i_bne,0,trap,UNLIKELY_TO_JUMP);
      break;
    }
   case swordhd:
    {
      rrr_ins(i_sf,rhs_reg,lhs_reg,destr);
      test_signed(destr,-0x8000,0x7fff,trap);
      break;
    }
   case uwordhd:
    {
      rrr_ins(i_sf,rhs_reg,lhs_reg,destr);
      test_unsigned(destr,0xffff,trap);
      break;
    }
   case scharhd:
    {
      rrr_ins(i_sf,rhs_reg,lhs_reg,destr);
      test_signed(destr, -128, 127, trap);
      break;
    }
   case ucharhd:
    {
      rrr_ins(i_sf,rhs_reg,lhs_reg,destr);
      test_unsigned(destr, 255, trap);
      break;
    }
   default:
    fail("NOT integer in minus with o/f");
  }
  return move(aa, dest, sp.fixed, 1);
}

/*
 * MULT_TAG
 */
int mult_error_treatment PROTO_N ((e,sp,dest)) PROTO_T (exp e X space sp X where dest)
{
  int lhs_reg=reg_operand(son(e),sp);
  int rhs_reg;
  int destr;
  long trap = trap_label(e);
  space nsp;
  ans aa;
  nsp=guardreg(lhs_reg,sp);
  rhs_reg=reg_operand(bro(son(e)),nsp);
  nsp=guardreg(rhs_reg,nsp);
  destr=regfrmdest(&dest,sp);
  setregalt(aa,destr);
  /* Both sides evaluated lhs in lhs_reg,rhs in rhs_reg*/
  switch(name(sh(e)))
  {
   case slonghd:
    {
      rrr_ins(i_mulso,lhs_reg,rhs_reg,destr);
      /* This should set the SO and OV bits of XER both to 1 if there is
	 an overflow */
      mf_ins(i_mcrxr,0);
      long_bc_ins(i_bgt,0,trap,UNLIKELY_TO_JUMP);
      break;
    }
   case ulonghd:
    {
      int creg=next_creg();
      
      if(architecture==POWERPC_CODE)
      {
	/* easy since we have mulhwu */
	rrr_ins(i_mulhwu,lhs_reg,rhs_reg,R_TMP0);
      }
      else
      {
	int tmp_reg;
	space nsp;
	int lab   = new_label();
	int lab2  = new_label();
	int creg  = next_creg();
	int creg2 = next_creg();
	int creg3 = next_creg();
	nsp = guardreg(lhs_reg,sp);
	nsp = guardreg(rhs_reg,nsp);
	
	tmp_reg=getreg(nsp.fixed);
	ld_const_ins(0,tmp_reg);
	cmp_ri_ins(i_cmp,lhs_reg,0,creg);
	bc_ins(i_bgt,creg,lab,LIKELY_TO_JUMP);
	mov_rr_ins(lhs_reg,tmp_reg);comment(NIL);
	set_label(lab);
	cmp_ri_ins(i_cmp,rhs_reg,0,creg2);
	bc_ins(i_bgt,creg2,lab2,LIKELY_TO_JUMP);
	rrr_ins(i_a,rhs_reg,tmp_reg,tmp_reg);
	set_label(lab2);
	rir_ins(i_sl,tmp_reg,1,tmp_reg);
	rrr_ins(i_mul,lhs_reg,rhs_reg,R_TMP0);
	rrr_ins(i_a,R_TMP0,tmp_reg,tmp_reg);
	cmp_ri_ins(i_cmp,tmp_reg,0,creg3);
	long_bc_ins(i_bne,creg3,trap,UNLIKELY_TO_JUMP);
	
      }
      
      cmp_ri_ins(i_cmp,R_TMP0,0,creg);
      long_bc_ins(i_bne,creg,trap,UNLIKELY_TO_JUMP);
      rrr_ins(i_muls,lhs_reg,rhs_reg,destr);
      /* if the high part of the answer is non-zero branch to trap */
      break;
    }
   case swordhd:
    {
      rrr_ins(i_muls,lhs_reg,rhs_reg,destr);
      test_signed(destr,-0x8000,0x7fff,trap);
      break;
    }
   case uwordhd:
    {
      rrr_ins(i_muls,lhs_reg,rhs_reg,destr);
      test_unsigned(destr,0xffff,trap);
      break;
    }
   case scharhd:
    {
      rrr_ins(i_muls,lhs_reg,rhs_reg,destr);
      test_signed(destr, -128, 127, trap);
      break;
    }
   case ucharhd:
    {
      rrr_ins(i_muls,lhs_reg,rhs_reg,destr);
      test_unsigned(destr, 255, trap);
      break;
    }
   default:
    fail("NOT integer in mult with o/f");
  }
  return move(aa, dest, nsp.fixed, 1);
}

/*
 * PLUS_TAG
 */
int plus_error_treatment PROTO_N ((e,sp,dest)) 
    PROTO_T (exp e X space sp X where dest )
{
  int lhs_reg=reg_operand(son(e),sp);
  int rhs_reg;
  int destr;
  long trap = trap_label(e);
  ans aa;
  
  rhs_reg = reg_operand(bro(son(e)),guardreg(lhs_reg,sp));
  destr=regfrmdest(&dest,sp);
  setregalt(aa,destr);
  switch(name(sh(e)))
  {
   case slonghd:
    {
      rrr_ins(i_ao,lhs_reg,rhs_reg,destr);
      mf_ins(i_mcrxr,0);
      long_bc_ins(i_bgt,0,trap,UNLIKELY_TO_JUMP);
      break;

    }
   case ulonghd:
    {
      rrr_ins(i_ao,lhs_reg,rhs_reg,destr);
      mf_ins(i_mcrxr,0);
      long_bc_ins(i_beq,0,trap,UNLIKELY_TO_JUMP);
      break;
    }
   case swordhd:
    {
      rrr_ins(i_a,lhs_reg,rhs_reg,destr);
      test_signed(destr,-0x8000,0x7fff,trap);
      break;
    }
   case uwordhd:
    {
      rrr_ins(i_a,lhs_reg,rhs_reg,destr);
      test_unsigned(destr,0xffff,trap);
      break;
    }
   case scharhd:
    {
      rrr_ins(i_a,lhs_reg,rhs_reg,destr);
      test_signed(destr, -128, 127, trap);
      break;
    }
   case ucharhd:
    {
      rrr_ins(i_a,lhs_reg,rhs_reg,destr);
      test_unsigned(destr, 255, trap);
      break;
    }
   default:
    fail("NOT integer shape in plus with overflow");
  }
  return move(aa, dest, sp.fixed, 0);
}
#if 0
/* 
 * ROUND
 * This is now done in installl_fns.c 
 */
void round_error_treatment PROTO_N ((e)) PROTO_T (exp *e)
{
  /* float --> int */
  exp round = *e;
  exp fl =son(*e);
  shape fl_shpe = sh(fl);
  bool trap = ERROR_TREATMENT_IS_TRAP(round);
  bool lower_strict,upper_strict;
  exp lower_bound;
  exp lower_adjustment;
  exp upper_bound;
  exp upper_adjustment;
  exp lower;
  exp upper;
  exp test_lower;
  exp test_upper;
  exp id;
  exp lab;
  exp clear;
  exp zero1;
  exp zero2;
  exp seq1;
  exp seq2;
  exp cond;
  
  ASSERT(shape_size(sh(round))==32);
  if (name(sh(round))==ulonghd)
  {
    lower_bound = me_u3(fl_shpe,me_shint(ulongsh,0)       ,float_tag);
    upper_bound = me_u3(fl_shpe,me_shint(ulongsh,UINT_MAX),float_tag);
  }
  else
  {
    lower_bound = me_u3(fl_shpe,me_shint(slongsh,INT_MIN),float_tag);
    upper_bound = me_u3(fl_shpe,me_shint(slongsh,INT_MAX),float_tag);
  }
  switch(round_number(round))
  {
   case R2ZERO:/* -1+l < f < 1+u */
    {
      lower_adjustment = me_u3(fl_shpe,me_shint(slongsh,-1),float_tag);
      upper_adjustment = me_u3(fl_shpe,me_shint(slongsh,1),float_tag);
      lower_strict = 1;
      upper_strict = 1;
      break;
    }
   case 4:/* round as state is same as round to nearest */
   case R2NEAR:/* -0.5+l < f < 0.5+u */
    {
      exp minus_one;
      exp one;
      exp two;
      
      minus_one = me_u3(fl_shpe,me_shint(slongsh,-1),float_tag);
      two = me_u3(fl_shpe,me_shint(slongsh,2),float_tag);
      lower_adjustment = me_b3(fl_shpe,minus_one,two,fdiv_tag);
      one = me_u3(fl_shpe,me_shint(slongsh,1),float_tag);
      two = me_u3(fl_shpe,me_shint(slongsh,2),float_tag);
      upper_adjustment = me_b3(fl_shpe,one,two,fdiv_tag);
      lower_strict = 1;
      upper_strict = 1;
      break;
    }
    
   case R2PINF:/* -1 +l < f =< u */
    {
      lower_adjustment = me_u3(fl_shpe,me_shint(slongsh,-1),float_tag);
      upper_adjustment = me_u3(fl_shpe,me_shint(slongsh,0),float_tag);
      lower_strict = 1;
      upper_strict = 0;
      break;
    }
    
   case R2NINF:/* l =< f < 1+u */
    {
      lower_adjustment = me_u3(fl_shpe,me_shint(slongsh,0),float_tag);
      upper_adjustment = me_u3(fl_shpe,me_shint(slongsh,1),float_tag);
      lower_strict = 0;
      upper_strict = 1;
      break;
    }
  }
  
  lower = me_b3(fl_shpe,lower_bound,lower_adjustment,fplus_tag);
  upper = me_b3(fl_shpe,upper_bound,upper_adjustment,fplus_tag);
  
  id = me_startid(fl_shpe,fl,0);/* start ident */
  
  clear = getexp(f_bottom,nilexp,0,nilexp,nilexp,0,0,clear_tag);

  if(trap)
  {
    exp t = getexp(f_bottom,nilexp,0,nilexp,nilexp,0,f_overflow,trap_tag);
    lab = me_b3(f_bottom,clear,t,labst_tag);
  }
  else
  {
    exp g = getexp(f_bottom,nilexp,0,nilexp,pt(round),0,0,goto_tag);
    lab = me_b3(f_bottom,clear,g,labst_tag);
  }
  

  test_lower = me_q1(no_nat_option,
		     lower_strict?f_greater_than:f_greater_than_or_equal,
		     &lab,
		     me_obtain(id),
		     lower,
		     test_tag);
  test_upper = me_q1(no_nat_option,
		     upper_strict?f_less_than:f_less_than_or_equal,
		     &lab,
		     me_obtain(id),
		     upper,
		     test_tag);
  zero1 = me_u3(f_top,test_lower,0);
  seq1 = me_b3(sh(test_upper),zero1,test_upper,seq_tag);
  cond = me_b3(f_top,seq1,lab,cond_tag);
  zero2 = me_u3(f_top,cond,0);
  seq2 = me_b3(fl_shpe,zero2,me_obtain(id),seq_tag);
  id = me_complete_id(id,seq2);
  
  seterrhandle(round,0);
  
  setlast(id);
  bro(id) = round;
  son(round) = id;
}
#endif
  
/*
 * NEG
 */
int neg_error_treatment PROTO_N ((e,sp,dest))
    PROTO_T (exp e X space sp X where dest )
{
  int r = reg_operand(son(e),sp);
  int destr = regfrmdest(&dest,sp);
  long trap = trap_label(e);
  ans aa;
  int cr; 
  space nsp;
  nsp = guardreg(destr,sp);

  switch (name(sh(e)))
  {
   case ucharhd:
   case uwordhd:
   case ulonghd:
    rr_ins(i_neg_cr,r,destr);
    long_bc_ins(i_bne,CRF0,trap,LIKELY_TO_JUMP);
    break;
   case scharhd:
    cr = next_creg();
    cmp_ri_ins(i_cmp,r,0xffffff80,cr);
    rr_ins(i_neg,r,destr);
    long_bc_ins(i_beq,cr,trap,UNLIKELY_TO_JUMP);
    break;
   case swordhd:
    cr = next_creg();
    cmp_ri_ins(i_cmp,r,0xffff8000,cr);
    rr_ins(i_neg,r,destr);
    long_bc_ins(i_beq,cr,trap,UNLIKELY_TO_JUMP);
    break;
   case slonghd:
    cr = next_creg();
    cmp_ri_ins(i_cmp,r,0x80000000,cr);
    rr_ins(i_neg,r,destr);
    long_bc_ins(i_beq,cr,trap,UNLIKELY_TO_JUMP);
    break;
   default:
    fail("Unknown Integer shape for neg tag\n");
  }
  setregalt(aa,destr);
  return move(aa,dest,nsp.fixed,1);
}
/*
 * REM0,REM1,REM2
 */
void rem_error_treatment PROTO_N ((l,r,e))
    PROTO_T (int l X int r X exp e )
{
  int creg  = next_creg();
  long trap = trap_label(e);

  cmp_ri_ins(i_cmp,r,0,creg);  
  long_bc_ins(i_beq,creg,trap,UNLIKELY_TO_JUMP);
  return;
}

/*****************************/
/*                           */
/* FLOATING error treatments */
/*                           */
/*****************************/
void chfl_error_treatment PROTO_N ((e,f)) PROTO_T (exp e X int f)
{
  long trap = trap_label(e);
  
  ASSERT(name(e)==chfl_tag);
  rrf_ins(i_frsp_cr,f,f);
  mcrfs_ins(CRF0,0);
  long_bc_ins(i_bso,CRF0,trap,UNLIKELY_TO_JUMP);
  return;
}


void do_fmop_error_jump PROTO_N ((e,fs,fd)) 
    PROTO_T (exp e X int fs X int fd )
{
  long trap = trap_label(e);
  Instruction_P ins;

  switch(name(e))
  {
   case fabs_tag:ins=i_fabs;break;
   case fneg_tag:ins=i_fneg;break;
   default:fail("Unknown error jump for fmop");break;
  }
  rrf_ins(ins,fs,fd);
  mcrfs_ins(CRF0,0);
  long_bc_ins(i_bso,CRF0,trap,UNLIKELY_TO_JUMP);
  if(is_single_precision(sh(e)))
  {
    rrf_ins(i_frsp,fd,fd);
    mcrfs_ins(CRF0,0);
    long_bc_ins(i_bso,CRF0,trap,UNLIKELY_TO_JUMP);
  }
  return;
}
void do_fop_error_jump PROTO_N ((e,fs1,fs2,fd)) 
    PROTO_T (exp e X int fs1 X int fs2 X int fd )
{
  long trap = trap_label(e);
  Instruction_P ins;
   
  switch (name(e))
  {
   case fplus_tag: ins = i_fa;break;
   case fminus_tag:ins = i_fs;break;
   case fmult_tag: ins = i_fm;break;
   case fdiv_tag:  ins = i_fd;break;
   default:fail("Unknown error jump for fop");
  }
  rrrf_ins(ins,fs1,fs2,fd);
  mcrfs_ins(CRF0,0);
  long_bc_ins(i_bso,CRF0,trap,UNLIKELY_TO_JUMP);
  switch(name(e))
  {
    /* div by 0 */
   case fdiv_tag:
    {
      mcrfs_ins(CRF0,1);
      long_bc_ins(i_bgt,CRF0,trap,UNLIKELY_TO_JUMP);
    }
  }
  if(is_single_precision(sh(e)))
  {
    rrf_ins(i_frsp,fd,fd);
    mcrfs_ins(CRF0,0);
    long_bc_ins(i_bso,CRF0,trap,UNLIKELY_TO_JUMP);
  }
  return;
}
