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


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:45 $
$Revision: 1.1.1.1 $
$Log: arith_codes.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:45  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/06  10:43:34  currie
 * Initial revision
 *
***********************************************************************/
#ifndef ARITH_CODES_H
#define ARITH_CODES_H


/****integer classes	| ref data_structures:RANGE
 ****			| use simple_ts.h:
 ****			| ref syntax_analysis:type specifiers
 ****			| ref tokenised objects:
 ****/ 
/*sizes*/
#define t_char		(0)		/*char*/
#define t_short		(1)		/*short*/
#define t_int		(2)			/*int*/
#define t_long		(3)		/*long*/
/*signedness*/
#define t_none		(0)		/* 0>>2 no sign*/
#define t_signed	(4)		/* 1>>2 signed*/
#define t_unsigned	(8)		/* 2>>2 unsigned*/

#define variety_filter	(3)	/*masks to leave the size of a non-tokenised integer*/
#define sign_filter	(12)	/*masks to leave the sign of a non-tokenised integer*/

#define int_range (t_int|t_signed) /*the commonly used integer type 'int'*/



/****floating_types	| ref data_structures:REALLEX
 ****			| ref data_structures:floating types
 ****			| use simple_ts.h:
 ****			| ref syntax_analysis:type specifiers
 ****			| ref data_structures:RANGE
 ****/
#define t_float		(0)	/*float*/
#define t_double	(1)	/*double*/
#define t_long_double	(2)	/*long double*/

/****arithmetic_types
 ****/
#define int_to_arith(i)(i)
#define arith_to_int(a)(a)
#define float_to_arith(f)(((f)<<3)|0x80)
#define arith_to_float(a)(((a)&0x7f)>>3)


#endif
