/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/check.h>
#include <shared/xalloc.h>

#include "config.h"

#include "exptypes.h"
#include <reader/codetypes.h>
#include <construct/flags.h>
#include <construct/installtypes.h>
#include <linkinfo/li_types.h>

#ifdef NEWDIAGS
#include <newdiag/dg_first.h>
#include <newdiag/dg_types.h>  /* new diags */
#include <newdiag/diagtypes.h> /* old diags */
#else
#include <diag/dg_first.h>
#include <diag/diaginfo.h>
#include <diag/dg_types.h>  /* new diags */
#include <diag/diagtypes.h> /* old diags */
#endif

#include <reader/basicread.h>
#include "out.h"
#include <construct/machine.h>
#include <construct/shapemacs.h>
#include "expmacs.h"
#include <construct/tags.h>
#include "szs_als.h"
#include <construct/exp.h>
#include <reader/externs.h>

#ifdef NEWDIAGS

#include <newdiag/dg_types.h>
#include <newdiag/dg_aux.h>
#include <newdiag/dg_globs.h>

#include "codermacs.h"
#include "instr.h"

#else

#include <diag/diagtypes.h>
#include <diag/mark_scope.h>
#include <diag/diagglob.h>

#endif




extern int locals_offset;	/* declared in cproc.c */


/*
    FORWARD DECLARATIONS
*/

#ifdef NEWDIAGS
static void stab_scope_open(dg_filename);
static void stab_scope_close(void);
static void stab_file(dg_filename);
static void stab_local(dg_name, int);
static void stab_types(void);
#else
static void stab_scope_open(long);
static void stab_scope_close(long);
static void stab_file(long, bool);
static void stab_local(diag_info *, int, exp);
static void stab_types(void);
#endif


/* label number sequence independent from text code */
static int diag_lab_no = 0;

static int
next_d_lab(void)
{
  return ++diag_lab_no;
}



/*
    DIAGNOSTICS FILE
*/

static FILE *dg_file;

#ifndef NEWDIAGS
static char *dg_file_name;
#endif

static void
d_outnl(void)
{
  /* avoids indicating completion of executable instruction */
  IGNORE fputs("\n", dg_file);
}



/*
    BASIC TYPE NUMBERS
*/

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


/*
    80x86 register numbers
*/

#ifdef NEWDIAGS
static long reg_stabno[8] = {0, 2, 1, 3, 7, 6, 5, 4};
#endif

/*
    BASIC POINTERS
*/

static long stab_ptrs[NO_STABS] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


/*
    CURRENT TYPE NUMBER
*/

static long typeno;


/*
    SIZE OF LAST STAB TYPE OUTPUT
*/

static long last_type_sz = 0;


/*
    CURRENT LINE NUMBER AND FILE NUMBER
*/

long currentlno = -1;

#ifdef NEWDIAGS

dg_filename currentfile = (dg_filename)0;
dg_filename prim_file = (dg_filename)0;

#else

long currentfile = -1;

#endif


/*
    ARRAY OF TYPE SIZES
*/

static long *type_sizes;
static int total_type_sizes = 0;


/*
    SETTING AND GETTING TYPE SIZES
*/

#define set_stab_size(i)	type_sizes[(i)] = last_type_sz
#define get_stab_size(i)	(type_sizes[(i)])
#define shape_stab_size(i, s)	type_sizes[(i)] = shape_size(s)


/*
    GET THE NEXT TYPE NUMBER
*/

static long
next_typen(void)
{
    if (typeno >= total_type_sizes) {
	int i, n = total_type_sizes, m = n + 100;
	type_sizes = xrealloc(type_sizes, (size_t)m * sizeof *type_sizes);
	for (i = n; i < m; i++) {
	    type_sizes[i] = 0;
	}
	total_type_sizes = m;
    }
    return typeno++;
}


#ifndef NEWDIAGS

/*
    ARRAY OF FILE DESCRIPTORS
*/

static filename *fds = NULL;
static int szfds = 0;
static int nofds = 0;


/*
    ADD A NEW FILE TO THE ARRAY OF FILE DESCRIPTORS
*/

void
stab_collect_files(filename f)
{
    if (fds == NULL) {
	szfds += 10;
	fds = xmalloc(szfds * sizeof *fds);
    } else if (nofds >= szfds) {
	szfds += 10;
	fds = xrealloc(fds, szfds * sizeof *fds);
    }
    fds[nofds++] = f;
    return;
}


/*
    FIND THE FILE DESCRIPTOR CORRESPONDING TO A FILE NAME
*/

static long
find_file(char *f)
{
    long i;
    for (i = 0; i < nofds; i++) {
	if (strcmp(f, fds[i]->file.ints.chars) == 0) {
	    return i;
	}
    }
    return 0;
}

#endif


static int last_proc_cname;
static char *last_proc_pname = "<<No Proc>>";

static void
out_procname(void)
{
  if (last_proc_cname == -1) {
    outs(last_proc_pname);
  } else {
    outs(local_prefix);
    outn((long)last_proc_cname);
  }
}


/*
    OUTPUT A FILE POSITION CONSTRUCT
*/

#define N_SLINE 0x44
#define N_DSLINE 0x46
#define N_BSLINE 0x48
#define N_LBRAC  0xc0
#define N_RBRAC  0xe0

#ifdef NEWDIAGS

void
stabd(dg_filename f, long lno, int seg)
{
    long i;
    if (f == currentfile && lno == currentlno) {
	return;
    }
    stab_file(f);

    if (seg != 0) {		/* 0 suppresses always */
      if (seg > 0) {		/* -ve line nos are put out in the stabs */
	i = next_d_lab();
	IGNORE fprintf(dg_file, ".LL.%ld:\n", i);
	IGNORE fprintf(dg_file, "\t.stabn\t0x%x,0,%ld,.LL.%ld-", seg, lno, i);
	out_procname();
	d_outnl();
      }
    }
    currentlno = lno;
    return;
}

#else

static void
stabd(long findex, long lno, int seg)
{
    long i;

    if (findex == currentfile && lno == currentlno) {
	return;
    }
    stab_file(findex, 1);

    if (seg != 0) {		/* 0 suppresses always */
      if (seg > 0) {		/* -ve line nos are put out in the stabs */
	i = next_d_lab();
	IGNORE fprintf(dg_file, ".LL.%ld:\n", i);
	IGNORE fprintf(dg_file, "\t.stabn\t0x%x,0,%ld,.LL.%ld-", seg, lno, i);
	out_procname();
	d_outnl();
      }
    }
    currentlno = lno;
    return;
}

#endif



#ifdef NEWDIAGS
/*
    OUTPUT DIAGNOSTICS SURROUNDING CODE
*/

void
code_diag_info(dg_info d, void(*mcode)(void *), void *args)
{
  if (d == nildiag) {
   (*mcode)(args);
    return;
  }
  switch (d->key) {
    case DGA_PARAMS: {
      dg_name arg = d->data.i_param.args;
      while (arg) {
	stab_local(arg, 1);
	arg = arg->next;
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
      if (d->data.i_src.endpos.line)
	stabd(d->data.i_src.endpos.file, d->data.i_src.endpos.line, N_SLINE);
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
	stabd(d->data.i_scope.endpos.file, d->data.i_scope.endpos.line,
	      N_SLINE);
      }
      break;
    }
    case DGA_NAME: {
      stab_local(d->data.i_nam.dnam, 0);
      code_diag_info(d->more, mcode, args);
      break;
    }
    default: {
      code_diag_info(d->more, mcode, args);
      break;
    }
  }
  return;
}


#else

/*
    OUTPUT INITIAL DIAGNOSTICS FOR A DIAGNOSE_TAG
*/

void
output_diag(diag_info *d, int proc_no, exp e)
{
  if (d->key == DIAG_INFO_SOURCE) {
    sourcemark *s = &d->data.source.beg;
    long f = find_file(s->file->file.ints.chars);
    stabd(f, (long)s->line_no.nat_val.small_nat, N_SLINE);
    return;
  }

  if (d->key == DIAG_INFO_ID) {
    exp acc = d->data.id_scope.access;

    if (isglob(son(acc)) || no(son(acc)) == 1) {
	return;
    }
    mark_scope(e);

    if (props(e) & 0x80) {
      stab_scope_open(currentfile);
      stabd(currentfile, (long)(currentlno + 1), N_SLINE);
    }

    stab_local(d, proc_no, acc);

    return;
  }
}


/*
    OUTPUT FINAL DIAGNOSTICS FOR A DIAGNOSE_TAG
*/

void
output_end_scope(diag_info *d, exp e)
{
    if (d->key == DIAG_INFO_SOURCE) {
	sourcemark *s = &d->data.source.end;
	long f = find_file(s->file->file.ints.chars);
	long lno = s->line_no.nat_val.small_nat;
	stabd(f, lno, N_SLINE);
	return;
    }
    if (d->key == DIAG_INFO_ID && props(e) & 0x80) {
	stab_scope_close(currentfile);
	return;
    }
    return;
}
#endif




/*
    FIND THE STAB OF A SIMPLE SHAPE
*/

#ifdef NEWDIAGS

static long
out_sh_type(shape s, char *nm)
{
  last_type_sz = shape_size(s);
  switch (name(s)) {
    case scharhd: return STAB_SCHAR;
    case ucharhd: return STAB_UCHAR;
    case swordhd: return STAB_SSHRT;
    case uwordhd: return STAB_USHRT;
    case slonghd: return strstr(nm, "long")? STAB_SLONG : STAB_SINT;
    case ulonghd: return strstr(nm, "long")? STAB_ULONG : STAB_UINT;
    case s64hd: return STAB_S64;
    case u64hd: return STAB_U64;
    case shrealhd: return STAB_FLOAT;
    case realhd: return STAB_DBL;
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
    if (strstr(x+1, "long")) {
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

#else

static long
out_sh_type(shape s)
{
    last_type_sz = shape_size(s);
    switch (name(s)) {
	case scharhd:
		return STAB_SCHAR;
	case ucharhd:
		return STAB_UCHAR;
	case swordhd:
		return STAB_SSHRT;
	case uwordhd:
		return STAB_USHRT;
	case slonghd:
		return STAB_SINT;
	case ulonghd:
		return STAB_UINT;
	case s64hd:
		return STAB_S64;
	case u64hd:
		return STAB_U64;
	case shrealhd:
		return STAB_FLOAT;
	case realhd:
		return STAB_DBL;
	case doublehd:
		return STAB_LDBL;
    }
    return STAB_VOID;
}

#endif


/*
    OUTPUT DIAGNOSTICS DIRECTIVE FOR A FILE
*/

#ifdef NEWDIAGS

static void
stab_file(dg_filename f)
{
    long i = next_d_lab();
    int stb;

    if (f == currentfile || !f) {
	return;
    }

    stb = (f == prim_file ? 0x64 : 0x84);
    IGNORE fprintf(dg_file, ".LL.%ld:\n", i);

    if (f->file_name[0]!= '/' && f->file_path[0]) {
      IGNORE fprintf(dg_file, "\t.stabs\t\"%s/\",0x%x,0,0,.LL.%ld\n",
		     f->file_path, stb, i);
    }

    IGNORE fprintf(dg_file, "\t.stabs\t\"%s\",0x%x,0,0,.LL.%ld\n",
		   f->file_name, stb, i);

    currentfile = f;
    return;
}

#else

static void
stab_file(long findex, bool internal)
{
    static long i = 0;

    if (findex == currentfile || findex < 0 || findex >= szfds) {
	return;
    }

    if (!internal) {
	/* source file */
	i = next_d_lab();
	IGNORE fprintf(dg_file, ".LL.%ld:\n", i);
	IGNORE fprintf(dg_file, "\t.stabs\t\"%s\",0x64,0,0,.LL.%ld\n",
		       fds[findex]->file.ints.chars, i);
    } else {
	/* included file */
	IGNORE fprintf(dg_file, "\t.stabs\t\"%s\",0x84,0,0,.LL.%ld\n",
		       fds[findex]->file.ints.chars, i);
    }
    currentfile = findex;
    return;
}

#endif


/*
    LIST OF DIAGNOSTIC SCOPES AND LOCAL VARIABLES
*/

#define DEL_SIZE 50

struct delay_stab {
    int del_t;
    union {
	struct {
	    char *nm;
#ifdef NEWDIAGS
	    dg_type dt;
#else
	    diag_type dt;
#endif
	    int offset;
	} l;
	struct {
	    int br;
	    int lev;
	    int lab;
	} b;
    } u;
};

enum del_types {D_PARAM, D_LOCAL, D_BRACKET, D_REG};

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
	    struct del_stab_array *s = (struct del_stab_array *)
		(xmalloc(sizeof(struct del_stab_array)));
	    s->more = NULL;
	    if (del_stab_start == NULL) {
		del_stab_start = s;
	    } else {
		last_del_array -> more = s;
	    }
	    c_del_array = last_del_array = s;
	}
	c_del_index = 0;
    }
    return (c_del_array -> a) + (c_del_index++);
}

static long open_label = 0;
static long bracket_level = 0;


/*
    START OF A DIAGNOSTICS SCOPE
*/

#ifdef NEWDIAGS

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
    IGNORE fprintf(dg_file, ".LL.%ld:\n", i);
    bracket_level++;
    open_label = i;
    return;
}

#else

static void
stab_scope_open(long findex)
{
    long i;
    stab_file(findex, 1);
    if (open_label != 0) {
	struct delay_stab *t = next_del_stab();
	t->del_t = D_BRACKET;
	t->u.b.br = N_LBRAC;
	t->u.b.lev = bracket_level;
	t->u.b.lab = open_label;
    }
    i = next_d_lab();
    IGNORE fprintf(dg_file, ".LL.%ld:\n", i);
    bracket_level++;
    open_label = i;
    return;
}

#endif


/*
    END OF A DIAGNOSTICS SCOPE
*/

#ifdef NEWDIAGS

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
    IGNORE fprintf(dg_file, ".LL.%ld:\n", i);
    bracket_level--;
    return;
}

#else

static void
stab_scope_close(long findex)
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
    IGNORE fprintf(dg_file, ".LL.%ld:\n", i);
    bracket_level--;
    return;
}

#endif


/*
    DEPTH COUNT FOR STAB TYPES
*/

static int max_depth = 64;
static int depth_now = 0;


/*
    OUTPUT A DIAGNOSTICS TYPE
*/

#define OUT_DT_SHAPE(dt)	out_dt_shape((depth_now = 0, dt))

#ifdef NEWDIAGS

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
      dg_tag tg = dt->data.t_tag;
      if (tg->key == DGK_NONE) {
	return 0;
      }
      if (tg->key == DGK_TYPE) {
	dg_type ref_t = tg->p.typ;
	if (ref_t == dt) {
	  return type_sizes[find_basic_type(ref_t->outref.u.s)];
	}
	return type_size(ref_t);
      }
      if (tg->key == DGK_NAME) {
	dg_name ref_n = tg->p.nam;
	if (ref_n->key == DGN_TYPE /* && ref_n->idnam.id_key == DG_ID_NONE */) {
	  dg_type ref_t = tg->p.nam->data.n_typ.raw;
	  return type_size(ref_t);
	}
      }
      return 0;
    }
    case DGT_BASIC: {
      return shape_size(dt->data.t_bas.b_sh);
    }
    case DGT_QUAL: {
      if (dt->data.t_qual.q_key == DG_PTR_T) {
        return 32;
      }
      {
	dg_type pdt = dt->data.t_qual.typ;
	return type_size(pdt);
      }
    }
    case DGT_ARRAY: {
      if (dt->data.t_arr.dims.len == 1) {
	dg_dim x;
	x = dt->data.t_arr.dims.array[0];
	if (x.d_key == DG_DIM_BOUNDS && !x.low_ref && !x.hi_ref && !x.hi_cnt) {
	  long lwb = no(son(x.lower.x));
	  long upb = no(son(x.upper.x));
	  long stride = no(son(dt->data.t_arr.stride));
	  return stride *(upb - lwb + 1);

	}
      }
      return 0;
    }
    case DGT_ENUM: {
      return shape_size(dt->data.t_enum.sha);
    }
    case DGT_STRUCT: {
      return shape_size(dt->data.t_struct.sha);
    }
    case DGT_BITF: {
      return dt->data.t_bitf.bv.bits;
    }
    case DGT_PROC: {
      return 32;
    }
    default :
      return 0;
  }
}

static void
out_dt_shape(dg_type dt)
{
  if (!dt) {
    IGNORE fprintf(dg_file, "%d", STAB_VOID);
    last_type_sz = 0;
    return;
  }

  if (dt->outref.k == LAB_D || (dt->outref.k < 0 && depth_now != 0)) {
    IGNORE fprintf(dg_file, "%ld", dt->outref.u.l);
    last_type_sz = get_stab_size(dt->outref.u.l);
    return;
  }

#if 0
  /* SunOS as(1) rejects stab lines >2k so reduce size arbitrarily */
  if (depth_now >= max_depth) {
    IGNORE fprintf(dg_file, "%d", STAB_SLONG);
    return;
  }
#endif
  depth_now++;

  switch (dt->key) {

    case DGT_TAGGED: {
      dg_tag tg = dt->data.t_tag;
      if (tg->done) {
	dt->outref = tg->outref;
	out_dt_shape(dt);
	break;
      }
      if (tg->key == DGK_NONE) {
	failer("external type");
	tg->done = 1;
	tg->outref.k = LAB_D;
	tg->outref.u.l = 0;
	out_dt_shape(dt);
	break;
      }
      if (tg->key == DGK_TYPE) {
	dg_type ref_t = tg->p.typ;
	if (ref_t == dt) {
	  if (ref_t->outref.k != LAB_STR)
	    failer("uninitialised?");
	  ref_t->outref.k = LAB_D;
	  ref_t->outref.u.l = find_basic_type(ref_t->outref.u.s);
	}
	out_dt_shape(ref_t);
	dt->outref = tg->outref = ref_t->outref;
	tg->done = 1;
	break;
      }
      if (tg->key == DGK_NAME) {
	dg_name ref_n = tg->p.nam;
	if (ref_n->key == DGN_TYPE /* && ref_n->idnam.id_key == DG_ID_NONE */) {
	  dg_type ref_t = tg->p.nam->data.n_typ.raw;
	  out_dt_shape(ref_t);
	  dt->outref = tg->outref = ref_t->outref;
	  tg->done = 1;
	  break;
	}
      }
      failer("unfinished convolution");
      tg->done = 1;
      tg->outref.k = LAB_D;
      tg->outref.u.l = 0;
      out_dt_shape(dt);
      break;
    }

    case DGT_BASIC: {
      dt->outref.u.l = out_sh_type(dt->data.t_bas.b_sh, dt->data.t_bas.tnam);
      dt->outref.k = LAB_D;
      out_dt_shape(dt);
      break;
    }

    case DGT_QUAL: {
      if (dt->data.t_qual.q_key == DG_PTR_T) {
	long non;
	dg_type pdt = dt->data.t_qual.typ;
	if (pdt->key == DGT_BASIC) {
	  long pn = out_sh_type(pdt->data.t_bas.b_sh, pdt->data.t_bas.tnam);
	  non = stab_ptrs[pn];
	  if (non == 0) {
	    non = (dt->outref.k < 0 ? dt->outref.u.l : next_typen());
	    stab_ptrs[pn] = non;
	    IGNORE fprintf(dg_file, "%ld=*%ld", non, pn);
	  } else {
	    IGNORE fprintf(dg_file, "%ld", non);
	  }
        } else {
	  non = (dt->outref.k < 0 ? dt->outref.u.l : next_typen());
	  IGNORE fprintf(dg_file, "%ld=*", non);
	  out_dt_shape(pdt);
	}
	dt->outref.u.l = non;
	dt->outref.k = LAB_D;
	last_type_sz = 32;
	set_stab_size(non);
      } else {
	dg_type pdt = dt->data.t_qual.typ;
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
	  long lwb = no(son(x.lower.x));
	  long upb = no(son(x.upper.x));
	  long stride = no(son(dt->data.t_arr.stride));
	  dg_type index_type = x.d_typ;
	  dg_type element_type = dt->data.t_arr.elem_type;
	  IGNORE fprintf(dg_file, "%ld=", non);
	  IGNORE fprintf(dg_file, "ar");
	  out_dt_shape(index_type);
	  IGNORE fprintf(dg_file, ";%ld;%ld;", lwb, upb);
	  out_dt_shape(element_type);
	  last_type_sz = stride *(upb - lwb + 2);
	  set_stab_size(non);
	  break;
	}
	if (x.d_key == DG_DIM_NONE) {
	  dg_type index_type = x.d_typ;
	  dg_type element_type = dt->data.t_arr.elem_type;
	  IGNORE fprintf(dg_file, "%ld=", non);
	  IGNORE fprintf(dg_file, "ar");
	  out_dt_shape(index_type);
	  IGNORE fprintf(dg_file, ";0;0;");
	  out_dt_shape(element_type);
	  last_type_sz = 0;
	  set_stab_size(non);
	  break;
	}
      }
      failer("complex array");
      break;
    }

    case DGT_ENUM: {
      int i;
      dg_enum *el = dt->data.t_enum.values.array;
      if (dt->outref.k >= 0) {
	dt->outref.u.l = next_typen();
      }
      dt->outref.k = LAB_D;
      IGNORE fprintf(dg_file, "%ld=e", dt->outref.u.l);
      for (i = 0; i < dt->data.t_enum.values.len; i++) {
	  IGNORE fprintf(dg_file, "%s:%d,", el[i].enam, no(son(el[i].value)));
      }
      IGNORE fprintf(dg_file, ";");
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
      IGNORE fprintf(dg_file, "%ld=%c%d", dt->outref.u.l, su,
		     shape_size(s) / 8);
      for (i = 0; i < dt->data.t_struct.u.fields.len; i++) {
	long offset = no(son(el[i].d.cm_f.f_offset));
	if (depth_now >= max_depth) {
	  depth_now = 0;
	  IGNORE fprintf(dg_file, "\\\\\",0x80,0,%d,%d\n", 0, 0);
	  IGNORE fprintf(dg_file, "\t.stabs\t\"");
	}
	depth_now++;
	IGNORE fprintf(dg_file, "%s:", el[i].d.cm_f.fnam);
	out_dt_shape(el[i].d.cm_f.f_typ);
	IGNORE fprintf(dg_file, ",%ld,%ld;", offset,
		       type_size(el[i].d.cm_f.f_typ));
      }
      IGNORE fprintf(dg_file, ";");
      last_type_sz = shape_size(s);
      set_stab_size(dt->outref.u.l);
      break;
    }

    case DGT_BITF: {
      bitfield_variety bv;
      bv = dt->data.t_bitf.bv;
      IGNORE fprintf(dg_file, "%d",(bv.has_sign ? STAB_SINT : STAB_UINT));
      last_type_sz = bv.bits;
      break;
    }

    case DGT_PROC: {
      dg_type result_type = dt->data.t_proc.res_type;
      long non1 = next_typen();
      long non2 = next_typen();
      dt->outref.u.l = non1;
      dt->outref.k = LAB_D;
      IGNORE fprintf(dg_file, "%ld=*%ld=f", non1, non2);
      out_dt_shape(result_type);
      last_type_sz = 32;
      set_stab_size(non1);
      set_stab_size(non2);
      break;
    }

    default : {
      IGNORE fprintf(dg_file, "%d", STAB_VOID);
      dt->outref.u.l = STAB_VOID;
      dt->outref.k = LAB_D;
      last_type_sz = 0;
      break;
    }
  }
#if 0
  if (dt->mor && dt->mor->this_tag) {
    dt->mor->this_tag->outref = dt->outref;
  }
#endif
  return;
}

#else

static void
out_dt_shape(diag_type dt)
{
    if (dt->been_outed) {
	IGNORE fprintf(dg_file, "%d",(int)dt->been_outed);
	last_type_sz = get_stab_size(dt->been_outed);
	return;
    }

    /* SunOS as(1) rejects stab lines >2k so reduce size arbitrarily */
    if (depth_now >= max_depth) {
	IGNORE fprintf(dg_file, "%d", STAB_SLONG);
	return;
    }
    depth_now++;

    switch (dt->key) {
	case DIAG_TYPE_PTR: {
	    long non;
	    diag_type pdt = dt->data.ptr.object;
	    if (pdt->key == DIAG_TYPE_VARIETY) {
		long pn = out_sh_type(f_integer(pdt->data.var));
		non = stab_ptrs[pn];
		if (non == 0) {
		    non = next_typen();
		    stab_ptrs[pn] = non;
		    IGNORE fprintf(dg_file, "%ld=*%ld", non, pn);
		} else {
		    IGNORE fprintf(dg_file, "%ld", non);
		}
	    } else {
		non = next_typen();
		IGNORE fprintf(dg_file, "%ld=*", non);
		out_dt_shape(dt->data.ptr.object);
	    }
	    dt->been_outed = non;
	    last_type_sz = 32;
	    set_stab_size(non);
	    break;
	}

	case DIAG_TYPE_ARRAY: {
#if 0
	    long str = no(dt->data.array.stride);
#endif
	    long lwb = no(dt->data.array.lower_b);
	    long upb = no(dt->data.array.upper_b);
	    diag_type index_type = dt->data.array.index_type;
	    diag_type element_type = dt->data.array.element_type;
	    long non = next_typen();
	    dt->been_outed = non;
	    IGNORE fprintf(dg_file, "%ld=ar", non);
	    out_dt_shape(index_type);
	    IGNORE fprintf(dg_file, ";%ld;%ld;", lwb, upb);
	    out_dt_shape(element_type);
	    last_type_sz *= (upb - lwb + 1);
	    set_stab_size(non);
	    break;
	}

	case DIAG_TYPE_STRUCT:
	case DIAG_TYPE_UNION: {
	    int i;
	    char su;
	    shape s;
	    diag_field_list fields;
	    long non = next_typen();
	    dt->been_outed = non;

	    if (dt->key == DIAG_TYPE_STRUCT) {
		fields = dt->data.t_struct.fields;
		s = dt->data.t_struct.tdf_shape;
		su = 's';
	    } else {
		fields = dt->data.t_union.fields;
		s = dt->data.t_union.tdf_shape;
		su = 'u';
	    }
	    IGNORE fprintf(dg_file, "%ld=%c%d", non, su, shape_size(s) / 8);

	    for (i = fields->lastused - 1; i >= 0; i--) {
		diag_field sf = (fields->array)[i];
		long offset = no(sf->where);

		if (depth_now >= max_depth) {
		    return;
		}
		depth_now++;
		IGNORE fprintf(dg_file, "%s:", sf->field_name.ints.chars);
		out_dt_shape(sf->field_type);
		IGNORE fprintf(dg_file, ",%ld,%ld;", offset, last_type_sz);
	    }
	    IGNORE fprintf(dg_file, ";");
	    last_type_sz = shape_size(s);
	    set_stab_size(non);
	    break;
	}

	case DIAG_TYPE_VARIETY: {
	    dt->been_outed = out_sh_type(f_integer(dt->data.var));
	    IGNORE fprintf(dg_file, "%ld", dt->been_outed);
	    break;
	}

	case DIAG_TYPE_PROC: {
	    diag_type result_type = dt->data.proc.result_type;
	    long non1 = next_typen();
	    long non2 = next_typen();
	    dt->been_outed = non1;
	    IGNORE fprintf(dg_file, "%ld=*%ld=f", non1, non2);
	    out_dt_shape(result_type);
	    last_type_sz = 32;
	    set_stab_size(non1);
	    set_stab_size(non2);
	    break;
	}

	case DIAG_TYPE_LOC: {
	    /* +++ use qualifier which gives "const"/"volatile" */
	    out_dt_shape(dt->data.loc.object);
	    break;
	}

	case DIAG_TYPE_FLOAT: {
	    dt->been_outed = out_sh_type(f_floating(dt->data.f_var));
	    IGNORE fprintf(dg_file, "%ld", dt->been_outed);
	    break;
	}

	case DIAG_TYPE_NULL: {
	    IGNORE fprintf(dg_file, "%d", STAB_VOID);
	    last_type_sz = 0;
	    break;
	}

	case DIAG_TYPE_BITFIELD: {
	    long sz = dt->data.bitfield.no_of_bits.nat_val.small_nat;
	    IGNORE fprintf(dg_file, "%d", STAB_SINT);
	    last_type_sz = sz;
	    break;
	}

	case DIAG_TYPE_ENUM: {
	    int i;
	    enum_values_list enumvals = dt->data.t_enum.values;
	    long non = next_typen();
	    dt->been_outed = non;
	    IGNORE fprintf(dg_file, "%ld=e", non);
	    for (i = enumvals->lastused - 1; i >= 0; i--) {
		enum_values ef = (enumvals->array)[i];
		IGNORE fprintf(dg_file, "%s:%d,", ef->nme.ints.chars,
			       no(ef->val));
	    }
	    IGNORE fprintf(dg_file, ";");
	    last_type_sz = 32;
	    set_stab_size(non);
	    break;
	}

	default : {
	    IGNORE fprintf(dg_file, "%d", STAB_VOID);
	    last_type_sz = 0;
	    break;
	}
    }
    return;
}

#endif


/*
    OUTPUT DIAGNOSTICS FOR A GLOBAL VARIABLE
*/

#ifdef NEWDIAGS

void
out_diag_global(dg_name di, int global, int cname, char * pname)
{
  char* nm;
  dg_type dt;
  if (!di || di->key != DGN_OBJECT) {
    return;
  }
  nm = idname_chars(di->idnam);
  dt = di->data.n_obj.typ;

  if (di->whence.line) {
    stabd(di->whence.file, di->whence.line, -N_DSLINE);
  }
  IGNORE fprintf(dg_file, "\t.stabs\t\"%s:%c", nm, (global ? 'G' : 'S'));
  OUT_DT_SHAPE(dt);
  if (global) {
    IGNORE fprintf(dg_file, "\",0x20,0,%ld,0\n", di->whence.line);
  } else {
    IGNORE fprintf(dg_file, "\",0x28,0,%ld,", di->whence.line);
    if (cname == -1) {
      outs(pname);
    } else {
      outs(local_prefix);
      outn((long)cname);
    }
    d_outnl();
  }
  return;
}

#else

void
diag_val_begin(diag_global *d, int global, int cname, char *pname)
{
  stabd(find_file(d->data.id.whence.file->file.ints.chars),
	(long)d->data.id.whence.line_no.nat_val.small_nat, -N_DSLINE);

  IGNORE fprintf(dg_file, "\t.stabs\t\"%s:%c", d->data.id.nme.ints.chars,
		 (global ? 'G' : 'S'));
  OUT_DT_SHAPE(d->data.id.new_type);
  if (global) {
    IGNORE fprintf(dg_file, "\",0x20,0,%d,0\n",
		   d->data.id.whence.line_no.nat_val.small_nat);
  } else {
    IGNORE fprintf(dg_file, "\",0x28,0,%d,",
		   d->data.id.whence.line_no.nat_val.small_nat);
    if (cname == -1) {
      outs(pname);
    } else {
      outs(local_prefix);
      outn((long)cname);
    }
    d_outnl();
  }
  return;
}

void
diag_val_end(diag_global *d)
{
  UNUSED(d);
  return;
}

#endif


/*
    OUTPUT DIAGNOSTICS FOR A PROCEDURE
*/

#ifdef NEWDIAGS

void
diag_proc_begin(dg_name di, int global, int cname, char *pname)
{
  char *nm;
  dg_type dt;
  last_proc_pname = pname;
  last_proc_cname = cname;
  if (!di || di->key != DGN_PROC) {
    return;
  }
  nm = idname_chars(di->idnam);
  dt = di->data.n_proc.typ;
  if (dt->key == DGT_PROC) {	/* it should be */
    dt = dt->data.t_proc.res_type;
  }

  if (di->whence.line) {
    stabd(di->whence.file, di->whence.line, 0);
  }
  outs("\t.stabs\t\"");
  outs(nm);
  if (global) {
    outs(":F");
  } else {
    outs(":f");
  }
  OUT_DT_SHAPE(dt);
  outs("\",0x24,0,0,");
  out_procname();
  d_outnl();
  return;
}

#else

void
diag_proc_begin(diag_global *d, int global, int cname, char *pname)
{
  last_proc_pname = pname;
  last_proc_cname = cname;
  if (!d) {
    return;
  }

  stabd(find_file(d->data.id.whence.file->file.ints.chars),
	(long)d->data.id.whence.line_no.nat_val.small_nat, 0);

  outs("\t.stabs\t\"");
  outs(d->data.id.nme.ints.chars);
  if (global) {
    outs(":F");
  } else {
    outs(":f");
  }
  OUT_DT_SHAPE(d->data.id.new_type->data.proc.result_type);
  outs("\",0x24,0,0,");
  out_procname();
  d_outnl();
  return;
}

#endif

void
diag_proc_end(void)
{
  if (del_stab_start != NULL) {
    struct del_stab_array *this_a = del_stab_start;
    int this_i = 0;
    while (this_a != c_del_array || this_i != c_del_index) {
	struct delay_stab *t;
	if (this_i == DEL_SIZE) {
	    this_a = this_a -> more;
	    this_i = 0;
	}
	t = (this_a->a) + (this_i ++);
	switch (t->del_t) {
	    case D_PARAM:
		IGNORE fprintf(dg_file, "\t.stabs\t\"%s:p", t->u.l.nm);
		OUT_DT_SHAPE(t->u.l.dt);
		IGNORE fprintf(dg_file, "\",0xa0,0,0,%d\n", t->u.l.offset + 8);
		break;
	    case D_LOCAL:
		IGNORE fprintf(dg_file, "\t.stabs\t\"%s:", t->u.l.nm);
		OUT_DT_SHAPE(t->u.l.dt);
		IGNORE fprintf(dg_file, "\",0x80,0,0,%d\n", t->u.l.offset -
			       locals_offset);
		break;
	    case D_REG:
		IGNORE fprintf(dg_file, "\t.stabs\t\"%s:r", t->u.l.nm);
		OUT_DT_SHAPE(t->u.l.dt);
		IGNORE fprintf(dg_file, "\",0x40,0,0,%d\n", t->u.l.offset);
		break;
	    default:
		IGNORE fprintf(dg_file, "\t.stabn\t0x%x,0,%d,.LL.%d-",
			       t->u.b.br, t->u.b.lev, t->u.b.lab);
		out_procname();
		d_outnl();
	}
    }
    c_del_array = del_stab_start;
    c_del_index = 0;
  }
  return;
}



/*
    OUTPUT DIAGNOSTICS FOR A LOCAL VARIABLE
*/

#ifdef NEWDIAGS

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
    id = son(id);
    if (name(id) == cont_tag && name(son(id)) == name_tag &&
	isvar(son(son(id)))) {
	  id = son(id);
    }
    if (name(id)!= name_tag || isdiscarded(id) || (isglob(son(id)) &&
	no(son(id)) == 0 && !(brog(son(id))->dec_u.dec_val.extnamed))) {
      return;
    }
    disp = no(id);
    id = son(id);
    nm = idname_chars(di->idnam);
    dt = di->data.n_obj.typ;
    t = next_del_stab();
    t->u.l.nm = nm;
    t->u.l.dt = dt;
    if (ptno(id) == reg_pl) {
      t->del_t = D_REG;
      t->u.l.offset = reg_stabno[get_reg_no(no(id))];
    } else {
      t->del_t = (param ? D_PARAM : D_LOCAL);
      t->u.l.offset = (disp + no(id)) / 8;
    }
    return;
}


#else

static void
stab_local(diag_info *d, int proc_no, exp acc)
{
    struct delay_stab *t = next_del_stab();
    t->del_t = (isparam(son(acc)) ? D_PARAM : D_LOCAL);
    t->u.l.nm = d->data.id_scope.nme.ints.chars;
    t->u.l.dt = d->data.id_scope.typ;
    t->u.l.offset = (no(acc) + no(son(acc))) / 8;
    return;
}

#endif



/*
    DEAL WITH BASIC TYPES
*/

static void
stab_types(void)
{
    total_type_sizes = NO_STABS;
    typeno = NO_STABS;
    type_sizes = (long *)xmalloc(NO_STABS * sizeof(long));
    IGNORE fputs("\t.stabs\t\"int:t1=r1;-2147483648;2147483647;\",0x80,0,0,0\n",
		 dg_file);
    IGNORE fputs("\t.stabs\t\"short int:t2=r1;-32768;32767;\",0x80,0,0,0\n",
		 dg_file);
    IGNORE fputs("\t.stabs\t\"short unsigned int:t3=r1;0;65535;\",0x80,0,0,0\n",
		 dg_file);
    IGNORE fputs("\t.stabs\t\"char:t4=r4;0;127;\",0x80,0,0,0\n", dg_file);
    IGNORE fputs("\t.stabs\t\"signed char:t5=r1;-128;127;\",0x80,0,0,0\n",
		 dg_file);
    IGNORE fputs("\t.stabs\t\"unsigned char:t6=r1;0;255;\",0x80,0,0,0\n",
		 dg_file);
    IGNORE fputs("\t.stabs\t\"long int:t7=r1;-2147483648;2147483647;\",0x80,0,0,0\n",
		 dg_file);
    IGNORE fputs("\t.stabs\t\"unsigned int:t8=r1;0;-1;\",0x80,0,0,0\n",
		 dg_file);
    IGNORE fputs("\t.stabs\t\"long unsigned int:t9=r1;0;-1;\",0x80,0,0,0\n",
		 dg_file);
    IGNORE fputs("\t.stabs\t\"float:t10=r1;4;0;\",0x80,0,0,0\n", dg_file);
    IGNORE fputs("\t.stabs\t\"double:t11=r1;8;0;\",0x80,0,0,0\n", dg_file);
    IGNORE fprintf(dg_file, "\t.stabs\t\"long double:t12=r1;%d;0;\",0x80,0,0,0\n",
		   DOUBLE_SZ / 8);
    IGNORE fputs("\t.stabs\t\"void:t13=13\",0x80,0,0,0\n", dg_file);
    IGNORE fputs("\t.stabs\t\"long long int:t14=r1;", dg_file);
    IGNORE fputs("01000000000000000000000;0777777777777777777777;\",0x80,0,0,0\n",
		 dg_file);
    IGNORE fputs("\t.stabs\t\"unsigned long long int:t15=r1;", dg_file);
    IGNORE fputs("0000000000000;01777777777777777777777;\",0x80,0,0,0\n",
		 dg_file);
    IGNORE fputs("\t.stabs\t\"__void_star:t16=*13\",0x80,0,0,0\n", dg_file);
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
    return;
}


#ifndef NEWDIAGS

/*
    DEAL WITH STRUCTURE, UNION AND ENUM TAGS
*/

void
stab_tagdefs(void)
{
    diag_tagdef **di = unit_ind_diagtags;
    int i, n = unit_no_of_diagtags, istag;

    for (i = 0; i < n; i++) {
	diag_type d = di[i]->d_type;
	istag = 1;

	switch (d->key) {
	    case DIAG_TYPE_STRUCT: {
		char *nme = d->data.t_struct.nme.ints.chars;
		if (nme && *nme) {
		    IGNORE fprintf(dg_file, "\t.stabs\t\"%s:", nme);
		} else {
		    static int s_count = 0;
		    IGNORE fprintf(dg_file, "\t.stabs\t\"_struct%d:",
				   s_count++);
		}
		break;
	    }
	    case DIAG_TYPE_UNION: {
		char *nme = d->data.t_union.nme.ints.chars;
		if (nme && *nme) {
		    IGNORE fprintf(dg_file, "\t.stabs\t\"%s:", nme);
		} else {
		    static int u_count = 0;
		    IGNORE fprintf(dg_file, "\t.stabs\t\"_union%d:", u_count++);
		}
		break;
	    }
	    case DIAG_TYPE_ENUM: {
		char *nme = d->data.t_enum.nme.ints.chars;
		if (nme && *nme) {
		    IGNORE fprintf(dg_file, "\t.stabs\t\"%s:", nme);
		} else {
		    static int e_count = 0;
		    IGNORE fprintf(dg_file, "\t.stabs\t\"_enum%d:", e_count++);
		}
		break;
	    }
	    default: {
		istag = 0;
		break;
	    }
	}
	if (istag) {
	    if (d->been_outed && 0) {
		IGNORE fprintf(dg_file, "%d", (int)d->been_outed);
	    } else {
		IGNORE fprintf(dg_file, "T");
		OUT_DT_SHAPE(d);
	    }
	    IGNORE fprintf(dg_file, "\",0x80,0,0,0\n");
	}
    }
    return;
}

#endif


/*
    DEAL WITH TYPEDEFS
*/

#ifndef NEWDIAGS

void
stab_typedefs(void)
{
    diag_descriptor *di = unit_diagvar_tab.array;
    int i, n = unit_diagvar_tab.lastused;
    for (i = 0; i < n; i++) {
	if (di[i].key == DIAG_TYPEDEF_KEY) {
	    long non = next_typen();
	    IGNORE fprintf(dg_file, "\t.stabs\t\"%s:t%ld=",
			   di[i].data.typ.nme.ints.chars, non);
	    OUT_DT_SHAPE(di[i].data.typ.new_type);
	    IGNORE fprintf(dg_file, "\",0x80,0,0,0\n");
	}
    }
    return;
}

#endif



/*
  INITIALISE DIAGNOSTICS
*/

#ifdef NEWDIAGS

void
out_diagnose_prelude(void)
{
  return;
}

#if 0
static void
prep_type(dg_type dt)
{
  if (dt->key == DGT_BASIC) {
    dt->outref.u.l = out_sh_type(dt->data.t_bas.b_sh, dt->data.t_bas.tnam);
    dt->outref.k = LAB_D;
  } else {
    last_type_sz = type_size(dt);
    dt->outref.k = -1;
    dt->outref.u.l = next_typen();
    set_stab_size(dt->outref.u.l);
  }
#if 0
  if (dt->mor && dt->mor->this_tag) {
    dt->mor->this_tag->outref = dt->outref;
  }
#endif
}
#endif

void
init_stab_aux(void)
{
  dg_compilation this_comp;
  dg_file = out_get_stream(); /* XXX: hack! */
  this_comp = all_comp_units;
  while (this_comp) {
    dg_name item = this_comp->dn_list;
    while (item) {
      if (item->key == DGN_PROC && item->data.n_proc.obtain_val) {
	prim_file = this_comp->prim_file;
      }
      item = item -> next;
    }
    this_comp = this_comp->another;
  }
  if (prim_file) {
    IGNORE fprintf(dg_file, "\t.file\t\"");
    if (prim_file->file_name[0]!= '/' && prim_file->file_path[0]) {
      IGNORE fprintf(dg_file, "%s/", prim_file->file_path);
    }
    IGNORE fprintf(dg_file, "%s\"\n",prim_file ->file_name);
    stab_file(prim_file);
  } else {
    IGNORE fprintf(dg_file, "\t.file\t\"no_source_file\"\n");
  }
  stab_types();
#if 0
  this_comp = all_comp_units;
  while (this_comp) {
    dg_name item = this_comp->dn_list;
    while (item) {
      if (item->key == DGN_TYPE) {
	dg_type dt = item->data.n_typ.raw;
	char *s = idname_chars(item->idnam);
	if (s[0]) {
	  if (!dt->outref.k) {
	    prep_type(dt);
	  }
	} else if ((dt->key == DGT_STRUCT &&
		    dt->data.t_struct.idnam.id_key == DG_ID_SRC &&
		    (s = dt->data.t_struct.idnam.idd.nam, s[0])) ||
		   (dt->key == DGT_ENUM && (s = dt->data.t_enum.tnam, s[0]))) {
	  if (!dt->outref.k) {
	    prep_type(dt);
	  }
	}
      }
      item = item->next;
    }
    this_comp = this_comp->another;
  }
#endif
  this_comp = all_comp_units;
  while (this_comp) {
    dg_name item = this_comp->dn_list;
    while (item) {
      if (item->key == DGN_TYPE && item->data.n_typ.raw->key != DGT_UNKNOWN) {
	dg_type dt = item->data.n_typ.raw;
	char *s = idname_chars(item->idnam);
	if (s[0]) {
	  IGNORE fprintf(dg_file, "\t.stabs\t\"%s:", s);
	  if (dt->outref.k == LAB_STR) {
	    dt->outref.k = LAB_D;
	    dt->outref.u.l = find_basic_type(dt->outref.u.s);
	  }
	  if (dt->outref.k == LAB_D) {
		IGNORE fprintf(dg_file, "%d", (int)dt->outref.u.l);
	  } else {
		IGNORE fprintf(dg_file, "t");
		OUT_DT_SHAPE(dt);
	  }
	  IGNORE fprintf(dg_file, "\",0x80,0,0,0\n");
	} else if ((dt->key == DGT_STRUCT &&
		    (dt->data.t_struct.idnam.id_key == DG_ID_SRC ||
		     dt->data.t_struct.idnam.id_key == DG_ID_EXT) &&
		    (s = dt->data.t_struct.idnam.idd.nam, s[0])) ||
		   (dt->key == DGT_ENUM && (s = dt->data.t_enum.tnam, s[0]))) {
	  IGNORE fprintf(dg_file, "\t.stabs\t\"%s:", s);
	  if (dt->outref.k == LAB_D) {
	    IGNORE fprintf(dg_file, "%d",(int)dt->outref.u.l);
	  } else {
	    IGNORE fprintf(dg_file, "T");
	    OUT_DT_SHAPE(dt);
	  }
	  IGNORE fprintf(dg_file, "\",0x80,0,0,0\n");
	}
#if 0
	if (item->mor && item->mor->this_tag) {
	  item->mor->this_tag->outref = item->data.n_typ.raw->outref;
	}
#endif
      }
      item = item->next;
    }
    this_comp = this_comp->another;
  }
  return;
}

#else

void
out_diagnose_prelude(void)
{
    dg_file_name = tmpnam(NULL);
    dg_file = fopen(dg_file_name, "w");
    if (dg_file == NULL) {
	failer("Can't open temporary diagnostics file");
	exit(EXIT_FAILURE);
    }
    stab_types();
    return;
}

void
init_stab_aux(void)
{
    int c;
    FILE *f;
    int i, j = -1;
    for (i = 0; i < nofds; i++) {
	char *s = fds[i]->file.ints.chars;
	int n = (int)strlen(s);
	if (n && s[n - 1]!= 'h') {
	    j = i;
	}
    }
    IGNORE fclose(dg_file);
    dg_file = out_get_stream(); /* XXX: hack! */
    if (j >= 0) {
	IGNORE fprintf(dg_file, "\t.file\t\"%s\"\n", fds[j] ->file.ints.chars);
    } else {
	IGNORE fprintf(dg_file, "\t.file\t\"no_source_file\"\n");
    }
    stab_file((long)j, 0);
    f = fopen(dg_file_name, "r");
    if (f == NULL) {
	failer("Can't open temporary diagnostics file");
	exit(EXIT_FAILURE);
    }
    while (c = fgetc(f), c != EOF) {
	outc(c);
    }
    IGNORE fclose(f);
    remove(dg_file_name);
    return;
}

#endif


void
out_diagnose_postlude(void)
{
    long i = next_d_lab();
    IGNORE fprintf(dg_file, ".LL.%ld:\n", i);
    IGNORE fprintf(dg_file, "\t.stabs\t\"\",0x64,0,0,.LL.%ld\n", i);
    return;
}
