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


#ifndef CHECK_INCLUDED
#define CHECK_INCLUDED


/*
    EXPRESSION CHECKING DECLARATIONS

    The routines in this module are concerned with checking various
    properties of expressions.
*/

extern int eq_token PROTO_S ( ( TOKEN, TOKEN ) ) ;
extern int eq_token_args PROTO_S ( ( IDENTIFIER, IDENTIFIER, LIST ( TOKEN ), LIST ( TOKEN ) ) ) ;
extern DECL_SPEC find_exp_linkage PROTO_S ( ( EXP, EXP *, int ) ) ;
extern int eq_offset PROTO_S ( ( OFFSET, OFFSET, int ) ) ;
extern int eq_exp_exact PROTO_S ( ( EXP, EXP ) ) ;
extern int eq_exp PROTO_S ( ( EXP, EXP, int ) ) ;
extern int is_const_exp PROTO_S ( ( EXP, int ) ) ;
extern int is_const_offset PROTO_S ( ( OFFSET, int, int ) ) ;
extern int is_zero_offset PROTO_S ( ( OFFSET ) ) ;
extern int overflow_exp PROTO_S ( ( EXP ) ) ;
extern int know_type PROTO_S ( ( EXP ) ) ;


#endif
