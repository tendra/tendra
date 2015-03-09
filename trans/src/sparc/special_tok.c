/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stddef.h>

#include <shared/check.h>
#include <shared/error.h>

#include <reader/code.h>
#include <reader/basicread.h>
#include <reader/externs.h>
#include <reader/messages_r.h>
#include <reader/main_reads.h>
#include <reader/c_arith_type.h>

#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/shape.h>
#include <construct/me_fns.h>
#include <construct/installglob.h>
#include <construct/install_fns.h>

#include <special/special_tok.h>

#include <main/flags.h>

#ifdef TDF_DIAG4
#include <diag4/special_tok.h>
#else
#include <diag3/diaginfo1.h>
#include <diag3/special_tok.h>
#endif

#include <refactor/refactor.h>

#include "translate.h"
#include "scan.h"
#include "new_tags.h"

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
	env_o = getexp(f_offset(f_callers_alignment(1), f_alignment(sh(arg1))),
				   NULL, 0, id, NULL, 0, 0, env_offset_tag);
	setvis(id);
	setenvoff(id);

	tkv->tk_exp = hold_refactor(f_add_to_ptr(f_current_env(), env_o));
	kill_exp(arg1,arg1);

	return true;
}

static bool
special_va_arg(tokval *tkv, token t, bitstream pars)
{
	exp arg1;
	shape s, s1;
	exp id, ass, con;
	exp_list el;

	place old_place;
	old_place = keep_place();
	set_place(pars);
	arg1 = hold_refactor(d_exp());
	s = d_shape();
	set_place(old_place);

	s1 = s;
	if (sparccpd(s)) {
		s1 = f_pointer (f_alignment (s));
	}

	id = me_startid(f_pointer(f_var_param_alignment), arg1, 0);
	ass = f_assign(me_obtain(id),
				   f_add_to_ptr(f_contents(f_pointer(f_var_param_alignment), me_obtain(id)),
								f_offset_pad(f_var_param_alignment, f_shape_offset (s1))));
	con = f_contents(s1,
					 f_add_to_ptr(f_contents(f_pointer(f_var_param_alignment), me_obtain(id)),
								  f_offset_negate(f_offset_pad(f_var_param_alignment, f_shape_offset(s1)))));
	if (sparccpd(s)) {
		con = f_contents (s, con);
	}
	el = new_exp_list(1);
	el = add_exp_list(el, ass, 0);

	tkv->tk_exp = hold_refactor(me_complete_id (id, f_sequence (el, con)));

	return true;
}

static bool
special_next_caller_offset(tokval *tkv, token t, bitstream pars)
{
	exp arg1;
	shape s1, s2;
	place old_place;

	old_place = keep_place();
	set_place(pars);
	arg1 = hold_refactor(d_exp());

	s1 = d_shape();
	s2 = d_shape();
	set_place(old_place);
	caller_offset_used = 1;

	if (sparccpd(s1)) {
		s1 = f_pointer(f_alignment(s1));
	}

	tkv->tk_exp = hold_refactor(f_offset_pad(f_parameter_alignment(s2),
								f_offset_add(arg1, f_shape_offset(s1))));
	return true;
}

static bool
special_next_callee_offset(tokval *tkv, token t, bitstream pars)
{
	exp arg1;
	shape s1, s2;
	place old_place;

	old_place = keep_place();
	set_place(pars);
	arg1 = hold_refactor(d_exp());

	s1 = d_shape();
	s2 = d_shape();
	set_place(old_place);

	tkv->tk_exp = hold_refactor(f_offset_pad(f_parameter_alignment(s2),
								f_offset_pad(f_alignment(s2),
											 f_offset_add(arg1, f_shape_offset(s1)))));
	return true;
}

static bool
special_sync_handler(tokval *tkv, token t, bitstream pars)
{
	tkv->tk_exp = getexp(f_top, NULL, 0, NULL, NULL, 0, 0, special_tag);

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
special_sparc(tokval *tkv, token t, bitstream pars)
{
	exp arg;
	place old_place;

	old_place = keep_place();
	set_place(pars);
	arg = d_exp();
	assert(name(arg) == val_tag);

	if (no(arg) == 0) {
		tkv->tk_exp = getexp(f_bottom, NULL, 0, NULL, NULL, 0, 0, special_tag);
	} else {
		error(ERR_INTERNAL, "Unsupported argument to token __sparc_special");
		tkv->tk_exp = getexp(f_top, NULL, 0, NULL, NULL, 0, 0, null_tag);
	}

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
	{ "c89.stdarg.__va_start", BUILTIN_VARARG, special_va_start    },
	{ "c89.stdarg.va_arg",     BUILTIN_VARARG, special_va_arg      },

	{ "~next_caller_offset",   0, special_next_caller_offset       },
	{ "~next_callee_offset",   0, special_next_callee_offset       },
	{ "~Sync_handler",         0, special_sync_handler             },

	{ "~alloca",          BUILTIN_ALLOCA,  special_alloca          },

	{ "~exp_to_source",   BUILTIN_DIAG,    special_exp_to_source   },
	{ "~diag_id_scope",   BUILTIN_DIAG,    special_diag_id_scope   },
	{ "~diag_type_scope", BUILTIN_DIAG,    special_diag_type_scope },
	{ "~diag_tag_scope",  BUILTIN_DIAG,    special_diag_tag_scope  },
#ifdef TDF_DIAG4
	{ "~dg_exp",          BUILTIN_DIAG,    special_dg_exp          },
#endif

	/* XXX: is this redundant wrt ~asm* below? */
	{ "__sparc_special",  BUILTIN_ASM,     special_sparc           },
	{ "~asm",             BUILTIN_ASM,     special_asm             },
	{ "~asm_sequence",    BUILTIN_ASM,     special_asm_sequence    },
	{ "~asm_exp_input",   BUILTIN_ASM,     special_asm_exp_input   },
	{ "~asm_exp_output",  BUILTIN_ASM,     special_asm_exp_output  },
	{ "~asm_exp_address", BUILTIN_ASM,     special_asm_exp_address }
};

size_t special_toks_count = sizeof special_toks / sizeof *special_toks;

