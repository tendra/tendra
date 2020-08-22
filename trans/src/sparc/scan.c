/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * The functions in this file define the scan through a program which
 * reorganises it so that all arguments of operations are suitable for
 * later code-production.  The procedure scan evaluates the register
 * requirements of an exp.  The exps are produced from the decoding
 * process and the various exp->exp transformations (common to other
 * translators).
 */

#include <assert.h>
#include <string.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <local/al.h>
#include <local/ash.h>
#include <local/exp.h>
#include <local/tag.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/externs.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/ash.h>
#include <construct/exp.h>
#include <construct/install_fns.h>
#include <construct/me_fns.h>

#include <flpt/flpt.h>

#include <refactor/const.h>
#include <refactor/optimise.h>
#include <refactor/refactor.h>

#include <utility/max.h>

#include <main/flags.h>

#include "procrec.h"
#include "proc.h"
#include "bits.h"
#include "regable.h"
#include "tempdecs.h"
#include "reg.h"
#include "muldvrem.h"
#include "translate.h"
#include "scan.h"
#include "special.h"
#include "reg_defs.h"
#include "make_code.h"

extern prop notbranch[];

static int stparam ;	/* Size of parameter list in bits */
static int fixparam ;	/* Next available place for param */

static bool nonevis     = true ;
static bool specialext ;	/* for PIC_code, special globals require proc_uses_external */
static int callerfortr ;

static bool gen_call;   /* true if the scan is within a general proc */
static bool v_proc;     /* true if the scan is within a general proc with vcallees */
static bool trad_proc;	/* true if the scan is within a proc with no callees */

int maxfix, maxfloat ;		/* The maximum numbers of t-regs */

/*
 * THE TYPE DESCRIBING REGISTER NEEDS
 *
 * The type needs is defined in procrec.h.  This is a structure
 * which has two integers giving the number of fixed and floating
 * point registers required to contain live values in the expression
 * parameters.  A further field prop is used for various flags about
 * certain forms of exp (mainly idents and procs).  The maxargs
 * field gives the maximum size in bits for the parameters of all
 * the procs called in the exp.  The needs of a proc body are
 * preserved in the needs field of the procrec (see procrec.h).
 */

/*
 * FIND A POINTER TO EXPRESSION POINTING TO e
 */
static exp *
ptr_position ( exp e )
{
	exp *res ;
	exp dad = father ( e ) ;
	exp sib = child ( dad ) ;

	if ( sib == e ) {
		res = &child ( dad ) ;
	} else {
		while ( next ( sib ) != e ) {
			sib = next ( sib ) ;
		}
		res = &next ( sib ) ;
	}

	return res;
}

/*
 * INSERT A NEW DECLARATION
 *
 * This procedure effectively inserts a new declaration into an exp.
 * This is used to stop a procedure requiring more than the available
 * number of registers.
 */
static void
cca ( exp ** to, exp * x )
{

#ifdef TDF_DIAG3
	if ((**to)->tag == diagnose_tag) {
		*to = &(child((**to)));
	}
#endif

	if ( x == ( *to ) ) {
		/* replace by Let tag = def In tag Ni */
		exp def = *x ;
		exp id = getexp ( sh ( def ), next ( def ), ( int ) def -> last,
		                  def, NULL, 0, 1, ident_tag ) ;
		exp tag = getexp ( sh ( def ), id, 1, id, NULL, 0, 0, name_tag ) ;

		/* use of tag */
		pt ( id ) = tag ;
		/* next ( def ) is body of Let = tag */
		next ( def ) = tag ;
		def -> last = false ;
		/* replace pointer to x by Let */
		*x = id ;

#ifdef TDF_DIAG4
		if (diag != DIAG_NONE) {
			dgf(id) = dgf(next(child(id)));
			dgf(next(child(id))) = NULL;
		}
#endif
	} else {
		/* replace by Let tag = def In ato/def = tag Ni */
		exp def = *x ;
		exp ato = *( *to ) ;

		exp id  = getexp ( sh ( ato ), next ( ato ), ( int ) ato -> last,
		                   def, NULL, 0, 1, ident_tag ) ;
		exp tag = getexp ( sh ( def ), next ( def ), ( int ) def -> last,
		                   id, NULL, 0, 0, name_tag ) ;

		/* use of tag */
		pt ( id ) = tag ;
		/* ato is body of Let */
		next ( def ) = ato ;
		def -> last = false ;
		/* its father is Let */
		next ( ato ) = id ;
		ato ->last = true ;

		/* replace pointer to 'to' by Let */
		**to = id ;
		/* replace use of x by tag */
		*x = tag ;
		/* later replacement to same 'to' will be at body of Let */
		*to = &next ( def ) ;

#ifdef TDF_DIAG4
		if (diag != DIAG_NONE) {
			dgf(id) = dgf(next(child(id)));
			dgf(next(child(id))) = NULL;
		}
#endif
	}
}

/*
 * BASIC REGISTER NEEDS
 *
 * This represent the requirements, one fixed point register,
 * two fixed point registers, one floating point register and
 * no registers respectively.
 */
static needs onefix    = { 1, 0, 0, 0 } ;
static needs twofix    = { 2, 0, 0, 0 } ;
static needs onefloat  = { 0, 1, 0, 0 } ;
static needs zeroneeds = { 0, 0, 0, 0 } ;

#if 0

/*
 * CHECK IF ANY USES OF id ARE AS AN INITIALISER FOR A DECLARATION
 */
bool
subvar_use ( exp uses )
{
	for ( ; uses != NULL ; uses = pt ( uses ) ) {
		if ( uses -> last && next ( uses ) -> tag == cont_tag ) {
			exp c = next ( uses ) ;
			if ( ! c -> last && next ( c ) -> last &&
			     next ( next ( c ) ) -> tag == ident_tag ) {
				exp id = next ( next ( c ) ) ;
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
 * WORK OUT REGISTER NEEDS FOR A GIVEN SHAPE
 */
static needs
shapeneeds ( shape s )
{
	if ( is_floating ( s->tag ) ) {
		return onefloat;
	}

	if ( valregable ( s ) ) {
		return onefix;
	} else {
		/* if the shape does not fit into a reg, needs two fixed
		regs for moving */
		return twofix;
	}

	UNREACHED;
}

/*
 * Transform a non-bit offset into a bit offset.
 * (borrowed from trans386)
 */
static void
make_bitfield_offset ( exp e, exp pe, int spe, shape sha )
{
	exp omul;
	exp val8;

	if (e->tag == val_tag) {
		no(e) *= 8;
		return;
	}

	omul = getexp (sha, next(e), (int)(e->last), e, NULL, 0, 0, offset_mult_tag);
	val8 = getexp (slongsh, omul, 1, NULL, NULL, 0, 8, val_tag);
	e->last = false;
	setnext(e, val8);

	if (spe) {
		child(pe) = omul;
	} else {
		next(pe) = omul;
	}
}

/*
 * IS AN EXPRESSSION COMPLEX?
 *
 * An expression is complex if, basically, it cannot be accessed by a
 * simple load or store instruction.
 */
static bool
complex ( exp e )
{
	if ( e->tag == name_tag ) {
		return 0;
	}

	if ( e->tag == cont_tag && child ( e ) -> tag == name_tag &&
	       isvar ( child ( child ( e ) ) ) ) {
		return 0;
	}

	if ( e->tag == val_tag || e->tag == real_tag || e->tag == null_tag ) {
		return 0;
	}

	return 1;
}

static int
scan_cond ( exp* e, exp outer_id )
{

	exp ste = *e;
	exp first = child (ste);
	exp labst = next (first);
	exp second = next (child (labst));

	assert(ste->tag == cond_tag);

	/* cond is { ... test(L); ? ; goto X | L:make_top}
	   if ? empty can replace by seq { ... not-test(X); make_top }
	 */
	if (second->tag == top_tag && sh(first)->tag == bothd && no(child(labst)) == 1
	    && first->tag == seq_tag && next(child(first))->tag == goto_tag) {
		exp l;

		for (l = child(child(first)); !l->last; l = next(l))
			;

		while (l->tag == seq_tag) {
			l = next(child(l));
		}

		if (l->tag == test_tag && pt(l) == labst) {
			settest_number(l, notbranch[(int)test_number(l)]);
			pt(l) = pt(next(child(first)));
			next(child(first)) = second;
			next(second) = first;
			second->last = true;
			next(first) = next(ste);

			if (ste->last) {
				first->last = true;
			} else {
				first->last = false;
			}

			*e = first;
			return 1;
		}

		return 0;
	}

	/* cond is ( seq (test to L;....|
	   L:cond(seq(test;...),...) ) ..... */
	if (first->tag == seq_tag && second->tag == cond_tag
	    && no(child(labst)) == 1
	    && child (child (first))->tag == test_tag
	    && pt (child (child (first))) == labst
	    && child (second)->tag == seq_tag
	    && child (child (child (second)))->tag == test_tag)
	{
		exp test1 = child (child (first));
		exp test2 = child (child (child (second)));
		exp op11 = child(test1);
		exp op21 = next(op11);
		exp op12 = child(test2);
		exp op22 = next(op12);

		bool c1 = complex (op11);
		bool c2 = complex (op21);

		if (c1 && eq_exp (op11, op12)) {
			/* ....if first operands of tests are same, identify them */
			exp newid = getexp (sh (ste), next (ste), ste->last, op11, NULL,
			                    0, 2, ident_tag);
			exp tag1 = getexp (sh (op11), op21, 0, newid, NULL, 0, 0, name_tag);
			exp tag2 = getexp (sh (op12), op22, 0, newid, NULL, 0, 0, name_tag);

			pt (newid) = tag1;
			pt (tag1)  = tag2;	/* uses of newid */
			next (op11) = ste;
			op11->last = false;/* body of newid */
			/* forget child test2 = child test1 */
			next (ste) = newid;
			ste->last = true;	/* father body = newid */
			child (test1) = tag1;
			child (test2) = tag2;	/* relace 1st operands of test */

			if (!complex(op21) ) {
				/* if the second operand of 1st test is simple, then
				   identification could go in a t-teg (!!!NB overloading
				   of inlined flag!!!).... */
				setinlined(newid);
			}

			kill_exp(op12, op12);
			*e = newid;
			if ( scan_cond (&next(child(labst)), newid) == 2 && complex(op22)) {
				/* ... however a further use of identification means that
				   the second operand of the second test must also be simple */
				clearinlined(newid);
			}

			return 1;
		} else if (c2 && eq_exp (op21, op22)) {
			/* ....if second operands of tests are same, identify them */

			exp newid = getexp (sh (ste), next (ste), ste->last, op21,
			                    NULL, 0, 2, ident_tag);
			exp tag1 = getexp (sh (op21), test1, 1,
			                   newid, NULL, 0, 0, name_tag);
			exp tag2 = getexp (sh (op22), test2, 1, newid, NULL,
			                   0, 0, name_tag);

			pt (newid) = tag1;
			pt (tag1)  = tag2;	/* uses of newid */
			next (op21) = ste;
			op21->last = false;
			/* body of newid */
			/* forget next child test2 = next child test1 */
			next (ste) = newid;
			ste->last = true;	/* father body = newid */
			next (op11) = tag1;
			next (op12) = tag2;

			if (!complex(op11) ) {
				setinlined(newid);
			}

			kill_exp(op22, op22);
			/* relace 2nd operands of test */
			* (e) = newid;
			if (scan_cond (&next(child(labst)), newid) == 2 && complex(op12) ) {
				clearinlined(newid);
			}

			return 1;
		} else if (op12->tag != name_tag
		           && op11->tag == name_tag
		           && child (op11) == outer_id
		           && eq_exp (child (outer_id), op12))
		{
			/* 1st param of test1 is already identified with
			   1st param of  test2 */
			exp tag = getexp (sh (op12), op22, 0, outer_id,
			                  pt (outer_id), 0, 0, name_tag);
			pt (outer_id) = tag;
			no (outer_id) += 1;

			if (complex(op21) ) {
				clearinlined(outer_id);
			}

			/* update usage of ident */
			child (test2) = tag;
			kill_exp(op12, op12);
			if (scan_cond (&next(child(labst)), outer_id) == 2 && complex(op22)) {
				clearinlined(outer_id);
			}

			return 2;
		}
	}

	return 0;
}

/*
 * WORK OUT REGISTER NEEDS FOR PLUS-LIKE OPERATIONS
 *
 * The operation will be n-ary, commutative and associative.
 */
needs
likeplus ( exp * e, exp ** at )
{
	needs a1 ;
	needs a2 ;
	prop pc ;
	exp *br = &child ( *e ) ;
	exp dad = *e ;
	exp prev ;
	bool commuted = 0 ;

	/* scan the first operand - won't be a val_tag */
	a1 = scan ( br, at ) ;

	/* likeplus exp with 1 operand should never occur */
	assert ( ! ( *br ) -> last ) ;

	do {
		exp *prevbr ;
		prevbr = br ;
		prev = *br ;

		br = &next ( prev ) ;
		a2 = scan ( br, at ) ;
		/* scan the next operand ... */
		if ( ( *br )->tag != val_tag ) {
			a1.floatneeds = MAX ( a1.floatneeds, a2.floatneeds ) ;
			pc = ( prop ) ( a2.propneeds & hasproccall ) ;
			if ( a2.fixneeds < maxfix && pc == 0 ) {
				/*... its evaluation will not disturb the accumulated result */
				a1.fixneeds = MAX ( a1.fixneeds, a2.fixneeds + 1 ) ;
				a1.propneeds = ( prop ) ( a1.propneeds | a2.propneeds ) ;
			} else if ( a1.fixneeds < maxfix && ( a1.propneeds & hasproccall ) == 0 &&
			            !commuted ) {
				/* ...its evaluation will call a proc, so put it first */
				exp op1 = child ( dad ) ;
				exp cop = *br ;
				bool lcop = ( bool ) cop -> last ;
				next ( prev ) = next ( cop ) ;

				if ( lcop ) {
					 prev ->last = true ;
				}

				next ( cop ) = op1 ;
				cop ->last = false ;
				child ( dad ) = cop ;
				br = ( prev == op1 ) ? &next ( cop ): prevbr ;
				commuted = 1 ;
				a1.fixneeds = MAX ( a2.fixneeds, a1.fixneeds + 1 ) ;
				a1.propneeds |= a2.propneeds ;
				a1.maxargs = MAX ( a1.maxargs, a2.maxargs ) ;
			} else {
				/* evaluation would disturb accumulated result, so replace
				   it by a newly declared tag */
				cca ( at, br ) ;
				a1.fixneeds = MAX ( a1.fixneeds, 2 ) ;
				a1.propneeds |= ( morefix | ( pc << 1 ) ) ;
				a1.maxargs = MAX ( a1.maxargs, a2.maxargs ) ;
			}
		} else {
			/* nothing */
		}
	} while ( ! ( *br ) -> last ) ;

#if 1
	/* exception handling regs (from mips) */
	if ( !optop ( *e ) ) {
		if ( a1.fixneeds < 4 ) {
			a1.fixneeds = 4 ;
		}
	}
#endif

	return a1;
}

/*
 * WORK OUT REGISTER NEEDS FOR DIVIDE-LIKE OPERATIONS
 *
 * The operation will be binary and non-commutative.
 */
needs
likediv ( exp * e, exp ** at )
{
	needs l ;
	needs r ;
	prop pc ;
	exp *arg = &child ( *e ) ;

	l = scan ( arg, at ) ;
	/* scan 1st operand */
	arg = &next ( *arg ) ;
	r = scan ( arg, at ) ;
	/* scan second operand ... */
	l.floatneeds = MAX ( l.floatneeds, r.floatneeds ) ;

	pc = ( prop ) ( r.propneeds & hasproccall ) ;
	if ( r.fixneeds < maxfix && pc == 0 ) {
		/* fits into registers */
		l.fixneeds = MAX ( l.fixneeds, r.fixneeds + 1 ) ;
		l.propneeds |= r.propneeds ;
	} else {
		/* requires new declaration of second operand */
		cca ( at, arg ) ;
		l.fixneeds = MAX ( l.fixneeds, 1 ) ;
		l.propneeds |= ( morefix | ( pc << 1 ) ) ;
		l.maxargs = MAX ( l.maxargs, r.maxargs ) ;
	}

#if 1
	/* exception handling regs (from mips) */
	if ( !optop ( *e ) ) {
		if ( l.fixneeds < 4 ) {
			l.fixneeds = 4 ;
		}
	}
#endif

	return l;
}

/*
 * WORK OUT REGISTER NEEDS FOR FLOATING-POINT OPERATIONS
 *
 * The operation will be binary.
 */
static needs
fpop ( exp * e, exp ** at )
{
	needs l ;
	needs r ;
	exp op = *e ;
	prop pcr, pcl ;
	exp *arg = &child ( op ) ;

	l = scan ( arg, at ) ;
	arg = &next ( *arg ) ;
	r = scan ( arg, at ) ;
	l.fixneeds = MAX ( l.fixneeds, r.fixneeds ) ;
	pcr = ( prop ) ( r.propneeds & hasproccall ) ;
	pcl = ( prop ) ( l.propneeds & hasproccall ) ;

	if ( (has & HAS_LONG_DOUBLE) && sh ( child ( op ) ) -> tag == doublehd ) {
		ClearRev ( op ) ;
		arg = &child ( op ) ;
		if ( !is_o ( ( *arg ) -> tag ) || pcl ) {
			cca ( at, arg ) ;
		}

		arg = &next ( child ( op ) ) ;
		if ( !is_o ( ( *arg ) -> tag ) || pcr ) {
			cca ( at, arg ) ;
		}

		l.floatneeds = MAX ( l.floatneeds, r.floatneeds ) ;
		l.maxargs = MAX ( l.maxargs, r.maxargs ) ;
		l.propneeds |= hasproccall ;
		return l;
	}

	if ( r.floatneeds <= l.floatneeds &&
	     r.floatneeds < maxfloat && pcr == 0 ) {
		l.floatneeds = MAX ( l.floatneeds, r.floatneeds + 1 ) ;
		l.floatneeds = MAX ( 2, l.floatneeds ) ;
		l.propneeds |= r.propneeds ;
		ClearRev ( op ) ;
	} else if ( pcl == 0 && l.floatneeds <= r.floatneeds &&
	            l.floatneeds < maxfloat ) {
		l.floatneeds = MAX ( r.floatneeds, l.floatneeds + 1 ) ;
		l.floatneeds = MAX ( 2, l.floatneeds ) ;
		l.propneeds |= r.propneeds ;
		SetRev ( op ) ;
	} else if ( r.floatneeds < maxfloat && pcr == 0 ) {
		l.floatneeds = MAX ( l.floatneeds, r.floatneeds + 1 ) ;
		l.floatneeds = MAX ( 2, l.floatneeds ) ;
		l.propneeds |= r.propneeds ;
		ClearRev ( op ) ;
	} else {
		cca ( at, arg ) ;
		ClearRev ( op ) ;
		l.floatneeds = MAX ( l.floatneeds, 2 ) ;
		l.propneeds |= ( morefloat | ( pcr << 1 ) ) ;
		l.maxargs = MAX ( l.maxargs, r.maxargs ) ;
	}

	return l;
}

/*
 * WORK OUT THE MAXIMUM OF TWO REGISTER NEEDS
 */
static needs
maxneeds ( needs a, needs b )
{
	needs an ;

	an.fixneeds = MAX ( a.fixneeds, b.fixneeds ) ;
	an.floatneeds = MAX ( a.floatneeds, b.floatneeds ) ;
	an.maxargs = MAX ( a.maxargs, b.maxargs ) ;
	an.callee_size = MAX(a.callee_size, b.callee_size);
	an.propneeds = ( prop ) ( a.propneeds | b.propneeds ) ;

	return an;
}

/*
 * WORK OUT THE REGISTER NEEDS OF A TUPLE OF EXPRESSIONS
 */
static needs
maxtup ( exp e, exp ** at )
{
	exp *s = &child ( e ) ;
	needs an ;
	an = zeroneeds ;

	if (*s == NULL) {
		return an;
	}

	while (an = maxneeds (an, scan (s, at)), !(*s)->last ) {
		s = &next(*s);
	}

	return an;
}

/*
 * IS A VALUE UNCHANGED OVER ITS SCOPE?
 *
 * This routine finds if usedname is only used in cont operation or as
 * result of ident.
 */
static bool
unchanged ( exp usedname, exp ident )
{
	exp uses;

	for ( uses = pt ( usedname ) ; uses != NULL ; uses = pt ( uses ) ) {
		if ( ! intnl_to ( ident, uses ) ) {
			continue ;
		}

		if ( ! uses -> last || next ( uses ) -> tag != cont_tag ) {
			exp z;

			for ( z = uses ; z != ident ; z = next ( z ) ) {
				if ( ! z -> last || ( next ( z ) -> tag != seq_tag &&
				                      next ( z ) -> tag != ident_tag ) ) {
					return 0;
				}
			}
		}
	}

	return 1;
}

/*
 * CHASE STRUCTURE PROCEDURE RESULTS
 *
 * The SPARC convention for delivering a struct from a procedure is
 * to have an extra pointer parameter in the proc; this means that
 * there must always be space in the calling work-space for the
 * result struct whether or not the value is used e.g. as in
 * f ( x ) or f ( x ).a etc.  This procedure is part of the
 * mechanism to determine whether it is necessary to insert a dummy
 * declaration to ensure that this space exists.
 */
static bool
chase ( exp sel, exp * e )
{
	exp *one ;
	bool b = 0 ;

	switch ( ( *e ) -> tag ) {

	case rep_tag:
	case ident_tag:
	case seq_tag:
	case labst_tag:
		b = chase ( sel, &next ( child ( *e ) ) ) ;
		break ;

	case solve_tag:
	case cond_tag:
		one = &child ( *e ) ;
		for ( ; ; ) {
			b = ( bool ) ( b | chase ( sel, one ) ) ;
			if ( ( *one ) -> last ) {
				break ;
			}
			one = &next ( *one ) ;
		}
		break ;

	case field_tag:
		if ( chase ( *e, &child ( *e ) ) ) {
			/* inner field has been distributed */
			exp stare = *e ;
			exp ss = child ( stare ) ;
			if ( ! stare -> last ) {
				ss ->last = false ;
			}
			next ( ss ) = next ( stare ) ;
			sh ( ss ) = sh ( stare ) ;
			*e = ss ;
			return chase ( sel, e ) ;
		}

		FALL_THROUGH;

	default:
		if ( child ( sel ) != *e && sh(*e)->tag != bothd) {
			/* only change if not outer */
			exp stare = *e ;
			exp newsel = getexp ( sh ( sel ), next ( stare ),
			                      ( int ) stare -> last, stare,
			                      NULL, props ( sel ), no ( sel ),
			                      sel->tag ) ;
			*e = newsel ;
			next ( stare ) = newsel ;
			stare ->last = true ;
			b = 1 ;
		}
	}

	if ( b ) {
		sh ( *e ) = sh ( sel ) ;
	}

	return b;
}

static exp
need_result_space ( exp e )
{
	/* dad if application needs to reserve space for struct result */
	exp dad = father ( e );

	switch (dad->tag) {
	case 0:	/* void in sequence, or param of apply_gen */
	case apply_tag:
	case caller_tag:
	case field_tag:
		return dad;

	case ident_tag:
		if (e == child (dad)) {
			return NULL;
		}

		return need_result_space (dad);

	case rep_tag:
		if (e == child (dad)) {
			return dad;
		}

		FALL_THROUGH;

	case cond_tag:
	case solve_tag:
	case labst_tag:
	case seq_tag:
#ifdef TDF_DIAG3
	case diagnose_tag:
#endif
		return need_result_space (dad);

	default:
		return NULL;
	}
}

static bool
spin_lab  ( exp lab )
{
	/* true if label implies a tight spin */
	exp dest = lab;
	exp temp, ll;

	for (;;) {
		assert (dest->tag == labst_tag);
		temp = next(child(dest));

		if (temp == NULL || temp->tag != goto_tag) {
			return 0;
		}

		ll = lab;
		for (;;) {
			if (pt(temp) == ll) {
				return 1;
			}

			if (ll == dest) {
				break;
			}

			ll = pt(next(child(ll)));
		}

		dest = pt(temp);
	}

	return 0;
}

/* Check for legal conditions for asm */
static void
id_in_asm ( exp id )
{
	if (!isparam(id) || !props(child(id))) {
		setvis (id);
	}
}

static int
is_asm_opnd ( exp e, int ext )
{
	unsigned char n = e->tag;

	UNUSED(ext);

	if (n == name_tag) {
		id_in_asm (child(e));
		return 1;
	}

	if (n == cont_tag && child(e)->tag == name_tag && isvar(child(child(e)))) {
		id_in_asm (child(child(e)));
		return 1;
	}

	return n == val_tag || n == real_tag || n == null_tag ||
	       (n == reff_tag && child(e)->tag == name_tag);
}

static int
is_asm_var ( exp e, int ext )
{
	unsigned char n = e->tag;

	UNUSED(ext);

	if (n == name_tag && isvar(child(e))) {
		id_in_asm (child(e));
		return 1;
	}

	return 0;
}

void
check_asm_seq ( exp e, int ext )
{
	if (e->tag == asm_tag) {
		if ((asm_string(e) && child(e)->tag == string_tag) ||
		    (asm_in(e) && is_asm_opnd(child(e), ext)) ||
		    (asm_var(e) && is_asm_var(child(e), ext)) ) {
			return;
		}
	}

	if (e->tag == seq_tag) {
		exp t;

		for (t = child(child(e)); ; t = next(t)) {
			check_asm_seq (t, ext);
			if (t->last) {
				break;
			}
		}

		check_asm_seq (next(child(e)), ext);
	} else if (e->tag != top_tag) {
		error(ERR_SERIOUS, "illegal ~asm");
	}
}

/*
 * SCAN AN EXPRESSION TO CALCULATE REGISTER NEEDS
 *
 * This procedure works out register requirements of an exp.  At each
 * call the fix field of the needs is the number of fixed point
 * registers required to contain live values to evaluate this
 * expression.  This never exceeds maxfix because if it would have,
 * a new declaration is introduced in the exp tree (similarly for
 * floating registers and maxfloat).  In these cases the prop field
 * will contain the bits morefix (or morefloat).
 *
 * Scan also works out various things concerned with proc calls.
 * The maxargs field contains the maximum size in bits of the space
 * required for the parameters of all the procedures called in the exp.
 *
 * An exp proc call produces a hasproccall bit in the prop field, if
 * this is transformed as part of the definition of a new declaration
 * the bit is replaced by a usesproccall. The distinction is only used
 * in unfolding nested proc calls; SPARC requires this to be done
 * statically. The condition that a proc exp is a leaf (i.e. no proc
 * calls) is that its prop contains neither bit.  If an ident exp
 * is suitable, scan marks the props of ident with either inreg or
 * infreg bits to indicate that a t-reg may be used for this tag.
 *
 * A thorough understanding of needs along with other procedures that
 * do switch ( exp->tag ) requires a knowledge of the meaning of
 * the fields of the exp in each case (this is documented somewhere).
 *
 * e is the expression to be scanned, at is the place to put any
 * new decs.  The order of recursive calls with same at is
 * critical.
 */
needs
scan ( exp * e, exp ** at )
{
	exp ste = *e ;
	int nstare = ( int ) ste->tag ;

#if 0
	/* ignore diagnostic information */
	while ( nstare == diag_tag || nstare == cscope_tag ||
	        nstare == fscope_tag ) {
		e = &child ( ste ) ;
		ste = *e ;
		nstare = ste->tag ;
	}
#endif

	switch ( nstare ) {
	case 0:
		return zeroneeds;

#if 0
	case compound_tag:
		return maxtup ( ste, at ) ;

#else
	case compound_tag:
#endif
	case nof_tag:
	case concatnof_tag:
	case ncopies_tag: {
		needs nl ;
		bool cantdo ;
		exp dad ;

		if ( ste->tag == ncopies_tag &&
		     child ( ste ) -> tag != name_tag &&
		     child ( ste ) -> tag != val_tag ) {
			nl = scan ( &child ( *e ), at ) ;
			cca ( at, &child ( *e ) ) ;
		} else {
			nl = maxtup ( *e, at ) ;
		}

		dad = father ( ste ) ;

		if ( dad->tag == compound_tag ||
		     dad->tag == nof_tag ||
		     dad->tag == concatnof_tag ) {
			cantdo = 0 ;
		} else {
			if ( ste -> last ) {
				if ( next ( ste ) -> tag == ass_tag ) {
					exp a = child ( next ( ste ) ) ;
					cantdo = ( bool ) ( a->tag != name_tag ||
					                    !isvar ( child ( a ) ) ) ;
				} else {
					cantdo = 1 ;
				}
			} else {
				if ( next ( ste ) -> last ) {
					cantdo = ( bool ) ( next ( next ( ste ) ) -> tag != ident_tag ) ;
				} else {
					cantdo = 1 ;
				}
			}
		}

		if ( cantdo ) {
			/* can only deal with tuples in simple assignment or id */
			int prpsx = ( int ) ( ( nl.propneeds & hasproccall ) << 1 ) ;
			cca ( at, ptr_position ( ste ) ) ;
			nl = shapeneeds ( sh ( *e ) ) ;
			nl.propneeds |= morefix ;
			nl.propneeds |= prpsx ;
		}

		if ( nl.fixneeds < 2 ) {
			nl.fixneeds = 2 ;
		}
		return nl;
	}

	case cond_tag: {
		/*
	    exp first = child ( ste ) ;
	    exp labst = next ( first ) ;
	    exp second = next ( child ( labst ) ) ;
		*/

		if (scan_cond(e, NULL) != 0) {
			return scan(e, at);
		}			/* else goto next case */

		FALL_THROUGH;
	}

	case labst_tag:
	case rep_tag:
	case solve_tag: {
		needs an ;
		exp *stat ;
		exp *statat ;
		stat = &child ( *e ) ;
		statat = stat ;

		an = zeroneeds ;
		while ( an = maxneeds ( an, scan ( stat, &statat ) ),
		        !(*stat)->last ) {
			stat = &next ( *stat ) ;
			statat = stat ;
		}

		if ( ( an.propneeds & usesproccall ) != 0 ) {
			an.propneeds |= hasproccall ;
		}

		return an;
	}

	case ident_tag: {
		needs bdy ;
		needs def ;
		exp stare = *e ;
		exp *arg = &next ( child ( stare ) ) ;
		exp t, s ;
		bool fxregble ;
		bool flregble ;
		bool old_nonevis = nonevis ;

		if ( no ( stare ) == 0 ) {
			/* no uses, should have caonly flag and no var flag */
			setcaonly ( stare ) ;
			clearvar ( stare ) ;

#ifdef TDF_DIAG4
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

		if (child(stare)->tag == formal_callee_tag) {
			setvis(stare);
		}

		if ( isparam ( stare ) && child(stare)->tag != formal_callee_tag) {
			/* Use the input regs %i0..%i5 for first 6*32 bits of params */
			exp def2 = child ( stare ) ;
			shape shdef = sh ( def2 ) ;
			int n = stparam ;
			int sizep = ( int ) shape_size ( shdef ) ;
			int last_reg;

			if ((gencompat && !trad_proc) || (!gencompat && gen_call)) {
				if (v_proc) {
					last_reg = 4;
				} else {
					last_reg = 5;
				}
			} else {
				last_reg = 6;
			}

			assert ( def2->tag == clear_tag ) ;
			if ( ( stparam >> 5 ) < ( last_reg ) /*&& !(isenvoff(stare))*/ ) {
				/* Param regs %i0..%i5 */
				/* is >= 1 param reg free for (part-of) the param */
				/* Use an available param reg */
				if (v_proc && (stparam >> 5) == last_reg) {
					/* reserve R_I5 for use as local reg */
					props(def2) = 0;
					stparam += 32;
					n = stparam;
				} else {
					props ( def2 ) = ( prop ) fixparam ;
				}
			} else {
				/* Pass by stack */
				/* envoffset'ed this way always */
				props ( def2 ) = 0 ;
			}

			/* "offset" in params */
			no ( def2 ) = n ;
			stparam = rounder ( n + sizep, 32 ) ;
			/* ( stparam / 32 ) */
			fixparam = R_I0 + ( stparam >> 5 ) ;
		} else if (isparam(stare) && child(stare)->tag == formal_callee_tag) {
			exp def2 = child(stare);
			exp shdef = sh(def2);
			int sizep = shape_size(shdef);
			int alp = shape_align(shdef);
			int n = rounder(callee_size, alp);
			no(def2) = n;
			callee_size = rounder(n + sizep, 32);
			props(def2) = 0;
		}

		nonevis = nonevis & !isvis ( stare ) ;

		bdy = scan ( arg, &arg ) ;
#if NO_TREG
		/* force minimal t-reg usage */
		bdy.fixneeds = maxfix ;
#endif
		/* scan the body-scope */
		arg = &child ( stare ) ;
		/* scan the initialisation of tag */
		def = scan ( arg, &arg ) ;

		nonevis = old_nonevis ;
		t = child ( stare ) ;
		s = next ( t ) ;
		fxregble = fixregable ( stare ) ;
		flregble = floatregable ( stare ) ;

		if ( isparam ( stare ) ) {
			if (child(stare)->tag != formal_callee_tag) {
				/* reg for param or else 0 */
				int x = ( int ) props ( child ( stare ) ) ;
				/* bit size of param */
				int par_size = shape_size ( sh ( child ( stare ) ) ) ;

				if ( par_size == 8 || par_size == 16 ) {
					/* on to right end of word */
					no ( child ( stare ) ) += 32 - par_size ;
				}

				if ( x != 0 && fxregble ) {
					/* leave suitable pars in par regs */
					no ( stare ) = x ;
					pset ( stare, inreg_bits ) ;
				} else {
					if ( x != 0 && flregble ) {
						/* Caller has placed float param in par regs;
						callee must store it out for use in float regs */
						no ( stare ) = 0 ;
					} else {
						/* Otherwise caller has placed param on stack */
						no ( stare ) = R_NO_REG ;
					}
				}
			} else {
				no(stare) = R_NO_REG;
			}
		} else {
			if ( !isvis ( *e ) && isparam ( *e ) && !isoutpar(stare) &&
			     ( bdy.propneeds & ( anyproccall | uses_res_reg_bit ) ) == 0 &&
			     ( fxregble || flregble ) &&
			     ( ((t->tag == apply_tag) || (t->tag == apply_general_tag)) ||
			       ( s->tag == seq_tag &&
			         next ( child ( s ) ) -> tag == res_tag &&
			         child ( next ( child ( s ) ) ) -> tag == cont_tag &&
			         isvar ( stare ) &&
			         child ( child ( next ( child ( s ) ) ) ) -> tag == name_tag &&
			         child ( child ( child ( next ( child ( s ) ) ) ) ) ==
			         stare ) ) ) {
				/* Let a: = .. ; return cont a */
				/* integrate this with the block above,
				   otherwise UNREACHED */
				/* put tag in result reg if definition is call of proc,
				   or body ends with return tag, provided result is not
				   used otherwise */
				pset ( stare, ( fxregble ? inreg_bits: infreg_bits ) ) ;
				bdy.propneeds |= uses_res_reg_bit ;
				/* identification uses result reg in body */
				no ( stare ) = R_USE_RES_REG ;
			} else if (isenvoff(stare)) { /* MUST go on stack */
				no ( stare ) = R_NO_REG ;
			} else if ( !isvar ( *e ) && !isparam ( *e ) &&
			            /* reff cont variable-not assigned to in scope */
			            ( ( t->tag == reff_tag &&
			                child ( t ) -> tag == cont_tag &&
			                child ( child ( t ) ) -> tag == name_tag &&
			                isvar ( child ( child ( child ( t ) ) ) ) &&
			                !isvis ( child ( child ( child ( t ) ) ) ) &&
			                !isglob ( child ( child ( child ( t ) ) ) ) &&
			                unchanged ( child ( child ( child ( t ) ) ),
			                            stare ) ) ||
			              /* cont variable - not assigned to in scope */
			              ( t->tag == cont_tag &&
			                child ( t ) -> tag == name_tag &&
			                isvar ( child ( child ( t ) ) ) &&
			                !isvis ( child ( child ( t ) ) ) &&
			                !isglob ( child ( child ( t ) ) ) &&
			                unchanged ( child ( child ( t ) ),
			                            stare ) ) ) ) {
				/* don't take space for this dec */
				pset ( stare, defer_bit ) ;
			} else if ( !isvar ( stare ) &&
			            ( ( props ( stare ) & 0x10 ) == 0 ) &&
			            ( t->tag == name_tag ||
			              t->tag == val_tag ) ) {
				/* don't take space for this dec */
				pset ( stare, defer_bit ) ;
			} else if ( fxregble &&
			            (bdy.propneeds & morefix) == 0 &&
			            (bdy.fixneeds < maxfix &&
			             ( /*isinlined(stare) ||*/
			                 ( bdy.propneeds & morefix ) == 0 &&
			                 ( ( bdy.propneeds & anyproccall ) == 0 ||
			                   tempdec ( stare, ( bool )
			                             ( ( bdy.propneeds & morefix ) == 0 &&
			                               bdy.fixneeds < maxfix_tregs - 2 )))))) {
				/* put this tag in some fixpt t-reg - which will be
				   decided in make_code */
				pset ( stare, inreg_bits ) ;
				no ( stare ) = 0 ;
				bdy.fixneeds += 1 ;
			} else if ( bdy.floatneeds < maxfloat &&
			            ( bdy.propneeds & morefloat ) == 0 &&
			            flregble &&
			            ( ( bdy.propneeds & anyproccall ) == 0 ||
			              tempdec ( stare, ( bool )
			                        ( ( bdy.propneeds & morefloat ) == 0 &&
			                          bdy.floatneeds < MAXFLOAT_TREGS - 1 ) ) ) ) {
				/* put this tag in some float t-reg - which will be
				   decided in make_code */
				pset ( stare, infreg_bits ) ;
				no ( stare ) = 0 ;
				bdy.floatneeds += 1 ;
				/* add isinlined when you enable float
				   reg allocation.... */
			} else {
				/* allocate either on stack or saved reg */
				no ( stare ) = R_NO_REG ;
			}
		}

		bdy = maxneeds ( bdy, def ) ;
		if ( ( bdy.propneeds & usesproccall ) != 0 ) {
			bdy.propneeds |= hasproccall ;
		}

		return bdy;
	}

	case seq_tag: {
		exp *arg = &next ( child ( *e ) ) ;
		needs an ;
		exp *stat ;
		an = scan ( arg, &arg ) ;
		stat = &child ( child ( *e ) ) ;

		arg = stat ;
		for ( ; ; ) {
			needs stneeds ;
			stneeds = scan ( stat, &arg ) ;
			/* initial statements voided */
			an = maxneeds ( an, stneeds ) ;
			if ( ( *stat ) -> last ) {
				if ( ( an.propneeds & usesproccall ) != 0 ) {
					an.propneeds |= hasproccall ;
				}
				return an;
			}

			stat = &next ( *stat ) ;
			arg = stat ;
		}

		UNREACHED;
	}

	case goto_tag: {
		needs nr ;

		nr = zeroneeds ;
		if (!sysV_assembler && spin_lab (pt(*e))) {
			nr.propneeds |= dont_optimise ; /* otherwise the SunOS assembler spins */
		}

		return nr;
	}

	case ass_tag:
	case assvol_tag: {
		exp *lhs = &child ( *e ) ;
		exp *rhs = &next ( *lhs ) ;
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

		if ( ( *lhs ) -> tag == name_tag &&
		     ( isvar ( child ( *lhs ) ) ||
		       ( ( nr.propneeds & ( hasproccall | morefix ) ) == 0 &&
		         nr.fixneeds < maxfix ) ) ) {
			/* simple destination */
			return nr;
		} else {
			needs nl ;
			prop prpx = ( prop ) ( ( nr.propneeds & hasproccall ) << 1 ) ;

			nl = scan ( lhs, at ) ;
			if ( ((*rhs)->tag == apply_tag || (*rhs)->tag == apply_general_tag) &&
			     nstare == ass_tag && (nl.propneeds & ( uses_res_reg_bit | anyproccall )) == 0) {
				/* source is proc call, so assign result reg directly */
				/* SKIP */ ;
			} else if ( nr.fixneeds >= maxfix || prpx != 0 ) {
				/* source and dest regs overlap, so identify source */
				cca ( at, rhs ) ;
				nl = shapeneeds ( sh ( *rhs ) ) ;
				nl.propneeds |= morefix ;
				nl.propneeds |= ( prpx >> 1 ) ;
				nl.propneeds |= prpx ;
			}

			nr.fixneeds += 1 ;
			return maxneeds ( nl, nr ) ;
		}
	}

	case untidy_return_tag:
	case res_tag: {
		ash a ;
		needs x ;
		shape s ;
		exp *arg = &child ( *e ) ;

		s = sh ( *arg ) ;
		a = ashof ( s ) ;
		/* clear possibility of tlrecirsion ; may be set later */
		props ( *e ) = 0 ;
		x = scan ( arg, at ) ;
		/* scan result exp ... */

		if ( is_floating ( s->tag ) && a.ashsize <= 64 ) {
			/* ... floating pt result */
			x.propneeds |= realresult_bit ;
			if ( s->tag != shrealhd ) {
				x.propneeds |= longrealresult_bit ;
			}
		} else {
			if ( !valregable ( s ) && s->tag != tophd ) {
				/* ... result does not fit into reg */
				x.propneeds |= long_result_bit ;
			}
		}

		if ( a.ashsize != 0 && ( *arg ) -> tag != clear_tag ) {
			/* ...not a void result */
			x.propneeds |= has_result_bit ;
		}

#if 0
		/* replace R_USE_RES_REG (from mips) by R_USE_R_I0 (here)
		and R_USE_RO0 (ident_tag above) */
		/* for present R_USE_RES_REG means R_USE_R_O0 */
		/* MIPS has single res reg, on SPARC it is windowed per-proc */
		if ( ( x & ( long_result_bit | anyproccall | uses_res_reg_bit ) ) == 0 ) {
			r = child ( *e ) ;
			if ( r->tag == ident_tag && isvar ( r ) &&
			     ( ss = next ( child ( r ) ) ) -> tag == seq_tag &&
			     ( t = next ( child ( ss ) ) ) -> tag == cont_tag &&
			     child ( t ) -> tag == name_tag &&
			     child ( child ( t ) ) == r )
			{
				/* result is tag allocated into result reg - see ident */
				if ( ( props ( r ) & inreg_bits ) != 0 ) {
					x.fixneeds-- ;
				} else if ( ( props ( r ) & infreg_bits ) != 0 ) {
					x.floatneeds-- ;
				} else {
					props ( r ) |= ( is_floating ( s->tag ) ) ?
					               infreg_bits: inreg_bits ;
				}

				x.propneeds |= uses_res_reg_bit ;
				/* identification uses result reg in body */
				no ( r ) = R_USE_RES_REG ;
			}
		}
#endif

		return x;
	}

	case apply_general_tag: {
		exp application = *(e);
		exp *fn = &child(application);
		exp callers = next(*fn);
		exp *cerl = &child(callers);
		int stpar = 0;
		needs nds, pstldnds;
		int i;
		nds = scan(fn, at);

		/* Identify it */
		if (nds.propneeds & hasproccall) {
			cca(at, fn);
			nds.propneeds &= ~hasproccall;
			nds.propneeds |= usesproccall;
			fn = &child(application);
		}

		for (i = 0; i < no(callers); ++i) {
			needs onepar;
			shape shonepar = sh(*cerl);
			exp * par = (*cerl)->tag == caller_tag ? &child(*cerl): cerl;
			int n = rounder(stpar + shape_size(shonepar), 32);
			onepar = scan(par, at);

			if ((/*(i != 0) && */ (onepar.propneeds & hasproccall)) ||
			   (onepar.fixneeds + (stpar >> 5) > maxfix)) {
				/* not the first parameter, and calls a proc */
				/* or the first if we need to preserve callee_start_reg */
				cca(at, par);
				nds.propneeds |= usesproccall;
				nds = maxneeds(shapeneeds(sh(*(par))), nds);
				nds.maxargs = MAX(nds.maxargs, onepar.maxargs);
			} else {
				nds = maxneeds(onepar, nds);
			}

			if ((*cerl)->tag == caller_tag) {
				no(*cerl) = stpar;
			}

			stpar = n;
			cerl = &next(*cerl);
		}
		nds.maxargs = MAX(nds.maxargs, stpar);
		maxfix -= 6;
		nds = maxneeds(scan(&next(next(child(application))), at), nds);
		maxfix += 6;
		pstldnds = scan(&next(next(next(child(application)))), at);
		if (pstldnds.propneeds & anyproccall) {
			set_postlude_has_call(application);
		} else {
			clear_postlude_has_call(application);
		}
		nds = maxneeds(nds, pstldnds);
		if ( sparccpd (sh(application)) ) {
			exp ap_context = need_result_space(application);
			if (ap_context != NULL) {
				/* find space for tuple result */
				assert ( ( * ptr_position ( application ) ) -> tag == apply_general_tag ) ;
				cca ( at, ptr_position ( application ) ) ;
				if (ap_context->tag != field_tag) {
					/* if context is application parameter, treat as pointer */
					setvar (next(next(application)));
					sh(pt(next(next(application)))) = f_pointer(f_alignment(sh(application)));
				}
				nds.propneeds |= usesproccall ;
			} else {
				nds.propneeds |= hasproccall ;
			}
		} else if ( next(next(next(child(application))))->tag != top_tag && valregable(sh(application))
		            && sh(application)->tag != tophd && sh(application)->tag != bothd ) {
			cca ( at, ptr_position ( application ) ) ;
			nds.propneeds |= usesproccall ;
		} else {
			nds.propneeds |= hasproccall ;
		}
		return nds;
	}
	case make_callee_list_tag: {
		exp cllees = *e;
		exp *par = &child(cllees);
		needs nds;
		int stpar = 0, i;
		nds = zeroneeds;
		for (i = 0; i < no(cllees); ++i) {
			needs onepar;
			shape shonepar = sh(*par);
			int n = rounder(stpar, shape_align(shonepar));
			onepar = scan(par, at);
			if ((onepar.propneeds & hasproccall) || (onepar.fixneeds + 1 > maxfix)) {
				/* identify it */
				cca(at, par);
				nds.propneeds |= usesproccall;
				nds = maxneeds(shapeneeds(sh(*par)), nds);
				nds.maxargs = MAX(nds.maxargs, onepar.maxargs);
			} else {
				nds = maxneeds(onepar, nds);
			}
			n += shape_size(shonepar);
			stpar = rounder(n, REG_SIZE);
			par = &next(*par);
		}
		no(cllees) = stpar;
		return nds;
	}
	case make_dynamic_callee_tag: {
		exp cllees = *e;
		exp *ptr = &child(cllees);
		needs ndsp, nds;
		nds = zeroneeds;
		ndsp = scan(ptr, at);
		if ((ndsp.propneeds & hasproccall) || (ndsp.fixneeds + 1 > maxfix)) {
			cca(at, ptr);
			nds.propneeds |= usesproccall;
			nds = maxneeds(shapeneeds(sh(*ptr)), nds);
			nds.maxargs = MAX(nds.maxargs, ndsp.maxargs);
		} else {
			nds = ndsp;
		}
		ndsp = scan(&next(child(cllees)), at);
		if ((ndsp.propneeds & hasproccall) || (ndsp.fixneeds + 2 > maxfix)) {
			cca(at, &next(child(cllees)));
			nds.propneeds |= usesproccall;
			nds = maxneeds(shapeneeds(sh(next(child(cllees)))), nds);
			nds.maxargs = MAX(nds.maxargs, ndsp.maxargs);
		} else {
			nds = maxneeds(ndsp, nds);
		}
		if (nds.fixneeds < 10) {
			nds.fixneeds = 10;    /* ?? */
		}
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
		needs ndsp, nds;
		exp *fn = &child(tlcl);
		ndsp = scan(fn, at);
		if ((ndsp.propneeds & hasproccall) || (ndsp.fixneeds + 1 > maxfix)) {
			cca(at, fn);
			nds.propneeds |= usesproccall;
			nds = maxneeds(shapeneeds(sh(*fn)), nds);
			nds.maxargs = MAX(nds.maxargs, ndsp.maxargs);
		} else {
			nds = ndsp;
		}
		ndsp = scan(&next(child(tlcl)), at);
		nds = maxneeds(nds, ndsp);
		if (nds.fixneeds < 6) {
			nds.fixneeds = 6;
		}
		return nds;
	}

	case apply_tag: {
		int i ;
		needs nds ;
		int parsize = 0 ;
		exp appl = *e ;
		exp fn = child ( appl ) ;
		exp *par = &next ( fn ) ;
		exp *fnexp = &child ( appl ) ;
		bool tlrecpos = nonevis && callerfortr ;

		nds = scan ( fnexp, at ) ;
		/* scan the function exp ... */
		if ( nds.propneeds & hasproccall ) {
			/* ... it must be identified */
			cca ( at, fnexp ) ;
			nds.propneeds &= ~hasproccall ;
			nds.propneeds |= usesproccall ;
			fn = child ( appl ) ;
			par = &next ( fn ) ;
		}

		if ( fn->tag != name_tag ||
		     ( child ( child ( fn ) ) != NULL &&
		       ((child ( child ( fn ) ) -> tag != proc_tag ) ||
		        child(child(fn))->tag == general_proc_tag))) {
			tlrecpos = 0 ;
		}

		for ( i = 1 ; ! fn -> last ; ++i ) {
			/* scan parameters in turn ... */
			needs onepar ;
			shape shpar = sh ( *par ) ;
			onepar = scan ( par, at ) ;

			if ( ( i != 1 && ( onepar.propneeds & hasproccall ) ) ||
			     onepar.fixneeds + ( parsize >> 5 ) > maxfix ) {
				/* if it isn't the first parameter, and it calls
				   a proc, identify it */
				cca ( at, par ) ;
				nds.propneeds |= usesproccall ;
				nds = maxneeds ( shapeneeds ( sh ( *par ) ), nds ) ;
				nds.maxargs = MAX ( nds.maxargs, onepar.maxargs ) ;
			} else {
				nds = maxneeds ( onepar, nds ) ;
			}
			parsize = ( int ) rounder ( parsize, shape_align ( shpar ) ) ;
			parsize = rounder ( parsize + shape_size ( shpar ), 32 ) ;
			if ( ( !valregable ( shpar ) &&
			       !is_floating ( shpar->tag ) ) ||
			     parsize > 128 ) {
				tlrecpos = 0 ;
			}
			if ( ( *par ) -> last ) {
				break ;
			}
			par = &next ( *par ) ;
		}

		if ( specialopt ( fn ) ) {
			/* eg vfork */
			nds.propneeds |= dont_optimise ;
		}

		if ( ( i = specialfn ( fn ) ) > 0 ) {
			/* eg strlen */
			nds = maxneeds ( specialneeds ( i ), nds ) ;
			return nds;
		}

		if ( tlrecpos ) {
			exp dad = father ( appl ) ;
			if ( dad->tag == res_tag ) {
				props ( dad ) = 1 ;     /* do a tl recursion */
			}
		}

		if ( sparccpd (sh(appl)) ) {
			exp ap_context = need_result_space(appl);
			if (ap_context != NULL) {
				/* find space for tuple result */
				assert ( ( * ptr_position ( appl ) ) -> tag == apply_tag ) ;
				cca ( at, ptr_position ( appl ) ) ;
				if (ap_context->tag != field_tag) {
					/* if context is application parameter, treat as pointer */
					setvar (next(next(appl)));
					sh(pt(next(next(appl)))) = f_pointer(f_alignment(sh(appl)));
				}
				nds.propneeds |= usesproccall ;
			} else {
				nds.propneeds |= hasproccall ;
			}
		} else {
			nds.propneeds |= hasproccall ;
		}
		nds.maxargs = MAX ( nds.maxargs, parsize ) ;
		/* clobber %o0..%o5,%o7 */
		nds.fixneeds = MAX ( nds.fixneeds, 8 ) ;
		return nds;

	}
	case movecont_tag: {	/* Only whilst it aways generates memmove */
		int i ;
		needs nds ;
		int parsize = 0 ;
		exp mv = *e ;
		exp *par = &child ( mv ) ;
		bool tlrecpos = nonevis && callerfortr ;
		nds = zeroneeds;

		for ( i = 1 ; i <= 3 ; ++i ) {
			/* scan parameters in turn ... */
			needs onepar ;
			shape shpar = sh ( *par ) ;
			onepar = scan ( par, at ) ;

			if ( ( i != 1 && ( onepar.propneeds & hasproccall ) ) ||
			     onepar.fixneeds + ( parsize >> 5 ) > maxfix ) {
				/* if it isn't the first parameter, and it calls
				   a proc, identify it */
				cca ( at, par ) ;
				nds.propneeds |= usesproccall ;
				nds = maxneeds ( shapeneeds ( sh ( *par ) ), nds ) ;
				nds.maxargs = MAX ( nds.maxargs, onepar.maxargs ) ;
			} else {
				nds = maxneeds ( onepar, nds ) ;
			}
			parsize = ( int ) rounder ( parsize, shape_align ( shpar ) ) ;
			parsize = rounder ( parsize + shape_size ( shpar ), 32 ) ;
			if ( ( !valregable ( shpar ) &&
			       !is_floating ( shpar->tag ) ) ||
			     parsize > 128 ) {
				tlrecpos = 0 ;
			}
			assert ((i != 3) || (*par)->last);
			par = &next ( *par ) ;
		}


		if ( tlrecpos ) {
			exp dad = father ( mv ) ;
			if ( dad->tag == res_tag ) {
				props ( dad ) = 1 ;     /* do a tl recursion */
			}
		}

		nds.propneeds |= hasproccall ;

		nds.maxargs = MAX ( nds.maxargs, parsize ) ;
		/* clobber %o0..%o5,%o7 */
		nds.fixneeds = MAX ( nds.fixneeds, 7 ) ;
		return nds;
	}

	case val_tag: {
		exp s = sh ( *e ) ;
		if ( s->tag == offsethd && al2 ( s ) >= 8 ) {
			/* express disps in bytes */
			no ( *e ) = no ( *e ) >> 3 ;
		}

		FALL_THROUGH;
	}

	case env_size_tag:
	case caller_name_tag:
	case null_tag:
	case real_tag:
	case string_tag:
	case env_offset_tag:
	case current_env_tag:
	case make_lv_tag:
	case last_local_tag: {
		return shapeneeds ( sh ( *e ) ) ;
	}
	case name_tag: {
		needs nds;
		nds = shapeneeds ( sh ( *e ) ) ;
		if (PIC_code && isglob (child(*e))) {
			long boff = no(*e) >> 3 ;
			if (boff < -4096 || boff > 4095) {
				nds.fixneeds += 1 ;
			}
		}
		return nds;
	}
	case give_stack_limit_tag: {
		specialext = 1;
		return shapeneeds ( sh ( *e ) ) ;
	}
	case formal_callee_tag:
	case clear_tag:
	case top_tag:
	case prof_tag:
	case local_free_all_tag: {
		return zeroneeds;
	}
	case local_free_tag: {
		needs nds;
		nds = scan( &child(*e), at);
		if (nds.fixneeds < 2) {
			nds.fixneeds = 2;
		}
	}

	case set_stack_limit_tag: {
		exp *arg = &child ( *e ) ;
		specialext = 1;
		return scan ( arg, at ) ;
	}
#ifdef return_to_label_tag
	case return_to_label_tag:
#endif
#ifdef TDF_DIAG3
	case diagnose_tag:
#endif
	case goto_lv_tag:
	case abs_tag:
	case neg_tag:
	case not_tag:
	case offset_negate_tag: {
		exp *arg = &child ( *e ) ;
		if (error_treatment_is_trap ( *e )) {
			specialext = 1;
		}
		return scan ( arg, at ) ;
	}
	case case_tag: {
		needs s;
		exp *arg = &child ( *e ) ;

		s = scan ( arg, at ) ;
		s.fixneeds = MAX ( s.fixneeds, 2 ) ; /* dense case calls getreg */
		return s;
	}

	case fneg_tag:
	case fabs_tag:
	case chfl_tag: {
		needs nds ;
		exp *pste;
		if (error_treatment_is_trap ( *e )) {
			specialext = 1;
		}
		nds = scan ( &child ( *e ), at ) ;
		pste = ptr_position(ste);
		if ( !optop ( *pste ) && nds.fixneeds < 2 ) {
			nds.fixneeds = 2 ;
		}
		if ((has & HAS_LONG_DOUBLE)) {
			exp op = *pste ;
			if ( sh ( op ) -> tag == doublehd ||
			     sh ( child ( op ) ) -> tag == doublehd ) {
#if 0
				if (*e->tag == fabs_tag) {
					replace_fabs(ste);
				}
#endif
				if ( !is_o ( child ( op ) -> tag ) || ( nds.propneeds & hasproccall ) ) {
					cca ( at, &child ( op ) ) ;
				}
				nds.propneeds |= hasproccall ;
			}
		}
		return nds;
	}

	case bitf_to_int_tag: {
		exp *arg = &child ( *e ) ;
		needs nds ;
		exp stararg ;
		exp stare ;
		int sizeb ;

		nds = scan ( arg, at ) ;
		stararg = *arg ;
		stare = *e ;
		sizeb = shape_size ( sh ( stararg ) ) ;
		if ( ( stararg->tag == name_tag &&
		       ( ( sizeb == 8 &&
		           ( no ( stararg ) & 7 ) == 0 ) ||
		         ( sizeb == 16 &&
		           ( no ( stararg ) & 15 ) == 0 ) ||
		         ( sizeb == 32 &&
		           ( no ( stararg ) & 31 ) == 0 ) ) ) ||
		     ( stararg->tag == cont_tag &&
		       ( ( child ( stararg ) -> tag != name_tag &&
		           child ( stararg ) -> tag != reff_tag ) ||
		         ( sizeb == 8 &&
		           ( no ( child ( stararg ) ) & 7 ) == 0 ) ||
		         ( sizeb == 16 &&
		           ( no ( child ( stararg ) ) & 15 ) == 0 ) ||
		         ( sizeb == 32 &&
		           ( no ( child ( stararg ) ) & 31 ) == 0 ) ) ) ) {
			/* these bitsint ( trimnof ( X ) ) could be implemented by
			   lb or lh instructions ... */
			int sgned = sh ( stare ) -> tag & 1 ;
			shape ns = ( sizeb == 8 ) ? ( sgned ? scharsh: ucharsh ):
			           ( sizeb == 16 ) ? ( sgned ? swordsh: uwordsh ):
			           sh ( stare ) ;
			/* can use short loads instead of bits extractions */
			if ( stararg->tag == cont_tag ) {
				/* make the ptr shape consistent */
				sh ( child ( stararg ) ) = f_pointer ( long_to_al (
				        ( long ) shape_align ( ns ) ) ) ;
			}
			sh ( stararg ) = ns ;
			 stare->tag = chvar_tag  ;
		}
		return nds;
	}

	case int_to_bitf_tag: {
		exp *arg = &child ( *e ) ;
		return scan ( arg, at ) ;
	}
	case round_tag: {
		needs s ;
		exp *arg ;
		exp *pste;
		int rm = ( int ) round_number ( *e ) ;
		if (error_treatment_is_trap ( *e )) {
			specialext = 1;
		}
		arg = &child ( *e ) ;
		s = scan ( arg, at ) ;
		pste = ptr_position(ste);
		s.fixneeds = MAX ( s.fixneeds, 2 ) ;
		if ( rm < 3 || sh ( *pste ) -> tag == ulonghd ) {
			s.floatneeds = MAX ( s.floatneeds, 3 ) ;
		} else {
			s.floatneeds = MAX ( s.floatneeds, 2 ) ;
		}
		if ((has & HAS_LONG_DOUBLE)) {
			exp op = *pste ;

			if ( sh ( child ( op ) ) -> tag == doublehd ) {
				if ( !is_o ( child ( op ) -> tag ) || ( s.propneeds & hasproccall ) ) {
					cca ( at, &child ( op ) ) ;
				}
				s.propneeds |= hasproccall ;
			}
		}
		return s;
	}

	case shl_tag:
	case shr_tag:
	case long_jump_tag: {
		int prpx ;
		needs nl, nr ;
		exp *lhs = &child ( *e ) ;
		exp *rhs = &next ( *lhs ) ;

		nr = scan ( rhs, at ) ;
		nl = scan ( lhs, at ) ;
		rhs = &next(*lhs);
		prpx = ( int ) ( ( nr.propneeds & hasproccall ) << 1 ) ;

		if ( nr.fixneeds >= maxfix || prpx != 0 ) {
			/* if reg requirements overlap, identify second operand */
			cca ( at, rhs ) ;
			nl = shapeneeds ( sh ( *rhs ) ) ;
			nl.propneeds |= morefix ;
			nl.propneeds &= ~(prpx >> 1) ;
			nl.propneeds |= prpx ;
		}
		nr.fixneeds += 1 ;
		nr.fixneeds += 1 ;	/* why? */
		return maxneeds ( nl, nr ) ;
	}

	case test_tag: {
		exp stare = *e ;
		exp l = child ( stare ) ;
		exp r = next ( l ) ;

		if ( ! stare -> last && next ( stare ) -> tag == test_tag &&
		     test_number ( stare ) == test_number ( next ( stare ) ) &&
		     eq_exp ( l, child ( next ( stare ) ) ) &&
		     eq_exp ( r, next ( child ( next ( stare ) ) ) ) ) {
			/* same test following in seq list - remove second test */
			if ( next ( stare ) -> last ) {
				stare ->last = true ;
			}
			next ( stare ) = next ( next ( stare ) ) ;
			no(child(pt(stare))) --; /* one less way there */
		}

		if ( stare -> last && next ( stare ) -> tag == 0 &&
		     next ( next ( stare ) ) -> tag == test_tag &&
		     next ( next ( next ( stare ) ) ) -> tag == seq_tag &&
		     test_number ( stare ) ==
		     test_number ( next ( next ( stare ) ) ) &&
		     eq_exp ( l, child ( next ( next ( stare ) ) ) ) &&
		     eq_exp ( r, next ( child ( next ( next ( stare ) ) ) ) ) ) {
			/* same test following in seq res - void second test */
			next ( next ( stare ) ) -> tag = top_tag ;
			child ( next ( next ( stare ) ) ) = NULL ;
			pt ( next ( next ( stare ) ) ) = NULL ;
			no(child(pt(stare))) --; /* one less way there */
		}

		assert ((l->tag == val_tag) ? (r->tag == val_tag): 1);
		/* jmf claims to have put one val
		   on right,so only allow val
		   test val */

		if ( r->tag == val_tag &&
		     (props(stare) == 5 || props(stare) == 6) && /* eq/neq */
		     no (r) == 0 &&	/* against 0 */
		     l->tag == and_tag && next (child (l))->tag == val_tag &&
		     (no (next (child (l))) & (no (next (child (l))) - 1)) == 0
		   ) {
			/* zero test  x & 2^n   -> neg test (x shl
			   (31-n)) */
			long  n = no (next (child (l)));
			int   x;
			for (x = 0; n > 0; x++) {
				n = n << 1;
			}
			if (x == 0) {		/* no shift required */
				next (child (l)) = r;	/* zero there */
				child (stare) = child (l);/* x */
			} else {
				l->tag = shl_tag;
				no (next (child (l))) = x;
			}
			props (stare) -= 3;	/* test for neg */
			sh (child (stare)) = slongsh;

		}

		if ( l->tag == bitf_to_int_tag &&
		     r->tag == val_tag &&
		     ( props ( stare ) == 5 || props ( stare ) == 6 ) &&
		     ( child ( l ) -> tag == cont_tag ||
		       child ( l ) -> tag == name_tag ) ) {
			/* equality of bits against +ve consts doesnt need
			   sign adjustment */
			long n = no ( r ) ;
			switch ( sh ( l ) -> tag ) {
			case scharhd: {
				if ( n >= 0 && n <= 127 ) {
					sh ( l ) = ucharsh ;
				}
				break ;
			}
			case swordhd: {
				if ( n >= 0 && n <= 0xffff ) {
					sh ( l ) = uwordsh ;
				}
				break ;
			}
			}
		} else if ( is_floating ( sh ( l ) -> tag ) ) {
			return fpop ( e, at ) ;
		} else if ( r->tag == val_tag && no ( r ) == 1 &&
		            ( props ( stare ) == 3 || props ( stare ) == 2 ) ) {
			no ( r ) = 0 ;
			if ( props ( stare ) == 3 ) {
				/* branch >= 1 -> branch > 0 */
				props ( stare ) = 4 ;
			} else {
				/* branch < 1 -> branch <= 0 */
				props ( stare ) = 1 ;
			}
		}
		return likediv ( e, at ) ;
	}

	case plus_tag: {
		/* replace any operands which are neg ( .. ) by -, if poss */
		exp sum = *e ;
		exp list = child ( sum ) ;
		bool someneg = 0 ;
		bool allneg = 1 ;
		if (error_treatment_is_trap ( *e )) {
			specialext = 1;
		}

		for ( ; optop ( sum ) ; ) {
			if ( list->tag == neg_tag ) {
				someneg = 1 ;
			} else {
				allneg = 0 ;
			}
			if ( list -> last ) {
				break ;
			}
			list = next ( list ) ;
		}

		if ( someneg ) {
			/* there are some neg () operands */
			if ( allneg ) {
				/* transform - .. - ... to - ( .. + .. + ... ) */
				exp x ;
				/* Build a new list form operand of neg_tags, which
				   will become plus_tag operands */
				x = child ( sum ) ;
				list = child ( x ) ;
				for ( ; ; ) {
					/* 'x' moves along neg_tag's lists 'list' moves
					   along children of neg_tag's lists, building a new list
					   eventually new list is made child of plus_tag */
					if ( ! x -> last ) {
						next ( list ) = child ( next ( x ) ) ;
						list ->last = false ;
						list = next ( list ) ;
						x = next ( x ) ;
					} else {
						/* set father to be */
						next ( list ) = sum ;
						list ->last = true ;
						/* set new children of plus_tag */
						child ( sum ) = child ( child ( sum ) ) ;
						break ;
					}
				}

				/* create new neg_tag to replace plus_tag, old
				   plus_tag being the operand of the new neg_tag */
				x = getexp ( sh ( sum ), next ( sum ), ( int ) sum -> last,
				             sum, NULL, 0, 0, neg_tag ) ;
				sum ->last = true ;
				/* set father of sum, new neg_tag exp */
				next ( sum ) = x ;
				*e = x ;
			} else {
				/* transform to ( ( .. ( .. + .. ) - .. ) - .. ) */
				int n = 0 ;
				exp nextsum = next ( sum ) ;
				bool lastsum = ( bool ) sum -> last ;
				exp x = child ( sum ) ;
				exp newsum = sum ;

				list = NULL ;
				for ( ; ; ) {
					exp nxt = next ( x ) ;
					bool final = ( bool ) x -> last ;

					if ( x->tag == neg_tag ) {
						next ( child ( x ) ) = list ;
						list = child ( x ) ;
					} else {
						next ( x ) = newsum ;
						newsum = x ;
						if ( ( n++ ) == 0 ) {
							newsum ->last = true ;
						} else {
							newsum ->last = false ;
						}
					}
					if ( final ) {
						break ;
					}
					x = nxt ;
				}

				if ( n > 1 ) {
					child ( sum ) = newsum ;
					/* use existing exp for add operations */
					newsum = sum ;
				}
				for ( ; ; ) {
					/* introduce - operations */
					exp nxt = next ( list ) ;
					next ( newsum ) = list ;
					newsum ->last = false ;
					x = getexp ( sh ( sum ), NULL, 0, newsum, NULL,
					             0, 0, minus_tag ) ;
					next ( list ) = x ;
					list ->last = true ;
					newsum = x ;
					if ( ( list = nxt ) == NULL ) {
						break ;
					}
				}

				next ( newsum ) = nextsum ;
				if ( lastsum ) {
					newsum ->last = true ;
				} else {
					newsum ->last = false ;
				}

				*e = newsum ;
			}

			return scan ( e, at ) ;
		}

		FALL_THROUGH;
	}

	case and_tag:
	case or_tag:
	case xor_tag:
		return likeplus ( e, at ) ;

#ifdef make_stack_limit_tag
	case make_stack_limit_tag:
#endif
	case minus_tag:
	case subptr_tag:
	case minptr_tag:
		if (error_treatment_is_trap ( *e )) {
			specialext = 1;
		}

		return likediv ( e, at ) ;

	case addptr_tag: {
		exp ptr_arg = child(*e);
		exp offset_arg = next(ptr_arg);
		int fralign = frame_al_of_ptr(sh(ptr_arg));

		if (fralign) {
			int offalign = frame_al1_of_offset(sh(offset_arg));
#if 0
			if (((offalign - 1)&offalign) != 0) {
				error(ERR_SERIOUS, "Mixed frame offsets not supported");
			}
#endif
			if (cees(offalign) && child(*e)->tag == current_env_tag) {
				setcallee_offset(child(*e));
			}

#if 0
			if (include_vcallees(fralign) && l_or_cees(offalign)) {
				exp newexp = getexp(sh(ptr_arg), offset_arg, 0, ptr_arg, NULL, 0, 0,
				                    locptr_tag);
				next(ptr_arg) = newexp;
				ptr_arg->last = true;
				child(*e) = newexp;
			}
#endif
		}

		return likediv(e, at);
	}

	case locptr_tag:
	case reff_tag:
	case float_tag:
	case offset_pad_tag:
	case chvar_tag: {
		exp *arg = &child ( *e ) ;
		exp *pste;
		needs nds ;

		if (error_treatment_is_trap ( *e )) {
			specialext = 1;
		}

		nds = shapeneeds ( sh ( *e ) );
		nds = maxneeds ( scan ( arg, at ), nds ) ;
		pste = ptr_position(ste);

		if ((has & HAS_LONG_DOUBLE)) {
			exp op = *pste ;

			if ( sh ( op ) -> tag == doublehd ) {
				nds.propneeds |= hasproccall ;
			}
		}

		return nds;
	}

	case cont_tag:
	case contvol_tag: {
		exp *arg = &child ( *e ) ;
		needs nds ;

		nds = maxneeds ( scan ( arg, at ), shapeneeds ( sh ( *e ) ) ) ;
		nds.fixneeds = MAX ( nds.fixneeds, 2 ) ;

		return nds;
	}

	case mult_tag:
mult_tag_case:
		if (error_treatment_is_trap ( *e )) {
			specialext = 1;
		}

		return multneeds ( e, at ) ;

	case offset_mult_tag:
	case offset_div_tag: {
		exp op1 = child(*e);
		exp op2 = next ( op1) ;
		shape s = sh ( op2 ) ;

		if ( op2->tag == val_tag && no ( op2 ) == 8 &&
		     s->tag == offsethd && al2 ( s ) >= 8 ) {
			/* offset is one byte */
			next ( op1 ) = next ( *e ) ;

			if ( ( *e ) -> last ) {
				op1 ->last = true ;
			} else {
				op1 ->last = false ;
			}

			sh(op1) = sh(*e);
			*e = op1 ;
			if ((*e)->tag == val_tag) {
				return shapeneeds ( sh ( *e ) ) ;    /* disps already in bytes */
			} else {
				return scan ( e, at ) ;
			}
		}

		if ( nstare == offset_mult_tag ) {
			goto mult_tag_case ;
		}

		FALL_THROUGH;
	}

	case div0_tag:
	case div1_tag:
	case div2_tag:
	case offset_div_by_int_tag:
		if (error_treatment_is_trap ( *e )) {
			specialext = 1;
		}

		return divneeds ( e, at ) ;

	case offset_add_tag:
	case offset_subtract_tag:
		if ((al2(sh(child(*e))) == 1) && (al2(sh(next(child(*e)))) != 1)) {
			make_bitfield_offset(next(child(*e)), child(*e), 0, sh(*e));
		}

		if ((al2(sh(child(*e))) != 1) && (al2(sh(next(child(*e)))) == 1)) {
			make_bitfield_offset(child(*e), *e, 1, sh(*e));
		}

		FALL_THROUGH;

	case component_tag:
		return likediv ( e, at ) ;

	case offset_max_tag:
	case max_tag:
	case min_tag: {
		needs nd;
		nd = likediv(e, at);
		nd.fixneeds = MAX(nd.fixneeds, 3);
		return nd;
	}

	case rem0_tag:
	case mod_tag:
	case rem2_tag:
		if (error_treatment_is_trap ( *e )) {
			specialext = 1;
		}

		return remneeds ( e, at ) ;

	case fdiv_tag:
	case fplus_tag:
	case fminus_tag:
	case fmult_tag: {
		exp op = *e ;
		exp a2 = next ( child ( op ) ) ;

		if (error_treatment_is_trap ( *e )) {
			specialext = 1;
		}

		if ( ! a2 -> last ) {
			/* + and * can have > 2 parameters - make them diadic
			   - can do better a + exp => let x = exp in a + x */
			exp opn = getexp ( sh ( op ), op, 0, a2, NULL,
			                   0, 0, op->tag ) ;
			/* don't need to transfer error treatment - nans */
			exp nd = getexp ( sh ( op ), next ( op ), ( int ) op -> last,
			                  opn, NULL, 0, 1, ident_tag ) ;
			exp id = getexp ( sh ( op ), op, 1, nd, NULL,
			                  0, 0, name_tag ) ;
			pt ( nd ) = id ;
			next ( child ( op ) ) = id ;
			op ->last = true ;
			next ( op ) = nd ;
			while ( ! a2 -> last ) {
				a2 = next ( a2 ) ;
			}
			next ( a2 ) = opn ;
			*e = nd ;

			return scan ( e, at ) ;
		}

		return fpop ( e, at ) ;
	}

	case fmax_tag:
		return fpop(e, at);

	case field_tag: {
		needs str ;
		exp *arg = &child ( *e ) ;

		if ( chase ( *e, arg ) ) {
			/* field has been distributed */
			exp stare = *e ;
			exp ss = child ( stare ) ;
			if ( ! stare -> last ) {
				ss ->last = false ;
			}
			next ( ss ) = next ( stare ) ;
			sh ( ss ) = sh ( stare ) ;
			*e = ss ;
			return scan ( e, at ) ;
		}

		str = scan ( arg, at ) ;
		return maxneeds ( str, shapeneeds ( sh ( *e ) ) ) ;
	}

	case general_proc_tag:
	case proc_tag: {
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
		nonevis = true ;
		specialext = proc_has_checkstack(*e);
		gen_call = (stare->tag == general_proc_tag);
		v_proc = proc_has_vcallees(*e);
		callee_size = 0;

		if (gencompat) {
			trad_proc = !proc_may_have_callees(stare);
		}

		/* scan the body of the proc */
		bexp = &child ( *e ) ;
		bat = bexp ;
		body = scan ( bexp, &bat ) ;

		if (specialext) {
			set_proc_uses_external ( *e ) ;
		}

		if ((gencompat && !trad_proc) || (!gencompat && gen_call)) {
			callee_size += 4 * PTR_SZ;
		}

		/* should never require this in reg in C */
		return body;
	}

	case alloca_tag: {
		needs nds ;

		if (checkalloc ( *e )) {
			specialext = 1;
		}

		nds = scan ( &child ( *e ), at ) ;
		if ( nds.fixneeds < 2 ) {
			nds.fixneeds = 2 ;
		}

		return nds;
	}

	case trap_tag:
		specialext = 1;
		return zeroneeds;

	case special_tag:
		return zeroneeds;

	case asm_tag: {
		needs nds;
		nds = zeroneeds;

		if (props(*e) != 0) {
			error(ERR_SERIOUS, "~asm not in ~asm_sequence");
		}

		check_asm_seq (child(*e), 0);
		/* clobber %o0..%o5,%o7 */
		nds.fixneeds = MAX ( nds.fixneeds, 8 ) ;
		nds.propneeds |= hasproccall ;

		return nds;
	}

	default:
		error(ERR_SERIOUS,  "Case not covered in needs scan" ) ;
		return zeroneeds;
	}

	UNREACHED;
}

