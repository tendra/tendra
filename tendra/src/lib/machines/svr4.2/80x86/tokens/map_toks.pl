/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/
	/* **************************************************** */
	/*							*/
	/*    Basic Mapping Token Definitions for svr4_i386	*/
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
32;


Tokdef .~longlong_width = [] NAT
64;


Tokdef .~size_t_width = [] NAT
32;


Tokdef .~fl_rep = [] NAT
1;


Tokdef .~dbl_rep = [] NAT
2;


Tokdef .~ldbl_rep = [] NAT
3;


Tokdef .~pv_align = [] ALIGNMENT
alignment(integer(var_width(false,8)));


Tokdef .~min_struct_rep = [] NAT
8;


Tokdef .~char_is_signed = [] BOOL
true;


Tokdef .~bitfield_is_signed = [] BOOL
false;




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
