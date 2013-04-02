/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*******************************************************************

  The routine refactor performs the bottom-up TDF-to-TDF optimising
  transformations. When a new exp is created refactor is applied to
  see if a recognised situation has arisen. refactor assumes that
  all components of this new exp have already had refactor applied to them.
  It returns 1 if it has made a change, 0 if not.


  hold_refactor holds an exp as the son of a dummy exp and then
  applies refactor. the need for this operation is explained in
  the overall documentation.

  eq_exp compares two exp for equality of effect.

  dochvar takes the int, i, and delivers the number which results from
  changing its variety to that specified by the shape, t.

 *******************************************************************/

#include "exptypes.h"
#include <construct/installtypes.h>

extern int refactor(exp e, exp scope);
extern int eq_exp(exp a, exp b);
extern int dochvar(int i, shape t);
extern int dochvar_e(int v, int big, shape f, shape t, int *pr);
extern exp hold_refactor(exp e);
extern exp hold_const_refactor(exp e);
extern exp hold(exp e);
extern int docmp_f(int test_no, exp a, exp b);
extern ntest int_inverse_ntest[];
extern ntest real_inverse_ntest[];
extern ntest exchange_ntest[];
