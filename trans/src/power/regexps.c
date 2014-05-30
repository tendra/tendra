/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/check.h>
#include <shared/error.h>

#include <local/exptypes.h>

#include <main/flags.h>

#include "memtdf.h"
#include "codegen.h"
#include "maxminmacs.h"		/* for absval() */
#include "comment.h"
#include "regexps.h"

struct regpeept
{
  ans inans;
  exp keptexp;
  bool iscont;
};

typedef struct regpeept regpeep;

#define FR_OFFSET		KEPT_FREG_OFFSET	/* 32 */
#define	LAST_ALL_REGS		(FR_OFFSET+FR_LAST)	/* 63 */

regpeep regexps[LAST_ALL_REGS+1];	/* [0:31] fix pt - [32:63] floating pt */

static bool sim_exp(exp, exp);


/* both either floating or fixed and same size and alignment */
bool keep_eq_size(shape as, shape bs)
{
  bool as_flt = is_floating(name(as));
  bool bs_flt = is_floating(name(bs));

  if (as_flt != bs_flt)
    return 0;			/* dissimilar float/fixed */

  return shape_size(as) == shape_size(bs) && shape_align(as) == shape_align(bs);
}


static bool sim_explist(exp al, exp bl)
{
  if (al == NULL && bl == NULL)
    return 1;
  if (al == NULL || bl == NULL)
    return 0;
  if (!sim_exp(al, bl))
    return 0;
  if (last(al) && last(bl))
    return 1;
  if (last(al) || last(bl))
    return 0;
  return sim_explist(bro(al), bro(bl));
}


static bool sim_exp(exp a, exp b)
{

  /*
   * basically eq_exp except equal shapes requirement is weakened to equal
   * sizes and alignments
   */
  if (name(a) == name(b))
  {
    if (name(a) == name_tag)
    {
      /* See if both are name_tags for same ident
	 with same offsets and same size and alignment */
      return son(a) == son(b) && no(a) == no(b) &&
	      keep_eq_size(sh(a), sh(b));
    }
    /* If it is not is_a
       OR
       if they are not the same size and alignment and same
     register type
     */
    if (!is_a(name(a)) || !keep_eq_size(sh(a), sh(b)))
    {
      return 0;
    }
    if (name(a) ==float_tag)
    {
      return eq_exp(son(a),son(b));
      /* float_tag is special since we could have e.g float (-1 slongsh) float (-1 ulongsh) */
    }

    return no(a) == no(b) && sim_explist(son(a), son(b));
  }
  return 0;
}


void clear_all(void)
{
  /* forget all register<->exp associations */
  int i;

  for (i = 0; i <= LAST_ALL_REGS; i++)
  {
    regexps[i].keptexp = NULL;
    setregalt(regexps[i].inans, 0);
  }
}


void clear_reg(int i)
{
  /* forget reg i - exp association */
  i = absval(i);
  if (i >= 0 && i <= LAST_ALL_REGS)
  {
    regexps[i].keptexp = NULL;
    setregalt(regexps[i].inans, 0);
  }
}


/* find if e has already been evaluated into a register low_reg..hi_reg

   Register tracking:
   The array regexps[] is an array of regpeep structures
   The elements of the structure regpeep are :

   ans inans;     This helps specify where the exp came from
   exp keptexp;   The exp
   bool iscont;   This specifies whether or not

   */
static ans iskept_regrange(exp e, int low_reg, int hi_reg)
{
  int i;
  ans aa;
  setregalt(aa, 0);		/* nilans until we know better */

  /* reg tracking of unions unsafe, as views of location can differ */
  /* +++ improve this */
  if (name(sh(e)) == cpdhd)
  {
    return aa;
  }


  for (i = low_reg; i <= hi_reg; i++)
  {
    exp ke = regexps[i].keptexp;

    if (ke != NULL)
    {
      /* There is an association with register i */
      bool isc = regexps[i].iscont;

      ASSERT(!IS_R_TMP(i));	/* should not track R_TMP */

      if (
	 ((!isc && sim_exp(ke, e)) ||
	  (name(e) == cont_tag && isc && keep_eq_size(sh(ke), sh(e))
	    && sim_exp(ke, son(e)) && al1(sh(son(e))) == al1(sh(ke)))
	  )
	)
      {
	aa = (regexps[i].inans);

	FULLCOMMENT4("iskept found 1: reg=%d isc=%d name(e) =%d name(son(e)) =%d",
		     i, isc, name(e), name(son(e)));
	COMMENT1("iskept found: no = %d",no(e));


	switch (aa.discrim)
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
	    /* else ... */
	  }
	default:
	  return aa;
	}
      }
      else if (name(ke) == cont_tag && !isc)
      {
	ans aq;

	aq = regexps[i].inans;

	if (aq.discrim == notinreg)
	{
	  instore is;

	  is = insalt(aq);
	  if (!is.adval && is.b.offset == 0 && IS_FIXREG(is.b.base)
	      && sim_exp(son(ke), e))
	  {

	    /*
	     * the contents of req expression is here as a reg-offset
	     */
	    is.adval = 1;
	    setinsalt(aq, is);

	    FULLCOMMENT4("iskept found 2: reg=%d isc=%d name(e) =%d name(son(e)) =%d",
			 i, isc, name(e), name(son(e)));

	    return aq;
	  }
	}
      }
      else if (name(ke) == reff_tag && !isc)
      {
	ans aq;

	aq = regexps[i].inans;
	if (aq.discrim == notinreg)
	{
	  instore is;

	  is = insalt(aq);
	  if (is.adval && is.b.offset == (no(ke) / 8)
	      && IS_FIXREG(is.b.base)
	      && sim_exp(son(ke), e))
	  {

	    /*
	     * a ref select of req expression is here as a reg-offset
	     */
	    is.adval = 1;
	    is.b.offset = 0;
	    setinsalt(aq, is);

	    FULLCOMMENT4("iskept found 3: reg=%d isc=%d name(e) =%d name(son(e)) =%d",
			 i, isc, name(e), name(son(e)));

	    return aq;
	  }
	}
      }
    }
  }
  return aa;
}


/* find if e has already been evaluated into register 'reg' */
ans iskept_inreg(exp e, int reg)
{
  return iskept_regrange(e, reg, reg);
}


/* find if e has already been evaluated into a fixed point register */
ans iskept_reg(exp e)
{
  return iskept_regrange(e, 0, R_LAST);
}


/* find if e has already been evaluated into a floating point register */
ans iskept_freg(exp e)
{
  return iskept_regrange(e, FR_OFFSET, LAST_ALL_REGS);
}


/* find if e has already been evaluated into any register */
ans iskept(exp e)
{
  return iskept_regrange(e, 0, LAST_ALL_REGS);
}


/* return reg if 'a' can is in fixed reg */
int ans_reg(ans aa)
{
  if (aa.discrim == inreg && regalt(aa)!= 0)
  {
    /* the same expression has already been evaluated into a reg */
    return regalt(aa);
  }

  if (aa.discrim == notinreg)
  {
    instore is; is = insalt(aa);	/* no init to avoid IBM cc bug */

    if (is.adval && is.b.offset == 0)
    {
      /* the same expression has already been evaluated into a reg */
      return is.b.base;
    }
  }

  return R_NO_REG;
}


/* set up exp - address association */
void keepexp(exp e, ans loc)
{
  int pos=0;

  switch (loc.discrim)
  {
  case insomereg:
  case insomefreg:
    {
      fail("Keep ? reg");
    }
  case inreg:
    {
      pos = regalt(loc);
      break;
    }
  case infreg:
    {
      pos = fregalt(loc).fr + FR_OFFSET;
      break;
    }
  case notinreg:
    {
      pos = insalt(loc).b.base;
      if (!IS_FIXREG(pos))
	return;
    }

  }

  ASSERT(pos >= 0 && pos <= LAST_ALL_REGS);

  if (IS_R_TMP(pos))
    return;			/* don't track R_TMP which is used outside
				 * tracking scheme */

  regexps[pos].keptexp = e;
  regexps[pos].inans = loc;
  regexps[pos].iscont = 0;
  COMMENT2("keepexp : reg %d kept name is %d",pos,name(e));
}


/* set up cont(e)-reg association */
/* if 0=<reg<=31  this means a fixed point register
   if 31<reg<=63  this means a float point register single precision
   if -63<=reg<-31 this means a float point register double precision
   */
void keepcont(exp e, int reg)
{
  freg fr;
  int z = absval(reg);

  if (z >= FR_OFFSET)
  {
    fr.dble = (reg < 0);
    fr.fr = z - FR_OFFSET;
    setfregalt(regexps[z].inans, fr);
  }
  else
  {
    instore is;

    if (IS_R_TMP(z))
      return;			/* don't track R_TMP which is used outside
				 * tracking scheme */

    is.b.base = reg;
    is.b.offset = 0;
    is.adval = 1;
    setinsalt(regexps[z].inans, is);
  }

  ASSERT(z >= 0 && z <= LAST_ALL_REGS);
  regexps[z].keptexp = e;
  regexps[z].iscont = 1;
  COMMENT2("keepcont : reg %d kept name is %d",z,name(e));

}


/* keepreg keeps the exp e */
/* if 0=<reg<=31  this means a fixed point register
   if 31<reg<=63  this means a float point register single precision
   if -63<=reg<-31 this means a float point register double precision
   */
void keepreg(exp e, int reg)
{
  freg fr;
  int z = absval(reg);

  if (z >= FR_OFFSET)
  {
    /* It is a float register */
    /* HACK: if reg <0 then it is double
       otherwise it is single precision */
    fr.dble = (reg < 0);
    fr.fr = z - FR_OFFSET;
    setfregalt(regexps[z].inans, fr);
  }
  else
  {
    instore is;
    if (IS_R_TMP(z))
    {
      return;			/* don't track R_TMP which is used outside
				 * tracking scheme */
    }
    is.b.base = reg;
    is.b.offset = 0;
    is.adval = 1;
    setinsalt(regexps[z].inans, is);
  }

  ASSERT(z >= 0 && z <= LAST_ALL_REGS);
  regexps[z].keptexp = e;
  regexps[z].iscont = 0;
  COMMENT3("keepreg : reg %d kept name is %d no %d",z,name(e),no(e));
}

bool couldeffect(exp , exp);

/* could 'e' be 'lhs' */
bool couldbe(exp e, exp lhs)/* is var name_tag exp or 0 meaning cont */
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
      return lhs == 0 && (isglob(s) || isvis(s));
    }
    if (IS_A_PROC(s))
      return lhs == 0;
    if (son(s) == NULL)
      return 1;
    return couldbe(son(s), lhs);
  }
  if (ne == cont_tag)
  {
    if (lhs != 0 && name(s) == name_tag && son(s)!= NULL)
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
bool couldeffect(exp e, exp z)/* a name or zero */
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
    if (son(son(e)) == NULL)
      return 1 /* could it happen? */ ;

    return couldeffect(son(son(e)), z);

  }
  if (ne < plus_tag || ne == contvol_tag)
    return 1;

  e = son(e);

  while (e != NULL)
  {
    if (couldeffect(e, z))
      return 1;
    if (last(e))
      return 0;
    e = bro(e);
  }
  return 0;
}


/* does e depend on z */
bool dependson(exp e, bool isc, exp z)
{
  if (e == NULL)
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
    if (son(son(z)) == NULL)
      return 1;			/* can it happen? */
    z = son(son(z));
  }

  /* z is now unambiguous variable name or 0 meaning some contents */

  return (isc)? couldbe(e, z): couldeffect(e, z);
}


/* remove association of any register which depends on lhs */
void clear_dep_reg(exp lhs)
{
  int i;

  for (i = 0; i <= LAST_ALL_REGS; i++)
  {
    if (regexps[i].keptexp != NULL)
    {
      switch (name(regexps[i].keptexp))
      {
      case val_tag:
      case null_tag:
      case real_tag:
      case string_tag:
      case name_tag:
      case current_env_tag:
	{
	  if (!regexps[i].iscont)
	  {
	    /* constant value, cannot be changed by assign */
	    continue;
	  }
	}
	/*FALLTHROUGH*/

      default:
	{
          if (dependson(regexps[i].keptexp, regexps[i].iscont, lhs))
          {
            FULLCOMMENT2("clear_dep_reg: reg=%d iscont=%d", i, regexps[i].iscont);
            regexps[i].keptexp = NULL;
            setregalt(regexps[i].inans, 0);
          }
	}
      }
    }
  }
}
