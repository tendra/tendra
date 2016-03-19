/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * Defines the scan through a program which reorganises it so
 * that all arguments of operations are suitable for later
 * code-production. The procedure scan evaluates the register
 * requirements of an exp. The exps are produced from the decoding
 * process and the various exp -> exp transformations in the proc
 * independent (common to other  translators)
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <shared/bool.h>
#include <shared/check.h>

#include <utility/max.h>

#include <local/szs_als.h>
#include <local/ash.h>
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

#include <flpt/flpt.h>

#include <main/flags.h>

#include <refactor/const.h>
#include <refactor/refactor.h>

#include "procrec.h"
#include "bitsmacs.h"
#include "regable.h"
#include "tempdecs.h"
#include "special.h"
#include "frames.h"
#include "regexps.h"
#include "reg_defs.h"
#include "oddtest.h"
#include "make_code.h"
#include "scan.h"
#include "localexpmacs.h"

int maxfix, maxfloat; /* the maximum number of t-regs */
static int stparam, fixparam, floatparam;
/* used by scan to set initial parameter positions */
static int numparams = 0;

extern alignment long_to_al(int);

extern long notbranch[6];

static bool nonevis     = true;
static int callerfortr;

needs scan(exp *, exp **);

/*
 * identifies integer varieties which require more work to manipulate
 * (because of a lack of appropriate instructions)
 */
#define is_awkward_variety(vname)((vname == scharhd || vname == ucharhd \
				  || vname == swordhd || vname == uwordhd))


/*
 * declaration of scan.
 *
 * needs is defined in procrectypes.h.
 * This is a structure which has two integers giving
 * the number of fixed and floating point registers required
 * to contain live values in the expression parameters. A
 * further field prop is used for various flags about certain
 * forms of exp (mainly idents and procs). The maxargs field
 * gives the maximum size in bits for the parameters of all the
 * procs called in the exp. The needs of a proc body are preserved
 * in the needs field of the procrec (see procrectypes.h).
*/

#if DO_NEW_DIVISION
#define is_machine_divide(e)(bro(son(e))->tag!= val_tag)
#else
#define is_machine_divide(e)1
#endif

/*
 * This procedure effectively inserts a new declaration into an exp.
 * This is used to stop a procedure requiring more than the
 * available number of registers.
 */
static void
cca(exp **to, exp *x)
{
	if ((**to)->tag == diagnose_tag) {
		*to = & son(**to);
	}

	if (x == *to) {
		/* replace by  Let tag = def In tag Ni */
		exp def = *x;
		exp id  = getexp(sh(def), bro(def), def->last, def, NULL, 0, 1, ident_tag);
		exp tag = getexp(sh(def), id, 1, id, NULL, 0, 0, name_tag);
		pt(id)   = tag; /* use of tag */
		bro(def) = tag; /* bro(def) is body of Let = tag */
		def->last = false;
		*x = id; /* replace pointer to x by Let */
	} else {
		/* replace by Let tag = def In ato/def = tag Ni */
		exp def = *x;
		exp ato = **to;
		exp id  = getexp(sh(ato), bro(ato), ato->last, def, NULL, 0, 1, ident_tag);
		exp tag = getexp(sh(def), bro(def), def->last, id, NULL, 0, 0, name_tag);

		pt(id) = tag; /* use of tag */
		bro(def) = ato; /* ato is body of Let */
		def->last = false;
		bro(ato) = id; /* its father is Let */
		ato->last = true;
		**to = id;  /* replace pointer to 'to' by Let */
		*x   = tag; /* replace use of x by tag */
		*to = & bro(def); /* later replacement to same 'to' will be at body of Let */
	}
}

static needs onefix    = { 1, 0, 0, 0 }; /* needs one fix pt reg */
static needs twofix    = { 2, 0, 0, 0 }; /* needs 2 fix pt regs */
static needs fourfix   = { 4, 0, 0, 0 };
static needs fivefix   = { 5, 0, 0, 0 };

static needs onefloat  = { 0, 1, 0, 0 }; /* needs 1 flt pt regs */
static needs zeroneeds = { 0, 0, 0, 0 }; /* has no needs */

/*
 * Calculate the number of registers required to move a data item of
 * shape s to/from memory. Worst case values.
 */
static needs
shapeneeds(shape s)
{
	ash as;

	if (is_floating(s->tag)) {
		return onefloat;
	}

	as = ashof(s);
	if (as.ashalign == 8 /* && s->tag == ptrhd */) {
		return fourfix;
	}

	/* If not aligned on 4 byte boundary */
	if (as.ashalign == 16) {
		return fivefix;
	}

	if (valregable(s)) {
		return onefix;
	} else {
		return twofix;
	}
}

static void
make_bitfield_offset(exp e, exp pe, int spe, shape sha)
{
	exp omul;
	exp val8;

	if (e->tag == val_tag) {
		no(e) *= 8;
		return;
	}

	omul = getexp(sha, bro(e), (int) e->last, e, NULL, 0, 0, offset_mult_tag);
	val8 = getexp(slongsh, omul, 1, NULL, NULL, 0, 8, val_tag);

	e->last = false;
	setbro(e, val8);
	if (spe) {
		son(pe) = omul;
	} else {
		bro(pe) = omul;
	}
}

/*
 * these are basically the expressions which cannot be accessed
 * by a simple load or store instruction
 */
static bool
complex(exp e)
{
	if (e->tag == name_tag ||
	    (e->tag == cont_tag && son(e)->tag == name_tag &&
	     isvar(son(son(e))))
	    || e->tag == val_tag || e->tag == real_tag || e->tag == null_tag)
	{
		return 0;
	}

	return 1;
}

static int
scan_cond(exp *e, exp outer_id)
{
	exp ste = *e;
	exp first  = son(ste);
	exp labst  = bro(first);
	exp second = bro(son(labst));

	assert(ste->tag == cond_tag);

	/*
	 * cond is { ... test(L); ? ; goto X | L:make_top}
	 * if ? empty can replace by seq { ... not-test(X); make_top }
	 */
	if (second->tag == top_tag && sh(first)->tag == bothd && no(son(labst)) == 1
	    && first->tag == seq_tag && bro(son(first))->tag == goto_tag)
	{
		exp l;

		for (l = son(son(first)); !l->last; l = bro(l))
			;

		while (l->tag == seq_tag) {
			l = bro(son(l));
		}

		if (l->tag == test_tag && pt(l) == labst) {
			settest_number(l, notbranch[test_number(l) - 1]);
			pt(l) = pt(bro(son(first)));
			bro(son(first)) = second;
			bro(second) = first;
			second->last = true;
			bro(first) = bro(ste);

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

	if (first->tag == seq_tag && second->tag == cond_tag
	    && no(son(labst)) == 1
	    && son(son(first))->tag == test_tag
	    && pt(son(son(first))) == labst
	    && son(second)->tag == seq_tag
	    && son(son(son(second)))->tag == test_tag)
	{
		/* cond is ( seq (test to L;....| L:cond(seq(test;...),...) )
		   ..... */
		exp test1 = son(son(first));
		exp test2 = son(son(son(second)));
		exp op11 = son(test1);
		exp op21 = bro(op11);
		exp op12 = son(test2);
		exp op22 = bro(op12);
		bool c1 = complex(op11);
		bool c2 = complex(op21);

		if (c1 && eq_exp(op11, op12)) {
			/* ....if first operands of tests are same, identify them */

			exp newid = getexp(sh(ste), bro(ste), ste->last, op11, NULL, 0, 2, ident_tag);
			exp tag1 = getexp(sh(op11), op21, 0, newid, NULL, 0, 0, name_tag);
			exp tag2 = getexp(sh(op12), op22, 0, newid, NULL, 0, 0, name_tag);

			pt(newid) = tag1;
			pt (tag1) = tag2;	/* uses of newid */
			bro (op11) = ste;
			op11->last = false;/* body of newid */
			/* forget son test2 = son test1 */
			bro(ste) = newid;
			ste->last = true;	/* father body = newid */
			son(test1) = tag1;
			son (test2) = tag2;	/* relace 1st operands of test */
			if (!complex(op21)) {
				/* if the second operand of 1st test is
				   simple, then identification could go
				   in a t-teg (!!!NB overloading of inlined flag!!!).... */
				setinlined(newid);
			}

			kill_exp(op12, op12);
			*(e) = newid;
			if (scan_cond(&bro(son(labst)), newid) == 2 && complex(op22)) {
				/* ... however a further use of identification means that
				   the second operand of the second test must also be simple */
				clearinlined(newid);
			}

			return 1;
		} else if (c2 && eq_exp(op21, op22)) {
			/* ....if second operands of tests are same, identify them */

			exp newid = getexp(sh(ste), bro(ste), ste->last, op21, NULL, 0, 2, ident_tag);
			exp tag1 = getexp(sh(op21), test1, 1, newid, NULL, 0, 0, name_tag);
			exp tag2 = getexp(sh(op22), test2, 1, newid, NULL, 0, 0, name_tag);

			pt(newid) = tag1;
			pt(tag1) = tag2;	/* uses of newid */
			bro(op21) = ste;
			op21->last = false;
			/* body of newid */
			/* forget bro son test2 = bro son test1 */
			bro(ste) = newid;
			ste->last = true;	/* father body = newid */
			bro(op11) = tag1;
			bro(op12) = tag2;

			if (!complex(op11)) {
				setinlined(newid);
			}

			kill_exp(op22, op22);
			/* relace 2nd operands of test */
			*e = newid;
			if (scan_cond(&bro(son(labst)), newid) == 2 && complex(op12)) {
				clearinlined(newid);
			}

			return 1;
		} else if (op12->tag != name_tag
		           && op11->tag == name_tag
		           && son(op11) == outer_id
		           && eq_exp(son(outer_id), op12))
		{
			/* 1st param of test1 is already identified with 1st param of  test2 */
			exp tag = getexp(sh(op12), op22, 0, outer_id, pt(outer_id), 0, 0, name_tag);
			pt(outer_id) = tag;
			no(outer_id) += 1;

			if (complex(op21)) {
				clearinlined(outer_id);
			}

			/* update usage of ident */
			son(test2) = tag;
			kill_exp(op12, op12);
			if (scan_cond(&bro(son(labst)), outer_id) == 2 && complex(op22)) {
				clearinlined(outer_id);
			}

			return 2;
		}
	}

	return 0;
}

/*
   does the scan on commutative and associative operations and
   may perform various transformations allowed by these properties
*/
static needs
likeplus(exp *e, exp **at)
{
	needs a1;
	needs a2;
	prop pc;
	exp *br = &son(*e);
	exp dad = *e;
	exp prev;
	bool commuted = 0;

#if 0
	if (optop(*e)) {
		assert(*br->tag != val_tag);
	}
#endif

	a1 = scan(br, at);

	/* scan the first operand - won't be a val_tag */
	do {
		exp *prevbr;
		prevbr = br;
		prev = *br;
		br = &bro(prev);
		a2 = scan(br, at);

		/* scan the next operand ... */
		if ((*br)->tag == val_tag) {
			continue;
		}

		a1.floatneeds = MAX(a1.floatneeds, a2.floatneeds);
		pc = a2.propsneeds & hasproccall;
		if (a2.fixneeds < maxfix && pc == 0) {
			/* ..its evaluation  will not disturb the accumulated result */
			a1.fixneeds   = MAX(a1.fixneeds, a2.fixneeds + 1);
			a1.propsneeds = a1.propsneeds | a2.propsneeds;
		} else if (a1.fixneeds < maxfix &&
				   (a1.propsneeds & hasproccall) == 0 && !commuted) {
			/* ..its evaluation will call a proc, so put it first */
			exp op1 = son(dad);
			exp cop = *br;
			bool lcop = cop->last;
			bro(prev) = bro(cop);
			if (lcop) {
				prev->last = true;
			}
			bro(cop) = op1;
			cop->last = false;
			son(dad) = cop;
			br = (prev == op1) ? &bro(cop) : prevbr;
			commuted = 1;

			a1.fixneeds    = MAX(a2.fixneeds, a1.fixneeds + 1);
			a1.propsneeds |= a2.propsneeds;
			a1.maxargs     = MAX(a1.maxargs, a2.maxargs);
		} else {
			/* ... its evaluation would disturb accumulated result,
			 * so replace it by a newly declared tag */
			cca(at, br);

			a1.fixneeds   = MAX(a1.fixneeds, 2);
			a1.propsneeds = a1.propsneeds | morefix | (pc << 1);
			a1.maxargs    = MAX(a1.maxargs, a2.maxargs);
		}
	} while (!(*br)->last);

	return a1;
}

/* scan non-commutative fix pt operation */
static needs
likediv(exp *e, exp **at)
{
	needs l;
	needs r;
	prop pc;
	exp *arg = &son(*e);
	l = scan(arg, at);

	/* scan 1st operand */
	arg = &bro(*arg);
	r = scan(arg, at);

	/* scan second operand ... */
	l.floatneeds = MAX(l.floatneeds, r.floatneeds);
	pc = r.propsneeds & hasproccall;
	if (r.fixneeds < maxfix && pc == 0) {
		/* ...it fits into registers */
		l.fixneeds   = MAX(l.fixneeds, r.fixneeds + 1);
		l.propsneeds = l.propsneeds | r.propsneeds;
	} else {
		/* ...it requires new declaration of second operand */
		cca(at, arg);
		l.fixneeds   = MAX(l.fixneeds, 1);
		l.propsneeds = l.propsneeds | morefix | (pc << 1);
		l.maxargs    = MAX(l.maxargs, r.maxargs);
	}

	return l;
}

/* scans diadic floating point operation  */
static needs
fpop(exp *e, exp **at)
{
	needs l;
	needs r;
	exp op = *(e);
	prop pcr, pcl;
	exp * arg = &son(op);
	bool withert = !(optop(*e));

	l = scan(arg, at);
	arg = &bro(*arg);
	r = scan(arg, at);
	l.fixneeds = MAX(l.fixneeds, r.fixneeds);
	pcr = r.propsneeds & hasproccall;
	pcl = l.propsneeds & hasproccall;

	if (r.floatneeds <= l.floatneeds && r.floatneeds < maxfloat && pcr == 0) {
		l.floatneeds = MAX(2, MAX(l.floatneeds, r.floatneeds + 1));
		l.propsneeds = l.propsneeds | r.propsneeds;
		ClearRev(op);
	} else if (pcl == 0 && l.floatneeds <= r.floatneeds && l.floatneeds < maxfloat) {
		l.floatneeds = MAX(2, MAX(r.floatneeds, l.floatneeds + 1));
		l.propsneeds = l.propsneeds | r.propsneeds;
		SetRev(op);
	} else if (r.floatneeds < maxfloat && pcr == 0) {
		l.floatneeds = MAX(2, MAX(l.floatneeds, r.floatneeds + 1));
		l.propsneeds = l.propsneeds | r.propsneeds;
		ClearRev(op);
	} else {
		cca(at, arg);
		ClearRev(op);
		l.floatneeds = MAX(l.floatneeds, 2);
		l.propsneeds = l.propsneeds | morefloat | (pcr << 1);
		l.maxargs = MAX(l.maxargs, r.maxargs);
	}

	if (withert && l.fixneeds < 2) {
		l.fixneeds = 2;
	}

	return l;
}

/*
 * Calculates a needs value. Each element of which is the
 * maximum of the corresponding elements in the two parameter needs
 */
static needs
maxneeds(needs a, needs b)
{
	needs an;

	an.fixneeds   = MAX(a.fixneeds,   b.fixneeds);
	an.floatneeds = MAX(a.floatneeds, b.floatneeds);
	an.maxargs    = MAX(a.maxargs,    b.maxargs);
	an.numparams  = MAX(a.numparams,  b.numparams);
	an.propsneeds = a.propsneeds | b.propsneeds;

	return an;
}

/*
 * calculates the needs of a tuple of expressions; any new
 * declarations required by a component expression will
 * replace the component expression
 */
static needs
maxtup(exp e, exp **at)
{
	exp *stat = &son(e);
	needs an;

	an = zeroneeds;
	if (son(e) == NULL) {
		return zeroneeds;
	}

	while (an = maxneeds(an, scan(stat, at)), !(*stat)->last) {
		stat = &bro(*stat);
	}

	return an;
}

/*
 * finds if usedname is only used in cont operation or as result
 * of ident i.e. value of name is unchanged over its scope
 */
static bool
unchanged(exp usedname, exp ident)
{
	exp uses;

	for (uses = pt(usedname); uses != NULL; uses = pt(uses)) {
		if (!intnl_to(ident, uses)) {
			continue;
		}

		if (!uses->last || bro(uses)->tag != cont_tag) {
			exp z;

			for (z = uses; z != ident; z = bro(z)) {
				if (!z->last || (bro(z)->tag != seq_tag && bro(z)->tag != ident_tag)) {
					return 0;
				}
			}
		}
	}

	return 1;
}

/*
 * check if e  is (let a = 0 in cond(inttest(L)=result; a=1 | L:top); a ni )
 * This will be compiled later using set instructions instead of branches
 */
static exp
absbool(exp id)
{
	if (isvar(id) && son(id)->tag == val_tag && no(son(id)) == 0
	    && no (id) == 2 /* name initially 0 only used twice */ )
	{
		exp bdy = bro(son(id));
		if (bdy->tag == seq_tag && bro(son(bdy))->tag == cont_tag &&
		    son(bro(son(bdy)))->tag == name_tag &&
		    son(son(bro(son(bdy)))) == id
		    /* one use is result  of sequence body */ )
		{
			exp c = son(son(bdy));
			if (c->last && c->tag == cond_tag /* seq is cond=c; id */ ) {
				exp first = son(c);
				exp second = bro(son(c));
				if (no (son(second)) == 1 /* only one jump to else */ &&
				    bro(son(second))->tag == top_tag
				    && first->tag == seq_tag /* cond is (seq= first | L: top) */ )
				{
					exp s = son(son(first));
					exp r = bro(son(first));
					if (r->tag == ass_tag && son(r)->tag == name_tag &&
					    son(son(r)) == id && bro(son(r))->tag == val_tag &&
					    no (bro (son (r))) == 1 /* last of seq is id = 1 */ &&
					    s->last && s->tag == test_tag && pt(s) == second
					    && !is_floating(sh(son(s))->tag))
					    /* *t of seq is int test jumping to second */
					{
						return s;
					}
				}
			}
		}
	}

	return 0;
}

exp *
ptr_position(exp e)
{
	exp sib;
	exp dad;

	dad = father(e);
	if (son(dad) == e) {
		return &son(dad);
	}

	for (sib = son(dad); bro(sib) != e; sib = bro(sib))
		;

	return &bro(sib);
}

/* distribute selection throughout compound expressions */
static bool
chase(exp sel, exp *e)
{
	bool b = 0;

	switch ((*e)->tag) {
	case ident_tag:
	case seq_tag:
	case rep_tag:
	case labst_tag:
		b = chase(sel, &bro(son(*e)));
		break;

	case solve_tag:
	case cond_tag: {
		exp *one;

		for (one = &son(*e); ; one = &bro(*one)) {
			b |= chase(sel, one);
			if ((*one)->last) {
				break;
			}
		}
		break;
	}

	case field_tag:
		if (chase(*e, &son(*e))) {
			/* inner field has been distributed */
			exp stare = *e;
			exp ss = son(stare);

			if (!stare->last) {
				ss->last = false;
			}

			bro(ss) = bro(stare);
			sh(ss) = sh(stare);
			*e = ss;

			return chase(sel, e);
		}

		/* ... continue to default */
		FALL_THROUGH;

	default:
		/* only change if not outer */
		if ((son(sel) != *e) && (sh(*e)->tag != bothd)) {
			exp stare = *e;
			exp newsel = getexp(sh(sel), bro(stare), stare->last, stare,
			                    NULL, props(sel), no(sel), sel->tag);
			*e =  newsel;
			bro(stare) = newsel;
			stare->last = true;
			b = 1;
		}
	}

	if (b) {
		sh(*e) = sh(sel);
	}

	return b;
}

/* check for C style varargs */
bool
vascan(exp *e)
{
	bool result = false;
	exp tr;
	int s2;

	for (tr = son(*e); (tr->tag == ident_tag) && (isparam(tr)) && (!result);
	     tr = bro(son(tr))) {
		s2 = shape_size(sh(son(tr)));
		result = (sh(son(tr))->tag == cpdhd) && last_param(tr) && (s2 == 0);
	}

	return result;
}

static bool gen_call;
static bool in_vcallers_proc;

/*
 * This procedure works out register requirements of an exp. At each
 * call the fix field of the needs is the number of fixpnt registers
 * required to contain live values to evaluate this expression.
 * This never exceeds maxfix because if it would have, a new
 * declaration is introduced in the exp tree (similarly for
 * floating regs and maxfloat). In these cases the prop field will
 * contain the bits morefix (or morefloat).
 *
 * As well as working out the register requirements scan performs
 * some transformations on the procedure.  It also determines whether
 * or not the procedure uses varargs, if it contains a division by a
 * non-constant, and if it may need to move values between float and
 * fixed point registers.
 *
 * If the procedure does contain a division by a non constant then
 * those registers which are corrupted by the division instruction
 * are not made available to the register allocator for the duration
 * of that procedure (see settempregs()).  A better, though more
 * complicated, solution would be to disallow the use of these
 * registers in evaluating the LHS of operations in which the RHS
 * contains a division.
 */
needs
scan(exp *e, exp **at)
{
	static int has_old_varargs;
	static int has_div;
	static int has_float;
	exp   ste = *(e);
	int   nstare = ste->tag;

	/*
	 * e is the expression to be scanned, at is the place to put any new decs.
	 * NB order of recursive calls with same at is critical
	 */

	switch (nstare) {
	case 0:
		return zeroneeds;

	case compound_tag:
	case nof_tag:
	case concatnof_tag:
	case ncopies_tag: {
		needs nl;
		bool cantdo;
		exp dad;

		if (ste->tag == ncopies_tag && son(ste)->tag != name_tag
		    && son(ste)->tag != val_tag) {
			nl = scan(&son(*e), at);
			cca(at, &son(*e));
		} else {
			nl = maxtup(*(e), at);
		}

		dad = father(ste);
		if (dad->tag == compound_tag || dad->tag == nof_tag
		    || dad->tag == concatnof_tag) {
			cantdo = 0;
		} else if (ste->last) {
			if (bro(ste)->tag == ass_tag) {
				exp a = son(bro(ste));
				cantdo = (a->tag != name_tag || !isvar(son(a)));
			} else {
				cantdo = 1;
			}
		} else if (bro(ste)->last) {
			cantdo = (bro(bro(ste))->tag != ident_tag);
		} else {
			cantdo = 1;
		}

		/* can only deal with tuples in simple assignment or identity */
		if (cantdo) {
			int prps = (nl.propsneeds & hasproccall) << 1;
			cca(at, ptr_position(ste));
			nl = shapeneeds(sh(*(e)));
			nl.propsneeds |= morefix;
			nl.propsneeds |= prps;
		}

		if (nl.fixneeds < 2) {
			nl.fixneeds = 2;
		}

		return nl;
	}

	case cond_tag: {
		exp t, f, v;

		if (oddtest(ste, & t, &f, &v)) {
			/* transform to f((absbool(t) <<1)-1)  */
			exp bc = bro(ste);
			bool lc = ste->last;
			exp ab = getexp(sh(v), NULL, 0, t, NULL, 0, 0, absbool_tag);
			exp shl = getexp(sh(v), NULL, 0, ab, NULL, 0, 0, shl_tag);
			exp v1 = getexp(sh(v), shl, 1, NULL, NULL, 0, 1, val_tag);
			exp p = getexp(sh(v), NULL, 1, shl, NULL, 0, 0, plus_tag);
			exp vm1 = getexp(sh(v), p, 1, NULL, NULL, 0, -1, val_tag);
			bro(ab) = v1;
			bro(shl) = vm1;
			bro(t) = ab;
			t->last = true;

			if (no(v) == -1) {
				settest_number(t, notbranch[test_number(t) - 1]);
			}

			if (f == v) {
				*e = p;
			} else {
				son(bro(v)) = p;
				bro(p) = bro(v);
				*e = f;
			}

			bro(*e) = bc;
			if (lc) {
				(*e)->last = true;
			} else {
				(*e)->last = false;
			}

			return scan(e, at);
		}

		/*
			if (is_maxlike(ste, &t) ) {
			son(ste) = t;
			bro(t) = ste; t->last = true;
			ste->tag = maxlike_tag;
			return scan(&son(ste), at);
			}
			if (is_minlike(ste, &t) ) {
			son(ste) = t;
			bro(t) = ste; t->last = true;
			ste->tag = minlike_tag;
			return scan(&son(ste), at);
			}
		*/

		if (is_abslike(ste, &t)) {
			son(ste) = t;
			bro(t) = ste;
			t->last = true;
			ste->tag = abslike_tag;
			return scan(&son(ste), at);
		}

		if (is_fabs(ste, &t)) {
			son(ste) = son(t);
			bro(son(t)) = ste;
			son(t)->last = true;
			ste->tag = fabs_tag;
			return scan(&son(ste), at);
		}

		if (scan_cond(e, NULL) != 0) {
			return scan(e, at);
		} /* else goto next case */
	}

		FALL_THROUGH;

	case labst_tag:
	case rep_tag:
	case solve_tag: {
		exp * stat;
		exp * statat;
		needs an;
		stat = &son(*e);
		statat = stat;

		an = zeroneeds;
		while (an = maxneeds(an, scan(stat, &statat)), !(*stat)->last) {
			stat = &bro(*stat);
			statat = stat;
		}

		if ((an.propsneeds & usesproccall) != 0) {
			an.propsneeds |= hasproccall;
		}

		return an;
	}

	case ident_tag: {
		needs bdy;
		needs def;
		exp stare = *e;
		exp *arg = &bro(son(stare)); /* ptr to body */
		exp t = pt(stare);
		exp s;
		bool fxregble;
		bool flregble;
		bool old_nonevis = nonevis;
		exp ab;

		/* bdy.numparams=0; */
#if 1
		if (!iscaonly(stare)) {
			setvis(stare);
		}

		if (son(stare)->tag == formal_callee_tag) {
			setvis(stare);
		}
#endif

		if (isparam(stare) && son(stare)->tag != formal_callee_tag) {
			exp def = son(stare);
			shape shdef = sh(def);
			long n = rounder(stparam, shape_align(shdef));
			long sizep = shape_size(shdef);
			numparams = MIN(numparams + rounder(sizep, REG_SIZE), 6 * REG_SIZE);
			/*numparams=MIN(numparams+MAX(REG_SIZE,sizep),6*REG_SIZE);*/
			/*assert(def->tag==clear_tag); */

			if (is_floating(shdef->tag)) {
				if (sizep <= 64 && stparam <= 320) {
					props(def) = floatparam;
					maxfloat--;
				}
			} else if (sizep <= 64  && stparam <= 320  ) { /*change for 64 bit regs*/
				props(def) = fixparam;
				maxfix--;
			} else if (stparam <= 320) {
				props(def) = fixparam;
			} else {
				props(def) = 0;
			}

			stparam    = rounder(n + sizep, 64); /* calculate the offset */
			fixparam   = 16 + (stparam >> 6); /* >> 6, was >>5 */
			floatparam = 16 + (stparam >> 6);
			if (((isvis(stare) && props(son(stare)) != 0 && (sh(son(stare))->tag == cpdhd))
				|| in_vcallers_proc) && last_param(stare))
			{
				/*
				 * must allow space for all parameter registers
				 * for * varargs function
				 */
				numparams = 12 * REG_SIZE;
			}

			no(def) = n;
			/* if varargs then save all param regs to stack */

			if (!is_floating(shdef->tag) && !valregable(shdef)) {
				setvis(stare);
			}

			/* now props(def) = pos parreg and no(def) = par stack address */
		} else if (isparam(stare) && son(stare)->tag == formal_callee_tag) {
			exp def = son(stare);
			shape shdef = sh(def);
			long sizep = shape_size(shdef);
			long alp = shape_align(shdef);
			long n = rounder(callee_size, alp);
			no(def) = n;
			callee_size = rounder(n + sizep, REG_SIZE);
		}

		if (gen_call) {
			numparams = MAX(6 * REG_SIZE, numparams);
		}

		nonevis &= !isvis(stare);
		bdy = scan(arg, &arg);
		/* scan the body-scope */
		arg = &son(stare);
		def = scan(arg, &arg);
		bdy.numparams = numparams;
		/* scan the initialisation of tag */

		nonevis = old_nonevis;
		t = son(stare);
		s = bro(t);
		fxregble = fixregable(stare);
		flregble = floatregable(stare);

		if (isparam(stare)) {
			if (son(stare)->tag != formal_callee_tag && !isvis(stare) &&
			    !isoutpar(stare) && (bdy.propsneeds & anyproccall) == 0) {
				/* leave pars in par regs or put in t-regs
				 * !! WHAT ABOUT TEMP DECS !!
				 */
				int x = props(son(stare));
				if (x != 0) {
					no(stare) = x;
					if (flregble) {
						props(stare) |= infreg_bits;
					} else {
						props(stare) |= inreg_bits;
					}
				} else if (fxregble && bdy.fixneeds < maxfix &&
				           (bdy.propsneeds & morefix) == 0)
				{
					no(stare) = NO_REG;
					props(stare) |= inreg_bits;
					bdy.fixneeds += 1;
				} else if (flregble &&
				           bdy.floatneeds < maxfloat &&
				           (bdy.propsneeds & morefloat) == 0)
				{
					no(stare) = NO_REG;
					props(stare) |= infreg_bits;
					bdy.floatneeds += 1;
				} else {
					no(stare) = 100;
				}
			} else {
				no(stare) = 100;
			}
		} else {
			if ((ab = absbool(stare)) != NULL) {
				/* form is (let a = 0 in cond(test(L)=ab;
				 * a=1 | L:top) ni replace declaration by
				 * ABS */
				bro(ab) = stare;
				ab->last = true; /* father => *e */
				son(stare) = ab;
				pt(stare) = NULL;
				pt(ab) = NULL;
				stare->tag = absbool_tag;
				return maxneeds(bdy, def);
			}

			if (!isvis(*e) && !isparam(*e) &&
			    (bdy.propsneeds & (anyproccall | uses2_bit)) == 0
			    && (fxregble || flregble) &&
			    (t->tag == apply_tag || t->tag == apply_general_tag ||
			     (s->tag == seq_tag && bro(son(s))->tag == res_tag &&
			      son(bro(son(s)))->tag == cont_tag && isvar(stare) &&
			      son(son(bro(son(s))))->tag == name_tag &&
			      son(son(son(bro(son(s))))) == stare)))
			{
                /* Let a := ..; return cont a */
				/* put tag in result reg if definition is
					   call of proc, or body ends with return
					   tag, provided result is not used other
					   wise */
				props(stare) |= (fxregble) ? inreg_bits : infreg_bits;
				bdy.propsneeds |= uses2_bit;
				no (stare) = 101;   /* identification  uses result reg in body
		       */
			} else if (!isvar(*e) && !isparam(*e) &&
			           ((t->tag == reff_tag && son(t)->tag == cont_tag &&
			             son(son(t))->tag == name_tag && isvar(son(son(son(t))))
			             && !isvis(son(son(son(t)))) &&
			             !isglob(son(son(son(t))))
			             && unchanged(son(son(son(t))), stare)
			             /* reff cont variable-not assigned to in
			                scope */
			            ) ||
			            (t->tag == cont_tag && son(t)->tag == name_tag &&
			             isvar(son(son(t))) && !isvis(son(son(t))) &&
			             !isglob(son(son(t))) && unchanged(son(son(t)), stare))))
			{
				/* cont variable - not assigned to in scope */
				props(stare) |= defer_bit;
				/* dont take space for this dec */
			} else if (!isvar(stare) && !isvis(stare) &&
			           ((props (stare) & 0x10 /* forced in const */ ) == 0)
			           && (t->tag == name_tag || t->tag == val_tag)) {
				props(stare) |= defer_bit;
				/* dont take space for this dec */
			} else if (fxregble && ( /*isinlined(stare)||*/
			               (bdy.fixneeds < maxfix &&
			                (bdy.propsneeds & morefix) == 0 &&
			                ((bdy.propsneeds & anyproccall) == 0 ||
			                 tempdec(stare, ((bdy.propsneeds & morefix) == 0 &&
			                                 bdy.fixneeds < maxfix - 2)))))) {
				/* put this tag in some  fixpt t-reg -
				   which will be decided  in make_code */
				props(stare) |= inreg_bits;
				no (stare) = NO_REG;	/* aha! */
				bdy.fixneeds += 1;
			} else if (bdy.floatneeds < maxfloat &&
			           (bdy.propsneeds & morefloat) == 0 && flregble &&
			           ((bdy.propsneeds & anyproccall) == 0
			            || tempdec(stare, ((bdy.propsneeds & morefloat) == 0 &&
			                               bdy.floatneeds < maxfloat - 2/*6*/)))) {
				/* put this tag in some  float t-reg -
				   which will be decided  in make_code */
				props(stare) |= infreg_bits;
				no(stare) = NO_REG;
				bdy.floatneeds += 1;
			} else {
#if 1
				if (fxregble && ((bdy.propsneeds & anyproccall) == 0) &&
				    (bdy.fixneeds < maxfix)) {
					SetPossParReg(stare);	/* +1 to fixneeds ? */
					bdy.fixneeds += 1;
				}
#endif
				no(stare) = 100;
				/* allocate either on stack or saved reg */
			}
		}

		bdy = maxneeds(bdy, def);
		if ((bdy.propsneeds & usesproccall) != 0) {
			bdy.propsneeds |= hasproccall;
		}

		return bdy;
	}

	case seq_tag: {
		exp *arg = &bro(son(*e));
		exp *stat;
		needs an;

		an = scan(arg, &arg);
		stat = &son(son(*e));

		arg = stat;
		for (;;) {
			needs stneeds;
			stneeds = scan(stat, &arg);
			/* initial statements voided */
			an = maxneeds(an, stneeds);
			if ((*stat)->last) {
				if ((an.propsneeds & usesproccall) != 0) {
					an.propsneeds |= hasproccall;
				}
				return an;
			}

			stat = &bro(*stat);
			arg = stat;
		}

	}

	case goto_tag:
		return zeroneeds;

	case ass_tag:
	case assvol_tag: {
		exp *lhs = &son(*e);
		exp *rhs = &bro(*lhs);
		needs nr;
		ash a;

		/* scan source */
		nr = scan(rhs, at);

		a = ashof(sh(*(rhs)));
		if (nstare != ass_tag || a.ashsize != a.ashalign || a.ashalign == 1) {
			/* complicated move */
			nr.propsneeds |= uses2_bit;
		}

		if ((*lhs)->tag == name_tag &&
		    (isvar(son(*(lhs))) ||
		     ((nr.propsneeds & (hasproccall | morefix)) == 0
		      && nr.fixneeds < maxfix)))
		{
			/* simple destination */
			return nr;
		} else {
			needs nl;

			prop prps = (nr.propsneeds & hasproccall) << 1;

			/* scan destination */
			nl = scan(lhs, at);
			nr.fixneeds += 1;

			if ((*rhs)->tag == apply_tag && (*rhs)->tag == apply_general_tag &&
			    nstare == ass_tag && (nl.propsneeds &
			                          (uses2_bit | anyproccall)) == 0) {
				/* source is proc call, so assign result reg directly */
				;
			} else if (nr.fixneeds >= maxfix || prps != 0) {
				/* source and destination regs overlap, so identify source */
				cca(at, rhs);
				nl = shapeneeds(sh(*(rhs)));
				nl.propsneeds |= morefix;
				nl.propsneeds &= ~(prps >> 1);
				nl.propsneeds |= prps;
			}

			return maxneeds(nl, nr);
		}
	}

	case untidy_return_tag:
	case res_tag: {
		ash a;
		needs x;
		shape s;
		exp *arg = &son(*e);
		exp r, ss, t;
		s = sh(*(arg));
		a = ashof(s);

		/* clear possibility of tlrecirsion; may be set later */
		props(*e) = 0;

		x = scan(arg, at);
		/* scan result exp ... */
		if (is_floating(s->tag)) {
			/* ... floating pt result */
			x.propsneeds |= realresult_bit;
			if (s->tag != shrealhd) {
				x.propsneeds |= longrealresult_bit;
			}
		} else {
			if (!valregable(s)) {
				/* .... result does not fit into reg */
				x.propsneeds |= long_result_bit;
			}
		}

		if (a.ashsize != 0) {
			/* ...not a void result */
			x.propsneeds |= has_result_bit;
		}

		if (((*e)->tag == res_tag) &&
		    (x.propsneeds & (long_result_bit | anyproccall | uses2_bit)) == 0) {
			r = son(*(e));
			if (r->tag == ident_tag && isvar(r) &&
			    (ss = bro(son(r)))->tag == seq_tag &&
			    (t = bro(son(ss)))->tag == cont_tag &&
			    son(t)->tag == name_tag && son(son(t)) == r)
			{
				/* result is tag allocated into result reg
				   - see ident_tag: */
				if ((props(r) & inreg_bits) != 0) {
					x.fixneeds--;
				} else if ((props(r) & infreg_bits) != 0) {
					x.floatneeds--;
				} else {
					props(r) |= is_floating(s->tag) ? infreg_bits : inreg_bits;
				}

				x.propsneeds |= uses2_bit;
				no (r) = 101;	/* identification  uses result reg in body */
			}
		}

		return x;
	}

	case apply_general_tag: {
		exp application = *(e);
		exp *fn = &son(application);
		exp callers = bro(*fn);
		exp *cerl = &son(callers);
		int stpar = 0;
		needs nds, pstldnds;
		int i;
		gen_call = true;
		nds = scan(fn, at);

		/* Identify it */
		if (nds.propsneeds & hasproccall) {
			cca(at, fn);
			nds.propsneeds &= ~hasproccall;
			nds.propsneeds |= usesproccall;
			fn = &son(application);
		}

		for (i = 0; i < no(callers); i++) {
			needs onepar;
			shape shonepar = sh(*cerl);
			exp * par = ((*cerl)->tag == caller_tag) ? &son(*cerl) : cerl;
			int n = rounder(stpar, shape_align(shonepar));
			onepar = scan(par, at);

			if (((i != 0) && (onepar.propsneeds & hasproccall)) ||
			    (onepar.fixneeds + (stpar >> 6) > maxfix)) {
				/* not the first parameter, and calls a proc */
				cca(at, par);
				nds.propsneeds |= usesproccall;
				nds = maxneeds(shapeneeds(sh(*(par))), nds);
				nds.maxargs = MAX(nds.maxargs, onepar.maxargs);
			} else {
				nds = maxneeds(onepar, nds);
			}

			if ((*cerl)->tag == caller_tag) {
				no(*cerl) = n;
			}

			n += shape_size(shonepar);
			stpar = rounder(n, REG_SIZE);
			cerl = &bro(*cerl);
		}

		nds.maxargs = MAX(nds.maxargs, stpar);
		nds = maxneeds(scan(&bro(bro(son(application))), at), nds);
		pstldnds = scan(&bro(bro(bro(son(application)))), at);

		if (pstldnds.propsneeds & (anyproccall | uses2_bit)) {
			props(*e) = 1;
			if (valregable(sh(application)) || floatregable(sh(application))) {
				cca(at, ptr_position(application));
				pstldnds.propsneeds |= usesproccall;
			}
		} else {
			props(*e) = 0;
		}

		nds = maxneeds(nds, pstldnds);
		nds.propsneeds |= hasproccall;

		return nds;
	}

	case make_callee_list_tag: {
		exp cllees = *e;
		exp *par = &son(cllees);
		needs nds;
		int stpar = 0, i;
		nds = zeroneeds;

		for (i = 0; i < no(cllees); ++i) {
			needs onepar;
			shape shonepar = sh(*par);
			int n = rounder(stpar, shape_align(shonepar));
			onepar = scan(par, at);

			/* identify it */
			if ((onepar.propsneeds & hasproccall) || (onepar.fixneeds + 1 > maxfix)) {
				cca(at, par);
				nds.propsneeds |= usesproccall;
				nds = maxneeds(shapeneeds(sh(*par)), nds);
				nds.maxargs = MAX(nds.maxargs, onepar.maxargs);
			} else {
				nds = maxneeds(onepar, nds);
			}

			n += shape_size(shonepar);
			stpar = rounder(n, REG_SIZE);
			par = &bro(*par);
		}

		no(cllees) = stpar;
		return nds;
	}

	case make_dynamic_callee_tag: {
		exp callees = *e;
		exp *ptr = &son(callees);
		needs ndsp, nds;
		nds = zeroneeds;
		ndsp = scan(ptr, at);

		if ((ndsp.propsneeds & hasproccall) || (ndsp.fixneeds + 1 > maxfix)) {
			cca(at, ptr);
			nds.propsneeds |= usesproccall;
			nds = maxneeds(shapeneeds(sh(*ptr)), nds);
			nds.maxargs = MAX(nds.maxargs, ndsp.maxargs);
		} else {
			nds = ndsp;
		}

		ndsp = scan(&bro(son(*e)), at);
		if ((ndsp.propsneeds & hasproccall) || (ndsp.fixneeds + 2 > maxfix)) {
			cca(at, &bro(son(callees)));
			nds.propsneeds |= usesproccall;
			nds = maxneeds(shapeneeds(sh(bro(son(*e)))), nds);
			nds.maxargs = MAX(nds.maxargs, ndsp.maxargs);
		} else {
			nds = maxneeds(ndsp, nds);
		}

		if(nds.fixneeds < 5) {
			nds.fixneeds = 5;    /* ?? */
		}

		return nds;
	}

	case same_callees_tag: {
		needs nds;
		nds = zeroneeds;
		nds.fixneeds = 4;		/* ?? */
		return nds;
	}

	case tail_call_tag: {
		needs ndsp, nds;
		exp *fn = &son(*e);
		ndsp = scan(fn, at);

		if ((ndsp.propsneeds & hasproccall) || (ndsp.fixneeds + 1 > maxfix)) {
			cca(at, fn);
			nds.propsneeds |= usesproccall;
			nds = maxneeds(shapeneeds(sh(*fn)), nds);
			nds.maxargs = MAX(nds.maxargs, ndsp.maxargs);
		} else {
			nds = ndsp;
		}

		gen_call = true;
		ndsp = scan(&bro(son(*e)), at);
		nds = maxneeds(nds, ndsp);
		return nds;
	}

	case apply_tag: {
		exp application = *(e);
		exp fn = son(application);
		exp *par    = &bro(fn);
		exp *fnexp  = &son(*e);
		int parsize = 0;
		needs nds;
		bool tlrecpos = nonevis && callerfortr;
		int i;

		nds = scan(fnexp, at);

		/* scan the function exp ... */
		if ((nds.propsneeds & hasproccall) != 0) {
			/* .... it must be identified */
			cca(at, fnexp);
			nds.propsneeds &= ~hasproccall;
			nds.propsneeds |= usesproccall;
			fn = son(application);
			par = &bro(fn);
		}

		if (fn->tag != name_tag ||
		    (son(son(fn)) != NULL && son(son(fn))->tag != proc_tag)) {
			tlrecpos = 0;
		}

		for (i = 1; !fn->last; ++i) {	/* scan parameters in turn ... */
			needs onepar;
			shape shpar = sh(*par);
			onepar = scan(par, at);

			if ((i != 1 && (onepar.propsneeds & hasproccall) != 0) ||
			    onepar.fixneeds + (parsize >> 6) > maxfix) {
				/* if it isn't the first parameter, and it
				   calls a proc, identify it */
				cca(at, par);
				nds.propsneeds |= usesproccall;
				nds = maxneeds(shapeneeds(sh(*(par))), nds);
				nds.maxargs = MAX(nds.maxargs, onepar.maxargs);
			} else {
				nds = maxneeds(onepar, nds);
			}

			parsize = rounder(parsize, shape_align(shpar));
			parsize = rounder(parsize + shape_size(shpar), REG_SIZE);

			/* ? */
			if ((!valregable(shpar) && !is_floating(shpar->tag)) || parsize > 384) {
				tlrecpos = 0;
			}

			if ((*par)->last) {
				break;
			}
			par = &bro(*par);
		}

		if ((i = specialfn(fn)) > 0) {
			nds = maxneeds(specialneeds(i), nds);
			return nds;
		}

		if (tlrecpos) {
			exp dad = father(application);
			if (dad->tag == res_tag) {
				props(dad) = 1; /* do a tl recursion*/
			}
		}

		nds.propsneeds |= hasproccall;
		nds.maxargs = MAX(nds.maxargs, parsize);

		return nds;
	}

	case name_tag:
		if (is_vararg(*e)) {
			/* if the tag represents va_list (set in spec_toks.c) */
			has_old_varargs = 1;
		}

		return shapeneeds(sh(*(e)));

	case val_tag: {
		exp s = sh(*e);

		if (s->tag == offsethd && al2(s) >= 8) {
			/* express disps in bytes */
			no(*e) = no(*e) >> 3;
		}

		/*... and continue */
	}

		FALL_THROUGH;

	case env_size_tag:
	case give_stack_limit_tag:
	case null_tag:
	case real_tag:
	case string_tag:
	case env_offset_tag:
	case general_env_offset_tag:
	case caller_name_tag:
	/* case next_frame_tag: */
	case current_env_tag:
	case make_lv_tag:
	case last_local_tag:
		return shapeneeds(sh(*(e)));

	case clear_tag:
	case formal_callee_tag:
	case top_tag:
	case prof_tag:
	case local_free_all_tag:
		return zeroneeds;

	case set_stack_limit_tag:
#ifdef return_to_label_tag
	case return_to_label_tag:
#endif
	case diagnose_tag:
	case neg_tag:
	case case_tag:
	case not_tag:
	case offset_negate_tag:
	case absbool_tag:
	case goto_lv_tag:
	case abs_tag:
	case local_free_tag: {
		exp *arg = &son(*e);
		return scan(arg, at);
	}

	case fneg_tag:
	case fabs_tag:
	case chfl_tag: {
		needs nds;

		nds = scan(&son(*e), at);
		if (!optop(*e) && nds.fixneeds < 2) {
			nds.fixneeds = 2;
		}

		return nds;
	}

	case alloca_tag: {
		needs nds;

		nds = scan(&son(*e), at);
		if (nds.fixneeds < 2) {
			nds.fixneeds = 2;
		}

		return nds;
	}

	case bitf_to_int_tag: {
		/* is bitfield signed or unsigned ?? */
		exp * arg = &son(*e);
		needs nds;
		exp stararg;
		exp stare;
		int sizeb;

		nds = scan(arg, at);
		stararg = *(arg);
		stare = *(e);
		sizeb = ashof(sh(stararg)).ashsize;

		if ((stararg->tag == name_tag &&
		     ((sizeb == 8 && (no(stararg) & 7) == 0)
		      || (sizeb == 16 && (no(stararg) & 15) == 0)
		      || (sizeb == 32 && (no(stararg) & 31) == 0)
		      || (sizeb == 64 && (no(stararg) & 63) == 0))
		    ) || (stararg->tag == cont_tag &&
		          ((son(stararg)->tag != name_tag &&
		            son(stararg)->tag != reff_tag)
		           || (sizeb == 8 && (no(son(stararg)) & 7) == 0)
		           || (sizeb == 16 && (no(son(stararg)) & 15) == 0)
		           || (sizeb == 32 && (no(son(stararg)) & 31) == 0)
		           || (sizeb == 64 && (no(son(stararg)) & 63) == 0))))
		{
			bool sgned = sh(stare)->tag & 1;
			shape ns = (sizeb == 8) ? ((sgned) ? scharsh : ucharsh)
			           : (sizeb == 16) ? ((sgned) ? swordsh : uwordsh)
			           : sh(stare);
			/*  can use short loads instead of bits extractions*/
			if (stararg->tag == cont_tag) {
				/* make the ptr shape consistent */
				sh(son(stararg)) = f_pointer(long_to_al(shape_align(ns)));
			}

			sh(stararg) = ns;
			stare->tag = chvar_tag;
		}

		return nds;
	}

	case int_to_bitf_tag: {
		exp *arg = &son(*e);
		return scan(arg, at);
	}

	case round_tag: {
		needs s;
		exp *arg = &son(*e);

		s = scan(arg, at);
		s.fixneeds = MAX(s.fixneeds, 2);
		s.floatneeds = MAX(s.floatneeds, 2);
		has_float = 1;

		return s;
	}

	case shl_tag:
	case shr_tag:
	case long_jump_tag: {
		exp *lhs = &son(*e);
		exp *rhs  = & bro(*lhs);
		needs nr;
		needs nl;
		prop prps;
		nr = scan(rhs, at);
		nl = scan(lhs, at);
		rhs = &bro(*lhs);
		prps = (nr.propsneeds & hasproccall) << 1;

		if (nr.fixneeds >= maxfix || prps != 0) {
			/* if reg requirements overlap, identify second operand */
			cca(at, rhs);
			nl = shapeneeds(sh(*(rhs)));
			nl.propsneeds |= morefix;
			nl.propsneeds &= ~(prps >> 1);
			nl.propsneeds |= prps;
		}

		nr.fixneeds += 1;
		return maxneeds(nl, nr);
	}

	case test_tag: {
		exp stare = *e;
		exp l = son(stare);
		exp r = bro(l);
		exp dad = father(stare);
		bool xlike = (dad->tag == maxlike_tag || dad->tag == minlike_tag
			|| dad->tag == abslike_tag);
		/* don't do various optimisations if xlike */

		if (!stare->last && bro(stare)->tag == test_tag &&
		    no(stare) == no(bro(stare)) &&
		    props(stare) == props(bro(stare)) &&
		    eq_exp(l, son(bro(stare))) && eq_exp(r, bro(son(bro(stare)))))
		{
			/* same test following in seq list - remove second test */
			if (bro(stare)->last) {
				stare->last = true;
			}

			bro(stare) = bro(bro(stare));
		}

		if (stare->last && bro(stare)->tag == 0 /* seq holder */
		    && bro(bro(stare))->tag == test_tag &&
		    bro(bro(bro(stare)))->tag == seq_tag &&
		    no(stare) == no(bro(bro(stare))) &&
		    props(stare) == props(bro(bro(stare))) &&
		    eq_exp(l, son(bro(bro(stare))))
		    && eq_exp(r, bro(son(bro(bro(stare))))))
		{
			/* same test following in seq res - void second test */
			bro(bro(stare))->tag = top_tag;
			son(bro(bro(stare))) = NULL;
			pt(bro(bro(stare))) = NULL;
		}

		if (!xlike && l->tag == val_tag && (props(stare) == 5 || props(stare) == 6)) {
			/* commute  const = x */
			bro(l) = stare;
			l->last = true;
			bro(r) = l;
			r->last = false;
			son(stare) = r;
			r = l;
			l = son(stare);
		}

		if (!xlike && r->tag == val_tag && (props(stare) == 5
		                                     || props(stare) == 6) && no(r) == 0 &&
		    l->tag == and_tag && bro(son(l))->tag == val_tag &&
		    (no(bro(son(l))) & (no(bro(son(l))) - 1)) == 0)
		{
			/* zero test  x & 2^n   -> neg test (x shl (31-n)) */
			exp copy;
			INT64  n = isbigval(bro(son(l))) ? exp_to_INT64((bro(son(l)))) :
			           make_INT64(0, no(bro(son(l))));
			int   x;
			for (x = 0; INT64_lt(zero_int64, n); ++x) {
				/*      for (x = 0; n > 0; x++) {*/
				n = INT64_shift_left(n, 1, 1);
				/*n = n << 1;*/
			}

			if (x == 0) { /* no shift required */
				bro (son (l)) = r;	/* zero there */
				son (stare) = son (l);/* x */
			} else {
				l->tag = shl_tag;
				no(bro(son(l))) = x;
			}

			props (stare) -= 3;	/* test for neg */
			if (!is64(sh(son(stare))) && l->tag != shl_tag) {
				sh(son(stare)) = slongsh;
				copy = getexp(s64sh, bro(son(stare)), 0, son(stare), NULL, 0, 0,
				              chvar_tag);
				son(stare) = copy;
			} else {
				sh(son(stare)) = s64sh;
			}
		}

		if (l->tag == bitf_to_int_tag && r->tag == val_tag &&
		    (props(stare) == 5 || props(stare) == 6) &&
		    (son(l)->tag == cont_tag || son(l)->tag == name_tag))
		{
			/* equality of bits against +ve consts doesnt need sign adjustment */
			long  n = no(r);

			switch (sh(l)->tag) {
			case scharhd:
				if (n >= 0 && n <= 127) {
					sh(l) = ucharsh;
				}
				break;

			case swordhd:
				if (n >= 0 && n <= 0xffff) {
					sh(l) = uwordsh;
				}
				break;

			default:
				;
			}
		} else if (is_floating(sh(l)->tag)) {
			return fpop(e, at);
		} else if (!xlike && r->tag == val_tag && no(r) == 1 && !isbigval(r)
		           && (props(stare) == 3 || props(stare) == 2))
		{
			no(r) = 0;
			if (props(stare) == 3) {
				props (stare) = 4;/* branch >=1 -> branch > 0 */
			} else	 {
				props (stare) = 1;/* branch <1 -> branch <= 0 */
			}
		}

		return likediv(e, at);
	}

	case plus_tag: {
		/* replace any operands which are neg(..)
		by - ,if poss */
		exp sum = *(e);
		exp list;
		bool someneg = 0;
		bool allneg = 1;

		for (list = son(sum); optop(sum); list = bro(list)) {
			if (list->tag == neg_tag) {
				someneg = 1;
			} else {
				allneg = 0;
			}

			if (list->last) {
				break;
			}
		}

		/* there are some neg() operands */
		if (someneg) {
			if (allneg) {
				/* transform -..-... to -(..+.. +...) */
				exp x = son(sum);
				list = son(x);

				/* ALTERATION #1 here to fix minor structural bug */
				for (;;) {
					if (!x->last) {
						bro(list) = son(bro(x));
						list->last = false;
						list = bro(list);
						x = bro(x);
					} else {
						bro(list) = sum;
						list->last = true;
						son(sum) = son(son(sum));
						/* use existing exp */
						break;
					}
				}

				x = getexp(sh(sum), bro(sum), sum->last, sum, NULL, 0, 0, neg_tag);
				sum->last = true;
				bro(sum) = x; /* set father of sum to be negate */
				*e = x;

				/* end allneg */
			} else {
				/* transform to  ((..(..+..) - ..) -..) */
				int n = 0;
				exp brosum = bro(sum);
				bool lastsum = sum->last;
				exp x = son(sum);
				exp newsum = sum;
				list = NULL;

				for (;;) {
					exp nxt = bro(x);
					bool final = x->last;
					if (x->tag == neg_tag) {
						bro(son(x)) = list;
						list = son(x);
					} else {
						bro(x) = newsum;
						newsum = x;
						if ((n++) == 0) {
							newsum->last = true;
						} else {
							newsum->last = false;
						}
					}
					if (final) {
						break;
					}
					x = nxt;
				}

				if (n > 1) {
					son(sum) = newsum;
					newsum = sum; /* use existing exp for add operations */
				}

				/* introduce - operations */
				for (;;) {
					exp nxt = bro(list);
					bro(newsum) = list;
					newsum->last = false;
					x = getexp(sh(sum), NULL, 0, newsum, NULL, 0, 0, minus_tag);

					bro(list) = x;
					list->last = true;
					newsum = x;
					if ((list = nxt) == NULL) {
						break;
					}
				}

				bro(newsum) = brosum;
				if (lastsum) {
					newsum->last = true;
				} else {
					newsum->last = false;
				}

				*e = newsum;
			}
			/* end else allneg */

			return scan(e, at);
		}

		/* end someneg - else continue to next case */
	}

		FALL_THROUGH;

	case and_tag:
	case mult_tag:
	case or_tag:
	case xor_tag:
		return likeplus(e, at);

	case addptr_tag: {
		exp ptr_arg = son(*e);
		exp offset_arg = bro(ptr_arg);
		int fralign = frame_al_of_ptr(sh(ptr_arg));

		if (fralign) {
			int offalign = frame_al1_of_offset(sh(offset_arg));

#if 0
			if (((offalign - 1) & offalign) != 0) {
				error(ERR_INTERNAL, "Mixed frame offsets not supported");
			}
#endif

			if (includes_vcallees(fralign) && l_or_cees(offalign)) {
				exp newexp = getexp(sh(ptr_arg), offset_arg, 0, ptr_arg,
					NULL, 0, 0, locptr_tag);
				bro(ptr_arg) = newexp;
				ptr_arg->last = true;
				son(*e) = newexp;
			}
		}

		return likediv(e, at);
	}

	case locptr_tag:
	case reff_tag:
	case offset_pad_tag:
	case chvar_tag: {
		exp *arg = &son(*e);
		needs nds;
		nds = maxneeds(scan(arg, at), shapeneeds(sh(*(e))));
		/* nds.fixneeds += 1;*/
		return nds;
	}

	case float_tag: {
		needs nds;
		exp *arg = &son(*e);
		nds = maxneeds(scan(arg, at), shapeneeds(sh(*(e))));
		if ((sh(son(*(e)))->tag == ulonghd) || (sh(son(*(e)))->tag == u64hd)) {
			if (nds.floatneeds < 2) {
				nds.floatneeds = 2; /* remove */
			}
		}

		has_float = 1;
		return nds;
	}

	case cont_tag:
	case contvol_tag: {
		exp *arg = &son(*e);
		needs nds;

		nds = maxneeds(scan(arg, at), shapeneeds(sh(*(e))));

		if (is_awkward_variety(sh(*e)->tag)) {
			nds.fixneeds = MAX(nds.fixneeds, 4);
		} else {
			nds.fixneeds = MAX(nds.fixneeds, 2);
		}

		if (nstare != cont_tag) {
			nds.propsneeds |= uses2_bit;
		}

		return nds;
	}

	case offset_mult_tag:
	case offset_div_tag: {
		exp op2 = bro(son(*e));
		shape s = sh(op2);

		if (op2->tag == val_tag && no(op2) == 8 && s->tag == offsethd && al2(s) >= 8) {
			/* offset is one byte */
			exp op1 = son(*e);
			bro(op1) = bro(*e);

			if ((*e)->last) {
				op1->last = true;
			} else {
				op1->last = false;
			}

			*e = op1;
			return scan(e, at);
		}

		/*... else continue */
	}

		FALL_THROUGH;

	case div2_tag:
	case rem2_tag:
	case rem0_tag:
	case div0_tag:
	case offset_div_by_int_tag:
		if (is_machine_divide(*e)) {
			has_div = 1;
		}

		return likediv(e, at);

	case offset_add_tag:
	case offset_subtract_tag:
		if ((al2(sh(son(*e))) == 1) && (al2(sh(bro(son(*e)))) != 1)) {
			make_bitfield_offset(bro(son(*e)), son(*e), 0, sh(*e));
		}

		if ((al2(sh(son(*e))) != 1) && (al2(sh(bro(son(*e)))) == 1)) {
			make_bitfield_offset(son(*e), *e, 1, sh(*e));
		}

		FALL_THROUGH;

#ifdef make_stack_limit_tag
	case make_stack_limit_tag:
#endif
	case min_tag:
	case max_tag:
	case minus_tag:
	case subptr_tag:
	case minptr_tag:
	case offset_max_tag:
	case component_tag:
		return likediv(e, at);

	case div1_tag:
		if (is_machine_divide(*e)) {
			has_div = 1;
		}

		if ((sh(*e)->tag & 1) == 0) {
			(*e)->tag = div2_tag;
		}

		return likediv(e, at);

	case mod_tag:
		if (is_machine_divide(*e)) {
			has_div = 1;
		}

		if ((sh(*e)->tag & 1) == 0) {
			(*e)->tag = rem2_tag;
		}

		return likediv(e, at);

	case fdiv_tag:
	case fplus_tag:
	case fminus_tag:
	case fmult_tag: {
		exp op = *(e);
		exp a2 = bro(son(op));
		has_float = 1;

		if (!a2->last) {
			/* + and * can have >2 parameters
			   - make them diadic - can do better
			   a+exp => let x = exp in a+x */
			exp opn = getexp(sh(op), op, 0, a2, NULL, 0, 0, op->tag);

			/* dont need to transfer error treatment - nans */
			exp nd = getexp(sh(op), bro(op), op->last, opn, NULL, 0, 1, ident_tag);
			exp id = getexp(sh(op), op, 1, nd, NULL, 0, 0, name_tag);
			pt(nd) = id;
			bro(son(op)) = id;
			op->last = true;
			bro(op) = nd;

			while (!a2->last) {
				a2 = bro(a2);
			}

			bro(a2) = opn;
			*(e) = nd;
			return scan(e, at);
		}

		return fpop(e, at);
	}

	case fmax_tag:
		has_float = 1;
		return fpop(e, at);

	case field_tag: {
		needs str;
		exp *arg = &son(*e);

		if (chase(*e, arg)) { /* field has been distributed */
			exp stare = *e;
			exp ss = son(stare);
			if (!stare->last) {
				ss->last = false;
			}

			bro(ss) = bro(stare);
			sh(ss)  = sh(stare);

			*e = ss;
			return scan(e, at);
		}

		str = scan(arg, at);
		return maxneeds(str, shapeneeds(sh(*(e))));
	}

	case general_proc_tag:
	case proc_tag: {
		exp *bexp;
		exp *bat;
		needs body;
		exp stare = *e;
		callerfortr = optim & OPTIM_TAIL && !proc_has_setjmp(stare)
		              && !proc_has_alloca(stare) && !proc_has_lv(stare) &&
		              !proc_uses_crt_env(stare);
		callerfortr = 0;
		maxfix = 12;  /* excluding regs corrupted by div */
		maxfloat = 12; /* jm - 21? */
		stparam = 0;
		fixparam = 16;
		floatparam = 16;
		nonevis = true;
		numparams = 0;
		callee_size = 0;
		gen_call = (stare->tag == general_proc_tag);
		in_vcallers_proc = (gen_call && proc_has_vcallers(stare));
		bexp = & son(*e);
		bat = bexp;
		body = scan(bexp, &bat);

		/* scan the body of the proc */
		if (gen_call || Has_fp) {
			/* reserve space for the link area */
			callee_size += 4 * PTR_SZ;
		}

#if 0
		if (stare->tag == proc_tag && gen_call) {
			set_proc_has_gen_call(*e);
		}

#endif

		if (has_old_varargs) {
			set_has_c_vararg(*e);
			has_old_varargs = 0;
		}

		if (has_div) {
			set_has_machine_division(*e);
			has_div = 0;
		}

		/* need to allocate space on stack for a float <-> int register move */
		if (has_float) {
			set_has_float(*e);
		}

		return body; /* should never require this in reg in C */
	}

	case movecont_tag: {
		exp *d = &son(*e);
		exp *s = & bro(*d);
		exp *sz = &bro(*s);

		needs nd;
		needs ns;
		needs nsz;
		prop prps;

		nd   = scan(d, at);
		ns   = scan(s, at);
		nsz  = scan(sz, at);
		prps = (ns.propsneeds & hasproccall) << 1;

		if (ns.fixneeds >= maxfix || prps != 0) {
			/* if reg requirements overlap, identify
			   second operand */
			cca(at, s);
			ns = shapeneeds(sh(*(s)));
			ns.propsneeds |= morefix;
			ns.propsneeds &= ~(prps >> 1);
			ns.propsneeds |= prps;
		}

		nd.fixneeds += 1;
		nd = maxneeds (nd, ns); /* ns? */
		prps = (nsz.propsneeds & hasproccall) << 1;

		/* if reg requirements overlap, identify last operand */
		if (nd.fixneeds + nsz.fixneeds >= maxfix || prps != 0) {
			cca(at, sz);
			nsz = shapeneeds(sh(*(sz)));
			nsz.propsneeds |= morefix;
			nsz.propsneeds &= ~(prps >> 1);
			nsz.propsneeds |= prps;
		}

		nd.fixneeds += 1;
		nd = maxneeds(nd, nsz);
		if (nd.fixneeds < 4) {
			nd.fixneeds = 3;
		}

		return nd;
	}

	case trap_tag:
	case special_tag:
		return zeroneeds;

	default:
		printf("case %d not covered in needs scan\n", (*e)->tag);
		/* NB should call failer */
		return zeroneeds;
	}
}

