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
#include "char.h"
#include "error.h"
#include "xalloc.h"


/*
    WHITE SPACE CHARACTERS

    This variable holds all the white space characters.
*/

letter *white_space = NULL ;


/*
    LEXICAL PASS REPRESENTATIONS

    These variables describe the various lexical passes.
*/

static character passes [2] = {
    { LAST_LETTER, NULL, NULL, NULL },
    { LAST_LETTER, NULL, NULL, NULL }
} ;

character *pre_pass = passes ;
character *main_pass = passes + 1 ;


/*
    ALLOCATE A NEW CHARACTER

    This routine allocates a new character with value c.
*/

static character *new_char
    PROTO_N ( ( c ) )
    PROTO_T ( letter c )
{
    character *p ;
    static int chars_left = 0 ;
    static character *chars_free = NULL ;
    if ( chars_left == 0 ) {
	chars_left = 100 ;
	chars_free = xmalloc_nof ( character, chars_left ) ;
    }
    p = chars_free + ( --chars_left ) ;
    p->ch = c ;
    p->defn = NULL ;
    p->cond = NULL ;
    p->opt = NULL ;
    p->next = NULL ;
    return ( p ) ;
}


/*
    ADD A CHARACTER

    This routine adds the string s (defined using data) to the lexical
    pass p.
*/

void add_char
    PROTO_N ( ( p, s, data ) )
    PROTO_T ( character *p X letter *s X char **data )
{
    character *q ;
    letter c = *s ;
    if ( p->next == NULL ) {
	q = new_char ( c ) ;
	p->next = q ;
    } else {
	character *r = NULL ;
	for ( q = p->next ; q && ( q->ch < c ) ; q = q->opt ) r = q ;
	if ( q && q->ch == c ) {
	    /* already exists */
	} else {
	    q = new_char ( c ) ;
	    if ( r == NULL ) {
		q->opt = p->next ;
		p->next = q ;
	    } else {
		q->opt = r->opt ;
		r->opt = q ;
	    }
	}
    }
    if ( c == LAST_LETTER ) {
	if ( q->defn ) {
	    error ( ERROR_SERIOUS,
		    "String for '%s' has already been defined to give '%s'",
		    data [0], q->defn ) ;
	}
	q->defn = data [0] ;
	q->args = data [1] ;
	q->cond = data [2] ;
    } else {
	add_char ( q, s + 1, data ) ;
    }
    return ;
}


/*
    ARRAY OF ALL GROUPS

    This array gives all the character groups.
*/

char_group groups [ MAX_GROUPS ] ;
int no_groups = 0 ;


/*
    CREATE A NEW GROUP

    This routine creates a new character group with name nm and
    definition s.
*/

void make_group
    PROTO_N ( ( nm, s ) )
    PROTO_T ( char *nm X letter *s )
{
    int i, n = no_groups ;
    for ( i = 0 ; i < n ; i++ ) {
	if ( streq ( nm, groups [i].name ) ) {
	    error ( ERROR_SERIOUS, "Group '%s' already defined", nm ) ;
	    return ;
	}
    }
    if ( n >= MAX_GROUPS ) {
	error ( ERROR_SERIOUS, "Too many groups defined (%d)", n ) ;
	return ;
    }
    groups [n].name = nm ;
    groups [n].defn = s ;
    no_groups = n + 1 ;
    return ;
}


/*
    IS A LETTER IN A GROUP?

    This routine checks whether the letter c is in the list p.
*/

int in_group
    PROTO_N ( ( p, c ) )
    PROTO_T ( letter *p X letter c )
{
    letter a ;
    if ( p == NULL ) return ( 0 ) ;
    while ( a = *( p++ ), a != LAST_LETTER ) {
	if ( a == c ) {
	    return ( 1 ) ;
	} else if ( a == WHITE_LETTER ) {
	    if ( in_group ( white_space, c ) ) return ( 1 ) ;
	} else if ( a >= GROUP_LETTER ) {
	    int n = ( int ) ( a - GROUP_LETTER ) ;
	    if ( in_group ( groups [n].defn, c ) ) return ( 1 ) ;
	}
    }
    return ( 0 ) ;
}


/*
    FIND AN ESCAPE SEQUENCE

    This routine finds the character corresponding to the escape sequence c.
*/

letter find_escape
    PROTO_N ( ( c ) )
    PROTO_T ( int c )
{
    letter a ;
    switch ( c ) {
	case 'n' : a = '\n' ; break ;
	case 't' : a = '\t' ; break ;
	case 'v' : a = '\v' ; break ;
	case 'f' : a = '\f' ; break ;
	case 'r' : a = '\r' ; break ;
	case '?' : a = '?' ; break ;
	case '"' : a = '"' ; break ;
	case '[' : a = '[' ; break ;
	case '\\' : a = '\\' ; break ;
	case '\'' : a = '\'' ; break ;
	case 'e' : a = EOF_LETTER ; break ;
	default : {
	    error ( ERROR_SERIOUS, "Unknown escape sequence, '\\%c'",
		    ( unsigned char ) c ) ;
	    a = ( letter ) ( c & 0xff ) ;
	    break ;
	}
    }
    return ( a ) ;
}


/*
    TRANSLATE A STRING INTO A CHARACTER STRING

    This routine translates the string s into an array of letters.
*/

letter *make_string
    PROTO_N ( ( s ) )
    PROTO_T ( char *s )
{
    int i = 0, n = ( int ) strlen ( s )  ;
    letter *p = xmalloc_nof ( letter, n + 1 ) ;
    while ( *s ) {
	letter a ;
	char c = *( s++ ) ;
	if ( c == '\\' ) {
	    c = *( s++ ) ;
	    a = find_escape ( c ) ;
	} else if ( c == '[' ) {
	    int j ;
	    size_t glen ;
	    char *gnm = s ;
	    while ( *s && *s != ']' ) s++ ;
	    glen = ( size_t ) ( s - gnm ) ;
	    if ( *s ) {
		s++ ;
	    } else {
		error ( ERROR_SERIOUS,
			"Unterminated character group name, '%s'", gnm ) ;
	    }
	    for ( j = 0 ; j < no_groups ; j++ ) {
		if ( strncmp ( gnm, groups [j].name, glen ) == 0 ) {
		    a = GROUP_LETTER + j ;
		    break ;
		}
	    }
	    if ( j == no_groups ) {
		if ( strncmp ( gnm, "white", glen ) == 0 ) {
		    a = WHITE_LETTER ;
		} else {
		    error ( ERROR_SERIOUS, "Unknown character group, '%.*s'",
			    ( int ) glen, gnm ) ;
		    a = '?' ;
		}
	    }
	    SET ( a ) ;
	} else {
	    a = ( letter ) ( c & 0xff ) ;
	}
	p [i] = a ;
	i++ ;
    }
    p [i] = LAST_LETTER ;
    return ( p ) ;
}


/*
    LIST OF ALL KEYWORDS

    This variable gives a list of all the keywords.
*/

keyword *keywords = NULL ;


/*
    ADD A KEYWORD

    This routine adds the keyword nm with its associated data to the list
    of all keywords.
*/

void add_keyword
    PROTO_N ( ( nm, data ) )
    PROTO_T ( char *nm X char **data )
{
    static int keywords_left = 0 ;
    static keyword *keywords_free = NULL ;
    keyword *p = keywords, *q = NULL ;
    while ( p ) {
	int c = strcmp ( nm, p->name ) ;
	if ( c == 0 ) {
	    error ( ERROR_SERIOUS, "Keyword '%s' already defined", nm ) ;
	    return ;
	}
	if ( c < 0 ) break ;
	q = p ;
	p = p->next ;
    }
    if ( keywords_left == 0 ) {
	keywords_left = 100 ;
	keywords_free = xmalloc_nof ( keyword, keywords_left ) ;
    }
    p = keywords_free + ( --keywords_left ) ;
    p->name = nm ;
    p->defn = data [0] ;
    p->args = data [1] ;
    p->cond = data [2] ;
    p->done = 0 ;
    if ( q == NULL ) {
	p->next = keywords ;
	keywords = p ;
    } else {
	p->next = q->next ;
	q->next = p ;
    }
    return ;
}
