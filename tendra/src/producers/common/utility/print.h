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


#ifndef PRINT_INCLUDED
#define PRINT_INCLUDED


/*
    OBJECT PRINTING DECLARATIONS

    The routines in this module are used to print objects of the various
    basic types used in the program.  They are used primarily in error
    reporting, but print_pptok is also used by the stand-alone preprocessor
    action.
*/

extern int print_access PROTO_S ( ( DECL_SPEC, BUFFER *, int ) ) ;
extern int print_btype PROTO_S ( ( BASE_TYPE, BUFFER *, int ) ) ;
extern int print_ctype PROTO_S ( ( CLASS_TYPE, QUALIFIER, int, BUFFER *, int ) ) ;
extern int print_cv PROTO_S ( ( CV_SPEC, BUFFER *, int ) ) ;
extern int print_dspec PROTO_S ( ( DECL_SPEC, BUFFER *, int ) ) ;
extern int print_etype PROTO_S ( ( ENUM_TYPE, int, BUFFER *, int ) ) ;
extern int print_exp PROTO_S ( ( EXP, int, BUFFER *, int ) ) ;
extern int print_flt PROTO_S ( ( FLOAT, BUFFER *, int ) ) ;
extern int print_ftype PROTO_S ( ( FLOAT_TYPE, BUFFER *, int ) ) ;
extern int print_graph PROTO_S ( ( GRAPH, int, BUFFER *, int ) ) ;
extern int print_hashid PROTO_S ( ( HASHID, int, int, BUFFER *, int ) ) ;
extern int print_id_short PROTO_S ( ( IDENTIFIER, QUALIFIER, BUFFER *, int ) ) ;
extern int print_id_long PROTO_S ( ( IDENTIFIER, QUALIFIER, BUFFER *, int ) ) ;
extern int print_itype PROTO_S ( ( INT_TYPE, BUFFER *, int ) ) ;
extern int print_lex PROTO_S ( ( int, BUFFER *, int ) ) ;
extern int print_loc PROTO_S ( ( LOCATION *, LOCATION *, BUFFER *, int ) ) ;
extern int print_nat PROTO_S ( ( NAT, int, BUFFER *, int ) ) ;
extern int print_nspace PROTO_S ( ( NAMESPACE, QUALIFIER, int, BUFFER *, int ) ) ;
extern int print_ntype PROTO_S ( ( BUILTIN_TYPE, BUFFER *, int ) ) ;
extern int print_offset PROTO_S ( ( OFFSET, BUFFER *, int ) ) ;
extern int print_pptok PROTO_S ( ( PPTOKEN *, BUFFER *, int ) ) ;
extern int print_sort PROTO_S ( ( TOKEN, int, BUFFER *, int ) ) ;
extern int print_str PROTO_S ( ( STRING, BUFFER *, int ) ) ;
extern int print_tok_value PROTO_S ( ( TOKEN, BUFFER *, int ) ) ;
extern int print_token PROTO_S ( ( IDENTIFIER, QUALIFIER, LIST ( TOKEN ), BUFFER *, int ) ) ;
extern int print_type PROTO_S ( ( TYPE, BUFFER *, int ) ) ;
extern int print_type_list PROTO_S ( ( LIST ( TYPE ), BUFFER *, int ) ) ;
extern void print_char PROTO_S ( ( unsigned long, int, int, BUFFER * ) ) ;
extern void print_source PROTO_S ( ( LOCATION *, int, int, CONST char *, FILE * ) ) ;
extern CONST char *ntype_name [] ;
extern int print_type_alias ;
extern int print_uniq_anon ;
extern int print_id_desc ;
extern int print_c_style ;
extern BUFFER print_buff ;


#endif
