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


#ifndef OPERATOR_INCLUDED
#define OPERATOR_INCLUDED


/*
    OPERATOR OVERLOADING DECLARATIONS

    The routines in this module are concerned with operator overloading.
*/

extern EXP apply_unary PROTO_S ( ( int, EXP, TYPE, TYPE, int ) ) ;
extern EXP apply_binary PROTO_S ( ( int, EXP, EXP, TYPE, TYPE, int ) ) ;
extern EXP apply_nary PROTO_S ( ( int, LIST ( EXP ), TYPE, TYPE, int ) ) ;
extern EXP unary_overload PROTO_S ( ( int, EXP ) ) ;
extern EXP binary_overload PROTO_S ( ( int, EXP, EXP ) ) ;
extern EXP function_overload PROTO_S ( ( EXP, LIST ( EXP ) ) ) ;
extern TYPE check_operator PROTO_S ( ( TYPE, IDENTIFIER, int, int * ) ) ;
extern EXP apply_builtin PROTO_S ( ( IDENTIFIER, LIST ( EXP ) ) ) ;
extern int ntest_token PROTO_S ( ( NTEST, int ) ) ;
extern int op_token PROTO_S ( ( EXP, int ) ) ;
extern int overload_depth ;
extern int overload_warn ;


#endif
