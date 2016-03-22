/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>
#include <stdio.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/string.h>
#include <shared/xalloc.h>

#include <local/ash.h>

#include <tdf/nat.h>
#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/basicread.h>

#include <symtab/symconst.h>
#include <symtab/syms.h>
#include <symtab/symtab.h>
#include <symtab/new_symbol.h>

#include <construct/installglob.h>
#include <construct/exp.h>
#include <construct/me_fns.h>

#include <main/driver.h>
#include <main/flags.h>
#include <main/print.h>

#include <diag3/diag_reform.h>

#include <refactor/optimise.h>

#include "procrec.h"
#include "tempdecs.h"
#include "weights.h"
#include "regalloc.h"
#include "make_code.h"
#include "code_here.h"
#include "eval.h"
#include "bits.h"
#include "scan.h"
#include "ibinasm.h"
#include "out_ba.h"
#include "stabs_diag3.h"
#include "extern_adds.h"
#include "mips_ins.h"
#include "main.h"
#include "frames.h"
#include "getregs.h"
#include "locate.h"

extern long aritherr_lab;
extern long stackerr_lab;


extern exp find_named_tag(char*, shape);
extern shape f_top;
extern shape f_proc;

procrec * procrecs;
dec ** main_globals;
static int main_globals_index;

extern long fscopefile;
extern bool do_extern_adds;

/* various identifier reserved by MIPS */
static bool
not_reserved(char *name)
{
	if (streq(name, "edata"))  return false;
	if (streq(name, "etext"))  return false;
	if (streq(name, "end"))    return false;
	if (streq(name, "_ftext")) return false;
	if (streq(name, "_fdata")) return false;
	if (streq(name, "_fbss"))  return false;
	if (streq(name, "_gp"))    return false;

	if (streq(name, "_procedure_table"))        return false;
	if (streq(name, "_procedure_string_table")) return false;

	return true;
}

static char
varsize(shape sha)
{
	return sha->tag == nofhd;
}

int current_symno;

void
globalise_name(dec *d)
{
	char *name;

	name = d->name;
	if (!d->extnamed) {
		return;
	}

	if (as_file) {
		asm_printop(".globl %s", name);
	}

	out_common(symnos[d->sym_number], iglobal);
}

static void
code_it(dec *d)
{
	exp tag;
	char *name;
	long symdef;
	bool extnamed;

	static space tempspace = { 0, 0 };

	tag      = d->exp;
	name     = d->name;
	symdef   = d->sym_number;
	extnamed = d->extnamed;

	if (symnos[symdef] < 0) {
		goto end; /* ? unused symbols */
	}

	if (son(tag) != NULL && (!extnamed || !is_comm(son(tag)))) {
		if (son(tag)->tag == proc_tag || son(tag)->tag == general_proc_tag) {
			diag_descriptor *dd = d->diag_info;

			/* compile code for proc */
			if (as_file) {
				asm_printop(".text\n .align 3");
			}


			out_common(0, itext);
			out_value(0, ialign, 3, 0);
			if (diag != DIAG_NONE) {
				if (dd != NULL) {
					sourcemark *sm = &dd->data.id.whence;
					diag3_driver->stabd(fscopefile = find_file(sm->file->file.ints.chars),
					                    sm->line_no.nat_val.small_nat, 0);
				} else {
					diag3_driver->stabd(0, 1, 0); /*no diagnostics for this proc */
				}
			}

			globalise_name(d);

			if (as_file) {
				asm_printop(".ent %s\n%s:", name, name);
			}

			out_ent (current_symno = symnos[symdef], ient, 2);/* why 2? */
			out_common(symnos[symdef], ilabel);

			if (as_file) {
				asm_printop(diag != DIAG_NONE ? ".option O1" : ".option O2");
			}

			out_option(1, (diag != DIAG_NONE) ? 1 : 2);

			symnoforstart(symdef, currentfile);
			settempregs(son(tag));
			code_here(son(tag), tempspace, nowhere);

			if (diag != DIAG_NONE && dd != NULL) {
				diag3_driver->stabd(fscopefile, currentlno + 1, 0);
			}

			if (as_file) {
				asm_printop(".end %s", name);
			}
			out_common(symnoforend(d, currentfile), iend);
		} else {			/* global values */
			exp c = son(tag);
			IGNORE evaluated(c, (isvar(tag)) ? (-symdef - 1) : symdef + 1, d);
		}
	} else {
		/* global declarations but no definitions or is_comm */
		long  size;
		shape s = (son(tag) == NULL) ? d->shape : sh(son(tag));
		size = (shape_size(s) + 7) >> 3;

		if ((isvar(tag) || s->tag != prokhd) && not_reserved(name)) {
			if ((son(tag) != NULL && is_comm(son(tag)))
			    || (son(tag) == NULL && varsize(sh(tag))))
			{
				if (size != 0) { /* ? ? ! ? */
					globalise_name(d);
					if (as_file) {
						asm_printop(".comm %s %ld", name, size);
					}

					out_value(symnos[symdef], icomm, size, 1);
				}
			} else {
				if (as_file) {
					asm_printop(".extern %s %ld", name, size);
				}

				out_value(symnos[symdef], iextern, size, 1);
			}
		} else if (son(tag) == NULL && !extnamed) {
			if (size != 0) { /* ? ? ! ? */
				if (as_file) {
					asm_printop(".lcomm %s %ld", name, size);
				}

				out_value(symnos[symdef], ilcomm, size, 1);
			}
		}
	}

end:

	d->processed = 1;
}

static void
mark_unaliased(exp e)
{
	exp p;

	bool ca = 1;

	for (p = pt(e); p != NULL && ca; p = pt(p)) {
		if (bro(p) == NULL ||
		    (!(p->last && bro(p)->tag == cont_tag) &&
		     !(!p->last && bro(p)->last && bro(bro(p))->tag == ass_tag))) {
			ca = 0;
		}
	}

	if (ca) {
		setcaonly(e);
	}
}

static void
remove_unused(void)
{
	dec **sdef = &top_def;
	while (*sdef != NULL) {
		exp crt_exp = (*sdef)->exp;
		bool extnamed = (*sdef)->extnamed;

		if (no(crt_exp) == 0 && !extnamed) {
			*sdef = (*sdef)->next;
		} else {
			sdef = &((*sdef)->next);
		}
	}
}

void
local_translate_capsule(void)
{
	dec *d;
	int noprocs;
	int i;

	opt_all_exps();
	remove_unused();

	if (dyn_init) {
		for (d = top_def; d != NULL; d = d->next) {
			exp crt_exp = d->exp;
			char *name  = d->name;

			if (streq(name, "main") && son(crt_exp) != NULL &&
			    son(crt_exp)->tag == proc_tag) {
				exp fn = me_obtain(find_named_tag("__DO_I_TDF", f_proc));
				exp cll = getexp(f_top, NULL, 0, fn, NULL, 0, 0, apply_tag);
				exp * dm = &son(son(crt_exp));
				exp hld, seq;
				bro(fn) = cll;
				fn->last = true;

				while ((*dm)->tag == ident_tag && isparam(*dm)) {
					dm = &bro(son(*dm));
				}
				/* dm is body of main after params */

				hld = getexp(f_top, *dm, 0, cll, NULL, 0, 1, 0);
				seq = getexp(sh(*dm), bro(*dm), (*dm)->last, hld, NULL, 0, 0, seq_tag);
				bro(*dm) = seq;
				(*dm)->last = true;
				bro(cll) = hld;
				cll->last = true;
				*dm = seq;
				break;
			}
		}
	}

	/* mark static unaliased */
	for (d = top_def; d != NULL; d = d->next) {
		exp crt_exp = d->exp;

		if (son(crt_exp) != NULL &&
		    !d->extnamed &&
		    isvar(crt_exp)) {
			mark_unaliased(crt_exp);
		}
	}

	noprocs = 0;
	for (d = top_def; d != NULL; d = d->next) {
		exp crt_exp = d->exp;

		if (son(crt_exp) != NULL
		    && (son(crt_exp)->tag == proc_tag ||
		        son(crt_exp)->tag == general_proc_tag)) {
			noprocs++;
		}
	}

	/* count procs */
	if (noprocs == 0) {
		procrecs = NULL;
	} else {
		procrecs = xcalloc(noprocs, sizeof(procrec));
		noprocs = 0;
	}

	for (d = top_def; d != NULL; d = d->next) {
		exp crt_exp = d->exp;

		if (son(crt_exp) != NULL &&
		    (son(crt_exp)->tag == proc_tag || son(crt_exp)->tag == general_proc_tag)) {
			no(son(crt_exp)) = noprocs++;
			/* put index into procrecs in no(proc) */
		}
	}

	if (do_extern_adds) {
		usages = xcalloc(noprocs, sizeof(exp));
		for (d = top_def; d != NULL; d = d->next) {
			exp crt_exp = d->exp;

			if (son(crt_exp) == NULL && isvar(crt_exp)) {
				global_usages(crt_exp, noprocs);
				/* try to identify globals ptrs in procs */
			}
		}
	}

	if (diag != DIAG_NONE && nofds != 0) {
		init_table_space(nofds, noprocs);
		add_dense_no(0, 0);
		add_dense_no (0, 0);	/* dont know why!! */
		symnosforfiles();
		stab_types();
	} else {
		init_table_space(1, noprocs);
		add_dense_no(0, 0);
		add_dense_no (0, 0);	/* dont know why!! */
		IGNORE new_lsym_d("NOFILE.c", 0, stFile, scText, 0, 0);
	}

	/* scan to put everything in MIPS form */
	for (d = top_def; d != NULL; d = d->next) {
		exp crt_exp = d->exp;

		if (son(crt_exp) != NULL && (son(crt_exp)->tag == proc_tag ||
	        son(crt_exp)->tag == general_proc_tag))
		{
			procrec * pr = &procrecs[no(son(crt_exp))];
			exp * st = &son(crt_exp);
			pr->needsproc = scan(st, &st);
			pr->callee_size = (callee_size + 63) & ~63;
		}
	}

	/* calculate the break points for register allocation and do it */
	for (d = top_def; d != NULL; d = d->next) {
		exp crt_exp = d->exp;

		if (son(crt_exp) != NULL
		    && (son(crt_exp)->tag == proc_tag ||
		        son(crt_exp)->tag == general_proc_tag))
		{
			procrec * pr = &procrecs[no(son(crt_exp))];
			needs * ndpr = & pr->needsproc;
			long pprops = (ndpr->propneeds);
			bool leaf = (pprops & anyproccall) == 0;
			spacereq forrest;
			int   freefixed = 8;	/* NO OF S_REGISTERS */
			int   freefloat = 6;	/* NO OF S $f REGISTERS */

			setframe_flags(son(crt_exp), leaf);
			if (!Has_fp) {
				freefixed++; /* can use $30 as normal caller save */
			}

			if (Has_vcallees) {
				freefixed--;
			}

			if (!No_S) {
				IGNORE weightsv(1.0, bro(son(son(crt_exp))));
			}

			/* estimate usage of tags in body of proc */
			forrest = regalloc(bro(son(son(crt_exp))), freefixed, freefloat,
			                   (PIC_code && !leaf) ? 32 : 0);
			/* reg and stack allocation for tags */

			pr->spacereqproc = forrest;

			setframe_info(son(crt_exp));
		}
	}

	/* put defs in main globals and set up symnos*/
	main_globals_index = 0;
	for (d = top_def; d != NULL; d = d->next) {
		main_globals_index++;
	}

	data_lab = (main_globals_index > 33) ? main_globals_index : 33;
	main_globals = xcalloc(main_globals_index, sizeof(dec*));
	symnos = xcalloc(main_globals_index, sizeof(int));

	d = top_def;
	for (i = 0; i < main_globals_index; i++) {
		main_globals[i] = d;
		d = d->next;
	}

	/* ... and set in the position and "addresses" of the externals */
	for (i = 0; i < main_globals_index; i++) {
		exp tag = main_globals[i]->exp;
		char *name = main_globals[i]->name;
		bool extnamed = main_globals[i]->extnamed;
		diag_descriptor * dinf = main_globals[i]->diag_info;
		main_globals[i] ->sym_number = i;
		if (no(tag) != 0 || (extnamed && son(tag) != NULL)
		    || streq(name, "__TDFhandler")
		    || streq(name, "__TDFstacklim"))
		{
			if (no(tag) == 1 && son(tag) == NULL && dinf != NULL /* diagnostics only! */ ) {
				symnos[i] = -1;
			} else {
				no(tag) = (i + 1) * 64 + 32;
				symnos[i] = symnoforext(main_globals[i], mainfile);
			}
		} else {
			symnos[i] = -1;
		}
	}

	setregalt(nowhere.answhere, 0);
	nowhere.ashwhere.ashsize = 0;
	nowhere.ashwhere.ashsize = 0;

	if (as_file) {
		asm_printop(".verstamp %d %d", majorno, minorno);

		if (PIC_code) {
			asm_printop(".option pic2");
		} else {
			asm_printf((diag != DIAG_NONE) ? "\t.option O1\n" : "\t.option O2\n");
		}
	}

	/* this is the only? use of these nos, to satisfy as1 */
	out_verstamp(majorno, minorno);

	if (PIC_code) {
		out_option(2, 2);
	} else {
		out_option(1, (diag != DIAG_NONE) ? 1 : 2);
	}

	if (diag != DIAG_NONE && nofds != 0) {
		diag3_driver->stab_file(0, false);
	} else {
		currentfile = 0;
	}

	/*
	 * compile procedures, evaluate constants, put in the .comm entries
	 * for undefined objects
	 */

	/*
	for (d = top_def; d != NULL; d = d->next) {
		exp tag       = d->exp;
		char *name    = d->name;
		bool extnamed = d->extnamed;

		if (son (tag) != NULL && (extnamed || no (tag) != 0 || streq (name, "main"))) {
			if (extnamed) {
				if (as_file) {
					asm_printop(".globl %s", name);
				}

				out_common (symnos[d->sym_number], iglobal);
			}
		}
	}
	*/

	for (d = top_def; d != NULL; d = d->next) {
		if (!d->processed) {
			code_it(d);
		}
	}

	/* return 1 for error, 0 for good */
}

