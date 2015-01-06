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
Tokdec .~abi_longdouble_rep : [] NAT;

Tokdec .~abi_char_is_signed : [] BOOL;

/*
 * C mapping tokens
 */

Tokdef .~char_width     = [] NAT .~abi_char_width;
Tokdef .~short_width    = [] NAT .~abi_short_width;
Tokdef .~int_width      = [] NAT .~abi_int_width;
Tokdef .~long_width     = [] NAT .~abi_long_width;
Tokdef .~longlong_width = [] NAT .~abi_longlong_width;
Tokdef .~size_t_width   = [] NAT .~abi_ptr_width;
Tokdef .~ptr_width      = [] NAT .~abi_ptr_width;

Tokdef .~fl_rep         = [] NAT .~abi_float_rep;
Tokdef .~dbl_rep        = [] NAT .~abi_double_rep;
Tokdef .~ldbl_rep       = [] NAT .~abi_longdouble_rep;

Tokdef .~char_is_signed = [] BOOL .~abi_char_is_signed;

Keep (
	.~char_width, .~short_width, .~int_width, .~long_width,
	.~longlong_width, .~size_t_width, .~ptr_width,
	.~fl_rep, .~dbl_rep, .~ldbl_rep,
	.~char_is_signed
)

