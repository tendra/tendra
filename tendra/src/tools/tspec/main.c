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
#include <signal.h>
#include "release.h"
#include "object.h"
#include "hash.h"
#include "index.h"
#include "lex.h"
#include "makefile.h"
#include "name.h"
#include "syntax.h"
#include "type.h"
#include "print.h"
#include "utility.h"


/*
    SIGNAL HANDLER

    This routine handles caught signals.
*/

static void handler
    PROTO_N ( ( sig ) )
    PROTO_T ( int sig )
{
    char *s ;
    hash_elem *e ;
    IGNORE signal ( SIGINT, SIG_IGN ) ;
    switch ( sig ) {
	case SIGINT : s = "interrupt" ; break ;
	case SIGSEGV : s = "segmentation violation" ; break ;
	case SIGTERM : s = "termination signal" ; break ;
	default : s = "unknown signal" ; break ;
    }
    error ( ERR_SERIOUS, "Caught %s", s ) ;
    e = sort_hash ( files ) ;
    while ( e ) {
	object *p = e->obj ;
	FILE *f = p->u.u_file ;
	if ( f ) {
	    char *nm = p->name ;
	    if ( verbose ) error ( ERR_INFO, "Removing %s ...", nm ) ;
	    IGNORE fclose ( f ) ;
	    IGNORE remove ( nm ) ;
	}
	e = e->next ;
    }
    exit ( exit_status ) ;
}


/*
    SEPARATE COMPILATION ROUTINE

    This routine performs the separate compilation of the set object p.
*/

static void separate
    PROTO_N ( ( p ) )
    PROTO_T ( object *p )
{
    info *i = p->u.u_info ;
    static char *exec = null ;
    if ( i->subset || i->file == null ) return ;
    if ( exec == null ) exec = buffer + strlen ( buffer ) ;
    IGNORE sprintf ( exec, "%s %s", i->api, i->file ) ;
    if ( verbose > 1 ) error ( ERR_INFO, "Executing '%s' ...", buffer ) ;
    if ( system ( buffer ) ) {
	error ( ERR_SERIOUS, "Separate compilation of %s failed", p->name ) ;
    }
    return ;
}


/*
    MARK A SET AS IMPLEMENTED

    This routine recursively marks all implemented subsets of p.
*/

static void implement
    PROTO_N ( ( p, depth ) )
    PROTO_T ( object *p X int depth )
{
    object *q ;
    info *i = p->u.u_info ;
    if ( i == null || i->implemented >= depth ) return ;
    i->implemented = depth ;
    for ( q = i->elements ; q != null ; q = q->next ) {
	if ( q->objtype == OBJ_IMPLEMENT ) {
	    implement ( q->u.u_obj, depth + 1 ) ;
	}
    }
    return ;
}


/*
    MAIN ROUTINE

    This is the main routine which interprets the command-line options
    and calls the appropriate routines.
*/

int main
    PROTO_N ( ( argc, argv ) )
    PROTO_T ( int argc X char **argv )
{
    int a ;
    char *env ;
    char *dir = "." ;
    char *api = null ;
    char *file = null ;
    char *subset = null ;
    object *commands = null ;
    FILE *preproc_file = null ;
    int show_index = 0 ;
    boolean check_only = 0 ;
    boolean preproc_input = 0 ;
    boolean separate_files = 0 ;

    /* Initialisation */
    line_no = 1 ;
    filename = "built-in definitions" ;
    init_hash () ;
    init_keywords () ;
    init_types () ;
    filename = "command line" ;
    IGNORE signal ( SIGINT, handler ) ;
    IGNORE signal ( SIGSEGV, handler ) ;
    IGNORE signal ( SIGTERM, handler ) ;

    /* Read system variables */
    env = getenv ( INPUT_ENV ) ;
    if ( env ) input_dir = string_copy ( env ) ;
    env = getenv ( OUTPUT_ENV ) ;
    if ( env ) {
	output_incl_dir = string_printf ( "%s/include", env ) ;
	output_incl_len = ( int ) strlen ( output_incl_dir ) + 1 ;
	output_src_dir = string_printf ( "%s/src", env ) ;
	output_src_len = ( int ) strlen ( output_src_dir ) + 1 ;
    }
    env = getenv ( INCLUDE_ENV ) ;
    if ( env ) {
	output_incl_dir = string_copy ( env ) ;
	output_incl_len = ( int ) strlen ( output_incl_dir ) + 1 ;
    }
    env = getenv ( SRC_ENV ) ;
    if ( env ) {
	output_src_dir = string_copy ( env ) ;
	output_src_len = ( int ) strlen ( output_src_dir ) + 1 ;
    }
    env = getenv ( COPYRIGHT_ENV ) ;
    if ( env ) copyright = string_copy ( env ) ;

    /* Process options */
    for ( a = 1 ; a < argc ; a++ ) {
	char *arg = argv [a] ;
	line_no = a ;
	if ( arg [0] == '-' ) {
	    if ( arg [1] == 'I' ) {
		dir = string_printf ( "%s:%s", dir, arg + 2 ) ;
	    } else if ( arg [1] == 'O' ) {
		output_incl_dir = arg + 2 ;
		output_incl_len = ( int ) strlen ( arg + 2 ) + 1 ;
	    } else if ( arg [1] == 'S' ) {
		output_src_dir = arg + 2 ;
		output_src_len = ( int ) strlen ( arg + 2 ) + 1 ;
	    } else if ( arg [1] == 'C' ) {
		copyright = arg + 2 ;
	    } else {
		char *s ;
		for ( s = arg + 1 ; *s ; s++ ) {
		    switch ( *s ) {
			case 'a' : separate_files = 0 ; break ;
			case 'c' : check_only = 1 ; break ;
			case 'd' : restrict_depth = 0 ; break ;
			case 'e' : preproc_file = stdout ; break ;
			case 'f' : force_output = 1 ; break ;
			case 'i' : show_index = 1 ; break ;
			case 'l' : local_input = 1 ; break ;
			case 'm' : show_index = 2 ; break ;
			case 'n' : progdate = date_stamp ( argv [0] ) ; break ;
			case 'p' : preproc_input = 1 ; break ;
			case 'r' : restrict_use = 1 ; break ;
			case 's' : separate_files = 1 ; break ;
			case 't' : allow_long_long = 1 ; break ;
			case 'u' : unique_names = 1 ; break ;
			case 'v' : verbose++ ; break ;
			case 'w' : warnings = 0 ; break ;
			case 'V' : {
			    error ( ERR_INFO, "Version: %s (release %s)",
				    progvers, RELEASE ) ;
			    break ;
			}
			default : {
			    error ( ERR_WARNING, "Unknown option, -%c", *s ) ;
			    break ;
			}
		    }
		}
	    }
	} else {
	    if ( api == null ) {
		api = arg ;
	    } else if ( file == null ) {
		file = arg ;
	    } else if ( subset == null ) {
		subset = arg ;
	    } else {
		error ( ERR_WARNING, "Too many arguments" ) ;
	    }
	}
    }
    if ( local_input ) {
	if ( subset ) error ( ERR_WARNING, "Too many arguments" ) ;
	subset = file ;
	file = api ;
	api = LOCAL_API ;
    }
    if ( api == null ) error ( ERR_FATAL, "Not enough arguments" ) ;
    input_dir = string_printf ( "%s:%s", dir, input_dir ) ;

    if ( preproc_input ) {
	/* Open preprocessed input */
	if ( file != null ) error ( ERR_WARNING, "Too many arguments" ) ;
	preproc_file = fopen ( api, "r" ) ;
	filename = api ;
	line_no = 1 ;
	if ( preproc_file == null ) {
	    error ( ERR_FATAL, "Can't open input file" ) ;
	}
    } else {
	/* Find the temporary file */
	int n ;
	if ( preproc_file == null ) {
	    preproc_file = tmpfile () ;
	    if ( preproc_file == null ) {
		error ( ERR_FATAL, "Can't open temporary file" ) ;
	    }
	}
	/* Do the preprocessing */
	preproc ( preproc_file, api, file, subset ) ;
	n = no_errors ;
	if ( n ) {
	    filename = null ;
	    error ( ERR_FATAL, "%d error(s) in preprocessor phase", n ) ;
	}
	if ( preproc_file == stdout ) exit ( exit_status ) ;
	filename = "temporary file" ;
	line_no = 1 ;
    }

    /* Deal with separate compilation */
    if ( separate_files ) {
	int n ;
	hash_elem *e ;
	char *s = buffer ;
	IGNORE sprintf ( s, "%s ", argv [0] ) ;
	for ( a = 1 ; a < argc ; a++ ) {
	    char *arg = argv [a] ;
	    if ( arg [0] == '-' ) {
		s = s + strlen ( s ) ;
		IGNORE sprintf ( s, "%s ", arg ) ;
	    }
	}
	s = s + strlen ( s ) ;
	IGNORE strcpy ( s, "-ac " ) ;
	filename = null ;
	e = sort_hash ( subsets ) ;
	while ( e ) {
	    separate ( e->obj ) ;
	    e = e->next ;
	}
	n = no_errors ;
	if ( n ) {
	    error ( ERR_FATAL, "%d error(s) in separate compilation", n ) ;
	}
	exit ( exit_status ) ;
    }

    /* Process the input */
    input_file = preproc_file ;
    input_pending = LEX_EOF ;
    rewind ( input_file ) ;
    ADVANCE_LEXER ;
    read_spec ( &commands ) ;
    if ( no_errors ) {
	filename = null ;
	error ( ERR_FATAL, "%d error(s) in analyser phase", no_errors ) ;
    }

    /* Perform the output */
    if ( !check_only ) {
	filename = null ;
	if ( commands && commands->objtype == OBJ_SET ) {
	    implement ( commands->u.u_obj, 1 ) ;
	    if ( show_index == 0 ) {
		print_set ( commands, 0 ) ;
		print_set ( commands, 1 ) ;
		if ( file == null ) {
		    hash_elem *e = sort_hash ( subsets ) ;
		    print_makefile ( api, e, 0 ) ;
		    print_makefile ( api, e, 1 ) ;
		}
	    } else {
		if ( show_index == 1 ) {
		    print_index ( commands ) ;
		} else {
		    print_machine_index ( commands ) ;
		}
	    }
	}
    }
    return ( exit_status ) ;
}
