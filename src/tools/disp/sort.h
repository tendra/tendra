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


#ifndef SORT_INCLUDED
#define SORT_INCLUDED


/*
    AUXILIARY TDF SORT DECODING ROUTINES

    Each TDF sort has an associated decoding routine.  Most of the
    routines are straightforward, and so have been automatically
    generated directly from the TDF specification.  This module deals
    with the few tricky cases.
*/

extern object *de_token_aux PROTO_S ( ( sortname, char * ) ) ;
extern void de_tdfstring_format PROTO_S ( ( void ) ) ;
extern void de_make_label PROTO_S ( ( long ) ) ;
void de_case_fn PROTO_S ( ( char *, char *, char * ) ) ;
void de_mk_proc_fn PROTO_S ( ( char *, char *, char *, char * ) ) ;
void de_solve_fn PROTO_S ( ( char *, char *, char *, char *, int ) ) ;
extern int warn_undeclared ;

#define de_case( X )		de_case_fn ( X, "bx", "ss" )
#define de_labelled( X )	de_solve_fn ( X, "l", "x", "x", 1 )
#define de_sequence( X )	format ( VERT_BRACKETS, "sequence", "+[x]" )
#define de_make_proc( X )	de_mk_proc_fn ( X, "S", "S?[u]t", "?[t?[u]]x" )
#define de_make_string( X )	de_tdfstring_format () ;

#define de_make_nat( X )\
	char *num = tdf_int_str () ;\
	out_signed ( num, 0 )

#define de_make_signed_nat( X )\
	long neg = tdf_bool () ;\
	char *num = tdf_int_str () ;\
	out_signed ( num, ( int ) neg )


#endif
