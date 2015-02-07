/* $Id$ */

/*
 * Copyright 2002-2014, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>
#include <stdio.h>

#include <shared/check.h>

#include <reader/token.h>

#include <diag3/diag_fns.h>
#include <diag3/diagglob.h>
#include <diag3/diaginfo1.h>

#include <main/driver.h>

#include <construct/machine.h>

#include "cv_types.h"
#include "cv_outtype.h"


/* VARIABLES */
/* All variables initialised */

static int crt_proc_start;
static int last_line_no;
static char *main_filename;	/* init by diagnose_prelude */
static int filename_space = 0;	/* init by diagnose_prelude */
static long filename_pos;
static int filename_gate = 0;	/* init by diagnose_prelude */

/* PROCEDURES */

static int
check_filename(sourcemark sm)
{
  if (main_filename) {
      if (!strcmp(main_filename, sm.file->file.ints.chars)) {
        return 1;
      }
      return 0;
  } else {
      main_filename = sm.file->file.ints.chars;
      return 1;
  }
}

void
out_diagnose_prelude(void)
{
  main_filename = (char *)0;
  filename_space = 0;
  filename_gate = 0;
  return;
}

void
out_diagnose_postlude(void)
{
  return;
}


#ifdef TDF_DIAG4

void
code_diag_info(diag_info *d, int proc_no, void(*mcode)(void *), void *args)
{
  if (d == nildiag) {
   (*mcode)(args);
    return;
  }
  switch (d->key) {
    case DIAG_INFO_SCOPE: {
	fprintf(as_file, " .def .bb; .val .; .scl 100;  .line %d; .endef\n",
		last_line_no);
	code_diag_info(d->more, proc_no, mcode, args);
	fprintf(as_file, " .def .eb; .val .; .scl 100; .line %d; .endef\n",
		last_line_no);
	return;
    }
    case DIAG_INFO_SOURCE: {
	int l = (int)d->data.source.beg.line_no.nat_val.small_nat -
	    crt_proc_start + 1;
	if (check_filename(d -> data.source.beg) && l != last_line_no) {
	  last_line_no = l;
	  if (l > 0) {
	    fprintf(as_file, " .ln %d\n", l);
	  }
	}
	code_diag_info(d->more, proc_no, mcode, args);
	return;
    }
    case DIAG_INFO_ID: {
	exp acc = d->data.id_scope.access;
	ot ty;
	int p, param_dec;
	if (name(acc)!= hold_tag && name(acc) != hold2_tag) {
	  failer("not hold_tag");
	}
	acc = son(acc);
	if (name(acc) == cont_tag && name(son(acc)) == name_tag &&
	    isvar(son(son(acc)))) {
	  acc = son(acc);
	}
	if (name(acc) == name_tag && !isdiscarded(acc) && !isglob(son(acc))) {
	  p = (no(acc) + no(son(acc))) / 8;
	  param_dec = isparam(son(acc));
	  fprintf(as_file, " .def %s; .val ", d->data.id_scope.nme.ints.chars);
	  if (param_dec) {
	    fprintf(as_file, "%d", p + 8);
	  } else {
	    fprintf(as_file, "%d-.Ldisp%d", p, proc_no);
	  }
	  fprintf(as_file, "; .scl %d; ",(param_dec) ? 9 : 1);
	  ty = out_type(d->data.id_scope.typ, 0);
	  fprintf(as_file, ".type 0%o; .endef\n", ty.type + (ty.modifier << 4));
	}
	code_diag_info(d->more, proc_no, mcode, args);
    }
  }
  return;
}

#else

void
output_diag(diag_info *d, int proc_no, exp e)
{
  if (d->key == DIAG_INFO_SOURCE) {
     int l = (int)d->data.source.beg.line_no.nat_val.small_nat -
	 crt_proc_start + 1;
     if (!check_filename(d -> data.source.beg)) {
       return;
     }

     if (l == last_line_no) {
       return;
     }
     last_line_no = l;
     if (l > 0) {
       fprintf(as_file, " .ln %d\n", l);
     }
     return;
  }
  if (d -> key == DIAG_INFO_ID) {
     ot ty;
     exp acc = d -> data.id_scope.access;
     int p = (no(acc) + no(son(acc))) / 8;
     int param_dec = isparam(son(acc));

     mark_scope(e);

     if (props(e) & 0x80) {
       fprintf(as_file, " .def .bb; .val .; .scl 100;  .line %d; .endef\n",
	       last_line_no);
     }

     fprintf(as_file, " .def %s; .val ", d->data.id_scope.nme.ints.chars);
     if (param_dec) {
       fprintf(as_file, "%d", p + 8);
     } else {
       fprintf(as_file, "%d-.Ldisp%d", p, proc_no);
     }
     fprintf(as_file, "; .scl %d; ",(param_dec) ? 9 : 1);
     ty = out_type(d -> data.id_scope.typ, 0);
     fprintf(as_file, ".type 0%o; .endef\n", ty.type + (ty.modifier<<4));

     return;
   }

  return;
}
#endif

void
output_end_scope(diag_info *d, exp e)
{
  if (d -> key == DIAG_INFO_ID && props(e) & 0x80) {
    fprintf(as_file, " .def .eb; .val .; .scl 100; .line %d; .endef\n",
	    last_line_no);
  }
  return;
}

void
diag_val_begin(diag_descriptor *d, int global, int cname, char *pname)
{
  ot typ;

  outs(" .def ");
  outs(d->data.id.nme.ints.chars);
  outs("; .val ");
  if (cname == -1) {
    outs(pname);
  } else {
    outs(local_prefix);
    outn((long)cname);
  }
  outs("; .scl ");
  outn((long)(global ? 2 : 3));
  outs("; ");
  typ = out_type(d->data.id.new_type, 0);
  fprintf(as_file, ".type 0%o; .endef\n", typ.type + (typ.modifier << 4));
  return;
}

void
diag_val_end(diag_descriptor *d)
{
  UNUSED(d);
  return;
}

void
diag_proc_begin(diag_descriptor *d, int global, int cname, char *pname)
{
  ot typ;
  UNUSED(cname);

  if (!d) {
    return;
  }

  check_filename(d->data.id.whence);

  outs(" .def ");
  outs(d->data.id.nme.ints.chars);
  outs("; .val ");
  outs(pname);
  outs("; .scl ");
  outn((long)(global ? 2 : 3));
  outs("; ");
  typ = out_type(d->data.id.new_type->data.proc.result_type, 0);
  fprintf(as_file, ".type 0%o; .endef\n", typ.type + (typ.modifier << 6) + 32);

  crt_proc_start = d->data.id.whence.line_no.nat_val.small_nat;
  last_line_no = 1;
  fprintf(as_file, " .def .bf; .val .; .scl 101; .line %d; .endef\n",
	  crt_proc_start);
  fprintf(as_file, " .ln 1\n");
  return;
}

void
diag_proc_end(diag_descriptor *d)
{
  if (!d) {
    return;
  }
  fprintf(as_file, " .def .ef; .val .; .scl 101; .line %d; .endef\n",
	  last_line_no + 1);
  fprintf(as_file, " .def %s; .val .; .scl -1; .endef\n",
	  d->data.id.nme.ints.chars);
  return;
}


void
cvOUTPUT_GLOBALS_TAB(void)
{
  diag_descriptor *di = unit_diagvar_tab.array;
  int n = unit_diagvar_tab.lastused;
  int i;
  ot typ;

  for (i=0; i<n; i++) {
     if (di[i].key == DIAG_TYPEDEF_KEY) {
	fprintf(as_file, " .def %s; .scl 13; ", di[i].data.typ.nme.ints.chars);
	typ = out_type(di[i].data.typ.new_type, 0);
	fprintf(as_file, ".type 0%o; .endef\n", typ.type + (typ.modifier << 4));
     }
  }
  return;
}

void
cvOUTPUT_DIAG_TAGS(void)
{
  diag_tagdef **di = unit_ind_diagtags;
  int n = unit_no_of_diagtags;
  int i;

  if (!filename_space) {
     filename_pos = ftell(as_file);
     outs("                                                                                                                      ");
     outnl();
     filename_space = 1;
   }

  for (i=0; i<n; ++i) {
     diag_type d = di[i] ->d_type;
     switch (d -> key)
      {
        case DIAG_TYPE_STRUCT:
        case DIAG_TYPE_UNION:
        case DIAG_TYPE_ENUM:
            out_tagged(d);
            break;
        default: break;
      }
   }
  return;
}

void
cvINSPECT_FILENAME(filename fn)
{
  long here;
  char *nm = fn->file.ints.chars;
  char *f;
  int len = (int)strlen(fn->file.ints.chars);

  if (filename_gate || len < 4 || len > 120 || nm[len-1] == 'h' ||
      nm[len-2]!= '.') {
    return;
  }

  f = &nm[len-2];

  while (f != nm && f[-1]!= '/') {
    --f;
  }

  filename_gate = 1;

  if (!filename_space) {
    fprintf(as_file, " .file \"%s\"\n", f);
  } else {
    here = ftell(as_file);
    fseek(as_file, filename_pos, 0);
    fprintf(as_file, " .file \"%s\"\n", f);
    fseek(as_file, here, 0);
  }
  return;
}
