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
#include <limits.h>
#include "c_types.h"
#include "error.h"
#include "char.h"
#include "ustring.h"
#include "xalloc.h"


/*
    CONTROLLED VERSION OF MALLOC

    All the program's memory allocation is through the routines defined in
    this file.  This routine allocates sz bytes of memory.
*/

gen_ptr xmalloc
    PROTO_N ( ( sz ) )
    PROTO_T ( gen_size sz )
{
    gen_ptr p ;
    if ( sz == 0 ) sz = 1 ;
    p = malloc ( ( size_t ) sz ) ;
    if ( p == NULL ) {
	max_errors = ULONG_MAX ;
	error ( ERROR_INTERNAL, "Memory allocation error" ) ;
	term_error ( 1 ) ;
    }
    return ( p ) ;
}


/*
    CONTROLLED VERSION OF REALLOC

    This routine reallocates the block of memory p to contain sz bytes.
    p can be the result of a previous memory allocation routine, or NULL.
*/

gen_ptr xrealloc
    PROTO_N ( ( p, sz ) )
    PROTO_T ( gen_ptr p X gen_size sz )
{
    gen_ptr q ;
    if ( sz == 0 ) sz = 1 ;
    if ( p ) {
	q = realloc ( p, ( size_t ) sz ) ;
    } else {
	q = malloc ( ( size_t ) sz ) ;
    }
    if ( q == NULL ) {
	max_errors = ULONG_MAX ;
	error ( ERROR_INTERNAL, "Memory allocation error" ) ;
	term_error ( 1 ) ;
    }
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
    STRING ALLOCATION BUFFER

    This buffer is used in the allocation of small strings.
*/

static gen_size chars_left = 0 ;
static string chars_free = NULL ;


/*
    ALLOCATE SPACE FOR A STRING

    This routine allocates space for n characters.  The memory allocation
    is buffered except for very long strings.
*/

string xustr
    PROTO_N ( ( n ) )
    PROTO_T ( gen_size n )
{
    string r ;
    if ( n < 1000 ) {
	/* Small strings */
	if ( n >= chars_left ) {
	    chars_left = 5000 ;
	    chars_free = xmalloc_nof ( character, chars_left ) ;
	}
	r = chars_free ;
	chars_free += n ;
	chars_left -= n ;
    } else {
	/* Large strings */
	r = xmalloc_nof ( character, n ) ;
    }
    return ( r ) ;
}


/*
    FREE SPACE ALLOCATED FOR A STRING

    This routine frees the space allocated by a previous call to xustr.
    For small strings the memory is only freed for the last call to xustr.
*/

void xufree
    PROTO_N ( ( s, n ) )
    PROTO_T ( string s X gen_size n )
{
    if ( s ) {
	if ( n < 1000 ) {
	    /* Small strings */
	    if ( s + n == chars_free ) {
		chars_free = s ;
		chars_left += n ;
	    }
	} else {
	    /* Large strings */
	    xfree_nof ( s ) ;
	}
    }
    return ;
}


/*
    COPY A STRING OF A GIVEN LENGTH

    This routine allocates space for a persistent copy of the string s
    of length n.  There is only one copy of each small string, otherwise
    xustr is used to allocate the space.
*/

string xustrncpy
    PROTO_N ( ( s, n ) )
    PROTO_T ( string s X gen_size n )
{
    string r ;
    if ( n < 2 ) {
	/* Small strings */
	static character buff [ NO_CHAR ] [2] ;
	int c = ( int ) s [0] ;
	if ( c < NO_CHAR ) {
	    r = buff [c] ;
	    r [0] = ( character ) c ;
	    r [1] = 0 ;
	    return ( r ) ;
	}
    }
    /* Large strings */
    r = xustr ( n + 1 ) ;
    ustrcpy_v ( r, s ) ;
    return ( r ) ;
}


/*
    COPY A STRING

    This routine allocates space for a persistent copy of the string s.
*/

string xustrcpy
    PROTO_N ( ( s ) )
    PROTO_T ( string s )
{
    gen_size n ;
    if ( s == NULL ) return ( NULL ) ;
    n = ( gen_size ) ustrlen ( s ) ;
    return ( xustrncpy ( s, n ) ) ;
}


/*
    CONCATENATE TWO STRINGS

    This routine allocates space for a persistent copy of the string s
    followed by the string t.  The memory is allocated using xustr.
*/

string xustrcat
    PROTO_N ( ( s, t ) )
    PROTO_T ( string s X string t )
{
    string r ;
    gen_size n, m ;
    if ( s == NULL ) return ( xustrcpy ( t ) ) ;
    if ( t == NULL ) return ( xustrcpy ( s ) ) ;
    n = ( gen_size ) ustrlen ( s ) ;
    m = n + ( gen_size ) ustrlen ( t ) + 1 ;
    r = xustr ( m ) ;
    ustrcpy_v ( r, s ) ;
    ustrcpy_v ( r + n, t ) ;
    return ( r ) ;
}


/*
    COPY A NUMBER OF CHARACTERS

    This routine copies n characters from t to s.
*/

void xumemcpy
    PROTO_N ( ( s, t, n ) )
    PROTO_T ( string s X string t X gen_size n )
{
    if ( n ) memcpy_v ( ( gen_ptr ) s, ( gen_ptr ) t, ( size_t ) n ) ;
    return ;
}


/*
    COMPARE TWO SEQUENCES OF CHARACTERS

    This routine compares the n characters given by s and t.
*/

int xumemcmp
    PROTO_N ( ( s, t, n ) )
    PROTO_T ( string s X string t X gen_size n )
{
    if ( s == t || n == 0 ) return ( 0 ) ;
    return ( memcmp ( ( gen_ptr ) s, ( gen_ptr ) t, ( size_t ) n ) ) ;
}
