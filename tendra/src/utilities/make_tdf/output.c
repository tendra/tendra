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
#include "cons_ops.h"
#include "info_ops.h"
#include "link_ops.h"
#include "par_ops.h"
#include "sort_ops.h"
#include "spec_ops.h"
#include "error.h"
#include "input.h"
#include "lex.h"
#include "output.h"


/*
    DO THE INITIAL SEGMENTS OF TWO STRINGS MATCH

    This macro gives a convenient method for testing whether the first
    C characters of the strings A and B are equal.
*/

#define strneq( A, B, C )\
	( strncmp ( ( A ), ( B ), ( size_t ) ( C ) ) == 0 )


/*
    CURRENT OUTPUT FILE

    These variables describe the current output file.
*/

static FILE *output_file ;
static char output_buff [512] ;
static int output_posn = 0 ;
static unsigned crt_column = 0 ;


/*
    CURRENT LOOP VARIABLES

    These variables keep track of the current state of the various
    output loops.
*/

static unsigned crt_major = 0 ;
static unsigned crt_minor = 0 ;
static int crt_unique = 0 ;
static SORT crt_sort = NULL_sort ;
static SORT_INFO crt_info = NULL_info ;
static CONSTRUCT crt_cons = NULL_cons ;
static PARAMETER crt_param = NULL_par ;
static int crt_param_no = 0 ;
static int last_param_no = 0 ;


/*
    PRINT A CHARACTER TO THE OUTPUT FILE

    This routine prints the character c to the output file updating the
    current column number.
*/

static void output_char
    PROTO_N ( ( c ) )
    PROTO_T ( int c )
{
    int i = output_posn ;
    output_buff [i] = ( char ) c ;
    if ( ++i >= 500 || c == '\n' ) {
	output_buff [i] = 0 ;
	IGNORE fputs ( output_buff, output_file ) ;
	i = 0 ;
    }
    if ( c == '\n' ) {
	crt_column = 0 ;
    } else if ( c == '\t' ) {
	crt_column = 8 * ( crt_column / 8 + 1 ) ;
    } else {
	crt_column++ ;
    }
    output_posn = i ;
    return ;
}


/*
    PRINT A STRING TO THE OUTPUT FILE

    This routine prints the string s to the output file.
*/

static void output_string
    PROTO_N ( ( s ) )
    PROTO_T ( char *s )
{
    char c ;
    while ( c = *( s++ ), c != 0 ) {
	output_char ( ( int ) c ) ;
    }
    return ;
}


/*
    OUTPUT AN ENCODING STRING FOR A CONSTRUCT

    This routine writes the encoding strings for the parameter sorts of
    the construct cons to the output file.
*/

static void output_cons
    PROTO_N ( ( cons, intro ) )
    PROTO_T ( CONSTRUCT cons X int intro )
{
    int c ;
    int brks = 0 ;
    unsigned kind = DEREF_unsigned ( cons_kind ( cons ) ) ;
    LIST ( PARAMETER ) p = DEREF_list ( cons_pars ( cons ) ) ;
    while ( !IS_NULL_list ( p ) ) {
	PARAMETER par = DEREF_par ( HEAD_list ( p ) ) ;
	SORT sort = DEREF_sort ( par_type ( par ) ) ;
	int align = DEREF_int ( par_align ( par ) ) ;
	int brk = DEREF_int ( par_brk ( par ) ) ;
	int intro2 = DEREF_int ( par_intro ( par ) ) ;
	if ( align ) output_char ( '|' ) ;
	if ( brk ) output_char ( '{' ) ;
	if ( intro2 ) intro = 1 ;
	c = output_sort ( sort, intro ) ;
	if ( c == '@' && kind == KIND_cond ) {
	    /* Conditional construct */
	    output_char ( '[' ) ;
	    sort = DEREF_sort ( cons_res ( cons ) ) ;
	    IGNORE output_sort ( sort, intro ) ;
	    output_char ( ']' ) ;
	}
	brks += brk ;
	p = TAIL_list ( p ) ;
    }
    while ( brks-- ) output_char ( '}' ) ;
    return ;
}


/*
    OUTPUT AN ENCODING STRING FOR A SORT

    Every basic and built-in type has an associated code letter.  This,
    together with various control characters for lists and optional sorts,
    allows every sort to be expressed as a sequence of characters.  This
    routine prints this encoding string for the sort sort to the output
    file
*/

int output_sort
    PROTO_N ( ( sort, intro ) )
    PROTO_T ( SORT sort X int intro )
{
    int c = DEREF_int ( sort_code ( sort ) ) ;
    SORT_INFO info = DEREF_info ( sort_info ( sort ) ) ;
    if ( !IS_NULL_info ( info ) ) {
	switch ( TAG_info ( info ) ) {
	    case info_builtin_tag :
	    case info_basic_tag : {
		if ( c < 32 ) {
		    char buff [10] ;
		    sprintf_v ( buff, "\\%03o", ( unsigned ) c ) ;
		    output_string ( buff ) ;
		} else {
		    output_char ( c ) ;
		}
		if ( intro ) {
		    int edge = DEREF_int ( sort_edge ( sort ) ) ;
		    if ( edge ) output_char ( '&' ) ;
		}
		break ;
	    }
	    case info_dummy_tag : {
		CONSTRUCT cons = DEREF_cons ( info_dummy_cons ( info ) ) ;
		output_cons ( cons, intro ) ;
		break ;
	    }
	    case info_clist_tag :
	    case info_slist_tag :
	    case info_option_tag : {
		sort = DEREF_sort ( info_clist_etc_arg ( info ) ) ;
		output_char ( c ) ;
		output_char ( '[' ) ;
		IGNORE output_sort ( sort, intro ) ;
		output_char ( ']' ) ;
		break ;
	    }
	}
    }
    return ( c ) ;
}


/*
    OUTPUT A FORMAT STRING

    This routine writes the format string s to the output file.
*/

static void output
    PROTO_N ( ( s ) )
    PROTO_T ( string s )
{
    char c ;
    while ( c = *( s++ ), c != 0 ) {
	if ( c == '%' ) {
	    char *s0 = s ;
	    int prec = 100 ;
	    char buff [120] ;
	    int have_prec = 0 ;
	    SORT cs = crt_sort ;
	    SORT_INFO ci = crt_info ;
	    CONSTRUCT cc = crt_cons ;
	    PARAMETER cp = crt_param ;
	    c = *( s++ ) ;
	    if ( c >= '0' && c <= '9' ) {
		/* Read precision */
		prec = ( int ) ( c - '0' ) ;
		while ( c = *( s++ ), ( c >= '0' && c <= '9' ) ) {
		    prec = 10 * prec + ( int ) ( c - '0' ) ;
		}
		have_prec = 1 ;
	    }
	    switch ( c ) {

		case 'C' :
		cons_format : {
		    /* Construct information */
		    if ( IS_NULL_cons ( cc ) ) goto misplaced_arg ;
		    c = *( s++ ) ;
		    switch ( c ) {
			case 'N' : {
			    /* '%CN' -> construct name */
			    string nm = DEREF_string ( cons_name ( cc ) ) ;
			    sprintf_v ( buff, "%.*s", prec, nm ) ;
			    output_string ( buff ) ;
			    break ;
			}
			case 'E' : {
			    /* '%CE' -> construct encoding */
			    unsigned e ;
			    e = DEREF_unsigned ( cons_encode ( cc ) ) ;
			    sprintf_v ( buff, "%u", e ) ;
			    output_string ( buff ) ;
			    break ;
			}
			case 'S' : {
			    /* '%CS' -> construct result sort */
			    goto sort_format ;
			}
			case 'X' : {
			    /* '%CX' -> construct encoding string */
			    output_cons ( cc, 0 ) ;
			    break ;
			}
			default : {
			    goto bad_format ;
			}
		    }
		    break ;
		}

		case 'P' : {
		    /* Parameter information */
		    if ( IS_NULL_par ( cp ) ) goto misplaced_arg ;
		    c = *( s++ ) ;
		    if ( c == 'N' ) {
			/* '%PN' -> parameter name */
			string nm = DEREF_string ( par_name ( cp ) ) ;
			sprintf_v ( buff, "%.*s", prec, nm ) ;
			output_string ( buff ) ;
		    } else if ( c == 'S' ) {
			/* '%PS' -> parameter sort */
			cs = DEREF_sort ( par_type ( cp ) ) ;
			ci = DEREF_info ( sort_info ( cs ) ) ;
			goto sort_format ;
		    } else if ( c == 'E' ) {
			/* '%PE' -> parameter number */
			sprintf_v ( buff, "%d", crt_param_no ) ;
			output_string ( buff ) ;
		    } else {
			goto bad_format ;
		    }
		    break ;
		}

		case 'S' :
		sort_format : {
		    /* Sort information */
		    if ( IS_NULL_info ( ci ) ) goto misplaced_arg ;
		    c = *( s++ ) ;
		    switch ( c ) {
			case 'N' : {
			    /* '%SN' -> sort name */
			    string nm = DEREF_string ( sort_name ( cs ) ) ;
			    sprintf_v ( buff, "%.*s", prec, nm ) ;
			    output_string ( buff ) ;
			    break ;
			}
			case 'T' : {
			    /* '%ST' -> sort name in capitals */
			    string nm = DEREF_string ( sort_caps ( cs ) ) ;
			    sprintf_v ( buff, "%.*s", prec, nm ) ;
			    output_string ( buff ) ;
			    break ;
			}
			case 'L' : {
			    /* '%SL' -> sort unit name */
			    string nm = DEREF_string ( sort_link ( cs ) ) ;
			    if ( nm ) {
				sprintf_v ( buff, "%.*s", prec, nm ) ;
				output_string ( buff ) ;
			    }
			    break ;
			}
			case 'U' : {
			    /* '%SU' -> sort unit name */
			    string nm = DEREF_string ( sort_unit ( cs ) ) ;
			    if ( nm ) {
				sprintf_v ( buff, "%.*s", prec, nm ) ;
				output_string ( buff ) ;
			    }
			    break ;
			}
			case 'B' : {
			    /* '%SB' -> bits in encoding */
			    unsigned b = 0 ;
			    if ( IS_info_basic ( ci ) ) {
				b = DEREF_unsigned ( info_basic_bits ( ci ) ) ;
			    }
			    sprintf_v ( buff, "%u", b ) ;
			    output_string ( buff ) ;
			    break ;
			}
			case 'E' : {
			    /* '%SE' -> extended encoding */
			    unsigned e = 0 ;
			    if ( IS_info_basic ( ci ) ) {
				e = DEREF_unsigned ( info_basic_extend ( ci ) ) ;
			    }
			    sprintf_v ( buff, "%u", e ) ;
			    output_string ( buff ) ;
			    break ;
			}
			case 'M' : {
			    /* '%SM' -> maximum encoding */
			    unsigned m = 0 ;
			    if ( IS_info_basic ( ci ) ) {
				m = DEREF_unsigned ( info_basic_max ( ci ) ) ;
			    }
			    if ( have_prec ) m += ( unsigned ) prec ;
			    sprintf_v ( buff, "%u", m ) ;
			    output_string ( buff ) ;
			    break ;
			}
			case 'C' : {
			    /* '%SC' -> sortname information */
			    cc = NULL_cons ;
			    if ( IS_info_basic ( ci ) ) {
				cc = DEREF_cons ( info_basic_sortname ( ci ) ) ;
			    }
			    goto cons_format ;
			}
			case 'S' : {
			    /* '%SS' -> subsort information */
			    if ( IS_info_clist_etc ( ci ) ) {
				cs = DEREF_sort ( info_clist_etc_arg ( ci ) ) ;
				ci = DEREF_info ( sort_info ( cs ) ) ;
			    }
			    goto sort_format ;
			}
			case 'X' : {
			    /* '%SX' -> construct encoding string */
			    IGNORE output_sort ( cs, 0 ) ;
			    break ;
			}
			default : {
			    goto bad_format ;
			}
		    }
		    break ;
		}

		case 'V' : {
		    c = *( s++ ) ;
		    if ( c == 'A' ) {
			/* '%VA' -> major version number */
			sprintf_v ( buff, "%u", crt_major ) ;
			output_string ( buff ) ;
		    } else if ( c == 'B' ) {
			/* '%VB' -> minor version number */
			sprintf_v ( buff, "%u", crt_minor ) ;
			output_string ( buff ) ;
		    } else {
			goto bad_format ;
		    }
		    break ;
		}

		case 'Z' : {
		    c = *( s++ ) ;
		    if ( c == 'V' ) {
			/* %ZV -> program version */
			sprintf_v ( buff, "%.*s", prec, progvers ) ;
			output_string ( buff ) ;
		    } else if ( c == 'X' ) {
			/* %ZX -> program name */
			sprintf_v ( buff, "%.*s", prec, progname ) ;
			output_string ( buff ) ;
		    } else {
			goto bad_format ;
		    }
		    break ;
		}

		case 'b' : {
		    /* '%b' -> backspaces */
		    if ( !have_prec ) prec = 1 ;
		    output_posn -= prec ;
		    if ( output_posn < 0 ) output_posn = 0 ;
		    break ;
		}

		case 't' : {
		    /* '%t' -> tabs */
		    if ( have_prec ) {
			while ( crt_column < ( unsigned ) prec ) {
			    output_char ( '\t' ) ;
			}
		    }
		    break ;
		}

		case 'u' : {
		    /* '%u' -> unique value */
		    if ( have_prec ) {
			crt_unique = prec ;
		    } else {
			prec = crt_unique++ ;
			sprintf_v ( buff, "%d", prec ) ;
			output_string ( buff ) ;
		    }
		    break ;
		}

		case '%' : {
		    /* '%%' -> '%' */
		    output_char ( '%' ) ;
		    break ;
		}

		case '@' : {
		    /* '%@' -> '@' */
		    output_char ( '@' ) ;
		    break ;
		}

		case '\n' : {
		    /* Escaped newline */
		    break ;
		}

		case '_' : {
		    /* Dummy end marker */
		    break ;
		}

		misplaced_arg : {
		    error ( ERROR_SERIOUS, "Misplaced format, '%%%.2s'", s0 ) ;
		    output_string ( "<error>" ) ;
		    break ;
		}

		default :
		bad_format : {
		    error ( ERROR_SERIOUS, "Unknown format, '%%%.2s'", s0 ) ;
		    output_string ( "<error>" ) ;
		    break ;
		}
	    }
	} else {
	    output_char ( ( int ) c ) ;
	}
    }
    return ;
}


/*
    EVALUATE A CONDITION

    This routine evaluates the condition given by the string s.
*/

static int eval_cond
    PROTO_N ( ( s ) )
    PROTO_T ( string s )
{
    string s0 = s ;
    SORT cs = crt_sort ;
    SORT_INFO ci = crt_info ;
    CONSTRUCT cc = crt_cons ;
    PARAMETER cp = crt_param ;

    if ( s [0] == '!' ) {
	/* Negate condition */
	return ( !eval_cond ( s + 1 ) ) ;
    }

    if ( strneq ( s, "sort.", 5 ) ) {
	/* Sort conditions */
	s += 5 ;
	sort_label : {
	    unsigned tag = 100 ;
	    if ( !IS_NULL_info ( ci ) ) tag = TAG_info ( ci ) ;
	    if ( streq ( s, "builtin" ) ) return ( tag == info_builtin_tag ) ;
	    if ( streq ( s, "basic" ) ) return ( tag == info_basic_tag ) ;
	    if ( streq ( s, "dummy" ) ) return ( tag == info_dummy_tag ) ;
	    if ( streq ( s, "list" ) ) return ( tag == info_clist_tag ) ;
	    if ( streq ( s, "slist" ) ) return ( tag == info_slist_tag ) ;
	    if ( streq ( s, "option" ) ) return ( tag == info_option_tag ) ;
	    if ( streq ( s, "simple" ) ) {
		return ( tag == info_basic_tag || tag == info_dummy_tag ) ;
	    }
	    if ( streq ( s, "compound" ) ) {
		if ( tag == info_option_tag ) return ( 1 ) ;
		return ( tag == info_clist_tag || tag == info_slist_tag ) ;
	    }
	    if ( streq ( s, "extends" ) ) {
		if ( tag == info_basic_tag ) {
		    unsigned a = DEREF_unsigned ( info_basic_extend ( ci ) ) ;
		    if ( a ) return ( 1 ) ;
		}
		return ( 0 ) ;
	    }
	    if ( streq ( s, "special" ) ) {
		int a = 0 ;
		if ( !IS_NULL_sort ( cs ) ) {
		    a = DEREF_int ( sort_special ( cs ) ) ;
		}
		return ( a ) ;
	    }
	    if ( streq ( s, "edge" ) ) {
		int a = 0 ;
		if ( !IS_NULL_sort ( cs ) ) {
		    a = DEREF_int ( sort_edge ( cs ) ) ;
		}
		return ( a ) ;
	    }
	    if ( streq ( s, "link" ) ) {
		if ( !IS_NULL_sort ( cs ) ) {
		    string nm = DEREF_string ( sort_link ( cs ) ) ;
		    if ( nm ) return ( 1 ) ;
		}
		return ( 0 ) ;
	    }
	    if ( streq ( s, "unit" ) ) {
		if ( !IS_NULL_sort ( cs ) ) {
		    string nm = DEREF_string ( sort_unit ( cs ) ) ;
		    if ( nm ) return ( 1 ) ;
		}
		return ( 0 ) ;
	    }
	    if ( strneq ( s, "name.", 5 ) ) {
		if ( tag == info_basic_tag ) {
		    cc = DEREF_cons ( info_basic_sortname ( ci ) ) ;
		} else {
		    cc = NULL_cons ;
		}
		goto cons_label ;
	    }
	    if ( strneq ( s, "sub.", 4 ) ) {
		s += 4 ;
		if ( tag == info_clist_tag || tag == info_slist_tag ||
		     tag == info_option_tag ) {
		    cs = DEREF_sort ( info_clist_etc_arg ( ci ) ) ;
		    ci = DEREF_info ( sort_info ( cs ) ) ;
		}
		goto sort_label ;
	    }
	    if ( strneq ( s, "eq.", 3 ) ) {
		s += 3 ;
		if ( !IS_NULL_sort ( cs ) ) {
		    string nm = DEREF_string ( sort_name ( cs ) ) ;
		    if ( streq ( nm, s ) ) return ( 1 ) ;
		}
		return ( 0 ) ;
	    }
	}

    } else if ( strneq ( s, "cons.", 5 ) ) {
	/* Construct conditions */
	cons_label : {
	    unsigned kind = KIND_dummy ;
	    s += 5 ;
	    if ( strneq ( s, "sort.", 5 ) ) {
		s += 5 ;
		if ( IS_NULL_cons ( cc ) ) {
		    cs = NULL_sort ;
		    ci = NULL_info ;
		}
		goto sort_label ;
	    }
	    if ( !IS_NULL_cons ( cc ) ) {
		kind = DEREF_unsigned ( cons_kind ( cc ) ) ;
	    }
	    if ( streq ( s, "simple" ) ) return ( kind == KIND_simple ) ;
	    if ( streq ( s, "token" ) ) return ( kind == KIND_token ) ;
	    if ( streq ( s, "cond" ) ) return ( kind == KIND_cond ) ;
	    if ( streq ( s, "edge" ) ) return ( kind == KIND_edge ) ;
	    if ( streq ( s, "foreign" ) ) return ( kind == KIND_foreign ) ;
	    if ( streq ( s, "special" ) ) return ( kind == KIND_special ) ;
	    if ( streq ( s, "params" ) ) {
		if ( !IS_NULL_cons ( cc ) ) {
		    LIST ( PARAMETER ) p = DEREF_list ( cons_pars ( cc ) ) ;
		    if ( !IS_NULL_list ( p ) ) return ( 1 ) ;
		}
		return ( 0 ) ;
	    }
	    if ( streq ( s, "extends" ) ) {
		if ( !IS_NULL_cons ( cc ) ) {
		    if ( !IS_NULL_info ( ci ) && IS_info_basic ( ci ) ) {
			unsigned b, e ;
			b = DEREF_unsigned ( info_basic_bits ( ci ) ) ;
			e = DEREF_unsigned ( cons_encode ( cc ) ) ;
			if ( e >= ( ( unsigned ) 1 << b ) ) return ( 1 ) ;
		    }
		}
		return ( 0 ) ;
	    }
	    if ( strneq ( s, "eq.", 3 ) ) {
		s += 3 ;
		if ( !IS_NULL_cons ( cc ) ) {
		    string nm = DEREF_string ( cons_name ( cc ) ) ;
		    if ( streq ( nm, s ) ) return ( 1 ) ;
		}
		return ( 0 ) ;
	    }
	}

    } else if ( strneq ( s, "param.", 6 ) ) {
	/* Parameter conditions */
	s += 6 ;
	if ( strneq ( s, "sort.", 5 ) ) {
	    s += 5 ;
	    if ( !IS_NULL_par ( cp ) ) {
		cs = DEREF_sort ( par_type ( cp ) ) ;
		ci = DEREF_info ( sort_info ( cs ) ) ;
	    } else {
		cs = NULL_sort ;
		ci = NULL_info ;
	    }
	    goto sort_label ;
	}
	if ( streq ( s, "align" ) ) {
	    int a = 0 ;
	    if ( !IS_NULL_par ( cp ) ) a = DEREF_int ( par_align ( cp ) ) ;
	    return ( a ) ;
	}
	if ( streq ( s, "break" ) ) {
	    int a = 0 ;
	    if ( !IS_NULL_par ( cp ) ) a = DEREF_int ( par_brk ( cp ) ) ;
	    return ( a ) ;
	}
	if ( streq ( s, "intro" ) ) {
	    int a = 0 ;
	    if ( !IS_NULL_par ( cp ) ) a = DEREF_int ( par_intro ( cp ) ) ;
	    return ( a ) ;
	}
	if ( streq ( s, "first" ) ) {
	    return ( crt_param_no == 0 ) ;
	}
	if ( streq ( s, "last" ) ) {
	    return ( crt_param_no == last_param_no ) ;
	}
	if ( strneq ( s, "eq.", 3 ) ) {
	    s += 3 ;
	    if ( !IS_NULL_par ( cp ) ) {
		string nm = DEREF_string ( par_name ( cp ) ) ;
		if ( streq ( nm, s ) ) return ( 1 ) ;
	    }
	    return ( 0 ) ;
	}

    } else {
	/* Other conditions */
	if ( streq ( s, "uniq" ) ) return ( crt_unique ) ;
	if ( streq ( s, "true" ) ) return ( 1 ) ;
	if ( streq ( s, "false" ) ) return ( 0 ) ;
    }
    error ( ERROR_SERIOUS, "Unknown condition, '%s'", s0 ) ;
    return ( 0 ) ;
}


/*
    WRITE A TEMPLATE FILE

    This routine writes the template file given by the commands cmd for
    the specification spec to the output file.
*/

static void output_template
    PROTO_N ( ( spec, cmd ) )
    PROTO_T ( SPECIFICATION spec X COMMAND cmd )
{
    if ( !IS_NULL_cmd ( cmd ) ) {
	crt_line_no = DEREF_int ( cmd_line ( cmd ) ) ;
	switch ( TAG_cmd ( cmd ) ) {
	    case cmd_simple_tag : {
		string s = DEREF_string ( cmd_simple_text ( cmd ) ) ;
		output ( s ) ;
		break ;
	    }
	    case cmd_compound_tag : {
		LIST ( COMMAND ) p ;
		p = DEREF_list ( cmd_compound_seq ( cmd ) ) ;
		while ( !IS_NULL_list ( p ) ) {
		    COMMAND a = DEREF_cmd ( HEAD_list ( p ) ) ;
		    output_template ( spec, a ) ;
		    p = TAIL_list ( p ) ;
		}
		break ;
	    }
	    case cmd_loop_tag : {
		string s = DEREF_string ( cmd_loop_control ( cmd ) ) ;
		COMMAND a = DEREF_cmd ( cmd_loop_body ( cmd ) ) ;
		if ( streq ( s, "sort" ) ) {
		    /* Loop over all sorts */
		    SORT ls = crt_sort ;
		    SORT_INFO li = crt_info ;
		    LIST ( SORT ) ps = DEREF_list ( spec_sorts ( spec ) ) ;
		    while ( !IS_NULL_list ( ps ) ) {
			SORT cs = DEREF_sort ( HEAD_list ( ps ) ) ;
			int mark = DEREF_int ( sort_mark ( cs ) ) ;
			if ( mark ) {
			    SORT_INFO ci = DEREF_info ( sort_info ( cs ) ) ;
			    if ( !IS_NULL_info ( ci ) ) {
				crt_sort = cs ;
				crt_info = ci ;
				output_template ( spec, a ) ;
			    }
			}
			ps = TAIL_list ( ps ) ;
		    }
		    crt_sort = ls ;
		    crt_info = li ;

		} else if ( streq ( s, "sort.cons" ) ) {
		    /* Loop over all constructs */
		    CONSTRUCT lc = crt_cons ;
		    SORT_INFO ci = crt_info ;
		    if ( !IS_NULL_info ( ci ) ) {
			if ( IS_info_basic ( ci ) ) {
			    LIST ( CONSTRUCT ) pc ;
			    pc = DEREF_list ( info_basic_cons ( ci ) ) ;
			    while ( !IS_NULL_list ( pc ) ) {
				crt_cons = DEREF_cons ( HEAD_list ( pc ) ) ;
				output_template ( spec, a ) ;
				pc = TAIL_list ( pc ) ;
			    }
			} else if ( IS_info_dummy ( ci ) ) {
			    crt_cons = DEREF_cons ( info_dummy_cons ( ci ) ) ;
			    output_template ( spec, a ) ;
			}
		    }
		    crt_cons = lc ;

		} else if ( streq ( s, "cons.param" ) ) {
		    /* Loop over all parameters */
		    int np = crt_param_no ;
		    int mp = last_param_no ;
		    PARAMETER lp = crt_param ;
		    CONSTRUCT cc = crt_cons ;
		    if ( !IS_NULL_cons ( cc ) ) {
			LIST ( PARAMETER ) pp ;
			pp = DEREF_list ( cons_pars ( cc ) ) ;
			crt_param_no = 0 ;
			last_param_no = ( int ) LENGTH_list ( pp ) - 1 ;
			while ( !IS_NULL_list ( pp ) ) {
			    crt_param = DEREF_par ( HEAD_list ( pp ) ) ;
			    output_template ( spec, a ) ;
			    crt_param_no++ ;
			    pp = TAIL_list ( pp ) ;
			}
		    }
		    last_param_no = mp ;
		    crt_param_no = np ;
		    crt_param = lp ;

		} else if ( streq ( s, "param.prev" ) ) {
		    /* Loop over all previous parameters */
		    int np = crt_param_no ;
		    int mp = last_param_no ;
		    PARAMETER lp = crt_param ;
		    CONSTRUCT cc = crt_cons ;
		    if ( !IS_NULL_cons ( cc ) ) {
			LIST ( PARAMETER ) pp ;
			pp = DEREF_list ( cons_pars ( cc ) ) ;
			crt_param_no = 0 ;
			last_param_no = np - 1 ;
			while ( !IS_NULL_list ( pp ) && crt_param_no < np ) {
			    crt_param = DEREF_par ( HEAD_list ( pp ) ) ;
			    output_template ( spec, a ) ;
			    crt_param_no++ ;
			    pp = TAIL_list ( pp ) ;
			}
		    }
		    last_param_no = mp ;
		    crt_param_no = np ;
		    crt_param = lp ;

		} else {
		    error ( ERROR_SERIOUS, "Unknown control, '%s'", s ) ;
		}
		break ;
	    }
	    case cmd_cond_tag : {
		string s = DEREF_string ( cmd_cond_control ( cmd ) ) ;
		COMMAND a = DEREF_cmd ( cmd_cond_true_code ( cmd ) ) ;
		COMMAND b = DEREF_cmd ( cmd_cond_false_code ( cmd ) ) ;
		if ( eval_cond ( s ) ) {
		    output_template ( spec, a ) ;
		} else {
		    output_template ( spec, b ) ;
		}
		break ;
	    }
	    case cmd_use_tag : {
		int m = 1 ;
		string c = DEREF_string ( cmd_use_cons ( cmd ) ) ;
		string s = DEREF_string ( cmd_use_sort ( cmd ) ) ;
		while ( s [0] == '!' ) {
		    m = !m ;
		    s++ ;
		}
		if ( c == NULL && streq ( s, "all" ) ) {
		    mark_all_sorts ( m ) ;
		} else {
		    SORT sn = find_sort ( s, 0 ) ;
		    if ( c ) {
			CONSTRUCT cn = find_construct ( sn, c ) ;
			mark_construct ( cn, m ) ;
		    } else {
			mark_sort ( sn, m ) ;
		    }
		}
		break ;
	    }
	    case cmd_special_tag : {
		SORT sn ;
		int m = 1 ;
		string c = DEREF_string ( cmd_special_cons ( cmd ) ) ;
		string s = DEREF_string ( cmd_special_sort ( cmd ) ) ;
		while ( s [0] == '!' ) {
		    m = !m ;
		    s++ ;
		}
		sn = find_sort ( s, 0 ) ;
		if ( c ) {
		    if ( m ) {
			set_special ( sn, c, KIND_special ) ;
		    } else {
			set_special ( sn, c, KIND_simple ) ;
		    }
		} else {
		    COPY_int ( sort_special ( sn ), m ) ;
		}
		mark_sort ( sn, 1 ) ;
		break ;
	    }
	}
    }
    return ;
}


/*
    MAIN OUTPUT ROUTINE

    This routine outputs all the information concerning the TDF specification
    spec to the output file nm using the template cmd.
*/

void output_spec
    PROTO_N ( ( nm, spec, cmd ) )
    PROTO_T ( char *nm X SPECIFICATION spec X COMMAND cmd )
{
    CONST char *tnm = crt_file_name ;
    crt_line_no = 1 ;
    if ( nm == NULL || streq ( nm, "-" ) ) {
	crt_file_name = "<stdout>" ;
	output_file = stdout ;
	nm = NULL ;
    } else {
	crt_file_name = nm ;
	output_file = fopen ( nm, "w" ) ;
	if ( output_file == NULL ) {
	    error ( ERROR_SERIOUS, "Can't open output file, '%s'", nm ) ;
	    return ;
	}
    }
    output_posn = 0 ;
    crt_column = 0 ;
    crt_file_name = tnm ;
    crt_major = DEREF_unsigned ( spec_major ( spec ) ) ;
    crt_minor = DEREF_unsigned ( spec_minor ( spec ) ) ;
    output_template ( spec, cmd ) ;
    if ( output_posn ) output_char ( '\n' ) ;
    if ( nm ) fclose_v ( output_file ) ;
    return ;
}
