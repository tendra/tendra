/* $Id$ */

/*
 * Copyright 2011-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <string.h>

#include <shared/check.h>
#include <shared/error.h>

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

int
special_token ( tokval *tkv, token t, bitstream pars, int sortcode )
{
	UNUSED(sortcode);

	if (t -> tok_name == NULL) {
		return 0;
	}

	if (builtin & BUILTIN_VARARG) {
		if (!strcmp(t -> tok_name,"c89.stdarg.__va_start") ) {
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
			return 1;
		}

		if (!strcmp(t -> tok_name,"c89.stdarg.va_arg") ) {
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
			return 1;
		}
	}


	/* TODO: BUILTIN_? */ {
		if (!strcmp(t -> tok_name,"~next_caller_offset") ) {
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
			return 1;
		}

		if (!strcmp(t -> tok_name,"~next_callee_offset") ) {
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
			return 1;
		}
	}

	if (builtin & BUILTIN_ALLOCA) {
		if (!strcmp(t -> tok_name, "~alloca"))  {
			exp arg1;
			place old_place;

			old_place = keep_place();
			set_place(pars);
			arg1 = hold_refactor(d_exp());
			set_place(old_place);

			tkv->tk_exp = hold_refactor(me_u3(f_pointer(long_to_al(8)),
			                                  arg1, alloca_tag));
			has_alloca = 1;
			return 1;
		}
	}

	/* TODO: BUILTIN_? */ {
		if (!strcmp(t->tok_name, "~Sync_handler")) {
			tkv->tk_exp = getexp(f_top, NULL, 0, NULL, NULL, 0, 0, special_tag);
			return 1;
		}
	}

	/* XXX: is this redundant wrt ~asm* below? */
	if (builtin & BUILTIN_ASM) {
		if (!strcmp(t->tok_name, "__sparc_special")) {
			exp arg;
			place old_place;

			old_place = keep_place();
			set_place(pars);
			arg = d_exp();
			assert(name(arg) == val_tag);

			if(no(arg) == 0) {
				tkv->tk_exp = getexp(f_bottom, NULL, 0, NULL, NULL, 0, 0, special_tag);
			} else {
				error(ERR_INTERNAL, "Unsupported argument to token __sparc_special");
				tkv->tk_exp = getexp(f_top, NULL, 0, NULL, NULL, 0, 0, null_tag);
			}

			set_place(old_place);
			return 1;
		}
	}

	if (builtin & BUILTIN_DIAG) {
		if (!strcmp(t -> tok_name, "~exp_to_source") ||
		    !strcmp(t -> tok_name, "~diag_id_scope") ||
		    !strcmp(t -> tok_name, "~diag_type_scope") ||
		    !strcmp(t -> tok_name, "~diag_tag_scope")
#ifdef TDF_DIAG4
		    || !strcmp(t -> tok_name, "~dg_exp")
#endif
		   )  {

			place old_place;
			old_place = keep_place();
			set_place(pars);
			tkv->tk_exp = hold_refactor(d_exp());

			if (diag == DIAG_NONE) {
				set_place(old_place);
				return 1;
			}

			if (!strcmp(t -> tok_name, "~exp_to_source")) {
#ifdef TDF_DIAG4
				tkv->tk_exp = read_exp_to_source (tkv->tk_exp);
#else
				diag_info * di = read_exp_to_source();
				exp r = getexp(sh(tkv->tk_exp), NULL, 0, tkv->tk_exp, NULL,
				               1, 0, diagnose_tag);
				setfather(r, tkv->tk_exp);
				dno(r) = di;
				tkv->tk_exp = r;

				crt_lno = natint(di -> data.source.end.line_no);
				crt_charno = natint(di -> data.source.end.char_off);
				crt_flnm = di -> data.source.beg.file->file.ints.chars;
#endif
				set_place(old_place);
				return 1;
			}

			if (!strcmp(t -> tok_name, "~diag_id_scope")) {
#ifdef TDF_DIAG4
				tkv->tk_exp = read_diag_id_scope (tkv->tk_exp);
#else
				diag_info * di = read_diag_id_scope();
				exp r = getexp(sh(tkv->tk_exp), NULL, 0, tkv->tk_exp, NULL,
				               2, 0, diagnose_tag);
				setfather(r, tkv->tk_exp);
				dno(r) = di;
				tkv->tk_exp = r;
#endif
				set_place(old_place);
				return 1;
			}

			if (!strcmp(t -> tok_name, "~diag_type_scope")) {
#ifdef TDF_DIAG4
				tkv->tk_exp = read_diag_type_scope (tkv->tk_exp);
#else
				diag_info * di = read_diag_type_scope();
				exp r = getexp(sh(tkv->tk_exp), NULL, 0, tkv->tk_exp, NULL,
				               3, 0, diagnose_tag);
				setfather(r, tkv->tk_exp);
				dno(r) = di;
				tkv->tk_exp = r;
#endif
				set_place(old_place);
				return 1;
			}

			if (!strcmp(t -> tok_name, "~diag_tag_scope")) {
#ifndef TDF_DIAG4
				diag_info * di = read_diag_tag_scope();
				exp r = getexp(sh(tkv->tk_exp), NULL, 0, tkv->tk_exp, NULL,
				               4, 0, diagnose_tag);
				setfather(r, tkv->tk_exp);
				dno(r) = di;
				tkv->tk_exp = r;
#endif
				set_place(old_place);
				return 1;
			}

#ifdef TDF_DIAG4
			if (!strcmp(t -> tok_name, "~dg_exp")) {
				tkv->tk_exp = read_dg_exp (tkv->tk_exp);
				set_place(old_place);
				return 1;
			}
#endif
		}
	}

	if (builtin & BUILTIN_ASM) {
		if (!strncmp(t -> tok_name, "~asm", 4)) {
			int prp;
			exp arg1;
			place old_place;

			old_place = keep_place();

			if (!strcmp(t -> tok_name, "~asm")) {
				set_place(pars);
				arg1 = hold_refactor(f_make_nof_int (ucharsh, d_string()));
				prp = 1;
			} else {
				if (!strcmp(t -> tok_name, "~asm_sequence")) {
					prp = 0;
				} else if (!strcmp(t -> tok_name, "~asm_exp_input")) {
					prp = 2;
				} else if (!strcmp(t -> tok_name, "~asm_exp_output")) {
					prp = 4;
				} else if (!strcmp(t -> tok_name, "~asm_exp_address")) {
					prp = 8;
				} else {
					return 1;
				}
				set_place(pars);
				arg1 = hold_refactor(d_exp());
			}

			set_place(old_place);

			tkv->tk_exp = getexp (f_top, NULL, 0, arg1, NULL, prp, 0, asm_tag);
			setfather (tkv->tk_exp, arg1);
			return 1;
		}
	}

	return 0;
}

