/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/xalloc.h>

#include <tdf/nat.h>
#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/token.h>
#include <reader/externs.h>
#include <reader/basicread.h>

#include <local/al.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/exp.h>
#include <construct/installglob.h>

#include <main/driver.h>
#include <main/flags.h>
#include <main/print.h>

#include "addr.h"
#include "procrec.h"
#include "bits.h"
#include "locate.h"
#include "translate.h"
#include "stabs_diag4.h"

#include <diag4/dg_types.h>
#include <diag4/dg_aux.h>
#include <diag4/diagglob.h>
#include <diag4/diag_reform.h>

extern bool last_param(exp);

static void stab_file(dg_filename);
static void stab_scope_open(dg_filename);
static void stab_scope_close(void);
static void out_dt_shape(dg_type);
static void stab_local(dg_name, int);

static FILE *dg_file;

/* label number sequence independent from text code */
static int diag_lab_no = 0;

static int
next_d_lab(void)
{
	return ++diag_lab_no;
}

#define STAB_SCHAR	4
#define STAB_UCHAR	6
#define STAB_SSHRT	2
#define STAB_USHRT	3
#define STAB_SLONG	7
#define STAB_ULONG	9
#define STAB_SINT	1
#define STAB_UINT	8
#define STAB_FLOAT	10
#define STAB_DBL	11
#define STAB_LDBL	12
#define STAB_VOID	13
#define STAB_S64	14
#define STAB_U64	15
#define STAB_VS		16
#define NO_STABS	17

static long stab_ptrs[NO_STABS] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*
 * CURRENT TYPE NUMBER
 */
static long typeno;

/*
 * SIZE OF LAST STAB TYPE OUTPUT
 */
static long last_type_sz = 0;

long currentlno = -1;

dg_filename currentfile = NULL;
dg_filename prim_file   = NULL;

static long *type_sizes;
static int total_type_sizes = 0;

#define set_stab_size(i)	type_sizes[(i)] = last_type_sz
#define get_stab_size(i)	(type_sizes[(i)])
#define shape_stab_size(i, s)	type_sizes[(i)] = shape_size(s)

/*
 * GET THE NEXT TYPE NUMBER
 */
static long
next_typen(void)
{
	if (typeno >= total_type_sizes) {
		int i, n = total_type_sizes, m = n + 100;

		type_sizes = xrealloc(type_sizes, m * sizeof *type_sizes);
		for (i = n; i < m; i++) {
			type_sizes[i] = 0;
		}

		total_type_sizes = m;
	}

	return typeno++;
}

/* solaris stores line no's relative to the start of the procedure, so
   remember the name */
static char *last_proc_lab = "<<No Proc>>";

/*
 * OUTPUT A FILE POSITION CONSTRUCT
 */
#define N_SLINE  0x44
#define N_DSLINE 0x46
#define N_BSLINE 0x48
#define N_LBRAC  0xc0
#define N_RBRAC  0xe0

static void
stabd(dg_filename f, long lno, int seg)
{
	long i;

	if (f == currentfile && lno == currentlno) {
		return;
	}

	stab_file(f);

	if (seg != 0) { /* 0 suppresses always */
		if (seg > 0) { /* -ve line nos are put out in the stabs */
			i = next_d_lab();
			asm_fprintf(dg_file, "\t.stabn\t0x%x,0,%ld,.LL.%ld-%s\n", seg,
			            lno, i, last_proc_lab);
			asm_fprintf(dg_file, ".LL.%ld:\n", i);
		}
	}

	currentlno = lno;
}

/*
 * OUTPUT DIAGNOSTICS SURROUNDING CODE
 */
static void
code_diag_info(dg_info d, void(*mcode)(void *), void *args)
{
	if (d == NULL) {
		mcode(args);
		return;
	}

	switch (d->key) {
	case DGA_PARAMS: {
		dg_name arg;

		for (arg = d->data.i_param.args; arg; arg = arg->next) {
			stab_local(arg, 1);
		}

		code_diag_info(d->more, mcode, args);
		break;
	}

	case DGA_SRC: {
		if (d->data.i_src.startpos.line) {
			stabd(d->data.i_src.startpos.file, d->data.i_src.startpos.line,
			      N_SLINE);
		}

		code_diag_info(d->more, mcode, args);
		if (d->data.i_src.endpos.line) {
			stabd(d->data.i_src.endpos.file, d->data.i_src.endpos.line, N_SLINE);
		}
		break;
	}

	case DGA_SCOPE:
	case DGA_EXTRA: {
		dg_filename f = currentfile;
		long l = currentlno + 1;

		if (d->data.i_scope.lexpos.line) {
			f = d->data.i_scope.lexpos.file;
			l = d->data.i_scope.lexpos.line;
		}

		stab_scope_open(f);
		stabd(f, l, N_SLINE);
		code_diag_info(d->more, mcode, args);
		stab_scope_close();

		if (d->data.i_scope.endpos.line) {
			stabd(d->data.i_scope.endpos.file, d->data.i_scope.endpos.line, N_SLINE);
		}
		break;
	}

	case DGA_NAME:
		stab_local(d->data.i_name.dname, 0);
		code_diag_info(d->more, mcode, args);
		break;

	default:
		code_diag_info(d->more, mcode, args);
		break;
	}
}

/*
 * FIND THE STAB OF A SIMPLE SHAPE
 */
static long
out_sh_type(shape s, char *nm)
{
	last_type_sz = shape_size(s);

	switch (s->tag) {
	case scharhd:  return STAB_SCHAR;
	case ucharhd:  return STAB_UCHAR;
	case swordhd:  return STAB_SSHRT;
	case uwordhd:  return STAB_USHRT;
	case slonghd:  return strstr(nm, "long") ? STAB_SLONG : STAB_SINT;
	case ulonghd:  return strstr(nm, "long") ? STAB_ULONG : STAB_UINT;
	case s64hd:    return STAB_S64;
	case u64hd:    return STAB_U64;
	case shrealhd: return STAB_FLOAT;
	case realhd:   return STAB_DBL;
	case doublehd: return STAB_LDBL;
	}

	return STAB_VOID;
}

static long
find_basic_type(char *s)
{
	char *x;

	if (strstr(s, "char")) {
		return strstr(s, "unsigned") ? STAB_UCHAR : STAB_SCHAR;
	}

	if (strstr(s, "double")) {
		return strstr(s, "long") ? STAB_LDBL : STAB_DBL;
	}

	if (strstr(s, "float")) {
		return STAB_FLOAT;
	}

	if (strstr(s, "short")) {
		return strstr(s, "unsigned") ? STAB_USHRT : STAB_SSHRT;
	}

	if ((x = strstr(s, "long"))) {
		if (strstr(x + 1, "long")) {
			return strstr(s, "unsigned") ? STAB_U64 : STAB_S64;
		}
		return strstr(s, "unsigned") ? STAB_ULONG : STAB_SLONG;
	}

	if (strstr(s, "int")) {
		return strstr(s, "unsigned") ? STAB_UINT : STAB_SINT;
	}

	if (strstr(s, "void_star")) {
		return STAB_VS;
	}

	return STAB_VOID;
}


/*
 * OUTPUT DIAGNOSTICS DIRECTIVE FOR A FILE
 */
static void
stab_file(dg_filename f)
{
	long i = next_d_lab();
	int stb;

	if (f == currentfile || !f) {
		return;
	}

	stb = (f == prim_file ? 0x64 : 0x84);

	if (f->file_name[0] != '/' && f->file_path[0]) {
		asm_fprintf(dg_file, "\t.stabs\t\"%s/\",0x%x,0,0,.LL.%ld\n", f->file_path, stb, i);
	}

	asm_fprintf(dg_file, "\t.stabs\t\"%s\",0x%x,0,0,.LL.%ld\n", f->file_name, stb, i);

	asm_fprintf(dg_file, ".LL.%ld:\n", i);
	currentfile = f;
}

/*
 * LIST OF DIAGNOSTIC SCOPES AND LOCAL VARIABLES
 */

#define DEL_SIZE 50

struct delay_stab {
	int del_t;
	union {
		struct {
			char *nm;
			dg_type dt;
			int offset;
		} l;
		struct {
			int br;
			int lev;
			int lab;
		} b;
	} u;
};

enum del_types {D_PARAM, D_LOCAL, D_BRACKET};

struct del_stab_array {
	struct del_stab_array *more;
	struct delay_stab a[DEL_SIZE];
};

static struct del_stab_array *del_stab_start = NULL;
static struct del_stab_array *last_del_array = NULL;
static struct del_stab_array *c_del_array = NULL;
static int c_del_index = DEL_SIZE;

static struct delay_stab *
next_del_stab(void)
{
	if (c_del_index == DEL_SIZE) {
		if (c_del_array != last_del_array) {
			c_del_array = c_del_array->more;
		} else {
			struct del_stab_array * s = xmalloc(sizeof(struct del_stab_array));

			s->more = NULL;

			if (del_stab_start == NULL) {
				del_stab_start = s;
			} else {
				last_del_array->more = s;
			}

			c_del_array = last_del_array = s;
		}
		c_del_index = 0;
	}

	return c_del_array->a + c_del_index++;
}

static long open_label = 0;
static long bracket_level = 1;

/*
 * START OF A DIAGNOSTICS SCOPE
 */
static void
stab_scope_open(dg_filename f)
{
	long i;
	stab_file(f);

	if (open_label != 0) {
		struct delay_stab *t = next_del_stab();
		t->del_t = D_BRACKET;
		t->u.b.br = N_LBRAC;
		t->u.b.lev = bracket_level;
		t->u.b.lab = open_label;
	}

	i = next_d_lab();
	asm_fprintf(dg_file, ".LL.%ld:\n", i);
	open_label = i;
	bracket_level++;
}

/*
 * END OF A DIAGNOSTICS SCOPE
 */
static void
stab_scope_close(void)
{
	long i;
	struct delay_stab *x;

	if (open_label != 0) {
		struct delay_stab *t = next_del_stab();
		t->del_t = D_BRACKET;
		t->u.b.br = N_LBRAC;
		t->u.b.lev = bracket_level;
		t->u.b.lab = open_label;
		open_label = 0;
	}

	i = next_d_lab();
	x = next_del_stab();
	x->del_t = D_BRACKET;
	x->u.b.br = N_RBRAC;
	x->u.b.lev = bracket_level;
	x->u.b.lab = i;

	asm_fprintf(dg_file, ".LL.%ld:\n", i);
	bracket_level--;
}

/*
 * DEPTH COUNT FOR STAB TYPES
 */
static int max_depth = 64;
static int depth_now = 0;

/*
 * OUTPUT A DIAGNOSTICS TYPE
 */
#define OUT_DT_SHAPE(dt)	out_dt_shape((depth_now = 0, dt))

static long
type_size(dg_type dt)
{
	if (!dt) {
		return 0;
	}

	if (dt->outref.k == LAB_D || dt->outref.k < 0) {
		return get_stab_size(dt->outref.u.l);
	}

	switch (dt->key) {
	case DGT_TAGGED: {
		dg_tag tag = dt->data.t_tag;

		if (tag->key == DGK_NONE) {
			return 0;
		}

		if (tag->key == DGK_TYPE) {
			dg_type ref_t = tag->p.type;
			if (ref_t == dt) {
				return type_sizes[find_basic_type(ref_t->outref.u.s)];
			}
			return type_size(ref_t);
		}

		if (tag->key == DGK_NAME) {
			dg_name ref_n = tag->p.name;
			if (ref_n->key == DGN_TYPE /* && ref_n->idname.id_key == DG_ID_NONE */) {
				dg_type ref_t = tag->p.name->data.n_type.raw;
				return type_size(ref_t);
			}
		}

		return 0;
	}

	case DGT_BASIC:
		return shape_size(dt->data.t_bas.b_sh);

	case DGT_QUAL:
		if (dt->data.t_qual.q_key == DG_PTR_T) {
			return 32;
		}

		{
			dg_type pdt = dt->data.t_qual.type;
			return type_size(pdt);
		}

	case DGT_ARRAY:
		if (dt->data.t_arr.dims.len == 1) {
			dg_dim x;
			x = dt->data.t_arr.dims.array[0];
			if (x.d_key == DG_DIM_BOUNDS && !x.low_ref && !x.hi_ref && !x.hi_cnt) {
				long lwb = no(child(x.lower.exp));
				long upb = no(child(x.upper.exp));
				long stride = no(child(dt->data.t_arr.stride));
				return stride * (upb - lwb + 1);

			}
		}
		return 0;

	case DGT_ENUM:
		return shape_size(dt->data.t_enum.sha);

	case DGT_STRUCT:
		return shape_size(dt->data.t_struct.sha);

	case DGT_BITF:
		return dt->data.t_bitf.bv.bits;

	case DGT_PROC:
		return 32;

	default:
		return 0;
	}
}

static void
out_dt_shape(dg_type dt)
{
	if (!dt) {
		asm_fprintf(dg_file, "%d", STAB_VOID);
		last_type_sz = 0;
		return;
	}

	if (dt->outref.k == LAB_D || (dt->outref.k < 0 && depth_now != 0)) {
		asm_fprintf(dg_file, "%ld", dt->outref.u.l);
		last_type_sz = get_stab_size(dt->outref.u.l);
		return;
	}

	depth_now++;

	switch (dt->key) {
	case DGT_TAGGED: {
		dg_tag tag = dt->data.t_tag;

		if (tag->done) {
			dt->outref = tag->outref;
			out_dt_shape(dt);
			break;
		}

		if (tag->key == DGK_NONE) {
			error(ERR_INTERNAL, "external type");
			tag->done = 1;
			tag->outref.k = LAB_D;
			tag->outref.u.l = 0;
			out_dt_shape(dt);
			break;
		}

		if (tag->key == DGK_TYPE) {
			dg_type ref_t = tag->p.type;

			if (ref_t == dt) {
				if (ref_t->outref.k != LAB_STR) {
					error(ERR_INTERNAL, "uninitialised?");
				}

				ref_t->outref.k = LAB_D;
				ref_t->outref.u.l = find_basic_type(ref_t->outref.u.s);
			}

			out_dt_shape(ref_t);
			dt->outref = tag->outref = ref_t->outref;
			tag->done = 1;
			break;
		}

		if (tag->key == DGK_NAME) {
			dg_name ref_n = tag->p.name;

			if (ref_n->key == DGN_TYPE /* && ref_n->idname.id_key == DG_ID_NONE */) {
				dg_type ref_t = tag->p.name->data.n_type.raw;
				out_dt_shape(ref_t);
				dt->outref = tag->outref = ref_t->outref;
				tag->done = 1;
				break;
			}
		}

		error(ERR_INTERNAL, "unfinished convolution");

		tag->done = 1;
		tag->outref.k = LAB_D;
		tag->outref.u.l = 0;
		out_dt_shape(dt);
		break;
	}

	case DGT_BASIC:
		dt->outref.u.l = out_sh_type(dt->data.t_bas.b_sh, dt->data.t_bas.tname);
		dt->outref.k = LAB_D;
		out_dt_shape(dt);
		break;

	case DGT_QUAL: {
		if (dt->data.t_qual.q_key == DG_PTR_T) {
			long non;

			dg_type pdt = dt->data.t_qual.type;
			if (pdt->key == DGT_BASIC) {
				long pn = out_sh_type(pdt->data.t_bas.b_sh, pdt->data.t_bas.tname);
				non = stab_ptrs[pn];
				if (non == 0) {
					non = (dt->outref.k < 0 ? dt->outref.u.l : next_typen());
					stab_ptrs[pn] = non;
					asm_fprintf(dg_file, "%ld=*%ld", non, pn);
				} else {
					asm_fprintf(dg_file, "%ld", non);
				}
			} else {
				non = (dt->outref.k < 0 ? dt->outref.u.l : next_typen());
				asm_fprintf(dg_file, "%ld=*", non);
				out_dt_shape(pdt);
			}

			dt->outref.u.l = non;
			dt->outref.k = LAB_D;
			last_type_sz = 32;
			set_stab_size(non);
		} else {
			dg_type pdt = dt->data.t_qual.type;
			out_dt_shape(pdt);
			dt->outref = pdt->outref;
		}
		break;
	}

	case DGT_ARRAY: {
		long non;

		if (dt->outref.k >= 0) {
			dt->outref.u.l = next_typen();
		}

		dt->outref.k = LAB_D;
		non = dt->outref.u.l;
		if (dt->data.t_arr.dims.len == 1) {
			dg_dim x;

			x = dt->data.t_arr.dims.array[0];

			if (x.d_key == DG_DIM_BOUNDS && !x.low_ref && !x.hi_ref && !x.hi_cnt) {
				long lwb = no(child(x.lower.exp));
				long upb = no(child(x.upper.exp));
				long stride = no(child(dt->data.t_arr.stride));
				dg_type index_type = x.d_type;
				dg_type element_type = dt->data.t_arr.elem_type;
				asm_fprintf(dg_file, "%ld=", non);
				asm_fprintf(dg_file, "ar");
				out_dt_shape(index_type);
				asm_fprintf(dg_file, ";%ld;%ld;", lwb, upb);
				out_dt_shape(element_type);
				last_type_sz = stride * (upb - lwb + 1);
				set_stab_size(non);
				break;
			}

			if (x.d_key == DG_DIM_NONE) {
				dg_type index_type = x.d_type;
				dg_type element_type = dt->data.t_arr.elem_type;
				asm_fprintf(dg_file, "%ld=", non);
				asm_fprintf(dg_file, "ar");
				out_dt_shape(index_type);
				asm_fprintf(dg_file, ";0;0;");
				out_dt_shape(element_type);
				last_type_sz = 0;
				set_stab_size(non);
				break;
			}
		}

		error(ERR_INTERNAL, "complex array");
		break;
	}

	case DGT_ENUM: {
		int i;
		dg_enum *el = dt->data.t_enum.values.array;

		if (dt->outref.k >= 0) {
			dt->outref.u.l = next_typen();
		}

		dt->outref.k = LAB_D;
		asm_fprintf(dg_file, "%ld=e", dt->outref.u.l);
		for (i = 0; i < dt->data.t_enum.values.len; i++) {
			asm_fprintf(dg_file, "%s:%d,", el[i].ename, no(child(el[i].value)));
		}

		asm_fprintf(dg_file, ";");
		last_type_sz = shape_size(dt->data.t_enum.sha);
		set_stab_size(dt->outref.u.l);
		break;
	}

	case DGT_STRUCT: {
		int i;
		char su = (dt->data.t_struct.is_union ? 'u' : 's');
		shape s = dt->data.t_struct.sha;

		dg_classmem * el = dt->data.t_struct.u.fields.array;
		if (dt->outref.k >= 0) {
			dt->outref.u.l = next_typen();
		}

		dt->outref.k = LAB_D;
		asm_fprintf(dg_file, "%ld=%c%d", dt->outref.u.l, su, shape_size(s) / 8);

		for (i = 0; i < dt->data.t_struct.u.fields.len; i++) {
			long offset = no(child(el[i].d.cm_f.f_offset));
			if (depth_now >= max_depth) {
				depth_now = 0;
				asm_fprintf(dg_file, "\\\\\",0x80,0,%d,%d\n", 0, 0);
				asm_fprintf(dg_file, "\t.stabs\t\"");
			}
			depth_now++;
			asm_fprintf(dg_file, "%s:", el[i].d.cm_f.fname);
			out_dt_shape(el[i].d.cm_f.f_type);
			asm_fprintf(dg_file, ",%ld,%ld;", offset, type_size(el[i].d.cm_f.f_type));
		}

		asm_fprintf(dg_file, ";");
		last_type_sz = shape_size(s);
		set_stab_size(dt->outref.u.l);
		break;
	}

	case DGT_BITF: {
		bitfield_variety bv;
		bv = dt->data.t_bitf.bv;
		asm_fprintf(dg_file, "%d", (bv.has_sign ? STAB_SINT : STAB_UINT));
		last_type_sz = bv.bits;
		break;
	}

	case DGT_PROC: {
		dg_type result_type = dt->data.t_proc.res_type;
		long non1 = next_typen();
		long non2 = next_typen();
		dt->outref.u.l = non1;
		dt->outref.k = LAB_D;
		asm_fprintf(dg_file, "%ld=*%ld=f", non1, non2);
		out_dt_shape(result_type);
		last_type_sz = 32;
		set_stab_size(non1);
		set_stab_size(non2);
		break;
	}

	default:
		asm_fprintf(dg_file, "%d", STAB_VOID);
		dt->outref.u.l = STAB_VOID;
		dt->outref.k = LAB_D;
		last_type_sz = 0;
		break;
	}
}

/*
 * OUTPUT DIAGNOSTICS FOR A GLOBAL VARIABLE
 */
static void
stab_global(dg_name di, exp global, char *name, int ext)
{
	char *nm;
	dg_type dt;

	if (!di || di->key != DGN_OBJECT) {
		return;
	}

	nm = idname_chars(di->idname);
	dt = di->data.n_obj.type;

	if (di->whence.line) {
		stabd(di->whence.file, di->whence.line, -N_DSLINE);
	}

	asm_fprintf(dg_file, "\t.stabs\t\"%s:%c", nm, (ext ? 'G' : 'S'));
	OUT_DT_SHAPE(dt);

	/* solaris puts line no,0 rather than 0, varname, so suppress the stabd
	   above, and do here. */
	asm_fprintf(dg_file, "\",%#x,0,%ld,%s\n",
		(ext ? 0x24 : ((no(global) != 0) ? 0x26 : 0x28)),
		di->whence.line, name);
}

/*
 * OUTPUT DIAGNOSTICS FOR A PROCEDURE
 */
static void
stab_proc(dg_name di, exp proc, char *name, int ext)
{
	char *nm;
	dg_type dt;

	if (!di || di->key != DGN_PROC) {
		return;
	}

	nm = idname_chars(di->idname);
	dt = di->data.n_proc.type;

	if (dt->key == DGT_PROC) {	/* it should be */
		dt = dt->data.t_proc.res_type;
	}

	last_proc_lab = name;
	if (di->whence.line) {
		stabd(di->whence.file, di->whence.line, 0);
	}

	asm_fprintf(dg_file, "\t.stabs\t\"%s:%c", nm, (ext ? 'F' : 'f'));
	OUT_DT_SHAPE(dt);
	asm_fprintf(dg_file, "\",0x24,0,%ld,%s\n", di->whence.line, name);
}

static void
stab_proc_end(void)
{
	if (del_stab_start != NULL) {
		struct del_stab_array *this_a = del_stab_start;
		int this_i = 0;

		while (this_a != c_del_array || this_i != c_del_index) {
			struct delay_stab *t;

			if (this_i == DEL_SIZE) {
				this_a = this_a->more;
				this_i = 0;
			}

			t = this_a->a + this_i++;

			switch (t->del_t) {
			case D_PARAM: {
				long disp = t->u.l.offset;

				asm_fprintf(dg_file, "\t.stabs\t\"%s:p", t->u.l.nm);
				OUT_DT_SHAPE(t->u.l.dt);
				asm_fprintf(dg_file, "\",0xa0,0,%d,%ld\n", 0, disp);

				if (disp <= 88) { /* register useage comment */
					asm_fprintf(dg_file, "\t.stabs\t\"%s:r", t->u.l.nm);
					OUT_DT_SHAPE(t->u.l.dt);
					asm_fprintf(dg_file, "\",0x40,0,%d,%ld\n", 0, 24 + ((disp - 68) / 4));
				}
				break;
			}

			case D_LOCAL: {
				long disp = t->u.l.offset;
				asm_fprintf(dg_file, "\t.stabs\t\"%s:", t->u.l.nm);
				OUT_DT_SHAPE(t->u.l.dt);
				asm_fprintf(dg_file, "\",0x80,0,%d,%ld\n", 0, disp);
				break;
			}

			default:
				asm_fprintf(dg_file, "\t.stabn\t0x%x,0,%d,.LL.%d-%s\n",
				            t->u.b.br, t->u.b.lev, t->u.b.lab, last_proc_lab);
			}
		}

		c_del_array = del_stab_start;
		c_del_index = 0;
	}
}

/*
 * OUTPUT DIAGNOSTICS FOR A LOCAL VARIABLE
 */
static void
stab_local(dg_name di, int param)
{
	exp id = di->data.n_obj.obtain_val;
	struct delay_stab *t;
	char *nm;
	dg_type dt;
	long disp;

	if (di->key != DGN_OBJECT || !id) {
		return;
	}

	id = child(id);
	if (id->tag == cont_tag && child(id)->tag == name_tag && isvar(child(child(id)))) {
		id = child(id);
	}

	if (id->tag != name_tag || isdiscarded(id) || (isglob(child(id)) &&
	        no(child(id)) == 0 && !(nextg(child(id))->extnamed))) {
		return;
	}

	disp = no(id);
	id = child(id);
	nm = idname_chars(di->idname);
	dt = di->data.n_obj.type;
	t = next_del_stab();

	if (id->tag == ident_tag && ((props(id) & defer_bit) == 0)) {
		disp += boff ( id ).offset; /* is this condition right ? */
	}

again:

	if (id->tag == ident_tag) {
		if ((props(id) & defer_bit) == 0) {
			/* +++ add assembler comment to say which reg is being used */
			t->del_t = (param ? D_PARAM : D_LOCAL);
			t->u.l.nm = nm;
			t->u.l.dt = dt;
			t->u.l.offset = disp;
			return;
		} else {
			exp sn = child(id);
			long d = disp;

			while (sn != NULL) {
				switch (sn->tag) {
				case name_tag: {
					disp = d + no(sn);
					id = child(sn);
					/* if ( isvar ( id ) ) dt = dt->data.ptr.object ;		?????????? */
					goto again;
				}

				case reff_tag:
					d += no(sn);
					sn = child(sn);
					break;

				case cont_tag:
					sn = child(sn);
					break;

				default:
					return;
				}
			}
		}
	}
}

/*
 * DEAL WITH BASIC TYPES
 */
static void
stab_types(void)
{
	total_type_sizes = NO_STABS;
	typeno = NO_STABS;

	type_sizes = xmalloc(NO_STABS * sizeof(long));

	asm_fprintop(dg_file, ".stabs \"int:t1=r1;-2147483648;2147483647;\",0x80,0,0,0");
	asm_fprintop(dg_file, ".stabs \"short int:t2=r1;-32768;32767;\",0x80,0,0,0");
	asm_fprintop(dg_file, ".stabs \"short unsigned int:t3=r1;0;65535;\",0x80,0,0,0");
	asm_fprintop(dg_file, ".stabs \"char:t4=r4;0;127;\",0x80,0,0,0");
	asm_fprintop(dg_file, ".stabs \"signed char:t5=r1;-128;127;\",0x80,0,0,0");
	asm_fprintop(dg_file, ".stabs \"unsigned char:t6=r1;0;255;\",0x80,0,0,0");
	asm_fprintop(dg_file, ".stabs \"long int:t7=r1;-2147483648;2147483647;\",0x80,0,0,0");
	asm_fprintop(dg_file, ".stabs \"unsigned int:t8=r1;0;-1;\",0x80,0,0,0");
	asm_fprintop(dg_file, ".stabs \"long unsigned int:t9=r1;0;-1;\",0x80,0,0,0");
	asm_fprintop(dg_file, ".stabs \"float:t10=r1;4;0;\",0x80,0,0,0");
	asm_fprintop(dg_file, ".stabs \"double:t11=r1;8;0;\",0x80,0,0,0");
	asm_fprintf(dg_file, ".stabs \"long double:t12=r1;%ld;0;\",0x80,0,0,0\n", DOUBLE_SZ / 8);
	asm_fprintop(dg_file, ".stabs \"void:t13=13\",0x80,0,0,0");
	asm_fprintop(dg_file, ".stabs \"long long int:t14=r1;");
	asm_fprintf(dg_file, "01000000000000000000000;0777777777777777777777;\",0x80,0,0,0\n");
	asm_fprintop(dg_file, ".stabs \"unsigned long long int:t15=r1;");
	asm_fprintf(dg_file, "0000000000000;01777777777777777777777;\",0x80,0,0,0\n");
	asm_fprintop(dg_file, ".stabs \"__void_star:t16=*13\",0x80,0,0,0");

	type_sizes[0] = 0;
	type_sizes[1] = 32;
	type_sizes[2] = 16;
	type_sizes[3] = 16;
	type_sizes[4] = 8;
	type_sizes[5] = 8;
	type_sizes[6] = 8;
	type_sizes[7] = 32;
	type_sizes[8] = 32;
	type_sizes[9] = 32;
	type_sizes[10] = 32;
	type_sizes[11] = 64;
	type_sizes[12] = DOUBLE_SZ;
	type_sizes[13] = 0;
	type_sizes[14] = 64;
	type_sizes[15] = 64;
	type_sizes[16] = 32;
}

/*
 * INITIALISE DIAGNOSTICS
 */
static void
init_stab(void)
{
}

static void
init_stab_aux(void)
{
	dg_compilation this_comp;
	dg_file = as_file;

	for (this_comp = all_comp_units; this_comp; this_comp = this_comp->another) {
		dg_name item;

		for (item = this_comp->dn_list; item; item = item->next) {
			if (item->key == DGN_PROC && item->data.n_proc.obtain_val) {
				prim_file = this_comp->prim_file;
			}
		}
	}

	if (prim_file) {
		stab_file(prim_file);
	}

	stab_types();

	for (this_comp = all_comp_units; this_comp; this_comp = this_comp->another) {
		dg_name item;

		for (item = this_comp->dn_list; item; item = item->next) {
			if (item->key == DGN_TYPE && item->data.n_type.raw->key != DGT_UNKNOWN) {
				dg_type dt = item->data.n_type.raw;
				char *s = idname_chars(item->idname);
				if (s[0]) {
					asm_fprintf(dg_file, "\t.stabs\t\"%s:", s);
					if (dt->outref.k == LAB_STR) {
						dt->outref.k = LAB_D;
						dt->outref.u.l = find_basic_type(dt->outref.u.s);
					}

					if (dt->outref.k == LAB_D) {
						asm_fprintf(dg_file, "%d", (int)dt->outref.u.l);
					} else {
						asm_fprintf(dg_file, "t");
						OUT_DT_SHAPE(dt);
					}
					asm_fprintf(dg_file, "\",0x80,0,0,0\n");
				} else if ((dt->key == DGT_STRUCT &&
				            (dt->data.t_struct.idname.id_key == DG_ID_SRC ||
				             dt->data.t_struct.idname.id_key == DG_ID_EXT)
				            && (s = dt->data.t_struct.idname.idd.name, s[0]))
				           || (dt->key == DGT_ENUM && (s = dt->data.t_enum.tname, s[0]))) {
					asm_fprintf(dg_file, "\t.stabs\t\"%s:", s);
					if (dt->outref.k == LAB_D) {
						asm_fprintf(dg_file, "%d", (int)dt->outref.u.l);
					} else {
						asm_fprintf(dg_file, "T");
						OUT_DT_SHAPE(dt);
					}
					asm_fprintf(dg_file, "\",0x80,0,0,0\n");
				}
			}
		}
	}
}

const struct diag4_driver diag4_driver_stabs = {
	init_stab,
	init_stab_aux,
	NULL,

	stabd,
	code_diag_info,
	stab_global,
	stab_proc,
	stab_proc_end,
	stab_types
};

