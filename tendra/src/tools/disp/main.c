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
#include "release.h"
#include "types.h"
#include "ascii.h"
#include "basic.h"
#include "file.h"
#include "capsule.h"
#include "pretty.h"
#include "sort.h"
#include "tdf.h"
#include "tree.h"
#include "unit.h"
#include "utility.h"


/*
    CURRENT VERSION
*/

#define version_string		"Version: 1.5"


/*
    MAIN ROUTINE
*/

int main
    PROTO_N ( ( argc, argv ) )
    PROTO_T ( int argc X char **argv )
{
    char c ;
    int input, output ;
    int a, b, stage = 1 ;

    /* Read the arguments */
    for ( a = 1 ; a < argc ; a++ ) {
	if ( argv [a][0] == '-' ) {
	    b = 1 ;
	    if ( argv [a][1] == 'n' ) {
		maxcol = 0 ;
		while ( c = argv [a][ ++b ], is_digit ( c ) ) {
		    maxcol = 10 * maxcol + digit ( c ) ;
		}
	    } else {
		while ( c = argv [a][ b++ ], c != 0 ) {
		    switch ( c ) {
			case 'd' : dflag = 0 ; break ;
			case 'g' : diagnostics = 1 ; break ;
			case 'h' : helpflag = 0 ; break ;
			case 'i' : /* Compatibility */ break ;
			case 'p' : progress = 1 ; break ;
			case 'q' : quickflag = 1 ; break ;
			case 'r' : recover = 1 ; break ;
			case 'x' : versions = 0 ; break ;
			case 'A' : {
			    diagnostics = 1 ;
			    show_usage = 1 ;
			    versions = 1 ;
			    break ;
			}
			case 'D' : dump = 1 ; break ;
			case 'E' : show_stuff = 1 ; break ;
			case 'S' : skip_pass = 0 ; break ;
			case 'T' : show_skip = 1 ; break ;
			case 'U' : show_usage = 1 ; break ;
			case 'V' : dumb_mode = 1 ; break ;
			case 'W' : warn_undeclared = 1 ; break ;

			case 'v' : {
			    /* Version number */
			    IGNORE fprintf ( stderr, "%s: %s",
					     progname, version_string ) ;
			    IGNORE fprintf ( stderr, " (TDF %d.%d)",
					     version_major, version_minor ) ;
			    IGNORE fprintf ( stderr, " (release %s)\n",
					     RELEASE ) ;
			    break ;
			}
		    }
		}
	    }
	} else {
	    /* Handle files */
	    switch ( stage ) {
		case 1  : input = a ; stage = 2 ; break ;
		case 2  : output = a ; stage = 3 ; break ;
		default : stage = 4 ; break ;
	    }
	}
    }

    /* Open the files */
    switch ( stage ) {
	case 1 : {
	    fatal_error ( "Not enough arguments" ) ;
	    break ;
	}
	case 2 : {
	    SET ( input ) ;
	    open_files ( argv [ input ], ( char * ) null ) ;
	    break ;
	}
	case 3 : {
	    SET ( input ) ;
	    SET ( output ) ;
	    open_files ( argv [ input ], argv [ output ] ) ;
	    break ;
	}
	default : {
	    fatal_error ( "Too many arguments" ) ;
	    break ;
	}
    }

    /* Perform binary dump if required */
    if ( dump ) {
	long f ;
	int bits = 0, n = 1 ;
	while ( f = fetch ( 1 ), !read_error ) {
	    if ( n == 1 ) IGNORE fprintf ( pp_file, "%d :\t", bits / 8 ) ;
	    IGNORE fputc ( ( f ? '1' : '0' ), pp_file ) ;
	    if ( n == 64 ) {
		IGNORE fputc ( '\n', pp_file ) ;
		n = 1 ;
	    } else {
		if ( n % 8 == 0 ) IGNORE fputc ( ' ', pp_file ) ;
		n++ ;
	    }
	    bits++ ;
	}
	if ( n != 1 ) IGNORE fputc ( '\n', pp_file ) ;
	exit ( 0 ) ;
    }

    /* Call the main routines */
    if ( diagnostics || show_usage ) do_foreign_sorts = 1 ;
    init_foreign_sorts () ;
    initialize_tree () ;
    de_capsule () ;
    pretty_tree () ;
    return ( exit_status ) ;
}
