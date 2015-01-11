/* $Id$ */

/*
 * Copyright 2015, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

Tokdec .~abi_rep_var_width    : [NAT] NAT;
Tokdec .~abi_rep_atomic_width : [] NAT;
Tokdec .~abi_best_div         : [] NAT;
Tokdec .~abi_little_endian    : [] BOOL;

Tokdef .~rep_var_width    = [w:NAT] NAT .~abi_rep_var_width[w];
Tokdef .~rep_atomic_width = [] NAT .~abi_rep_atomic_width;
Tokdef .~best_div         = [] NAT .~abi_best_div;
Tokdef .~little_endian    = [] BOOL .~abi_little_endian;

Keep (
	.~rep_var_width,
	.~rep_atomic_width, .~best_div, .~little_endian
)

