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


#ifndef CONSTANT_INCLUDED
#define CONSTANT_INCLUDED


/*
    CONSTANT EVALUATION MACROS

    All the calculation routines are based on lists of unsigned int's
    holding values in the range [0,0xffff].  The type unsigned long is
    guaranteed to contain at least the range [0,0xffffffff].  All
    calculations are performed in this double precision type to allow for
    overflows.  The macros LO_HALF, HI_HALF, EXTEND_VALUE and COMBINE_VALUES
    are used for converting to and from the extended type.
*/

#define NAT_DIGITS		16
#define NAT_MASK		( ( unsigned ) 0xffff )

#define LO_HALF( A )		( ( unsigned ) ( ( A ) & NAT_MASK ) )
#define HI_HALF( A )		( LO_HALF ( ( A ) >> NAT_DIGITS ) )

#define EXTEND_VALUE( A )	( ( unsigned long ) ( A ) )
#define COMBINE_VALUES( A, B )	( EXTEND_VALUE ( A ) +\
				  ( EXTEND_VALUE ( B ) << NAT_DIGITS ) )
#define EXTENDED_MAX		COMBINE_VALUES ( NAT_MASK, NAT_MASK )


/*
    CONSTANT EVALUATION DECLARATIONS

    The routines in this module are concerned with constructing and
    performing calculations with integer constant expressions.
*/

extern void init_constant PROTO_S ( ( void ) ) ;
extern void init_float PROTO_S ( ( FLOAT_TYPE ) ) ;
extern FLOAT get_float PROTO_S ( ( TYPE, int ) ) ;

extern NAT make_nat_literal PROTO_S ( ( NAT, unsigned, unsigned ) ) ;
extern NAT make_large_nat PROTO_S ( ( LIST ( unsigned ) ) ) ;
extern NAT make_nat_value PROTO_S ( ( unsigned long ) ) ;
extern NAT make_small_nat PROTO_S ( ( int ) ) ;
extern unsigned long get_nat_value PROTO_S ( ( NAT ) ) ;
extern NAT negate_nat PROTO_S ( ( NAT ) ) ;
extern NAT binary_nat_op PROTO_S ( ( unsigned, NAT, NAT ) ) ;
extern int compare_nat PROTO_S ( ( NAT, NAT ) ) ;
extern int eq_nat PROTO_S ( ( NAT, NAT ) ) ;

extern int check_nat_range PROTO_S ( ( TYPE, NAT ) ) ;
extern int check_type_size PROTO_S ( ( TYPE, NAT ) ) ;
extern NAT max_type_value PROTO_S ( ( TYPE, int ) ) ;
extern void check_bounds PROTO_S ( ( int, TYPE, EXP ) ) ;
extern unsigned eval_const_cond PROTO_S ( ( EXP ) ) ;
extern unsigned no_bits PROTO_S ( ( unsigned ) ) ;
extern int divides_nat PROTO_S ( ( EXP, EXP ) ) ;
extern int is_zero_nat PROTO_S ( ( NAT ) ) ;
extern int is_negative_nat PROTO_S ( ( NAT ) ) ;
extern int is_error_nat PROTO_S ( ( NAT ) ) ;
extern int is_calc_nat PROTO_S ( ( NAT ) ) ;
extern int is_zero_exp PROTO_S ( ( EXP ) ) ;
extern int is_literal PROTO_S ( ( EXP ) ) ;


/*
    CONSTANT EVALUATION ROUTINES

    These routines are concerned with the evaluation of integer constant
    expressions.  They are so designed that the int_lit expressions are
    precisely the constant-expressions from the grammar.
*/

extern EXP make_test_nat PROTO_S ( ( EXP ) ) ;
extern EXP make_unary_nat PROTO_S ( ( unsigned, EXP ) ) ;
extern EXP make_binary_nat PROTO_S ( ( unsigned, EXP, EXP ) ) ;
extern EXP make_compare_nat PROTO_S ( ( NTEST, EXP, EXP ) ) ;
extern EXP make_cond_nat PROTO_S ( ( EXP, EXP, EXP ) ) ;
extern EXP make_cast_nat PROTO_S ( ( TYPE, EXP, ERROR *, unsigned ) ) ;
extern EXP make_int_exp PROTO_S ( ( TYPE, unsigned, NAT ) ) ;
extern NAT make_nat_exp PROTO_S ( ( EXP, ERROR * ) ) ;
extern EXP calc_nat_value PROTO_S ( ( NAT, TYPE ) ) ;

#define SMALL_NAT_SIZE		257
#define SMALL_NAT_ALLOC		17
#define SMALL_FLT_SIZE		2

extern NAT small_neg_nat [ SMALL_NAT_SIZE ] ;
extern NAT small_nat [ SMALL_NAT_SIZE ] ;
extern string small_number [ SMALL_FLT_SIZE ] ;


#endif
