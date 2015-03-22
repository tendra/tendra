/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * This file consists of the floating point and complex operations
 * extracted from install_fns.c, to reduce compilation unit sizes.
 */

#include <ctype.h>
#include <time.h>
#include <stdlib.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/xalloc.h>

#include <reader/exp.h>
#include <local/szs_als.h>

#include <tdf/nat.h>

#include <reader/basicread.h>
#include <reader/main_reads.h>
#include <reader/readglob.h>
#include <reader/table_fns.h>
#include <reader/readglob.h>
#include <reader/externs.h>

#include <construct/exp.h>
#include <construct/tags.h>
#include <construct/me_fns.h>
#include <construct/installglob.h>
#include <construct/flpt.h>
#include <construct/shape.h>
#include <construct/messages_c.h>
#include <construct/install_fns.h>

#include <main/flags.h>

#include <refactor/refactor.h>

#ifdef TRANS_POWER
#include <local/cpu.h>
#endif

extern shape shcomplexsh;
extern shape complexsh;
extern shape complexdoublesh;
static exp_list reorder_list(exp_list, int);
static exp me_contents(exp);
extern int eq_et(error_treatment, error_treatment);
extern exp TDFcallaux(error_treatment, exp, char *, shape);
extern exp find_named_tg(char *, shape);

static exp me_complete_chain(exp, exp, exp);
static exp push(exp, exp);
static void square_x_iy(error_treatment, exp *, exp *, exp);
static void mult_w_by_z(error_treatment, exp *, exp *, exp, exp, exp);
static exp make_comp_1_z(floating_variety, error_treatment, exp, exp, exp, exp,
                         exp, exp);
static exp f_bin_floating_plus(error_treatment, exp, exp);
static exp f_bin_floating_mult(error_treatment, exp, exp);
static exp real_power(error_treatment, exp, exp);

exp
f_change_floating_variety(error_treatment flpt_err, floating_variety r, exp arg1)
{
	if (name(sh(arg1)) == bothd) {
		return arg1;
	}

	if (check & CHECK_SHAPE) {
		if (!((is_complex(sh(arg1)) && is_complex(f_floating(r))) ||
		      (is_float(sh(arg1)) && is_float(f_floating(r)))))
		{
			error(ERR_INTERNAL, CHSH_CHFL);
		}
	}

	if (eq_shape(f_floating(r), sh(arg1))) {	/* i.e. does nothing */
		return arg1;	/* Discard the other bits ? */
	}

	if (~has & HAS_COMPLEX && is_complex(sh(arg1))) {
		shape complex_shape = sh(arg1);
		floating_variety real_fv = f_float_of_complex(f_floating(r));

		exp c1 = me_startid(complex_shape, arg1, 0);

		exp obtain1_c1 = me_obtain(c1); /* contents of arg1 */
		exp obtain2_c1 = me_obtain(c1);

		exp x = f_real_part(obtain1_c1);      /* re(arg1) */
		exp y = f_imaginary_part(obtain2_c1); /* im(arg1) */

		exp new_x = f_change_floating_variety(flpt_err, real_fv, x);
		exp new_y = f_change_floating_variety(flpt_err, real_fv, y);

		exp make_comp = f_make_complex(r, new_x, new_y);
		c1 = me_complete_id(c1, make_comp);	/* Does a 'hold_refactor' */

		return c1;
	}

#if TRANS_HPPA
	{
		exp t = me_c1(f_floating(r), flpt_err, arg1, chfl_tag);
		if (!optop(t) && name(sh(t)) == doublehd) {
			exp id = me_startid(sh(t), t, 0);
			exp tmp = me_complete_id(id, me_obtain(id));
			return tmp;
		} else {
			return t;
		}
	}
#endif

	return me_c1(f_floating(r), flpt_err, arg1, chfl_tag);
}

exp
f_complex_conjugate(exp arg1)
{
	if (name(sh(arg1)) == bothd) {
		return arg1;
	}

	if (check & CHECK_SHAPE) {
		if (!is_complex(sh(arg1))) {
			error(ERR_INTERNAL, CHSH_CONJUGATE);
		}
	}

	if (~has & HAS_COMPLEX) {
		shape complex_shape = sh(arg1);	/* shape of our complex numbers */
		floating_variety real_fv = f_float_of_complex(complex_shape);
		shape real_shape = f_floating(real_fv);
		floating_variety complex_fv = f_complex_of_float(real_shape);

		exp c1 = me_startid(complex_shape, arg1, 0);

		exp obtain1_c1 = hold_refactor(me_obtain(c1)); /* contents of arg1 */
		exp obtain2_c1 = hold_refactor(me_obtain(c1));

		exp x1 = f_real_part(obtain1_c1);      /* re(arg1) */
		exp y1 = f_imaginary_part(obtain2_c1); /* im(arg1) */

		exp neg_im = f_floating_negate(f_impossible, y1); /* - im(arg1) */
		exp make_comp = f_make_complex(complex_fv, x1, neg_im);

		c1 = me_complete_id(c1, make_comp);

		return c1;
	}

	return me_u3(sh(arg1), arg1, conj_tag);
}

exp
f_float_int(error_treatment flpt_err, floating_variety f, exp arg1)
{
	if (name(sh(arg1)) == bothd) {
		return arg1;
	}

	if (check & CHECK_SHAPE) {
		if (!is_integer(sh(arg1))) {
			error(ERR_INTERNAL, CHSH_FLINT);
		}
	}

	if (is_complex(f_floating(f))) {
		flpt fzero_copy = new_flpt();
		floating_variety fv = f_float_of_complex(f_floating(f));
		shape real_shape = f_floating(fv);
		exp zero;
		exp res = f_float_int(flpt_err, fv, arg1);
		res = hold_refactor(res);
		flt_copy(flptnos[fzero_no], &flptnos[fzero_copy]);
		zero = getexp(real_shape, NULL, 1, NULL, NULL, 0, fzero_copy, real_tag);
		return f_make_complex(f, res, zero);
	}

	if (~has & HAS_64_BIT) {
		if ((name(arg1) != val_tag || flpt_err.err_code > 2) &&
		    shape_size(sh(arg1)) > 32) {
			if (has & HAS_LONG_DOUBLE) {
				exp z = TDFcallaux(flpt_err, arg1,
					is_signed(sh(arg1)) ?  "__TDFUs_float" : "__TDFUu_float",
				    doublesh);
				z = hold_refactor(z);
				if (f != doublefv) {
					z = me_c1(f_floating(f), flpt_err, z, chfl_tag);
				}

				return z;
			} else {
				exp z = TDFcallaux(flpt_err, arg1, is_signed(sh(arg1)) ?
					"__TDFUs_float" : "__TDFUu_float", realsh);
				z = hold_refactor(z);
				if (f != realfv) {
					z = me_c1(f_floating(f), flpt_err, z, chfl_tag);
				}

				return z;
			}
		}
	}

	return me_c1(f_floating(f), flpt_err, arg1, float_tag);
}

exp
f_floating_abs(error_treatment ov_err, exp arg1)
{
	if (name(sh(arg1)) == bothd) {
		return arg1;
	}

	if (check & CHECK_SHAPE) {
		if (!is_float(sh(arg1))) {
			error(ERR_INTERNAL, CHSH_FLABS);
		}
	}

#if TRANS_HPPA
	{
		exp r = me_u1(ov_err, arg1, fabs_tag);
		if (!optop(r) && name(sh(r)) == doublehd) {
			exp id  = me_startid(sh(r), r, 0);
			exp tmp = me_complete_id(id, me_obtain(id));

			return tmp;
		} else {
			return r;
		}
	}
#endif

	return me_u1(ov_err, arg1, fabs_tag);
}

exp
f_floating_div(error_treatment ov_err, exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!((is_float(sh(arg1)) || is_complex(sh(arg1))) &&
		      eq_shape(sh(arg1), sh(arg2))))
		{
			error(ERR_INTERNAL, CHSH_FLDIV);
		}
	}

	if (~has & HAS_COMPLEX && is_complex(sh(arg1))) {
		shape complex_shape = sh(arg1);	/* shape of our complex numbers */
		floating_variety real_fv = f_float_of_complex(complex_shape);
		shape real_shape = f_floating(real_fv);
		floating_variety complex_fv = f_complex_of_float(real_shape);

		exp z1 = me_startid(complex_shape, arg1, 0);
		exp z2 = me_startid(complex_shape, arg2, 0);

		exp obtain1_z1 = hold_refactor(me_obtain(z1));	/* contents of arg1 */
		exp obtain2_z1 = hold_refactor(me_obtain(z1));
		exp obtain1_z2 = hold_refactor(me_obtain(z2));	/* contents of arg2 */
		exp obtain2_z2 = hold_refactor(me_obtain(z2));

		exp z1_re = f_real_part(obtain1_z1);		/* re(arg1) */
		exp z2_re = f_real_part(obtain1_z2);		/* re(arg2) */
		exp z1_im = f_imaginary_part(obtain2_z1);		/* im(arg1) */
		exp z2_im = f_imaginary_part(obtain2_z2);		/* im(arg2) */

		exp x1 = me_startid(real_shape, z1_re, 0);
		exp x2 = me_startid(real_shape, z2_re, 0);
		exp y1 = me_startid(real_shape, z1_im, 0);
		exp y2 = me_startid(real_shape, z2_im, 0);

		exp obtain1_x1 = hold_refactor(me_obtain(x1)); /* x1 is used twice */
		exp obtain2_x1 = hold_refactor(me_obtain(x1));
		exp obtain1_y1 = hold_refactor(me_obtain(y1)); /* y1 is used twice */
		exp obtain2_y1 = hold_refactor(me_obtain(y1));

		exp obtain1_x2 = hold_refactor(me_obtain(x2)); /* x2 is used four times */
		exp obtain2_x2 = hold_refactor(me_obtain(x2));
		exp obtain3_x2 = hold_refactor(me_obtain(x2));
		exp obtain4_x2 = hold_refactor(me_obtain(x2));
		exp obtain1_y2 = hold_refactor(me_obtain(y2)); /* y2 is used four times */
		exp obtain2_y2 = hold_refactor(me_obtain(y2));
		exp obtain3_y2 = hold_refactor(me_obtain(y2));
		exp obtain4_y2 = hold_refactor(me_obtain(y2));

		exp mult_x2_x2 = f_bin_floating_mult(ov_err, obtain1_x2, obtain2_x2);
		exp mult_y2_y2 = f_bin_floating_mult(ov_err, obtain1_y2, obtain2_y2);
		exp mult_x1_x2 = f_bin_floating_mult(ov_err, obtain1_x1, obtain3_x2);
		exp mult_y1_y2 = f_bin_floating_mult(ov_err, obtain1_y1, obtain3_y2);
		exp mult_y1_x2 = f_bin_floating_mult(ov_err, obtain2_y1, obtain4_x2);
		exp mult_x1_y2 = f_bin_floating_mult(ov_err, obtain2_x1, obtain4_y2);

		exp plus1 = f_bin_floating_plus(ov_err, mult_x2_x2, mult_y2_y2);
		exp plus2 = f_bin_floating_plus(ov_err, mult_x1_x2, mult_y1_y2);
		exp minus1 = f_floating_minus(ov_err, mult_y1_x2, mult_x1_y2);

		exp denom = me_startid(real_shape, plus1, 0);

		exp obtain_denom1 = hold_refactor(me_obtain(denom));
		exp obtain_denom2 = hold_refactor(me_obtain(denom));

		exp answer_re = f_floating_div(ov_err, plus2, obtain_denom1);
		exp answer_im = f_floating_div(ov_err, minus1, obtain_denom2);
		exp make_comp = f_make_complex(complex_fv, answer_re, answer_im);

		denom = me_complete_id(denom, make_comp);
		y2 = me_complete_id(y2, denom);
		y1 = me_complete_id(y1, y2);
		x2 = me_complete_id(x2, y1);
		x1 = me_complete_id(x1, x2);
		z2 = me_complete_id(z2, x1);
		z1 = me_complete_id(z1, z2);

		return z1;
	}

#if TRANS_HPPA
	{
		exp r;

		r = hold_refactor(me_b1(ov_err, arg1, arg2, fdiv_tag));
		if (!optop(r) && name(sh(r)) == doublehd) {
			exp id = me_startid(sh(r), r, 0);
			exp tmp = me_complete_id(id, me_obtain(id));

			return tmp;
		} else {
			return r;
		}
	}
#endif

	return hold_refactor(me_b1(ov_err, arg1, arg2, fdiv_tag));
}

exp
f_floating_maximum(error_treatment flpt_err, exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}

	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!is_float(sh(arg1)) || !eq_shape(sh(arg1), sh(arg2))) {
			error(ERR_INTERNAL, CHSH_FLMAX);
		}
	}

	return hold_refactor(me_b1(flpt_err, arg1, arg2, fmax_tag));
}

exp
f_floating_minimum(error_treatment flpt_err, exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}
	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!is_float(sh(arg1)) || !eq_shape(sh(arg1), sh(arg2))) {
			error(ERR_INTERNAL, CHSH_FLMIN);
		}
	}

	return hold_refactor(me_b1(flpt_err, arg1, arg2, fmin_tag));
}

/*
 * The following code needs to generate labels for use with 'cond_tag'.
 *
 * This is currently implemented using the knowledge that a label can be
 * obtained by taking a pointer to an EXP - a hack which was introduced
 * because of the need to use 'f_integer_test' with 64-bit integers.
 *
 * This hack is performed exclusively by the MACRO 'make_label'
 */
#define make_label(EXP) &EXP

/*
 * 'is_constant_arg' checks to see if E1 is
 * a constant that will fit into type 'int'.
 */
#define is_constant_arg(E1)                     \
    (name(E1) == val_tag && !isbigval(E1) &&    \
    (is_signed(sh(E1)) || (no(E1) >> 31 == 0)))

exp
f_floating_power(error_treatment ov_err, exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}

	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!((is_float(sh(arg1)) || is_complex(sh(arg1))) &&
		      is_integer(sh(arg2))))
		{
			error(ERR_INTERNAL, CHSH_FLPOWER);
		}
	}

	/* PAB changes - 31 October 1994 */

	/* Gives shorter .s file if n < 10 and arg1 is unknown */

	if (is_complex(sh(arg1))) {
		shape integer_shape = sh(arg2);
		shape complex_shape = sh(arg1);	/* shape of our complex numbers */
		floating_variety real_fv = f_float_of_complex(complex_shape);
		shape real_shape = f_floating(real_fv);
		floating_variety complex_fv = f_complex_of_float(real_shape);

		exp sn = me_startid(integer_shape, arg2, 0);

		if (is_constant_arg(arg2) ||
		    ((name(arg2) == name_tag) && (name(son(arg2)) == ident_tag)
		     && !isvar(son(arg2)) && is_constant_arg(son(son(arg2)))))
		{
			/* we know the power */
			int n;
			int exponent;
			exp z = push(sn, me_startid(complex_shape, arg1, 0));

			if (is_constant_arg(arg2)) {
				exponent = no(arg2); /* arg2 is a constant */
			} else {
				exponent = no(son(son(arg2)));
				/* arg2 identifies a constant */
			}

			n = abs(exponent);
			if (n == 0) {
				exp answer_re, answer_im, make_comp;

				flpt fzero_copy = new_flpt();
				flpt fone_copy = new_flpt();

				flt_copy(flptnos[fzero_no], &flptnos[fzero_copy]);
				flt_copy(flptnos[fone_no], &flptnos[fone_copy]);

				answer_re = getexp(real_shape, NULL, 1, NULL, NULL, 0,
				                   fone_copy, real_tag);
				answer_im = getexp(real_shape, NULL, 1, NULL, NULL, 0,
				                   fzero_copy, real_tag);

				make_comp = f_make_complex(complex_fv, answer_re, answer_im);
				return me_complete_chain(z, arg2, make_comp);
			} else {
				exp link_next;

				exp z_re = f_real_part(me_obtain(z));
				exp z_im = f_imaginary_part(me_obtain(z));

				exp x = push(z, me_startid(real_shape, z_re, 0));
				exp y = push(x, me_startid(real_shape, z_im, 0));

				exp u, v, mylast;;

				while ((n % 2) == 0) {
					mylast = y;
					square_x_iy(ov_err, &x, &y, mylast);
					n = n / 2;
				}

				if (n == 1) {
					/* return z */
					if (exponent < 0) {
						link_next = make_comp_1_z(complex_fv, ov_err,
						                          me_obtain(x), me_obtain(x),
						                          me_obtain(x), me_obtain(y),
						                          me_obtain(y), me_obtain(y));
					} else {
						link_next = f_make_complex(complex_fv, me_obtain(x),
						                           me_obtain(y));
					}

					return me_complete_chain(y, arg2, link_next); /*  return z  */
				} else {
					/*  w = z  */
					u = push(y, me_startid(real_shape, me_obtain(x), 0));
					v = push(u, me_startid(real_shape, me_obtain(y), 0));
					mylast = v;
				}

				while (n != 1) {
					/*  z = z*z  */
					square_x_iy(ov_err, &x, &y, mylast);
					mylast = y;
					n = n / 2;
					if ((n % 2) == 1) {
						/*  w = w*z  */
						mult_w_by_z (ov_err, &u, &v, x, y, mylast);
						mylast = v;
					}
				}

				if (exponent < 0) {
					link_next = make_comp_1_z(complex_fv, ov_err,
					                          me_obtain(u), me_obtain(u),
					                          me_obtain(u), me_obtain(v),
					                          me_obtain(v), me_obtain(v));
				} else {
					link_next = f_make_complex(complex_fv, me_obtain(u), me_obtain(v));
				}

				/* return w */
				return me_complete_chain(v, arg2, link_next);
			}
		} else {
			/* main building blocks */
			exp reinitialise_w, main_loop, make_comp;
			exp square_z, mult_z_w, half_n, update_w, repeat_body;
			exp seq, seq_zero, make_comp1, make_comp2;
			exp real0, real1, x, y, u, v;

			exp z = me_startid(complex_shape, arg1, 0);

			exp abs_val_sn = f_abs(ov_err, me_obtain(sn));
			exp n = me_startid(sh(sn), abs_val_sn, 1);

			exp z_re = f_real_part(me_obtain(z));
			exp z_im = f_imaginary_part(me_obtain(z));

			flpt fzero_copy = new_flpt();
			flpt fone_copy = new_flpt();

			flt_copy(flptnos[fzero_no], &flptnos[fzero_copy]);
			flt_copy(flptnos[fone_no], &flptnos[fone_copy]);

			real0 = getexp(real_shape, NULL, 1, NULL, NULL, 0, fzero_copy,
			               real_tag);
			real1 = getexp(real_shape, NULL, 1, NULL, NULL, 0, fone_copy,
			               real_tag);

			x = me_startid(real_shape, z_re, 1);	/* re(arg1) */
			y = me_startid(real_shape, z_im, 1);	/* re(arg2) */

			u = me_startid(real_shape, real1, 1);	/* re(w) = 1.0 */
			v = me_startid(real_shape, real0, 1);	/* im(w) = 0.0 */

			/* change value of w to z if n is odd  */
			{
				exp constant1 = me_shint(integer_shape, 1);
				exp constant2 = me_shint(integer_shape, 2);

				exp rem_n_2 = f_rem0(f_impossible, f_impossible, me_contents(n), constant2);

				exp assign_u = hold_refactor(me_b3(f_top, me_obtain(u), me_contents(x), ass_tag));
				exp assign_v = hold_refactor(me_b3(f_top, me_obtain(v), me_contents(y), ass_tag));

				exp top_cell = me_l1(f_top, top_tag);
				exp alt_labst = hold_refactor(me_b3(sh(top_cell),
					me_null(f_top, 0, clear_tag), top_cell, labst_tag));

				exp is_n_odd = f_integer_test(no_nat_option, f_equal,
					make_label(alt_labst), rem_n_2, constant1);

				exp seq_zero = hold_refactor(me_b2(is_n_odd, assign_u, 0));
				exp seq = hold_refactor(me_b3(sh(assign_v), seq_zero, assign_v, seq_tag));

				reinitialise_w = hold_refactor(me_b3(lub_shape(sh(seq),
					sh(alt_labst)), seq, alt_labst, cond_tag));
			}

			/* z = z * z */
			{
				exp minus_x_y = f_floating_minus(ov_err, me_contents(x), me_contents(y));
				exp  plus_x_y = f_bin_floating_plus(ov_err, me_contents(x), me_contents(y));
				exp  mult_x_y = f_bin_floating_mult(ov_err, me_contents(x), me_contents(y));

				exp tmp = me_startid(real_shape, mult_x_y, 0);

				exp answer_re = f_bin_floating_mult(ov_err, minus_x_y, plus_x_y);
				exp answer_im = f_bin_floating_plus(ov_err, me_obtain(tmp), me_obtain(tmp));

				exp assign_x = hold_refactor(me_b3(f_top, me_obtain(x), answer_re, ass_tag));
				exp assign_y = hold_refactor(me_b3(f_top, me_obtain(y), answer_im, ass_tag));

				exp seq_zero = hold_refactor(me_u2(assign_x, 0));
				exp seq = hold_refactor(me_b3(sh(assign_y), seq_zero, assign_y, seq_tag));

				square_z = me_complete_id(tmp, seq);
			}

			/* w = z * w */
			{
				exp mult_x_u = f_bin_floating_mult(ov_err, me_contents(x), me_contents(u));
				exp mult_x_v = f_bin_floating_mult(ov_err, me_contents(x), me_contents(v));
				exp mult_y_u = f_bin_floating_mult(ov_err, me_contents(y), me_contents(u));
				exp mult_y_v = f_bin_floating_mult(ov_err, me_contents(y), me_contents(v));

				exp tmp = me_startid(real_shape, mult_y_u, 0);

				exp answer_re = f_floating_minus(ov_err, mult_x_u, mult_y_v);
				exp answer_im = f_bin_floating_plus(ov_err, mult_x_v, me_obtain(tmp));

				exp assign_u = hold_refactor(me_b3(f_top, me_obtain(u), answer_re, ass_tag));
				exp assign_v = hold_refactor(me_b3(f_top, me_obtain(v), answer_im, ass_tag));

				exp seq_zero = hold_refactor(me_u2(assign_u, 0));
				exp seq = hold_refactor(me_b3(sh(assign_v), seq_zero, assign_v, seq_tag));

				mult_z_w = me_complete_id(tmp, seq);
			}

			/* n = n / 2 */
			{
				exp constant2 = me_shint(integer_shape, 2);

				exp answer = f_div0(f_impossible, f_impossible, me_contents(n), constant2);
				half_n = hold_refactor(me_b3(f_top, me_obtain(n), answer, ass_tag));
			}

			/* if n is odd then w = z * w */
			{
				exp constant1 = me_shint(integer_shape, 1);
				exp constant2 = me_shint(integer_shape, 2);

				exp rem_n_2 = f_rem0(f_impossible, f_impossible, me_contents(n), constant2);

				exp top_cell = me_l1(f_top, top_tag);
				exp alt_labst = hold_refactor(me_b3(f_top, me_null(f_top, 0,
					clear_tag), top_cell, labst_tag));

				exp is_n_odd = f_integer_test(no_nat_option, f_equal,
					make_label(alt_labst), rem_n_2, constant1);
				exp seq_zero = hold_refactor(me_u2(is_n_odd, 0));
				exp seq = hold_refactor(me_b3(sh(mult_z_w), seq_zero, mult_z_w, seq_tag));

				update_w = hold_refactor(me_b3(lub_shape(sh(seq), sh(alt_labst)),
					seq, alt_labst, cond_tag));
			}

			/* repeat + body */
			{
				exp if_n_equals_1, seq_zero, seq, body_labst;

				exp constant1 = me_shint(integer_shape, 1);
				exp top_cell = me_l1(f_top, top_tag);

				body_labst = hold_refactor(me_b3(sh(top_cell),
					me_null(f_top, 0, clear_tag), top_cell, labst_tag));

				if_n_equals_1 = f_integer_test(no_nat_option, f_equal,
					make_label(body_labst), me_contents(n), constant1);

				seq_zero = me_b2(square_z, update_w, 0);
				setbro(square_z, half_n); /* insert half_n between */
				setbro(half_n, update_w); /* square_x and update_w */
				clearlast(half_n);
				seq_zero = hold_refactor(seq_zero);

				seq = hold_refactor(me_b3(sh(if_n_equals_1), seq_zero,
					if_n_equals_1, seq_tag));

				setbro(son(body_labst), seq);
				clearlast(son(body_labst));
				setfather(body_labst, seq);

				repeat_body = hold_refactor(me_b3(sh(seq), top_cell, body_labst, rep_tag));
				note_repeat(repeat_body);
			}

			/* make loop - only done if mod(n) > 1 */
			{
				exp constant1 = me_shint(integer_shape, 1);

				exp top_cell = me_l1(f_top, top_tag);
				exp alt_labst = hold_refactor(me_b3(f_top,
					me_null(f_top, 0, clear_tag), top_cell, labst_tag));

				exp is_n_gt_1 = f_integer_test(no_nat_option, f_greater_than,
					make_label(alt_labst), me_contents(n), constant1);

				exp seq_zero = hold_refactor(me_u2(is_n_gt_1, 0));
				exp seq = hold_refactor(me_b3(sh(repeat_body), seq_zero,
					repeat_body, seq_tag));

				main_loop = hold_refactor(me_b3(lub_shape(sh(seq), sh(alt_labst)),
					seq, alt_labst, cond_tag));
			}

			make_comp1 = f_make_complex(complex_fv, me_contents(u), me_contents(v));
			make_comp2 = make_comp_1_z(complex_fv, ov_err,
				me_contents(u), me_contents(u), me_contents(u),
				me_contents(v), me_contents(v), me_contents(v));

			/* if arg2 is negative then make_comp2 else make_comp1 */
			{
				exp constant0 = me_shint(integer_shape, 0);

				exp alt_labst = hold_refactor(me_b3(sh(make_comp1),
					me_null(f_top, 0, clear_tag), make_comp1, labst_tag));

				exp is_arg2_negative = f_integer_test(no_nat_option, f_less_than,
					make_label(alt_labst), me_obtain(sn), constant0);

				exp seq_zero = hold_refactor(me_u2(is_arg2_negative, 0));
				exp seq = hold_refactor(me_b3(sh(make_comp2), seq_zero, make_comp2, seq_tag));

				make_comp = hold_refactor(me_b3(lub_shape(sh(seq), sh(alt_labst)),
					seq, alt_labst, cond_tag));
			}

			seq_zero = hold_refactor(me_b2(reinitialise_w, main_loop, 0));
			seq = hold_refactor(me_b3(sh(make_comp), seq_zero, make_comp, seq_tag));


			v  = me_complete_id(v, seq);
			u  = me_complete_id(u, v);
			y  = me_complete_id(y, u);
			x  = me_complete_id(x, y);
			n  = me_complete_id(n, x);
			sn = me_complete_id(sn, n);
			z  = me_complete_id(z, sn);

			return z;
		}
	}

	return real_power(ov_err, arg1, arg2);
}

exp
f_floating_minus(error_treatment ov_err, exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}

	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!((is_float(sh(arg1)) || is_complex(sh(arg1))) &&
		      eq_shape(sh(arg1), sh(arg2)))) {
			error(ERR_INTERNAL, CHSH_FLMINUS);
		}
	}

	if (~has & HAS_COMPLEX && is_complex(sh(arg1))) {
		shape complex_shape = sh(arg1);	/* shape of our complex numbers */
		floating_variety real_fv = f_float_of_complex(complex_shape);
		shape real_shape = f_floating(real_fv);
		floating_variety complex_fv = f_complex_of_float(real_shape);

		exp z1 = me_startid(complex_shape, arg1, 0);
		exp z2 = me_startid(complex_shape, arg2, 0);

		exp x1 = f_real_part(me_obtain(z1));	/* re(arg1) */
		exp x2 = f_real_part(me_obtain(z2));	/* re(arg2) */
		exp y1 = f_imaginary_part(me_obtain(z1));	/* im(arg1) */
		exp y2 = f_imaginary_part(me_obtain(z2));	/* im(arg2) */

		exp minus_re = f_floating_minus(ov_err, x1, x2);
		exp minus_im = f_floating_minus(ov_err, y1, y2);
		exp make_comp = f_make_complex(complex_fv, minus_re, minus_im);

		z2 = me_complete_id(z2, make_comp);
		z1 = me_complete_id(z1, z2);

		return z1;
	}

#if TRANS_HPPA
	{
		exp r = hold_refactor(me_b1(ov_err, arg1, arg2, fminus_tag));
		if (!optop(r) && name(sh(r)) == doublehd) {
			exp id = me_startid(sh(r), r, 0);
			exp tmp = me_complete_id(id, me_obtain(id));
			return tmp;
		} else {
			return r;
		}
	}
#endif

	return hold_refactor(me_b1(ov_err, arg1, arg2, fminus_tag));
}

exp
f_floating_mult(error_treatment ov_err, exp_list arg1)
{
	exp first = arg1.start;
	exp r = getexp(sh(first), NULL, 0, first, NULL, 0, 0, fmult_tag);

	if (name(sh(first)) == bothd || arg1.number == 1) {
		return first;
	}

	clear_exp_list(arg1);
	seterrhandle(r, ov_err.err_code);
	if (isov(r)) {
		setjmp_dest(r, get_lab(ov_err.jmp_dest));
	}

	if (check & CHECK_SHAPE) {
		exp t = first;

		for (;;) {
			if (!((is_float(sh(t)) || is_complex(sh(t))) &&
			      eq_shape(sh(t), sh(first)))) {
				error(ERR_INTERNAL, CHSH_FLMULT);
			}

			if (t == arg1.end) {
				break;
			}

			t = bro(t);
			if (name(sh(t)) == bothd) {
				return t;
			}
		}
	}

	if (~has & HAS_COMPLEX && is_complex(sh(arg1.start))) {
		shape complex_shape = sh(arg1.start); /* shape of our complex numbers */
		floating_variety real_fv = f_float_of_complex(complex_shape);
		shape real_shape = f_floating(real_fv);
		floating_variety complex_fv = f_complex_of_float(real_shape);

		exp x1, y1, x2, y2, z1, z1_re, z1_im, t, link_next, prod_re, prod_im;

#if 0
		arg1 = reorder_list(arg1, 1); /* reorder so constants are at the front */
#else
		(void) reorder_list;
#endif

		z1 = me_startid(complex_shape, arg1.start, 0);

		z1_re = f_real_part(me_obtain(z1));	/* re(arg1.first) */
		z1_im = f_imaginary_part(me_obtain(z1));	/* im(arg1.first) */

		x1 = push(z1, me_startid(real_shape, z1_re, 0));
		y1 = push(x1, me_startid(real_shape, z1_im, 0));

		t = arg1.start;

		while (t != arg1.end) {
			t = bro(t);
			z1 = push(y1, me_startid(complex_shape, t, 0));

			z1_re = f_real_part(me_obtain(z1));		/* contents of next */
			z1_im = f_imaginary_part(me_obtain(z1));	/*   list element   */

			x2 = push(z1, me_startid(real_shape, z1_re, 0));
			y2 = push(x2, me_startid(real_shape, z1_im, 0));

			if (eq_exp(x1, x2) && eq_exp(y1, y2)) {
				exp minus_x1_x2 = f_floating_minus(ov_err, me_obtain(x1), me_obtain(x2));
				exp  plus_x1_x2 = f_bin_floating_plus(ov_err, me_obtain(x1), me_obtain(x2));
				exp  mult_x1_y1 = f_bin_floating_mult(ov_err, me_obtain(x1), me_obtain(y1));

				prod_re = f_bin_floating_mult(ov_err, minus_x1_x2, plus_x1_x2);
				prod_im = f_bin_floating_plus(ov_err, mult_x1_y1, mult_x1_y1);
			} else {
				exp mult_x1_x2 = f_bin_floating_mult(ov_err, me_obtain(x1), me_obtain(x2));
				exp mult_y1_y2 = f_bin_floating_mult(ov_err, me_obtain(y1), me_obtain(y2));
				exp mult_x1_y2 = f_bin_floating_mult(ov_err, me_obtain(x1), me_obtain(y2));
				exp mult_x2_y1 = f_bin_floating_mult(ov_err, me_obtain(x2), me_obtain(y1));

				prod_re = f_floating_minus(ov_err, mult_x1_x2, mult_y1_y2);
				prod_im = f_bin_floating_plus(ov_err, mult_x1_y2, mult_x2_y1);
			}

			x1 = push(y2, me_startid(real_shape, prod_re, 0));
			y1 = push(x1, me_startid(real_shape, prod_im, 0));
		}

		link_next = f_make_complex(complex_fv, me_obtain(x1), me_obtain(y1));

		return me_complete_chain(y1, arg1.start, link_next);
	}

	setfather(r, arg1.end);

#if TRANS_HPPA
	if (!optop(r) && name(sh(r)) == doublehd) {
		exp id = me_startid(sh(r), r, 0);
		exp tmp = me_complete_id(id, me_obtain(id));
		return tmp;
	} else
#endif
		return r;
}

exp
f_floating_negate(error_treatment ov_err, exp arg1)
{
	if (name(sh(arg1)) == bothd) {
		return arg1;
	}

	if (check & CHECK_SHAPE) {
		if (!is_float(sh(arg1)) && !is_complex(sh(arg1))) {
			error(ERR_INTERNAL, CHSH_FLNEGATE);
		}
	}

	if (~has & HAS_COMPLEX && is_complex(sh(arg1))) {
		shape complex_shape = sh(arg1);	/* shape of our complex numbers */
		floating_variety real_fv = f_float_of_complex(complex_shape);
		shape real_shape = f_floating(real_fv);
		floating_variety complex_fv = f_complex_of_float(real_shape);

		exp c1 = me_startid(complex_shape, arg1, 0);

		exp obtain1_c1 = hold_refactor(me_obtain(c1));	/* contents of arg1 */
		exp obtain2_c1 = hold_refactor(me_obtain(c1));

		exp x1 = f_real_part(obtain1_c1);			/* re(arg1) */
		exp y1 = f_imaginary_part(obtain2_c1);		/* im(arg1) */

		exp neg_re = f_floating_negate(ov_err, x1);	/* -re(arg1) */
		exp neg_im = f_floating_negate(ov_err, y1);	/* -im(arg1) */
		exp make_comp = f_make_complex(complex_fv, neg_re, neg_im);

		c1 = me_complete_id(c1, make_comp);

		return c1;
	}

#if TRANS_HPPA
	{
		exp r = hold_refactor(me_u1(ov_err, arg1, fneg_tag));
		if (!optop(r) && name(sh(r)) == doublehd) {
			exp id = me_startid(sh(r), r, 0);
			exp tmp = me_complete_id(id, me_obtain(id));
			return tmp;
		} else {
			return r;
		}
	}
#endif

	return hold_refactor(me_u1(ov_err, arg1, fneg_tag));
}

exp
f_floating_plus(error_treatment ov_err, exp_list arg1)
{
	exp first = arg1.start;
	exp r = getexp(sh(first), NULL, 0, first, NULL, 0, 0, fplus_tag);

	if (name(sh(first)) == bothd || arg1.number == 1) {
		return first;
	}

	clear_exp_list(arg1);
	seterrhandle(r, ov_err.err_code);

	if (isov(r)) {
		setjmp_dest(r, get_lab(ov_err.jmp_dest));
	}

	if (check & CHECK_SHAPE) {
		exp t = first;

		for (;;) {
			if (!((is_float(sh(t)) || is_complex(sh(t))) &&
			      eq_shape(sh(t), sh(first)))) {
				error(ERR_INTERNAL, CHSH_FLPLUS);
			}

			if (t == arg1.end) {
				break;
			}

			t = bro(t);
			if (name(sh(t)) == bothd) {
				return t;
			}
		}
	}

	if (~has & HAS_COMPLEX && is_complex(sh(arg1.start))) {
		exp z1, z2, x1, y1, x2, y2, make_comp, t;

		shape complex_shape = sh(arg1.start); /* shape of our complex numbers */
		floating_variety real_fv = f_float_of_complex(complex_shape);
		shape real_shape = f_floating(real_fv);
		floating_variety complex_fv = f_complex_of_float(real_shape);

#if 0
		arg1 = reorder_list(arg1, 1); /* reorder so constants are at the front */
#endif

		z1 = me_startid(complex_shape, arg1.start, 0);

		x1 = f_real_part(me_obtain(z1));		/* re(arg1.first) */
		y1 = f_imaginary_part(me_obtain(z1));	/* im(arg1.first) */

		t = arg1.start;
		z2 = z1;					/* start chain of idents */

		while (t != arg1.end) {
			t = bro(t);
			z2 = push(z2, me_startid(complex_shape, t, 0));

			x2 = f_real_part(me_obtain(z2));	/* contents of next */
			y2 = f_imaginary_part(me_obtain(z2));	/* list element */

			x1 = f_bin_floating_plus(ov_err, x1, x2);	/* pass it this on */
			y1 = f_bin_floating_plus(ov_err, y1, y2);	/*  as new result  */
		}

		make_comp = f_make_complex(complex_fv, x1, y1);

		return me_complete_chain(z2, arg1.start, make_comp);
	}

	setfather(r, arg1.end);

#if TRANS_HPPA
	if (!optop(r) && name(sh(r)) == doublehd) {
		exp id = me_startid(sh(r), r, 0);
		exp tmp = me_complete_id(id, me_obtain(id));
		return tmp;
	} else
#endif
		return r;
}

exp
f_floating_test(nat_option prob, error_treatment flpt_err, ntest nt,
                label dest, exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}

	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!((is_float(sh(arg1)) || is_complex(sh(arg1))) &&
		      eq_shape(sh(arg1), sh(arg2)))) {
			error(ERR_INTERNAL, CHSH_FLTEST);
		}
	}

	if (~has & HAS_COMPLEX && is_complex(sh(arg1))) {

		shape complex_shape = sh(arg1);	/* shape of our complex numbers */
		exp z1 = me_startid(complex_shape, arg1, 0);
		exp z2 = me_startid(complex_shape, arg2, 0);

		exp obtain1_z1 = hold_refactor(me_obtain(z1));	/* contents of arg1 */
		exp obtain2_z1 = hold_refactor(me_obtain(z1));
		exp obtain1_z2 = hold_refactor(me_obtain(z2));	/* contents of arg2 */
		exp obtain2_z2 = hold_refactor(me_obtain(z2));

		exp x1 = f_real_part(obtain1_z1);			/* re(arg1) */
		exp x2 = f_real_part(obtain1_z2);			/* re(arg2) */
		exp y1 = f_imaginary_part(obtain2_z1);		/* im(arg1) */
		exp y2 = f_imaginary_part(obtain2_z2);		/* im(arg2) */

		if (check & CHECK_SHAPE) {
			if ((nt != f_equal) && (nt != f_not_equal)) {
				error(ERR_INTERNAL, CHSH_FLTEST);
			}
		}

		if (nt == f_equal) {
			/* equality of z1 and z2 */
			exp test1 = f_floating_test(prob, flpt_err, f_equal, dest, x1, x2);
			exp test2 = f_floating_test(prob, flpt_err, f_equal, dest, y1, y2);

			exp seq_zero = hold_refactor(me_u2(test1, 0));
			exp seq = hold_refactor(me_b3(sh(test2), seq_zero, test2, seq_tag));
			z2 = me_complete_id(z2, seq);
		} else {
			/* inequality of z1 and z2 */
			exp seq, conditional;

			exp top_cell = me_l1(f_top, top_tag);
			exp alt_labst = hold_refactor(me_b3(f_top, me_null(f_top, 0, clear_tag),
				top_cell, labst_tag));

			exp test1 = f_floating_test(prob, flpt_err, f_equal,
				make_label(alt_labst), x1, x2);
			exp test2 = f_floating_test(prob, flpt_err, f_not_equal, dest, y1, y2);
			exp seq_zero = hold_refactor(me_b2(test1, test2, 0));

			seq = hold_refactor(me_b3(f_bottom, seq_zero, f_make_top(), seq_tag));

			conditional = hold_refactor(me_b3(f_top, seq, alt_labst, cond_tag));

			z2 = me_complete_id(z2, conditional);
		}

		z1 = me_complete_id(z1, z2);

		return z1;
	}

	return me_q2(prob, flpt_err, nt, dest, arg1, arg2, test_tag);
}

exp
f_imaginary_part(exp arg1)
{
	shape real_shape;

	if (name(sh(arg1)) == bothd) {
		return arg1;
	}

	if (check & CHECK_SHAPE) {
		if (!is_complex(sh(arg1))) {
			error(ERR_INTERNAL, CHSH_IMAG);
		}
	}

	real_shape = f_floating(f_float_of_complex(sh(arg1)));
	if (~has & HAS_COMPLEX) {
		exp t = me_u3(real_shape, arg1, field_tag);
		no(t) = shape_size(real_shape);
		return hold_refactor(t);
	}

	return me_u3(real_shape, arg1, imag_tag);
}

exp
f_real_part(exp arg1)
{
	shape real_shape;

	if (name(sh(arg1)) == bothd) {
		return arg1;
	}

	if (check & CHECK_SHAPE) {
		if (!is_complex(sh(arg1))) {
			error(ERR_INTERNAL, CHSH_REAL);
		}
	}

	real_shape = f_floating(f_float_of_complex(sh(arg1)));
	if (~has & HAS_COMPLEX) {
		exp t = me_u3(real_shape, arg1, field_tag);
		no(t) = 0;
		return hold_refactor(t);
	}

	return me_u3(real_shape, arg1, realpart_tag);
}

exp
f_make_complex(floating_variety f, exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}

	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!is_float(sh(arg1)) || !is_float(sh(arg2)) ||
		    !eq_shape(sh(arg1), sh(arg2)) || f != f_complex_of_float(sh(arg1))) {
			error(ERR_INTERNAL, CHSH_MAKE_COMPLEX);
		}
	}

	if (has & HAS_COMPLEX) {
		return me_b3(f_floating(f), arg1, arg2, make_complex_tag);
	}

	switch (f) {
	case shcomplexfv: {
		shape off_set = f_offset(SHREAL_ALIGN, SHREAL_ALIGN);
		exp val1 = me_shint(off_set, 0);
		exp val2 = me_shint(off_set, SHREAL_SZ);
		exp sz = me_shint(off_set, SHREAL_SZ + SHREAL_SZ);
		exp r = getexp(f_compound(sz), NULL, 0, val1, NULL, 0, 0, compound_tag);

		setbro(val1, arg1);
		clearlast(val1);
		setbro(arg1, val2);
		clearlast(arg1);
		setbro(val2, arg2);
		clearlast(val2);
		setfather(r, arg2);
		return hold_refactor(r);
	}

	case complexfv: {
		shape off_set = f_offset(REAL_ALIGN, REAL_ALIGN);
		exp val1 = me_shint(off_set, 0);
		exp val2 = me_shint(off_set, REAL_SZ);
		exp sz = me_shint(off_set, REAL_SZ + REAL_SZ);
		exp r = getexp(f_compound(sz), NULL, 0, val1, NULL, 0, 0, compound_tag);

		setbro(val1, arg1);
		clearlast(val1);
		setbro(arg1, val2);
		clearlast(arg1);
		setbro(val2, arg2);
		clearlast(val2);
		setfather(r, arg2);
		return hold_refactor(r);
	}

	case complexdoublefv: {
		shape off_set = f_offset(DOUBLE_ALIGN, DOUBLE_ALIGN);
		exp val1 = me_shint(off_set, 0);
		exp val2 = me_shint(off_set, DOUBLE_SZ);
		exp sz = me_shint(off_set, DOUBLE_SZ + DOUBLE_SZ);
		exp r = getexp(f_compound(sz), NULL, 0, val1, NULL, 0, 0, compound_tag);

		setbro(val1, arg1);
		clearlast(val1);
		setbro(arg1, val2);
		clearlast(arg1);
		setbro(val2, arg2);
		clearlast(val2);
		setfather(r, arg2);
		return hold_refactor(r);
	}

	default:
		error(ERR_INTERNAL, "Illegal floating_variety for make_complex_tag");
		return NULL;
	}
}

#if FBASE == 10

exp
f_make_floating(floating_variety fv, rounding_mode rm, bool sign,
	string mantissa, nat base, signed_nat expo)
{
	int ignore_zero = 1;
	int lg = mantissa.number;
	flpt f = new_flpt();
	int sig_digs = 0;
	int i;
	int point = 0;
	char ch;
	int exponent = snatint(expo);

	if (PIC_code) {
		proc_externs = 1;
	}

	if (snatneg(expo)) {
		exponent = - exponent;
	}

	if (natint(base) != 10) {
		error(ERR_INTERNAL, BASE_NOT_10);
	}

	for (i = 0; i < MANT_SIZE; ++i) {
		(flptnos[f].mant)[i] = 0;
	}

	for (i = 0; i < lg; ++i) {
		ch = mantissa.ints.chars[i];
		if (ch == '0' && ignore_zero) {
			if (point) {
				--exponent;
			}
		} else {
			if (ch == '.') {
				point = 1;
			} else {
				ignore_zero = 0;

				if (!point) {
					++exponent;
				}

				if (sig_digs < MANT_SIZE) {
					flptnos[f].mant[sig_digs++] = ch - '0';
				}
			}
		}
	}

	if (ignore_zero) {
		flptnos[f].exp = 0;
		flptnos[f].sign = 0;
	} else {
		flptnos[f].exp = exponent - 1;
		flptnos[f].sign = (sign ? -1 : 1);
	}

	if (flptnos[f].exp > target_dbl_maxexp) {
		error(ERR_INTERNAL, BIG_FLPT);
	}

	return getexp(f_floating(fv), NULL, 0, NULL, NULL, 0, f, real_tag);

}

#else

exp
f_make_floating(floating_variety fv, rounding_mode rm, bool sign,
	string mantissa, nat natbase, signed_nat expo)
{
	int ignore_zero = 1;
	int lg = mantissa.number;
	flpt f = new_flpt();
	int has_sig_digs = 0;
	int i;
	int point = 0;
	int exponent = snatint(expo);
	flt fr;
	int base = natint(natbase);


	flt_zero(&fr);

	if (PIC_code) {
		proc_externs = 1;
	}

	if (base != 10 && base != 16 && base != 8 && base != 2 && base != 4) {
		error(ERR_INTERNAL, BAD_BASE);
	}

	if (snatneg(expo)) {
		exponent = -exponent;
	}

	for (i = 0; i < lg; ++i) {
		char c = mantissa.ints.chars[i];
		if (c != '0' || !ignore_zero) {
			ignore_zero = 0;
			if (c == '.') {
				point = 1;
			} else {
				c = c - '0';
				if (c != 0) {
					has_sig_digs = 1;
				}
				exponent -= point;
				flpt_newdig((unsigned int)c, &fr, base);
			}
		}
	}

	if (ignore_zero) {
		fr.exp = 0;
		fr.sign = 0;
	} else {
		if (has_sig_digs) {
			fr.sign = (sign ? -1 : 1);
		} else {
			fr.sign = 0;
		}
		flpt_scale(exponent, &fr, base);
	}


	flpt_round((int) rm, flpt_bits((floating_variety) fv), &fr);

	if (check & CHECK_FLPT_OVERFLOW) {
		r2l r;
		r = real2longs_IEEE(&fr, fv);
		UNUSED(r);
	}

	flptnos[f] = fr;

	return getexp(f_floating(fv), NULL, 0, NULL, NULL, 0, f, real_tag);
}

#endif

exp
f_power(error_treatment ov_err, exp arg1, exp arg2)
{
	if (name(sh(arg1)) == bothd) {
		kill_exp(arg2, arg2);
		return arg1;
	}

	if (name(sh(arg2)) == bothd) {
		kill_exp(arg1, arg1);
		return arg2;
	}

	if (check & CHECK_SHAPE) {
		if (!is_integer(sh(arg1)) || !is_integer(sh(arg2))) {
			error(ERR_INTERNAL, CHSH_POWER);
		}
	}

	return real_power(ov_err, arg1, arg2);
}

exp
f_round_with_mode(error_treatment flpt_err, rounding_mode mode, variety r, exp arg1)
{
	exp res;

	if (name(sh(arg1)) == bothd) {
		return arg1;
	}

	if (is_complex(sh(arg1))) {
		arg1 = f_real_part(arg1);
	}

	if (check & CHECK_SHAPE) {
		if (!is_float(sh(arg1))) {
			error(ERR_INTERNAL, CHSH_ROUND);
		}
	}

	if (~has & HAS_64_BIT) {
		if (shape_size(r) > 32 && (name(arg1) != real_tag || flpt_err.err_code >= 4)) {
			int s = is_signed(r);
			char *fn;
			exp e;

			arg1 = hold_refactor(f_change_floating_variety(f_impossible, (has & HAS_LONG_DOUBLE) ? 2 : 1, arg1));

			switch (mode) {
			case R2NEAR: fn = (s) ? "__TDFUs_R2NEAR"  : "__TDFUu_R2NEAR";    break;
			case R2PINF: fn = (s) ? "__TDFUs_R2PINF"  : "__TDFUu_R2PINF";    break;
			case R2NINF: fn = (s) ? "__TDFUs_R2NINF"  : "__TDFUu_R2NINF";    break;
			case R2ZERO: fn = (s) ? "__TDFUs_R2ZERO"  : "__TDFUu_R2ZERO";    break;
			default:     fn = (s) ? "__TDFUs_ASSTATE" : "__TDFUu_R2ASSTATE"; break;
			}

			e = TDFcallaux(flpt_err, arg1, fn, r);
			return hold_refactor(e);
		}
	}

#if TRANS_MIPS
	/*
	 * mips does not seem to get float->unsigned long right,
	 * so convert to signed long and adjust if too big.
	 */
	else if (name(arg1) != real_tag && shape_size(r) == 32 &&
	         !is_signed(r)) {
		floating_variety fa = (shape_size(sh(arg1)) == 32) ? 0 : 1;
		exp_list st;
		exp z;
		exp d1 = me_startid(r, arg1, 0);
		exp hldr = getexp(f_top, NULL, 0, NULL, NULL, 0, 0, 0);
		exp lb = getexp(f_top, NULL, 0, hldr, NULL, 0, 0,
		                labst_tag);

		exp fmax = hold_refactor(f_float_int(f_impossible, fa,
		                                     me_shint(ulongsh,
		                                             0x80000000)));
		exp d2 = me_startid(r, fmax, 0);
		exp tst = f_floating_test(no_nat_option, f_impossible,
		                          f_less_than, &lb, me_obtain(d1),
		                          me_obtain(d2));
		exp nconv = f_round_with_mode(flpt_err, mode, slongsh,
		                              me_obtain(d1));
		exp first;
		exp alt;
		exp cnd;
		st = new_exp_list(1);
		st = add_exp_list(st, tst, 0);
		first = f_sequence(st, f_change_variety(flpt_err, r, nconv));
		z = f_round_with_mode(flpt_err, mode, slongsh,
		                      f_floating_minus(f_impossible,
		                                       me_obtain(d1),
		                                       me_obtain(d2)));
		alt = f_plus(f_impossible, f_change_variety(f_impossible, r, z),
		             me_shint(r, 0x80000000));
		cnd = f_conditional(&lb, first, alt);
		return me_complete_id(d1, me_complete_id(d2, cnd));

	}
#endif

#if TRANS_POWER
	if (name(arg1) != real_tag || flpt_err.err_code > 2) {
		if (cpu != CPU_POWERPC) {
			exp id;
			exp apply1;
			exp apply2;
			long shp_sze = shape_size(f_integer(r));
			bool sgned = is_signed(f_integer(r));
			bool err = (flpt_err.err_code > 2);
			char *nm;
			char *nm_err;
			int power_mode;

			/* Set up ident to hold arg1 */
			if (name(sh(arg1)) == shrealhd) {
				arg1 = f_change_floating_variety(f_impossible, realfv, arg1);
			}
			id = me_startid(f_top, arg1, 0);

			/* Set up power_mode */
			switch (mode) {
			case R2ZERO: power_mode = 0; break;
			case R2NEAR: power_mode = 1; break;
			case R2PINF: power_mode = 2; break;
			case R2NINF: power_mode = 3; break;
			default:     power_mode = 1; break;
			}

			/* Work out which functions to call */
			if (sgned) {
				nm = "__TDFrnd_sgned";
				nm_err = "__TDFerr_rnd_sgned";
			} else {
				nm = "__TDFrnd_unsgned";
				nm_err = "__TDFerr_rnd_unsgned";
			}

			{
				exp_list pars2;
				exp_option no_var;
				pars2 = new_exp_list(2);
				no_var.present = 0;
				pars2 = add_exp_list(pars2, me_obtain(id), 0);
				pars2 = add_exp_list(pars2, me_shint(uwordsh, power_mode), 1);
				apply2 = f_apply_proc(sgned ? slongsh : ulongsh,
					me_obtain(find_named_tg(nm, f_proc)), pars2, no_var);
			}

			if (err) {
				exp_list st;
				exp seq;
				exp pl;
				exp_list pars1;
				exp_option no_var;
				no_var.present = 0;

				pars1 = new_exp_list(2);
				pars1 = add_exp_list(pars1, me_obtain(id), 0);
				pars1 = add_exp_list(pars1, me_shint(uwordsh, power_mode), 1);
				apply1 = f_apply_proc(f_top, me_obtain(find_named_tg(nm_err, f_proc)),
				                      pars1, no_var);

				pl = f_plus(flpt_err, me_shint(slongsh, INT_MAX),
				            me_obtain(find_named_tg("__TDFrnd_error", slongsh)));
				st = new_exp_list(2);
				st = add_exp_list(st, apply1, 0);
				st = add_exp_list(st, pl, 1);
				seq = f_sequence(st, apply2);
				id = me_complete_id(id, seq);
			} else {
				id = me_complete_id(id, apply2);
			}

			if (shp_sze < 32) {
				id = f_change_variety(flpt_err, f_integer(r), id);
			}

			return id;
		}
	}
	/* FALL THROUGH */
#endif

	res = getexp(f_integer(r), NULL, 0, arg1, NULL, 0, 0, round_tag);
	setround_number(res, mode);
	seterrhandle(res, flpt_err.err_code);

	if (flpt_err.err_code == 4) {
		setjmp_dest(res, get_lab(flpt_err.jmp_dest));
	}

	setfather(res, arg1);
	return res;
}

floating_variety
f_flvar_parms(nat base, nat mantissa_digits,
	nat minimum_exponent, nat maximum_exponent)
{
	int b = natint(base);
	int mantdig = natint(mantissa_digits);
	int neg_minexp = natint(minimum_exponent);
	int maxexp = natint(maximum_exponent);

	while (b != 2) {
		if ((b & 1) != 0) {
			error(ERR_INTERNAL, "base in flvar_parms must be a power of 2");
		}

		mantdig += mantdig;
		neg_minexp += neg_minexp;
		maxexp += maxexp;

		b = (b >> 1);
	}

	if (mantdig <= 24 && neg_minexp <= 126 && maxexp <= 127) {
		return 0;
	}

	if (mantdig <= 53 && neg_minexp <= 1022 && maxexp <= 1023) {
		return 1;
	}

	if ((has & HAS_LONG_DOUBLE)) {
		if (mantdig <= 64 && neg_minexp <= 16382 && maxexp <= 16383) {
			return 2;
		}

		return 2;
	} else {
		return 1;
	}
}

floating_variety
f_complex_parms(nat base, nat mantissa_digits, nat minimum_exponent,
                nat maximum_exponent)
{
	return float_to_complex_var(f_flvar_parms(base, mantissa_digits,
		minimum_exponent, maximum_exponent));
}

void
init_floating_variety(void)
{
	shrealsh = getshape(0, const_al1, const_al1, SHREAL_ALIGN, SHREAL_SZ, shrealhd);
	realsh = getshape(0, const_al1, const_al1, REAL_ALIGN, REAL_SZ, realhd);
	doublesh = getshape(0, const_al1, const_al1, DOUBLE_ALIGN, DOUBLE_SZ, doublehd);

	if (~has & HAS_COMPLEX) {
		shcomplexsh = getshape(0, const_al1, const_al1, SHREAL_ALIGN, 2 * SHREAL_SZ, cpdhd);
		complexsh = getshape(0, const_al1, const_al1, REAL_ALIGN, 2 * REAL_SZ, cpdhd);
		complexdoublesh = getshape(0, const_al1, const_al1, DOUBLE_ALIGN, 2 * DOUBLE_SZ, cpdhd);
	} else {
		shcomplexsh = getshape(0, const_al1, const_al1, SHREAL_ALIGN, 2 * SHREAL_SZ, shcomplexhd);
		complexsh = getshape(0, const_al1, const_al1, REAL_ALIGN, 2 * REAL_SZ, complexhd);
		complexdoublesh = getshape(0, const_al1, const_al1,
			DOUBLE_ALIGN, 2 * DOUBLE_SZ, complexdoublehd);
	}
}

floating_variety f_dummy_floating_variety;

floating_variety
f_float_of_complex(shape sha)
{
	int s = shape_size(sha) / 2;

	if (s == SHREAL_SZ) {
		return shrealfv;
	}

	if (s == REAL_SZ) {
		return realfv;
	}

	if (s == DOUBLE_SZ) {
		return doublefv;
	}

	error(ERR_INTERNAL, "Expecting a complex shape");

	return f_dummy_floating_variety;
}

floating_variety
f_complex_of_float(shape sha)
{
	int s = shape_size(sha);

	if (s == SHREAL_SZ) {
		return shcomplexfv;
	}

	if (s == REAL_SZ) {
		return complexfv;
	}

	if (s == DOUBLE_SZ) {
		return complexdoublefv;
	}

	error(ERR_INTERNAL, "Expecting a floating shape");
	return f_dummy_floating_variety;
}

static floating_variety
fv_of_shape(shape sha)
{
	int s = shape_size(sha);

	if (s == SHREAL_SZ) {
		return shrealfv;
	}

	if (s == REAL_SZ) {
		return realfv;
	}

	if (s == DOUBLE_SZ) {
		return doublefv;
	}

	error(ERR_INTERNAL, "Expecting a complex shape");

	return f_dummy_floating_variety;
}

static
void square_x_iy(error_treatment ov_err, exp *arg1, exp *arg2, exp arg3)
{
	exp x = *arg1;
	exp y = *arg2;

	exp obtain1_x = me_obtain(x);
	exp obtain2_x = me_obtain(x);
	exp obtain3_x = me_obtain(x);
	exp obtain1_y = me_obtain(y);
	exp obtain2_y = me_obtain(y);
	exp obtain3_y = me_obtain(y);

	exp minus_x_y = f_floating_minus(ov_err, obtain1_x, obtain1_y);
	exp plus_x_y = f_bin_floating_plus(ov_err, obtain2_x, obtain2_y);
	exp mult_x_y = f_bin_floating_mult(ov_err, obtain3_x, obtain3_y);

	exp tmp = push(arg3, me_startid(sh(x), mult_x_y, 0));

	exp obtain1_tmp = hold_refactor(me_obtain(tmp));
	exp obtain2_tmp = hold_refactor(me_obtain(tmp));

	exp answer_re = f_bin_floating_mult(ov_err, minus_x_y, plus_x_y);
	exp answer_im = f_bin_floating_plus(ov_err, obtain1_tmp, obtain2_tmp);

	x = push(tmp, me_startid(sh(x), answer_re, 0));
	y = push(x, me_startid(sh(x), answer_im, 0));

	*arg1 = x;
	*arg2 = y;
}

static
void mult_w_by_z(error_treatment ov_err, exp *arg1, exp *arg2, exp arg3,
                 exp arg4, exp arg5)
{
	exp u = *arg1;
	exp v = *arg2;
	exp x =  arg3;
	exp y =  arg4;

	exp obtain1_x = me_obtain(x);
	exp obtain2_x = me_obtain(x);
	exp obtain1_y = me_obtain(y);
	exp obtain2_y = me_obtain(y);

	exp obtain1_u = me_obtain(u);
	exp obtain2_u = me_obtain(u);
	exp obtain1_v = me_obtain(v);
	exp obtain2_v = me_obtain(v);

	exp mult_x_u = f_bin_floating_mult(ov_err, obtain1_x, obtain1_u);
	exp mult_x_v = f_bin_floating_mult(ov_err, obtain2_x, obtain1_v);
	exp mult_y_u = f_bin_floating_mult(ov_err, obtain1_y, obtain2_u);
	exp mult_y_v = f_bin_floating_mult(ov_err, obtain2_y, obtain2_v);

	exp tmp = push(arg5, me_startid(sh(x), mult_y_u, 0));
	exp obtain_tmp = hold_refactor(me_obtain(tmp));

	exp answer_re = f_floating_minus(ov_err, mult_x_u, mult_y_v);
	exp answer_im = f_bin_floating_plus(ov_err, mult_x_v, obtain_tmp);

	u = push(tmp, me_startid(sh(x), answer_re, 0));
	v = push(u, me_startid(sh(x), answer_im, 0));

	*arg1 = u;
	*arg2 = v;
}

static exp
make_comp_1_z(floating_variety complex_fv, error_treatment ov_err,
              exp contents1_u, exp contents2_u, exp contents3_u,
              exp contents1_v, exp contents2_v, exp contents3_v)
{
	exp mult_u_u = f_bin_floating_mult(ov_err, contents1_u, contents2_u);
	exp mult_v_v = f_bin_floating_mult(ov_err, contents1_v, contents2_v);
	exp mod_squared = f_bin_floating_plus(ov_err, mult_u_u, mult_v_v);
	exp mod_sq = me_startid(sh(contents1_u), mod_squared, 0);

	exp obtain1_mod_sq = me_obtain(mod_sq);
	exp obtain2_mod_sq = me_obtain(mod_sq);

	exp v_div_mod_sq = f_floating_div(ov_err, contents3_v, obtain2_mod_sq);

	exp answer_re = f_floating_div(ov_err, contents3_u, obtain1_mod_sq);
	exp answer_im = f_floating_negate(ov_err, v_div_mod_sq);

	exp make_comp = f_make_complex(complex_fv, answer_re, answer_im);
	return me_complete_id(mod_sq, make_comp);
}

#define is_const(X)	(name(X) != ident_tag)

static exp_list
reorder_list(exp_list arg1, int consts_first)
{
	exp type1_start, type1_end, type2_start, type2_end, t;

	type1_start = type1_end = type2_start = type2_end = NULL;
	setbro(arg1.end, NULL);

	for (t = arg1.start; t != arg1.end; t = bro(t)) {
		if ((is_const(t) && consts_first) || !(is_const(t) || consts_first)) {
			if (type1_start == NULL) {
				type1_start = type1_end = t;	/* first of type 1 */
			} else {
				setbro(type1_end, t);		/* add to existing type 1's */
				type1_end = t;
			}
		} else {
			if (type2_start == NULL) {
				type2_start = type2_end = t;	/* first of type 2 */
			} else {
				setbro(type2_end, t);		/* add to existing type 2's */
				type2_end = t;
			}
		}
	}

	if ((type1_start != NULL) && (type2_start != NULL)) {
		arg1.start = type1_start;
		setbro(type1_end, type2_start);	/* if list is not a mixture */
		arg1.end = type2_end;		/* no reordering has to be done */
	}

	return arg1;
}

static exp
me_contents(exp arg1)
{
	exp r = me_u3(sh(arg1), me_obtain(arg1), cont_tag);

	return hold_refactor(r);
}

/*
 * Used in conjunction with the function "me_complete_chain",
 * this function is used to push "ident_tag" declarations onto a "stack"
 * so that they can be linked up later.
 *
 * It is used in loops where the number of "ident_tag"s is unknown
 * and they need to be bound together in a "first-used last-bound" order
 * - hence the stack.
 *
 * arg1 is the new element
 * arg2 is the top element on the stack
 */
static exp
push(exp arg1, exp arg2)
{
	setbro(arg2, arg1);
	return arg2;
}

/*
 * Take the stack full of "ident_tag" declarations and link them together
 * with the last element in the list being "last_link" and the body
 * around which the declarations are put be "link_to".
 */
static exp
me_complete_chain(exp ident_chain, exp last_link, exp link_to)
{
	exp remove_link;

	while (son(ident_chain) != last_link) {
		remove_link = bro(ident_chain);
		link_to = me_complete_id(ident_chain, link_to);
		ident_chain = remove_link;
	}

	return me_complete_id(ident_chain, link_to);
}

/*
 * Binary version of 'f_floating_plus'
 */
static exp
f_bin_floating_plus(error_treatment ov_err, exp arg1, exp arg2)
{
	exp_list el;

	el = new_exp_list(2);
	el = add_exp_list(el, arg1, 0);
	el = add_exp_list(el, arg2, 1);

	return f_floating_plus(ov_err, el);
}

/*
 * Binary version of 'f_floating_mult'
 */
static exp
f_bin_floating_mult(error_treatment ov_err, exp arg1, exp arg2)
{
	exp_list el;

	el = new_exp_list(2);
	el = add_exp_list(el, arg1, 0);
	el = add_exp_list(el, arg2, 1);

	return f_floating_mult(ov_err, el);
}

static exp
optimise_with_wrap(exp arg, shape shape1, shape shape2)
{
	if (!eq_shape(shape1, shape2)) {
		return f_change_variety(f_wrap, shape2, arg);
	}

	return arg;
}

static exp
real_power(error_treatment ov_err, exp arg1, exp arg2)
{
	/* Gives shorter .s file if n<10 and arg1 is unknown */

	exp real1, sn;
	exp(*f_real_mult)(error_treatment, exp, exp);
	shape real_shape, integer_shape, tmp_shape;

	/* With wrap, we may as well work with 'int's and change back after */

	tmp_shape = sh(arg1);
	if (is_integer(tmp_shape) && !is_signed(tmp_shape) &&
	    shape_size(sh(arg1)) < 32 && eq_et(ov_err, f_wrap)) {
		arg1 = hold_refactor(f_change_variety(f_impossible, ulongsh, arg1));
	}

	/* Widen to 'int' if necessary - guarantees negate will work */

	if (shape_size(sh(arg2)) < 32) {
		arg2 = hold_refactor(f_change_variety(f_impossible, slongsh, arg2));
	}

	real_shape = sh(arg1);	/* shape of the result */
	integer_shape = sh(arg2);
	sn = me_startid(integer_shape, arg2, 0);

	/* Identify an exp which represents the value 1 (or 1.0) */

	if (is_integer(real_shape)) {
		real1 = me_shint(real_shape, 1);
	} else {
		real1 = me_shint(integer_shape, 1);
		real1 = f_float_int(f_impossible, fv_of_shape(real_shape), real1);
		real1 = hold_refactor(real1);	/* This should be reduced to 1.0 */
	}
	real1 = push(sn, me_startid(real_shape, real1, 0));

	/* Decide which is the suitable function for multiplying two numbers */

	f_real_mult = (is_integer(real_shape) ? f_mult : f_bin_floating_mult);

	if (is_constant_arg(arg2) ||
	    ((name(arg2) == name_tag) && (name(son(arg2)) == ident_tag) &&
	     !isvar(son(arg2)) && is_constant_arg(son(son(arg2))))) {
		/* we know the power */
		int exponent;
		exp x;

		if (is_constant_arg(arg2)) {
			exponent = no(arg2);	/* arg2 is a constant */
		} else {
			exponent = no(son(son(arg2)));
			/* arg2 identifies a constant */
		}

		if (exponent < 0) {
			if (is_integer(real_shape)) {
				error(ERR_INTERNAL, "constant value out of range: power: must be non-negative");
			} else {
				/* take reciprocal */
				arg1 = hold_refactor(f_floating_div(ov_err, me_obtain(real1),
				                                    arg1));
			}
		}
		x = push(real1, me_startid(real_shape, arg1, 0));

		if (exponent == 0) {
			return me_complete_chain(x, arg2, optimise_with_wrap(me_obtain(real1),
				real_shape, tmp_shape));
		}

		{
			exp w, mylast = x;
			int n = abs(exponent);

			while ((n % 2) == 0) {
				exp mult_x_x;
				mult_x_x = (*f_real_mult)(ov_err, me_obtain(x), me_obtain(x));
				mylast = x = push(mylast, me_startid(real_shape,
				                                     hold_refactor(mult_x_x), 0));
				n = n / 2;
			}

			if (n == 1) {
				/* return x  */
				return me_complete_chain(x, arg2, optimise_with_wrap(me_obtain(x),
				                                 real_shape, tmp_shape));
			} else {
				/*  w = x  */
				mylast = w = push(x, me_startid(real_shape, me_obtain(x), 0));
			}

			while (n != 1) {
				exp mult_x_x;
				mult_x_x = (*f_real_mult)(ov_err, me_obtain(x), me_obtain(x));
				mylast = x = push(mylast, me_startid(real_shape,
				                                     hold_refactor(mult_x_x), 0));
				n = n / 2;
				if ((n % 2) == 1) {
					exp mult_w_x;
					mult_w_x = (*f_real_mult)(ov_err, me_obtain(w), me_obtain(x));
					mylast = w = push(mylast, me_startid(real_shape,
						hold_refactor(mult_w_x), 0));
				}
			}

			/*  return w  */
			return me_complete_chain(w, arg2, optimise_with_wrap(me_obtain(w),
			                         real_shape, tmp_shape));
		}
	} else {
		exp reinitialise_w, main_loop, make_comp; /* main building blocks */
		exp square_x, mult_x_w, half_n, update_w, repeat_body;
		exp seq, w, x, n;

		n = me_obtain(sn);
		if (!is_integer(real_shape)) { /* Must be positive for integer powers */
			n = f_abs(f_impossible, n);
		}

		n = push(real1, me_startid(integer_shape, n, 1));
		w = push(n, me_startid(real_shape, me_obtain(real1), 1));
		x = push(w, me_startid(real_shape, arg1, 1));

		/* change value of w to z if n is odd  */
		{
			exp rem_n_2 = f_and(me_contents(n), me_shint(integer_shape, 1));
			exp assign_w = f_assign(me_obtain(w), me_contents(x));
			exp alt_labst = hold_refactor(me_b3(f_top, f_make_value(f_top),
			                                    f_make_top(), labst_tag));
			exp is_n_odd = f_integer_test(no_nat_option, f_equal,
			                              make_label(alt_labst), rem_n_2,
			                              me_shint(integer_shape, 1));
			exp seq = f_sequence(add_exp_list(new_exp_list(1), is_n_odd, 0), assign_w);
			reinitialise_w = hold_refactor(me_b3(lub_shape(sh(seq), sh(alt_labst)),
			                                     seq, alt_labst, cond_tag));
		}

		/* x = x * x */
		{
			exp mult_x_x;
			mult_x_x = (*f_real_mult)(ov_err, me_contents(x), me_contents(x));
			square_x = f_assign(me_obtain(x), mult_x_x);
		}

		/* w = x * w */
		{
			exp answer;
			answer = (*f_real_mult)(ov_err, me_contents(x), me_contents(w));
			mult_x_w = f_assign(me_obtain(w), answer);
		}

		/* n = n / 2 */
		{
			exp answer = f_shift_right(me_contents(n),
			                           me_shint(integer_shape, 1));
			half_n = f_assign(me_obtain(n), answer);
		}

		/* if n is odd then w = z * w */
		{
			exp rem_n_2 = f_and(me_contents(n), me_shint(integer_shape, 1));
			exp alt_labst = hold_refactor(me_b3(f_top, f_make_value(f_top),
			                                    f_make_top(), labst_tag));
			exp is_n_odd = f_integer_test(no_nat_option, f_equal,
			                              make_label(alt_labst),
			                              rem_n_2, me_shint(integer_shape, 1));
			exp seq = f_sequence(add_exp_list(new_exp_list(1),
			                                  is_n_odd, 0), mult_x_w);
			update_w = hold_refactor(me_b3(lub_shape(sh(seq), sh(alt_labst)),
			                               seq, alt_labst, cond_tag));
		}

		/* repeat + body */
		{
			exp body_labst, if_n_equals_1;
			exp_list st;

			body_labst = hold_refactor(me_b3(f_top, f_make_value(f_top),
			                                 f_make_top(), labst_tag));

			if_n_equals_1 = f_integer_test(no_nat_option, f_equal,
			                               make_label(body_labst),
			                               me_contents(n),
			                               me_shint(integer_shape, 1));

			st = new_exp_list(1);
			st = add_exp_list(st, square_x, 0);
			st = add_exp_list(st, half_n, 1);
			st = add_exp_list(st, update_w, 2);
			seq = f_sequence(st, if_n_equals_1);

			setbro(son(body_labst), seq);
			setsh (body_labst, sh (seq));	/*  put seq into the body  */
			clearlast (son(body_labst));	/*  of the labst           */
			setfather(body_labst, seq);

			repeat_body = hold_refactor(me_b3(sh(body_labst), f_make_top(),
			                                  body_labst, rep_tag));
			note_repeat(repeat_body);
		}

		/* make loop - only done if  mod(n) > 1 */
		{
			exp alt_labst = hold_refactor(me_b3(f_top, f_make_value(f_top),
			                                    f_make_top(), labst_tag));
			exp is_n_gt_1 = f_integer_test(no_nat_option, f_greater_than,
			                               make_label(alt_labst),
			                               me_contents(n),
			                               me_shint(integer_shape, 1));
			exp seq = f_sequence(add_exp_list(new_exp_list(1),
			                                  is_n_gt_1, 0), repeat_body);
			main_loop = hold_refactor(me_b3(lub_shape(sh(seq), sh(alt_labst)),
			                                seq, alt_labst, cond_tag));
		}

		if (is_integer(real_shape)) {
			make_comp = me_contents(w);
		} else {
			exp make_comp2 = f_floating_div(ov_err, me_obtain(real1),
			                                me_contents(w));
			exp alt_labst = hold_refactor(me_b3(real_shape, f_make_value(f_top),
			                                    make_comp2, labst_tag));
			exp is_arg2_positive = f_integer_test(no_nat_option,
			                                      f_greater_than_or_equal,
			                                      make_label(alt_labst),
			                                      me_obtain(sn),
			                                      me_shint(integer_shape, 0));
			exp seq = f_sequence(add_exp_list(new_exp_list(1),
			                                  is_arg2_positive, 0),
			                     me_contents(w));

			make_comp = hold_refactor(me_b3(lub_shape(sh(seq), sh(alt_labst)), seq,
			                                alt_labst, cond_tag));
		}

		seq = f_sequence(add_exp_list(add_exp_list(new_exp_list(1),
		                              reinitialise_w, 0),
		                              main_loop, 1), make_comp);
		seq = optimise_with_wrap(seq, real_shape, tmp_shape);
		return  me_complete_chain(x, arg2, seq);
	}
}

