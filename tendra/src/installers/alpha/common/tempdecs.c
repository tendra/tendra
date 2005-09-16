/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


/*  
  tempdec.c - is the value in the declaration required over  
  proc calls ?  If it isn't, declaration can be allocated 
  in t-reg, rather than s-reg.
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

/* 
   reduces nouses for each non-assignment use of id encountered 
   in e; sets useinpar if use in actual parameter posn 
   terminates with 0 on applications or jumps terminates with 2 
   on assignment to id otherwise delivers 1
*/
int
trace_uses(exp e, exp id)
{
  Assert(e!=(exp)0);
  Assert(id!=(exp)0);
  switch(name(e)) {
    case name_tag: {
      nouses -=(son(e)==id);
      return (1);
    }	
    case apply_general_tag :
    case apply_tag :{
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
    
    
  case case_tag:  {
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
    else{
      int nu = nouses;
      if (trace_uses(son(e),id) != 1 ||
	  trace_uses(bro(son(e)), id) !=1 ){
	nouses = nu;
	return 0;
      }
      return 1;
    }
  }
  case goto_lv_tag:
  {
    int nu = nouses;
    if(trace_uses(son(e),id) != 1){
      nouses = nu;
    }
    return 0;
  }
  case test_tag:{
    int nu = nouses;
    if((trace_uses(son(e),id) != 1) || (trace_uses(bro(son(e)),id)!= 1)){
      nouses = nu;
    }	
    return 0;
   }
   case solve_tag:case cond_tag: {
     return trace_uses(son(e),id);
   }
   case goto_tag:case rep_tag:
     return 0;
   case current_env_tag:
     return 0;
   default: {
     exp s = son(e);
     int nu = nouses; /* s list can be done in any order ...*/
     if (s == nilexp) return 1;
     for(;;) {
       int el = trace_uses(s, id);
       if (el!=1 ) { /* ... so reset nouses if any terminate */
	 nouses = nu; 
	 return el; 
       }
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
  if (name(dad)==cond_tag || name(dad)==rep_tag || name(dad) == res_tag
      || name(dad) == solve_tag || name(dad) == labst_tag
      || name(dad) == case_tag || name(dad)== goto_lv_tag
      || name(dad) == test_tag ||  name(dad) == apply_tag) {
    /* don't try too hard ! */
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
simple_seq(exp e, exp id)
{
  exp dad = father(e);
  for(;;) {
    if (dad == id) return 1;
    if (name(dad)==seq_tag || name(dad)==0
	|| name(dad) == ident_tag) { dad = father(dad);}
    else return 0;
  }
}

bool tempdecopt = 0;		/* flag to allow this optimisation; -Tt
				   sets to 0 */

bool
tempdec(exp e, bool enoughs)
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
/*	if (!simple_seq(bro(bro(p)), e) ) return 0;*/
	/* ... in simple sequence */		 
	continue;
      }
      nouses++;
    }
  }
  else nouses = no(e);
  
  /* trace simple successors to assignments or init to id to find 
     if all uses occur before unpredictable change of control 
     (or another assignment to id) */
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
    if (useinpar) props(e) |= notparreg; 
    /* don't allocate this into par reg */
    return 1;
  }
  return 0;
}


		



