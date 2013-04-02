/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#include "implement.h"


/*
    SYSTEM ATEXIT FUNCTION

    The macro sys_atexit calls the system atexit function.  The macro
    FS_ATEXIT may be defined on machines where atexit is not defined.
*/

#ifndef FS_ATEXIT
#define FS_ATEXIT	0
#endif

#if ( FS_ATEXIT == 1 )
extern "C" int on_exit ( EXITER, char * ) ;
#define sys_atexit( X )	( on_exit ) ( X, NULL )
#else
#define sys_atexit( X )	( atexit ) ( X )
#endif


/*
    LIST OF TERMINATION FUNCTIONS

    This list represents all the termination functions which are to be
    called at the end of a program.
*/

DTOR_LIST *__TCPPLUS_dtors = 0 ;


/*
    CALL ALL TERMINATION FUNCTIONS

    This routine scans down the list of all termination functions calling
    each in turn.
*/

void __TCPPLUS_term ()
{
    DTOR_LIST *p = __TCPPLUS_dtors ;
    __TCPPLUS_dtors = 0 ;
    while ( p ) {
	CLASS *q = p->arg ;
	if ( q ) {
	    // Destructor call
	    p->func ( q, 2 ) ;
	} else {
	    // atexit function call
	    ( ( EXITER ) p->func ) () ;
	}
	p = p->next ;
    }
    return ;
}


/*
    INITIALISE TERMINATION FUNCTIONS

    This routine uses the system atexit to register the function
    __TCPPLUS_term as being called at the end of the program.
*/

void __TCPPLUS_init ()
{
    static int started = 0 ;
    if ( !started ) {
	sys_atexit ( __TCPPLUS_term ) ;
	started = 1 ;
    }
    return ;
}


/*
    REPLACEMENT ATEXIT FUNCTION

    This routine is a replacement for the system atexit function which
    works in conjunction with the destructor lists.
*/

int __TCPPLUS_atexit ( EXITER fn )
{
    DTOR_LIST *p = ( DTOR_LIST * ) malloc ( sizeof ( DTOR_LIST ) ) ;
    if ( p == NULL ) return ( -1 ) ;
    p->next = __TCPPLUS_dtors ;
    p->arg = NULL ;
    p->func = ( DESTRUCTOR ) fn ;
    __TCPPLUS_dtors = p ;
    __TCPPLUS_init () ;
    return ( 0 ) ;
}
