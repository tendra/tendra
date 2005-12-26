/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1996
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


#include "config.h"
#include "common_types.h"
#include "exp.h"
#include "install_fns.h"
#include "externs.h"
#include "shapemacs.h"
#include "tags.h"
#include "instrs.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "codex.h"
#include "evaluate.h"
#include "utility.h"
#include "where.h"
#include "coder.h"
#include "instr.h"
#include "translate.h"


/*
 *    FIND THE EXTERNAL NAME OF AN OPERAND
 *
 *    The expression e, representing an external, is looked up in the main_globals
 *    table, and its external name is returned.
 */

static char
*extname(exp e)
{
    dec *d = brog (e);
#if 0
    if (d->dec_u.dec_val.external_register) {
		error ("External registers not yet implemented");
		return ("????");
    }
#endif
    return (d->dec_u.dec_val.dec_id);
}


/*
 *    MACROS
 *
 *    These macros are used as convenient shorthands in operand.
 */

#define  make_ind(X, Y)	make_indirect (reg (X), (Y) / 8)
#define  make_ext(X, Y)	make_extern (extname (X), (Y) / 8)
#define  make_ext_ind(X, Y)	make_extern_ind (extname (X), (Y) / 8)


/*
 *    TRANSLATE AN INDEX OPERAND
 *
 *    The operand corresponding to w1 indexed by w2 times sf is translated into
 *    a mach_op.
 */

static mach_op
*index_opnd(where w1, where w2, int sf)
{
    mach_op *op1, *op2;
    if (name (w2.wh_exp) != name_tag) {
		error ("Illegal index operand");
		return (null);
    }
    op1 = operand (L32, w1);
    op2 = operand (L32, w2);
    return (make_index_op (op1, op2, sf));
}


/*
 *    ERROR MESSAGE
 *
 *    In debugging mode a little extra information is always useful.
 */

#ifdef EBUG
static char *illegal_operand = "Illegal operand, case %d";
#else
static char *illegal_operand = "Illegal operand";
#endif


/*
 *    TRANSLATE A TDF OPERAND INTO A MACHINE OPERAND
 *
 *    The value wh of size sz is converted into a mach_op.
 */

mach_op
*operand(long sz, where wh)
{
    long d;
    mach_op *op;
    exp w = wh.wh_exp;
    long off = wh.wh_off;
	
    switch (name (w)) {
		
	case val_tag : {
	    long k = no (w) + off;
	    if (is_offset (w)) k /= 8;
	    if (sz == 8) k &= 0xff;
	    if (sz == 16) k &= 0xffff;
	    return (make_value (k));
	}
		
	case ident_tag :
	case labst_tag : {
	    switch (ptno (w)) {
		case var_pl : {
		    d = no (w) - off;
		    return (make_rel_ap (-(d / 8)));
		}
#ifndef tdf3
		case par2_pl : {
		    d = no (w) + off;
		    return (make_rel_ap2 (d / 8));
		}
		case par3_pl : {
		    d = no (w) + off;
		    return (make_rel_sp (d / 8));
		}
#endif
		case par_pl : {
		    d = no (w) + off + 32;
		    return (make_rel_ap (d / 8));
		}
		case reg_pl : {
		    return (make_register (reg (no (w))));
		}
		default : {
		    error (illegal_operand, 0);
		    return (null);
		}
	    }
	}
		
	case name_tag : {
	    exp id = son (w);
	    long d1 = no (w) + off;
	    long d2 = no (id);
		
	    if (isglob (id)) {
			if (name(sh(w)) == prokhd){
#if 1
				if ((son (id) == nilexp ||
					 name (son (id)) == proc_tag ||
					 name(son(id)) == general_proc_tag))
#endif
					return (make_ext (id, d1));
				
			}
			return (make_ext_ind (id, d1));
	    }
		
	    switch (ptno (id)) {
#ifndef tdf3
		case par2_pl : {
			return (make_rel_ap2 ((d1 + d2 ) / 8));
		}
		case par3_pl : {
			return (make_rel_sp ((d1 + d2 ) / 8));
		}
#endif
			
		case par_pl : {
		    return (make_rel_ap ((d1 + d2 + 32) / 8));
		}
		case var_pl : {
		    return (make_rel_ap ((d1 - d2) / 8));
		}
		case reg_pl : {
		    return (make_register (reg (d2)));
		}
		default : {
		    error (illegal_operand, 1);
		    return (null);
		}
	    }
	}
		
	case cont_tag :
	case ass_tag : {
	    exp r = son (w);
	    switch (name (r)) {
			
		case name_tag : {
		    exp id = son (r);
		    if (!isvar (id)) {
				if (isglob (id)) {
					int ra;
					if (name (sh (w)) == prokhd) {
						if (off) error (illegal_operand, 2);
						return (make_ext_ind (id, no (r)));
					}
					op = make_ext_ind (id, off);
					ra = tmp_reg (m_movl, op);
					return (make_indirect (ra, no (r) / 8));
				}
				switch (ptno (id)) {
			    case par_pl : {
					d = no (id) + no (r) + 32;
					op = make_ind_rel_ap (d / 8, off / 8);
					return (op);
			    }
#ifndef tdf3
			    case par2_pl : {
					d = no (id) + no (r);
					op = make_ind_rel_ap2 (d / 8, off / 8);
					return (op);
			    }
			    case par3_pl : {
					d = no (id) + no (r);
					op = make_ind_rel_ap3 (d / 8, off / 8);
					return (op);
			    }
#endif
			    case var_pl : {
					d = -(no (id)) + no (r);
					op = make_ind_rel_ap (d / 8, off / 8);
					return (op);
			    }
			    case reg_pl : {
					return (make_ind (no (id), off));
			    }
			    default : {
					error (illegal_operand, 4);
					return (null);
			    }
				}
		    } else {
				where new_w;
				new_w.wh_exp = r;
				new_w.wh_off = off;
				return (operand (sz, new_w));
		    }
		}
			
		case cont_tag : {
		    exp rr = son (r);
			int roff = 0;
			if (name (rr) == reff_tag){
				rr = son(rr);
				roff = no(rr);
			}
		    switch (name (rr)) {
				
			case name_tag : {
			    exp id = son (rr);
#if 0
			    if (!isvar (id)) {
					error (illegal_operand, 5);
					return (null);
			    }
#endif
			    if (isglob (id)) {
					int ra;
					op = make_ext_ind (id, no (rr));
					ra = tmp_reg (m_movl, op);
					return (make_indirect (ra, off / 8));
			    }
			    switch (ptno (id)) {
				case par_pl : {
				    d = no (id) + no (rr) + 32 + roff;
				    op = make_ind_rel_ap (d / 8, off / 8);
				    return (op);
				}
#ifndef tdf3
				case par2_pl : {
				    d = no (id) + no (rr);
				    op = make_ind_rel_ap2 (d / 8, off / 8);
				    return (op);
				}
				case par3_pl : {
				    d = no (id) + no (rr);
				    op = make_ind_rel_ap3 (d / 8, off / 8);
				    return (op);
				}
#endif
				case var_pl : {
				    d = -(no (id)) + no (rr) + roff;
				    op = make_ind_rel_ap (d / 8, off / 8);
				    return (op);
				}
				case reg_pl : {
				    return (make_ind (no (id), off));
				}
				default : {
				    error (illegal_operand, 6);
				    return (null);
				}
			    }
			}
				
			default : {
			    error (illegal_operand, 7);
			    return (null);
			}
		    }
		}
			
		case reff_tag : {
		    exp rr = son (r);
		    switch (name (rr)) {
				
			case name_tag : {
			    exp id = son (rr);
			    if (isglob (id)) {
					int ra;
					op = make_ext_ind (id, 0);
					ra = tmp_reg (m_movl, op);
					return (make_indirect (ra, no (r) / 8));
			    }
			    switch (ptno (id)) {
				case reg_pl : {
				    d = no (r) + off;
				    return (make_ind (no (id), d));
				}
				case par2_pl:
				case par3_pl:
				case par_pl : {
				    int ra;
				    where new_w;
				    new_w.wh_exp = id;
				    new_w.wh_off = 0;
				    op = operand (L32, new_w);
				    ra = tmp_reg (m_movl, op);
				    d = no (r) + off;
				    return (make_indirect (ra, d / 8));
				}
				case var_pl : {
				    int ra;
				    where new_w;
				    new_w.wh_exp = id;
				    new_w.wh_off = 0;
				    op = operand (L32, new_w);
				    ra = tmp_reg (m_movl, op);
				    d = no (r) + off;
				    return (make_indirect (ra, d / 8));
				}
				default : {
				    error (illegal_operand, 8);
				    return (null);
				}
			    }
			}
				
			case cont_tag : {
			    exp rrr = son (rr);
			    exp id = son (rrr);
			    if (ptno (id) == reg_pl) {
					d = no (r) + off;
					return (make_ind (no (id), d));
			    }
			    if (ptno (id) == var_pl) {
					int ra;
					where new_w;
					new_w.wh_exp = id;
					new_w.wh_off = 0;
					op = operand (L32, new_w);
					ra = tmp_reg (m_movl, op);
					d = no (r) + off;
					return (make_indirect (ra, d / 8));
			    }
			    error (illegal_operand, 9);
			    return (null);
			}
				
			case addptr_tag : {
			    where new_w;
			    new_w.wh_exp = rr;
			    new_w.wh_off = no (r) + off;
			    return (operand (sz, new_w));
			}
				
			default : {
			    error (illegal_operand, 10);
			    return (null);
			}
		    }
		}
			
		case addptr_tag : {
		    where wb, wc;
		    exp rr = son (r);
		    exp eb = bro (rr);
		    exp ec = simple_exp (cont_tag);
		    son (ec) = rr;
		    wb.wh_exp = eb;
		    wb.wh_off = 0;
		    wc.wh_exp = ec;
		    wc.wh_off = off;
		    switch (name (eb)) {
				
			case name_tag :
			case cont_tag : {
			    return (index_opnd (wc, wb, 1));
			}
				
			case offset_mult_tag : {
			    long k = no (bro (son (eb))) / 8;
			    if (sz == 8 * k) {
					wb.wh_exp = son (eb);
					wb.wh_off = 0;
					return (index_opnd (wc, wb, (int) k));
			    }
			    error (illegal_operand, 11);
			    return (null);
			}
				
			default : {
			    error (illegal_operand, 12);
			    return (null);
			}
		    }
		}
			
		default : {
		    error (illegal_operand, 14);
		    return (null);
		}
	    }
	}
		
	case dummy_tag : {
	    exp r = son (w);
	    switch (name (r)) {
			
		case ident_tag : {
		    /* This is used by m_lea */
		    switch (ptno (r)) {
			case reg_pl : {
			    return (make_ind (no (r), no (w)));
			}
			case var_pl : {
			    int ra;
			    where new_w;
			    new_w.wh_exp = r;
			    new_w.wh_off = 0;
			    op = operand (L32, new_w);
			    ra = tmp_reg (m_movl, op);
			    d = no (w);
			    return (make_indirect (ra, d / 8));
			}
			default : {
			    error (illegal_operand, 15);
			    return (null);
			}
		    }
		}
			
		case name_tag : {
		    exp id = son (r);
		    if (isglob (id)) {
				return (make_ext_ind (id, no (w)));
		    }
		    switch (ptno (id)) {
			case reg_pl : {
			    return (make_ind (no (id), no (w)));
			}
			case var_pl : {
			    int ra;
			    where new_w;
			    new_w.wh_exp = id;
			    new_w.wh_off = 0;
			    op = operand (L32, new_w);
			    ra = tmp_reg (m_movl, op);
			    d = no (w);
			    return (make_indirect (ra, d / 8));
			}
			default : {
			    error (illegal_operand, 16);
			    return (null);
			}
		    }
		}
			
		case cont_tag :
		case ass_tag : {
		    exp rr = son (r);
		    exp id = son (rr);
		    if (isglob (id)) {
				return (make_ext_ind (id, no (w)));
		    }
		    switch (ptno (id)) {
			case reg_pl : {
			    return (make_ind (no (id), no (w)));
			}
			case var_pl : {
			    int ra;
			    where new_w;
			    new_w.wh_exp = id;
			    new_w.wh_off = 0;
			    op = operand (L32, new_w);
			    ra = tmp_reg (m_movl, op);
			    d = no (w);
			    return (make_indirect (ra, d / 8));
			}
			default : {
			    error (illegal_operand, 17);
			    return (null);
			}
		    }
		}
			
		case addptr_tag : {
		    where new_w;
		    new_w.wh_exp = r;
		    new_w.wh_off = no (w) + off;
		    return (operand (sz, new_w));
		}
			
		default : {
		    error (illegal_operand, 18);
		    return (null);
		}
	    }
	}
		
	case reff_tag : {
	    exp r = son (w);
	    switch (name (r)) {
			
		case name_tag : {
		    exp id = son (r);
		    if (isglob (id)) {
				return (make_ext (id, no (w)));
		    }
		    switch (ptno (id)) {
			case reg_pl : {
			    if (no (w)) {
					int ra = reg (no (id));
					if (is_dreg (ra)) {
						op = make_register (ra);
						ra = tmp_reg (m_movl, op);
						add_to_reg (ra, no (w) / 8);
					} else {
						op = make_indirect (ra, no (w) / 8);
						ra = tmp_reg (m_lea, op);
					}
					return (make_register (ra));
			    }
			    d = no (id);
			    return (make_register (reg (d)));
			}
			default : {
			    error (illegal_operand, 19);
			    return (null);
			}
		    }
		}
			
		case cont_tag :
		case ass_tag : {
		    exp rr = son (r);
		    exp id = son (rr);
		    if (isglob (id)) {
				if (no (w)) {
					int ra;
					op = make_ext_ind (id, 0);
					ra = tmp_reg (m_movl, op);
					add_to_reg (ra, no (w) / 8);
					return (make_register (ra));
				}
				return (make_ext_ind (id, 0));
		    }
		    switch (ptno (id)) {
			case reg_pl : {
			    debug_warning ("reff - untested case");
			    return (make_ind (no (id), no (w)));
			}
			case var_pl : {
			    int ra;
			    where new_w;
			    new_w.wh_exp = id;
			    new_w.wh_off = 0;
			    op = operand (L32, new_w);
			    ra = tmp_reg (m_movl, op);
			    if (no (w)) add_to_reg (ra, no (w) / 8);
			    return (make_register (ra));
			}
			default : {
			    error (illegal_operand, 20);
			    return (null);
			}
		    }
		}
			
		case addptr_tag : {
		    where new_w;
		    debug_warning ("reff - untested case");
		    new_w.wh_exp = r;
		    new_w.wh_off = 0;
		    return (operand (sz, new_w));
		}
			
		default : {
		    error (illegal_operand, 21);
		    return (null);
		}
	    }
	}
		
	case addptr_tag : {
	    where wb, wc;
	    exp r = son (w);
	    exp eb = bro (r);
	    exp ec = simple_exp (cont_tag);
	    son (ec) = r;
	    wb.wh_exp = eb;
	    wb.wh_off = 0;
	    wc.wh_exp = ec;
	    wc.wh_off = off;
	    switch (name (eb)) {
			
		case name_tag :
		case cont_tag : {
		    return (index_opnd (wc, wb, 1));
		}
			
		case offset_mult_tag : {
		    long k = no (bro (son (eb))) / 8;
		    wb.wh_exp = son (eb);
		    wb.wh_off = 0;
		    return (index_opnd (wc, wb, (int) k));
		}
			
		default : {
		    error (illegal_operand, 22);
		    return (null);
		}
	    }
	}
	case general_proc_tag:
		
	case proc_tag : {
	    long lb = next_lab ();
	    make_constant (lb, w);
	    return (make_lab (lb, 0));
	}
		
	case real_tag :
	case string_tag : {
	    long lb;
	    if (off == 0) {
			lb = next_lab ();
			make_constant (lb, w);
			return (make_lab_ind (lb, 0));
	    }
	    debug_warning ("Offset from label");
	    return (make_lab_ind (no (const_list) + 1, off / 8));
	}
		
	case res_tag : {
	    return (make_lab_ind (no (w), 0));
	}
		
	case null_tag : {
	    return (make_value (0));
	}
#ifndef tdf3
	case apply_general_tag :
	case tail_call_tag :
#endif
	case apply_tag : {
	    return (make_dec_sp ());
	}
		
	case field_tag : {
	    where new_w;
	    new_w.wh_exp = son (w);
	    new_w.wh_off = no (w) + off;
	    return (operand (sz, new_w));
	}
		
	case current_env_tag : {
	    return (make_register (REG_AP));
	}
		
#ifndef tdf3
	case env_size_tag : {
		dec* dp = brog(son(son(w)));
		return  make_lab ((long) dp, 0);
	}
		
	case env_offset_tag : {
		exp ident_exp = son (w);
		return  make_lab ((long) ident_exp, 0);
	}
#else
	case env_offset_tag : {
	    exp id = son (w);
	    switch (ptno (id)) {
		case var_pl : {
		    d = no (id) - off;
		    return (make_value (-(d / 8)));
		}
			
		case par2_pl :  {
		    d = no (id) + off;
		    return (make_value (d / 8));
		}
		case par3_pl :
			
		case par_pl : {
		    d = no (id) + off + 32;
		    if (used_stack){
				d += 32;
		    }
		    return (make_value (d / 8));
		}
	    }
	    error (illegal_operand, 23);
	    return (null);
	}
#endif
	case make_lv_tag : {
	    return (make_lab (ptno (pt (son (pt (w)))), 0));
	}
		
	case local_free_all_tag : {
	    return (make_special_data ("PA"));
	}
		
	case internal_tag : {
	    return (make_lab_ind (no (w), off / 8));
	}
		
	default : {
	    error (illegal_operand, 24);
	    return (null);
	}
    }
}


/*
 *    FIND WHICH REGISTERS ARE CHANGED IN AN OPERAND
 *
 *    This routine returns the bitmask of all the registers changed in the
 *    operand op.  c is true to indicate that the operand is being assigned
 *    to.  If c is false, the only way op can change a register is if it is
 *    a pre-decrement or post-increment.
 */

bitpattern
regs_changed(mach_op *op, int c)
{
    int t = op->type;
    if (t == MACH_DEC || t == MACH_INC) return (regmsk (op->def.num));
    if (!c) return (0);
    if (t == MACH_REG) return (regmsk (op->def.num));
    if (t == MACH_RPAIR) {
		return (regmsk (op->def.num) | regmsk (op->plus->def.num));
    }
    return (0);
}


/*
 *    OUTPUT AN INSTRUCTION WITH NO OPERANDS
 *
 *    The instruction instr is created.
 */

void
ins0(int instr)
{
    make_instr (instr, null, null, 0);
    return;
}


/*
 *    OUTPUT AN INSTRUCTION WITH ONE OPERAND
 *
 *    The instruction instr with a single operand, a, of size asz is created.
 *    a_changed is true to indicate that a is assigned to.
 */

void
ins1(int instr, long asz, where a, int a_changed)
{
    mach_op *op = operand (asz, a);
    bitpattern ch = regs_changed (op, a_changed);
    make_instr (instr, op, null, ch);
    return;
}


/*
 *    OUTPUT AN INSTRUCTION WITH TWO OPERANDS
 *
 *    The instruction instr with a two operands, a of size asz and b of size bsz,
 *    is created.  b_changed is true to indicate that b is assigned to.
 */

void
ins2(int instr, long asz, long bsz, where a,
	 where b, int b_changed)
{
    bitpattern ch;
    mach_op *opa = operand (asz, a);
    mach_op *opb = operand (bsz, b);
    ch = (regs_changed (opa, 0) | regs_changed (opb, b_changed));
    make_instr (instr, opa, opb, ch);
    return;
}


/*
 *    OUTPUT AN INSTRUCTION WITH TWO OPERANDS, ONE A CONSTANT
 *
 *    The instruction instr with a two operands, a constant c and a of size asz,
 *    is created.  a_changed is true to indicate that a is assigned to.
 */

void
ins2n(int instr, long c, long asz, where a,
	  int a_changed)
{
    mach_op *opc = make_value (c);
    mach_op *opa = operand (asz, a);
    bitpattern ch = regs_changed (opa, a_changed);
    make_instr (instr, opc, opa, ch);
    return;
}


/*
 *    OUTPUT AN INSTRUCTION WITH TWO OPERANDS, ONE A HEX CONSTANT
 *
 *    The instruction instr with a two operands, a constant c and a of size asz,
 *    is created.  a_changed is true to indicate that a is assigned to.  This
 *    routine only differs from ins2n in that the constant will be output in
 *    hex rather than decimal.
 */

void
ins2h(int instr, long c, long asz, where a,
	  int a_changed)
{
    mach_op *opc = make_hex_value (c);
    mach_op *opa = operand (asz, a);
    bitpattern ch = regs_changed (opa, a_changed);
    make_instr (instr, opc, opa, ch);
    return;
}

void
save_stack()
{
	if (extra_stack || stack_dec)
		error ("unclean stack");
	make_comment("Save stack pointer");
	ins2 (m_movl, 32, 32, SP, firstlocal, 1);
}

void
restore_stack()
{
	if (extra_stack || stack_dec)
		error ("unclean stack");
	make_comment("Restore stack pointer");
	ins2 (m_movl, 32, 32, firstlocal, SP, 1);
}

