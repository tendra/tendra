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
$Date: 1998/02/06 17:05:20 $
$Revision: 1.2 $
$Log: main.c,v $
 * Revision 1.2  1998/02/06  17:05:20  release
 * Last minute pre-release polishing.
 *
 * Revision 1.1.1.1  1998/01/17  15:57:23  release
 * First version to be checked into rolling release.
 *
 * Revision 1.7  1995/09/05  16:27:51  currie
 * include files + 2r lex
 *
 * Revision 1.6  1995/09/04  10:30:42  currie
 * Update version
 *
 * Revision 1.5  1995/08/22  09:26:06  currie
 * stupid gcc!!
 *
 * Revision 1.4  1995/08/21  16:06:09  currie
 * build 4.2
 *
 * Revision 1.3  1995/08/15  16:21:41  currie
 * for build 4.1
 *
 * Revision 1.2  1995/06/08  09:13:53  currie
 * Added sigs to tokdecs/defs
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.3  1995/03/24  13:08:18  currie
 * Remore unary + in keeps2
 *
 * Revision 1.2  1994/07/21  10:36:25  currie
 * Added banner
 *
***********************************************************************/
#include "config.h"
#include "release.h"
#include "util.h"
#include "namedecs.h"
#include "lex.h"
#include "includes.h"
#include "syntax.h"
#include "units.h"

#ifndef RELEASE
#define RELEASE		"unknown"
#endif

static char *pl_version = "pl: Version 5.0 (TDF %lu.%lu, Release %s)\n" ;
static char *pl_usage = "pl [-v] [-Ipath] [-g] [-V] infile.pl outfile.j" ;

int main
    PROTO_N ( ( argc, argv ) )
    PROTO_T ( int argc X char **argv ) 
{
    int i ;
    int ok = 1 ;
    int diag = 0 ;
    char *in = NULL ;
    char *out = NULL ;
    init_includes () ;
    for ( i = 1 ; i < argc; i++ ) {
	char *a = argv [i] ;
	if ( a [0] == '-' ) {
	    switch ( a [1] ) {
		case 'g' : {
		    if ( a [2] ) ok = 0 ;
		    diag = 1 ;
		    break ;
		}
		case 'I' : {
		    add_include ( a + 2 ) ;
		    break ;
		}
		case 'v' : {
		    if ( a [2] ) ok = 0 ;
		    do_pp = 1 ;
		    break ;
		}
		case 'V' : {
		    char *vc = RELEASE ;
		    unsigned long va = MAJOR_NO ;
		    unsigned long vb = MINOR_NO ;
		    if ( a [2] ) ok = 0 ;
		    IGNORE fprintf ( stderr, pl_version, va, vb, vc ) ;
		    break ;
		}
		default : {
		    ok = 0 ;
		    break ;
		}
	    }
	} else {
	    if ( in == NULL ) {
		in = a ;
	    } else if ( out == NULL ) {
		out = a ;
	    } else {
		ok = 0 ;
	    }
	}
    }
    if ( in == NULL || out == NULL ) ok = 0 ;
    if ( !ok ) {
	IGNORE fprintf ( stderr, "Error: Usage = %s\n", pl_usage ) ;
	exit ( EXIT_FAILURE ) ;
    }
    in_file = fopen ( in, "r" ) ;
    file_name = in ;
    if ( in_file == NULL ) {
	IGNORE fprintf ( stderr, "Error: Can't open input file, %s.\n", in ) ;
	exit ( EXIT_FAILURE ) ;
    }
    out_file = fopen ( out, "wb" ) ;
    if ( out_file == NULL ) {
	IGNORE fprintf ( stderr, "Error: Can't open output file, %s.\n", out ) ;
	exit ( EXIT_FAILURE ) ;
    }
    lex_v = reader () ;
    init_units () ;
    if ( diag ) line_no_tok = next_capsule_name ( tok_ent ) ;
    read_program () ;
    IGNORE fclose ( in_file ) ;
    IGNORE fclose ( out_file ) ;
    return ( 0 ) ;
}
