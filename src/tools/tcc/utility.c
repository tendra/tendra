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
#include "list.h"
#include "flags.h"
#include "main.h"
#include "suffix.h"
#include "utility.h"


/*
    ERROR VARIABLES

    The value exit_status gives the overall status of the program.  It
    can be EXIT_SUCCESS or EXIT_FAILURE.  The variable progname gives
    the name of the program, which is used in error reports.
*/

int exit_status = EXIT_SUCCESS ;
char *progname = PROGNAME_TCC ;


/*
    PRINT AN ERROR MESSAGE

    This routine prints an error message s (a printf-style string,
    which may be followed by any number of arguments) of severity e
    (see utility.h).
*/

void error
    PROTO_V ( ( int e, char *s, ... ) ) /* VARARGS */
{
    va_list args ;
    char *errtype = null ;
#if FS_STDARG
    va_start ( args, s ) ;
#else
    int e ;
    char *s ;
    va_start ( args ) ;
    e = va_arg ( args, int ) ;
    s = va_arg ( args, char * ) ;
#endif
    switch ( e ) {
	case FATAL : {
	    exit_status = EXIT_FAILURE ;
	    errtype = "Fatal" ;
	    break ;
	}
	case INTERNAL : {
	    exit_status = EXIT_FAILURE ;
	    errtype = "Internal" ;
	    break ;
	}
	case SERIOUS : {
	    exit_status = EXIT_FAILURE ;
	    errtype = "Error" ;
	    break ;
	}
	case OPTION : {
	    exit_status = EXIT_FAILURE ;
	    errtype = "Option interpreter" ;
	    break ;
	}
	case WARNING : {
	    if ( !warnings ) {
		va_end ( args ) ;
		return ;
	    }
	    errtype = "Warning" ;
	    break ;
	}
	case INFO : {
	    errtype = "Information" ;
	    break ;
	}
    }
    if ( checker ) progname = PROGNAME_TCHK ;
    IGNORE fprintf ( stderr, "%s: ", progname ) ;
    if ( errtype ) IGNORE fprintf ( stderr, "%s: ", errtype ) ;
    IGNORE vfprintf ( stderr, s, args ) ;
    IGNORE fprintf ( stderr, ".\n" ) ;
    va_end ( args ) ;
    if ( e == FATAL ) main_end () ;
    return ;
}


/*
    PRINT A COMMENT

    This routine prints the comment s (a printf-style string, which
    may be followed by any number of arguments) to the standard output.
*/

void comment
    PROTO_V ( ( int e, char *s, ... ) ) /* VARARGS */
{
    FILE *f ;
    va_list args ;
#if FS_STDARG
    va_start ( args, s ) ;
#else
    int e ;
    char *s ;
    va_start ( args ) ;
    e = va_arg ( args, int ) ;
    s = va_arg ( args, char * ) ;
#endif
    f = ( e ? stdout : stderr ) ;
    IGNORE fflush ( f ) ;
    IGNORE vfprintf ( f, s, args ) ;
    IGNORE fflush ( f ) ;
    va_end ( args ) ;
    return ;
}


/*
    ALLOCATE A BLOCK OF MEMORY

    This routine allocates a block of memory of size sz and returns
    the result.
*/

pointer xalloc
    PROTO_N ( ( sz ) )
    PROTO_T ( int sz )
{
    pointer p = ( pointer ) malloc ( ( size_t ) sz ) ;
    if ( p == null ) error ( FATAL, "Memory allocation error" ) ;
    return ( p ) ;
}


/*
    REALLOCATE A BLOCK OF MEMORY

    This routine reallocates the block of memory p to have size sz.
    xrealloc ( null, sz ) is equivalent to xalloc ( sz ).

*/

pointer xrealloc
    PROTO_N ( ( p, sz ) )
    PROTO_T ( pointer p X int sz )
{
    pointer q ;
    if ( p == null ) return ( xalloc ( sz ) ) ;
    q = ( pointer ) realloc ( p, ( size_t ) sz ) ;
    if ( q == null ) error ( FATAL, "Memory reallocation error" ) ;
    return ( q ) ;
}


/*
    ALLOCATE SPACE FOR A STRING

    This routine allocates n characters of memory for use in the string
    memory allocation routines.
*/

static char *string_alloc
    PROTO_N ( ( n ) )
    PROTO_T ( int n )
{
    char *r ;
    if ( n >= 1000 ) {
	/* Long strings are allocated space by alloc_nof */
	r = alloc_nof ( char, n ) ;
    } else {
	/* Short strings are allocated space from a buffer */
	static int no_free = 0 ;
	static char *free_chars = null ;
	if ( n >= no_free ) {
	    no_free = 4000 ;
	    free_chars = alloc_nof ( char, no_free ) ;
	}
	r = free_chars ;
	no_free -= n ;
	free_chars += n ;
    }
    return ( r ) ;
}


/*
    COPY A STRING

    This routine allocates space for a copy of the string s and copies
    the string into this space.  This copy is returned.
*/

char *string_copy
    PROTO_N ( ( s ) )
    PROTO_T ( char *s )
{
    int n = ( int ) strlen ( s ) ;
    char *r = string_alloc ( n + 1 ) ;
    IGNORE strcpy ( r, s ) ;
    return ( r ) ;
}


/*
    COPY TWO STRINGS

    This routine allocates space for a copy of the string s followed by
    a copy of the string t and concatenates the strings into this space.
    This copy is returned.
*/

char *string_concat
    PROTO_N ( ( s, t ) )
    PROTO_T ( char *s X char *t )
{
    int n = ( int ) strlen ( s ) ;
    int m = ( int ) strlen ( t ) ;
    char *r = string_alloc ( n + m + 1 ) ;
    IGNORE strcpy ( r, s ) ;
    IGNORE strcpy ( r + n, t ) ;
    return ( r ) ;
}


/*
    TEMPORARY WORK SPACE

    This variable gives a temporary work space of size buffer_size
    (see utility.h) which is used as a scratch work area.
*/

char *buffer ;
