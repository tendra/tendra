/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef SPECIAL_ARITH_CODES_H
#define SPECIAL_ARITH_CODES_H


/*
 * integer classes
 *     | ref data_structures:RANGE
 * 	   | use simple_ts.h:
 * 	   | ref syntax_analysis:type specifiers
 *     | ref tokenised objects:
 */

/* sizes */
enum {
	t_char  = 0,
	t_short = 1,
	t_int   = 2,
	t_long  = 3
};

/* signedness */
enum {
	t_none     = 0 << 2, /* no sign  */
	t_signed   = 1 << 2, /* signed   */
	t_unsigned = 2 << 2  /* unsigned */
};

#define variety_filter 3  /* masks to leave the size of a non-tokenised integer */
#define sign_filter    12 /* masks to leave the sign of a non-tokenised integer */

#define int_range (t_int | t_signed) /* the commonly used integer type 'int' */


/*
 * floating_types
 *     | ref data_structures:REALLEX
 *     | ref data_structures:floating types
 *     | use simple_ts.h:
 *     | ref syntax_analysis:type specifiers
 *     | ref data_structures:RANGE
 */
enum {
	t_float       = 0,
	t_double      = 1,
	t_long_double = 2
};

/* arithmetic_types */
#define int_to_arith(i)        (i)
#define arith_to_int(a)        (a)
#define float_to_arith(f)    (((f) << 3) | 0x80)
#define arith_to_float(a)    (((a) & 0x7f) >> 3)


#endif

