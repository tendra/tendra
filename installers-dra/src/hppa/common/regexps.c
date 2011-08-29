/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
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


/*
$Log: regexps.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:03  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1996/11/14  15:22:26  wfs
 *    Fixed a bug in regexps.c which was common to most of the installers and
 * has only just come to light due to PWE's work on powertrans. (There was
 * previously only a patch.) Cosmetic changes to other files.
 *
 * Revision 1.3  1996/01/23  15:26:07  wfs
 * "current_env_tag" in "dependson()".
 *
 * Revision 1.2  1995/12/18  13:12:30  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.2  1995/10/20  14:11:15  wfs
 * gcc compilation changes.
 *
 * Revision 5.1  1995/09/15  13:13:36  wfs
 * Mike Gerrard's bug fix incorporated.
 *
 * Revision 5.0  1995/08/25  13:42:58  wfs
 * Preperation for August 25 Glue release
 *
 * Revision 3.4  1995/08/25  10:29:56  wfs
 * Register synonyms changed
 *
 * Revision 3.4  1995/08/25  10:29:56  wfs
 * Register synonyms changed
 *
 * Revision 3.1  95/04/10  16:28:04  16:28:04  wfs (William Simmonds)
 * Apr95 tape version.
 *
 * Revision 3.0  95/03/30  11:18:54  11:18:54  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 *
 * Revision 2.0  95/03/15  15:28:43  15:28:43  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 *
 * Revision 1.1  95/01/11  13:16:12  13:16:12  wfs (William Simmonds)
 * Initial revision
 *
*/


#define HPPATRANS_CODE
/* regexps.c

For trivial 'peephole' optimisations

*/



#include "config.h"
#include "expmacs.h"
#include "addrtypes.h"
#include "tags.h"
#include "move.h"
#include "bitsmacs.h"
#include "maxminmacs.h"
#include "shapemacs.h"
#include "common_types.h"
#include "regmacs.h"
#include "myassert.h"
#include "comment.h"
#include "check.h"
#include "regexps.h"

/* 22.11.94. Corrected bug found by Ian Currie, i.e. isglob(s) assertion
   added to line 351 */


int line;

regpeep regexps[64];		/* [0:31] fix pt - [32:47] floating pt */

bool sim_exp(exp, exp);

/* Same size and alignment and "both float or both fixed". */
bool eq_sze
(shape as, shape bs)
{
  if (is_floating(name(as)))
    return name(as) == name(bs);
  if (is_floating(name(bs)))
    return 0;
  return shape_size(as) == shape_size(bs) && shape_align(as) == shape_align(bs);
}

bool sim_explist
(exp al, exp bl)
{
  if (al == nilexp && bl == nilexp)
    return 1;
  if (al == nilexp || bl == nilexp)
    return 0;
  if (!sim_exp(al, bl))
    return 0;
  if (last(al) && last(bl))
    return 1;
  if (last(al) || last(bl))
    return 0;
  return sim_explist(bro(al), bro(bl));
}

bool sim_exp
(exp a, exp b)

 /*
  * basically eq_exp except equal shapes requirement  is weakened to equal
  * sizes and alignments
  */
{
   if (name(a) == name(b))
   {
      if (name(a) == name_tag)
      {
	 return son(a) == son(b) && no(a) == no(b) &&
	      eq_sze(sh(a), sh(b));
      }
      if (!is_a(name(a)) || !eq_sze(sh(a), sh(b)))
	 return 0;
      if(name(a)==float_tag)/* NEW bit */
      {
	return eq_exp(son(a),son(b));
      }
      return no(a) == no(b) && sim_explist(son(a), son(b));
  };
  return 0;
}

/* forget all register - exp associations */
void clear_all
(void)
{
  int i;

  for (i = 0; i < 48; i++)
  {
    regexps[i].keptexp = nilexp;
    setregalt(regexps[i].inans, 0);
  }
}



/* forget reg i - exp association */
void clear_reg
(int i)
{
  i = ABS_OF(i);
  if (i >= 0 && i < 48)
  {
    regexps[i].keptexp = nilexp;
    setregalt(regexps[i].inans, 0);
  }
}


/* find if e has already been evaluated into a register */
ans iskept
(exp e)
{
  int i;
  ans nilans;

  setregalt(nilans, 0);		/* init nilans */

#ifdef NO_KEPT_OPTS
  /* no reg tracking */
  return nilans;
#endif

  /* reg tracking of unions unsafe, as views of location can differ */
  /* +++ track on fields */
  /* +++ safe to allow structs but not unions */
  if (name(sh(e)) == cpdhd)
  {
    return nilans;
  }

  for (i = 0; i < 48; i++)
  {
    exp ke = regexps[i].keptexp;
    bool isc = regexps[i].iscont;

    if (ke != nilexp)
    {
      /* there is an accociation with reg i */
      if (
	 ((!isc && sim_exp(ke, e)) ||
	  (name(e) == cont_tag && isc && eq_sze(sh(ke), sh(e))
	    && sim_exp(ke, son(e)))
	  )
	)
      {
	ans aa;
	aa = (regexps[i].inans);

#if 0
	FULLCOMMENT4("iskept found: reg=%d isc=%d name(e) =%d name(son(e)) =%d", i, isc, name(e), name(son(e)));
	FULLCOMMENT3("	hd(e) =%d hd(son(e)) =%d hd(ke) =%d", name(sh(e)), name(sh(son(e))), name(sh(ke)));
	FULLCOMMENT3("	sim_exp(ke, e) =%d sim_exp(ke, son(e)) =%d eq_size(sh(ke), sh(e)) =%d",
		sim_exp(ke, e), sim_exp(ke, son(e)), eq_size(sh(ke), sh(e)));
#endif

	switch (discrim(aa))
	{
	case notinreg:
	  {
	    if (!aa.val.instoreans.adval)
	    {

	      /*
	       * the expression is given indirectly - it may have also been
	       * loaded into a register
	       */
	      continue;
	    }
	  }
	  /* FALLTHROUGH */

	default:
	  return aa;
	}
      }
      else if (name(ke) == cont_tag && !isc)
      {
	ans aq;

	aq = regexps[i].inans;
	if (discrim(aq) == notinreg)
	{
	  instore is;

	  is = insalt(aq);
	  if (!is.adval && is.b.offset == 0 && IS_FIXREG(is.b.base)
	      && sim_exp(son(ke), e))
	  {
	    /* the contents of req expression is here as a reg-offset */
	    is.adval = 1;
	    setinsalt(aq, is);
	    return aq;
	  }
	}
      }
      else if (name(ke) == reff_tag && !isc)
      {
	ans aq;

	aq = regexps[i].inans;
	if (discrim(aq) == notinreg)
	{
	  instore is;

	  is = insalt(aq);
	  if (is.adval && is.b.offset == (no(ke) / 8)
	      && IS_FIXREG(is.b.base)
	      && sim_exp(son(ke), e))
	  {
	    /* a ref select of req expression is here as a reg-offset */
	    is.adval = 1;
	    is.b.offset = 0;
	    setinsalt(aq, is);
	    return aq;
	  }
	}
      }
    }
  }
  return nilans;
}

/* set up exp - address association */
void keepexp
(exp e, ans loc)
{
  int reg=0;

  switch (discrim(loc))
  {
  case insomereg:
  case insomefreg:
    {
      fail("keep ? reg");
    }
#if USE_BITAD
  case bitad:
    {
      return;
    }
#endif
  case inreg:
    {
      reg = regalt(loc);
      break;
    }
  case infreg:
    {
      reg = fregalt(loc).fr + 32;
      break;
    }
  case notinreg:
    {
      reg = insalt(loc).b.base;
      if (!IS_FIXREG(reg))
	return;
      break;
    }
  default:{}
  }

  assert(reg >= 0 && reg < 48);
  assert(reg != GR1);

  regexps[reg].keptexp = e;
  regexps[reg].inans = loc;
  regexps[reg].iscont = 0;
}

/* set up cont(e)-reg association */
void keepcont
(exp e, int regcode)
{
  freg fr;
  int reg = ABS_OF(regcode);

  assert(reg >= 0 && reg < 48);
  assert(reg != GR1);

  if (reg > 31)
  {
    fr.dble = ((regcode < 0)? 1 : 0);
    fr.fr = reg - 32;
    setfregalt(regexps[reg].inans, fr);
  }
  else
  {
    instore is;

    is.b.base = regcode;
    is.b.offset = 0;
    is.adval = 1;
    setinsalt(regexps[reg].inans, is);
  }

  regexps[reg].keptexp = e;
  regexps[reg].iscont = 1;
}

/* set up e-reg association */
void keepreg
(exp e, int regcode)
{
  freg fr;
  int reg = ABS_OF(regcode);

  assert(reg >= 0 && reg < 48);
  assert(reg != GR1);

  if (reg > 31)
  {
    fr.dble = ((regcode < 0)? 1 : 0);
    fr.fr = reg - 32;
    setfregalt(regexps[reg].inans, fr);
  }
  else
  {
    instore is;

    is.b.base = regcode;
    is.b.offset = 0;
    is.adval = 1;
    setinsalt(regexps[reg].inans, is);
  }

  regexps[reg].keptexp = e;
  regexps[reg].iscont = 0;
}


bool couldeffect(exp, exp);


/* could e be lhs */
bool couldbe
(exp e, exp lhs)
{
  int ne = name(e);
  exp s = son(e);

  if (ne == name_tag)
  {
    if (lhs != 0 && s == son(lhs))
    {
      return 1;
    }
    if (isvar(s))
    {
      return lhs == 0 && (isvis(s) || isglob(s));
    }
    if (IS_A_PROC(s))
      return lhs == 0;
    if (son(s) == nilexp)
      return 1;
    return couldbe(son(s), lhs);
  }
  if (ne == cont_tag)
  {
    if (lhs != 0 && name(s) == name_tag && son(s)!= nilexp)
    {
      return son(s) == son(lhs) || isvis(son(lhs)) || isvis(son(s));
    }
    return 1;
  }
  if (ne == reff_tag || ne == field_tag)
  {
    return couldbe(s, lhs);
  }
  if (ne == addptr_tag || ne == subptr_tag)
  {
    return couldbe(s, lhs) || couldeffect(bro(s), lhs);
  }

  return 1;

}

/* could alteration to z effect e? */
bool
couldeffect(exp e, exp z /* a name or zero */)
{
  int ne = name(e);
  if (ne == cont_tag)
  {
    return couldbe(son(e), z);
  }
  if (ne == name_tag)
  {
    if (isvar(son(e)))
      return z == 0 && isvis(son(e));
    if (IS_A_PROC(son(e)))
      return 0;
    if (son(son(e)) == nilexp)
      return 1 /* could it happen? */ ;

    return couldeffect(son(son(e)), z);

  }
  if (ne < plus_tag || ne == contvol_tag)
    return 1;

  e = son(e);

  while (e != nilexp)
  {
    if (couldeffect(e, z))
      return 1;
    if (last(e))
      return 0;
    e = bro(e);
  }
  return 0;
}

bool dependson
(exp e, bool isc, exp z)
{				/* does e depend on z */
  if (e == nilexp)
  {
    return 0;
  }
  for (;;)
  {
    if (name(z) == reff_tag || name(z) == addptr_tag ||
	name(z) == subptr_tag)
    {
      z = son(z);
    }

    if (name(z)!= name_tag)
    {
      if (name(z)!= cont_tag)
	return 1;
      z = 0;
      break;
    }

    if (isvar(son(z)))
      break;
    if (IS_A_PROC(son(z)))
    {
      z = 0;
      break;
    }
    if (son(son(z)) == nilexp)
      return 1;			/* can it happen? */
    z = son(son(z));
  }

  /* z is now unambiguous variable name or 0 meaning some contents */

  return isc ? couldbe(e, z) : couldeffect(e, z);
}


/* remove association of any register which depends on lhs */
void clear_dep_reg
(exp lhs)
{
  int i;

  for (i = 0; i < 48; i++)
  {
    if (dependson(regexps[i].keptexp, regexps[i].iscont, lhs))
    {
      regexps[i].keptexp = nilexp;
      setregalt(regexps[i].inans, 0);
    }
  }
}





