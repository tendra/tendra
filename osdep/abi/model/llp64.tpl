/*
 * Copyright 2014, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

Tokdef .~abi_char_width     = [] NAT  8;
Tokdef .~abi_short_width    = [] NAT 16;
Tokdef .~abi_int_width      = [] NAT 32;
Tokdef .~abi_long_width     = [] NAT 32;
Tokdef .~abi_longlong_width = [] NAT 64;
Tokdef .~abi_ptr_width      = [] NAT 64;

Keep (
	.~abi_char_width, .~abi_short_width, .~abi_int_width,
	.~abi_long_width, .~abi_longlong_width, .~abi_ptr_width
)

