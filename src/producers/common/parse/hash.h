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


#ifndef HASH_INCLUDED
#define HASH_INCLUDED


/*
    HASH TABLE DECLARATIONS

    The routines in this module are concerned with the look-up of identifiers
    in the hash table.
*/

extern HASHID lookup_name PROTO_S ( ( string, unsigned long, int, int ) ) ;
extern HASHID lookup_conv PROTO_S ( ( TYPE ) ) ;
extern HASHID lookup_constr PROTO_S ( ( TYPE, IDENTIFIER ) ) ;
extern HASHID lookup_destr PROTO_S ( ( TYPE, IDENTIFIER ) ) ;
extern HASHID lookup_anon PROTO_S ( ( void ) ) ;
extern HASHID expand_name PROTO_S ( ( HASHID, CLASS_TYPE ) ) ;
extern HASHID next_expand_name PROTO_S ( ( HASHID ) ) ;
extern void prime_name PROTO_S ( ( IDENTIFIER ) ) ;

extern int find_hashid PROTO_S ( ( HASHID ) ) ;
extern void init_hash PROTO_S ( ( void ) ) ;
extern IDENTIFIER underlying_id PROTO_S ( ( IDENTIFIER ) ) ;
extern void set_hashid_loc PROTO_S ( ( IDENTIFIER, IDENTIFIER ) ) ;
extern unsigned long hash PROTO_S ( ( string ) ) ;
extern IDENTIFIER underlying_op ;
extern HASHID *hash_ops_table ;
extern HASHID hash_keyword [] ;
extern HASHID *hash_table ;


/*
    LOOK UP AN OVERLOADED OPERATOR FUNCTION NAME

    This macro returns the hash table entry for the overloaded operator
    function name corresponding to the lexical token number T.  Note that
    the ISO keywords and digraphs have already been mapped onto their
    primary representations.
*/

#define lookup_op( T )		( hash_ops_table [ ( T ) ] )


/*
    HASH TABLE SIZES

    These macros give the sizes of various hash tables.
*/

#define HASH_SIZE		( ( unsigned long ) 4096 )
#define HASH_POWER		( ( unsigned long ) 37 )
#define HASH_TYPE_SIZE		( ( unsigned long ) 256 )


/*
    KEYWORD HASH TABLE ENTRIES

    The macro KEYWORD gives a convenient method of accessing the table
    hash_keyword.
*/

#define KEYWORD( T )		( hash_keyword [ ( T ) - lex_auto ] )
#define EQ_KEYWORD( N, T )	EQ_hashid ( ( N ), KEYWORD ( T ) )


#endif
