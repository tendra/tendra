/* $Id$ */

/*
 * Copyright 2014, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

Tokdef .~model_char_width     = [] NAT  8;
Tokdef .~model_short_width    = [] NAT 16;
Tokdef .~model_int_width      = [] NAT 32;
Tokdef .~model_long_width     = [] NAT 32;
Tokdef .~model_longlong_width = [] NAT 64;
Tokdef .~model_ptr_width      = [] NAT 64;

Keep (
	.~model_char_width, .~model_short_width, .~model_int_width,
	.~model_long_width, .~model_longlong_width, .~model_ptr_width
)

