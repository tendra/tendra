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
#include "read.h"
#include "calculus.h"
#include "check.h"
#include "code.h"
#include "common.h"
#include "disk.h"
#include "error.h"
#include "lex.h"
#include "output.h"
#include "pretty.h"
#include "print.h"
#include "template.h"
#include "token.h"
#include "write.h"
#include "xalloc.h"


/*
    ACTIONS

    These macros are used to describe the various actions which the
    program can perform.
*/

#define ACTION_C		0
#define ACTION_TOKEN		1
#define ACTION_DISK		2
#define ACTION_PRETTY		3
#define ACTION_PRINT		4
#define ACTION_WRITE		5
#define ACTION_LIST		6
#define ACTION_TEMPL		7


/*
    LIST ACTION

    This is the trivial action which just prints a list of all the types
    in the algebra.
*/

static void list_action
    PROTO_N ( ( nm ) )
    PROTO_T ( char *nm )
{
    if ( streq ( nm, "." ) ) {
	output_file = stdout ;
    } else {
	output_file = fopen ( nm, "w" ) ;
	if ( output_file == NULL ) {
	    error ( ERROR_SERIOUS, "Can't open output file, '%s'", nm ) ;
	    return ;
	}
    }
    LOOP_TYPE output ( "%TT ;\n", CRT_TYPE ) ;
    flush_output () ;
    if ( output_file != stdout ) fclose_v ( output_file ) ;
    return ;
}


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
    int text = 1 ;
    int no_args = 0 ;
    int last_arg = 0 ;
    int need_alg = 1 ;
    char *in = NULL ;
    char *alg = NULL ;
    int act = ACTION_C ;

    /* Scan arguments */
    set_progname ( argv [0], "1.2" ) ;
    for ( a = 1 ; a < argc ; a++ ) {
	char *arg = argv [a] ;
	if ( arg [0] != '-' ) {
	    last_arg = a ;
	    no_args++ ;
	}
    }
    if ( no_args == 1 ) last_arg = 0 ;

    /* Process arguments */
    for ( a = 1 ; a < argc ; a++ ) {
	char *arg = argv [a] ;
	if ( arg [0] == '-' ) {
	    int known ;
	    if ( arg [1] && arg [2] ) {
		/* Multi-character options */
		known = 0 ;
		switch ( arg [1] ) {
		    case 'A' : {
			/* Output algebra name */
			alg = arg + 2 ;
			known = 1 ;
			break ;
		    }
		    case 'E' : {
			/* File containing extra types */
			if ( need_alg ) new_algebra () ;
			process_file ( arg + 2, 0 ) ;
			need_alg = 0 ;
			known = 1 ;
			break ;
		    }
		    case 'T' : {
			/* Template file */
			if ( act == ACTION_TOKEN ) token_cond = 1 ;
			in = arg + 2 ;
			act = ACTION_TEMPL ;
			known = 1 ;
			break ;
		    }
		}
	    } else {
		/* Single character options */
		known = 1 ;
		switch ( arg [1] ) {
		    /* Input flags */
		    case 'r' : text = 0 ; break ;
		    case 'i' : text = 1 ; break ;

		    /* Output flags */
		    case 'c' : act = ACTION_C ; break ;
		    case 'd' : act = ACTION_DISK ; break ;
		    case 'l' : act = ACTION_LIST ; break ;
		    case 'o' : act = ACTION_PRETTY ; break ;
		    case 'p' : act = ACTION_PRINT ; break ;
		    case 't' : act = ACTION_TOKEN ; break ;
		    case 'w' : act = ACTION_WRITE ; break ;

		    /* Output options */
		    case 'a' : extra_asserts = 1 ; break ;
		    case 'e' : extra_headers = 1 ; break ;
		    case 'm' : map_proto = 0 ; break ;
		    case 'n' : const_tokens = 0 ; break ;
		    case 'x' : allow_vec = 0 ; break ;
		    case 'z' : allow_stack = 0 ; break ;

		    /* Other options */
		    case 'q' : verbose_output = 0 ; break ;
		    case 'v' : report_version () ; break ;
		    default : known = 0 ; break ;
		}
	    }
	    if ( !known ) {
		error ( ERROR_WARNING, "Unknown option, '%s'", arg ) ;
	    }
	} else if ( a != last_arg ) {
	    if ( need_alg ) new_algebra () ;
	    if ( text ) {
		process_file ( arg, 1 ) ;
	    } else {
		read_file ( arg ) ;
	    }
	    check_types () ;
	    check_names ( 0 ) ;
	    need_alg = 1 ;
	}
    }
    if ( no_args == 0 ) error ( ERROR_FATAL, "Not enough arguments" ) ;
    if ( !need_alg ) error ( ERROR_SERIOUS, "Badly placed -E option" ) ;

    /* Look up output algebra */
    if ( alg ) {
	ALGEBRA_DEFN *al = find_algebra ( alg ) ;
	if ( al == NULL ) {
	    error ( ERROR_SERIOUS, "Algebra %s not defined", alg ) ;
	} else {
	    algebra = al ;
	}
    }

    /* Generate output */
    if ( exit_status == EXIT_SUCCESS ) {
	char *out = ( last_arg ? argv [ last_arg ] : "." ) ;
	switch ( act ) {
	    case ACTION_C : main_action_c ( out ) ; break ;
	    case ACTION_TOKEN : main_action_tok ( out ) ; break ;
	    case ACTION_DISK : disk_action ( out ) ; break ;
	    case ACTION_PRETTY : pretty_file ( out ) ; break ;
	    case ACTION_PRINT : print_action ( out ) ; break ;
	    case ACTION_WRITE : write_file ( out ) ; break ;
	    case ACTION_LIST : list_action ( out ) ; break ;
	    case ACTION_TEMPL : template_file ( in, out ) ; break ;
	}
    } else {
	error ( ERROR_FATAL, "No output generated due to previous errors" ) ;
    }
    return ( exit_status ) ;
}
