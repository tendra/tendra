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


#ifndef MACRO_INCLUDED
#define MACRO_INCLUDED


/*
    TYPE REPRESENTING THE LOCATION OF A LIST OF TOKENS

    This type represents the location of a list of tokens and it used in
    expand_macro.  The toks field gives a pointer to this list, while the
    next field allows these locations to be formed into lists.
*/

typedef struct tok_loc_tag {
    PPTOKEN **toks ;
    struct tok_loc_tag *next ;
} TOKEN_LOC ;


/*
    MACRO EXPANSION DECLARATIONS

    The routines in this module are concerned with the manipulation of
    lists of preprocessing tokens, including the expansion of macros.
*/

extern void init_macros PROTO_S ( ( int, int ) ) ;
extern void term_macros PROTO_S ( ( void ) ) ;
extern PPTOKEN *recognise_strings PROTO_S ( ( PPTOKEN *, HASHID, int ) ) ;
extern PPTOKEN *expand_macro PROTO_S ( ( HASHID, TOKEN_LOC *, int ) ) ;
extern PPTOKEN *read_line PROTO_S ( ( int, int ) ) ;
extern PPTOKEN *expand_tok_list PROTO_S ( ( PPTOKEN * ) ) ;
extern PPTOKEN *clean_tok_list PROTO_S ( ( PPTOKEN * ) ) ;
extern PPTOKEN *new_pptok PROTO_S ( ( void ) ) ;
extern void free_tok_list PROTO_S ( ( PPTOKEN * ) ) ;
extern int quote_tok_list PROTO_S ( ( PPTOKEN *, int, int ) ) ;
extern void token_parts PROTO_S ( ( int, PPTOKEN * ) ) ;


/*
    MACRO EXPANSION VARIABLES

    These variables are used in the macro expansion routines.
*/

extern NAMESPACE assert_namespace ;
extern PPTOKEN *free_tokens ;
extern TOKEN_LOC *file_loc ;


/*
    BUILT-IN MACRO FLAG

    This flag is used as part of the storage field of a macro to indicate
    a built-in macro.
*/

#define dspec_builtin		dspec_static


#endif
