/*
 * Copyright 2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

Tokdec .~rep_fv_radix        : [NAT] NAT;
Tokdec .~rep_fv_width        : [NAT] NAT;
Tokdec .~rep_fv_mantissa     : [NAT] NAT;
Tokdec .~rep_fv_min_exp      : [NAT] NAT;
Tokdec .~rep_fv_max_exp      : [NAT] NAT;
Tokdec .~rep_fv              : [NAT] FLOATING_VARIETY;
Tokdec .~rep_fv_epsilon      : [NAT] EXP;
Tokdec .~rep_fv_min_val      : [NAT] EXP;
Tokdec .~rep_fv_max_val      : [NAT] EXP;
Tokdec .~rep_fv_min_norm_val : [NAT] EXP;
Tokdec .~rep_fv_max_10_exp   : [NAT] NAT;
Tokdec .~rep_fv_dig          : [NAT] NAT;

Tokdec .~abi_float_rep       : [] NAT;
Tokdec .~abi_double_rep      : [] NAT;
Tokdec .~abi_longdouble_rep  : [] NAT;

/* [n] is ignored */
Tokdef __PROXY_FLT_RADIX = [] EXP
	snat_from_nat(false, .~rep_fv_radix[.~abi_float_rep]) (Int);


Tokdef __PROXY_FLT_DIG = [] EXP
	snat_from_nat(false, .~rep_fv_dig[.~abi_float_rep]) (Int);

Tokdef __PROXY_FLT_EPSILON = [] EXP
	.~rep_fv_epsilon[.~abi_float_rep];

Tokdef __PROXY_FLT_MANT_DIG = [] EXP
	snat_from_nat(false, .~rep_fv_mantissa[.~abi_float_rep]) (Int);

Tokdef __PROXY_FLT_MIN = [] EXP
	.~rep_fv_min_norm_val[.~abi_float_rep];

Tokdef __PROXY_FLT_MAX = [] EXP
	.~rep_fv_max_val[.~abi_float_rep];

Tokdef __PROXY_FLT_MAX_10_EXP = [] EXP
	snat_from_nat(false, .~rep_fv_max_10_exp[.~abi_float_rep]) (Int);

Tokdef __PROXY_FLT_MIN_10_EXP = [] EXP
	-(snat_from_nat(false, .~rep_fv_max_10_exp[.~abi_float_rep]) (Int) - 1(Int));

Tokdef __PROXY_FLT_MAX_EXP = [] EXP
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
 * describes a normalised value. Here we encode __PROXY_FLT_MIN_EXP in terms of
 * .~rep_fv_max_exp instead.
 *
 * Here the -1 caters for IEEE 754's asymetric exponent range.
 *
 * The C macros FLT_MIN_EXP and FLT_MAX_EXP are responsible for adding
 * their own +1 offsets. So we do not need to take that into account here;
 * these tokens are written in terms of the IEEE 754 ranges.
 */
Tokdef __PROXY_FLT_MIN_EXP = [] EXP
	-(snat_from_nat(false, .~rep_fv_max_exp[.~abi_float_rep]) (Int) - 1(Int));


Tokdef __PROXY_DBL_DIG = [] EXP
	snat_from_nat(false, .~rep_fv_dig[.~abi_double_rep]) (Int);

Tokdef __PROXY_DBL_EPSILON = [] EXP
	.~rep_fv_epsilon[.~abi_double_rep];

Tokdef __PROXY_DBL_MANT_DIG = [] EXP
	snat_from_nat(false, .~rep_fv_mantissa[.~abi_double_rep]) (Int);

Tokdef __PROXY_DBL_MIN = [] EXP
	.~rep_fv_min_norm_val[.~abi_double_rep];

Tokdef __PROXY_DBL_MAX = [] EXP
	.~rep_fv_max_val[.~abi_double_rep];

Tokdef __PROXY_DBL_MAX_10_EXP = [] EXP
	snat_from_nat(false, .~rep_fv_max_10_exp[.~abi_double_rep]) (Int);

Tokdef __PROXY_DBL_MIN_10_EXP = [] EXP
	-(snat_from_nat(false, .~rep_fv_max_10_exp[.~abi_double_rep]) (Int) - 1(Int));

Tokdef __PROXY_DBL_MAX_EXP = [] EXP
	snat_from_nat(false, .~rep_fv_max_exp[.~abi_double_rep]) (Int);

Tokdef __PROXY_DBL_MIN_EXP = [] EXP
	-(snat_from_nat(false, .~rep_fv_max_exp[.~abi_double_rep]) (Int) - 1(Int));


Tokdef __PROXY_LDBL_DIG = [] EXP
	snat_from_nat(false, .~rep_fv_dig[.~abi_longdouble_rep]) (Int);

Tokdef __PROXY_LDBL_EPSILON = [] EXP
	.~rep_fv_epsilon[.~abi_longdouble_rep];

Tokdef __PROXY_LDBL_MANT_DIG = [] EXP
	snat_from_nat(false, .~rep_fv_mantissa[.~abi_longdouble_rep]) (Int);

Tokdef __PROXY_LDBL_MIN = [] EXP
	.~rep_fv_min_norm_val[.~abi_longdouble_rep];

Tokdef __PROXY_LDBL_MAX = [] EXP
	.~rep_fv_max_val[.~abi_longdouble_rep];

Tokdef __PROXY_LDBL_MAX_10_EXP = [] EXP
	snat_from_nat(false, .~rep_fv_max_10_exp[.~abi_longdouble_rep]) (Int);

Tokdef __PROXY_LDBL_MIN_10_EXP = [] EXP
	-(snat_from_nat(false, .~rep_fv_max_10_exp[.~abi_longdouble_rep]) (Int) - 1(Int));

Tokdef __PROXY_LDBL_MAX_EXP = [] EXP
	snat_from_nat(false, .~rep_fv_max_exp[.~abi_longdouble_rep]) (Int);

Tokdef __PROXY_LDBL_MIN_EXP = [] EXP
	-(snat_from_nat(false, .~rep_fv_max_exp[.~abi_longdouble_rep]) (Int) - 1(Int));


Keep (
	__PROXY_FLT_RADIX,

	__PROXY_FLT_DIG,
	__PROXY_FLT_EPSILON,
	__PROXY_FLT_MANT_DIG,
	__PROXY_FLT_MIN,
	__PROXY_FLT_MAX,
	__PROXY_FLT_MIN_10_EXP,
	__PROXY_FLT_MAX_10_EXP,
	__PROXY_FLT_MIN_EXP,
	__PROXY_FLT_MAX_EXP,

	__PROXY_DBL_DIG,
	__PROXY_DBL_EPSILON,
	__PROXY_DBL_MANT_DIG,
	__PROXY_DBL_MIN,
	__PROXY_DBL_MAX,
	__PROXY_DBL_MIN_10_EXP,
	__PROXY_DBL_MAX_10_EXP,
	__PROXY_DBL_MIN_EXP,
	__PROXY_DBL_MAX_EXP,

	__PROXY_LDBL_DIG,
	__PROXY_LDBL_EPSILON,
	__PROXY_LDBL_MANT_DIG,
	__PROXY_LDBL_MIN,
	__PROXY_LDBL_MAX,
	__PROXY_LDBL_MIN_10_EXP,
	__PROXY_LDBL_MAX_10_EXP,
	__PROXY_LDBL_MIN_EXP,
	__PROXY_LDBL_MAX_EXP
)

