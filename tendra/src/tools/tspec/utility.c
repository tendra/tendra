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
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include "name.h"
#include "utility.h"

#ifdef FS_NO_MODE_T
typedef unsigned short mode_t ;
#endif

#ifndef errno
extern int errno ;
#endif


/*
    INPUT BUFFER

    This buffer is used to store strings in various contexts.
*/

char *buffer = null ;


/*
    ERROR VARIABLES

    The value exit_status gives the overall status of the program.  It
    can be EXIT_SUCCESS or EXIT_FAILURE.  The variable progname gives
    the name of the program, which is used in error reports.  filename
    and line_no give the current file position.
*/

int exit_status = EXIT_SUCCESS ;
int no_errors = 0 ;
int warnings = 1 ;
char *progname = "tspec" ;
char *progvers = "2.8" ;
time_t progdate = 0 ;
char *filename = null ;
int line_no = 1 ;


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
    boolean show_line = 1 ;
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
	case ERR_FATAL : {
	    exit_status = EXIT_FAILURE ;
	    errtype = "Fatal" ;
	    no_errors++ ;
	    break ;
	}
	case ERR_INTERNAL : {
	    exit_status = EXIT_FAILURE ;
	    errtype = "Internal" ;
	    no_errors++ ;
	    break ;
	}
	case ERR_SERIOUS : {
	    exit_status = EXIT_FAILURE ;
	    errtype = "Error" ;
	    no_errors++ ;
	    break ;
	}
	case ERR_WARNING : {
	    if ( !warnings ) {
		va_end ( args ) ;
		return ;
	    }
	    errtype = "Warning" ;
	    break ;
	}
	case ERR_INFO : {
	    errtype = "Info" ;
	    show_line = 0 ;
	    break ;
	}
    }
    if ( progname ) IGNORE fprintf ( stderr, "%s: ", progname ) ;
    if ( errtype ) IGNORE fprintf ( stderr, "%s: ", errtype ) ;
    IGNORE vfprintf ( stderr, s, args ) ;
    if ( filename && show_line ) {
	IGNORE fprintf ( stderr, ", %s, line %d", filename, line_no ) ;
    }
    IGNORE fprintf ( stderr, ".\n" ) ;
    va_end ( args ) ;
    if ( e == ERR_FATAL ) exit ( exit_status ) ;
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
    if ( p == null ) error ( ERR_FATAL, "Memory allocation error" ) ;
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
    if ( q == null ) error ( ERR_FATAL, "Memory reallocation error" ) ;
    return ( q ) ;
}


/*
    ALLOCATE SPACE FOR A STRING

    This routine allocates space for a string of size n.
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
	    no_free = 1000 ;
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
    CONCATENCATE TWO STRINGS

    This routine allocates space for the concatenation of the strings
    s and t.
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
    CONSTRUCT A STRING

    This routine takes a printf string and a list of arguments, and
    does a sprintf into a permanent area of memory.
*/

char *string_printf
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
    IGNORE vsprintf ( buffer, s, args ) ;
    va_end ( args ) ;
    return ( string_copy ( buffer ) ) ;
}


/*
    MODE OF DIRECTORIES CREATED

    The mode of any created directories is determined.  On a truly POSIX
    compliant machine, the first branch is taken.
*/

#if defined ( S_IRWXU ) && defined ( S_IRWXG ) && defined ( S_IRWXO )
#define  DIRMODE	( S_IRWXU | S_IRWXG | S_IRWXO )
#else
#if defined ( S_IREAD ) && defined ( S_IWRITE ) && defined ( S_IEXEC )
#define  DIRMODE	( S_IREAD | S_IWRITE | S_IEXEC )
#else
#define  DIRMODE	0777
#endif
#endif


/*
    CREATE A DIRECTORY TO PUT A FILE IN

    This routine recursively creates a directory to contain a file
    named nm.
*/

void create_dir
    PROTO_N ( ( nm ) )
    PROTO_T ( char *nm )
{
    struct stat st ;
    char *dir = dirname ( nm ) ;
    if ( dir == null ) return ;
    if ( stat ( dir, &st ) == 0 ) return ;
#ifdef ENOENT
    if ( errno != ENOENT ) {
	error ( ERR_SERIOUS, "Illegal directory, %s", dir ) ;
	return ;
    }
#endif
    create_dir ( dir ) ;
    if ( verbose ) error ( ERR_INFO, "Creating directory, %s ...", dir ) ;
    if ( mkdir ( dir, ( mode_t ) DIRMODE ) ) {
	error ( ERR_SERIOUS, "Can't create directory, %s", dir ) ;
	return ;
    }
    return ;
}


/*
    CHECK A FILENAME

    This routine checks the file name nm for excessively long components,
    which may cause problems on some machines.
*/

void check_name
    PROTO_N ( ( nm ) )
    PROTO_T ( char *nm )
{
    char *p ;
    int i = 0, n = 0 ;
    for ( p = nm ; *p ; p++ ) {
	if ( *p == '/' ) {
	    if ( i > n ) n = i ;
	    i = 0 ;
	} else {
	    i++ ;
	}
    }
    if ( i > n ) n = i ;
    if ( n > 14 ) {
	char *err = "The filename %s contains a component of length %d" ;
	error ( ERR_WARNING, err, nm, n ) ;
    }
    return ;
}


/*
    FIND THE DATE STAMP ON A FILE

    This routine finds the modification time of the file nm.  Zero is
    returned for inaccessible files.
*/

time_t date_stamp
    PROTO_N ( ( nm ) )
    PROTO_T ( char *nm )
{
    struct stat st ;
    if ( nm && stat ( nm, &st ) == 0 ) return ( st.st_mtime ) ;
    return ( ( time_t ) 0 ) ;
}
