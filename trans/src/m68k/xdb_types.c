/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <time.h>
#include <stdio.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/xalloc.h>

#include <tdf/nat.h>
#include <tdf/shape.h>

#include <reader/externs.h>

#include <utility/bits.h>

#include <main/flags.h>
#include <main/print.h>

#include "instrs.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "output.h"
#include "xdb_output.h"
#include "xdb_types.h"
#include "assembler.h"


/*
    GENERATE A UNIQUE IDENTIFIER
*/

static unsigned
unique_id(void)
{
	static unsigned u = 0;
	if (u == 0) {
		time_t t = time((time_t *)NULL);
		u = (unsigned)t;
	}
	return u;
}


/*
    CURRENT POSITIONS IN DIAGNOSTIC NAME TABLES
*/

static posn_t dtposn_local = LOCAL_POSN;
static posn_t dtposn_globl = GLOBL_POSN;


/*
    OUTPUT A DIAGNOSTIC DIRECTIVE
*/

posn_t
out_dd(FILE *file, int n, int loc)
{
	diag_directive *d = dd + n;
	long sz = (diag == DIAG_XDB_NEW ? d->new_size : d->old_size);
	posn_t p = (loc ? dtposn_local : dtposn_globl);
	asm_fprintf(file, "%s", instr_names[d->instr]);
	if (loc) {
		dtposn_local = p + sz;
	} else {
		dtposn_globl = p + sz;
	}
	return p;
}


/*
     CREATE A NEW TABLE POSITION
*/

static table_posn *
new_table_posn(posn_t n, long sz)
{
	table_posn *p;
	static int no_tp_free = 0;
	static table_posn *tp_free;
	if (no_tp_free == 0) {
		no_tp_free = 20;
		tp_free = xmalloc_nof(table_posn, no_tp_free);
	}
	p = tp_free++;
	no_tp_free--;
	p->is_lab = false;
	p->posn = n;
	p->size = sz;
	return p;
}


/*
    OUTPUT A TABLE POSITION
*/

void
out_posn(FILE *file, table_posn *p, int comma)
{
	if (p->is_lab) {
		asm_fprintf(file, "LD%d",(int)p->posn);
	} else {
		asm_fprintf(file, "0x%x",(unsigned int)p->posn);
	}
	asm_fprintf(file, "%c", comma ? ',' : '\n');
}


/*
    GO TO A POSITION IN A FILE AND PRINT A TABLE POSITION
*/

void
fill_gap(FILE *file, long fp, posn_t t)
{
	long fp_old = ftell(file);
	if (fseek(file, fp, SEEK_SET) == -1) {
		error(ERR_SERIOUS, "Internal file seek error");
		return;
	}
	asm_fprintf(file, "0x%x", (unsigned int)t);
	if (fseek(file, fp_old, SEEK_SET) == -1) {
		error(ERR_SERIOUS, "Internal file seek error");
	}
}


/*
    CURRENT DIAGNOSTICS LABEL NUMBER
*/

static long diag_lab = 0;


/*
    FIND THE TABLE POSITION OF A TDF SHAPE
*/

static table_posn *
analyse_diag_shape(FILE *file, shape sha)
{
	posn_t t;
	long sz;

	UNUSED(file);

	t = NULL_POSN;
	sz = shape_size(sha);
	switch (sha->tag) {
	case scharhd:
		t = CHAR_POSN + sz;
		break;
	case swordhd:
	case slonghd:
		t = SIGNED_POSN + sz;
		break;
	case ucharhd:
	case uwordhd:
	case ulonghd:
		t = UNSIGNED_POSN + sz;
		break;
	case shrealhd:
	case realhd:
	case doublehd:
		t = FLOATING_POSN + sz;
		break;
	}
	return new_table_posn(t, sz);
}


/*
    FIND THE TABLE POSITION OF A DIAGNOSTIC TYPE
*/

table_posn *
analyse_diag_type(FILE *file, diag_type dt, int loc)
{
	table_posn *res;
	if (dt->been_outed) {
		return (table_posn *)dt->been_outed;
	}

	switch (dt->key) {
	case DIAG_TYPE_ARRAY: {
		diag_type dtl = dt->data.array.element_type;
		long lo = no(dt->data.array.lower_b);
		long hi = no(dt->data.array.upper_b);

		table_posn *p = analyse_diag_type(file, dtl, loc);
		long sz = (hi - lo + 1)*(p->size);
		posn_t s, t = out_dd(file, xdb_subrange, loc);

		if (diag == DIAG_XDB_NEW) {
			asm_fprintf(file, "0,0,");
		}
		asm_fprintf(file, "%ld,%ld,0x%x,32\n", lo, hi,
			(unsigned int)(SIGNED_POSN + 32));
		s = out_dd(file, xdb_array, loc);
		if (diag == DIAG_XDB_NEW) {
			asm_fprintf(file, "0,0,0,0,0,0,");
		}
		asm_fprintf(file, "0,%ld,0x%x,", sz,(unsigned int)t);
		if (diag == DIAG_XDB_NEW) {
			out_posn(file, p, 1);
			asm_fprintf(file, "%ld\n", p->size);
		} else {
			out_posn(file, p, 0);
		}
		res = new_table_posn(s, sz);
		break;
	}
	case DIAG_TYPE_BITFIELD: {
		long sz = dt->data.bitfield.no_of_bits.nat_val.small_nat;
		res = new_table_posn(SIGNED_POSN + 32, sz);
		break;
	}
	case DIAG_TYPE_ENUM: {
		char *nm = dt->data.t_enum.name.ints.chars;
		enum_values *fld = dt->data.t_enum.values->array;
		long i, n = (long)dt->data.t_enum.values->lastused;

		/* Initialize enumeration information */
		long fp;
		posn_t t;
		t = out_dd(file, xdb_enum, loc);
		fp = ftell(file);
		asm_fprintf(file, "%s,32\n", NULL_POSN_STR);
		res = new_table_posn(t, 32L);

		/* Deal with enumeration members */
		for (i = n - 1; i >= 0; i--) {
			char *fnm = fld[i] ->name.ints.chars;
			long v = no(fld[i] ->val);
			posn_t s = out_dd(file, xdb_memenum, loc);
			fill_gap(file, fp, s);
			if (diag == DIAG_XDB_NEW) {
				asm_fprintf(file, "0,");
			}
			if (*fnm) {
				diag_string(file, fnm);
			} else {
				diag_string(file, "__unknown");
			}
			asm_fprintf(file, ",%ld,", v);
			fp = ftell(file);
			asm_fprintf(file, "%s\n", NULL_POSN_STR);
		}

		/* Round off enumeration definition */
		if (*nm) {
			IGNORE out_dd(file, xdb_tagdef, loc);
			asm_fprintf(file, "0,");
			if (diag == DIAG_XDB_NEW) {
				asm_fprintf(file, "1,");
			}
			diag_string(file, nm);
			asm_fprintf(file, ",");
			out_posn(file, res, 0);
		}
		break;
	}
	case DIAG_TYPE_FLOAT: {
		shape sha = f_floating(dt->data.f_var);
		res = analyse_diag_shape(file, sha);
		break;
	}
	case DIAG_TYPE_LOC: {
		diag_type dtl = dt->data.loc.object;
		res = analyse_diag_type(file, dtl, loc);
		break;
	}
	case DIAG_TYPE_NULL:
		res = new_table_posn(NULL_POSN, 0L);
		break;
	case DIAG_TYPE_PROC: {
		diag_type dtl = dt->data.proc.result_type;
		table_posn *p = analyse_diag_type(file, dtl, loc);
		posn_t t = out_dd(file, xdb_functype, loc);
		if (diag == DIAG_XDB_NEW) {
			asm_fprintf(file, "0,0,");
		}
		asm_fprintf(file, "32,");
		out_posn(file, p, 1);
		asm_fprintf(file, "%s\n", NULL_POSN_STR);
		res = new_table_posn(t, 32L);
		break;
	}
	case DIAG_TYPE_PTR: {
		diag_type dtl = dt->data.ptr.object;
		table_posn *p = analyse_diag_type(file, dtl, loc);
		posn_t t = out_dd(file, xdb_pointer, loc);
		out_posn(file, p, 1);
		asm_fprintf(file, "32\n");
		res = new_table_posn(t, 32L);
		break;
	}
	case DIAG_TYPE_STRUCT: {
		shape sha = dt->data.t_struct.tdf_shape;
		long sz = shape_size(sha);
		char *nm = dt->data.t_struct.name.ints.chars;
#if 0
		struct_fields *fld = dt->data.t_struct.fields->array;
#else
		diag_field *fld = dt->data.t_struct.fields->array;
#endif
		long i, n = (long)dt->data.t_struct.fields->lastused;

		/* Initialize structure information */
		long fp;
		posn_t t;
		int taglab = 0;
		char nmbuff[50];
		long dlab = diag_lab++;
		if (diag == DIAG_XDB_NEW) {
			if (*nm == 0) {
				unsigned u = unique_id();
				nm = nmbuff;
				sprintf(nm, "(%u.%ld)", u, dlab);
			}
			taglab = 1;
		}
		if (!taglab) {
			asm_fprintf(file, "LD%ld:", dlab);
		}
		t = out_dd(file, xdb_struct, loc);
		asm_fprintf(file, "0,");
		fp = ftell(file);
		asm_fprintf(file, "%s,%s,%s,%ld\n", NULL_POSN_STR, NULL_POSN_STR,
			NULL_POSN_STR, sz);
		res = new_table_posn(t, sz);

		/* Print tag information */
		if (*nm) {
			posn_t tt;
			if (taglab) {
				asm_fprintf(file, "LD%ld:", dlab);
			}
			tt = out_dd(file, xdb_tagdef, loc);
			asm_fprintf(file, "0,");
			if (diag == DIAG_XDB_NEW) {
				asm_fprintf(file, "1,");
			}
			diag_string(file, nm);
			asm_fprintf(file, ",");
			out_posn(file, res, 0);
			if (taglab) {
				t = tt;
			}
		}

		/* Set up structure label */
		res->is_lab = true;
		res->posn = (posn_t)dlab;
		dt->been_outed = res;

		/* Deal with structure fields */
		for (i = n - 1; i >= 0; i--) {
			char *fnm = fld[i] ->field_name.ints.chars;
			long off = no(fld[i] ->where);
			diag_type dtl = fld[i] ->field_type;
			table_posn *q = analyse_diag_type(file, dtl, loc);
			posn_t s = out_dd(file, xdb_field, loc);
			fill_gap(file, fp, s);
			if (diag == DIAG_XDB_NEW) {
				asm_fprintf(file, "0,0,");
			}
			if (*fnm) {
				diag_string(file, fnm);
			} else {
				diag_string(file, "__unknown");
			}
			asm_fprintf(file, ",%ld,", off);
			out_posn(file, q, 1);
			asm_fprintf(file, "%ld,", q->size);
			fp = ftell(file);
			asm_fprintf(file, "%s\n", NULL_POSN_STR);
		}

		/* Round off structure definition */
		res->is_lab = false;
		res->posn = t;
		break;
	}
	case DIAG_TYPE_UNION: {
		shape sha = dt->data.t_union.tdf_shape;
		long sz = shape_size(sha);
		char *nm = dt->data.t_union.name.ints.chars;
#if 0
		union_fields *fld = dt->data.t_union.fields->array;
#else
		diag_field *fld = dt->data.t_union.fields->array;
#endif
		long i, n = (long)dt->data.t_union.fields->lastused;

		/* Initialize union information */
		long fp;
		posn_t t;
		int taglab = 0;
		long dlab = diag_lab++;
		char nmbuff[50];
		if (diag == DIAG_XDB_NEW) {
			if (*nm == 0) {
				unsigned u = unique_id();
				nm = nmbuff;
				sprintf(nm, "(%u.%ld)", u, dlab);
			}
			taglab = 1;
		}
		if (!taglab) {
			asm_fprintf(file, "LD%ld:", dlab);
		}
		t = out_dd(file, xdb_union, loc);
		fp = ftell(file);
		asm_fprintf(file, "%s,%ld\n", NULL_POSN_STR, sz);
		res = new_table_posn(t, sz);

		/* Print tag information */
		if (*nm) {
			posn_t tt;
			if (taglab) {
				asm_fprintf(file, "LD%ld:", dlab);
			}
			tt = out_dd(file, xdb_tagdef, loc);
			asm_fprintf(file, "0,");
			if (diag == DIAG_XDB_NEW) {
				asm_fprintf(file, "1,");
			}
			diag_string(file, nm);
			asm_fprintf(file, ",");
			out_posn(file, res, 0);
			if (taglab) {
				t = tt;
			}
		}

		/* Set up union label */
		res->is_lab = true;
		res->posn = (posn_t)dlab;
		dt->been_outed = res;

		/* Deal with union fields */
		for (i = n - 1; i >= 0; i--) {
			char *fnm = fld[i] ->field_name.ints.chars;
			long off = no(fld[i] ->where);
			diag_type dtl = fld[i] ->field_type;
			table_posn *q = analyse_diag_type(file, dtl, loc);
			posn_t s = out_dd(file, xdb_field, loc);
			fill_gap(file, fp, s);
			if (diag == DIAG_XDB_NEW) {
				asm_fprintf(file, "0,0,");
			}
			if (*fnm) {
				diag_string(file, fnm);
			} else {
				diag_string(file, "__unknown");
			}
			asm_fprintf(file, ",%ld,", off);
			out_posn(file, q, 1);
			asm_fprintf(file, "%ld,", q->size);
			fp = ftell(file);
			asm_fprintf(file, "%s\n", NULL_POSN_STR);
		}

		/* Round off union definition */
		res->is_lab = false;
		res->posn = t;
		break;
	}

	case DIAG_TYPE_VARIETY: {
		shape sha = f_integer(dt->data.var);
		res = analyse_diag_shape(file, sha);
		break;
	}

	default:
		res = new_table_posn(NULL_POSN, 0L);
		break;
	}

	dt->been_outed = res;
	return res;
}


/*
    DIAGNOSTIC SCOPE STACK
*/

static dscope *dscope_stack = NULL;
static int no_dscope = 0;
static int dscope_stk_size = 0;


/*
    PUSH A DIAGNOSTICS SCOPE
*/

void
push_dscope(posn_t p, int t)
{
	int n = no_dscope++;
	if (n >= dscope_stk_size) {
		dscope_stk_size += 20;
		dscope_stack = xrealloc_nof(dscope_stack, dscope, dscope_stk_size);
	}
	dscope_stack[n].posn = p;
	dscope_stack[n].dscope_type = t;
}


/*
    POP A DIAGNOSTICS SCOPE
*/

dscope *
pop_dscope(void)
{
	int n = no_dscope;
	if (n == 0) {
		return NULL;
	}
	no_dscope = (--n);
	return dscope_stack + n;
}
