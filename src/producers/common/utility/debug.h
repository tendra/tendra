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


#ifdef RUNTIME
#ifndef DEBUG_INCLUDED
#define DEBUG_INCLUDED


/*
    DEBUGGING ROUTINE DECLARATIONS

    The routines in this module are designed to aid in program development;
    they do not form part of the program proper.  They are only defined if
    the macro RUNTIME is defined.
*/

extern void DEBUG_access PROTO_S ( ( DECL_SPEC ) ) ;
extern void DEBUG_btype PROTO_S ( ( BASE_TYPE ) ) ;
extern void DEBUG_cinfo PROTO_S ( ( CLASS_INFO ) ) ;
extern void DEBUG_ctype PROTO_S ( ( CLASS_TYPE ) ) ;
extern void DEBUG_cusage PROTO_S ( ( CLASS_USAGE ) ) ;
extern void DEBUG_cv PROTO_S ( ( CV_SPEC ) ) ;
extern void DEBUG_dspec PROTO_S ( ( DECL_SPEC ) ) ;
extern void DEBUG_etype PROTO_S ( ( ENUM_TYPE ) ) ;
extern void DEBUG_exp PROTO_S ( ( EXP ) ) ;
extern void DEBUG_flt PROTO_S ( ( FLOAT ) ) ;
extern void DEBUG_ftype PROTO_S ( ( FLOAT_TYPE ) ) ;
extern void DEBUG_func PROTO_S ( ( IDENTIFIER ) ) ;
extern void DEBUG_graph PROTO_S ( ( GRAPH ) ) ;
extern void DEBUG_hashid PROTO_S ( ( HASHID ) ) ;
extern void DEBUG_hash_table PROTO_S ( ( string ) ) ;
extern void DEBUG_id PROTO_S ( ( IDENTIFIER ) ) ;
extern void DEBUG_id_long PROTO_S ( ( IDENTIFIER ) ) ;
extern void DEBUG_inst PROTO_S ( ( INSTANCE ) ) ;
extern void DEBUG_itype PROTO_S ( ( INT_TYPE ) ) ;
extern void DEBUG_lex PROTO_S ( ( int ) ) ;
extern void DEBUG_loc PROTO_S ( ( LOCATION * ) ) ;
extern void DEBUG_mangle PROTO_S ( ( IDENTIFIER ) ) ;
extern void DEBUG_member PROTO_S ( ( MEMBER ) ) ;
extern void DEBUG_members PROTO_S ( ( NAMESPACE ) ) ;
extern void DEBUG_nat PROTO_S ( ( NAT ) ) ;
extern void DEBUG_nspace PROTO_S ( ( NAMESPACE ) ) ;
extern void DEBUG_ntest PROTO_S ( ( NTEST ) ) ;
extern void DEBUG_ntype PROTO_S ( ( BUILTIN_TYPE ) ) ;
extern void DEBUG_offset PROTO_S ( ( OFFSET ) ) ;
extern void DEBUG_pptok PROTO_S ( ( PPTOKEN * ) ) ;
extern void DEBUG_pptoks PROTO_S ( ( PPTOKEN * ) ) ;
extern void DEBUG_sort PROTO_S ( ( TOKEN ) ) ;
extern void DEBUG_stmt PROTO_S ( ( EXP ) ) ;
extern void DEBUG_str PROTO_S ( ( STRING ) ) ;
extern void DEBUG_type PROTO_S ( ( TYPE ) ) ;
extern void DEBUG_unmangle PROTO_S ( ( CONST char * ) ) ;
extern void DEBUG_virt PROTO_S ( ( VIRTUAL ) ) ;

extern void DEBUG_source PROTO_S ( ( int ) ) ;
extern void DEBUG_where PROTO_S ( ( void ) ) ;

#if c_class_IMPLEMENTATION
extern void debug PROTO_S ( ( c_class * ) ) ;
#endif

#define DEBUG_file	stdout
#define DEBUG_text( A )	fputs_v ( ( A ), DEBUG_file )
#define DEBUG_mark	fprintf_v ( DEBUG_file, "%s: %d\n", __FILE__, __LINE__ )

extern int print_exp_aux PROTO_S ( ( EXP, int, BUFFER *, int ) ) ;
extern int print_offset_aux PROTO_S ( ( OFFSET, BUFFER *, int ) ) ;
extern void debug_option PROTO_S ( ( char * ) ) ;
extern int debugging ;


#endif
#endif
