/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <shared/check.h>
#include <shared/error.h>

#include <local/ash.h>

#include <reader/exp.h>
#include <reader/exp.h>
#include <reader/basicread.h>
#include <reader/externs.h>

#include <construct/exp.h>
#include <construct/installglob.h>
#include <construct/shape.h>
#include <construct/flpt.h>
#include <construct/install_fns.h>
#include <construct/tags.h>

#include <main/flags.h>

#include <refactor/optimise.h>

#include "localtypes.h"
#include "assembler.h"
#include "instrs.h"
#include "evaluate.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "peephole.h"
#include "codex.h"
#include "output.h"
#include "tests.h"
#include "utility.h"
#include "where.h"
#include "coder.h"
#include "operations.h"
#include "ops_shared.h"
#include "translate.h"
#include "codec.h"

#include "xdb_basics.h"
#include "xdb_types.h"
#include "xdb_output.h"

#ifndef tdf3
#include "general_proc.h"
#include "68k_globals.h"
#endif

extern bool have_cond;
extern int do_pic;
extern ast add_shape_to_stack(ash, shape);


/*
    SELECT BYTE, WORD OR LONG INSTRUCTION

    opb, opw and opl give the byte, word and long versions of an instruction.
    The appropriate instruction for size sz is returned.
*/

int ins
(long sz, int opb, int opw, int opl)
{
    if (sz <= 8) return opb;
    if (sz <= 16) return opw;
    if (sz <= 32) return opl;
    error(ERROR_SERIOUS, "Illegal instruction size");
    return opl;
}


/*
    SELECT SINGLE OR DOUBLE FLOATING-POINT INSTRUCTION

    ops and opd give the single and double precision versions of an
    instruction.  The appropriate instruction for size sz is returned.
*/

int insf
(long sz, int ops, int opd, int opx)
{
    if (sz == 32) return ops;
    if (sz == 64) return opd;
    error(ERROR_SERIOUS, "Illegal instruction size");
    return opx;
}


/*
    ADD A CONSTANT TO AN ADDRESS REGISTER

    This routine is used primarily for updating the stack.  It adds d
    to the A-register with number r.
*/

void add_to_reg
(int r, long d)
{
    if (d) {
	int instr;
	mach_op *op1;
	mach_op *op2 = make_register(r);
	if (d > 0 && d <= 8) {
	    instr = m_addql;
	    op1 = make_value(d);
	} else if (d < 0 && d >= -8) {
	    instr = m_subql;
	    op1 = make_value(-d);
	} else {
	    instr = m_lea;
	    op1 = make_indirect(r, d);
	}
	make_instr(instr, op1, op2, regmsk(r));
	have_cond = 0;
    }
    return;
}


/*
    CHECK RESERVED NAMES

    This routine returns 1 if nm is a name reserved by the linker.
*/

bool reserved
(char *nm)
{
    int i;
    static char *rn[] = {
	"_edata", "_etext", "_end", "__edata", "__etext", "__end"
    };
    for (i = 0; i < array_size(rn); i++) {
	if (eq(nm, rn[i])) return 1;
    }
    return 0;
}


/*
    STACK INFORMATION

    A number of variable are used to represent the state of the stack.
    used_stack is true to indicate that space has been allocated for
    variables on the stack or that alloca is used in the current
    procedure (the latter is also indicated by has_alloca) or that
    we are in diagnostics mode.  It forces the use of the application
    pointer instead of the stack pointer.  max_stack gives the amount
    of space allocated on the stack.

    stack_dec and stack_size are both used to keep track of changes
    to the stack pointer due to pushes and pops etc.

    extra_stack is used in coder for working out the position of
    procedure arguments which are compound results of procedure calls.

    ldisp is the extra value which needs to be added to the stack pointer
    to reference procedure arguments.  Its value is not known until the
    entire procedure has been coded, so a special label is used to
    represent its value during the procedure coding.  used_ldisp is
    true to indicate that this special label has been used.
*/

bool used_stack = 0;
long max_stack = 0;
long stack_dec = 0;
long stack_size = 0;
long extra_stack = 0;
bool used_ldisp = 0;
long ldisp = 0;


/*
    PENDING STACK DISPLACEMENT

    Consecutive changes to the stack pointer are combined whenever
    possible.  stack_change gives the current amount of change which
    has not been output as an instruction.
*/

long stack_change = 0;
int stack_direction = 0;


/*
    DECREASE THE STACK

    This routine decreases the stack pointer by d bits.
*/

void dec_stack
(long d)
{
    if (d) {
	stack_change -= d;
	stack_direction = (d > 0 ? 1 : 0);
	have_cond = 0;
#ifndef NDEBUG
        update_stack();
#endif
    }
    return;
}


/*
    OUTPUT STACK DISPLACEMENT

    This routine outputs any accummulated stack changes.
*/

void update_stack
(void)
{
    if (stack_change) {
	long d = stack_change / 8;
	stack_size += stack_change;
	stack_change = 0;
	add_to_reg(REG_SP, d);
    }
    return;
}


/*
    CHANGE DATA AREA

    This routine changes the current address area.  p can be one of
    the values ptext, pdata or pbss given in codex.h.
*/

void area
(int p)
{
    static int current_area = -1;
    static int previous_area = -1;
    if (p == plast)p = previous_area;
    if (p != current_area) {
	int i;
	switch (p) {
	    case ptext: i = m_as_text; break;
	    case pdata: i = m_as_data; break;
	    case pbss: i = m_as_bss; break;
	    default : i = m_dont_know; break;
	}
	make_instr(i, NULL, NULL, 0);
	previous_area = current_area;
	current_area = p;
    } else {
	previous_area = current_area;
    }
    return;
}


/*
    OUTPUT A LIBRARY CALL

    A call of the library routine with name nm is output.
*/

void libcall
(char *nm)
{
    mach_op *p = make_extern_data(nm, 0);
    /* nb. float_to_unsigned was a macro, and not defined for -D SUN */
#if 0 /*float_to_unsigned*/
    int lab;
    if ((have_overflow() || have_continue()) && !strcmp(nm,float_to_unsigned)) {
      /* we need to ensure that the value in %fp0 is not outside the valid
	 range for an unsigned int, otherwise there will be a floating
	 point exception in the library routine. */
      bool sw;
      exp e = getexp(ulongsh,NULL,0,NULL,NULL,0,1333788672,val_tag);
      exp loc = sim_exp(shrealsh,FP1);
      lab = (have_continue())?next_lab(): overflow_jump;
      ins2(m_fmoves,shape_size(shrealsh),shape_size(shrealsh),zw(e),zw(loc));
      /*move(ulongsh,zw(e),zw(loc));  */
      sw = cmp(shrealsh,FP0,FP1,tst_gr);

      make_jump(branch_ins(tst_gr,sw,0,1),lab);
      kill_exp(e,e);
    }
#endif

    make_instr(m_call, p, NULL, ~save_msk);
    no_calls++;
#if 0
    if (have_continue() && !strcmp(nm,float_to_unsigned)) {
      make_label(lab);
    }
#endif
    have_cond = 0;
    return;
}


/*
    REGISTER MASKS

    regsinuse gives all the registers which are currented allocated
    values.  regsinproc is a cummulative record of all the registers
    which have been used in the current procedure.  reuseables is
    the record of all the current active reuseable registers.  bigregs
    records all registers in the current procedure which span procedure
    calls.
*/

bitpattern regsinuse;
bitpattern regsinproc;
bitpattern reuseables;
bitpattern regsindec;
bitpattern bigregs;


/*
    OTHER VARIABLES

    crt_ret_lab is a label number assigned to the return sequence of
    the current procedure.  just_ret is set to be true if the return
    sequence just consists of a single rts instruction.  no_calls
    records the number of procedure calls in the current procedure.
*/

long crt_ret_lab = 0;
bool just_ret = 0;
int no_calls = 0;


/*
    PROLOGUE POSITIONS

    This records the position of the prologue of the current procedure.
*/

mach_ins *prologue_ins;


/*
    GENERAL PURPOSE PROCEDURE PROLOGUE

    There are two cases.  If output_immediately is false then the
    prologue is not inserted until the end of the procedure.  Otherwise
    a number of special labels are used to represent values which will
    not be known until the end of the procedure.
*/

void prologue
(void)
{
    mach_op *op1, *op2;
    have_cond = 0;
    just_ret = 1;
    if (!output_immediately) {
	/* Just record position in this case */
	prologue_ins = current_ins;
	return;
    }
    /* Output generalized link and push instructions */
    op1 = make_register(REG_AP);
    op2 = make_special("PA");
    make_instr(m_linkl, op1, op2, 0);
    op1 = make_special("PB");
    op2 = make_indirect(REG_SP, 0);
    make_instr(m_moveml, op1, op2, 0);
    op1 = make_special("PC");
    op2 = make_indirect(REG_AP, 0);
    op2->of->plus = make_special("PD");
    make_instr(m_fmovemx, op1, op2, 0);
    return;
}


/*
    GENERAL PURPOSE PROCEDURE EPILOGUE

    The registers used in the procedure and the space used on the stack
    are analysed and used to form the procedure epilogue.  If
    output_immediately is false then we go back and fill in the
    prologue.  Otherwise the values of the special labels used in the
    prologue are output.  There is some testing to see if D1, A0, A1
    and FP1 can be put to better use.
*/

void epilogue
(int restore_only)
{
    int r;
    bitpattern m;
    long st, st1;
    mach_op *op1, *op2;

    int push_all = 0, use_link = 0;
    int tmp_d1 = -1, tmp_a0 = -1, tmp_a1 = -1;

    bitpattern rmsk = regs(regsinproc & save_msk);
    bitpattern smsk = rmsk;
    bitpattern cmsk = 0;
    bitpattern fmsk = 0;
    bitpattern fsmsk = fregs(regsinproc & save_msk);

    reset_round_mode();  /* restore the default floating point rounding mode */

    for (r = REG_FP7, m = 1; r >= REG_FP2; r--, m <<= 1) {
	if (regsinproc & regmsk(r))fmsk |= m;
    }

    if (no_calls) {
	smsk &= ~bigregs;
	fsmsk &= ~bigregs;
    }
    if (!restore_only) {
      make_label(crt_ret_lab);
    }

    if (diag != DIAG_NONE) xdb_diag_proc_return();

    if (!output_immediately) {
	bool d1_free = 0;

	/* Use D1 if not already used */
	if (!(regsinproc & regmsk(REG_D1))) {
	    m = smsk & dreg_msk;
	    if (m) {
		/* Replace a used D-register by D1 */
		r = reg(m);
		reg_names[r] = reg_names[REG_D1];
		rmsk &= ~regmsk(r);
		smsk &= ~regmsk(r);
		cmsk |= regmsk(r);
	    } else {
		d1_free = 1;
	    }
	}

	/* Use A0 if not already used */
	if (!(regsinproc & regmsk(REG_A0))) {
	    m = smsk & areg_msk;
	    if (m) {
		/* Replace a used A-register by A0 */
		r = reg(m);
		reg_names[r] = reg_names[REG_A0];
		rmsk &= ~regmsk(r);
		smsk &= ~regmsk(r);
		cmsk |= regmsk(r);
	    } else if (no_calls == 0) {
		m = rmsk & dreg_msk;
		if (m) {
		    /* Move a used D-register into A0 */
		    tmp_a0 = reg(m);
		    rmsk &= ~regmsk(tmp_a0);
		    smsk = rmsk;
		    op1 = make_register(REG_A0);
		    op2 = make_register(tmp_a0);
		    make_instr(m_movl, op1, op2, regmsk(tmp_a0));
		    just_ret = 0;
		}
	    }
	}

	/* Use A1 if not already used */
	if (!(regsinproc & regmsk(REG_A1))) {
	    m = smsk & areg_msk;
	    if (m) {
		/* Replace a used A-register by A1 */
		r = reg(m);
		reg_names[r] = reg_names[REG_A1];
		rmsk &= ~regmsk(r);
		smsk &= ~regmsk(r);
		cmsk |= regmsk(r);
	    } else if (no_calls == 0) {
		m = rmsk & dreg_msk;
		if (m) {
		    /* Move a used D-register into A1 */
		    tmp_a1 = reg(m);
		    rmsk &= ~regmsk(tmp_a1);
		    smsk = rmsk;
		    op1 = make_register(REG_A1);
		    op2 = make_register(tmp_a1);
		    make_instr(m_movl, op1, op2, regmsk(tmp_a1));
		    just_ret = 0;
		}
	    }
	}

	/* Use FP1 if not already used */
	if (!(regsinproc & regmsk(REG_FP1))) {
	    for (r = REG_FP7, m = 1; r >= REG_FP2; r--, m <<= 1) {
		if (fsmsk & regmsk(r)) {
		    reg_names[r] = reg_names[REG_FP1];
		    fmsk &= ~m;
		    fsmsk &= ~regmsk(r);
		    cmsk |= regmsk(r);
		    r = REG_FP1;
		}
	    }
	}

	if (d1_free && no_calls == 0) {
	    m = rmsk & areg_msk;
	    if (m) {
		/* Move a used A-register into D1 */
		tmp_d1 = reg(m);
		rmsk &= ~regmsk(tmp_d1);
		op1 = make_register(REG_D1);
		op2 = make_register(tmp_d1);
		make_instr(m_movl, op1, op2, regmsk(tmp_d1));
		just_ret = 0;
	    }
	}

    }

    /* Calculate stack displacements */
/* todo use symbol instead of number */
    st1 = round(max_stack, 32) / 8 + 16 * bits_in(fmsk);
    st = st1 + 4 * bits_in(rmsk);
    if (st1 || used_stack || !push_all || output_immediately)use_link = 1;

    /* Remove floating-point registers from the stack */
    if (fmsk) {
	just_ret = 0;
	op1 = make_indirect(REG_AP, -st1);
	op2 = make_hex_value(fmsk);
	make_instr(m_fmovemx, op1, op2, 0);
    }

    /* Remove registers from the stack */
    if (rmsk) {
	just_ret = 0;
	if (push_all) {
	    for (r = REG_AP - 1; r > REG_D1; r--) {
		if (rmsk & regmsk(r)) {
		    op1 = make_inc_sp();
		    op2 = make_register(r);
		    make_instr(m_movl, op1, op2, regmsk(r));
		}
	    }
	} else {
	    if (must_use_bp) {
		op1 = make_indirect(REG_AP, -st);
	    } else {
		op1 = make_indirect(REG_SP, 0);
	    }
	    op2 = make_hex_value(rmsk);
	    make_instr(m_moveml, op1, op2, rmsk);
	    just_ret = 0;
	}
    }

    /* Output unlink instruction */
    if (use_link) {
	just_ret = 0;
	op1 = make_register(REG_AP);
	make_instr(m_unlk, op1, NULL, 0);
    }
    if (!restore_only) {
      /* Output return instruction */
      make_instr(m_rts, NULL, NULL, 0);
    }

    if (output_immediately) {

	/* Output stack displacement value */
	if (used_ldisp) {
	    op1 = make_int_data(use_link ? st + 4 : st);
	    set_special("S", op1);
	}

	/* Output values used in prologue */
	just_ret = 0;
	op1 = make_int_data(-st);
	set_special("PA", op1);
	op1 = make_hex_data(rmsk);
	set_special("PB", op1);
	op1 = make_hex_data(fmsk);
	set_special("PC", op1);
	op1 = make_int_data(-st1);
	set_special("PD", op1);

    } else if (!restore_only) {

	/* Go back to the prologue position */
	mach_ins *p = current_ins;
	current_ins = prologue_ins;

        cur_proc_env_size = ldisp = (use_link ? st + 4 : st);

	/* Output link instruction */
	if (use_link) {
	    long c = (push_all ? -st1 : -st);
	    int i = (c < -0x7fff ? m_linkl : m_linkw);
	    op1 = make_register(REG_AP);
	    op2 = make_value(c);
	    make_instr(i, op1, op2, 0);
	}

	/* Save register in D1 if necessary */
	if (tmp_d1 >= 0) {
	    op1 = make_register(tmp_d1);
	    op2 = make_register(REG_D1);
	    make_instr(m_movl, op1, op2, regmsk(REG_D1));
	}

	/* Save register in A0 if necessary */
	if (tmp_a0 >= 0) {
	    op1 = make_register(tmp_a0);
	    op2 = make_register(REG_A0);
	    make_instr(m_movl, op1, op2, regmsk(REG_A0));
	}

	/* Save register in A1 if necessary */
	if (tmp_a1 >= 0) {
	    op1 = make_register(tmp_a1);
	    op2 = make_register(REG_A1);
	    make_instr(m_movl, op1, op2, regmsk(REG_A1));
	}

	/* Put registers onto the stack */
	if (rmsk) {
	    if (push_all) {
		for (r = REG_D1 + 1; r < REG_AP; r++) {
		    if (rmsk & regmsk(r)) {
			op1 = make_register(r);
			op2 = make_dec_sp();
			make_instr(m_movl, op1, op2, 0);
		    }
		}
	    } else {
		op1 = make_hex_value(rmsk);
		op2 = make_indirect(REG_SP, 0);
		make_instr(m_moveml, op1, op2, 0);
	    }
	}

	/* Put floating-point registers onto the stack */
	if (fmsk) {
	    op1 = make_hex_value(fmsk);
	    op2 = make_indirect(REG_AP, -st1);
	    make_instr(m_fmovemx, op1, op2, 0);
	}

	/* Return to previous position */
	current_ins = p;
    }
    callmsk = cmsk;
    have_cond = 0;
    return;
}


/*
    PROFILING

    In order for prof and gprof to work, we need to associate four bytes
    of data with each procedure and make the first two lines of the
    procedure move the address of these bytes into the A0 register and
    call mcount.  Unfortunately mcount uses A1 so, if the procedure returns
    a complex result, the address where we are meant to put it, which was
    in A1, is lost.  cc doesn't take account of this, and so can go
    wrong under these circumstances.  I instead call a dummy routine,
    Lmcount, given below, which stores the value of A1 and then jumps to
    mcount, and restore the value of A1 afterwards.

			text
		Lmcount:
			mov.l	%a1, Lmstore
			jmp.l	mcount
			data
		Lmstore:
			long	0

    The flag used_my_mcount is set to be true if Lmcount is used.
*/

static bool used_my_mcount = 0;


/*
    OUTPUT PROFILING DATA

    This routine outputs the profiling data for a procedure.  If save_a1
    is true, the alternative profiling routine is used.
*/

void out_profile
(bool save_a1)
{
    exp z;
    mach_op *op1, *op2;
    /* Make a new label */
    long lb = next_lab();

    switch (abi) {
    case ABI_NEXT:
    case ABI_SUNOS: /* probably wrong */
	op1 = make_lab_data(lb, 0);
	op2 = make_register(REG_A0);
	make_instr(m_lea, op1, op2, regmsk(REG_A0));
	break;

    case ABI_HPUX:
	op1 = make_lab(lb, 0);
	op2 = make_register(REG_A0);
	make_instr(m_movl, op1, op2, regmsk(REG_A0));
	break;
    }

    if (save_a1) {
	/* Call dummy version of mcount - see below */
	libcall("Lmcount");
	/* Restore the value of A1 */
	op1 = make_extern_ind("Lmstore", 0);
	op2 = make_register(REG_A1);
	make_instr(m_movl, op1, op2, regmsk(REG_A1));
	used_my_mcount = 1;
    } else {
	/* Call mcount */
	switch (abi) {
	case ABI_HPUX:  libcall("mcount"); break;
	case ABI_NEXT:  libcall("mcount"); break;
	case ABI_SUNOS: libcall("mcount"); break; /* probably wrong */
	}
    }

    /* Set up the label to point to 0 */
    z = simple_exp(val_tag);
    sh(z) = slongsh;
    make_constant(lb, z);
    return;
}


/*
    OUTPUT ALTERNATIVE PROFILING ROUTINE

    This routine outputs the alternative profiling routine Lmcount
    described above if it is required.
*/

void profile_hack
(void)
{
    mach_op *op1, *op2;
    if (!used_my_mcount) return;
    area(ptext);
    make_external_label("Lmcount");
    op1 = make_register(REG_A1);
    op2 = make_extern_ind("Lmstore", 0);
    make_instr(m_movl, op1, op2, 0);
    switch (abi) {
    case ABI_HPUX:  op1 = make_extern_data("mcount", 0); break;
    case ABI_NEXT:  op1 = make_extern_data("mcount", 0); break;
    case ABI_SUNOS: op1 = make_extern_data("mcount", 0); break;
    }
    make_instr(m_jmp, op1, NULL, 0);
    area(pdata);
    make_external_label("Lmstore");
    op1 = make_int_data(0);
    make_instr(m_as_long, op1, NULL, 0);
    return;
}

#if 0
/*
    ENCODE A PROCEDURE

    This routine encodes a procedure call.  The procedure is named pname
    with oname as an alternative (used with diagnostics).  The actual
    body of the procedure is p.
*/

void cproc
(exp p, char *pname, long cname, int is_ext, int reg_res, diag_global *di)
{
    exp t;
    ash stack;
    ash param_pos;
    mach_op *op1, *op2;
    static long crt_proc_no = 0;

#ifndef tdf3
    cur_proc_has_tail_call = 0;
    cur_proc_use_same_callees = 0;
    scan2(1, p, p);
    comp_weights(p);
#endif

    /* Set up flags, register masks, stack etc. */
    bigregs = 0;
    crt_ret_lab = next_lab();
    extra_stack = 0;
    have_cond = 0;
    max_stack = 0;
    no_calls = 0;
    regsinproc = 0;
    regsinuse = 0;
    reuseables = 0;
    regsindec = 0;
    stack = 0;
    special_no = crt_proc_no++;
    stack_dec = 0;
    stack_size = 0;
    used_ldisp = 0;
    used_stack = diag != DIAG_NONE || must_use_bp;

    /* Mark procedure body */
    ptno(p) = par_pl;
    no(p) = 0;

    /* Mark procedure parameters */
    param_pos = 0;
    t = son(p);
    while (name(t) == ident_tag && isparam(t)) {
	ast a;
	a = add_shape_to_stack(param_pos, sh(son(t)));
	ptno(t) = par_pl;
	no(t) = a.astoff + a.astadj;
	param_pos = a.astash;

        make_visible(t);

	t = bro(son(t));
    }

    /* Output procedure name(s) */
    area(ptext);
    if (!no_align_directives) {
      make_instr(m_as_align4, NULL, NULL, 0);
    }
    if (is_ext && pname) {
	if (strcmp(pname, "_cmppt") == 0) {
	    /* Hack to get alignments right */
	    make_instr(m_nop, NULL, NULL, 0);
	    make_instr(m_nop, NULL, NULL, 0);
	}
	op1 = make_extern_data(pname, 0);
	make_instr(m_as_global, op1, NULL, 0);
    }
    if (cname == -1) {
	make_external_label(pname);
    } else {
	make_label(cname);
    }

    /* Output profiling information if required */
    if (do_profile) {
	out_profile(!reg_res);
	used_stack = 1;
    }

    /* Set up procedure prologue */
    prologue();

    /* Output PIC prologue if necessary */
    if (do_pic && proc_uses_external(p)) {
	regsinproc |= regmsk(REG_A5);
	regsinuse |= regmsk(REG_A5);
	bigregs |= regmsk(REG_A5);
	op1 = make_indirect(REG_PC, 0);
	op1->of->plus = make_extern_data("_GLOBAL_OFFSET_TABLE_@GOTPC", 0);
	op2 = make_register(REG_A5);
	make_instr(m_lea, op1, op2, regmsk(REG_A5));
    }

    /* Diagnostics for start of procedure */
    if (diag != DIAG_NONE && di)xdb_diag_proc_begin(di, p, pname, cname, is_ext);

    /* Allow for procedures which return compound results */
    if (!reg_res) {
	/* Save A1 on the stack */
	ast newstack;
	newstack = add_shape_to_stack(stack, slongsh);
	stack = newstack.astash;
	max_stack = 32;
	used_stack = 1;
	op1 = make_register(REG_A1);
	op2 = make_indirect(REG_AP, -4);
	make_instr(m_movl, op1, op2, 0);
    }

    /* Encode the procedure body */
    if (diag != DIAG_NONE) {
	dnt_begin();
	coder(zero, stack, t);
	dnt_end();
    } else
      coder(zero, stack, t);

    /* Output the procedure epilogue */
#ifndef tdf3
    general_epilogue(0, 0);
#else
    epilogue(0);
#endif
    /* Apply peephole optimizations and return */
    if (optim & OPTIM_PEEPHOLE)peephole();

    /* Diagnostics for end of procedure */
    if (diag != DIAG_NONE && di)xdb_diag_proc_end(di);
    return;
}

#endif
