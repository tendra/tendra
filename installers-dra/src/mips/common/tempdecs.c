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
$Date: 1998/01/17 15:56:07 $
$Revision: 1.1.1.1 $
$Log: tempdecs.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:07  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/10/02  10:30:34  currie
 * env_offset + -g (PIC)
 *
 * Revision 1.2  1995/07/07  09:52:40  currie
 * apply_general in tempdecs
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/*  tempdec.c - is the value in the declaration required over  proc calls ?
	if it isn't, declaration can be allocated in t-reg, rather than
	s-reg.

*/

#include "config.h"
#include "tags.h"
#include "common_types.h"
#include "exp.h"
#include "const.h"
#include "expmacs.h"
#include "bitsmacs.h"
#include "tempdecs.h"


static int nouses;
static bool useinpar;

int trace_uses
    PROTO_N ( (e, id) )
    PROTO_T ( exp e X exp id )
{
	/* reduces nouses for each non-assignment use of id encountered in e;
	    sets useinpar if use in actual parameter posn
	    terminates with 0 on applications or jumps
	    terminates with 2 on assignment to id
	    otherwise delivers 1
	*/

     switch(name(e)) {
	case name_tag: {
	    nouses -=(son(e)==id);
	    return (1);
	}
	case apply_tag: case apply_general_tag:{
	    int u = nouses;
	    int p = 1;
	    exp l = son(e);
	    while( p==1 ) {
	    	p = trace_uses(l, id);
	    	if (u!=nouses || p==2) { useinpar=1; }
	    	if (p==0) nouses = u;
	    	if (last(l)) break;
	    	l = bro(l);
	    }

	    return 0;
	}

	case ident_tag: {
	     exp f = son(e);
	     exp s = bro(f);
	     int a;
	     if ( ( props(e) & defer_bit) != 0 ) {
		exp t = f;
		f = s;
	  	s = t;
	     }
	     a = trace_uses(f, id);
	     if (a !=1) return a;
	     return trace_uses(s, id);
	}


	case case_tag: case res_tag: {
	      trace_uses(son(e), id);
	      return 0;
	}

	case labst_tag: return 0;

	case seq_tag: {
		exp s = son(son(e));
		for(;;) {
			int el = trace_uses(s, id);
			if (el!=1 ) return el;
			if (last(s)) return trace_uses(bro(son(e)),id);
			s = bro(s);
		}

	}

	case ass_tag: {
	    if (isvar(id) && name(son(e))==name_tag && son(son(e))==id) {
		trace_uses(bro(son(e)),id);
	 	return 2;
	    }
	    else {
		int nu = nouses;
		if (trace_uses(son(e),id) != 1 ||
				trace_uses(bro(son(e)), id) !=1 ){
			nouses = nu;
			return 0;
		}
		return 1;
	    }
	}
        case goto_lv_tag:{
		int nu = nouses;
		if (trace_uses(son(e),id) != 1) {
			nouses = nu;
		}
		return 0;
	}
	case test_tag:{
		int nu = nouses;
		if (trace_uses(son(e),id) != 1 ||
				trace_uses(bro(son(e)), id) !=1 ){
			nouses = nu;
		}
		return 0;
	}
	case solve_tag: case cond_tag: {
		return trace_uses(son(e), id);
	}

	case goto_tag: case rep_tag: case env_offset_tag: return 0;

	default: {
	     exp s = son(e);
	     int nu = nouses; /* s list can be done in any order ...*/
	     if (s == nilexp) return 1;
	     for(;;) {
		int el = trace_uses(s, id);
		if (el!=1 ) { /* ... so reset nouses if any terminate */
			 nouses = nu;
			 return el;
		};
		if (last(s)) return 1;
		s = bro(s);
	     }
	}

     }
}


void after_a
    PROTO_N ( (a, id) )
    PROTO_T ( exp a X exp id )
{
	/* apply trace_uses to dynamic successors of a */
           	exp dad ;
	exp l;
         tailrec: dad = father(a);
	if (nouses == 0) return;
	if (name(dad)==cond_tag || name(dad)==rep_tag || name(dad)==res_tag
	      || name(dad) == solve_tag || name(dad) == labst_tag
	      || name(dad) == case_tag || name(dad)== goto_lv_tag
	      || name(dad) == test_tag ||  name(dad) == apply_tag) {
		 /* dont try too hard ! */
		while (name(dad) != apply_tag && dad !=id) dad = father(dad);
		if (name(dad) == apply_tag) { useinpar =1;}
		return;
	}


	for (l=a; !last(l); l=bro(l)) {
	    int u = trace_uses(bro(l), id);
	    if (u!=1|| nouses==0) return;
	}
	a = dad;
	if (dad!=id) goto tailrec;
}



bool tempdecopt = 1;		/* flag to allow this optimisation; -Tt
				   sets to 0 */

bool tempdec
    PROTO_N ( (e, enoughs) )
    PROTO_T ( exp e X bool enoughs )
{
				/* e is a local declaration; 'enoughs'
				   is a misnomer to say whether there are
				   t-regs available delivers 1 if e can be
				   allocated into t-reg or par reg */
	exp p;
	if (!tempdecopt ) return 0;
	nouses = 0;
	useinpar = 0;
	if (isvar(e) ) {
	   for (p=pt(e); p!=nilexp; p =pt(p)) {
	    /* find no of uses which are not assignments to id ... */
	    if (!last(p) && last(bro(p))
		 && name(bro(bro(p))) == ass_tag ) {
		continue;
	    }
	    nouses++;
	  }
	}
	else nouses = no(e);

	/* trace simple successors to assignmnts or init to id to find if
		all uses occur before unpredictable change of control
			(or another assignment to id) */

	if (nouses>30) return 0; /* takes too long */

	if (name(son(e)) != clear_tag || isparam(e)) { after_a(son(e), e); }

	if (isvar(e)) {
	  for (p=pt(e); p!=nilexp; p =pt(p)) {
	    if (!last(p) && last(bro(p))
		 && name(bro(bro(p))) == ass_tag ) {
		after_a(bro(bro(p)), e);
	    }
	  }
	}

	if (nouses ==0 &&(enoughs || !useinpar) ) {
	     if (useinpar) props(e) |= notparreg; /* don't allocate this into par reg */
	     return 1;
	}
	return 0;
}
