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
#include "errors.h"
#include "error.h"
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
static int read_string PROTO_S ( ( void ) ) ;

#define get_comment( A, B )	read_comment ()
#define get_identifier( A )	read_identifier ( ( A ) )
#define get_string( A )		read_string ()
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

    This buffer is used by read_token to hold the values of identifiers
    and strings.
*/

char token_buff [2000] ;
static char *token_end = token_buff + sizeof ( token_buff ) ;
char *first_comment = NULL ;


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
    return ( lex_identifier ) ;
}


/*
    READ A STRING

    This routine reads a string.  It is entered after the initial quote has
    been read.  Note that new line characters are allowed in strings.
*/

static int read_string
    PROTO_Z ()
{
    int c ;
    int escaped = 0 ;
    char *t = token_buff ;
    while ( c = read_char (), ( c != '"' || escaped ) ) {
	if ( c == LEX_EOF ) {
	    error ( ERROR_SERIOUS, "Unexpected end of string" ) ;
	    break ;
	}
	*( t++ ) = ( char ) c ;
	if ( t == token_end ) error ( ERROR_FATAL, "Buffer overflow" ) ;
	if ( escaped ) {
	    escaped = 0 ;
	} else {
	    if ( c == '\\' ) escaped = 1 ;
	}
    }
    *t = 0 ;
    return ( lex_string ) ;
}


/*
    READ A COMMENT

    This routine reads a C style comment, returning the lexical token
    immediately following.  It is entered after the first two characters
    have been read.
*/

static int read_comment
    PROTO_Z ()
{
    int state = 0 ;
    char *t = token_buff ;
    *( t++ ) = '/' ;
    *( t++ ) = '*' ;
    while ( state != 2 ) {
	int c = read_char () ;
	if ( c == LEX_EOF ) {
	    error ( ERROR_SERIOUS, "End of file in comment" ) ;
	    return ( lex_eof ) ;
	}
	if ( c == '*' ) {
	    state = 1 ;
	} else if ( state == 1 && c == '/' ) {
	    state = 2 ;
	} else {
	    state = 0 ;
	}
	*( t++ ) = ( char ) c ;
	if ( t == token_end ) t = token_buff + 2 ;
    }
    if ( first_comment == NULL ) first_comment = xstrcpy ( token_buff ) ;
    return ( read_token () ) ;
}


/*
    CURRENT TOKEN

    These variables are used by the parser to hold the current and former
    lexical tokens.
*/

int crt_lex_token ;
int saved_lex_token ;


/*
    PROCESS FILE

    This routine processes the input file nm.  If nm is the null string
    then the standard input is used.
*/

void process_file
    PROTO_N ( ( nm ) )
    PROTO_T ( char *nm )
{
    crt_line_no = 1 ;
    if ( nm == NULL || streq ( nm, "-" ) ) {
	crt_file_name = "stdin" ;
	lex_input = stdin ;
	nm = NULL ;
    } else {
	crt_file_name = nm ;
	lex_input = fopen ( nm, "r" ) ;
	if ( lex_input == NULL ) {
	    error ( ERROR_SERIOUS, "Can't open input file, '%s'", nm ) ;
	    return ;
	}
    }
    ADVANCE_LEXER ;
    read_errors () ;
    if ( nm != NULL ) fclose_v ( lex_input ) ;
    return ;
}
