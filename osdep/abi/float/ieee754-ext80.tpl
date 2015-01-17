/* $Id$ */

/*
 * Copyright 2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "ieee754.tpl"

Tokdef .~abi_float_rep      = [] NAT iee754_float_rep;
Tokdef .~abi_double_rep     = [] NAT iee754_double_rep;
Tokdef .~abi_longdouble_rep = [] NAT iee754_ext80_rep;

/*
 * XXX: these __ABI_ tokens could find a home elsewhere;
 * they are specific to the libc hacked includes which use them,
 * and portable wrt the float representation.
 *
 * Possibly could live as PL_TDF in the api/ directory under osdep/,
 * in which case the __ABI prefix would be better named __API.
 * These tokens are presented in terms of the C89 float.h macros.
 */

/* [n] is ignored */
Tokdef __ABI_FLT_RADIX = [] EXP
	snat_from_nat(false, .~rep_fv_radix   [.~abi_float_rep]) (Int);


Tokdef __ABI_FLT_DIG = [] EXP
	snat_from_nat(false, ieee754_dig[.~abi_float_rep]) (Int);

Tokdef __ABI_FLT_EPSILON = [] EXP
	.~rep_fv_epsilon[.~abi_float_rep];

Tokdef __ABI_FLT_MANT_DIG = [] EXP
	snat_from_nat(false, .~rep_fv_mantissa[.~abi_float_rep]) (Int);

Tokdef __ABI_FLT_MIN = [] EXP
	ieee754_min_val[.~abi_float_rep];

Tokdef __ABI_FLT_MAX = [] EXP
	.~rep_fv_max_val[.~abi_float_rep];

Tokdef __ABI_FLT_MAX_10_EXP = [] EXP
	snat_from_nat(false, ieee754_max_10_exp[.~abi_float_rep]) (Int);

Tokdef __ABI_FLT_MIN_10_EXP = [] EXP
	-(snat_from_nat(false, ieee754_max_10_exp[.~abi_float_rep]) (Int) - 1(Int));

Tokdef __ABI_FLT_MAX_EXP = [] EXP
	snat_from_nat(false, .~rep_fv_max_exp[.~abi_float_rep]) (Int);

/*
 * C89 says:
 *
 *   FLT_MIN_EXP is the minimum negative integer such that FLT_RADIX raised
 *   to that power minus 1 is a normalized floating-point number, $e sub min$
 *
 * The Token Guide says:
 *
 *   .~rep_fv_min_exp(n) will be the maximum integer m such that
 *   (.~rep_fv_radix(n)) - m is exactly representable (though not
 *   necessarily normalised) by the FLOATING_VARIETY .~rep_fv(n).
 *
 * So .~rep_fv_min_exp isn't what we want for FLT_MIN_EXP, because FLT_MIN_EXP
 * describes a normalised value. Here we encode __ABI_FLT_MIN_EXP in terms of
 * .~rep_fv_max_exp instead.
 *
 * Here the -1 caters for IEEE 754's asymetric exponent range.
 *
 * The C macros FLT_MIN_EXP and FLT_MAX_EXP are responsible for adding
 * their own +1 offsets. So we do not need to take that into account here;
 * these tokens are written in terms of the IEEE 754 ranges.
 */
Tokdef __ABI_FLT_MIN_EXP = [] EXP
	-(snat_from_nat(false, .~rep_fv_max_exp[.~abi_float_rep]) (Int) - 1(Int));


Tokdef __ABI_DBL_DIG = [] EXP
	snat_from_nat(false, ieee754_dig[.~abi_double_rep]) (Int);

Tokdef __ABI_DBL_EPSILON = [] EXP
	.~rep_fv_epsilon[.~abi_double_rep];

Tokdef __ABI_DBL_MANT_DIG = [] EXP
	snat_from_nat(false, .~rep_fv_mantissa[.~abi_double_rep]) (Int);

Tokdef __ABI_DBL_MIN = [] EXP
	ieee754_min_val[.~abi_double_rep];

Tokdef __ABI_DBL_MAX = [] EXP
	.~rep_fv_max_val[.~abi_double_rep];

Tokdef __ABI_DBL_MAX_10_EXP = [] EXP
	snat_from_nat(false, ieee754_max_10_exp[.~abi_double_rep]) (Int);

Tokdef __ABI_DBL_MIN_10_EXP = [] EXP
	-(snat_from_nat(false, ieee754_max_10_exp[.~abi_double_rep]) (Int) - 1(Int));

Tokdef __ABI_DBL_MAX_EXP = [] EXP
	snat_from_nat(false, .~rep_fv_max_exp[.~abi_double_rep]) (Int);

Tokdef __ABI_DBL_MIN_EXP = [] EXP
	-(snat_from_nat(false, .~rep_fv_max_exp[.~abi_double_rep]) (Int) - 1(Int));


Tokdef __ABI_LDBL_DIG = [] EXP
	snat_from_nat(false, ieee754_dig[.~abi_longdouble_rep]) (Int);

Tokdef __ABI_LDBL_EPSILON = [] EXP
	.~rep_fv_epsilon[.~abi_longdouble_rep];

Tokdef __ABI_LDBL_MANT_DIG = [] EXP
	snat_from_nat(false, .~rep_fv_mantissa[.~abi_longdouble_rep]) (Int);

Tokdef __ABI_LDBL_MIN = [] EXP
	ieee754_min_val[.~abi_longdouble_rep];

Tokdef __ABI_LDBL_MAX = [] EXP
	.~rep_fv_max_val[.~abi_longdouble_rep];

Tokdef __ABI_LDBL_MAX_10_EXP = [] EXP
	snat_from_nat(false, ieee754_max_10_exp[.~abi_longdouble_rep]) (Int);

Tokdef __ABI_LDBL_MIN_10_EXP = [] EXP
	-(snat_from_nat(false, ieee754_max_10_exp[.~abi_longdouble_rep]) (Int) - 1(Int));

Tokdef __ABI_LDBL_MAX_EXP = [] EXP
	snat_from_nat(false, .~rep_fv_max_exp[.~abi_longdouble_rep]) (Int);

Tokdef __ABI_LDBL_MIN_EXP = [] EXP
	-(snat_from_nat(false, .~rep_fv_max_exp[.~abi_longdouble_rep]) (Int) - 1(Int));


Keep (
	.~rep_fv, .~rep_fv_width, .~rep_fv_radix, .~rep_fv_mantissa, .~rep_fv_min_exp,
	.~rep_fv_max_exp, .~rep_fv_epsilon, .~rep_fv_min_val, .~rep_fv_max_val,

	.~abi_float_rep, .~abi_double_rep, .~abi_longdouble_rep,

	__ABI_FLT_RADIX,

	__ABI_FLT_DIG,
	__ABI_FLT_EPSILON,
	__ABI_FLT_MANT_DIG,
	__ABI_FLT_MIN,
	__ABI_FLT_MAX,
	__ABI_FLT_MIN_10_EXP,
	__ABI_FLT_MAX_10_EXP,
	__ABI_FLT_MIN_EXP,
	__ABI_FLT_MAX_EXP,

	__ABI_DBL_DIG,
	__ABI_DBL_EPSILON,
	__ABI_DBL_MANT_DIG,
	__ABI_DBL_MIN,
	__ABI_DBL_MAX,
	__ABI_DBL_MIN_10_EXP,
	__ABI_DBL_MAX_10_EXP,
	__ABI_DBL_MIN_EXP,
	__ABI_DBL_MAX_EXP,

	__ABI_LDBL_DIG,
	__ABI_LDBL_EPSILON,
	__ABI_LDBL_MANT_DIG,
	__ABI_LDBL_MIN,
	__ABI_LDBL_MAX,
	__ABI_LDBL_MIN_10_EXP,
	__ABI_LDBL_MAX_10_EXP,
	__ABI_LDBL_MIN_EXP,
	__ABI_LDBL_MAX_EXP
)

