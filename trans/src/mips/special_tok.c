/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/check.h>

#include <reader/code.h>
#include <reader/basicread.h>
#include <reader/c_arith_type.h>
#include <reader/messages_r.h>
#include <reader/main_reads.h>
#include <reader/externs.h>
#include <reader/special_tok.h>

#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/me_fns.h>
#include <construct/installglob.h>
#include <construct/install_fns.h>

#include <main/flags.h>

#include <diag3/diaginfo1.h>
#include <diag3/special_tok.h>

#include <refactor/refactor.h>

static bool
special_alloca(tokval *tkv, token t, bitstream pars)
{
	exp arg1;
	place old_place;

	old_place = keep_place();
	set_place(pars);

	arg1 = hold_refactor(d_exp());
	set_place(old_place);
	tkv->tk_exp = hold_refactor(me_u3(f_pointer(long_to_al(8)), arg1, alloca_tag));
	has_alloca = 1;

	return true;
}

static bool
special_exp_to_source(tokval *tkv, token t, bitstream pars)
{
	place old_place;
	diag_info *di;
	exp r;

	old_place = keep_place();
	set_place(pars);
	tkv->tk_exp = hold_refactor(d_exp());

	if (diag == DIAG_NONE) {
		set_place(old_place);
		return true;
	}

	di = read_exp_to_source();
	r = getexp(sh(tkv->tk_exp), NULL, 0, tkv->tk_exp, NULL, 1, 0, diagnose_tag);
	setfather(r, tkv->tk_exp);
	dno(r) = di;
	tkv->tk_exp = r;
	set_place(old_place);

	crt_lno    = natint(di->data.source.end.line_no);
	crt_charno = natint(di->data.source.end.char_off);
	crt_flnm   = di->data.source.beg.file->file.ints.chars;

	return true;
}

static bool
special_diag_id_scope(tokval *tkv, token t, bitstream pars)
{
	place old_place;
	diag_info *di;
	exp r;

	old_place = keep_place();
	set_place(pars);
	tkv->tk_exp = hold_refactor(d_exp());

	if (diag == DIAG_NONE) {
		set_place(old_place);
		return true;
	}

	di = read_diag_id_scope();
	r = getexp(sh(tkv->tk_exp), NULL, 0, tkv->tk_exp, NULL, 2, 0, diagnose_tag);
	setfather(r, tkv->tk_exp);
	dno(r) = di;
	tkv->tk_exp = r;
	set_place(old_place);

	return true;
}

static bool
special_diag_type_scope(tokval *tkv, token t, bitstream pars)
{
	place old_place;
	diag_info *di;
	exp r;

	old_place = keep_place();
	set_place(pars);
	tkv->tk_exp = hold_refactor(d_exp());

	if (diag == DIAG_NONE) {
		set_place(old_place);
		return true;
	}

	di = read_diag_type_scope();
	r = getexp(sh(tkv->tk_exp), NULL, 0, tkv->tk_exp, NULL, 3, 0, diagnose_tag);
	setfather(r, tkv->tk_exp);
	dno(r) = di;
	tkv->tk_exp = r;
	set_place(old_place);

	return true;
}

static bool
special_diag_tag_scope(tokval *tkv, token t, bitstream pars)
{
	place old_place;
	diag_info *di;
	exp r;

	old_place = keep_place();
	set_place(pars);
	tkv->tk_exp = hold_refactor(d_exp());

	if (diag == DIAG_NONE) {
		set_place(old_place);
		return true;
	}

	di = read_diag_tag_scope();
	r = getexp(sh(tkv->tk_exp), NULL, 0, tkv->tk_exp, NULL, 4, 0, diagnose_tag);
	setfather(r, tkv->tk_exp);
	dno(r) = di;
	tkv->tk_exp = r;
	set_place(old_place);

	return true;
}

const struct special_tok special_toks[] = {
	{ "~alloca",          BUILTIN_ALLOCA,  special_alloca          },

	{ "~exp_to_source",   BUILTIN_DIAG,    special_exp_to_source   },
	{ "~diag_id_scope",   BUILTIN_DIAG,    special_diag_id_scope   },
	{ "~diag_type_scope", BUILTIN_DIAG,    special_diag_type_scope },
	{ "~diag_tag_scope",  BUILTIN_DIAG,    special_diag_tag_scope  }
};

size_t special_toks_count = sizeof special_toks / sizeof *special_toks;

