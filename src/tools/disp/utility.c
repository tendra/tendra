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
#if FS_STDARG
#include <stdarg.h>
#else
#include <varargs.h>
#endif
#include "types.h"
#include "file.h"
#include "pretty.h"
#include "utility.h"


/*
    PROGRAM NAME

    The program name is output in all error reports.
*/

char *progname = "disp" ;


/*
    EXIT STATUS

    This flag is set to 1 whenever an error occurs.  It is the value
    with which the program finally exits.
*/

int exit_status = EXIT_SUCCESS ;


/*
    RECOVERY FLAG

    This flag controls whether an attempt is made to recover from
    non-fatal errors.  Anything after an error is likely to be of very
    little use.
*/

int recover = 0 ;


/*
    REPORT A FATAL ERROR

    An error is reported and the program aborts immediately.
*/

void fatal_error
    PROTO_V ( ( char *s, ... ) ) /* VARARGS */
{
    va_list args ;
#if FS_STDARG
    va_start ( args, s ) ;
#else
    char *s ;
    va_start ( args ) ;
    s = va_arg ( args, char * ) ;
#endif
    if ( progname ) IGNORE fprintf ( stderr, "%s: ", progname ) ;
    IGNORE fprintf ( stderr, "Error: " ) ;
    IGNORE vfprintf ( stderr, s, args ) ;
    IGNORE fprintf ( stderr, ".\n" ) ;
    va_end ( args ) ;
    exit ( EXIT_FAILURE ) ;
}


/*
    REPORT AN INPUT ERROR

    An error is reported together with the position within the input
    file where it occured, and the program either attempts to recover
    (if the recover flag is true) or outputs what it has read so far
    and then exits (otherwise).
*/

void input_error
    PROTO_V ( ( char *s, ... ) ) /* VARARGS */
{
    va_list args ;
    long b = here.byte ;
#if FS_STDARG
    va_start ( args, s ) ;
#else
    char *s ;
    va_start ( args ) ;
    s = va_arg ( args, char * ) ;
#endif
    if ( progname ) IGNORE fprintf ( stderr, "%s: ", progname ) ;
    IGNORE fprintf ( stderr, "Error: " ) ;
    IGNORE vfprintf ( stderr, s, args ) ;
    IGNORE fprintf ( stderr, ", byte %ld, bit %d.\n", b, here.bit ) ;
    va_end ( args ) ;
    exit_status = EXIT_FAILURE ;
    if ( !recover ) {
	pretty_tree () ;
	exit ( EXIT_FAILURE ) ;
    }
    return ;
}


/*
    ALLOCATE A SECTION OF MEMORY

    This routine allocates n bytes of memory.
*/

pointer xalloc
    PROTO_N ( ( n ) )
    PROTO_T ( int n )
{
    pointer ptr = ( pointer ) malloc ( ( size_t ) n ) ;
    if ( ptr == null ) fatal_error ( "Memory allocation error" ) ;
    return ( ptr ) ;
}


/*
    REALLOCATE A SECTION OF MEMORY

    This routine reallocates n bytes of memory.
*/

pointer xrealloc
    PROTO_N ( ( p, n ) )
    PROTO_T ( pointer p X int n )
{
    pointer ptr ;
    if ( p == null ) return ( xalloc ( n ) ) ;
    ptr = ( pointer ) realloc ( p, ( size_t ) n ) ;
    if ( ptr == null ) fatal_error ( "Memory allocation error" ) ;
    return ( ptr ) ;
}
