/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


/**********************************************************************
$Author: release $
$Date: 1998/03/17 16:54:17 $
$Revision: 1.6 $
$Log: dg_aux.c,v $
 * Revision 1.6  1998/03/17  16:54:17  release
 * Couple of minor fixes.
 *
 * Revision 1.5  1998/03/17  16:34:58  pwe
 * correction for non-NEWDIAGS
 *
 * Revision 1.4  1998/03/15  16:00:29  pwe
 * regtrack dwarf dagnostics added
 *
 * Revision 1.3  1998/03/11  11:03:28  pwe
 * DWARF optimisation info
 *
 * Revision 1.2  1998/02/18  11:22:13  pwe
 * test corrections
 *
 * Revision 1.1.1.1  1998/01/17  15:55:46  release
 * First version to be checked into rolling release.
 *
 * Revision 1.8  1998/01/11  18:44:46  pwe
 * consistent new/old diags
 *
 * Revision 1.7  1998/01/09  09:29:40  pwe
 * prep restructure
 *
 * Revision 1.6  1997/12/04  19:36:13  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.5  1997/11/06  09:17:33  pwe
 * ANDF-DE V1.8
 *
 * Revision 1.4  1997/10/28  10:12:26  pwe
 * local location support
 *
 * Revision 1.3  1997/10/23  09:20:57  pwe
 * ANDF-DE V1.7 and extra diags
 *
 * Revision 1.2  1997/10/10  18:16:33  pwe
 * prep ANDF-DE revision
 *
 * Revision 1.1  1997/08/23  13:26:36  pwe
 * initial ANDF-DE
 *
***********************************************************************/


#include "config.h"
#include "common_types.h"
#include "basicread.h"
#include "xalloc.h"
#include "sortmacs.h"
#include "expmacs.h"
#include "tags.h"
#include "externs.h"
#include "check.h"
#include "exp.h"
#include "me_fns.h"
#include "table_fns.h"
#include "flags.h"
#include "const.h"
#include "dg_aux.h"
#include "dg_globs.h"


#ifndef NEWDIAGS
#define isdiaginfo(e)	0
#define setisdiaginfo(e)
#define isdiscarded(e)	0
#define setisdiscarded(e)
#else
static int clean_copy = 0;	/* set by copy_dg_separate */
#endif


int doing_inlining = 0;

dg_info current_dg_info = (dg_info)0;	/* needed when coding extra_diags */
exp current_dg_exp = nilexp;		/* needed when coding extra_diags */

short_sourcepos no_short_sourcepos;



#define DG_CLUMP_SIZE 50	/* Generate a clump of dg_name etc together */
#define FILE_CLUMP_SIZE 5


typedef union			/* These have similar size */
{
  struct dg_name_t	nam;
  struct dg_type_t	typ;
  struct dg_info_t	inf;
  struct dg_more_t	mor;
} dg_union;

static int dg_clump_left = 0;
static dg_union * next_dg;

static void make_dg_clump
    PROTO_Z ()
{
  next_dg = (dg_union *) xcalloc (DG_CLUMP_SIZE, sizeof (dg_union));
  dg_clump_left = DG_CLUMP_SIZE;
  return;
}

dg_name new_dg_name
    PROTO_N ( (k) )
    PROTO_T ( dg_name_key k )
{
  dg_name ans;
  if (!dg_clump_left) make_dg_clump();
  dg_clump_left --;
  ans = &((next_dg ++)->nam);
  ans->key = k;
  ans->mor = (dg_more_name)0;
  ans->next = (dg_name)0;
  return ans;
}

dg_type new_dg_type
    PROTO_N ( (k) )
    PROTO_T ( dg_type_key k )
{
  dg_type ans;
  if (!dg_clump_left) make_dg_clump();
  dg_clump_left --;
  ans = &((next_dg ++)->typ);
  ans->key = k;
  ans->outref.k = NO_LAB;
  ans->mor = (dg_more_name)0;
  return ans;
}

dg_info new_dg_info
    PROTO_N ( (k) )
    PROTO_T ( dg_info_key k )
{
  dg_info ans;
  if (!dg_clump_left) make_dg_clump();
  dg_clump_left --;
  ans = &((next_dg ++)->inf);
  ans->key = k;
  ans->this_tag = (dg_tag)0;
  ans->more = (dg_info)0;
  return ans;
}

void extend_dg_name
    PROTO_N ( (nm) )
    PROTO_T ( dg_name nm )
{
  dg_more_name mor;
  if (!dg_clump_left) make_dg_clump();
  dg_clump_left --;
  nm->mor = mor = &((next_dg ++)->mor);
  mor->this_tag = (dg_tag)0;
  mor->inline_ref = (dg_tag)0;
  mor->refspec = (dg_tag)0;
  mor->elabn = (dg_tag)0;
  mor->exptns = no_dg_type_list_option;
  mor->end_pos = no_short_sourcepos;
  mor->en_family = (dg_dim *)0;
  mor->vslot = nilexp;
  mor->repn = nilexp;
  mor->acc = DG_ACC_NONE;
  mor->virt = DG_VIRT_NONE;
  mor->isinline = 0;
  mor->prognm = 0;
  mor->isconst = 0;
  mor->isspec = 0;
  mor->issep = 0;
  mor->isnew = 0;
  mor->aderiv = 0;
  return;
}

void extend_dg_type
    PROTO_N ( (tp) )
    PROTO_T ( dg_type tp )
{
  dg_more_name mor;
  if (!dg_clump_left) make_dg_clump();
  dg_clump_left --;
  tp->mor = mor = &((next_dg ++)->mor);
  mor->this_tag = (dg_tag)0;
  mor->inline_ref = (dg_tag)0;
  mor->refspec = (dg_tag)0;
  mor->elabn = (dg_tag)0;
  mor->acc = DG_ACC_NONE;
  mor->virt = DG_VIRT_NONE;
  mor->isinline = 0;
  mor->prognm = 0;
  mor->isconst = 0;
  mor->isspec = 0;
  mor->isnew = 0;
  mor->aderiv = 0;
  return;
}

void init_dgtag
    PROTO_N ( (tg) )
    PROTO_T ( dg_tag tg )
{
  tg->key = DGK_NONE;
  tg->done = 0;
  tg->needed = 0;
  tg->any_inl = 0;
  tg->outref.k = NO_LAB;
  tg->abstract_lab = (long)0;
  tg->copy = (dg_tag)0;
  return;
}

dg_tag gen_tg_tag
    PROTO_Z ()
{
  dg_tag tg = (dgtag_struct *) xcalloc (1, sizeof (dgtag_struct));
  init_dgtag (tg);
  return tg;
}



/* The following avoids repetitions of pointers and other qualified types */

dg_type get_qual_dg_type
    PROTO_N ( (qual, typ) )
    PROTO_T ( dg_qual_type_key qual X dg_type typ )
{
  static dg_type qual_type_list [N_DG_QUAL_TYPES] = { (dg_type)0 };
  dg_type ans = qual_type_list[qual];
  while (ans) {
    if (ans->data.t_qual.typ == typ)
      return ans;
    ans = ans->data.t_qual.another;
  }
  ans = new_dg_type(DGT_QUAL);
  ans->data.t_qual.q_key = qual;
  ans->data.t_qual.typ = typ;
  ans->data.t_qual.another = qual_type_list[qual];
  qual_type_list[qual] = ans;
  return ans;
}

/* The following avoids repetitions of bitfield types */

dg_type get_dg_bitfield_type
    PROTO_N ( (typ, sha, bv) )
    PROTO_T ( dg_type typ X shape sha X bitfield_variety bv )
{
  static dg_type bf_list = (dg_type)0;
  dg_type ans = bf_list;
  while (ans) {
    if (ans->data.t_bitf.expanded == typ &&
	ans->data.t_bitf.bv.bits == bv.bits &&
	ans->data.t_bitf.bv.has_sign == bv.has_sign )
      return ans;
    ans = ans->data.t_bitf.another;
  }
  ans = new_dg_type(DGT_BITF);
  ans->data.t_bitf.expanded = typ;
  ans->data.t_bitf.sha = sha;
  ans->data.t_bitf.bv = bv;
  ans->data.t_bitf.another = bf_list;
  bf_list = ans;
  return ans;
}

/* All other types are either unlikely to be repeated, or are rare */


/* dg_idname is overkill for many purposes - we just want a string */

char * idname_chars
    PROTO_N ( (nam) )
    PROTO_T ( dg_idname nam )
{
  static char * empty = "";
  switch (nam.id_key) {
    case DG_ID_INST: failer ("inappropriate dg_instance_idname"); return empty;
    case DG_ID_NONE: return empty;
    default: return nam.idd.nam;
  }
}


/* Avoid repetition of files */

dg_filename get_filename
    PROTO_N ( (dat, host, path, nam) )
    PROTO_T ( long dat X char * host X char * path X char * nam )
{
  static dg_filename next_file = (dg_filename)0;
  static int filespace_left = 0;

  dg_filename ans = all_files;
  while (ans) {
    if (ans->file_dat == dat &&
	!strcmp (ans->file_host, host) &&
	!strcmp (ans->file_path, path) &&
	!strcmp (ans->file_name, nam) )
      return ans;
    ans = ans->another;
  }

  if (!filespace_left) {
    next_file = (dg_filename) xcalloc (FILE_CLUMP_SIZE, sizeof (struct file_t));
    filespace_left = FILE_CLUMP_SIZE;
  }
  filespace_left --;
  ans = (next_file ++);
  ans->file_dat = dat;
  ans->file_host = host;
  ans->file_path = path;
  ans->file_name = nam;
  ans->another = all_files;
  all_files = ans;
  return ans;
}


short_sourcepos shorten_sourcepos
    PROTO_N ( (pos) )
    PROTO_T ( dg_sourcepos pos )
{
  short_sourcepos ans;
  switch (pos.sp_key) {
    case SP_SHORT:
    case SP_SPAN: {
      ans.file = pos.file;
      ans.line = pos.from_line;
      ans.column = pos.from_column;
      break;
    }
    case SP_FILE: {
      ans.file = pos.file;
      ans.line = 0;
      ans.column = 0;
      break;
    }
    default: {
      ans.file = (dg_filename)0;
      ans.line = 0;
      ans.column = 0;
    }
  }
  return ans;
}

short_sourcepos end_sourcepos
    PROTO_N ( (pos) )
    PROTO_T ( dg_sourcepos pos )
{
  short_sourcepos ans;
  if (pos.sp_key == SP_SPAN) {
    ans.file = pos.to_file;
    ans.line = pos.to_line;
    ans.column = pos.to_column;
  }
  else {
    ans.file = (dg_filename)0;
    ans.line = 0;
    ans.column = 0;
  }
  return ans;
}


dg_type find_proc_type
    PROTO_N ( (t) )
    PROTO_T ( dg_type t )
{
  if (t && t->key == DGT_PROC)
    return t;
  if (t && t->key == DGT_TAGGED) {
    dg_tag tg = t->data.t_tag;
    if (tg->key == DGK_TYPE)
      return find_proc_type (tg->p.typ);
    if (tg->key == DGK_NAME) {
      dg_name ref_n = tg->p.nam;
      if (ref_n->key == DGN_TYPE)
	return find_proc_type (ref_n->data.n_typ.raw);
    }
  }
  failer ("proc type details unavailable");
  return f_dg_proc_type (new_dg_param_list (0), f_dg_void_type,
		no_bool_option, no_nat_option, no_nat_option,
		no_procprops_option);
}




static void scan_diag_names
    PROTO_N ( (e, whole) )
    PROTO_T ( exp e X exp whole )
{
  if (name (e) == name_tag) {
    exp id = son(e);
    if (!isdiaginfo (e) && !internal_to (whole, id)) {
      setisdiaginfo (e);
      -- no(id);
    }
    return;
  }
  if (son(e) != nilexp && name (e) != env_offset_tag) {
    exp t = son(e);
    for (;;) {
      scan_diag_names (t, whole);
      if (last(t))
	return;
      t = bro(t);
    }
  }
  return;
}

exp diaginfo_exp
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  /* mark external names to avoid influencing optimisations */
  exp ans;
  if (!e)
    return e;
  scan_diag_names (e, e);
  ans = hold (e);
  setpt (ans, nilexp);
  setbro (ans, nilexp);	/* these fields are used in dwarf generation */
  no(ans) = 0;
  props(ans) = 0;
  clearlast (ans);
  IGNORE check (e, e);
  return ans;
}


#ifdef NEWDIAGS

void diag_kill_id
    PROTO_N ( (id) )
    PROTO_T ( exp id )
{
  exp t = pt(id);
  while (t) {
    if (!isdiaginfo(t))
      failer ("bad kill ident");
    setdiscarded(t);
    t = pt(t);
  }
  son(id) = nilexp;
  return;
}


void set_obj_ref
    PROTO_N ( (nm) )
    PROTO_T ( dg_name nm )
{	/* nm is defining reference for its obtain value */
  exp e = nm->data.n_obj.obtain_val;
  while (e && (name(e) == hold_tag || name(e) == cont_tag || 
	name(e) == reff_tag))
    e = son(e);
  if (e && name(e) == name_tag && isglob(son(e)) && 
	!(brog(son(e))->dec_u.dec_val.diag_info))
    brog(son(e))->dec_u.dec_val.diag_info = nm;
  return;
}

static int matched_obj
    PROTO_N ( (e, nm, refans) )
    PROTO_T ( exp e X dg_name nm X dg_tag * refans )
{				/* e is name_tag for required object */
  exp x;
  if (nm->key != DGN_OBJECT)
    return 0;
  x = nm->data.n_obj.obtain_val;
  while (x && (name(x) == hold_tag || name(x) == cont_tag || 
	name(x) == reff_tag))
    x = son(x);
  if ((x) && name(x) == name_tag && son(x) == son(e)) {
    if ((no(x) <= no(e)) && 
	(no(x) + shape_size(sh(x)) >= no(e) + shape_size(sh(e)) )) {
      if (!nm->mor || !nm->mor->this_tag)
	IGNORE f_dg_tag_name (gen_tg_tag (), nm);
      *refans = nm->mor->this_tag;
      return 1;
    }
  }
  return 0;
}

static int end_ref_search
    PROTO_N ( (e, d, refans) )
    PROTO_T ( exp e X dg_info d X dg_tag * refans )
{
  dg_name pm;
  while (d && d->key != DGA_NAME && d->key != DGA_INL_CALL &&
		d->key != DGA_PARAMS)
    d = d->more;
  if (!d)
    return 0;
  if (d->more && end_ref_search (e, d->more, refans))
    return 1;
  if (d->key == DGA_NAME)
    return (matched_obj (e, d->data.i_nam.dnam, refans));
			/* otherwise inlined call or outermost proc */
  if (d->key == DGA_PARAMS)
    pm = d->data.i_param.args;
  else
    pm = d->data.i_inl.args;
  while (pm && !matched_obj (e, pm, refans))
    pm = pm->next;
  return 1;	/* we don't search the caller environment */
}

static dg_tag find_obj_ref
    PROTO_N ( (contex, e) )
    PROTO_T ( exp contex X exp e )
{				/* e is name_tag for required object */
  dg_tag ans = (dg_tag)0;
  while ((name(contex) != ident_tag || !isglob(contex)) &&
	(!dgf(contex) || !end_ref_search (e, dgf(contex), &ans)))
    contex = father (contex);
  if (!ans) {
    dg_compilation cl = all_comp_units;
    while (cl) {
      dg_name dl = cl->dn_list;
      while (dl) {
	if (matched_obj (e, dl, &ans))
	  return ans;
	dl = dl->next;
      }
      cl = cl->another;
    }
  }
  return ans;
}



static void check_const_exp
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  if (!e)
    return;
  if (name(e) != hold_tag || name(son(e)) != val_tag)
    failer ("diag_type may need copying");
	/* copy within type, unless all name_tags are uncopied */
  return;
}

static void check_const_type
    PROTO_N ( (t) )
    PROTO_T ( dg_type t )
{
  int i;
  switch (t->key) {
    case DGT_QUAL:
      check_const_type (t->data.t_qual.typ);
      break;
    case DGT_CONS:
      check_const_type (t->data.t_cons.typ);
      break;
    case DGT_ARRAY:
      check_const_type (t->data.t_arr.elem_type);
      check_const_exp (t->data.t_arr.stride);
      for (i = 0; i < t->data.t_arr.dims.len; i++) {
	dg_dim * dim = &(t->data.t_arr.dims.array[i]);
	if (dim->d_key != DG_DIM_TYPE) {
	  if (!dim->low_ref)
	    check_const_exp (dim->lower.x);
	  if (!dim->hi_ref)
	    check_const_exp (dim->upper.x);
	}
      }
      break;
    case DGT_SUBR:
      check_const_type (t->data.t_subr.d_typ);
      if (!t->data.t_subr.low_ref)
	check_const_exp (t->data.t_subr.lower.x);
      if (!t->data.t_subr.hi_ref)
        check_const_exp (t->data.t_subr.upper.x);
      break;
    case DGT_STRUCT:
      for (i = 0; i < t->data.t_struct.u.fields.len; i++) {
	dg_classmem * f = &(t->data.t_struct.u.fields.array[i]);
	check_const_type (f->d.cm_f.f_typ);
	check_const_exp (f->d.cm_f.f_offset);
      }
      break;
    case DGT_PROC:
      if (t->data.t_proc.res_type)
	check_const_type (t->data.t_proc.res_type);
      for (i = 0; i < t->data.t_proc.params.len; i++) {
	dg_param * p = &(t->data.t_proc.params.array[i]);
	check_const_type (p->p_typ);
      }
      break;
    case DGT_STRING:
      check_const_exp (t->data.t_string.lb);
      check_const_exp (t->data.t_string.length);
      break;
    case DGT_CLASS:
    case DGT_PMEM:
      failer ("uncopyable type");
      break;
    default:
      break;
  }
  return;
}


static int inner_copy = 0;


static dg_name new_copy_name
    PROTO_N ( (d) )
    PROTO_T ( dg_name d )
{
  dg_name new = new_dg_name(d->key);
  if (d->mor && d->mor->this_tag) {
    IGNORE f_dg_tag_name (gen_tg_tag(), new);
    if (d->mor->this_tag->copy)
      failer ("bad copy_diagname");
    if (inner_copy)
      d->mor->this_tag->copy = new->mor->this_tag;
  }
  if (doing_inlining) {
    if (!d->mor || (!d->mor->this_tag && !d->mor->inline_ref))
      IGNORE f_dg_tag_name (gen_tg_tag(), d);
    if (!d->mor->inline_ref)
      d->mor->inline_ref = d->mor->this_tag;
  }
  new->idnam = d->idnam;
  new->whence = d->whence;
  if (d->mor && (d->mor->inline_ref || d->mor->refspec || d->mor->acc
	|| d->mor->isconst)) {
    extend_dg_name (new);
    new->mor->inline_ref = d->mor->inline_ref;
    new->mor->refspec = d->mor->refspec;
    new->mor->acc = d->mor->acc;
    new->mor->isconst = d->mor->isconst;
  }
  return new;
}

static int is_copied
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  if (!e)
    return 0;
  switch (name(e)) {
    case name_tag:
      return (copying(son(e)));
    case hold_tag:
    case cont_tag:
    case contvol_tag:
    case reff_tag:
    case chvar_tag:
    case chfl_tag:
      return is_copied (son(e));
    case val_tag:
    case null_tag:
    case real_tag:
    case string_tag:
      return 0;
    default:
      failer("unexpected copy_diagname obtain_val");
  }
  return 0;
}


static dg_name copy_diagname
    PROTO_N ( (d, var, lab, need) )
    PROTO_T ( dg_name d X exp var X exp lab X int need )
{
		/* need (new dg_name) if copying a name_list, or if inlining */
  dg_name new = d;
  switch (d->key) {
    case DGN_OBJECT: {
      int moved = is_copied (d->data.n_obj.obtain_val);
      check_const_type (d->data.n_obj.typ);
      if (need || moved) {
	new = new_copy_name (d);
	new->data.n_obj = d->data.n_obj;
#if 0
	if (moved)
#endif
	  new->data.n_obj.obtain_val = 
		copy_res (d->data.n_obj.obtain_val, var, lab);
      }
      break;
    }
    case DGN_TYPE: {
      check_const_type (d->data.n_typ.raw);
      break;
    }
    case DGN_IMPORT: {
      if (d->data.n_imp.i_typ)
	check_const_type (d->data.n_imp.i_typ);
      break;
    }
    default:
      failer ("unexpected copy_diagname");
  };
  return new;
}

static void update_detch_copy PROTO_S ((detch_info * dl, int update));

static void update_diag_copy
    PROTO_N ( (e, d, update) )
    PROTO_T ( exp e X dg_info d X int update )
{
  if (d) {
    if (update) {	/* use all dg_tag copies */
      switch (d->key) {
	case DGA_INL_RES: {
	  dg_tag ic = d->data.i_res.call;
	  if (ic->copy)
	    d->data.i_res.call = ic->copy;
	  break;
	}
	case DGA_BEG: {
	  dg_tag tg = d->data.i_tg;
	  if (tg->copy)
	    d->data.i_tg = tg->copy;
	  break;
	}
	case DGA_RVS: {
	  dg_tag tg = d->data.i_rvs.u.tg;
	  if (tg && tg->copy)
	    d->data.i_rvs.u.tg = tg->copy;
	  break;
	}
	case DGA_DETCH: {
	  update_detch_copy (d->data.i_detch.dl, 1);
	  break;
	}
	case DGA_MOVD:
	case DGA_HOIST: {
	  dg_tag tg = d->data.i_movd.tg;
	  if (tg && tg->copy)
	    d->data.i_movd.tg = tg->copy;
#if 1
	  if (d->key == DGA_MOVD && !d->more)
	    failer ("lost movd?");
#endif
	  break;
	}
	default:
	  break;
      }
    }
    else {		/* remove all dg_tag copies */
      if (d->this_tag && (doing_inlining || clean_copy))
	d->this_tag->copy = (dg_tag)0;
		/* otherwise keep record for code movement */
      switch (d->key) {
	case DGA_NAME: {
	  dg_name a = d->data.i_nam.dnam;
	  if (a->mor && a->mor->this_tag)
	    a->mor->this_tag->copy = (dg_tag)0;
	  break;
	}
	case DGA_INL_CALL: {
	  dg_name a = d->data.i_inl.args;
	  while (a) {
	    if (a->mor && a->mor->this_tag)
	      a->mor->this_tag->copy = (dg_tag)0;
	    a = a->next;
	  }
	  break;
	}
	case DGA_X_CATCH: {
	  dg_name a = d->data.i_catch.ex;
	  if (a->mor && a->mor->this_tag)
	    a->mor->this_tag->copy = (dg_tag)0;
	  break;
	}
	case DGA_DETCH: {
	  if (doing_inlining || clean_copy)
	    update_detch_copy (d->data.i_detch.dl, 0);
	  break;
	}
#if 1
	case DGA_MOVD: {
	  if (!d->more)
	    failer ("lost movd?");
	  break;
	}
#endif
	default:
	  break;
      }
    }
    update_diag_copy (e, d->more, update);
  }
  else
  if (e) {
    switch (name(e)) {
      case name_tag:
      case env_offset_tag:
      case general_env_offset_tag:
	break;
      default: {
	exp s = son(e);
	while (s) {
	  update_diag_copy (s, dgf(s), update);
	  if (last(s))
	    break;
	  s = bro(s);
	}
      }
    }
  }
  return;
}

static void update_detch_copy
    PROTO_N ( (dl, update) )
    PROTO_T ( detch_info * dl X int update )
{
  while (dl) {
    if (dl->info)
      update_diag_copy (nilexp, dl->info, update);
    if (update && dl->tg && dl->tg->copy)
      dl->tg = dl->tg->copy;
    if (dl->sub)
      update_detch_copy (dl->sub, update);
    dl = dl->next;
  }
  return;
}


static detch_info * copy_detch_tree PROTO_S ((detch_info * dl));

static dg_info copy_dg_info
    PROTO_N ( (d, var, lab, doing_exp_copy) )
    PROTO_T ( dg_info d X exp var X exp lab X int doing_exp_copy )
{
  dg_info new = new_dg_info(d->key);
  if (d->this_tag) {
    IGNORE f_make_tag_dg (gen_tg_tag(), new);
    if (d->this_tag->copy)
      failer ("bad copy_dg_info");
    if (inner_copy)
      d->this_tag->copy = new->this_tag;
  }
  switch (new->key) {
    case DGA_PARAMS: {
      new->data.i_param = d->data.i_param;
      break;
    }
    case DGA_COMP: {
      new->data.i_comp = d->data.i_comp;
      break;
    }
    case DGA_SRC: {
      new->data.i_src = d->data.i_src;
      break;
    }
    case DGA_LAB:
    case DGA_EXTRA:
    case DGA_SCOPE: {
      new->data.i_scope = d->data.i_scope;
      break;
    }
    case DGA_NAME: {
      new->data.i_nam = d->data.i_nam;
      if (doing_exp_copy)	/* a named item might be copied */
	new->data.i_nam.dnam = 
		copy_diagname (d->data.i_nam.dnam, var, lab, doing_inlining);
      break;
    }
    case DGA_WITH: {
      new->data.i_with = d->data.i_with;
      check_const_type (d->data.i_with.w_typ);
      if (doing_exp_copy)
	new->data.i_with.w_exp = copy_res (d->data.i_with.w_exp, var, lab);
      break;
    }
    case DGA_CALL: {
      new->data.i_call = d->data.i_call;
      break;
    }
    case DGA_INL_CALL: {
      dg_name a = d->data.i_inl.args;
      dg_name * b = &(new->data.i_inl.args);
      new->data.i_inl = d->data.i_inl;
      if (doing_exp_copy) {
	while (a) {
	  *b = copy_diagname (a, var, lab, 1);
	  a = a->next;
	  b = &((*b)->next);
	}
      }
      d->data.i_inl.proc->any_inl = 1;
      break;
    }
    case DGA_INL_RES: {
      new->data.i_res = d->data.i_res;
      new->data.i_res.call = d->data.i_res.call;
      break;
    }
    case DGA_X_TRY: {
      new->data.i_try = d->data.i_try;
      break;
    }
    case DGA_X_CATCH: {
      new->data.i_catch = d->data.i_catch;
      if (doing_exp_copy)
	new->data.i_catch.ex = 
		copy_diagname (d->data.i_catch.ex, var, lab, doing_inlining);
      break;
    }
    case DGA_X_RAISE: {
      new->data.i_raise = d->data.i_raise;
      if (d->data.i_raise.x_typ)
	check_const_type (d->data.i_raise.x_typ);
      if (d->data.i_raise.x_val && doing_exp_copy)
	new->data.i_raise.x_val = copy_res (d->data.i_raise.x_val, var, lab);
      break;
    }
    case DGA_BRANCH: {
      new->data.i_brn = d->data.i_brn;
      break;
    }
    case DGA_TEST:
    case DGA_JUMP: {
      new->data.i_tst = d->data.i_tst;
      break;
    }
    case DGA_LJ: {
      new->data.i_lj = d->data.i_lj;
      break;
    }
    case DGA_BEG: {
      new->data.i_tg = d->data.i_tg;
      break;
    }
    case DGA_DEST: {
      new->data.i_dest = d->data.i_dest;
      break;
    }
    case DGA_RVS: {
      new->data.i_rvs = d->data.i_rvs;
      break;
    }
    case DGA_BAR: {
      new->data.i_bar = d->data.i_bar;
      break;
    }
    case DGA_DETCH: {
      new->data.i_detch = d->data.i_detch;
      if (doing_exp_copy)
	new->data.i_detch.dl = copy_detch_tree (new->data.i_detch.dl);
      break;
    }
    case DGA_MOVD:
    case DGA_HOIST: {
      new->data.i_movd = d->data.i_movd;
#if 1
      if (d->key == DGA_MOVD && !d->more)
	failer ("lost movd?");
#endif
      break;
    }
    case DGA_OPTIM: {
      new->data.i_optim = d->data.i_optim;
      break;
    }
    case DGA_REMVAL: {
      new->data.i_remval = d->data.i_remval;
      if (copying(son(son(d->data.i_remval.var))))
	new->data.i_remval.var = copy (d->data.i_remval.var);
      break;
    }
    default:
      failer ("copy_diaginfo incomplete");
  };
  return new;
}

static detch_info * copy_detch_tree
    PROTO_N ( (dl) )
    PROTO_T ( detch_info * dl )
{
  detch_info * ans = (detch_info *) xcalloc (1, sizeof (detch_info));
  *ans = *dl;
  if (dl->info)
    ans->info = copy_dg_info (dl->info, nilexp, nilexp, 1);
  if (dl->sub)
    ans->sub = copy_detch_tree (dl->sub);
  if (dl->next)
    ans->next = copy_detch_tree (dl->next);
  return ans;
}


exp copy_res_diag
    PROTO_N ( (e, d, var, lab) )
    PROTO_T ( exp e X dg_info d X exp var X exp lab )
{
  int ic = inner_copy;
  dg_info new;
  exp ans;
  if (!d /* || 
	(name(e) == name_tag && isdiaginfo(e) && !doing_inlining && !clean-copy) */
		/* only one defining name tag */
     ) {
    dg_info all = dgf(e);
    dgf(e) = nildiag;
    ans = copy_res (e, var, lab);
    dgf(e) = all;
    dgf(ans) = combine_diaginfo (dgf(ans), d);
    return ans;
  }
  if (d->key == DGA_PARAMS)
    return copy_res_diag (e, d->more, var, lab);
  inner_copy = 1;
  new = copy_dg_info (d, var, lab, 1);
  ans = copy_res_diag (e, d->more, var, lab);

  new->more = dgf(ans);
  dgf(ans) = new;
  if (!ic) {
    inner_copy = 0;
    update_diag_copy (ans, dgf(ans), 1);
    update_diag_copy (e, dgf(e), 0);
  }
  return ans;
}

exp diag_hold_check	/* called by copy_res when inlining */
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  int was_inlining = doing_inlining;
  exp hc;
  doing_inlining = 0;
  hc = hold_check (e);
  doing_inlining = was_inlining;
  return hc;
}


static dg_tag current_inliner = (dg_tag)0;

static int ref_param
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  switch (name(e)) {
    case name_tag:
    case cont_tag:
    case chvar_tag:
    case chfl_tag:
      return ref_param (son(e));
    case ident_tag:
      if (isparam(e))
	return 1;
      if (dgf(e) || isglob(e))
	return 0;
      return ref_param (son(e));
    default:
      return 0;
  }
}

void start_diag_inlining
    PROTO_N ( (e, dn) )
    PROTO_T ( exp e X dg_name dn )
{
  exp body = son(e);
  dg_info di;
  int any_inl;
  dg_name_list args = (dg_name)0;
  if (!dn || dn->key != DGN_PROC)
    return;
  while (name(body) == ident_tag && (isparam(body) ||
		(!dgf(body) && ref_param (son(body)) )))
    body = bro(son(body));
  di = dgf(body);
  if (di && di->key == DGA_PARAMS) {
    dn->data.n_proc.params = di;
    args = di->data.i_param.args;
  }
  if (!dn->mor || !dn->mor->this_tag)
    IGNORE f_dg_tag_name (gen_tg_tag(), dn);
  any_inl = dn->mor->this_tag->any_inl;
  di = f_inline_call_dg (			/* for copying only */
		dn->mor->this_tag,
		args,
		no_nat_option);
  dn->mor->this_tag->any_inl = any_inl;
  current_inliner = gen_tg_tag();
  di = f_make_tag_dg (current_inliner, di);
  di->more = dgf(body);
  dgf(body) = di;
  return;
}

void end_diag_inlining
    PROTO_N ( (e, dn) )
    PROTO_T ( exp e X dg_name dn )
{
  exp body;
  if (!dn || dn->key != DGN_PROC)
    return;
  body = son(e);
  while (name(body) == ident_tag && (isparam(body) ||
		(!dgf(body) && ref_param (son(body)) )))
    body = bro(son(body));
  dgf(body) = dgf(body)->more;
  current_inliner = 0;
  return;
}

dg_info combine_diaginfo
    PROTO_N ( (d1, d2) )
    PROTO_T ( dg_info d1 X dg_info d2 )
{
  dg_info d;
  if (!d1)
    return d2;
  if (!d2)
    return d1;
  d = copy_dg_info (d1, nilexp, nilexp, 0);
  d->more = combine_diaginfo (d1->more, d2);
  return d;
}

void diag_inline_result
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  if (current_inliner)
    dgf(e) = f_inline_result_dg (current_inliner);
  return;
}


void dg_whole_comp
    PROTO_N ( (whole, comp) )
    PROTO_T ( exp whole X exp comp )
{
		/* for use before replace (whole, comp, x) when
		   whole is replaced by its only remaining component */
  if (dgf(whole)) {
    dg_info * next = &(dgf(whole)->more);
    while (*next)
      next = &((*next)->more);
    *next = dgf(comp);
    dgf(comp) = dgf(whole);
  }
  return;
}


void dg_complete_inline
    PROTO_N ( (whole , comp) )
    PROTO_T ( exp whole X exp comp )
{
		/* as dg_whole_comp, but remove DGA_CALL */
  if (dgf(whole)) {
    int rem = 0;
    dg_info * next = &(dgf(whole)->more);
    while (*next) {
      if ((*next)->key == DGA_CALL) {
	*next = (*next)->more;
	rem = 1;
      }
      else
        next = &((*next)->more);
    }
    if (rem) {
		/* we must find DGA_INL_CALL to replace the DGA_CALL */
      while (!dgf(comp)) {
        if (name(comp) == ident_tag)
	  comp = bro(son(comp));
	else
	if (name(comp) == cond_tag)
	  comp = son(comp);
	else
	  break;
      }
      if (!dgf(comp) || dgf(comp)->key != DGA_INL_CALL)
	failer ("lost inline call movement");
    }
    *next = dgf(comp);
    dgf(comp) = dgf(whole);
  }
  return;
}


static detch_info * gather_detch
    PROTO_N ( (e, dx, reason, descend, reuse, opt_ref) )
    PROTO_T ( exp e X dg_info * dx X int reason X int descend X int reuse
			X dg_tag opt_ref )
{
			/* e is exp under consideration.
			   dx is (ref) dg_info under consideration
				part of dgf(e); this info being removed.
			   reason is enumerated reason for debugger.
			   descend is nonzero if son(e) to be processed.
			   reuse is nonzero if simple movement (e remains in use).
			   opt_ref for reference to complex optimisation info.
			*/
  dg_info d = *dx;
  detch_info * ans;
  exp s;
  if (d) {
    if (d->key == DGA_DETCH) {		/* previous detachment */
      detch_info * more = gather_detch (e, &(d->more), reason, descend, 
				reuse, opt_ref);
      detch_info ** ptr;
      if (d->data.i_detch.posn < 0) {
	ans = d->data.i_detch.dl;
      }
      else {
	ans = more;
	more = d->data.i_detch.dl;
      }
      ptr = &ans;
      while (*ptr)
	ptr = &((*ptr)->next);
      *ptr = more;
      return ans;
    }
    if (d->key == DGA_MOVD) {		/* previous simple movement */
      if (!d->more)
	failer ("lost movd?");
      if (reason < d->data.i_movd.reason) {
        d->data.i_movd.reason = reason;
	d->data.i_movd.tg = opt_ref;
      }
      if (reuse)
	return (detch_info *)0;
      d->data.i_movd.lost = 1;
      if (d->more->key == DGA_INL_CALL) {	/* ignore internals */
	*dx = (dg_info)0;
	return (detch_info *)0;
      }
      *dx = d->more->more;
      return gather_detch (e, dx, reason, descend, reuse, opt_ref);
    }
    ans = (detch_info *) xcalloc (1, sizeof (detch_info));
    ans->next = (detch_info *)0;
    if (d->key == DGA_INL_CALL)
      ans->sub = (detch_info *)0;
    else
      ans->sub = gather_detch (e, &(d->more), reason, descend, reuse, opt_ref);
    ans->why = reason;
    if (reuse) {
      d = new_dg_info (DGA_MOVD);
      d->data.i_movd.reason = reason;
      d->data.i_movd.lost = 0;
      d->data.i_movd.tg = opt_ref;
      d->data.i_movd.lo_pc = 0;
      d->more = *dx;
      *dx = d;
      if (!d->more)
	failer ("lost movd?");
      IGNORE f_make_tag_dg (gen_tg_tag(), d);
      ans->info = (dg_info)0;
      ans->tg = d->this_tag;
    }
    else {		/* original about to be discarded */
      ans->info = d;
      d->more = (dg_info)0;
      ans->tg = opt_ref;
    }
    return ans;
  }
  if (extra_diags && reuse &&
	(name(e) == apply_tag || name(e) == apply_general_tag)) {
	/* need info to modify in case of subsequent inlining */
    dg_info x = dgf(e);
    while (x && x->key != DGA_CALL)
      x = x->more;
    if (!x) {
      *dx = d = new_dg_info (DGA_CALL);
      d->data.i_call.clnam = (char*)0;
      d->data.i_call.pos = no_short_sourcepos;
      d->data.i_call.ck = 0;
      return gather_detch (e, dx, reason, descend, reuse, opt_ref);
    }
  }
  if (!descend)
    return (detch_info *)0;
  s = son(e);
  if (name(e) == name_tag || name(e) == env_size_tag ||
	name(e) == env_offset_tag || !s)
    return (detch_info *)0;
  ans = gather_detch (s, &(dgf(s)), reason, descend, reuse, opt_ref);
  if (name(e) != case_tag) {
    detch_info ** ptr = &ans;
    while (!last(s)) {
      s = bro(s);
      while (*ptr)
	ptr = &((*ptr)->next);
      *ptr = gather_detch (s, &(dgf(s)), reason, descend, reuse, opt_ref);
    }
  }
  return ans;
}


static void dg_detach
    PROTO_N ( (old, keep, position, reason, descend, reuse, opt_ref) )
    PROTO_T ( exp old X exp keep X int position X int reason X int descend
			X int reuse X dg_tag opt_ref )
{
  detch_info * info = 
		gather_detch (old, &(dgf(old)), reason, descend, reuse, opt_ref);
  if (info) {
    dg_info newd = new_dg_info (DGA_DETCH);
    newd->data.i_detch.posn = position;
    newd->data.i_detch.dl = info;
    newd->more = dgf(keep);
    dgf(keep) = newd;
  }
  return;
}

void dg_dead_code
    PROTO_N ( (dead, prev) )
    PROTO_T ( exp dead X exp prev )
{			/* mark removal of dead code following prev */
  dg_detach (dead, prev, +1, DGD_DEAD, 1, 0, (dg_tag)0);
  return;
}

void dg_rdnd_code
    PROTO_N ( (rdnd, next) )
    PROTO_T ( exp rdnd X exp next )
{			/* mark removal of redundant code before next */
  dg_detach (rdnd, next, -1, DGD_RDND, 1, 0, (dg_tag)0);
  return;
}

void dg_detach_const
    PROTO_N ( (part, whole) )
    PROTO_T ( exp part X exp whole )
{			/* incorporated part in whole evaluated constant*/
  dg_detach (part, whole, 0, DGD_CNST, 0, 0, (dg_tag)0);
  return;
}

void dg_restruct_code
    PROTO_N ( (outer, inner, posn) )
    PROTO_T ( exp outer X exp inner X int posn )
{			/* mark movement of inner into outer */
  dg_detach (inner, outer, posn, DGD_MOVD, 1, 1, (dg_tag)0);
  return;
}

void dg_rem_ass
    PROTO_N ( (ass) )
    PROTO_T ( exp ass )
{			/* mark removal of propagated assignment */
  exp val = bro(son(ass));
  if (name(son(ass)) == name_tag && (name(val) == val_tag || 
			name(val) == real_tag || name (val) == null_tag)) {
    dg_info h = dgf(val);
    dg_info * dx = &(dgf(ass));
    dg_info rem = new_dg_info (DGA_REMVAL);
    rem->data.i_remval.var = hold(me_obtain (son(son(ass))));
    setisdiaginfo (son(rem->data.i_remval.var));
    -- no(son(son(rem->data.i_remval.var)));
    dgf(val) = nildiag;
    rem->data.i_remval.val = copy(val);
    dgf(val) = h;
    rem->data.i_remval.lo_pc = (long)0;
    rem->more = nildiag;
    while (*dx)
      dx = &((*dx)->more);
    *dx = rem;
  }
  dg_detach (ass, bro(son(ass)), -1, DGD_REM, 0, 0, (dg_tag)0);
  return;
}

void strip_dg_context
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  dg_info d = dgf(e);
  while (d && (d->key == DGA_DETCH || d->key == DGA_NAME))
    d = d->more;
  dgf(e) = d;
  return;
}

static dg_info * after_dg_context
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  dg_info * dx = &(dgf(e));
  while (*dx && ((*dx)->key == DGA_DETCH || (*dx)->key == DGA_NAME))
    dx = &((*dx)->more);
  return dx;
}

void dg_extracted
    PROTO_N ( (nm, old) )
    PROTO_T ( exp nm X exp old )
{			/* old replaced by nm */
  dg_info con_start = dgf(old);
  dg_info con_end = (strip_dg_context(old), dgf(old));
  dg_info * dx;
  if (name(nm) != name_tag || (dx = after_dg_context (son(nm)), !(*dx)->this_tag))
    failer ("make_optim error");
  dg_detach (old, nm, -1, DGD_EXTRACT, 1, 0, (*dx)->this_tag);
  if (con_start != con_end) {
    dg_info d = con_start;
    while (d->more != con_end)
      d = d->more;
    d->more = dgf(nm);
    dgf(nm) = con_start;
  }
  return;
}


static void gather_objects
    PROTO_N ( (e, whole, obs, ass) )
    PROTO_T ( exp e X exp whole X objset ** obs X int ass )
{
		/* gather into obs, all objects accessed within e that are 
		   external to whole, distinguishing those that may be altered */
  exp t;
  switch (name(e)) {
    case name_tag: {
      if (!intnl_to (whole, son(e))) {
	dg_tag tg = find_obj_ref (whole, e);
	if (tg) {
	  objset * x = *obs;
	  while (x && x->tg != tg)
	    x = x->next;
	  if (!x) {
	    x = (objset *) xcalloc (1, sizeof (objset));
	    x->tg = tg;
	    x->ass = ass;
	    x->next = *obs;
	    *obs = x;
	  }
	  else
	  if (ass)
	    x->ass = 1;
	}
      }
      return;
    }
    case ident_tag: {
      gather_objects (bro(son(e)), whole, obs, ass);
      break;	/* definition part no_ass */
    }
    case seq_tag: {
      gather_objects (bro(son(e)), whole, obs, ass);
      e = son(e);
      break;	/* statements no_ass */
    }
    case cond_tag: {
      gather_objects (son(e), whole, obs, ass);
      gather_objects (bro(son(e)), whole, obs, ass);
      return;
    }
    case labst_tag: {
      gather_objects (bro(son(e)), whole, obs, ass);
      return;
    }
    case rep_tag: {
      gather_objects (son(e), whole, obs, 0);
      gather_objects (bro(son(e)), whole, obs, ass);
      return;
    }
    case solve_tag: {
      t = son(e);
      for (;;) {
	gather_objects (t, whole, obs, ass);
	if (last(t))
	  return;
	t = bro(t);
      }
    }
    case ass_tag:
    case assvol_tag: {
      gather_objects (son(e), whole, obs, 1);
      gather_objects (bro(son(e)), whole, obs, 0);
      return;
    }
    case addptr_tag: {
      gather_objects (son(e), whole, obs, ass);
      gather_objects (bro(son(e)), whole, obs, 0);
      return;
    }
    case env_offset_tag: {
      return;
    }
    default:
      break;
  }
  t = son(e);		/* remaining cases all no_ass */
  while (t) {
    gather_objects (t, whole, obs, 0);
    if (last(t))
      return;
    t = bro(t);
  }
  return;
}


void make_optim_dg
    PROTO_N ( (reason, e) )
    PROTO_T ( int reason X exp e )
{
  dg_info sub = new_dg_info (DGA_HOIST);
  exp konst = son(e);
  exp body = bro(konst);
  dg_info * dx;
  dgf(e) = dgf(body);
  dgf(body) = nildiag;
  dx = after_dg_context (e);
  if (!*dx || (*dx)->key != DGA_OPTIM || (*dx)->data.i_optim.reason != reason) {
    dg_info ans = new_dg_info (DGA_OPTIM);
    ans->data.i_optim.reason = reason;
    ans->data.i_optim.objs = (objset *)0;
    ans->data.i_optim.lo_pc = ans->data.i_optim.hi_pc = 0;
    IGNORE f_make_tag_dg (gen_tg_tag(), ans);
    ans->more = *dx;
    *dx = ans;
  }
  sub->data.i_movd.reason = reason;
  sub->data.i_movd.lost = 0;
  sub->data.i_movd.tg = (*dx)->this_tag;
  sub->data.i_movd.lo_pc = sub->data.i_movd.hi_pc = 0;
  sub->more = dgf(konst);
  dgf(konst) = sub;
  gather_objects (konst, konst, &((*dx)->data.i_optim.objs), 0);
  return;
}

exp copy_dg_separate
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{			/* Used instead of copy if the original may 
			   still be in use. This resets tracing of 
			   dg_tag copies */
  exp ans;
  clean_copy = 1;
  ans = copy(e);
  clean_copy = 0;
  return ans;
}

#endif


exp relative_exp
    PROTO_N ( (s, t) )
    PROTO_T ( shape s X token t )
{
  exp id = me_startid (s, f_make_value (s), 0);
  tokval tv;
  tv.tk_exp = me_obtain (id);
  tv = apply_tok(t, keep_place(), EXP_S, &tv);
  IGNORE me_complete_id (id, hold_check (tv.tk_exp));
  return hold(id);
}
