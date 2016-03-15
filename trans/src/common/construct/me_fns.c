/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <tdf/nat.h>
#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/table_fns.h>
#include <reader/externs.h>
#include <reader/basicread.h>

#include <construct/exp.h>
#include <construct/installglob.h>
#include <construct/install_fns.h>
#include <construct/me_fns.h>

#include <main/flags.h>

#include <refactor/refactor.h>

/* a collection of useful procedures for makeing up exps */

/* PROCEDURES */

exp
me_obtain(exp id)
{
	shape sha = (son(id) == NULL) ? sh(id) : sh(son(id));
	exp n;
	n = getexp((isvar(id)) ? f_pointer(align_of(sha)) : sha, NULL, 0, id,
		   pt(id), 0, 0, name_tag);
	++no(id);
	pt(id) = n;
	return n;
}


exp
me_startid(shape sha, exp def, int isv)
{
	exp r = getexp(sha, NULL, 0, def, NULL, 0, 0, ident_tag);
	if (isv) {
		setvar(r);
	}
	return r;
}


exp
me_start_clearvar(shape sha, shape shb)
{
	exp init = getexp(shb, NULL, 0, NULL, NULL, 0, 0, clear_tag);
	exp var = getexp(sha, NULL, 0, init, NULL, 0, 0, ident_tag);
	setvar(var);
	return var;
}


exp
me_complete_id(exp id, exp body)
{
	son(id)->last = false;
	bro(son(id)) = body;
	body->last = true;
	bro(body) = id;
	sh(id) = sh(body);
	return hold_refactor(id);
}


exp
me_u1(error_treatment ov_err, exp arg1, unsigned char nm)
{
	exp r = getexp(sh(arg1), NULL, 0, arg1, NULL, 0, 0, nm);
	seterrhandle(r, ov_err.err_code);
	if (isov(r)) {
		setjmp_dest(r, get_lab(ov_err.jmp_dest));
	}
	setfather(r, arg1);
	return r;
}


exp
me_u2(exp arg1, unsigned char nm)
{
	exp r = getexp(sh(arg1), NULL, 0, arg1, NULL, 0, 0, nm);
	setfather(r, arg1);
	return r;
}


exp
me_u3(shape sha, exp arg1, unsigned char nm)
{
	exp r = getexp(sha, NULL, 0, arg1, NULL, 0, 0, nm);
	setfather(r, arg1);
	return r;
}


exp
me_b1(error_treatment ov_err, exp arg1, exp arg2, unsigned char nm)
{
	exp r = getexp(sh(arg1), NULL, 0, arg1, NULL, 0, 0, nm);
	seterrhandle(r, ov_err.err_code);
	setbro(arg1, arg2);
	arg1->last = false;
	if (isov(r)) {
		setjmp_dest(r, get_lab(ov_err.jmp_dest));
	}
	setfather(r, arg2);
	return r;
}


exp
me_b2(exp arg1, exp arg2, unsigned char nm)
{
	exp r = getexp(sh(arg1), NULL, 0, arg1, NULL, 0, 0, nm);
	setbro(arg1, arg2);
	arg1->last = false;
	setfather(r, arg2);
	return r;
}


exp
me_b3(shape sha, exp arg1, exp arg2, unsigned char nm)
{
	exp r = getexp(sha, NULL, 0, arg1, NULL, 0, 0, nm);
	setbro(arg1, arg2);
	arg1->last = false;
	setfather(r, arg2);
	return r;
}


exp
me_b4(error_treatment div0_err, error_treatment ov_err, exp arg1, exp arg2,
      unsigned char nm)
{
	exp id, tst, divexp, seq;

	if (div0_err.err_code != 4) {
		return me_b1(ov_err, arg1, arg2, nm);
	}

	id = me_startid(sh(arg1), arg2, 0);
	divexp = me_b1(ov_err, arg1, me_obtain(id), nm);
	tst = me_q1(no_nat_option, f_not_equal, div0_err.jmp_dest,
		    me_obtain(id), me_shint(sh(arg1), 0), test_tag);
	seq = me_b2(me_u2(tst, 0), divexp, seq_tag);
	return me_complete_id(id, seq);
}


exp
me_c1(shape sha, error_treatment ov_err, exp arg1, unsigned char nm)
{
	exp r = getexp(sha, NULL, 0, arg1, NULL, 0, 0, nm);
	seterrhandle(r, ov_err.err_code);
	if (isov(r)) {
		setjmp_dest(r, get_lab(ov_err.jmp_dest));
	}
	setfather(r, arg1);
	return r;
}


exp
me_c2(shape sha, exp arg1, unsigned char nm)
{
	exp r = getexp(sha, NULL, 0, arg1, NULL, 0, 0, nm);
	setfather(r, arg1);
	return r;
}


exp
me_l1(shape s, unsigned char nm)
{
	exp r = getexp(s, NULL, 0, NULL, NULL, 0, 0, nm);
	return r;
}


static exp
me_q1_aux(nat_option prob, ntest nt, exp lab, exp arg1, exp arg2,
	  unsigned char nm)
{
	exp r;
	r = getexp(f_top, NULL, 0, arg1, lab, 0, 0, nm);
	no(r) = (prob.present) ? natint(prob.val) : 1000;
	settest_number(r, nt);
	setbro(arg1, arg2);
	arg1->last = false;
	++no(son(lab));
	setfather(r, arg2);
	return r;
}


exp
me_q1(nat_option prob, ntest nt, label dest, exp arg1, exp arg2,
      unsigned char nm)
{
	return me_q1_aux(prob, nt, get_lab(dest), arg1, arg2, nm);
}


static exp
me_q2_aux(nat_option prob, error_treatment err, ntest nt, exp lab, exp arg1,
	  exp arg2, unsigned char nm)
{
	exp r;
	UNUSED(err);
	r = getexp(f_top, NULL, 0, arg1, lab, 0, 0, nm);
	no(r) = (prob.present) ? natint(prob.val) : 1000;
	settest_number(r, nt);
	setbro(arg1, arg2);
	arg1->last = false;
	++no(son(lab));
	setfather(r, arg2);

	return r;
}


exp
me_q2(nat_option prob, error_treatment err, ntest nt, label dest, exp arg1,
      exp arg2, unsigned char nm)
{
	return me_q2_aux(prob, err, nt, get_lab(dest), arg1, arg2, nm);
}


exp
me_shint(shape sha, int i)
{
	return getexp(sha, NULL, 0, NULL, NULL, 0, i, val_tag);
}


exp
me_null(shape sha, int i, unsigned char nm)
{
	return getexp(sha, NULL, 0, NULL, NULL, 0, i, nm);
}


void
note_repeat(exp r)
{
	if (crt_repeat != NULL) {
		++no(crt_repeat);
	}
	repeat_list = getexp(f_top, crt_repeat, 0, NULL, repeat_list, 1, 0,
			     0);
	crt_repeat = repeat_list;

	pt(r) = crt_repeat;

	son(crt_repeat) = r;
	crt_repeat = bro(crt_repeat);
}


/* the result is an alignment for something of which the addresses must be
 * divisible by n bits */
alignment
long_to_al(int n)
{
	switch (n) {
	case   0:
	case   1: return const_al1;
	case   8: return const_al8;
	case  16: return const_al16;
	case  32: return const_al32;
	case  64: return const_al64;
	case 512: return const_al512;

	default:
		error(ERR_INTERNAL, "illegal value for alignment");
		return const_al32;
	}
}


/* the shape describes an integer */
int
is_integer(shape s)
{
	return s->tag >= scharhd && s->tag <= u64hd;
}


/* the shape describes a floating point number */
int
is_float(shape s)
{
	return s->tag >= shrealhd && s->tag <= doublehd;
}


int
is_complex(shape s)
{
	if (~has & HAS_COMPLEX) {
		return s->tag == cpdhd;
	}

	return s->tag >= shcomplexhd && s->tag <= complexdoublehd;
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
