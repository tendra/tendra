/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/xalloc.h>

#include <construct/exp.h>

#include <utility/bits.h>

#include "assembler.h"
#include "instrs.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "peephole.h"
#include "output.h"

extern bool have_cond;
extern bool just_ret;
extern long crt_ret_lab;


/*
    This table gives a correspondence between the conditional jump
    "if condition goto ..." and the opposite conditional jump
    "if not condition goto ...".
*/

#define OPPOSITE_JUMPS
#include "instr_aux.h"


/*
    This routine searches the list of all instructions for label n.
    It returns NULL if it cannot be found.
*/

static mach_ins *
find_label(long n)
{
	mach_ins *p;
	for (p = all_mach_ins; p; p = p->next) {
		if (p->ins_no == m_label_ins && p->op1->def.num == n) {
			return p;
		}
	}
	return NULL;
}


/*
    A jump alias is a label followed immediately by an unconditional
    jump to another label.  It is possible to get cycles of mutually
    dependent jump aliases.  This routine checks whether the alias a=>b
    is part of a cycle, and if so returns null.  Otherwise it returns
    the position of label b.
*/

#define  alias_max	20

static mach_ins *
check_jump_alias(long a, long b)
{
	int i, n;
	mach_ins *p, *q;
	long alias[alias_max];

	if (a == b) {
		return NULL;
	}

	alias[0] = a;
	alias[1] = b;
	p = find_label(b);
	if (p == NULL) {
		return NULL;
	}

	for (n = 2, q = p; n < alias_max; n++) {
		while (q && q->ins_no == m_label_ins)q = q->next;
		if (q && q->ins_no == m_bra) {
			long c = q->op1->def.num;
			for (i = 0; i < n; i++) {
				if (c == alias[i]) {
					return NULL;
				}
			}
			alias[n] = c;
			q = find_label(c);
		} else {
			return p;
		}
	}
	return NULL;
}


/*
    This routine finds the length of all jumps and marks each as long,
    word or byte.  The length is based on the number of instructions
    jumped over.  It would be better if the assembler could do this.
*/

#define  byte_len_min	-16
#define  byte_len_max	16
#define  word_len_min	-2000
#define  word_len_max	2000

static void
find_jump_sizes(long lmin, long lmax)
{
	long *tb;
	mach_ins *p;
	long i, n = lmax - lmin + 1;

	/* Allocate a temporary label position table */
	if (n <= 0) {
		return;
	}

	tb = xmalloc_nof(long, n);

	for (i = 0; i < n; i++) {
		tb[i] = 0;
	}

	/* Fill in label positions */
	for (p = all_mach_ins, i = 1; p; p = p->next) {
		if (p->ins_no == m_label_ins) {
			n = p->op1->def.num - lmin;
			tb[n] = i;
		} else {
			i++;
		}
	}

	/* Work out jump lengths */
	for (p = all_mach_ins, i = 1; p; p = p->next) {
		int r = p->ins_no;
		if (is_jump(r)) {
			n = p->op1->def.num;
			if (just_ret && n == crt_ret_lab && r == m_bra) {
				p->ins_no = m_rts;
				free_mach_op(p->op1);
				p->op1 = NULL;
			} else {
				int m = long_jump;
				long d = tb[n - lmin];
				if (d) {
					d -= i;
					if (d >= byte_len_min &&
					    d <= byte_len_max && d) {
						m = byte_jump;
					} else if (d >= word_len_min &&
						   d <= word_len_max) {
						m = word_jump;
					}
				}
				p->ins_no = r + m;
			}
		}
		if (r != m_label_ins) {
			i++;
		}
	}

	free(tb);
}


/*
    Normally this is just ~save_msk, but if, for example D2 is renamed to
    D1 by epilogue then D2 has to be marked as changed by procedure calls.
*/

bitpattern callmsk = 0;


/*
    This routine scans through the list of all instructions applying
    various simple optimizations.
*/

void
peephole(void)
{
    long a1, a2;
    mach_ins *p, *q;
    mach_op *op1, *op2;
    int knock_on_effects;

    mach_op *hold[32];
    bitpattern unknown;

    int removed_p;
    mach_ins *p_up, *p_down;

    long lmin = 100000, lmax = -100000;

#define  remove_p()			\
    if (p_up == NULL) {			\
	all_mach_ins = p_down;		\
    } else {				\
	p_up->next = p_down;		\
    }					\
    removed_p = 1;

    do {
	knock_on_effects = 0;
	unknown = 0xffffffff;
	p_up = NULL;
	p = all_mach_ins;
	while (p != NULL) {
	    int n = p->ins_no;
	    bitpattern ch = p->changed;

	    removed_p = 0;
	    p_down = p->next;

	    if (n == m_lea) {
		/* Some lea's can be turned into moves */
		op1 = p->op1;
		if (op1->type == MACH_CONT) {
		    op2 = op1->of;
		    if (op2->type == MACH_REG && op2->plus == NULL) {
			if (op2->def.num == p->op2->def.num) {
			    /* The move may be nugatory */
			    remove_p();
			    reclaim_ins(p);
			} else {
			    /* Create the move */
			    p->ins_no = m_movl;
			    p->op1 = op2;
			    op1->of = NULL;
			    free_mach_op(op1);
			}
		    }
		}
	    }

	    if (n == m_pea) {
		/* Some pea's can be turned into pushes */
		op1 = p->op1;
		if (op1->type == MACH_CONT) {
		    op2 = op1->of;
		    if (op2->type == MACH_REG && op2->plus == NULL) {
			/* Create the push */
			p->ins_no = m_movl;
			p->op1 = op2;
			op1->type = MACH_DEC;
			op1->def.num = REG_SP;
			op1->of = NULL;
			p->op2 = op1;
		    }
		}
	    }

	    if (n == m_bra) {
		/* Remove unreachable code after unconditional jumps */
		q = p_down;
		while (q && q->ins_no != m_label_ins) {
		    mach_ins *q1 = q->next;
		    reclaim_ins(q);
		    knock_on_effects = 1;
		    q = q1;
		}
		p->next = q;
		p_down = q;
	    }

	    if (is_jump(n)) {
		a1 = p->op1->def.num;

		/* Remove jumps to immediately following labels */
		q = p_down;
		while (q && q->ins_no == m_label_ins) {
		    a2 = q->op1->def.num;
		    if (a1 == a2) {
			remove_p();
			reclaim_ins(p);
			knock_on_effects = 1;
		    }
		    q = q->next;
		}

		if (!knock_on_effects && n != m_bra && p_down) {
		    int m = p_down->ins_no;

		    if (m == oppo_jump(n)) {
			/* A jump following its opposite jump can be
			   made unconditional */
			p_down->ins_no = m_bra;
			m = m_bra;
		    }

		    if (m == m_bra) {
			/* Negate conditionals if appropriate :

				if (cond) goto L1
				goto L2
				L1: ....

			   becomes :

				if (!cond) goto L2
				L1: ....
			*/
			q = p_down->next;
			while (q && q->ins_no == m_label_ins) {
			    a2 = q->op1->def.num;
			    if (a1 == a2) {
				remove_p();
				reclaim_ins(p);
				p_down->ins_no = oppo_jump(n);
				knock_on_effects = 1;
			    }
			    q = q->next;
			}

		    } else if (m == n) {
			/* Consecutive identical jumps are unnecessary */
			q = p_down;
			p_down = q->next;
			q->next = NULL;
			reclaim_ins(q);
			p->next = p_down;
			knock_on_effects = 1;

		    } else if (just_ret && m != m_label_ins) {
			/* Negate certain simple returns :

				if (cond) goto L1
				return x
				L1: ....

			   becomes :

				if (!cond) goto L2
				L1: ....
				.....
				L2: return x
			*/
			q = p_down->next;
			if (q && q->ins_no == m_bra &&
			     q->op1->def.num == crt_ret_lab) {
			    bool go = 0;
			    q = q->next;
			    while (q && q->ins_no == m_label_ins) {
				a2 = q->op1->def.num;
				if (a2 == a1) {
					go = 1;
				}
				if (a2 == crt_ret_lab) {
					go = 0;
				}
				q = q->next;
			    }
			    if (go) {
				a2 = next_lab();
				if (a2 < lmin) {
					lmin = a2;
				}
				if (a2 > lmax) {
					lmax = a2;
				}
				p->ins_no = oppo_jump(n);
				p->op1->def.num = a2;
				q = p_down->next;
				p->next = q->next;
				q->next = NULL;
				reclaim_ins(q);
				if (!no_align_directives) {
                                  make_instr(m_as_align4, NULL, NULL, 0);
				}
				make_label(a2);
				current_ins->next = p_down;
				p_down->next = NULL;
				current_ins = current_ins->next;
				make_instr(m_rts, NULL, NULL, 0);
				p_down = p->next;
			    }
			}
		    }
		}
	    }

	    if (n == m_label_ins) {
		/* Update maximum and minimum label numbers */
		a1 = p->op1->def.num;
		if (a1 < lmin) {
			lmin = a1;
		}
		if (a1 > lmax) {
			lmax = a1;
		}

		/* Look for jump aliases :

			L1 : goto L2
			....
			L2 : ....

		   becomes :

			goto L2
			....
			L2 :
			L1 : ....

		   provided L1=>L2 is not part of a cycle of jump aliases.
		*/
		q = p->next;
		while (q && q->ins_no == m_label_ins)q = q->next;
		if (q && q->ins_no == m_bra) {
		    a2 = q->op1->def.num;
		    q = check_jump_alias(a1, a2);
		    if (q != NULL) {
			/* Move the label */
			remove_p();
			p->next = q->next;
			q->next = p;
			knock_on_effects = 1;
		    }
		}
	    }

	    /* Look at consecutive moves */
	    if (n == m_movl && p_down && p_down->ins_no == m_movl) {
		a1 = p->op1->type;
		a2 = p->op2->type;
		if (a1 == MACH_REG && a2 != MACH_REG &&
		     !check_op(p->op2, p->op1->def.num) &&
		     equal_op(p->op2, p_down->op1)) {
		    /* b = a, c = b => b = a, c = a */
		    free_mach_op(p_down->op1);
		    p_down->op1 = make_register(p->op1->def.num);
		}
		if (a1 != MACH_REG && a2 == MACH_REG &&
		     !check_op(p->op1, p->op2->def.num) &&
		     equal_op(p->op1, p_down->op1)) {
		    /* b = a, c = a => b = a, c = b */
		    free_mach_op(p_down->op1);
		    p_down->op1 = make_register(p->op2->def.num);
		}
	    }

	    /* Moving constants into registers */
	    if ((n == m_movl || n == m_moveq) && p->op2->type == MACH_REG) {
		int t = p->op1->type;
		if (t == MACH_HEX) {
			t = MACH_VAL;
		}
		if ((t == MACH_VAL || t == MACH_EXT || t == MACH_LAB) &&
		     p->op1->plus == NULL) {
		    long z = p->op2->def.num;
		    if (!(unknown & regmsk(z)) &&
			 hold[z] ->type == t &&
			 hold[z] ->def.num == p->op1->def.num) {
			/* Move is strictly unnecessary */
			if (p_down && is_jump(p_down->ins_no)) {
			    /* Keep it in for test purposes */
			} else {
			    remove_p();
			    reclaim_ins(p);
			}
		    } else {
			hold[z] = p->op1;
			hold[z] ->type = t;
			unknown &= ~ch;
			ch = 0;
		    }
		}
	    }

	    /* Remove ignore instructions */
	    if (n == m_ignore_ins) {
		remove_p();
		reclaim_ins(p);
	    }

	    /* Deal with registers changed by procedure calls */
	    if (n == m_call) {
		    ch |= callmsk;
	    }

	    /* Update p_up, p and unknown */
	    if (!removed_p) {
		p_up = p;
		unknown |= ch;
	    }
	    p = p_down;
	}
    } while (knock_on_effects);

    /* Work out jump sizes */
    if (!asm_does_jump_lens) {
        find_jump_sizes(lmin, lmax);
    }
}


/*
    This table gives the correspondence between instruction numbers
    and instruction sizes.
*/

static bool instr_sz[] = {
#define INSTR_SIZES
#include "instr_aux.h"
};


/*
    This routine checks for (some) possible uses of post-increment and
    pre-decrement instructions.  It returns 1 if a change has been
    made.
*/

bool
post_inc_refactor(mach_ins *q, bitpattern r)
{
	long r1, r2, sz;
	int move_ins;
	bool incr = 1, use_op1 = 1, use_op2 = 1;

	mach_op *op;
	mach_ins *p = q->next;

	if (p == NULL) {
		return 0;
	}

	/* The first instruction may be m_subql */
	if (p->ins_no == m_subql) {
		sz = p->op1->def.num;
		r1 = p->op2->def.num;
		p = p->next;
		if (p == NULL) {
			return 0;
		}
		incr = 0;
	}

	/* The next instruction must be a move of two registers */
	if (p->ins_no != m_movl) {
		return 0;
	}
	if (p->op1->type != MACH_REG) {
		return 0;
	}
	if (p->op2->type != MACH_REG) {
		return 0;
	}
	if (incr) {
		r1 = p->op1->def.num;
	} else {
		/* The first register must be the one in the m_subql */
		if (p->op1->def.num != r1) {
			return 0;
		}
	}

	/* The second register must be that given by r */
	r2 = p->op2->def.num;
	if (regmsk(r2) != r) {
		return 0;
	}

	if (incr) {
		/* The next instruction must be "lea sz(r2), r1" */
		p = p->next;
		if (p == NULL) {
			return 0;
		}
		if (p->ins_no != m_lea) {
			return 0;
		}
		if (p->op1->type != MACH_CONT) {
			return 0;
		}
		if (p->op1->of->type != MACH_REG) {
			return 0;
		}
		if (p->op1->of->def.num != r2) {
			return 0;
		}
		if (p->op1->of->plus->type != MACH_VAL) {
			return 0;
		}
		sz = p->op1->of->plus->def.num;
		if (p->op2->type != MACH_REG) {
			return 0;
		}
		if (p->op2->def.num != r1) {
			return 0;
		}
	}

	/* Check the value of sz */
	if (sz == 1) {
		move_ins = m_movb;
	} else if (sz == 2) {
		move_ins = m_movw;
	} else if (sz == 4) {
		move_ins = m_movl;
	} else {
		return 0;
	}

	p = p->next;
	if (p == NULL) {
		return 0;
	}
	if (p->next) {
		/* The next instruction may be "move (r2), reg" */
		if (p->next->next) {
			return 0;
		}
		if (p->next->ins_no != move_ins) {
			return 0;
		}
		op = p->next->op1;
		if (op->type != MACH_CONT) {
			return 0;
		}
		if (op->of->type != MACH_REG) {
			return 0;
		}
		if (op->of->def.num != r2) {
			return 0;
		}
		if (op->of->plus != NULL) {
			return 0;
		}
	}

	/* Check the size of the current operation */
	if (!is_simple(p->ins_no) || instr_sz[p->ins_no] != sz) {
		return 0;
	}

	/* Check if the first operand is (r2) */
	if (p->op1) {
		op = p->op1;
		if (op->type != MACH_CONT) {
			use_op1 = 0;
		} else {
			if (op->of->type != MACH_REG) {
				use_op1 = 0;
			}
			if (op->of->def.num != r2) {
				use_op1 = 0;
			}
			if (op->of->plus != NULL) {
				use_op1 = 0;
			}
		}
	} else {
		use_op1 = 0;
	}

	/* Check if the second operand is (r2) */
	if (p->op2) {
		op = p->op2;
		if (op->type != MACH_CONT) {
			use_op2 = 0;
		} else {
			if (op->of->type != MACH_REG) {
				use_op2 = 0;
			}
			if (op->of->def.num != r2) {
				use_op2 = 0;
			}
			if (op->of->plus != NULL) {
				use_op2 = 0;
			}
		}
	} else {
		use_op2 = 0;
	}

	/* Check that the operands are alright */
	if (use_op1 + use_op2 != 1) {
		return 0;
	}
	if (use_op1 && check_op(p->op2, r2)) {
		return 0;
	}
	if (use_op2 && check_op(p->op1, r2)) {
		return 0;
	}

	/* Make the change */
	reclaim_ins(q->next->next);
	reclaim_ins(q->next);
	if (use_op1) {
		free_mach_op(p->op1);
		p->op1 = (incr ? make_inc_sp(): make_dec_sp());
		p->op1->def.num = r1;
	} else {
		free_mach_op(p->op2);
		p->op2 = (incr ? make_inc_sp(): make_dec_sp());
		p->op2->def.num = r1;
	}
	p->changed |= regmsk(r1);
	q->next = p;
	if (p->next) {
		p->next->op1->of->def.num = r1;
		if (incr)p->next->op1->of->plus = make_value(-sz);
	} else {
		if (use_op2)have_cond = 0;
	}
	return 1;
}
