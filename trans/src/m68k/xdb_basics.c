/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <string.h>

#include <shared/bool.h>
#include <shared/check.h>

#include <tdf/nat.h>

#include <reader/exp.h>
#include <reader/token.h>

#include <utility/bits.h>

#include <main/flags.h>

#include <diag3/diag_fns.h>
#include <diag3/diagglob.h>
#include <diag3/mark_scope.h>
#include <diag3/diaginfo1.h>
#include <diag3/diag_reform.h>

#include "codex.h"
#include "instrs.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "output.h"
#include "xdb_types.h"
#include "xdb_basics.h"
#include "xdb_output.h"
#include "stab_types.h"


/*
    DIAGNOSTICS INITIALIZATION ROUTINE
*/

static void
diag_prologue(void)
{
	init_diag();
}


/*
    DIAGNOSTICS TERMINATION ROUTINE
*/

static void
diag_epilogue(void)
{
	while (dnt_end()) {
		; /* empty */
	}
	if (diag == DIAG_STABS) {
		mach_op *op = make_extern_data("Letext", 0);
		area(ptext);
		make_stabs("\"\"", 100, 0, op);
		make_external_label("Letext");
	}
	output_all();
	copy_diag();
}


/*
    OUTPUT A DIAGNOSTICS SOURCE MARK
*/

static void
diag_mark(sourcemark *sm)
{
	char *nm = sm->file->file.ints.chars;
	long ln = sm->line_no.nat_val.small_nat;
	diag_source(nm, ln, 1);
}


/*
    DIAGNOSTICS FOR A LOCAL VARIABLE
*/

static void
diag_variable(diag_info *di, exp e)
{
	exp s;
	diag_type t;
	char *nm;
	long p;

	UNUSED(e);

	s = di->data.id_scope.access;
	t = di->data.id_scope.type;
	nm = di->data.id_scope.name.ints.chars;
	p = (no(s) + no(son(s))) / 8;

	if (!isparam(son(s))) {
		diag_local_variable(t, nm, p);
	}
}


/*
    START OF A DIAGNOSTICS ITEM
*/

void
diag_start(diag_info *di, exp e)
{
	switch (di->key) {
	case DIAG_INFO_SOURCE: {
		sourcemark *sm = &(di->data.source.beg);
		diag_mark(sm);
		break;
	}
	case DIAG_INFO_ID:
		mark_scope(e);
		if (props(e) & 0x80) {
			dnt_begin();
		}
		if (diag != DIAG_XDB_NEW) {
			diag_variable(di, e);
		}
		break;
	default:
		break;
	}
}


/*
    END OF A DIAGNOSTICS ITEM
*/

void
diag_end(diag_info *di, exp e)
{
	if (di->key == DIAG_INFO_ID) {
		if (diag == DIAG_XDB_NEW) {
			diag_variable(di, e);
		}
		if (props(e) & 0x80) {
			dnt_end();
		}
	}
}


/*
    DIAGNOSTICS FOR THE START OF A PROCEDURE
*/

void
xdb_diag_proc_begin(diag_descriptor *di, exp p, char *pname, long cname,
		    int is_ext)
{
	char *nm;
	diag_type t;
	sourcemark *sm;

	UNUSED(cname);
	UNUSED(is_ext);

	nm = di->data.id.name.ints.chars;
	t = di->data.id.new_type;
	sm = & (di->data.id.whence);

	diag_proc_main(t, p, nm, !is_local(pname), pname);
	diag_mark(sm);
}


/*
    DIAGNOSTICS FOR THE RETURN STATEMENT OF A PROCEDURE
*/

void
xdb_diag_proc_return(void)
{
	if (diag == DIAG_XDB_NEW) {
		slt_exit();
	}
}


/*
    DIAGNOSTICS FOR THE END OF A PROCEDURE
*/

void
xdb_diag_proc_end(diag_descriptor *di)
{
	UNUSED(di);

	area(ptext);
	if (diag == DIAG_XDB_NEW) {
		mach_op *op1 = make_lab_data(crt_diag_proc_lab, 0);
		mach_op *op2 = make_extern_data(".-1", 0);
		make_instr(m_as_assign, op1, op2, 0);
	} else if (diag == DIAG_XDB_OLD) {
		make_label(crt_diag_proc_lab);
	}
	dnt_end();
	area(plast);
}


/*
    DIAGNOSTICS FOR THE START OF A VALUE
*/

void
xdb_diag_val_begin(diag_descriptor *di, char *pname, long cname, int is_ext)
{
	char *nm;
	diag_type t;

	UNUSED(cname);
	UNUSED(is_ext);

	nm = di->data.id.name.ints.chars;
	t = di->data.id.new_type;
	diag_globl_variable(t, nm, !is_local(pname), pname, 1);
}


/*
    OUTPUT GLOBAL TABLE
*/

static void
OUTPUT_GLOBALS_TAB(void)
{
	diag_descriptor *di = unit_diagvar_tab.array;
	unsigned long i, n = unit_diagvar_tab.lastused;
	for (i = 0; i < n; i++) {
		if (di[i].key == DIAG_TYPEDEF_KEY) {
			diag_type d = di[i].data.type.new_type;
			char *name = di[i].data.type.name.ints.chars;
			diag_type_defn(name, d);
		}
	}
}


/*
    OUTPUT ALL DIAGNOSTIC TAGS
*/

static void
OUTPUT_DIAG_TAGS(void)
{
}


/*
    INSPECT FILENAME
*/

static void
INSPECT_FILENAME(filename fn)
{
	char *nm = fn->file.ints.chars;
	diag_source(nm, 1, 0);
}


/*
    COMPARE TWO DECLARATIONS
*/

static bool
cmp_dec(dec *x, dec *y)
{
	int c;
	long lx, ly;
	sourcemark *sx, *sy;
	diag_descriptor *dx = x->diag_info;
	diag_descriptor *dy = y->diag_info;
	if (dy == NULL || dy->key != DIAG_ID_KEY) {
		return 0;
	}
	if (dx == NULL || dx->key != DIAG_ID_KEY) {
		return 1;
	}
	sx = & (dx->data.id.whence);
	lx = sx->line_no.nat_val.small_nat;
	sy = & (dy->data.id.whence);
	ly = sy->line_no.nat_val.small_nat;
	c = strcmp((char *)sx, (char *)sy);
	if (c < 0) {
		return 0;
	}
	if (c > 0) {
		return 1;
	}
	return lx > ly ? 1 : 0;
}


/*
    SORT DECLARATION INTO ORDER
*/

dec *
sort_decs(dec *p)
{
	dec *res = NULL;
	dec *x = p, *y;
	while (x != NULL) {
		dec *nextx = x->next;
		dec *before = NULL;
		for (y = res; y != NULL; y = y->next) {
			if (!cmp_dec(x, y)) {
				break;
			}
			before = y;
		}
		if (before == NULL) {
			x->next = res;
			res = x;
		} else {
			x->next = before->next;
			before->next = x;
		}
		x = nextx;
	}
	return res;
}

static diag_descriptor *
NEW_DIAG_GLOBAL(diag_descriptor *d)
{
	return d;
}

const struct diag3_driver diag3_driver_stabs = {
	diag_prologue,
	diag_epilogue,

	NULL,
	NEW_DIAG_GLOBAL,
	OUTPUT_GLOBALS_TAB,
	OUTPUT_DIAG_TAGS,
	INSPECT_FILENAME,

	/* TODO: adjust functions here to diag3_driver API */
	NULL,
	NULL,

	NULL,
	NULL,

	NULL,
	NULL
};

