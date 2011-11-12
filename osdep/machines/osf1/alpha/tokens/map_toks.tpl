/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

	/* **************************************************** */
	/*							*/
	/*    Basic Mapping Token Definitions for dec_alpha	*/
	/*							*/
	/* **************************************************** */




	/* C MAPPING TOKENS */


Tokdef .~char_width = [] NAT
8;


Tokdef .~short_width = [] NAT
16;


Tokdef .~int_width = [] NAT
32;


Tokdef .~long_width = [] NAT
64;


Tokdef .~longlong_width = [] NAT
64;


Tokdef .~size_t_width = [] NAT
64;


Tokdef .~fl_rep = [] NAT
1;


Tokdef .~dbl_rep = [] NAT
2;


Tokdef .~ldbl_rep = [] NAT
2;


Tokdef .~pv_align = [] ALIGNMENT
alignment(integer(var_width(false,8)));


Tokdef .~min_struct_rep = [] NAT
8;


Tokdef .~char_is_signed = [] BOOL
true;


Tokdef .~bitfield_is_signed = [] BOOL
true;




	/* FORTRAN MAPPING TOKENS */


Tokdef .~F_char_width = [] NAT
8;


Tokdef .~F_int_width = [] NAT
32;


Tokdef .~F_fl_rep = [] NAT
1;


Tokdef .~F_dbl_rep = [] NAT
2;




Keep (
.~char_width, .~short_width, .~int_width, .~long_width, .~longlong_width,
.~size_t_width,
.~fl_rep, .~dbl_rep, .~ldbl_rep, .~pv_align, .~min_struct_rep,
.~char_is_signed, .~bitfield_is_signed,
.~F_char_width, .~F_int_width, .~F_fl_rep, .~F_dbl_rep
)
