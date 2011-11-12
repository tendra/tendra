/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef ARITH_CODES_H
#define ARITH_CODES_H


/* integer classes	| ref data_structures:RANGE
 *			| use simple_ts.h:
 *			| ref syntax_analysis:type specifiers
 *			| ref tokenised objects:
 */
/*sizes*/
#define t_char		(0)	/*char*/
#define t_short		(1)	/*short*/
#define t_int		(2)	/*int*/
#define t_long		(3)	/*long*/
/*signedness*/
#define t_none		(0)	/* 0>>2 no sign*/
#define t_signed	(4)	/* 1>>2 signed*/
#define t_unsigned	(8)	/* 2>>2 unsigned*/

#define variety_filter	(3)	/*masks to leave the size of a non-tokenised integer*/
#define sign_filter	(12)	/*masks to leave the sign of a non-tokenised integer*/

#define int_range (t_int|t_signed) /*the commonly used integer type 'int'*/



/* floating_types	| ref data_structures:REALLEX
 *			| ref data_structures:floating types
 *			| use simple_ts.h:
 *			| ref syntax_analysis:type specifiers
 *			| ref data_structures:RANGE
 */
#define t_float		(0)	/*float*/
#define t_double	(1)	/*double*/
#define t_long_double	(2)	/*long double*/

/* arithmetic_types */
#define int_to_arith(i)		(i)
#define arith_to_int(a)		(a)
#define float_to_arith(f)	(((f) <<3) |0x80)
#define arith_to_float(a)	(((a) &0x7f) >>3)


#endif /* ARITH_CODES_H */
