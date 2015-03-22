/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * Defines the scan through a program which reorganises it so that all
 * arguments of operations are 80386 operands. 80386 specific.
 *
 * These procedures use a pair of a boolean and and exp (eg sto and to)
 * instead of a pointer to an exp. The boolean is true if the exp being
 * referred to is the son of the given exp, and false if it is the brother.
 *
 * This is to allow exps to be represented by indices into arrays and to
 * allow the arrays to be realloced, which invalidates the use of
 * &son(to) and &bro(to).
 */

#include <stddef.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <reader/exp.h>

#include <reader/externs.h>
#include <reader/basicread.h>

#include <construct/exp.h>
#include <construct/tags.h>
#include <construct/shape.h>
#include <construct/label_ops.h>
#include <construct/install_fns.h>

#include <main/flags.h>

#include "localtypes.h"
#include "make_code.h"
#include "instr386.h"
#include "scan.h"
#include "localexpmacs.h"

#define assexp(isson, p, v) if (isson)setson(p, v); else setbro(p, v)
#define contexp(isson, p)((isson)? son(p): bro(p))

/*
 * Inserts an identity declaration of x at to,
 * and replaces x by a use of the identifier
 */
static void cca
(int sto, exp to, int sx, exp x)
{
  exp def, ato, id, tg;
  def = contexp(sx, x);
  if (name(def)==caller_tag) {	/* position sensitive */
    cca(sto, to, 1, def);
    return;
  }
  ato = contexp(sto, to);
  id = getexp(sh(ato), bro(ato), (int)(last(ato)), def, NULL,
      0, 1, ident_tag);
  tg = getexp(sh(def), bro(def), (int)(last(def)), id, NULL,
      0, 0, name_tag);
  pt(id) = tg;
  clearlast(def);
  if (def != ato) {
    bro(def) = ato;
    bro(ato) = id;
    setlast(ato);
    assexp(sto, to, id);
    assexp(sx, x, tg);
  }
  else {
    bro(def) = tg;
    bro(tg) = id;
    setlast(tg);
    clearlast(def);
    assexp(sto, to, id);
  }
#ifdef TDF_DIAG4
  if (diag != DIAG_NONE) {
    dgf(id) = dgf(bro(son(id)));
    dgf(bro(son(id))) = nildiag;
  }
#endif
}

/*
 * Keeping the same to, scans along the bro list e, applying cca to introduce
 * an identity declaration when doit is 1.
 *
 * Keeps count as the index position along the list in order to pass it to doit.
 *
 * If it uses cca it scans the resulting declaration, using the same to. If it
 * doesnt use cca, it scans the list element, still using the same to.
 * This keeps all operations in the same order.
 *
 * Result of cc is true if the operands are all of 80386 form. Some operations
 * are allowed to have not more than one operand not of 80386 form; this is then
 * precomputed in reg0 before the operations. This boolean result is used
 * to ensure that not more than one operand is so treated.
 */
static int cc
(int sto, exp to, int se, exp e,	      int(*doit)(exp, int, int),
 int count, int usereg0)
{
  int unused = usereg0;	/* can still use reg0 */
  exp ec = contexp(se, e);
  if (last(ec)) {
    if (doit(ec, count, unused)) {
      cca(sto, to, se, e);
      ec = contexp(sto, to);
      return scan(1, ec, son(ec), unused);
    }
    else {
      if (unused)
	return scan(se, e, ec, 1);
      return scan(sto, to, ec, unused);
    }
  }
  else {
    unused = cc(sto, to, 0, ec, doit, count + 1, unused);
    /* can we still use reg0? */
    ec = contexp(se, e);
    if (doit(ec, count, unused)) {
      cca(sto, to, se, e);
      ec = contexp(sto, to);
      return scan(1, ec, son(ec), unused);
    }
    else {
      if (unused)
	return scan(sto, to, ec, 1);
      return scan(sto, to, ec, unused);
    }
  }
}

/*
 * Keeping the same to, scans along the bro list e, applying cca to introduce
 * an identity declaration when doit is 1.
 *
 * Keeps count as the index position along the list in order to pass it to doit.
 *
 * If it uses cca it scans the resulting declaration, using the same to. If it
 * doesnt use cca, it scans the list element, still using the same to.
 * This keeps all operations in the same order.
 *
 * The difference in detail from cc supports the asymmetry of div etc.
 */
static void cc1
(int sto, exp to, int se, exp e,	      int(*doit)(exp, int, int),
 int count, int usereg0)
{
  int unused = ((count == 1)? usereg0 : 0);
	/* can we still use reg0? */
  exp ec = contexp(se, e);
  if (last(ec)) {
    if (doit(ec, count, unused)) {
      cca(sto, to, se, e);
      ec = contexp(sto, to);
      IGNORE scan(1, ec, son(ec), unused);
      return;
    }
    else {
      if (unused) {
	IGNORE scan(se, e, ec, 1);
        return;
      }
      IGNORE scan(sto, to, ec, unused);
      return;
    }
  }
  else {
    cc1(sto, to, 0, ec, doit, count + 1, unused);
    /* can we still use reg0? */
    ec = contexp(se, e);
    if (doit(ec, count, unused)) {
      cca(sto, to, se, e);
      ec = contexp(sto, to);
      IGNORE scan(1, ec, son(ec), unused);
      return;
    }
    else {
      if (unused) {
	IGNORE scan(se, e, ec, 1);
	return;
      }
      IGNORE scan(sto, to, ec, unused);
      return;
    }
  }
}

/*
 * Does cca and forces the declaration to use a register
 */
static void ccp
(int sto, exp to, int sx, exp x)
{
  exp toc;
  cca(sto, to, sx, x);
  toc = contexp(sto, to);
  setusereg(toc);
  IGNORE scan(1, toc, son(toc), 0);
}

/*
 * Is an operand
 */
static int is_opnd
(exp e)
{
				/* make sure (is_o && is_crc -> !is_opnd) */
  unsigned char  n = name(e);
  if (n == name_tag) {
    if (isvar(son(e)))
	return isglob(son(e)) && !PIC_code;
    return son(son(e))!= NULL &&
	(!isglob(son(e)) || !PIC_code || name(sh(son(e)))!= prokhd ||
				(brog(son(e)) -> extnamed)) &&
	(name(son(son(e)))!= ident_tag || !isparam(son(son(e))));
  }
  return 
      n == val_tag || n == real_tag || n == env_size_tag ||
      n == cont_tag ||
      n == string_tag ||
      n == null_tag ||
      n == proc_tag || n == general_proc_tag;
}

/*
 * This checks the integer argument of an addptr to make sure that it is of the
 * right form, including the scale factor for the kind of operand.
 *
 * This introduces two declarations, only the inner one forces the use of
 * a register.
 *
 * This guarantees that we only load the registers as close to the actual
 * instruction as possible, since we are short of registers on the 80386
 */
static void ap_argsc
(int sto, exp to, exp e)
{
  exp p, a, q;
  int  k;
  int do1 = 1;

  if (name(son(e)) == reff_tag)
    q = son(son(e));
  else
    q = son (e);		/* q must be addptr - all addptrs processed here */

  if ((frame_al_of_ptr(sh(son(q))) & al_includes_vcallees) &&
	(frame_al1_of_offset(sh(bro(son(q)))) & al_includes_caller_args)) {
				/* env_offset to arg requires indirection from frame pointer */
    shape pc_sh = f_pointer(f_callers_alignment(0));
    exp c = getexp(pc_sh, bro(son(q)), 0, NULL, NULL, 0, 0, cont_tag);
    exp r = getexp(pc_sh, c, 1, son(q), NULL, 0, 64, reff_tag);
    setfather(r, son(q));
    son(c) = r;
    son(q) = c;
  }

  p = son(q);
  a = bro(p);

  if (name(p) == name_tag && isvar(son(p)) && isglob(son(p)))
    do1 = 0;

  if (do1)
    ccp(1, e, 1, q);

  if (name(a) == offset_mult_tag && name(bro(son(a))) == val_tag &&
  (k = no(bro(son(a))), k == 8 || k == 16 || k == 32 || k == 64))
    ccp(1, e, 1, bro(son(q)));
  else
    ccp(1, e, 0, son(q));

  if (do1) {
    cca(sto, to, 1, son(e));
    cca(sto, to, 1, bro(son(son(e))));
  }
  else
    cca(sto, to, 1, son(e));
}

/*
 * Checks that the argument of a cont or the destination of an assign has the
 * right form for an operand, and introduces a declaration if not.
 *
 * Continues processing with the same to.
 *
 * These arguments can contain declarations, so that we can load addresses as
 * close as possible to the instructions that use them, since we are short
 * of registers in the 80386.
 *
 * This is done by contop in instr386, during the code production.
 */
static int cont_arg
(int sto, exp to, exp e, int usereg0)
{
  unsigned char  n = name(son(e));


    if (n == name_tag && isvar(son(son(e))))
      return usereg0;

    if (n == cont_tag && usereg0 && shape_size(sh(e)) <= 32) {
      cont_arg(sto, to, son(e), 1);
      return 0;
    }

    if (n == reff_tag) {
      exp s = son(son(e));
      if (name(s) == name_tag) {
	if (isusereg(son(s)))
          return 0;
        if (!PIC_code && isglob(son(s)) && isvar(son(s)))
          return 0;
      }

      if (name(s) == cont_tag && usereg0 && shape_size(sh(e)) <= 32) {
	cont_arg(sto, to, s, 1);
	return 0;
      }

      if (name(s) == addptr_tag) {
	ap_argsc(sto, to, e);
	return 0;
      }
    }


    if (n == addptr_tag) {
      ap_argsc(sto, to, e);
      return 0;
    }

  if (n == reff_tag)
    ccp(1, e, 1, son(e));
  else
    ccp(1, e, 1, e);

  cca(sto, to, 1, son(e));

  return 0;
}

/* Is assignable */
static int is_assable
(exp e)
{
  return is_a(name(e)) || name(e) == alloca_tag ||
	((name(e) == apply_tag || name(e) == apply_general_tag) &&
	(name(sh(e)) <= ulonghd || name(sh(e)) == ptrhd));
}

/* doit routine, is not an operand */
static int notopnd
(exp t, int c, int usereg0)
{
  UNUSED(c);
  if (usereg0) {
    if (is_opnd(t))
      return 0;
    return !is_assable(t);
  }
  return !is_opnd(t);
}

static int scan_for_alloca(exp);

static int scan_alloc_args
(exp s)
{
  if (scan_for_alloca(s))
    return 1;
  if (last(s))
    return 0;
  return scan_alloc_args(bro(s));
}

static int scan_for_alloca
(exp t)
{
  switch (name(t)) {
    case local_free_all_tag:
    case local_free_tag:
    case last_local_tag:
    case alloca_tag:
    case make_lv_tag:
      return 1;
    case case_tag:
      return scan_for_alloca(son(t));
    case labst_tag:
      return scan_for_alloca(bro(son(t)));
    case env_offset_tag:
    case string_tag:
    case name_tag:
      return 0;
    case apply_general_tag:
      if call_is_untidy(t)
	return 1;
      return scan_alloc_args(son(t));
    default:
      if (son(t) == NULL)
        return 0;
      return scan_alloc_args(son(t));
  }
}

static int no_alloca
(exp t, int c, int usereg0)
{
  UNUSED(c); UNUSED(usereg0);
  return scan_for_alloca(t);
}

/* Uses cc, requiring all to be operands */
static void all_opnd
(int sto, exp to, exp e, int usereg0)
{
  IGNORE cc(sto, to, 1, e, notopnd, 1, usereg0);
}

/* doit routine, not assignable */
static int notass
(exp t, int i, int usereg0)
{
  UNUSED(i); UNUSED(usereg0);
  return !is_assable(t);
}

/* Uses cc, requiring all to be assignable */
static void all_assable
(int sto, exp to, exp e)
{
  IGNORE cc(sto, to, 1, e, notass, 1, 1);
}

/* Just used in the next routine */
static int is_direct
(exp e)
{
  unsigned char  s = name(e);
  return (s == name_tag && !isglob(son(e)) && !isvar(son(e))) ||
  (s == cont_tag && name(son(e)) == name_tag &&
	!isglob(son(son(e))) && isvar(son(son(e))));
}

/* Is indirectly addressable */
static int is_indable
(exp e)
{
  unsigned char  s = name(e);
  if (s == name_tag)
    return 1;

  if (s == cont_tag) {
    unsigned char  t = name(son(e));
    return (t == name_tag && isvar(son(son(e)))) ||
	(t == cont_tag && name(son(son(e))) == name_tag &&
	  isvar(son(son(son(e))))) ||
	(t == reff_tag && is_direct(son(son(e))));
  }

  return (s == reff_tag && is_direct(son(e))) ||
      s == addptr_tag;
}

/* son must be indirectly addressable */
static void indable_son
(int sto, exp to, exp e)
{
  if (!is_indable(son(e))) {
    exp ec;
    cca(sto, to, 1, e);
    ec = contexp(sto, to);
    IGNORE scan(1, ec, son(ec), 0);
  }
  else
    IGNORE scan(sto, to, son(e), 0);
}

/* Apply scan to this bro list, moving "to" along it */
static void scanargs
(int st, exp e, int usereg0)
{
  exp t = e;
  exp temp;

  while (temp = contexp(st, t), IGNORE scan(st, t, temp, usereg0),
      temp = contexp(st, t), !last(temp)) {
    t = contexp(st, t);
    st = 0;
  }
}

/* doit routine for plus first arg cant be negate, others can */
static int plusdo
(exp t, int i, int usereg0)
{
  UNUSED(i);
  if (usereg0)
    return 0;
  if (name(t) == neg_tag)
    return 0;
  return !is_opnd(t);
}

/* doit routine for mult */
static int multdo
(exp t, int i, int usereg0)
{
  UNUSED(i);
  return usereg0 ? 0 : !is_opnd(t);
}

/* doit routine for and */
static int anddo
(exp t, int i, int usereg0)
{
  UNUSED(i);
  return usereg0 ? 0 : !is_opnd(t);
}

/* doit routine for xor */
static int notado
(exp t, int i, int usereg0)
{
  UNUSED(i);
  return usereg0 ? 0 : !is_opnd(t);
}

/* Change offset representation bytes to bits */
static void make_bitfield_offset
(exp e, exp pe, int spe, shape sha)
{
  exp omul;
  exp val8;
  if (name(e) == val_tag)
    return;
  omul = getexp(sha, bro(e), (int)(last(e)), e, NULL, 0, 0, offset_mult_tag);
  val8 = getexp(slongsh, omul, 1, NULL, NULL, 0, 8, val_tag);
  clearlast(e);
  setbro(e, val8);
  assexp(spe, pe, omul);
}

static void scan_apply_args
(int spto, exp pto, int sato, exp ato)
{
  if (scan_alloc_args(contexp(sato, ato)))
    IGNORE cc(spto, pto, sato, ato, no_alloca, 1, 0);
  else
    IGNORE scanargs(sato, ato, 1);
}

/* Avoid registers corrupted by dynamic callees */
static void cca_for_cees
(int sto, exp to, exp e)
{
  if (name(son(e)) == name_tag) {
    if (!isglob(son(son(e))))
      set_intnl_call(son(son(e)));
    return;
  }
  if (name(son(e)) == cont_tag && name(son(son(e))) == name_tag) {
    if (!isglob(son(son(son(e)))))
      set_intnl_call(son(son(son(e))));
    return;
  }
  cca(sto, to, 1, e);
  set_intnl_call(contexp(sto, to));
}

static int is_asm_opnd
(exp e, int ext)
{
  unsigned char n = name(e);

  UNUSED(ext);

  if (n == name_tag) {
    setvis(son(e));
    return 1;
  }
  if (n == cont_tag && name(son(e)) == name_tag && isvar(son(son(e)))) {
    setvis(son(son(e)));
    return 1;
  }
  return n == val_tag || n == real_tag || n == null_tag ||
	(n == reff_tag && name(son(e)) == name_tag);
}

static int is_asm_var
(exp e, int ext)
{
  unsigned char n = name(e);

  UNUSED(ext);

  if (n == name_tag && isvar(son(e))) {
    setvis(son(e));
    return 1;
  }
  return 0;
}

void check_asm_seq
(exp e, int ext)
{
  if (name(e) == asm_tag) {
    if ((asm_string(e) && name(son(e)) == string_tag) ||
	(asm_in(e) && is_asm_opnd(son(e), ext)) ||
	(asm_var(e) && is_asm_var(son(e), ext)))
      return;
  }
  if (name(e) == seq_tag) {
    exp t = son(son(e));
    for (;;) {
      check_asm_seq(t, ext);
      if (last(t))
	break;
      t = bro(t);
    }
    check_asm_seq(bro(son(e)), ext);
  }
  else
  if (name(e)!= top_tag)
    error(ERR_INTERNAL, "illegal ~asm");
}

/* Main scan routine */
int scan
(int sto, exp to, exp e, int usereg0)
{
  switch (name(e)) {
    case prof_tag:
	return 0;
    case cond_tag:
    case rep_tag:
    case compound_tag:
    case solve_tag:
    case nof_tag:
    case concatnof_tag:
    case ncopies_tag:
#ifndef TDF_DIAG4
    case diagnose_tag:
#endif
    case caller_tag:
      {
	if (son(e) == NULL) /* empty make_nof */
	  return 0;
	scanargs(1, e, 1);
	return 0;
      }

    case labst_tag:
      {
	IGNORE scan(0, son(e), bro(son(e)), 1);
	return 0;
      }
    case ident_tag:
      {
	IGNORE scan(0, son(e), bro(son(e)), 0);
	IGNORE scan(1, e, son(e), 0);
	return 0;
      }
    case seq_tag:
      {
	scanargs(1, son(e), 1);
	IGNORE scan(0, son(e), bro(son(e)), 1);
	return 0;
      }

    case local_free_tag:
    case long_jump_tag:
    case return_to_label_tag:
      {
	all_assable(sto, to, e);
	return 0;
      }

    case offset_add_tag:
    case offset_subtract_tag:
      {
	if (al2(sh(son(e))) == 1 && al2(sh(bro(son(e))))!= 1)
	  make_bitfield_offset(bro(son(e)), son(e), 0, sh(e));
	if (al2(sh(son(e)))!= 1 && al2(sh(bro(son(e)))) == 1)
	  make_bitfield_offset(son(e), e, 1, sh(e));
	IGNORE all_opnd(sto, to, e, usereg0);
	return 0;
	/* all arguments except possibly one must be operands */
      }

    case offset_mult_tag:
    case alloca_tag:
    case minus_tag:
    case neg_tag:
    case not_tag:
    case offset_pad_tag:
    case offset_negate_tag:
    case offset_max_tag:
    case int_to_bitf_tag:
    case testbit_tag:
    case bitf_to_int_tag:
    case max_tag:
    case min_tag:
    case abs_tag:
      {
	IGNORE all_opnd(sto, to, e, usereg0);
	return 0;
	/* all arguments except possibly one must be operands */
      }
    case subptr_tag:
    case minptr_tag:
    case make_stack_limit_tag:
      {
	IGNORE all_opnd(sto, to, e, 0);
	return 0;
      }
    case set_stack_limit_tag:
      {
	exp lim = find_stlim_var();
	setbro(lim, son(e));
	setson(e, lim);
	setname(e, ass_tag);
	return scan(sto, to, e, usereg0);
      }
    case chvar_tag:
      {
	int ur = usereg0 && name(son(e))!= cont_tag;
	IGNORE all_opnd(sto, to, e, ur);
	return 0;
      }

    case test_tag:
    case absbool_tag:
      {
	if ((name(sh(son(e))) >= shrealhd &&
	      name(sh(son(e))) <= doublehd))
	  IGNORE all_opnd (sto, to, e, 0);/* all arguments must be operands */
	else
	  IGNORE all_opnd(sto, to, e, usereg0);
	/* all arguments except possibly one must be operands */
	return 0;
      }

    case mod_tag:
    case rem2_tag:
    case rem0_tag:
    case div1_tag:
    case div2_tag:
    case div0_tag:
      {
	if (name(sh(e)) == u64hd) {
	  exp * bottom = &bro(son(e));
	  if (name(*bottom) == chvar_tag && shape_size(sh(son(*bottom))) <= 32 &&
		name(son(*bottom))!= val_tag && !is_signed(sh(son(*bottom)))) {
	    if (shape_size(sh(son(*bottom))) == 32) {
	      setbro(son(*bottom), bro(*bottom));
	      *bottom = son(*bottom);
	    }
	    else
	      setsh(son(*bottom), ulongsh);
	  }
	}
	cc1(sto, to, 1, e, notopnd, 1, usereg0);
	return 0;
	/* all arguments except possibly the first must be operands */
      }

    case shl_tag:
    case shr_tag:
    case rotl_tag:
    case rotr_tag:
    case offset_div_tag:
      {
	cc1(sto, to, 1, e, notopnd, 1, usereg0);
	return 0;
	/* all arguments except possibly the first must be operands */
      }

    case offset_div_by_int_tag:
      {
	if (name(sh(bro(son(e))))!= slonghd &&  name(sh(bro(son(e))))!= ulonghd) {
	  exp ch = getexp((name(sh(bro(son(e)))) &1 ? slongsh : ulongsh),
		e, 1, bro(son(e)), NULL, 0, 0, chvar_tag);
	  setbro(bro(son(e)), ch);
	  setbro(son(e), ch);
	}
	cc1(sto, to, 1, e, notopnd, 1, usereg0);
	return 0;
	/* all arguments except possibly the first must be operands */
      }

    case fplus_tag:
    case fminus_tag:
    case fmult_tag:
    case fdiv_tag:
    case fneg_tag:
    case fabs_tag:
    case chfl_tag:
    case float_tag:
    case round_tag:
    case movecont_tag:
      {
	IGNORE all_opnd (sto, to, e, 0);/* all arguments must be operands */
	return 0;
      }
    case ass_tag:
    case assvol_tag:
      {
	exp toc;
	if (name (e) == assvol_tag)/* change assvol to assign */
	  setname(e, ass_tag);
	IGNORE cont_arg(sto, to, e, 0);
	/* special check for references */
	if (!is_assable(bro(son(e)))) {
	  /* second argument must be assignable */
	  cca(sto, to, 0, son(e));
	  toc = contexp(sto, to);
	  IGNORE scan(1, toc, son(toc), 1);
	}
	else
	  IGNORE scan(sto, to, bro(son(e)), 1);
	return 0;
      }
    case apply_tag:
      {
	if (builtinproc(e)) {	/* son must be named global */
	  if (!last(son(e)))
	    IGNORE cc(sto, to, 0, son(e), notopnd, 1, 0);
	  return 0;
	}
        if (!last(son(e)))
	  scan_apply_args(sto, to, 0, son(e));
	indable_son(sto, to, e);
	return 0;
      }
    case apply_general_tag:
      {
	exp cees = bro(bro(son(e)));
	exp p_post = cees;	/* bro(p_post) is postlude */
	while (name(bro(p_post)) == ident_tag && name(son(bro(p_post))) == caller_name_tag)
	  p_post = son(bro(p_post));
	scan(0, p_post, bro(p_post), 1);
	if (son(cees)!= NULL)
	  scan_apply_args(sto, to, 1, cees);
	if (no(bro(son(e)))!= 0)
	  scan_apply_args(sto, to, 1, bro(son(e)));
	indable_son(sto, to, e);
	if ((name(cees) == make_dynamic_callee_tag && name(bro(son(cees)))!= val_tag)
		|| (name(cees) == same_callees_tag && callee_size < 0))
	  has_dy_callees = 1;
	if (name(cees) == same_callees_tag)
	  has_same_callees = 1;
	if (name(cees) == make_dynamic_callee_tag || name(cees) == same_callees_tag)
	  cca_for_cees(sto, to, e);
	return 0;
      }
    case tail_call_tag:
      {
	exp cees = bro(son(e));
	has_tail_call = 1;
	if (son(cees)!= NULL)
	  IGNORE cc(sto, to, 1, cees, no_alloca, 1, 0);
	indable_son(sto, to, e);
	if (name(cees) == make_dynamic_callee_tag && name(bro(son(cees)))!= val_tag)
	  has_dy_callees = 1;
	if (name(cees) == same_callees_tag)
	  has_same_callees = 1;
	if (name(cees) == make_dynamic_callee_tag)
	  cca_for_cees(sto, to, e);
	return 0;
      }
    case goto_lv_tag:
      {
	indable_son(sto, to, e);
	return 0;
      }
    case res_tag:
    case untidy_return_tag:
      {
	if ((name(sh(son(e))) == cpdhd) &&
	 (name(son(e))!= cont_tag ||
	      name(son(son(e)))!= name_tag ||
	      !isvar(son(son(son(e)))))) { /* gcc compatibility */
	  exp ec;
	  cca(sto, to, 1, e);
	  ec = contexp(sto, to);
	  IGNORE scan(1, ec, son(ec), 0);
	  return 0;
	}
	else  {
	  IGNORE(scan(sto, to, son(e), 1));
	  return 0;
	}
      }
    case case_tag:
      {
	exp toc;
	if (name(son(e))!= name_tag &&
	(name(son(e))!= cont_tag ||
	      name(son(son(e)))!= name_tag)) {
	  cca(sto, to, 1, e);
	  toc = contexp(sto, to);
	  IGNORE scan(1, toc, son(toc), 0);
	}
	else
	  IGNORE scan(sto, to, son(e), 0);
	return 0;
      }
    case plus_tag:
      {
	IGNORE cc(sto, to, 1, e, plusdo, 1, usereg0);
	return 0;
      }
    case addptr_tag:
      {
	exp f = father(e);
	exp new_r = getexp(sh(e), bro(e), (int)(last(e)),
                             e, NULL, 0,
	    0, reff_tag);
	exp * ref = refto(f, e);
	setlast(e);
	bro(e) = new_r;
	*ref = new_r;
	ap_argsc(sto, to, new_r);
	return 0;
      }
    case mult_tag:
      {
	if (shape_size(sh(e)) == 64 && optop(e)) {
	  exp * arglist = &son(e);
	  for (;;) {
	    if (name(*arglist) == chvar_tag && shape_size(sh(son(*arglist))) <= 32 &&
		(is_signed(sh(e)) || !is_signed(sh(son(*arglist))))) {
	      if (shape_size(sh(son(*arglist))) == 32) {
		setbro(son(*arglist), bro(*arglist));
		if (last(*arglist))
		  setlast(son(*arglist));
		else
		  clearlast(son(*arglist));
		*arglist = son(*arglist);
	      }
	      else
		setsh(son(*arglist), (is_signed(sh(e))? slongsh : ulongsh));
	    }
	    if (last(*arglist))
	      break;
	    arglist = &bro(*arglist);
	  }
	}
	IGNORE cc(sto, to, 1, e, multdo, 1, usereg0);
	return 0;
      }
    case and_tag:
      {
	IGNORE cc(sto, to, 1, e, anddo, 1, usereg0);
	return 0;
      }
    case or_tag:
    case xor_tag:
      {
	IGNORE cc(sto, to, 1, e, notado, 1, usereg0);
	return 0;
      }
    case cont_tag:
    case contvol_tag:
      {
	if (name(e) == contvol_tag)
	  setname(e, cont_tag);
	return cont_arg(sto, to, e, usereg0);
      }
    case field_tag:
      {
	if (!is_o(name(son(e))) || name(e) == cont_tag) {
	  exp temp;
	  cca(sto, to, 1, e);
	  temp = contexp(sto, to);
	  return scan(1, temp, son(temp), usereg0);
	}
	else
	  return scan(sto, to, son(e), usereg0);
      }
    case reff_tag:
      {
	if (name(son(e)) == addptr_tag) {
	  ap_argsc(sto, to, e);
	  return 0;
	}

	ccp(sto, to, 1, e);
	return 0;
      }
    case proc_tag:
    case general_proc_tag:
      {
	IGNORE scan(1, e, son(e), 1);
	return 0;
      }
    case asm_tag:
      {
	if (props(e)!= 0)
	  error(ERR_INTERNAL, "~asm not in ~asm_sequence");
	check_asm_seq(son(e), 0);
	proc_has_asm = 1;
	return 0;
      }

    case name_tag:
      if (!is_opnd(e)) {
	return 0;
      }

	/* DELIBERATE FALL THROUGH */
    default:
      return usereg0;
  }
}
