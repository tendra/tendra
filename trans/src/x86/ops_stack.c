/* $Id$ */

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

static exp cont_stacklimit = NULL; /* initialised if and when needed */

int
use_pop_ass(exp n, exp ln)
{
	exp id;

	if (ln->tag == cont_tag) {
		ln = son(ln);
	}

	if (ln->tag != name_tag) {
		return 0;
	}

	id = son(ln);
	while (n != id && n->last &&
		   (is_a(n->tag) || n->tag == ident_tag ||
			n->tag == ass_tag)) {
		n = bro(n);
	}

	if (n == id) {
		return get_reg_no(no(id)) - fstack_pos + 2;
	}

	return 0;
}

int
use_pop(exp n, exp ln)
{
	exp id;

	if (ln->tag == cont_tag) {
		ln = son(ln);
	}

	if (ln->tag != name_tag) {
		return 0;
	}

	id = son(ln);
	while (n != id && n->last) {
		n = bro(n);
	}

	if (n == id) {
		return get_reg_no(no(id)) - fstack_pos + 2;
	}

	return 0;
}

/*
 * leave proc, discarding any callee parameters
 * can overwrite %ecx
 */
void
retins(void)
{
	int n = (remove_struct_ref && has_struct_res(crt_proc_exp)) ? 32 : 0;

	if (callee_size >= 0) {
		if ((n += callee_size) == 0) {
			ins0(ret);
		} else {
			ins1(ret, 32, mw(zeroe, n / 8));
		}
	} else {	/* variable sized callees to be discarded */
		ins0 (popecx);	/* return address */
		ins0 ("pop %esp");	/* discard callees */
		if (n != 0) {
			add(slongsh, mw(zeroe, n / 8), sp, sp);
		}
		ins0("jmp *%ecx");
	}
}

void
stack_return(int longs)
{
	if (longs == 32 && (regsinuse & 0x2) == 0) {
		ins0(popedx);
#ifdef DWARF2
		if (diag == DIAG_DWARF2 && no_frame) {
			dw2_track_pop();
		}
#endif
		invalidate_dest(reg1);
		stack_dec += longs;
		return;
	}

	if (longs == 32 && (regsinuse & 0x4) == 0) {
		ins0(popecx);
#ifdef DWARF2
		if (diag == DIAG_DWARF2 && no_frame) {
			dw2_track_pop();
		}
#endif
		invalidate_dest(reg2);
		stack_dec += longs;
		return;
	}

	if (cpu & CPU_80586 && longs == 64 && (regsinuse & 0x2) == 0) {
		ins0(popedx);
#ifdef DWARF2
		if (diag == DIAG_DWARF2 && no_frame) {
			dw2_track_pop();
		}
#endif
		ins0(popedx);
#ifdef DWARF2
		if (diag == DIAG_DWARF2 && no_frame) {
			dw2_track_pop();
		}
#endif
		invalidate_dest(reg1);
		stack_dec += longs;
		return;
	}

	if (cpu & CPU_80586 && longs == 64 && (regsinuse & 0x4) == 0) {
		ins0(popecx);
#ifdef DWARF2
		if (diag == DIAG_DWARF2 && no_frame) {
			dw2_track_pop();
		}
#endif
		ins0(popecx);
#ifdef DWARF2
		if (diag == DIAG_DWARF2 && no_frame) {
			dw2_track_pop();
		}
#endif
		invalidate_dest(reg2);
		stack_dec += longs;
		return;
	}

	add(slongsh, mw(zeroe, (longs / 8)), sp, sp);
	stack_dec += longs;
#ifdef DWARF2
	if (diag == DIAG_DWARF2 && no_frame) {
		dw2_track_sp();
	}
#endif
}

/*
 * Call instruction
 */
void
callins(int longs, exp fn, int ret_stack_dec)
{
	cond1_set = false;
	cond2_set = false;

	if (fn->tag == name_tag && !isvar(son(fn)) && isglob(son(fn))) {
		exp ind = getexp(f_proc, NULL, 0, fn, NULL, 0, 0, cont_tag);
#ifdef DWARF2
		if (current_dg_info) {
			current_dg_info->data.i_call.brk = set_dw_text_label();
			current_dg_info->data.i_call.p.k = WH_STR;
			current_dg_info->data.i_call.p.u.s = (brog(son(fn))) ->name;
			current_dg_info->data.i_call.p.o = no(fn) / 8;
		}
#endif
		ins1(call, 32, mw(ind, 0));
		retcell(ind);
	} else {
		if (inmem(mw(fn, 0))) {
			move(slongsh, mw(fn, 0), reg0);
			fn = reg0.where_exp;
		}

#ifdef DWARF2
		if (current_dg_info) {
			int rn;
			if (fn->tag == name_tag && !isvar(son(fn))) {
				rn = no(son(fn));
			} else if (fn->tag == cont_tag && son(fn)->tag == name_tag &&
			           isvar(son(son(fn)))) {
				rn = no(son(son(fn)));
			} else {
				error(ERR_INTERNAL, "where?");
				rn = 1;
			}
			current_dg_info->data.i_call.brk = set_dw_text_label();
			current_dg_info->data.i_call.p.k = WH_REG;
			current_dg_info->data.i_call.p.u.l = get_reg_no(rn);
		}
#endif

		ins1ind(call, 32, mw(fn, 0));
	}

	stack_dec = ret_stack_dec;
#ifdef DWARF2
	if (diag == DIAG_DWARF2) {
		dw2_start_basic_block();
	}
#endif

	if (longs == 32 || (longs == 64 && cpu & CPU_80586) ||
	    !no_frame || !not_in_params || !not_in_postlude) {
		stack_return(longs);
	} else {
		keep_short = true;
	}
}

void
jumpins(exp lab)
{
	if (inmem(mw(lab, 0))) {
		move(slongsh, mw(lab, 0), reg0);
		lab = reg0.where_exp;
	}

	ins1ind(jmp, 32, mw(lab, 0));
}

/* Decrease the stack */
void
decstack(int longs)
{
	ins2(subl,  32,  32, mw(zeroe, (longs / 8)), sp);
}

void
long_jump(exp e)
{
	UNUSED(e);

	ins0(popebp);
	ins0(ret);
}

exp
find_stlim_var(void)
{
	return make_extn("__trans386_stack_limit", ulongsh, 1);
}

void
checkalloc_stack(where sz, int b)
{
	/* uses reg1 */
	int erlab = next_lab();
	int cnlab = next_lab();

	if (cont_stacklimit == NULL) {
		cont_stacklimit = make_extn("__trans386_stack_limit", ulongsh, 1);
		if (!PIC_code) {
			cont_stacklimit = getexp(ulongsh, NULL, 1, cont_stacklimit, NULL, 0, 0, cont_tag);
		}
	}

	ins2(movl, 32, 32, sp, reg1);
	ins2(subl, 32, 32, sz, reg1);
	simple_branch(jb, erlab);
	if (PIC_code) {
		ins2(movl, 32, 32, mw(cont_stacklimit, 0), reg0);
		ins2(cmpl, 32, 32, ind_reg0, reg1);
		simple_branch(ja, cnlab);
	} else {
		ins2(cmpl, 32, 32, mw(cont_stacklimit, 0), reg1);
		simple_branch(ja, cnlab);
	}

	simple_set_label(erlab);
	trap_ins(f_stack_overflow);
	simple_set_label(cnlab);
	if (b) {
		ins2(movl, 32, 32, reg1, sp);
	}
}

void
save_stack(void)
{
	if (extra_stack || stack_dec) {
		error(ERR_INTERNAL, "unclean stack");
	}

	ins2(movl, 32, 32, sp, firstlocal);
}

void
restore_stack(void)
{
	if (extra_stack || stack_dec) {
		error(ERR_INTERNAL, "unclean stack");
	}

	ins2(movl, 32, 32, firstlocal, sp);
}

