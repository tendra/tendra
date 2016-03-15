/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/string.h>

#include <local/szs_als.h>
#include <local/ash.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/externs.h>

#include <construct/exp.h>
#include <construct/install_fns.h>
#include <construct/installglob.h>
#include <construct/reg_result.h>

#include <main/driver.h>
#include <main/flags.h>
#include <main/print.h>

#include <refactor/optimise.h>

#include "localtypes.h"
#include "mach.h"
#include "where.h"
#include "codec.h"
#include "make_code.h"
#include "operations.h"
#include "ops_shared.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "instr.h"
#include "codex.h"
#include "output.h"
#include "instrs.h"
#include "peephole.h"
#include "tests.h"
#include "utility.h"
#include "weights.h"
#include "translate.h"
#include "general_proc.h"
#include "special_exps.h"
#include "68k_globals.h"
#include "localexpmacs.h"

#include "xdb_basics.h"
#include "xdb_output.h"

void scan(bool sto, exp to, exp e);
extern bool just_ret;
extern mach_ins *prologue_ins;

static void code_postlude(exp postlude, exp callers, ash stack, long post_offset);
static bool test_push_args(exp args, ash* args_size);
static void push_args(where w, ash stack, exp args);
static void place_arguments(exp args, ash stack, long start);
static void general_epilogue(bool uses_callers_pointer, bool has_checkstack);

/* make_code.c & codex.c */
extern ast add_shape_to_stack(ash stack, shape s);
extern void prologue(void);
extern void out_profile(bool save_a1);
extern int do_pic;

/*
 * This routine encodes a procedure call. The procedure is named pname
 * with oname as an alternative (used with diagnostics).
 * The actual body of the procedure is p.
 */
void
gcproc(exp p, char *pname, long cname, int is_ext, int reg_res, diag_descriptor *di)
{
	exp t;
	ash stack;
	ash param_pos;

	mach_op *op1, *op2;
	static long crt_proc_no = 0;

	bool has_callers = 0;
	bool has_checkstack = 0;
	bool uses_callers_pointer = 0;
	cur_proc_callees_size = 0;

	/* find out if the call has tail_call or same_callees constructs */
	cur_proc_has_tail_call = 0;
	cur_proc_use_same_callees = 0;
	scan(1, p, p);
	comp_weights(p);

	/* Set up flags, register masks, stack etc. */
	has_alloca = proc_has_alloca(p);
	must_use_bp = has_alloca || proc_has_lv(p) || proc_uses_crt_env(p);
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
	used_stack = do_profile || diag != DIAG_NONE || must_use_bp;

	/* Mark procedure body */
	ptno(p) = par_pl;
	no(p) = 0;

	/* Mark procedure parameters */
	param_pos = 0;

	/* the callees are encoded first. Scan to first callee if any */

	t = son(p);
	while (t->tag == ident_tag && isparam(t) &&
	       son(t)->tag != formal_callee_tag) {
		t = bro(son(t));
		has_callers = 1;
	}

	cur_proc_has_vcallees = proc_has_vcallees(p);
	uses_callers_pointer = cur_proc_has_vcallees && has_callers;

	if (uses_callers_pointer) {
		/* ok callers are accessed by use of a5 */
		regsinproc |= regmsk(REG_A5);
		regsinuse  |= regmsk(REG_A5);
	}

	/* do we have any callees? */
	if (t->tag == ident_tag && son(t)->tag == formal_callee_tag) {
		while (t->tag == ident_tag && son(t)->tag == formal_callee_tag) {
			ast a;

			a = add_shape_to_stack(param_pos, sh(son(t)));
			no(t) = a.astoff + a.astadj + (cur_proc_has_vcallees ? 4 * 8 : 0);
			param_pos = a.astash;
			ptno(t) = par_pl;

			make_visible(t);

			t = bro(son(t));
		}

		cur_proc_callees_size = param_pos;
	}

	/* encode the caller parameters */
	{
		exp caller = son(p);
		int location_id = par_pl;

		if (uses_callers_pointer) {
			location_id = par2_pl;
			param_pos = 0;
		}

		while (caller->tag == ident_tag && isparam(caller) &&
		       son(caller)->tag != formal_callee_tag) {

			ast a;
			a = add_shape_to_stack(param_pos, sh(son(caller)));
			ptno(caller) = location_id;
			no(caller) = a.astoff + a.astadj;
			param_pos = a.astash;

			make_visible(caller);

			caller = bro(son(caller));
		}
	}

	/* calculate callers size */
	cur_proc_callers_size = param_pos;
	if (! uses_callers_pointer) {
		cur_proc_callers_size -= cur_proc_callees_size;
	}

	/* Output procedure s->tag */
	area(ptext);
	make_instr(m_as_align4, NULL, NULL, 0);
	if (is_ext && pname) {
		if (streq(pname, "_cmppt")) {
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

	if (streq(pname, "_main")) {
		asm_comment("Do Dynamic Initialization");
		op1 = make_extern_ind("___TDF_main", 0);
		make_instr(m_call, op1, NULL, 0);
	}

	/* Output profiling information if required */
	if (do_profile) {
		out_profile(!reg_res);
		used_stack = 1;
	}

	if (proc_has_checkstack(p)) {
		/*
		 * Check that there is room for env_size(<this proc>)
		 * since callers, callees & return address are pushed
		 * we only check for the rest.
		 */
		long already_allocated = cur_proc_callers_size + cur_proc_callees_size + 32;
		where w;
		w = mw(get_env_size(cur_proc_dec), - already_allocated);
		checkalloc_stack(w, 0);
		has_checkstack = 1;
	}

	/* Set up procedure prologue */
	prologue();

	/* Diagnostics for start of procedure */
	if (diag != DIAG_NONE && di) {
		xdb_diag_proc_begin(di, p, pname, cname, is_ext);
	}

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
	need_preserve_stack = 0;

	if (proc_uses_crt_env(p) && proc_has_lv(p) && has_alloca) {
		need_preserve_stack = 1;
		stack += 32;
		max_stack += 32;
		save_stack();
	}

	/* Encode the procedure body */
	if (diag != DIAG_NONE) {
		dnt_begin();
		make_code(zero, stack, t);
		dnt_end();
	} else {
		make_code(zero, stack, t);
	}

	/* Output the procedure epilogue */
	general_epilogue(uses_callers_pointer, has_checkstack);

	/* Apply peephole optimizations and return */
	if (optim & OPTIM_PEEPHOLE) {
		peephole();
	}

	/* Diagnostics for end of procedure */
	if (diag != DIAG_NONE && di) {
		xdb_diag_proc_end(di);
	}
}

/*
 * restore_regs_subsribers is used by restore_regs.
 * It is a list of places to put insructions to restore registers.
 * If untidy is true, it means that sp shall not be restored.
 */

typedef struct rrs_tag {
	mach_ins* ins;
	restore_type_t restore_type ;
	struct rrs_tag* next;
} rrs;

static rrs *restore_regs_subsribers = 0;

/*
 * RESTORE_REGS
 *
 * Subscribe on code to restore registers. See restore_regs_output below.
 * Restore_type is one of: ALL, NOT_SP, NOT_A6_OR_SP
 */
void restore_regs
(restore_type_t typ)
{
	rrs* p = xmalloc(sizeof(rrs));
	p->ins  = current_ins;
	p->next = restore_regs_subsribers;
	p->restore_type = typ;
	restore_regs_subsribers = p;
}

/* used by restore_regs_output below */
static rrs *
pop_restore_regs_subsriber(void)
{
	rrs* p = restore_regs_subsribers;

	if (p != 0) {
		restore_regs_subsribers = p->next;
	}

	return p;
}

/*
 * RESTORE_REGS_OUTPUT
 *
 * Output instructions to restore registers.
 * This is done in all places where the restore_regs call has been made.
 *
 * This procedure is called by epilogue after installing the body of a
 * General Procedure. First then we know which registers to restore.
 *
 * rmsk is the set of normal regs to restore from AP - st
 * fmsk is the set of floating point regs to restore from AP - st1
 *
 * side effect: current_ins is changed
 */
static void
restore_regs_output(bitpattern rmsk, bitpattern fmsk, long st, long st1, bool uses_link)
{
	rrs* p;

	while ((p = pop_restore_regs_subsriber())) {
		mach_op *op1, *op2;
		current_ins = p->ins;

		asm_comment("Restore Registers");

		/* Restore floating-point registers from the stack */
		if (fmsk) {
			just_ret = 0;
			op1 = make_indirect(REG_AP, -st1);
			op2 = make_hex_value(fmsk);
			make_instr(m_fmovemx, op1, op2, fmsk);
		}

		/* Restore registers from the stack */
		if (rmsk) {
			just_ret = 0;
			if (must_use_bp) {
				op1 = make_indirect(REG_AP, -st);
			} else {
				op1 = make_indirect(REG_SP, 0);
			}
			op2 = make_hex_value(rmsk);
			make_instr(m_moveml, op1, op2, rmsk);
		}

		if (uses_link) {
			just_ret = 0;

			switch (p->restore_type) {
			case ALL:
				/* Output unlink instruction */
				op1 = make_register(REG_AP);
				make_instr(m_unlk, op1, NULL, regmsk(REG_AP));
				break;
			case NOT_SP:
				asm_comment("untidy return => Restore A6, but not SP");
				op1 = make_indirect(REG_AP, 0);
				op2 = make_register(REG_AP);
				make_instr(m_movl, op1, op2, regmsk(REG_AP));
				break;
			case NOT_A6_OR_SP:
				asm_comment("exit with long jump => Don't restore A6 or SP");
				break;
			default:
				error(ERR_SERIOUS, "wrong restore type");
			}
		}
	}
}

/*
 * CLEANUP_BT
 *
 * Cleanup before a tail call is performed. Used by tail_call.
 * Restore registers and frees callees stack room and return address.
 */
static void
cleanup_bt(bool save_ret, int rg)
{
	mach_op *op1, *op2;

	asm_comment("Cleanup before tail call ...");

	/* save callees size in scratch register if needed */
	if (cur_proc_has_vcallees) {
		asm_comment("save old callees size");
		op1 = make_indirect(REG_AP, 8);
		op2 = make_register(REG_D0);
		make_instr(m_movl, op1, op2, regmsk(REG_D0));
	}

	/* subscribe on code to restore registers */
	restore_regs(ALL);

	if (save_ret) {
		asm_comment("save return address in register");
		op1 = make_indirect(REG_SP, 0);
		op2 = make_register(rg);
		make_instr(m_movl, op1, op2, regmsk(rg));
	}

	if (cur_proc_has_vcallees) {
		asm_comment("cleanup variable callees and return address");
		op1 = make_register(REG_D0);
		op2 = make_register(REG_SP);
		make_instr(m_addl, op1, op2, regmsk(REG_SP));

		op1 = make_value(8);  /* size of callers pointer & ret.addr. */
		op2 = make_register(REG_SP);
		make_instr(m_addl, op1, op2, regmsk(REG_SP));
	} else {
		asm_comment("cleanup static callees and return address");
		op1 = make_value(cur_proc_callees_size / 8 + 4);
		op2 = make_register(REG_SP);
		make_instr(m_addl, op1, op2, regmsk(REG_SP));
	}
	asm_comment("Cleanup before tail call done");
}

/*
 * CLEANUP
 *
 * Restore registers and frees callees stack room, just before return from
 * a procedure. Used by general_epilogue.
 * The return address is restored.
 */
void cleanup
(void)
{
	mach_op *op1, *op2;
	bool callees_to_clean = cur_proc_has_vcallees || cur_proc_callees_size;

	asm_comment("Cleanup before return ...");

	/* save callees size in scratch register if needed */
	if (cur_proc_has_vcallees) {
		asm_comment("save callees size");
		op1 = make_indirect(REG_AP, 8);
		op2 = make_register(REG_A0);
		make_instr(m_movl, op1, op2, regmsk(REG_A0));
	}

	/* subscribe on code to restore registers */
	restore_regs(ALL);

	if (callees_to_clean) {
		asm_comment("save return address in register");
		op1 = make_indirect(REG_SP, 0);
		op2 = make_register(REG_A1);
		make_instr(m_movl, op1, op2, regmsk(REG_A1));

		if (cur_proc_has_vcallees) {
			asm_comment("cleanup variable callees and return address");
			op1 = make_register(REG_A0);
			op2 = make_register(REG_SP);
			make_instr(m_addl, op1, op2, regmsk(REG_SP));

			op1 = make_value(4); /* size of callers pointer */
			op2 = make_register(REG_SP);
			make_instr(m_addl, op1, op2, regmsk(REG_SP));
		} else {
			asm_comment("cleanup static callees");
			op1 = make_value(cur_proc_callees_size / 8);
			op2 = make_register(REG_SP);
			make_instr(m_addl, op1, op2, regmsk(REG_SP));
		}

		asm_comment("put return address back on the stack");
		op1 = make_register(REG_A1);
		op2 = make_indirect(REG_SP, 0);
		make_instr(m_movl, op1, op2, 0);
	}
	asm_comment("Cleanup before return done");
}

/*
 * PUSH_RANGE
 *
 * Push memory in the range [start, end] on the stack. (start > end).
 * (modifies start, end, SP)
 */
static void
push_range(int start, int end)
{
	mach_op *op1, *op2;
	long lb;

	asm_comment("Push range");

	lb = next_lab();
	make_label(lb);

	op1 = make_predec(start);
	op2 = make_dec_sp();
	make_instr(m_movw, op1, op2, regmsk(REG_SP));

	op1 = make_register(start);
	op2 = make_register(end);
	make_instr(m_cmpl, op1, op2, 0);

	make_jump(m_bne, lb);
}

/*
 * MAKE_CALLEES_SIZE
 *
 * Returns an operand specifying the size of the callees for
 * the current procedure.
 */
static mach_op *
make_callees_size(void)
{
	/* Is it a run time value ? */
	if (cur_proc_has_vcallees) {
		return make_indirect(REG_AP, 8);
	}

	/* or compile time value ? */
	return make_value(cur_proc_callees_size / 8);
}

/*
 * PUSH_SAME_CALLEES
 *
 * Used by apply_general_proc to push the same callees
 * (modifies A0,D0,D1,SP)
 */
static void
push_same_callees(bool var_callees)
{
	mach_op *op1, *op2;

	/* do we have any callees to push? */
	if (cur_proc_has_vcallees || cur_proc_callees_size) {
		asm_comment("Push same callees");
		asm_comment("end of callees");
		op1 = make_register(REG_AP);
		op2 = make_register(REG_D1);
		make_instr(m_movl, op1, op2, regmsk(REG_D1));

		/* add sizeof(ret-addr)+sizeof(preincrement) ?+sizeof(callees size)? */
		op1 = make_value((cur_proc_has_vcallees) ? 12 : 8);
		op2 = make_register(REG_D1);
		make_instr(m_addl, op1, op2, regmsk(REG_D1));

		asm_comment("start of callees");
		op1 = make_register(REG_D1);
		op2 = make_register(REG_A0);
		make_instr(m_movl, op1, op2, regmsk(REG_A0));

		op1 = make_callees_size();
		op2 = make_register(REG_A0);
		make_instr(m_addl, op1, op2, regmsk(REG_A0));

		push_range(REG_A0, REG_D1);
	}

	if (var_callees) {
		asm_comment("push size of callees on the stack");
		op1 = make_callees_size();
		op2 = make_dec_sp();
		make_instr(m_movl, op1, op2, regmsk(REG_SP));

		stack_size -= 32;
	}
}

/*
 * PUSH_DYNAMIC_CALLEES
 *
 * Used by apply_general_proc to push dynamic callees
 * Callees size is available in D1 afterwards.
 * (modifies A0,D0,D1,SP)
 */
static void
push_dynamic_callees(exp pcallees, ash stack)
{
	mach_op *op1, *op2;
	exp ptr = son(pcallees);
	exp sze = bro(ptr);
	exp ident, ident_def;
	bool const_compound_shape = 0;
	long total_size = 0;

	asm_comment("Push dynamic callees");

	make_code(A1, stack, ptr);
	make_code(D1, stack, sze);

	/* are callees of compond shape ? */
	if (ptr->tag == name_tag) {
		ident = son(ptr);
		ident_def = son(ident);
		if (ident_def->tag == compound_tag) {
			const_compound_shape = !(isvar(ident));
		}
	}

	if (const_compound_shape) {
		long value;
		exp pair = son(ident_def);
		if (pair) {
			for (;;) {
				pair = bro(pair);
				value = no(pair);

				op1 = make_value(value);
				op2 = make_dec_sp();
				make_instr(m_movl, op1, op2, regmsk(REG_SP));
				total_size += 4;

				if (pair->last) {
					break;
				}
				pair = bro(pair);
			}
		}
	} else {
		/* Let A0 point to end of callees */
		op1 = make_register(REG_A1);
		op2 = make_register(REG_A0);
		make_instr(m_movl, op1, op2, regmsk(REG_A0));

		op1 = make_register(REG_D1);
		op2 = make_register(REG_A0);
		make_instr(m_addl, op1, op2, regmsk(REG_A0));

		push_range(REG_A0, REG_A1);
	}

	if (call_has_vcallees(pcallees)) {
		asm_comment("push size of dynamic callees on the stack");
		if (const_compound_shape) {
			op1 = make_value(total_size);
		} else {
			op1 = make_register(REG_D1);
		}
		op2 = make_dec_sp();
		make_instr(m_movl, op1, op2, regmsk(REG_SP));

		stack_size -= 32;
	} else {
		debug_warning("call with dynamic callees requires var_callees PROCPROPS");
	}
}

/*
 * PUSH_DYNAMIC_CALLEES_BT
 *
 * Used by tail_call to push dynamic callees
 * (modifies A0,A1,D0,D1,SP)
 */
static void
push_dynamic_callees_bt(exp pcallees, ash stack)
{
	mach_op *op1, *op2;

	push_dynamic_callees(pcallees, stack);

	asm_comment("push return address");
	op1 = make_indirect(REG_AP, 4);
	op2 = make_dec_sp();
	make_instr(m_movl, op1, op2, regmsk(REG_SP));

	asm_comment("put end of callees, size & return address in A1");
	op1 = make_register(REG_SP);
	op2 = make_register(REG_A1);
	make_instr(m_movl, op1, op2, regmsk(REG_A1));

	asm_comment("put start of callees in A0");
	op1 = make_register(REG_A1);
	op2 = make_register(REG_A0);
	make_instr(m_movl, op1, op2, regmsk(REG_A0));

	/* add size of callee from D1 */
	op1 = make_register(REG_D1);
	op2 = make_register(REG_A0);
	make_instr(m_addl, op1, op2, regmsk(REG_A0));

	/* add size of return address and size of callees size if needed */
	op1 = make_value((call_has_vcallees(pcallees)) ? 8 : 4);
	op2 = make_register(REG_A0);
	make_instr(m_addl, op1, op2, regmsk(REG_A0));

	cleanup_bt(0, 0);

	push_range(REG_A0, REG_A1);
}

/*
 * A1_RESULT_POINTER
 *
 * For results which do not fit into registers a pointer to
 * where the result is to be put is passed in A1
 */
static void
A1_result_pointer(long comp_size, long longs, long start_stack, where dest)
{
	if (comp_size) {
		/* Find the space allocated for unwanted results */
		where w;
		w = mnw(longs / 8);
		asm_comment("let A1 point to unwanted compund result");
		add(slongsh, SP, w, A1);
	} else {
		long doff;
		/* Find the address of where the result is to be put */
		tmp_reg_prefer = REG_A1;

		if (apply_tag_flag) {
			/*
			 * For recursive use of apply_proc or apply_general
			 * we need to be very careful if the result is itself
			 * to be a procedure argument to get the right stack offset.
			 */

			/* push old value */
			long ex = extra_stack;
			extra_stack += start_stack;

			if ((dest.wh_exp == SP_p.wh_exp) && (dest.wh_is == SP_p.wh_is)) {
				/* Careful! */

				/* push where offset */
				doff = dest.wh_off;

				dest.wh_off = doff + extra_stack;

				asm_comment("let A1 point to compund result used as procedure argument");
				mova(dest, A1);

				/* pop where offset */
				dest.wh_off = doff;

			} else {
				/* Easy */
				asm_comment("let A1 point to compund result from eval. of call par.");
				mova(dest, A1);
			}

			/* pop value after call */
			extra_stack = ex ;
		} else {
			/* Otherwise (easy) ... */
			asm_comment("let A1 point to compund result");
			mova(dest, A1);
		}
	}

	/* Make sure we don't reuse A1 accidently */
	avoid_tmp_reg(REG_A1);
	regsinproc |= regmsk(REG_A1);
}

/*
 * POSTLUDE_HAS_CODE
 *
 * Returns true if postlude has code
 */
static bool
postlude_has_code(exp postlude)
{
	while (postlude->tag == ident_tag && son(postlude)->tag == caller_name_tag) {
		postlude = bro(son(postlude));
	}

	return postlude->tag != top_tag;
}

/*
 * APPLY_GENERAL_PROC
 *
 * Code a General Procedure Call.
 */
void
apply_general_proc(exp e, where dest, ash stack)
{
	/* Procedure applications */
	where tmp_dest;
	mach_op *op1, *op2;
	long comp_size = 0;
	long longs = 0, stkdec;
	long start_stack = stack_dec;
	long callers_size = 0, callees_size = 0 ; /* size of parameters on the stack */
	long size_size = 0 ;                      /* size of callees size */
	long callees_size_total = 0 ;             /* size of callees and callees size */
	long result_size = 0 ;                    /* size of result */

	bool push_result = 0, use_push = 1, reg_res;
	bool has_postlude = 0, has_checkstack = 0, is_untidy = 0;

	exp proc, caller_args, pcallees = 0, postlude = 0, callee_args = 0;

	asm_comment("Apply Proc");

	/* Find the procedure and the arguments */

	tmp_dest = dest;
	proc = son(e);
	caller_args = (!proc->last) ? bro(proc) : NULL;

	if (e->tag == apply_general_tag) {
		pcallees     = bro(caller_args);
		postlude    = bro(pcallees);
		callee_args = son(pcallees);
		caller_args = son(caller_args);

		is_untidy = call_is_untidy(e);
		has_checkstack = call_has_checkstack(e);
		has_postlude = postlude_has_code(postlude);
	}

	/* calculate length of callers and see if we can push them */

	if (! test_push_args(caller_args, &callers_size)) {
		use_push = 0;
	}

	if (pcallees) {
		if (pcallees->tag == make_callee_list_tag) {
			/* calculate length of callees and see if we can push them */
			if (! test_push_args(callee_args, &callees_size)) {
				use_push = 0;
			}
		}
		size_size = ((call_has_vcallees(pcallees)) ? 32 : 0);
		callees_size_total = callees_size + size_size;
	}

	/* total parameter space */
	longs = callers_size + callees_size_total;

	/* Does the result go into a register? */
	reg_res = reg_result(sh(e));
	if (!reg_res) {
		if (eq_where(dest, zero)) {
			/* Calculate size of ignored compound result */
			comp_size = round(shape_size(sh(e)), param_align);
		}
	}

	/* Find total amount of stack decrease */
	stkdec = longs + comp_size;

	if (has_checkstack) {
		/* check if there is room for parameters and return address on the stack */
		checkalloc_stack(mnw(stkdec / 8 + 4), 0);
	}

	/* Put arguments onto stack */
	if (use_push) {
		if (comp_size) {
			/* Make room for unwanted compound result */
			dec_stack(comp_size);
			stack_dec -= comp_size;
		}

		if (caller_args) {
			asm_comment("Push callers");
			push_args(zw(e), stack, caller_args);
		}

		if (pcallees) {
			if (pcallees->tag == make_dynamic_callee_tag) {
				push_dynamic_callees(pcallees, stack);
				stack_dec -= callees_size_total;
			} else if (pcallees->tag == same_callees_tag) {
				push_same_callees(call_has_vcallees(pcallees));
				stack_dec -= callees_size_total;
			} else {
				if (callee_args) {
					asm_comment("Push static callees");
					push_args(zw(e), stack, callee_args);
				}
				if (call_has_vcallees(pcallees)) {
					asm_comment("push size of callees on the stack");
					stack_dec -= 32;
					stack_size -= 32;

					op1 = make_value(callees_size / 8);
					op2 = make_dec_sp();
					make_instr(m_movl, op1, op2, regmsk(REG_SP));
				}
			}
		}
	} else {
		/* Can't just use push => Decrease stack instead */
		dec_stack(stkdec);
		stack_dec -= stkdec;

		if (caller_args) {
			asm_comment("Place callers on the stack");
			place_arguments(caller_args, stack, callees_size_total);
		}
		if (pcallees) {
			if (pcallees->tag == make_dynamic_callee_tag) {
				push_dynamic_callees(pcallees, stack);
			} else if (pcallees->tag == same_callees_tag) {
				push_same_callees(call_has_vcallees(pcallees));
			} else {
				if (callee_args) {
					asm_comment("Place static callees on the stack");
					place_arguments(callee_args, stack, size_size);
				}
				if (call_has_vcallees(pcallees)) {
					asm_comment("push size of callees on the stack");
					op1 = make_value(callees_size / 8);
					op2 = make_indirect(REG_SP, 0);
					make_instr(m_movl, op1, op2, regmsk(REG_SP));
				}
			}
		}
	}

	start_stack -= stack_dec;

	if (!reg_res) {
		A1_result_pointer(comp_size, longs, start_stack, dest);
	}

	/* Output the call instruction */
	callins(0, proc);

	if (is_untidy) {
		stack_dec = 0; /* We can't keep track of it any longer */
		if (need_preserve_stack) {
			save_stack();
		}
	} else {
		/* callees has now been cleaned up by called proc. */
		stack_dec += callees_size_total;
		stack_size += callees_size_total;
	}

	/* can we cleanup callers now ? */
	if (!(has_postlude || is_untidy)) {
		/* Clean up of callers and room for ignored compund result. */
		stack_dec += callers_size + comp_size;
		dec_stack(- callers_size - comp_size);
	}

	/* Move the result into place */
	if (comp_size) {
		asm_comment("(unwanted compound result)");
	} else if (eq_where(dest, zero)) {
		asm_comment("(unwanted simple result)");
	} else {
		/* ok the result is needed */
		if (has_postlude) {
			/* we need to preserve result on stack */
			result_size = rounder(shape_size(sh(e)), param_align);
			dec_stack(result_size);
			stack_dec -= result_size;
			tmp_dest = SP_p;
			push_result = 1;
		}
		if (reg_res) {
			if (shape_size(sh(e)) <= 32) {
				/* Small register results are in D0 */
				move(sh(e), D0, tmp_dest);
			} else {
				/* Larger register results are in D0 and D1 */
#ifdef SYSV_ABI
				move(sh(e), FP0, tmp_dest);
#else
				move(sh(e), D0_D1, tmp_dest);
				regsinproc |= regmsk(REG_D1);
#endif
			}
		} else {
			asm_comment("(compound result)");
			if (has_postlude) {
				asm_comment("save compound result before postlude...");
				move(sh(e), dest, tmp_dest);
				asm_comment("save compound result before postlude done");
			}

			/*
			 * Compound results should already have been copied to
			 * the position pointed to by A1 by the called procedure
			 * and returned by it in D0, so no further action should
			 * be required by the calling procedure.  Unfortunately
			 * cc doesn't always get this right for union results.
			 */
#ifdef OLD_SPEC
			if (cconv == CCONV_HP && sh(e)->tag == unhd) {
				regsinproc |= regmsk(REG_A0);
				move(slongsh, D0, A0);
				move(sh(e), A0_p, dest);
			}
#endif
		}
	}

	if (has_postlude) {
		code_postlude(postlude, caller_args, stack, result_size);

		/* put return value back in register */
		if (push_result) {
			asm_comment("restore result after postlude...");
			move(sh(e), SP_p, dest);
			asm_comment("restore result after postlude done");
			dec_stack(-result_size);
			stack_dec += result_size;
		}

		/*
		 * Delayed clean up of callers and room for ignored compund result.
		 * callees are cleaned by the called proc.
		 */
		if (! is_untidy) {
			stack_dec += callers_size + comp_size;
			dec_stack(- callers_size - comp_size);
		}
	}
}

/*
 * TEST_PUSH_ARGS
 *
 * The total stack space requiered by the arguments is returned in args_size.
 *
 * Returns true if all arguments (args) can be pushed to the stack.
 *
 * The args_size is also used if false is returned.
 */
static bool
test_push_args(exp args, ash* args_size)
{
	/* See if we can push all the arguments */

	bool use_push = 1;
	exp arg = args, formal;
	ash stack = 0;
	ast stack_add_res;

	while (arg != NULL) {
		formal = (arg->tag == caller_tag) ? son(arg) : arg;

		if (cpd_param(sh(formal))) {
			use_push = 0;
		}
		if ((sh(formal)->tag == s64hd) || (sh(formal)->tag == u64hd)) {
			use_push = 0;
		}
		if (! push_arg(formal)) {
			use_push = 0;
		}

		stack_add_res = add_shape_to_stack(stack, sh(formal));
		stack = stack_add_res.astash;

		/* information used by code_postlude */
		if (arg->tag == caller_tag) {
			no(arg) = stack_add_res.astoff + stack_add_res.astadj;
		}

		arg = (arg->last ? NULL : bro(arg));
	}

	(* args_size) = stack;

	return use_push;
}

/*
 * PLACE_ARGUMENTS
 *
 * Encodes procedure arguments on the stack.
 */
static void
place_arguments(exp args, ash stack, long start)
{
	exp arg = args;
	ast stack_add_res;
	where stack_pointer;
	long adj;
	long st = start;

	/* Indicate recursive calls */
	apply_tag_flag ++;

	/* Encode the arguments onto the stack */
	while (arg != NULL) {
		exp formal = (arg->tag == caller_tag) ? son(arg) : arg;

		char nc = sh(formal)->tag;
		if (nc == scharhd || nc == ucharhd) {
			adj = 24;
		} else if (nc == swordhd || nc == uwordhd) {
			adj = 16;
		} else {
			adj = 0;
		}

		stack_pointer = mw(SP_p.wh_exp, st + adj);
		make_code(stack_pointer, stack, formal);
		stack_add_res = add_shape_to_stack(st, sh(formal));
		st = stack_add_res.astash;

		arg = (arg->last ? NULL : bro(arg));
	}

	apply_tag_flag --;
}

/*
 * PUSH A SET OF PROCEDURE ARGUMENTS
 *
 * The arguments are given by a bro-list t.
 * They are coded in reverse order.
 */
static void
push_args(where w, ash stack, exp args)
{
	long sz = shape_size(sh(args));
	exp formal;

	if (args->last) {
		/* Code last argument */
		formal = (args->tag == caller_tag) ? son(args) : args;
		make_code(w, stack, formal);
		stack_dec -= rounder(sz, param_align);
	} else {
		/* Code the following arguments */
		push_args(w, stack, bro(args));
		/* And then this one */
		formal = (args->tag == caller_tag) ? son(args) : args;
		make_code(w, stack, formal);
		stack_dec -= rounder(sz, param_align );
	}
}

/*
 * TAIL_CALL
 *
 * Code a tail call.
 */
void
tail_call(exp e, where dest, ash stack)
{
	exp proc;
	exp pcallees;
	exp callee_args;
	mach_op *op1, *op2;
	long new_callees_size;
	bool use_push;

	UNUSED(dest);

	proc        = son(e);
	pcallees    = bro(proc);
	callee_args = son(pcallees);
	use_push = 1;

	asm_comment("Tail Call");

	update_stack();

	if (pcallees->tag == make_dynamic_callee_tag) {
		/*
		 * A0 and A1 are used by cleanup. We are just about to make the tail
		 * call with shape bottom, so they are free
		 */
		push_dynamic_callees_bt(pcallees, stack);
		jmpins(proc);
		return;
	}

	/*
	 * Same callees?
	 */
	if (pcallees->tag == same_callees_tag) {
		restore_regs(ALL);

		if (! cur_proc_has_vcallees  && call_has_vcallees(pcallees)) {
			asm_comment("push size of same static callees and ret.addr. on the stack");
			op1 = make_indirect(REG_SP, 0);
			op2 = make_register(REG_D0);
			make_instr(m_movl, op1, op2, regmsk(REG_SP));

			op1 = make_callees_size();
			op2 = make_indirect(REG_SP, 0);
			make_instr(m_movl, op1, op2, regmsk(REG_SP));

			op1 = make_register(REG_D0);
			op2 = make_dec_sp();
			make_instr(m_movl, op1, op2, regmsk(REG_SP));
		} else if (cur_proc_has_vcallees  && ! call_has_vcallees(pcallees)) {
			asm_comment("remove size of same static callees from the stack");
			op1 = make_inc_sp();
			op2 = make_indirect(REG_SP, 0);
			make_instr(m_movl, op1, op2, regmsk(REG_SP));
		}
		jmpins(proc);
		return;
	}

	/*
	 * Nothing more than same calleers?
	 */
	if (!(callee_args || cur_proc_has_vcallees || call_has_vcallees(pcallees))) {
		restore_regs(ALL);
		jmpins(proc);
		return;
	}

	/*
	 * No callees?
	 */
	if (! callee_args) {
		asm_comment("save return address");
		op1 = make_indirect(REG_AP, 4);
		op2 = make_register(REG_A1);
		make_instr(m_movl, op1, op2, regmsk(REG_D0));

		cleanup_bt(0, 0);

		if (call_has_vcallees(pcallees)) {
			asm_comment("push zero size of callees on the stack");
			op1 = make_value(0);
			op2 = make_dec_sp();
			make_instr(m_movl, op1, op2, regmsk(REG_SP));
		}

		asm_comment("push return address back");
		op1 = make_register(REG_A1);
		op2 = make_dec_sp();
		make_instr(m_movl, op1, op2, regmsk(REG_SP));

		jmpins(proc);
		return;
	}

	/*
	 * New callees!
	 */

	if (! test_push_args(callee_args, &new_callees_size)) {
		use_push = 0;
	}

	if (use_push) {
		asm_comment("Push callees");
		push_args(zw(e), stack, callee_args);
	} else {
		/* Decrease stack */
		dec_stack(new_callees_size);
		stack_dec -= new_callees_size;
		place_arguments(callee_args, stack, 0);
	}

	if (call_has_vcallees(pcallees)) {
		asm_comment("push size of new callees on the stack");
		op1 = make_value(new_callees_size / 8);
		op2 = make_dec_sp();
		make_instr(m_movl, op1, op2, regmsk(REG_SP));
	}

	asm_comment("push return address");
	op1 = make_indirect(REG_AP, 4);
	op2 = make_dec_sp();
	make_instr(m_movl, op1, op2, regmsk(REG_SP));

	/*
	   Setup source, dest and end mark for push_range
	   We will use D1 & A0.
	   */

	asm_comment("save end of new callees and return address");
	op1 = make_register(REG_SP);
	op2 = make_register(REG_D1);
	make_instr(m_movl, op1, op2, regmsk(REG_D1));

	asm_comment("save start of new callees and return address");
	op1 = make_register(REG_SP);
	op2 = make_register(REG_A0);
	make_instr(m_movl, op1, op2, regmsk(REG_A0));

	/* add sizeof(new calless) sizeof(ret-addr) + ?+sizeof(callees size)? */
	op1 = make_value(new_callees_size / 8 + 4 + (call_has_vcallees(pcallees) ? 4 : 0));
	op2 = make_register(REG_A0);
	make_instr(m_addl, op1, op2, regmsk(REG_A0));

	cleanup_bt(0, 0);

	asm_comment("push the new callees");
	push_range(REG_A0, REG_D1);

	/* make the jump instruction */
	jmpins(proc);
}

/*
 * GENERAL PURPOSE PROCEDURE EPILOGUE
 *
 * The registers used in the procedure and the space used on the stack
 * are analysed and used to form the procedure epilogue.
 * There is some testing to see if D1, A0, A1 and FP1 can be put to
 * better use.
 */
static void
general_epilogue(bool uses_callers_pointer, bool has_checkstack)
{
	int r, instruction_id;
	bitpattern m;
	long st, st1;
	mach_op *op1, *op2;
	mach_ins * save_ins_pointer;

	int tmp_d1 = -1, tmp_a0 = -1, tmp_a1 = -1;

	bitpattern rmsk  = regs(regsinproc & save_msk);
	bitpattern smsk  = rmsk;
	bitpattern cmsk  = 0;
	bitpattern fmsk  = 0;
	bitpattern fsmsk = fregs(regsinproc & save_msk);
	bool d1_free;
	bool uses_link = 0;

	UNUSED(has_checkstack);

	asm_comment("Epilogue");

	/* restore the default floating point rounding mode */
	reset_round_mode();

	for (r = REG_FP7, m = 1; r >= REG_FP2; r--, m <<= 1) {
		if (regsinproc & regmsk(r)) {
			fmsk |= m;
		}
	}

	/* any calls? */
	if (no_calls > 0) {
		if (uses_callers_pointer) {
			/* Variable number of calles => A5 used as pointer to first caller */
			smsk &= ~regmsk(REG_A5);
		}

		smsk &= ~bigregs;
		fsmsk &= ~bigregs;
	}

	make_label(crt_ret_lab);

	if (diag != DIAG_NONE) {
		xdb_diag_proc_return();
	}

	d1_free = !(regsinproc & regmsk(REG_D1));

	/* Use D1 if not already used */
	if (d1_free) {
		m = smsk & dreg_msk ;     /* m = set of D'regs */
		if (m) {
			/* Replace a used D-register by D1 */
			r = reg(m);        /* get the first free register number in the set */
			reg_names[r] = reg_names[REG_D1];
			rmsk &= ~regmsk(r);
			smsk &= ~regmsk(r);
			cmsk |= regmsk(r);
			d1_free = 0;
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
	if (fsmsk && !(regsinproc & regmsk(REG_FP1))) {
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

	/* Calculate stack displacements */
	st1 = round(max_stack, 32) / 8 + 16 * bits_in(fmsk);
	st = st1 + 4 * bits_in(rmsk);

	if (st1 || st || used_stack || must_use_bp || cur_proc_has_vcallees) {
		uses_link = 1;
	}

	cleanup();

	/* Output return instruction */
	make_instr(m_rts, NULL, NULL, 0);

	/* Output instructions to restore registers */
	save_ins_pointer = current_ins;
	restore_regs_output(rmsk, fmsk, st, st1, uses_link);

	/* Go back to the prologue position */
	current_ins = prologue_ins;

	/* Calculate the offset between procedure args and sp */
	ldisp = (uses_link ? st + 4 : st);

	/* Calculate env_size(ldisp + sizeof(return address) + sizeof(params))*/
	cur_proc_env_size = ldisp + 4 + (cur_proc_callers_size + cur_proc_callees_size) / 8;
#if 0
	if (has_checkstack) {
		cur_proc_env_size += 1024 ;    /* room for exception handler */
	}
#endif

	if (uses_link) {
		/* Output link instruction */
		/* push AP; AP = SP; sp=sp-st */
		instruction_id = (-st > 0x7fff ? m_linkl : m_linkw);
		op1 = make_register(REG_AP);
		op2 = make_value(-st);
		make_instr(instruction_id, op1, op2, regmsk(REG_AP) | regmsk(REG_SP));
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
		op1 = make_hex_value(rmsk);
		op2 = make_indirect(REG_SP, 0);
		make_instr(m_moveml, op1, op2, 0);
	}

	/* Put floating-point registers onto the stack */
	if (fmsk) {
		op1 = make_hex_value(fmsk);
		op2 = make_indirect(REG_AP, -st1);
		make_instr(m_fmovemx, op1, op2, 0);
	}

	if (uses_callers_pointer) {
		asm_comment("Variable callees => Get address of first caller");

		regsinproc |= regmsk(REG_A5);

		op1 = make_register(REG_AP);
		op2 = make_register(REG_A5);
		make_instr(m_movl, op1, op2, regmsk(REG_A5));

		/* A5 = AP + cur_proc_callees_size */
		/* AP points to the first parameter, callees size is before */
		op1 = make_callees_size();
		op2 = make_register(REG_A5);
		make_instr(m_addl, op1, op2, regmsk(REG_A5));

		op1 = make_value(12);
		op2 = make_register(REG_A5);
		make_instr(m_addl, op1, op2, regmsk(REG_A5));
	}


	/* Return to previous position */
	current_ins = save_ins_pointer;

	callmsk = cmsk;
	have_cond = 0;
}

/*
 * CODE_POSTLUDE
 *
 * The postlude parameters positions on the stack are setup,
 * and make_code is called with the postlude body.
 */
static void
code_postlude(exp postlude, exp callers, ash stack, long post_offset)
{
	asm_comment("Postlude ...");

	/* mark parameters by use of the values calculated by gcproc */
	while (postlude->tag == ident_tag && son(postlude)->tag == caller_name_tag) {
		int n = no(son(postlude));
		exp a = callers;
		while (n != 0) {
			a = bro(a);
			n--;
		}
		if (a->tag != caller_tag) {
			error(ERR_SERIOUS, "Bad postlude");
		}

		ptno(postlude) = par3_pl;
		no(postlude) = no(a) + stack_dec + post_offset;

		postlude = bro(son(postlude));
	}

	/* code the postlude */
	make_code(zero, stack, postlude);

	asm_comment("Postlude done");
}

/*
 * Makes code for untidy return
 */
void
untidy_return(void)
{
	mach_op *op1, *op2;

	asm_comment("untidy return");

	asm_comment("push return address");
	op1 = make_indirect(REG_AP, 4);
	op2 = make_dec_sp();
	make_instr(m_movl, op1, op2, regmsk(REG_SP));

	restore_regs(NOT_SP);
	/* Output return instruction */
	make_instr(m_rts, NULL, NULL, 0);
}

/*
 * Make a label with named after the address of e and the value of the
 * env offset from e (an ident_tag) to the application pointer.
 */
void
make_visible(exp e)
{
	mach_op *op1, *op2;
	long offval;

	/* Does it need to be visible? */

	if (!((isvis(e)) || (isenvoff(e)))) {
		return;
	}

	setismarked(e);

	switch (ptno(e)) {
	case var_pl:  offval = -no(e) / 8; break;
	case par2_pl: offval =  no(e) / 8; break;

	case par3_pl:
	case par_pl:
	default:
		offval = no(e) / 8 + 4;
		if (used_stack) {
			offval += 4;
		}
	}

	op1 = make_lab_data((long)e, 0);
	op2 = make_int_data(offval);

	make_instr_aux(m_as_assign, op1, op2, 0, 0);
}

/*
 * If a caller parameter is accessed from a framepointer with variable
 * callees we need to transform the pointer in the addptr expression to
 * callers pointer.
 */
static void
fix_addptr(exp addptr)
{
	exp pointer  = son(addptr);
	exp offset   = bro(pointer);
	exp E1, E2, E3, E4, E5;
	shape pc_sh;

	/* access of a caller param. relative to an environment with variable? */

	if (!((frame_al_of_ptr(sh(pointer)) & al_includes_vcallees) &&
	      (frame_al1_of_offset(sh(offset)) & al_includes_caller_args))) {
		return;
	}

	/*
	 * exchange application pointer with callers pointer:
	 *
	 * addptr(pointer, offset) --> addptr(pointer2, offset)
	 * where pointer2 = reff(addptr(pointer, cont(reff(pointer, 8*8))), 12*8)
	 *
	 *
	 *                addptr
	 *                  |
	 *                  |(son)   bro(son)
	 *                  |-------------|
	 *            E5  reff(8*8)     offset
	 *                  |(son)
	 *                  |
	 *            E4  addptr
	 *                  |(son)   bro(son)
	 *                  |----------|
	 *               pointer  E3  cont
	 *                             |(son)
	 *                             |
	 *                        E2  reff(12*8)
	 *                             |(son)
	 *                             |
	 *                        E1  pointer (copy)
	 *
	 */

	pc_sh = f_pointer(f_callers_alignment(0));

	E1 = copyexp(pointer);
	E2 = getexp(pc_sh, 0, 0, E1, 0, 0, 8 * 8, reff_tag);
	E3 = getexp(pc_sh, 0, 0, E2, 0, 0, 0, cont_tag);
	E4 = getexp(pc_sh, 0, 0, pointer, 0, 0, 0, addptr_tag);
	E5 = getexp(pc_sh, 0, 0, E4, 0, 0, 12 * 8, reff_tag);
	son(addptr) = E5;

	/* Terminate each bro list */
	setfather(E2, E1);
	setfather(E3, E2);
	setfather(E4, E3);
	setfather(E5, E4);

	bro(pointer) = E3;
	bro(E5) = offset;
}

/*
 * Transforms an entire exp recursively.
 */
static void
transform(exp e)
{
	exp s = son(e);

	/* Transform the childs (if any) */
	if (s && (e->tag != name_tag) && (e->tag != env_offset_tag) && (e->tag != case_tag))
		for (; s && s != e; s = bro(s)) {
			transform(s);
		}

	/* Transform this one */
	switch (e->tag) {
	case addptr_tag:
		fix_addptr(e);
		break;

	default:
		/* nothing to do */
		break;
	}
}

/*
 * Scan through the declarations and apply transform
 * called from trans.
 */
void
make_transformations(void)
{
	dec *d;

	for (d = top_def; d != NULL; d = d->next) {
		exp e = son(d->dec_exp);
		if (e) {
			transform(e);
		}
	}
}

/*
 * Make a label with:
 * value: env_size(proc)
 * name:  L<value of procedure declaration pointer)
 */
void
output_env_size(dec* proc, long envsize)
{
	mach_op *op1, *op2;

	asm_comment("env_size comes here:");
	op1 = make_lab_data((long)proc, 0);
	op2 = make_int_data(envsize);
	make_instr_aux(m_as_assign, op1, op2, 0, 0);
}

