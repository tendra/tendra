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


/* 80x86/cproc.c */

/**********************************************************************
$Author: release $
$Date: 1998/03/16 11:25:21 $
$Revision: 1.4 $
$Log: cproc.c,v $
 * Revision 1.4  1998/03/16  11:25:21  release
 * Modifications prior to version 4.1.2.
 *
 * Revision 1.3  1998/03/15  16:00:14  pwe
 * regtrack dwarf dagnostics added
 *
 * Revision 1.2  1998/03/11  11:03:03  pwe
 * DWARF optimisation info
 *
 * Revision 1.1.1.1  1998/01/17  15:55:51  release
 * First version to be checked into rolling release.
 *
 * Revision 1.31  1997/10/23  09:36:56  pwe
 * extra_diags
 *
 * Revision 1.30  1997/10/10  18:25:03  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.29  1997/08/23  13:45:28  pwe
 * initial ANDF-DE
 *
 * Revision 1.28  1997/05/02  11:04:47  pwe
 * minor dwarf2 corrections
 *
 * Revision 1.27  1997/04/17  11:55:43  pwe
 * dwarf2 improvements
 *
 * Revision 1.26  1997/04/02  10:33:10  pwe
 * diagnose pl_tests
 *
 * Revision 1.25  1997/03/24  11:15:08  pwe
 * dwarf2 option/default
 *
 * Revision 1.24  1997/03/20  16:23:35  pwe
 * dwarf2
 *
 * Revision 1.23  1996/12/13  14:39:19  pwe
 * prep NEWDIAGS
 *
 * Revision 1.22  1996/11/08  16:19:02  pwe
 * check_stack to check before modifying stack
 *
 * Revision 1.21  1996/10/31  12:02:33  pwe
 * correct env_offset used in constant evaluation
 *
 * Revision 1.20  1996/10/29  13:50:51  pwe
 * correct space for patched instructions
 *
 * Revision 1.19  1996/10/08  07:58:56  pwe
 * revised correction to env_offset v id out_of_line
 *
 * Revision 1.18  1996/10/07  13:31:06  pwe
 * push make_value, and env_offset v id out_of_line
 *
 * Revision 1.17  1996/07/31  12:56:53  pwe
 * restore alloca stack after longjump
 *
 * Revision 1.16  1996/07/09  09:43:35  pwe
 * caller env_offset if callees present, and tidy
 *
 * Revision 1.15  1996/02/08  13:45:12  pwe
 * Linux elf v aout option
 *
 * Revision 1.14  1996/01/10  09:19:03  pwe
 * profile const & envoffset correction
 *
 * Revision 1.13  1996/01/05  16:25:22  pwe
 * env_size and env_offset within constant expressions
 *
 * Revision 1.12  1995/12/22  09:34:27  pwe
 * solaris diags for stack objects
 *
 * Revision 1.11  1995/12/21  13:47:02  pwe
 * trap for missing pops (sco problem)
 *
 * Revision 1.10  1995/10/13  15:19:47  pwe
 * solaris PIC and linux tcc
 *
 * Revision 1.9  1995/10/09  15:14:09  pwe
 * dynamic initialisation etc
 *
 * Revision 1.8  1995/09/05  16:24:45  pwe
 * specials and exception changes
 *
 * Revision 1.7  1995/08/30  16:06:24  pwe
 * prepare exception trapping
 *
 * Revision 1.6  1995/08/23  09:42:39  pwe
 * track fpu control word for trap etc
 *
 * Revision 1.5  1995/08/14  13:53:30  pwe
 * several corrections, tail calls and error jumps
 *
 * Revision 1.4  1995/08/04  08:29:09  pwe
 * 4.0 general procs implemented
 *
 * Revision 1.3  1995/04/13  11:38:57  pwe
 * odd_bits clean for proc ending with bottom
 *
 * Revision 1.2  1995/01/30  12:56:04  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  14:15:22  jmf
 * Initial revision
 *
 * Revision 1.1  1994/07/12  14:29:47  jmf
 * Initial revision
 *
**********************************************************************/


/**********************************************************************
   cproc produces the code for the procedure defined by which has
   name pname.

**********************************************************************/

#include "config.h"
#include "common_types.h"
#include "weights.h"
#include "basicread.h"
#include "tags.h"
#include "codermacs.h"
#include "instr386.h"
#include "expmacs.h"
#include "exp.h"
#include "operand.h"
#include "shapemacs.h"
#include "instr.h"
#include "instrmacs.h"
#include "out.h"
#include "check.h"
#include "flags.h"
#include "codec.h"
#include "xalloc.h"
#include "global_opt.h"
#include "reg_record.h"
#include "externs.h"
#include "install_fns.h"
#include "installglob.h"
#include "machine.h"
#include "localflags.h"
#include "diag_fns.h"
#include "messages_8.h"
#include "assembler.h"
#include "coder.h"
#include "scan2.h"
#include "cproc.h"

#ifdef NEWDWARF
#include "dw2_config.h"
#include "dw2_info.h"
#include "dw2_basic.h"
#include "dw2_extra.h"
#endif

static exp returns_list;

int locals_offset;	/* global, needed for solaris stabs */
exp hasenvoff_list = nilexp;	/* global, used by coder */

/* MACROS */

#define GLOBALTABLEMASK 0x8

/* PROCEDURES */

static void add_odd_bits
    PROTO_N ( (r) )
    PROTO_T ( outofline * r )
{
  if (r != (outofline*)0) {
    if (r -> next == (outofline*)0)
      last_odd_bit = 1;
    add_odd_bits(r -> next);
  }
  else
    return;

  current_odd_bit = r;
  if (is80486)
    dot_align(4);
  simple_set_label(r->labno);
  clear_reg_record(crt_reg_record);
#ifdef NEWDWARF
  if (dwarf2) {
#if 1
    dw2_start_extra_bit (r->body);
#else
    dw2_start_extra_bit (r->dw2_slave);
#endif
    START_BB ();
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
  if (name(sh(r->body)) != bothd)  {
    clean_stack();
    jump(r->jr, 0);
  }
  else
    stack_dec = 0;
#ifdef NEWDWARF
  if (dwarf2)
#if 1
    dw2_end_extra_bit (r->body);
#else
    dw2_end_extra_bit (r->dw2_hi);
#endif
#endif
  return;
}

static void out_pops
    PROTO_N ( (tot_sp, push_space, extra, dpos) )
    PROTO_T ( int tot_sp X int push_space X int extra X int dpos )
{
#ifdef NEWDWARF
  int st;
  long dwl0 = 0, dwl1 = 0, dwl2 = 0, dwl3 = 0, dwl4 = 0;
#endif
  tot_sp -= extra;
  if (no_frame && !stack_aligned_8byte) {
    if (tot_sp != push_space) {
      outs ("add esp, ");
      outn ((long)(tot_sp - push_space));
      outnl();
#ifdef NEWDWARF
      if (diagnose && dwarf2)
	dwl0 = set_dw_text_label ();
#endif
    };
  }
  else {
    if (tot_sp != push_space || has_alloca || stack_aligned_8byte) {
      outs ("lea esp, -");
      outn ((long)push_space);
      outs ("(ebp)");
      outnl();
    };
  };

  /* pop the registers at the end */
  if (no_frame && (min_rfree & 0x40)) {
    outs ("pop ebp");
    outnl();
#ifdef NEWDWARF
    if (diagnose && dwarf2)
      dwl1 = set_dw_text_label ();
#endif
  };
  if (min_rfree & 0x20) {
    outs ("pop esi");
    outnl();
#ifdef NEWDWARF
    if (diagnose && dwarf2)
      dwl2 = set_dw_text_label ();
#endif
  };
  if (min_rfree & 0x10) {
    outs ("pop edi");
    outnl();
#ifdef NEWDWARF
    if (diagnose && dwarf2)
      dwl3 = set_dw_text_label ();
#endif
  };
  if (min_rfree & 0x8) {
    outs ("pop ebx");
    outnl();
#ifdef NEWDWARF
    if (diagnose && dwarf2)
      dwl4 = set_dw_text_label ();
#endif
  };

  if (!no_frame)  {
    outs ("pop ebp");
    outnl();
#ifdef NEWDWARF
    if (diagnose && dwarf2)
      dwl1 = set_dw_text_label ();
#endif
  };
  outnl();
#ifdef NEWDWARF
  if (diagnose && dwarf2) {
    st = fseek (fpout, dpos, 0);
    if (st == -1) {
      failer (SEEK_FAILURE);
      exit(EXIT_FAILURE);
    };
    dw2_fde_restore_args (dwl0, dwl1, dwl2, dwl3, dwl4, push_space);
  }
#endif
  return;
}

static void out_untidy_pops
    PROTO_N ( (tot_sp, push_space) )
    PROTO_T ( int tot_sp X int push_space )
{
  if (no_frame) {
    int s_offset = tot_sp - push_space;
    if (min_rfree & 0x40) {
      outs ("mov ebp, ");
      outn ((long)s_offset);
      outs ("(esp)");
      outnl();
      s_offset += 4;
    };
    if (min_rfree & 0x20) {
      outs ("mov esi, ");
      outn ((long)s_offset);
      outs ("(esp)");
      outnl();
      s_offset += 4;
    };
    if (min_rfree & 0x10) {
      outs ("mov edi, ");
      outn ((long)s_offset);
      outs ("(esp)");
      outnl();
      s_offset += 4;
    };
    if (min_rfree & 0x8) {
      outs ("mov ebx, ");
      outn ((long)s_offset);
      outs ("(esp)");
      outnl();
      /* s_offset += 4; */
    };
  }
  else {
    int fm_offset = - push_space;
    if (min_rfree & 0x20) {
      outs ("mov esi, ");
      outn ((long)fm_offset);
      outs ("(ebp)");
      outnl();
      fm_offset += 4;
    };
    if (min_rfree & 0x10) {
      outs ("mov edi, ");
      outn ((long)fm_offset);
      outs ("(ebp)");
      outnl();
      fm_offset += 4;
    };
    if (min_rfree & 0x8) {
      outs ("mov ebx, ");
      outn ((long)fm_offset);
      outs ("(ebp)");
      outnl();
      /* fm_offset += 4; */
    };
    outs ("mov ebp, 0(ebp)");
    outnl();
  };
  return;
}


int cproc
    PROTO_N ( (p, pname, cname, global, diag_props) )
    PROTO_T ( exp p X char *pname X int cname X int global X diag_global * diag_props )
{
  exp jr, t, body;
  ash stack;
  int  ms;
  int tot_sp;
  int param_pos;
  int byte_stack_align = stack_align / 8;
  int   st;
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
#ifdef NEWDWARF
  long dwl0, dwl8, dw_entry_pos;
  long dwl1 = 0, dwl2 = 0, dwl3 = 0, dwl4 = 0;
  char * dw_labroom = "                 ";
		     /* .Ldw12345678:\n */
#endif

  int request_align_8byte;

  returns_list = nilexp;
  crt_proc_exp = p;
  crt_proc_id = next_lab();
  crt_ret_lab = next_lab ();	/* set up the return label for the
				   procedure */
  crt_ret_lab_used = 0;
  odd_bits = (outofline*)0;
  scale = (float)1.0;
  not_in_params = 1;
  not_in_postlude = 1;
  keep_short = 0;
  repeat_level = 0;
  callee_size = (proc_has_vcallees(p) ? -1 : 0);
  ferrsize = 0;
  fpucon = normal_fpucon;

  has_dy_callees = 0;		/* set by scan2 when stack_dec indeterminable */
  has_tail_call = 0;		/* set by scan2, used in coder */
  has_same_callees = 0;		/* set by scan2, used in coder */
  proc_has_asm = 0;		/* set by scan2 if any asm operands */
  IGNORE scan2(1, p, p, 0);
  useful_double = 0;
  comp_weights(p);

/* 8byte align */
  request_align_8byte = permit_8byte_align && useful_double;

  if (pname[0] != local_prefix[0])
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
    regsinuse = 0x40; /* prevent ebp from being used as an ordinary
                          register */

  fstack_pos = first_fl_reg;

  max_stack = 0;		/* maximum stack value attained */
  max_extra_stack = 0;		/* maximum stack value attained */
  min_rfree = 0;		/* total registers used */
  stack_dec = 0;		/* current stack decrement */
  cond1_set = 0;
  cond2_set = 0;		/* state of condition flags is not known
				*/
  clear_reg_record (crt_reg_record);
  stack.ashsize = 0;
  stack.ashalign = 0;



  vc_pointer = nilexp;
				/* set up params before any diagnostics */
  t = son(p);
  param_pos = 0;
  while (name(t) == ident_tag && isparam(t) && name(son(t)) != formal_callee_tag)
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
     while (name(pp) == ident_tag && isparam(pp) && name(son(pp)) != formal_callee_tag)
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
    outs (".define ");
    outs (pname);
    outnl ();
  };

  if (is80486)
    dot_align(16);
  else
    dot_align(4);

  if (diagnose)
#ifdef NEWDWARF
    DIAG_PROC_BEGIN (diag_props, global, cname, pname, p);
#else
    diag_proc_begin (diag_props, global, cname, pname);
#endif

  if (cname == -1)
    outs (pname);
  else
    {
      outs(local_prefix);
      outn((long)cname);
    };
  outs (":");
  outnl ();
#ifdef NEWDWARF
  if (diagnose && dwarf2) {
    START_BB ();
    dwl0 = set_dw_text_label ();
  }
#endif

/* space for setting local displacement label */
  if (flush_before_tell)
    IGNORE fflush(fpout);
  old_pos1 = ftell (fpout);
  outs ("                  \n");
     /* ".LdispNNNN = SSSSS\n" */
  outnl ();
  if (flush_before_tell)
    IGNORE fflush(fpout);
  old_pos1a = ftell (fpout);
  outs ("                     \n");
     /* ".LfcwdispNNNN = SSSSS\n" */
  outnl ();

  if (!no_frame) {
    outs ("push ebp");
    outnl ();
    outs ("mov ebp, esp");
    outnl ();
#ifdef NEWDWARF
    if (diagnose && dwarf2)
      dwl1 = set_dw_text_label ();
#endif
  };

/* space for pushing fixed point registers */
  if (flush_before_tell)
    IGNORE fflush(fpout);
  old_pos2 = ftell (fpout);
  outs ("        \n");
     /* "push ebx\n" */
#ifdef NEWDWARF
  if (diagnose && dwarf2)
    outs (dw_labroom);
#endif
  outnl ();
  if (flush_before_tell)
    IGNORE fflush(fpout);
  old_pos3 = ftell (fpout);
  outs ("        \n");
     /* "push edi\n" */
#ifdef NEWDWARF
  if (diagnose && dwarf2)
    outs (dw_labroom);
#endif
  outnl ();
  if (flush_before_tell)
    IGNORE fflush(fpout);
  old_pos4 = ftell (fpout);
  outs ("        \n");
     /* "push esi\n" */
#ifdef NEWDWARF
  if (diagnose && dwarf2)
    outs (dw_labroom);
#endif
  outnl ();
  if (no_frame) {
    if (flush_before_tell)
      IGNORE fflush(fpout);
    old_pos5 = ftell (fpout);
    outs ("        \n");
       /* "push ebp\n" */
#ifdef NEWDWARF
    if (diagnose && dwarf2)
      outs (dw_labroom);
#endif
    outnl ();
  }

/* space for subtract from stack pointer */
  if (flush_before_tell)
    IGNORE fflush(fpout);
  old_pos8 = ftell (fpout);
  outs ("              \n");
     /* "sub esp, SSSSS\n" */
     /* "mov eax, SSSSS\n" */
  outnl ();
  if (proc_has_checkstack(p)) {
    checkalloc_stack (reg0, 1);
  };
#ifdef NEWDWARF
  if (diagnose && dwarf2) {
    dwl8 = set_dw_text_label ();
    dw_entry_pos = dw2_start_fde (dwl0, dwl1);
  }
#endif

  if (stack_aligned_8byte) {
    outs("and esp, -8");
    outnl();
  };

  if (flush_before_tell)
    IGNORE fflush(fpout);
  old_pos9 = ftell (fpout);
  outs ("                                  \n");
     /* "o16 mov 0-.LfcwdispNNNN(ebp), DDDD\n" */
  outnl ();


#if islinux || isfreebsd
  if (
#if islinux
	!linux_elf &&
#endif
	pname[0] != local_prefix[0] &&
	!strcmp (pname+prefix_length, "main")) {
    out_main_prelude();
  }
#endif

  if (do_profile) {
    int  labl = next_lab ();	/* output profile procedure header */
    outs (".sect .data");
    outnl ();
    dot_align(4);
    outs(local_prefix);
    outs ("P");
    outn ((long)labl);
    outs (":");
    outnl ();
    outs (".data4 0");
    outnl ();
    outs (".sect .text");
    outnl ();
    outs ("lea edx, ");
    outs(local_prefix);
    outs ("P");
    outn ((long)labl);
    outnl ();
    outs ("call _mcount");
    outnl ();
  };

  need_preserve_stack = 0;
  if (proc_uses_crt_env(p) && proc_has_lv(p) && has_alloca)
   {
     need_preserve_stack = 1;
     stack.ashsize += 32;
     max_stack = stack.ashsize;
     save_stack ();
   };

  scale = (float)1.0;
  last_odd_bit = 0;
  doing_odd_bits = 0;
  coder (zero, stack, body); /* code body of procedure */

  stack_dec = 0;
  doing_odd_bits = 1;
  while (odd_bits != (outofline*)0) {
    outofline * ol = odd_bits;
    odd_bits = (outofline*)0;
    last_odd_bit = 0;
    add_odd_bits(ol);
  }


  if (crt_ret_lab_used) {
    jr = getexp (f_bottom, nilexp, 0, nilexp, nilexp, 0,
                0, 0);
    sonno(jr) = stack_dec;
    ptno(jr) = crt_ret_lab;
    fstack_pos_of(jr) = (prop)first_fl_reg;
    set_label (jr);
  };

	/* If the procedure loads the current env and uses make_lv
	   it may be the destination of a long_jump. In that case
	   ebx, esi and edi must be saved at and restored at exit.
	   ebp will be saved and restored anyway because such a
	   procedure will have a frame pointer.
	*/
  if (proc_uses_crt_env(p) && proc_has_lv(p))
    min_rfree |= 0x38;

  /* compute space needed for local variables in memory */
  ms = ((max_stack + 31) / 32) * 4;
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
#ifdef NEWDWARF
    long over_lab;
    if (diagnose && dwarf2) {
      over_lab = next_dwarf_label ();
      dw2_return_pos (over_lab);
    }
#endif
    restore_callregs (0);
    retins();
    outnl ();
#ifdef NEWDWARF
    if (diagnose && dwarf2)
      dw2_after_fde_exit (over_lab);
#endif
  };
  outnl ();

  this_pos = ftell (fpout);
  while (returns_list != nilexp) {
    st = fseek (fpout, (long)no(returns_list), 0);
    if (st == -1) {
      failer (SEEK_FAILURE);
      exit(EXIT_FAILURE);
    };
    if (name(returns_list) == 1)
      out_untidy_pops (tot_sp, push_space);
    else
      out_pops(tot_sp, push_space, ptno(returns_list)/8, sonno(returns_list));
    returns_list = bro(returns_list);
  };
  fseek(fpout, this_pos, 0);

  locals_offset = tot_sp;
  if (diagnose) {
    no (p) = tot_sp;	/* may be used by delayed diagnostics */
#ifdef NEWDWARF
    DIAG_PROC_END (diag_props, p);
#else
    diag_proc_end (diag_props);
#endif
#ifdef NEWDWARF
  if (dwarf2)
    dw2_complete_fde ();
#endif
  }

  /* now set in the information at the head of the procedure */
  {

    if (flush_before_tell)
      IGNORE fflush(fpout);
    this_pos = ftell (fpout);
    st = fseek (fpout, old_pos1, 0);
    if (st == -1) {
      failer (SEEK_FAILURE);
      exit(EXIT_FAILURE);
    };

    /* set the label which says how much the stack was decreased, in case
       frame pointer addressing is used  */
    outs(local_prefix);
    outs ("disp");
    outn ((long)crt_proc_id);
    outs (" = ");
    outn ((long)tot_sp);

    if (ferrsize != 0) {
	/* set label for displacement to fpu control local store */
      st = fseek (fpout, old_pos1a, 0);
      if (st == -1) {
        failer (SEEK_FAILURE);
        exit(EXIT_FAILURE);
      };
      outs(local_prefix);
      outs ("fcwdisp");
      outn ((long)crt_proc_id);
      outs (" = ");
      outn ((long)((no_frame) ? (tot_sp - push_space - ferrsize) : (push_space + ferrsize)));
    }

    st = fseek (fpout, this_pos, 0);
    if (st == -1) {
      failer (SEEK_FAILURE);
      exit(EXIT_FAILURE);
    };
  };

  if (tot_sp != push_space || proc_has_checkstack(p)) {
    if (flush_before_tell)
      IGNORE fflush(fpout);
    this_pos = ftell (fpout);
    st = fseek (fpout, old_pos8, 0);
    if (st == -1) {
      failer (SEEK_FAILURE);
      exit(EXIT_FAILURE);
    };

    /* decrease the stack if necessary */
    if (proc_has_checkstack(p)) {
      outs ("mov eax, ");
      outn ((long)(tot_sp - push_space));
    }
    else {
      outs ("sub esp, ");
      outn ((long)(tot_sp - push_space));
    };
    outnl();

    if (ferrsize != 0) {	/* record FPU control word */
      st = fseek (fpout, old_pos9, 0);
      if (st == -1) {
        failer (SEEK_FAILURE);
        exit(EXIT_FAILURE);
      };
      move (uwordsh, mw(zeroe, normal_fpucon), mw(ferrmem, 0));
    }

    st = fseek (fpout, this_pos, 0);
    if (st == -1) {
      failer (SEEK_FAILURE);
      exit(EXIT_FAILURE);
    };
  };

  /* push registers as necessary */
  if (min_rfree & 0x8) {
    st = fseek (fpout, old_pos2, 0);
    if (st == -1) {
      failer (SEEK_FAILURE);
      exit(EXIT_FAILURE);
    };
    outs ("push ebx");
    outnl();
#ifdef NEWDWARF
    if (diagnose && dwarf2)
      dwl2 = set_dw_text_label ();
#endif
  };

  if (min_rfree & 0x10) {
    st = fseek (fpout, old_pos3, 0);
    if (st == -1) {
      failer (SEEK_FAILURE);
      exit(EXIT_FAILURE);
    };
    outs ("push edi");
    outnl();
#ifdef NEWDWARF
    if (diagnose && dwarf2)
      dwl3 = set_dw_text_label ();
#endif
  };


  if (min_rfree & 0x20) {
    st = fseek (fpout, old_pos4, 0);
    if (st == -1) {
      failer (SEEK_FAILURE);
      exit(EXIT_FAILURE);
    };
    outs ("push esi");
    outnl();
#ifdef NEWDWARF
    if (diagnose && dwarf2)
      dwl4 = set_dw_text_label ();
#endif
  };

  if (no_frame && (min_rfree & 0x40)) {
    st = fseek (fpout, old_pos5, 0);
    if (st == -1) {
      failer (SEEK_FAILURE);
      exit(EXIT_FAILURE);
    };
    outs ("push ebp");
    outnl();
#ifdef NEWDWARF
    if (diagnose && dwarf2)
      dwl1 = set_dw_text_label ();
#endif
  };

#ifdef NEWDWARF
  if (diagnose && dwarf2) {
    st = fseek (fpout, dw_entry_pos, 0);
    if (st == -1) {
      failer (SEEK_FAILURE);
      exit(EXIT_FAILURE);
    };
    dw2_fde_entry (dwl0, dwl1, dwl2, dwl3, dwl4, dwl8, tot_sp);
  };
#endif

  st = fseek (fpout, this_pos, 0);
  if (st == -1) {
    failer (SEEK_FAILURE);
    exit(EXIT_FAILURE);
  };

  if (pname[0] != local_prefix[0])
    proc_size (pname);

  if (proc_needs_envsize(p)) {
    outs(local_prefix);
    outs ("ESZ");
    outs (pname);
    outs (" = ");
    outn ((long)(tot_sp + 4 + max_extra_stack/8));
    outnl ();
  }

#if islinux || isfreebsd
  if (
#if islinux
	!linux_elf &&
#endif
	pname[0] != local_prefix[0] &&
	!strcmp (pname+prefix_length, "main")) {
    out_main_postlude();
  }
#endif

  /* now prepare params with env_offset for possible constant evaluation */
  t = son(p);
  while (name(t) == ident_tag && isparam(t)) {
    if (isenvoff(t)) {
      no(t) += 64;
      name(t) = 0;
      ptno(t) = local_pl;
    }
    t = bro(son(t));
  }
  while (hasenvoff_list != nilexp) {
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

  return (proc_needs_envsize(p) ? tot_sp + 4 + max_extra_stack/8 : 0);
}


/* Restore call_save registers (%ebp, %esi, %edi, %ebx)
   when we know which ones are reused.
   This preserves %eax, %ecx, %edx */
void restore_callregs
    PROTO_N ( (untidy) )
    PROTO_T ( int untidy )
{
  char *sp50 = "                                                  ";
  long retpos = ftell(fpout);
  outs("?");	/* will be overwritten, to cause assembler fail if sco bug */
  outs(sp50); outs(sp50); outs(sp50);
  outnl();
  returns_list = getexp(f_top, returns_list, 0, nilexp,
				nilexp, 0, 0, (unsigned char)untidy);
  no(returns_list) = (int)retpos;
  ptno(returns_list) = stack_dec;
#ifdef NEWDWARF
  if (diagnose && dwarf2)
    sonno(returns_list) = (int)dw2_prep_fde_restore_args (untidy);
#endif
  return;
}
