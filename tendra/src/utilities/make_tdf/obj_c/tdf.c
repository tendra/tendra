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


#include "config.h"
#include "tdf.h"
#include "error.h"
#include "xalloc.h"


/*
    FREE OBJECTS

    These variables indicate the free tdf.  There is an array containing
    lists of small blocks, plus a single larger block.
*/

#define free_tdf_max	16
static tdf *free_tdf = NULL ;
static unsigned free_tdf_left = 0 ;
static tdf *free_tdf_array [ free_tdf_max ] = {
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
} ;


/*
    GENERATE A NEW OBJECT BLOCK

    This routine generates a new blcok of tdf of size sz.  Small blocks
    are allocated from the tdf array, others from the main tdf list.
*/

tdf *gen_tdf
    PROTO_N ( ( sz ) )
    PROTO_T ( unsigned sz )
{
    tdf *p ;
    unsigned n = sz ;

    if ( n < free_tdf_max ) {
	/* Allocate from small block array */
	p = free_tdf_array [n] ;
	if ( p ) {
	    free_tdf_array [n] = TAIL_list ( p ) ;
	    return ( p ) ;
	}
    }

    /* Allocate from large block */
    if ( n > free_tdf_left ) {
	free_tdf_left = 1000 ;
	free_tdf = xmalloc_nof ( tdf, free_tdf_left ) ;
    }
    p = free_tdf ;
    free_tdf += sz ;
    free_tdf_left -= sz ;
    return ( p ) ;
}


/*
    DESTROY AN OBJECT BLOCK

    This routine destroys the block of tdf p of size sz.  Only small
    blocks are recycled.
*/

void destroy_tdf
    PROTO_N ( ( p, sz ) )
    PROTO_T ( tdf *p X unsigned sz )
{
    unsigned n = sz ;
    if ( p && n < free_tdf_max ) {
	TAIL_list ( p ) = free_tdf_array [n] ;
	free_tdf_array [n] = p ;
    }
    return ;
}


/*
    DUMMY OBJECT BLOCK DESTRUCTOR

    This routine is a dummy destructor which does nothing.
*/

void dummy_destroy_tdf
    PROTO_N ( ( p, sz ) )
    PROTO_T ( tdf *p X unsigned sz )
{
    UNUSED ( p ) ;
    UNUSED ( sz ) ;
    return ;
}


/*
    DESTROY A LIST OF OBJECT BLOCKS

    This routine destroys the list p of blocks of tdf of size sz.  The
    list is added to the appropriate entry of the free tdf array.
*/

void destroy_tdf_list
    PROTO_N ( ( p, sz ) )
    PROTO_T ( tdf *p X unsigned sz )
{
    unsigned n = sz + 1 ;
    if ( p && n < free_tdf_max ) {
	tdf *q = p ;
	while ( TAIL_list ( p ) ) p = TAIL_list ( p ) ;
	TAIL_list ( p ) = free_tdf_array [n] ;
	free_tdf_array [n] = q ;
    }
    return ;
}


/*
    FIND THE LENGTH OF A LIST

    This routine calculates the length of the list p.
*/

unsigned length_tdf_list
    PROTO_N ( ( p ) )
    PROTO_T ( tdf *p )
{
    tdf *q ;
    unsigned n = 0 ;
    for ( q = p ; q != NULL ; q = TAIL_list ( q ) ) n++ ;
    return ( n ) ;
}


/*
    REVERSE A LIST

    This routine reverses the order of the list p.
*/

tdf *reverse_tdf_list
    PROTO_N ( ( p ) )
    PROTO_T ( tdf *p )
{
    tdf *r = NULL ;
    tdf *q = p ;
    while ( q != NULL ) {
	tdf *nq = TAIL_list ( q ) ;
	TAIL_list ( q ) = r ;
	r = q ;
	q = nq ;
    }
    return ( r ) ;
}


/*
    APPEND TWO LISTS

    This routine appends the lists of tdf blocks p and q.
*/

tdf *append_tdf_list
    PROTO_N ( ( p, q ) )
    PROTO_T ( tdf *p X tdf *q )
{
    tdf *r = p ;
    if ( r == NULL ) return ( q ) ;
    while ( TAIL_list ( r ) ) r = TAIL_list ( r ) ;
    TAIL_list ( r ) = q ;
    return ( p ) ;
}


/*
    FIND THE LAST MEMBER OF A LIST

    This routine returns the last member of the list of tdf blocks p.
*/

tdf *end_tdf_list
    PROTO_N ( ( p ) )
    PROTO_T ( tdf *p )
{
    tdf *r = p ;
    if ( r == NULL ) return ( NULL ) ;
    while ( TAIL_list ( r ) ) r = TAIL_list ( r ) ;
    return ( r ) ;
}


/*
    ASSERTION ROUTINES

    These routine implement the assertion checks.
*/

#ifdef ASSERTS
#define assert_calculus assertion
#include "assert_def.h"
#endif
