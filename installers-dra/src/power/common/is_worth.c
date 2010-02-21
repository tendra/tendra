/*
    Copyright (c) 1993 Open Software Foundation, Inc.


    All Rights Reserved


    Permission to use, copy, modify, and distribute this software
    and its documentation for any purpose and without fee is hereby
    granted, provided that the above copyright notice appears in all
    copies and that both the copyright notice and this permission
    notice appear in supporting documentation.


    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING
    ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE.


    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
    WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
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



/**********************************************************************
$Author: release $
$Date: 1998/02/04 15:48:52 $
$Revision: 1.2 $
$Log: is_worth.c,v $
 * Revision 1.2  1998/02/04  15:48:52  release
 * Added OSF copyright message.
 *
 * Revision 1.1.1.1  1998/01/17  15:55:57  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1996/10/04  16:01:38  pwe
 * add banners and mod for PWE ownership
 *
**********************************************************************/


#include "config.h"
#include "common_types.h"
#include "tags.h"
#include "expmacs.h"
#include "exp.h"
#include "shapemacs.h"
#include "instruct.h"	/* IMM_SIZE() */
#include "regable.h"
/* construct/is_worth.h defines the interface each installer must implement */
#include "is_worth.h"


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
static bool is_worth_cont_aux PROTO_N ((c)) PROTO_T (exp c)
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
int is_worth PROTO_N ((c)) PROTO_T (exp c) /* used only in mc_list */
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
	return (!IMM_SIZE(n) && (n & (n - 1)) != 0 && (n & (n + 1)) != 0 && ((n - 1) & (n - 2)) != 0);
      }
    case div1_tag:
    case div2_tag:
    case rem2_tag:
      {
	/* a/2^n transformed later to shift */
	return (!IMM_SIZE(n) && (n & (n - 1)) != 0);
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
	    return (!IMM_SIZE(n) && !IMMLOGU_SIZE(n));
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
	return (!IMM_SIZE(n)) /* short literal operands */ ;
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
