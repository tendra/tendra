/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <local/expmacs.h>
#include <local/exptypes.h>

#include <construct/tags.h>
#include <construct/exp.h>

#include <main/flags.h>

#include <refactor/const.h>

#include "bitsmacs.h"
#include "tempdecs.h"

static int nouses;
static bool useinpar;

int
trace_uses(exp e, exp id)
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
	    return 1;
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


void
after_a(exp a, exp id)
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



bool
tempdec(exp e, bool enoughs)
{
				/* e is a local declaration; 'enoughs'
				   is a misnomer to say whether there are
				   t-regs available delivers 1 if e can be
				   allocated into t-reg or par reg */
	exp p;
	if (~optim & OPTIM_TEMPDEC) return 0;
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
