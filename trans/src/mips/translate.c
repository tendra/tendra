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
#include <tdf/tag.h>

#include <reader/basicread.h>

#include <symtab/symconst.h>
#include <symtab/syms.h>
#include <symtab/symtab.h>
#include <symtab/new_symbol.h>

#include <construct/installglob.h>
#include <construct/exp.h>
#include <construct/shape.h>
#include <construct/me_fns.h>

#include <main/driver.h>
#include <main/flags.h>
#include <main/print.h>

#include <diag3/diag_reform.h>

#include <refactor/optimise.h>

#include "tempdecs.h"
#include "weights.h"
#include "procrectypes.h"
#include "regalloc.h"
#include "make_code.h"
#include "code_here.h"
#include "eval.h"
#include "bitsmacs.h"
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


extern exp find_named_tg(char*, shape);
extern shape f_top;
extern shape f_proc;

procrec * procrecs;
dec ** main_globals;
static int main_globals_index;

extern long fscopefile;
extern bool do_extern_adds;

/* various identifier reserved by MIPS */
static bool
not_reserved(char *id)
{
	if (streq(id, "edata"))  return false;
	if (streq(id, "etext"))  return false;
	if (streq(id, "end"))    return false;
	if (streq(id, "_ftext")) return false;
	if (streq(id, "_fdata")) return false;
	if (streq(id, "_fbss"))  return false;
	if (streq(id, "_gp"))    return false;

	if (streq(id, "_procedure_table"))        return false;
	if (streq(id, "_procedure_string_table")) return false;

	return true;
}

static char
varsize(shape sha)
{
	return sha->tag == nofhd;
}

int current_symno;

void
globalise_name(dec * my_def)
{
	char *id;

	id = my_def->dec_id;
	if (!my_def->extnamed) {
		return;
	}

	if (as_file) {
		asm_printop(".globl %s", id);
	}

	out_common(symnos[my_def->sym_number], iglobal);
}

static void
code_it(dec *my_def)
{
	exp tg;
	char *id;
	long symdef;
	bool extnamed;

	static space tempspace = { 0, 0 };

	tg = my_def->dec_exp;
	id = my_def->dec_id;
	symdef = my_def ->sym_number;
	extnamed =  my_def->extnamed;

	if (symnos[symdef] < 0) {
		goto end; /* ? unused symbols */
	}

	if (son(tg) != NULL && (!extnamed || !is_comm(son(tg)))) {
		if (son(tg)->tag == proc_tag || son(tg)->tag == general_proc_tag) {
			diag_descriptor * dd =  my_def->diag_info;

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

			globalise_name(my_def);

			if (as_file) {
				asm_printop(".ent %s\n%s:", id, id);
			}

			out_ent (current_symno = symnos[symdef], ient, 2);/* why 2? */
			out_common(symnos[symdef], ilabel);

			if (as_file) {
				asm_printop(diag != DIAG_NONE ? ".option O1" : ".option O2");
			}

			out_option(1, (diag != DIAG_NONE) ? 1 : 2);

			symnoforstart(symdef, currentfile);
			settempregs(son(tg));
			code_here(son(tg), tempspace, nowhere);

			if (diag != DIAG_NONE && dd != NULL) {
				diag3_driver->stabd(fscopefile, currentlno + 1, 0);
			}

			if (as_file) {
				asm_printop(".end %s", id);
			}
			out_common(symnoforend(my_def, currentfile), iend);
		} else {			/* global values */
			exp c = son(tg);
			IGNORE evaluated(c, (isvar(tg)) ? (-symdef - 1) : symdef + 1, my_def);
		}
	} else {
		/* global declarations but no definitions or is_comm */
		long  size;
		shape s = (son(tg) == NULL) ? my_def->dec_shape : sh(son(tg));
		size = (shape_size(s) + 7) >> 3;

		if ((isvar(tg) || s->tag != prokhd) && not_reserved(id)) {
			if ((son(tg) != NULL && is_comm(son(tg)))
			    || (son(tg) == NULL && varsize(sh(tg))))
			{
				if (size != 0) { /* ? ? ! ? */
					globalise_name(my_def);
					if (as_file) {
						asm_printop(".comm %s %ld", id, size);
					}

					out_value(symnos[symdef], icomm, size, 1);
				}
			} else {
				if (as_file) {
					asm_printop(".extern %s %ld", id, size);
				}

				out_value(symnos[symdef], iextern, size, 1);
			}
		} else if (son(tg) == NULL && !extnamed) {
			if (size != 0) { /* ? ? ! ? */
				if (as_file) {
					asm_printop(".lcomm %s %ld", id, size);
				}

				out_value(symnos[symdef], ilcomm, size, 1);
			}
		}
	}

end:

	my_def->processed = 1;
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
		exp crt_exp = (*sdef)->dec_exp;
		bool extnamed = (*sdef)->extnamed;

		if (no(crt_exp) == 0 && !extnamed) {
			*sdef = (*sdef)->def_next;
		} else {
			sdef = &((*sdef)->def_next);
		}
	}
}

void
local_translate_capsule(void)
{
	dec * my_def;
	int noprocs;
	int i;

	opt_all_exps();
	remove_unused();

	if (dyn_init) {
		for (my_def = top_def; my_def != NULL; my_def = my_def->def_next) {
			exp crt_exp = my_def->dec_exp;
			char * id = my_def->dec_id;
			if (streq(id, "main") && son(crt_exp) != NULL &&
			    son(crt_exp)->tag == proc_tag) {
				exp fn = me_obtain(find_named_tg("__DO_I_TDF", f_proc));
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
	for (my_def = top_def; my_def != NULL; my_def = my_def->def_next) {
		exp crt_exp = my_def->dec_exp;
		if (son(crt_exp) != NULL &&
		    !my_def->extnamed &&
		    isvar(crt_exp)) {
			mark_unaliased(crt_exp);
		}
	}

	noprocs = 0;
	for (my_def = top_def; my_def != NULL; my_def = my_def->def_next) {
		exp crt_exp = my_def->dec_exp;
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
		procrecs = (procrec *)xcalloc(noprocs, sizeof(procrec));
		noprocs = 0;
	}

	for (my_def = top_def; my_def != NULL; my_def = my_def->def_next) {
		exp crt_exp = my_def->dec_exp;
		if (son(crt_exp) != NULL &&
		    (son(crt_exp)->tag == proc_tag || son(crt_exp)->tag == general_proc_tag)) {
			no(son(crt_exp)) = noprocs++;
			/* put index into procrecs in no(proc) */
		}
	}

	if (do_extern_adds) {
		usages = (exp*)xcalloc(noprocs, sizeof(exp));
		for (my_def = top_def; my_def != NULL; my_def = my_def->def_next) {
			exp crt_exp = my_def->dec_exp;
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
	for (my_def = top_def; my_def != NULL; my_def = my_def->def_next) {
		exp crt_exp = my_def->dec_exp;
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
	for (my_def = top_def; my_def != NULL; my_def = my_def->def_next) {
		exp crt_exp = my_def->dec_exp;
		if (son(crt_exp) != NULL
		    && (son(crt_exp)->tag == proc_tag ||
		        son(crt_exp)->tag == general_proc_tag))
		{
			procrec * pr = &procrecs[no(son(crt_exp))];
			needs * ndpr = & pr->needsproc;
			long pprops = (ndpr->propsneeds);
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
	for (my_def = top_def; my_def != NULL; my_def = my_def->def_next) {
		main_globals_index++;
	}

	data_lab = (main_globals_index > 33) ? main_globals_index : 33;
	main_globals = (dec**)xcalloc(main_globals_index, sizeof(dec*));
	symnos = (int *)xcalloc(main_globals_index, sizeof(int));

	my_def = top_def;
	for (i = 0; i < main_globals_index; i++) {
		main_globals[i] = my_def;
		my_def = my_def->def_next;
	}

	/* ... and set in the position and "addresses" of the externals */
	for (i = 0; i < main_globals_index; i++) {
		exp tg = main_globals[i]->dec_exp;
		char *id = main_globals[i]->dec_id;
		bool extnamed = main_globals[i]->extnamed;
		diag_descriptor * dinf = main_globals[i]->diag_info;
		main_globals[i] ->sym_number = i;
		if (no(tg) != 0 || (extnamed && son(tg) != NULL)
		    || streq(id, "__TDFhandler")
		    || streq(id, "__TDFstacklim"))
		{
			if (no(tg) == 1 && son(tg) == NULL && dinf != NULL /* diagnostics only! */ ) {
				symnos[i] = -1;
			} else {
				no(tg) = (i + 1) * 64 + 32;
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
	for (my_def = top_def; my_def != NULL; my_def = my_def->def_next) {
		exp tg = my_def->dec_exp;
		char *id = my_def->dec_id;
		bool extnamed = my_def->extnamed;

		if (son (tg) != NULL && (extnamed || no (tg) != 0 || streq (id, "main"))) {
			if (extnamed) {
				if (as_file) {
					asm_printop(".globl %s", id);
				}

				out_common (symnos[my_def->sym_number], iglobal);
			}
		}
	}
	*/

	for (my_def = top_def; my_def != NULL; my_def = my_def->def_next) {
		if (!my_def->processed) {
			code_it(my_def);
		}
	}

	/* return 1 for error, 0 for good */
}

