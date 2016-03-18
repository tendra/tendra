/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <stdlib.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/xalloc.h>

#include <tdf/sort.h>

#include <reader/exp.h>

#include <reader/readglob.h>
#include <reader/basicread.h>
#include <reader/main_reads.h>
#include <reader/externs.h>
#include <reader/read_sort.h>
#include <reader/table_fns.h>

#include <construct/exp.h>
#include <construct/installglob.h>
#include <construct/install_fns.h>
#include <construct/aldefs.h>

#include <special/special_tok.h>

#ifdef TDF_DIAG3
#include <diag3/diagglob.h>
#include <diag3/dg_fns.h>
#endif
#ifdef TDF_DIAG4
#include <diag4/diagglob.h>
#include <diag4/dg_fns.h>
#endif

#include <refactor/refactor.h>

typedef struct tag_con_t {
	dec *namet;
	exp e;
	struct tag_con_t *rest;
} tag_con;

typedef struct lab_con_t {
	label namel;
	exp e;
	struct lab_con_t *rest;
} lab_con;

struct context_t {
	tok_define *toks;

	short no_toks;
	bool recursive :1;

	/*
	 * don't know how many tag & labs defined in token
	 * so have to keep list; NB used only if recursive
	 */
	tag_con *tags;
	lab_con *labs;

	struct context_t *outer;
};

/* The initial values are only to give something to push */
context *crt_context = NULL;

static tokformals_list nil_params;

/* find the exp which is labelled by l */
exp
get_lab(label l)
{
	context *con;
	lab_con *lc;

	for (con = crt_context; con != NULL; con = con->outer) {
		for (lc = con->labs; lc != NULL; lc = lc->rest) {
			if (lc->namel == l) {
				return lc->e;
			}
		}
	}

	return *l;
}

/* set the exp which is labelled by l */
void
set_lab(label l, exp e)
{
	if (crt_context == NULL || !crt_context->recursive) {
		*l = e;
	} else {
		lab_con *lc = xmalloc(sizeof(lab_con));
		lc->namel = l;
		lc->e = e;
		lc->rest = crt_context->labs;
		crt_context->labs = lc;
	}
}

/* find the tag declaration indexed by tag */
dec *
get_dec(int tag)
{
	dec *res;

	res = unit_ind_tags[tag];
	res->index = tag;

	return res;
}

/* find the alignment tag value indexed by tag */
aldef *
get_aldef(int tag)
{
	return unit_ind_als[tag];
}

/* find the token declaration indexed by tag */
tok_define *
get_tok(int tk)
{
	context *con;
	int i;

	for (con = crt_context; con != NULL; con = con->outer) {
		for (i = 0; i < con->no_toks; i++) {
			if (tk == con->toks[i].tdtoken) {
				return &con->toks[i];
			}
		}
	}

	return unit_ind_tokens[tk];
}

/* find the exp known as tag */
exp
get_tag(tag tag)
{
	context *con;
	tag_con *tc;

	for (con = crt_context; con != NULL; con = con->outer) {
		for (tc = con->tags; tc != NULL; tc = tc->rest) {
			if (tc->namet == tag) {
				return tc->e;
			}
		}
	}

	return tag->exp;
}

/* set the exp known as tag */
void
set_tag(tag tag, exp e)
{
	if (crt_context == NULL || !crt_context->recursive) {
		tag->exp = e;
	} else {
		tag_con *tc = xmalloc(sizeof(tag_con));
		tc->namet = tag;
		tc->e = e;
		tc->rest = crt_context->tags;
		crt_context->tags = tc;
	}
}

/* apply tk to its parameters in pars, and return the result */
tokval
apply_tok(token td, bitstream pars, int sortcode, tokval * actual_pars)
{
	if (td->tok_special || !td->defined) {
		tokval tkv;

		if (special_token(special_toks, special_toks_count, &tkv, td, pars, sortcode)) {
			return tkv;
		}

		if (special_token(special_ariths, special_ariths_count, &tkv, td, pars, sortcode)) {
			return tkv;
		}

		if (special_token(special_allocs, special_allocs_count, &tkv, td, pars, sortcode)) {
			return tkv;
		}

		if (special_token(special_diags, special_diags_count, &tkv, td, pars, sortcode)) {
			return tkv;
		}
	}

	if (!td->defined) {
		/* detect various errors and give helpful information */
		error(ERR_INTERNAL, "use of undefined token - fatal error");

		if (td->is_capsule_token &&
		    td->tok_index < capsule_no_of_tokens &&
		    td->tok_index >= 0 &&
		    td->tok_name != NULL) {
			IGNORE fprintf(stderr, "token is: %s\n", td->tok_name);
		} else {
			if (td->is_capsule_token &&
			    td->tok_index < capsule_no_of_tokens &&
			    td->tok_index >= 0) {
				IGNORE fprintf(stderr, "capsule token number: %d\n", td->tok_index);
			} else {
				if (td->tok_index >= 0 &&
				    td->tok_index < unit_no_of_tokens) {
					IGNORE fprintf(stderr, "local unit token number: %d\n", td->tok_index);
				} else {
					IGNORE fprintf(stderr, "token number out of bounds\n");
				}
			}
			exit(EXIT_FAILURE);
		}
	}

	{
		int npars = td->params.number; /* number of parameters */

		/* to construct the bindings for this expansion */
		context new_context;
		context *old_context = crt_context;

		tokval val;

		/* to record the current place in the input stream */
		place old_place;

		int j;

		dec **old_tagtab;        /* to remember the current tag table */
		exp *old_labtab;         /* to remember the current label table */
		tok_define **old_toktab; /* to remember the current token table */
		aldef **old_altab;       /* to remember the current alignment tag table */

		diag_tagdef **old_diagtab;		/* TDF_DIAG3 */
		dgtag_struct **old_dgtab;		/* TDF_DIAG4 */

		old_tagtab  = unit_ind_tags;
		old_labtab  = unit_labtab;
		old_toktab  = unit_ind_tokens;
		old_altab   = unit_ind_als;
		old_diagtab = unit_ind_diagtags;	/* TDF_DIAG3 */
		old_dgtab   = unit_ind_dgtags;		/* TDF_DIAG4 */

		new_context.no_toks = (short)npars;
		nil_params.number = 0;

		/* if a value has already been computed (there will be no parameters) */
		if (td->valpresent && (td->unit_number == crt_tagdef_unit_no)) {
			if (sortcode == f_exp.code) {
				tokval v;

				/* copy it if the result is an expression,
				 * since we may be going to alter it */
				v.tk_exp = copy(td->tdvalue.tk_exp);

				return v;
			} else  {
				return td->tdvalue;
			}
		}

		/* remember the current input stream */
		old_place = keep_place();

		set_place(pars);

		/* now set up the new parameter bindings */
		if (npars > 0) {
			new_context.toks = xcalloc(npars, sizeof(tok_define));

			/* read in the parameter values and bind them to the formals */
			for (j = 0; j < npars; ++j) {
				sortname sn;
				exp old_crt_repeat;  /* XX008 */

				sn = (td->params.par_sorts)[j];
				new_context.toks[j].tdsort      = sn; /* parameter sort */
				new_context.toks[j].tdtoken     = (td->params.par_names)[j]; /* formal */
				new_context.toks[j].valpresent  = true; /* the value is known */
				new_context.toks[j].unit_number = crt_tagdef_unit_no;
				new_context.toks[j].re_evaluate = false; /* and does not need re-evaluating */
				new_context.toks[j].params      = nil_params; /* it has no parameters itself */

				/* XX008 */
				if (sn.code == f_exp.code) {
					old_crt_repeat = crt_repeat;
					crt_repeat = NULL;
				} else {
					SET(old_crt_repeat);
				}

				/* read a parameter */
				if (actual_pars != NULL) {
					/* this is not used at present*/
					new_context.toks[j].tdvalue = actual_pars[j];
				} else {
					new_context.toks[j].tdvalue = read_sort(sn.code);
				}

				/* XX008 */
				if (sn.code == f_exp.code) {
					crt_repeat = old_crt_repeat;
				}

				new_context.toks[j].defined     = true;  /* and say it is defined */
				new_context.toks[j].tok_special = false; /* and say it is not special */
				new_context.toks[j].recursive   = (sn.code == SORT_TOKEN); /* and say it is not recursive for simple sorts */
				new_context.toks[j].tok_context = crt_context;
			}
		}

		/* set up the place to read the definition */
		set_place(td->tdplace);

		new_context.recursive = td->recursive;
		new_context.outer     = td->tok_context;
		new_context.tags      = NULL;
		new_context.labs      = NULL;

		crt_context = &new_context;

		/* now set up the tables which belong to the place
		 * where the token was defined */
		unit_ind_tags     = td->my_tagtab;
		unit_labtab       = td->my_labtab;
		unit_ind_tokens   = td->my_toktab;
		unit_ind_als      = td->my_altab;
		unit_ind_diagtags = td->my_diagtab;	/* TDF_DIAG3 */
		unit_ind_dgtags   = td->my_dgtab;	/* TDF_DIAG4 */

		/* read the body of the definition */
		td->recursive = true;  /* set up to detect recursion */
		val           = read_sort(sortcode);
		td->recursive = new_context.recursive;

		/* restore the place in the input stream */
		set_place(old_place);

		/* kill off exps (they were copied) */
		for (j = 0; j < npars; ++j) {
			if (new_context.toks[j].tdsort.code == f_exp.code) {
				exp ek = new_context.toks[j].tdvalue.tk_exp;
				kill_exp(ek, ek);
			}
		}

		/* restore the old environment of tables */
		crt_context       = old_context;
		unit_ind_tags     = old_tagtab;
		unit_labtab       = old_labtab;
		unit_ind_tokens   = old_toktab;
		unit_ind_als      = old_altab;
		unit_ind_diagtags = old_diagtab;	/* TDF_DIAG3 */
		unit_ind_dgtags   = old_dgtab;		/* TDF_DIAG4 */

		if (!doing_aldefs && npars == 0 && !new_context.recursive) {
			/* if there were no parameters, record the
			 * value for the next application of the token */
			td->valpresent = true;
			td->tdvalue    = val;

			if (sortcode == f_exp.code) {
				tokval v;

				/* if we are remembering it we must copy,
				 * because the returned value might be altered */
				v.tk_exp = copy(val.tk_exp);
				IGNORE hold(val.tk_exp);

				return v;
			}
		} else {
			/* free the space used for parameter binding */
			xfree(new_context.toks);
		}

		while (new_context.tags != NULL) {
			tag_con *r = new_context.tags;
			new_context.tags = new_context.tags->rest;
			xfree(r);
		}

		while (new_context.labs != NULL) {
			lab_con *r = new_context.labs;
			new_context.labs = new_context.labs->rest;
			xfree(r);
		}

		return val;
	}
}

