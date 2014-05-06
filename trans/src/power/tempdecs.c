/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/error.h>

#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/flags.h>

#include <refactor/const.h>

#include <local/exptypes.h>
#include <local/expmacs.h>
#include "bitsmacs.h"
#include "regable.h"
#include "tempdecs.h"
#include "regmacs.h"
#include "stack.h"
#include <local/localflags.h>

/* to go in a switch as in case CASE_APPLYLIKE: */
#define	CASE_APPLYLIKE	apply_tag: case round_tag:case apply_general_tag


static int nouses;
static bool useinpar;
static int param_uses(exp);
static int locate_param(exp);

bool APPLYLIKE(exp e)
{
  if (name(e) ==apply_tag)
    return 1;
  if (name(e) ==apply_general_tag)
    return 1;
  if (name(e) ==round_tag)
    if (name(sh(e)) == ulonghd || cpu != CPU_POWERPC)
      return 1;
  return 0;
}
/* RETURNS_R_RESULT returns 1 if the exp returns R_RESULT when evaluated */
bool RETURNS_R_RESULT(exp e)
{
  if (name(e) ==apply_tag && valregable(sh(e)))
  {
    return 1;
  }
  if (name(e) ==apply_general_tag && valregable(sh(e)))
  {
    return 1;
  }
  if (name(e) ==round_tag)
  {
    if (name(sh(e)) ==ulonghd || cpu != CPU_POWERPC)
      return 1;
  }
  return 0;
}
/* RETURNS_FR_RESULT returns 1 if the exp returns FR_RESULT when evaluated */
bool RETURNS_FR_RESULT(exp e)
{
  if (name(e) ==apply_tag && is_floating(name(sh(e))))
  {
    return 1;
  }
  if (name(e) ==apply_general_tag && is_floating(name(sh(e))))
  {
    return 1;
  }
  return 0;
}


int trace_uses(exp e, exp id)
{
  /*
   * reduces nouses for each non-assignment use of id encountered in e; sets
   * useinpar if use in actual parameter (or function) posn terminates with 0 on
   * applications or jumps terminates with 2 on assignment to id otherwise
   * delivers 1
   * 0 is returned if trace_uses runs into a dead end
   * 2 is returned if trace_uses runs into another assignment
   * 1 is returned if still searching ok so as soon as 0 or 2 is returned
   * the recursion ends quickly
   */

  if (APPLYLIKE(e))
  {
    /* u is nouses before we start to scan the parameters */
    int u = nouses;
    int p = 1;
    exp l = son(e);

    while (p == 1)
    {
      p = trace_uses(l, id);
      if (u != nouses || p == 2)
      {
	/* We found a use of the ident or we found an assignment to it */
	useinpar = 1;
      }

      if (p == 0)
	nouses = u;
      if (last(l))
	break;
      l = bro(l);
    }
    return 0;
  }

  switch (name(e))
  {
   case caller_name_tag:
   case env_offset_tag:
   case general_env_offset_tag:
    /* Don't want to look at sons of these tags */
    return 1;
   case name_tag:
    {
      nouses -= (son(e) == id);
      return 1;
    }

   case ident_tag:
    {
      exp f = son(e);
      exp s = bro(f);
      int a;

      if ((props(e) & defer_bit)!= 0)
      {
	exp t = f;

	f = s;
	s = t;
      }
      a = trace_uses(f, id);
      if (a != 1)
	return a;
      return trace_uses(s, id);
    }
   case case_tag:
    {
      trace_uses(son(e), id);
      return 0;
    }

  case labst_tag:
    return 0;

   case cond_tag:
    {
      int el;

      /* Cond tags are not treated like the default since we know
	 that the first argument will be coded first */
      el = trace_uses(son(e),id);
      if (el != 1)
      {
	return el;
      }
      return 0;
    }
   case seq_tag:
    {
      exp s = son(son(e));

      for (;;)
      {
	int el = trace_uses(s, id);

	if (el != 1)
	  return el;
	if (last(s))
	  return trace_uses(bro(son(e)), id);
	s = bro(s);
      }
    }

   case ass_tag:
    {
      if (isvar(id) && name(son(e)) == name_tag && son(son(e)) == id)
      {
	trace_uses(bro(son(e)), id);
	return 2;
      }
      else if (APPLYLIKE(bro(son(e))))
      {
	return trace_uses(bro(son(e)), id);
      }
      /* else cont to next case */
    }
   default:
    {
      exp s = son(e);
      int nu = nouses;
      int bad_arguments = 0;
      /* A bad argument is one which contains an assignment or something to stop flow */
      int good_arguments = 0;
      /* A good_argument is one which contains one or more uses of id, but doesn't have
	 any assignments or things to stop flow */
      int ret_value = 0;

      if (s==nilexp)
      {
	/*no arguments */
	return 1;
      }
      for (;;)
      {
	int monitor_uses;
	int el;
	monitor_uses = nouses;
	el = trace_uses(s, id);
	if (el==1  && nouses < monitor_uses)
	{
	  /* argument with uses of ident*/
	  good_arguments ++;
	}
	if (el != 1)
	{
	  /* An argument corrupts the flow */
	  bad_arguments++;
	  ret_value = el;
	}
	if (last(s))
	  break;
	s = bro(s);
      }
      if (bad_arguments==0)
      {
	return 1;
	/* No problems */
      }

      if (bad_arguments==1 && good_arguments==0)
      {
	/* one bad one */
	/* all the rest don't use it */
	return ret_value;
      }
      nouses = nu;
      return ret_value;
    }
  }
}


void after_a(exp a, exp id)
{
  /* apply trace_uses to dynamic successors of a */
  exp dad;
  exp l;

tailrecurse:
  dad = father(a);
  if (nouses == 0)
    return;
  if (name(dad) == cond_tag || name(dad) == rep_tag
      || name(dad) == solve_tag || name(dad) == labst_tag
      || name(dad) == case_tag || name(dad) == goto_tag
      || name(dad) == test_tag || APPLYLIKE(dad))
  {
    /* dont try too hard ! */
    while (APPLYLIKE(dad) && dad != id)
      dad = father(dad);
    if (APPLYLIKE(dad))
    {
      useinpar = 1;
    }
    return;
  }


  for (l = a; !last(l); l = bro(l))
  {
    int u = trace_uses(bro(l), id);

    if (u != 1 || nouses == 0)
      return;
  }
  a = dad;
  if (dad != id)
    goto tailrecurse;
}
bool simple_seq(exp e, exp id)
{
#if 0
  exp dad = father(e);

  for (;;)
  {
    if (dad == id)
      return 1;
    if (name(dad) == seq_tag || name(dad) == 0
	|| name(dad) == ident_tag)
    {
      dad = father(dad);
    }
    else
      return 0;
  }
#else
  return 1;
#endif
}

int tempdec(exp e, bool enoughs)
{
  /*
   * e is a local declaration; 'enoughs' is a misnomer to say whether there
   * are t-regs available delivers 1 if e can be allocated into t-reg or par
   * reg
   */
  exp p;

  if (~optim & OPTIM_TEMPDEC)
    return 0;

  nouses = 0;
  useinpar = 0;

  if (isvar(e))
  {
    for (p = pt(e); p != nilexp; p = pt(p))
    {
      /* find no of uses which are not assignments to id ... */
      if (!last(p) && last(bro(p))
	  && name(bro(bro(p))) == ass_tag)
      {
	if (!simple_seq(bro(bro(p)), e))
	  return 0;
	continue;
      }
      nouses++;
    }
  }
  else
    nouses = no(e);

  /*
   * trace simple successors to assignmnts or init to id to find if all uses
   * occur before unpredictable change of control (or another assignment to
   * id)
   */

  if (name(son(e))!= clear_tag || isparam(e))
  {
    after_a(son(e), e);
  }

  if (isvar(e))
  {
    for (p = pt(e); p != nilexp; p = pt(p))
    {
      if (!last(p) && last(bro(p))
	  && name(bro(bro(p))) == ass_tag)
      {
	after_a(bro(bro(p)), e);
      }
    }
  }

  if (nouses == 0 && (enoughs || !useinpar))
  {
    if (useinpar)
    {
      /* See if it can be allocated into a parameter register */
      props(e) |= notparreg;
      if (isparam(e))
      {
	return param_uses(e);
      }
      else
	return 100;
    }
    return 100;
  }
  return 0;
}
static int param_uses(exp id)
{
  exp p;
  ASSERT(isparam(id));
  ASSERT(useinpar);
  ASSERT(nouses==0);
  /* We found all the uses of the ident and we found one of them in a parameter list */

  for (p=pt(id); p!=nilexp;p = pt(p))
  {
    if (APPLYLIKE(father(p)))
    {
      return locate_param(p);
    }
  }
  /* not a simple use in a parameter list */
  return 100;
}
static int locate_param(exp e)
{
  exp f = father(e);
  bool is_float = is_floating(name(sh(e)));
  exp par;


  ASSERT(APPLYLIKE(f));
  switch (name(f))
  {
   case apply_general_tag:
    par =  son(bro(son(f)));
    break;
   case apply_tag:
    par = bro(son(f));
    break;
   case round_tag:
    par = son(f);
    break;
   default:
    return 0;
  }
  {
    int fxparam = R_FIRST_PARAM;
    int flparam = FR_FIRST_PARAM;
    int stparam = 0;

    for (;;)
    {
      int par_size = shape_size(sh(par));

      if (par==e)
      {
	/* We have found it */
	if (is_float)
	{
	  if (flparam>FR_LAST_PARAM)
	    return 0;
	  else
	    return flparam;
	}
	else
	{
	  if (fxparam>end_param)
	    return 0;
	  else
	    return fxparam;
	}
      }
      stparam = ALIGNNEXT(stparam + par_size,32);
      fxparam = (stparam/32) + R_FIRST_PARAM;
      if (is_floating(name(sh(par))))
      {
	flparam++;
      }
      if (last(par))
	break;
      par = bro(par);
    }
    return 0;
  }
}



