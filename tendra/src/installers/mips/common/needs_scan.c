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
$Date: 1998/01/17 15:56:06 $
$Revision: 1.1.1.1 $
$Log: needs_scan.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:06  release
 * First version to be checked into rolling release.
 *
 * Revision 1.20  1996/12/09  12:49:25  currie
 * Large offsets
 *
 * Revision 1.19  1996/12/04  17:54:05  currie
 * result uses2
 *
 * Revision 1.18  1996/06/07  15:22:39  currie
 * procs with struct results in complicated posn
 *
 * Revision 1.17  1996/04/24  08:55:48  currie
 * Case may require 3 regs
 *
 * Revision 1.16  1996/03/14  15:45:02  currie
 * ptr position in apply_general
 *
 * Revision 1.15  1996/02/26  10:29:37  currie
 * shifts with weird params
 *
 * Revision 1.14  1996/01/17  10:25:01  currie
 * tidy transformed idents of idents
 *
 * Revision 1.13  1996/01/12  10:06:12  currie
 * AVS - env_offset + main declared but not d3efined
 *
 * Revision 1.12  1995/11/13  11:53:18  currie
 * prof_tag fix
 *
 * Revision 1.11  1995/10/30  18:26:25  currie
 * AVS err - 2-24-126-127-test05 - too many floats
 *
 * Revision 1.10  1995/09/22  15:49:15  currie
 * added outpar
 *
 * Revision 1.9  1995/09/21  15:42:48  currie
 * silly reordering by as again
 *
 * Revision 1.8  1995/09/12  10:59:37  currie
 * gcc pedanttry
 *
 * Revision 1.7  1995/09/04  10:11:53  currie
 * e changes !
 *
 * Revision 1.6  1995/08/15  09:19:26  currie
 * Dynamic callees + trap_tag
 *
 * Revision 1.5  1995/08/09  10:53:40  currie
 * apply_general bug
 *
 * Revision 1.4  1995/07/03  10:09:29  currie
 * untidy return
 *
 * Revision 1.3  1995/06/28  12:15:23  currie
 * New make_stack_limit etc
 *
 * Revision 1.2  1995/05/05  08:12:58  currie
 * initial_value + signtures
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/******************************************************************

		needs_scan.c

	Defines the scan through a program which reorganises it so that all
arguments of operations are suitable for later code-production. The procedure
scan evaluates the register requirements of an exp. The exps are produced
from the decoding process and the various exp -> exp transformations  in
the proc independent (common to other  translators)

*************************************************************/

#include "config.h"
#include "common_types.h"
#include "exptypes.h"
#include "exp.h"
#include "expmacs.h"
#include "tags.h"
#include "procrectypes.h"
#include "bitsmacs.h"
#include "maxminmacs.h"
#include "regable.h"
#include "tempdecs.h"
#include "shapemacs.h"
#include "special.h"
#include "const.h"
#include "new_tags.h"
#include "flpt.h"
#include "install_fns.h"
#include "externs.h"
#include "extratags.h"
#include "frames.h"
#include "flags.h"
#include "main.h"
#include "basicread.h"
#include "check.h"
#include "me_fns.h"
#include "externs.h"
#include "needs_scan.h"
#include "oddtest.h"

int   maxfix,
      maxfloat;			/* the maximum number of t-regs */
static int   stparam, fixparam, floatparam;
				/* used by scan to set initial parameter
						positions */

extern long notbranch[6];
extern bool do_tlrecursion;

static bool rscope_level = 0;
static bool nonevis = 1;
static int callerfortr;

bool gen_call;


/* declaration of scan.
	 needs is defined in procrectypes.h.
 This is a structure which has two integers giving
the number of fixed and floating point registers required to contain live values
in the expression parameters. A further field prop is used for various
flags about certain forms of exp (mainly idents and procs). The maxargs
field gives the maximum size in bits for the parameters of all the procs
called in the exp. The needs of a proc body are preserved in the needs field
of the procrec (see procrectypes.h).
*/

/***************************************************************
		cca

This procedure effectively inserts a new declaration into an exp. This
is used to stop a procedure requiring more than the available number of
registers.
****************************************************************/

void cca
    PROTO_N ( (to, x) )
    PROTO_T ( exp ** to X exp * x )
{
  if (x == (*to)) {
    exp def = * (x);
    /* replace by  Let tg = def In tg Ni */
    exp id = getexp (sh (def), bro (def), last (def), def, nilexp,
	0, 1, ident_tag);
    exp tg = getexp (sh (def), id, 1, id, nilexp,
	0, 0, name_tag);
    pt (id) = tg;		/* use of tag */
    bro (def) = tg;		/* bro(def) is body of Let = tg */
    clearlast (def);
    * (x) = id;		/* replace pointer to x by Let */
    return;
  }
  else {			/* replace by Let tg = def In ato/def = tg
				   Ni */
    exp def = * (x);
    exp ato = * (*to);
    exp id = getexp (sh (ato), bro (ato), last (ato), def, nilexp,
	0, 1, ident_tag);
    exp tg = getexp (sh (def), bro (def), last (def), id, nilexp,
	0, 0, name_tag);
    pt (id) = tg;		/* use of tg */
    bro (def) = ato;		/* ato is body of Let */
    clearlast (def);
    bro (ato) = id;		/* its father is Let */
    setlast (ato);
    * (*to) = id;		/* replace pointer to 'to' by Let */
    * (x) = tg;		/* replace use of x by tg */
    if (name(def)==ident_tag) {
	tidy_ident(id);
	*to = ptr_position(ato);
	no(id)= 100; /*it has already been scanned */
    }
    else  *to = & bro(son(id));		/* later replacement to same 'to' will be
				   at body of Let */
    return;
  }
}

needs onefix = {
  1, 0, 0, 0
};				/* needs one fix pt reg */
needs twofix = {
  2, 0, 0, 0
};				/* needs 2 fix pt regs */
needs threefix = {
  3, 0, 0, 0
};				/* needs 3 fix pt regs */
needs fourfix = {
  4, 0, 0, 0
};				/* needs 4 fix pt regs */
needs onefloat = {
  0, 1, 0, 0
};				/* needs 1 flt pt regs */
needs zeroneeds = {
  0, 0, 0, 0
};				/* has no needs */

bool subvar_use
    PROTO_N ( (uses) )
    PROTO_T ( exp uses )
{ /* check to see if any uses of id is initialiser to subvar dec */
	for(;uses != nilexp; uses=pt(uses)) {
	     if (last(uses) && name(bro(uses))==cont_tag) {
		exp c = bro(uses);
		if (!last(c) && last(bro(c)) && name(bro(bro(c))) == ident_tag) {
		     exp id = bro(bro(c));
		     if ((props(id) & subvar) != 0 && (props(id) & inanyreg) !=0) return 1;
		}
	     }
	}
	return 0;
}


needs shapeneeds
    PROTO_N ( (s) )
    PROTO_T ( shape s )
{	/* this gives the needs for manipulating a
				   value of shape s */
  if (is_floating (name (s)))
    return onefloat;
  else {
    if (valregable (s))
      return onefix;
    else {			/* if the shape does not fit into a reg,
				   it may need up to four fixed regs for moving
				 */
      int al = shape_align(s);
      if (al == 1) {
	return threefix;
      }
      if (al == 8) {
	if (shape_size(s) < 16 ) return twofix;
	return fourfix;
      }
      else {
	int unitmv = min(al,32);
	if (shape_size(s)/unitmv < inlineassign) {
		return twofix;
	}
	else return fourfix;
      }
    }
  }
}

bool complex
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{		/* these are basically the expressions
				   which cannot be accessed by a simple
				   load or store instruction */
  if (name (e) == name_tag ||
      (name (e) == cont_tag && name (son (e)) == name_tag &&
	isvar (son (son (e))))
      || name (e) == val_tag || name (e) == real_tag || name(e)==null_tag ) {
    return 0;
  }
  else {
    return 1;
  }
}

int scan_cond
    PROTO_N ( (e, outer_id) )
    PROTO_T ( exp * e X exp outer_id )
{

	exp ste = *e;
	exp first = son (ste);
	exp labst = bro (first);
	exp second = bro (son (labst));

	Assert(name(ste)==cond_tag);

	if (name(second)==top_tag && name(sh(first))==bothd && no(son(labst))==1
		&& name(first)==seq_tag && name(bro(son(first))) == goto_tag){
		/* cond is { ... test(L); ? ; goto X | L:make_top}
			if ? empty can replace by seq { ... not-test(X); make_top }
		*/
		exp l = son(son(first));
		while(!last(l)) { l = bro(l); }
		while(name(l)==seq_tag) { l = bro(son(l)); }
		if (name(l)==test_tag && pt(l)==labst) {
		   settest_number(l, notbranch[test_number(l)-1]);
		   pt(l) = pt(bro(son(first)));
		   bro(son(first)) = second;
		   bro(second) = first; setlast(second);
		   bro(first) = bro(ste);
		   if(last(ste)) { setlast(first);} else { clearlast(first); }
		   *e = first;
		   return 1;
		}
		else return 0;
	}


	if (name (first) == seq_tag && name (second) == cond_tag
	    && no(son(labst)) == 1
	    && name (son (son (first))) == test_tag
            && pt (son (son (first))) == labst
	    && name (son (second)) == seq_tag
	    && name (son (son (son (second)))) == test_tag) {
				/* cond is ( seq (test to L;....|
				   L:cond(seq(test;...),...) ) ..... */
	  exp test1 = son (son (first));
	  exp test2 = son (son (son (second)));
	  exp op11 = son(test1);
	  exp op21 = bro(op11);
	  exp op12 = son(test2);
	  exp op22 = bro(op12);
	  bool c1 = complex (op11);
	  bool c2 = complex (op21);

	  if (c1 && eq_exp (op11, op12)) {
				/* ....if first operands of tests are
				   same, identify them */
	    exp newid = getexp (sh (ste), bro (ste), last (ste), op11, nilexp,
		0, 2, ident_tag);
	    exp tg1 = getexp (sh (op11), op21, 0, newid, nilexp, 0, 0, name_tag);
	    exp tg2 = getexp (sh (op12), op22, 0, newid, nilexp, 0, 0, name_tag);

	    pt (newid) = tg1;
	    pt (tg1) = tg2;	/* uses of newid */
	    bro (op11) = ste; clearlast (op11);/* body of newid */
	    /* forget son test2 = son test1 */
	    bro (ste) = newid;
	    setlast (ste);	/* father body = newid */
	    son (test1) = tg1;
	    son (test2) = tg2;	/* relace 1st operands of test */
	    if (!complex(op21) ) {
	        /* if the second operand of 1st test is simple, then identification
			could go in a t-teg (!!!NB overloading of inlined flag!!!).... */
		setinlined(newid);
	    }
	    kill_exp(op12, op12);
	    * (e) = newid;
	    if( scan_cond (&bro(son(labst)), newid) == 2 && complex(op22)) {
		/* ... however a further use of identification means that
		   the second operand of the second test must also be simple */
		clearinlined(newid);
	    }
	    return 1;
	  }
	  else
	  if (c2 && eq_exp (op21, op22)) {
				/* ....if second operands of tests are
				   same, identify them */

	      exp newid = getexp (sh (ste), bro (ste), last (ste), op21,
		  nilexp, 0, 2, ident_tag);
	      exp tg1 = getexp (sh (op21), test1, 1,
		  newid, nilexp, 0, 0, name_tag);
	      exp tg2 = getexp (sh (op22), test2, 1, newid, nilexp,
		  0, 0, name_tag);

	      pt (newid) = tg1;
	      pt (tg1) = tg2;	/* uses of newid */
	      bro (op21) = ste; clearlast (op21);
	      /* body of newid */
	      /* forget bro son test2 = bro son test1 */
	      bro (ste) = newid;
	      setlast (ste);	/* father body = newid */
	      bro (op11) = tg1;
	      bro (op12) = tg2;
              if (!complex(op11) ) { setinlined(newid); }
	      kill_exp(op22, op22);
	      /* relace 2nd operands of test */
	      * (e) = newid;
	      if (scan_cond (&bro(son(labst)), newid) == 2 && complex(op12) ) {
			clearinlined(newid);
	      }
	      return 1;
	  }
	  else
	  if (name (op12) != name_tag
		  && name (op11) == name_tag
		  && son (op11) == outer_id
		  && eq_exp (son (outer_id), op12)
		) {		/* 1st param of test1 is already identified with
				   1st param of  test2 */
		exp tg = getexp (sh (op12), op22, 0, outer_id,
		    pt (outer_id), 0, 0, name_tag);
		pt (outer_id) = tg;
		no (outer_id) += 1;
		if (complex(op21) ){ clearinlined(outer_id); }
		/* update usage of ident */
		son (test2) = tg;
		kill_exp(op12, op12);
		if (scan_cond (&bro(son(labst)), outer_id) == 2 && complex(op22)) {
			clearinlined(outer_id);
		}
		return 2;
	      }


	}
	return 0;
}




needs likeplus
    PROTO_N ( (e, at) )
    PROTO_T ( exp * e X exp ** at )
{
				/* does the scan on commutative and
				   associative operations and may perform
				   various transformations allowed by
				   these properties */
  needs a1;
  needs a2;
  prop pc;
  exp * br  = &son(*e);
  exp prev;
  bool commuted = 0;
  exp dad = * (e);

  a1 = scan (br, at);
  /* scan the first operand - won't be a val_tag */

  do {
    exp * prevbr;
    prevbr = br;
    prev = * (br);
    br = &bro(prev);
    a2 = scan (br, at);
    /* scan the next operand ... */
    if (name (* (br)) != val_tag) {
      a1.floatneeds = max (a1.floatneeds, a2.floatneeds);
      pc = a2.propsneeds & hasproccall;
      if (a2.fixneeds < maxfix && pc == 0) {
				/* ... its evaluation  will not disturb
				 the accumulated result */
        if (a2.fixneeds<=a1.fixneeds || commuted ||
	    a1.fixneeds >= maxfix || (a1.propsneeds & hasproccall) != 0) {
	  a1.fixneeds = max (a1.fixneeds, a2.fixneeds + 1);
	}
	else { /* ... needs more regs so put it first to reduce
			 register usage */
	  exp op1 = son (dad);
	  exp cop = * (br);
	  bool lcop = last (cop);
	  bro (prev) = bro (cop);
	  if (lcop)
	    setlast (prev);
	  bro (cop) = op1;
	  clearlast (cop);
	  son (dad) = cop;
	  br = (prev==op1) ? &bro(cop):prevbr;
	  a1.fixneeds = max (a2.fixneeds, a1.fixneeds + 1);
	}
	a1.propsneeds |= a2.propsneeds;
      }
      else
	if (a1.fixneeds < maxfix &&
	    (a1.propsneeds & hasproccall) == 0 && !commuted) {
				/* ...its evaluation will call a proc, so
				   put it first  */
	  exp dad = * (e);
	  exp op1 = son (dad);
	  exp cop = * (br);
	  bool lcop = last (cop);
	  bro (prev) = bro (cop);
	  if (lcop)
	    setlast (prev);
	  bro (cop) = op1;
	  clearlast (cop);
	  son (dad) = cop;
	  br = (prev==op1) ? &bro(cop):prevbr;
	  commuted = 1;
	  a1.fixneeds = max (a2.fixneeds, a1.fixneeds + 1);
	  a1.propsneeds |= a2.propsneeds;
	  a1.maxargs = max (a1.maxargs, a2.maxargs);
	}

	else {			/* ... its evaluation would disturb
				   accumulated result, so replace it by a
				   newly declared tag */
	  cca (at, br);
	  a1.fixneeds = max (a1.fixneeds, 2);
	  a1.propsneeds = a1.propsneeds | morefix | (pc << 1);
	  a1.maxargs = max (a1.maxargs, a2.maxargs);
	}
    }
  } while (!last (* (br)));
  if (!optop(*(e)) ) {
  	if (a1.fixneeds <4) a1.fixneeds = 4;
  }
  return a1;
}

needs likediv
    PROTO_N ( (e, at) )
    PROTO_T ( exp * e X exp ** at )
{
				/* scan non-commutative fix pt operation
				*/
  needs l;
  needs r;
  prop pc;
  exp * arg = &son(*e);
  l = scan (arg, at);
  /* scan 1st operand */
  arg = &bro(*arg);
  r = scan (arg, at);
  /* scan second operand ... */
  l.floatneeds = max (l.floatneeds, r.floatneeds);
  pc = r.propsneeds & hasproccall;
  if (r.fixneeds < maxfix && pc == 0) {/* ...it fits into registers */
    l.fixneeds = max (l.fixneeds, r.fixneeds + 1);
    l.propsneeds = l.propsneeds | r.propsneeds;
  }
  else {			/* ...it requires new declaration of
				   second operand */
    cca (at, arg);
    l.fixneeds = max (l.fixneeds, 1);
    l.propsneeds = l.propsneeds | morefix | (pc << 1);
    l.maxargs = max (l.maxargs, r.maxargs);
  }

  if ( name(*e) != test_tag &&
     (!optop(*(e)) || name(*e)== div1_tag || name(*e)==mod_tag )) {
  	if (l.fixneeds <4) l.fixneeds = 4;
  }
  return l;
}

needs fpop
    PROTO_N ( (e, at) )
    PROTO_T ( exp * e X exp ** at )
{
				/* scans diadic floating point operation  */
  needs l;
  needs r;
  exp op = *(e);
  prop pcr, pcl;
  exp * arg = &son(op);
  bool withert = !(optop(*e));

  l = scan (arg, at);
  arg = &bro(*arg);
  r = scan (arg, at);
  l.fixneeds = max (l.fixneeds, r.fixneeds);
  pcr = r.propsneeds & hasproccall;
  pcl = l.propsneeds & hasproccall;

  if (r.floatneeds <= l.floatneeds && r.floatneeds < maxfloat && pcr==0) {
	    l.floatneeds = max (2, max (l.floatneeds, r.floatneeds + 1));
	    l.propsneeds = l.propsneeds | r.propsneeds;
	    ClearRev(op);
  }
  else
  if (pcl == 0 && l.floatneeds <= r.floatneeds && l.floatneeds < maxfloat ) {
	    l.floatneeds = max (2, max (r.floatneeds, l.floatneeds + 1));
	    l.propsneeds = l.propsneeds | r.propsneeds;
	    SetRev(op);
  }
  else
  if (r.floatneeds < maxfloat && pcr == 0) {
    l.floatneeds = max (2, max (l.floatneeds, r.floatneeds + 1));
    l.propsneeds = l.propsneeds | r.propsneeds;
    ClearRev(op);
  }
  else {
    cca (at, arg);
    ClearRev(op);
    l.floatneeds = max (l.floatneeds, 2);
    l.propsneeds = l.propsneeds | morefloat | (pcr << 1);
    l.maxargs = max (l.maxargs, r.maxargs);
  }
  if (withert && l.fixneeds < 2) l.fixneeds = 2;
  return l;
}

/**********************************************************************
	maxneeds

Calculates a needs value. Each element of which is the maximum of the
corresponding elements in the two parameter needs
**********************************************************************/

needs maxneeds
    PROTO_N ( (a, b) )
    PROTO_T ( needs a X needs b )
{
  needs an;
  an.fixneeds = max (a.fixneeds, b.fixneeds);
  an.floatneeds = max (a.floatneeds, b.floatneeds);
  an.maxargs = max (a.maxargs, b.maxargs);
  an.propsneeds = a.propsneeds | b.propsneeds;
  return an;
}

/**********************************************************************
	maxsequence

**********************************************************************/

needs maxtup
    PROTO_N ( (e, at) )
    PROTO_T ( exp e X exp ** at )
{	/* calculates the needs of a tuple of
				   expressions; any new declarations
				   required by a component expression will
				   replace the component expression */
  exp * stat = &son(e);
  needs an;

  an = zeroneeds;
  if (*stat == nilexp) return an;
  while (an = maxneeds (an, scan (stat, at)), !last(*stat) ) {
    stat = &bro(*stat);
  }
  return an;
}

bool unchanged
    PROTO_N ( (usedname, ident) )
    PROTO_T ( exp usedname X exp ident )
{
				/* finds if usedname is only used in cont
				   operation or as result of ident i.e.
				   value of name is unchanged over its
				   scope */
  exp uses = pt (usedname);
  while (uses != nilexp) {
    if (intnl_to (ident, uses)) {
      if (!last (uses) || name (bro (uses)) != cont_tag) {
	exp z = uses;
	while (z != ident) {
	  if (!last (z) ||
	      (name (bro (z)) != seq_tag && name (bro (z)) != ident_tag)) {
	    return 0;
	  }
	  z = bro (z);
	}
      }
    }
    uses = pt (uses);
  }
  return 1;
}



exp absbool
    PROTO_N ( (id) )
    PROTO_T ( exp id /* declaration */ )
{			/* check if e  is (let a = 0 in
                               cond(inttest(L)=result; a=1 | L:top); a
                               ni ) This will be compiled later using
                               set instructions instead of branches */
  if (isvar (id) && name (son (id)) == val_tag && no (son (id)) == 0
      && no (id) == 2 /* name initially 0 only used twice */ ) {
    exp bdy = bro (son (id));
    if (name (bdy) == seq_tag && name (bro (son (bdy))) == cont_tag &&
	name (son (bro (son (bdy)))) == name_tag &&
	son (son (bro (son (bdy)))) == id
	 /* one use is result  of sequence body */ ) {
      exp c = son (son (bdy));
      if (last (c) && name (c) == cond_tag /* seq is cond=c; id */ ) {
	exp first = son (c);
	exp second = bro (son (c));
	if (no (son (second)) == 1 /* only one jump to else */ &&
	    name (bro (son (second))) == top_tag
	    && name (first) == seq_tag /* cond is (seq= first | L: top) */ ) {
	  exp s = son (son (first));
	  exp r = bro (son (first));
	  if (name (r) == ass_tag && name (son (r)) == name_tag &&
	      son (son (r)) == id && name (bro (son (r))) == val_tag &&
	      no (bro (son (r))) == 1 /* last of seq is id = 1 */ &&
	      last (s) && name (s) == test_tag && pt (s) == second
	      && !is_floating (name (sh (son (s))))
				/**t of seq is int test jumping to
				   second */
	    ) {
	    return s;
	  }
	}

      }

    }


  }
  return 0;
}

exp * ptr_position
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
	exp * a;
	exp dad = father(e);
	if (son(dad)==e) {
		a = &son(dad);
	}
	else {
		exp sib = son(dad);
		while (bro(sib)!=e) { sib = bro(sib); }
		a = &bro(sib);
	}
	return a;
}

void change_to_var
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{	/* change identity to variable definition */
	exp p = pt(e);
	shape ns;
	Assert(name(e)==ident_tag && !isvar(e));
	setvar(e);
	setcaonly(e);
	ns = f_pointer(f_alignment(sh(son(e))));
	while (p != nilexp) {
		exp * pos = ptr_position(p);
		exp ncont = getexp(sh(p), bro(p), last(p), p, nilexp, 0, 0,
					cont_tag);
		bro(p) = ncont; setlast(p);
		sh(p) = ns;
		*pos = ncont;
		p = pt(p);
	}
}

void change_names
    PROTO_N ( (f, t, except) )
    PROTO_T ( exp f X exp t X exp except )
{	/* replace uses of ident f (!= except) to uses of t */
	exp py = pt(f);
	Assert(name(f)==ident_tag && name(t)==ident_tag && name(except)==name_tag);
	while (py != nilexp) {
		exp ppy = pt(py);
		if (py != except) {
			son(py) = t; /* change f to t */
			pt(py) = pt(t);
			pt(t) = py;
			no(t)++;  /* maintain usage */
		}
		py = ppy;
	}
}


void tidy_ident
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
	/* replace Var/Id x = Var y = e1 in { e2; contents(y)} in e3;
	   by Var x = e1 in { e2/(y=>x); e3}
	   replace Var/Id x = Id y = e1 in {e2; y} in e3
           by Var/Id x = e1 in { e2/y=>(cont)x; e3}
	*/
	exp init; exp bdyinit; exp idy;
	exp e1;
	exp e3;
	Assert(name(e)==ident_tag);
	init = son(e);
	e3 = bro(init);
	if ( name(init) != ident_tag || isparam(e)) { return ;}
	tidy_ident(init);
	e1 = son(init);
	bdyinit = bro(e1);
	if (!isvar(init)) {
	  if (name(bdyinit) == seq_tag) {
	    	exp idy = bro(son(bdyinit));
		exp broe3;
		bool laste3;
		if (name(idy) != name_tag || son(idy) != init ||
			no(idy) !=0 ||
			shape_size(sh(idy)) != shape_size(sh(e1)) ||
			shape_align(sh(idy)) != shape_align(sh(e1)) ) {
		    return;
		}
		if (isvar(e)) {
			change_to_var(init);
		}
		change_names(init, e, idy);

		broe3 = bro(e3);
		laste3 = last(e3);
		bro(son(bdyinit)) = e3;
		bro(e3) = bdyinit; setlast(bdyinit);
				/* bdyinit is now { e2/(y=>x); e3} */
		bro(bdyinit) = broe3;
		if (laste3) { setlast(bdyinit); }
		else { clearlast(bdyinit); }
		son(e) = e1;  /* bro(e1) is bdyinit */
		return;
	  }
	  else
	  if (name(bdyinit)== name_tag && (idy = son(bdyinit))==init
		&& no(bdyinit)==0 &&
		shape_size(sh(idy)) == shape_size(sh(e1)) &&
		shape_align(sh(idy)) == shape_align(sh(e1)) ) {
		/* form is Var/Id x = Id y = e1 in y in e3
			=> Var x = e1 in e3 */
		bro(e1) = e3;
		son(e) = e1;
	  }
	  else return;
	}
	else {
	  if (name(bdyinit) == seq_tag) {
		exp cy = bro(son(bdyinit));
		exp broe3;
		bool laste3;
		if (name(cy) != cont_tag) return;

		idy = son(cy);
		if (name(idy) != name_tag || no(idy) != 0 ||
			son(idy) != init ||
			shape_size(sh(cy)) != shape_size(sh(e1)) ||
			shape_align(sh(cy)) != shape_align(sh(e1)) ) {
			return;
		}
		if (!isvar(e)) {
			change_to_var(e);
			e3 = bro(init);
			if (isvis(init)) { setvis(e); }
			if (!iscaonly(init)) { ClearCaonly(e); }
		}

		change_names(init,e,idy);

		broe3 = bro(e3);
		laste3 = last(e3);
		bro(son(bdyinit)) = e3;
		bro(e3) = bdyinit; setlast(bdyinit);
				/* bdyinit is now { e2/(y=>x); e3} */
		bro(bdyinit) = broe3;
		if (laste3) { setlast(bdyinit); }
		else { clearlast(bdyinit); }
		son(e) = e1;  /* bro(e1) is bdyinit */
		return;
	  }
	  else
	  if (name(bdyinit) == cont_tag) {
		exp cy =  bro(son(bdyinit));
		idy = son(cy);
		if (name(idy) != name_tag || no(idy) != 0 ||
			son(idy) != init ||
			shape_size(sh(cy)) != shape_size(sh(e1)) ||
			shape_align(sh(cy)) != shape_align(sh(e1)) ) {
			return;
		}
		/* form is Var x = Var y = e1 in cont(y) in e3
			=> Var x = e1 in e3 */
		if (!isvar(e)) {
			change_to_var(e);
			e3 = bro(init);
			if (isvis(init)) { setvis(e); }
			if (!iscaonly(init)) { ClearCaonly(e); }
		}
		bro(e1) = e3;
		son(e) = e1;
	  }
	  else return;
	}

}


bool chase
    PROTO_N ( (sel, e) )
    PROTO_T ( exp sel X exp * e )
{
	/* distribute selection throughout compound expressions */
      bool b = 0;
      exp * one;
      switch(name(*e)) {
    	case ident_tag:
    	case seq_tag:
    	case rep_tag:
    	case labst_tag: {
    	  b = chase(sel, &bro(son(*e)));
    	  break;
    	}
    	case solve_tag:
    	case cond_tag: {
    	  one = &son(*e);
    	  for(;;)  {
    	    b |= chase(sel, one);
    	    if (last(*one)) break;
    	    one = &bro(*one);
    	  }
    	  break;
    	}
    	case field_tag: {
    	  if (chase(*e, &son(*e))) {
    	  	/* inner field has been distributed */
    	  	exp stare = *e;
    	  	exp ss = son(stare);
    	  	if (!last (stare)) clearlast (ss);
	  	bro (ss) = bro (stare);
	  	sh (ss) = sh (stare);
	  	*e = ss;
	  	return chase(sel, e);
	  } /* ... continue to default */
	}
    	default: {
    	  if (son(sel)!= *e && name(sh(*e)) != bothd) {
		/* only change if not outer */
    	    exp stare = *e;
	    exp newsel = getexp (sh (sel), bro (stare), last (stare), stare, nilexp,
	      		props (sel), no (sel), name (sel));
	    *e =  newsel;
	    bro(stare)=newsel;  setlast(stare);
	    b = 1;
	  }
	}
      }
      if (b) sh(*e) = sh(sel);
      return b;
}

bool use_not_rep
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
	exp u ;
	if (no(e) !=1) return 0;
	u = father(pt(e));
	while (u != e) {
		if (name(u) == rep_tag || name(u) == solve_tag) {
			return 0;
		}
		else { u = father(u); }
	}
	return 1;
}

/********************************************************************
		scan

    This procedure works out register requirements of an exp. At each call
    the fix field of the needs is the number of fixpnt registers required to
    contain live values to evaluate this expression. This never exceeds
    maxfix because if it would have, a new declaration is introduced in the
    exp tree (similarly for floating regs and maxfloat). In these cases the
    prop field will contain the bits morefix (or morefloat).

    Scan also works out various things concerned with proc calls.  The
    maxargs field contains the max size in bits of the space required for
    the parameters of all the procedures called in the exp. An exp proc call
    produces a hasproccall bit in the prop field, if this is transformed as
    part of the definition of a new declaration the bit is replaced by a
    usesproccall. The distinction is only used in unfolding nested proc
    calls; MIPS requires this to be done statically. The condition that a
    proc exp is a leaf (i.e no proc calls) is that its prop contains neither
    bit.

    If an ident exp is suitable, scan marks the props of ident with
    either inreg or infreg bits to indicate that a t reg may be used for
    this tag.

    A thorough understanding of needs along with other procedures
    that do switch(name(exp)) requires a knowledge of the meaning of the
    fields of the exp in each case.

********************************************************************/


needs scan
    PROTO_N ( (e, at) )
    PROTO_T ( exp * e X exp ** at )
{
				/*  e is the expression to be scanned, at
				   is the place to put any new decs . NB order of recursive
				   calls with same at is critical */
  exp   ste = * (e);
  int   nstare = name (ste);

/*  while
    (nstare == diag_tag || nstare == cscope_tag || nstare == fscope_tag) {
    e = &son(ste);
    ste = * (e);
    nstare = name (ste);
  }
*/





  switch (nstare) {
    case 0: {
	return zeroneeds;
      };



    case compound_tag: case nof_tag:  case concatnof_tag: case ncopies_tag:
      {
	needs nl;
	bool cantdo;
	exp dad;
	if (name(ste)==ncopies_tag && name(son(ste)) !=name_tag
		&& name(son(ste)) != val_tag ) {
	    nl = scan(&son(*e), at);
	    cca(at, &son(*e));
	}
	else nl = maxtup(*(e), at);

	dad = father(ste);
	if (name(dad)==compound_tag || name(dad) == nof_tag
				|| name(dad) == concatnof_tag) {
		cantdo=0;
	}
	else
	if (last(ste) ){
		if (name(bro(ste)) == ass_tag ) {
			exp a = son(bro(ste));
			cantdo = (name(a) != name_tag || !isvar(son(a)) );
		}
		else cantdo = 1;
	}
	else
	if (last(bro(ste)) ) { cantdo = (name(bro(bro(ste))) != ident_tag) ;}
	else cantdo = 1;


	if (cantdo)  {
		/* can only deal with tuples in simple assignment or identity */
		int prps = (nl.propsneeds & hasproccall) << 1;
		cca(at, ptr_position(ste));
		nl = shapeneeds(sh(*(e)));
		nl.propsneeds |= morefix;
	      	nl.propsneeds |= prps;
	}

	if (nl.fixneeds <2) nl.fixneeds = 2;
	return nl;
      };



    case cond_tag:
      {
	exp t, f, v;


	if (oddtest(ste, & t, &f, &v) ) {
		/* transform to f((absbool(t) <<1)-1)  */
		exp bc = bro(ste);
		bool lc = last(ste);
		exp ab = getexp(sh(v), nilexp, 0, t, nilexp, 0, 0, absbool_tag);
		exp shl = getexp(sh(v), nilexp, 0, ab, nilexp, 0, 0, shl_tag);
		exp v1 = getexp(sh(v), shl, 1, nilexp,nilexp, 0, 1, val_tag);
		exp p = getexp(sh(v), nilexp, 1, shl, nilexp, 0, 0, plus_tag);
		exp vm1 = getexp(sh(v), p, 1, nilexp,nilexp, 0, -1, val_tag);
		bro(ab) = v1;
		bro(shl) = vm1;
		bro(t) = ab; setlast(t);
		if (no(v)==-1) {settest_number(t, notbranch[test_number(t)-1]);}
		if (f==v) {
			*e = p;
		}
		else {
			son(bro(v)) = p;
			bro(p) = bro(v);
			*e = f;
		}
		bro(*e) = bc; if (lc) { setlast(*e); } else {clearlast(*e); }
		return scan(e, at);
	}

	if (is_maxlike(ste, &t) ) {
		son(ste) = t;
		bro(t) = ste; setlast(t);
		setname(ste, maxlike_tag);
		return scan(&son(ste), at);
	}
	if (is_minlike(ste, &t) ) {
		son(ste) = t;
		bro(t) = ste; setlast(t);
		setname(ste, minlike_tag);
		return scan(&son(ste), at);
	}
	if (is_abslike(ste, &t) ) {
		son(ste) = t;
		bro(t) = ste; setlast(t);
		setname(ste, abslike_tag);
		return scan(&son(ste), at);
	}
	if (is_fabs(ste, &t) ) {
		son(ste) = son(t);
		bro(son(t)) = ste; setlast(son(t));
		setname(ste, fabs_tag);
		return scan(&son(ste), at);
	}

	if (scan_cond(e, nilexp) !=0) {
		return scan(e, at);
	}			/* else goto next case */
      }



    case labst_tag:
    case rep_tag:
    case solve_tag:
      {
	exp * stat;
	exp * statat;
	needs an;
	stat = &son(*e);
	statat = stat;
	an = zeroneeds;
	while (an = maxneeds (an, scan (stat, &statat)),

	    !last (* (stat))) {
	  stat = &bro(*stat);
	  statat = stat;
	}
	if ((an.propsneeds & usesproccall) != 0) {
	  an.propsneeds |= hasproccall;
	}
	return an;
      }

/*********************************************************************
	ident

shape of exp is body,
son is def, brother of son is body,
ptr of ident exp is chain of uses
*********************************************************************/

    case ident_tag:
      { tidy_ident(*e); /* remove nugatory idents in initialisation */
      }
      {

	  needs bdy;
	  needs def;
	  exp stare = * (e);
	  exp * arg = &bro(son(stare));
	  exp t = pt (stare), s;
	  bool fxregble;
	  bool flregble;
	  bool old_nonevis = nonevis;
	  exp ab;

	  if (isvar(stare) && !iscaonly(stare)) setvis(stare);




          if (!isvar (stare)  && !isvis(stare) && !isparam(stare)
	        && ((props(stare) & 0x10) !=0)
		&& use_not_rep(stare) ) {
		/* remove declaration */
		/*only one use */
		exp u = pt(stare);
		exp init = son(stare);
		exp bdy = bro(init);
		exp * posu = ptr_position(u);
		bro(init) = bro(u);
		if(last(u)) { setlast(init);} else {clearlast(init); }
		*posu = init;
		bro(bdy)= bro(stare);
		if (last(stare)) { setlast(bdy);} else { clearlast(bdy); }
		*e = bdy;
		return scan(e, at);
	  }


	  if (isparam(stare)
		&& name(son(stare))!= formal_callee_tag) {
	  	exp def = son(stare);
	  	shape shdef = sh(def);
	  	long n = rounder(stparam, shape_align(shdef));
	  	long sizep = shape_size(shdef);

	  	Assert(name(def)==clear_tag);
		if (is_floating(name(shdef)) ) {
			if (n + sizep <= 128 ) {
				props(def) = floatparam++;
				maxfloat--;
			}
		}
		else
		if (sizep<=32  && stparam <=96  ) {
			props(def) = fixparam;
			maxfix--;
		}
		else props(def)=0;
		if (BIGEND && sizep <32 && valregable(shdef)) {
			/* characters are promoted to ints */
		     	int dn = (sizep==8)?24:16;
			exp pu = pt(stare);
			while (pu != nilexp) {
				no(pu)+= dn;
				pu = pt(pu);
			}
		}
		no(def) = n;
		stparam = rounder(n+sizep, 32 );
		fixparam = 4 +(stparam>>5);


		if (!is_floating(name(shdef)) && !valregable(shdef))
				 setvis(stare);
		/* now props(def) = pos parreg and no(def) = par stack address
		*/
	  }
	  else
	  if (isparam(stare) && name(son(stare))== formal_callee_tag) {
	  	exp def = son(stare);
	  	shape shdef = sh(def);
	  	long sizep = shape_size(shdef);
	  	long alp = shape_align(shdef);
	  	long n = rounder(callee_size, alp);
	  	no(def) = n;
	  	callee_size = rounder(n+sizep, 32);

	  }
	  nonevis &= !isvis(stare);

	  bdy = scan (arg, &arg);
	  /* scan the body-scope */
	  arg = &son(stare);
	  def = scan (arg, &arg);
	  /* scan the initialisation of tag */

	  nonevis = old_nonevis;
	  t = son (stare);
	  s = bro (t);
	  fxregble = fixregable (stare);
	  flregble = floatregable (stare);

	  if (isparam(stare) ) {
	    if (!isvis(stare) && !isoutpar(stare)
		       && name(son(stare)) != formal_callee_tag &&
	          (bdy.propsneeds & anyproccall)==0   ) {
	          /* leave pars in par regs or put in t-regs
	             !! WHAT ABOUT TEMP DECS !!
	          */
	    	int x = props(son(stare));
	    	if (x != 0) {
	    	  no(stare)= x;
	    	  if (flregble) { props(stare)|= infreg_bits; }
	    	  else { props(stare) |= inreg_bits; }
	    	}
	    	else
	    	if (fxregble &&
	    	     bdy.fixneeds < maxfix && (bdy.propsneeds & morefix) == 0 ){
	    	  no(stare) = 0;
	    	  props(stare) |= inreg_bits;
	    	  bdy.fixneeds+=1;
	    	}
	    	else
	    	if (flregble &&
	    		bdy.floatneeds < maxfloat &&
	    		(bdy.propsneeds & morefloat) == 0 ) {
	    	  no(stare) = 0;
	    	  props(stare) |= infreg_bits;
	    	  bdy.floatneeds +=1;
	    	}
	    	else no(stare) = 100;
	    }
	    else no(stare) = 100;

	  }
	  else {
            if ((ab = absbool (stare)) != nilexp) {
                                  /* form is (let a = 0 in cond(test(L)=ab;
                                     a=1 | L:top) ni replace declaration by
                                     ABS */
              bro (ab) = stare;
              setlast (ab);       /* father => *e */
              son (stare) = ab;
              pt (stare) = nilexp;
              pt (ab) = nilexp;
              setname (stare, absbool_tag);
              return maxneeds (bdy, def);
            }

            if (!isvis (*e) && !isparam(*e) &&
                  (bdy.propsneeds & (anyproccall | uses2_bit)) == 0
                  && (fxregble || flregble) &&
                (name (t) == apply_tag ||
                  (name (s) == seq_tag && name (bro (son (s))) == res_tag &&
                    name (son (bro (son (s)))) == cont_tag && isvar (stare) &&
                    name (son (son (bro (son (s))))) == name_tag &&
                    son (son (son (bro (son (s))))) == stare
                  )               /* Let a := ..; return cont a */
                )
              ) {                 /* put tag in result reg if definition is
                                     call of proc, or body ends with return
                                     tag, provided result is not used other
                                     wise */
              props (stare) |= (fxregble) ? inreg_bits : infreg_bits;
              bdy.propsneeds |= uses2_bit;
              no (stare) = 101;   /* identification  uses result reg in body
                                  */
	      if (fxregble) bdy.fixneeds+=1;
            }

            else
	    if (!isvar (*e) && !isparam(*e) &&
		((name (t) == reff_tag && name (son (t)) == cont_tag &&
		    name (son (son (t))) == name_tag && isvar (son (son (son (t))))
		    && !isvis (son (son (son (t)))) && !isglob (son (son (son (t))))
		    && unchanged (son (son (son (t))), stare)
				/* reff cont variable-not assigned to in
				   scope */
		  ) ||
		  (name (t) == cont_tag && name (son (t)) == name_tag &&
		    isvar (son (son (t))) && !isvis (son (son (t))) && !isglob (son (son (t)))
		    && unchanged (son (son (t)), stare)
				/* cont variable - not assigned to in
				   scope */
		  )
		)
	      ) {
	      props (stare) |= defer_bit;
				/* dont take space for this dec */
	    }
	    else
	    if (!isvar (stare)  && !isvis(stare) &&
              ((props (stare) & 0x10 /* forced in const */ ) == 0
                && (name (t) == name_tag || name (t) == val_tag ))) {
              props (stare) |= defer_bit;
                              /* dont take space for this dec */
            }
            else
            if ( fxregble && bdy.fixneeds < maxfix
                 && ( isinlined(stare) ||
		 ((bdy.propsneeds & morefix) == 0 &&
                 ((bdy.propsneeds & anyproccall) == 0
                  || tempdec (stare, ((bdy.propsneeds & morefix) == 0 &&
                      bdy.fixneeds < 10)))
		) ) ) {
                            /* put this tag in some  fixpt t-reg -
                               which will be decided  in make_code */
              props (stare) |= inreg_bits;
              no (stare) = 0;
              bdy.fixneeds += 1;
            }
            else
            if ( flregble && bdy.floatneeds < maxfloat
                 && ( isinlined(stare) ||
		((bdy.propsneeds & morefloat) == 0
                 && ((bdy.propsneeds & anyproccall) == 0
                  || tempdec (stare, ((bdy.propsneeds & morefloat) == 0 &&
                      bdy.floatneeds < 6)))
		) ) ) {
                          /* put this tag in some  float t-reg -
                             which will be decided  in make_code */
              props (stare) |= infreg_bits;
              no (stare) = 0;
              bdy.floatneeds += 1;
            }
            else {
	      if (fxregble && (bdy.propsneeds & anyproccall) == 0) {
			SetPossParReg(stare);
	      }
              no (stare) = 100;
                          /* allocate either on stack or saved reg
                          */
            }
	  }
	  bdy = maxneeds (bdy, def);
	  if ((bdy.propsneeds & usesproccall) != 0) {
	    bdy.propsneeds |= hasproccall;
	  }
	  return bdy;
	}

/*********************************************************************
	sequence

shape of exp is shape of end of sequence
son is sequence holder, son of this is list of voided statements.
*********************************************************************/

    case seq_tag:
      {
	exp * arg = &bro(son(*e));
	needs an;
	exp * stat;
	exp * atsc = &son(son(*e));
	for(;;) {
		exp sc = *atsc;
		if (name(sc) == cond_tag && name(sh(son(sc)))==bothd
			&& name(bro(son(bro(son(sc))))) == top_tag) {
			/* sc is cond(... goto | make_top); can replace
				make_top by next exp in sequence */
		   exp lbst = bro(son(sc));
		   exp mkt = bro(son(lbst));
		   exp ne = (last(sc))? bro(son(*e)): bro(sc);
		   exp bne = bro(ne);
		   bool lne = last(ne);
		   if (name(ne) != cond_tag ) {
			/* only worthwhile eliding if ne is a cond */
			if (last(sc)) break;
			atsc = &bro(sc);
			continue;
		   }
		   sh(sc) = sh(ne);
		   bro(ne) = lbst; setlast(ne);
		   bro(son(lbst)) = ne;
			/* sc is now cond( ... goto | next cond exp) */
		   if (!last(sc)) { /* not last in seq - swallow next*/
			bro(sc) = bne;
			if (lne) { setlast(sc); } else { clearlast(sc);}
			no(son(*e))--; /* one less statement */
		   }
		   else
		   if (no(son(*e)) != 1) { /* last but not only - replace by
					make_top and put cond in res posn */
			bro(mkt) = bro(sc); setlast(mkt);
			*atsc = mkt;
			bro(sc) = bne;
			if (lne) { setlast(sc); } else { clearlast(sc);}
			*arg = sc;
			sc = mkt;
		   }
		   else { /* whole sequence can be replace by cond */
			bro(sc) = bro(*e);
			if (last(*e)) { setlast(sc); } else {clearlast(sc); }
			*e = sc;
			return scan(e, at);
		   }

		}
		if (last(sc)) break;
		atsc = &bro(sc);
	}


	an = scan (arg, &arg);
	stat = &son(son(*e));

	arg = stat;
	for (;;) {
	  needs stneeds;
	  stneeds = scan (stat, &arg);
				/* initial statements voided */
	  an = maxneeds (an, stneeds);
	  if (last (* (stat))) {
	    if ((an.propsneeds & usesproccall) != 0) {
	      an.propsneeds |= hasproccall;
	    }
	    return an;
	  }
	  stat = &bro(*stat);
	  arg = stat;
	}

      };

/********************************************************************
	goto

shape is bottom
son is exp for value jumped with
ptr is labelled exp
*********************************************************************/

    case goto_tag: case trap_tag:
      {
	return zeroneeds;
      };

    case ass_tag:
    case assvol_tag:
      {
	exp * lhs = &son(*e);
	exp * rhs = &bro(*lhs);
	needs nr;
	ash a;

	nr = scan (rhs, at);
	/* scan source */

	a = ashof (sh (* (rhs)));

	if (name (* (lhs)) == name_tag && (no(*lhs) < 8*32768 && no(*lhs) >= -8*32768) &&
	    (isvar (son (* (lhs))) &&  /* can do better for regable rhs*/
	      ((nr.propsneeds & (hasproccall | morefix)) == 0
		&& nr.fixneeds < maxfix
	      )
	    )
	  ) {			/* simple destination */
	  return nr;
	}
	else {
	  needs nl;
	  prop prps = (nr.propsneeds & hasproccall) << 1;
	  nl = scan (lhs, at);
	  /* scan destination */
	  if (name (* (rhs)) == apply_tag && nstare == ass_tag &&
	      (nl.propsneeds & (uses2_bit | anyproccall)) == 0) {
				/* source is proc call, so assign result
				   reg directly */
	    ;
	  }
	  else
	    if (nr.fixneeds >= maxfix || prps != 0) {
				/* source and destination regs overlap, so
				   identify source */
	      cca (at, rhs);
	      nl = shapeneeds (sh (* (rhs)));
	      nl.propsneeds |= morefix;
	      nl.propsneeds &= ~(prps >> 1);
	      nl.propsneeds |= prps;
	    }
	  nr.fixneeds += 1;
	  return maxneeds (nl, nr);
	}
      };

    case res_tag: case untidy_return_tag:
      {
	ash a;
	needs x;
	shape s;
	exp * arg = &son(*e);
	exp r, ss, t;
	s = sh (* (arg));
	a = ashof (s);
	props(*e) = 0; /* clear possibility of tlrecirsion; may be set later */
	x = scan (arg, at);
	/* scan result exp ... */
	if (is_floating (name (s))) {/* ... floating pt result */
	  x.propsneeds |= realresult_bit;
	  if (name (s) != shrealhd) {
	    x.propsneeds |= longrealresult_bit;
	  }
	}
	else {
	  if (!valregable (s)) {/* .... result does not fit into reg */
	    x.propsneeds |= long_result_bit;
	  }
	}
	if (a.ashsize != 0) {	/* ...not a void result */
	  x.propsneeds |= has_result_bit;
	}


	return x;
      };

    case apply_general_tag: {
	exp application = *(e);
	exp *fn = &son (application);
	exp cers = bro(*fn);
	exp *cerl = &son(cers);
	long stpar = 0;

	needs nds;
	needs plnds;
	int i;

	gen_call = 1;

	nds = scan(fn, at);
	if ((nds.propsneeds & hasproccall) != 0) {
				/* .... it must be identified */
	  cca (at, fn);
	  nds.propsneeds &= ~hasproccall;
	  nds.propsneeds |= usesproccall;
	  fn = &son(application);
	}

	for(i=0; i<no(cers); i++) {
		needs onepar;
		shape shonepar = sh(*cerl);
		exp * par = (name(*cerl)==caller_tag)?&son(*cerl):cerl;
		int n = rounder(stpar, shape_align(shonepar));
		onepar = scan(par,at);
	    	if ((i != 0 && (onepar.propsneeds & hasproccall) != 0) ||
	  		onepar.fixneeds+(stpar>>5) > maxfix) {
				/* if it isn't the first parameter, and it
				   calls a proc, identify it */
	    	  cca (at, par);
	    	  nds.propsneeds |= usesproccall;
	    	  nds = maxneeds (shapeneeds (sh (* (par))), nds);
	    	  nds.maxargs = max (nds.maxargs, onepar.maxargs);
	  	}
	  	else {
	  	  nds = maxneeds (onepar, nds);
	  	}
	  	if (name(*cerl)==caller_tag) { no(*cerl) = n; };
	  	n = n + shape_size(shonepar);
	  	stpar = rounder(n,32);
	  	cerl = &bro(*cerl);
	}
	nds.maxargs = max (nds.maxargs, stpar);
	nds = maxneeds(scan(&bro(bro(son(application))), at), nds);

	plnds = scan(&bro(bro(bro(son(application)))), at);




	if ((plnds.propsneeds & (anyproccall | uses2_bit)) != 0) {
		props(application) = 1;
		if (is_floating(name(sh(application)))
			|| valregable(sh(application))) {
			cca(at, ptr_position(application));
			plnds.propsneeds |= usesproccall;
		}
	}
	else { props(application) = 0; }

	nds = maxneeds(nds, plnds);
	nds.propsneeds |= hasproccall;
	return nds;
	}

   case make_callee_list_tag: {
   	exp cees = *e;
	exp * par = &son(cees);
	needs nds;
	long stpar = 0;
	int i;
	nds = zeroneeds;
	for(i=0; i<no(cees); i++) {
		needs onepar;
		shape shonepar = sh(*par);
		int n = rounder(stpar, shape_align(shonepar));
		onepar = scan(par,at);
	    	if (((onepar.propsneeds & hasproccall) != 0) ||
	  		onepar.fixneeds+1 > maxfix) {
				/* if it calls a proc, identify it */
	    	   cca (at, par);
	    	   nds.propsneeds |= usesproccall;
	    	   nds = maxneeds (shapeneeds (sh (* (par))), nds);
	    	   nds.maxargs = max (nds.maxargs, onepar.maxargs);
	  	}
	  	else {
	  	  nds = maxneeds (onepar, nds);
	  	}
	  	n = n + shape_size(shonepar);
	  	stpar = rounder(n,32);
	  	par = &bro(*par);
	  }
	no(cees) = stpar;
	return nds;
   }
   case make_dynamic_callee_tag: {
	exp cees = *e;
	exp *ptr = &son(cees);
	needs ndsp;
	needs nds;
	nds = zeroneeds;
	ndsp = scan(ptr, at);
	if (((ndsp.propsneeds & hasproccall) != 0) ||
	  		ndsp.fixneeds+1 > maxfix) {
	    	 cca (at, ptr);
	    	 nds.propsneeds |= usesproccall;
	    	 nds = maxneeds (shapeneeds (sh (* (ptr))), nds);
	    	 nds.maxargs =  max(nds.maxargs, ndsp.maxargs);
	}
	else {
	  	nds = ndsp;
	}
	ndsp = scan(&bro(son(*e)), at);
	if (((ndsp.propsneeds & hasproccall) != 0) ||
	  		ndsp.fixneeds+2 > maxfix) {
	    	 cca (at, &bro(son(cees)));
	    	 nds.propsneeds |= usesproccall;
	    	 nds = maxneeds (shapeneeds (sh (bro(son(*e)))), nds);
	    	 nds.maxargs = max (nds.maxargs, ndsp.maxargs);
	}
	else {
	  	nds = maxneeds (ndsp, nds);
	}
        if (nds.fixneeds<8) nds.fixneeds = 8;
        return nds;
    }

    case same_callees_tag: {
    	needs nds;
    	nds = zeroneeds;
    	nds.fixneeds = 6;
    	return nds;
    }

    case tail_call_tag: {
	needs ndsp;
	needs nds;
	exp *fn = &son(*e);
	ndsp =  scan(fn, at);
	if (((ndsp.propsneeds & hasproccall) != 0) ||
	  		ndsp.fixneeds+1 > maxfix) {
	    	 cca (at, fn);
	    	 nds.propsneeds |= usesproccall;
	    	 nds = maxneeds (shapeneeds (sh (* (fn))), nds);
	    	 nds.maxargs =  max(nds.maxargs, ndsp.maxargs);
	}
	else {
	  	nds = ndsp;
	}
	gen_call = 1;

	ndsp = scan(&bro(son(*e)), at);
	nds = maxneeds(nds, ndsp);
	if (nds.fixneeds < 5) nds.fixneeds = 5;
	return nds;
   }




    case apply_tag:
      {
	exp application = *(e);
	exp fn = son (application);
	exp * par = &bro(fn);
	exp * fnexp = &son(*e);
	int   parsize =0;
	needs nds;
	bool tlrecpos = nonevis && callerfortr && (rscope_level == 0);
	int   i;

	if (BIGEND && !last(fn)) {
		/* ABI says that all int pars <32 bits are promoted to int*/
	    for(;;) {
		shape s = sh(*par);
		if (shape_size(s) < 32 && valregable(s)) {
		  exp cv = getexp((is_signed(s))?slongsh:ulongsh, bro(*par),
				last(*par), *par, nilexp, 0, 0, chvar_tag);
		  bro(*par) = cv; setlast(*par);
		  *par = cv;
		}
		if (last(*par)) break;
		par = &bro(*par);
	    }
	    par = &bro(fn);
	}


	nds = scan (fnexp, at);
	/* scan the function exp ... */
	if ((nds.propsneeds & hasproccall) != 0) {
				/* .... it must be identified */
	  cca (at, fnexp);
	  nds.propsneeds &= ~hasproccall;
	  nds.propsneeds |= usesproccall;
	  fn = son(application);
	  par = &bro(fn);
	}

	if (name(fn) != name_tag ||
		 (son(son(fn)) != nilexp && name(son(son(fn))) != proc_tag) ) {
		 tlrecpos = 0;
	}

	for (i = 1;!last(fn); ++i) {	/* scan parameters in turn ... */
	  needs onepar;
	  shape shpar = sh(*par);
	  onepar = scan (par, at);

	  parsize = rounder(parsize, shape_align(shpar));
	  onepar.fixneeds += (parsize>>5);
	  if ((i != 1 && (onepar.propsneeds & hasproccall) != 0) ||
	  		onepar.fixneeds > maxfix) {
				/* if it isn't the first parameter, and it
				   calls a proc, identify it */
	    cca (at, par);
	    nds.propsneeds |= usesproccall;
	    if (onepar.fixneeds !=0) nds.propsneeds |= morefix;
	    if (onepar.floatneeds !=0) nds.propsneeds |= morefloat;
	    nds = maxneeds (shapeneeds (sh (* (par))), nds);
	    nds.maxargs = max (nds.maxargs, onepar.maxargs);
	  }
	  else {
	    nds = maxneeds (onepar, nds);
	  }

	  parsize = rounder(parsize+shape_size(shpar), 32);
	  if ((!valregable(shpar) && !is_floating(name(shpar))) || parsize > 128) {
	  	tlrecpos = 0;
	  }
	  if (last (* (par))) {
	    break;
	  };
	  par = &bro(*par);
	}

	if ((i = specialfn (fn)) > 0) {/* eg strlen */
	  nds = maxneeds (specialneeds (i), nds);
	  return nds;
	}
	else
	  if (i == -1) {	/* call of strcpy .... */
	    /* TEST for constant string?????????????????
	    exp par2 = * (par);
	    if (name (par2) == eval_tag && name (son (par2)) == pack_tag
		&& name (son (son (par2))) == string_tag) {

	      setname (* (e), ass_tag);
	      son (* (e)) = * (parlist);
	      son (par2) = son (son (par2));
	      sh (par2) = sh (son (par2));
	      bro (par2) = * (e) ;
	      bro(son(par2)) = par2;
	      return maxneeds (nds, twofix);
	    }
	    */
	  }

	if (tlrecpos) {
		exp dad = father(application);
		if (name(dad)==res_tag) {
			props(dad) = 1; /* do a tl recursion*/
		}
	}
	nds.propsneeds |= hasproccall;
	nds.maxargs = max (nds.maxargs, parsize);
	return nds;

      };

    case val_tag: {
    	exp s = sh(*e);
    	if (name(s)==offsethd && al2(s) >= 8) {
    		/* express disps in bytes */
    		no(*e) = no(*e) >>3;
    	}
    	return shapeneeds (sh (* (e)));
    }

    case name_tag: {
	int n = no(*e);
	shape vs = sh(*e);
	if ( n>= 8*32768 || n < -8*32786) { /* offset too big for assembler */
		shape  s = f_offset(al1_of(vs), al1_of(vs));
		exp v = me_shint(s, n);
		exp nm = me_obtain(son(*e));
		exp ao = me_b3(vs, nm, v, addptr_tag);
		bro(ao) = bro(*e);
		if (last(*e)){ setlast(ao);} else {clearlast(ao);}
		*e = ao;
		kill_exp(ste, ste);
		return scan(e, at);
	}
        return shapeneeds (sh (* (e)));
    }
    case null_tag:
    case real_tag:
    case string_tag:
    case env_offset_tag: case general_env_offset_tag:
    case current_env_tag: case make_lv_tag:
    case last_local_tag:
    case caller_name_tag: case give_stack_limit_tag:
    case env_size_tag:
      {
	return shapeneeds (sh (* (e)));
      };

    case prof_tag: {
	name(*e) = top_tag;
	return zeroneeds;
    };
    case clear_tag:
    case top_tag: case local_free_all_tag:
    case formal_callee_tag:
      {
	return zeroneeds;
      };

    case case_tag: {
	needs nds;
    	nds = scan(&son(*e), at);
	if (nds.fixneeds < 3) nds.fixneeds = 3;
	return nds;
    }

    case set_stack_limit_tag:
    case neg_tag:
    case not_tag: case abs_tag:
    case offset_negate_tag: case absbool_tag: case return_to_label_tag:
    case diagnose_tag:   case goto_lv_tag:
      {
	exp * arg = &son(*e);
	return scan (arg, at);
      };
    case fneg_tag: case fabs_tag:
    case chfl_tag: {
    	needs nds;
    	nds = scan(&son(*e), at);
    	if (!optop(*e) && nds.fixneeds <2) nds.fixneeds = 2;
    	return nds;
    }

   case alloca_tag: {
    	needs nds;
    	nds = scan(&son(*e), at);
    	if (nds.fixneeds <2) nds.fixneeds = 2;
    	return nds;
    }
    case bitf_to_int_tag:
      {
	exp * arg = &son(*e);
	needs nds;
	exp stararg;
	exp stare;
	int   sizeb;

	nds = scan (arg, at);
	stararg = *(arg);
	stare = * (e);
	sizeb = ashof (sh (stararg)).ashsize;
	if ((name(stararg)==name_tag &&
	      ((sizeb == 8 && (no (stararg) & 7) == 0)
	         || (sizeb == 16 && (no (stararg) & 15) == 0)
	         || (sizeb == 32 && (no(stararg) & 31)== 0)
	       )
	     ) || (name(stararg)==cont_tag &&
		((name(son(stararg)) != name_tag && name(son(stararg)) != reff_tag)
		   || (sizeb == 8 && (no (son(stararg)) & 7) == 0)
	      	   || (sizeb == 16 && (no (son(stararg)) & 15) == 0)
	     	   || (sizeb == 32 && (no(son(stararg)) & 31)== 0)
		)
	         )
	   ) {
		bool sgned = is_signed(sh(stare));
		shape ns = (sizeb==8)? ( (sgned)?scharsh:ucharsh)
			  : (sizeb==16) ?((sgned)?swordsh:uwordsh)
			  : sh(stare);
		/*  can use short loads instead of bits extractions*/
		if (name(stararg)==cont_tag) {
			/* make the ptr shape consistent */
			sh(son(stararg)) = f_pointer(long_to_al(shape_align(ns)));
		}
		sh(stararg) = ns;
		setname(stare, chvar_tag);
	}
	return nds;
      }

    case int_to_bitf_tag:
      {
	exp * arg = &son(*e);
	return scan (arg, at);
      }

    case round_tag:
      {
	needs s;
	exp * arg = &son(*e);
	shape sres = sh(*e);
        if (shape_size(sres) != 32 ) {
	   exp ch = getexp(sres, bro(*e), last(*e), *e, pt(*e), props(*e),
				0, chvar_tag);
	   bro(*e) = ch; setlast(*e);
	   sh(*e) = slongsh;
	   *e = ch;
	   return scan(e, at);
	}

	s = scan (arg, at);
	s.fixneeds = max (s.fixneeds, (optop(*e))?2:5);
	s.floatneeds = max (s.floatneeds, 2);
	return s;
      };

    case shl_tag:
    case shr_tag: case long_jump_tag:
      {
	exp * lhs = &son(*e);
	exp * rhs  = & bro(*lhs);
	needs nr;
        needs nl;
        prop prps ;
	if (name(*rhs)==val_tag) {
		return scan (lhs, at);
	}

        nr = scan(rhs, at);
        nl = scan (lhs, at);
	rhs = &bro(*lhs);
        prps = (nr.propsneeds & hasproccall) << 1;
        if (nr.fixneeds >= maxfix || prps != 0) {
                              /* if reg requirements overlap, identify
                                 second operand */
          cca (at, rhs);
          nl = shapeneeds (sh (* (rhs)));
          nl.propsneeds |= morefix;
          nl.propsneeds &= ~(prps >> 1);
          nl.propsneeds |= prps;
        }
        nr.fixneeds += 1;
        return maxneeds (nl, nr);

      };


    case test_tag:
      {
	exp stare = *(e);
	exp l = son (stare);
	exp r = bro (l);
	exp dad = father(stare);
	bool xlike = (name(dad)==maxlike_tag || name(dad)==minlike_tag || name(dad)==abslike_tag);
			/* don't do various optimisations if xlike */

	if (!last (stare) && name (bro (stare)) == test_tag &&
	    no (stare) == no (bro (stare)) &&
	    props(stare)==props(bro(stare)) &&
	    eq_exp (l, son (bro (stare))) && eq_exp (r, bro (son (bro (stare))))
	  ) {			/* same test following in seq list -
				   remove second test */
	  if (last (bro (stare)))
	    setlast (stare);
	  bro (stare) = bro (bro (stare));
	}

	if (last (stare) && name (bro (stare)) == 0/* seq holder */
	    && name (bro (bro (stare))) == test_tag &&
	    name (bro (bro (bro (stare)))) == seq_tag &&
	    no (stare) == no (bro (bro (stare))) &&
	    props(stare)==props(bro(bro(stare))) &&
	    eq_exp (l, son (bro (bro (stare))))
	    && eq_exp (r, bro (son (bro (bro (stare)))))
	  ) {			/* same test following in seq res - void
				   second test */
	  setname (bro (bro (stare)), top_tag);
	  son (bro (bro (stare))) = nilexp;
	  pt (bro (bro (stare))) = nilexp;
	}

	if (!xlike && name (l) == val_tag && (props (stare) == 5 || props (stare) == 6)) {
				/* commute  const = x */
	  bro (l) = stare;
	  setlast (l);
	  bro (r) = l;
	  clearlast (r);
	  son (stare) = r;
	  r = l;
	  l = son (stare);
	}

	if (!xlike && name (r) == val_tag && (props (stare) == 5 || props (stare) == 6) &&
	    no (r) == 0 &&
	    name (l) == and_tag && name (bro (son (l))) == val_tag &&
	    (no (bro (son (l))) & (no (bro (son (l))) - 1)) == 0
	  ) {			/* zero test  x & 2^n   -> neg test (x shl
				   (31-n)) */
	  long  n = no (bro (son (l)));
	  int   x;
	  for (x = 0; n > 0; x++) {
	    n = n << 1;
	  }
	  if (x == 0) {		/* no shift required */
	    bro (son (l)) = r;	/* zero there */
	    son (stare) = son (l);/* x */
	  }
	  else {
	    setname (l, shl_tag);
	    no (bro (son (l))) = x;
	  }
	  props (stare) -= 3;	/* test for neg */
	  sh (son (stare)) = slongsh;

	}
	if (name (l) == bitf_to_int_tag && name (r) == val_tag &&
	    (props (stare) == 5 || props (stare) == 6) &&
	    (name (son (l)) == cont_tag || name (son (l)) == name_tag)) {
				/* equality of bits against +ve consts
				   doesnt need sign adjustment */
	  long  n = no (r);
	  switch (name (sh (l))) {
	    case scharhd:
	      {
		if (n >= 0 && n <= 127) {
		  sh (l) = ucharsh;
		} break;
	      }
	    case swordhd:
	      {
		if (n >= 0 && n <= 0xffff) {
		  sh (l) = uwordsh;
		} break;
	      }

	    default: ;
	  }
	}
	else
	  if (is_floating (name (sh (l)))) {
	    return fpop (e, at);
	  }
	  else
	    if (!xlike && name (r) == val_tag && no (r) == 1
		&& (props (stare) == 3 || props (stare) == 2)) {
	      no (r) = 0;
	      if (props (stare) == 3) {
		props (stare) = 4;/* branch >=1 -> branch > 0 */
	      }
	      else {
		props (stare) = 1;/* branch <1 -> branch <= 0 */
	      }
	    }

	return likediv (e, at);

      }


    case movecont_tag:{
        exp * d = &son(*e);
        exp * s = & bro(*d);
        exp * sz = &bro(*s);
	needs nd;
        needs ns;
        needs nsz;
        prop prps ;
        nd = scan(d, at);
        ns = scan (s, at);
        nsz = scan(sz, at);
        prps = (ns.propsneeds & hasproccall) << 1;
        if (ns.fixneeds >= maxfix || prps != 0) {
                              /* if reg requirements overlap, identify
                                 second operand */
          cca (at, s);
          ns = shapeneeds (sh (* (s)));
          ns.propsneeds |= morefix;
          ns.propsneeds &= ~(prps >> 1);
          ns.propsneeds |= prps;
        }
        nd.fixneeds += 1;
        nd = maxneeds (nd, ns);
        prps= (nsz.propsneeds & hasproccall) << 1;
        if (nd.fixneeds +nsz.fixneeds >= maxfix || prps != 0) {
                              /* if reg requirements overlap, identify
                                 last operand */
          cca (at, sz);
          nsz = shapeneeds (sh (* (sz)));
          nsz.propsneeds |= morefix;
          nsz.propsneeds &= ~(prps >> 1);
          nsz.propsneeds |= prps;
        }
        nd.fixneeds+=1;
        nd = maxneeds(nd,nsz);
        if (nd.fixneeds < 4) nd.fixneeds = 3;
        return nd;
     }




    case plus_tag:
      {				/* replace any operands which are neg(..)
				   by - ,if poss */
	exp sum = * (e);
	exp list = son (sum);
	bool someneg = 0;
	bool allneg = 1;
	for (;optop(sum);) {
	  if (name (list) == neg_tag)
	    someneg = 1;
	  else
	    allneg = 0;
	  if (last (list))
	    break;
	  list = bro (list);
	}

	if (someneg) {		/* there are some neg() operands */
	  if (allneg) {
	    /* transform -..-... to -(..+.. +...) */
	    exp x = son (sum);
	    list = son (x);
	    for (;;) {
	      if (!last (x)) {
	        bro (list) = son (bro (x));
		clearlast (list);
		list = bro (list);
		x = bro (x);
	      }
	      else {
		bro(list) = sum;
		setlast (list);
		son (sum) = son (son (sum));
		/* use existing exp */
		break;
	      }
	    }
	    x = getexp (sh (sum), bro (sum), last (sum), sum, nilexp,
		0, 0, neg_tag);
	    setlast(sum); bro(sum)=x; /* set father of sum to be negate */
	    * (e) = x;

	  }			/* end allneg */
	  else {
	    /* transform to  ((..(..+..) - ..) -..) */
	    int   n = 0;
	    exp brosum = bro (sum);
	    bool lastsum = last (sum);
	    exp x = son (sum);
	    exp newsum = sum;
	    list = nilexp;
	    for (;;) {
	      exp nxt = bro (x);
	      bool final = last (x);
	      if (name (x) == neg_tag) {
		bro (son (x)) = list;
		list = son (x);
	      }
	      else {
		bro (x) = newsum;
		newsum = x;
		if ((n++) == 0)
		  setlast (newsum);
		else
		  clearlast (newsum);
	      }
	      if (final)
		break;
	      x = nxt;
	    }

	    if (n > 1) {
	      son (sum) = newsum;
	      newsum = sum;	/* use existing exp for add operations */
	    }
	    for (;;) {		/* introduce - operations */
	      exp nxt = bro (list);
	      bro (newsum) = list;
	      clearlast (newsum);
	      x = getexp (sh (sum), nilexp, 0, newsum, nilexp, 0, 0, minus_tag);

	      bro (list) = x;
	      setlast (list);
	      newsum = x;
	      if ((list = nxt) == nilexp)
		break;
	    }
	    bro (newsum) = brosum;
	    if (lastsum) {
	      setlast (newsum);
	    }
	    else {
	      clearlast (newsum);
	    }
	    * (e) = newsum;

	  }			/* end else allneg */

	  return scan (e, at);

	}			/* end someneg  */
	return likeplus (e, at);
      }


   case addptr_tag:
    {
    	exp p = son(*e);
    	exp d = bro(p);
    	int fal = frame_al_of_ptr(sh(p));
    	if (fal!=0) {
    		int oal = frame_al1_of_offset(sh(d));
/*    		if( ((oal-1)&oal) != 0) {
    			failer("can't cope with mixed frame offsets yet");
    		}
    		if ((oal & fal)==0) {
    			failer("frame-ptr and offset incompatible");
    		}
*/
    		if ( includes_vcallees(fal) && l_or_cees(oal)) {
    			/* if oal = locals or callees relative to local reg
    			   else relative to fp */
    		   exp ne = getexp(sh(p), d, 0, p, nilexp, 0, 0,
    		   		locptr_tag);
    		   bro(p) = ne; setlast(p);
    		   son(*e) = ne;
    		}
    	}
    	/* ... and continue */
    }
    case mult_tag:
    case and_tag:
    case or_tag:
    case xor_tag:
      {
	return likeplus (e, at);
      };



    case reff_tag:
    case chvar_tag:
    case offset_pad_tag:
    case locptr_tag:

      {
	exp * arg = &son(*e);
	return maxneeds (scan (arg, at),
	    shapeneeds (sh (* (e))));
      };

    case float_tag:  {
	needs nds;
	exp * arg = &son(*e);
	nds = maxneeds (scan (arg, at), shapeneeds (sh (* (e))));
	if (name(sh(son(*(e)))) == ulonghd) {
		if (nds.floatneeds <2) nds.floatneeds =2;
	}
	return nds;
    }

    case cont_tag:
    case contvol_tag:
      {
	exp * arg = &son(*e);
	needs nds;

	nds = maxneeds (scan (arg, at), shapeneeds (sh (* (e))));
	nds.fixneeds = max (nds.fixneeds, 2);

	return nds;
      };

    case offset_mult_tag: case offset_div_tag: {
	exp op1 = son(*e);
    	exp op2 = bro(op1);
    	shape s = sh(op2);
    	if (name(op2)==val_tag  && name(s)==offsethd
		&& al2(s) >= 8) {
	    int n = no(op2)/8;
	    if (n == 1) {
    		/* offset is one  byte */
    		bro(op1) = bro(*e);
    		if (last(*e)) { setlast(op1); } else {clearlast(op1); }
    		*e = op1;
    		return( scan(e, at));
	    }
	    else
	    if ( name(*e) == offset_mult_tag && n > 1 && (n&(n-1))== 0)
	      if( name(op1) == and_tag
		      && name(son(op1))== shr_tag &&
		      name(bro(son(op1)))==val_tag ) {
		exp shexp = son(op1);
		exp ac = bro(shexp);
		exp shop1 = son(shexp);
		exp shop2 = bro(shop1);
		int na = no(ac);
		if ((na&(na+1))==0 && name(shop2)==val_tag) {
		    int pn = 0;
		    int ns = no(shop2);
		    int i = n;
		    while (i>1) { i >>= 1; pn++; }

		    if (ns > pn) {
		      /* can do transform:
		       (((shop1>>ns) & na) * n) =>
				    shop1>>(ns-pn) & (na*n)
		      */
		      no(shop2) = ns-pn;
		      no(ac) = na*n;
		      bro(op1) = bro(*e);
    		      if (last(*e)) { setlast(op1); } else {clearlast(op1); }
		      *e = op1;
    		      return( scan(e, at));
		    }
		}
	     }
	     else { /* will do this by literal shift */
		no(op2) = n;
		return scan(&son(*e), at);
	     }
    	}
	return likediv (e, at);

    }

    case offset_add_tag: {
	exp l = son(*e);
	exp r = bro(l);
	if (name(l) == val_tag) {
		sh(l) = sh(r);   /* both offsets will be treated the same */
		son(*e) = r; clearlast(r);
		bro(r) = l; setlast(l); bro(l) = *e;
			/* ... and put val last */
	}
        else
	if (al2(sh(l))>=8 && al2(sh(r)) <8) {
	       return likediv (e, at);
	}
	setname(*e, plus_tag);

	return likeplus(e,at);
    }

    case offset_subtract_tag: {
	exp l = son(*e);
	exp r = bro(l);
	if (name(r)==val_tag) {
		sh(r) = sh(l);   /* both offsets will be treated the same */
	}
	else
	if ( al2(sh(r))>=8 && al2(sh(l)) <8) {
	        return likediv (e, at);
	}

	setname(*e, minus_tag);
	return likediv (e, at);
    }
    case div0_tag:
    case rem0_tag:
    case div2_tag:
    case minus_tag:
    case subptr_tag:
    case minptr_tag: case make_stack_limit_tag:
    case rem2_tag:
    case offset_div_by_int_tag:
    case component_tag:
      {
	return likediv (e, at);
      };
    case offset_max_tag: case max_tag: case min_tag: case local_free_tag:
	{ needs nd;
	  nd = likediv(e, at);
	  nd.fixneeds = max(nd.fixneeds, 3);
	  return nd;
	}
    case div1_tag: {
    	if (!is_signed(sh(*e))) { setname(*e, div2_tag); }
    	return likediv(e,at);
    }
    case mod_tag: {
    	if (!is_signed(sh(*e))) { setname(*e, rem2_tag); }
    	return likediv(e,at);
    }
    case fdiv_tag:
/* THIS IS TOO ACCURATE FOR PLATFORM!
      {
	exp z = * (e);
	exp a2 = bro (son (z));
	if (name (a2) == real_tag) { replace X/const by X*const^-1
	  flt inverse;
	  flt unitflt;
	  str2flt ("1.0", &unitflt, (char **) 0);
	  if (flt_div (unitflt, flptnos[no (a2)], &inverse) == OKAY) {
				  a/const => a* (1.0/const)
	    int   f = new_flpt ();
	    flptnos[f] = inverse;
	    no (a2) = f;
	    setname (z, fmult_tag);
	  }
	}
      }
*/
      /* and continue to next case */

    case fplus_tag:
    case fminus_tag:
    case fmult_tag:
      {
        exp op = *(e);
        exp a2 = bro(son(op));
        if (!last(a2) ) { /* + and * can have >2 parameters
        		  - make them diadic - can do better
        		  a+exp => let x = exp in a+x */
           	exp opn = getexp(sh(op), op, 0, a2, nilexp, 0, 0, name(op));
           		/* dont need to transfer error treatment - nans */
        	exp nd = getexp(sh(op), bro(op), last(op), opn, nilexp, 0, 1,
        			ident_tag);
        	exp id = getexp(sh(op), op, 1, nd, nilexp, 0, 0, name_tag);
        	pt(nd) = id;
        	bro(son(op)) = id;
        	setlast(op); bro(op) = nd;
        	while (!last(a2)) a2 = bro(a2);
        	bro(a2) = opn;
        	*(e) = nd;
        	return scan(e, at);
        }

	return fpop (e, at);
      };

    case field_tag:
      {
	needs str;
	exp * arg = &son(*e);
	if (chase(*e, arg)) { /* field has been distributed */
	  exp stare = *e;
	  exp ss = son (stare);
	  if (!last (stare))
	    clearlast (ss);
	  bro (ss) = bro (stare);
	  sh (ss) = sh (stare);
	  *e = ss;
	  return (scan (e, at));
	}
	str = scan (arg, at);
	return maxneeds (str, shapeneeds (sh (* (e))));
      };

/*********************************************************************
	load_proc


number is number of proc (useful for indexing)
*********************************************************************/

    case proc_tag:
    case general_proc_tag:
      {
	exp * bexp;
	exp * bat;
	needs body;
	exp stare = *(e);

	callerfortr = do_tlrecursion && !proc_has_setjmp(stare) && !proc_has_alloca(stare) &&
			!proc_has_lv(stare) && !proc_uses_crt_env(stare);

	maxfix = (PIC_code)?15:16;
		/* ie $2-$15, $24 & $25 if not PIC */
	maxfloat = 10;
  	gen_call = (name(stare)==general_proc_tag);
	callee_size = 0;
	stparam = 0;
	fixparam = 4;
	floatparam = 6;
	nonevis = 1;
	rscope_level = 0;

	bexp = & son(*e);
	bat = bexp;
	body = scan (bexp, &bat);
	/* scan the body of the proc */
        setframe_flags(*e, (body.propsneeds & anyproccall)==0);
        if(gen_call || Has_fp) callee_size+=128;

	return body;		/*  should never require this in reg in C */

      }



    default:
      {
	printf ("case %d not covered in needs scan\n", name (* e));
	/* NB should call failer */
	return zeroneeds;
      }

  }
}
