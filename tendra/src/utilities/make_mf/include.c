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
#include "tokens.h"


/*
    CURRENT PATHNAME

    This variable gives the pathname structure corresponding to the
    current input file.
*/

PATHNAME *crt_pathname = NULL ;


/*
    READ AN INCLUSION STRING

    This routine reads and analyses the string following a '#include' in
    the file f.  qo is true for quoted strings and false for angle bracket
    strings.
*/

static void read_incl_string
    PROTO_N ( ( f, qo ) )
    PROTO_T ( FILE *f X int qo )
{
    int c ;
    PATHNAME *p ;
    char buff [1000] ;
    char *s = buff ;
    int qc = ( qo ? '"' : '>' ) ;

    /* Read the string */
    while ( c = getc ( f ), c != qc ) {
	if ( c == EOF ) {
	    error ( ERROR_WARNING, "End of file in string" ) ;
	    break ;
	} else if ( c == '\n' ) {
	    error ( ERROR_WARNING, "End of line in string" ) ;
	    IGNORE ungetc ( c, f ) ;
	    break ;
	}
	*( s++ ) = ( char ) c ;
    }
    *s = 0 ;

    /* Create the dependency */
    p = search_pathname ( incl_dirs, buff, qo ) ;
    if ( p ) {
	add_dependency ( crt_pathname, p ) ;
	add_dependency ( h_files, p ) ;
    }
    return ;
}


/*
    MACHINE STATES

    These values give the various states for the machine used to scan for
    '#include' directives.
*/

#define STATE_NONE			0
#define STATE_NEWLINE			1
#define STATE_PREPROC			2
#define STATE_INCLUDE_I			3
#define STATE_INCLUDE_N			4
#define STATE_INCLUDE_C			5
#define STATE_INCLUDE_L			6
#define STATE_INCLUDE_U			7
#define STATE_INCLUDE_D			8
#define STATE_INCLUDE_E			9
#define STATE_STRING			10


/*
    PROCESS C SOURCE FILE

    This routine analyses the dependencies for the C source, or similar,
    file given by p.  The file parsing algorithms are rather simple.
*/

void process_file
    PROTO_N ( ( p ) )
    PROTO_T ( PATHNAME *p )
{
    int c ;
    FILE *f ;
    char *nm = p->full ;
    int state = STATE_NEWLINE ;

    /* Open the input file */
    crt_line_no = 1 ;
    crt_file_name = nm ;
    f = fopen ( nm, "r" ) ;
    if ( f == NULL ) {
	if ( p->exists == 0 ) {
	    error ( ERROR_SERIOUS, "Can't open input file, '%s'", nm ) ;
	    p->exists = 1 ;
	}
	crt_file_name = NULL ;
	return ;
    }
    crt_pathname = p ;

    while ( c = getc ( f ), c != EOF ) {

	switch ( c ) {

	    case ' ' :
	    case '\t' :
	    case '\f' :
	    case '\v' : {
		/* White space */
		if ( state >= STATE_INCLUDE_I &&
		     state < STATE_INCLUDE_E ) {
		    state = STATE_NONE ;
		} else {
		    /* state unchanged */
		}
		break ;
	    }

	    case '\n' : {
		/* New lines */
		state = STATE_NEWLINE ;
		crt_line_no++ ;
		break ;
	    }

	    case '\\' : {
		/* Escaped newlines */
		c = getc ( f ) ;
		if ( c == '\n' ) {
		    /* state unchanged */
		    crt_line_no++ ;
		} else {
		    IGNORE ungetc ( c, f ) ;
		    goto default_lab ;
		}
		break ;
	    }

	    case '/' : {
		/* Comments */
		c = getc ( f ) ;
		if ( c == '*' ) {
		    int comment = 0 ;
		    while ( comment != 2 ) {
			c = getc ( f ) ;
			if ( c == EOF ) {
			    error ( ERROR_WARNING, "End of file in comment" ) ;
			    break ;
			} else if ( c == '\n' ) {
			    crt_line_no++ ;
			    comment = 0 ;
			} else if ( c == '*' ) {
			    comment = 1 ;
			} else if ( comment == 1 && c == '/' ) {
			    comment = 2 ;
			} else {
			    comment = 0 ;
			}
		    }
		} else if ( c == '/' ) {
		    do {
			c = getc ( f ) ;
			if ( c == EOF ) {
			    error ( ERROR_WARNING, "End of file in comment" ) ;
			    break ;
			}
		    } while ( c != '\n' ) ;
		    crt_line_no++ ;
		} else {
		    IGNORE ungetc ( c, f ) ;
		    goto default_lab ;
		}
		if ( state >= STATE_INCLUDE_I && state < STATE_INCLUDE_E ) {
		    state = STATE_NONE ;
		} else {
		    /* state unchanged */
		}
		break ;
	    }

	    case '#' : {
		/* Hash symbol */
		if ( state != STATE_NEWLINE ) goto default_lab ;
		state = STATE_PREPROC ;
		break ;
	    }

	    case 'i' : {
		/* The i of include */
		if ( state != STATE_PREPROC ) goto default_lab ;
		state = STATE_INCLUDE_I ;
		break ;
	    }

	    case 'n' : {
		/* The n of include */
		if ( state != STATE_INCLUDE_I ) goto default_lab ;
		state = STATE_INCLUDE_N ;
		break ;
	    }

	    case 'c' : {
		/* The c of include */
		if ( state != STATE_INCLUDE_N ) goto default_lab ;
		state = STATE_INCLUDE_C ;
		break ;
	    }

	    case 'l' : {
		/* The l of include */
		if ( state != STATE_INCLUDE_C ) goto default_lab ;
		state = STATE_INCLUDE_L ;
		break ;
	    }

	    case 'u' : {
		/* The u of include */
		if ( state != STATE_INCLUDE_L ) goto default_lab ;
		state = STATE_INCLUDE_U ;
		break ;
	    }

	    case 'd' : {
		/* The d of include */
		if ( state != STATE_INCLUDE_U ) goto default_lab ;
		state = STATE_INCLUDE_D ;
		break ;
	    }

	    case 'e' : {
		/* The e of include */
		if ( state != STATE_INCLUDE_D ) goto default_lab ;
		state = STATE_INCLUDE_E ;
		break ;
	    }

	    case '<' : {
		if ( state != STATE_INCLUDE_E ) goto default_lab ;
		read_incl_string ( f, 0 ) ;
		state = STATE_STRING ;
		break ;
	    }

	    case '"' : {
		if ( state != STATE_INCLUDE_E ) goto skip_string_lab ;
		read_incl_string ( f, 1 ) ;
		state = STATE_STRING ;
		break ;
	    }

	    case '\'' :
	    skip_string_lab : {
		/* Normal string literals */
		int escaped = 0 ;
		int qo = c ;
		do {
		    c = getc ( f ) ;
		    if ( c == EOF ) {
			error ( ERROR_WARNING, "End of file in string" ) ;
			break ;
		    }
		    if ( escaped ) {
			escaped = 0 ;
			if ( c == '\n' ) crt_line_no++ ;
			c = 'x' ;
		    } else {
			if ( c == '\\' ) escaped = 1 ;
			if ( c == '\n' ) {
			    error ( ERROR_WARNING, "End of line in string" ) ;
			    IGNORE ungetc ( c, f ) ;
			    break ;
			}
		    }
		} while ( c != qo ) ;
		goto default_lab ;
	    }

	    default :
	    default_lab : {
		if ( state == STATE_INCLUDE_E ) {
		    error ( ERROR_WARNING,
			    "Unrecognised '#include' directive" ) ;
		} else if ( state == STATE_STRING ) {
		    error ( ERROR_WARNING,
			    "End of '#include' directive expected" ) ;
		}
		state = STATE_NONE ;
		break ;
	    }
	}
    }

    /* Close the input file */
    fclose_v ( f ) ;
    crt_file_name = NULL ;
    crt_pathname = NULL ;
    return ;
}


/*
    TEST WHETHER A FILE EXISTS

    This routine tests whether the file given by the pathname p exists.
*/

void test_file
    PROTO_N ( ( p ) )
    PROTO_T ( PATHNAME *p )
{
    if ( p->exists == 0 ) {
	char *nm = p->full ;
	FILE *f = fopen ( nm, "r" ) ;
	if ( f == NULL ) {
	    crt_line_no = 1 ;
	    crt_file_name = nm ;
	    error ( ERROR_SERIOUS, "Can't open input file, '%s'", nm ) ;
	    crt_file_name = NULL ;
	    p->exists = 1 ;
	    return ;
	}
	fclose_v ( f ) ;
    }
    return ;
}
