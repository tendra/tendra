/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
  This file contains functions which handle the various aspects
  of procedure definition and invocation.
*/

#include <assert.h>
#include <string.h>

#include <shared/check.h>

#include <local/out.h>
#include <local/szs_als.h>
#include <local/diag_config.h>

#include <reader/expmacs.h>
#include <reader/exptypes.h>

#ifdef NEWDWARF
#include <local/dw2_config.h>
#endif

#include <reader/basicread.h>
#include <reader/externs.h>

#include <construct/tags.h>
#include <construct/installtypes.h>
#include <construct/exp.h>
#include <construct/shapemacs.h>

#include <main/flags.h>

#include "addrtypes.h"
#include "maxminmacs.h"
#include "proctypes.h"
#include "eval.h"
#include "move.h"
#include "comment.h"
#include "getregs.h"
#include "guard.h"
#include "locate.h"
#include "code_here.h"
#include "inst_fmt.h"
#include "sparcins.h"
#include "bitsmacs.h"
#include "labels.h"
#include "regexps.h"
#include "regmacs.h"
#include "regable.h"
#include "special.h"
#include "translate.h"
#include "makecode.h"
#include "proc.h"
#include "sparctrans.h"
#include "localexpmacs.h"

#ifdef NEWDIAGS
#include <newdiag/dg_globs.h>
#endif

#ifdef NEWDWARF
#include <dwarf2/dw2_info.h>
#include <dwarf2/dw2_basic.h>
#include "dw2_extra.h"
#endif

/*
  CODE GENERATION STATE FOR THE CURRENT PROCEDURE
*/

static void alloc_space(int,int);
static void alloc_reg_space(int,int);

extern int call_base_reg;

struct proc_state proc_state;
static exp current_proc;

int gencompat;
bool Has_vcallees = 0;
bool Has_no_vcallers = 0;
bool in_general_proc = 0;
bool May_have_callees = 0;


static bool in_postlude = 0;

extern char * proc_name;
int local_reg = R_I5;

int callee_start_reg = R_I5;   /* will point to start of callee params */

int callee_end_reg = R_I4;     /* will point to end of callee params.  Only
				  used for variable or dynamic parameter
				  lists */
int callee_start_reg_out = R_O5;
int callee_end_reg_out = R_O4;


static int vc_call = 0;

int aritherr_lab = 0;

int stackerr_lab = 0;
int local_stackerr_lab = 0;

#define is64(X)((name(X) ==u64hd) || (name(X) ==s64hd))


void call_tdf_main
(void) {
  outs("\tcall\t___TDF_main\n");
  outs("\tnop\n");
  return;
}




/*
  FIND TEMPORARY MEMORY
  This is a temporary location in the stack frame callee parameter
  save area that can be used in short instruction sequences, such
  as moving between float and fixed registers.  It is initialised
  in the procedure prelude.
*/

baseoff mem_temp
(int byte_offset) {
  baseoff b;
  b = proc_state.mem_temp0;
  /* only 2 words of temp allocated */
  assert(byte_offset >= 0 && byte_offset < 8);
  b.offset += byte_offset;
  return b;
}



/*
  Postlude chaining function
*/
static postlude_chain * old_postludes;

void update_plc
(postlude_chain* chain, int maxargs) {

  while (chain) {
    exp pl = chain->postlude;
    while (name(pl) == ident_tag) {
      if (name(son(pl)) == caller_name_tag)
	no(pl) += (maxargs<<1);
      pl = bro(son(pl));
    }
    chain = chain->outer;
  }
  return;
}


/*
  ENCODE A PROCEDURE DEFINITION
*/

makeans make_proc_tag_code
(exp e, space sp, where dest, int exitlab) {
  procrec *pr = &procrecs[no(e)];
  needs *ndpr = &pr->needsproc;
  spacereq *sppr = &pr->spacereqproc;
  long pprops = (long)(ndpr->prps);
  bool leaf = ( bool ) ( ( pprops & anyproccall ) == 0 ) ;	/* LINT */
  long maxargs = ndpr->maxargs ;/* maxargs of proc body in bits */
  long st = sppr->stack ;		/* space for locals in bits */
  struct proc_state old_proc_state;
  makeans mka;
  exp par;
  old_postludes = (postlude_chain*)NULL;
  current_proc = e;
  Has_vcallees = (name(e) == general_proc_tag) && (proc_has_vcallees(e));
  Has_no_vcallers = (name(e) == proc_tag) || (!proc_has_vcallers(e));
  in_general_proc = (name(e) == general_proc_tag);
  if (gencompat) {
    May_have_callees = proc_may_have_callees(e);
  }
  /* save & reinstate proc_state for nested procs */
  old_proc_state = proc_state;
  mka.lab = exitlab;
  mka.regmove = NOREG;
  if ((gencompat && May_have_callees) || (!gencompat && in_general_proc)) {
    sp = guardreg(callee_start_reg,sp);
  }

  if (Has_vcallees) {
    sp = guardreg(callee_end_reg,sp);
    outs("\t.optim\t\"-O0\"\n"); /* as -O2 optimises out some moves
				    from %sp to other registers */
  }

  /* this is a procedure definition */
  assert(name(e) == proc_tag || name(e) == general_proc_tag);

  /* set global flag for res_tag */
  proc_state.leaf_proc = leaf;

  /* maxargs is the maxargs in bits of any proc called, not this proc */

  /* SPARC reserved stack area */
  if (leaf) {
    /* reg window dump area */
    assert(maxargs == 0);
    maxargs = (16)* 32;
  }
  else {
    assert(maxargs >= 0);
    /* at least reg param dump for calls */
    if (maxargs < (6)* 32)maxargs = (6)* 32;
    /* plus reg window dump area + hidden struct return param */
    maxargs += (16 + 1)* 32;
  }

  /* use space we are allowing for called procs */
  proc_state.mem_temp0.base = R_SP;
  proc_state.mem_temp0.offset = (16 + 1 + 1)* 4;

  /* double word aligned */
  assert((proc_state.mem_temp0.offset & 7) == 0);

  /* make sure mem_temp () is allowed for */
  if (proc_state.mem_temp0.base == R_SP &&
       maxargs < ((proc_state.mem_temp0.offset + 8) << 3)) {
    /* ie, a leaf proc */
    assert(leaf);
    maxargs = (proc_state.mem_temp0.offset + 8) << 3;
    }

  /* align to 64 bit boundaries */
  maxargs = (maxargs + 63) & ~63;
  st = (st + 63) & ~63;
  /* -----------------------WARNING--------------------------- */
  /* if you alter these then please check boff_env_offset, 'cos
     they're effectively reproduced there..... */
  proc_state.locals_space = st;
  proc_state.locals_offset = 0;
  /*proc_state.params_offset = ( 16 + 1 ) * 32 ;*/
  proc_state.params_offset = PARAMS_OFFSET;
  proc_state.callee_size = ndpr->callee_size;
  /* beyond register window save area and hidden param of
     caller's frame */

  proc_state.frame_size = maxargs + st;
  proc_state.maxargs = maxargs;

  st = proc_state.frame_size >> 3;

#ifdef NEWDWARF
  if (diag == DIAG_DWARF2) {
    START_BB();
    dw2_start_fde(current_proc);
  }
#endif

  if (name(e) == general_proc_tag) {
    if (proc_has_checkstack(e) && (st > 64)) {
      rir_ins(i_save,R_SP,-64,R_SP);
    }
    else {
      rir_ins(i_save,R_SP,-st,R_SP);
    }
#ifdef NEWDWARF
    if (diag == DIAG_DWARF2)
      dw2_fde_save();
#endif
    if (gencompat && May_have_callees) {
      int entry_lab = new_label();
      uncond_ins(i_b,entry_lab);
      /*rir_ins(i_save,R_SP,0,R_SP);*/

      if (st>64) {
	rir_ins(i_sub,R_SP, st - 64,R_SP);
      }
      set_label(entry_lab);
    }
  }
  else{
    rir_ins(i_save, R_SP, -st, R_SP);
#ifdef NEWDWARF
    if (diag == DIAG_DWARF2)
      dw2_fde_save();
#endif
    /* more here about fp */
  }

  /* position independent code */
  if (PIC_code && proc_uses_external(e)) {
    char *g = "__GLOBAL_OFFSET_TABLE_";
    if (sysV_assembler)g++;
    outs("1:\n");
    outs("\tcall\t2f\n");
    outf("\tsethi\t%%hi(%s+ (.-1b)),%%l7\n", g);
    outs("2:\n");
    outf("\tor\t%%l7,%%lo(%s+ (.-1b)),%%l7\n", g);
    outs("\tadd\t%l7,%o7,%l7\n");
#ifdef NEWDWARF
    if (diag == DIAG_DWARF2)
      lost_count_ins();
#endif
  }

  local_stackerr_lab = 0;
  stackerr_lab = 0;
  if (name(e) == general_proc_tag) {
    if (proc_has_checkstack(e)) {
      baseoff b;
      int rtmp;
      int rt;
      if (st > 64) {
	rt = getreg(sp.fixed);
	rir_ins(i_sub,R_SP,(st - 64),rt);
      }
      else {
	rt = R_SP;
      }
      b = find_tag(TDF_STACKLIM);
      stackerr_lab = new_label();
      rtmp = getreg(guardreg(rt,sp).fixed);
      ld_ins(i_ld,b,rtmp);
      condrr_ins(i_bgtu,rtmp,R_SP,stackerr_lab);
      if (rt != R_SP) {
	rr_ins(i_mov,rt,R_SP);
      }
    }

    /* Here we make a local copy of the callees */
    if (Has_vcallees) {
      baseoff b;
      int copy_lab = new_label();
      int end_copy_lab = new_label();
      /* copy callees to new space (pointed to by reg rdest) */
      int rsize = getreg(sp.fixed);
      int rdest = getreg(guardreg(rsize,sp).fixed);
      int rt = getreg(guardreg(rdest,sp).fixed);
      rrr_ins(i_sub,callee_end_reg,callee_start_reg,rsize);
      condrr_ins(i_be,rsize,R_G0,end_copy_lab);
      alloc_reg_space(rsize,rdest);
      b.offset = 0;
      set_label(copy_lab);
      b.base = callee_start_reg;
      ld_ro_ins(i_ld,b,rt);
      b.base = rdest;
      st_ro_ins(i_st,rt,b);
      rir_ins(i_add,callee_start_reg,PTR_SZ>>3,callee_start_reg);
      rir_ins(i_add,rdest,PTR_SZ>>3,rdest);
      condrr_ins(i_bne,callee_start_reg,callee_end_reg,copy_lab);
      /* now set up the new callee pointers */
      rr_ins(i_mov,rdest,callee_end_reg);
      rrr_ins(i_sub,rdest,rsize,callee_start_reg);
      set_label(end_copy_lab);
    } else if ((gencompat && May_have_callees) || !gencompat) {
      baseoff b;
      int size = proc_state.callee_size/8;
      int rdest = getreg(sp.fixed);
      int el;
      int rt = getreg(guardreg(rdest,sp).fixed);
      alloc_space(size,rdest);
      b.offset = 0;
      for (el = proc_state.callee_size/8;el>0;el -= (PTR_SZ>>3)) {
	b.base = callee_start_reg;
	b.offset = el - (PTR_SZ>>3);
	ld_ro_ins(i_ld,b,rt);
	b.base = rdest;
	st_ro_ins(i_st,rt,b);
      }
      /* now deallocate old storage.  This is needs for outpars to be
	 accessed properly from postludes. */
#if 0
      rir_ins(i_add,callee_start_reg,((proc_state.callee_size>>3) +7) &~7,callee_start_reg);
      rir_ins(i_sub,callee_start_reg,96,R_FP);
#endif
      rr_ins(i_mov,rdest,callee_start_reg);

    }
  }
  if (do_profile) {
      /* implement -p option, call mcount */
    static int p_lab = 0;
    p_lab++;
    if (sysV_assembler) {
      outs("\t.reserve\tLP.");
      outn(p_lab);
      outs(",4,\".bss\",4\n");
      }
    else {
      outs("\t.reserve\tLP.");
      outn(p_lab);
      outs(",4,\"bss\",4\n");
    }
    insection(text_section);
    outs("\tset\tLP.");
    outn(p_lab);
    outs(",%o0\n");
#ifdef NEWDWARF
    if (diag == DIAG_DWARF2)
      lost_count_ins();
#endif
    extj_special_ins(i_call, "mcount", 1);
  }

    /* Move params if necessary */
  par = son(e);
  while (name(par) == ident_tag) {
    if (isparam(par)) {
      /* Got a parameter ident */
      int r = (int)props(son(par));
      /* ( r == 0 ) ? ( on stack ) : ( input reg no ) */
/*	assert ( name ( son ( par ) ) == clear_tag ) ;*/

      if (r != 0) {
	/* Parameter in register */
	assert(R_I0 <= r && r <= R_I5);

	if (no(par)!= 0) {
	  if (no(par) == R_NO_REG) {
	    /* struct/union parameter, on stack aleady,
	       nothing useful in reg */
	    assert(!fixregable(par) &&
		     !floatregable(par));
	  }
	  else if (no(par) == r) {
	    if (name(sh(son(par))) == ucharhd) {
	      rir_ins(i_and, r, 255, no(par));
	    }
	    else if (name(sh(son(par))) == uwordhd) {
	      rir_ins(i_and, r, 65535, no(par));
	    }
	  }
	  else {
	    if (name(sh(son(par))) == ucharhd) {
	      rir_ins(i_and, r, 255, no(par));
	    }
	    else if (name(sh(son(par))) == uwordhd) {
	      rir_ins(i_and, r, 65535, no(par));
	    }
	    else {
	      rr_ins(i_mov, r, no(par));
	    }
	  }
	}
	else {
	  /* Parameter in reg move to stack */
	  baseoff stackpos;
	  long size = shape_size(sh(son(par)));
	  int offs = (int)((no(son(par)) +
				 proc_state.params_offset) >> 3);
	  stackpos.base = R_FP;
	  stackpos.offset =offs;

	  switch (size) {
	    case  8: st_ro_ins(i_stb, r, stackpos); break;
	    case 16: st_ro_ins(i_sth, r, stackpos); break;
	    case 32: st_ro_ins(i_st,  r, stackpos); break;
	    case 64: {
	      /* A double can be passed first word in reg
		 (R_I5) and second word on stack. Must only
		 store out first word in this case  */
	      st_ro_ins(i_st, r, stackpos);
	      if (r != R_I5) {
		/* float point double passed in fixed
		   point reg pair */
		stackpos.offset += 4;
		st_ro_ins(i_st, r + 1, stackpos);
	      }
	      break;
	    }
	    default : {
	      fail("bad size in make_proc_tag_code");
	      break;
	    }
	  }
	}
      }
      else {
	/* Param on stack, no change */
      }
    }
    par = bro(son(par));
  }

  clear_all();


    if ((pprops & long_result_bit)!= 0) {
      /* structure or union result, address of space to [ %fp+64 ] */
      instore is;
      /* [%fp+64] as per call convention */
      is.adval = 0;
      is.b.base = R_FP;
      is.b.offset = (16 * 4);
      setinsalt(proc_state.procans, is);
    }
    else if ((pprops & realresult_bit)!= 0) {
      /* proc has real result */
      freg frg;
      frg.fr = 0;
      frg.dble = (bool)((pprops & longrealresult_bit)? 1 : 0);
      setfregalt(proc_state.procans, frg);
    }
    else if ((pprops & has_result_bit)!= 0) {
      setregalt(proc_state.procans, R_I0);
    }
    else {
      /* no result */
      setregalt(proc_state.procans, R_G0);
    }

    proc_state.rscope_level = 0;
    proc_state.result_label = 0;

    /* code for body of proc */
#if 1
    if (abi != ABI_SYSV && do_dynamic_init && !strcmp(proc_name,"_main")) {
      call_tdf_main();
    }
#endif
   (void)code_here(son(e), sp, nowhere);
    clear_all();
    if (stackerr_lab) {
      set_label(stackerr_lab);
      fprintf(as_file, "\t%s\n", i_restore);
      if (local_stackerr_lab) {
	set_label(local_stackerr_lab);
      }

      /*rir_ins(i_add,R_SP,proc_state.frame_size>>3,R_SP);*/
      do_exception(f_stack_overflow);
    }
    if (aritherr_lab != 0) {
      set_label(aritherr_lab);
      do_exception(f_overflow);
    }

#ifndef RET_IN_CODE
    if (proc_state.result_label !=0) {
      set_label(proc_state.result_label);
#ifdef NEWDWARF
      if (diag == DIAG_DWARF2)
        dw2_return_pos(0);
#endif
      ret_restore_ins();
    }
#endif
#ifdef NEWDWARF
    if (diag == DIAG_DWARF2)
      dw2_complete_fde();
#endif
    proc_state = old_proc_state;
    return mka;
}



/*
  ENCODE A PROCEDURE RESULT
*/

makeans make_res_tag_code
(exp e, space sp, where dest, int exitlab) {
  where w;
  makeans mka;
  mka.lab = exitlab;
  mka.regmove = NOREG;
  assert(name(e) == res_tag || name(e) == untidy_return_tag);
  w.answhere = proc_state.procans;
  w.ashwhere = ashof(sh(son(e)));
 (void)code_here(son(e), sp, w);
  assert(proc_state.rscope_level == 0);
				/* procedure return */
  switch (discrim(w.answhere)) {
    case notinreg: {
      instore isw;
      isw = insalt(w.answhere);
      /* [%fp+64] as per call convention */
      if (isw.adval == 0 && isw.b.base == R_FP &&
	   isw.b.offset == (16 * 4)) {
	/* struct or union result */
#ifdef NEWDWARF
	if (diag == DIAG_DWARF2)
	  dw2_return_pos(0);
#endif
	stret_restore_ins();
	break;
      }
	   /* FALL THROUGH */
    }
    default :
    {
      /* not struct or union result */
      if (proc_state.leaf_proc && name(e) == res_tag && !sysV_assembler
#ifdef NEWDIAGS
		&& !diag_visible) {
#else
		&& diag == DIAG_NONE) {
#endif
	/* Use only one return per proc, as this is necessary
	   for the peep-hole assembler 'as -O' to recognise
	   leaf procs (not applicable in SunOS
	   5 assembler).  Empirical tests show that using last
	   return is very slightly faster for SPECint tests
		- but beware of confusing diagnostic info */
	if (proc_state.result_label == 0) {
	  /* first return in proc, generate return */
	  proc_state.result_label = new_label();
	  /* first return in a leaf proc is ret_restore,
	     others branch here */
#if RET_IN_CODE
	  set_label(proc_state.result_label);
	  {
	    baseoff b;
	    b.base = R_FP;
#if 0
	    if (Has_vcallees) {
	      baseoff b;
	      b.base = R_FP;
	      b.offset = -4 * PTR_SZ>>3;
	      ld_ro_ins(i_ld,b,local_reg);
	    }
#endif
	  }
#ifdef NEWDWARF
	  if (diag == DIAG_DWARF2)
	    dw2_return_pos(0);
#endif
	  if (name(e) == res_tag) {
	    ret_restore_ins();
	  }
	  else {
	    fprintf(as_file, "\t%s\n", i_ret);
#ifdef NEWDWARF
	    if (diag == DIAG_DWARF2)
	      count_ins(1);
#endif
	    rir_ins(i_restore,R_SP,-proc_state.maxargs>>3,R_SP);
	  }

#else
	  uncond_ins(i_b, proc_state.result_label);
#endif
	}
	else {
	  /* jump to the return for this proc */
	  uncond_ins(i_b, proc_state.result_label);
	}
      }
      else {
	baseoff b;
	b.base = R_FP;
#if 0
	if (Has_vcallees) {
	  baseoff b;
	  b.base = R_FP;
	  b.offset = -4 * PTR_SZ>>3;
	  ld_ro_ins(i_ld,b,local_reg);
	}
#endif
	/* return here, avoiding cost of branch to return */
#ifdef NEWDWARF
	if (diag == DIAG_DWARF2)
	  dw2_return_pos(0);
#endif
	if (name(e) == res_tag) {
	  ret_restore_ins();
	}
	else {
	  fprintf(as_file, "\t%s\n", i_ret);
#ifdef NEWDWARF
	  if (diag == DIAG_DWARF2)
	    count_ins(1);
#endif
	  rir_ins(i_restore,R_SP,-proc_state.maxargs>>3,R_SP);
	  /*fprintf ( as_file, "\t%s,\%sp,0,\%sp\n", i_restore ) ;*/
	}
	/*      ret_restore_ins () ;*/
      }
    }
  }
  /* regs invalid after return (what about inlining?) */
  clear_all();
  return mka;
}


/*
  ENCODE A PROCEDURE CALL
*/
extern int reg_result(shape);

makeans make_apply_tag_code
(exp e, space sp, where dest, int exitlab) {
  exp fn = son(e);
  exp par = bro(fn);
  exp list = par;
  int hda = (int)name(sh(e));
  int special;
  int param_reg = R_O0 ;	 /* next param reg to use */
  int param_regs_used ;	 /* how many were used */
  ash ansash;
  space nsp;
  int void_result = ((name(sh(e)) == tophd) ||
		    (name(sh(e)) == bothd));

  int reg_res = reg_result(sh(e));
  int guarded_dest_reg = R_NO_REG ;/* reg used to address tuple result */
  makeans mka;

  exp dad = father(e);
  bool tlrecurse = (bool)(proc_state.rscope_level == 0 &&
			      name(dad) == res_tag && props(dad));

  nsp = sp;

  mka.lab = exitlab;
  mka.regmove = NOREG;
  assert(name(e) == apply_tag);

  /* first see if it is a special to be handled inline */
  if ((special = specialfn(fn)) > 0) {
    /* eg function is strlen */
    mka.lab = specialmake(special, list, sp, dest, exitlab);
    return mka;
  }

  ansash = ashof(sh(e));

  if (!reg_res && !void_result) {
    /* structure or union result, address of space to [%sp+64]
     must do this before evaluating args as dest may use param reg */
    instore is;
    baseoff stack_struct_ret_addr;

    /* [%sp+64] as per call convention */
    stack_struct_ret_addr.base = R_SP;
    stack_struct_ret_addr.offset = (16 * 4);

    assert(discrim(dest.answhere) == notinreg);
    if(discrim(dest.answhere) != notinreg){	/* should be redundant */
      is.b = mem_temp(0);
      is.adval = 1;
    }
    else{
      is = insalt(dest.answhere);
    }
    if (is.adval) {
      /* generate address of dest */
      if (IS_FIXREG(is.b.base)) {
	if (is.b.offset == 0) {
	  st_ro_ins(i_st, is.b.base, stack_struct_ret_addr);
	}
	else {
	  rir_ins(i_add, is.b.base, is.b.offset, R_TMP);
	  st_ro_ins(i_st, R_TMP, stack_struct_ret_addr);
	}
	guarded_dest_reg = is.b.base ;	/* can be guarded */
      }
      else {
	set_ins(is.b, R_TMP);
	st_ro_ins(i_st, R_TMP, stack_struct_ret_addr);
      }
    }
    else {
      /* load dest */
      ld_ins(i_ld, is.b, R_TMP);
      st_ro_ins(i_st, R_TMP, stack_struct_ret_addr);
    }
  }


  /* evaluate params to param reg or stack */
  if (!last(fn)) {
    int param_offset = (16 + 1)* 32;
    /* beyond reg window save area and hidden param of caller's frame */

    /* evaluate parameters in turn */
    for (; ;) {
      ash ap;
      where w;
      shape a = sh(list);
      int hd = (int)name(a);
      ap = ashof(a);
      w.ashwhere = ap;

      if ( 0 /*struct_par*/ ) {
	/* non-ABI construct being used - give stronger warning */
	if (abi == ABI_SYSV) fail("Structure parameter passed by value");
      }

      if (is_floating(hd) && param_reg <= R_O5) {
	/* Float point. Copy to stack as if stack parameter,
	   then recover words as needed into fixed point regs */
	instore is;
	/* Locations we offer may not be aligned for doubles.  We
	   assume 'move' can cope with this */
	is.b.base = R_SP;
	is.b.offset = param_offset >> 3;
	is.adval = 1;

	setinsalt(w.answhere, is);
	(void)code_here(list, nsp, w);
	ld_ro_ins(i_ld, is.b, param_reg);
	nsp = guardreg(param_reg, nsp);
	param_reg++;
	param_offset += 32;

	if (hd != shrealhd) {
	  /* double */
	  if (param_reg <= R_O5) {
	    /* double whose second word can go in reg */
	    is.b.offset += 4;
	    ld_ro_ins(i_ld, is.b, param_reg);
	    nsp = guardreg(param_reg, nsp);
	    param_reg++;
	  }
	  param_offset += 32;
	}
      }
      else if (valregable(sh(list)) && param_reg <= R_O5) {
	/* fixed point parameter in a single reg */
	nsp = guardreg(param_reg, nsp);
	reg_operand_here(list, nsp, param_reg);
	param_reg++;
	param_offset += 32;
      }
      else {
	/* stack parameter */
	instore is;
	/* Locations we offer may not be aligned for doubles.
	   We assume 'move' can cope with this  */
	is.b.base = R_SP;
	is.b.offset = param_offset >> 3;
	is.adval = 1;
	if (valregable(sh(list)) &&
	    (ap.ashsize == 8 || ap.ashsize == 16)) {
	  /* Byte or 16bit scalar parameter - convert to integer.
	     We must pass a full word to conform with SPARC ABI,
	     so have to expand source to full word.  We do this
	     by loading into a reg */
	  int r = reg_operand(list, nsp);
	  ans op;
	  setregalt(op, r);
	  /* round down to word boundary */
	  is.b.offset &= ~0x3;
	  ap.ashsize = ap.ashalign = 32;
	  w.ashwhere = ap;
	  setinsalt(w.answhere, is);
	 (void)move(op, w, guardreg(r, nsp).fixed, 1);
	}
	else {
	  setinsalt(w.answhere, is);
	 (void)code_here(list, nsp, w);
	}
	param_offset = (int)(param_offset + ap.ashsize);
      }

      if (last(list))break;
      list = bro(list);
    }
  }

  assert(param_reg >= R_O0 && param_reg <= R_O5 + 1);
  param_regs_used = param_reg - R_O0;

  if (special != 0) {
    extj_special_ins(i_call, special_call_name(special),
		       param_regs_used);
  }
  else if (name(fn) == name_tag &&
	      name(son(fn)) == ident_tag &&
	     (son(son(fn)) == NULL ||
		(name(son(son(fn))) == proc_tag ||
		 name(son(son(fn))) == general_proc_tag))) {
    baseoff b;
    b = boff(son(fn));
    if (!tlrecurse) {
#ifdef NEWDWARF
      if (current_dg_info) {
	current_dg_info->data.i_call.brk = set_dw_text_label();
	current_dg_info->data.i_call.p.k = WH_CODELAB;
	current_dg_info->data.i_call.p.u.l = b.base;
	current_dg_info->data.i_call.p.o = b.offset;
      }
#endif
      extj_ins(i_call, b, param_regs_used);
    }
    else {
      assert(!tlrecurse);
    }
  }
  else {
    int r = reg_operand(fn, nsp);
#ifdef NEWDWARF
    if (current_dg_info) {
      current_dg_info->data.i_call.brk = set_dw_text_label();
      current_dg_info->data.i_call.p.k = WH_REG;
      current_dg_info->data.i_call.p.u.l = r;
    }
#endif
    extj_reg_ins(i_call, r, param_regs_used);
  }

  if (!reg_res && !void_result) {
    /* Generate unimp instruction, as per structure result call
       convention.  Argument is low-order 12 bits of structure size,
       see section D.4 of * SPARC architecture manual */
    unimp_ins((long)((ansash.ashsize / 8) & 0xfff));
  }

#ifdef NEWDWARF
  if (diag == DIAG_DWARF2)
    START_BB();
#endif

  /* grab clobbered %g and %o regs, as safety test for bad code */
  {
    int r;
    space gsp;
    gsp = sp;

    /* %g1..%g_reg_max, %o0..%o7 */
    for (r = R_G1; r < R_O7 + 1;
		     r = ((r == R_G0 + g_reg_max)? R_O0 : r + 1)) {
      /* skip R_O0 as often used in result-reg optimisation */
      if (!(r == R_TMP || r == R_O0 || r == R_SP ||
	      r == guarded_dest_reg)) {
	/* not special regs */
	gsp = needreg(r, gsp);
      }
    }
  }
  clear_all () ;	/* ??? not %i0..%l7 that may be t-regs */

  if (reg_res) {
    ans aa;
    if (is_floating(hda)) {
      freg frg;
      frg.fr = 0;
      frg.dble = (bool)(hda != shrealhd);
      setfregalt(aa, frg);
      /* move floating point result of application to destination */
     (void)move(aa, dest, sp.fixed, 1);
    }
    else {
      setregalt(aa, R_O0);
      if (discrim(dest.answhere) == inreg) {
	int r = regalt(dest.answhere);
	if (r == R_G0) {
	  /* void result */
	}
	else if (r != R_O0) {
	  /* move result from %o0 */
	 (void)move(aa, dest, sp.fixed, 1);
	}
	else {
	  /* no move required */
	}
	mka.regmove = R_O0;
      }
      else {
	(void)move(aa, dest, sp.fixed, 1);
      }
    }
  }
  else {
    /* not register result */
  }
  return mka;
}


static space do_callers
(exp list, space sp, int* param_reg, bool trad_call) {
  int param_offset = (16+1)*32; /* beyond reg window save area &
				 hidden param of callers frame */
  int last_reg;

  if ((gencompat && !trad_call) || (!gencompat && in_general_proc)) {
    if (vc_call) {
      last_reg = R_O3;
    }
    else {
      last_reg = R_O4;
    }
  }
  else {
    last_reg = R_O5;
  }

  for (;;) {
    ash ap;
    where w;
    shape a = sh(list);
    int hd = (int)name(a);
    exp par = (name(list) == caller_tag)?son(list): list;
    ap = ashof(a);
    w.ashwhere = ap;
    if (is_floating(hd) && *param_reg <= last_reg) {
      /* floating pt.  Copy to stack as if stack param then recover
	 into fixed point reg */
      instore is;
      is.b.base = R_SP;
      is.b.offset = param_offset>>3;
      is.adval = 1;
      setinsalt(w.answhere,is);
     (void)code_here(par, sp, w);
      if (hd == doublehd) {
	rir_ins(i_add,is.b.base,is.b.offset,*param_reg);
      }
      else {
	ld_ro_ins(i_ld, is.b, *param_reg);
      }
      sp = guardreg(*param_reg, sp);
     (*param_reg) ++;
      param_offset += 32;
      if (hd == realhd) {
	/* double */
	if (*param_reg <= last_reg) {
	  /* double whose second word can go in reg */
	  is.b.offset += 4;
	  ld_ro_ins(i_ld, is.b, *param_reg);
	  sp = guardreg(* param_reg, sp);
	 (*param_reg) ++;
	}
	param_offset += 32;
      }
    }
    else if (valregable(sh(list)) && *param_reg <= last_reg) {
      /* fixed point parameter in a single reg */
      sp = guardreg(*param_reg, sp);
      reg_operand_here(list, sp, *param_reg);
     (*param_reg) ++;
      param_offset += 32;
    }
    else {
      /* stack parameter */
      instore is;
      /* Locations we offer may not be aligned for doubles.
	 We assume 'move' can cope with this  */
      is.b.base = R_SP;
      is.b.offset = param_offset >> 3;
      is.adval = 1;
      if (valregable(sh(list)) &&
	  (ap.ashsize == 8 || ap.ashsize == 16)) {
	/* Byte or 16bit scalar parameter - convert to integer.
	   We must pass a full word to conform with SPARC ABI,
	   so have to expand source to full word.  We do this
	   by loading into a reg */
	int r = reg_operand(list, sp);
	ans op;
	setregalt(op, r);
	/* round down to word boundary */
	is.b.offset &= ~0x3;
	ap.ashsize = ap.ashalign = 32;
	w.ashwhere = ap;
	setinsalt(w.answhere, is);
	(void)move(op, w, guardreg(r, sp).fixed, 1);
      }
      else{
	setinsalt(w.answhere, is);
	(void)code_here(par, sp, w);
      }
      if (*param_reg <= last_reg) {
	/* Copy back into the correct param regs */
	int start_offset = is.b.offset;
	int block_size = w.ashwhere.ashsize;
	baseoff curr_pos;
	curr_pos.base = R_SP;
	curr_pos.offset = start_offset;
	if (is64(sh(list)) || (name(sh(list)) == cpdhd) ||
	  (name(sh(list)) == nofhd)) {
	  rir_ins(i_add,curr_pos.base,curr_pos.offset,*param_reg);
	 (*param_reg) ++;
	  block_size -=32;
        }
	else {
	  while (*param_reg <= last_reg && block_size>0) {
	    ld_ro_ins(i_ld,curr_pos,*param_reg);
	    ++ (*param_reg);
	    curr_pos.offset += 4;
	    block_size -= 32;
	  }
	}
      }
      param_offset = (int)(param_offset + ap.ashsize);
    }
    if (last(list)) return sp;
    list = bro(list);
  }

  return sp;
}

/*
  Give the first parameter par_base, find parameter 'num'
*/
exp get_param
(exp par_base, int num) {
  exp res_exp = par_base;
  int current_par;
  if (num == 1) return par_base;
  for (current_par = 2;current_par<=num;++current_par) {
    res_exp = bro(res_exp);
  }
  return res_exp;
}




/*
  Move the caller parameters up the stack from their current position
  by %size_reg bytes.  The function assumes that there will always be at
  least one parameter.
*/
static void move_parameters
(exp callers, int size_reg, space sp) {
  int param_offset;   /* offset of first parameter */
  int newbase;
  baseoff b;
  int last_caller = 0;
  int has_callers = 0;
  exp current_caller = son(callers);
  int rtmp = getreg(sp.fixed);
  int rtop = getreg(guardreg(rtmp,sp).fixed);
  int i;

  param_offset = 64;
  for (i=0;i<no(callers);++i) {
    if (shape_size(sh(current_caller)) > 32)
      param_offset += 8;
    else
      param_offset += 4;
    current_caller = bro(current_caller);
  }
  current_caller = son(callers);


  /* top is sp + param_offset + callers * num */
  while (!last_caller) {
    last_caller = last(current_caller);
    if (name(current_caller) == caller_tag) {
      has_callers = 1;
    }
    current_caller = bro(current_caller);
  }
  current_caller = son(callers);
  last_caller = 0;

  if (!has_callers) return;
  rir_ins(i_add,R_SP,param_offset /*+ (no(callers))*/,rtop);


  b.offset = param_offset;
  b.offset = 0;
  if (size_reg == R_NO_REG)
    newbase = rtop;
  else {
    newbase = getreg(guardreg(rtop,sp).fixed);
    rrr_ins(i_add,rtop,size_reg,newbase);
  }
  assert(current_caller != (exp)NULL);

  for (i=no(callers);i>0;--i) {
    exp par = get_param(son(callers),i);
    if (name(par) == caller_tag) {
      /* move it up the stack */
      b.base = rtop;
      ld_ro_ins(i_ld,b,rtmp);
      b.base = newbase;
      st_ro_ins(i_st,rtmp,b);
      if (shape_size(sh(par)) > 32) {
	b.base = rtop;
	b.offset = -4;
	ld_ro_ins(i_ld,b,rtmp);
	b.base = newbase;
	st_ro_ins(i_st,rtmp,b);
      }
      b.offset -= 4;
    }
    else
      b.offset -= (shape_size(sh(par)) > 32 ? 8 : 4);
  }
  return;
}



makeans make_apply_general_tag_code
(exp e, space sp, where dest, int exitlab) {
  exp fn = son(e);
  exp callers = bro(fn);
  exp cllees = bro(callers);
  exp postlude = bro(cllees);
  int hda = (int)name(sh(e));
  int param_reg = R_O0;
  int param_regs_used;
  ash ansash;
  space nsp;
  int void_result = ((name(sh(e)) == tophd) ||
		    (name(sh(e)) == bothd));

  int reg_res = reg_result(sh(e));
  int guarded_dest_reg = R_NO_REG; /* reg used to address tuple result */
  makeans mka;
  exp dad = father(e);
  bool tlrecurse = (bool)(proc_state.rscope_level == 0 &&
			      name(dad) == res_tag && props(dad));
  bool trad_call = 0;
  ansash = ashof(sh(e));
  nsp = sp;
  mka.lab = exitlab;
  mka.regmove = NOREG;
  if ((call_has_vcallees(cllees)!= 0)) {
    outs("\t.optim\t\"-O0\"\n");
  }

  param_regs_used = param_reg - R_O0;

  if (gencompat && (call_has_vcallees(cllees) == 0)) {
    if (name(cllees) == make_callee_list_tag) {
      if (no(cllees) == 0)
	trad_call = 1;
    }
    else if (name(cllees) == make_dynamic_callee_tag) {
      if (name(bro(son(cllees))) == val_tag && no(bro(son(cllees))) == 0)
	trad_call = 1;
    }
    else {	/* same callees */
      if (!May_have_callees)
	trad_call = 1;
    }
  }

  if (!trad_call)
   (void)make_code(cllees,nsp,nowhere,0);

  if (!reg_res && !void_result) {
    /* structure result */
        instore is;
    baseoff stack_struct_ret_addr;

    /* [%sp+64] as per call convention */
    stack_struct_ret_addr.base = R_SP;
    stack_struct_ret_addr.offset = (16 * 4);

    assert(discrim(dest.answhere) == notinreg);
    if(discrim(dest.answhere) != notinreg){	/* should be redundant */
      discrim(dest.answhere) = notinreg;
      is.b.base = R_SP;
      is.b.offset = (4*16);
      /* is.b = mem_temp(0);   not compatible with out_pars */
      is.adval = 1;
      dest.answhere.val.instoreans = is;
    }
    else{
      is = insalt(dest.answhere);
    }
    if (is.adval) {
      /* generate address of dest */
      if (IS_FIXREG(is.b.base)) {
	if (is.b.offset == 0) {
	  st_ro_ins(i_st, is.b.base, stack_struct_ret_addr);
	}
	else {
	  rir_ins(i_add, is.b.base, is.b.offset, R_TMP);
	  st_ro_ins(i_st, R_TMP, stack_struct_ret_addr);
	}
	guarded_dest_reg = is.b.base ;	/* can be guarded */
      }
      else {
	set_ins(is.b, R_TMP);
	st_ro_ins(i_st, R_TMP, stack_struct_ret_addr);
      }
    }
    else {
      /* load dest */
      ld_ins(i_ld, is.b, R_TMP);
      st_ro_ins(i_st, R_TMP, stack_struct_ret_addr);
    }
  }


  if ((gencompat && !trad_call) || !gencompat) {
    /*rr_ins(i_mov,callee_start_reg,R_O5);*/
    nsp = guardreg(R_O5,nsp);
    if (call_has_vcallees(cllees)) {
      /*rr_ins(i_mov,callee_end_reg,R_O4);*/
      nsp = guardreg(R_O4,nsp);
    }
  }

  if (no(callers)!= 0) {
    int tmp = in_general_proc;
    in_general_proc = 1;
    vc_call = (call_has_vcallees(cllees)!=0);
    nsp = do_callers(son(callers),nsp,&param_reg, trad_call);
    vc_call = 0;
    in_general_proc = tmp;
  }
  call_base_reg = R_SP;

  if (name(fn) == name_tag && name(son(fn)) == ident_tag &&
      (son(son(fn)) == NULL ||
	(name(son(son(fn))) == proc_tag ||
	  name(son(son(fn))) == general_proc_tag))) {
    baseoff b;
    b = boff(son(fn));
    if (!tlrecurse) {
      /* don't tell the assembler how many parameters are being used, as
	 it optimises away changes to "unused" parameter registers which,
	 in general procs, are needed to pass callees.
	 */
#ifdef NEWDWARF
      if (current_dg_info) {
	current_dg_info->data.i_call.brk = set_dw_text_label();
	current_dg_info->data.i_call.p.k = WH_CODELAB;
	current_dg_info->data.i_call.p.u.l = b.base;
	current_dg_info->data.i_call.p.o = b.offset;
      }
#endif
      extj_ins(i_call,b,-1 /*param_regs_used*/);
    }
    else{
      assert(!tlrecurse);
    }
  }
  else{
    int r = reg_operand(fn,nsp);
#ifdef NEWDWARF
    if (current_dg_info) {
      current_dg_info->data.i_call.brk = set_dw_text_label();
      current_dg_info->data.i_call.p.k = WH_REG;
      current_dg_info->data.i_call.p.u.l = r;
    }
#endif
    extj_reg_ins(i_call,r,-1 /*param_regs_used*/);
  }
  if (!reg_res && !void_result) {
    /* Generate unimp instruction, as per structure result call
	   convention.  Argument is low-order 12 bits of structure size,
	   see section D.4 of * SPARC architecture manual */
    unimp_ins((long)((ansash.ashsize / 8) & 0xfff));
  }

#ifdef NEWDWARF
  if (diag == DIAG_DWARF2)
    START_BB();
#endif

  /* free the space used to generate the callee parameters and, if in
     a postlude, move the caller outpars up the stack to a correct parameter
     offset from the new stack pointer */

  clear_all();
  {
    int size_reg;
    space nsp;
    nsp = guardreg(R_O0,sp);
    if ((gencompat && trad_call) || !gencompat)
      size_reg = R_NO_REG;
    else {
      if (name(cllees) == make_callee_list_tag) {
	size_reg = getreg(nsp.fixed);
	ir_ins(i_mov,((no(cllees) >>3) +23) &~7,size_reg);
      }
      else if (name(cllees) == make_dynamic_callee_tag) {
	size_reg = reg_operand(bro(son(cllees)),nsp);
	rir_ins(i_add,size_reg,4*(PTR_SZ>>3) +7,size_reg);
	rir_ins(i_and,size_reg,~7,size_reg);
      }
      else {	/* same callees */
	size_reg = getreg(nsp.fixed);
	if (Has_vcallees) {
	  rrr_ins(i_sub,callee_end_reg,callee_start_reg,size_reg);
	}
	else {
	  ir_ins(i_mov,proc_state.callee_size/8,size_reg);
	}
      }
      nsp = guardreg(size_reg,nsp);
    }
    if(no(callers)/* && (in_postlude || postlude_has_call(e))*/) {
      move_parameters(callers,size_reg,nsp); /* move all outpars into
						    correct positions */
    }
    if (!call_is_untidy(cllees) && size_reg != R_NO_REG) {
      if (!sysV_assembler) {
	/* with -O2 SunOS removes [add %sp,X,%sp] statements. */
	outs("\t.optim\t\"-O0\"\n");
      }
      rrr_ins(i_add,R_SP,size_reg,R_SP);
    }
  }



  /* grab clobbered %g and %o regs, as safety test for bad code */
  {
    int r;
    space gsp;
    gsp = sp;

    /* %g1..%g_reg_max, %o0..%o7 */
    for (r = R_G1; r < R_O7 + 1;
		     r = ((r == R_G0 + g_reg_max)? R_O0 : r + 1)) {
      /* skip R_O0 as often used in result-reg optimisation */
      if (!(r == R_TMP || r == R_O0 || r == R_SP ||
	      r == guarded_dest_reg)) {
	/* not special regs */
	gsp = needreg(r, gsp);
      }
    }
  }
  clear_all () ;	/* ??? not %i0..%l7 that may be t-regs */

  if (reg_res) {
    ans aa;
    if (is_floating(hda)) {
      freg frg;
      frg.fr = 0;
      frg.dble = (bool)(hda != shrealhd);
      setfregalt(aa, frg);
      /* move floating point result of application to destination */
     (void)move(aa, dest, sp.fixed, 1);
    } else {
      setregalt(aa, R_O0);
      if (discrim(dest.answhere) == inreg) {
	int r = regalt(dest.answhere);
	if (r == R_G0) {
	  /* void result */
	}
	else if (r != R_O0) {
	  /* move result from %o0 */
	 (void)move(aa, dest, sp.fixed, 1);
	}
	else {
	  /* no move required */
	  assert(name(postlude) == top_tag);
	}
	mka.regmove = R_O0;
      }
      else {
	(void)move(aa, dest, sp.fixed, 1);
      }
    }
  }
  else {
    /* not register result */
  }
#if 0
  if (Has_vcallees) {
    baseoff b;
    b.base = R_FP;
    b.offset = -3 *(PTR_SZ>>3);
    ld_ro_ins(i_ld,b,local_reg);
  }
#endif

  if (call_is_untidy(cllees)) {
    /*    rir_ins(i_sub,R_SP,proc_state.maxargs>>3,R_SP);*/
    /*assert(name(bro(cllees)) == top_tag);*/
  }
  else if (postlude_has_call(e)) {
    exp x = son(callers);
    postlude_chain p;

    if (x != NULL) {
      for (;;) {
	if (name(x) == caller_tag) {
	  no(x) += proc_state.maxargs;
#if 0
	  if (name(sh(x)) == realhd) {
	    no(x) -=32;
	  }
#endif
	}
	if (last(x))break;
	x = bro(x);
      }
    }
    mka.regmove = NOREG;
    update_plc(old_postludes,proc_state.maxargs);
    p.postlude = postlude;
    p.outer = old_postludes;
    old_postludes = &p;
    rir_ins(i_sub,R_SP,proc_state.maxargs>>3,R_SP);

    in_postlude = 1;
   (void)make_code(postlude,sp,nowhere,0);
    in_postlude = 0;
    rir_ins(i_add,R_SP,proc_state.maxargs>>3,R_SP);
    old_postludes = p.outer;
    update_plc(old_postludes,-proc_state.maxargs);
  }
  else {
   (void)make_code(postlude,sp,nowhere,0);
  }

  return mka;
}


/*
  Allocate an amount of space on the stack corresponding to the value
  held in register size_reg, and store a pointer to the resulting area
  in register ptr_reg.
*/
static void alloc_reg_space
(int size_reg, int ptr_reg) {

  int maxargbytes = (int)proc_state.maxargs/8;
  rir_ins(i_add,size_reg,7,R_TMP);
  rir_ins(i_and,R_TMP,~7,R_TMP);      /* make the size a multiple of 8 */
  rrr_ins(i_sub,R_SP,R_TMP,R_SP);
  rir_ins(i_add,R_SP,maxargbytes,ptr_reg);
  return;
}


/*
   As alloc_reg_space, but with a constant size.
*/
static void alloc_space
(int size, int ptr_reg) {
  int maxargbytes = (int)proc_state.maxargs/8;
  size = (size+7) &~7;
  rir_ins(i_sub,R_SP,size,R_SP);
  rir_ins(i_add,R_SP,maxargbytes,ptr_reg);
  return;
}


makeans make_make_callee_list_tag
(exp e, space sp, where dest, int exitlab) {
  int size = ((no(e) >>3) + 23) &~7;
  makeans mka;
  bool vc = call_has_vcallees(e);
  exp list = son(e);
  where w;
  instore is;
  baseoff b;
  int disp = 0;
  ash ap;
  space nsp;
  int rdest;

  nsp = guardreg(R_O5,sp);
  nsp = guardreg(R_O4,nsp);
  mka.regmove = R_G0;
  mka.lab = 0;
  /* perform an alloca */
  call_base_reg = getreg((nsp.fixed|PARAM_TREGS));
  nsp = guardreg(call_base_reg,nsp);
  rr_ins(i_mov,R_SP,call_base_reg);
  rdest  = getreg(nsp.fixed);
  nsp = guardreg(rdest,nsp);
  alloc_space(size,rdest); /* */

  b.base = rdest;
  b.offset = size - (PTR_SZ>>3);
  st_ro_ins(i_st,R_FP,b);
  if (no(e)) {
    int lastpar = 0;
    for (;!lastpar;list = bro(list)) {
      ap = ashof(sh(list));
      disp = rounder(disp,ap.ashalign);
      is.b.offset = disp>>3;
      is.b.base = rdest;
      is.adval = 1;
      w.ashwhere = ap;
      setinsalt(w.answhere,is);
      code_here(list,guard(w,nsp),w);
      disp = rounder(disp+ap.ashsize,PTR_SZ);
      lastpar = last(list);
    }
  }
  rr_ins(i_mov,rdest,callee_start_reg_out);/* Not before, as the construction
					      of the callees may require that
					      we access some of the old
					      callees */
  if (vc) {
    rir_ins(i_add,callee_start_reg_out,size,callee_end_reg_out);
    /*rir_ins(i_add,R_FP,size,R_FP);*/
  }
  return mka;
}



/*
  Construct a copy of the current callees for use in a new procedure
  call.  This writes the callee pointer(s) to the output registers o4 and
  o5, so a tail call will have to copy back to i4,i5.
*/
makeans make_same_callees_tag
(exp e, space sp, where dest, int exitlab) {
  baseoff b;
  bool vc = call_has_vcallees(e);
  makeans mka;
  space nsp;
  mka.regmove = R_G0;
  if (Has_vcallees) {
    /* copy from [callee_start_reg ... callee_end_reg] into newly allocated
       area, then set callee_start reg to start of area and, if the call
       also has vcallees, set callee_end_reg to the end of the area.
       */
    int rsize; /* register to contain the size of the
				     callee parameters area */
    int rsrc,rdest;               /* registers containing pointers to where
				     to copy from and to */
    int rtmp;                     /* temporary register used in copying */

    int end_copy_lab = new_label();   /* marks end of copy loop */
    int start_copy_lab = new_label(); /* marks start of copy loop */
    nsp = guardreg(R_O4,sp);
    nsp = guardreg(R_O5,nsp);
    call_base_reg = getreg((nsp.fixed|PARAM_TREGS));
    nsp = guardreg(call_base_reg,sp);
    rsize = getreg(nsp.fixed);
    nsp = guardreg(rsize,sp);
    rsrc = getreg(nsp.fixed);
    nsp = guardreg(rsrc,nsp);
    rdest = getreg(nsp.fixed);
    nsp = guardreg(rdest,nsp);
    rrr_ins(i_sub,callee_end_reg,callee_start_reg,rsize);
    rr_ins(i_mov,R_SP,call_base_reg);
    alloc_reg_space(rsize,rdest); /* */
    rrr_ins(i_add,rdest,rsize,rdest);

    /* now do top-down copy of parameters */
    rir_ins(i_sub,callee_end_reg, 4*(PTR_SZ>>3), rsrc);
    rir_ins(i_sub,rdest, 4*(PTR_SZ>>3), rdest);
    /*condrr_ins(i_be,rdest,rsrc,end_copy_lab);*/
    set_label(start_copy_lab);
    b.base = rsrc;
    b.offset = - (PTR_SZ>>3);
    rtmp = getreg(nsp.fixed);
    ld_ro_ins(i_ld,b,rtmp);
    b.base = rdest;
    st_ro_ins(i_st,rtmp,b);
    rir_ins(i_sub,rsrc,PTR_SZ>>3,rsrc);
    rir_ins(i_sub,rdest,PTR_SZ>>3,rdest);
    condrr_ins(i_bne,rsrc,callee_start_reg,start_copy_lab);
    set_label(end_copy_lab);
    /* callee_start_reg will now be rdest */
    rr_ins(i_mov,rdest,callee_start_reg_out);

    if (vc) {
      rrr_ins(i_add,callee_start_reg_out,rsize,callee_end_reg_out);
    }
  }
  else {
    int size_of_callees = proc_state.callee_size/8;
    int rdest;
    int el;
    int rsrc;
    space nsp;
    int tmpreg;
    nsp = guardreg(R_O4,sp);
    nsp = guardreg(R_O5,nsp);
    call_base_reg = getreg((nsp.fixed|PARAM_TREGS));
    nsp = guardreg(call_base_reg,sp);
    rdest = getreg(nsp.fixed);
    nsp = guardreg(rdest,sp);
    tmpreg = getreg(nsp.fixed);
    nsp = guardreg(tmpreg,nsp);
    rr_ins(i_mov,R_SP,call_base_reg);
    alloc_space(size_of_callees,rdest); /* */
    b.base = rdest;
    b.offset = size_of_callees - (PTR_SZ>>3);
    st_ro_ins(i_st,R_FP,b);
    rsrc = getreg(nsp.fixed);
    rir_ins(i_add,callee_start_reg,size_of_callees,rsrc);
    /*rir_ins(i_add,rdest,size_of_callees,rdest);*/
    for (el= (size_of_callees-4*(PTR_SZ>>3));el>0;el-= (PTR_SZ>>3)) {
      b.base = rsrc;
      b.offset = el - size_of_callees - (PTR_SZ>>3);
      ld_ro_ins(i_ld,b,tmpreg);
      b.base = rdest;
      b.offset = el - (PTR_SZ>>3);
      st_ro_ins(i_st,tmpreg,b);
    }
    /* callee_start_reg will no be rdest */
    if (vc) {
      rir_ins(i_add,rdest,size_of_callees,callee_end_reg_out);
      /*rr_ins(i_mov,rdest,callee_end_reg_out);*/
    }
    rr_ins(i_mov,rdest,callee_start_reg_out);
    /*rir_ins(i_sub,rdest,size_of_callees,callee_start_reg_out);*/
  }
  return mka;
}


/*
   Produce code to dynamically construct a new set of callee params.  The
   parameters are placed in a specially allocated piece of the current stack,
   and pointed to by callee_start_reg and callee_end_reg.
*/
makeans make_make_dynamic_callee_tag
(exp e, space sp, where dest, int exitlab) {
  /* bool vc = call_has_vcallees(e); */
  int rptr,rsize,rdest,r_true_size;
  int copy_start_lab = new_label();
  int copy_end_lab = new_label();
  space nsp;
  baseoff b;
  makeans mka;
  mka.regmove = R_G0;
  mka.lab = exitlab;
  nsp = guardreg(R_O5,sp);
  nsp = guardreg(R_O4,nsp);
  call_base_reg = getreg((nsp.fixed|PARAM_TREGS));
  nsp = guardreg(call_base_reg,nsp);
  rptr = getreg(nsp.fixed);
  nsp = guardreg(rptr,nsp);
  load_reg(son(e),rptr,nsp);    /* rptr now contains a pointer to the start of
			       the callees */
  rsize = getreg(nsp.fixed);
  nsp = guardreg(rsize,nsp);
  load_reg(bro(son(e)),rsize,nsp); /* rsize now contains the size of the
				      callees */
  rdest = getreg(nsp.fixed);
  nsp = guardreg(rdest,nsp);
  r_true_size = getreg(nsp.fixed);
  nsp = guardreg(r_true_size,nsp);
  /*rdest = callee_start_reg_out;*/ /*getreg(nsp.fixed);*/
  rir_ins(i_add,rsize,4*(PTR_SZ>>3) +7,r_true_size);
  rir_ins(i_and,r_true_size,~7,r_true_size);
  rr_ins(i_mov,R_SP,call_base_reg);

  alloc_reg_space(r_true_size,rdest); /* */
  rrr_ins(i_add,rdest,r_true_size /*rsize*/,R_TMP);
  /*rrr_ins(i_sub,rdest,r_true_size,rdest);*/
  b.base = R_TMP;
  b.offset = - (PTR_SZ>>3);
  st_ro_ins(i_st,R_FP,b);
  rr_ins(i_mov,rdest,callee_start_reg_out);
  /*if(vc)*/ rr_ins(i_mov,R_TMP,callee_end_reg_out);

  /* Now copy from rptr to rdest */
  condrr_ins(i_ble,rsize,R_G0,copy_end_lab);  /* make shure size > 0 */
  b.offset = 0;
  set_label(copy_start_lab);
  b.base = rptr;
  ld_ro_ins(i_ld,b,R_TMP);
  b.base = rdest;
  st_ro_ins(i_st,R_TMP,b);
  rir_ins(i_add,rptr,PTR_SZ>>3,rptr);
  rir_ins(i_add,rdest,PTR_SZ>>3,rdest);
  rir_ins(i_sub,rsize,PTR_SZ>>3,rsize);
  condrr_ins(i_bgt,rsize,R_G0,copy_start_lab);
  set_label(copy_end_lab);
  return mka;
}




/*
  This generates code for a tail_call tag.  The target of the call MUST be
  a general proc.
*/
makeans make_tail_call_tag
(exp e, space sp, where dest, int exitlab) {
  exp fn = son(e);
  exp cllees = bro(fn);
  exp bdy = son(current_proc);
  space nsp;
  bool vc = call_has_vcallees(cllees);
  int callee_size = proc_state.callee_size;
  makeans mka;
  baseoff bproc;
  bool glob = ((name(fn) == name_tag) && (name(son(fn)) == ident_tag) &&
	      ((son(son(fn)) == NULL) || (name(son(son(fn))) == proc_tag)
		|| (name(son(son(fn))) == general_proc_tag)));
  bool trad_proc = 0;
  if (gencompat && !vc) {
    if (name(cllees) == make_callee_list_tag) {
      if (no(cllees) == 0)
	trad_proc = 1;
    }
    else if (name(cllees) == make_dynamic_callee_tag) {
      if (name(bro(son(cllees))) == val_tag && no(bro(son(cllees))) == 0)
	trad_proc = 1;
    }
    else {	/* same callees */
      if (!May_have_callees)
	trad_proc = 1;
    }
  }

  mka.lab = exitlab;
  mka.regmove = R_G0;
  nsp = sp;
  nsp.fixed |= PARAM_TREGS;
  if (name(cllees)!= same_callees_tag) {
    code_here(cllees,sp,nowhere);
  }
#ifndef NEWDIAGS
  for (;name(bdy) == diagnose_tag;bdy=son(bdy));
#endif

  while (name(bdy) == ident_tag && isparam(bdy)) {
    exp sbdy = son(bdy);
    baseoff b;
    b.base = R_FP;
    b.offset = (no(sbdy) >>3) + (proc_state.params_offset>>3);

    if (name(sbdy) == formal_callee_tag) {
      if ((props(bdy) & inanyreg)!=0) {
	b.offset -= (proc_state.callee_size>>3);
	if (isvar(bdy)) {
	  if (is_floating(name(sh(bdy)))) {
	    stf_ins(i_st,no(bdy)<<1,b); 	/* add case for long double */
	  }
	  else {
	    st_ro_ins(i_st,no(bdy),b);
	  }
	}
      }
    }
    else if (props(sbdy) == 0 && ((props(bdy) & inanyreg)!=0)) {
      /* move from reg to store */
      if (isvar(bdy)) {
	if (is_floating(name(sh(sbdy)))) {
	  stf_ins(i_stf,no(bdy) <<1,b);
	}
	else{
	  assert(IS_IN_REG(props(sbdy)));
/*	  props(sbdy) = (props(sbdy)-R_I0)+R_O0;*/
	  st_ro_ins(i_st,no(bdy),b);
	}
      }
    }
    else if (props(sbdy)!=0 && ((props(bdy) &inanyreg) == 0)) {
      /* move from store to reg */
      int par_reg = props(sbdy);
      int last_reg = (shape_size(sh(sbdy)) > 32 ? par_reg+1 : par_reg);
      int past_reg = ((trad_proc)? R_I5+1 :(vc)?R_I4:R_I5);
					  /* registers i4 & i5 are reserved
					       in general procs for handling
					       of callee parameters */
      assert(IS_IN_REG(par_reg));
/*    props(sbdy) = (props(sbdy)-R_I0)+R_O0;*/
      if ((last_param(bdy) && isvis(bdy) && !Has_no_vcallers)
		|| last_reg >= past_reg)
	last_reg = past_reg - 1;
      while (par_reg <= last_reg) {
	ld_ro_ins(i_ld,b,par_reg);
	++par_reg;
	b.offset += 4;
      }
    }
    else if (props(sbdy)!= 0 && (props(sbdy)!= no(bdy))) {
      if (is_floating(name(sh(sbdy)))) {
	freg fr;
	fr.fr = no(bdy);
	fr.dble = (name(sh(sbdy)) == realhd);
	stf_ins(i_st, fr.fr<<1, mem_temp(0));
	ld_ro_ins(i_ld, mem_temp(0), props(sbdy));
	if (fr.dble) {
	  stf_ins(i_st,(fr.fr << 1) + 1,
		    mem_temp(4));
	  ld_ro_ins(i_ld, mem_temp(4), props(sbdy) + 1);
	}
      }
      else{
	assert(IS_IN_REG(props(sbdy)));
/*	props(sbdy) = (props(sbdy)-R_I0)+R_O0;*/
	rr_ins(i_mov,no(bdy),props(sbdy));
      }
    }
    bdy = bro(sbdy);
  }

  bproc = boff(son(fn));
  assert(bproc.offset == 0);
  if ((gencompat && trad_proc)) {
    int r = getreg(nsp.fixed);
    if (glob) {
      set_ins(bproc,r);
    }
    else{
      load_reg(fn,r,nsp);
    }
    if (!sysV_assembler) {
	/* with -O2 SunOS corrupts unusual jmp/restore combination. */
      outs("\t.optim\t\"-O0\"\n");
    }
#ifdef NEWDWARF
    if (current_dg_info) {
	current_dg_info->data.i_lj.brk = set_dw_text_label();
	current_dg_info->data.i_lj.j.k = WH_REG;
	current_dg_info->data.i_lj.j.u.l = r;
    }
#endif
    extj_reg_ins_no_delay(i_jmp,r,-1);
    fprintf ( as_file, "\t%s\n", i_restore ) ;	/* delay slot */
#ifdef NEWDWARF
    if (diag == DIAG_DWARF2)
      count_ins(1);
#endif
  }
  else
  {
    bproc.offset = 12;
    if (name(cllees)!= same_callees_tag) {
      rr_ins(i_mov,callee_start_reg_out,callee_start_reg);
      if (vc)rr_ins(i_mov,callee_end_reg_out,callee_end_reg);
    }
    if (name(cllees) == same_callees_tag && (vc && !Has_vcallees)) {
      rir_ins(i_add,callee_start_reg,callee_size>>3,callee_end_reg);
    }

    {
      int r = getreg(nsp.fixed);
      if (glob) {
	set_ins(bproc,r);
#ifdef NEWDWARF
	if (current_dg_info) {
	  current_dg_info->data.i_lj.brk = set_dw_text_label();
	  current_dg_info->data.i_lj.j.k = WH_REG;
	  current_dg_info->data.i_lj.j.u.l = r;
	}
#endif
	extj_reg_ins(i_jmp,r,-1);
      }
      else{
	load_reg(fn,r,nsp);
	rir_ins(i_add,r,12,r);
#ifdef NEWDWARF
	if (current_dg_info) {
	  current_dg_info->data.i_lj.brk = set_dw_text_label();
	  current_dg_info->data.i_lj.j.k = WH_REG;
	  current_dg_info->data.i_lj.j.u.l = r;
	}
#endif
	extj_reg_ins(i_jmp,r,-1);
      }
    }
  }
  clear_all();
  return mka;
}


