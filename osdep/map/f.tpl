/* $Id$ */

/*
 * Copyright 2014, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

Tokdec .~abi_char_width     : [] NAT;
Tokdec .~abi_short_width    : [] NAT;
Tokdec .~abi_int_width      : [] NAT;
Tokdec .~abi_long_width     : [] NAT;
Tokdec .~abi_longlong_width : [] NAT;
Tokdec .~abi_ptr_width      : [] NAT;

Tokdec .~abi_float_rep      : [] NAT;
Tokdec .~abi_double_rep     : [] NAT;

/*
 * Fortran mapping tokens
 */

Tokdef .~F_char_width = [] NAT .~abi_char_width;
Tokdef .~F_int_width  = [] NAT .~abi_int_width;

Tokdef .~F_fl_rep     = [] NAT .~abi_float_rep;
Tokdef .~F_dbl_rep    = [] NAT .~abi_double_rep;

Keep (
	.~F_char_width, .~F_int_width,
	.~F_fl_rep, .~F_dbl_rep
)

