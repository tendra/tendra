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
#include "external.h"
#include "filename.h"
#include "list.h"
#include "execute.h"
#include "flags.h"
#include "startup.h"
#include "utility.h"


/*
    THE STARTUP AND ENDUP FILES

    These variables give the names and file descriptors for the startup
    and endup files, plus the command-line options to pass them to the
    producer.
*/

static FILE *startup_file = null, *endup_file = null ;
static char *startup_name = null, *endup_name = null ;
char *startup_opt = null, *endup_opt = null ;


/*
    ADD A MESSAGE TO THE STARTUP FILE

    This routine prints the message s to the tcc startup file.
*/

void add_to_startup
    PROTO_N ( ( s ) )
    PROTO_T ( char *s )
{
    if ( startup_name == null ) {
	startup_name = temp_name ( temporary_dir, "ts" ) ;
	startup_opt = string_concat ( "-f", startup_name ) ;
    }
    opt_startup = add_item ( opt_startup, s ) ;
    if ( dry_run ) return ;
    if ( startup_file == null ) {
	startup_file = fopen ( startup_name, "a" ) ;
	if ( startup_file == null ) {
	    error ( SERIOUS, "Can't open startup file, '%s'", startup_name ) ;
	    return ;
	}
	IGNORE fprintf ( startup_file, "#line 1 \"%s\"\n", name_h_file ) ;
    }
    IGNORE fputs ( s, startup_file ) ;
    return ;
}


/*
    ADD A MESSAGE TO THE ENDUP FILE

    This routine prints the message s to the tcc endup file.
*/

void add_to_endup
    PROTO_N ( ( s ) )
    PROTO_T ( char *s )
{
    if ( endup_name == null ) {
	endup_name = temp_name ( temporary_dir, "te" ) ;
	startup_opt = string_concat ( "-e", endup_name ) ;
    }
    opt_endup = add_item ( opt_endup, s ) ;
    if ( dry_run ) return ;
    if ( endup_file == null ) {
	endup_file = fopen ( endup_name, "a" ) ;
	if ( endup_file == null ) {
	    error ( SERIOUS, "Can't open endup file, '%s'", endup_name ) ;
	    return ;
	}
	IGNORE fprintf ( endup_file, "#line 1 \"%s\"\n", name_E_file ) ;
    }
    IGNORE fputs ( s, endup_file ) ;
    return ;
}


/*
    THE TOKEN DEFINITION FILE

    This file is used to hold TDF notation for the definition of the
    command-line tokens.
*/

static FILE *tokdef_file = null ;
char *tokdef_name = null ;


/*
    ADD A MESSAGE TO THE TOKEN DEFINITION FILE

    This routine prints the message s to the tcc token definition file.
*/

void add_to_tokdef
    PROTO_N ( ( s ) )
    PROTO_T ( char *s )
{
    if ( tokdef_name == null ) {
	tokdef_name = temp_name ( temporary_dir, "td" ) ;
    }
    if ( dry_run ) return ;
    if ( tokdef_file == null ) {
	tokdef_file = fopen ( tokdef_name, "a" ) ;
	if ( tokdef_file == null ) {
	    error ( SERIOUS, "Can't open token definition file, '%s'",
		    tokdef_name ) ;
	    return ;
	}
	IGNORE fputs ( "( make_tokdec ~char variety )\n", tokdef_file ) ;
	IGNORE fputs ( "( make_tokdec ~signed_int variety )\n\n",
		       tokdef_file ) ;
    }
    IGNORE fputs ( s, tokdef_file ) ;
    return ;
}


/*
    CLOSE THE STARTUP AND ENDUP FILES

    This routine closes the startup and endup files.
*/

void close_startup
    PROTO_Z ()
{
    if ( startup_file ) {
	IGNORE fclose ( startup_file ) ;
	startup_file = null ;
    }
    if ( endup_file ) {
	IGNORE fclose ( endup_file ) ;
	endup_file = null ;
    }
    if ( tokdef_file ) {
	IGNORE fclose ( tokdef_file ) ;
	tokdef_file = null ;
    }
    return ;
}


/*
    CLEAN UP THE STARTUP AND ENDUP FILES

    This routine is called before the program terminates either to
    remove the tcc startup and endup files or to move them if they
    are to be preserved.
*/

void remove_startup
    PROTO_Z ()
{
    if ( keeps [ STARTUP_FILE ] ) {
	if ( startup_name ) {
	    cmd_list ( exec_move ) ;
	    cmd_string ( startup_name ) ;
	    cmd_string ( name_h_file ) ;
	    IGNORE execute ( no_filename, no_filename ) ;
	}
	if ( endup_name ) {
	    cmd_list ( exec_move ) ;
	    cmd_string ( endup_name ) ;
	    cmd_string ( name_E_file ) ;
	    IGNORE execute ( no_filename, no_filename ) ;
	}
	if ( tokdef_name ) {
	    cmd_list ( exec_move ) ;
	    cmd_string ( tokdef_name ) ;
	    cmd_string ( name_p_file ) ;
	    IGNORE execute ( no_filename, no_filename ) ;
	}
    } else {
	if ( startup_name ) {
	    cmd_list ( exec_remove ) ;
	    cmd_string ( startup_name ) ;
	    IGNORE execute ( no_filename, no_filename ) ;
	}
	if ( endup_name ) {
	    cmd_list ( exec_remove ) ;
	    cmd_string ( endup_name ) ;
	    IGNORE execute ( no_filename, no_filename ) ;
	}
	if ( tokdef_name ) {
	    cmd_list ( exec_remove ) ;
	    cmd_string ( tokdef_name ) ;
	    IGNORE execute ( no_filename, no_filename ) ;
	}
    }
    return ;
}


/*
    DEAL WITH STARTUP PRAGMA OPTIONS

    This routine translates command-line compilation mode options into
    the corresponding pragma statements.
*/

void add_pragma
    PROTO_N ( ( s ) )
    PROTO_T ( char *s )
{
    char *e ;
    char *level = "warning" ;
    static char *start_scope = "#pragma TenDRA begin\n" ;
    if ( start_scope ) {
	add_to_startup ( start_scope ) ;
	start_scope = null ;
    }
    e = strchr ( s, '=' ) ;
    if ( e ) {
	level = e + 1 ;
	*e = 0 ;
    }

    /* Write option to startup file */
    add_to_startup ( "#pragma TenDRA option \"" ) ;
    add_to_startup ( s ) ;
    add_to_startup ( "\" " ) ;
    add_to_startup ( level ) ;
    add_to_startup ( "\n" ) ;
    return ;
}


/*
    DEAL WITH STARTUP TOKEN OPTIONS

    This routine translates command-line token definition options into
    the corresponding pragma statements.
*/

void add_token
    PROTO_N ( ( s ) )
    PROTO_T ( char *s )
{
    char *type = "int" ;
    char *defn = "1" ;
    char *e = strchr ( s, '=' ) ;
    if ( e ) {
	defn = e + 1 ;
	*e = 0 ;
    }

    /* Write token description to startup file */
    add_to_startup ( "#pragma token EXP const : " ) ;
    add_to_startup ( type ) ;
    add_to_startup ( " : " ) ;
    add_to_startup ( s ) ;
    add_to_startup ( " #\n" ) ;
    add_to_startup ( "#pragma interface " ) ;
    add_to_startup ( s ) ;
    add_to_startup ( "\n" ) ;

    /* Write definition to token definition file */
    add_to_tokdef ( "( make_tokdef " ) ;
    add_to_tokdef ( s ) ;
    add_to_tokdef ( " exp\n" ) ;
    add_to_tokdef ( "  ( make_int ~signed_int " ) ;
    add_to_tokdef ( defn ) ;
    add_to_tokdef ( " ) )\n\n" ) ;
    return ;
}
