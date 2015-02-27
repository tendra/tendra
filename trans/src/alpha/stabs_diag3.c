/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
  This file contains functions to handle code diagnostics for
  alpha/OSF1. (largely based on the mips installer version
  'stabs_diag3.c').
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/xalloc.h>

#include <reader/exp.h>
#include <reader/code.h>
#include <reader/token.h>

#include <construct/shape.h>
#include <construct/exp.h>
#include <construct/tags.h>

#include <diag3/diagtypes.h>
#include <diag3/diag_fns.h>
#include <diag3/diagglob.h>
#include <diag3/mark_scope.h>
#include <diag3/diaginfo1.h>
#include <diag3/diag_reform.h>

#include <symtab/symconst.h>
#include <symtab/symtab.h>
#include <symtab/new_symbol.h>

#include <main/driver.h>
#include <main/print.h>

#include "procrectypes.h"
#include "procrecs.h"
#include "bitsmacs.h"
#include "locate.h"
#include "stabs_diag3.h"
#include "ibinasm.h"
#include "out_ba.h"
#include "make_code.h"
#include "cross.h"

extern bool last_param(exp e);
extern long currentfile;
/* our current fileno  */
extern long mainfile;
/* default fileno for no diags or shape output */


int *file_dnos;		/* dense nos for files */

filename * fds;
int nofds = 0;
int szfds = 0;


static void
collect_files(filename f)
{
  if (nofds>=szfds) {
    fds = (filename*)xrealloc(fds,(size_t)(szfds+=5)*sizeof(filename));
  }
  fds[nofds++] = f;
}

int find_file
(const char *name)
{
  int i;
  for (i=0; i<nofds; i++) {
    if (strcmp(name, fds[i] ->file.ints.chars) ==0) return i;
  }
  return 0;
}



/* produce symnos for all text files in compilation */
void symnosforfiles
(void)
{
  int   i;
  file_dnos = (int *)xcalloc(nofds, sizeof(int));
  for (i = 0; i < nofds; i++) {
    file_dnos[i] = new_lsym_d(fds[i] ->file.ints.chars, 0, stFile, scText,
			      (diag_type)0, i);
  }
}

/* output .file directive for file i */
static void
stab_file(long i, bool internal)
{
  int l;

  assert(internal == false);

  UNUSED(internal);

  if (currentfile == i)
    return;

  l = (int)strlen(fds[i] ->file.ints.chars);

  if (as_file) {
    asm_printop(".file %d \"%s\"", file_dnos[i],
		fds[i] ->file.ints.chars+1);
  }

  out_value(file_dnos[i], ifile, make_INT64(0,l), 0);
  out_data(fds[i] ->file.ints.chars, l);

  currentfile = i;
}

int currentlno = -1;		/* the last line number output */

static void
stabd(long findex, long lno, int seg)
{
  UNUSED(seg);

  if (findex==currentfile && lno==currentlno) return;
  stab_file(findex, false);
  if (as_file)
    asm_printop(".loc %d %ld", file_dnos[findex], lno);
  out_loc(file_dnos[findex],(unsigned)lno);
  currentlno = lno;
}

static char lexlev[] = "0";	/* historic !!! */


static void
diagbr_open(long findex)
{
  int symno;
  stab_file(findex, false);
  symno = new_lsym_d(NULL, 0, stBlock, scText,(diag_type)0,
      currentfile);
  lexlev[0] ++;
  if (as_file) {
    asm_printop(".bgnb %d", symno);
  }
  out_ent(symno, ibgnb, 0);
}

static void
diagbr_close(long findex)
{
  int symno;
  stab_file(findex, false);
  symno = new_lsym_d(NULL, 0, stEnd, scText,(diag_type)0,
      currentfile);
  lexlev[0] --;
  if (as_file) {
    asm_printop(".endb %d", symno);
  }
  out_ent(symno, iendb, 0);
}



/*
   output appropriate rubbish to symbol table to indicate the declaration of a
   local identifier, nm, defined by id, displaced by disp; findex is the index
   of the file containing the declaration.  The text below gives o/p for
   identifiers allocated in registers; in fact, with current translator,
   none are used by stab_local. I don't even know whether the MIPS dbx can
   actually use them.
*/
static void
stab_local(char *nm, diag_type dt, exp ldid, int disp, long findex)
{

  int fs = frame_size >> 3;
  exp id = son(ldid);
  short   sc;
  int  v;
  disp+=no(ldid);
again:
  if (name(id) == ident_tag) {
    if ((props(id) & defer_bit) == 0) {
      if ((props(id) & inreg_bits)!= 0) {
	sc = scRegister;
	v = no(id);
	/*if (as_file){
	  x (asm_printf( " # %s is in $%d\n", nm, v));
	  }*/
      }
      else if ((props(id) & infreg_bits)!= 0) {
	sc = scRegister;
	v = (no(id) << 1) + float_register;
/*	  if (as_file)
	  x (asm_printf( " # %s is in $f%d\n", nm, v - float_register));*/
      }
      else {
	v = ((no(id) & ~0x3f) >> 4) + (locals_offset >> 3) + disp / 8 - fs;
	sc = scAbs;
/*	  if (as_file)
	  x (asm_printf(
	  " # %s is in %ld($fp)  == %ld($29)\n", nm,
	  v, v + fs));*/

      }
      IGNORE new_lsym_d (nm,v,/*(isparam(id))?stParam :*/stLocal,sc,dt,findex);
    }
    else {
      exp sn = son(id);
      int d = disp;
      while (sn != NULL) {
	switch (name(sn)) {
	  case name_tag: {
	    disp = d + no(sn);
	    id = son(sn);
	    if (isvar(id))dt = dt->data.ptr.object;
	    goto again;
	  }
	  case reff_tag: {
	    d += no(sn);
	    sn = son(sn);
	    break;
	  }
	  case cont_tag: {
	    sn = son(sn);
	    break;
	  }
	  default:
	  return;
	}
      }
    }
  }
}

static void output_diag
(diag_info *d, int proc_no, exp e)
{
  exp x;

  UNUSED(proc_no);

  if (d->key == DIAG_INFO_SOURCE) {
    sourcemark * s = & d->data.source.beg;
    int f = find_file(s->file->file.ints.chars);
    stabd(f, s->line_no.nat_val.small_nat, 0);
    return;
  }
  if (d->key != DIAG_INFO_ID) return;
  x = d->data.id_scope.access;
  if (isglob(son(x)) || no(son(x)) ==1) return;
  /* can't output global values as local names in dbx
     && not only diag use */
  mark_scope(e);
  if (props(e) & 0x80) {
    stabd(currentfile, currentlno+1, 0); /* don't have proper lineno */
    diagbr_open(currentfile);
  }
  stab_local(d->data.id_scope.nme.ints.chars, d->data.id_scope.typ,
	     x,0,currentfile);
  if (last_param(son(x))) {
    stabd(currentfile, currentlno+1, 0); /* don't have proper lineno */
  }
}


static void output_end_scope
(diag_info *d, exp e)
{
  if (d->key == DIAG_INFO_SOURCE) {
    sourcemark * s = & d->data.source.end;
    int f = find_file(s->file->file.ints.chars);
    int lno = s->line_no.nat_val.small_nat;
    stabd(f, (lno==currentlno)?lno+1:lno, 0); /*approx */
    return;
  }
  if (d -> key == DIAG_INFO_ID && props(e) & 0x80) {
    diagbr_close(currentfile);
  }
}

/*
  The following procs are concerned with expressing TDF
  types as dbx types.  The possible circularity of types and
  the vagaries of the type representation contribute to their
  complication.
*/

typedef struct {
  char *n;
  int  v;
  int   st;
  int   sc;
  diag_type s;
} tsym;
static int notsyms = 0;
static int nexttsym = 0;
static tsym * ats = NULL;


/*
   used to accumulate all the type reprs arising
   from shapes in the program by calling addtsym ....
*/
void addtsym
(char *n, int v, int st, int sc, diag_type s)
{
  tsym * a;
  if (nexttsym >= notsyms) {
    ats = (tsym *)xrealloc((void *)ats,(size_t)(nexttsym + 100)* sizeof(tsym));
    notsyms = nexttsym + 100;
  }
  a = &ats[nexttsym++];
  a -> n = n;
  a -> v = v;
  a -> st = st;
  a -> sc = sc;
  a -> s = s;
}

typedef struct {
  diag_type sutype;
  int   symindex;
} shauxt;
static int noshaux = 0;
int nextshaux = 0;
shauxt * shaux = NULL;


/*
   used to remember all the indexes into the auxilliary
   symbol table for all the shapes in the program
*/
bool eq_sutype
(diag_type a, diag_type b)
{

  diag_field_list  fa;
  diag_field_list  fb;
  int j;
  if (a==b) return 1;
  if (a->key != b->key) return 0;
  if (a->key != DIAG_TYPE_STRUCT && a->key != DIAG_TYPE_UNION) return 0;
   if (strcmp(a->data.t_struct.nme.ints.chars, b->data.t_struct.nme.ints.chars))
     return 0;
  fa = a->data.t_struct.fields;
  fb = b->data.t_struct.fields;
  if (fa->lastused != fb->lastused) return 0;
  for (j=fa->lastused-1; j>=0; j--) {
    diag_field sfa = (fa->array)[j];
    diag_field sfb = (fb->array)[j];
    if (strcmp(sfa->field_name.ints.chars, sfb->field_name.ints.chars))
      return 0;
  }
  return(bool)eq_shape(a->data.t_struct.tdf_shape,b->data.t_struct.tdf_shape);
}


/*
   finds the index into the auxilliary table for type s
*/
int find_aux
(diag_type s)
{
  int   i;
  for (i = 0; i < nextshaux; i++) {
    if (eq_sutype(s, shaux[i].sutype))
      return shaux[i].symindex;
  }
  return - 1;
}


/*
   remembers ind as index into aux table for shape s
*/
static void addaux
(diag_type s, int ind)
{

  shauxt * x;
  if (nextshaux >= noshaux) {
    shaux = (shauxt *)xrealloc((void *)shaux,
				(size_t)(nextshaux + 10)* sizeof(shauxt));
  }
  x = &shaux[nextshaux++];
  x -> sutype = s;
  x -> symindex = ind;
}

static diag_tagdef ** su_diags = NULL;
static long no_of_sus = 0;
static long leng_sus = 0;

static void
OUTPUT_DIAG_TAGS(void)
{
  /*collects structs & unions */
  diag_tagdef ** di = unit_ind_diagtags;
  long n = unit_no_of_diagtags;
  long i;
  long il = no_of_sus;

  for (i=0; i<n; ++i) {
    diag_type d = di[i] ->d_type;
    switch (d -> key) {
      case DIAG_TYPE_STRUCT:
      case DIAG_TYPE_UNION: {
	int j;
	for (j=0; j < il; j++) {
	  if (eq_sutype(d, su_diags[j] ->d_type))break;
	}
	if (j!=il)break;
	if (no_of_sus >= leng_sus) {
	  su_diags = (diag_tagdef**)xrealloc(su_diags,
				(size_t)(leng_sus+=20)*sizeof(diag_tagdef*));
	}
	su_diags[no_of_sus++] = di[i];
	break;
      }
      default: break;
    }
  }
}



/*
   outputs symbol table info for all struct & union  in program
*/
void stab_types
(void)
{
  int i;
  int firsts = get_sym_index(mainfile);
  for (i = 0; i < no_of_sus; ++i) {/* treat struct shapes */
    int   j;
    diag_tagdef * sc = su_diags[i];
    switch (sc->d_type->key) {
      case DIAG_TYPE_STRUCT:
      case DIAG_TYPE_UNION: {
	diag_field_list  fields = sc->d_type->data.t_struct.fields;
	shape s = sc->d_type->data.t_struct.tdf_shape;
	char * nme = sc->d_type->data.t_struct.nme.ints.chars;
	addaux(sc->d_type, nexttsym+firsts);
	addtsym(nme, shape_size(s) >>3, stBlock, scInfo, sc->d_type);
	for (j=fields->lastused-1; j>=0; j--) {
	  diag_field sf = (fields->array)[j];
	  addtsym(sf->field_name.ints.chars, no(sf->where), stMember, scInfo,
		  sf->field_type);
	}
	break;
      }
      default:;
    }
    addtsym("", 0, stEnd, scInfo,(diag_type)0);
  }

  for (i = 0; i < nexttsym; i++) {/* output accumulated type info */
    tsym * t = &ats[i];
   IGNORE new_lsym(t -> n, t -> v, t -> st, t -> sc, t->s, mainfile);
  }

  for (i = 0; i < unit_diagvar_tab.lastused; ++i) {
  /* associated names of types */
    diag_descriptor * dd = unit_diagvar_tab.array+i;
    if (dd->key == DIAG_TYPEDEF_KEY) {
     IGNORE new_lsym_d(dd->data.typ.nme.ints.chars, 0, stTypedef, scInfo,
		       dd->data.typ.new_type, mainfile);
    }
  }
  free(ats);
}

static diag_descriptor *
NEW_DIAG_GLOBAL(diag_descriptor *d)
{
	return d;
}

static void
OUTPUT_GLOBALS_TAB(void)
{
}

const struct diag3_driver diag3_driver_stabs = {
	NULL,
	NULL,

	stabd,
	NEW_DIAG_GLOBAL,
	OUTPUT_GLOBALS_TAB,
	OUTPUT_DIAG_TAGS,
	collect_files,
	stab_file,
	NULL,
	NULL,
	NULL,
	NULL,

	output_diag,
	output_end_scope,

	NULL,
	NULL,

	NULL,
	NULL
};

