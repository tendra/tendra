/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stddef.h>

#include <shared/bool.h>

#include <tdf/tag.h>

#include <reader/externs.h>
#include <reader/basicread.h>

#include <construct/exp.h>
#include <construct/shape.h>

#include "extern_adds.h"
#include "procrectypes.h"
#include "scan.h"
#include "localexpmacs.h"


/* replaces uses of extern in procs by local identification of address;

   initially replace usage chain by
     name:0; pt: usage chain in proc P; son: P; props: !=0 if in loop
	no: no of usages in proc; bro: last in usage chain;
    in usages[no of procs]
    Use this to determine if and where to identify global to a proc local

*/

exp * usages;

static bool
enter_parents(exp e)
{
	exp dad =e;
	bool inloop = 0;
	assert(name(e)==name_tag);
	for(;;) {
	  	dad = father(dad);
		if (name(dad)==rep_tag) {
		  	inloop=1;
		}
		else
		if (name(dad)==proc_tag) {
			exp nu = usages[no(dad)];
			if (nu == NULL) {
			  nu = getexp(sh(e), e, 1, dad, NULL, 0,
			  		0, 0);
			  usages[no(dad)] = nu;
		        }
			props(nu) |= inloop;
			pt(e) = pt(nu);
				/* remember pt(e) before entry */
			pt(nu) = e;
			no(nu)++;
			return 1;
		}
		else
		if (name(dad)== ident_tag && isglob(dad)) {
			return 0;
		}
		else
		if (name(dad) == 102) {
			/* could be leftover from exp token expansion
				with no pars */
			return 0;
		}
	}
}



void
global_usages(exp id, int nop)
{
	exp plist, nextpl;
	int i;
	assert(name(id)==ident_tag && isglob(id) && son(id)==NULL);
	if (no(id)==0) return;

	for(i=0; i<nop; i++) {
		usages[i] = NULL;
	}
	plist = pt(id);
	nextpl = pt(plist);
	pt(id) = NULL;
	no(id) = 0;
	for(;;) {
		if (!enter_parents(plist)) {
			pt(plist) = pt(id);
			pt(id) = plist;
			no(id)++;
		}
		if ((plist = nextpl) == NULL) break;
		nextpl = pt(plist);
	}

	for(i=0; i<nop; i++) {
	  exp ui = usages[i];
	  if (ui != NULL) {

	     if (props(ui) != 0  ) {
	     	/* id is used enough in proc i - so identify it locally */
		exp * pi;
		shape sname = f_pointer(f_alignment(sh(id)));
		for(pi= &son(son(ui));;) {
		  if (name(*pi)== ident_tag && isparam(*pi)) {
		  	pi = &bro(son(*pi));
		  }
		  else
		  if (name(*pi) == diagnose_tag || name(*pi) == prof_tag) {
			pi = &son(*pi);
		  }
		  else {
		  	/* invent new def to identify global ... */
			exp nl = getexp(sname,
				   *pi, 0, id, pt(id), 0, 0, name_tag);
			exp ndef = getexp(sh(*pi), bro(*pi),last(*pi),
					 nl, NULL, 0x10 /*don't defer */,
					0, ident_tag);
			exp lu = pt(ui);
			setlast(*pi); bro(*pi) = ndef;
			pt(id) = nl; no(id)++;
			*pi = ndef;
			/*... and replace uses of global by ndef */
			while(lu != NULL) {
			  exp nlu = pt(lu);
			  if (no(lu)!=0) {
				exp * plu = ptr_position(lu);
				exp nrf = getexp(sh(lu), bro(lu), last(lu),
						lu, NULL, 0, no(lu), reff_tag);
				sh(lu) = sname;
				no(lu) = 0;
				bro(lu) = nrf; setlast(lu);
				*plu = nrf;
			  }
			  son(lu) = ndef;
			  pt(lu) = pt(ndef);
		          pt(ndef)= lu; no(ndef)++;
			  lu = nlu;
			}
			break;
		  }
		}
	      }
	      else {
	      	/* restore normal usage chain */
		pt(bro(ui)) = pt(id);
		pt(id) = pt(ui);
		no(id)+= no(ui);
	      }
	      retcell(ui);
	   }
	}
}
