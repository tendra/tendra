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
$Date: 1998/01/17 15:55:45 $
$Revision: 1.1.1.1 $
$Log: read_fns.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:45  release
 * First version to be checked into rolling release.
 *
 * Revision 1.16  1998/01/09  09:24:58  pwe
 * correct for dg_tags local to tagdef unit
 *
 * Revision 1.15  1997/12/04  19:49:59  pwe
 * ANDF-DE V1.9
 *
 * Revision 1.14  1997/11/04  18:30:02  pwe
 * ANDF-DE V1.8
 *
 * Revision 1.13  1997/08/23  13:30:47  pwe
 * no invert order, and initial ANDF-DE
 *
 * Revision 1.12  1996/10/21  08:54:10  currie
 * long_jump_access
 *
Revision 1.11  1996/06/17 15:30:45  currie
tok signatures

Revision 1.10  1996/06/04 15:40:52  currie
minor bug with repeated defs

Revision 1.9  1996/05/17 10:57:32  currie
signature bug

 * Revision 1.8  1995/10/11  17:09:17  currie
 * transfer token
 *
 * Revision 1.7  1995/09/27  12:39:49  currie
 * Peters PIC code
 *
 * Revision 1.6  1995/09/15  13:28:09  currie
 * add_prefix
 *
 * Revision 1.5  1995/09/11  15:36:20  currie
 * gcc pedantry
 *
 * Revision 1.4  1995/06/22  09:21:10  currie
 * Signatures on tokens
 *
 * Revision 1.3  1995/06/08  14:55:27  currie
 * changes inherited from v3
 *
 * Revision 1.2  1995/05/05  08:12:13  currie
 * initial_value + signtures
 *
 * Revision 1.1  1995/04/06  10:43:34  currie
 * Initial revision
 *
***********************************************************************/




/* this file contains the definitions of some of the functions
   called from decoder.c to set up the in-store representations of TDF.
   It defines those functions which are independent of the actual
   representation, particularly the token substitution and
   unit handling
*/


#include "config.h"
#include "common_types.h"
#include "basicread.h"
#include "toktypes.h"
#include "exp.h"
#include "expmacs.h"
#include "main_reads.h"
#include "tags.h"
#include "flags.h"
#include "me_fns.h"
#include "installglob.h"
#include "readglob.h"
#include "table_fns.h"
#include "flpttypes.h"
#include "flpt.h"
#include "xalloc.h"
#include "shapemacs.h"
#include "read_fns.h"
#include "sortmacs.h"
#include "machine.h"
#include "spec.h"
#include "check.h"
#include "aldefs.h"
#include "externs.h"
#include "diag_fns.h"	/* OLD DIAGS */
#include "dg_fns.h"	/* NEW DIAGS */
#include "messages_r.h"
#include "natmacs.h"


/* Some external declarations  */

extern diag_type_unit f_make_diagtype_unit PROTO_S ((void));	/* OLD DIAGS */
extern int f_make_linkinfo_unit PROTO_S ((void));
extern void start_make_linkinfo_unit PROTO_S ((int, int, int, int ));
extern int machine_toks PROTO_S ((char *));
extern void tidy_initial_values PROTO_S ((void));

/* MACROS */

    /* codes for the types of unit which are understood here */
#define UNKNOWN_UNIT 0
#define TOKDEC_UNIT 1
#define TOKDEF_UNIT 2
#define AL_UNIT 3
#define TAGDEC_UNIT 4
#define TAGDEF_UNIT 5
#define DIAGDEF_UNIT 6		/* OLD DIAGS */
#define DIAGTYPE_UNIT 7		/* OLD DIAGS */
#define LINKINFO_UNIT 8
#define VERSIONS_UNIT 9
#define DGCOMP_UNIT 10		/* NEW DIAGS */

  /* codes for the kinds of linkable variable which are understood here */
#define UNKNOWN_TYPE 0
#define TOK_TYPE 1
#define TAG_TYPE 2
#define AL_TYPE 3
#define DIAGTAG_TYPE 4		/* OLD DIAGS */
#define DGTAG_TYPE 5		/* NEW DIAGS */

/* VARIABLES */
/* All variables are initialised, jmf */

int crt_group_type;	 /* the code for the current group of units */
int crt_links_type;/* the code for the current type of linkable variable                      */
int crt_extern_link_type;/* the code for the current type of externally
                             linked variable */
tdfstring * crt_capsule_groups; /* the identifier for the current group
                                   of units */
int crt_capsule_group_no; /* the number in the group */
int crt_capsule_link_no;  /* the number of linkable variables
                               of the current type */
capsule_link_list crt_capsule_linking;

static int no_of_local_tokens;



/* PROCEDURES */

  /* translates the name of a group of units into  its code */
int group_type
    PROTO_N ( (s) )
    PROTO_T ( char * s )
{
  if (!strcmp(s, "tokdec"))
    return TOKDEC_UNIT;
  if (!strcmp(s, "tokdef"))
    return TOKDEF_UNIT;
  if (!strcmp(s, "aldef"))
    return AL_UNIT;
  if (!strcmp(s, "tagdec"))
    return TAGDEC_UNIT;
  if (!strcmp(s, "tagdef"))
    return TAGDEF_UNIT;
  if (!strcmp(s, "diagdef"))		/* OLD DIAGS */
    return DIAGDEF_UNIT;
  if (!strcmp(s, "diagtype"))		/* OLD DIAGS */
    return DIAGTYPE_UNIT;
  if (!strcmp(s, "linkinfo"))
    return LINKINFO_UNIT;
  if (!strcmp(s, "versions"))
    return VERSIONS_UNIT;
  if (!strcmp(s, "dgcompunit"))		/* NEW DIAGS */
    return DGCOMP_UNIT;
  return UNKNOWN_UNIT;
}

  /* translates the name of a kind of linkable variable into its code */
int links_type
    PROTO_N ( (s) )
    PROTO_T ( char * s )
{
  if (!strcmp(s, "token"))
    return TOK_TYPE;
  if (!strcmp(s, "tag"))
    return TAG_TYPE;
  if (!strcmp(s, "alignment"))
    return AL_TYPE;
  if (!strcmp(s, "diagtag"))		/* OLD DIAGS */
    return DIAGTAG_TYPE;
  if (!strcmp(s, "dgtag"))		/* NEW DIAGS */
    return DGTAG_TYPE;
  return UNKNOWN_TYPE;
}

char * external_to_string
    PROTO_N ( (ext) )
    PROTO_T ( external ext )
{
	char * res;
	int n, i, l;
	tdfstring * t;
	if (ext.isstring) {
		return (char*)ext.ex.id.ints.chars;
	}
	else {
		n = ext.ex.u.number;
		t = ext.ex.u.elems;
		l=n;
		for(i=0; i<n; i++) l += t[i].number * (t[i].size / 8);
		res = (char*)xcalloc(l+1, sizeof(char));
		l = 0;
		for(i=0; i<n; i++) {
			IGNORE(strcpy(res+l, t[i].ints.chars));
			l+= t[i].number * (t[i].size / 8);
			res[l++] = 'U';
		}
		return res;
	}
}


char * make_local_name
    PROTO_Z ()
{
      /* invent a local label identifier */
  char *id;
  char *st = intchars (next_lab ());
  int   l = (int)strlen (st);
  int lpl = (int)strlen(local_prefix);
  id = (char *) xcalloc (l + lpl + 1, sizeof (char));
  IGNORE strcpy(id, local_prefix);
  IGNORE strcpy(&id[lpl], st);
  return id;
}

static void check_tok_sig
    PROTO_N ( (t, sig) )
    PROTO_T ( tok_define * t X string sig )
{
	char * sid = sig.ints.chars;
	int s = (sig.size*sig.number)/8;
	if (t->signature != (char*)0) {
		char * id = t->signature;
			    	int i;
		for(i=0; i<s; i++) {
			if (id[i]!=sid[i]) break;
		}
		if (i!=s || id[s] !=0) {
			   IGNORE fprintf(stderr, "%s\n%s\n", id, sid);
			   failer("Token signatures should be equal");
		}
	}
	else {
		t->signature = sid;
	}
}

  /* all the _apply_token functions follow this pattern */
procprops f_procprops_apply_token
    PROTO_N ( (token_value, token_args) )
    PROTO_T ( token token_value X bitstream token_args )
{
   tokval v;
   v = apply_tok(token_value, token_args, PROCPROPS, (tokval*)0);
   return v.tk_procprops;
}

  /* all the _cond functions follow this pattern */
procprops f_procprops_cond
    PROTO_N ( (control, e1, e2) )
    PROTO_T ( exp control X bitstream e1 X bitstream e2 )
{
  bitstream bs;
  procprops res;
  int n;
  bs = keep_place();

    /* the control must evaluate to a constant */
  if (name(control) != val_tag)
    failer(CONTROL_EXP);
  n = no(control);
  retcell(control);
  if (n==0)
   {
      /* use the second bitstream */
     set_place(e2);
     res = d_procprops();
   }
  else
   {
      /* use the first bitstream */
     set_place(e1);
     res = d_procprops();
   };
 set_place(bs);
 return res;
}

string f_string_apply_token
    PROTO_N ( (token_value, token_args) )
    PROTO_T ( token token_value X bitstream token_args )
{
   tokval v;
   v = apply_tok(token_value, token_args, STRING, (tokval*)0);
   return v.tk_string;
}

  /* all the _cond functions follow this pattern */
string f_string_cond
    PROTO_N ( (control, e1, e2) )
    PROTO_T ( exp control X bitstream e1 X bitstream e2 )
{
  bitstream bs;
  string res;
  int n;
  bs = keep_place();

    /* the control must evaluate to a constant */
  if (name(control) != val_tag)
    failer(CONTROL_EXP);
  n = no(control);
  retcell(control);
  if (n==0)
   {
      /* use the second bitstream */
     set_place(e2);
     res = d_string();
   }
  else
   {
      /* use the first bitstream */
     set_place(e1);
     res = d_string();
   };
 set_place(bs);
 return res;
}


alignment f_alignment_apply_token
    PROTO_N ( (token_value, token_args) )
    PROTO_T ( token token_value X bitstream token_args )
{
   tokval v;
   v = apply_tok(token_value, token_args, ALIGNMENT_SORT, (tokval*)0);
   return v.tk_alignment;
}

  /* all the _cond functions follow this pattern */
alignment f_alignment_cond
    PROTO_N ( (control, e1, e2) )
    PROTO_T ( exp control X bitstream e1 X bitstream e2 )
{
  bitstream bs;
  alignment res;
  int n;
  bs = keep_place();

    /* the control must evaluate to a constant */
  if (name(control) != val_tag)
    failer(CONTROL_EXP);
  n = no(control);
  retcell(control);
  if (n==0)
   {
      /* use the second bitstream */
     set_place(e2);
     res = d_alignment();
   }
  else
   {
      /* use the first bitstream */
     set_place(e1);
     res = d_alignment();
   };
 set_place(bs);
 return res;
}

access f_access_apply_token
    PROTO_N ( (token_value, token_args) )
    PROTO_T ( token token_value X bitstream token_args )
{
   tokval v;
   v = apply_tok(token_value, token_args, ACCESS_SORT, (tokval*)0);
   return v.tk_access;
}


access f_access_cond
    PROTO_N ( (control, e1, e2) )
    PROTO_T ( exp control X bitstream e1 X bitstream e2 )
{
  bitstream bs;
  access res;
  int n;
  bs = keep_place();

    /* the control must evaluate to a constant */
  if (name(control) != val_tag)
    failer(CONTROL_EXP);
  n = no(control);
  retcell(control);
  if (n==0)
   {
      /* use the second bitstream */
     set_place(e2);
     res = d_access();
   }
  else
   {
      /* use the first bitstream */
     set_place(e1);
     res = d_access();
   };
 set_place(bs);
 return res;
}

transfer_mode f_transfer_mode_apply_token
    PROTO_N ( (token_value, token_args) )
    PROTO_T ( token token_value X bitstream token_args )
{
   tokval v;
   v = apply_tok(token_value, token_args, TRANSFER_MODE_SORT, (tokval*)0);
   return v.tk_transfer_mode;
}


transfer_mode f_transfer_mode_cond
    PROTO_N ( (control, e1, e2) )
    PROTO_T ( exp control X bitstream e1 X bitstream e2 )
{
  bitstream bs;
  transfer_mode res;
  int n;
  bs = keep_place();

    /* the control must evaluate to a constant */
  if (name(control) != val_tag)
    failer(CONTROL_EXP);
  n = no(control);
  retcell(control);
  if (n==0)
   {
      /* use the second bitstream */
     set_place(e2);
     res = d_transfer_mode();
   }
  else
   {
      /* use the first bitstream */
     set_place(e1);
     res = d_transfer_mode();
   };
 set_place(bs);
 return res;
}


bitfield_variety f_bfvar_apply_token
    PROTO_N ( (token_value, token_args) )
    PROTO_T ( token token_value X bitstream token_args )
{
   tokval v;
   v = apply_tok(token_value, token_args, BITFIELD_VARIETY, (tokval*)0);
   return v.tk_bitfield_variety;
}

bitfield_variety f_bfvar_cond
    PROTO_N ( (control, e1, e2) )
    PROTO_T ( exp control X bitstream e1 X bitstream e2 )
{
  bitstream bs;
  bitfield_variety res;
  int n;
  bs = keep_place();
  if (name(control) != val_tag)
    failer(CONTROL_EXP);
  n = no(control);
  retcell(control);
  if (n==0)
   {
     set_place(e2);
     res = d_bitfield_variety();
   }
  else
   {
     set_place(e1);
     res = d_bitfield_variety();
   };
 set_place(bs);
 return res;
}

bool f_bool_apply_token
    PROTO_N ( (token_value, token_args) )
    PROTO_T ( token token_value X bitstream token_args )
{
   tokval v;
   v = apply_tok(token_value, token_args, BOOL, (tokval*)0);
   return v.tk_bool;
}

bool f_bool_cond
    PROTO_N ( (control, e1, e2) )
    PROTO_T ( exp control X bitstream e1 X bitstream e2 )
{
  bitstream bs;
  bool res;
  int n;
  bs = keep_place();
  if (name(control) != val_tag)
    failer(CONTROL_EXP);
  n = no(control);
  retcell(control);
  if (n==0)
   {
     set_place(e2);
     res = d_bool();
   }
  else
   {
     set_place(e1);
     res = d_bool();
   };
 set_place(bs);
 return res;
}


  /* locate the index number of the linkable variable */
int find_index
    PROTO_N ( (nm) )
    PROTO_T ( char * nm )
{
  int i;
  for (i=0; i < crt_capsule_linking.number; ++i)
   {
     if (!strcmp((crt_capsule_linking.members[i]).id, nm))
        return i;
   };
  return -1;
}


void start_make_capsule
    PROTO_N ( (prop_names, capsule_linking) )
    PROTO_T ( tdfstring_list prop_names X capsule_link_list capsule_linking )
{
  int i;

  while (capsule_freelist) {
    capsule_frees * cf = capsule_freelist -> next;
    xfree((void*)capsule_freelist->ptr);
    xfree((void*)capsule_freelist);
    capsule_freelist = cf;
  };

  crt_tagdef_unit_no = -1;
  unit_index = 0;
  top_aldef = (aldef *)0;
  doing_aldefs = 0;

  crt_capsule_groups = prop_names.elems;
  crt_capsule_group_no = prop_names.number;

  crt_capsule_linking = capsule_linking;
  crt_capsule_link_no = capsule_linking.number;

  i = find_index("token");
  capsule_no_of_tokens = (i == -1) ? 0 :
               natint((capsule_linking.members[i]).n);

  i = find_index("tag");
  capsule_no_of_tags = (i == -1) ? 0 :
               natint((capsule_linking.members[i]).n);

  i = find_index("alignment");
  capsule_no_of_als = (i == -1) ? 0 :
               natint((capsule_linking.members[i]).n);

  i = find_index("diagtag");		/* OLD DIAGS */
  capsule_no_of_diagtags = (i == -1) ? 0 :
               natint((capsule_linking.members[i]).n);

  i = find_index("dgtag");		/* NEW DIAGS */
  capsule_no_of_dgtags = (i == -1) ? 0 :
               natint((capsule_linking.members[i]).n);

  capsule_toktab = (tok_define*)xcalloc(capsule_no_of_tokens,
                          sizeof(tok_define));
  capsule_tagtab = (dec*)xcalloc(capsule_no_of_tags, sizeof(dec));
  capsule_altab = (aldef*)xcalloc(capsule_no_of_als, sizeof(aldef));
  capsule_diag_tagtab = (diag_tagdef*)xcalloc(capsule_no_of_diagtags,
                                         sizeof(diag_tagdef));	/* OLD DIAGS */
  capsule_dgtab = (dgtag_struct*)xcalloc(capsule_no_of_dgtags,
                                         sizeof(dgtag_struct));	/* NEW DIAGS */

  for (i = 0; i < capsule_no_of_tokens; ++i) {
        /* initialise the table of tokens */
    tok_define * tp = &capsule_toktab[i];
    tp -> tok_special = 0;
    tp -> valpresent = 0;
    tp -> unit_number = crt_tagdef_unit_no;
    tp -> defined = 0;
    tp -> tok_index = i;
    tp -> is_capsule_token = 1;
    tp -> recursive = 0;
  };

  for (i = 0; i < capsule_no_of_tags; ++i) {
        /* initialise the table of tags */
    dec * dp = &capsule_tagtab[i];
    dp -> dec_u.dec_val.dec_outermost = 0;
    dp -> dec_u.dec_val.dec_id = (char *) 0;
    dp -> dec_u.dec_val.extnamed = 0;
    dp -> dec_u.dec_val.diag_info = (diag_global *)0;
    dp -> dec_u.dec_val.have_def = 0;
    dp -> dec_u.dec_val.dec_shape = nilexp;
    dp -> dec_u.dec_val.processed = 0;
    dp -> dec_u.dec_val.isweak = 0;
  };

  for (i = 0; i < capsule_no_of_als; ++i) {
        /* initialise the table of alignment tags */
    aldef * ap = &capsule_altab[i];
    ap -> al.al_n = 0;
  };

  init_capsule_diagtags();	/* OLD DIAGS */
  init_capsule_dgtags();	/* NEW DIAGS */

  return;
}

capsule f_make_capsule
    PROTO_N ( (prop_names, capsule_linking, external_linkage, units) )
    PROTO_T ( tdfstring_list prop_names X capsule_link_list capsule_linking X
	      extern_link_list external_linkage X unit_list units )
{
  UNUSED(prop_names); UNUSED(capsule_linking);
  UNUSED(external_linkage);UNUSED(units);

  translate_capsule();
  return 0;
}

void init_capsule
    PROTO_Z ()
{
  return;
}

capsule_link f_make_capsule_link
    PROTO_N ( (sn, n) )
    PROTO_T ( tdfstring sn X tdfint n )
{
  capsule_link res;
  res.n = n;
  res.id = (char*)sn.ints.chars;
  return res;
}

error_treatment f_errt_apply_token
    PROTO_N ( (token_value, token_args) )
    PROTO_T ( token token_value X bitstream token_args )
{
   tokval v;
   v = apply_tok(token_value, token_args, ERROR_TREATMENT, (tokval*)0);
   return v.tk_error_treatment;
}

error_treatment f_errt_cond
    PROTO_N ( (control, e1, e2) )
    PROTO_T ( exp control X bitstream e1 X bitstream e2 )
{
  bitstream bs;
  error_treatment res;
  int n;
  bs = keep_place();
  if (name(control) != val_tag)
    failer(CONTROL_EXP);
  n = no(control);
  retcell(control);
  if (n==0)
   {
     set_place(e2);
     res = d_error_treatment();
   }
  else
   {
     set_place(e1);
     res = d_error_treatment();
   };
 set_place(bs);
 return res;
}


exp f_exp_apply_token
    PROTO_N ( (token_value, token_args) )
    PROTO_T ( token token_value X bitstream token_args )
{
   tokval v;
   v = apply_tok(token_value, token_args, EXP_S, (tokval*)0);
   return v.tk_exp;
}

exp f_exp_cond
    PROTO_N ( (control, e1, e2) )
    PROTO_T ( exp control X bitstream e1 X bitstream e2 )
{
  bitstream bs;
  exp res;
  int n;
  bs = keep_place();
  if (name(control) != val_tag)
    failer(CONTROL_EXP);
  n = no(control);
  retcell(control);
  if (n==0)
   {
     set_place(e2);
     res = d_exp();
   }
  else
   {
     set_place(e1);
     res = d_exp();
   };
 set_place(bs);
 return res;
}

external f_string_extern
    PROTO_N ( (s) )
    PROTO_T ( tdfstring s )
{
  external e;
  e.isstring = 1;
  e.ex.id = s;
  return e;
}

external f_unique_extern
    PROTO_N ( (u) )
    PROTO_T ( unique u )
{
  external e;
  e.isstring = 0;
  e.ex.u = u;
  return e;
}

external f_chain_extern
    PROTO_N ( (s, i) )
    PROTO_T ( tdfstring s X tdfint i )
{
	UNUSED (s);
	UNUSED (i);
	failer("chain_extern not yet done");
	return f_dummy_external;
}

void init_external
    PROTO_Z ()
{
  return;
}

external f_dummy_external;

floating_variety f_flvar_apply_token
    PROTO_N ( (token_value, token_args) )
    PROTO_T ( token token_value X bitstream token_args )
{
   tokval v;
   v = apply_tok(token_value, token_args, FLOATING_VARIETY, (tokval*)0);
   return v.tk_floating_variety;
}

floating_variety f_flvar_cond
    PROTO_N ( (control, e1, e2) )
    PROTO_T ( exp control X bitstream e1 X bitstream e2 )
{
  bitstream bs;
  floating_variety res;
  int n;
  bs = keep_place();
  if (name(control) != val_tag)
    failer(CONTROL_EXP);
  n = no(control);
  retcell(control);
  if (n==0)
   {
     set_place(e2);
     res = d_floating_variety();
   }
  else
   {
     set_place(e1);
     res = d_floating_variety();
   };
 set_place(bs);
 return res;
}


label f_label_apply_token
    PROTO_N ( (token_value, token_args) )
    PROTO_T ( token token_value X bitstream token_args )
{
   tokval v;
   v = apply_tok(token_value, token_args, LABEL, (tokval*)0);
   return v.tk_label;
}

label f_make_label
    PROTO_N ( (labelno) )
    PROTO_T ( tdfint labelno )
{
  return &unit_labtab[natint(labelno)];
}

void init_label
    PROTO_Z ()
{
  return;
}

label f_dummy_label;

nat f_nat_apply_token
    PROTO_N ( (token_value, token_args) )
    PROTO_T ( token token_value X bitstream token_args )
{
   tokval v;
   v = apply_tok(token_value, token_args, NAT, (tokval*)0);
   return v.tk_nat;
}

nat f_nat_cond
    PROTO_N ( (control, e1, e2) )
    PROTO_T ( exp control X bitstream e1 X bitstream e2 )
{
  bitstream bs;
  nat res;
  int n;
  bs = keep_place();
  if (name(control) != val_tag)
    failer(CONTROL_EXP);
  n = no(control);
  retcell(control);
  if (n==0)
   {
     set_place(e2);
     res = d_nat();
   }
  else
   {
     set_place(e1);
     res = d_nat();
   };
 set_place(bs);
 return res;
}

ntest f_ntest_apply_token
    PROTO_N ( (token_value, token_args) )
    PROTO_T ( token token_value X bitstream token_args )
{
   tokval v;
   v = apply_tok(token_value, token_args, NTEST, (tokval*)0);
   return v.tk_ntest;
}

ntest f_ntest_cond
    PROTO_N ( (control, e1, e2) )
    PROTO_T ( exp control X bitstream e1 X bitstream e2 )
{
  bitstream bs;
  ntest res;
  int n;
  bs = keep_place();
  if (name(control) != val_tag)
    failer(CONTROL_EXP);
  n = no(control);
  retcell(control);
  if (n==0)
   {
     set_place(e2);
     res = d_ntest();
   }
  else
   {
     set_place(e1);
     res = d_ntest();
   };
 set_place(bs);
 return res;
}

rounding_mode f_rounding_mode_apply_token
    PROTO_N ( (token_value, token_args) )
    PROTO_T ( token token_value X bitstream token_args )
{
   tokval v;
   v = apply_tok(token_value, token_args, ROUNDING_MODE, (tokval*)0);
   return v.tk_rounding_mode;
}

rounding_mode f_rounding_mode_cond
    PROTO_N ( (control, e1, e2) )
    PROTO_T ( exp control X bitstream e1 X bitstream e2 )
{
  bitstream bs;
  rounding_mode res;
  int n;
  bs = keep_place();
  if (name(control) != val_tag)
    failer(CONTROL_EXP);
  n = no(control);
  retcell(control);
  if (n==0)
   {
     set_place(e2);
     res = d_rounding_mode();
   }
  else
   {
     set_place(e1);
     res = d_rounding_mode();
   };
 set_place(bs);
 return res;
}

shape f_shape_apply_token
    PROTO_N ( (token_value, token_args) )
    PROTO_T ( token token_value X bitstream token_args )
{
   tokval v;
   v = apply_tok(token_value, token_args, SHAPE, (tokval*)0);
   return v.tk_shape;
}

shape f_shape_cond
    PROTO_N ( (control, e1, e2) )
    PROTO_T ( exp control X bitstream e1 X bitstream e2 )
{
  bitstream bs;
  shape res;
  int n;
  bs = keep_place();
  if (name(control) != val_tag)
    failer(CONTROL_EXP);
  n = no(control);
  retcell(control);
  if (n==0)
   {
     set_place(e2);
     res = d_shape();
   }
  else
   {
     set_place(e1);
     res = d_shape();
   };
 set_place(bs);
 return res;
}

signed_nat f_signed_nat_apply_token
    PROTO_N ( (token_value, token_args) )
    PROTO_T ( token token_value X bitstream token_args )
{
   tokval v;
   v = apply_tok(token_value, token_args, SIGNED_NAT, (tokval*)0);
   return v.tk_signed_nat;
}

signed_nat f_signed_nat_cond
    PROTO_N ( (control, e1, e2) )
    PROTO_T ( exp control X bitstream e1 X bitstream e2 )
{
  bitstream bs;
  signed_nat res;
  int n;
  bs = keep_place();
  if (name(control) != val_tag)
    failer(CONTROL_EXP);
  n = no(control);
  retcell(control);
  if (n==0)
   {
     set_place(e2);
     res = d_signed_nat();
   }
  else
   {
     set_place(e1);
     res = d_signed_nat();
   };
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
sortname f_diag_filename;	/* OLD DIAGS */
sortname f_diag_type;		/* OLD DIAGS */
sortname f_foreign;
sortname f_access;
sortname f_transfer_mode;
sortname f_procprops;
sortname f_string;
sortname f_dg;			/* NEW DIAGS */
sortname f_dg_dim;		/* NEW DIAGS */
sortname f_dg_filename;		/* NEW DIAGS */
sortname f_dg_idname;		/* NEW DIAGS */
sortname f_dg_name;		/* NEW DIAGS */
sortname f_dg_type;		/* NEW DIAGS */

sortname f_foreign_sort
    PROTO_N ( (foreign_name) )
    PROTO_T ( tdfstring foreign_name )
{
  if (!strcmp(foreign_name.ints.chars, "~diag_file"))	/* OLD DIAGS */
    return f_diag_filename;
  if (!strcmp(foreign_name.ints.chars, "~diag_type"))	/* OLD DIAGS */
    return f_diag_type;
  if (!strcmp(foreign_name.ints.chars, "DG"))		/* NEW DIAGS */
    return f_dg;
  if (!strcmp(foreign_name.ints.chars, "DG_DIM"))	/* NEW DIAGS */
    return f_dg_dim;
  if (!strcmp(foreign_name.ints.chars, "DG_FILENAME"))	/* NEW DIAGS */
    return f_dg_filename;
  if (!strcmp(foreign_name.ints.chars, "DG_IDNAME"))	/* NEW DIAGS */
    return f_dg_idname;
  if (!strcmp(foreign_name.ints.chars, "DG_NAME"))	/* NEW DIAGS */
    return f_dg_name;
  if (!strcmp(foreign_name.ints.chars, "DG_TYPE"))	/* NEW DIAGS */
    return f_dg_type;
  return f_foreign;
}

sortname f_token
    PROTO_N ( (result, params) )
    PROTO_T ( sortname result X sortname_list params )
{
   sortname res;
   res.code = TOKEN;
   res.result = result.code;
   res.pars = params;
   return res;
}

sortname f_variety;
void init_sortname
    PROTO_Z ()
{
   f_alignment_sort.code = ALIGNMENT_SORT;
   f_bitfield_variety.code =   BITFIELD_VARIETY;
   f_bool.code =   BOOL;
   f_error_treatment.code =   ERROR_TREATMENT;
   f_exp.code =   EXP_S;
   f_floating_variety.code =   FLOATING_VARIETY;
   f_label.code = LABEL;
   f_nat.code =   NAT;
   f_ntest.code =   NTEST;
   f_rounding_mode.code =   ROUNDING_MODE;
   f_shape.code =   SHAPE;
   f_signed_nat.code =   SIGNED_NAT;
   f_tag.code = TAG;
   f_al_tag.code = AL_TAG;
   f_variety.code = VARIETY;
   f_diag_filename.code = DIAG_FILENAME;	/* OLD DIAGS */
   f_diag_type.code = DIAG_TYPE_SORT;		/* OLD DIAGS */
   f_foreign.code = FOREIGN;
   f_access.code = ACCESS_SORT;
   f_transfer_mode.code = TRANSFER_MODE_SORT;
   f_procprops.code = PROCPROPS;
   f_string.code = STRING;
   f_dg.code = DG_SORT;				/* NEW DIAGS */
   f_dg_dim.code = DG_DIM_SORT;			/* NEW DIAGS */
   f_dg_filename.code = DG_FILENAME_SORT;	/* NEW DIAGS */
   f_dg_idname.code = DG_IDNAME_SORT;		/* NEW DIAGS */
   f_dg_name.code = DG_NAME_SORT;		/* NEW DIAGS */
   f_dg_type.code = DG_TYPE_SORT;		/* NEW DIAGS */

   return;
}

sortname f_dummy_sortname;

tag f_tag_apply_token
    PROTO_N ( (token_value, token_args) )
    PROTO_T ( token token_value X bitstream token_args )
{
   tokval v;
   v = apply_tok(token_value, token_args, TAG, (tokval*)0);
   return v.tk_tag;
}

al_tag f_al_tag_apply_token
    PROTO_N ( (token_value, token_args) )
    PROTO_T ( token token_value X bitstream token_args )
{
   tokval v;
   v = apply_tok(token_value, token_args, AL_TAG, (tokval*)0);
   return v.tk_al_tag;
}

tag f_make_tag
    PROTO_N ( (tagno) )
    PROTO_T ( tdfint tagno )
{
  return get_dec(natint(tagno));
}

void init_tag
    PROTO_Z ()
{
  return;
}

al_tag f_make_al_tag
    PROTO_N ( (tagno) )
    PROTO_T ( tdfint tagno )
{
  return get_aldef(natint(tagno));
}

void init_al_tag
    PROTO_Z ()
{
  return;
}

tag f_dummy_tag;
al_tag f_dummy_al_tag;

void check_sig
    PROTO_N ( (tg, sig) )
    PROTO_T ( tag tg X string sig )
{
	char * sid = sig.ints.chars;
	int s = (sig.size*sig.number)/8;
	if (tg->dec_u.dec_val.has_signature) {
		char * id = tg->dec_u.dec_val.dec_id;
	    	int i;
		for(i=0; i<s; i++) {
			if (id[i]!=sid[i]) break;
		}
		if (i!=s || id[s] !=0) {
			   IGNORE fprintf(stderr, "%s\n%s\n", id, sid);
			   failer("Signatures should be equal");
		}
	}
	else {
		tg->dec_u.dec_val.dec_id = sid;
		tg->dec_u.dec_val.has_signature = 1;
	}
}





tagdec f_make_id_tagdec
    PROTO_N ( (t_intro, acc, sig, x) )
    PROTO_T ( tdfint t_intro X access_option acc X string_option sig X shape x )
{
  tagdec res;
  res.tg = get_dec(natint(t_intro));
  res.sha = x;
  res.acc = acc;
  res.is_variable = 0;
  res.is_common = 0;
  res.tg -> dec_u.dec_val.is_common = 0;
  if (sig.present) check_sig(res.tg, sig.val);
  return res;
}

tagdec f_make_var_tagdec
    PROTO_N ( (t_intro, acc, sig, x) )
    PROTO_T ( tdfint t_intro X access_option acc X string_option sig X shape x )
{
  tagdec res;
  res.tg = get_dec(natint(t_intro));
  res.sha = x;
  res.acc = acc;
  res.is_variable = 1;
  res.is_common = 0;
  res.tg -> dec_u.dec_val.is_common = 0;
  if (sig.present) check_sig(res.tg, sig.val);
  return res;
}

tagdec f_common_tagdec
    PROTO_N ( (t_intro, acc, sig, x) )
    PROTO_T ( tdfint t_intro X access_option acc X string_option sig X shape x )
{
  tagdec res;
  res.tg = get_dec(natint(t_intro));
  res.sha = x;
  res.acc = acc;
  res.is_variable = 1;
  res.is_common = 1;
  res.tg -> dec_u.dec_val.is_common = 0;
  if (sig.present) check_sig(res.tg, sig.val);
  return res;
}

void init_tagdec
    PROTO_Z ()
{
  return;
}

tagdec f_dummy_tagdec;


void start_make_id_tagdef
    PROTO_N ( (t) )
    PROTO_T ( tdfint t )
{
  UNUSED(t);
  rep_make_proc = 0;
  return;
}

tagdef f_make_id_tagdef
    PROTO_N ( (t, sig, e) )
    PROTO_T ( tdfint t X string_option sig X exp e )
{
  dec * dp = get_dec(natint(t));
  tagdef res;
  res.tg = dp;
  if (dp -> dec_u.dec_val.processed ||
        son(dp -> dec_u.dec_val.dec_exp) != nilexp)
    res.def = nilexp; /* set to nilexp if already output */
  else
    res.def = e;
  res.var = 0;
  res.is_common = 0;
  if (sig.present) check_sig(dp, sig.val);
  rep_make_proc = 1;
  return res;
}

void start_make_var_tagdef
    PROTO_N ( (t) )
    PROTO_T ( tdfint t )
{
  UNUSED(t);

  return;
}

tagdef f_make_var_tagdef
    PROTO_N ( (t, opt_access, sig, e) )
    PROTO_T ( tdfint t X access_option opt_access X string_option sig X exp e )
{
  dec * dp = get_dec(natint(t));
  tagdef res;
  UNUSED(opt_access);
  res.tg = dp;
  if (dp -> dec_u.dec_val.processed ||
        son(dp -> dec_u.dec_val.dec_exp) != nilexp)
    res.def = nilexp; /* set to nilexp if already output */
  else
    res.def = e;
  res.var = 1;
  res.is_common = 0;
  if (sig.present) check_sig(dp, sig.val);
  return res;
}

void start_common_tagdef
    PROTO_N ( (t) )
    PROTO_T ( tdfint t )
{
  UNUSED(t);
  return;
}

tagdef f_common_tagdef
    PROTO_N ( (t, opt_access, sig, e) )
    PROTO_T ( tdfint t X access_option opt_access X string_option sig X exp e )
{
  dec * dp = get_dec(natint(t));
  tagdef res;
  UNUSED(opt_access);
  res.tg = dp;
  res.def = e;
  res.var = 1;
  res.is_common = 1;
  if (sig.present) check_sig(dp, sig.val);
  return res;
}

void init_tagdef
    PROTO_Z ()
{
  return;
}

void init_al_tagdef
    PROTO_Z ()
{
  return;
}

tagdef f_dummy_tagdef;
al_tagdef f_dummy_al_tagdef;

char* add_prefix
    PROTO_N ( (nm) )
    PROTO_T ( char * nm )
{
  char * id;
  int idl = (int)strlen(nm);
  int   j;
  int npl = (int)strlen(name_prefix);
  if (npl == 0) return nm;
  id = (char *) xcalloc ( (idl + npl + 1), sizeof (char));
  id[idl + npl] = 0;
  for (j = npl; j < (idl+npl); ++j)
    id[j] = nm[j-npl];
  for (j = 0; j < npl; ++j)
    id[j] = name_prefix[j];
  return id;
}

tagextern f_make_tagextern
    PROTO_N ( (internal, ext) )
    PROTO_T ( tdfint internal X external ext )
{
  dec * dp = &capsule_tagtab[natint(internal)];
  char *nm = external_to_string(ext);
  char * id = add_prefix(nm);
  dp -> dec_u.dec_val.dec_id = id;
  dp -> dec_u.dec_val.dec_outermost = 1;
  dp -> dec_u.dec_val.extnamed = 1;

  return 0;
}

taglink f_make_taglink
    PROTO_N ( (internal, ext) )
    PROTO_T ( tdfint internal X tdfint ext )
{
  unit_ind_tags[natint(internal)] =
      &capsule_tagtab[natint(ext)];
  return 0;
}


allink f_make_allink
    PROTO_N ( (internal, ext) )
    PROTO_T ( tdfint internal X tdfint ext )
{
  unit_ind_als[natint(internal)] =
      &capsule_altab[natint(ext)];
  return 0;
}


tokdec f_make_tokdec
    PROTO_N ( (tok, sig, s) )
    PROTO_T ( tdfint tok X string_option sig X sortname s )
{
  tok_define * tok_d = get_tok(natint(tok));
  if (sig.present) check_tok_sig(tok_d, sig.val);
  UNUSED(s);
  return 0;
}

void init_tokdec
    PROTO_Z ()
{
  return;
}

tokdec f_dummy_tokdec;

tokdef f_make_tokdef
    PROTO_N ( (tokn, sig,def) )
    PROTO_T ( tdfint tokn X string_option sig X bitstream def )
{
  sortname result_sort;
  tokformals_list params;
  place old_place;
  tok_define * tok = get_tok(natint(tokn));
  if (sig.present) check_tok_sig(tok, sig.val);
  old_place = keep_place();
  set_place(def);
  IGNORE getcode(1);
  result_sort = d_sortname();
  params = d_tokformals_list();
  tok -> tdsort = result_sort;
  tok -> params = params;
  tok -> tdplace = keep_place();
  tok -> defined = 1;
  tok->tok_context = (context*)0;

    /* record the tables which are current so that they can be
       used when the token is applied */
  tok -> my_labtab = unit_labtab;
  tok -> my_tagtab = unit_ind_tags;
  tok -> my_toktab = unit_ind_tokens;
  tok -> my_altab = unit_ind_als;
  tok -> my_diagtab = unit_ind_diagtags;	/* OLD DIAGS */
  tok -> my_dgtab = unit_ind_dgtags;		/* NEW DIAGS */
  if (params.number == 0)
    tok -> re_evaluate = 0;
  else
    tok -> re_evaluate = 1;

  set_place(old_place);
  return 0;
}

token f_use_tokdef
    PROTO_N ( (def) )
    PROTO_T ( bitstream def )
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
  tok -> tok_special = 0;
  tok -> valpresent = 0;
  tok -> unit_number = crt_tagdef_unit_no;
  tok -> defined = 0;
  tok -> is_capsule_token = 0;
  tok -> recursive = 0;
  tok -> tdsort = result_sort;
  tok -> params = params;
  tok -> tdplace = keep_place();
  tok -> defined = 1;
  tok->tok_context = crt_context;

    /* record the tables which are current so that they can be
       used when the token is applied */
  tok -> my_labtab = unit_labtab;
  tok -> my_tagtab = unit_ind_tags;
  tok -> my_toktab = unit_ind_tokens;
  tok -> my_altab = unit_ind_als;
  tok -> my_diagtab = unit_ind_diagtags;	/* OLD DIAGS */
  tok -> my_dgtab = unit_ind_dgtags;		/* NEW DIAGS */

  if (params.number == 0)
    tok -> re_evaluate = 0;
  else
    tok -> re_evaluate = 1;

  set_place(old_place);
  return tok;
}


void init_tokdef
    PROTO_Z ()
{
  return;
}

tokdef f_dummy_tokdef;

token f_token_apply_token
    PROTO_N ( (token_value, token_args) )
    PROTO_T ( token token_value X bitstream token_args )
{
   tokval v;
   v = apply_tok(token_value, token_args, TOKEN, (tokval*)0);
   return v.tk_token;
}

token f_make_tok
    PROTO_N ( (tokno) )
    PROTO_T ( tdfint tokno )
{
  return get_tok(natint(tokno));
}

void init_token
    PROTO_Z ()
{
  return;
}

token f_dummy_token;

token_defn f_token_definition
    PROTO_N ( (result_sort, tok_params) )
    PROTO_T ( sortname result_sort X tokformals_list tok_params )
{
  UNUSED (result_sort);
  UNUSED (tok_params);
  failer ("dummy");
  return f_dummy_token_defn;
}

void init_token_defn
    PROTO_Z ()
{
  return;
}

token_defn f_dummy_token_defn;

tokextern f_make_tokextern
    PROTO_N ( (internal, ext) )
    PROTO_T ( tdfint internal X external ext )
{
  tok_define * t = &capsule_toktab[natint(internal)];
  char * s = external_to_string(ext);
  t -> tok_name = s;

  if (machine_toks(s))  /* determines special tokens specific
			   to each machine */
    t -> tok_special = 1;


  if (replace_arith_type)  {
    if (!strcmp(s, "~arith_type"))
      t -> tok_special = 1;
    if (!strcmp(s, "~promote"))
      t -> tok_special = 1;
    if (!strcmp(s, "~sign_promote"))
      t -> tok_special = 1;
    if (!strcmp(s, "~convert"))
      t -> tok_special = 1;
  };
  if (do_alloca && !strcmp(s, "~alloca"))
    t -> tok_special = 1;
  return 0;
}

alextern f_make_alextern
    PROTO_N ( (internal, ext) )
    PROTO_T ( tdfint internal X external ext )
{
  UNUSED(internal); UNUSED(ext);
  return 0;
}


tokformals f_make_tokformals
    PROTO_N ( (sn, tk) )
    PROTO_T ( sortname sn X tdfint tk )
{
  tokformals res;
  res.sn = sn;
  res.tk = natint(tk);
  return res;
}

void init_tokformals
    PROTO_Z ()
{
  return;
}

toklink f_make_toklink
    PROTO_N ( (internal, ext) )
    PROTO_T ( tdfint internal X tdfint ext )
{
  unit_ind_tokens[natint(internal)] =
      &capsule_toktab[natint(ext)];
  return 0;
}

link f_make_link
    PROTO_N ( (internal, ext) )
    PROTO_T ( tdfint internal X tdfint ext )
{
  switch (crt_links_type)
   {
     case TOK_TYPE:
       IGNORE f_make_toklink(internal, ext);
       return 0;
     case TAG_TYPE:
       IGNORE f_make_taglink(internal, ext);
       return 0;
     case AL_TYPE:
       IGNORE f_make_allink(internal, ext);
       return 0;
     case DIAGTAG_TYPE:		/* OLD DIAGS */
       IGNORE f_make_diagtaglink(internal, ext);
       return 0;
     case DGTAG_TYPE:		/* NEW DIAGS */
       IGNORE f_make_dglink(internal, ext);
       return 0;
     default:
       failer(VARIABLE_TYPE);
       return 0;
   };
}

unique f_make_unique
    PROTO_N ( (text) )
    PROTO_T ( tdfstring_list text )
{
  return text;
}

void init_unique
    PROTO_Z ()
{
   return;
}


variety f_var_apply_token
    PROTO_N ( (token_value, token_args) )
    PROTO_T ( token token_value X bitstream token_args )
{
   tokval v;
   v = apply_tok(token_value, token_args, VARIETY, (tokval*)0);
   return v.tk_variety;
}

variety f_var_cond
    PROTO_N ( (control, e1, e2) )
    PROTO_T ( exp control X bitstream e1 X bitstream e2 )
{
  bitstream bs;
  variety res;
  int n;
  bs = keep_place();
  if (name(control) != val_tag)
    failer(CONTROL_EXP);
  n = no(control);
  retcell(control);
  if (n==0)
   {
     set_place(e2);
     res = d_variety();
   }
  else
   {
     set_place(e1);
     res = d_variety();
   };
 set_place(bs);
 return res;
}


void start_make_tokdec_unit
    PROTO_N ( (no_of_tokens, no_of_tags, no_of_als, no_of_diagtags, no_of_dgtags) )
    PROTO_T ( int no_of_tokens X int no_of_tags X int no_of_als X int no_of_diagtags X int no_of_dgtags )
{
  int i;

  unit_no_of_tokens = no_of_tokens;
  unit_ind_tokens = (tok_define * *)xcalloc(unit_no_of_tokens,
                    sizeof(tok_define *));
  for (i = 0; i < unit_no_of_tokens; ++i)
    unit_ind_tokens[i] = (tok_define*)0;

  unit_no_of_tags = no_of_tags;
  unit_ind_tags = (dec * *)xcalloc(unit_no_of_tags,
                    sizeof(dec *));
  for (i = 0; i < unit_no_of_tags; ++i)
    unit_ind_tags[i] = (dec*)0;

  unit_no_of_als = no_of_als;
  unit_ind_als = (aldef * *)xcalloc(unit_no_of_als,
                    sizeof(aldef *));
  for (i = 0; i < unit_no_of_als; ++i)
    unit_ind_als[i] = (aldef*)0;

  unit_no_of_diagtags = no_of_diagtags;		/* OLD DIAGS */
  unit_ind_diagtags = (diag_tagdef * *)xcalloc(unit_no_of_diagtags,
                    sizeof(diag_tagdef *));
  for (i = 0; i < unit_no_of_diagtags; ++i)
    unit_ind_diagtags[i] = (diag_tagdef *)0;

  unit_no_of_dgtags = no_of_dgtags;		/* NEW DIAGS */
  unit_ind_dgtags = (dgtag_struct * *)xcalloc(unit_no_of_dgtags,
                    sizeof(dgtag_struct *));
  for (i = 0; i < unit_no_of_dgtags; ++i)
    unit_ind_dgtags[i] = (dgtag_struct *)0;

  return;
}

tokdec_unit f_make_tokdec_unit
    PROTO_Z ()
{
  int i;
  int j = 0;
  for (i = 0; i < unit_no_of_tokens; ++i)
   {
    if (unit_ind_tokens[i] == (tok_define*)0)
      unit_ind_tokens[i] = &unit_toktab[j++];
   };
  start_bytestream();
  IGNORE d_tokdec_list();
  end_bytestream();
  return 0;
}

void start_make_tokdef_unit
    PROTO_N ( (no_of_tokens, no_of_tags, no_of_als, no_of_diagtags, no_of_dgtags) )
    PROTO_T ( int no_of_tokens X int no_of_tags X int no_of_als X int no_of_diagtags X int no_of_dgtags )
{
  int i;

  unit_no_of_tokens = no_of_tokens;
  unit_ind_tokens = (tok_define * *)xcalloc(unit_no_of_tokens,
                    sizeof(tok_define *));
  for (i = 0; i < unit_no_of_tokens; ++i)
    unit_ind_tokens[i] = (tok_define*)0;

  unit_no_of_tags = no_of_tags;
  unit_ind_tags = (dec * *)xcalloc(unit_no_of_tags,
                    sizeof(dec *));
  for (i = 0; i < unit_no_of_tags; ++i)
    unit_ind_tags[i] = (dec*)0;

  unit_no_of_als = no_of_als;
  unit_ind_als = (aldef * *)xcalloc(unit_no_of_als,
                    sizeof(aldef *));
  for (i = 0; i < unit_no_of_als; ++i)
    unit_ind_als[i] = (aldef*)0;

  unit_no_of_diagtags = no_of_diagtags;		/* OLD DIAGS */
  unit_ind_diagtags = (diag_tagdef * *)xcalloc(unit_no_of_diagtags,
                    sizeof(diag_tagdef *));
  for (i = 0; i < unit_no_of_diagtags; ++i)
    unit_ind_diagtags[i] = (diag_tagdef *)0;

  unit_no_of_dgtags = no_of_dgtags;		/* NEW DIAGS */
  unit_ind_dgtags = (dgtag_struct * *)xcalloc(unit_no_of_dgtags,
                    sizeof(dgtag_struct *));
  for (i = 0; i < unit_no_of_dgtags; ++i)
    unit_ind_dgtags[i] = (dgtag_struct *)0;

  return;
}

tokdef_unit f_make_tokdef_unit
    PROTO_Z ()
{
  int i;
  int j = 0;
  int no_of_labels;
  for (i = 0; i < unit_no_of_tokens; ++i)
   {
    if (unit_ind_tokens[i] == (tok_define*)0)
      unit_ind_tokens[i] = &unit_toktab[j++];
   };
  j = 0;
  for (i = 0; i < unit_no_of_tags; ++i)
   {
    if (unit_ind_tags[i] == (dec*)0)
      unit_ind_tags[i] = &unit_tagtab[j++];
   };
  j = 0;
  for (i = 0; i < unit_no_of_als; ++i)
   {
    if (unit_ind_als[i] == (aldef*)0)
      unit_ind_als[i] = &unit_altab[j++];
   };
  j = 0;
  for (i = 0; i < unit_no_of_dgtags; ++i)	/* NEW DIAGS */
   {
    if (unit_ind_dgtags[i] == (dgtag_struct *)0)
      unit_ind_dgtags[i] = &unit_dgtagtab[j++];
   };
  start_bytestream();
  no_of_labels = small_dtdfint();
  unit_no_of_labels = no_of_labels;
  unit_labtab = (exp*)xcalloc(unit_no_of_labels, sizeof(exp));
  IGNORE d_tokdef_list();
  end_bytestream();

  /* tables must be kept for use during token application */

  return 0;
}

void start_make_tagdec_unit
    PROTO_N ( (no_of_tokens, no_of_tags, no_of_als, no_of_diagtags, no_of_dgtags) )
    PROTO_T ( int no_of_tokens X int no_of_tags X int no_of_als X int no_of_diagtags X int no_of_dgtags )
{
  int i;

  unit_no_of_tokens = no_of_tokens;
  unit_ind_tokens = (tok_define * *)xcalloc(unit_no_of_tokens,
                    sizeof(tok_define *));
  for (i = 0; i < unit_no_of_tokens; ++i)
    unit_ind_tokens[i] = (tok_define*)0;

  unit_no_of_tags = no_of_tags;
  unit_ind_tags = (dec * *)xcalloc(unit_no_of_tags,
                    sizeof(dec *));
  for (i = 0; i < unit_no_of_tags; ++i)
    unit_ind_tags[i] = (dec*)0;

  unit_no_of_als = no_of_als;
  unit_ind_als = (aldef * *)xcalloc(unit_no_of_als,
                    sizeof(aldef *));
  for (i = 0; i < unit_no_of_als; ++i)
    unit_ind_als[i] = (aldef*)0;

  unit_no_of_diagtags = no_of_diagtags;		/* OLD DIAGS */
  unit_ind_diagtags = (diag_tagdef * *)xcalloc(unit_no_of_diagtags,
                    sizeof(diag_tagdef *));
  for (i = 0; i < unit_no_of_diagtags; ++i)
    unit_ind_diagtags[i] = (diag_tagdef *)0;

  unit_no_of_dgtags = no_of_dgtags;		/* NEW DIAGS */
  unit_ind_dgtags = (dgtag_struct * *)xcalloc(unit_no_of_dgtags,
                    sizeof(dgtag_struct *));
  for (i = 0; i < unit_no_of_dgtags; ++i)
    unit_ind_dgtags[i] = (dgtag_struct *)0;

  return;
}

tagdec_unit f_make_tagdec_unit
    PROTO_Z ()
{
  int i;
  int j = 0;
  int no_of_labels;
  for (i = 0; i < unit_no_of_tokens; ++i)
   {
    if (unit_ind_tokens[i] == (tok_define*)0)
      unit_ind_tokens[i] = &unit_toktab[j++];
   };
  j = 0;
  for (i = 0; i < unit_no_of_tags; ++i)
   {
    if (unit_ind_tags[i] == (dec*)0)
      unit_ind_tags[i] = &unit_tagtab[j++];
   };
  j = 0;
  for (i = 0; i < unit_no_of_als; ++i)
   {
    if (unit_ind_als[i] == (aldef*)0)
      unit_ind_als[i] = &unit_altab[j++];
   };
  j = 0;
  for (i = 0; i < unit_no_of_dgtags; ++i)	/* NEW DIAGS */
   {
    if (unit_ind_dgtags[i] == (dgtag_struct *)0)
      unit_ind_dgtags[i] = &unit_dgtagtab[j++];
   };
  start_bytestream();
  no_of_labels = small_dtdfint();
  unit_no_of_labels = no_of_labels;
  unit_labtab = (exp*)xcalloc(unit_no_of_labels, sizeof(exp));
  IGNORE d_tagdec_list();
  end_bytestream();

  xfree((void*)unit_ind_tokens);
  xfree((void*)unit_ind_tags);
  xfree((void*)unit_ind_als);
  xfree((void*)unit_labtab);

  xfree((void*)unit_toktab);

  return 0;
}

void start_make_versions_unit
    PROTO_N ( (no_of_tokens, no_of_tags, no_of_als, no_of_diagtags, no_of_dgtags) )
    PROTO_T ( int no_of_tokens X int no_of_tags X int no_of_als X int no_of_diagtags X int no_of_dgtags )
{
  int i;

  unit_no_of_tokens = no_of_tokens;
  unit_ind_tokens = (tok_define * *)xcalloc(unit_no_of_tokens,
                    sizeof(tok_define *));
  for (i = 0; i < unit_no_of_tokens; ++i)
    unit_ind_tokens[i] = (tok_define*)0;

  unit_no_of_tags = no_of_tags;
  unit_ind_tags = (dec * *)xcalloc(unit_no_of_tags,
                    sizeof(dec *));
  for (i = 0; i < unit_no_of_tags; ++i)
    unit_ind_tags[i] = (dec*)0;

  unit_no_of_als = no_of_als;
  unit_ind_als = (aldef * *)xcalloc(unit_no_of_als,
                    sizeof(aldef *));
  for (i = 0; i < unit_no_of_als; ++i)
    unit_ind_als[i] = (aldef*)0;

  unit_no_of_diagtags = no_of_diagtags;		/* OLD DIAGS */
  unit_ind_diagtags = (diag_tagdef * *)xcalloc(unit_no_of_diagtags,
                    sizeof(diag_tagdef *));
  for (i = 0; i < unit_no_of_diagtags; ++i)
    unit_ind_diagtags[i] = (diag_tagdef *)0;

  unit_no_of_dgtags = no_of_dgtags;		/* NEW DIAGS */
  unit_ind_dgtags = (dgtag_struct * *)xcalloc(unit_no_of_dgtags,
                    sizeof(dgtag_struct *));
  for (i = 0; i < unit_no_of_dgtags; ++i)
    unit_ind_dgtags[i] = (dgtag_struct *)0;

  return;
}

version_props f_make_versions_unit
    PROTO_Z ()
{
  int i;
  int j = 0;
  for (i = 0; i < unit_no_of_tokens; ++i)
   {
    if (unit_ind_tokens[i] == (tok_define*)0)
      unit_ind_tokens[i] = &unit_toktab[j++];
   };
  j = 0;
  for (i = 0; i < unit_no_of_tags; ++i)
   {
    if (unit_ind_tags[i] == (dec*)0)
      unit_ind_tags[i] = &unit_tagtab[j++];
   };
  j = 0;
  for (i = 0; i < unit_no_of_als; ++i)
   {
    if (unit_ind_als[i] == (aldef*)0)
      unit_ind_als[i] = &unit_altab[j++];
   };
  start_bytestream();
  IGNORE d_version_list();
  end_bytestream();

  xfree((void*)unit_ind_tokens);
  xfree((void*)unit_ind_tags);
  xfree((void*)unit_ind_als);

  xfree((void*)unit_toktab);
  xfree((void*)unit_tagtab);

  return 0;
}

void start_make_tagdef_unit
    PROTO_N ( (no_of_tokens, no_of_tags, no_of_als, no_of_diagtags, no_of_dgtags) )
    PROTO_T ( int no_of_tokens X int no_of_tags X int no_of_als X int no_of_diagtags X int no_of_dgtags )
{
  int i;

  if (separate_units)
   {
    ++crt_tagdef_unit_no;
    set_large_alloc();
   };

  unit_no_of_tokens = no_of_tokens;
  unit_ind_tokens = (tok_define * *)xcalloc(unit_no_of_tokens,
                    sizeof(tok_define *));
  for (i = 0; i < unit_no_of_tokens; ++i)
    unit_ind_tokens[i] = (tok_define*)0;

  unit_no_of_tags = no_of_tags;
  unit_ind_tags = (dec * *)xcalloc(unit_no_of_tags,
                    sizeof(dec *));
  for (i = 0; i < unit_no_of_tags; ++i)
    unit_ind_tags[i] = (dec*)0;

  unit_no_of_als = no_of_als;
  unit_ind_als = (aldef * *)xcalloc(unit_no_of_als,
                    sizeof(aldef *));
  for (i = 0; i < unit_no_of_als; ++i)
    unit_ind_als[i] = (aldef*)0;

  unit_no_of_diagtags = no_of_diagtags;		/* OLD DIAGS */
  unit_ind_diagtags = (diag_tagdef * *)xcalloc(unit_no_of_diagtags,
                    sizeof(diag_tagdef *));
  for (i = 0; i < unit_no_of_diagtags; ++i)
    unit_ind_diagtags[i] = (diag_tagdef *)0;

  unit_no_of_dgtags = no_of_dgtags;		/* NEW DIAGS */
  unit_ind_dgtags = (dgtag_struct * *)xcalloc(unit_no_of_dgtags,
                    sizeof(dgtag_struct *));
  for (i = 0; i < unit_no_of_dgtags; ++i)
    unit_ind_dgtags[i] = (dgtag_struct *)0;

  return;
}




tagdef_unit f_make_tagdef_unit
    PROTO_Z ()
{
  int i;
  int j = 0;
  int no_of_labels;
  for (i = 0; i < unit_no_of_tokens; ++i)
   {
    if (unit_ind_tokens[i] == (tok_define*)0)
      unit_ind_tokens[i] = &unit_toktab[j++];
   };
  j = 0;
  for (i = 0; i < unit_no_of_tags; ++i)
   {
    if (unit_ind_tags[i] == (dec*)0)
      unit_ind_tags[i] = &unit_tagtab[j++];
   };
  j = 0;
  for (i = 0; i < unit_no_of_als; ++i)
   {
    if (unit_ind_als[i] == (aldef*)0)
      unit_ind_als[i] = &unit_altab[j++];
   };
  j = 0;
  for (i = 0; i < unit_no_of_dgtags; ++i)	/* NEW DIAGS */
   {
    if (unit_ind_dgtags[i] == (dgtag_struct *)0)
      unit_ind_dgtags[i] = &unit_dgtagtab[j++];
   };
  start_bytestream();
  no_of_labels = small_dtdfint();
  unit_no_of_labels = no_of_labels;
  unit_labtab = (exp*)xcalloc(unit_no_of_labels, sizeof(exp));
  IGNORE d_tagdef_list();
  tidy_initial_values();
  translate_unit();
  end_bytestream();

  xfree((void*)unit_ind_tokens);
  xfree((void*)unit_ind_tags);
  xfree((void*)unit_ind_als);
  xfree((void*)unit_labtab);

  xfree((void*)unit_toktab);
  xfree((void*)unit_tagtab);

  return 0;
}

void start_make_aldef_unit
    PROTO_N ( (no_of_tokens, no_of_tags, no_of_als, no_of_diagtags, no_of_dgtags) )
    PROTO_T ( int no_of_tokens X int no_of_tags X int no_of_als X int no_of_diagtags X int no_of_dgtags )
{
  int i;

  unit_no_of_tokens = no_of_tokens;
  unit_ind_tokens = (tok_define * *)xcalloc(unit_no_of_tokens,
                    sizeof(tok_define *));
  for (i = 0; i < unit_no_of_tokens; ++i)
    unit_ind_tokens[i] = (tok_define*)0;

  unit_no_of_tags = no_of_tags;
  unit_ind_tags = (dec * *)xcalloc(unit_no_of_tags,
                    sizeof(dec *));
  for (i = 0; i < unit_no_of_tags; ++i)
    unit_ind_tags[i] = (dec*)0;

  unit_no_of_als = no_of_als;
  unit_ind_als = (aldef * *)xcalloc(unit_no_of_als,
                    sizeof(aldef *));
  for (i = 0; i < unit_no_of_als; ++i)
    unit_ind_als[i] = (aldef*)0;

  unit_no_of_diagtags = no_of_diagtags;		/* OLD DIAGS */
  unit_ind_diagtags = (diag_tagdef * *)xcalloc(unit_no_of_diagtags,
                    sizeof(diag_tagdef *));
  for (i = 0; i < unit_no_of_diagtags; ++i)
    unit_ind_diagtags[i] = (diag_tagdef *)0;

  unit_no_of_dgtags = no_of_dgtags;		/* NEW DIAGS */
  unit_ind_dgtags = (dgtag_struct * *)xcalloc(unit_no_of_dgtags,
                    sizeof(dgtag_struct *));
  for (i = 0; i < unit_no_of_dgtags; ++i)
    unit_ind_dgtags[i] = (dgtag_struct *)0;

  return;
}

aldef_unit f_make_aldef_unit
    PROTO_Z ()
{
  int i;
  int j = 0;
  int no_of_labels;
  for (i = 0; i < unit_no_of_tokens; ++i)
   {
    if (unit_ind_tokens[i] == (tok_define*)0)
      unit_ind_tokens[i] = &unit_toktab[j++];
   };
  j = 0;
  for (i = 0; i < unit_no_of_als; ++i)
   {
    if (unit_ind_als[i] == (aldef*)0)
      unit_ind_als[i] = &unit_altab[j++];
   };
  start_bytestream();
  no_of_labels = small_dtdfint();
  unit_no_of_labels = no_of_labels;
  unit_labtab = (exp*)xcalloc(unit_no_of_labels, sizeof(exp));
  IGNORE d_al_tagdef_list();
  end_bytestream();

  xfree((void*)unit_ind_tokens);
  xfree((void*)unit_ind_tags);
  xfree((void*)unit_ind_als);
  xfree((void*)unit_labtab);

  xfree((void*)unit_toktab);
  xfree((void*)unit_tagtab);

  return 0;
}

void start_make_unit
    PROTO_N ( (lvl) )
    PROTO_T ( tdfint_list lvl )
{
  int w;
  int ntok = 0;
  int ntag = 0;
  int nal = 0;
  int ndiagtype = 0;	/* OLD DIAGS */
  int ndgtag = 0;	/* NEW DIAGS */

  ++unit_index;

  if (lvl.number != 0) {
    w = find_index("token");
    ntok = (w == -1) ? 0 : natint(lvl.members[w]);
    w = find_index("tag");
    ntag = (w == -1) ? 0 : natint(lvl.members[w]);
    w = find_index("alignment");
    nal = (w == -1) ? 0 : natint(lvl.members[w]);
    w = find_index("diagtag");		/* OLD DIAGS */
    ndiagtype = (w == -1) ? 0 : natint(lvl.members[w]);
    w = find_index("dgtag");		/* NEW DIAGS */
    ndgtag = (w == -1) ? 0 : natint(lvl.members[w]);
  };

  switch(crt_group_type)
   {
     case TOKDEC_UNIT:
              start_make_tokdec_unit(ntok, ntag, nal, ndiagtype, ndgtag);
              return;
     case TOKDEF_UNIT:
              start_make_tokdef_unit(ntok, ntag, nal, ndiagtype, ndgtag);
              return;
     case AL_UNIT:
	      doing_aldefs = 1;
              start_make_aldef_unit(ntok, ntag, nal, ndiagtype, ndgtag);
              return;
     case TAGDEC_UNIT:
	      if (doing_aldefs) {
                process_aldefs();
	        doing_aldefs = 0;
	      };
              start_make_tagdec_unit(ntok, ntag, nal, ndiagtype, ndgtag);
              return;
     case TAGDEF_UNIT:
              start_make_tagdef_unit(ntok, ntag, nal, ndiagtype, ndgtag);
              return;
     case DIAGDEF_UNIT:		/* OLD DIAGS */
              start_make_diagdef_unit(ntok, ntag, nal, ndiagtype);
              return;
     case DIAGTYPE_UNIT:	/* OLD DIAGS */
	      if (doing_aldefs) {
                process_aldefs();
	        doing_aldefs = 0;
	      };
              start_make_diagtype_unit(ntok, ntag, nal, ndiagtype);
              return;
     case LINKINFO_UNIT:
              start_make_linkinfo_unit(ntok, ntag, nal, 0 /* discarded */);
              return;
     case VERSIONS_UNIT:
              start_make_versions_unit(ntok, ntag, nal, ndiagtype, ndgtag);
              return;
     case DGCOMP_UNIT:	/* NEW DIAGS */
	      if (doing_aldefs) {
                process_aldefs();
	        doing_aldefs = 0;
	      };
              start_make_dg_comp_unit(ntok, ntag, nal, ndgtag);
              return;
     default:
              return;
   };
}

unit f_make_unit
    PROTO_N ( (lvl, lks, prs) )
    PROTO_T ( tdfint_list lvl X links_list lks X bytestream prs )
{
  UNUSED(lvl); UNUSED(lks); UNUSED(prs);
  switch(crt_group_type)
   {
     case TOKDEC_UNIT:
              IGNORE f_make_tokdec_unit();
              break;
     case TOKDEF_UNIT:
              IGNORE f_make_tokdef_unit();
              break;
     case AL_UNIT:
              IGNORE f_make_aldef_unit();
              break;
     case TAGDEC_UNIT:
              IGNORE f_make_tagdec_unit();
              break;
     case TAGDEF_UNIT:
              IGNORE f_make_tagdef_unit();
              break;
     case DIAGDEF_UNIT:		/* OLD DIAGS */
              if (diagnose)
                IGNORE f_make_diagdef_unit();
              else
                ignore_bytestream();
              break;
     case DIAGTYPE_UNIT:	/* OLD DIAGS */
              if (diagnose)
                IGNORE f_make_diagtype_unit();
              else
                ignore_bytestream();
              break;
     case LINKINFO_UNIT:
              IGNORE f_make_linkinfo_unit();
              break;
     case VERSIONS_UNIT:
	      IGNORE f_make_versions_unit();
	      break;
     case DGCOMP_UNIT:	/* NEW DIAGS */
              if (diagnose)
                IGNORE f_make_dg_comp_unit();
              else
                ignore_bytestream();
              break;
     default:
              ignore_bytestream();
              break;
   };
  return 0;
}

linkextern f_make_linkextern
    PROTO_N ( (internal, ext) )
    PROTO_T ( tdfint internal X external ext )
{
  switch (crt_extern_link_type)
   {
     case TOK_TYPE:
       return f_make_tokextern(internal, ext);
     case TAG_TYPE:
       return f_make_tagextern(internal, ext);
     case AL_TYPE:
       return f_make_alextern(internal, ext);
     case DIAGTAG_TYPE:		/* OLD DIAGS */
       return f_make_diagtagextern(internal, ext);
     case DGTAG_TYPE:		/* NEW DIAGS */
       return f_make_dgtagextern(internal, ext);
     default:
       failer(VARIABLE_TYPE);
       return 0;
   };
}

group f_make_group
    PROTO_N ( (us) )
    PROTO_T ( unit_list us )
{
  UNUSED(us);
  return 0;
}

links f_make_links
    PROTO_N ( (ls) )
    PROTO_T ( link_list ls )
{
  UNUSED(ls);
  return 0;
}

extern_link f_make_extern_link
    PROTO_N ( (el) )
    PROTO_T ( linkextern_list el )
{
  UNUSED(el);
  return 0;
}

tokdef_props f_make_tokdefs
    PROTO_N ( (nl, tds) )
    PROTO_T ( tdfint nl X tokdef_list tds )
{
  UNUSED(nl); UNUSED(tds);
  return 0;
}

tokdec_props f_make_tokdecs
    PROTO_N ( (tds) )
    PROTO_T ( tokdec_list tds )
{
  UNUSED(tds);
  return 0;
}

tagdef_props f_make_tagdefs
    PROTO_N ( (nl, tds) )
    PROTO_T ( tdfint nl X tagdef_list tds )
{
  UNUSED(nl); UNUSED(tds);
  return 0;
}

al_tagdef_props f_make_al_tagdefs
    PROTO_N ( (nl, tds) )
    PROTO_T ( tdfint nl X al_tagdef_list tds )
{
  UNUSED(nl); UNUSED(tds);
  return 0;
}

tagdec_props f_make_tagdecs
    PROTO_N ( (nl, tds) )
    PROTO_T ( tdfint nl X tagdec_list tds )
{
 UNUSED(nl); UNUSED(tds);
 return 0;
}



sortname_list new_sortname_list
    PROTO_N ( (n) )
    PROTO_T ( int n )
{
  sortname_list res;
  res.number = n;
  res.elems = (sortname*)xcalloc(n, sizeof(sortname));
  return res;
}

sortname_list add_sortname_list
    PROTO_N ( (list, elem, index) )
    PROTO_T ( sortname_list list X sortname elem X int index )
{
  list.elems[index] = elem;
  return list;
}

tokformals_list new_tokformals_list
    PROTO_N ( (n) )
    PROTO_T ( int n )
{
  tokformals_list res;
  res.number = n;
  res.par_sorts = (sortname *)xcalloc(n, sizeof(sortname));
  res.par_names = (int *)xcalloc(n, sizeof(int));
  return res;
}

tokformals_list add_tokformals_list
    PROTO_N ( (list, elem, index) )
    PROTO_T ( tokformals_list list X tokformals elem X int index )
{
  list.par_sorts[index] = elem.sn;
  list.par_names[index] = elem.tk;
  return list;
}

tokdec_list new_tokdec_list
    PROTO_N ( (n) )
    PROTO_T ( int n )
{
  UNUSED(n);
  return 0;
}

tokdec_list add_tokdec_list
    PROTO_N ( (list, elem, index) )
    PROTO_T ( tokdec_list list X tokdec elem X int index )
{
  UNUSED(list); UNUSED(elem); UNUSED(index);
  return 0;
}

tokdef_list new_tokdef_list
    PROTO_N ( (n) )
    PROTO_T ( int n )
{
  UNUSED(n);
  return 0;
}

tokdef_list add_tokdef_list
    PROTO_N ( (list, elem, index) )
    PROTO_T ( tokdef_list list X tokdef elem X int index )
{
  UNUSED(list); UNUSED(elem); UNUSED(index);
  return 0;
}

al_tagdef_list new_al_tagdef_list
    PROTO_N ( (n) )
    PROTO_T ( int n )
{
  UNUSED(n);
  return 0;
}

al_tagdef_list add_al_tagdef_list
    PROTO_N ( (list, elem, index) )
    PROTO_T ( al_tagdef_list list X al_tagdef elem X int index )
{
  UNUSED(list); UNUSED(elem); UNUSED(index);
  return 0;
}


al_tagdef f_make_al_tagdef
    PROTO_N ( (t, a) )
    PROTO_T ( tdfint t X alignment a )
{
  aldef * ap = get_aldef(natint(t));
  ap -> next_aldef = top_aldef;
  top_aldef = ap;
  ap -> al = a -> al;
  return 0;
}



tagdec_list new_tagdec_list
    PROTO_N ( (n) )
    PROTO_T ( int n )
{
  UNUSED(n);
  return 0;
}

tagdec_list add_tagdec_list
    PROTO_N ( (list, elem, index) )
    PROTO_T ( tagdec_list list X tagdec elem X int index )
{
    dec * dp = elem.tg;
    shape s;
    exp e;
    UNUSED(list); UNUSED(index);
    s = elem.sha;

    e = getexp(s, nilexp, 0, nilexp, nilexp, 0, 0, ident_tag);

    if (elem.is_variable)
     {
#if keep_PIC_vars
       setvar(e);
#else
       if (PIC_code && dp -> dec_u.dec_val.extnamed)
         sh(e) = f_pointer(f_alignment(s));
       else
         setvar(e);
#endif
     };

    if (elem.acc & (f_visible | f_long_jump_access))
      setvis(e);
    if (elem.acc & f_constant)
      setcaonly(e);

    dp -> dec_u.dec_val.acc = elem.acc;

    dp -> dec_u.dec_val.dec_exp = e;

    if (dp -> dec_u.dec_val.dec_shape != nilexp) {
      if (shape_size(s) > shape_size(dp -> dec_u.dec_val.dec_shape))
        dp -> dec_u.dec_val.dec_shape = s;
    };

    if (dp -> dec_u.dec_val.dec_shape == nilexp) {
      dp -> dec_u.dec_val.dec_shape = s;
      dp -> def_next = (dec *)0;
      *deflist_end = dp;
      deflist_end = &((*deflist_end) -> def_next);
    };

    dp -> dec_u.dec_val.dec_var = (unsigned int)(isvar(e) || elem.is_variable) ;
    if (!dp -> dec_u.dec_val.have_def)
     {
      setglob(e);
     };
    /* the defining exp */
    brog(dp -> dec_u.dec_val.dec_exp) = dp;
    if (dp -> dec_u.dec_val.dec_id == (char *) 0)
      dp -> dec_u.dec_val.dec_id = make_local_name();

  return 0;
}

tagdef_list new_tagdef_list
    PROTO_N ( (n) )
    PROTO_T ( int n )
{
  UNUSED(n);
  return 0;
}

tagdef_list add_tagdef_list
    PROTO_N ( (list, elem, index) )
    PROTO_T ( tagdef_list list X tagdef elem X int index )
{
  dec * dp = elem.tg;
  exp old_def = son(dp -> dec_u.dec_val.dec_exp);
  exp new_def = elem.def;
  UNUSED(list); UNUSED(index);
  if (dp -> dec_u.dec_val.processed || new_def == nilexp)
    return 0;

  if (old_def == nilexp ||
       shape_size(sh(new_def)) > shape_size(sh(old_def)) ||
       (name(new_def) != clear_tag && name(old_def) == clear_tag))  {
    son(dp -> dec_u.dec_val.dec_exp) = new_def;
    setfather(dp -> dec_u.dec_val.dec_exp, elem.def);
  };

  return 0;
}

tdfident_list new_tdfident_list
    PROTO_N ( (n) )
    PROTO_T ( int n )
{
  tdfstring_list res;
  res.elems = (tdfstring *)xcalloc(n, sizeof(tdfstring));
  res.number = n;
  return res;
}

tdfident_list add_tdfident_list
    PROTO_N ( (list, elem, index) )
    PROTO_T ( tdfident_list list X tdfident elem X int index )
{
  list.elems[index] = elem;
  return list;
}

tdfint_list new_tdfint_list
    PROTO_N ( (n) )
    PROTO_T ( int n )
{
  tdfint_list res;
  res.members = (tdfint *)xcalloc(n, sizeof(tdfint));
  res.number = n;
  return res;
}

tdfint_list add_tdfint_list
    PROTO_N ( (list, elem, index) )
    PROTO_T ( tdfint_list list X tdfint elem X int index )
{
  list.members[index] = elem;
  return list;
}

group_list new_group_list
    PROTO_N ( (n) )
    PROTO_T ( int n )
{
  UNUSED(n);
  crt_group_type = group_type(crt_capsule_groups[0].ints.chars);
  return 0;
}

group_list add_group_list
    PROTO_N ( (list, elem, index) )
    PROTO_T ( group_list list X group elem X int index )
{
  UNUSED(list); UNUSED(elem);
  if (index < (crt_capsule_group_no-1))
    crt_group_type = group_type(crt_capsule_groups[index+1].ints.chars);
  return 0;
}

links_list new_links_list
    PROTO_N ( (n) )
    PROTO_T ( int n )
{
  UNUSED(n);
  if (crt_capsule_link_no != 0)
    crt_links_type = links_type(crt_capsule_linking.members[0].id);
  return 0;
}

links_list add_links_list
    PROTO_N ( (list, elem, index) )
    PROTO_T ( links_list list X links elem X int index )
{
  UNUSED(list); UNUSED(elem);
  if (index < (crt_capsule_linking.number-1))
    crt_links_type = links_type(crt_capsule_linking.members[index+1].id);
  return 0;
}

extern_link_list new_extern_link_list
    PROTO_N ( (n) )
    PROTO_T ( int n )
{
  UNUSED(n);
  if (crt_capsule_link_no != 0)
    crt_extern_link_type = links_type(crt_capsule_linking.members[0].id);
  return 0;
}

extern_link_list add_extern_link_list
    PROTO_N ( (list, elem, index) )
    PROTO_T ( extern_link_list list X extern_link elem X int index )
{
  UNUSED(list); UNUSED(elem);
  if (index < (crt_capsule_linking.number-1))
     crt_extern_link_type =
         links_type(crt_capsule_linking.members[index+1].id);
  return 0;
}

capsule_link_list new_capsule_link_list
    PROTO_N ( (n) )
    PROTO_T ( int n )
{
  capsule_link_list res;
  res.members = (capsule_link *)xcalloc(n, sizeof(capsule_link));
  res.number = n;
  return res;
}

capsule_link_list add_capsule_link_list
    PROTO_N ( (list, elem, index) )
    PROTO_T ( capsule_link_list list X capsule_link elem X int index )
{
  list.members[index] = elem;
  return list;
}

unit_list new_unit_list
    PROTO_N ( (n) )
    PROTO_T ( int n )
{
  UNUSED(n);
  return 0;
}

unit_list add_unit_list
    PROTO_N ( (list, elem, index) )
    PROTO_T ( unit_list list X unit elem X int index )
{
  UNUSED(list); UNUSED(elem); UNUSED(index);
  return 0;
}

link_list new_link_list
    PROTO_N ( (n) )
    PROTO_T ( int n )
{
  int i;
  switch (crt_links_type)
   {
       /* initialise the table */
     case TOK_TYPE:
       no_of_local_tokens = unit_no_of_tokens - n;
       unit_toktab = (tok_define *)xcalloc(no_of_local_tokens,
                         sizeof(tok_define));
       for (i = 0; i < no_of_local_tokens; ++i) {
         tok_define * tp = &unit_toktab[i];
         tp -> tok_special = 0;
         tp -> valpresent = 0;
         tp -> unit_number = crt_tagdef_unit_no;
         tp -> defined = 0;
         tp -> tok_index = i;
         tp -> is_capsule_token = 0;
         tp -> recursive = 0;
       };
       return 0;
     case TAG_TYPE:
       unit_tagtab = (dec *)xcalloc(unit_no_of_tags - n,
                         sizeof(dec));
       for (i = 0; i < unit_no_of_tags - n; ++i) {
         dec * dp = &unit_tagtab[i];
         dp -> dec_u.dec_val.dec_outermost = 0;
         dp -> dec_u.dec_val.dec_id = (char *) 0;
         dp -> dec_u.dec_val.extnamed = 0;
         dp -> dec_u.dec_val.diag_info = (diag_global *)0;
         dp -> dec_u.dec_val.have_def = 0;
         dp -> dec_u.dec_val.dec_shape = nilexp;
         dp -> dec_u.dec_val.processed = 0;
         dp -> dec_u.dec_val.isweak = 0;
         dp -> dec_u.dec_val.dec_exp = nilexp;
       };
       return 0;
     case AL_TYPE:
       unit_altab = (aldef *)xcalloc(unit_no_of_als - n,
                         sizeof(aldef));
       for (i = 0; i < unit_no_of_als - n; ++i) {
         aldef * ap = &unit_altab[i];
         ap -> al.al_n = 0;
       };
       return 0;
     case DIAGTAG_TYPE:		/* OLD DIAGS */
       init_unit_diagtags(n);
       return 0;
     case DGTAG_TYPE:		/* NEW DIAGS */
       init_unit_dgtags(n);
       return 0;
     default:
       failer(LINK_TYPE);
       return 0;
   };
}

link_list add_link_list
    PROTO_N ( (list, elem, index) )
    PROTO_T ( link_list list X link elem X int index )
{
  UNUSED(list); UNUSED(elem); UNUSED(index);
  return 0;
}

linkextern_list new_linkextern_list
    PROTO_N ( (n) )
    PROTO_T ( int n )
{
  UNUSED(n);
  return 0;
}

linkextern_list add_linkextern_list
    PROTO_N ( (list, elem, index) )
    PROTO_T ( linkextern_list list X linkextern elem X int index )
{
  UNUSED(list); UNUSED(elem); UNUSED(index);
  return 0;
}




exp_option no_exp_option;

exp_option yes_exp_option
    PROTO_N ( (elem) )
    PROTO_T ( exp elem )
{
  exp_option res;
  res.present = 1;
  res.val = elem;
  return res;
}

void init_exp_option
    PROTO_Z ()
{
   no_exp_option.present = 0;
   return;
}

tag_option no_tag_option;

tag_option yes_tag_option
    PROTO_N ( (elem) )
    PROTO_T ( tag elem )
{
  tag_option res;
  res.present = 1;
  res.val = elem;
  return res;
}

void init_tag_option
    PROTO_Z ()
{
   no_tag_option.present = 0;
   return;
}

void init_capsule_link
    PROTO_Z ()
{
  return;
}


void init_extern_link
    PROTO_Z ()
{
  return;
}

void init_group
    PROTO_Z ()
{
  return;
}

void init_unit
    PROTO_Z ()
{
  return;
}

void init_link
    PROTO_Z ()
{
  return;
}

void init_linkextern
    PROTO_Z ()
{
  return;
}

void init_links
    PROTO_Z ()
{
  return;
}

void init_tagdec_props
    PROTO_Z ()
{
  return;
}

void init_tagdef_props
    PROTO_Z ()
{
  return;
}

void init_al_tagdef_props
    PROTO_Z ()
{
  return;
}

void init_tokdec_props
    PROTO_Z ()
{
  return;
}

void init_tokdef_props
    PROTO_Z ()
{
  return;
}





