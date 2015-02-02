/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>

#include <local/ash.h>

#include <construct/installtypes.h>
#include <construct/ash.h>
#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/shape.h>

#include <main/flags.h>

#include "addrtypes.h"
#include "proctypes.h"
#include "labels.h"
#include "makecode.h"
#include "bitsmacs.h"
#include "locate.h"
#include "regexps.h"
#include "regmacs.h"
#include "inst_fmt.h"
#include "sparcins.h"
#include "special.h"
#include "regable.h"
#include "guard.h"
#include "move.h"
#include "comment.h"
#include "code_here.h"

#include "local_reform.h"


/*
  HAS A REGISTER BEEN ALLOCATED FOR A VALUE?
  The expression e is checked to see if it has been allocated into a
  fixed register.  If so the register number is returned, otherwise
  R_NO_REG is returned.
*/

int 
regofval ( exp e )
{
  exp dc = son ( e ) ;
  if ( name ( e ) == name_tag && name ( dc ) == ident_tag ) {
    if ( ( props ( dc ) & defer_bit ) != 0 ) {
      return regofval ( son ( dc ) ) ;
    }
    if ( ( props ( dc ) & inreg_bits ) != 0 ) {
      return isvar ( dc ) ? ( -no ( dc ) ) : ( no ( dc ) ) ;
    }
    return R_NO_REG;
  } 
  else if ( name ( e ) == val_tag && no ( e ) == 0 ) {
    return R_G0;
  }
  return R_NO_REG;
}


/*
  HAS A FLOATING REGISTER BEEN ALLOCATED FOR A VALUE?
  The expression e is checked to see if it has been allocated into a
  floating register.  If so the register number is returned, 
  otherwise R_NO_REG is returned.
*/

int 
fregofval ( exp e )
{
  exp dc = son ( e ) ;
  if ( name ( e ) == name_tag && name ( dc ) == ident_tag ) {
    if ( ( props ( dc ) & infreg_bits ) != 0 ) {
      return no ( dc ) ;
    }
    return R_NO_REG;
  }
  return R_NO_REG;
}


/*
  AUXILIARY MAKE_CODE ROUTINE
  This routine calls make_code and ties up any internal exit labels.
*/
static int 
make_code_here ( exp e, space sp, where dest )
{
  makeans mka ;
  mka = make_code ( e, sp, dest, 0 ) ;
  if ( mka.lab != 0 ) {
    clear_all () ;
    set_label ( mka.lab ) ;
#ifdef DWARF2
    START_BB ();
#endif
  }
  return mka.regmove;
}


/*
  DOES AN EXPRESSION FIT INTO A REGISTER?
  If e easily fits into a unique fixed register then this register 
  number is returned.  Otherwise R_NO_REG is returned.
*/
static int 
is_reg_operand ( exp e )
{
  ans aa ;
  int x = regofval ( e ) ;
  if ( x >= 0 && x < R_NO_REG ) return x;
  if ( name ( e ) == cont_tag ) {
    x = regofval ( son ( e ) ) ;
    if ( x < 0 ) return -x;
  }
  aa = iskept ( e ) ;
  if ( discrim ( aa ) == inreg && regalt ( aa ) != 0 ) {
    return regalt ( aa ) ;
  }
  if ( discrim ( aa ) == notinreg ) {
    instore is ;
    is = insalt ( aa ) ;
    if ( is.adval && is.b.offset == 0 ) {
      int r = is.b.base ;
      return r;
    }
  }
  return R_NO_REG;
}


/*
  CODE AN EXPRESSION INTO A REGISTER
  The expression e is encoded into a fixed register and the register
  number is returned.
*/

int 
reg_operand ( exp e, space sp )
{
  int reg = is_reg_operand ( e ) ;
  if ( reg == R_NO_REG || reg == R_G0 ) {
    /* allow make_code_here to choose the register */
    ans aa ;
    where w ;
    reg = -1 ;
    setsomeregalt ( aa, &reg ) ;
    w.answhere = aa ;
    w.ashwhere = ashof ( sh ( e ) ) ;
    ( void ) make_code_here ( e, sp, w ) ;
    assert (reg != -1);
    keepreg ( e, reg ) ;
    return reg;
  } 
  else {
    /* e was found easily in a register */
    assert ( IS_FIXREG ( reg ) ) ;
    return reg;
  }
}


/*
  CODE AN EXPRESSION INTO A GIVEN REGISTER
  The expression e is encoded into the given fixed register.
*/
void 
reg_operand_here ( exp e, space sp, int this_reg )
{
  int reg = is_reg_operand ( e ) ;
  if ( reg == R_NO_REG || reg == R_G0 ) {
    /* evaluate e into this_reg directly */
    where w ;
    w.ashwhere = ashof ( sh ( e ) ) ;
    setregalt ( w.answhere, this_reg ) ;
    ( void ) make_code_here ( e, sp, w ) ;
  } 
  else {
    /* e was found easily in a register, so just do a move */
    assert ( IS_FIXREG ( reg ) ) ;
    if ( reg != this_reg ) rr_ins ( i_mov, reg, this_reg ) ;
  }
  if(name(e) != make_lv_tag) keepreg ( e, this_reg ) ;
  return ;
}


/*
  CODE AN EXPRESSION INTO A FLOATING REGISTER
  The expression e is encoded into a floating register and the 
  register number is returned.
*/

int 
freg_operand ( exp e, space sp, int reg )
{
  ans aa ;
  where w ;
  freg fr ;
  int x = fregofval ( e ) ;
  if ( x >= 0 && x < R_NO_REG ) return x;
  w.ashwhere = ashof ( sh ( e ) ) ;
  fr.dble = ( bool ) ( ( w.ashwhere.ashsize == 64 ) ? 1 : 0 ) ;
  if ( name ( e ) == cont_tag ) {
    x = fregofval ( son ( e ) ) ;
    if ( x < R_NO_REG ) return x;
  } 
  else if ( name ( e ) == apply_tag || name(e) == apply_general_tag) {
    fr.fr = 0 ;
    setfregalt ( aa, fr ) ;
    w.answhere = aa ;
    /* w.ashwhere already correctly set up above */
    make_code ( e, sp, w, 0 ) ;
    /* floating point procedures give their result in %f0 */
    return 0;
  }
  aa = iskept ( e ) ;
  if ( discrim ( aa ) == infreg ) {
    /* e already evaluated in fl reg */
    return regalt ( aa ) /* cheat */ ;
  }
  fr.fr = reg ;
  setfregalt ( aa, fr ) ;
  w.answhere = aa ;
  ( void ) make_code_here ( e, sp, w ) ;
  keepexp ( e, aa ) ;
  return reg;
}


/*
  ENCODE AN EXPRESSION
  The expression e is encoded into dest using make_code, and any
  internal exit labels are tied up.  However in the case when e is
  in a fixed register this is optimised to a move.
*/

int 
code_here ( exp e, space sp, where dest )
{
  int reg = is_reg_operand ( e ) ;
  if ( reg == R_NO_REG || reg == R_G0 ) {
    return make_code_here ( e, sp, dest ) ;
  } 
  else {
    /* e was found easily in a register */
    ans aa ;
    assert ( IS_FIXREG ( reg ) ) ;
    assert ( ashof ( sh ( e ) ).ashsize <= 32 ) ;
    setregalt ( aa, reg ) ;
    ( void ) move ( aa, dest, guardreg ( reg, sp ).fixed, 1 ) ;
#ifdef TDF_DIAG4
    if (dgf(e))
      diag_arg (e, sp, dest);
#endif
    return reg;
  }
}
