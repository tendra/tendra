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
#include "error.h"
#include "include.h"
#include "option.h"
#include "path.h"
#include "xalloc.h"


/*
    COMMAND-LINE OPTIONS

    These variables give various compiler, and other options, derived
    from the command-line.
*/

OPTION *cmd_opts = NULL ;
OPTION *rule_opts = NULL ;
DIRECTORY *incl_dirs = NULL ;
DIRECTORY *lib_dirs = NULL ;


/*
    SEARCH FOR AN OPTION

    This routine searches the given list of options for one that matches
    opt (up to the first '=').
*/

OPTION *find_option
    PROTO_N ( ( list, opt ) )
    PROTO_T ( OPTION *list X char *opt )
{
    char *e = strchr ( opt, '=' ) ;
    if ( e ) {
	OPTION *f ;
	size_t sz = ( size_t ) ( e - opt ) + 1 ;
	for ( f = list ; f != NULL ; f = f->next ) {
	    if ( strncmp ( f->opt, opt, sz ) == 0 ) return ( f ) ;
	}
    }
    return ( NULL ) ;
}


/*
    ADD AN OPTION TO A LIST

    This routine adds the option opt to the end of the given list, returning
    the result.  If dup is true then duplicates (up to the first '=') are
    handled by replacement.
*/

OPTION *add_option
    PROTO_N ( ( list, opt, dup ) )
    PROTO_T ( OPTION *list X char *opt X int dup )
{
    OPTION *d ;
    OPTION *f = list ;
    static int options_left = 0 ;
    static OPTION *options_free = NULL ;

    /* Check for duplicates */
    while ( *opt == ' ' || *opt == '\t' ) opt++ ;
    if ( dup ) {
	d = find_option ( list, opt ) ;
	if ( d != NULL ) {
	    d ->opt = opt ;
	    return ( list ) ;
	}
    }

    /* Allocate new directory */
    if ( options_left == 0 ) {
	options_left = 200 ;
	options_free = xmalloc_nof ( OPTION, options_left ) ;
    }
    d = options_free + ( --options_left ) ;
    d->opt = opt ;
    d->next = NULL ;

    /* Insert into list */
    if ( f == NULL ) {
	list = d ;
    } else {
	while ( f->next ) f = f->next ;
	f->next = d ;
    }
    return ( list ) ;
}


/*
    ADD A DIRECTORY TO A LIST

    This routine adds the directory dir to the end of the given list,
    returning the result.  Note that built-in options are inserted
    at the end of the list.
*/

DIRECTORY *add_directory
    PROTO_N ( ( list, dir, builtin ) )
    PROTO_T ( DIRECTORY *list X PATHNAME *dir X int builtin )
{
    DIRECTORY *d ;
    DIRECTORY *e = NULL ;
    DIRECTORY *f = list ;

    /* Allocate new directory */
    static int directories_left = 0 ;
    static DIRECTORY *directories_free = NULL ;
    if ( directories_left == 0 ) {
	directories_left = 50 ;
	directories_free = xmalloc_nof ( DIRECTORY, directories_left ) ;
    }
    d = directories_free + ( --directories_left ) ;
    d->dir = dir ;
    d->builtin = builtin ;

    /* Insert into list */
    while ( f != NULL ) {
	if ( !builtin && f->builtin ) break ;
	e = f ;
	f = f->next ;
    }
    if ( e == NULL ) {
	d->next = list ;
	list = d ;
    } else {
	d->next = e->next ;
	e->next = d ;
    }
    return ( list ) ;
}


/*
    SEARCH AN INCLUSION DIRECTORY

    This routine checks whether the subfile nm of p exists, either as a
    previously defined pathname, or as an actual file.  Note that the
    pathname is built up in pathbuff.
*/

static PATHNAME *search_directory
    PROTO_N ( ( p, nm ) )
    PROTO_T ( PATHNAME *p X char *nm )
{
    FILE *f ;
    char *bnm ;
    PATHNAME *r ;

    /* Create the pathname */
    char *pnm = pathbuff ;
    sprintf_v ( pnm, "%s/%s", p->full, nm ) ;
    bnm = pnm + strlen ( p->full ) + 1 ;

    /* Check if it already exists */
    r = find_pathname ( p, bnm, pnm, 0 ) ;
    if ( r ) return ( r ) ;

    /* Check if the file can be opened */
    f = fopen ( pnm, "r" ) ;
    if ( f ) {
	/* Create it is it can */
	fclose_v ( f ) ;
	r = find_pathname ( p, bnm, pnm, 1 ) ;
	return ( r ) ;
    }
    return ( NULL ) ;
}


/*
    SEARCH FOR AN INCLUSION DEPENDENCY

    This routine searches for a file named nm along the given inclusion
    search path.  The flag qo is true to indicate that the search
    algorithm for quoted '#include' directives is to be used, and false
    if that for angle bracketed '#include' directives is to be used.
    The null pathname is returned if the file cannot be found or is
    only found in the default directories.
*/

PATHNAME *search_pathname
    PROTO_N ( ( path, nm, qo ) )
    PROTO_T ( DIRECTORY *path X char *nm X int qo )
{
    PATHNAME *p ;
    DIRECTORY *d ;

    /* Check for full pathnames */
    if ( nm [0] == '/' ) {
	/* Full pathnames */
	error ( ERROR_WARNING, "Inclusion of '%s' is not portable", nm ) ;
	p = make_pathname ( nm, 0 ) ;
	return  ( p ) ;
    }

    /* Check for quoted inclusions */
    if ( qo ) {
	/* Quoted inclusions */
	if ( crt_pathname ) {
	    p = search_directory ( crt_pathname->up, nm ) ;
	    if ( p ) return ( p ) ;
	}
    }

    /* Scan through path */
    for ( d = path ; d != NULL ; d = d->next ) {
	p = search_directory ( d->dir, nm ) ;
	if ( p ) {
	    if ( d->builtin ) return ( NULL ) ;
	    return ( p ) ;
	}
    }

    /* Report unfound files */
    p = search_directory ( nonexistant_dir, nm ) ;
    if ( p == NULL ) {
	/* Unfound files are created in nonexistant_dir */
	error ( ERROR_WARNING, "Can't find file, '%s'", nm ) ;
	p = make_pathname ( pathbuff, 0 ) ;
	p->exists = 1 ;
    }
    return ( NULL ) ;
}
