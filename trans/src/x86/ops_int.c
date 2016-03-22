/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/string.h>

#include <local/ash.h>
#include <local/out.h>
#include <local/cpu.h>
#include <local/code.h>
#include <local/exp.h>

#ifdef DWARF2
#include <local/dw2_config.h>
#endif

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/basicread.h>
#include <reader/externs.h>

#include <construct/exp.h>
#include <construct/install_fns.h>
#include <construct/installglob.h>

#include <flpt/flpt.h>

#include <utility/bits.h>
#include <utility/max.h>

#include <main/flags.h>
#include <main/print.h>

#include <refactor/refactor.h>

#include "localtypes.h"
#include "make_code.h"
#include "cproc.h"
#include "reg_record.h"
#include "overlap.h"
#include "operand.h"
#include "instr.h"
#include "ops.h"
#include "ops_shared.h"
#include "instrs.h"

#ifdef TDF_DIAG4
#include <diag4/dg_fns.h>
#include <diag4/diagglob.h>
#endif

#ifdef DWARF2
#include <dwarf2/dw2_basic.h>
#include <dwarf2/dw2_lines.h>
#include "dw2_extra.h"
#endif

static exp lib64_error  = NULL;
static exp lib64_s_mult = NULL;
static exp lib64_u_mult = NULL;
static exp lib64_div[4];
static exp lib64_rem[4];

static int lib64_set = 0;

static void
try_overflow(shape sha, int inv)
{
	if (overflow_e != NULL) {
		exp oe = overflow_e;

		if (isov(overflow_e)) {
			exp jd = pt(son(pt(overflow_e)));
			overflow_e = NULL;
			jmp_overflow(jd, is_signed(sha), inv);
		} else if (istrap(overflow_e)) {
			overflow_e = NULL;
			trap_overflow(is_signed(sha), inv);
		}

		overflow_e = oe;
	}
}

/*
 * abs value a1 of shape sha and put it in dest
 */
void
absop(shape sha, where a1, where dest)
{
	int labno = next_lab();
	where q;
	int sz = shape_size(sha);
	char *op, *ng;

	q = dest;

	switch (sz) {
	case 8: op = testb; ng = negb; break;
	case 16: op = testw; ng = negw; break;
	case 32:
	case 64: op = testl; ng = negl; break;

	default:
		error(ERR_INTERNAL, "unexpected size");
	}

	cond1_set = false;
	cond2_set = false;

	if (inmem(dest)) {
		move(sha, a1, reg0);
		q = reg0;
	} else {
		move(sha, a1, dest);
	}

	if (sz == 64) {
		/* must be in reg0/reg1 */
		ins2(testl, 32, 32, reg1, reg1);
		simple_branch(jge, labno);
		move(slongsh, reg1, reg2);
		move(slongsh, zero, reg1);
		ins1(negl, 32, reg0);
		ins2(sbbl, 32, 32, reg2, reg1);
		try_overflow(sha, 0);
		invalidate_dest(reg1);
		invalidate_dest(reg2);
	} else {
		ins2(op, sz, sz, q, q);
		simple_branch(jg, labno);
		ins1(ng, sz, q);
		try_overflow(sha, 0);
	}

	invalidate_dest(q);
	simple_set_label(labno);
	move(sha, q, dest);
}

static void
maxmin(shape sha, where a1, where a2, where dest, int ismax)
{
	where tempw;
	int labno = next_lab();
	int lab64;
	int mem1;
	int mem2;
	char *in;
	int sz = shape_size(sha);
	char *op12;
	char *op21;
	int late_contop = 0;

	if (is_signed(sha)) {
		op12 = ismax ? jl : jg;
		op21 = ismax ? jg : jl;
	} else {
		op12 = ismax ? jb : ja;
		op21 = ismax ? ja : jb;
	}

	cond1_set = false;
	cond2_set = false;

	switch (sz) {
	case  8: in = cmpb; break;
	case 16: in = cmpw; break;
	case 32: in = cmpl; break;

	case 64:
		lab64 = next_lab();
		break;	/* use cmpl instead of in */
	default:
		error(ERR_INTERNAL, "unexpected size");
	}

	if (eq_where(a2, dest)) {
		tempw = a1;
		a1 = a2;
		a2 = tempw;
	}

	mem1 = inmem(a1);
	mem2 = inmem(a2);

	if (eq_where(a1, a2)) {
		move(sha, a1, dest);
		return;
	}

	if (eq_where(a1, dest)) {
		exp hold1 = son(a1.where_exp);
		exp hold2 = son(a2.where_exp);
		int riu = regsinuse;

		if (mem1 && mem2) {
			move(sha, a2, reg0);
			maxmin(sha, a1, reg0, dest, ismax);
			return;
		}

		if (a2.where_exp->tag != val_tag) {
			if (mem1) {
				if (sz == 64) {
					/* a2 must be reg0/1 */
					regsinuse |= 0x2;
					contop(a1.where_exp, 1, dest);
					ins2(cmpl, 32, 32, mw(a1.where_exp, a1.where_off + 32), reg1);
					simple_branch(op12, labno);
					simple_branch(jne, lab64);
					ins2(cmpl, 32, 32, a1, reg0);
					simple_branch((ismax ? jb : ja), labno);
					late_contop = contop_dopop;
					contop_dopop = 0;
				} else {
					contop(a1.where_exp, eq_where(a2, reg0), dest);
					ins2(in, sz, sz, a1, a2);
					end_contop();
					simple_branch(op12, labno);
				}
			} else {
				if (mem2) {
					if (sz == 64) {
						/* a1 and dest must be reg0/1 */
						regsinuse |= 0x2;
						contop(a2.where_exp, 1, dest);
						ins2(cmpl, 32, 32, reg1, mw(a2.where_exp, a2.where_off + 32));
						simple_branch(op12, labno);
						simple_branch(jne, lab64);
						ins2(cmpl, 32, 32, reg0, a2);
						simple_branch((ismax ? jb : ja), labno);
					} else {
						contop(a2.where_exp, eq_where(a1, reg0), dest);
						ins2(in, sz, sz, a1, a2);
						simple_branch(op12, labno);
					}
					late_contop = contop_dopop;
					contop_dopop = 0;
				} else  {		/* cannot be (sz == 64) */
					ins2(in, sz, sz, a1, a2);
					simple_branch(op12, labno);
				}
			}
		} else {
			if (sz == 64) {
				int c, c1;

				if (!isbigval(a2.where_exp)) {
					c = no(a2.where_exp) + a2.where_off;
					c1 = (is_signed(sha) && c < 0) ? -1 : 0;
				} else {
					flt64 x;
					int ov;
					x = flt_to_f64(no(a2.where_exp), is_signed(sha), &ov);
					c = x.small;
					c1 = x.big;
				}

				if (mem1) {
					contop(a1.where_exp, 0, dest);
					ins2(cmpl, 32, 32, mw(zeroe, c1), mw(a1.where_exp, a1.where_off + 32));
					simple_branch(op21, labno);
					simple_branch(jne, lab64);
					ins2(cmpl, 32, 32, mw(zeroe, c), a1);
					simple_branch((ismax ? ja : jb), labno);
					late_contop = contop_dopop;
					contop_dopop = 0;
				} else {
					/* a1 and dest must be reg0/1 */
					ins2(cmpl, 32, 32, mw(zeroe, c1), reg1);
					simple_branch(op21, labno);
					simple_branch(jne, lab64);
					ins2(cmpl, 32, 32, mw(zeroe, c), reg0);
					simple_branch((ismax ? ja : jb), labno);
				}
			} else {
				if (mem1) {
					contop(a1.where_exp, 0, dest);
					ins2(in, sz, sz, a2, a1);
					end_contop();
				} else {
					ins2(in, sz, sz, a2, a1);
				}

				simple_branch(op21, labno);
			}
		}

		if (sz == 64) {
			simplest_set_lab(lab64);
		}

		move(sha, a2, dest);
		simple_set_label(labno);
		if (late_contop) {
			contop_dopop = late_contop;
			end_contop();
		}

		regsinuse = riu;
		invalidate_dest(dest);
		invalidate_dest(a1);
		invalidate_dest(a2);
		son(a1.where_exp) = hold1;
		son(a2.where_exp) = hold2;
		return;
	}

	if (eq_where(a1, reg0)) {
		reg0_in_use = 1;
		maxmin(sha, reg0, a2, reg0, ismax);
		move(sha, reg0, dest);
		return;
	}

	if (eq_where(a2, reg0)) {
		reg0_in_use = 1;
		maxmin(sha, a1, reg0, reg0, ismax);
		move(sha, reg0, dest);
		return;
	}

	move(sha, a1, reg0);
	maxmin(sha, reg0, a2, dest, ismax);
}

/* max values a1, a2 of shape sha and put them in dest */
void
maxop(shape sha, where a1, where a2, where dest)
{
	maxmin(sha, a1, a2, dest, 1);
}

/* min values a1, a2 of shape sha and put them in dest */
void
minop(shape sha, where a1, where a2, where dest)
{
	maxmin(sha, a1, a2, dest, 0);
}

/* add values a1, a2 of shape sha and put them in dest  */
static void
add_plus(shape sha, where a1, where a2, where dest, int plus1)
{
	int sz;
	exp a = a1.where_exp;
	int aoff = a1.where_off;
	exp b = a2.where_exp;
	int boff = a2.where_off;
	sz = shape_size(sha);

	if (a->tag == val_tag && sh(a)->tag == offsethd && al2(sh(a)) != 1) {
		if (sha->tag == offsethd && al2(sha) != 1) {
			no(a) = no(a) / 8;
		}

		sh(a) = slongsh;
	}

	if (b->tag == val_tag && sh(b)->tag == offsethd && al2(sh(b)) != 1) {
		if (sha->tag == offsethd && al2(sha) != 1) {
			no(b) = no(b) / 8;
		}

		sh(b) = slongsh;
	}

	cond1_set = true;
	cond2_set = false;

	/* we know the conditions are set according to the which will be in dest */
	cond1 = dest;

	if (eq_where(a1, dest) &&
	    (!keep_short || !flinmem(dest))) {	/* altering dest */
		if (b->tag == val_tag && !plus1 && !isbigval(b) && (no(b) + boff == 0 ||
		        ((no(b) + boff == 1 || no(b) + boff == -1) && sz <= 32 &&
		         (overflow_e == NULL || is_signed(sha))))) {
			exp hold = son(a);
			if (no (b) + boff == 0) {	/* adding zero */
				cond1_set = false;		/* we didn't know conditions after all */
				return;
			}

			contop (a, 0, a1);	/* get the address of a if necessary */
			if (no (b) + boff == 1) {	/* use inc */
				if (sz == 8) {
					ins1(incb, sz, a1);
				}
				if (sz == 16) {
					ins1(incw, sz, a1);
				}
				if (sz == 32) {
					ins1(incl, sz, a1);
				}
			} else {			/* use dec */
				if (sz == 8) {
					ins1(decb, sz, a1);
				}
				if (sz == 16) {
					ins1(decw, sz, a1);
				}
				if (sz == 32) {
					ins1(decl, sz, a1);
				}
			}

			invalidate_dest(dest);
			end_contop();
			try_overflow(sha, plus1);
			son(a) = hold;
			return;
		}

		if (!inmem(a1) || !inmem(a2)) {
			/* either a1 or a2 is not in memory */
			int riu = regsinuse;
			exp holda = son(a);
			exp holdb = son(b);

			if (sz == 64) {
				regsinuse |= 0x2;
			}

			if (inmem(a1)) {
				contop(a, eq_where(reg0, a2), a1);
			} else {
				contop(b, (eq_where(reg0, a2) || eq_where(reg0, a1)), a1);
			}

			if (plus1) {
				ins0(stc);
			}

			if (sz == 8) {
				ins2((plus1 ? adcb : addb), sz, sz, a2, a1);
			}
			if (sz == 16) {
				ins2((plus1 ? adcw : addw), sz, sz, a2, a1);
			}
			if (sz == 32) {
				ins2((plus1 ? adcl : addl), sz, sz, a2, a1);
			}
			if (sz == 64) {
				where hi1, lo1, hi2, lo2;
				lo1 = a1;
				hi1 = (inmem(a1) ? mw(a, aoff + 32) : reg1);
				if (b->tag == val_tag) {
					int c, c1;
					if (!isbigval(b)) {
						c = no(b) + boff;
						c1 = (is_signed(sha) && c < 0) ? -1 : 0;
					} else {
						flt64 x;
						int ov;
						x = flt_to_f64(no(b), is_signed(sha), &ov);
						c = x.small;
						c1 = x.big;
					}
					lo2 = mw(zeroe, c);
					hi2 = mw(zeroe, c1);
				} else {
					lo2 = a2;
					hi2 = (inmem(a2) ? mw(b, boff + 32) : reg1);
				}
				ins2((plus1 ? adcl : addl), 32, 32, lo2, lo1);
				ins2(adcl, 32, 32, hi2, hi1);
			}

			invalidate_dest(dest);
			end_contop();
			regsinuse = riu;
			try_overflow(sha, plus1);
			son(a) = holda;
			son(b) = holdb;
			return;
		}

		move(sha, a2, reg0);
		add_plus(sha, reg0, a1, a1, plus1);
		invalidate_dest(dest);
		return;
	}

	if (eq_where(a2, dest) &&
	    (!keep_short || !flinmem(dest))) {	/* altering dest */
		if (a->tag == val_tag && !plus1 && !isbigval(a) && (no(a) + aoff == 0 ||
		        ((no(a) + aoff == 1 || no(a) + aoff == -1) && sz <= 32 &&
		         (overflow_e == NULL || is_signed(sha))))) {
			exp hold = son(a);

			if (no (a) + aoff == 0) {	/* adding zero */
				cond1_set = false; /* we didn't know conditions after all */
				return;
			}

			contop(b, 0, a2);
			if (no (a) + aoff == 1) {	/* use inc */
				if (sz == 8) {
					ins1(incb, sz, a2);
				}
				if (sz == 16) {
					ins1(incw, sz, a2);
				}
				if (sz == 32) {
					ins1(incl, sz, a2);
				}
			} else {			/* use dec */
				if (sz == 8) {
					ins1(decb, sz, a2);
				}
				if (sz == 16) {
					ins1(decw, sz, a2);
				}
				if (sz == 32) {
					ins1(decl, sz, a2);
				}
			}

			invalidate_dest(dest);
			end_contop();
			try_overflow(sha, plus1);
			son(a) = hold;
			return;
		}

		if (!inmem(a1) || !inmem(a2)) {
			/* either a1 or a2 is not in memory */
			int riu = regsinuse;
			exp holda = son(a);
			exp holdb = son(b);

			if (sz == 64) {
				regsinuse |= 0x2;
			}

			if (inmem(a1)) {
				contop(a, eq_where(reg0, a2), a2);
			} else {
				contop(b, (eq_where(reg0, a2) || eq_where(reg0, a1)), a2);
			}

			if (plus1) {
				ins0(stc);
			}

			if (sz == 8) {
				ins2((plus1 ? adcb : addb), sz, sz, a1, a2);
			}
			if (sz == 16) {
				ins2((plus1 ? adcw : addw), sz, sz, a1, a2);
			}
			if (sz == 32) {
				ins2((plus1 ? adcl : addl), sz, sz, a1, a2);
			}

			if (sz == 64) {
				where hi1, lo1, hi2, lo2;
				lo2 = a2;
				hi2 = inmem(a2) ? mw(b, a2.where_off + 32) : reg1;

				if (a->tag == val_tag) {
					int c, c1;
					if (!isbigval(a)) {
						c = no(a) + aoff;
						c1 = (is_signed(sha) && c < 0) ? -1 : 0;
					} else {
						flt64 x;
						int ov;
						x = flt_to_f64(no(a), is_signed(sha), &ov);
						c = x.small;
						c1 = x.big;
					}
					lo1 = mw(zeroe, c);
					hi1 = mw(zeroe, c1);
				} else {
					lo1 = a1;
					hi1 = (inmem(a1) ? mw(a, aoff + 32) : reg1);
				}

				ins2((plus1 ? adcl : addl), 32, 32, lo1, lo2);
				ins2(adcl, 32, 32, hi1, hi2);
			}

			invalidate_dest(dest);
			try_overflow(sha, plus1);
			end_contop();
			regsinuse = riu;

			son(a) = holda;
			son(b) = holdb;
			return;
		}

		move(sha, a1, reg0);
		add_plus(sha, reg0, a2, a2, plus1);
		invalidate_dest(dest);
		return;
	}

	if (a->tag == val_tag && !plus1 && !isbigval(a) && no(a) + aoff == 0) {
		/* adding zero and moving */
		cond1_set = false;
		move(sha, a2, dest);
		return;
	}

	if (b->tag == val_tag && !plus1 && !isbigval(b) && no(b) + boff == 0) {
		/* adding zero and moving */
		cond1_set = false;
		move(sha, a1, dest);
		return;
	}

	/* switch on memory position of a1, a2, dest */
	switch ((inmem(a1) << 2) + (inmem(a2) << 1) + inmem(dest)) {
	case 0: {
		/* none in memory */
		exp ap;
		int n;

		if (overflow_e != NULL || sz > 32) {
			move(sha, a2, dest);
			add_plus(sha, a1, dest, dest, plus1);
			return;
		}

		/* otherwise cannot be plus1 */
		if (a->tag == val_tag) {
			if (b->tag == val_tag) {/* we know the answer */
				cond1_set = false;
				move(sha, mw(zeroe, no(a) + no(b) + a1.where_off + a2.where_off), dest);
				return;
			}

			if (sh(a)->tag == offsethd) {
				n = 1;
			} else {
				n = 8;
			}

			if (n == 8 && (no(a) & (int)0xf0000000) == 0) {
				ap = getexp(f_bottom, NULL, 0, b, NULL, 0,
				            (no(a) + a1.where_off) * n,
				            reff_tag);
				cond1_set = false;
				ins2(leal, 32, 32, mw(ap, 0), dest);
				retcell(ap);
				invalidate_dest(dest);
				return;
			} else  {
				move(sha, a2, dest);
				add(sha, a1, dest, dest);
				return;
			}
		}

		if (b->tag == val_tag) {
			if (sh(b)->tag == offsethd) {
				n = 1;
			} else {
				n = 8;
			}

			if (n == 8 && (no(b) & (int)0xf0000000) == 0) {
				ap = getexp(f_bottom, NULL, 0, a, NULL, 0,
				            (no(b) + a2.where_off) * n,
				            reff_tag);
				cond1_set = false;
				ins2(leal, 32, 32, mw(ap, 0), dest);
				retcell(ap);
				invalidate_dest(dest);
				return;
			} else  {
				move(sha, a1, dest);
				add(sha, a2, dest, dest);
				return;
			}
		}

		ap = getexp(f_bottom, NULL, 0, a, NULL, 0, 0, addptr_tag);
		{
			exp temp = bro(a);
			bro(a) = b;
			cond1_set = false;
			ins2(leal, 32, 32, mw(ap, 0), dest);
			retcell(ap);
			invalidate_dest(dest);
			bro(a) = temp;
			return;
		}
	}

	case 1:
	case 3:
	case 5:
	case 7:
		/* dest is in memory */
		add_plus(sha, a1, a2, reg0, plus1);
		move(sha, reg0, dest);
		return;

	case 2: 			/* a2 in memory others not */
		if (eq_where(a1, reg0)) {
			reg0_in_use = 1;
		}
		move(sha, a2, dest);
		add_plus(sha, a1, dest, dest, plus1);
		invalidate_dest(dest);
		return;

	case 4: 			/* a1 in memory others not */
		if (eq_where(a2, reg0)) {
			reg0_in_use = 1;
		}
		move(sha, a1, dest);
		add_plus(sha, a2, dest, dest, plus1);
		invalidate_dest(dest);
		return;

	default: 			/* case 6 a1 and a2 in memory, dest not */
		move(sha, a2, reg0);
		add_plus(sha, a1, reg0, reg0, plus1);
		move(sha, reg0, dest);
		return;
	}
}

/* add values a1, a2 of shape sha and put them in dest */
void
add(shape sha, where a1, where a2, where dest)
{
	add_plus(sha, a1, a2, dest, 0);
}

/* negate a1 in sup_dest then add a2 and put in dest */
static void
inverted_sub(shape sha, where a1, where a2, where sup_dest, where dest)
{
	if (overflow_e == NULL) {
		negate(sha, a1, sup_dest);
		add_plus(sha, a2, sup_dest, dest, 0);
	} else {
		exp old_overflow_e = overflow_e;
		overflow_e = NULL;
		not(sha, a1, sup_dest);
		overflow_e = old_overflow_e;
		add_plus(sha, a2, sup_dest, dest, 1);
	}
}

/*
 * Subtract a1 from a2 and put in dest, shape sha, structure similar to add qv.
 * for comments
 */
void
sub(shape sha, where a1, where a2, where dest)
{
	int  sz;
	exp a = a1.where_exp;
	int  aoff = a1.where_off;
	exp b = a2.where_exp;
	sz = shape_size(sha);

	if (a->tag == val_tag && sh(a)->tag == offsethd && al2(sh(a)) != 1) {
		if (sha->tag == offsethd && al2(sha) != 1) {
			no(a) = no(a) / 8;
		}

		sh(a) = slongsh;
	}

	if (b->tag == val_tag && sh(b)->tag == offsethd && al2(sh(b)) != 1) {
		if (sha->tag == offsethd && al2(sha) != 1) {
			no(b) = no(b) / 8;
		}

		sh(b) = slongsh;
	}

	if (sha->tag & 1) {
		cond1_set = true;
		cond2_set = false;
		cond1 = dest;
	} else {
		/* the conditions are not set correctly if unsigned */
		cond1_set = false;
		cond2_set = false;
	}


	if (eq_where(a2, dest) && (!keep_short || !flinmem(dest))) {
		if (a->tag == val_tag && !isbigval(a) && (no(a) + aoff == 0 ||
		        ((no(a) + aoff == 1 || no(a) + aoff == -1) && sz <= 32 &&
		         (overflow_e == NULL || is_signed(sha))))) {
			exp hold = son(b);
			if (no (a) + aoff == 0) {	/* we didn't know the conditions */
				cond1_set = false;
				return;
			}

			contop(b, 0, a2);
			if (no (a) + aoff == 1) {	/* use dec */
				if (sz == 8) {
					ins1(decb, sz, a2);
				}
				if (sz == 16) {
					ins1(decw, sz, a2);
				}
				if (sz == 32) {
					ins1(decl, sz, a2);
				}
			} else {			/* use inc */
				if (sz == 8) {
					ins1(incb, sz, a2);
				}
				if (sz == 16) {
					ins1(incw, sz, a2);
				}
				if (sz == 32) {
					ins1(incl, sz, a2);
				}
			}

			invalidate_dest(dest);
			end_contop();
			try_overflow(sha, 0);
			son(b) = hold;
			return;
		}

		if (!inmem(a1) || !inmem(a2)) {
			int riu = regsinuse;
			exp holda = son(a);
			exp holdb = son(b);

			if (sz == 64) {
				regsinuse |= 0x2;
			}
			if (inmem(a1)) {
				contop(a, eq_where(reg0, a2), a2);
			} else {
				contop(b, (eq_where(reg0, a2) || eq_where(reg0, a1)), a2);
			}

			if (sz == 8) {
				ins2(subb, sz, sz, a1, a2);
			}
			if (sz == 16) {
				ins2(subw, sz, sz, a1, a2);
			}
			if (sz == 32) {
				ins2(subl, sz, sz, a1, a2);
			}
			if (sz == 64) {
				where hi1, lo1, hi2, lo2;

				lo2 = a2;
				hi2 = (inmem(a2) ? mw(b, a2.where_off + 32) : reg1);

				if (a->tag == val_tag) {
					int c, c1;
					if (!isbigval(a)) {
						c = no(a) + aoff;
						c1 = (is_signed(sha) && c < 0) ? -1 : 0;
					} else {
						flt64 x;
						int ov;
						x = flt_to_f64(no(a), is_signed(sha), &ov);
						c = x.small;
						c1 = x.big;
					}
					lo1 = mw(zeroe, c);
					hi1 = mw(zeroe, c1);
				} else {
					lo1 = a1;
					hi1 = (inmem(a1) ? mw(a, aoff + 32) : reg1);
				}

				ins2(subl, 32, 32, lo1, lo2);
				ins2(sbbl, 32, 32, hi1, hi2);
			}

			invalidate_dest(dest);
			end_contop();
			regsinuse = riu;
			try_overflow(sha, 0);

			son(a) = holda;
			son(b) = holdb;
			return;
		}

		move(sha, a1, reg0);
		sub(sha, reg0, dest, dest);
		invalidate_dest(dest);
		return;
	}

	if (a->tag == val_tag && !isbigval(a) && no(a) + aoff == 0) {
		cond1_set = false;
		move(sha, a2, dest);
		return;
	}

	switch ((inmem(a1) << 2) + (inmem(a2) << 1) + inmem(dest)) {
	case 0:
	case 2: /* a2 may be in mem, others not */
		if (!eq_where(a1, dest)) {
			if (eq_where(a1, reg0)) {
				reg0_in_use = 1;
			}

			move(sha, a2, dest);
			sub(sha, a1, dest, dest);
			invalidate_dest(dest);
			return;
		}

		if (eq_where(a1, reg0) || eq_where(a2, reg0)) {
			if (eq_where(a2, reg0)) {
				reg0_in_use = 1;
			}

			inverted_sub(sha, a1, a2, dest, dest);
			return;
		}

		inverted_sub(sha, a1, a2, reg0, dest);
		return;

	case 4: /* a1 in memory others not */
		if (eq_where(dest, reg0)) {
			move(sha, a2, reg0);
			sub(sha, a1, reg0, reg0);
			invalidate_dest(dest);
			return;
		}

		FALL_THROUGH;

	case 1:
	case 3:
	case 5:
	case 7: /* dest is in memory */
		sub(sha, a1, a2, reg0);
		move(sha, reg0, dest);
		return;

	default: /* case 6 a1 and a2 in memory, dest not */
		/* we ought to look to see if dest affects the addressing of a1 or
		   a2, and use it if not */
		inverted_sub(sha, a1, a2, reg0, dest);
		return;
	}
}

/*
 * Put a negated into dest, shape sha
 */
void
negate(shape sha, where a, where dest)
{
	int  sz;
	sz = shape_size(sha);

	cond1_set = true;
	cond2_set = false;
	cond1 = dest;

	if (!inmem (a) && eq_where (a, dest)) {
		/* negating in situ */
		if (sz == 8) {
			ins1(negb, sz, dest);
			invalidate_dest(dest);
		}
		if (sz == 16) {
			ins1(negw, sz, dest);
			invalidate_dest(dest);
		}
		if (sz == 32) {
			ins1(negl, sz, dest);
			invalidate_dest(dest);
		}
		if (sz == 64) {	/* must be reg0/1 */
			move(slongsh, reg1, reg2);
			move(slongsh, zero, reg1);
			ins1(negl, 32, reg0);
			ins2(sbbl, 32, 32, reg2, reg1);
			try_overflow(sha, 0);
			invalidate_dest(reg0);
			invalidate_dest(reg1);
			invalidate_dest(reg2);
			return;
		}

		try_overflow(sha, 0);
		return;
	}

	if (!inmem(a) && a.where_exp->tag != val_tag &&
	    (w_islastuse(a) || eq_where(a, reg0))) {
		/* a is a register and no longer needed */
		negate(sha, a, a);
		move(sha, a, dest);
		return;
	}

	if (!inmem (dest)) {
		/* dest is a register */
		move(sha, a, dest);
		negate(sha, dest, dest);
		invalidate_dest(dest);
		return;
	}

	/* dest is in memory, a is either in memory or needed, it won't be reg0 */
	move(sha, a, reg0);
	negate(sha, reg0, reg0);
	move(sha, reg0, dest);
}

static void
needs_lib64(void)
{
	if (!lib64_set) {
		lib64_s_mult = make_extn("__TDFUs_mult", f_proc, 0);
		lib64_u_mult = make_extn("__TDFUu_mult", f_proc, 0);
		lib64_div[0] = make_extn("__TDFUu_div2", f_proc, 0);
		lib64_div[1] = make_extn("__TDFUs_div2", f_proc, 0);
		lib64_div[2] = make_extn("__TDFUu_div1", f_proc, 0);
		lib64_div[3] = make_extn("__TDFUs_div1", f_proc, 0);
		lib64_rem[0] = make_extn("__TDFUu_rem2", f_proc, 0);
		lib64_rem[1] = make_extn("__TDFUs_rem2", f_proc, 0);
		lib64_rem[2] = make_extn("__TDFUu_rem1", f_proc, 0);
		lib64_rem[3] = make_extn("__TDFUs_rem1", f_proc, 0);
		lib64_error = make_extn("__TDFerror", slongsh, 1);

		if (!PIC_code) {
			lib64_error = getexp(slongsh, NULL, 1, lib64_error, NULL, 0, 0, cont_tag);
		}

		lib64_set = 1;
	}
}

/*
 * 64-bit multiply a1 by a2, result to reg0/1 arg shapes sh1,
 * sh2 may be 32 or 64-bit proper subset varieties for sha
 */
static void
mult64(shape sha, shape sh1, shape sh2, where a1, where a2)
{
	int riu = regsinuse;	/* we know reg2 not in use */
	exp holda2 = son(a2.where_exp);

	if (shape_size(sh1) == 32) {
		if (shape_size(sh2) != 32 || (eq_where(a2, reg0) && !eq_where(a1, reg0))) {
			mult64(sha, sh2, sh1, a2, a1);
			return;
		}

		if (eq_where(a1, reg0)) {
			int difsg = (is_signed(sh1) != is_signed(sh2));
			int lab1, lab2;
			regsinuse |= 0x2;
			contop(a2.where_exp, 1, a2);

			if (a2.where_exp->tag == val_tag) {
				if ((no(a2.where_exp) = a2.where_off) >= 0) {
					sh2 = sh1;
					difsg = 0;
				}
				reg0_in_use = 1;
				move(sh2, a2, reg2);
				a2 = reg2;
			}

			if (difsg && is_signed(sh2)) {
				if (inmem(a2)) {
					ins2(movl, 32, 32, a2, reg2);
					a2 = reg2;
				}
				ins2(xchg, 32, 32, reg0, reg2);
			}

			if (difsg) {
				lab1 = next_lab();
				lab2 = next_lab();
				ins2(testl, 32, 32, reg0, reg0);
				simple_branch(jns, lab1);
				ins1(mull, 32, a2);
				ins2(decl, 32, 32, a2, reg1);
				simple_branch(jmp, lab2);
				simplest_set_lab(lab1);
				ins1(mull, 32, a2);
				simplest_set_lab(lab2);
			} else {
				ins1((is_signed(sh1) ? imull : mull), 32, a2);
			}

			end_contop();
			regsinuse = riu;
			son(a2.where_exp) = holda2;
			return;
		}

		/* neither is in reg0 */
		if (is_signed(sh2) && !is_signed(sh1)) {
			mult64(sha, sh2, sh1, a2, a1);
			return;
		}

		if (is_signed(sh1)) {
			if (a1.where_exp->tag != val_tag) {
				move(sh1, a1, reg0);
				mult64(sha, sh1, sh2, reg0, a2);
				return;
			}

			if ((no(a1.where_exp) + a1.where_off) >= 0 || is_signed(sh2)) {
				move(sh2, a2, reg0);
				mult64(sha, sh2, sh2, reg0, a1);
				return;
			}

			/* otherwise, we are multiplying negative constant by unsigned */
			move(sh1, a1, reg0);
			contop(a2.where_exp, 1, a2);
			if (a2.where_exp->tag == val_tag) {
				reg0_in_use = 1;
				move(sh2, a2, reg2);
				a2 = reg2;
			}

			ins1(mull, 32, a2);
			ins2(subl, 32, 32, a2, reg1);
			end_contop();
			son(a2.where_exp) = holda2;
			return;
		}

		/* both are unsigned */
		if (a1.where_exp->tag == val_tag) {
			move(sh1, a1, reg0);
			mult64(sha, sh1, sh2, reg0, a2);
			return;
		}

		{
			move(sh2, a2, reg0);
			mult64(sha, sh2, sh1, reg0, a1);
			return;
		}
	}

	if (overflow_e != NULL && !optop(overflow_e)) {
		/* need library proc to check for overflow */
		needs_lib64();

		if (eq_where(a1, reg0)) {
			a1 = a2;
			a2 = reg0;
		}

		move(sha, a2, pushdest);
		extra_stack += 64;
		move(sha, a1, pushdest);
		extra_stack -= 64;
		callins(0, (is_signed(sha) ? lib64_s_mult : lib64_u_mult), stack_dec);
		add(slongsh, mw(zeroe, 16), sp, sp);
		ins2(movl, 32, 32, mw(lib64_error, 0), reg2);

		if (PIC_code) {
			ins2(movl, 32, 32, ind_reg2, reg2);
		}

		ins2(testl, 32, 32, reg2, reg2);
		test_exception(f_greater_than_or_equal, slongsh);
		return;
	}

	if (shape_size(sh2) == 32 || (a2.where_exp->tag == val_tag && !isbigval(a2.where_exp))) {
		if (eq_where(a1, reg0)) {
			reg0_in_use = 1;
			regsinuse |= 0x2;
			move(slongsh, a2, reg2);
		} else {
			move(slongsh, a2, reg2);
			regsinuse |= 0x4;
			move(sha, a1, reg0);
		}

		ins0(pushedx);
#ifdef DWARF2
		if (diag == DIAG_DWARF2 && no_frame) {
			dw2_track_push();
		}
#endif

		if (is_signed(sha) && is_signed(sh2) &&
		    (a2.where_exp->tag != val_tag || (no(a2.where_exp) + a2.where_off) < 0)) {
			ins0(pusheax);

#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_push();
			}
#endif

			ins1(mull, 32, reg2);
			if (a2.where_exp->tag != val_tag) {
				int lab1 = next_lab();
				ins2(testl, 32, 32, reg2, reg2);
				simple_branch(jns, lab1);
				ins2(subl, 32, 32, ind_sp, reg1);
				simplest_set_lab(lab1);
			} else {
				ins2(subl, 32, 32, ind_sp, reg1);
			}
			ins2(addl, 32, 32, mw(zeroe, 4), sp);
		} else {
			ins1(mull, 32, reg2);
		}

		ins2(imull, 32, 32, ind_sp, reg2);
		ins2(addl, 32, 32, reg2, reg1);
		ins0(popecx);

#ifdef DWARF2
		if (diag == DIAG_DWARF2 && no_frame) {
			dw2_track_pop();
		}
#endif

		regsinuse = riu;
		return;
	}

	if (eq_where(a1, a2)) {
		move(sha, a1, reg0);
		ins0(pushedx);

#ifdef DWARF2
		if (diag == DIAG_DWARF2 && no_frame) {
			dw2_track_push();
		}
#endif

		ins2(movl, 32, 32, reg0, reg2);
		ins1(mull, 32, reg0);
		ins2(imull, 32, 32, ind_sp, reg2);
		ins2(addl, 32, 32, reg2, reg1);
		ins2(addl, 32, 32, reg2, reg1);
		ins0(popecx);

#ifdef DWARF2
		if (diag == DIAG_DWARF2 && no_frame) {
			dw2_track_pop();
		}
#endif

		return;
	}

	if (eq_where(a2, reg0)) {
		son(a2.where_exp) = holda2;
		a2 = a1;
		holda2 = son(a2.where_exp);
		a1 = reg0;
	}

	move(sha, a1, reg0);
	reg0_in_use = 1;
	regsinuse |= 0x6;
	contop(a2.where_exp, 1, a2);
	ins0(pushedx);

#ifdef DWARF2
	if (diag == DIAG_DWARF2 && no_frame) {
		dw2_track_push();
	}
#endif

	extra_stack += 32;
	ins2(movl, 32, 32, reg0, reg2);
	ins1(mull, 32, a2);
	ins2(imull, 32, 32, mw(a2.where_exp, a2.where_off + 32), reg2);
	ins2(addl, 32, 32, reg2, reg1);
	ins0(popecx);

#ifdef DWARF2
	if (diag == DIAG_DWARF2 && no_frame) {
		dw2_track_pop();
	}
#endif

	extra_stack -= 32;
	ins2(imull, 32, 32, a2, reg2);
	ins2(addl, 32, 32, reg2, reg1);
	end_contop();
	regsinuse = riu;
	son(a2.where_exp) = holda2;
}

static void
clean_multiply(int stored)
{
	if (stored) {
		ins0(popedx);

#ifdef DWARF2
		if (diag == DIAG_DWARF2 && no_frame) {
			dw2_track_pop();
		}
#endif

		extra_stack -= 32;
		invalidate_dest(reg1);
	}
}

/*
 * multiply a1 by a2 add inc and put into dest.
 * optimisation has already been done.
 */
void
multiply(shape sha, where a1, where a2, where dest)
{
	int  sz;
	char *in;
	int stored = 0;
	exp hold_a1 = son(a1.where_exp);
	exp hold_a2 = son(a2.where_exp);
	sz = shape_size(sha);

	cond1_set = false;
	cond2_set = false;

	if (sz == 64) {
		mult64(sha, sh(a1.where_exp), sh(a2.where_exp), a1, a2);
		move(sha, reg0, dest);
		invalidate_dest(reg0);
		invalidate_dest(reg2);
		return;
	}

	if (sz == 8) {
		in = imulb;
	} else if (sz == 16) {
		in = imulw;
	} else {
		in = imull;
	}

	invalidate_dest(reg0);
	if (a2.where_exp->tag == val_tag && sz != 8 &&
	    (is_signed(sha) || overflow_e == NULL || optop(overflow_e))) {
		/* x * const->y */
		contop(a1.where_exp, eq_where(reg0, a1), dest);
		if (!inmem(dest)) {
			/* x * const->reg */
			if (a1.where_exp->tag == val_tag) {
				move(sha, a1, dest);
				son(a1.where_exp) = hold_a1;
				a1 = dest;
				hold_a1 = son(a1.where_exp);
			}
			ins3(in, sz, sz, sz, a2, a1, dest);
			invalidate_dest(dest);
			end_contop();
			try_overflow(sha, 0);
			son(a1.where_exp) = hold_a1;
			return;
		}

		/* x * const->notreg   : use reg0 */
		if (a1.where_exp->tag == val_tag) {
			move(sha, a1, reg0);
			son(a1.where_exp) = hold_a1;
			a1 = reg0;
			hold_a1 =  son(a1.where_exp);
		}

		ins3(in, sz, sz, sz, a2, a1, reg0);
		invalidate_dest(reg0);
		end_contop();
		try_overflow(sha, 0);
		move(sha, reg0, dest);
		son(a1.where_exp) = hold_a1;
		return;
	}

	if (is_signed(sha) && sz != 8) {
		/* signed : we don't have to disturb eax/edx */
		if (!inmem(dest)) {
			if (eq_where(a2, dest)) {
				contop(a1.where_exp,
				       (eq_where(reg0, a1) || eq_where(reg0, a2)), dest);
				ins2(in, sz, sz, a1, dest);
				invalidate_dest(dest);
				end_contop();
				try_overflow(sha, 0);
				son(a1.where_exp) = hold_a1;
				return;
			}
			if (eq_where(a1, dest)) {
				contop(a2.where_exp,
				       (eq_where(reg0, a1) || eq_where(reg0, a2)), dest);
				ins2(in, sz, sz, a2, dest);
				invalidate_dest(dest);
				end_contop();
				try_overflow(sha, 0);
				son(a2.where_exp) = hold_a2;
				return;
			}
		}

		if (eq_where(reg0, a2)) {
			contop(a1.where_exp, 1, reg0);
			ins2(in, sz, sz, a1, reg0);
			invalidate_dest(reg0);
			end_contop();
			try_overflow(sha, 0);
			move(sha, reg0, dest);
			son(a1.where_exp) = hold_a1;
			return;
		}

		move(sha, a1, reg0);
		contop(a2.where_exp, 1, reg0);
		ins2(in, sz, sz, a2, reg0);
		invalidate_dest(reg0);
		end_contop();
		try_overflow(sha, 0);
		move(sha, reg0, dest);
		son(a2.where_exp) = hold_a2;
		return;
	} else {
		/* unsigned : use mul which only allows eax edx result */
		/* or signed imulb with same constraint */
		if (!is_signed(sha)) {
			in = &in[1];
		}

		if ((regsinuse & 0x2) && !eq_where(dest, reg1)) {
			stored = 1;
			ins0(pushedx);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_push();
			}
#endif
			extra_stack += 32;
			check_stack_max;
			invalidate_dest(reg1);
		}

		if (eq_where(reg0, dest)) {
			if (eq_where(a2, reg0)) {
				contop(a1.where_exp, 1, a1);
				if (a1.where_exp->tag == val_tag) {
					move(sha, a1, reg1);
					ins1(in, sz, reg1);
				} else {
					ins1(in, sz, a1);
				}

				invalidate_dest(reg0);
				invalidate_dest(reg1);
				invalidate_dest(a1);
				end_contop();
				clean_multiply(stored);
				try_overflow(sha, 0);
				son(a1.where_exp) = hold_a1;
				return;
			}

			if (eq_where(a1, reg0)) {
				contop(a2.where_exp, 1, a2);
				if (a2.where_exp->tag == val_tag) {
					move(sha, a2, reg1);
					ins1(in, sz, reg1);
				} else {
					ins1(in, sz, a2);
				}

				invalidate_dest(reg0);
				invalidate_dest(reg1);
				invalidate_dest(a2);
				end_contop();
				clean_multiply(stored);
				try_overflow(sha, 0);
				son(a2.where_exp) = hold_a2;
				return;
			}
		}

		if (eq_where(reg0, a2)) {
			contop(a1.where_exp, 1, a1);
			if (a1.where_exp->tag == val_tag) {
				move(sha, a1, reg1);
				ins1(in, sz, reg1);
			} else {
				ins1(in, sz, a1);
			}

			invalidate_dest(a1);
			invalidate_dest(reg0);
			invalidate_dest(reg1);
			end_contop();
			clean_multiply(stored);
			try_overflow(sha, 0);
			move(sha, reg0, dest);
			son(a1.where_exp) = hold_a1;
			return;
		}

		move(sha, a1, reg0);
		contop(a2.where_exp, 1, a2);
		if (a2.where_exp->tag == val_tag) {
			move(sha, a2, reg1);
			ins1(in, sz, reg1);
		} else {
			ins1(in, sz, a2);
		}

		invalidate_dest(a2);
		invalidate_dest(a1);
		invalidate_dest(reg0);
		invalidate_dest(reg1);
		end_contop();
		clean_multiply(stored);
		try_overflow(sha, 0);
		move(sha, reg0, dest);
		son(a2.where_exp) = hold_a2;
		return;
	}
}

#define short_mults 6
static int mtab[short_mults] = {
	25, 15, 9, 7, 5, 3
};

/* do multiplications by small integer constants */
void
longc_mult(where a1, where a2, where dest, int inc)
{
	int i, j;
	int n = no(a2.where_exp) + a2.where_off;
	shape sha = slongsh;
	exp holdd = son(dest.where_exp);

	if (sh(a2.where_exp)->tag == offsethd && al2(sh(a2.where_exp)) != 1) {
		n = n / 8;
	}

	cond1_set = false;
	cond2_set = false;

	if (n == 0) {
		move(sha, zero, dest);
		return;
	}

	if (n == 1) {
		move(sha, a1, dest);
		return;
	}

	switch (n) {
	case 2:
		if (inmem(a1)) {
			where newdest;
			newdest = (inmem(dest)) ? reg0 : dest;
			move(sha, a1, newdest);
			add(sha, newdest, newdest, dest);
			return;
		}

		add(sha, a1, a1, dest);
		return;

	case 3:
		if (inmem(a1)) {
			move(sha, a1, reg0);
			contop(dest.where_exp, 1, dest);
			mult_op(inc, reg0, reg0, 2, dest);
			invalidate_dest(dest);
			son(dest.where_exp) = holdd;
			return;
		}

		contop(dest.where_exp, eq_where(reg0, a1), dest);
		mult_op(inc, a1, a1, 2, dest);
		invalidate_dest(dest);
		son(dest.where_exp) = holdd;
		return;

	case 5:
		if (inmem(a1)) {
			move(sha, a1, reg0);
			contop(dest.where_exp, 1, dest);
			mult_op(inc, reg0, reg0, 4, dest);
			invalidate_dest(dest);
			son(dest.where_exp) = holdd;
			return;
		}

		contop(dest.where_exp, eq_where(reg0, a1), dest);
		mult_op(inc, a1, a1, 4, dest);
		invalidate_dest(dest);
		son(dest.where_exp) = holdd;
		return;

	case 7:
		if (!inmem(a1) && !inmem(dest) && !eq_where(a1, dest)) {
			longc_mult(a1, mw(zeroe, 8), dest, inc);
			sub(sha, a1, dest, dest);
			return;
		}

		if (!inmem(a1) && !inmem(dest)) {
			if (!eq_where(a1, reg0)) {
				contop(dest.where_exp, 1, dest);
				mult_op(inc, a1, a1, 2, reg0);
				mult_op(inc, reg0, a1, 4, dest);
				invalidate_dest(reg0);
				invalidate_dest(dest);
				son(dest.where_exp) = holdd;
				return;
			} else  {
				ins0(pushedx);
#ifdef DWARF2
				if (diag == DIAG_DWARF2 && no_frame) {
					dw2_track_push();
				}
#endif
				mult_op(inc, a1, a1, 2, reg1);
				mult_op(inc, reg1, reg0, 4, dest);
				invalidate_dest(dest);
				ins0(popedx);
#ifdef DWARF2
				if (diag == DIAG_DWARF2 && no_frame) {
					dw2_track_pop();
				}
#endif
				return;
			}
		}

		if (inmem(a1) && !inmem(dest)) {
			move(sha, a1, reg0);
			longc_mult(reg0, a2, dest, inc);
			return;
		}

		multiply(sha, a1, a2, dest);
		return;

	case 9:
		if (inmem(a1)) {
			move(sha, a1, reg0);
			contop(dest.where_exp, 1, dest);
			mult_op(inc, reg0, reg0, 8, dest);
			invalidate_dest(dest);
			son(dest.where_exp) = holdd;
			return;
		}

		contop(dest.where_exp, eq_where(reg0, a1), dest);
		mult_op(inc, a1, a1, 8, dest);
		invalidate_dest(dest);
		son(dest.where_exp) = holdd;
		return;

	case 15: {
		if (!inmem(a1)) {
			mult_op(inc, a1, a1, 2, reg0);
		} else  {
			move(sha, a1, reg0);
			mult_op(inc, reg0, reg0, 2, reg0);
		}

		contop(dest.where_exp, 1, dest);
		mult_op(inc, reg0, reg0, 4, dest);
		invalidate_dest(reg0);
		invalidate_dest(dest);
		son(dest.where_exp) = holdd;
		return;
	}

	case 25: {
		if (!inmem(a1)) {
			mult_op(inc, a1, a1, 4, reg0);
		} else  {
			move(sha, a1, reg0);
			mult_op(inc, reg0, reg0, 4, reg0);
		}

		contop(dest.where_exp, 1, dest);
		mult_op(inc, reg0, reg0, 4, dest);
		invalidate_dest(reg0);
		invalidate_dest(dest);
		son(dest.where_exp) = holdd;
		return;
	}

	default:
		if ((n & (n - 1)) == 0) {
			int mask = 1;
			int c;
			for (c = 0; (mask & n) == 0; ++c) {
				mask += mask;
			}
			shiftl(sha, mw(zeroe, c), a1, dest);
			return;
		}

		if ((-n & (-n - 1)) == 0) {
			int mask = 1;
			int c;
			for (c = 0; (mask & -n) == 0; ++c) {
				mask += mask;
			}

			shiftl(sha, mw(zeroe, c), a1, dest);
			negate(sha, dest, dest);
			return;
		}

		for (i = 0; i < short_mults; ++i) {
			if ((n % mtab[i]) == 0) {
				int x = n / mtab[i];
				if ((x & (x - 1)) == 0) {
					where w;
					if (inmem(dest)) {
						w = reg0;
					} else {
						w = dest;
					}
					longc_mult(a1, mw(zeroe, mtab[i]), w, 0);
					longc_mult(w, mw(zeroe, x), dest, inc);
					return;
				}

				for (j = 0; j < short_mults; ++j) {
					if (x == mtab[j]) {
						where w;
						if (inmem(dest)) {
							w = reg0;
						} else {
							w = dest;
						}

						longc_mult(a1, mw(zeroe, mtab[i]), w, 0);
						longc_mult(w, mw(zeroe, x), dest, inc);
						return;
					}
				}
			}
		}

		multiply(sha, a1, a2, dest);
		return;
	}
}

/*
 * Multiply a1 by a2 and put into dest.
 * look out for special cases by calling longc_mult
 */
void
mult(shape sha, where a1, where a2, where dest)
{
	int  inc = 0;
	int sha_size = shape_size(sha);
	cond1_set = false;
	cond2_set = false;

	if (a1.where_exp->tag == val_tag && sha_size == 32) {
		longc_mult(a2, a1, dest, inc);
		return;
	}

	if (a2.where_exp->tag == val_tag && sha_size == 32) {
		longc_mult(a1, a2, dest, inc);
		return;
	}

	multiply(sha, a1, a2, dest);
}

/* divide top by bottom and put in dest */
static void
divit(shape sha, where bottom, where top, where dest, int whichdiv, int use_shift)
{
	int sz;
	int v;
	where d;
	int sg = is_signed(sha);
	int r1flag = 0, r2flag = 0;
	int reslab = 0, test_zero = 0, test_ov = 0;
	shape shb = sh(bottom.where_exp);
	d = bottom;

	/*
	 * Fudge because some systems have ptrdiff_t as unsigned
	 * though ANSI C says it must be signed
	 */
	if (sh(top.where_exp)->tag == offsethd) {
		sg = 1;
	}

	if (overflow_e != NULL && !istrap(overflow_e)) {
		if (bottom.where_exp->tag != val_tag || no(bottom.where_exp) == 0) {
			test_zero = 1;
		}
		if (sg && (bottom.where_exp->tag != val_tag || no(bottom.where_exp) == -1)) {
			test_ov = 1;
		}
	}

	sz = shape_size(sha);

	cond1_set = false;
	cond2_set = false;

	if ((use_shift || !sg) &&
	    bottom.where_exp->tag == val_tag && !isbigval(bottom.where_exp) &&
	    (v = no(bottom.where_exp), v > 0 && (v & (v - 1)) == 0)) {
		int  c = 0;
		int  m = 1;
		where rw;

		if (shb->tag == offsethd &&
		    al2(shb) != 1) {
			v = v / 8;
		}

		while (m != v) {
			++c;
			m = m << 1;
		}

		if (c == 0) {
			move(sha, top, dest);
			return;
		}

		if (inmem(dest)) {
			rw = reg0;
		} else {
			rw = dest;
		}
		move(sha, top, rw);
		switch (sz) {
		case  8: ins2((sg) ? sarb : shrb, 8, 8,  mw(zeroe, c), rw); break;
		case 16: ins2((sg) ? sarw : shrw, 8, 16, mw(zeroe, c), rw); break;

		case 64:
			rotshift64 (1, sg, mw (zeroe, c));	/* shift within reg0/reg1 */
			break;

		default: /* case 32 */
			ins2((sg) ? sarl : shrl, 8, 32, mw(zeroe, c), rw);
		}

		invalidate_dest(rw);
		if (inmem(dest)) {
			move(sha, rw, dest);
		}

		return;
	}

	if (sz == 64 && shape_size(shb) == 64 && (
	        bottom.where_exp->tag != val_tag || isbigval(bottom.where_exp) ||
	        no(bottom.where_exp) < 0 || sg)) {
		needs_lib64();

		if (eq_where(top, reg0)) {
			ins2(subl, 32, 32, mw(zeroe, 16), sp);
			extra_stack += 128;
			move(sha, top, mw(ind_sp.where_exp, -128));
			move(sha, bottom, mw(ind_sp.where_exp, -64));
			invalidate_dest(ind_sp);
			extra_stack -= 128;
		} else {
			move(sha, bottom, pushdest);
			extra_stack += 64;
			move(sha, top, pushdest);
			extra_stack -= 64;
		}

		callins(0, lib64_div[sg + 2 * (whichdiv == 1)], stack_dec);
		ins2(addl, 32, 32, mw(zeroe, 16), sp);
		if (overflow_e != NULL && !optop(overflow_e)) {
			ins2(movl, 32, 32, mw(lib64_error, 0), reg2);
			if (PIC_code) {
				ins2(movl, 32, 32, ind_reg2, reg2);
			}
			ins2(testl, 32, 32, reg2, reg2);
			test_exception(f_greater_than_or_equal, slongsh);
		}

		move(sha, reg0, dest);
		return;
	}

	if (sz == 8) {
		if (sg) {
			change_var(swordsh, top, reg0);
		} else {
			change_var(uwordsh, top, reg0);
		}
	} else {
		move(sha, top, reg0);
	}

	if (flinmem(bottom) || (eq_where(bottom, reg1) && sz > 8) || (whichdiv == 1 && sg)) {
		d = reg2;

		if (regsinuse & 0x4 && !eq_where(dest, reg2)) {
			/* preserve ecx if necessary */
			r2flag = 1;
			ins0(pushecx);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_push();
			}
#endif
			stack_dec -= 32;
			check_stack_max;
		}

		reg0_in_use = 1;
		if (sz == 64) {
			int riu = regsinuse;
			regsinuse |= 0x2;
			move(shb, bottom, reg2);
			regsinuse = riu;
		} else {
			move(shb, bottom, reg2);
		}
	}

	/* avoid divide by zero trap */
	if (test_zero) {
		IGNORE cmp(shb, d, zero, f_not_equal, NULL);
		if (isov(overflow_e)) {
			test_exception(f_not_equal, shb);
		} else {
			reslab = next_lab();
			simple_branch(je, reslab);
		}
	}

	/* avoid most_neg divide by -1 trap */
	if (test_ov) {
		int divlab = next_lab();
		if (reslab == 0) {
			reslab = next_lab();
		}
		IGNORE cmp(shb, d, mw(zeroe, -1), f_equal, NULL);
		simple_branch(jne, divlab);
		negate(sha, reg0, reg0);
		simple_branch(jmp, reslab);
		simple_set_label(divlab);
	}

	if (!eq_where(dest, reg1) && regsinuse & 0x2 && sz > 8) {
		r1flag = 1;
		ins0(pushedx);

#ifdef DWARF2
		if (diag == DIAG_DWARF2 && no_frame) {
			dw2_track_push();
		}
#endif

		stack_dec -= 32;
		check_stack_max;
		invalidate_dest(reg1);
	}

	/* signed */
	if (sg) {
		switch (sz) {
		case 8:
			ins1(idivb, 8, d);
			break;

		case 16:
			move(swordsh, reg0, reg1);
			ins2(sarw, 16, 16, mw(zeroe, 15), reg1);
			ins1(idivw, 16, d);
			break;

		case 64:
			error(ERR_INTERNAL, "bad operation");

		default:
			move(slongsh, reg0, reg1);
			ins2(sarl, 32, 32, mw(zeroe, 31), reg1);
			ins1(idivl, 32, d);
		}

		if (whichdiv == 1) {
			int end = next_lab();

			switch (sz) {
			case 8:
				ins0("testb %ah,%ah");
				simple_branch(je, end);
				ins0("xorb %ah,%cl");
				simple_branch(jge, end);
				ins1(decb, 8, reg0);
				break;

			case 16:
				ins2(testw, 16, 16, reg1, reg1);
				simple_branch(je, end);
				ins2(xorw, 16, 16, reg1, reg2);
				simple_branch(jge, end);
				ins1(decw, 16, reg0);
				break;

			default:
				ins2(testl, 32, 32, reg1, reg1);
				simple_branch(je, end);
				ins2(xorl, 32, 32, reg1, reg2);
				simple_branch(jge, end);
				ins1(decl, 32, reg0);
			}

			simplest_set_lab(end);
		}
	} else {			/* unsigned */
		switch (sz) {
		case 8:
			ins1(divb, 8, d);
			break;

		case 16:
			ins2(xorw, 16, 16, reg1, reg1);
			ins1(divw, 16, d);
			break;

		case 64:
			ins0(pusheax);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_push();
			}
#endif
			move(slongsh, reg1, reg0);
			ins2(xorl, 32, 32, reg1, reg1);
			ins1(divl, 32, d);
			ins2(xchg, 32, 32, ind_sp, reg0);
			ins1(divl, 32, d);
			ins0(popedx);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_pop();
			}
#endif
			break;

		default:
			ins2(xorl, 32, 32, reg1, reg1);
			ins1(divl, 32, d);
		}
	}

	invalidate_dest(reg0);
	invalidate_dest(reg1);
	invalidate_dest(reg2);

	if (r1flag) {
		ins0(popedx);
#ifdef DWARF2
		if (diag == DIAG_DWARF2 && no_frame) {
			dw2_track_pop();
		}
#endif
		stack_dec += 32;
	}

	if (reslab != 0) {
		simple_set_label(reslab);
	}

	if (r2flag) {
		ins0(popecx);
#ifdef DWARF2
		if (diag == DIAG_DWARF2 && no_frame) {
			dw2_track_pop();
		}
#endif
		stack_dec += 32;
	}

	move(sha, reg0, dest);
}

void
div2(shape sha, where bottom, where top, where dest)
{
	divit(sha, bottom, top, dest, 2, 0);
}

void
div1(shape sha, where bottom, where top, where dest)
{
	divit(sha, bottom, top, dest, 1, 1);
}

void
div0(shape sha, where bottom, where top, where dest)
{
	divit(sha, bottom, top, dest, 0, 1);
}

/*
 * Remainder after dividing top by bottom to dest
 */
static void
remit(shape sha, where bottom, where top, where dest, int whichrem, int use_mask)
{
	int sz;
	where d;
	int sg = is_signed(sha);
	int r1flag = 0, r2flag = 0;
	int v;
	int reslab = 0, test_zero = 0, test_ov = 0;
	shape shb = sh(bottom.where_exp);
	d = bottom;
	sz = shape_size(sha);

	if (overflow_e != NULL && !istrap(overflow_e)) {
		if (bottom.where_exp->tag != val_tag || no(bottom.where_exp) == 0) {
			test_zero = 1;
		}

		if (sg && (bottom.where_exp->tag != val_tag || no(bottom.where_exp) == -1)) {
			test_ov = 1;
		}
	}

	cond1_set = false;
	cond2_set = false;

	if ((use_mask || !sg) &&
	    bottom.where_exp->tag == val_tag && !isbigval(bottom.where_exp) &&
	    (v = no(bottom.where_exp), v > 0 && (v & (v - 1)) == 0)) {
		/* Use and if possible (Note this is compatible with ANSI C, but not with Ada) */
		int  c = 0;
		int  m = 1;

		while (m != v) {
			++c;
			m = m << 1;
		}

		and(sha, top, mw(zeroe, lsb_mask[c]), dest);
		return;
	}

	if (sz == 64 && shape_size(shb) == 64 && (
	        bottom.where_exp->tag != val_tag || isbigval(bottom.where_exp) ||
	        no(bottom.where_exp) < 0 || sg))
	{
		needs_lib64();
		if (eq_where(top, reg0)) {
			ins2(subl, 32, 32, mw(zeroe, 16), sp);
			extra_stack += 128;
			move(sha, top, mw(ind_sp.where_exp, -128));
			move(sha, bottom, mw(ind_sp.where_exp, -64));
			extra_stack -= 128;
		} else {
			move(sha, bottom, pushdest);
			extra_stack += 64;
			move(sha, top, pushdest);
			extra_stack -= 64;
		}

		callins(0, lib64_rem[sg + 2 * (whichrem == 1)], stack_dec);
		ins2(addl, 32, 32, mw(zeroe, 16), sp);
		if (overflow_e != NULL && !optop(overflow_e)) {
			ins2(movl, 32, 32, mw(lib64_error, 0), reg2);
			if (PIC_code) {
				ins2(movl, 32, 32, ind_reg2, reg2);
			}
			ins2(testl, 32, 32, reg2, reg2);
			test_exception(f_greater_than_or_equal, slongsh);
		}

		move(sha, reg0, dest);
		return;
	}

	if (sz == 8) {
		if (sg) {
			change_var(swordsh, top, reg0);
		} else {
			change_var(uwordsh, top, reg0);
		}
	} else {
		move(sha, top, reg0);
	}

	if (flinmem(bottom) || (eq_where(bottom, reg1) && sz > 8) || (whichrem == 1 && sg)) {
		d = reg2;
		if (regsinuse & 0x4 && !eq_where(dest, reg2)) {
			/* preserve ecx if necessary */
			r2flag = 1;
			ins0(pushecx);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_push();
			}
#endif
			stack_dec -= 32;
			check_stack_max;
		}

		reg0_in_use = 1;
		if (sz == 64) {
			int riu = regsinuse;
			regsinuse |= 0x2;
			move(shb, bottom, reg2);
			regsinuse = riu;
		} else {
			move(shb, bottom, reg2);
		}
	}

	/* avoid divide by zero trap */
	if (test_zero) {
		IGNORE cmp(shb, d, zero, f_not_equal, NULL);
		if (isov(overflow_e)) {
			test_exception(f_not_equal, shb);
		} else {
			reslab = next_lab();
			simple_branch(je, reslab);
		}
	}

	/* avoid most_neg divide by -1 trap */
	if (test_ov) {
		int divlab = next_lab();
		if (reslab == 0) {
			reslab = next_lab();
		}

		IGNORE cmp(shb, d, mw(zeroe, -1), f_equal, NULL);
		simple_branch(jne, divlab);
		move(sha, zero, reg0);
		simple_branch(jmp, reslab);
		simple_set_label(divlab);
	}

	if (!eq_where(dest, reg1) && regsinuse & 0x2 && sz > 8) {
		r1flag = 1;
		ins0(pushedx);
#ifdef DWARF2
		if (diag == DIAG_DWARF2 && no_frame) {
			dw2_track_push();
		}
#endif
		stack_dec -= 32;
		check_stack_max;
		invalidate_dest(reg1);
	}

	/* signed */
	if (sg) {
		switch (sz) {
		case 8:
			ins1(idivb, 8, d);
			break;

		case 16:
			move(swordsh, reg0, reg1);
			ins2(sarw, 16, 16, mw(zeroe, 15), reg1);
			ins1(idivw, 16, d);
			break;

		case 64:
			error(ERR_INTERNAL, "bad operation");

		default:
			move(slongsh, reg0, reg1);
			ins2(sarl, 32, 32, mw(zeroe, 31), reg1);
			ins1(idivl, 32, d);
		}

		if (whichrem == 1) {
			int end = next_lab();

			switch (sz) {
			case 8:
				ins0("testb %ah,%ah");
				simple_branch(je, end);
				move(scharsh, reg2, reg0);
				ins0("xorb %ah,%cl");
				simple_branch(jge, end);
				ins0("addb %al,%ah");
				break;

			case 16:
				ins2(testw, 16, 16, reg1, reg1);
				simple_branch(je, end);
				move(swordsh, reg2, reg0);
				ins2(xorw, 16, 16, reg1, reg2);
				simple_branch(jge, end);
				ins2(addw, 16, 16, reg0, reg1);
				break;

			default:
				ins2(testl, 32, 32, reg1, reg1);
				simple_branch(je, end);
				move(slongsh, reg2, reg0);
				ins2(xorl, 32, 32, reg1, reg2);
				simple_branch(jge, end);
				ins2(addl, 32, 32, reg0, reg1);
			}

			simple_set_label(end);
		}
	} else {
		/* unsigned */
		switch (sz) {
		case 8:
			ins1(divb, 8, d);
			break;

		case 16:
			ins2(xorw, 16, 16, reg1, reg1);
			ins1(divw, 16, d);
			break;

		case 64:
			ins0(pusheax);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_push();
			}
#endif
			move(slongsh, reg1, reg0);
			ins2(xorl, 32, 32, reg1, reg1);
			ins1(divl, 32, d);
			ins0(popeax);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_pop();
			}
#endif
			ins1(divl, 32, d);
			break;

		default:
			ins2(xorl, 32, 32, reg1, reg1);
			ins1(divl, 32, d);
		}
	}

	if (sz == 8) {
		ins0("movb %ah,%al");
	} else if (sz == 64) {
		move(slongsh, reg1, reg0);
		ins2(xorl, 32, 32, reg1, reg1);
	} else {
		move(sha, reg1, reg0);
	}

	invalidate_dest(reg0);
	invalidate_dest(reg1);
	invalidate_dest(reg2);

	if (r1flag) {
		ins0(popedx);
#ifdef DWARF2
		if (diag == DIAG_DWARF2 && no_frame) {
			dw2_track_pop();
		}
#endif
		stack_dec += 32;
	}

	if (reslab != 0) {
		simple_set_label(reslab);
	}

	if (r2flag) {
		ins0(popecx);
#ifdef DWARF2
		if (diag == DIAG_DWARF2 && no_frame) {
			dw2_track_pop();
		}
#endif
		stack_dec += 32;
	}

	move(sha, reg0, dest);
}

/* remainder after dividing top by bottom to dest */
void
rem2(shape sha, where bottom, where top, where dest)
{
	remit(sha, bottom, top, dest, 2, 0);
}

/* remainder after dividing top by bottom to dest */
void
rem0(shape sha, where bottom, where top, where dest)
{
	remit(sha, bottom, top, dest, 0, 1);
}

/* remainder after dividing top by bottom to dest */
void
mod(shape sha, where bottom, where top, where dest)
{
	remit(sha, bottom, top, dest, 1, 1);
}

