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
#include "tdf.h"
#include "cmd_ops.h"
#include "spec_ops.h"
#include "error.h"
#include "input.h"
#include "lex.h"
#include "syntax.h"
#include "xalloc.h"


/*
    INPUT FILE

    This is the file from which the lexical routine read their input.
*/

static FILE *lex_input ;


/*
    PENDING BUFFER

    Pending characters are dealt with by means of this buffer.  pending
    is set to the start of the buffer to indicate that there are no
    characters pending, otherwise the pending characters are stored in
    the buffer.  The buffer may need increasing in size if the look-ahead
    required by the lexical analyser increases.
*/

static int pending_buff [12] = { '?' } ;
static int *pending = pending_buff ;


/*
    MAPPINGS AND DECLARATIONS FOR AUTOMATICALLY GENERATED SECTION

    These macros give the mappings between the actions used in the
    automatically generated lexical analyser and the routines defined
    in this file.
*/

static int read_char PROTO_S ( ( void ) ) ;
static int read_comment PROTO_S ( ( void ) ) ;
static int read_identifier PROTO_S ( ( int ) ) ;
static int read_number PROTO_S ( ( int ) ) ;

#define get_comment( A )	read_comment ()
#define get_identifier( A )	read_identifier ( ( A ) )
#define get_number( A )		read_number ( ( A ) )
#define unknown_token( A )	lex_unknown
#define unread_char( A )	*( ++pending ) = ( A )


/*
    AUTOMATICALLY GENERATED SECTION

    The main body of the lexical analyser is automatically generated.
*/

#include "lexer.h"


/*
    GET THE NEXT CHARACTER

    This routine reads the next character, either from the pending buffer
    or from the input file.
*/

static int read_char
    PROTO_Z ()
{
    int c ;
    if ( pending != pending_buff ) {
	c = *( pending-- ) ;
    } else {
	c = fgetc ( lex_input ) ;
	if ( c == '\n' ) crt_line_no++ ;
	if ( c == EOF ) return ( LEX_EOF ) ;
	c &= 0xff ;
    }
    return ( c ) ;
}


/*
    TOKEN BUFFER

    This buffer is used by read_token to hold the values of identifiers.
    Similarly token_value is used to hold the values of numbers.
*/

char token_buff [2000] ;
static char *token_end = token_buff + sizeof ( token_buff ) ;
char *first_comment = NULL ;
unsigned token_value = 0 ;


/*
    READ AN IDENTIFIER

    This routine reads an identifier beginning with a, returning the
    corresponding lexical token.  Keywords are dealt with locally.
*/

static int read_identifier
    PROTO_N ( ( a ) )
    PROTO_T ( int a )
{
    int c = a, cl ;
    char *t = token_buff ;
    do {
	*( t++ ) = ( char ) c ;
	if ( t == token_end ) error ( ERROR_FATAL, "Buffer overflow" ) ;
	c = read_char () ;
	cl = lookup_char ( c ) ;
    } while ( is_alphanum ( cl ) ) ;
    *t = 0 ;
    unread_char ( c ) ;

    /* Deal with keywords */
    t = token_buff ;
#define MAKE_KEYWORD( A, B )\
    if ( streq ( t, ( A ) ) ) return ( B ) ;
#include "keyword.h"
    return ( lex_name ) ;
}


/*
    READ A NUMBER

    This routine reads a number.  It is entered after the initial digit,
    a, has been read.  The number's value is stored in token_value.
*/

static int read_number
    PROTO_N ( ( a ) )
    PROTO_T ( int a )
{
    int c = a, cl ;
    unsigned n = 0 ;
    do {
	unsigned m = 10 * n + ( unsigned ) ( c - '0' ) ;
	if ( m < n ) error ( ERROR_SERIOUS, "Number overflow" ) ;
	n = m ;
	c = read_char () ;
	cl = lookup_char ( c ) ;
    } while ( is_digit ( cl ) ) ;
    unread_char ( c ) ;
    token_value = n ;
    return ( lex_number ) ;
}


/*
    READ A COMMENT

    This routine reads a shell style comment.  It is entered after the
    initial hash character has been read.
*/

static int read_comment
    PROTO_Z ()
{
    int c ;
    char *t = token_buff ;
    do {
	*( t++ ) = ' ' ;
	if ( t == token_end ) t = token_buff ;
	*( t++ ) = '*' ;
	if ( t == token_end ) t = token_buff ;
	do {
	    c = read_char () ;
	    if ( c == LEX_EOF ) {
		error ( ERROR_SERIOUS, "End of file in comment" ) ;
		return ( lex_eof ) ;
	    }
	    *( t++ ) = ( char ) c ;
	    if ( t == token_end ) t = token_buff ;
	} while ( c != '\n' ) ;
	c = read_char () ;
    } while ( c == '#' ) ;
    unread_char ( c ) ;
    *t = 0 ;
    if ( first_comment == 0 ) first_comment = xstrcpy ( token_buff ) ;
    return ( read_token () ) ;
}


/*
    GET A COMMAND FROM A STRING

    This routine returns the address of the first non-white space character
    from the string ps.  It returns the null pointer if the end of the line
    is reached.
*/

static char *get_command
    PROTO_N ( ( ps ) )
    PROTO_T ( char **ps )
{
    char *t = *ps ;
    char *s = t ;
    if ( s ) {
	char c ;
	while ( c = *s, ( c == ' ' || c == '\t' || c == '\r' ) ) {
	    *s = 0 ;
	    s++ ;
	}
	if ( c == '#' || c == '\n' || c == 0 ) {
	    *s = 0 ;
	    *ps = NULL ;
	    return ( NULL ) ;
	}
	t = s ;
	while ( c = *s, !( c == ' ' || c == '\t' || c == '\r' ||
			   c == '\n' || c == 0 ) ) {
	    s++ ;
	}
	*ps = s ;
    }
    return ( t ) ;
}


/*
    READ A TEMPLATE FILE

    This routine reads a template file from the current input file.
*/

COMMAND read_template
    PROTO_N ( ( p ) )
    PROTO_T ( COMMAND p )
{
    int go = 1 ;
    char buff [1000] ;
    FILE *f = lex_input ;
    int ln1 = crt_line_no ;
    LIST ( COMMAND ) q = NULL_list ( COMMAND ) ;
    do {
	COMMAND r = NULL_cmd ;
	int ln2 = crt_line_no ;
	char *s = fgets ( buff, 1000, f ) ;
	if ( s == NULL ) {
	    /* End of file */
	    if ( IS_cmd_cond ( p ) ) {
		error ( ERROR_SERIOUS, "End of '@if' expected" ) ;
	    } else if ( IS_cmd_loop ( p ) ) {
		error ( ERROR_SERIOUS, "End of '@loop' expected" ) ;
	    }
	    break ;
	}
	s = xstrcpy ( s ) ;
	if ( s [0] == '@' ) {
	    /* Complex command */
	    int complex = 1 ;
	    char *s1, *s2, *s3 ;
	    s++ ;
	    s1 = get_command ( &s ) ;
	    if ( s1 == NULL ) s1 = "<empty>" ;
	    s2 = get_command ( &s ) ;
	    s3 = get_command ( &s ) ;
	    if ( streq ( s1, "if" ) ) {
		if ( s2 == NULL ) {
		    error ( ERROR_SERIOUS, "Incomplete '@%s' command", s1 ) ;
		    s2 = "true" ;
		}
		MAKE_cmd_cond ( ln2, s2, NULL_cmd, NULL_cmd, r ) ;
	    } else if ( streq ( s1, "else" ) ) {
		if ( IS_cmd_cond ( p ) ) {
		    COMMAND v = DEREF_cmd ( cmd_cond_true_code ( p ) ) ;
		    if ( !IS_NULL_cmd ( v ) ) {
			error ( ERROR_SERIOUS, "Duplicate '@%s' command", s1 ) ;
		    }
		    q = REVERSE_list ( q ) ;
		    MAKE_cmd_compound ( ln1, q, v ) ;
		    COPY_cmd ( cmd_cond_true_code ( p ), v ) ;
		    q = NULL_list ( COMMAND ) ;
		    ln1 = ln2 ;
		} else {
		    error ( ERROR_SERIOUS, "Misplaced '@%s' command", s1 ) ;
		}
		s3 = s2 ;
	    } else if ( streq ( s1, "endif" ) ) {
		if ( IS_cmd_cond ( p ) ) {
		    go = 0 ;
		} else {
		    error ( ERROR_SERIOUS, "Misplaced '@%s' command", s1 ) ;
		}
		s3 = s2 ;
	    } else if ( streq ( s1, "loop" ) ) {
		if ( s2 == NULL ) {
		    error ( ERROR_SERIOUS, "Incomplete '@%s' command", s1 ) ;
		    s2 = "false" ;
		}
		MAKE_cmd_loop ( ln2, s2, NULL_cmd, r ) ;
	    } else if ( streq ( s1, "end" ) ) {
		if ( IS_cmd_loop ( p ) ) {
		    go = 0 ;
		} else {
		    error ( ERROR_SERIOUS, "Misplaced '@%s' command", s1 ) ;
		}
		s3 = s2 ;
	    } else if ( streq ( s1, "use" ) ) {
		if ( s2 == NULL ) {
		    error ( ERROR_SERIOUS, "Incomplete '@%s' command", s1 ) ;
		    s2 = "all" ;
		}
		MAKE_cmd_use ( ln2, s2, s3, r ) ;
		if ( s3 ) s3 = get_command ( &s ) ;
		complex = 0 ;
	    } else if ( streq ( s1, "special" ) ) {
		if ( s2 == NULL ) {
		    error ( ERROR_SERIOUS, "Incomplete '@%s' command", s1 ) ;
		    s2 = "<none>" ;
		}
		MAKE_cmd_special ( ln2, s2, s3, r ) ;
		if ( s3 ) s3 = get_command ( &s ) ;
		complex = 0 ;
	    } else if ( streq ( s1, "comment" ) ) {
		s3 = NULL ;
	    } else {
		error ( ERROR_SERIOUS, "Unknown command, '@%s'", s1 ) ;
		s3 = NULL ;
	    }
	    if ( s3 ) {
		error ( ERROR_SERIOUS, "End of '@%s' expected", s1 ) ;
	    }
	    crt_line_no = ln2 + 1 ;
	    if ( !IS_NULL_cmd ( r ) ) {
		/* Read body of command */
		if ( complex ) {
		    COMMAND u = read_template ( r ) ;
		    if ( IS_cmd_cond ( r ) ) {
			COMMAND v = DEREF_cmd ( cmd_cond_true_code ( r ) ) ;
			if ( IS_NULL_cmd ( v ) ) {
			    COPY_cmd ( cmd_cond_true_code ( r ), u ) ;
			} else {
			    COPY_cmd ( cmd_cond_false_code ( r ), u ) ;
			}
		    } else if ( IS_cmd_loop ( r ) ) {
			COPY_cmd ( cmd_loop_body ( r ), u ) ;
		    }
		}
		CONS_cmd ( r, q, q ) ;
	    }
	} else {
	    /* Simple command */
	    MAKE_cmd_simple ( ln2, s, r ) ;
	    CONS_cmd ( r, q, q ) ;
	    crt_line_no = ln2 + 1 ;
	}
    } while ( go ) ;
    q = REVERSE_list ( q ) ;
    MAKE_cmd_compound ( ln1, q, p ) ;
    return ( p ) ;
}


/*
    CURRENT TOKEN

    These variables are used by the parser to hold the current and former
    lexical tokens.
*/

int crt_lex_token ;
int saved_lex_token ;


/*
    OPEN AN INPUT FILE

    This routine opens the input file nm.  It returns true if the file is
    opened successfully.
*/

int open_file
    PROTO_N ( ( nm ) )
    PROTO_T ( char *nm )
{
    crt_line_no = 1 ;
    if ( nm == NULL || streq ( nm, "-" ) ) {
	crt_file_name = "stdin" ;
	lex_input = stdin ;
    } else {
	crt_file_name = nm ;
	lex_input = fopen ( nm, "r" ) ;
	if ( lex_input == NULL ) {
	    error ( ERROR_SERIOUS, "Can't open input file, '%s'", nm ) ;
	    return ( 0 ) ;
	}
    }
    return ( 1 ) ;
}


/*
    CLOSE THE INPUT FILE

    This routine closes the current input file.
*/

void close_file
    PROTO_Z ()
{
    FILE *f = lex_input ;
    if ( f != stdin ) fclose_v ( f ) ;
    return ;
}
