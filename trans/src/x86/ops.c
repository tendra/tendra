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

#define PREFETCH_COUNT 1000

static where SPILLREG;	/* no init needed */
static int SPILLMASK;	/* no init needed */

int cmp_64hilab = -1;	/* >=0 iff label required by cmp */

where cond1, cond2a, cond2b;	/* no init needed */
bool cond1_set = false; /* init by cproc */
bool cond2_set = false; /* init by cproc */
int fstack_pos;			/* init by cproc */
int  top_regsinuse;		/* no init needed */
exp overflow_e = NULL;	/* no init needed */
int ferrsize;			/* init by cproc */
int fpucon;			/* init by cproc */

/* initialised by initzeros */
exp zeroe;			/* constant exps and wheres */
exp fzeroe;
exp fonee;
static exp flongmaxe;
exp dlongmaxe;
static exp dllmaxe;
static exp dzeroe;
static exp donee;
where zero;
where fzero;
static where fone;
where dzero;
static where done;
exp smaxe;
exp sllmaxe;

static exp dummys;
static exp dummyu;
static exp reg0id;
static exp reg0charid;
static exp reg0uid;
static exp reg1id;
static exp reg2id;
static exp reg3id;
static exp reg4id;
static exp reg5id;
static exp reg6id;
static exp spid;
static exp bpid;
static exp pushid;
static exp flstackid;
static exp stack0ref;
where reg0;
static where reg0char;
static where reg0u;
where reg1;
where reg2;
where reg3;
where reg4;
where reg5;
where reg6;
where sp;
where bp;
where ind_sp;
where ind_reg0;
where ind_reg1;
where ind_reg2;
static where ind_reg4;
where pushdest;
where flstack;
static where stack0;

static exp firstlocalid;
where firstlocal;

static exp ferrmemid;
exp ferrmem;

where reg_wheres[7];
/* end of values inited by initzeros */

int contop_level = 0; /* initial value for pushing must be 0 */
int reg0_in_use  = 0; /* initial value for pushing must be 0 */
int contop_dopop = 0; /* initial value for pushing must be 0 */

char maxdigs[]  = "4294967296";
char smaxdigs[] = "2147483648";

void
test_exception(int test_no, shape sha)
{
	if (overflow_e != NULL) {
		exp oe = overflow_e;

		if (isov(overflow_e)) {
			exp jd = pt(son(pt(overflow_e)));
			overflow_e = NULL;
			branch(test_no, jd, is_signed(sha), sha->tag);
		} else if (istrap(overflow_e)) {
			overflow_e = NULL;
			test_trap(test_no, is_signed(sha), sha->tag);
		}

		overflow_e = oe;
	}
}

static void
do_exception(void)
{
	if (overflow_e != NULL) {
		exp oe = overflow_e;

		if (isov(overflow_e)) {
			exp jd = pt(son(pt(overflow_e)));
			overflow_e = NULL;
			jump(jd, 0);
		} else if (istrap(overflow_e)) {
			overflow_e = NULL;
			trap_ins(f_overflow);
		}

		overflow_e = oe;
	}
}

static void
cmp64_contop(int d)
{
	if (d && contop_dopop) {
		int lolab = next_lab();
		simple_branch(je, lolab);

		if (contop_dopop == 1) {
			ins1(popl, size32, SPILLREG);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_pop();
			}
#endif
		} else {
			exp ap = getexp(f_bottom, NULL, 0, sp.where_exp,
			                NULL, 0, 4, reff_tag);
			ins2(leal, size32, size32, mw(ap, 0), sp);
		}

		simple_branch(jmp, cmp_64hilab);
		simplest_set_lab(lolab);
	} else {
		simple_branch(jne, cmp_64hilab);
	}
}

void
end_contop(void)
{
	if (contop_level == 0) {
		reg0_in_use = 0;
	}

	if (contop_dopop) {
		if (contop_dopop == 1) {
			ins1(popl, size32, SPILLREG);
#ifdef DWARF2
			if (diag == DIAG_DWARF2 && no_frame) {
				dw2_track_pop();
			}
#endif
		} else {
			exp ap = getexp(f_bottom, NULL, 0, sp.where_exp,
			                NULL, 0, 4, reff_tag);
			ins2(leal, size32, size32, mw(ap, 0), sp);
		}

		invalidate_dest(SPILLREG);
		contop_dopop = 0;
		extra_stack -= 32;
		min_rfree |= SPILLMASK;
	}
}

/*
 * If a in cont or ass of an identified object, load the address
 */
void
contop(exp a, int r0inuse, where dest)
{
	unsigned char n = a->tag;
	int  offset = 0;

	contop_level++;

	if (PIC_code) {
		SPILLREG  = reg4;
		SPILLMASK = 0x10;
	} else {
		SPILLREG  = reg3;
		SPILLMASK = 0x8;
	}

	if ((n == cont_tag || n == ass_tag || n == reff_tag)
	    && son(a)->tag == ident_tag) {
		/* IF 1 */
		ash st;				/* dummy stack for use by make_code */
		exp fin = bro (son (son (a)));	/* fin holds body of final identity */
		unsigned char  oldn = fin->tag;		/* oldn hold name of final identity */
		exp id1 = son (a);			/* outer identity */
		int  inreg1 = ptno(son(son(id1))) == reg_pl;
		/* true if def of outer identity is already in a register */
		int  reg_mask = (~regsinuse) & 0x3e;
		int  regs_free = count_regs(reg_mask);
		/* number of free integer registers */
		exp old_overflow_e;

		st.ashsize  = 0;
		st.ashalign = 0;

		if (r0inuse && contop_level == 1) {
			reg0_in_use |= 1;    /* cannot use reg0 */
		}

		if (oldn == ident_tag) {
			/* IF 2 */
			/* body of id1 is an identity, so TWO identities, so addptr ivolved */
			exp id2 = bro (son (id1));	/* inner identity */
			int  inreg2 = ptno(son(son(id2))) == reg_pl;
			/* true if def of inner identity is already in a register */
			int  regs_good = regs_free + inreg1 + inreg2;
			/* we want two registers but the definitions of id1 and id2 will do */
			fin = bro(son(fin));
			oldn = fin->tag;		/* correct fin and oldn */

			if (regs_good < 2) {
				/* IF 3 */
				/* we have two declarations and need some registers */

				if ((inreg1 + inreg2) == 1 && !reg0_in_use) {
					/* with reg0 we have enough registers */
					if (inreg2) {
						ptno(id1) = reg_pl;
						no (id1) = 1;		/* id1 uses reg0 */
						ptno(id2) = reg_pl;
						no(id2) = no(son(son(id2)));
					} else {
						ptno(id2) = reg_pl;
						no (id2) = 1;		/* id2 uses reg0 */
						ptno(id1) = reg_pl;
						no(id1) = no(son(son(id1)));
					}

					make_code(mw(id1, 0), st, son(id1));
					make_code(mw (id2, 0), st, son (id2)); /* work out defs */
					contop_level--;
					son (a) = fin;		/* code body in caller */
					return;
				}


				if (regs_free == 1 || !reg0_in_use) {
					/* there is one free register, no need to spill */
					where use_reg;		/* holds free register */

					if (regs_free == 1) {
						frr f;
						f = first_reg(reg_mask);
						use_reg = reg_wheres[f.fr_no];	/* free register from mask */
						min_rfree |= reg_mask;	/* mark as used */
					} else {
						use_reg = reg0;    /* reg0 is free */
					}

					if (fin->tag == reff_tag) {	/* remove reff */
						offset = no(fin);
						fin = son(fin);
					}

					old_overflow_e = overflow_e;
					overflow_e = NULL;

					/*
					 * This must be an addptr, note that the calculations
					 * cannot involve the free reg.
					 */
					if (bro(son(fin))->tag == name_tag) {
						/*
						 * The offset is named, so add the pointer to the
						 * offset and put in the free register.
						 */
						add(slongsh, mw(son(id2), 0), mw(son(id1), 0), use_reg);
					} else {
						/*
						 * This is an offset_mult so do the arithmetic of address
						 * calculation and put the address in the free register.
						 */
						exp m = bro(son(fin));
						move(slongsh, mw(son(id1), 0), use_reg);
						mult(slongsh, use_reg, mw(bro(son(m)), 0),
						     use_reg);
						add(slongsh, mw(son(id2), 0), use_reg, use_reg);
					}
					overflow_e = old_overflow_e;

					if (offset != 0) {
						/* put back the reff if there was one */
						exp r = getexp(sh(son(a)), NULL, 0, use_reg.where_exp,
						               NULL, 0, offset, reff_tag);
						son(a) = r;
					} else {
						son(a) = use_reg.where_exp;
					}

					/* The address is in the free register, code the rest in caller */
					contop_level--;
					return;
				}

				/* we are a register short so spill SPILLREG */
				ins1(pushl, size32, SPILLREG);
#ifdef DWARF2
				if (diag == DIAG_DWARF2 && no_frame) {
					dw2_track_push();
				}
#endif
				extra_stack += 32;
				check_stack_max;

				if (fin->tag == reff_tag) {	/* remove reff */
					offset = no(fin);
					fin = son(fin);
				}

				old_overflow_e = overflow_e;
				overflow_e = NULL;

				/* it must be an addptr */
				if (bro(son(fin))->tag == name_tag) {
					/* the offset is named */
					move(slongsh, mw(son(id1), 0), SPILLREG);
					/* put the offset in SPILLREG */

					if (eq_where(SPILLREG, mw(son(id2), 0)))
						/* id2 is the SPILLREG, so add the pushed value */
					{
						add(slongsh, stack0, SPILLREG, SPILLREG);
					} else
						/* otherwise add def of id2 to SPILLREG */
					{
						add(slongsh, mw(son(id2), 0), SPILLREG, SPILLREG);
					}
				} else {
					/* the offset is an offset_mult */
					exp m = bro(son(fin));
					move(slongsh, mw(son(id1), 0), SPILLREG);
					/* number to SPILLREG */
					mult(slongsh, SPILLREG, mw(bro(son(m)), 0), SPILLREG);
					/* multiply by size */
					if (eq_where(SPILLREG, mw(son(id2), 0)))
						/* id2 is the SPILLREG, so add the pushed value */
					{
						add(slongsh, stack0, SPILLREG, SPILLREG);
					} else
						/* otherwise add def of id2 to SPILLREG */
					{
						add(slongsh, mw(son(id2), 0), SPILLREG, SPILLREG);
					}
				}
				overflow_e = old_overflow_e;

				if (offset != 0) {	/* put back the reff if needed */
					exp r = getexp(sh(son(a)), NULL, 0, SPILLREG.where_exp,
					               NULL, 0, offset, reff_tag);
					son(a) = r;
				} else {
					son(a) = SPILLREG.where_exp;
				}
				/* code the rest in the caller */

				contop_level--;

				if (!eq_where(dest, SPILLREG)) {
					contop_dopop = 1;
				}	/* arrange to pop SPILLREG if not equal
				   to dest */
				else {
					contop_dopop = 2;    /* do not pop SPILREG */
				}
				return;
			}

			/* regs_goo >= 2 so we have enough registers */
			fin->tag = top_tag;	/* nullify fin */
			make_code(reg0, st, son (a));	/* code the declarations */
			/* we are coding the identity declaration */
			contop_level--;
			fin->tag = oldn;	/* restore fin */
			son (a) = fin;		/* code the rest in caller */
			return;
		}
		/* end of IF 2 */

		/* one declaration, so simple indirection */
		if (!inreg1 && regs_free == 0) {
			/* we need another register */
			if (reg0_in_use) {
				/* we shall have to spill one */
				ins1 (pushl, size32, SPILLREG);	/* spill SPILLREG */
#ifdef DWARF2
				if (diag == DIAG_DWARF2 && no_frame) {
					dw2_track_push();
				}
#endif
				extra_stack += 32;
				check_stack_max;

				move(slongsh, mw(son(id1), 0), SPILLREG);
				/* put the pointer into SPILLREG */

				ptno(id1) = reg_pl;
				no(id1) = SPILLMASK;	/* set place for identity to SPILLREG */

				son(a) = fin;	/* code the rest in caller */
				contop_level--;
				if (!eq_where(dest, SPILLREG)) {
					contop_dopop = 1;    /* arrange to pop SPILLREG */
				} else {
					contop_dopop = 2;    /* do not pop SPILLREG */
				}
				return;
			}

			/* reg0 is available */
			move(slongsh, mw(son(id1), 0), reg0);
			/* put the pointer into reg0 */

			ptno(id1) = reg_pl;
			no(id1) = 1;	/* set place for identity to reg0 */

			contop_level--;
			son(a) = fin;	/* code the rest in caller */
			return;
		}

		fin->tag = top_tag;	/* nullify fin */
		make_code(reg0, st, son (a));	/* we are coding the identity declaration */
		contop_level--;
		fin->tag = oldn;	/* restore fin */
		son (a) = fin;		/* code the rest in caller */
		return;
	}

	contop_level--;
	top_regsinuse = regsinuse;
}

void
initzeros(void)
{
	/* set up the constants */
	int  flongmax  = new_flpt();
	int  fllmax    = new_flpt();
	int  fslongmax = new_flpt();
	int  fsllmax   = new_flpt();
	int  i;
	flt *flongmaxr  = &flptnos[flongmax];
	flt *fllmaxr    = &flptnos[fllmax];
	flt *fslongmaxr = &flptnos[fslongmax];
	flt *fsllmaxr   = &flptnos[fsllmax];

	flongmaxr->sign  = 1;
	flongmaxr->exp   = 2;
	fllmaxr->sign    = 1;
	fllmaxr->exp     = 4;
	fslongmaxr->sign = 1;
	fslongmaxr->exp  = 1;
	fsllmaxr->sign   = 1;
	fsllmaxr->exp    = 3;

	for (i = 0; i < MANT_SIZE; i++) {
		flongmaxr->mant [i] = (unsigned short) (i == 0 ? 1     : 0);
		fllmaxr->mant   [i] = (unsigned short) (i == 0 ? 1     : 0);
		fslongmaxr->mant[i] = (unsigned short) (i == 0 ? 32768 : 0);
		fsllmaxr->mant  [i] = (unsigned short) (i == 0 ? 32768 : 0);
	}

	zeroe     = getexp(f_bottom, NULL, 0, NULL, NULL, 0, 0, val_tag);
	fzeroe    = getexp(shrealsh, NULL, 0, NULL, NULL, 0, fzero_no, real_tag);
	fonee     = getexp(shrealsh, NULL, 0, NULL, NULL, 0, fone_no, real_tag);
	flongmaxe = getexp(shrealsh, NULL, 0, NULL, NULL, 0, flongmax, real_tag);
	smaxe     = getexp(realsh, NULL, 0, NULL, NULL, 0, fslongmax, real_tag);
	sllmaxe   = getexp(doublesh, NULL, 0, NULL, NULL, 0, fsllmax, real_tag);
	dzeroe    = getexp(realsh, NULL, 0, NULL, NULL, 0, fzero_no, real_tag);
	donee     = getexp(realsh, NULL, 0, NULL, NULL, 0, fone_no, real_tag);
	dlongmaxe = getexp(realsh, NULL, 0, NULL, NULL, 0, flongmax, real_tag);
	dllmaxe   = getexp(doublesh, NULL, 0, NULL, NULL, 0, fllmax, real_tag);
	pushid    = getexp(f_bottom, NULL, 0, NULL, NULL, 0, 0, apply_tag);
	pushdest.where_exp = pushid;
	pushdest.where_off = 0;
	zero.where_exp  = zeroe;
	fzero.where_exp = fzeroe;
	fone.where_exp  = fonee;
	dzero.where_exp = dzeroe;
	done.where_exp  = donee;
	zero.where_off  = 0;
	fzero.where_off = 0;
	fone.where_off  = 0;
	dzero.where_off = 0;
	done.where_off  = 0;

	dummys = getexp(slongsh, NULL, 0, NULL, NULL, 0, 0, val_tag);
	dummyu = getexp(ulongsh, NULL, 0, NULL, NULL, 0, 0, val_tag);

	reg0id = getexp(f_bottom, NULL, 0, dummys, NULL, 0, 0x1, ident_tag);
	ptno(reg0id) = reg_pl;
	reg0 = mw(getexp(slongsh, NULL, 0, reg0id, NULL, 0, 0, name_tag), 0);

	reg0charid = getexp(f_bottom, NULL, 0, dummys, NULL, 0, 0x1, ident_tag);
	ptno(reg0charid) = reg_pl;
	reg0char = mw(getexp(scharsh, NULL, 0, reg0id, NULL, 0, 0, name_tag), 0);

	reg1id = getexp(f_bottom, NULL, 0, dummys, NULL, 0, 0x2, ident_tag);
	ptno(reg1id) = reg_pl;
	reg1 = mw(getexp(slongsh, NULL, 0, reg1id, NULL, 0, 0, name_tag), 0);

	reg2id = getexp(f_bottom, NULL, 0, dummys, NULL, 0, 0x4, ident_tag);
	ptno(reg2id) = reg_pl;
	reg2 = mw(getexp(slongsh, NULL, 0, reg2id, NULL, 0, 0, name_tag), 0);

	reg3id = getexp(f_bottom, NULL, 0, dummys, NULL, 0, 0x8, ident_tag);
	ptno(reg3id) = reg_pl;
	reg3 = mw(getexp(slongsh, NULL, 0, reg3id, NULL, 0, 0, name_tag), 0);


	reg4id = getexp(f_bottom, NULL, 0, dummys, NULL, 0, 0x10, ident_tag);
	ptno(reg4id) = reg_pl;
	reg4 = mw(getexp(slongsh, NULL, 0, reg4id, NULL, 0, 0, name_tag), 0);

	reg5id = getexp(f_bottom, NULL, 0, dummys, NULL, 0, 0x20, ident_tag);
	ptno(reg5id) = reg_pl;
	reg5 = mw(getexp(slongsh, NULL, 0, reg5id, NULL, 0, 0, name_tag), 0);

	reg6id = getexp(f_bottom, NULL, 0, dummys, NULL, 0, 0x40, ident_tag);
	ptno(reg6id) = reg_pl;
	reg6 = mw(getexp(slongsh, NULL, 0, reg6id, NULL, 0, 0, name_tag), 0);

	flstackid = getexp(f_bottom, NULL, 0, dummys, NULL, 0, 0x10000, ident_tag);
	ptno(flstackid) = reg_pl;
	flstack = mw(getexp(realsh, NULL, 0, flstackid, NULL, 0, 0, name_tag), 0);

	reg0uid = getexp(f_bottom, NULL, 0, dummyu, NULL, 0, 0x1, ident_tag);
	ptno(reg0uid) = reg_pl;
	reg0u = mw(getexp(ulongsh, NULL, 0, reg0uid, NULL, 0, 0, name_tag), 0);

	spid = getexp(f_bottom, NULL, 0, dummys, NULL, 0, 128, ident_tag);
	ptno(spid) = reg_pl;
	sp = mw(getexp(slongsh, NULL, 0, spid, NULL, 0, 0, name_tag), 0);

	bpid = getexp(f_bottom, NULL, 0, dummys, NULL, 0, 64, ident_tag);
	ptno(bpid) = reg_pl;
	bp = mw(getexp(slongsh, NULL, 0, bpid, NULL, 0, 0, name_tag), 0);


	stack0ref = getexp(f_top, NULL, 0, sp.where_exp, NULL, 0, -32,
	                   reff_tag);
	stack0 = mw(getexp(f_pointer(f_alignment(slongsh)), NULL, 0,
	                   stack0ref, NULL, 0, 0, cont_tag), 0);

	ind_reg0 = mw(getexp(f_pointer(f_alignment(slongsh)), NULL, 0,
	                     reg0.where_exp, NULL, 0, 0, cont_tag), 0);
	ind_reg1 = mw(getexp(f_pointer(f_alignment(slongsh)), NULL, 0,
	                     reg1.where_exp, NULL, 0, 0, cont_tag), 0);
	ind_reg2 = mw(getexp(f_pointer(f_alignment(slongsh)), NULL, 0,
	                     reg2.where_exp, NULL, 0, 0, cont_tag), 0);
	ind_reg4 = mw(getexp(f_pointer(f_alignment(slongsh)), NULL, 0,
	                     reg4.where_exp, NULL, 0, 0, cont_tag), 0);
	ind_sp = mw(getexp(f_pointer(f_alignment(slongsh)), NULL, 0, sp.where_exp,
	                   NULL, 0, 0, cont_tag), 0);

	firstlocalid = getexp(f_bottom, NULL, 0, dummys, NULL, 0, 0, ident_tag);
	ptno(firstlocalid) = local_pl;
	firstlocal = mw(getexp(slongsh, NULL, 0, firstlocalid, NULL, 0, 0, name_tag), 0);

	reg_wheres[0] = reg0;
	reg_wheres[1] = reg1;
	reg_wheres[2] = reg2;
	reg_wheres[3] = reg3;
	reg_wheres[4] = reg4;
	reg_wheres[5] = reg5;
	reg_wheres[6] = bp;

	ferrmemid = getexp(f_bottom, NULL, 0, NULL, NULL, 0, 0, ident_tag);
	ptno(ferrmemid) = ferr_pl;
	ferrmem = getexp(realsh, NULL, 0, ferrmemid, NULL, 0, 0, name_tag);
}

/*
 * 80386 output routines
 */

/* is w in memory and not a constant */
int
flinmem(where w)
{
	exp e = w.where_exp;
	unsigned char  n = e->tag;
	exp id;
	int recog = 0;

	if (n == ident_tag || n == labst_tag) {
		id = e;
		recog = 1;
	} else {
		if (n == name_tag) {
			id = son(e);
			recog = 1;
		} else {
			if ((n == cont_tag || n == ass_tag) &&
			    son(e)->tag == name_tag && isvar(son(son(e)))) {
				id = son(son(e));
				recog = 1;
			}
		}
	}

#ifdef TDF_DIAG3
	if (n == diagnose_tag) {
		return flinmem(mw(son(e), w.where_off));
	}
#endif

	if (!recog) {
		return 1;
	} else {
		SET(id);
	}

	if (ptno(id) == reg_pl &&
	    (sh (son (id))->tag > ucharhd || no (id) < 0x10)) { /* 0x10 is edi */
		return 0;    /* there are no char versions of edi, esi */
	}

	return 1;
}

/*
 * Is w in memory or an integer or null pointer constant?
 */
int
inmem(where w)
{
	unsigned char  n = w.where_exp->tag;

	if (n == val_tag ||
	    n == null_tag || n == current_env_tag) {
		return 0;
	}

	return flinmem(w);
}

int
w_islastuse(where w)
{
	exp e = w.where_exp;

	if (e->tag == name_tag && !isvar(son(e))) {
		return islastuse(e);
	}

	if (e->tag == cont_tag && son(e)->tag == name_tag &&
	    isvar(son(son(e)))) {
		return islastuse(son(e));
	}

	return 0;
}

/*
 * Compare from with min (from - min) values have shape sha. The testno for
 * which it is being used is supplied so that we can optimise cmp(0, x)
 *
 * Result true (1) if optimised compare with 0 in which case we need
 * to ignore overflow
 */
int
cmp(shape sha, where from, where min, int nt, exp e)
{
	int sz;
	exp cc   = cond1.where_exp;
	exp cc2a = cond2a.where_exp;
	exp me;
	int contop_done = 0;
	where has_equiv_from;
	where has_equiv_min;
	exp hold_from = son(from.where_exp);
	exp hold_min = son(min.where_exp);
	sz = shape_size(sha);

	if (cond1_set &&
	    (eq_where(min, zero) || (min.where_exp->tag == null_tag && no(min.where_exp) == 0)) &&
	    (is_signed(sha) || nt >= 5) &&
	    ((cc->tag == ident_tag && eq_shape(sh(son(cc)), sha)) ||
	     (cc->tag == ass_tag && eq_shape(sh(bro(son(cc))), sha)) ||
	     eq_shape(sh(cc), sha)) &&
	    eq_where(cond1, from) && sz <= 32) {
		return 1;
	}

	/* we are comparing the value from which the conditions are set with zero */
	if (cond2_set &&
	    ((cc2a->tag == ident_tag && eq_shape(sh(son(cc2a)), sha)) ||
	     eq_shape(sh(cc2a), sha)) &&
	    eq_where(cond2a, from) &&
	    eq_where(cond2b, min)) {
		return 0;    /* we are repeating the previous comparison */
	}

	if (!is_floating(sha->tag)) {
		where orig_min;
		orig_min = min;
		has_equiv_from = equiv_reg(from, sz);

		if (has_equiv_from.where_exp != NULL) {
			from = has_equiv_from;
			hold_from = son(from.where_exp);
		}

		has_equiv_min = equiv_reg(min, sz);
		if (has_equiv_min.where_exp != NULL) {
			min = has_equiv_min;
			hold_min = son(min.where_exp);
		}

		if (cond1_set &&
		    (eq_where(min, zero) || (min.where_exp->tag == null_tag && no(min.where_exp) == 0)) &&
		    (is_signed(sha) || nt >= 5) &&
		    ((cc->tag == ident_tag && eq_shape(sh(son(cc)), sha)) ||
		     (cc->tag == ass_tag && eq_shape(sh(bro(son(cc))), sha)) ||
		     eq_shape(sh(cc), sha)) &&
		    eq_where(cond1, from) && sz <= 32) {
			return 1;    /* we are comparing the value from which the conditions are set with zero */
		}

		if (cond2_set &&
		    ((cc2a->tag == ident_tag && eq_shape(sh(son(cc2a)), sha)) ||
		     eq_shape(sh(cc2a), sha)) &&
		    eq_where(cond2a, from) &&
		    eq_where(cond2b, min)) {
			return 0;    /* we are repeating the previous comparison */
		}

		if (((min.where_exp->tag == null_tag && no(min.where_exp) == 0)
		     || eq_where(min, zero)) &&
		    !inmem(from)) {
			/* min is zero */

			cond1_set = true;
			cond2_set = false;
			cond1     = from;

			if (sz == 8) {
				ins2(testb, sz, sz, from, from);
				return 0;
			}
			if (sz == 16) {
				ins2(testw, sz, sz, from, from);
				return 0;
			}
			if (sz == 32) {
				ins2(testl, sz, sz, from, from);
				return 0;
			}
			if (sz == 64) {	/* !inmem, so from must be reg0/reg1 */
				if (nt >= 5) {
					ins2(orl, 32, 32, reg1, reg0);
					invalidate_dest(reg0);
					cond1_set = false;
					return 0;
				} else if (nt == f_less_than || nt == f_greater_than_or_equal) {
					ins2(testl, 32, 32, reg1, reg1);
					cond1_set = false;
					return 0;
				}
			}
		}

		cond1_set = false;
		cond2_set = true;
		cond2a = from;
		cond2b = min;

		if (nt >= 5 &&
		    ((from.where_exp->tag == null_tag && no(from.where_exp) == 0) ||
		     eq_where(from, zero)) &&
		    !inmem(min)) {
			/* from is zero and the test is == or != so we don't have to reverse its sense */

			if (sz == 8) {
				ins2(testb, sz, sz, min, min);
				return 0;
			}
			if (sz == 16) {
				ins2(testw, sz, sz, min, min);
				return 0;
			}
			if (sz == 32) {
				ins2(testl, sz, sz, min, min);
				return 0;
			}
			if (sz == 64) {	/* !inmem, so min must be reg0/reg1 */
				ins2(orl, 32, 32, reg1, reg0);
				invalidate_dest(reg0);
				cond2_set = false;
				return 0;
			}
		}

		if (sz != 16 && sz <= 32 && ((min.where_exp->tag == null_tag ||
		                              min.where_exp->tag == val_tag) &&
		                             no(min.where_exp) == 0) &&
		    inmem(from) && has_equiv_from.where_exp == NULL) {
			{
				move(sha, from, reg0);
				cond1_set = false;
				cond2_set = false;
				IGNORE cmp(sha, reg0, min, nt, e);
			}
			return 0;
		}

		{
			char *in;
			int riu = regsinuse;

			switch (sz) {
			case  8: in = cmpb; break;
			case 16: in = cmpw; break;
			case 32:
			case 64: in = cmpl; break;

			default:
				error(ERR_INTERNAL, "unexpected size");
			}

			if ((inmem(from) && inmem(min)) ||
			    (sha->tag == prokhd && !PIC_code && !eq_where(min, reg0)) ||
			    (from.where_exp->tag == name_tag &&
			     isvar(son(from.where_exp))) ||
			    (from.where_exp->tag == reff_tag &&
			     son(from.where_exp)->tag == name_tag &&
			     !isvar(son(son(from.where_exp)))))
			{
				if ((from.where_exp->tag == name_tag &&
				     ((isvar(son(from.where_exp)) &&
				       ptno(son(from.where_exp)) <= par_pl) ||
				      (PIC_code &&
				       isglob(son(from.where_exp)) &&
				       (sha->tag == prokhd || sha->tag == ptrhd) &&
				       !brog(son(from.where_exp))-> extnamed))) ||
				    from.where_exp->tag == reff_tag)
				{
					mova(from, reg0);
				} else {
					move(sha, from, reg0);
				}

				son(from.where_exp) = hold_from;
				from = reg0;
				hold_from = son(from.where_exp);
			} else {
				if (inmem(from)) {
					if (sz == 64) {
						regsinuse |= 0x2;
					}
					contop(from.where_exp, eq_where(reg0, min), reg0);
					contop_done = 1;
				}
			}

			if ((min.where_exp->tag == val_tag || min.where_exp->tag == env_offset_tag) &&
			    ((from.where_exp->tag == val_tag || from.where_exp->tag == env_offset_tag) ||
			     (keep_short && inmem(from)))) {
				move(sha, from, reg0);
				son(from.where_exp) = hold_from;
				from = reg0;
				hold_from = son(from.where_exp);
			}

			if (eq_where(from, reg0) && eq_where(min, reg0)
			    && !eq_where(orig_min, reg0)) {
				son(min.where_exp) = hold_min;
				min = orig_min;		/* equiv_reg lost due to evaluation of from */
				hold_min = son(min.where_exp);
			}

			me = min.where_exp;
			if ((me->tag == name_tag && isvar(son(me)) &&
			     ptno(son(me)) <= par_pl) ||
			    (PIC_code && me->tag == name_tag && isglob(son(me)) &&
			     (sha->tag == prokhd || sha->tag == ptrhd) &&
			     !brog(son(me))-> extnamed) ||
			    (me->tag == reff_tag && son(me)->tag == name_tag &&
			     !isvar(son(son(me)))))
			{
				if (eq_where(from, reg0)) {
					ins0(pusheax);
#ifdef DWARF2
					if (diag == DIAG_DWARF2 && no_frame) {
						dw2_track_push();
					}
#endif

					extra_stack += 32;
					check_stack_max;
					mova(min, reg0);
					ins2(in, sz, sz, reg0, mw(ind_sp.where_exp, -32));
					invalidate_dest(ind_sp);
					invalidate_dest(reg0);
					ins0(popeax);
#ifdef DWARF2
					if (diag == DIAG_DWARF2 && no_frame) {
						dw2_track_pop();
					}
#endif

					extra_stack -= 32;
					son(from.where_exp) = hold_from;
					son(min.where_exp) = hold_min;
					return 0;
				}

				mova(min, reg0);
				son(min.where_exp) = hold_min;
				min = reg0;
				hold_min = son(min.where_exp);
			} else {
				if (inmem(min)) {
					if (sz == 64) {
						regsinuse |= 0x2;
					}
					contop(min.where_exp, eq_where(reg0, from), reg0);
					contop_done = 1;
				}
			}

			if (sz == 8 && (eq_where(min, reg4) || eq_where(min, reg5))) {
				if (!eq_where(from, reg0)) {
					move(sha, min, reg0);
					son(min.where_exp) = hold_min;
					min = reg0;
					hold_min = son(min.where_exp);
				} else {
					sub(sha, min, reg0, reg0);
					if (contop_done) {
						end_contop();
					}
					son(from.where_exp) = hold_from;
					son(min.where_exp) = hold_min;
					return 0;
				}
			}

			if (sz != 64) {
				ins2 (in, sz, sz, min, from);/* do the comparison */
				if (contop_done) {
					end_contop();
				}
				son(from.where_exp) = hold_from;
				son(min.where_exp) = hold_min;
				return 0;
			}

			{		/* compare 64bit */
				where fromlo, fromhi, minlo, minhi;
				cond2_set = false;

				if (eq_where(from, reg0)) {
					fromlo = reg0;
					fromhi = reg1;
				} else {
					fromlo = from;
					fromhi = mw(from.where_exp, from.where_off + 32);
				}

				if (eq_where(min, reg0)) {
					minlo = reg0;
					minhi = reg1;
				} else if (min.where_exp->tag == val_tag) {
					int c, c1;
					if (!isbigval(min.where_exp)) {
						c = no(min.where_exp);
						c1 = (is_signed(sha) && c < 0) ? -1 : 0;
						if (c == 0 && (nt == f_greater_than_or_equal || nt == f_less_than)) {
							/* sign bit says it all, so ignore fromlo */
							ins2(cmpl, 32, 32, zero, fromhi);
							if (contop_done) {
								end_contop();
							}
							regsinuse = riu;
							son(from.where_exp) = hold_from;
							son(min.where_exp) = hold_min;
							return 0;
						}
					} else {
						flt64 x;
						int ov;
						x = flt_to_f64(no(min.where_exp), is_signed(sha), &ov);
						c = x.small;
						c1 = x.big;
					}
					minlo = mw(zeroe, c);
					minhi = mw(zeroe, c1);
				} else {
					minlo = min;
					minhi = mw(min.where_exp, min.where_off + 32);
				}

				if (nt >= 5 || !is_signed(sha)) {
					int flags_set_lab = next_lab();
					ins2(cmpl, 32, 32, minhi, fromhi);
					simple_branch(jne, flags_set_lab);
					ins2(cmpl, 32, 32, minlo, fromlo);
					simplest_set_lab(flags_set_lab);
					if (contop_done) {
						end_contop();
					}
					regsinuse = riu;
					son(from.where_exp) = hold_from;
					son(min.where_exp) = hold_min;
					return 0;
				}

				cmp_64hilab = next_lab();
				ins2(cmpl, 32, 32, minhi, fromhi);
				cmp64_contop (contop_done);	/* if hi unequal, undo contop and jump to cmp_64hilab */
				ins2(cmpl, 32, 32, minlo, fromlo);

				if (contop_done) {
					end_contop();
				}
				regsinuse = riu;
				son(from.where_exp) = hold_from;
				son(min.where_exp) = hold_min;
				return 0;
			}
		}
	} else {
		cond1_set = false;
		cond2_set = true;
		cond2a    = from;
		cond2b    = min;

		fl_comp (sha, from, min, e);	/* do a floating point comparison */
		son(from.where_exp) = hold_from;
		son(min.where_exp) = hold_min;
		return 0;
	}
}

/*
 * Change variety from (which has shape fsh) to sha, and put in to
 */
void
change_var_sh(shape sha, shape fsh, where from, where to)
{
	exp fe = from.where_exp;
	exp holdfe = son(fe);
	int  szf, /* size of from */
	     szt; /* size of to */
	bool sgf, /* from is signed */
	     sgt; /* to is signed */

	cond1_set = false;
	cond2_set = false; /* see note on move */

	szf = shape_size(fsh);
	sgf = is_signed(fsh);

	/* set szt and sgt */
	switch (sha->tag) {
	case scharhd: szt =  8; sgt = true;  break;
	case ucharhd: szt =  8; sgt = false; break;
	case swordhd: szt = 16; sgt = true;  break;
	case uwordhd: szt = 16; sgt = false; break;
	case slonghd: szt = 32; sgt = true;  break;
	case s64hd:   szt = 64; sgt = true;  break;
	case u64hd:   szt = 64; sgt = false; break;

	case bitfhd:
		szt = 32;
		sgt = is_signed(sha);
		sha = sgt ? slongsh : ulongsh;
		break;

	default:
		szt = 32;
		sgt = false;
		break;
	}

	if (fe->tag == val_tag) {	/* we know the value */
		int val;
		if (!isbigval(fe)) {
			val = dochvar(no(fe), sha);
			if (overflow_e != NULL && (dochvar(no(fe), fsh) != val || (val < 0 &&
			                           ((szt == 32 && (sgt != sgf)) || (szt == 64 && !sgt && sgf))))) {
				do_exception();
			}
			no(fe) = val;
		} else {
			flt64 x;
			int ov;

			x = flt_to_f64(no(fe), sgf, &ov);
			val = dochvar((int)(x.small), sha);
			if (overflow_e != NULL && (
			        (szt == 64 && x.big < 0 && (sgt != sgf)) ||
			        (szt == 32 && ((!(x.small & (1 << 31)) && x.big != 0) ||
			                       ((x.small & (1 << 31)) && x.big != -sgt))) ||
			        (szt < 32))) {
				do_exception();
			}

			if (szt != 64) {
				no(fe) = val;
				clearbigval(fe);
			}
		}

		sh(fe) = sha;
		move(sha, from, to);
		return;
	}

	if (fsh->tag == bitfhd) {
		if (szf < 8) {
			if (sgf && !sgt) {
				and (scharsh, from, mw(zeroe, (1 << szf) - 1), reg0);
				from = reg0;
			}

			szf = 8;
			fsh = (sgf) ? scharsh : ucharsh;
		} else if (szf < 16) {
			if (sgf && !sgt) {
				and (swordsh, from, mw(zeroe, (1 << szf) - 1), reg0);
				from = reg0;
			}

			szf = 16;
			fsh = (sgf) ? swordsh : uwordsh;
		} else if (szf < 32) {
			if (sgf && !sgt) {
				and (slongsh, from, mw(zeroe, (1 << szf) - 1), reg0);
				from = reg0;
			}

			szf = 32;
			fsh = (sgf) ? slongsh : ulongsh;
		}
	}

	if (overflow_e != NULL && (sgt < sgf || (szt - sgt) < (szf - sgf))) {
		int smax = (szt == 64) ? 0x7fffffff : (1 << (szt - 1)) - 1;
		int min = sgt ? (-smax) - 1 : 0;
		int max = sgt ? smax : smax + smax + 1;

		if (inmem(from)) {
			move(fsh, from, reg0);
			from = reg0;
		}

		if (szf == 64) {
			if (szt == 64) {
				IGNORE cmp(slongsh, reg1, zero, f_greater_than_or_equal, NULL);
				test_exception(f_greater_than_or_equal, slongsh);
			} else {
				int lab1;
				IGNORE cmp(slongsh, reg1, zero, f_equal, NULL);

				if (sgf && sgt) {
					int lab2 = next_lab();
					lab1 = next_lab();
					simple_branch(je, lab2);
					IGNORE cmp(slongsh, reg1, mw(zeroe, -1), f_equal, NULL);
					test_exception(f_equal, slongsh);
					IGNORE cmp(ulongsh, from, mw(zeroe, min), f_greater_than_or_equal, NULL);
					test_exception(f_greater_than_or_equal, ulongsh);
					simple_branch(jmp, lab1);
					simplest_set_lab(lab2);
				} else {
					test_exception(f_equal, slongsh);
				}

				if (szt != 32 || sgt) {
					IGNORE cmp(ulongsh, reg0, mw(zeroe, max), f_less_than_or_equal, NULL);
					test_exception(f_less_than_or_equal, ulongsh);
				}

				if (sgf && sgt) {
					simplest_set_lab(lab1);
				}
			}
		} else {
			if (sgf && (!sgt || szt < szf)) {
				IGNORE cmp(fsh, from, mw(zeroe, min), f_greater_than_or_equal, NULL);
				test_exception(f_greater_than_or_equal, fsh);
			}

			if ((szt - sgt) < (szf - sgf)) {
				IGNORE cmp(fsh, from, mw(zeroe, max), f_less_than_or_equal, NULL);
				test_exception(f_less_than_or_equal, fsh);
			}
		}
	}
	if (szf == 8) {
		if (bad_from_reg(from)) {
			move(slongsh, from, reg0);
			from = reg0;
		}
		if (szt == 8) {
			move(sha, from, to);
			return;
		}
		if (szt == 16) {
			if (sgf) {
				if (inmem(to)) {
					contop(fe, eq_where(reg0, from), reg0);
					ins2(movsbw, szf, szt, from, reg0);
					invalidate_dest(reg0);
					end_contop();
					move(sha, reg0, to);
				} else {
					contop(fe, eq_where(reg0, from), to);
					ins2(movsbw, szf, szt, from, to);
					invalidate_dest(to);
					end_contop();
				}

				son(fe) = holdfe;
				return;
			} else {
				if (inmem(to)) {
					contop(fe, eq_where(reg0, from), reg0);
					ins2(movzbw, szf, szt, from, reg0);
					invalidate_dest(reg0);
					end_contop();
					move(sha, reg0, to);
				} else {
					contop(fe, eq_where(reg0, from), to);
					ins2(movzbw, szf, szt, from, to);
					invalidate_dest(to);
					end_contop();
				}

				son(fe) = holdfe;
				return;
			}
		}
		if (szt >= 32) {
			if (sgf) {
				if (inmem(to) || szt == 64) {
					contop(fe, eq_where(reg0, from), reg0);
					ins2(movsbl, szf, 32, from, reg0);
					invalidate_dest(reg0);
					end_contop();
					if (szt == 64) {
						if (sgt) {
							move(slongsh, reg0, reg1);
							ins2(sarl, 8, 32, mw(zeroe, 31), reg1);
						} else {
							move(ulongsh, zero, reg1);
						}
					}
					move(sha, reg0, to);
				} else {
					contop(fe, eq_where(reg0, from), to);
					ins2(movsbl, szf, szt, from, to);
					invalidate_dest(to);
					end_contop();
				}
				son(fe) = holdfe;
				return;
			}

			if (inmem(to) || szt == 64) {
				move(scharsh, from, reg0);
				and (slongsh, reg0, mw(zeroe, 0xff), reg0);
				if (szt == 64) {
					move(ulongsh, zero, reg1);
				}
				move(sha, reg0, to);
			} else {
				if (eq_where(to, reg4) || eq_where(to, reg5) ||
				    eq_where(to, reg6)) {
					contop(fe, eq_where(reg0, from), to);
					ins2(movzbl, szf, szt, from, to);
					invalidate_dest(to);
					end_contop();
				} else {
					move(scharsh, from, to);
					and (slongsh, to, mw(zeroe, 0xff), to);
				}
			}

			son(fe) = holdfe;
			return;
		}
	}
	if (szf == 16) {
		if (szt == 8) {
			if (bad_from_reg(from)) {
				move(slongsh, from, reg0);
				from = reg0;
			}

			if (sgt) {
				if (inmem(to)) {
					move(sh(fe), from, reg0);
					move(sha, reg0, to);
				} else {
					move(sha, from, to);
				}
				son(fe) = holdfe;
				return;
			}
			move(sha, from, to);
			son(fe) = holdfe;
			return;
		}
		if (szt == 16) {
			move(sha, from, to);
			son(fe) = holdfe;
			return;
		}

		if (sgf) {
			if (inmem(to) || szt == 64) {
				contop(fe, eq_where(reg0, from), reg0);
				ins2(movswl, szf, 32, from, reg0);
				invalidate_dest(reg0);
				end_contop();

				if (szt == 64) {
					if (sgt) {
						move(slongsh, reg0, reg1);
						ins2(sarl, 8, 32, mw(zeroe, 31), reg1);
					} else {
						move(ulongsh, zero, reg1);
					}
				}
				move(sha, reg0, to);
			} else {
				contop(fe, eq_where(reg0, from), to);
				ins2(movswl, szf, szt, from, to);
				invalidate_dest(to);
				end_contop();
			}

			son(fe) = holdfe;
			return;
		}

		if (inmem(to) || szt == 64) {
			move(swordsh, from, reg0);
			and (slongsh, reg0, mw(zeroe, 0xffff), reg0);
			if (szt == 64) {
				move(ulongsh, zero, reg1);
			}
			move(sha, reg0, to);
		} else {
			move(swordsh, from, to);
			and (slongsh, to, mw(zeroe, 0xffff), to);
		}

		son(fe) = holdfe;
		return;
	}

	if (szf >= 32) {
		if (szt == 8) {
			if (bad_from_reg(from)) {
				move(slongsh, from, reg0);
				from = reg0;
			}

			if (sgt) {
				if (inmem(from) && inmem(to)) {
					move(sh(fe), from, reg0);
					move(sha, reg0, to);
				} else {
					move(sha, from, to);
				}

				son(fe) = holdfe;
				return;
			}

			move(sha, from, to);
			son(fe) = holdfe;
			return;
		}

		if (szt == 16) {
			if (sgt) {
				if (inmem(to)) {
					move(sha, from, reg0);
					move(sha, reg0, to);
				} else {
					move(sha, from, to);
				}

				son(fe) = holdfe;
				return;
			}

			move(sha, from, to);
			son(fe) = holdfe;
			return;
		}

		if (szt > szf) {
			move(slongsh, from, reg0);
			if (sgf && sgt) {
				move(slongsh, reg0, reg1);
				ins2(sarl, 8, 32, mw(zeroe, 31), reg1);
			} else {
				move(ulongsh, zero, reg1);
			}

			invalidate_dest(reg0);
			from = reg0;
		}

		move(sha, from, to);
		son(fe) = holdfe;
		return;
	}

	if (!sgf) {
		move(sha, from, to);
		son(fe) = holdfe;
		return;
	}

	move(sha, from, to);
	son(fe) = holdfe;
}

/* change variety from to sha, and put in to */
void
change_var(shape sha, where from, where to)
{
	exp fe = from.where_exp;
	shape fsh = sh(fe);
	exp old_overflow_e = overflow_e;
	overflow_e = NULL;
	change_var_sh(sha, fsh, from, to);
	overflow_e = old_overflow_e;
}

/* change variety from to sha, and put in to */
void
change_var_refactor(shape sha, where from, where to)
{
	exp fe = from.where_exp;
	shape fsh = sh(fe);
	change_var_sh(sha, fsh, from, to);
}

/* Use test instruction */
void
test(shape sha, where a, where b)
{
	char *t;
	int  sz;
	exp hold;

	sz = shape_size(sha);

	switch (sz) {
	case  8: t = testb; break;
	case 16: t = testw; break;
	default: t = testl; break;
	}

	cond1_set = false;
	cond2_set = false;

	if (inmem(a) && inmem(b)) {
		hold = son(b.where_exp);
		move(sha, a, reg0);
		contop(b.where_exp, 1, reg0);
		ins2(t, sz, sz, reg0, b);
		end_contop();
		son(b.where_exp) = hold;
		return;
	}

	if (!inmem(b) && a.where_exp->tag != val_tag) {
		hold = son(a.where_exp);
		contop(a.where_exp, (eq_where(reg0, a) || eq_where(reg0, b)), reg0);
		ins2(t, sz, sz, b, a);
		end_contop();
		son(a.where_exp) = hold;
		return;
	}

	hold = son(b.where_exp);
	contop(b.where_exp, (eq_where(reg0, a) || eq_where(reg0, b)), reg0);
	ins2(t, sz, sz, a, b);
	end_contop();
	son(b.where_exp) = hold;
}

/*
 * Builtin functions. All args are operands
 */
void
special_ins(char *name, exp arg, where dest)
{
	UNUSED(dest);

	if (streq(name, "__trans386_special") && arg->tag == val_tag) {
		switch (no(arg)) {
		case 0:
			ins0(fwait);
			return;

		case 1:
			ins0(finit);
			fpucon = 0x37f;
			reset_fpucon();
			return;

		case 2:
			ins0(fclex);
			return;
		}
	}

	error(ERR_INTERNAL, "bad operation");
}

void
start_asm(void)
{
	asm_printf("\n");
	asm_comment("ASM sequence start");
}

void
end_asm(void)
{
	asm_printf("\n");
	asm_comment("ASM sequence ends");
}

void
asm_ins(exp e)
{
	if (son(e)->tag == string_tag) {
		asm_printf("%s", nostr(son(e)));
	} else {
		bool prev_use_bp = must_use_bp;
		must_use_bp = true;	/* scan must ensure !no_frame */
		operand(shape_size(son(e)), mw(son(e), 0), 1, 0);
		must_use_bp = prev_use_bp;
	}
}

