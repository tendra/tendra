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


#ifndef CONSTRUCT_INCLUDED
#define CONSTRUCT_INCLUDED


/*
    CONSTRUCTOR AND DESTRUCTOR FUNCTION DECLARATIONS

    The routines in this module are concerned with constructors, destructors
    and conversion functions.
*/

extern NAMESPACE ctor_begin PROTO_S ( ( void ) ) ;
extern EXP ctor_end PROTO_S ( ( NAMESPACE, EXP, int ) ) ;
extern void ctor_initialise PROTO_S ( ( NAMESPACE, IDENTIFIER, EXP ) ) ;
extern EXP ctor_none PROTO_S ( ( EXP, EXP * ) ) ;
extern EXP ctor_postlude PROTO_S ( ( EXP, EXP ) ) ;
extern EXP copy_ctor PROTO_S ( ( EXP, int ) ) ;
extern EXP except_postlude PROTO_S ( ( IDENTIFIER ) ) ;

extern TYPE check_constr PROTO_S ( ( TYPE, IDENTIFIER, NAMESPACE ) ) ;
extern TYPE check_destr PROTO_S ( ( TYPE, IDENTIFIER, NAMESPACE ) ) ;
extern TYPE check_conv PROTO_S ( ( TYPE, IDENTIFIER ) ) ;
extern TYPE inferred_return PROTO_S ( ( TYPE, IDENTIFIER ) ) ;

extern IDENTIFIER find_operator PROTO_S ( ( CLASS_TYPE, int ) ) ;
extern IDENTIFIER make_pseudo_destr PROTO_S ( ( IDENTIFIER, BASE_TYPE, IDENTIFIER, BASE_TYPE ) ) ;
extern CLASS_INFO implicit_decl PROTO_S ( ( CLASS_TYPE, CLASS_INFO, DECL_SPEC ) ) ;
extern void implicit_defn PROTO_S ( ( IDENTIFIER, int ) ) ;

extern EXP init_default PROTO_S ( ( TYPE, EXP *, int, int, ERROR * ) ) ;
extern EXP convert_constr PROTO_S ( ( TYPE, LIST ( EXP ), ERROR *, unsigned ) ) ;
extern EXP convert_conv_aux PROTO_S ( ( TYPE, EXP, ERROR *, unsigned ) ) ;
extern EXP convert_conv PROTO_S ( ( TYPE, EXP, ERROR *, unsigned ) ) ;
extern EXP convert_gen PROTO_S ( ( unsigned, EXP, ERROR * ) ) ;
extern EXP apply_constr PROTO_S ( ( IDENTIFIER, LIST ( EXP ) ) ) ;
extern EXP add_constr_args PROTO_S ( ( EXP, CLASS_TYPE, int ) ) ;
extern unsigned extra_constr_args PROTO_S ( ( IDENTIFIER, CLASS_TYPE ) ) ;
extern EXP apply_trivial_func PROTO_S ( ( IDENTIFIER, LIST ( EXP ) ) ) ;
extern EXP trivial_destr PROTO_S ( ( EXP ) ) ;
extern int have_constr_expl ;
extern int have_conv_expl ;


/*
    IMPLICIT CONSTRUCTOR IDENTIFIERS

    These values are used to represent the four member functions which
    may be implicitly declared for a class - the default constructor, the
    copy constructor, the default destructor and the copy assignment
    operator.  A dummy value for explicit constructors is provided.
*/

#define DEFAULT_USR			0
#define DEFAULT_CONSTR			1
#define DEFAULT_COPY			2
#define DEFAULT_DESTR			3
#define DEFAULT_ASSIGN			4
#define DEFAULT_DELETE			5
#define DEFAULT_PRELUDE			6


/*
    EXTRA CONSTRUCT ARGUMENT VALUES

    These values represent the extra argument which are passed to
    constructors and destructors.
*/

#define EXTRA_NONE			0
#define EXTRA_CONSTR			1

#define EXTRA_DELETE			1
#define EXTRA_DESTR			2


#endif
