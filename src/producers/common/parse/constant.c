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
#include "c_types.h"
#include "etype_ops.h"
#include "exp_ops.h"
#include "flt_ops.h"
#include "ftype_ops.h"
#include "id_ops.h"
#include "nat_ops.h"
#include "str_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "basetype.h"
#include "cast.h"
#include "char.h"
#include "check.h"
#include "constant.h"
#include "convert.h"
#include "expression.h"
#include "file.h"
#include "inttype.h"
#include "literal.h"
#include "syntax.h"
#include "template.h"
#include "tokdef.h"
#include "ustring.h"
#include "xalloc.h"


/*
    SMALL LITERALS

    These arrays are used to hold the small integer literals to avoid
    duplication.
*/

NAT small_nat [ SMALL_NAT_SIZE ] ;
NAT small_neg_nat [ SMALL_NAT_SIZE ] ;


/*
    SMALL NUMBERS

    These strings are used to hold strings representing the small integer
    literals to avoid duplication.
*/

string small_number [ SMALL_FLT_SIZE ] ;


/*
    CREATE A SMALL NUMBER

    This routine returns the element of the arrays small_nat or small_neg_nat
    corresponding to the value v, allocating it if necessary.
*/

NAT make_small_nat
    PROTO_N ( ( v ) )
    PROTO_T ( int v )
{
    NAT n ;
    if ( v >= 0 ) {
	n = small_nat [v] ;
	if ( IS_NULL_nat ( n ) ) {
	    MAKE_nat_small ( ( unsigned ) v, n ) ;
	    small_nat [v] = n ;
	}
    } else {
	v = -v ;
	n = small_neg_nat [v] ;
	if ( IS_NULL_nat ( n ) ) {
	    n = make_small_nat ( v ) ;
	    MAKE_nat_neg ( n, n ) ;
	    small_neg_nat [v] = n ;
	}
    }
    return ( n ) ;
}


/*
    CONSTANT EVALUATION BUFFERS

    These lists are used to hold single digit lists in the constant
    evaluation routines to allow for uniform handling of both small and
    large literals.
*/

static LIST ( unsigned ) small_nat_1 ;
static LIST ( unsigned ) small_nat_2 ;


/*
    ALLOCATE A DIGIT LIST

    This routine allocates a list of digits of length n.  The digits in the
    list are initialised to zero.
*/

static LIST ( unsigned ) digit_list
    PROTO_N ( ( n ) )
    PROTO_T ( unsigned n )
{
    LIST ( unsigned ) p = NULL_list ( unsigned ) ;
    while ( n ) {
	CONS_unsigned ( 0, p, p ) ;
	n-- ;
    }
    return ( p ) ;
}


/*
    MAKE AN EXTENDED VALUE INTO AN INTEGER CONSTANT

    This routine creates an integer constant from an extended value, v.
*/

NAT make_nat_value
    PROTO_N ( ( v ) )
    PROTO_T ( unsigned long v )
{
    NAT n ;
    unsigned lo = LO_HALF ( v ) ;
    unsigned hi = HI_HALF ( v ) ;
    if ( hi ) {
	LIST ( unsigned ) p = NULL_list ( unsigned ) ;
	CONS_unsigned ( hi, p, p ) ;
	CONS_unsigned ( lo, p, p ) ;
	MAKE_nat_large ( p, n ) ;
    } else if ( lo < SMALL_NAT_SIZE ) {
	n = small_nat [ lo ] ;
	if ( IS_NULL_nat ( n ) ) n = make_small_nat ( ( int ) lo ) ;
    } else {
	MAKE_nat_small ( lo, n ) ;
    }
    return ( n ) ;
}


/*
    MAKE AN INTEGER CONSTANT INTO AN EXTENDED VALUE

    This routine finds the extended value corresponding to the integer
    constant n.  If n is the null constant or does not fit into an extended
    value then the maximum extended value is returned.
*/

unsigned long get_nat_value
    PROTO_N ( ( n ) )
    PROTO_T ( NAT n )
{
    if ( !IS_NULL_nat ( n ) ) {
	unsigned tag = TAG_nat ( n ) ;
	if ( tag == nat_small_tag ) {
	    unsigned val = DEREF_unsigned ( nat_small_value ( n ) ) ;
	    return ( EXTEND_VALUE ( val ) ) ;
	} else if ( tag == nat_large_tag ) {
	    LIST ( unsigned ) p = DEREF_list ( nat_large_values ( n ) ) ;
	    if ( LENGTH_list ( p ) == 2 ) {
		unsigned v1, v2 ;
		v1 = DEREF_unsigned ( HEAD_list ( p ) ) ;
		v2 = DEREF_unsigned ( HEAD_list ( TAIL_list ( p ) ) ) ;
		return ( COMBINE_VALUES ( v1, v2 ) ) ;
	    }
	}
    }
    return ( EXTENDED_MAX ) ;
}


/*
    MAKE A LIST OF DIGITS INTO AN INTEGER CONSTANT

    This routine creates an integer constant from a list of digits, p.
    This list may contain initial zero digits, which need to be removed.
*/

NAT make_large_nat
    PROTO_N ( ( p ) )
    PROTO_T ( LIST ( unsigned ) p )
{
    NAT n ;
    LIST ( unsigned ) q = p ;
    LIST ( unsigned ) r = p ;

    /* Scan for last nonzero digit */
    while ( !IS_NULL_list ( q ) ) {
	unsigned v = DEREF_unsigned ( HEAD_list ( q ) ) ;
	if ( v != 0 ) r = q ;
	q = TAIL_list ( q ) ;
    }

    /* Construct result */
    if ( EQ_list ( r, p ) ) {
	/* Small values */
	unsigned v = DEREF_unsigned ( HEAD_list ( p ) ) ;
	if ( v < SMALL_NAT_SIZE ) {
	    n = make_small_nat ( ( int ) v ) ;
	} else {
	    MAKE_nat_small ( v, n ) ;
	}
	DESTROY_list ( p, SIZE_unsigned ) ;
    } else {
	/* Large values */
	q = TAIL_list ( r ) ;
	COPY_list ( PTR_TAIL_list ( r ), NULL_list ( unsigned ) ) ;
	DESTROY_list ( q, SIZE_unsigned ) ;
	MAKE_nat_large ( p, n ) ;
    }
    return ( n ) ;
}


/*
    BUILD UP AN INTEGER CONSTANT

    This routine multiplies the integer constant n by b and adds d.  It is
    used when building up integer constants from strings of digits - b gives
    the base and d the digit being added.  b will not be zero, and n will
    be a simple constant.  Note that the original value of n is overwritten
    with the return value.
*/

NAT make_nat_literal
    PROTO_N ( ( n, b, d ) )
    PROTO_T ( NAT n X unsigned b X unsigned d )
{
    NAT res ;
    unsigned long lb = EXTEND_VALUE ( b ) ;

    if ( IS_NULL_nat ( n ) ) {
	/* Map null integer to zero */
	unsigned long ld = EXTEND_VALUE ( d ) ;
	res = make_nat_value ( ld ) ;

    } else if ( IS_nat_small ( n ) ) {
	/* Small integers */
	unsigned val = DEREF_unsigned ( nat_small_value ( n ) ) ;
	unsigned long lv = EXTEND_VALUE ( val ) ;
	unsigned long ld = EXTEND_VALUE ( d ) ;
	unsigned long lr = lv * lb + ld ;
	unsigned r1 = LO_HALF ( lr ) ;
	unsigned r2 = HI_HALF ( lr ) ;

	if ( r2 == 0 ) {
	    /* Result remains small */
	    if ( r1 < SMALL_NAT_SIZE ) {
		res = small_nat [ r1 ] ;
		if ( IS_NULL_nat ( res ) ) {
		    res = make_small_nat ( ( int ) r1 ) ;
		}
	    } else if ( val < SMALL_NAT_SIZE ) {
		MAKE_nat_small ( r1, res ) ;
	    } else {
		COPY_unsigned ( nat_small_value ( n ), r1 ) ;
		res = n ;
	   }
	} else {
	    /* Overflow - create large integer */
	    LIST ( unsigned ) digits = NULL_list ( unsigned ) ;
	    if ( val >= SMALL_NAT_SIZE ) {
		unsigned ign ;
		DESTROY_nat_small ( destroy, ign, n ) ;
		UNUSED ( ign ) ;
	    }
	    CONS_unsigned ( r2, digits, digits ) ;
	    CONS_unsigned ( r1, digits, digits ) ;
	    MAKE_nat_large ( digits, res ) ;
	}

    } else {
	/* Large integers */
	LIST ( unsigned ) vals = DEREF_list ( nat_large_values ( n ) ) ;
	LIST ( unsigned ) v = vals ;
	unsigned carry = d ;

	/* Scan through digits */
	while ( !IS_NULL_list ( v ) ) {
	    unsigned val = DEREF_unsigned ( HEAD_list ( v ) ) ;
	    unsigned long lv = EXTEND_VALUE ( val ) ;
	    unsigned long lc = EXTEND_VALUE ( carry ) ;
	    unsigned long lr = lv * lb + lc ;
	    COPY_unsigned ( HEAD_list ( v ), LO_HALF ( lr ) ) ;
	    carry = HI_HALF ( lr ) ;
	    v = TAIL_list ( v ) ;
	}

	if ( carry ) {
	    /* Overflow - add an extra digit */
	    CONS_unsigned ( carry, NULL_list ( unsigned ), v ) ;
	    IGNORE APPEND_list ( vals, v ) ;
	}
	res = n ;
    }
    return ( res ) ;
}


/*
    IS AN INTEGER CONSTANT ZERO?

    This routine checks whether the integer constant n is zero.
*/

int is_zero_nat
    PROTO_N ( ( n ) )
    PROTO_T ( NAT n )
{
    unsigned val ;
    if ( !IS_nat_small ( n ) ) return ( 0 ) ;
    val = DEREF_unsigned ( nat_small_value ( n ) ) ;
    return ( val ? 0 : 1 ) ;
}


/*
    IS AN INTEGER CONSTANT NEGATIVE?

    This routine checks whether the integer constant n is negative.
*/

int is_negative_nat
    PROTO_N ( ( n ) )
    PROTO_T ( NAT n )
{
    return ( IS_nat_neg ( n ) ) ;
}


/*
    IS AN INTEGER CONSTANT AN ERROR EXPRESSION?

    This routine checks whether the integer constant n represents an error
    expression.
*/

int is_error_nat
    PROTO_N ( ( n ) )
    PROTO_T ( NAT n )
{
    if ( IS_nat_calc ( n ) ) {
	EXP e = DEREF_exp ( nat_calc_value ( n ) ) ;
	TYPE t = DEREF_type ( exp_type ( e ) ) ;
	return ( IS_type_error ( t ) ) ;
    }
    return ( 0 ) ;
}


/*
    IS AN INTEGER CONSTANT A CALCULATED VALUE?

    This routine checks whether the integer constant n is a calculated
    value.
*/

int is_calc_nat
    PROTO_N ( ( n ) )
    PROTO_T ( NAT n )
{
    unsigned tag = TAG_nat ( n ) ;
    if ( tag == nat_neg_tag ) {
	n = DEREF_nat ( nat_neg_arg ( n ) ) ;
	tag = TAG_nat ( n ) ;
    }
    if ( tag == nat_calc_tag || tag == nat_token_tag ) return ( 1 ) ;
    return ( 0 ) ;
}


/*
    FIND THE VALUE OF A CALCULATED CONSTANT

    This routine creates an integer constant expression of type t with
    value n.
*/

EXP calc_nat_value
    PROTO_N ( ( n, t ) )
    PROTO_T ( NAT n X TYPE t )
{
    EXP e ;
    TYPE s = t ;
    int ch = check_nat_range ( s, n ) ;
    if ( ch != 0 ) {
	/* n doesn't fit into t */
	int fit = 0 ;
	string str = NULL_string ;
	s = find_literal_type ( n, BASE_OCTAL, SUFFIX_NONE, str, &fit ) ;
    }
    MAKE_exp_int_lit ( s, n, exp_token_tag, e ) ;
    if ( !EQ_type ( s, t ) ) {
	e = make_cast_nat ( t, e, KILL_err, CAST_STATIC ) ;
    }
    return ( e ) ;
}


/*
    SIMPLIFY AN INTEGER CONSTANT EXPRESSION

    This routine simplifies the integer constant expression e by replacing
    it by the value of a calculated constant.  This is avoided when this
    constant may be tokenised.
*/

static EXP calc_exp_value
    PROTO_N ( ( e ) )
    PROTO_T ( EXP e )
{
    NAT n = DEREF_nat ( exp_int_lit_nat ( e ) ) ;
    if ( IS_nat_calc ( n ) ) {
	/* Calculated value */
	unsigned etag = DEREF_unsigned ( exp_int_lit_etag ( e ) ) ;
	if ( etag != exp_identifier_tag ) {
	    /* Preserve enumerators */
	    e = DEREF_exp ( nat_calc_value ( n ) ) ;
	}
    }
    return ( e ) ;
}


/*
    NEGATE AN INTEGER CONSTANT

    This routine negates the integer constant n.
*/

NAT negate_nat
    PROTO_N ( ( n ) )
    PROTO_T ( NAT n )
{
    if ( !IS_NULL_nat ( n ) ) {
	switch ( TAG_nat ( n ) ) {
	    case nat_small_tag : {
		unsigned val = DEREF_unsigned ( nat_small_value ( n ) ) ;
		if ( val < SMALL_NAT_SIZE ) {
		    n = small_neg_nat [ val ] ;
		    if ( IS_NULL_nat ( n ) ) {
			int v = ( int ) val ;
			n = make_small_nat ( -v ) ;
		    }
		    break ;
		}
		goto default_lab ;
	    }
	    case nat_neg_tag : {
		n = DEREF_nat ( nat_neg_arg ( n ) ) ;
		break ;
	    }
	    case nat_calc_tag : {
		EXP e = DEREF_exp ( nat_calc_value ( n ) ) ;
		e = make_uminus_exp ( lex_minus, e ) ;
		MAKE_nat_calc ( e, n ) ;
		break ;
	    }
	    default :
	    default_lab : {
		MAKE_nat_neg ( n, n ) ;
		break ;
	    }
	}
    }
    return ( n ) ;
}


/*
    COMPARE TWO INTEGER CONSTANTS

    This routine compares the integer constants n and m.  It returns 0 if
    they are equal, 1 if n > m and -1 if n < m.  A value of 2 or -2 is
    returned if the result is target dependent or otherwise indeterminate.
*/

int compare_nat
    PROTO_N ( ( n, m ) )
    PROTO_T ( NAT n X NAT m )
{
    unsigned tn, tm ;
    unsigned vn, vm ;
    LIST ( unsigned ) ln, lm ;

    /* Check for obvious equality */
    if ( EQ_nat ( n, m ) ) return ( 0 ) ;
    if ( IS_NULL_nat ( n ) ) return ( 2 ) ;
    if ( IS_NULL_nat ( m ) ) return ( -2 ) ;
    tn = TAG_nat ( n ) ;
    tm = TAG_nat ( m ) ;

    /* Check for tokenised values */
    if ( tn == nat_token_tag ) {
	if ( tm == nat_token_tag ) {
	    IDENTIFIER in = DEREF_id ( nat_token_tok ( n ) ) ;
	    IDENTIFIER im = DEREF_id ( nat_token_tok ( m ) ) ;
	    LIST ( TOKEN ) pn = DEREF_list ( nat_token_args ( n ) ) ;
	    LIST ( TOKEN ) pm = DEREF_list ( nat_token_args ( m ) ) ;
	    if ( eq_token_args ( in, im, pn, pm ) ) return ( 0 ) ;
	}
	return ( 2 ) ;
    }
    if ( tm == nat_token_tag ) {
	return ( 2 ) ;
    }

    /* Check for calculated values */
    if ( tn == nat_calc_tag ) {
	if ( tm == nat_calc_tag ) {
	    EXP en = DEREF_exp ( nat_calc_value ( n ) ) ;
	    EXP em = DEREF_exp ( nat_calc_value ( m ) ) ;
	    if ( eq_exp ( en, em, 1 ) ) return ( 0 ) ;
	}
	return ( 2 ) ;
    }
    if ( tm == nat_calc_tag ) {
	return ( 2 ) ;
    }

    /* Deal with negation operations */
    if ( tn == nat_neg_tag ) {
	if ( tm == nat_neg_tag ) {
	    /* Both negative */
	    int c ;
	    n = DEREF_nat ( nat_neg_arg ( n ) ) ;
	    m = DEREF_nat ( nat_neg_arg ( m ) ) ;
	    c = compare_nat ( n, m ) ;
	    return ( -c ) ;
	}
	/* n negative, m positive */
	return ( -1 ) ;
    }
    if ( tm == nat_neg_tag ) {
	/* m negative, n positive */
	return ( 1 ) ;
    }

    /* Now deal with small integers */
    if ( tn == nat_small_tag ) {
	if ( tm == nat_small_tag ) {
	    /* Both small */
	    vn = DEREF_unsigned ( nat_small_value ( n ) ) ;
	    vm = DEREF_unsigned ( nat_small_value ( m ) ) ;
	    if ( vn == vm ) return ( 0 ) ;
	    return ( vn > vm ? 1 : -1 ) ;
	} else {
	    /* n small, m large */
	    return ( -1 ) ;
	}
    }
    if ( tm == nat_small_tag ) {
	/* m small, n large */
	return ( 1 ) ;
    }

    /* Now deal with large integers */
    ln = DEREF_list ( nat_large_values ( n ) ) ;
    lm = DEREF_list ( nat_large_values ( m ) ) ;
    vn = LENGTH_list ( ln ) ;
    vm = LENGTH_list ( lm ) ;
    if ( vn == vm ) {
	/* Same length */
	int c = 0 ;
	while ( !IS_NULL_list ( ln ) ) {
	    /* Scan through digits */
	    vn = DEREF_unsigned ( HEAD_list ( ln ) ) ;
	    vm = DEREF_unsigned ( HEAD_list ( lm ) ) ;
	    if ( vn != vm ) {
		c = ( vn > vm ? 1 : -1 ) ;
	    }
	    ln = TAIL_list ( ln ) ;
	    lm = TAIL_list ( lm ) ;
	}
	/* c is set to the most significant difference */
	return ( c ) ;
    }
    /* Different lengths */
    return ( vn > vm ? 1 : -1 ) ;
}


/*
    UNIFY TWO INTEGER LITERALS

    This routine unifies the integer literals n and m by defining tokens
    if possible.  It returns true if the token is assigned a value.
*/

static int unify_nat
    PROTO_N ( ( n, m ) )
    PROTO_T ( NAT n X NAT m )
{
    IDENTIFIER id ;
    LIST ( TOKEN ) args ;
    switch ( TAG_nat ( n ) ) {
	case nat_token_tag : {
	    id = DEREF_id ( nat_token_tok ( n ) ) ;
	    args = DEREF_list ( nat_token_args ( n ) ) ;
	    break ;
	}
	case nat_calc_tag : {
	    EXP e = DEREF_exp ( nat_calc_value ( n ) ) ;
	    if ( !IS_exp_token ( e ) ) return ( 0 ) ;
	    id = DEREF_id ( exp_token_tok ( e ) ) ;
	    args = DEREF_list ( exp_token_args ( e ) ) ;
	    break ;
	}
	default : {
	    return ( 0 ) ;
	}
    }
    if ( IS_NULL_list ( args ) && defining_token ( id ) ) {
	return ( define_nat_token ( id, m ) ) ;
    }
    return ( 0 ) ;
}


/*
    ARE TWO INTEGER LITERALS EQUAL?

    This routine returns true if the literals n and m are equal.
*/

int eq_nat
    PROTO_N ( ( n, m ) )
    PROTO_T ( NAT n X NAT m )
{
    if ( EQ_nat ( n, m ) ) return ( 1 ) ;
    if ( IS_NULL_nat ( n ) || IS_NULL_nat ( m ) ) return ( 0 ) ;
    if ( compare_nat ( n, m ) == 0 ) return ( 1 ) ;
    if ( force_tokdef || force_template || expand_tokdef ) {
	if ( unify_nat ( n, m ) ) return ( 1 ) ;
	if ( unify_nat ( m, n ) ) return ( 1 ) ;
    }
    return ( 0 ) ;
}


/*
    PERFORM A BINARY INTEGER CONSTANT CALCULATION

    This routine is used to evaluate the binary operation indicated by tag
    on the integer constants a and b, which will be simple literals.  The
    permitted operations are '+', '-', '*', '/', '%', '<<', '>>', '&', '|',
    and '^'.  The null literal is returned for undefined or implementation
    dependent calculations.
*/

NAT binary_nat_op
    PROTO_N ( ( tag, a, b ) )
    PROTO_T ( unsigned tag X NAT a X NAT b )
{
    unsigned vn, vm ;
    NAT n = a, m = b ;
    NAT res = NULL_nat ;
    int sn = 0, sm = 0 ;
    unsigned ln, lm, la ;
    LIST ( unsigned ) p, q ;
    LIST ( unsigned ) pn, pm ;

    /* Decompose n */
    if ( IS_NULL_nat ( n ) ) return ( NULL_nat ) ;
    if ( IS_NULL_nat ( m ) ) return ( NULL_nat ) ;
    if ( IS_nat_neg ( n ) ) {
	n = DEREF_nat ( nat_neg_arg ( n ) ) ;
	sn = 1 ;
    }
    if ( IS_nat_small ( n ) ) {
	vn = DEREF_unsigned ( nat_small_value ( n ) ) ;
	if ( vn == 0 ) {
	    /* Find results if a is zero */
	    switch ( tag ) {
		case exp_plus_tag :
		case exp_or_tag :
		case exp_xor_tag : {
		    /* 0 op b = b */
		    return ( b ) ;
		}
		case exp_minus_tag : {
		    /* 0 - b = -b */
		    res = negate_nat ( b ) ;
		    return ( res ) ;
		}
		case exp_mult_tag :
		case exp_lshift_tag :
		case exp_rshift_tag :
		case exp_and_tag : {
		    /* 0 op b = 0 */
		    return ( a ) ;
		}
	    }
	}
	pn = small_nat_1 ;
	COPY_unsigned ( HEAD_list ( pn ), vn ) ;
	ln = 1 ;
    } else {
	vn = 0 ;
	pn = DEREF_list ( nat_large_values ( n ) ) ;
	ln = LENGTH_list ( pn ) ;
    }

    /* Decompose m */
    if ( IS_nat_neg ( m ) ) {
	m = DEREF_nat ( nat_neg_arg ( m ) ) ;
	sm = 1 ;
    }
    if ( IS_nat_small ( m ) ) {
	vm = DEREF_unsigned ( nat_small_value ( m ) ) ;
	if ( vm == 0 ) {
	    /* Find results if b is zero */
	    switch ( tag ) {
		case exp_plus_tag :
		case exp_minus_tag :
		case exp_lshift_tag :
		case exp_rshift_tag :
		case exp_or_tag :
		case exp_xor_tag : {
		    /* a op 0 = a */
		    return ( a ) ;
		}
		case exp_mult_tag :
		case exp_and_tag : {
		    /* a op 0 = 0 */
		    return ( b ) ;
		}
		case exp_div_tag :
		case exp_rem_tag : {
		    /* a op 0 undefined */
		    return ( NULL_nat ) ;
		}
	    }
	}
	pm = small_nat_2 ;
	COPY_unsigned ( HEAD_list ( pm ), vm ) ;
	lm = 1 ;
    } else {
	vm = 0 ;
	pm = DEREF_list ( nat_large_values ( m ) ) ;
	lm = LENGTH_list ( pm ) ;
    }

    /* Find the larger of ln and lm */
    la = ( ln > lm ? ln : lm ) ;

    /* Perform the appropriate calculation */
    switch ( tag ) {

	case exp_plus_tag :
	exp_plus_label : {
	    /* Deal with 'a + b' */
	    if ( sn == sm ) {
		/* Same sign */
		if ( la == 1 ) {
		    /* Add two small values */
		    unsigned long en = EXTEND_VALUE ( vn ) ;
		    unsigned long em = EXTEND_VALUE ( vm ) ;
		    unsigned long er = en + em ;
		    res = make_nat_value ( er ) ;
		} else {
		    /* Add two large values */
		    unsigned carry = 0 ;
		    p = digit_list ( la + 1 ) ;
		    q = p ;
		    while ( !IS_NULL_list ( q ) ) {
			unsigned long en, em, er ;
			unsigned long ec = EXTEND_VALUE ( carry ) ;
			if ( !IS_NULL_list ( pn ) ) {
			    vn = DEREF_unsigned ( HEAD_list ( pn ) ) ;
			    en = EXTEND_VALUE ( vn ) ;
			    pn = TAIL_list ( pn ) ;
			} else {
			    en = 0 ;
			}
			if ( !IS_NULL_list ( pm ) ) {
			    vm = DEREF_unsigned ( HEAD_list ( pm ) ) ;
			    em = EXTEND_VALUE ( vm ) ;
			    pm = TAIL_list ( pm ) ;
			} else {
			    em = 0 ;
			}
			er = en + em + ec ;
			COPY_unsigned ( HEAD_list ( q ), LO_HALF ( er ) ) ;
			carry = HI_HALF ( er ) ;
			q = TAIL_list ( q ) ;
		    }
		    res = make_large_nat ( p ) ;
		}
		if ( sn ) res = negate_nat ( res ) ;
	    } else {
		/* Different signs - try 'a - ( -b )' */
		sm = !sm ;
		goto exp_minus_label ;
	    }
	    break ;
	}

	case exp_minus_tag :
	exp_minus_label : {
	    /* Deal with 'a - b' */
	    if ( sn == sm ) {
		/* Same sign */
		int c ;
		if ( ln == lm ) {
		    /* Same length */
		    c = compare_nat ( n, m ) ;
		    if ( c == 0 ) {
			/* n - m is zero if n == m */
			res = small_nat [0] ;
			break ;
		    }
		} else if ( ln < lm ) {
		    /* Definitely n < m */
		    c = -1 ;
		} else {
		    /* Definitely n > m */
		    c = 1 ;
		}
		if ( c < 0 ) {
		    /* If n < m, try '( -m ) - ( -n )' */
		    unsigned v = vn ;
		    vn = vm ;
		    vm = v ;
		    p = pn ;
		    pn = pm ;
		    pm = p ;
		    sn = !sn ;
		}
		/* Now work out n - m */
		if ( la == 1 ) {
		    /* Subtract two small values */
		    unsigned long en = EXTEND_VALUE ( vn ) ;
		    unsigned long em = EXTEND_VALUE ( vm ) ;
		    unsigned long er = en - em ;
		    res = make_nat_value ( er ) ;
		} else {
		    /* Subtract two large values */
		    int carry = 0 ;
		    p = digit_list ( la ) ;
		    q = p ;
		    while ( !IS_NULL_list ( q ) ) {
			unsigned v ;
			if ( !IS_NULL_list ( pn ) ) {
			    vn = DEREF_unsigned ( HEAD_list ( pn ) ) ;
			    pn = TAIL_list ( pn ) ;
			} else {
			    vn = 0 ;
			}
			if ( !IS_NULL_list ( pm ) ) {
			    vm = DEREF_unsigned ( HEAD_list ( pm ) ) ;
			    pm = TAIL_list ( pm ) ;
			} else {
			    vm = 0 ;
			}
			if ( carry ) {
			    if ( vn ) {
				vn-- ;
				carry = 0 ;
			    } else {
				vn = NAT_MASK ;
			    }
			}
			if ( vn < vm ) carry = 1 ;
			v = ( ( vn - vm ) & NAT_MASK ) ;
			COPY_unsigned ( HEAD_list ( q ), v ) ;
			q = TAIL_list ( q ) ;
		    }
		    res = make_large_nat ( p ) ;
		}
		if ( sn ) res = negate_nat ( res ) ;
	    } else {
		/* Different signs - try 'a + ( -b )' */
		sm = !sm ;
		goto exp_plus_label ;
	    }
	    break ;
	}

	case exp_mult_tag : {
	    /* Deal with 'a * b' */
	    if ( ln == 1 && vn == 1 ) {
		/* Multiply by +/- 1 */
		res = b ;
		if ( sn ) res = negate_nat ( res ) ;
		break ;
	    }
	    if ( lm == 1 && vm == 1 ) {
		/* Multiply by +/- 1 */
		res = a ;
		if ( sm ) res = negate_nat ( res ) ;
		break ;
	    }
	    if ( la == 1 ) {
		/* Deal with small values */
		unsigned long en = EXTEND_VALUE ( vn ) ;
		unsigned long em = EXTEND_VALUE ( vm ) ;
		unsigned long er = en * em ;
		res = make_nat_value ( er ) ;
	    } else {
		/* Deal with large values */
		unsigned vs ;
		unsigned long en, em, es ;
		LIST ( unsigned ) pr, ps, pt ;
		p = digit_list ( ln + lm ) ;
		q = p ;
		while ( !IS_NULL_list ( pn ) ) {
		    pr = q ;
		    vn = DEREF_unsigned ( HEAD_list ( pn ) ) ;
		    en = EXTEND_VALUE ( vn ) ;
		    pt = pm ;
		    while ( !IS_NULL_list ( pt ) ) {
			ps = pr ;
			vm = DEREF_unsigned ( HEAD_list ( pt ) ) ;
			em = en * EXTEND_VALUE ( vm ) ;
			while ( em ) {
			    vs = DEREF_unsigned ( HEAD_list ( ps ) ) ;
			    es = EXTEND_VALUE ( vs ) + em ;
			    vs = LO_HALF ( es ) ;
			    COPY_unsigned ( HEAD_list ( ps ), vs ) ;
			    em = EXTEND_VALUE ( HI_HALF ( es ) ) ;
			    ps = TAIL_list ( ps ) ;
			}
			pr = TAIL_list ( pr ) ;
			pt = TAIL_list ( pt ) ;
		    }
		    pn = TAIL_list ( pn ) ;
		    q = TAIL_list ( q ) ;
		}
		res = make_large_nat ( p ) ;
	    }
	    if ( sn != sm ) res = negate_nat ( res ) ;
	    break ;
	}

	case exp_div_tag : {
	    /* Deal with 'a / b' */
	    if ( la <= 2 ) {
		/* Deal with smallish values */
		unsigned long en = get_nat_value ( n ) ;
		unsigned long em = get_nat_value ( m ) ;
		unsigned long er = en / em ;
		if ( sn || sm ) {
		    /* One operand is negative, check remainder */
		    unsigned long es = en % em ;
		    if ( es ) break ;
		}
		res = make_nat_value ( er ) ;
		if ( sn != sm ) res = negate_nat ( res ) ;
	    }
	    /* NOT YET IMPLEMENTED */
	    break ;
	}

	case exp_rem_tag : {
	    /* Deal with a % b' */
	    if ( la <= 2 ) {
		/* Deal with smallish values */
		unsigned long en = get_nat_value ( n ) ;
		unsigned long em = get_nat_value ( m ) ;
		unsigned long es = en % em ;
		if ( sn || sm ) {
		    /* One operand is negative, check remainder */
		    if ( es ) break ;
		}
		res = make_nat_value ( es ) ;
	    }
	    /* NOT YET IMPLEMENTED */
	    break ;
	}

	case exp_lshift_tag : {
	    /* Deal with 'a << b' */
	    unsigned carry = 0 ;
	    unsigned long en, em ;
	    if ( sn || sm ) break ;
	    em = get_nat_value ( m ) ;
	    if ( em > 4096 ) {
		/* Only attempt smallish values */
		break ;
	    }
	    lm = ( unsigned ) ( em / NAT_DIGITS ) ;
	    em %= NAT_DIGITS ;
	    la = ln + lm + 1 ;
	    p = digit_list ( la ) ;
	    q = p ;
	    while ( lm ) {
		/* Step over zero digits */
		q = TAIL_list ( q ) ;
		lm-- ;
	    }
	    while ( !IS_NULL_list ( pn ) ) {
		/* Copy remaining digits */
		vn = DEREF_unsigned ( HEAD_list ( pn ) ) ;
		if ( em ) {
		    en = EXTEND_VALUE ( vn ) ;
		    en <<= em ;
		    vn = ( LO_HALF ( en ) | carry ) ;
		    carry = HI_HALF ( en ) ;
		}
		COPY_unsigned ( HEAD_list ( q ), vn ) ;
		pn = TAIL_list ( pn ) ;
		q = TAIL_list ( q ) ;
	    }
	    /* Copy carry flag */
	    COPY_unsigned ( HEAD_list ( q ), carry ) ;
	    res = make_large_nat ( p ) ;
	    break ;
	}

	case exp_rshift_tag : {
	    /* Deal with 'a >> b' */
	    unsigned long en, em ;
	    if ( sn || sm ) break ;
	    em = get_nat_value ( m ) ;
	    while ( em >= NAT_DIGITS && ln ) {
		/* Shift right one nat digit */
		em -= NAT_DIGITS ;
		pn = TAIL_list ( pn ) ;
		ln-- ;
	    }
	    if ( ln == 0 ) {
		/* Shifted off end */
		res = small_nat [0] ;
	    } else if ( ln == 1 ) {
		/* Remainder fits into a single digit */
		vn = DEREF_unsigned ( HEAD_list ( pn ) ) ;
		vn >>= em ;
		if ( vn < SMALL_NAT_SIZE ) {
		    res = make_small_nat ( ( int ) vn ) ;
		} else {
		    MAKE_nat_small ( vn, res ) ;
		}
	    } else {
		/* More than one digit left */
		p = digit_list ( ln ) ;
		q = p ;
		while ( !IS_NULL_list ( pn ) ) {
		    /* Copy remaining digits */
		    vn = DEREF_unsigned ( HEAD_list ( pn ) ) ;
		    COPY_unsigned ( HEAD_list ( q ), vn ) ;
		    pn = TAIL_list ( pn ) ;
		    q = TAIL_list ( q ) ;
		}
		/* Shift further if required */
		if ( em ) {
		    unsigned carry = 0 ;
		    p = REVERSE_list ( p ) ;
		    q = p ;
		    while ( !IS_NULL_list ( q ) ) {
			vn = DEREF_unsigned ( HEAD_list ( q ) ) ;
			en = COMBINE_VALUES ( 0, vn ) ;
			en >>= em ;
			vn = ( HI_HALF ( en ) | carry ) ;
			COPY_unsigned ( HEAD_list ( q ), vn ) ;
			carry = LO_HALF ( en ) ;
			q = TAIL_list ( q ) ;
		    }
		    p = REVERSE_list ( p ) ;
		}
		res = make_large_nat ( p ) ;
	    }
	    break ;
	}

	case exp_and_tag :
	case exp_or_tag :
	case exp_xor_tag : {
	    /* Deal with 'a & b', 'a | b' and 'a ^ b' */
	    if ( sn || sm ) break ;
	    if ( la <= 2 ) {
		/* Deal with smallish values */
		unsigned long er ;
		unsigned long en = get_nat_value ( n ) ;
		unsigned long em = get_nat_value ( m ) ;
		if ( tag == exp_and_tag ) {
		    er = ( en & em ) ;
		} else if ( tag == exp_or_tag ) {
		    er = ( en | em ) ;
		} else {
		    er = ( en ^ em ) ;
		}
		res = make_nat_value ( er ) ;
	    } else {
		/* Deal with large values */
		p = digit_list ( la ) ;
		q = p ;
		while ( !IS_NULL_list ( q ) ) {
		    unsigned vr ;
		    if ( !IS_NULL_list ( pn ) ) {
			vn = DEREF_unsigned ( HEAD_list ( pn ) ) ;
			pn = TAIL_list ( pn ) ;
		    } else {
			vn = 0 ;
		    }
		    if ( !IS_NULL_list ( pm ) ) {
			vm = DEREF_unsigned ( HEAD_list ( pm ) ) ;
			pm = TAIL_list ( pm ) ;
		    } else {
			vm = 0 ;
		    }
		    if ( tag == exp_and_tag ) {
			vr = ( vn & vm ) ;
		    } else if ( tag == exp_or_tag ) {
			vr = ( vn | vm ) ;
		    } else {
			vr = ( vn ^ vm ) ;
		    }
		    COPY_unsigned ( HEAD_list ( q ), vr ) ;
		    q = TAIL_list ( q ) ;
		}
		res = make_large_nat ( p ) ;
	    }
	    break ;
	}
    }
    return ( res ) ;
}


/*
    EVALUATE A CONSTANT EXPRESSION

    This routine transforms the integer constant expression e into an
    integer constant.  Any errors arising are added to the position
    indicated by err.
*/

NAT make_nat_exp
    PROTO_N ( ( e, err ) )
    PROTO_T ( EXP e X ERROR *err )
{
    NAT n ;
    TYPE t ;

    /* Remove any parentheses round e */
    unsigned tag = TAG_exp ( e ) ;
    while ( tag == exp_paren_tag ) {
	e = DEREF_exp ( exp_paren_arg ( e ) ) ;
	tag = TAG_exp ( e ) ;
    }

    /* The result should now be an integer constant */
    if ( tag == exp_int_lit_tag ) {
	n = DEREF_nat ( exp_int_lit_nat ( e ) ) ;
	return ( n ) ;
    }

    /* Check expression type */
    t = DEREF_type ( exp_type ( e ) ) ;
    switch ( TAG_type ( t ) ) {
	case type_integer_tag :
	case type_enumerate_tag :
	case type_bitfield_tag : {
	    /* Double check for integer constants */
	    if ( !is_const_exp ( e, 0 ) ) {
		add_error ( err, ERR_expr_const_bad () ) ;
	    }
	    break ;
	}
	case type_token_tag : {
	    /* Allow template types */
	    if ( !is_templ_type ( t ) ) goto default_lab ;
	    break ;
	}
	case type_error_tag : {
	    /* Allow for error propagation */
	    break ;
	}
	default :
	default_lab : {
	    /* Otherwise report an error */
	    add_error ( err, ERR_expr_const_int ( t ) ) ;
	    if ( IS_exp_float_lit ( e ) ) {
		/* Evaluate floating point literals */
		FLOAT f = DEREF_flt ( exp_float_lit_flt ( e ) ) ;
		n = round_float_lit ( f, crt_round_mode ) ;
		if ( !IS_NULL_nat ( n ) ) return ( n ) ;
	    }
	    e = make_error_exp ( 0 ) ;
	    break ;
	}
    }
    MAKE_nat_calc ( e, n ) ;
    return ( n ) ;
}


/*
    FIND THE NUMBER OF BITS IN AN INTEGER

    This routine returns the number of bits in the integer n from the
    range [0,0xffff].
*/

unsigned no_bits
    PROTO_N ( ( n ) )
    PROTO_T ( unsigned n )
{
    unsigned bits = 0 ;
    static unsigned char small_bits [16] = {
	0, 1, 2, 2, 3, 3, 3, 3,
	4, 4, 4, 4, 4, 4, 4, 4
    } ;
    if ( n & ( ( unsigned ) 0xfff0 ) ) {
	n >>= 4 ;
	bits += 4 ;
	if ( n & 0x0ff0 ) {
	    n >>= 4 ;
	    bits += 4 ;
	    if ( n & 0x00f0 ) {
		n >>= 4 ;
		bits += 4 ;
	    }
	}
    }
    bits += ( unsigned ) small_bits [n] ;
    return ( bits ) ;
}


/*
    FIND THE NUMBER OF BITS IN AN INTEGER CONSTANT

    This routine calculates the number of bits in the representation of
    the simple integer constant n.  The flag eq is set to false unless
    n is exactly a power of 2.
*/

static unsigned get_nat_bits
    PROTO_N ( ( n, eq ) )
    PROTO_T ( NAT n X int *eq )
{
    unsigned val ;
    unsigned bits = 0 ;
    if ( IS_nat_small ( n ) ) {
	val = DEREF_unsigned ( nat_small_value ( n ) ) ;
    } else {
	LIST ( unsigned ) vals = DEREF_list ( nat_large_values ( n ) ) ;
	for ( ; ; ) {
	    val = DEREF_unsigned ( HEAD_list ( vals ) ) ;
	    vals = TAIL_list ( vals ) ;
	    if ( IS_NULL_list ( vals ) ) break ;
	    if ( val ) *eq = 0 ;
	    bits += NAT_DIGITS ;
	}
    }
    if ( val ) {
	/* Check the most significant digit */
	if ( val & ( val - 1 ) ) *eq = 0 ;
	bits += no_bits ( val ) ;
    }
    return ( bits ) ;
}


/*
    CHECK WHETHER AN INTEGER CONSTANT FITS INTO A TYPE

    This routine checks whether the integer constant n fits into the range
    of values of the integral, enumeration or bitfield type t.  The value
    returned is:

	0 if n definitely fits into t,
	1 if n may fit into t and t is not unsigned,
	2 if n may fit into t and t is unsigned,
	3 if n definitely does not fit into t and t is not unsigned,
	4 if n definitely does not fit into t and t is unsigned,
	5 if n definitely does not fit into any type and t is not unsigned,
	6 if n definitely does not fit into any type and t is unsigned.
*/

int check_nat_range
    PROTO_N ( ( t, n ) )
    PROTO_T ( TYPE t X NAT n )
{
    int eq = 1 ;
    int neg = 0 ;
    unsigned msz ;
    unsigned bits ;
    BASE_TYPE sign ;

    /* Find type information */
    unsigned sz = find_type_size ( t, &msz, &sign ) ;
    int u = ( sign == btype_unsigned ? 1 : 0 ) ;

    /* Deal with complex constants */
    unsigned tag = TAG_nat ( n ) ;
    if ( tag == nat_neg_tag ) {
	n = DEREF_nat ( nat_neg_arg ( n ) ) ;
	tag = TAG_nat ( n ) ;
	neg = 1 ;
    }
    if ( tag == nat_calc_tag || tag == nat_token_tag ) {
	return ( 1 + u ) ;
    }

    /* Find the number of bits in the representation of n */
    bits = get_nat_bits ( n, &eq ) ;
    if ( bits > basetype_info [ ntype_ellipsis ].max_bits ) {
	return ( 5 + u ) ;
    }

    /* Check the type range */
    if ( sign == btype_unsigned ) {
	/* Unsigned types (eg [0-255]) */
	if ( neg ) return ( 4 ) ;
	if ( bits <= sz ) return ( 0 ) ;
	if ( bits > msz ) return ( 4 ) ;
    } else if ( sign == btype_signed ) {
	/* Symmetric signed types (eg [-127,127]) */
	if ( bits < sz ) return ( 0 ) ;
	if ( bits >= msz ) return ( 3 ) ;
    } else if ( sign == ( btype_signed | btype_long ) ) {
	/* Asymmetric signed types (eg [-128,127]) */
	if ( bits < sz ) return ( 0 ) ;
	if ( bits == sz && neg && eq ) return ( 0 ) ;
	if ( bits >= msz ) return ( 3 ) ;
    } else {
	/* Unspecified types */
	if ( neg ) return ( 3 ) ;
	if ( bits < sz ) return ( 0 ) ;
	if ( bits >= msz ) return ( 3 ) ;
    }
    return ( 1 + u ) ;
}


/*
    CHECK A TYPE SIZE

    This routine checks whether the integer literal n exceeds the number
    of bits in the integral, enumeration or bitfield type t.  It is used,
    for example, in checking for overlarge shifts and bitfield sizes.
    It returns -1 if n is less than the minimum number of bits, 0 if it
    is equal, and 1 otherwise.
*/

int check_type_size
    PROTO_N ( ( t, n ) )
    PROTO_T ( TYPE t X NAT n )
{
    unsigned sz ;
    unsigned msz ;
    BASE_TYPE sign ;
    unsigned long st, sn ;
    switch ( TAG_nat ( n ) ) {
	case nat_neg_tag :
	case nat_calc_tag :
	case nat_token_tag : {
	    /* Negative and calculated values are alright */
	    return ( -1 ) ;
	}
    }
    sn = get_nat_value ( n ) ;
    if ( sn == EXTENDED_MAX ) return ( 1 ) ;
    sz = find_type_size ( t, &msz, &sign ) ;
    UNUSED ( sign ) ;
    UNUSED ( msz ) ;
    st = EXTEND_VALUE ( sz ) ;
    if ( sn < st ) return ( -1 ) ;
    if ( sn == st ) return ( 0 ) ;
    return ( 1 ) ;
}


/*
    FIND THE MAXIMUM VALUE FOR A TYPE

    This routine returns the maximum value (or the minimum value if neg is
    true) which is guaranteed to fit into the type t.  The null constant
    is returned if the value can't be determined.  If t is the null type
    the maximum value which can fit into any type is returned.
*/

NAT max_type_value
    PROTO_N ( ( t, neg ) )
    PROTO_T ( TYPE t X int neg )
{
    NAT n ;
    unsigned sz ;
    unsigned msz ;
    int zero = 0 ;
    BASE_TYPE sign ;
    if ( !IS_NULL_type ( t ) ) {
	sz = find_type_size ( t, &msz, &sign ) ;
    } else {
	sz = basetype_info [ ntype_ellipsis ].max_bits ;
	sign = btype_unsigned ;
    }
    if ( !( sign & btype_signed ) ) {
	zero = neg ;
    }
    if ( !( sign & btype_unsigned ) ) {
	if ( sz == 0 ) zero = 1 ;
	sz-- ;
    }
    if ( zero ) {
	n = small_nat [0] ;
    } else {
	n = make_nat_value ( ( unsigned long ) sz ) ;
	n = binary_nat_op ( exp_lshift_tag, small_nat [1], n ) ;
	if ( !IS_NULL_nat ( n ) ) {
	    if ( !neg || !( sign & btype_long ) ) {
		n = binary_nat_op ( exp_minus_tag, n, small_nat [1] ) ;
	    }
	    if ( neg ) n = negate_nat ( n ) ;
	}
    }
    return ( n ) ;
}




/*
    CONSTRUCT A CONSTANT INTEGRAL EXPRESSION

    This routine constructs an integer literal expression of type t from
    the literal n, performing any appropriate bounds checks.  tag indicates
    the operation used to form this result.  The null expression is returned
    to indicate that n may not fit into t.
*/

EXP make_int_exp
    PROTO_N ( ( t, tag, n ) )
    PROTO_T ( TYPE t X unsigned tag X NAT n )
{
    EXP e ;
    int ch = check_nat_range ( t, n ) ;
    if ( ch == 0 ) {
	MAKE_exp_int_lit ( t, n, tag, e ) ;
    } else {
	e = NULL_exp ;
    }
    return ( e ) ;
}


/*
    CHECK ARRAY BOUNDS

    This routine checks an array index operation indicated by op (which
    can be '[]', '+' or '-') for the array type t and the constant integer
    index expression a.  Note that a must be less than the array bound for
    '[]', but may be equal to the bound for the other operations (this is
    the 'one past the end' rule).
*/

void check_bounds
    PROTO_N ( ( op, t, a ) )
    PROTO_T ( int op X TYPE t X EXP a )
{
    if ( IS_exp_int_lit ( a ) ) {
	int ok = 0 ;
	NAT n = DEREF_nat ( type_array_size ( t ) ) ;
	NAT m = DEREF_nat ( exp_int_lit_nat ( a ) ) ;

	/* Unbound arrays do not give an error */
	if ( IS_NULL_nat ( n ) ) return ;

	/* Calculated indexes are alright */
	if ( is_calc_nat ( m ) ) return ;

	/* Check the bounds */
	if ( op == lex_minus ) m = negate_nat ( m ) ;
	if ( !IS_nat_neg ( m ) ) {
	    if ( !is_calc_nat ( n ) ) {
		int c = compare_nat ( m, n ) ;
		if ( c < 0 ) ok = 1 ;
		if ( c == 0 && op != lex_array_Hop ) ok = 1 ;
	    }
	}

	/* Report the error */
	if ( !ok ) report ( crt_loc, ERR_expr_add_array ( m, t, op ) ) ;
    }
    return ;
}


/*
    EVALUATE A CONSTANT CAST OPERATION

    This routine is used to cast the integer constant expression a to the
    integral, bitfield, or enumeration type t.  The argument cast indicated
    whether the cast used is implicit or explicit (see cast.h).  Any errors
    arising are added to err.
*/

EXP make_cast_nat
    PROTO_N ( ( t, a, err, cast ) )
    PROTO_T ( TYPE t X EXP a X ERROR *err X unsigned cast )
{
    EXP e ;
    int ch ;
    unsigned etag = exp_cast_tag ;
    NAT n = DEREF_nat ( exp_int_lit_nat ( a ) ) ;
    if ( cast == CAST_IMPLICIT ) {
	etag = DEREF_unsigned ( exp_int_lit_etag ( a ) ) ;
    }
    ch = check_nat_range ( t, n ) ;
    if ( ch != 0 ) {
	/* n may not fit into t */
	a = calc_exp_value ( a ) ;
	MAKE_exp_cast ( t, CONV_INT_INT, a, e ) ;
	MAKE_nat_calc ( e, n ) ;
    }
    MAKE_exp_int_lit ( t, n, etag, e ) ;
    UNUSED ( err ) ;
    return ( e ) ;
}


/*
    EVALUATE A CONSTANT UNARY OPERATION

    This routine is used to evaluate the unary operation indicated by tag
    on the integer constant expression a.  Any necessary operand conversions
    and arithmetic type conversions have already been performed on a.  The
    permitted operations are '!', '-' and '~'.
*/

EXP make_unary_nat
    PROTO_N ( ( tag, a ) )
    PROTO_T ( unsigned tag X EXP a )
{
    EXP e ;
    TYPE t = DEREF_type ( exp_type ( a ) ) ;
    NAT n = DEREF_nat ( exp_int_lit_nat ( a ) ) ;

    /* Can only evaluate result if n is not calculated */
    if ( !is_calc_nat ( n ) ) {
	switch ( tag ) {
	    case exp_not_tag : {
		/* Deal with '!a' */
		unsigned p = test_bool_exp ( a ) ;
		if ( p == BOOL_UNKNOWN ) break ;
		e = make_bool_exp ( BOOL_NEGATE ( p ), tag ) ;
		return ( e ) ;
	    }
	    case exp_abs_tag : {
		/* Deal with 'abs ( a )' */
		int c = compare_nat ( n, small_nat [0] ) ;
		if ( c == 0 || c == 1 ) return ( a ) ;
		if ( c == -1 ) goto negate_lab ;
		break ;
	    }
	    case exp_negate_tag :
	    negate_lab : {
		/* Deal with '-a' */
		n = negate_nat ( n ) ;
		e = make_int_exp ( t, tag, n ) ;
		if ( !IS_NULL_exp ( e ) ) return ( e ) ;
		break ;
	    }
	    case exp_compl_tag : {
		/* Deal with '~a' */
		/* NOT YET IMPLEMENTED */
		break ;
	    }
	}
    }

    /* Calculated case */
    a = calc_exp_value ( a ) ;
    MAKE_exp_negate_etc ( tag, t, a, e ) ;
    MAKE_nat_calc ( e, n ) ;
    MAKE_exp_int_lit ( t, n, tag, e ) ;
    return ( e ) ;
}


/*
    CHECK A CHARACTER LITERAL CONSTANT

    This routine checks whether the integer constant expression a represents
    one of the decimal character literals, '0', '1', ..., '9'.  If so it
    returns the corresponding value in the range [0,9].  Otherwise it
    returns -1.
*/

static int eval_char_nat
    PROTO_N ( ( a, k ) )
    PROTO_T ( EXP a X unsigned *k )
{
    unsigned tag = TAG_exp ( a ) ;
    if ( tag == exp_int_lit_tag ) {
	NAT n = DEREF_nat ( exp_int_lit_nat ( a ) ) ;
	if ( IS_nat_calc ( n ) ) {
	    a = DEREF_exp ( nat_calc_value ( n ) ) ;
	    tag = TAG_exp ( a ) ;
	}
    }
    if ( tag == exp_char_lit_tag ) {
	int d = DEREF_int ( exp_char_lit_digit ( a ) ) ;
	STRING str = DEREF_str ( exp_char_lit_str ( a ) ) ;
	*k = DEREF_unsigned ( str_simple_kind ( str ) ) ;
	return ( d ) ;
    }
    if ( tag == exp_cast_tag ) {
	a = DEREF_exp ( exp_cast_arg ( a ) ) ;
	return ( eval_char_nat ( a, k ) ) ;
    }
    return ( -1 ) ;
}


/*
    ADD A VALUE TO A CHARACTER LITERAL CONSTANT

    This routine adds or subtracts (depending on the value of tag) the
    value n to the decimal character literal d, casting the result to
    type t.  The null expression is returned if the result is not a
    character literal.  For example, this routine is used to evaluate
    '4' + 3 as '7' regardless of the underlying character set.  This
    wouldn't be terribly important, but certain validation set suites
    use 6 + '0' - '6' as a null pointer constant!
*/

static EXP make_char_nat
    PROTO_N ( ( t, tag, d, kind, n ) )
    PROTO_T ( TYPE t X unsigned tag X int d X unsigned kind X NAT n )
{
    int neg = ( tag == exp_minus_tag ? 1 : 0 ) ;
    if ( IS_nat_neg ( n ) ) {
	/* Negate if necessary */
	n = DEREF_nat ( nat_neg_arg ( n ) ) ;
	neg = !neg ;
    }
    if ( IS_nat_small ( n ) ) {
	unsigned v = DEREF_unsigned ( nat_small_value ( n ) ) ;
	if ( v < 10 ) {
	    int m = ( int ) v ;
	    if ( neg ) m = -m ;
	    d += m ;
	    if ( d >= 0 && d < 10 ) {
		/* Construct the result */
		EXP e ;
		STRING str ;
		character s [2] ;
		ERROR err = NULL_err ;
		s [0] = ( character ) ( d + char_zero ) ;
		s [1] = 0 ;
		MAKE_str_simple ( 1, xustrcpy ( s ), kind, str ) ;
		e = make_string_exp ( str ) ;
		e = make_cast_nat ( t, e, &err, CAST_STATIC ) ;
		if ( !IS_NULL_err ( err ) ) report ( crt_loc, err ) ;
		return ( e ) ;
	    }
	}
    }
    return ( NULL_exp ) ;
}


/*
    EVALUATE A CONSTANT BINARY OPERATION

    This routine is used to evaluate the binary operation indicated by tag
    on the integer constant expressions a and b.  Any necessary operand
    conversions and arithmetic type conversions have already been performed
    on a and b.  The permitted operations are '+', '-', '*', '/', '%', '<<',
    '>>', '&', '|', '^', '&&' and '||'.
*/

EXP make_binary_nat
    PROTO_N ( ( tag, a, b ) )
    PROTO_T ( unsigned tag X EXP a X EXP b )
{
    EXP e ;
    int calc = 1 ;
    NAT res = NULL_nat ;
    TYPE t = DEREF_type ( exp_type ( a ) ) ;
    NAT n = DEREF_nat ( exp_int_lit_nat ( a ) ) ;
    NAT m = DEREF_nat ( exp_int_lit_nat ( b ) ) ;

    /* Examine simple cases */
    switch ( tag ) {
	case exp_plus_tag : {
	    /* Deal with 'a + b' */
	    if ( is_zero_nat ( n ) ) {
		res = m ;
	    } else if ( is_zero_nat ( m ) ) {
		res = n ;
	    }
	    break ;
	}
	case exp_minus_tag : {
	    /* Deal with 'a - b' */
	    int c = compare_nat ( n, m ) ;
	    if ( c == 0 && !overflow_exp ( a ) ) {
		res = small_nat [0] ;
	    } else if ( is_zero_nat ( n ) ) {
		e = make_unary_nat ( exp_negate_tag, b ) ;
		return ( e ) ;
	    } else if ( is_zero_nat ( m ) ) {
		res = n ;
	    }
	    break ;
	}
	case exp_mult_tag : {
	    /* Deal with 'a * b' */
	    if ( is_zero_nat ( n ) && !overflow_exp ( b ) ) {
		res = n ;
	    } else if ( is_zero_nat ( m ) && !overflow_exp ( a ) ) {
		res = m ;
	    }
	    if ( EQ_nat ( n, small_nat [1] ) ) {
		res = m ;
	    } else if ( EQ_nat ( m, small_nat [1] ) ) {
		res = n ;
	    }
	    break ;
	}
	case exp_max_tag : {
	    /* Deal with 'max ( a, b )' */
	    int c = compare_nat ( n, m ) ;
	    if ( ( c == 0 || c == 1 ) && !overflow_exp ( b ) ) {
		res = n ;
	    } else if ( c == -1 && !overflow_exp ( a ) ) {
		res = m ;
	    }
	    calc = 0 ;
	    break ;
	}
	case exp_min_tag : {
	    /* Deal with 'min ( a, b )' */
	    int c = compare_nat ( n, m ) ;
	    if ( ( c == 0 || c == 1 ) && !overflow_exp ( a ) ) {
		res = m ;
	    } else if ( c == -1 && !overflow_exp ( b ) ) {
		res = n ;
	    }
	    calc = 0 ;
	    break ;
	}
	case exp_log_and_tag : {
	    /* Deal with 'a && b' */
	    unsigned p = test_bool_exp ( a ) ;
	    unsigned q = test_bool_exp ( b ) ;
	    if ( p == BOOL_TRUE && q == BOOL_TRUE ) {
		/* EMPTY */
	    } else if ( p == BOOL_FALSE && !overflow_exp ( b ) ) {
		/* EMPTY */
	    } else if ( q == BOOL_FALSE && !overflow_exp ( a ) ) {
		p = BOOL_FALSE ;
	    } else {
		calc = 0 ;
		break ;
	    }
	    e = make_bool_exp ( p, tag ) ;
	    return ( e ) ;
	}
	case exp_log_or_tag : {
	    /* Deal with 'a || b' */
	    unsigned p = test_bool_exp ( a ) ;
	    unsigned q = test_bool_exp ( b ) ;
	    if ( p == BOOL_FALSE && q == BOOL_FALSE ) {
		/* EMPTY */
	    } else if ( p == BOOL_TRUE && !overflow_exp ( b ) ) {
		/* EMPTY */
	    } else if ( q == BOOL_TRUE && !overflow_exp ( a ) ) {
		p = BOOL_TRUE ;
	    } else {
		calc = 0 ;
		break ;
	    }
	    e = make_bool_exp ( p, tag ) ;
	    return ( e ) ;
	}
    }

    /* Return result if known (either n, m or 0) */
    if ( !IS_NULL_nat ( res ) ) {
	MAKE_exp_int_lit ( t, res, tag, e ) ;
	return ( e ) ;
    }

    /* Can only evaluate result if n and m are not calculated */
    if ( calc && !is_calc_nat ( n ) && !is_calc_nat ( m ) ) {
	res = binary_nat_op ( tag, n, m ) ;
	if ( !IS_NULL_nat ( res ) ) {
	    e = make_int_exp ( t, tag, res ) ;
	    if ( !IS_NULL_exp ( e ) ) return ( e ) ;
	}
    }

    /* Check for digit characters */
    if ( tag == exp_plus_tag || tag == exp_minus_tag ) {
	unsigned ka, kb ;
	int da = eval_char_nat ( a, &ka ) ;
	int db = eval_char_nat ( b, &kb ) ;
	if ( da >= 0 ) {
	    if ( db >= 0 && tag == exp_minus_tag ) {
		/* Difference of two digits */
		res = make_small_nat ( da - db ) ;
		e = make_int_exp ( t, tag, res ) ;
		if ( !IS_NULL_exp ( e ) ) return ( e ) ;
	    } else {
		/* Digit plus or minus value */
		e = make_char_nat ( t, tag, da, ka, m ) ;
		if ( !IS_NULL_exp ( e ) ) return ( e ) ;
	    }
	} else if ( db >= 0 && tag == exp_plus_tag ) {
	    /* Digit plus value */
	    e = make_char_nat ( t, tag, db, kb, n ) ;
	    if ( !IS_NULL_exp ( e ) ) return ( e ) ;
	}
    }

    /* Calculated case */
    a = calc_exp_value ( a ) ;
    b = calc_exp_value ( b ) ;
    MAKE_exp_plus_etc ( tag, t, a, b, e ) ;
    MAKE_nat_calc ( e, res ) ;
    MAKE_exp_int_lit ( t, res, tag, e ) ;
    return ( e ) ;
}


/*
    EVALUATE A CONSTANT TEST OPERATION

    This routine is used to convert the integer constant expression a to
    a boolean.
*/

EXP make_test_nat
    PROTO_N ( ( a ) )
    PROTO_T ( EXP a )
{
    EXP e ;
    NAT n = DEREF_nat ( exp_int_lit_nat ( a ) ) ;
    if ( !is_calc_nat ( n ) ) {
	/* Zero is false, non-zero is true */
	unsigned tag = DEREF_unsigned ( exp_int_lit_etag ( a ) ) ;
	unsigned b = BOOL_NEGATE ( is_zero_nat ( n ) ) ;
	e = make_bool_exp ( b, tag ) ;
    } else {
	/* Calculated case */
	TYPE t = DEREF_type ( exp_type ( a ) ) ;
	if ( check_int_type ( t, btype_bool ) ) {
	    e = a ;
	} else {
	    a = calc_exp_value ( a ) ;
	    MAKE_exp_test ( type_bool, ntest_not_eq, a, e ) ;
	    MAKE_nat_calc ( e, n ) ;
	    MAKE_exp_int_lit ( type_bool, n, exp_test_tag, e ) ;
	}
    }
    return ( e ) ;
}


/*
    EVALUATE A CONSTANT COMPARISON OPERATION

    This routine is used to evaluate the comparison operation indicated by
    op on the integer constant expressions a and b.  Any necessary operand
    conversions and arithmetic type conversions have already been performed
    on a and b.
*/

EXP make_compare_nat
    PROTO_N ( ( op, a, b ) )
    PROTO_T ( NTEST op X EXP a X EXP b )
{
    EXP e ;
    NAT n = DEREF_nat ( exp_int_lit_nat ( a ) ) ;
    NAT m = DEREF_nat ( exp_int_lit_nat ( b ) ) ;
    int c = compare_nat ( n, m ) ;
    if ( c == 0 ) {
	/* n and m are definitely equal */
	if ( !overflow_exp ( a ) ) {
	    unsigned cond = BOOL_FALSE ;
	    switch ( op ) {
		case ntest_eq :
		case ntest_less_eq :
		case ntest_greater_eq : {
		    cond = BOOL_TRUE ;
		    break ;
		}
	    }
	    e = make_bool_exp ( cond, exp_compare_tag ) ;
	    return ( e ) ;
	}
    } else if ( c == 1 ) {
	/* n is definitely greater than m */
	if ( !overflow_exp ( a ) && !overflow_exp ( b ) ) {
	    unsigned cond = BOOL_FALSE ;
	    switch ( op ) {
		case ntest_not_eq :
		case ntest_greater :
		case ntest_greater_eq : {
		    cond = BOOL_TRUE ;
		    break ;
		}
	    }
	    e = make_bool_exp ( cond, exp_compare_tag ) ;
	    return ( e ) ;
	}
    } else if ( c == -1 ) {
	/* n is definitely less than m */
	if ( !overflow_exp ( a ) && !overflow_exp ( b ) ) {
	    unsigned cond = BOOL_FALSE ;
	    switch ( op ) {
		case ntest_not_eq :
		case ntest_less :
		case ntest_less_eq : {
		    cond = BOOL_TRUE ;
		    break ;
		}
	    }
	    e = make_bool_exp ( cond, exp_compare_tag ) ;
	    return ( e ) ;
	}
    }

    /* Calculated values require further calculation */
    a = calc_exp_value ( a ) ;
    b = calc_exp_value ( b ) ;
    MAKE_exp_compare ( type_bool, op, a, b, e ) ;
    MAKE_nat_calc ( e, n ) ;
    MAKE_exp_int_lit ( type_bool, n, exp_compare_tag, e ) ;
    return ( e ) ;
}


/*
    EVALUATE A CONSTANT CONDITIONAL OPERATION

    This routine is used to evaluate the conditional operation 'a ? b : c'
    when a, b and c are all integer constant expressions.  Any necessary
    operand conversions and arithmetic type conversions have already been
    performed on a, b and c.
*/

EXP make_cond_nat
    PROTO_N ( ( a, b, c ) )
    PROTO_T ( EXP a X EXP b X EXP c )
{
    EXP e ;
    TYPE t = DEREF_type ( exp_type ( b ) ) ;
    NAT n = DEREF_nat ( exp_int_lit_nat ( b ) ) ;
    NAT m = DEREF_nat ( exp_int_lit_nat ( c ) ) ;
    unsigned p = test_bool_exp ( a ) ;
    if ( p == BOOL_TRUE && !overflow_exp ( c ) ) {
	/* EMPTY */
    } else if ( p == BOOL_FALSE && !overflow_exp ( b ) ) {
	n = m ;
    } else {
	/* Calculated case */
	b = calc_exp_value ( b ) ;
	c = calc_exp_value ( c ) ;
	MAKE_exp_if_stmt ( t, a, b, c, NULL_id, e ) ;
	MAKE_nat_calc ( e, n ) ;
    }
    MAKE_exp_int_lit ( t, n, exp_if_stmt_tag, e ) ;
    return ( e ) ;
}


/*
    DOES ONE EXPRESSION DIVIDE ANOTHER?

    This routine returns true if a and b are both integer constant
    expressions and b divides a.
*/

int divides_nat
    PROTO_N ( ( a, b ) )
    PROTO_T ( EXP a X EXP b )
{
    if ( IS_exp_int_lit ( a ) && IS_exp_int_lit ( b ) ) {
	unsigned long vn, vm ;
	NAT n = DEREF_nat ( exp_int_lit_nat ( a ) ) ;
	NAT m = DEREF_nat ( exp_int_lit_nat ( b ) ) ;
	if ( IS_nat_neg ( n ) ) n = DEREF_nat ( nat_neg_arg ( n ) ) ;
	if ( IS_nat_neg ( m ) ) m = DEREF_nat ( nat_neg_arg ( m ) ) ;
	vn = get_nat_value ( n ) ;
	vm = get_nat_value ( m ) ;
	if ( vm == 0 ) return ( 1 ) ;
	if ( vn == EXTENDED_MAX || vm == EXTENDED_MAX ) return ( 0 ) ;
	if ( ( vn % vm ) == 0 ) return ( 1 ) ;
    }
    return ( 0 ) ;
}


/*
    EVALUATE A CONSTANT CONDITION

    This routine evaluates the boolean expression e, returning BOOL_FALSE,
    BOOL_TRUE or BOOL_UNKNOWN depending on whether it is always false,
    always true, or constant, but indeterminant.  BOOL_INVALID is returned
    for non-constant expressions.
*/

unsigned eval_const_cond
    PROTO_N ( ( e ) )
    PROTO_T ( EXP e )
{
    if ( !IS_NULL_exp ( e ) ) {
	switch ( TAG_exp ( e ) ) {
	    case exp_int_lit_tag : {
		/* Boolean constants */
		unsigned b = test_bool_exp ( e ) ;
		return ( b ) ;
	    }
	    case exp_not_tag : {
		/* Logical negation */
		EXP a = DEREF_exp ( exp_not_arg ( e ) ) ;
		unsigned b = eval_const_cond ( a ) ;
		if ( b == BOOL_FALSE ) return ( BOOL_TRUE ) ;
		if ( b == BOOL_TRUE ) return ( BOOL_FALSE ) ;
		return ( b ) ;
	    }
	    case exp_log_and_tag : {
		/* Logical and */
		EXP a1 = DEREF_exp ( exp_log_and_arg1 ( e ) ) ;
		EXP a2 = DEREF_exp ( exp_log_and_arg2 ( e ) ) ;
		unsigned b1 = eval_const_cond ( a1 ) ;
		unsigned b2 = eval_const_cond ( a2 ) ;
		if ( b1 == BOOL_FALSE || b2 == BOOL_FALSE ) {
		    return ( BOOL_FALSE ) ;
		}
		if ( b1 == BOOL_TRUE && b2 == BOOL_TRUE ) {
		    return ( BOOL_TRUE ) ;
		}
		if ( b1 == BOOL_INVALID ) return ( BOOL_INVALID ) ;
		if ( b2 == BOOL_INVALID ) return ( BOOL_INVALID ) ;
		return ( BOOL_UNKNOWN ) ;
	    }
	    case exp_log_or_tag : {
		/* Logical or */
		EXP a1 = DEREF_exp ( exp_log_or_arg1 ( e ) ) ;
		EXP a2 = DEREF_exp ( exp_log_or_arg2 ( e ) ) ;
		unsigned b1 = eval_const_cond ( a1 ) ;
		unsigned b2 = eval_const_cond ( a2 ) ;
		if ( b1 == BOOL_TRUE || b2 == BOOL_TRUE ) {
		    return ( BOOL_TRUE ) ;
		}
		if ( b1 == BOOL_FALSE && b2 == BOOL_FALSE ) {
		    return ( BOOL_FALSE ) ;
		}
		if ( b1 == BOOL_INVALID ) return ( BOOL_INVALID ) ;
		if ( b2 == BOOL_INVALID ) return ( BOOL_INVALID ) ;
		return ( BOOL_UNKNOWN ) ;
	    }
	    case exp_test_tag : {
		/* Test against zero */
		EXP a = DEREF_exp ( exp_test_arg ( e ) ) ;
		NTEST op = DEREF_ntest ( exp_test_tst ( e ) ) ;
		if ( IS_exp_null ( a ) ) {
		    /* Null pointers */
		    if ( op == ntest_eq ) return ( BOOL_TRUE ) ;
		    if ( op == ntest_not_eq ) return ( BOOL_FALSE ) ;
		}
		break ;
	    }
	    case exp_location_tag : {
		/* Conditions can contain locations */
		EXP a = DEREF_exp ( exp_location_arg ( e ) ) ;
		return ( eval_const_cond ( a ) ) ;
	    }
	}
	if ( is_const_exp ( e, -1 ) ) return ( BOOL_UNKNOWN ) ;
    }
    return ( BOOL_INVALID ) ;
}


/*
    IS AN INTEGER CONSTANT EXPRESSION ZERO?

    This routine checks whether the expression a is a zero integer constant.
    It is used to identify circumstances when zero is actually the null
    pointer etc.
*/

int is_zero_exp
    PROTO_N ( ( a ) )
    PROTO_T ( EXP a )
{
    if ( !IS_NULL_exp ( a ) && IS_exp_int_lit ( a ) ) {
	NAT n = DEREF_nat ( exp_int_lit_nat ( a ) ) ;
	return ( is_zero_nat ( n ) ) ;
    }
    return ( 0 ) ;
}


/*
    IS AN INTEGER CONSTANT A LITERAL?

    This routine checks whether the integer constant expression a is an
    integer literal or is the result of a constant evaluation.  This
    information is recorded in the etag field of the expression.  It
    returns 2 if the literal was precisely '0'.
*/

int is_literal
    PROTO_N ( ( a ) )
    PROTO_T ( EXP a )
{
    if ( IS_exp_int_lit ( a ) ) {
	unsigned etag = DEREF_unsigned ( exp_int_lit_etag ( a ) ) ;
	if ( etag == exp_int_lit_tag ) return ( 1 ) ;
	if ( etag == exp_null_tag ) return ( 2 ) ;
	if ( etag == exp_identifier_tag ) return ( 1 ) ;
    }
    return ( 0 ) ;
}


/*
    FIND A SMALL FLOATING POINT LITERAL

    This routine returns the nth literal associated with the floating point
    type t.  The null literal is returned if n is too large.
*/

FLOAT get_float
    PROTO_N ( ( t, n ) )
    PROTO_T ( TYPE t X int n )
{
    FLOAT_TYPE ft = DEREF_ftype ( type_floating_rep ( t ) ) ;
    LIST ( FLOAT ) fp = DEREF_list ( ftype_small ( ft ) ) ;
    while ( !IS_NULL_list ( fp ) ) {
	if ( n == 0 ) {
	    FLOAT flt = DEREF_flt ( HEAD_list ( fp ) ) ;
	    return ( flt ) ;
	}
	n-- ;
	fp = TAIL_list ( fp ) ;
    }
    return ( NULL_flt ) ;
}


/*
    INITIALISE A FLOATING POINT TYPE

    This routine initialises the floating point type ft by creating its
    list of small literal values.
*/

void init_float
    PROTO_N ( ( ft ) )
    PROTO_T ( FLOAT_TYPE ft )
{
    int n ;
    NAT z = small_nat [0] ;
    string fp = small_number [0] ;
    LIST ( FLOAT ) p = NULL_list ( FLOAT ) ;
    for ( n = SMALL_FLT_SIZE - 1 ; n >= 0 ; n-- ) {
	FLOAT f ;
	string ip = small_number [n] ;
	MAKE_flt_simple ( ip, fp, z, f ) ;
	CONS_flt ( f, p, p ) ;
    }
    COPY_list ( ftype_small ( ft ), p ) ;
    return ;
}


/*
    INITIALISE CONSTANT EVALUATION ROUTINES

    This routine initialises the small_nat array and the buffers used in
    the constant evaluation routines.
*/

void init_constant
    PROTO_Z ()
{
    int n = 0 ;
    while ( n < SMALL_NAT_ALLOC ) {
	IGNORE make_small_nat ( n ) ;
	IGNORE make_small_nat ( -n ) ;
	n++ ;
    }
    while ( n < SMALL_NAT_SIZE ) {
	small_nat [n] = NULL_nat ;
	small_neg_nat [n] = NULL_nat ;
	n++ ;
    }
    small_neg_nat [0] = small_nat [0] ;
    CONS_unsigned ( 0, NULL_list ( unsigned ), small_nat_1 ) ;
    CONS_unsigned ( 0, NULL_list ( unsigned ), small_nat_2 ) ;
    small_number [0] = ustrlit ( "0" ) ;
    small_number [1] = ustrlit ( "1" ) ;
    return ;
}
