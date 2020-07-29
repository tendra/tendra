/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/bool.h>
#include <shared/check.h>

#include <tdf/nat.h>
#include <tdf/tag.h>

#include <reader/basicread.h>
#include <reader/externs.h>
#include <reader/main_reads.h>

#include <construct/exp.h>
#include <construct/me_fns.h>
#include <construct/installglob.h>
#include <construct/install_fns.h>

#include <special/special_tok.h>

#include <main/flags.h>

#include <refactor/refactor.h>

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
	if (s->tag == apply_tag) {
		settoinline(s);
	}

	if (s->tag == ident_tag && son(s)->tag == clear_tag &&
	    bro(son(s))->tag == seq_tag &&
	    son(son(bro(son(s))))->tag == apply_tag) {
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

	{ "~asm",             BUILTIN_ASM,     special_asm             },
	{ "~asm_sequence",    BUILTIN_ASM,     special_asm_sequence    },
	{ "~asm_exp_input",   BUILTIN_ASM,     special_asm_exp_input   },
	{ "~asm_exp_output",  BUILTIN_ASM,     special_asm_exp_output  },
	{ "~asm_exp_address", BUILTIN_ASM,     special_asm_exp_address }
};

size_t special_toks_count = sizeof special_toks / sizeof * special_toks;

