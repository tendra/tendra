/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <utility/bits.h>

#include <local/fbase.h>

#include <main/driver.h>
#include <main/print.h>

#include "assembler.h"
#include "instrs.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "output.h"
#include "codex.h"


/*
    This table gives the mapping between instruction numbers and the
    corresponding names.
*/

char *instr_names_dotty[] = {
#define INSTR_SET_0
#undef  INSTR_SET_1
#include "instr_aux.h"
};

char *instr_names_simple[] = {
#undef  INSTR_SET_0
#define INSTR_SET_1
#include "instr_aux.h"
};


/*
    This table gives the mapping between register numbers and register
    names.
*/

static char *glob_reg_names_percent[] = {
#define REGISTER_SET_0
#undef  REGISTER_SET_1
#include "instr_aux.h"
};

static char *glob_reg_names_simple[] = {
#undef  REGISTER_SET_0
#define REGISTER_SET_1
#include "instr_aux.h"
};



/*
    This table gives the local mapping between register numbers and
    register names.  It is initialized from the table of global register
    names, but may be changed thereafter.
*/

char *reg_names[NO_OF_REGS];


/*
    This routine outputs the register name corresponding to a given
    register number.
*/

#define  out_reg_name(X)	asm_printf("%s", reg_names[(X)])


/*
    This routine prints the sum of all data, external and labels, starting
    with ptr, and moving down the plus-chain.
*/

static void
out_data(mach_op *ptr)
{
	mach_op *p;
	bool neg_next  = false;
	bool need_plus = false;
	for (p = ptr; p; p = p->plus) {
		switch (p->type) {
		case MACH_EXT:
		case MACH_EXTQ:
			if (need_plus || neg_next) {
				asm_printf("%c", neg_next ? '-' : '+');
			}
			asm_printf("%s", p->def.str);
			need_plus = true;
			neg_next  = false;
			break;
		case MACH_LAB:
		case MACH_LABQ:
			if (need_plus || neg_next) {
				asm_printf("%c", neg_next ? '-' : '+');
			}
			asm_printf( "%c%ld", LPREFIX, p->def.num);
			need_plus = true;
			neg_next  = false;
			break;
		case MACH_SPEC:
		case MACH_SPECQ:
			if (!output_immediately && p->def.str == special_str) {
				/* The value of LSx is known, so use it */
				long n = ldisp;
				if (neg_next) {
					n = -n;
				}
				if (p->plus && p->plus->type == MACH_VAL) {
					p->plus->def.num += n;
				} else {
					if (need_plus && n >= 0) {
						asm_printf("+");
					}
					asm_printf( "%ld", n);
					need_plus = true;
				}
			} else {
				if (need_plus || neg_next) {
					asm_printf("%c", neg_next ? '-' : '+');
				}
				asm_printf( "%c%s%ld", LPREFIX, p->def.str, (long) special_no);
				need_plus = true;
			}
			neg_next = false;
			break;
		case MACH_VAL:
		case MACH_VALQ: {
			long n = p->def.num;
			if (neg_next) {
				n = -n;
			}
			if (need_plus && n >= 0) {
				asm_printf("+");
			}
			asm_printf( "%ld", n);
			need_plus = true;
			neg_next  = false;
			break;
		}
		case MACH_HEX:
		case MACH_HEXQ: {
			long n = p->def.num;
			if (neg_next) {
				n = (-n);
			}
			if (need_plus && n >= 0) {
				asm_printf("+");
			}
			asm_printf("0x%lx", (unsigned long) n);
			need_plus = true;
			neg_next  = false;
			break;
		}
		case MACH_NEG:
			neg_next = true;
			break;
		default:
			return;
		}
	}
}


/*
    This routine outputs a scaled register operand.
*/

static void
out_scaled(mach_op *ptr)
{
	long sf = ptr->def.num;
	asm_scale_before();
	out_reg_name(ptr->of->def.num);
	if (sf == 1) {
		asm_scale_1();
	} else {
		asm_scale();
		asm_printf( "%ld", sf);
	}
}


/*
    This routine outputs a floating point number.
*/

static void
out_float(flt *f)
{
	UNUSED(f);

	error(ERR_SERIOUS, "Illegal floating point constant");
}


/*
    MACROS FOR CONSTRUCTS DEPENDING ON asm_data_first

    TODO: these really oughn't be macros
*/

#define  out_data_1(X)		if (asm_data_first && X) out_data(X)
#define  out_data_1a(X)		if (asm_data_first && X) { out_data(X); asm_printf(","); }
#define  out_data_1b(X)		if (asm_data_first && X) { asm_printf(","); out_data(X); }
#define  out_sf_data(X, Y)          \
    if (asm_data_first) {           \
        if (Y) out_scaled(Y);       \
    } else {                        \
        if (X) {                    \
            asm_printf("(");      \
            out_data(X);            \
            if (Y) {                \
                asm_printf(",");  \
                out_scaled(Y);      \
            }                       \
            asm_printf(")");      \
        } else {                    \
            if (Y) {                \
                asm_printf("(");  \
                out_scaled(Y);      \
                asm_printf(")");  \
            }                       \
        }                           \
    }


/*
   OUTPUT A MACHINE OPERAND

   This routine prints a machine operand.
 */

static void
out_mach_op(mach_op *ptr)
{
	mach_op *p = ptr;
	switch (p->type) {
	case MACH_BF: {
		/* Bitfield operands */
		long bf_off = p->def.num;
		long bf_bits = p->plus->def.num;
		out_mach_op(p->of);
		asm_bf_before();
		asm_nprefix();
		asm_printf( "%ld", bf_off);
		asm_bf_middle();
		asm_nprefix();
		asm_printf( "%ld", bf_bits);
		asm_bf_after();
		return;
	}
	case MACH_CONT:
		p = p->of;
		switch (p->type) {
		case MACH_CONT: {
			/* Memory indirect (post- or pre-indexed) */
			mach_op *p1 = p->plus;
			mach_op *p2 = NULL;
			mach_op *q = p->of;
			mach_op *q1 = q->plus;
			mach_op *q2 = NULL;
			if (p1 && p1->type == MACH_SCALE) {
				p2 = p1;
				p1 = p2->plus;
			}
			if (q1 && q1->type == MACH_SCALE) {
				if (p2) {
					error(ERR_SERIOUS, "Illegal addressing mode");
					asm_error();
					return;
				}
				q2 = q1;
				q1 = q2->plus;
			}
			asm_mem_before();
			out_data_1a(q1);
			out_reg_name(q->def.num);
			asm_mem_second();
			out_sf_data(q1, q2);
			asm_mem_third();
			out_sf_data(p1, p2);
			if (p2) {
				out_scaled(p2);
			}
			out_data_1b(p1);
			asm_mem_after();
			return;
		}
		case MACH_REG: {
			/* Register indirect (with displacement or index) */
			mach_op *p1 = p->plus;
			mach_op *p2 = NULL;
			if (p1) {
				if (p1->type == MACH_SCALE) {
					p2 = p1;
					p1 = p2->plus;
				}
				out_data_1(p1);
			}
			asm_ind_before();
			out_reg_name(p->def.num);
			asm_ind_middle();
			out_sf_data(p1, p2);
			asm_ind_after();
			return;
		}
		case MACH_EXTQ: {
			/* External indirect (with displacement or index) */
			mach_op *p1 = p->plus;
			mach_op *p2 = NULL;
			if (p1) {
				if (p1->type == MACH_SCALE) {
					p2 = p1;
					p1 = p2->plus;
				}
				out_data_1(p1);
			}
			asm_ind_before();
			asm_printf("%s", p->def.str);
			asm_ind_middle();
			out_sf_data(p1, p2);
			asm_ind_after();
			return;
		}
		case MACH_EXT:
		case MACH_LAB:
		case MACH_SPEC:
		case MACH_VAL:
		case MACH_HEX:
		case MACH_NEG:
			/* Contents of immediate data, externals, labels */
			out_data(p);
			return;
		}
		error(ERR_SERIOUS, "Illegal addressing mode");
		asm_error();
		return;
	case MACH_DEC:
		/* Register indirect with predecrement */
		asm_predec_before();
		out_reg_name(p->def.num);
		asm_predec_after();
		return;
	case MACH_INC:
		/* Register indirect with postincrement */
		asm_postinc_before();
		out_reg_name(p->def.num);
		asm_postinc_after();
		return;
	case MACH_REG:
		/* Register direct */
		out_reg_name(p->def.num);
		return;
	case MACH_RPAIR:
		/* Register pair */
		out_reg_name(p->def.num);
		asm_rpair_sep();
		out_reg_name(p->plus->def.num);
		return;
	case MACH_EXT:
	case MACH_LAB:
	case MACH_SPEC:
	case MACH_VAL:
	case MACH_HEX:
		/* Immediate data, externals, labels */
		asm_nprefix();
		out_data(p);
		return;
	case MACH_EXTQ:
	case MACH_LABQ:
	case MACH_SPECQ:
		/* Contents of externals, labels */
		out_data(p);
		return;
	case MACH_FLOATQ:
		/* Floating-point data */
		out_float(p->def.fp);
		return;
	case MACH_VALQ:
		/* Integer data */
		asm_printf( "%ld", p->def.num);
		return;
	case MACH_HEXQ:
		/* Integer data */
		asm_printf("0x%lx", (unsigned long) p->def.num);
		return;
	}
	error(ERR_SERIOUS, "Illegal addressing mode");
	asm_error();
}


/*
    This routine outputs all the machine instructions, together with their
    operands (if any).
*/

void
output_all(void)
{
	int n;
	mach_ins *p;
	for (p = all_mach_ins; p; p = p->next) {
		n = p->ins_no;
#ifndef NDEBUG
#if 0
		/*
		 * This is for debugging convenience; the idea is to watch 'found'
		 * for the instruction number just before the one you're after,
		 * and then step forwards.
		 */
		if (n != m_comment) {
			asm_printf( "#inst%ld\n", p->id);
		}
		if (p->id == 4921) {
			int found = 1;
		}
#endif
#endif
		switch (n) {
		case m_comment:
#ifndef NDEBUG
			asm_printf( "#%s\n", p->op1->def.str);
#endif
			break;

#ifdef m_ignore_ins
		case m_ignore_ins:
			/* Ignore */
			break;
#endif /* m_ignore_ins */

		case m_label_ins:
			/* Labels */
			asm_label( "%c%ld", LPREFIX, p->op1->def.num);
			break;

		case m_extern_ins:
			/* Externals */
			out_data(p->op1);
			asm_printf( ":\n");
			break;

		case m_as_byte:
		case m_as_short:
		case m_as_long:
		case m_stabs:
		case m_stabd:
		case m_stabn:
		case m_dd_special: {
			/* Data */
			mach_op *q;
			bool started = 0;
			int c = 0;
			for (q = p->op1; q; q = q->of) {
				if (c == 0) {
					if (started) {
						asm_printf("\n");
					}
					asm_printf("%s", instr_names[n]);
				} else {
					asm_printf(",");
				}
				out_data(q);
				started = 1;
				if (++c == 8) {
					c = 0;
				}
			}
			asm_printf("\n");
			break;
		}
		case m_as_assign:
			if (asm_uses_equals) {
			    out_mach_op(p->op1);
			    asm_printf("=");
			    out_mach_op(p->op2);
			    asm_printf("\n");
			    break;
			}
			FALL_THROUGH;
		default:
			if (is_jump(n)) {
				/* Jumps */
				if (!asm_does_jump_lens && is_unsized(n)) {
					n += long_jump;
				}
				asm_printf( "%s%c%ld", instr_names[n], LPREFIX, p->op1->def.num);
				if (n == m_bra || n == m_brab ||
				    n == m_braw || n == m_bral) {
					/* Align after unconditional jumps */
					asm_printf("\n");
					if (!no_align_directives) {
						asm_printf("%s", instr_names[m_as_align4]);
					}
				}
			} else {
				/* Simple instructions */
				asm_printf("%s", instr_names[n]);
				if (p->op1) {
					out_mach_op(p->op1);
				}
				if (p->op2) {
					asm_printf(",");
#ifndef NDEBUG
					asm_printf(" ");
#endif
					out_mach_op(p->op2);
				}
			}
			asm_printf("\n");
			break;
		}
	}
}


/*
    Apply a couple of patches for odd instruction quirks.
*/

void
init_instructions(void)
{
	if (asm_no_btst_suffix) {
		instr_names[m_btstb] = instr_names[m_btst];
		instr_names[m_btstl] = instr_names[m_btst];
	}
}


/*
    This routine copies the table of global register names into the
    table of global register names.
*/

void
init_output(void)
{
	memcpy(reg_names, glob_reg_names, asm_percent_regs
		? sizeof glob_reg_names_percent
		: sizeof glob_reg_names_simple);
#ifdef SYSV_ABI
	{
		char *r = reg_names[REG_A0];
		reg_names[REG_A0] = reg_names[REG_A1];
		reg_names[REG_A1] = r;
	}
#endif /* SYS_ABI */
	all_mach_ins = NULL;
	current_ins = NULL;
}

