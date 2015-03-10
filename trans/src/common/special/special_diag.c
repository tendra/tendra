/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
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

#ifdef TDF_DIAG3
static bool
special_diag3(tokval *tkv, token t, bitstream pars,
	diag_info *(*f)(void), prop p)
{
	place old_place;
	diag_info *di;
	exp r;

	assert(f != NULL);

	old_place = keep_place();
	set_place(pars);
	tkv->tk_exp = hold_refactor(d_exp());

	if (diag == DIAG_NONE) {
		set_place(old_place);
		return true;
	}

	di = f();
	r = getexp(sh(tkv->tk_exp), NULL, 0, tkv->tk_exp, NULL, p, 0, diagnose_tag);
	setfather(r, tkv->tk_exp);
	dno(r) = di;
	tkv->tk_exp = r;
	set_place(old_place);

	if (p == 1) {
		crt_lno    = natint(di->data.source.end.line_no);
		crt_charno = natint(di->data.source.end.char_off);
		crt_flnm   = di->data.source.beg.file->file.ints.chars;
	}

	return true;
}
#endif

#ifdef TDF_DIAG4
static bool
special_diag4(tokval *tkv, token t, bitstream pars,
	exp (*f)(exp))
{
	place old_place;

	old_place = keep_place();
	set_place(pars);
	tkv->tk_exp = hold_refactor(d_exp());

	if (diag == DIAG_NONE) {
		set_place(old_place);
		return true;
	}

	if (f != NULL) {
		tkv->tk_exp = f(tkv->tk_exp);
	}

	set_place(old_place);

	return true;
}
#endif

static bool
special_exp_to_source(tokval *tkv, token t, bitstream pars)
{
#ifdef TDF_DIAG3
	return special_diag3(tkv, t, pars, read_exp_to_source, 1);
#endif

#ifdef TDF_DIAG4
	return special_diag4(tkv, t, pars, read_exp_to_source);
#endif

	return false;
}

static bool
special_diag_id_scope(tokval *tkv, token t, bitstream pars)
{
#ifdef TDF_DIAG3
	return special_diag3(tkv, t, pars, read_diag_id_scope, 2);
#endif

#ifdef TDF_DIAG4
	return special_diag4(tkv, t, pars, read_diag_id_scope);
#endif

	return false;
}

static bool
special_diag_type_scope(tokval *tkv, token t, bitstream pars)
{
#ifdef TDF_DIAG3
	return special_diag3(tkv, t, pars, read_diag_type_scope, 3);
#endif

#ifdef TDF_DIAG4
	return special_diag4(tkv, t, pars, read_diag_type_scope);
#endif

	return false;
}

static bool
special_diag_tag_scope(tokval *tkv, token t, bitstream pars)
{
#ifdef TDF_DIAG3
	return special_diag3(tkv, t, pars, read_diag_tag_scope, 4);
#endif

#ifdef TDF_DIAG4
	return special_diag4(tkv, t, pars, NULL);
#endif

	return false;
}

#ifdef TDF_DIAG4
static bool
special_dg_exp(tokval *tkv, token t, bitstream pars)
{
	return special_diag4(tkv, t, pars,
		read_dg_exp);
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

