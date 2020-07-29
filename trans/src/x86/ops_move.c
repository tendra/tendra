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

static exp name_memmove = NULL; /* initialised if and when needed */

int
count_regs(int mask)
{
	return bits_in(mask & 0xf) + bits_in((mask >> 4) & 0x3);
}

/*
 * Is e in a register?
 */
int
in_reg(exp e)
{
	unsigned char  ne = e->tag;

	if (ne == name_tag && ptno(son(e)) == reg_pl) {
		int n = no(son(e));

		if (!iscaonly(son(e)) && isvar(son(e))) {
			n = (n | (int)0x80000000);
		}

		return n;
	}

	if (ne == cont_tag && son(e)->tag == name_tag &&
		isvar(son(son(e))) &&
		ptno(son(son(e))) == reg_pl) {
		int n = no(son(son(e)));

		if (!iscaonly(son(son(e))) && isvar(son(son(e)))) {
			n = (n | (int)0x80000000);
		}

		return n;
	}

	if (ne == ass_tag && son(e)->tag == name_tag &&
		isvar(son(son(e))) &&
		ptno(son(son(e))) == reg_pl) {
		int n = no(son(son(e)));

		if (!iscaonly(son(son(e))) && isvar(son(son(e)))) {
			n = (n | (int)0x80000000);
		}

		return n;
	}

	if (ne == ident_tag && ptno(e) == reg_pl) {
		int n = no(e);

		if (!iscaonly(e) && isvar(e)) {
			n = (n | (int)0x80000000);
		}

		return n;
	}

	if (ne == current_env_tag) {
		return 0x40;
	}

	return 0;
}

int
bad_from_reg(where from)
{
	return !inmem(from) && from.where_exp->tag != val_tag &&
		(in_reg(from.where_exp) & 0x70);
}

static int
all_in_regs(exp e)
{
	exp id1, id2;
	unsigned char  n = e->tag;

	if ((n == cont_tag || n == ass_tag || n == reff_tag)
		&& son(e)->tag == ident_tag) {
		id1 = son(e);

		if (ptno(son(son(id1))) != reg_pl) {
			return 0;
		}

		id2 = bro(son(id1));
		if (id2->tag != ident_tag) {
			return 1;
		}

		return ptno(son(son(id2))) == reg_pl;
	}

	return 1;
}

static int
two_contops(exp fe, exp te)
{
	int nr = count_regs((~regsinuse) & 0x3e);

	if (nr >= 2) {
		return 1;
	}

	if (nr == 1) {
		return all_in_regs(fe) || all_in_regs(te);
	}

	return all_in_regs(fe) && all_in_regs(te);
}

/*
 * Move value of shape sha from "from" to "to"
 */
void
move(shape sha, where from, where to)
{
	int sz;
	int c, c1;
	int isco = 0;
	exp fe = from.where_exp;
	exp te = to.where_exp;
	exp holdfe = son(fe);
	exp holdte = son(te);
	where reg_w;
	sz = rounder(shape_size(sha), 8);

	if (sz == 0 || eq_where(from, to)) {
		return;
	}

	/* move does not set conditions. Only clear if to spoils cond record */
	if ((cond1_set && (eq_where(to, cond1) ||
	                   invalidates(to.where_exp, cond1.where_exp))) ||
	    (cond2_set &&
	     (eq_where(to, cond2a) || eq_where(to, cond2b) ||
	      invalidates(to.where_exp, cond2a.where_exp) ||
	      invalidates(to.where_exp, cond2b.where_exp)))) {
		cond1_set = false;
		cond2_set = false;
	}

	if (fe->tag == reff_tag ||
	    (PIC_code && fe->tag == name_tag &&
	     isglob(son(fe)) &&
	     (sha->tag == offsethd) &&
	     !brog(son(fe))-> extnamed)) {
		mova(from, to);
		return;
	}

	if (sha->tag >= shrealhd && sha->tag <= doublehd) {
		/* moving a float or double */
		int f1 = in_fl_reg(from.where_exp);
		int f2 = in_fl_reg(to.where_exp);
		int f1pos = f1 ? get_reg_no(f1) : 0;
		int f2pos = f2 ? get_reg_no(f2) : 0;

		if (f1pos && f1pos == f2pos && f2 != 0x10000) {
			return;    /* from and to are the same */
		}

		if (f1pos && f1pos > f2pos && f2 != 0x10000) {
			if (f1pos == fstack_pos &&
			    from.where_exp != flstack.where_exp &&
			    /* sha->tag != doublehd && */
			    use_pop_ass(to.where_exp, from.where_exp) != 2) {
				if (flinmem (to)) {	/* are going to pop the floating point stack */
					contop (te, 0, reg0);	/* compute address of to if necessary */
					if (sha->tag == shrealhd) {
						ins1(fsts, 32, to);
					} else if (sha->tag == realhd) {
						ins1(fstl, 64, to);
					} else {
						ins1(fstpt, 96, to);
						ins1(fldt, 96, to);
					}
					end_contop();
					son(fe) = holdfe;
					son(te) = holdte;
					return;
				}

				ins1 (fst, 0, to);	/* store fstack0 into to (a reg) */
				son(fe) = holdfe;
				son(te) = holdte;
				return;
			}

			if (f1pos != fstack_pos) {
				move(sha, from, flstack);
			}

			/* push from into floating point stack */
			if (flinmem (to)) {	/* store from fstack0 into memory and pop */
				contop(te, 0, reg0);
				if (sha->tag == shrealhd) {
					ins1(fstps, 32, to);
				} else if (sha->tag == realhd) {
					ins1(fstpl, 64, to);
				} else {
					ins1(fstpt, 96, to);
				}

				pop_fl;
				end_contop();
				son(fe) = holdfe;
				son(te) = holdte;
				return;
			}

			ins1 (fstp, 0, to);	/* pop from fstack0 into floating point register */
			pop_fl;
			son(fe) = holdfe;
			son(te) = holdte;
			return;
		}

		if (in_fl_reg(to.where_exp)) {
			int fz;

			if (from.where_exp->tag == real_tag &&
			    ((fz = cmpflpt(no(from.where_exp),
			                   no(fzeroe), 5), fz) ||
			     cmpflpt(no(from.where_exp), no(fonee), 5))) {
				if (fz) {
					ins0 (fldz);    /* push zero into fstack0 */
				} else {
					ins0 (fld1);    /* push one into fstack0 */
				}
			} else {
				if (flinmem (from)) {	/* push from into fstack0 from memory */
					contop (fe, 0, reg0);	/* put address of from into reg0 if necessary */
					if (sha->tag == shrealhd) {
						ins1(flds, 32, from);
					} else if (sha->tag == realhd) {
						ins1(fldl, 64, from);
					} else {
						ins1(fldt, 96, from);
					}
					end_contop();
				} else {
					if (f1pos == fstack_pos) {/* push fstack0 */
						load_stack0();
					} else {
						ins1 (fld, 0, from);    /* push floating point register */
					}
				}
			}

			push_fl;			/* we necessarily did a push */
			if (flinmem (to)) {	/* pop fstack0 to to (in memory ) */
				contop(te, 0, reg0);
				if (sha->tag == shrealhd) {
					ins1(fstps, 32, to);
				} else if (sha->tag == realhd) {
					ins1(fstpl, 64, to);
				} else {
					ins1(fstpt, 96, to);
				}

				pop_fl;
				end_contop();
				son(fe) = holdfe;
				son(te) = holdte;
				return;
			}

			f2 = in_fl_reg(to.where_exp);
			f2pos = get_reg_no(f2);
			if (f2pos == fstack_pos) {
				son(fe) = holdfe;
				son(te) = holdte;
				return;
			}

			ins1 (fstp, 0, to);	/* store fstack0 in to (a reg) and pop floating point stack */
			pop_fl;
			son(fe) = holdfe;
			son(te) = holdte;
			return;
		}

		/* fall through for floating point number not in coprocessor */
	}

	if (to.where_exp->tag == apply_tag) {	/* pushing */
		where reg_w;

		if (fe->tag == real_tag) {
			int fv = sh(fe)->tag - shrealhd;
			r2l fint;

			fint = real2longs_IEEE(&flptnos[no(fe)], fv);
			if (sz >= 96) {
				move(slongsh, mw(zeroe, fint.i3), to);
			}

			if (sz >= 64) {
				move(slongsh, mw(zeroe, fint.i2), to);
			}

			move(slongsh, mw(zeroe, fint.i1), to);
			son(fe) = holdfe;
			son(te) = holdte;
			return;
		}

		/* we are pushing on parameter stack */
		if (sz == 32) {
			reg_w = equiv_reg(from, sz);

			if (reg_w.where_exp != NULL) {
				ins1(pushl, 32, reg_w);
#ifdef DWARF2
				if (diag == DIAG_DWARF2 && no_frame) {
					dw2_track_push();
				}
#endif
				son(fe) = holdfe;
				son(te) = holdte;
				return;
			}
		}

		if (sz == 64) {	/* must be s64 or u64 */
			if (fe->tag == val_tag) {	/* moving a constant integer */
				if (!isbigval(fe)) {
					c = no(fe) + from.where_off;
					c1 = (sha->tag == s64hd && c < 0) ? -1 : 0;
				} else {
					flt64 x;
					int ov;
					x = flt_to_f64(no(fe), is_signed(sh(fe)), &ov);
					c = x.small;
					c1 = x.big;
				}

				ins1(pushl, 32, mw(zeroe, c1));
#ifdef DWARF2
				if (diag == DIAG_DWARF2 && no_frame) {
					dw2_track_push();
				}
#endif

				ins1(pushl, 32, mw(zeroe, c));
#ifdef DWARF2
				if (diag == DIAG_DWARF2 && no_frame) {
					dw2_track_push();
				}
#endif

				son(fe) = holdfe;
				son(te) = holdte;
				return;
			}

			move(sha, from, reg0);
			ins0(pushedx);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_push();
			}
#endif

			ins0(pusheax);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_push();
			}
#endif

			son(fe) = holdfe;
			son(te) = holdte;
			return;
		}

		if (sz < 32 ||
		    (cpu & CPU_80486 && inmem(from))) {
			move(sha, from, reg0);
			ins1(pushl, 32, reg0);

#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_push();
			}
#endif

			son(fe) = holdfe;
			son(te) = holdte;
			return;
		}

		contop(from.where_exp, 0, reg0);
		ins1(pushl, sz, from);
#ifdef DWARF2
		if (diag == DIAG_DWARF2 && no_frame) {
			dw2_track_push();
		}
#endif

		end_contop();
		son(fe) = holdfe;
		son(te) = holdte;
		return;
	}

	if (inmem(from) && inmem(to) && ((sz <= 32 && sz != 24)
	                                 || sha->tag == u64hd || sha->tag == s64hd)) {
		/* from and to are both in memory */
		move(sha, from, reg0);
		move(sha, reg0, to);
		son(fe) = holdfe;
		son(te) = holdte;
		return;
	}

	if (fe->tag == real_tag) {
		int fv = sh(fe)->tag - shrealhd;
		r2l fint;

		fint = real2longs_IEEE(&flptnos[no(fe)], fv);
		move(slongsh, mw(zeroe, fint.i1), to);
		if (sz >= 64) {
			move(slongsh, mw(zeroe, fint.i2), mw(te, to.where_off + 32));
		}
		if (sz >= 96) {
			move(slongsh, mw(zeroe, fint.i3), mw(te, to.where_off + 64));
		}

		son(fe) = holdfe;
		son(te) = holdte;
		return;
	}

	if (fe->tag == val_tag) {	/* moving a constant integer */
		isco = 1;

		if (!isbigval(fe)) {
			c = no(fe) + from.where_off;
			if (sz == 64) {
				c1 = (sha->tag == s64hd && c < 0) ? -1 : 0;
			}
		} else {
			flt64 x;
			int ov;
			x = flt_to_f64(no(fe), is_signed(sh(fe)), &ov);
			c = x.small;
			c1 = x.big;
		}
	}

	if (fe->tag == null_tag) {	/* moving a constant NULL */
		isco = 1;
		c = no(fe);
	}

	if (isco) {			/* moving a constant */
		contop(te, 0, to);
		SET(c);

		if (c == 0 && !inmem (to) && sz <= 32) {/* constant is zero, so clear */
			cond1_set = false;
			cond2_set = false;
			ins2(xorl, 32, 32, to, to);
			invalidate_dest(to);
			end_contop();
			son(fe) = holdfe;
			son(te) = holdte;
			return;
		}

		/* use fastest operation for each size of constant */

		if (sz == 8 && !eq_where(to, reg5) && !eq_where(to, reg4)) {
			ins2(movb, sz, sz, mw(zeroe, (c & 0xff)), to);
			invalidate_dest(to);
			end_contop();
			son(fe) = holdfe;
			son(te) = holdte;
			return;
		}

		if (sz == 16) {
			ins2(movw, sz, sz, mw(zeroe, (c & 0xffff)), to);
			invalidate_dest(to);
			end_contop();
			son(fe) = holdfe;
			son(te) = holdte;
			return;
		}

		if (sz == 64) {
			if (eq_where(to, reg0)) {
				if (c == 0) {
					ins2(xorl, 32, 32, reg0, reg0);
				} else {
					ins2(movl, 32, 32, mw(zeroe, c), reg0);
				}

				if (c1 == 0) {
					ins2(xorl, 32, 32, reg1, reg1);
				} else {
					ins2(movl, 32, 32, mw(zeroe, c1), reg1);
				}

				invalidate_dest(reg0);
				invalidate_dest(reg1);
			} else {
				ins2(movl, 32, 32, mw(zeroe, c), to);
				ins2(movl, 32, 32, mw(zeroe, c1), mw(te, to.where_off + 32));
				invalidate_dest(to);
			}

			end_contop();
			son(fe) = holdfe;
			son(te) = holdte;
			return;
		}

		if (inmem(to) && (c == 0 &&
		                  ((te->tag == ass_tag && son(te)->tag == name_tag &&
		                    isvar(son(son(te)))) ||
		                   (te->tag == ident_tag)))) {
			reg_w = equiv_reg(from, sz);
			if (reg_w.where_exp != NULL) {
				move(sha, reg_w, to);
			} else {
				move(slongsh, from, reg0);
				move(slongsh, reg0, to);
				move_reg(from, reg0, sha);
			}
		} else {
			ins2(movl, 32, 32, from, to);
		}

		invalidate_dest(to);
		end_contop();
		son(fe) = holdfe;
		son(te) = holdte;
		return;
	}

	/* moving a non-constant value */

	if (sz == 8) {		/* moving a byte */
		if (!inmem(from) &&
		    (in_reg(from.where_exp) & 0x70)) {
			if (!inmem(to)) {
				move(slongsh, from, to);
				son(fe) = holdfe;
				son(te) = holdte;
				return;
			}

			move(slongsh, from, reg0);
			move(sha, reg0, to);
			son(fe) = holdfe;
			son(te) = holdte;
			return;
		}

		if (!inmem(to) && to.where_exp->tag != val_tag &&
		    (in_reg(to.where_exp) & 0x70)) {
			if (!inmem(from)) {
				move(slongsh, from, to);
				son(fe) = holdfe;
				son(te) = holdte;
				return;
			}

			move(sha, from, reg0);
			move(slongsh, reg0, to);
			son(fe) = holdfe;
			son(te) = holdte;
			return;
		}

		if (in_reg(from.where_exp)) {
			contop(te, eq_where(reg0, from), to);
			ins2(movb, sz, sz, from, to);
			invalidate_dest(to);
			move_reg(from, to, sha);
			end_contop();
		} else {
			reg_w = equiv_reg(from, sz);
			if (reg_w.where_exp != NULL) {
				move(sha, reg_w, to);
				move_reg(from, to, sha);
			} else {
				contop(fe, 0, to);
				ins2(movb, sz, sz, from, to);
				invalidate_dest(to);
				move_reg(from, to, sha);
				end_contop();
			}
		}

		son(fe) = holdfe;
		son(te) = holdte;
		return;
	}

	if (sz == 16) {		/* moving 16 bits */
		if (in_reg(from.where_exp)) {
			contop(te, eq_where(reg0, from), to);
			ins2(movw, sz, sz, from, to);
			invalidate_dest(to);
			move_reg(from, to, sha);
			end_contop();
		} else {
			reg_w = equiv_reg(from, sz);
			if (reg_w.where_exp != NULL) {
				move(sha, reg_w, to);
				move_reg(from, to, sha);
			} else {
				contop(fe, 0, to);
				ins2(movw, sz, sz, from, to);
				invalidate_dest(to);
				move_reg(from, to, sha);
				end_contop();
			}
		}

		son(fe) = holdfe;
		son(te) = holdte;
		return;
	}

	if (sz == 32) {		/* moving 32 bits */
		if (in_reg(from.where_exp)) {
			contop(te, eq_where(reg0, from), to);
			ins2(movl, sz, sz, from, to);
			invalidate_dest(to);
			move_reg(from, to, sha);
			end_contop();
		} else {
			reg_w = equiv_reg(from, sz);
			if (reg_w.where_exp != NULL) {
				move(sha, reg_w, to);
				move_reg(from, to, sha);
			} else {
				contop(fe, 0, to);
				ins2(movl, sz, sz, from, to);
				invalidate_dest(to);
				move_reg(from, to, sha);
				end_contop();
			}
		}

		son(fe) = holdfe;
		son(te) = holdte;
		return;
	}

	if (sz == 64 && (eq_where(to, reg0) || eq_where(from, reg0))) {
		/* moving reg0 & reg1 to or from memory */
		where w1;
		int riu = regsinuse;

		if (!eq_where(from, reg0)) {
			regsinuse |= 0x2;
			contop(fe, 0, reg0);
			w1 = mw(fe, from.where_off + 32);
			ins2(movl, sz, sz, w1, reg1);
			ins2(movl, sz, sz, from, reg0);
			invalidate_dest(reg0);
			invalidate_dest(reg1);
			end_contop();
		} else if (!eq_where(to, reg0)) {
			regsinuse |= 0x2;
			contop(te, 1, to);
			w1 = mw(te, to.where_off + 32);
			ins2(movl, sz, sz, reg0, to);
			ins2(movl, sz, sz, reg1, w1);
			invalidate_dest(to);
			end_contop();
		}

		regsinuse = riu;
		son(fe) = holdfe;
		son(te) = holdte;
		return;
	}

	if (sha->tag == realhd && might_overlap(sha, from, to)) {
		if ((regsinuse & 0x7e) != 0x7e) {
			int  foff = from.where_off;
			int  toff = to.where_off;
			int  old_regsinuse = regsinuse;
			where extra_reg;

			contop(fe, 1, to);
			regsinuse = top_regsinuse;
			contop_level++;
			reg0_in_use = 1;
			contop(te, 1, to);
			regsinuse = old_regsinuse;

			if ((regsinuse & 0x2) == 0) {
				extra_reg = reg1;
			} else if ((regsinuse & 0x4) == 0) {
				extra_reg = reg2;
			} else if ((regsinuse & 0x8) == 0) {
				extra_reg = reg3;
				min_rfree |= 0x8;
			} else if ((regsinuse & 0x10) == 0) {
				extra_reg = reg4;
				min_rfree |= 0x10;
			} else if ((regsinuse & 0x20) == 0) {
				extra_reg = reg5;
				min_rfree |= 0x20;
			} else if ((regsinuse & 0x40) == 0) {
				extra_reg = reg6;
				min_rfree |= 0x40;
			} else {
				SET(extra_reg);
			}

			ins2(movl, size32, size32, mw(fe, foff), reg0);
			ins2(movl, size32, size32, mw(fe, foff + 32), extra_reg);
			ins2(movl, size32, size32, reg0, mw(te, toff));
			ins2(movl, size32, size32, extra_reg, mw(te, toff + 32));

			invalidate_dest(reg0);
			invalidate_dest(extra_reg);
			invalidate_dest(to);

			end_contop();
			contop_level--;
			end_contop();
			son(fe) = holdfe;
			son(te) = holdte;
			return;
		}

		move(sha, from, flstack);
		move(sha, flstack, to);
		son(fe) = holdfe;
		son(te) = holdte;
		return;
	}

	if (sz <= (40 * 8) && two_contops(fe, te)) {
		int i;
		int foff = from.where_off;
		int toff = to.where_off;
		int old_regsinuse = regsinuse;

		contop(fe, 1, to);
		regsinuse = top_regsinuse;
		contop_level++;
		reg0_in_use = 1;
		contop(te, 1, to);
		regsinuse = old_regsinuse;

		/* use movl as far as possible */
		for (i = 0; i <= (sz - 32); i = i + 32) {
			ins2(movl, size32, size32, mw(fe, foff + i), reg0);
			ins2(movl, size32, size32, reg0, mw(te, toff + i));
			invalidate_dest(mw(te, toff + i));
		}

		if (i == sz) {
			invalidate_dest(reg0);
			end_contop();
			contop_level--;
			end_contop();
			son(fe) = holdfe;
			son(te) = holdte;
			return;
		}

		/* move final word and byte if necessary */
		if ((sz - i) >= 16) {
			ins2(movw, size16, size16, mw(fe, foff + i), reg0);
			ins2(movw, size16, size16, reg0, mw(te, toff + i));
			invalidate_dest(mw(te, toff + i));
			i += 16;
		}

		if ((sz - i) >= 8) {
			ins2(movb, size8, size8, mw(fe, foff + i), reg0);
			ins2(movb, size8, size8, reg0, mw(te, toff + i));
			invalidate_dest(mw(te, toff + i));
		}

		invalidate_dest(reg0);
		end_contop();
		contop_level--;
		end_contop();
		son(fe) = holdfe;
		son(te) = holdte;
		return;
	}

	if (sha->tag == realhd) {
		move(sha, from, flstack);
		move(sha, flstack, to);
		son(fe) = holdfe;
		son(te) = holdte;
		return;
	}

	{
		/* use rep movsl to do the move */
		int old_extra_stack = extra_stack;
		int old_regsinuse;

		if (regsinuse & 0x20) {
			extra_stack += 32;
			ins0(pushesi);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_push();
			}
#endif
		}

		if (regsinuse & 0x10) {
			extra_stack += 32;
			ins0(pushedi);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_push();
			}
#endif
		}

		if (regsinuse & 0x4) {
			extra_stack += 32;
			ins0(pushecx);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_push();
			}
#endif
		}

		old_regsinuse = regsinuse;
		if (regsinuse & 0x20) {
			mova(from, pushdest);
			extra_stack += 32;
		} else {
			mova(from, reg5);
			regsinuse |= 0x20;
		}

		mova(to, reg4);
		regsinuse = old_regsinuse;

		move(slongsh, mw(zeroe, (sz / 32)), reg2);

		if (regsinuse & 0x20) {
			ins0(popesi);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_pop();
			}
#endif
		}

		ins0(rep);
		ins0(movsl);

		/* and move the last word and byte if necessary */
		sz = sz % 32;
		if (sz >= 16) {
			ins0(movsw);
			sz -= 16;
		}
		if (sz == 8) {
			ins0(movsb);
		}

		invalidate_dest(reg2);
		invalidate_dest(reg4);
		invalidate_dest(reg5);

		if (regsinuse & 0x4) {
			ins0(popecx);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_pop();
			}
#endif
		}
		if (regsinuse & 0x10) {
			ins0(popedi);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_pop();
			}
#endif
		}
		if (regsinuse & 0x20) {
			ins0(popesi);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_pop();
			}
#endif
		}

		check_stack_max;
		extra_stack = old_extra_stack;
		min_rfree |= 0x30;
		invalidate_dest(to);
		son(fe) = holdfe;
		son(te) = holdte;
		return;
	}
}

/*
 * Use rep movsb
 */
void
movecont(where from, where to, where length, int nooverlap)
{
	if (nooverlap) {
		int old_extra_stack = extra_stack;

		if (regsinuse & 0x20) {
			extra_stack += 32;
			ins0(pushesi);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_push();
			}
#endif
		}
		if (regsinuse & 0x10) {
			extra_stack += 32;
			ins0(pushedi);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_push();
			}
#endif
		}

		ins0(pushecx);
#ifdef DWARF2
		if (diag == DIAG_DWARF2 && no_frame) {
			dw2_track_push();
		}
#endif

		extra_stack += 32;
		move(sh(from.where_exp), from, pushdest);
		extra_stack += 32;
		move(sh(to.where_exp), to, pushdest);
		extra_stack += 32;
		move(sh(length.where_exp), length, pushdest);
		ins0(popecx);

#ifdef DWARF2
		if (diag == DIAG_DWARF2 && no_frame) {
			dw2_track_pop();
		}
#endif
		ins0(popedi);
#ifdef DWARF2
		if (diag == DIAG_DWARF2 && no_frame) {
			dw2_track_pop();
		}
#endif
		ins0(popesi);
#ifdef DWARF2
		if (diag == DIAG_DWARF2 && no_frame) {
			dw2_track_pop();
		}
#endif

		move(slongsh, reg2, reg0);
		ins2(sarl, size8, size32, mw(zeroe, 2), reg2);
		ins0(rep);
		ins0(movsl);
		move(slongsh, reg0, reg2);
		ins2(andl, size32, size32, mw(zeroe, 3), reg2);
		ins0(rep);
		ins0(movsb);
		ins0(popecx);

#ifdef DWARF2
		if (diag == DIAG_DWARF2 && no_frame) {
			dw2_track_pop();
		}
#endif
		if (regsinuse & 0x10) {
			ins0(popedi);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_pop();
			}
#endif
		}

		if (regsinuse & 0x20) {
			ins0(popesi);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_pop();
			}
#endif
		}

		check_stack_max;
		extra_stack = old_extra_stack;
		min_rfree |= 0x30;
		invalidate_dest(reg0);
		invalidate_dest(reg2);
		invalidate_dest(to);
	} else {
		move(sh(length.where_exp), length, pushdest);
		extra_stack += 32;
		move(sh(from.where_exp), from, pushdest);
		extra_stack += 32;
		move(sh(to.where_exp), to, pushdest);

		if (name_memmove == NULL) {
			name_memmove = make_extn("memmove", f_proc, 0);
		}

		callins (0, name_memmove, stack_dec);	/* call_libfn("memmove"); */
		extra_stack -= 64;
		add(slongsh, mw(zeroe, 12), sp, sp);
		invalidate_dest(reg0);
		invalidate_dest(reg1);
		invalidate_dest(reg2);
	}
}

/* move address of from to to */
void
mova(where from, where to)
{
	exp fe = from.where_exp;
	exp holdfe = son(fe);

	cond1_set = false;
	cond2_set = false;

	if (fe->tag == reff_tag && son (fe)->tag != ident_tag) {/* add on offset from reff */
		mova(mw(son(fe), from.where_off + no(fe)), to);
		return;
	}

	if (to.where_exp->tag == apply_tag) {	/* pushing */
		if (!PIC_code && fe->tag == cont_tag &&
		    son(fe)->tag != ident_tag &&
		    (son(fe)->tag != name_tag || !isvar(son(son(fe)))) &&
		    ((extra_stack == 0 && from.where_off == 0) ||
		     !eq_where(mw(son(fe), 0), sp))) {
			contop(fe, 0, to);
			ins1lit(pushl,  32, mw(son(fe), from.where_off));

#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_push();
			}
#endif

			end_contop();
			son(fe) = holdfe;
			return;
		}

		if (!PIC_code && fe->tag == name_tag &&
		    isglob(son(fe)) && isvar(son(fe))) {
			contop(fe, 0, to);
			ins1lit(pushl,  32, from);

#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_push();
			}
#endif

			end_contop();
			son(fe) = holdfe;
			return;
		}

		mova(from, reg0);
		ins1(pushl,  32, reg0);
#ifdef DWARF2
		if (diag == DIAG_DWARF2 && no_frame) {
			dw2_track_push();
		}
#endif
		return;
	}

	if (inmem(to)) {
		mova(from, reg0);
		move(slongsh, reg0, to);
		return;
	}

	if (!PIC_code && fe->tag == name_tag && isvar(son(fe)) &&
	    isglob(son(fe))) {
		move(slongsh, from, to);
		return;
	}

	contop(from.where_exp, 0, to);

	if (fe->tag == name_tag && !isvar(son(fe)) && ptno(son(fe)) == reg_pl) {
		add(slongsh, mw(fe, 0), mw(zeroe, from.where_off / 8), to);
	} else {
		ins2(leal,  32,  32, from, to);
	}

	invalidate_dest(to);
	end_contop();
	son(fe) = holdfe;
}

