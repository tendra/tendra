/*
 * Copyright 2002-2014, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>
#include <stdio.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/string.h>

#include <reader/token.h>

#include <diag3/diag_fns.h>
#include <diag3/diagglob.h>
#include <diag3/diaginfo1.h>
#include <diag3/diag_reform.h>
#include <diag3/mark_scope.h>

#include <main/driver.h>
#include <main/print.h>

#include <construct/machine.h>

#include "cv_types.h"
#include "cv_outtype.h"

static int crt_proc_start;
static int last_line_no;
static char *main_filename;    /* init by diagnose_prelude */
static int filename_space = 0; /* init by diagnose_prelude */
static int filename_gate  = 0; /* init by diagnose_prelude */
static long filename_pos;

static int
check_filename(sourcemark sm)
{
	if (!main_filename) {
		main_filename = sm.file->file.ints.chars;
		return 1;
	}

	if (streq(main_filename, sm.file->file.ints.chars)) {
		return 1;
	}

	return 0;
}

static void
out_diagnose_prelude(void)
{
	main_filename  = NULL;
	filename_space = 0;
	filename_gate  = 0;
}

static void
out_diagnose_postlude(void)
{
}

#ifdef TDF_DIAG3

static void
output_diag(diag_info *d, int proc_no, exp e)
{
	if (d->key == DIAG_INFO_SOURCE) {
		int l = (int) d->data.source.beg.line_no.nat_val.small_nat -
		        crt_proc_start + 1;
		if (!check_filename(d->data.source.beg)) {
			return;
		}

		if (l == last_line_no) {
			return;
		}

		last_line_no = l;

		if (l > 0) {
			asm_printf(" .ln %d\n", l);
		}
		return;
	}

	if (d->key == DIAG_INFO_ID) {
		ot ty;
		exp acc = d->data.id_scope.access;
		int p = (no(acc) + no(child(acc))) / 8;
		int param_dec = isparam(child(acc));

		mark_scope(e);

		if (e->props & 0x80) {
			asm_printf(" .def .bb; .val .; .scl 100;  .line %d; .endef\n",
			            last_line_no);
		}

		asm_printf(" .def %s; .val ", d->data.id_scope.name.ints.chars);
		if (param_dec) {
			asm_printf("%d", p + 8);
		} else {
			asm_printf("%d-.Ldisp%d", p, proc_no);
		}
		asm_printf("; .scl %d; ", (param_dec) ? 9 : 1);
		ty = out_type(d->data.id_scope.type, 0);
		asm_printf(".type 0%o; .endef\n", ty.type + (ty.modifier << 4));

		return;
	}
}

#endif

#ifdef TDF_DIAG4

void
code_diag_info(diag_info *d, int proc_no,
	void(*mcode)(void *), void *args)
{
	if (d == NULL) {
		(*mcode)(args);
		return;
	}

	switch (d->key) {
	case DIAG_INFO_SCOPE: {
		asm_printf(" .def .bb; .val .; .scl 100;  .line %d; .endef\n",
		           last_line_no);
		code_diag_info(d->more, proc_no, mcode, args);
		asm_printf(" .def .eb; .val .; .scl 100; .line %d; .endef\n",
		           last_line_no);
		return;
	}

	case DIAG_INFO_SOURCE: {
		int l = (int) d->data.source.beg.line_no.nat_val.small_nat
			- crt_proc_start + 1;
		if (check_filename(d->data.source.beg) && l != last_line_no) {
			last_line_no = l;
			if (l > 0) {
				asm_printf(" .ln %d\n", l);
			}
		}

		code_diag_info(d->more, proc_no, mcode, args);
		return;
	}

	case DIAG_INFO_ID: {
		exp acc = d->data.id_scope.access;
		ot ty;
		int p, param_dec;

		if (acc->tag != hold_tag && acc->tag != hold2_tag) {
			failer("not hold_tag");
		}

		acc = child(acc);
		if (acc->tag == cont_tag && child(acc)->tag == name_tag &&
		    isvar(child(child(acc)))) {
			acc = child(acc);
		}

		if (acc->tag == name_tag && !isdiscarded(acc) && !isglob(child(acc))) {
			p = (no(acc) + no(child(acc))) / 8;
			param_dec = isparam(child(acc));
			asm_printf(" .def %s; .val ", d->data.id_scope.name.ints.chars);
			if (param_dec) {
				asm_printf("%d", p + 8);
			} else {
				asm_printf("%d-.Ldisp%d", p, proc_no);
			}
			asm_printf("; .scl %d; ", (param_dec) ? 9 : 1);
			ty = out_type(d->data.id_scope.type, 0);
			asm_printf(".type 0%o; .endef\n", ty.type + (ty.modifier << 4));
		}

		code_diag_info(d->more, proc_no, mcode, args);
	}
	}
}

#endif

static void
output_end_scope(diag_info *d, exp e)
{
	if (d->key == DIAG_INFO_ID && e->props & 0x80) {
		asm_printf(" .def .eb; .val .; .scl 100; .line %d; .endef\n",
			last_line_no);
	}
}

static void
diag_val_begin(diag_descriptor *d, int global, int cname, char *pname)
{
	ot type;

	asm_printf(" .def %s; .val ", d->data.id.name.ints.chars);
	if (cname == -1) {
		asm_printf("%s", pname);
	} else {
		asm_printf("%s%d", local_prefix, cname);
	}
	asm_printf("; .scl %d; ", global ? 2 : 3);
	type = out_type(d->data.id.new_type, 0);
	asm_printf(".type 0%o; .endef\n", type.type + (type.modifier << 4));
}

static void
diag_val_end(diag_descriptor *d)
{
	UNUSED(d);
}

static void
diag_proc_begin(diag_descriptor *d, int global, int cname, char *pname)
{
	ot type;

	UNUSED(cname);

	if (!d) {
		return;
	}

	check_filename(d->data.id.whence);

	asm_printf(" .def %s; .val %s; .scl %d; ",
	           d->data.id.name.ints.chars, pname, global ? 2 : 3);
	type = out_type(d->data.id.new_type->data.proc.result_type, 0);
	asm_printf(".type 0%o; .endef\n", type.type + (type.modifier << 6) + 32);

	crt_proc_start = d->data.id.whence.line_no.nat_val.small_nat;
	last_line_no = 1;
	asm_printf(" .def .bf; .val .; .scl 101; .line %d; .endef\n", crt_proc_start);
	asm_printf(" .ln 1\n");
}

static void
diag_proc_end(diag_descriptor *d)
{
	if (!d) {
		return;
	}

	asm_printf(" .def .ef; .val .; .scl 101; .line %d; .endef\n", last_line_no + 1);
	asm_printf(" .def %s; .val .; .scl -1; .endef\n", d->data.id.name.ints.chars);
}

static void
OUTPUT_GLOBALS_TAB(void)
{
	diag_descriptor *di = unit_diagvar_tab.array;
	int n = unit_diagvar_tab.lastused;
	int i;
	ot type;

	for (i = 0; i < n; i++) {
		if (di[i].key == DIAG_TYPEDEF_KEY) {
			asm_printf(" .def %s; .scl 13; ", di[i].data.type.name.ints.chars);
			type = out_type(di[i].data.type.new_type, 0);
			asm_printf(".type 0%o; .endef\n", type.type + (type.modifier << 4));
		}
	}
}

static void
OUTPUT_DIAG_TAGS(void)
{
	diag_tagdef **di;
	int i, n;

	di = unit_ind_diagtags;
	n  = unit_no_of_diagtags;

	if (!filename_space) {
		filename_pos = ftell(as_file);
		asm_printf("                                                                                                                      \n");
		filename_space = 1;
	}

	for (i = 0; i < n; ++i) {
		diag_type d = di[i] ->d_type;
		switch (d->key) {
		case DIAG_TYPE_STRUCT:
		case DIAG_TYPE_UNION:
		case DIAG_TYPE_ENUM:
			out_tagged(d);
			break;

		default:
			break;
		}
	}
}

static void
INSPECT_FILENAME(filename fn)
{
	char *nm, *f;
	long here;
	int len;

	nm  = fn->file.ints.chars;
	len = strlen(nm);

	if (filename_gate
		|| len < 4 || len > 120
		|| nm[len - 1] == 'h' || nm[len - 2] != '.')
	{
		return;
	}

	f = &nm[len - 2];

	while (f != nm && f[-1] != '/') {
		--f;
	}

	filename_gate = 1;

	if (!filename_space) {
		asm_printf(" .file \"%s\"\n", f);
	} else {
		here = ftell(as_file);
		fseek(as_file, filename_pos, 0);
		asm_printf(" .file \"%s\"\n", f);
		fseek(as_file, here, 0);
	}
}

static diag_descriptor *
NEW_DIAG_GLOBAL(diag_descriptor *d)
{
	return d;
}

const struct diag3_driver diag3_driver_cv = {
	out_diagnose_prelude,
	out_diagnose_postlude,

	NULL,
	NEW_DIAG_GLOBAL,
	OUTPUT_GLOBALS_TAB,
	OUTPUT_DIAG_TAGS,
	INSPECT_FILENAME,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,

	output_diag,
	output_end_scope,

	diag_proc_begin,
	diag_proc_end,

	diag_val_begin,
	diag_val_end
};

