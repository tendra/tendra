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


#ifndef LITERAL_INCLUDED
#define LITERAL_INCLUDED


/*
    LITERAL CONSTRUCTION DECLARATIONS

    The routines in this module are concerned with the construction of
    integer, floating-point, character, string and boolean literal
    expressions.
*/

extern EXP make_literal_exp PROTO_S ( ( string, int *, int ) ) ;
extern EXP make_bool_exp PROTO_S ( ( unsigned, unsigned ) ) ;
extern EXP make_string_exp PROTO_S ( ( STRING ) ) ;

extern int is_zero_float PROTO_S ( ( FLOAT ) ) ;
extern int eq_float_lit PROTO_S ( ( FLOAT, FLOAT ) ) ;
extern int eq_string_lit PROTO_S ( ( STRING, STRING ) ) ;
extern unsigned test_bool_exp PROTO_S ( ( EXP ) ) ;
extern unsigned long eval_line_digits PROTO_S ( ( string, unsigned * ) ) ;
extern unsigned long get_multi_char PROTO_S ( ( string, int * ) ) ;
extern unsigned long get_string_char PROTO_S ( ( STRING, int * ) ) ;
extern void add_multi_char PROTO_S ( ( string, unsigned long, int ) ) ;
extern unsigned long eval_unicode PROTO_S ( ( int, unsigned, int *, string *, ERROR * ) ) ;
extern TYPE find_literal_type PROTO_S ( ( NAT, int, int, string, int * ) ) ;
extern TYPE find_char_type PROTO_S ( ( NAT ) ) ;
extern NAT round_float_lit PROTO_S ( ( FLOAT, RMODE ) ) ;
extern STRING new_string_lit PROTO_S ( ( string, string, int ) ) ;
extern STRING concat_string_lit PROTO_S ( ( STRING, STRING ) ) ;
extern STRING share_string_lit PROTO_S ( ( STRING ) ) ;
extern NAT eval_char_lit PROTO_S ( ( STRING ) ) ;
extern int get_char_value PROTO_S ( ( EXP ) ) ;
extern void begin_literal PROTO_S ( ( int, int ) ) ;
extern void add_range_literal PROTO_S ( ( EXP, int ) ) ;
extern void add_type_literal PROTO_S ( ( TYPE ) ) ;
extern void add_token_literal PROTO_S ( ( IDENTIFIER, unsigned ) ) ;
extern void set_string_qual PROTO_S ( ( CV_SPEC ) ) ;
extern void set_escape PROTO_S ( ( EXP, EXP ) ) ;
extern void set_char_lit PROTO_S ( ( TYPE ) ) ;
extern void init_literal PROTO_S ( ( void ) ) ;

extern unsigned char digit_values [] ;
extern unsigned char escape_sequences [] ;
extern RMODE crt_round_mode ;
extern CV_SPEC cv_string ;


/*
    STRING TYPES

    The values STRING_* form a bitfield which is used to identify the
    various types of string literals.  The values CHAR_* are used to
    identify the various types of character in multibyte strings.
*/

#define STRING_NONE		( ( unsigned ) 0x00 )
#define STRING_CHAR		( ( unsigned ) 0x01 )
#define STRING_WIDE		( ( unsigned ) 0x02 )
#define STRING_MULTI		( ( unsigned ) 0x04 )
#define STRING_FAT		( ( unsigned ) 0x08 )
#define CHAR_SIMPLE		0
#define CHAR_ASCII		1
#define CHAR_OCTAL		2
#define CHAR_HEX		3
#define CHAR_UNI4		4
#define CHAR_UNI8		5
#define CHAR_NONE		6
#define MULTI_WIDTH		5


/*
    BOOLEAN VALUES

    These values give the boolean values, true and false, plus a third
    value indicating an indeterminate boolean.  A fourth error value is
    also given.
*/

#define BOOL_FALSE		( ( unsigned ) 0 )
#define BOOL_TRUE		( ( unsigned ) 1 )
#define BOOL_UNKNOWN		( ( unsigned ) 2 )
#define BOOL_INVALID		( ( unsigned ) 3 )
#define BOOL_VALUE( C )		( ( C ) ? BOOL_TRUE : BOOL_FALSE )
#define BOOL_NEGATE( C )	( ( C ) ? BOOL_FALSE : BOOL_TRUE )


/*
    LITERAL BASE AND SUFFIX VALUES

    These values are used to identify the various bases and suffixes for
    integer literals.
*/

#define BASE_DECIMAL		0
#define BASE_OCTAL		1
#define BASE_HEXADECIMAL	2
#define BASE_NO			3

#define SUFFIX_NONE		0
#define SUFFIX_U		1
#define SUFFIX_L		2
#define SUFFIX_UL		3
#define SUFFIX_LL		4
#define SUFFIX_ULL		5
#define SUFFIX_NO		6

#define SUFFIX( U, L )		( 2 * ( L ) + ( U ) )


#endif
