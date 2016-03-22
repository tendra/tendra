/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/xalloc.h>

#include <local/exp.h>
#include <local/szs_als.h>

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>

#include <construct/exp.h>
#include <construct/installglob.h>
#include <construct/machine.h>

#include <utility/bits.h>
#include <utility/imath.h>

#include <main/driver.h>
#include <main/flags.h>

#include <refactor/optimise.h>

#include <diag3/diag_reform.h>

#include "instrs.h"
#include "eval.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "weights.h"
#include "mach.h"
#include "where.h"
#include "codex.h"
#include "output.h"
#include "tests.h"
#include "xdb_basics.h"
#include "assembler.h"

extern dec *sort_decs(dec *);
static void output_all_exps(void);

#ifndef tdf3
#include "general_proc.h"
#include "68k_globals.h"
bool need_dummy_double = false;
#endif

/*
 * EXTERNAL POSITIONS
 */
static long crt_ext_off = 64;
static long crt_ext_pt  = 10;

/*
 * MARK AN EXPRESSION AS BEING STATIC AND UNALIASED
 */
static void
mark_unaliased(exp e)
{
	exp p;
	bool ca = 1;

	for (p = pt(e); p != NULL && ca; p = pt(p)) {
		exp q = bro(p);

		if (q == NULL) {
			ca = 0;
		} else if (!(p->last && q->tag == cont_tag) &&
		          !(!p->last && q->last && bro(q)->tag == ass_tag)) {
			ca = 0;
		}
	}

	if (ca) {
		setcaonly(e);
	}
}

/*
 * This routine gets all the TDF read into the correct operand form
 * and applies the dead variable and register allocation analysis.
 */
void
local_translate_capsule(void)
{
	dec *d;

#if 0
	/* Fix procedure handling (copied from trans386) */
	for (d = top_def; d != NULL; d = d->next) {
		exp crt_exp = d->exp;
		exp idval;

		if (d->var) {
			continue;
		}

		if ((sh(crt_exp)->tag != prokhd || (idval = son(crt_exp),
			 idval != NULL && idval->tag != null_tag &&
			 idval->tag != proc_tag && idval->tag != general_proc_tag)))
		{
			exp p, np;

			/* make variable, and change all uses to contents */

			if (d->extnamed) {
				sh(crt_exp) = f_pointer(f_alignment(sh(crt_exp)));
			} else {
				setvar(crt_exp);
			}

			for (p = pt(crt_exp; p != NULL; p = np) {
				exp *ptr;
				exp c;

				np = pt(p);
				ptr = refto(father(p), p);
				c = getexp(sh(p), bro(p), p->last, p, NULL, 0, 0, cont_tag);

				setfather(c, p);

				if (no(p) != 0) {
					exp r = getexp(sh(p), c, 1, p, NULL, 0, no(p), reff_tag);
					no(p) = 0;
					son(c) = r;
					setfather(r, p);
				}

				*ptr = c;
			}
		}
	}
#endif

	make_transformations();

#ifndef NDEBUG
	opt_all_exps();
#endif

	/* Mark static unaliases declarations */
	if (!separate_units) {
		for (d = top_def; d != NULL; d = d->next) {
			exp c = d->exp;
			if (son(c) != NULL && !d->extnamed && isvar(c)) {
				mark_unaliased(c);
			}
		}
	}

	/* Mark locations for all globals */
	for (d = top_def; d != NULL; d = d->next) {
		if (d->processed) {
			exp c = d->exp;
			ptno(c) = crt_ext_pt++;
			no(c) = crt_ext_off;
			crt_ext_off += shape_size(d->shape);
		}
	}

	/* Set up alignment rules */
	double_align = DBL_ALIGN;
	param_align  = PARAM_ALIGN;
	stack_align  = STACK_ALIGN;

	diagnose_registers = false;

	MAX_BF_SIZE = (cconv != CCONV_HP ? MAX_BF_SIZE_CC : MAX_BF_SIZE_GCC);

	/* Call initialization routines */
	init_instructions();
	init_weights();
	init_wheres();

	/* Decode, optimize and process the input TDF */
	init_output();
	area(ptext);

	if (diag != DIAG_NONE) {
		diag3_driver->out_diagnose_prelude();
	}

	/* Output all code */
	output_all_exps();
}

/*
 * The procedure with declaration d, name, definition c and body s
 * is encoded.
 */
static void
code_proc(dec *d, char *name, exp c, exp s)
{
	diag_descriptor *di;
	int reg_res;
	int is_ext;

	UNUSED(c);

	di = d->diag_info;
	reg_res = (has_struct_res(s) ? 0 : 1);
	is_ext = (d->extnamed ? 1 : 0);

	area(ptext);

	cur_proc_dec = d;
	cur_proc_callees_size = 0;
	cur_proc_has_vcallees = false;

	/* Code procedure body */
#if 0
	if (s->tag == proc_tag) {
		cproc(s, name, -1, is_ext, reg_res, di);
	} else
#endif
		gcproc(s, name, -1, is_ext, reg_res, di);

	d->index = cur_proc_env_size; /* for use in constant evaluation */

	output_env_size(d, cur_proc_env_size);
}

/*
 * The constant with declaration d, definition c and body s
 * is encoded.
 */
static void
code_const(dec *d)
{
	diag_descriptor *di;
	exp c, s;
	char *name;

	c = d->exp;
	s = son(c);
	name = d->name;
	di = d->diag_info;

	area(isvar(c) ? pdata : ptext);
	if (!no_align_directives) {
		make_instr(m_as_align4, NULL, NULL, 0);
	}

	evaluate(s, -1L , name, !isvar(c), 1, di);
}

/*
 * ENCODE THE CONSTANTS IN const_list
 *
 * All auxiliary constants are formed into a list, const_list.  This
 * routine applies evaluate to each element of this list.
 */
static void
code_const_list(void)
{
	while (const_list != NULL) {
		exp t, s;
		bool b;

		t = const_list;
		s = son(t);
		b = (s->tag != res_tag);
		const_list = bro(const_list);

		if (s->tag == proc_tag || s->tag == general_proc_tag) {
			char *name = xmalloc(30);
			sprintf(name, "%s%ld", local_prefix, no(t));
			gcproc(s, NULL, no(t), 0, 1, NULL);
		} else {
			area(b ? pdata : ptext);
			evaluate(s, no(t), NULL, b, 0, NULL);
		}
	}
}

/*
 * CONST_READY
 *
 * Returns TRUE if it is possible to evaluate the value of the constant now
 */
static int
const_ready(exp e)
{
	unsigned char n = e->tag;

	if (n == env_size_tag) {
		return brog(son(son(e)))->processed;
	}

	if (n == env_offset_tag) {
		return ismarked(son(e));
	}

	if (n == name_tag || son(e) == NULL) {
		return 1;
	}

	for (e = son(e); !e->last; e = bro(e)) {
		if (!const_ready(e)) {
			return 0;
		}
	}

	return const_ready(e);
}

typedef struct delayedconst {
	dec* This;
	struct delayedconst* next;
} delayed_const;

static delayed_const *delayed_const_list = 0;

static void
eval_if_ready(dec *d)
{
	exp c = d->exp;

	if (const_ready(c)) {
		code_const(d);
	} else {
		delayed_const *p = xmalloc(sizeof(delayed_const));
		p->This = d;
		p->next = delayed_const_list;
		delayed_const_list = p;
	}
}

static void
eval_delayed_const_list(void)
{
	delayed_const *p;
	bool done = false;

	while (!done) {
		for (p = delayed_const_list; p != NULL; p = p->next) {
			dec *d;
			exp c;

			d = p->This;
			if (d->processed) {
				continue;
			}


			c = d->exp;
			if (const_ready(c)) {
				code_const(d);
				d->processed = 1;
			}

			done = false;
		}
	}
}

/*
 * This routine scans through all the declarations encoding suitably.
 */
static void
output_all_exps(void)
{
	dec *d = top_def;

	if (diag != DIAG_NONE) {
		d = sort_decs(d);
	}

	area(ptext);

	/* Clear any existing output */
	output_all();
	free_all_ins();

	/* Scan through the declarations */
	for (d = top_def; d != NULL; d = d->next) {
		exp c, s;
		char *name;

		if (d->processed) {
			continue;
		}

		c = d->exp;
		s = son(c);
		name = d->name;

		init_output();

		if (s != NULL) {
			if (s->tag == proc_tag || s->tag == general_proc_tag) {
				code_proc(d, name, c, s);
				code_const_list();
				d->processed = 1;
			} else {
				eval_if_ready(d);
				code_const_list();
			}
		} else {
			shape sha = d->shape;
			long sz = iround(shape_size(sha) / 8, 4);

			area(ptext);
			if (!is_local(name) && isvar(c) && varsize(sha) && !reserved(name)) {
				if (sz) {
					mach_op *op1 = make_extern_data(name, 0);
					mach_op *op2 = make_int_data(sz);
					make_instr(m_as_common, op1, op2, 0);
				}
			} else {
				if (is_local(name) && no(c)) {
					mach_op *op1 = make_extern_data(name, 0);
					mach_op *op2 = make_int_data(sz);
					make_instr(m_as_local, op1, op2, 0);
				}
			}

			d->processed = 1;
		}

		output_all();
		free_all_ins();
	}

	eval_delayed_const_list();
	output_all();
	free_all_ins();

	/* Add final touches */
	init_output();
	if (need_dummy_double) {
		mach_op *op1 = make_extern_data("___m68k_dummy_double", 0);
		mach_op *op2 = make_int_data(8);
		make_instr(m_as_common, op1, op2, 0);
	}

	if (do_profile) {
		profile_hack();
	}

	area(pdata);
	output_all();

	free_all_ins();
}

