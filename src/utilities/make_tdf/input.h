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


#ifndef INPUT_INCLUDED
#define INPUT_INCLUDED


/*
    INPUT CONSTRUCTION DECLARATIONS
*/

extern SORT find_sort PROTO_S ( ( string, int ) ) ;
extern void compound_sort PROTO_S ( ( SORT, string, unsigned, int ) ) ;
extern void basic_sort PROTO_S ( ( SORT, unsigned, unsigned, LIST ( CONSTRUCT )  ) ) ;
extern PARAMETER find_param PROTO_S ( ( CONSTRUCT, unsigned ) ) ;
extern CONSTRUCT make_construct PROTO_S ( ( string, unsigned, SORT, LIST ( PARAMETER ) ) ) ;
extern CONSTRUCT find_construct PROTO_S ( ( SORT, string ) ) ;
extern LIST ( LINKAGE ) foreign_sorts PROTO_S ( ( void ) ) ;
extern LIST ( SORT ) check_sorts PROTO_S ( ( void ) ) ;
extern void mark_construct PROTO_S ( ( CONSTRUCT, int ) ) ;
extern void mark_sort PROTO_S ( ( SORT, int ) ) ;
extern void mark_all_sorts PROTO_S ( ( int ) ) ;
extern void set_special PROTO_S ( ( SORT, string, unsigned ) ) ;
extern CONSTRUCT get_special PROTO_S ( ( SORT, unsigned ) ) ;
extern string ends_in PROTO_S ( ( string, string ) ) ;
extern void builtin_sorts PROTO_S ( ( void ) ) ;
extern string to_capitals PROTO_S ( ( string ) ) ;


/*
    KINDS OF CONSTRUCT
*/

#define KIND_simple		( ( unsigned ) 0 )
#define KIND_token		( ( unsigned ) 1 )
#define KIND_cond		( ( unsigned ) 2 )
#define KIND_edge		( ( unsigned ) 3 )
#define KIND_foreign		( ( unsigned ) 4 )
#define KIND_special		( ( unsigned ) 5 )
#define KIND_dummy		( ( unsigned ) 6 )


#endif
