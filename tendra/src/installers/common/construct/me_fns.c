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
#include "exp.h"
#include "expmacs.h"
#include "table_fns.h"
#include "externs.h"
#include "installglob.h"
#include "tags.h"
#include "install_fns.h"
#include "check.h"
#include "messages_c.h"
#include "shapemacs.h"
#include "basicread.h"
#include "natmacs.h"
#include "me_fns.h"

/* a collection of useful procedures for makeing up exps */

/* PROCEDURES */

exp
me_obtain(exp id)
{
	shape sha = (son(id)==nilexp)?sh(id):sh(son(id));
	exp n;
	n = getexp((isvar(id)) ? f_pointer(align_of(sha)) : sha,
			   nilexp, 0, id, pt(id), 0, 0, name_tag);
	++no(id);
	pt(id) = n;
	return n;
}

exp
me_startid(shape sha, exp def, int isv)
{
	exp r = getexp(sha, nilexp, 0, def, nilexp, 0, 0, ident_tag);
	if (isv)
		setvar(r);
	return r;
}

exp
me_start_clearvar(shape sha, shape shb)
{
	exp init = getexp(shb, nilexp, 0, nilexp, nilexp, 0, 0, clear_tag);
	exp var = getexp(sha, nilexp, 0, init, nilexp, 0, 0, ident_tag);
	setvar(var);
	return var;
}

exp
me_complete_id(exp id, exp body)
{
	clearlast(son(id));
	bro(son(id)) = body;
	setlast(body);
	bro(body) = id;
	sh(id) = sh(body);
	return hold_check(id);
}

exp
me_u1(error_treatment ov_err, exp arg1, unsigned char nm)
{
	exp r = getexp (sh (arg1), nilexp, 0, arg1, nilexp,
					0, 0, nm);
	seterrhandle(r, ov_err.err_code);
	if (isov(r))
		setjmp_dest(r, get_lab(ov_err.jmp_dest));
	setfather (r, arg1);
	return r;
}

exp
me_u2(exp arg1, unsigned char nm)
{
	exp r = getexp (sh (arg1), nilexp, 0, arg1, nilexp, 0, 0, nm);
	setfather (r, arg1);
	return r;
}

exp
me_u3(shape sha, exp arg1, unsigned char nm)
{
	exp r = getexp (sha, nilexp, 0, arg1, nilexp, 0, 0, nm);
	setfather (r, arg1);
	return r;
}

exp
me_b1(error_treatment ov_err, exp arg1, exp arg2,
	  unsigned char nm)
{
	exp r = getexp (sh (arg1), nilexp, 0, arg1, nilexp,
					0, 0, nm);
	seterrhandle(r, ov_err.err_code);
	setbro(arg1, arg2);
	clearlast(arg1);
	if (isov(r))
		setjmp_dest(r, get_lab(ov_err.jmp_dest));
	setfather (r, arg2);
	return r;
}

exp
me_b2(exp arg1, exp arg2, unsigned char nm)
{
	exp r = getexp (sh (arg1), nilexp, 0, arg1, nilexp, 0, 0, nm);
	setbro(arg1, arg2);
	clearlast(arg1);
	setfather (r, arg2);
	return r;
}

exp
me_b3(shape sha, exp arg1, exp arg2, unsigned char nm)
{
	exp r = getexp (sha, nilexp, 0, arg1, nilexp, 0, 0, nm);
	setbro(arg1, arg2);
	clearlast(arg1);
	setfather (r, arg2);
	return r;
}

exp
me_c1(shape sha, error_treatment ov_err, exp arg1,
	  unsigned char nm)
{
	exp r = getexp (sha, nilexp, 0, arg1, nilexp,
					0, 0, nm);
	seterrhandle(r, ov_err.err_code);
	if (isov(r))
		setjmp_dest(r, get_lab(ov_err.jmp_dest));
	setfather (r, arg1);
	return r;
}

exp
me_c2(shape sha, exp arg1, unsigned char nm)
{
	exp r = getexp (sha, nilexp, 0, arg1, nilexp, 0, 0, nm);
	setfather (r, arg1);
	return r;
}

exp
me_l1(shape s, unsigned char nm)
{
	exp r = getexp (s, nilexp, 0, nilexp, nilexp, 0, 0, nm);
	return r;
}



exp
me_q1_aux(nat_option prob, ntest nt, exp lab,
		  exp arg1, exp arg2, unsigned char nm)
{
	exp r;
	r = getexp (f_top, nilexp, 0, arg1, lab, 0, 0, nm);
	no(r) = (prob.present) ? natint(prob.val) : 1000;
	settest_number(r, nt);
	setbro(arg1, arg2);
	clearlast(arg1);
	++no(son(lab));
	setfather (r, arg2);
	return r;
}

exp
me_q1(nat_option prob, ntest nt, label dest,
	  exp arg1, exp arg2, unsigned char nm)
{
	return me_q1_aux(prob, nt, get_lab(dest), arg1, arg2, nm);
}

exp
me_q2_aux(nat_option prob, error_treatment err,
		  ntest nt, exp lab, exp arg1, exp arg2,
		  unsigned char nm)
{
	exp r;
	UNUSED(err);
	r = getexp (f_top, nilexp, 0, arg1, lab, 0, 0, nm);
	no(r) = (prob.present) ? natint(prob.val) : 1000;
	settest_number(r, nt);
	setbro(arg1, arg2);
	clearlast(arg1);
	++no(son(lab));
	setfather (r, arg2);
	
	return r;
}

exp
me_q2(nat_option prob, error_treatment err,
	  ntest nt, label dest, exp arg1, exp arg2,
	  unsigned char nm)
{
	return me_q2_aux(prob, err, nt, get_lab(dest), arg1, arg2, nm);
}

exp
me_shint(shape sha, int i)
{
	return getexp(sha, nilexp, 0, nilexp, nilexp, 0, i, val_tag);
}

exp
me_null(shape sha, int i, unsigned char nm)
{
	return getexp(sha, nilexp, 0, nilexp, nilexp, 0, i, nm);
}

exp
me_b4(error_treatment div0_err, error_treatment ov_err,
	  exp arg1, exp arg2, unsigned char nm)
{
	exp id, tst, divexp, seq;
	
	if (div0_err.err_code != 4)
		return me_b1(ov_err, arg1, arg2, nm);
	
	id = me_startid(sh(arg1), arg2, 0);
	divexp = me_b1(ov_err, arg1, me_obtain(id), nm);
	tst = me_q1(no_nat_option, f_not_equal, div0_err.jmp_dest,
				me_obtain(id), me_shint(sh(arg1), 0), test_tag);
	seq = me_b2(me_u2(tst, 0), divexp, seq_tag);
	return me_complete_id(id, seq);
}

void
note_repeat(exp r)
{
	if (crt_repeat != nilexp)
		++no (crt_repeat);
	repeat_list = getexp (f_top, crt_repeat, 0, nilexp,
						  repeat_list, 1, 0, 0);
	crt_repeat = repeat_list;
	
	pt(r) = crt_repeat;
	
	son (crt_repeat) = r;
	crt_repeat = bro(crt_repeat);
	return;
}

/* the result is an alignment for something of which the
 *     addresses must be divisible by n bits */
alignment
long_to_al(int n)
{
	switch (n) {
    case 0:
    case 1: return const_al1;
    case 8: return const_al8;
    case 16: return const_al16;
    case 32: return const_al32;
    case 64: return const_al64;
    case 512: return const_al512;
    default: failer(BAD_LONG_AL);
		return const_al32;
	};
}

/* the shape describes an integer */
int
is_integer(shape s)
{
	return name(s) >= scharhd && name(s) <= u64hd;
}

/* the shape describes a floating point number */
int
is_float(shape s)
{
	return name(s) >= shrealhd && name(s) <= doublehd;
}

int
is_complex(shape s)
{
#if substitute_complex
	return (name(s) == cpdhd);
#else
	return name(s) >= shcomplexhd && name(s) <= complexdoublehd;
#endif
}

floating_variety
float_to_complex_var(floating_variety f)
{
	return f+3;
}

floating_variety
complex_to_float_var(floating_variety f)
{
	return f-3;
}
