/*
 * Copyright 2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "ieee754.tpl"

Tokdef .~abi_float_rep      = [] NAT iee754_float_rep;
Tokdef .~abi_double_rep     = [] NAT iee754_double_rep;
Tokdef .~abi_longdouble_rep = [] NAT iee754_ext80_rep;

Keep (
	.~rep_fv, .~rep_fv_width, .~rep_fv_radix, .~rep_fv_mantissa, .~rep_fv_min_exp,
	.~rep_fv_max_exp, .~rep_fv_epsilon, .~rep_fv_min_val, .~rep_fv_max_val,
	.~rep_fv_min_norm_val, .~rep_fv_max_10_exp, .~rep_fv_dig,

	.~abi_float_rep, .~abi_double_rep, .~abi_longdouble_rep
)

