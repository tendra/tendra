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


#include "config.h"
#include "extern_adds.h"
#include "common_types.h"
#include "tags.h"
#include "exp.h"
#include "expmacs.h"
#include "shapemacs.h"
#include "externs.h"


extern exp * ptr_position PROTO_S ((exp e));

/* replaces uses of extern in procs by local identification of address;

   initially replace usage chain by
     name:0; pt: usage chain in proc P; son: P; props: !=0 if in loop
	no: no of usages in proc; bro: last in usage chain;
    in usages[no of procs]
    Use this to determine if and where to identify global to a proc local	

*/

exp * usages;

static bool enter_parents
    PROTO_N ( ( e ) )
    PROTO_T ( exp e )
{
  exp dad =e;
  bool inloop = 0;
  Assert(name(e)==name_tag);
  for(;;) {
    dad = father(dad);
    if (name(dad)==rep_tag) {
      inloop=1;
    }
    else if (name(dad)==proc_tag) {
      exp nu = usages[no(dad)];
      if (nu == nilexp) {
	nu = getexp(sh(e), e, 1, dad, nilexp, 0,0, 0);
	usages[no(dad)] = nu;
      }
      props(nu) |= inloop;
      pt(e) = pt(nu); 
				/* remember pt(e) before entry */
      pt(nu) = e;
      no(nu)++;
      return 1;
    }
    else if (name(dad)== ident_tag && isglob(dad)) {
      return 0;
    }
    else if (name(dad) == 102 || name(dad) == hold_tag) {
      /* thou shalt use descriptive names for constants (102 ?) */

      /* could be leftover from exp token expansion with no pars */
      return 0;
    }
  }
}



void global_usages
    PROTO_N ( ( id, nop ) )
    PROTO_T ( exp id X int nop )
{
  exp plist, nextpl;
  int i;
  Assert(name(id)==ident_tag && isglob(id) && son(id)==nilexp);
  if (no(id)==0) return;
  for(i=0; i<nop; i++) {
    usages[i] = nilexp;
  }
  plist = pt(id);
  nextpl = pt(plist);
  pt(id) = nilexp;
  no(id) = 0;
  for(;;) {
    if (!enter_parents(plist)) {
      pt(plist) = pt(id);
      pt(id) = plist;
      no(id)++;
    }
    if ((plist = nextpl) == nilexp) break;
    nextpl = pt(plist);
  }
  for(i=0; i<nop; i++) {
    exp ui = usages[i];
    if (ui != nilexp) {
      if (props(ui) != 0  ) {
	/* id is used enough in proc i - 
	   so identify it locally */		
	exp * pi;
	shape sname = f_pointer(f_alignment(sh(id)));
	for(pi= &son(son(ui));;) {
	  if (name(*pi)== ident_tag && isparam(*pi)) {
	    pi = &bro(son(*pi));
	  }
	  else if (name(*pi) == diagnose_tag || name(*pi) == prof_tag) {
	    pi = &son(*pi);
	  }	
	  else {
	    /* invent new def to identify global ... */	
	    exp nl = getexp(sname,
			    *pi, 0, id, pt(id), 0, 0, name_tag);
	    exp ndef = getexp(sh(*pi), bro(*pi),last(*pi),
			      nl, nilexp, 0x10/*don't defer */, 
			      0, ident_tag);
	    exp lu = pt(ui);
	    setlast(*pi); bro(*pi) = ndef;
	    pt(id) = nl; no(id)++;
	    setcaonly(ndef);
	    *pi = ndef;
	    /*... and replace uses of global by ndef */
	    while(lu != nilexp) {
	      exp nlu = pt(lu);
	      if (no(lu)!=0) {
		exp * plu = ptr_position(lu);
		exp nrf = getexp(sh(lu), bro(lu), last(lu),
				 lu, nilexp, 0, no(lu), reff_tag);
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
					
				 


