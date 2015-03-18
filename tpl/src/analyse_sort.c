/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include "config.h"

#include "util.h"
#include "defs.h"
#include "syntax.h"
#include "analyse_sort.h"
#include "encodings.h"
#include "enc_nos.h"
#include "lex.h"
#include "namedecs.h"
#include "streams.h"
#include "errors.h"


void
read_tdfint(void)
{
    fail("This shouldn't happen");
}

void
read_tdfbool(void)
{
    fail("This shouldn't happen");
}


static void
out_nontoksort(int sort)
{
    switch (sort) {
	case access_sort:
		o_access;
		return;
	case alignment_sort:
		o_alignment_sort;
		return;
	case al_tag_sort:
		o_al_tag;
		return;
	case bitfield_variety_sort:
		o_bitfield_variety;
		return ;
	case bool_sort:
		o_bool;
		return;
	case error_treatment_sort:
		o_error_treatment;
		return;
	case exp_sort:
		o_exp;
		return;
	case floating_variety_sort:
		o_floating_variety;
		return;
	case label_sort:
		o_label;
		return;
	case nat_sort:
		o_nat;
		return;
	case ntest_sort:
		o_ntest;
		return;
	case rounding_mode_sort:
		o_rounding_mode;
		return;
	case shape_sort:
		o_shape;
		return;
	case signed_nat_sort:
		o_signed_nat;
		return;
	case string_sort:
		o_string;
		return;
	case tag_sort:
		o_tag;
		return;
	case transfer_mode_sort:
		o_transfer_mode;
		return;
	case variety_sort:
		o_variety;
		return;
    }
    fail("Not a legal sort");
}

void
out_sort(Sort *s)
{
    if (s->sort != token_sort) {
	out_nontoksort(s->sort);
    } else {
	out_toksort(s->toksort);
    }
}

void
out_toksort(TokSort *ts)
{
    Tokpar *tp = ts->pars;
    o_token(
	out_sort(&ts->ressort),
	while (tp != (Tokpar *)0) {
	    LIST_ELEM(out_sort(&tp->par));
	    tp = tp->next;
	}
   );
}


void
analyse_sort(int sort)
{
    switch (sort) {
	case access_sort:
		read_access();
		return;
	case alignment_sort:
		read_alignment();
		return;
	case al_tag_sort:
		read_al_tag();
		return;
	case bitfield_variety_sort:
		read_bitfield_variety();
		return;
	case bool_sort:
		read_bool();
		return;
	case error_treatment_sort:
		read_error_treatment();
		return;
	case exp_sort:
		read_exp();
		return;
	case floating_variety_sort:
		read_floating_variety();
		return;
	case label_sort:
		read_label();
		return;
	case nat_sort:
		read_nat();
		return;
	case ntest_sort:
		read_ntest();
		return;
	case rounding_mode_sort:
		read_rounding_mode();
		return;
	case shape_sort:
		read_shape();
		return;
	case signed_nat_sort:
		read_signed_nat();
		return;
	case string_sort:
		read_string();
		return;
	case tag_sort:
		read_tag();
		return;
	case token_sort:
		read_token();
		return;
	case transfer_mode_sort:
		read_transfer_mode();
		return;
	case variety_sort:
		read_variety();
		return;
    }
    fail("Not a legal sort");
}


static void
tokp(Tokpar *tp)
{
    if (tp == (Tokpar *)0) {
	    return;
    }
    skip_term(lex_osq);
    analyse_sort(tp->par.sort);
    while ((tp=tp->next) != (Tokpar *)0) {
	skip_term(lex_comma);
	analyse_sort(tp->par.sort);
    }
    skip_term(lex_csq);
}


static void
tok(Tokdec *td)
{
    if (td->sort.ressort.sort != token_sort) {
	make_tok(&td->idname.name);
    } else {
	o_token_apply_token(make_tok(&td->idname.name), tokp(td->sort.pars));
	/* XXX: this only allow two levels */
    }
}

void
expand_tok(Tokdec *td, TokSort *ts)
{
    Tokpar *tp = ts->pars;
    switch (ts->ressort.sort) {
	case access_sort:
	    o_access_apply_token(tok(td), tokp(tp));
	    break;
	case alignment_sort:
	    o_alignment_apply_token(tok(td), tokp(tp));
	    break;
	case al_tag_sort:
	    o_al_tag_apply_token(tok(td), tokp(tp));
	    break;
	case bitfield_variety_sort:
	    o_bfvar_apply_token(tok(td), tokp(tp));
	    break;
	case bool_sort:
	    o_bool_apply_token(tok(td), tokp(tp));
	    break;
	case error_treatment_sort:
	    o_errt_apply_token(tok(td), tokp(tp));
	    break;
	case exp_sort:
	    o_exp_apply_token(tok(td), tokp(tp));
	    break;
	case floating_variety_sort:
	    o_flvar_apply_token(tok(td), tokp(tp));
	    break;
	case label_sort:
	    o_label_apply_token(tok(td), tokp(tp));
	    break;
	case nat_sort:
	    o_nat_apply_token(tok(td), tokp(tp));
	    break;
	case ntest_sort:
	    o_ntest_apply_token(tok(td), tokp(tp));
	    break;
	case rounding_mode_sort:
	    o_rounding_mode_apply_token(tok(td), tokp(tp));
	    break;
	case shape_sort:
	    o_shape_apply_token(tok(td), tokp(tp));
	    break;
	case signed_nat_sort:
	    o_signed_nat_apply_token(tok(td), tokp(tp));
	    break;
	case string_sort:
	    o_string_apply_token(tok(td), tokp(tp));
	    break;
	case tag_sort:
	    o_tag_apply_token(tok(td), tokp(tp));
	    break;
	case token_sort:
	    expand_tok(td, ts->ressort.toksort);
	    break;
	case transfer_mode_sort:
	    o_transfer_mode_apply_token(tok(td), tokp(tp));
	    break;
	case variety_sort:
	    o_var_apply_token(tok(td), tokp(tp));
	    break;
	default:
	    fail("Not a legal sort");
	    break;
    }
}
