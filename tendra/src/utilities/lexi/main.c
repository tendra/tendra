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
#include "char.h"
#include "error.h"
#include "lex.h"
#include "output.h"
#include "syntax.h"


/*
    MAIN ROUTINE

    This is the main routine.  It processes the command-line options,
    reads the input file, and writes the output files.
*/

int main
    PROTO_N ( ( argc, argv ) )
    PROTO_T ( int argc X char **argv )
{
    int a ;
    int key = 0 ;
    int too_many = 0 ;
    char *input = NULL ;
    char *output = NULL ;

    /* Process arguments */
    set_progname ( argv [0], "1.1" ) ;
    for ( a = 1 ; a < argc ; a++ ) {
	char *arg = argv [a] ;
	if ( arg [0] == '-' && arg [1] ) {
	    int known = 0 ;
	    switch ( arg [1] ) {
		case 'k' : {
		    if ( arg [2] ) break ;
		    key = 1 ;
		    known = 1 ;
		    break ;
		}
		case 'l' : {
		    sid_prefix = arg + 2 ;
		    known = 1 ;
		    break ;
		}
		case 'v' : {
		    if ( arg [2] ) break ;
		    report_version () ;
		    known = 1 ;
		    break ;
		}
	    }
	    if ( !known ) {
		error ( ERROR_WARNING, "Unknown option, '%s'", arg ) ;
	    }
	} else {
	    if ( input == NULL ) {
		input = arg ;
	    } else if ( output == NULL ) {
		output = arg ;
	    } else {
		too_many = 1 ;
	    }
	}
    }

    /* Check arguments */
    if ( input == NULL ) error ( ERROR_FATAL, "Not enough arguments" ) ;
    if ( too_many ) error ( ERROR_WARNING, "Too many arguments" ) ;

    /* Process input file */
    process_file ( input ) ;

    /* Generate output */
    if ( exit_status == EXIT_SUCCESS ) {
	if ( white_space == NULL ) white_space = make_string ( " \t\n" ) ;
	if ( output == NULL || streq ( output, "-" ) ) {
	    lex_output = stdout ;
	    output = NULL ;
	} else {
	    lex_output = fopen ( output, "w" ) ;
	    if ( lex_output == NULL ) {
		error ( ERROR_FATAL, "Can't open output file, %s", output ) ;
	    }
	}
	if ( key ) {
	    output_keyword () ;
	} else {
	    output_all () ;
	}
	if ( output ) fclose_v ( lex_output ) ;
    } else {
	error ( ERROR_FATAL, "Terminating due to previous errors" ) ;
    }
    return ( exit_status ) ;
}
