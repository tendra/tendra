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


#ifndef PREPROC_INCLUDED
#define PREPROC_INCLUDED


/*
    PREPROCESSING DECLARATIONS

    The routines in this module are concerned with the processing of
    preprocessing directives.  They include preprocess_file which is the
    stand-alone preprocessing action of the program.
*/

extern int read_preproc_dir PROTO_S ( ( int, int ) ) ;
extern void patch_preproc_dir PROTO_S ( ( PPTOKEN * ) ) ;
extern int read_include PROTO_S ( ( int, int ) ) ;
extern unsigned check_macro PROTO_S ( ( HASHID, int ) ) ;
extern IDENTIFIER make_assert PROTO_S ( ( HASHID, int ) ) ;
extern void read_ident PROTO_S ( ( int ) ) ;
extern void read_weak PROTO_S ( ( int ) ) ;
extern void preprocess_file PROTO_S ( ( void ) ) ;
extern void start_preproc_if PROTO_S ( ( void ) ) ;
extern int clear_preproc_if PROTO_S ( ( void ) ) ;
extern int patch_cond PROTO_S ( ( int, int ) ) ;


/*
    PREPROCESSING VARIABLES

    These variables are used by the preprocessing routines.
*/

extern int preproc_only ;
extern int preproc_space ;
extern int pragma_number ;
extern int in_preproc_dir ;
extern int no_preproc_dir ;
extern int in_pragma_dir ;
extern int in_hash_if_exp ;
extern EXP crt_hash_if_exp ;
extern LOCATION preproc_loc ;
extern IDENTIFIER token_macro ;


/*
    CONDITIONAL COMPILATION STATES

    These values are used to identify the various conditional compilation
    states.  The condition may be true, false, being skipped, or unresolved.
    In addition a conditional compilation may or may not have associated
    '#else' and '#elif' statements.  There is a special value for indicating
    the end of an individual file.
*/

#define PP_FALSE			( ( unsigned ) 0x00 )
#define PP_TRUE				( ( unsigned ) 0x01 )
#define PP_PAST				( ( unsigned ) 0x02 )
#define PP_SKIP				( ( unsigned ) 0x03 )
#define PP_UNRESOLVED			( ( unsigned ) 0x04 )
#define PP_COND_MASK			( ( unsigned ) 0x0f )
#define PP_HAVE_ELSE			( ( unsigned ) 0x10 )
#define PP_HAVE_ELIF			( ( unsigned ) 0x20 )
#define PP_TOKEN			( ( unsigned ) 0x40 )
#define PP_END				( ( unsigned ) 0xff )


#endif
