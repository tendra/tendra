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
#include "types.h"
#include "depend.h"
#include "error.h"
#include "option.h"
#include "output.h"
#include "path.h"
#include "xalloc.h"


/*
    INITIALISATION FILE

    This macro gives the default location for the initialisation file.
*/

#ifndef INIT_FILE
#define INIT_FILE	"make_mf.ini"
#endif


/*
    READ A CONFIGURATION FILE

    This routine reads a sequence of configuration options from the
    file nm.  dir gives the standard initialisation file directory.
*/

static OPTION *read_options
    PROTO_N ( ( nm, dir ) )
    PROTO_T ( char *nm X char *dir )
{
    char *s ;
    OPTION *opts = NULL ;
    FILE *f = fopen ( nm, "r" ) ;
    if ( f == NULL && dir && nm [0] != '/' ) {
	/* Try standard directory */
	char *nm2 = xstrcat ( dir, nm ) ;
	f = fopen ( nm2, "r" ) ;
    }
    if ( f == NULL ) {
	error ( ERROR_SERIOUS, "Can't open configuration file, '%s'", nm ) ;
	return ( opts ) ;
    }
    while ( s = fgets ( pathbuff, 1000, f ), s != NULL ) {
	while ( *s == ' ' || *s == '\t' ) s++ ;
	if ( *s == '#' || *s == '\n' || *s == 0 ) {
	    /* Comments */
	} else {
	    /* Other lines */
	    char *e = strchr ( s, '\n' ) ;
	    if ( e ) {
		do {
		    *( e-- ) = 0 ;
		} while ( *e == ' ' || *e == '\t' ) ;
	    }
	    s = xstrcpy ( s ) ;
	    opts = add_option ( opts, s, 0 ) ;
	}
    }
    fclose_v ( f ) ;
    return ( opts ) ;
}


/*
    MAIN ROUTINE

    This is the top level routine.  It calls the initialisation routines,
    processes the command-line options, and calls the output routines.
*/

int main
    PROTO_N ( ( argc, argv ) )
    PROTO_T ( int argc X char **argv )
{
    int a = 1 ;
    char *init ;
    OPTION *opt ;
    OPTION *opts ;
    char *pre = NULL ;
    char *init_dir = NULL ;

    /* Call initialisation routines */
    set_progname ( argv [0], "1.1" ) ;
    init = getenv ( "MAKE_MF_INIT" ) ;
    if ( init == NULL ) init = INIT_FILE ;
    pre = strrchr ( init, '/' ) ;
    if ( pre ) {
	/* Copy the directory component */
	init_dir = xstrcpy ( init ) ;
	pre = strrchr ( init_dir, '/' ) ;
	pre [1] = 0 ;
	pre = NULL ;
    }
    if ( a < argc ) {
	/* '+f<init>' allowed as first option */
	char *arg = argv [a] ;
	if ( arg [0] == '+' && arg [1] == 'f' ) {
	    init = arg + 2 ;
	    a++ ;
	}
    }
    opts = read_options ( init, init_dir ) ;
    if ( exit_status == EXIT_FAILURE ) return ( exit_status ) ;

    /* Process command-line options */
    while ( a < argc ) {
	char *arg = argv [a] ;
	if ( pre ) {
	    arg = xstrcat ( pre, arg ) ;
	    pre = NULL ;
	} else {
	    arg = xstrcpy ( arg ) ;
	}
	if ( arg [0] == '-' ) {
	    switch ( arg [1] ) {
		case 'I' : case 'L' : case 'o' : {
		    /* Two part options */
		    if ( arg [2] == 0 ) pre = arg ;
		    break ;
		}
	    }
	} else if ( arg [0] == '+' ) {
	    switch ( arg [1] ) {
		case 'A' : case 'C' : case 'F' : case 'H' :
		case 'I' : case 'L' : case 'R' : case 'V' :
		case 'W' : case 'm' : case 'w' : {
		    /* Two part options */
		    if ( arg [2] == 0 ) pre = arg ;
		    break ;
		}
	    }
	}
	if ( pre == NULL ) opts = add_option ( opts, arg, 0 ) ;
	a++ ;
    }

    /* Analyse options */
    for ( opt = opts ; opt != NULL ; opt = opt->next ) {
	char *arg = opt->opt ;
	if ( arg [0] == '-' ) {
	    switch ( arg [1] ) {

		case 'I' : {
		    /* Include directory */
		    PATHNAME *p = make_pathname ( arg + 2, 1 ) ;
		    if ( p->alias == NULL ) p->alias = src_alias ( 0 ) ;
		    p->exists = 1 ;
		    incl_dirs = add_directory ( incl_dirs, p, 0 ) ;
		    goto all_options ;
		}

		case 'L' : {
		    /* Library directory */
		    PATHNAME *p = make_pathname ( arg + 2, 1 ) ;
		    if ( p->alias == NULL ) p->alias = src_alias ( 1 ) ;
		    p->exists = 1 ;
		    lib_dirs = add_directory ( lib_dirs, p, 0 ) ;
		    goto all_options ;
		}

		case 'o' : {
		    PATHNAME *p = make_pathname ( arg + 2, 1 ) ;
		    p->exists = 1 ;
		    output_file = p ;
		    goto all_options ;
		}

		default :
		all_options : {
		    /* Other options */
		    cmd_opts = add_option ( cmd_opts, arg, 0 ) ;
		    break ;
		}
	    }

	} else if ( arg [0] == '+' ) {
	    switch ( arg [1] ) {

		case 'A' : {
		    /* Alias definition */
		    PATHNAME *p = make_pathname ( arg + 2, 1 ) ;
		    p->exists = 1 ;
		    break ;
		}

		case 'C' : {
		    /* Current working directory */
		    PATHNAME *p = make_pathname ( arg + 2, 1 ) ;
		    p->exists = 1 ;
		    current_dir = p ;
		    break ;
		}

		case 'F' : {
		    /* Configuration file */
		    OPTION *fopts = read_options ( arg + 2, init_dir ) ;
		    if ( fopts ) {
			OPTION *p = fopts ;
			while ( p->next ) p = p->next ;
			p->next = opt->next ;
			opt->next = fopts ;
		    }
		    break ;
		}

		case 'H' : {
		    /* Home directory */
		    PATHNAME *p = make_pathname ( arg + 2, 1 ) ;
		    p->exists = 1 ;
		    home_dir = p ;
		    break ;
		}

		case 'I' : {
		    /* Built-in include directory */
		    PATHNAME *p = make_pathname ( arg + 2, 1 ) ;
		    p->exists = 1 ;
		    incl_dirs = add_directory ( incl_dirs, p, 1 ) ;
		    break ;
		}

		case 'L' : {
		    /* Built-in include directory */
		    PATHNAME *p = make_pathname ( arg + 2, 1 ) ;
		    p->exists = 1 ;
		    lib_dirs = add_directory ( lib_dirs, p, 1 ) ;
		    break ;
		}

		case 'R' : case 'V' : {
		    /* Rule definitions */
		    int dup = 0 ;
		    if ( arg [1] == 'V' ) dup = 1 ;
		    rule_opts = add_option ( rule_opts, arg + 2, dup ) ;
		    break ;
		}

		case 'W' : {
		    /* Work directory */
		    PATHNAME *p = make_pathname ( arg + 2, 1 ) ;
		    p->exists = 1 ;
		    work_dir = p ;
		    break ;
		}

		case 'i' : {
		    if ( streq ( arg + 1, "init" ) ) {
			init_pathname () ;
			cmd_opts = NULL ;
			rule_opts = NULL ;
			incl_dirs = NULL ;
			lib_dirs = NULL ;
			break ;
		    }
		    goto unknown_options ;
		}

		case 'm' : {
		    /* Machine type */
		    char *mach = arg + 2 ;
		    if ( streq ( mach, "dos" ) ) {
			dos_pathname = 1 ;
			dos_output = 1 ;
			break ;
		    }
		    if ( streq ( mach, "dos-unix" ) ) {
			dos_pathname = 1 ;
			dos_output = 0 ;
			break ;
		    }
		    if ( streq ( mach, "unix" ) ) {
			dos_pathname = 0 ;
			dos_output = 0 ;
			break ;
		    }
		    if ( streq ( mach, "unix-dos" ) ) {
			dos_pathname = 0 ;
			dos_output = 1 ;
			break ;
		    }
		    goto unknown_options ;
		}

		case 'r' : {
		    /* Relative pathnames */
		    if ( streq ( arg + 1, "relative" ) ) {
			relative_output = 1 ;
			break ;
		    }
		    goto unknown_options ;
		}

		case 'w' : {
		    /* Maximum width */
		    max_column = atoi ( arg + 2 ) ;
		    break ;
		}

		default :
		unknown_options : {
		    error ( ERROR_WARNING, "Unknown option, '%s'", arg ) ;
		    break ;
		}
	    }

	} else {
	    /* Create aliases for source directories */
	    PATHNAME *p = make_pathname ( arg, 1 ) ;
	    if ( p->up->alias == NULL ) p->up->alias = src_alias ( 0 ) ;
	}
    }

    /* Check for incomplete options */
    if ( pre ) error ( ERROR_WARNING, "Incomplete option, '%s'", pre ) ;

    /* Process input files */
    for ( opt = opts ; opt != NULL ; opt = opt->next ) {
	char *arg = opt->opt ;
	if ( arg [0] != '-' && arg [0] != '+' ) {
	    PATHNAME *p = make_pathname ( arg, 1 ) ;
	    find_dependency ( p, 0 ) ;
	}
    }

    /* Provide some default alias definitions */
    if ( work_dir->alias == NULL ) work_dir->alias = "WORK" ;

    /* Call output routines */
    output_all ( stdout ) ;
    return ( exit_status ) ;
}
