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


#ifndef TOKDEF_INCLUDED
#define TOKDEF_INCLUDED


/*
    TDF TOKEN DECLARATIONS

    The routines in this module are concerned with the definition of TDF
    tokens.
*/

extern int define_exp_token PROTO_S ( ( IDENTIFIER, EXP, int ) ) ;
extern int define_func_token PROTO_S ( ( IDENTIFIER, IDENTIFIER ) ) ;
extern int define_mem_token PROTO_S ( ( IDENTIFIER, OFFSET, TYPE, int ) ) ;
extern int define_nat_token PROTO_S ( ( IDENTIFIER, NAT ) ) ;
extern int define_templ_token PROTO_S ( ( IDENTIFIER, IDENTIFIER ) ) ;
extern int define_type_token PROTO_S ( ( IDENTIFIER, TYPE, int ) ) ;
extern int define_token_macro PROTO_S ( ( IDENTIFIER, IDENTIFIER ) ) ;
extern int define_mem_macro PROTO_S ( ( IDENTIFIER, TYPE ) ) ;
extern int defining_token PROTO_S ( ( IDENTIFIER ) ) ;

extern LIST ( TOKEN ) make_token_args PROTO_S ( ( IDENTIFIER, LIST ( IDENTIFIER ), ERROR * ) ) ;
extern int save_token_args PROTO_S ( ( LIST ( IDENTIFIER ), LIST ( TOKEN ) ) ) ;
extern void restore_token_args PROTO_S ( ( LIST ( IDENTIFIER ), int ) ) ;
extern int merge_token_args PROTO_S ( ( LIST ( IDENTIFIER ), int, int ) ) ;
extern void assign_token PROTO_S ( ( IDENTIFIER, TOKEN ) ) ;
extern int is_bound_tok PROTO_S ( ( TOKEN, int ) ) ;
extern TOKEN find_tokdef PROTO_S ( ( IDENTIFIER ) ) ;
extern void init_token_args PROTO_S ( ( void ) ) ;

extern PPTOKEN *skip_token_args PROTO_S ( ( IDENTIFIER ) ) ;
extern EXP parse_exp_token PROTO_S ( ( IDENTIFIER, PPTOKEN * ) ) ;
extern OFFSET parse_mem_token PROTO_S ( ( IDENTIFIER, PPTOKEN * ) ) ;
extern TYPE parse_type_token PROTO_S ( ( IDENTIFIER, PPTOKEN * ) ) ;
extern int unify_id PROTO_S ( ( IDENTIFIER, IDENTIFIER, int ) ) ;

extern IDENTIFIER unify_id_pending ;
extern int in_proc_token ;
extern int force_template ;
extern int force_tokdef ;
extern int expand_tokdef ;
extern TYPE redef_type ;


#endif
