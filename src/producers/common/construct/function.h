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


#ifndef FUNCTION_INCLUDED
#define FUNCTION_INCLUDED


/*
    FUNCTION DECLARATIONS

    The routines in this module are concerned with the construction and
    application of functions.
*/

extern void begin_function PROTO_S ( ( IDENTIFIER ) ) ;
extern EXP end_function PROTO_S ( ( IDENTIFIER, EXP ) ) ;
extern void begin_param PROTO_S ( ( IDENTIFIER ) ) ;
extern void end_param PROTO_S ( ( void ) ) ;
extern void adjust_param PROTO_S ( ( TYPE ) ) ;
extern int function_params PROTO_S ( ( TYPE ) ) ;
extern TYPE make_param_type PROTO_S ( ( TYPE, int ) ) ;
extern TYPE make_func_type PROTO_S ( ( TYPE, int, CV_SPEC, LIST ( TYPE ) ) ) ;
extern CV_SPEC func_linkage PROTO_S ( ( CV_SPEC ) ) ;
extern void member_func_type PROTO_S ( ( CLASS_TYPE, unsigned, TYPE ) ) ;
extern void check_weak_func PROTO_S ( ( TYPE, int ) ) ;
extern void decl_func_type PROTO_S ( ( IDENTIFIER, TYPE, int ) ) ;
extern TYPE find_func_type PROTO_S ( ( TYPE ) ) ;
extern TYPE redecl_func_type PROTO_S ( ( IDENTIFIER, TYPE, TYPE, int, int ) ) ;
extern EXP apply_func_id PROTO_S ( ( IDENTIFIER, QUALIFIER, GRAPH, LIST ( EXP ) ) ) ;
extern LIST ( EXP ) convert_args PROTO_S ( ( LIST ( EXP ) ) ) ;
extern EXP make_func_exp PROTO_S ( ( EXP, LIST ( EXP ), int ) ) ;
extern EXP check_inline PROTO_S ( ( IDENTIFIER, LIST ( EXP ), TYPE ) ) ;
extern TYPE check_main PROTO_S ( ( TYPE, HASHID ) ) ;
extern void recheck_main PROTO_S ( ( IDENTIFIER ) ) ;
extern int pass_complex_type PROTO_S ( ( TYPE ) ) ;
extern unsigned min_no_args PROTO_S ( ( TYPE ) ) ;
extern void func_type_defn PROTO_S ( ( int ) ) ;
extern ERROR check_param_type PROTO_S ( ( IDENTIFIER, TYPE ) ) ;
extern TYPE check_ret_type PROTO_S ( ( TYPE, ERROR *, int ) ) ;
extern int check_func_dargs PROTO_S ( ( TYPE, int, int ) ) ;
extern void object_type PROTO_S ( ( TYPE, unsigned ) ) ;


/*
    FUNCTION VARIABLES

    These variables are used to store information about the current
    function definition.
*/

extern IDENTIFIER crt_func_id ;
extern TYPE crt_func_return ;
extern int crt_func_complex ;
extern IDENTIFIER main_function ;


/*
    FUNCTION TYPES

    The various kinds of functions are given by combinations of the
    following values, which are stored in the ellipsis field of the
    corresponding function type.  In C++ the only possibilities are
    FUNC_NONE and FUNC_ELLIPSIS indicating whether or not the function
    is declared with ellipsis; the fact that these have the values 0 and
    1 is used.  In C non-prototype functions introduce other kinds of
    function:

	FUNC_NO_PARAMS		no type information,
	FUNC_WEAK_PARAMS	weak prototype or non-prototype definition,
	FUNC_WEAK_ARGS		implicit weak prototype.

    During type construction the following values are used:

	FUNC_NO_PARAMS		no type information,
	FUNC_PARAMS		non-prototype definition,
	FUNC_WEAK		weak prototype.
*/

#define FUNC_NONE		0
#define FUNC_ELLIPSIS		1
#define FUNC_WEAK		2
#define FUNC_PARAMS		4
#define FUNC_NO_PARAMS		8
#define FUNC_WEAK_PARAMS	( FUNC_WEAK | FUNC_PARAMS )
#define FUNC_WEAK_ARGS		( FUNC_WEAK )
#define FUNC_VAR_PARAMS		( FUNC_ELLIPSIS | FUNC_NO_PARAMS )
#define FUNC_NON_PROTO		( FUNC_WEAK | FUNC_PARAMS | FUNC_NO_PARAMS )


#endif
