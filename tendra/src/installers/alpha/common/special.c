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


/* 	$Id: special.c,v 1.1.1.1 1998/01/17 15:56:01 release Exp $	 */

#ifndef lint
static char vcid[] = "$Id: special.c,v 1.1.1.1 1998/01/17 15:56:01 release Exp $";
#endif /* lint */

/*
   special.c
   inlines some of the simpler standard library functions
*/

/*
$Log: special.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:01  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/08/21  08:46:29  john
 * Changed include files
 *
 * Revision 1.2  1995/03/29  14:06:06  john
 * Changes to keep tcheck happy
 *
 * Revision 1.1.1.1  1995/03/23  10:39:22  john
 * Entered into CVS
 *
 * Revision 1.5  1995/03/23  10:14:26  john
 * Minor change
 *
 * Revision 1.4  1995/01/31  14:25:53  john
 * Removed dead variable
 *
*/

#include "config.h"
#include "expmacs.h"
#include "addresstypes.h"
#include "shapemacs.h"
#include "move.h"
#include "pseudo.h"
#include "getregs.h"
#include "guard.h"
#include "code_here.h"
#include "inst_fmt.h"
#include "alpha_ins.h"
#include "labels.h"
#include "tags.h"
#include "procrectypes.h"
#include "bitsmacs.h"
#include "common_types.h"
#include "reg_defs.h"
#include "fail.h"
#include "special.h"


int   specno
    PROTO_N ( (n) )
    PROTO_T ( char *n )
{
	/* these are the procs I could do
				   something about */
  if    (strcmp (n, "strcpy") == 0)
          return - 1;
  if (strcmp (n, "strlen") == 0)
    return 2;
  if (strcmp (n, "strcmp") == 0)
    return - 3;
  return 0;
}

static  needs strcpyneeds = {
  0, 0, 0, 0
};
static  needs strlenneeds = {
  2, 0, uses2_bit, 0
};
static  needs strcmpneeds = {
  2, 0, 0, 0
};

needs specialneeds
    PROTO_N ( (i) )
    PROTO_T ( int i )
{
    /* these are the needs for their expansion */
  switch (i) {
    case 1: 
      return strcpyneeds;
    case 2: 
      return strlenneeds;
    case 3: 
      return strcmpneeds;
    default: 
	failer ("not special fn");
  }
  return strcpyneeds;
}

int   specialfn
    PROTO_N ( (fn) )
    PROTO_T ( exp fn )
{
    /* could I treat this function load specially ? */
  if (name (fn) == name_tag && name (son (fn)) == ident_tag &&
      isglob (son (fn)) && son (son (fn)) == nilexp) {
    char *extname = brog(son (fn)) -> dec_u.dec_val.dec_id;
    return specno (extname);
  }
  return 0;
}


int   specialmake
    PROTO_N ( (n, par, sp, dest, exitlab) )
    PROTO_T ( int n X exp par X space sp X where dest X int exitlab )
{
  switch (n) {
    case  2: 		/* translate strlen in the obvious manner 
				*/
      {
	      where w;
	int   lstart = new_label ();
	int   r;
	int   r1;
	setregalt (w.answhere, AT);
	w.ashwhere = ashof (sh (par));
	code_here (par, sp, w);
	r = (dest.answhere.discrim == inreg) ? regalt (dest.answhere)
	  : getreg (sp.fixed);
	r1 = getreg (guardreg (r, sp).fixed);
	if (r == 0) {
	  r = 2;
	}
	      operate_fmt_immediate(i_addq,AT,1,r);
	      /*rri_ins (i_addq, r, 3, 1);*/
	set_label (lstart);

/*	ls_ins (i_lb, r1, ind3);
	rri_ins (i_add, 3, 3, 1);*/
/*	condr_ins (i_bnez, r1, lstart);

	operate_fmt (i_sub, r, 3, r);
	setregalt (aa, r);
	move (aa, dest, sp, 1);*/
	return exitlab;
      }
    default: 
	failer ("not special");
  }
  return exitlab;
}
