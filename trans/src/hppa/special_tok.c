/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <local/al.h>

#include <tdf/nat.h>
#include <tdf/shape.h>
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
special_va_start(tokval *tkv, token t, bitstream pars)
{
	exp arg1;
	exp id;
	exp env_o;

	place old_place;
	old_place = keep_place();
	set_place(pars);
	arg1 = hold_refactor(d_exp());
	set_place(old_place);

	if (arg1->tag != name_tag) {
		error(ERR_INTERNAL, "Not a tag in va_start");
	}

	id = son(arg1);

	env_o = getexp(f_offset(frame_alignment, f_alignment(sh(arg1))),
	               NULL, 0, id, NULL, 0, 0, env_offset_tag);
	setvis(id);
	setenvoff(id);
	tkv->tk_exp = hold_refactor(f_add_to_ptr(f_add_to_ptr(f_current_env(), env_o), f_shape_offset(sh(arg1))));
	kill_exp(arg1, arg1);

	return true;
}

static bool
special_next_caller_offset(tokval *tkv, token t, bitstream pars)
{
	exp arg1, arg2;
	shape sha1, sha2, sha3;
	place old_place;

	old_place = keep_place();
	set_place(pars);
	arg1 = hold_refactor(d_exp());
	sha1 = d_shape();
	sha2 = d_shape();
	set_place(old_place);

	sha3 = (shape_size(sha2) > 64 ? f_pointer(f_alignment(sha2)) :
	       (shape_size(sha2) < 32 ? swordsh : sha2));
	arg2 = hold_refactor(f_offset_pad(f_parameter_alignment(sha3),
	                                  f_shape_offset(sha3)));

	if ((shape_size(sha1) <= 32 || shape_size(sha1) > 64) && shape_size(sha3) == 64) {
		arg1 = hold_refactor(f_offset_pad(f_parameter_alignment(realsh), arg1));
	}

	tkv->tk_exp = hold_refactor(me_b3(f_offset(al1_of(sh(arg1)),
	                                  al2_of(sh(arg2))),
	                                  arg1, arg2, offset_subtract_tag));

	if (shape_size(sha2) > 64) {
		al2_of(sh(tkv->tk_exp))->al.sh_hd = nofhd + 1;
	}

	return 1;
}

static bool
special_next_callee_offset(tokval *tkv, token t, bitstream pars)
{
	exp arg1, arg2, off;
	shape sha1, sha2;
	place old_place;

	old_place = keep_place();
	set_place(pars);
	arg1 = hold_refactor(d_exp());
	sha1 = d_shape();
	sha2 = d_shape();
	set_place(old_place);

	arg2 = hold_refactor(f_offset_pad(f_parameter_alignment(sha1), f_shape_offset(sha1)));
	off  = hold_refactor(me_b3(f_offset(al1_of(sh(arg1)),
	                                    al2_of(sh(arg2))), arg1, arg2, offset_add_tag));

	if (shape_align(sha1) < shape_align(sha2)) {
		tkv->tk_exp = hold_refactor(f_offset_pad(f_parameter_alignment(sha2), off));
	} else {
		tkv->tk_exp = off;
	}

	return true;
}

const struct special_tok special_toks[] = {
	{ "c89.stdarg.__va_start", BUILTIN_VARARG, special_va_start   },

	/* TODO: BUILTIN_? */
	{ "__trans_next_caller_offset", 0, special_next_caller_offset },
	{ "__trans_next_callee_offset", 0, special_next_callee_offset }
};

size_t special_toks_count = sizeof special_toks / sizeof * special_toks;

