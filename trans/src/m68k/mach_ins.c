/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/xalloc.h>

#include "instrs.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "codex.h"
#include "output.h"
#include "utility.h"

extern bool have_cond;

/*
    If this is true, all instructions are output immediately.  This
    effectively switches off all peephole optimizations.
*/

int output_immediately = 0;

/*
    A list of all instructions in maintained.  The current instruction is
    given by current_ins.
*/

mach_ins *all_mach_ins = NULL;
mach_ins *current_ins = NULL;


/*
    This is used to help get a more accurate idea of which registers
    are known during the peephole optimizations.
*/

long last_jump = -1;
bitpattern last_jump_regs = 0;


/*
    A list of free mach_ins's, linked by their next field, is maintained.
*/

static mach_ins *mach_ins_list = NULL;


/*
    The operands of the instruction are freed and the instruction
    itself is added to the list of all free instructions.
*/

void
reclaim_ins(mach_ins *p)
{
	if (p->op1) {
		free_mach_op(p->op1);
	}
	if (p->op2) {
		free_mach_op(p->op2);
	}
	p->next = mach_ins_list;
	mach_ins_list = p;
}


/*
    All the instructions in the list of all instructions are freed and
    the list is reset to zero length.
*/

void
free_all_ins(void)
{
	mach_ins *p = all_mach_ins, *q = NULL;
	if (p == NULL) {
		return;
	}
	while (p != NULL) {
		if (p->op1) {
			free_mach_op(p->op1);
		}
		if (p->op2) {
			free_mach_op(p->op2);
		}
		q = p;
		p = p->next;
	}
	q->next = mach_ins_list;
	mach_ins_list = all_mach_ins;
	all_mach_ins = NULL;
	current_ins = NULL;
	last_jump = -1;
	last_jump_regs = 0;
}


/*
    A new instruction, with instruction number insno and operands op1 and
    op2 is added to the list of all instructions.  ch gives the mask of
    all registers changed by the instruction.  If susp is true then
    this instruction is never output immediately.  This only occurs in
    tmp_reg.

    This routine is usual called via the macro make_instr which has the
    same first four arguments, but has susp always false.
*/

#ifndef NDEBUG
static int next_id = 0;
#endif

void
make_instr_aux(int insno, mach_op *op1, mach_op *op2, bitpattern ch, int susp)
{
	mach_ins *p;
	if (insno != m_comment) {
		if (stack_change) {
			update_stack();
		}
	}
	if (mach_ins_list == NULL) {
		int i, n = 1000;
		mach_ins_list = xmalloc_nof(mach_ins, n);
		for (i = 0; i < n - 1; i++) {
			(mach_ins_list + i) ->next = mach_ins_list + (i + 1);
		}
		(mach_ins_list + (n - 1))->next = NULL;
	}
	p = mach_ins_list;
	mach_ins_list = p->next;
#ifndef NDEBUG
	p->id = ++next_id;
#if 0
	/*
	 * This is for debugging convenience; the idea is to watch 'found'
	 * for the instruction number just before the one you're after,
	 * and then step forwards.
	 */
	if (p->id == 4803) {
		int found = 1;
	}
#endif
#endif
	p->ins_no = insno;
	p->op1 = op1;
	p->op2 = op2;
	p->changed = ch;
	last_jump_regs |= ch;
	if (current_ins == NULL) {
		p->next = all_mach_ins;
		all_mach_ins = p;
	} else {
		p->next = current_ins->next;
		current_ins->next = p;
	}
	current_ins = p;

	if (insno != m_comment) {
		/* Clear the temporary register status */
		tmp_reg_status = 0;
		tmp_reg_prefer = 0;
	}

	if (output_immediately && !susp) {
		output_all();
		free_all_ins();
	}
}


/*
    A label is added to the list of all instructions.  This has the effect
    of marking all registers as changed.
*/

void
make_label(long n)
{
	mach_op *p = new_mach_op();
	p->type = MACH_LABQ;
	p->def.num = n;
	make_instr_aux(m_label_ins, p, NULL,(bitpattern)0xffff, 0);
	have_cond = 0;
}

/*
    An external label is added to the list of all instructions.  This has
    the effect of marking all registers as changed.
*/

void
make_external_label(char *nm)
{
	mach_op *p = new_mach_op();
	p->type = MACH_EXTQ;
	p->def.str = nm;
	make_instr_aux(m_extern_ins, p, NULL,(bitpattern)0xffff, 0);
	have_cond = 0;
}


/*
    A jump, instruction number insno, to label n, is added to the list
    of all instructions.
*/

void
make_jump(int insno, long n)
{
	mach_op *p = new_mach_op();
	p->type = MACH_LABQ;
	p->def.num = n;
	make_instr_aux(insno, p, NULL,(bitpattern)0, 0);
	if (n != last_jump) {
		last_jump = n;
		last_jump_regs = 0;
	}
}


/*
    The special label with identifier nm is set equal to the given value.
*/

void
set_special(char *nm, mach_op *op)
{
	mach_op *op1 = make_special_data(nm);
	make_instr_aux(m_as_assign, op1, op,(bitpattern)0, 0);
}

