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


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:57:25 $
$Revision: 1.1.1.1 $
$Log: util.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:25  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.2  1994/07/21  10:36:44  currie
 * Added banner
 *
***********************************************************************/

#include "config.h"
#include "errors.h"
#include "util.h"


char *copy_string
    PROTO_N ( ( s ) )
    PROTO_T ( char *s )
{
    unsigned i ;
    unsigned ls = ( unsigned ) strlen ( s ) ;
    char *res = CALLOC ( char, ls + 1 ) ;
    for ( i = 0 ; i < ls ; i++ ) res [i] = s [i] ;
    res [ ls ] = 0 ;
    return ( res ) ;
}

char *append_string
    PROTO_N ( ( a, b ) )
    PROTO_T ( char *a X char *b )
{
    unsigned i;
    unsigned la = ( unsigned ) strlen ( a ) ;
    unsigned lb = ( unsigned ) strlen ( b ) ;
    char *res = CALLOC ( char, la + lb + 1 ) ;
    for ( i = 0 ; i < la ; i++ ) res [i] = a [i] ;
    for ( i = 0 ; i < lb ; i++ ) res [ i + la ] = b [i] ;
    res [ la + lb ] = 0 ;
    return ( res ) ;
}

Pointer xmalloc
    PROTO_N ( ( n ) )
    PROTO_T ( unsigned n )
{
    Pointer p = ( Pointer ) malloc ( ( size_t ) n ) ;
    if ( p == NULL ) fail ( "Memory allocation error" ) ;
    return ( p ) ;
}

Pointer xcalloc
    PROTO_N ( ( n, m ) )
    PROTO_T ( unsigned n X unsigned m )
{
    Pointer p = ( Pointer ) calloc ( ( size_t ) n, ( size_t ) m ) ;
    if ( p == NULL ) fail ( "Memory allocation error" ) ;
    return ( p ) ;
}
