/*
    		 Crown Copyright (c) 1996

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
/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/utility.c,v 1.1.1.1 1998/01/17 15:55:49 release Exp $
--------------------------------------------------------------------------
$Log: utility.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
Revision 1.1.1.1  1997/10/13 12:43:00  ma
First version.

Revision 1.3  1997/10/13 08:50:16  ma
Made all pl_tests for general proc & exception handling pass.

Revision 1.2  1997/03/20 12:52:20  ma
Removed #if 0 and #endif around used definitions.

Revision 1.1.1.1  1997/03/14 07:50:19  ma
Imported from DRA

 * Revision 1.1.1.1  1996/09/20  10:56:59  john
 *
 * Revision 1.1.1.1  1996/03/26  15:45:18  john
 *
 * Revision 1.4  94/11/08  11:24:26  11:24:26  ra (Robert Andrews)
 * Changed error reporting format slightly.
 *
 * Revision 1.3  94/02/21  16:05:37  16:05:37  ra (Robert Andrews)
 * Clear up a long-int confusion.
 *
 * Revision 1.2  93/04/19  13:37:53  13:37:53  ra (Robert Andrews)
 * Line numbers in error reports were wrong.
 *
 * Revision 1.1  93/02/22  17:16:55  17:16:55  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#include "config.h"
#if FS_STDARG
#include <stdarg.h>
#else
#include <varargs.h>
#endif
#include "common_types.h"
#include "basicread.h"
#include "instrs.h"
#include "utility.h"
extern long crt_line_num ;
extern char *crt_fname ;
extern char *progname ;
long total_calloced ;
#if 0
/* Makes automatically generated makefile work */
#include "xalloc.c"
#endif


/*
    FIND THE BASENAME OF A FILE

    The string nm is analysed and a pointer to the character after the
    last '/' is returned.
*/

char *basename
    PROTO_N ( ( nm ) )
    PROTO_T ( char *nm )
{
    char *bn = nm ;
    for ( ; *nm ; nm++ ) if ( *nm == '/' ) bn = nm + 1 ;
    return ( bn ) ;
}


/*
    FIND THE FIRST NONZERO BIT

    This routine returns the bit number of the least significant set
    bit in n.  For 0 it returns -1.
*/

int bit_one
    PROTO_N ( ( n ) )
    PROTO_T ( bitpattern n )
{
    int c = 0 ;
    bitpattern m ;
    for ( m = n ; m ; m >>= 1, c++ ) if ( m & 1 ) return ( c ) ;
    return ( -1 ) ;
}


/*
    FIND THE NUMBER OF SET BITS

    The number of set bits in n is returned.
*/

int bits_in
    PROTO_N ( ( n ) )
    PROTO_T ( bitpattern n )
{
    /* Table of bits in : 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F */
    static int b [16] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4 } ;
    int c = 0 ;
    while ( n ) {
	c += b [ n & 0xf ] ;
	n >>= 4 ;
    }
    return ( c ) ;
}


/*
    BIT PATTERNS

    lo_bits [n] is the number with its bottom n bits set and the rest
    zero.  hi_bits [n] is the number with its top n bits set and the rest
    zero.
*/

bitpattern lo_bits [] = { 0,
    0x00000001, 0x00000003, 0x00000007, 0x0000000f,
    0x0000001f, 0x0000003f, 0x0000007f, 0x000000ff,
    0x000001ff, 0x000003ff, 0x000007ff, 0x00000fff,
    0x00001fff, 0x00003fff, 0x00007fff, 0x0000ffff,
    0x0001ffff, 0x0003ffff, 0x0007ffff, 0x000fffff,
    0x001fffff, 0x003fffff, 0x007fffff, 0x00ffffff,
    0x01ffffff, 0x03ffffff, 0x07ffffff, 0x0fffffff,
    0x1fffffff, 0x3fffffff, 0x7fffffff, 0xffffffff } ;

bitpattern hi_bits [] = { 0,
    0x80000000, 0xc0000000, 0xe0000000, 0xf0000000,
    0xf8000000, 0xfc000000, 0xfe000000, 0xff000000,
    0xff800000, 0xffc00000, 0xffe00000, 0xfff00000,
    0xfff80000, 0xfffc0000, 0xfffe0000, 0xffff0000,
    0xffff8000, 0xffffc000, 0xffffe000, 0xfffff000,
    0xfffff800, 0xfffffc00, 0xfffffe00, 0xffffff00,
    0xffffff80, 0xffffffc0, 0xffffffe0, 0xfffffff0,
    0xfffffff8, 0xfffffffc, 0xfffffffe, 0xffffffff } ;


/*
    NUMBER OF ERRORS

    errors is the number of errors which have occurred.  max_errors is
    the maximum number of errors that will be tolerated before exiting.
*/

int errors = 0 ;
#ifdef EBUG
int max_errors = 10 ;
#else
int max_errors = 1 ;
#endif


/*
    PRINT AN ERROR REPORT

    This routine prints the error report s together with any additional
    arguments.
*/

void error
    PROTO_V ( ( char *s, ... ) )
{
    char c ;
    char *p ;
    va_list args ;
#if FS_STDARG
    va_start ( args, s ) ;
    p = s ;
#else
    va_start ( args ) ;
    p = va_arg ( args, char * ) ;
#endif
    if ( progname ) fprintf ( stderr, "%s : ", progname ) ;
    fprintf ( stderr, "Error : " ) ;
    c = *p ;
    if ( c >= 'a' && c <= 'z' ) {
	c += ( 'A' - 'a' ) ;
	fputc ( c, stderr ) ;
	p++ ;
    }
    vfprintf ( stderr, p, args ) ;
    if ( crt_line_num != -1 && crt_fname ) {
	fprintf ( stderr, ", %s, line %ld", crt_fname, crt_line_num ) ;
    }
    fprintf ( stderr, ".\n" ) ;
    va_end ( args ) ;
#ifdef IGNORE_ERRORS
    return ;
#endif
    if ( max_errors == 0 ) exit ( EXIT_FAILURE ) ;
    if ( ++errors > max_errors ) {
	fprintf ( stderr, "%s : Too many errors.\n", progname ) ;
	exit ( EXIT_FAILURE ) ;
    }
    return ;
}

/*
    PRINT A SIMPLE ERROR

    This routine prints the simple error report s.
*/

void failer
    PROTO_N ( ( s ) )
    PROTO_T ( char *s )
{
    error ( s ) ;
    return ;
}


/*
    PRINT A WARNING

    This routine prints the warning message s together with any additional
    arguments.
*/

void warning
    PROTO_V ( ( char *s, ... ) )
{
    char c ;
    char *p ;
    va_list args ;
#if FS_STDARG
    va_start ( args, s ) ;
    p = s ;
#else
    va_start ( args ) ;
    p = va_arg ( args, char * ) ;
#endif
    if ( progname ) ( void ) fprintf ( stderr, "%s : ", progname ) ;
    fprintf ( stderr, "Warning : " ) ;
    c = *p ;
    if ( c >= 'a' && c <= 'z' ) {
	c += ( 'A' - 'a' ) ;
	fputc ( c, stderr ) ;
	p++ ;
    }
    ( void ) vfprintf ( stderr, p, args ) ;
    ( void ) fprintf ( stderr, ".\n" ) ;
    va_end ( args ) ;
    return ;
}


/*
    MEMORY HACK VALUE
*/

#define memhack 0

/*
    ALLOCATE A BLOCK OF MEMORY

    A pointer to a block of memory of size sz is returned.  Failure to
    allocate this memory gives an immediate fatal error.
*/

voidstar xmalloc
    PROTO_N ( ( sz ) )
    PROTO_T ( size_t sz )
{
    voidstar res ;
    if ( sz == 0 ) return ( null ) ;
    res = ( voidstar ) malloc ( sz + memhack ) ;
    if ( res == null ) {
	error ( "Can't allocate memory" ) ;
	exit ( EXIT_FAILURE ) ;
    }
#ifdef MEM_DEBUG
    printf ( "%d (malloc, %d bytes)\n", res, sz ) ;
    fflush ( stdout ) ;
#endif
    return ( res ) ;
}


/*
    ALLOCATE ROOM IN MEMORY

    A pointer to a block of memory of size n * sz is returned.  This
    memory is initialized to 0.  Failure to allocate memory gives an
    immediate fatal error.
*/

voidstar xcalloc
    PROTO_N ( ( n, sz ) )
    PROTO_T ( int n X size_t sz )
{
    voidstar res ;
    if ( n == 0 || sz == 0 ) return ( null ) ;
    if ( sz == sizeof ( char ) && n < 100 ) {
	/* Be careful not to free character arrays */
	static char *cbuffer = null ;
	static size_t cbuffsz = 0 ;
	if ( n + memhack >= cbuffsz ) {
	    cbuffsz = 2000 ;
	    cbuffer = ( char * ) calloc ( cbuffsz, sizeof ( char ) ) ;
	    if ( cbuffer == null ) {
		error ( "Can't allocate memory" ) ;
		exit ( EXIT_FAILURE ) ;
	    }
	}
	res = ( voidstar ) cbuffer ;
	cbuffer += ( n + memhack ) ;
	cbuffsz -= ( n + memhack ) ;
    } else {
	res = ( voidstar ) calloc ( n + memhack, sz ) ;
	if ( res == null ) {
	    error ( "Can't allocate memory" ) ;
	    exit ( EXIT_FAILURE ) ;
	}
    }
#ifdef MEM_DEBUG
    printf ( "%d (calloc, %d bytes)\n", res, n * sz ) ;
    fflush ( stdout ) ;
#endif
    return ( res ) ;
}


/*
    REALLOCATE A BLOCK OF MEMORY

    The previously allocated memory pointed to by p is reallocated
    to size n.  A pointer to the new block of memory is returned.
    Failure to allocate memory gives an immediate fatal error.
*/

voidstar xrealloc
    PROTO_N ( ( p, sz ) )
    PROTO_T ( voidstar p X size_t sz )
{
    voidstar res ;
    if ( p == null ) return ( xmalloc ( sz ) ) ;
    if ( sz == 0 ) return ( null ) ;
    res = ( voidstar ) realloc ( p, sz + memhack ) ;
    if ( res == null ) {
	error ( "Can't reallocate memory" ) ;
	exit ( EXIT_FAILURE ) ;
    }
#ifdef MEM_DEBUG
    printf ( "%d (realloc, %d bytes)\n", res, sz ) ;
    fflush ( stdout ) ;
#endif
    return ( res ) ;
}


/*
    FREE A BLOCK OF MEMORY

    The block of memory pointed to by p is returned to free.  p must
    previously have been allocated using one of the routines above.
*/

void xfree
    PROTO_N ( ( p ) )
    PROTO_T ( voidstar p )
{
    if ( p == null ) return ;
    free ( p ) ;
    return ;
}

