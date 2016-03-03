/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>
#include <shared/check.h>

#include <local/tag.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>

#include <construct/exp.h>

#include <main/flags.h>

#include "procrectypes.h"
#include "bitsmacs.h"
#include "frames.h"
#include "regable.h"
#include "reg_defs.h"
#include "dump_distr.h"

static  space zsp = {
  0, 0
};				/* long fixed, long flt */

static void
maxsp(space *a, space b)
{
  a -> fixed |= b.fixed;
  a -> flt |= b.flt;
}


/* 
   accumulate s regs used in e; pars gives bits indicating 
   which s-regs are used for the parameters of current proc; 
   incpars says dont ignore pars in registers 
*/
static space
suses(exp e, space *pars, int incpars)
{

  space ans;
  ans = zsp;
  if (e == NULL)
    return ans;
  switch (e->tag) {
  case name_tag: {
    exp id = son (e);
    if (id->tag == ident_tag) {
      if (isglob (id) || (props (id) & inanyreg) == 0)
	return ans /* global or not in register */ ;
      if ((props (id) & defer_bit) != 0)
	return suses (son (id), pars, incpars);/*dec does not take space*/
      if (isparam(id) && no(id) !=0 && 
	  ((!incpars && props(son(id)) != 0) || no(id)==props(son(id)) ) )
	/* par in original reg (perhaps destined for sreg) */
	return ans;
      if ((props(id) & infreg_bits)!=0 ) {
	if (no (id) != NO_REG  && no(id)!=0) {/* uses floating s-reg */
	  if(isparam(id) && props(son(id))!=0 && props(son(id))>=incpars){
	    return ans;
	  }
	  else{
	    ans.flt = (1<<(no(id)));
	  }
	}
      }
      else
	if (no (id) != 0 && no (id) != 32) {
	  /* in s seg */
	  if (isparam(id) && props(son(id)) !=0 && 
	      props(son(id)) >= incpars) return ans;
	  ans.fixed = 1 << (no (id));
	}
    }
    break;
  }
  case case_tag: 
  {
    return suses (son (e), pars, incpars);
  }
  case seq_tag: {
    exp t = son (son (e));
    ans = suses (bro (son (e)), pars, incpars);
    for (;;) {
      maxsp (&ans, suses (t, pars,incpars));
      if (t->last) {
	return ans;
      }
      t = bro (t);
    }
  }
  case env_offset_tag :
  case 0 : 
  case goto_tag : 
  case val_tag :
  case special_tag :
  case null_tag : 
  case real_tag : 
  case string_tag : 
  case clear_tag : 
  case current_env_tag :
  case top_tag : {
    break;
  }
  case apply_general_tag:
  case tail_call_tag:
  {
    maxsp(&ans,*pars);
    goto def1;
  }
  
  case apply_tag: {
    /* proc call preserves s-regs; however must make sure that any
	   pars destined for s-regs get there */
    exp dad = father(e);
    if (dad->tag==res_tag && props(dad)) {
      /* tl recursion  - don't have to dump link or later regs */
      int i;
      exp p = bro(son(e));
      if (son(e)->last || p->tag==top_tag) return ans;
      for(i=(incpars>6)?incpars:6; ; i++) {
	if (!valregable(sh(p))) i=22;
	maxsp(&ans, suses(p, pars, i));
	if(p->last) return ans;
	p = bro(p);
      }
    } else 	maxsp (&ans, *pars);
  }				/* else cont to default */
  FALL_THROUGH;
  default: def1:{
    exp t = son (e);
    maxsp (&ans, suses (t, pars,incpars));
    while (t!=NULL && !t->last) {
      t = bro (t);
      maxsp (&ans, suses (t, pars,incpars));
    }
  }
  }
  return ans;
}

static bool
sameregs(space *a, space *b)
{
  return (a -> fixed | b -> fixed) == b -> fixed && (a -> flt | b -> flt) == b -> flt;
}

static space
remd(space *tobd, space *dmpd)
{
  /* any regs left out of tobd after dmpd has been done */
  space ans;
  ans.fixed = tobd -> fixed & ~dmpd -> fixed;
  ans.flt = tobd -> flt & ~dmpd -> flt;
  return ans;
}




/* 
   replace exp in pe by new dump with props = fixeds and 
   no = flts to be dumped ; thread different dumps to same rsc 
   via pt; delivers bool to say whether all sregs have been 
   dumped 
*/
static bool
placedump(exp *pe, space *dmpd, space *tobd, space *nds)
{
  exp e = *pe;
  exp dflt = getexp(NULL, NULL, 1, NULL,NULL, 0, nds->flt & ~dmpd->flt, dump_tag);
  exp dump = getexp (sh (e), bro (e), e->last, e, dflt, 0, (nds -> fixed & ~dmpd -> fixed),
       dump_tag);
  bro (e) = dump;
  e->last = true;
  *(pe) = dump;
  (dmpd -> fixed) |= nds -> fixed;
  (dmpd -> flt) |= nds -> flt;
  return sameregs (tobd, dmpd);
}



/* 
   delivers last exp in seq first after all tests (to second) ; 
   beforeb is space up to end of tests; second only use beforeb;
   otherwise NULL 
*/
static exp
goodcond(exp first, exp second, space *beforeb, space *pars)
{
  exp t;
  space nds;
  int   n = no (son (second));	/* no of uses of labst second */
  if (first->tag != seq_tag)
    return NULL;
  t = son (son (first));
  *beforeb = zsp;
  for (;;) {
    maxsp(beforeb, suses(t, pars, 0));

    if (t->tag == test_tag) {
      if (pt (t) != second)
	return NULL;
      if (--n == 0) break;
    }
    if (t->last) {
     	return NULL;
    }
    t = bro (t);
  }
  nds = suses (second, pars, 0);
  if (sameregs (&nds, beforeb))
    return t;
  return NULL;
}

static bool
alljumps(exp e, exp slv, int *nol)
{
  /* all all branches to labsts of slove_tag slv in e ? */
  recurse:
  switch (e->tag) {
  case case_tag: {
    exp z = bro(son(e));
    for(;;) {
      if (father(pt(z))==slv) {
	if (--(*nol)==0) return 1;
      }
      if (z->last) { e = son(e); goto recurse; }
      z = bro(z);
    }
  }
  case goto_tag: case test_tag: {
    if (father(pt(e))==slv) {
      if (--(*nol)==0) return 1;
    }
    if (e->tag== goto_tag) return 0;
    /* and continue */
  }
  FALL_THROUGH;
  case name_tag: case val_tag: case float_tag: case string_tag:
    return 0;
  default: {
    exp se = son(e);
    if (se==NULL) return 0;
    for(;;) {
      if (se->last) { e = se; goto recurse; }
      if (alljumps(se, slv, nol)) return 1;
      se = bro(se);
    }
  }
  }
}
   


static bool
goodsolve(exp e)
{
  exp m = bro(son(e));
  int nol;
  for(nol=0;;nol++) {
    if (no(son(m))!=1) return 0; /* more than one branch to labst */
    if (m->last) break;
    m = bro(m);
  }
  return alljumps(son(e), e, &nol);
}

static int  notregs;
static int  notfregs;
 /* use to make sure of enough t-regs which are not par regs; I reuse any
    par registers whose pars are put in s-regs as t-regs  */

static void
pushdumps(exp *pe, space *dmpd, space *tobd, space *pars)
{
  /* tries to delay the dumps of the s-regs as late as possible 
     ; pe is the place in the tree to insert any dump found
     necessary in this recursion; dmpd gives the sregs already dumped and
     tobd is all which may have to be dumped; pars give the registers
     containing the initial position of any parameters */

  space nds;
  exp e = *(pe);
  exp *arg;

  switch (e->tag) {
  case ident_tag: {
    nds = suses (son (e), pars,0);
    if ((props (e) & inanyreg) != 0 && no (e) == 0) {
      /*  This definition will be allocated into a t-reg so make sure
	  of enough t-regs which are not par regs; I reuse any par
	  registers whose pars are put in s-regs as t-regs  */
      if (is_floating(sh(son(e))->tag)) {
	if (notfregs-- < 0) {
	  nds = remd (tobd, dmpd);
	  placedump ( pe, dmpd, tobd, &nds);
	  return;
	}
      }
      else {
	if (notregs-- < 0) {
	  nds = remd (tobd, dmpd);
	  placedump ( pe, dmpd, tobd, &nds);
	  return;
	}
      }
    }
    if (son(e)->tag != clear_tag || 
	(isparam(e) && props(son(e))==0 /* ie initially on stack */)  ) {
      /* id could be in s-reg; find from use */
      maxsp (&nds, suses (pt (e), pars, 0));
    }
    if (sameregs (&nds, dmpd) ||
	!placedump ( pe, dmpd, tobd, &nds)) {
      /* not all regs have been dumped - continue with body */
      arg = &bro(son (e));
      pushdumps ( arg, dmpd, tobd, pars);
    }	
    return;
  }
  case seq_tag: {
    exp prev;
    exp list = son (son (e));
    if (list->last ) {
      nds = suses(bro(son(e)), pars, 22);
      if (nds.fixed==0 && nds.flt==0) {
	/* seq consists of two exps with last not using regs */
	pushdumps(&son(son(e)), dmpd, tobd, pars);
	return;
      }
    }
    nds = suses (list, pars, 0);
    if (!sameregs (&nds, dmpd)) {
      /* first statement uses undumped s-regs */
      if (placedump ( pe, dmpd, tobd, &nds)) {
	return;
      }
    }
    prev = list;
    while (!list->last) {
      prev = list;
      list = bro (list);
      nds = suses (list, pars, 0);
      if (!sameregs (&nds, dmpd)) {
	/* uses undumped s-regs; construct new seq as result of this
	   one .... */
	exp s_hold = getexp (sh (e), bro (son (e)), 0, list, NULL, 0, 0, son(e)->tag);
	exp seq = getexp (sh (e), e, 1, s_hold, NULL, 0, 0, seq_tag);
	bro (prev) = son (e);
	prev->last = true;
	bro (son (e)) = seq;
	bro (bro (s_hold)) = seq;
	while (!list->last) {
	  list = bro (list);
	}
	bro (list) = s_hold;
	/* .... and continue with new result */
	arg = &bro(son (e));
	if (!placedump ( arg, dmpd, tobd, &nds)) {
	  pushdumps ( arg, dmpd, tobd, pars);
	}
	return;
      }
    }
    /* no new s-regs used - carry on with result */
    arg = &bro(son (e));
    pushdumps ( arg, dmpd, tobd, pars);
    return;
  }
  case cond_tag: {
    exp first = son (e);
    exp second = bro (first);
    exp t;
    bool same;
    space beforeb;
    nds = suses (first, pars, 0);
    same = sameregs (&nds, dmpd);
    if (!same && (t = goodcond (first, second, &beforeb, pars)) != NULL) {
      /* worth looking further  into first part */
      if (!sameregs(&beforeb, dmpd) ) {
	if (placedump ( pe, dmpd, tobd, &beforeb)) {
	  return;
	}
      }	  	
      if (!t->last) {
	exp seq_hold = getexp (sh (first), bro (son (first)), 0, bro (t), NULL, 0, 0, son(first)->tag);
	exp new = getexp (sh (first), first, 1, seq_hold, NULL, 0, 0, seq_tag);
	exp x = son (seq_hold);
	while (!x->last) {
	  x = bro (x);
	}
	bro (x) = seq_hold;	/* set dad son seq_hold */
	bro (bro (seq_hold)) = new;
	bro (seq_hold)->last = true;/* set dad of seq_hold */
	bro (son (first)) = new;
	t->last = true;
	bro (t) = son (first);
	/* first is now (t; (rest of first)) */
      }
      arg = &bro(son (first));
      pushdumps ( arg, dmpd, tobd, pars);
      return;
    }
    if (!same) {		/* new s-regs used in first part */
      if (placedump ( pe, dmpd, tobd, &nds)) {
	return;
      }
    }
    arg = &bro(son (e));
    pushdumps ( arg, dmpd, tobd, pars);
    return;
  }

/*    case diag_tag: 
    case fscope_tag: 
    case cscope_tag: {
	arg= &son(e);
	pushdumps ( arg, dmpd, tobd, pars);
	return;
      }
*/
  case labst_tag: {		/* can only arrive here from cond */
    arg = &bro(son (e));
    pushdumps ( arg, dmpd, tobd, pars);
    return;
  }
  case solve_tag: {
    if (goodsolve(e)) {
      exp m = bro(son(e));
      space old_dmpd;	
      nds = suses(son(e), pars, 0);
      if (!sameregs(&nds, dmpd)) {
	if (placedump(pe, dmpd,tobd, &nds) ) return;
      }
      old_dmpd = *dmpd;
      for(;;) {
	pushdumps(&bro(son(m)), dmpd, tobd, pars);
	if (m->last) return;
	m = bro(m);
	*dmpd = old_dmpd;
      }
    } /* else continue ... */		
  }
    FALL_THROUGH;
  default: {
      nds = suses(e, pars, 0);
      if (!sameregs(&nds, dmpd)) {
	placedump ( pe, dmpd, tobd, &nds);
      }
    }
  }	
}


void
dump_opt(exp rscope, space *tobd, space *pars)
{
  /* rscope is proc-tag exp;  tobd is set of s-regs to be dumped; 
     pars is subset of tobd which will be used as  parameters of 
     proc */
  exp  * arg;
  space dmpd;
  dmpd = zsp;			/* those regs already dumped */
  arg = &son(rscope);

  notregs = 10;
  notfregs = 8;			/* no of t-regs != par regs */
  if (~optim & OPTIM_DUMP || No_S || sameregs (tobd, &dmpd)) {
    IGNORE placedump( arg, &dmpd, tobd, tobd);
  }
  else {
    IGNORE pushdumps( arg, &dmpd, tobd, pars);
  }
}
