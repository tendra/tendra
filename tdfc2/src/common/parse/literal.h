/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef LITERAL_INCLUDED
#define LITERAL_INCLUDED


/*
    LITERAL CONSTRUCTION DECLARATIONS

    The routines in this module are concerned with the construction of
    integer, floating-point, character, string and boolean literal
    expressions.
*/

extern EXP make_literal_exp(string, int *, int);
extern EXP make_bool_exp(unsigned, unsigned);
extern EXP make_string_exp(STRING);

extern int is_zero_float(FLOAT);
extern int eq_float_lit(FLOAT, FLOAT);
extern int eq_string_lit(STRING, STRING);
extern unsigned test_bool_exp(EXP);
extern unsigned long eval_line_digits(string, unsigned *);
extern unsigned long get_multi_char(string, int *);
extern unsigned long get_string_char(STRING, int *);
extern void add_multi_char(string, unsigned long, int);
extern unsigned long eval_unicode(int, unsigned, int *, string *, ERROR *);
extern TYPE find_literal_type(NAT, int, int, string, int *);
extern TYPE find_char_type(NAT);
extern NAT round_float_lit(FLOAT, RMODE);
extern STRING new_string_lit(string, string, int);
extern STRING concat_string_lit(STRING, STRING);
extern STRING share_string_lit(STRING);
extern NAT eval_char_lit(STRING);
extern int get_char_value(EXP);
extern void begin_literal(int, int);
extern void add_range_literal(EXP, int);
extern void add_type_literal(TYPE);
extern void add_token_literal(IDENTIFIER, unsigned);
extern void set_string_qual(CV_SPEC);
extern void set_escape(EXP, EXP);
extern void set_char_lit(TYPE);
extern void init_literal(void);
extern int init_literal_map(const char *);

extern unsigned char digit_values[];
extern unsigned char escape_sequences[];
extern RMODE crt_round_mode;
extern CV_SPEC cv_string;


/*
    STRING TYPES

    The values STRING_* form a bitfield which is used to identify the
    various types of string literals.  The values CHAR_* are used to
    identify the various types of character in multibyte strings.
*/

enum {
	STRING_NONE  = 0x00U,
	STRING_CHAR  = 0x01U,
	STRING_WIDE  = 0x02U,
	STRING_MULTI = 0x04U,
	STRING_FAT   = 0x08U
};

enum {
	CHAR_SIMPLE,
	CHAR_ASCII,
	CHAR_OCTAL,
	CHAR_HEX,
	CHAR_UNI4,
	CHAR_UNI8,
	CHAR_NONE
};

#define MULTI_WIDTH 5


/*
    BOOLEAN VALUES

    These values give the boolean values, true and false, plus a third
    value indicating an indeterminate boolean.  A fourth error value is
    also given.
*/

enum {
	BOOL_FALSE,
	BOOL_TRUE,
	BOOL_UNKNOWN,
	BOOL_INVALID
};

#define BOOL_VALUE(C)		((C) ? BOOL_TRUE  : BOOL_FALSE)
#define BOOL_NEGATE(C)		((C) ? BOOL_FALSE : BOOL_TRUE )


/*
    LITERAL BASE AND SUFFIX VALUES

    These values are used to identify the various bases and suffixes for
    integer literals.
*/

enum {
	BASE_DECIMAL,
	BASE_OCTAL,
	BASE_HEXADECIMAL,
	BASE_NO
};

enum {
	SUFFIX_NONE,
	SUFFIX_U,
	SUFFIX_L,
	SUFFIX_UL,
	SUFFIX_LL,
	SUFFIX_ULL,
	SUFFIX_NO
};

#define SUFFIX(U, L)		(2 * (L) + (U))


#endif
