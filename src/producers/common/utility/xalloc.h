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


#ifndef XALLOC_INCLUDED
#define XALLOC_INCLUDED


/*
    MEMORY ALLOCATION DECLARATIONS

    The routines in this module are concerned with the allocation of
    heap memory.
*/

extern gen_ptr xmalloc PROTO_S ( ( gen_size ) ) ;
extern gen_ptr xrealloc PROTO_S ( ( gen_ptr, gen_size ) ) ;
extern void xfree PROTO_S ( ( gen_ptr ) ) ;
extern string xustr PROTO_S ( ( gen_size ) ) ;
extern string xustrcpy PROTO_S ( ( string ) ) ;
extern string xustrncpy PROTO_S ( ( string, gen_size ) ) ;
extern string xustrcat PROTO_S ( ( string, string ) ) ;
extern void xufree PROTO_S ( ( string, gen_size ) ) ;
extern void xumemcpy PROTO_S ( ( string, string, gen_size ) ) ;
extern int xumemcmp PROTO_S ( ( string, string, gen_size ) ) ;


/*
    MACROS FOR ACCESSING MEMORY ALLOCATION ROUTINES

    These macros give a convenient method for accessing the routines above.
    For example, xmalloc_nof ( T, N ) allocates space for N objects of
    type T.
*/

#define xalloc_scale( T, N )\
	( ( gen_size ) ( N ) * ( gen_size ) sizeof ( T ) ) )

#define xmalloc_one( T )\
	( ( T * ) xmalloc ( xalloc_scale ( T, 1 ) )

#define xmalloc_nof( T, N )\
	( ( T * ) xmalloc ( xalloc_scale ( T, N ) )

#define xrealloc_nof( P, T, N )\
	( ( T * ) xrealloc ( ( gen_ptr ) ( P ), xalloc_scale ( T, N ) )

#define xfree_nof( P )\
	xfree ( ( gen_ptr ) ( P ) )


#endif
