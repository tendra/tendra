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
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>
#include "types.h"
#include "error.h"
#include "path.h"
#include "xalloc.h"


/*
    DOS PATHNAME FLAG

    This flag is set to true if allowance is to be made for DOS pathnames.
*/

int dos_pathname = 0 ;


/*
    STANDARD PATHNAMES

    These pathnames represent the root directory, '/', and the current
    working directory, '.', and the working directory.
*/

PATHNAME *root_dir = NULL ;
PATHNAME *current_dir = NULL ;
PATHNAME *home_dir = NULL ;
PATHNAME *work_dir = NULL ;
PATHNAME *anonymous_dir = NULL ;
PATHNAME *nonexistant_dir = NULL ;
PATHNAME *output_file = NULL ;
PATHNAME *o_files = NULL ;
PATHNAME *c_files = NULL ;
PATHNAME *h_files = NULL ;
PATHNAME *j_files = NULL ;
PATHNAME *k_files = NULL ;
PATHNAME *l_files = NULL ;
PATHNAME *y_files = NULL ;
PATHNAME *l_output = NULL ;
PATHNAME *y_output = NULL ;


/*
    FILE SUFFIXES

    These variables give various file name suffixes.
*/
    
char *cpp_suffix = "cc" ;
char *k_suffix = "k" ;


/*
    CREATE A SOURCE DIRECTORY ALIAS

    This routine creates an alias for a source, or similar, directory.  The
    first alias generated has the form 'SRC', subsequent aliases being
    'SRC2', 'SRC3' etc.
*/

char *src_alias
    PROTO_N ( ( n ) )
    PROTO_T ( int n )
{
    char *aka ;
    static int src_no [2] = { 1, 1 } ;
    static char *src_name [2] = { "SRC", "LIB" } ;
    if ( src_no [n] == 1 ) {
	aka = src_name [n] ;
    } else {
	char buff [20] ;
	sprintf_v ( buff, "%s%d", src_name [n], src_no [n] ) ;
	aka = xstrcpy ( buff ) ;
    }
    ( src_no [n] )++ ;
    return ( aka ) ;
}


/*
    PATHNAME BUFFER

    This buffer is used in make_pathname to split the input filename into
    its components.
*/

char pathbuff [2000] ;


/*
    ALLOCATE A NEW PATHNAME

    This routine allocates a new pathname structure with name component nm
    and full name fnm.
*/

static PATHNAME *new_pathname
    PROTO_N ( ( nm, fnm ) )
    PROTO_T ( char *nm X char *fnm )
{
    char *suff ;
    PATHNAME *p ;
    static int pathnames_left = 0 ;
    static PATHNAME *pathnames_free = NULL ;
    if ( pathnames_left == 0 ) {
	pathnames_left = 200 ;
	pathnames_free = xmalloc_nof ( PATHNAME, pathnames_left ) ;
    }
    p = pathnames_free + ( --pathnames_left ) ;
    p->name = xstrcpy ( nm ) ;
    suff = strrchr ( p->name, '.' ) ;
    p->suffix = ( suff ? suff + 1 : "" ) ;
    p->full = xstrcpy ( fnm ) ;
    p->quote = NULL ;
    p->alias = NULL ;
    p->dep = NULL ;
    p->mark = 0 ;
    p->exists = 0 ;
    p->up = NULL ;
    p->sub = NULL ;
    p->next = NULL ;
    return ( p ) ;
}


/*
    CREATE A PATHNAME COMPONENT

    This routine searches for a pathname with directory component p and
    filename bnm.  fnm gives the associated complete path.  If cr is true
    then the file is created if it does not already exist, otherwise
    the null pointer is returned.
*/

PATHNAME *find_pathname
    PROTO_N ( ( p, bnm, fnm, cr ) )
    PROTO_T ( PATHNAME *p X char *bnm X char *fnm X int cr )
{
    PATHNAME *q = p ;
    char *str = bnm ;
    do {
	char *s = strchr ( str, '/' ) ;
	if ( s ) *s = 0 ;
	if ( streq ( str, "" ) ) {
	    /* No effect */
	} else if ( streq ( str, "." ) ) {
	    /* No effect */
	} else if ( streq ( str, ".." ) ) {
	    /* Go up one level */
	    q = q->up ;
	} else if ( streq ( str, "..." ) ) {
	    /* Anonymous directory */
	    q = anonymous_dir ;
	} else {
	    /* Search for component */
	    PATHNAME *r ;
	    for ( r = q->sub ; r != NULL ; r = r->next ) {
		if ( streq ( str, r->name ) ) break ;
	    }
	    if ( r == NULL ) {
		/* Create component */
		if ( !cr ) {
		    if ( s ) *s = '/' ;
		    return ( NULL ) ;
		}
		r = new_pathname ( str, fnm ) ;
		r->up = q ;
		r->next = q->sub ;
		q->sub = r ;
	    }
	    q = r ;
	}
	if ( s ) *( s++ ) = '/' ;
	str = s ;
    } while ( str != NULL ) ;
    return ( q ) ;
}


/*
    CREATE A PATHNAME

    This routine creates a pathname structure for a file named fnm.  If
    eq is true then fnm may be prefixed by an alias identifier, for example
    "alias=file".
*/

PATHNAME *make_pathname
    PROTO_N ( ( fnm, eq ) )
    PROTO_T ( char *fnm X int eq )
{
    PATHNAME *p ;
    char *str = pathbuff ;
    char *aka = NULL ;

    /* Copy fnm into path buffer */
    if ( fnm != str ) {
	if ( strlen ( fnm ) >= sizeof ( pathbuff ) ) {
	    error ( ERROR_SERIOUS, "Pathname '%s' too long", fnm ) ;
	    return ( root_dir ) ;
	}
	strcpy_v ( str, fnm ) ;
    }

    /* Check for aliases */
    while ( *str == ' ' || *str == '\t' ) str++ ;
    if ( eq ) {
	char *eqs = strchr ( str, '=' ) ;
	if ( eqs ) {
	    *eqs = 0 ;
	    aka = xstrcpy ( str ) ;
	    str = eqs + 1 ;
	}
    }

    /* Allow for DOS pathnames */
    if ( dos_pathname ) {
	char c ;
	char *s = str ;

	/* Deal with separators */
	while ( c = *s, c != 0 ) {
	    if ( c == '\\' ) *s = '/' ;
	    s++ ;
	}

	/* Deal with disk letters */
	if ( isalpha ( str [0] ) && str [1] == ':' ) {
	    if ( str [0] != 'c' ) {
		error ( ERROR_SERIOUS, "Bad disk letter, '%c'", str [0] ) ;
	    }
	    if ( str [2] == '/' ) {
		str += 2 ;
	    } else {
		str [1] = '/' ;
		str++ ;
	    }
	}
    }

    /* Create result */
    p = ( str [0] == '/' ? root_dir : current_dir ) ;
    p = find_pathname ( p, str, str, 1 ) ;
    if ( str [0] != '/' ) p->quote = xstrcpy ( str ) ;
    if ( p->alias == NULL ) p->alias = aka ;
    return ( p ) ;
}


/*
    CREATE A DERIVED PATHNAME

    This routine creates a pathname in the directory p with name derived
    from q, but with its existing suffix replaced by suff.  
*/

PATHNAME *derived_pathname
    PROTO_N ( ( p, q, suff ) )
    PROTO_T ( PATHNAME *p X PATHNAME *q X char *suff )
{
    int n ;
    char *pnm = pathbuff ;
    sprintf_v ( pnm, "%s/%s", p->full, q->name ) ;
    n = ( int ) strlen ( pnm ) - ( int ) strlen ( q->suffix ) ;
    strcpy_v ( pnm + n, suff ) ;
    n = ( int ) strlen ( p->full ) + 1 ;
    return ( find_pathname ( p, pnm + n, pnm, 1 ) ) ;
}


/*
    INITIALISE THE STANDARD PATHNAMES

    This routine sets up the standard pathnames for the root and current
    directories.
*/

void init_pathname
    PROTO_Z ()
{
    char *d ;

    /* Find the root directory */
    root_dir = new_pathname ( "", "/" ) ;
    root_dir->up = root_dir ;

    /* Find the current directory */
    current_dir = root_dir ;
    d = getcwd ( pathbuff, ( int ) sizeof ( pathbuff ) ) ;
    if ( d == NULL ) {
	error ( ERROR_WARNING, "Can't find current directory" ) ;
    } else {
	current_dir = make_pathname ( d, 0 ) ;
    }

    /* Find the home directory */
    d = getenv ( "HOME" ) ;
    if ( d == NULL ) {
	home_dir = root_dir ;
    } else {
	home_dir = make_pathname ( d, 0 ) ;
    }

    /* Set up other files and directories */
    work_dir = current_dir ;
    nonexistant_dir = make_pathname ( "/****", 0 ) ;
    anonymous_dir = make_pathname ( "/****", 0 ) ;
    output_file = make_pathname ( "a.out", 0 ) ;

    /* Groups of files */
    o_files = make_pathname ( "/****/****.o", 0 ) ;
    c_files = make_pathname ( "/****/****.c", 0 ) ;
    h_files = make_pathname ( "/****/****.h", 0 ) ;
    j_files = make_pathname ( "/****/****.j", 0 ) ;
    k_files = make_pathname ( "/****/****.k", 0 ) ;
    l_files = make_pathname ( "/****/****.l", 0 ) ;
    y_files = make_pathname ( "/****/****.y", 0 ) ;
    l_output = make_pathname ( "/****/*****.l", 0 ) ;
    y_output = make_pathname ( "/****/*****.y", 0 ) ;
    return ;
}
