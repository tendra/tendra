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


#include "implement.h"


/*
    DEFAULT NEW HANDLER

    The default new handler throws a bad_alloc exception.
*/

static void default_new_handler ()
{
    throw bad_alloc () ;
}


/*
    CURRENT NEW HANDLER

    This value gives the current new handler function.
*/

static new_handler crt_new_handler = default_new_handler ;


/*
    SET CURRENT NEW HANDLER

    This routine sets the current new handler function to fn, returning
    the previous value.
*/

new_handler std::set_new_handler ( new_handler fn ) throw ()
{
    new_handler prev = crt_new_handler ;
    crt_new_handler = fn ;
    return ( prev ) ;
}


/*
    STANDARD MEMORY ALLOCATION FUNCTION

    This routine allocates sz bytes of memory, throwing an exception if
    this is not possible.
*/

void *__TCPPLUS_new ( size_t sz ) throw ( bad_alloc )
{
    void *p ;
    if ( sz == 0 ) sz = 1 ;
    while ( p = malloc ( sz ), p == NULL ) {
	new_handler fn = crt_new_handler ;
	if ( fn == NULL ) throw bad_alloc () ;
	fn () ;
    }
    return ( p ) ;
}


/*
    NO-EXCEPTION MEMORY ALLOCATION FUNCTION

    This routine allocates sz bytes of memory, returning a null pointer if
    this is not possible.
*/

void *__TCPPLUS_new_nothrow ( size_t sz ) throw ()
{
    void *p ;
    if ( sz == 0 ) sz = 1 ;
    while ( p = malloc ( sz ), p == NULL ) {
	try {
	    new_handler fn = crt_new_handler ;
	    if ( fn == NULL ) return ( NULL ) ;
	    fn () ;
	}
	catch ( const bad_alloc & ) {
	    // Return null if handler throws an exception
	    return ( NULL ) ;
	}
    }
    return ( p ) ;
}


/*
    STANDARD MEMORY DEALLOCATION FUNCTION

    This routine deallocates the memory given by p.
*/

void __TCPPLUS_delete ( void *p ) throw ()
{
    if ( p ) free ( p ) ;
    return ;
}


/*
    THE STANDARD NOTHROW OBJECT

    This object is used in the no-exception memory allocation routines.
*/

const nothrow_t std::nothrow = {} ;
