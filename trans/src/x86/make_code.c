/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * make_code produces code for expressions. It calls codec to produce code
 * for expressions which deliver results, and produces code itself for
 * the others.
 */

#include <string.h>
#include <limits.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/xalloc.h>

#include <local/ash.h>
#include <local/out.h>
#include <local/cpu.h>
#include <local/codermacs.h>

#ifdef DWARF2
#include <local/dw2_config.h>
#endif

#include <reader/exp.h>
#include <reader/code.h>
#include <reader/basicread.h>
#include <reader/externs.h>
#include <reader/readglob.h>

#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/shape.h>
#include <construct/install_fns.h>
#include <construct/installglob.h>
#include <construct/machine.h>
#include <construct/reg_result.h>
#include <construct/label_ops.h>
#include <construct/misc_c.h>

#include <main/flags.h>
#include <main/print.h>

#include <refactor/refactor.h>

#include <utility/bits.h>

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
#include "cproc.h"
#include "make_code.h"
#include "localexpmacs.h"

#ifdef TDF_DIAG4
#include <diag4/diag_fns.h>
#include <diag4/dg_aux.h>
#include <diag4/dg_globs.h>
#include <diag4/diag_reform.h>
#else
#include <diag3/diag_fns.h>
#include <diag3/diaginfo1.h>
#include <diag3/diag_reform.h>
#endif

#ifdef DWARF2
#include <dwarf2/dw2_info.h>
#include <dwarf2/dw2_basic.h>
#include <dwarf2/dw2_lines.h>
#include "dw2_extra.h"
#endif

extern exp hasenvoff_list;

#define crit_noframe 300

#define align_crit 10000.0



#define noreg 6
#define nobigreg 4
#define nosmallreg 2
#define bigmask1 0x40
#define bigmask1ns 0x8
#define bigmask2 0x30
#define smallmask1 0x2
#define smallmask2 0x6

#define nofl 6
#define nobigfl 3
#define bigflmask 0x1000
#define smallflmask 0x200

/* All variables initialised */

float scale = (float)1.0;	/* init by cproc */

int  remove_struct_ref;
int  crt_ret_lab;	/* init by cproc */
int  crt_ret_lab_used;	/* init by cproc */
int  min_rfree;		/* init by cproc */
int  max_stack;		/* init by cproc */
int  regsinuse;		/* init by cproc */
outofline * odd_bits;	/* init by cproc */
int last_odd_bit; 	/* init by cproc */
int doing_odd_bits; 	/* init by cproc */
outofline * current_odd_bit; 	/* init by cproc */
exp crt_proc_exp;	/* init by cproc */

int not_in_params = 1;	/* init by cproc */
int not_in_postlude = 1;	/* init by cproc */
int repeat_level = 0;	/* init by cproc */
int callee_size = 0;	/* init by cproc */
exp vc_pointer;		/* init by cproc */
int has_dy_callees = 0;	/* init by cproc */
int has_tail_call = 0;	/* init by cproc */
int has_same_callees = 0;	/* init by cproc */
int need_preserve_stack = 0;	/* init by cproc */
int proc_has_asm = 0;	/* init by cproc */


void clean_stack
(void)
{
  if (no_frame && not_in_params && not_in_postlude && stack_dec != 0)
    stack_return(-stack_dec);
}

/*
 * Is this a pushable proc argument?
 */
static int push_arg
(exp e)
{
  shape sha = sh(e);
  unsigned char  n = name(sha);

  if (name(e) == real_tag)
    return 1;

  if (is_floating(n) || n == cpdhd || n == nofhd)
    return 0;

  return 1;
}

static void code_push
(ash stack, exp t)
{
  int n = (int)name(t);
  if (is_o(n))
    make_code(pushdest, stack, t);
  else {
    make_code(reg0, stack, t);
    move(sh(t), reg0, pushdest);
  };
}

/*
 * Produce the code for proc params in order from last to first.
 */
static void code_pars
(ash stack, exp t)
{
  int tsize = shape_size(sh(t));
  if (last (t)) {		/* last parameter is pushed first */
    code_push(stack,(name(t) ==caller_tag)? son(t): t);
    stack_dec -= rounder(tsize, param_align);
  }
  else {
    code_pars (stack, bro (t));/* encode the rest of the parameters */
    code_push (stack, (name(t)==caller_tag) ? son(t) : t);	/* code this parameter */
    stack_dec -= rounder(tsize, param_align);
    /* allow for the size */
  };
}

/*
 * Stack parameters ready for apply_proc
 */
static int procargs
(ash stack, exp arg, int has_checkstack)
{
  int use_push = 1;
  int longs = 0, extra;
  exp t = arg;
  while (t != NULL) {
    if (name(t) ==caller_tag) {
      if (use_push && !push_arg(son(t)))
        use_push = 0;
      no(t) = longs;	/* needed for postlude */
    }
    else {
      if (use_push && !push_arg(t))
        use_push = 0;
    }
    longs = rounder(longs + shape_size(sh(t)), param_align);
    if (last(t))
      break;
    t = bro(t);
  };
  extra = (longs - stack_dec)% stack_align;
  longs += extra;

  if (use_push) {
	  /*
	   * Push instructions can be used. Note that stack_dec is moved
	   * so that instructions which address positively with respect to
	   * sp can be changed.
	   */
    if (extra != 0) {
      sub(slongsh, mw(zeroe, extra/8), sp, sp);
      stack_dec -= extra;  /* align stack to param_align */
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_sp();
#endif
    };
    if (arg != NULL) {
      if (has_checkstack && longs > 160) {
	/* check stack before pushing args if more than 5 words */
	checkalloc_stack(mw(zeroe, longs/8), 0);
      }
      code_pars(stack, arg);
    }
  }
  else {
	  /*
	   * If push cannot be used, move the stack down first, and then
	   * assemble the parameters in place. Again, adjust stack_dec.
	   */
    int off = extra;
    if (has_checkstack)
      checkalloc_stack(mw(zeroe, longs/8), 1);
    else
      decstack(longs);
    cond1_set = 0;
    cond2_set = 0;
    stack_dec -= longs;
#ifdef DWARF2
    if (diag == DIAG_DWARF2 && no_frame)
      dw2_track_sp();
#endif

    t = arg;
    while (1)
     {
	make_code(mw(ind_sp.where_exp, off), stack,(name(t) ==caller_tag ? son(t): t));
	off = rounder(off + shape_size(sh(t)), param_align);
	if (last(t))
	  break;
	t = bro(t);
     };
  };
  return longs;
}

/*
 * Stack dynamic or same callees.
 * %edx and %ecx don't need to be preserved.
 */
static int push_cees
(exp src, exp siz, int vc, ash stack)
{
  int old_regsinuse = regsinuse;
  int longs = -1;
  if (siz == NULL && callee_size >= 0)
    longs = callee_size;
  if (siz != NULL && name(siz) == val_tag)
    longs = rounder(no(siz), param_align);
  if (longs == 0) {
    if (vc) {
      ins2(leal, 32, 32, mw(ind_sp.where_exp, longs), reg0);
      ins0(pusheax);
      stack_dec -= 32;
      return 32;
    }
    return 0;
  }
  if (longs < 0) {
    must_use_bp = 1;	/* scan() must ensure !no_frame */
    if (siz == NULL) {
	/* calculate size from calling proc callees */
      asm_printop("movl 8(%s),%s", "%ebp", "%eax");
      asm_printop("subl %s,%s", "%ebp", "%eax");
      asm_printop("subl $12,%s", "%eax");
    }
    else {
      make_code(reg0, stack, siz);
      if (al2(sh(siz)) < param_align) {
	if (al2(sh(siz)) == 1) {
	  asm_printop("addl $31,%s", "%eax");
	  asm_printop("shrl $3,%s", "%eax");
	}
	else
	  asm_printop("addl $3,%s", "%eax");
	asm_printop("andl $-4,%s", "%eax");
      }
    }
    ins0(pusheax);
    stack_dec -= 32;
  }
  if (src == NULL) {
    if (callee_size >= 0)
      asm_printop("leal 8(%s),%s", "%ebp", "%eax");
    else
      asm_printop("leal 12(%s),%s", "%ebp", "%eax");
    }
  else
    make_code(reg0, stack, src);
  move(slongsh, reg5, reg1);
  move(slongsh, reg0, reg5);
  if (longs < 0) {
    ins0(popecx);
    stack_dec += 32;
    if (vc)
      asm_printop("movl %s,%s", "%esp", "%eax");
    asm_printop("subl %s,%s", "%ecx", "%esp");
    asm_printop("shrl $2,%s", "%ecx");
    if (vc)
      asm_printop("pushl %s", "%eax");
  }
  else {
    sub(slongsh, mw(zeroe, longs/8), sp, sp);
    stack_dec -= longs;
    if (vc) {
      ins2(leal, 32, 32, mw(ind_sp.where_exp, longs), reg0);
      ins0(pusheax);
      stack_dec -= 32;
    }
    move(slongsh, mw(zeroe, longs/32), reg2);
    if (vc)
      longs += 32;
  }
  move(slongsh, reg4, reg0);
  if (vc)
    asm_printop("leal 4(%s),%s", "%esp", "%edi");
  else
    asm_printop("movl %s,%s", "%esp", "%edi");
  asm_printop("rep");
  asm_printop("movsl");
  move(slongsh, reg0, reg4);
  move(slongsh, reg1, reg5);
  regsinuse = old_regsinuse;
  invalidate_dest(reg1);
  invalidate_dest(reg2);
  invalidate_dest(reg4);
  invalidate_dest(reg5);
  return longs;
}

/*
 * alloc_reg tries to choose registers for a value of shape sha.
 * If there is no room, can_do of the result is 0, otherwise 1.
 * If it can, ru_regs of result is the registers (as bit pattern)
 * and ru_reg_free contains the bit pattern for the registers in use.
 * rs is the bit pattern for the registers in use. All the registers must
 * be above br (register number as integer, ie 0 for reg0 etc)
 */

/*
 * Allocate registers ebx esi edi, providing br registers are left.
 */
static regu alloc_reg_big
(int rs, shape sha, int br, int byteuse)
{
  int  sz,
        nr,
        mask,
        i,
        reg_left;		/* number of registers available */
  regu ru;
  int  noshort = 0;
  sz = shape_size(sha);
  if (sz <= 8 || byteuse)
    noshort = 3;
  nr = (sz + 31) / 32;
  reg_left = noreg - noshort - bits_in(rs & 0xf)
		 - bits_in(((unsigned int)rs >> 4) & 0x7);


  if ((reg_left) < (br)) {	/* can't allocate */
    ru.can_do = 0;
    return ru;
  };

  switch (nr) {			/* number of registers needed
				   (consecutive) */
    case 1:
      mask = (noshort == 0)? bigmask1 : bigmask1ns;
      i = nobigreg - noshort;
      break;
    case 2:
      mask = bigmask2;
      i = nobigreg - 1;
      break;
    default: {
      SET(mask);
      SET(i);
      error(ERR_INTERNAL, WRONG_REGSIZE);
    };
  };

  while ((rs & mask)!= 0 && i > 0) {
    mask = (int)((unsigned int)mask >> 1);
    --i;
  };

  if (i > 0) {			/* allocate registers */
    min_rfree |= mask;
    ru.can_do = 1;
    ru.ru_regs = mask;
    ru.ru_reg_free = rs | mask;
  }
  else {
    ru.can_do = 0;
  }

  return ru;
}

/*
 * Allocate registers ecx edx ebx esi edi if at least br registers
 * are available.
 */
static regu alloc_reg_small
(int rs, shape sha, int br, int byteuse)
{
  int sz, nr, mask, i;
  int reg_left;		/* number of registers left */
  regu ru;
  int  noshort = 0;
  sz = shape_size(sha);
  if (sz <= 8 || byteuse)
    noshort = 3;
  nr = (sz + 31) / 32;
  reg_left = noreg - noshort - bits_in(rs & 0xf)
		 - bits_in(((unsigned int)rs >> 4) & 0x7);


  if ((reg_left) < (br)) {	/* can't allocate */
    ru.can_do = 0;
    return ru;
  };

  switch (nr) {			/* number of registers needed
				   (consecutive) */
    case 1:
      mask = smallmask1;
      i = nosmallreg;
      break;
    case 2:
      mask = smallmask2;
      i = nosmallreg - 1;
      break;
    default: {
      SET(mask);
      SET(i);
      error(ERR_INTERNAL, WRONG_REGSIZE);
     };
  };

  while ((rs & mask)!= 0 && i > 0) {
    mask = (int)((unsigned int)mask << 1);
    --i;
  };

  if (i > 0) {			/* allocate */
    min_rfree |= mask;
    ru.can_do = 1;
    ru.ru_regs = mask;
    ru.ru_reg_free = rs | mask;
    return ru;
  }
  else
    return alloc_reg_big(rs, sha, br, byteuse);

}

/*
 * Allocate floating point registers, if at least br are available.
 */
static regu alloc_fl_small
(int rs, int br)
{
  int  mask, i, reg_left;
  regu ru;
  reg_left = nofl - bits_in(((unsigned int)rs >> 8) & 0xf)
		- bits_in(((unsigned int)rs >> 12) & 0xf);


  if ((reg_left) < (br)) {	/* can't allocate */
    ru.can_do = 0;
    return ru;
  };

  mask = smallflmask;
  i = nofl;

  while ((rs & mask)!= 0 && i > 0) {
    mask = (int)((unsigned int)mask << 1);
    --i;
  };

  if (i > 0) {			/* allocate */
    ru.can_do = 1;
    ru.ru_regs = mask;
    ru.ru_reg_free = rs | mask;
  }
  else
    ru.can_do = 0;		/* can't allocate */

  return ru;
}

/*
 * Allocate all registers.
 */
static regu alloc_reg
(int rs, shape sha, int br, int big_reg, exp e)
{
  if (name(sha) >= shrealhd && name(sha) <= doublehd) {
#ifdef TDF_DIAG4
    if (big_reg || diag_visible || round_after_flop ||
#else
    if (big_reg || diag != DIAG_NONE || round_after_flop ||
#endif
	(cpu & CPU_80586 && isvar(e))) {
      regu ru;
      ru.can_do = 0;
      return ru;
    }
    else
      return alloc_fl_small(rs, br);
  };
  if (big_reg)
    return alloc_reg_big(rs, sha, br, isbyteuse(e));
  else
    return alloc_reg_small(rs, sha, br, isbyteuse(e));
}

/*
 * def_where choose where to put a declaration. e is the declaration.
 * def is the definition (for identity) or initialisation (for variable).
 * stack is the ash for the current stack position. The alignment for the
 * stack on the 80386 for the cc implementation is always 32 bits, but it
 * might not be on other implementations.
 *
 * The dcl returned gives:
 *
 *   dcl_pl - code for where value is (eg reg_pl for registers). These
 *            codes are defined in codermacs.h
 *   dcl_n  - the offset (in bits) where the value starts if it is on the
 *            stack.
 *            the bit pattern for the registers if it is in registers.
 *   dcl_place - the ash for the stack after the allocation. This will
 *            be the same as stack if the allocation is in registers.
 *   dcl_new - 1 if this is a new declaration. 0 if it renaming an
 *            existing value, and the old one is being reused.
 */
static dcl alloc_regable
(dcl dc, exp def, exp e, int big_reg)
{
  where alt;
  int defsize = shape_size(sh(def));
  regu ru;
  alt = equiv_reg(mw(def, 0), defsize);

  if (alt.where_exp != NULL) {
    int  mask = no(son(alt.where_exp));
    if (mask != 1 && (!big_reg || mask >= 0x8)) {
      if ((mask & regsinuse)!= 0 && !isvar(e) &&
	 (defsize > 8 || mask < 0x10)) {
	if (no_side(bro(son(e)))) {
	  dc.dcl_pl = reg_pl;
	  dc.dcl_n = mask;
	  dc.dcl_new = 0;
	  return dc;
	};
      };
    };
  };


  if (ru = alloc_reg(regsinuse, sh(def), no(e), big_reg, e),
      ru.can_do) {
    if (alt.where_exp != NULL) {
      int  mask = no(son(alt.where_exp));
      if (mask != 1 && (!big_reg || mask >= 0x8)) {
	if ((mask & regsinuse) == 0 &&
	   (defsize > 8 || mask < 0x10)) {
	  dc.dcl_pl = reg_pl;
	  dc.dcl_n = mask;
	  return dc;
	};
      };
    };

    dc.dcl_pl = reg_pl;
    dc.dcl_n = ru.ru_regs;
    return dc;
  };
  dc.dcl_pl = 0;
  return dc;
}

static dcl def_where
(exp e, exp def, ash stack)
{
  int big_reg = has_intnl_call(e);
  dcl dc;
  ash locash;
  exp body = bro(def);
  dc.dcl_place = stack;
  dc.dcl_new = 1;


  if (name(sh(def)) == tophd && !isvis(e)) {
    dc.dcl_pl = nowhere_pl;
    dc.dcl_n = 0;
    return dc;
  };

  if (name(def) == name_tag && !isvar(son(def)) &&
        no(def) == 0 && isloadparam(def)) {
    if (regable(e) && (name(son(son(def))) ==formal_callee_tag ?
			 !has_same_callees : !has_tail_call)) {
	dcl ndc;
	ndc = alloc_regable(dc, def, e, big_reg);
	if (ndc.dcl_pl != 0)		/* local copy of arg in register */
	  return ndc;
    };
    dc.dcl_pl = ptno(son(def));
    dc.dcl_n = no(son(def));
    dc.dcl_new = 0;
    return dc;
  };


  if (!isvar(e) &&
     ((name(def) == name_tag && !isvar(son(def)) &&
	 (!isglob(son(def)))
	) ||
	(name(def) == cont_tag && name(son(def)) == name_tag &&
	  isvar(son(son(def))) &&
	 (!isglob(son(son(def)))) &&

	  no_side(body)))) {
    /*
	 * Either we are identifying something already identified or the
     * contents of a variable which is not altered by the body of the
     * definition.
	 */
    if (name(def) == name_tag) {
      dc.dcl_pl = ptno(son(def));
      dc.dcl_n = no(son(def)) + no(def);
    }
    else {
      dc.dcl_pl = ptno(son(son(def)));
      dc.dcl_n = no(son(son(def))) + no(son(def));
    };

    /* We have the declaration */

    if (dc.dcl_pl == reg_pl) {	/* if the old one was in registers, reuse
				   it. */
      dc.dcl_new = 0;
      return dc;
    };

    if (regable(e)) {
	dcl ndc;
	ndc = alloc_regable(dc, def, e, big_reg);
	if (ndc.dcl_pl != 0)
	  return ndc;
    };

    dc.dcl_new = 0;		/* if there was not room, reuse the old dec */
    return dc;

  };

  /* Try to allocate in registers, except when narrowing fp variety */
  if (regable(e) &&
	(name(def)!= chfl_tag || name(sh(def)) >= name(sh(son(def))))) {
    dcl ndc;
    ndc = alloc_regable(dc, def, e, big_reg);
    if (ndc.dcl_pl != 0)
      return ndc;
  };


  /* Otherwise allocate on the stack */

  {
    int a = 32;
    shape s = sh(def);
    if (stack_aligned_8byte && (name(s) == realhd ||
			(name(s) == nofhd && ptno(s) == realhd)))
      a = 64;

    locash.ashalign = 32;
    dc.dcl_n = rounder(stack.ashsize, a);

    locash.ashsize = dc.dcl_n + shape_size(sh(def));

    dc.dcl_place = locash;
    dc.dcl_pl = local_pl;
    return dc;
  };

}

/*
 * Solve produces the code for the solve construction.
 *
 *  s is the whole list of braches
 *  l is the branches of which the label record have not been created.
 *  dest is the destination for the value produced by each branch
 *  jr is the jump record for the end of the construction.
 *  stack is the initial stack ash
 */
static void solve
(exp s, exp l, where dest, exp jr, ash stack)
{
  while (!last (l)) {		/* not the last branch */
    exp record = getexp(f_bottom, NULL,
       (bool)(props(son(bro(l))) & 2),
        NULL,
	NULL, 0, 0, 0);
    sonno(record) = stack_dec;
    ptno(record) = next_lab();
    fstack_pos_of(record) = (prop)fstack_pos;	/* CAST:jmf: */

    /*
	 * Record the floating point stack position, fstack_pos
     * record is jump record for the label
	 */
    pt (son (bro (l))) = record;/* put it away */
    l = bro(l);
  };

  {
    int  r1;
    exp t;

	/* Record regsinuse for the start of each branch and for the end. */
    r1 = regsinuse;

    if (name(s)!= goto_tag || pt(s)!= bro(s))
      make_code(dest, stack, s);	/* code the starting exp */
#ifdef TDF_DIAG4
    else
      diag_arg(dest, stack, s);
#endif
    reset_fpucon();
    t = s;
    do {
      regsinuse = r1;
      if (name(sh(t))!= bothd) {
	jump(jr, in_fstack(dest.where_exp));
      };
      /* only put in jump if needed */
      t = bro(t);
      align_label(2, pt(son(t)));
      set_label(pt(son(t)));
      make_code(dest, stack, t);
      reset_fpucon();
    }
    while (!last(t));
    regsinuse = r1;
    return;
  }
}

/*
 * caser produces the code for the case construction e, putting the
 * result into dest.
 */
static void caser
(exp arg, int exhaustive, exp case_exp)
{
  exp t = arg;
  int  n;
  int i;
  int *v;
  int  sz;
  int min;
  int max;

  min=no(bro(arg));
  do
  {
    t=bro(t);
  }
  while (bro(t)!=NULL);
  max= ((son(t) ==NULL)? no(t): no(son(t)));


  /* Prepare to use jump table */
  v = (int *)xcalloc(max - min + 1, sizeof(int));
  for (i = 0; i < (max - min + 1); ++i)
    v[i] = -1;
  t = arg;
  do {
    exp lab;
    t = bro(t);
    lab = final_dest(pt(t));
    n = ptno(pt(son(lab)));
    for (i = no(t);
	i <= ((son(t) == NULL)? no(t): no(son(t)));
	++i)
      v[i - min] = n;
  }
  while (bro(t)!= NULL);

  switch (name(sh(arg)))EXHAUSTIVE {
    case scharhd:
    case ucharhd:
      sz = 8;
      break;
    case swordhd:
    case uwordhd:
      sz = 16;
      break;
    case slonghd:
    case ulonghd:
      sz = 32;
      break;
  };

  caseins(sz, arg, min, max,v, exhaustive, 0 , case_exp);
  /* put in jump table */
}

/*
 * make_code produces code for all constructions. It uses codec to
 * produce the code for the non side-effecting constructions. e is
 * the construction to be processed, dest is where the result is to go,
 * stack is the ash for the current stack.
 */
static ash stack_room
(ash stack, where dest, int off)
{
  if (name(dest.where_exp) == ident_tag)
   {
     if (ptno(dest.where_exp)!= local_pl)
       return stack;
     if ((no(dest.where_exp) + off) > stack.ashsize)
       stack.ashsize = no(dest.where_exp) + off;
   };

  return stack;
}

#ifdef TDF_DIAG4
static void make_code1
#else
void make_code
#endif
(where dest, ash stack, exp e)
{
  float old_scale;
  switch (name(e)) {
    case ident_tag:
      {
	exp def = son(e);
	exp body = bro(def);
	int sz;
	dcl dc;
	int old_fstack_pos;
	if (isinlined(e) && dest.where_off == 0 &&
		name(dest.where_exp) == ident_tag &&
		(!has_intnl_call(e) || ptno(dest.where_exp)!= reg_pl ||
		  (no(dest.where_exp) > 4 && no(dest.where_exp) < smallflmask))) {
	  dc.dcl_pl = ptno(dest.where_exp);
	  dc.dcl_n = no(dest.where_exp);
	  dc.dcl_place.ashsize = stack.ashsize + shape_size(sh(def));
	  dc.dcl_place.ashalign = 32;
	  dc.dcl_new = 1;
	}
	else
	  dc = def_where (e, def, stack);/* allocate space */

	sz = (dc.dcl_place).ashsize;

	/* Record the allocation in pt and no for when the value is used. */
	ptno(e) = dc.dcl_pl;
	no(e)   = dc.dcl_n;

	if (ptno(e) == reg_pl && name(sh(def)) >= shrealhd &&
	    name(sh(def)) <= doublehd) {
	  /*
	   * If the value being defined is going in the floating point
	   * registers, record the floating point stack level, so that we
	   * can ensure that it is the same at the end of the construction
	   */
	  old_fstack_pos = fstack_pos;
	};

        if (isenvoff(e)) {
          set_env_off(-dc.dcl_n, e);
        };

	if (dc.dcl_new) {
	  /* if it is new we must evaluate the def */
	  if (ptno(e) == nowhere_pl)
	    make_code(zero, stack, def);/* discard the value */
	  else
           {
	    make_code(mw(e, 0), stack, def);
           };

	  if (ptno(e) == reg_pl) {
	    /* modify regsinuse if a register is being used */
	    regsinuse |= dc.dcl_n;
	  };
	  if (ptno(e) == local_pl) {
	    /* modify max_stack if the stack is being used */
	    if (sz > max_stack)
	      max_stack = sz;
	  };
	};

	make_code(dest, dc.dcl_place, body);/* code the body */

	if (dc.dcl_new && ptno(e) == reg_pl) {
	  regsinuse &= ~dc.dcl_n;
	  /*
	   * Restore regsinuse. It is done by removing the bits of this allocation,
	   * rather than restoring the old value, so that allocation and restoration
	   * need not nest.
	   */
	  if (name(sh(def)) >= shrealhd && name(sh(def)) <= doublehd &&
	      fstack_pos != (SET(old_fstack_pos)old_fstack_pos) &&
	      ptno(e) == reg_pl &&
	      name(sh(e))!= bothd) {
	    /* restore the floating point registers if necessary */

	    if (ptno(e) == reg_pl &&
		!in_fstack(dest.where_exp)) {
	      int   rn = get_reg_no(no(e));
	      if (rn == fstack_pos)
		discard_fstack();
	      else {
		if (rn < fstack_pos)
		  discard_st1();
	      };
	    };
	  };
	};

	if (dc.dcl_new && ptno(e) == local_pl) {
	  exp temp = getexp(f_top, NULL, 1, e, NULL, 0, 0, name_tag);
	  if (isvar(e))
	    temp = getexp(f_top, NULL, 1, temp, NULL, 0, 0, cont_tag);
	  invalidate_dest(mw(temp, 0));
	  if (isvar(e))
	    retcell(son(temp));
	  retcell(temp);
	}

	if (isenvoff(e)) {
	  /* prepare for possible later constant evaluation */
	  hasenvoff_list = getexp(f_bottom, hasenvoff_list, 0, e, NULL, 0, 0, 0);
	}

	return;
      };
    case seq_tag:
      {
	exp t = son(son(e));
	int no_bottom;
	while (make_code(zero, stack, t),
	/* code and discard the statements */
	    no_bottom = (name(sh(t))!= bothd),
	    !last(t))
	  t = bro(t);
	if (no_bottom)
	  make_code(dest, stack, bro(son(e)));
#ifdef TDF_DIAG4
	else
	if (diag != DIAG_NONE) {
	  /* Beware lost information !!! */
	  name(bro(son(e))) = top_tag;
	  son(bro(son(e))) = NULL;
	  dgf(bro(son(e))) = nildiag;
	}
#endif
	return;
      };
    case cond_tag:
      {
	int  old_fstack_pos = fstack_pos;
	exp first = son(e);
	exp alt = bro(first);
	exp record;	/* jump record for alt */
	int  r1;
	exp jr = NULL; /* jump record for end of construction */

	if (no(son(alt)) == 0) {
	  make_code(dest, stack, first);
#ifdef TDF_DIAG4
	  if (diag != DIAG_NONE) {
		/* Beware lost information !!! */
	    name(bro(son(alt))) = top_tag;
	    son(bro(son(alt))) = NULL;
	    dgf(bro(son(alt))) = nildiag;
	  }
#endif
	  return;
	};

	clean_stack();


	record = getexp(f_bottom, NULL, 0,
	      NULL, NULL,
	      0, 0, 0);
        sonno(record) = stack_dec;
        fstack_pos_of(record) = (prop)fstack_pos;
	if (pt(son(alt))!= NULL)
	    ptno(record) = ptno(pt(son(alt)));
	else
            ptno(record) = next_lab();


	if (name(bro(son(alt))) == top_tag && stack_dec == 0 && !is_loaded_lv(alt)) {
	  int extract = take_out_of_line(first, alt, repeat_level > 0, scale);

	  if (extract) {
	    exp t = son(son(first));
	    exp p, s, z;
	    int test_n;
	    shape sha;
	    outofline * rec;
	    exp tst = (is_tester(t, 0))? t : bro(son(t));
	      jr = getexp(f_bottom, NULL, 0, NULL, NULL, 0,
	        0, 0);
              sonno(jr) = stack_dec;
              ptno(jr) = next_lab();
              fstack_pos_of(jr) = (prop)fstack_pos;
	    sha = sh(son(tst));
	    rec = (outofline*)xmalloc(sizeof(outofline));
	    rec->next = odd_bits;
	    odd_bits = rec;
	    rec->dest = dest;
	    rec->stack = stack;
	    rec->regsinuse = regsinuse;
	    rec->fstack_pos = fstack_pos;
	    rec->labno = next_lab();	/* number for outofline bit */
	    rec->repeat_level = repeat_level;
	    rec->scale = (float)0.5 * scale;
	    rec->jr = jr;	/* jump record for return from bit */

	    if (last(t))
	      first = bro(son(first));
	    else
	      son(son(first)) = bro(son(son(first)));

	    rec->body = first;
	    pt(son(alt)) = record;

	    test_n = (int)test_number(tst);
	    if (name(sha) < shrealhd || name(sha) > doublehd)
	      test_n = (int)int_inverse_ntest[test_n];
	    else
	      test_n = (int)real_inverse_ntest[test_n];

	    settest_number(tst, test_n);
	    z = getexp(f_bottom, NULL, 0, NULL, NULL, 0, 0, 0);
	    sonno(z) = stack_dec;
	    fstack_pos_of(z) = (prop)fstack_pos;
	    ptno(z) = rec->labno;
	    s = getexp(sha, NULL, 0, NULL, z, 0, 0, 0);
	    p = getexp(sha, tst, 0, s, NULL, 0, 0, 0);
	    pt(tst) = p;
	    make_code(zero, stack, t);
	    if (name(sh(first))!= bothd) {
	      reset_fpucon();
	      set_label(jr);
#ifdef DWARF2
	      if (diag == DIAG_DWARF2) {
	        dw2_start_basic_block();
	      }
#endif
	      clear_reg_record(crt_reg_record);
	    };

	    rec->cond1_set = cond1_set;
	    rec->cond2_set = cond2_set;
	    rec->cond1 = cond1;
	    rec->cond2a = cond2a;
	    rec->cond2b = cond2b;
#if 0
#ifdef DWARF2
	    if (diag == DIAG_DWARF2) {
	      rec->dw2_hi = next_dwarf_label();
	      rec->dw2_slave = next_dwarf_label();
	      dw2_extend_scope(rec->labno, rec->dw2_hi, rec->dw2_slave);
	    }
#endif
#endif
	    return;
	  };
	};

        old_scale = scale;
        scale = (float)0.5*scale;

	/*
	 * Record floating point stack position so that we can align the positions.
	 */
	/* jump record set up for alt */
	pt(son(alt)) = record;
	/* set the record in for use by jumps in first. */

	/*
	 * regsinuse is the same at the start of first and alt,
	 * and at the end of the construction.
	 */
	r1 = regsinuse;

	make_code(dest, stack, first);
	reset_fpucon();
	clean_stack();

	regsinuse = r1;		/* restore regsinuse for alt */

	if (name(bro(son(alt))) == top_tag && !is_loaded_lv(alt)) {
	  /* if alt is only load top, do nothing but set the label */
	  if (name(sh(first)) == bothd && no(son(alt))!= 0)
	    align_label(2, record);

	  if (name(first) == seq_tag &&
		  name(bro(son(first))) == seq_tag &&
		  name(bro(son(bro(son(first))))) == apply_tag)
	    align_label(0, record);
	  set_label(record);
#ifdef DWARF2
	  if (diag == DIAG_DWARF2) {
	    dw2_start_basic_block();
	  }
#endif
	  fstack_pos = old_fstack_pos;
	  clear_reg_record(crt_reg_record);
          scale = old_scale;
	  return;
	};

	if (name(sh(first))!= bothd &&
		(no(son(alt))!= 0 || name(bro(son(alt)))!= goto_tag)) {
	  /*
	   * If the first did not end with jump or ret, put in a jump to
	   * the end of the construction, and make a jump record for it
	   */
	    jr = getexp(f_bottom, NULL, 0, NULL, NULL, 0,
	        0, 0);
            sonno(jr) = stack_dec;
            ptno(jr) = next_lab();
            fstack_pos_of(jr) = (prop)fstack_pos;
	  jump(jr, in_fstack(dest.where_exp));
	};

	if (no(son(alt))!= 0 || name(bro(son(alt)))!= goto_tag) {
	if (no(son(alt))!= 0)
          align_label(2, record);
	set_label (record);	/* the label for the start of alt */
	fstack_pos = old_fstack_pos;
	make_code(dest, stack, alt);
	reset_fpucon();
	regsinuse = r1;		/* restore regsinuse for end of
				   construction */
	if (name(sh(first))!= bothd) {
	  /* Set the label for the end of the construction if first needed it. */
	  SET(jr);
	  if (name(sh(alt)) == bothd)
	    align_label(2, jr);
	  set_label(jr);
#ifdef DWARF2
	  if (diag == DIAG_DWARF2) {
	    dw2_start_basic_block();
	  }
#endif
	};
      };
	cond1_set = 0;
	cond2_set = 0;		/* we don't know what condition flags are set */
        scale = old_scale;
	return;
      };
    case labst_tag: 		/* code a labelled statement */
      {
	clear_reg_record(crt_reg_record);
	cond1_set = 0;
	cond2_set = 0;
	fpucon = normal_fpucon;

        if (is_loaded_lv(e)) {
	  set_lv_label(e);
	  if (need_preserve_stack)
	    restore_stack();
	  else if (!has_alloca)
            set_stack_from_bp();
	};
        fstack_pos = (int)fstack_pos_of(pt(son(e)));
        stack_dec = sonno(pt(son(e)));

        old_scale = scale;
#ifdef DWARF2
	if (diag == DIAG_DWARF2) {
	  dw2_start_basic_block();
	}
#endif
	make_code(dest, stack, bro(son(e)));
        scale = old_scale;

	clear_reg_record(crt_reg_record);
	clean_stack();
	return;
      };
    case rep_tag:
      {
	exp start = son(e);
	exp body = bro(start);
	exp record;		/* jump record for loop label */
        ++repeat_level;
	make_code(mw(body, 0), stack, start);
	/* code the starter of the loop */
	reset_fpucon();
	clean_stack();
	record = getexp(f_bottom, NULL, 1, NULL,
	    NULL, 0, 0, 0);
        sonno(record) = stack_dec;
        ptno(record) = next_lab();
        fstack_pos_of(record) = (prop)fstack_pos;
	cond1_set = 0;
	cond2_set = 0;
        align_label(1, record);
	set_label (record);	/* set the label at the start of body */
	pt(son(body)) = record;
        old_scale = scale;
        if (scale < 1e30)
		scale = (float)20.0 * scale;
	make_code(dest, stack, body);
        scale = old_scale;
        --repeat_level;
	return;
      };
    case prof_tag:
      scale = (float)no(e);
      return;
    case goto_tag:
      {
	exp lab;
        clean_stack();
	lab = final_dest(pt(e));
#ifdef DWARF2
	if (current_dg_info) {
	  current_dg_info->data.i_tst.brk = set_dw_text_label();
	  current_dg_info->data.i_tst.jlab.u.l = ptno(pt(son(lab)));
	  current_dg_info->data.i_tst.jlab.k = LAB_CODE;
	}
#endif
	if (label_is_next(lab, e)) {
	  int  fs_dest = (int)fstack_pos_of(pt(son(lab)));
	  int  good_fs = fstack_pos;
	  while (fstack_pos > fs_dest)
	    discard_fstack();
	  reset_fpucon();
	  fstack_pos = good_fs;
	  return;
	};
	jump(pt(son(lab)), 0);
	return;
      };
    case goto_lv_tag:
      {
	clean_stack();
	reset_fpucon();
        jumpins(son(e));
        return;
      };
    case long_jump_tag:
      {
	make_code(pushdest, stack, bro(son(e)));
	extra_stack += 32;
	make_code(pushdest, stack, son(e));
	extra_stack += 32;
	check_stack_max;
	reset_fpucon();
	long_jump(e);
	extra_stack -= 64;
	return;
      };
    case testbit_tag:
      {
		/* Not more than one argument will not be a possible 80386 operand */
	exp lab = pt(e);
	exp temp;
	ntest testno = test_number(e);
	int isret = 0;

	if (name(lab) == labst_tag) {
	  exp q = short_next_jump(e);
	  if (q != NULL &&
		(name(q) == goto_tag ||
		  (name(q) == res_tag && name(son(q)) == top_tag)) &&
		label_is_next(lab, q)) {
	    shape sha = sh(son(e));
	    if (name(q) == goto_tag) {
	      temp = pt(q);
	      pt(q) = lab;
	    }
	    else {
              temp = getexp(f_bottom, NULL, 0, NULL,
                                NULL, 0, 0, 0);
	      ptno(temp) = crt_ret_lab;
	      fstack_pos_of(temp) = (prop)first_fl_reg;
	      temp = getexp(f_top, NULL, 0, NULL, temp,
				 0, 0, 0);
	      temp = getexp(f_top, lab, 0, temp, NULL,
				 0, 0, labst_tag);
	      crt_ret_lab_used = 1;
	      pt(q) = lab;
	      name(q) = goto_tag;
	      isret = 1;
	    };
	    lab = temp;
	    pt(e) = lab;
	    if (name(sha) < shrealhd || name(sha) > doublehd)
	      settest_number(e,(int)int_inverse_ntest[testno]);
	    else
	      settest_number(e,(int)real_inverse_ntest[testno]);
#ifdef TDF_DIAG4
	    if (current_dg_info)
	      current_dg_info->data.i_tst.inv = 1 - current_dg_info->data.i_tst.inv;
#endif
	  };
        };
	if (!isret)
	  temp = final_dest_test(lab, e);
	SET(temp);
	if (pt(son(temp)) == NULL) {
	  ++no(son(temp));
	  pt(son(temp)) = copyexp(pt(son(lab)));
	  ptno(pt(son(temp))) = next_lab();
	}
	else
	if (temp != lab) {
	  --no(son(lab));
	  ++no(son(temp));
	};
	pt(e) = temp;
       {
	where qw;
	exp lab_exp = pt(e);
	exp jr = pt(son(lab_exp));
	exp arg1 = son(e);
	exp arg2 = bro(arg1);
	if (!is_o(name(arg1)) || is_crc(arg1)) {
	  /* arg1 is not a possible 80386 operand, precompute it in reg0 */
	  qw.where_exp = copyexp(reg0.where_exp);
	  sh(qw.where_exp) = sh(arg1);
	  qw.where_off = 0;
	  make_code(qw, stack, arg1);
	  arg1 = qw.where_exp;
	};
	if (!is_o(name(arg2)) || is_crc(arg2)) {
	  /* arg2 is not a possible 80386 operand, precompute it in reg0 */
	  qw.where_exp = copyexp(reg0.where_exp);
	  sh(qw.where_exp) = sh(arg2);
	  qw.where_off = 0;
	  make_code(qw, stack, arg2);
	  arg2 = qw.where_exp;
	};

	clean_stack();
#ifdef DWARF2
	if (current_dg_info) {
	  current_dg_info->data.i_tst.brk = set_dw_text_label();
	  current_dg_info->data.i_tst.jlab.u.l = ptno(jr);
	  current_dg_info->data.i_tst.jlab.k = LAB_CODE;
	}
#endif
	test(sh(arg1), mw(arg1, 0), mw(arg2, 0));
	branch((int)test_number(e), jr, 1,(int)name(sh(arg1)));
#ifdef DWARF2
	if (diag == DIAG_DWARF2) {
	  dw2_start_basic_block();
	}
	if (current_dg_info)
	  current_dg_info->data.i_tst.cont = set_dw_text_label();
#endif
	return;
       };
      };
    case absbool_tag:
    case test_tag:
      {
		/* not more than one argument will not be a possible 80386 operand */
	exp lab = pt(e);
	exp temp;
	ntest testno = test_number(e);
	int isret = 0;
	exp original_lab = lab;		/* preserve for extra_diags */

	if (name(e) == test_tag) {
	  if (name(lab) == labst_tag) {
	    exp q = short_next_jump(e);
	    if (q != NULL &&
		 (name(q) == goto_tag ||
		    (name(q) == res_tag && name(son(q)) == top_tag)) &&
		  label_is_next(lab, q)) {
	      shape sha = sh(son(e));
	      if (name(q) == goto_tag) {
	        temp = pt(q);
	        pt(q) = lab;
	      }
	      else {
                temp = getexp(f_bottom, NULL, 0, NULL,
                                NULL, 0, 0, 0);
		ptno(temp) = crt_ret_lab;
		fstack_pos_of(temp) = (prop)first_fl_reg;
	        temp = getexp(f_top, NULL, 0, NULL, temp,
				 0, 0, 0);
	        temp = getexp(f_top, lab, 0, temp, NULL,
				 0, 0, labst_tag);
		crt_ret_lab_used = 1;
	        pt(q) = lab;
	        name(q) = goto_tag;
	        isret = 1;
	      };
	      lab = temp;
	      pt(e) = lab;
	      if (name(sha) < shrealhd || name(sha) > doublehd)
	        settest_number(e,(int)int_inverse_ntest[testno]);
	      else
	        settest_number(e,(int)real_inverse_ntest[testno]);
#ifdef TDF_DIAG4
	      if (current_dg_info)
		current_dg_info->data.i_tst.inv = 1 - current_dg_info->data.i_tst.inv;
#endif
	    };
          };
	  if (!isret)
	    temp = final_dest_test(lab, e);
	  SET(temp);
	  if (pt(son(temp)) == NULL) {
	    ++no(son(temp));
	    pt(son(temp)) = copyexp(pt(son(lab)));
	    ptno(pt(son(temp))) = next_lab();
	  }
	  else
	  if (temp != lab) {
	    --no(son(lab));
	    ++no(son(temp));
	  };
	  pt(e) = temp;
	};
	{
	  where qw;
	  exp arg1 = son(e);
	  exp arg2 = bro(arg1);
	  unsigned char  test_n = test_number(e);
	  exp lab_exp = pt(e);
	  exp jr;
	  int sg;
	  if (name(e) ==test_tag)
	    jr = pt(son(lab_exp));
	  if (!is_o(name(arg1)) || is_crc(arg1)) {
	    /* arg1 is not a possible 80386 operand, precompute it in reg0 */
	    qw.where_exp = copyexp(reg0.where_exp);
	    sh(qw.where_exp) = sh(arg1);
	    qw.where_off = 0;
	    make_code(qw, stack, arg1);
	    arg1 = qw.where_exp;
	  }
#ifdef TDF_DIAG4
	  else
	    diag_arg(dest, stack, arg1);
#endif
	  if (!is_o(name(arg2)) || is_crc(arg2)) {
	    /* arg2 is not a possible 80386 operand, precompute it in reg0 */
	    qw.where_exp = copyexp(reg0.where_exp);
	    sh(qw.where_exp) = sh(arg2);
	    qw.where_off = 0;
	    make_code(qw, stack, arg2);
	    arg2 = qw.where_exp;
	  }
#ifdef TDF_DIAG4
	  else
	    diag_arg(dest, stack, arg2);
#endif

	  switch (name(sh(arg1))) {
	    case scharhd:
	    case swordhd:
	    case slonghd:
	    case offsethd:
	      sg = 1;
	      break;
	    case ucharhd:
	    case uwordhd:
	    case ulonghd:
	    case shrealhd:
	    case realhd:
	    case doublehd:
	    case ptrhd:
	      sg = 0;
	      break;
	    default:
	      sg = is_signed(sh(arg1));
	      break;
	  };

	  if (name(arg1) == val_tag || name(arg1) == env_offset_tag ||
		(name(arg1) == name_tag && isvar(son(arg1)) && isglob(son(arg1)))) {
		/* if only one constant, cmp expects it to be arg2 */
	    exp holde = arg1;
	    arg1 = arg2;
	    arg2 = holde;
	    test_n = exchange_ntest[test_n];
#ifdef TDF_DIAG4
	    if (current_dg_info)
	      current_dg_info->data.i_tst.inv = 1 - current_dg_info->data.i_tst.inv;
#endif
	  };

	  if (name(arg1) == null_tag) {
	    error(ERR_INTERNAL, "test_tag of wrong form");
	  }
	  else {
	    clean_stack();
	    if (name(e) == absbool_tag && sg &&
		(test_n == f_greater_than || test_n == f_less_than_or_equal)) {
	      cond1_set = 0;	/* avoid cmp(0) optimisation to clear overflow */
	    }
	    if (cmp(sh(arg1), mw(arg1, 0), mw(arg2, 0), (int)test_n, e)) {
	      if (sg) {
		sg = -1;   /* ignore overflow when testing sign bit */
	      }
	    }
	    if (name(e) == test_tag) {
	      SET(jr);
#ifdef DWARF2
	      if (current_dg_info) {
		current_dg_info->data.i_tst.brk = set_dw_text_label();
		current_dg_info->data.i_tst.jlab.u.l = ptno(jr);
		current_dg_info->data.i_tst.jlab.k = LAB_CODE;
	      }
#endif
	      branch((int)test_n, jr, sg,(int)name(sh(arg1)));
#ifdef DWARF2
	      if (diag == DIAG_DWARF2) {
	        dw2_start_basic_block();
	      }
	      if (current_dg_info)
	        current_dg_info->data.i_tst.cont = set_dw_text_label();
#endif
	    }
	    else
	    if (!eq_where(dest, zero)) {
	      setcc((int)int_inverse_ntest[test_n], sg,
			(int)name(sh(arg1)));
	      if (shape_size(sh(e)) > 8)
	        and(slongsh, reg0, mw(zeroe, 0xff), reg0);
	      move(sh(e), reg0, dest);
	    };
	  };

	  /* may be needed for extra_diags */
	  pt(e) = original_lab;

	  return;
	};
      };
    case ass_tag:
    case assvol_tag:
      {
	exp assdest = son(e);
	exp assval = bro(assdest);

        if (!newcode && name(sh(assval)) == bitfhd)
         {
           bits_to_mem(assval, e, stack);
           return;
         };

	make_code(mw(e, 0), stack, assval);
	/* set the destination and code the rest */
	return;
      };
    case concatnof_tag:
     {
      int off = dest.where_off + shape_size(sh(son(e)));
      make_code(dest, stack, son(e));
      make_code(mw(dest.where_exp, off),
             stack_room(stack, dest, off), bro(son(e)));
      return;
     };
    case ncopies_tag:
     {
       int i;
       int sz;
       int off;
       if (no(e) == 0)
         return;

       sz = shape_size(sh(e)) /no(e);
       for (i = 0; i < no(e); ++i)
        {
          off = dest.where_off + i*sz;
          make_code(mw(dest.where_exp, off),
                stack_room(stack, dest, off), copyexp(son(e)));
        };
       return;
      };
    case nof_tag:
      {
        exp v = son(e);
        shape sha;
        int off;
        int crt = 0;

        if (v == NULL)
          return;

        sha = sh(v);
        off = rounder(shape_size(sha), shape_align(sha));

        while (1)
         {
           make_code(mw(dest.where_exp, dest.where_off + crt),
                 stack_room(stack, dest, dest.where_off + crt), v);
           if (last(v))
             return;
           crt += off;
           v = bro(v);
         };
      };
    case compound_tag:
      {
        exp v = son(e);
        if (v == NULL)
          return;

        while (1)
         {
           make_code(mw(dest.where_exp, dest.where_off + no(v)),
                 stack_room(stack, dest, dest.where_off + no(v)), bro(v));
           if (last(bro(v)))
             return;
           v = bro(bro(v));
         };
      };
    case apply_tag:
    case apply_general_tag:
      {
	exp proc = son(e);
	exp arg = (!last(proc))? bro(proc): NULL;
	exp cees = NULL;
	exp postlude = NULL;
	int untidy_call = 0;
	int has_checkstack = 0;
	int  longs, more_longs, old_regsinuse, prev_use_bp;
	int multi_reg = (shape_size(sh(e)) > 32 && reg_result(sh(e))
				 && !is_floating(name(sh(e))));
	int old_nip = not_in_params;
	int push_result = 0;
	int post_offset = 0;
	int ret_stack_dec;

	if (builtinproc(e)) {
	  dec* dp = brog(son(proc));
	  char *id = dp -> dec_id;
	  special_ins(id + strlen(name_prefix), arg, dest);
	  return;
	}

	if (name(e) ==apply_general_tag) {
	  arg = son(arg);
	  cees = bro(bro(proc));
	  if (name(bro(cees))!= top_tag)
	    postlude = bro(cees);
	  untidy_call = call_is_untidy(e);
	  has_checkstack = call_has_checkstack(e);
	}

	not_in_params = 0;
	longs = procargs(stack, arg, has_checkstack);
	ret_stack_dec = stack_dec;

	/* may be altered by push_cees */
	prev_use_bp = must_use_bp;

	if (cees == NULL)
	  more_longs = 0;
	else {
	  switch (name(cees)) {
	    case make_callee_list_tag:
	      {
		more_longs = procargs(stack, son(cees), has_checkstack);
		if (call_has_vcallees(cees)) {
		  ins2(leal, 32, 32, mw(ind_sp.where_exp, more_longs), reg0);
		  ins0(pusheax);
		  stack_dec -= 32;
		  more_longs += 32;
		}
		break;
	      }
	    case make_dynamic_callee_tag:
	      {
		exp ptr = son(cees);
		exp siz = bro(ptr);
		more_longs = push_cees(ptr, siz, call_has_vcallees(cees), stack);
		break;
	      }
	    case same_callees_tag:
	      {
		more_longs = push_cees(NULL, NULL, call_has_vcallees(cees), stack);
		break;
	      }
	  }
	}

	check_stack_max;
	reset_fpucon();
	not_in_params = old_nip;
	if (remove_struct_ref) {
	  longs -= no(e);		/* struct return address removed by call */
	  ret_stack_dec += no(e);
	  post_offset = no(e);
	}
	if (postlude == NULL && !untidy_call) {
	  old_regsinuse = regsinuse;
	  if (multi_reg)
	    regsinuse |= 0x2;	/* prevent callins using pop edx */
	  callins(longs, son(e), ret_stack_dec);
	  regsinuse = old_regsinuse;
	}
	else {
	  callins (0, son (e), ret_stack_dec);	/* delay arg stack return */
	  if (untidy_call) {
	    stack_dec = 0;	/* as alloca, must_use_bp */
	    if (need_preserve_stack)
	      save_stack();
	  };
	}
	must_use_bp = prev_use_bp;

	invalidate_dest(mw(NULL, 0));

	clear_low_reg_record(crt_reg_record);
	cond1_set = 0;
	cond2_set = 0;		/* we don't know the state of the conditions */
	if (eq_where(dest, zero))
	{
	  if (reg_result (sh (e))) {/* answer in register */
	    if (name(sh(e)) >= shrealhd && name(sh(e)) <= doublehd) {
	      push_fl;
	      discard_fstack();
	    }
	  }
	}
	else {
	  where temp_dest;
	  if (postlude == NULL)
	    temp_dest = dest;
	  else {
	    push_result = 1;
	    temp_dest = pushdest;
	  }
	  if (reg_result (sh (e))) {
		/* answer in register */
	    if (name(sh(e)) >= shrealhd && name(sh(e)) <= doublehd) {
	      push_fl;
	      move(sh(e), flstack, temp_dest);
	    }
	    else
	      move(sh(e), reg0, temp_dest);
	  }
	  else
	    error(ERR_INTERNAL, STRUCT_RES);  /* compound result */
	}

	if (postlude != NULL) {
	  int sz = rounder(shape_size(sh(e)), param_align);
	  old_nip = not_in_postlude;
	  not_in_postlude = 0;
	  while (name(postlude) == ident_tag && name(son(postlude)) == caller_name_tag) {
	    int n = no(son(postlude));
	    exp a = arg;
	    while (n != 0) {
	      a = bro(a);
	      n--;
	    }
	    if (name(a)!= caller_tag)
	      error(ERR_INTERNAL, BAD_POSTLUDE);
	    no(postlude) = no(a) + stack_dec - post_offset;
	    ptno(postlude) = callstack_pl;
	    postlude = bro(son(postlude));
	  }
	  if (push_result) {
	    stack_dec -= sz;
	    check_stack_max;
	  }
	  make_code(zero, stack, postlude);
	  if (push_result) {
	    if (name(dest.where_exp) == apply_tag) {
	      move(sh(e), ind_sp, dest);
	      stack_dec += sz;
	    }
	    else {
	      longs += shape_size(sh(e));
	      if (dest.where_exp == ind_sp.where_exp)
		dest.where_off += longs;
	      move(sh(e), ind_sp, dest);
	    }
	  }
	  stack_return(longs);
	  not_in_postlude = old_nip;
	}

	return;
      };
    case tail_call_tag:
      {
	exp proc = son(e);
	exp cees = bro(proc);
	int longs;
	int prev_use_bp = must_use_bp;	/* may be altered by push_cees */
	int old_nip = not_in_params;
	int old_stack_dec = stack_dec;
	not_in_params = 0;
	switch (name(cees)) {
	  case make_callee_list_tag:
	    {
	      not_in_params = 0;
	      longs = procargs(stack, son(cees), call_has_checkstack(e));
	      not_in_params = old_nip;
	      break;
	    }
	  case make_dynamic_callee_tag:
	    {
	      longs = push_cees(son(cees), bro(son(cees)), 0, stack);
	      break;
	    }
	  case same_callees_tag:
	    {
	      longs = 0;
	      break;
	    }
	}
	check_stack_max;

	/* clear off any unwanted fstack registers */
	{
	  int good_fs = fstack_pos;
	  while (fstack_pos > first_fl_reg)
	    discard_fstack();
	  fstack_pos = good_fs;
	  reset_fpucon();
	}

	if (longs == 0) {
	  make_code(reg0, stack, proc);	/* proc value to %eax */
	  restore_callregs(0);
		/* stack reduced to old callees and return address */

	  if (name(cees) == same_callees_tag) {
	    if (callee_size < 0 && !call_has_vcallees(cees)) {
	      asm_printop("popl %s", "%ecx");
	      asm_printop("movl %s, (%s)", "%ecx", "%esp");
	    }
	    if (callee_size >= 0 && call_has_vcallees(cees)) {
	      asm_printop("popl %s", "%ecx");
	      asm_printop("leal %d(%s),%s", callee_size / 8, "%esp", "%edx");
	      asm_printop("pushl %s", "%edx");
	      asm_printop("pushl %s", "%ecx");
	    }
	  }
	  else {
	    if (callee_size != 0 || call_has_vcallees(cees)) {
	      asm_printop("popl %s", "%ecx");
	      if (callee_size < 0) {
		asm_printop("popl %s", "%edx");
		asm_printop("movl %s,%s", "%edx", "%esp");
	      }
	      else
	      if (callee_size == 0)
		asm_printop("movl %s %s", "%esp", "%edx");
	      else {
		asm_printop("leal %d(%s),%s", callee_size / 8, "%esp", "%edx");
		asm_printop("movl %s,%s", "%edx", "%esp");
	      }
	      if (call_has_vcallees(cees))
		asm_printop("pushl %s", "%edx");
	      asm_printop("pushl %s", "%ecx");
	    }
	  }
	  asm_printop("jmp *%s", "%eax");
	  asm_printf("\n");
	}
	else {
			/* callees have been pushed */
	  if (call_has_vcallees(cees)) {
	    if (callee_size >= 0) {
	      asm_printf("\tleal ");
	      rel_ap(4 + callee_size/8, 1);
	      asm_printf(",%s\n", "%eax");
	      ins0(pusheax);
	    }
	    else {
	      asm_printf("\tpushl ");
	      rel_ap(4, 1);
	    }
	    asm_printf("\n");
	    stack_dec -= 32;
	  }
	  asm_printf("\tpushl ");
	  rel_ap (0, 1);	/* push return address after callees */
	  asm_printf("\n");
	  stack_dec -= 32;
	  make_code(pushdest, stack, proc);	/* push proc for call by return */
	  stack_dec -= 32;
	  check_stack_max;
	  if (longs < 0) {	/* must be dynamic_callees */
	    exp sz = bro(son(cees));
	    move(slongsh, mw(sz,0), reg2);
	    if (al2(sh(sz)) < param_align) {
	      if (al2(sh(sz)) == 1) {
		asm_printop("addl $31,%s", "%ecx");
		asm_printop("shrl $3,%s", "%ecx");
	      }
	      else
		asm_printop("addl $3,%s", "%ecx");
	      asm_printop("andl $-4,%s", "%ecx");
	    }
	  }
	  if (!call_has_vcallees(cees)) {
	    if (callee_size >= 0) {
	      asm_printf("\tleal ");
	      rel_ap(4 + callee_size/8, 1);
	      asm_printf(",%s", "%eax");
	    }
	    else {
	      asm_printf("\tmovl ");
	      rel_ap(4, 1);
	      asm_printf(",%s\n", "%eax");
	    }
	  }

	  restore_callregs(1);

		/*
		 * callees, return and proc to call are stacked
		 * size in %ecx if longs<0; callers at %eax unless stacked for vcallees
		 */
	  asm_printop("pushl %s", "%esi");
	  asm_printop("pushl %s", "%edi");
	  if (call_has_vcallees(cees))
	    asm_printop("movl 16(%s),%s", "%esp", "%edi");
	  else
	    asm_printop("movl %s,%s", "%eax", "%edi");
	  if (longs < 0) {
	    asm_printop("addl $%d, %s", call_has_vcallees(cees) ? 20 : 16, "%ecx");
	    asm_printop("leal -4(%s),%s", "%esp", "%esi");
	    asm_printop("addl %s,%s", "%ecx", "%esi");
	    asm_printop("shrl $2,%s", "%ecx");
	  }
	  else {
	    asm_printop("movl $%d,%s",    longs / 32 + call_has_vcallees(cees) ?  5 :  4, "%ecx");
	    asm_printop("leal %d(%s),%s", longs /  8 + call_has_vcallees(cees) ? 16 : 12, "%esp", "%esi");
	  }
	  asm_printop("subl $4,%s", "%edi");
	  asm_printop("std");
	  asm_printop("rep");
	  asm_printop("movsl");
	  asm_printop("cld");
	  asm_printop("leal 4(%s),%s", "%edi", "%esp");
	  asm_printop("popl %s", "%edi");
	  asm_printop("popl %s", "%esi");
	  asm_printop("ret");
	}

	cond1_set = 0;
	cond2_set = 0;
	stack_dec = old_stack_dec;
	must_use_bp = prev_use_bp;
	return;
      };
    case alloca_tag:
      {
	where sz_where;
        if (name(son(e)) == val_tag)
          {
	    int n = no(son(e));
	    if (name(sh(son(e)))!= offsethd)
	      n = 8 * n;
	    sz_where = mw(zeroe, rounder(n, stack_align) /8);
          }
        else {
	  exp temp = getexp(slongsh, NULL, 0, NULL, NULL, 0, 0, val_tag);
          if (name(sh(son(e))) == offsethd && al2(sh(son(e))) == 1) {
	    no(temp) = 31;
	    bop(add, ulongsh, temp, son(e), reg0, stack);
            shiftr(ulongsh, mw(zeroe,3), reg0, reg0);
	    and(ulongsh, mw(zeroe, -4), reg0, reg0);
	    sz_where = reg0;
          }
          else if (al2(sh(son(e))) < 32) {
	    no(temp) = 3;
	    bop(add, ulongsh, temp, son(e), reg0, stack);
	    and(ulongsh, mw(zeroe, -4), reg0, reg0);
	    sz_where = reg0;
          }
	  else {
	    sz_where = reg0;
	    make_code(sz_where, stack, son(e));
	  }
	  retcell(temp);
        };
	if (checkalloc(e))
	  checkalloc_stack(sz_where, 1);	/* uses reg1 */
	else
	  sub(ulongsh, sz_where, sp, sp);
	if (!eq_where(dest, zero))
	  move(sh(e), sp, dest);
	if (need_preserve_stack)
	  save_stack();
	return;
      };
    case last_local_tag:
      {
	move(sh(e), sp, dest);
	return;
      };
    case local_free_tag:
        move(slongsh, mw(son(e),0), sp);
        if (name(bro(son(e))) == val_tag)
          {
            int sz;
	    int n = no(bro(son(e)));
	    if (name(sh(bro(son(e))))!= offsethd)
	      n = 8 * n;
	    sz = rounder(n, stack_align);
            add(slongsh, mw(zeroe, sz/8), sp, sp);
          }
	else
	    add(slongsh, mw(bro(son(e)), 0), sp, sp);
	add(slongsh, mw(zeroe, 3), sp, sp);
	and(slongsh, mw(zeroe, -stack_align/8), sp, sp);
	if (need_preserve_stack)
	  save_stack();
        return;
    case local_free_all_tag:
        set_stack_from_bp();
	if (need_preserve_stack)
	  save_stack();
        return;
    case ignorable_tag:
	make_code(dest, stack, son(e));
	return;
    case res_tag:
    case untidy_return_tag:
      {
	int old_stack_dec = stack_dec;
#ifdef DWARF2
	long over_lab;
#endif
	cond1_set = 0;
	cond2_set = 0;
	{
	  /* procedure call not inlined, this res is for a procedure */
	  if (reg_result (sh (son (e)))) {/* answer to registers */
	    int with_fl_reg = 0;
	    /* int simple_res = (name(son(e)) == val_tag); */
	    int  good_fs;

	    /* if (!simple_res) */
	    {
	      if (name(sh(son(e))) >= shrealhd &&
		  name(sh(son(e))) <= doublehd) {
	        make_code(flstack, stack, son(e));
	        with_fl_reg = 1;
	      }
	      else {
	        make_code(reg0, stack, son(e));
	      };
	    };

	    if (name(sh(son(e)))!= bothd) {
	      good_fs = fstack_pos;
	      if (with_fl_reg) {
			/* jumping with a floating value */

	        /* clear off any unwanted stack registers */
	        while (fstack_pos > (first_fl_reg + 1))
	          discard_st1();
	        fstack_pos = good_fs - 1;
	      }
	      else {
	        /* clear off any unwanted stack registers */
	         while (fstack_pos > first_fl_reg)
	          discard_fstack();
	        fstack_pos = good_fs;
	      };
	      reset_fpucon();
	      if (name(e) ==untidy_return_tag) {
		int old_regsinuse = regsinuse;
		regsinuse &= ~0x6;	/* %ecx, %edx not preserved */
		if (shape_size(sh(son(e))) > 32 && !with_fl_reg)
		  regsinuse |= 0x2;	/* %edx used for return value */
		if (stack_dec != 0)
		  stack_return(-stack_dec);
		regsinuse = old_regsinuse;
		asm_printf("\tpushl ");
		rel_ap (0, 1);	/* push return address for return after pops */
		asm_printf("\n");
#ifdef DWARF2
		if (diag == DIAG_DWARF2)
		  dw2_untidy_return();
#endif
	      }
#ifdef DWARF2
	      if (diag == DIAG_DWARF2) {
		over_lab = next_dwarf_label();
		dw2_return_pos(over_lab);
	      }
#endif
	      restore_callregs(name(e) ==untidy_return_tag);
#if 0
	      if (simple_res) {	/* now done earlier for dw2_returns consistency */
	        make_code(reg0, stack, son(e));
	      };
#endif

	      if (name(e) ==untidy_return_tag)
		ins0(ret);
	      else
		retins();
	      asm_printf("\n");
#ifdef DWARF2
	      if (diag == DIAG_DWARF2)
		dw2_after_fde_exit(over_lab);
#endif
	    };
	    stack_dec = old_stack_dec;
	    return;
	  };
	  error(ERR_INTERNAL, STRUCT_RETURN);
	  return;
	};
      };
    case return_to_label_tag:
      {
	int good_fs = fstack_pos;
		/* clear off any unwanted stack registers */
	while (fstack_pos > first_fl_reg)
	  discard_fstack();
	fstack_pos = good_fs;
	reset_fpucon();
	move(slongsh, mw(son(e), 0), reg0);
	restore_callregs(0);
	ins0("jmp *%eax");
	return;
      };
    case movecont_tag:
      {
	exp frome = son(e);
	exp toe = bro(frome);
	exp lengthe = bro(toe);
	movecont(mw(frome, 0), mw(toe, 0), mw(lengthe, 0),
		  isnooverlap(e));
	return;
      };
    case solve_tag:
      {
	exp jr = getexp(f_bottom, NULL, 0, NULL, NULL, 0,
	    0, 0);
	clean_stack();
        sonno(jr) = stack_dec;
        ptno(jr) = next_lab();
        fstack_pos_of(jr) = (prop)fstack_pos;
	/* jump record for end */
	solve(son(e), son(e), dest, jr, stack);
	if (name(sh(e))!= bothd) {
	  align_label(0, jr);
	  set_label(jr);
#ifdef DWARF2
	  if (diag == DIAG_DWARF2) {
	    dw2_start_basic_block();
	  }
#endif
	};
	fpucon = normal_fpucon;
	cond1_set = 0;
	cond2_set = 0;
	return;
      };
    case case_tag:
      {
	where qw;
	exp arg1 = son(e);
	exp b = bro(arg1);
	exp t = arg1;
	while (!last(t))
	  t = bro(t);
	bro(t) = NULL;

	if (!is_o(name(arg1)) || is_crc(arg1)) {
				/* argument is not a possible 80386
				   operand, precompute it in reg0 */
	  qw.where_exp = copyexp(reg0.where_exp);
	  sh(qw.where_exp) = sh(arg1);
	  qw.where_off = 0;
	  make_code(qw, stack, arg1);
	  arg1 = qw.where_exp;
	  bro(arg1) = b;
	};

	clean_stack();

	IGNORE caser(arg1, name(sh(e)) == bothd, e);

	return;
      };
#ifndef TDF_DIAG4
    case diagnose_tag:  {
	diag_info * d = dno(e);
	if (d->key == DIAG_INFO_SOURCE) {
	  crt_lno = natint(d -> data.source.beg.line_no);
	  crt_charno = natint(d -> data.source.beg.char_off);
	  crt_flnm = d -> data.source.beg.file->file.ints.chars;
	};
        diag3_driver->output_diag(d, crt_proc_id, e);
        make_code(dest, stack, son(e));
        diag3_driver->output_end_scope(d, e);
        return;
      };
#endif
    case trap_tag: {
	trap_ins(no(e));
	return;
      }
    case asm_tag: {
	if (props(e))
	  asm_ins(e);
	else {
	  start_asm();
          make_code(dest, stack, son(e));
	  end_asm();
	}
	clear_low_reg_record(crt_reg_record);
	return;
      }
    default:
      if (!is_a(name(e))) {
	error(ERR_INTERNAL, BADOP);
	return;
      };

      if (name(dest.where_exp)!= val_tag)
	codec(dest, stack, e);
      else
      if (!optop(e)) {
	if (name(sh(e)) >= shrealhd && name(sh(e)) <= doublehd) {
	  codec(flstack, stack, e);
	  discard_fstack();
	}
	else
	  codec(reg0, stack, e);
      }
      else
      if (name(e)!=name_tag && name(e)!=env_offset_tag && son(e)!=NULL) {
	exp l = son(e);		/* catch all discards with side-effects */
	for (;;) {
	  make_code(dest, stack, l);
	  if (last(l))break;
	  l = bro(l);
	}
      }
      return;
  };
}

#ifdef TDF_DIAG4
struct coder_args {
	where dest;
	ash stack;
	exp e;
};

static void make_code2
(void * args)
{
  struct coder_args * x = (struct coder_args *)args;
  make_code1(x->dest, x->stack, x->e);
  return;
}

static dg_where dg_where_dest
(exp e)
{
  dg_where w;
  if (name(e) == name_tag || name(e) == reff_tag) {
    w = dg_where_dest(son(e));
    w.o += no(e) /8;
    return w;
  }
  if (name(e)!= ident_tag)
    error(ERR_INTERNAL, "bad dg_where");
  if (isglob(e)) {
    w.k = WH_STR;
    w.u.s = (brog(e)) ->dec_id;
    w.o = 0;
    return w;
  }
  if (ptno(e) < 0 || ptno(e) > 10)	/* contop case */
    return dg_where_dest(son(e));
  switch (ptno(e)) {
    case local_pl: {
      w.k = WH_REGOFF;
      w.u.l = -2;
      w.o = no(e) /8;
      break;
    }
    case par_pl: {
      w.k = WH_REGOFF;
      w.u.l = -1;
      w.o = (no(e) /8) + 4;
      break;
    }
    case reg_pl: {
      w.k = WH_REG;
      w.u.l = get_reg_no(no(e));
      break;
    }
    default:
      error(ERR_INTERNAL, "bad dg_where");
      SET(w);
  }
  return w;
}

static dg_where contop_where
(exp id)
{
  return dg_where_dest(bro(son(id)));
}


dg_where find_diag_res
(void * args)
{
  struct coder_args * x = (struct coder_args *)args;
  exp e = x->dest.where_exp;
  dg_where w;
  switch (name(e)) {
    case val_tag: {
      w.k = NO_WH;
      break;
    }
    case ident_tag:
    case name_tag: {
      w = dg_where_dest(e);
      break;
    }
    case ass_tag: {
      if (name(son(e)) == ident_tag)
	w = contop_where(son(e));
      else
	w = dg_where_dest(son(e));
      break;
    }
    case apply_tag: {
      w.k = WH_REGOFF;
      w.u.l = get_reg_no(no(son(sp.where_exp)));
      w.o = 0;
      break;
    }
    default:
      error(ERR_INTERNAL, "unexpected diag_res dest");
      SET(w);
  }
  return w;
}

void make_code
(where dest, ash stack, exp e)
{
  dg_info d;
  dg_info was_current = current_dg_info;
  current_dg_info = nildiag;
  if (extra_diags) {
    switch (name(e)) {
      case apply_tag:
      case apply_general_tag: {
	d = dgf(e);
	while (d && d->key != DGA_CALL)
	  d = d->more;
	if (!d) {
	  d = new_dg_info(DGA_CALL);
	  d->data.i_call.clnam = NULL;
	  d->data.i_call.pos = no_short_sourcepos;
	  d->data.i_call.ck = 0;
	  dgf(e) = combine_diaginfo(dgf(e), d);
	}
	break;
      }
      case test_tag: {
	d = dgf(e);
#if DWARF2
	if (dw_doing_branch_tests)
	  break;
#endif
	while (d && d->key != DGA_TEST)
	  d = d->more;
	if (!d) {
	  d = new_dg_info(DGA_TEST);
	  d->data.i_tst.pos = no_short_sourcepos;
	  d->data.i_tst.inv = 0;
	  dgf(e) = combine_diaginfo(dgf(e), d);
	}
	break;
      }
      case goto_tag: {
	short_sourcepos p;
	d = dgf(e);
#if DWARF2
	if (dw_doing_branch_tests)
	  break;
#endif
	p = no_short_sourcepos;
	while (d && d->key != DGA_JUMP) {
	  if (d->key == DGA_SRC)
	    p = d->data.i_src.startpos;
	  d = d->more;
	}
	if (!d) {
	  d = new_dg_info(DGA_JUMP);
	  d->data.i_tst.pos = p;
	  dgf(e) = combine_diaginfo(dgf(e), d);
	}
	break;
      }
      case goto_lv_tag:
      case return_to_label_tag:
      case long_jump_tag:
      case tail_call_tag: {
	d = dgf(e);
#if DWARF2
	if (dw_doing_branch_tests)
	  break;
#endif
	while (d && d->key != DGA_LJ)
	  d = d->more;
	if (!d) {
	  d = new_dg_info(DGA_LJ);
	  d->data.i_tst.pos = no_short_sourcepos;
	  dgf(e) = combine_diaginfo(dgf(e), d);
	}
	break;
      }
    }
  }
  d = dgf(e);
  if (d != nildiag) {
    dg_info dpos = nildiag;
    struct coder_args args;
    args.dest = dest;
    args.stack = stack;
    current_dg_exp = args.e = e;
    while (d != nildiag) {
      if (d->key == DGA_SRC && d->data.i_src.startpos.file) {
	crt_lno = d->data.i_src.startpos.line;
	crt_charno = d->data.i_src.startpos.column;
	crt_flnm = d->data.i_src.startpos.file->file_name;
        if (d->data.i_src.endpos.file) {
	  dpos = d;
	  break;
	}
      };
      d = d->more;
    };
#ifndef TDF_DIAG4
    diag3_driver->code_diag_info(dgf(e), crt_proc_id, make_code2,(void*) &args);
#else
#if DWARF2
    if (diag == DIAG_DWARF2) {
      dw2_code_info(dgf(e), make_code2, (void*) &args);
    }
#else
    diag4_driver->code_diag_info(dgf(e), make_code2,(void*) &args);
#endif
#endif
    if (dpos) {
      crt_lno = dpos->data.i_src.endpos.line;
      crt_charno = dpos->data.i_src.endpos.column;
      crt_flnm = dpos->data.i_src.endpos.file->file_name;
    };
  }
  else
    make_code1(dest, stack, e);
  current_dg_info = was_current;
  return;
}



static void done_arg
(void * args)
{
  UNUSED(args);
  return;
}

void diag_arg
(where dest, ash stack, exp e)
{
  if (dgf(e)) {
    struct coder_args args;
    args.dest = dest;
    args.stack = stack;
    current_dg_exp = args.e = e;
#ifndef TDF_DIAG4
    diag3_driver->code_diag_info(dgf(e), crt_proc_id, done_arg,(void*) &args);
#else
#if DWARF2
    if (diag == DIAG_DWARF2) {
      dw2_code_info(dgf(e), done_arg, (void*) &args);
    }
#else
    diag4_driver->code_diag_info(dgf(e), done_arg,(void*) &args);
#endif
#endif
  }
}

#endif

