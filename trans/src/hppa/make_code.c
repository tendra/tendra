/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <string.h>
#include <stdio.h>

#include <shared/check.h>
#include <shared/error.h>
#include <shared/xalloc.h>

#include <local/ash.h>
#include <local/out.h>

#include <reader/exp.h>
#include <reader/externs.h>
#include <reader/basicread.h>

#include <construct/installtypes.h>
#include <construct/ash.h>
#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/shape.h>
#include <construct/install_fns.h>
#include <construct/f64.h>
#include <construct/misc_c.h>
#include <construct/reg_result.h>

#include <main/driver.h>
#include <main/flags.h>
#include <main/print.h>

#include <refactor/optimise.h>
#include <refactor/refactor.h>

#include "addrtypes.h"
#include "new_tags.h"
#include "maxminmacs.h"
#include "proctypes.h"
#include "eval.h"
#include "move.h"
#include "oprators.h"
#include "getregs.h"
#include "guard.h"
#include "locate.h"
#include "code_here.h"
#include "inst_fmt.h"
#include "hppains.h"
#include "bitsmacs.h"
#include "labels.h"
#include "regexps.h"
#include "regmacs.h"
#include "regable.h"
#include "muldvrem.h"
#include "proc.h"
#include "stabs_diag3.h"
#include "translate.h"
#include "frames.h"
#include "make_code.h"
#include "extratags.h"
#include "special.h"
#include "loc_signal.h"
#include "labexp.h"
#include "localexpmacs.h"

#define outp fprintf
#define isdbl(e)((bool)(name(e)!= shrealhd))

int repeat_level;                 /* init by proc */
outofline *odd_bits;             /* init by proc */
int last_odd_bit;
int doing_odd_bits;
static exp crt_proc;
where nowhere;
int do_indexed_loads = 1;

extern char export[128];
extern int leaf;
extern labexp current,first;
extern int RSCOPE_LEVEL,RSCOPE_LABEL;
extern exp find_named_tg(char *, shape);
extern baseoff find_tg(char* s);

#define GETREG(d, s)(discrim((d).answhere) == inreg ?\
			  regalt((d).answhere):\
			  getreg((s).fixed))

#define GETFREG(d, s)(discrim((d).answhere) == infreg ?\
			  regalt((d).answhere):\
			  getfreg((s).flt))

#define TARGET(f)(main_globals[(-boff(son(f)).base) -1] ->dec_u.dec_val.dec_id)

baseoff zero_exception_register
(space sp)
{
   baseoff b;
   int r = getreg(sp.fixed);
   ld_ins(i_lo,0,mem_temp(0),r);
   b.base = r;  b.offset = 0;
   st_ins(i_sw,GR0,b);
   ldf_ins(i_fldw,b,0);
   return b;
}

void trap_handler
(baseoff b, int trap, int excep)
{
   stf_ins(i_fstw,0,b);
   ld_ins(i_lb,0,b,b.base);
   ir_ins(i_ldi,fs_,empty_ltrl,excep,GR1);
   rrr_ins(i_and,c_eq,b.base,GR1,0);
   ub_ins(cmplt_N,trap);
}

long trap_label
(exp e)
{
   if ((errhandle(e) &3) ==3)
   {
      if (aritherr_lab==0)
	 aritherr_lab = new_label();
      return aritherr_lab;
   }
   else
      return no(son(pt(e)));
}

void reset_tos
(void)
{
   st_ins(i_sw,SP,SP_BOFF);
}

void test_if_outside_of_var
(unsigned char v, int r, int trap)
{
   if (v==ucharhd)
   {
      riir_ins(i_extru,c_,r,31,8,1);
      cj_ins(c_neq,1,r,trap);
   }
   else
   if (v==scharhd)
   {
      riir_ins(i_extrs,c_,r,31,8,1);
      cj_ins(c_neq,1,r,trap);
   }
   else
   if (v==uwordhd)
   {
      riir_ins(i_extru,c_,r,31,16,1);
      cj_ins(c_neq,1,r,trap);
   }
   else
   if (v==swordhd)
   {
      riir_ins(i_extrs,c_,r,31,16,1);
      cj_ins(c_neq,1,r,trap);
   }
}


typedef struct postl_ {exp pl; struct postl_ * outer; } postl_chain;
static postl_chain * old_pls;

void update_plc
(postl_chain * ch, int ma)
{
   while (ch != NULL)
   {
      exp pl= ch->pl;
      while (name(pl) ==ident_tag && name(son(pl)) ==caller_name_tag)
      {
	 no(pl) += ma;
	 pl = bro(son(pl));
      }
      ch = ch->outer;
   }
}

/*
 * Ensure everywhere has a checknan() that needs one (cf. mips)
 */
void checknan
(exp e, int fr)
{
	UNUSED(e);
	UNUSED(fr);

#if 0
  long trap = no(son(pt(e)));
  int t = (ABS_OF(fr) - 32) << 1;

  asm_comment("checknan: %%f%d trap=%d", t, trap);
  error(ERR_SERIOUS, "checknan");
#endif
}

/*
 * Start of volatile use
 */
void setvolatile
(void)
{
/*    outs(";\t.volatile\n" ) ;  */
}

/* end of volatile use */
void setnovolatile
(void)
{
/*    outs(";\t.nonvolatile\n" ) ;  */
}

/*
 * Unsigned branch table
 */
static const char *(usbranch_tab[]) =
{
   c_,  /* never branch (shouldn't be used) */
   c_gequ,
   c_gu,
   c_lequ,
   c_lu,
   c_neq,
   c_eq,
};


#define usbranches(i)(usbranch_tab[i])

/*
 * Signed branch table
 */
const char *(sbranch_tab[]) =
{
   c_,  /* never branch (shouldn't be used) */
   c_geq,
   c_g,
   c_leq,
   c_l,
   c_neq,
   c_eq,
   c_TR,
};

#define sbranches(i)(sbranch_tab[i])

static const char *(fbranch_tab[]) =
{
   c_,  /* never branch (shouldn't (be used) */
   c_g,
   c_geq,
   c_l,
   c_leq,
   c_eq,
   c_neq,
};

#define fbranches(i)(fbranch_tab[i])

/* used to invert TDF tests */
long notbranch[] ={7,4,3,2,1,6,5,0};

/*
 * Find the last test in sequence e which is a branch to second,
 * if any, otherwise nil
 */
static exp testlast
(exp e, exp second)
{
  if (name(e) == test_tag && pt(e) == second)
  {
    return e;
  }
  if (name(e) == seq_tag)
  {
    if (name(bro(son(e))) == test_tag && pt(bro(son(e))) == second)
    {
      return bro(son(e));
    }
    else if (name(bro(son(e))) == top_tag)
    {
      exp list = son(son(e));

      for (;;)
      {
	if (last(list))
	{
	  if (name(list) == test_tag && pt(list) == second)
	  {
	    return list;
	  }
	  else
	  {
	    return 0;
	  }
	}
	else
	{
	  list = bro(list);
	}
      }
    }
  }
  return 0;
}

bool last_param
(exp e)
{
  if (!isparam(e))
    return 0;
  e = bro(son(e));
aa:if (name(e) == ident_tag && isparam(e)
			    && name(son(e))!= formal_callee_tag)
    return 0;
  if (name(e) == diagnose_tag)
  {
    e = son(e);
    goto aa;
  }
  return 1;
}

/* Does e, or components of e, contain a bitfield? */
/* +++ should detect this earlier && record in props(e) once-and-for-all */
static int has_bitfield
(exp e)
{
  if (e == NULL)
    return 0;
  switch (name(e))
  {
  case compound_tag:
    {

	/*
	 * (compound_tag <offset> <initialiser> ... )
	 */
      /* look at alignment of initialisers */
      e = bro(son(e));
      while (1)
      {
	if (has_bitfield(e))
	  return 1;		/* found bitfield */

	if (last(e))
	  return 0;		/* all done, no bitfield */

	e = bro(bro(e));	/* try next initialiser */
      }
      /* NOTREACHED */
  default:
      return ashof(sh(e)).ashalign == 1;	/* found bitfield */
    }
    /* NOTREACHED */
  }
  /* NOTREACHED */
}

/*
 * Convert all NON-bitfields from byte-offsets back to bit-offsets,
 * so the compound can be output correctly by eval().
 * Permanently undoes the needscan.c:scan() case val_tag:.
 *
 * NB must do this EXACTLY ONCE.
 */
static void fix_nonbitfield
(exp e)
{
  if (name(e) == compound_tag)
  {
    e = son(e);
    while (1)
    {
      if (name(e) == val_tag && name(sh(e)) == offsethd && al2(sh(e)) >= 8)
	  no(e) = no(e) << 3;	/* fix it */

      fix_nonbitfield(bro(e));	/* recursively fix the rest of the struct */

      if (last(bro(e)))
	  return;		/* all done */

      e = bro(bro(e));	/* next pair */
    }
  }
}


void restore_callees
(void)
{
	/*
	 * Puts back on the stack those callees, if any, which were kept in
	 * registers.
	 */

   exp bdy = son(crt_proc);
   while (name(bdy) ==dump_tag || name(bdy) ==diagnose_tag)
       bdy = son(bdy);
   while (name(bdy) ==ident_tag && isparam(bdy) && name(son(bdy))!=formal_callee_tag)
   {
      bdy = bro(son(bdy));
   }
   while (name(bdy) ==ident_tag && isparam(bdy))
   {
      exp sbdy = son(bdy);
      baseoff b;
      b.base = Has_vcallees ? FP : EP;
      b.offset = (no(sbdy) -callees_offset) >>3;
      if (props(bdy) & infreg_bits)
      {
      }
      else
      if (props(bdy) &inreg_bits)
      {
	 st_ins(i_sw,no(bdy),b);
      }
      bdy = bro(sbdy);
   }
}


exp find_ote
(exp e, int n)
{
   exp d = father(e);
   while (name(d)!=apply_general_tag)
      d = father(d);
   d = son(bro(son(d))); /* list otagexps */
   while (n !=0)
   {
      d = bro(d);
      n--;
   }
   assert(name(d) ==caller_tag);
   return d;
}


void do_exception
(int e)
{
   baseoff b;
   ir_ins(i_ldi,fs_,"",e,ARG0);
   b = boff(find_named_tg("__hppahandler",f_pointer(f_alignment(f_proc))));
   ld_ins(i_lw, 1, b, GR22);
   call_millicode(MILLI_DYNCALL, RP, "", 1);
}

space do_callers
(exp list, space sp, char *stub)
{
   int off = 8<<5;
   int fixpar,fltpar;
   char s[16];
   instore is;
   is.b.base = SP;
   is.adval = 1;
   stub[0] ='\t';
   stub[1] =0;
   for (;;)
   {
      /* Evaluate parameters in turn. */
      where w;
      ash ap;
      int par_al;
      int par_sz;
      exp par = (name(list) ==caller_tag)? son(list): list;
      int hd = name(sh(list));
      ap = ashof(sh(list));
      w.ashwhere = ap;
      par_sz = (ap.ashsize > 32)? 64 : 32;
      off+=par_sz;
      if (par_sz==64 && !is_floating(name(sh(list))) && !valregable(sh(list)))
	 par_al = 64;
      else
	 par_al = (ap.ashalign < 32)? 32 : ap.ashalign;
      off = rounder(off,par_al);
      is.b.offset = - (off>>3);
      if (is_floating(hd) && off< (13<<5))
      {
	 freg frg;
	 ans ansfr;
	 frg.fr = (fltpar = (off>>5) -5);
	 if (hd==shrealhd)
	 {
	    frg.dble = 0;
	    sprintf(s,"ARGW%d=FR ",fltpar-4);
	    strcat(stub,s);
	 }
	 else
	 {
	    frg.dble = 1;
	    if (off== (10<<5))
	       strcat(stub,"ARGW0=FR ARGW1=FU ");
	    else
	       strcat(stub,"ARGW2=FR ARGW3=FU ");
	 }
	 setfregalt(ansfr,frg);
	 w.answhere = ansfr;
	 /* Evaluate parameter into floating parameter register. */
	 code_here(par,sp,w);
	 sp = guardfreg(frg.fr, sp);
#if 1
	/*
	 * This "#if" statement copies parameters passed in floating
	 * point registers to the corresponding fixed point registers.
	 * It is neccessary to ensure that possible varargs are correctly
	 * dumped on the stack.
	 */
	 fixpar = ARG0+ (off>>5) -9;
	 if (hd == shrealhd)
	 {
	    stf_ins(i_fstw,(frg.fr*3),is.b);
	    ld_ins(i_ldw,1,is.b,fixpar);
	    sp = guardreg(fixpar,sp);
	 }
	 else
	 {
	    stf_ins(i_fstd,(frg.fr*3) +1,is.b);
	    ld_ins(i_ldw,1,is.b,fixpar);
	    sp = guardreg(fixpar,sp);
	    is.b.offset += 4;
	    fixpar -= 1;
	    ld_ins(i_ldw,1,is.b,fixpar);
	    sp = guardreg(fixpar,sp);
	 }
#endif
      }
      else
      if (valregable(sh(list)) && off< (13<<5))
      {
	 ans ansr;
	 setregalt(ansr,fixpar = ARG0+ (off>>5) -9);
	 w.answhere = ansr;
	 /* Evaluate parameter into fixed parameter register. */
	 code_here(par,sp,w);
	 sp = guardreg(fixpar,sp);
	 sprintf(s,"ARGW%d=GR ",fixpar-ARG0);
	 strcat(stub,s);
      }
      else
      {
	 /* Evaluate parameter into argument space on stack. */
#if 1
	 if (valregable(sh(list)) && ap.ashsize<32)
	 {
		/*
		 * Byte or 16bit scalar parameter - convert to integer.
		 * We must expand source to a full word to conform to HP PA
		 * conventions. We do this by loading into a reg.
		 */
	    int r = reg_operand(par,sp);
	    st_ins(i_sw,r,is.b);
	 }
	 else
#endif
	 {
	    setinsalt(w.answhere,is);
	    code_here(par,sp,w);
	    fixpar = ARG0+ ((-is.b.offset) >>2) -9;
	    while (par_sz)
	    {
			/*
			 * Copy (parts of) compound paramater into vacant parameter
	         * registers.
			 */
	       if (fixpar<ARG3+1)
	       {
		  ld_ins(i_lw,0,is.b,fixpar);
		  sprintf(s,"ARGW%d=GR ",fixpar-ARG0);
		  strcat(stub,s);
		  sp = guardreg(fixpar,sp);
	       }
	       fixpar--;
	       is.b.offset+=4;
	       par_sz-=32;
	    }
	 }
      }
      if (name(list) == caller_tag)
      {
#if 1
	 if (shape_size(sh(list)) <32 && valregable(sh(list)))
	    no(list) = off-32+shape_size(sh(list));
	 else
#endif
	    no(list) = off;
      }
      if (last(list))
	 return sp;
      else
	 list = bro(list);
   }
   /* End "for" */
}


void do_callee_list
(exp e, space sp)
{
   long disp = 18<<5;
   if (no(e)!= 0)
   {
      exp list = son(e);
      where w;
      ash ap;
      instore is;
      is.b.base = SP;
      is.adval = 1;
      for (;;)
      {
	 ap = ashof(sh(list));
	 disp = rounder(disp, ap.ashalign);
	 is.b.offset = disp>>3;
	 w.ashwhere = ap;
	 setinsalt(w.answhere, is);
    	 code_here(list,sp,w);
	 disp = rounder(disp+ap.ashsize,32);
    	 if (last(list))break;
	 list = bro(list);
      }
   }
}

void load_reg
(exp e, int r, space sp)
{
   where w;
   w.ashwhere = ashof(sh(e));
   setregalt(w.answhere,r);
   code_here(e,sp,w);
}

/*
 * Produce code for expression e, putting its result in dest using t-regs
 * given by sp. If non-zero, exitlab is the label of where the code is to
 * continue.
 */
makeans make_code
(exp e, space sp, where dest, int exitlab)
{
  long constval=0;
  makeans mka;
  asm_comment("make_code: %d,\t%d,\tprops=%#x",
	      name(sh(e)), name(e), props(e));
  asm_comment("           space= (%ld,%ld) (%d)", sp.fixed, sp.flt, (int) discrim(dest.answhere));

 tailrecurse:
  mka.lab = exitlab;
  mka.regmove = NOREG;

  insection(text_section);
  fflush(as_file);
  switch (name(e))
  {

	/*
	 * Procedure related code selection is handled by make_XXX_tag_code()
	 * functions in proc.c.
	 */

  case env_size_tag:
  {
     exp tg = son(son(e));
     procrec * pr = &procrecs[no(son(tg))];
     constval = (pr->frame_sz+0) >> 3;
     goto moveconst;
  }


  case proc_tag: case general_proc_tag:
  {
     crt_proc = e;
     old_pls = NULL;
     return make_proc_tag_code(e, sp, dest, exitlab);
  }


  case untidy_return_tag:
#if 1
  case return_to_label_tag:
#endif
  case res_tag:
  {
     /* procedure result */
     return make_res_tag_code(e,sp,dest,exitlab);
  }

  case tail_call_tag:
  {
     exp fn = son(e);
     exp cees = bro(fn);
     bool glob = is_fn_glob(fn);
     exp bdy = son(crt_proc);
     space nsp;
     nsp = sp;

     if (name(cees) == make_callee_list_tag)
     {
	do_callee_list(cees, sp);
     }
     else
     if (name(cees) == make_dynamic_callee_tag)
     {
	baseoff b;
	int r;
	if (Has_fp)
	{
	   b.base = FP; b.offset = 68;
	}
	else
	{
	   b.base = SP; b.offset = - (frame_sz>>3) + 68;
	}
    	r = getreg(nsp.fixed);
    	load_reg(son(cees),r,nsp);
	st_ins(i_sw,r,b);
	b.offset -= 4;
    	r = getreg(nsp.fixed);
    	load_reg(bro(son(cees)),r,nsp);
	st_ins(i_sw,r,b);  /* NB The sum of the callee sizes has been put on the stack. */
     }
     else
     if (name(cees) == same_callees_tag)
     {
	restore_callees();
     }
     if (!glob)
     {
	 int r = getreg(nsp.fixed);
	 load_reg(fn, r, nsp);
	 st_ins(i_sw, r, mem_temp(0));
     }

     /* Move the callers to the correct place if neccessary. */
     bdy = son(crt_proc);
     while (name(bdy) == dump_tag || name(bdy) == diagnose_tag)
	bdy = son(bdy);
     while (name(bdy) == ident_tag && isparam(bdy)
		 	           && name(son(bdy))!= formal_callee_tag)
     {
      	exp sbdy = son(bdy);
	int pr =  props(sbdy);
#if 0
	if (pt(bdy) == NULL && diag == DIAG_NONE)
	{
	   /**  Parameter never used.  **/
	}
	else
#endif
	if (pr == 0 && (props(bdy) &inanyreg)!= 0)
	{
	   /* Parameter is passed on stack, but is kept in reg given by no(bdy). */
	   if (isvar(bdy))
	   {
	      baseoff b;
	      b.base = SP;
	      b.offset = - ((no(sbdy) +params_offset) >>3);
	      if (is_floating(name(sh(sbdy))))
	      {
		 /* Cannot occur whilst floats are kept on the stack. */
	      }
	      else
	      {
		 st_ins(i_sw,no(bdy),b);
	      }
	   }
	}
	else
	if (pr && (props(bdy) &inanyreg) == 0)
	{
	   /* Parameter is passed in reg, but is kept on stack. */
	   if (Has_no_vcallers)
	   {
	      baseoff stkpos;
	      int off,sz = shape_size(sh(sbdy));
	      off = - ((no(sbdy) +params_offset) >>3);
	      stkpos.base = Has_vcallees ? FP : EP;
	      stkpos.offset = off;
	      if (is_floating(name(sh(sbdy))))
	      {
		 ldf_ins(sz == 64 ? i_fldd : i_fldw, stkpos, pr);
	      }
	      else
	      {
		 ld_ins(i_lw, 1, stkpos, pr);
		 if (sz > 32)
		 {
			/*
			 * Parameter must be a compound passed by value with sz<=64,
			 * load the second half into register.
			 */
		    stkpos.offset+=4;
		    ld_ins(i_lw, 1, stkpos, pr-1);
		 }
	      }
	   }
	}
	else
	if (pr != 0 && props(sbdy)!= no(bdy))
	{
		/*
		 * Parameter is passed in a different register to that which it is kept in.
		 */
	   if (is_floating(name(sh(sbdy))))
	   {
	      /* Cannot occur whilst floats are kept on the stack. */
	   }
	   else
	   {
	      if (Has_no_vcallers)
		 rr_ins(i_copy, no(bdy), pr);
	      else
	      {
		 baseoff b;
		 b.base = Has_vcallees ? FP : EP;
		 b.offset = - ((((pr-GR26) <<3) +params_offset) >>3);
		 st_ins(i_sw,no(bdy),b);
	      }
	   }
	}
	bdy = bro(sbdy);
     }
     if (!Has_no_vcallers)
     {
	int r;
	baseoff b;
	b.base = Has_vcallees ? FP : EP;
	b.offset = -36;
	for (r=GR26;r<=GR23;r++)
	{
	   ld_ins(i_lw, 1, b, r);
	   b.offset-=4;
	}
     }

     if (!glob)
     {
	ld_ins(i_ldw, 1, mem_temp(0), GR22);
     }
     if (name(cees) == make_callee_list_tag)
     {
       	/* Copy callees from top of stack. */
	int i;
	baseoff b;
	b.offset = - (frame_sz>>3);
	if (!Has_fp)
	{
	   b.base = (Has_vsp ? EP : SP);
	   ld_ins(i_lo,0,b,T4);
	}
	if (call_has_vcallees(cees))
	{
	   /* Store the callee size. */
	   ir_ins(i_ldi, fs_, empty_ltrl, no(cees) >> 3, GR1);
	   st_ir_ins(i_stw, cmplt_, GR1, fs_, empty_ltrl, 64,                                       Has_fp ? FP : T4);
	}
       	for (i = 0; i < (no(cees) >> 3); i += 4)
	{
	   b.base = SP;
       	   b.offset = i + (18 << 2);
	   ld_ins(i_lw, 0, b, T3);
	   b.base = Has_fp ? FP : T4;
       	   st_ins(i_sw, T3, b);
       	}
    	/*
    	 *	sp + 72 + 0  ->  sp -(frame size) + 72 + 0
    	 *	sp + 72 + 4  ->  sp -(frame size) + 72 + 4
    	 *	sp + 72 + 8  ->  sp -(frame size) + 72 + 8
    	 *                     ....
    	 *                     ....
    	 */
	if (Has_fp)
	{
	   rr_ins(i_copy, FP, SP);
	}
	else
	{
	   rr_ins(i_copy, T4, SP);
	}
     }
     else
     if (name(cees) == make_dynamic_callee_tag)
     {
	int lb,le;
	baseoff b;

	if (Has_fp)
	   rr_ins(i_copy, FP, SP);
	else
	{
	   b.offset = - (frame_sz>>3);
	   b.base = (Has_vsp ? EP : SP);
	   ld_ins(i_lo, 0, b, SP);
	}
	b.base = SP;  b.offset = 68;

	ld_ins(i_lw,0,b,T2);
	/* T2 = pointer to the bytes constituting the dynamic callees. */
	b.offset-=4;
	ld_ins(i_lw,0,b,T3);
	/* T3 = number of bytes constituting the dynamic callees. */

	lb = new_label();
	le = new_label();
	cj_ins(c_eq, 0, T3, le);
	rrr_ins(i_add, c_, T2, T3, T4);
	ld_ir_ins(i_ldo, cmplt_, fs_, empty_ltrl, 18<<2, SP, T3);
	outlab("L$$",lb);
	ld_ir_ins(i_ldbs, cmplt_MA, fs_, empty_ltrl, 1, T2, GR1);
	comb_ins(c_l, T2, T4, lb);
	st_ir_ins(i_stbs, cmplt_MA, GR1, fs_, empty_ltrl, 1, T3);
	outlab("L$$",le);
     }
     else
     {
	if (Has_fp)
	   rr_ins(i_copy, FP, SP);
	else
	{
	   baseoff b;
	   b.offset = - (frame_sz>>3);
	   b.base = (Has_vsp ? EP : SP);
	   ld_ins(i_lo, 0, b, SP);
	}
	if (name(cees) == same_callees_tag && call_has_vcallees(cees)                    && !Has_vcallees)
	{
		/*
		 * We must store the sum of the callee sizes - it hasn't
		 * yet been done.
		 */
	      ir_ins(i_ldi, fs_, empty_ltrl, no(cees) >> 3, GR1);
	      st_ir_ins(i_stw, cmplt_, GR1, fs_, empty_ltrl, 64, SP);
	}

     }
     restore_sregs();  /**  Restore s-regs.  **/
     ld_ir_ins(i_ldw, cmplt_, fs_, empty_ltrl, -20, SP, RP);
     if (glob)
     {
	call_ins(cmplt_, TARGET(fn), 0, "");
     }
     else
     {
	call_millicode(MILLI_DYNCALL, 0, "", 1);
     }
     return mka;
  }


  case apply_tag:		/* procedure call */
  {
     exp fn = son(e);
     exp par = bro(fn);
     int hda = name(sh(e));
     int special;
     space nsp;
     int void_result = (name(sh(e)) ==tophd);
     int reg_res = reg_result(sh(e));
     makeans mka;
     exp dad = father(e);
     bool tlrecurse = RSCOPE_LEVEL==0 && (name(dad) ==res_tag) && props(dad);
     char stub[128];  /* relocation stub */
     nsp = sp;
     stub[0] ='\t';
     stub[1] ='\0';

     mka.lab = exitlab;
     mka.regmove = NOREG;

     /* first see if it is a special to be handled inline */
     if ( (special=specialfn(fn)) > 0 )   /* eg function is strlen */
     {
	mka.lab = specialmake(special,par,sp,dest,exitlab);
	return mka;
     }

     if (!last(fn))
	nsp = do_callers(par,sp,stub);

     if (!reg_res && !void_result && shape_size(sh(e)) >64)
     {
	/* structure or union result, address passed in %r28 (=RET0) */
	instore is;
	assert(discrim(dest.answhere) == notinreg);
	/* struct must be in memory */
	is = insalt(dest.answhere);
	if (is.adval)
	{
	   /* generate address of dest */
	   if (IS_FIXREG(is.b.base))
	      ld_ins(i_lo,SIGNED,is.b,RET0);
	   else
 	      set_ins("",is.b,RET0);
	}
	else
	   ld_ins(i_lw,SIGNED,is.b,RET0);
	nsp = guardreg(RET0,nsp);
     }

     if (special != 0)
     {
	extj_special_ins(special_call_name(special),RP,stub,1);
	if (PIC_code)
	   rr_ins(i_copy,GR5,GR19);
     }
     else
     if (is_fn_glob(fn))
     {
	if (!tlrecurse)
	   call_ins(cmplt_,TARGET(fn),RP,stub);
     }
     else
     {
	reg_operand_here(fn,nsp,GR22);
	call_millicode(MILLI_DYNCALL,RP,stub,1);
     }

     if (!reg_res && !void_result && (shape_size(sh(e)) <65))
     {
	/* 64 bit structure or union result returned in RET0 and RET1 */
	instore is;
	is = insalt(dest.answhere);
	if (is.adval)
	{
	   st_ins(i_sw,RET0,is.b);
	   is.b.offset+=4;
	   st_ins(i_sw,RET1,is.b);
	}
	else
	{
	   baseoff b;
	   ld_ins(i_lw,SIGNED,is.b,GR1);
	   b.base=GR1;
	   b.offset=0;
	   st_ins(i_sw,RET0,b);
	   b.offset+=4;
	   st_ins(i_sw,RET1,b);
	}
     }

     clear_all();

     if (reg_res)
     {
	ans aa;
	if (is_floating(hda))
	{
	   freg frg;
	   frg.fr = R_FR4;
	   frg.dble = (hda==shrealhd ? 0 : 1);
	   setfregalt(aa,frg);
	   move(aa,dest,sp.fixed,1);
	   /* move floating point result of application to destination */
	}
	else
	{
	   setregalt(aa,RET0);
	   if (discrim(dest.answhere) ==inreg)
	   {
	      int r = regalt(dest.answhere);
	      if (r!=RET0 && r!=GR0)
	      {
		 /* Move from RET0 */
		 move(aa,dest,sp.fixed,1);
	      }
	      mka.regmove = RET0;
	   }
	   else
	   {
	      /* dest not inreg */
	      move(aa,dest,sp.fixed,1);
	   }
	}
     }
     return mka;
  }

  case apply_general_tag:
  {
      exp fn = son(e);
      exp cers = bro(fn);
      exp cees = bro(cers);
      exp pl = bro(cees);
      space nsp;
      char stub[128];  /* relocation stub */
      stub[0] ='\t';
      stub[1] ='\0';

      if (no(cers)!=0)
	 nsp = do_callers(son(cers),sp,stub);
      else
	 nsp = sp;

     IGNORE make_code(cees,nsp,nowhere,0);

      if (!reg_result(sh(e)) && name(sh(e))!=tophd && shape_size(sh(e)) >64)
      {
	 /* Must be a structure or union result, pass address in RET0 */
	 instore is;
	 assert(discrim(dest.answhere) == notinreg);
	 /* struct must be in memory */
	 is = insalt(dest.answhere);
	 if (is.adval)
	 {
	    /* generate address of dest */
	    if (IS_FIXREG(is.b.base))
	       ld_ins(i_lo,SIGNED,is.b,RET0);
	    else
 	       set_ins("",is.b,RET0);
	 }
	 else
	    ld_ins(i_lw,SIGNED,is.b,RET0);
	 nsp = guardreg(RET0,nsp);
      }

      if (is_fn_glob(fn))
      {
	 call_ins(cmplt_,TARGET(fn),RP,stub);
      }
      else
      {
	 reg_operand_here(fn,nsp,GR22);
	 call_millicode(MILLI_DYNCALL,RP,stub,1);
      }
      clear_all();  /* forget all register memories */
      if (reg_result(sh(e)))
      {
	 int hda = name(sh(e));
	 ans aa;
	 if (is_floating(hda))
	 {
	    freg frg;
	    frg.fr = R_FR4;
	    frg.dble = (hda != shrealhd);
	    setfregalt(aa, frg);
	    move(aa, dest, sp.fixed, 1);
	    /* move floating point result of application to destination */
	 }
	 else
	 {
	    setregalt(aa, RET0);
	    mka.regmove = RET0;
	    move(aa, dest, sp.fixed, 1);
	    /* move fixed point result of application to destination */
	 }
      }
      else
      if (name(sh(e))!=tophd && (shape_size(sh(e)) <65))
      {
	 /* 64 bit structure or union result returned in RET0 and RET1 */
	 instore is;
	 is = insalt(dest.answhere);
	 if (discrim(dest.answhere) ==inreg && dest.answhere.val.regans==GR0)
	 {
	    /* dest is nowhere, do nothing */
	 }
	 else if (is.adval)
	 {
	    st_ins(i_sw,RET0,is.b);
	    is.b.offset+=4;
	    st_ins(i_sw,RET1,is.b);
	 }
	 else
	 {
	    baseoff b;
	    ld_ins(i_lw,SIGNED,is.b,GR1);
	    b.base=GR1;
	    b.offset=0;
	    st_ins(i_sw,RET0,b);
	    b.offset+=4;
	    st_ins(i_sw,RET1,b);
	 }
      }
      if (call_is_untidy(cees))
      {
	 int ma = (max_args+511) & (~511);
	 ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,(ma>>3),SP,SP);
	 if (Has_tos)
	    reset_tos();
	 if (PIC_code)
	    st_ir_ins(i_stw,cmplt_,GR5,fs_,empty_ltrl,-32,SP);
      }
      else
      if (postlude_has_call(e))
      {
	 exp x = son(cers);
	 postl_chain p;
	 int ma = (max_args+511) & (~511);
	 for (;x!=NULL;)
	 {
	    if (name(x) ==caller_tag)
	    {
	       no(x) += ma;
	    }
	    if (last(x))
	       break;
	    else
	       x = bro(x);
	 }
	 mka.regmove = NOREG;
	 update_plc(old_pls,ma);
	 p.pl = pl;
	 p.outer = old_pls;
	 old_pls = &p;
	 ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,ma>>3,SP,SP);
	IGNORE make_code(pl, sp, nowhere, 0);
	 ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,- (ma>>3),SP,SP);
	 old_pls = p.outer;
	 update_plc(old_pls,-ma);
      }
      else
	IGNORE make_code(pl, sp, nowhere, 0);
      return mka;
  }


  case caller_name_tag:
  {
     return mka;
  }

  case caller_tag:
  {
     e = son(e); goto tailrecurse;
  }


  case make_callee_list_tag:
  {
     bool vc = call_has_vcallees(e);
     do_callee_list(e, sp);
     if (vc)
     {
	 ir_ins(i_ldi,fs_,empty_ltrl,no(e) >>3,GR1);
	 st_ir_ins(i_stw,cmplt_,GR1,fs_,empty_ltrl,64,SP);
     }
     return mka;
  }


  case same_callees_tag:
  {
     bool vc = call_has_vcallees(e);
     restore_callees();
     if (Has_vcallees)
     {
	int startl = new_label();
	int endl = new_label();
	/* Load callee_sz (in bytes), stored in 64(FP), into tmp T4. */
	ld_ir_ins(i_ldw,cmplt_,fs_,empty_ltrl,64,FP,T4);
	comb_ins(c_eq,0,T4,endl);
	if (vc)
	{
	   st_ir_ins(i_stw,cmplt_,T4,fs_,empty_ltrl,64,SP);
	}
	else
	{
	   z_ins(i_nop);
	}
	/*
	 * Copy 72(FP),76(FP),...,68+callee_sz(FP) to 72(SP),76(FP),...,68+callee_sz(SP)
	 */
	ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,72,FP,T3);
	rrr_ins(i_add,c_,T4,T3,T4);
	ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,72,SP,T2);
	outlab("L$$",startl);
	ld_ir_ins(i_ldbs,cmplt_MA,fs_,empty_ltrl,1,T3,GR1);
	comb_ins(c_l,T3,T4,startl);
	st_ir_ins(i_stbs,cmplt_MA,GR1,fs_,empty_ltrl,1,T2);
	outlab("L$$",endl);
     }
     else
     {
	int csz = (callee_sz>>3);
	if (csz)
	{
	   int co = - (callees_offset>>3);
	   imm_to_r(csz,T4);
	   if (vc)
	   {
	      st_ir_ins(i_stw,cmplt_,T4,fs_,empty_ltrl,64,SP);
	   }
	   if (csz<17)
	   {
	       /*
			* 16 or fewer bytes to move - may as well move them word
		    * by word then finish off byte by byte.
		    */
	      int nw = csz& (~3);
	      int o,base,off;
	      if (SIMM14(co))
	      {
		 base = EP;
		 off = co;
	      }
	      else
	      {
		 ir_ins(i_addil,fs_L,empty_ltrl,co,EP);
		 ld_ir_ins(i_ldo,cmplt_,fs_R,empty_ltrl,co,GR1,T3);
		 base = T3;
		 off = 0;
	      }
	      for (o=0;o<nw;o+=4)
	      {
		 ld_ir_ins(i_ldw,cmplt_,fs_,empty_ltrl,off+o,base,GR1);
		 st_ir_ins(i_stw,cmplt_,GR1,fs_,empty_ltrl,72+o,SP);
	      }
	      for (;o<csz;o++)
	      {
		 ld_ir_ins(i_ldb,cmplt_,fs_,empty_ltrl,off+o,base,GR1);
		 st_ir_ins(i_stb,cmplt_,GR1,fs_,empty_ltrl,72+o,SP);
	      }
	   }
	   else
	   {
	      /*  use a loop to move bytes  */
	     int startl = new_label();
	     if (SIMM14(co))
	     {
		ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,co,EP,T3);
	     }
	     else
	     {
		ir_ins(i_addil,fs_L,empty_ltrl,co,EP);
		ld_ir_ins(i_ldo,cmplt_,fs_R,empty_ltrl,co,GR1,T3);
	     }
	     rrr_ins(i_add,c_,T4,T3,T4);
	     ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,72,SP,T2);
	     outlab("L$$",startl);
	     ld_ir_ins(i_ldbs,cmplt_MA,fs_,empty_ltrl,1,T3,GR1);
	     comb_ins(c_l,T3,T4,startl);
	     st_ir_ins(i_stbs,cmplt_MA,GR1,fs_,empty_ltrl,1,T2);
	   }
	}
	else
	if (vc)
	{
	   st_ir_ins(i_stw,cmplt_,0,fs_,empty_ltrl,64,SP);
	}
     }
     return mka;
  }


    case make_dynamic_callee_tag:
    {
       /* vc = call_has_vcallees(e);  it should do!  */
       int lower,upper,szr;
       space nsp;
       int lb,le;
       nsp = sp;
       lower = getreg(nsp.fixed);
       load_reg(son(e),lower,nsp);
       nsp = guardreg(lower,nsp);
       szr = getreg(nsp.fixed);
       load_reg(bro(son(e)),szr,nsp);
       guardreg(szr,nsp);
       szr = reg_operand(bro(son(e)),nsp);
		/*
		 * lower = pointer to the bytes constituting the dynamic callees
		 * szr = number of bytes constituting the dynamic callees
		 */
       upper = getreg(nsp.fixed);
       lb = new_label();
       le = new_label();
       st_ir_ins(i_stw,cmplt_,szr,fs_,empty_ltrl,64,SP);
       cj_ins(c_eq,0,szr,le);
       rrr_ins(i_add,c_,lower,szr,upper);  /*  `upper' is where we stop  */
       ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,18<<2,SP,szr);
       outlab("L$$",lb);
       ld_ir_ins(i_ldbs,cmplt_MA,fs_,empty_ltrl,1,lower,GR1);
       comb_ins(c_l,lower,upper,lb);
       st_ir_ins(i_stbs,cmplt_MA,GR1,fs_,empty_ltrl,1,szr);
       outlab("L$$",le);
       return mka;
    }

  case ident_tag:
  {
     where placew;
     int r = NOREG;
     bool remember = 0;
     exp se = son(e);

     if (props(e) & defer_bit)
     {
 	return make_code(bro(se), sp, dest, exitlab);
     }
     if (se == NULL)
     {
	/* Historical - unused tags are now removed cleanly */
	placew = nowhere;
     }
     else
     if (name(son(e)) == caller_name_tag)
     {
	/* the ident of a caller in a postlude */
	exp ote = find_ote(e,no(son(e)));
       	no(e) = no(ote);
	placew = nowhere;
     }
     else
     {
	ash a;
	int n = no(e);
	a = ashof(sh(se));
	if (props(e) & inreg_bits)
	{
	   /* tag is to be found in a fixed pt reg */
	   if (n == 0)
	   {
 	      /* We need to allocate a fixed t-reg */
	      int s = sp.fixed;
	      if (props(e) & notparreg)
	      {
		 s |= PARAM_TREGS;
	      }
	      if (props(e) &notresreg)
	      {
		 s |= RMASK(RET0);
	      }
	      n = getreg(s);
	      no(e) = n;
	   }
	   else
	   if (n == RET0)
	   {
	      /* use result reg optimisation */
 	      assert(!(props(e) & notparreg));
	      IGNORE needreg(RET0, sp);	/* just as an error check */
	   }
	   else
	   {
	      assert(IS_SREG(n));
	   }
	   setregalt(placew.answhere, n);
	}
	else
	if (props(e) & infreg_bits)
	{
	   /* tag in some float reg */
	   freg frg;
	   if (n == 0)
	   {
	      /*
	       * if it hasn't been already allocated into a s-reg
	       * allocate tag into float-reg ...
	       */
	      int s = sp.flt;
	      if (props(e) & notparreg)
		 s |= PARAM_FLT_TREGS;
	      n = getfreg(s);
	      no(e) = n;
	   }
	   else
	   if (n == R_DEFER_FR4)
	   {
	      n = R_FR4;
	      no(e) = R_FR4;
	   }
	   else
	   {
	      assert(IS_FLT_SREG(n));
	   }
	   frg.fr = n;
	   frg.dble = (a.ashsize==64 ? 1 : 0);
	   setfregalt(placew.answhere, frg);
	}
	else
	if (isparam(e))
	{
 	   instore is;
	   long n = no(se);  /* bit disp of param */
	   if (name(son(e))!= formal_callee_tag)
	   {
	      /* A caller parameter kept on the stack. */
    	      is.adval = 1;
	      is.b.base = GR17;
	      is.b.offset = - ((n+params_offset) >>3);
	      setinsalt(placew.answhere, is);
	      no(e) = n * 2 + GR17;
	      remember = 1;
	      if ((last_param(e) && (!Has_no_vcallers ||
				     (isvis(e) && props(se)!=0))) ||
		   a.ashsize==0)
	      {
 	         /* possible varargs, dump remaining param regs on stack */
		 int i = n >> 5; /* next offset */
		 int off =- (params_offset>>3) - (i<<2);
		 i--;
		 while (i<4)
		 {
		    st_ir_ins(i_stw,cmplt_,ARG0+i,fs_,empty_ltrl,off, Has_vcallees ? FP : EP);
		    strcat(export,i==0 ? ",ARGW0=GR" : i==1 ? ",ARGW1=GR" : i==2 ? ",ARGW2=GR" : ",ARGW3=GR");
		    off-=4;
		    i++;
		 }
	      }
	   }
	   else
	   {
	      /* A callee parameter */
	      instore is;
	      is.b.base = EP;
	      is.b.offset = no(se);
	      no(e) = is.b.offset;
	      is.adval = 1;
	      setinsalt(placew.answhere,is);
	   }
	}
	else
	{
 	   /* A local living on the stack */
	   instore is;
	   is.b = boff(e);
	   is.adval = 1;
#if USE_BITAD
	   if (a.ashalign != 1)
	   {
	      setinsalt(placew.answhere, is);
	      remember = 1;
	   }
	   else
	   {
	      is.b.offset = is.b.offset << 3;
	      setbitadalt(placew.answhere, is);
	   }
#else
	   setinsalt(placew.answhere, is);
	   remember = 1;
#endif
	}
	placew.ashwhere = a;
     }
     if (isparam(e))
     {
	if (name(se)!= formal_callee_tag)
	{
	   int off,sz = shape_size(sh(se));
	   baseoff stkpos;
	   int n = no(se);
	   int pr = props(se); /* (pr == 0) ? (on stack) : (input reg) */
	   stkpos.base = Has_vcallees ? FP : EP;
	   off = - ((n+params_offset) >>3);
	   stkpos.offset = off;
#if 0
	   if (pt(e) ==NULL && diag == DIAG_NONE)
	   {
	      /* parameter never used */
	   }
	   else
#endif
	   if (pr && (props(e) & inanyreg) == 0)
	   {
	      /* param in reg pr, move to stack */
	      if (is_floating(name(sh(se))))
		 stf_ins(sz==64 ? i_fstd : i_fstw,pr,stkpos);
	      else
	      {
		 if (sz==8)
		    st_ins(i_sb,pr,stkpos);
		 else
		 if (sz==16)
		    st_ins(i_sh,pr,stkpos);
		 else
		 if (sz==32)
		    st_ins(i_sw,pr,stkpos);
		 else  /*  sz==64  */
		 {
		    st_ins(i_sw,pr,stkpos);
		    stkpos.offset+=4;
		    st_ins(i_sw,pr-1,stkpos);
		 }
	      }
	      if (name(sh(se))!= cpdhd && name(sh(se))!= nofhd)
		 remember = 0;
	    }
	    else
	    if (pr==0 && (props(e) &inanyreg)!=0)
	    {
	       /* param on stack, move to reg */
	       int d = no(e);
	       if (sz==8)
		  ld_ins(i_lb,1,stkpos,d);
	       else
	       if (sz==16)
		  ld_ins(i_lh,1,stkpos,d);
	       else
	       if (sz==32)
		  ld_ins(i_lw,1,stkpos,d);
	       remember = 1;
	       r = d;
	    }
	    else
	    if (pr && pr!=no(e))
	    {
	       /* param passed in reg=pr, move to different reg=no(e) */
	       int d = no(e);
	       rr_ins(i_copy,pr,d);
	       remember = 1;
	       r = d;
	    }
	 }
	 else
	 {
	    if (props(e) & inanyreg)
	    {
	       /* A callee parameter passed on stack but kept in register */
	       instore is;
	       ans aa;
	       is.b.base = Has_vcallees ? FP : EP;
	       is.b.offset = (no(se) -callees_offset) >>3;
	       is.adval = 0;
	       setinsalt(aa,is);
	       move(aa,placew,sp.fixed,is_signed(sh(se)));
	    }
	 }
      }
      else
      {
	 r = code_here(son(e), sp, placew);
      }

      if (remember && r != NOREG && pt(e)!= NULL && eq_sze(sh(son(e)), sh(pt(e))))
      {
 	 /* Temporarily in a register, track it to optimise future access */
 	 if (isvar(e))
	 {
	    keepcont(pt(e), r);
	 }
	 else
	 {
	    keepreg(pt(e), r);
	 }
      }

      /* and evaluate the body of the declaration */
      mka = make_code(bro(son(e)), guard(placew, sp), dest, exitlab);
      return mka;
  }

  case seq_tag:
  {
     exp t = son(son(e));
     for (;;)
     {
	exp next = (last(t))?(bro(son(e))): bro(t);
	if ( name(next) == goto_tag )	/* gotos end sequences */
	{
 	   make_code(t, sp, nowhere, no(son(pt(next))));
	}
	else
	{
	   code_here(t, sp, nowhere);
	}
	if (last(t))
	{
	   return make_code(bro(son(e)), sp, dest, exitlab);
	}
	t = bro(t);
     }
  }

  case cond_tag:
  {
     exp first = son(e);
     exp alt = bro(son(e));
     exp test;
     exp record;	 /* jump record for alt */
     exp jr = NULL;   /* jump record for end of construction */

     if (discrim(dest.answhere) == insomereg)
     {
	/* must make choice of register to contain answer to cond */
	int *sr = someregalt(dest.answhere);
	if (*sr != -1)
	   error(ERR_SERIOUS, "somereg *2");
	*sr = getreg(sp.fixed);
	setregalt(dest.answhere, *sr);
     }
     if (name(first) ==goto_tag && pt(first) ==alt)
     {
	/* first is goto alt */
	no(son(alt)) = 0;
	return make_code(alt, sp, dest, exitlab);
     }
#if 1
     /*  "take_out_of_line" stuff  */
     if (name(bro(son(alt))) == top_tag && diag == DIAG_NONE)
     {
	int extract = take_out_of_line(first, alt, repeat_level > 0, 1.0);
	if (extract)
	{
	   static ntest real_inverse_ntest[] = {
		0, 4, 3, 2, 1, 6, 5, 0, 0, 0, 0, 0, 0, 0, 0
	   };
	   exp t = son(son(first));
	   exp p, s, z;
	   int test_n;
	   shape sha;
	   outofline * rec;
	   exp tst = (is_tester(t, 0))? t : bro(son(t));
	   record = getexp(f_bottom, NULL, 0, NULL, NULL,0, 0, 0);
	   if (pt(son(alt))!= NULL)
	      ptno(record) = ptno(pt(son(alt)));
	   else
	      ptno(record) = new_label();
	   jr = getexp(f_bottom, NULL, 0, NULL, NULL, 0, 0, 0);
	   ptno(jr) = new_label();
	   sha = sh(son(tst));
	   rec = (outofline*)xmalloc(sizeof(outofline));
	   rec->next = odd_bits;
	   odd_bits = rec;
 	   rec->dest = dest;
	   rec->labno = new_label();	/* label for outofline body */
	   if (last(t))
	      first = bro(son(first));
	   else
	      son(son(first)) = bro(son(son(first)));
	   rec->body = first;
	   rec->sp=sp;
	       rec->jr=jr;
	   pt(son(alt)) = record;
	   test_n = (int)test_number(tst);
	   if (name(sha) < shrealhd || name(sha) > doublehd)
	      test_n = (int)int_inverse_ntest[test_n];
	   else
	      test_n = (int)real_inverse_ntest[test_n];
	   settest_number(tst, test_n);
	   z = getexp(f_bottom, NULL, 0, NULL, NULL, 0, 0, 0);
	   ptno(z) = rec->labno;/* z->ptf.l */
	   s = getexp(sha, NULL, 0, NULL, z, 0, 0, 0);
	   no(s) = rec->labno;
	   p = getexp(sha, NULL, 0, s, NULL, 0, 0, 0);
	   pt(tst) = p;
  	   mka = make_code(t,sp,dest,0);
	   if (name(sh(first))!= bothd)
	   {
	      outlab("L$$",ptno(jr));
	      clear_all();
	   };
	   return mka;
	};
     };
#endif

     if (name(first) == goto_tag && pt(first) == alt)
     {
	/* first is goto alt */
	no(son(alt)) = 0;
	return make_code(alt, sp, dest, exitlab);
     }
     else
     if (name(alt) == labst_tag && name(bro(son(alt))) == top_tag)
     {
	/* alt is empty */
	int endl = (exitlab == 0)? new_label(): exitlab;
	no(son(alt)) = endl;
	make_code(first, sp, dest, endl);
	mka.lab = endl;
	return mka;
     }
     else
     if (name(alt) == labst_tag && name(bro(son(alt))) == goto_tag)
     {
	/* alt is goto */
	exp g = bro(son(alt));
	no(son(alt)) = no(son(pt(g)));
	return make_code(first, sp, dest, exitlab);
     }

     if ( ( test = testlast(first, alt) ) ) /* I mean it */
     {
	/* effectively an empty then part */
	int l = (exitlab != 0)? exitlab : new_label();
	bool rev = !!IsRev(test);
	ptno(test) = -l;  /* make test jump to exitlab - see test_tag: */
	props(test) = notbranch[props(test)];
	if (rev)
	{
	   SetRev(test);
	}
	/* ... with inverse test */
	no(son(alt)) = new_label();
	make_code(first, sp, dest, l);
	make_code(alt, sp, dest, l);
	mka.lab = l;
	return mka;
     }
     else
     {
	int fl, l;
	no(son(alt)) = new_label();
	fl = make_code(first, sp, dest, exitlab).lab;
 	l = (fl != 0)? fl :((exitlab != 0)? exitlab : new_label());
	ub_ins(cmplt_,l);
	clear_all();
	make_code(alt, sp, dest, l);
	mka.lab = l;
	return mka;
     }
  }

  case labst_tag:
  {
     if (no(son(e))!= 0)
     {
	clear_all();
	outlab("L$$",no(son(e)));
     }
     if (is_loaded_lv(e) && No_S)
     {
	/* Could be the target of a long_jump - we must reset SP and FP */
	if (Has_tos)
	   ld_ins(i_lw,1,SP_BOFF,SP);
	else
	   rr_ins(i_copy,EP,SP);
	if (Has_fp)
	   ld_ins(i_lw,1,FP_BOFF,FP);
	if (PIC_code)
	{
	   ld_ir_ins(i_ldw,cmplt_,fs_R,empty_ltrl,-32,SP,GR19);
	   if (!leaf)
	   {
	      rr_ins(i_copy,GR19,GR5);
	   }
	}
     }
     return make_code(bro(son(e)), sp, dest, exitlab);
  }

  case rep_tag:
  {
     makeans mka;
     exp first = son(e);
     exp second = bro(first);
     ++ repeat_level;
     code_here(first,sp,nowhere);
     no(son(second)) = new_label();
     mka = make_code(second, sp, dest, exitlab);
     -- repeat_level;
     return mka;
  }

  case goto_lv_tag:
  {
     int r = reg_operand(son(e),sp);
     extj_reg_ins(i_bv,r);
     z_ins(i_nop);
     clear_all();
     return mka;
  }

  case goto_tag:
  {
     int lab = no(son(pt(e)));
     assert(lab >= 100);
     clear_all();
     /* if (lab != exitlab) */
     {
	ub_ins(cmplt_,lab);
     }
     return mka;
  }

  case absbool_tag:
  {
     error(ERR_SERIOUS, "make_code: absbool_tag not used on HPPA");
     /* NOTREACHED */
  }

  case test_tag:
  {
     exp l = son(e);
     exp r = bro(l);
     int lab = (ptno(e) < 0)? -ptno(e): no(son(pt(e)));
     /* see frig in cond_tag */
     shape shl = sh(l);
     const char *branch;
     int n = (int) test_number(e);	/* could have Rev bit in props */

     if (use_long_double && name(sh(l)) == doublehd)
     {
	quad_op(e, sp, dest);
	cj_ins(c_eq,0,RET0,lab);
	return mka;
     }

     if (is_floating(name(sh(l))))
     {
	/* float test */
	bool dble = ((name(shl) ==shrealhd)? 0 : 1);
	int a1;
	const char *branch = fbranches(n);
	/* choose branch and compare instructions */
	int a2;
	space nsp;
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
	if (dble)
	   cmp_rrf_ins(i_fcmp,f_dbl,branch,(3*a1+1), (3*a2+1));
	else
	   cmp_rrf_ins(i_fcmp,f_sgl,branch,(3*a1), (3*a2));
	z_ins(i_ftest);
	ub_ins(cmplt_,lab);
	return mka;
     }				/* end float test */
     else
     {
			     /* int test */
	int a1;
	int a2;
	bool unsgn;
	if (name(l) == val_tag)
	{
	   /* put literal operand on right */
	   exp temp = l;
 	   l = r;
	   r = temp;
	   if (n <= 2)
 	     n += 2;
	   else
	   if (n <= 4)
 	     n -= 2;
	}

	/* choose branch instruction */
	unsgn = (bool)(!is_signed(shl) && name(shl)!=ptrhd);
	branch = unsgn ? usbranches(n): sbranches(n);

	/*
	 * Generally, anding with an immediate requires 2 instructions.
	 * But, if the and is only being compared to 0, we may be able to get by
	 * with one instruction.
	 */
	if (name(l) == and_tag && name(r) ==val_tag && no(r) ==0 &&
	   (branch == c_eq || branch == c_neq) && !(unsgn && (n==2 || n==3)))
	{
	   exp sonl = son(l);
	   exp bsonl = bro(sonl);
	   if (name(bsonl) == val_tag)
	   {
	      int v = no(bsonl);
	      if (IS_POW2(v))
	      {
		 /* We can branch on bit */

		 /* Which bit, b, to branch on ? */
		 int b=0;
		 while ((v & (1<<b)) == 0)b++;
		 b=31-b;
		 a1 = reg_operand(sonl,sp);
		 if (optim & OPTIM_PEEPHOLE)
		 {
		    bb_in(branch==c_eq ? bit_is_0 : bit_is_1,a1,b,lab);
		 }
		 else
		 {
		    riir_ins(i_extru,branch==c_eq ? c_OD : c_EV,a1,b,1,0);
		    ub_ins(cmplt_N,lab);
		 }
		 return mka;
	      }
	      else
	      {
		 /* v = 00..0011..1100..00 or v = 11..1100..0011..11 ? */
		 int pos = 0, len, next, m;
		 if (v & 1)
		    m = ~v;
		 else
		    m = v;
		 while (pos < 32 && (m & (1<<pos)) ==0)pos++;
		 len = pos;
		 while (len < 32 && (m & (1<<len)))len++;
		 next = len;
		 len -= pos;
		 pos = 31-pos;
		 while (next < 32 && (m & (1<<next)) ==0)next++;
		 if (next == 32)
		 {
		    int d;
		    space nsp;
		    a1 = reg_operand(sonl,sp);
		    nsp = guardreg(a1,sp);
		    d = getreg(nsp.fixed);
		    if (v&1)
		    {
		       /* 2 instructions! Is this worth implementing ? */
		       rr_ins(i_copy,a1,d);
		       iiir_ins(i_depi,c_,0,pos,len,d);
		    }
		    else
		       riir_ins(i_extru,c_,a1,pos,len,d);
		    cij_ins(branch,0,d,lab);
		    return mka;
		 }
	      }
	   }
	}

	a1 = reg_operand(l, sp);
	if (name(r) == val_tag)
	{
	   if (unsgn && (no(r) ==0) && (n==2 || n==3))
	   {
	      if (n==3)
		 ub_ins(cmplt_,lab);
	   }
	   else
	      cij_ins(branch,no(r),a1,lab);
	}
	else
	{
 	   space nsp;
 	   nsp = guardreg(a1, sp);
 	   a2 = reg_operand(r, nsp);
 	   if ((n != 5) && (n !=6))
	   {
	      if ((name(l) == cont_tag) && (name(son(l)) == name_tag) &&
		  isse_opt(son(son(l))))
		 riir_ins(i_extrs,c_, a1,31,shape_size(sh(l)),a1);
	      if ((name(r) == cont_tag) && (name(son(r)) == name_tag) &&
		   isse_opt(son(son(r))))
		 riir_ins(i_extrs,c_, a2,31,shape_size(sh(r)),a2);
	   }
	   cj_ins(branch,a2,a1,lab);
	}
	return mka;
     }
  }

  case ass_tag:
  case assvol_tag:
  {
     exp lhs = son(e);
     exp rhs = bro(lhs);
     where assdest;
     space nsp;
     int contreg = NOREG;
     int hdrhs = name(sh(rhs));
     bool is_float = is_floating(hdrhs);

     if (use_long_double && hdrhs == doublehd)
	is_float = 0;

     /* +++ lose chvar_tag on rhs if no result, remember to invalidate reg */
     /* +++ remove name(e)==ass_tag tests now assbits_tag has gone */

     if (name(e) == assvol_tag)
     {

	/* Assign to volatile location. Disable register-location tracing. */
	/* Disable peep-hole optimisation  */
	asm_comment("make_code: Assign to volatile");
	clear_all();
	setvolatile();
     }

     if (name(e) == ass_tag &&
	 (name(rhs) == apply_tag || is_muldivrem_call(rhs)) &&
	 ((is_float) || valregable(sh(rhs))))
      {
	 where apply_res;
	 /* set up apply_res */
	 if (is_float)
	 {
	    freg frg;
	    frg.fr = R_FR4;
	    frg.dble = (hdrhs!=shrealhd);
	    setfregalt(apply_res.answhere, frg);
	 }
	 else
	 {
	    setregalt(apply_res.answhere, RET0);
	 }
	 apply_res.ashwhere = ashof(sh(rhs));

	 code_here(rhs, sp, apply_res);
	 nsp = guard(apply_res, sp);

	 assdest = locate(lhs, nsp, sh(rhs), 0);
	 move(apply_res.answhere, assdest, nsp.fixed, 1);
	 move(apply_res.answhere, dest, nsp.fixed, 1);

	 clear_dep_reg(lhs);
	 return mka;
      }

      assdest = locate(lhs, sp, sh(rhs), 0);
      nsp = guard(assdest, sp);
#if USE_BITAD
      if (assdest.ashwhere.ashalign == 1)
      {
 	 /* assignment of a bitfield, get address in proper form */
	 instore is;
	 switch (discrim(assdest.answhere))
	 {
	    case inreg:
	    {
	       is.b.base = regalt(assdest.answhere);
	       is.b.offset = 0;
	       is.adval = 1;
	       break;
	    }
	    case notinreg:
	    {
	       is = insalt(assdest.answhere);
	       if (!is.adval)
	       {
		  int r = getreg(nsp.fixed);
		  ld_ins(i_lw,1,is.b,r);
		  nsp = guardreg(r, nsp);
		  is.adval = 1;
		  is.b.base = r;
		  is.b.offset = 0;
	       }
	       else
		  is.b.offset = is.b.offset << 3;
 	       break;
	   }
	   case bitad:
	   {
	      is = bitadalt(assdest.answhere);
	      break;
	   }
	   default:
	     error(ERR_SERIOUS, "wrong assbits");
	}
	setbitadalt(assdest.answhere, is);
     }
     else
#endif
     if (name(e) == ass_tag &&
	  discrim(assdest.answhere) == notinreg &&
	  assdest.ashwhere.ashsize == assdest.ashwhere.ashalign)
     {
	instore is;
	is = insalt(assdest.answhere);
	if (!is.adval)
	{
	/*
	 * This is an indirect assignment, so make it direct by
	 * loading pointer into reg  (and remember it)
	 */
	   int r = getreg(nsp.fixed);
	   ld_ins(i_lw,1,is.b,r);
	   nsp = guardreg(r, nsp);
	   is.adval = 1;
	   is.b.base = r;
	   is.b.offset = 0;
	   setinsalt(assdest.answhere, is);
	   keepexp(lhs, assdest.answhere);
	}
     }
#if 1
     if (name(e) == ass_tag && is_float && discrim(assdest.answhere) == notinreg)
     {
	/*
	 * Ensure floating point values assigned using floating point regs so
	 * floating point reg tracking works better. move() uses fixed regs
	 * for mem to mem, so must pre-load to floating point reg.
	 */
	int f = freg_operand(rhs, nsp, getfreg(nsp.flt));
	freg frg;
	ans aa;
	frg.fr = f;
	frg.dble = (hdrhs!=shrealhd);
	setfregalt(aa, frg);
	nsp = guardfreg(f, nsp);
	move(aa, assdest, nsp.fixed, 1);
	move(aa, dest, nsp.fixed, 1);
	clear_dep_reg(lhs);
	/* +++ frg in mka */
	return mka;
     }
#endif
     /* evaluate source into assignment destination .... */
     contreg = code_here(rhs, nsp, assdest);
     /* ... and move it into dest - could use assignment as value */
     switch (discrim(assdest.answhere))
     {
	case inreg:
	{
	   int a = regalt(assdest.answhere);
	   keepreg(rhs, a);
	   /* remember that source has been evaluated into a */
	   clear_dep_reg(lhs);
	   /* forget register dependencies on destination */
	   move(assdest.answhere, dest, nsp.fixed, 1);
	   break;
	}
	case infreg:
	{
	   freg frg;
	   int r;
 	   frg = fregalt(assdest.answhere);
	   r = frg.fr + 32;
	   if (frg.dble)
	      r = -r;
	   keepreg(rhs, r);
	   /* remember that source has been evaluated into a */
	   clear_dep_reg(lhs);
	   /* forget register dependencies on destination */
	   move(assdest.answhere, dest, nsp.fixed, 1);
	   break;
	}
	case notinreg:
#if USE_BITAD
	case bitad:
#endif
	{
	   if (contreg != NOREG && name(e) == ass_tag)
	   {
	      ans aa;
	      space nnsp;
	      if (contreg > 0 && contreg < 31)
	      {
		 setregalt(aa, contreg);
		 nnsp = guardreg(contreg, sp);
	      }
	      else
	      {
		 freg frg;
		 frg.fr = ABS_OF(contreg) - 32;
		 frg.dble = (contreg < 0);
		 nnsp = nsp;
		 setfregalt(aa, frg);
	      }
	     IGNORE move(aa, dest, nnsp.fixed, 1);
	      /* forget register dependencies on destination */
	      clear_dep_reg(lhs);
	      /* remember that dest contains source, provided that it is not
	      * dependent on it */
	      if (name(lhs) ==name_tag)
	      {
		 exp dc = son(lhs);
		 if (son(dc)!=NULL)
		    dc = son(dc);
		 if (shape_size(sh(dc)) ==shape_size(sh(rhs)))
		    keepcont(lhs,contreg);
	      }
	      else
	      if (!dependson(lhs,0,lhs))
		 keepcont(lhs,contreg);
	      return mka;
	   }
	   clear_dep_reg(lhs);
	   /* forget register dependencies on destination */
	   move(assdest.answhere, dest, nsp.fixed, 1);
	   break;
	}
	case insomereg:
	{
	   clear_dep_reg(lhs);
	   /* forget register dependencies on destination */
	   move(assdest.answhere, dest, guard(assdest, sp).fixed, 1);
	}
	default:;

     }				/* end sw on answhere */
     if (name(e) == assvol_tag)
	setnovolatile();
     return mka;
  }

  case compound_tag:
  {
     exp t = son(e);
     space nsp;
     instore str;
     int r;

      /* Initialse bitfield by constructing an appropriate constant. */
     /* Other compounds are initialised from register values below */
     if (has_bitfield(e))
     {
	instore isa;
	ans aa;
	labexp next;

	/* word-align bitfields for ease of access */
	if (dest.ashwhere.ashalign < 32)
	    dest.ashwhere.ashalign =32;

	/* generate constant value... */
	fix_nonbitfield(e);	/* Ensure all offsets are BIT-offsets. */
	next = (labexp)xmalloc(sizeof(struct labexp_t));
	next->e = e;
	next->lab = next_data_lab();
	next->next = (labexp)0;
	current->next = next;
	current = next;
	isa.adval = 0;
	isa.b.offset = 0;
	isa.b.base = next->lab;
	/* ... and place it in dest */
	setinsalt(aa, isa);
	mka.regmove = move(aa, dest, sp.fixed, 1);
	return mka;
     }

     nsp = sp;
     switch (discrim(dest.answhere))
     {
	case notinreg:
	{
	   str = insalt(dest.answhere);	/* it should be !! */
	   if (!str.adval)
	   {
	      int r = getreg(sp.fixed);
	      nsp = guardreg(r, sp);
	      ld_ins(i_lw,1,str.b,r);
	      str.adval = 1;
	      str.b.base = r;
	      str.b.offset = 0;
	   }
	   for (;;)
	   {
	      where newdest;
	      instore newis;
	      newis = str;
	      newis.b.offset += no(t);
 	      assert(name(t) == val_tag && al2(sh(t)) >= 8); /* offset in bits */
	      setinsalt(newdest.answhere, newis);
	      newdest.ashwhere = ashof(sh(bro(t)));
	      assert(ashof(bro(t)).ashalign != 1); /* stray bitfield */
	      code_here(bro(t), nsp, newdest);
	      if (last(bro(t)))
		 return mka;
	      t = bro(bro(t));
	   }
	}
	case insomereg:
	{
	   int *sr = someregalt(dest.answhere);
  	   if (*sr != -1)
	      error(ERR_INTERNAL, "Somereg *2");
 	   *sr = getreg(sp.fixed);
	   setregalt(dest.answhere, *sr);
	   /* ,... */
       }
       case inreg:
       {
	  code_here(bro(t), sp, dest);
	  r = regalt(dest.answhere);
	  assert(name(t) == val_tag);
	  if (no(t)!= 0)
	     rrir_ins(i_shd,c_,r,0,32- (((al2(sh(t)) >= 8)?(no(t) << 3): no(t))),r);
	  nsp = guardreg(r, sp);
	  while (!last(bro(t)))
	  {
	     int z;
 	     t = bro(bro(t));
	     assert(name(t) == val_tag);
	     z = reg_operand(bro(t), nsp);
	     if (no(t)!= 0)
		rrir_ins(i_shd,c_,z,0,32- (((al2(sh(t)) >= 8)?(no(t) << 3): no(t))),z);
	     rrr_ins(i_or,c_,r,z,r);
	  }
	  return mka;
       }
       case insomefreg:
       {
	  somefreg sfr;
	  freg fr;
   	  sfr = somefregalt(dest.answhere);
	  if (*sfr.fr != -1)
	     error(ERR_INTERNAL, "Somefreg *2");
	  *sfr.fr = getfreg(sp.flt);
	  fr.fr = *sfr.fr;
	  fr.dble = sfr.dble;
	  setfregalt(dest.answhere, fr);
       }
       case infreg:
       {
	  code_here(bro(t), sp, dest);
	  if (!last(bro(t)) || name(t)!=val_tag || no(t)!=0)
	     error(ERR_INTERNAL, "No Tuples in freg");
	  return mka;
       }
       default:;
    }

  }

  case nof_tag:
  case concatnof_tag:
  {
     exp t = son(e);
     space nsp;
     instore str;
     int r, disp = 0;
#if 1
     if (t==NULL)
	return mka;
#endif
     nsp = sp;
     switch (discrim(dest.answhere))
     {
	case notinreg:
	{
	   str = insalt(dest.answhere);	/* it should be !! */
	   if (!str.adval)
	   {
	      int r = getreg(sp.fixed);
	      nsp = guardreg(r, sp);
 	      ld_ins(i_lw,1,str.b,r);
	      str.adval = 1;
	      str.b.base = r;
	      str.b.offset = 0;
	   }
	   for (;;)
	   {
	      where newdest;
	      instore newis;
 	      newis = str;
	      newis.b.offset += disp;
	      setinsalt(newdest.answhere, newis);
	      newdest.ashwhere = ashof(sh(t));
	      code_here(t, nsp, newdest);
	      if (last(t))
 	         return mka;
	      disp += (rounder(shape_size(sh(t)), shape_align(sh(bro(t)))) >> 3);
	      t = bro(t);
	   }
	}
	case insomereg:
	{
	   int *sr = someregalt(dest.answhere);
 	   if (*sr != -1)
 	      error(ERR_INTERNAL, "Somereg *2");
	   *sr = getreg(sp.fixed);
	   setregalt(dest.answhere, *sr);
	   /* ,... */
	}
	case inreg:
	{
	   code_here(t, sp, dest);
	   r = regalt(dest.answhere);
	   nsp = guardreg(r, sp);
	   while (!last(t))
	   {
	     int z;
 	     disp += rounder(shape_size(sh(t)), shape_align(sh(bro(t))));
	     t = bro(t);
	     z = reg_operand(t, nsp);
	     rrir_ins(i_shd,c_,z,0,32-disp,z);
	     rrr_ins(i_or,c_,r,z,r);
	  }
	  return mka;
       }
       default:
	 error(ERR_INTERNAL, "No Tuples in freg");
    }
  }

  case ncopies_tag:
  {
     exp t = son(e);
     space nsp;
     instore str;
     int i, r, disp = 0;

     nsp = sp;
     switch (discrim(dest.answhere))
     {
	case notinreg:
	{
	   str = insalt(dest.answhere);	/* it should be !! */
	   if (!str.adval)
	   {
	      int r = getreg(sp.fixed);
 	      nsp = guardreg(r, sp);
	      ld_ins(i_lw,1,str.b,r);
	      str.adval = 1;
	      str.b.base = r;
	      str.b.offset = 0;
	   }
	   for (i = 1; i <= no(e); i++)
	   {
	      where newdest;
	      instore newis;
	      newis = str;
	      newis.b.offset += disp;
	      setinsalt(newdest.answhere, newis);
	      newdest.ashwhere = ashof(sh(t));
	      code_here(t, nsp, newdest);
	      disp += (rounder(shape_size(sh(t)), shape_align(sh(t))) >> 3);
	   }
	   return mka;
	}
	case insomereg:
	{
	   int *sr = someregalt(dest.answhere);
 	   if (*sr != -1)
 	      error(ERR_INTERNAL, "Somereg *2");
	   *sr = getreg(sp.fixed);
	   setregalt(dest.answhere, *sr);
	   /* ,... */
	}
	case inreg:
	{
	   code_here(t, sp, dest);
	   r = regalt(dest.answhere);
	   nsp = guardreg(r, sp);
	   for (i = 1; i <= no(e); i++)
	   {
	      int z;
 	      disp += rounder(shape_size(sh(t)), shape_align(sh(t)));
	      z = reg_operand(t, nsp);
	      rrir_ins(i_shd,c_,z,0,32-disp,z);
	      rrr_ins(i_or,c_,r,z,r);
	   }
	   return mka;
	}
	default:
	  error(ERR_INTERNAL, "No Tuples in freg");
     }
   }

    case diagnose_tag:
    {
       /* Diagnostics */
       diag_info *d = dno(e);
       stab_begin(d,0,e);
       mka = make_code(son(e),sp,dest,exitlab);
       stab_end(d,e);
       return mka;
    }

  case solve_tag:
  {
     exp m = bro(son(e));
     int l = exitlab;

     if (discrim(dest.answhere) == insomereg)
     {
	int *sr = someregalt(dest.answhere);
	if (*sr != -1)
 	   error(ERR_SERIOUS, "somereg *2");
	*sr = getreg(sp.fixed);
	setregalt(dest.answhere, *sr);
     }

     /* set up all the labels in the component labst_tags */
     for (;;)
     {
	no(son(m)) = new_label();
	if (last(m))
	  break;
	m = bro(m);
     }
     m = son(e);

     /* evaluate all the component statements */
     for (;;)
     {
	int fl = make_code(m, sp, dest, l).lab;

	clear_all();
	if (fl != 0)
	   l = fl;

	if (!last(m))
	{
 	   /* jump to end of solve */
	   if (l == 0)
	      l = new_label();
	   if (name(sh(m))!= bothd)
	   {
	      ub_ins(cmplt_,l);
	   }
	}
	if (last(m))
	{
	   mka.lab = l;
	   return mka;
	};
	m = bro(m);
     }
  }

  case case_tag:
  {
     int r = reg_operand(son(e),sp);
     /* evaluate controlling integer into register r */
     exp z = bro(son(e));
     exp zt = z;
     long n;
     long l;
     long u = 0x80000000;

     unsigned long approx_range;  /* max(u-l, 0x7fffffff) avoiding overflow */
     bool use_jump_vector;
     l = no(zt);
     for (n = 1;;n++)
     {
	/* calculate crude criterion for using jump vector or branches */
	if (u + 1 != no(zt) && son(zt)!= NULL)
	   n++;
	if (last(zt))
	{
	   u = (son(zt)!= NULL)? no(son(zt)): no(zt);
	   break;
	}
	if (son(zt)!= NULL)
	{
	   u = no(son(zt));
	}
	else
	{
	   if (u + 1 == no(zt))
	      u += 1;
	}
	zt = bro(zt);
     }
	/*
	 * Now l is lowest controlling value, u is highest, and n is number of
	 * cases
	 */
     if (u - l < 0)
	approx_range = 0x7fffffff;  /* u-l overflowed into -ve, use huge */
     else
	approx_range = u - l;
     if (approx_range < 16)
     {
	/* small jump vector needed, decide on instuctions executed only */

	unsigned jump_vector_cnt = ((l >= 0 && l <= 4)? 8 : 9);
	unsigned cmp_jmp_step_cnt = 2 + (!SIMM13(l)) + (!SIMM13(u));

	/* cmp & jmp, delay slot filled plus possibly load of large consts */
	/* +++ assume default used as often as case, is this good? */
	unsigned default_weight = 1;	/* likelyhood of default against
					 * single case */
	unsigned total_case_test_chain_cnt =
	((((n + 1) * cmp_jmp_step_cnt) * n) / 2) + 1	/* unused delay slot on
	    last case */ ;
	unsigned default_test_chain_cnt =
	(n * cmp_jmp_step_cnt) + 1 /* unused delay slot */ ;
	unsigned average_test_chain_cnt =
	(total_case_test_chain_cnt + (default_test_chain_cnt * default_weight)) / (n + default_weight);


	use_jump_vector = jump_vector_cnt <= average_test_chain_cnt;
	asm_comment("case_tag small jump vector: jump_vector_cnt=%d average_test_chain_cnt=%d",
		     jump_vector_cnt, average_test_chain_cnt);
     }
     else
     {
	/*
	 * space-time product criterion for jump vector instead of tests and
	 * branches
	 */
	unsigned long range_factor = approx_range + 9;
	unsigned long n_factor = ((unsigned long)n * n) / 2;

	use_jump_vector = range_factor <= n_factor;

     }

     assert(l <= u);
     assert(n >= 0);

     if (use_jump_vector)
     {
	/* use jump vector, 8/9 insts overhead */
	int endlab = new_label();
	int veclab = 0;
	char zeroveclab[16];
	int mr = getreg(sp.fixed);
	zeroveclab[0] = 0;
	if (!PIC_code)
	{
	   veclab = next_data_lab();
	   sprintf(zeroveclab, "LD$%ld",(long)veclab);
	}
	if (l >= 0 && l <= 4)
	{
	   /* between 0 and 4 dummy table entries used to avoid subtract */
	   cij_ins(c_lu,u,r,endlab);
 	   n = 0;
	   if (PIC_code)
	   {
	      bl_in(cmplt_,".+8",GR1);
	      iiir_ins(i_depi,c_,0,31,2,GR1);
	      ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,16,GR1,GR1);
	   }
	   else
	   {
	      ir_ins(i_ldil,fs_L,zeroveclab,0,GR1);
	      ld_ir_ins(i_ldo,cmplt_,fs_R,zeroveclab,0,GR1,GR1);
	   }
	   ld_rr_ins(i_ldwx,cmplt_S,r,GR1,GR1);
	}
	else
	{
	   /* subtract to index jump vector */
	   if SIMM11(-l)
	      irr_ins(i_addi,c_,fs_,-l,r,mr);
	   else
	   {
	      ir_ins(i_addil,fs_L,empty_ltrl,-l,r);
	      ld_ir_ins(i_ldo,cmplt_,fs_R,empty_ltrl,-l,GR1,mr);
	   }
	   cij_ins(c_lu,u-l,mr,endlab);
	   n = l;
	   if (PIC_code)
	   {
	      bl_in(cmplt_,".+8",GR1);
	      iiir_ins(i_depi,c_,0,31,2,GR1);
	      ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,16,GR1,GR1);
	   }
	   else
	   {
	      ir_ins(i_ldil,fs_L,zeroveclab,0,GR1);
	      ld_ir_ins(i_ldo,cmplt_,fs_R,zeroveclab,0,GR1,GR1);
	   }
	   ld_rr_ins(i_ldwx,cmplt_S,mr,GR1,GR1);
	}

	extj_reg_ins(i_bv,GR1 /* not a call */ );
	z_ins(i_nop);

	/* build the jump vector */

	if (!PIC_code)
	   outlab("LD$",veclab);
   	for (;;)
	{
	   char labl[48];
	   for (; no(z) > n; n++)
	   {
	      sprintf(labl,"L$$%d",endlab);
	      out_directive(".WORD",labl);
	   }
	   u = (son(z) == NULL)? n : no(son(z));
	   for (; n <= u; n++)
	   {
	      sprintf(labl,"L$$%d",no(son(pt(z))));
	      out_directive(".WORD",labl);
	   }
	   if (last(z))
	      break;
	   z = bro(z);
	}
	clear_all();
	outlab("L$$",endlab);
	return mka;
     }
     else
     {
		/*
		 * Use branches - tests are already ordered
		 */
	int over = 0;
	mm lims;
	lims = maxmin(sh(son(e)));
	if (is_signed(sh(son(e))))
	{
	   long u,l;
	   for (;;)
	   {
	      int lab = no(son(pt(z)));
	      l = no(z);
	      if (son(z) == NULL)
	      {
 	         /* only single test required */
		 cij_ins(c_eq,l,r,lab);
		 if (l == lims.maxi)
		    lims.maxi -= 1;
		 else
		 if (l == lims.mini)
		    lims.mini += 1;
	      }
	      else
	      if (u = no(son(z)), l > lims.mini)
	      {
		 if (u >= lims.maxi)
		 {
		    cij_ins(c_leq,l,r,lab);
		    lims.maxi = l - 1;
		 }
		 else
		 {
		    if (over == 0)
		       over = new_label();
		    cij_ins(c_g,l,r,over);
		    cij_ins(c_geq,u,r,lab);
		    lims.mini = u + 1;
		 }
	      }
	      else
	      if (u < lims.maxi)
	      {
		 cij_ins(c_geq,u,r,lab);
		 lims.mini = u + 1;
	      }
	      else
	      {
		 ub_ins(cmplt_,lab);
	      }
	      if (last(z))
	      {
		 if (over != 0)
		 {
		    clear_all();
		    outlab("L$$",over);
		 }
		 return mka;
	      }
	      z = bro(z);
	   }
	}
	else
	{
	   unsigned long maxi,mini,u,l;
	   maxi = (unsigned)lims.maxi;
	   mini = (unsigned)lims.mini;
	   for (;;)
	   {
	      int lab = no(son(pt(z)));
	      l = no(z);
	      if (son(z) == NULL)
	      {
		 /* only single test required */
		 cij_ins(c_eq,l,r,lab);
		 if (l == maxi)
		   maxi -= 1;
		 else
		 if (l == mini)
		    mini += 1;
	      }
	      else
	      if (u = no(son(z)), l > mini)
	      {
		 if (u >= maxi)
		 {
		    cij_ins(c_lequ,l,r,lab);
		    maxi = l - 1;
		 }
		 else
		 {
		    if (over == 0)
		    {
		       over = new_label();
		    }
		    cij_ins(c_gu,l,r,over);
		    cij_ins(c_gequ,u,r,lab);
		    mini = u + 1;
		 }
	      }
	      else
	      if (u < maxi)
	      {
		 cij_ins(c_gequ,u,r,lab);
		 mini = u + 1;
	      }
	      else
	      {
		 ub_ins(cmplt_,lab);
 	      }
	      if (last(z))
	      {
		 if (over != 0)
		 {
		    clear_all();
		    outlab("L$$",over);
		 }
		 return mka;
	      }
 	      z = bro(z);
	   }
	}
     }
  }

  case offset_add_tag:
  case plus_tag:
  {
     if (optop(e))
     {
	mka.regmove = comm_op(e, sp, dest, i_add);
     }
     else
     {
	/* error_jump to "trap" on overflow */
	int trap = trap_label(e);
	int l,r,d;
	space nsp;
	l = reg_operand(son(e),sp);
	nsp = guardreg(l,sp);
	r = reg_operand(bro(son(e)),guardreg(l,sp));
	nsp = guardreg(r,sp);
	if (discrim(dest.answhere)!=inreg || (d=regalt((dest).answhere)) ==0)
	   d = getreg(nsp.fixed);
	if (shape_size(sh(e)) ==32)
	{
	   rrr_ins(i_add,is_signed(sh(e))? c_NSV : c_NUV,l,r,d);
	   ub_ins(cmplt_N,trap);
	}
	else
	{
	   rrr_ins(i_add,c_,l,r,d);
	   test_if_outside_of_var(name(sh(e)),d,trap);
	}
	if (discrim(dest.answhere)!=inreg)
	{
	   ans aa;
	   setregalt(aa,d);
	   move(aa,dest,sp.fixed,1);
	}
	mka.regmove=d;
     }
     return mka;
  }

  case offset_pad_tag:
  {
     int r,o;
     ans aa;
     space nsp;
     if ((al2(sh(son(e))) < al2(sh(e))) || (al1_of(sh(e)) ->al.al_val.al_frame & 4)!=0)
     {
	int al = (al2(sh(son(e))) ==1)? al2(sh(e)):(al2(sh(e)) /8);
	r = GETREG(dest,sp);
	o = reg_operand(son(e),sp);
	if ((al1_of(sh(e)) ->al.al_val.al_frame & 4) ==0)
	{
	   irr_ins(i_addi,c_,fs_,al-1,o,r);
	   logical_op(i_and,-al,r,r);
	}
	else
	   logical_op(i_and,-al,o,r);
	if (al2(sh(son(e))) ==1)
	{
	   /* Operand is bit-offset, byte-offset required. */
	   riir_ins(i_extrs,c_,r,28,29,r);
	}
     }
     else
     {
	if (al2(sh(e))!=1 || al2(sh(son(e))) ==1)
	{
	   /* Already aligned correctly, whether as bit or byte-offset. */
	   e = son(e);
	   goto tailrecurse;
	}
	r = GETREG(dest,sp);
	o = reg_operand(son(e),sp);
	rrr_ins(i_sh3add,c_,o,0,r);
     }
     setregalt(aa,r);
     nsp = guardreg(r,sp);
     mka.regmove = move(aa,dest,nsp.fixed,0);
     return mka;
  }

  case locptr_tag:
  {
     int ansr = GETREG(dest,sp);
     int pr = reg_operand(son(e),sp);
     space nsp;
     ans aa;
     baseoff b;
     b.base = pr; b.offset = FP_BOFF.offset;
     ld_ins(i_lw,0,b,ansr);
     setregalt(aa,ansr);
     nsp = guardreg(ansr,sp);
     mka.regmove = move(aa,dest,nsp.fixed,0);
     return mka;
  }

  case chvar_tag:
  {
      /*
       * Change integer variety.
       */
      exp arg = son(e); 		/* source of chvar, adjusted below */
      int size_e = shape_size(sh(e));  /* shape of result */
      int to = (int) name(sh(e));     /* to hd */
      int from;			     /* from hd */
      int sreg,dreg;
      bool inmem_dest;
      space nsp;
      /*
       * For a series of chvar_tags, do large to small in one go.
       */
      while (name(arg) == chvar_tag && shape_size(sh(arg)) >= size_e)
      {
  	 arg = son(arg);
      }
      from = (int)name(sh(arg));
#if 1
      if (from == bitfhd)
      {
	 switch (shape_size(sh(arg)))
	 {
	     case 8:
		sh(arg) = is_signed(sh(arg))? scharsh : ucharsh;
		from = name(sh(arg));
		break;
	     case 16:
		sh(arg) = is_signed(sh(arg))? swordsh : uwordsh;
		from = name(sh(arg));
		break;
	     case 32:
		sh(arg) = is_signed(sh(arg))? slongsh : ulongsh;
		from = name(sh(arg));
		break;
	 }
      }

      if (to == bitfhd)
      {
	 switch (shape_size(sh(e)))
	 {
	     case 8:
		sh(e) = is_signed(sh(e))? scharsh : ucharsh;
		to = name(sh(e));
		break;
	     case 16:
		sh(e) = is_signed(sh(e))? swordsh : uwordsh;
		to = name(sh(e));
		break;
	     case 32:
		sh(e) = is_signed(sh(e))? slongsh : ulongsh;
		to = name(sh(e));
		break;
	  }
      }
#endif
      /*
       * Small to large conversions.
       */
      if (from == to || (to == uwordhd && from == ucharhd) ||
	  (to == ulonghd && (from == ucharhd || from == uwordhd)) ||
	  (to == swordhd && (from == scharhd || from == ucharhd)) ||
	  (to == slonghd && from != ulonghd))
      {
	 ans aa;
	 if (discrim(dest.answhere) ==inreg)
	 {
	    sreg = regalt(dest.answhere);
	    reg_operand_here(arg, sp, sreg);
	 }
	 else
	 {
	    sreg = reg_operand(arg, sp);
	 }
	 setregalt(aa,sreg);
	 mka.regmove = move(aa, dest, sp.fixed, is_signed(sh(e)));
	 return mka;
      }

      sreg = reg_operand(arg,sp);
      nsp = guardreg(sreg,sp);

      if (!optop(e))
      {
	 bool signf = is_signed(sh(arg));
	 bool signt = is_signed(sh(e));
	 int trap = trap_label(e);
	 if (signf)
	 {
	    if (signt)
	    {
	       if (to == scharhd)
		  riir_ins(i_extrs,c_,sreg,31,8,GR1);
	       else
	       if (to == swordhd)
		  riir_ins(i_extrs,c_,sreg,31,16,GR1);
	       cj_ins(c_neq,sreg,GR1,trap);
	    }
	    else
	    {
	       if (from == scharhd)
	       {
		  if (optim & OPTIM_PEEPHOLE)
		     bb_in(bit_is_1,sreg,24,trap);
		  else
		  {
		     riir_ins(i_extru,c_eq,sreg,24,1,0);
		     ub_ins(cmplt_,trap);
		  }
	       }
	       else
	       if (from == swordhd)
	       {
		  if (to == ucharhd)
		  {
		     riir_ins(i_extru,c_eq,sreg,23,24,0);
		     ub_ins(cmplt_,trap);
		  }
		  else
		  {
		     if (optim & OPTIM_PEEPHOLE)
			bb_in(bit_is_1,sreg,16,trap);
		     else
		     {
			riir_ins(i_extru,c_eq,sreg,16,1,0);
			ub_ins(cmplt_,trap);
		     }
		  }
	       }
	       else
	       {
		  if (to == ucharhd)
		  {
		     riir_ins(i_extru,c_eq,sreg,23,24,0);
		     ub_ins(cmplt_,trap);
		  }
		  else
		  if (to == uwordhd)
		  {
		     riir_ins(i_extru,c_eq,sreg,15,16,0);
		     ub_ins(cmplt_,trap);
		  }
		  else
		  {
		     if (optim & OPTIM_PEEPHOLE)
			bb_in(bit_is_1,sreg,0,trap);
		     else
		     {
			riir_ins(i_extru,c_eq,sreg,0,1,0);
			ub_ins(cmplt_,trap);
		     }
		  }
	       }
	    }
	 }
	 else
	 {
	    if (signt)
	    {
	       if (to == scharhd)
	       {
		  riir_ins(i_extru,c_eq,sreg,24,25,0);
		  ub_ins(cmplt_,trap);
	       }
	       else
	       if (to == swordhd)
	       {
		  riir_ins(i_extru,c_eq,sreg,16,17,0);
		  ub_ins(cmplt_,trap);
	       }
	       else
	       {
		  if (optim & OPTIM_PEEPHOLE)
		     bb_in(bit_is_1,sreg,0,trap);
		  else
		  {
		     riir_ins(i_extru,c_eq,sreg,0,1,0);
		     ub_ins(cmplt_,trap);
		  }
	       }
	    }
	    else
	    {
	       if (to == ucharhd)
		  riir_ins(i_extru,c_,sreg,31,8,GR1);
	       else
		  riir_ins(i_extru,c_,sreg,31,16,GR1);
	       cj_ins(c_neq,sreg,GR1,trap);
	    }
	 }
      }

      switch (discrim(dest.answhere))
      {
	 case inreg:
	 {
	    dreg = regalt(dest.answhere);
	    if (dreg == 0)
	       return mka;		/* dest void */
	    inmem_dest = 0;
	    break;
	 }
	 case insomereg:
	 {
 	    int *dr = someregalt(dest.answhere);
	    dreg = getreg(sp.fixed);
	    *dr = dreg;
	    inmem_dest = 0;
	    break;
	 }
	 default:
	 {
	    dreg = getreg(sp.fixed);
	    inmem_dest = 1;
	    break;
	 }
      }
      if (inmem_dest && size_e <= shape_size(sh(arg)))
      {
 	 /* going to smaller sized memory, store will truncate */
	 ans aa;
	 setregalt(aa, sreg);
	IGNORE move(aa, dest, nsp.fixed, 1);
      }
      else
      {
	 /* from != to */

	 /* Shorten type if needed */
	 if (to==ucharhd)
	 {
	    if (dreg==sreg)
	       riir_ins(i_dep,c_,0,23,24,dreg);
	    else
	       riir_ins(i_zdep,c_,sreg,31,8,dreg);
	 }
	 else
	 if (to==scharhd)
	 {
	    riir_ins(i_extrs,c_,sreg,31,8,dreg);
	 }
	 else
	 if (to==uwordhd)
	 {
	    if (from!=ucharhd)
	    {
	       if (dreg==sreg)
		  riir_ins(i_dep,c_,0,15,16,dreg);
	       else
		  riir_ins(i_zdep,c_,sreg,31,16,dreg);
	    }
	    else
	    if (sreg!=dreg)
	       rr_ins(i_copy,sreg,dreg);
	 }
	 else
	 if (to == swordhd)
	 {
	    if (from!=scharhd && from!=ucharhd)
	    {
	       riir_ins(i_extrs,c_,sreg,31,16,dreg);
	    }
	    else
	    if (sreg!=dreg)
	       rr_ins(i_copy,sreg,dreg);
	 }
	 else
	 {
	    if (sreg!=dreg)
	       rr_ins(i_copy,sreg,dreg);
	 }
	 if (inmem_dest)
	 {
	    ans aa;
	    setregalt(aa, dreg);
	    move(aa, dest, nsp.fixed, 1);
	 }
	 else
	 {
	    mka.regmove = dreg;
	 }
      }
      return mka;
   }

  case minus_tag:
  case offset_subtract_tag:
  {
     if (optop(e))
     {
	mka.regmove = non_comm_op(e, sp, dest, i_sub);
     }
     else
     {
	/* error_jump to "trap" on overflow */
	int trap = trap_label(e);
	int l,r,d;
	space nsp;
	int us = !is_signed(sh(e));
	l = reg_operand(son(e),sp);
	nsp = guardreg(l,sp);
	r = reg_operand(bro(son(e)),guardreg(l,sp));
	nsp = guardreg(r,sp);
	if (discrim(dest.answhere)!=inreg || (d=regalt((dest).answhere)) ==0)
	   d = getreg(nsp.fixed);
	if (us || shape_size(sh(e)) ==32)
	{
	   rrr_ins(i_sub,us ? c_gequ : c_NSV,l,r,d);
	   ub_ins(cmplt_N,trap);
	}
	else
	{
	   rrr_ins(i_sub,c_,l,r,d);
	   test_if_outside_of_var(name(sh(e)),d,trap);
	}
	if (discrim(dest.answhere)!=inreg)
	{
	   ans aa;
	   setregalt(aa,d);
	   move(aa,dest,sp.fixed,1);
	}
	mka.regmove=d;
     }
     return mka;
  }

  case mult_tag:
  case offset_mult_tag:
  {
     bool sgned = is_signed(sh(e));
     if (optop(e))
     {
	asm_comment("mult_tag: name(sh(e)) =%d sgned=%d", name(sh(e)), sgned);
	mka.regmove = do_mul_comm_op(e, sp, dest, sgned);
	return mka;
     }
     else
     {
	int trap = trap_label(e);
	int end = new_label();
	space nsp;
	ans aa;
	baseoff b;
	b = mem_temp(0);
	reg_operand_here(son(e),sp,ARG0);
	nsp = guardreg(ARG0,sp);
	reg_operand_here(bro(son(e)),nsp,ARG1);
	if (sgned)
	{
	   irr_ins(i_comiclr,c_neq,fs_,1,ARG0,RET0);
	   rr_ins(i_copy,ARG1,RET0);
	   cij_ins(c_gu,2,ARG0,end);
	   irr_ins(i_comiclr,c_neq,fs_,1,ARG1,RET0);
	   rr_ins(i_copy,ARG0,RET0);
	   cij_ins(c_gu,2,ARG1,end);
	   iiir_ins(i_zdepi,c_,-1,0,1,GR1);
	   cj_ins(c_eq,ARG0,GR1,trap);
	   cj_ins(c_eq,ARG1,GR1,trap);
	   ld_ins(i_lo,1,b,GR1);
	   b.base = GR1;
	   b.offset = 4;
	   rrr_ins(i_xor,c_,ARG0,ARG1,ARG2);
	   rrr_ins(i_comclr,c_geq,ARG0,0,0);
	   rrr_ins(i_sub,c_,0,ARG0,ARG0);
	   rrr_ins(i_comclr,c_geq,ARG1,0,0);
	   rrr_ins(i_sub,c_,0,ARG1,ARG1);
	   st_ins(i_sw,ARG1,b);
	   b.offset = 0;
	   st_ins(i_sw,ARG0,b);
	   ldf_ins(i_fldd,b,13);
	   rrrf_ins(i_xmpyu,f_,12,14,13);
	   cmp_rrf_ins(i_fcmp,f_sgl,c_eq,12,0);
	   z_ins(i_ftest);
	   ub_ins(cmplt_N,trap);
	   stf_ins(i_fstw,14,b);
	   ld_ins(i_lw,1,b,RET0);
	   rrr_ins(i_comclr,c_geq,ARG2,0,0);
	   rrr_ins(i_sub,c_,0,RET0,RET0);
	   rrr_ins(i_xor,c_geq,RET0,ARG2,0);
	   ub_ins(cmplt_N,trap);
	   outlab("L$$",end);
	}
	else
	{
	   ld_ins(i_lo,1,b,GR1);
	   b.base = GR1;
	   b.offset = 4;
	   st_ins(i_sw,ARG1,b);
	   b.offset = 0;
	   st_ins(i_sw,ARG0,b);
	   ldf_ins(i_fldd,b,13);
	   rrrf_ins(i_xmpyu,f_,12,14,13);
	   cmp_rrf_ins(i_fcmp,f_sgl,c_eq,12,0);
	   z_ins(i_ftest);
	   ub_ins(cmplt_N,trap);
	   stf_ins(i_fstw,14,b);
	   ld_ins(i_lw,1,b,RET0);
	}
	test_if_outside_of_var(name(sh(e)),RET0,trap);
	setregalt(aa,RET0);
	mka.regmove = move(aa, dest, nsp.fixed, 0);
	clear_t_regs();
	return mka;
     }
  }

  case div0_tag:
  case div1_tag:
  case div2_tag:
  case offset_div_by_int_tag:
  case offset_div_tag:
  {
     bool sgned = is_signed(sh(e));
     mka.regmove = do_div_op(e,sp,dest,sgned);
     return mka;
  }

  case rem0_tag:
  case mod_tag: /* i.e. rem1_tag */
  case rem2_tag:
  {
     bool sgned = is_signed(sh(e));
     mka.regmove = do_rem_op(e, sp, dest, sgned);
     return mka;
  }

  case abs_tag:
  {
     int d;
     ans a;
     space nsp;
     int us = !is_signed(sh(e));
     int sz = shape_size(sh(e));
     if (us)
     {
	d = GETREG(dest,sp);
	if (d==0 && !(optop(e)))
	   d = getreg(sp.fixed);
	reg_operand_here(son(e),sp,d);
     }
     else
     if (optop(e))
     {
	int r = reg_operand(son(e),sp);
	d = GETREG(dest,sp);
	if (r==d)
	{
	   rrr_ins(i_sub,c_leq,0,d,GR1);
	   rr_ins(i_copy,GR1,d);
	}
	else
	{
	   rrr_ins(i_sub,c_geq,0,r,d);
	   rr_ins(i_copy,r,d);
	}
	tidyshort(d,sh(e));
     }
     else
     {
	int trap = trap_label(e);
	int lab = new_label();
	d = GETREG(dest,sp);
	if (d==0 && !(optop(e)))
	   d = getreg(sp.fixed);
	reg_operand_here(son(e),sp,d);
	if (sz==32)
	{
	   cj_ins(c_geq,d,0,lab);
	   rrr_ins(i_sub,c_NSV,0,d,d);
	   ub_ins(cmplt_N,trap);
	   outlab("L$$",lab);
	}
	else
	{
	   cj_ins(c_geq,d,0,lab);
	   if (sz==16)
	      iiir_ins(i_zdepi,c_,-1,16,17,GR1);
	   else
	      iiir_ins(i_zdepi,c_,-1,24,25,GR1);
	   cj_ins(c_eq,d,GR1,trap);
	   rrr_ins(i_sub,c_,0,d,d);
	   outlab("L$$",lab);
	}
	tidyshort(d,sh(e));
     }
     setregalt(a,d);
     nsp = guardreg(d,sp);
     mka.regmove = move(a, dest, nsp.fixed, 0);
     return mka;
  }

  case max_tag:
  case min_tag:
  case offset_max_tag:
  {
     int a,d;
     ans aa;
     space nsp;
     ins_p cond;
     exp l = son(e);
     exp r = bro(son(e));
     int nshl = name(sh(l));
     if (discrim(dest.answhere) ==inreg)
	 d = regalt(dest.answhere);
     else
	 d = getreg(sp.fixed);
     nsp = guardreg(d,sp);
     a = reg_operand(l,nsp);
     if (nshl==scharhd || nshl==swordhd || nshl==slonghd || nshl==offsethd)
	cond = (name(e) ==min_tag ? c_geq : c_leq);
     else
	cond = (name(e) ==min_tag ? c_gequ : c_lequ);
     if (name(r) ==val_tag && SIMM11(no(r)))
     {
	int n=no(r);
	rr_ins(i_copy,a,d);
	irr_ins(i_comiclr,cond,fs_,n,a,0);
	ir_ins(i_ldi,fs_,empty_ltrl,n,d);
     }
     else
     {
	int b;
	nsp = guardreg(a,nsp);
	b = reg_operand(r,nsp);
	rr_ins(i_copy,a,d);
	rrr_ins(i_comclr,cond,b,a,0);
	rr_ins(i_copy,b,d);
     }
     setregalt(aa, d);
     mka.regmove = move(aa, dest, sp.fixed, 1);
     return mka;
  }

  case make_lv_tag:
  {
     int d;
     ans a;
     space nsp;
     char label_name[32];
     if (discrim(dest.answhere) ==inreg)
	d = regalt(dest.answhere);
     else
	d = getreg(sp.fixed);
     sprintf(label_name,"L$$%d",no(son(pt(e))));
     if (PIC_code)
     {
	int n = next_PIC_pcrel_lab();
	char s[64];
	sprintf(s,"%s-$PIC_pcrel$%d",label_name,n);
	bl_in(cmplt_,".+8",GR1);
	iiir_ins(i_depi,c_,0,31,2,GR1);
	outlab("$PIC_pcrel$",n);
	ir_ins(i_addil,fs_L,s,0,GR1);
	ld_ir_ins(i_ldo,cmplt_,fs_R,s,0,GR1,d);
     }
     else
     {
	ir_ins(i_ldil,fs_L,label_name,0,d);
	ld_ir_ins(i_ldo,cmplt_,fs_R,label_name,0,d,d);
     }
     setregalt(a, d);
     nsp=guardreg(d,sp);
     move(a, dest, nsp.fixed, 0);
     mka.regmove = d;
     return mka;
  }

  case long_jump_tag:
  {
     int envr = reg_operand(son(e),sp);
     int lab = reg_operand(bro(son(e)), guardreg(envr,sp));
     extj_reg_ins(i_bv,lab);
     rr_ins(i_copy,envr,GR4); /* GR4==EP in the enviroment we're jumping to */
     return mka;
  }

  case offset_negate_tag:
  {
     mka.regmove=monop(e,sp,dest,i_subi);
     return mka;
  }

  case neg_tag:
  {
     if (optop(e))
     {
	mka.regmove = monop(e,sp,dest,i_sub);
     }
     else
     {
	/* error_jump to "trap" on overflow */
	int trap = trap_label(e);
	int d = GETREG(dest,sp);
	int us = !is_signed(sh(e));
	if (d==0)
	   d = getreg(sp.fixed);
	reg_operand_here(son(e),sp,d);
	if (us || shape_size(sh(e)) ==32)
	{
	   rrr_ins(i_sub,us ? c_gequ : c_NSV,0,d,d);
	   ub_ins(cmplt_N,trap);
	}
	else
	{
	   rrr_ins(i_sub,c_,0,d,d);
	   test_if_outside_of_var(name(sh(e)),d,trap);
	}
	if (discrim(dest.answhere)!=inreg)
	{
	   ans aa;
	   setregalt(aa,d);
	   move(aa,dest,sp.fixed,1);
	}
	mka.regmove = d;
     }
     return mka;
  }

  case shl_tag:
  case shr_tag:
    {
      exp s = son(e);
      exp b = bro(s);
      int a;
      int d;
      ans aa;
      space nsp;
      bool sgned = is_signed(sh(e));
      int sz = shape_size(sh(e));
      a = getreg(sp.fixed);

      if (name(b) ==val_tag)
      {
	 int n = no(b) & (sz-1);
	 reg_operand_here(s,sp,a);
	 nsp = guardreg(a, sp);
	 d = GETREG(dest,nsp);
	 if (n==0)
	 {
	    if (a!=d)
	       rr_ins(i_copy,a,d);
	 }
	 else
	 {
	    if (name(e) ==shr_tag)
	       riir_ins(sgned ? i_extrs : i_extru,c_,a,31-n,sz-n,d);
	    else
	       rrir_ins(i_shd,c_,a,0,32-n,d);
	 }
      }
      else
      {
	 int ar;
	 if (name(s) ==val_tag && SIMM5(no(s)) && name(e) ==shl_tag)
	 {
	    int n = no(s);
	    nsp = sp;
	    d = GETREG(dest,nsp);
	    ar = reg_operand(b, nsp);
	    irr_ins(i_subi,c_lu,fs_,31,ar,GR1);
	    r_ins(i_mtsar,GR1);
	    irr_ins(i_comiclr,c_lu,fs_,31,GR1,d);
	    iir_ins(i_zvdepi,c_,n,32,d);
	 }
	 else
	 {
	    reg_operand_here(s,sp,a);
	    nsp = guardreg(a, sp);
	    d = GETREG(dest,nsp);
	    ar = reg_operand(b, nsp);
	    if (name(e) ==shr_tag)
	    {
	       if (sgned)
	       {
		  /* sole variable arithmetic shift right */
		  irr_ins(i_subi,c_,fs_,31,ar,GR1);
		  r_ins(i_mtsar,GR1);
		  rir_ins(i_vextrs,c_,a,sz,d);
	       }
	       else
	       {
		  /* sole variable logical shift right */
		  r_ins(i_mtsar,ar);
		  rrr_ins(i_vshd,c_,0,a,d);
	       }
	    }
	    else
	    {
	       /* sole variable logical shift left */
	       if (a==d)
	       {
		   irr_ins(i_subi,c_gequ,fs_,31,ar,GR1);
		   rr_ins(i_copy,0,d);
		   r_ins(i_mtsar,GR1);
		   rir_ins(i_zvdep,c_,d,32,d);
	       }
	       else
	       {
		  irr_ins(i_subi,c_lu,fs_,31,ar,GR1);
		  r_ins(i_mtsar,GR1);
		  irr_ins(i_comiclr,c_lu,fs_,31,GR1,d);
		  rir_ins(i_zvdep,c_,a,32,d);
	       }
	    }
	 }
       }
       if (!optop(e) && name(e) ==shl_tag && sz<32)
       {
	  int trap = trap_label(e);
	  riir_ins(i_extru,c_eq,d,31-sz,32-sz,0);
	  ub_ins(cmplt_,trap);
       }
       setregalt(aa, d);
       move(aa, dest, nsp.fixed, 1);
       mka.regmove = d;
       return mka;

    }				/* end shl, shr */

  case minptr_tag:
    {
      mka.regmove = non_comm_op(e, sp, dest, i_sub);
      return mka;
    }

  case make_stack_limit_tag:
    {
      mka.regmove = comm_op(e, sp, dest, i_add);
      return mka;
    }

  case fplus_tag:
    {
      mka.regmove = fop(e, sp, dest, i_fadd);
      return mka;
    }

  case fminus_tag:
    {
      mka.regmove = fop(e, sp, dest, i_fsub);
      return mka;
    }

  case fmult_tag:
    {
      mka.regmove = fop(e, sp, dest, i_fmpy);
      return mka;
    }

  case fdiv_tag:
    {
      mka.regmove = fop(e, sp, dest, i_fdiv);
      return mka;
    }

  case fneg_tag:
  {
     int a1,r1;
     int dble = (name(sh(e)) ==shrealhd ? 0 : 1);
     freg frg;
     baseoff b;

     if (use_long_double && name(sh(e)) == doublehd)
     {
	quad_op(e, sp, dest);
	return mka;
     }

     r1 = getfreg(sp.flt);
     a1 = freg_operand(son(e), sp, r1);

     if (!optop(e))
     {
	b = zero_exception_register(sp);
     }
     if (discrim(dest.answhere) ==infreg)
     {
	frg = fregalt(dest.answhere);
	clear_freg(frg.fr<<1);
	if (dble)
	{
	   rrrf_ins(i_fsub,f_dbl,1,3*a1+1,3*(frg.fr) +1);
	   clear_freg((frg.fr<<1) +1);
	}
	else
	   rrrf_ins(i_fsub,f_sgl,0,3*a1,3*(frg.fr));
	if (!optop(e))
	{
	   trap_handler(b,trap_label(e), (OVERFLOW|UNDERFLOW));
	}
     }
     else
     {
	ans aa;
	frg.fr = r1;
	frg.dble = dble;
	setfregalt(aa, frg);
	clear_freg(r1<<1);
	if (dble)
	{
	   rrrf_ins(i_fsub,f_dbl,1,3*a1+1,3*r1+1);
	   clear_freg((r1<<1) +1);
	}
	else
	   rrrf_ins(i_fsub,f_sgl,0,3*a1,3*r1);
	if (!optop(e))
	{
	   trap_handler(b,trap_label(e), (OVERFLOW|UNDERFLOW));
	}
	move(aa,dest,sp.fixed,1);
     }

     mka.regmove = (dble ? - (frg.fr + 32):(frg.fr + 32));
     if (!optop(e))
       checknan(e, mka.regmove);
     return mka;
  }

  case fabs_tag:
    {
      freg frg;
      int a1,r1;
      bool dble;
      baseoff b;

      if (use_long_double && name(sh(e)) == doublehd)
      {
	 quad_op(e, sp, dest);
	 return mka;
      }

      r1 = getfreg(sp.flt);
      a1 = freg_operand(son(e), sp, r1);
      dble = isdbl(sh(e));

      if (!optop(e))
      {
	 b = zero_exception_register(sp);
      }
      switch (discrim(dest.answhere))
      {
      case infreg:
	{
	  frg = fregalt(dest.answhere);
	  clear_freg(frg.fr<<1);
	  if (dble)
	  {
	     rrf_ins(i_fabs,f_dbl,"",3*a1+1,3*(frg.fr) +1);
	     clear_freg((frg.fr<<1) +1);
	  }
	  else
	     rrf_ins(i_fabs,f_sgl,"",3*a1,3*(frg.fr));
	  if (!optop(e))
	  {
	     trap_handler(b,trap_label(e),OVERFLOW|UNDERFLOW);
	  }
	  break;
	}

      default:
	{
	  ans aa;

	  frg.fr = r1;
	  frg.dble = dble;
	  setfregalt(aa, frg);
	  clear_freg(r1<<1);
	  if (dble)
	  {
	     rrf_ins(i_fabs,f_dbl,"",3*a1+1,3*r1+1);
	     clear_freg((r1<<1) +1);
	  }
	  else
	     rrf_ins(i_fabs,f_sgl,"",3*a1,3*r1);
	  if (!optop(e))
	  {
	     trap_handler(b,trap_label(e),OVERFLOW|UNDERFLOW);
	  }
	  move(aa, dest, sp.fixed, 1);
	}
      }

      mka.regmove = (dble ? - (frg.fr + 32):(frg.fr + 32));
      if (!optop(e))
	checknan(e, mka.regmove);
      return mka;
    }

  case float_tag:
    {
      exp in = son(e);
      where w;
      int f = (discrim(dest.answhere) == infreg)
      ? regalt(dest.answhere)	/* cheat */
      : getfreg(sp.flt);
      freg frg;
      ans aa;
      ash ain;
      bool from_sgned ;

      ain = ashof(sh(in));
      from_sgned = is_signed(sh(in));

      /*
       * error_jump would be superfluous.
       */

      if (use_long_double && name(sh(e)) ==doublehd)
      {
	 quad_op(e, sp, dest);
	 return mka;
      }


      frg.fr = f;
      frg.dble = isdbl(sh(e));

      if (ain.ashsize == 32 && !from_sgned)
      {

	/*
	 * Unsigned 32 bit to float. No single HPPA instruction to handle this.
	 * We handle it thus: stw r,mem_temp(0), fldws memtemp(0) fR,
	 * fcpy,sgl 0,f, fcnvxf,dbl,(sgl or dbl) f,(fL or f).
	 */

	int r = reg_operand(in, sp);

	st_ins(i_sw, r, mem_temp(0));
	ldf_ins(i_fldw, mem_temp(0), (3*f) +2);
	rrf_ins(i_fcpy,f_sgl,"",0,3*f+1);
	if (name(sh(e)) ==shrealhd)
	   rrf_ins(i_fcnvxf,f_dbl,f_sgl,3*f+1,3*f);
	else
	   rrf_ins(i_fcnvxf,f_dbl,f_dbl,3*f+1,3*f+1);

      }
      else if (ain.ashsize == 32)
      {
	/* signed 32 bit to float */
	/* pretend the int is a one word float to move to float reg */
	freg fint;

	fint.fr = f;
	fint.dble = 0;
	setfregalt(w.answhere, fint);
	w.ashwhere = ashof(sh(in));
	code_here(in, sp, w);
	if (name(sh(e)) ==shrealhd)
	   rrf_ins(i_fcnvxf,f_sgl,f_sgl,3*f,3*f);
	else
	   rrf_ins(i_fcnvxf,f_sgl,f_dbl,3*f,3*f+1);
      }
      else
      {
	/* bytes and halfs must go through fixpt regs */
	int r = reg_operand(in, sp);

	/* store and load to move to float reg */
	st_ins(i_sw, r, mem_temp(0));
	ldf_ins(i_fldw,mem_temp(0),3*f);
	if (name(sh(e)) ==shrealhd)
	   rrf_ins(i_fcnvxf,f_sgl,f_sgl,3*f,3*f);
	else
	   rrf_ins(i_fcnvxf,f_sgl,f_dbl,3*f,3*f+1);
      }

      setfregalt(aa, frg);
      move(aa, dest, sp.fixed, 1);
      mka.regmove = ((frg.dble)? - (f + 32):(f + 32));
      return mka;
    }

  case chfl_tag:
    {
      int to = name(sh(e));
      int from = name(sh(son(e)));
      bool dto = isdbl(sh(e));
      bool dfrom = isdbl(sh(son(e)));
      freg frg;
      ans aa;
      where w;
      baseoff b;

     if (use_long_double) {
      if (to==doublehd)
      {
	 if (from==doublehd)
	 {
	    /* no change in representation */
	    return make_code(son(e),sp,dest,exitlab);
	 }
	 quad_op(e, sp, dest);
	 return mka;
      }
      else
      if (from==doublehd)
      {
	 quad_op(e, sp, dest);
	 frg.fr = 4;
	 frg.dble = dto;
	 setfregalt(aa,frg);
       	IGNORE move(aa,dest,sp.fixed,1);
	 return mka;
      }
     }

      if (!dto && !dfrom)
      {
	 /* no change in representation */
	 if (!optop(e))
	 {
	    b = zero_exception_register(sp);
	 }
	 return make_code(son(e), sp, dest, exitlab);
      }
      else
      {
	if (discrim(dest.answhere) == infreg)
	{
	  frg = fregalt(dest.answhere);
	}
	else
	{
	  frg.fr = getfreg(sp.flt);
	}
	frg.dble = dfrom;
	setfregalt(aa, frg);
	w.answhere = aa;
	w.ashwhere = ashof(sh(son(e)));
	code_here(son(e), sp, w);
	if (!optop(e))
	{
	   b = zero_exception_register(sp);
	}
	if (dfrom)
	   rrf_ins(i_fcnvff,f_dbl,f_sgl,3*(frg.fr) +1,3*(frg.fr));
	else
	   rrf_ins(i_fcnvff,f_sgl,f_dbl,3*(frg.fr),3*(frg.fr) +1);
	if (!optop(e))
	{
	   trap_handler(b,trap_label(e), (OVERFLOW|UNDERFLOW));
	}
	frg.dble = dto;
	setfregalt(aa, frg);
	move(aa, dest, sp.fixed, 1);
	mka.regmove = ((frg.dble)? - (frg.fr + 32):(frg.fr + 32));
	return mka;
      }
    }

  case and_tag:
    {
#if 0
      exp r = son(e);
      exp l = bro(son(e));
      ans aa;

      /* +++ enable this optimisation for big-endian */
      if (last(l) && name(l) == val_tag && (no(l) == 255 || no(l) == 0xffff)
	  && ((name(r) == name_tag && regofval(r) == R_NO_REG)
	      || (name(r) == cont_tag &&
		 (name(son(r))!= name_tag
		   || regofval(son(r)) > 0
		  )
		 )
	     )
	  && (aa = iskept(r), (discrim(aa) == inreg && regalt(aa) == 0))
	)
      {				/* can use load short instructions */
	where w;
	int dsize = dest.ashwhere.ashsize;
	int asize = (no(l) == 255)? 8 : 16;

	w = locate(r, sp, sh(r), 0);
	if (discrim(w.answhere) == notinreg
	    &&  discrim(dest.answhere) == notinreg && no(l) == 0xffff)
	{
	  instore isw;
	  instore isd;

	  isw = insalt(w.answhere);
	  isd = insalt(dest.answhere);
	  if (!isw.adval && isd.adval && isw.b.base == isd.b.base &&
	      isd.b.offset == isw.b.offset)
	  {
	    if (dsize > 16)
	    {
	      isd.b.offset += 2;/* just clear out top bits */
	      ls_ins(i_sh, 0, isd.b);
	    }
	    return mka;
	  }			/* else drop through to load short case */
	}

	dest.ashwhere.ashsize = dest.ashwhere.ashalign =
	  min(dsize, asize);
	mka.regmove
	  = move(w.answhere, dest, guard(w, sp).fixed, 0 /* unsigned */ );
      }
      else
#endif
      {
	mka.regmove = comm_op(e, sp, dest, i_and);
      }
      return mka;
    }
  case or_tag:
    {
      mka.regmove = comm_op(e, sp, dest, i_or);
      return mka;
    }

  case xor_tag:
    {
      mka.regmove = comm_op(e, sp, dest, i_xor);
      return mka;
    }

  case not_tag:
    {
      mka.regmove = monop(e,sp,dest,i_uaddcm);
      return mka;
    }

    /* +++ mips uses same code as name_tag for cont/contvol_tag should we combine? */
  case cont_tag:
  case contvol_tag:
    {

      if (name(e) == contvol_tag)
      {
	/*
	 * Load contents of volatile location. Diasble register-location
	 * tracing. Disable peep-hole optimisation.
	 */
	asm_comment("make_code: Load volatile");
	clear_all();
	setvolatile();
      }

      /* see if an indexed shift load is appropriate */
      if (do_indexed_loads && name(e) ==cont_tag)
      {
	 exp sone,p,o;
	 bool sgned=is_signed(sh(e));
	 int dr,ashsize;
	 ans aa;
	 ash ashe;
	 int is_float = is_floating(name(sh(e)));
	 ashe=ashof(sh(e));
	 ashsize=ashe.ashsize;
	 if (name(son(e)) ==reff_tag && !no(son(e)))
	    sone = son(son(e));
	 else
	    sone = son(e);
	 if (son(sone)!= (exp)0)
	 {
	    if (name(son(sone)) ==offset_mult_tag)
	    {
	       o=son(sone);   /* an offset ? */
	       p=bro(o);     /* a pointer ? */
	    }
	    else
	    {
	       p=son(sone);   /* a pointer ? */
	       o=bro(p);     /* an offset ? */
	    }
	    if (name(sone) == addptr_tag && name(o) ==offset_mult_tag
				          && name(bro(son(o))) ==val_tag)
	    {
	       long shift;
	       shift=no(bro(son(o)));
	       if (ashe.ashalign==ashsize &&
		   ((ashsize==16 && (shift==2 || shift==0)) ||
		    (ashsize==32 && (shift==4 || shift==0)) ||
		    (ashsize==64 && is_float && (shift==8 || shift==0))))
	       {
		  space nsp;
		  int lhs,rhs;
		  const char *cmplt;
		  if (son(sone) ->commuted)
		  {
		     lhs = reg_operand(son(o),sp);
		     nsp = guardreg(lhs,sp);
		     rhs = reg_operand(p,nsp);
		  }
		  else
		  {
		     rhs = reg_operand(p,sp);
		     nsp = guardreg(rhs,sp);
		     lhs = reg_operand(son(o),nsp);
		  }
		  /* register rhs contains the evaluation of pointer
		     operand of addptr */
		  cmplt = (shift==0 ? cmplt_ : cmplt_S);
		  if (is_float)
  	          {
		     freg dfreg;
  	             if (discrim(dest.answhere) == infreg)
			dfreg = fregalt(dest.answhere);
		     else
			dfreg.fr = getfreg(sp.flt);

		     dfreg.dble = (ashsize==64);

		     if (dfreg.dble)
			ldf_rr_ins(i_flddx,cmplt,lhs,rhs,(3*dfreg.fr) +1);
		     else
			ldf_rr_ins(i_fldwx,cmplt,lhs,rhs,3*dfreg.fr);
	    	     setfregalt(aa, dfreg);
		  }
		  else
		  {
		     dr = (discrim(dest.answhere) == inreg)? dest.answhere.val.regans : getreg(guardreg(lhs,nsp).fixed);
		     if (ashsize==32)
			ld_rr_ins(i_ldwx,cmplt,lhs,rhs,dr);
		     else
		     {
			ld_rr_ins(i_ldhx,cmplt,lhs,rhs,dr);
			if (sgned)
			   riir_ins(i_extrs,c_,dr,31,16,dr);
		     }
		     setregalt(aa, dr);
		  }
		  mka.regmove = move(aa, dest, nsp.fixed, sgned);
		  return mka;
	       }
	    }
	 }
      }



#ifndef NO_REGREG_LOADS
   if (do_indexed_loads) {
      exp addptr_sons = son(son(e));
      /* see if we can use reg(reg) addressing for this load */
      if (name(son(e)) ==addptr_tag)
      {
	 ash ashe;
	 int ashsize;
	 bool is_float = is_floating(name(sh(e)));
	 ashe = ashof(sh(e));
	 ashsize = ashe.ashsize;
	 if (last(bro(addptr_sons)) && ashe.ashalign==ashsize &&
	    (ashsize==8 || ashsize==16 || ashsize==32 || is_float))
	 {
	    int lhsreg;
	    int rhsreg;
	    bool sgned = ((ashsize >= 32) || is_signed(sh(e)));
	    ans aa;
	    if (addptr_sons->commuted)
	    {
	       /* offset register */
	       lhsreg = reg_operand(addptr_sons, sp);
	       /* base register */
	       rhsreg = reg_operand(bro(addptr_sons), guardreg(lhsreg, sp));
	    }
	    else
	    {
	       /* base register */
	       rhsreg = reg_operand(addptr_sons, sp);
	       /* offset register */
	       lhsreg = reg_operand(bro(addptr_sons), guardreg(rhsreg, sp));
	    }
 	    if (is_float)
	    {
	       freg dfreg;
	       if (discrim(dest.answhere) == infreg)
		  dfreg = fregalt(dest.answhere);
	       else
		  dfreg.fr = getfreg(sp.flt);
 	       dfreg.dble = (ashsize==64);
	       if (ashsize==32)
		  ldf_rr_ins(i_fldwx,cmplt_,lhsreg,rhsreg,3*dfreg.fr);
	       else
		  ldf_rr_ins(i_flddx,cmplt_,lhsreg,rhsreg,(3*dfreg.fr) +1);
	       setfregalt(aa, dfreg);
	    }
	    else
	    {
	       int dreg = (discrim(dest.answhere) ==inreg)? dest.answhere.val.regans : getreg(sp.fixed);

	       if (ashsize==8)
	       {
		  ld_rr_ins(i_ldbx,cmplt_,lhsreg,rhsreg,dreg);
		  if (sgned)
		     riir_ins(i_extrs,c_,dreg,31,8,dreg);
	       }
	       else if (ashsize==16)
	       {
		  ld_rr_ins(i_ldhx,cmplt_,lhsreg,rhsreg,dreg);
		  if (sgned)
		     riir_ins(i_extrs,c_,dreg,31,16,dreg);
	       }
	       else
		  ld_rr_ins(i_ldwx,cmplt_,lhsreg,rhsreg,dreg);
	       setregalt(aa, dreg);
	    }
	    mka.regmove = move(aa, dest, sp.fixed, sgned);
	    if (name(e) == contvol_tag)
	    {
	       mka.regmove = NOREG;
	       setnovolatile();
	    }
	    return mka;
	 }
      }
   }
#endif /* NO_REGREG_LOADS */
  }
    /* FALLTHROUGH */

  case name_tag:
  case field_tag:
  case reff_tag:
  case addptr_tag:
  case subptr_tag:
    {

      where w;
      bool sgned;
      int dr = (discrim(dest.answhere) ==inreg)? dest.answhere.val.regans : 0;
      if (name(e) == contvol_tag)
      {
	clear_all();
	setvolatile();
      }
      w = locate(e, sp, sh(e), dr);	/* address of arg */
      sgned = ((w.ashwhere.ashsize >= 32) || ((is_signed(sh(e)))? 1 : 0));
      /* +++ load real into float reg, move uses fixed reg */
      mka.regmove = move(w.answhere, dest,(guard(w, sp)).fixed, sgned);
      if (name(e) == contvol_tag)
      {
	setnovolatile();
	mka.regmove = NOREG;
      }
      return mka;
    }				/* end cont */

  case string_tag:
  case real_tag:
  {
     instore isa;
     ans aa;
     bool sgned = ((ashof(sh(e)).ashsize >= 32) || is_signed(sh(e)));
     labexp next;
      /* place constant in appropriate data segment */
     next  = (labexp)xmalloc(sizeof(struct labexp_t));
     next->e = e;
     next->lab = next_data_lab();
     next->next = (labexp)0;
     current->next = next;
     current = next;
     isa.adval = 0;
     isa.b.offset = 0;
     isa.b.base = next->lab;
     setinsalt(aa, isa);
     mka.regmove = move(aa, dest, sp.fixed, sgned);
     return mka;
  }				/* end eval */

  case val_tag:
    {
      asm_comment("make_code val_tag: no(e) = %d", no(e));
      if (shape_size(sh(e)) >32)
      {
	 flt64 t;
	 int ov;
	 int r = getreg(sp.fixed);
	 space nsp;
	 int big;
	 unsigned int small;
	 ans aa;
	 if (discrim(dest.answhere)!=notinreg)
	    return mka;
	 if (isbigval(e))
	 {
	    t = flt_to_f64(no(e),0,&ov);
	 }
	 else
	 {
	    t.big = (is_signed(sh(e)) && no(e) <0)?-1:0;
	    t.small = no(e);
	 }
	 nsp = guardreg(r,sp);
	 big = t.big;
	 imm_to_r(big,r);
	 setregalt(aa,r);
	 dest.ashwhere.ashsize = 32;
	 dest.ashwhere.ashalign = 32;
	 move(aa,dest,nsp.fixed,1);
	 small = t.small;
	 imm_to_r(small,r);
	 dest.answhere.val.instoreans.b.offset+=4;
	 move(aa,dest,nsp.fixed,1);
	 return mka;
      }
      if (no(e) == 0)
      {
	goto null_tag_case;
      }
      else
      {
	ash a;

	a = ashof(sh(e));
	if (a.ashsize == 32 || is_signed(sh(e)) ==0)
 	   constval = no(e);
	else if (a.ashsize == 8)
	{
	  constval = no(e) & 255;
	  constval -= (constval & 128) << 1;
	}
	else
	{
	  constval = no(e) & 65535;
	  constval -= (constval & 32768) << 1;
	}
	asm_comment("make_code val_tag: constval = %ld", constval);
	goto moveconst;
      }
    }

  case top_tag:
  case prof_tag:
  case clear_tag:
  {
     /* Do nothing */
     if (discrim(dest.answhere) ==insomereg)
     {
	int *sr = someregalt(dest.answhere);
	if (*sr!=-1)
	   error(ERR_SERIOUS, "Illegal register");
	*sr = GR0;
     }
     return mka;
  }

  case null_tag:
null_tag_case:
    {
      ans aa;

      setregalt(aa, GR0);
      mka.regmove = move(aa, dest, sp.fixed, 1);
      return mka;
    }

  case last_local_tag:
  {
     int r = GETREG(dest,sp);
     ans aa;
     baseoff b;
     int maxargbytes = max_args>>3;
     b.base = SP;
     b.offset = -maxargbytes - 4;
     ld_ins(i_lw,1,b,r);
     setregalt(aa, r);
     mka.regmove = move(aa,dest,sp.fixed,1);
     return mka;
  }

  case local_free_tag:
  {
     exp s = son(e);
     int r = reg_operand(s,sp);
     int maxargbytes = max_args>>3;
     if (SIMM14(maxargbytes))
	ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,maxargbytes,r,SP);
     else
     {
	ir_ins(i_addil,fs_L,empty_ltrl,maxargbytes,r);
	ld_ir_ins(i_ldo,cmplt_,fs_R,empty_ltrl,maxargbytes,GR1,SP);
     }
     if (Has_tos)
	reset_tos();
     return mka;
  }

  case local_free_all_tag:
  {
     if (Has_vsp)
     {
	rr_ins(i_copy,EP,SP);
	if (Has_tos)
	   reset_tos();
     }
     return mka;
  }

  case current_env_tag:
  {
     int r = GETREG(dest,sp);
     ans aa;
     rr_ins(i_copy,EP,r);
     setregalt(aa, r);
     mka.regmove = move(aa, dest, sp.fixed, 1);
     return mka;
  }

  case env_offset_tag: case general_env_offset_tag:
  {
     constval = frame_offset(son(e));
     goto moveconst;
  }

  case set_stack_limit_tag:
  {
     baseoff b;
     int r = reg_operand(son(e), sp);
     exp stl = find_named_tg("__TDFstacklim",
			     f_pointer(f_alignment(f_proc)));
     setvar(stl);
     b = boff(stl);
     st_ins(i_sw,r,b);
     return mka;
  }

  case give_stack_limit_tag:
  {
     baseoff b;
     ans aa;
     int r = GETREG(dest,sp);
     exp stl = find_named_tg("__TDFstacklim",
			     f_pointer(f_alignment(f_proc)));
     setvar(stl);
     b = boff(stl);
     ld_ins(i_lw,1,b,r);
     setregalt(aa,r);
     move(aa,dest,guardreg(r,sp).fixed,1);
     return mka;
  }

  case trap_tag:
  {
     if (no(e) == f_overflow)
     {
	do_exception(SIGFPE);
     }
     else
     if (no(e) == f_nil_access)
     {
	do_exception(SIGSEGV);
     }
     else
     {
	do_exception(SIGUSR1);
     }
     return mka;
  }

  case round_tag:
  {
      /*
       * Floating point variety to integer variety conversion.
       */
     int r = GETREG(dest,sp);
     freg f1,f2;
     ans aa;
     int s;
     baseoff b;
     space nsp;
     int us = !(is_signed(sh(e)));
     int rm = (int)round_number(e);
     unsigned char nm = name(sh(e));
     int inmem = (discrim(dest.answhere) ==notinreg);
     int trap=0;
     int br;
     nsp = sp;
     if (!optop(e))
	trap = trap_label(e);
      /*
       * rm = 0 = nearest, rm = 1 = smaller, rm = 2 = larger, rm = 3 = to zero
       */
     if (r==0 && !optop(e))
     {
	r = getreg(sp.fixed);
	nsp = guardreg(r, sp);
     }
     s = shape_size(sh(son(e)));
     if (name(sh(son(e))) ==doublehd && use_long_double)
     {
	if ( rm==3 && errhandle(e)<2 )
	/*
	 * Can't risk calling "_U_Qfcnvfxt_dbl_to_sgl"
	 * if error_treatment is continue
	 */
	{
     	   quad_op(e, nsp, dest);
	   if (nm == ucharhd && !inmem)
	      riir_ins(i_dep,c_,0,23,24,RET0);
	   else
	   if (nm == scharhd)
	      riir_ins(i_extrs,c_,RET0,31,8,RET0);
	   else
	   if (nm == uwordhd && !inmem)
	      riir_ins(i_dep,c_,0,15,16,RET0);
	   else
	   if (nm == swordhd)
	      riir_ins(i_extrs,c_,RET0,31,16,RET0);
	   setregalt(aa, RET0);
	   mka.regmove = move(aa, dest, nsp.fixed, 1);
	   if (inmem)
	      mka.regmove = NOREG;
	   return mka;
	}
	else
	{
	   /* Convert to double putting result in %fr4 */
      	   quad_op(e, nsp, dest);
	   f1.fr = 4;
	   /* and treat as a double.. */
	}
     }
     else
     {
	f1.fr = freg_operand(son(e),nsp,getfreg(nsp.flt));
     }
     b = mem_temp(0);
     br = getreg(nsp.fixed);
     ld_ins(i_lo,0,b,br);
     b.base = br; b.offset = 0;
     if (!optop(e) && us && (shape_size(sh(e)) <=32))
     {
	f2.fr = getfreg(guardfreg(f1.fr,nsp).flt);
	rrf_ins(i_fcpy,f_dbl,"",(R_FR0*3) +1,(3*f2.fr) +1);
     }
     else
	f2.fr = f1.fr;
     if (rm < 3)
     {
	if (rm > 0)
	{
	   /* Set rounding mode bits in floating point status register      */
	   if (rm == 1)
	      iiir_ins(i_zdepi,c_,-1,22,2,r);
	   else
	      iiir_ins(i_zdepi,c_,-1,21,1,r);
	   st_ins(i_sw,r,b);
	   ldf_ins(i_fldw,b,0);  /*  n.b. this zeros the exception register  */
	}
	/* Round and convert. */
	if (us)
	{
	   if (s > 32)
	   {
	      rrf_ins(i_fcnvfx,f_dbl,f_dbl,(f1.fr*3) +1,(f2.fr*3) +1);
	   }
	   else
	   {
	      rrf_ins(i_fcnvfx,f_sgl,f_dbl,(f1.fr*3) +1,(f2.fr*3) +1);
	   }
	}
	else if (s > 32)
	{
	   rrf_ins(i_fcnvfx,f_dbl,f_sgl,(f1.fr*3) +1,(f2.fr*3) +2);
	}
	else
	   rrf_ins(i_fcnvfx,f_sgl,f_sgl,(f1.fr*3) +1,(f2.fr*3) +2);
	if (!optop(e) && !us)
	   stf_ins(i_fstd,1,b);
	if (rm > 0)
	{
	   /*
	    * Reset rounding mode to rm = nearest (without corrupting
	    * the exception register data)
	    */
	   iiir_ins(i_zdepi,c_,0,22,2,r);
	   b.offset = 4;
	   st_ins(i_sw,r,b);
	   ldf_ins(i_fldw,b,0);
	   b.offset = 0;
	}
     }
     else
     {
	if ((!optop(e)) && (!us))
	{
	   /*  Zero exception register  */
	   st_ins(i_sw,GR0,b);
	   ldf_ins(i_fldw,b,0);
	}
	if (us)
	{
	   if (s > 32)
	   {
	      rrf_ins(i_fcnvfxt,f_dbl,f_dbl,(f1.fr*3) +1,(f2.fr*3) +1);
	   }
	   else
	   {
	      rrf_ins(i_fcnvfxt,f_sgl,f_dbl,(f1.fr*3) +1,(f2.fr*3) +1);
	   }
	}
	else if (s > 32)
	{
	   rrf_ins(i_fcnvfxt,f_dbl,f_sgl,(f1.fr*3) +1,(f2.fr*3) +2);
	}
	else
	   rrf_ins(i_fcnvfxt,f_sgl,f_sgl,(f1.fr*3) +1,(f2.fr*3) +2);
	if ((!optop(e)) && (!us))
	   stf_ins(i_fstd,1,b);
     }
     if (!optop(e))
     {
	if (us)
	{
	   stf_ins(i_fstd,(f2.fr*3) +1,b);
	   ld_ins(i_lw,1,b,r);
	   cj_ins(c_neq,r,0,trap);
	   b.offset=4;
	}
	else
	{
	   /*
	    * If the unimplemented flag in the exception
	    * register was set, then jump to trap.
	    */
	   ld_ins(i_lw,0,b,r);
	   imm_to_r(64,GR1);
	   rrr_ins(i_and,c_eq,r,GR1,0);
	   ub_ins(cmplt_N,trap);
	   stf_ins(i_fstw,(f2.fr*3) +2,b);
	}
	ld_ins(i_lw,1,b,r);
	test_if_outside_of_var(nm,r,trap);
	if (nm!=slonghd && nm!=ulonghd)
	   rr_ins(i_copy,GR1,r);
     }
     else
     {
	stf_ins(i_fstw,(f2.fr*3) +2,b);
	/* Load and shorten to type if needed. */
	if (nm == ucharhd)
	{
	   b.offset += 3;
	   ld_ins(i_lb,0,b,r);
	}
	else
	if (nm == scharhd)
	{
	   ld_ins(i_lw,1,b,r);
	   riir_ins(i_extrs,c_,r,31,8,r);
	}
	else
	if (nm == uwordhd)
	{
	   b.offset += 2;
	   ld_ins(i_lh,0,b,r);
	}
	else
	if (nm == swordhd)
	{
	   ld_ins(i_lw,1,b,r);
	   riir_ins(i_extrs,c_,r,31,16,r);
	}
	else
	   ld_ins(i_lw,1,b,r);
     }
     setregalt(aa,r);
     mka.regmove = move(aa, dest, nsp.fixed, 1);
     clear_freg(f2.fr<<1);
     return mka;
  }

  case int_to_bitf_tag:
    {
      int r;
      int size_res = shape_size(sh(e));
      int size_op = shape_size(sh(son(e)));
      ans aa;
      space nsp;

      r = reg_operand(son(e), sp);

      asm_comment("make_code int_to_bitf_tag: size=%d", size_res);

      /* maybe this not needed if going to memory +++ */
      if (size_res != size_op && size_res != 32)
      {
	int destr;

	switch (discrim(dest.answhere))
	{
      case inreg:
      {
	destr = regalt(dest.answhere);
	break;
      }
  default:
  {
    destr = getreg(sp.fixed);
  }
    }

	if (r==destr)
	   riir_ins(i_dep,c_,0,31-size_res,32-size_res,destr);
	else
	   riir_ins(i_zdep,c_,r,31,size_res,destr);
	r = destr;
      }

      /* r is appropriately truncated operand */

      nsp = guardreg(r, sp);
      setregalt(aa, r);
      move(aa, dest, nsp.fixed, 0);
      return mka;
    }

  case bitf_to_int_tag:
    {
      ash a;
      int r;
      where w;
      bool src_sgned = is_signed(sh(son(e)));
      bool target_sgned = is_signed(sh(e));

      a = ashof(sh(son(e)));
      switch (discrim(dest.answhere))
      {
      case inreg:
	{
	  r = regalt(dest.answhere);
	  break;
	}
      default:
	{
	  r = getreg(sp.fixed);
	}
      }

#if 0
      /* +++ enable */
      if ((name(son(e)) == cont_tag || name(son(e)) == name_tag)
	  && (a.ashsize == 8 || a.ashsize == 16 || a.ashsize == 32))
      {				/* simple extractions of bytes, halfs and
				 * words- see transform in check */
	where intreg;
	int olds = sh(son(e));

	setregalt(intreg.answhere, r);
	intreg.ashwhere.ashsize = a.ashsize;
	intreg.ashwhere.ashalign = a.ashsize;
	sh(son(e)) = sh(e);	/* should be done in scan */
	w = locate(son(e), sp, sh(e), r);
	move(w.answhere, intreg, guard(w, sp).fixed, is_signed(sh(e)));
	move(intreg.answhere, dest, sp.fixed, 1);
	sh(son(e)) = olds;
	keepreg(e, r);
	return mka;
      }
#endif

      /* else do shifts/and */
      setregalt(w.answhere, r);
      w.ashwhere = a;
      code_here(son(e), sp, w);

      asm_comment("make_code bitf_to_int_tag: size=%ld", a.ashsize);

      if (a.ashsize != 32 && src_sgned != target_sgned)
      {
	/* propogate/correct sign bits */
	/* +++ make move() handle this by pasting sign down */

	asm_comment("make_code bitf_to_int_tag: adjusting to sign/size %d/%ld -> %d/%ld",
		 src_sgned, a.ashsize,
		 target_sgned, a.ashsize);

	if (target_sgned)
	   riir_ins(i_extrs,c_,r,31,a.ashsize,r);
	else
	   riir_ins(i_dep,c_,0,31-a.ashsize,32-a.ashsize,r);
      }

      move(w.answhere, dest, guardreg(r, sp).fixed, 0);
      keepreg(e, r);
      return mka;
    }

  case alloca_tag:
  {
     /* Grow stack frame by n bytes and then grab n bytes */
     exp s=son(e);
     int maxargbytes=max_args>>3;
     ans aa;
     int r = GETREG(dest, sp);
     baseoff b;
     int n,t;
     if ( name(s)==val_tag )  /* n is a constant */
     {
	n = no(s);
	if (Has_ll)
	{
	   n+=4;
	}
	/*
	 * Adjust n to be multiple of 64 so stack stays 64 byte aligned
	 */
	n = (n+63) & ~(63);
	if (n != 0)
	{
	   /* alloca(n) = %sp - maxargbytes */
	   b.base = SP; b.offset = -maxargbytes;
	   ld_ins(i_lo,0,b,r);
	   /* grow stack frame, i.e. %sp -> %sp + n */
	   b.offset = n;
	   ld_ins(i_lo, 0, b, SP);
	}
     }
     else
     {
	space nsp;
	nsp = guardreg(r, sp);
	n = reg_operand(s, sp);
	t = getreg(nsp.fixed);
	/* adjust n so that stack stays 64 byte aligned */
	if (Has_ll)
	   ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,67,n,t);
	else
	   ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,63,n,t);
	riir_ins(i_dep,c_,0,31,6,t);

	/* alloca(n) = %sp - maxargbytes */
	b.base = SP;
	b.offset = -maxargbytes;
	ld_ins(i_lo,0,b,r);
	/* %sp -> %sp + n */
	rrr_ins(i_add,c_,SP,t,SP);
     }
     if (checkalloc(e))
     {
	exp stl = find_named_tg("__TDFstacklim",
	 	            f_pointer(f_alignment(f_proc)));
	setvar(stl);
	b = boff(stl);
	ld_ins(i_lw,1,b,GR1);
	if (stackerr_lab==0)
	{
	   stackerr_lab = new_label();
	}
	cj_ins(c_g,SP,GR1,stackerr_lab);
     }
     if (Has_tos)
	reset_tos();
     setregalt(aa, r);
     mka.regmove = move(aa, dest, guardreg(r, sp).fixed, 0);
     mka.lab = exitlab;
     if (Has_ll)
     {
	baseoff b;
	b.base = SP;
	b.offset = -maxargbytes -4;
	st_ins(i_sw,r,b);
     }
     return mka;
  }

  case movecont_tag:
  {
     exp szarg = bro(bro(son(e)));
     int dr, sr, sz, szr, mr,alt=0,lab;
     int finish = new_label();
     space nsp;
     where w;
     nsp = sp;
     w.ashwhere = ashof(sh(bro(bro(son(e)))));
     if (0 && name(szarg) ==val_tag)
     {
	sz = evalexp(szarg);
	if (sz==0)
	   return mka;
	else
	if (!(isnooverlap(e) || SIMM14(sz)))
	{
	   imm_to_r(sz,szr);
	}
     }
     else
     {
	szr = getreg(sp.fixed);
	setregalt(w.answhere, szr);
	make_code(szarg, sp, w, 0);
	nsp = guardreg(szr, sp);
	if (name(szarg) ==val_tag)
	{
	   if (no(szarg) ==0)
	      return mka;
	}
	else
	   cj_ins(c_eq,0,szr,finish);
     }
     sr = getreg(nsp.fixed);
     setregalt(w.answhere, sr);
     w.ashwhere = ashof(sh(son(e)));
     make_code(son(e), sp, w , 0);
     nsp = guardreg(sr, sp);
     dr = getreg(nsp.fixed);
     setregalt(w.answhere, dr);
     make_code(bro(son(e)), nsp, w, 0);
     nsp = guardreg(dr, nsp);
     cj_ins(c_eq,sr,dr,finish);
     mr = getreg(nsp.fixed);
     if (!isnooverlap(e))
     {
	alt = new_label();
	cj_ins(c_l,sr,dr,alt);
     }
     /* No overlap or dr<sr */
     lab = new_label();
     if (0 && name(szarg) ==val_tag)
     {
	if (SIMM14(sz))
	   ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,sz,sr,mr);
	else
	{
	   /* Moving more than 2^14 bytes. */
	   if (isnooverlap(e))
	   {
	      ir_ins(i_addil,fs_L,empty_ltrl,sz,sr);
	      ld_ir_ins(i_ldo,cmplt_,fs_R,empty_ltrl,sz,sr,mr);
	   }
	   else
	      rrr_ins(i_add,c_,szr,sr,mr);
	}
     }
     else
     {
	rrr_ins(i_add,c_,szr,sr,mr);
     }
     outlab("L$$",lab);
     ld_ir_ins(i_ldbs,cmplt_MA,fs_,empty_ltrl,1,sr,GR1);
     comb_ins(c_l,sr,mr,lab);
     st_ir_ins(i_stbs,cmplt_MA,GR1,fs_,empty_ltrl,1,dr);
     if (!isnooverlap(e))
     {
	/* Overlap or dr>sr */
	ub_ins(cmplt_N,finish);
	outlab("L$$",alt);
	lab = new_label();
	rr_ins(i_copy,sr,mr);
	if (0 && name(szarg) ==val_tag && SIMM14(sz))
	{
	      ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,sz,sr,sr);
	      ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,sz,dr,dr);
	}
	else
	{
	   rrr_ins(i_add,c_,sr,szr,sr);
	   rrr_ins(i_add,c_,dr,szr,dr);
	}
	outlab("L$$",lab);
	ld_ir_ins(i_ldbs,cmplt_MB,fs_,empty_ltrl,-1,sr,GR1);
	comb_ins(c_g,sr,mr,lab);
	st_ir_ins(i_stbs,cmplt_MB,GR1,fs_,empty_ltrl,-1,dr);
     }
     outlab("L$$",finish);
     clear_dep_reg(bro(son(e)));
     return mka;
  }

  default:
  {
      char C[64];
      sprintf(C,"TDF construct %d not done yet in make_code",name(e));
      error(ERR_SERIOUS, C);
    }
  }

  assert(0);			/* should have return/goto from switch */

  moveconst:
  {
     int r;
     if (discrim(dest.answhere) ==inreg)
     {
	r = regalt(dest.answhere);
	imm_to_r(constval,r);
     }
     else
     {
  	ans aa;
	if (constval == 0)
 	    r = GR0;		/* HPPA zero reg */
	else
	{
	   r = getreg(sp.fixed);
	   imm_to_r(constval,r);
	}
	setregalt(aa, r);
	move(aa, dest, guardreg(r, sp).fixed, 1);
     }
     mka.regmove = r;
     return mka;
   }
}				/* end make_code */


/*
 * commented out return_to_label_tag and make_stack_limit_tag for puposes
 * of debugging until proper 4.0 libraries are built.
 */

