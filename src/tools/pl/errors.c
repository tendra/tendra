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
$Date: 1998/01/17 15:57:24 $
$Revision: 1.1.1.1 $
$Log: errors.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:24  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.3  1994/12/05  10:12:57  currie
 * Extended size of input buffer
 *
 * Revision 1.2  1994/07/21  10:35:59  currie
 * Added banner
 *
***********************************************************************/
#include "config.h"
#if FS_STDARG
#include <stdarg.h>
#else
#include <varargs.h>
#endif
#include "util.h"
#include "streams.h"
#include "errors.h"
#include "defs.h"


void fail
    PROTO_V ( ( char *s, ... ) )
    /*VARARGS*/
{
    char c ;
    va_list args ;
    FILE *f = stderr ;
#if FS_STDARG
    va_start ( args, s ) ;
#else
    char *s ;
    va_start ( args ) ;
    s = va_arg ( args, char * ) ;
#endif
    IGNORE fprintf ( f, "Error: " ) ;
    IGNORE vfprintf ( f, s, args ) ;
    c = buff [ bind ] ;
    buff [ bind ] = 0 ;
    IGNORE fprintf ( f, ", %s, line %ld.\n", file_name, cLINE ) ;
    IGNORE fprintf ( f, "    %s!!!!", buff ) ;
    buff [ bind ] = c ;
    IGNORE fprintf ( f, "%s\n", buff + bind ) ;
    va_end ( args ) ;
    exit ( EXIT_FAILURE ) ;
}

void assert_sort
    PROTO_N ( ( x ) )
    PROTO_T ( unsigned x )
{
    unsigned y = current_TDF->sort ;
    if ( y != x ) {
	fail ( "Sort error: req = %u, curr = %u", x, y ) ;
    }
    return ;
}


void assert_sort_or_empty
    PROTO_N ( ( x ) )
    PROTO_T ( unsigned x )
{
    unsigned y = current_TDF->sort ;
    if ( current_TDF->no != 0 && y != x ) {
	fail ( "Sort/list error: req = %u, curr = %u", x, y ) ;
    }
    return ;
}
