/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************

                            codec.c

   codec produces code for operations which produce values.
   e is the operation and dest is where the result is to be put.

**********************************************************************/

#include <shared/check.h>

#include <stddef.h>

#include <reader/basicread.h>
#include <reader/readglob.h>
#include <reader/externs.h>

#include <construct/exp.h>
#include <construct/tags.h>
#include <construct/shapemacs.h>
#include <construct/flags.h>
#include <construct/install_fns.h>
#include <construct/flpt.h>

#include "exptypes.h"
#include "expmacs.h"
#include "instr386.h"
#include "operand.h"
#include "coder.h"
#include "codermacs.h"
#include "instr.h"
#include "messages_8.h"
#include "reg_record.h"
#include "instrmacs.h"

#include "codec.h"


/* PROCEDURES */

/* returns true if is_o(e) but not a possible 80386 operand */
int is_crc
(exp e)
{
		/* make sure (is_o && is_crc -> !is_opnd) */
  if (name(e) == name_tag) {
    if (isvar(son(e)))
      return !isglob(son(e)) || PIC_code;
    /* else */
      return son(son(e)) == nilexp ||
	(isglob(son(e)) && PIC_code && name(sh(son(e))) == prokhd &&
			!(brog(son(e)) -> dec_u.dec_val.extnamed)) ||
	(name(son(son(e))) == ident_tag && isparam(son(son(e))));
  }

  if (name(e) == reff_tag || name(e) == field_tag)
    return 1;

  if (name(e)!= cont_tag)
    return 0;

  if (name(son(e)) == cont_tag)
    return 1;

  return name(son(e)) == reff_tag &&
	  name(son(son(e))) == cont_tag;
}

/* op is a procedure for encoding a unary
   operation. If a is a possible 80386
   operand, uop applies this operator to
   produce the code for a, leaving the
   result in dest. sha gives the shape for
   the operation. If a is not a possible
   80386 operand, then uop produces code
   for a to put it into eax (reg0) and
   then applies op to eax, putting the
   result into dest. */
void uop
(void(*op)(shape, where, where), shape sha, exp a, where dest, ash stack)
{
  if (!is_o(name(a)) || is_crc(a)) {
    where qw;
    if (!inmem(dest))
      qw.where_exp = copyexp(dest.where_exp);
    else
      qw.where_exp = copyexp(reg0.where_exp);
    sh(qw.where_exp) = sha;
    qw.where_off = 0;
    coder(qw, stack, a);
   (*op)(sha, qw, dest);
    retcell(qw.where_exp);
    cond1_set = 0;
    return;
  };
 (*op)(sha, mw(a, 0), dest);
  return;
}

static int no_reg_needed
(exp e)
{
  if (name(e) == val_tag)
    return 1;
  if (name(e) == cont_tag &&
	name(son(e)) == name_tag &&
	isvar(son(son(e))) &&
	ptno(son(son(e)))!= reg_pl)
    return 1;
  if (name(e) == name_tag &&
	!isvar(son(e)) &&
	ptno(son(e))!= reg_pl)
    return 1;
  return 0;
}

/* op is a procedure for encoding a binary
   operation. Not more than one of a and b
   will not be a possible 80386 operand.
   This has been ensured by scan2. If a
   and b are both possible 80386 operands,
   bop applies this operator to produce
   the code, leaving the result in dest.
   sha gives the shape for the operation.
   If either a or b is not a possible
   80386 operand, then bop produces code
   for it to put it into eax (reg0) and
   then applies op to eax and the other
   operand, putting the result into dest.
*/
void bop
(void(*op)(shape, where, where, where), shape sha, exp a, exp b, where dest, ash stack)
{
  where qw;

  if (!is_o(name(a)) || is_crc(a)) {
    if (!inmem(dest) && no_reg_needed(b))
      qw.where_exp = copyexp(dest.where_exp);
    else
      qw.where_exp = copyexp(reg0.where_exp);
    sh(qw.where_exp) = sha;
    qw.where_off = 0;
    coder(qw, stack, a);
   (*op)(sha, qw, mw(b, 0), dest);
    retcell(qw.where_exp);
    cond1_set = 0;
    return;
  };
  if (!is_o(name(b)) || is_crc(b)) {
    if (!inmem(dest) && no_reg_needed(a))
      qw.where_exp = copyexp(dest.where_exp);
    else
      qw.where_exp = copyexp(reg0.where_exp);
    sh(qw.where_exp) = sha;
    qw.where_off = 0;
    coder(qw, stack, b);
   (*op)(sha, mw(a, 0), qw, dest);
    retcell(qw.where_exp);
    cond1_set = 0;
    return;
  };

 (*op)(sha, mw(a, 0), mw(b, 0), dest);
  return;
}

/* process the binary logical operation
   exp. op is the compiling procedure for
   the operation. It is commutative and
   associative, the operation takes a
   variable number of arguments. It is
   therefore necessary to avoid the
   mistake of assigning to the destination
   (dest) inappropriately if its value is
   used in the expression. At most one of
   the arguments will not be a possible
   80386 operand. If there is such an
   argument, logop precomputes it, putting
   the value into reg0. */
static void logop
(void(*op)(shape, where, where, where), exp e, where dest, ash stack)
{
  exp arg1 = son(e);
  exp arg2 = bro(arg1);
  shape sha = sh(e);
  exp t, u;
  where qw;

  if (last(arg1)) {
    coder(dest, stack, arg1);
    return;
  };

  if (last (arg2)) {		/* just two arguments. */
    bop(op, sha, arg1, arg2, dest, stack);
    return;
  };
  /* need to take care about overlap between dest and args or to avoid
     extra push. So use reg0. */
  qw.where_exp = copyexp(reg0.where_exp);
  sh(qw.where_exp) = sha;
  qw.where_off = 0;
  t = arg1;
  /* now look for an argument which is not a possible 80386 operand */
  while (1) {
    if (!is_o(name(t)) || is_crc(t))
      break;
    if (last(t)) {
      t = nilexp;
      break;
    };
    t = bro(t);
  };

  if (t == nilexp) {		/* all arguments are possible 80386
				   operands */
   (*op)(sha, mw(arg1, 0), mw(arg2, 0), qw);
    t = bro(arg2);
    while (!last(t)) {
      (*op) (sha, mw (t, 0), qw, qw);/* encode operations in turn */
      t = bro(t);
    };
    (*op) (sha, mw (t, 0), qw, dest);/* encode final operation */
    retcell(qw.where_exp);
    cond1_set = 0;
    return;
  };

  coder (qw, stack, t);		/* encode the single argument which is not
				   a possible 80386 operend */
  u = arg1;
  /* now encode the remaining operations */
  while (1) {
    if (t != u) {
      if (last(u) || (bro(u) == t && last(bro(u))))
	(*op)(sha, mw(u, 0), qw, dest);
      else
	(*op)(sha, mw(u, 0), qw, qw);
    };
    if (last(u))
      break;
    u = bro(u);
  };
  retcell(qw.where_exp);
  cond1_set = 0;
  return;
}

/* process the multiply operation
   exp. op is the compiling procedure for
   the operation. It is commutative and
   associative, the operation takes a
   variable number of arguments. It is
   therefore necessary to avoid the
   mistake of assigning to the destination
   (dest) inappropriately if its value is
   used in the expression. At most one of
   the arguments will not be a possible
   80386 operand. If there is such an
   argument, it is precomputed, putting
   the value into reg0. */
static void multop
(void(*op)(shape, where, where, where), exp e, where dest, ash stack)
{
  exp arg1 = son(e);
  exp arg2 = bro(arg1);
  exp t, u;
  where qw;

  if (last(arg1)) {
    coder(dest, stack, arg1);
    return;
  };

  if (last (arg2)) {		/* just two arguments. */
    bop(op, sh(e), arg1, arg2, dest, stack);
    return;
  };
  /* need to take care about overlap between dest and args or to avoid
     extra push. So use reg0. */
  qw.where_exp = copyexp(reg0.where_exp);
  sh(qw.where_exp) = sh(e);
  qw.where_off = 0;
  t = arg1;
  /* now look for an argument which is not a possible 80386 operand */
  while (1) {
    if (!is_o(name(t)) || is_crc(t))
      break;
    if (last(t)) {
      t = nilexp;
      break;
    };
    t = bro(t);
  };

  if (t == nilexp) {		/* all arguments are possible 80386
				   operands */
   (*op)(sh(e), mw(arg1, 0), mw(arg2, 0), qw);
    t = bro(arg2);
    while (!last(t)) {
      (*op) (sh (e), mw (t, 0), qw, qw);/* encode operations in turn */
      t = bro(t);
    };
    (*op) (sh (e), mw (t, 0), qw, dest);/* encode final operation */
    retcell(qw.where_exp);
    cond1_set = 0;
    return;
  };

  coder (qw, stack, t);		/* encode the single argument which is not
				   a possible 80386 operend */
  u = arg1;
  /* now encode the remaining operations */
  while (1) {
    if (t != u) {
      if (last(u) || (bro(u) == t && last(bro(u))))
	(*op)(sh(e), mw(u, 0), qw, dest);
      else
	(*op)(sh(e), mw(u, 0), qw, qw);
    };
    if (last(u))
      break;
    u = bro(u);
  };
  retcell(qw.where_exp);
  cond1_set = 0;
  return;
}

/* if a is a negation form b-son(a)
   otherwise b+a in dest */
static void addsub
(shape sha, where a, where b, where dest, exp e)
{
  UNUSED(e);
  if (name(a.where_exp) == neg_tag)
    sub(sha, mw(son(a.where_exp), 0), b, dest);
  else
    add(sha, a, b, dest);
  return;
}



/***********************************************************************
   codec outputs the code which evaulates e and puts the result into
   dest.
 ***********************************************************************/


/* encode e, putting the result into dest.
   stack is the current stack level */
void codec
(where dest, ash stack, exp e)
{
  switch (name(e)) {
    case plus_tag:
      {				/* at most one of the arguments will not
				   be a possible 80386 operand */
	exp arg1 = son(e);
	exp arg2 = bro(arg1);
	exp t, u, v;
	where qw;
	exp old_overflow_e = overflow_e;

	if (last (arg1)) {	/* there is only one argument */
	  coder(dest, stack, arg1);
	  return;
	};

	if (!optop(e))
          overflow_e = e;

	if (last(arg2) && is_o(name(arg1)) && !is_crc(arg1) &&
	   ((is_o(name(arg2)) && !is_crc(arg2)) ||
	     (name(arg2) == neg_tag &&
	       !is_crc(son(arg2)) &&
	       is_o(name(son(arg2)))))) {
	  /* just two arguments. */
	  addsub(sh(e), mw(arg2, 0), mw(arg1, 0), dest, e);
          overflow_e = old_overflow_e;
	  return;
	};
	/* need to take care about overlap between dest and args or to
	   avoid extra push. So use reg0. */
	t = arg1;
	qw.where_exp = copyexp(reg0.where_exp);
	sh(qw.where_exp) = sh(e);
	qw.where_off = 0;

	/* now look for argument which is not a possible 80386 operand */
	while (1) {
	  if ((!is_o(name(t)) || is_crc(t)) &&
	     (name(t)!= neg_tag || !is_o(name(son(t))) ||
	       is_crc(son(t))))
	    break;
	  if (last(t)) {
	    t = nilexp;
	    break;
	  };
	  t = bro(t);
	};

	if (t == nilexp && name(arg1) == neg_tag &&
	    name(arg2) == neg_tag)
	  t = arg1;

	if (t == nilexp) {	/* all arguments are possible 80386
				   operands */
	  t = bro(arg2);
	  if (name(arg1) == neg_tag)
	    addsub(sh(e), mw(arg1, 0), mw(arg2, 0),
		(t == e)? dest : qw, e);
	  else
	    addsub(sh(e), mw(arg2, 0), mw(arg1, 0),
		(t == e)? dest : qw, e);
	  if (t == e)
           {
             overflow_e = old_overflow_e;
	     return;
           };
	  while (!last(t)) {
	    u = bro(t);
	    addsub(sh(e), mw(t, 0), qw, qw, e);
	    t = u;
	  };
	  addsub(sh(e), mw(t, 0), qw, dest, e);
          overflow_e = old_overflow_e;
	  return;
	};

	coder (qw, stack, t);	/* encode the argument which is not a
				   possible 80386 operand */
	u = arg1;
	/* now encode the remaining operations */
	while (1) {
	  v = bro(u);
	  if (t != u) {
	    if (last(u) || (v == t && last(v)))
	      addsub(sh(e), mw(u, 0), qw, dest, e);
	    else
	      addsub(sh(e), mw(u, 0), qw, qw, e);
	  };
	  if (last(u))
	    break;
	  u = v;
	};
	retcell(qw.where_exp);
        cond1_set = 0;
        overflow_e = old_overflow_e;
	return;
      };
    case addptr_tag: {		/* use index operation */
	mova(mw(e, 0), dest);
	return;
      };
    case chvar_tag: {
	exp a = son(e);
	exp old_overflow_e = overflow_e;
        if (!optop(e))
          overflow_e = e;
	if (!is_o(name(a)) || is_crc(a)) {
				/* argument is not a possible 80386
				   operand, so evaluate it in reg0 */
	  if (inmem(dest) ||
		(shape_size(sh(a)) == 8 && bad_from_reg(dest)) ||
		shape_size(sh(a)) == 64) {
	    where qw;
	    qw.where_exp = copyexp(reg0.where_exp);
	    sh(qw.where_exp) = sh(a);
	    qw.where_off = 0;
	    coder(qw, stack, a);
	    change_var_refactor(sh(e), qw, dest);
	    overflow_e = old_overflow_e;
	    retcell(qw.where_exp);
            cond1_set = 0;
	    return;
	  };
	  coder(dest, stack, a);
	  if (name(sh(e)) > name(sh(a)))
	    change_var_sh(sh(e), sh(a), dest, dest);
	  overflow_e = old_overflow_e;
	  return;
	};
	change_var_refactor(sh(e), mw(a, 0), dest);
	overflow_e = old_overflow_e;
	return;
      };
    case minus_tag:
      {
	exp old_overflow_e = overflow_e;
        if (!optop(e))
          overflow_e = e;
	bop(sub, sh(e), bro(son(e)), son(e), dest, stack);
	overflow_e = old_overflow_e;
	return;
      };
    case subptr_tag:
    case minptr_tag:
    case make_stack_limit_tag:
      {
	bop(sub, sh(e), bro(son(e)), son(e), dest, stack);
	return;
      };
    case mult_tag:
      {
        if (!optop(e))
          {
	    exp old_overflow_e = overflow_e;
            overflow_e = e;
	    multop(multiply, e, dest, stack);
            overflow_e = old_overflow_e;
          }
        else
	  multop(mult, e, dest, stack);
	return;
      };
    case div2_tag:
      {
	exp old_overflow_e = overflow_e;
        if (errhandle(e))
          overflow_e = e;
	bop(div2, sh(e), bro(son(e)), son(e), dest, stack);
	overflow_e = old_overflow_e;
	return;
      };
    case div1_tag:
      {
	exp old_overflow_e = overflow_e;
        if (errhandle(e))
          overflow_e = e;
	bop(div1, sh(e), bro(son(e)), son(e), dest, stack);
	overflow_e = old_overflow_e;
	return;
      };
    case div0_tag:
      {
	exp old_overflow_e = overflow_e;
        if (errhandle(e))
          overflow_e = e;
	bop(div0, sh(e), bro(son(e)), son(e), dest, stack);
	overflow_e = old_overflow_e;
	return;
      };
    case neg_tag:
      {
	exp old_overflow_e = overflow_e;
        if (!optop(e))
          overflow_e = e;
	uop(negate, sh(e), son(e), dest, stack);
	overflow_e = old_overflow_e;
	return;
      };
    case shl_tag:
      {
	exp old_overflow_e = overflow_e;
	overflow_e = e;
        if (!optop(e))
          overflow_e = e;
	bop(shiftl, sh(e), bro(son(e)), son(e), dest, stack);
	overflow_e = old_overflow_e;
	return;
      };
    case shr_tag:
      {
	bop(shiftr, sh(e), bro(son(e)), son(e), dest, stack);
	return;
      };
    case rotl_tag:
      {
	bop(rotatel, sh(e), bro(son(e)), son(e), dest, stack);
	return;
      };
    case rotr_tag:
      {
	bop(rotater, sh(e), bro(son(e)), son(e), dest, stack);
	return;
      };
    case mod_tag:
      {
	exp old_overflow_e = overflow_e;
        if (errhandle(e))
          overflow_e = e;
	bop(mod, sh(e), bro(son(e)), son(e), dest, stack);
	overflow_e = old_overflow_e;
	return;
      };
    case rem2_tag:
      {
	exp old_overflow_e = overflow_e;
        if (errhandle(e))
          overflow_e = e;
	bop(rem2, sh(e), bro(son(e)), son(e), dest, stack);
	overflow_e = old_overflow_e;
	return;
      };
    case rem0_tag:
      {
	exp old_overflow_e = overflow_e;
        if (errhandle(e))
          overflow_e = e;
	bop(rem0, sh(e), bro(son(e)), son(e), dest, stack);
	overflow_e = old_overflow_e;
	return;
      };
    case round_tag:
      {
	shape s = sh(e);
	where d;
	d = dest;
	if (shape_size(s) < 32) {
	  s = slongsh;
	  if (inmem(dest))
	    d = reg0;
	}
        setup_fl_ovfl(e);
	switch (round_number(e)) {
	  case 0:
		uop(frnd0, s, son(e), d, stack);
		break;
	  case 1:
		uop(frnd1, s, son(e), d, stack);
		break;
	  case 2:
		uop(frnd2, s, son(e), d, stack);
		break;
	  case 3:
		uop(frnd3, s, son(e), d, stack);
		break;
	  case 4:
		uop(frnd4, s, son(e), d, stack);
		break;
	};
        test_fl_ovfl(e, d);
	if (name(s)!= name(sh(e))) {
	  exp old_overflow_e = overflow_e;
          if (!optop(e))
            overflow_e = e;
	  change_var_sh(sh(e), s, d, dest);
	  overflow_e = old_overflow_e;
	}
	return;
      };
    case fplus_tag:
      {
        setup_fl_ovfl(e);
	fl_multop(fplus_tag, sh(e), son(e), dest);
        test_fl_ovfl(e, dest);
	return;
      };
    case fmult_tag:
      {
        setup_fl_ovfl(e);
	fl_multop(fmult_tag, sh(e), son(e), dest);
        test_fl_ovfl(e, dest);
	return;
      };
    case fminus_tag:
      {
        setup_fl_ovfl(e);
	fl_binop(fminus_tag, sh(e), mw(bro(son(e)), 0),
	    mw(son(e), 0), dest, bro(son(e)));
        test_fl_ovfl(e, dest);
	return;
      };
    case fdiv_tag:
      {
        setup_fl_ovfl(e);
	fl_binop(fdiv_tag, sh(e), mw(bro(son(e)), 0),
	      mw(son(e), 0), dest, bro(son(e)));
        test_fl_ovfl(e, dest);
	return;
      };
    case fneg_tag: {
        setup_fl_ovfl(e);
	fl_neg(sh(e), mw(son(e), 0), dest);
        test_fl_ovfl(e, dest);
	return;
      };
    case fabs_tag: {
        setup_fl_ovfl(e);
	fl_abs(sh(e), mw(son(e), 0), dest);
        test_fl_ovfl(e, dest);
	return;
      };
    case float_tag: {
        setup_fl_ovfl(e);
	floater(sh(e), mw(son(e), 0), dest);
        test_fl_ovfl(e, dest);
	return;
      };
    case chfl_tag: {
	if (name(sh(e)) < name(sh(son(e))))
	  setup_fl_ovfl(e);
	changefl(sh(e), mw(son(e), 0), dest);
	if (name(sh(e)) < name(sh(son(e))))
	  test_fl_ovfl(e, dest);
	return;
      };
    case and_tag: {
	logop(and, e, dest, stack);
	return;
      };
    case or_tag: {
	logop(or, e, dest, stack);
	return;
      };
    case xor_tag: {
	logop(xor, e, dest, stack);
	return;
      };
    case not_tag: {
	uop(not, sh(e), son(e), dest, stack);
	return;
      };
    case offset_pad_tag:
      if (al2(sh(son(e))) >= al2(sh(e)))
	{
	  if (al2(sh(e))!= 1 || al2(sh(son(e))) == 1)
            coder(dest, stack, son(e));
	  else {
	    coder(reg0, stack, son(e));
	    shiftl(slongsh, mw(zeroe, 3), reg0, dest);
	  }
	}
      else
        {
          int al = al2(sh(e)) /8;
          coder(reg0, stack, son(e));
	  if (al2(sh(son(e))) == 1) {
            add(slongsh, mw(zeroe, al*8 -1), reg0, reg0);
	    shiftr(slongsh, mw(zeroe, 3), reg0, reg0);
	  }
	  else
            add(slongsh, mw(zeroe, al-1), reg0, reg0);
          and(slongsh, mw(zeroe, -al), reg0, dest);
        };
      return;
    case offset_add_tag:
      {
	bop(add, sh(e), son(e), bro(son(e)), dest, stack);
	return;
      };
    case abs_tag:
      {
	exp old_overflow_e = overflow_e;
        if (!optop(e))
          overflow_e = e;
	uop(absop, sh(e), son(e), dest, stack);
	overflow_e = old_overflow_e;
	return;
      };
    case offset_max_tag:
    case max_tag:
      {
	bop(maxop, sh(e), son(e), bro(son(e)), dest, stack);
	return;
      };
    case min_tag:
      {
	bop(minop, sh(e), son(e), bro(son(e)), dest, stack);
	return;
      };
   case offset_subtract_tag:
      {
	bop(sub, sh(e), bro(son(e)), son(e), dest, stack);
	return;
      };
    case offset_mult_tag:
      {
	bop(mult, slongsh, son(e), bro(son(e)), dest, stack);
	return;
      };
    case offset_negate_tag: {
	uop(negate, sh(e), son(e), dest, stack);
	return;
      };
    case offset_div_by_int_tag:
      {
	bop(div0, sh(e), bro(son(e)), son(e), dest, stack);
	return;
      };
    case offset_div_tag:
      {
	if (shape_size(sh(e)) == 32)
	  bop(div0, sh(e), bro(son(e)), son(e), dest, stack);
	else
	if (inmem(dest)) {
	  bop(div0, sh(son(e)), bro(son(e)), son(e), reg0, stack);
	  change_var(sh(e), reg0, dest);
	}
	else {
	  bop(div0, sh(son(e)), bro(son(e)), son(e), dest, stack);
	  change_var(sh(e), dest, dest);
	}
	return;
      };
    case absbool_tag:
      {
	failer(NO_SETCC);
        return;
      };

    case int_to_bitf_tag:
     {
       int mask = lsmask[shape_size(sh(e))];
       move(slongsh, mw(son(e), 0), dest);
       and(slongsh, mw(zeroe, mask), dest, dest);
       return;
     };
    case bitf_to_int_tag:
      coder(reg0, stack, son(e));
      change_var_sh(sh(e), sh(son(e)), reg0, dest);
      return;
    case alloca_tag:
      coder(dest, stack, e);
      return;
    case power_tag:
      failer("integer power not implemented");
      return;
    case cont_tag:
      if (!newcode && name(sh(e)) == bitfhd)
        {
          mem_to_bits(e, sh(e), dest, stack);
          return;
        };
       /* deliberate fall through into default */
    default:
      {
	if (!is_o (name (e))) {	/* e is not a possible 80386 operand,
				   precompute it into reg0 and move to
				   dest */
	  where qw;
	  qw.where_exp = copyexp(reg0.where_exp);
	  sh(qw.where_exp) = sh(e);
	  qw.where_off = 0;
	  coder(qw, stack, e);
	  move(sh(e), qw, dest);
	  retcell(qw.where_exp);
          cond1_set = 0;
	  return;
	};

	if (is_crc(e) && name(e)!= name_tag
		 && name(e)!= reff_tag && name(e)!= field_tag) {
	  exp s = son(e);
	  exp ss = son(s);
	  exp sss = ss;
	  exp * p = & son(e);

	  if (name(s) == reff_tag) {
	    sss = son(ss);
	    p = & son(s);
	  }

	  if (name(sss) == name_tag && ptno(son(sss)) == reg_pl) {
	    move(sh(e), mw(e, 0), dest);
	    return;
	  }
	  else {
	    exp temp = copyexp(reg0.where_exp);
	    exp preserve = *p;
	    coder(reg0, stack, *p);
	    *p = temp;
	    move(sh(e), mw(e, 0), dest);
	    *p = preserve;	/* may still be needed for diags */
	    return;
	  }
	}


	if (name(e) == reff_tag &&
	   (name(son(e)) == name_tag ||
	     (name(son(e)) == cont_tag &&
		name(son(son(e))) == name_tag))) {
	  /* look for case when reff should be done by add */
	  add(slongsh, mw(son(e), 0), mw(zeroe, no(e) / 8), dest);
	  return;
	};

	if ((name(e) == name_tag && isvar(son(e))) ||
	    name(e) == reff_tag ||
           (PIC_code && name(e) == name_tag && isglob(son(e)) &&
               name(sh(son(e))) == prokhd &&
               !brog(son(e)) ->  dec_u.dec_val.extnamed)) {
          if (ptno(son(e))!= nowhere_pl)
	    mova(mw(e, 0), dest);
	  return;
	};

        if (name(e) == clear_tag)
          {
            if ((name(sh(e)) >= shrealhd && name(sh(e)) <= doublehd &&
		!inmem(dest)) || name(dest.where_exp) == apply_tag)
              move(sh(e), fzero, dest);
            return;
          };


	/* other values */

	if (name(e)!= top_tag && name(e)!= prof_tag)
	  move(sh(e), mw(e, 0), dest);
	else
	  top_regsinuse = regsinuse;
	return;
      };
  };
}
