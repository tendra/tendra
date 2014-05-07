/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <local/expmacs.h>

#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/shapemacs.h>
#include <construct/is_worth.h>

#define true 1
#define false 0

int
is_worth(exp c)
{				/* decide if constant c is worth declaring
				   separately */
  unsigned char cnam = name (c);
  bool isflt = is_floating(name(sh(c)));

  if (name (sh (c)) == ptrhd && al1(sh(c))==1 )
    return 0;			/* ptr bits */
  if (cnam == real_tag) return true;
  if (cnam == cont_tag && isflt && (name(son(c)) != name_tag || isglob(son(son(c))) )) {
		return true;
  }
  if (cnam == cont_tag && name (son (c)) == name_tag && isglob (son (son (c)))) {
	return true;
  }
  if (cnam == val_tag) {	/* it is sometimes worthwhile extracting
				   big constants from loops ... */
    long  n = no (c);
    exp dad;
    if (n == 0 || bro(c)==nilexp) {
      return false;
    }
    dad = father (c);
    if (dad==nilexp) return false;
    switch (name (dad)) {
      case and_tag:
	{
	  exp grandad = father (dad);
	  if ( grandad != nilexp &&
	       name (grandad) == test_tag && (n & (n - 1)) == 0 &&
	      (props (grandad) == 5 || props (grandad) == 6) &&
	      ((name (bro (son (grandad))) == val_tag && no (bro (son (grandad))) == 0)
	      || (name (son (grandad)) == val_tag && no (son (grandad)) == 0))
	    ) {			/*  a & 2^n == 0 is transformed later to
				   shift and test negative */
	    return 0;
	  }
	  /* else next case */
	}
      case or_tag:
      case xor_tag:

	{
	  return n < 0 || n >= 0xffff;/* short literal operands */
	}

      case test_tag: return 1;
      case mult_tag: case offset_mult_tag:
	{
	  if (n <= 0x7fff && n > -0x8000)
	    return 0;		/* short literal operands */
	  /* a*2^n and a*2^(n+-1) are transformed later to shifts and adds
	     */
	  return (n & (n - 1)) != 0 && (n & (n + 1)) != 0 && ((n - 1) & (n - 2)) != 0;
	}
      case div1_tag:
      case div2_tag:
      case rem2_tag:
	{
	  if (n <= 0x7fff && n > -0x8000)
	    return 0 /* short literal operands */ ;
	  /* a/2^n transformed later to shift */
	  return (n & (n - 1)) != 0;
	}

      default:
	{
	  return n > 0x7fff || n < -0x8000 /* short literal operands */ ;
	}
    }				/* end sw */

  }

  return ((!is_o (cnam) && cnam != clear_tag) ||
  /* ignore simple things unless ... */
      (cnam == cont_tag && name (son (c)) == cont_tag &&
	name (son (son (c))) == name_tag)
    );

}
