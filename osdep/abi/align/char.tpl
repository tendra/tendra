/*
 * Copyright 2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

Tokdec .~abi_char_width : [] NAT;

Tokdef .~abi_pv_align = [] ALIGNMENT
	alignment(integer(var_width(false, .~abi_char_width)));

Keep (
	.~abi_pv_align
)

