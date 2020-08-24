/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <shared/bool.h>
#include <shared/error.h>

#include <local/ash.h>
#include <local/out.h>
#include <local/code.h>

#ifdef DWARF2
#include <local/dw2_config.h>
#endif

#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/externs.h>
#include <reader/readglob.h>
#include <reader/basicread.h>

#include <construct/installglob.h>
#include <construct/exp.h>
#include <construct/machine.h>

#include <flpt/flpt.h>

#include <main/driver.h>
#include <main/flags.h>
#include <main/print.h>

#ifdef TDF_DIAG3
#include <diag3/diag_fns.h>
#include <diag3/diag_reform.h>
#endif
#ifdef TDF_DIAG4
#include <diag4/diag_fns.h>
#include <diag4/diag_reform.h>
#endif

#include <refactor/optimise.h>

#include "localtypes.h"
#include "make_code.h"
#include "instr.h"
#include "scan.h"
#include "weights.h"
#include "ops.h"
#include "operand.h"
#include "assembler.h"
#include "cproc.h"
#include "eval.h"
#include "tv_callees.h"

#ifdef DWARF2
#include <dwarf2/dw2_iface.h>
#include <dwarf2/dw2_abbrev.h>
#include <dwarf2/dw2_common.h>
#endif

/* XXX: just here until this finds a home in a header */
#ifdef TDF_DIAG3
void init_stab_aux(void);
#endif

#define ptg(x) ((x)->pt.glob) /* addition to expmacs */

static exp delayed_const_list = NULL;

static int
const_ready(exp e)
{
	unsigned char n = e->tag;

	if (n == env_size_tag) {
		return nextg(child(child(e)))->processed;
	}

	if (n == env_offset_tag) {
		return child(e)->tag == 0;
	}

	if (n == name_tag || child(e) == NULL) {
		return 1;
	}

	for (e = child(e); !e->last; e = next(e)) {
		if (!const_ready(e)) {
			return 0;
		}
	}

	return const_ready(e);
}

static void
eval_if_ready(exp t, int now)
{
	if (!now && !const_ready(child(t))) {
		next(t) = delayed_const_list;
		delayed_const_list = t;

		return;
	}

	if (!isglob(t)) {
		if (!writable_strings && child(t)->tag != res_tag) {
			out_readonly_section();
			asm_printf("\n");
		} else {
			if (do_prom) {
				error(ERR_INTERNAL, "prom data");
			}
			asm_printf(".data\n");
		}

		evaluate(child(t), no(t), NULL, (child(t)->tag != res_tag), 0, NULL);
	} else {
		dec *d = ptg(t);

		if (!writable_strings &&
			(!isvar(t) || (d->acc & f_constant)) &&
			!PIC_code) {
			out_readonly_section();
			asm_printf("\n");
#ifdef DWARF2
			if (diag == DIAG_DWARF2) {
				note_ro(d->name);
			}
#endif
		} else {
			if (do_prom) {
				error(ERR_INTERNAL, "prom data");
			}
			asm_printf(".data\n");
#ifdef DWARF2
			if (diag == DIAG_DWARF2) {
				note_data(d->name);
			}
#endif
		}

		evaluate(child(t), -1, d->name, !isvar(t), (int) d->extnamed
#ifdef TDF_DIAG3
			 , d->diag_info
#endif
#ifdef TDF_DIAG4
			 , d->dg_name
#endif
			);
	}

	retcell(t);
}

static void
code_def(dec *d)
{
	exp tag  = d->exp;
	char *name = d->name;

	if (child(tag) != NULL && shape_size(sh(child(tag))) == 0 && child(tag)->tag == asm_tag) {
		ash stack;
		stack.ashsize = stack.ashalign = 0;

		if (child(tag)->props != 0) {
			error(ERR_INTERNAL, "~asm not in ~asm_sequence");
		}

		check_asm_seq(child(child(tag)), 1);
		asm_printf(".text\n");
		make_code(zero, stack, child(tag));
		asm_printf("\n");
	}

	if (child(tag) != NULL && (d->extnamed || no(tag) != 0)) {
		if (child(tag)->tag == proc_tag || child(tag)->tag == general_proc_tag) {
			if (dyn_init && strncmp("__I.TDF", name + strlen(name_prefix), 7) == 0) {
				out_initialiser(name);
				set_proc_uses_external (child (tag));	/* for PIC_code, should be done in install_fns? */
			}

			asm_printf(".text\n");
			if (isvar(tag)) {
				char *new = make_local_name();
				if (d->extnamed) {
					d->extnamed = 0;
					asm_printf(".globl %s\n", name);
				}

				dot_align(4);
				asm_label("%s", name);
				asm_printf(".long %s\n", new);
				name = new;
				d->extnamed = 0;
			}

			/* for use in constant evaluation */
			d->index = cproc(child(tag), name, -1, (int) d->extnamed
#ifdef TDF_DIAG3
		          , d->diag_info
#endif
#ifdef TDF_DIAG4
		          , d->dg_name
#endif
		         );

			while (const_list != NULL) {
				/* put in the constants required by the procedure */
				exp t = const_list;
				const_list = next(const_list);
				eval_if_ready(t, 0);
			}
		} else {
			/* global values */
#ifdef TDF_DIAG3
			diag_descriptor * diag_props = d->diag_info;
#endif
#ifdef TDF_DIAG4
			struct dg_name_t * diag_props = d->dg_name;
#endif

			if (shape_size(sh(child(tag))) == 0) {
				if (d->extnamed) {
					asm_printf(".globl %s\n", name);
				} else if (assembler == ASM_SUN) {
					asm_printf(".local %s\n", name);
				} else if (assembler == ASM_GAS) {
					asm_printf(".data\n");
					asm_printf("%s:\n", name);
				} else {
					asm_printf(".set %s, 0\n", name);
				}
			} else if (!PIC_code && !isvar(tag) && child(tag)->tag == null_tag &&
			           sh(child(tag))->tag == prokhd) {
				if (d->extnamed) {
					asm_printf(".globl %s\n", name);
				} else if (assembler == ASM_SUN) {
					asm_printf(".local %s\n", name);
				}
				asm_printf(".set %s, %ld\n", name, (long) no(child(tag)));
			} else {
				if (!d->isweak && is_comm(child(tag))) {
					int is_ext = d->extnamed;

					if (diag_props && diag != DIAG_NONE) {
#ifdef TDF_DIAG3
						diag3_driver->diag_val_begin(diag_props, is_ext, -1, name);
#endif
#ifdef TDF_DIAG4
						diag4_driver->out_diag_global(diag_props, is_ext, -1, name);
#endif
					}

					if (child(tag)->tag == clear_tag && no(child(tag)) == -1) {
						/* prom global data */
						if (is_ext) {
							asm_printf(".globl %s\n", name);
						}

						out_dot_lcomm(name, sh(child(tag)));

#ifdef DWARF2
						if (diag == DIAG_DWARF2) {
							note_data(name);
						}
#endif
					} else if (is_ext) {
						out_dot_comm(name, sh(child(tag)));
					} else {
						out_dot_lcomm(name, sh(child(tag)));
					}

					if (diag_props) {
#ifdef TDF_DIAG3
						diag3_driver->diag_val_end(diag_props);
#endif
					}
				} else {
					/* global values */
					exp t = getexp(f_bottom, NULL, 0, child(tag), NULL, tag->props, -1, 0);
					ptg(t) = d;
					eval_if_ready(t, 0);
				}
			}
		}
	}

	if (child(tag) != NULL) {
		d->processed = 1;
	}
}

static void
mark_unaliased(exp e)
{
	int ca = 1;
	exp p;

	for (p = pt(e); p != NULL && ca; p = pt(p)) {
#ifdef TDF_DIAG4
		if ((next(p) == NULL ||
#else
		if (next(p) == NULL ||
#endif
		     (!(p->last && next(p)->tag == cont_tag) &&
		     !(!p->last && next(p)->last &&
		        next(next(p))->tag == ass_tag)))
#ifdef TDF_DIAG4
		    && !isdiaginfo(p))
#endif
			ca = 0;
	}

	if (ca) {
		setcaonly(e);
	}
}

void
local_translate_capsule(void)
{
	dec *d;

#ifdef TDF_DIAG3
	if (diag == DIAG_STABS) {
		init_stab_aux();
	}
#endif

	for (d = top_def; d != NULL; d = d->next) {
		exp crt_exp = d->exp;

		if (PIC_code) {
			exp idval = child(crt_exp);
			if (!d->var &&
			    (idval == NULL || (idval->tag != val_tag && idval->tag != real_tag &&
			                       idval->tag != null_tag) /* optimised out in opt_all_exps/refactor_ext */
			    ) &&
			    (sh(crt_exp)->tag != prokhd ||
			     (idval != NULL && idval->tag != null_tag &&
			      idval->tag != proc_tag && idval->tag != general_proc_tag)))
			{
				/* make variable, and change all uses to contents */
				exp p, np;

				if (d->extnamed) {
					sh(crt_exp) = f_pointer(f_alignment(sh(crt_exp)));
				} else {
					setvar(crt_exp);
				}

				for (p = pt(crt_exp); p != NULL; p = np) {
					exp *ptr;
					exp c;

					np = pt(p);
					ptr = refto(father(p), p);
					c = getexp(sh(p), next(p), p->last, p, NULL, 0, 0, cont_tag);
					setfather(c, p);

					if (no(p) != 0) {
						exp r = getexp(sh(p), c, 1, p, NULL, 0, no(p), reff_tag);
						no(p) = 0;
						child(c) = r;
						setfather(r, p);
					}

					*ptr = c;
				}
			}
		} else {
			/* !PIC_code; make indirect global idents direct */
			exp tag = crt_exp;
			while (!isvar(tag) && child(tag) != NULL && child(tag)->tag == name_tag && no(child(tag)) == 0) {
				tag = child(child(tag));
			}

			if (tag != crt_exp) {
				exp p, np;

				for (p = pt(crt_exp); p != NULL; p = np) {
					np = pt(p);
					if (child(p) != crt_exp) {
						error(ERR_INTERNAL, "not simple name");
					}

					child(p) = tag;
					pt(p) = pt(tag);
					pt(tag) = p;
					++no(tag);
				}

				pt(crt_exp) = NULL;
				no(crt_exp) = 0;
			}
		}
	}

	opt_all_exps();

	transform_var_callees();

	/* mark static unaliased */
	for (d = top_def; d != NULL; d = d->next) {
		exp crt_exp;

		crt_exp = d->exp;
		if (child(crt_exp) != NULL && !d->extnamed && isvar(crt_exp)) {
			mark_unaliased(crt_exp);
		}
	}

	extra_stack = 0;
	init_weights();
	initzeros();
	const_list = NULL;

	if (diag != DIAG_NONE) {
#ifdef DWARF2
		init_dwarf2();
#endif
#ifdef TDF_DIAG3
		diag3_driver->out_diagnose_prelude();
#endif
	}

#ifdef DWARF2
	if (diag == DIAG_DWARF2) {
		asm_printf(".text\n");
		if (dump_abbrev) {
			do_abbreviations();
		}

		dwarf2_prelude();
		make_dwarf_common();
		dwarf2_postlude();
	}
#endif

	/*
	 * compile procedures, evaluate constants, put in the .comm entries
	 * for undefined objects
	 */

	for (d = top_def; d != NULL; d = d->next) {
		if (!d->processed) {
			code_def(d);
		}
	}

	while (delayed_const_list != NULL) {
		exp t = delayed_const_list;
		delayed_const_list = next(delayed_const_list);
		eval_if_ready(t, 1);
	}

	asm_printf(".text\n");

#ifdef DWARF2
	if (diag == DIAG_DWARF2) {
		dwarf2_postlude();
	}
#endif
}

