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

/* C mapping tokens */
Tokdef .~char_width     = [] NAT .~model_char_width;
Tokdef .~short_width    = [] NAT .~model_short_width;
Tokdef .~int_width      = [] NAT .~model_int_width;
Tokdef .~long_width     = [] NAT .~model_long_width;
Tokdef .~longlong_width = [] NAT .~model_longlong_width;
Tokdef .~size_t_width   = [] NAT .~model_ptr_width;
Tokdef .~ptr_width      = [] NAT .~model_ptr_width;

Keep (
	.~char_width, .~short_width, .~int_width, .~long_width,
	.~longlong_width, .~size_t_width, .~ptr_width
)

