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


#ifndef ALLOCATE_INCLUDED
#define ALLOCATE_INCLUDED


/*
    ALLOCATION EXPRESSION DECLARATIONS

    The routines in this module are used to build up the new and delete
    expressions.  sizeof expressions are also included for no very good
    reason.
*/

extern IDENTIFIER find_allocator PROTO_S ( ( TYPE, int, int, IDENTIFIER ) ) ;
extern TYPE check_allocator PROTO_S ( ( TYPE, IDENTIFIER, int, int ) ) ;
extern void recheck_allocator PROTO_S ( ( IDENTIFIER, int ) ) ;
extern EXP make_delete_exp PROTO_S ( ( int, int, EXP ) ) ;
extern EXP make_new_exp PROTO_S ( ( TYPE, int, int, LIST ( EXP ), EXP ) ) ;
extern EXP make_new_init PROTO_S ( ( TYPE, LIST ( EXP ), int ) ) ;
extern EXP begin_new_try PROTO_S ( ( void ) ) ;
extern EXP end_new_try PROTO_S ( ( EXP, EXP ) ) ;
extern EXP new_try_body PROTO_S ( ( EXP ) ) ;
extern EXP make_sizeof_exp PROTO_S ( ( TYPE, EXP, int, int ) ) ;
extern TYPE typeof_exp PROTO_S ( ( EXP *, int, int ) ) ;
extern NAT make_new_array_dim PROTO_S ( ( EXP ) ) ;
extern void old_delete_array PROTO_S ( ( EXP ) ) ;
extern EXP sizeof_array PROTO_S ( ( TYPE *, TYPE ) ) ;
extern EXP sizeof_init PROTO_S ( ( EXP, TYPE ) ) ;
extern EXP sizeof_exp PROTO_S ( ( TYPE ) ) ;


#endif
