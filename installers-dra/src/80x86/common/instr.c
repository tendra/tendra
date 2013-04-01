/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/**********************************************************************
                           instr.c


   defines the general routines for outputting instructions and labels:



**********************************************************************/

#include <string.h>
#include <stdlib.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include "config.h"

#ifdef NEWDWARF
#include "dw2_config.h"
#endif

#include <reader/table_fns.h>
#include <reader/basicread.h>
#include <reader/readglob.h>
#include <reader/externs.h>

#include <construct/exp.h>
#include <construct/flags.h>
#include <construct/tags.h>
#include <construct/shapemacs.h>
#include <construct/flpt.h>
#include <construct/flpttypes.h>
#include <construct/installglob.h>
#include <construct/install_fns.h>
#include <construct/machine.h>
#include <construct/label_ops.h>

#include <refactor/refactor.h>

#include "exptypes.h"
#include "out.h"
#include "operand.h"
#include "expmacs.h"
#include "instr386.h"
#include "coder.h"
#include "reg_record.h"
#include "codermacs.h"
#include "localflags.h"
#include "assembler.h"
#include "messages_8.h"
#include "instrmacs.h"

#include "instr.h"

#ifdef NEWDWARF
#include "dw2_extra.h"
#include "diag_config.h"
#endif


/* LOCAL TYPE */

typedef union eu_u {int i; exp e;} punner;

/* MACROS */

#define fstack_base 8

/* VARIABLES */
/* All variables initialised */

int  extra_stack = 0;	/* init by init_all */
int max_extra_stack = 0;	/* init by cproc */
int no_frame;		/* init by cproc */
#ifndef NEWDIAGS
static long  last_jump_pos;	/* set locally */
#endif
int  last_jump_label;	/* cleared to -1 by outnl */
int avoid_intov; /* No software interrupts */

static exp cont_err_handler = nilexp;


/* IDENTITIES */

char *margin = " ";		/* instruction left margin */
char *spx = " ";		/* separates instruction from operands */
char *sep = ",";		/* separates operands */

char *reg_name_long[8] = {
  "%eax", "%edx", "%ecx", "%ebx", "%edi", "%esi", "%ebp", "%esp"
};
char *reg_name_word[7] = {
  "%ax", "%dx", "%cx", "%bx", "%di", "%si", "%bp"
};
char *reg_name_byte[7] = {
  "%al", "%dl", "%cl", "%bl", "%??", "%??", "%??"
};

char *fl_reg_name[8] = {
  "%st", "%st(1)", "%st(2)", "%st(3)", "%st(4)", "%st(5)", "%st(6)",
  "%st(7)",
};

/* PROCEDURES */

void temp_push_fl
(void)
{
  ++fstack_pos;
  return;
}
void temp_pop_fl
(void)
{
  --fstack_pos;
  return;
}


/***************************************************************

outreal outputs a floating point number

****************************************************************/

void outreal
(exp e)
{
  flt * f = &flptnos[no(e)];
  int sw = name(sh(e)) - shrealhd;
  r2l longs;

  longs = real2longs_IEEE(f, sw);

  switch (sw) {
    case 0:
      outhex(longs.i1);
      outnl();
      break;
    case 1:
      outhex(longs.i1);
      outs(",");
      outhex(longs.i2);
      outnl();
      break;
    case 2:
      outhex(longs.i1);
      outs(",");
      outhex(longs.i2);
      outs(",");
      outhex(longs.i3);
      outnl();
      break;
  };

  return;
}

/* output operand i (in bytes) relative to
   stack pointer  uses address relative to
   frame pointer if it might be shorter */
void rel_sp
(int i, int b)
{
  int  n = i + (extra_stack / 8);
  if (!must_use_bp) {
				/* if we might use alloca all
				   displacements must be relative to frame
				   pointer */
    if (n == 0) {
      outs("(%esp");
      if (b)
	outs(")");
      return;
    };
    if (n <= 127 || no_frame || stack_aligned_8byte) {
				/* use stack pointer if displacement from
				   it is small */
      outn((long)n);
      outs("(%esp");
      if (b)
	outs(")");
      return;
    };
  };
  /* otherwise use displacement from frame pointer */
  outn((long)(i + (stack_dec / 8)));
  outs("-");
  outs(local_prefix);
  outs("disp");
  outn((long)crt_proc_id);
  outs("(%ebp");
  if (b)
    outs(")");
  return;
}

/* output operand i (in bytes) relative to
   stack pointer */
void rel_cp
(int i, int b)
{
  int  n = i + (extra_stack / 8);
  if (n == 0) {
    outs("(%esp");
    if (b)
      outs(")");
    return;
  };
  outn((long)n);
  outs("(%esp");
  if (b)
    outs(")");
  return;
}

/* output operand relative to frame
   pointer */
void rel_ap
(int i, int b)
{
  if (no_frame) {
    outn((long)(i + ((extra_stack - stack_dec) / 8)));
    outs("+");
    outs(local_prefix);
    outs("disp");
    outn((long)crt_proc_id);
    outs("(%esp");
    if (b)
      outs(")");
    return;
  }
  else {
    outn((long)i + 4);
    outs("(%ebp");
    if (b)
      outs(")");
    return;
  };
}

/* output operand relative to frame
   pointer and push space*/
void rel_ap1
(int i, int b)
{
  if (no_frame) {
    outn((long)(i + ((extra_stack - stack_dec) / 8)));
    outs("+");
    outs(local_prefix);
    outs("fcwdisp");
    outn((long)crt_proc_id);
    outs("(%esp");
    if (b)
      outs(")");
    return;
  }
  else {
    outn((long)i);
    outs("-");
    outs(local_prefix);
    outs("fcwdisp");
    outn((long)crt_proc_id);
    outs("(%ebp");
    if (b)
      outs(")");
    return;
  };
}

int  get_reg_no
(int regs)
{
  frr fr;
  /* find the registers associated with the bit pattern regs */

  fr = first_reg(regs);
  if (regs == 0x10000 || fr.fr_no == (fstack_pos))
    return fstack_pos;
  return fr.fr_no;		/* this is the register number */
}

/* output a register address, regs is a
   bit pattern, rdisp is an offset in bit
   units. le tells us how to refer to the
   register (eg al or ax or eax) */
void regn
(int regs, int rdisp, exp ldname, int le)
{
  int  z;
  char **rn;
  UNUSED(rdisp);
  z = get_reg_no(regs);

  if (name(ldname) == name_tag && islastuse(ldname))
    regsinuse = regsinuse & ~regs;

  if (z >= first_fl_reg) {
    if (z == first_fl_reg) {
      outs(fl_reg_name[0]);
      return;
    };
    if (fstack_pos > 16) {
      failer(BAD_FSTACK);
      exit(EXIT_FAILURE);
    };
    outs(fl_reg_name[fstack_pos - z]);
    /* variables held in the floating point registers have to be addressed
       relative to the current stack position, because the registers are a
       stack as well as a register bank */
    return;
  };

  switch (le) {
    case 8:
      rn = reg_name_byte;
      break;
    case 16:
      rn = reg_name_word;
      break;
    default:
      rn = reg_name_long;
      break;
  };
  outs (rn[z]);			/* this outputs the register name */
  return;
}


/* output a displacement from register operand */
void ind_reg
(int regs, int rdisp, int offset, exp ldname, int b)
{
  if (regs == 128)
    offset += extra_stack;

  if (offset == 0) {
    outs("(");
    regn(regs, rdisp, ldname, 32);
    if (b)
      outs(")");
  }
  else {
    outn((long)offset / 8);
    outs("(");
    regn(regs, rdisp, ldname, 32);
    if (b)
      outs(")");
  };
  return;
}

/* use indexed addressing */
void index_opnd
(where whmain, where wh, int sc)
{
  exp m = whmain.where_exp;
  if ((name(m) == name_tag && ptno(son(m)) == reg_pl) ||
     (name(m) == cont_tag && name(son(m)) == name_tag &&
	isvar(son(son(m))) && ptno(son(son(m))) == reg_pl))
    outs("(");
  operand(32, whmain, 0, 0);
  outs(",");
  operand(32, wh, 1, 0);
  if (sc != 1) {
    outs(",");
    outn((long)sc);
  };
  outs(")");
  return;
}


/* output an external operand */
void extn
(exp id, int off, int b)
{
  dec * et;

  et = brog(id);

  if (PIC_code)
   {
     char * got;
     if (et -> dec_u.dec_val.extnamed)
        got = "GOT";
     else
        got = "GOTOFF";
     outs(et -> dec_u.dec_val.dec_id);
     outs("@");
     outs(got);
     if (off != 0)
      {
        outs("+");
        outn((long)off / 8);
      };
     outs("(%ebx");
     if (b)
       outs(")");
     return;
   };

  if (off == 0)
    outs(et -> dec_u.dec_val.dec_id);
  else {
    outs(et -> dec_u.dec_val.dec_id);
    outs("+");
    outn((long)off / 8);
  };
  if (!b)
    outs("(");
  return;
}

/* an integer constant */
void int_operand
(int k, int l)
{
  int  mask;
  switch (l) {
    case 8:
      mask = 0xff;
      break;
    case 16:
      mask = 0xffff;
      break;
    default:
      mask = 0xffffffff;
  };
  outs("$");
  outn((long)k & mask);
  return;
}


/* an external literal */
void const_extn
(exp ident, int noff)
{
  if (!PIC_code)
    outs("$");
  extn(ident, noff, 1);
  return;
}

/* an external literal */
void proc_extn
(exp id, int off)
{
  if (PIC_code)
   {
     dec * et;
     et = brog(id);
     if (off == 0)
       outs(et -> dec_u.dec_val.dec_id);
     else {
        outn((long)off / 8);
        outs("+");
        outs(et -> dec_u.dec_val.dec_id);
     };
     if (et -> dec_u.dec_val.extnamed)
        outs("@PLT");
   }
  else
   {
     outs("$");
     extn(id, off, 1);
   };

  return;
}

void ldisp
(void)
{
   outs(local_prefix);
   outs("disp");
   outn((long)crt_proc_id);
}

void label_operand
(exp e)
{
  punner l;
  l.e = pt(e);
  outs("$");
  outs(local_prefix);
  outs("V");
  outhex(l.i);
  return;
}

void set_lv_label
(exp e)
{
  punner l;
  l.e = e;
  min_rfree |= 0x78;  /* save all callee registers */

  outs(local_prefix);
  outs("V");
  outhex(l.i);
  outs(":");
  outnl();
  return;
}

void set_env_off
(int s, exp n)
{
  punner l;
  l.e = n;
  outs(".set ");
  outs(local_prefix);
  outs("O");
  outhex(l.i);		/* produce an identifying number */
  outs(",");
  if (s<4)
   {
    outn((long) -s/8);
    outs("-");
    outs(local_prefix);
    outs("disp");
    outn((long)crt_proc_id);
   }
  else
   outn((long)s/8);
  outnl();
}

void envoff_operand
(exp e, int off)
{
  punner l;
  l.e = e;
  if (off != 0)
   {
    outn((long)off);
    outs("+");
   };
  outs(local_prefix);
  outs("O");
  outhex(l.i);		/* produce an identifying number */
  return;
}

void envsize_operand
(exp e)
{
  dec * et = brog(e);
  outs(local_prefix);
  outs("ESZ");
  outs(et -> dec_u.dec_val.dec_id);
  return;
}

/* 80386 instruction with no operands */
void ins0
(char *i)
{
  outs(margin);
  outs(i);
  outnl();
  return;
}

/* one operand */
void ins1
(char *i, int le1, where a1)
{
  outs(margin);
  outs(i);
  outs(spx);
  operand(le1, a1, 1, 0);
  outnl();
  return;
}

/* one operand, which is indirect */
void ins1ind
(char *i, int le1, where a1)
{
  outs(margin);
  outs(i);
  outs(spx);
  outs("*");
  operand(le1, a1, 1, 0);
  outnl();
  return;
}

/* one operand, which is immediate */
void ins1lit
(char *i, int le1, where a1)
{
  outs(margin);
  outs(i);
  outs(spx);
  operand(le1, a1, 1, 1);
  outnl();
  return;
}

/* two operands */
void ins2
(char *i, int le1, int le2, where a1, where a2)
{
  outs(margin);
  outs(i);
  outs(spx);
  operand(le1, a1, 1, 0);
  outs(sep);
  operand(le2, a2, 1, 0);
  outnl();
  return;
}

/* three operands */
void ins3
(char *i, int le1, int le2, int le3, where a1, where a2, where a3)
{
  outs(margin);
  outs(i);
  outs(spx);
  operand(le1, a1, 1, 0);
  outs(sep);
  operand(le2, a2, 1, 0);
  outs(sep);
  operand(le3, a3, 1, 0);
  outnl();
  return;
}


void simplest_set_lab
(int labno)
{
  outs(local_prefix);
  outn((long)labno);
  outs(":");
  outnl();
}


void simple_set_label
(int labno)
{
#ifdef CHECKIMPROVE
  if (labno == last_jump_label)
    failer("redundant jump");
#endif
#ifndef NEWDIAGS
  /* eliminate immediately previous jump to this label */
  if (diag == DIAG_NONE && labno == last_jump_label) {
		out_set_pos(last_jump_pos);
  };
#endif

  cond1_set = 0;
  cond2_set = 0;
  outs(local_prefix);
  outn ((long)labno);		/* the label no is held in the ptr field
				*/
  outs(":");
  outnl();
/* Removed for experiments: improves compress?
  keep_short = 1;
*/
  return;
}

/* set label described by the jump record jr */
void set_label
(exp jr)
{
  simple_set_label(ptno(jr));
}

/*  jump record: exp
    pt - label;
    last - forward;
    son - stack_dec;
    prop - floating stack position
*/

void discard_fstack
(void)
{
  outs(" fstp %st(0)");
  outnl();
  pop_fl;
  return;
}

void discard_st1
(void)
{
  outs(" fstp %st(1)");
  outnl();
  pop_fl;
}


/* output a jump to the label described by
   jump record jr */
void jump
(exp jr, int with_fl_reg)
{
  int  fs_dest = (int)fstack_pos_of(jr);
  int  good_fs = fstack_pos;
  int  good_sd = stack_dec;
  if (fs_dest < first_fl_reg)
    failer(FSTACK_UNSET);
  if (with_fl_reg) {		/* jumping with a floating value */
    /* clear off any unwanted stack registers */
    while (fstack_pos > (fs_dest + 1))
      discard_st1();
    fstack_pos = good_fs - 1;
  }
  else {
    /* clear off any unwanted stack registers */
    while (fstack_pos > fs_dest)
      discard_fstack();
    fstack_pos = good_fs;
  };

  if (sonno(jr) > stack_dec) {
    add(slongsh, mw(zeroe,(sonno(jr) -stack_dec) / 8), sp, sp);
    stack_dec = sonno(jr);
  }

  reset_fpucon();
  stack_dec = good_sd;

#ifndef NEWDIAGS
  last_jump_pos = out_tell_pos();
#endif
  outs(margin);
  outs(jmp);
  outs(spx);
  outs(local_prefix);
  outn((long)ptno(jr));
  outnl();
  last_jump_label = ptno(jr);
  return;
}

static char* xse = "<=0";	/* no corresponding jump instruction */
static char* xnse = ">0";


/* output code for a branch instruction
   determined by test_no. The test is
   signed if sg is true */
static char *out_branch
(int sg, int test_no, int shnm)
{
  if (shnm >= shrealhd && shnm <= doublehd) {
    switch (test_no) {
      case 1:
	return jne;

      case 2:
	return jne;

      case 3:
	return jpe;

      case 4:
	return jpe;

      case 5:
	return jpe;

      case 6:
	return jpo;

      case 7:
	return jpo;

      case 8:
	return jpo;

      case 9:
	return je;

      case 10:
	return je;

      case 11:
	return jne;

      case 12:
	return je;

      case 13:
	return jne;

      case 14:
	return je;

      default:
	failer(BAD_TESTNO);
    };
  };

  if (sg) {
    switch (test_no) {
      case 1:
	return sg < 0 ? xse : jle;
      case 2:
	return sg < 0 ? js : jl;

      case 3:
	return sg < 0 ? jns : jge;

      case 4:
	return sg < 0 ? xnse : jg;

      case 5:
	return jne;

      case 6:
	return je;

      default:
	failer(BAD_TESTNO);
    };
  }
  else {
    switch (test_no) {
      case 1:
	return jbe;

      case 2:
	return jb;

      case 3:
	return jae;

      case 4:
	return ja;

      case 5:
	return jne;

      case 6:
	return je;

      default:
	failer(BAD_TESTNO);
    };
  };
  return (char *)0;
}

void simple_branch
(char *j, int labno)
{
  outs(margin);
  outs(j);
  outs(spx);
  outs(local_prefix);
  outn((long)labno);
  outnl();

}


/* output conditional jump to jr. testno
   specifies kind of test. sg is 1 if
   signed arithmetic, 0 unsigned, -1 if
   signed vs zero (ignoring overflow).
   shnm name of shape */
void branch
(int test_no, exp jr, int sg, int shnm)
{
  int  fs_dest = (int)fstack_pos_of(jr);
  int  good_fs = fstack_pos;
  int  good_fpucon = fpucon;
  if (fs_dest < first_fl_reg)
    failer(FSTACK_UNSET);
  if (fstack_pos > fs_dest || sonno(jr)!= stack_dec || fpucon != normal_fpucon
	|| cmp_64hilab >= 0) {
	/* floating point stack or call stack need attention */
    int  nl = next_lab();
    int inv_test_no = (flpt_always_comparable ||
			(shnm < shrealhd || shnm > doublehd))
				?(int)int_inverse_ntest[test_no]
				:(int)real_inverse_ntest[test_no];

    char* cj = out_branch((cmp_64hilab >= 0 ? 0 : sg), inv_test_no, shnm);
    if (*cj == 'j') {
      simple_branch(cj, nl);
    }
    else	/* compare with zero, ignoring overflow */
    if (*cj == '>') {
      int nl1 = next_lab();
      simple_branch(js, nl1);
      simple_branch(jne, nl);
      simplest_set_lab(nl1);
    }
    else {
      simple_branch(js, nl);
      simple_branch(je, nl);
    }

    if (cmp_64hilab >= 0) {
      int nl2 = ptno(jr);
      if (shnm != s64hd)
	failer("uncompleted 64-bit comparison");
      if (fstack_pos > fs_dest || sonno(jr)!= stack_dec || fpucon != normal_fpucon) {
	nl2 = next_lab();
	simplest_set_lab(nl2);
      }
      jump(jr, 0);
      simplest_set_lab(cmp_64hilab);
      simple_branch(out_branch(1, test_no, shnm), nl2);
      cmp_64hilab = -1;
    }
    else
      jump(jr, 0);

    fstack_pos = good_fs;
    fpucon = good_fpucon;
    simplest_set_lab(nl);
    return;
  };

  {
    char* cj = out_branch(sg, test_no, shnm);
    if (*cj == 'j') {
      simple_branch(cj, ptno(jr));
    }
    else	/* compare with zero, ignoring overflow */
    if (*cj == '>') {
      int nl1 = next_lab();
      simple_branch(js, nl1);
      simple_branch(jne, ptno(jr));
      simplest_set_lab(nl1);
    }
    else {
      simple_branch(js, ptno(jr));
      simple_branch(je, ptno(jr));
    }
  }
  return;
}

void setcc
(int test_no, int sg, int shnm)
{
  char * b;
  if (cmp_64hilab >= 0) {
    int chl = cmp_64hilab;
    int nl = next_lab();
    if (shnm != s64hd)
      failer("uncompleted 64-bit comparison");
    cmp_64hilab = -1;
    setcc(test_no, 0, ulonghd);
    simple_branch(jmp, nl);
    simplest_set_lab(chl);
    setcc(test_no, sg, slonghd);
    simplest_set_lab(nl);
  }

  b = out_branch(sg, test_no, shnm);
  if (*b != 'j')
    failer(NO_SETCC);
  outs(margin);
  outs("set");
  outs(&b[1]);
  outs(spx);
  outs(reg_name_byte[0]);
  outnl();
  return;
}

/* output conditional jump to jr if overflow
   sg is 1 if signed arithmetic, 0 unsigned */
void jmp_overflow
(exp jr, int sg, int inv)
{
  int  fs_dest = (int)fstack_pos_of(jr);
  int  good_fs = fstack_pos;
  int  good_fpucon = fpucon;
  if (fs_dest < first_fl_reg)
    failer(FSTACK_UNSET);
  if (fstack_pos > fs_dest || sonno(jr)!= stack_dec || fpucon != normal_fpucon) {
	/* floating point stack or call stack need attention */
    int  nl = next_lab();
    if (sg)
      simple_branch(jno, nl);
    else
      simple_branch((inv ? jb : jae), nl);
    jump(jr, 0);
    fstack_pos = good_fs;
    fpucon = good_fpucon;
    simplest_set_lab(nl);
    return;
  };
  if (sg)
    simple_branch(jo, ptno(jr));
  else
    simple_branch((inv ? jae : jb), ptno(jr));
  return;
}


/* software interrupt */
void trap_ins
(int s)
{
  if (!avoid_intov) {
    if (s == f_overflow) {
      ins0 ("int $4");	/* numeric interrupt */
      return;
    }
  } else if (avoid_intov == 16) {
    if (s == f_overflow) {
      ins0 ("int $16");	/* mimic floating point interrupt */
      return;
    }
  }

  if (cont_err_handler == nilexp) {
    cont_err_handler = make_extn("__trans386_errhandler", f_proc, 1);
    if (!PIC_code)
      cont_err_handler = getexp(f_proc, nilexp, 1, cont_err_handler, nilexp, 0, 0, cont_tag);
  }
  ins1(pushl, 32, mw(zeroe, s));
#ifdef NEWDWARF
  if (diag == DIAG_DWARF2 && no_frame)
    dw2_track_push();
#endif
  ins2(movl, 32, 32, mw(cont_err_handler, 0), reg0);
  if (PIC_code)
    ins1ind(call, 32, ind_reg0);
  else
    ins1ind(call, 32, reg0);
  return;
}


/* output software interrupt if overflow
   sg is 1 if signed arithmetic, 0 unsigned */
void trap_overflow
(int sg, int inv)
{
    if (avoid_intov) {
        int nl = next_lab();
        if (sg)
          simple_branch(jno, nl);
        else
          simple_branch((inv ? jb : jae), nl);
        trap_ins(f_overflow);
        simplest_set_lab(nl);
    } else {
      if (sg)
        ins0(into);
      else {
        int nl = next_lab();
        simple_branch((inv ? jb : jae), nl);
        trap_ins(f_overflow);
        simplest_set_lab(nl);
      }
    }
}


/* conditional software interrupt
   sg is 1 if signed arithmetic
   shnm name of shape */
void test_trap
(int test_no, int sg, int shnm)
{
  int nl = next_lab();
  int inv_test_no = (flpt_always_comparable ||
			(shnm < shrealhd || shnm > doublehd))
				?(int)int_inverse_ntest[test_no]
				:(int)real_inverse_ntest[test_no];
  simple_branch(out_branch(sg, inv_test_no, shnm), nl);
  trap_ins(f_overflow);
  simplest_set_lab(nl);
  return;
}



/* special output for doing multiply by
   using index instructions */
void mult_op
(int inc, where rmain, where rind, int sc, where dest)
{
  outs(margin);
  outs("leal");
  outs(spx);
  if (inc != 0)
    outn((long)inc);
  outs("(");
  if (name(rmain.where_exp)!= val_tag ||
     (no(rmain.where_exp) + rmain.where_off)!= 0)
    operand(32, rmain, 1, 0);
  outs(",");
  operand(32, rind, 1, 0);
  if (sc != 1) {
    outs(",");
    outn((long)sc);
  };
  outs("),");

  if (inmem(dest)) {
    operand(32, reg0, 1, 0);
    outnl();
    invalidate_dest(reg0);
    end_contop();
    move(slongsh, reg0, dest);
  }
  else {
    operand(32, dest, 1, 0);
    outnl();
    end_contop();
  };
  return;
}

/* output the case switch jump and the jump table */
void caseins
(int sz, exp arg, int min, int max, int *v, int exhaustive, int in_eax, exp case_exp)
{
  int tab;
  int absent;
  where a;
  int need_label_flag=0;
  exp next= short_next_jump(case_exp);
  if (next != nilexp && name(next) ==goto_tag)
  {
    exp lab=final_dest(pt(next));
    absent=ptno(pt(son(lab)));
  }
  else
  {
    absent = (exhaustive)? -1 : next_lab();
    need_label_flag=1;
  }

  tab = next_lab();
  a = mw(arg, 0);

  if (inmem(mw(arg, 0)) || sz != 32) {
    if (!in_eax)
      change_var(slongsh, a, reg0);
    a = reg0;
  }

  /* the switch jump */
  out_switch_jump(tab, a, min);

  /* table of offsets */
  out_switch_table(tab, min, max, v, absent);

  if (!exhaustive && need_label_flag==1) {
    /*  label for default of switch; continue here */
    outs(local_prefix);
    outn((long)absent);
    outs(":");
    outnl();
#ifdef NEWDWARF
    START_BB();
#endif
  };
  return;
}


void const_intnl
(int addr, int lab, int off)
{
  if (PIC_code)
   {
    outs(local_prefix);
    outn((long)lab);
    outs("@GOTOFF");
    if (off != 0) {
      outs("+");
      outn((long)off / 8);
    };
    outs("(%ebx)");
    return;
   }
  else
   {
    if (addr)
      outs("$");
    outs(local_prefix);
    outn((long)lab);
    if (off != 0) {
      outs("+");
      outn((long)off / 8);
    };
    return;
  };
}

void load_stack0
(void)
{
  outs(" fld %st(0)");
  outnl();
  return;
}

void outbp
(void)
{
  outs("%ebp");
}

void set_stack_from_bp
(void)
{
  outs(margin);
  outs(leal);
  outs(spx);
  outn((long)stack_dec/8);
  outs("-");
  outs(local_prefix);
  outs("disp");
  outn((long)crt_proc_id);
  outs("(%ebp)");
  outs(sep);
  outs("%esp");
  outnl();
  return;
}

void testah
(int mask)
{
  outs(" testb $");
  outn((long)mask);
  outs(",%ah");
  outnl();
  return;
}

exp make_extn
(char * n, shape s, int v)
{
  dec * g = (dec *)(xmalloc(sizeof(dec)));
  exp id = getexp(s, nilexp, 1, nilexp, nilexp, 0, 0, ident_tag);
  exp nme = getexp(s, nilexp, 1, id, nilexp, 0, 0, name_tag);
  setglob(id);
  if (v) {
	if (keep_PIC_vars) {
          setvar(id);
	} else if (PIC_code) {
          sh(id) = f_pointer(f_alignment(s));
	} else {
          setvar(id);
	}
  }
  brog(id) = g;
  if (prefix_length != 0) {
    int nl = (int)strlen(n);
    int j;
    char * newn = (char *)xcalloc((nl + prefix_length + 1), sizeof(char));
    for (j = 0; j < prefix_length; ++j)
      newn[j] = name_prefix[j];
    for (j = 0; j < nl; ++j)
      newn[j+prefix_length] = n[j];
    newn[nl+prefix_length] = 0;
    n = newn;
  }
  g -> dec_u.dec_val.dec_exp = id;
  g -> dec_u.dec_val.dec_id = n;
  g -> dec_u.dec_val.extnamed = 1;
  return nme;
}



/* shift or rotate 64 bits in reg0/reg1 */
void rotshift64
(int shft, int sig, where wshift)
{
  if (name(wshift.where_exp) == val_tag) {	/* no of places is constant */
    int places = no(wshift.where_exp) + wshift.where_off;
    if (places >= 32) {
      places -= 32;
      switch (shft) {
	case 0:
	  if (places)
	    ins2(shll, 8, 32, mw(zeroe,places), reg0);
	  move(ulongsh, reg0, reg1);
	  move(ulongsh, zero, reg0);
	  return;
	case 1:
	  move(ulongsh, reg1, reg0);
	  if (places)
	    ins2((sig ? sarl : shrl), 8, 32, mw(zeroe,places), reg0);
	  if (sig)
	    ins2(sarl, 8, 32, mw(zeroe,31), reg1);
	  else
	    move(ulongsh, zero, reg1);
	  return;
	default: {
	  if (!places) {
	    ins2(xchg, 32, 32, reg0, reg1);
	    return;
	  }
	  places = 32 - places;
	  shft = 5 - shft;	/* reverse rotate */
	}
      }
    };
    if (places == 0)
      return;
    switch (shft) {	/* between 1 and 31 places */
      case 0:
	ins3(shldl, 8, 32, 32, mw(zeroe,places), reg0, reg1);
	ins2(shll, 8, 32, mw(zeroe,places), reg0);
	return;
      case 1:
	ins3(shrdl, 8, 32, 32, mw(zeroe,places), reg1, reg0);
	ins2((sig ? sarl : shrl), 8, 32, mw(zeroe,places), reg1);
	return;
      default: {
	char * dsh = (shft == 2 ? shrdl : shldl);
        extra_stack += 64;
	check_stack_max;
	ins0(pushedx);
#ifdef NEWDWARF
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_push();
#endif
	ins0(pusheax);
#ifdef NEWDWARF
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_push();
#endif
	ins3(dsh, 8, 32, 32, mw(zeroe,places),
		reg1, mw(ind_sp.where_exp,-32));
	ins3(dsh, 8, 32, 32, mw(zeroe,places),
		reg0, mw(ind_sp.where_exp,-64));
	ins0(popeax);
#ifdef NEWDWARF
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_pop();
#endif
	ins0(popedx);
#ifdef NEWDWARF
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_pop();
#endif
	invalidate_dest(ind_sp);
        extra_stack -= 64;
	return;
      }
    }
  };
  {				/* number of places in reg2 */
    int lablow = next_lab();
    int labend = next_lab();
    ins2(cmpl, 32, 32, mw(zeroe,32), reg2);
    simple_branch(jl, lablow);
    switch (shft) {
      case 0:
	ins2(subl, 32, 32, mw(zeroe,32), reg2);
	ins2(shll, 8, 32, reg2, reg0);
	move(ulongsh, reg0, reg1);
	move(ulongsh, zero, reg0);
	break;
      case 1:
	ins2(subl, 32, 32, mw(zeroe,32), reg2);
	move(ulongsh, reg1, reg0);
	ins2((sig ? sarl : shrl), 8, 32, reg2, reg0);
	if (sig)
	  ins2(sarl, 8, 32, mw(zeroe,31), reg1);
	else
	  move(ulongsh, zero, reg1);
	break;
      default: {
	int labx = next_lab();
	char * dsh = (shft == 2 ? shldl : shrdl);	/* reversed rotate */
	simple_branch(je, labx);
	ins2(subl, 32, 32, mw(zeroe,64), reg2);
	ins1(negl, 32, reg2);
        extra_stack += 64;
	check_stack_max;
	ins0(pushedx);
#ifdef NEWDWARF
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_push();
#endif
	ins0(pusheax);
#ifdef NEWDWARF
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_push();
#endif
	ins3(dsh, 8, 32, 32, reg2, reg1, mw(ind_sp.where_exp,-32));
	ins3(dsh, 8, 32, 32, reg2, reg0, mw(ind_sp.where_exp,-64));
	ins0(popeax);
#ifdef NEWDWARF
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_pop();
#endif
	ins0(popedx);
#ifdef NEWDWARF
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_pop();
#endif
	invalidate_dest(ind_sp);
        extra_stack -= 64;
	simple_branch(jmp, labend);
	simplest_set_lab(labx);
	ins2(xchg, 32, 32, reg0, reg1);
      }
    }
    simple_branch(jmp, labend);
    simplest_set_lab(lablow);
    switch (shft) {	/* between 0 and 31 places */
      case 0:
	ins3(shldl, 8, 32, 32, reg2, reg0, reg1);
	ins2(shll, 8, 32, reg2, reg0);
	break;
      case 1:
	ins3(shrdl, 8, 32, 32, reg2, reg1, reg0);
	ins2((sig ? sarl : shrl), 8, 32, reg2, reg1);
	break;
      default: {
	char * dsh = (shft == 2 ? shrdl : shldl);
        extra_stack += 64;
	check_stack_max;
	ins0(pushedx);
#ifdef NEWDWARF
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_push();
#endif
	ins0(pusheax);
#ifdef NEWDWARF
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_push();
#endif
	ins3(dsh, 8, 32, 32, reg2, reg1, mw(ind_sp.where_exp,-32));
	ins3(dsh, 8, 32, 32, reg2, reg0, mw(ind_sp.where_exp,-64));
	ins0(popeax);
#ifdef NEWDWARF
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_pop();
#endif
	ins0(popedx);
#ifdef NEWDWARF
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_pop();
#endif
	invalidate_dest(ind_sp);
        extra_stack -= 64;
      }
    }
    simplest_set_lab(labend);
  };
  return;
}
