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


#ifndef VARIABLE_INCLUDED
#define VARIABLE_INCLUDED


/*
    VARIABLE ANALYSIS DECLARATIONS

    The routines in this module are concerned with the variable analysis
    checks.
*/

extern unsigned long check_global PROTO_S ( ( int ) ) ;
extern unsigned long check_namespace PROTO_S ( ( NAMESPACE, EXP, int, int ) ) ;
extern unsigned long check_identifier PROTO_S ( ( IDENTIFIER, NAMESPACE, EXP, int, int ) ) ;
extern void check_flow PROTO_S ( ( IDENTIFIER, EXP, int ) ) ;
extern void preserve_id PROTO_S ( ( IDENTIFIER, int ) ) ;
extern EXP make_unused_exp PROTO_S ( ( EXP ) ) ;
extern EXP make_set_exp PROTO_S ( ( EXP ) ) ;
extern int suppress_variable ;
extern int anon_c_linkage ;
extern int preserve_all ;


/*
    VARIABLE CHECK STATES

    These values are used to indicate the checking level in check_namespace,
    check_identifier etc.
*/

#define ANON_NONE		0
#define ANON_INLINE		1
#define ANON_NAMESPACE		2
#define ANON_CLASS		3
#define ANON_GLOBAL		4


#endif
