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
#include "read_types.h"
#include "analyser.h"
#include "fetch.h"
#include "file.h"
#include "table.h"
#include "utility.h"
#include "write.h"
extern char *progname ;
extern char *capname ;
extern int decode_status ;
extern int have_version ;


/*
    ARE INPUT AND OUTPUT TEXT OR CODE?

    The form of any error message depends on whether the input file
    is text or code.
*/

boolean text_input = 1 ;
boolean text_output = 0 ;


/*
    EXIT STATUS

    The overall exit status of the program.
*/

int exit_status = EXIT_SUCCESS ;


/*
    REPORT A FATAL ERROR

    The error s is reported and the program exits.
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
    IS AN INPUT ERROR FATAL?

    Not all input errors cause an immediate exit.  These should set
    is_fatal to false before calling input_error.
*/

boolean is_fatal = 1 ;


/*
    REPORT AN INPUT ERROR

    The input error s is reported and the program exits.
*/

void input_error
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
    if ( input_file ) {
	IGNORE fprintf ( stderr, ", %s", input_file ) ;
	if ( text_input ) {
	    IGNORE fprintf ( stderr, ", line %ld", line_no ) ;
	} else {
	    long b = input_posn () ;
	    if ( capname ) {
		IGNORE fprintf ( stderr, ", capsule %s", capname ) ;
	    }
	    switch ( decode_status ) {
		case 0 : {
		    IGNORE fprintf ( stderr, " (at outermost level)" ) ;
		    break ;
		}
		case 1 : {
		    IGNORE fprintf ( stderr, " (in linking information)" ) ;
		    break ;
		}
		case 2 : {
		    IGNORE fprintf ( stderr, " (in unit body)" ) ;
		    break ;
		}
	    }
	    IGNORE fprintf ( stderr, ", byte %ld, bit %ld", b / 8, b % 8 ) ;
	    if ( decode_status == 0 ) {
		IGNORE fprintf ( stderr, " (Illegal TDF capsule?)" ) ;
	    }
	    if ( decode_status >= 1 && !have_version ) {
		IGNORE fprintf ( stderr, " (TDF version error?)" ) ;
	    }
	}
    }
    IGNORE fprintf ( stderr, ".\n" ) ;
    va_end ( args ) ;
    if ( is_fatal ) {
	if ( text_output ) {
	    sort_all () ;
	    print_capsule () ;
	    IGNORE fputs ( "# TERMINATED ON INPUT ERROR\n", output ) ;
	}
	exit ( EXIT_FAILURE ) ;
    }
    is_fatal = 1 ;
    exit_status = EXIT_FAILURE ;
    return ;
}


/*
    ISSUE A WARNING

    The warning message s is printed.
*/

void warning
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
    IGNORE fprintf ( stderr, "Warning: " ) ;
    IGNORE vfprintf ( stderr, s, args ) ;
    IGNORE fprintf ( stderr, ".\n" ) ;
    va_end ( args ) ;
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
    pointer ptr ;
    if ( n == 0 ) return ( null ) ;
    ptr = ( pointer ) malloc ( ( size_t ) n ) ;
    if ( ptr == null ) {
	if ( !text_input && decode_status == 0 ) {
	    fatal_error ( "Memory allocation error (Illegal TDF capsule?)" ) ;
	}
	fatal_error ( "Memory allocation error" ) ;
    }
    return ( ptr ) ;
}


/*
    REALLOCATE A SECTION OF MEMORY

    This routine reallocates n bytes of memory for the pointer p.
*/

pointer xrealloc
    PROTO_N ( ( p, n ) )
    PROTO_T ( pointer p X int n )
{
    pointer ptr ;
    if ( n == 0 ) return ( null ) ;
    if ( p == null ) return ( xalloc ( n ) ) ;
    ptr = ( pointer ) realloc ( p, ( size_t ) n ) ;
    if ( ptr == null ) fatal_error ( "Memory allocation error" ) ;
    return ( ptr ) ;
}


/*
    MAKE A COPY OF A STRING

    This routine makes a permanent copy of the string s of length n.
*/

char *string_copy
    PROTO_N ( ( s, n ) )
    PROTO_T ( char *s X int n )
{
    int m = ( n + 1 ) * ( int ) sizeof ( char ) ;
    char *p = ( char * ) xalloc ( m ) ;
    IGNORE strncpy ( p, s, ( size_t ) n ) ;
    p [n] = 0 ;
    return ( p ) ;
}


/*
    MAKE A TEMPORARY COPY OF A STRING

    This routine copies a string into a temporary buffer.
*/

char *temp_copy
    PROTO_N ( ( s ) )
    PROTO_T ( char *s )
{
    static char *buff = null ;
    static int bufflen = 0 ;
    int n = ( int ) strlen ( s ) + 1 ;
    if ( n >= bufflen ) {
	bufflen = n + 100 ;
	buff = ( char * ) xrealloc ( ( pointer ) buff, bufflen ) ;
    }
    IGNORE strcpy ( buff, s ) ;
    return ( buff ) ;
}


/*
    CONVERT AN UNSIGNED LONG TO OCTAL

    The result is returned as a string of octal digits.
*/

char *ulong_to_octal
    PROTO_N ( ( n ) )
    PROTO_T ( unsigned long n )
{
    int i = 99 ;
    char buff [100] ;
    if ( n == 0 ) return ( "0" ) ;
    buff [i] = 0 ;
    while ( n ) {
	buff [ --i ] = ( char ) ( '0' + ( n & 7 ) ) ;
	n >>= 3 ;
    }
    return ( string_copy ( buff + i, 99 - i ) ) ;
}


/*
    CONVERT AN OCTAL STRING TO AN UNSIGNED LONG

    Any overflow is ignored (but see below).
*/

unsigned long octal_to_ulong
    PROTO_N ( ( num ) )
    PROTO_T ( char *num )
{
    unsigned long n = 0 ;
    for ( ; *num ; num++ ) {
	n = ( n << 3 ) + ( unsigned long ) ( *num - '0' ) ;
    }
    return ( n ) ;
}


/*
    DOES THE GIVEN OCTAL STRING FIT INTO AN UNSIGNED LONG?

    The number of binary digits needed to represent the octal number
    is calculated and compared against the number of bits in an
    unsigned long, minus sz (to allow for a sign bit).
*/

boolean fits_ulong
    PROTO_N ( ( num, sz ) )
    PROTO_T ( char *num X int sz )
{
    int n = 3 * ( int ) strlen ( num ) ;
    int m = BYTESIZE * ( int ) sizeof ( unsigned long ) - sz ;
    switch ( *num ) {
	case '0' : n -= 3 ; break ;
	case '1' : n -= 2 ; break ;
	case '2' : n -= 1 ; break ;
	case '3' : n -= 1 ; break ;
    }
    if ( n <= m ) return ( 1 ) ;
    return ( 0 ) ;
}
