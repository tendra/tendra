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

/*
 * op values a1, a2 of shape sha and put them in dest. opb, opw and opl are the
 * byte, short and long versions of the operator. one is the unit for the
 * operator. Similar to plus qv. for comments.
 */
static void
andetc(char *opb, char *opw, char *opl, int one, shape sha, where a1, where a2, where dest)
{
	int sz;
	exp a = a1.where_exp;
	int aoff = a1.where_off;
	exp b = a2.where_exp;
	int boff = a2.where_off;
	exp holda = son(a);
	exp holdb = son(b);
	sz = shape_size(sha);

	if (a->tag == val_tag && !isbigval(a) && no(a) + aoff == one) {
		move(sha, a2, dest);
		return;
	}

	if (b->tag == val_tag && !isbigval(b) && no(b) + boff == one) {
		move(sha, a1, dest);
		return;
	}

	cond1_set = true;
	cond2_set = false;
	cond1     = dest; /* conditions will be set from dest */

	if (eq_where(a1, dest) &&
	    (!keep_short || !flinmem(dest))) {
		if (!inmem(a1) || !inmem(a2)) {
			/* use 2 address */
			int riu = regsinuse;
			if (sz == 64) {
				regsinuse |= 0x2;
			}

			if (inmem(a1)) {
				contop(a, eq_where(reg0, a2), a1);
			} else {
				contop(b, (eq_where(reg0, a2) || eq_where(reg0, a1)), a1);
			}

			if (sz == 8) {
				ins2(opb, sz, sz, a2, a1);
			} else if (sz == 16) {
				ins2(opw, sz, sz, a2, a1);
			} else if (sz == 32) {
				ins2(opl, sz, sz, a2, a1);
			} else if (sz == 64) {
				where dhi, dlo, shi, slo;

				if (inmem(a1)) {
					dlo = a1;
					dhi = mw(a, aoff + 32);
				} else {
					dlo = reg0;
					dhi = reg1;
				}

				if (b->tag == val_tag) {
					int c, c1;
					if (!isbigval(b)) {
						c = no(b) + boff;
						c1 = (sha->tag == s64hd && c < 0) ? -1 : 0;
					} else {
						flt64 x;
						int ov;
						x = flt_to_f64(no(b), is_signed(sha), &ov);
						c = x.small;
						c1 = x.big;
					}
					if (c != one) {
						ins2(opl, 32, 32, mw(zeroe, c), dlo);
					}
					if (c1 != one) {
						ins2(opl, 32, 32, mw(zeroe, c1), dhi);
					}
				} else {
					if (inmem(a2)) {
						slo = a2;
						shi = mw(b, boff + 32);
					} else {
						slo = reg0;
						shi = reg1;
					}
					ins2(opl, 32, 32, slo, dlo);
					ins2(opl, 32, 32, shi, dhi);
				}
			}

			invalidate_dest(dest);
			end_contop();
			regsinuse = riu;
			son(a) = holda;
			son(b) = holdb;
			return;
		}

		move(sha, a2, reg0);
		andetc(opb, opw, opl, one, sha, reg0, dest, dest);
		return;
	}

	if (eq_where(a2, dest) &&
	    (!keep_short || !flinmem(dest))) {	/* use 2 address */
		if (!inmem(a1) || !inmem(a2)) {
			int riu = regsinuse;

			if (sz == 64) {
				regsinuse |= 0x2;
			}

			if (inmem(a1)) {
				contop(a, eq_where(reg0, a2), a2);
			} else {
				contop(b, (eq_where(reg0, a1) || eq_where(reg0, a2)), a2);
			}

			if (sz == 8) {
				ins2(opb, sz, sz, a1, a2);
			} else if (sz == 16) {
				ins2(opw, sz, sz, a1, a2);
			}

			if (sz == 32) {
				ins2(opl, sz, sz, a1, a2);
			} else if (sz == 64) {
				where dhi, dlo, shi, slo;

				if (inmem(a2)) {
					dlo = a2;
					dhi = mw(b, boff + 32);
				} else {
					dlo = reg0;
					dhi = reg1;
				}

				if (a->tag == val_tag) {
					int c, c1;

					if (!isbigval(a)) {
						c = no(a) + aoff;
						c1 = (sha->tag == s64hd && c < 0) ? -1 : 0;
					} else {
						flt64 x;
						int ov;
						x = flt_to_f64(no(a), is_signed(sha), &ov);
						c = x.small;
						c1 = x.big;
					}

					if (c != one) {
						ins2(opl, 32, 32, mw(zeroe, c), dlo);
					}

					if (c1 != one) {
						ins2(opl, 32, 32, mw(zeroe, c1), dhi);
					}
				} else {
					if (inmem(a1)) {
						slo = a1;
						shi = mw(a, aoff + 32);
					} else {
						slo = reg0;
						shi = reg1;
					}

					ins2(opl, 32, 32, slo, dlo);
					ins2(opl, 32, 32, shi, dhi);
				}
			}

			invalidate_dest(dest);
			end_contop();
			regsinuse = riu;
			son(a) = holda;
			son(b) = holdb;
			return;
		}

		move(sha, a1, reg0);
		andetc(opb, opw, opl, one, sha, reg0, dest, dest);
		return;
	}

	switch ((inmem(a1) << 2) + (inmem(a2) << 1) + inmem(dest)) {
	case 0:
		move(sha, a2, dest);
		andetc(opb, opw, opl, one, sha, a1, dest, dest);
		return;

	case 1:
	case 3:
	case 5:
	case 7:
		andetc(opb, opw, opl, one, sha, a1, a2, reg0);
		move(sha, reg0, dest);
		return;

	case 2:
		if (eq_where(a1, reg0)) {
			reg0_in_use = 1;
		}

		move(sha, a2, dest);
		andetc(opb, opw, opl, one, sha, a1, dest, dest);
		return;

	case 4:
		if (eq_where(a2, reg0)) {
			reg0_in_use = 1;
		}

		move(sha, a1, dest);
		andetc(opb, opw, opl, one, sha, a2, dest, dest);
		return;

	default: /* case 6 */
		move(sha, a2, reg0);
		andetc(opb, opw, opl, one, sha, a1, reg0, reg0);
		move(sha, reg0, dest);
		return;
	}
}

void
and(shape sha, where a1, where a2, where dest)
{
	andetc(andb, andw, andl, -1, sha, a1, a2, dest);
}

void
or(shape sha, where a1, where a2, where dest)
{
	andetc(orb, orw, orl, 0, sha, a1, a2, dest);
}

void
xor(shape sha, where a1, where a2, where dest)
{
	andetc(xorb, xorw, xorl, 0, sha, a1, a2, dest);
}

/* put not(a) into dest, shape sha */
void
not(shape sha, where a, where dest)
{
	int  sz;
	sz = shape_size(sha);

	cond1_set = false;
	cond2_set = false;

	if (!inmem (a) && eq_where (a, dest)) {
		/* inverting in situ */
		if (sz == 8) {
			ins1(notb, sz, dest);
			invalidate_dest(dest);
			return;
		}
		if (sz == 16) {
			ins1(notw, sz, dest);
			invalidate_dest(dest);
			return;
		}
		if (sz == 32) {
			ins1(notl, sz, dest);
			invalidate_dest(dest);
			return;
		}
		if (sz == 64) {
			/* must be reg0/1 */
			ins1(notl, 32, reg0);
			ins1(notl, 32, reg1);
			invalidate_dest(reg0);
			invalidate_dest(reg1);
			return;
		}
	}

	if (!inmem(a) && a.where_exp->tag != val_tag &&
	    (w_islastuse(a) || eq_where(a, reg0))) {
		not(sha, a, a);
		move(sha, a, dest);
		return;
	}

	if (!inmem (dest)) {
		/* dest is a register */
		move(sha, a, dest);
		not(sha, dest, dest);
		invalidate_dest(dest);
		return;
	}

	/* dest is in memory, a is either in memory or needed, it won't be reg0 */
	move(sha, a, reg0);
	not(sha, reg0, reg0);
	move(sha, reg0, dest);
}

/*
 * Shift from wshift places to to.
 */
void
shiftl(shape sha, where wshift, where from, where to)
{
	exp p = wshift.where_exp;
	int  places = no(p) + wshift.where_off;
	char *shifter;
	int  sz;
	int sig = is_signed(sha);
	exp holdto = son(to.where_exp);
	sz = shape_size(sha);

	cond1_set = false;
	cond2_set = false;

	if (sz == 64) {
		int riu = regsinuse;
		move(sha, from, reg0);

		if (wshift.where_exp->tag == val_tag) {
			rotshift64(0, sig, wshift);
		} else {	/* need count in reg2 */
			if (regsinuse & 0x4) {
				ins0(pushecx);
#ifdef DWARF2
				if (diag == DIAG_DWARF2 && no_frame) {
					dw2_track_push();
				}
#endif
				extra_stack += 32;
				check_stack_max;
			}

			reg0_in_use = 1;
			regsinuse |= 0x2;
			move(slongsh, wshift, reg2);
			rotshift64(0, sig, wshift);
			invalidate_dest(reg2);

			if (regsinuse & 0x4) {
				ins0(popecx);
#ifdef DWARF2
				if (diag == DIAG_DWARF2 && no_frame) {
					dw2_track_pop();
				}
#endif
				extra_stack -= 32;
			}
		}

		invalidate_dest(reg0);
		invalidate_dest(reg1);
		move(sha, reg0, to);
		regsinuse = riu;
		return;
	}

	/* choose shift operation from signedness and length */
	switch (sz) {
	case  8: shifter = sig ? salb : shlb; break;
	case 16: shifter = sig ? salw : shlw; break;
	default: shifter = sig ? sall : shll; break;
	}

	if (p->tag == val_tag) {	/* no of places is constant */
		if (places >= 32) {
			move(sha, zero, to);
			return;
		}

		if (places == 0) {
			move(sha, from, to);
			return;
		}

		if (places >= 1 && places <= 1) {	/* correspond to longc_mult */
			int k = 8;

			if (places == 1) {
				k = 2;
			}

			if (places == 2) {
				k = 4;
			}

			longc_mult(from, mw(zeroe, k), to, 0);
			return;
		}

		if (eq_where (from, to)) {	/* shift in situ */
			contop(to.where_exp, 0, to);
			ins2(shifter, 8, sz, wshift, to);
			invalidate_dest(to);
			end_contop();
			son(to.where_exp) = holdto;
			return;
		}

		if (!inmem (to)) {		/* to is a register */
			move(sha, from, to);
			contop(to.where_exp, 0, to);
			ins2(shifter, 8, sz, wshift, to);
			invalidate_dest(to);
			end_contop();
			son(to.where_exp) = holdto;
			return;
		}

		/* use reg0 to shift in */
		move(sha, from, reg0);
		ins2(shifter, 8, sz, wshift, reg0);
		invalidate_dest(reg0);
		move(sha, reg0, to);
		invalidate_dest(to);
		return;
	}

	/* we don't know the number of places */
	{
		int to_reg2, wshift_reg2;
		to_reg2 = eq_where(to, reg2);
		wshift_reg2 = eq_where(wshift, reg2);

		if (!to_reg2 && (regsinuse & 0x4) && !wshift_reg2) {
			ins0(pushecx);

#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_push();
			}
#endif

			extra_stack += 32;
			check_stack_max;
		}

		/* scan has guaranteed that wshift is not in reg0 */

		change_var(slongsh, from, reg0);
		reg0_in_use = 1;
		move(slongsh, wshift, reg2);

		ins2(shifter, 8, sz, reg2, reg0);
		invalidate_dest(reg0);
		invalidate_dest(reg2);

		if (!to_reg2 && (regsinuse & 0x4) && !wshift_reg2) {
			ins0(popecx);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_pop();
			}
#endif
			extra_stack -= 32;
		}

		/* reg2 might be used in the address of to */
		move(sha, reg0, to);
	}

}

/*
 * Shift from wshift places to to.
 */
static void
rotshiftr(int shft, shape sha, where wshift, where from, where to)
{
	exp p = wshift.where_exp;
	int places = no(p) + wshift.where_off;
	char *shifter;
	int sz;
	int sig = is_signed(sha);
	exp holdto = son(to.where_exp);
	sz = shape_size(sha);

	cond1_set = false;
	cond2_set = false;

	if (sz == 64) {
		int riu = regsinuse;
		move(sha, from, reg0);

		if (wshift.where_exp->tag == val_tag) {
			rotshift64(shft + 1, sig, wshift);
		} else {	/* need count in reg2 */
			if (regsinuse & 0x4) {
				ins0(pushecx);
#ifdef DWARF2
				if (diag == DIAG_DWARF2 && no_frame) {
					dw2_track_push();
				}
#endif
				extra_stack += 32;
				check_stack_max;
			}

			reg0_in_use = 1;
			regsinuse |= 0x2;
			move(slongsh, wshift, reg2);
			rotshift64(shft + 1, sig, wshift);
			invalidate_dest(reg2);
			if (regsinuse & 0x4) {
				ins0(popecx);
#ifdef DWARF2
				if (diag == DIAG_DWARF2 && no_frame) {
					dw2_track_pop();
				}
#endif
				extra_stack -= 32;
			}
		}

		invalidate_dest(reg0);
		invalidate_dest(reg1);
		move(sha, reg0, to);
		regsinuse = riu;
		return;
	}

	if (shft == 0) {
		switch (sz) {
		case  8: shifter = sig ? sarb : shrb; break;
		case 16: shifter = sig ? sarw : shrw; break;
		default: shifter = sig ? sarl : shrl; break;
		}
	} else {
		switch (sz) {
		case  8: shifter = (shft == 1) ? rorb : rolb; break;
		case 16: shifter = (shft == 1) ? rorw : rolw; break;
		default: shifter = (shft == 1) ? rorl : roll; break;
		}
	}

	if (p->tag == val_tag) {
		if (places >= 32) {
			if (sig) {
				no(p) = 31;
			} else {
				move(sha, zero, to);
				return;
			}
		}

		if (eq_where(from, to)) {
			contop(to.where_exp, 0, to);
			ins2(shifter, 8, sz, wshift, to);
			invalidate_dest(to);
			end_contop();
			son(to.where_exp) = holdto;
			return;
		}

		if (!inmem(to)) {
			move(sha, from, to);
			contop(to.where_exp, 0, to);
			ins2(shifter, 8, sz, wshift, to);
			invalidate_dest(to);
			end_contop();
			son(to.where_exp) = holdto;
			return;
		}

		move(sha, from, reg0);
		ins2(shifter, 8, sz, wshift, reg0);
		invalidate_dest(reg0);
		move(sha, reg0, to);
		return;
	}

	{
		int to_reg2, wshift_reg2;
		int selfed = 0;
		to_reg2 = eq_where(to, reg2);
		wshift_reg2 = eq_where(wshift, reg2);

		if (!to_reg2 && (regsinuse & 0x4) && !wshift_reg2) {
			ins0(pushecx);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_push();
			}
#endif
			extra_stack += 32;
			check_stack_max;
		}

		/* scan has guaranteed that wshift is not in reg0 */

		if (eq_where(from, to) &&
		    !eq_where(from, reg2) &&
		    ((regsinuse & 0x4) == 0 || wshift_reg2) &&
		    sz == 32) {
			move(slongsh, wshift, reg2);
			ins2(shifter, 8, sz, reg2, to);
			invalidate_dest(to);
			invalidate_dest(reg2);
			selfed = 1;
		} else {
			change_var(slongsh, from, reg0);
			reg0_in_use = 1;
			move(slongsh, wshift, reg2);

			ins2(shifter, 8, sz, reg2, reg0);
			invalidate_dest(reg0);
			invalidate_dest(reg2);
		}

		if (!to_reg2 && (regsinuse & 0x4) && !wshift_reg2) {
			ins0(popecx);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_pop();
			}
#endif
			extra_stack -= 32;
		}

		/* reg2 might be used in the address of to */
		if (!selfed) {
			move(sha, reg0, to);
		}
	}
}

/* shift from wshift places to to. */
void
shiftr(shape sha, where wshift, where from, where to)
{
	rotshiftr(0, sha, wshift, from, to);
}

/* shift from wshift places to to. */
void
rotater(shape sha, where wshift, where from, where to)
{
	rotshiftr(1, sha, wshift, from, to);
}

/* shift from wshift places to to. */
void
rotatel(shape sha, where wshift, where from, where to)
{
	rotshiftr(2, sha, wshift, from, to);
}

static int
adjust_pos(exp e, int nbits)
{
	int pos;

	UNUSED(nbits);

	pos = no(e) % 8;
	no(e) -= pos;

	return pos;
}

/*
 * Find bit position of bitfield defined by e, and alter e to address
 * the start of the byte.
 */
static int
bit_pos_cont(exp e, int nbits)
{
	if (e->tag == reff_tag ||
	    e->tag == name_tag) {
		return adjust_pos(e, nbits);
	}

	if (e->tag == ident_tag) {
		if (bro(son(e))->tag == reff_tag) {
			return adjust_pos(bro(son(e)), nbits);
		}

		if (bro(son(e))->tag == ident_tag) {
			return bit_pos_cont(bro(son(e)), nbits);
		}

		if (bro(son(e))->tag == name_tag &&
		    son(bro(son(e))) == e &&
		    son(e)->tag == name_tag) {
			return bit_pos_cont(son(son(e)), nbits);
		}

		if (son(e)->tag == name_tag) {
			return adjust_pos(son(e), nbits);
		}

		return 0;
	}

	error(ERR_INTERNAL, "illegal bit opnd");
	return 0;
}

/*
 * Find bit position of bitfield defined by e, and alter e to address the start
 * of the byte. Looks at top level and calls bit_pos_cont to it is a cont or ass
 * (which needs recursive calling)
 */
static int
bit_pos(exp e, int nbits)
{
	if (e->tag == name_tag) {
		return adjust_pos(e, nbits);
	}

	if (e->tag == cont_tag || e->tag == ass_tag) {
		return bit_pos_cont(son(e), nbits);
	}

	if (e->tag == ident_tag) {
		return 0;
	}

	error(ERR_INTERNAL, "illegal bit opnd");
	return 0;
}

void
mem_to_bits(exp e, shape sha, where dest, ash stack)
{
	int pos, lsn;
	int nbits = shape_size(sha);
	shape dsh;
	char *rs;
	shape move_sh;

	cond1_set = false;
	cond2_set = false;

	dsh = (is_signed(sha)) ? slongsh : ulongsh;

	pos = bit_pos(e, nbits);

	lsn = 32 - nbits - pos;
	rs = (is_signed(sha)) ? sarl : shrl;
	/* right shift with sign extension or not */

	if (pos == 0 && (nbits == 8 || nbits == 16)) {
		/* can use byte or word instructions. */
		shape osh;
		exp temp;

		if (nbits == 8) {
			if (is_signed(sha)) {
				osh = scharsh;
			} else {
				osh = ucharsh;
			}
		} else {
			if (is_signed(sha)) {
				osh = swordsh;
			} else {
				osh = uwordsh;
			}
		}

		sh(e) = osh;
		temp = getexp(dsh, NULL, 0, e, NULL, 0, 0, chvar_tag);
		make_code(dest, stack, temp);
		retcell(temp);
		return;
	}

	if ((pos + nbits) <= 8) {
		move_sh = scharsh;
	} else {
		move_sh = slongsh;
	}

	if (!inmem (dest)) {		/* dest is register */
		move (move_sh, mw (e, 0), dest);/* move e to dest */
		if (lsn != 0) {
			ins2(shll,  32,  32, mw(zeroe, lsn), dest);
		}

		invalidate_dest(dest);
		/* shift it left to remove unwanted bits */
		if (nbits != 32) {
			ins2(rs,  32,  32, mw(zeroe, 32 - nbits), dest);
		}

		/* shift it right to remove unwanted bits and propagate sign if necessary */
		invalidate_dest(dest);
		return;
	}

	move (move_sh, mw (e, 0), reg0);/* move e to reg0 */
	if (lsn != 0) {
		ins2(shll,  32,  32, mw(zeroe, lsn), reg0);
	}

	invalidate_dest(reg0);
	/* shift it left to remove unwanted bits */
	if (nbits != 32) {
		ins2(rs,  32,  32, mw(zeroe, 32 - nbits), reg0);
	}

	/* shift it right to remove unwanted bits and propagate sign if necessary */
	move (dsh, reg0, dest);/* move to dest */
}

void
bits_to_mem(exp e, exp d, ash stack)
{
	int pos;
	int nbits = shape_size(sh(e));
	int mask, lsn, k;
	where dest;
	shape move_sh;
	dest = mw(d, 0);

	cond1_set = false;
	cond2_set = false;

	pos = bit_pos(d, nbits);

	lsn = 32 - nbits - pos;
	mask = msb_mask[lsn] + lsb_mask[pos];

	k = lsb_mask[nbits] << pos;

	if ((pos + nbits) <= 8) {
		move_sh = scharsh;
		mask &= 0xff;
		k &= 0xff;
	} else {
		move_sh = slongsh;
	}

	if (e->tag == int_to_bitf_tag && son(e)->tag == val_tag) {
		if (no(son(e)) == lsb_mask[nbits]) {
			/* if we are assigning all ones, just or them in */
			or (move_sh, mw(zeroe, k), dest, dest);
			return;
		}

		if (no(son(e)) == 0) {
			/* if we are assigning all ones, just or them in */
			k = ~k;
			if ((pos + nbits) <= 8) {
				k &= 0xff;
			}
			and (move_sh, mw(zeroe, k), dest, dest);
			return;
		}
	}

	if (pos == 0 && (nbits == 8 || nbits == 16)) {
		shape osh;

		if (nbits == 8) {
			osh = ucharsh;
		} else {
			osh = uwordsh;
		}

		if (e->tag == int_to_bitf_tag) {
			if (son(e)->tag == val_tag) {
				move(osh, mw(son(e), 0), dest);
			} else {
				make_code(reg0, stack, son(e));
				move(osh, reg0, dest);
			}
		} else {
			move(osh, mw(e, 0), dest);
		}

		return;
	}

	/* mask the bits we are putting in out of the dest */
	if (e->tag != val_tag) {	/* this needs improvement */
		if (e->tag == int_to_bitf_tag) {
			make_code(reg0, stack, son(e));
		} else {
			move(sh(e), mw(e, 0), reg0);
		}

		and (slongsh, mw(zeroe, lsb_mask[nbits]), reg0, reg0);
		/* mask it to the right size */
		if (pos != 0) {
			ins2(shll,  32,  32, mw(zeroe, pos), reg0);
		}

		invalidate_dest(reg0);
		/* shift it into position */
		keep_short = false;	/* stop use of reg0 by and */
		and (move_sh, mw(zeroe, mask), dest, dest);
		add (move_sh, reg0, dest, dest);/* and add it into the dest */
		return;
	} else {
		k = (no(e) & lsb_mask[nbits]) << pos;

		/* constant bits we are assigning */
		if (k == 0) {
			return;    /* if we are assigning zero we don't need anything more */
		}

		move(slongsh, mw(zeroe, k), reg0);
		/* we don't need this move to reg0 since add looks after this better */
		keep_short = false;
		and (move_sh, mw(zeroe, mask), dest, dest);
		add (move_sh, reg0, dest, dest);/* add into dest */
		return;
	}
}

