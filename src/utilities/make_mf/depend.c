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
#include "include.h"
#include "option.h"
#include "path.h"
#include "xalloc.h"


/*
    ALLOCATE A NEW DEPENDENCY

    This routine allocates a new dependency structure for the file p.
*/

static DEPENDENCY *new_dependency
    PROTO_Z ()
{
    DEPENDENCY *d ;
    static int dependencies_left = 0 ;
    static DEPENDENCY *dependencies_free = NULL ;
    if ( dependencies_left == 0 ) {
	dependencies_left = 200 ;
	dependencies_free = xmalloc_nof ( DEPENDENCY, dependencies_left ) ;
    }
    d = dependencies_free + ( --dependencies_left ) ;
    return ( d ) ;
}


/*
    ADD A FILE TO A DEPENDENCY LIST

    This routine creates a dependency of p on q.
*/

void add_dependency
    PROTO_N ( ( p, q ) )
    PROTO_T ( PATHNAME *p X PATHNAME *q )
{
    DEPENDENCY *d ;
    DEPENDENCY *e = NULL ;

    /* Check for cyclic dependencies */
    if ( q->mark == 2 ) {
	error ( ERROR_WARNING, "Cyclic dependency on '%s'", q->full ) ;
	return ;
    }

    /* Check for duplicate dependencies */
    for ( d = p->dep ; d != NULL ; d = d->next ) {
	if ( d->file == q ) return ;
	if ( strcmp ( d->file->name, q->name ) < 0 ) e = d ;
    }

    /* Create new dependency */
    d = new_dependency () ;
    d->file = q ;
    if ( e == NULL ) {
	d->next = p->dep ;
	p->dep = d ;
    } else {
	d->next = e->next ;
	e->next = d ;
    }
    return ;
}


/*
    SEARCH FOR A C SOURCE FILE

    Given a binary object file, TDF capsule, or C spec file, p, this routine
    searches for a C source file which can be compiled to give this file.
*/

static void find_c_file
    PROTO_N ( ( p ) )
    PROTO_T ( PATHNAME *p )
{
    PATHNAME *pc ;
    char *s = xstrcat ( p->name, cpp_suffix ) ;
    int n = ( int ) strlen ( s ) - 1 ;
    strcpy_v ( s + n, "c" ) ;
    pc = search_pathname ( incl_dirs, s, 0 ) ;
    if ( pc == NULL ) {
	strcpy_v ( s + n, "C" ) ;
	pc = search_pathname ( incl_dirs, s, 0 ) ;
	if ( pc == NULL ) {
	    strcpy_v ( s + n, cpp_suffix ) ;
	    pc = search_pathname ( incl_dirs, s, 0 ) ;
	}
    }
    if ( pc ) {
	add_dependency ( p, pc ) ;
	add_dependency ( c_files, pc ) ;
	pc->exists = 1 ;
    }
    return ;
}


/*
    FIND THE DEPENDENCIES ASSOCIATED WITH A FILE

    This routine analyses the file given by the pathname p for dependencies.
*/

void find_dependency
    PROTO_N ( ( p, depth ) )
    PROTO_T ( PATHNAME *p X int depth )
{
    char *suff ;
    DEPENDENCY *d ;
    if ( p->mark ) return ;

    /* Generate an alias for the directory containing p */
    if ( p->up->alias == NULL ) p->up->alias = src_alias ( 0 ) ;

    /* Check dependencies for various file types */
    suff = p->suffix ;
    if ( streq ( suff, cpp_suffix ) ) {
	suff = "C" ;
    } else if ( streq ( suff, k_suffix ) ) {
	suff = "k" ;
    }
    if ( strlen ( suff ) != 1 ) goto default_lab ;
    switch ( suff [0] ) {

	case 'c' :
	case 'C' : {
	    /* C and C++ source files */
	    process_file ( p ) ;
	    if ( depth == 0 ) {
		/* Derive a binary object file from this */
		PATHNAME *po = derived_pathname ( work_dir, p, "o" ) ;
		add_dependency ( po, p ) ;
		add_dependency ( o_files, po ) ;
		po->exists = 1 ;

		/* Also derive a TDF capsule */
		po = derived_pathname ( work_dir, p, "j" ) ;
		add_dependency ( po, p ) ;
		add_dependency ( j_files, po ) ;
		po->exists = 1 ;

		/* Also derive a C spec file */
		po = derived_pathname ( work_dir, p, k_suffix ) ;
		add_dependency ( po, p ) ;
		add_dependency ( k_files, po ) ;
		po->exists = 1 ;

		/* Only top level files are counted */
		add_dependency ( c_files, p ) ;
	    }
	    break ;
	}

	case 'o' : {
	    /* Binary object files */
	    test_file ( p ) ;
	    if ( depth == 0 ) find_c_file ( p ) ;
	    add_dependency ( o_files, p ) ;
	    break ;
	}

	case 'j' : {
	    /* TDF capsules */
	    test_file ( p ) ;
	    if ( depth == 0 ) find_c_file ( p ) ;
	    add_dependency ( j_files, p ) ;
	    break ;
	}

	case 'k' : {
	    /* C spec files */
	    test_file ( p ) ;
	    if ( depth == 0 ) find_c_file ( p ) ;
	    add_dependency ( k_files, p ) ;
	    break ;
	}

	case 'l' : {
	    /* LEX source files */
	    PATHNAME *ph ;
	    process_file ( p ) ;
	    ph = derived_pathname ( p->up, p, "h" ) ;
	    add_dependency ( ph, p ) ;
	    add_dependency ( l_output, ph ) ;
	    ph->exists = 1 ;
	    add_dependency ( l_files, p ) ;
	    break ;
	}

	case 'y' : {
	    /* YACC source files */
	    PATHNAME *ph ;
	    process_file ( p ) ;
	    ph = derived_pathname ( p->up, p, "h" ) ;
	    add_dependency ( ph, p ) ;
	    add_dependency ( y_output, ph ) ;
	    ph->exists = 1 ;
	    add_dependency ( y_files, p ) ;
	    break ;
	}

	default :
	default_lab : {
	    /* Unrecognised source files */
	    if ( depth == 0 ) {
		error ( ERROR_WARNING, "Unknown file type, '%s'", p->name ) ;
	    }
	    process_file ( p ) ;
	    break ;
	}
    }

    /* Analyse sub-dependencies */
    p->mark = 2 ;
    for ( d = p->dep ; d != NULL ; d = d->next ) {
	find_dependency ( d->file, depth + 1 ) ;
    }
    p->mark = 1 ;
    return ;
}
