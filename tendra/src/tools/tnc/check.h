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


#ifndef CHECK_INCLUDED
#define CHECK_INCLUDED


/*
    BASIC SHAPE CHECKING ROUTINES
*/

extern void check_exp_fn PROTO_S ( ( node * ) ) ;
extern void check_nat_fn PROTO_S ( ( node * ) ) ;
extern void check_shape_fn PROTO_S ( ( node * ) ) ;
extern void check_snat_fn PROTO_S ( ( node * ) ) ;
extern void check_access_fn PROTO_S ( ( node * ) ) ;
extern void check_tagdef PROTO_S ( ( construct * ) ) ;
extern boolean do_check ;
extern char *checking ;

#define check_exp( X )		check_exp_fn ( ( X ) )
#define check_nat( X )		check_nat_fn ( ( X ) )
#define check_shape( X )	check_shape_fn ( ( X ) )
#define check_signed_nat( X )	check_snat_fn ( ( X ) )
#define check_access( X )	check_access_fn ( ( X ) )


#endif
