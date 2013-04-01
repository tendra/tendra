/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
  The functions in this file define the scan through a program which
  reorganises it so that all arguments of operations are suitable for
  later code-production.  The procedure scan evaluates the register
  requirements of an exp.  The exps are produced from the decoding
  process and the various exp->exp transformations (common to other
  translators).
*/

#include <assert.h>
#include <string.h>

#include <shared/check.h>

#include "config.h"

#include <reader/externs.h>

#include <construct/exp.h>
#include <construct/tags.h>
#include <construct/shapemacs.h>
#include <construct/flpt.h>
#include <construct/install_fns.h>
#include <construct/flags.h>
#include <construct/me_fns.h>

#include <refactor/const.h>
#include <refactor/optimise.h>

#include "exptypes.h"
#include "expmacs.h"
#include "extra_tags.h"
#include "new_tags.h"
#include "proctypes.h"
#include "bitsmacs.h"
#include "maxminmacs.h"
#include "regable.h"
#include "tempdecs.h"
#include "special.h"
#include "regmacs.h"
#include "muldvrem.h"
#include "translat.h"
#include "comment.h"
#include "needscan.h"
#include "reg_defs.h"
#include "szs_als.h"
#include "makecode.h"
#include "localflags.h"

extern prop notbranch[];

/*
  LOCAL VARIABLES
*/


static int stparam ;		/* Size of parameter list in bits */
static int fixparam ;		/* Next available place for param */

static int rscope_level = 0 ;
static bool nonevis = 1 ;
static bool specialext ;	/* for PIC_code, special globals require proc_uses_external */
static int callerfortr ;

int maxfix, maxfloat ;		/* The maximum numbers of t-regs */
static bool gen_call;   /* true if the scan is within a general proc */
static bool v_proc;     /* true if the scan is within a general proc with vcallees */
static bool trad_proc;	/* true if the scan is within a proc with no callees */

/*
  THE TYPE DESCRIBING REGISTER NEEDS

  The type needs is defined in proctypes.h.  This is a structure 
  which has two integers giving the number of fixed and floating 
  point registers required to contain live values in the expression 
  parameters.  A further field prop is used for various flags about 
  certain forms of exp (mainly idents and procs).  The maxargs 
  field gives the maximum size in bits for the parameters of all 
  the procs called in the exp.  The needs of a proc body are 
  preserved in the needs field of the procrec (see proctypes.h).
*/


/*
  FIND A POINTER TO EXPRESSION POINTING TO e
*/

exp 
*ptr_position ( exp e ){
  exp *res ;
  exp dad = father ( e ) ;
  exp sib = son ( dad ) ;
  if ( sib == e ) {
    res = &son ( dad ) ;
  } 
  else {
    while ( bro ( sib ) != e ) {
      sib = bro ( sib ) ;
    }	
    res = &bro ( sib ) ;
  }
  return res;
}


/*
  INSERT A NEW DECLARATION
  This procedure effectively inserts a new declaration into an exp.
  This is used to stop a procedure requiring more than the available
  number of registers.
*/

void 
cca ( exp ** to, exp * x ){

#ifndef NEWDIAGS
  if (name((**to))==diagnose_tag){
    *to = &(son((**to)));  
  }
#endif
  if ( x == ( *to ) ) {
    /* replace by Let tg = def In tg Ni */
    exp def = *x ;
    exp id = getexp ( sh ( def ), bro ( def ), ( int ) last ( def ),
		      def, nilexp, 0, 1, ident_tag ) ;
    exp tg = getexp ( sh ( def ), id, 1, id, nilexp, 0, 0, name_tag ) ;
    /* use of tag */
    pt ( id ) = tg ;
    /* bro ( def ) is body of Let = tg */
    bro ( def ) = tg ;
    clearlast ( def ) ;
    /* replace pointer to x by Let */
    *x = id ;
#ifdef NEWDIAGS
    if (diag != DIAG_NONE) {
      dgf(id) = dgf(bro(son(id)));
      dgf(bro(son(id))) = nildiag;
    }
#endif
    return ;
  } 
  else {
    /* replace by Let tg = def In ato/def = tg Ni */
    exp def = *x ;
    exp ato = *( *to ) ;
    exp id = getexp ( sh ( ato ), bro ( ato ), ( int ) last ( ato ),
		      def, nilexp, 0, 1, ident_tag ) ;
    exp tg = getexp ( sh ( def ), bro ( def ), ( int ) last ( def ),
		      id, nilexp, 0, 0, name_tag ) ;
    /* use of tg */
    pt ( id ) = tg ;
    /* ato is body of Let */
    bro ( def ) = ato ;
    clearlast ( def ) ;
    /* its father is Let */
    bro ( ato ) = id ;
    setlast ( ato ) ;
    /* replace pointer to 'to' by Let */
    *( *to ) = id ;
    /* replace use of x by tg */
    *x = tg ;
    /* later replacement to same 'to' will be at body of Let */
    *to = &bro ( def ) ;
#ifdef NEWDIAGS
    if (diag != DIAG_NONE) {
      dgf(id) = dgf(bro(son(id)));
      dgf(bro(son(id))) = nildiag;
    }
#endif
  }
  return ;
}


/*
  BASIC REGISTER NEEDS

  This represent the requirements, one fixed point register, 
  two fixed point registers, one floating point register and 
  no registers respectively.
*/

needs onefix = { 1, 0, 0, 0 } ;
needs twofix = { 2, 0, 0, 0 } ;
needs onefloat = { 0, 1, 0, 0 } ;
needs zeroneeds = { 0, 0, 0, 0 } ;


#if 0

/*
  CHECK IF ANY USES OF id ARE AS AN INITIALISER FOR A DECLARATION
*/

bool 
subvar_use ( exp uses )
{
  for ( ; uses != nilexp ; uses = pt ( uses ) ) {
    if ( last ( uses ) && name ( bro ( uses ) ) == cont_tag ) {
      exp c = bro ( uses ) ;
      if ( !last ( c ) && last ( bro ( c ) ) &&
	   name ( bro ( bro ( c ) ) ) == ident_tag ) {
	exp id = bro ( bro ( c ) ) ;
	if ( ( props ( id ) & subvar ) != 0 &&
	     ( props ( id ) & inanyreg ) != 0 ) {
	  return 1;
	}
      }
    }
  }
  return 0;
}

#endif


/*
  WORK OUT REGISTER NEEDS FOR A GIVEN SHAPE
*/

needs 
shapeneeds ( shape s ){
  if ( is_floating ( name ( s ) ) ) {
    return onefloat;
  } 
  else {
    if ( valregable ( s ) ) {
      return onefix;
    } 
    else {
      /* if the shape does not fit into a reg, needs two fixed
	 regs for moving */
      return twofix;
    }
  }
  /* NOT REACHED */
}


/*
  Transform a non-bit offset into a bit offset.
  (borrowed from trans386)
*/
static void 
make_bitfield_offset ( exp e, exp pe, int spe, shape sha ){
  exp omul;
  exp val8;
  if (name(e) == val_tag){
    no(e) *= 8;
    return;
  }
  omul = getexp (sha, bro(e), (int)(last (e)), e, nilexp, 0, 0, offset_mult_tag);
  val8 = getexp (slongsh, omul, 1, nilexp, nilexp, 0, 8, val_tag);
  clearlast(e);
  setbro(e, val8);
  if(spe) {
    son(pe) = omul;
  }
  else{
    bro(pe) = omul;
  }
  return;
}



/*
  IS AN EXPRESSSION COMPLEX?
  An expression is complex if, basically, it cannot be accessed by a
  simple load or store instruction.
*/

bool 
complex ( exp e ){
  if ( name ( e ) == name_tag ||
       ( name ( e ) == cont_tag && name ( son ( e ) ) == name_tag &&
	 isvar ( son ( son ( e ) ) ) ) ||
       name(e) == val_tag || name(e) == real_tag || name(e) == null_tag ) {
    return 0;
  } 
  else {
    return 1;
  }
  /* NOT REACHED */
}

int 
scan_cond ( exp* e, exp outer_id ){

  exp ste = *e;
  exp first = son (ste);
  exp labst = bro (first);
  exp second = bro (son (labst));

  assert(name(ste)==cond_tag);

  if (name(second)==top_tag && name(sh(first))==bothd && no(son(labst))==1
      && name(first)==seq_tag && name(bro(son(first))) == goto_tag){
    /* cond is { ... test(L); ? ; goto X | L:make_top}
       if ? empty can replace by seq { ... not-test(X); make_top }
       */
    exp l = son(son(first));
    while(!last(l)) { l = bro(l); }
    while(name(l)==seq_tag) { l = bro(son(l)); }
    if (name(l)==test_tag && pt(l)==labst) {
      settest_number(l, notbranch[(int)test_number(l)]);
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
	/* if the second operand of 1st test is simple, then 
	   identification could go in a t-teg (!!!NB overloading 
	   of inlined flag!!!).... */
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
    else if (c2 && eq_exp (op21, op22)) {
	 /* ....if second operands of tests are same, identify them */

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
    else if (name (op12) != name_tag
	     && name (op11) == name_tag 
	     && son (op11) == outer_id
	     && eq_exp (son (outer_id), op12)
	     ) {	/* 1st param of test1 is already identified with
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


/*
  WORK OUT REGISTER NEEDS FOR PLUS-LIKE OPERATIONS
  The operation will be n-ary, commutative and associative.
*/

needs 
likeplus ( exp * e, exp ** at ){
  needs a1 ;
  needs a2 ;
  prop pc ;
  exp *br = &son ( *e ) ;
  exp dad = *e ;
  exp prev ;
  bool commuted = 0 ;

  /* scan the first operand - won't be a val_tag */
  a1 = scan ( br, at ) ;

  /* likeplus exp with 1 operand should never occur */
  assert ( !( last ( *br ) ) ) ;

  do {
    exp *prevbr ;
    prevbr = br ;
    prev = *br ;
    br = &bro ( prev ) ;
    a2 = scan ( br, at ) ;
    /* scan the next operand ... */
    if ( name ( *br ) != val_tag ) {
      a1.floatneeds = MAX_OF ( a1.floatneeds, a2.floatneeds ) ;
      pc = ( prop ) ( a2.prps & hasproccall ) ;
      if ( a2.fixneeds < maxfix && pc == 0 ) {
	/*... its evaluation will not disturb the accumulated result */
	a1.fixneeds = MAX_OF ( a1.fixneeds, a2.fixneeds + 1 ) ;
	a1.prps = ( prop ) ( a1.prps | a2.prps ) ;
      } 
      else if ( a1.fixneeds < maxfix &&
		pntst ( a1, hasproccall ) == 0 &&
		!commuted ) {
	/* ...its evaluation will call a proc, so put it first */
	exp op1 = son ( dad ) ;
	exp cop = *br ;
	bool lcop = ( bool ) last ( cop ) ;
	bro ( prev ) = bro ( cop ) ;
	if ( lcop ) setlast ( prev ) ;
	bro ( cop ) = op1 ;
	clearlast ( cop ) ;
	son ( dad ) = cop ;
	br = ( prev == op1 ) ? &bro ( cop ) : prevbr ;
	commuted = 1 ;
	a1.fixneeds = MAX_OF ( a2.fixneeds, a1.fixneeds + 1 ) ;
	pnset ( a1, a2.prps ) ;
	a1.maxargs = MAX_OF ( a1.maxargs, a2.maxargs ) ;
      } 
      else {
	/* evaluation would disturb accumulated result, so replace
	   it by a newly declared tag */
	cca ( at, br ) ;
	a1.fixneeds = MAX_OF ( a1.fixneeds, 2 ) ;
	pnset ( a1, morefix | ( pc << 1 ) ) ;
	a1.maxargs = MAX_OF ( a1.maxargs, a2.maxargs ) ;
      }
    } else {
      /* nothing */
    }
  } while ( !last ( *br ) ) ;

#if 1
  /* exception handling regs (from mips) */
  if ( !optop ( *e ) ) {
    if ( a1.fixneeds < 4 ) a1.fixneeds = 4 ;
  }
#endif
  return a1;
}


/*
  WORK OUT REGISTER NEEDS FOR DIVIDE-LIKE OPERATIONS
  The operation will be binary and non-commutative.
*/

needs 
likediv ( exp * e, exp ** at ){
  needs l ;
  needs r ;
  prop pc ;
  exp *arg = &son ( *e ) ;

  l = scan ( arg, at ) ;
  /* scan 1st operand */
  arg = &bro ( *arg ) ;
  r = scan ( arg, at ) ;
  /* scan second operand ... */
  l.floatneeds = MAX_OF ( l.floatneeds, r.floatneeds ) ;

  pc = ( prop ) ( r.prps & hasproccall ) ;
  if ( r.fixneeds < maxfix && pc == 0 ) {
    /* fits into registers */
    l.fixneeds = MAX_OF ( l.fixneeds, r.fixneeds + 1 ) ;
    pnset ( l, r.prps ) ;
  } 
  else {
    /* requires new declaration of second operand */
    cca ( at, arg ) ;
    l.fixneeds = MAX_OF ( l.fixneeds, 1 ) ;
    pnset ( l, morefix | ( pc << 1 ) ) ;
    l.maxargs = MAX_OF ( l.maxargs, r.maxargs ) ;
  }

#if 1
  /* exception handling regs (from mips) */
  if ( !optop ( *e ) ) {
    if ( l.fixneeds < 4 ) l.fixneeds = 4 ;
  }
#endif
  return l;
}


/*
  WORK OUT REGISTER NEEDS FOR FLOATING-POINT OPERATIONS
  The operation will be binary.
*/

needs 
fpop ( exp * e, exp ** at ){
  needs l ;
  needs r ;
  exp op = *e ;
  prop pcr, pcl ;
  exp *arg = &son ( op ) ;

  l = scan ( arg, at ) ;
  arg = &bro ( *arg ) ;
  r = scan ( arg, at ) ;
  l.fixneeds = MAX_OF ( l.fixneeds, r.fixneeds ) ;
  pcr = ( prop ) ( r.prps & hasproccall ) ;
  pcl = ( prop ) ( l.prps & hasproccall ) ;

  if ( use_long_double && name ( sh ( son ( op ) ) ) == doublehd ) {
    ClearRev ( op ) ;
    arg = &son ( op ) ;
    if ( !is_o ( name ( *arg ) ) || pcl ) cca ( at, arg ) ;
    arg = &bro ( son ( op ) ) ;
    if ( !is_o ( name ( *arg ) ) || pcr ) cca ( at, arg ) ;
    l.floatneeds = MAX_OF ( l.floatneeds, r.floatneeds ) ;
    l.maxargs = MAX_OF ( l.maxargs, r.maxargs ) ;
    pnset ( l, hasproccall ) ;
    return l;
  }

  if ( r.floatneeds <= l.floatneeds &&
       r.floatneeds < maxfloat && pcr == 0 ) {
    l.floatneeds = MAX_OF ( l.floatneeds, r.floatneeds + 1 ) ;
    l.floatneeds = MAX_OF ( 2, l.floatneeds ) ;
    pnset ( l, r.prps ) ;
    ClearRev ( op ) ;
  } 
  else if ( pcl == 0 && l.floatneeds <= r.floatneeds &&
	    l.floatneeds < maxfloat ) {
    l.floatneeds = MAX_OF ( r.floatneeds, l.floatneeds + 1 ) ;
    l.floatneeds = MAX_OF ( 2, l.floatneeds ) ;
    pnset ( l, r.prps ) ;
    SetRev ( op ) ;
  } 
  else if ( r.floatneeds < maxfloat && pcr == 0 ) {
    l.floatneeds = MAX_OF ( l.floatneeds, r.floatneeds + 1 ) ;
    l.floatneeds = MAX_OF ( 2, l.floatneeds ) ;
    pnset ( l, r.prps ) ;
    ClearRev ( op ) ;
  } 
  else {
    cca ( at, arg ) ;
    ClearRev ( op ) ;
    l.floatneeds = MAX_OF ( l.floatneeds, 2 ) ;
    pnset ( l, morefloat | ( pcr << 1 ) ) ;
    l.maxargs = MAX_OF ( l.maxargs, r.maxargs ) ;
  }
  return l;
}


/*
  WORK OUT THE MAXIMUM OF TWO REGISTER NEEDS
*/

needs 
maxneeds ( needs a, needs b ){
  needs an ;
  an.fixneeds = MAX_OF ( a.fixneeds, b.fixneeds ) ;
  an.floatneeds = MAX_OF ( a.floatneeds, b.floatneeds ) ;
  an.maxargs = MAX_OF ( a.maxargs, b.maxargs ) ;
  an.callee_size = MAX_OF(a.callee_size,b.callee_size);
  an.prps = ( prop ) ( a.prps | b.prps ) ;
  return an;
}


/*
  WORK OUT THE REGISTER NEEDS OF A TUPLE OF EXPRESSIONS
*/

needs 
maxtup ( exp e, exp ** at ){
  exp *s = &son ( e ) ;
  needs an ;
  an = zeroneeds ;
  if( *s == nilexp) return an;
  while (an = maxneeds (an, scan (s, at)), !last(*s) ) {
    s = &bro(*s);
  }
  return an;


  /* NOT REACHED */
}


/*
  IS A VALUE UNCHANGED OVER ITS SCOPE?

  This routine finds if usedname is only used in cont operation or as
  result of ident.
*/

bool 
unchanged ( exp usedname, exp ident ){
  exp uses = pt ( usedname ) ;
  while ( uses != nilexp ) {
    if ( intnl_to ( ident, uses ) ) {
      if ( !last ( uses ) || name ( bro ( uses ) ) != cont_tag ) {
	exp z = uses ;
	while ( z != ident ) {
	  if ( !last ( z ) || ( name ( bro ( z ) ) != seq_tag &&
				name ( bro ( z ) ) != ident_tag ) ) {
	    return 0;
	  }
	  z = bro ( z ) ;
	}
      }
    }
    uses = pt ( uses ) ;
  }
  return 1;
}


/*
  CHASE STRUCTURE PROCEDURE RESULTS
  The SPARC convention for delivering a struct from a procedure is
  to have an extra pointer parameter in the proc; this means that 
  there must always be space in the calling work-space for the 
  result struct whether or not the value is used e.g. as in 
  f ( x ) or f ( x ).a etc.  This procedure is part of the 
  mechanism to determine whether it is necessary to insert a dummy 
  declaration to ensure that this space exists.
*/

bool 
chase ( exp sel, exp * e ){
  exp *one ;
  bool b = 0 ;

  switch ( name ( *e ) ) {

    case rep_tag :
    case ident_tag :
    case seq_tag :
    case labst_tag : {
      b = chase ( sel, &bro ( son ( *e ) ) ) ;
      break ;
    }

    case solve_tag :
    case cond_tag : {
      one = &son ( *e ) ;
      for ( ; ; ) {
	b = ( bool ) ( b | chase ( sel, one ) ) ;
	if ( last ( *one ) ) break ;
	one = &bro ( *one ) ;
      }
      break ;
    }

    case field_tag : {
      if ( chase ( *e, &son ( *e ) ) ) {
	/* inner field has been distributed */
	exp stare = *e ;
	exp ss = son ( stare ) ;
	if ( !last ( stare ) ) clearlast ( ss ) ;
	bro ( ss ) = bro ( stare ) ;
	sh ( ss ) = sh ( stare ) ;
	*e = ss ;
	return chase ( sel, e ) ;
      }
      /* FALL THROUGH */
    }

    default : {
      if ( (son ( sel ) != *e) && (name (sh(*e)) != bothd)) {
	/* only change if not outer */
	exp stare = *e ;
	exp newsel = getexp ( sh ( sel ), bro ( stare ),
			      ( int ) last ( stare ), stare,
			      nilexp, props ( sel ), no ( sel ),
			      name ( sel ) ) ;
	*e = newsel ;
	bro ( stare ) = newsel ;
	setlast ( stare ) ;
	b = 1 ;
      }
    }
  }
  if ( b ) sh ( *e ) = sh ( sel ) ;
  return b;
}


exp 
need_result_space ( exp e ) {
	/* dad if application needs to reserve space for struct result */
  exp dad = father ( e );
  switch (name (dad)) {
    case 0:	/* void in sequence, or param of apply_gen */
    case apply_tag:
    case caller_tag:
    case field_tag:
      return dad;
    case ident_tag:
      if (e == son (dad))
	return nilexp;
      return need_result_space (dad);
    case rep_tag:
      if (e == son (dad))
	return dad;
      /* else fall through */
    case cond_tag:
    case solve_tag:
    case labst_tag:
    case seq_tag:
#ifndef NEWDIAGS
    case diagnose_tag:
#endif
      return need_result_space (dad);
    default:
      return nilexp;
  }
}


bool 
spin_lab  ( exp lab ) {
	/* true if label implies a tight spin */
  exp dest = lab;
  exp temp, ll;
  for (;;) {
    assert (name(dest) == labst_tag);
    temp = bro(son(dest));
    if (temp == nilexp || name(temp) != goto_tag)
      return 0;
    ll = lab;
    for (;;) {
      if (pt(temp) == ll)
	return 1;
      if (ll == dest)
	break;
      ll = pt(bro(son(ll)));
    }
    dest = pt(temp);
  };
  return 0;
}
  
/* Check for legal conditions for asm */

static void 
id_in_asm ( exp id )
{
  if (!isparam(id) || !props(son(id)))
    setvis (id);
  return;
}
		       
static int 
is_asm_opnd ( exp e, int ext )
{
  unsigned char n = name (e);
  if (n == name_tag) {
    id_in_asm (son(e));
    return 1;
  }
  if (n == cont_tag && name(son(e)) == name_tag && isvar(son(son(e)))) {
    id_in_asm (son(son(e)));
    return 1;
  }
  return n == val_tag || n == real_tag || n == null_tag ||
	(n == reff_tag && name(son(e)) == name_tag);
}

static int 
is_asm_var ( exp e, int ext )
{
  unsigned char n = name (e);
  if (n == name_tag && isvar(son(e))) {
    id_in_asm (son(e));
    return 1;
  }
  return 0;
}

void 
check_asm_seq ( exp e, int ext )
{
  if (name(e) == asm_tag) {
    if ((asm_string(e) && name(son(e)) == string_tag) ||
	(asm_in(e) && is_asm_opnd(son(e), ext)) ||
	(asm_var(e) && is_asm_var(son(e), ext)) )
      return;
  }
  if (name(e) == seq_tag) {
    exp t = son(son(e));
    for (;;) {
      check_asm_seq (t, ext);
      if (last(t))
	break;
      t = bro(t);
    }
    check_asm_seq (bro(son(e)), ext);
  }
  else
  if (name(e) != top_tag)
    fail ("illegal ~asm");
  return;
}





/*
  SCAN AN EXPRESSION TO CALCULATE REGISTER NEEDS

  This procedure works out register requirements of an exp.  At each
  call the fix field of the needs is the number of fixed point 
  registers required to contain live values to evaluate this 
  expression.  This never exceeds maxfix because if it would have, 
  a new declaration is introduced in the exp tree (similarly for 
  floating registers and maxfloat).  In these cases the prop field 
  will contain the bits morefix (or morefloat).
  
  Scan also works out various things concerned with proc calls.
  The maxargs field contains the maximum size in bits of the space
  required for the parameters of all the procedures called in the 
  exp.

  An exp proc call produces a hasproccall bit in the prop field, if
  this is transformed as part of the definition of a new declaration
  the bit is replaced by a usesproccall. The distinction is only used
  in unfolding nested proc calls; SPARC requires this to be done
  statically. The condition that a proc exp is a leaf (i.e. no proc 
  calls) is that its prop contains neither bit.  If an ident exp 
  is suitable, scan marks the props of ident with either inreg or 
  infreg bits to indicate that a t-reg may be used for this tag.
  
  A thorough understanding of needs along with other procedures that
  do switch ( name ( exp ) ) requires a knowledge of the meaning of
  the fields of the exp in each case (this is documented somewhere).
*/

needs 
scan ( exp * e, exp ** at ){
  /* e is the expression to be scanned, at is the place to put any
     new decs.  The order of recursive calls with same at is 
     critical. */

  exp ste = *e ;
  int nstare = ( int ) name ( ste ) ;

#if 0
  /* ignore diagnostic information */
  while ( nstare == diag_tag || nstare == cscope_tag ||
	  nstare == fscope_tag ) {
    e = &son ( ste ) ;
    ste = *e ;
    nstare = name ( ste ) ;
  }
#endif

  switch ( nstare ) {

    case 0 : {
      return zeroneeds;
    }
#if 0
    case compound_tag : {
      return maxtup ( ste, at ) ;
    }
#else
    case compound_tag :
#endif
    case nof_tag :
    case concatnof_tag :
    case ncopies_tag : {
      needs nl ;
      bool cantdo ;
      exp dad ;
      if ( name ( ste ) == ncopies_tag &&
	   name ( son ( ste ) ) != name_tag &&
	   name ( son ( ste ) ) != val_tag ) {
	nl = scan ( &son ( *e ), at ) ;
	cca ( at, &son ( *e ) ) ;
      } 
      else {
	nl = maxtup ( *e, at ) ;
      }
      dad = father ( ste ) ;

      if ( name ( dad ) == compound_tag ||
	   name ( dad ) == nof_tag ||
	   name ( dad ) == concatnof_tag ) {
	cantdo = 0 ;
      } 
      else {
	if ( last ( ste ) ) {
	  if ( name ( bro ( ste ) ) == ass_tag ) {
	    exp a = son ( bro ( ste ) ) ;
	    cantdo = ( bool ) ( name ( a ) != name_tag ||
				!isvar ( son ( a ) ) ) ;
	  } 
	  else {
	    cantdo = 1 ;
	  }
	} 
	else {
	  if ( last ( bro ( ste ) ) ) {
	    cantdo = ( bool ) ( name ( bro ( bro ( ste ) ) ) !=
				ident_tag ) ;
	  } 
	  else {
	    cantdo = 1 ;
	  }
	}
      }

      if ( cantdo ) {
	/* can only deal with tuples in simple assignment or id */
	int prpsx = ( int ) ( pntst ( nl, hasproccall ) << 1 ) ;
	cca ( at, ptr_position ( ste ) ) ;
	nl = shapeneeds ( sh ( *e ) ) ;
	pnset ( nl, morefix ) ;
	pnset ( nl, prpsx ) ;
      }

      if ( nl.fixneeds < 2 ) nl.fixneeds = 2 ;
      return nl;
    }

    case cond_tag : {
/*	    exp first = son ( ste ) ;
	    exp labst = bro ( first ) ;
	    exp second = bro ( son ( labst ) ) ; */

      if (scan_cond(e, nilexp) !=0) {
	return scan(e, at);
      }			/* else goto next case */
    }
    /* FALL THROUGH */

    case labst_tag :
    case rep_tag :
    case solve_tag : {
      needs an ;
      exp *stat ;
      exp *statat ;
      stat = &son ( *e ) ;
      statat = stat ;
      an = zeroneeds ;
      while ( an = maxneeds ( an, scan ( stat, &statat ) ),
	      !last ( *stat ) ) {
	stat = &bro ( *stat ) ;
	statat = stat ;
      }
      if ( pntst ( an, usesproccall ) != 0 ) {
	pnset ( an, hasproccall ) ;
      }
      return an;
    }

    case ident_tag : {
      needs bdy ;
      needs def ;
      exp stare = *e ;
      exp *arg = &bro ( son ( stare ) ) ;
      exp t, s ;
      bool fxregble ;
      bool flregble ;
      bool old_nonevis = nonevis ;
      if ( no ( stare ) == 0 ) {
	/* no uses, should have caonly flag and no var flag */
	setcaonly ( stare ) ;
	clearvar ( stare ) ;
#ifdef NEWDIAGS
	t = pt (stare);
	while (t) {
	  assert (isdiaginfo (t));
	  setdiscarded (t);
	  t = pt(t);
	}
#endif
      }

      if ( isvar ( stare ) && ( !iscaonly ( stare ) ||
				all_variables_visible ) ) {
	setvis ( stare ) ;
      }

      if (name(son(stare)) == formal_callee_tag) {
	setvis(stare);
      }
      

      if ( isparam ( stare ) && name(son(stare))!= formal_callee_tag) {
	/* Use the input regs %i0..%i5 for first 6*32 bits of params */
	exp def2 = son ( stare ) ;
	shape shdef = sh ( def2 ) ;
	int n = stparam ;
	int sizep = ( int ) shape_size ( shdef ) ;
	int last_reg;
	if ((gencompat && !trad_proc) || (!gencompat && gen_call)) {
	  if(v_proc) {
	    last_reg = 4;
	  }
	  else {
	    last_reg = 5;
	  }
	}
	else {
	  last_reg = 6;
	}
	assert ( name ( def2 ) == clear_tag ) ;
	if ( ( stparam >> 5 ) < ( last_reg ) /*&& !(isenvoff(stare))*/ ) {
	  /* Param regs %i0..%i5 */
	  /* is >= 1 param reg free for (part-of) the param */
	  /* Use an available param reg */
	  if(v_proc && (stparam>>5)==last_reg) {
	    /* reserve R_I5 for use as local reg */
	    props(def2) = 0;
	    stparam += 32;
	    n = stparam;
	  }
	  else {
	    props ( def2 ) = ( prop ) fixparam ;
	  }
	} 
	else {
	  /* Pass by stack */
	  /* envoffset'ed this way always */
	  props ( def2 ) = 0 ;
	}
	/* "offset" in params */
	no ( def2 ) = n ;
	stparam = rounder ( n + sizep, 32 ) ;
	/* ( stparam / 32 ) */
	fixparam = R_I0 + ( stparam >> 5 ) ;
      }
      else if(isparam(stare) && name(son(stare)) == formal_callee_tag){
	exp def2 = son(stare);
	exp shdef = sh(def2);
	int sizep = shape_size(shdef);
	int alp = shape_align(shdef);
	int n = rounder(callee_size,alp);
	no(def2) = n;
	callee_size = rounder(n+sizep,32);
	props(def2) = 0;
      }
    
      nonevis = ( bool ) ( nonevis & !isvis ( stare ) ) ;

      bdy = scan ( arg, &arg ) ;
#if NO_TREG
      /* force minimal t-reg usage */
      bdy.fixneeds = maxfix ;
#endif
      /* scan the body-scope */
      arg = &son ( stare ) ;
      /* scan the initialisation of tag */
      def = scan ( arg, &arg ) ;

      nonevis = old_nonevis ;
      t = son ( stare ) ;
      s = bro ( t ) ;
      fxregble = fixregable ( stare ) ;
      flregble = floatregable ( stare ) ;

      if ( isparam ( stare ) ) {
	if(name(son(stare)) != formal_callee_tag){
	  /* reg for param or else 0 */
	  int x = ( int ) props ( son ( stare ) ) ;
	  /* bit size of param */
	  int par_size = shape_size ( sh ( son ( stare ) ) ) ;
	  if ( par_size == 8 || par_size == 16 ) {
	    /* on to right end of word */
	    no ( son ( stare ) ) += 32 - par_size ;
	  }
	  if ( x != 0 && fxregble ) {
	    /* leave suitable pars in par regs */
	    no ( stare ) = x ;
	    pset ( stare, inreg_bits ) ;
	  } 
	  else {
	    if ( x != 0 && flregble ) {
	      /* Caller has placed float param in par regs;
		 callee must store it out for use in float regs */
	      no ( stare ) = 0 ;
	    } 
	    else {
	      /* Otherwise caller has placed param on stack */
	      no ( stare ) = R_NO_REG ;
	    }
	  }
	}
	else
	  no(stare) = R_NO_REG;
      } 
      else {
	if ( !isvis ( *e ) && isparam ( *e ) && !isoutpar(stare) &&
	     pntst ( bdy, anyproccall | uses_res_reg_bit ) == 0 &&
	     ( fxregble || flregble ) &&
	     ( ((name (t)==apply_tag) || (name(t)==apply_general_tag)) ||
	       ( name ( s ) == seq_tag &&
		 name ( bro ( son ( s ) ) ) == res_tag &&
		 name ( son ( bro ( son ( s ) ) ) ) == cont_tag &&
		 isvar ( stare ) &&
		 name ( son ( son ( bro ( son ( s ) ) ) ) ) ==
		 name_tag &&
		 son ( son ( son ( bro ( son ( s ) ) ) ) ) ==
		 stare ) ) ) {
	  /* Let a : = .. ; return cont a */
	  /* integrate this with the block above,
	     otherwise NOTREACHED */
	  /* put tag in result reg if definition is call of proc,
	     or body ends with return tag, provided result is not
	     used otherwise */
	  pset ( stare, ( fxregble ? inreg_bits : infreg_bits ) ) ;
	  pnset ( bdy, uses_res_reg_bit ) ;
	  /* identification uses result reg in body */
	  no ( stare ) = R_USE_RES_REG ;
	}
	else if (isenvoff(stare)) /* MUST go on stack */	  {
	  no ( stare ) = R_NO_REG ;
	} 
	else if ( !isvar ( *e ) && !isparam ( *e ) &&
		  /* reff cont variable-not assigned to in scope */
		  ( ( name ( t ) == reff_tag &&
		      name ( son ( t ) ) == cont_tag &&
		      name ( son ( son ( t ) ) ) == name_tag &&
		      isvar ( son ( son ( son ( t ) ) ) ) &&
		      !isvis ( son ( son ( son ( t ) ) ) ) &&
		      !isglob ( son ( son ( son ( t ) ) ) ) &&
		      unchanged ( son ( son ( son ( t ) ) ),
				  stare ) ) ||
		    /* cont variable - not assigned to in scope */
		    ( name ( t ) == cont_tag &&
		      name ( son ( t ) ) == name_tag &&
		      isvar ( son ( son ( t ) ) ) &&
		      !isvis ( son ( son ( t ) ) ) &&
		      !isglob ( son ( son ( t ) ) ) &&
		      unchanged ( son ( son ( t ) ),
				  stare ) ) ) ) {
	  /* don't take space for this dec */
	  pset ( stare, defer_bit ) ;
	  } 
	else if ( !isvar ( stare ) &&
		  ( ( props ( stare ) & 0x10 ) == 0 ) &&
		  ( name ( t ) == name_tag ||
		    name ( t ) == val_tag ) ) {
	  /* don't take space for this dec */
	  pset ( stare, defer_bit ) ;
	  } 
	else if ( fxregble &&
		  pntst(bdy,morefix)==0 &&
		  (bdy.fixneeds < maxfix &&
		   ( /*isinlined(stare) ||*/
		     pntst ( bdy, morefix ) == 0 &&
		     ( pntst ( bdy, anyproccall ) == 0 ||
		       tempdec ( stare, ( bool )
				 ( pntst ( bdy, morefix ) == 0 &&
				   bdy.fixneeds < maxfix_tregs - 2 ))))))
	  {
	    /* put this tag in some fixpt t-reg - which will be
	       decided in make_code */
	    pset ( stare, inreg_bits ) ;
	    no ( stare ) = 0 ;
	    bdy.fixneeds += 1 ;
	    } 
	else if ( bdy.floatneeds < maxfloat &&
		  pntst ( bdy, morefloat ) == 0 &&
		  flregble &&
		  ( pntst ( bdy, anyproccall ) == 0 ||
		    tempdec ( stare, ( bool )
			      ( pntst ( bdy, morefloat ) == 0 &&
				bdy.floatneeds < MAXFLOAT_TREGS - 1 ) ) ) ) {
	  /* put this tag in some float t-reg - which will be
	     decided in make_code */
	  pset ( stare, infreg_bits ) ;
	  no ( stare ) = 0 ;
	  bdy.floatneeds += 1 ;
				/* add isinlined when you enable float
				   reg allocation.... */
	} 
	else {
	  /* allocate either on stack or saved reg */
	  no ( stare ) = R_NO_REG ;
	}
      }
      bdy = maxneeds ( bdy, def ) ;
      if ( pntst ( bdy, usesproccall ) != 0 ) {
	pnset ( bdy, hasproccall ) ;
      }
      return bdy;
    }

    case seq_tag : {
      exp *arg = &bro ( son ( *e ) ) ;
      needs an ;
      exp *stat ;
      an = scan ( arg, &arg ) ;
      stat = &son ( son ( *e ) ) ;

      arg = stat ;
      for ( ; ; ) {
	needs stneeds ;
	stneeds = scan ( stat, &arg ) ;
	/* initial statements voided */
	an = maxneeds ( an, stneeds ) ;
	if ( last ( *stat ) ) {
	  if ( pntst ( an, usesproccall ) != 0 ) {
	    pnset ( an, hasproccall ) ;
	  }
	  return an;
	}
	stat = &bro ( *stat ) ;
	arg = stat ;
      }
      /* NOT REACHED */
    }

    case goto_tag : {
      needs nr ;
      nr = zeroneeds ;
      if (!sysV_assembler && spin_lab (pt(*e))) {
	pnset ( nr, dont_optimise ) ;		/* otherwise the SunOS assembler spins */
      }
      return nr;
    }
    case ass_tag :
    case assvol_tag : {
      exp *lhs = &son ( *e ) ;
      exp *rhs = &bro ( *lhs ) ;
      needs nr ;
      ash a ;

      /* scan source */
      nr = scan ( rhs, at ) ;

      a = ashof ( sh ( *rhs ) ) ;
      if ( nstare != ass_tag || a.ashsize != a.ashalign ||
	   a.ashalign == 1 ) {
	/* struct/union assign */
	if ( !( a.ashsize <= 32 && a.ashsize == a.ashalign ) ) {
	  /* memory block copy */
	  nr.fixneeds += 2 ;
	}
      }

      if ( name ( *lhs ) == name_tag &&
	   ( isvar ( son ( *lhs ) ) ||
	     ( pntst ( nr, hasproccall | morefix ) == 0 &&
	       nr.fixneeds < maxfix ) ) ) {
	/* simple destination */
	return nr;
      } 
      else {
	needs nl ;
	prop prpx = ( prop ) ( pntst ( nr, hasproccall ) << 1 ) ;

	nl = scan ( lhs, at ) ;
	if ( (name(*rhs)==apply_tag || name(*rhs)==apply_general_tag) && 
	     nstare==ass_tag && pntst(nl,uses_res_reg_bit|anyproccall)==0) {
	  /* source is proc call, so assign result reg directly */
	  /* SKIP */ ;
	} 
	else if ( nr.fixneeds >= maxfix || prpx != 0 ) {
	  /* source and dest regs overlap, so identify source */
	  cca ( at, rhs ) ;
	  nl = shapeneeds ( sh ( *rhs ) ) ;
	  pnset ( nl, morefix ) ;
	  pnclr ( nl, ( prpx >> 1 ) ) ;
	  pnset ( nl, prpx ) ;
	}
	nr.fixneeds += 1 ;
	return maxneeds ( nl, nr ) ;
      }
    }
    case untidy_return_tag :
    case res_tag : {
      ash a ;
      needs x ;
      shape s ;
      exp *arg = &son ( *e ) ;

      s = sh ( *arg ) ;
      a = ashof ( s ) ;
      /* clear possibility of tlrecirsion ; may be set later */
      props ( *e ) = 0 ;
      x = scan ( arg, at ) ;
      /* scan result exp ... */
      if ( is_floating ( name ( s ) ) && a.ashsize <= 64 ) {
	/* ... floating pt result */
	pnset ( x, realresult_bit ) ;
	if ( name ( s ) != shrealhd ) {
	  pnset ( x, longrealresult_bit ) ;
	}
      } 
      else {
	if ( !valregable ( s ) && name ( s ) != tophd ) {
	  /* ... result does not fit into reg */
	  pnset ( x, long_result_bit ) ;
	}
      }

      if ( a.ashsize != 0 && name ( *arg ) != clear_tag ) {
	/* ...not a void result */
	pnset ( x, has_result_bit ) ;
      }

#if 0
      /* replace R_USE_RES_REG (from mips) by R_USE_R_I0 (here)
	 and R_USE_RO0 (ident_tag above) */
      /* for present R_USE_RES_REG means R_USE_R_O0 */
      /* MIPS has single res reg, on SPARC it is windowed per-proc */
      if ( pntst ( x, ( long_result_bit | anyproccall |
			uses_res_reg_bit ) ) == 0 ) {
	r = son ( *e ) ;
	if ( name ( r ) == ident_tag && isvar ( r ) &&
	     name ( ss = bro ( son ( r ) ) ) == seq_tag &&
	     name ( t = bro ( son ( ss ) ) ) == cont_tag &&
	     name ( son ( t ) ) == name_tag &&
	     son ( son ( t ) ) == r ) {
	  /* result is tag allocated into result reg - see ident */
	  if ( ( props ( r ) & inreg_bits ) != 0 ) {
	    x.fixneeds-- ;
	  } 
	  else if ( ( props ( r ) & infreg_bits ) != 0 ) {
	    x.floatneeds-- ;
	  } 
	  else {
	    props ( r ) |= ( is_floating ( name ( s ) ) ) ?
	      infreg_bits : inreg_bits ;
	  }
	  pnset ( x, uses_res_reg_bit ) ;
	  /* identification uses result reg in body */
	  no ( r ) = R_USE_RES_REG ;
	}
      }
#endif
      return x;
    }
    case apply_general_tag : {
      exp application = *(e);
      exp *fn = &son(application);
      exp callers = bro(*fn);
      exp *cerl = &son(callers);
      int stpar = 0;
      needs nds,pstldnds;
      int i;
      nds = scan(fn,at);
      if(pntst(nds,hasproccall)!=0){	/* Identify it */
	cca(at,fn);
	pnclr(nds,hasproccall);
	pnset(nds,usesproccall);
	fn = &son(application);
      }
      for(i=0;i<no(callers);++i){
	needs onepar;
	shape shonepar = sh(*cerl);
	exp * par = (name(*cerl)==caller_tag)?&son(*cerl):cerl;
	int n = rounder(stpar + shape_size(shonepar), 32);
	onepar = scan(par,at);
	
	if((/*(i != 0) && */pntst(onepar,hasproccall)!=0) || 
	   (onepar.fixneeds+(stpar>>5) > maxfix)){
	  /* not the first parameter, and calls a proc */
	  /* or the first if we need to preserve callee_start_reg */
	  cca(at,par);
	  pnset(nds,usesproccall);
	  nds = maxneeds(shapeneeds(sh(*(par))),nds);
	  nds.maxargs = max(nds.maxargs,onepar.maxargs);
	}
	else{
	  nds = maxneeds(onepar,nds);
	}

	if(name(*cerl) == caller_tag){
	  no(*cerl) = stpar;
	}

	stpar = n;
	cerl = &bro(*cerl);
      }
      nds.maxargs = max(nds.maxargs,stpar);
      maxfix -= 6;
      nds = maxneeds(scan(&bro(bro(son(application))),at),nds);
      maxfix += 6;
      pstldnds = scan(&bro(bro(bro(son(application)))),at);
      if(pntst(pstldnds,anyproccall)!=0){
	set_postlude_has_call(application);
      }
      else{
	clear_postlude_has_call(application);
      }
      nds = maxneeds(nds,pstldnds);
      if ( sparccpd (sh(application)) ) {
	exp ap_context = need_result_space(application);
	if (ap_context != nilexp) {
	  /* find space for tuple result */
	  assert ( name ( *( ptr_position ( application ) ) ) == apply_general_tag ) ;
	  cca ( at, ptr_position ( application ) ) ;
	  if (name(ap_context) != field_tag) {
		/* if context is application parameter, treat as pointer */
	    setvar (bro(bro(application)));
	    sh(pt(bro(bro(application)))) = f_pointer(f_alignment(sh(application)));
	  }
	  pnset ( nds, usesproccall ) ;
	}
	else
	  pnset ( nds, hasproccall ) ;
      } 
      else if ( name(bro(bro(bro(son(application))))) != top_tag && valregable(sh(application))
		&& name(sh(application)) != tophd && name(sh(application)) != bothd ) {
	cca ( at, ptr_position ( application ) ) ;
	pnset ( nds, usesproccall ) ;
      }
      else {
	pnset ( nds, hasproccall ) ;
      }
      return nds;
    }
    case make_callee_list_tag : {
      exp cllees = *e;
      exp *par = &son(cllees);
      needs nds;
      int stpar = 0,i;
      nds = zeroneeds;
      for(i=0;i<no(cllees);++i){
	needs onepar;
	shape shonepar = sh(*par);
	int n = rounder(stpar,shape_align(shonepar));
	onepar = scan(par,at);
	if((pntst(onepar,hasproccall)!=0) || (onepar.fixneeds+1>maxfix)){
	  /* identify it */
	  cca(at,par);
	  pnset(nds,usesproccall);
	  nds = maxneeds(shapeneeds(sh(*par)),nds);
	  nds.maxargs = max(nds.maxargs,onepar.maxargs);
	}
	else{
	  nds = maxneeds(onepar,nds);
	}
	n += shape_size(shonepar);
	stpar = rounder(n,REG_SIZE);
	par = &bro(*par);
      }
      no(cllees) = stpar;
      return nds;
    }
    case make_dynamic_callee_tag : {
      exp cllees = *e;
      exp *ptr = &son(cllees);
      needs ndsp,nds;
      nds = zeroneeds;
      ndsp = scan(ptr,at);
      if((pntst(ndsp,hasproccall)!=0) || (ndsp.fixneeds+1>maxfix)){
	cca(at,ptr);
	pnset(nds,usesproccall);
	nds = maxneeds(shapeneeds(sh(*ptr)),nds);
	nds.maxargs = max(nds.maxargs,ndsp.maxargs);
      }
      else{
	nds = ndsp;
      }
      ndsp = scan(&bro(son(cllees)),at);
      if((pntst(ndsp,hasproccall)!=0) || (ndsp.fixneeds+2>maxfix)){
	cca(at,&bro(son(cllees)));
	pnset(nds,usesproccall);
	nds = maxneeds(shapeneeds(sh(bro(son(cllees)))),nds);
	nds.maxargs = max(nds.maxargs,ndsp.maxargs);
      }
      else{
	nds = maxneeds(ndsp,nds);
      }
      if(nds.fixneeds<10) nds.fixneeds = 10;	/* ?? */
      return nds;
    }
    case same_callees_tag: {
      needs nds;
      nds = zeroneeds;
      nds.fixneeds = 6;
      return nds;
    }
    case tail_call_tag: {
      exp tlcl = *e;
      needs ndsp,nds;
      exp *fn = &son(tlcl);
      ndsp = scan(fn,at);
      if((pntst(ndsp,hasproccall)!=0) || (ndsp.fixneeds+1 > maxfix)){
	cca(at,fn);
	pnset(nds,usesproccall);
	nds = maxneeds(shapeneeds(sh(*fn)),nds);
	nds.maxargs = max(nds.maxargs,ndsp.maxargs);
      }
      else{
	nds = ndsp;
      }
      ndsp = scan(&bro(son(tlcl)),at);
      nds = maxneeds(nds,ndsp);
      if(nds.fixneeds < 6) nds.fixneeds = 6;
      return nds;
    }

    case apply_tag : {
      int i ;
      needs nds ;
      int parsize = 0 ;
      exp appl = *e ;
      exp fn = son ( appl ) ;
      exp *par = &bro ( fn ) ;
      exp *fnexp = &son ( appl ) ;
      bool tlrecpos = ( bool ) ( nonevis && callerfortr &&
				 ( rscope_level == 0 ) ) ;

      nds = scan ( fnexp, at ) ;
      /* scan the function exp ... */
      if ( pntst ( nds, hasproccall ) != 0 ) {
	/* ... it must be identified */
	cca ( at, fnexp ) ;
	pnclr ( nds, hasproccall ) ;
	pnset ( nds, usesproccall ) ;
	fn = son ( appl ) ;
	par = &bro ( fn ) ;
      }

      if ( name ( fn ) != name_tag ||
	   ( son ( son ( fn ) ) != nilexp &&
	     ((name ( son ( son ( fn ) ) ) != proc_tag ) ||
	      name(son(son(fn)))==general_proc_tag))) {
	tlrecpos = 0 ;
      }

      for ( i = 1 ; !last ( fn ) ; ++i ) {
	/* scan parameters in turn ... */
	needs onepar ;
	shape shpar = sh ( *par ) ;
	onepar = scan ( par, at ) ;

	if ( ( i != 1 && pntst ( onepar, hasproccall ) != 0 ) ||
	     onepar.fixneeds + ( parsize >> 5 ) > maxfix ) {
	  /* if it isn't the first parameter, and it calls
	     a proc, identify it */
	  cca ( at, par ) ;
	  pnset ( nds, usesproccall ) ;
	  nds = maxneeds ( shapeneeds ( sh ( *par ) ), nds ) ;
	  nds.maxargs = MAX_OF ( nds.maxargs, onepar.maxargs ) ;
	} 
	else {
	  nds = maxneeds ( onepar, nds ) ;
	}
	parsize = ( int ) rounder ( parsize, shape_align ( shpar ) ) ;
	parsize = rounder ( parsize + shape_size ( shpar ), 32 ) ;
	if ( ( !valregable ( shpar ) &&
	       !is_floating ( name ( shpar ) ) ) ||
	     parsize > 128 ) {
	  tlrecpos = 0 ;
	}
	if ( last ( *par ) ) {
	  break ;
	}
	par = &bro ( *par ) ;
      }

      if ( specialopt ( fn ) ) {
	/* eg vfork */
	pnset ( nds, dont_optimise ) ;
      }

      if ( ( i = specialfn ( fn ) ) > 0 ) {
	/* eg strlen */
#if 0
	nds = maxneeds ( specialneeds ( i ), nds ) ;
#endif
	return nds;
      } 
      else if ( i == -1 ) {
	/* call of strcpy ... (removed) */
      }

      if ( tlrecpos ) {
	exp dad = father ( appl ) ;
	if ( name ( dad ) == res_tag ) {
	  props ( dad ) = 1 ;     /* do a tl recursion */
	}
      }

      if ( sparccpd (sh(appl)) ) {
	exp ap_context = need_result_space(appl);
	if (ap_context != nilexp) {
	  /* find space for tuple result */
	  assert ( name ( *( ptr_position ( appl ) ) ) == apply_tag ) ;
	  cca ( at, ptr_position ( appl ) ) ;
	  if (name(ap_context) != field_tag) {
		/* if context is application parameter, treat as pointer */
	    setvar (bro(bro(appl)));
	    sh(pt(bro(bro(appl)))) = f_pointer(f_alignment(sh(appl)));
	  }
	  pnset ( nds, usesproccall ) ;
	}
	else
	  pnset ( nds, hasproccall ) ;
      } 
      else {
	pnset ( nds, hasproccall ) ;
      }
      nds.maxargs = MAX_OF ( nds.maxargs, parsize ) ;
      /* clobber %o0..%o5,%o7 */
      nds.fixneeds = MAX_OF ( nds.fixneeds, 8 ) ;
      return nds;

    }
    case movecont_tag : {	/* Only whilst it aways generates memmove */
      int i ;
      needs nds ;
      int parsize = 0 ;
      exp mv = *e ;
      exp *par = &son ( mv ) ;
      bool tlrecpos = ( bool ) ( nonevis && callerfortr &&
				 ( rscope_level == 0 ) ) ;
      nds = zeroneeds;
    
      for ( i = 1 ; i<=3 ; ++i ) {
	/* scan parameters in turn ... */
	needs onepar ;
	shape shpar = sh ( *par ) ;
	onepar = scan ( par, at ) ;

	if ( ( i != 1 && pntst ( onepar, hasproccall ) != 0 ) ||
	     onepar.fixneeds + ( parsize >> 5 ) > maxfix ) {
	  /* if it isn't the first parameter, and it calls
	     a proc, identify it */
	  cca ( at, par ) ;
	  pnset ( nds, usesproccall ) ;
	  nds = maxneeds ( shapeneeds ( sh ( *par ) ), nds ) ;
	  nds.maxargs = MAX_OF ( nds.maxargs, onepar.maxargs ) ;
	} 
	else {
	  nds = maxneeds ( onepar, nds ) ;
	}
	parsize = ( int ) rounder ( parsize, shape_align ( shpar ) ) ;
	parsize = rounder ( parsize + shape_size ( shpar ), 32 ) ;
	if ( ( !valregable ( shpar ) &&
	       !is_floating ( name ( shpar ) ) ) ||
	     parsize > 128 ) {
	  tlrecpos = 0 ;
	}
	assert ((i != 3) || last(*par));
	par = &bro ( *par ) ;
      }


      if ( tlrecpos ) {
	exp dad = father ( mv ) ;
	if ( name ( dad ) == res_tag ) {
	  props ( dad ) = 1 ;     /* do a tl recursion */
	}
      }

      pnset ( nds, hasproccall ) ;

      nds.maxargs = MAX_OF ( nds.maxargs, parsize ) ;
      /* clobber %o0..%o5,%o7 */
      nds.fixneeds = MAX_OF ( nds.fixneeds, 7 ) ;
      return nds;
    }

    case val_tag : {
      exp s = sh ( *e ) ;
      if ( name ( s ) == offsethd && al2 ( s ) >= 8 ) {
	/* express disps in bytes */
	no ( *e ) = no ( *e ) >> 3 ;
      }
      /* FALL THROUGH */
    }
    case env_size_tag :
    case caller_name_tag :
    case null_tag :
    case real_tag :
    case string_tag :
    case env_offset_tag :
    case current_env_tag :
    case make_lv_tag : 
    case last_local_tag : {
      return shapeneeds ( sh ( *e ) ) ;
    }
    case name_tag : {
      needs nds;
      nds = shapeneeds ( sh ( *e ) ) ;
      if (PIC_code && isglob (son(*e))) { 
	long boff = no(*e) >> 3 ;
	if (boff < -4096 || boff > 4095)
	  nds.fixneeds += 1 ;
      }
      return nds;
    }
    case give_stack_limit_tag : {
      specialext = 1;
      return shapeneeds ( sh ( *e ) ) ;
    }
    case formal_callee_tag :
    case clear_tag :
    case top_tag :
    case prof_tag :
    case local_free_all_tag : {
      return zeroneeds;
    }
    case local_free_tag: {
      needs nds;
      nds = scan( &son(*e),at);
      if(nds.fixneeds < 2) nds.fixneeds = 2;
    }

#if 0
    case rscope_tag : {
      needs sn ;
      exp *s = &son ( *e ) ;
#if 0
      exp lst ;
#endif
      rscope_level++ ;
#if 0
      /* only needed when OPTIM_TAIL is set */
      ( void ) last_statement ( son ( *e ), &lst ) ; /* always true */
      if ( name ( lst ) == res_tag ) {
	/* can remove res */
	exp *pos = ptr_position ( lst ) ;
	exp t ;

	bro ( son ( lst ) ) = bro ( lst ) ;
	if ( last ( lst ) ) {
	  setlast ( son ( lst ) ) ;
	} 
	else {
	  clearlast ( son ( lst ) ) ;
	}
	*pos = son ( lst ) ;
	for ( t = father ( *pos ) ; name ( sh ( t ) ) == bothd ;
				    t = father ( t ) ) {
	  /* adjust ancestors to correct shape */
	  sh ( t ) = sh ( *pos ) ;
	}
      }
#endif
      sn = scan ( s, &s ) ;
      rscope_level-- ;
      return sn;
    }
#endif
    case set_stack_limit_tag : {
      exp *arg = &son ( *e ) ;
      specialext = 1;
      return scan ( arg, at ) ;
    }
#ifdef return_to_label_tag
    case return_to_label_tag :
#endif
#ifndef NEWDIAGS
    case diagnose_tag :
#endif
    case goto_lv_tag :
    case abs_tag :
    case neg_tag :
    case not_tag :
    case offset_negate_tag : {
      exp *arg = &son ( *e ) ;
      if (error_treatment_is_trap ( *e ))
	specialext = 1;
      return scan ( arg, at ) ;
    }
    case case_tag :
    { 
      needs s;
      exp *arg = &son ( *e ) ;

      s = scan ( arg, at ) ;
      s.fixneeds = MAX_OF ( s.fixneeds, 2 ) ; /* dense case calls getreg */
      return s;
    }

    case fneg_tag :
    case fabs_tag :
    case chfl_tag : {
      needs nds ;
      exp *pste;
      if (error_treatment_is_trap ( *e ))
	specialext = 1;
      nds = scan ( &son ( *e ), at ) ;
      pste = ptr_position(ste);
      if ( !optop ( *pste ) && nds.fixneeds < 2 ) nds.fixneeds = 2 ;
      if (use_long_double) {
	exp op = *pste ;
	if ( name ( sh ( op ) ) == doublehd ||
	     name ( sh ( son ( op ) ) ) == doublehd ) {
#if 0
	  if(name(*e) == fabs_tag){
	    replace_fabs(ste);
	  }
#endif
	  if ( !is_o ( name ( son ( op ) ) ) ||
	       pntst ( nds, hasproccall ) ) {
	    cca ( at, &son ( op ) ) ;
	  }
	  pnset ( nds, hasproccall ) ;
	}
      }
      return nds;
    }

    case bitf_to_int_tag : {
      exp *arg = &son ( *e ) ;
      needs nds ;
      exp stararg ;
      exp stare ;
      int sizeb ;

      nds = scan ( arg, at ) ;
      stararg = *arg ;
      stare = *e ;
      sizeb = shape_size ( sh ( stararg ) ) ;
      if ( ( name ( stararg ) == name_tag &&
	     ( ( sizeb == 8 &&
		 ( no ( stararg ) & 7 ) == 0 ) ||
	       ( sizeb == 16 &&
		 ( no ( stararg ) & 15 ) == 0 ) ||
	       ( sizeb == 32 &&
		 ( no ( stararg ) & 31 ) == 0 ) ) ) ||
	   ( name ( stararg ) == cont_tag &&
	     ( ( name ( son ( stararg ) ) != name_tag &&
		 name ( son ( stararg ) ) != reff_tag ) ||
	       ( sizeb == 8 &&
		 ( no ( son ( stararg ) ) & 7 ) == 0 ) ||
	       ( sizeb == 16 &&
		 ( no ( son ( stararg ) ) & 15 ) == 0 ) ||
	       ( sizeb == 32 &&
		 ( no ( son ( stararg ) ) & 31 ) == 0 ) ) ) ) {
	/* these bitsint ( trimnof ( X ) ) could be implemented by
	   lb or lh instructions ... */
	int sgned = name ( sh ( stare ) ) & 1 ;
	shape ns = ( sizeb == 8 ) ? ( sgned ? scharsh : ucharsh ) :
	  ( sizeb == 16 ) ? ( sgned ? swordsh : uwordsh ) :
	  sh ( stare ) ;
	/* can use short loads instead of bits extractions */
	if ( name ( stararg ) == cont_tag ) {
	  /* make the ptr shape consistent */
	  sh ( son ( stararg ) ) = f_pointer ( long_to_al (
							   ( long ) shape_align ( ns ) ) ) ;
	}
	sh ( stararg ) = ns ;
	setname ( stare, chvar_tag ) ;
      }
      return nds;
    }

    case int_to_bitf_tag : {
      exp *arg = &son ( *e ) ;
      return scan ( arg, at ) ;
    }
    case round_tag : {
      needs s ;
      exp *arg ;
      exp *pste;
      int rm = ( int ) round_number ( *e ) ;
      if (error_treatment_is_trap ( *e ))
	specialext = 1;
      arg = &son ( *e ) ;
      s = scan ( arg, at ) ;
      pste = ptr_position(ste);
      s.fixneeds = MAX_OF ( s.fixneeds, 2 ) ;
      if ( rm < 3 || name ( sh ( *pste ) ) == ulonghd ) {
	s.floatneeds = MAX_OF ( s.floatneeds, 3 ) ;
      } 
      else {
	s.floatneeds = MAX_OF ( s.floatneeds, 2 ) ;
      }
      if (use_long_double) {
	exp op = *pste ;
	      
	if ( name ( sh ( son ( op ) ) ) == doublehd ) {
	  if ( !is_o ( name ( son ( op ) ) ) ||
	       pntst ( s, hasproccall ) ) {
	    cca ( at, &son ( op ) ) ;
	  }
	  pnset ( s, hasproccall ) ;
	}
      }
      return s;
    }

    case shl_tag :
    case shr_tag :
    case long_jump_tag : {
      int prpx ;
      needs nl, nr ;
      exp *lhs = &son ( *e ) ;
      exp *rhs = &bro ( *lhs ) ;

      nr = scan ( rhs, at ) ;
      nl = scan ( lhs, at ) ;
      rhs = &bro(*lhs);
      prpx = ( int ) ( pntst ( nr, hasproccall ) << 1 ) ;

      if ( nr.fixneeds >= maxfix || prpx != 0 ) {
	/* if reg requirements overlap, identify second operand */
	cca ( at, rhs ) ;
	nl = shapeneeds ( sh ( *rhs ) ) ;
	pnset ( nl, morefix ) ;
	pnclr ( nl, ( prpx >> 1 ) ) ;
	pnset ( nl, prpx ) ;
      }
      nr.fixneeds += 1 ;
      nr.fixneeds += 1 ;	/* why? */
      return maxneeds ( nl, nr ) ;
    }

    case test_tag : {
      exp stare = *e ;
      exp l = son ( stare ) ;
      exp r = bro ( l ) ;

      if ( !last ( stare ) && name ( bro ( stare ) ) == test_tag &&
	   test_number ( stare ) == test_number ( bro ( stare ) ) &&
	   eq_exp ( l, son ( bro ( stare ) ) ) &&
	   eq_exp ( r, bro ( son ( bro ( stare ) ) ) ) ) {
	/* same test following in seq list - remove second test */
	if ( last ( bro ( stare ) ) ) setlast ( stare ) ;
	bro ( stare ) = bro ( bro ( stare ) ) ;
	no(son(pt(stare))) --; /* one less way there */
      }

      if ( last ( stare ) && name ( bro ( stare ) ) == 0 &&
	   name ( bro ( bro ( stare ) ) ) == test_tag &&
	   name ( bro ( bro ( bro ( stare ) ) ) ) == seq_tag &&
	   test_number ( stare ) ==
	   test_number ( bro ( bro ( stare ) ) ) &&
	   eq_exp ( l, son ( bro ( bro ( stare ) ) ) ) &&
	   eq_exp ( r, bro ( son ( bro ( bro ( stare ) ) ) ) ) ) {
	/* same test following in seq res - void second test */
	setname ( bro ( bro ( stare ) ), top_tag ) ;
	son ( bro ( bro ( stare ) ) ) = nilexp ;
	pt ( bro ( bro ( stare ) ) ) = nilexp ;
	no(son(pt(stare))) --; /* one less way there */
      }

      assert ((name(l) == val_tag) ? (name(r) == val_tag) : 1);
 				/* jmf claims to have put one val 
				   on right,so only allow val 
				   test val */

      if ( name(r) == val_tag && 
	   (props(stare) == 5 || props(stare) == 6) && /* eq/neq */
	   no (r) == 0 &&	/* against 0 */
	   name (l) == and_tag && name (bro (son (l))) == val_tag &&
	   (no (bro (son (l))) & (no (bro (son (l))) - 1)) == 0
	   ) 
	{			/* zero test  x & 2^n   -> neg test (x shl
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

      if ( name ( l ) == bitf_to_int_tag &&
	   name ( r ) == val_tag &&
	   ( props ( stare ) == 5 || props ( stare ) == 6 ) &&
	   ( name ( son ( l ) ) == cont_tag ||
	     name ( son ( l ) ) == name_tag ) ) {
	/* equality of bits against +ve consts doesnt need
	   sign adjustment */
	long n = no ( r ) ;
	switch ( name ( sh ( l ) ) ) {
	  case scharhd : {
	    if ( n >= 0 && n <= 127 ) {
	      sh ( l ) = ucharsh ;
	    }
	    break ;
	  }
	  case swordhd : {
	    if ( n >= 0 && n <= 0xffff ) {
	      sh ( l ) = uwordsh ;
	    }
	    break ;
	  }
	}
      } 
      else if ( is_floating ( name ( sh ( l ) ) ) ) {
	return fpop ( e, at ) ;
      } 
      else if ( name ( r ) == val_tag && no ( r ) == 1 &&
		  ( props ( stare ) == 3 || props ( stare ) == 2 ) ) {
	no ( r ) = 0 ;
	if ( props ( stare ) == 3 ) {
	  /* branch >= 1 -> branch > 0 */
	  props ( stare ) = 4 ;
	} 
	else {
	  /* branch < 1 -> branch <= 0 */
	  props ( stare ) = 1 ;
	}
      }
      return likediv ( e, at ) ;
    }

    case plus_tag : {
      /* replace any operands which are neg ( .. ) by -, if poss */
      exp sum = *e ;
      exp list = son ( sum ) ;
      bool someneg = 0 ;
      bool allneg = 1 ;
      if (error_treatment_is_trap ( *e ))
	specialext = 1;

      for ( ; optop ( sum ) ; ) {
	if ( name ( list ) == neg_tag ) {
	  someneg = 1 ;
	} 
	else {
	  allneg = 0 ;
	}
	if ( last ( list ) ) break ;
	list = bro ( list ) ;
      }

      if ( someneg ) {
	/* there are some neg () operands */
	if ( allneg ) {
	  /* transform - .. - ... to - ( .. + .. + ... ) */
	  exp x ;
	  /* Build a new list form operand of neg_tags, which
	     will become plus_tag operands */
	  x = son ( sum ) ;
	  list = son ( x ) ;
	  for ( ; ; ) {
	    /* 'x' moves along neg_tag's lists 'list' moves
	       along sons of neg_tag's lists, building a new list
	       eventually new list is made son of plus_tag */
	    if ( !last ( x ) ) {
	      bro ( list ) = son ( bro ( x ) ) ;
	      clearlast ( list ) ;
	      list = bro ( list ) ;
	      x = bro ( x ) ;
	    } 
	    else {
	      /* set father to be */
	      bro ( list ) = sum ;
	      setlast ( list ) ;
	      /* set new sons of plus_tag */
	      son ( sum ) = son ( son ( sum ) ) ;
	      break ;
	    }
	  }

	  /* create new neg_tag to replace plus_tag, old
	     plus_tag being the operand of the new neg_tag */
	  x = getexp ( sh ( sum ), bro ( sum ), ( int ) last ( sum ),
		       sum, nilexp, 0, 0, neg_tag ) ;
	  setlast ( sum ) ;
	  /* set father of sum, new neg_tag exp */
	  bro ( sum ) = x ;
	  *e = x ;
	} 
	else {
	  /* transform to ( ( .. ( .. + .. ) - .. ) - .. ) */
	  int n = 0 ;
	  exp brosum = bro ( sum ) ;
	  bool lastsum = ( bool ) last ( sum ) ;
	  exp x = son ( sum ) ;
	  exp newsum = sum ;

	  list = nilexp ;
	  for ( ; ; ) {
	    exp nxt = bro ( x ) ;
	    bool final = ( bool ) last ( x ) ;

	    if ( name ( x ) == neg_tag ) {
	      bro ( son ( x ) ) = list ;
	      list = son ( x ) ;
	    } 
	    else {
	      bro ( x ) = newsum ;
	      newsum = x ;
	      if ( ( n++ ) == 0 ) {
		setlast ( newsum ) ;
	      } 
	      else {
		clearlast ( newsum ) ;
	      }
	    }
	    if ( final ) break ;
	    x = nxt ;
	  }

	  if ( n > 1 ) {
	    son ( sum ) = newsum ;
	    /* use existing exp for add operations */
	    newsum = sum ;
	  }
	  for ( ; ; ) {
	    /* introduce - operations */
	    exp nxt = bro ( list ) ;
	    bro ( newsum ) = list ;
	    clearlast ( newsum ) ;
	    x = getexp ( sh ( sum ), nilexp, 0, newsum, nilexp,
			 0, 0, minus_tag ) ;
	    bro ( list ) = x ;
	    setlast ( list ) ;
	    newsum = x ;
	    if ( ( list = nxt ) == nilexp ) break ;
	  }
	  bro ( newsum ) = brosum ;
	  if ( lastsum ) {
	    setlast ( newsum ) ;
	  } 
	  else {
	    clearlast ( newsum ) ;
	  }
	  *e = newsum ;

	}
	return scan ( e, at ) ;

      }
      /* FALL THROUGH */
    }

    case and_tag :
    case or_tag :
    case xor_tag : {
      return likeplus ( e, at ) ;
    }
#ifdef make_stack_limit_tag
    case make_stack_limit_tag :
#endif
    case minus_tag :
    case subptr_tag :
    case minptr_tag : {
      if (error_treatment_is_trap ( *e ))
	specialext = 1;
      return likediv ( e, at ) ;
    }
    case addptr_tag :
    {
      exp ptr_arg = son(*e);
      exp offset_arg = bro(ptr_arg);
      int fralign = frame_al_of_ptr(sh(ptr_arg));
      if(fralign){
	int offalign = frame_al1_of_offset(sh(offset_arg));
#if 0
	if(((offalign-1)&offalign)!=0){
	  fail("Mixed frame offsets not supported");
	}
#endif
	if(cees(offalign) && name(son(*e)) == current_env_tag) {
	  setcallee_offset(son(*e));
	}
	


#if 0
	if(include_vcallees(fralign) && l_or_cees(offalign)){
	  exp newexp = getexp(sh(ptr_arg),offset_arg,0,ptr_arg,nilexp,0,0,
			      locptr_tag);
	  bro(ptr_arg) = newexp;
	  setlast(ptr_arg);
	  son(*e) = newexp;
	}
#endif
      }
      return likediv(e,at);
    }
    case locptr_tag : 
    case reff_tag :
    case float_tag :
    case offset_pad_tag :
    case chvar_tag : {
      exp *arg = &son ( *e ) ;
      exp *pste;
      needs nds ;
      if (error_treatment_is_trap ( *e ))
	specialext = 1;
      nds =  shapeneeds ( sh ( *e ) );
      nds = maxneeds ( scan ( arg, at ), nds ) ;
      pste = ptr_position(ste);
      if (use_long_double) {
	exp op = *pste ;

	if ( name ( sh ( op ) ) == doublehd ) {
	  pnset ( nds, hasproccall ) ;
	}
      }
      return nds;
    }

    case cont_tag :
    case contvol_tag : {
      exp *arg = &son ( *e ) ;
      needs nds ;
      nds = maxneeds ( scan ( arg, at ), shapeneeds ( sh ( *e ) ) ) ;
      nds.fixneeds = MAX_OF ( nds.fixneeds, 2 ) ;
      return nds;
    }

    case mult_tag :
    mult_tag_case : {
      if (error_treatment_is_trap ( *e ))
	specialext = 1;
      return multneeds ( e, at ) ;
    }

    case offset_mult_tag :
    case offset_div_tag : {

      exp op1 = son(*e);
      exp op2 = bro ( op1) ;
      shape s = sh ( op2 ) ;
      if ( name ( op2 ) == val_tag && no ( op2 ) == 8 &&
	   name ( s ) == offsethd && al2 ( s ) >= 8 ) {
	/* offset is one byte */
	bro ( op1 ) = bro ( *e ) ;
	if ( last ( *e ) ) {
	  setlast ( op1 ) ;
	} 
	else {
	  clearlast ( op1 ) ;
	}
	sh(op1) = sh(*e);
	*e = op1 ;
	if (name(*e) == val_tag)
	  return shapeneeds ( sh ( *e ) ) ;	/* disps already in bytes */
	else
	  return scan ( e, at ) ;
      }

      if ( nstare == offset_mult_tag ) goto mult_tag_case ;
      /* FALL THROUGH */
    }

    case div0_tag:
    case div1_tag :
    case div2_tag :
    case offset_div_by_int_tag : {
      if (error_treatment_is_trap ( *e ))
	specialext = 1;
      return divneeds ( e, at ) ;
    }

    case offset_add_tag :
    case offset_subtract_tag : {
      if((al2(sh(son(*e))) == 1) && (al2(sh(bro(son(*e)))) != 1)){
	make_bitfield_offset(bro(son(*e)),son(*e),0,sh(*e));
      }
      if((al2(sh(son(*e))) != 1) && (al2(sh(bro(son(*e)))) == 1)){
	make_bitfield_offset(son(*e),*e,1,sh(*e));
      }
    }
      /* FALL_THROUGH */
    case component_tag : {
      return likediv ( e, at ) ;
    }
    case offset_max_tag: case max_tag: case min_tag:
    { needs nd;
    nd = likediv(e, at);
    nd.fixneeds = MAX_OF(nd.fixneeds, 3);
    return nd;
    } 

    case rem0_tag:
    case mod_tag :
    case rem2_tag : {
      if (error_treatment_is_trap ( *e ))
	specialext = 1;
      return remneeds ( e, at ) ;
    }

    case fdiv_tag :
#if ( FBASE == 10 )
    {
      exp z = *e ;
      exp a2 = bro ( son ( z ) ) ;

      if ( name ( a2 ) == real_tag ) {
	/* replace X / const by X * ( 1.0 / const ) */
	flt inverse ;
	flt unitflt ;
	unitflt = flptnos [ fone_no ] ;
	if ( flt_div ( unitflt, flptnos [ no ( a2 ) ],
		       &inverse ) == OKAY ) {
	  int f = new_flpt () ;
	  flptnos [f] = inverse ;
	  no ( a2 ) = f ;
	  setname ( z, fmult_tag ) ;
	}
      }
    }
    /* FALL THROUGH */
#endif

    case fplus_tag :
    case fminus_tag :
    case fmult_tag : {
      exp op = *e ;
      exp a2 = bro ( son ( op ) ) ;
      if (error_treatment_is_trap ( *e ))
	specialext = 1;

      if ( !last ( a2 ) ) {
	/* + and * can have > 2 parameters - make them diadic
	   - can do better a + exp => let x = exp in a + x */
	exp opn = getexp ( sh ( op ), op, 0, a2, nilexp,
			   0, 0, name ( op ) ) ;
	/* don't need to transfer error treatment - nans */
	exp nd = getexp ( sh ( op ), bro ( op ), ( int ) last ( op ),
			  opn, nilexp, 0, 1, ident_tag ) ;
	exp id = getexp ( sh ( op ), op, 1, nd, nilexp,
			  0, 0, name_tag ) ;
	pt ( nd ) = id ;
	bro ( son ( op ) ) = id ;
	setlast ( op ) ;
	bro ( op ) = nd ;
	while ( !last ( a2 ) ) a2 = bro ( a2 ) ;
	bro ( a2 ) = opn ;
	*e = nd ;
	return scan ( e, at ) ;
      }
      return fpop ( e, at ) ;
    }

    case fmax_tag : {
      return fpop(e,at);
    }
    
    case field_tag : {
      needs str ;
      exp *arg = &son ( *e ) ;
      if ( chase ( *e, arg ) ) {
	/* field has been distributed */
	exp stare = *e ;
	exp ss = son ( stare ) ;
	if ( !last ( stare ) ) clearlast ( ss ) ;
	bro ( ss ) = bro ( stare ) ;
	sh ( ss ) = sh ( stare ) ;
	*e = ss ;
	return scan ( e, at ) ;
      }
      str = scan ( arg, at ) ;
      return maxneeds ( str, shapeneeds ( sh ( *e ) ) ) ;
    }
    case general_proc_tag :
    case proc_tag : {
      exp *bexp ;
      exp *bat ;
      needs body ;
      exp stare = *e ;

      /* set number temp t-regs that can be used in proc */
      maxfix = maxfix_tregs ;
      maxfloat = MAXFLOAT_TREGS ;

      /* on SPARC tail recursion is harder than MIPS and less of a win
	 but still worth implementing sometime */
      assert(~optim & OPTIM_TAIL);

      callerfortr = optim & OPTIM_TAIL && !proc_has_setjmp ( stare ) &&
	!proc_has_alloca ( stare ) &&
	!proc_has_lv ( stare ) &&
	!proc_uses_crt_env ( stare ) ;
      stparam = 0 ;
      fixparam = R_I0 ;
      nonevis = 1 ;
      specialext = proc_has_checkstack(*e);
      rscope_level = 0 ;
      gen_call = (name(stare) == general_proc_tag);
      v_proc = proc_has_vcallees(*e);
      callee_size = 0;
      if (gencompat) {
        trad_proc = !proc_may_have_callees(stare);
      }
      /* scan the body of the proc */
      bexp = &son ( *e ) ;
      bat = bexp ;
      body = scan ( bexp, &bat ) ;
      if (specialext)
	set_proc_uses_external ( *e ) ;
      if ((gencompat && !trad_proc) || (!gencompat && gen_call)) {
	callee_size += 4 * PTR_SZ;
      }
      /* should never require this in reg in C */
      return body;
    }

    case alloca_tag : {
      needs nds ;
      if (checkalloc ( *e ))
	specialext = 1;
      nds = scan ( &son ( *e ), at ) ;
      if ( nds.fixneeds < 2 ) nds.fixneeds = 2 ;
      return nds;
    }
    case trap_tag :{
      specialext = 1;
      return zeroneeds;
    }
    case special_tag :{
      return zeroneeds;
    }
    case asm_tag:
    {
      needs nds;
      nds = zeroneeds;
      if (props(*e) != 0)
	  fail ("~asm not in ~asm_sequence");
      check_asm_seq (son(*e), 0);
      /* clobber %o0..%o5,%o7 */
      nds.fixneeds = MAX_OF ( nds.fixneeds, 8 ) ;
      pnset ( nds, hasproccall ) ;
      return nds;
    };
    default : {
      fail ( "Case not covered in needs scan" ) ;
      return zeroneeds;
    }
  }
  /* NOT REACHED */
}

