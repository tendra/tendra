/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * Defines 80386 instructions such as add, sub etc.
 */

#include <string.h>

#include <shared/check.h>
#include <shared/error.h>

#include <local/ash.h>
#include <local/out.h>
#include <local/cpu.h>
#include <local/codermacs.h>

#ifdef DWARF2
#include <local/dw2_config.h>
#endif

#include <reader/exp.h>
#include <reader/basicread.h>
#include <reader/externs.h>

#include <construct/shape.h>
#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/install_fns.h>
#include <construct/flpt.h>
#include <construct/flpttypes.h>
#include <construct/f64.h>
#include <construct/installglob.h>

#include <main/flags.h>
#include <main/print.h>

#include <refactor/refactor.h>

#include <utility/bits.h>

#include "localtypes.h"
#include "make_code.h"
#include "cproc.h"
#include "reg_record.h"
#include "overlap.h"
#include "messages_8.h"
#include "operand.h"
#include "instr.h"
#include "instr386.h"
#include "instrmacs.h"
#include "localexpmacs.h"

#ifdef TDF_DIAG4
#include <diag4/dg_globs.h>
#endif

#ifdef DWARF2
#include <dwarf2/dw2_basic.h>
#include <dwarf2/dw2_lines.h>
#include "dw2_extra.h"
#endif

#define PREFETCH_COUNT 1000

/* All variables initialised */

static where SPILLREG;	/* no init needed */
static int SPILLMASK;	/* no init needed */

int cmp_64hilab = -1;	/* >=0 iff label required by cmp */

where cond1, cond2a, cond2b;	/* no init needed */
int cond1_set = 0;		/* init by cproc */
int cond2_set = 0;		/* init by cproc */
int fstack_pos;			/* init by cproc */
int  top_regsinuse;		/* no init needed */
exp overflow_e = NULL;	/* no init needed */
int ferrsize;			/* init by cproc */
int fpucon;			/* init by cproc */

		/* initialised by initzeros */
exp zeroe;			/* constant exps and wheres */
exp fzeroe;
exp fonee;
exp flongmaxe;
exp dlongmaxe;
exp dllmaxe;
exp dzeroe;
exp donee;
where zero;
where fzero;
where fone;
where dzero;
where done;
exp smaxe;
exp sllmaxe;

exp dummys;
exp dummyu;
exp reg0id;
exp reg0charid;
exp reg0uid;
exp reg1id;
exp reg2id;
exp reg3id;
exp reg4id;
exp reg5id;
exp reg6id;
exp spid;
exp bpid;
exp pushid;
exp flstackid;
exp stack0ref;
where reg0;
where reg0char;
where reg0u;
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
where ind_reg4;
where pushdest;
where flstack;
where stack0;

static exp firstlocalid;
static where firstlocal;

exp ferrmemid;
exp ferrmem;

where reg_wheres[7];
		/* end of values inited by initzeros */

static int   contop_level = 0;	/* initial value for pushing must be 0 */
static int reg0_in_use = 0;	/* initial value for pushing must be 0 */
int contop_dopop = 0;		/* initial value for pushing must be 0 */

static exp name_memmove = NULL;	/* initialised if and when needed */
static exp cont_stacklimit = NULL;	/* initialised if and when needed */
static exp lib64_s_mult = NULL;
static exp lib64_u_mult = NULL;
static exp lib64_div[4];
static exp lib64_rem[4];
static exp lib64_error = NULL;
static int lib64_set = 0;


int first_fl_reg = 8;

char  maxdigs[] = "4294967296";
char  smaxdigs[] = "2147483648";

static int flpt_test_no[] = {0, 0x45, 0x5, 0x5, 0x41, 0x44, 0x44,
			     0x41, 0x5, 0x5, 0x45, 0x40, 0x40, 0x4, 0x4};


static void try_overflow
(shape sha, int inv)
{
  if (overflow_e != NULL) {
    exp oe = overflow_e;
    if (isov(overflow_e)) {
      exp jd = pt(son(pt(overflow_e)));
      overflow_e = NULL;
      jmp_overflow(jd, is_signed(sha), inv);
    }
    else
    if (istrap(overflow_e)) {
      overflow_e = NULL;
      trap_overflow(is_signed(sha), inv);
    }
    overflow_e = oe;
  }
}

static void test_exception
(int test_no, shape sha)
{
  if (overflow_e != NULL) {
    exp oe = overflow_e;
    if (isov(overflow_e)) {
      exp jd = pt(son(pt(overflow_e)));
      overflow_e = NULL;
      branch(test_no, jd, is_signed(sha), name(sha));
    }
    else
    if (istrap(overflow_e)) {
      overflow_e = NULL;
      test_trap(test_no, is_signed(sha), name(sha));
    }
    overflow_e = oe;
  }
}

static void do_exception
(void)
{
  if (overflow_e != NULL) {
    exp oe = overflow_e;
    if (isov(overflow_e)) {
      exp jd = pt(son(pt(overflow_e)));
      overflow_e = NULL;
      jump(jd, 0);
    }
    else
    if (istrap(overflow_e)) {
      overflow_e = NULL;
      trap_ins(f_overflow);
    }
    overflow_e = oe;
  }
}

static int use_pop_ass
(exp n, exp ln)
{
  exp id;
  if (name(ln) == cont_tag)
    ln = son(ln);
  if (name(ln)!= name_tag)
    return 0;
  id = son(ln);
  while (n != id && last(n) &&
	(is_a(name(n)) || name(n) == ident_tag ||
		name(n) == ass_tag))
    n = bro(n);
  if (n == id)
    return get_reg_no(no(id)) - fstack_pos + 2;
  return 0;
}

static int   use_pop
(exp n, exp ln)
{
  exp id;
  if (name(ln) == cont_tag)
    ln = son(ln);
  if (name(ln)!= name_tag)
    return 0;
  id = son(ln);
  while (n != id && last(n))
    n = bro(n);
  if (n == id)
    return get_reg_no(no(id)) - fstack_pos + 2;
  return 0;
}

int  count_regs
(int mask)
{
  return bits_in(mask & 0xf) + bits_in((mask >> 4) & 0x3);
}

static void cmp64_contop
(int d)
{
  if (d && contop_dopop) {
    int lolab = next_lab();
    simple_branch(je, lolab);
    if (contop_dopop == 1)
     {
      ins1(popl, size32, SPILLREG);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_pop();
#endif
     }
    else
     {
	exp ap = getexp(f_bottom, NULL, 0, sp.where_exp,
                          NULL, 0, 4, reff_tag);
        ins2(leal, size32, size32, mw(ap, 0), sp);
     };
    simple_branch(jmp, cmp_64hilab);
    simplest_set_lab(lolab);
  }
  else
    simple_branch(jne, cmp_64hilab);
}

void end_contop
(void)
{
  if (contop_level == 0)
    reg0_in_use = 0;
  if (contop_dopop) {
    if (contop_dopop == 1)
     {
      ins1(popl, size32, SPILLREG);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_pop();
#endif
     }
    else
     {
	exp ap = getexp(f_bottom, NULL, 0, sp.where_exp,
                          NULL, 0, 4, reff_tag);
        ins2(leal, size32, size32, mw(ap, 0), sp);
     };
    invalidate_dest(SPILLREG);
    contop_dopop = 0;
    extra_stack -= 32;
    min_rfree |= SPILLMASK;
  };
}

/*
 * If a in cont or ass of an identified object, load the address
 */
void contop
(exp a, int r0inuse, where dest)
{
  unsigned char  n = name(a);
  int  offset = 0;

  contop_level++;

  if (PIC_code) {
    SPILLREG = reg4;
    SPILLMASK = 0x10;
  }
  else {
    SPILLREG = reg3;
    SPILLMASK = 0x8;
  };

  if ((n == cont_tag || n == ass_tag || n == reff_tag)
      && name(son(a)) == ident_tag) {
		/* IF 1 */
    ash st;				/* dummy stack for use by make_code */
    exp fin = bro (son (son (a)));	/* fin holds body of final identity */
    unsigned char  oldn = name (fin);		/* oldn hold name of final identity */
    exp id1 = son (a);			/* outer identity */
    int  inreg1 = ptno(son(son(id1))) == reg_pl;
					/* true if def of outer identity is already in a register */
    int  reg_mask = (~regsinuse) & 0x3e;
    int  regs_free = count_regs(reg_mask);
					/* number of free integer registers */
    exp old_overflow_e;
    st.ashsize = 0;
    st.ashalign = 0;

    if (r0inuse && contop_level == 1)
      reg0_in_use |= 1;			/* cannot use reg0 */

    if (oldn == ident_tag) {
		/* IF 2 */
	/* body of id1 is an identity, so TWO identities, so addptr ivolved */
      exp id2 = bro (son (id1));	/* inner identity */
      int  inreg2 = ptno(son(son(id2))) == reg_pl;
					/* true if def of inner identity is already in a register */
      int  regs_good = regs_free + inreg1 + inreg2;
					/* we want two registers but the definitions of id1 and id2 will do */
      fin = bro(son(fin));
      oldn = name (fin);		/* correct fin and oldn */

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
	  }
	  else {
	    ptno(id2) = reg_pl;
	    no (id2) = 1;		/* id2 uses reg0 */
	    ptno(id1) = reg_pl;
	    no(id1) = no(son(son(id1)));
	  };

	  make_code(mw(id1, 0), st, son(id1));
	  make_code(mw (id2, 0), st, son (id2)); /* work out defs */
	  contop_level--;
	  son (a) = fin;		/* code body in caller */
	  return;
	};


	if (regs_free == 1 || !reg0_in_use) {
					/* there is one free register, no need to spill */
	  where use_reg;		/* holds free register */

	  if (regs_free == 1) {
	    frr f;
	    f = first_reg(reg_mask);
	    use_reg = reg_wheres[f.fr_no];	/* free register from mask */
	    min_rfree |= reg_mask;	/* mark as used */
	  }
	  else
	    use_reg = reg0;		/* reg0 is free */

	  if (name (fin) == reff_tag) {	/* remove reff */
	    offset = no(fin);
	    fin = son(fin);
	  };
          old_overflow_e = overflow_e;
          overflow_e = NULL;
			/*
			 * This must be an addptr, note that the calculations
			 * cannot involve the free reg.
			 */
	  if (name(bro(son(fin))) == name_tag) {
			/*
			 * The offset is named, so add the pointer to the
			 * offset and put in the free register.
			 */
	    add(slongsh, mw(son(id2), 0), mw(son(id1), 0), use_reg);
	  }
	  else {
			/*
			 * This is an offset_mult so do the arithmetic of address
			 * calculation and put the address in the free register.
			 */
	    exp m = bro(son(fin));
            move(slongsh, mw(son(id1), 0), use_reg);
            mult(slongsh, use_reg, mw(bro(son(m)), 0),
		use_reg);
	    add(slongsh, mw(son(id2), 0), use_reg, use_reg);
	  };
          overflow_e = old_overflow_e;

	  if (offset != 0) {
			/* put back the reff if there was one */
	    exp r = getexp(sh(son(a)), NULL, 0, use_reg.where_exp,
		NULL, 0, offset, reff_tag);
	    son(a) = r;
	  }
	  else
	    son(a) = use_reg.where_exp;
		/* The address is in the free register, code the rest in caller */
	  contop_level--;
	  return;
	};

		/* we are a register short so spill SPILLREG */
	ins1(pushl, size32, SPILLREG);
#ifdef DWARF2
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_push();
#endif
	extra_stack += 32;
	check_stack_max;

	if (name (fin) == reff_tag) {	/* remove reff */
	  offset = no(fin);
	  fin = son(fin);
	};

        old_overflow_e = overflow_e;
        overflow_e = NULL;
		/* it must be an addptr */
	if (name(bro(son(fin))) == name_tag) {
		/* the offset is named */
	  move(slongsh, mw(son(id1), 0), SPILLREG);
			/* put the offset in SPILLREG */

	  if (eq_where(SPILLREG, mw(son(id2), 0)))
			/* id2 is the SPILLREG, so add the pushed value */
	    add(slongsh, stack0, SPILLREG, SPILLREG);
	  else
			/* otherwise add def of id2 to SPILLREG */
	    add(slongsh, mw(son(id2), 0), SPILLREG, SPILLREG);
	}
	else {
		/* the offset is an offset_mult */
	  exp m = bro(son(fin));
	  move(slongsh, mw(son(id1), 0), SPILLREG);
			/* number to SPILLREG */
	  mult(slongsh, SPILLREG, mw(bro(son(m)), 0), SPILLREG);
			/* multiply by size */
	  if (eq_where(SPILLREG, mw(son(id2), 0)))
			/* id2 is the SPILLREG, so add the pushed value */
	    add(slongsh, stack0, SPILLREG, SPILLREG);
	  else
			/* otherwise add def of id2 to SPILLREG */
	    add(slongsh, mw(son(id2), 0), SPILLREG, SPILLREG);
	};
        overflow_e = old_overflow_e;

	if (offset != 0) {	/* put back the reff if needed */
	  exp r = getexp(sh(son(a)), NULL, 0, SPILLREG.where_exp,
	      NULL, 0, offset, reff_tag);
	  son(a) = r;
	}
	else
	  son(a) = SPILLREG.where_exp;
			/* code the rest in the caller */

	contop_level--;

	if (!eq_where(dest, SPILLREG))
	  contop_dopop = 1;	/* arrange to pop SPILLREG if not equal
				   to dest */
	else
	  contop_dopop = 2;	/* do not pop SPILREG */
	return;
      };

		/* regs_goo >= 2 so we have enough registers */
      setname (fin, top_tag);	/* nullify fin */
      make_code(reg0, st, son (a));	/* code the declarations */
      /* we are coding the identity declaration */
      contop_level--;
      setname (fin, oldn);	/* restore fin */
      son (a) = fin;		/* code the rest in caller */
      return;
    };
		/* end of IF 2 */

		/* one declaration, so simple indirection */
    if (!inreg1 && regs_free == 0) {
		/* we need another register */
      if (reg0_in_use) {
		/* we shall have to spill one */
	ins1 (pushl, size32, SPILLREG);	/* spill SPILLREG */
#ifdef DWARF2
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_push();
#endif
	extra_stack += 32;
	check_stack_max;

	move(slongsh, mw(son(id1), 0), SPILLREG);
		/* put the pointer into SPILLREG */

        ptno(id1) = reg_pl;
        no(id1) = SPILLMASK;	/* set place for identity to SPILLREG */

        son(a) = fin;	/* code the rest in caller */
	contop_level--;
	if (!eq_where(dest, SPILLREG))
	  contop_dopop = 1;	/* arrange to pop SPILLREG */
	else
	  contop_dopop = 2;	/* do not pop SPILLREG */
	return;
      };

		/* reg0 is available */
      move(slongsh, mw(son(id1), 0), reg0);
		/* put the pointer into reg0 */

      ptno(id1) = reg_pl;
      no(id1) = 1;	/* set place for identity to reg0 */

      contop_level--;
      son(a) = fin;	/* code the rest in caller */
      return;
    };


    setname (fin, top_tag);	/* nullify fin */
    make_code(reg0, st, son (a));	/* we are coding the identity declaration */
    contop_level--;
    setname (fin, oldn);	/* restore fin */
    son (a) = fin;		/* code the rest in caller */
    return;
  };
  contop_level--;
  top_regsinuse = regsinuse;
}

void initzeros
(void)
{
				/* set up the constants */
  int  flongmax = new_flpt();
  int  fllmax = new_flpt();
  int  fslongmax = new_flpt();
  int  fsllmax = new_flpt();
  int  i;
  flt * flongmaxr = &flptnos[flongmax];
  flt * fllmaxr = &flptnos[fllmax];
  flt * fslongmaxr = &flptnos[fslongmax];
  flt * fsllmaxr = &flptnos[fsllmax];

  flongmaxr -> sign = 1;
  flongmaxr -> exp = 2;
  fllmaxr -> sign = 1;
  fllmaxr -> exp = 4;
  fslongmaxr -> sign = 1;
  fslongmaxr -> exp = 1;
  fsllmaxr -> sign = 1;
  fsllmaxr -> exp = 3;
  for (i = 0; i < MANT_SIZE; i++) {
   (flongmaxr -> mant)[i] = (unsigned short)((i == 0)? 1 : 0);
   (fllmaxr -> mant)[i] = (unsigned short)((i == 0)? 1 : 0);
   (fslongmaxr -> mant)[i] = (unsigned short)((i == 0)? 32768 : 0);
   (fsllmaxr -> mant)[i] = (unsigned short)((i == 0)? 32768 : 0);
  };

  zeroe = getexp(f_bottom, NULL, 0, NULL, NULL, 0, 0, val_tag);
  fzeroe = getexp(shrealsh, NULL, 0, NULL, NULL, 0, fzero_no, real_tag);
  fonee = getexp(shrealsh, NULL, 0, NULL, NULL, 0, fone_no, real_tag);
  flongmaxe = getexp(shrealsh, NULL, 0, NULL, NULL, 0,
      flongmax, real_tag);
  smaxe = getexp(realsh, NULL, 0, NULL, NULL, 0,
      fslongmax, real_tag);
  sllmaxe = getexp(doublesh, NULL, 0, NULL, NULL, 0,
      fsllmax, real_tag);
  dzeroe = getexp(realsh, NULL, 0, NULL, NULL, 0, fzero_no, real_tag);
  donee = getexp(realsh, NULL, 0, NULL, NULL, 0, fone_no, real_tag);
  dlongmaxe = getexp(realsh, NULL, 0, NULL, NULL, 0,
      flongmax, real_tag);
  dllmaxe = getexp(doublesh, NULL, 0, NULL, NULL, 0,
      fllmax, real_tag);
  pushid = getexp(f_bottom, NULL, 0, NULL, NULL, 0, 0, apply_tag);
  pushdest.where_exp = pushid;
  pushdest.where_off = 0;
  zero.where_exp = zeroe;
  fzero.where_exp = fzeroe;
  fone.where_exp = fonee;
  dzero.where_exp = dzeroe;
  done.where_exp = donee;
  zero.where_off = 0;
  fzero.where_off = 0;
  fone.where_off = 0;
  dzero.where_off = 0;
  done.where_off = 0;

  dummys = getexp(slongsh, NULL, 0, NULL, NULL, 0, 0, val_tag);
  dummyu = getexp(ulongsh, NULL, 0, NULL, NULL, 0, 0, val_tag);

  reg0id = getexp(f_bottom, NULL, 0, dummys, NULL, 0,
      0x1, ident_tag);
  ptno(reg0id) = reg_pl;
  reg0 = mw(getexp(slongsh, NULL, 0, reg0id, NULL, 0, 0, name_tag),
      0);

  reg0charid = getexp(f_bottom, NULL, 0, dummys, NULL, 0,
      0x1, ident_tag);
  ptno(reg0charid) = reg_pl;
  reg0char = mw(getexp(scharsh, NULL, 0, reg0id,
	NULL, 0, 0, name_tag),
      0);

  reg1id = getexp(f_bottom, NULL, 0, dummys, NULL, 0,
      0x2, ident_tag);
  ptno(reg1id) = reg_pl;
  reg1 = mw(getexp(slongsh, NULL, 0, reg1id, NULL, 0, 0, name_tag),
      0);

  reg2id = getexp(f_bottom, NULL, 0, dummys, NULL, 0,
      0x4, ident_tag);
  ptno(reg2id) = reg_pl;
  reg2 = mw(getexp(slongsh, NULL, 0, reg2id, NULL, 0, 0, name_tag),
      0);

  reg3id = getexp(f_bottom, NULL, 0, dummys, NULL, 0,
      0x8, ident_tag);
  ptno(reg3id) = reg_pl;
  reg3 = mw(getexp(slongsh, NULL, 0, reg3id, NULL, 0, 0, name_tag),
      0);


  reg4id = getexp(f_bottom, NULL, 0, dummys, NULL, 0,
      0x10, ident_tag);
  ptno(reg4id) = reg_pl;
  reg4 = mw(getexp(slongsh, NULL, 0, reg4id, NULL, 0, 0, name_tag),
      0);

  reg5id = getexp(f_bottom, NULL, 0, dummys, NULL, 0,
      0x20, ident_tag);
  ptno(reg5id) = reg_pl;
  reg5 = mw(getexp(slongsh, NULL, 0, reg5id, NULL, 0, 0, name_tag),
      0);

  reg6id = getexp(f_bottom, NULL, 0, dummys, NULL, 0,
      0x40, ident_tag);
  ptno(reg6id) = reg_pl;
  reg6 = mw(getexp(slongsh, NULL, 0, reg6id, NULL, 0, 0, name_tag),
      0);

  flstackid = getexp(f_bottom, NULL, 0, dummys, NULL, 0,
      0x10000, ident_tag);
  ptno(flstackid) = reg_pl;
  flstack = mw(getexp(realsh, NULL, 0, flstackid, NULL,
	0, 0, name_tag),
      0);

  reg0uid = getexp(f_bottom, NULL, 0, dummyu, NULL, 0,
      0x1, ident_tag);
  ptno(reg0uid) = reg_pl;
  reg0u = mw(getexp(ulongsh, NULL, 0, reg0uid, NULL, 0, 0, name_tag),
      0);

  spid = getexp(f_bottom, NULL, 0, dummys, NULL, 0,
      128, ident_tag);
  ptno(spid) = reg_pl;
  sp = mw(getexp(slongsh, NULL, 0, spid, NULL, 0, 0, name_tag), 0);

  bpid = getexp(f_bottom, NULL, 0, dummys, NULL, 0,
      64, ident_tag);
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
int flinmem
(where w)
{
  exp e = w.where_exp;
  unsigned char  n = name(e);
  exp id;
  int recog = 0;

  if (n == ident_tag || n == labst_tag) {
    id = e;
    recog = 1;
  }
  else {
    if (n == name_tag) {
      id = son(e);
      recog = 1;
    }
    else {
      if ((n == cont_tag || n == ass_tag) &&
	  name(son(e)) == name_tag && isvar(son(son(e)))) {
	id = son(son(e));
	recog = 1;
      }
    };
  };

#ifndef TDF_DIAG4
  if (n == diagnose_tag)
    return flinmem(mw(son(e), w.where_off));
#endif

  if (!recog)
    return 1;
  else {
    SET(id);
  };

  if (ptno(id) == reg_pl &&
      (name (sh (son (id))) > ucharhd || no (id) < 0x10))/* 0x10 is edi */
    return 0;  /* there are no char versions of edi, esi */

  return 1;
}

/*
 * Is w in memory or an integer or null pointer constant?
 */
int inmem
(where w)
{
  unsigned char  n = name(w.where_exp);
  if (n == val_tag ||
	n == null_tag || n == current_env_tag)
    return 0;
  return flinmem(w);
}

int w_islastuse
(where w)
{
  exp e = w.where_exp;
  if (name(e) == name_tag && !isvar(son(e)))
    return islastuse(e);
  if (name(e) == cont_tag && name(son(e)) == name_tag &&
       isvar(son(son(e))))
    return islastuse(son(e));
  return 0;
}

/*
 * abs value a1 of shape sha and put it in dest
 */
void absop
(shape sha, where a1, where dest)
{
  int labno = next_lab();
  where q;
  int sz = shape_size(sha);
  char * op, * ng;

  q = dest;

  switch (sz) {
    case 8:
      op = testb;
      ng = negb;
      break;
    case 16:
      op = testw;
      ng = negw;
      break;
    case 32:
    case 64:
      op = testl;
      ng = negl;
      break;
    default:
      error(ERR_INTERNAL, "unexpected size");
  };

  cond1_set = 0;
  cond2_set = 0;

  if (inmem(dest)) {
    move(sha, a1, reg0);
    q = reg0;
  }
  else
    move(sha, a1, dest);

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
  }
  else {
    ins2(op, sz, sz, q, q);
    simple_branch(jg, labno);
    ins1(ng, sz, q);
    try_overflow(sha, 0);
  }
  invalidate_dest(q);
  simple_set_label(labno);
  move(sha, q, dest);
}

static void maxmin
(shape sha, where a1, where a2, where dest, int ismax)
{
  where tempw;
  int labno = next_lab();
  int lab64;
  int mem1;
  int mem2;
  char *in;
  int sz = shape_size(sha);
  char * op12;
  char * op21;
  int late_contop = 0;

  if (is_signed(sha)) {
    op12 = (ismax) ? jl : jg;
    op21 = (ismax)? jg : jl;
  }
  else {
    op12 = (ismax) ? jb : ja;
    op21 = (ismax)? ja : jb;
  };

  cond1_set = 0;
  cond2_set = 0;

  switch (sz) {
    case 8:
      in = cmpb;
      break;
    case 16:
      in = cmpw;
      break;
    case 32:
      in = cmpl;
      break;
    case 64:
      lab64 = next_lab();
      break;	/* use cmpl instead of in */
    default:
      error(ERR_INTERNAL, "unexpected size");
  };

  if (eq_where(a2, dest)) {
    tempw = a1;
    a1 = a2;
    a2 = tempw;
  };

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
    };
    if (name(a2.where_exp)!= val_tag) {
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
	}
	else {
	  contop(a1.where_exp, eq_where(a2, reg0), dest);
          ins2(in, sz, sz, a1, a2);
	  end_contop();
          simple_branch(op12, labno);
	};
      }
      else {
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
	  }
	  else {
	    contop(a2.where_exp, eq_where(a1, reg0), dest);
            ins2(in, sz, sz, a1, a2);
            simple_branch(op12, labno);
	  };
	  late_contop = contop_dopop;
	  contop_dopop = 0;
	}
	else  {		/* cannot be (sz == 64) */
	  ins2(in, sz, sz, a1, a2);
          simple_branch(op12, labno);
        };
      };
    }
    else {
      if (sz == 64) {
	int c, c1;
	if (!isbigval(a2.where_exp)) {
	  c = no(a2.where_exp) + a2.where_off;
	  c1 = (is_signed(sha) && c < 0)? -1 : 0;
	}
	else {
	  flt64 x;
	  int ov;
	  x = flt_to_f64(no(a2.where_exp), is_signed(sha), &ov);
	  c = x.small;
	  c1 = x.big;
	};
	if (mem1) {
	  contop(a1.where_exp, 0, dest);
	  ins2(cmpl, 32, 32, mw(zeroe, c1), mw(a1.where_exp, a1.where_off + 32));
	  simple_branch(op21, labno);
	  simple_branch(jne, lab64);
	  ins2(cmpl, 32, 32, mw(zeroe, c), a1);
	  simple_branch((ismax ? ja : jb), labno);
	  late_contop = contop_dopop;
	  contop_dopop = 0;
	}
	else {
		/* a1 and dest must be reg0/1 */
	  ins2(cmpl, 32, 32, mw(zeroe, c1), reg1);
	  simple_branch(op21, labno);
	  simple_branch(jne, lab64);
	  ins2(cmpl, 32, 32, mw(zeroe, c), reg0);
	  simple_branch((ismax ? ja : jb), labno);
	};
      }
      else {
	if (mem1) {
	  contop(a1.where_exp, 0, dest);
          ins2(in, sz, sz, a2, a1);
	  end_contop();
	}
	else
          ins2(in, sz, sz, a2, a1);
	simple_branch(op21, labno);
      };
    };
    if (sz == 64)
      simplest_set_lab(lab64);
    move(sha, a2, dest);
    simple_set_label(labno);
    if (late_contop) {
      contop_dopop = late_contop;
      end_contop();
    };
    regsinuse = riu;
    invalidate_dest(dest);
    invalidate_dest(a1);
    invalidate_dest(a2);
    son(a1.where_exp) = hold1;
    son(a2.where_exp) = hold2;
    return;
  };

  if (eq_where(a1, reg0)) {
    reg0_in_use = 1;
    maxmin(sha, reg0, a2, reg0, ismax);
    move(sha, reg0, dest);
    return;
  };

  if (eq_where(a2, reg0)) {
    reg0_in_use = 1;
    maxmin(sha, a1, reg0, reg0, ismax);
    move(sha, reg0, dest);
    return;
  };

  move(sha, a1, reg0);
  maxmin(sha, reg0, a2, dest, ismax);
}


/* max values a1, a2 of shape sha and put them in dest */
void maxop
(shape sha, where a1, where a2, where dest)
{
  maxmin(sha, a1, a2, dest, 1);
}

/* min values a1, a2 of shape sha and put them in dest */
void minop
(shape sha, where a1, where a2, where dest)
{
  maxmin(sha, a1, a2, dest, 0);
}

/* add values a1, a2 of shape sha and put them in dest  */
void add_plus
(shape sha, where a1, where a2, where dest, int plus1)
{
  int  sz;
  exp a = a1.where_exp;
  int  aoff = a1.where_off;
  exp b = a2.where_exp;
  int  boff = a2.where_off;
  sz = shape_size(sha);

  if (name(a) == val_tag && name(sh(a)) == offsethd && al2(sh(a))!= 1) {
    if (name(sha) == offsethd && al2(sha)!= 1)
      no(a) = no(a) / 8;
    sh(a) = slongsh;
  };
  if (name(b) == val_tag && name(sh(b)) == offsethd && al2(sh(b))!= 1) {
    if (name(sha) == offsethd && al2(sha)!= 1)
      no(b) = no(b) / 8;
    sh(b) = slongsh;
  };

  cond1_set = 1;
  cond2_set = 0;

  /* we know the conditions are set according to the which will be in dest */
  cond1 = dest;

  if (eq_where(a1, dest) &&
	(!keep_short || !flinmem(dest))) {	/* altering dest */
    if (name(b) == val_tag && !plus1 && !isbigval(b) && (no(b) + boff == 0 ||
	 ((no(b) + boff == 1 || no(b) + boff == -1) && sz <= 32 &&
	   (overflow_e == NULL || is_signed(sha))))) {
      exp hold = son(a);
      if (no (b) + boff == 0) {	/* adding zero */
	cond1_set = 0;		/* we didn't know conditions after all */
	return;
      };
      contop (a, 0, a1);	/* get the address of a if necessary */
      if (no (b) + boff == 1) {	/* use inc */
	if (sz == 8) {
	  ins1(incb, sz, a1);
	};
	if (sz == 16) {
	  ins1(incw, sz, a1);
	};
	if (sz == 32) {
	  ins1(incl, sz, a1);
	};
      }
      else {			/* use dec */
	if (sz == 8) {
	  ins1(decb, sz, a1);
	};
	if (sz == 16) {
	  ins1(decw, sz, a1);
	};
	if (sz == 32) {
	  ins1(decl, sz, a1);
	};
      };
      invalidate_dest(dest);
      end_contop();
      try_overflow(sha, plus1);
      son(a) = hold;
      return;
    };

    if (!inmem(a1) || !inmem(a2)) {
      /* either a1 or a2 is not in memory */
      int riu = regsinuse;
      exp holda = son(a);
      exp holdb = son(b);
      if (sz == 64)
	regsinuse |= 0x2;
      if (inmem(a1))
	contop(a, eq_where(reg0, a2), a1);
      else
	contop(b,
	    (eq_where(reg0, a2) || eq_where(reg0, a1)), a1);
      if (plus1)
	ins0(stc);
      if (sz == 8) {
	ins2((plus1 ? adcb : addb), sz, sz, a2, a1);
      };
      if (sz == 16) {
	ins2((plus1 ? adcw : addw), sz, sz, a2, a1);
      };
      if (sz == 32) {
	ins2((plus1 ? adcl : addl), sz, sz, a2, a1);
      };
      if (sz == 64) {
	where hi1, lo1, hi2, lo2;
	lo1 = a1;
	hi1 = (inmem(a1)? mw(a, aoff + 32): reg1);
	if (name(b) == val_tag) {
	  int c, c1;
	  if (!isbigval(b)) {
	    c = no(b) + boff;
	    c1 = (is_signed(sha) && c < 0)? -1 : 0;
	  }
	  else {
	    flt64 x;
	    int ov;
	    x = flt_to_f64(no(b), is_signed(sha), &ov);
	    c = x.small;
	    c1 = x.big;
	  };
	  lo2 = mw(zeroe, c);
	  hi2 = mw(zeroe, c1);
	}
	else {
	  lo2 = a2;
	  hi2 = (inmem(a2)? mw(b, boff + 32): reg1);
	}
	ins2((plus1 ? adcl : addl), 32, 32, lo2, lo1);
	ins2(adcl, 32, 32, hi2, hi1);
      };
      invalidate_dest(dest);
      end_contop();
      regsinuse = riu;
      try_overflow(sha, plus1);
      son(a) = holda;
      son(b) = holdb;
      return;
    };

    move(sha, a2, reg0);
    add_plus(sha, reg0, a1, a1, plus1);
    invalidate_dest(dest);
    return;
  };

  if (eq_where(a2, dest) &&
	(!keep_short || !flinmem(dest))) {	/* altering dest */
    if (name(a) == val_tag && !plus1 && !isbigval(a) && (no(a) + aoff == 0 ||
	 ((no(a) + aoff == 1 || no(a) + aoff == -1) && sz <= 32 &&
	   (overflow_e == NULL || is_signed(sha))))) {
      exp hold = son(a);
      if (no (a) + aoff == 0) {	/* adding zero */
	cond1_set = 0;		/* we didn't know conditions after all */
	return;
      };
      contop(b, 0, a2);
      if (no (a) + aoff == 1) {	/* use inc */
	if (sz == 8) {
	  ins1(incb, sz, a2);
	};
	if (sz == 16) {
	  ins1(incw, sz, a2);
	};
	if (sz == 32) {
	  ins1(incl, sz, a2);
	};
      }
      else {			/* use dec */
	if (sz == 8) {
	  ins1(decb, sz, a2);
	};
	if (sz == 16) {
	  ins1(decw, sz, a2);
	};
	if (sz == 32) {
	  ins1(decl, sz, a2);
	};
      };
      invalidate_dest(dest);
      end_contop();
      try_overflow(sha, plus1);
      son(a) = hold;
      return;
    };

    if (!inmem(a1) || !inmem(a2)) {
      /* either a1 or a2 is not in memory */
      int riu = regsinuse;
      exp holda = son(a);
      exp holdb = son(b);
      if (sz == 64)
	regsinuse |= 0x2;
      if (inmem(a1))
	contop(a, eq_where(reg0, a2), a2);
      else
	contop(b,
	    (eq_where(reg0, a2) || eq_where(reg0, a1)), a2);
      if (plus1)
	ins0(stc);
      if (sz == 8) {
	ins2((plus1 ? adcb : addb), sz, sz, a1, a2);
      };
      if (sz == 16) {
	ins2((plus1 ? adcw : addw), sz, sz, a1, a2);
      };
      if (sz == 32) {
	ins2((plus1 ? adcl : addl), sz, sz, a1, a2);
      };
      if (sz == 64) {
	where hi1, lo1, hi2, lo2;
	lo2 = a2;
	hi2 = (inmem(a2)? mw(b, a2.where_off + 32): reg1);
	if (name(a) == val_tag) {
	  int c, c1;
	  if (!isbigval(a)) {
	    c = no(a) + aoff;
	    c1 = (is_signed(sha) && c < 0)? -1 : 0;
	  }
	  else {
	    flt64 x;
	    int ov;
	    x = flt_to_f64(no(a), is_signed(sha), &ov);
	    c = x.small;
	    c1 = x.big;
	  };
	  lo1 = mw(zeroe, c);
	  hi1 = mw(zeroe, c1);
	}
	else {
	  lo1 = a1;
	  hi1 = (inmem(a1)? mw(a, aoff + 32): reg1);
	}
	ins2((plus1 ? adcl : addl), 32, 32, lo1, lo2);
 	ins2(adcl, 32, 32, hi1, hi2);
      };
      invalidate_dest(dest);
      try_overflow(sha, plus1);
      end_contop();
      regsinuse = riu;
      son(a) = holda;
      son(b) = holdb;
      return;
    };

    move(sha, a1, reg0);
    add_plus(sha, reg0, a2, a2, plus1);
    invalidate_dest(dest);
    return;
  };

  if (name(a) == val_tag && !plus1 && !isbigval(a) && no(a) + aoff == 0) {
    /* adding zero and moving */
    cond1_set = 0;
    move(sha, a2, dest);
    return;
  };

  if (name(b) == val_tag && !plus1 && !isbigval(b) && no(b) + boff == 0) {
    /* adding zero and moving */
    cond1_set = 0;
    move(sha, a1, dest);
    return;
  };

  /* switch on memory position of a1, a2, dest */
  switch ((inmem(a1) << 2) + (inmem(a2) << 1) + inmem(dest)) {
    case 0:
      {				/* none in memory */
	exp ap;
        int n;
        if (overflow_e != NULL || sz > 32)
          {
            move(sha, a2, dest);
            add_plus(sha, a1, dest, dest, plus1);
            return;
          };
	/* otherwise cannot be plus1 */
	if (name(a) == val_tag) {
	  if (name (b) == val_tag) {/* we know the answer */
	    cond1_set = 0;
	    move(sha, mw(zeroe,
		    no(a) + no(b) + a1.where_off + a2.where_off),
		    dest);
	    return;
	  };
          if (name(sh(a)) == offsethd)
            n = 1;
          else
            n = 8;
          if (n == 8 && (no(a) & (int)0xf0000000) == 0) {
	    ap = getexp(f_bottom, NULL, 0, b, NULL, 0,
	       (no(a) + a1.where_off)* n,
	        reff_tag);
	    cond1_set = 0;
	    ins2(leal, 32, 32, mw(ap, 0), dest);
	    retcell(ap);
	    invalidate_dest(dest);
	    return;
          }
          else  {
            move(sha, a2, dest);
            add(sha, a1, dest, dest);
            return;
          };
	};
	if (name(b) == val_tag) {
          if (name(sh(b)) == offsethd)
            n = 1;
          else
            n = 8;
          if (n == 8 && (no(b) & (int)0xf0000000) == 0) {
	    ap = getexp(f_bottom, NULL, 0, a, NULL, 0,
	       (no(b) + a2.where_off)* n,
	        reff_tag);
	    cond1_set = 0;
	    ins2(leal, 32, 32, mw(ap, 0), dest);
	    retcell(ap);
	    invalidate_dest(dest);
	    return;
          }
          else  {
            move(sha, a1, dest);
            add(sha, a2, dest, dest);
            return;
          };
	};
	ap = getexp(f_bottom, NULL, 0, a, NULL, 0, 0,
	      addptr_tag);
	{
	  exp temp = bro(a);
	  bro(a) = b;
	  cond1_set = 0;
	  ins2(leal, 32, 32, mw(ap, 0), dest);
	  retcell(ap);
          invalidate_dest(dest);
	  bro(a) = temp;
          return;
	}
      };
    case 1:
    case 3:
    case 5:
    case 7:
      /* dest is in memory */
      add_plus(sha, a1, a2, reg0, plus1);
      move(sha, reg0, dest);
      return;
    case 2: 			/* a2 in memory others not */
      if (eq_where(a1, reg0))
	reg0_in_use = 1;
      move(sha, a2, dest);
      add_plus(sha, a1, dest, dest, plus1);
      invalidate_dest(dest);
      return;
    case 4: 			/* a1 in memory others not */
      if (eq_where(a2, reg0))
	reg0_in_use = 1;
      move(sha, a1, dest);
      add_plus(sha, a2, dest, dest, plus1);
      invalidate_dest(dest);
      return;
    default: 			/* case 6 a1 and a2 in memory, dest not */
      move(sha, a2, reg0);
      add_plus(sha, a1, reg0, reg0, plus1);
      move(sha, reg0, dest);
      return;
  };
}

/* add values a1, a2 of shape sha and put them in dest */
void add
(shape sha, where a1, where a2, where dest)
{
  add_plus(sha, a1, a2, dest, 0);
}

/* negate a1 in sup_dest then add a2 and put in dest */
void inverted_sub
(shape sha, where a1, where a2, where sup_dest, where dest)
{
  if (overflow_e == NULL) {
    negate(sha, a1, sup_dest);
    add_plus(sha, a2, sup_dest, dest, 0);
  }
  else {
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
void sub
(shape sha, where a1, where a2, where dest)
{
  int  sz;
  exp a = a1.where_exp;
  int  aoff = a1.where_off;
  exp b = a2.where_exp;
  sz = shape_size(sha);

  if (name(a) == val_tag && name(sh(a)) == offsethd && al2(sh(a))!= 1) {
    if (name(sha) == offsethd && al2(sha)!= 1)
      no(a) = no(a) / 8;
    sh(a) = slongsh;
  };
  if (name(b) == val_tag && name(sh(b)) == offsethd && al2(sh(b))!= 1) {
    if (name(sha) == offsethd && al2(sha)!= 1)
      no(b) = no(b) / 8;
    sh(b) = slongsh;
  };

  if (name(sha) & 1) {
    cond1_set = 1;
    cond2_set = 0;
    cond1 = dest;
  }
  else {			/* the conditions are not set correctly if
				   unsigned */
    cond1_set = 0;
    cond2_set = 0;
  };


  if (eq_where(a2, dest) &&
	(!keep_short || !flinmem(dest))) {
    if (name(a) == val_tag && !isbigval(a) && (no(a) + aoff == 0 ||
	 ((no(a) + aoff == 1 || no(a) + aoff == -1) && sz <= 32 &&
	   (overflow_e == NULL || is_signed(sha))))) {
      exp hold = son(b);
      if (no (a) + aoff == 0) {	/* we didn't know the conditions */
	cond1_set = 0;
	return;
      };
      contop(b, 0, a2);
      if (no (a) + aoff == 1) {	/* use dec */
	if (sz == 8) {
	  ins1(decb, sz, a2);
	};
	if (sz == 16) {
	  ins1(decw, sz, a2);
	};
	if (sz == 32) {
	  ins1(decl, sz, a2);
	};
      }
      else {			/* use inc */
	if (sz == 8) {
	  ins1(incb, sz, a2);
	};
	if (sz == 16) {
	  ins1(incw, sz, a2);
	};
	if (sz == 32) {
	  ins1(incl, sz, a2);
	};
      };
      invalidate_dest(dest);
      end_contop();
      try_overflow(sha, 0);
      son(b) = hold;
      return;
    };

    if (!inmem(a1) || !inmem(a2)) {
      int riu = regsinuse;
      exp holda = son(a);
      exp holdb = son(b);
      if (sz == 64)
	regsinuse |= 0x2;
      if (inmem(a1))
	contop(a, eq_where(reg0, a2), a2);
      else
	contop(b,
	    (eq_where(reg0, a2) || eq_where(reg0, a1)), a2);
      if (sz == 8) {
	ins2(subb, sz, sz, a1, a2);
      };
      if (sz == 16) {
	ins2(subw, sz, sz, a1, a2);
      };
      if (sz == 32) {
	ins2(subl, sz, sz, a1, a2);
      };
      if (sz == 64) {
	where hi1, lo1, hi2, lo2;
	lo2 = a2;
	hi2 = (inmem(a2)? mw(b, a2.where_off + 32): reg1);
	if (name(a) == val_tag) {
	  int c, c1;
	  if (!isbigval(a)) {
	    c = no(a) + aoff;
	    c1 = (is_signed(sha) && c < 0)? -1 : 0;
	  }
	  else {
	    flt64 x;
	    int ov;
	    x = flt_to_f64(no(a), is_signed(sha), &ov);
	    c = x.small;
	    c1 = x.big;
	  };
	  lo1 = mw(zeroe, c);
	  hi1 = mw(zeroe, c1);
	}
	else {
	  lo1 = a1;
	  hi1 = (inmem(a1)? mw(a, aoff + 32): reg1);
	}
 	ins2(subl, 32, 32, lo1, lo2);
 	ins2(sbbl, 32, 32, hi1, hi2);
      };
      invalidate_dest(dest);
      end_contop();
      regsinuse = riu;
      try_overflow(sha, 0);
      son(a) = holda;
      son(b) = holdb;
      return;
    };

    move(sha, a1, reg0);
    sub(sha, reg0, dest, dest);
    invalidate_dest(dest);
    return;
  };

  if (name(a) == val_tag && !isbigval(a) && no(a) + aoff == 0) {
    cond1_set = 0;
    move(sha, a2, dest);
    return;
  };

  switch ((inmem(a1) << 2) + (inmem(a2) << 1) + inmem(dest)) {
    case 0:
    case 2: 			/* a2 may be in mem, others not */
      if (!eq_where(a1, dest)) {
	if (eq_where(a1, reg0))
	  reg0_in_use = 1;
	move(sha, a2, dest);
	sub(sha, a1, dest, dest);
	invalidate_dest(dest);
	return;
      };
      if (eq_where(a1, reg0) || eq_where(a2, reg0)) {
	if (eq_where(a2, reg0))
	  reg0_in_use = 1;
	inverted_sub(sha, a1, a2, dest, dest);
	return;
      };
      inverted_sub(sha, a1, a2, reg0, dest);
      return;
    case 4:  			/* a1 in memory others not */
      if (eq_where(dest, reg0)) {
	move(sha, a2, reg0);
	sub(sha, a1, reg0, reg0);
	invalidate_dest(dest);
	return;
      };		/* else drop through */
    case 1:
    case 3:
    case 5:
    case 7: 			/* dest is in memory */
      sub(sha, a1, a2, reg0);
      move(sha, reg0, dest);
      return;
    default: 			/* case 6 a1 and a2 in memory, dest not */
      /* we ought to look to see if dest affects the addressing of a1 or
         a2, and use it if not */
      inverted_sub(sha, a1, a2, reg0, dest);
      return;
  };
}

/*
 * Put a negated into dest, shape sha
 */
void negate
(shape sha, where a, where dest)
{
  int  sz;
  sz = shape_size(sha);

  cond1_set = 1;
  cond2_set = 0;
  cond1 = dest;

  if (!inmem (a) && eq_where (a, dest)) {
    /* negating in situ */
    if (sz == 8) {
      ins1(negb, sz, dest);
      invalidate_dest(dest);
    };
    if (sz == 16) {
      ins1(negw, sz, dest);
      invalidate_dest(dest);
    };
    if (sz == 32) {
      ins1(negl, sz, dest);
      invalidate_dest(dest);
    };
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
    };
    try_overflow(sha, 0);
    return;
  };

  if (!inmem(a) && name(a.where_exp)!= val_tag &&
     (w_islastuse(a) || eq_where(a, reg0))) {
    /* a is a register and no longer needed */
    negate(sha, a, a);
    move(sha, a, dest);
    return;
  };

  if (!inmem (dest)) {		/* dest is a register */
    move(sha, a, dest);
    negate(sha, dest, dest);
    invalidate_dest(dest);
    return;
  };

  /* dest is in memory, a is either in memory or needed, it won't be reg0 */
  move(sha, a, reg0);
  negate(sha, reg0, reg0);
  move(sha, reg0, dest);
}

/* put not(a) into dest, shape sha */
void not
(shape sha, where a, where dest)
{
  int  sz;
  sz = shape_size(sha);

  cond1_set = 0;
  cond2_set = 0;

  if (!inmem (a) && eq_where (a, dest)) {
    /* inverting in situ */
    if (sz == 8) {
      ins1(notb, sz, dest);
      invalidate_dest(dest);
      return;
    };
    if (sz == 16) {
      ins1(notw, sz, dest);
      invalidate_dest(dest);
      return;
    };
    if (sz == 32) {
      ins1(notl, sz, dest);
      invalidate_dest(dest);
      return;
    };
    if (sz == 64) {
	  /* must be reg0/1 */
      ins1(notl, 32, reg0);
      ins1(notl, 32, reg1);
      invalidate_dest(reg0);
      invalidate_dest(reg1);
      return;
    };
  };

  if (!inmem(a) && name(a.where_exp)!= val_tag &&
     (w_islastuse(a) || eq_where(a, reg0))) {
    not(sha, a, a);
    move(sha, a, dest);
    return;
  };

  if (!inmem (dest)) {
    /* dest is a register */
    move(sha, a, dest);
    not(sha, dest, dest);
    invalidate_dest(dest);
    return;
  };

  /* dest is in memory, a is either in memory or needed, it won't be reg0 */
  move(sha, a, reg0);
  not(sha, reg0, reg0);
  move(sha, reg0, dest);
}

/*
 * Floating register for e
 */
int  in_fl_reg
(exp e)
{
  unsigned char  ne = name(e);
  if (ne == name_tag && ptno(son(e)) == reg_pl) {
    int  n = no(son(e));
    return (n > 0x80)? n : 0;
  };
  if (ne == cont_tag && name(son(e)) == name_tag &&
      isvar(son(son(e))) &&
      ptno(son(son(e))) == reg_pl) {
    int  n = no(son(son(e)));
    return (n > 0x80)? n : 0;
  };
  if (ne == ass_tag && name(son(e)) == name_tag &&
      isvar(son(son(e))) &&
      ptno(son(son(e))) == reg_pl) {
    int  n = no(son(son(e)));
    return (n > 0x80)? n : 0;
  };
  if (ne == ident_tag && ptno(e) == reg_pl) {
    int  n = no(e);
    return (n > 0x80)? n : 0;
  };
  return 0;
}

/*
 * Is e in the floating point stack top?
 */
int in_fstack
(exp e)
{
  int  f = in_fl_reg(e);
  int  fpos = (f)? get_reg_no(f): 0;
  return fpos == fstack_pos;
}

/*
 * Is e in a register?
 */
int  in_reg
(exp e)
{
  unsigned char  ne = name(e);
  if (ne == name_tag && ptno(son(e)) == reg_pl) {
    int  n = no(son(e));
    if (!iscaonly(son(e)) && isvar(son(e)))
      n = (n | (int)0x80000000);
    return n;
  };
  if (ne == cont_tag && name(son(e)) == name_tag &&
      isvar(son(son(e))) &&
      ptno(son(son(e))) == reg_pl) {
    int  n = no(son(son(e)));
    if (!iscaonly(son(son(e))) && isvar(son(son(e))))
      n = (n | (int)0x80000000);
    return n;
  };
  if (ne == ass_tag && name(son(e)) == name_tag &&
      isvar(son(son(e))) &&
      ptno(son(son(e))) == reg_pl) {
    int  n = no(son(son(e)));
    if (!iscaonly(son(son(e))) && isvar(son(son(e))))
      n = (n | (int)0x80000000);
    return n;
  };
  if (ne == ident_tag && ptno(e) == reg_pl) {
    int  n = no(e);
    if (!iscaonly(e) && isvar(e))
      n = (n | (int)0x80000000);
    return n;
  };
  if (ne == current_env_tag)
    return 0x40;
  return 0;
}

static int all_in_regs
(exp e)
{
  exp id1, id2;
  unsigned char  n = name(e);

  if ((n == cont_tag || n == ass_tag || n == reff_tag)
      && name(son(e)) == ident_tag) {
    id1 = son(e);
    if (ptno(son(son(id1)))!= reg_pl)
      return 0;
    id2 = bro(son(id1));
    if (name(id2)!= ident_tag)
      return 1;
    return ptno(son(son(id2))) == reg_pl;
  };

  return 1;
}

int two_contops
(exp fe, exp te)
{
  int   nr = count_regs((~regsinuse) & 0x3e);
  if (nr >= 2)
    return 1;
  if (nr == 1)
    return all_in_regs(fe) || all_in_regs(te);
  return all_in_regs(fe) && all_in_regs(te);
}

/*
 * Move value of shape sha from "from" to "to"
 */
void move
(shape sha, where from, where to)
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

  if (sz == 0 || eq_where(from, to))
    return;

  /* move does not set conditions. Only clear if to spoils cond record */
  if ((cond1_set && (eq_where(to, cond1) ||
	  invalidates(to.where_exp, cond1.where_exp))) ||
     (cond2_set &&
	(eq_where(to, cond2a) || eq_where(to, cond2b) ||
	  invalidates(to.where_exp, cond2a.where_exp) ||
	  invalidates(to.where_exp, cond2b.where_exp)))) {
    cond1_set = 0;
    cond2_set = 0;
  };

  if (name(fe) == reff_tag ||
	(PIC_code && name(fe) == name_tag &&
	  isglob(son(fe)) &&
	 (name(sha) == offsethd) &&
	  !brog(son(fe)) ->  extnamed))
    {
      mova(from, to);
      return;
    };

  if (name(sha) >= shrealhd && name(sha) <= doublehd) {
    /* moving a float or double */
    int  f1 = in_fl_reg(from.where_exp);
    int  f2 = in_fl_reg(to.where_exp);
    int  f1pos = (f1)? get_reg_no(f1): 0;
    int  f2pos = (f2)? get_reg_no(f2): 0;
    if (f1pos && f1pos == f2pos && f2 != 0x10000)
      return;			/* from and to are the same */
    if (f1pos && f1pos > f2pos && f2 != 0x10000) {
      if (f1pos == fstack_pos &&
	  from.where_exp != flstack.where_exp &&
	/* name (sha) != doublehd && */
	  use_pop_ass(to.where_exp, from.where_exp)!= 2) {
	if (flinmem (to)) {	/* are going to pop the floating point stack */
	  contop (te, 0, reg0);	/* compute address of to if necessary */
	  if (name(sha) == shrealhd)
	    ins1(fsts, 32, to);
	  else
	  if (name(sha) == realhd)
	    ins1(fstl, 64, to);
	  else {
	    ins1(fstpt, 96, to);
	    ins1(fldt, 96, to);
	  };
	  end_contop();
	  son(fe) = holdfe;
	  son(te) = holdte;
	  return;
	};
	ins1 (fst, 0, to);	/* store fstack0 into to (a reg) */
	son(fe) = holdfe;
	son(te) = holdte;
	return;
      };
      if (f1pos != fstack_pos)
	move(sha, from, flstack);
      /* push from into floating point stack */
      if (flinmem (to)) {	/* store from fstack0 into memory and pop */
	contop(te, 0, reg0);
	if (name(sha) == shrealhd)
	  ins1(fstps, 32, to);
	else
	if (name(sha) == realhd)
	  ins1(fstpl, 64, to);
	else
	  ins1(fstpt, 96, to);
	pop_fl;
	end_contop();
	son(fe) = holdfe;
	son(te) = holdte;
	return;
      };
      ins1 (fstp, 0, to);	/* pop from fstack0 into floating point register */
      pop_fl;
      son(fe) = holdfe;
      son(te) = holdte;
      return;
    };
    if (in_fl_reg(to.where_exp)) {
      int fz;
      if (name(from.where_exp) == real_tag &&
	 ((fz = cmpflpt(no(from.where_exp),
                           no(fzeroe), 5), fz) ||
	    cmpflpt(no(from.where_exp), no(fonee), 5))) {
	if (fz)
	  ins0 (fldz);		/* push zero into fstack0 */
	else
	  ins0 (fld1);		/* push one into fstack0 */
      }
      else {
	if (flinmem (from)) {	/* push from into fstack0 from memory */
	  contop (fe, 0, reg0);	/* put address of from into reg0 if necessary */
	  if (name(sha) == shrealhd)
	    ins1(flds, 32, from);
	  else
	  if (name(sha) == realhd)
	    ins1(fldl, 64, from);
	  else
	    ins1(fldt, 96, from);
	  end_contop();
	}
	else {
	  if (f1pos == fstack_pos) {/* push fstack0 */
	    load_stack0();
	  }
	  else
	    ins1 (fld, 0, from);/* push floating point register */
	};
      };
      push_fl;			/* we necessarily did a push */
      if (flinmem (to)) {	/* pop fstack0 to to (in memory ) */
	contop(te, 0, reg0);
	if (name(sha) == shrealhd)
	  ins1(fstps, 32, to);
	else
	if (name(sha) == realhd)
	  ins1(fstpl, 64, to);
	else
	  ins1(fstpt, 96, to);
	pop_fl;
	end_contop();
	son(fe) = holdfe;
	son(te) = holdte;
	return;
      };

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
    };
    /* fall through for floating point number not in coprocessor */
  };


  if (name (to.where_exp) == apply_tag) {	/* pushing */
    where reg_w;
    if (name(fe) == real_tag) {
      int fv = name(sh(fe)) - shrealhd;
      r2l fint;
      fint = real2longs_IEEE(&flptnos[no(fe)], fv);
      if (sz >= 96)
        move(slongsh, mw(zeroe, fint.i3), to);
      if (sz >= 64)
        move(slongsh, mw(zeroe, fint.i2), to);
      move(slongsh, mw(zeroe, fint.i1), to);
      son(fe) = holdfe;
      son(te) = holdte;
      return;
    };
    /* we are pushing on parameter stack */
    if (sz == 32) {
      reg_w = equiv_reg(from, sz);
      if (reg_w.where_exp != NULL) {
	ins1(pushl, 32, reg_w);
#ifdef DWARF2
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_push();
#endif
	son(fe) = holdfe;
	son(te) = holdte;
	return;
      };
    };
    if (sz == 64) {	/* must be s64 or u64 */
      if (name (fe) == val_tag) {	/* moving a constant integer */
	if (!isbigval(fe)) {
	  c = no(fe) + from.where_off;
	  c1 = (name(sha) == s64hd && c < 0)? -1 : 0;
	}
	else {
	  flt64 x;
	  int ov;
	  x = flt_to_f64(no(fe), is_signed(sh(fe)), &ov);
	  c = x.small;
	  c1 = x.big;
	}
	ins1(pushl, 32, mw(zeroe, c1));
#ifdef DWARF2
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_push();
#endif

	ins1(pushl, 32, mw(zeroe, c));
#ifdef DWARF2
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_push();
#endif

	son(fe) = holdfe;
	son(te) = holdte;
	return;
      }
      move(sha, from, reg0);
      ins0(pushedx);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_push();
#endif

      ins0(pusheax);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_push();
#endif

      son(fe) = holdfe;
      son(te) = holdte;
      return;
    };
    if (sz < 32 ||
        (cpu & CPU_80486 && inmem(from))) {
      move(sha, from, reg0);
      ins1(pushl, 32, reg0);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_push();
#endif

      son(fe) = holdfe;
      son(te) = holdte;
      return;
    };
    contop(from.where_exp, 0, reg0);
    ins1(pushl, sz, from);
#ifdef DWARF2
    if (diag == DIAG_DWARF2 && no_frame)
      dw2_track_push();
#endif

    end_contop();
    son(fe) = holdfe;
    son(te) = holdte;
    return;
  };


  if (inmem(from) && inmem(to) && ((sz <= 32 && sz != 24)
				|| name(sha) == u64hd || name(sha) == s64hd)) {
    /* from and to are both in memory */
    move(sha, from, reg0);
    move(sha, reg0, to);
    son(fe) = holdfe;
    son(te) = holdte;
    return;
  };

  if (name(fe) == real_tag) {
    int fv = name(sh(fe)) - shrealhd;
    r2l fint;
    fint = real2longs_IEEE(&flptnos[no(fe)], fv);
    move(slongsh, mw(zeroe, fint.i1), to);
    if (sz >= 64)
      move(slongsh, mw(zeroe, fint.i2), mw(te, to.where_off + 32));
    if (sz >= 96)
      move(slongsh, mw(zeroe, fint.i3), mw(te, to.where_off + 64));
    son(fe) = holdfe;
    son(te) = holdte;
    return;
  };

  if (name (fe) == val_tag) {	/* moving a constant integer */
    isco = 1;
    if (!isbigval(fe)) {
      c = no(fe) + from.where_off;
      if (sz == 64)
	c1 = (name(sha) == s64hd && c < 0)? -1 : 0;
    }
    else {
      flt64 x;
      int ov;
      x = flt_to_f64(no(fe), is_signed(sh(fe)), &ov);
      c = x.small;
      c1 = x.big;
    }
  };
  if (name (fe) == null_tag) {	/* moving a constant NULL */
    isco = 1;
    c = no(fe);
  };


  if (isco) {			/* moving a constant */

    contop(te, 0, to);
    SET(c);

    if (c == 0 && !inmem (to) && sz <= 32) {/* constant is zero, so clear */
      cond1_set = 0;
      cond2_set = 0;
      ins2(xorl, 32, 32, to, to);
      invalidate_dest(to);
      end_contop();
      son(fe) = holdfe;
      son(te) = holdte;
      return;
    };

    /* use fastest operation for each size of constant */

    if (sz == 8 && !eq_where(to, reg5) && !eq_where(to, reg4)) {
      ins2(movb, sz, sz, mw(zeroe,(c & 0xff)), to);
      invalidate_dest(to);
      end_contop();
      son(fe) = holdfe;
      son(te) = holdte;
      return;
    };

    if (sz == 16) {
      ins2(movw, sz, sz, mw(zeroe,(c & 0xffff)), to);
      invalidate_dest(to);
      end_contop();
      son(fe) = holdfe;
      son(te) = holdte;
      return;
    };

    if (sz == 64) {
      if (eq_where(to, reg0)) {
	if (c == 0)
	  ins2(xorl, 32, 32, reg0, reg0);
	else
	  ins2(movl, 32, 32, mw(zeroe, c), reg0);
	if (c1 == 0)
	  ins2(xorl, 32, 32, reg1, reg1);
	else
	  ins2(movl, 32, 32, mw(zeroe, c1), reg1);
	invalidate_dest(reg0);
	invalidate_dest(reg1);
      }
      else {
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
	((name(te) == ass_tag && name(son(te)) == name_tag &&
		isvar(son(son(te)))) ||
		(name(te) == ident_tag)))) {
      reg_w = equiv_reg(from, sz);
      if (reg_w.where_exp != NULL)
	move(sha, reg_w, to);
      else {
        move(slongsh, from, reg0);
        move(slongsh, reg0, to);
        move_reg(from, reg0, sha);
      };
    }
    else {
      ins2(movl, 32, 32, from, to);
    }

    invalidate_dest(to);
    end_contop();
    son(fe) = holdfe;
    son(te) = holdte;
    return;
  };

  /* moving a non-constant value */

  if (sz == 8) {		/* moving a byte */
    if (!inmem(from) &&
	(in_reg(from.where_exp) & 0x70)) {
      if (!inmem(to)) {
	move(slongsh, from, to);
	son(fe) = holdfe;
	son(te) = holdte;
	return;
      };
      move(slongsh, from, reg0);
      move(sha, reg0, to);
      son(fe) = holdfe;
      son(te) = holdte;
      return;
    };

    if (!inmem(to) && name(to.where_exp)!= val_tag &&
	(in_reg(to.where_exp) & 0x70)) {
      if (!inmem(from)) {
	move(slongsh, from, to);
	son(fe) = holdfe;
	son(te) = holdte;
	return;
      };
      move(sha, from, reg0);
      move(slongsh, reg0, to);
      son(fe) = holdfe;
      son(te) = holdte;
      return;
    };

    if (in_reg(from.where_exp)) {
      contop(te, eq_where(reg0, from), to);
      ins2(movb, sz, sz, from, to);
      invalidate_dest(to);
      move_reg(from, to, sha);
      end_contop();
    }
    else {
      reg_w = equiv_reg(from, sz);
      if (reg_w.where_exp != NULL) {
	move(sha, reg_w, to);
	move_reg(from, to, sha);
      }
      else {
	contop(fe, 0, to);
	ins2(movb, sz, sz, from, to);
	invalidate_dest(to);
	move_reg(from, to, sha);
	end_contop();
      };
    };
    son(fe) = holdfe;
    son(te) = holdte;
    return;
  };
  if (sz == 16) {		/* moving 16 bits */
    if (in_reg(from.where_exp)) {
      contop(te, eq_where(reg0, from), to);
      ins2(movw, sz, sz, from, to);
      invalidate_dest(to);
      move_reg(from, to, sha);
      end_contop();
    }
    else {
      reg_w = equiv_reg(from, sz);
      if (reg_w.where_exp != NULL) {
	move(sha, reg_w, to);
	move_reg(from, to, sha);
      }
      else {
	contop(fe, 0, to);
	ins2(movw, sz, sz, from, to);
	invalidate_dest(to);
	move_reg(from, to, sha);
	end_contop();
      };
    };
    son(fe) = holdfe;
    son(te) = holdte;
    return;
  };
  if (sz == 32) {		/* moving 32 bits */

    if (in_reg(from.where_exp)) {
      contop(te, eq_where(reg0, from), to);
      ins2(movl, sz, sz, from, to);
      invalidate_dest(to);
      move_reg(from, to, sha);
      end_contop();
    }
    else {
      reg_w = equiv_reg(from, sz);
      if (reg_w.where_exp != NULL) {
	move(sha, reg_w, to);
	move_reg(from, to, sha);
      }
      else {
	contop(fe, 0, to);
	ins2(movl, sz, sz, from, to);
	invalidate_dest(to);
	move_reg(from, to, sha);
	end_contop();
      };
    };
    son(fe) = holdfe;
    son(te) = holdte;
    return;
  };

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
    }
    else
    if (!eq_where(to, reg0)) {
      regsinuse |= 0x2;
      contop(te, 1, to);
      w1 = mw(te, to.where_off + 32);
      ins2(movl, sz, sz, reg0, to);
      ins2(movl, sz, sz, reg1, w1);
      invalidate_dest(to);
      end_contop();
    };
    regsinuse = riu;
    son(fe) = holdfe;
    son(te) = holdte;
    return;
  }

  if (name(sha) == realhd && might_overlap(sha, from, to)) {
     if ((regsinuse & 0x7e)!= 0x7e) {
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

        if ((regsinuse & 0x2) == 0)
	  extra_reg = reg1;
	else
        if ((regsinuse & 0x4) == 0)
	  extra_reg = reg2;
	else
        if ((regsinuse & 0x8) == 0) {
	  extra_reg = reg3;
	  min_rfree |= 0x8;
        }
	else
        if ((regsinuse & 0x10) == 0) {
	  extra_reg = reg4;
	  min_rfree |= 0x10;
        }
	else
        if ((regsinuse & 0x20) == 0) {
	  extra_reg = reg5;
	  min_rfree |= 0x20;
        }
	else
        if ((regsinuse & 0x40) == 0) {
	  extra_reg = reg6;
	  min_rfree |= 0x40;
        }
	else {
	  SET(extra_reg);
	};
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
      };
    move(sha, from, flstack);
    move(sha, flstack, to);
    son(fe) = holdfe;
    son(te) = holdte;
    return;
  };

  if (sz <= (40 * 8) && two_contops(fe, te)) {
    int  i;
    int  foff = from.where_off;
    int  toff = to.where_off;
    int  old_regsinuse = regsinuse;


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
    };
    if (i == sz) {
      invalidate_dest(reg0);
      end_contop();
      contop_level--;
      end_contop();
      son(fe) = holdfe;
      son(te) = holdte;
      return;
    };
    /* move final word and byte if necessary */
    if ((sz - i) >= 16) {
      ins2(movw, size16, size16, mw(fe, foff + i), reg0);
      ins2(movw, size16, size16, reg0, mw(te, toff + i));
      invalidate_dest(mw(te, toff + i));
      i += 16;
    };
    if ((sz - i) >= 8) {
      ins2(movb, size8, size8, mw(fe, foff + i), reg0);
      ins2(movb, size8, size8, reg0, mw(te, toff + i));
      invalidate_dest(mw(te, toff + i));
    };
    invalidate_dest(reg0);
    end_contop();
    contop_level--;
    end_contop();
    son(fe) = holdfe;
    son(te) = holdte;
    return;
  };

  if (name(sha) == realhd) {
    move(sha, from, flstack);
    move(sha, flstack, to);
    son(fe) = holdfe;
    son(te) = holdte;
    return;
  };

  {
		/* use rep movsl to do the move */
    int  old_extra_stack = extra_stack;
    int  old_regsinuse;
    if (regsinuse & 0x20) {
      extra_stack += 32;
      ins0(pushesi);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_push();
#endif
    };
    if (regsinuse & 0x10) {
      extra_stack += 32;
      ins0(pushedi);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_push();
#endif
    };
    if (regsinuse & 0x4) {
      extra_stack += 32;
      ins0(pushecx);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_push();
#endif
    };
    old_regsinuse = regsinuse;
    if (regsinuse & 0x20) {
      mova(from, pushdest);
      extra_stack += 32;
    }
    else {
      mova(from, reg5);
      regsinuse |= 0x20;
    };

    mova(to, reg4);
    regsinuse = old_regsinuse;

    move(slongsh, mw(zeroe,(sz / 32)), reg2);

    if (regsinuse & 0x20) {
      ins0(popesi);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_pop();
#endif
    }
    ins0(rep);
    ins0(movsl);

    /* and move the last word and byte if necessary */
    sz = sz % 32;
    if (sz >= 16) {
      ins0(movsw);
      sz -= 16;
    };
    if (sz == 8)
      ins0(movsb);


    invalidate_dest(reg2);
    invalidate_dest(reg4);
    invalidate_dest(reg5);
    if (regsinuse & 0x4) {
      ins0(popecx);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_pop();
#endif
    };
    if (regsinuse & 0x10) {
      ins0(popedi);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_pop();
#endif
    };
    if (regsinuse & 0x20) {
      ins0(popesi);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_pop();
#endif
    };
    check_stack_max;
    extra_stack = old_extra_stack;
    min_rfree |= 0x30;
    invalidate_dest(to);
    son(fe) = holdfe;
    son(te) = holdte;
    return;
  };
}

/*
 * Use rep movsb
 */
void movecont
(where from, where to, where length, int nooverlap)
{
  if (nooverlap) {
    int  old_extra_stack = extra_stack;
    if (regsinuse & 0x20) {
      extra_stack += 32;
      ins0(pushesi);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_push();
#endif
    }
    if (regsinuse & 0x10) {
      extra_stack += 32;
      ins0(pushedi);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_push();
#endif
    }
    ins0(pushecx);
#ifdef DWARF2
    if (diag == DIAG_DWARF2 && no_frame)
      dw2_track_push();
#endif
    extra_stack += 32;
    move(sh(from.where_exp), from, pushdest);
    extra_stack += 32;
    move(sh(to.where_exp), to, pushdest);
    extra_stack += 32;
    move(sh(length.where_exp), length, pushdest);
    ins0(popecx);
#ifdef DWARF2
    if (diag == DIAG_DWARF2 && no_frame)
      dw2_track_pop();
#endif
    ins0(popedi);
#ifdef DWARF2
    if (diag == DIAG_DWARF2 && no_frame)
      dw2_track_pop();
#endif
    ins0(popesi);
#ifdef DWARF2
    if (diag == DIAG_DWARF2 && no_frame)
      dw2_track_pop();
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
    if (diag == DIAG_DWARF2 && no_frame)
      dw2_track_pop();
#endif
    if (regsinuse & 0x10) {
      ins0(popedi);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_pop();
#endif
    }
    if (regsinuse & 0x20) {
      ins0(popesi);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_pop();
#endif
    }
    check_stack_max;
    extra_stack = old_extra_stack;
    min_rfree |= 0x30;
    invalidate_dest(reg0);
    invalidate_dest(reg2);
    invalidate_dest(to);
  }
  else {
    move(sh(length.where_exp), length, pushdest);
    extra_stack += 32;
    move(sh(from.where_exp), from, pushdest);
    extra_stack += 32;
    move(sh(to.where_exp), to, pushdest);
    if (name_memmove == NULL)
      name_memmove = make_extn("memmove", f_proc, 0);
    callins (0, name_memmove, stack_dec);	/* call_libfn("memmove"); */
    extra_stack -= 64;
    add(slongsh, mw(zeroe, 12), sp, sp);
    invalidate_dest(reg0);
    invalidate_dest(reg1);
    invalidate_dest(reg2);
  };
}

void retins
(void)
{
 /*
  * leave proc, discarding any callee parameters
  * can overwrite %ecx
  */
  int n = (remove_struct_ref && has_struct_res(crt_proc_exp))? 32 : 0;
  if (callee_size >= 0) {
    if ((n += callee_size) == 0)
      ins0(ret);
    else
      ins1(ret, 32, mw(zeroe, n/8));
  }
  else {	/* variable sized callees to be discarded */
    ins0 (popecx);	/* return address */
    ins0 ("pop %esp");	/* discard callees */
    if (n != 0)
      add(slongsh, mw(zeroe, n/8), sp, sp);
    ins0("jmp *%ecx");
  }
}

void stack_return
(int longs)
{
  if (longs == 32 && (regsinuse & 0x2) == 0)
   {
     ins0(popedx);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_pop();
#endif
     invalidate_dest(reg1);
     stack_dec += longs;
     return;
   };
  if (longs == 32 && (regsinuse & 0x4) == 0)
   {
     ins0(popecx);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_pop();
#endif
     invalidate_dest(reg2);
     stack_dec += longs;
     return;
   };
  if (cpu & CPU_80586 && longs == 64 && (regsinuse & 0x2) == 0)
   {
     ins0(popedx);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_pop();
#endif
     ins0(popedx);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_pop();
#endif
     invalidate_dest(reg1);
     stack_dec += longs;
     return;
   };
  if (cpu & CPU_80586 && longs == 64 && (regsinuse & 0x4) == 0)
   {
     ins0(popecx);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_pop();
#endif
     ins0(popecx);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_pop();
#endif
     invalidate_dest(reg2);
     stack_dec += longs;
     return;
   };
  add(slongsh, mw(zeroe,(longs / 8)), sp, sp);
  stack_dec += longs;
#ifdef DWARF2
  if (diag == DIAG_DWARF2 && no_frame)
    dw2_track_sp();
#endif
}

/*
 * Call instruction
 */
void callins
(int longs, exp fn, int ret_stack_dec)
{
  cond1_set = 0;
  cond2_set = 0;
  if (name(fn) == name_tag && !isvar(son(fn)) && isglob(son(fn))) {
    exp ind = getexp(f_proc, NULL, 0, fn, NULL, 0,
	0, cont_tag);
#ifdef DWARF2
    if (current_dg_info) {
      current_dg_info->data.i_call.brk = set_dw_text_label();
      current_dg_info->data.i_call.p.k = WH_STR;
      current_dg_info->data.i_call.p.u.s = (brog(son(fn))) ->dec_id;
      current_dg_info->data.i_call.p.o = no(fn) /8;
    }
#endif
    ins1(call, 32, mw(ind, 0));
    retcell(ind);
  }
  else {
    if (inmem(mw(fn, 0))) {
      move(slongsh, mw(fn, 0), reg0);
      fn = reg0.where_exp;
    };
#ifdef DWARF2
    if (current_dg_info) {
      int rn;
      if (name(fn) ==name_tag && !isvar(son(fn)))
	rn = no(son(fn));
      else
      if (name(fn) ==cont_tag && name(son(fn)) ==name_tag &&
		isvar(son(son(fn))))
	rn = no(son(son(fn)));
      else {
	error(ERR_INTERNAL, "where?");
	rn = 1;
      }
      current_dg_info->data.i_call.brk = set_dw_text_label();
      current_dg_info->data.i_call.p.k = WH_REG;
      current_dg_info->data.i_call.p.u.l = get_reg_no(rn);
    }
#endif
    ins1ind(call, 32, mw(fn, 0));
  };
  stack_dec = ret_stack_dec;
#ifdef DWARF2
  if (diag == DIAG_DWARF2) {
    dw2_start_basic_block();
  }
#endif
  if (longs == 32 || (longs == 64 && cpu & CPU_80586) ||
	!no_frame || !not_in_params || !not_in_postlude)
    stack_return(longs);
  else
    keep_short = 1;
}

void jumpins
(exp lab)
{
    if (inmem(mw(lab, 0))) {
      move(slongsh, mw(lab, 0), reg0);
      lab = reg0.where_exp;
    };
    ins1ind(jmp, 32, mw(lab, 0));
}

/*
 * Compare from with min (from - min) values have shape sha. The testno for
 * which it is being used is supplied so that we can optimise cmp(0, x)
 *
 * Result true (1) if optimised compare with 0 in which case we need
 * to ignore overflow
 */
int cmp
(shape sha, where from, where min, int nt, exp e)
{
  int  sz;
  exp cc = cond1.where_exp;
  exp cc2a = cond2a.where_exp;
  exp me;
  int contop_done = 0;
  where has_equiv_from;
  where has_equiv_min;
  exp hold_from = son(from.where_exp);
  exp hold_min = son(min.where_exp);
  sz = shape_size(sha);

  if (cond1_set &&
     (eq_where(min, zero) || (name(min.where_exp) == null_tag && no(min.where_exp) == 0)) &&
     (is_signed(sha) || nt >= 5) &&
     ((name(cc) == ident_tag && eq_shape(sh(son(cc)), sha)) ||
	(name(cc) == ass_tag && eq_shape(sh(bro(son(cc))), sha)) ||
	eq_shape(sh(cc), sha)) &&
      eq_where(cond1, from) && sz <= 32)
    return 1;			/* we are comparing the value from which
				   the conditions are set with zero */

  if (cond2_set &&
	((name(cc2a) == ident_tag && eq_shape(sh(son(cc2a)), sha)) ||
	  eq_shape(sh(cc2a), sha)) &&
	eq_where(cond2a, from) &&
	eq_where(cond2b, min))
    return 0;			/* we are repeating the previous comparison */


  if (!is_floating(name(sha))) {
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
       (eq_where(min, zero) || (name(min.where_exp) == null_tag && no(min.where_exp) == 0)) &&
       (is_signed(sha) || nt >= 5) &&
       ((name(cc) == ident_tag && eq_shape(sh(son(cc)), sha)) ||
	 (name(cc) == ass_tag && eq_shape(sh(bro(son(cc))), sha)) ||
	  eq_shape(sh(cc), sha)) &&
        eq_where(cond1, from) && sz <= 32)
      return 1;			/* we are comparing the value from which the conditions are set with zero */

    if (cond2_set &&
	 ((name(cc2a) == ident_tag && eq_shape(sh(son(cc2a)), sha)) ||
	    eq_shape(sh(cc2a), sha)) &&
	  eq_where(cond2a, from) &&
	  eq_where(cond2b, min))
      return 0;			/* we are repeating the previous comparison */

    if (((name(min.where_exp) == null_tag && no(min.where_exp) == 0)
	 || eq_where(min, zero)) &&
	!inmem(from)) {
				/* min is zero */

      cond1_set = 1;
      cond2_set = 0;
      cond1 = from;


      if (sz == 8) {
	ins2(testb, sz, sz, from, from);
	return 0;
      };
      if (sz == 16) {
	ins2(testw, sz, sz, from, from);
	return 0;
      };
      if (sz == 32) {
	ins2(testl, sz, sz, from, from);
	return 0;
      };
      if (sz == 64) {	/* !inmem, so from must be reg0/reg1 */
	if (nt >= 5) {
	  ins2(orl, 32, 32, reg1, reg0);
	  invalidate_dest(reg0);
	  cond1_set = 0;
	  return 0;
	}
	else
	if (nt == f_less_than || nt == f_greater_than_or_equal) {
	  ins2(testl, 32, 32, reg1, reg1);
	  cond1_set = 0;
	  return 0;
	}
      }
    };


    cond1_set = 0;
    cond2_set = 1;
    cond2a = from;
    cond2b = min;


    if (nt >= 5 &&
       ((name(from.where_exp) == null_tag && no(from.where_exp) == 0) ||
		 eq_where(from, zero)) &&
        !inmem(min)) {
      /* from is zero and the test is == or != so we don't have to reverse its sense */

      if (sz == 8) {
	ins2(testb, sz, sz, min, min);
	return 0;
      };
      if (sz == 16) {
	ins2(testw, sz, sz, min, min);
	return 0;
      };
      if (sz == 32) {
	ins2(testl, sz, sz, min, min);
	return 0;
      };
      if (sz == 64) {	/* !inmem, so min must be reg0/reg1 */
	ins2(orl, 32, 32, reg1, reg0);
	invalidate_dest(reg0);
	cond2_set = 0;
	return 0;
      }
    };

    if (sz != 16 && sz <= 32 && ((name(min.where_exp) == null_tag ||
		 name(min.where_exp) == val_tag) &&
			 no(min.where_exp) == 0) &&
        inmem(from) && has_equiv_from.where_exp == NULL) {
      {
        move(sha, from, reg0);
	cond1_set = 0;
	cond2_set = 0;
        IGNORE cmp(sha, reg0, min, nt, e);
      };
      return 0;
    };

    {
      char *in;
      int riu = regsinuse;
      switch (sz) {
	case 8:
	  in = cmpb;
	  break;
	case 16:
	  in = cmpw;
	  break;
	case 32:
	case 64:
	  in = cmpl;
	  break;
	default:
	  error(ERR_INTERNAL, "unexpected size");
      };

      if ((inmem(from) && inmem(min)) ||
	 (name(sha) == prokhd && !PIC_code && !eq_where(min, reg0)) ||
	 (name(from.where_exp) == name_tag &&
	    isvar(son(from.where_exp))) ||
	  (name(from.where_exp) == reff_tag &&
	    name(son(from.where_exp)) == name_tag &&
	    !isvar(son(son(from.where_exp))))) {
	if ((name(from.where_exp) == name_tag &&
	   ((isvar(son(from.where_exp)) &&
	      ptno(son(from.where_exp)) <= par_pl) ||
           (PIC_code &&
              isglob(son(from.where_exp)) &&
	     (name(sha) == prokhd || name(sha) == ptrhd) &&
              !brog(son(from.where_exp)) ->  extnamed))) ||
	      name(from.where_exp) == reff_tag)
	  mova(from, reg0);
	else
	  move(sha, from, reg0);
	son(from.where_exp) = hold_from;
	from = reg0;
	hold_from = son(from.where_exp);
      }
      else {
	if (inmem(from)) {
	  if (sz == 64)
	    regsinuse |= 0x2;
	  contop(from.where_exp, eq_where(reg0, min), reg0);
	  contop_done = 1;
	};
      };

      if ((name(min.where_exp) == val_tag || name(min.where_exp) == env_offset_tag) &&
           ((name(from.where_exp) == val_tag || name(from.where_exp) == env_offset_tag) ||
		(keep_short && inmem(from)))) {
        move(sha, from, reg0);
	son(from.where_exp) = hold_from;
        from = reg0;
	hold_from = son(from.where_exp);
      };

      if (eq_where(from, reg0) && eq_where(min, reg0)
				&& !eq_where(orig_min, reg0)) {
	son(min.where_exp) = hold_min;
	min = orig_min;		/* equiv_reg lost due to evaluation of from */
	hold_min = son(min.where_exp);
      }

      me = min.where_exp;
      if ((name(me) == name_tag && isvar(son(me)) &&
	     ptno(son(me)) <= par_pl) ||
         (PIC_code && name(me) == name_tag && isglob(son(me)) &&
           (name(sha) == prokhd || name(sha) == ptrhd) &&
             !brog(son(me)) ->  extnamed) ||
	  (name(me) == reff_tag && name(son(me)) == name_tag &&
	    !isvar(son(son(me))))) {
	if (eq_where(from, reg0)) {
          ins0(pusheax);
#ifdef DWARF2
	  if (diag == DIAG_DWARF2 && no_frame)
	    dw2_track_push();
#endif
          extra_stack += 32;
	  check_stack_max;
	  mova(min, reg0);
	  ins2(in, sz, sz, reg0, mw(ind_sp.where_exp, -32));
	  invalidate_dest(ind_sp);
	  invalidate_dest(reg0);
          ins0(popeax);
#ifdef DWARF2
	  if (diag == DIAG_DWARF2 && no_frame)
	    dw2_track_pop();
#endif
          extra_stack -= 32;
	  son(from.where_exp) = hold_from;
	  son(min.where_exp) = hold_min;
          return 0;
	};
	mova(min, reg0);
	son(min.where_exp) = hold_min;
	min = reg0;
	hold_min = son(min.where_exp);
     }
      else {
	if (inmem(min)) {
	  if (sz == 64)
	    regsinuse |= 0x2;
	  contop(min.where_exp, eq_where(reg0, from), reg0);
	  contop_done = 1;
	};
      };

      if (sz == 8 && (eq_where(min, reg4) || eq_where(min, reg5))) {
	if (!eq_where(from, reg0)) {
	  move(sha, min, reg0);
	  son(min.where_exp) = hold_min;
	  min = reg0;
	  hold_min = son(min.where_exp);
	}
	else {
	  sub(sha, min, reg0, reg0);
	  if (contop_done)
	    end_contop();
	  son(from.where_exp) = hold_from;
	  son(min.where_exp) = hold_min;
	  return 0;
	}
      };

      if (sz != 64) {
	ins2 (in, sz, sz, min, from);/* do the comparison */
	if (contop_done)
	  end_contop();
	son(from.where_exp) = hold_from;
	son(min.where_exp) = hold_min;
	return 0;
      }
      {		/* compare 64bit */
	where fromlo, fromhi, minlo, minhi;
	cond2_set = 0;
	if (eq_where(from, reg0)) {
	  fromlo = reg0;
	  fromhi = reg1;
	}
	else {
	  fromlo = from;
	  fromhi = mw(from.where_exp, from.where_off + 32);
	}
	if (eq_where(min, reg0)) {
	  minlo = reg0;
	  minhi = reg1;
	}
	else
	if (name(min.where_exp) == val_tag) {
	  int c, c1;
	  if (!isbigval(min.where_exp)) {
	    c = no(min.where_exp);
	    c1 = (is_signed(sha) && c < 0)? -1 : 0;
	    if (c == 0 && (nt == f_greater_than_or_equal || nt == f_less_than)) {
				/* sign bit says it all, so ignore fromlo */
	      ins2(cmpl, 32, 32, zero, fromhi);
	      if (contop_done)
		end_contop();
	      regsinuse = riu;
	      son(from.where_exp) = hold_from;
	      son(min.where_exp) = hold_min;
	      return 0;
	    }
	  }
	  else {
	    flt64 x;
	    int ov;
	    x = flt_to_f64(no(min.where_exp), is_signed(sha), &ov);
	    c = x.small;
	    c1 = x.big;
	  }
	  minlo = mw(zeroe, c);
	  minhi = mw(zeroe, c1);
	}
	else {
	  minlo = min;
	  minhi = mw(min.where_exp, min.where_off + 32);
	}
	if (nt >= 5 || !is_signed(sha)) {
	  int flags_set_lab = next_lab();
	  ins2(cmpl, 32, 32, minhi, fromhi);
	  simple_branch(jne, flags_set_lab);
	  ins2(cmpl, 32, 32, minlo, fromlo);
	  simplest_set_lab(flags_set_lab);
	  if (contop_done)
	    end_contop();
	  regsinuse = riu;
	  son(from.where_exp) = hold_from;
	  son(min.where_exp) = hold_min;
	  return 0;
	}
	cmp_64hilab = next_lab();
	ins2(cmpl, 32, 32, minhi, fromhi);
	cmp64_contop (contop_done);	/* if hi unequal, undo contop and jump to cmp_64hilab */
	ins2(cmpl, 32, 32, minlo, fromlo);
        if (contop_done)
	  end_contop();
	regsinuse = riu;
	son(from.where_exp) = hold_from;
	son(min.where_exp) = hold_min;
        return 0;
      }
    };
  }
  else {
    cond1_set = 0;
    cond2_set = 1;
    cond2a = from;
    cond2b = min;

    fl_comp (sha, from, min, e);	/* do a floating point comparison */
    son(from.where_exp) = hold_from;
    son(min.where_exp) = hold_min;
    return 0;
  }
}

int bad_from_reg
(where from)
{
    return !inmem(from) && name(from.where_exp)!= val_tag &&
	(in_reg(from.where_exp) & 0x70);
}

/*
 * Change variety from (which has shape fsh) to sha, and put in to
 */
void change_var_sh
(shape sha, shape fsh, where from, where to)
{
  exp fe = from.where_exp;
  exp holdfe = son(fe);
  int  szf,			/* size of from */
        szt;			/* size of to */
  int sgf,			/* from is signed */
    sgt;			/* to is signed */

  cond1_set = 0;
  cond2_set = 0;		/* see note on move */

  szf = shape_size(fsh);
  sgf = is_signed(fsh);

  /* set szt and sgt */
  switch (name(sha)) {
    case scharhd:
      szt = 8;
      sgt = 1;
      break;
    case ucharhd:
      szt = 8;
      sgt = 0;
      break;
    case swordhd:
      szt = 16;
      sgt = 1;
      break;
    case uwordhd:
      szt = 16;
      sgt = 0;
      break;
    case slonghd:
      szt = 32;
      sgt = 1;
      break;
    case s64hd:
      szt = 64;
      sgt = 1;
      break;
    case u64hd:
      szt = 64;
      sgt = 0;
      break;
    case bitfhd:
      szt = 32;
      sgt = is_signed(sha);
      sha = (sgt)? slongsh: ulongsh;
      break;
    default:
      szt = 32;
      sgt = 0;
      break;
  };

  if (name (fe) == val_tag) {	/* we know the value */
    int val;
    if (!isbigval(fe)) {
      val = dochvar(no(fe), sha);
      if (overflow_e != NULL && (dochvar(no(fe), fsh)!= val || (val < 0 &&
		((szt == 32 && (sgt != sgf)) || (szt == 64 && !sgt && sgf)))))
	do_exception();
      no(fe) = val;
    }
    else {
      flt64 x;
      int ov;
      x = flt_to_f64(no(fe), sgf, &ov);
      val = dochvar((int)(x.small), sha);
      if (overflow_e != NULL && (
		(szt == 64 && x.big < 0 && (sgt != sgf)) ||
		(szt == 32 && ((!(x.small & (1<<31)) && x.big != 0) ||
			((x.small & (1<<31)) && x.big != -sgt))) ||
		(szt < 32)))
	do_exception();
      if (szt != 64) {
	no(fe) = val;
	clearbigval(fe);
      }
    };
    sh(fe) = sha;
    move(sha, from, to);
    return;
  };


  if (name(fsh) == bitfhd) {
    if (szf < 8) {
      if (sgf && !sgt) {
	and(scharsh, from, mw(zeroe,(1 << szf) - 1), reg0);
	from = reg0;
      }
      szf = 8;
      fsh = (sgf)? scharsh : ucharsh;
    }
    else
    if (szf < 16) {
      if (sgf && !sgt) {
	and(swordsh, from, mw(zeroe,(1 << szf) - 1), reg0);
	from = reg0;
      }
      szf = 16;
      fsh = (sgf)? swordsh : uwordsh;
    }
    else
    if (szf < 32) {
      if (sgf && !sgt) {
	and(slongsh, from, mw(zeroe,(1 << szf) - 1), reg0);
	from = reg0;
      }
      szf = 32;
      fsh = (sgf)? slongsh : ulongsh;
    }
  }

  if (overflow_e != NULL && (sgt < sgf || (szt - sgt) < (szf - sgf))) {
    int smax = (szt == 64)? 0x7fffffff :(1 << (szt-1)) - 1;
    int min = (sgt)?(-smax) -1 : 0;
    int max = (sgt)? smax : smax+smax+1;
    if (inmem(from)) {
      move(fsh, from, reg0);
      from = reg0;
    };
    if (szf == 64) {
      if (szt == 64) {
	IGNORE cmp(slongsh, reg1, zero, f_greater_than_or_equal, NULL);
	test_exception(f_greater_than_or_equal, slongsh);
      }
      else {
	int lab1;
	IGNORE cmp(slongsh, reg1, zero, f_equal, NULL);
	if (sgf && sgt) {
	  int lab2 = next_lab();
	  lab1 = next_lab();
	  simple_branch(je, lab2);
	  IGNORE cmp(slongsh, reg1, mw(zeroe,-1), f_equal, NULL);
	  test_exception(f_equal, slongsh);
	  IGNORE cmp(ulongsh, from, mw(zeroe,min), f_greater_than_or_equal, NULL);
	  test_exception(f_greater_than_or_equal, ulongsh);
	  simple_branch(jmp, lab1);
	  simplest_set_lab(lab2);
	}
	else
	  test_exception(f_equal, slongsh);
	if (szt != 32 || sgt) {
	  IGNORE cmp(ulongsh, reg0, mw(zeroe,max), f_less_than_or_equal, NULL);
	  test_exception(f_less_than_or_equal, ulongsh);
	};
	if (sgf && sgt)
	  simplest_set_lab(lab1);
      };
    }
    else {
      if (sgf && (!sgt || szt < szf)) {
	IGNORE cmp(fsh, from, mw(zeroe,min), f_greater_than_or_equal, NULL);
	test_exception(f_greater_than_or_equal, fsh);
      };
      if ((szt - sgt) < (szf - sgf)) {
	IGNORE cmp(fsh, from, mw(zeroe,max), f_less_than_or_equal, NULL);
	test_exception(f_less_than_or_equal, fsh);
      };
    };
  }

  if (szf == 8) {
    if (bad_from_reg(from)) {
      move(slongsh, from, reg0);
      from = reg0;
    };

    if (szt == 8) {
      move(sha, from, to);
      return;
    };

    if (szt == 16) {
      if (sgf) {
	if (inmem(to)) {
	  contop(fe, eq_where(reg0, from), reg0);
	  ins2(movsbw, szf, szt, from, reg0);
	  invalidate_dest(reg0);
	  end_contop();
	  move(sha, reg0, to);
	}
	else {
	  contop(fe, eq_where(reg0, from), to);
	  ins2(movsbw, szf, szt, from, to);
	  invalidate_dest(to);
	  end_contop();
	};
	son(fe) = holdfe;
	return;
      }
      else {
	if (inmem(to)) {
	  contop(fe, eq_where(reg0, from), reg0);
	  ins2(movzbw, szf, szt, from, reg0);
	  invalidate_dest(reg0);
	  end_contop();
	  move(sha, reg0, to);
	}
	else {
	  contop(fe, eq_where(reg0, from), to);
	  ins2(movzbw, szf, szt, from, to);
	  invalidate_dest(to);
	  end_contop();
	};
	son(fe) = holdfe;
	return;
      };
    };
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
	      ins2(sarl, 8, 32, mw(zeroe,31), reg1);
	    }
	    else
	      move(ulongsh, zero, reg1);
	  };
	  move(sha, reg0, to);
	}
	else {
	  contop(fe, eq_where(reg0, from), to);
	  ins2(movsbl, szf, szt, from, to);
	  invalidate_dest(to);
	  end_contop();
	};
	son(fe) = holdfe;
	return;
      };
      if (inmem(to) || szt == 64) {
	move(scharsh, from, reg0);
	and(slongsh, reg0, mw(zeroe, 0xff), reg0);
	if (szt == 64)
	  move(ulongsh, zero, reg1);
	move(sha, reg0, to);
	}
      else {
	if (eq_where(to, reg4) || eq_where(to, reg5) ||
		 eq_where(to, reg6)) {
	  contop(fe, eq_where(reg0, from), to);
	  ins2(movzbl, szf, szt, from, to);
	  invalidate_dest(to);
	  end_contop();
	}
	else {
	  move(scharsh, from, to);
	  and(slongsh, to, mw(zeroe, 0xff), to);
	};
      };
      son(fe) = holdfe;
      return;
    };
  };

  if (szf == 16) {
    if (szt == 8) {
      if (bad_from_reg(from)) {
        move(slongsh, from, reg0);
        from = reg0;
      };

      if (sgt) {
	if (inmem(to)) {
	  move(sh(fe), from, reg0);
	  move(sha, reg0, to);
	}
	else
	  move(sha, from, to);
	son(fe) = holdfe;
	return;
      };
      move(sha, from, to);
      son(fe) = holdfe;
      return;
    };
    if (szt == 16) {
      move(sha, from, to);
      son(fe) = holdfe;
      return;
    };
    if (sgf) {
      if (inmem(to) || szt == 64) {
	contop(fe, eq_where(reg0, from), reg0);
	ins2(movswl, szf, 32, from, reg0);
	invalidate_dest(reg0);
	end_contop();
	if (szt == 64) {
	  if (sgt) {
	    move(slongsh, reg0, reg1);
	    ins2(sarl, 8, 32, mw(zeroe,31), reg1);
	  }
	  else
	    move(ulongsh, zero, reg1);
	};
	move(sha, reg0, to);
      }
      else {
	contop(fe, eq_where(reg0, from), to);
	ins2(movswl, szf, szt, from, to);
	invalidate_dest(to);
	end_contop();
      };
      son(fe) = holdfe;
      return;
    };
    if (inmem(to) || szt == 64) {
      move(swordsh, from, reg0);
      and(slongsh, reg0, mw(zeroe, 0xffff), reg0);
      if (szt == 64)
	move(ulongsh, zero, reg1);
      move(sha, reg0, to);
    }
    else {
      move(swordsh, from, to);
      and(slongsh, to, mw(zeroe, 0xffff), to);
    };
    son(fe) = holdfe;
    return;
  };

  if (szf >= 32) {
    if (szt == 8) {
      if (bad_from_reg(from)) {
        move(slongsh, from, reg0);
        from = reg0;
      };
      if (sgt) {
        if (inmem(from) && inmem(to)) {
	  move(sh(fe), from, reg0);
	  move(sha, reg0, to);
        }
        else
	  move(sha, from, to);
	son(fe) = holdfe;
        return;
      };
      move(sha, from, to);
      son(fe) = holdfe;
      return;
    };

    if (szt == 16) {
      if (sgt) {
        if (inmem(to)) {
	  move(sha, from, reg0);
  	  move(sha, reg0, to);
        }
        else
  	  move(sha, from, to);
	son(fe) = holdfe;
        return;
      };
      move(sha, from, to);
      son(fe) = holdfe;
      return;
    };
    if (szt > szf) {
      move(slongsh, from, reg0);
      if (sgf && sgt) {
	move(slongsh, reg0, reg1);
	ins2(sarl, 8, 32, mw(zeroe,31), reg1);
      }
      else
	move(ulongsh, zero, reg1);
      invalidate_dest(reg0);
      from = reg0;
    }
    move(sha, from, to);
    son(fe) = holdfe;
    return;
  };

  if (!sgf) {
    move(sha, from, to);
    son(fe) = holdfe;
    return;
  };

  move(sha, from, to);
  son(fe) = holdfe;
}

/* change variety from to sha, and put in to */
void change_var
(shape sha, where from, where to)
{
  exp fe = from.where_exp;
  shape fsh = sh(fe);
  exp old_overflow_e = overflow_e;
  overflow_e = NULL;
  change_var_sh(sha, fsh, from, to);
  overflow_e = old_overflow_e;
}

/* change variety from to sha, and put in to */
void change_var_refactor
(shape sha, where from, where to)
{
  exp fe = from.where_exp;
  shape fsh = sh(fe);
  change_var_sh(sha, fsh, from, to);
}

/*
 * op values a1, a2 of shape sha and put them in dest. opb, opw and opl are the
 * byte, short and long versions of the operator. one is the unit for the
 * operator. Similar to plus qv. for comments.
 */
void andetc
(char *opb, char *opw, char *opl, int one, shape sha, where a1, where a2, where dest)
{
  int  sz;
  exp a = a1.where_exp;
  int  aoff = a1.where_off;
  exp b = a2.where_exp;
  int  boff = a2.where_off;
  exp holda = son(a);
  exp holdb = son(b);
  sz = shape_size(sha);

  if (name(a) == val_tag && !isbigval(a) && no(a) + aoff == one) {
    move(sha, a2, dest);
    return;
  };

  if (name(b) == val_tag && !isbigval(b) && no(b) + boff == one) {
    move(sha, a1, dest);
    return;
  };

  cond1_set = 1;
  cond2_set = 0;
  cond1 = dest;			/* conditions will be set from dest */

  if (eq_where(a1, dest) &&
	(!keep_short || !flinmem(dest))) {
    if (!inmem(a1) || !inmem(a2)) {
      /* use 2 address */
      int riu = regsinuse;
      if (sz == 64)
	regsinuse |= 0x2;
      if (inmem(a1))
	contop(a, eq_where(reg0, a2), a1);
      else
	contop(b,
	    (eq_where(reg0, a2) || eq_where(reg0, a1)), a1);
      if (sz == 8) {
	ins2(opb, sz, sz, a2, a1);
      }
      else
      if (sz == 16) {
	ins2(opw, sz, sz, a2, a1);
      }
      else
      if (sz == 32) {
	ins2(opl, sz, sz, a2, a1);
      }
      else
      if (sz == 64) {
	where dhi, dlo, shi, slo;
	if (inmem(a1)) {
	  dlo = a1;
	  dhi = mw(a, aoff+32);
	}
	else {
	  dlo = reg0;
	  dhi = reg1;
	};
	if (name(b) == val_tag) {
	  int c, c1;
	  if (!isbigval(b)) {
	    c = no(b) + boff;
	    c1 = (name(sha) == s64hd && c < 0)? -1 : 0;
	  }
	  else {
	    flt64 x;
	    int ov;
	    x = flt_to_f64(no(b), is_signed(sha), &ov);
	    c = x.small;
	    c1 = x.big;
	  }
	  if (c != one)
	    ins2(opl, 32, 32, mw(zeroe, c), dlo);
	  if (c1 != one)
	    ins2(opl, 32, 32, mw(zeroe, c1), dhi);
	}
	else {
	  if (inmem(a2)) {
	    slo = a2;
	    shi = mw(b, boff+32);
	  }
	  else {
	    slo = reg0;
	    shi = reg1;
	  };
	  ins2(opl, 32, 32, slo, dlo);
	  ins2(opl, 32, 32, shi, dhi);
	};
      };
      invalidate_dest(dest);
      end_contop();
      regsinuse = riu;
      son(a) = holda;
      son(b) = holdb;
      return;
    };

    move(sha, a2, reg0);
    andetc(opb, opw, opl, one, sha, reg0, dest, dest);
    return;
  };

  if (eq_where(a2, dest) &&
	(!keep_short || !flinmem(dest))) {	/* use 2 address */
    if (!inmem(a1) || !inmem(a2)) {
      int riu = regsinuse;
      if (sz == 64)
	regsinuse |= 0x2;
      if (inmem(a1))
	contop(a, eq_where(reg0, a2), a2);
      else
	contop(b,
	    (eq_where(reg0, a1) || eq_where(reg0, a2)), a2);
      if (sz == 8) {
	ins2(opb, sz, sz, a1, a2);
      }
      else
      if (sz == 16) {
	ins2(opw, sz, sz, a1, a2);
      }
      if (sz == 32) {
	ins2(opl, sz, sz, a1, a2);
      }
      else
      if (sz == 64) {
	where dhi, dlo, shi, slo;
	if (inmem(a2)) {
	  dlo = a2;
	  dhi = mw(b, boff+32);
	}
	else {
	  dlo = reg0;
	  dhi = reg1;
	};
	if (name(a) == val_tag) {
	  int c, c1;
	  if (!isbigval(a)) {
	    c = no(a) + aoff;
	    c1 = (name(sha) == s64hd && c < 0)? -1 : 0;
	  }
	  else {
	    flt64 x;
	    int ov;
	    x = flt_to_f64(no(a), is_signed(sha), &ov);
	    c = x.small;
	    c1 = x.big;
	  }
	  if (c != one)
	    ins2(opl, 32, 32, mw(zeroe, c), dlo);
	  if (c1 != one)
	    ins2(opl, 32, 32, mw(zeroe, c1), dhi);
	}
	else {
	  if (inmem(a1)) {
	    slo = a1;
	    shi = mw(a, aoff+32);
	  }
	  else {
	    slo = reg0;
	    shi = reg1;
	  };
	  ins2(opl, 32, 32, slo, dlo);
	  ins2(opl, 32, 32, shi, dhi);
	};
      };
      invalidate_dest(dest);
      end_contop();
      regsinuse = riu;
      son(a) = holda;
      son(b) = holdb;
      return;
    };

    move(sha, a1, reg0);
    andetc(opb, opw, opl, one, sha, reg0, dest, dest);
    return;
  };

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
      if (eq_where(a1, reg0))
	reg0_in_use = 1;
      move(sha, a2, dest);
      andetc(opb, opw, opl, one, sha, a1, dest, dest);
      return;
    case 4:
      if (eq_where(a2, reg0))
	reg0_in_use = 1;
      move(sha, a1, dest);
      andetc(opb, opw, opl, one, sha, a2, dest, dest);
      return;
    default: 			/* case 6 */
      move(sha, a2, reg0);
      andetc(opb, opw, opl, one, sha, a1, reg0, reg0);
      move(sha, reg0, dest);
      return;
  };

}

void and
(shape sha, where a1, where a2, where dest)
{
  andetc(andb, andw, andl, -1, sha, a1, a2, dest);
}

void or
(shape sha, where a1, where a2, where dest)
{
  andetc(orb, orw, orl, 0, sha, a1, a2, dest);
}

void xor
(shape sha, where a1, where a2, where dest)
{
  andetc(xorb, xorw, xorl, 0, sha, a1, a2, dest);
}


static void needs_lib64
(void)
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
    if (!PIC_code)
      lib64_error = getexp(slongsh, NULL, 1, lib64_error, NULL, 0, 0, cont_tag);
    lib64_set = 1;
  };
}

/*
 * 64-bit multiply a1 by a2, result to reg0/1 arg shapes sh1,
 * sh2 may be 32 or 64-bit proper subset varieties for sha
 */
static void mult64
(shape sha, shape sh1, shape sh2, where a1, where a2)
{
  int riu = regsinuse;	/* we know reg2 not in use */
  exp holda2 = son(a2.where_exp);

  if (shape_size(sh1) == 32) {
    if (shape_size(sh2)!= 32 || (eq_where(a2, reg0) && !eq_where(a1, reg0))) {
      mult64(sha, sh2, sh1, a2, a1);
      return;
    };
    if (eq_where(a1, reg0)) {
      int difsg = (is_signed(sh1)!= is_signed(sh2));
      int lab1, lab2;
      regsinuse |= 0x2;
      contop(a2.where_exp, 1, a2);
      if (name(a2.where_exp) == val_tag) {
	if ((no(a2.where_exp) = a2.where_off) >= 0) {
	  sh2 = sh1;
	  difsg = 0;
	};
	reg0_in_use = 1;
	move(sh2, a2, reg2);
	a2 = reg2;
      };
      if (difsg && is_signed(sh2)) {
	if (inmem(a2)) {
	  ins2(movl, 32, 32, a2, reg2);
	  a2 = reg2;
	};
	ins2(xchg, 32, 32, reg0, reg2);
      };
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
      }
      else
        ins1((is_signed(sh1)? imull : mull), 32, a2);
      end_contop();
      regsinuse = riu;
      son(a2.where_exp) = holda2;
      return;
    };
	/* neither is in reg0 */
    if (is_signed(sh2) && !is_signed(sh1)) {
      mult64(sha, sh2, sh1, a2, a1);
      return;
    };
    if (is_signed(sh1)) {
      if (name(a1.where_exp)!= val_tag) {
	move(sh1, a1, reg0);
	mult64(sha, sh1, sh2, reg0, a2);
	return;
      };
      if ((no(a1.where_exp) + a1.where_off) >= 0 || is_signed(sh2)) {
	move(sh2, a2, reg0);
	mult64(sha, sh2, sh2, reg0, a1);
	return;
      };
	/* otherwise, we are multiplying negative constant by unsigned */
      move(sh1, a1, reg0);
      contop(a2.where_exp, 1, a2);
      if (name(a2.where_exp) == val_tag) {
	reg0_in_use = 1;
	move(sh2, a2, reg2);
	a2 = reg2;
      };
      ins1(mull, 32, a2);
      ins2(subl, 32, 32, a2, reg1);
      end_contop();
      son(a2.where_exp) = holda2;
      return;
    };
	/* both are unsigned */
    if (name(a1.where_exp) == val_tag) {
      move(sh1, a1, reg0);
      mult64(sha, sh1, sh2, reg0, a2);
      return;
    };
    {
      move(sh2, a2, reg0);
      mult64(sha, sh2, sh1, reg0, a1);
      return;
    };
  };

  if (overflow_e != NULL && !optop(overflow_e)) {
				/* need library proc to check for overflow */
    needs_lib64();
    if (eq_where(a1, reg0)) {
      a1 = a2;
      a2 = reg0;
    };
    move(sha, a2, pushdest);
    extra_stack += 64;
    move(sha, a1, pushdest);
    extra_stack -= 64;
    callins(0,(is_signed(sha)? lib64_s_mult : lib64_u_mult), stack_dec);
    add(slongsh, mw(zeroe, 16), sp, sp);
    ins2(movl, 32, 32, mw(lib64_error, 0), reg2);
    if (PIC_code)
      ins2(movl, 32, 32, ind_reg2, reg2);
    ins2(testl, 32, 32, reg2, reg2);
    test_exception(f_greater_than_or_equal, slongsh);
    return;
  };

  if (shape_size(sh2) == 32 || (name(a2.where_exp) == val_tag && !isbigval(a2.where_exp))) {
    if (eq_where(a1, reg0)) {
      reg0_in_use = 1;
      regsinuse |= 0x2;
      move(slongsh, a2, reg2);
    }
    else {
      move(slongsh, a2, reg2);
      regsinuse |= 0x4;
      move(sha, a1, reg0);
    }
    ins0(pushedx);
#ifdef DWARF2
    if (diag == DIAG_DWARF2 && no_frame)
      dw2_track_push();
#endif
    if (is_signed(sha) && is_signed(sh2) &&
	 (name(a2.where_exp)!= val_tag || (no(a2.where_exp) + a2.where_off) < 0)) {
      ins0(pusheax);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_push();
#endif
      ins1(mull, 32, reg2);
      if (name(a2.where_exp)!= val_tag) {
	int lab1 = next_lab();
	ins2(testl, 32, 32, reg2, reg2);
	simple_branch(jns, lab1);
	ins2(subl, 32, 32, ind_sp, reg1);
	simplest_set_lab(lab1);
      }
      else
	ins2(subl, 32, 32, ind_sp, reg1);
      ins2(addl, 32, 32, mw(zeroe,4), sp);
    }
    else
      ins1(mull, 32, reg2);
    ins2(imull, 32, 32, ind_sp, reg2);
    ins2(addl, 32, 32, reg2, reg1);
    ins0(popecx);
#ifdef DWARF2
    if (diag == DIAG_DWARF2 && no_frame)
      dw2_track_pop();
#endif
    regsinuse = riu;
    return;
  };

  if (eq_where(a1, a2)) {
    move(sha, a1, reg0);
    ins0(pushedx);
#ifdef DWARF2
    if (diag == DIAG_DWARF2 && no_frame)
      dw2_track_push();
#endif
    ins2(movl, 32, 32, reg0, reg2);
    ins1(mull, 32, reg0);
    ins2(imull, 32, 32, ind_sp, reg2);
    ins2(addl, 32, 32, reg2, reg1);
    ins2(addl, 32, 32, reg2, reg1);
    ins0(popecx);
#ifdef DWARF2
    if (diag == DIAG_DWARF2 && no_frame)
      dw2_track_pop();
#endif
    return;
  };

  if (eq_where(a2, reg0)) {
    son(a2.where_exp) = holda2;
    a2 = a1;
    holda2 = son(a2.where_exp);
    a1 = reg0;
  };
  move(sha, a1, reg0);
  reg0_in_use = 1;
  regsinuse |= 0x6;
  contop(a2.where_exp, 1, a2);
  ins0(pushedx);
#ifdef DWARF2
  if (diag == DIAG_DWARF2 && no_frame)
    dw2_track_push();
#endif
  extra_stack += 32;
  ins2(movl, 32, 32, reg0, reg2);
  ins1(mull, 32, a2);
  ins2(imull, 32, 32, mw(a2.where_exp, a2.where_off+32), reg2);
  ins2(addl, 32, 32, reg2, reg1);
  ins0(popecx);
#ifdef DWARF2
  if (diag == DIAG_DWARF2 && no_frame)
    dw2_track_pop();
#endif
  extra_stack -= 32;
  ins2(imull, 32, 32, a2, reg2);
  ins2(addl, 32, 32, reg2, reg1);
  end_contop();
  regsinuse = riu;
  son(a2.where_exp) = holda2;
}


static void clean_multiply
(int stored)
{
  if (stored)
   {
      ins0(popedx);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_pop();
#endif
      extra_stack -= 32;
      invalidate_dest(reg1);
   };
}

/*
 * multiply a1 by a2 add inc and put into dest.
 * optimisation has already been done.
 */
void multiply
(shape sha, where a1, where a2, where dest)
{
  int  sz;
  char *in;
  int stored = 0;
  exp hold_a1 = son(a1.where_exp);
  exp hold_a2 = son(a2.where_exp);
  sz = shape_size(sha);

  cond1_set = 0;
  cond2_set = 0;

  if (sz == 64) {
    mult64(sha, sh(a1.where_exp), sh(a2.where_exp), a1, a2);
    move(sha, reg0, dest);
    invalidate_dest(reg0);
    invalidate_dest(reg2);
    return;
  };

  if (sz == 8)
    in = imulb;
  else {
    if (sz == 16)
      in = imulw;
    else
      in = imull;
  };
  invalidate_dest(reg0);
  if (name(a2.where_exp) == val_tag && sz != 8 &&
	(is_signed(sha) || overflow_e == NULL || optop(overflow_e))) {
    	    /* x * const -> y */
    contop(a1.where_exp, eq_where(reg0, a1), dest);
    if (!inmem(dest)) {
        /* x * const -> reg */
      if (name(a1.where_exp) == val_tag) {
	move(sha, a1, dest);
	son(a1.where_exp) = hold_a1;
	a1 = dest;
	hold_a1 = son(a1.where_exp);
      };
      ins3(in, sz, sz, sz, a2, a1, dest);
      invalidate_dest(dest);
      end_contop();
      try_overflow(sha, 0);
      son(a1.where_exp) = hold_a1;
      return;
    };
       /* x * const -> notreg   : use reg0 */
    if (name(a1.where_exp) == val_tag) {
      move(sha, a1, reg0);
      son(a1.where_exp) = hold_a1;
      a1 = reg0;
      hold_a1 =  son(a1.where_exp);
    };
    ins3(in, sz, sz, sz, a2, a1, reg0);
    invalidate_dest(reg0);
    end_contop();
    try_overflow(sha, 0);
    move(sha, reg0, dest);
    son(a1.where_exp) = hold_a1;
    return;
  };

  if (is_signed(sha) && sz != 8) {
      /* signed : we don't have to disturb eax/edx */
    if (!inmem(dest)) {
      if (eq_where(a2, dest)) {
	contop(a1.where_exp,
	    (eq_where(reg0, a1) || eq_where(reg0, a2)),
	    dest);
	ins2(in, sz, sz, a1, dest);
	invalidate_dest(dest);
	end_contop();
        try_overflow(sha, 0);
	son(a1.where_exp) = hold_a1;
	return;
      };
      if (eq_where(a1, dest)) {
	contop(a2.where_exp,
	    (eq_where(reg0, a1) || eq_where(reg0, a2)),
	    dest);
	ins2(in, sz, sz, a2, dest);
	invalidate_dest(dest);
	end_contop();
        try_overflow(sha, 0);
	son(a2.where_exp) = hold_a2;
	return;
      };
    };
    if (eq_where(reg0, a2)) {
      contop(a1.where_exp, 1, reg0);
      ins2(in, sz, sz, a1, reg0);
      invalidate_dest(reg0);
      end_contop();
      try_overflow(sha, 0);
      move(sha, reg0, dest);
      son(a1.where_exp) = hold_a1;
      return;
    };
    move(sha, a1, reg0);
    contop(a2.where_exp, 1, reg0);
    ins2(in, sz, sz, a2, reg0);
    invalidate_dest(reg0);
    end_contop();
    try_overflow(sha, 0);
    move(sha, reg0, dest);
    son(a2.where_exp) = hold_a2;
    return;
  }
  else {
       /* unsigned : use mul which only allows eax edx result */
	/* or signed imulb with same constraint */
    if (!is_signed(sha))
      in = &in[1];
    if ((regsinuse & 0x2) && !eq_where(dest, reg1)) {
      stored = 1;
      ins0(pushedx);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_push();
#endif
      extra_stack += 32;
      check_stack_max;
      invalidate_dest(reg1);
    };
    if (eq_where(reg0, dest)) {
      if (eq_where(a2, reg0)) {
	contop(a1.where_exp, 1, a1);
	if (name(a1.where_exp) == val_tag) {
	  move(sha, a1, reg1);
	  ins1(in, sz, reg1);
	}
	else {
	  ins1(in, sz, a1);
	};
        invalidate_dest(reg0);
        invalidate_dest(reg1);
	invalidate_dest(a1);
	end_contop();
	clean_multiply(stored);
        try_overflow(sha, 0);
	son(a1.where_exp) = hold_a1;
	return;
      };
      if (eq_where(a1, reg0)) {
	contop(a2.where_exp, 1, a2);
	if (name(a2.where_exp) == val_tag) {
	  move(sha, a2, reg1);
	  ins1(in, sz, reg1);
	}
	else {
	  ins1(in, sz, a2);
	};
        invalidate_dest(reg0);
        invalidate_dest(reg1);
	invalidate_dest(a2);
	end_contop();
	clean_multiply(stored);
        try_overflow(sha, 0);
	son(a2.where_exp) = hold_a2;
	return;
      };
    };
    if (eq_where(reg0, a2)) {
      contop(a1.where_exp, 1, a1);
      if (name(a1.where_exp) == val_tag) {
	move(sha, a1, reg1);
	ins1(in, sz, reg1);
      }
      else {
	ins1(in, sz, a1);
      };
      invalidate_dest(a1);
      invalidate_dest(reg0);
      invalidate_dest(reg1);
      end_contop();
      clean_multiply(stored);
      try_overflow(sha, 0);
      move(sha, reg0, dest);
      son(a1.where_exp) = hold_a1;
      return;
    };
    move(sha, a1, reg0);
    contop(a2.where_exp, 1, a2);
    if (name(a2.where_exp) == val_tag) {
      move(sha, a2, reg1);
      ins1(in, sz, reg1);
    }
    else {
      ins1(in, sz, a2);
    };
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
  };
}

#define short_mults 6
int  mtab[short_mults] = {
  25, 15, 9, 7, 5, 3
};

/* do multiplications by small integer constants */
void longc_mult
(where a1, where a2, where dest, int inc)
{
  int  i,
        j;
  int  n = no(a2.where_exp) + a2.where_off;
  shape sha = slongsh;
  exp holdd = son(dest.where_exp);

  if (name(sh(a2.where_exp)) == offsethd && al2(sh(a2.where_exp))!= 1)
     n = n / 8;

  cond1_set = 0;
  cond2_set = 0;

  if (n == 0) {
    move(sha, zero, dest);
    return;
  };

  if (n == 1) {
    move(sha, a1, dest);
    return;
  };


  switch (n) {
    case 2:
      if (inmem(a1)) {
	where newdest;
	newdest = (inmem(dest))? reg0 : dest;
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
      };
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
      };
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
      };
      if (!inmem(a1) && !inmem(dest)) {
	if (!eq_where(a1, reg0)) {
	  contop(dest.where_exp, 1, dest);
	  mult_op(inc, a1, a1, 2, reg0);
	  mult_op(inc, reg0, a1, 4, dest);
	  invalidate_dest(reg0);
	  invalidate_dest(dest);
	  son(dest.where_exp) = holdd;
	  return;
	}
	else  {
	  ins0(pushedx);
#ifdef DWARF2
	  if (diag == DIAG_DWARF2 && no_frame)
	    dw2_track_push();
#endif
	  mult_op(inc, a1, a1, 2, reg1);
	  mult_op(inc, reg1, reg0, 4, dest);
	  invalidate_dest(dest);
	  ins0(popedx);
#ifdef DWARF2
	  if (diag == DIAG_DWARF2 && no_frame)
	    dw2_track_pop();
#endif
	  return;
	};
      };
      if (inmem(a1) && !inmem(dest)) {
	move(sha, a1, reg0);
	longc_mult(reg0, a2, dest, inc);
	return;
      };
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
      };
      contop(dest.where_exp, eq_where(reg0, a1), dest);
      mult_op(inc, a1, a1, 8, dest);
      invalidate_dest(dest);
      son(dest.where_exp) = holdd;
      return;
    case 15: {
        if (!inmem(a1)) {
	  mult_op(inc, a1, a1, 2, reg0);
	}
	else  {
	  move(sha, a1, reg0);
	  mult_op(inc, reg0, reg0, 2, reg0);
	};
	contop(dest.where_exp, 1, dest);
	mult_op(inc, reg0, reg0, 4, dest);
	invalidate_dest(reg0);
	invalidate_dest(dest);
	son(dest.where_exp) = holdd;
	return;
      };
    case 25: {
        if (!inmem(a1)) {
	  mult_op(inc, a1, a1, 4, reg0);
	}
	else  {
	  move(sha, a1, reg0);
	  mult_op(inc, reg0, reg0, 4, reg0);
	};
	contop(dest.where_exp, 1, dest);
	mult_op(inc, reg0, reg0, 4, dest);
	invalidate_dest(reg0);
	invalidate_dest(dest);
	son(dest.where_exp) = holdd;
	return;
      };
    default:
      if ((n & (n - 1)) == 0) {
	int  mask = 1;
	int  c;
	for (c = 0;(mask & n) == 0; ++c)
	  mask += mask;
	shiftl(sha, mw(zeroe, c), a1, dest);
	return;
      };
      if ((-n & (-n - 1)) == 0) {
	int  mask = 1;
	int  c;
	for (c = 0;(mask & -n) == 0; ++c)
	  mask += mask;
	shiftl(sha, mw(zeroe, c), a1, dest);
        negate(sha, dest, dest);
	return;
      };
      for (i = 0; i < short_mults; ++i) {
	if ((n % mtab[i]) == 0) {
	  int  x = n / mtab[i];
	  if ((x & (x - 1)) == 0) {
	    where w;
	    if (inmem(dest))
	      w = reg0;
	    else
	      w = dest;
	    longc_mult(a1, mw(zeroe, mtab[i]), w, 0);
	    longc_mult(w, mw(zeroe, x), dest, inc);
	    return;
	  };
	  for (j = 0; j < short_mults; ++j) {
	    if (x == mtab[j]) {
	      where w;
	      if (inmem(dest))
		w = reg0;
	      else
		w = dest;
	      longc_mult(a1, mw(zeroe, mtab[i]), w, 0);
	      longc_mult(w, mw(zeroe, x), dest, inc);
	      return;
	    };
	  };
	};
      };
      multiply(sha, a1, a2, dest);
      return;
  };
}

/*
 * Multiply a1 by a2 and put into dest.
 * look out for special cases by calling longc_mult
 */
void mult
(shape sha, where a1, where a2, where dest)
{
  int  inc = 0;
  int sha_size = shape_size(sha);
  cond1_set = 0;
  cond2_set = 0;

  if (name(a1.where_exp) == val_tag && sha_size == 32) {
    longc_mult(a2, a1, dest, inc);
    return;
  };

  if (name(a2.where_exp) == val_tag && sha_size == 32) {
    longc_mult(a1, a2, dest, inc);
    return;
  };

  multiply(sha, a1, a2, dest);
}

/*
 * Shift from wshift places to to.
 */
void shiftl
(shape sha, where wshift, where from, where to)
{
  exp p = wshift.where_exp;
  int  places = no(p) + wshift.where_off;
  char *shifter;
  int  sz;
  int sig = is_signed(sha);
  exp holdto = son(to.where_exp);
  sz = shape_size(sha);

  cond1_set = 0;
  cond2_set = 0;

  if (sz == 64) {
    int riu = regsinuse;
    move(sha, from, reg0);
    if (name(wshift.where_exp) == val_tag)
      rotshift64(0, sig, wshift);
    else {	/* need count in reg2 */
      if (regsinuse & 0x4) {
        ins0(pushecx);
#ifdef DWARF2
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_push();
#endif
        extra_stack += 32;
        check_stack_max;
      };
      reg0_in_use = 1;
      regsinuse |= 0x2;
      move(slongsh, wshift, reg2);
      rotshift64(0, sig, wshift);
      invalidate_dest(reg2);
      if (regsinuse & 0x4) {
         ins0(popecx);
#ifdef DWARF2
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_pop();
#endif
         extra_stack -= 32;
      }
    };
    invalidate_dest(reg0);
    invalidate_dest(reg1);
    move(sha, reg0, to);
    regsinuse = riu;
    return;
  }

  switch (sz) {			/* choose shift operation from signedness and length */
    case 8:
      shifter = (sig)? salb : shlb;
      break;
    case 16:
      shifter = (sig)? salw : shlw;
      break;
    default:
      shifter = (sig)? sall : shll;
  };

  if (name (p) == val_tag) {	/* no of places is constant */
    if (places >= 32) {
      move(sha, zero, to);
      return;
    };
    if (places == 0)
      {
        move(sha, from, to);
        return;
      };

    if (places >=1 && places <= 1)	/* correspond to longc_mult */
     {
       int k = 8;
       if (places == 1)
         k = 2;
       if (places == 2)
         k = 4;
       longc_mult(from, mw(zeroe, k), to, 0);
       return;
     };

    if (eq_where (from, to)) {	/* shift in situ */
      contop(to.where_exp, 0, to);
      ins2(shifter, 8, sz, wshift, to);
      invalidate_dest(to);
      end_contop();
      son(to.where_exp) = holdto;
      return;
    };
    if (!inmem (to)) {		/* to is a register */
      move(sha, from, to);
      contop(to.where_exp, 0, to);
      ins2(shifter, 8, sz, wshift, to);
      invalidate_dest(to);
      end_contop();
      son(to.where_exp) = holdto;
      return;
    };
    /* use reg0 to shift in */
    move(sha, from, reg0);
    ins2(shifter, 8, sz, wshift, reg0);
    invalidate_dest(reg0);
    move(sha, reg0, to);
    invalidate_dest(to);
    return;
  };
  {				/* we don't know the number of places */
    int   to_reg2,
          wshift_reg2;
    to_reg2 = eq_where(to, reg2);
    wshift_reg2 = eq_where(wshift, reg2);

    if (!to_reg2 && (regsinuse & 0x4) && !wshift_reg2) {
      ins0(pushecx);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_push();
#endif
      extra_stack += 32;
      check_stack_max;
    };

    /* scan has guaranteed that wshift is not in reg0 */

    change_var(slongsh, from, reg0);
    reg0_in_use = 1;
    move(slongsh, wshift, reg2);

    ins2(shifter, 8, sz, reg2, reg0);
    invalidate_dest(reg0);
    invalidate_dest(reg2);

    if (!to_reg2 && (regsinuse & 0x4) && !wshift_reg2)
     {
       ins0(popecx);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_pop();
#endif
       extra_stack -= 32;
     }

    /* reg2 might be used in the address of to */
    move(sha, reg0, to);
  };

}

/*
 * Shift from wshift places to to.
 */
static void rotshiftr
(int shft, shape sha, where wshift, where from, where to)
{
  exp p = wshift.where_exp;
  int  places = no(p) + wshift.where_off;
  char *shifter;
  int  sz;
  int sig = is_signed(sha);
  exp holdto = son(to.where_exp);
  sz = shape_size(sha);

  cond1_set = 0;
  cond2_set = 0;

  if (sz == 64) {
    int riu = regsinuse;
    move(sha, from, reg0);
    if (name(wshift.where_exp) == val_tag)
      rotshift64(shft+1, sig, wshift);
    else {	/* need count in reg2 */
      if (regsinuse & 0x4) {
        ins0(pushecx);
#ifdef DWARF2
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_push();
#endif
        extra_stack += 32;
        check_stack_max;
      };
      reg0_in_use = 1;
      regsinuse |= 0x2;
      move(slongsh, wshift, reg2);
      rotshift64(shft+1, sig, wshift);
      invalidate_dest(reg2);
      if (regsinuse & 0x4) {
         ins0(popecx);
#ifdef DWARF2
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_pop();
#endif
         extra_stack -= 32;
      }
    };
    invalidate_dest(reg0);
    invalidate_dest(reg1);
    move(sha, reg0, to);
    regsinuse = riu;
    return;
  }

  if (shft == 0) {
    switch (sz) {
      case 8:
        shifter = (sig)? sarb : shrb;
        break;
      case 16:
        shifter = (sig)? sarw : shrw;
        break;
      default:
        shifter = (sig)? sarl : shrl;
    }
  }
  else {
    switch (sz) {
      case 8:
        shifter = (shft == 1)? rorb : rolb;
        break;
      case 16:
        shifter = (shft == 1)? rorw : rolw;
        break;
      default:
        shifter = (shft == 1)? rorl : roll;
    }
  };

  if (name(p) == val_tag) {
    if (places >= 32) {
      if (sig)
	no(p) = 31;
      else {
	move(sha, zero, to);
	return;
      };
    };
    if (eq_where(from, to)) {
      contop(to.where_exp, 0, to);
      ins2(shifter, 8, sz, wshift, to);
      invalidate_dest(to);
      end_contop();
      son(to.where_exp) = holdto;
      return;
    };
    if (!inmem(to)) {
      move(sha, from, to);
      contop(to.where_exp, 0, to);
      ins2(shifter, 8, sz, wshift, to);
      invalidate_dest(to);
      end_contop();
      son(to.where_exp) = holdto;
      return;
    };
    move(sha, from, reg0);
    ins2(shifter, 8, sz, wshift, reg0);
    invalidate_dest(reg0);
    move(sha, reg0, to);
    return;
  };
  {
    int   to_reg2,
          wshift_reg2;
    int selfed = 0;
    to_reg2 = eq_where(to, reg2);
    wshift_reg2 = eq_where(wshift, reg2);

    if (!to_reg2 && (regsinuse & 0x4) && !wshift_reg2) {
      ins0(pushecx);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_push();
#endif
      extra_stack += 32;
      check_stack_max;
    };

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
    }
    else {
      change_var(slongsh, from, reg0);
      reg0_in_use = 1;
      move(slongsh, wshift, reg2);

      ins2(shifter, 8, sz, reg2, reg0);
      invalidate_dest(reg0);
      invalidate_dest(reg2);
    };

    if (!to_reg2 && (regsinuse & 0x4) && !wshift_reg2)
     {
       ins0(popecx);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_pop();
#endif
       extra_stack -= 32;
     }

    /* reg2 might be used in the address of to */
    if (!selfed)
      move(sha, reg0, to);
  };
}

/* shift from wshift places to to. */
void shiftr
(shape sha, where wshift, where from, where to)
{
  rotshiftr(0, sha, wshift, from, to);
}

/* shift from wshift places to to. */
void rotater
(shape sha, where wshift, where from, where to)
{
  rotshiftr(1, sha, wshift, from, to);
}

/* shift from wshift places to to. */
void rotatel
(shape sha, where wshift, where from, where to)
{
  rotshiftr(2, sha, wshift, from, to);
}

/* divide top by bottom and put in dest */
static void divit
(shape sha, where bottom, where top, where dest, int whichdiv, int use_shift)
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
  if (name(sh(top.where_exp)) == offsethd)
    sg = 1;

  if (overflow_e != NULL && !istrap(overflow_e)) {
    if (name(bottom.where_exp)!= val_tag || no(bottom.where_exp) == 0)
      test_zero = 1;
    if (sg && (name(bottom.where_exp)!= val_tag || no(bottom.where_exp) == -1))
      test_ov = 1;
  }

  sz = shape_size(sha);

  cond1_set = 0;
  cond2_set = 0;

  if ((use_shift || !sg) &&
      name(bottom.where_exp) == val_tag && !isbigval(bottom.where_exp) &&
     (v = no(bottom.where_exp), v > 0 && (v & (v - 1)) == 0)) {
    int  c = 0;
    int  m = 1;
    where rw;
    if (name(shb) == offsethd &&
          al2(shb)!= 1)
      v = v / 8;
    while (m != v) {
      ++c;
      m = m << 1;
    };

    if (c == 0) {
      move(sha, top, dest);
      return;
    };

    if (inmem(dest))
      rw = reg0;
    else
      rw = dest;
    move(sha, top, rw);
    switch (sz) {
      case 8:
	ins2((sg)? sarb : shrb, 8, 8, mw(zeroe, c), rw);
	break;
      case 16:
	ins2((sg)? sarw : shrw, 8, 16, mw(zeroe, c), rw);
	break;
      case 64:
	rotshift64 (1, sg, mw (zeroe, c));	/* shift within reg0/reg1 */
	break;
      default: /* case 32 */
	ins2((sg)? sarl : shrl, 8, 32, mw(zeroe, c), rw);
    }
    invalidate_dest(rw);
    if (inmem(dest))
      move(sha, rw, dest);
    return;
  };

  if (sz == 64 && shape_size(shb) == 64 && (
	name(bottom.where_exp)!= val_tag || isbigval(bottom.where_exp) ||
 	no(bottom.where_exp) < 0 || sg)) {
    needs_lib64();
    if (eq_where(top, reg0)) {
      ins2(subl, 32, 32, mw(zeroe, 16), sp);
      extra_stack += 128;
      move(sha, top, mw(ind_sp.where_exp, -128));
      move(sha, bottom, mw(ind_sp.where_exp, -64));
      invalidate_dest(ind_sp);
      extra_stack -= 128;
    }
    else {
      move(sha, bottom, pushdest);
      extra_stack += 64;
      move(sha, top, pushdest);
      extra_stack -= 64;
    }
    callins(0, lib64_div[sg + 2*(whichdiv==1)], stack_dec);
    ins2(addl, 32, 32, mw(zeroe, 16), sp);
    if (overflow_e != NULL && !optop(overflow_e)) {
      ins2(movl, 32, 32, mw(lib64_error, 0), reg2);
      if (PIC_code)
        ins2(movl, 32, 32, ind_reg2, reg2);
      ins2(testl, 32, 32, reg2, reg2);
      test_exception(f_greater_than_or_equal, slongsh);
    }
    move(sha, reg0, dest);
    return;
  };

  if (sz == 8) {
    if (sg)
      change_var(swordsh, top, reg0);
    else
      change_var(uwordsh, top, reg0);
  }
  else
    move(sha, top, reg0);


  if (flinmem(bottom) || (eq_where(bottom, reg1) && sz > 8) || (whichdiv==1 && sg)) {
    d = reg2;
    if (regsinuse & 0x4 && !eq_where(dest, reg2)) {
      /* preserve ecx if necessary */
      r2flag = 1;
      ins0(pushecx);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_push();
#endif
      stack_dec -= 32;
      check_stack_max;
    };
    reg0_in_use = 1;
    if (sz == 64) {
      int riu = regsinuse;
      regsinuse |= 0x2;
      move(shb, bottom, reg2);
      regsinuse = riu;
    }
    else
      move(shb, bottom, reg2);
  };

  if (test_zero) {		/* avoid divide by zero trap */
    IGNORE cmp(shb, d, zero, f_not_equal, NULL);
    if (isov(overflow_e))
      test_exception(f_not_equal, shb);
    else {
      reslab = next_lab();
      simple_branch(je, reslab);
    }
  }

  if (test_ov) {		/* avoid most_neg divide by -1 trap */
    int divlab = next_lab();
    if (reslab == 0)
      reslab = next_lab();
    IGNORE cmp(shb, d, mw(zeroe,-1), f_equal, NULL);
    simple_branch(jne, divlab);
    negate(sha, reg0, reg0);
    simple_branch(jmp, reslab);
    simple_set_label(divlab);
  }

  if (!eq_where(dest, reg1) && regsinuse & 0x2 && sz > 8) {
    r1flag = 1;
    ins0(pushedx);
#ifdef DWARF2
    if (diag == DIAG_DWARF2 && no_frame)
      dw2_track_push();
#endif
    stack_dec -= 32;
    check_stack_max;
    invalidate_dest(reg1);
  };

  if (sg) {			/* signed */
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
	error(ERR_INTERNAL, BADOP);
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
    };
  }
  else {			/* unsigned */
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
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_push();
#endif
	move(slongsh, reg1, reg0);
	ins2(xorl, 32, 32, reg1, reg1);
	ins1(divl, 32, d);
	ins2(xchg, 32, 32, ind_sp, reg0);
	ins1(divl, 32, d);
	ins0(popedx);
#ifdef DWARF2
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_pop();
#endif
	break;
      default:
	ins2(xorl, 32, 32, reg1, reg1);
	ins1(divl, 32, d);
    }
  };
  invalidate_dest(reg0);
  invalidate_dest(reg1);
  invalidate_dest(reg2);

  if (r1flag)
   {
     ins0(popedx);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_pop();
#endif
     stack_dec += 32;
   };

  if (reslab != 0)
    simple_set_label(reslab);

  if (r2flag)
   {
     ins0(popecx);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_pop();
#endif
     stack_dec += 32;
   };

  move(sha, reg0, dest);
}


void div2
(shape sha, where bottom, where top, where dest)
{
  divit(sha, bottom, top, dest, 2, 0);
}

void div1
(shape sha, where bottom, where top, where dest)
{
  divit(sha, bottom, top, dest, 1, 1);
}

void div0
(shape sha, where bottom, where top, where dest)
{
  divit(sha, bottom, top, dest, 0, 1);
}

/*
 * Remainder after dividing top by bottom to dest
 */
static void remit
(shape sha, where bottom, where top, where dest, int whichrem, int use_mask)
{
  int  sz;
  where d;
  int sg = is_signed(sha);
  int r1flag = 0, r2flag = 0;
  int  v;
  int reslab = 0, test_zero = 0, test_ov = 0;
  shape shb = sh(bottom.where_exp);
  d = bottom;
  sz = shape_size(sha);

  if (overflow_e != NULL && !istrap(overflow_e)) {
    if (name(bottom.where_exp)!= val_tag || no(bottom.where_exp) == 0)
      test_zero = 1;
    if (sg && (name(bottom.where_exp)!= val_tag || no(bottom.where_exp) == -1))
      test_ov = 1;
  }

  cond1_set = 0;
  cond2_set = 0;

  if ((use_mask || !sg) &&
      name(bottom.where_exp) == val_tag && !isbigval(bottom.where_exp) &&
     (v = no(bottom.where_exp), v > 0 && (v & (v - 1)) == 0)) {
    /* Use and if possible (Note this is compatible with ANSI C, but not with Ada) */
    int  c = 0;
    int  m = 1;
    while (m != v) {
      ++c;
      m = m << 1;
    };
    and(sha, top, mw(zeroe, lsmask[c]), dest);
    return;
  };

  if (sz == 64 && shape_size(shb) == 64 && (
	name(bottom.where_exp)!= val_tag || isbigval(bottom.where_exp) ||
 	no(bottom.where_exp) < 0 || sg)) {
    needs_lib64();
    if (eq_where(top, reg0)) {
      ins2(subl, 32, 32, mw(zeroe, 16), sp);
      extra_stack += 128;
      move(sha, top, mw(ind_sp.where_exp, -128));
      move(sha, bottom, mw(ind_sp.where_exp, -64));
      extra_stack -= 128;
    }
    else {
      move(sha, bottom, pushdest);
      extra_stack += 64;
      move(sha, top, pushdest);
      extra_stack -= 64;
    }
    callins(0, lib64_rem[sg + 2*(whichrem==1)], stack_dec);
    ins2(addl, 32, 32, mw(zeroe, 16), sp);
    if (overflow_e != NULL && !optop(overflow_e)) {
      ins2(movl, 32, 32, mw(lib64_error, 0), reg2);
      if (PIC_code)
        ins2(movl, 32, 32, ind_reg2, reg2);
      ins2(testl, 32, 32, reg2, reg2);
      test_exception(f_greater_than_or_equal, slongsh);
    }
    move(sha, reg0, dest);
    return;
  };

  if (sz == 8) {
    if (sg)
      change_var(swordsh, top, reg0);
    else
      change_var(uwordsh, top, reg0);
  }
  else
    move(sha, top, reg0);


  if (flinmem(bottom) || (eq_where(bottom, reg1) && sz > 8) || (whichrem==1 && sg)) {
    d = reg2;
    if (regsinuse & 0x4 && !eq_where(dest, reg2)) {
      /* preserve ecx if necessary */
      r2flag = 1;
      ins0(pushecx);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_push();
#endif
      stack_dec -= 32;
      check_stack_max;
    };
    reg0_in_use = 1;
    if (sz == 64) {
      int riu = regsinuse;
      regsinuse |= 0x2;
      move(shb, bottom, reg2);
      regsinuse = riu;
    }
    else
      move(shb, bottom, reg2);
  };

  if (test_zero) {		/* avoid divide by zero trap */
    IGNORE cmp(shb, d, zero, f_not_equal, NULL);
    if (isov(overflow_e))
      test_exception(f_not_equal, shb);
    else {
      reslab = next_lab();
      simple_branch(je, reslab);
    }
  }

  if (test_ov) {		/* avoid most_neg divide by -1 trap */
    int divlab = next_lab();
    if (reslab == 0)
      reslab = next_lab();
    IGNORE cmp(shb, d, mw(zeroe,-1), f_equal, NULL);
    simple_branch(jne, divlab);
    move(sha, zero, reg0);
    simple_branch(jmp, reslab);
    simple_set_label(divlab);
  }

  if (!eq_where(dest, reg1) && regsinuse & 0x2 && sz > 8) {
    r1flag = 1;
    ins0(pushedx);
#ifdef DWARF2
    if (diag == DIAG_DWARF2 && no_frame)
      dw2_track_push();
#endif
    stack_dec -= 32;
    check_stack_max;
    invalidate_dest(reg1);
  };

  if (sg) {			/* signed */
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
	error(ERR_INTERNAL, BADOP);
      default:
	move(slongsh, reg0, reg1);
	ins2(sarl, 32, 32, mw(zeroe, 31), reg1);
	ins1(idivl, 32, d);
    }
    if (whichrem==1) {
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
     };
  }
  else {			/* unsigned */
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
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_push();
#endif
	move(slongsh, reg1, reg0);
	ins2(xorl, 32, 32, reg1, reg1);
	ins1(divl, 32, d);
	ins0(popeax);
#ifdef DWARF2
        if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_pop();
#endif
	ins1(divl, 32, d);
	break;
      default:
	ins2(xorl, 32, 32, reg1, reg1);
	ins1(divl, 32, d);
    }
  };
  if (sz == 8)
    ins0("movb %ah,%al");
  else
  if (sz == 64) {
    move(slongsh, reg1, reg0);
    ins2(xorl, 32, 32, reg1, reg1);
  }
  else
    move(sha, reg1, reg0);
  invalidate_dest(reg0);
  invalidate_dest(reg1);
  invalidate_dest(reg2);


  if (r1flag)
   {
     ins0(popedx);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_pop();
#endif
     stack_dec += 32;
   };

  if (reslab != 0)
    simple_set_label(reslab);

  if (r2flag)
   {
     ins0(popecx);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_pop();
#endif
     stack_dec += 32;
   };

  move(sha, reg0, dest);
}

/* remainder after dividing top by bottom to dest */
void rem2
(shape sha, where bottom, where top, where dest)
{
  remit(sha, bottom, top, dest, 2, 0);
}

/* remainder after dividing top by bottom to dest */
void rem0
(shape sha, where bottom, where top, where dest)
{
  remit(sha, bottom, top, dest, 0, 1);
}

/* remainder after dividing top by bottom to dest */
void mod
(shape sha, where bottom, where top, where dest)
{
  remit(sha, bottom, top, dest, 1, 1);
}

/* move address of from to to */
void mova
(where from, where to)
{
  exp fe = from.where_exp;
  exp holdfe = son(fe);

  cond1_set = 0;
  cond2_set = 0;

  if (name(fe) == reff_tag &&
      name (son (fe)) != ident_tag) {/* add on offset from reff */
    mova(mw(son(fe), from.where_off + no(fe)), to);
    return;
  };

  if (name (to.where_exp) == apply_tag) {	/* pushing */
    if (!PIC_code && name(fe) == cont_tag &&
         name(son(fe))!= ident_tag &&
	(name(son(fe))!= name_tag || !isvar(son(son(fe)))) &&
	((extra_stack == 0 && from.where_off == 0) ||
	  !eq_where(mw(son(fe), 0), sp))) {
      contop(fe, 0, to);
      ins1lit(pushl,  32, mw(son(fe), from.where_off));
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_push();
#endif
      end_contop();
      son(fe) = holdfe;
      return;
    };
    if (!PIC_code &&name(fe) == name_tag &&
        isglob(son(fe)) && isvar(son(fe))) {
      contop(fe, 0, to);
      ins1lit(pushl,  32, from);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_push();
#endif
      end_contop();
      son(fe) = holdfe;
      return;
    };
    mova(from, reg0);
    ins1(pushl,  32, reg0);
#ifdef DWARF2
    if (diag == DIAG_DWARF2 && no_frame)
      dw2_track_push();
#endif
    return;
  };


  if (inmem(to)) {
    mova(from, reg0);
    move(slongsh, reg0, to);
    return;
  };

  if (!PIC_code && name(fe) == name_tag && isvar(son(fe)) &&
      isglob(son(fe))) {
    move(slongsh, from, to);
    return;
  };

  contop(from.where_exp, 0, to);

  if (name(fe) == name_tag && !isvar(son(fe)) && ptno(son(fe)) == reg_pl)
    add(slongsh, mw(fe, 0), mw(zeroe, from.where_off/8), to);
  else
    ins2(leal,  32,  32, from, to);

  invalidate_dest(to);
  end_contop();
  son(fe) = holdfe;
}

int   adjust_pos
(exp e, int nbits)
{
  int   pos;
  UNUSED(nbits);
  pos = no(e)% 8;
  no(e) -= pos;
  return pos;
}

/*
 * Find bit position of bitfield defined by e, and alter e to address
 * the start of the byte.
 */
int   bit_pos_cont
(exp e, int nbits)
{
  if (name(e) == reff_tag ||
      name(e) == name_tag)
    return adjust_pos(e, nbits);

  if (name(e) == ident_tag) {
    if (name(bro(son(e))) == reff_tag)
      return adjust_pos(bro(son(e)), nbits);

    if (name(bro(son(e))) == ident_tag)
      return bit_pos_cont(bro(son(e)), nbits);

    if (name(bro(son(e))) == name_tag &&
	son(bro(son(e))) == e &&
	name(son(e)) == name_tag)
      return bit_pos_cont(son(son(e)), nbits);

    if (name(son(e)) == name_tag)
      return adjust_pos(son(e), nbits);

    return 0;
  };

  error(ERR_INTERNAL, BAD_BIT_OPND);
  return 0;

}

/*
 * Find bit position of bitfield defined by e, and alter e to address the start
 * of the byte. Looks at top level and calls bit_pos_cont to it is a cont or ass
 * (which needs recursive calling)
 */
int   bit_pos
(exp e, int nbits)
{
  if (name(e) == name_tag)
    return adjust_pos(e, nbits);

  if (name(e) == cont_tag || name(e) == ass_tag)
    return bit_pos_cont(son(e), nbits);

  if (name(e) == ident_tag)
    return 0;

  error(ERR_INTERNAL, BAD_BIT_OPND);
  return 0;
}

void mem_to_bits
(exp e, shape sha, where dest, ash stack)
{
  int pos, lsn;
  int nbits = shape_size(sha);
  shape dsh;
  char *rs;
  shape move_sh;

  cond1_set = 0;
  cond2_set = 0;


  dsh = (is_signed(sha))? slongsh : ulongsh;

  pos = bit_pos(e, nbits);

  lsn = 32 - nbits - pos;
  rs = (is_signed(sha))? sarl : shrl;
	/* right shift with sign extension or not */

  if (pos == 0 && (nbits == 8 || nbits == 16)) {
    /* can use byte or word instructions. */
    shape osh;
    exp temp;

    if (nbits == 8) {
      if (is_signed(sha))
	osh = scharsh;
      else
	osh = ucharsh;
    }
    else {
      if (is_signed(sha))
	osh = swordsh;
      else
	osh = uwordsh;
    };

    sh(e) = osh;
    temp = getexp(dsh, NULL, 0, e, NULL, 0, 0, chvar_tag);
    make_code(dest, stack, temp);
    retcell(temp);
    return;
  };

  if ((pos + nbits) <= 8)
    move_sh = scharsh;
  else
    move_sh = slongsh;

  if (!inmem (dest)) {		/* dest is register */
    move (move_sh, mw (e, 0), dest);/* move e to dest */
    if (lsn != 0)
      ins2(shll,  32,  32, mw(zeroe, lsn), dest);
    invalidate_dest(dest);
    /* shift it left to remove unwanted bits */
    if (nbits != 32)
      ins2(rs,  32,  32, mw(zeroe, 32 - nbits), dest);
    /* shift it right to remove unwanted bits and propagate sign if necessary */
    invalidate_dest(dest);
    return;
  };

  move (move_sh, mw (e, 0), reg0);/* move e to reg0 */
  if (lsn != 0)
    ins2(shll,  32,  32, mw(zeroe, lsn), reg0);
  invalidate_dest(reg0);
  /* shift it left to remove unwanted bits */
  if (nbits != 32)
    ins2(rs,  32,  32, mw(zeroe, 32 - nbits), reg0);
  /* shift it right to remove unwanted bits and propagate sign if necessary */
  move (dsh, reg0, dest);/* move to dest */
}

void bits_to_mem
(exp e, exp d, ash stack)
{
  int pos;
  int nbits = shape_size(sh(e));
  int mask, lsn, k;
  where dest;
  shape move_sh;
  dest = mw(d, 0);

  cond1_set = 0;
  cond2_set = 0;

  pos = bit_pos(d, nbits);

  lsn = 32 - nbits - pos;
  mask = msmask[lsn] + lsmask[pos];

  k = lsmask[nbits] << pos;

  if ((pos+nbits) <= 8)
   {
    move_sh = scharsh;
    mask &= 0xff;
    k &= 0xff;
   }
  else
    move_sh = slongsh;

  if (name(e) == int_to_bitf_tag && name(son(e)) == val_tag) {
    if (no(son(e)) == lsmask[nbits]) {
      /* if we are assigning all ones, just or them in */
      or(move_sh, mw(zeroe, k), dest, dest);
      return;
    };
    if (no(son(e)) == 0) {
      /* if we are assigning all ones, just or them in */
      k = ~k;
      if ((pos+nbits) <= 8)
        k &= 0xff;
      and(move_sh, mw(zeroe, k), dest, dest);
      return;
    };
  };

  if (pos == 0 && (nbits == 8 || nbits == 16)) {
    shape osh;

    if (nbits == 8)
      osh = ucharsh;
    else
      osh = uwordsh;
    if (name(e) == int_to_bitf_tag)
     {
	if (name(son(e)) == val_tag) {
	  move(osh, mw(son(e), 0), dest);
	}
	else {
         make_code(reg0, stack, son(e));
         move(osh, reg0, dest);
	};
     }
    else
       move(osh, mw(e, 0), dest);
    return;
  };

  /* mask the bits we are putting in out of the dest */
  if (name (e) != val_tag) {	/* this needs improvement */
    if (name(e) == int_to_bitf_tag)
       make_code(reg0, stack, son(e));
    else
       move(sh(e), mw(e, 0), reg0);
    and(slongsh, mw(zeroe, lsmask[nbits]), reg0, reg0);
    /* mask it to the right size */
    if (pos != 0)
      ins2(shll,  32,  32, mw(zeroe, pos), reg0);
    invalidate_dest(reg0);
    /* shift it into position */
    keep_short = 0;	/* stop use of reg0 by and */
    and(move_sh, mw(zeroe, mask), dest, dest);
    add (move_sh, reg0, dest, dest);/* and add it into the dest */
    return;
  }
  else {
    k = (no(e) & lsmask[nbits]) << pos;
    /* constant bits we are assigning */
    if (k == 0)
      return;			/* if we are assigning zero we don't need anything more */
    move(slongsh, mw(zeroe, k), reg0);
    /* we don't need this move to reg0 since add looks after this better */
    keep_short = 0;
    and(move_sh, mw(zeroe, mask), dest, dest);
    add (move_sh, reg0, dest, dest);/* add into dest */
    return;
  };
}

/*
 * Apply floating point operation op between fstack0 and memory.
 * Reverse arguments of operation if rev.
 */
void fopm
(shape sha, unsigned char op, int rev, where wh)
{
  exp hold = son(wh.where_exp);
  contop(wh.where_exp, 0, reg0);
  if (name (sha) == shrealhd) {	/* floats */
    switch (op) {
      case fplus_tag:
	ins1(fadds,  32, wh);
	end_contop();
	son(wh.where_exp) = hold;
	return;
      case fminus_tag:
	if (rev)
	  ins1(fsubrs,  32, wh);
	else
	  ins1(fsubs,  32, wh);
	end_contop();
	son(wh.where_exp) = hold;
	return;
      case fmult_tag:
	ins1(fmuls,  32, wh);
	end_contop();
	son(wh.where_exp) = hold;
	return;
      case fdiv_tag:
	if (rev)
	  ins1(fdivrs,  32, wh);
	else
	  ins1(fdivs,  32, wh);
	end_contop();
	son(wh.where_exp) = hold;
	return;
      default:
	error(ERR_INTERNAL, BAD_FLOP);
	end_contop();
	son(wh.where_exp) = hold;
	return;
    };
  };

  switch (op) {			/* doubles */
    case fplus_tag:
      ins1(faddl,  64, wh);
      end_contop();
      son(wh.where_exp) = hold;
      return;
    case fminus_tag:
      if (rev)
	ins1(fsubrl,  64, wh);
      else
	ins1(fsubl,  64, wh);
      end_contop();
      son(wh.where_exp) = hold;
      return;
    case fmult_tag:
      ins1(fmull,  64, wh);
      end_contop();
      son(wh.where_exp) = hold;
      return;
    case fdiv_tag:
      if (rev)
	ins1(fdivrl,  64, wh);
      else
	ins1(fdivl,  64, wh);
      end_contop();
      son(wh.where_exp) = hold;
      return;
    default:
      error(ERR_INTERNAL, BAD_FLOP);
      end_contop();
      son(wh.where_exp) = hold;
      return;
  };
}

/*
 * Apply floating point operation op between fstack0 and fstackn.
 * Reverse arguments of operation if rev.
 */
void fopr
(unsigned char op, int rev, where wh, where d, int and_pop)
{
  switch (op) {
    case fplus_tag:
      if (and_pop) {
	ins2(faddp, 0, 0, wh, d);
	pop_fl;
      }
      else
	ins2(fadd, 0, 0, wh, d);
      break;
    case fminus_tag:
      if (rev) {
	if (and_pop) {
	  ins2(fsubrp, 0, 0, wh, d);
	  pop_fl;
	}
	else
	  ins2(fsubr, 0, 0, wh, d);
      }
      else {
	if (and_pop) {
	  ins2(fsubp, 0, 0, wh, d);
	  pop_fl;
	}
	else
	  ins2(fsub, 0, 0, wh, d);
      };
      break;
    case fmult_tag:
      if (and_pop) {
	ins2(fmulp, 0, 0, wh, d);
	pop_fl;
      }
      else
	ins2(fmul, 0, 0, wh, d);
      break;
    case fdiv_tag:
      if (rev) {
	if (and_pop) {
	  ins2 (fdivrp, 0, 0, wh, d);/* (1,arg1-in-st0,arg2,1) -> arg2 */
	  pop_fl;
	}
	else
	  ins2 (fdivr, 0, 0, wh, d); /* (1,arg2,arg1-in-st0,0) -> st0 */
      }
      else {
	if (and_pop) {
	  ins2 (fdivp, 0, 0, wh, d); /* (0,arg2-in-st0,arg1,1) -> arg1 */
	  pop_fl;
	}
	else
	  ins2 (fdiv, 0, 0, wh, d);  /* (0,arg1,arg2-in-st0,0) -> st0 */
      };
      break;
    default:
      error(ERR_INTERNAL, BAD_FLOP);
      break;
  };
}

/*
 * Apply binary floating point operation to arg1 and arg2 and
 * put result into dest
 */
void fl_binop
(unsigned char op, shape sha, where arg1, where arg2, where dest, exp last_arg)
{
  int   m1 = flinmem(arg1);
  int   m2 = flinmem(arg2);
  int   m3 = flinmem(dest);
  int tst = (m1 << 2) + (m2 << 1) + m3;

  if (name(sha) == doublehd && tst > 1)
   {
     move(sha, arg1, flstack);
     move(sha, arg2, flstack);
     switch (op)
      {
        case fplus_tag:
           ins0("faddp %st,%st(1)"); break;
        case fminus_tag:
	   ins0("fsubp %st,%st(1)"); break;
        case fmult_tag:
	   ins0("fmulp %st,%st(1)"); break;
        case fdiv_tag:
	   ins0("fdivp %st,%st(1)"); break;
      };
     pop_fl;
     move(sha, flstack, dest);
     return;
   };

  switch (tst) {
    case 6:
    case 7:
      move(sha, arg2, flstack);
      fopm(sha, op, 0, arg1);

      move(sha, flstack, dest);
      return;
    case 4:
      if (eq_where(arg2, dest)) {
	int  fd = in_fl_reg(dest.where_exp);
	if (fd && get_reg_no(fd) == fstack_pos) {
	  fopm(sha, op, 0, arg1);

	  return;
	};
	move(sha, arg1, flstack);
	fopr (op, 1, flstack, dest, 1); /* 1: fdivrp st,st(2) */

	return;
      };
      /* fall through to case 5 */
    case 5:

      if (use_pop(last_arg, arg2.where_exp) == 2) {
	fopm(sha, op, 0, arg1);

	move(sha, flstack, dest);
	return;
      };

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
	};
	move(sha, arg2, flstack);
	fopr (op, 0, flstack, dest, 1);/* 3: fdivp st,st(2) */

	return;
      };
      /* fall through to case 3 */
    case 3:
      if (use_pop(last_arg, arg1.where_exp) == 2) {
	fopm(sha, op, 1, arg2);

	move(sha, flstack, dest);
	return;
      };

      move(sha, arg2, flstack);
      fopr (op, 0, arg1, flstack, 0); /* 4: fdiv st(2),st */

      move(sha, flstack, dest);
      return;
    case 0:
    case 1:
      {
	int   up1;
	int   up2;
	up1 = use_pop_ass(last_arg, arg1.where_exp);
	up2 = use_pop_ass(last_arg, arg2.where_exp);

	if (tst == 0) {
	  int  fd1 = get_reg_no(in_fl_reg(arg1.where_exp));
	  int  fd2 = get_reg_no(in_fl_reg(arg2.where_exp));

	  if (up1 == 2 && fd2 != fstack_pos && eq_where(arg2, dest)) {
	    fopr(op, 1, flstack, arg2, 1); /* 8: fdivrp st,st(3) */
	    return;
	  };
	  if (up2 == 2 && fd1 != fstack_pos && eq_where(arg1, dest)) {
	    fopr(op, 0, flstack, arg1, 1); /* 11:  fdivp st,st(3) */
	    return;
	  };
	};

	{
	  if (up1 == 2) {
	    int  fd2;
	    fd2 = in_fl_reg(arg2.where_exp);
	    if (get_reg_no(fd2)!= fstack_pos) {
	      if (tst == 0) {
	        fopr (op, 1, arg2, flstack, 0); /* 9: fdivr st(1),st */
	        move(sha, flstack, dest);
	        return;
	      }
	      else
	      if (up2 == 1) {
	        fopr (op, 1, flstack, arg2, 1); /* 7: divrp st,st(1) */
	        move(sha, flstack, dest);
	        return;
	      };
	    };
	  };

	  if (up2 == 2) {
	    int  fd1;
	    fd1 = in_fl_reg(arg1.where_exp);
	    if (get_reg_no(fd1)!= fstack_pos) {
	      if (tst == 0) {
	        fopr (op, 0, arg1, flstack, 0); /* 10: fdiv st(2), st */
	        move(sha, flstack, dest);
	        return;
	      }
	      else
	      if (up1 == 1) {
	        fopr (op, 0, flstack, arg1, 1); /* untested */
	        move(sha, flstack, dest);
	        return;
	      }
	      else {
		fopr(op, 0, arg1, flstack, 0); /* 6: fdiv st(2),st */
		move(sha, flstack, dest);
		return;
	      };
	    };
	  };
	};


	move(sha, arg2, flstack);
	fopr (op, 0, arg1, flstack, 0); /* 5: fdiv st(2),st */

	move(sha, flstack, dest);
	return;
	};


  };
}

/*
 * Apply binary floating point operation to list of arguments arglist and
 * put result into dest
 */
void fl_multop
(unsigned char op, shape sha, exp arglist, where dest)
{
  exp arg1 = arglist;
  exp arg2 = bro(arg1);
  if (last (arg1)) {	/* only one arg, so just move to dest */
    move(sha, mw(arg1, 0), dest);
    return;
  }
  if (last (arg2)) {	/* two args */
    fl_binop(op, sha, mw(arg1, 0), mw(arg2, 0), dest, arg2);
    return;
  }
  move(sha, mw(arg1, 0), flstack);
  for (;;) {
    move(sha, mw(arg2, 0), flstack);
    switch (op)
     {
	case fplus_tag:
	   ins0("faddp %st,%st(1)"); break;
	case fmult_tag:
	   ins0("fmulp %st,%st(1)"); break;
	default:
	   error(ERR_INTERNAL, BAD_FLOP); break;
      };
    pop_fl;
    if (last(arg2))break;
    arg2 = bro(arg2);
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
static  void round_code
(int mode, int ul, int sz)
{
  if (mode == 0 || mode == 4) {
    sub(slongsh, mw(zeroe, sz/8), sp, sp);
    extra_stack += sz;
    check_stack_max;
  }
  else {
    sub(slongsh, mw(zeroe,(sz+32) /8), sp, sp);
    extra_stack += (sz+32);
    check_stack_max;
    ins1(fstcw, size16, mw(ind_sp.where_exp,(- (sz+32))));
    if (ul && mode ==3) {	/* round toward zero unsigned */
      int labpos = next_lab();
      int labend = next_lab();
      ins0(ftst);
      ins1(fnstsw, 16, reg0);
      testah(flpt_test_no[f_less_than]);
      move(swordsh, mw(ind_sp.where_exp,(- (sz+32))), reg0);
      simple_branch(jpe, labpos);
      or (swordsh, mw (zeroe, (mode << 10)), reg0, reg0);  /* neg, round toward zero */
      simple_branch(jmp, labend);
      simplest_set_lab(labpos);
      or (swordsh, mw (zeroe, (1 << 10)), reg0, reg0);  /* pos, round down */
      simplest_set_lab(labend);
    }
    else {
      move(swordsh, mw(ind_sp.where_exp,(- (sz+32))), reg0);
      or(swordsh, mw(zeroe,(mode << 10)), reg0, reg0);
    };
    move(swordsh, reg0, mw(ind_sp.where_exp,(- (sz+16))));
    invalidate_dest(reg0);
    ins1(fldcw, size16, mw(ind_sp.where_exp,(- (sz+16))));
  };
  if (ul) {
    if (sz == 64) {
      move(doublesh, mw(sllmaxe, 0), flstack);
      ins0("fsubrp %st,%st(1)");
      pop_fl;
    }
    else
      ins1(fsubl, size64, mw(smaxe, 0));
  };
  ins0(frndint);
  ins1((sz == 64 ? fistpll : fistpl), sz, mw(ind_sp.where_exp,(-sz)));
  if (mode != 0 && mode != 4) {
    ins1(fldcw, size16, mw(ind_sp.where_exp,(- (sz+32))));
    add(slongsh, mw(zeroe, 4), sp, sp);
    extra_stack -= 32;
  };
  invalidate_dest(ind_sp);
}

static  void roundit
(shape sha, where from, where to, int mode)
{
  shape shfrom = sh(from.where_exp);
  int ul = (name(sha) == ulonghd || name(sha) == u64hd);
  int sz = (shape_size(sha) == 64)? 64 : 32;

  cond1_set = 0;
  cond2_set = 0;

  move(shfrom, from, flstack);

  round_code(mode, ul, sz);
  if (ul) {
    xor(ulongsh, mw(ind_sp.where_exp, -32), mw(zeroe,(int)((unsigned int)1<<31)),
	mw(ind_sp.where_exp, -32));
  }
  pop_fl;
  if (flinmem(to)) {
    move(sha, mw(ind_sp.where_exp, -sz), reg0);
    invalidate_dest(reg0);
    add(slongsh, mw(zeroe, sz/8), sp, sp);
    extra_stack -= sz;
    move(sha, reg0, to);
  }
  else
   {
    move(sha, mw(ind_sp.where_exp, -sz), to);
    add(slongsh, mw(zeroe, sz/8), sp, sp);
    extra_stack -= sz;
   };
}

/* Floating point round */
void frnd0
(shape sha, where from, where to)
{
  roundit(sha, from, to, 0);
}

/* Floating point round */
void frnd1
(shape sha, where from, where to)
{
  roundit(sha, from, to, 1);
}

/* Floating point round */
void frnd2
(shape sha, where from, where to)
{
  roundit(sha, from, to, 2);
}

/* Floating point round */
void frnd3
(shape sha, where from, where to)
{
  roundit(sha, from, to, 3);
}

/* Floating point round */
void frnd4
(shape sha, where from, where to)
{
  roundit(sha, from, to, 4);
}

/* Float the integer from, result to */
void floater
(shape sha, where from, where to)
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
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_push();
#endif
      from = ind_sp;
    }
    else {
      if (szf == 64) {
	ins0(pushedx);
#ifdef DWARF2
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_push();
#endif
	ins0(pusheax);
#ifdef DWARF2
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_push();
#endif
      }
      else {
	ins1(pushl, szf, from);
#ifdef DWARF2
	if (diag == DIAG_DWARF2 && no_frame)
	  dw2_track_push();
#endif
      }
      from = ind_sp;
    };
  };

  holdfe = son(from.where_exp);
  contop(from.where_exp, 0, reg0);
  ins1((szf == 64 ? fildll : fildl), szf, from);
  if (name(shfrom) == ulonghd || name(shfrom) == u64hd) {
    int  lab = next_lab();
    ins2(cmpl, szf, szf, zero, from);
    simple_branch(jge, lab);
    if (szf == 64) {
      move(doublesh, mw(sllmaxe, 0), flstack);
      ins0("faddp %st,%st(1)");
    }
    else
      ins1(faddl, size64, mw(dlongmaxe, 0));
    simple_set_label(lab);
  };
  end_contop();

  if (!im || szf < 32) {
    ins2(addl,  32,  32, mw(zeroe,(szf == 64 ? 8 : 4)), sp);
  };
  push_fl;
  move(sha, flstack, to);
  son(from.where_exp) = holdfe;
}

/*
 * Change floating variety of from to sha, put in to.
 * Shortening change now dealt with by test_fl_ovfl
 */
void changefl
(shape sha, where from, where to)
{
  shape shfrom = sh(from.where_exp);
  if (in_fl_reg (from.where_exp)) {/* from is in a fl reg */
	/* change in case of shortening now dealt with by test_fl_ovfl */
    move (sha, from, to);	/* just move to destination */
    return;
  };

  /* from is not in fl reg */
  move(shfrom, from, flstack);
  move(sha, flstack, to);
}

/* Floating point negate */
void fl_neg
(shape sha, where from, where to)
{
  int  f1 = in_fl_reg(from.where_exp);
  int  f2 = in_fl_reg(to.where_exp);


  if (f1 != 0 && f2 != 0 &&
      get_reg_no(f1) == fstack_pos &&
      get_reg_no(f2) == fstack_pos) {
    ins0(fchs);
    return;
  };
  move(sha, from, flstack);
  ins0(fchs);
  move(sha, flstack, to);
}

/* Floating point abs */
void fl_abs
(shape sha, where from, where to)
{
  int  f1 = in_fl_reg(from.where_exp);
  int  f2 = in_fl_reg(to.where_exp);


  if (f1 != 0 && f2 != 0 &&
      get_reg_no(f1) == fstack_pos &&
      get_reg_no(f2) == fstack_pos) {
    ins0(fabs);
    return;
  };
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
void fl_comp
(shape sha, where pos, where neg, exp e)
{
	/* can improve this to use other comparison instructions */
  cond1_set = 0;
  cond2_set = 0;
  move(sha, neg, flstack);
  move(sha, pos, flstack);
  ins0(fcompp);

  ins1(fnstsw,  16, reg0);

  testah(flpt_test_no[test_number(e)]);

  invalidate_dest(reg0);
  pop_fl;
  pop_fl;
}

/* Use test instruction */
void test
(shape sha, where a, where b)
{
  char *t;
  int  sz;
  exp hold;

  sz = shape_size(sha);

  switch (sz) {
    case 8:
      t = testb;
      break;
    case 16:
      t = testw;
      break;
    default:
      t = testl;
  };

  cond1_set = 0;
  cond2_set = 0;

  if (inmem(a) && inmem(b)) {
    hold = son(b.where_exp);
    move(sha, a, reg0);
    contop(b.where_exp, 1, reg0);
    ins2(t, sz, sz, reg0, b);
    end_contop();
    son(b.where_exp) = hold;
    return;
  };
  if (!inmem(b) && name(a.where_exp)!= val_tag) {
    hold = son(a.where_exp);
    contop(a.where_exp, (eq_where(reg0, a) || eq_where(reg0, b)),
	reg0);
    ins2(t, sz, sz, b, a);
    end_contop();
    son(a.where_exp) = hold;
    return;
  };
  hold = son(b.where_exp);
  contop(b.where_exp, (eq_where(reg0, a) || eq_where(reg0, b)),
      reg0);
  ins2(t, sz, sz, a, b);
  end_contop();
  son(b.where_exp) = hold;
}

/* Decrease the stack */
void decstack
(int longs)
{

  ins2(subl,  32,  32, mw(zeroe,(longs / 8)), sp);
}

void long_jump
(exp e)
{
  UNUSED(e);

  ins0(popebp);
  ins0(ret);
}

static int fp_clear = 0;

void reset_fpucon
(void)
{
  fp_clear = 0;
  if (fpucon == normal_fpucon)
    return;
  if (fpucon & ~normal_fpucon & (int)0xd) {
    ins0(fclex);
    fp_clear = 1;
  }
  if (ferrsize < 32)
    ferrsize = 32;
  ins1(fldcw, 16, mw(ferrmem,0));
  fpucon = normal_fpucon;
}

static void set_fpucon
(int mask, int val)
{
  if ((fpucon & mask) == val)
    return;
  fpucon = ((~mask & fpucon) | val);
  if (ferrsize < 32)
    ferrsize = 32;
  move(uwordsh, mw(zeroe, fpucon), mw(ferrmem, 16));
  ins1(fldcw, 16, mw(ferrmem,16));
}

void setup_fl_ovfl
(exp e)
{
  int traps = 0xd;
  int ival;
  int eprmask = 0x300;
  if (errhandle(e) == 0) {
    if (name(sh(e)) == doublehd)
      set_fpucon(eprmask, eprmask);
    return;
  }
  if (!fp_clear && !optop(e)) {
    ins0(fclex);
    fp_clear = 1;
  }
  ival = (istrap(e)? 0 : traps);
  if (name(sh(e)) == doublehd || name(sh(e)) == s64hd || name(sh(e)) == u64hd)
    set_fpucon((eprmask | traps), (eprmask | ival));
  else
    set_fpucon(traps, ival);
}

void test_fl_ovfl
(exp e, where dest)
{
  int r;
  if (errhandle(e) == 0)
    return;
  r = in_fl_reg(dest.where_exp);
  if (r && (name(sh(e)) == realhd || name(sh(e)) == shrealhd)) {
	/* overflow won't register until stored in memory */
    where m;
    int reqsize = 32 + shape_size(sh(e));
    if (ferrsize < reqsize)
      ferrsize = reqsize;
    m = mw(ferrmem,32);
    if (get_reg_no(r) == fstack_pos && !optop(e)) {
	/* avoid move, which pops the stack */
      if (name(sh(e)) == realhd)
	ins1(fstl, 64, m);
      else
	ins1(fsts, 32, m);
    }
    else {
      move(sh(e), dest, m);
      if (optop(e))		/* replace by suitable value */
	move(sh(e), m, dest);
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
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_push();
#endif
    }
    ins1(fstsw,  16, reg0);
    ins2(testb, 8, 8, mw(zeroe, 13), reg0);
		/* Overflow, Zero divide or Invalid  */
    if (eq_where(dest, reg0)) {
      ins0(popeax);
#ifdef DWARF2
      if (diag == DIAG_DWARF2 && no_frame)
	dw2_track_pop();
#endif
    }
    branch(f_equal, pt(son(pt(e))), 0, scharhd);
    invalidate_dest(reg0);
  };
}

exp find_stlim_var
(void)
{
  return make_extn("__trans386_stack_limit", ulongsh, 1);
}

void checkalloc_stack
(where sz, int b)
{
  /* uses reg1 */
  int erlab = next_lab();
  int cnlab = next_lab();
  if (cont_stacklimit == NULL) {
    cont_stacklimit = make_extn("__trans386_stack_limit", ulongsh, 1);
    if (!PIC_code)
      cont_stacklimit = getexp(ulongsh, NULL, 1, cont_stacklimit, NULL, 0, 0, cont_tag);
  }
  ins2(movl, 32, 32, sp, reg1);
  ins2(subl, 32, 32, sz, reg1);
  simple_branch(jb, erlab);
  if (PIC_code) {
    ins2(movl, 32, 32, mw(cont_stacklimit, 0), reg0);
    ins2(cmpl, 32, 32, ind_reg0, reg1);
    simple_branch(ja, cnlab);
  }
  else {
    ins2(cmpl, 32, 32, mw(cont_stacklimit, 0), reg1);
    simple_branch(ja, cnlab);
  }
  simple_set_label(erlab);
  trap_ins(f_stack_overflow);
  simple_set_label(cnlab);
  if (b)
    ins2(movl, 32, 32, reg1, sp);
}

/*
 * Builtin functions. All args are operands
 */
void special_ins
(char * id, exp arg, where dest)
{
  UNUSED(dest);

  if (!strcmp(id, "__trans386_special") && name(arg) == val_tag) {
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
    };
  }
  error(ERR_INTERNAL, BADOP);
}

void save_stack
(void)
{
  if (extra_stack || stack_dec)
    error(ERR_INTERNAL, "unclean stack");
  ins2(movl, 32, 32, sp, firstlocal);
}

void restore_stack
(void)
{
  if (extra_stack || stack_dec)
    error(ERR_INTERNAL, "unclean stack");
  ins2(movl, 32, 32, firstlocal, sp);
}

void start_asm
(void)
{
  asm_printf("\n");
  asm_comment("ASM sequence start");
}

void end_asm
(void)
{
  asm_printf("\n");
  asm_comment("ASM sequence ends");
}

void asm_ins
(exp e)
{
  if (name(son(e)) == string_tag)
    asm_printf("%s", nostr(son(e)));
  else {
    int prev_use_bp = must_use_bp;
    must_use_bp = 1;	/* scan must ensure !no_frame */
    operand(shape_size(son(e)), mw(son(e), 0), 1, 0);
    must_use_bp = prev_use_bp;
  }
}
