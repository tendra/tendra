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
#include <reader/special_tok.h>

#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/me_fns.h>
#include <construct/installglob.h>
#include <construct/install_fns.h>

#include <main/flags.h>

#include <refactor/refactor.h>

#ifdef TDF_DIAG4
#include <diag4/special_tok.h>
#else
#include <diag3/diaginfo1.h>
#include <diag3/special_tok.h>
#endif

static bool
special_profile(tokval *tkv, token t, bitstream pars)
{
	nat n;
	place old_place;

	old_place = keep_place();
	set_place(pars);
	n = d_nat();

	set_place(old_place);
	tkv->tk_exp = f_profile(n);

	return true;
}

static bool
special_inline(tokval *tkv, token t, bitstream pars)
{
	exp s;
	place old_place;

	old_place = keep_place();
	set_place(pars);
	IGNORE d_shape();

	s = d_exp();
	if (name(s) == apply_tag) {
		settoinline(s);
	}

	if (name(s) == ident_tag && name(son(s)) == clear_tag &&
		name(bro(son(s))) == seq_tag &&
		name(son(son(bro(son(s))))) == apply_tag)
	{
		settoinline(son(son(bro(son(s)))));
	}

	s = hold_refactor(s);

	set_place(old_place);
	tkv->tk_exp = s;

	return true;
}

static bool
special_div(tokval *tkv, token t, bitstream pars)
{
	exp arg1, arg2;
	place old_place;

	old_place = keep_place();
	set_place(pars);

	arg1 = hold_refactor(d_exp());
	arg2 = hold_refactor(d_exp());

	set_place(old_place);
	tkv->tk_exp = me_b2(arg1, arg2, div0_tag);

	return true;
}

static bool
special_rem(tokval *tkv, token t, bitstream pars)
{
	exp arg1, arg2;
	place old_place;

	old_place = keep_place();
	set_place(pars);

	arg1 = hold_refactor(d_exp());
	arg2 = hold_refactor(d_exp());

	set_place(old_place);
	tkv->tk_exp = me_b2(arg1, arg2, rem0_tag);

	return true;
}

static bool
special_arith_type(tokval *tkv, token t, bitstream pars)
{
	int a, b;
	place old_place;
	signed_nat sn;

	old_place = keep_place();
	set_place(pars);

	sn = d_signed_nat(); a = snatint(sn);
	sn = d_signed_nat(); b = snatint(sn);

	set_place(old_place);
	snatint(sn) = arith_type(a, b);
	tkv->tk_signed_nat = sn;

	return true;
}

static bool
special_promote(tokval *tkv, token t, bitstream pars)
{
	int a;
	place old_place;
	signed_nat sn;

	old_place = keep_place();
	set_place(pars);

	sn = d_signed_nat();
	a = snatint(sn);

	set_place(old_place);
	snatint(sn) = promote(a);
	tkv->tk_signed_nat = sn;

	return true;
}

static bool
special_sign_promote(tokval *tkv, token t, bitstream pars)
{
	int a;
	place old_place;
	signed_nat sn;

	old_place = keep_place();
	set_place(pars);

	sn = d_signed_nat();
	a = snatint(sn);

	set_place(old_place);
	snatint(sn) = sign_promote(a);
	tkv->tk_signed_nat = sn;

	return true;
}

static bool
special_convert(tokval *tkv, token t, bitstream pars)
{
	int a;
	place old_place;
	signed_nat sn;

	old_place = keep_place();
	set_place(pars);

	sn = d_signed_nat();
	a = snatint(sn);

	set_place(old_place);
	tkv->tk_variety = convert((unsigned)a);

	return true;
}

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

static bool
special_asm(tokval *tkv, token t, bitstream pars)
{
	int prp;
	exp arg1;
	place old_place;

	old_place = keep_place();

	prp = 1;
	set_place(pars);
	arg1 = hold_refactor(f_make_nof_int(ucharsh, d_string()));

	set_place(old_place);
	tkv->tk_exp = getexp(f_top, NULL, 0, arg1, NULL, prp, 0, asm_tag);
	setfather(tkv->tk_exp, arg1);

	return true;
}

static bool
special_asm_sequence(tokval *tkv, token t, bitstream pars)
{
	int prp;
	exp arg1;
	place old_place;

	old_place = keep_place();

	prp = 0;
	set_place(pars);
	arg1 = hold_refactor(d_exp());

	set_place(old_place);
	tkv->tk_exp = getexp(f_top, NULL, 0, arg1, NULL, prp, 0, asm_tag);
	setfather(tkv->tk_exp, arg1);

	return true;
}

static bool
special_asm_exp_input(tokval *tkv, token t, bitstream pars)
{
	int prp;
	exp arg1;
	place old_place;

	old_place = keep_place();

	prp = 2;
	set_place(pars);
	arg1 = hold_refactor(d_exp());

	set_place(old_place);
	tkv->tk_exp = getexp(f_top, NULL, 0, arg1, NULL, prp, 0, asm_tag);
	setfather(tkv->tk_exp, arg1);

	return true;
}

static bool
special_asm_exp_output(tokval *tkv, token t, bitstream pars)
{
	int prp;
	exp arg1;
	place old_place;

	old_place = keep_place();

	prp = 4;
	set_place(pars);
	arg1 = hold_refactor(d_exp());

	set_place(old_place);
	tkv->tk_exp = getexp(f_top, NULL, 0, arg1, NULL, prp, 0, asm_tag);
	setfather(tkv->tk_exp, arg1);

	return true;
}

static bool
special_asm_exp_address(tokval *tkv, token t, bitstream pars)
{
	int prp;
	exp arg1;
	place old_place;

	old_place = keep_place();

	prp = 8;
	set_place(pars);
	arg1 = hold_refactor(d_exp());

	set_place(old_place);
	tkv->tk_exp = getexp(f_top, NULL, 0, arg1, NULL, prp, 0, asm_tag);
	setfather(tkv->tk_exp, arg1);

	return true;
}

const struct special_tok special_toks[] = {
	{ "JMFprofile",       BUILTIN_DEBUG,   special_profile         },
	{ "JMFinline",        BUILTIN_DEBUG,   special_inline          },

	{ "~div",             BUILTIN_DIV,     special_div             },
	{ "~rem",             BUILTIN_DIV,     special_rem             },

	{ "~arith_type",      BUILTIN_PROMOTE, special_arith_type      },
	{ "~promote",         BUILTIN_PROMOTE, special_promote         },
	{ "~sign_promote",    BUILTIN_PROMOTE, special_sign_promote    },
	{ "~convert",         BUILTIN_PROMOTE, special_convert         },

	{ "~alloca",          BUILTIN_ALLOCA,  special_alloca          },

	{ "~exp_to_source",   BUILTIN_DIAG,    special_exp_to_source   },
	{ "~diag_id_scope",   BUILTIN_DIAG,    special_diag_id_scope   },
	{ "~diag_type_scope", BUILTIN_DIAG,    special_diag_type_scope },
	{ "~diag_tag_scope",  BUILTIN_DIAG,    special_diag_tag_scope  },
#ifdef TDF_DIAG4
	{ "~dg_exp",          BUILTIN_DIAG,    special_dg_exp          },
#endif

	{ "~asm",             BUILTIN_ASM,     special_asm             },
	{ "~asm_sequence",    BUILTIN_ASM,     special_asm_sequence    },
	{ "~asm_exp_input",   BUILTIN_ASM,     special_asm_exp_input   },
	{ "~asm_exp_output",  BUILTIN_ASM,     special_asm_exp_output  },
	{ "~asm_exp_address", BUILTIN_ASM,     special_asm_exp_address }
};

size_t special_toks_count = sizeof special_toks / sizeof *special_toks;

