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


/*
    OUTPUT VARIABLES

    The variable max_column controls the maximum width of the output.  The
    flag dos_output determines whether filenames are output in DOS form.
*/

int max_column = 75 ;
int dos_output = 0 ;
int relative_output = 0 ;


/*
    STRING LENGTH

    This macro finds the length of a string, converting the result to an
    int.
*/

#define length( S )	( ( int ) strlen ( S ) )


/*
    PRINT A PATHNAME

    This routine prints the pathname p to the file f, substituting any
    aliases.
*/

static void output_pathname
    PROTO_N ( ( p, f ) )
    PROTO_T ( PATHNAME *p X FILE *f )
{
    char *a = p->alias ;
    if ( a ) {
	fputc_v ( '$', f ) ;
	fputc_v ( '{', f ) ;
	fputs_v ( a, f ) ;
	fputc_v ( '}', f ) ;
    } else {
	char *c = p->name ;
	int sep = ( dos_output ? '\\' : '/' ) ;
	if ( p == root_dir ) {
	    fputs_v ( c, f ) ;
	    fputc_v ( sep, f ) ;
	} else if ( p == anonymous_dir ) {
	    fputs_v ( ".", f ) ;
	} else {
	    PATHNAME *q = p->up ;
	    if ( q != anonymous_dir ) {
		if ( q == root_dir && q->alias == NULL ) {
		    /* Root directory */
		} else {
		    output_pathname ( q, f ) ;
		}
		fputc_v ( sep, f ) ;
	    }
	    fputs_v ( c, f ) ;
	}
    }
    return ;
}


/*
    FIND THE LENGTH OF A PATHNAME

    This routine calculates the number of characters printed by a call to
    output_pathname with argument p.
*/

static int length_pathname
    PROTO_N ( ( p ) )
    PROTO_T ( PATHNAME *p )
{
    int len ;
    char *a = p->alias ;
    if ( a ) {
	len = length ( a ) + 3 ;
    } else {
	char *c = p->name ;
	if ( p == root_dir ) {
	    len = length ( c ) + 1 ;
	} else if ( p == anonymous_dir ) {
	    len = 1 ;
	} else {
	    PATHNAME *q = p->up ;
	    if ( q == anonymous_dir ) {
		/* Anonymous directory */
		len = 0 ;
	    } else if ( q == root_dir && q->alias == NULL ) {
		/* Root directory */
		len = 1 ;
	    } else {
		len = length_pathname ( q ) + 1 ;
	    }
	    len += length ( c ) ;
	}
    }
    return ( len ) ;
}


/*
    PRINT A PATHNAME

    This routine calls output_pathname, printing a preceding space if ns
    is true and taking the column number col into account.  It returns
    the new column number.
*/

static int output_path
    PROTO_N ( ( p, col, ns, f ) )
    PROTO_T ( PATHNAME *p X int col X int ns X FILE *f )
{
    int len = length_pathname ( p ) + 1 ;
    if ( col + len >= max_column ) {
	fputs_v ( "\\\n", f ) ;
	col = 0 ;
	ns = 1 ;
    }
    if ( ns ) fputc_v ( ' ', f ) ;
    output_pathname ( p, f ) ;
    return ( col + len ) ;
}


/*
    PRINT ALL ALIASES

    This routine scans through all the files beneath p, printing any alias
    definitions to f.  Note how any alias is temporarily suspended when
    printing the definition.
*/

static void output_aliases
    PROTO_N ( ( p, f ) )
    PROTO_T ( PATHNAME *p X FILE *f )
{
    if ( p ) {
	char *a = p->alias ;
	output_aliases ( p->next, f ) ;
	if ( a && p != anonymous_dir ) {
	    p->alias = NULL ;
	    fputs_v ( a, f ) ;
	    fputc_v ( '=', f ) ;
	    if ( relative_output && p->quote ) {
		fputs_v ( p->quote, f ) ;
	    } else {
		output_pathname ( p, f ) ;
	    }
	    fputc_v ( '\n', f ) ;
	    p->alias = a ;
	}
	output_aliases ( p->sub, f ) ;
    }
    return ;
}


/*
    PRINT A LIST OF OPTIONS

    This routine prints the list of options d to the file f.  Each option
    is printed only if it appears in the string opts.  col gives the initial
    column number, and ns is true to indicate that a space needs to be
    printed.  The final column number is returned.
*/

static int output_opts
    PROTO_N ( ( d, opts, col, ns, f ) )
    PROTO_T ( OPTION *d X char *opts X int col X int ns X FILE *f )
{
    while ( d != NULL ) {
	char *s = d->opt ;
	if ( strchr ( opts, s [1] ) ) {
	    int len = length ( s ) + 1 ;
	    if ( col + len >= max_column ) {
		fputs_v ( "\\\n", f ) ;
		col = 0 ;
		ns = 1 ;
	    }
	    if ( ns ) fputc_v ( ' ', f ) ;
	    fputs_v ( s, f ) ;
	    col += len ;
	    ns = 1 ;
	}
	d = d->next ;
    }
    return ( col ) ;
}


/*
    PRINT A LIST OF DIRECTORIES

    This routine prints the list of directories d to the file f.  Each
    directory is prefixed by the string pre.  col gives the initial
    column number, and ns is true to indicate that a space needs to be
    printed.  The final column number is returned.
*/

static int output_dirs
    PROTO_N ( ( d, pre, post, col, ns, f ) )
    PROTO_T ( DIRECTORY *d X char *pre X char *post X int col X int ns X FILE *f )
{
    while ( d != NULL ) {
	if ( d->builtin == 0 ) {
	    PATHNAME *p = d->dir ;
	    int len = length_pathname ( p ) ;
	    len = length ( pre ) + len + length ( post ) + 1 ;
	    if ( col + len >= max_column ) {
		fputs_v ( "\\\n", f ) ;
		col = 0 ;
		ns = 1 ;
	    }
	    if ( ns ) fputc_v ( ' ', f ) ;
	    fputs_v ( pre, f ) ;
	    output_pathname ( p, f ) ;
	    fputs_v ( post, f ) ;
	    col += len ;
	    ns = 1 ;
	}
	d = d->next ;
    }
    return ( col ) ;
}


/*
    PRINT A SERIES OF DEPENDENCIES

    This routine prints all the dependencies for the pathname p.  If rec
    is true then these dependencies are expanded recursively.
*/

static int output_deps
    PROTO_N ( ( p, rec, col, ns, f ) )
    PROTO_T ( PATHNAME *p X int rec X int col X int ns X FILE *f )
{
    if ( rec ) {
	DEPENDENCY *d ;
	static int recursive_mark = 10 ;
	for ( d = p->dep ; d != NULL ; d = d->next ) {
	    PATHNAME *q = d->file ;
	    if ( q->mark != recursive_mark ) {
		col = output_path ( q, col, ns, f ) ;
		q->mark = recursive_mark ;
		ns = 1 ;
	    }
	}
	for ( d = p->dep ; d != NULL ; d = d->next ) {
	    PATHNAME *q = d->file ;
	    col = output_deps ( q, 2, col, ns, f ) ;
	    ns = 1 ;
	}
	if ( rec == 1 ) recursive_mark++ ;
    } else {
	DEPENDENCY *d ;
	for ( d = p->dep ; d != NULL ; d = d->next ) {
	    PATHNAME *q = d->file ;
	    col = output_path ( q, col, ns, f ) ;
	    ns = 1 ;
	}
    }
    return ( col ) ;
}


/*
    CURRENT PATHNAME

    This variable holds the current loop counter.
*/

static PATHNAME *crt_file = NULL ;


/*
    FIND ALL FILES OF A TYPE

    This routine returns the file giving all files of type c.
*/

static PATHNAME *all_files
    PROTO_N ( ( c ) )
    PROTO_T ( int c )
{
    switch ( c ) {
	case 'o' : return ( o_files ) ;
	case 'c' : return ( c_files ) ;
	case 'j' : return ( j_files ) ;
	case 'k' : return ( k_files ) ;
	case 'h' : return ( h_files ) ;
	case 'l' : return ( l_files ) ;
	case 'y' : return ( y_files ) ;
	case 'L' : return ( l_output ) ;
	case 'Y' : return ( y_output ) ;
    }
    return ( NULL ) ;
}


/*
    PRINT A RULE DEFINITION

    This routine prints the rule definition given by the string str
    to the file f.
*/

static void output_rule
    PROTO_N ( ( str, f ) )
    PROTO_T ( char *str X FILE *f )
{
    char c ;
    int ns = 0 ;
    int col = 0 ;

    /* Scan through string */
    while ( c = *( str++ ), c != 0 ) {
	if ( c == '%' ) {
	    /* Format characters */
	    c = *( str++ ) ;
	    switch ( c ) {

		case 'C' : {
		    /* Current working directory */
		    col = output_path ( current_dir, col, ns, f ) ;
		    ns = 0 ;
		    break ;
		}

		case 'F' : {
		    /* Include directories */
		    col = output_dirs ( incl_dirs, "", "/*.c", col, ns, f ) ;
		    ns = 0 ;
		    break ;
		}

		case 'H' : {
		    /* Home directory */
		    col = output_path ( home_dir, col, ns, f ) ;
		    ns = 0 ;
		    break ;
		}

		case 'I' : {
		    /* Include directories */
		    col = output_dirs ( incl_dirs, "-I", "", col, ns, f ) ;
		    ns = 0 ;
		    break ;
		}

		case 'L' : {
		    /* Library directories */
		    col = output_dirs ( lib_dirs, "-L", "", col, ns, f ) ;
		    ns = 0 ;
		    break ;
		}

		case 'O' : {
		    /* Output name */
		    col = output_path ( output_file, col, ns, f ) ;
		    ns = 0 ;
		    break ;
		}

		case 'W' : {
		    /* Work directory */
		    col = output_path ( work_dir, col, ns, f ) ;
		    ns = 0 ;
		    break ;
		}

		case 'B' : {
		    /* Current file basename */
		    if ( crt_file ) {
			char *nm = crt_file->name ;
			int len = length ( nm ) ;
			if ( col + len >= max_column ) {
			    fputs_v ( "\\\n", f ) ;
			    col = 0 ;
			    ns = 1 ;
			}
			if ( ns ) fputc_v ( ' ', f ) ;
			fputs_v ( nm, f ) ;
			col += len + ns ;
			ns = 0 ;
		    }
		    break ;
		}

		case 'D' : {
		    /* Current file directory */
		    if ( crt_file ) {
			col = output_path ( crt_file->up, col, ns, f ) ;
			ns = 0 ;
		    }
		    break ;
		}

		case 'X' : {
		    /* Current file */
		    if ( crt_file ) {
			col = output_path ( crt_file, col, ns, f ) ;
			ns = 0 ;
		    }
		    break ;
		}

		case 'Y' : {
		    /* Current file dependencies */
		    if ( crt_file ) {
			col = output_deps ( crt_file, 0, col, ns, f ) ;
			ns = 0 ;
		    }
		    break ;
		}

		case 'Z' : {
		    /* Current file dependencies (recursive) */
		    if ( crt_file ) {
			col = output_deps ( crt_file, 1, col, ns, f ) ;
			ns = 0 ;
		    }
		    break ;
		}

		case '[' : {
		    /* Options matching a pattern */
		    char *begin = str + 1 ;
		    char *end = strchr ( begin, ']' ) ;
		    if ( end == NULL ) {
			error ( ERROR_SERIOUS, "Unterminated escape" ) ;
		    } else {
			*end = 0 ;
			col = output_opts ( cmd_opts, str, col, ns, f ) ;
			*end = ']' ;
			str = end + 1 ;
		    }
		    ns = 0 ;
		    break ;
		}

		default : {
		    PATHNAME *p = all_files ( c ) ;
		    if ( p ) {
			/* All files of a type */
			col = output_deps ( p, 0, col, ns, f ) ;
			ns = 0 ;
		    } else {
			/* Unknown escape sequences */
			error ( ERROR_SERIOUS, "Unknown escape, '%%%c'", c ) ;
			str-- ;
		    }
		    break ;
		}
	    }

	} else if ( c == '\\' ) {
	    /* Escape sequences */
	    c = *( str++ ) ;
	    switch ( c ) {
		case 'n' : {
		    /* Newline */
		    fputc_v ( '\n', f ) ;
		    col = 0 ;
		    ns = 0 ;
		    break ;
		}
		case 't' : {
		    /* Tab */
		    fputc_v ( '\t', f ) ;
		    col = 8 * ( col / 8 ) + 8 ;
		    while ( c = *str, ( c == ' ' || c == '\t' ) ) {
			str++ ;
		    }
		    ns = 0 ;
		    break ;
		}
		case ':' :
		case '%' :
		case '\\' : {
		    /* Simple escape sequences */
		    goto print_character ;
		}
		default : {
		    /* Unknown escape sequences */
		    error ( ERROR_SERIOUS, "Unknown escape, '\\%c'", c ) ;
		    str-- ;
		    break ;
		}
	    }

	} else if ( c == ' ' || c == '\t' ) {
	    /* Spaces */
	    ns = 1 ;

	} else {
	    /* Other characters */
	    print_character : {
		if ( ns ) {
		    if ( col >= max_column - 10 ) {
			fputs_v ( "\\\n", f ) ;
			col = 0 ;
		    }
		    fputc_v ( ' ', f ) ;
		    ns = 0 ;
		    col++ ;
		}
		fputc_v ( c, f ) ;
		col++ ;
	    }
	}
    }
    fputc_v ( '\n', f ) ;
    return ;
}


/*
    MAIN OUTPUT ROUTINE

    This routine prints all the output to the file f.
*/

void output_all
    PROTO_N ( ( f ) )
    PROTO_T ( FILE *f )
{
    int n = 0 ;
    OPTION *p = rule_opts ;
    OPTION *lab_stack [20] ;
    DEPENDENCY *dep_stack [20] ;
    lab_stack [0] = NULL ;
    dep_stack [0] = NULL ;

    /* Print file header */
    fprintf_v ( f, "# Automatically generated by %s version %s\n",
		progname, progvers ) ;

    /* Print file alias definitions */
    fputs_v ( "\n# Standard directories and files\n", f ) ;
    output_aliases ( root_dir, f ) ;
    fputc_v ( '\n', f ) ;

    /* Print rule definitions */
    while ( p != NULL ) {
	char *opt = p->opt ;
	if ( opt [0] == ':' ) {
	    /* Labels */
	    if ( opt [2] == 0 ) {
		if ( opt [1] == '<' || opt [1] == '>' ) {
		    /* End of loop */
		    if ( n == 0 ) {
			error ( ERROR_SERIOUS, "Unexpected end of loop" ) ;
		    } else if ( dep_stack [n] && opt [1] == '<' ) {
			/* Go back to start of loop */
			dep_stack [n] = dep_stack [n]->next ;
			if ( dep_stack [n] ) {
			    crt_file = dep_stack [n]->file ;
			} else {
			    crt_file = NULL ;
			}
			p = lab_stack [n] ;
		    } else {
			/* Continue to next statement */
			n-- ;
			if ( n && dep_stack [n] ) {
			    crt_file = dep_stack [n]->file ;
			} else {
			    crt_file = NULL ;
			}
		    }
		} else {
		    /* Start of loop */
		    DEPENDENCY *d = NULL ;
		    if ( opt [1] == 'x' ) {
			if ( crt_file ) d = crt_file->dep ;
		    } else {
			/* Start of loop */
			PATHNAME *q = all_files ( opt [1] ) ;
			if ( q ) {
			    d = q->dep ;
			} else {
			    error ( ERROR_SERIOUS,
				    "Unknown label, '%s'", opt ) ;
			}
		    }
		    n++ ;
		    if ( n >= 20 ) {
			error ( ERROR_SERIOUS, "Label depth too great" ) ;
			break ;
		    }
		    dep_stack [n] = d ;
		    lab_stack [n] = p ;
		    if ( d ) {
			crt_file = d->file ;
		    } else {
			crt_file = NULL ;
		    }
		}
	    } else {
		error ( ERROR_SERIOUS, "Unknown label, '%s'", opt ) ;
	    }
	} else {
	    /* Rules */
	    if ( n == 0 || dep_stack [n] ) output_rule ( opt, f ) ;
	}
	p = p->next ;
    }
    return ;
}
