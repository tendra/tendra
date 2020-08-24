/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

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

int first_fl_reg = 8;

static int flpt_test_no[] = {
	0, 0x45, 0x5, 0x5, 0x41, 0x44, 0x44,
	0x41, 0x5, 0x5, 0x45, 0x40, 0x40, 0x4, 0x4
};

/*
 * Floating register for e
 */
int
in_fl_reg(exp e)
{
	unsigned char  ne = e->tag;

	if (ne == name_tag && ptno(child(e)) == reg_pl) {
		int n = no(child(e));
		return n > 0x80 ? n : 0;
	}

	if (ne == cont_tag && child(e)->tag == name_tag &&
	    isvar(child(child(e))) &&
	    ptno(child(child(e))) == reg_pl) {
		int n = no(child(child(e)));
		return n > 0x80 ? n : 0;
	}

	if (ne == ass_tag && child(e)->tag == name_tag &&
	    isvar(child(child(e))) &&
	    ptno(child(child(e))) == reg_pl) {
		int n = no(child(child(e)));
		return n > 0x80 ? n : 0;
	}

	if (ne == ident_tag && ptno(e) == reg_pl) {
		int n = no(e);
		return n > 0x80 ? n : 0;
	}

	return 0;
}

/*
 * Is e in the floating point stack top?
 */
int
in_fstack(exp e)
{
	int f = in_fl_reg(e);
	int fpos = f ? get_reg_no(f) : 0;
	return fpos == fstack_pos;
}

/*
 * Apply floating point operation op between fstack0 and memory.
 * Reverse arguments of operation if rev.
 */
static void
fopm(shape sha, unsigned char op, int rev, where wh)
{
	exp hold = child(wh.where_exp);
	contop(wh.where_exp, 0, reg0);

	/* floats */
	if (sha->tag == shrealhd) {
		switch (op) {
		case fplus_tag:
			ins1(fadds,  32, wh);
			end_contop();
			child(wh.where_exp) = hold;
			return;

		case fminus_tag:
			if (rev) {
				ins1(fsubrs,  32, wh);
			} else {
				ins1(fsubs,  32, wh);
			}
			end_contop();
			child(wh.where_exp) = hold;
			return;

		case fmult_tag:
			ins1(fmuls,  32, wh);
			end_contop();
			child(wh.where_exp) = hold;
			return;

		case fdiv_tag:
			if (rev) {
				ins1(fdivrs,  32, wh);
			} else {
				ins1(fdivs,  32, wh);
			}
			end_contop();
			child(wh.where_exp) = hold;
			return;

		default:
			error(ERR_INTERNAL, "illegal floating point operation");
			end_contop();
			child(wh.where_exp) = hold;
			return;
		}
	}

	/* doubles */
	switch (op) {
	case fplus_tag:
		ins1(faddl,  64, wh);
		end_contop();
		child(wh.where_exp) = hold;
		return;

	case fminus_tag:
		if (rev) {
			ins1(fsubrl,  64, wh);
		} else {
			ins1(fsubl,  64, wh);
		}
		end_contop();
		child(wh.where_exp) = hold;
		return;

	case fmult_tag:
		ins1(fmull,  64, wh);
		end_contop();
		child(wh.where_exp) = hold;
		return;

	case fdiv_tag:
		if (rev) {
			ins1(fdivrl,  64, wh);
		} else {
			ins1(fdivl,  64, wh);
		}
		end_contop();
		child(wh.where_exp) = hold;
		return;

	default:
		error(ERR_INTERNAL, "illegal floating point operation");
		end_contop();
		child(wh.where_exp) = hold;
		return;
	}
}

/*
 * Apply floating point operation op between fstack0 and fstackn.
 * Reverse arguments of operation if rev.
 */
static void
fopr(unsigned char op, int rev, where wh, where d, int and_pop)
{
	switch (op) {
	case fplus_tag:
		if (and_pop) {
			ins2(faddp, 0, 0, wh, d);
			pop_fl;
		} else {
			ins2(fadd, 0, 0, wh, d);
		}
		break;

	case fminus_tag:
		if (rev) {
			if (and_pop) {
				ins2(fsubrp, 0, 0, wh, d);
				pop_fl;
			} else {
				ins2(fsubr, 0, 0, wh, d);
			}
		} else {
			if (and_pop) {
				ins2(fsubp, 0, 0, wh, d);
				pop_fl;
			} else {
				ins2(fsub, 0, 0, wh, d);
			}
		}
		break;

	case fmult_tag:
		if (and_pop) {
			ins2(fmulp, 0, 0, wh, d);
			pop_fl;
		} else {
			ins2(fmul, 0, 0, wh, d);
		}
		break;

	case fdiv_tag:
		if (rev) {
			if (and_pop) {
				ins2 (fdivrp, 0, 0, wh, d); /* (1,arg1-in-st0,arg2,1)->arg2 */
				pop_fl;
			} else {
				ins2 (fdivr, 0, 0, wh, d); /* (1,arg2,arg1-in-st0,0)->st0 */
			}
		} else {
			if (and_pop) {
				ins2 (fdivp, 0, 0, wh, d); /* (0,arg2-in-st0,arg1,1)->arg1 */
				pop_fl;
			} else {
				ins2 (fdiv, 0, 0, wh, d);    /* (0,arg1,arg2-in-st0,0)->st0 */
			}
		}
		break;

	default:
		error(ERR_INTERNAL, "illegal floating point operation");
		break;
	}
}

/*
 * Apply binary floating point operation to arg1 and arg2 and
 * put result into dest
 */
void
fl_binop(unsigned char op, shape sha, where arg1, where arg2, where dest, exp last_arg)
{
	int m1  = flinmem(arg1);
	int m2  = flinmem(arg2);
	int m3  = flinmem(dest);
	int tst = (m1 << 2) + (m2 << 1) + m3;

	if (sha->tag == doublehd && tst > 1) {
		move(sha, arg1, flstack);
		move(sha, arg2, flstack);

		switch (op) {
		case fplus_tag:  ins0("faddp %st,%st(1)"); break;
		case fminus_tag: ins0("fsubp %st,%st(1)"); break;
		case fmult_tag:  ins0("fmulp %st,%st(1)"); break;
		case fdiv_tag:   ins0("fdivp %st,%st(1)"); break;
		}

		pop_fl;
		move(sha, flstack, dest);
		return;
	}

	switch (tst) {
	case 6:
	case 7:
		move(sha, arg2, flstack);
		fopm(sha, op, 0, arg1);

		move(sha, flstack, dest);
		return;

	case 4:
		if (eq_where(arg2, dest)) {
			int fd = in_fl_reg(dest.where_exp);
			if (fd && get_reg_no(fd) == fstack_pos) {
				fopm(sha, op, 0, arg1);

				return;
			}

			move(sha, arg1, flstack);
			fopr (op, 1, flstack, dest, 1); /* 1: fdivrp st,st(2) */

			return;
		}

		FALL_THROUGH;

	case 5:
		if (use_pop(last_arg, arg2.where_exp) == 2) {
			fopm(sha, op, 0, arg1);

			move(sha, flstack, dest);
			return;
		}

		move(sha, arg1, flstack);
		fopr (op, 1, arg2, flstack, 0); /* 2: fdivr st(2),st */

		move(sha, flstack, dest);
		return;

	case 2:
		if (eq_where(arg1, dest)) {
			int  fd = in_fl_reg(dest.where_exp);
			if (fd && get_reg_no(fd) == fstack_pos) {
				fopm(sha, op, 1, arg2);

				return;
			}
			move(sha, arg2, flstack);
			fopr (op, 0, flstack, dest, 1);/* 3: fdivp st,st(2) */

			return;
		}

		FALL_THROUGH;

	case 3:
		if (use_pop(last_arg, arg1.where_exp) == 2) {
			fopm(sha, op, 1, arg2);

			move(sha, flstack, dest);
			return;
		}

		move(sha, arg2, flstack);
		fopr (op, 0, arg1, flstack, 0); /* 4: fdiv st(2),st */

		move(sha, flstack, dest);
		return;

	case 0:
	case 1: {
		int up1, up2;

		up1 = use_pop_ass(last_arg, arg1.where_exp);
		up2 = use_pop_ass(last_arg, arg2.where_exp);

		if (tst == 0) {
			int  fd1 = get_reg_no(in_fl_reg(arg1.where_exp));
			int  fd2 = get_reg_no(in_fl_reg(arg2.where_exp));

			if (up1 == 2 && fd2 != fstack_pos && eq_where(arg2, dest)) {
				fopr(op, 1, flstack, arg2, 1); /* 8: fdivrp st,st(3) */
				return;
			}
			if (up2 == 2 && fd1 != fstack_pos && eq_where(arg1, dest)) {
				fopr(op, 0, flstack, arg1, 1); /* 11:  fdivp st,st(3) */
				return;
			}
		}

		{
			if (up1 == 2) {
				int  fd2;
				fd2 = in_fl_reg(arg2.where_exp);
				if (get_reg_no(fd2) != fstack_pos) {
					if (tst == 0) {
						fopr (op, 1, arg2, flstack, 0); /* 9: fdivr st(1),st */
						move(sha, flstack, dest);
						return;
					} else if (up2 == 1) {
						fopr (op, 1, flstack, arg2, 1); /* 7: divrp st,st(1) */
						move(sha, flstack, dest);
						return;
					}
				}
			}

			if (up2 == 2) {
				int  fd1;
				fd1 = in_fl_reg(arg1.where_exp);
				if (get_reg_no(fd1) != fstack_pos) {
					if (tst == 0) {
						fopr (op, 0, arg1, flstack, 0); /* 10: fdiv st(2), st */
						move(sha, flstack, dest);
						return;
					} else if (up1 == 1) {
						fopr (op, 0, flstack, arg1, 1); /* untested */
						move(sha, flstack, dest);
						return;
					} else {
						fopr(op, 0, arg1, flstack, 0); /* 6: fdiv st(2),st */
						move(sha, flstack, dest);
						return;
					}
				}
			}
		}

		move(sha, arg2, flstack);
		fopr (op, 0, arg1, flstack, 0); /* 5: fdiv st(2),st */

		move(sha, flstack, dest);
		return;
	}
	}
}

/*
 * Apply binary floating point operation to list of arguments arglist and
 * put result into dest
 */
void
fl_multop(unsigned char op, shape sha, exp arglist, where dest)
{
	exp arg1 = arglist;
	exp arg2 = next(arg1);

	if (arg1->last) {
		/* only one arg, so just move to dest */
		move(sha, mw(arg1, 0), dest);
		return;
	}

	if (arg2->last) {
		/* two args */
		fl_binop(op, sha, mw(arg1, 0), mw(arg2, 0), dest, arg2);
		return;
	}

	move(sha, mw(arg1, 0), flstack);

	for (;;) {
		move(sha, mw(arg2, 0), flstack);

		switch (op) {
		case fplus_tag: ins0("faddp %st,%st(1)"); break;
		case fmult_tag: ins0("fmulp %st,%st(1)"); break;

		default:
			error(ERR_INTERNAL, "illegal floating point operation");
			break;
		}

		pop_fl;
		if (arg2->last) {
			break;
		}

		arg2 = next(arg2);
	}

	move(sha, flstack, dest);
}

/*
 * Rounds the value in the top of fl stack and pops it into "to".
 * Rounding according to mode:
 *
 *    0 round to nearest,midway to even:
 *    1 round down:
 *    2 round up:
 *    3 round toward 0
 *    4 is round as state
 *
 * ul is true iff dest is unsigned >= 32
 * sz is 32 unless dest is 64-bit
 */
static void
round_code(int mode, int ul, int sz)
{
	if (mode == 0 || mode == 4) {
		sub(slongsh, mw(zeroe, sz / 8), sp, sp);
		extra_stack += sz;
		check_stack_max;
	} else {
		sub(slongsh, mw(zeroe, (sz + 32) / 8), sp, sp);
		extra_stack += (sz + 32);
		check_stack_max;
		ins1(fstcw, size16, mw(ind_sp.where_exp, (- (sz + 32))));

		if (ul && mode == 3) {	/* round toward zero unsigned */
			int labpos = next_lab();
			int labend = next_lab();
			ins0(ftst);
			ins1(fnstsw, 16, reg0);
			testah(flpt_test_no[f_less_than]);
			move(swordsh, mw(ind_sp.where_exp, (- (sz + 32))), reg0);
			simple_branch(jpe, labpos);
			or (swordsh, mw (zeroe, (mode << 10)), reg0, reg0);  /* neg, round toward zero */
			simple_branch(jmp, labend);
			simplest_set_lab(labpos);
			or (swordsh, mw (zeroe, (1 << 10)), reg0, reg0);  /* pos, round down */
			simplest_set_lab(labend);
		} else {
			move(swordsh, mw(ind_sp.where_exp, (- (sz + 32))), reg0);
			or (swordsh, mw(zeroe, (mode << 10)), reg0, reg0);
		}

		move(swordsh, reg0, mw(ind_sp.where_exp, (- (sz + 16))));
		invalidate_dest(reg0);
		ins1(fldcw, size16, mw(ind_sp.where_exp, (- (sz + 16))));
	}

	if (ul) {
		if (sz == 64) {
			move(doublesh, mw(sllmaxe, 0), flstack);
			ins0("fsubrp %st,%st(1)");
			pop_fl;
		} else {
			ins1(fsubl, size64, mw(smaxe, 0));
		}
	}

	ins0(frndint);
	ins1((sz == 64 ? fistpll : fistpl), sz, mw(ind_sp.where_exp, (-sz)));
	if (mode != 0 && mode != 4) {
		ins1(fldcw, size16, mw(ind_sp.where_exp, (- (sz + 32))));
		add(slongsh, mw(zeroe, 4), sp, sp);
		extra_stack -= 32;
	}

	invalidate_dest(ind_sp);
}

static void
roundit(shape sha, where from, where to, int mode)
{
	shape shfrom = sh(from.where_exp);
	int ul = (sha->tag == ulonghd || sha->tag == u64hd);
	int sz = (shape_size(sha) == 64) ? 64 : 32;

	cond1_set = false;
	cond2_set = false;

	move(shfrom, from, flstack);

	round_code(mode, ul, sz);
	if (ul) {
		xor(ulongsh, mw(ind_sp.where_exp, -32), mw(zeroe, (int)((unsigned int)1 << 31)),
		    mw(ind_sp.where_exp, -32));
	}

	pop_fl;
	if (flinmem(to)) {
		move(sha, mw(ind_sp.where_exp, -sz), reg0);
		invalidate_dest(reg0);
		add(slongsh, mw(zeroe, sz / 8), sp, sp);
		extra_stack -= sz;
		move(sha, reg0, to);
	} else {
		move(sha, mw(ind_sp.where_exp, -sz), to);
		add(slongsh, mw(zeroe, sz / 8), sp, sp);
		extra_stack -= sz;
	}
}

/* Floating point round */
void
frnd0(shape sha, where from, where to)
{
	roundit(sha, from, to, 0);
}

/* Floating point round */
void
frnd1(shape sha, where from, where to)
{
	roundit(sha, from, to, 1);
}

/* Floating point round */
void
frnd2(shape sha, where from, where to)
{
	roundit(sha, from, to, 2);
}

/* Floating point round */
void
frnd3(shape sha, where from, where to)
{
	roundit(sha, from, to, 3);
}

/* Floating point round */
void
frnd4(shape sha, where from, where to)
{
	roundit(sha, from, to, 4);
}

/* Float the integer from, result to */
void
floater(shape sha, where from, where to)
{
	shape shfrom = sh(from.where_exp);
	int  szf;
	int im;
	exp holdfe;
	szf = shape_size(shfrom);
	im = inmem(from);

	if (!im || szf < 32) {
		if (szf < 32) {
			change_var(slongsh, from, reg0);
			ins1(pushl,  32, reg0);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_push();
			}
#endif
			from = ind_sp;
		} else {
			if (szf == 64) {
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
			} else {
				ins1(pushl, szf, from);
#ifdef DWARF2
				if (diag == DIAG_DWARF2 && no_frame) {
					dw2_track_push();
				}
#endif
			}
			from = ind_sp;
		}
	}

	holdfe = child(from.where_exp);
	contop(from.where_exp, 0, reg0);
	ins1((szf == 64 ? fildll : fildl), szf, from);
	if (shfrom->tag == ulonghd || shfrom->tag == u64hd) {
		int  lab = next_lab();
		ins2(cmpl, szf, szf, zero, from);
		simple_branch(jge, lab);
		if (szf == 64) {
			move(doublesh, mw(sllmaxe, 0), flstack);
			ins0("faddp %st,%st(1)");
		} else {
			ins1(faddl, size64, mw(dlongmaxe, 0));
		}
		simple_set_label(lab);
	}
	end_contop();

	if (!im || szf < 32) {
		ins2(addl,  32,  32, mw(zeroe, (szf == 64 ? 8 : 4)), sp);
	}

	push_fl;
	move(sha, flstack, to);
	child(from.where_exp) = holdfe;
}

/*
 * Change floating variety of from to sha, put in to.
 * Shortening change now dealt with by test_fl_ovfl
 */
void
changefl(shape sha, where from, where to)
{
	shape shfrom = sh(from.where_exp);

	if (in_fl_reg (from.where_exp)) {/* from is in a fl reg */
		/* change in case of shortening now dealt with by test_fl_ovfl */
		move (sha, from, to);	/* just move to destination */
		return;
	}

	/* from is not in fl reg */
	move(shfrom, from, flstack);
	move(sha, flstack, to);
}

/* Floating point negate */
void
fl_neg(shape sha, where from, where to)
{
	int  f1 = in_fl_reg(from.where_exp);
	int  f2 = in_fl_reg(to.where_exp);

	if (f1 != 0 && f2 != 0 &&
	    get_reg_no(f1) == fstack_pos &&
	    get_reg_no(f2) == fstack_pos) {
		ins0(fchs);
		return;
	}

	move(sha, from, flstack);
	ins0(fchs);
	move(sha, flstack, to);
}

/* Floating point abs */
void
fl_abs(shape sha, where from, where to)
{
	int  f1 = in_fl_reg(from.where_exp);
	int  f2 = in_fl_reg(to.where_exp);

	if (f1 != 0 && f2 != 0 &&
	    get_reg_no(f1) == fstack_pos &&
	    get_reg_no(f2) == fstack_pos) {
		ins0(fabs);
		return;
	}

	move(sha, from, flstack);
	ins0(fabs);
	move(sha, flstack, to);
}

/*
 * For each of 14 possible comparison operators replace the sahf,
 * j?? as follows:
 *
 *     <   andb $0b00000101,%ah; jpo    !<   andb $0b00000101,%ah; jpe
 *     >   andb $0b01000101,%ah; jz    	!>   andb $0b01000101,%ah; jnz
 *     <=  andb $0b01000001,%ah; jpo    !<=  andb $0b01000001,%ah; jpe
 *     >=  andb $0b00000101,%ah; jz     !>=  andb $0b00000101,%ah; jnz
 *     ==  andb $0b01000100,%ah; jpo    !=   andb $0b01000100,%ah; jpe
 *     <>  andb $0b01000000,%ah; jz     !<>  andb $0b01000000,%ah; jnz
 *     <>= andb $0b00000100,%ah; jz     !<>= andb $0b00000100,%ah; jnz
 */

/* Floating point compare */
void
fl_comp(shape sha, where pos, where neg, exp e)
{
	/* can improve this to use other comparison instructions */
	cond1_set = false;
	cond2_set = false;
	move(sha, neg, flstack);
	move(sha, pos, flstack);
	ins0(fcompp);

	ins1(fnstsw,  16, reg0);

	testah(flpt_test_no[test_number(e)]);

	invalidate_dest(reg0);
	pop_fl;
	pop_fl;
}

static int fp_clear = 0;

void
reset_fpucon(void)
{
	fp_clear = 0;

	if (fpucon == normal_fpucon) {
		return;
	}

	if (fpucon & ~normal_fpucon & (int)0xd) {
		ins0(fclex);
		fp_clear = 1;
	}

	if (ferrsize < 32) {
		ferrsize = 32;
	}

	ins1(fldcw, 16, mw(ferrmem, 0));
	fpucon = normal_fpucon;
}

static void
set_fpucon(int mask, int val)
{
	if ((fpucon & mask) == val) {
		return;
	}

	fpucon = ((~mask & fpucon) | val);
	if (ferrsize < 32) {
		ferrsize = 32;
	}

	move(uwordsh, mw(zeroe, fpucon), mw(ferrmem, 16));
	ins1(fldcw, 16, mw(ferrmem, 16));
}

void
setup_fl_ovfl(exp e)
{
	int traps = 0xd;
	int ival;
	int eprmask = 0x300;

	if (errhandle(e) == 0) {
		if (sh(e)->tag == doublehd) {
			set_fpucon(eprmask, eprmask);
		}
		return;
	}

	if (!fp_clear && !optop(e)) {
		ins0(fclex);
		fp_clear = 1;
	}

	ival = (istrap(e) ? 0 : traps);
	if (sh(e)->tag == doublehd || sh(e)->tag == s64hd || sh(e)->tag == u64hd) {
		set_fpucon((eprmask | traps), (eprmask | ival));
	} else {
		set_fpucon(traps, ival);
	}
}

void
test_fl_ovfl(exp e, where dest)
{
	int r;

	if (errhandle(e) == 0) {
		return;
	}

	r = in_fl_reg(dest.where_exp);
	if (r && (sh(e)->tag == realhd || sh(e)->tag == shrealhd)) {
		/* overflow won't register until stored in memory */
		where m;

		int reqsize = 32 + shape_size(sh(e));
		if (ferrsize < reqsize) {
			ferrsize = reqsize;
		}

		m = mw(ferrmem, 32);
		if (get_reg_no(r) == fstack_pos && !optop(e)) {
			/* avoid move, which pops the stack */
			if (sh(e)->tag == realhd) {
				ins1(fstl, 64, m);
			} else {
				ins1(fsts, 32, m);
			}
		} else {
			move(sh(e), dest, m);
			if (optop(e)) {	/* replace by suitable value */
				move(sh(e), m, dest);
			}
		}
	}

	if (optop(e)) {
		fp_clear = 0;
		return;
	}

	if (isov(e)) {
		if (eq_where(dest, reg0)) {
			ins0(pusheax);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_push();
			}
#endif
		}

		ins1(fstsw,  16, reg0);
		ins2(testb, 8, 8, mw(zeroe, 13), reg0);

		/* Overflow, Zero divide or Invalid  */
		if (eq_where(dest, reg0)) {
			ins0(popeax);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_pop();
			}
#endif
		}

		branch(f_equal, pt(child(pt(e))), 0, scharhd);
		invalidate_dest(reg0);
	}
}

