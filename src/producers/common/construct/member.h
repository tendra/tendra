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


#ifndef MEMBER_INCLUDED
#define MEMBER_INCLUDED


/*
    MEMBER SELECTOR DECLARATIONS

    The routines in this module are concerned with the construction and
    manipulation of class member selectors.
*/

extern EXP begin_field_exp PROTO_S ( ( int, EXP, TYPE *, NAMESPACE * ) ) ;
extern EXP end_field_exp PROTO_S ( ( int, EXP, TYPE, NAMESPACE, IDENTIFIER, int ) ) ;
extern EXP make_field_exp PROTO_S ( ( int, EXP, EXP ) ) ;
extern EXP make_member_exp PROTO_S ( ( int, EXP, EXP ) ) ;
extern EXP make_this_field PROTO_S ( ( IDENTIFIER ) ) ;

extern OFFSET decons_bitf_exp PROTO_S ( ( EXP * ) ) ;
extern OFFSET decons_bitf_off PROTO_S ( ( OFFSET * ) ) ;
extern NAMESPACE offset_nspace PROTO_S ( ( TYPE ) ) ;
extern OFFSET offset_member PROTO_S ( ( TYPE, IDENTIFIER, TYPE *, NAMESPACE, int ) ) ;
extern OFFSET offset_index PROTO_S ( ( TYPE, EXP, TYPE * ) ) ;
extern OFFSET offset_add PROTO_S ( ( OFFSET, OFFSET ) ) ;


#endif
