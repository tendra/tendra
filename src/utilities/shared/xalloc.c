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
#include "error.h"
#include "xalloc.h"


/*
    CONTROLLED VERSION OF MALLOC

    All the program's memory allocation is through the routines defined in
    this file.  This routine allocates sz bytes of memory.
*/

gen_ptr xmalloc
    PROTO_N ( ( sz ) )
    PROTO_T ( long sz )
{
    gen_ptr p = malloc ( ( size_t ) sz ) ;
    if ( p == NULL ) error ( ERROR_FATAL, "Memory allocation error" ) ;
    return ( p ) ;
}


/*
    CONTROLLED VERSION OF CALLOC

    This routine allocates and initializes n objects of size sz bytes.
*/

gen_ptr xcalloc
    PROTO_N ( ( n, sz ) )
    PROTO_T ( long n X long sz )
{
    gen_ptr p = calloc ( ( size_t ) sz, ( size_t ) n ) ;
    if ( p == NULL ) error ( ERROR_FATAL, "Memory allocation error" ) ;
    return ( p ) ;
}


/*
    CONTROLLED VERSION OF REALLOC

    This routine reallocates the block of memory p to contain sz bytes.
    p can be the result of a previous memory allocation routine, or NULL.
*/

gen_ptr xrealloc
    PROTO_N ( ( p, sz ) )
    PROTO_T ( gen_ptr p X long sz )
{
    gen_ptr q ;
    if ( p ) {
	q = realloc ( p, ( size_t ) sz ) ;
    } else {
	q = malloc ( ( size_t ) sz ) ;
    }
    if ( q == NULL ) error ( ERROR_FATAL, "Memory allocation error" ) ;
    return ( q ) ;
}


/*
    CONTROLLED VERSION OF FREE

    This routine frees the block of memory p.  p can be the result of a
    previous memory allocation routine, or NULL.
*/

void xfree
    PROTO_N ( ( p ) )
    PROTO_T ( gen_ptr p )
{
    if ( p ) free ( p ) ;
    return ;
}


/*
    ALLOCATE SPACE FOR A STRING

    This routine allocates space for n characters.  The memory allocation
    is buffered except for very long strings.
*/

char *xstr
    PROTO_N ( ( n ) )
    PROTO_T ( long n )
{
    char *r ;
    if ( n >= 1000 ) {
	r = xmalloc_nof ( char, n ) ;
    } else {
	static long chars_left = 0 ;
	static char *chars_free = 0 ;
	if ( n >= chars_left ) {
	    chars_left = 5000 ;
	    chars_free = xmalloc_nof ( char, chars_left ) ;
	}
	r = chars_free ;
	chars_free += n ;
	chars_left -= n ;
    }
    return ( r ) ;
}


/*
    COPY A STRING

    This routine allocates space for a persistent copy of the string s.
*/

char *xstrcpy
    PROTO_N ( ( s ) )
    PROTO_T ( CONST char *s )
{
    long n ;
    char *r ;
    if ( s == NULL ) return ( NULL ) ;
    n = ( long ) strlen ( s ) + 1 ;
    r = xstr ( n ) ;
    strcpy_v ( r, s ) ;
    return ( r ) ;
}


/*
    CONCATENATE TWO STRINGS

    This routine allocates space for a persistent copy of the string s
    followed by the string t.
*/

char *xstrcat
    PROTO_N ( ( s, t ) )
    PROTO_T ( CONST char *s X CONST char *t )
{
    char *r ;
    long n, m ;
    if ( s == NULL ) return ( xstrcpy ( t ) ) ;
    if ( t == NULL ) return ( xstrcpy ( s ) ) ;
    n = ( long ) strlen ( s ) ;
    m = n + ( long ) strlen ( t ) + 1 ;
    r = xstr ( m ) ;
    strcpy_v ( r, s ) ;
    strcpy_v ( r + n, t ) ;
    return ( r ) ;
}
