/*
 * Copyright 2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "var64.tpl"

Tokdef .~abi_rep_atomic_width = [] NAT 32;
Tokdef .~abi_best_div         = [] NAT 2;
Tokdef .~abi_little_endian    = [] BOOL true;

Keep (
	.~abi_rep_var_width,
	.~abi_rep_atomic_width, .~abi_best_div, .~abi_little_endian
)

