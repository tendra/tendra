/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/bool.h>
#include <shared/error.h>

#include <utility/bits.h>

#include <local/tag.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/externs.h>

#include <construct/exp.h>
#include <construct/install_fns.h>

#include <main/flags.h>
#include <main/driver.h>
#include <main/print.h>

#include "instrs.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "codex.h"
#include "eval.h"
#include "where.h"
#include "make_code.h"
#include "instr.h"
#include "translate.h"
#include "output.h"


/*
    The expression e, representing an external, is looked up in the main_globals
    table, and its external name is returned.
*/

static char *
extname(exp e)
{
	dec *d = brog(e);
#if 0
	if (d->external_register) {
		error(ERR_SERIOUS, "External registers not yet implemented");
		return "????";
	}
#endif
	return d->name;
}


/*
    These macros are used as convenient shorthands in operand.
*/

#define make_ind(X, Y)		make_indirect(reg(X), (Y) / 8)
#define make_ext(X, Y)		make_extern(extname(X), (Y) / 8)
#define make_ext_ind(X, Y)	make_extern_ind(extname(X), (Y) / 8)


/*
    The operand corresponding to w1 indexed by w2 times sf is translated into
    a mach_op.
*/

static mach_op *
index_opnd(where w1, where w2, int sf)
{
	mach_op *op1, *op2;
	if (w2.wh_exp->tag != name_tag) {
		error(ERR_SERIOUS, "Illegal index operand");
		return NULL;
	}
	op1 = operand(32L, w1);
	op2 = operand(32L, w2);
	return make_index_op(op1, op2, sf);
}


/*
    In debugging mode a little extra information is always useful.
*/

#ifndef NDEBUG
static char *illegal_operand = "Illegal operand, case %d";
#else
static char *illegal_operand = "Illegal operand";
#endif


/*
    The value wh of size sz is converted into a mach_op.
*/

mach_op *
operand(long sz, where wh)
{
	long d;
	mach_op *op;
	exp w = wh.wh_exp;
	long off = wh.wh_off;

	switch (w->tag) {
	case val_tag: {
		long k = no(w) + off;
		if (is_offset(w)) {
			k /= 8;
		}
		if (sz == 8) {
			k &= 0xff;
		}
		if (sz == 16) {
			k &= 0xffff;
		}
		return make_value(k);
	}
	case ident_tag:
	case labst_tag:
		switch (ptno(w)) {
		case var_pl:
			d = no(w) - off;
			return make_rel_ap(-(d / 8));
#ifndef tdf3
		case par2_pl:
			d = no(w) + off;
			return make_rel_ap2(d / 8);
		case par3_pl:
			d = no(w) + off;
			return make_rel_sp(d / 8);
#endif
		case par_pl:
			d = no(w) + off + 32;
			return make_rel_ap(d / 8);
		case reg_pl:
			return make_register(reg(no(w)));
		default:
			error(ERR_SERIOUS, illegal_operand, 0);
			return NULL;
		}
	case name_tag: {
		exp id = son(w);
		long d1 = no(w) + off;
		long d2 = no(id);

		if (isglob(id)) {
			if (sh(w)->tag == prokhd) {
#if 1
				if ((son(id) == NULL ||
				     son(id)->tag == proc_tag ||
				     son(id)->tag == general_proc_tag))
#endif
					return make_ext(id, d1);

			}
			return make_ext_ind(id, d1);
		}

		switch (ptno(id)) {
#ifndef tdf3
		case par2_pl:
			return make_rel_ap2((d1 + d2 ) / 8);
		case par3_pl:
			return make_rel_sp((d1 + d2 ) / 8);
#endif
		case par_pl:
			return make_rel_ap((d1 + d2 + 32) / 8);
		case var_pl:
			return make_rel_ap((d1 - d2) / 8);
		case reg_pl:
			return make_register(reg(d2));
		default:
			error(ERR_SERIOUS, illegal_operand, 1);
			return NULL;
		}
	}
	case cont_tag:
	case ass_tag: {
		exp r = son(w);
		switch (r->tag) {
		case name_tag: {
			exp id = son(r);
			if (!isvar(id)) {
				if (isglob(id)) {
					int ra;
					if (sh(w)->tag == prokhd) {
						if (off) {
							error(ERR_SERIOUS, illegal_operand, 2);
						}
						return make_ext_ind(id, no(r));
					}
					op = make_ext_ind(id, off);
					ra = tmp_reg(m_movl, op);
					return make_indirect(ra, no(r) / 8);
				}
				switch (ptno(id)) {
				case par_pl:
					d = no(id) + no(r) + 32;
					op = make_ind_rel_ap(d / 8, off / 8);
					return op;
#ifndef tdf3
				case par2_pl:
					d = no(id) + no(r);
					op = make_ind_rel_ap2(d / 8, off / 8);
					return op;
				case par3_pl:
					d = no(id) + no(r);
					op = make_ind_rel_ap3(d / 8, off / 8);
					return op;
#endif
				case var_pl:
					d = - (no(id)) + no(r);
					op = make_ind_rel_ap(d / 8, off / 8);
					return op;
				case reg_pl:
					return make_ind(no(id), off);
				default:
					error(ERR_SERIOUS, illegal_operand, 4);
					return NULL;
				}
			} else {
				where new_w;
				new_w.wh_exp = r;
				new_w.wh_off = off;
				return operand(sz, new_w);
			}
		}
		case cont_tag: {
			exp rr = son(r);
			int roff = 0;
			if (rr->tag == reff_tag) {
				rr = son(rr);
				roff = no(rr);
			}
			switch (rr->tag) {
			case name_tag: {
				exp id = son(rr);
#if 0
				if (!isvar(id)) {
					error(ERR_SERIOUS, illegal_operand, 5);
					return NULL;
				}
#endif
				if (isglob(id)) {
					int ra;
					op = make_ext_ind(id, no(rr));
					ra = tmp_reg(m_movl, op);
					return make_indirect(ra, off / 8);
				}
				switch (ptno(id)) {
				case par_pl:
					d = no(id) + no(rr) + 32 + roff;
					op = make_ind_rel_ap(d / 8, off / 8);
					return op;
#ifndef tdf3
				case par2_pl:
					d = no(id) + no(rr);
					op = make_ind_rel_ap2(d / 8, off / 8);
					return op;
				case par3_pl:
					d = no(id) + no(rr);
					op = make_ind_rel_ap3(d / 8, off / 8);
					return op;
#endif
				case var_pl:
					d = - (no(id)) + no(rr) + roff;
					op = make_ind_rel_ap(d / 8, off / 8);
					return op;
				case reg_pl:
					return make_ind(no(id), off);
				default:
					error(ERR_SERIOUS, illegal_operand, 6);
					return NULL;
				}
			}
			default:
				error(ERR_SERIOUS, illegal_operand, 7);
				return NULL;
			}
		}
		case reff_tag: {
			exp rr = son(r);
			switch (rr->tag) {
			case name_tag: {
				exp id = son(rr);
				if (isglob(id)) {
					int ra;
					op = make_ext_ind(id, 0);
					ra = tmp_reg(m_movl, op);
					return make_indirect(ra, no(r) / 8);
				}
				switch (ptno(id)) {
				case reg_pl:
					d = no(r) + off;
					return make_ind(no(id), d);
				case par2_pl:
				case par3_pl:
				case par_pl: {
					int ra;
					where new_w;
					new_w.wh_exp = id;
					new_w.wh_off = 0;
					op = operand(32L, new_w);
					ra = tmp_reg(m_movl, op);
					d = no(r) + off;
					return make_indirect(ra, d / 8);
				}
				case var_pl: {
					int ra;
					where new_w;
					new_w.wh_exp = id;
					new_w.wh_off = 0;
					op = operand(32L, new_w);
					ra = tmp_reg(m_movl, op);
					d = no(r) + off;
					return make_indirect(ra, d / 8);
				}
				default:
					error(ERR_SERIOUS, illegal_operand, 8);
					return NULL;
				}
			}
			case cont_tag: {
				exp rrr = son(rr);
				exp id = son(rrr);
				if (ptno(id) == reg_pl) {
					d = no(r) + off;
					return make_ind(no(id), d);
				}
				if (ptno(id) == var_pl) {
					int ra;
					where new_w;
					new_w.wh_exp = id;
					new_w.wh_off = 0;
					op = operand(32L, new_w);
					ra = tmp_reg(m_movl, op);
					d = no(r) + off;
					return make_indirect(ra, d / 8);
				}
				error(ERR_SERIOUS, illegal_operand, 9);
				return NULL;
			}
			case addptr_tag: {
				where new_w;
				new_w.wh_exp = rr;
				new_w.wh_off = no(r) + off;
				return operand(sz, new_w);
			}
			default:
				error(ERR_SERIOUS, illegal_operand, 10);
				return NULL;
			}
		}
		case addptr_tag: {
			where wb, wc;
			exp rr = son(r);
			exp eb = bro(rr);
			exp ec = simple_exp(cont_tag);
			son(ec) = rr;
			wb.wh_exp = eb;
			wb.wh_off = 0;
			wc.wh_exp = ec;
			wc.wh_off = off;

			switch (eb->tag) {
			case name_tag:
			case cont_tag:
				return index_opnd(wc, wb, 1);
			case offset_mult_tag: {
				long k = no(bro(son(eb))) / 8;
				if (sz == 8 * k) {
					wb.wh_exp = son(eb);
					wb.wh_off = 0;
					return index_opnd(wc, wb, (int) k);
				}
				error(ERR_SERIOUS, illegal_operand, 11);
				return NULL;
			}
			default:
				error(ERR_SERIOUS, illegal_operand, 12);
				return NULL;
			}
		}
		default:
			error(ERR_SERIOUS, illegal_operand, 14);
			return NULL;
		}
	}
	case dummy_tag: {
		exp r = son(w);

		switch (r->tag) {
		case ident_tag:
			/* This is used by m_lea */
			switch (ptno(r)) {
			case reg_pl:
				return make_ind(no(r), no(w));
			case var_pl: {
				int ra;
				where new_w;
				new_w.wh_exp = r;
				new_w.wh_off = 0;
				op = operand(32L, new_w);
				ra = tmp_reg(m_movl, op);
				d = no(w);
				return make_indirect(ra, d / 8);
			}
			default:
				error(ERR_SERIOUS, illegal_operand, 15);
				return NULL;
			}
		case name_tag: {
			exp id = son(r);
			if (isglob(id)) {
				return make_ext_ind(id, no(w));
			}
			switch (ptno(id)) {
			case reg_pl:
				return make_ind(no(id), no(w));
			case var_pl: {
				int ra;
				where new_w;
				new_w.wh_exp = id;
				new_w.wh_off = 0;
				op = operand(32L, new_w);
				ra = tmp_reg(m_movl, op);
				d = no(w);
				return make_indirect(ra, d / 8);
			}
			default:
				error(ERR_SERIOUS, illegal_operand, 16);
				return NULL;
			}
		}
		case cont_tag:
		case ass_tag: {
			exp rr = son(r);
			exp id = son(rr);
			if (isglob(id)) {
				return make_ext_ind(id, no(w));
			}
			switch (ptno(id)) {
			case reg_pl:
				return make_ind(no(id), no(w));
			case var_pl: {
				int ra;
				where new_w;
				new_w.wh_exp = id;
				new_w.wh_off = 0;
				op = operand(32L, new_w);
				ra = tmp_reg(m_movl, op);
				d = no(w);
				return make_indirect(ra, d / 8);
			}
			default:
				error(ERR_SERIOUS, illegal_operand, 17);
				return NULL;
			}
		}
		case addptr_tag: {
			where new_w;
			new_w.wh_exp = r;
			new_w.wh_off = no(w) + off;
			return operand(sz, new_w);
		}
		default:
			error(ERR_SERIOUS, illegal_operand, 18);
			return NULL;
		}
	}
	case reff_tag: {
		exp r = son(w);

		switch (r->tag) {
		case name_tag: {
			exp id = son(r);
			if (isglob(id)) {
				return make_ext(id, no(w));
			}
			switch (ptno(id)) {
			case reg_pl:
				if (no(w)) {
					int ra = reg(no(id));
					if (is_dreg(ra)) {
						op = make_register(ra);
						ra = tmp_reg(m_movl, op);
						add_to_reg(ra, no(w) / 8);
					} else {
						op = make_indirect(ra,
								   no(w) / 8);
						ra = tmp_reg(m_lea, op);
					}
					return make_register(ra);
				}
				d = no(id);
				return make_register(reg(d));
			default:
				error(ERR_SERIOUS, illegal_operand, 19);
				return NULL;
			}
		}
		case cont_tag:
		case ass_tag: {
			exp rr = son(r);
			exp id = son(rr);
			if (isglob(id)) {
				if (no(w)) {
					int ra;
					op = make_ext_ind(id, 0);
					ra = tmp_reg(m_movl, op);
					add_to_reg(ra, no(w) / 8);
					return make_register(ra);
				}
				return make_ext_ind(id, 0);
			}
			switch (ptno(id)) {
			case reg_pl:
				debug_warning("reff - untested case");
				return make_ind(no(id), no(w));
			case var_pl: {
				int ra;
				where new_w;
				new_w.wh_exp = id;
				new_w.wh_off = 0;
				op = operand(32L, new_w);
				ra = tmp_reg(m_movl, op);
				if (no(w)) {
					add_to_reg(ra, no(w) / 8);
				}
				return make_register(ra);
			}
			default:
				error(ERR_SERIOUS, illegal_operand, 20);
				return NULL;
			}
		}
		case addptr_tag: {
			where new_w;
			debug_warning("reff - untested case");
			new_w.wh_exp = r;
			new_w.wh_off = 0;
			return operand(sz, new_w);
		}
		default:
			error(ERR_SERIOUS, illegal_operand, 21);
			return NULL;
		}
	}
	case addptr_tag: {
		where wb, wc;
		exp r = son(w);
		exp eb = bro(r);
		exp ec = simple_exp(cont_tag);
		son(ec) = r;
		wb.wh_exp = eb;
		wb.wh_off = 0;
		wc.wh_exp = ec;
		wc.wh_off = off;

		switch (eb->tag) {
		case name_tag:
		case cont_tag:
			return index_opnd(wc, wb, 1);
		case offset_mult_tag: {
			long k = no(bro(son(eb))) / 8;
			wb.wh_exp = son(eb);
			wb.wh_off = 0;
			return index_opnd(wc, wb, (int) k);
		}
		default:
			error(ERR_SERIOUS, illegal_operand, 22);
			return NULL;
		}
	}
	case general_proc_tag:
	case proc_tag: {
		long lb = next_lab();
		make_constant(lb, w);
		return make_lab(lb, 0);
	}
	case real_tag:
	case string_tag: {
		long lb;
		if (off == 0) {
			lb = next_lab();
			make_constant(lb, w);
			return make_lab_ind(lb, 0);
		}
		debug_warning("Offset from label");
		return make_lab_ind(no(const_list) + 1, off / 8);
	}
	case res_tag:
		return make_lab_ind(no(w), 0);
	case null_tag:
		return make_value(0);
#ifndef tdf3
	case apply_general_tag:
	case tail_call_tag:
#endif
	case apply_tag:
		return make_dec_sp();
	case field_tag: {
		where new_w;
		new_w.wh_exp = son(w);
		new_w.wh_off = no(w) + off;
		return operand(sz, new_w);
	}
	case current_env_tag:
		return make_register(REG_AP);
#ifndef tdf3
	case env_size_tag: {
		dec *dp = brog(son(son(w)));
		return make_lab((long)dp, 0);
	}
	case env_offset_tag: {
		exp ident_exp = son(w);
		return make_lab((long)ident_exp, 0);
	}
#else
	case env_offset_tag: {
		exp id = son(w);
		switch (ptno(id)) {
		case var_pl:
			d = no(id) - off;
			return make_value(-(d / 8));
		case par2_pl:
			d = no(id) + off;
			return make_value(d / 8);
		case par3_pl:
		case par_pl:
			d = no(id) + off + 32;
			if (used_stack) {
				d += 32;
			}
			return make_value(d / 8);
		}
		error(ERR_SERIOUS, illegal_operand, 23);
		return NULL;
	}
#endif
	case make_lv_tag:
		return make_lab(ptno(pt(son(pt(w)))), 0);
	case local_free_all_tag:
		return make_special_data("PA");
	case internal_tag:
		return make_lab_ind(no(w), off / 8);
	default:
		error(ERR_SERIOUS, illegal_operand, 24);
		return NULL;
	}
}


/*
    This routine returns the bitmask of all the registers changed in the
    operand op.  c is true to indicate that the operand is being assigned
    to.  If c is false, the only way op can change a register is if it is
    a pre-decrement or post-increment.
*/

bitpattern
regs_changed(mach_op *op, int c)
{
	int t = op->type;
	if (t == MACH_DEC || t == MACH_INC) {
		return regmsk(op->def.num);
	}
	if (!c) {
		return 0;
	}
	if (t == MACH_REG) {
		return regmsk(op->def.num);
	}
	if (t == MACH_RPAIR) {
		return regmsk(op->def.num) | regmsk(op->plus->def.num);
	}
	return 0;
}


/*
    The instruction instr is created.
*/

void
ins0(int instr)
{
	make_instr(instr, NULL, NULL, 0);
}


/*
    The instruction instr with a single operand, a, of size asz is created.
    a_changed is true to indicate that a is assigned to.
*/

void
ins1(int instr, long asz, where a, int a_changed)
{
	mach_op *op = operand(asz, a);
	bitpattern ch = regs_changed(op, a_changed);
	make_instr(instr, op, NULL, ch);
}


/*
    The instruction instr with a two operands, a of size asz and b of size bsz,
    is created.  b_changed is true to indicate that b is assigned to.
*/

void
ins2(int instr, long asz, long bsz, where a, where b, int b_changed)
{
	bitpattern ch;
	mach_op *opa = operand(asz, a);
	mach_op *opb = operand(bsz, b);
	ch = (regs_changed(opa, 0) | regs_changed(opb, b_changed));
	make_instr(instr, opa, opb, ch);
}


/*
    The instruction instr with a two operands, a constant c and a of size asz,
    is created.  a_changed is true to indicate that a is assigned to.
*/

void
ins2n(int instr, long c, long asz, where a, int a_changed)
{
	mach_op *opc = make_value(c);
	mach_op *opa = operand(asz, a);
	bitpattern ch = regs_changed(opa, a_changed);
	make_instr(instr, opc, opa, ch);
}


/*
    The instruction instr with a two operands, a constant c and a of size asz,
    is created.  a_changed is true to indicate that a is assigned to.  This
    routine only differs from ins2n in that the constant will be output in
    hex rather than decimal.
*/

void
ins2h(int instr, long c, long asz, where a, int a_changed)
{
	mach_op *opc = make_hex_value(c);
	mach_op *opa = operand(asz, a);
	bitpattern ch = regs_changed(opa, a_changed);
	make_instr(instr, opc, opa, ch);
}

void
save_stack(void)
{
	if (extra_stack || stack_dec) {
		error(ERR_SERIOUS, "unclean stack");
	}
	asm_comment("Save stack pointer");
	ins2(m_movl, 32, 32, SP, firstlocal, 1);
}

void
restore_stack(void)
{
	if (extra_stack || stack_dec) {
		error(ERR_SERIOUS, "unclean stack");
	}
	asm_comment("Restore stack pointer");
	ins2(m_movl, 32, 32, firstlocal, SP, 1);
}
