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
$Date: 1998/01/17 15:55:47 $
$Revision: 1.1.1.1 $
$Log: misc_c.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
***********************************************************************/




#include "config.h"
#include "common_types.h"
#include "exp.h"
#include "expmacs.h"
#include "tags.h"
#include "externs.h"
#include "shapemacs.h"
#include "complex_eq.h"

#include "misc_c.h"

static int invar_list
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  while (1) {
    if (e==nilexp)
      return 1;
    if (!invariant_to_apply(e))
      return 0;
    if (last(e))
      return 1;
    e = bro(e);
  };
}

/* determines if e has no side effects and the same value
   if evaluated immediately before and after any procedure
   call (including a recursive one). The evaluation of the
   procedure arguments is assumed to to affect the value of e.
   e will not be nilexp.
*/
int invariant_to_apply
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  if (name(e) == cont_tag)
     return (name(son(e)) == name_tag && isvar(son(son(e))) &&
		iscaonly(son(son(e))) && !isglob(son(son(e))));

  if (name(e) == seq_tag || name(e)  == ident_tag ||
	(name(e) >= plus_tag && name(e) < cont_tag) ||
	name(e) == field_tag || name(e) == reff_tag)
    return invar_list(son(e));

  if (name(e) == contvol_tag)
    return 0;

  return 1;
}

int is_tester
    PROTO_N ( (e, eq) )
    PROTO_T ( exp e X int eq )
{
  if (name(e) == test_tag || name(e) == testbit_tag) {
    if (!eq || test_number(e) == f_equal)
      return 1;
  };
  return 0;
}

int take_out_of_line
    PROTO_N ( (first, alt, in_repeat, scale) )
    PROTO_T ( exp first X exp alt X int in_repeat X double scale )
{
  int extract;
  extract = in_repeat &&
		    name(first) == seq_tag &&
		    name(sh(first)) == bothd &&
		    no(son(alt)) == 1 &&
		    ((is_tester(son(son(first)), 0) &&
		      pt(son(son(first))) == alt) ||
		     (name(son(son(first))) == ident_tag &&
		      is_tester(bro(son(son(son(first)))), 0) &&
		      pt(bro(son(son(son(first))))) == alt)
		     );
  if (!extract &&
	      name(first) == seq_tag &&
	      no(son(alt)) == 1 &&
	      name(bro(son(first))) == apply_tag &&
	      ((is_tester(son(son(first)), 0) &&
		      pt(son(son(first))) == alt) ||
		     (name(son(son(first))) == ident_tag &&
		      is_tester(bro(son(son(son(first)))), 0) &&
		      pt(bro(son(son(son(first))))) == alt)
	      ))
	    extract = 1;

  if (!extract &&
		    name(first) == seq_tag &&
		    no(son(alt)) == 1 &&
		    ((is_tester(son(son(first)), 1) &&
		      pt(son(son(first))) == alt &&
			name(bro(son(son(son(first))))) == null_tag) ||
		     (name(son(son(first))) == ident_tag &&
		      is_tester(bro(son(son(son(first)))), 1) &&
		      pt(bro(son(son(son(first))))) == alt &&
			name(bro(son(bro(son(son(son(first))))))) ==
				 null_tag )
		     ))
	    extract = 1;
  if (!extract &&
		    name(first) == seq_tag &&
		    no(son(alt)) == 1 &&
		    name(son(son(first))) == ident_tag &&
		    is_tester(bro(son(son(son(first)))), 0) &&
		    pt(bro(son(son(son(first))))) == alt &&
		    no(bro(son(son(son(first))))) < 29)
	    extract = 1;
  if (!extract &&
		    name(first) == seq_tag &&
		    no(son(alt)) == 1 &&
		    (is_tester(son(son(first)), 0) &&
		      pt(son(son(first))) == alt)) {
    exp q = bro(son(son(first)));
    exp p = nilexp;
    if (name(q) == prof_tag)
      p = q;
    if (name(q) == 0 && name(bro(q)) == seq_tag &&
	name(son(son(bro(q)))) == prof_tag)
      p = son(son(bro(q)));

    if (p != nilexp && (double)(no(p)) < (0.29 * scale))
      extract = 1;
  };
  return extract;
}

int take_out_by_prob
    PROTO_N ( (first, alt) )
    PROTO_T ( exp first X exp alt )
{
  int extract = 0;
  if (!extract &&
		    name(first) == seq_tag &&
		    no(son(alt)) == 1 &&
		    (is_tester(son(son(first)), 0) &&
		      pt(son(son(first))) == alt &&
			no(son(son(first))) < 29))
	    extract = 1;
  if (!extract &&
		    name(first) == seq_tag &&
		    no(son(alt)) == 1 &&
		    name(son(son(first))) == ident_tag &&
		    is_tester(bro(son(son(son(first)))), 0) &&
		    pt(bro(son(son(son(first))))) == alt &&
		    no(bro(son(son(son(first))))) < 29)
	    extract = 1;
  return extract;
}
/* looks for things like
	(a ~ b) ? a: b
	puts test in t - can make use of delay-slot
*/
int is_maxop
    PROTO_N ( (x, t) )
    PROTO_T ( exp x X exp *t )
{
  exp op1, op2, z, l, w;
  if (name(x) != cond_tag) goto flab0;
  { exp xC = son(x);
    if (name(xC) != seq_tag) goto flab0;
    { exp xCC = son(xC);
      { exp xCCC = son(xCC);
        *t = xCCC;
        if (name(xCCC) != test_tag) goto flab0;
        l=pt(*t);
        { exp xCCCC = son(xCCC);
          op1 = xCCCC;
          if (!(!is_floating(name(sh(op1))))) goto flab0;
          if (last(xCCCC)) goto flab0;
          xCCCC = bro(xCCCC);
          op2 = xCCCC;
          if(!last(xCCCC)) goto flab0;
        }
        if(!last(xCCC)) goto flab0;
      }
      if (last(xCC)) goto flab0;
      xCC = bro(xCC);
      z = xCC;
      if (!(complex_eq_exp(z, op1, nilexp,nilexp))) goto flab0;
      if(!last(xCC)) goto flab0;
    }
    if (last(xC)) goto flab0;
    xC = bro(xC);
    if (l != xC) goto flab0;
    { exp xCC = son(xC);
      z = xCC;
      if (!(no(z)==1)) goto flab0;
      if (last(xCC)) goto flab0;
      xCC = bro(xCC);
      w = xCC;
      if (!(complex_eq_exp(w, op2,nilexp,nilexp))) goto flab0;
      if(!last(xCC)) goto flab0;
    }
    if(!last(xC)) goto flab0;
  }
  return 1;
  flab0: return 0;
}

/* looks for things like
	(a ~ b) ? b: a
	puts test in t - can make use of delay-slot
*/
int is_minop
    PROTO_N ( (x, t) )
    PROTO_T ( exp x X exp *t )
{
  exp op1, op2, z, l, w;
  if (name(x) != cond_tag) goto flab0;
  { exp xC = son(x);
    if (name(xC) != seq_tag) goto flab0;
    { exp xCC = son(xC);
      { exp xCCC = son(xCC);
        *t = xCCC;
        if (name(xCCC) != test_tag) goto flab0;
        l=pt(*t);
        { exp xCCCC = son(xCCC);
          op1 = xCCCC;
          if (!(!is_floating(name(sh(op1))))) goto flab0;
          if (last(xCCCC)) goto flab0;
          xCCCC = bro(xCCCC);
          op2 = xCCCC;
          if(!last(xCCCC)) goto flab0;
        }
        if(!last(xCCC)) goto flab0;
      }
      if (last(xCC)) goto flab0;
      xCC = bro(xCC);
      z = xCC;
      if (!(complex_eq_exp(z, op2,nilexp,nilexp))) goto flab0;
      if(!last(xCC)) goto flab0;
    }
    if (last(xC)) goto flab0;
    xC = bro(xC);
    if (l != xC) goto flab0;
    { exp xCC = son(xC);
      z = xCC;
      if (!(no(z)==1)) goto flab0;
      if (last(xCC)) goto flab0;
      xCC = bro(xCC);
      w = xCC;
      if (!(complex_eq_exp(w, op1,nilexp,nilexp))) goto flab0;
      if(!last(xCC)) goto flab0;
    }
    if(!last(xC)) goto flab0;
  }
  return 1;
  flab0: return 0;
}

#if condassign_implemented

int is_condassign
    PROTO_N ( (e, to_test, to_ass) )
    PROTO_T ( exp e X exp * to_test X exp * to_ass )
{
  exp arg1 = son(e);
  exp arg2 = bro(arg1);
  exp z;
  exp st;
  exp ass;
  exp val;
  if (name(arg1) != seq_tag)
    return 0;

  z = son(arg1);
  st = son(z);
  ass = bro(z);

  if (no(son(arg2)) != 1 || name(bro(son(arg2))) != top_tag)
    return 0;
  if (name(st) != test_tag && name(st) != testbit_tag)
    return 0;
  if (!last(st))
    return 0;
  if (name(ass) != ass_tag)
    return 0;
  if (name(son(ass)) != name_tag || !isvar(son(son(ass))))
    return 0;

  val = bro(son(ass));
  *to_test = st;
  *to_ass = ass;
  if (name(val) == val_tag)
    return 1;

  return 0;
}
#endif


