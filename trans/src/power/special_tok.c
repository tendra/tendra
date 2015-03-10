/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

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

const struct special_tok special_toks[] = {
	{ "~alloca", BUILTIN_ALLOCA, special_alloca }
};

size_t special_toks_count = sizeof special_toks / sizeof *special_toks;

