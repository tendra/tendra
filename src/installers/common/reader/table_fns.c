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
$Log: table_fns.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:45  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1997/08/23  13:31:07  pwe
 * no invert order, and initial ANDF-DE
 *
 * Revision 1.1  1995/04/06  10:43:34  currie
 * Initial revision
 *
***********************************************************************/


#include "config.h"
#include "common_types.h"
#include "readglob.h"
#include "xalloc.h"
#include "basicread.h"
#include "sortmacs.h"
#include "exp.h"
#include "expmacs.h"
#include "main_reads.h"
#include "externs.h"
#include "spec_tok.h"
#include "read_sort.h"
#include "messages_r.h"
#include "installglob.h"
#include "install_fns.h"
#include "diagglob.h"
#include "dg_fns.h"
#include "check.h"

#include "table_fns.h"




/* VARIABLES */
/* The initial values are only to give something to push, jmf */




context * crt_context = (context*)0;

/* IDENTITY */

static tokformals_list nil_params;


/* PROCEDURES */


exp get_lab
    PROTO_N ( (l) )
    PROTO_T ( label l )
{
	/* find the exp which is labelled by l */
	context * con = crt_context;
	while (con != (context*)0) {
	   lab_con * lc = con->labs;
	   while (lc != (lab_con*)0) {
	   	if (lc->namel == l) return lc->e;
		lc = lc->rest;
	   }
	   con = con->outer;
	}
	return *l;
}

void set_lab
    PROTO_N ( (l, e) )
    PROTO_T ( label l X exp e )
{
  /* set the exp which is labelled by l */
  if (crt_context == (context*)0 || crt_context->recursive == 0) {
  	*l = e;
  }
  else {
  	lab_con * lc = (lab_con*)xmalloc(sizeof(lab_con));
	lc->namel = l; lc->e = e; lc->rest = crt_context->labs;
	crt_context->labs = lc;
  }
  return;
}


dec * get_dec
    PROTO_N ( (tg) )
    PROTO_T ( int tg )
{
  /* find the tag declaration indexed by tg */
  dec * res = unit_ind_tags[tg];
  res->dec_u.dec_val.index = tg;
  return res;
}

aldef * get_aldef
    PROTO_N ( (tg) )
    PROTO_T ( int tg )
{
  /* find the alignment tag value indexed by tg */
  return unit_ind_als[tg];
}

tok_define * get_tok
    PROTO_N ( (tk) )
    PROTO_T ( int tk )
{
  /* find the token declaration indexed by tg */
  context * con = crt_context;
  while (con != (context *)0) {
     int n = con->no_toks;
     int nl = (n > LOCAL_TOKS)?LOCAL_TOKS:n;
     tok_define * cbind = &con->loctoks[0];
     int i;
     for(i=0; i<nl; i++) {
     	if (tk == cbind[i].tdtoken) {
		return & cbind[i];
	}
     }
     cbind = con->othertoks;
     for(i=LOCAL_TOKS; i<n; i++) {
     	if (tk == cbind[i-LOCAL_TOKS].tdtoken) {
		return & cbind[i-LOCAL_TOKS];
	}
     }
     con = con->outer;
  }
  return unit_ind_tokens[tk];
}


exp get_tag
    PROTO_N ( (tg) )
    PROTO_T ( tag tg )
{
	/* find the exp known as tg */
   	context * con = crt_context;
	while (con != (context*)0) {
	   tag_con * tc = con->tags;
	   while (tc != (tag_con*)0) {
	   	if (tc->namet == tg) return tc->e;
		tc = tc->rest;
	   }
	   con = con->outer;
	}
   	return tg -> dec_u.dec_val.dec_exp;
}



void set_tag
    PROTO_N ( (tg, e) )
    PROTO_T ( tag tg X exp e )
{
  /* set the exp known as tg */
  if (crt_context == (context*)0 || crt_context->recursive == 0) {
  	tg -> dec_u.dec_val.dec_exp = e;
  }
  else {
  	tag_con * tc = (tag_con*)xmalloc(sizeof(tag_con));
	tc->namet = tg; tc->e = e; tc->rest = crt_context->tags;
	crt_context->tags = tc;
  }
  return;
}


  /* apply tk to its parameters in pars, and return the result */
tokval apply_tok
    PROTO_N ( (td, pars, sortcode, actual_pars) )
    PROTO_T ( token td X bitstream pars X int sortcode X tokval * actual_pars )
{
  if (td -> tok_special || td -> defined == 0)
	  /* handle the special tokens */
    { tokval tkv;
      int done = 0;
      tkv = special_token(td, pars, sortcode, &done);
      if (done)
        return tkv;
    };

  if (td -> defined == 0)
   {
     /* detect various errors and give helpful information */
     if (td -> defined == 0)
       failer(UNDEFINED_TOK);

     if (td -> is_capsule_token &&
         td -> tok_index < capsule_no_of_tokens &&
         td -> tok_index >= 0 &&
         td -> tok_name != (char*)0)
        IGNORE fprintf(stderr, "token is: %s\n", td -> tok_name);
     else
      {
        if (td -> is_capsule_token &&
            td -> tok_index < capsule_no_of_tokens &&
            td -> tok_index >= 0)
           IGNORE fprintf(stderr, "capsule token number: %d\n", td -> tok_index);
        else
         {
           if (td -> tok_index >= 0 &&
               td -> tok_index < unit_no_of_tokens)
              IGNORE fprintf(stderr, "local unit token number: %d\n",
                       td -> tok_index);
           else
              IGNORE fprintf(stderr, "token number out of bounds\n");
         };
      };
     exit(EXIT_FAILURE);
   };

 {
  int npars = td -> params.number;  /* number of parameters */
  context new_context; /* to construct the bindings for this expansion */
  context * old_context = crt_context;

  tokval val;
  place old_place;  /* to record the current place in the input stream */
  tok_define * new_bindings;
  int i,j;
  dec * * old_tagtab;
     /* to remember the current tag table */
  exp* old_labtab;
     /* to remember the current label table */
  tok_define * * old_toktab;
     /* to remember the current token table */
  aldef * * old_altab;
     /* to remember the current alignment tag table */
  diag_tagdef * * old_diagtab;		/* OLD DIAGS */
  dgtag_struct * * old_dgtab;		/* NEW DIAGS */

     /* now remember them */
  old_tagtab = unit_ind_tags;
  old_labtab = unit_labtab;
  old_toktab = unit_ind_tokens;
  old_altab = unit_ind_als;
  old_diagtab = unit_ind_diagtags;	/* OLD DIAGS */
  old_dgtab = unit_ind_dgtags;		/* NEW DIAGS */

  new_context.no_toks = (short) npars;
  nil_params.number = 0;

  if (td -> valpresent &&
       (td -> unit_number == crt_tagdef_unit_no ))
    {
      /* if a value has already been computed
         (there will be no parameters) */

          if (sortcode == f_exp.code)
           {tokval v;
            v.tk_exp = copy(td -> tdvalue.tk_exp);
              /* copy it if the result is an expression since
                 we may be going to alter it */
            return v;
           }
          else  {
            return td -> tdvalue;
	  };
    };

  old_place = keep_place();  /* remember the current input stream */
  set_place(pars);

     /* now set up the new parameter bindings */
  if (npars > LOCAL_TOKS) {
    new_context.othertoks = (tok_define *) xcalloc (npars-LOCAL_TOKS,
                            			sizeof (tok_define));
  }

  new_bindings = &new_context.loctoks[0];


  for (j=0; j<npars; ++j)
   {
        /* read in the parameter values and bind them to the formals */
      sortname sn;
      exp old_crt_repeat;  /* XX008 */
      if (j>=LOCAL_TOKS) {
      	i = j-LOCAL_TOKS; new_bindings = new_context.othertoks;
      }
      else i = j;
      sn = (td -> params.par_sorts)[j];
      new_bindings[i].tdsort = sn;
          /* parameter sort */
      new_bindings[i].tdtoken = (td -> params.par_names)[j];
          /* formal */
      new_bindings[i].valpresent = 1;
          /* the value is known */
      new_bindings[i].unit_number = crt_tagdef_unit_no;
      new_bindings[i].re_evaluate = 0;
          /* and does not need re-evaluating */
      new_bindings[i].params = nil_params;
          /* it has no parameters itself */

      if (sn.code == f_exp.code) {  /* XX008 */
	old_crt_repeat = crt_repeat;
	crt_repeat = nilexp;
      }
      else {
	SET(old_crt_repeat);
      };
      if (actual_pars != (tokval*)0) {
	new_bindings[i].tdvalue = actual_pars[j]; /* this is not used at present*/
      }
      else {
        new_bindings[i].tdvalue = read_sort(sn.code);
      }
          /* read a parameter */
      if (sn.code == f_exp.code) {  /* XX008 */
	crt_repeat = old_crt_repeat;
      };

      new_bindings[i].defined = 1;
          /* and say it is defined */
      new_bindings[i].tok_special = 0;
          /* and say it is not special */
      new_bindings[i].recursive = (sn.code == TOKEN);
          /* and say it is not recursive for simple sorts */
      new_bindings[i].tok_context = crt_context;
   };

  set_place(td -> tdplace);  /* set up the place to read the definition */

  new_context.recursive = td -> recursive;
  new_context.outer = td -> tok_context;
  new_context.tags = (tag_con *)0;
  new_context.labs = (lab_con *)0;

  crt_context = &new_context;

   /* now set up the tables which belong to the place where the
      token was defined */
  unit_ind_tags = td -> my_tagtab;
  unit_labtab = td -> my_labtab;
  unit_ind_tokens = td -> my_toktab;
  unit_ind_als = td -> my_altab;
  unit_ind_diagtags = td -> my_diagtab;		/* OLD DIAGS */
  unit_ind_dgtags = td -> my_dgtab;		/* NEW DIAGS */

  /* read the body of the definition */
  td -> recursive = 1;  /* set up to detect recursion */
  val = read_sort(sortcode);
  td -> recursive = new_context.recursive;

  set_place(old_place);  /* restore the place in the input stream */

  new_bindings = &new_context.loctoks[0];

  for (j = 0; j < npars; ++j) {/* kill off exps (they were copied) */
    tok_define * q;
    if (j>=LOCAL_TOKS) {
    	i = j-LOCAL_TOKS; new_bindings = new_context.othertoks;
    }
    else i = j;
    q = &new_bindings[i];
    if (q -> tdsort.code == f_exp.code) {
      exp ek = q -> tdvalue.tk_exp;
      kill_exp (ek, ek);
    };
  };

    /* restore the old environment of tables */
  crt_context = old_context;
  unit_ind_tags = old_tagtab;
  unit_labtab = old_labtab;
  unit_ind_tokens = old_toktab;
  unit_ind_als = old_altab;
  unit_ind_diagtags = old_diagtab;	/* OLD DIAGS */
  unit_ind_dgtags = old_dgtab;		/* NEW DIAGS */

  if (!doing_aldefs && npars == 0 && new_context.recursive == 0)
   {
          /* if there were no parameters, record the value for the
             next application of the token */
	td -> valpresent = 1;
	td -> tdvalue = val;
	if (sortcode == f_exp.code)
           {tokval v;
            v.tk_exp = copy(val.tk_exp);
              /* if we are remembering it we must copy, because the
                 returned value might be altered */
	    IGNORE hold(val.tk_exp);
            return v;
           };
   }
  else
  if (npars > LOCAL_TOKS)
       xfree((void *)new_context.othertoks);
          /* free the space used for parameter binding */
  while(new_context.tags != (tag_con*)0) {
  	tag_con * r = new_context.tags;
	new_context.tags = new_context.tags->rest;
	xfree((void *)r);
  }
  while(new_context.labs != (lab_con*)0) {
  	lab_con * r = new_context.labs;
	new_context.labs = new_context.labs->rest;
	xfree((void *)r);
  }
  return val;
 };
}



