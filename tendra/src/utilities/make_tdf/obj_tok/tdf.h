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
    AUTOMATICALLY GENERATED FROM ALGEBRA tdf (VERSION 1.0)
    BY calculus (VERSION 1.2)
*/

#ifndef TDF_H_TOK_INCLUDED
#define TDF_H_TOK_INCLUDED

#ifndef tdf_NAME
#define tdf_NAME			"tdf"
#define tdf_VERSION			"1.0"
#define tdf_SPECIFICATION		1
#define tdf_IMPLEMENTATION		0
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

#ifndef tdf_DESTR_DEFINED
#define tdf_DESTR_DEFINED
typedef void ( *DESTROYER ) () ;
#endif

#pragma token PROC ( TYPE ) TYPE PTR #
#pragma token PROC ( TYPE ) TYPE LIST #
#pragma token PROC ( TYPE ) TYPE STACK #
#pragma token PROC ( TYPE ) TYPE SIZE #

#pragma interface PTR LIST STACK SIZE


/* Enumeration type definitions */



/* Union type definitions */

#pragma token TYPE PARAMETER #
#pragma interface PARAMETER
#pragma token TYPE CONSTRUCT #
#pragma interface CONSTRUCT
#pragma token TYPE SORT_INFO #
#pragma interface SORT_INFO
#pragma token TYPE SORT #
#pragma interface SORT
#pragma token TYPE LINKAGE #
#pragma interface LINKAGE
#pragma token TYPE SPECIFICATION #
#pragma interface SPECIFICATION
#pragma token TYPE COMMAND #
#pragma interface COMMAND


/* Structure declarations */



/* Identity type definitions */



/* Structure definitions */

#ifndef tdf_STRUCT_DEFINED
#define tdf_STRUCT_DEFINED

#endif /* tdf_STRUCT_DEFINED */


/* Function declarations */

extern void destroy_tdf () ;
extern void dummy_destroy_tdf () ;
#ifdef tdf_IO_ROUTINES
extern unsigned crt_tdf_alias ;
extern void clear_tdf_alias PROTO_S ( ( void ) ) ;
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

#ifdef tdf_IO_ROUTINES
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

#ifdef tdf_IO_ROUTINES
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


/* Definitions for primitive unsigned */

#pragma token EXP const : SIZE ( unsigned ) : SIZE_unsigned #

#pragma token PROC (\
	EXP : PTR ( unsigned ) :,\
	EXP : unsigned :\
    ) EXP : void : COPY_unsigned #

#pragma token PROC (\
	EXP : PTR ( unsigned ) :\
    ) EXP : unsigned : DEREF_unsigned #

#pragma token PROC (\
	EXP : unsigned :,\
	EXP : LIST ( unsigned ) :,\
	EXP lvalue : LIST ( unsigned ) :\
    ) STATEMENT CONS_unsigned #

#pragma token PROC (\
	EXP lvalue : unsigned :,\
	EXP lvalue : LIST ( unsigned ) :,\
	EXP : LIST ( unsigned ) :\
    ) STATEMENT UN_CONS_unsigned #

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : LIST ( unsigned ) :,\
	EXP : LIST ( unsigned ) :\
    ) STATEMENT DESTROY_CONS_unsigned #

#pragma token PROC (\
	EXP : unsigned :,\
	EXP lvalue : STACK ( unsigned ) :\
    ) STATEMENT PUSH_unsigned #

#pragma token PROC (\
	EXP lvalue : unsigned :,\
	EXP lvalue : STACK ( unsigned ) :\
    ) STATEMENT POP_unsigned #

#pragma interface SIZE_unsigned COPY_unsigned DEREF_unsigned
#pragma interface CONS_unsigned UN_CONS_unsigned DESTROY_CONS_unsigned
#pragma interface PUSH_unsigned POP_unsigned


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


/* Definitions for union PARAMETER */

#define ORDER_par ( ( unsigned ) 1 )
#pragma token EXP const : PARAMETER : NULL_par #
#pragma token PROC ( EXP : PARAMETER : ) EXP : int : IS_NULL_par #
#pragma token PROC ( EXP : PARAMETER :, EXP : PARAMETER : ) EXP : int : EQ_par #
#pragma interface NULL_par IS_NULL_par EQ_par

#pragma token EXP const : SIZE ( PARAMETER ) : SIZE_par #

#pragma token PROC (\
	EXP : PTR ( PARAMETER ) :,\
	EXP : PARAMETER :\
    ) EXP : void : COPY_par #

#pragma token PROC (\
	EXP : PTR ( PARAMETER ) :\
    ) EXP : PARAMETER : DEREF_par #

#pragma token PROC (\
	EXP : PARAMETER :,\
	EXP : LIST ( PARAMETER ) :,\
	EXP lvalue : LIST ( PARAMETER ) :\
    ) STATEMENT CONS_par #

#pragma token PROC (\
	EXP lvalue : PARAMETER :,\
	EXP lvalue : LIST ( PARAMETER ) :,\
	EXP : LIST ( PARAMETER ) :\
    ) STATEMENT UN_CONS_par #

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : PARAMETER :,\
	EXP lvalue : LIST ( PARAMETER ) :,\
	EXP : LIST ( PARAMETER ) :\
    ) STATEMENT DESTROY_CONS_par #

#pragma token PROC (\
	EXP : PARAMETER :,\
	EXP lvalue : STACK ( PARAMETER ) :\
    ) STATEMENT PUSH_par #

#pragma token PROC (\
	EXP lvalue : PARAMETER :,\
	EXP lvalue : STACK ( PARAMETER ) :\
    ) STATEMENT POP_par #

#pragma interface SIZE_par COPY_par DEREF_par
#pragma interface CONS_par UN_CONS_par DESTROY_CONS_par
#pragma interface PUSH_par POP_par


/* Definitions for union CONSTRUCT */

#define ORDER_cons ( ( unsigned ) 1 )
#pragma token EXP const : CONSTRUCT : NULL_cons #
#pragma token PROC ( EXP : CONSTRUCT : ) EXP : int : IS_NULL_cons #
#pragma token PROC ( EXP : CONSTRUCT :, EXP : CONSTRUCT : ) EXP : int : EQ_cons #
#pragma interface NULL_cons IS_NULL_cons EQ_cons

#pragma token EXP const : SIZE ( CONSTRUCT ) : SIZE_cons #

#pragma token PROC (\
	EXP : PTR ( CONSTRUCT ) :,\
	EXP : CONSTRUCT :\
    ) EXP : void : COPY_cons #

#pragma token PROC (\
	EXP : PTR ( CONSTRUCT ) :\
    ) EXP : CONSTRUCT : DEREF_cons #

#pragma token PROC (\
	EXP : CONSTRUCT :,\
	EXP : LIST ( CONSTRUCT ) :,\
	EXP lvalue : LIST ( CONSTRUCT ) :\
    ) STATEMENT CONS_cons #

#pragma token PROC (\
	EXP lvalue : CONSTRUCT :,\
	EXP lvalue : LIST ( CONSTRUCT ) :,\
	EXP : LIST ( CONSTRUCT ) :\
    ) STATEMENT UN_CONS_cons #

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : CONSTRUCT :,\
	EXP lvalue : LIST ( CONSTRUCT ) :,\
	EXP : LIST ( CONSTRUCT ) :\
    ) STATEMENT DESTROY_CONS_cons #

#pragma token PROC (\
	EXP : CONSTRUCT :,\
	EXP lvalue : STACK ( CONSTRUCT ) :\
    ) STATEMENT PUSH_cons #

#pragma token PROC (\
	EXP lvalue : CONSTRUCT :,\
	EXP lvalue : STACK ( CONSTRUCT ) :\
    ) STATEMENT POP_cons #

#pragma interface SIZE_cons COPY_cons DEREF_cons
#pragma interface CONS_cons UN_CONS_cons DESTROY_CONS_cons
#pragma interface PUSH_cons POP_cons


/* Definitions for union SORT_INFO */

#define ORDER_info ( ( unsigned ) 6 )
#pragma token EXP const : SORT_INFO : NULL_info #
#pragma token PROC ( EXP : SORT_INFO : ) EXP : int : IS_NULL_info #
#pragma token PROC ( EXP : SORT_INFO :, EXP : SORT_INFO : ) EXP : int : EQ_info #
#pragma interface NULL_info IS_NULL_info EQ_info

#pragma token EXP const : SIZE ( SORT_INFO ) : SIZE_info #

#pragma token PROC (\
	EXP : PTR ( SORT_INFO ) :,\
	EXP : SORT_INFO :\
    ) EXP : void : COPY_info #

#pragma token PROC (\
	EXP : PTR ( SORT_INFO ) :\
    ) EXP : SORT_INFO : DEREF_info #

#pragma token PROC (\
	EXP : SORT_INFO :,\
	EXP : LIST ( SORT_INFO ) :,\
	EXP lvalue : LIST ( SORT_INFO ) :\
    ) STATEMENT CONS_info #

#pragma token PROC (\
	EXP lvalue : SORT_INFO :,\
	EXP lvalue : LIST ( SORT_INFO ) :,\
	EXP : LIST ( SORT_INFO ) :\
    ) STATEMENT UN_CONS_info #

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : SORT_INFO :,\
	EXP lvalue : LIST ( SORT_INFO ) :,\
	EXP : LIST ( SORT_INFO ) :\
    ) STATEMENT DESTROY_CONS_info #

#pragma token PROC (\
	EXP : SORT_INFO :,\
	EXP lvalue : STACK ( SORT_INFO ) :\
    ) STATEMENT PUSH_info #

#pragma token PROC (\
	EXP lvalue : SORT_INFO :,\
	EXP lvalue : STACK ( SORT_INFO ) :\
    ) STATEMENT POP_info #

#pragma interface SIZE_info COPY_info DEREF_info
#pragma interface CONS_info UN_CONS_info DESTROY_CONS_info
#pragma interface PUSH_info POP_info


/* Definitions for union SORT */

#define ORDER_sort ( ( unsigned ) 1 )
#pragma token EXP const : SORT : NULL_sort #
#pragma token PROC ( EXP : SORT : ) EXP : int : IS_NULL_sort #
#pragma token PROC ( EXP : SORT :, EXP : SORT : ) EXP : int : EQ_sort #
#pragma interface NULL_sort IS_NULL_sort EQ_sort

#pragma token EXP const : SIZE ( SORT ) : SIZE_sort #

#pragma token PROC (\
	EXP : PTR ( SORT ) :,\
	EXP : SORT :\
    ) EXP : void : COPY_sort #

#pragma token PROC (\
	EXP : PTR ( SORT ) :\
    ) EXP : SORT : DEREF_sort #

#pragma token PROC (\
	EXP : SORT :,\
	EXP : LIST ( SORT ) :,\
	EXP lvalue : LIST ( SORT ) :\
    ) STATEMENT CONS_sort #

#pragma token PROC (\
	EXP lvalue : SORT :,\
	EXP lvalue : LIST ( SORT ) :,\
	EXP : LIST ( SORT ) :\
    ) STATEMENT UN_CONS_sort #

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : SORT :,\
	EXP lvalue : LIST ( SORT ) :,\
	EXP : LIST ( SORT ) :\
    ) STATEMENT DESTROY_CONS_sort #

#pragma token PROC (\
	EXP : SORT :,\
	EXP lvalue : STACK ( SORT ) :\
    ) STATEMENT PUSH_sort #

#pragma token PROC (\
	EXP lvalue : SORT :,\
	EXP lvalue : STACK ( SORT ) :\
    ) STATEMENT POP_sort #

#pragma interface SIZE_sort COPY_sort DEREF_sort
#pragma interface CONS_sort UN_CONS_sort DESTROY_CONS_sort
#pragma interface PUSH_sort POP_sort


/* Definitions for union LINKAGE */

#define ORDER_link ( ( unsigned ) 1 )
#pragma token EXP const : LINKAGE : NULL_link #
#pragma token PROC ( EXP : LINKAGE : ) EXP : int : IS_NULL_link #
#pragma token PROC ( EXP : LINKAGE :, EXP : LINKAGE : ) EXP : int : EQ_link #
#pragma interface NULL_link IS_NULL_link EQ_link

#pragma token EXP const : SIZE ( LINKAGE ) : SIZE_link #

#pragma token PROC (\
	EXP : PTR ( LINKAGE ) :,\
	EXP : LINKAGE :\
    ) EXP : void : COPY_link #

#pragma token PROC (\
	EXP : PTR ( LINKAGE ) :\
    ) EXP : LINKAGE : DEREF_link #

#pragma token PROC (\
	EXP : LINKAGE :,\
	EXP : LIST ( LINKAGE ) :,\
	EXP lvalue : LIST ( LINKAGE ) :\
    ) STATEMENT CONS_link #

#pragma token PROC (\
	EXP lvalue : LINKAGE :,\
	EXP lvalue : LIST ( LINKAGE ) :,\
	EXP : LIST ( LINKAGE ) :\
    ) STATEMENT UN_CONS_link #

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : LINKAGE :,\
	EXP lvalue : LIST ( LINKAGE ) :,\
	EXP : LIST ( LINKAGE ) :\
    ) STATEMENT DESTROY_CONS_link #

#pragma token PROC (\
	EXP : LINKAGE :,\
	EXP lvalue : STACK ( LINKAGE ) :\
    ) STATEMENT PUSH_link #

#pragma token PROC (\
	EXP lvalue : LINKAGE :,\
	EXP lvalue : STACK ( LINKAGE ) :\
    ) STATEMENT POP_link #

#pragma interface SIZE_link COPY_link DEREF_link
#pragma interface CONS_link UN_CONS_link DESTROY_CONS_link
#pragma interface PUSH_link POP_link


/* Definitions for union SPECIFICATION */

#define ORDER_spec ( ( unsigned ) 1 )
#pragma token EXP const : SPECIFICATION : NULL_spec #
#pragma token PROC ( EXP : SPECIFICATION : ) EXP : int : IS_NULL_spec #
#pragma token PROC ( EXP : SPECIFICATION :, EXP : SPECIFICATION : ) EXP : int : EQ_spec #
#pragma interface NULL_spec IS_NULL_spec EQ_spec

#pragma token EXP const : SIZE ( SPECIFICATION ) : SIZE_spec #

#pragma token PROC (\
	EXP : PTR ( SPECIFICATION ) :,\
	EXP : SPECIFICATION :\
    ) EXP : void : COPY_spec #

#pragma token PROC (\
	EXP : PTR ( SPECIFICATION ) :\
    ) EXP : SPECIFICATION : DEREF_spec #

#pragma token PROC (\
	EXP : SPECIFICATION :,\
	EXP : LIST ( SPECIFICATION ) :,\
	EXP lvalue : LIST ( SPECIFICATION ) :\
    ) STATEMENT CONS_spec #

#pragma token PROC (\
	EXP lvalue : SPECIFICATION :,\
	EXP lvalue : LIST ( SPECIFICATION ) :,\
	EXP : LIST ( SPECIFICATION ) :\
    ) STATEMENT UN_CONS_spec #

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : SPECIFICATION :,\
	EXP lvalue : LIST ( SPECIFICATION ) :,\
	EXP : LIST ( SPECIFICATION ) :\
    ) STATEMENT DESTROY_CONS_spec #

#pragma token PROC (\
	EXP : SPECIFICATION :,\
	EXP lvalue : STACK ( SPECIFICATION ) :\
    ) STATEMENT PUSH_spec #

#pragma token PROC (\
	EXP lvalue : SPECIFICATION :,\
	EXP lvalue : STACK ( SPECIFICATION ) :\
    ) STATEMENT POP_spec #

#pragma interface SIZE_spec COPY_spec DEREF_spec
#pragma interface CONS_spec UN_CONS_spec DESTROY_CONS_spec
#pragma interface PUSH_spec POP_spec


/* Definitions for union COMMAND */

#define ORDER_cmd ( ( unsigned ) 6 )
#pragma token EXP const : COMMAND : NULL_cmd #
#pragma token PROC ( EXP : COMMAND : ) EXP : int : IS_NULL_cmd #
#pragma token PROC ( EXP : COMMAND :, EXP : COMMAND : ) EXP : int : EQ_cmd #
#pragma interface NULL_cmd IS_NULL_cmd EQ_cmd

#pragma token EXP const : SIZE ( COMMAND ) : SIZE_cmd #

#pragma token PROC (\
	EXP : PTR ( COMMAND ) :,\
	EXP : COMMAND :\
    ) EXP : void : COPY_cmd #

#pragma token PROC (\
	EXP : PTR ( COMMAND ) :\
    ) EXP : COMMAND : DEREF_cmd #

#pragma token PROC (\
	EXP : COMMAND :,\
	EXP : LIST ( COMMAND ) :,\
	EXP lvalue : LIST ( COMMAND ) :\
    ) STATEMENT CONS_cmd #

#pragma token PROC (\
	EXP lvalue : COMMAND :,\
	EXP lvalue : LIST ( COMMAND ) :,\
	EXP : LIST ( COMMAND ) :\
    ) STATEMENT UN_CONS_cmd #

#pragma token PROC (\
	EXP : DESTROYER :,\
	EXP lvalue : COMMAND :,\
	EXP lvalue : LIST ( COMMAND ) :,\
	EXP : LIST ( COMMAND ) :\
    ) STATEMENT DESTROY_CONS_cmd #

#pragma token PROC (\
	EXP : COMMAND :,\
	EXP lvalue : STACK ( COMMAND ) :\
    ) STATEMENT PUSH_cmd #

#pragma token PROC (\
	EXP lvalue : COMMAND :,\
	EXP lvalue : STACK ( COMMAND ) :\
    ) STATEMENT POP_cmd #

#pragma interface SIZE_cmd COPY_cmd DEREF_cmd
#pragma interface CONS_cmd UN_CONS_cmd DESTROY_CONS_cmd
#pragma interface PUSH_cmd POP_cmd


#endif
