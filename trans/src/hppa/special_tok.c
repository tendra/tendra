/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/check.h>
#include <shared/error.h>

#include <local/szs_als.h>

#include <reader/code.h>
#include <reader/basicread.h>
#include <reader/externs.h>
#include <reader/messages_r.h>
#include <reader/main_reads.h>
#include <reader/c_arith_type.h>
#include <reader/special_tok.h>

#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/shape.h>
#include <construct/me_fns.h>
#include <construct/installglob.h>
#include <construct/install_fns.h>

#include <main/flags.h>

#include <diag3/diaginfo1.h>
#include <diag3/special_tok.h>

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

	if (name(arg1) != name_tag) {
		error(ERR_INTERNAL, "Not a tag in va_start");
	}

	id = son(arg1);

	env_o = getexp(f_offset(frame_alignment, f_alignment(sh(arg1))),
				   NULL, 0, id, NULL, 0, 0, env_offset_tag);
	setvis(id);
	setenvoff(id);
	tkv->tk_exp = hold_refactor(f_add_to_ptr(f_add_to_ptr(f_current_env(), env_o),f_shape_offset(sh(arg1))));
	kill_exp(arg1,arg1);

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

	if (shape_size(sha2)>64) {
		al2_of(sh(tkv->tk_exp))->al.sh_hd = nofhd+1;
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
		tkv->tk_exp = hold_refactor(f_offset_pad(f_parameter_alignment(sha2),off));
	} else {
		tkv->tk_exp = off;
	}

	return true;
}

static bool
special_alloc_size(tokval *tkv, token t, bitstream pars)
{
	exp off,off1,arg1;
	place old_place;

	old_place = keep_place();
	set_place(pars);

	arg1 = hold_refactor(d_exp());
	set_place(old_place);

	off1 = hold_refactor(f_offset_pad(SLONG_ALIGN, arg1));
	off  = hold_refactor(me_b3(f_offset(al1_of(sh(off1)), SLONG_ALIGN),
							  off1, f_shape_offset(slongsh), offset_add_tag));

	tkv->tk_exp = hold_refactor(f_offset_pad(const_al512, off));

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

struct special_tok special_toks[] = {
	{ "c89.stdarg.__va_start", BUILTIN_VARARG, special_va_start    },

	/* TODO: BUILTIN_? */
	{ "__trans_next_caller_offset", 0, special_next_caller_offset  },
	{ "__trans_next_callee_offset", 0, special_next_callee_offset  },

	{ "~alloc_size",      BUILTIN_ALLOCA,  special_alloc_size      },
	{ "~alloca",          BUILTIN_ALLOCA,  special_alloca          },

	{ "~exp_to_source",   BUILTIN_DIAG,    special_exp_to_source   },
	{ "~diag_id_scope",   BUILTIN_DIAG,    special_diag_id_scope   },
	{ "~diag_type_scope", BUILTIN_DIAG,    special_diag_type_scope },
	{ "~diag_tag_scope",  BUILTIN_DIAG,    special_diag_tag_scope  }
};

size_t special_toks_count = sizeof special_toks / sizeof *special_toks;

