/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/string.h>
#include <shared/xalloc.h>

#include <local/ash.h>

#include <tdf/nat.h>
#include <tdf/shape.h>
#include <tdf/tag.h>

#include <construct/installglob.h>
#include <construct/exp.h>
#include <construct/dec.h>

#include <refactor/optimise.h>

#include <symtab/symconst.h>
#include <symtab/syms.h>
#include <symtab/symtab.h>
#include <symtab/new_symbol.h>

#include <flpt/flpt.h>

#include <main/driver.h>
#include <main/flags.h>
#include <main/print.h>

#include <diag3/diag_reform.h>

#include "tempdecs.h"
#include "procrec.h"
#include "weights.h"
#include "regalloc.h"
#include "make_code.h"
#include "code_here.h"
#include "eval.h"
#include "bitsmacs.h"
#include "scan.h"
#include "main.h"
#include "frames.h"
#include "reg_defs.h"
#include "stabs_diag3.h"
#include "out_ba.h"
#include "ibinasm.h"
#include "directives.h"
#include "pseudo.h"
#include "outofline.h"
#include "alpha_ins.h"
#include "labels.h"
#include "inst_fmt.h"
#include "regexps.h"
#include "getregs.h"
#include "extern_adds.h"
#include "locate.h"
#include "translate.h"
#include "localexpmacs.h"

static bool do_extern_adds;
static int main_globals_index;

procrec *procrecs;
dec **main_globals;

extern filename * fds;

/*
 * used to prevent illegal use of the various identifiers
 * reserved by the alpha assembler
 */
static bool
not_reserved(char *name)
{
	if (streq(name, "edata"))  return 0;
	if (streq(name, "etext"))  return 0;
	if (streq(name, "end"))    return 0;
	if (streq(name, "_ftext")) return 0;
	if (streq(name, "_fdata")) return 0;
	if (streq(name, "_fbss"))  return 0;
	if (streq(name, "_gp"))    return 0;

	if (streq(name, "_procedure_table"))        return 0;
	if (streq(name, "_procedure_string_table")) return 0;

	return 1;
}

static int current_symno;

static void
code_it(dec *d)
{
	exp tag;
	char *name;
	int symdef;
	bool extnamed;

	static space tempspace = { 0, 0 };

	tag  = d->exp;
	name = d->name;

	symdef   = d->sym_number;
	extnamed = d->extnamed;

	if (symnos[symdef] < 0) {
		d->processed = 1;
		return;
	}

	if (son(tag) != NULL && (!extnamed || !is_comm(son(tag)))) {
		if (son(tag)->tag == proc_tag || son(tag)->tag == general_proc_tag) {
			diag_descriptor *dd = d->diag_info;

			/* compile code for proc */
			set_text_section();
			if (dyn_init && !strncmp("__I.TDF", name, 7)) {
				char *new_name;

				/*
				 * we have an initialisation procedure, just change its name
				 * and the linker will do the rest
				 */
				new_name = xcalloc(strlen(name) + strlen("__init_") + 1, sizeof (char));
				strcpy(new_name, "__init_");
				strcat(new_name, name);
				xfree(name);
				name = new_name;
				d->name = name;
			}

			if (diag != DIAG_NONE && dd != NULL) {
				sourcemark *sm = &dd->data.id.whence;
				set_file(sm->file->file.ints.chars, 2);
				diag3_driver->stabd(fscopefile = find_file(sm->file->file.ints.chars),
									sm->line_no.nat_val.small_nat, 0);
			} else if (diag != DIAG_NONE) {
				out_value(0, ifile, make_INT64(0, 1), 0);
				out_data("NOFILE.c", strlen("NOFILE.c"));
				out_loc(0, 0);

#if 0
				init_table_space(1, 0);
				if (nofds == 0) {
					nofds = 1;
					symnosforfiles();
					nofds = 0;
				}

				diag3_driver->stabd(0, 1, 0);
#endif
			}

			if (as_file) {
				asm_printop(".ent %s\n%s:", name, name);
			}

			out_ent(current_symno = symnos[symdef], ient, 2);
			out_common(symnos[symdef], ilabel);
			out_option(1, diag != DIAG_NONE ? 1 : 2);
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
		} else {
			/* global values */
			exp c = son(tag);
			IGNORE evaluated(c, isvar(tag) ? -symdef - 1 : symdef + 1);
		}
	} else {
		/* global declarations but no definitions or is_comm */
		long size;
		shape s = d->shape;
		bool vs = son(tag) != NULL /* ie is_comm */;
		size = (shape_size(s) + 7) >> 3;

		if ((isvar(tag) || s->tag != prokhd) && not_reserved(name)) {
			if (vs /* && size != 0 */) {
				if (as_file) {
					asm_printop(".comm %s %ld", name, size == 0 ? 4 : size);
				}

				out_value(symnos[symdef], icomm, size == 0 ? 4 : size, 0);
			} else {
				if (as_file) {
					asm_printop(".extern %s %ld", name, size);
				}

				out_value(symnos[symdef], iextern, size, 1);
			}
		} else if (son(tag) == NULL && !extnamed) {
			if (as_file) {
				asm_printf( "\n\t.lcomm\t%s %ld\n", name, size);
			}

			out_value(symnos[symdef], ilcomm, size, 1);
		}
	}

	/*  NO! the pt fields are wrong!
	    kill_exp(son(tag), son(tag));
	 */

	/*end:*/
	/*son(tag) = NULL;*/
	d->processed = 1;
}

static void
mark_unaliased(exp e)
{
	bool ca = 1;
	exp p;

	for (p = pt (e); p != NULL && ca; p = pt(p)) {
		if (bro(p) == NULL || (!(p->last && bro(p)->tag == cont_tag) &&
		                      !(!p->last && bro(p)->last && bro(bro(p))->tag == ass_tag))) {
			ca = 0;
		}
	}

	if (ca) {
		setcaonly(e);
	}
}

/*
 * Return the tag with the given name
 */
baseoff
find_tag(char *s)
{
	int i;

	for (i = 0; i < main_globals_index; i++) {
		exp tag;
		char *name;

		tag  = main_globals[i]->exp;
		name = main_globals[i]->name;
		if (streq(name, s)) {
			return boff(tag);
		}
	}

	printf("%s\n: ", s);
	error(ERR_FATAL, "tag not declared");

	UNREACHED;
}

void
local_translate_capsule(void)
{
	extern exp *usages;
	dec *d;
	int noprocs;
	int i;

	setregalt(nowhere.answhere, NO_REG);
	nowhere.ashwhere.ashsize = 0;
	nowhere.ashwhere.ashsize = 0;

	opt_all_exps();

	/* mark static unaliased */
	for (d = top_def; d != NULL; d = d->next) {
		exp crt_exp;

		crt_exp = d->exp;
		if (son(crt_exp) != NULL && !d->extnamed && isvar(crt_exp)) {
			mark_unaliased(crt_exp);
		}
	}

	/* remove static functions with no uses if compiling with diagnostics */
	if (diag != DIAG_NONE) {
		dec **ptr_def;

		ptr_def = &top_def;
		while (*ptr_def) {
			exp crt_exp;

			crt_exp = (*ptr_def)->exp;
			if (son(crt_exp) != NULL) {
				if ((son(crt_exp)->tag == general_proc_tag ||
				    son(crt_exp)->tag == proc_tag) &&
				   (no(crt_exp) == 0 && diag != DIAG_NONE && !(*ptr_def)->extnamed)) {
					dec *old_ptr = *ptr_def;
					*ptr_def = (*ptr_def)->next;
					free(old_ptr);
				} else {
					ptr_def = &((*ptr_def)->next);
				}
			} else {
				ptr_def = &((*ptr_def)->next);
			}
		}
	}

	noprocs = 0;
	for (d = top_def; d != NULL; d = d->next) {
		exp crt_exp = d->exp;

		if (son(crt_exp) != NULL && (son(crt_exp)->tag == proc_tag ||
		                             son(crt_exp)->tag == general_proc_tag)) {
			noprocs++;
		}
	}

	/* count procs */
	procrecs = xcalloc(noprocs, sizeof (procrec));
	noprocs = 0;

	for (d = top_def; d != NULL; d = d->next) {
		exp crt_exp = d->exp;

		if (son(crt_exp) != NULL && (son(crt_exp)->tag == proc_tag
		                              || son(crt_exp)->tag == general_proc_tag)) {
			no(son(crt_exp)) = noprocs++;
			/* put index into procrecs in no(proc) */
		}
	}

	if (do_extern_adds) {
		usages = xcalloc(noprocs, sizeof(exp));
		for (d = top_def; d != NULL; d = d->next) {
			exp crt_exp = d->exp;

			if (son(crt_exp) == NULL && isvar(crt_exp) ) {
				/* try to identify globals ptrs in procs */
				global_usages(crt_exp, noprocs);
			}
		}
	}

	if (diag != DIAG_NONE) {
		int l, i;
		char *ftmp;

		init_table_space(nofds, noprocs);
		add_dense_no(0, 0);
		add_dense_no(0, 0);

#if 1
		for (i = 0; i < nofds; ++i) {
			l = strlen(fds[i]->file.ints.chars);
			ftmp = xcalloc(l + 1, sizeof(char));
			ftmp[0] = 'X';
			strcpy(ftmp + 1, fds[i]->file.ints.chars);
			fds[i]->file.ints.chars = xrealloc(fds[i]->file.ints.chars, l + 1);
			strcpy(fds[i]->file.ints.chars, ftmp);
			xfree(ftmp);
		}
#endif

		symnosforfiles();
		stab_types();
	} else {
		init_table_space(1, noprocs);
		add_dense_no(0, 0);
		add_dense_no(0, 0);
		IGNORE new_lsym_d("NOFILE.c", 0, stFile, scText, 0, 0);
	}

	for (d = top_def; d != NULL; d = d->next) {
		exp crt_exp = d->exp;

		if (son(crt_exp) != NULL && (son(crt_exp)->tag == proc_tag
		                              || son(crt_exp)->tag == general_proc_tag)) {
			procrec *pr;
			exp *st;
			bool has_varargs;

			pr = &procrecs[no(son(crt_exp))];
			st = &son(crt_exp);
			has_varargs = vascan(st);

			(*st)->dfile = "";
			if (has_varargs) {
				set_has_c_vararg(*st);
			} else {
				clear_has_c_vararg(*st);
			}

			pr->needsproc   = scan(st, &st);
			pr->callee_size = (callee_size + 63) & ~63;
		}
	}


	/* calculate the break points for register allocation and do it */
	for (d = top_def; d != NULL; d = d->next) {
		exp crt_exp = d->exp;

		if (son(crt_exp) != NULL && (son(crt_exp)->tag == proc_tag
		                              || son(crt_exp)->tag == general_proc_tag)) {
			procrec *pr = &procrecs[no(son(crt_exp))];
			needs *ndpr = & pr->needsproc;
			long pprops = ndpr->propneeds;
			bool leaf = (pprops & anyproccall) == 0;
			spacereq forrest;
			int freefixed = 6;
			int freefloat = 8;

			setframe_flags(son(crt_exp), leaf);
			/* if (Has_vcallees || proc_has_gen_call(son(crt_exp))) freefixed--;*/
			if (Has_vcallees) {
				freefixed--;
			}

			freefixed += (Has_fp == 0);
			if (!No_S) {
				IGNORE weightsv (1.0, bro(son(son(crt_exp))));
			}

			/* estimate usage of tags in body of proc */
			forrest = regalloc(bro(son(son(crt_exp))), freefixed, freefloat, 0);

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

	data_lab = main_globals_index > 33 ? main_globals_index : 33;
	main_globals = xcalloc(main_globals_index, sizeof (dec *));
	symnos = xcalloc(main_globals_index, sizeof (int));

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
		main_globals[i]->sym_number = i;

		/* if not NULL */
		if (no(tag) != 0 || (extnamed && son(tag) != NULL)
		     || streq(name, "__alpha_errhandler") || streq(name, "__alpha_stack_limit"))
		{
			if (no(tag) == 1 && son(tag) == NULL && (bro(pt(tag)) == NULL ||
			    bro(pt(tag))->tag == 101 || bro(pt(tag))->tag == 102 )
			   /* diagnostics only! */ )
			{
				symnos[i] = -1;
			} else {
				no(tag) = (i + 1) * 64 + 32;
				symnos[i] = symnoforext(main_globals[i], mainfile);
			}
		} else {
			/* only applies to alphatrans */
			symnos[i] = -1;
			/* symnos[i] = symnoforext(main_globals[i],mainfile);*/
		}
	}

	if (as_file) {
		asm_comment("produced by TDF->Alpha/OSF1 installer");
		asm_printop(".ugen");
	}

	out_common(0, iugen);

	if (assembler & ASM_OSF1) {
		if (as_file) {
			asm_printop(".verstamp %d %d", majorno, minorno);
		}
	}

	out_verstamp(majorno, minorno);

	out_option(1, diag != DIAG_NONE ? 1 : 2);

	if (diag != DIAG_NONE && nofds != 0) {
		diag3_driver->stab_file(0, false);
	} else {
		currentfile = 0;
	}

	/*
	 * compile procedures, evaluate constants, put in the
	 * .comm entries for undefined objects
	 */
	for (d = top_def; d != NULL; d = d->next) {
		exp tag       = d->exp;
		char *name    = d->name;
		bool extnamed = d->extnamed;

		if (son(tag) != NULL && (extnamed || no(tag) != 0 || streq(name, "main"))) {
			if (!extnamed) {
				continue;
			}

			/* globalise all global names  */
			if (dyn_init && !strncmp("__I.TDF", name, 7)) {
				char *new_name = xcalloc(strlen(name) + strlen("__init_") + 1, sizeof (char));
				strcpy(new_name, "__init_");
				strcat(new_name, name);
				xfree(name);
				name = new_name;
				d->name = new_name;
			}

			if (as_file) {
				asm_printop(".globl %s", name);
			}

			out_common(symnos[d->sym_number] , iglobal);
		}
	}

	for (d = top_def; d != NULL; d = d->next) {
		if (!d->processed) {
			code_it(d);
		}
	}
}

