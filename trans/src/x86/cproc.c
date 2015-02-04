/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * cproc produces the code for the procedure defined by which has
 * name pname.
 */

#include <string.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#ifdef DWARF2
#include <local/dw2_config.h>
#endif

#include <local/ash.h>
#include <local/out.h>
#include <local/cpu.h>
#include <local/codermacs.h>

#ifdef TDF_DIAG4
#include <diag4/diag_fns.h>
#else
#include <diag3/diag_fns.h>
#endif

#include <reader/basicread.h>
#include <reader/externs.h>

#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/shape.h>
#include <construct/install_fns.h>
#include <construct/installglob.h>
#include <construct/machine.h>

#include <main/flags.h>

#include "localtypes.h"
#include "weights.h"
#include "instr386.h"
#include "operand.h"
#include "instr.h"
#include "instrmacs.h"
#include "codec.h"
#include "reg_record.h"
#include "messages_8.h"
#include "assembler.h"
#include "coder.h"
#include "scan.h"
#include "cproc.h"
#include "localexpmacs.h"

#ifdef DWARF2
#include <dwarf2/dw2_info.h>
#include <dwarf2/dw2_basic.h>
#include "dw2_extra.h"
#endif

static exp returns_list;

unsigned normal_fpucon;
int stack_aligned_8byte = 0;
int permit_8byte_align  = 1;
int useful_double = 0;
int keep_short = 0;
int always_use_frame;
int locals_offset;	/* global, needed for solaris stabs */
exp hasenvoff_list = NULL;	/* global, used by coder */

#define GLOBALTABLEMASK 0x8

static void add_odd_bits
(outofline * r)
{
  if (r != NULL) {
    if (r -> next == NULL)
      last_odd_bit = 1;
    add_odd_bits(r -> next);
  }
  else
    return;

  current_odd_bit = r;
  if (cpu & CPU_80486)
    dot_align(4);
  simple_set_label(r->labno);
  clear_reg_record(crt_reg_record);
#ifdef DWARF2
  if (diag == DIAG_DWARF2) {
#if 1
    dw2_start_extra_bit(r->body);
#else
    dw2_start_extra_bit(r->dw2_slave);
#endif
    dw2_start_basic_block();
  }
#endif

  regsinuse = r->regsinuse;
  fstack_pos = r->fstack_pos;
  cond1_set = r->cond1_set;
  cond2_set = r->cond2_set;
  cond1 = r->cond1;
  cond2a = r->cond2a;
  cond2b = r->cond2b;
  repeat_level = r->repeat_level;
  scale = r->scale;
  coder(r->dest, r->stack, r->body);
  if (name(sh(r->body))!= bothd) {
    clean_stack();
    jump(r->jr, 0);
  }
  else
    stack_dec = 0;
#ifdef DWARF2
  if (diag == DIAG_DWARF2)
#if 1
    dw2_end_extra_bit(r->body);
#else
    dw2_end_extra_bit(r->dw2_hi);
#endif
#endif
  return;
}

static void out_pops
(int tot_sp, int push_space, int extra, int dpos)
{
#ifdef DWARF2
  long dwl0 = 0, dwl1 = 0, dwl2 = 0, dwl3 = 0, dwl4 = 0;
#endif
  tot_sp -= extra;
  if (no_frame && !stack_aligned_8byte) {
    if (tot_sp != push_space) {
      outs(" addl $");
      outn((long)(tot_sp - push_space));
      outs(",%esp");
      outnl();
#ifdef DWARF2
      if (diag == DIAG_DWARF2)
	dwl0 = set_dw_text_label();
#endif
    };
  }
  else {
    if (tot_sp != push_space || has_alloca || stack_aligned_8byte) {
      outs(" leal -");
      outn((long)push_space);
      outs("(%ebp),%esp");
      outnl();
    };
  };

  /* pop the registers at the end */
  if (no_frame && (min_rfree & 0x40)) {
    outs(" pop %ebp");
    outnl();
#ifdef DWARF2
    if (diag == DIAG_DWARF2)
      dwl1 = set_dw_text_label();
#endif
  };
  if (min_rfree & 0x20) {
    outs(" pop %esi");
    outnl();
#ifdef DWARF2
    if (diag == DIAG_DWARF2)
      dwl2 = set_dw_text_label();
#endif
  };
  if (min_rfree & 0x10) {
    outs(" pop %edi");
    outnl();
#ifdef DWARF2
    if (diag == DIAG_DWARF2)
      dwl3 = set_dw_text_label();
#endif
  };
  if (min_rfree & 0x8) {
    outs(" pop %ebx");
    outnl();
#ifdef DWARF2
    if (diag == DIAG_DWARF2)
      dwl4 = set_dw_text_label();
#endif
  };

  if (!no_frame) {
    outs(" pop %ebp");
    outnl();
#ifdef DWARF2
    if (diag == DIAG_DWARF2)
      dwl1 = set_dw_text_label();
#endif
  };
  outnl();
#ifdef DWARF2
  if (diag == DIAG_DWARF2) {
    out_set_pos(dpos);
    dw2_fde_restore_args(dwl0, dwl1, dwl2, dwl3, dwl4, push_space);
  }
#endif
  return;
}

static void out_untidy_pops
(int tot_sp, int push_space)
{
  if (no_frame) {
    int s_offset = tot_sp - push_space;
    if (min_rfree & 0x40) {
      outs(" movl ");
      outn((long)s_offset);
      outs("(%esp),%ebp");
      outnl();
      s_offset += 4;
    };
    if (min_rfree & 0x20) {
      outs(" movl ");
      outn((long)s_offset);
      outs("(%esp),%esi");
      outnl();
      s_offset += 4;
    };
    if (min_rfree & 0x10) {
      outs(" movl ");
      outn((long)s_offset);
      outs("(%esp),%edi");
      outnl();
      s_offset += 4;
    };
    if (min_rfree & 0x8) {
      outs(" movl ");
      outn((long)s_offset);
      outs("(%esp),%ebx");
      outnl();
      /* s_offset += 4; */
    };
  }
  else {
    int fm_offset = - push_space;
    if (min_rfree & 0x20) {
      outs(" movl ");
      outn((long)fm_offset);
      outs("(%ebp),%esi");
      outnl();
      fm_offset += 4;
    };
    if (min_rfree & 0x10) {
      outs(" movl ");
      outn((long)fm_offset);
      outs("(%ebp),%edi");
      outnl();
      fm_offset += 4;
    };
    if (min_rfree & 0x8) {
      outs(" movl ");
      outn((long)fm_offset);
      outs("(%ebp),%ebx");
      outnl();
      /* fm_offset += 4; */
    };
    outs(" movl 0(%ebp),%ebp");
    outnl();
  };
  return;
}

#ifdef TDF_DIAG4
int cproc
(exp p, char *pname, int cname, int global, struct dg_name_t * diag_props)
#else
int cproc
(exp p, char *pname, int cname, int global, diag_global * diag_props)
#endif
{
  exp jr, t, body;
  ash stack;
  int  ms;
  int tot_sp;
  int param_pos;
  int byte_stack_align = stack_align / 8;
  long  old_pos1,
        old_pos1a,
        old_pos2,
        old_pos3,
        old_pos4,
        old_pos5,
        old_pos8,
        old_pos9,
        this_pos;
  int  push_space = 0;
#ifdef DWARF2
  long dwl0, dwl8, dw_entry_pos;
  long dwl1 = 0, dwl2 = 0, dwl3 = 0, dwl4 = 0;
  char * dw_labroom = "                 ";
		     /* .Ldw12345678:\n */
#endif

  int request_align_8byte;

  returns_list = NULL;
  crt_proc_exp = p;
  crt_proc_id = next_lab();
  crt_ret_lab = next_lab ();	/* set up the return label for the procedure */
  crt_ret_lab_used = 0;
  odd_bits = NULL;
  scale = (float)1.0;
  not_in_params = 1;
  not_in_postlude = 1;
  keep_short = 0;
  repeat_level = 0;
  callee_size = (proc_has_vcallees(p)? -1 : 0);
  ferrsize = 0;
  fpucon = normal_fpucon;

  has_dy_callees = 0;		/* set by scan when stack_dec indeterminable */
  has_tail_call = 0;		/* set by scan, used in coder */
  has_same_callees = 0;		/* set by scan, used in coder */
  proc_has_asm = 0;		/* set by scan if any asm operands */
  IGNORE scan(1, p, p, 0);
  useful_double = 0;
  comp_weights(p);

/* 8byte align */
  request_align_8byte = permit_8byte_align && useful_double;

  if (pname[0]!= local_prefix[0])
    proc_type(pname);

  has_alloca = proc_has_alloca(p);

  must_use_bp = (has_alloca || proc_has_lv(p));

  regsinuse = 0;

  no_frame = 1;
  if (always_use_frame || do_profile || must_use_bp || has_dy_callees ||
        proc_uses_crt_env(p) || proc_has_setjmp(p) || proc_has_asm
    )
     no_frame = 0;

  if (request_align_8byte && no_frame) {
    no_frame = 0;
    stack_aligned_8byte = 1;
  }
  else
    stack_aligned_8byte = 0;

  if (!no_frame)
    regsinuse = 0x40; /* prevent ebp from being used as an ordinary register */

  fstack_pos = first_fl_reg;

  max_stack = 0;		/* maximum stack value attained */
  max_extra_stack = 0;		/* maximum stack value attained */
  min_rfree = 0;		/* total registers used */
  stack_dec = 0;		/* current stack decrement */
  cond1_set = 0;
  cond2_set = 0;		/* state of condition flags is not known
				*/
  clear_reg_record(crt_reg_record);
  stack.ashsize = 0;
  stack.ashalign = 0;



  vc_pointer = NULL;
				/* set up params before any diagnostics */
  t = son(p);
  param_pos = 0;
  while (name(t) == ident_tag && isparam(t) && name(son(t))!= formal_callee_tag)
   {
     t = bro(son(t));
   };
  if (name(t) == ident_tag && name(son(t)) == formal_callee_tag)
   {
     if (callee_size < 0)
	vc_pointer = t;
     while (name(t) == ident_tag && name(son(t)) == formal_callee_tag)
      {
	ptno(t) = par_pl;
	no(t) = param_pos;
	if (isenvoff(t))
	  set_env_off(param_pos+64, t);
	param_pos = rounder(param_pos + shape_size(sh(son(t))), param_align);
	t = bro(son(t));
      };
     if (callee_size == 0)
	callee_size = param_pos;
   };
   {
     exp pp = son(p);
     while (name(pp) == ident_tag && isparam(pp) && name(son(pp))!= formal_callee_tag)
      {
	ptno(pp) = par_pl;
	no(pp) = param_pos;
	if (isenvoff(pp))
	  set_env_off(param_pos+64, pp);
	param_pos = rounder(param_pos + shape_size(sh(son(pp))), param_align);
	pp = bro(son(pp));
      };
   };

  body = t;




  if (global) {
    outs(".globl ");
    outs(pname);
    outnl();
  };

  if (cpu & CPU_80486)
    dot_align(16);
  else
    dot_align(4);

  if (diag != DIAG_NONE)
    {
#ifdef DWARF2
    if (diag == DIAG_DWARF2) {
		dw2_proc_start(p, diag_props);
	}
#else
    diag_proc_begin(diag_props, global, cname, pname);
#endif
    };

  if (cname == -1)
    {
      outs(pname);
    }
  else
    {
      outs(local_prefix);
      outn((long)cname);
    };
  outs(":");
  outnl();
#ifdef DWARF2
  if (diag == DIAG_DWARF2) {
    dw2_start_basic_block();
    dwl0 = set_dw_text_label();
  }
#endif

/* space for setting local displacement label */
  old_pos1 = out_tell_pos();
  outs("                          ");
     /* ".set .LdispNNNN, SSSSS\n" */
  outnl();
  old_pos1a = out_tell_pos();
  outs("                             ");
     /* ".set .LfcwdispNNNN, SSSSS\n" */
  outnl();

  if (!no_frame) {
    outs(" pushl %ebp");
    outnl();
    outs(" movl %esp,%ebp");
    outnl();
#ifdef DWARF2
    if (diag == DIAG_DWARF2)
      dwl1 = set_dw_text_label();
#endif
  };

/* space for pushing fixed point registers */
  old_pos2 = out_tell_pos();
  outs("               ");
     /* " pushl %ebx\n" */
#ifdef DWARF2
  if (diag == DIAG_DWARF2)
    outs(dw_labroom);
#endif
  outnl();
  old_pos3 = out_tell_pos();
  outs("               ");
     /* " pushl %edi\n" */
#ifdef DWARF2
  if (diag == DIAG_DWARF2)
    outs(dw_labroom);
#endif
  outnl();
  old_pos4 = out_tell_pos();
  outs("               ");
     /* " pushl %esi\n" */
#ifdef DWARF2
  if (diag == DIAG_DWARF2)
    outs(dw_labroom);
#endif
  outnl();
  if (no_frame) {
    old_pos5 = out_tell_pos();
    outs("               ");
       /* " pushl %ebp\n" */
#ifdef DWARF2
    if (diag == DIAG_DWARF2)
      outs(dw_labroom);
#endif
    outnl();
  }

/* space for subtract from stack pointer */
  old_pos8 = out_tell_pos();
  outs("                     ");
     /* " subl $SSSSS,%esp\n" */
     /* " movl $SSSSS,%eax\n" */
  outnl();
  if (proc_has_checkstack(p)) {
    checkalloc_stack(reg0, 1);
  };
#ifdef DWARF2
  if (diag == DIAG_DWARF2) {
    dwl8 = set_dw_text_label();
    dw_entry_pos = dw2_start_fde(dwl0, dwl1);
  }
#endif

  if (stack_aligned_8byte) {
    outs(" andl $-8,%esp");
    outnl();
  };

  old_pos9 = out_tell_pos();
  outs("                                    ");
     /* "movw $DDDD,0-.LfcwdispNNNN(%ebp)\n" */
  outnl();

  if (assembler != ASM_SUN && format == FORMAT_AOUT) {
	if (pname[0]!= local_prefix[0] &&
	!strcmp(pname + strlen(name_prefix), "main")) {
      out_main_prelude();
    }
  }

  if (do_profile) {
    int  labl = next_lab ();	/* output profile procedure header */
    outs(".data");
    outnl();
    dot_align(4);
    outs(local_prefix);
    outs("P");
    outn((long)labl);
    outs(":");
    outnl();
    outs(" .long 0");
    outnl();
    outs(".text");
    outnl();
    outs(" leal ");
    outs(local_prefix);
    outs("P");
    outn((long)labl);
    outs(",%edx");
    outnl();
    outs(" call _mcount");
    outnl();
  };


  if (PIC_code && proc_uses_external(p))
   {
     regsinuse |= GLOBALTABLEMASK;
     min_rfree |= GLOBALTABLEMASK;
     pic_prelude();
   };

  need_preserve_stack = 0;
  if (proc_uses_crt_env(p) && proc_has_lv(p) && has_alloca)
   {
     need_preserve_stack = 1;
     stack.ashsize += 32;
     max_stack = stack.ashsize;
     save_stack();
   };

  scale = (float)1.0;
  last_odd_bit = 0;
  doing_odd_bits = 0;
  coder (zero, stack, body); /* code body of procedure */

  stack_dec = 0;
  doing_odd_bits = 1;
  while (odd_bits != NULL) {
    outofline * ol = odd_bits;
    odd_bits = NULL;
    last_odd_bit = 0;
    add_odd_bits(ol);
  }


  if (crt_ret_lab_used) {
    jr = getexp(f_bottom, NULL, 0, NULL, NULL, 0,
                0, 0);
    sonno(jr) = stack_dec;
    ptno(jr) = crt_ret_lab;
    fstack_pos_of(jr) = (prop)first_fl_reg;
    set_label(jr);
  };

	/*
	 * If the procedure loads the current env and uses make_lv it may be
	 * the destination of a long_jump. In that case ebx, esi and edi must
	 * be saved at and restored at exit. ebp will be saved and restored
	 * anyway because such a procedure will have a frame pointer.
	 */
  if (proc_uses_crt_env(p) && proc_has_lv(p))
    min_rfree |= 0x38;

  /* compute space needed for local variables in memory */
  ms = ((max_stack + 31) / 32)* 4;
  /* compute space needed for pushing registers */
  if (no_frame && min_rfree & 0x40)
    push_space += 4;
  if (min_rfree & 0x20)
    push_space += 4;
  if (min_rfree & 0x10)
    push_space += 4;
  if (min_rfree & 0x8)
    push_space += 4;

  ferrsize /= 8;
  tot_sp = rounder(ms + push_space + ferrsize, byte_stack_align);

  if (crt_ret_lab_used) {
#ifdef DWARF2
    long over_lab;
    if (diag == DIAG_DWARF2) {
      over_lab = next_dwarf_label();
      dw2_return_pos(over_lab);
    }
#endif
    restore_callregs(0);
    retins();
    outnl();
#ifdef DWARF2
    if (diag == DIAG_DWARF2)
      dw2_after_fde_exit(over_lab);
#endif
  };
  outnl();

  this_pos = out_tell_pos();
  while (returns_list != NULL) {
	  out_set_pos(no(returns_list)); /* XXX: no (macro) returns int */
    if (name(returns_list) == 1)
      out_untidy_pops(tot_sp, push_space);
    else
      out_pops(tot_sp, push_space, ptno(returns_list) /8, sonno(returns_list));
    returns_list = bro(returns_list);
  };
  out_set_pos(this_pos);

  locals_offset = tot_sp;
  if (diag != DIAG_NONE) {
    no (p) = tot_sp;	/* may be used by delayed diagnostics */
#ifndef TDF_DIAG4
    diag_proc_end(diag_props);
#else
#if DWARF2
    if (diag == DIAG_DWARF2) {
      dw2_proc_end(p);
    }
#else
    diag_proc_end(diag_props);
#endif
#endif
#ifdef DWARF2
  if (diag == DIAG_DWARF2)
    dw2_complete_fde();
#endif
  }

  /*
   * Now set in the information at the head of the procedure
   */
  {

    this_pos = out_tell_pos();
    out_set_pos(old_pos1);

    /*
	 * Set the label which says how much the stack was decreased, in case
     * frame pointer addressing is used
	 */
    outs(".set ");
    outs(local_prefix);
    outs("disp");
    outn((long)crt_proc_id);
    outs(", ");
    outn((long)tot_sp);

    if (ferrsize != 0) {
	/* set label for displacement to fpu control local store */
	    out_set_pos(old_pos1a);
      outs(".set ");
      outs(local_prefix);
      outs("fcwdisp");
      outn((long)crt_proc_id);
      outs(", ");
      outn((long)((no_frame)?(tot_sp - push_space - ferrsize):(push_space + ferrsize)));
    }

    out_set_pos(this_pos);
  };

  if (tot_sp != push_space || proc_has_checkstack(p)) {
    this_pos = out_tell_pos();
    out_set_pos(old_pos8);

    /* decrease the stack if necessary */
    if (proc_has_checkstack(p)) {
      outs(" movl $");
      outn((long)(tot_sp - push_space));
      outs(",%eax");
    }
    else {
      outs(" subl $");
      outn((long)(tot_sp - push_space));
      outs(",%esp");
    };
    outnl();

    if (ferrsize != 0) {	/* record FPU control word */
	    out_set_pos(old_pos9);
      move(uwordsh, mw(zeroe, normal_fpucon), mw(ferrmem, 0));
    }

    out_set_pos(this_pos);
  };

  /* push registers as necessary */
  if (min_rfree & 0x8) {
	  out_set_pos(old_pos2);
    outs(" pushl %ebx");
    outnl();
#ifdef DWARF2
    if (diag == DIAG_DWARF2)
      dwl2 = set_dw_text_label();
#endif
  };

  if (min_rfree & 0x10) {
	  out_set_pos(old_pos3);
    outs(" pushl %edi");
    outnl();
#ifdef DWARF2
    if (diag == DIAG_DWARF2)
      dwl3 = set_dw_text_label();
#endif
  };


  if (min_rfree & 0x20) {
	  out_set_pos(old_pos4);
    outs(" pushl %esi");
    outnl();
#ifdef DWARF2
    if (diag == DIAG_DWARF2)
      dwl4 = set_dw_text_label();
#endif
  };

  if (no_frame && (min_rfree & 0x40)) {
	  out_set_pos(old_pos5);
    outs(" pushl %ebp");
    outnl();
#ifdef DWARF2
    if (diag == DIAG_DWARF2)
      dwl1 = set_dw_text_label();
#endif
  };

#ifdef DWARF2
  if (diag == DIAG_DWARF2) {
	  out_set_pos(dw_entry_pos);
    dw2_fde_entry(dwl0, dwl1, dwl2, dwl3, dwl4, dwl8, tot_sp);
  };
#endif

  out_set_pos(this_pos);

  if (pname[0]!= local_prefix[0])
    proc_size(pname);

  if (proc_needs_envsize(p)) {
    outs(".set ");
    outs(local_prefix);
    outs("ESZ");
    outs(pname);
    outs(", ");
    outn((long)(tot_sp + 4 + max_extra_stack/8));
    outnl();
  }

  if (assembler != ASM_SUN && format == FORMAT_AOUT) {
    if (pname[0]!= local_prefix[0] &&
	!strcmp(pname + strlen(name_prefix), "main")) {
      out_main_postlude();
    }
  }

  /*
   * now prepare params with env_offset for possible constant evaluation
   */
  t = son(p);
  while (name(t) == ident_tag && isparam(t)) {
    if (isenvoff(t)) {
      no(t) += 64;
      name(t) = 0;
      ptno(t) = local_pl;
    }
    t = bro(son(t));
  }
  while (hasenvoff_list != NULL) {
    exp id = son(hasenvoff_list);
    exp next = bro(hasenvoff_list);
    no(id) -= (locals_offset * 8);
    name(id) = 0;
    retcell(hasenvoff_list);
    hasenvoff_list = next;
  }

  if (no_frame)			/* hold info for later diagnostics */
    clear_proc_has_fp(p);
  else
    set_proc_has_fp(p);

  return proc_needs_envsize(p)? tot_sp + 4 + max_extra_stack/8 : 0;
}

/*
 * Restore call_save registers (%ebp, %esi, %edi, %ebx)
 * when we know which ones are reused.
 * This preserves %eax, %ecx, %edx
 */
void restore_callregs
(int untidy)
{
  char *sp50 = "                                                  ";
  long retpos = out_tell_pos();
  outs("?");	/* will be overwritten, to cause assembler fail if sco bug */
  outs(sp50); outs(sp50); outs(sp50);
  outnl();
  returns_list = getexp(f_top, returns_list, 0, NULL,
				NULL, 0, 0,(unsigned char)untidy);
  no(returns_list) = (int)retpos;
  ptno(returns_list) = stack_dec;
#ifdef DWARF2
  if (diag == DIAG_DWARF2)
    sonno(returns_list) = (int)dw2_prep_fde_restore_args(untidy);
#endif
  return;
}
