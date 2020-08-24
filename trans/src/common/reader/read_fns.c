/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* this file contains the definitions of some of the functions
   called from decoder.c to set up the in-store representations of TDF.
   It defines those functions which are independent of the actual
   representation, particularly the token substitution and
   unit handling
*/

#include <string.h>
#include <stdio.h>
#include <string.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/string.h>
#include <shared/xalloc.h>

#include <tdf/nat.h>
#include <tdf/shape.h>
#include <tdf/sort.h>
#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/basicread.h>
#include <reader/token.h>
#include <reader/main_reads.h>
#include <reader/readglob.h>
#include <reader/table_fns.h>
#include <reader/reader.h>
#include <reader/externs.h>

#include <construct/exp.h>
#include <construct/me_fns.h>
#include <construct/installglob.h>
#include <construct/machine.h>
#include <construct/aldefs.h>

#include <utility/prefix.h>

#include <main/flags.h>

#ifdef TDF_DIAG3
#include <diag3/diag_fns.h>
#include <diag3/dg_fns.h>
#endif
#ifdef TDF_DIAG4
#include <diag4/diag_fns.h>
#include <diag4/dg_fns.h>
#endif


/* Some external declarations  */

extern diag_type_unit f_make_diagtype_unit(void);	/* TDF_DIAG3 */
extern int f_make_linkinfo_unit(void);
extern void start_make_linkinfo_unit(int, int, int, int);
extern int machine_toks(char *);
extern void tidy_initial_values(void);

/* MACROS */

    /* codes for the types of unit which are understood here */
#define UNKNOWN_UNIT	 0
#define TOKDEC_UNIT	 1
#define TOKDEF_UNIT	 2
#define AL_UNIT		 3
#define TAGDEC_UNIT	 4
#define TAGDEF_UNIT	 5
#define DIAGDEF_UNIT	 6	/* TDF_DIAG3 */
#define DIAGTYPE_UNIT	 7	/* TDF_DIAG3 */
#define LINKINFO_UNIT	 8
#define VERSIONS_UNIT	 9
#define DGCOMP_UNIT	10	/* TDF_DIAG4 */

  /* codes for the kinds of linkable variable which are understood here */
#define UNKNOWN_TYPE	0
#define TOK_TYPE	1
#define TAG_TYPE	2
#define AL_TYPE		3
#define DIAGTAG_TYPE	4	/* TDF_DIAG3 */
#define DGTAG_TYPE	5	/* TDF_DIAG4 */

/* VARIABLES */
/* All variables are initialised, jmf */

int crt_group_type;		/* the code for the current group of units */
static int crt_links_type;        /* the code for the current type of linkable variable */
static int crt_extern_link_type;	/* the code for the current type of externally linked variable */
static tdfstring *crt_capsule_groups;	/* the identifier for the current group of units */
static int crt_capsule_group_no;	/* the number in the group */
static int crt_capsule_link_no;	/* the number of linkable variables of the current type */
static capsule_link_list crt_capsule_linking;

static int no_of_local_tokens;



/* PROCEDURES */

/*
 * This is a workaround for shared/xcalloc asserting count is non-zero, but the
 * code here relying on being able to do that. I believe it's just this code
 * which wants to calloc zero sizes (and expects a NULL), so I'm keeping this
 * here, rather than also permitting that elsewhere. However, I think most of
 * these instances probably oughn't to use calloc at all.
 */
static void *
rf_xcalloc(size_t count, size_t size)
{
	if (count == 0) {
		return NULL;
	}

	return xcalloc(count, size);
}

  /* translates the name of a group of units into  its code */
static int
group_type(char *s)
{
  if (streq(s, "tokdec")) {
    return TOKDEC_UNIT;
  }
  if (streq(s, "tokdef")) {
    return TOKDEF_UNIT;
  }
  if (streq(s, "aldef")) {
    return AL_UNIT;
  }
  if (streq(s, "tagdec")) {
    return TAGDEC_UNIT;
  }
  if (streq(s, "tagdef")) {
    return TAGDEF_UNIT;
  }
  if (streq(s, "diagdef")) {		/* TDF_DIAG3 */
    return DIAGDEF_UNIT;
  }
  if (streq(s, "diagtype")) {		/* TDF_DIAG3 */
    return DIAGTYPE_UNIT;
  }
  if (streq(s, "linkinfo")) {
    return LINKINFO_UNIT;
  }
  if (streq(s, "versions")) {
    return VERSIONS_UNIT;
  }
  if (streq(s, "dgcompunit")) {	/* TDF_DIAG4 */
    return DGCOMP_UNIT;
  }
  return UNKNOWN_UNIT;
}

/* translates the name of a kind of linkable variable into its code */
static int
links_type(char *s)
{
  if (streq(s, "token")) {
    return TOK_TYPE;
  }
  if (streq(s, "tag")) {
    return TAG_TYPE;
  }
  if (streq(s, "alignment")) {
    return AL_TYPE;
  }
  if (streq(s, "diagtag")) {		/* TDF_DIAG3 */
    return DIAGTAG_TYPE;
  }
  if (streq(s, "dgtag")) {		/* TDF_DIAG4 */
    return DGTAG_TYPE;
  }
  return UNKNOWN_TYPE;
}

char *
external_to_string(external ext)
{
	char *res;
	int n, i, l;
	tdfstring *t;
	if (ext.isstring) {
		return (char *)ext.ex.id.ints.chars;
	}
	else {
		n = ext.ex.u.number;
		t = ext.ex.u.elems;
		l=n;
		for (i = 0; i < n; i++) {
			l += t[i].number *(t[i].size / 8);
		}
		res = xcalloc(l + 1, sizeof(char));
		l = 0;
		for (i = 0; i < n; i++) {
			IGNORE(strcpy(res + l, t[i].ints.chars));
			l += t[i].number * (t[i].size / 8);
			res[l++] = 'U';
		}
		return res;
	}
}

/*
 * Invent a local label identifier.
 */
char *
make_local_name(void)
{
	char *s = intchars(next_lab());
	return add_prefix(local_prefix, s);
}

static void
check_tok_sig(tok_define *t, string sig)
{
	char *sid = sig.ints.chars;
	int s = (sig.size * sig.number) / 8;
	if (t->signature != NULL) {
		char *id = t->signature;
		int i;
		for (i = 0; i < s; i++) {
			if (id[i] != sid[i])break;
		}
		if (i !=s || id[s] != 0) {
			error(ERR_INTERNAL, "Token signatures should be equal: %s != %s", id, sid);
		}
	} else {
		t->signature = sid;
	}
}

/* all the _apply_token functions follow this pattern */
procprops
f_procprops_apply_token(token token_value, bitstream token_args)
{
   tokval v;
   v = apply_tok(token_value, token_args, SORT_PROCPROPS, NULL);
   return v.tk_procprops;
}

/* all the _cond functions follow this pattern */
procprops
f_procprops_cond(exp control, bitstream e1, bitstream e2)
{
  bitstream bs;
  procprops res;
  int n;
  bs = keep_place();

  /* the control must evaluate to a constant */
  if (control->tag != val_tag) {
    error(ERR_INTERNAL, "illegal control expression");
  }
  n = no(control);
  retcell(control);
  if (n == 0) {
     /* use the second bitstream */
     set_place(e2);
     res = d_procprops();
  } else {
     /* use the first bitstream */
     set_place(e1);
     res = d_procprops();
  }
 set_place(bs);
 return res;
}

string
f_string_apply_token(token token_value, bitstream token_args)
{
   tokval v;
   v = apply_tok(token_value, token_args, SORT_STRING, NULL);
   return v.tk_string;
}

/* all the _cond functions follow this pattern */
string
f_string_cond(exp control, bitstream e1, bitstream e2)
{
  bitstream bs;
  string res;
  int n;
  bs = keep_place();

  /* the control must evaluate to a constant */
  if (control->tag != val_tag) {
    error(ERR_INTERNAL, "illegal control expression");
  }
  n = no(control);
  retcell(control);
  if (n == 0) {
    /* use the second bitstream */
    set_place(e2);
    res = d_string();
  } else {
    /* use the first bitstream */
    set_place(e1);
    res = d_string();
  }
  set_place(bs);
  return res;
}


alignment
f_alignment_apply_token(token token_value, bitstream token_args)
{
  tokval v;
  v = apply_tok(token_value, token_args, SORT_ALIGNMENT, NULL);
  return v.tk_alignment;
}

/* all the _cond functions follow this pattern */
alignment
f_alignment_cond(exp control, bitstream e1, bitstream e2)
{
  bitstream bs;
  alignment res;
  int n;
  bs = keep_place();

  /* the control must evaluate to a constant */
  if (control->tag != val_tag) {
    error(ERR_INTERNAL, "illegal control expression");
  }
  n = no(control);
  retcell(control);
  if (n == 0) {
    /* use the second bitstream */
    set_place(e2);
    res = d_alignment();
  } else {
    /* use the first bitstream */
    set_place(e1);
    res = d_alignment();
  }
  set_place(bs);
  return res;
}

access
f_access_apply_token(token token_value, bitstream token_args)
{
  tokval v;
  v = apply_tok(token_value, token_args, SORT_ACCESS, NULL);
  return v.tk_access;
}


access
f_access_cond(exp control, bitstream e1, bitstream e2)
{
  bitstream bs;
  access res;
  int n;
  bs = keep_place();

  /* the control must evaluate to a constant */
  if (control->tag != val_tag) {
    error(ERR_INTERNAL, "illegal control expression");
  }
  n = no(control);
  retcell(control);
  if (n == 0) {
    /* use the second bitstream */
    set_place(e2);
    res = d_access();
  } else {
    /* use the first bitstream */
    set_place(e1);
    res = d_access();
  }
  set_place(bs);
  return res;
}

transfer_mode
f_transfer_mode_apply_token(token token_value, bitstream token_args)
{
   tokval v;
   v = apply_tok(token_value, token_args, SORT_TRANSFER_MODE, NULL);
   return v.tk_transfer_mode;
}


transfer_mode
f_transfer_mode_cond(exp control, bitstream e1, bitstream e2)
{
  bitstream bs;
  transfer_mode res;
  int n;
  bs = keep_place();

  /* the control must evaluate to a constant */
  if (control->tag != val_tag) {
    error(ERR_INTERNAL, "illegal control expression");
  }
  n = no(control);
  retcell(control);
  if (n == 0) {
    /* use the second bitstream */
    set_place(e2);
    res = d_transfer_mode();
  } else {
    /* use the first bitstream */
    set_place(e1);
    res = d_transfer_mode();
  }
  set_place(bs);
  return res;
}


bitfield_variety
f_bfvar_apply_token(token token_value, bitstream token_args)
{
   tokval v;
   v = apply_tok(token_value, token_args, SORT_BITFIELD_VARIETY, NULL);
   return v.tk_bitfield_variety;
}

bitfield_variety
f_bfvar_cond(exp control, bitstream e1, bitstream e2)
{
  bitstream bs;
  bitfield_variety res;
  int n;
  bs = keep_place();
  if (control->tag != val_tag) {
    error(ERR_INTERNAL, "illegal control expression");
  }
  n = no(control);
  retcell(control);
  if (n == 0) {
    set_place(e2);
    res = d_bitfield_variety();
  } else {
    set_place(e1);
    res = d_bitfield_variety();
  }
  set_place(bs);
  return res;
}

bool
f_bool_apply_token
(token token_value, bitstream token_args)
{
   tokval v;
   v = apply_tok(token_value, token_args, SORT_BOOL, NULL);
   return v.tk_bool;
}

bool
f_bool_cond(exp control, bitstream e1, bitstream e2)
{
  bitstream bs;
  bool res;
  int n;
  bs = keep_place();
  if (control->tag != val_tag) {
    error(ERR_INTERNAL, "illegal control expression");
  }
  n = no(control);
  retcell(control);
  if (n == 0) {
    set_place(e2);
    res = d_bool();
  } else {
    set_place(e1);
    res = d_bool();
  }
  set_place(bs);
  return res;
}


/* locate the index number of the linkable variable */
static int
find_index(char *nm)
{
  int i;
  for (i = 0; i < crt_capsule_linking.number; ++i) {
    if (streq((crt_capsule_linking.members[i]).id, nm)) {
      return i;
    }
  }
  return -1;
}


void
start_make_capsule
(tdfstring_list prop_names, capsule_link_list capsule_linking)
{
  int i;

  while (capsule_freelist) {
    capsule_frees * cf = capsule_freelist -> next;
    xfree(capsule_freelist->ptr);
    xfree(capsule_freelist);
    capsule_freelist = cf;
  }

  crt_tagdef_unit_no = -1;
  unit_index = 0;
  top_aldef = NULL;
  doing_aldefs = false;

  crt_capsule_groups = prop_names.elems;
  crt_capsule_group_no = prop_names.number;

  crt_capsule_linking = capsule_linking;
  crt_capsule_link_no = capsule_linking.number;

  i = find_index("token");
  capsule_no_of_tokens = (i == -1) ? 0 : natint((capsule_linking.members[i]).n);

  i = find_index("tag");
  capsule_no_of_tags = (i == -1) ? 0 : natint((capsule_linking.members[i]).n);

  i = find_index("alignment");
  capsule_no_of_als = (i == -1) ? 0 : natint((capsule_linking.members[i]).n);

  i = find_index("diagtag");		/* TDF_DIAG3 */
  capsule_no_of_diagtags = (i == -1) ? 0 :
      natint((capsule_linking.members[i]).n);

  i = find_index("dgtag");		/* TDF_DIAG4 */
  capsule_no_of_dgtags = (i == -1) ? 0 : natint((capsule_linking.members[i]).n);

  capsule_toktab = rf_xcalloc(capsule_no_of_tokens, sizeof(tok_define));
  capsule_tagtab = rf_xcalloc(capsule_no_of_tags, sizeof(dec));
  capsule_altab = rf_xcalloc(capsule_no_of_als, sizeof(aldef));
  capsule_diag_tagtab = rf_xcalloc(capsule_no_of_diagtags, sizeof(diag_tagdef));	 
  /* TDF_DIAG3 */
  capsule_dgtab = rf_xcalloc(capsule_no_of_dgtags, sizeof(dgtag_struct));	/* TDF_DIAG4 */

  for (i = 0; i < capsule_no_of_tokens; ++i) {
     /* initialise the table of tokens */
    tok_define *tp = &capsule_toktab[i];
    tp->tok_special = false;
    tp->valpresent = false;
    tp->unit_number = crt_tagdef_unit_no;
    tp->defined = false;
    tp->tok_index = i;
    tp->is_capsule_token = true;
    tp->recursive = false;
  }

  for (i = 0; i < capsule_no_of_tags; ++i) {
    /* initialise the table of tags */
    dec *dp = &capsule_tagtab[i];
    dp->outermost = 0;
    dp->name = NULL;
    dp->extnamed = 0;
#ifdef TDF_DIAG3
    dp->diag_info = NULL;
#endif
#ifdef TDF_DIAG4
    dp->dg_name = NULL;
#endif
    dp->have_def = 0;
    dp->shape = NULL;
    dp->processed = 0;
    dp->isweak = 0;
  }

  for (i = 0; i < capsule_no_of_als; ++i) {
    /* initialise the table of alignment tags */
    aldef *ap = &capsule_altab[i];
    ap->al.state = ALDEF_NONE;
  }

  init_capsule_diagtags();	/* TDF_DIAG3 */
  init_capsule_dgtags();	/* TDF_DIAG4 */
}

capsule
f_make_capsule(tdfstring_list prop_names, capsule_link_list capsule_linking,
	       extern_link_list external_linkage, unit_list units)
{
  UNUSED(prop_names);
  UNUSED(capsule_linking);
  UNUSED(external_linkage);
  UNUSED(units);

  reader_dispatch.dispatch_capsule();
  return 0;
}

void
init_capsule(void)
{
}

capsule_link
f_make_capsule_link(tdfstring sn, tdfint n)
{
  capsule_link res;
  res.n = n;
  res.id = (char *)sn.ints.chars;
  return res;
}

error_treatment
f_errt_apply_token(token token_value, bitstream token_args)
{
   tokval v;
   v = apply_tok(token_value, token_args, SORT_ERROR_TREATMENT, NULL);
   return v.tk_error_treatment;
}

error_treatment
f_errt_cond(exp control, bitstream e1, bitstream e2)
{
  bitstream bs;
  error_treatment res;
  int n;
  bs = keep_place();
  if (control->tag != val_tag) {
    error(ERR_INTERNAL, "illegal control expression");
  }
  n = no(control);
  retcell(control);
  if (n==0) {
     set_place(e2);
     res = d_error_treatment();
  } else {
     set_place(e1);
     res = d_error_treatment();
  }
  set_place(bs);
  return res;
}


exp
f_exp_apply_token(token token_value, bitstream token_args)
{
   tokval v;
   v = apply_tok(token_value, token_args, SORT_EXP, NULL);
   return v.tk_exp;
}

exp
f_exp_cond(exp control, bitstream e1, bitstream e2)
{
  bitstream bs;
  exp res;
  int n;
  bs = keep_place();
  if (control->tag != val_tag) {
    error(ERR_INTERNAL, "illegal control expression");
  }
  n = no(control);
  retcell(control);
  if (n==0) {
     set_place(e2);
     res = d_exp();
  } else {
     set_place(e1);
     res = d_exp();
  }
  set_place(bs);
  return res;
}

external
f_string_extern(tdfstring s)
{
  external e;
  e.isstring = 1;
  e.ex.id = s;
  return e;
}

external
f_unique_extern(unique u)
{
  external e;
  e.isstring = 0;
  e.ex.u = u;
  return e;
}

external
f_chain_extern(tdfstring s, tdfint i)
{
	UNUSED(s);
	UNUSED(i);
	error(ERR_INTERNAL, "chain_extern not yet done");
	return f_dummy_external;
}

void
init_external(void)
{
}

external f_dummy_external;

floating_variety
f_flvar_apply_token(token token_value, bitstream token_args)
{
   tokval v;
   v = apply_tok(token_value, token_args, SORT_FLOATING_VARIETY, NULL);
   return v.tk_floating_variety;
}

floating_variety
f_flvar_cond(exp control, bitstream e1, bitstream e2)
{
  bitstream bs;
  floating_variety res;
  int n;
  bs = keep_place();
  if (control->tag != val_tag) {
    error(ERR_INTERNAL, "illegal control expression");
  }
  n = no(control);
  retcell(control);
  if (n == 0) {
     set_place(e2);
     res = d_floating_variety();
  } else {
     set_place(e1);
     res = d_floating_variety();
  }
  set_place(bs);
  return res;
}


label
f_label_apply_token(token token_value, bitstream token_args)
{
   tokval v;
   v = apply_tok(token_value, token_args, SORT_LABEL, NULL);
   return v.tk_label;
}

label
f_make_label(tdfint labelno)
{
  return &unit_labtab[natint(labelno)];
}

void
init_label(void)
{
}

label f_dummy_label;

nat
f_nat_apply_token(token token_value, bitstream token_args)
{
   tokval v;
   v = apply_tok(token_value, token_args, SORT_NAT, NULL);
   return v.tk_nat;
}

nat
f_nat_cond(exp control, bitstream e1, bitstream e2)
{
  bitstream bs;
  nat res;
  int n;
  bs = keep_place();
  if (control->tag != val_tag) {
    error(ERR_INTERNAL, "illegal control expression");
  }
  n = no(control);
  retcell(control);
  if (n == 0) {
     set_place(e2);
     res = d_nat();
  } else {
     set_place(e1);
     res = d_nat();
  }
  set_place(bs);
  return res;
}

ntest
f_ntest_apply_token(token token_value, bitstream token_args)
{
   tokval v;
   v = apply_tok(token_value, token_args, SORT_NTEST, NULL);
   return v.tk_ntest;
}

ntest
f_ntest_cond(exp control, bitstream e1, bitstream e2)
{
  bitstream bs;
  ntest res;
  int n;
  bs = keep_place();
  if (control->tag != val_tag) {
    error(ERR_INTERNAL, "illegal control expression");
  }
  n = no(control);
  retcell(control);
  if (n == 0) {
     set_place(e2);
     res = d_ntest();
  } else {
     set_place(e1);
     res = d_ntest();
  }
  set_place(bs);
  return res;
}

rounding_mode
f_rounding_mode_apply_token(token token_value, bitstream token_args)
{
   tokval v;
   v = apply_tok(token_value, token_args, SORT_ROUNDING_MODE, NULL);
   return v.tk_rounding_mode;
}

rounding_mode
f_rounding_mode_cond(exp control, bitstream e1, bitstream e2)
{
  bitstream bs;
  rounding_mode res;
  int n;
  bs = keep_place();
  if (control->tag != val_tag)
    error(ERR_INTERNAL, "illegal control expression");
  n = no(control);
  retcell(control);
  if (n == 0) {
     set_place(e2);
     res = d_rounding_mode();
  } else {
     set_place(e1);
     res = d_rounding_mode();
  }
  set_place(bs);
  return res;
}

shape
f_shape_apply_token(token token_value, bitstream token_args)
{
   tokval v;
   v = apply_tok(token_value, token_args, SORT_SHAPE, NULL);
   return v.tk_shape;
}

shape
f_shape_cond(exp control, bitstream e1, bitstream e2)
{
  bitstream bs;
  shape res;
  int n;
  bs = keep_place();
  if (control->tag != val_tag) {
    error(ERR_INTERNAL, "illegal control expression");
  }
  n = no(control);
  retcell(control);
  if (n == 0) {
     set_place(e2);
     res = d_shape();
  } else {
     set_place(e1);
     res = d_shape();
  }
  set_place(bs);
  return res;
}

signed_nat
f_signed_nat_apply_token(token token_value, bitstream token_args)
{
   tokval v;
   v = apply_tok(token_value, token_args, SORT_SIGNED_NAT, NULL);
   return v.tk_signed_nat;
}

signed_nat
f_signed_nat_cond(exp control, bitstream e1, bitstream e2)
{
  bitstream bs;
  signed_nat res;
  int n;
  bs = keep_place();
  if (control->tag != val_tag) {
    error(ERR_INTERNAL, "illegal control expression");
  }
  n = no(control);
  retcell(control);
  if (n == 0) {
     set_place(e2);
     res = d_signed_nat();
  } else {
     set_place(e1);
     res = d_signed_nat();
  }
  set_place(bs);
  return res;

}


sortname f_alignment_sort;
sortname f_bitfield_variety;
sortname f_bool;
sortname f_error_treatment;
sortname f_exp;
sortname f_floating_variety;
sortname f_label;
sortname f_nat;
sortname f_ntest;
sortname f_rounding_mode;
sortname f_shape;
sortname f_signed_nat;
sortname f_tag;
sortname f_al_tag;
sortname f_diag_filename;	/* TDF_DIAG3 */
sortname f_diag_type;		/* TDF_DIAG3 */
sortname f_foreign;
sortname f_access;
sortname f_transfer_mode;
sortname f_procprops;
sortname f_string;
sortname f_dg;			/* TDF_DIAG4 */
sortname f_dg_dim;		/* TDF_DIAG4 */
sortname f_dg_filename;		/* TDF_DIAG4 */
sortname f_dg_idname;		/* TDF_DIAG4 */
sortname f_dg_name;		/* TDF_DIAG4 */
sortname f_dg_type;		/* TDF_DIAG4 */

sortname
f_foreign_sort(tdfstring foreign_name)
{
  if (streq(foreign_name.ints.chars, "~diag_file")) {	/* TDF_DIAG3 */
    return f_diag_filename;
  }
  if (streq(foreign_name.ints.chars, "~diag_type")) {	/* TDF_DIAG3 */
    return f_diag_type;
  }
  if (streq(foreign_name.ints.chars, "DG")) {		/* TDF_DIAG4 */
    return f_dg;
  }
  if (streq(foreign_name.ints.chars, "DG_DIM")) {	/* TDF_DIAG4 */
    return f_dg_dim;
  }
  if (streq(foreign_name.ints.chars, "DG_FILENAME")) {/* TDF_DIAG4 */
    return f_dg_filename;
  }
  if (streq(foreign_name.ints.chars, "DG_IDNAME")) {	/* TDF_DIAG4 */
    return f_dg_idname;
  }
  if (streq(foreign_name.ints.chars, "DG_NAME")) {	/* TDF_DIAG4 */
    return f_dg_name;
  }
  if (streq(foreign_name.ints.chars, "DG_TYPE")) {	/* TDF_DIAG4 */
    return f_dg_type;
  }
  return f_foreign;
}

sortname
f_token(sortname result, sortname_list params)
{
   sortname res;
   res.code = SORT_TOKEN;
   res.result = result.code;
   res.pars = params;
   return res;
}

sortname f_variety;
void
init_sortname(void)
{
   f_alignment_sort.code   = SORT_ALIGNMENT;
   f_bitfield_variety.code = SORT_BITFIELD_VARIETY;
   f_bool.code             = SORT_BOOL;
   f_error_treatment.code  = SORT_ERROR_TREATMENT;
   f_exp.code              = SORT_EXP;
   f_floating_variety.code = SORT_FLOATING_VARIETY;
   f_label.code            = SORT_LABEL;
   f_nat.code              = SORT_NAT;
   f_ntest.code            = SORT_NTEST;
   f_rounding_mode.code    = SORT_ROUNDING_MODE;
   f_shape.code            = SORT_SHAPE;
   f_signed_nat.code       = SORT_SIGNED_NAT;
   f_tag.code              = SORT_TAG;
   f_al_tag.code           = SORT_AL_TAG;
   f_variety.code          = SORT_VARIETY;
   f_diag_filename.code    = SORT_FILENAME;      /* TDF_DIAG3 */
   f_diag_type.code        = SORT_DIAG_TYPE;     /* TDF_DIAG3 */
   f_foreign.code          = SORT_FOREIGN;
   f_access.code           = SORT_ACCESS;
   f_transfer_mode.code    = SORT_TRANSFER_MODE;
   f_procprops.code        = SORT_PROCPROPS;
   f_string.code           = SORT_STRING;
   f_dg.code               = SORT_DG;            /* TDF_DIAG4 */
   f_dg_dim.code           = SORT_DG_DIM;        /* TDF_DIAG4 */
   f_dg_filename.code      = SORT_DG_FILENAME;   /* TDF_DIAG4 */
   f_dg_idname.code        = SORT_DG_IDNAME;     /* TDF_DIAG4 */
   f_dg_name.code          = SORT_DG_NAME;       /* TDF_DIAG4 */
   f_dg_type.code          = SORT_DG_TYPE;       /* TDF_DIAG4 */
}

sortname f_dummy_sortname;

tag
f_tag_apply_token(token token_value, bitstream token_args)
{
   tokval v;
   v = apply_tok(token_value, token_args, SORT_TAG, NULL);
   return v.tk_tag;
}

al_tag
f_al_tag_apply_token(token token_value, bitstream token_args)
{
   tokval v;
   v = apply_tok(token_value, token_args, SORT_AL_TAG, NULL);
   return v.tk_al_tag;
}

tag
f_make_tag(tdfint tagno)
{
  return get_dec(natint(tagno));
}

void
init_tag(void)
{
}

al_tag
f_make_al_tag(tdfint tagno)
{
  return get_aldef(natint(tagno));
}

void
init_al_tag(void)
{
}

tag f_dummy_tag;
al_tag f_dummy_al_tag;

static void
check_sig(tag tag, string sig)
{
	char *sid = sig.ints.chars;
	int s = (sig.size * sig.number) / 8;
	if (tag->has_signature) {
		char *name = tag->name;
	    	int i;
		for (i = 0; i < s; i++) {
			if (name[i] != sid[i]) {
				break;
			}
		}
		if (i != s || name[s] != 0) {
			   error(ERR_INTERNAL, "Signatures should be equal. %s != %s", name, sid);
		}
	} else {
		tag->name = sid;
		tag->has_signature = 1;
	}
}





tagdec
f_make_id_tagdec(tdfint t_intro, access_option acc, string_option sig, shape x)
{
  tagdec res;
  res.tag = get_dec(natint(t_intro));
  res.sha = x;
  res.acc = acc;
  res.is_variable = false;
  res.is_common   = false;
  res.tag->is_common = false;
  if (sig.present) {
    check_sig(res.tag, sig.val);
  }
  return res;
}

tagdec
f_make_var_tagdec(tdfint t_intro, access_option acc, string_option sig, shape x)
{
  tagdec res;
  res.tag = get_dec(natint(t_intro));
  res.sha = x;
  res.acc = acc;
  res.is_variable = true;
  res.is_common   = false;
  res.tag->is_common = false;
  if (sig.present) {
    check_sig(res.tag, sig.val);
  }
  return res;
}

tagdec
f_common_tagdec(tdfint t_intro, access_option acc, string_option sig, shape x)
{
  tagdec res;
  res.tag = get_dec(natint(t_intro));
  res.sha = x;
  res.acc = acc;
  res.is_variable = true;
  res.is_common   = true;
  res.tag->is_common = false;
  if (sig.present) {
    check_sig(res.tag, sig.val);
  }
  return res;
}

void
init_tagdec(void)
{
}

tagdec f_dummy_tagdec;


void
start_make_id_tagdef(tdfint t)
{
  UNUSED(t);
  rep_make_proc = false;
}

tagdef
f_make_id_tagdef(tdfint t, string_option sig, exp e)
{
  dec *dp = get_dec(natint(t));
  tagdef res;
  res.tag = dp;
  if (dp->processed ||
      child(dp->exp) != NULL) {
    res.def = NULL; /* set to NULL if already output */
  } else {
    res.def = e;
  }
  res.is_variable = false;
  res.is_common   = false;
  if (sig.present) {
    check_sig(dp, sig.val);
  }
  rep_make_proc = true;
  return res;
}

void
start_make_var_tagdef(tdfint t)
{
  UNUSED(t);
}

tagdef
f_make_var_tagdef(tdfint t, access_option opt_access, string_option sig, exp e)
{
  dec *dp = get_dec(natint(t));
  tagdef res;
  UNUSED(opt_access);
  res.tag = dp;
  if (dp->processed ||
      child(dp->exp) != NULL) {
    res.def = NULL; /* set to NULL if already output */
  } else {
    res.def = e;
  }
  res.is_variable = true;
  res.is_common   = false;
  if (sig.present) {
    check_sig(dp, sig.val);
  }
  return res;
}

void
start_common_tagdef(tdfint t)
{
  UNUSED(t);
}

tagdef
f_common_tagdef(tdfint t, access_option opt_access, string_option sig, exp e)
{
  dec *dp = get_dec(natint(t));
  tagdef res;
  UNUSED(opt_access);
  res.tag = dp;
  res.def = e;
  res.is_variable = true;
  res.is_common   = true;
  if (sig.present) {
    check_sig(dp, sig.val);
  }
  return res;
}

void
init_tagdef(void)
{
}

void
init_al_tagdef(void)
{
}

tagdef f_dummy_tagdef;
al_tagdef f_dummy_al_tagdef;

tagextern
f_make_tagextern(tdfint internal, external ext)
{
  dec *dp = &capsule_tagtab[natint(internal)];
  char *name = external_to_string(ext);
  dp->name = add_prefix(name_prefix, name);
  dp->outermost = 1;
  dp->extnamed = 1;

  return 0;
}

taglink
f_make_taglink(tdfint internal, tdfint ext)
{
  unit_ind_tags[natint(internal)] = &capsule_tagtab[natint(ext)];
  return 0;
}


allink
f_make_allink(tdfint internal, tdfint ext)
{
  unit_ind_als[natint(internal)] = &capsule_altab[natint(ext)];
  return 0;
}


tokdec
f_make_tokdec(tdfint tok, string_option sig, sortname s)
{
  tok_define *tok_d = get_tok(natint(tok));
  if (sig.present) {
    check_tok_sig(tok_d, sig.val);
  }
  UNUSED(s);
  return 0;
}

void
init_tokdec(void)
{
}

tokdec f_dummy_tokdec;

tokdef
f_make_tokdef(tdfint tokn, string_option sig, bitstream def)
{
  sortname result_sort;
  tokformals_list params;
  place old_place;
  tok_define *tok = get_tok(natint(tokn));
  if (sig.present) {
    check_tok_sig(tok, sig.val);
  }
  old_place = keep_place();
  set_place(def);
  IGNORE getcode(1);
  result_sort = d_sortname();
  params = d_tokformals_list();
  tok->tdsort = result_sort;
  tok->params = params;
  tok->tdplace = keep_place();
  tok->defined = true;
  tok->tok_context = NULL;

    /* record the tables which are current so that they can be
       used when the token is applied */
  tok->my_labtab = unit_labtab;
  tok->my_tagtab = unit_ind_tags;
  tok->my_toktab = unit_ind_tokens;
  tok->my_altab = unit_ind_als;
  tok->my_diagtab = unit_ind_diagtags;	/* TDF_DIAG3 */
  tok->my_dgtab = unit_ind_dgtags;	/* TDF_DIAG4 */
  if (params.number == 0) {
    tok -> re_evaluate = false;
  } else {
    tok -> re_evaluate = true;
  }

  set_place(old_place);
  return 0;
}

token
f_use_tokdef(bitstream def)
{
  token tok = (token)xcalloc(1, sizeof(tok_define)) /* space thief ?*/;
  sortname result_sort;
  tokformals_list params;
  place old_place;

  old_place = keep_place();
  set_place(def);
  IGNORE getcode(1);
  result_sort = d_sortname();
  params = d_tokformals_list();
  tok->tok_special = false;
  tok->valpresent = false;
  tok->unit_number = crt_tagdef_unit_no;
  tok->defined = false;
  tok->is_capsule_token = false;
  tok->recursive = false;
  tok->tdsort = result_sort;
  tok->params = params;
  tok->tdplace = keep_place();
  tok->defined = true;
  tok->tok_context = crt_context;

  /* record the tables which are current so that they can be used when
     the token is applied */
  tok->my_labtab = unit_labtab;
  tok->my_tagtab = unit_ind_tags;
  tok->my_toktab = unit_ind_tokens;
  tok->my_altab = unit_ind_als;
  tok->my_diagtab = unit_ind_diagtags;	/* TDF_DIAG3 */
  tok->my_dgtab = unit_ind_dgtags;	/* TDF_DIAG4 */

  if (params.number == 0) {
    tok->re_evaluate = false;
  } else {
    tok->re_evaluate = true;
  }

  set_place(old_place);
  return tok;
}


void
init_tokdef(void)
{
}

tokdef f_dummy_tokdef;

token
f_token_apply_token(token token_value, bitstream token_args)
{
   tokval v;
   v = apply_tok(token_value, token_args, SORT_TOKEN, NULL);
   return v.tk_token;
}

token
f_make_tok(tdfint tokno)
{
  return get_tok(natint(tokno));
}

void
init_token(void)
{
}

token f_dummy_token;

token_defn
f_token_definition(sortname result_sort, tokformals_list tok_params)
{
  UNUSED(result_sort);
  UNUSED(tok_params);
  error(ERR_INTERNAL, "dummy");
  return f_dummy_token_defn;
}

void
init_token_defn(void)
{
}

token_defn f_dummy_token_defn;

tokextern
f_make_tokextern(tdfint internal, external ext)
{
  tok_define *t = &capsule_toktab[natint(internal)];
  char *s = external_to_string(ext);
  t->tok_name = s;

  /* determines special tokens specific to each machine */
  if (machine_toks(s)) {
    t->tok_special = true;
  }

  if (replace_arith_type) {
    if (streq(s, "~arith_type")) {
      t->tok_special = true;
    }
    if (streq(s, "~promote")) {
      t->tok_special = true;
    }
    if (streq(s, "~sign_promote")) {
      t->tok_special = true;
    }
    if (streq(s, "~convert")) {
      t->tok_special = true;
    }
  }
  if (do_alloca && streq(s, "~alloca")) {
    t->tok_special = true;
  }
  return 0;
}

alextern
f_make_alextern(tdfint internal, external ext)
{
  UNUSED(internal);
  UNUSED(ext);
  return 0;
}


tokformals
f_make_tokformals(sortname sn, tdfint tk)
{
  tokformals res;
  res.sn = sn;
  res.tk = natint(tk);
  return res;
}

void
init_tokformals(void)
{
}

toklink
f_make_toklink(tdfint internal, tdfint ext)
{
  unit_ind_tokens[natint(internal)] = &capsule_toktab[natint(ext)];
  return 0;
}

link
f_make_link(tdfint internal, tdfint ext)
{
  switch (crt_links_type)
   {
     case TOK_TYPE:     IGNORE f_make_toklink(internal, ext);     return 0;
     case TAG_TYPE:     IGNORE f_make_taglink(internal, ext);     return 0;
     case AL_TYPE:      IGNORE f_make_allink(internal, ext);      return 0;
     case DIAGTAG_TYPE: IGNORE f_make_diagtaglink(internal, ext); return 0; /* TDF_DIAG3 */
     case DGTAG_TYPE:   IGNORE f_make_dglink(internal, ext);      return 0; /* TDF_DIAG4 */

     default:
       error(ERR_INTERNAL, "illegal variable type");
       return 0;
   }
}

unique
f_make_unique(tdfstring_list text)
{
  return text;
}

void
init_unique(void)
{
}


variety
f_var_apply_token(token token_value, bitstream token_args)
{
   tokval v;
   v = apply_tok(token_value, token_args, SORT_VARIETY, NULL);
   return v.tk_variety;
}

variety
f_var_cond(exp control, bitstream e1, bitstream e2)
{
  bitstream bs;
  variety res;
  int n;
  bs = keep_place();
  if (control->tag != val_tag) {
    error(ERR_INTERNAL, "illegal control expression");
  }
  n = no(control);
  retcell(control);
  if (n==0) {
    set_place(e2);
    res = d_variety();
  } else {
    set_place(e1);
    res = d_variety();
  }
  
  set_place(bs); return res;
}


static void
start_make_tokdec_unit(int no_of_tokens, int no_of_tags, int no_of_als,
		       int no_of_diagtags, int no_of_dgtags)
{
  int i;

  unit_no_of_tokens = no_of_tokens;
  unit_ind_tokens = rf_xcalloc(unit_no_of_tokens, sizeof(tok_define *));
  for (i = 0; i < unit_no_of_tokens; ++i) {
    unit_ind_tokens[i] = NULL;
  }

  unit_no_of_tags = no_of_tags;
  unit_ind_tags = rf_xcalloc(unit_no_of_tags, sizeof(dec *));
  for (i = 0; i < unit_no_of_tags; ++i) {
    unit_ind_tags[i] = NULL;
  }

  unit_no_of_als = no_of_als;
  unit_ind_als = rf_xcalloc(unit_no_of_als, sizeof(aldef *));
  for (i = 0; i < unit_no_of_als; ++i) {
    unit_ind_als[i] = NULL;
  }

  unit_no_of_diagtags = no_of_diagtags;		/* TDF_DIAG3 */
  unit_ind_diagtags = rf_xcalloc(unit_no_of_diagtags, sizeof(diag_tagdef *));
  for (i = 0; i < unit_no_of_diagtags; ++i) {
    unit_ind_diagtags[i] = NULL;
  }

  unit_no_of_dgtags = no_of_dgtags;		/* TDF_DIAG4 */
  unit_ind_dgtags = rf_xcalloc(unit_no_of_dgtags, sizeof(dgtag_struct *));
  for (i = 0; i < unit_no_of_dgtags; ++i) {
    unit_ind_dgtags[i] = NULL;
  }
}

tokdec_unit
f_make_tokdec_unit(void)
{
  int i;
  int j = 0;
  for (i = 0; i < unit_no_of_tokens; ++i) {
    if (unit_ind_tokens[i] == NULL) {
      unit_ind_tokens[i] = &unit_toktab[j++];
    }
  }
  start_bytestream();
  IGNORE d_tokdec_list();
  end_bytestream();
  return 0;
}

static void
start_make_tokdef_unit(int no_of_tokens, int no_of_tags, int no_of_als,
		       int no_of_diagtags, int no_of_dgtags)
{
  int i;

  unit_no_of_tokens = no_of_tokens;
  unit_ind_tokens = rf_xcalloc(unit_no_of_tokens, sizeof(tok_define *));
  for (i = 0; i < unit_no_of_tokens; ++i) {
    unit_ind_tokens[i] = NULL;
  }

  unit_no_of_tags = no_of_tags;
  unit_ind_tags = rf_xcalloc(unit_no_of_tags, sizeof(dec *));
  for (i = 0; i < unit_no_of_tags; ++i) {
    unit_ind_tags[i] = NULL;
  }

  unit_no_of_als = no_of_als;
  unit_ind_als = rf_xcalloc(unit_no_of_als, sizeof(aldef *));
  for (i = 0; i < unit_no_of_als; ++i) {
    unit_ind_als[i] = NULL;
  }

  unit_no_of_diagtags = no_of_diagtags;		/* TDF_DIAG3 */
  unit_ind_diagtags = rf_xcalloc(unit_no_of_diagtags,
					      sizeof(diag_tagdef *));
  for (i = 0; i < unit_no_of_diagtags; ++i) {
    unit_ind_diagtags[i] = NULL;
  }

  unit_no_of_dgtags = no_of_dgtags;		/* TDF_DIAG4 */
  unit_ind_dgtags = rf_xcalloc(unit_no_of_dgtags,
					     sizeof(dgtag_struct *));
  for (i = 0; i < unit_no_of_dgtags; ++i) {
    unit_ind_dgtags[i] = NULL;
  }
}

tokdef_unit
f_make_tokdef_unit(void)
{
  int i;
  int j = 0;
  int no_of_labels;
  for (i = 0; i < unit_no_of_tokens; ++i) {
    if (unit_ind_tokens[i] == NULL) {
      unit_ind_tokens[i] = &unit_toktab[j++];
    }
  }
  j = 0;
  for (i = 0; i < unit_no_of_tags; ++i) {
    if (unit_ind_tags[i] == NULL) {
      unit_ind_tags[i] = &unit_tagtab[j++];
    }
  }
  j = 0;
  for (i = 0; i < unit_no_of_als; ++i) {
    if (unit_ind_als[i] == NULL) {
      unit_ind_als[i] = &unit_altab[j++];
    }
  }
  j = 0;
  for (i = 0; i < unit_no_of_dgtags; ++i) {	/* TDF_DIAG4 */
    if (unit_ind_dgtags[i] == NULL) {
      unit_ind_dgtags[i] = &unit_dgtagtab[j++];
    }
  }
  start_bytestream();
  no_of_labels = small_dtdfint();
  unit_no_of_labels = no_of_labels;
  unit_labtab = rf_xcalloc(unit_no_of_labels, sizeof(exp));
  IGNORE d_tokdef_list();
  end_bytestream();

  /* tables must be kept for use during token application */

  return 0;
}

static void
start_make_tagdec_unit(int no_of_tokens, int no_of_tags, int no_of_als,
		       int no_of_diagtags, int no_of_dgtags)
{
  int i;

  unit_no_of_tokens = no_of_tokens;
  unit_ind_tokens = rf_xcalloc(unit_no_of_tokens, sizeof(tok_define *));
  for (i = 0; i < unit_no_of_tokens; ++i) {
    unit_ind_tokens[i] = NULL;
  }

  unit_no_of_tags = no_of_tags;
  unit_ind_tags = rf_xcalloc(unit_no_of_tags, sizeof(dec *));
  for (i = 0; i < unit_no_of_tags; ++i) {
    unit_ind_tags[i] = NULL;
  }

  unit_no_of_als = no_of_als;
  unit_ind_als = rf_xcalloc(unit_no_of_als, sizeof(aldef *));
  for (i = 0; i < unit_no_of_als; ++i) {
    unit_ind_als[i] = NULL;
  }

  unit_no_of_diagtags = no_of_diagtags;		/* TDF_DIAG3 */
  unit_ind_diagtags = rf_xcalloc(unit_no_of_diagtags,
					      sizeof(diag_tagdef *));
  for (i = 0; i < unit_no_of_diagtags; ++i) {
    unit_ind_diagtags[i] = NULL;
  }

  unit_no_of_dgtags = no_of_dgtags;		/* TDF_DIAG4 */
  unit_ind_dgtags = rf_xcalloc(unit_no_of_dgtags, sizeof(dgtag_struct *));
  for (i = 0; i < unit_no_of_dgtags; ++i) {
    unit_ind_dgtags[i] = NULL;
  }
}

tagdec_unit
f_make_tagdec_unit(void)
{
  int i;
  int j = 0;
  int no_of_labels;
  for (i = 0; i < unit_no_of_tokens; ++i) {
    if (unit_ind_tokens[i] == NULL) {
      unit_ind_tokens[i] = &unit_toktab[j++];
    }
  }
  j = 0;
  for (i = 0; i < unit_no_of_tags; ++i) {
    if (unit_ind_tags[i] == NULL) {
      unit_ind_tags[i] = &unit_tagtab[j++];
    }
  }
  j = 0;
  for (i = 0; i < unit_no_of_als; ++i) {
    if (unit_ind_als[i] == NULL) {
      unit_ind_als[i] = &unit_altab[j++];
    }
  }
  j = 0;
  for (i = 0; i < unit_no_of_dgtags; ++i) {	/* TDF_DIAG4 */
    if (unit_ind_dgtags[i] == NULL) {
      unit_ind_dgtags[i] = &unit_dgtagtab[j++];
    }
  }
  start_bytestream();
  no_of_labels = small_dtdfint();
  unit_no_of_labels = no_of_labels;
  unit_labtab = rf_xcalloc(unit_no_of_labels, sizeof(exp));
  IGNORE d_tagdec_list();
  end_bytestream();

  xfree(unit_ind_tokens);
  xfree(unit_ind_tags);
  xfree(unit_ind_als);
  xfree(unit_labtab);

  xfree(unit_toktab);

  return 0;
}

static void
start_make_versions_unit(int no_of_tokens, int no_of_tags, int no_of_als,
			 int no_of_diagtags, int no_of_dgtags)
{
  int i;

  unit_no_of_tokens = no_of_tokens;
  unit_ind_tokens = rf_xcalloc(unit_no_of_tokens, sizeof(tok_define *));
  for (i = 0; i < unit_no_of_tokens; ++i) {
    unit_ind_tokens[i] = NULL;
  }

  unit_no_of_tags = no_of_tags;
  unit_ind_tags = rf_xcalloc(unit_no_of_tags, sizeof(dec *));
  for (i = 0; i < unit_no_of_tags; ++i) {
    unit_ind_tags[i] = NULL;
  }

  unit_no_of_als = no_of_als;
  unit_ind_als = rf_xcalloc(unit_no_of_als, sizeof(aldef *));
  for (i = 0; i < unit_no_of_als; ++i) {
    unit_ind_als[i] = NULL;
  }

  unit_no_of_diagtags = no_of_diagtags;		/* TDF_DIAG3 */
  unit_ind_diagtags = rf_xcalloc(unit_no_of_diagtags,
					      sizeof(diag_tagdef *));
  for (i = 0; i < unit_no_of_diagtags; ++i) {
    unit_ind_diagtags[i] = NULL;
  }

  unit_no_of_dgtags = no_of_dgtags;		/* TDF_DIAG4 */
  unit_ind_dgtags = rf_xcalloc(unit_no_of_dgtags, sizeof(dgtag_struct *));
  for (i = 0; i < unit_no_of_dgtags; ++i) {
    unit_ind_dgtags[i] = NULL;
  }
}

version_props
f_make_versions_unit(void)
{
  int i;
  int j = 0;
  for (i = 0; i < unit_no_of_tokens; ++i) {
    if (unit_ind_tokens[i] == NULL) {
      unit_ind_tokens[i] = &unit_toktab[j++];
    }
  }
  j = 0;
  for (i = 0; i < unit_no_of_tags; ++i) {
    if (unit_ind_tags[i] == NULL) {
      unit_ind_tags[i] = &unit_tagtab[j++];
    }
  }
  j = 0;
  for (i = 0; i < unit_no_of_als; ++i) {
    if (unit_ind_als[i] == NULL) {
      unit_ind_als[i] = &unit_altab[j++];
    }
  }
  start_bytestream();
  IGNORE d_version_list();
  end_bytestream();

  xfree(unit_ind_tokens);
  xfree(unit_ind_tags);
  xfree(unit_ind_als);

  xfree(unit_toktab);
  xfree(unit_tagtab);

  return 0;
}

static void
start_make_tagdef_unit(int no_of_tokens, int no_of_tags, int no_of_als,
		       int no_of_diagtags, int no_of_dgtags)
{
  int i;

  if (separate_units) {
    ++crt_tagdef_unit_no;
    set_large_alloc();
  }

  unit_no_of_tokens = no_of_tokens;
  unit_ind_tokens = rf_xcalloc(unit_no_of_tokens, sizeof(tok_define *));
  for (i = 0; i < unit_no_of_tokens; ++i) {
    unit_ind_tokens[i] = NULL;
  }

  unit_no_of_tags = no_of_tags;
  unit_ind_tags = rf_xcalloc(unit_no_of_tags, sizeof(dec *));
  for (i = 0; i < unit_no_of_tags; ++i) {
    unit_ind_tags[i] = NULL;
  }

  unit_no_of_als = no_of_als;
  unit_ind_als = rf_xcalloc(unit_no_of_als, sizeof(aldef *));
  for (i = 0; i < unit_no_of_als; ++i) {
    unit_ind_als[i] = NULL;
  }

  unit_no_of_diagtags = no_of_diagtags;		/* TDF_DIAG3 */
  unit_ind_diagtags = rf_xcalloc(unit_no_of_diagtags, sizeof(diag_tagdef *));
  for (i = 0; i < unit_no_of_diagtags; ++i) {
    unit_ind_diagtags[i] = NULL;
  }

  unit_no_of_dgtags = no_of_dgtags;		/* TDF_DIAG4 */
  unit_ind_dgtags = rf_xcalloc(unit_no_of_dgtags, sizeof(dgtag_struct *));
  for (i = 0; i < unit_no_of_dgtags; ++i) {
    unit_ind_dgtags[i] = NULL;
  }
}




tagdef_unit
f_make_tagdef_unit(void)
{
  int i;
  int j = 0;
  int no_of_labels;
  for (i = 0; i < unit_no_of_tokens; ++i) {
    if (unit_ind_tokens[i] == NULL) {
      unit_ind_tokens[i] = &unit_toktab[j++];
    }
  }
  j = 0;
  for (i = 0; i < unit_no_of_tags; ++i) {
    if (unit_ind_tags[i] == NULL) {
      unit_ind_tags[i] = &unit_tagtab[j++];
    }
  }
  j = 0;
  for (i = 0; i < unit_no_of_als; ++i) {
    if (unit_ind_als[i] == NULL) {
      unit_ind_als[i] = &unit_altab[j++];
    }
  }
  j = 0;
  for (i = 0; i < unit_no_of_dgtags; ++i) {	/* TDF_DIAG4 */
    if (unit_ind_dgtags[i] == NULL) {
      unit_ind_dgtags[i] = &unit_dgtagtab[j++];
    }
  }
  start_bytestream();
  no_of_labels = small_dtdfint();
  unit_no_of_labels = no_of_labels;
  unit_labtab = rf_xcalloc(unit_no_of_labels, sizeof(exp));
  IGNORE d_tagdef_list();
  tidy_initial_values();
  reader_dispatch.dispatch_unit();
  end_bytestream();

  xfree(unit_ind_tokens);
  xfree(unit_ind_tags);
  xfree(unit_ind_als);
  xfree(unit_labtab);

  xfree(unit_toktab);
  xfree(unit_tagtab);

  return 0;
}

static void
start_make_aldef_unit(int no_of_tokens, int no_of_tags, int no_of_als,
		      int no_of_diagtags, int no_of_dgtags)
{
  int i;

  unit_no_of_tokens = no_of_tokens;
  unit_ind_tokens = rf_xcalloc(unit_no_of_tokens, sizeof(tok_define *));
  for (i = 0; i < unit_no_of_tokens; ++i) {
    unit_ind_tokens[i] = NULL;
  }

  unit_no_of_tags = no_of_tags;
  unit_ind_tags = rf_xcalloc(unit_no_of_tags, sizeof(dec *));
  for (i = 0; i < unit_no_of_tags; ++i) {
    unit_ind_tags[i] = NULL;
  }

  unit_no_of_als = no_of_als;
  unit_ind_als = rf_xcalloc(unit_no_of_als, sizeof(aldef *));
  for (i = 0; i < unit_no_of_als; ++i) {
    unit_ind_als[i] = NULL;
  }

  unit_no_of_diagtags = no_of_diagtags;		/* TDF_DIAG3 */
  unit_ind_diagtags = rf_xcalloc(unit_no_of_diagtags,
					      sizeof(diag_tagdef *));
  for (i = 0; i < unit_no_of_diagtags; ++i) {
    unit_ind_diagtags[i] = NULL;
  }

  unit_no_of_dgtags = no_of_dgtags;		/* TDF_DIAG4 */
  unit_ind_dgtags = rf_xcalloc(unit_no_of_dgtags, sizeof(dgtag_struct *));
  for (i = 0; i < unit_no_of_dgtags; ++i) {
    unit_ind_dgtags[i] = NULL;
  }
}

aldef_unit
f_make_aldef_unit(void)
{
  int i;
  int j = 0;
  int no_of_labels;
  for (i = 0; i < unit_no_of_tokens; ++i) {
    if (unit_ind_tokens[i] == NULL) {
      unit_ind_tokens[i] = &unit_toktab[j++];
    }
  }
  j = 0;
  for (i = 0; i < unit_no_of_als; ++i) {
    if (unit_ind_als[i] == NULL) {
      unit_ind_als[i] = &unit_altab[j++];
    }
  }
  start_bytestream();
  no_of_labels = small_dtdfint();
  unit_no_of_labels = no_of_labels;
  unit_labtab = rf_xcalloc(unit_no_of_labels, sizeof(exp));
  IGNORE d_al_tagdef_list();
  end_bytestream();

  xfree(unit_ind_tokens);
  xfree(unit_ind_tags);
  xfree(unit_ind_als);
  xfree(unit_labtab);

  xfree(unit_toktab);
  xfree(unit_tagtab);

  return 0;
}

void
start_make_unit(tdfint_list lvl)
{
  int w;
  int ntok = 0;
  int ntag = 0;
  int nal = 0;
  int ndiagtype = 0;	/* TDF_DIAG3 */
  int ndgtag = 0;	/* TDF_DIAG4 */

  ++unit_index;

  if (lvl.number != 0) {
    w = find_index("token");
    ntok = (w == -1) ? 0 : natint(lvl.members[w]);
    w = find_index("tag");
    ntag = (w == -1) ? 0 : natint(lvl.members[w]);
    w = find_index("alignment");
    nal = (w == -1) ? 0 : natint(lvl.members[w]);
    w = find_index("diagtag");		/* TDF_DIAG3 */
    ndiagtype = (w == -1) ? 0 : natint(lvl.members[w]);
    w = find_index("dgtag");		/* TDF_DIAG4 */
    ndgtag = (w == -1) ? 0 : natint(lvl.members[w]);
  }

  switch (crt_group_type)
   {
     case TOKDEC_UNIT:
              start_make_tokdec_unit(ntok, ntag, nal, ndiagtype, ndgtag);
              return;
     case TOKDEF_UNIT:
              start_make_tokdef_unit(ntok, ntag, nal, ndiagtype, ndgtag);
              return;
     case AL_UNIT:
	      doing_aldefs = true;
              start_make_aldef_unit(ntok, ntag, nal, ndiagtype, ndgtag);
              return;
     case TAGDEC_UNIT:
	      if (doing_aldefs) {
                process_aldefs();
	        doing_aldefs = false;
	      }
              start_make_tagdec_unit(ntok, ntag, nal, ndiagtype, ndgtag);
              return;
     case TAGDEF_UNIT:
              start_make_tagdef_unit(ntok, ntag, nal, ndiagtype, ndgtag);
              return;
     case DIAGDEF_UNIT:		/* TDF_DIAG3 */
              start_make_diagdef_unit(ntok, ntag, nal, ndiagtype);
              return;
     case DIAGTYPE_UNIT:	/* TDF_DIAG3 */
	      if (doing_aldefs) {
                process_aldefs();
	        doing_aldefs = false;
	      }
              start_make_diagtype_unit(ntok, ntag, nal, ndiagtype);
              return;
     case LINKINFO_UNIT:
              start_make_linkinfo_unit(ntok, ntag, nal, 0 /* discarded */);
              return;
     case VERSIONS_UNIT:
              start_make_versions_unit(ntok, ntag, nal, ndiagtype, ndgtag);
              return;
     case DGCOMP_UNIT:	/* TDF_DIAG4 */
	      if (doing_aldefs) {
                process_aldefs();
	        doing_aldefs = false;
	      }
              start_make_dg_comp_unit(ntok, ntag, nal, ndgtag);
              return;
     default:
              return;
   }
}

unit
f_make_unit(tdfint_list lvl, links_list lks, bytestream prs)
{
  UNUSED(lvl);
  UNUSED(lks);
  UNUSED(prs);
  switch (crt_group_type)
   {
     case DIAGDEF_UNIT:		/* TDF_DIAG3 */
              if (diag != DIAG_NONE) {
                IGNORE f_make_diagdef_unit();
	      } else {
                ignore_bytestream();
	      }
              break;
     case DIAGTYPE_UNIT:	/* TDF_DIAG3 */
              if (diag != DIAG_NONE) {
                IGNORE f_make_diagtype_unit();
	      } else {
                ignore_bytestream();
	      }
              break;
     case DGCOMP_UNIT:	/* TDF_DIAG4 */
              if (diag != DIAG_NONE) {
                IGNORE f_make_dg_comp_unit();
	      } else {
                ignore_bytestream();
	      }
              break;

     case TOKDEC_UNIT:   IGNORE f_make_tokdec_unit();   break;
     case TOKDEF_UNIT:   IGNORE f_make_tokdef_unit();   break;
     case AL_UNIT:       IGNORE f_make_aldef_unit();    break;
     case TAGDEC_UNIT:   IGNORE f_make_tagdec_unit();   break;
     case TAGDEF_UNIT:   IGNORE f_make_tagdef_unit();   break;
     case LINKINFO_UNIT: IGNORE f_make_linkinfo_unit(); break;
     case VERSIONS_UNIT: IGNORE f_make_versions_unit(); break;

     default:
              ignore_bytestream();
              break;
   }
  return 0;
}

linkextern
f_make_linkextern(tdfint internal, external ext)
{
  switch (crt_extern_link_type)
   {
     case TOK_TYPE:     return f_make_tokextern(internal, ext);
     case TAG_TYPE:     return f_make_tagextern(internal, ext);
     case AL_TYPE:      return f_make_alextern(internal, ext);
     case DIAGTAG_TYPE: return f_make_diagtagextern(internal, ext); /* TDF_DIAG3 */
     case DGTAG_TYPE:   return f_make_dgtagextern(internal, ext);   /* TDF_DIAG4 */

     default:
       error(ERR_INTERNAL, "illegal variable type");
       return 0;
   }
}

group
f_make_group(unit_list us)
{
  UNUSED(us);
  return 0;
}

links
f_make_links(link_list ls)
{
  UNUSED(ls);
  return 0;
}

extern_link
f_make_extern_link(linkextern_list el)
{
  UNUSED(el);
  return 0;
}

tokdef_props
f_make_tokdefs(tdfint nl, tokdef_list tds)
{
  UNUSED(nl);
  UNUSED(tds);
  return 0;
}

tokdec_props
f_make_tokdecs(tokdec_list tds)
{
  UNUSED(tds);
  return 0;
}

tagdef_props
f_make_tagdefs(tdfint nl, tagdef_list tds)
{
  UNUSED(nl);
  UNUSED(tds);
  return 0;
}

al_tagdef_props
f_make_al_tagdefs(tdfint nl, al_tagdef_list tds)
{
  UNUSED(nl);
  UNUSED(tds);
  return 0;
}

tagdec_props
f_make_tagdecs(tdfint nl, tagdec_list tds)
{
 UNUSED(nl);
 UNUSED(tds);
 return 0;
}



sortname_list
new_sortname_list(int n)
{
  sortname_list res;
  res.number = n;
  res.elems = rf_xcalloc(n, sizeof(sortname));
  return res;
}

sortname_list
add_sortname_list(sortname_list list, sortname elem, int index)
{
  list.elems[index] = elem;
  return list;
}

tokformals_list
new_tokformals_list(int n)
{
  tokformals_list res;
  res.number = n;
  res.par_sorts = rf_xcalloc(n, sizeof(sortname));
  res.par_names = rf_xcalloc(n, sizeof(int));
  return res;
}

tokformals_list
add_tokformals_list(tokformals_list list, tokformals elem, int index)
{
  list.par_sorts[index] = elem.sn;
  list.par_names[index] = elem.tk;
  return list;
}

tokdec_list
new_tokdec_list(int n)
{
  UNUSED(n);
  return 0;
}

tokdec_list
add_tokdec_list(tokdec_list list, tokdec elem, int index)
{
  UNUSED(list);
  UNUSED(elem);
  UNUSED(index);
  return 0;
}

tokdef_list
new_tokdef_list(int n)
{
  UNUSED(n);
  return 0;
}

tokdef_list
add_tokdef_list(tokdef_list list, tokdef elem, int index)
{
  UNUSED(list);
  UNUSED(elem);
  UNUSED(index);
  return 0;
}

al_tagdef_list
new_al_tagdef_list(int n)
{
  UNUSED(n);
  return 0;
}

al_tagdef_list
add_al_tagdef_list(al_tagdef_list list, al_tagdef elem, int index)
{
  UNUSED(list);
  UNUSED(elem);
  UNUSED(index);
  return 0;
}


al_tagdef
f_make_al_tagdef(tdfint t, alignment a)
{
  aldef *ap = get_aldef(natint(t));
  ap->next = top_aldef;
  top_aldef = ap;
  ap->al = a->al;
  return 0;
}



tagdec_list
new_tagdec_list(int n)
{
  UNUSED(n);
  return 0;
}

tagdec_list
add_tagdec_list(tagdec_list list, tagdec elem, int index)
{
    dec *dp = elem.tag;
    shape s;
    exp e;
    UNUSED(list);
    UNUSED(index);
    s = elem.sha;

    e = getexp(s, NULL, 0, NULL, NULL, 0, 0, ident_tag);

    if (elem.is_variable) {
	if (keep_PIC_vars) {
          setvar(e);
	} else if (PIC_code && dp -> extnamed) {
          sh(e) = f_pointer(f_alignment(s));
	} else {
          setvar(e);
	}
    }

    if (elem.acc & (f_visible | f_long_jump_access)) {
      setvis(e);
    }
    if (elem.acc & f_constant) {
      setcaonly(e);
    }

    dp->acc = elem.acc;

    dp->exp = e;

    if (dp->shape != NULL) {
      if (shape_size(s) > shape_size(dp->shape)) {
        dp->shape = s;
      }
    }

    if (dp->shape == NULL) {
      dp->shape = s;
      dp->next = NULL;
      *deflist_end = dp;
      deflist_end = & ((*deflist_end)->next);
    }

    dp->var = (unsigned int)(isvar(e) || elem.is_variable);
    if (!dp->have_def) {
      setglob(e);
    }
    /* the defining exp */
    nextg(dp->exp) = dp;
    if (dp->name == NULL) {
      dp->name = make_local_name();
    }

  return 0;
}

tagdef_list
new_tagdef_list(int n)
{
  UNUSED(n);
  return 0;
}

tagdef_list
add_tagdef_list(tagdef_list list, tagdef elem, int index)
{
  dec *dp = elem.tag;
  exp old_def = child(dp->exp);
  exp new_def = elem.def;
  UNUSED(list);
  UNUSED(index);
  if (dp->processed || new_def == NULL) {
    return 0;
  }

  if (old_def == NULL ||
      shape_size(sh(new_def)) > shape_size(sh(old_def)) ||
      (new_def->tag != clear_tag && old_def->tag == clear_tag)) {
    child(dp->exp) = new_def;
    setfather(dp->exp, elem.def);
  }

  return 0;
}

tdfident_list
new_tdfident_list(int n)
{
  tdfstring_list res;
  res.elems = rf_xcalloc(n, sizeof(tdfstring));
  res.number = n;
  return res;
}

tdfident_list
add_tdfident_list(tdfident_list list, tdfident elem, int index)
{
  list.elems[index] = elem;
  return list;
}

tdfint_list
new_tdfint_list(int n)
{
  tdfint_list res;
  res.members = rf_xcalloc(n, sizeof(tdfint));
  res.number = n;
  return res;
}

tdfint_list
add_tdfint_list(tdfint_list list, tdfint elem, int index)
{
  list.members[index] = elem;
  return list;
}

group_list
new_group_list(int n)
{
  UNUSED(n);
  crt_group_type = group_type(crt_capsule_groups[0].ints.chars);
  return 0;
}

group_list
add_group_list(group_list list, group elem, int index)
{
  UNUSED(list);
  UNUSED(elem);
  if (index < (crt_capsule_group_no - 1)) {
    crt_group_type = group_type(crt_capsule_groups[index + 1].ints.chars);
  }
  return 0;
}

links_list
new_links_list(int n)
{
  UNUSED(n);
  if (crt_capsule_link_no != 0) {
    crt_links_type = links_type(crt_capsule_linking.members[0].id);
  }
  return 0;
}

links_list
add_links_list(links_list list, links elem, int index)
{
  UNUSED(list);
  UNUSED(elem);
  if (index < (crt_capsule_linking.number - 1)) {
    crt_links_type = links_type(crt_capsule_linking.members[index + 1].id);
  }
  return 0;
}

extern_link_list
new_extern_link_list(int n)
{
  UNUSED(n);
  if (crt_capsule_link_no != 0) {
    crt_extern_link_type = links_type(crt_capsule_linking.members[0].id);
  }
  return 0;
}

extern_link_list
add_extern_link_list(extern_link_list list, extern_link elem, int index)
{
  UNUSED(list);
  UNUSED(elem);
  if (index < (crt_capsule_linking.number - 1)) {
    crt_extern_link_type =
	links_type(crt_capsule_linking.members[index + 1].id);
  }
  return 0;
}

capsule_link_list
new_capsule_link_list(int n)
{
  capsule_link_list res;
  res.members = rf_xcalloc(n, sizeof(capsule_link));
  res.number = n;
  return res;
}

capsule_link_list
add_capsule_link_list(capsule_link_list list, capsule_link elem, int index)
{
  list.members[index] = elem;
  return list;
}

unit_list
new_unit_list(int n)
{
  UNUSED(n);
  return 0;
}

unit_list
add_unit_list(unit_list list, unit elem, int index)
{
  UNUSED(list);
  UNUSED(elem);
  UNUSED(index);
  return 0;
}

link_list
new_link_list(int n)
{
  int i;
  switch (crt_links_type)
   {
       /* initialise the table */
     case TOK_TYPE:
       no_of_local_tokens = unit_no_of_tokens - n;
       unit_toktab = rf_xcalloc(no_of_local_tokens,
					   sizeof(tok_define));
       for (i = 0; i < no_of_local_tokens; ++i) {
         tok_define *tp = &unit_toktab[i];
         tp->tok_special = false;
         tp->valpresent = false;
         tp->unit_number = crt_tagdef_unit_no;
         tp->defined = false;
         tp->tok_index = i;
         tp->is_capsule_token = false;
         tp->recursive = false;
       }
       return 0;
     case TAG_TYPE:
       unit_tagtab = rf_xcalloc(unit_no_of_tags - n, sizeof(dec));
       for (i = 0; i < unit_no_of_tags - n; ++i) {
         dec *dp = &unit_tagtab[i];
         dp->outermost = 0;
         dp->name = NULL;
         dp->extnamed = 0;
#ifdef TDF_DIAG3
         dp->diag_info = NULL;
#endif
#ifdef TDF_DIAG4
         dp->dg_name = NULL;
#endif
         dp->have_def = 0;
         dp->shape = NULL;
         dp->processed = 0;
         dp->isweak = 0;
         dp->exp = NULL;
       }
       return 0;
     case AL_TYPE:
       unit_altab = rf_xcalloc(unit_no_of_als - n, sizeof(aldef));
       for (i = 0; i < unit_no_of_als - n; ++i) {
         aldef *ap = &unit_altab[i];
         ap->al.state = ALDEF_NONE;
       }
       return 0;
     case DIAGTAG_TYPE:		/* TDF_DIAG3 */
       init_unit_diagtags(n);
       return 0;
     case DGTAG_TYPE:		/* TDF_DIAG4 */
       init_unit_dgtags(n);
       return 0;
     default:
       error(ERR_INTERNAL, "illegal link type");
       return 0;
   }
}

link_list
add_link_list(link_list list, link elem, int index)
{
  UNUSED(list);
  UNUSED(elem);
  UNUSED(index);
  return 0;
}

linkextern_list
new_linkextern_list(int n)
{
  UNUSED(n);
  return 0;
}

linkextern_list
add_linkextern_list(linkextern_list list, linkextern elem, int index)
{
  UNUSED(list);
  UNUSED(elem);
  UNUSED(index);
  return 0;
}

exp_option no_exp_option;

exp_option
yes_exp_option(exp elem)
{
  exp_option res;
  res.present = true;
  res.val = elem;
  return res;
}

void
init_exp_option(void)
{
   no_exp_option.present = false;
}

tag_option no_tag_option;

tag_option
yes_tag_option(tag elem)
{
  tag_option res;
  res.present = true;
  res.val = elem;
  return res;
}

void
init_tag_option(void)
{
   no_tag_option.present = false;
}

void
init_capsule_link(void)
{
}


void
init_extern_link(void)
{
}

void
init_group(void)
{
}

void
init_unit(void)
{
}

void
init_link(void)
{
}

void
init_linkextern(void)
{
}

void
init_links(void)
{
}

void
init_tagdec_props(void)
{
}

void
init_tagdef_props(void)
{
}

void
init_al_tagdef_props(void)
{
}

void
init_tokdec_props(void)
{
}

void
init_tokdef_props(void)
{
}
