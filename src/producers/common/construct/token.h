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


#ifndef TOKEN_INCLUDED
#define TOKEN_INCLUDED


/*
    TDF TOKEN DECLARATIONS

    The routines in this module are concerned with the construction of
    TDF tokens.
*/

extern IDENTIFIER make_token_decl PROTO_S ( ( TOKEN, int, IDENTIFIER, IDENTIFIER ) ) ;
extern IDENTIFIER make_tok_param PROTO_S ( ( TOKEN, int, IDENTIFIER ) ) ;
extern IDENTIFIER prog_tok_param PROTO_S ( ( IDENTIFIER, TYPE, unsigned, LIST ( IDENTIFIER ) ) ) ;

extern TOKEN begin_proc_token PROTO_S ( ( void ) ) ;
extern TOKEN cont_proc_token PROTO_S ( ( TOKEN, LIST ( IDENTIFIER ), LIST ( IDENTIFIER ) ) ) ;
extern TOKEN end_proc_token PROTO_S ( ( TOKEN, TOKEN ) ) ;
extern void set_proc_token PROTO_S ( ( LIST ( IDENTIFIER ) ) ) ;

extern TOKEN make_func_token PROTO_S ( ( TYPE ) ) ;
extern TOKEN make_type_token PROTO_S ( ( BASE_TYPE ) ) ;
extern TOKEN make_exp_token PROTO_S ( ( TYPE, int, int ) ) ;
extern TOKEN make_member_token PROTO_S ( ( TYPE, TYPE, DECL_SPEC ) ) ;
extern TOKEN func_proc_token PROTO_S ( ( TOKEN ) ) ;
extern int type_token_key PROTO_S ( ( BASE_TYPE ) ) ;

extern EXP expand_exp PROTO_S ( ( EXP, int, int ) ) ;
extern NAT expand_nat PROTO_S ( ( NAT, int, int, ERROR * ) ) ;
extern OFFSET expand_offset PROTO_S ( ( OFFSET, int ) ) ;
extern TYPE expand_type PROTO_S ( ( TYPE, int ) ) ;
extern TOKEN expand_sort PROTO_S ( ( TOKEN, int, int ) ) ;
extern CLASS_TYPE expand_ctype PROTO_S ( ( CLASS_TYPE, int, TYPE * ) ) ;
extern LIST ( TOKEN ) expand_args PROTO_S ( ( LIST ( TOKEN ), int, int ) ) ;
extern LIST ( TYPE ) expand_exceptions PROTO_S ( ( LIST ( TYPE ), int, int * ) ) ;
extern TOKEN expand_templ_sort PROTO_S ( ( TOKEN, int ) ) ;
extern void reset_templ_sort PROTO_S ( ( TOKEN ) ) ;
extern int expand_anon_bitfield ;

extern EXP apply_exp_token PROTO_S ( ( IDENTIFIER, LIST ( TOKEN ), int ) ) ;
extern NAT apply_nat_token PROTO_S ( ( IDENTIFIER, LIST ( TOKEN ) ) ) ;
extern OFFSET apply_mem_token PROTO_S ( ( IDENTIFIER, LIST ( TOKEN ) ) ) ;
extern TYPE apply_type_token PROTO_S ( ( IDENTIFIER, LIST ( TOKEN ), IDENTIFIER ) ) ;
extern TOKEN apply_token PROTO_S ( ( IDENTIFIER, LIST ( TOKEN ) ) ) ;

extern IDENTIFIER find_token PROTO_S ( ( IDENTIFIER ) ) ;
extern IDENTIFIER find_tag_token PROTO_S ( ( IDENTIFIER ) ) ;
extern IDENTIFIER find_mem_token PROTO_S ( ( IDENTIFIER, IDENTIFIER ) ) ;
extern IDENTIFIER find_func_token PROTO_S ( ( IDENTIFIER, unsigned ) ) ;
extern IDENTIFIER find_ext_token PROTO_S ( ( IDENTIFIER ) ) ;
extern IDENTIFIER tok_member PROTO_S ( ( IDENTIFIER, TYPE, int ) ) ;
extern void token_interface PROTO_S ( ( IDENTIFIER, int ) ) ;
extern int crt_interface ;


#endif
