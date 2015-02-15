/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <string.h>

#include <shared/error.h>

#include <reader/exp.h>

#include <construct/installtypes.h>
#include <construct/exp.h>
#include <construct/tags.h>

#include <main/flags.h>
#include <main/driver.h>
#include <main/print.h>

#include <diag3/dg_first.h>
#include <diag3/diaginfo.h>
#include <diag3/dg_types.h>		/* TDF_DIAG4 */
#include <diag3/diagtypes.h>		/* TDF_DIAG3 */
#include <diag3/diaginfo1.h>

#include "assembler.h"
#include "codex.h"
#include "instrs.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "output.h"
#include "utility.h"
#include "xdb_types.h"
#include "xdb_output.h"
#include "stab_types.h"


/*
    WORK OUT WHETHER TO DO A DYNAMIC TEST FOR DIAGNOSTIC FORMAT
    TODO: ...which is overkill, and probably ought to be removed
*/

#ifdef dynamic_test
extern double atof(const char *);
#include <sys/utsname.h>
#endif


/*
    This array gives information on all the available diagnostic directives,
    included those which are unused.
*/

diag_directive dd[] = {
    { m_dd_array, 2, 2 },
    { m_dd_begin, 1, 1 },
    { m_dd_const, 0, 0 },	/* unknown */
    { m_dd_dvar, 2, 2 },
    { m_dd_end, 1, 1 },
    { m_dd_entry, 0, 0 },	/* unknown */
    { m_dd_enum, 1, 1 },
    { m_dd_field, 2, 2 },
    { m_dd_file, 0, 0 },	/* unknown */
    { m_dd_fparam, 2, 2 },
    { m_dd_function, 3, 3 },
    { m_dd_functype, 2, 2 },
    { m_dd_import, 0, 0 },	/* unknown */
    { m_dd_label, 0, 0 },	/* unknown */
    { m_dd_memenum, 2, 2 },
    { m_dd_module, 1, 2 },
    { m_dd_pointer, 1, 1 },
    { m_dd_set, 0, 0 },		/* unknown */
    { m_dd_srcfile, 1, 1 },
    { m_dd_struct, 2, 2 },
    { m_dd_subrange, 2, 2 },
    { m_dd_svar, 2, 2 },
    { m_dd_tagdef, 1, 1 },
    { m_dd_typedef, 1, 1 },
    { m_dd_union, 1, 1 },
    { m_dd_variant, 0, 0 }	/* unknown */
};


/*
    There are three sections of diagnostic information in the new
    diagnostics mode (the vt, lntt and gntt sections).  One temporary
    file is used for each.  In the TDF_DIAG3 diagnosics mode there is
    only one section (the dntt section), and only one file, diagfp2,
    is used.
*/

static FILE *diagfp1;
static FILE *diagfp2;
static FILE *diagfp3;


/*
    The temporary files are opened, and the headings of the various
    sections are printed.
*/

void init_diag
(void)
{
#ifdef dynamic_test
    double vs = (diag == DIAG_XDB_NEW ? 7.40 : 7.05);

    struct utsname u;
    char *os = "HP-UX";
    uname(&u);
    os = u.sysname;
    vs = atof(u.release);
    if (strcmp(os, "HP-UX") == 0) {
	diag = (vs >= 7.40 ? DIAG_XDB_NEW : DIAG_XDB_OLD);
    } else {
	error(ERR_INTERNAL, "diagnostic format not recognised");
	exit(1);
   }
#endif

    switch (diag) {

	case DIAG_STABS: {
	    /* Temporary files not used */
	    break;
	}

	case DIAG_XDB_NEW: {
	    diagfp1 = tmpfile();
	    diagfp2 = tmpfile();
	    diagfp3 = tmpfile();
	    if (diagfp1 == NULL || diagfp2 == NULL || diagfp3 == NULL) {
		error(ERR_FATAL, "Can't open temporary diagnostics file");
	    }
	    asm_fprintf(diagfp1, "%s\n", instr_names[m_as_data]);
	    asm_fprintf(diagfp1, "%s\n", instr_names[m_dd_vt]);
	    asm_fprintf(diagfp2, "%s\n", instr_names[m_dd_lntt]);
	    asm_fprintf(diagfp3, "%s\n", instr_names[m_dd_gntt]);
	    break;
	}

	case DIAG_XDB_OLD: {
	    diagfp2 = tmpfile();
	    if (diagfp2 == NULL) {
		error(ERR_FATAL, "Can't open temporary diagnostics file");
	    }
	    asm_fprintf(diagfp2, "%s\n", instr_names[m_as_data]);
	    asm_fprintf(diagfp2, "%s\n", instr_names[m_dd_start]);
	    break;

	default:
		error(ERR_SERIOUS, "unsupported assembler dialect");
	}
    }
}


/*
    The the file is copied to the main output file, as_file.
*/

static void copy_diag_file
(FILE *file)
{
    int c;
    rewind(file);
    while (c = getc(file), c != EOF)putc(c, as_file);
    fclose(file);
}


/*
    This flag is true if a newline has just been output in the vt area.
*/

static int vt_newline = 1;


/*
    All the diagnostic files are copied to the main output file.
*/

void copy_diag
(void)
{
    if (diag == DIAG_XDB_NEW) {
	if (vt_newline) {
	    asm_fprintf(diagfp1, "%s0\n", instr_names[m_dd_vtbytes]);
	} else {
	    asm_fprintf(diagfp1, ",0\n");
	}
	copy_diag_file(diagfp1);
	copy_diag_file(diagfp2);
	copy_diag_file(diagfp3);
    } else if (diag == DIAG_XDB_OLD) {
	copy_diag_file(diagfp2);
    }
}


/*
    Diagnostic strings (eg. procedure and variable names) are dealt with
    differently in the two formats.  In the old format they are output
    direct, in the new they are added to the vt table and the offset
    from the start of the table is used.
*/

void diag_string
(FILE *file, char *s)
{
    if (diag == DIAG_XDB_NEW) {
	static int vtposn = 0;
	static int vtwidth = 0;
	if (vt_newline) {
	    asm_fprintf(diagfp1, "%s0", instr_names[m_dd_vtbytes]);
	    vt_newline = 0;
	} else {
	    asm_fprintf(diagfp1, ",0");
	}
	vtposn++;
	vtwidth++;
	asm_fprintf(file, "%d", vtposn);
	for (; *s; s++) {
	    if (vt_newline) {
		asm_fprintf(diagfp1, "%s%d", instr_names[m_dd_vtbytes], *s);
		vt_newline = 0;
	    } else {
		asm_fprintf(diagfp1, ",%d", *s);
	    }
	    vtposn++;
	    vtwidth++;
	    if (vtwidth > 12) {
		asm_fprintf(diagfp1, "\n");
		vt_newline = 1;
		vtwidth = 0;
	    }
	}
    } else {
	asm_fprintf(file, "\"%s\"", s);
    }
}


/*
    These variables record the current position in the source file.
*/

char *crt_fname = "";
long crt_line_num = -1;


/*
    A count of the number of slt instructions is maintained.
*/

static int slt_num = 0;


/*
    An sltspecial instruction is output.  This goes straight into the
    main output file.
*/

static void slt_special
(int t, posn_t p)
{
    mach_op *op1, *op2, *op3;
    area(ptext);
    op1 = make_int_data(t);
    op2 = make_int_data(crt_line_num);
    op3 = make_hex_data(p);
    op1->of = op2;
    op2->of = op3;
    make_instr(m_dd_special, op1, NULL, 0);
    area(plast);
    slt_num++;
}


/*
    An sltnormal instruction is output.  This goes straight into the
    main output file.
*/

static void slt_normal
(void)
{
    mach_op *op;
    area(ptext);
    op = make_int_data(crt_line_num);
    if (diag == DIAG_STABS) {
	mach_op *op1 = make_int_data(68);
	op1->of = make_int_data(0);
	op1->of->of = op;
	make_instr(m_stabd, op1, NULL, 0);
    } else {
	make_instr(m_dd_normal, op, NULL, 0);
    }
    area(plast);
    slt_num++;
}


/*
    An sltexit instruction is output (new format only).
*/

void slt_exit
(void)
{
    mach_op *op;
    area(ptext);
    op = make_int_data(crt_line_num);
    make_instr(m_dd_exit, op, NULL, 0);
    area(plast);
    slt_num++;
}


/*
    OUTPUT A DNT BEGIN INSTRUCTION
*/

void dnt_begin
(void)
{
    if (diag == DIAG_STABS) {
	long lab = next_lab();
	make_label(lab);
	push_dscope((posn_t)lab, 0);
    } else {
	posn_t p = out_dd(diagfp2, xdb_begin, 1);
	push_dscope(p, 4);
	if (diag == DIAG_XDB_NEW)asm_fprintf(diagfp2, "0,");
	asm_fprintf(diagfp2, "%d\n", slt_num);
	slt_special(5, p);
    }
}


/*
    OUTPUT A DNT END INSTRUCTION
*/

int dnt_end
(void)
{
    dscope *d = pop_dscope();
    if (d == NULL) return 0;
    if (diag == DIAG_STABS) {
	long lab1 = (long)d->posn;
	long lab2 = next_lab();
	make_label(lab2);
	make_stabn(192, lab1);
	make_stabn(224, lab2);
    } else {
	posn_t p = out_dd(diagfp2, xdb_end, 1);
	if (diag == DIAG_XDB_NEW) {
	    asm_fprintf(diagfp2, "%d,0,", d->dscope_type);
	}
	asm_fprintf(diagfp2, "%d,0x%x\n", slt_num,
		 (unsigned int)d->posn);
	slt_special(6, p);
    }
    return 1;
}


/*
    FLAG FOR MODULE NAME
*/

static bool have_module = 0;


/*
    This routine output the necessary instructions to indicate a change
    of source file.
*/

void diag_source_file
(char *nm, long ln)
{
    if (diag == DIAG_STABS) {
	int n = strlen(nm) + 3;
	char *qnm = alloc_nof(char, n);
	mach_op *op = make_extern_data("Ltext", 0);
	sprintf(qnm, "\"%s\"", nm);
	make_stabs(qnm,(have_module ? 132 : 100), 0L, op);
	if (!have_module) {
	    make_external_label("Ltext");
	    init_stab_types();
	    have_module = 1;
	}
	crt_fname = nm;
	crt_line_num = ln;
    } else {
	posn_t x = out_dd(diagfp2, xdb_srcfile, 1);
	asm_fprintf(diagfp2, "1,");
	diag_string(diagfp2, nm);
	asm_fprintf(diagfp2, ",%d\n", slt_num);
	crt_fname = nm;
	crt_line_num = ln;
	make_instr(m_dd_align, NULL, NULL, 0);
	slt_special(1, x);
	if (!have_module) {
	    x = out_dd(diagfp2, xdb_module, 1);
	    if (diag == DIAG_XDB_NEW) {
		asm_fprintf(diagfp2, "0,0");
	    } else {
		diag_string(diagfp2, nm);
	    }
	    asm_fprintf(diagfp2, ",%d\n", slt_num);
	    push_dscope(x, 1);
	    slt_special(2, x);
	    have_module = 1;
	}
    }
}


/*
    This routine outputs an instruction indicating the position within
    the source file.
*/

void diag_source
(char *nm, long ln, int d)
{
    if (have_module && d == 0) return;
    if (!eq(nm, crt_fname))diag_source_file(nm, ln);
    crt_line_num = ln;
    if (d)slt_normal();
}


/*
    CURRENT DIAGNOSTICS PROCEDURE LABEL
*/

long crt_diag_proc_lab;


/*
    DIAGNOSTICS FOR A PROCEDURE
*/

void diag_proc_main
(diag_type dt, exp e, char *id, int is_glob, char *val)
{
    exp a;
    posn_t t;
    long fp;
    table_posn *p;
    diag_type dtl;

    /* Analyse result sort */
    if (dt->key != DIAG_TYPE_PROC) {
	error(ERR_SERIOUS, "Illegal procedure type");
	return;
    }
    dtl = dt->data.proc.result_type;

    if (diag == DIAG_STABS) {
	mach_op *op = make_extern_data(val, 0);
	char *st = analyse_stab_type(dtl, id,(is_glob ? "F" : "f"));
	make_stabs(st, 36, crt_line_num, op);
	dnt_begin();
    } else {
	p = analyse_diag_type(diagfp2, dtl, 1);

	/* Create diagnostics procedure label */
	crt_diag_proc_lab = next_lab();

	/* Output function diagnostic directive */
	t = out_dd(diagfp2, xdb_function, 1);
	asm_fprintf(diagfp2, "%d,1,", is_glob);
	if (diag == DIAG_XDB_NEW)asm_fprintf(diagfp2, "0,0,0,0,0,");
	diag_string(diagfp2, id);
	if (strcmp(id, "main") == 0) {
	    asm_fprintf(diagfp2, ",");
	    diag_string(diagfp2, "_MAIN_");
	    asm_fprintf(diagfp2, ",");
	} else {
	    asm_fprintf(diagfp2, ",0,");
	}
	fp = ftell(diagfp2);
	asm_fprintf(diagfp2, "%s,%d,%s,", NULL_POSN_STR, slt_num, val);
	out_posn(diagfp2, p, 1);
	if (diag == DIAG_XDB_NEW)asm_fprintf(diagfp2, "%s,", val);
	asm_fprintf(diagfp2, "L%ld\n", crt_diag_proc_lab);

	/* Start new diagnostic scope */
	push_dscope(t, 2);
	slt_special(3, t);
    }

    /* Step over actual procedure arguments */
    a = son(e);
    while (name(a) == ident_tag /* && isparam(a) */ ) {
	a = bro(son(a));
    }

    /* Read procedure argument definitions */
    while (name(a) == diagnose_tag) {
	diag_info *di = dno(a);
	if (di->key == DIAG_INFO_ID) {
	    exp ps = di->data.id_scope.access;
	    if (isparam(son(ps))) {
		diag_type pdt = di->data.id_scope.typ;
		char *pnm = di->data.id_scope.nme.ints.chars;
		long off = 8 + (no(ps) + no(son(ps))) / 8;
		if (diag == DIAG_STABS) {
		    mach_op *op = make_int_data(off);
		    char *st = analyse_stab_type(pdt, pnm, "p");
		    make_stabs(st, 160, 0L, op);
		} else {
		    p = analyse_diag_type(diagfp2, pdt, 1);
		    t = out_dd(diagfp2, xdb_fparam, 1);
		    fill_gap(diagfp2, fp, t);
		    if (diag == DIAG_XDB_NEW) {
			asm_fprintf(diagfp2, "0,0,0,0,0,");
		    } else {
			asm_fprintf(diagfp2, "0,0,");
		    }
		    if (*pnm) {
			diag_string(diagfp2, pnm);
		    } else {
			diag_string(diagfp2, "__unknown");
		    }
		    asm_fprintf(diagfp2, ",%ld,", off);
		    out_posn(diagfp2, p, 1);
		    fp = ftell(diagfp2);
		    if (diag == DIAG_XDB_NEW) {
			asm_fprintf(diagfp2, "%s,0\n", NULL_POSN_STR);
		    } else {
			asm_fprintf(diagfp2, "%s\n", NULL_POSN_STR);
		    }
		}
	    }
	}
	a = son(a);
    }
}


/*
    DIAGNOSTICS FOR A GLOBAL IDENTIFIER
*/

void diag_globl_variable
(diag_type dt, char *id, int is_glob, char *val, int has_def)
{
    if (diag == DIAG_STABS) {
	if (is_glob) {
	    char *st = analyse_stab_type(dt, id, "G");
	    make_stabs(st, 32, crt_line_num, NULL);
	} else {
	    mach_op *op = make_extern_data(val, 0);
	    char *st = analyse_stab_type(dt, id, "S");
	    make_stabs(st, 38, crt_line_num, op);
	}
    } else {
	int loc;
	FILE *file;
	table_posn *x;
	if (diag == DIAG_XDB_NEW) {
	    loc = (is_glob ? 0 : 1);
	    file = (is_glob ? diagfp3 : diagfp2);
	} else {
	    loc = 1;
	    file = diagfp2;
	}
	x = analyse_diag_type(file, dt, loc);
	(void)out_dd(file, xdb_svar, loc);
	if (diag == DIAG_XDB_NEW) {
	    asm_fprintf(file, "%d,0,0,0,0,", is_glob);
	} else {
	    asm_fprintf(file, "%d,0,", is_glob);
	}
	diag_string(file, id);
	if (has_def) {
	    asm_fprintf(file, ",%s,", val);
	} else {
	    asm_fprintf(file, ",-1,");
	}
	out_posn(file, x, 1);
	asm_fprintf(file, "0,0\n");
    }
}


/*
    DIAGNOSTICS FOR A LOCAL IDENTIFIER
*/

void diag_local_variable
(diag_type dt, char *id, long fp)
{
    if (diag == DIAG_STABS) {
	mach_op *op = make_int_data(-fp);
	char *st = analyse_stab_type(dt, id, "l");
	make_stabs(st, 128, crt_line_num, op);
    } else {
	table_posn *x = analyse_diag_type(diagfp2, dt, 1);
	(void)out_dd(diagfp2, xdb_dvar, 1);
	if (diag == DIAG_XDB_NEW) {
	    asm_fprintf(diagfp2, "0,0,0,0,");
	} else {
	    asm_fprintf(diagfp2, "0,0,0,");
	}
	diag_string(diagfp2, id);
	asm_fprintf(diagfp2, ",%ld,", -fp);
	if (diag == DIAG_XDB_NEW) {
	    out_posn(diagfp2, x, 1);
	    asm_fprintf(diagfp2, "0\n");
	} else {
	    out_posn(diagfp2, x, 0);
	}
    }
}


/*
    DIAGNOSTICS FOR A TYPE DEFINITION
*/

void diag_type_defn
(char *nm, diag_type dt)
{
    switch (dt->key) {

	case DIAG_TYPE_UNINIT:
	case DIAG_TYPE_INITED: {
	    /* Ignore unused types */
	    break;
	}

	default : {
	    if (diag == DIAG_STABS) {
		char *st = analyse_stab_type(dt, nm, "t");
		make_stabs(st, 128, 1L, NULL);
	    } else {
		int loc = (diag == DIAG_XDB_NEW ? 0 : 1);
		FILE *file = (loc ? diagfp2 : diagfp3);
		table_posn *p = analyse_diag_type(file, dt, loc);
		(void)out_dd(file, xdb_typedef, loc);
		asm_fprintf(file, "0,");
		diag_string(file, nm);
		asm_fprintf(file, ",");
		out_posn(file, p, 0);
	    }
	    break;
	}
    }
}
