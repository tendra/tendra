/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * Defines the general routines for outputting instructions and labels.
 */

#include <string.h>
#include <stdlib.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/xalloc.h>

#include <local/out.h>
#include <local/code.h>

#ifdef DWARF2
#include <local/dw2_config.h>
#endif

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/table_fns.h>
#include <reader/basicread.h>
#include <reader/readglob.h>
#include <reader/externs.h>

#include <construct/exp.h>
#include <construct/installglob.h>
#include <construct/install_fns.h>
#include <construct/machine.h>
#include <construct/label_ops.h>

#include <flpt/flpt.h>

#include <main/flags.h>
#include <main/print.h>

#include <refactor/refactor.h>

#include "localtypes.h"
#include "assembler.h"
#include "operand.h"
#include "ops.h"
#include "make_code.h"
#include "cproc.h"
#include "reg_record.h"
#include "instrs.h"
#include "instr.h"

#ifdef DWARF2
#include "dw2_extra.h"
#include <dwarf2/dw2_lines.h>
#endif

typedef union eu_u {int i; exp e;} punner;

#define fstack_base 8

/* All variables initialised */

int  extra_stack = 0;	/* init by init_all */
int max_extra_stack = 0;	/* init by cproc */
int no_frame;		/* init by cproc */
#ifdef TDF_DIAG3
static long  last_jump_pos;	/* set locally */
#endif
int avoid_intov; /* No software interrupts */

static exp cont_err_handler = NULL;


static char *reg_name_long[8] = {
  "%eax", "%edx", "%ecx", "%ebx", "%edi", "%esi", "%ebp", "%esp"
};

static char *reg_name_word[7] = {
  "%ax", "%dx", "%cx", "%bx", "%di", "%si", "%bp"
};

static char *reg_name_byte[7] = {
  "%al", "%dl", "%cl", "%bl", "%??", "%??", "%??"
};

static char *fl_reg_name[8] = {
  "%st", "%st(1)", "%st(2)", "%st(3)", "%st(4)", "%st(5)", "%st(6)",
  "%st(7)",
};

void temp_push_fl
(void)
{
  ++fstack_pos;
}
void temp_pop_fl
(void)
{
  --fstack_pos;
}

/*
 * Outputs a floating point number.
 */
void outreal
(exp e)
{
  flt * f = &flptnos[no(e)];
  int sw = sh(e)->tag - shrealhd;
  r2l longs;

  longs = real2longs_IEEE(f, sw);

  switch (sw) {
    case 0:
      asm_printf("0x%x\n", longs.i1);
      break;
    case 1:
      asm_printf("0x%x,0x%x\n", longs.i1, longs.i2);
      break;
    case 2:
      asm_printf("0x%x,0x%x,0x%x\n", longs.i1, longs.i2, longs.i3);
      break;
  }
}

/*
 * Output operand i (in bytes) relative to stack pointer
 * uses address relative to frame pointer if it might be shorter
 */
void rel_sp
(int i, int b)
{
  int  n = i + (extra_stack / 8);
  if (!must_use_bp) {
				/* if we might use alloca all displacements must be relative to frame pointer */
    if (n == 0) {
      asm_printf("(%s", "%esp");
      if (b)
	asm_printf(")");
      return;
    }
    if (n <= 127 || no_frame || stack_aligned_8byte) {
				/* use stack pointer if displacement from it is small */
      asm_printf("%d(%s", n, "%esp");
      if (b)
	asm_printf(")");
      return;
    }
  }
  /* otherwise use displacement from frame pointer */
  asm_printf("%d-%sdisp%d(%s", i + (stack_dec / 8), local_prefix, crt_proc_id, "%ebp");
  if (b)
    asm_printf(")");
}

/*
 * Output operand i (in bytes) relative to stack pointer
 */
void rel_cp
(int i, int b)
{
  int  n = i + (extra_stack / 8);
  if (n == 0) {
    asm_printf("(%s", "%esp");
    if (b)
      asm_printf(")");
    return;
  }
  asm_printf("%d(%s", n, "%esp");
  if (b)
    asm_printf(")");
}

/*
 * Output operand relative to frame pointer
 */
void rel_ap
(int i, int b)
{
  if (no_frame) {
    asm_printf("%d+%sdisp%d(%s", i + ((extra_stack - stack_dec) / 8), local_prefix, crt_proc_id, "%esp");
    if (b)
      asm_printf(")");
    return;
  }
  else {
    asm_printf("%d(%s", i + 4, "%ebp");
    if (b)
      asm_printf(")");
    return;
  }
}

/*
 * Output operand relative to frame pointer and push space
 */
void rel_ap1
(int i, int b)
{
  if (no_frame) {
    asm_printf("%d+%sfcwdisp%d(%s", i + (extra_stack - stack_dec) / 8, local_prefix, crt_proc_id, "%esp");
    if (b)
      asm_printf(")");
    return;
  }
  else {
    asm_printf("%d-%sfcwdisp%d(%s", i, local_prefix, crt_proc_id, "%ebp");
    if (b)
      asm_printf(")");
    return;
  }
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

/*
 * Output a register address, regs is a bit pattern,
 * rdisp is an offset in bit units.
 * le tells us how to refer to the register (eg al or ax or eax)
 */
void regn
(int regs, int rdisp, exp ldname, int le)
{
  int  z;
  char **rn;
  UNUSED(rdisp);
  z = get_reg_no(regs);

  if (ldname->tag == name_tag && islastuse(ldname))
    regsinuse = regsinuse & ~regs;

  if (z >= first_fl_reg) {
    if (z == first_fl_reg) {
      asm_printf("%s", fl_reg_name[0]);
      return;
    }
    if (fstack_pos > 16) {
      error(ERR_INTERNAL, "bad floating point stack");
      exit(EXIT_FAILURE);
    }
    asm_printf("%s", fl_reg_name[fstack_pos - z]);
    /*
	 * Variables held in the floating point registers have to be addressed
     * relative to the current stack position, because the registers are a
     * stack as well as a register bank
	 */
    return;
  }

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
  }
  asm_printf("%s", rn[z]);			/* this outputs the register name */
}

/* Output a displacement from register operand */
void ind_reg
(int regs, int rdisp, int offset, exp ldname, int b)
{
  if (regs == 128)
    offset += extra_stack;

  if (offset == 0) {
    asm_printf("(");
    regn(regs, rdisp, ldname, 32);
    if (b)
      asm_printf(")");
  }
  else {
    asm_printf("%d(", offset / 8);
    regn(regs, rdisp, ldname, 32);
    if (b)
      asm_printf(")");
  }
}

/* Use indexed addressing */
void index_opnd
(where whmain, where wh, int sc)
{
  exp m = whmain.where_exp;
  if ((m->tag == name_tag && ptno(son(m)) == reg_pl) ||
     (m->tag == cont_tag && son(m)->tag == name_tag &&
	isvar(son(son(m))) && ptno(son(son(m))) == reg_pl))
    asm_printf("(");
  operand(32, whmain, 0, 0);
  asm_printf(",");
  operand(32, wh, 1, 0);
  if (sc != 1) {
    asm_printf(",%d", sc);
  }
  asm_printf(")");
}

/* Output an external operand */
void extn
(exp id, int off, int b)
{
  dec * et;

  et = brog(id);

  if (PIC_code)
   {
     char * got;
     if (et -> extnamed)
        got = "GOT";
     else
        got = "GOTOFF";
     asm_printf("%s@%s", et -> name, got);
     if (off != 0)
      {
        asm_printf("+%d", off / 8);
      }
     asm_printf("(%s", "%ebx");
     if (b)
       asm_printf(")");
     return;
   }

  if (off == 0)
    asm_printf("%s", et -> name);
  else {
    asm_printf("%s+%d", et -> name, off / 8);
  }
  if (!b)
    asm_printf("(");
}

/* An integer constant */
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
  }
  asm_printf("$%d", k & mask);
}

/* An external literal */
void const_extn
(exp ident, int noff)
{
  if (!PIC_code)
    asm_printf("$");
  extn(ident, noff, 1);
}

/* An external literal */
void proc_extn
(exp id, int off)
{
  if (PIC_code)
   {
     dec * et;
     et = brog(id);
     if (off == 0)
       asm_printf("%s", et -> name);
     else {
        asm_printf("%d+%s", off / 8, et->name);
     }
     if (et -> extnamed)
        asm_printf("@PLT");
   }
  else
   {
     asm_printf("$");
     extn(id, off, 1);
   }
}

void ldisp
(void)
{
   asm_printf("%sdisp%d", local_prefix, crt_proc_id);
}

void label_operand
(exp e)
{
  exp labst = pt(e);

  if (ptno(labst) == 0)
    ptno(labst) = next_lab();
  asm_printf("$%sV0x%lx", local_prefix, ptno(labst));
}

void set_lv_label
(exp e)
{
  if (ptno(e) == 0)
    ptno(e) = next_lab();

  min_rfree |= 0x78;  /* save all callee registers */

  asm_label("%sV0x%lx", local_prefix, ptno(e));
}

void set_env_off
(int s, exp n)
{
  punner l;
  l.e = n;
  asm_printf(".set %sO0x%x,", local_prefix, l.i); /* produce an identifying number */
  if (s<4)
   {
    asm_printf("%d-%sdisp%d", -s / 8, local_prefix, crt_proc_id);
   }
  else
   asm_printf("%d", s / 8);
  asm_printf("\n");
}

void envoff_operand
(exp e, int off)
{
  punner l;
  l.e = e;
  if (off != 0)
   {
    asm_printf("%d+", off);
   }
  asm_printf("%sO0x%x", local_prefix, l.i); /* produce an identifying number */
}

void envsize_operand
(exp e)
{
  dec * et = brog(e);
  asm_printf("%sESZ%s", local_prefix, et->name);
}

/* 80386 instruction with no operands */
void ins0
(char *i)
{
  asm_printf("\t%s\n", i);
}

/* One operand */
void ins1
(char *i, int le1, where a1)
{
  asm_printf("\t%s ", i);
  operand(le1, a1, 1, 0);
  asm_printf("\n");
}

/* One operand, which is indirect */
void ins1ind
(char *i, int le1, where a1)
{
  asm_printf("\t%s *", i);
  operand(le1, a1, 1, 0);
  asm_printf("\n");
}

/* One operand, which is immediate */
void ins1lit
(char *i, int le1, where a1)
{
  asm_printf("\t%s ", i);
  operand(le1, a1, 1, 1);
  asm_printf("\n");
}

/* Two operands */
void ins2
(char *i, int le1, int le2, where a1, where a2)
{
  asm_printf("\t%s ", i);
  operand(le1, a1, 1, 0);
  asm_printf(",");
  operand(le2, a2, 1, 0);
  asm_printf("\n");
}

/* Three operands */
void ins3
(char *i, int le1, int le2, int le3, where a1, where a2, where a3)
{
  asm_printf("\t%s ", i);
  operand(le1, a1, 1, 0);
  asm_printf(",");
  operand(le2, a2, 1, 0);
  asm_printf(",");
  operand(le3, a3, 1, 0);
  asm_printf("\n");
}

void simplest_set_lab
(int labno)
{
  asm_label("%s%d", local_prefix, labno);
}

void simple_set_label
(int labno)
{
  cond1_set = false;
  cond2_set = false;
  asm_label("%s%d", local_prefix, labno); /* the label no is held in the ptr field */
/* Removed for experiments: improves compress?
  keep_short = true;
*/
}

/* Set label described by the jump record jr */
void set_label
(exp jr)
{
  simple_set_label(ptno(jr));
}

/*
 * jump record: exp
 *
 *  pt   - label;
 *  last - forward;
 *  son  - stack_dec;
 *  prop - floating stack position
 */
void discard_fstack
(void)
{
  asm_printop("fstp %s(0)", "%st");
  pop_fl;
}

void discard_st1
(void)
{
  asm_printop("fstp %s(1)", "%st");
  pop_fl;
}

/*
 * Output a jump to the label described by jump record jr
 */
void jump
(exp jr, int with_fl_reg)
{
  int  fs_dest = (int)fstack_pos_of(jr);
  int  good_fs = fstack_pos;
  int  good_sd = stack_dec;
  if (fs_dest < first_fl_reg)
    error(ERR_INTERNAL, "floating point stack level not set");
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
  }

  if (sonno(jr) > stack_dec) {
    add(slongsh, mw(zeroe,(sonno(jr) -stack_dec) / 8), sp, sp);
    stack_dec = sonno(jr);
  }

  reset_fpucon();
  stack_dec = good_sd;

#ifdef TDF_DIAG3
  last_jump_pos = out_tell_pos();
#endif
  asm_printf("\t%s %s%ld\n", jmp, local_prefix, (long) ptno(jr));
}

static char* xse = "<=0";	/* no corresponding jump instruction */
static char* xnse = ">0";

/*
 * Output code for a branch instruction determined by test_no.
 * The test is signed if sg is true
 */
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
	error(ERR_INTERNAL, "bad test number");
    }
  }

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
	error(ERR_INTERNAL, "bad test number");
    }
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
	error(ERR_INTERNAL, "bad test number");
    }
  }
  return NULL;
}

void simple_branch
(char *j, int labno)
{
  asm_printf("\t%s %s%d\n", j, local_prefix, labno);
}

/*
 * Output conditional jump to jr. testno specifies kind of test.
 * sg is 1 if signed arithmetic, 0 unsigned,
 * -1 if signed vs zero (ignoring overflow).
 * shnm name of shape
 */
void branch
(int test_no, exp jr, int sg, int shnm)
{
  int  fs_dest = (int)fstack_pos_of(jr);
  int  good_fs = fstack_pos;
  int  good_fpucon = fpucon;
  if (fs_dest < first_fl_reg)
    error(ERR_INTERNAL, "floating point stack level not set");
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
	error(ERR_INTERNAL, "uncompleted 64-bit comparison");
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
  }

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
}

void setcc
(int test_no, int sg, int shnm)
{
  char * b;
  if (cmp_64hilab >= 0) {
    int chl = cmp_64hilab;
    int nl = next_lab();
    if (shnm != s64hd)
      error(ERR_INTERNAL, "uncompleted 64-bit comparison");
    cmp_64hilab = -1;
    setcc(test_no, 0, ulonghd);
    simple_branch(jmp, nl);
    simplest_set_lab(chl);
    setcc(test_no, sg, slonghd);
    simplest_set_lab(nl);
  }

  b = out_branch(sg, test_no, shnm);
  if (*b != 'j')
    error(ERR_INTERNAL, "no setcc");
  asm_printf("\tset%s %s\n", &b[1], reg_name_byte[0]);
}

/*
 * Output conditional jump to jr if overflow
 * sg is 1 if signed arithmetic, 0 unsigned
 */
void jmp_overflow
(exp jr, int sg, int inv)
{
  int  fs_dest = (int)fstack_pos_of(jr);
  int  good_fs = fstack_pos;
  int  good_fpucon = fpucon;
  if (fs_dest < first_fl_reg)
    error(ERR_INTERNAL, "floating point stack level not set");
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
  }
  if (sg)
    simple_branch(jo, ptno(jr));
  else
    simple_branch((inv ? jae : jb), ptno(jr));
}

/* Software interrupt */
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

  if (cont_err_handler == NULL) {
    cont_err_handler = make_extn("__trans386_errhandler", f_proc, 1);
    if (!PIC_code)
      cont_err_handler = getexp(f_proc, NULL, 1, cont_err_handler, NULL, 0, 0, cont_tag);
  }
  ins1(pushl, 32, mw(zeroe, s));
#ifdef DWARF2
  if (diag == DIAG_DWARF2 && no_frame)
    dw2_track_push();
#endif
  ins2(movl, 32, 32, mw(cont_err_handler, 0), reg0);
  if (PIC_code)
    ins1ind(call, 32, ind_reg0);
  else
    ins1ind(call, 32, reg0);
}

/*
 * Output software interrupt if overflow
 * sg is 1 if signed arithmetic, 0 unsigned
 */
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

/*
 * Conditional software interrupt
 * sg is 1 if signed arithmetic shnm name of shape
 */
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
}

/*
 * Special output for doing multiply by using index instructions
 */
void mult_op
(int inc, where rmain, where rind, int sc, where dest)
{
  asm_printf("\tleal ");
  if (inc != 0)
    asm_printf("%d", inc);
  asm_printf("(");
  if (rmain.where_exp->tag!= val_tag ||
     (no(rmain.where_exp) + rmain.where_off)!= 0)
    operand(32, rmain, 1, 0);
  asm_printf(",");
  operand(32, rind, 1, 0);
  if (sc != 1) {
    asm_printf(",%d", sc);
  }
  asm_printf("),");

  if (inmem(dest)) {
    operand(32, reg0, 1, 0);
    asm_printf("\n");
    invalidate_dest(reg0);
    end_contop();
    move(slongsh, reg0, dest);
  }
  else {
    operand(32, dest, 1, 0);
    asm_printf("\n");
    end_contop();
  }
}

/* Output the case switch jump and the jump table */
void caseins
(int sz, exp arg, int min, int max, int *v, int exhaustive, int in_eax, exp case_exp)
{
  int tab;
  int absent;
  where a;
  bool need_label_flag = false;
  exp next= short_next_jump(case_exp);
  if (next != NULL && next->tag ==goto_tag)
  {
    exp lab=final_dest(pt(next));
    absent=ptno(pt(son(lab)));
  }
  else
  {
    absent = (exhaustive)? -1 : next_lab();
    need_label_flag = true;
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

  if (!exhaustive && need_label_flag) {
    /*  label for default of switch; continue here */
    asm_label("%s%d", local_prefix, absent);
#ifdef DWARF2
    if (diag == DIAG_DWARF2) {
      dw2_start_basic_block();
    }
#endif
  }
}

void const_intnl
(int addr, int lab, int off)
{
  if (PIC_code)
   {
    asm_printf("%s%d@GOTOFF", local_prefix, lab);
    if (off != 0) {
      asm_printf("+%d", off / 8);
    }
    asm_printf("(%s)", "%ebx");
    return;
   }
  else
   {
    if (addr)
      asm_printf("$");
    asm_printf("%s%d", local_prefix, lab);
    if (off != 0) {
      asm_printf("+%d", off / 8);
    }
    return;
  }
}

void load_stack0
(void)
{
  asm_printop("fld %s(0)", "%st");
}

void outbp
(void)
{
  asm_printf("%s", "%ebp");
}

void set_stack_from_bp
(void)
{
  asm_printop("%s %d-%sdisp%d(%s) %s", leal, stack_dec / 8, local_prefix, crt_proc_id, "%ebp", "%esp");
}

void testah
(int mask)
{
  asm_printop("testb $%d,%s", mask, "%ah");
}

exp make_extn
(char * n, shape s, int v)
{
  dec * g = xmalloc(sizeof(dec));
  exp id = getexp(s, NULL, 1, NULL, NULL, 0, 0, ident_tag);
  exp nme = getexp(s, NULL, 1, id, NULL, 0, 0, name_tag);
  size_t prefix_length = strlen(name_prefix);
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
    char * newn = xcalloc((nl + prefix_length + 1), sizeof(char));
    for (j = 0; j < prefix_length; ++j)
      newn[j] = name_prefix[j];
    for (j = 0; j < nl; ++j)
      newn[j+prefix_length] = n[j];
    newn[nl+prefix_length] = 0;
    n = newn;
  }
  g -> exp = id;
  g -> name = n;
  g -> extnamed = 1;
  return nme;
}

/* Shift or rotate 64 bits in reg0/reg1 */
void rotshift64
(int shft, int sig, where wshift)
{
  if (wshift.where_exp->tag == val_tag) {	/* no of places is constant */
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
    }
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
#ifdef DWARF2
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_push();
#endif
	ins0(pusheax);
#ifdef DWARF2
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_push();
#endif
	ins3(dsh, 8, 32, 32, mw(zeroe,places),
		reg1, mw(ind_sp.where_exp,-32));
	ins3(dsh, 8, 32, 32, mw(zeroe,places),
		reg0, mw(ind_sp.where_exp,-64));
	ins0(popeax);
#ifdef DWARF2
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_pop();
#endif
	ins0(popedx);
#ifdef DWARF2
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_pop();
#endif
	invalidate_dest(ind_sp);
        extra_stack -= 64;
	return;
      }
    }
  }
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
#ifdef DWARF2
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_push();
#endif
	ins0(pusheax);
#ifdef DWARF2
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_push();
#endif
	ins3(dsh, 8, 32, 32, reg2, reg1, mw(ind_sp.where_exp,-32));
	ins3(dsh, 8, 32, 32, reg2, reg0, mw(ind_sp.where_exp,-64));
	ins0(popeax);
#ifdef DWARF2
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_pop();
#endif
	ins0(popedx);
#ifdef DWARF2
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
#ifdef DWARF2
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_push();
#endif
	ins0(pusheax);
#ifdef DWARF2
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_push();
#endif
	ins3(dsh, 8, 32, 32, reg2, reg1, mw(ind_sp.where_exp,-32));
	ins3(dsh, 8, 32, 32, reg2, reg0, mw(ind_sp.where_exp,-64));
	ins0(popeax);
#ifdef DWARF2
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_pop();
#endif
	ins0(popedx);
#ifdef DWARF2
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_pop();
#endif
	invalidate_dest(ind_sp);
        extra_stack -= 64;
      }
    }
    simplest_set_lab(labend);
  }
}
