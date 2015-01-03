/* $Id$ */

/*
 * Copyright 2014, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* C mapping tokens */
Tokdef .~char_width     = [] NAT  8;
Tokdef .~short_width    = [] NAT 16;
Tokdef .~int_width      = [] NAT 64;
Tokdef .~long_width     = [] NAT 64;
Tokdef .~longlong_width = [] NAT 64; /* unofficial */
Tokdef .~size_t_width   = [] NAT 64;
Tokdef .~ptr_width      = [] NAT 64;

/* Fortran mapping tokens */
Tokdef .~F_char_width   = [] NAT  8;
Tokdef .~F_int_width    = [] NAT 64;

Keep (
	.~char_width, .~short_width, .~int_width, .~long_width, .~longlong_width,
	.~size_t_width, .~ptr_width,
	.~F_char_width, .~F_int_width
)

