/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
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
