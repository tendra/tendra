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


/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/codehere.c,v 1.2 1998/03/11 11:03:52 pwe Exp $
--------------------------------------------------------------------------
$Log: codehere.c,v $
 * Revision 1.2  1998/03/11  11:03:52  pwe
 * DWARF optimisation info
 *
 * Revision 1.1.1.1  1998/01/17  15:55:53  release
 * First version to be checked into rolling release.
 *
 * Revision 1.6  1997/08/23  13:53:36  pwe
 * initial ANDF-DE
 *
 * Revision 1.5  1997/04/17  11:59:31  pwe
 * dwarf2 support
 *
 * Revision 1.4  1995/09/29  09:42:04  john
 * Fix to apply
 *
 * Revision 1.3  1995/07/18  09:38:23  john
 * Implemented return_to_label
 *
 * Revision 1.2  1995/05/26  12:56:29  john
 * Reformatting
 *
 * Revision 1.1.1.1  1995/03/13  10:18:28  john
 * Entered into CVS
 *
 * Revision 1.3  1994/07/07  16:11:33  djch
 * Jul94 tape
 *
 * Revision 1.3  1994/07/07  16:11:33  djch
 * Jul94 tape
 *
 * Revision 1.2  1994/05/25  14:20:10  djch
 * added assert for extra sanity
 *
 * Revision 1.1  1994/05/03  14:49:29  djch
 * Initial revision
 *
 * Revision 1.4  93/08/27  11:22:06  11:22:06  ra (Robert Andrews)
 * Got rid of sp argument to is_reg_operand, a couple of lint-like
 * changes.
 * 
 * Revision 1.3  93/08/13  14:35:08  14:35:08  ra (Robert Andrews)
 * Reformatted.
 * 
 * Revision 1.2  93/06/29  14:22:26  14:22:26  ra (Robert Andrews)
 * Made an integer cast explicit.
 * 
 * Revision 1.1  93/06/24  14:57:59  14:57:59  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#define SPARCTRANS_CODE
#include "config.h"
#include "common_types.h"
#include "myassert.h"
#include "addrtypes.h"
#include "proctypes.h"
#include "labels.h"
#include "expmacs.h"
#include "tags.h"
#include "makecode.h"
#include "exp.h"
#include "bitsmacs.h"
#include "locate.h"
#include "regexps.h"
#include "regmacs.h"
#include "inst_fmt.h"
#include "sparcins.h"
#include "shapemacs.h"
#include "special.h"
#include "regable.h"
#include "guard.h"
#include "move.h"
#include "comment.h"
#include "codehere.h"


/*
  HAS A REGISTER BEEN ALLOCATED FOR A VALUE?
  The expression e is checked to see if it has been allocated into a
  fixed register.  If so the register number is returned, otherwise
  R_NO_REG is returned.
*/

int regofval 
    PROTO_N ( ( e ) )
    PROTO_T ( exp e )
{
  exp dc = son ( e ) ;
  if ( name ( e ) == name_tag && name ( dc ) == ident_tag ) {
    if ( ( props ( dc ) & defer_bit ) != 0 ) {
      return ( regofval ( son ( dc ) ) ) ;
    }
    if ( ( props ( dc ) & inreg_bits ) != 0 ) {
      return ( ( isvar ( dc ) ) ? ( -no ( dc ) ) : ( no ( dc ) ) ) ;
    }
    return ( R_NO_REG ) ;
  } 
  else if ( name ( e ) == val_tag && no ( e ) == 0 ) {
    return ( R_G0 ) ;
  }
  return ( R_NO_REG ) ;
}


/*
  HAS A FLOATING REGISTER BEEN ALLOCATED FOR A VALUE?
  The expression e is checked to see if it has been allocated into a
  floating register.  If so the register number is returned, 
  otherwise R_NO_REG is returned.
*/

int fregofval 
    PROTO_N ( ( e ) )
    PROTO_T ( exp e )
{
  exp dc = son ( e ) ;
  if ( name ( e ) == name_tag && name ( dc ) == ident_tag ) {
    if ( ( props ( dc ) & infreg_bits ) != 0 ) {
      return ( no ( dc ) ) ;
    }
    return ( R_NO_REG ) ;
  }
  return ( R_NO_REG ) ;
}


/*
  AUXILIARY MAKE_CODE ROUTINE
  This routine calls make_code and ties up any internal exit labels.
*/
static int make_code_here 
    PROTO_N ( ( e, sp, dest ) )
    PROTO_T ( exp e X space sp X where dest )
{
  makeans mka ;
  mka = make_code ( e, sp, dest, 0 ) ;
  if ( mka.lab != 0 ) {
    clear_all () ;
    set_label ( mka.lab ) ;
#ifdef NEWDWARF
    START_BB ();
#endif
  }
  return ( mka.regmove ) ;
}


/*
  DOES AN EXPRESSION FIT INTO A REGISTER?
  If e easily fits into a unique fixed register then this register 
  number is returned.  Otherwise R_NO_REG is returned.
*/
static int is_reg_operand 
    PROTO_N ( ( e ) )
    PROTO_T ( exp e )
{
  ans aa ;
  int x = regofval ( e ) ;
  if ( x >= 0 && x < R_NO_REG ) return ( x ) ;
  if ( name ( e ) == cont_tag ) {
    x = regofval ( son ( e ) ) ;
    if ( x < 0 ) return ( -x ) ;
  }
  aa = iskept ( e ) ;
  if ( discrim ( aa ) == inreg && regalt ( aa ) != 0 ) {
    return ( regalt ( aa ) ) ;
  }
  if ( discrim ( aa ) == notinreg ) {
    instore is ;
    is = insalt ( aa ) ;
    if ( is.adval && is.b.offset == 0 ) {
      int r = is.b.base ;
      return ( r ) ;
    }
  }
  return ( R_NO_REG ) ;
}


/*
  CODE AN EXPRESSION INTO A REGISTER
  The expression e is encoded into a fixed register and the register
  number is returned.
*/

int reg_operand 
    PROTO_N ( ( e, sp ) )
    PROTO_T ( exp e X space sp )
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
    return ( reg ) ;
  } 
  else {
    /* e was found easily in a register */
    assert ( IS_FIXREG ( reg ) ) ;
    return ( reg ) ;
  }
}


/*
  CODE AN EXPRESSION INTO A GIVEN REGISTER
  The expression e is encoded into the given fixed register.
*/
void reg_operand_here 
    PROTO_N ( ( e, sp, this_reg ) )
    PROTO_T ( exp e X space sp X int this_reg )
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

int freg_operand 
    PROTO_N ( ( e, sp, reg ) )
    PROTO_T ( exp e X space sp X int reg )
{
  ans aa ;
  where w ;
  freg fr ;
  int x = fregofval ( e ) ;
  if ( x >= 0 && x < R_NO_REG ) return ( x ) ;
  w.ashwhere = ashof ( sh ( e ) ) ;
  fr.dble = ( bool ) ( ( w.ashwhere.ashsize == 64 ) ? 1 : 0 ) ;
  if ( name ( e ) == cont_tag ) {
    x = fregofval ( son ( e ) ) ;
    if ( x < R_NO_REG ) return ( x ) ;
  } 
  else if ( name ( e ) == apply_tag || name(e) == apply_general_tag) {
    fr.fr = 0 ;
    setfregalt ( aa, fr ) ;
    w.answhere = aa ;
    /* w.ashwhere already correctly set up above */
    make_code ( e, sp, w, 0 ) ;
    /* floating point procedures give their result in %f0 */
    return ( 0 ) ;
  }
  aa = iskept ( e ) ;
  if ( discrim ( aa ) == infreg ) {
    /* e already evaluated in fl reg */
    return ( regalt ( aa ) ) /* cheat */ ;
  }
  fr.fr = reg ;
  setfregalt ( aa, fr ) ;
  w.answhere = aa ;
  ( void ) make_code_here ( e, sp, w ) ;
  keepexp ( e, aa ) ;
  return ( reg ) ;
}


/*
  ENCODE AN EXPRESSION
  The expression e is encoded into dest using make_code, and any
  internal exit labels are tied up.  However in the case when e is
  in a fixed register this is optimised to a move.
*/

int code_here 
    PROTO_N ( ( e, sp, dest ) )
    PROTO_T ( exp e X space sp X where dest )
{
  int reg = is_reg_operand ( e ) ;
  if ( reg == R_NO_REG || reg == R_G0 ) {
    return ( make_code_here ( e, sp, dest ) ) ;
  } 
  else {
    /* e was found easily in a register */
    ans aa ;
    assert ( IS_FIXREG ( reg ) ) ;
    assert ( ashof ( sh ( e ) ).ashsize <= 32 ) ;
    setregalt ( aa, reg ) ;
    ( void ) move ( aa, dest, guardreg ( reg, sp ).fixed, 1 ) ;
#ifdef NEWDIAGS
    if (dgf(e))
      diag_arg (e, sp, dest);
#endif
    return ( reg ) ;
  }
}
