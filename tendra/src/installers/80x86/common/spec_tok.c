/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


#include "config.h"
#include "common_types.h"
#include "basicread.h"
#include "tags.h"
#include "exp.h"
#include "expmacs.h"
#include "diag_fns.h"
#include "flags.h"
#include "check.h"
#include "me_fns.h"
#include "externs.h"
#include "installglob.h"
#include "main_reads.h"
#include "install_fns.h"
#include "c_arith_type.h"
#include "natmacs.h"
#include "spec_tok.h"
#include "dg_fns.h"


/* intercepts specially defined tokens */

tokval
special_token(token t, bitstream pars, int sortcode, int * done)
{
	tokval tkv;
	UNUSED(sortcode);

	if (t->tok_name == (char*)0) {
		SET(tkv); /* call looks at done to see if result is meaningful */
		return tkv;
	}

	if (strcmp(t->tok_name, "JMFprofile") == 0)  {
		nat n;

		n = d_nat();

		tkv.tk_exp = f_profile(n);
		*done = 1;
		return tkv;
	}
	if (strcmp(t->tok_name, "JMFinline") == 0)  {
		exp s;

		IGNORE d_shape();
		s = d_exp();
		if (name(s) == apply_tag)
			settoinline(s);
		if (name(s) == ident_tag && name(son(s)) == clear_tag &&
			name(bro(son(s))) == seq_tag &&
			name(son(son(bro(son(s))))) == apply_tag)
			settoinline(son(son(bro(son(s)))));


		s = hold_check(s);

		tkv.tk_exp = s;
		*done = 1;
		return tkv;
	}
	if (strcmp(t->tok_name, "~div") == 0)  {
		exp arg1, arg2;

		arg1 = hold_check(d_exp());
		arg2 = hold_check(d_exp());

		tkv.tk_exp = me_b2(arg1, arg2, div0_tag);
		*done = 1;
		return tkv;
	}
	if (strcmp(t->tok_name, "~rem") == 0)  {
		exp arg1, arg2;

		arg1 = hold_check(d_exp());
		arg2 = hold_check(d_exp());

		tkv.tk_exp = me_b2(arg1, arg2, rem0_tag);
		*done = 1;
		return tkv;
	}
#ifdef INBUILT_PROMOTE
	if (strcmp(t->tok_name, "~arith_type") == 0) {
		int a, b;
		signed_nat sn;

		sn = d_signed_nat();
		a = snatint(sn);
		sn = d_signed_nat();
		b = snatint(sn);
		snatint(sn) = arith_type(a, b);
		tkv.tk_signed_nat = sn;
		*done = 1;
		return tkv;
	}
	if (strcmp(t->tok_name, "~promote") == 0) {
		int a;
		signed_nat sn;

		sn = d_signed_nat();
		a = snatint(sn);
		snatint(sn) = promote(a);
		tkv.tk_signed_nat = sn;
		*done = 1;
		return tkv;
	}
	if (strcmp(t->tok_name, "~sign_promote") == 0) {
		int a;
		signed_nat sn;

		sn = d_signed_nat();
		a = snatint(sn);
		snatint(sn) = sign_promote(a);
		tkv.tk_signed_nat = sn;
		*done = 1;
		return tkv;
	}
	if (strcmp(t->tok_name, "~convert") == 0) {
		int a;
		signed_nat sn;

		sn = d_signed_nat();
		a = snatint(sn);
		tkv.tk_variety = convert((unsigned)a);
		*done = 1;
		return tkv;
	}
#endif
	if (strcmp(t->tok_name, "~alloca") == 0)  {
		exp arg1;

		arg1 = hold_check(d_exp());
		tkv.tk_exp = hold_check(me_u3(f_pointer(long_to_al(8)),
									  arg1, alloca_tag));
		*done = 1;
		has_alloca = 1;
		return tkv;
	}

	if (strcmp(t->tok_name, "~exp_to_source") == 0 ||
		strcmp(t->tok_name, "~diag_id_scope") == 0 ||
		strcmp(t->tok_name, "~diag_type_scope") == 0 ||
		strcmp(t->tok_name, "~diag_tag_scope") == 0
#ifdef NEWDIAGS
		|| strcmp(t->tok_name, "~dg_exp") == 0
#endif
		)  {
		tkv.tk_exp = hold_check(d_exp());
		*done = 1;

		if (!diagnose)
			return tkv;

		if (strcmp(t->tok_name, "~exp_to_source") == 0) {
#ifdef NEWDIAGS
			tkv.tk_exp = read_exp_to_source (tkv.tk_exp);
#else
			diag_info * di = read_exp_to_source();
			exp r = getexp(sh(tkv.tk_exp), nilexp, 0, tkv.tk_exp, nilexp,
						   1, 0, diagnose_tag);
			setfather(r, tkv.tk_exp);
			dno(r) = di;
			tkv.tk_exp = r;
			crt_lno = natint(di->data.source.end.line_no);
			crt_charno = natint(di->data.source.end.char_off);
			crt_flnm = di->data.source.beg.file->file.ints.chars;
#endif
			return tkv;
		}

		if (strcmp(t->tok_name, "~diag_id_scope") == 0) {
#ifdef NEWDIAGS
			tkv.tk_exp = read_diag_id_scope (tkv.tk_exp);
#else
			diag_info * di = read_diag_id_scope();
			exp r = getexp(sh(tkv.tk_exp), nilexp, 0, tkv.tk_exp, nilexp,
						   2, 0, diagnose_tag);
			setfather(r, tkv.tk_exp);
			dno(r) = di;
			tkv.tk_exp = r;
#endif
			return tkv;
		}

		if (strcmp(t->tok_name, "~diag_type_scope") == 0) {
#ifdef NEWDIAGS
			tkv.tk_exp = read_diag_type_scope (tkv.tk_exp);
#else
			diag_info * di = read_diag_type_scope();
			exp r = getexp(sh(tkv.tk_exp), nilexp, 0, tkv.tk_exp, nilexp,
						   3, 0, diagnose_tag);
			setfather(r, tkv.tk_exp);
			dno(r) = di;
			tkv.tk_exp = r;
#endif
			return tkv;
		}

		if (strcmp(t->tok_name, "~diag_tag_scope") == 0) {
#ifndef NEWDIAGS
			diag_info * di = read_diag_tag_scope();
			exp r = getexp(sh(tkv.tk_exp), nilexp, 0, tkv.tk_exp, nilexp,
						   4, 0, diagnose_tag);
			setfather(r, tkv.tk_exp);
			dno(r) = di;
			tkv.tk_exp = r;
#endif
			return tkv;
		}

#ifdef NEWDIAGS
		if (strcmp(t->tok_name, "~dg_exp") == 0) {
			tkv.tk_exp = read_dg_exp (tkv.tk_exp);
			return tkv;
		}
#endif

	}

	if (strncmp(t->tok_name, "~asm", 4) == 0) {
		int prp;
		exp arg1;

		if (strcmp(t->tok_name, "~asm") == 0) {
			arg1 = hold_check (f_make_nof_int (ucharsh, d_string()));
			prp = 1;
		} else {
			if (strcmp(t->tok_name, "~asm_sequence") == 0)
				prp = 0;
			else if (strcmp(t->tok_name, "~asm_exp_input") == 0)
				prp = 2;
			else if (strcmp(t->tok_name, "~asm_exp_output") == 0)
				prp = 4;
			else if (strcmp(t->tok_name, "~asm_exp_address") == 0)
				prp = 8;
			else
				return tkv;
			arg1 = hold_check (d_exp());
		}
		tkv.tk_exp = getexp (f_top, nilexp, 0, arg1, nilexp, prp, 0, asm_tag);
		setfather (tkv.tk_exp, arg1);
		*done = 1;
		return tkv;
	}

	SET(tkv); /* call looks at done to see if result is meaningful */
	return tkv;
}
