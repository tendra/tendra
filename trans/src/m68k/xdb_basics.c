/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <string.h>

#include <reader/exp.h>
#include <reader/code.h>
#include <reader/token.h>

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

void
diag_prologue(void)
{
	init_diag();
	return;
}


/*
    DIAGNOSTICS TERMINATION ROUTINE
*/

void
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
	return;
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
	return;
}


/*
    DIAGNOSTICS FOR A LOCAL VARIABLE
*/

static void
diag_variable(diag_info *di, exp e)
{
	exp s = di->data.id_scope.access;
	diag_type t = di->data.id_scope.typ;
	char *nm = di->data.id_scope.nme.ints.chars;
	long p = (no(s) + no(son(s))) / 8;
	if (!isparam(son(s))) {
		diag_local_variable(t, nm, p);
	}
	return;
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
	return;
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
	return;
}


/*
    DIAGNOSTICS FOR THE START OF A PROCEDURE
*/

void
xdb_diag_proc_begin(diag_descriptor *di, exp p, char *pname, long cname,
		    int is_ext)
{
	char *nm = di->data.id.nme.ints.chars;
	diag_type t = di->data.id.new_type;
	sourcemark *sm = & (di->data.id.whence);
	diag_proc_main(t, p, nm, !is_local(pname), pname);
	diag_mark(sm);
	return;
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
	return;
}


/*
    DIAGNOSTICS FOR THE END OF A PROCEDURE
*/

void
xdb_diag_proc_end(diag_descriptor *di)
{
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
	return;
}


/*
    DIAGNOSTICS FOR THE START OF A VALUE
*/

void
xdb_diag_val_begin(diag_descriptor *di, char *pname, long cname, int is_ext)
{
	char *nm = di->data.id.nme.ints.chars;
	diag_type t = di->data.id.new_type;
	diag_globl_variable(t, nm, !is_local(pname), pname, 1);
	return;
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
			diag_type d = di[i].data.typ.new_type;
			char *nm = di[i].data.typ.nme.ints.chars;
			diag_type_defn(nm, d);
		}
	}
	return;
}


/*
    OUTPUT ALL DIAGNOSTIC TAGS
*/

static void
OUTPUT_DIAG_TAGS(void)
{
	return;
}


/*
    INSPECT FILENAME
*/

static void
INSPECT_FILENAME(filename fn)
{
	char *nm = fn->file.ints.chars;
	diag_source(nm, 1, 0);
	return;
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
	diag_descriptor *dx = x->dec_u.dec_val.diag_info;
	diag_descriptor *dy = y->dec_u.dec_val.diag_info;
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
		dec *nextx = x->def_next;
		dec *before = NULL;
		for (y = res; y != NULL; y = y->def_next) {
			if (!cmp_dec(x, y)) {
				break;
			}
			before = y;
		}
		if (before == NULL) {
			x->def_next = res;
			res = x;
		} else {
			x->def_next = before->def_next;
			before->def_next = x;
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
	NEW_DIAG_GLOBAL,
	OUTPUT_GLOBALS_TAB,
	OUTPUT_DIAG_TAGS,
	INSPECT_FILENAME
};

