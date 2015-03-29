/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * This is the principal code producing module
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/string.h>
#include <shared/xalloc.h>

#include <local/szs_als.h>
#include <local/ash.h>
#include <local/tag.h>

#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/exp.h>
#include <reader/externs.h>
#include <reader/basicread.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/ash.h>
#include <construct/exp.h>
#include <construct/shape.h>
#include <construct/install_fns.h>

#include <flpt/flpt.h>

#include <main/driver.h>
#include <main/flags.h>
#include <main/print.h>

#include <diag3/diag_fns.h>
#include <diag3/diag_reform.h>

#include <symtab/syms.h>

#include "addrtypes.h"
#include "make_code.h"
#include "maxminmacs.h"
#include "procrectypes.h"
#include "eval.h"
#include "move.h"
#include "operators.h"
#include "pseudo.h"
#include "getregs.h"
#include "guard.h"
#include "locate.h"
#include "code_here.h"
#include "inst_fmt.h"
#include "alpha_ins.h"
#include "handle_sregs.h"
#include "bitsmacs.h"
#include "labels.h"
#include "regexps.h"
#include "special.h"
#include "main.h"
#include "dump_distr.h"
#include "frames.h"
#include "reg_defs.h"
#include "cross.h"
#include "regable.h"
#include "stabs_diag3.h"
#include "outofline.h"
#include "out_ba.h"
#include "float.h"
#include "translate.h"
#include "localexpmacs.h"

int fscopefile;	/* file of current proc */

/*extern void add_odd_bits(outofline*);*/

int use_umulh_for_div;
bool fail_with_denormal_constant;
bool treat_denorm_specially;

static ans procans;
static int rscope_level;
static int rscope_label;
static int result_label = 0;
static long max_args;

static baseoff procbase = {
	RA, 0L
};

static flt alpha_word_max = { { 32768, 0, 0, 0, 0, 0, 0, 0 }, 1, 0 };
static flt alpha_long_max = { {     1, 0, 0, 0, 0, 0, 0, 0 }, 1, 2 };
static flt alpha_quad_max = { {     1, 0, 0, 0, 0, 0, 0, 0 }, 1, 4 };

where nowhere;
int stack_top;
int arg_stack_space = 0;

static int paramsdumpstart;
static int gpdumpstart;

static exp crt_proc;

static int use_andcomp = 0;
int in_general_proc = 0;
static int in_vcallers_apply = 0;
static int aritherr_lab = 0;
static int stackerr_lab = 0;

static int testrev[] = {
	4, 3, 2, 1, 6, 5
};
/*
outofline *odd_bits;
int doing_odd_bits;
*/

/* put register number 'Reg' back into the current space. */
#define replace_reg(Reg, Space) ((Space) & ~(1 << (Reg)))

#define fix_parameter_size(X, Y) if ((Y) == 32) { \
	operate_fmt_immediate(i_addl,X,0,X);\
}

#define error_treatment_is_trap(e) ((errhandle(e) & 3) == 3)

/*
 * Return true if the floating point number is zero and false otherwise.
 */
static bool
is_fzero(flt fnum)
{
	int i;

	for (i = 0; (i < MANT_SIZE) && (fnum.mant[i] == 0); ++i)
		;

	return i == MANT_SIZE;
}

/*
 * Functions to handle the 'trap' exception handling mechanism.
 */
static int
trap_label(exp e)
{
	if (!error_treatment_is_trap(e)) {
		return no(son(pt(e)));
	}

	if (aritherr_lab == 0) {
		aritherr_lab = new_label();
	}

	return aritherr_lab;
}

static void
do_exception(int ex)
{
	baseoff b;

	load_store_immediate(i_ldiq, FIRST_INT_ARG,  ex);
	setnoat();
	/*  b = find_tag("__TDFhandler");*/
	b = find_tag("__alpha_errhandler");
	load_store(i_ldq, AT, b);
	operate_fmt(i_bis, AT, AT, PV);
	b.base = AT;
	b.offset = 0;
	integer_jump(i_jmp, 31, AT, 0);
	setat();
}

/*
 * Check that the floating point register contains a non-negative value
 * and, if it does, convert to signed by adding the appropriate constant.
 */
static void
fix_unsigned(freg fr, space sp, int name)
{
	space nsp;
	int ftmp;
	freg newfr;
	ans aa;
	flpt fltval;
	exp float_exp;
	instore isa;
	where dest;
	flt constval;

	nsp = guardfreg(fr.fr, sp);
	ftmp = getfreg(nsp.flt);
	fltval = new_flpt();

	switch (name) {
	case uwordhd: constval = alpha_word_max; break;
	case ulonghd: constval = alpha_long_max; break;
	case u64hd:   constval = alpha_quad_max; break;
	}

	flptnos[fltval] = constval;
	asm_comment("BEGIN fix_unsigned");
	float_exp = getexp(realsh, NULL, 1, NULL, NULL, 0, fltval, real_tag);
	isa = evaluated(float_exp, 0);
	set_text_section();
	setinsalt(aa, isa);
	dest.ashwhere.ashsize = (fr.type == IEEE_single) ? 32 : 64;
	dest.ashwhere.ashalign = dest.ashwhere.ashsize;
	newfr.fr = ftmp;
	newfr.type = fr.type;
	setfregalt(dest.answhere, newfr);
	IGNORE move(aa, dest, nsp, 0);
	float_op((fr.type == IEEE_single) ? i_adds : i_addt, fr.fr, ftmp, ftmp);
	float_op(i_fcmovlt, fr.fr, ftmp, fr.fr);
	asm_comment("END fix_unsigned");
}

static INT64
unsigned_rep(INT64 val, shape dest_shape)
{
	switch (name(dest_shape)) {
	case ucharhd: return val & 0xff;
	case uwordhd: return val & 0xffff;
	case ulonghd: return val & 0xffffffff;
	case u64hd:   return val;
	default:      return val;
	}
}

/*
 * Inserts global pointer reference.
 */
static void
set_global_pointer(void)
{
	baseoff a;

	a.offset = 0;
	a.base   = PV;

	load_store(i_ldgp, GP, a);
}

#if !DO_NEW_DIVISION

/*
 * This function produces a code sequence to divide the contents
 * of register 'src' by constant value 'm' and store the result
 * in register 'target'.
 *
 * The division is performed by calculating umax64/b and then
 * performing an umulh of this with the source register.
 */
static void
divide_by_constant(int src, INT64 m, int target, space sp)
{
	space newsp;
	int rtmp;
	int ruse;
	INT64 divres;

	newsp = guardreg(src, sp);
	rtmp = getreg(newsp.fixed);
	ruse = getreg(guardreg(rtmp, newsp).fixed);

	operate_fmt(i_subq, 31, src, ruse);
	operate_fmt(i_cmovgt, src, src, ruse);
	INT64_assign(divres, INT64_increment(INT64_divide(umax, m, 0)));
	load_store_immediate(i_ldiq, rtmp, divres);
	operate_fmt(i_umulh, rtmp, ruse, target);
	operate_fmt(i_subq, 31, target, ruse);
	operate_fmt(i_cmovlt, src, ruse, target);
}

#endif

#if DO_NEW_DIVISION

/*
 * Output log2(x) rounding up.
 */
int
log2(INT64 val)
{
	int res = 0;
	int absval;

	absval = abs(val);

	while (!INT64_eq(absval, make_INT64(0, 1))) {
		/* while (absval != 1) { */
		while (!INT64_eq(INT64_mod(absval, make_INT64(0, 2), 1), make_INT64(0, 0))) {
			/* while (absval % 2) { */
			absval = INT64_increment(absval);
			/* ++absval; */
		}

		while (INT64_eq(INT64_mod(absval, make_INT64(0, 2), 1), make_INT64(0, 0))) {
			/* while (absval % 2 == 0) { */
			++res;
			absval = INT64_divide(absval, make_INT64(0, 2), 1);
			/* absval /= 2; */
		}
	}

	return res;
}

/*
 * If 1/m can be transformed into the form: 1/m = 1/(2^n) * (2^x/b).
 * Then return the values of n and x required.
 * If successful, return true, otherwise, return false.
 */
bool
calculate_shift_for_division(INT64 m, int *n, int *x, bool is_quad)
{
	INT64 val = m;
	int shift = 0;
	int power = 1;
	INT64 r;

	INT64 max32 = make_INT64(0, 0xffffffff);
	INT64 max16 = make_INT64(0, 0xffff);

	if (is_quad) {
		/*r = (429496729L%m) * 429496729L;*/
		r = INT64_mult(max32, INT64_mod(max32, m, 1), 1);
	} else {
		/*r = (65536%m) *65536;*/
		r = INT64_mult(max16, INT64_mod(max16, m, 1), 1);
	}

	r = INT64_mod(r, val, 1);
	/*r = r % val; */
	while (INT64_eq(INT64_mod(val, make_INT64(0, 2), 1), make_INT64(0, 0))) {
		/*  while(val%2 == 0){*/
		val = INT64_shift_right(val, 1, 1);
		/*val/=2;*/
		shift++;
	}

	if (INT64_eq(val, make_INT64(0, 1))) {
		error(ERR_INTERNAL, "Unexpected power of 2 in shift calculation");
		exit(EXIT_FAILURE);
	}

	while ((INT64_lt(make_INT64(0, power), val) &&
	        INT64_lt(make_INT64(0, power), INT64_subtract(val, r, 1)))) {
		/*while ((power<val) && (val-r > power)){*/
		r = INT64_mult(r, make_INT64(0, 2), 1);
		/*r *= 2;*/
		/*r = r % val;*/
		r = INT64_mod(r, val, 1);
		power *= 2;
		/*power *= 2;*/
	}

	*n = shift;
	*x = power;

	return INT64_lt(make_INT64(0, power), val) ? true : false;
	/*return (power<val)?true:false;*/
}

/*
 * This function produces a code sequence to divide the contents of
 * register 'src' by constant value 'm' and store the result in
 * register 'target'.
 *
 * The division is performed by calculating umax64/b and then performing
 * an umulh of this with the source register.
 * The code produced makes use of the AT register.
 */
static void
divide_by_constant(exp div, exp lhs, exp valexp, int r_dest, space nsp)
{
	INT64 m = zero_int64;
	INT64 divres;
	bool simple_div;
	INT64 max_val;
	INT64 factor;
	int shift, power /*,factor*/;
	int src = reg_operand(lhs, nsp);
	int ruse, rdest, r_frac_value;
	space newsp = guardreg(src, nsp);
	int is_quad = !is32(sh(lhs));
	newsp = guardreg(r_dest, newsp);

	if (!is_quad) {
		m = make_INT64(0, no(valexp));
	} else {
		m = flt64_to_INT64(exp_to_f64(valexp));
	}

	if (!is_signed(sh(lhs)) && INT64_lt(m, make_INT64(0, 0))) {
		setnoat();
		load_store_immediate(i_ldiq, AT, m);
		operate_fmt(i_cmpule, AT, src, rdest);
		setat();
		return;
	}

	/*max_val = is_quad?0xffffffffffffffffL:0xffffffffL;*/
	max_val = is_quad ? make_INT64(0xffffffff, 0xffffffff) : make_INT64(0, 0xffffffff);

	simple_div = calculate_shift_for_division(m, &shift, &power, is_quad);
	r_frac_value = r_dest;	/* alias, saves registers */

	if (simple_div) {
		factor = m/*2<<power*/;
		factor = INT64_shift_left(make_INT64(0, 2), log2(m) - 1, 1);
		/*factor = 2<<(log2(m)-1);*/
	} else if (is_signed(sh(lhs))) {
		factor = (m);
		factor = INT64_shift_left(make_INT64(0, 2), log2(m) - 1, 1);
		/*factor = 2<<(log2(m)-1);*/
		shift = 0 /*factor*/;
	} else {
		factor = INT64_subtract(INT64_shift_left(make_INT64(0, 2), log2(m) - 1, 1), m, 1);
		/*factor = (2<<(log2(m)-1))-m;*/
		/*    factor = power-m;*/
	}

	divres = INT64_add(INT64_divide(factor, m, 1),
	                   INT64_mult(
	                       INT64_divide(max_val, m, 1),
	                       factor, 1),
	                   1);
	/*  divres = factor/m + (max_val/m)*factor;*/
	if (!is_quad)divres =
		    INT64_add(
		        INT64_divide(
		            INT64_shift_left(make_INT64(0, 1), 32 + log2(m) - 1, 1),
		            m, 1),
		        INT64_divide(
		            INT64_shift_left(make_INT64(0, 1), log2(m) - 1, 1),
		            m, 1),
		        1);

#if 0
	if (!is_quad) {
		divres = (((long)0x1 << (32 + log2(m))) / m) + (1 << log2(m)) / m;
	}
#endif

	if (is_signed(sh(lhs))) {
		/*ruse = getreg(newsp.fixed);*/
		ruse = AT;
		setnoat();
		operate_fmt(i_subq, 31, src, ruse);
		operate_fmt(i_cmovgt, src, src, ruse);
	} else {
		if (!is_quad) {
			/*ruse = getreg(newsp.fixed);*/
			ruse = AT;
			setnoat();
			operate_fmt_immediate(i_zap, src, 240, ruse);
		} else {
			ruse = src;
		}
	}

	if (is_quad) {
		operate_fmt_big_immediate(i_umulh, ruse, divres, r_dest);
	} else {
		load_store_immediate(i_ldiq, r_frac_value, divres);
		operate_fmt(i_mulq, ruse, r_frac_value, r_dest);
	}

	if (is_signed(sh(lhs))) {
		operate_fmt_immediate(i_sra, r_dest, (is_quad ? 0 : 32) + log2(m) - 1, r_dest);
	} else {
		operate_fmt_immediate(i_srl, r_dest,
			(is_quad ? 0 : 32) + ((!simple_div) ? 0 : (log2(m) - 1)), r_dest);
	}

	if (is_signed(sh(lhs))) {
		operate_fmt(i_subq, 31, r_dest, ruse);
		operate_fmt(INT64_lt(make_INT64(0, 0), m) ? i_cmovlt : i_cmovgt, src, ruse, r_dest);
		/*operate_fmt((m>0)?i_cmovlt:i_cmovgt,src,ruse,r_dest);*/
	} else if (!simple_div && !is_signed(sh(lhs))) {
		operate_fmt(i_addq, r_dest, ruse, r_dest);
		operate_fmt_immediate(i_srl, r_dest, log2(m), r_dest);
	}

	if (ruse == AT) {
		setat();
	}
}

#endif

/*
 * This function produces a code sequence to convert the value in
 * register reg from shape src_shape to shape dest_shape.
 *
 * Returns true if any code is produced and false otherwise.
 */
static bool
convert_shapes(int dest_shape, int src_shape, int reg, int dreg)
{
	if (reg >= 32 || dreg >= 32) {
		return false;
	}

	switch (dest_shape) {
	case s64hd:
	case u64hd:
		switch (src_shape) {
		/* clear all but the bottom byte */
		case ucharhd: operate_fmt_immediate(i_zapnot, reg, 1,  dreg); return true;
		case uwordhd: operate_fmt_immediate(i_zapnot, reg, 3,  dreg); return true;
		case ulonghd: operate_fmt_immediate(i_zapnot, reg, 15, dreg); return true;

		default:
			return false;
		}

	case slonghd:
		switch (src_shape) {
		case ucharhd: operate_fmt_immediate(i_zapnot, reg, 1, dreg); return true;
		case uwordhd: operate_fmt_immediate(i_zapnot, reg, 3, dreg); return true;
		case ulonghd: return false; /* operate_fmt_immediate(i_addl,reg,0,dreg); return true; */
			/* sign extend */
#if 0
		case s64hd: operate_fmt_immediate(i_zapnot, reg, 15, dreg);
			/*operate_fmt_immediate(i_addl,reg,0,reg);*/ return true;
#endif

		default:
			return false;
		}

	case ulonghd:
		switch (src_shape) {
		case scharhd: operate_fmt_immediate(i_zapnot, reg, 1, dreg); return true;
		case swordhd: operate_fmt_immediate(i_zapnot, reg, 3, dreg); return true;
		case slonghd: return false; /* operate_fmt_immediate(i_zapnot,reg,15,dreg); return true; */
#if 0
		case s64hd: operate_fmt_immediate(i_zapnot, reg, 15, dreg); return true;
#endif

		default:
			return false;
		}

	default:
		return false;
	}
}

#define OVERFLOW_VALUE 0x02e0000000000000

#if 0

/*
 * Checks for floating point error.
 *
 * This function outputs code to look at the contents of the
 * floating  point control register (FPCR) and determine whether
 * or not a floating point error has occured. If an error is
 * detected a jump is made to the label specified in no(son(pt(e))).
 *
 * The error status is determined by looking at the summary bit
 * of the FPCR (bit 63) which is a bitwise OR of all the error bits.
 * The errors recognised are: integer overflow, inexact result,
 * underflow,overflow,division by zero, and invalid operation.
 */
static void
check_exception(exp e, space sp)
{
	long trap;
	int r1, r2;

	if (!pt(e)) {
		error(ERR_INTERNAL, "Error handler not present");
	}

	trap = trap_label(e);  	/* label of handler */
	r1 = getfreg(sp.flt);
	r2 = getfreg(guardfreg(r1, sp).flt);
	no_parameter_instructions(i_trapb);
	float_op(i_mf_fpcr, r1, r1, r1);

#if 0
	/*float_op(i_mt_fpcr,31,31,31);*/
	float_load_store_immediate(i_ldit, r2, "1.0"); 	/* ?? */
	float_op(i_cpys, r1, r2, r2); /* take the sign bit of the fpcr and append 1.0 */
	no_parameter_instructions(i_trapb);
	float_branch(i_fblt, r2, trap);
#else
	{
		baseoff b;
		int rt = getreg(sp.fixed);
		b.base = SP;
		b.offset = stack_top;
		float_load_store(i_stt, r1, b);
		load_store(i_ldq, rt, b);
		/* now check for overflow (bits 57/55/54/53) */
		operate_fmt_big_immediate(i_and, rt, OVERFLOW_VALUE, rt);
		no_parameter_instructions(i_trapb);
		integer_branch(i_bne, rt, trap);
	}
#endif
}

#endif

#define check_exception(e, sp)	((void) 0)

#define PLUS_INFINITY 3

static void
set_up_rounding_mode(int val)
{
	UNUSED(val);
}

/*
 * This function returns the appropriate branch instruction
 * for the test represented by 'i'
 */
static instruction
sbranches(int i)
{
	switch (i) {
	case 1: return i_ble;
	case 2: return i_blt;
	case 3: return i_bge;
	case 4: return i_bgt;
	case 5: return i_bne;
	case 6: return i_beq;

	default:
		error(ERR_INTERNAL, "Illegal value for ntest");
	}

	return i_ble;
}

static bool
fdouble_comparisons(instruction *ins, int i)
{
	switch (i) {
	case 1: *ins = i_cmptle; return false;
	case 2: *ins = i_cmptlt; return false;
	case 3: *ins = i_cmptlt; return true;
	case 4: *ins = i_cmptle; return true;
	case 5: *ins = i_cmpteq; return true;
	case 6: *ins = i_cmpteq; return false;

	default:
		error(ERR_INTERNAL, "illegal branch");
		return false;
	}
}

/*
 * This function selects an appropriate compare instruction for the test
 * represented by 'i', returning the instruction name in the 'ins' parameter.
 *
 * As the set of instructions available does not directly cover all the
 * required tests, some instructions carry out the inverse of the required test.
 * In these cases, the return value is true, otherwise it is false.
 */
static bool
comparisons(instruction *ins, shape s, int i)
{
	if ((is_signed(s))) {
		/* treat pointer as signed (even though it isn't) */

		switch (i) {
		case 1: *ins = i_cmple; return false;
		case 2: *ins = i_cmplt; return false;
		case 3: *ins = i_cmplt; return true;
		case 4: *ins = i_cmple; return true;
		case 5: *ins = i_cmpeq; return true;
		case 6: *ins = i_cmpeq; return false;

		default:
			error(ERR_INTERNAL, "illegal branch");
			return false;
		}
	} else {
		switch (i) {
		case 1: *ins = i_cmpule; return false;
		case 2: *ins = i_cmpult; return false;
		case 3: *ins = i_cmpult; return true; /* actually >= */
		case 4: *ins = i_cmpule; return true; /* actually > */
		case 5: *ins = i_cmpeq;  return true;
		case 6: *ins = i_cmpeq;  return false;

		default:
			error(ERR_INTERNAL, "illegal branch");
			return false;
		}
	}
}

/*
 * Conditional moves
 */
static instruction
condmove(int i)
{
	switch (i) {
	case 1: return i_cmovle;
	case 2: return i_cmovlt;
	case 3: return i_cmovge;
	case 4: return i_cmovgt;
	case 5: return i_cmovne;
	case 6: return i_cmoveq;

	default:
		error(ERR_INTERNAL, "Illegal value for ntest");
		return i_cmovle;
	}
}

/*
static instruction
fcondmove(int i)
{
	switch(i){
	case 1: return i_fcmovle;
	case 2: return i_fcmovlt;
	case 3: return i_fcmovge;
	case 4: return i_fcmovgt;
	case 5: return i_fcmovne;
	case 6: return i_fcmoveq;

	default:
		error(ERR_INTERNAL, "Illegal value for ntest");
	}
}
*/

static bool
compares(instruction *ins, shape s, int i)
{
	if (is_signed(s)) {
		switch (i) {
		case 1: *ins = i_cmplt; return false;
		case 2: *ins = i_cmple; return false;
		case 3: *ins = i_cmplt; return false;
		case 4: *ins = i_cmple; return false;
		case 5: *ins = i_cmpeq; return false;
		case 6: *ins = i_cmpeq; return false;
		}
	} else {
		switch (i) {
		case 1: *ins = i_cmpult; return false;
		case 2: *ins = i_cmpule; return false;
		case 3: *ins = i_cmpult; return true;
		case 4: *ins = i_cmpule; return true;
		case 5: *ins = i_cmpeq;  return false;
		case 6: *ins = i_cmpeq;  return false;
		}
	}

	return false;
}

/*
static instruction
fbranches(int i)
{
	switch (i) {
	case 1: return i_fble;
	case 2: return i_fblt;
	case 3: return i_fbge;
	case 4: return i_fbgt;
	case 5: return i_fbne;
	case 6: return i_fbeq;

	default:
		error(ERR_INTERNAL, "Illegal value for ntest");
	}
}

static instruction
fdbranches(int i)
{
	switch (i) {
	case 1: return i_fble;
	case 2: return i_fblt;
	case 3: return i_fbge;
	case 4: return i_fbgt;
	case 5: return i_fbne;
	case 6: return i_fbeq;

	default:
		error(ERR_INTERNAL, "Illegal value for ntest");
	}
}
*/

/* used to invert TDF tests */
long  notbranch[6] = {
	4, 3, 2, 1, 6, 5
};

/*
 * Move sizereg bytes to dest from source using movereg bytemove is the maximum
 * number of bytes which can be moved in a single instruction if available.
 *
 * In order to reduce the time for the operation the function attempts to use
 * the most appropriate load & store instructions, which requires that the
 * number of bytes remaining to be copied and the alignment of the object be
 * taken into account.
 *
 * As the code sequence required to generate word (16 bit) load/store is
 * prohibitively long, these cases are treated as bytes.
 */

/*
 * Without overlap (destination < source)
 */
static void
move_dlts(int dest, int src, int sizereg, int movereg, int bytemove, space sp)
{
	int qword_lab, lword_lab, byte_lab, endlab;
	int rtest = getreg(sp.fixed);

	baseoff b;
	b.offset = 0;
	qword_lab = (bytemove == 8) ? new_label() : -1;
	lword_lab = (bytemove >= 4) ? new_label() : -1;
	byte_lab = new_label();
	endlab = new_label();

	switch (bytemove) {
	case 8:
		set_label(qword_lab);
		operate_fmt_immediate(i_cmplt, sizereg, 8, rtest);
		integer_branch(i_bne, rtest, lword_lab);
		b.base = src;
		load_store(i_ldq, movereg, b);
		b.base = dest;
		load_store(i_stq, movereg, b);
		operate_fmt_immediate(i_addq, src, 8, src);
		operate_fmt_immediate(i_addq, dest, 8, dest);
		operate_fmt_immediate(i_subq, sizereg, 8, sizereg);
		integer_branch(i_beq, sizereg, endlab);
		integer_branch(i_br, 31, qword_lab);
		FALL_THROUGH;
	case 4:
		set_label(lword_lab);
		operate_fmt_immediate(i_cmplt, sizereg, 4, rtest);
		integer_branch(i_bne, rtest, byte_lab);
		b.base = src;
		load_store(i_ldl, movereg, b);
		b.base = dest;
		load_store(i_stq, movereg, b);
		operate_fmt_immediate(i_addq, src, 4, src);
		operate_fmt_immediate(i_addq, dest, 4, dest);
		operate_fmt_immediate(i_subq, sizereg, 4, sizereg);
		integer_branch(i_beq, sizereg, endlab);
		integer_branch(i_br, 31, lword_lab);
		FALL_THROUGH;
	case 2:
		FALL_THROUGH;
	case 1: {
		int rtmp = getreg(sp.fixed);
		int rtmp2 = getreg(sp.fixed);

		set_label(byte_lab);
		integer_branch(i_beq, sizereg, endlab);
		b.base = src;
		load_store(i_ldq_u, movereg, b);
		setnoat();
		load_store(i_lda, AT, b);
		operate_fmt(i_extbl, movereg, AT, movereg);
		b.base = dest;
		load_store(i_lda, AT, b);
		load_store(i_ldq_u, rtmp, b);
		operate_fmt(i_insbl, movereg, AT, rtmp2);
		operate_fmt(i_mskbl, rtmp, AT, rtmp);
		setat();
		operate_fmt(i_bis, rtmp, rtmp2, rtmp);
		load_store(i_stq_u, rtmp, b);
		operate_fmt_immediate(i_addq, src, 1, src);
		operate_fmt_immediate(i_addq, dest, 1, dest);
		operate_fmt_immediate(i_subq, sizereg, 1, sizereg);
		integer_branch(i_bne, sizereg, byte_lab);
	}
	}

	set_label(endlab);
}

/*
 * With overlap (destination > src)
 */
static void
move_dgts(int dest, int src, int sizereg, int movereg, int bytemove, space sp)
{
	int qword_lab, lword_lab, byte_lab, endlab;
	int rtest = getreg(sp.fixed);
	baseoff b;
	b.offset = 0;

	qword_lab = (bytemove == 8) ? new_label() : -1;
	lword_lab = (bytemove >= 4) ? new_label() : -1;

	byte_lab = new_label();
	endlab = new_label();
	operate_fmt(i_addq, dest, sizereg, dest);
	operate_fmt(i_addq, src, sizereg, src);

	switch (bytemove) {
	case 8:
		b.offset = -8;
		set_label(qword_lab);
		operate_fmt_immediate(i_cmplt, sizereg, 8, rtest);
		integer_branch(i_bne, rtest, lword_lab);
		b.base = src;
		load_store(i_ldq, movereg, b);
		b.base = dest;
		load_store(i_stq, movereg, b);
		operate_fmt_immediate(i_subq, src, 8, src);
		operate_fmt_immediate(i_subq, dest, 8, dest);
		operate_fmt_immediate(i_subq, sizereg, 8, sizereg);
		integer_branch(i_beq, sizereg, endlab);
		integer_branch(i_br, 31, qword_lab);
		FALL_THROUGH;
	case 4:
		b.offset = -4;
		set_label(lword_lab);
		operate_fmt_immediate(i_cmplt, sizereg, 4, rtest);
		integer_branch(i_bne, rtest, byte_lab);
		b.base = src;
		load_store(i_ldl, movereg, b);
		b.base = dest;
		load_store(i_stq, movereg, b);
		operate_fmt_immediate(i_subq, src, 4, src);
		operate_fmt_immediate(i_subq, dest, 4, dest);
		operate_fmt_immediate(i_subq, sizereg, 4, sizereg);
		integer_branch(i_beq, sizereg, endlab);
		integer_branch(i_br, 31, lword_lab);
		FALL_THROUGH;
	case 2:
		FALL_THROUGH;
	case 1: {
		int rtmp = getreg(sp.fixed);
		int rtmp2 = getreg(sp.fixed);

		b.offset = -1;
		set_label(byte_lab);
		integer_branch(i_beq, sizereg, endlab);
		b.base = src;
		load_store(i_ldq_u, movereg, b);
		setnoat();
		load_store(i_lda, AT, b);
		operate_fmt(i_extbl, movereg, AT, movereg);
		b.base = dest;
		load_store(i_lda, AT, b);
		load_store(i_ldq_u, rtmp, b);
		operate_fmt(i_insbl, movereg, AT, rtmp2);
		operate_fmt(i_mskbl, rtmp, AT, rtmp);
		setat();
		operate_fmt(i_bis, rtmp, rtmp2, rtmp);
		load_store(i_stq_u, rtmp, b);
		operate_fmt_immediate(i_subq, src, 1, src);
		operate_fmt_immediate(i_subq, dest, 1, dest);
		operate_fmt_immediate(i_subq, sizereg, 1, sizereg);
		integer_branch(i_bne, sizereg, byte_lab);
	}
	}

	set_label(endlab);
}

static
void reset_tos(void)
{
	if (Has_tos) {
		baseoff b;
		b.base = FP;
		b.offset = -((PTR_SZ >> 3) * 2) - arg_stack_space;
		load_store(i_stq, SP, b);
	}
}

/*
 * This function finds the last test in the sequence e which is
 * a branch to second, if any exists, otherwise it returns nil.
 */
static exp
testlast(exp e, exp second)
{
	if (name(e) == test_tag && pt(e) == second) {
		return e;
	}

	if (name(e) != seq_tag) {
		return 0;
	}

	if (name(bro(son(e))) == test_tag && pt(bro(son(e))) == second) {
		return bro(son(e));
	} else if (name(bro(son(e))) == top_tag) {
		exp list;

		list = son(son(e));

		for (;;) {
			if (last(list)) {
				if (name(list) == test_tag && pt(list) == second) {
					return list;
				} else {
					return 0;
				}
			} else {
				list = bro(list);
			}
		}
	}

	return 0;
}

bool
last_param(exp e)
{
	if (!isparam(e)) {
		return false;
	}

	e = bro(son(e));
	while (name(e) == diagnose_tag) {
		e = son(e);
	}

	if ((name(e) != ident_tag) || !isparam(e) || name(son(e)) == formal_callee_tag) {
		return true;
	}

	return false;
}

static void
test_unsigned(int reg, unsigned long upper, unsigned trap)
{
	setnoat();
	operate_fmt_big_immediate(i_cmpule, reg, upper, AT);
	integer_branch(i_beq, AT, trap);
	setat();
}

static void
test_signed(int reg, long lower, long upper, int trap)
{
	setnoat();
	operate_fmt_big_immediate(i_cmplt, reg, lower, AT);
	integer_branch(i_bne, AT, trap);
	operate_fmt_big_immediate(i_cmple, reg, upper, AT);
	integer_branch(i_beq, AT, trap);
	setat();
}

static void
test_signed_and_trap(int reg, long lower, long upper, int except)
{
	int ok_lab = new_label();
	int jump_label = new_label();

	setnoat();
	operate_fmt_big_immediate(i_cmplt, reg, lower, AT);
	integer_branch(i_bne, AT, jump_label);
	operate_fmt_big_immediate(i_cmple, reg, upper, AT);
	integer_branch(i_beq, AT, jump_label);
	setat();
	integer_branch(i_br, 31, ok_lab);
	set_label(jump_label);
	do_exception(except);
	set_label(ok_lab);
}

static void
test_unsigned_and_trap(int reg, unsigned long upper, unsigned except)
{
	int ok_lab = new_label();

	setnoat();
	operate_fmt_big_immediate(i_cmpule, reg, upper, AT);
	integer_branch(i_bne, AT, ok_lab);
	setat();
	do_exception(except);
	set_label(ok_lab);
}

/*
 * This function returns a register for use as a destination operand.
 *
 * If the final destination is in a register then that register is returned,
 * otherwise a new register is selected from the pool.
 */
static int
regfrmdest(where *dest, space sp)
{
	switch (dest->answhere.discrim) {
	case inreg:
		return regalt(dest->answhere);

	default:
		return getreg(sp.fixed);
	}
}

static freg
fregfrmdest(where *dest, space sp)
{
	switch (dest->answhere.discrim) {
	case infreg:
		return fregalt(dest->answhere);

	default: {
		freg fr;
		fr.fr = getfreg(sp.flt);
		fr.type = IEEE_double;

		return fr;
	}
	}
}

/*
 * Divide dividend by divisor using the divide instructions supplied
 * by the the assembler. These divide instructions corrupt the t-regs
 * 23, 24, 25, 27 (PV), and 28 (AT) which have to be protected if in use.
 *
 * Returns result register.
 */
static int
divide_using_div(exp div, exp dividend, exp divisor, where dest, space sp, instruction div_ins)
{
	int r_result;
	space newsp;
	int r_dividend, r_divisor;
	int uns;

	newsp = guardreg(AT, sp);
	uns = !is_signed(sh(dividend));

	r_result = regfrmdest(&dest, newsp);
	if (r_result == NO_REG) {
		r_result = getreg(newsp.fixed);
	}

	newsp = guardreg(r_result, newsp);
	r_dividend = reg_operand(dividend, newsp);
	clear_reg(AT), clear_reg(23), clear_reg(24), clear_reg(25), clear_reg(27);
	newsp = guardreg(r_dividend, newsp);

	if (r_result == NO_REG) {
		r_result = getreg(newsp.fixed);
	}

	if (name(divisor) == val_tag && optop(div)) {
		r_divisor = no(divisor);
	} else {
		r_divisor = reg_operand(divisor, newsp);
	}

	/* test for (-inf)/-1 and /0 */
	if (!optop(div) && !error_treatment_is_trap(div)) {
		int over = new_label();
		int trap = trap_label(div);
		integer_branch(i_beq, r_divisor, trap);

		if (!(is_signed(sh(div)))) {
			int rt = getreg(newsp.fixed);
			asm_comment("check unsigned overflow");
			operate_fmt_immediate(i_cmpeq, r_divisor, -1, rt);
			integer_branch(i_bne, rt, trap);
			set_label(over);
		}
	}

	if (!optop(div) && is_signed(sh(div)) && (is64(sh(div)) || is32(sh(div)))) {
		int continue_lab = new_label();
		setnoat();
		operate_fmt_immediate(i_cmpeq, r_divisor, -1, AT);
		integer_branch(i_beq, AT, continue_lab);
		operate_fmt_big_immediate(i_cmpeq, r_dividend, maxmin(sh(div)).mini, AT);
		integer_branch(i_beq, AT, continue_lab);

		if (error_treatment_is_trap(div)) {
			do_exception(f_overflow);
		} else {
			integer_branch(i_br, 31, trap_label(div));
		}

		set_label(continue_lab);
		setat();
	}

	if ((name(divisor) != val_tag) || !optop(div)) {
		operate_fmt(div_ins, r_dividend, r_divisor, r_result);
	} else {
		operate_fmt_immediate(div_ins, r_dividend, r_divisor, r_result);
	}

	if (name(div) == div1_tag) {
		int rem_neg = new_label();
		int exitlab = new_label();
		int rrem = getreg(newsp.fixed);

		if ((name(divisor) != val_tag) || !optop(div)) {
			operate_fmt(((uns) ? ((is64(sh(div))) ? i_remqu : i_remlu) :
			             (is64(sh(div))) ? i_remq : i_reml),
			            r_dividend, r_divisor, rrem);
		} else {
			operate_fmt_immediate(((uns) ? ((is64(sh(div))) ? i_remqu : i_remlu) :
			                       (is64(sh(div))) ? i_remq : i_reml),
			                      r_dividend, r_divisor, rrem);
		}

		integer_branch(i_beq, rrem, exitlab);
		integer_branch(i_blt, rrem, rem_neg);
		/*set_label(rem_pos);*/
		integer_branch(i_bge, r_divisor, exitlab);
		operate_fmt_immediate((is64(sh(div))) ? i_addq : i_addl, r_result, -1, r_result);
		integer_branch(i_br, 31, exitlab);
		set_label(rem_neg);
		integer_branch(i_ble, r_divisor, exitlab);
		operate_fmt_immediate((is64(sh(div))) ? i_addq : i_addl, r_result, -1, r_result);
		set_label(exitlab);
	}

	if (optop(div)) {
		return r_result;
	}

	switch (name(sh(div))) {
	case ucharhd:
		if (error_treatment_is_trap(div)) {
			test_unsigned_and_trap(r_result, 255, f_overflow);
		} else {
			test_unsigned(r_result, 255, trap_label(div));
		}
		break;

	case scharhd:
		if (error_treatment_is_trap(div)) {
			test_signed_and_trap(r_result, -128, 127, f_overflow);
		} else {
			test_signed(r_result, -128, 127, trap_label(div));
		}
		break;

	case uwordhd:
		if (error_treatment_is_trap(div)) {
			test_unsigned_and_trap(r_result, 0xffff, f_overflow);
		} else {
			test_unsigned(r_result, 0xffff, trap_label(div));
		}
		break;

	case swordhd:
		if (error_treatment_is_trap(div)) {
			test_signed_and_trap(r_result, -0x8000, 0x7fff, f_overflow);
		} else {
			test_signed(r_result, -0x8000, 0x7fff, trap_label(div));
		}
		break;

	case ulonghd:
		if (error_treatment_is_trap(div)) {
			test_unsigned_and_trap(r_result, 0xffffffff, f_overflow);
		} else {
			test_unsigned(r_result, 0xffffffff, trap_label(div));
		}
		break;

	case slonghd:
		if (error_treatment_is_trap(div)) {
			test_signed_and_trap(r_result, -0x80000000L, 0x7fffffff, f_overflow);
		} else {
			test_signed(r_result, -0x80000000L, 0x7fffffff, trap_label(div));
		}
		break;

	case s64hd:
		if (error_treatment_is_trap(div)) {
			test_signed_and_trap(r_result, -0x8000000000000000L, 0x7fffffffffffffffL, f_overflow);
		} else {
			test_signed(r_result, -0x8000000000000000L, 0x7fffffffffffffffL
						, trap_label(div));
		}
		break;

	case u64hd:
		if (error_treatment_is_trap(div)) {
			test_unsigned_and_trap(r_result, 0xffffffffffffffffL, f_overflow);
		} else {
			test_unsigned(r_result, 0xffffffffffffffffL, trap_label(div));
		}
		break;

	default:
		error(ERR_INTERNAL, "Illegal shape in div");
	}

	return r_result;
}

static int proc_has_vararg;

/*
 * Process a parameter list
 */
static space
do_callers(exp list, space sp, int *sizecallers)
{
	int disp;
	int spar;
	int fpar = 16;
	instore is;
	is.b.base = SP;
	is.b.offset = 0;
	is.adval = 1;

#ifdef DO_SPECIAL
	if ((disp = specialfn (fn)) > 0) { /* eg function is strlen */
		mka.lab = specialmake(disp, list, sp, dest, exitlab);
		return mka;
	}
#endif

	disp = 0;
	spar = FIRST_INT_ARG; /* register holding 1st integer parameter */

	/* evaluate parameters in turn */
	for (;;) {
		int   hd = name(sh(list));
		where w;
		ash ap;
		int paral;
		int parsize;

		ap = ashof(sh(list));
		paral = (ap.ashalign < 32) ? 32 : ap.ashalign;
		if (spar > 21) {
			ap.ashalign = 64;
			paral = 64;
		}

		parsize = ap.ashsize;
		/* all parameters passed on stack are quadword aligned */
		w.ashwhere = ap;
		disp = rounder(disp, paral);
		spar = FIRST_INT_ARG + (disp >> 6);
		fpar = FIRST_FLOAT_ARG + (disp >> 6);

		if (disp > 448) {
			spar = 22;
			fpar = 22;
		}

		if (is_floating(hd) && disp + parsize <= 384) {
			freg frg;
			ans ansfr;
			frg.fr = fpar++;

			if (hd != shrealhd) {
				frg.type = IEEE_double;
			} else {
				frg.type = IEEE_single;
			}

			setfregalt(ansfr, frg);
			w.answhere = ansfr;
			code_here(list, sp, w);
			/* evaluate parameter into floating parameter register */
			sp = guardfreg(frg.fr, sp);
		} else if (((valregable(sh(list)) || (name(sh(list)) == cpdhd)) ||
		            (name(sh(list)) == nofhd)) && spar <= 21) {
			/* compound types are always passed in registers (given enough space). */
			ans ansr;
			int par_reg;
			int numleft = parsize - ((LAST_INT_ARG - spar + 1) << 6);
			int pregs_used = min((numleft >> 6) + 6, 6);

			setregalt(ansr, spar);
			w.answhere = ansr;

			for (par_reg = spar; par_reg < spar + pregs_used; ++par_reg) {
				sp = guardreg(par_reg, sp);
			}

			sp = guardreg(spar, sp);
			code_here(list, sp, w);

			if (numleft > 0) {
				is.b.offset += (numleft >> 3); /* += number of bytes remaining */
			}
		} else {
			/* pass remaining parameters on the stack. The parameters are aligned on 8 byte boundaries. */
			setinsalt(w.answhere, is);
			is.b.offset += (max(ap.ashsize, REG_SIZE) >> 3);
			/* 'size' was used here */
			code_here(list, sp, w);
			/* eval parameter into argument space on stack */
		}

		if (name(list) == caller_tag) {
			no(list) = disp;
		}

		disp += parsize;
		disp = rounder(disp, REG_SIZE);
		*sizecallers = min(disp, NUM_PARAM_REGS * REG_SIZE);

		if (last(list)) {
			return sp;
		}

		list = bro(list);
	}

	return sp;
}

static void
load_reg(exp e, int r, space sp)
{
	where w;

	w.ashwhere = ashof(sh(e));
	setregalt(w.answhere, r);
	code_here(e, sp, w);
}

static postlude_chain * old_postludes;

static void
update_plc(postlude_chain *chain, int ma)
{
	while (chain) {
		exp pl;

		for (pl = chain->postlude;
			name(pl) == ident_tag && name(son(pl)) == caller_name_tag;
			pl = bro(son(pl)))
		{
			no(pl) += (ma << 1);
		}

		chain = chain->outer;
	}
}

/*
 * This function finds the caller_tag corresponding to a caller_name tag
 */
static exp
find_ote(exp name, int n)
{
	exp dad;

	for (dad = father(name); name(dad) != apply_general_tag; dad = father(dad))
		;

	for (dad = son(bro(son(dad))); n; dad = bro(dad), n--)
		;

	assert(name(dad) == caller_tag);

	return dad;
}

/*
 * This function produces code for expression e,
 * evaluating its result into dest.
 */
makeans
make_code(exp e, space sp, where dest, int exitlab)
{
	INT64  constval;
	makeans mka;

	static int param_stack_space;
	static int sizecallers = 0;

tailrecurse:

	mka.lab     = exitlab;
	mka.regmove = NOREG;

	clear_INT64(constval);

	switch (name(e)) {
	case ident_tag: {
		where placew;
		int   r = NOREG;
		bool remember = 0;
		placew = nowhere;

		if (name(sh(son(e))) == ptrhd && name(son(e)) != cont_tag) {
			/* We should never be identifing a pointer to bits */
			if (al1(sh(son(e))) == 1) {
#if 0
				error(ERR_INTERNAL, "Identify REF BITS");
#endif
			}
		}

		if (is_param_reg(no(e)) && is32(sh(son(e))) &&
		    name(son(e)) != formal_callee_tag) {
			operate_fmt_immediate(i_addl, no(e), 0, no(e));
		}

		/*
		 * The tag of this declaration is transparently identified
		 * with its definition, without reserving more space
		 */
		if (props(e) & defer_bit) {
			e = bro(son(e));
			goto tailrecurse;
		}

		if (son(e) == NULL) {
			placew = nowhere;	/* is this needed? */
		} else if (name(son(e)) == caller_name_tag) {
			exp ote = find_ote(e, no(son(e)));
			int disp = no(ote);

			if (in_vcallers_apply) {
				/* bit of a hack here */
				if (is_floating(name(sh(son(e))))) {
					no(e) = (((disp - sizecallers) >> 3) << 4) + SP;
				} else {
					no(e) = (((disp - 6 * PTR_SZ) >> 3) << 4) + SP;
				}
			} else {
				no(e) = (((disp - sizecallers) >> 3) << 4) + SP;
			}

			placew = nowhere;
		} else {
			ash a;
			int   n = no(e);

			a = ashof(sh(son(e)));
			if (is_param_reg(n) && (props(e) &inreg_bits) && proc_has_vararg) {
				props(e) &= (~inreg_bits);
			}

			if (((props(e) & inreg_bits) != 0)) {
				/* tag in some fixed pt reg */
				/*
				 * If it hasn't been already allocated into a s-reg (or r0)
				 * allocate tag into fixed t-reg ...
				 */
				if (n == NO_REG) {
					int   s = sp.fixed;
					if (props (e) & notparreg) { /* ... but not a parameter reg */
						s |= PARAM_REGS;
					}

					n = getreg(s);
					no(e) = n;
				}

				setregalt(placew.answhere, n);
			} else if ((props(e) & infreg_bits) != 0) {
				/* tag in some float reg */
				freg frg;

				/*
				 * If it hasn't been already allocated into a s-reg (or r0)
				 * allocate tag into float-reg ...
				 */
				if (n == NO_REG) {
					int s = sp.flt;
					if (props(e) & notparreg) {
						s |= 0xc0;
					}
					n = getfreg(s);
					no(e) = n;
				}

				frg.fr = n;
				if (a.ashsize == 64) {
					frg.type = IEEE_double;
				} else {
					frg.type = IEEE_single;
				}

				setfregalt(placew.answhere, frg);
			} else if (isparam(e)) {
				if (name(son(e)) != formal_callee_tag) {
					instore is;
					int this_reg = -1;
					int comp_size;
					int n;
					int offset_adjustment;

					/*
					 * Floating point registers are to be separated from fixed point
					 * registers when saving to the stack
					 */

					if (proc_has_vararg && !is_floating(name(sh(son(e))))) {
						offset_adjustment = 6 * PTR_SZ;
					} else {
						offset_adjustment = arg_stack_space * 8;
					}

					if (Has_fp) {
						n = (no(son(e)) >> 3) - (offset_adjustment >> 3);
					} else {
						n = (((no(son(e)) + frame_size + callee_size - offset_adjustment) >> 3));
					}

					if (props(son(e))) {
						this_reg = (props(son(e)) - 16) << 6;
					}

					/* save all parameters in 64 bit chunks */
					/* Byte disp of params */
					is.b.offset = n;
					is.b.base = (Has_fp) ? FP : SP;
					is.adval = 1;
					setinsalt(placew.answhere, is);

					if (Has_fp) {
						if (Has_no_vcallers || is_floating(name(sh(son(e))))) {
							no(e) = ((no(son(e)) + frame_size + callee_size - locals_offset -
							          (offset_adjustment)) << 1) + FP;
						} else {
							no(e) = ((no(son(e)) + frame_size + callee_size - locals_offset
							          - (arg_stack_space << 3)) << 1) + FP;
							no(e) = ((no(son(e)) + frame_size + callee_size - locals_offset
							          - (offset_adjustment)) << 1) + FP;
						}
					} else {
						no(e) = ((no(son(e)) + frame_size + callee_size - locals_offset -
						          (offset_adjustment)) << 1) + SP;
					}

					if ((a.ashsize > 64) && (this_reg != -1)) {
						for (comp_size = a.ashsize; comp_size > 0 && this_reg < 384;
						     comp_size -= 64)
						{
							load_store(i_stq, 16 + (this_reg >> 6), is.b);
							this_reg += 64;
							is.b.offset += 8;
						}

						/*props(son(e))=0;*/ /* ensures it wont be saved again */
					}

					if (proc_has_vararg && last_param(e) && (this_reg >= 0)) {
						/* attempt to detect vararg */
						int r = rounder(no(son(e)) + shape_size(sh(son(e))), REG_SIZE);

						setinsalt(placew.answhere, is);

						for (r = this_reg; r <= 320; r += 64) {
							/* no need to save first freg */
							is.b.offset = ((r + paramsdumpstart) >> 3) -
							              ((is.b.base == FP) ? (frame_size >> 3) : 0);
							float_load_store(i_stt, 16 + (r >> 6), is.b);
						}

						for (r = this_reg; r <= 320; r += 64) {
							is.b.offset = ((r + gpdumpstart) >> 3) -
							              ((is.b.base == FP) ? (frame_size >> 3) : 0);;
							load_store(i_stq, 16 + (r >> 6), is.b);
						}

						is.b.offset = n;
					} else {
						/*
						 * The alignment of a complex shape is the maximum of the alignments
						 * of its components.
						 *
						 * This assignment overrides that rule in order to simplify saving the
						 * parameter to the stack.
						 */
						if ((name(sh(son(e))) == cpdhd) && (a.ashsize == 64)) {
							a.ashalign = a.ashsize;
						}

						is.b.offset = n;
					}

					setinsalt(placew.answhere, is);
					remember = 1;
				} else {
					no(e) = ((no(son(e)) + frame_size - locals_offset) << 1) +
					        ((Has_vcallees) ? local_reg : FP);

					if (!Has_vcallees) {
						no(e) -= (arg_stack_space << 4);
					}

					placew = nowhere;
				}
			} else {
				/* allocate on stack */

				int   base = n & 0x3f;
				instore is;
				is.b.base = base;
				is.b.offset = (n - base) >> 4;
				is.adval = 1;

				if (base == SP) {
					is.b.offset += locals_offset >> 3;
				} else if ((base == FP && Has_fp)) {
#if 1
					is.b.offset += (((locals_offset - callee_size - frame_size) >> 3)
					                /*- ((in_general_proc)?0:arg_stack_space)*/);
#else
					is.b.offset += (((locals_offset - callee_size - frame_size) >> 3)
					                - arg_stack_space);
#endif
				} else if ((base == local_reg && Has_vcallees)) {
					is.b.offset += ((locals_offset - frame_size) >> 3);
				}

				setinsalt(placew.answhere, is);
				remember = 1;
			}

			placew.ashwhere = a;
		}

		if (isparam(e) && name(son(e)) != formal_callee_tag) {
			exp se = son(e);
			exp d = e;

			/* parameter fiddles */
			if (props(se) == 0 && (props(d) & inanyreg) != 0) {
				/* not originally in required reg */
				ans a;
				instore is;

				is.b.base   = (Has_fp) ? FP : SP;
				is.b.offset = ((no(se) - (arg_stack_space << 3)) +
				               ((Has_fp) ? 0 : ((callee_size + frame_size)))) >> 3;

				is.adval = 0;
				setinsalt(a, is);
				IGNORE move(a, placew, sp, name(sh(se)) & 1);
			} else if (props(se) != 0 && (props(d) & inanyreg) == 0) {
				/* originally in reg and required in store */
				ans a;

				if (is_floating(name(sh(se)))) {
					freg fr;
					fr.fr = props(se);
					if (name(sh(se)) != shrealhd) {
						fr.type = IEEE_double;
					} else {
						fr.type = IEEE_single;
					}
					setfregalt(a, fr);
				} else {
					setregalt(a, props(se));
				}

				r = move(a, placew, sp, 0);
			} else if (props(se) != 0 && props(se) != no(d)) {
				/* in wrong register */
				int sr = no(d);
				int tr = props(se);

				if (is_floating(name(sh(se)))) {
					if ((fltdone & (1 << (sr))) != 0) {
						float_op((name(sh(se)) != shrealhd) ? i_cpys : i_cpys,
						         (int)props(se), (int)(props(se)), no(d));
					} else {
						props(se) = sr;
						no(d) = tr;
						sp = guardfreg(tr, sp);
						/* !? swopped and moved in  dump_tag !? */
					}
				} else {
					if ((fixdone & (1 << sr)) != 0) {
						/* operate_fmt(i_bis,no(d),no(d),(int)props(se));*/
						operate_fmt(i_bis, (int)props(se), (int)props(se), no(d));
					} else {
						props(se) = sr;
						no(d) = tr;
						sp = guardreg(tr, sp);
						/* !? swapped for dump_tag !? */
					}
				}
			}

			/* maybe more about promotions */
		} else if (isparam(e) && name(son(e)) == formal_callee_tag) {
			exp se = son(e);
			exp d = e;

			if ((props(d) & inanyreg) != 0) {
				/* callee parameter assigned to reg */
				ans a;
				instore is;

				is.b.base   = FP;
				is.b.offset = (no(se) - callee_size) >> 3;
				is.adval    = 0;

				setinsalt(a, is);
				IGNORE move(a, placew, sp, is_signed(sh(se)));
			}
		} else {
			r = code_here(son(e), sp, placew);
			/* evaluate the initialisation of tag, putting it into place allocated ... */
		}

		if (remember && r != NOREG && pt(e) != NULL
		    && eq_sze(sh(son(e)), sh(pt(e)))) {
			/* ...if it was temporarily in a register, remember it */
			if (isvar(e)) {
				keepcont(pt(e), r);
			} else {
				keepreg(pt(e), r);
			}
		}

		sp =  guard(placew, sp);
		e = bro(son(e));

		goto tailrecurse; /* and evaluate the body of the declaration */
	}

	case clear_tag:
		return mka;

	case seq_tag: {
		exp t;

		for (t = son(son(e)); ; t = bro(t)) {
			exp next = (last(t)) ? (bro(son(e))) : bro(t);

			if (name (next) == goto_tag) {/* gotos end sequences */
				make_code(t, sp, nowhere, no(son(pt(next))));
			} else {
				code_here(t, sp, nowhere);
			}

			if (last(t)) {
				e = bro(son(e));
				goto tailrecurse;
			}
		}
	}

	case cond_tag: {
		exp first = son(e);
		exp second = bro(son(e));
		exp test;

		if (dest.answhere.discrim == insomereg) {
			/* must make choice of register to contain answer to cond */
			int  *sr = someregalt(dest.answhere);
			if (*sr != -1) {
				error(ERR_INTERNAL, "Somereg *2");
			}

			*sr = getreg(sp.fixed);
			setregalt(dest.answhere, *sr);
		} else if (dest.answhere.discrim == insomefreg) {
			somefreg sfr;
			freg fr;

			sfr = somefregalt(dest.answhere);
			if (*sfr.fr != -1) {
				error(ERR_INTERNAL, "Somefreg *2");
			}

			*sfr.fr = getfreg(sp.flt);
			fr.fr = *sfr.fr;
			fr.type = sfr.type;
			setfregalt(dest.answhere, fr);
		}

		if (name(first) == goto_tag && pt(first) == second) {
			/* first is goto second */
			no(son(second)) = 0;
			mka = make_code(second, sp, dest, exitlab);

			return mka;
		} else if (name(second) == labst_tag &&
		           name(bro(son(second))) == top_tag) {
			/* second is empty */
			int   endl = (exitlab == 0) ? new_label() : exitlab;
			no(son(second)) = endl;
			make_code(first, sp, dest, endl);
			mka.lab = endl;

			return mka;
		} else if (name(second) == labst_tag &&
		           name(bro(son(second))) == goto_tag) {
			/* second is goto */
			exp g = bro(son(second));
			no(son(second)) = no(son(pt(g)));
			mka = make_code(first, sp, dest, exitlab);

			return mka;
		}

		if ((test = testlast(first, second)) /* I mean it */ ) {
			/* effectively an empty then part */
			int   l = (exitlab != 0) ? exitlab : new_label();
			bool rev = IsRev(test);

			ptno(test)  = -l;	/* make test jump to exitlab - see test_tag: */
			props(test) = notbranch[(props(test) & 127) - 1];

			if (rev) {
				SetRev(test);
			}

			/* ... with inverse test */
			no(son(second)) = new_label();
			make_code(first, sp, dest, l);
			make_code(second, sp, dest, l);
			mka.lab = l;

			return mka;
		} else {
			int fl;
			int l;

			no(son(second)) = new_label();
			fl = make_code(first, sp, dest, exitlab).lab;

			l = (fl != 0) ? fl : ((exitlab != 0) ? exitlab : new_label());
			if (name(sh(first)) != bothd) {
				integer_branch(i_br, 31, l);
			}

			make_code(second, sp, dest, l);
			clear_all();
			mka.lab = l;

			return mka;
		}
		}

	case labst_tag:
		if (no(son(e)) != 0) {
			set_label(no(son(e)));
		}

		if (is_loaded_lv(e) && No_S) {
			/* can be target of long_jump; reset sp */
			baseoff b;
			b.base = FP;

			if (Has_vcallees) {
#if 0
				b.offset = -arg_stack_space - (3 * (PTR_SZ >> 3));
#endif
				b.offset = - (3 * (PTR_SZ >> 3));
				load_store(i_ldq, local_reg, b);
			}

			if (Has_tos) {
				b.offset = - (PTR_SZ >> 3) - (arg_stack_space);
				load_store(i_ldq, SP, b);
			} else {
				asm_comment("labst_tag:");
				operate_fmt_immediate(i_subq, FP, (frame_size + callee_size) >> 3, SP);
			}
		}

		e = bro(son(e));
		goto tailrecurse;

	case rep_tag: {
		exp first = son(e);
		exp second = bro(first);

		code_here(first, sp, nowhere);
		no(son(second)) = new_label();
		/*e = second;*/
		mka = make_code(second, sp, dest, exitlab);

		return mka;
		/*goto tailrecurse;*/
	}

	case goto_tag: {
		int   lab = no(son(pt(e)));
		clear_all();
		integer_branch(i_br, 31, lab);

		return mka;
	}

	case make_lv_tag: {
		int r = regfrmdest(&dest, sp);

		ans aa;
		load_store_label(i_lda, r, no(son(pt(e))));
		setregalt(aa, r);
		move(aa, dest, guardreg(r, sp), 0);
		mka.regmove = r;

		return mka;
	}

	case long_jump_tag: {
		int fp = reg_operand(son(e), sp);
		int labval = reg_operand(bro(son(e)), sp);

		asm_comment("long jump");
		operate_fmt(i_bis, fp, fp, FP);	/* move fp into FP */
		/* load labval into register*/
		integer_jump(i_jmp, 31, labval, 0);

		return mka;
	}

	/* max(x,y) and min(x,y) */
	case offset_max_tag:
	case max_tag:
	case min_tag: {
		exp l = son(e);
		exp r = bro(l);

		int a1 = reg_operand(l, sp);
		int a2 = reg_operand(r, sp);
		int d = regfrmdest(&dest, sp);
		int rtmp = getreg(guardreg(d, sp).fixed);
		ans aa;

		operate_fmt(i_bis, a1, a1, d);
		operate_fmt(is_signed(sh(l)) ? i_cmplt : i_cmpult, a1, a2, rtmp);

		if ((name(e) == max_tag) || (name(e) == offset_max_tag)) {
			operate_fmt(i_cmovne, rtmp, a2, d);
		} else {
			operate_fmt(i_cmoveq, rtmp, a2, d);
		}

		setregalt(aa, d);
		IGNORE move(aa, dest, guardreg(d, sp), 0);
		mka.regmove = d;

		return mka;
	}

	case fmax_tag: {
		exp l = son(e);
		exp r = bro(l);

		int a1 = freg_operand(l, sp);
		int a2 = freg_operand(r, sp);

		freg rd;
		int rtmp;
		ans aa;
		rd = fregfrmdest(&dest, sp);
		rtmp = getfreg(guardreg(rd.fr, sp).fixed);
		float_op(i_cpys, a1, a1, rd.fr);
		float_op(i_cmptlt, a1, a2, rtmp);
		float_op(i_fcmovne, rtmp, a2, rd.fr);
		setfregalt(aa, rd);
		mka.regmove = move(aa, dest, guardfreg(rd.fr, sp), 1);

		return mka;
	}

	case abslike_tag: {
		/*
		 * If (test x) then res = -x, else res = x *
		 *
		 * The code produced for this construct is:
		 * move x to res, neg x -> y, cmov(test) x,y,res.
		 *
		 * If the test is unsigned then we can optimise certain cases,
		 * i.e. less-than and greater-than-or-equal are
		 * always false and true respectively
		 */
		exp l = son(son(e));
		instruction cmove_ins;
		space nsp;
		int test_num;
		int dest_reg;
		ans aa;
		int a1, rtmp;
		nsp = sp;

		test_num = props(son(e));
		dest_reg = regfrmdest(&dest, nsp);
		mka.regmove = dest_reg;
		setregalt(aa, dest_reg);
		nsp = guardreg(dest_reg, nsp);
		a1 = reg_operand(l, nsp);
		nsp = guardreg(dest_reg, nsp);
		rtmp = getreg(nsp.fixed);
		operate_fmt(i_bis, a1, a1, dest_reg);
		cmove_ins = condmove(test_num);
		operate_fmt(i_subq, 31, a1, rtmp);
		operate_fmt(cmove_ins, a1, rtmp, dest_reg);
		move(aa, dest, guardreg(dest_reg, nsp), 0);

		return mka;
	}

	/* case abslike_tag: */
	case absbool_tag: {
		/* need to clear up the distinctions between comparison and conditional move. */
		exp l = son(son(e));
		exp r = bro(l);
		shape shl = sh(l);
		instruction compare_ins;
		int   n = props(son(e));
		int   d;
		int   a1;
		int   a2;
		bool xlike = (name(e) != absbool_tag);
		ans aa;
		bool uns = (!is_signed(shl));

		if (!xlike && name(l) == val_tag) {
			/* put literal operand on right */
			exp temp = l;

			l = r;
			r = temp;

			if (n <= 2) {
				n += 2;
			} else if (n <= 4) {
				n -= 2;
			}
		}

		IGNORE compares(&compare_ins, shl, n);
		d = regfrmdest(&dest, sp);

		/* reg d will contain result of compare */

		a1 = reg_operand(l, sp);
		sp = guardreg(a1, sp);

		if (xlike && a1 == d) {
			d = getreg(sp.fixed);
		}

		if (name(r) == val_tag) {
			if ((n == 1) || (n == 2)) {
				int rt = getreg(guardreg(d, sp).fixed);
				if (no(r)) {
					INT64 res;

					if (isbigval(r)) {
						INT64_assign(res, flt64_to_INT64(exp_to_f64(r)));
						/*res=flt64_to_INT64(exp_to_f64(r));*/
					} else {
						INT64_assign(res, make_INT64(0, no(r)));
					}

					load_store_immediate(i_ldiq, rt, res);
				} else {
					rt = 31;
				}

				if (name(e) != absbool_tag) {
					int rtmp;

					if (uns) {
						rtmp = getreg(sp.fixed);
						operate_fmt(compare_ins, rt, a1, rtmp);
					} else {
						rtmp = rt;
					}

					compare_ins = condmove(n);
					operate_fmt(i_bis, rtmp, rtmp, d);
					operate_fmt(compare_ins, a1, a1, d);
				} else {
					operate_fmt(compare_ins, rt, a1, d);
				}
			} else {
				if (isbigval(r)) {
					operate_fmt_big_immediate(compare_ins, a1,
					                          flt64_to_INT64(exp_to_f64(r)), d);
				} else {
					operate_fmt_immediate(compare_ins, a1, no(r), d);
				}
			}

			if(n == 6) {	/* ? */
				operate_fmt(i_cmpeq, d, 31, d);
			}

			/* invert the result */
		} else {
			space nsp;
			nsp = guardreg(a1, sp);
			a2 = reg_operand(r, nsp);

			if (xlike && a2 == d) {
				nsp = guardreg(a2, nsp);
				d = getreg(nsp.fixed);
			}

			if ((n == 1) || (n == 2)) {
				operate_fmt(compare_ins, a2, a1, d);
			} else {
				operate_fmt(compare_ins, a1, a2, d);
			}

			if (n == 6) {
				operate_fmt(i_cmpeq, d, 31, d);
			}
		}

		if (name(e) == maxlike_tag || name(e) == minlike_tag) {
			instruction ins;
			int l = new_label();
			setnoreorder();
			ins = (name(e) == maxlike_tag) ? i_bne : i_beq;

			/*operate_fmt(i_addu, d, a1, 0);*/
			integer_branch(ins, d, l);
			if (name(r) == val_tag) {
				INT64 v;
				low_INT64(v) = no(r);
				load_store_immediate(i_ldil, d, v);
			} else {
				operate_fmt(i_bis, no(r), no(r), d);
			}

			set_label_no_clear(l);
			setreorder();
		} else if (name(e) == abslike_tag) {
			int l1 = new_label();
			int l2 = new_label();
			setnoreorder();
			integer_branch(i_bne, d, l2);
			operate_fmt(i_subq, 31, a1, d);
			integer_branch(i_br, 31, l1);
			set_label(l2);
			operate_fmt(i_bis, a1, a1, d);

			set_label_no_clear(l1);
			setreorder();
		}

		setregalt(aa, d);
		move(aa, dest, guardreg(d, sp), 0);
		mka.regmove = d;
		return mka;
	}

	/*
	 * Tests are performed by either a comparison or subraction instruction,
	 * followed by a conditional branch. If the test is unsigned, or if
	 * a subtraction could cause an overflow, then comparisons must be used.
	 */
	case test_tag: {
		exp l = son(e);
		exp r = bro(l);
		int   lab = (ptno (e) < 0) ? -ptno (e) : no (son (pt (e))); /* !! */
		/* see frig in cond_tag */
		shape shl = sh(l);
		instruction test_ins;
		int   n = (props (e)) & 127; /* could have Rev bit in props*/
		bool rev;
		bool is_compare = ((!is_signed(shl)) && ((n - 5) < 0) &&
		                   (name(shl) != ptrhd)) || ((is64(shl)));
		is_compare = true;

		if (is_floating(name(sh(l)))) {
			instruction compare_ins;
			space nsp;
			int rev;
			int a1, a2, dest;
			a1 = freg_operand(l, sp);
			nsp = guardfreg(a1, sp);
			a2 = freg_operand(r, nsp);
			dest = getfreg(nsp.flt);
			rev = fdouble_comparisons(&compare_ins, n);
			float_op(compare_ins, a1, a2, dest);
			float_branch(rev ? i_fbeq : i_fbne, dest, lab);
			return mka;
		} else {
			int a1;
			int a2;

			if (name (l) == val_tag) {/* put literal operand on right */
				exp temp = l;

				l = r;
				r = temp;

				if (n <= 2) {
					n += 2;
				} else if (n <= 4) {
					n -= 2;
				}
			}

			if (is_compare) {
				rev = comparisons(&test_ins, shl, n);
			} else {
				rev = 0;
				test_ins = sbranches(n);
			}

			a1 = reg_operand(l, sp);
			if (name(r) == val_tag) {
				space nsp;
				int rtemp;

				switch (name(sh(r))) {
				case ucharhd: no(r) = (unsigned char)  no(r); break;
				case scharhd: no(r) = (char)           no(r); break;
				case swordhd: no(r) = (short)          no(r); break;
				case uwordhd: no(r) = (unsigned short) no(r); break;
				}

				if ((no(r) != 0) || (isbigval(r))) {
					nsp = guardreg(a1, sp);
					rtemp = getreg(nsp.fixed);

					if (is_compare) {
						if (isbigval(r)) {
							operate_fmt_big_immediate(test_ins, a1, exp_to_INT64(r), rtemp);
						} else {
							operate_fmt_immediate(test_ins, a1, no(r), rtemp);
						}
						integer_branch(rev ? i_beq : i_bne, rtemp, lab);
					} else {
						if (name(shl) == ulonghd) {
							operate_fmt_immediate(i_addl, a1, 0, a1);
						}
						if (isbigval(r)) {
							INT64 res = flt64_to_INT64(exp_to_f64(r));
							operate_fmt_big_immediate(i_subq, a1, res, rtemp);
						} else {
							operate_fmt_immediate(i_subq, a1, no(r), rtemp);
						}
						integer_branch(test_ins, rtemp, lab);
					}
				} else {
					if (is_compare) {
						int rtmp = getreg(guardreg(a1, sp).fixed);
						if (is_signed(shl)) {
							test_ins = sbranches(n);
							integer_branch(test_ins, a1, lab);
						} else {
							operate_fmt(test_ins, a1, 31, rtmp);
							integer_branch(rev ? i_beq : i_bne, rtmp, lab);
						}
					} else {
						int dreg = a1;
						integer_branch(test_ins, dreg, lab);
					}
				}
			} else {
				space nsp;
				int rtemp;
				nsp = guardreg(a1, sp);
				a2 = reg_operand(r, nsp);

				if (a2 != 31) {
					rtemp = getreg(guardreg(a2, nsp).fixed);
					if (is_compare) {
						operate_fmt(test_ins, a1, a2, rtemp);
						integer_branch(rev ? i_beq : i_bne, rtemp, lab);
					} else {
						operate_fmt(is64(sh(son(e))) ? i_subq : i_subl, a1, a2,
						            rtemp);
						integer_branch(test_ins, rtemp, lab);
					}
				} else {
					test_ins = sbranches(n);
					integer_branch(test_ins, a1, lab);
				}
			}
			return mka;
		}
	}

	case ass_tag:
	case assvol_tag: {
		exp lhs = son(e);
		exp rhs = bro(lhs);
		where assdest;
		space nsp;
		ash arhs;

		int   contreg = NOREG;
		if (name(e) == assvol_tag) {
			clear_all();
			/*setvolatile ();*/
		}

		arhs = ashof(sh(rhs));

		if (name(e) == ass_tag && name(rhs) == apply_tag &&
		    (is_floating(name(sh(rhs))) || valregable(sh(rhs)))) {
			/* if source is simple proc call, evaluate it first and do assignment */
			ans aa;
			code_here(rhs, sp, nowhere);

			if (is_floating(name(sh(rhs)))) {
				freg frg;
				frg.fr = 0;
				if (arhs.ashsize == 64) {
					frg.type = IEEE_double;
				} else {
					frg.type = IEEE_single;
				}
				setfregalt(aa, frg);
			} else {
				setregalt(aa, RESULT_REG);
			}

			assdest = locate(lhs, guardreg(RESULT_REG, sp), sh(rhs), NO_REG);
			move(aa, assdest, sp, 1);
			move(aa, dest, sp, 1);
			clear_dep_reg(lhs);
			return mka;
		}

		/*	if (al1(sh(lhs)) == 1 || arhs.ashalign == 1)
			clear_reg (0);*/

		assdest = locate(lhs, sp, sh(rhs), NO_REG);
		nsp = guard(assdest, sp);
		/* evaluate address of destination */

		if (assdest.ashwhere.ashalign == 1) {
			/* this is an assignment of a bitfield, so get address in proper form */
			instore is;

			switch (assdest.answhere.discrim) {
			case inreg:
				is.b.base = regalt(assdest.answhere);
				is.b.offset = 0;
				is.adval = 1;
				break;

			case notinreg:
				is = insalt(assdest.answhere);
				if (!is.adval) {
					int   r = getreg(nsp.fixed);
					load_store(i_ldq, r, is.b);
					nsp = guardreg(r, nsp);
					is.adval = 1;
					is.b.base = r;
					is.b.offset = 0;
				} else {
					is.b.offset = is.b.offset << 3;
				}
				break;

#if 0
			case bitad:
				is = bitadalt(assdest.answhere);
				break;
#endif

			default:
				error(ERR_INTERNAL, "Wrong assbits");
			}
			/*	  setbitadalt (assdest.answhere, is);*/
		} else if (name(e) == ass_tag
		           && assdest.answhere.discrim == notinreg
		           && assdest.ashwhere.ashsize == assdest.ashwhere.ashalign) {
			instore is;
			is = insalt(assdest.answhere);

			if (!is.adval) {
				/*
				 * This is an indirect assignment, so make it direct
				 * by loading pointer into a register (and remember it)
				 */
				int   r = getreg(nsp.fixed);
				load_store(i_ldq, r, is.b);
				nsp = guardreg(r, nsp);
				is.adval = 1;
				is.b.base = r;
				is.b.offset = 0;
				setinsalt(assdest.answhere, is);
				keepexp(lhs, assdest.answhere);
			}
		}

		/*
		 * Evaluate source into assignment destination and move it into dest
		 * - could use assignment as value
		 */
		contreg = code_here(rhs, guard(assdest, nsp), assdest);

		switch (assdest.answhere.discrim) {
		case inreg: {
			int a = regalt(assdest.answhere);

			keepreg(rhs, a);
			/* remember that source has been evaluated into a */
			clear_dep_reg(lhs);
			/* forget register dependencies on destination */
			move(assdest.answhere, dest, nsp, 1);
			break;
		}

		case infreg: {
			freg frg;
			int   r;

			frg = fregalt(assdest.answhere);
			r = frg.fr + 32;

			if (frg.type == IEEE_double) {
				r = -r;
			}

			keepreg(rhs, r);
			/* remember that source has been evaluated into a */
			clear_dep_reg(lhs);
			/* forget register dependencies on destination */
			move(assdest.answhere, dest, nsp, 1);
			break;
		}

		/* case bitad: */
		case notinreg:
			if (contreg != NOREG && name(e) == ass_tag) {
				ans aa;
				space nnsp;

				if (contreg > 0 && contreg < 31) {
					setregalt(aa, contreg);
					nnsp = guardreg(contreg, sp);
				} else {
					freg frg;
					frg.fr = abs(contreg) - 32;
					if (contreg < 0) {
						frg.type = IEEE_double;
					} else {
						frg.type = IEEE_single;
					}
					nnsp = nsp;
					setfregalt(aa, frg);
				}

				move(aa, dest, nnsp, 1);
				clear_dep_reg(lhs);
				/* forget register dependencies on destination */
				if (name(lhs) == name_tag || !dependson(lhs, 0, lhs)) {
					/* remember that dest contains source,
					provided that it is not dependent on it */
					keepcont(lhs, contreg);
				}
				return mka;
			}

			clear_dep_reg(lhs);
			/* forget register dependencies on destination */
			move(assdest.answhere, dest, nsp, 1);
			break;

		case insomereg:
		case insomefreg:
			clear_dep_reg(lhs);
			/* forget register dependencies on destination */
			move(assdest.answhere, dest, guard(assdest, sp), 1);
		}

		/*	if (name (e) == assvol_tag)*/
		/*setnovolatile ();*/
		return mka;
	}

	case compound_tag: {
		exp t = son(e);
		space nsp;
		instore str;
		int r;

		nsp = sp;

		switch (dest.answhere.discrim) {
		case notinreg: {
			str = insalt(dest.answhere); /* it should be !! */

			if (!str.adval) {
				int   r = getreg(sp.fixed);
				nsp = guardreg(r, sp);
				load_store(i_ldq, r, str.b);
				str.adval = 1;
				str.b.base = r;
				str.b.offset = 0;
			}

			for (;;) {
				where newdest;
				instore newis;
				newis = str;
				newis.b.offset += no(t);
				assert(name(t) == val_tag && al2(sh(t)) >= 8);
				setinsalt(newdest.answhere, newis);
				newdest.ashwhere = ashof(sh(bro(t)));
				code_here(bro(t), nsp, newdest);

				if (last(bro(t))) {
					return mka;
				}

				t = bro(bro(t));
			}
		}

		case insomereg: {
			int *sr = someregalt(dest.answhere);

			if (*sr != -1) {
				error(ERR_INTERNAL, "Somereg *2");
			}

			*sr = getreg(sp.fixed);
			setregalt(dest.answhere, *sr);
		}
			FALL_THROUGH;
		case inreg:
			code_here(bro(t), sp, dest);
			r = regalt(dest.answhere);
			assert(name(t) == val_tag);

			if (no(t) != 0) {
				operate_fmt_immediate(i_sll, r,
				                      (al2(sh(t)) >= 8) ? (no(t) << 3) : no(t), r);
			}

			nsp = guardreg(r, sp);
			while (!last(bro(t))) {
				int z;
				t = bro(bro(t));
				assert(name(t) == val_tag);
				z = reg_operand(bro(t), nsp);

				if (no(t) != 0) {
					operate_fmt_immediate
					(i_sll, z, (al2(sh(t)) >= 8) ? (no(t) << 3) : no(t), z);
				}

				operate_fmt(i_bis, z, z, r);
			}

			return mka;

		default:
			error(ERR_INTERNAL, "No Tuples in freg");
		}
		break;
	}

	case nof_tag:
	case concatnof_tag: {
		exp t = son(e);
		space nsp;
		instore str;
		int r, disp = 0;

		nsp = sp;

		switch (dest.answhere.discrim) {
		case notinreg:
			str = insalt (dest.answhere);	/* it should be !! */
			if (!str.adval) {
				int   r = getreg(sp.fixed);
				nsp = guardreg(r, sp);
				load_store(i_ldq, r, str.b);
				str.adval = 1;
				str.b.base = r;
				str.b.offset = 0;
			}

			for (; t != NULL; t = bro(t)) {
				where newdest;
				instore newis;

				newis = str;
				newis.b.offset += disp;
				setinsalt(newdest.answhere, newis);
				newdest.ashwhere = ashof(sh(t));
				code_here(t, nsp, newdest);

				if (last(t)) {
					return mka;
				}

				disp += (rounder(shape_size(sh(t)), shape_align(sh(bro(t)))) >> 3);
			}

			return mka;

		case insomereg: {
			int *sr = someregalt(dest.answhere);

			if (*sr != -1) {
				error(ERR_INTERNAL, "Somereg *2");
			}

			*sr = getreg(sp.fixed);
			setregalt(dest.answhere, *sr);

			/* ,... */
		}
			FALL_THROUGH;
		case inreg: {
			if (t == NULL) {
				return mka;
			}

			code_here(t, sp, dest);
			r = regalt(dest.answhere);
			nsp = guardreg(r, sp);

			while (!last(t)) {
				int z;
				disp += rounder(shape_size(sh(t)), shape_align(sh(bro(t))));
				t = bro(t);
				z = reg_operand(t, nsp);
				operate_fmt_immediate(i_sll, z, disp, z);
				operate_fmt(i_bis, z, z, r);
			}

			return mka;
		}

		default:
			error(ERR_INTERNAL, "No Tuples in freg");
		}

		break;
	}

	case ncopies_tag: {
		exp t = son(e);
		space nsp;
		instore str;
		int i, r, disp = 0;
		nsp = sp;

		switch (dest.answhere.discrim) {
		case notinreg:
			str = insalt (dest.answhere); /* it should be !! */
			if (!str.adval) {
				int   r = getreg(sp.fixed);
				nsp = guardreg(r, sp);
				load_store(i_ldq, r, str.b);
				str.adval = 1;
				str.b.base = r;
				str.b.offset = 0;
			}

			for (i = 1; i <= no(e); i++) {
				where newdest;
				instore newis;
				newis = str;
				newis.b.offset += disp;
				setinsalt(newdest.answhere, newis);
				newdest.ashwhere = ashof(sh(t));
				code_here(t, nsp, newdest);
				disp += (rounder(shape_size(sh(t)), shape_align(sh(t))) >> 3);
			}

			return mka;

		case insomereg: {
			int * sr = someregalt(dest.answhere);
			if (*sr != -1) {
				error(ERR_INTERNAL, "Somereg *2");
			}
			*sr = getreg(sp.fixed);
			setregalt(dest.answhere, *sr);
		}
			FALL_THROUGH;
		case inreg:
			code_here(t, sp, dest);
			r = regalt(dest.answhere);
			nsp = guardreg(r, sp);
			for (i = 1; i <= no(e); i++) {
				int z;
				disp += rounder(shape_size(sh(t)), shape_align(sh(t)));
				z = reg_operand(t, nsp);
				operate_fmt_immediate(i_sll, z, disp, z);
				operate_fmt(i_bis, z, z, r);
			}
			return mka;

		default:
			error(ERR_INTERNAL, "No Tuples in freg");
		}

		break;
	}

	case apply_tag: {
		exp fn = son(e);
		exp par = bro(fn);
		exp list = par;
		int   hda = name(sh(e));
		int   disp;
		int   spar;
		int   fpar = 16;
		instore is;
		is.b.base = SP;
		is.b.offset = 0;
		is.adval = 1;

#ifdef DO_SPECIAL
		if ((disp = specialfn (fn)) > 0) { /* eg function is strlen */
			mka.lab = specialmake(disp, list, sp, dest, exitlab);
			return mka;
		}
#endif

		disp = 0;
		spar = FIRST_INT_ARG; /* register holding 1st integer parameter */

		if (!last(fn)) {
			/* evaluate parameters in turn */
			for (;;) {
				int hd = name(sh(list));
				where w;
				ash ap;
				int paral;
				int parsize;
				ap = ashof(sh(list));
				paral = (ap.ashalign < 32) ? 32 : ap.ashalign;

				if (spar > 21) {
					ap.ashalign = 64;
					paral = 64;
				}

				parsize = ap.ashsize;
				/* all parameters passed on stack are quadword aligned */
				w.ashwhere = ap;
				disp = rounder(disp, paral);
				spar = FIRST_INT_ARG + (disp >> 6);
				fpar = FIRST_FLOAT_ARG + (disp >> 6);

				if (disp > 448) {
					spar = 22;
					fpar = 22;
				}

				if (is_floating(hd) && disp + parsize <= 384) {
					freg frg;
					ans ansfr;
					frg.fr = fpar++;

					if (hd != shrealhd) {
						frg.type = IEEE_double;
					} else {
						frg.type = IEEE_single;
					}

					setfregalt(ansfr, frg);
					w.answhere = ansfr;
					code_here(list, sp, w);
					/* eval parameter into floating parameter register */
					sp = guardfreg(frg.fr, sp);
				} else if (((valregable(sh(list)) || (name(sh(list)) == cpdhd)) ||
				            (name(sh(list)) == nofhd)) && spar <= 21) {
					/* compound types are always passed in registers
					   (given enough space). */
					ans ansr;
					int par_reg;
					int numleft = parsize - ((LAST_INT_ARG - spar + 1) << 6);
					int pregs_used = min((numleft >> 6) + 6, 6);
					setregalt(ansr, spar);
					w.answhere = ansr;

					for (par_reg = spar; par_reg < spar + pregs_used; ++par_reg) {
						sp = guardreg(par_reg, sp);
					}

					sp = guardreg(spar, sp);
					code_here(list, sp, w);
					if (numleft > 0) {
						is.b.offset += (numleft >> 3); /* += number of bytes remaining */
					}
				} else {
					/*
					 * Pass remaining parameters on the stack.
					 * The parameters are aligned on 8 byte boundaries.
					 */
					setinsalt(w.answhere, is);
					is.b.offset += (max(ap.ashsize, REG_SIZE) >> 3);
					/* 'size' was used here */
					code_here(list, sp, w);
					/* eval parameter into argument space on stack */
				}

				if (name(list) == caller_tag) {
					no(list) = disp;
				}

				disp += parsize;
				disp = rounder(disp, REG_SIZE);

				if (last(list)) {
					break;
				}

				list = bro(list);
			}
		}

		if (name(fn) == name_tag && name(son(fn)) == ident_tag
		    && (son(son(fn)) == NULL || name(son(son(fn))) == proc_tag)) {
			/* the procedure can be entered directly */
			if (			/*!tlrecurse*/1) {
				baseoff a;
				integer_jump_external(i_jsr, 26, boff(son(fn)));
				a.base = RA;
				a.offset = 0;
				load_store(i_ldgp, GP, a);
			} else {
				if (Has_fp) {
					baseoff b;
					b.base = FP;
					b.offset = (frame_size + callee_size) >> 3;
					restore_sregs(fixdone, fltdone);
					operate_fmt(i_bis, FP, FP, SP);
					load_store(i_ldq, FP, b);
				} else {
					baseoff b;
					b.base = SP;
					b.offset = (frame_size + callee_size) >> 3;

					restore_sregs(fixdone, fltdone);
					load_store(i_lda, SP, b);
				}
				integer_jump_external(i_jmp, 31, boff(son(fn)));
				if (as_file) {
					asm_printf(" # Tail recursion\n");
				}

			}
		} else {
			/* the address of the proc is evaluated and entered indirectly */
			int destreg = reg_operand(fn, guardreg(26, sp));
			operate_fmt(i_bis, destreg, destreg, PV);
			integer_jump(i_jsr, RA, destreg, 0);
			load_store(i_ldgp, GP, procbase);
		}

		if (in_general_proc) {
			/* Temporary */
			/*	operate_fmt_immediate(i_addq,SP,(callee_size+frame_size)>>3,FP);*/
		}

		clear_all(); /* forget all register memories */

		{
			ans aa;

			if (is_floating(hda)) {
				freg frg;
				frg.fr = 0;

				if (hda != shrealhd) {
					frg.type = IEEE_double;
				} else {
					frg.type = IEEE_single;
				}

				setfregalt(aa, frg);
				move(aa, dest, sp, 1);
				/* move floating point result of application to destination */
			} else {
				setregalt(aa, RESULT_REG);
				mka.regmove = 0;
				move(aa, dest, sp, 1);
				/* move floating point result of application to destination */
			}

			/* else struct results are moved by body of proc */
		}

		return mka;
	}

	case caller_tag: {
		e = son(e);
		goto tailrecurse;
	}

	case apply_general_tag: {
		exp fn = son(e);
		exp callers = bro(fn);
		exp cllees = bro(callers);
		exp postlude = bro(cllees);
		space nsp;
		int postlude_arg_space;
		nsp = sp;

		if (no(callers) != 0) {
			nsp = do_callers(son(callers), sp, &sizecallers);
		} else {
			sizecallers = 0;
		}

		if ((in_vcallers_apply = call_has_vcallers(cllees))) {
			sizecallers = 12 * REG_SIZE;
		} else {
			sizecallers = 6 * REG_SIZE;
		}

		IGNORE make_code(cllees, nsp, nowhere, 0);
		if (name(fn) == name_tag && name(son(fn)) == ident_tag &&
		    (son(son(fn)) == NULL || name(son(son(fn))) == proc_tag ||
		     name(son(son(fn))) == general_proc_tag)) {
			baseoff a;
			a.base = RA;
			a.offset = 0;
			integer_jump_external(i_jsr, 26, boff(son(fn)));
			load_store(i_ldgp, GP, a);
		} else {
			integer_jump_fn(i_jmp, 31, fn, sp);
		}

		clear_all();

		{
			int hda = name(sh(e));
			ans aa;
			if (is_floating(hda)) {
				freg frg;
				frg.fr = 0;
				if (hda != shrealhd) {
					frg.type = IEEE_double;
				} else {
					frg.type = IEEE_single;
				}
				setfregalt(aa, frg);
				move(aa, dest, sp, 1);
				/* move floating point result of application
				   to destination */
			} else {
				setregalt(aa, RESULT_REG);
				mka.regmove = RESULT_REG;
				move(aa, dest, sp, 1);
				/* move floating point result of application to destination */
			}
			/* else struct results are moved by body of proc */
		}

		if (in_vcallers_apply) {
			postlude_arg_space = max(max_args, sizecallers);
		} else {
			postlude_arg_space = max(max_args, 6 * PTR_SZ);
		}

		if (call_is_untidy(cllees)) {
			operate_fmt_immediate(i_subq, SP, postlude_arg_space >> 3, SP);
			reset_tos();
			assert(name(bro(cllees)) == top_tag);
		} else if (postlude_has_call(e)) {
			exp x = son(callers);
			postlude_chain p;

			for (;;) {
				if (name(x) == caller_tag) {
					no(x) += postlude_arg_space;
				}

				if (last(x)) {
					break;
				}

				x = bro(x);
			}

			asm_comment("In postlude, with call");
			/* operate_fmt_immediate(i_subq,SP,max_args>>3,SP);*/

			mka.regmove = NOREG;
			update_plc(old_postludes, postlude_arg_space);
			p.postlude = postlude;
			p.outer = old_postludes;
			old_postludes = &p;
			operate_fmt_immediate(i_subq, SP, postlude_arg_space >> 3, SP);
			IGNORE make_code(postlude, sp, nowhere, 0);
			operate_fmt_immediate(i_addq, SP, postlude_arg_space >> 3, SP);
			old_postludes = p.outer;
			update_plc(old_postludes, -postlude_arg_space);
		} else {
			IGNORE make_code(postlude, sp, nowhere, 0);
		}

		in_vcallers_apply = 0;

		return mka;
	}

	case caller_name_tag:
		return mka;

	case make_callee_list_tag: {
		int size  = ((no(e) >> 3) + 39) & ~7;
		int alloc_size;
		bool vc = call_has_vcallees(e);
		exp list = son(e);
		instore is;
		where w;
		baseoff b;
		int disp = 0;
		ash ap;
		exp anc = father(e);

		if (call_has_vcallers(e)) {
			alloc_size = size + (12 * (PTR_SZ >> 3));
			sizecallers = (12 * (PTR_SZ));
		} else {
			alloc_size = size + ((name(anc) == tail_call_tag) ? (6 * PTR_SZ >> 3) :
			                     (sizecallers >> 3));
		}

		b.base = SP;
		operate_fmt_immediate(i_subq, SP, alloc_size, SP);

		if (name(anc) == tail_call_tag) {
			/*b.offset = alloc_size - (PTR_SZ>>3) - arg_stack_space;*/
			b.offset = alloc_size - (PTR_SZ >> 3);
			load_store(i_stq, FP, b);
		} else {
			b.offset = alloc_size - (PTR_SZ >> 3) - (sizecallers >> 3);
			load_store(i_stq, FP, b);
		}

#if 0
		if (!Has_fp) {
			operate_fmt_immediate(i_addq, SP, size, FP);
		}
#endif

		update_plc(old_postludes, alloc_size << 3);
		if (no(e)) {
			int lastpar = 0;

			for (; !lastpar; list =  bro(list)) {
				ap = ashof(sh(list));
				disp = rounder(disp, ap.ashalign);
				is.b.offset = disp >> 3;
				is.b.base = SP;
				is.adval = 1;
				w.ashwhere = ap;
				setinsalt(w.answhere, is);
				code_here(list, sp, w);
				disp = rounder(disp + ap.ashsize, PTR_SZ);
				/*	disp = rounder(disp+ap.ashsize,is32(sh(list))?32:64);*/
				lastpar = last(list);
			}
		}

		update_plc(old_postludes, -alloc_size << 3);

#if 1
		if (vc  && (name(anc) == apply_general_tag)) {
			operate_fmt_immediate(i_addq, SP, alloc_size, FP);
		}
#endif

		return mka;
	}

	case same_callees_tag: {
		baseoff b;
		bool vc = call_has_vcallees(e);
		space nsp;

		if (Has_vcallees) {
			int rsize = getreg(sp.fixed);
			int rsrc, rdest;
			int le = new_label();
			int lb = new_label();
			int tmp;
			nsp = guardreg(rsize, sp);
			tmp = getreg(nsp.fixed);
			nsp = guardreg(tmp, nsp);
			rsrc = getreg(nsp.fixed);
			nsp = guardreg(rsrc, nsp);
			rdest = getreg(nsp.fixed);
			nsp = guardreg(rdest, nsp);
			operate_fmt(i_bis, SP, SP, tmp);
			operate_fmt(i_subq, FP, local_reg, rsize);

			if (!Has_no_vcallers && !call_has_vcallers(e)) {
				operate_fmt_immediate(i_subq, rsize, 6 * PTR_SZ >> 3, rsize);
			}

			if ((sizecallers >> 3) > arg_stack_space) {
				operate_fmt_immediate(i_addq, rsize,
				                      ((sizecallers >> 3) - arg_stack_space), rsize);
			}

			operate_fmt(i_subq, SP, rsize, SP);
			b.base = tmp;
			b.offset = - (PTR_SZ >> 3) - (sizecallers >> 3);
			load_store(i_stq, FP, b);
			operate_fmt_immediate(i_subq, FP, 4 * (PTR_SZ >> 3) + (arg_stack_space), rsrc);
			operate_fmt_immediate(i_subq, tmp, (4 * (PTR_SZ >> 3)) + (sizecallers >> 3), rdest);

			setnoat();
			operate_fmt(i_cmpeq, rdest, SP, AT);
			integer_branch(i_bne, AT, le);
			setat();
			set_label(lb);
			b.base = rsrc;
			b.offset = - (PTR_SZ >> 3);
			load_store(i_ldq, rsize, b);
			b.base = rdest;
			load_store(i_stq, rsize, b);
			operate_fmt_immediate(i_subq, rsrc, PTR_SZ >> 3, rsrc);
			operate_fmt_immediate(i_subq, rdest, PTR_SZ >> 3, rdest);
			setnoat();
			operate_fmt(i_cmpeq, rdest, SP, AT);
			integer_branch(i_beq, AT, lb);
			setat();
			set_label(le);

			if (vc) {
				operate_fmt(i_bis, tmp, tmp, FP);
			}
		} else {
			int cs = callee_size >> 3;
			int i;
			int tr = getreg(sp.fixed);
			operate_fmt_immediate(i_subq, SP, cs + (sizecallers >> 3), SP);
			b.base = SP;
			b.offset = cs - (PTR_SZ >> 3) /*-arg_stack_space*//*-(sizecallers>>3)*/;
			load_store(i_stq, FP, b);

			for (i = cs - (4 * 8); i > 0; i -= 8) {
				b.base = FP;
				b.offset = i - cs - 8 - (arg_stack_space);
				load_store(i_ldq, tr, b);
				b.base = SP;
				b.offset = i - 8;
				load_store(i_stq, tr, b);
			}

			if (vc) {
				operate_fmt_immediate(i_addq, SP, cs + (sizecallers >> 3), FP);
			}
		}

		return mka;
	}

	case make_dynamic_callee_tag: {
		bool vc = call_has_vcallees(e);
		exp anc = father(e);
		int extra_space;
		int rptr, rsize, rdest, tempreg, ls, le;
		space nsp;
		baseoff b;
		extra_space = (name(anc) == apply_general_tag) ? (sizecallers >> 3) : arg_stack_space;
		rptr = getreg(sp.fixed);
		load_reg(son(e), rptr, sp);
		nsp = guardreg(rptr, sp);
		rsize = getreg(nsp.fixed);
		load_reg(bro(son(e)), rsize, sp);
		nsp = guardreg(rsize, nsp);
		rdest = getreg(nsp.fixed);
		nsp = guardreg(rdest, nsp);
		tempreg = getreg(nsp.fixed);
		operate_fmt_immediate(i_addq, rsize, (4 * (PTR_SZ >> 3) + extra_space) + 7, rdest);
		operate_fmt_immediate(i_bic, rdest, 7, rdest);
		b.base = SP;
		b.offset = - (PTR_SZ >> 3) - (sizecallers >> 3);
		load_store(i_stq, FP, b);

		if (vc) {
			operate_fmt(i_bis, SP, SP, FP);
		}

		operate_fmt(i_subq, SP, rdest, SP);
		operate_fmt(i_bis, SP, SP, rdest);
		ls = new_label();
		le = new_label();
		integer_branch(i_ble, rsize, le);
		b.offset = 0;
		set_label(ls);
		b.base = rptr;
		load_store(i_ldq, tempreg, b);
		b.base = rdest;
		load_store(i_stq, tempreg, b);
		operate_fmt_immediate(i_addq, rdest, (PTR_SZ >> 3), rdest);
		operate_fmt_immediate(i_addq, rptr, (PTR_SZ >> 3), rptr);
		operate_fmt_immediate(i_subq, rsize, (PTR_SZ >> 3), rsize);
		integer_branch(i_bgt, rsize, ls);
		set_label(le);
		return mka;
	}

	case tail_call_tag: {
		exp fn = son(e);
		exp cllees = bro(fn);
		exp bdy = son(crt_proc);
		int stack_space;
		int rsize = -1;
		stack_space = max(arg_stack_space, 6 * (PTR_SZ >> 3));

		if (name(cllees) == make_callee_list_tag) {
			code_here(cllees, sp, nowhere);
		}

		for (; name(bdy) == dump_tag || name(bdy) == diagnose_tag; bdy = son(bdy))
			;

		while (name(bdy) == ident_tag && isparam(bdy)) {
			/* go throught the current callers, making sure they are in the right place */
			exp sbody = son(bdy);
			baseoff b;

			if (Has_fp) {
				b.base = FP;
				b.offset = (no(sbody) >> 3) - stack_space;
			} else {
				b.base = SP;
				b.offset = (no(sbody) + frame_size + callee_size) >> 3;
			}

#if 0


			b.base = FP;
			b.offset = (no(sbody) >> 3) - (PTR_SZ >> 3)  ; /* This will work its way through the caller param area */
			b.offset = no(sbody) >> 3;
#endif

			if (name(sbody) == formal_callee_tag) {
				if ((props(bdy) & inanyreg)) {
					b.offset -= callee_size >> 3;
					if (isvar(bdy)) {
						if (is_floating(name(sh(sbody)))) {
							float_load_store((name(sh(sbody)) == shrealhd) ? i_sts : i_stt, no(bdy), b);
						} else {
							load_store(is64(sh(sbody)) ? i_stq : i_stl, no(bdy), b);
						}
					}
				}
			} else if (props(sbody) == 0 && (props(bdy) &inanyreg) != 0) {
				/* move from reg to store */
				if (isvar(bdy)) {
					if (is_floating(name(sh(sbody)))) {
						float_load_store((name(sh(sbody)) == shrealhd) ? i_sts : i_stt, no(bdy), b);
					} else {
						load_store(is64(sh(sbody)) ? i_stq : i_stl, props(sbody), b);
					}
				}
			} else if (props(sbody) != 0 && (props(bdy) & inanyreg) == 0) {
				/* move from store to reg */
				if (is_floating(name(sh(sbody)))) {
					float_load_store((name(sh(sbody)) == shrealhd) ? i_lds : i_ldt, props(sbody), b);
				} else {
					if (isvis(bdy) && last_param(bdy) && !Has_no_vcallers) {
						int this_reg = props(sbody);
						int r;
						assert(this_reg >= 16);
						b.offset = ((this_reg + 1 - 16) << 3) + ((gpdumpstart - frame_size) >> 3);
						for (r = this_reg + 1; r <= LAST_INT_ARG; ++r) {
							load_store(i_ldq, r, b);
							b.offset += (REG_SIZE >> 3);
						}
						b.offset = ((paramsdumpstart - frame_size) >> 3);
						for (r = FIRST_FLOAT_ARG; r <= LAST_FLOAT_ARG; ++r) {
							float_load_store(i_ldt, r, b);
							b.offset += (REG_SIZE >> 3);
						}
						b.offset = ((this_reg - 16) << 3) + ((gpdumpstart - frame_size) >> 3);
						load_store(is64(sh(sbody)) ? i_ldq : i_ldl, props(sbody), b);
					} else {
						load_store(is64(sh(sbody)) ? i_ldq : i_ldl, props(sbody), b);
					}
				}
			} else if (props(sbody) != 0 && (props(sbody) != no(bdy))) {
				/* move from reg to reg */
				if (is_floating(name(sh(sbody)))) {
					float_op(i_cpys, no(bdy), no(bdy), props(sbody));
				} else {
					operate_fmt(i_bis, no(bdy), no(bdy), props(sbody));
				}
			}

			bdy = bro(sbody);
		}

		restore_sregs(fixdone, fltdone);

		/*
		 * Allocate space on the frame for the number of callees used in the
		 * tail call which exceed the number of callees for this procedure
		 */
		if (name(cllees) == make_callee_list_tag) {
			int x = (((no(cllees) >> 3) + 39) & ~7) + stack_space;
			baseoff b;
			int i;
			int rndcllees = ((no(cllees) >> 3) + 7) & ~7;
			setnoat();

			for (i = no(cllees) >> 3; i > 0; i -= (PTR_SZ >> 3)) {
				b.base = SP;
				b.offset = i - (PTR_SZ >> 3);
				load_store(i_ldq, AT, b);
				b.base = FP;
				b.offset = i - (4 * (PTR_SZ >> 3)) - (rndcllees + (PTR_SZ >> 3))
				           - stack_space;
				load_store(i_stq, AT, b);
			}

			setat();
			operate_fmt_immediate(i_subq, FP, x, SP);
		} else if (name(cllees) == make_dynamic_callee_tag) {
			int rdest, rsource, tempreg, le, ls;
			space nsp;
			baseoff b;
			rdest = getreg(sp.fixed);
			nsp = guardreg(rdest, sp);
			rsource = getreg(nsp.fixed);
			load_reg(son(cllees), rsource, sp);
			nsp = guardreg(rsource, nsp);
			rsize = getreg(nsp.fixed);
			load_reg(bro(son(cllees)), rsize, nsp);
			nsp = guardreg(rsize, nsp);
			tempreg = getreg(nsp.fixed);
			operate_fmt_immediate(i_subq, FP, 4 * (PTR_SZ >> 3) + stack_space, rdest);
			operate_fmt_immediate(i_addq, rsize, 7, rsize);
			operate_fmt_immediate(i_bic, rsize, 7, rsize);
			operate_fmt(i_addq, rsource, rsize, rsource);
			le = new_label();
			ls = new_label();
			integer_branch(i_ble, rsize, le);
			set_label(ls);
			b.base = rsource;
			b.offset = - (PTR_SZ >> 3);
			load_store(i_ldq, tempreg, b);
			b.base = rdest;
			load_store(i_stq, tempreg, b);
			operate_fmt_immediate(i_subq, rdest, (PTR_SZ >> 3), rdest);
			operate_fmt_immediate(i_subq, rsource, (PTR_SZ >> 3), rsource);
			operate_fmt_immediate(i_subq, rsize, (PTR_SZ >> 3), rsize);
			integer_branch(i_bgt, rsize, ls);
			set_label(le);
			operate_fmt(i_bis, rdest, rdest, SP);
		} else {
			if (Has_vcallees) {
				operate_fmt(i_bis, local_reg, local_reg, SP);
			} else {
				operate_fmt_immediate(i_subq, FP, stack_space + (callee_size >> 3), SP);
			}
		}

		if (Has_vcallees) {
			baseoff b;
			b.base = FP;
			b.offset = (-4 * (PTR_SZ >> 3)) - stack_space;
			load_store(i_ldq, local_reg, b);
		}

		if (!in_general_proc) {
			baseoff b;
			b.base = FP;
			b.offset = - (PTR_SZ >> 3) - arg_stack_space;
			setnoat();
			load_store(i_ldq, AT, b);
			b.base = SP;

			if (name(cllees) != make_dynamic_callee_tag) {
				b.offset = (((no(cllees) >> 3) + 39) & ~7) - (PTR_SZ >> 3);
			} else {
				load_reg(bro(son(cllees)), rsize, sp);
				operate_fmt_immediate(i_addq, rsize, 7, rsize);
				operate_fmt_immediate(i_bic, rsize, 7, rsize);
				operate_fmt_immediate(i_addq, rsize, (39 & ~7) - (PTR_SZ >> 3), rsize);
				operate_fmt(i_addq, rsize, SP, rsize);
				b.base = rsize;
				b.offset = 0;
			}

			load_store(i_stq, AT, b);
			if (Has_vcallees) {
				operate_fmt(i_bis, FP, FP, local_reg);
			}
		}

		{
			int rt = getreg(sp.fixed);
			rt = reg_operand(fn, guardreg(RA, sp));
			operate_fmt(i_bis, rt, rt, PV);
			integer_jump(i_jmp, 31, rt, 0);
			/*integer_jump_external(i_jmp,31,boff(son(fn)));*/
		}

		return mka;
	}

#ifdef return_to_label_tag
	case return_to_label_tag: {
		int r = getreg(sp.fixed);
		where w;
		w.ashwhere.ashsize = 64;
		w.ashwhere.ashalign = 64;
		setregalt(w.answhere, r);
		code_here(son(e), sp, w);
		clear_all();

		if (Has_fp) {
			baseoff b;
			b.base = FP;
			restore_sregs(fixdone, fltdone);
			if (Has_vcallees) {
				b.offset = -4 * (PTR_SZ >> 3);
				load_store(i_ldq, local_reg, b);
			}
			b.offset = - (PTR_SZ >> 3) - arg_stack_space;
			operate_fmt(i_bis, FP, FP, SP);
			load_store(i_ldq, FP, b);
		} else if (frame_size != 0) {
			restore_sregs(fixdone, fltdone);
			operate_fmt_immediate(i_addq, SP, frame_size >> 3, SP);
		}

		integer_jump(i_jmp, 31, r, 0);
		clear_all();
		return mka;
	}
#endif

	case untidy_return_tag:
	case res_tag: {
		where w;
		w.answhere = procans;
		w.ashwhere = ashof(sh(son(e)));
		code_here(son(e), sp, w);

		/* evaluate result value */
		if (name(e) == untidy_return_tag) {
			asm_comment("untidy return");
		}

		clear_all ();		/* clear all register memories */
		if (rscope_level == 0) {/* normal proc body */
			if (name(son(e)) == apply_tag && props(e)) {
				return mka;
			}

			/* was a tail recursion */
			if (frame_size == 0 && !Has_fp) {
				integer_jump(i_ret, 31, RA, 1);
			}

			if (result_label != 0) {
				integer_branch(i_br, 31, result_label);
				asm_comment("Return");
			} else {
				if ((fixdone | fltdone) == 0) {
					result_label = new_label();
					set_label(result_label);
				}

				if (Has_fp) {
					baseoff b;
					b.base = FP;
					restore_sregs(fixdone, fltdone);

					if (Has_vcallees) {
						b.offset = -4 * (PTR_SZ >> 3) - arg_stack_space;
						load_store(i_ldq, local_reg, b);
					}

					b.offset = (in_general_proc) ? (-PTR_SZ >> 3) : (-arg_stack_space - (PTR_SZ >> 3));;
					b.offset = (-arg_stack_space - (PTR_SZ >> 3));;
#if 0
					if (arg_stack_space && in_general_proc && name(e) == res_tag) {
						operate_fmt_immediate(i_addq, FP, arg_stack_space, SP);
					}

					else
#endif
					if (name(e) == res_tag) {
						operate_fmt(i_bis, FP, FP, SP);
					}
					load_store(i_ldq, FP, b);
				} else {
					baseoff a;
					restore_sregs(fixdone, fltdone);
					/* restore dumped value of s-regs on entry */
					a.base = SP;
					a.offset = (callee_size + frame_size) >> 3;

					if (a.offset != 0 && name(e) == res_tag) {
						load_store(i_lda, SP, a);
					}

					/* reset stack ptr */
				}

				integer_jump(i_ret, 31, RA, 1);
			}
		} else {			/* inlined result */
			if (rscope_label == 0) {
				rscope_label = new_label();
			}

			if (rscope_label != exitlab) {
				integer_branch(i_br, 31, rscope_label);
				/*
				  uncond_ins (i_b, rscope_label);*/
			}
		}

		sizecallers = 0;
		return mka;
	}

	case diagnose_tag:
		diag3_driver->output_diag(dno(e), 0, e);
		/*      output_symbolic_diagnostic(as_file,dno(e));*/
		mka = make_code(son(e), sp, dest, exitlab);
		diag3_driver->output_end_scope(dno(e), e);

		return mka;

	case solve_tag: {
		exp m = bro(son(e));
		int   l = exitlab;

		if (dest.answhere.discrim == insomereg) {
			/* choose register for result */
			int  *sr = someregalt(dest.answhere);
			if (*sr != -1) {
				error(ERR_INTERNAL, "Somereg *2");
			}
			*sr = getreg(sp.fixed);
			setregalt(dest.answhere, *sr);
		} else if (dest.answhere.discrim == insomefreg) {
			somefreg sfr;
			freg fr;
			sfr = somefregalt(dest.answhere);
			if (*sfr.fr != -1) {
				error(ERR_INTERNAL, "Somefreg *2");
			}
			*sfr.fr = getfreg(sp.flt);
			fr.fr = *sfr.fr;
			fr.type = sfr.type;
			setfregalt(dest.answhere, fr);
		}

		for (;;) {
			/* set up all the labels in the component labst_tags */
			no(son(m)) = new_label();
			if (last(m)) {
				break;
			}
			m = bro(m);
		}

		/* evaluate all the component statements */
		for (m = son(e); ; m = bro(m)) {
			int   fl = make_code(m, sp, dest, l).lab;
			clear_all();

			if (fl != 0) {
				l = fl;
			}

			if (!last (m)) {	/* jump to end of solve */
				if (l == 0) {
					l = new_label();
				}

				if (name(sh(m)) != bothd) {
					integer_branch(i_br, 31, l);
				}
			}

			if (last(m)) {
				mka.lab = l;
				return mka;
			}
		}
	}

	/* case_tag now uses the INT64 type.  */
	case case_tag: {
		int   r = reg_operand(son(e), sp);
		/* evaluate controlling integer into reg r */
		mm lims;
		exp z = bro(son(e));
		exp zt = z;
		INT64  n;
		INT64  l;
		INT64  u;
		INT64 xt, yt;
		int control_sgned = is_signed(sh(son(e)));

		u = make_INT64(0x80000000, 0x00000000);
		/*INT64_assign(u,smin);*/
		asm_comment("begin case");
		INT64_assign(l, exp_to_INT64(zt));

		for (n = make_INT64(0, 1);; n = INT64_increment(n)) {
			/* Calculate crude criterion for using jump vector or branches */
			if (!(INT64_eq(INT64_increment(u), exp_to_INT64(zt))) &&
			    (son(zt) != NULL)) {
				n = INT64_increment(n);
			}

			if (last(zt)) {
				u = (son(zt) != NULL) ? exp_to_INT64(son(zt)) : exp_to_INT64(zt);
				break;
			}

			if (son(zt) != NULL) {
				u = exp_to_INT64(son(zt));
			} else {
				if (INT64_eq(INT64_increment(u), exp_to_INT64(zt))) {
					u = INT64_increment(u);
				}
			}

			zt = bro(zt);
		}

		/* Now l is lowest controlling value and u is highest */
		/*	 The above actually means: */
		if (control_sgned) {
			xt = (INT64_subtract(INT64_shift_right(u, 1, 1),
			                     INT64_shift_right(l, 1, 1), 1));
			yt = (INT64_subtract(INT64_divide(INT64_mult(n, n, 1),
			                                  make_INT64(0, 4), 1),
			                     make_INT64(0, 3), 1));
		} else {
			unsigned long uu = unsigned_rep(u, sh(son(e)));
			unsigned long lu = unsigned_rep(l, sh(son(e)));
			xt = (INT64_subtract(INT64_shift_right(uu, 1, 1),
			                     INT64_shift_right(lu, 1, 1), 1));
			yt = (INT64_subtract(INT64_divide(INT64_mult(n, n, 1),
			                                  make_INT64(0, 4), 1),
			                     make_INT64(0, 3), 1));
		}

		/*
		 * Space-time product criterion for jump vector instead of
		 * tests and branches.
		 */
		if (xt <= yt) {
			/* use jump vector */
			int   endlab = new_label();
			int   veclab = next_dlab_sym();
			baseoff zeroveclab;
			baseoff zero3;
			int  rtmp = getreg(guardreg(r, sp).fixed); /* could use AT */

			zero3.base = rtmp;
			zero3.offset = 0;
			zeroveclab.offset = 0;
			zeroveclab.base = veclab;

			n = l;
			start_new_capsule(false);

			if (as_file) {
				asm_printop(".rdata\n$$%d:", veclab);
			}

			out_common(0, irdata);
			out_common(tempsnos[veclab - 32], ilabel);

			for (;;) {
				for (; INT64_lt(n, exp_to_INT64(z));
				     n = INT64_increment(n)) {
					/* o/p jump vector */
					if (as_file) {
						asm_printop(".gprel32 $%d", endlab);
					}
					out_value(-endlab, igprel32, make_INT64(0, 0), 1);
				}

				u = (son(z) == NULL) ? n : exp_to_INT64(son(z));
				for (; INT64_leq(n, u) /*n <= u*/; n = INT64_increment(n)/*n++*/) {
					if (as_file) {
						asm_printop(".gprel32 $%d", no(son(pt(z))));
					}
					out_value(-no(son(pt(z))), igprel32, make_INT64(0, 0), 1);
				}

				if (last(z)) {
					break;
				}

				z = bro(z);
			}

			set_text_section();
			setnoat();
			load_store(i_lda, AT, zeroveclab);

			if (!INT64_eq(l, zero_int64) /*l != 0*/) {
				int rtmp2;
				INT64 lit;
				space newsp;
				newsp = guardreg(r, sp);
				newsp = guardreg(rtmp, newsp);
				rtmp2 = getreg(newsp.fixed);
				lit = INT64_subtract(make_INT64(0, 0), l, 1);
				operate_fmt_big_immediate(i_addq, r, lit, rtmp);
				lit = INT64_increment(INT64_subtract(u, l, 1));
				operate_fmt_big_immediate(i_cmpult, rtmp, lit, rtmp2);
				integer_branch(i_beq, rtmp2, endlab);
				operate_fmt(i_s4addq, rtmp, AT, rtmp);
			} else {
				int rtmp2;
				space newsp;
				newsp = guardreg(r, sp);
				newsp = guardreg(rtmp, newsp);
				rtmp2 = getreg(newsp.fixed);
				load_store_immediate(i_ldiq, rtmp2, INT64_increment(u));

				/*	   operate_fmt(i_subq,r,rtmp2,rtmp);
					   integer_branch(i_bge,rtmp,endlab); */
				operate_fmt(i_cmpule, rtmp2, r, rtmp);
				integer_branch(i_bne, rtmp, endlab);
				operate_fmt(i_s4addq, r, AT, rtmp);
			}

			setat();
			load_store(i_ldl, rtmp, zero3);
			operate_fmt(i_addq, rtmp, GP, rtmp);
			integer_jump(i_jmp, 31, rtmp, endlab); /* endlab is hint */
			set_label(endlab);
			close_capsule();
			asm_comment("end case");

			return mka;
		} else {
			int over = 0;	/* use branches - tests are already ordered */
			int rtmp = getreg(guardreg(r, sp).fixed);
			bool usw;
			lims = maxmin(sh(son(e)));
			usw = !is_signed(sh(son(e)));

			for (;;) {
				int lab = no(son(pt(z))); /* can this be big */
				l = exp_to_INT64(z);

				if (isbigval(son(pt(z)))) {
					error(ERR_SERIOUS, "64 bit labels not implemented");
				}

				if (son (z) == NULL) { /* only single test required */
					operate_fmt_big_immediate(i_cmpeq, r, l, rtmp);
					integer_branch(i_bne, rtmp, lab);
					if (INT64_eq(l, lims.maxi)) {
						lims.maxi = INT64_decrement(lims.maxi);
					} else if (INT64_eq(l, lims.mini)) {
						lims.mini = INT64_increment(lims.mini);
					}
				} else if (u = exp_to_INT64(son(z)),
				           INT64_leq(lims.mini, l) || usw) {
					/*	       if (INT64_lt(lims.maxi,INT64_and(INT64_not(usw),u))){ */
					if (INT64_leq(lims.maxi, u) && !usw) {
						/* have already tested lower */
						operate_fmt_big_immediate(i_cmplt, r, l, rtmp);
						integer_branch(i_beq, rtmp, lab);
						lims.maxi = INT64_decrement(l);
					} else {
						if (over == 0) {
							over = new_label();
						}
						operate_fmt_big_immediate(i_cmplt, r, l, rtmp);
						integer_branch(i_bne, rtmp, over);
						operate_fmt_big_immediate(i_cmple, r, u, rtmp);
						integer_branch(i_bne, rtmp, lab);
						lims.mini = INT64_increment(u);
					}
				} else if  (INT64_lt(u, lims.maxi)) {
					/* lower is <= lower limit of shape */
					operate_fmt_big_immediate(i_cmple, r, u, rtmp);
					integer_branch(i_bne, rtmp, lab);
					lims.mini = INT64_increment(u);
				} else {	/* upper is >= upper limit of shape */
					integer_branch(i_br, 31, lab);
				}

				if (last(z)) {
					if (over != 0) {
						set_label(over);
					}
					asm_comment("end case");
					return mka;
				}

				z = bro(z);
			}
		}
	}

	case plus_tag:
	case offset_add_tag: {
		if (optop(e)) {
			mka.regmove = comm_op(e, sp, dest, (dest.ashwhere.ashsize == 32) ?  i_addl : i_addq);
			return mka;
		}
#if 0
		if (error_treatment_is_trap(e) /*&& is_signed(sh(e))*/) {
			mka.regmove = comm_op(e, sp, dest, (dest.ashwhere.ashsize == 32) ?  i_addlv : i_addqv);
			return mka;
		}
#endif
		else {
			int r1 = reg_operand(son(e), sp);
			int r2, r0;
			int over = new_label();
			int trap = trap_label(e);
			space nsp;
			ans aa;
			nsp = guardreg(r1, sp);
			r2 = reg_operand(bro(son(e)), nsp);
			nsp = guardreg(r2, nsp);
			r0 = getreg(nsp.fixed);
			nsp = guardreg(r0, nsp);
			operate_fmt(is64(sh(e)) ? i_addq : i_addl, r1, r2, r0);

			switch (name(sh(e))) {
			case s64hd:
			case slonghd: {
				int r3 = getreg(sp.fixed);
				operate_fmt(i_xor, r1, r2, r3);
				integer_branch(i_blt, r3, over);
				operate_fmt(i_xor, r0, r1, r3);

				if (error_treatment_is_trap(e)) {
					integer_branch(i_bge, r3, over);
					do_exception(f_overflow);
				} else {
					integer_branch(i_blt, r3, trap);
				}

				set_label(over);
				break;
			}

			case ulonghd:
			case u64hd: {
				int r3 = getreg(sp.fixed);
				operate_fmt(i_cmpult, r0, r1, r3);

				if (error_treatment_is_trap(e)) {
					int oklab = new_label();
					integer_branch(i_beq, r3, oklab);
					do_exception(f_overflow);
					set_label(oklab);
				} else {
					integer_branch(i_bne, r3, trap);
				}
				break;
			}

			case uwordhd:
				if (error_treatment_is_trap(e)) {
					test_unsigned_and_trap(r0, 0xffff, f_overflow);
				} else {
					test_unsigned(r0, 0xffff, trap);
				}
				break;

			case swordhd:
				if (error_treatment_is_trap(e)) {
					test_signed_and_trap(r0, -0x8000L, 0x7fff, f_overflow);
				} else {
					test_signed(r0, -0x8000L, 0x7fff, trap);
				}
				break;

			case ucharhd:
				if (error_treatment_is_trap(e)) {
					test_unsigned_and_trap(r0, 255, f_overflow);
				} else {
					test_unsigned(r0, 255, trap);
				}
				break;

			case scharhd:
				if (error_treatment_is_trap(e)) {
					test_signed_and_trap(r0, -128, 127, f_overflow);
				} else {
					test_signed(r0, -128, 127, trap);
				}
				break;

			default:
				error(ERR_INTERNAL, "illegal shape");
			}

			setregalt(aa, r0);
			mka.regmove = move(aa, dest, nsp, 0);

			return mka;
		}
	}

	case chvar_tag: {
		int   a;
		int tmpreg;
		int   d;
		ans aa;
		int   nsh = name(sh(e));

		switch (dest.answhere.discrim) {
		case inreg: {
			ash arga;
			arga = ashof(sh(son(e)));

			if (arga.ashsize <= dest.ashwhere.ashsize) {
				dest.ashwhere = arga;
			}

			a = regalt(dest.answhere);
			if (a == NO_REG) {
				a = getreg(sp.fixed);
				setregalt(dest.answhere, a);
				dest.ashwhere.ashsize = shape_size(sh(son(e)));
				dest.ashwhere.ashalign = dest.ashwhere.ashsize;
			}

			code_here(son(e), sp, dest);
			/* evaluate argument into reg */
			break;
		}

		default:
			a = reg_operand(son(e), sp);
			/* evaluate arguement into a */
		}

		setregalt(aa, a);
		if (sh(son(e)) == sh(e)) {
			mka.regmove = move(aa, dest, sp, 1);
			return mka;
		}

		if ((dest.answhere.discrim == inreg) &&
		    (dest.answhere.val.regans == a)) {
			tmpreg = a;
		} else {
			tmpreg = getreg(sp.fixed);
		}

		/*
		 * Destination is 64 bits wide, the only thing we have to worry about
		 * is the conversion of unsigned values to signed, which can be avoided
		 * by the following code.
		 */
		if (nsh >= s64hd) {
			if (convert_shapes(nsh, name(sh(son(e))), a, tmpreg)) {
				setregalt(aa, tmpreg);
			}

			mka.regmove = move(aa, dest, sp, 1);
			return mka;
		}

		if (sh (son (e)) == sh (e) /*|| nsh  >= slonghd*/) {
			/* no changes required, so just move to dest */
			mka.regmove = move(aa, dest, sp, 1);
			return mka;
		}

		switch (dest.answhere.discrim) {
		case insomereg: {
			int  *dr = someregalt(dest.answhere);
			d = getreg(sp.fixed);
			*dr = d;
			goto out;
		}

		case inreg: {
			d = regalt(dest.answhere);
			goto out;
		}

		default:
			/* representation in store will be same so just move */
			move(aa, dest, sp, 1);
			return mka;
		}

out:

		/* d is destination register - do appropriate ands etc */
		if (d == NO_REG) {
			return mka;
		}

		/*       IGNORE convert_shapes(nsh,name(sh(son(e))),a,d);*/
		switch (nsh) {
		case ucharhd:
			if (is_signed(sh(son(e))) && !optop(e)) {
				if (error_treatment_is_trap(e)) {
					int new_lab = new_label();
					integer_branch(i_bge, a, new_lab);
					do_exception(f_overflow);
					set_label(new_lab);
				} else {
					integer_branch(i_blt, a, trap_label(e));
				}
			}

			if (!optop(e)) {
				if (error_treatment_is_trap(e)) {
					test_unsigned_and_trap(a, 255, f_overflow);
				} else {
					test_unsigned(a, 255, trap_label(e));
				}
			}

			operate_fmt_immediate(i_and, a, 255, d);
			break;

		case scharhd:
			if (!is_signed(sh(son(e))) && !optop(e)) {
				setnoat();
				operate_fmt_immediate(i_cmpule, a, 0x7f, AT);

				if (!error_treatment_is_trap(e)) {
					integer_branch(i_beq, AT, trap_label(e));
				} else {
					int new_lab = new_label();
					integer_branch(i_bne, AT, new_lab);
					do_exception(f_overflow);
					set_label(new_lab);
				}
				setat();
			}

			if (!optop(e)) {
				if (error_treatment_is_trap(e)) {
					test_signed_and_trap(a, -128, 127, f_overflow);
				} else {
					test_signed(a, -128, 127, trap_label(e));
				}
			}

			operate_fmt_immediate(i_extqh, a, 1, d);
			operate_fmt_immediate(i_sra, d, REG_SIZE - 8, d);
			break;

		case uwordhd:
			if (is_signed(sh(son(e))) && !optop(e)) {
				if (error_treatment_is_trap(e)) {
					int new_lab = new_label();
					integer_branch(i_bge, a, new_lab);
					do_exception(f_overflow);
					set_label(new_lab);
				} else {
					integer_branch(i_blt, a, trap_label(e));
				}
			}

			if (!optop(e)) {
				if (error_treatment_is_trap(e)) {
					test_unsigned_and_trap(a, 0xffff, f_overflow);
				} else {
					test_unsigned(a, 0xffff, trap_label(e));
				}
			}

			operate_fmt_immediate(i_and, a, (1 << 16) - 1, d);
			break;

		case swordhd:
			if (!is_signed(sh(son(e))) && !optop(e)) {
				setnoat();
				operate_fmt_immediate(i_cmpule, a, 0x7fff, AT);

				if (error_treatment_is_trap(e)) {
					int new_lab = new_label();
					integer_branch(i_bne, AT, new_lab);
					do_exception(f_overflow);
					set_label(new_lab);
				} else {
					integer_branch(i_beq, AT, trap_label(e));
				}
				setat();
			}

			if (!optop(e)) {
				if (error_treatment_is_trap(e)) {
					test_signed_and_trap(a, -0x8000L, 0x7fff, f_overflow);
				} else {
					test_signed(a, -0x8000L, 0x7fff, trap_label(e));
				}
			}

			operate_fmt_immediate(i_sll, a, 48, d);
			operate_fmt_immediate(i_sra, d, 48, d);
			break;

		case ulonghd:
			if (is_signed(sh(son(e))) && !optop(e)) {
				if (error_treatment_is_trap(e)) {
					int new_lab = new_label();
					integer_branch(i_bge, a, new_lab);
					do_exception(f_overflow);
					set_label(new_lab);
				} else {
					integer_branch(i_blt, a, trap_label(e));
				}
			}

			if (!optop(e)) {
				if (error_treatment_is_trap(e)) {
					test_unsigned_and_trap(a, 0xffffffff, f_overflow);
				} else {
					test_unsigned(a, 0xffffffff, trap_label(e));
				}
			}

			operate_fmt_immediate(i_addl, a, 0, d);
			/*operate_fmt_big_immediate(i_and,a,0xffffffff,d);*/
			break;

		case slonghd:
			if (!is_signed(sh(son(e))) && !optop(e)) {
				setnoat();
				operate_fmt_big_immediate(i_cmpule, a, 0x7fffffff, AT);

				if (error_treatment_is_trap(e)) {
					int new_lab = new_label();
					integer_branch(i_bne, AT, new_lab);
					do_exception(f_overflow);
					set_label(new_lab);
				} else {
					integer_branch(i_beq, AT, trap_label(e));
				}
				setat();
			}

			if (!optop(e)) {
				if (error_treatment_is_trap(e)) {
					test_signed_and_trap(a, -0x80000000L, 0x7fffffff, f_overflow);
				} else {
					test_signed(a, -0x80000000L, 0x7fffffff, trap_label(e));
				}
			}

			operate_fmt_immediate(i_sll, a, 32, d);
			operate_fmt_immediate(i_sra, d, 32, d);
			break;

		case s64hd:
			if (!is_signed(sh(e)) && !optop(e)) {
				setnoat();
				operate_fmt_big_immediate(i_cmpule, a, 0x7fffffffffffffffL, AT);

				if (error_treatment_is_trap(e)) {
					int new_lab = new_label();
					integer_branch(i_bne, AT, new_lab);
					do_exception(f_overflow);
					set_label(new_lab);
				} else {
					integer_branch(i_beq, AT, trap_label(e));
				}
				setat();
			}

			if (!optop(e)) {
				if (error_treatment_is_trap(e)) {
					test_signed_and_trap(a, -0x8000000000000000L, 0x7fffffffffffffffL, f_overflow);
				} else {
					test_signed(a, -0x8000000000000000L, 0x7fffffffffffffffL, trap_label(e));
				}
			}

			operate_fmt(i_bis, a, a, d);
			break;

		case u64hd:
			if (is_signed(sh(e)) && !optop(e)) {
				if (error_treatment_is_trap(e)) {
					int new_lab = new_label();
					integer_branch(i_bge, a, new_lab);
					do_exception(f_overflow);
					set_label(new_lab);
				} else {
					integer_branch(i_blt, a, trap_label(e));
				}
			}

			operate_fmt(i_bis, a, a, d);
			break;

		default:
			error(ERR_INTERNAL, "Illegal shape in chvar");
		}

#if 0
		if (nsh == ucharhd) {
			operate_fmt_immediate(i_and, a, 255, d);
		} else if (nsh == uwordhd) {
			operate_fmt_immediate(i_and, a, (1 << 16) - 1, d);
		} else if (nsh == scharhd) {
			/*	      operate_fmt_immediate (i_sll,a,REG_SIZE-8,d);*/
			operate_fmt_immediate(i_extqh, a, 1, d);
			operate_fmt_immediate(i_sra, d, REG_SIZE - 8, d);
		} else if (nsh == swordhd) {
			operate_fmt_immediate(i_sll, a, 32, d);
			operate_fmt_immediate(i_sra, d, 32, d);
		}
#endif

		mka.regmove = d;
		return mka;
	}

	case minus_tag:
	case offset_subtract_tag: {
		if (optop(e)) {
			mka.regmove = non_comm_op(e, sp, dest, is64(sh(e)) ? i_subq : i_subl);
			return mka;
		}
#if 0
		if (error_treatment_is_trap(e) && is_signed(sh(e))) {
			mka.regmove = non_comm_op(e, sp, dest, is64(sh(e)) ? i_subqv : i_sublv);
			return mka;
		}
#endif
		else {
			/*	   if(!optop(e)) check_exception(e,sp);*/
			int r1 = reg_operand(son(e), sp);
			int r2, r3, r0;
			int over = new_label();
			int trap = trap_label(e);
			space nsp;
			ans aa;
			nsp = guardreg(r1, sp);
			r2 = reg_operand(bro(son(e)), nsp);
			nsp = guardreg(r2, nsp);
			r0 = getreg(nsp.fixed);
			nsp = guardreg(r0, nsp);
			operate_fmt((is64(sh(e))) ? i_subq : i_subl, r1, r2, r0);

			switch (name(sh(e))) {
			case s64hd:
			case slonghd:
				r3 = getreg(nsp.fixed);
				operate_fmt(i_xor, r1, r2, r3);
				integer_branch(i_bge, r3, over);
				operate_fmt(i_xor, r0, r1, r3);

				if (error_treatment_is_trap(e)) {
					integer_branch(i_bge, r3, over);
					do_exception(f_overflow);
				} else {
					integer_branch(i_blt, r3, trap);
				}

				set_label(over);
				break;

			case u64hd:
			case ulonghd:
				r3 = getreg(guardreg(r0, nsp).fixed);
				operate_fmt(i_cmpult, r1, r2, r3);

				if (error_treatment_is_trap(e)) {
					int ok_lab = new_label();
					integer_branch(i_beq, r3, ok_lab);
					do_exception(f_overflow);
					set_label(ok_lab);
				} else {
					integer_branch(i_bne, r3, trap);
				}
				break;

			case scharhd:
				if (error_treatment_is_trap(e)) {
					test_signed_and_trap(r0, -128, 127, f_overflow);
				} else {
					test_signed(r0, -128, 127, trap);
				}
				break;

			case ucharhd:
				if (error_treatment_is_trap(e)) {
					test_unsigned_and_trap(r0, 255, f_overflow);
				} else {
					test_unsigned(r0, 255, trap);
				}
				break;

			case swordhd:
				if (error_treatment_is_trap(e)) {
					test_signed_and_trap(r0, -0x8000L, 0x7fff, f_overflow);
				} else {
					test_signed(r0, -0x8000L, 0x7fff, trap);
				}
				break;

			case uwordhd:
				if (error_treatment_is_trap(e)) {
					test_unsigned_and_trap(r0, 0xffff, f_overflow);
				} else {
					test_unsigned(r0, 0xffff, trap);
				}
				break;

			default:
				error(ERR_INTERNAL, "NOT integer in minus with o/f");
			}

			setregalt(aa, r0);
			mka.regmove = move(aa, dest, nsp, 0);

			return mka;
		}

		return mka;
	}

	/* end minus */
	case mult_tag:
	case offset_mult_tag: {
		exp rop = bro(son(e));
		instruction mult_ins;

		if (!optop(e) & error_treatment_is_trap(e)) {
			mult_ins = is64(sh(e)) ? i_mulqv : i_mullv;
		} else {
			mult_ins = is64(sh(e)) ? i_mulq : i_mull;
		}

		if (last(rop) && name(rop) == val_tag && optop(e)) {
			/* multiplication by constant m */
			int   m = no(rop);
			int   p2;

			if (m > 1 && (
			        ((p2 = m) & (m - 1)) == 0 ||
			        (m & (p2 = m + 1)) == 0 ||
			        ((p2 = m - 1) & (m - 2)) == 0))
			{

				/* m = 2^shleng   or  m = 2^(shleng +/- 1) */
				int   r = reg_operand(son(e), sp);
				/* evaluate first arguement */
				int   rr;
				space nsp;
				int   shleng;
				ans aa;

				for (shleng = 0; p2 != 1; shleng++) {
					p2 >>= 1;
				}

				switch (dest.answhere.discrim) {
				case inreg:
					rr = regalt(dest.answhere);
					if (rr != r || (m & (m - 1)) == 0) {
						nsp = sp;
						break;
					}

					FALL_THROUGH;
				default:
					nsp = guardreg(r, sp);
					rr = getreg(nsp.fixed);
				}

				operate_fmt_immediate(i_sll, r, shleng, rr);

				if ((m & (m - 1)) != 0) {
					if (optop(e)) {
						operate_fmt(((m & (m + 1)) == 0) ? i_subq : i_addq, rr, r, rr);
					} else {
						operate_fmt(((m & (m + 1)) == 0) ? i_subqv : i_addqv, rr, r, rr);
					}
				}

				if (!optop(e) && !error_treatment_is_trap(e)) {
					check_exception(e, sp);
				}

				setregalt(aa, rr);
				mka.regmove = move(aa, dest, guardreg(rr, sp), 1);
				return mka;
			}
		} /* else do straightforward mult */

		if (optop(e) /*|| error_treatment_is_trap(e)*/) {
			mka.regmove = comm_op(e, sp, dest, mult_ins);
		} else { /* if (!optop(e) && !error_treatment_is_trap(e)) */
			int r1 = reg_operand(son(e), sp);
			int r2, r0;
			/*int over = new_label();*/
			space nsp;
			ans aa;
			int contlab = new_label();
			int zerolab = new_label();
			int mult_end_lab = new_label();
			nsp = guardreg(r1, sp);
			r2 = reg_operand(bro(son(e)), nsp);
			nsp = guardreg(r2, nsp);
			r0 = getreg(nsp.fixed);
			nsp = guardreg(r0, nsp);
			integer_branch(i_beq, r1, zerolab);
			integer_branch(i_beq, r2, zerolab);
			integer_branch(i_br, 31, contlab);
			set_label(zerolab);
			operate_fmt(i_bis, 31, 31, r0);
			integer_branch(i_br, 31, mult_end_lab);
			set_label(contlab);

			/*	operate_fmt(is64(sh(e))?i_mulq:i_mull,r1,r2,r0);*/
			if (error_treatment_is_trap(e)) {
				operate_fmt(i_mulqv, r1, r2, r0);
			} else {
				operate_fmt(i_mulq, r1, r2, r0);
			}

			switch (name(sh(e))) {
			case u64hd:
			case s64hd: {
				int r3 = getreg(sp.fixed);
				int oklab = new_label();
				integer_branch(i_beq, r1, oklab);
				integer_branch(i_beq, r2, oklab);

				if (error_treatment_is_trap(e)) {
					int new_lab = new_label();
					integer_branch(i_bne, r0, new_lab);
					do_exception(f_overflow);
					set_label(new_lab);
				} else {
					integer_branch(i_beq, r0, trap_label(e));
				}

				set_label(oklab);
				operate_fmt(i_xor, r1, r2, r3);
				/*integer_branch(i_blt,r3,over);*/
				operate_fmt(i_xor, r3, r0, r3);

				if (error_treatment_is_trap(e)) {
					int ok_lab = new_label();
					integer_branch(i_bge, r3, ok_lab);
					do_exception(f_overflow);
					set_label(ok_lab);
				} else {
					integer_branch(i_blt, r3, trap_label(e));
				}

				/*set_label(over);*/
				break;
			}

			case slonghd:
				if (!error_treatment_is_trap(e)) {
					int r3 = getreg(sp.fixed);
					operate_fmt(i_xor, r1, r2, r3);
					operate_fmt(i_xor, r3, r0, r3);
					integer_branch(i_blt, r3, trap_label(e));
					test_signed(r0, -0x80000000L, 0x7fffffff, trap_label(e));
				} else {
#if 1
					int oklab = new_label();
					int r3 = getreg(sp.fixed);
					operate_fmt(i_xor, r1, r2, r3);
					operate_fmt(i_xor, r3, r0, r3);
					integer_branch(i_bge, r3, oklab);
					do_exception(f_overflow);
					set_label(oklab);
#endif
					test_signed_and_trap(r0, -0x80000000L, 0x7fffffff, f_overflow);
				}

				break;

			case ulonghd:
				if (!error_treatment_is_trap(e)) {
					int r3 = getreg(sp.fixed);
					operate_fmt(i_xor, r1, r2, r3);
					integer_branch(i_blt, r3, trap_label(e));
					test_unsigned(r0, 0xffffffff, trap_label(e));
				} else {
					int r3 = getreg(sp.fixed);
					int oklab = new_label();
					operate_fmt(i_xor, r1, r2, r3);
					integer_branch(i_bge, r3, oklab);
					do_exception(f_overflow);
					set_label(oklab);
					test_unsigned_and_trap(r0, 0xffffffff, f_overflow);
				}
				break;

			case uwordhd:
				if (error_treatment_is_trap(e)) {
					test_unsigned_and_trap(r0, 0xffff, f_overflow);
				} else {
					test_unsigned(r0, 0xffff, trap_label(e));
				}
				break;

			case swordhd:
				if (error_treatment_is_trap(e)) {
					test_signed_and_trap(r0, -0x8000L, 0x7fff, f_overflow);
				} else {
					test_signed(r0, -0x8000L, 0x7fff, trap_label(e));
				}
				break;

			case ucharhd:
				if (error_treatment_is_trap(e)) {
					test_unsigned_and_trap(r0, 255, f_overflow);
				} else {
					test_unsigned(r0, 255, trap_label(e));
				}
				break;

			case scharhd:
				if (error_treatment_is_trap(e)) {
					test_signed_and_trap(r0, -128, 127, f_overflow);
				} else {
					test_signed(r0, -128, 127, trap_label(e));
				}
				break;

			default:
				error(ERR_INTERNAL, "illegal shape");
			}

			set_label(mult_end_lab);
			setregalt(aa, r0);
			mka.regmove = move(aa, dest, nsp, 0);
		}

		return mka;
	}

	case div1_tag:
	case div2_tag:
	case offset_div_by_int_tag:
	case offset_div_tag:
	case div0_tag: {
		exp rop = bro(son(e));
		exp lop = son(e);
		bool uns = (name (sh (e)) & 1) == 0; /* ?? */
		space nsp;
		int r0;
		ans aa;
		ash a;
		instruction div_ins;

		if (name(rop) == val_tag) {
			/* unsigned division by constant */
			int   m = no(rop);
			if ((m == 0) && !optop(e)) {
				integer_branch(i_br, 31, trap_label(e));
			}

			if (m > 1 && (m & (m - 1)) == 0) {
				int   r = reg_operand(son(e), sp);
				/* replace div by 2^shleng by arith sh right shleng */
				int   shleng;
				int   rr;

				for (shleng = 0; m != 1; shleng++) {
					m >>= 1;
				}

				rr = regfrmdest(&dest, (guardreg(r, sp)));
				operate_fmt_immediate((uns) ? i_srl : i_sra, r, shleng, rr);
				setregalt(aa, rr);
				mka.regmove = move(aa, dest, guardreg(r, guardreg(rr, sp)), 1);

				return mka;
			} else if (use_umulh_for_div && m > 0) {
				int r = reg_operand(son(e), sp);
				int rr = regfrmdest(&dest, sp);

				if (m != 1) {		/* no point in dividing by 1 ! */
#if DO_NEW_DIVISION
					divide_by_constant(e, lop, rop, rr, nsp);
#else
					divide_by_constant(r, make_INT64(0, m), rr, guardreg(r, sp));
#endif
				} else {
					rr = r;
				}

				setregalt(aa, rr);
				mka.regmove = move(aa, dest, guardreg(rr, sp), 1);

				return mka;
			}
		}

		a = ashof(sh(son(e)));

		if (!optop(e) && !error_treatment_is_trap(e)) {/* test for (-inf)/-1 and /0 */
			check_exception(e, sp);
		}

		nsp.fixed = (sp.fixed) | (1 << 23) | (1 << 24) | (1 << 25) | (1 << 27);
		div_ins = (uns) ? ((a.ashsize == 32) ? i_divlu : i_divqu) :
		          (a.ashsize == 32) ? i_divl : i_divq;

		if (!optop(e) && !error_treatment_is_trap(e)) {
			int rd = reg_operand(rop, sp);
			integer_branch(i_beq, rd, no(son(pt(e))));
		}

		r0 = divide_using_div(e, lop, rop, dest, nsp, div_ins);
		setregalt(aa, r0);
		clear_reg(AT);
		clear_reg(23);
		clear_reg(24);
		clear_reg(25);
		clear_reg(27);

		mka.regmove = move(aa, dest, guardreg(r0, sp), 0);

		return mka;
	}

#if 0
	case div1_tag: {  /* only applies to signed operands */
		exp rop = bro(son(e));
		exp lop = son(e);
		int ne = name(e);
		space nsp;
		int r0, r1, r2;
		int lab, treg;
		ans aa;
		r2 = reg_operand(rop, sp);
		nsp = guardreg(r2, sp);
		r1 = reg_operand(lop, nsp);

		if (!optop(e)) { /* test for (-inf)/-1 and /0 */
			long over = new_label();
			long trap = no(son(pt(e)));
			ans aa;
			set_label(over);
		}

		r0 = regfrmdest(&dest, nsp);
		treg = getreg(guardreg(r0, nsp).fixed);
		lab = new_label();
		operate_fmt(i_xor, treg, r2, treg);
		operate_fmt(i_sra, treg, 31, treg);
		operate_fmt(i_addq, r0, treg, r0);
		set_label(lab);
		setregalt(aa, r0);
		mka.regmove = move(aa, dest, guardreg(r0, sp), 0);

		return mka;
	}
#endif

	case neg_tag:
	case offset_negate_tag:
		if (optop(e) /* || (name(sh(e)) & 1) ==0 */ ) {
			int r1 = getreg(sp.fixed);
			int a1;
			space nsp;
			a1 = reg_operand(son(e), sp);

			if (dest.answhere.discrim == inreg) {
				int d = regalt(dest.answhere);
				operate_fmt(is64(sh(e)) ? i_subq : i_subl, 31, a1, d);
				/*if (optop(e)) tidyshort(d,sh(e));*/
			} else {
				ans a;
				setregalt(a, r1);
				operate_fmt(is64(sh(e)) ? i_subq : i_subl, 31, a1, r1);
				/*if (optop(e)) tidyshort(r1,sh(e));*/
				nsp = guardreg(r1, sp);
				move(a, dest, nsp, 1);
				mka.regmove = r1;
			}

			return mka;
		} else {
			int r1 = reg_operand(son(e), sp);
			space nsp;
			/* int trap = trap_label(e); */
			int r2;
			ans aa;
			nsp = guardreg(r1, sp);
			r2 = getreg(nsp.fixed);
			operate_fmt(i_subq, 31, r1, r2);

			switch (name(sh(e))) {
			case ucharhd:
				if (optop(e)) {
					break;
				}

				if (error_treatment_is_trap(e)) {
					test_unsigned_and_trap(r2, 255, f_overflow);
				} else {
					test_unsigned(r2, 255, trap_label(e));
				}
				break;

			case scharhd:
				if (optop(e)) {
					break;
				}

				if (error_treatment_is_trap(e)) {
					test_signed_and_trap(r2, -128, 127, f_overflow);
				} else {
					test_signed(r2, -128, 127, trap_label(e));
				}
				break;

			case uwordhd:
				if (optop(e)) {
					break;
				}

				if (error_treatment_is_trap(e)) {
					test_unsigned_and_trap(r2, 0xffff, f_overflow);
				} else {
					test_unsigned(r2, 0xffff, trap_label(e));
				}
				break;

			case swordhd:
				if (optop(e)) {
					break;
				}

				if (error_treatment_is_trap(e)) {
					test_signed_and_trap(r2, -0x8000L, 0x7fff, f_overflow);
				} else {
					test_signed(r2, -0x8000L, 0x7fff, trap_label(e));
				}
				break;

			case ulonghd:
				if (optop(e)) {
					break;
				}

				if (error_treatment_is_trap(e)) {
					test_unsigned_and_trap(r2, 0xffffffff, f_overflow);
				} else {
					test_unsigned(r2, 0xffffffff, trap_label(e));
				}
				break;

			case slonghd:
				if (optop(e)) {
					break;
				}

				if (error_treatment_is_trap(e)) {
					test_signed_and_trap(r2, -0x80000000L, 0x7fffffff, f_overflow);
				} else {
					test_signed(r2, -0x80000000L, 0x7fffffff, trap_label(e));
				}
				break;

			case s64hd:
				if (optop(e)) {
					break;
				}

				if (error_treatment_is_trap(e)) {
					test_unsigned_and_trap(r1, 0x7fffffffffffffffL, f_overflow);
				} else {
					test_unsigned(r1, 0x7fffffffffffffffL, trap_label(e));
				}
				break;

			case u64hd:
				if (optop(e)) {
					break;
				}

				if (error_treatment_is_trap(e)) {
					int new_lab = new_label();
					integer_branch(i_ble, r1, new_lab);
					do_exception(f_overflow);
					set_label(new_lab);
				} else {
					integer_branch(i_bgt, r1, trap_label(e));
				}
				break;

			default:
				error(ERR_INTERNAL, "Illegal shape in neg");
			}

			setregalt(aa, r2);
			mka.regmove = move(aa, dest, guardreg(r2, nsp), 0);

			return mka;
		}

	case goto_lv_tag: {
		int r = reg_operand(son(e), sp);

		integer_jump(i_jmp, 31, r, 0);
		clear_all();

		return mka;
	}

	case movecont_tag: {
		exp szarg = bro(bro(son(e)));
		int dr, sr, szr, mr;
		int lout = new_label();
		space nsp;
		int bytemove;
		where w;

		sr = getreg(sp.fixed);
		setregalt(w.answhere, sr);
		w.ashwhere = ashof(sh(son(e)));
		IGNORE make_code(son(e), sp, w , 0);

		nsp = guardreg(sr, sp);
		dr = getreg(nsp.fixed);
		setregalt(w.answhere, dr);
		IGNORE make_code(bro(son(e)), nsp, w, 0);

		nsp = guardreg(dr, nsp);
		w.ashwhere = ashof(sh(bro(bro(son(e)))));
		szr = getreg(nsp.fixed);
		setregalt(w.answhere, szr);
		IGNORE make_code(szarg, nsp, w, 0);

		nsp = guardreg(szr, nsp);
		mr = getreg(nsp.fixed);
		bytemove = al2(sh(szarg)) >> 3;

		if (name(szarg) != val_tag || no(szarg) == 0) {
			integer_branch(i_beq, szr, lout);
		}

		if (isnooverlap(e)) {
			move_dlts(dr, sr, szr, mr, bytemove, sp);
		} else {
			int gtlab = new_label();
			int rtmp = getreg(nsp.fixed);
			operate_fmt(i_cmple, dr, sr, rtmp);
			integer_branch(i_beq, rtmp, gtlab);
			move_dlts(dr, sr, szr, mr, bytemove, sp);
			integer_branch(i_br, 31, lout);
			set_label(gtlab);
			move_dgts(dr, sr, szr, mr, bytemove, sp);
		}

		set_label(lout);

		return mka;
	}

	case set_stack_limit_tag: {
		int reg = reg_operand(son(e), sp);
		baseoff b;
		/*      b = find_tag("__TDFstacklim");*/
		b = find_tag("__alpha_stack_limit");
		load_store(i_stq, reg, b);

		return mka;
	}

	case give_stack_limit_tag: {
		ans aa;
		baseoff b;
		int reg = regfrmdest(&dest, sp);

		/*      b = find_tag("__TDFstacklim");*/
		b = find_tag("__alpha_stack_limit");
		load_store(i_ldq, reg, b);
		setregalt(aa, reg);
		move(aa, dest, guardreg(reg, sp), 1);

		return mka;
	}

	case shl_tag:
	case shr_tag: {
		exp s = son(e);
		exp b = bro(s);
		int a;
		int d;
		int src_reg;
		ans aa;
		space nsp;
		bool sgned = is_signed(sh(e));
		instruction shnat;
		instruction shun;

		a = reg_operand(s, sp);

		/* choose which shift instruction */
		if (name(e) == shr_tag) {
			shnat = (sgned) ? i_sra : i_srl;
			shun = i_sll;
		} else {
			shnat = i_sll;
			shun = (sgned) ? i_sra : i_srl;
		}

		nsp = guardreg(a, sp);
		d = regfrmdest(&dest, nsp);

		/*
		 * When applying right shifts to unsigned data which is less then
		 * the full (64 bit) register length, we must ensure that all the
		 * unused bits in the upper part of the register are set to zero.
		 */
		if (!is64(sh(son(e))) && !is_signed(sh(son(e)))
		    && ins_equal(i_srl, shnat)) {
			src_reg = getreg(nsp.fixed);
			if (name(sh(son(e))) == ulonghd) {
				operate_fmt_immediate(i_zapnot, a, 15, src_reg);
			} else if (name(sh(son(e))) == uwordhd) {
				operate_fmt_immediate(i_zapnot, a, 3, src_reg);
			} else if (name(sh(son(e))) == ucharhd) {
				operate_fmt_immediate(i_zapnot, a, 1, src_reg);
			}
		} else {
			src_reg = a;
		}

		nsp = guardreg(src_reg, nsp);
		if (name(b) == val_tag) {
			/* if it's a constant shift we don't have to choose shift dynamically ... */
			if (no(b) >= 0) {
#if 0
				if (!is64(sh(son(e))) && !is_signed(sh(son(e))) &&
				    ins_equal(i_srl, shnat)) {
					/*
					 * If quantity being shifted right is not 64 bits wide then
					 * the top 32 bits of the register containing it must be set to zero.
					 * This does not apply to arithmetic shifts.
					 */
					operate_fmt_immediate(i_zapnot, a, 15, a);
				}
#endif
				operate_fmt_immediate(shnat, src_reg, no(b), d);
			} else {
				operate_fmt_immediate(shun, src_reg, -no(b), d);
			}
		} else {
			int sr = getreg(nsp.fixed);
			int ar = reg_operand(b, nsp);

			/* ... similarly in these cases */
			if (!is_signed(sh(b)) || (name(b) == and_tag && name(bro(son(b))) == val_tag
			        && no(bro(son(b))) > 0 && no(bro(son(b))) <= 31))
			{
				operate_fmt(shnat, src_reg, ar, d);
			} else {
				/* choose shift dynamically */
				int l = new_label();
				int endl = new_label();

				if (!is64(sh(son(e)))) {
					operate_fmt_immediate(i_sll, src_reg, 32, src_reg);
					operate_fmt_immediate(is_signed(sh(son(e))) ? i_sra : i_srl, src_reg
					                      , 32, src_reg);
					/*operate_fmt_immediate(i_zap,a,240,a);*/	/* ?? */
				}

				integer_branch(i_bge, ar, l);

				operate_fmt(i_subq, 31, ar, sr);
				operate_fmt(shun, src_reg, sr, d);
				integer_branch(i_br, 31, endl);
				set_label(l);
				operate_fmt(shnat, src_reg, ar, d);
				set_label(endl);
			}
		}

		if (is32(sh(e)) && (name(e) == shl_tag)) {
			operate_fmt_immediate(i_addl, d, 0, d);
		}

		setregalt(aa, d);
		move(aa, dest, nsp, 1);
		mka.regmove = d;

		return mka;
	}

#if 0
	case mod_tag: {
		/* only applies to signed operands */
		exp rop = bro(son(e));
		exp lop = son(e);
		int ne = name(e);
		space nsp;
		int r0, r1, r2;
		int lab, treg;
		ans aa;

		error(ERR_INTERNAL, "mod_tag not implemented correctly");
		r1 = reg_operand(lop, sp);
		nsp = guardreg(r1, sp);
		r2 = reg_operand(rop, nsp);

		if (!optop(e)) {		/* test for (-inf)/-1 and /0 */
			long over = new_label();
			long trap = no(son(pt(e)));
			int rt = getreg(guardreg(r2, nsp).fixed);
			ans aa;
			integer_branch(i_beq, r2, trap);
			operate_fmt_immediate(i_cmpeq, r2, -1, rt);
			integer_branch(i_bne, r2, over);
			operate_fmt_big_immediate(i_cmpeq, r1, maxmin(sh(e)).mini, rt);
			integer_branch(i_beq, rt, trap);
			set_label(over);
		}

		r0 = regfrmdest(&dest, nsp);
		error(ERR_INTERNAL, "mod tag not implemented correctly");
		/*	operate_fmt(i_rem, r0, r1, r2);*/
		treg = getreg(guardreg(r0, nsp).fixed);
		lab = new_label();
		/*	condri_ins(i_beq, r0, 0, lab);*/
		operate_fmt(i_xor, treg, r0, r2);
		/*	condri_ins(i_bge, treg, 0, lab);*/
		operate_fmt(i_addq, r0, r0, r2);
		set_label(lab);
		setregalt(aa, r0);
		mka.regmove = move(aa, dest, guardreg(r0, sp), 0);

		return mka;
	}

#endif
	/*
	 * Remainder operations have the same effect on the registers
	 * AT, 23, 24, 25 and 27 as the division operations,
	 * So they must be treated in the same way.
	 */
	case mod_tag:
	case rem0_tag:
	case rem2_tag: {
		exp rop = bro(son(e));
		exp lop = son(e);
		bool uns = !is_signed(sh(e));
		space nsp;
		int r0, r1, r2;
		ans aa;
#if 0
		int size = dest.ashwhere.ashsize;
#endif

		nsp = sp;

		/*
		 * If the second argument is a constant then we can replace the rem*
		 * instruction by either an and instruction, or an umulh and multiplication
		 * followed by a subtraction.
		 */
		if (name(rop) == val_tag) {
			int r = reg_operand(son(e), sp);
			int m = no(rop);	/* value of constant */
			int rres = regfrmdest(&dest, sp);
			int rtmp = getreg(guardreg(rres, sp).fixed);

			if (m > 1 && ((m & (m - 1)) == 0)) {
				/* if the constant is a power of 2 then use an and */
				ans aa;
				operate_fmt_immediate(i_and, r, no(rop) - 1, rres);
				setregalt(aa, rres);
				mka.regmove = move(aa, dest, guardreg(rres, sp), 1);

				return mka;
			} else {
				if (m != 1) {
					if (use_umulh_for_div) {
#if DO_NEW_DIVISION
						divide_by_constant(e, lop, rop, rtmp, nsp);
#else
						divide_by_constant(r, make_INT64(0, m), rtmp, guardreg(r, sp));
#endif
					} else {
						if (!optop(e) && (m == 0)) {
							if (error_treatment_is_trap(e)) {
								do_exception(f_overflow);
							} else {
								integer_branch(i_br, 31, trap_label(e));
							}
						} else {
							operate_fmt_immediate(uns ? i_divqu : i_divq, r, m, rtmp);
						}
					}
					operate_fmt_immediate(i_mulq, rtmp, m, rtmp);
					operate_fmt(i_subq, r, rtmp, rres);
				} else {
					load_store_immediate(i_ldiq, rres, make_INT64(0, 0));
				}
				setregalt(aa, rres);
				mka.regmove = move(aa, dest, guardreg(rres, sp), 1);
				return mka;
			}
		}

		nsp.fixed |= ((1 << 23) | (1 << 24) | (1 << 25) | (1 << 27));
		r1 = reg_operand(lop, nsp);
		clear_reg(23);
		clear_reg(24);
		clear_reg(25);
		clear_reg(27);
		nsp = guardreg(r1, nsp);
		r2 = reg_operand(rop, nsp);

		if (!optop(e)) {		/* test for (-inf)/-1 and /0 */
			check_exception(e, nsp);
		}

		if ((r0 = regfrmdest(&dest, nsp)) == NO_REG) {
			r0  = getreg(nsp.fixed);
		}

		nsp = guardreg(r0, nsp);
		if (!optop(e)) {
			integer_branch(i_beq, r2, trap_label(e));
		}

		operate_fmt((uns) ? ((is64(sh(e))) ? i_remqu : i_remlu) :
		            ((is64(sh(e))) ? i_remq : i_reml), r1, r2, r0);
#if 0
		operate_fmt((uns) ? ((size == 32) ? i_remlu : i_remqu) :
		            ((size == 32) ? i_reml : i_remq),
		            r1, r2, r0);
#endif

		if (name(e) == mod_tag) {
			int res_neg = new_label();
			int exitlab = new_label();
			integer_branch(i_beq, r0, exitlab);
			integer_branch(i_blt, r0, res_neg);
			integer_branch(i_bge, r2, exitlab);
#if 0
			operate_fmt((size == 32) ? i_addl : i_addq, r0, r2, r0);
#endif
			operate_fmt(is64(sh(e)) ? i_addq : i_addl, r0, r2, r0);
			integer_branch(i_br, 31, exitlab);
			set_label(res_neg);
			integer_branch(i_ble, r2, exitlab);
#if 0
			operate_fmt((size == 32) ? i_addl : i_addq, r0, r2, r0);
#endif
			operate_fmt(is64(sh(e)) ? i_addq : i_addl, r0, r2, r0);
			set_label(exitlab);
		}

		setregalt(aa, r0);
		if ((r2 == 23) || (r2 == 24) || (r2 == 25) || (r2 == AT)) {
			clear_dep_reg(rop);
		}

		if ((r1 == 23) || (r1 == 24) || (r1 == 25) || (r1 == AT)) {
			clear_dep_reg(lop);
		}

		clear_reg(23);
		clear_reg(24);
		clear_reg(25);
		clear_reg(27);

		mka.regmove = move(aa, dest, guardreg(r0, nsp), 0);
		return mka;
	}

	case offset_pad_tag: {
		int rdest = regfrmdest(&dest, sp);
		int roff = reg_operand(son(e), sp);
		ans aa;

		if (al2(sh(son(e))) >= al2(sh(e))) {
			if (al2(sh(e)) != 1 || al2(sh(son(e))) == 1) {
				e = son(e);
				goto tailrecurse;
			}
			operate_fmt_immediate(i_sll, roff, 3, rdest);
		} else {
			int al = (al2(sh(son(e))) == 1) ? al2(sh(e)) : (al2(sh(e)) / 8);
			operate_fmt_immediate(i_addq, roff, al - 1, rdest);
			operate_fmt_immediate(i_and, rdest, -al, rdest);
			if (al2(sh(son(e))) == 1) {
				operate_fmt_immediate(i_sra, rdest, 3, rdest);
			}
		}

		setregalt(aa, rdest);
		mka.regmove = move(aa, dest, guardreg(rdest, sp), 0);
		return mka;
	}

#ifdef make_stack_limit_tag
	case make_stack_limit_tag:
#endif
	case minptr_tag:
		mka.regmove = non_comm_op(e, sp, dest, i_subq);
		return mka;

	case abs_tag: {
		int arg = reg_operand(son(e), sp);
		int rtmp = getreg(guardreg(arg, sp).fixed);
		int destreg;
		ans tmp;

		switch (dest.answhere.discrim) {
		case inreg: destreg = regalt(dest.answhere); break;
		default:    destreg = getreg(sp.fixed);      break;
		}

		if (destreg == NO_REG) {
			destreg = getreg(sp.fixed);
		}

		operate_fmt(i_bis, arg, arg, destreg);
		operate_fmt(i_subq, 31, arg, rtmp);
		operate_fmt(i_cmovgt, rtmp, rtmp, destreg);

		if (!optop(e) /*&& !error_treatment_is_trap(e)*/) {
			int rt = getreg(sp.fixed);
			operate_fmt_big_immediate(i_subq, destreg, maxmin(sh(e)).maxi, rt);
			if (error_treatment_is_trap(e)) {
				int newl = new_label();
				integer_branch(i_ble, rt, newl);
				do_exception(f_overflow);
				set_label(newl);
			} else {
				integer_branch(i_bgt, rt, trap_label(e));
			}
		}

		setregalt(tmp, destreg);
		mka.regmove = move(tmp, dest, sp, 1);

		return mka;
	}

	case fplus_tag:
		mka.regmove = fop(e, sp, dest, (name(sh(e)) != shrealhd) ? i_addt : i_adds);

		if ((name(sh(e)) != shrealhd) &&
		    (fregalt(dest.answhere).type == IEEE_single) &&
		    dest.answhere.discrim == infreg) {
		}

		if (!optop(e)) {
			check_exception(e, sp);
		}

		return mka;

	case fminus_tag:
		mka.regmove = fop(e, sp, dest, (name(sh(e)) != shrealhd) ? i_subt : i_subs);

		if (!optop(e)) {
			check_exception(e, sp);
		}

		return mka;

	case fmult_tag: {
		instruction mult_ins;

		mult_ins = (name(sh(e)) != shrealhd) ? i_mult : i_muls;
		mka.regmove = fop(e, sp, dest, mult_ins);

		if (!optop(e) && !error_treatment_is_trap(e)) {
			check_exception(e, sp);
		}

		return mka;
	}

	case fdiv_tag: {
		instruction div_ins;

		div_ins = (name(sh(e)) != shrealhd) ? i_divt : i_divs;

		/*
		if (!optop(e)){
			div_ins = (name(sh(e)) != shrealhd)?i_divtsu:i_divssu;
		} else{
			div_ins = (name(sh(e)) != shrealhd)?i_divt:i_divs;
		}
		*/

		if (!optop(e) && !error_treatment_is_trap(e)) {
			int fr = freg_operand(bro(son(e)), sp);
			float_branch(i_fbeq, fr, no(son(pt(e))));
		}

		mka.regmove = fop(e, sp, dest, div_ins);

		if (!optop(e) && !error_treatment_is_trap(e)) {
			check_exception(e, sp);
		}

		return mka;
	}

	case fneg_tag:
	case fabs_tag: {
		instruction ins;
		freg fr;
		int arg = freg_operand(son(e), sp);

		if (name(e) == fneg_tag) {
			if (optop(e)) {
				ins = (name(sh(e)) != shrealhd) ? i_subt : i_subs;
			} else {
				ins = (name(sh(e)) != shrealhd) ? i_subtsu : i_subssu;
			}
		} else {
			ins = i_cpys;
		}

		switch (dest.answhere.discrim) {
		case infreg:
			fr = fregalt(dest.answhere);
			float_op(ins, 31, arg, fr.fr);
			break;

		default: {
			ans tmp;
			fr.type = (dest.ashwhere.ashsize == 32) ? IEEE_single : IEEE_double;
			fr.fr = getfreg(sp.flt);
			setfregalt(tmp, fr);
			float_op(ins, 31, arg, fr.fr);
			move(tmp, dest, sp, 1);
		}
		}

		if (!optop(e) && (name(e) == fneg_tag) && !error_treatment_is_trap(e)) {
			check_exception(e, sp);
		}

		mka.regmove = ((fr.type == IEEE_double) ? - (fr.fr + 32) : (fr.fr + 32));

		return mka;
	}

	case float_tag: {
		exp in = son(e);
		where w;
		int r;
		int f = dest.answhere.discrim == infreg ? regalt(dest.answhere) : getfreg(sp.flt);
		freg frg;
		ans aa;
		ash ain;
		bool quad;
		ain = ashof(sh(in));
		quad = (ain.ashsize != 32);
		frg.fr = f;
		frg.type = IEEE_single;

		if (ain.ashsize < 32) {
			/* go via fixed point register for bytes and words */
			where tmp;
			ans src;
			r = reg_operand(in, sp);
			setregalt(tmp.answhere, r);
			tmp.ashwhere = ashof(sh(in));
			/*code_here(in,sp,tmp);*/	/* move it into fixed pt reg r */
			setregalt(src, r);
			frg.type = IEEE_double;
			setfregalt(tmp.answhere, frg);
			move(src, tmp, sp, 0);
		} else {
			switch (name(sh(in))) {
			case swordhd:
			case uwordhd:
			case slonghd:
			case ulonghd:
			case s64hd:
			case u64hd: {
				freg load_reg;

				load_reg.type = IEEE_double; /* so we load in an octaword */
				load_reg.fr   = f;

				setfregalt(w.answhere, load_reg);
				w.ashwhere = ashof(sh(in));
				code_here(in, sp, w);
				break;
			}

			default:
				setfregalt(w.answhere, frg);
				w.ashwhere = ashof(sh(in));
				code_here(in, sp, w);
				break;
			}
		}

		if (!quad) {
			float_convert(i_cvtlq, f, f);
		}

		float_convert((name(sh(e)) == shrealhd) ? i_cvtqs : i_cvtqt, f, f);

		if (name(sh(e)) != shrealhd) {
			frg.type = IEEE_double;
		}

		setfregalt(aa, frg);
		move(aa, dest, sp, 1);

		if (name(sh(in)) == u64hd || (name(sh(in)) == ulonghd)) {
			fix_unsigned(frg, sp, name(sh(in)));
		}

		mka.regmove = (frg.type == IEEE_double) ? - (f + 32) : (f + 32);
		return mka;
	}

	case chfl_tag: {
		int   to = name(sh(e));
		int   from = name(sh(son(e)));
		bool dto = (to != shrealhd) ? 1 : 0;
		bool dfrom = (from != shrealhd) ? 1 : 0;

		if (!dto && !dfrom) {	/* no change in representation */
			return make_code(son(e), sp, dest, exitlab);
		} else {
			freg frg;
			ans aa;
			where w;

			if (dest.answhere.discrim == infreg) {
				frg = fregalt(dest.answhere);
			} else {
				frg.fr = getfreg(sp.flt);
			}

			if(dto) {	/* was dfrom */
				frg.type = IEEE_double;
			} else {
				frg.type = IEEE_single;
			}

			setfregalt(aa, frg);
			w.answhere = aa;
			w.ashwhere = ashof(sh(son(e)));
			code_here(son(e), sp, w);

			if (dto) {
				frg.type = IEEE_double;
			} else {
				frg.type = IEEE_single;
			}

			if ((!dto) && dfrom) {
				/* If converting from double to single then we need to use a conversion */
				float_convert(i_cvtts, frg.fr, frg.fr);
			}

			setfregalt(aa, frg);
			move(aa, dest, sp, 1);
			mka.regmove = (frg.type == IEEE_double) ? - (frg.fr + 32) : (frg.fr + 32);

			if (!optop(e) && !dto && !error_treatment_is_trap(e)) {
				check_exception(e, sp);
			}

			return mka;
		}
	}

	case and_tag:
		if (use_andcomp && name(bro(son(e))) == not_tag) {
			bro(son(e)) = son(bro(son(e)));
			mka.regmove = comm_op(e, sp, dest, i_bic);
		} else if (use_andcomp && name(son(e)) == not_tag) {
			exp tmp = copyexp(son(e));
			son(e) = bro(son(e));
			bro(son(e)) = son(tmp);
			/*retcell(tmp)*/;
			mka.regmove = comm_op(e, sp, dest, i_bic);
		} else {
			mka.regmove = comm_op(e, sp, dest, i_and);
		}

		return mka;

	case andcomp_tag:
		mka.regmove = comm_op(e, sp, dest, i_bic);
		return mka;

	case or_tag:
		mka.regmove = comm_op(e, sp, dest, i_bis);
		return mka;

	case xor_tag:
		mka.regmove = comm_op(e, sp, dest, i_xor);
		return mka;

	case not_tag: {
		int arg = reg_operand(son(e), sp);

		switch (dest.answhere.discrim) {
		case inreg: {
			int the_dest = regalt(dest.answhere);
			operate_fmt(i_ornot, 31, arg, the_dest);
			break;
		}

		default: {
			ans a;
			space nsp;
			int reg = getreg(sp.fixed);
			setregalt(a, reg);
			operate_fmt(i_ornot, 31, arg, reg);
			tidyshort(reg, sh(e));
			nsp = guardreg(reg, sp);
			move(a, dest, nsp, is_signed(sh(e)));
		}
		}

		return mka;
	}

	case locptr_tag: {
		int ptr = reg_operand(son(e), sp);
		int ansr = regfrmdest(&dest, sp);

		baseoff b;
		ans aa;
		b.base = ptr;
		b.offset = -arg_stack_space - 3 * (PTR_SZ >> 3);
		load_store(i_ldq, ansr, b);
		setregalt(aa, ansr);
		mka.regmove = move(aa, dest, guardreg(ansr, sp), 0);
		return mka;
	}

	case cont_tag:
	case name_tag:
	case field_tag:
	case reff_tag:
	case addptr_tag:
	case subptr_tag:
	case contvol_tag: {
		where w;
		bool sgned;
		int dr = (dest.answhere.discrim == inreg) ? dest.answhere.val.regans : NO_REG;

		if (name(e) == contvol_tag) {
			clear_all();
			/*setvolatile ();*/
		}

		clear_dep_reg(e);

		w = locate(e, guardreg(dr, sp), sh(e), dr);
		/* 'address of argument */
		/*sgned = ((w.ashwhere.ashsize >= 64)
		|| name (sh (e)) & 1) ? 1 : 0;*/
		sgned = is_signed(sh(e));
		mka.regmove = move(w.answhere, dest, (guard(w, sp)), sgned);
		clear_dep_reg(e);

		if (name(e) == contvol_tag) {
			mka.regmove = NOREG;
			/* setnovolatile ();*/
		}
		return mka;
	}

#if (FBASE != 10)
	case real_tag:
#endif
	case string_tag: {
		instore isa;
		ans aa;
		bool sgned = ((ashof(sh(e)).ashsize >= 32) || name(sh(e)) & 1) ? 1 : 0;

		if (name(e) == real_tag) {
			bool is_denorm = is_denormal(e);
			if (is_fzero(flptnos[no(e)]) || (is_denorm && treat_denorm_specially)) {
				freg frg;
				frg.fr = 31;
				frg.type = (shape_size(sh(e)) == 32) ? IEEE_single : IEEE_double;
				setfregalt(aa, frg);
				mka.regmove = move(aa, dest, sp, sgned);

				if (is_denorm) {
					if (fail_with_denormal_constant) {
						error(ERR_INTERNAL, "Denormalised constant encountered");
						exit(EXIT_FAILURE);
					}

					error(ERR_WARN, "Replaced IEEE denormal with 0.0");
					asm_comment("Replaced IEEE denormal with 0.0");
				}

				return mka;
			}
		}

		isa = evaluated(e, 0);
		set_text_section();
		setinsalt(aa, isa);
		mka.regmove = move(aa, dest, sp, sgned);
		return mka;
	}

#if (FBASE == 10)	/* now defunct */
	case real_tag: {
		instore isa;
		ans aa;
		char *flt_string;	/* a string representing the real literal */
		char *ld_ins;
		freg fr;
		int use_fzero;		/* set if value of real is 0.0 */

		bool sgned = ((ashof(sh(e)).ashsize >= 32) || name(sh(e)) & 1) ? 1 : 0;
		flt_string = floating_value(e);
		use_fzero = streq(flt_string, "0.0");

		switch (dest.answhere.discrim) {
		case infreg:
			fr.fr = regalt(dest.answhere);
			fr.type = (dest.ashwhere.ashsize == 32) ? IEEE_single : IEEE_double;
			break;

		case insomefreg:
			if (use_fzero) {
				break;
			}

			fr.fr = getfreg(sp.flt);
			fr.type = (dest.ashwhere.ashsize == 32) ? IEEE_single : IEEE_double;
			break;

		case notinreg:
			fr.fr = getfreg(sp.flt);
			fr.type = (dest.ashwhere.ashsize == 32) ? IEEE_single : IEEE_double;
			break;

		default:
			error(ERR_INTERNAL, "dubious target for real_tag ");
		}

		ld_ins = (fr.type == IEEE_single) ? i_ldis : i_ldit;
		if (use_fzero) {
			if (dest.answhere.discrim == insomefreg) {
				*dest.answhere.val.somefregans.fr = 31;
				return mka;
			} else {
				float_op(i_cpys, 31, 31, fr.fr);
			}
		} else {
			float_load_store_immediate(ld_ins, fr.fr, flt_string);
		}

		if (dest.answhere.discrim == insomefreg) {
			*dest.answhere.val.somefregans.fr = fr.fr;
		}

		if (dest.answhere.discrim == notinreg) {
			/* put reg contents into memory */
			ans src;
			setfregalt(src, fr);
			mka.regmove = move(src, dest, sp, sgned);
		}

		return mka;
	}
#endif

	case val_tag:
		if (no(e) == 0 && !isbigval(e)) {
			goto null_tag_case;
		} else {
			ash a;
			a = ashof(sh(e));

			switch (a.ashsize)	{
			case 8:
				low_INT64(constval) = no(e) & 255;
				if (is_signed(sh(e))) {
					low_INT64(constval) -= (low_INT64(constval) & 128) << 1;
				}
				break;

			case 32:
				low_INT64(constval) = no(e);
#if 0
				if (is_signed(sh(e))) {
					low_INT64(constval) = no(e);
				} else {
					low_INT64(constval) = uno(e);
				}
#endif
				break;

			case 64: {
				int findex = no(e);
				int ov;

				if (isbigval(e)) {
					flt64 res;
					res = flt_to_f64(findex, is_signed(sh(e)), &ov);
					INT64_assign(constval, flt64_to_INT64(res));
				} else {
					low_INT64(constval) = no(e);
				}
				break;
			}

			default:
				low_INT64(constval) = no(e) & 65535;
				if (is_signed(sh(e))) {
					low_INT64(constval) -= (low_INT64(constval) & 32768) << 1;
				}
				break;
			}

			goto moveconst;
		}

	case prof_tag:
	case top_tag:
		return mka;

	case dump_tag: {
		int fxd = no(e);
		int fld = no(pt(e));
		int old_fixdone = fixdone;
		int old_fltdone = fltdone;
		int old_result_label = result_label;
		exp l;
		result_label = 0;
		dump_sregs(fxd, fld);

		if ((fxd & (1 << RA))) {
			sp.fixed &= ~(1 << RA);
		}

		for (l = son(crt_proc); name(l) == ident_tag && isparam(l);) {
			/* move any pars still in registers which go into dump regs */
			int sr = props(son(l));
			int tr = no(l);

			if ((props(l) & inanyreg) != 0 && (tr != sr) && sr != 0) {
				if ((props(l) & infreg_bits) != 0 &&
				    (fld & (1 << (sr))) != 0) {
					if (name(sh(son(l))) != shrealhd) {
						float_op(i_cpys, tr, tr, sr);
					} else {
						float_op(i_cpys, tr, tr, sr);
					}
					sp.flt &= ~(1 << tr); /* release fpar reg */
					no(l) = sr;
					props(son(l)) = tr;
				} else if (((fxd & (1 << sr)) != 0) && (props(l) & inreg_bits)) {
					operate_fmt(i_bis, tr, tr, sr);
					sp.fixed &= ~(1 << tr); /* release par reg */
					no(l) = sr;
					props(son(l)) = tr;
				}
			}

			l = bro(son(l));
			if (name(l) == dump_tag) {
				l = son(l);
			}
		}

		code_here(son(e), sp, dest);

		for (l = son(crt_proc); name(l) == ident_tag && isparam(l);) {
			/* restore structure of moved pars */
			int sr = props(son(l));
			int tr = no(l);

			if ((props(l) & inanyreg) != 0 && (tr != sr) && sr != 0) {
				if ((props(l) & infreg_bits) != 0 &&
				    (fld & (1 << (tr << 1))) != 0) {
					no(l) = sr;
					props(son(l)) = tr;
				} else if ((fxd & (1 << tr)) != 0) {
					no(l) = sr;
					props(son(l)) = tr;
				}
			}

			l = bro(son(l));
			if (name(l) == dump_tag) {
				l = son(l);
			}
		}

		if (name(sh(e)) != bothd) {
			restore_sregs(fxd, fld);
		}

		fixdone = old_fixdone;
		fltdone = old_fltdone;
		result_label = old_result_label;
		return mka;
	}

	case env_size_tag: {
		exp tg = son(son(e));
		procrec *pr = &procrecs[no(son(tg))];
		constval = (pr->frame_size + pr->callee_size) >> 3;

		goto moveconst;
	}

	case general_proc_tag:
	case proc_tag: {
		/*
		 * set up locals_offset, fixdump, floatdump,
		 * frame_size, dumpstart
		 * dec stack  ; output frame and mask
		 * code here;
		 *
		 * The standard stack layout for a make_proc is as follows:
		 *
		 *     ------------------------------------- Bottom of env
		 *     space for caller params to be passed on stack
		 *     (If containing apply or apply_general)
		 *
		 *     space for dumped s registers
		 *     locals
		 *     space for dumped arguments (first 6)
		 *     -------------------------------------- Top of env
		 *     remaining arguments (in callers frame)
		 *
		 *
		 * for general procs the frame will be set up as follows:
		 *
		 *     ----------------------------  Bottom of callee env
		 *     extra caller parameters (If containing apply or apply_general)
		 *     callee parameters (1,2,,,,,)
		 *     space for dumped s registers
		 *     locals
		 *     caller local reg
		 *     callee local reg
		 *     callee top of stack
		 *     caller frame pointer
		 *     Up to 6 caller parameters
		 *     --------------------------- Top of callee env
		 *     Any remaining caller parameters
		 *
		 */

		procrec * pr = & procrecs[no(e)];
		needs * ndpr = & pr->needsproc;
		long pprops = (ndpr->propsneeds);
		bool leaf = (pprops & anyproccall) == 0;
		space tbd;
		space pars;
		long st;
		exp l;
		int i;
		int has_va;
		setframe_flags(e, leaf);
		has_va = has_c_vararg(e) || ((name(e) == general_proc_tag) &&
		                             (!Has_no_vcallers));
		in_general_proc = (name(e) == general_proc_tag);
		old_postludes = (postlude_chain*)NULL;
		crt_proc = e;
		frame_size = pr->frame_size;
		locals_offset = pr->locals_offset;
		max_args = pr->max_args;
		param_stack_space = (min(max_args, (Has_no_vcallers) ? 6 * PTR_SZ : 12 * PTR_SZ)) >> 3;
		arg_stack_space = min(pr->needsproc.numparams, (has_va) ? 12 * PTR_SZ : 6 * PTR_SZ) >> 3;

#if 0
		if (pr->needsproc.numparams > 11 * PTR_SZ) {
			arg_stack_space = 12 * PTR_SZ;
		} else {
			arg_stack_space = max(pr->needsproc.numparams,
			                      (Has_no_vcallers ? 6 * PTR_SZ : 12 * PTR_SZ));
		}
#endif

		/* this doesn't actually waste much space, and simplifies matters later */
		if (name(e) == general_proc_tag /* || proc_has_gen_call(e)*/) {
			int old_arg_count = arg_stack_space;
			arg_stack_space = ((has_va) ? 12 * PTR_SZ : 6 * PTR_SZ) >> 3;
			if (arg_stack_space > old_arg_count) {
				frame_size += ((arg_stack_space - old_arg_count) << 3);
			}
		}

		/*
		 * param_stack_space contains the maximum number of bytes that will be
		 * required to save the registers used by this proc when passing parameters
		 * to other procedures.
		 *
		 * As the space is actually allocated in the callee frame, this is only
		 * needed for apply_general_proc. arg_stack_space contains the number of
		 * arguments passed to this proc, and for which space must be reserved
		 * within the current frame.
		 */
		UNUSED(param_stack_space);
		for (i = 0; i < min(pr->needsproc.numparams >> 6, NUM_PARAM_REGS); ++i) {
			sp = guardreg(FIRST_INT_ARG + i, sp);
		}

		paramsdumpstart = pr->paramsdumpstart;

		/*
		 * The fixed point registers will be stored in the space
		 * starting from gpdumpstart
		 */

		gpdumpstart = (has_va) ? paramsdumpstart + 384 : paramsdumpstart;
		proc_has_vararg = (has_va) ? 1 : 0;
		fixdump = pr->fixdump;
		floatdump = pr->floatdump;
		dumpstart = pr->dumpstart;
		fldumpstart = pr->fldumpstart;
		callee_size = pr->callee_size;
		stack_top = (locals_offset >> 3) - 8;

		st = (frame_size + callee_size) >> 3;
		fixdone = fltdone = 0;	/* no s-regs have been dumped yet */

		tbd.fixed = fixdump;
		tbd.flt   = floatdump;

		pars.fixed = (leaf) ? 0 : (1 << RA);
		pars.flt = 0;

		for (l = son(e); name(l) == ident_tag && isparam(l) &&
		     name(son(l)) != formal_callee_tag; l = bro(son(l))) {
			if ((props(l) & infreg_bits) != 0) {
				int n = props(son(l));
				if (n != no(l) && n != 0) {
					pars.flt |= (1 << no(l));
				}
			} else if ((props(l) & inreg_bits) != 0) {
				int n = props(son(l));
				if (n != no(l) && n != 0) {
					pars.fixed |= (1 << no(l));
				}
			}
		}

		dump_opt(e, &tbd, &pars);
		set_global_pointer();

		if (name(e) == general_proc_tag) {
			if (Has_vcallees) {
				baseoff b;
				b.base = FP;
				b.offset = (-4 * PTR_SZ >> 3) - arg_stack_space;
				load_store(i_stq, local_reg, b);
				operate_fmt(i_bis, SP, SP, local_reg);

				if (!leaf) {
					b.offset = (-3 * PTR_SZ >> 3) - arg_stack_space;
					load_store(i_stq, local_reg, b);
				}
			} else if (Has_fp && name(e) == general_proc_tag) {
				operate_fmt_immediate(i_addq, SP, arg_stack_space +
				                      (callee_size >> 3), FP);
			}

			if (frame_size != 0 || callee_size != 0) {
				operate_fmt_immediate(i_subq, SP, (frame_size + callee_size) >> 3, SP);
			}
		} else {
			if (st != 0) {
				baseoff a;
				a.base = SP;
				a.offset = -st;
				load_store(i_lda, SP, a);
			}

			setframe(st, 0);
			/* I'm not sure that this is the right order for these - diagnostics ? */

			setprologue(2);
			if (Has_fp) {
				baseoff b;
				b.base = SP;
#if 0
				b.offset = ((callee_size + frame_size) >> 3) -
				           arg_stack_space - (PTR_SZ >> 3);
#endif
				b.offset = ((callee_size + frame_size - PTR_SZ) >> 3) -
				           ((in_general_proc) ? 0 : arg_stack_space);

				b.offset = ((callee_size + frame_size - PTR_SZ) >> 3) -
				           (arg_stack_space);

				load_store(i_stq, FP, b);
				operate_fmt_immediate(i_addq, SP, st, FP);
				/*operate_fmt(i_bis,SP,SP,FP);*/

				if (Has_tos) {
					b.base = FP;
					b.offset = - ((PTR_SZ >> 3) * 2) - (arg_stack_space);
					load_store(i_stq, SP, b);
				}
			}
		}

		if (proc_has_checkstack(e)) {
			baseoff b;
			int rtmp = getreg(sp.fixed);
			/*	b = find_tag("__TDFstacklim");*/
			b = find_tag("__alpha_stack_limit");
			stackerr_lab = new_label();
			load_store(i_ldq, rtmp, b);
			setnoat();
			operate_fmt(i_cmplt, SP, rtmp, AT);
			integer_branch(i_bne, AT, stackerr_lab);
			setat();
		} else {
			stackerr_lab = 0;
		}

		if ((pprops & realresult_bit) != 0) {
			freg frg;

			/* proc has real result */
			/* add an entry for complex result : returned in f0/f1 */

			frg.fr = 0;

			if (pprops & longrealresult_bit) {
				frg.type = IEEE_double;
			} else {
				frg.type = IEEE_single;
			}

			setfregalt(procans, frg);
		} else if ((pprops & has_result_bit) != 0) {
			/* proc has fixed pt result */
			setregalt(procans, RESULT_REG);
		} else {			/* proc has no result */
			setregalt(procans, NO_REG);
		}

		result_label = 0;
		aritherr_lab = 0;

		/* fix up integers passed in registers */
		for (l = son(e); name(l) == ident_tag && isparam(l); l = bro(son(l))) {
			if (props(l) & inreg_bits) {
				int n = props(son(l));
				assert((n >= FIRST_INT_ARG) && (n <= LAST_INT_ARG));
				if (is32(sh(son(l)))) {
					operate_fmt_immediate(i_addl, n, 0, n);
				}
			}
		}

		code_here(son(e), guardreg(RA, sp), nowhere);
		param_stack_space = arg_stack_space = sizecallers = 0;

		/* evaluate body of proc */
		if (stackerr_lab) {
			set_label(stackerr_lab);
			operate_fmt_immediate(i_addq, SP, frame_size >> 3, SP);
			do_exception(f_stack_overflow);
		}

		if (aritherr_lab) {
			set_label(aritherr_lab);
			do_exception(f_overflow);
		}

		return mka;
	}

	case alloca_tag: {
		exp s = son(e);
		int r = regfrmdest(&dest, sp);
		int rd;
		ans aa;
		asm_comment("alloca");

		if (checkalloc(e)) {
			rd = getreg(sp.fixed);
			operate_fmt(i_bis, SP, SP, rd);
		} else {
			rd = SP;
		}

		if (name(s) == val_tag) {
			operate_fmt_immediate(i_subq, rd, (no(s) + 7) & ~7, rd);
		} else {
			int tmp = getreg(sp.fixed);
			int rop = reg_operand(s, sp);
			operate_fmt_immediate(i_addq, rop, 7, tmp);
			operate_fmt_immediate(i_bic, tmp, 7, tmp);
			operate_fmt(i_subq, rd, tmp, rd);
		}

		if (checkalloc(e)) {
			int rt = getreg(sp.fixed);
			baseoff b;
			b = find_tag("__alpha_stack_limit");
			load_store(i_ldq, rt, b);
			setnoat();
			operate_fmt(i_cmple, rt, SP, AT);
			if (stackerr_lab == 0) {
				stackerr_lab = new_label();
			}
			integer_branch(i_beq, AT, stackerr_lab);
			setat();
			operate_fmt(i_bis, rd, rd, SP);
		}

		reset_tos();
		operate_fmt_immediate(i_addq, SP, max(0, (max_args - 6 * (PTR_SZ)) >> 3), r);
		/*operate_fmt(i_bis,SP,SP,r);*/
		setregalt(aa, r);
		mka.regmove = move(aa, dest, sp, 1);

		return mka;
	}

	case last_local_tag: {
		int r = regfrmdest(&dest, sp);
		ans aa;

		/*operate_fmt_immediate(i_addq,SP,max_args>>3,r);*/
		operate_fmt(i_bis, SP, SP, r);
		setregalt(aa, r);
		mka.regmove = move(aa, dest, sp, 1);

		return mka;
	}

	case local_free_tag: {
		exp s = son(e);
		int r = reg_operand(s, sp);
		exp off = bro(s);

		asm_comment("local_free_tag");
		if (name(off) == val_tag) {
			operate_fmt_immediate(i_addq, r, ((no(off) >> 3) + 7) & ~7, r);
		} else {
			int rtmp = reg_operand(off, guardreg(r, sp));
			operate_fmt_immediate(i_addq, rtmp, 7, rtmp);
			operate_fmt_immediate(i_bic, rtmp, 7, rtmp);
			operate_fmt(i_addq, r, rtmp, r);
		}

		if (Has_fp) {
			/*operate_fmt_immediate(i_subq,r,max_args>>3,SP);*/
			operate_fmt(i_bis, r, r, SP);
			reset_tos();
		}

		return mka;
	}

	case local_free_all_tag:
		if (Has_fp) {
			operate_fmt_immediate(i_subq, FP, (frame_size + callee_size) >> 3, SP);
			reset_tos();
		}

		return mka;

	case current_env_tag: {
		int r = regfrmdest(&dest, sp);
		ans aa;

		if (Has_fp) {
			operate_fmt(i_bis, FP, FP, r);
		} else {
			operate_fmt_immediate(i_addq, SP, (frame_size + callee_size) >> 3, r);
		}

		setregalt(aa, r);
		mka.regmove = move(aa, dest, sp, 1);

		return mka;
	}

	case general_env_offset_tag:
	case env_offset_tag:
		low_INT64(constval) = frame_offset(son(e));
		goto moveconst;

	case null_tag:
null_tag_case: {
		ans aa;
		setregalt(aa, 31);
		mka.regmove = move(aa, dest, sp, 1);

		return mka;
	}

	case round_tag: {
		int   r = (dest.answhere.discrim == inreg) ? regalt(dest.answhere)
		          : getreg(sp.fixed);
		int   sfr = freg_operand(son(e), sp);
		int   dfr = getfreg(guardfreg(sfr, sp).flt);
		ash a;
		ans aa;
		int   s;
		instruction ins;
		int truncate = (round_number(e) != f_to_nearest);
		a = ashof(sh(son(e)));
		s = a.ashsize;

		if (r == NO_REG) {
			assert(!optop(e));
			r = getreg(sp.fixed);
		}

		/*
		 * start of round
		 * simply do a conversion: double->long or float->int
		 * need to check FPCR for possible [over/under]flow
		 */
		ins = (truncate) ? i_cvttqc : i_cvttq;
		if (round_number(e) == f_toward_zero) {
			ins = i_cvttqc;
		} else if (round_number(e) == f_toward_smaller) {
			ins = i_cvttqm;
		} else if (round_number(e) == f_toward_larger) {
			set_up_rounding_mode(PLUS_INFINITY);
			ins = i_cvttqd;
		} else {
			ins = i_cvttq;
		}

		float_convert(ins, sfr, dfr); /* convert to integer QW */

		/* now move the result into register r */
		{
			ans source;
			where d;
			freg fr;
			fr.fr = dfr;
			fr.type = (s == 32) ? IEEE_single : IEEE_double;
			setfregalt(source, fr);
			setregalt(d.answhere, r);
			d.ashwhere = a;
			move(source, d, sp, 0);
		}

		/* we may have to cope with overflow a la C */
		if (name(sh(e)) == ucharhd) {
			if (!optop(e) && !error_treatment_is_trap(e)) {
				test_unsigned(r, 255, trap_label(e));
			} else if (error_treatment_is_trap(e)) {
				test_unsigned_and_trap(r, 255, f_overflow);
			}

			operate_fmt_immediate(i_and, r, 255, r);
		} else if (name(sh(e)) == uwordhd) {
			if (!optop(e) && !error_treatment_is_trap(e)) {
				test_unsigned(r, 0xffff, trap_label(e));
			} else if (error_treatment_is_trap(e)) {
				test_unsigned_and_trap(r, 0xffff, f_overflow);
			}

			operate_fmt_immediate(i_and, r, (1 << 16) - 1, r);
		} else if (name(sh(e)) == scharhd) {
			if (!optop(e) && !error_treatment_is_trap(e)) {
				test_signed(r, -128, 127, trap_label(e));
			} else if (error_treatment_is_trap(e)) {
				test_signed_and_trap(r, -128, 127, f_overflow);
			}

			operate_fmt_immediate(i_sll, r, 56, r);
			operate_fmt_immediate(i_sra, r, 56, r);
		} else if (name(sh(e)) == swordhd) {
			if (!optop(e) && !error_treatment_is_trap(e)) {
				test_signed(r, -0x8000L, 0x7fff, trap_label(e));
			} else if (error_treatment_is_trap(e)) {
				test_signed_and_trap(r, -0x8000L, 0x7fff, f_overflow);
			}

			operate_fmt_immediate(i_sll, r, 48, r);
			operate_fmt_immediate(i_sra, r, 48, r);
		} else if (name(sh(e)) == slonghd) {
			if (!optop(e) && !error_treatment_is_trap(e)) {
				test_signed(r, -0x80000000L, 0x7fffffff, trap_label(e));
			} else if (error_treatment_is_trap(e)) {
				test_signed_and_trap(r, -0x80000000L, 0x7fffffff, f_overflow);
			}

			operate_fmt_immediate(i_sll, r, 32, r);
			operate_fmt_immediate(i_sra, r, 32, r);
		} else if (name(sh(e)) == ulonghd) {
			if (!optop(e) && !error_treatment_is_trap(e)) {
				test_unsigned(r, 0xffffffff, trap_label(e));
			} else if (error_treatment_is_trap(e)) {
				test_unsigned(r, 0xffffffff, f_overflow);
			}

			operate_fmt_immediate(i_zap, r, 240, r);
		}

		setregalt(aa, r);
		mka.regmove = move(aa, dest, sp, 1);

		return mka;
	}

	case int_to_bitf_tag: {
		int   r;
		where w;
		ash a;
		ash ai;
		ans aa;
		space nsp;

		a = ashof(sh(e));
		ai = ashof(sh(son(e)));
		r = regfrmdest(&dest, sp);

		setregalt(w.answhere, r);
		w.ashwhere = a;
		code_here(son(e), sp, w);

		if (a.ashsize != ai.ashsize) {
			operate_fmt_immediate(i_and, r, (1 << a.ashsize) - 1, r);
		}

		nsp = guardreg(r, sp);
		setregalt(aa, r);
		move(aa, dest, nsp, 0);

		return mka;
	}

	case bitf_to_int_tag: {
		ash a;
		int   r;
		where w;
		a = ashof(sh(son(e)));
		r = regfrmdest(&dest, sp);

		setregalt(w.answhere, r);
		w.ashwhere = a;
		code_here(son(e), sp, w);

		if (a.ashsize != 64) {
			if ((name((sh(e))) & 1) == 1) {
				operate_fmt_immediate(i_sll, r, 64 - a.ashsize, r);
				operate_fmt_immediate(i_sra, r, 64 - a.ashsize, r);
			} else {
				operate_fmt_immediate(i_and, r, ((1 << a.ashsize) - 1), r);
			}
		}

		move(w.answhere, dest, guardreg(r, sp), 0);
		keepreg(e, r);

		return mka;
	}

#ifdef trap_tag
	case trap_tag:
		if (no(e) == f_overflow) {
			do_exception(f_overflow);
		} else if (no(e) == f_nil_access) {
			do_exception(f_nil_access);
		} else {
			do_exception(f_stack_overflow);
		}

		return mka;
#endif

	case special_tag:
		if (no(e) == 0) {
			no_parameter_instructions(i_trapb);
		}

		return mka;

#if 1
	case condassign_tag: {
		/*
		 * This handles a conditional assignment of the form:
		 * IF ( A .rel. B) THEN X = Y, using conditional moves.
		 *
		 * son(e) is the test_tag and bro(son(e)) is the assignment.
		 *
		 * Note that the test condition is the opposite of the condition
		 * for the conditional move (because the original test is a
		 * jump over the assigment).
		 */
		where assdest;
		instruction cinst;
		exp ctest = son(e);
		exp cass = bro(ctest);
		exp ltest = son(ctest);	/* lhs of test */
		exp rtest = bro(ltest);	/* rhs of test */
		int testid = props(ctest) & 127;
		int targ1, targ2;		/* arguments of test */
		int aarg1, aarg2;		/* arguments of assignment */
		int rev = 0;		/* set if test is reversed */
		ans aa;
		exp rhs = bro(son(cass));
		error(ERR_INTERNAL, "condassign_tag should not be encountered");
		assdest = locate(son(cass), sp, sh(rhs), NO_REG);

		if (((is_floating(name(sh(ltest)))) &&
		     (!is_floating(name(sh(son(cass))))))
		    || ((!is_floating(name(sh(ltest))))
		        && (is_floating((name(sh(son(cass)))))))) {
			return make_code(ctest, sp, dest, exitlab);
		}

		if (is_floating(name(sh(ltest)))) {
			bool fcompare = (name(sh(ltest)) != shrealhd);
			instruction compare_ins;
			space nsp;
			int rdest  = getfreg(sp.flt);
			freg frg;
			targ1 = freg_operand(ltest, sp);
			nsp = guardreg(targ1, sp);
			targ2 = freg_operand(rtest, nsp);

			if (fcompare) {
				rev = fdouble_comparisons(&compare_ins, testid);
				float_op(compare_ins, targ1, targ2, rdest);
			} else {
				float_op(i_subs, targ1, targ2, rdest);
			}

			aarg1 = freg_operand(son(cass), sp);
			nsp = guardreg(aarg1, sp);
			aarg2 = freg_operand(bro(son(cass)), nsp);
			frg.fr = aarg1;
			frg.type = (name(sh(ltest)) == shrealhd) ? IEEE_single : IEEE_double;
			float_op(rev ? i_fcmovne : i_fcmoveq, rdest, aarg2, aarg1);
			setfregalt(aa, frg);
		} else { /* integer */
			bool is_compare = ((!is_signed(sh(ltest))) && ((testid - 5) < 0) &&
			                   (name(sh(ltest)) != ptrhd)) || ((is64(sh(ltest))));
			instruction compare_ins;
			int rres;	/* the result of the test */

			if (is_compare) {
				rev = comparisons(&compare_ins, sh(ltest), testid);
			}

			targ1 = reg_operand(ltest, sp);
			if (name(rtest) == val_tag) {
				space nsp;
				if (no(rtest) || (isbigval(rtest))) {
					nsp = guardreg(targ1, sp);
					rres = getreg(nsp.fixed);

					if (is_compare) {
						if (isbigval(rtest)) {
							operate_fmt_big_immediate(compare_ins, targ1,
							                          exp_to_INT64(rtest), rres);
						} else {
							operate_fmt_immediate(compare_ins, targ1, no(rtest), rres);
						}
					} else {
						if (name(sh(ltest)) == ulonghd) {
							operate_fmt_immediate(i_addl, targ1, 0, targ1);
						}
						if (isbigval(rtest)) {
							operate_fmt_big_immediate(i_subq, targ1, exp_to_INT64(rtest),
							                          rres);
						} else {
							operate_fmt_immediate(i_subq, targ1, no(rtest), rres);
						}
					}
				} else {	/* test against zero */
					rev = 0;
					rres = targ1;
				}
			} else {
				space nsp;
				nsp = guardreg(targ1, sp);
				targ2 = reg_operand(rtest, nsp);

				if (targ2 == 31) {
					rev = 0;
					rres = targ1;
				} else {
					rres = getreg(nsp.fixed);
					if (is_compare) {
						operate_fmt(compare_ins, targ1, targ2, rres);
					} else {
						operate_fmt(i_subq, targ1, targ2, rres);
					}
				}
			}

			aarg1 = regfrmdest(&assdest, sp);
			cinst = condmove((!rev) ? testrev[testid - 1] : testid);

			if (is_compare) {
				cinst = rev ? i_cmovne : i_cmoveq;
			} else {
				cinst = condmove((!rev) ? testrev[testid - 1] : testid);
			}

			if (name(rhs) == val_tag) {
				if (isbigval(rhs)) {
					operate_fmt_big_immediate(cinst, rres, exp_to_INT64(rhs), aarg1);
				} else {
					if (no(rhs) == 0 && (testid == 5)) {
						operate_fmt_immediate(i_cmpeq, rres, 31, aarg1);
					} else {
						operate_fmt_big_immediate(cinst, rres, exp_to_INT64(rhs), aarg1);
					}
				}
			} else {
				int r2 = reg_operand(rhs, sp);
				operate_fmt(cinst, rres, r2, aarg1);
			}
			setregalt(aa, aarg1);
		}

		IGNORE move(aa, assdest, sp, 1);
		IGNORE move(aa, dest, sp, 1);
		clear_dep_reg(son(cass));

		return mka;
	}

#endif
	default:
		error(ERR_SERIOUS, "Tag %d not implemented", name(e));
	}

moveconst:
	{
		int   r = regfrmdest(&dest, sp);
		ans aa;

		if (r == NO_REG) {
			r = getreg(sp.fixed);
		}

		if (r != 31) {
			/* somewhere! */
			if (INT64_eq(constval, zero_int64)) {
				operate_fmt(i_bis, 31, 31, r);
			} else {
				load_store_immediate(is64(sh(e)) ? i_ldiq : i_ldil, r, constval);
			}

			setregalt(aa, r);
			move(aa, dest, guardreg(r, sp), 1);
		}

		mka.regmove = r;
		return mka;
	}
}

