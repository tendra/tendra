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

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA errors (VERSION 1.0)
    BY calculus (VERSION 1.2)
*/

#ifndef ERRORS_H_TOK_INCLUDED
#define ERRORS_H_TOK_INCLUDED

#ifndef errors_NAME
#define errors_NAME			"errors"
#define errors_VERSION			"1.0"
#define errors_SPECIFICATION		1
#define errors_IMPLEMENTATION		0
#endif


/* Prototype macros */

#ifndef PROTO_S
#ifdef __STDC__
#define PROTO_S( types )		types
#define PROTO_N( names )
#define PROTO_T( parms )		( parms )
#define PROTO_Z()			( void )
#define X				,
#else
#define PROTO_S( types )		()
#define PROTO_N( names )		names
#define PROTO_T( parms )		parms ;
#define PROTO_Z()			()
#define X				;
#endif
#endif

#ifndef CONST_S
#define CONST_S
#endif


/* Primitive types */

typedef char * string ;


/* Basic types */

#ifndef errors_DESTR_DEFINED
#define errors_DESTR_DEFINED
typedef void ( *DESTROYER ) () ;
#endif

#pragma token PROC ( TYPE ) TYPE PTR #
#pragma token PROC ( TYPE ) TYPE LIST #
#pragma token PROC ( TYPE ) TYPE STACK #
#pragma token PROC ( TYPE ) TYPE SIZE #

#pragma interface PTR LIST STACK SIZE


/* Enumeration type definitions */



/* Union type definitions */

#pragma token TYPE NAME #
#pragma interface NAME
#pragma token TYPE MESSAGE #
#pragma interface MESSAGE
#pragma token TYPE MAP #
#pragma interface MAP
#pragma token TYPE PARAM #
#pragma interface PARAM
#pragma token TYPE ENTRY #
#pragma interface ENTRY


/* Structure declarations */



/* Identity type definitions */

typedef NAME KEY ;
typedef NAME PROPERTY ;
typedef NAME TYPE ;
typedef NAME USAGE ;


/* Structure definitions */

#ifndef errors_STRUCT_DEFINED
#define errors_STRUCT_DEFINED

#endif /* errors_STRUCT_DEFINED */


/* Function declarations */

extern void destroy_errors () ;
extern void dummy_destroy_errors () ;
#ifdef errors_IO_ROUTINES
extern unsigned crt_errors_alias ;
extern void clear_errors_alias PROTO_S ( ( void ) ) ;
#endif


/* Pointer token specifications */

#pragma token PROC {\
	TYPE t, EXP : PTR ( t ) : e1, EXP : SIZE ( t ) : e2 |\
	EXP e1, EXP e2\
    } EXP : PTR ( t ) : STEP_ptr #

#pragma token PROC (\
	TYPE t\
    ) EXP const : PTR ( t ) : NULL_ptr #

#pragma token PROC {\
	TYPE t, EXP : PTR ( t ) : e |\
	EXP e\
    } EXP : int : IS_NULL_ptr #

#pragma token PROC {\
	TYPE t, EXP : PTR ( t ) : e1, EXP : PTR ( t ) : e2 |\
	EXP e1, EXP e2\
    } EXP : int : EQ_ptr #

#pragma token PROC {\
	TYPE t, EXP : SIZE ( t ) : e |\
	EXP e\
    } EXP : PTR ( t ) : MAKE_ptr #

#pragma token PROC {\
	TYPE t, EXP : PTR ( t ) : e1, EXP : SIZE ( t ) : e2 |\
	EXP e1, EXP e2\
    } EXP : void : DESTROY_ptr #

#pragma token PROC (\
	TYPE t\
    ) EXP : PTR ( t ) : UNIQ_ptr #

#pragma token PROC {\
	TYPE t, EXP : PTR ( t ) : e |\
	EXP e\
    } EXP : void : DESTROY_UNIQ_ptr #

#pragma interface STEP_ptr NULL_ptr IS_NULL_ptr EQ_ptr
#pragma interface MAKE_ptr DESTROY_ptr

#ifdef errors_IO_ROUTINES
#pragma token PROC {\
	TYPE t, EXP : PTR ( t ) : e |\
	EXP e\
    } EXP : void * : VOIDSTAR_ptr #
#pragma interface VOIDSTAR_ptr
#endif

#pragma token PROC (\
	TYPE t\
    ) EXP const : SIZE ( PTR ( t ) ) : SIZE_ptr #

#pragma token PROC {\
	TYPE t, EXP : PTR ( PTR ( t ) ) : e1,\
	EXP : PTR ( t ) : e2 |\
	EXP e1, EXP e2\
    } EXP : void : COPY_ptr #

#pragma token PROC {\
	TYPE t, EXP : PTR ( PTR ( t ) ) : e |\
	EXP e\
    } EXP : PTR ( t ) : DEREF_ptr #

#pragma token PROC {\
	TYPE t, EXP : PTR ( t ) : e2,\
	EXP : LIST ( PTR ( t ) ) : e3,\
	EXP lvalue : LIST ( PTR ( t ) ) : e4 |\
	EXP e2, EXP e3, EXP e4\
    } STATEMENT CONS_ptr #

#pragma token PROC {\
	TYPE t, EXP lvalue : PTR ( t ) : e2,\
	EXP lvalue : LIST ( PTR ( t ) ) : e3,\
	EXP : LIST ( PTR ( t ) ) : e4 |\
	EXP e2, EXP e3, EXP e4\
    } STATEMENT UN_CONS_ptr #

#pragma token PROC {\
	TYPE t, EXP : DESTROYER : e1,\
	EXP lvalue : PTR ( t ) : e2,\
	EXP lvalue : LIST ( PTR ( t ) ) : e3,\
	EXP : LIST ( PTR ( t ) ) : e4 |\
	EXP e1, EXP e2, EXP e3, EXP e4\
    } STATEMENT DESTROY_CONS_ptr #

#pragma token PROC {\
	TYPE t, EXP : PTR ( t ) : e2,\
	EXP lvalue : STACK ( PTR ( t ) ) : e3 |\
	EXP e2, EXP e3\
    } STATEMENT PUSH_ptr #

#pragma token PROC {\
	TYPE t, EXP lvalue : PTR ( t ) : e2,\
	EXP lvalue : STACK ( PTR ( t ) ) : e3 |\
	EXP e2, EXP e3\
    } STATEMENT POP_ptr #

#pragma interface SIZE_ptr COPY_ptr DEREF_ptr
#pragma interface CONS_ptr UN_CONS_ptr DESTROY_CONS_ptr
#pragma interface PUSH_ptr POP_ptr


/* List token specifications */

#pragma token PROC {\
	TYPE t, EXP : LIST ( t ) : e |\
	EXP e\
    } EXP : PTR ( t ) : HEAD_list #

#pragma token PROC {\
	TYPE t, EXP : LIST ( t ) : e |\
	EXP e\
    } EXP : PTR ( LIST ( t ) ) : PTR_TAIL_list #

#pragma token PROC {\
	TYPE t, EXP : LIST ( t ) : e |\
	EXP e\
    } EXP : LIST ( t ) : TAIL_list #

#pragma token PROC {\
	TYPE t, EXP : LIST ( t ) : e1 |\
	EXP e1\
    } EXP : unsigned : LENGTH_list #

#pragma token PROC {\
	TYPE t, EXP : LIST ( t ) : e1 |\
	EXP e1\
    } EXP : LIST ( t ) : END_list #

#pragma token PROC {\
	TYPE t, EXP : LIST ( t ) : e1 |\
	EXP e1\
    } EXP : LIST ( t ) : REVERSE_list #

#pragma token PROC {\
	TYPE t, EXP : LIST ( t ) : e1, EXP : LIST ( t ) : e2 |\
	EXP e1, EXP e2\
    } EXP : LIST ( t ) : APPEND_list #

#pragma token PROC (\
	TYPE t\
    ) EXP const : LIST ( t ) : NULL_list #

#pragma token PROC {\
	TYPE t, EXP : LIST ( t ) : e |\
	EXP e\
    } EXP : int : IS_NULL_list #

#pragma token PROC {\
	TYPE t, EXP : LIST ( t ) : e1, EXP : LIST ( t ) : e2 |\
	EXP e1, EXP e2\
    } EXP : int : EQ_list #

#pragma token PROC (\
	TYPE t\
    ) EXP : LIST ( t ) : UNIQ_list #

#pragma token PROC {\
	TYPE t, EXP : LIST ( t ) : e |\
	EXP e\
    } EXP : void : DESTROY_UNIQ_list #

#pragma token PROC {\
	TYPE t, EXP : LIST ( t ) : e1, EXP : SIZE ( t ) : e2 |\
	EXP e1, EXP e2\
    } STATEMENT DESTROY_list #

#pragma interface HEAD_list PTR_TAIL_list TAIL_list
#pragma interface LENGTH_list END_list REVERSE_list APPEND_list
#pragma interface NULL_list IS_NULL_list EQ_list
#pragma interface UNIQ_list DESTROY_UNIQ_list DESTROY_list

#ifdef errors_IO_ROUTINES
#pragma token PROC {\
	TYPE t, EXP : LIST ( t ) : e |\
	EXP e\
    } EXP : void * : VOIDSTAR_list #
#pragma interface VOIDSTAR_list
#endif

#pragma token PROC (\
	TYPE t\
    ) EXP const : SIZE ( LIST ( t ) ) : SIZE_list #

#pragma token PROC {\
	TYPE t, EXP : PTR ( LIST ( t ) ) : e1,\
	EXP : LIST ( t ) : e2 |\
	EXP e1, EXP e2\
    } EXP : void : COPY_list #

#pragma token PROC {\
	TYPE t, EXP : PTR ( LIST ( t ) ) : e |\
	EXP e\
    } EXP : LIST ( t ) : DEREF_list #

#pragma token PROC {\
	TYPE t, EXP : LIST ( t ) : e2,\
	EXP : LIST ( LIST ( t ) ) : e3,\
	EXP lvalue : LIST ( LIST ( t ) ) : e4 |\
	EXP e2, EXP e3, EXP e4\
    } STATEMENT CONS_list #

#pragma token PROC {\
	TYPE t, EXP lvalue : LIST ( t ) : e2,\
	EXP lvalue : LIST ( LIST ( t ) ) : e3,\
	EXP : LIST ( LIST ( t ) ) : e4 |\
	EXP e2, EXP e3, EXP e4\
    } STATEMENT UN_CONS_list #

#pragma token PROC {\
	TYPE t, EXP : DESTROYER : e1,\
	EXP lvalue : LIST ( t ) : e2,\
	EXP lvalue : LIST ( LIST ( t ) ) : e3,\
	EXP : LIST ( LIST ( t ) ) : e4 |\
	EXP e1, EXP e2, EXP e3, EXP e4\
    } STATEMENT DESTROY_CONS_list #

#pragma token PROC {\
	TYPE t, EXP : LIST ( t ) : e2,\
	EXP lvalue : STACK ( LIST ( t ) ) : e3 |\
	EXP e2, EXP e3\
    } STATEMENT PUSH_list #

#pragma token PROC {\
	TYPE t, EXP lvalue : LIST ( t ) : e2,\
	EXP lvalue : STACK ( LIST ( t ) ) : e3 |\
	EXP e2, EXP e3\
    } STATEMENT POP_list #

#pragma interface SIZE_list COPY_list DEREF_list
#pragma interface CONS_list UN_CONS_list DESTROY_CONS_list
#pragma interface PUSH_list POP_list


/* Stack token specifications */

#pragma token PROC (\
	TYPE t\
    ) EXP const : STACK ( t ) : NULL_stack #

#pragma token PROC {\
	TYPE t, EXP : STACK ( t ) : e |\
	EXP e\
    } EXP : int : IS_NULL_stack #

#pragma token PROC {\
	TYPE t, EXP : STACK ( t ) : e1 |\
	EXP e1\
    } EXP : LIST ( t ) : LIST_stack #

#pragma token PROC {\
	TYPE t, EXP : LIST ( t ) : e1 |\
	EXP e1\
    } EXP : STACK ( t ) : STACK_list #

#pragma interface NULL_stack IS_NULL_stack LIST_stack STACK_list

#pragma token PROC (\
	TYPE t\
    ) EXP const : SIZE ( STACK ( t ) ) : SIZE_stack #

#pragma token PROC {\
	TYPE t, EXP : PTR ( STACK ( t ) ) : e1,\
	EXP : STACK ( t ) : e2 |\
	EXP e1, EXP e2\
    } EXP : void : COPY_stack #

#pragma token PROC {\
	TYPE t, EXP : PTR ( STACK ( t ) ) : e |\
	EXP e\
    } EXP : STACK ( t ) : DEREF_stack #

#pragma token PROC {\
	TYPE t, EXP : STACK ( t ) : e2,\
	EXP : LIST ( STACK ( t ) ) : e3,\
	EXP lvalue : LIST ( STACK ( t ) ) : e4 |\
	EXP e2, EXP e3, EXP e4\
    } STATEMENT CONS_stack #

#pragma token PROC {\
	TYPE t, EXP lvalue : STACK ( t ) : e2,\
	EXP lvalue : LIST ( STACK ( t ) ) : e3,\
	EXP : LIST ( STACK ( t ) ) : e4 |\
	EXP e2, EXP e3, EXP e4\
    } STATEMENT UN_CONS_stack #

#pragma token PROC {\
	TYPE t, EXP : DESTROYER : e1,\
	EXP lvalue : STACK ( t ) : e2,\
	EXP lvalue : LIST ( STACK ( t ) ) : e3,\
	EXP : LIST ( STACK ( t ) ) : e4 |\
	EXP e1, EXP e2, EXP e3, EXP e4\
    } STATEMENT DESTROY_CONS_stack #

#pragma token PROC {\
	TYPE t, EXP : STACK ( t ) : e2,\
	EXP lvalue : STACK ( STACK ( t ) ) : e3 |\
	EXP e2, EXP e3\
    } STATEMENT PUSH_stack #

#pragma token PROC {\
	TYPE t, EXP lvalue : STACK ( t ) : e2,\
	EXP lvalue : STACK ( STACK ( t ) ) : e3 |\
	EXP e2, EXP e3\
    } STATEMENT POP_stack #

#pragma interface SIZE_stack COPY_stack DEREF_stack
#pragma interface CONS_stack UN_CONS_stack DESTROY_CONS_stack
#pragma interface PUSH_stack POP_stack


/* Size token specifications */

#pragma token PROC {\
	TYPE t, VARIETY v,\
	EXP : SIZE ( t ) : e1, EXP : v : e2 |\
	EXP e1, EXP e2\
    } EXP : SIZE ( t ) : SCALE #

#pragma interface SCALE


/* Definitions for primitive int */

#pragma token EXP const : SIZE ( int ) : SIZE_int #

#pragma token PROC (\
	EXP : PTR ( int ) :,\
	EXP : int :\
    ) EXP : void : COPY_int #

#pragma token PROC (\
	EXP : PTR ( int ) :\
    ) EXP : int : DEREF_int #

#pragma token PROC (\
	EXP : int :,\
	EXP : LIST ( int ) :,\
	EXP lvalue : LIST ( int ) :\
    ) STATEMENT CONS_int #

#pragma token PROC (\
	EXP lvalue : int :,\
	EXP lvalue : LIST ( int ) :,\
	EXP : LIST ( int ) :\
    ) STATEMENT UN_CONS_int #

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : int :,\
	EXP lvalue : LIST ( int ) :,\
	EXP : LIST ( int ) :\
    ) STATEMENT DESTROY_CONS_int #

#pragma token PROC (\
	EXP : int :,\
	EXP lvalue : STACK ( int ) :\
    ) STATEMENT PUSH_int #

#pragma token PROC (\
	EXP lvalue : int :,\
	EXP lvalue : STACK ( int ) :\
    ) STATEMENT POP_int #

#pragma interface SIZE_int COPY_int DEREF_int
#pragma interface CONS_int UN_CONS_int DESTROY_CONS_int
#pragma interface PUSH_int POP_int


/* Definitions for primitive string */

#pragma token EXP const : SIZE ( string ) : SIZE_string #

#pragma token PROC (\
	EXP : PTR ( string ) :,\
	EXP : string :\
    ) EXP : void : COPY_string #

#pragma token PROC (\
	EXP : PTR ( string ) :\
    ) EXP : string : DEREF_string #

#pragma token PROC (\
	EXP : string :,\
	EXP : LIST ( string ) :,\
	EXP lvalue : LIST ( string ) :\
    ) STATEMENT CONS_string #

#pragma token PROC (\
	EXP lvalue : string :,\
	EXP lvalue : LIST ( string ) :,\
	EXP : LIST ( string ) :\
    ) STATEMENT UN_CONS_string #

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : string :,\
	EXP lvalue : LIST ( string ) :,\
	EXP : LIST ( string ) :\
    ) STATEMENT DESTROY_CONS_string #

#pragma token PROC (\
	EXP : string :,\
	EXP lvalue : STACK ( string ) :\
    ) STATEMENT PUSH_string #

#pragma token PROC (\
	EXP lvalue : string :,\
	EXP lvalue : STACK ( string ) :\
    ) STATEMENT POP_string #

#pragma interface SIZE_string COPY_string DEREF_string
#pragma interface CONS_string UN_CONS_string DESTROY_CONS_string
#pragma interface PUSH_string POP_string


/* Definitions for union NAME */

#define ORDER_name ( ( unsigned ) 1 )
#pragma token EXP const : NAME : NULL_name #
#pragma token PROC ( EXP : NAME : ) EXP : int : IS_NULL_name #
#pragma token PROC ( EXP : NAME :, EXP : NAME : ) EXP : int : EQ_name #
#pragma interface NULL_name IS_NULL_name EQ_name

#pragma token EXP const : SIZE ( NAME ) : SIZE_name #

#pragma token PROC (\
	EXP : PTR ( NAME ) :,\
	EXP : NAME :\
    ) EXP : void : COPY_name #

#pragma token PROC (\
	EXP : PTR ( NAME ) :\
    ) EXP : NAME : DEREF_name #

#pragma token PROC (\
	EXP : NAME :,\
	EXP : LIST ( NAME ) :,\
	EXP lvalue : LIST ( NAME ) :\
    ) STATEMENT CONS_name #

#pragma token PROC (\
	EXP lvalue : NAME :,\
	EXP lvalue : LIST ( NAME ) :,\
	EXP : LIST ( NAME ) :\
    ) STATEMENT UN_CONS_name #

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : NAME :,\
	EXP lvalue : LIST ( NAME ) :,\
	EXP : LIST ( NAME ) :\
    ) STATEMENT DESTROY_CONS_name #

#pragma token PROC (\
	EXP : NAME :,\
	EXP lvalue : STACK ( NAME ) :\
    ) STATEMENT PUSH_name #

#pragma token PROC (\
	EXP lvalue : NAME :,\
	EXP lvalue : STACK ( NAME ) :\
    ) STATEMENT POP_name #

#pragma interface SIZE_name COPY_name DEREF_name
#pragma interface CONS_name UN_CONS_name DESTROY_CONS_name
#pragma interface PUSH_name POP_name


/* Definitions for union MESSAGE */

#define ORDER_msg ( ( unsigned ) 2 )
#pragma token EXP const : MESSAGE : NULL_msg #
#pragma token PROC ( EXP : MESSAGE : ) EXP : int : IS_NULL_msg #
#pragma token PROC ( EXP : MESSAGE :, EXP : MESSAGE : ) EXP : int : EQ_msg #
#pragma interface NULL_msg IS_NULL_msg EQ_msg

#pragma token EXP const : SIZE ( MESSAGE ) : SIZE_msg #

#pragma token PROC (\
	EXP : PTR ( MESSAGE ) :,\
	EXP : MESSAGE :\
    ) EXP : void : COPY_msg #

#pragma token PROC (\
	EXP : PTR ( MESSAGE ) :\
    ) EXP : MESSAGE : DEREF_msg #

#pragma token PROC (\
	EXP : MESSAGE :,\
	EXP : LIST ( MESSAGE ) :,\
	EXP lvalue : LIST ( MESSAGE ) :\
    ) STATEMENT CONS_msg #

#pragma token PROC (\
	EXP lvalue : MESSAGE :,\
	EXP lvalue : LIST ( MESSAGE ) :,\
	EXP : LIST ( MESSAGE ) :\
    ) STATEMENT UN_CONS_msg #

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : MESSAGE :,\
	EXP lvalue : LIST ( MESSAGE ) :,\
	EXP : LIST ( MESSAGE ) :\
    ) STATEMENT DESTROY_CONS_msg #

#pragma token PROC (\
	EXP : MESSAGE :,\
	EXP lvalue : STACK ( MESSAGE ) :\
    ) STATEMENT PUSH_msg #

#pragma token PROC (\
	EXP lvalue : MESSAGE :,\
	EXP lvalue : STACK ( MESSAGE ) :\
    ) STATEMENT POP_msg #

#pragma interface SIZE_msg COPY_msg DEREF_msg
#pragma interface CONS_msg UN_CONS_msg DESTROY_CONS_msg
#pragma interface PUSH_msg POP_msg


/* Definitions for union MAP */

#define ORDER_map ( ( unsigned ) 1 )
#pragma token EXP const : MAP : NULL_map #
#pragma token PROC ( EXP : MAP : ) EXP : int : IS_NULL_map #
#pragma token PROC ( EXP : MAP :, EXP : MAP : ) EXP : int : EQ_map #
#pragma interface NULL_map IS_NULL_map EQ_map

#pragma token EXP const : SIZE ( MAP ) : SIZE_map #

#pragma token PROC (\
	EXP : PTR ( MAP ) :,\
	EXP : MAP :\
    ) EXP : void : COPY_map #

#pragma token PROC (\
	EXP : PTR ( MAP ) :\
    ) EXP : MAP : DEREF_map #

#pragma token PROC (\
	EXP : MAP :,\
	EXP : LIST ( MAP ) :,\
	EXP lvalue : LIST ( MAP ) :\
    ) STATEMENT CONS_map #

#pragma token PROC (\
	EXP lvalue : MAP :,\
	EXP lvalue : LIST ( MAP ) :,\
	EXP : LIST ( MAP ) :\
    ) STATEMENT UN_CONS_map #

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : MAP :,\
	EXP lvalue : LIST ( MAP ) :,\
	EXP : LIST ( MAP ) :\
    ) STATEMENT DESTROY_CONS_map #

#pragma token PROC (\
	EXP : MAP :,\
	EXP lvalue : STACK ( MAP ) :\
    ) STATEMENT PUSH_map #

#pragma token PROC (\
	EXP lvalue : MAP :,\
	EXP lvalue : STACK ( MAP ) :\
    ) STATEMENT POP_map #

#pragma interface SIZE_map COPY_map DEREF_map
#pragma interface CONS_map UN_CONS_map DESTROY_CONS_map
#pragma interface PUSH_map POP_map


/* Definitions for union PARAM */

#define ORDER_param ( ( unsigned ) 1 )
#pragma token EXP const : PARAM : NULL_param #
#pragma token PROC ( EXP : PARAM : ) EXP : int : IS_NULL_param #
#pragma token PROC ( EXP : PARAM :, EXP : PARAM : ) EXP : int : EQ_param #
#pragma interface NULL_param IS_NULL_param EQ_param

#pragma token EXP const : SIZE ( PARAM ) : SIZE_param #

#pragma token PROC (\
	EXP : PTR ( PARAM ) :,\
	EXP : PARAM :\
    ) EXP : void : COPY_param #

#pragma token PROC (\
	EXP : PTR ( PARAM ) :\
    ) EXP : PARAM : DEREF_param #

#pragma token PROC (\
	EXP : PARAM :,\
	EXP : LIST ( PARAM ) :,\
	EXP lvalue : LIST ( PARAM ) :\
    ) STATEMENT CONS_param #

#pragma token PROC (\
	EXP lvalue : PARAM :,\
	EXP lvalue : LIST ( PARAM ) :,\
	EXP : LIST ( PARAM ) :\
    ) STATEMENT UN_CONS_param #

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : PARAM :,\
	EXP lvalue : LIST ( PARAM ) :,\
	EXP : LIST ( PARAM ) :\
    ) STATEMENT DESTROY_CONS_param #

#pragma token PROC (\
	EXP : PARAM :,\
	EXP lvalue : STACK ( PARAM ) :\
    ) STATEMENT PUSH_param #

#pragma token PROC (\
	EXP lvalue : PARAM :,\
	EXP lvalue : STACK ( PARAM ) :\
    ) STATEMENT POP_param #

#pragma interface SIZE_param COPY_param DEREF_param
#pragma interface CONS_param UN_CONS_param DESTROY_CONS_param
#pragma interface PUSH_param POP_param


/* Definitions for union ENTRY */

#define ORDER_entry ( ( unsigned ) 1 )
#pragma token EXP const : ENTRY : NULL_entry #
#pragma token PROC ( EXP : ENTRY : ) EXP : int : IS_NULL_entry #
#pragma token PROC ( EXP : ENTRY :, EXP : ENTRY : ) EXP : int : EQ_entry #
#pragma interface NULL_entry IS_NULL_entry EQ_entry

#pragma token EXP const : SIZE ( ENTRY ) : SIZE_entry #

#pragma token PROC (\
	EXP : PTR ( ENTRY ) :,\
	EXP : ENTRY :\
    ) EXP : void : COPY_entry #

#pragma token PROC (\
	EXP : PTR ( ENTRY ) :\
    ) EXP : ENTRY : DEREF_entry #

#pragma token PROC (\
	EXP : ENTRY :,\
	EXP : LIST ( ENTRY ) :,\
	EXP lvalue : LIST ( ENTRY ) :\
    ) STATEMENT CONS_entry #

#pragma token PROC (\
	EXP lvalue : ENTRY :,\
	EXP lvalue : LIST ( ENTRY ) :,\
	EXP : LIST ( ENTRY ) :\
    ) STATEMENT UN_CONS_entry #

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : ENTRY :,\
	EXP lvalue : LIST ( ENTRY ) :,\
	EXP : LIST ( ENTRY ) :\
    ) STATEMENT DESTROY_CONS_entry #

#pragma token PROC (\
	EXP : ENTRY :,\
	EXP lvalue : STACK ( ENTRY ) :\
    ) STATEMENT PUSH_entry #

#pragma token PROC (\
	EXP lvalue : ENTRY :,\
	EXP lvalue : STACK ( ENTRY ) :\
    ) STATEMENT POP_entry #

#pragma interface SIZE_entry COPY_entry DEREF_entry
#pragma interface CONS_entry UN_CONS_entry DESTROY_CONS_entry
#pragma interface PUSH_entry POP_entry


#endif
