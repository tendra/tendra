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


#ifndef ALIGNMENT_INCLUDED
#define ALIGNMENT_INCLUDED


/*
    ROUTINES FOR MANIPULATING ALIGNMENTS AND OFFSETS
*/

extern node *al_top ;
extern node *al_code ;
extern node *al_frame ;
extern node *al_alloca ;
extern node *al_var_param ;

extern void init_alignments PROTO_S ( ( void ) ) ;
extern node *al_shape PROTO_S ( ( node * ) ) ;
extern void al_equals PROTO_S ( ( node *, node * ) ) ;
extern void al_includes PROTO_S ( ( node *, node * ) ) ;
extern node *al_union PROTO_S ( ( node *, node * ) ) ;
extern node *offset_from PROTO_S ( ( node * ) ) ;
extern node *offset_to PROTO_S ( ( node * ) ) ;
extern node *ptr_to PROTO_S ( ( node * ) ) ;


#endif
