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


#ifndef ACCESS_INCLUDED
#define ACCESS_INCLUDED


/*
    TYPE REPRESENTING LIST OF PENDING ACCESS CHECKS

    This type is used to represent a list of pending access checks.  These
    fall into two categories - member accesses and base class accesses.
*/

typedef struct {
    LIST ( IDENTIFIER ) ids ;
    LIST ( GRAPH ) bases ;
    LIST ( int ) info ;
    int pending ;
    int inherit ;
} ACCESS_LIST ;


/*
    ACCESS DECLARATIONS

    The routines in this module are concerned with class member access.
*/

extern IDENTIFIER access_decl PROTO_S ( ( IDENTIFIER ) ) ;
extern void friend_function PROTO_S ( ( CLASS_TYPE, IDENTIFIER, int ) ) ;
extern void friend_class PROTO_S ( ( CLASS_TYPE, IDENTIFIER, int ) ) ;
extern DECL_SPEC join_access PROTO_S ( ( DECL_SPEC, DECL_SPEC ) ) ;
extern void check_access PROTO_S ( ( IDENTIFIER, DECL_SPEC ) ) ;
extern void check_base_access PROTO_S ( ( GRAPH ) ) ;
extern void immediate_access PROTO_S ( ( IDENTIFIER, IDENTIFIER ) ) ;
extern int clear_access PROTO_S ( ( IDENTIFIER, ACCESS_LIST * ) ) ;
extern int report_access PROTO_S ( ( IDENTIFIER ) ) ;
extern void adjust_access PROTO_S ( ( IDENTIFIER, DECL_SPEC, int ) ) ;
extern void free_access PROTO_S ( ( ACCESS_LIST * ) ) ;
extern void save_access PROTO_S ( ( ACCESS_LIST * ) ) ;
extern int restore_access PROTO_S ( ( IDENTIFIER, ACCESS_LIST * ) ) ;
extern ACCESS_LIST crt_access_list ;
extern int do_access_checks ;
extern DECL_SPEC crt_access ;
extern DECL_SPEC prev_access ;
extern int have_access_decl ;


/*
    SECONDARY ACCESS MACROS

    These macros are used for converting between primary and secondary
    access values.
*/

#define shadow_access( A )	( ( ( A ) & dspec_access ) << 2 )
#define unshadow_access( A )	( ( ( A ) & dspec_access2 ) >> 2 )


#endif
