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
#include "object.h"
#include "hash.h"
#include "lex.h"
#include "name.h"
#include "syntax.h"
#include "type.h"
#include "utility.h"


/*
    CREATE A KEYWORD

    This routine creates a keyword nm with lexical token value t.
*/

static void make_keyword
    PROTO_N ( ( nm, t ) )
    PROTO_T ( char *nm X int t )
{
    object *p = make_object ( nm, OBJ_KEYWORD ) ;
    p->u.u_num = t ;
    IGNORE add_hash ( keywords, p, no_version ) ;
    return ;
}


/*
    INITIALISE KEYWORDS

    This routine initialises the hash table of keywords.
*/

void init_keywords
    PROTO_Z ()
{
#define MAKE_KEYWORD( NAME, LEX )\
    make_keyword ( NAME, LEX )
#include "keyword.h"
    return ;
}


/*
    CURRENT LEXICAL TOKEN

    These variables are used to store the value of the current lexical
    token.
*/

int crt_lex_token = lex_unknown ;
int saved_lex_token = lex_unknown ;
char *token_value = null ;


/*
    INPUT FILE

    These variable input_file gives the file from which the input is read.
    The input_pending variable is used to unread one character.
*/

FILE *input_file ;
int input_pending = LEX_EOF ;


/*
    READ A CHARACTER FROM THE INPUT FILE

    This routine reads the next character from the input file.
*/

static int read_char
    PROTO_Z ()
{
    int c = input_pending ;
    if ( c == LEX_EOF ) {
	c = fgetc ( input_file ) ;
	if ( c == '\n' ) line_no++ ;
	if ( c == EOF ) return ( LEX_EOF ) ;
	c &= 0xff ;
    } else {
	input_pending = LEX_EOF ;
    }
    return ( c ) ;
}


/*
    MAPPINGS OF LEXICAL ANALYSER ROUTINES

    These macros give the mappings from the lexical analyser to the
    routines defined in this module.
*/

static int read_identifier PROTO_S ( ( int, int, int ) ) ;
static int read_number PROTO_S ( ( int, int ) ) ;
static int read_string PROTO_S ( ( int ) ) ;
static int read_insert PROTO_S ( ( int ) ) ;
static int read_c_comment PROTO_S ( ( int ) ) ;
static int read_comment PROTO_S ( ( int ) ) ;

#define unread_char( A )	input_pending = ( A )
#define get_global( A )		read_identifier ( 0, ( A ), 0 )
#define get_local( A, B )	read_identifier ( ( A ), ( B ), 0 )
#define get_command( A, B )	read_identifier ( ( A ), ( B ), 0 )
#define get_variable( A, B )	read_identifier ( ( A ), ( B ), 0 )
#define get_number( A )		read_number ( ( A ), 0 )
#define get_string( A )		read_string ( 0 )
#define get_comment( A )	read_comment ( 0 )
#define get_c_comment( A, B )	read_c_comment ( 0 )
#define get_text( A, B )	read_insert ( 0 )
#define unknown_token( A )	lex_unknown


/*
    INCLUDE THE LEXICAL ANALYSER

    The automatically generated lexical analyser is included at this
    point.  It defines the routine read_token which reads the next
    lexical token from the input file.
*/

#include "lexer.h"


/*
    READ AN IDENTIFIER NAME

    This routine reads an identifier name from the input file.  It is
    entered after the first character, b, has been read.  a gives the
    identifier prefix, '+' for commands, '$' for variables, '~' for
    local identifiers, and 0 for normal identifiers.
*/

static int read_identifier
    PROTO_N ( ( a, b, pp ) )
    PROTO_T ( int a X int b X int pp )
{
    int c ;
    object *p ;
    int i = 0 ;
    char *s = buffer ;
    if ( a ) s [ i++ ] = ( char ) a ;
    s [ i++ ] = ( char ) b ;
    for ( ; ; ) {
	c = read_char () ;
	if ( !is_alphanum ( lookup_char ( c ) ) ) break ;
	s [i] = ( char ) c ;
	if ( ++i >= buffsize ) {
	    error ( ERR_SERIOUS, "Identifier too long" ) ;
	    i = 1 ;
	}
    }
    unread_char ( c ) ;
    s [i] = 0 ;
    p = search_hash ( keywords, s, no_version ) ;
    if ( p ) return ( p->u.u_num ) ;
    token_value = s ;
    if ( a == 0 ) {
	if ( !pp ) token_value = string_copy ( s ) ;
	return ( lex_name ) ;
    }
    if ( a == '$' ) {
	if ( !pp ) token_value = string_copy ( s ) ;
	return ( lex_variable ) ;
    }
    if ( a == '+' ) {
	/* Commands */
	if ( !pp ) token_value = string_copy ( s ) ;
	error ( ERR_SERIOUS, "Unknown command, '%s'", s ) ;
	return ( lex_name ) ;
    }
    token_value = string_concat ( HIDDEN_NAME, s + 1 ) ;
    return ( lex_name ) ;
}


/*
    READ A NUMBER

    This routine reads a number from the input file.  It is entered after
    the initial character, a, has been read.
*/

static int read_number
    PROTO_N ( ( a, pp ) )
    PROTO_T ( int a X int pp )
{
    int c ;
    int i = 0 ;
    char *s = buffer ;
    s [ i++ ] = ( char ) a ;
    for ( ; ; ) {
	c = read_char () ;
	if ( !is_digit ( lookup_char ( c ) ) ) break ;
	s [i] = ( char ) c ;
	if ( ++i >= buffsize ) {
	    error ( ERR_SERIOUS, "Number too long" ) ;
	    i = 0 ;
	}
    }
    unread_char ( c ) ;
    s [i] = 0 ;
    if ( pp ) {
	token_value = s ;
    } else {
	token_value = string_copy ( s ) ;
    }
    return ( lex_number ) ;
}


/*
    READ A STRING

    This routine reads a string from the input file.  It is entered after
    the initial quote has been read.
*/

static int read_string
    PROTO_N ( ( pp ) )
    PROTO_T ( int pp )
{
    int c ;
    int i = 0 ;
    char *s = buffer ;
    for ( ; ; ) {
	c = read_char () ;
	if ( c == '"' ) {
	    /* End of string */
	    break ;
	} else if ( c == '\\' ) {
	    /* Deal with escaped characters */
	    c = read_char () ;
	    if ( c == '\n' || c == LEX_EOF ) goto new_line ;
	    if ( pp ) {
		/* Preserve escapes when preprocessing */
		s [i] = '\\' ;
		i++ ;
	    } else {
		/* Examine escape sequence */
		switch ( c ) {
		    case 'n' : c = '\n' ; break ;
		    case 'r' : c = '\r' ; break ;
		    case 't' : c = '\t' ; break ;
		}
	    }
	} else if ( c == '\n' || c == LEX_EOF ) {
	    /* Deal with new lines */
	    new_line : {
		error ( ERR_SERIOUS, "New line in string" ) ;
		s [i] = 0 ;
		return ( lex_string ) ;
	    }
	}
	s [i] = ( char ) c ;
	if ( ++i >= buffsize ) {
	    error ( ERR_SERIOUS, "String too long" ) ;
	    i = 0 ;
	}
    }
    s [i] = 0 ;
    if ( pp ) {
	token_value = s ;
    } else {
	token_value = string_copy ( s ) ;
    }
    return ( lex_string ) ;
}


/*
    READ A SECTION OF QUOTED TEXT

    This routine reads a section of quoted text (indicated by enclosure
    in a number of percent signs) into the buffer.  On entry two percents
    have already been read.  Firstly any further percents are read, then
    the text is read until an equal number of percents are encountered.
    Any leading or trailing whitespace is ignored if pp is false.
*/

static int read_insert
    PROTO_N ( ( pp ) )
    PROTO_T ( int pp )
{
    int c ;
    int i = 0 ;
    int p = 0 ;
    int percents = 2 ;
    char *s = buffer ;
    while ( c = read_char (), c == '%' ) percents++ ;
    unread_char ( c ) ;
    if ( pp ) {
	/* Preserve percents when preprocessing */
	if ( percents < buffsize ) {
	    for ( i = 0 ; i < percents ; i++ ) s [i] = '%' ;
	} else {
	    error ( ERR_SERIOUS, "Insert too long" ) ;
	}
    }
    do {
	c = read_char () ;
	if ( c == '%' ) {
	    p++ ;
	} else {
	    if ( c == LEX_EOF ) {
		error ( ERR_SERIOUS, "End of file in quoted text" ) ;
		return ( lex_eof ) ;
	    }
	    p = 0 ;
	}
	s [i] = ( char ) c ;
	if ( ++i >= buffsize ) {
	    error ( ERR_SERIOUS, "Insert too long" ) ;
	    i = 0 ;
	}
    } while ( p != percents ) ;
    if ( pp ) {
	/* Preserve percents when preprocessing */
	s [i] = 0 ;
	token_value = s ;
    } else {
	/* Strip out initial and final white space */
	if ( i >= p ) i -= p ;
	s [i] = 0 ;
	while ( --i >= 0 ) {
	    int a = ( int ) s [i] ;
	    int t = lookup_char ( a & 0xff ) ;
	    if ( !is_white ( t ) ) break ;
	    s [i] = 0 ;
	}
	i = 0 ;
	for ( ; ; ) {
	    int a = ( int ) s [i] ;
	    int t = lookup_char ( a & 0xff ) ;
	    if ( !is_white ( t ) ) break ;
	    i++ ;
	}
	token_value = string_copy ( s + i ) ;
    }
    return ( percents % 2 ? lex_build_Hinsert : lex_insert ) ;
}


/*
    READ A C COMMENT

    This routine reads a C-style comment into the buffer.  The routine is
    entered just after the initial / * has been read, and continues until
    the corresponding * /.
*/

static int read_c_comment
    PROTO_N ( ( pp ) )
    PROTO_T ( int pp )
{
    int c ;
    int i = 2 ;
    int p = 0 ;
    char *s = buffer ;
    s [0] = '/' ;
    s [1] = '*' ;
    do {
	c = read_char () ;
	if ( c == '*' && p == 0 ) {
	    p = 1 ;
	} else if ( c == '/' && p == 1 ) {
	    p = 2 ;
	} else {
	    p = 0 ;
	}
	if ( c == LEX_EOF ) {
	    error ( ERR_SERIOUS, "End of file in comment" ) ;
	    return ( lex_eof ) ;
	}
	s [i] = ( char ) c ;
	if ( ++i >= buffsize ) {
	    error ( ERR_SERIOUS, "Comment too long" ) ;
	    i = 2 ;
	}
    } while ( p != 2 ) ;
    s [i] = 0 ;
    if ( pp ) {
	token_value = s ;
    } else {
	token_value = string_copy ( s ) ;
    }
    return ( lex_comment ) ;
}


/*
    READ A TSPEC COMMENT

    This routine steps over a tspec comment.  It is entered after the
    initial '#' has been read and skips to the end of the line.  If pp
    is false then the next token is returned.
*/

static int read_comment
    PROTO_N ( ( pp ) )
    PROTO_T ( int pp )
{
    int c ;
    while ( c = read_char (), c != '\n' ) {
	if ( c == LEX_EOF ) {
	    error ( ERR_SERIOUS, "End of file in comment" ) ;
	    return ( lex_eof ) ;
	}
    }
    if ( pp ) return ( lex_unknown ) ;
    return ( read_token () ) ;
}


/*
    READ A PREPROCESSING TOKEN

    This routine is a stripped down version of read_token which is used
    in preprocessing.  Initial white space is skipped if w is true.
    The token read is always stored in the buffer.
*/

static int read_pptoken
    PROTO_N ( ( w ) )
    PROTO_T ( int w )
{
    int c ;
    int t = lex_unknown ;
    do {
	c = read_char () ;
    } while ( w && is_white ( lookup_char ( c ) ) ) ;
    switch ( c ) {
	case '"' : {
	    return ( read_string ( 1 ) ) ;
	}
	case '#' : {
	    IGNORE read_comment ( 1 ) ;
	    if ( w ) return ( read_pptoken ( w ) ) ;
	    c = '\n' ;
	    break ;
	}
	case '%' : {
	    int a = read_char () ;
	    if ( a == '%' ) return ( read_insert ( 1 ) ) ;
	    unread_char ( a ) ;
	    break ;
	}
	case '+' : {
	    int a = read_char () ;
	    if ( is_alpha ( lookup_char ( a ) ) ) {
		return ( read_identifier ( c, a, 1 ) ) ;
	    }
	    unread_char ( a ) ;
	    break ;
	}
	case '/' : {
	    int a = read_char () ;
	    if ( a == '*' ) return ( read_c_comment ( 1 ) ) ;
	    unread_char ( a ) ;
	    break ;
	}
	case ':' : {
	    int a = read_char () ;
	    if ( a == '=' ) {
		buffer [0] = ( char ) c ;
		buffer [1] = ( char ) a ;
		buffer [2] = 0 ;
		return ( lex_assign ) ;
	    }
	    unread_char ( a ) ;
	    break ;
	}
	case '(' : t = lex_open_Hround ; break ;
	case ')' : t = lex_close_Hround ; break ;
	case '{' : t = lex_open_Hbrace ; break ;
	case '}' : t = lex_close_Hbrace ; break ;
	case ';' : t = lex_semicolon ; break ;
	case ',' : t = lex_comma ; break ;
	case LEX_EOF : t = lex_eof ; break ;
    }
    buffer [0] = ( char ) c ;
    buffer [1] = 0 ;
    return ( t ) ;
}


/*
    READ A STRING

    This routine reads a string plus one other character from the input
    file, storing the string in str and returning the other character.
    b is set to true if the string is enclosed in brackets.
*/

static int read_pp_string
    PROTO_N ( ( str, b ) )
    PROTO_T ( char **str X int *b )
{
    int c = read_pptoken ( 1 ) ;
    if ( c == lex_open_Hround ) {
	*b = 1 ;
	c = read_pptoken ( 1 ) ;
    }
    if ( c != lex_string ) {
	error ( ERR_SERIOUS, "Syntax error - string expected" ) ;
	*str = "???" ;
	return ( c ) ;
    }
    *str = string_copy ( buffer ) ;
    c = read_pptoken ( 1 ) ;
    if ( *b ) {
	if ( c != lex_close_Hround ) {
	    error ( ERR_SERIOUS, "Syntax error - ')' expected" ) ;
	}
	c = read_pptoken ( 1 ) ;
    }
    return ( c ) ;
}


/*
    PRINT A SUBSET NAME

    This routine prints the command cmd "api", "file", "subset" to the
    file output.
*/

static void print_subset_name
    PROTO_N ( ( output, cmd, api, file, subset, b ) )
    PROTO_T ( FILE *output X char *cmd X
	      char *api X char *file X char *subset X int b )
{
    if ( b ) {
	IGNORE fprintf ( output, "%s ( \"%s\" )", cmd, api ) ;
    } else {
	IGNORE fprintf ( output, "%s \"%s\"", cmd, api ) ;
    }
    if ( file ) IGNORE fprintf ( output, ", \"%s\"", file ) ;
    if ( subset ) {
	if ( file == null ) IGNORE fputs ( ", \"\"", output ) ;
	IGNORE fprintf ( output, ", \"%s\"", subset ) ;
    }
    return ;
}


/*
    PRINT THE CURRENT FILE POSITION

    This routine prints file name and line number directives to the file
    output.
*/

static void print_posn
    PROTO_N ( ( output ) )
    PROTO_T ( FILE *output )
{
    static char *last_filename = "" ;
    if ( !streq ( filename, last_filename ) ) {
	IGNORE fprintf ( output, "$FILE = \"%s\" ;\n", filename ) ;
	last_filename = filename ;
    }
    IGNORE fprintf ( output, "$LINE = %d ;\n", line_no - 1 ) ;
    return ;
}


/*
    PREPROCESS A SUBFILE

    This routine reads a +IMPLEMENT or +USE directive (indicated by n)
    from the input file to output.
*/

static void preproc_subfile
    PROTO_N ( ( output, cmd ) )
    PROTO_T ( FILE *output X char *cmd )
{
    int c ;
    int txt ;
    int b = 0 ;
    char *api = null ;
    char *file = null ;
    char *subset = null ;
    c = read_pp_string ( &api, &b ) ;
    if ( c == lex_comma ) {
	int d = 0 ;
	c = read_pp_string ( &file, &d ) ;
	if ( d ) {
	    error ( ERR_SERIOUS, "Illegally bracketed string" ) ;
	    d = 0 ;
	}
	if ( c == lex_comma ) {
	    c = read_pp_string ( &subset, &d ) ;
	    if ( d ) error ( ERR_SERIOUS, "Illegally bracketed string" ) ;
	}
	if ( *file == 0 ) file = null ;
    }
    if ( c == lex_semicolon ) {
	txt = ';' ;
    } else if ( c == lex_open_Hround ) {
	txt = '(' ;
    } else {
	error ( ERR_SERIOUS, "Syntax error - ';' or '(' expected" ) ;
	txt = ';' ;
    }
    preproc ( output, api, file, subset ) ;
    print_posn ( output ) ;
    print_subset_name ( output, cmd, api, file, subset, b ) ;
    IGNORE fputc ( ' ', output ) ;
    IGNORE fputc ( txt, output ) ;
    return ;
}


/*
    PREPROCESS A FILE

    This routine preprocesses the subset api:file:subset into output.
*/

void preproc
    PROTO_N ( ( output, api, file, subset ) )
    PROTO_T ( FILE *output X char *api X char *file X char *subset )
{
    int c ;
    char *s ;
    object *p ;
    char *sn, *nm ;
    FILE *old_file ;
    int old_pending ;
    int old_line_no ;
    char *old_filename ;
    boolean found = 0 ;
    int brackets = 0 ;
    int end_brackets = 0 ;
    int if_depth = 0 ;
    int else_depth = 0 ;
    FILE *input = null ;
    boolean printing = ( boolean ) ( subset ? 0 : 1 ) ;

    /* Check for previous inclusion */
    sn = subset_name ( api, file, subset ) ;
    p = search_hash ( subsets, sn, no_version ) ;
    if ( p != null ) {
	if ( p->u.u_info == null ) {
	    error ( ERR_SERIOUS, "Recursive inclusion of '%s'", sn ) ;
	} else if ( p->u.u_info->implemented ) {
	    error ( ERR_SERIOUS, "Set '%s' not found", sn ) ;
	}
	return ;
    }

    /* Open the input file */
    nm = ( file ? file : MASTER_FILE ) ;
    if ( !streq ( api, LOCAL_API ) ) {
	nm = string_printf ( "%s/%s", api, nm ) ;
    }
    s = input_dir ;
    while ( s ) {
	char *t = strchr ( s, ':' ) ;
	if ( t == null ) {
	   IGNORE sprintf ( buffer, "%s/%s", s, nm ) ;
	   s = null ;
	} else {
	   IGNORE strcpy ( buffer, s ) ;
	   IGNORE sprintf ( buffer + ( t - s ), "/%s", nm ) ;
	   s = t + 1 ;
	}
	input = fopen ( buffer, "r" ) ;
	if ( input ) {
	    nm = string_copy ( buffer ) ;
	    break ;
	}
    }
    if ( input == null ) {
	input = fopen ( nm, "r" ) ;
	if ( input == null ) {
	    char *err = "Set '%s' not found (can't find file %s)" ;
	    error ( ERR_SERIOUS, err, sn, nm ) ;
	    p = make_object ( sn, OBJ_SUBSET ) ;
	    IGNORE add_hash ( subsets, p, no_version ) ;
	    p->u.u_info = make_info ( api, file, subset ) ;
	    p->u.u_info->implemented = 1 ;
	    return ;
	}
    }
    if ( verbose > 1 ) {
	if ( subset ) {
	    error ( ERR_INFO, "Preprocessing %s [%s] ...", nm, subset ) ;
	} else {
	    error ( ERR_INFO, "Preprocessing %s ...", nm ) ;
	}
    }
    old_filename = filename ;
    old_line_no = line_no ;
    old_file = input_file ;
    old_pending = input_pending ;
    filename = nm ;
    line_no = 1 ;
    input_file = input ;
    input_pending = LEX_EOF ;
    p = make_object ( sn, OBJ_SUBSET ) ;
    IGNORE add_hash ( subsets, p, no_version ) ;

    /* Print position identifier */
    print_subset_name ( output, "+SET", api, file, subset, 0 ) ;
    IGNORE fputs ( " := {\n", output ) ;
    if ( printing ) print_posn ( output ) ;

    /* Process the input */
    while ( c = read_pptoken ( 0 ), c != lex_eof ) {
	switch ( c ) {

	    case lex_subset : {
		/* Deal with subsets */
		int d = 0 ;
		c = read_pp_string ( &s, &d ) ;
		if ( d ) error ( ERR_SERIOUS, "Illegally bracketed string" ) ;
		if ( c != lex_assign ) {
		    error ( ERR_SERIOUS, "Syntax error - ':=' expected" ) ;
		}
		c = read_pptoken ( 1 ) ;
		if ( c != lex_open_Hbrace ) {
		    error ( ERR_SERIOUS, "Syntax error - '{' expected" ) ;
		}
		brackets++ ;
		if ( printing ) {
		    int b = brackets ;
		    char *cmd = "+IMPLEMENT" ;
		    preproc ( output, api, file, s ) ;
		    print_subset_name ( output, cmd, api, file, s, 0 ) ;
		    IGNORE fputs ( " ;\n", output ) ;
		    do {
			c = read_pptoken ( 0 ) ;
			if ( c == lex_open_Hbrace ) {
			    brackets++ ;
			} else if ( c == lex_close_Hbrace ) {
			    brackets-- ;
			} else if ( c == lex_eof ) {
			    char *err = "Can't find end of subset '%s'" ;
			    error ( ERR_SERIOUS, err, s ) ;
			    goto end_of_file ;
			}
		    } while ( brackets >= b ) ;
		    c = read_pptoken ( 1 ) ;
		    if ( c != lex_semicolon ) {
			error ( ERR_SERIOUS, "Syntax error - ';' expected" ) ;
		    }
		    print_posn ( output ) ;
		} else {
		    if ( streq ( s, subset ) ) {
			if ( found ) {
			    char *err = "Set '%s' already defined (line %d)" ;
			    error ( ERR_SERIOUS, err, sn, p->line_no ) ;
			} else {
			    found = 1 ;
			    printing = 1 ;
			    print_posn ( output ) ;
			    p->line_no = line_no ;
			    end_brackets = brackets ;
			}
		    }
		}
		break ;
	    }

	    case lex_implement : {
		/* Deal with subset uses */
		if ( printing ) preproc_subfile ( output, "+IMPLEMENT" ) ;
		break ;
	    }

	    case lex_use : {
		/* Deal with subset uses */
		if ( printing ) preproc_subfile ( output, "+USE" ) ;
		break ;
	    }

	    case lex_set : {
		/* Deal with sets */
		error ( ERR_SERIOUS, "+SET directive in preprocessor" ) ;
		goto default_lab ;
	    }

	    case lex_if :
	    case lex_ifdef :
	    case lex_ifndef : {
		if_depth++ ;
		else_depth = 0 ;
		goto default_lab ;
	    }

	    case lex_else : {
		if ( if_depth == 0 ) {
		    error ( ERR_SERIOUS, "+ELSE without +IF" ) ;
		} else {
		    if ( else_depth ) {
			error ( ERR_SERIOUS, "Duplicate +ELSE" ) ;
		    }
		    else_depth = 1 ;
		}
		goto default_lab ;
	    }

	    case lex_endif : {
		if ( if_depth == 0 ) {
		    error ( ERR_SERIOUS, "+ENDIF without +IF" ) ;
		} else {
		    if_depth-- ;
		}
		else_depth = 0 ;
		goto default_lab ;
	    }

	    case lex_string : {
		/* Deal with strings */
		if ( printing ) {
		    IGNORE fprintf ( output, "\"%s\"", buffer ) ;
		}
		break ;
	    }

	    case lex_open_Hbrace : {
		/* Start of subset */
		brackets++ ;
		goto default_lab ;
	    }

	    case lex_close_Hbrace : {
		/* End of subset */
		brackets-- ;
		if ( brackets < 0 ) {
		    error ( ERR_SERIOUS, "Unmatched '}'" ) ;
		    brackets = 0 ;
		}
		if ( subset && brackets < end_brackets ) {
		    printing = 0 ;
		}
		goto default_lab ;
	    }

	    default :
	    default_lab : {
		/* Deal with simple tokens */
		if ( printing ) IGNORE fputs ( buffer, output ) ;
		break ;
	    }
	}
    }

    /* End of file */
    end_of_file : {
	if ( brackets ) {
	    error ( ERR_SERIOUS, "Bracket imbalance of %d", brackets ) ;
	}
	while ( if_depth ) {
	    error ( ERR_SERIOUS, "+IF without +ENDIF" ) ;
	    if_depth-- ;
	}
	IGNORE fputs ( "} ;\n", output ) ;
	IGNORE fclose ( input ) ;
	p->u.u_info = make_info ( api, file, subset ) ;
	filename = old_filename ;
	line_no = old_line_no ;
	input_file = old_file ;
	input_pending = old_pending ;
	if ( subset && !found ) {
	    char *err = "Set '%s' not found (can't find subset '%s')" ;
	    error ( ERR_SERIOUS, err, sn, subset ) ;
	    p->u.u_info->implemented = 1 ;
	}
	return ;
    }
}
