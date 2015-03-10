/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/bool.h>
#include <shared/check.h>

#include <reader/code.h>
#include <reader/basicread.h>
#include <reader/externs.h>
#include <reader/messages_r.h>
#include <reader/main_reads.h>
#include <reader/c_arith_type.h>

#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/me_fns.h>
#include <construct/installglob.h>
#include <construct/install_fns.h>

#include <special/special_tok.h>

#include <main/flags.h>

#include <refactor/refactor.h>

#ifdef TDF_DIAG4
#include <diag4/special_tok.h>
#else
#include <diag3/diaginfo1.h>
#include <diag3/special_tok.h>
#endif

static bool
special_exp_to_source(tokval *tkv, token t, bitstream pars)
{
	place old_place;
#ifndef TDF_DIAG4
	diag_info *di;
	exp r;
#endif

	old_place = keep_place();
	set_place(pars);
	tkv->tk_exp = hold_refactor(d_exp());

	if (diag == DIAG_NONE) {
		set_place(old_place);
		return true;
	}

#ifdef TDF_DIAG4
	tkv->tk_exp = read_exp_to_source(tkv->tk_exp);
#else
	di = read_exp_to_source();
	r = getexp(sh(tkv->tk_exp), NULL, 0, tkv->tk_exp, NULL, 1, 0, diagnose_tag);
	setfather(r, tkv->tk_exp);
	dno(r) = di;
	tkv->tk_exp = r;
#endif
	set_place(old_place);

#ifndef TDF_DIAG4
	crt_lno    = natint(di->data.source.end.line_no);
	crt_charno = natint(di->data.source.end.char_off);
	crt_flnm   = di->data.source.beg.file->file.ints.chars;
#endif

	return true;
}

static bool
special_diag_id_scope(tokval *tkv, token t, bitstream pars)
{
	place old_place;
#ifndef TDF_DIAG4
	diag_info *di;
	exp r;
#endif

	old_place = keep_place();
	set_place(pars);
	tkv->tk_exp = hold_refactor(d_exp());

	if (diag == DIAG_NONE) {
		set_place(old_place);
		return true;
	}

#ifdef TDF_DIAG4
	tkv->tk_exp = read_diag_id_scope(tkv->tk_exp);
#else
	di = read_diag_id_scope();
	r = getexp(sh(tkv->tk_exp), NULL, 0, tkv->tk_exp, NULL, 2, 0, diagnose_tag);
	setfather(r, tkv->tk_exp);
	dno(r) = di;
	tkv->tk_exp = r;
#endif
	set_place(old_place);

	return true;
}

static bool
special_diag_type_scope(tokval *tkv, token t, bitstream pars)
{
	place old_place;
#ifndef TDF_DIAG4
	diag_info *di;
	exp r;
#endif

	old_place = keep_place();
	set_place(pars);
	tkv->tk_exp = hold_refactor(d_exp());

	if (diag == DIAG_NONE) {
		set_place(old_place);
		return true;
	}

#ifdef TDF_DIAG4
	tkv->tk_exp = read_diag_type_scope(tkv->tk_exp);
#else
	di = read_diag_type_scope();
	r = getexp(sh(tkv->tk_exp), NULL, 0, tkv->tk_exp, NULL, 3, 0, diagnose_tag);
	setfather(r, tkv->tk_exp);
	dno(r) = di;
	tkv->tk_exp = r;
#endif
	set_place(old_place);

	return true;
}

static bool
special_diag_tag_scope(tokval *tkv, token t, bitstream pars)
{
	place old_place;
#ifndef TDF_DIAG4
	diag_info *di;
	exp r;
#endif

	old_place = keep_place();
	set_place(pars);
	tkv->tk_exp = hold_refactor(d_exp());

	if (diag == DIAG_NONE) {
		set_place(old_place);
		return true;
	}

#ifndef TDF_DIAG4
	di = read_diag_tag_scope();
	r = getexp(sh(tkv->tk_exp), NULL, 0, tkv->tk_exp, NULL, 4, 0, diagnose_tag);
	setfather(r, tkv->tk_exp);
	dno(r) = di;
	tkv->tk_exp = r;
#endif
	set_place(old_place);

	return true;
}

#ifdef TDF_DIAG4
static bool
special_dg_exp(tokval *tkv, token t, bitstream pars)
{
	place old_place;

	old_place = keep_place();
	set_place(pars);
	tkv->tk_exp = hold_refactor(d_exp());

	if (diag == DIAG_NONE) {
		set_place(old_place);
		return true;
	}

	tkv->tk_exp = read_dg_exp(tkv->tk_exp);
	set_place(old_place);

	return true;
}
#endif

const struct special_tok special_diags[] = {
	{ "~exp_to_source",   BUILTIN_DIAG, special_exp_to_source   },
	{ "~diag_id_scope",   BUILTIN_DIAG, special_diag_id_scope   },
	{ "~diag_type_scope", BUILTIN_DIAG, special_diag_type_scope },
	{ "~diag_tag_scope",  BUILTIN_DIAG, special_diag_tag_scope  },
#ifdef TDF_DIAG4
	{ "~dg_exp",          BUILTIN_DIAG, special_dg_exp          }
#endif
};

size_t special_diags_count = sizeof special_diags / sizeof *special_diags;

