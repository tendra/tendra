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
    GENERIC POINTER
*/

#if FS_PTR_VOID
typedef void *gen_ptr ;
#else
typedef char *gen_ptr ;
#endif


/*
    DECLARATIONS FOR MEMORY ALLOCATION ROUTINES
*/

extern gen_ptr xmalloc PROTO_S ( ( long ) ) ;
extern gen_ptr xcalloc PROTO_S ( ( long, long ) ) ;
extern gen_ptr xrealloc PROTO_S ( ( gen_ptr, long ) ) ;
extern void xfree PROTO_S ( ( gen_ptr ) ) ;
extern char *xstr PROTO_S ( ( long ) ) ;
extern char *xstrcpy PROTO_S ( ( CONST char * ) ) ;
extern char *xstrcat PROTO_S ( ( CONST char *, CONST char * ) ) ;


/*
    MACROS FOR ACCESSING MEMORY ALLOCATION ROUTINES

    These macros give a convenient method for accessing the routines above.
    For example, xmalloc_nof ( T, N ) allocates space for N objects of
    type T.
*/

#define xmalloc_nof( T, N )\
    ( ( T * ) xmalloc ( ( long ) ( N ) * ( long ) sizeof ( T ) ) )
#define xcalloc_nof( T, N )\
    ( ( T * ) xcalloc ( ( long ) ( N ), ( long ) sizeof ( T ) ) )
#define xrealloc_nof( P, T, N )\
    ( ( T * ) xrealloc ( ( gen_ptr ) ( P ),\
			 ( long ) ( N ) * ( long ) sizeof ( T ) ) )
#define xfree_nof( P )\
    xfree ( ( gen_ptr ) ( P ) )


#endif
