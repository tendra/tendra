/* $Id$ */

/*
 * Copyright 2014, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

Tokdec .~model_char_width     : [] NAT;
Tokdec .~model_short_width    : [] NAT;
Tokdec .~model_int_width      : [] NAT;
Tokdec .~model_long_width     : [] NAT;
Tokdec .~model_longlong_width : [] NAT;
Tokdec .~model_ptr_width      : [] NAT;

/* Fortran mapping tokens */
Tokdef .~F_char_width = [] NAT .~model_char_width;
Tokdef .~F_int_width  = [] NAT .~model_int_width;

Keep (
	.~F_char_width, .~F_int_width
)

