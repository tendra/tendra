/*
    Copyright (c) 1993 Open Software Foundation, Inc.


    All Rights Reserved


    Permission to use, copy, modify, and distribute this software
    and its documentation for any purpose and without fee is hereby
    granted, provided that the above copyright notice appears in all
    copies and that both the copyright notice and this permission
    notice appear in supporting documentation.


    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING
    ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE.


    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
    WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

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



/**********************************************************************
$Author: release $
$Date: 1998/02/04 15:48:41 $
$Revision: 1.2 $
$Log: codehere.c,v $
 * Revision 1.2  1998/02/04  15:48:41  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:56  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  15:59:47  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#include "config.h"
#include "memtdf.h"
#include "codegen.h"
#include "geninst.h"
#include "makecode.h"
#include "myassert.h"
#include "comment.h"
#include "tempdecs.h"
#include "regable.h"
#include "codehere.h"

/* regofval returns R_NO_REG unlesss e is a name tag
   which is obtaining something which is inreg */

int regofval PROTO_N ((e)) PROTO_T (exp e)
{
  exp dc = son(e);

  /*********************************/
  /*        _________              */
  /* e--->  | name  |              */
  /*        ~~~~|~~~~              */
  /*        ____|____              */
  /* dc-->  | ident |              */ 
  /*        ~~~~~~~~~              */
  /*********************************/
  if (name(e) == name_tag)
  {
    ASSERT(name(dc) == ident_tag);
    if (props(dc) & defer_bit)
    {
      return regofval(son(dc));
    }
    if (props(dc) & inreg_bits)
    {
      /* HACK: The no(dc) is a register number 0-31 i.e positive
       * so by negating it if it isvar we can pass back more info
       */
      return ((isvar(dc)) ? (-no(dc)) : (no(dc)));
    }
    return R_NO_REG;
  }
  else
  {
    return R_NO_REG;
  }
}
/* fregofval same as regofval, but used for float regs */
int fregofval PROTO_N ((e)) PROTO_T (exp e)
{
  exp dc = son(e);

  if (name(e) == name_tag)
  {
    /*********************************/
    /*        _________              */
    /* e--->  | name  |              */
    /*        ~~~~|~~~~              */
    /*        ____|____              */
    /* dc-->  | ident |              */ 
    /*        ~~~~|~~~~              */
    /*********************************/
    ASSERT(name(dc) == ident_tag);
    
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

/* is_reg_operand returns R_NO_REG unless the exp e
   is in a register already. This can be due to the 
   fact that it is an ident in a register,
   or that it has been tracked in the register tracking
   mechanism. */
static int is_reg_operand PROTO_N ((e)) PROTO_T (exp e)
{
  int x = regofval(e);  

  if (x >= 0 && x < R_NO_REG)
  {
    /* This is the case where we are getting the
       contents of an ident which is not a variable,
       and lives in a register.*/
    /*********************************/
    /*        _________              */
    /* e--->  | name  |              */
    /*        ~~~~|~~~~              */
    /*        ____|____              */
    /*        | ident |  isvar=0     */ 
    /*        ~~~~|~~~~  inreg       */
    /*********************************/
    return x;
  }
  
  if (name(e) == cont_tag)
  {
    x = regofval(son(e));
    if (x < 0)
    {
      /* This is the case when we have the contents of
	 a variable which is inreg. Thus no one could
	 have taken the address of this ident, since
	 that would mean it was not inreg. Therefore
	 we have a variable living in a register. */
      /*********************************/
      /*        _________              */
      /* e--->  | cont  |              */
      /*        ~~~~|~~~~              */
      /*        ____|____              */
      /*        | name  |              */ 
      /*        ~~~~|~~~~              */
      /*        ____|____              */
      /*        | ident |  isvar=1     */
      /*        ~~~~|~~~~  inreg       */
      /*********************************/
      return (-x);
    }
  }
  return ans_reg(iskept_reg(e));
}


/* 
 * make_code_here
 * Calls make_code and tie up any internal exit labels 
 */
static int make_code_here PROTO_N ((e,sp,dest)) PROTO_T (exp e X space sp X where dest)
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



/* reg_operand evaluates the exp e into a register,
   and returns that register. is_reg_operand is used
   in order to activate the register tracking scheme,
   or to see if the exp is something simple. */
int reg_operand PROTO_N ((e,sp)) PROTO_T (exp e X space sp)
{
  int reg;
  
  reg = is_reg_operand(e);

  if (IS_R_NO_REG(reg))
  {
    /* We allow make_code_here to evaluate e into a register 
       of its choice by setting someregalt. */
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
    /* The exp e was found in a register by 
       is_reg_operand */
    ASSERT(IS_FIXREG(reg));
    return reg;
  }
}


/* like reg_operand, but to specified reg 
 */
void reg_operand_here PROTO_N ((e,sp,this_reg)) PROTO_T (exp e X space sp X int this_reg)
{
  int reg;

  ASSERT(!IS_R_NO_REG(this_reg));
  ASSERT(IS_FIXREG(this_reg));

  /* First check to see if e is lying around 
     in exact reg we want */
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
    ASSERT(IS_FIXREG(reg));

    if (reg != this_reg)
    {
      mov_rr_ins(reg, this_reg);comment(NIL);
    }
  }
  keepreg(e, this_reg);
}


int freg_operand PROTO_N ((e,sp,reg)) PROTO_T (exp e X space sp X int reg)
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
    COMMENT("freg_operand: call of float point result proc");
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
 * Optimises the case where the value of 'e' is in a register.
 */
int code_here PROTO_N ((e,sp,dest)) PROTO_T (exp e X space sp X where dest)
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

    ASSERT(IS_FIXREG(reg));
    ASSERT(ashof(sh(e)).ashsize<=32);

    setregalt(aa, reg);
    move(aa, dest, guardreg(reg, sp).fixed, 1);

    return reg;
  }
}
