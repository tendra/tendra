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
#include "check.h"
#include "de_types.h"
#include "de_capsule.h"
#include "de_unit.h"
#include "decode.h"
#include "eval.h"
#include "fetch.h"
#include "high.h"
#include "node.h"
#include "shape.h"
#include "table.h"
#include "tdf.h"
#include "utility.h"


/*
    DECODE AN EXTENDED VALUE

    An extended n bit encoding is decoded.
*/

long fetch_extn
    PROTO_N ( ( n ) )
    PROTO_T ( int n )
{
    long r = 0, s ;
    while ( s = fetch ( n ), s == 0 ) r += ( ( 1 << n ) - 1 ) ;
    return ( r + s ) ;
}


/*
    DECODE A TDF INTEGER

    A TDF integer is decoded and returned as a long (no overflow checks).
*/

long tdf_int
    PROTO_Z ()
{
    long d, n = 0 ;
    do {
	d = fetch ( 4 ) ;
	n = 8 * n + ( d & 7 ) ;
    } while ( !( d & 8 ) ) ;
    return ( n ) ;
}


/*
    DECODE A TOKEN APPLICATION

    A token application returning sort s is appended to p.  If s is
    SORT_unknown a simple token (rather than a token application) is
    read.
*/

construct *de_token
    PROTO_N ( ( p, s ) )
    PROTO_T ( node *p X sortname s )
{
    long bits ;
    construct *t ;
    tok_info *info ;
    construct dummy ;

    /* Find token type */
    long n = de_token_bits () ;
    if ( n == ENC_make_tok ) {
	long m = tdf_int () ;
	t = find_binding ( crt_binding, tok_var, m ) ;
	info = get_tok_info ( t ) ;
	p->son = new_node () ;
	p->son->cons = t ;
    } else if ( n == ENC_use_tokdef ) {
	char *nm ;
	t = make_construct ( SORT_token ) ;
	nm = alloc_nof ( char, 32 ) ;
	IGNORE sprintf ( nm, "~~token_%ld", t->encoding ) ;
	t->name = nm ;
	if ( add_to_var_hash ( t, SORT_token ) ) {
	    input_error ( "%s has already been defined", nm ) ;
	}
	de_token_defn ( t, ( node * ) null ) ;
	info = get_tok_info ( t ) ;
	p->son = new_node () ;
	p->son->cons = t ;
    } else {
	high_sort *h ;
	construct *tt ;
	tt = de_token ( p, SORT_token ) ;
	info = get_tok_info ( tt ) ;
	h = high_sorts + high_no ( info->res ) ;
	dummy.name = "high level token" ;
	dummy.u.tok_u.res = h->res ;
	dummy.u.tok_u.args = find_decode_string ( h ) ;
	t = &dummy ;
	info = &dummy.u.tok_u ;
    }

    /* Quit here if only reading token */
    if ( s == SORT_unknown ) {
	if ( !text_output ) {
	    p->son->son = new_node () ;
	    p->son->son->cons = &token_cons ;
	}
	return ( null ) ;
    }

    /* Find the length of the arguments */
    bits = tdf_int () ;

    if ( info->res == SORT_unknown ) {
	/* Unknown token */
	if ( bits ) {
	    /* Step over arguments */
	    char *args ;
	    if ( streq ( t->name, "~dg_exp" ) ) {
		args = "xFF" ;
	    } else if ( streq ( t->name, "~exp_to_source" ) ) {
		args = "xFF" ;
	    } else if ( streq ( t->name, "~diag_id_scope" ) ) {
		args = "x$xF" ;
	    } else if ( streq ( t->name, "~diag_type_scope" ) ) {
		args = "x$F" ;
	    } else if ( streq ( t->name, "~diag_tag_scope" ) ) {
		args = "x$F" ;
	    } else {
		warning ( "Token %s undeclared", t->name ) ;
		args = "F" ;
	    }
	    bits += input_posn () ;
	    p->son->son = de_node ( args ) ;
	    bits -= input_posn () ;
	    if ( bits < 0 ) {
		input_error ( "Token %s, arguments length wrong", t->name ) ;
		return ( t ) ;
	    }
	    input_skip ( bits ) ;
	} else {
	    /* No argument - can deduce token sort */
	    info->res = s ;
	    info->dec = 1 ;
	}
    } else {
	/* Known token */
	if ( s == SORT_token ) {
	    /* Must be high level */
	    if ( !is_high ( info->res ) ) {
		input_error ( "Sort error in token %s", t->name ) ;
	    }
	} else if ( info->res != s ) {
	    /* Result sort must match */
	    input_error ( "Sort error in token %s", t->name ) ;
	}
	if ( info->args ) {
	    /* Decode arguments */
	    long end_posn = input_posn () + bits ;
	    p->son->son = de_node ( info->args ) ;
	    if ( input_posn () != end_posn ) {
		input_error ( "Token %s, arguments length wrong", t->name ) ;
		return ( t ) ;
	    }
	} else {
	    /* No arguments */
	    if ( bits ) {
		input_error ( "Token %s, arguments length wrong", t->name ) ;
		return ( t ) ;
	    }
	}
	info->dec = 1 ;
    }

    /* Mark used tokens */
    if ( info->dec ) adjust_token ( t ) ;
    return ( t ) ;
}


/*
    DECODE A VARIABLE SORT

    A construct of the vth variable sort is decoded.
*/

node *de_var_sort
    PROTO_N ( ( v ) )
    PROTO_T ( long v )
{
    long n = tdf_int () ;
    node *p = new_node () ;
    p->cons = find_binding ( crt_binding, v, n ) ;
    return ( p ) ;
}


/*
    DECODE A LABEL

    A label construct is decoded.
*/

void de_make_label
    PROTO_N ( ( p ) )
    PROTO_T ( node *p )
{
    long n = tdf_int () ;
    p->son = new_node () ;
    p->son->cons = find_label ( n ) ;
    return ;
}


/*
    DECODE A STRING OF DECODE CHARACTERS

    The string of decode character str is decoded.
*/

node *de_node
    PROTO_N ( ( str ) )
    PROTO_T ( char *str )
{
    char c ;
    node *p, *q = null, *qe = null ;
    while ( c = *str, c != 0 && c != ']' ) {
	switch ( c ) {

	    case '[' :
	    case '{' :
	    case '}' :
	    case '&' :
	    case '^' : {
		/* Ignore these cases */
		p = null ;
		break ;
	    }

	    case '|' : {
		/* Align input stream */
		byte_align () ;
		p = null ;
		break ;
	    }

	    case 'i' : {
		/* Decode an integer as a string of octal digits */
		long d, n = 0 ;
		char buff [1000] ;
		do {
		    d = fetch ( 4 ) ;
		    buff [n] = ( char ) ( '0' + ( d & 7 ) ) ;
		    n++ ;
		} while ( !( d & 8 ) ) ;
		buff [n] = 0 ;
		p = new_node () ;
		p->cons = new_construct () ;
		if ( fits_ulong ( buff, 1 ) ) {
		    p->cons->sortnum = SORT_small_tdfint ;
		    p->cons->encoding = ( long ) octal_to_ulong ( buff ) ;
		} else {
		    p->cons->sortnum = SORT_tdfint ;
		    p->cons->name = string_copy_aux ( buff ) ;
		}
		break ;
	    }

	    case 'j' : {
		/* Decode a bit */
		p = new_node () ;
		p->cons = ( tdf_bool () ? &true_cons : &false_cons ) ;
		break ;
	    }

	    case '$' : {
		/* Decode a string */
		long i, n = tdf_int () ;
		if ( n == 8 ) {
		    char *s ;
		    n = tdf_int () ;
		    s = alloc_nof ( char, n + 1 ) ;
		    p = new_node () ;
		    p->cons = new_construct () ;
		    p->cons->sortnum = SORT_tdfstring ;
		    p->cons->encoding = n ;
		    p->cons->name = s ;
		    p->cons->next = null ;
		    for ( i = 0 ; i < n ; i++ ) {
			s [i] = ( char ) fetch ( 8 ) ; /* LINT */
		    }
		    s [n] = 0 ;
		} else {
		    long m ;
		    node *px ;
		    p = new_node () ;
		    p->cons = &string_cons ;
		    p->son = make_int ( n ) ;
		    m = tdf_int () ;
		    px = new_node () ;
		    px->cons = new_construct () ;
		    px->cons->sortnum = SORT_repeat ;
		    px->cons->encoding = m ;
		    p->son->bro->bro = px ;
		    for ( i = 0 ; i < m ; i++ ) {
			long v = fetch ( ( int ) n ) ;
			if ( i == 0 ) {
			    px->son = make_int ( v ) ;
			    px = px->son ;
			} else {
			    px->bro->bro = make_int ( v ) ;
			    px = px->bro->bro ;
			}
		    }
		}
		break ;
	    }

	    case '=' : {
		/* Decode an aligned string */
		char *s ;
		long i, n = tdf_int () ;
		if ( n != 8 ) input_error ( "Only 8-bit strings allowed" ) ;
		n = tdf_int () ;
		byte_align () ;
		s = alloc_nof ( char, n + 1 ) ;
		p = new_node () ;
		p->cons = new_construct () ;
		p->cons->sortnum = SORT_tdfstring ;
		p->cons->encoding = n ;
		p->cons->name = s ;
		p->cons->next = null ;
		for ( i = 0 ; i < n ; i++ ) {
		    s [i] = ( char ) fetch ( 8 ) ; /* LINT */
		}
		s [n] = 0 ;
		byte_align () ;
		break ;
	    }

	    case '*' : {
		/* The following text is repeated n times */
		de_list_start () ;
		goto percent_case ;
	    }

	    case '%' :
	    percent_case : {
		/* The following text is repeated n times */
		node *pe = null ;
		long i, n = tdf_int () ;
		p = new_node () ;
		p->cons = new_construct () ;
		p->cons->sortnum = SORT_repeat ;
		p->cons->encoding = n ;
		str += 2 ;
		for ( i = 0 ; i < n ; i++ ) {
		    node *pi = de_node ( str ) ;
		    if ( pe == null ) {
			p->son = pi ;
		    } else {
			pe->bro = pi ;
		    }
		    pe = pi ;
		    while ( pe->bro ) pe = pe->bro ;
		}
		str = skip_text ( str ) ;
		break ;
	    }

	    case '?' : {
		/* The following text is optional */
		p = new_node () ;
		p->cons = &optional_cons ;
		str += 2 ;
		if ( tdf_bool () ) {
		    p->son = de_node ( str ) ;
		    if ( *str == '*' && p->son->cons->encoding == 0 ) {
			/* Get rid of optional empty lists */
			p->son = null ;
		    }
		}
		str = skip_text ( str ) ;
		break ;
	    }

	    case '@' : {
		/* The following text is a bitstream */
		long len, pos ;
		str += 2 ;
		len = tdf_int () ;
		pos = input_posn () ;
		p = new_node () ;
		p->cons = &bytestream_cons ;
		p->son = de_node ( str ) ;
		if ( len + pos != input_posn () ) {
		    input_error ( "Conditional length wrong" ) ;
		}
		str = skip_text ( str ) ;
		break ;
	    }

	    case 'T' : {
		node dummy ;
		str = find_sortname ( str, ( sortname * ) null ) ;
		IGNORE de_token ( &dummy, SORT_unknown ) ;
		p = dummy.son ;
		break ;
	    }

	    case 'F' : {
		/* Unknown sort */
		p = new_node () ;
		p->cons = &unknown_cons ;
		break ;
	    }

	    default : {
		/* Basic sorts */
		sortname s = find_sort ( c ) ;
		p = ( sort_decode [s] ) () ;
		break ;
	    }
	}
	if ( p ) {
	    if ( qe == null ) {
		q = p ;
	    } else {
		qe->bro = p ;
	    }
	    qe = p ;
	    while ( qe->bro ) qe = qe->bro ;
	}
	str++ ;
    }
    return ( q ) ;
}
