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


#ifndef SHAPE_INCLUDED
#define SHAPE_INCLUDED


/*
    BASIC SHAPE CONSTRUCTION ROUTINES
*/

extern node *sh_bottom ;
extern node *sh_proc ;
extern node *sh_top ;

extern node *sh_bitfield PROTO_S ( ( node * ) ) ;
extern node *sh_compound PROTO_S ( ( node * ) ) ;
extern node *sh_floating PROTO_S ( ( node * ) ) ;
extern node *sh_integer PROTO_S ( ( node * ) ) ;
extern node *sh_nof PROTO_S ( ( node *, node * ) ) ;
extern node *sh_offset PROTO_S ( ( node *, node * ) ) ;
extern node *sh_pointer PROTO_S ( ( node * ) ) ;
extern void init_shapes PROTO_S ( ( void ) ) ;
extern node *string_length PROTO_S ( ( node * ) ) ;
extern node *copy_node PROTO_S ( ( node * ) ) ;


/*
    BASIC SHAPE CHECKING ROUTINES
*/

extern node *check_shapes PROTO_S ( ( node *, node *, int ) ) ;
extern node *lub PROTO_S ( ( node *, node * ) ) ;
extern node *check1 PROTO_S ( ( int, node * ) ) ;
extern node *check2 PROTO_S ( ( int, node *, node * ) ) ;
extern node *checkn PROTO_S ( ( int, node *, int ) ) ;
extern node *normalize PROTO_S ( ( node * ) ) ;


/*
    TOKEN EXPANSION ROUTINES
*/

extern node *expand_tok PROTO_S ( ( node * ) ) ;
extern node *expand_fully PROTO_S ( ( node * ) ) ;
extern node *set_token_args PROTO_S ( ( construct **, node *, int ) ) ;
extern void expand_all PROTO_S ( ( void ) ) ;


#endif
