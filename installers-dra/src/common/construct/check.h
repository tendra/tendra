/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/**********************************************************************
$Author: pwe $
$Date: 1998/02/11 16:56:37 $
$Revision: 1.2 $
$Log: check.h,v $
 * Revision 1.2  1998/02/11  16:56:37  pwe
 * corrections
 *
 * Revision 1.1.1.1  1998/01/17  15:55:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
***********************************************************************/



/*******************************************************************

                              checkdecs.h

  The routine check performs the bottom-up TDF-to-TDF optimising
  transformations. When a new exp is created check is applied to
  see if a recognised situation has arisen. check assumes that
  all components of this new exp have already had check applied to them.
  It returns 1 if it has made a change, 0 if not.


  hold_check holds an exp as the son of a dummy exp and then
  applies check. the need for this operation is explained in
  the overall documentation.

  eq_exp compares two exp for equality of effect.

  dochvar takes the int, i, and delivers the number which results from
  changing its variety to that specified by the shape, t.

 *******************************************************************/



#include "config.h"
#include "exptypes.h"
#include "installtypes.h"

extern int check(exp e, exp scope);
extern int eq_exp(exp a, exp b);
extern int dochvar(int i, shape t);
extern int dochvar_e(int v, int big, shape f, shape t, int *pr);
extern exp hold_check(exp e);
extern exp hold_const_check(exp e);
extern exp hold(exp e);
extern int docmp_f(int test_no, exp a, exp b);
extern ntest int_inverse_ntest[];
extern ntest real_inverse_ntest[];
extern ntest exchange_ntest[];
