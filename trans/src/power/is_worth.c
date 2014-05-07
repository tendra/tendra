/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <local/expmacs.h>

#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/shapemacs.h>

/* construct/is_worth.h defines the interface each installer must implement */
#include <construct/is_worth.h>

#include "instruct.h"	/* IMM_SIZE() */
#include "regable.h"



#define true 1
#define false 0


/*
 * Will an ident exp be in memory?
 * We have to guess at this stage for non globals.
 */
#define INMEMIDENT(ident_exp)	(isvis(ident_exp) || isglob(ident_exp))




/*
 * is_worth() for a complicated cont_tag.
 * True for any combination of reff_tag, cont_tag and name_tag.
 * 'c' is the son of the top cont_tag.
 * Allowing anything causes a bug when compiling SPECINT92 085.gcc.
 */
static bool is_worth_cont_aux(exp c)
{
  switch(name(c))
  {
  case reff_tag:
    if (no(c) != 0)
      return 0;			/* dont optimise non-zero offset */
    /*FALLTHROUGH*/
  case cont_tag:
    return is_worth_cont_aux(son(c));

  case name_tag:
    return 1;

  default:
    return 0;
  }
  /*NOTREACHED*/
}


/*
 * Decide if expression c is worth declaring separately over a range it's
 * value will not change over, eg outside loop.
 * We have to balance the value of this against likely register pressure
 * impact.
 */
int is_worth(exp c) /* used only in mc_list */
{				/* decide if constant c is worth declaring
				 * separately */
  int cnam = name(c);
  shape s = sh(c);

  if (!is_floating(name(s)) && !valregable(s))
    return false;			/* cannot go inreg, and anyway
					 * too big to be worthwhile */

  if (name(s) == ptrhd && al1(s) == 1)
    return false;			/* ptr bits */

  if (cnam == real_tag)
    return true;			/* real const complex to load */

  if (cnam == goto_tag)
    return false;			/* never identify a goto (causes bad labels) */

  if (cnam == cont_tag && name(son(c)) == name_tag)
  {
    /* a simple load, most worthwile for globals to avoid TOC access */
    return INMEMIDENT(son(son(c)));
  }

  if (cnam == cont_tag)
  {
    /* complex load */
    return is_worth_cont_aux(son(c));
  }

  if (cnam == name_tag && isglob(son(c)) && name(s) != prokhd)
  {
    /* avoid load of TOC table entry in loops, except for params where there is no load delay */
    return name(father(c)) != apply_tag;
  }

  if (cnam == val_tag)
  {
    /* it is sometimes worthwhile extracting big constants from loops ... */
    long n = no(c);
    exp dad = father(c);

    switch (name(dad))
    {
    case and_tag:	/* +++ allow for rlimn instruction */
    case or_tag:
    case xor_tag:
      {
	return !(IMMLOGL_SIZE(n) || IMMLOGU_SIZE(n));	/* short literal operands */
      }
    case mult_tag:
    case offset_mult_tag:
      {
	/*
	 * a*2^n and a*2^(n+-1) are transformed later to shifts and adds
	 */
	return !IMM_SIZE(n) && (n & (n - 1)) != 0 && (n & (n + 1)) != 0 && ((n - 1) & (n - 2)) != 0;
      }
    case div1_tag:
    case div2_tag:
    case rem2_tag:
      {
	/* a/2^n transformed later to shift */
	return !IMM_SIZE(n) && (n & (n - 1)) != 0;
      }

    case ass_tag:
    case assvol_tag:
      {
	/* must load all constants before store */
	/* +++ better way of working out inmem lhs */
	exp lhs = son(dad);

	if (name(lhs) == name_tag)
	{
	  if (INMEMIDENT(son(lhs)))
	    return true;		/* inmem */
	  else
	    return !IMM_SIZE(n) && !IMMLOGU_SIZE(n);
					/* big const */
	}
	else
	{
	  /* complicated inmem */
	  return true;
	}
      }

    default:
      {
	return !IMM_SIZE(n) /* short literal operands */ ;
      }
    }				/* end sw */

  }

  if (is_o(cnam) || cnam == clear_tag)
  {
    /* simple construct */
    return false;
  }

  /* something complicated */
  return true;
}
