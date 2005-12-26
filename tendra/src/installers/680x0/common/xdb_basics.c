/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1996
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


#include "config.h"
#include "common_types.h"
#include "codex.h"
#include "diag_fns.h"
#include "diagglob.h"
#include "instrs.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "mark_scope.h"
#include "output.h"
#include "xdb_types.h"
#include "xdb_basics.h"
#include "xdb_output.h"
#include "stab_types.h"


/*
 *    DIAGNOSTICS INITIALIZATION ROUTINE
 */

void
diag_prologue()
{
    init_diag ();
    return;
}


/*
 *    DIAGNOSTICS TERMINATION ROUTINE
 */

void
diag_epilogue()
{
    while (dnt_end ()) /* empty */;
    if (diag_format == DIAG_STAB) {
		mach_op *op = make_extern_data ("Letext", 0);
		area (ptext);
		make_stabs ("\"\"", 100, 0, op);
		make_external_label ("Letext");
    }
    output_all ();
    copy_diag ();
    return;
}


/*
 *    OUTPUT A DIAGNOSTICS SOURCE MARK
 */

static void
diag_mark(sourcemark *sm)
{
    char *nm = sm->file->file.ints.chars;
    long ln = sm->line_no.nat_val.small_nat;
    diag_source (nm, ln, 1);
    return;
}


/*
 *    DIAGNOSTICS FOR A LOCAL VARIABLE
 */

static void
diag_variable(diag_info *di, exp e)
{
    exp s = di->data.id_scope.access;
    diag_type t = di->data.id_scope.typ;
    char *nm = di->data.id_scope.nme.ints.chars;
    long p = (no (s) + no (son (s))) / 8;
    if (!isparam (son (s))) {
		diag_local_variable (t, nm, p);
    }
    return;
}


/*
 *    START OF A DIAGNOSTICS ITEM
 */

void
diag_start(diag_info *di, exp e)
{
    switch (di->key) {
		
	case DIAG_INFO_SOURCE : {
	    sourcemark *sm = &(di->data.source.beg);
	    diag_mark (sm);
	    break;
	}
		
	case DIAG_INFO_ID : {
	    mark_scope (e);
	    if (props (e) & 0x80) dnt_begin ();
	    if (diag_format != DIAG_XDB_NEW) diag_variable (di, e);
	    break;
	}
		
	default : {
	    break;
	}
    }
    return;
}


/*
 *    END OF A DIAGNOSTICS ITEM
 */

void
diag_end(diag_info *di, exp e)
{
    if (di->key == DIAG_INFO_ID) {
		if (diag_format == DIAG_XDB_NEW) diag_variable (di, e);
		if (props (e) & 0x80) dnt_end ();
    }
    return;
}


/*
 *    DIAGNOSTICS FOR THE START OF A PROCEDURE
 */

void
xdb_diag_proc_begin(diag_global *di, exp p,
					char *pname, long cname,
					int is_ext)
{
    char *nm = di->data.id.nme.ints.chars;
    diag_type t = di->data.id.new_type;
    sourcemark *sm = &(di->data.id.whence);
    diag_proc_main (t, p, nm, !is_local (pname), pname);
    diag_mark (sm);
    return;
}


/*
 *    DIAGNOSTICS FOR THE RETURN STATEMENT OF A PROCEDURE
 */

void
xdb_diag_proc_return ()
{
    if (diag_format == DIAG_XDB_NEW) slt_exit ();
    return;
}


/*
 *    DIAGNOSTICS FOR THE END OF A PROCEDURE
 */

void
xdb_diag_proc_end(diag_global *di)
{
    area (ptext);
    if (diag_format == DIAG_XDB_NEW) {
		mach_op *op1 = make_lab_data (crt_diag_proc_lab, 0);
		mach_op *op2 = make_extern_data (".-1", 0);
		make_instr (m_as_assign, op1, op2, 0);
    } else if (diag_format == DIAG_XDB_OLD) {
		make_label (crt_diag_proc_lab);
    }
    dnt_end ();
    area (plast);
    return;
}


/*
 *    DIAGNOSTICS FOR THE START OF A VALUE
 */

void
xdb_diag_val_begin(diag_global *di, char *pname,
				   long cname, int is_ext)
{
    char *nm = di->data.id.nme.ints.chars;
    diag_type t = di->data.id.new_type;
    diag_globl_variable (t, nm, !is_local (pname), pname, 1);
    return;
}


/*
 *    OUTPUT GLOBAL TABLE
 */

void
OUTPUT_GLOBALS_TAB()
{
    diag_descriptor *di = unit_diagvar_tab.array;
    unsigned long i, n = unit_diagvar_tab.lastused;
    for (i = 0 ; i < n ; i++) {
		if (di [i].key == DIAG_TYPEDEF_KEY) {
			diag_type d = di [i].data.typ.new_type;
			char *nm = di [i].data.typ.nme.ints.chars;
			diag_type_defn (nm, d);
		}
    }
    return;
}


/*
 *    OUTPUT ALL DIAGNOSTIC TAGS
 */

void
OUTPUT_DIAG_TAGS()
{
    return;
}


/*
 *    INSPECT FILENAME
 */

void
INSPECT_FILENAME(filename fn)
{
    char *nm = fn->file.ints.chars;
    diag_source (nm, 1, 0);
    return;
}


/*
 *    COMPARE TWO DECLARATIONS
 */

static bool
cmp_dec(dec *x, dec *y)
{
    int c;
    long lx, ly;
    char *fx, *fy;
    sourcemark *sx, *sy;
    diag_global *dx = x->dec_u.dec_val.diag_info;
    diag_global *dy = y->dec_u.dec_val.diag_info;
    if (dy == null || dy->key != DIAG_ID_KEY) return (0);
    if (dx == null || dx->key != DIAG_ID_KEY) return (1);
    sx = &(dx->data.id.whence);
    fx = sx->file->file.ints.chars;
    lx = sx->line_no.nat_val.small_nat;
    sy = &(dy->data.id.whence);
    fy = sy->file->file.ints.chars;
    ly = sy->line_no.nat_val.small_nat;
    c = strcmp ((char*)sx, (char*)sy);
    if (c < 0) return (0);
    if (c > 0) return (1);
    return (lx > ly ? 1 : 0);
}


/*
 *    SORT DECLARATION INTO ORDER
 */

dec
*sort_decs(dec *p)
{
    dec *res = null;
    dec *x = p, *y;
    while (x != null) {
		dec *nextx = x->def_next;
		dec *before = null;
		for (y = res ; y != null ; y = y->def_next) {
			if (!cmp_dec (x, y)) break;
			before = y;
		}
		if (before == null) {
			x->def_next = res;
			res = x;
		} else {
			x->def_next = before->def_next;
			before->def_next = x;
		}
		x = nextx;
    }
    return (res);
}
