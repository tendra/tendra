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
#include "external.h"
#include "filename.h"
#include "list.h"
#include "execute.h"
#include "flags.h"
#include "compile.h"
#include "main.h"
#include "options.h"
#include "startup.h"
#include "suffix.h"
#include "utility.h"


/*
    CURRENT VERSION NUMBER

    Version 4.0 of tcc is a complete rewrite from version 3.x.  The
    revision number is automatically generated from the RCS revision
    and is stored in version.h.
*/

#define VERSION_STRING		"Version: 4.0"

#ifndef RELEASE
#define RELEASE 		"unknown"
#endif


/*
    PRINT THE CURRENT VERSION

    This routine prints the version number.
*/

void print_version
    PROTO_Z ()
{
    error ( INFO, "%s%s, Machine: %s, Release: %s", VERSION_STRING,
	    ( checker ? " (checker)" : "" ), machine_name, RELEASE ) ;
    flag_no_files = 1 ;
    return ;
}


/*
    ENVIRONMENT

    This variable given the array of environmental variables which is
    passed as the third argument to main.
*/

char **environment = null ;


/*
    SIGNAL HANDLER

    This routine is the main signal handler.  It reports any interesting
    signals and then cleans up.
*/

void handler
    PROTO_N ( ( sig ) )
    PROTO_T ( int sig )
{
    IGNORE signal ( SIGINT, SIG_IGN ) ;
    if ( verbose ) comment ( 1, "\n" ) ;
    if ( sig != SIGINT ) {
	char *cmd = ( last_command ? last_command : "unknown" ) ;
	error ( SERIOUS, "Caught signal %d in '%s'", sig, cmd ) ;
	if ( !flag_keep_err && ( remove ( "core" ) == 0 ) ) {
	    error ( WARNING, "Removed core" ) ;
	}
    }
    exit_status = EXIT_FAILURE ;
    main_end () ;
    return ;
}


/*
    TEMPORARY DIRECTORY FLAG

    This flag is true to indicate that the temporary directory needs
    removing.
*/

static boolean made_tempdir = 0 ;


/*
    MAIN INITIALISATION ROUTINE

    This is the initialisation routine called at the very start of the
    program.  The signals SIGINT, SIGSEGV, SIGTERM and SIGFPE are all
    in ANSI.
*/

static void main_start
    PROTO_N ( ( prog, envp ) )
    PROTO_T ( char *prog X char **envp )
{
    environment = envp ;
    buffer = alloc_nof ( char, buffer_size ) ;
    progname = find_basename ( prog ) ;
    IGNORE signal ( SIGINT, handler ) ;
    IGNORE signal ( SIGSEGV, handler ) ;
    IGNORE signal ( SIGTERM, handler ) ;
#ifdef SIGFPE
    IGNORE signal ( SIGFPE, handler ) ;
#endif
    initialise_options () ;
    return ;
}


/*
    MAIN CONSOLIDATION ROUTINE

    This routine is called after all the command-line arguments have
    been processed, but before any actual compilation takes place.
*/

static void main_middle
    PROTO_Z ()
{
    char *s = temp_name ( temporary_dir, progname ) ;
    tempdir = string_copy ( s ) ;
    cmd_list ( exec_mkdir ) ;
    cmd_string ( tempdir ) ;
    IGNORE execute ( no_filename, no_filename ) ;
    if ( last_return ) {
	error ( FATAL, "Can't create temporary directory" ) ;
    }
    made_tempdir = 1 ;
    return ;
}


/*
    MAIN CLEAN UP ROUTINE

    This routine always used to exit the program, except when an
    exec fails in the child process.  It cleans up the temporary
    directory etc. and returns exit_status to the calling process.
*/

void main_end
    PROTO_Z ()
{
    IGNORE signal ( SIGINT, SIG_IGN ) ;
    remove_junk () ;
    remove_startup () ;
    if ( made_tempdir ) {
	made_tempdir = 0 ;
	cmd_string ( ( char * ) null ) ;
	cmd_list ( exec_remove ) ;
	cmd_string ( tempdir ) ;
	IGNORE execute ( no_filename, no_filename ) ;
    }
    kill_stray () ;
    exit ( exit_status ) ;
}


/*
    MAIN ROUTINE

    This is the main routine.
*/

int main
    PROTO_N ( ( argc, argv ) )
    PROTO_T ( int argc X char **argv )
{ 
    int a ;
    char *s ;
    filename *output ;
    list *opts = null ;

    /* Initialisation */
    main_start ( PROGNAME_TCC, environ ) ;

    /* Check TCCOPTS options */
    s = getenv ( TCCOPT_VAR ) ;
    if ( s != null ) {
    	opts = make_list ( s ) ;
        process_options ( opts, main_optmap ) ;
        free_list ( opts ) ;
        opts = null ;
    }

    /* Process command line options */
    for ( a = argc - 1 ; a >= 1 ; a-- ) {
	opts = insert_item ( argv [a], opts ) ;
    }
    process_options ( opts, main_optmap ) ;
    update_options () ;
    free_list ( opts ) ;

    /* Check for input files */
    if ( input_files == null ) {
	if ( flag_no_files ) main_end () ;
	error ( FATAL, "No input files specified" ) ;
    }

    /* Apply compilation */
    main_middle () ;
    output = apply_all ( input_files ) ;

    /* Check for unprocessed files */
    while ( output != null ) {
	if ( output->storage == INPUT_FILE ) {
	    error ( WARNING, "Input file '%s' not processed", output->name ) ;
	}
	output = output->next ;
    }

    /* Exit from program */
    main_end () ;
    return ( 0 ) ;
}
