/*
    		 Crown Copyright (c) 1997, 1998
    
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


#ifndef PREDICT_INCLUDED
#define PREDICT_INCLUDED


/*
    PARSER LOOK-AHEAD DECLARATIONS

    The routines in this module are used to implement look-ahead functions
    within the parser in order to get round some of the more complex parsing
    problems (such as resolving between declarations and expressions).
*/

extern int predict_array PROTO_S ( ( void ) ) ;
extern int predict_class PROTO_S ( ( int ) ) ;
extern int predict_decl PROTO_S ( ( void ) ) ;
extern int predict_destr PROTO_S ( ( NAMESPACE ) ) ;
extern int predict_dspec PROTO_S ( ( int ) ) ;
extern int predict_func_defn PROTO_S ( ( void ) ) ;
extern int predict_init PROTO_S ( ( void ) ) ;
extern int predict_obj_defn PROTO_S ( ( void ) ) ;
extern int predict_operator PROTO_S ( ( void ) ) ;
extern int predict_param PROTO_S ( ( void ) ) ;
extern int predict_ptr PROTO_S ( ( int ) ) ;
extern int predict_template PROTO_S ( ( void ) ) ;
extern int predict_tspec PROTO_S ( ( int ) ) ;
extern int predict_typeid PROTO_S ( ( int ) ) ;
extern int predict_typename PROTO_S ( ( void ) ) ;


/*
    PARSER STATE VARIABLES

    These variables are used by the parser to store information about the
    current parser state.
*/

extern int have_type_specifier ;
extern int have_type_declaration ;
extern int have_func_declarator ;
extern int in_function_defn ;
extern int in_class_defn ;
extern int in_declaration ;
extern int in_default_arg ;
extern int in_weak_param ;
extern int in_ptr_mem_selector ;
extern int in_token_decl ;
extern int in_template_decl ;
extern int really_in_function_defn ;
extern int really_in_class_defn ;
extern int is_function_next ;
extern int is_constructor_next ;

extern int no_side_effects ;
extern int no_type_defns ;
extern int have_destructor ;
extern unsigned long no_declarations ;
extern unsigned long no_token_defns ;


/*
    FEATURE USE FLAGS

    These flags are set to indicate that certain features, which require
    the program to perform extra checks, have been used.
*/

extern int used_extern_volatile ;
extern int used_register ;


/*
    TYPE DECLARATION VALUES

    These macros give the various values assigned to have_type_declaration.
    If no types have been declared in a sequence of type specifiers it is
    TYPE_DECL_NONE, if an anonymous class is defined it is TYPE_DECL_ANON,
    if an elaborated type specifier is declared it is TYPE_DECL_ELABORATE,
    otherwise it is TYPE_DECL_NORMAL.
*/

#define TYPE_DECL_NONE			0
#define TYPE_DECL_NORMAL		1
#define TYPE_DECL_ANON			2
#define TYPE_DECL_ELABORATE		3
#define TYPE_DECL_OVER_ELAB		4


#endif
