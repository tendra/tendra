/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>

#include <shared/error.h>

#include <local/ash.h>

#include <tdf/tag.h>

#include <construct/installtypes.h>
#include <construct/aldefs.h>
#include <construct/dec.h>
#include <construct/ash.h>

#include <main/print.h>

#include "codegen.h"
#include "geninst.h"
#include "make_code.h"
#include "tempdecs.h"
#include "regable.h"
#include "code_here.h"

/*
 * regofval returns R_NO_REG unlesss e is a name tag which is obtaining
 * something which is inreg
 */
int regofval(exp e)
{
  exp dc = son(e);

  /*
   *        _________
   * e--->  | name  |
   *        ~~~~|~~~~
   *        ____|____
   * dc-->  | ident |
   *        ~~~~~~~~~
   */
  if (name(e) == name_tag)
  {
    assert(name(dc) == ident_tag);
    if (props(dc) & defer_bit)
    {
      return regofval(son(dc));
    }
    if (props(dc) & inreg_bits)
    {
      /*
       * HACK: The no(dc) is a register number 0-31 i.e positive
       * so by negating it if it isvar we can pass back more info
       */
      return (isvar(dc)) ? (-no(dc)) : (no(dc));
    }
    return R_NO_REG;
  }
  else
  {
    return R_NO_REG;
  }
}

/*
 * fregofval same as regofval, but used for float regs
 */
static int
fregofval(exp e)
{
  exp dc = son(e);

  if (name(e) == name_tag)
  {
    /*
     *        _________
     * e--->  | name  |
     *        ~~~~|~~~~
     *        ____|____
     * dc-->  | ident |
     *        ~~~~|~~~~
     */
    assert(name(dc) == ident_tag);

    if ((props(dc) & infreg_bits) != 0)
    {
      return no(dc);
    }
    return R_NO_REG;
  }
  else
  {
    return R_NO_REG;
  }
}

/*
 * is_reg_operand returns R_NO_REG unless the exp e is in a register already.
 * This can be due to the fact that it is an ident in a register, or that
 * it has been tracked in the register tracking mechanism.
 */
static int is_reg_operand(exp e)
{
  int x = regofval(e);  

  if (x >= 0 && x < R_NO_REG)
  {
    /*
	 * This is the case where we are getting the contents of an ident
	 * which is not a variable, and lives in a register.
	 */

    /*
     *        _________
     * e--->  | name  |
     *        ~~~~|~~~~
     *        ____|____
     *        | ident |  isvar = 0
     *        ~~~~|~~~~  inreg
     */
    return x;
  }
  
  if (name(e) == cont_tag)
  {
    x = regofval(son(e));
    if (x < 0)
    {
	/*
	 * This is the case when we have the contents of a variable which is inreg.
	 * Thus no one could have taken the address of this ident, since that
	 * would mean it was not inreg. Therefore we have a variable living
	 * in a register.
	 */

      /*
       *        _________
       * e--->  | cont  |
       *        ~~~~|~~~~
       *        ____|____
       *        | name  |
       *        ~~~~|~~~~
       *        ____|____
       *        | ident |  isvar = 1
       *        ~~~~|~~~~  inreg
       */
      return -x;
    }
  }
  return ans_reg(iskept_reg(e));
}

/*
 * make_code_here
 * Calls make_code and tie up any internal exit labels
 */
static int make_code_here(exp e, space sp, where dest)
{
  makeans mka;

  mka = make_code(e, sp, dest, 0);
  if (mka.lab != 0)
  {
    clear_all();
    set_label(mka.lab);
  }
  return mka.regmove;
}

/*
 * reg_operand evaluates the exp e into a register, and returns that register.
 * is_reg_operand is used in order to activate the register tracking scheme,
 * or to see if the exp is something simple.
 */
int reg_operand(exp e, space sp)
{
  int reg;

  reg = is_reg_operand(e);

  if (IS_R_NO_REG(reg))
  {
    /*
	 * We allow make_code_here to evaluate e into a register of its choice
	 * by setting someregalt.
	 */
    ans aa;
    where w;

    if(RETURNS_R_RESULT(e))
    {
      reg = R_RESULT;
      setregalt(aa,R_RESULT);
    }
    else
    {
      reg = -1;
      setsomeregalt(aa, &reg);
    }

    w.answhere = aa;
    w.ashwhere = ashof(sh(e));
    make_code_here(e, sp, w);
    keepreg(e, reg);
    return reg;
  }
  else
  {
    /* The exp e was found in a register by is_reg_operand */
    assert(IS_FIXREG(reg));
    return reg;
  }
}

/* like reg_operand, but to specified reg */
void reg_operand_here(exp e, space sp, int this_reg)
{
  int reg;

  assert(!IS_R_NO_REG(this_reg));
  assert(IS_FIXREG(this_reg));

  /* First check to see if e is lying around in exact reg we want */
  reg = ans_reg(iskept_inreg(e, this_reg));

  if (reg == this_reg)
  {
    return;
  }			/* it's there, nothing to do */


  /* Now check to see if e is lying around in any reg */

  reg = is_reg_operand(e);

  if (IS_R_NO_REG(reg))
  {
    /* not found, evaluate to this_reg */
    where w;

    w.ashwhere = ashof(sh(e));
    setregalt(w.answhere, this_reg);
    make_code_here(e, sp, w);
  }
  else
  {
    /* e was found in a reg, move to this_reg if needed */
    assert(IS_FIXREG(reg));

    if (reg != this_reg)
    {
      mov_rr_ins(reg, this_reg);
    }
  }
  keepreg(e, this_reg);
}


int freg_operand(exp e, space sp, int reg)
{
  int x = fregofval(e);
  ans aa;
  where w;
  freg fr;

  w.ashwhere = ashof(sh(e));
  fr.dble = (w.ashwhere.ashsize == 64) ? 1 : 0;

  if (x >= 0 && x < R_NO_REG)
  {
    return x;
  }

  if (name(e) == cont_tag)
  {
    x = fregofval(son(e));
    if (x < R_NO_REG)
    {
      return x;
    }
  }
  else if (RETURNS_FR_RESULT(e))
  {
    fr.fr = FR_RESULT;
    setfregalt(aa, fr);
    asm_comment("freg_operand: call of float point result proc");
    w.answhere = aa;
    /* w.ashwhere already correctly set up above */
    make_code(e, sp, w, 0);
    return FR_RESULT;
  }

  aa = iskept(e);

  if (aa.discrim == infreg)/* lets move this out */
  {
    freg f;
    f = fregalt(aa);

    if (f.dble == fr.dble)
    {
      return f.fr;
    }
  }

  /* +++ use somefreg */
  fr.fr = reg;
  setfregalt(aa, fr);
  w.answhere = aa;
  make_code_here(e, sp, w);
  keepexp(e, aa);
  return reg;
}

/*
 * The procedure code_here calls make_code and ensures that
 * any internal exit labels are tied up after the call.
 *
 * Optimises the case where the value of 'e' is in a register.
 */
int code_here(exp e, space sp, where dest)
{
  int reg;

  reg = is_reg_operand(e);

  if (IS_R_NO_REG(reg))
  {
    return make_code_here(e, sp, dest);
  }
  else
  {
    /* +++ do in make_code maybe */
    /* +++ for reals as well */ 
    /* e was found easily in a reg */
    ans aa;

    assert(IS_FIXREG(reg));
    assert(ashof(sh(e)).ashsize<=32);

    setregalt(aa, reg);
    move(aa, dest, guardreg(reg, sp).fixed, 1);

    return reg;
  }
}
