/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <signal.h>
#include <stdio.h>

#include <shared/check.h>
#include <shared/error.h>
#include <shared/xalloc.h>

#include <local/ash.h>

#include <reader/exp.h>

#include <construct/installtypes.h>
#include <construct/ash.h>
#include <construct/reg_result.h>

#include <main/driver.h>
#include <main/flags.h>
#include <main/print.h>

#include "memtdf.h"
#include "codegen.h"
#include "geninst.h"
#include "translate.h"
#include "make_code.h"
#include "proc.h"
#include "stack.h"
#include "mem_copy.h"
#include "parameter.h"
#include "error.h"
#include "dynamic_init.h"
#include "stack.h"
#include "scan.h"
#include "localexpmacs.h"

space do_callers(int,exp,space);
void do_function_call(exp,space);
void do_general_function_call(exp,space);
makeans move_result_to_dest(exp,space,where,int);
void restore_callers(int);
void restore_callees(void);
static exp find_ote(exp,int);

typedef struct postl_ {exp pl; struct postl_ * outer; } postl_chain;
static postl_chain * old_pls;

void update_plc(postl_chain * ch, int ma)
{
	while (ch != NULL) {
	  exp pl= ch->pl;
	  while (name(pl) ==ident_tag && name(son(pl)) ==caller_name_tag) {
		no(pl) += (ma<<6);
		pl = bro(son(pl));
	  }
	  ch = ch->outer;
	}
}
/*
 * Temp location in stack frame callee param save area that can be used
 * in short instruction sequence, such as move between float and fixed regs.
 * Initialised at procedure prelude, for that procedure.
 */
baseoff mem_temp(int byte_offset)
{
  baseoff b;

  b.base = R_SP;
  b.offset = -8;

  /*
   * Only 2 words of temp allocated
   */
  assert(byte_offset >= 0 && byte_offset < 8);
  b.offset += byte_offset;

  return b;
}

/*
 * Implement -p option, by calling mcount with static location address as param.
 */
static void call_mcount(void)
{
  static int p_lab = 0;

  p_lab++;

  /* generate .toc entry */
  asm_printop(".toc");
  asm_printf( "T.P.%d:\t.tc\tP.%d[TC],P.%d\n", p_lab, p_lab, p_lab);

  /* mcount counter */
  asm_printop(".lcomm P.%d,%d", p_lab, 4);

  /* reset to default text segment */
  asm_printop(".csect [PR]");

  /* call mcount */
  asm_printop("%s %d,T.P.%d(%d)", get_instruction(i_l), R_FIRST_PARAM, p_lab, R_TOC);
#ifdef TDF_MCOUNT
  extj_special_ins(i_bl, ".TDF_mcount");
#else
  extj_special_ins(i_bl, ".mcount");
#endif
  clear_all();
}


/* is param ident e the last param, or for a proc no params? */
bool last_caller_param(exp e)
{
  exp next;

  assert(IS_A_PROC(e) || (name(e) == ident_tag && isparam(e)));
  /* Look at the body of the ident for another param */
  if (IS_A_PROC(e))
  {
    next = son(e);
  }
  else
  {
    next = bro(son(e));
  }

  /* Skip diagnose_tag which may be before next param */
  while (name(next) == diagnose_tag)
  {
    next = son(next);
  }

  if (name(next) == ident_tag
      && isparam(next)
      && name(son(next))!=formal_callee_tag)
  {
    return 0;			/* another caller param */
  }
  else
  {
    return 1;			/* anything else means e was last param */
  }
}

/*
 * The following functions generate code for various procedure related
 * constructs. They put the result in dest using t-regs given by sp.
 * If non-zero, exitlab is the label of where the code is to continue.
 * These functions are called by make_code(), the code selection switch.
 */

/* procedure definition */
void make_proc_tag_code(exp e, space sp)
{
  procrec *pr = &procrecs[no(e)];
  long pprops = pr->needsproc.propsneeds;

  clear_all();

  suspected_varargs = 0;

  old_pls = NULL;

  p_current = e;

  initialise_procedure(pr);

  generate_procedure_prologue();

  output_parameters(e);

  if (do_dynamic_init && proc_is_main(e))
  {
    call__main();
  }

  /*
   * Profiling info
   */
  if (do_profile && !p_leaf)
  {
	/*
	 * In the event of the procedure having no parameters,
	 * mcount would not have been called, so we call it here.
	 */
    call_mcount();
  }

  /*
   * Setup p_result
   */
  if ((pprops & realresult_bit) != 0)	/* proc has real result */
  {
    freg frg;

    frg.fr = FR_RESULT;
    frg.dble = (pprops & longrealresult_bit)? 1 : 0;
    setfregalt(p_result, frg);
  }
  else if ((pprops & has_result_bit)!= 0)
  {
    setregalt(p_result, R_RESULT);
  }
  else
  {
    setregalt(p_result, R_0);		/* no result */
  }
  p_return_label = 0;

  init_proc_errors(e);

  make_code(son(e), sp, nowhere, 0);

  output_error_labels();

  /* epilogue created at make_res_tag_code */
}


/* ident/param definition within proc */
makeans make_ident_tag_code(exp e, space sp, where dest, int exitlab)
{
  exp init_exp = son(e);			/* initialisation exp */
  int ident_size = shape_size(sh(init_exp));
  int ident_align = shape_align(sh(init_exp));
  int ident_no = no(e);
  where placew;
  int r = R_NO_REG;
  bool remember = 0;
  makeans mka;

  if (props(e) & defer_bit)
  {
    return make_code(bro(init_exp), sp, dest, exitlab);
  }

  /* Is it an identification of a caller in a postlude? */
  if (name(init_exp) ==caller_name_tag)
  {
    exp ote = find_ote(e,no(init_exp));
    long caller_disp = no(ote) >>3;

    no(e) = ENCODE_FOR_BOFF(caller_disp , OUTPUT_CALLER_PARAMETER);
    set_coded_caller(ote); /* Used in apply_general*/

    assert((props(e) & inanyreg) ==0);
    /* Should not have been allocated a register by regalloc or scan() */
    placew = nowhere;
  }
  /* Is it in a fixed point register? */
  else if (props(e) &inreg_bits)
  {
    if (ident_no==R_NO_REG)	/* Need to allocate a t-reg */
    {
      int s = sp.fixed;

      if (props(e) & notparreg)
      {
	s |= PARAM_TREGS;
      }
      if (props(e) & notresreg)
      {
	s |= RMASK(R_RESULT);
      }
      ident_no = getreg(s);
      no(e) = ident_no;
    }
    setregalt(placew.answhere,ident_no);
  }
  /* Is it in a floating point register? */
  else if (props(e) & infreg_bits)
  {
    freg frg;
    if (ident_no==FR_NO_REG)	/* Need to allocate a t-reg */
    {
      int s = sp.flt;

      if (props(e) & notparreg)
      {
	s |= PARAM_FLT_TREGS;
      }
      if (props(e) & notresreg)
      {
	s |= RMASK(FR_RESULT);
      }
      ident_no = getfreg(s);
      no(e) = ident_no;
    }
    frg.fr = ident_no;
    frg.dble = (ident_size==64);
    setfregalt(placew.answhere, frg);
  }
  /* Is it a parameter on the stack? */
  else if (isparam(e))
  {
    instore is;

    if (name(init_exp)!= formal_callee_tag)
    {
      /* Caller parameter living on stack */
      long caller_offset = no(init_exp) >>3;
      no(e) = ENCODE_FOR_BOFF(caller_offset , INPUT_CALLER_PARAMETER);
      if (isvarargparam(e))
      {
	if (ident_size == 0)
	{
	  /* void from <varargs.h> */
	  ident_size = 32;
	  ident_align = 32;
	}
      }
    }
    else
    {
      /* Callee parameter living on stack */
      long callee_offset = no(init_exp) >>3;
      no(e) = ENCODE_FOR_BOFF(callee_offset , INPUT_CALLEE_PARAMETER);
    }
    is.b = boff(e);
    is.adval = 1;
    setinsalt(placew.answhere, is);
  }
  /* Allocate on the stack? */
  else
  {
    /* It is a local living on the stack */
    instore is;

    is.b = boff(e);
    is.adval = 1;
    setinsalt(placew.answhere, is);
    remember = 1;
  }

  placew.ashwhere.ashsize  = ident_size;
  placew.ashwhere.ashalign = ident_align;

  if (isparam(e))
  {
    if (name(init_exp) ==formal_callee_tag && (props(e) & inanyreg))
    {
      instore is;
      ans aa;
      assert(p_has_fp);
      is.b.base = R_FP;
      is.b.offset = EXTRA_CALLEE_BYTES + (no(init_exp) >>3);
      is.adval = 0;
      setinsalt(aa,is);
      move(aa,placew,sp.fixed,is_signed(sh(init_exp)));
    }
  }
  else
  {
    r = code_here(init_exp, sp, placew);
  }

  asm_comment("make_ident_tag_code end_init: no(e) =%d", no(e));

  if (remember && r != R_NO_REG && pt(e)!= NULL
      && keep_eq_size(sh(init_exp), sh(pt(e))))
  {
    /* It was temporarily in a register, track it to optimise future access */
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
  mka = make_code(bro(init_exp), guard(placew, sp), dest, exitlab);

  asm_comment("make_ident_tag_code end_range: no(e) =%d", no(e));

  return mka;
}

/*
 * Delivers the procedure result with either a normal or an untidy return
 */
void make_res_tag_code(exp e, space sp)
{
  where w;
  bool untidy = (name(e) ==untidy_return_tag)? 1 : 0;

  w.answhere = p_result;
  w.ashwhere = ashof(sh(son(e)));

  code_here(son(e), sp, w);	/* Evaluation of result value */


  if (p_leaf
      && p_sreg_first_save == R_NO_REG
      && p_sfreg_first_save == FR_NO_REG)
  {
    /* Short return sequence so generate everytime */
    if (untidy)
    {
      generate_untidy_procedure_epilogue();
    }
    else
    {
      generate_procedure_epilogue();
    }
  }
  else
  {
    /* jump to the end of proc for long return sequence */
    if (p_return_label == 0)
    {
      /* For diagnostics always produce return code */
      if (p_no_of_returns>1 && diag == DIAG_NONE)
      {
	p_return_label = new_label();
	set_label(p_return_label);
      }
      if (untidy)
      {
	generate_untidy_procedure_epilogue();
      }
      else
      {
	generate_procedure_epilogue();
      }
    }
    else
    {
      /* jump to the return sequence at first return */
      uncond_ins(i_b, p_return_label);
    }
  }

  clear_all();
}


/* procedure call */
makeans make_apply_tag_code(exp e, space sp, where dest, int exitlab)
{
  exp fn = son(e);		/* Function */
  exp par = bro(fn);		/* Parameters list */
  space nsp;
  nsp=sp;

  /* Structure results are assumed to be transformed */
  assert(redo_structfns);
/* XXX: assertion fails
  assert(reg_result(sh(e)));
*/

  /* Callers evaluated to usual place relative to sp */
  if (!last(fn)) {nsp = do_callers(PROC_PARAM_REGS,par,nsp);}

  /* Function call */
 (void) do_function_call(fn,nsp);

  /* Clear all treg associations */
  clear_all();

  /* Move the result to correct destination */
  return move_result_to_dest(e,sp,dest,exitlab);
}

makeans make_apply_general_tag_code(exp e, space sp, where dest, int exitlab)
{
  exp fn = son(e);
  exp cers = bro(fn);
  exp cees = bro(cers);
  exp pl = bro(cees);
  space nsp;
  makeans mka;
  nsp = sp;

  /* Callers evaluated to usual place relative to sp */
  /* Any params with caller_tag are marked with offset */
  if (no(cers)!=0) { nsp = do_callers(GENERAL_PROC_PARAM_REGS,son(cers),sp);}

  /* Callees */
 (void)make_code(cees,nsp,nowhere,0);

  /* Function */
 (void) do_general_function_call(fn,nsp);


  /*
   * This code works on the assumption that the stack pointer is returned
   * to where it was initially. i.e no untidy returns from the general_proc.
   *
   * The postlude also works on the assumption that no calls to alloca are
   * done within it.
   */

  /* clear all register associations */
  clear_all();

  /* move the result to the destination */
  mka = move_result_to_dest(e,sp,dest,exitlab);

  /*
   * Possibility here that the function is untidy. In this case we must
   * ensure that there is room to construct subsequent parameter lists
   * within this procedure. The only way to guarantee this is to pull down
   * the stack pointer by an extra p_args_and_link_size
   */
  if (call_is_untidy(cees))
  {
    rir_ins(i_a,R_SP,-p_args_and_link_size,R_SP);
    if (p_has_saved_sp)
    {
      save_sp_on_stack();
    }
  }

  if (postlude_has_call(e))
  {
    exp x = son(cers);
    postl_chain p;
    for (;x != NULL;)
    {
      if (name(x) ==caller_tag)
      {
	no(x) += p_args_and_link_size<<3;
      }
      if (last(x))
      {
	break;
      }
      x=bro(x);
    }
    update_plc(old_pls, p_args_and_link_size);
    p.pl = pl;
    p.outer = old_pls;
    old_pls = &p;

    rir_ins(i_a,R_SP,-p_args_and_link_size,R_SP);
   (void)make_code(pl,sp,nowhere,0);
    rir_ins(i_a,R_SP,p_args_and_link_size,R_SP);

    old_pls = p.outer;
    update_plc(old_pls, -p_args_and_link_size);
    mka.regmove = R_NO_REG; /* The result reg is corrupted */
  }
  else
  {
   (void)make_code(pl,sp,nowhere,0);
  }
  return mka;
}
void make_return_to_label_tag_code(exp e, space sp)
{
  int r = reg_operand(son(e),sp);

  mt_ins(i_mtlr,r);
  /* See generate_procedure_epilogue in stack.c for similarity */
  if (p_frame_size != 0)
  {
    if (p_has_fp)
    {
      /* Use the frame pointer to collapse the frame */
      mov_rr_ins(R_FP,R_SP);asm_comment("collapse frame using FP");
    }
    else if (p_has_back_chain)
    {
      /* Use the back chain to collapse the stack frame */
      baseoff back_chain;
      back_chain.base = R_SP;
      back_chain.offset = 0;
      ld_ro_ins(i_l, back_chain, R_SP);asm_comment("collapse frame using back chain");
    }
    else
    {
      /* Use the frame size to collapse the stack frame */
      rir_ins(i_a,R_SP,p_frame_size, R_SP);
    }
  }
  /* At this point the stack pointer is collapsed to where the s-regs are
     stored */
  if (p_has_tp)
  {
    mov_rr_ins(R_TP,R_TEMP_TP);asm_comment("copy TP to TEMP_TP");
    restore_sregs(R_SP,0);
    mov_rr_ins(R_TEMP_TP,R_SP);asm_comment("collapse frame using TEMP_TP");
  }
  else
  {
    restore_sregs(R_SP,0);
  }
  /* At this point the stack pointer is in its return position */
  /* Now we move r to the link register */

  z_ins(i_br);
}

void make_tail_call_tag_code(exp e, space sp)
{
  exp fn =son(e);
  exp cees = bro(fn);
  baseoff callee_pointer;
  bool direct_call = (name(fn) == name_tag
		      && name(son(fn)) == ident_tag
		      && (son(son(fn)) == NULL || IS_A_PROC(son(son(fn)))));
  static int identification = 0;
  identification++;
  asm_printf("# Begin tail call no %d\n",identification);


  callee_pointer.base = R_SP;
  callee_pointer.offset = 0;
  assert(p_has_fp);


  if (name(cees) ==make_callee_list_tag || name(cees) ==make_dynamic_callee_tag)
  {
    /* +++ This is a bit of a long winded way to do the tail call for
       make_dynamic_callee_tag since the callees are copied twice. */
    code_here(cees,sp,nowhere);
    if (direct_call==0)
    {
      /* dynamic call */
      int desc_base = reg_operand(fn,sp);
      baseoff b;

      b.base = desc_base;
      b.offset = 0;
      ld_ro_ins(i_l,b,R_TMP0);
      b.base = R_SP;
      b.offset = 4;
      st_ro_ins(i_st,R_TMP0,b);
    }
    restore_link_register();
    restore_callers(GENERAL_PROC_PARAM_REGS);
    /* Set up R_TEMP_TP and R_TEMP_FP */
    if (p_has_tp)
    {
      mov_rr_ins(R_TP,R_TEMP_TP);asm_comment("copy TP to TEMP_TP");
    }
    else
    {
      /* This only happens with a tail call in a normal proc */
      mov_rr_ins(R_FP,R_TEMP_TP);asm_comment("copy FP to TEMP_TP");
    }
    mov_rr_ins(R_FP,R_TEMP_FP);asm_comment("copy FP to TEMP_FP");
    restore_sregs(R_TEMP_FP,0);

    /* At this point R_TP is R_TEMP_TP and R_FP is R_TEMP_FP */

    /* Pull down R_TEMP_TP by the size of the callees */
    if (name(cees) ==make_callee_list_tag)
    {
      int size_of_callee_list=ALIGNNEXT((no(cees) >>3) +EXTRA_CALLEE_BYTES , 8);
      st_ro_ins(i_st,R_TEMP_TP,callee_pointer);

      mov_rr_ins(R_SP,R_TEMP_FP);
      rir_ins(i_a,R_TEMP_TP,- (long)(size_of_callee_list),R_TEMP_TP);
      reverse_static_memory_copy(R_TEMP_FP,R_TEMP_TP,size_of_callee_list);
      mov_rr_ins(R_TEMP_TP,R_SP);
    }
    else
    {

      ld_ro_ins(i_l,callee_pointer,R_TMP0);
      rrr_ins(i_s,R_TMP0,R_SP,R_TMP0);
      /* R_TMP0 should now contain the callee size */
      st_ro_ins(i_st,R_TEMP_TP,callee_pointer);
      rrr_ins(i_s,R_TEMP_TP,R_TMP0,R_TEMP_TP);
      mov_rr_ins(R_SP,R_TEMP_FP);
      reverse_dynamic_word_memory_copy(R_TEMP_FP,R_TEMP_TP,R_TMP0);
      mov_rr_ins(R_TEMP_TP,R_SP);
    }
    /* The memory copy does not corrupt R_TEMP_TP or R_TEMP_FP */
    /* Finally put the stack pointer at the bottom of the callees */

  }
  else if (name(cees) ==same_callees_tag)
  {
    if (name(p_current) ==general_proc_tag)
    {
      if (direct_call ==0)
      {
	/* dynamic call */
	int desc_base = reg_operand(fn,sp);
	baseoff b;

	b.base = desc_base;
	b.offset = 0;
	ld_ro_ins(i_l,b,R_TMP0);
	b.base = R_FP;
	b.offset = 4;
	st_ro_ins(i_st,R_TMP0,b);
      }
      restore_link_register();
      restore_callees();
      restore_callers(GENERAL_PROC_PARAM_REGS);
      mov_rr_ins(R_FP,R_TEMP_FP);asm_comment("copy FP to TEMP_FP");
      restore_sregs(R_TEMP_FP,0);
      mov_rr_ins(R_TEMP_FP,R_SP);asm_comment("collapse frame using TEMP_FP");
    }
    else
    {
      /* This should only occur in the initialisation required for dynamic
	 initialisation of globals as required for c++ */
      assert(p_has_fp);
      restore_link_register();
      restore_callers(PROC_PARAM_REGS);
      mov_rr_ins(R_FP,R_TEMP_FP);asm_comment("copy FP to TEMP_FP");
      restore_sregs(R_TEMP_FP,0);
      mov_rr_ins(R_TEMP_FP,R_SP);asm_comment("collapse frame using TEMP_FP");
    }
  }

  /* Function */
  if (direct_call)
  {
    baseoff b;
    b = boff(son(fn));
    extj_ins(i_b, b);
    /* Link register is set up to be the previous stack frames */
  }
  else
  {
    /* Link register is set up to be the previous stack frames */
    /* Count register is set up to be the target address */
    baseoff b;
    b.base = R_SP;
    b.offset = 4;
    ld_ro_ins(i_l,b,R_TMP0);
    mt_ins(i_mtctr,R_TMP0);
    z_ins(i_bctr);
  }
  asm_printf("# End tail call no %d\n",identification);
}

void make_same_callees_tag_code(exp e, space sp)
{
  int roldsp;
  int rfrom;
  int rto;
  space nsp;
  baseoff callee_pointer;
  nsp = sp;
  callee_pointer.base = R_SP;
  callee_pointer.offset = 0;

  UNUSED(e);

  assert(name(p_current) ==general_proc_tag);

  rfrom = getreg(nsp.fixed);nsp = guardreg(rfrom,nsp);
  rto = getreg(nsp.fixed);nsp = guardreg(rto,nsp);
  roldsp = getreg(nsp.fixed);nsp = guardreg(roldsp,nsp);

  restore_callees();
  mov_rr_ins(R_FP,rfrom);
  mov_rr_ins(R_SP,roldsp);

  if (p_has_vcallees)
  {
	/*
	 * We use the difference between R_TP and R_FP to calculate the size
	 * of the vcallees and then pulls the stack pointer down by this amount
	 * and copies the callees onto the bottom of the stack.
	 *
	 * Finally it sets up the callee pointer which points to the top of
	 * the newly constructed callee list.
	 */
    int rsize;
    rsize = getreg(nsp.fixed);nsp = guardreg(rsize,nsp);


    rrr_ins(i_s,R_TP,R_FP,rsize);
    rrr_ins(i_s,R_SP,rsize,R_SP);
    mov_rr_ins(R_SP,rto);

    dynamic_word_memory_copy(rfrom,rto,rsize); /* copy the callees */
  }
  else
  {
    /* We can do slightly better since we know the size of the callees */
    long csize = ALIGNNEXT(p_callee_size + EXTRA_CALLEE_BYTES,8);

    rir_ins(i_a,R_SP,-csize,R_SP);
    mov_rr_ins(R_SP,rto);
    static_memory_copy(rfrom,rto,csize);
  }
  st_ro_ins(i_st,roldsp,callee_pointer);
}




void make_callee_list_tag_code(exp e, space sp)
{
  long x;
  exp list = son(e);
  long disp;
  where w;
  instore is;
  baseoff new_stackpos;

	/*
	 * This is an explicit creation of the callee list on the bottom of
	 * the stack. no(e) contains the total size in bits required to create
	 * the callee list. The EXTRA_CALLEE_BYTES are the bytes needed to
	 * store the extra info on the bottom of the callee list.
	 * At present only 4 bytes are required to hold a pointer which
	 * points to the top of the list.
	 */

  x = ALIGNNEXT((no(e) >>3) + EXTRA_CALLEE_BYTES  , 8);
  new_stackpos.base = R_SP;
  new_stackpos.offset = -x;
  st_ro_ins(i_stu , R_SP , new_stackpos);

  disp = EXTRA_CALLEE_BYTES * 8;/* start coding them here */
  update_plc(old_pls,x);
  if (no(e)!=0)
  {
    for (;;)
    {
      ash ap;

      ap = ashof(sh(list));
      disp = ALIGNNEXT(disp, ap.ashalign);
      is.b.offset = disp>>3;
      is.b.base = R_SP;
      is.adval = 1;
      w.ashwhere = ap;
      setinsalt(w.answhere,is);
      code_here(list,sp,w);
      disp = ALIGNNEXT(disp + ap.ashsize,32);
      if (last(list))
	break;
      list = bro(list);
    }
  }
  update_plc(old_pls,-x);
}

void make_dynamic_callee_tag_code(exp e, space sp)
{
  int rfrom;
  int rto;
  int rsize;
  int rsize_adjusted;
  baseoff callee_pointer;
  space nsp;

  callee_pointer.base = R_SP;
  callee_pointer.offset = 0;

  rfrom = reg_operand(son(e),sp);nsp = guardreg(rfrom,sp);
  rsize = reg_operand(bro(son(e)),nsp);nsp = guardreg(rsize,nsp);
  if (al2(sh(bro(son(e)))) < 32)
  {	/* shouldn't happen for correct ANDF? */
    rir_ins(i_a, rsize, 3, rsize);
    rir_ins(i_and, rsize, ~3, rsize);
  }

  rto = getreg(nsp.fixed);nsp = guardreg(rto,nsp);
  rsize_adjusted = getreg(nsp.fixed);nsp = guardreg(rsize_adjusted,nsp);


  rir_ins(i_a,rsize , EXTRA_CALLEE_BYTES + 7 , rsize_adjusted);
  rir_ins(i_and ,rsize_adjusted ,~7 , rsize_adjusted);
  /* Pull down the stack frame by rsize_adjusted bytes */
  rrr_ins(i_s, R_SP, rsize_adjusted , R_SP);

  rir_ins(i_a, R_SP , EXTRA_CALLEE_BYTES , rto); /* copy to here */
  /* copy rsize bytes from rfrom to rto */
  /* +++ Can we do this word at a time */

  reverse_dynamic_word_memory_copy(rfrom,rto,rsize);
  /* the memory copy preserves rfrom,rto and rsize */
  rrr_ins(i_a,rsize_adjusted,R_SP,R_TMP0);
  st_ro_ins(i_st,R_TMP0,callee_pointer);
}

space do_callers(int n, exp list, space sp)
{
	/*
	 * Evaluates parameters into fixed registers or float registers or stack
	 * according to the calling convention.
	 */
  int disp = 0;
  int param_reg = R_FIRST_PARAM;
  int last_param_reg = R_FIRST_PARAM;
  int fr_param_reg = FR_FIRST_PARAM;
  space nsp;
  int final_param = n + R_FIRST_PARAM - 1;
  nsp =sp;

  for (;;)
  {
    exp par = name(list) ==caller_tag ?son(list):list;
    shape par_shape = sh(par);
    ash ap;
    where w;
    ap = ashof(sh(par));
    w.ashwhere = ap;

    if (is_floating(name(par_shape)) && param_reg <= final_param)
    {
      bool dble = is_double_precision(par_shape);
      instore is;
      freg frg;

      is.b = boff_location(ENCODE_FOR_BOFF((disp>>3),OUTPUT_CALLER_PARAMETER));
      is.adval = 1;

      frg.fr= (fr_param_reg<=FR_LAST_PARAM?fr_param_reg:getfreg(nsp.flt));
      frg.dble = dble;
      setfregalt(w.answhere, frg);

	/*
	 * The floating parameter is evaluated into a floating parameter t-reg
	 * (If we have not filled them all up ) else a spare t-reg.
	 */
      code_here(par, nsp, w);

      if (frg.fr == fr_param_reg)
      {
	/*
	 * The floatind paramter is in a floating parameter t-reg so we must guard it
	 */
	nsp = guardfreg(frg.fr, nsp);
      }
      /* Copy it onto the stack at its correct position */
      stf_ro_ins((dble ? i_stfd : i_stfs), frg.fr, is.b);

      /* load it into the fixed parameter t-reg */
      ld_ro_ins(i_l, is.b, param_reg);asm_comment("load float-param from stack into param reg");
      nsp = guardreg(param_reg, nsp);

      param_reg++;
      last_param_reg = param_reg;

      if (dble && param_reg <= final_param)
      {
	/* Double whose second half can be loaded into fixed param t-reg */
	is.b.offset += 4;
	ld_ro_ins(i_l, is.b, param_reg);asm_comment("it was a double so we load other half");
	nsp = guardreg(param_reg, nsp);
	param_reg++;
	last_param_reg = param_reg;
      }
      fr_param_reg++;
    }
    else if (valregable(sh(par)) && param_reg <= final_param)
    {
      /* valregable ensures that we can evaluate it into a register so we
	 evaluate it into a param_reg*/
      ans ansr;
      setregalt(ansr,param_reg);
      w.answhere = ansr;
      code_here(par,nsp,w);
      nsp = guardreg(param_reg, nsp);
      param_reg++;
      last_param_reg = param_reg;
    }
    else
    {
      /* stack parameter */
      int param_size = ap.ashsize;
      instore is;
      is.adval = 1;

      is.b= boff_location(ENCODE_FOR_BOFF((disp >> 3),OUTPUT_CALLER_PARAMETER));
      if (param_size == 0)
      {
	/* from fake <varargs.h> param, nothing to do */
	/* Could be something of shape top which needs evaluating */
	/* Fix for avs suite FlowControl/apply_proc*/
	code_here(par,sp,nowhere);
      }
      else if (is_floating(name(par_shape)))
      {
	freg frg;
	/* store floating parameter on the stack */
	frg.fr= (fr_param_reg<=FR_LAST_PARAM ? fr_param_reg : getfreg(nsp.flt));

	frg.dble = name(par_shape)!= shrealhd;
	setfregalt(w.answhere, frg);
	code_here(par, nsp, w);

	if (frg.fr == fr_param_reg)
	{
	  nsp = guardfreg(frg.fr, nsp);
	}

	stf_ro_ins((frg.dble ? i_stfd : i_stfs), frg.fr, is.b);

	fr_param_reg++;
      }
      else if (param_reg <= final_param)
      {
	/*
	 * By elimination it must be an aggregrate whose whole or part
	 * is to be passed in regs
	 */
	int last_ld_reg;
	int r;
	bool allinreg;
	int dolastoffset;

	last_ld_reg = param_reg + (ALIGNNEXT(param_size, 32) /32) - 1;
	if (last_ld_reg > final_param)
	{
	  last_ld_reg = final_param;
	  allinreg = 0;
	}
	else
	{
	  allinreg = 1;
	}

	if (allinreg && name(par) == cont_tag)
	{
	  /* a small simple ident, which we can load easily */
	  where w;
	  w = locate(par, nsp, sh(par), 0);

	  assert(w.answhere.discrim==notinreg);

	  is = insalt(w.answhere);

	  asm_comment("apply: simple aggregate parameter: adval=%d reg=%d off=%ld",
		   is.adval, is.b.base, is.b.offset);
	  assert(!is.adval);
	  /* it is already lying about */
	  if (!IS_FIXREG(is.b.base))
	  {
	    /* make addressable */
	    set_ins(is.b, last_ld_reg);
	    is.b.base = last_ld_reg;
	    is.b.offset = 0;
	  }

	}
	else
	{
	  /* evaluate aggregate to stack location for param, then move to regs */
	  /* +++ do better for aggregate passed partially in regs */
	  setinsalt(w.answhere, is);
	  /* Get that horrible thing written directly into the stack */
	  code_here(par, nsp, w);
	}

	/* now load as many regs as required */

	dolastoffset = -1;

	for (r = param_reg; r <= last_ld_reg; r++)
	{
	  if (r == is.b.base)
	  {
	    /* clash with base reg, do it later */
	    dolastoffset = is.b.offset;
	  }
	  else
	  {
	    ld_ro_ins(i_l, is.b, r);asm_comment("copy struct param from stack into param regs");
	  }

	  nsp = guardreg(r, nsp);
	  is.b.offset += 4;
	}

	if (dolastoffset != -1)
	{
	  /* do ld that clashed with base reg */
	  is.b.offset = dolastoffset;
	  ld_ro_ins(i_l, is.b, is.b.base);asm_comment("copy the last part of the structure due to clash of regs");
	}
      }
      else
      {
	setinsalt(w.answhere, is);
	code_here(par, nsp, w);
      }

      /* move param_reg on by size */
      param_reg += (param_size + 31) / 32;
    }

    if (name(list) ==caller_tag)
    {
      no(list) =disp;
    }

    if (last(list))
      break;
    list = bro(list);

    disp = ALIGNNEXT(disp + ap.ashsize, 32);
  }				/* end for */

  assert(last_param_reg >= R_FIRST_PARAM && last_param_reg <= final_param + 1);
  return nsp;

}
void do_function_call(exp fn, space sp)
{
  if (name(fn) == name_tag
      && name(son(fn)) == ident_tag
      && (son(son(fn)) == NULL || IS_A_PROC(son(son(fn))))
     )
  {
    /* direct call */
    baseoff b;
    b = boff(son(fn));
    extj_ins(i_bl, b);
  }
  else
  {
    /* proc ptr call */
    int desc_base = reg_operand(fn, sp);
    baseoff b;

    asm_comment("proc ptr call");

    b.base = desc_base;
    b.offset = 0;
    ld_ro_ins(i_l, b, R_TMP0);asm_comment("load function address to R_TMP0");
    mt_ins(i_mtlr, R_TMP0);
    /* +++ use scan() so we can do this in proc prelude */
    b.base = R_SP;
    b.offset = STACK_SAVED_TOC;
    st_ro_ins(i_st, R_TOC, b);asm_comment("save toc pointer for this function");
    b.base = desc_base;
    b.offset = 4;
    ld_ro_ins(i_l, b, R_TOC);asm_comment("load up toc pointer for function");
    /* +++ load env ptr from descriptor */
    z_ins(i_brl);
    b.base = R_SP;
    b.offset = STACK_SAVED_TOC;
    ld_ro_ins(i_l, b, R_TOC);asm_comment("restore toc pointer");
  }
}
void do_general_function_call(exp fn, space sp)
{
  if (name(fn) == name_tag
      && name(son(fn)) == ident_tag
      && (son(son(fn)) == NULL || IS_A_PROC(son(son(fn))))
     )
  {
    /* direct call */
    baseoff b;
    b = boff(son(fn));
    extj_ins(i_bl, b);
  }
  else
  {
    /* proc ptr call */
    int desc_base = reg_operand(fn, sp);
    baseoff b;
    baseoff saved_toc;
    int r;

    asm_comment("proc ptr call");
    r = getreg(guardreg(desc_base,sp).fixed);

    b.base = desc_base;
    b.offset = 0;
    ld_ro_ins(i_l, b, R_TMP0);asm_comment("load function address to R_TMP0");
    mt_ins(i_mtlr, R_TMP0);
    saved_toc.base = R_SP;
    saved_toc.offset = 0;
    ld_ro_ins(i_l , saved_toc ,r);asm_comment("load up top of callees");
    saved_toc.base = r;
    saved_toc.offset = STACK_SAVED_TOC;
    st_ro_ins(i_st, R_TOC, saved_toc);asm_comment("save toc pointer");
    b.base = desc_base;
    b.offset = 4;
    ld_ro_ins(i_l, b, R_TOC);asm_comment("load up toc pointer for function");
    /* +++ load env ptr from descriptor */
    z_ins(i_brl);
    /* on return from a general proc, R_SP is returned to top of callees */
    b.base = R_SP;
    b.offset = STACK_SAVED_TOC;
    ld_ro_ins(i_l, b, R_TOC);asm_comment("restore toc pointer");
  }
}
makeans move_result_to_dest(exp e, space sp, where dest, int exitlab)
{
  makeans mka;
  int hda = name(sh(e));	/* Shape of result */
  ans aa;
  mka.regmove=R_NO_REG;
  mka.lab = exitlab;

  /* move result of application to destination */
  if (is_floating(hda))
  {
    freg frg;

    frg.fr = FR_RESULT;
    frg.dble = (hda != shrealhd);
    setfregalt(aa, frg);
    asm_comment("apply: is_floating result, dble=%d", frg.dble);
    move(aa, dest, sp.fixed, 1);
  }
  else
  {
    setregalt(aa, R_RESULT);
    mka.regmove = R_RESULT;
    if (dest.answhere.discrim == inreg)
    {
      int r = regalt(dest.answhere);

      if (r == R_0)
      {
	asm_comment("apply: void result");
      }
      else if (r != R_RESULT)
      {
	asm_comment("apply: dest inreg, move from R_RESULT");
	move(aa, dest, sp.fixed, 1);
      }
      else
      {
	asm_comment("apply: dest R_RESULT, no move");
      }
    }
    else if (dest.answhere.discrim == insomereg)
    {
      int *dr = someregalt(dest.answhere);
      asm_comment("apply: dest insomereg set to R_RESULT");
      if (*dr != -1)
      {
	error(ERR_SERIOUS, "somereg been set up");
      }
      *dr = R_RESULT;
    }
    else
    {
      asm_comment("apply: dest not inreg or insomereg");
      move(aa, dest, sp.fixed, 1);
    }
  }
  return mka;
}
void restore_callers(int n)
{
  /* finds all the callers and puts them into there correct register */
  exp bdy = son(p_current);
  int final_param = n + R_FIRST_PARAM - 1;

  asm_comment("restore callers");
  while (name(bdy) ==diagnose_tag)
  {
    bdy = son(bdy);
  }
  while (name(bdy) ==ident_tag && isparam(bdy)
	 && name(son(bdy))!=formal_callee_tag)
  {
    exp sbdy = son(bdy);
    baseoff parampos;
    bool ident_in_register = (props(bdy) & inanyreg)!=0;
    bool is_aggregate = IS_AGGREGATE(sh(sbdy));
    int param_reg = props(sbdy);
    int ident_size = shape_size(sh(sbdy));

    if (p_has_tp)
    {
      parampos.base = R_TP;
    }
    else
    {
      /* Non general proc */
      parampos.base = R_FP;
    }

    parampos.offset = (no(sbdy) >>3) + STACK_ARG_AREA;


    if (param_reg==0 && ident_in_register)
    {
      /* Parameter which was passed by stack and allocated into
	 a register */
      assert(!is_aggregate);/* +++ allow 32 bit aggregates */
      if (isvar(bdy))
      {
	/* somebody has assigned to it so it must be reloaded */
	if (is_floating(name(sh(sbdy))))
	{
	  bool dble = is_double_precision(sh(sbdy));
	  stf_ro_ins(dble ? i_stfd :i_stfs,no(bdy),parampos);
	}
	else
	{
	  st_ro_ins(i_st,no(bdy),parampos);
	}
      }
    }
    else if (param_reg != 0 && ! ident_in_register)
    {
      /* should be in reg is in store */
      if (is_aggregate)
      {
	/* this is an aggregate which was passed partially or totally in register */
	int last_st_reg = param_reg + (ALIGNNEXT(ident_size,32)) -1;
	int r;
	baseoff bo;
	bo = boff(bdy);

	if (last_st_reg > final_param)
	  last_st_reg = final_param;

	for (r = param_reg;r<=last_st_reg;r++)
	{
	  ld_ro_ins(i_l,bo,r);asm_comment("restore struct into caller param regs");
	  bo.offset +=4;
	}
      }
      else if (is_floating(name(sh(sbdy))))
      {
	bool dble = is_double_precision(sh(sbdy));
	ldf_ro_ins(dble ? i_lfd:i_lfs,parampos,param_reg);
      }
      else
      {
	ld_ro_ins(i_l,parampos,param_reg);asm_comment("restore param reg from stack");
      }
    }
    else if (props(sbdy)!=0 && props(sbdy)!=no(bdy))
    {
      /* in wrong register */
      if (is_floating(name(sh(sbdy))))
      {
	rrf_ins(i_fmr,no(bdy),param_reg);
      }
      else
      {
	mov_rr_ins(no(bdy),param_reg);asm_comment("restore param reg from reg");
      }
    }
    bdy = bro(sbdy);
  }
  if (suspected_varargs)
  {
    baseoff v;
    int r;
    if (p_has_tp)
    {
      v.base = R_TP;
    }
    else
    {
      v.base = R_FP;
    }
    v.offset = saved_varargs_offset;
    for (r = saved_varargs_register; r<= final_param ;r++)
    {
      ld_ro_ins(i_l,v,r);asm_comment("restore all params since varargs");
      v.offset += 4;
    }
  }
}
void restore_callees(void)
{
	/*
	 * It is possible that callees are allocated s-regs in which case they
	 * must be moved back on to their proper place on the stack.
	 */
  exp bdy = son(p_current);
  asm_comment("restore callees");

  while (name(bdy) ==diagnose_tag)
  {
    bdy = son(bdy);
  }
  while (name(bdy) ==ident_tag && isparam(bdy)
	 && name(son(bdy))!=formal_callee_tag)
  {
    bdy = bro(son(bdy));
  }
  while (name(bdy) ==ident_tag && isparam(bdy))
  {
    exp sbdy = son(bdy);
    baseoff stackpos;
    stackpos.base = R_FP;
    stackpos.offset = EXTRA_CALLEE_BYTES + (no(sbdy) >>3);
    if (props(bdy) & infreg_bits)
    {
      bool dble = is_double_precision(sh(sbdy));
      assert(IS_FLT_SREG(no(bdy)));
      stf_ro_ins(dble?i_stfd:i_stfs,no(bdy),stackpos);
    }
    else if (props(bdy) & inreg_bits)
    {
      assert(IS_SREG(no(bdy)));
      st_ro_ins(i_st,no(bdy),stackpos);
    }
    bdy = bro(sbdy);
  }
}
static exp find_ote(exp e, int n)
{
  exp d = father(e);
  while (name(d)!=apply_general_tag)d = father(d);
  d = son(bro(son(d))); /* list otagexps */
  while (n !=0) { d = bro(d); n--;}
  assert(name(d) ==caller_tag);
  return d;
}
