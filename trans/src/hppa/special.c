/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <string.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/string.h>

#include <tdf/nat.h>
#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/exp.h>
#include <construct/machine.h>

#include <main/flags.h>
#include <main/driver.h>
#include <main/print.h>

#include <refactor/const.h>

#include "procrec.h"
#include "translate.h"
#include "addr.h"
#include "move.h"
#include "reg.h"
#include "getregs.h"
#include "guard.h"
#include "code_here.h"
#include "inst_fmt.h"
#include "hppains.h"
#include "labels.h"
#include "bits.h"
#include "proc.h"
#include "frames.h"
#include "regexps.h"
#include "special.h"

/*
 * these are the procs I could do something about
 * >0 special, handle inline in specialmake
 * 0 not special
 */
static int
specno(char * n)
{
	asm_comment("specno(%s)", n);

	if (streq(n, "___builtin_asm") || streq(n, "___TDF_builtin_asm")) {
		return 4;
	}

	if (streq(n, "___builtin_alloca") || streq(n, "___TDF_builtin_alloca")) {
		return 5;
	}

	return 0;
}

/* what name to use with call instruction for specials */
char *
special_call_name(int i)
{
	switch (i) {
	case 5:
		return "_alloca";

	default:
		error(ERR_SERIOUS, "attempting external call to builtin");
		return "";
	}

	UNREACHED;
}

static needs zeroneeds = {0, 0, 0, 0};	/* has no needs */
#if 0
static const needs onefixneeds = {1, 0, 0, 0};	/* one fix reg needs */
static const needs twofixneeds = {2, 0, 0, 0};	/* two fix reg needs */
#endif

/* these are the needs for their expansion */
needs
specialneeds(int i)
{
	asm_comment("specialneeds(%d,...)", i);

	switch (i) {
	case 4: return zeroneeds; /* asm(string) */
	case 5: return zeroneeds; /* alloca(n) */

	default:
		asm_comment("specialneeds: unimplemented builtin %d", i);
		error(ERR_SERIOUS, "unimplemented builtin");
		return zeroneeds;
	}

	UNREACHED;
}

/* could I treat this function load specially ? */
int
specialfn(exp fn)
{
	if (fn->tag == name_tag && son(fn)->tag == ident_tag &&
	    isglob(son(fn)) && son(son(fn)) == NULL) {
		char *extname = nextg(son(fn))->name;

		return specno(extname);
	}

	return 0;
}

/* Is a call to this function reason to prohibit optmisation of caller? */
int
specialopt(exp fn)
{
	if (fn->tag == name_tag && son(fn)->tag == ident_tag &&
	    isglob(son(fn)) && son(son(fn)) == NULL) {
		char *extname = nextg(son(fn))->name;

		if (extname == 0) {
			return 0;
		}

		extname += strlen(name_prefix); /* Normalise "_foo" -> "foo" */

		asm_comment("specialopt: %s", extname);

		if ((streq(extname, "vfork")) ||
		    (streq(extname, "setjmp")) ||
		    (streq(extname, "_setjmp")) ||
		    (streq(extname, "sigsetjmp"))
		   ) {
			asm_comment("specialopt: return 1");
			return 1;
		}
	}
	return 0;
}

int
specialmake(int i, exp par, space sp, where dest, int exitlab)
{
	switch (i) {
	case 4: {
		/* asm(s) - simply output s */
		exp e;
		char *s;

		/* "par" is (eval_tag (pack_tag (string_tag no=string-table-index))) */
		e = son(son(par));
		if (e->tag != string_tag) {
			error(ERR_SERIOUS, "asm argument not string");
			return 0;
		}
		s = nostr(e);

		/* asm is dangerous; as the least precaution, zap register tracking. */
		clear_all();
		asm_printf("!  asm:\n" );
		asm_printf( "%s\n", s);
		break;
	}

	case 5: {
		/* alloca(n) - grow stack frame by n bytes and then grab
		grab n bytes */

		int maxargbytes = max_args >> 3;
		int dreg;
		ans aa;

		dreg = ((discrim(dest.answhere) == inreg) ? regalt(dest.answhere) : getreg(sp.fixed));

		if (par->tag == val_tag) {
			/* n is a constant */
			int n = no(par);

			/* adjust n to be multiple of 64 so stack stays 64 byte aligned */
			n = (n + 63) & ~(63);

			if (n != 0) {
				/* alloca(n) = %sp - maxargbytes */
				if (SIMM14(-maxargbytes)) {
					ld_ir_ins(i_ldo, cmplt_, fs_, empty_ltrl, -maxargbytes, SP, dreg);
				} else {
					ir_ins(i_addil, fs_L, empty_ltrl, -maxargbytes, SP);
					ld_ir_ins(i_ldo, cmplt_, fs_R, empty_ltrl, -maxargbytes, GR1, dreg);
				}
				/* grow stack frame, i.e. %sp -> %sp + n */
				if (SIMM14(n)) {
					ld_ir_ins(i_ldo, cmplt_, fs_, empty_ltrl, n, SP, SP);
				} else {
					/* grow stack frame by more than 8192 bytes */
					ir_ins(i_addil, fs_L, empty_ltrl, n, SP);
					ld_ir_ins(i_ldo, cmplt_, fs_R, empty_ltrl, n, GR1, SP);
				}
			}
		} else {
			int nreg = reg_operand(par, sp);

			/* adjust nreg so that stack stays 64 byte aligned */
			ld_ir_ins(i_ldo, cmplt_, fs_, empty_ltrl, 63, nreg, GR1);
			riir_ins(i_dep, c_, 0, 31, 6, GR1);

			/* alloca(n) = %sp - maxargbytes */
			if (SIMM14(-maxargbytes)) {
				ld_ir_ins(i_ldo, cmplt_, fs_, empty_ltrl, -maxargbytes, SP, dreg);
			} else {
				ir_ins(i_addil, fs_L, empty_ltrl, -maxargbytes, SP);
				ld_ir_ins(i_ldo, cmplt_, fs_R, empty_ltrl, -maxargbytes, GR1, dreg);
			}
			/* %sp -> %sp + nreg */
			rrr_ins(i_add, c_, SP, GR1, SP);
		}

		setregalt(aa, dreg);
		move(aa, dest, guardreg(dreg, sp).fixed, 0);
		break;
	}

	default:
		asm_comment("specialmake: unimplemented builtin %d", i);
		error(ERR_SERIOUS, "unimplemented builtin");
		return 0;
	}

	return exitlab;		/* for most cases */
}

#define sz_millicode_lib 7

static struct {
	const char *proc_name;
	bool called;
	bool in_library;
} millicode_lib [ sz_millicode_lib ] = {
	{ milli_mulU,    0, 1 }, /* $$mulU    */
	{ milli_mulI,    0, 1 }, /* $$mulI    */
	{ milli_divU,    0, 1 }, /* $$mulU    */
	{ milli_divI,    0, 1 }, /* $$divI    */
	{ milli_remU,    0, 1 }, /* $$remU    */
	{ milli_remI,    0, 1 }, /* $$remI    */
	{ milli_dyncall, 0, 1 }, /* $$dyncall */
};

/*
 * Output a millicode library call
 */
void
call_millicode(int n, int r, char *stub, bool restore_linkage_ptr_reg)
{
	const char *nm = millicode_lib[n].proc_name;
	millicode_lib[n].called = 1;
	extj_special_ins(nm, r, stub, 0);

	if (PIC_code && restore_linkage_ptr_reg) {
		rr_ins(i_copy, GR5, GR19);
	}
}

void
import_millicode(void)
{
	int n;

	for(n = 0; n < sz_millicode_lib; n++) {
		if (millicode_lib[n].called) {
			asm_printop(".IMPORT %s,MILLICODE", millicode_lib[n].proc_name);
		}
	}
}

