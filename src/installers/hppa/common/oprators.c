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


/*
$Log: oprators.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:03  release
 * First version to be checked into rolling release.
 *
 * Revision 1.9  1997/01/29  10:19:14  wfs
 *    Fixed a minor bug in "move.c" and "oprators.c" due to immediates of  >
 * 14 bits appearing in the field of ldo instrcutions.
 *
 * Revision 1.8  1996/11/25  13:43:25  wfs
 *    Fixed the comm_op register tracking bug in "oprators.c" and removed a
 * few superfluous "#if 0"s.
 *
 * Revision 1.7  1996/08/30  09:02:30  wfs
 * Various fixes of bugs arising from avs and pl_tdf tests.
 *
 * Revision 1.6  1996/02/15  10:09:40  wfs
 * Incorrect decrement - which I introduced in last bug fix - removed.
 *
 * Revision 1.5  1996/02/14  17:19:20  wfs
 * "next_caller_offset" and "next_callee_offset" have become special tokens
 * defined in "spec_tok.c". Bug fix to a "and_tag" optimization in
 * "oprators.c". A few bug fixes in "makecode.c" arising from the variable
 * caller tests. "promote_pars" defined in "config.h".
 *
 * Revision 1.4  1996/01/22  17:26:02  wfs
 * Bug fix to "make_stack_limit_tag".
 *
 * Revision 1.3  1996/01/17  13:51:02  wfs
 * Another adjustment to "round_tag" - avoid "_U_Qfcnvfxt_dbl_to_sgl" if the
 * error_treatment is "continue".
 *
 * Revision 1.2  1995/12/18  13:12:14  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.6  1995/10/20  14:08:29  wfs
 * gcc compilation changes.
 *
 * Revision 5.5  1995/10/13  10:44:34  wfs
 * Partial fix of a "round_with_mode" bug.
 *
 * Revision 5.4  1995/10/12  17:22:21  wfs
 * A "=" where there should have been "==".
 *
 * Revision 5.3  1995/10/10  16:50:25  wfs
 * There is a problem in the common code which means that floating_test's
 * error_treatment cannot be implemented for the time being.
 *
 * Revision 5.2  1995/10/09  13:09:29  wfs
 * Cosmetic changes.
 *
 * Revision 5.1  1995/09/15  13:04:52  wfs
 * Rewrote "quad_op" to ease reading and implementation of the quad
 * error jumps.
 *
 * Revision 5.0  1995/08/25  13:42:58  wfs
 * Preperation for August 25 Glue release
 *
 * Revision 3.4  1995/08/25  10:19:50  wfs
 * Register synonyms changed
 *
 * Revision 3.4  1995/08/25  10:19:50  wfs
 * Register synonyms changed
 *
 * Revision 3.1  95/04/10  16:27:38  16:27:38  wfs (William Simmonds)
 * Apr95 tape version.
 * 
 * Revision 3.0  95/03/30  11:18:31  11:18:31  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 * 
 * Revision 2.0  95/03/15  15:28:22  15:28:22  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 * 
 * Revision 1.7  95/02/10  11:41:20  11:41:20  wfs (William Simmonds)
 * Removed call to evaluated() - initialising expressions are now
 * stored in a linked list and written to outf after the procedure
 * body has been translated (c.f. translate_capsule).
 * 
 * Revision 1.6  95/01/25  13:37:44  13:37:44  wfs (William Simmonds)
 * Refined error_jump of float plus, minus, mult, div.
 * 
 * Revision 1.5  95/01/25  10:31:56  10:31:56  wfs (William Simmonds)
 * First attempt at installing error_jump in the float plus, minus, mult
 * and div tags.
 * 
 * Revision 1.4  95/01/23  18:58:04  18:58:04  wfs (William Simmonds)
 * Cosmetic changes to do_comm and non_comm_op.
 * 
 * Revision 1.3  95/01/17  17:30:00  17:30:00  wfs (William Simmonds)
 * Changed name of an included header file.
 * 
 * Revision 1.2  95/01/12  11:27:16  11:27:16  wfs (William Simmonds)
 * Corrected bug in `logical_op' which was causing hppatrans
 * to fail to bootstrap.
 * 
 * Revision 1.1  95/01/11  13:14:24  13:14:24  wfs (William Simmonds)
 * Initial revision
 * 
*/


#define HPPATRANS_CODE
#include "config.h"
#include "codehere.h"
#include "expmacs.h"
#include "addrtypes.h"
#include "inst_fmt.h"
#include "move.h"
#include "maxminmacs.h"
#include "getregs.h"
#include "guard.h"
#include "tags.h"
#include "shapemacs.h"
#include "bitsmacs.h"
#include "common_types.h"
#include "myassert.h"
#include "labels.h"
#include "frames.h"
#include "oprators.h"

#define isdbl(e) ( ( bool ) ( name ( e ) != shrealhd ) )


#if use_long_double
#include "externs.h"
#include "install_fns.h"
#include "regmacs.h"
#include "exp.h"
#include "out.h"
#include "locate.h"
#include "eval.h"
#include "muldvrem.h"
#include "proc.h"
#include "basicread.h"
#include "inst_fmt.h"
#endif

extern long trap_label PROTO_S ((exp));
extern void trap_handler PROTO_S ((baseoff,int,int));
extern baseoff zero_exception_register PROTO_S ((space));
extern labexp current,first;


int long_double_0 = 0;

/* corrects possible overflows of chars and shorts in reg r */
void tidyshort 
    PROTO_N ( ( r, s ) )
    PROTO_T ( int r X shape s )
{
  if (name(s) == ucharhd)
     riir_ins(i_dep,c_,0,23,24,r);
  else if (name(s) == uwordhd)
     riir_ins(i_dep,c_,0,15,16,r);
}


 /*
  * given a list of expressions seq which contains one whose value is in
  * register reg, removes that exp from seq and delivers 1; otherwise delivers
  * 0
  */
bool regremoved 
    PROTO_N ( ( seq, reg ) )
    PROTO_T ( exp * seq X int reg )
{
  exp s = *seq;
  exp t = bro(s);

  if (ABS_OF(regofval(s)) == reg)
  {
    (*seq) = t;
    return 1;
  }
  for (;;)
  {
    if (ABS_OF(regofval(t)) == reg)
    {
      bro(s) = bro(t);
      if (last(t))
	setlast(s);
      return 1;
    }
    if (last(t))
    {
      return 0;
    }
    s = t;
    t = bro(t);
  }
}



/*
 *   logical operation, lop, with operands immediate, i, and register, r
 */
void logical_op
    PROTO_N ( (lop,i,r,d) )
    PROTO_T ( CONST char *lop X long i X int r X int d )
{
   int t;
   if (r==d)
      t=GR1; 
   else
      t=d;
   if (lop==i_and && i==-1)
   {
      if (r!=d)
	 rr_ins(i_copy,r,d);
      return;
   }
   else if ( lop==i_and && IS_POW2((i+1)))
   {
      int p=0;
      while ( i & (1<<p) ) p++;
      if (r==d)
	 iiir_ins(i_depi,c_,0,31-p,32-p,d);
      else
	 riir_ins(i_extru,c_,r,31,p,d);
      return;
   }
   else if ( lop==i_and && IS_POW2((-i)) )
   {
      int p=0;
      while ( (i & (1<<p))==0 ) p++;
      if (r!=d)
	 rr_ins(i_copy,r,d);
      iiir_ins(i_depi,c_,0,31,p,d);
      return;
   }
   else if ( lop==i_or )
   {
      if (r==0)
      {
	 imm_to_r(i,d);
	 return;
      }
      else 
      if (i==-1)
      {
	 ir_ins(i_ldi,fs_,"",-1,d);
	 return;
      }
      else
      {
	 int j=0;
	 unsigned int p=i;
	 while ( (p & (1<<j))==0 ) j++;
	 p=p>>j;
	 if (((p+1)&p)==0)
	 {
	    int k=0;
	    while ( p & (1<<k) ) k++;
	    if (r!=d)
	       rr_ins(i_copy,r,d);
	    iiir_ins(i_depi,c_,-1,31-j,k,d);
	    return;
	 }
      }
   }
   if (SIMM14(i))
   {
      ir_ins(i_ldi,fs_,"",i,t);
      rrr_ins(lop,c_,r,t,d);
   }
   else
   if (SIMM14(~i) && lop==i_and)
   {
      ir_ins(i_ldi,fs_,"",~i,t);
      rrr_ins(i_andcm,c_,r,t,d);
   }
   else
   if ( ((i&(i+1))==0) && lop==i_and)
   {
       unsigned long ui = i;
       int nbits=0;
       while (ui != 0)
       {
	 nbits++;
	 ui=ui>>1;
       }
       riir_ins(i_zdep,c_,r,31,nbits,d);
   }
   else
   {
      imm_to_r(i,t);
      rrr_ins(lop,c_,r,t,d);
   }
}



 /*
  * evaluates the fixed operation seq1 rins seq 2 rins...., into reg final,
  * using sp as free t-regs
  */
void do_comm 
    PROTO_N ( ( seq, sp, final, rins ) )
    PROTO_T ( exp seq X space sp X int final X ins_p rins )
{
  int r = 0;
  space nsp;
  int a1;
  int a2;
  exp next = bro(seq);

  if ( name(seq)==not_tag &&
       last(next) &&
       rins==i_and &&
       name(next)!=val_tag )
  {
     a1=reg_operand(son(seq), sp);
     nsp = guardreg(a1, sp);
     a2=reg_operand(next, nsp);
     rrr_ins(i_andcm,c_,a2,a1,final);
     return;
  }

  if ( name(next)==not_tag &&
      last(next) && 
      rins==i_and &&
      name(seq)!=val_tag )
  {
     a1=reg_operand(seq, sp);
     nsp = guardreg(a1, sp);
     a2=reg_operand(son(next), nsp);
     rrr_ins(i_andcm,c_,a1,a2,final);
     return;
  }

  if ( name(next)==val_tag &&
       last(next) &&
       rins==i_and &&
       name(seq)==shr_tag )
  {
     exp shift=bro(son(seq));
     if (name(shift)==val_tag)
     { 
	int n,s;
	n=no(next);
	s=no(shift);
	if ( IS_POW2((n+1)) )
	{
	   int p=0;
	   a1=reg_operand(son(seq), sp);
	   while ( n & (1<<p) ) p++;
	   if ( p > (32-s) )
	      p = 32-s;
	   riir_ins(i_extru,c_,a1,31-s,p,final);
	   return;
	}
     }
  }


  /* evaluate 1st operand into a1 */
  
  if ( name(seq)==cont_tag && name(bro(seq))==val_tag && last(bro(seq))
       && !(props(son(seq)) & inreg_bits) )
  {
     reg_operand_here(seq, sp, final);
     a1 = final;
  }
  else
     a1 = reg_operand(seq, sp);

  if ( name(father(seq))==make_stack_limit_tag )
  {
     baseoff b;
     b.offset = FP_BOFF.offset;
     b.base = a1;
     ld_ins(i_lw,0,b,b.base);
  }

  for (;;)
  {
    nsp = guardreg(a1, sp);
    seq = bro(seq);
    if (name(seq) == val_tag)	/* next operand is a constant */
    {
      int n=no(seq);
      if (last(seq))
      {
	if (rins==i_add)
	{
	   if (SIMM14(n))
	      ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,n,a1,final);
	   else
	   {
	      ir_ins(i_addil,fs_L,empty_ltrl,n,a1);
	      ld_ir_ins(i_ldo,cmplt_,fs_R,empty_ltrl,n,GR1,final);
	   }
	}
	else
	   logical_op(rins,n,a1,final);
	return;
      }
      else
      {
	 if (r == 0)
	     r = getreg(sp.fixed);
	 if (rins==i_add)
	 {
	   if (SIMM14(n))
	      ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,n,a1,r);
	   else
	   {
	      ir_ins(i_addil,fs_L,empty_ltrl,n,a1);
	      ld_ir_ins(i_ldo,cmplt_,fs_R,empty_ltrl,n,GR1,r);
	   }
	 }
	 else
	    logical_op(rins,n,a1,r);
      }
    }
    else
    {
       exp sq = seq;
       CONST char *ins = rins;

       a2 = reg_operand(sq, nsp);
       /* evaluate next operand */
       if (last(seq))
       {
 	  rrr_ins(ins,c_,a1,a2,final);
	  return;
       }
       else
       {
	  if (r == 0)
	     r = getreg(sp.fixed);
	  rrr_ins(ins,c_,a1,a2,r);
       }
    }
    a1 = r;
  }
}



/* evaluate commutative operation rrins given by e into d, using sp to get t-regs */
int comm_op 
    PROTO_N ( ( e, sp, d, rrins ) )
    PROTO_T ( exp e X space sp X where d X ins_p rrins )
{
  CONST char *rins = rrins;

  switch (discrim ( d.answhere ))
  {
  case inreg:
    {
      int dest = regalt(d.answhere);
      bool usesdest = regremoved(&son(e), dest);
      exp seq = son(e);

      /*
       * the destination is in a register; take care that we dont alter it
       * before possible use as an operand ....
       */
      if (usesdest && last(seq))
      {
	/* used, but there is only one other operand */
	if (name(seq)==val_tag)
	{
	   int n = no(seq);
	   if (rrins==i_add)
	   {
	      if (SIMM14(n))
		 ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,n,dest,dest);
	      else
	      {
		 ir_ins(i_addil,fs_L,empty_ltrl,n,dest);
		 ld_ir_ins(i_ldo,cmplt_,fs_R,empty_ltrl,n,GR1,dest);
	      }
	   }
	   else
	      logical_op(rins,n,dest,dest);
	}
	else
	   rrr_ins(rins,c_,dest,reg_operand(seq,sp),dest);
	if (optop(e))
	   tidyshort(dest, sh(e));
	return dest;
      }
      else if (usesdest)
      {
	/* dest used, use temp */
	int r = getreg(sp.fixed);

	do_comm(seq, sp, r, rins);
	rrr_ins(rins,c_,dest,r,dest);
	if (optop(e))
	   tidyshort(dest, sh(e));
	return dest;
      }
      else
      {
	/* dest not used, evaluate into dest */
	do_comm(seq, sp, dest,rins);
	if (optop(e))
	   tidyshort(dest, sh(e));
	return dest;
      }
    }				/* end inreg */
  default:
    {
      ans a;
      int r = getreg(sp.fixed);
      space nsp;
      bool rok = 1;
      setregalt(a, r);
      do_comm(son(e), sp, r, rins);
      /* evaluate the expression into r ... */
      if (discrim(d.answhere) != notinreg)
      {
	 if (optop(e))
	    tidyshort(r, sh(e));
      }
      else
	 rok = shape_size(sh(e))==32;
      nsp = guardreg(r, sp);
      move(a, d, nsp.fixed, 1);
      /* ... and move into a */
      return ((rok)?r:NOREG);
    }				/* notinreg */
  }				/* end switch */
}



int non_comm_op 
    PROTO_N ( ( e, sp, dest, rins ) )
    PROTO_T ( exp e X space sp X where dest X ins_p rins )
 /* evalate binary operation e with rins into dest */
{
   exp l = son(e);
   exp r = bro(l);
   int a1 = reg_operand(l, sp);
   space nsp;
   int a2;
   CONST char *ins;
   ins=rins;
   nsp = guardreg(a1, sp);
   a2 = reg_operand(r, nsp);
   if (discrim( dest.answhere )==inreg)
   {
      int d = regalt(dest.answhere);
      rrr_ins(ins,c_,a1,a2,d);
      if (optop(e))
	 tidyshort(d, sh(e));
      return d;
   }
   else
   {
      /* destination elsewhere */
      ans a;
      int r1 = getreg(nsp.fixed);
      setregalt(a, r1);
      rrr_ins(ins,c_,a1,a2,r1);
      if (optop(e))
	 tidyshort(r1, sh(e));
      nsp = guardreg(r1, sp);
      move(a, dest, nsp.fixed, 1);
      return r1;
   }
}

int monop 
    PROTO_N ( ( e, sp, dest, ins ) )
    PROTO_T ( exp e X space sp X where dest X ins_p ins )
 /* evaluate fixed monadic operation e using ins into dest */
{
   int r1 = getreg(sp.fixed);
   int a1 = reg_operand(son(e), sp);

   /* operand in reg a1 */
   space nsp;

   if ( discrim(dest.answhere) == inreg )
   {
      /* destination in register */
      int d = regalt(dest.answhere);
      if (ins==i_subi)
	 rrr_ins(i_sub,c_,0,a1,d);
      else
      if (ins==i_sub)
	 rrr_ins(i_sub,c_,0,a1,d);
      else
	 rrr_ins(i_uaddcm,c_,0,a1,d);
      if (optop(e))
	 tidyshort(d,sh(e));
      return d;
   }
   else
   {
      /* destination elsewhere */
      ans a;
      setregalt(a, r1);
      if (ins==i_subi)
	 rrr_ins(i_sub,c_,0,a1,r1);
      else
      if (ins==i_sub)
	 rrr_ins(i_sub,c_,0,a1,r1);
      else
	 rrr_ins(i_uaddcm,c_,0,a1,r1);
      if (optop(e))
	 tidyshort(r1, sh(e));
      nsp = guardreg(r1, sp);
      move(a, dest, nsp.fixed, 1);
      return r1;
   }
}


#if use_long_double

/*
    GET THE ADDRESS OF A LONG DOUBLE
*/
static void quad_addr
    PROTO_N ( (e,r,sp) )
    PROTO_T ( exp e X int r X space sp )
{
    instore is ;
    if (name(e)==real_tag)
    {
	labexp next;
	next  = (labexp) malloc( sizeof(struct labexp_t) );
	next->e = e;
	next->lab = next_data_lab();
	next->next = (labexp) 0;
	current->next = next;
	current = next;
	is.adval = 0;
	is.b.offset = 0;
	is.b.base = next->lab;
    }
    else
    {
       where w ;
       w=locate1(e,sp,sh(e),0) ;
       if (discrim(w.answhere)!=notinreg) 
	  failer ("Illegal expression in quad_addr");
       is=insalt(w.answhere) ;
    }
    if (is.adval)
    {
	failer("Illegal expression in quad_addr") ;
    }
    if (IS_FIXREG(is.b.base))
    {
       if (is.b.offset==0)
       {
	  if (is.b.base!=r)
	     rr_ins(i_copy,is.b.base,r) ;
       }
       else
	  ld_ins(i_lo,1,is.b,r) ;
    }
    else
       set_ins("",is.b,r) ;
    return ;
}


/*
    LONG DOUBLE LIBRARY
*/

static struct {
		  CONST char proc_name[32] ;
		  bool called ;
	      } long_double_lib [ 14 ] =
	      {
		  { "_U_Qfcmp", 0 },
		  { "_U_Qfadd", 0 },
		  { "_U_Qfsub", 0 },
		  { "_U_Qfmpy", 0 },
		  { "_U_Qfdiv", 0 },
		  { "_U_Qfcnvff_dbl_to_quad", 0 },
		  { "_U_Qfcnvff_sgl_to_quad", 0 },
		  { "_U_Qfcnvxf_dbl_to_quad", 0 },
		  { "_U_Qfcnvxf_sgl_to_quad", 0 },
		  { "_U_Qfcnvff_quad_to_dbl", 0 },
		  { "_U_Qfcnvff_quad_to_sgl", 0 },
		  { "_U_Qfabs", 0 },
		  { "_U_Qfcnvfxt_quad_to_sgl", 0 },
		  { "_U_Qfrnd", 0 }
	      } ;


void import_long_double_lib
    PROTO_Z ()
{
   int n;
   for(n=0; n<14; n++)
      if ( long_double_lib[n].called )
	 fprintf(outf,"\t.IMPORT\t%s,CODE\n",long_double_lib[n].proc_name);
   if (long_double_0)
   {
      outnl();
      outs("\t.DATA\n");
      outs("$qfp_lit_sym$\n");
      outs("\t.ALIGN\t8\n");
      outs("\t.STRINGZ \"\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\"\n");
      outs("\t.STRINGZ \"?\\xFF\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\"\n");
   }
}


/*
    DO A QUAD FLOAT OPERATION
*/
void quad_op
    PROTO_N ( ( e, sp, dest ) )
    PROTO_T ( exp e X space sp X where dest )
{
   char *s=0,*stub=0;
   bool quad_ret = 1 ;

   switch ( name(e) )
   {
      case test_tag:
      {
	 /* Quad comparisons */
	 exp l,r;
	 int tn;
	 quad_ret = 0 ;
	 s = "_U_Qfcmp";
	 stub = "ARGW0=GR,ARGW1=GR,ARGW2=GR";
	 long_double_lib[0].called=1;
	 sp = guardreg(ARG2,sp);
	 tn = (int)test_number(e);
	 if ( tn < 1 || tn > 6 )
	 {
	    fail ( "Illegal floating-point test" ) ;
	 }
	 ir_ins(i_ldi, fs_, empty_ltrl, tn==1 ? 17 : tn==2 ? 21 : tn==3 ? 9 : tn==4 ? 13 : tn==5 ? 4 : 25,               ARG2);
	 if ( IsRev(e) )
	 {
	    r = son(e);
	    l = bro(r);
	 }
	 else
	 {
	    l = son(e);
	    r = bro(l);
	 }
	 quad_addr(l,ARG0,sp) ;
	 sp = guardreg(ARG0,sp) ;
	 quad_addr(r,ARG1,sp) ;
	 break;
      }
      case fneg_tag : 
      {
	 baseoff b;
	 b.base=0; b.offset=0;
	 s = "_U_Qfsub" ;
	 long_double_lib[2].called=1;
	 set_ins("$qfp_lit_sym$",b,ARG0);
	 sp = guardreg(ARG0,sp);
	 quad_addr(son(e),ARG1,sp) ;
	 sp = guardreg(ARG1,sp);
	 stub = "ARGW0=GR,ARGW1=GR";
	 long_double_0 = 1;
	 break ;
      }
      case fabs_tag :
      {
	 s = "_U_Qfabs" ;
	 long_double_lib[11].called=1;
	 stub = "ARGW0=GR";
	 quad_addr(son(e),ARG0,sp) ;
	 break ;
      }
      case chfl_tag :
      {
 	 ans aa ;
	 where w ;
	 freg frg ;
	 exp l;
	 if ( name(sh(e)) == doublehd )
	 {
	    baseoff b;
	    b.base=SP;
	    l = son(e);
	    if ( name(sh(l)) == doublehd )
	       return;
	    else 
	    if  (name(sh(l))==realhd)
	    {
	       s = "_U_Qfcnvff_dbl_to_quad" ;
	       long_double_lib[5].called=1;
	       frg.dble=1;
	       frg.fr=5;
	       stub = "ARGW0=FR,ARGW1=FU";
	    }
	    else
	    {
	       s = "_U_Qfcnvff_sgl_to_quad" ;
	       long_double_lib[6].called=1;
	       frg.dble=0;
	       frg.fr=4;
	       stub = "ARGW0=FR";
	    }
	    setfregalt ( aa, frg ) ;
	    w.answhere = aa ;
	    w.ashwhere = ashof (sh(l)) ;
	    code_here(l,sp,w);
	    if (frg.dble)
	    {
	       b.offset=-40;
	       stf_ins(i_fstd,(5*3)+1,b);
	       ld_ins(i_ldw,1,b,ARG1);
	       b.offset+=4;
	       ld_ins(i_ldw,1,b,ARG0);
	    }
	    else
	    {
	       b.offset=-36;
	       stf_ins(i_fstw,(4*3)+0,b);
	       ld_ins(i_ldw,1,b,ARG0);
	    }
	 }
	 else
	 {
	    if ( isdbl(sh(e)) )
	    {
	       s = "_U_Qfcnvff_quad_to_dbl";
	       long_double_lib[9].called=1;
	    }
	    else
	    {
	       s = "_U_Qfcnvff_quad_to_sgl";
	       long_double_lib[10].called=1;
	    }
	    stub = "ARGW0=GR";
	    quad_ret = 0;
	    quad_addr(son(e),ARG0,sp) ;
	 }
	 break ;
      }
      case float_tag :
      {
	 exp l = son(e);
	 reg_operand_here(l,sp,ARG0);
	 sp = guardreg(ARG0,sp);
	 if ( name(sh(l))==ulonghd )
	 {
	    rr_ins(i_copy,0,ARG1);
	    long_double_lib[7].called=1;
	    s = "_U_Qfcnvxf_dbl_to_quad" ;
	    stub = "ARGW0=GR,ARGW1=GR";
	 }
	 else
	 {
	    s = "_U_Qfcnvxf_sgl_to_quad" ;
	    long_double_lib[8].called=1;
	    stub = "ARGW0=GR";
	 }
	 break ;
      }
      case round_tag :
      {
	 if ( round_number(e)==3 && errhandle(e)<2 )
	 {
	    s = "_U_Qfcnvfxt_quad_to_sgl";
	    long_double_lib[12].called=1;
	 }
	 else
	 {
	    s = "_U_Qfcnvff_quad_to_dbl";
	    long_double_lib[9].called=1;
	 }
	 stub = "ARGW0=GR";
	 quad_ret = 0;
	 quad_addr(son(e),ARG0,sp) ;
	 break;
      }
#if 0
      /* Binary operations */
      {
	 stub = "ARGW0=GR,ARGW1=GR";
	 break ;
      }
#endif
      case fplus_tag :
      case fminus_tag : 
      case fmult_tag :
      case fdiv_tag :
      {
	 exp l,r;
	 if ( name(e) == fplus_tag )
	 {
	    s = "_U_Qfadd" ;
	    long_double_lib[1].called=1;
	 }
	 else
	 if ( name(e) == fminus_tag )
	 {
	   s = "_U_Qfsub" ; 
	   long_double_lib[2].called=1;
	 }
	 else
	 if ( name(e) == fmult_tag )
	 {
	    s = "_U_Qfmpy" ; 
	    long_double_lib[3].called=1;
	 }
	 else
	 {
	    s = "_U_Qfdiv" ;
	    long_double_lib[4].called=1;
	 }
	 stub = "ARGW0=GR,ARGW1=GR";
	 if ( IsRev(e) )
	 {
	    r = son(e);
	    l = bro(r);
	 }
	 else
	 {
	    l = son(e);
	    r = bro(l);
	 }
	 quad_addr(l,ARG0,sp) ;
	 sp = guardreg(ARG0,sp) ;
	 quad_addr(r,ARG1,sp) ;
	 break ;
      }
      default :
	fail ( "Illegal floating-point operation" ) ;
   }
   if (quad_ret)
   {
      instore is ;
      is = insalt(dest.answhere);
      if (discrim(dest.answhere)!=notinreg)
	  failer("Illegal expression in quad_op");
      if (is.adval)
      {
	 if (IS_FIXREG(is.b.base))
	 {
	    if (is.b.offset==0)
	       rr_ins(i_copy,is.b.base,RET0) ;
	    else
	       ld_ins(i_lo,1,is.b,RET0) ;
	 } 
	 else
	    set_ins("",is.b,RET0) ;
      }
      else
	 ld_ins(i_lw,1,is.b,RET0) ;
   }
   /* ..and make call */
   call_ins(cmplt_,s,RP,stub) ;
#if 1
   if (!optop(e) && name(e)!=test_tag)
   {
      int trap = trap_label(e);
      baseoff b;
      int end;
      if (quad_ret)
      {
	 instore is ;
	 end=new_label();
	 is = insalt(dest.answhere);
	 if (discrim(dest.answhere)!=notinreg)
	    failer("Illegal expression in quad_op");
	 if (is.adval)
	 {
	    if (IS_FIXREG(is.b.base))
	    {
	       if (is.b.offset==0)
		  rr_ins(i_copy,is.b.base,RET0) ;
	       else
		  ld_ins(i_lo,1,is.b,RET0) ;
	    } 
	    else
	       set_ins("",is.b,RET0) ;
	 }
	 else
	    ld_ins(i_lw,1,is.b,RET0) ;
	 b.base =  RET0; b.offset = 4;
	 ld_ins(i_lw,1,b,T3);
	 cj_ins( c_neq, 0, T3, end ) ;         
	 b.offset+=4;
	 ld_ins(i_lw,1,b,T3);
	 cj_ins( c_neq, 0, T3, end ) ;         
	 b.offset+=4;
	 ld_ins(i_lw,1,b,T3);
	 cj_ins( c_neq, 0, T3, end ) ;         
	 b.offset=0;
	 ld_ins(i_lw,1,b,T3);
	 imm_to_r(2147418112,T4);
	 cj_ins( c_eq, T4, T3, trap ) ;         
	 imm_to_r(-65536,T4);
	 cj_ins( c_eq, T4, T3, trap ) ;         
	 outlab("L$$",end);
      }
      else
      if ( name(e) == chfl_tag )
      {
	 if ( isdbl(sh(e)) )
	 {
	    baseoff b;
	    b = mem_temp(0);
	    end = new_label();
	    stf_ins(i_fstd,3*4+1,b);
	    b.offset+=4;
	    ld_ins(i_lw,1,b,T3);
	    cj_ins( c_neq, 0, T3, end ) ;         
	    b.offset-=4;
	    ld_ins(i_lw,1,b,T3);
	    imm_to_r(2146435072,T4);
	    cj_ins( c_eq, T4, T3, trap ) ;         
	    imm_to_r(-1048576,T4);
	    cj_ins( c_eq, T4, T3, trap ) ;         
	    outlab("L$$",end);
	 }
	 else
	 {
	    baseoff b;
	    b = mem_temp(0);
	    stf_ins(i_fstw,3*4,b);
	    ld_ins(i_lw,1,b,T3);
	    imm_to_r(2139095040,T4);
	    cj_ins( c_eq, T4, T3, trap ) ;         
	    imm_to_r(-8388608,T4);
	    cj_ins( c_eq, T4, T3, trap ) ;         
	 }
      }
   }
#endif
   clear_t_regs() ;
   return ;
}

#endif


int fop
    PROTO_N ( (e, sp, dest, ins) )
    PROTO_T ( exp e X space sp X where dest X ins_p ins )
{
   /* Evaluate floating dyadic operation e using ins into dest. If
      !optop(e), then we have two fixed point registers at our disposal */
   exp l = son(e);
   exp r = bro(l);
   int a1,a2,dble;
   space nsp;
   freg fr;
   ans aa;
   baseoff b;

#if use_long_double
   if (name(sh(e))==doublehd)
   {
      /* i.e. quads */
      quad_op( e, sp, dest );
      return (NOREG) ;
   }
#endif


   dble=( name(sh(e))==realhd ? 1 : 0 );
   if (IsRev(e))
   {
      a2 = freg_operand(r, sp, getfreg(sp.flt));
      nsp = guardfreg(a2, sp);
      a1 = freg_operand(l, nsp, getfreg(nsp.flt));
   }
   else
   {
      a1 = freg_operand(l, sp, getfreg(sp.flt));
      nsp = guardfreg(a1, sp);
      a2 = freg_operand(r, nsp, getfreg(nsp.flt));
   }
   if ( (discrim(dest.answhere)) == infreg )
      fr = fregalt(dest.answhere);
   else
   {
      fr.fr = getfreg(nsp.flt);
      fr.dble = (dest.ashwhere.ashsize == 64) ? 1 : 0;
      setfregalt(aa, fr);
   }
   if (!optop(e))
   {
      b = zero_exception_register(nsp);
   }
   if (dble)
      rrrf_ins(ins,f_dbl,(3*a1)+1,(3*a2)+1,(3*fr.fr)+1);
   else
      rrrf_ins(ins,f_sgl,3*a1,3*a2,3*fr.fr);
   if (!optop(e))
   {
      trap_handler(b,trap_label(e),EXCEPTION_CODE);
   }
   if ( (discrim(dest.answhere)) != infreg )
      move(aa, dest, sp.fixed, 1);
   return ( dble ? -(fr.fr + 32) : (fr.fr + 32) );
}
