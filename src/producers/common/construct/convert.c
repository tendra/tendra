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
#include "ctype_ops.h"
#include "etype_ops.h"
#include "exp_ops.h"
#include "ftype_ops.h"
#include "graph_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "itype_ops.h"
#include "nat_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "option.h"
#include "basetype.h"
#include "cast.h"
#include "check.h"
#include "chktype.h"
#include "constant.h"
#include "construct.h"
#include "convert.h"
#include "derive.h"
#include "expression.h"
#include "function.h"
#include "identifier.h"
#include "initialise.h"
#include "instance.h"
#include "inttype.h"
#include "literal.h"
#include "member.h"
#include "namespace.h"
#include "overload.h"
#include "predict.h"
#include "quality.h"
#include "syntax.h"
#include "template.h"
#include "tokdef.h"
#include "token.h"


/*
    FIND THE PROMOTION OF A TYPE

    This routine finds the promoted type for the type t.  For integral
    types the promoted type is calculated and stored when the type is
    first constructed.  Enumeration types and bitfield types are promoted
    according to their underlying types.  Other types (including floating
    point types) are their own promotions.
*/

TYPE promote_type
    PROTO_N ( ( t ) )
    PROTO_T ( TYPE t )
{
    switch ( TAG_type ( t ) ) {
	case type_integer_tag : {
	    /* Retrieve the promotion of an integral type */
	    INT_TYPE it = DEREF_itype ( type_integer_rep ( t ) ) ;
	    t = DEREF_type ( itype_prom ( it ) ) ;
	    break ;
	}
	case type_enumerate_tag : {
	    /* Find the underlying type of an enumeration */
	    ENUM_TYPE et = DEREF_etype ( type_enumerate_defn ( t ) ) ;
	    t = DEREF_type ( etype_rep ( et ) ) ;
	    t = promote_type ( t ) ;
	    break ;
	}
	case type_bitfield_tag : {
	    /* Retrieve the promotion of a bitfield type */
	    INT_TYPE it = DEREF_itype ( type_bitfield_defn ( t ) ) ;
	    t = DEREF_type ( itype_prom ( it ) ) ;
	    break ;
	}
    }
    return ( t ) ;
}


/*
    FIND THE ARGUMENT PROMOTION OF A TYPE

    This routine finds the argument promotion type for the type t.  This
    is identical to the normal arithmetic promotion type for integral types,
    but differs for floating point types (float promotes to double etc.).
    Any errors are added to the end of err.
*/

TYPE arg_promote_type
    PROTO_N ( ( t, err ) )
    PROTO_T ( TYPE t X ERROR *err )
{
    switch ( TAG_type ( t ) ) {
	case type_integer_tag :
	case type_enumerate_tag :
	case type_bitfield_tag : {
	    /* Promote integral types */
	    t = promote_type ( t ) ;
	    break ;
	}
	case type_floating_tag : {
	    /* Retrieve the promotion of a floating point type */
	    FLOAT_TYPE ft = DEREF_ftype ( type_floating_rep ( t ) ) ;
	    t = DEREF_type ( ftype_arg_prom ( ft ) ) ;
	    break ;
	}
	case type_top_tag :
	case type_bottom_tag : {
	    /* Can't have 'void' arguments */
	    add_error ( err, ERR_basic_fund_void_exp ( t ) ) ;
	    break ;
	}
	case type_func_tag : {
	    /* Apply function-to-pointer conversion */
	    MAKE_type_ptr ( cv_none, t, t ) ;
	    break ;
	}
	case type_array_tag : {
	    /* Apply array-to-pointer conversion */
	    TYPE s = DEREF_type ( type_array_sub ( t ) ) ;
	    MAKE_type_ptr ( cv_none, s, t ) ;
	    break ;
	}
	case type_compound_tag : {
	    /* Types with constructors are suspicious */
	    if ( pass_complex_type ( t ) ) {
		add_error ( err, ERR_expr_call_struct ( t ) ) ;
	    }
	    break ;
	}
    }
    return ( t ) ;
}


/*
    IS A TYPE EQUAL TO ITS ARGUMENT PROMOTION TYPE?

    This routine checks whether the integral or floating point type t is
    equal to its argument promotion type.
*/

int is_arg_promote
    PROTO_N ( ( t ) )
    PROTO_T ( TYPE t )
{
    int eq = 1 ;
    if ( !IS_NULL_type ( t ) ) {
	t = expand_type ( t, 1 ) ;
	switch ( TAG_type ( t ) ) {
	    case type_integer_tag :
	    case type_floating_tag : {
		TYPE s = arg_promote_type ( t, KILL_err ) ;
		if ( !EQ_type ( s, t ) ) {
		    int ft = force_tokdef ;
		    force_tokdef = 0 ;
		    eq = eq_type_unqual ( s, t ) ;
		    force_tokdef = ft ;
		}
		break ;
	    }
	}
    }
    return ( eq ) ;
}


/*
    FIND THE TYPE WHICH PROMOTES TO A GIVEN TYPE

    This routine is a partial inverse to arg_promote_type which finds a
    type whose promotion is t.
*/

TYPE unpromote_type
    PROTO_N ( ( t ) )
    PROTO_T ( TYPE t )
{
    if ( !IS_NULL_type ( t ) ) {
	switch ( TAG_type ( t ) ) {
	    case type_integer_tag : {
		INT_TYPE it = DEREF_itype ( type_integer_rep ( t ) ) ;
		INT_TYPE is = DEREF_itype ( type_integer_sem ( t ) ) ;
		if ( !EQ_itype ( is, it ) ) t = make_itype ( is, is ) ;
		break ;
	    }
	    case type_floating_tag : {
		FLOAT_TYPE ft = DEREF_ftype ( type_floating_rep ( t ) ) ;
		FLOAT_TYPE fs = DEREF_ftype ( type_floating_sem ( t ) ) ;
		if ( !EQ_ftype ( fs, ft ) ) t = make_ftype ( fs, fs ) ;
		break ;
	    }
	}
    }
    return ( t ) ;
}


/*
    FIND THE TYPE FOR AN ARITHMETIC OPERATION

    This routine performs finds the result type for an arithmetic operation
    involving operands of types t and s.  These will always be arithmetic
    types.  The operands a and b are passed in order to help determine the
    semantic type of the result.
*/

TYPE arith_type
    PROTO_N ( ( t, s, a, b ) )
    PROTO_T ( TYPE t X TYPE s X EXP a X EXP b )
{
    TYPE r ;
    if ( EQ_type ( t, s ) ) {
	/* Equal types, promote the result */
	r = promote_type ( t ) ;
    } else {
	unsigned nt = TAG_type ( t ) ;
	unsigned ns = TAG_type ( s ) ;
	if ( nt == type_floating_tag ) {
	    if ( ns == type_floating_tag ) {
		/* Two floating point types */
		r = arith_ftype ( t, s ) ;
	    } else {
		/* If there is one floating type, this is the result */
		r = t ;
	    }
	} else {
	    if ( ns == type_floating_tag ) {
		/* If there is one floating type, this is the result */
		r = s ;
	    } else {
		/* Two integer types, promote them both */
		TYPE pt = promote_type ( t ) ;
		TYPE ps = promote_type ( s ) ;
		if ( EQ_type ( pt, ps ) ) {
		    r = pt ;
		} else {
		    r = arith_itype ( pt, ps, a, b ) ;
		}
	    }
	}
    }
    return ( r ) ;
}


/*
    QUALIFIER DEPTH

    The value qualifier depth is set by check_qualifier to the depth of
    the deepest different cv-qualifier it encounters.  The easy cases
    are 0 (the types are identically qualified) and 1 (the conversion
    is of the form 'cv1 T *' to 'cv2 T *').  The value qualifier_diff
    gives the qualifiers added at this stage.
*/

int qualifier_depth = 0 ;
static CV_SPEC qualifier_diff = cv_none ;


/*
    CHECK QUALIFICATION CONVERSIONS

    This routine checks for qualification conversions from the pointer or
    pointer to member type s to the pointer or pointer to member type t.
    For the qualification conversion to be valid, the two types have to obey
    four rules.  They have to be similar (i.e. the same up to cv-qualifiers)
    - this is assumed to be true if safe is true.  Each target qualifier
    must be more const-qualified and more volatile-qualified than the
    corresponding source qualifier.  Finally if two qualifiers differ
    then all the previous target qualifiers must involve const.  The C
    rules are slightly different.  Only one level of pointers is
    considered and the types pointed to must be compatible.  Note that
    for pointer to member types it is not checked that the underlying
    classes are the same at the top level.  This is to allow base class
    pointer to member conversion to be checked elsewhere.
*/

unsigned check_qualifier
    PROTO_N ( ( t, s, safe ) )
    PROTO_T ( TYPE t X TYPE s X int safe )
{
    int j = 0 ;
    int all_const = 1 ;
    unsigned res = QUAL_EQUAL ;
    t = expand_type ( t, 1 ) ;
    s = expand_type ( s, 1 ) ;
    qualifier_depth = 0 ;
    qualifier_diff = cv_none ;
    while ( !EQ_type ( t, s ) ) {
        unsigned nt = TAG_type ( t ) ;
        unsigned ns = TAG_type ( s ) ;
	CV_SPEC qt = DEREF_cv ( type_qual ( t ) ) ;
	CV_SPEC qs = DEREF_cv ( type_qual ( s ) ) ;

	/* Check qualifiers */
	if ( j == 0 ) {
	    /* Don't bother with top level qualifiers */
	    /* EMPTY */
	} else {
	    if ( nt == type_array_tag ) qt = find_cv_qual ( t ) ;
	    if ( ns == type_array_tag ) qs = find_cv_qual ( s ) ;
	    qt &= cv_qual ;
	    qs &= cv_qual ;
	    if ( qt != qs ) {
		CV_SPEC qr = ( qs & ~qt ) ;
		if ( qr & cv_const ) res &= ~QUAL_CONST ;
		if ( qr & cv_volatile ) res &= ~QUAL_VOLATILE ;
		res &= ~QUAL_EXACT ;
		if ( !all_const ) {
		    /* For inequality should have all consts in t */
		    res &= ~QUAL_ALL_CONST ;
		}
		qualifier_depth = j ;
		qualifier_diff = ( qt & ~qs ) ;
	    }
	    if ( !( qt & cv_const ) ) all_const = 0 ;
	}

	/* Check next type */
	switch ( nt ) {

	    case type_ptr_tag :
	    case type_ref_tag : {
		/* Pointer types */
		if ( ns != nt ) goto error_lab ;
#if LANGUAGE_C
		if ( j > 0 ) goto error_lab ;
#endif
		t = DEREF_type ( type_ptr_etc_sub ( t ) ) ;
		s = DEREF_type ( type_ptr_etc_sub ( s ) ) ;
		break ;
	    }

#if LANGUAGE_CPP
	    case type_ptr_mem_tag : {
		/* Pointer to member types */
		CLASS_TYPE cs, ct ;
		if ( ns != nt ) goto error_lab ;
		ct = DEREF_ctype ( type_ptr_mem_of ( t ) ) ;
		cs = DEREF_ctype ( type_ptr_mem_of ( s ) ) ;
		if ( j == 0 ) {
		    /* Top level classes checked elsewhere */
		    /* EMPTY */
		} else if ( !eq_ctype ( ct, cs ) ) {
		    /* Must point to members of the same class */
		    if ( in_template_decl ) {
			/* Mark template parameter types */
			TYPE ft = DEREF_type ( ctype_form ( ct ) ) ;
			TYPE fs = DEREF_type ( ctype_form ( cs ) ) ;
			if ( is_templ_depend ( ft ) ) res |= QUAL_TEMPL ;
			if ( is_templ_depend ( fs ) ) res |= QUAL_TEMPL ;
		    }
		    res &= ~( QUAL_EXACT | QUAL_SIMILAR ) ;
		    return ( res ) ;
		}
		t = DEREF_type ( type_ptr_mem_sub ( t ) ) ;
		s = DEREF_type ( type_ptr_mem_sub ( s ) ) ;
		break ;
	    }
#endif

	    case type_func_tag : {
		/* Function types */
		int eq ;
		if ( ns != nt ) goto error_lab ;
		if ( safe ) {
		    eq = 3 ;
		} else {
		    eq = eq_func_type ( t, s, 1, 0 ) ;
		    if ( eq < 2 ) goto error_lab ;
		}
		if ( res == QUAL_EQUAL ) res |= QUAL_FUNC ;
		if ( eq != 3 ) {
		    /* Linkage specifiers don't match */
		    res &= ~( QUAL_EXACT | QUAL_SIMILAR ) ;
		}
		return ( res ) ;
	    }

	    case type_top_tag :
	    case type_bottom_tag :
	    case type_compound_tag : {
		/* Don't trust 'safe' in these cases */
		if ( ns == nt && eq_type_unqual ( t, s ) ) return ( res ) ;
		goto error_lab ;
	    }

	    default : {
		/* Check other types */
		if ( safe ) return ( res ) ;
		if ( ns == nt && eq_type_unqual ( t, s ) ) return ( res ) ;
		goto error_lab ;
	    }

	    error_lab : {
		/* Unequal types */
#if LANGUAGE_C
		TYPE r = type_composite ( t, s, 1, 0, KILL_err, 0 ) ;
		if ( !IS_NULL_type ( r ) ) {
		    if ( IS_type_func ( r ) ) {
			if ( res == QUAL_EQUAL ) res |= QUAL_FUNC ;
		    }
		    return ( res ) ;
		}
#endif
		if ( in_template_decl ) {
		    /* Mark template parameter types */
		    if ( is_templ_depend ( t ) ) res |= QUAL_TEMPL ;
		    if ( is_templ_depend ( s ) ) res |= QUAL_TEMPL ;
		}
		if ( ns == type_error_tag || nt == type_error_tag ) {
		    /* Mark error types */
		    res |= QUAL_TEMPL ;
		}
		res &= ~( QUAL_EXACT | QUAL_SIMILAR ) ;
		return ( res ) ;
	    }
	}
	j++ ;
    }
    return ( res ) ;
}


/*
    FIND THE TYPE FOR A POINTER OPERATION

    This routine finds the common type for a pointer operation involving
    the pointer types t and s (as used, for example, in the relational
    operators).  Pointer conversions and qualification conversions are
    applied (including base class conversions if base is true), but the
    result must be a qualified version of one of the arguments, so only
    depth 1 qualification conversions are applied.  If t and s cannot be
    brought to a common type then the suspect flag is set to 2 and
    qualified 'void *' is returned.  suspect is set to 1 if precisely
    one of the types is 'void *'.  The routine also operates on reference
    types except that it returns a null type in the 'void *' case.
*/

TYPE ptr_common_type
    PROTO_N ( ( t, s, base, suspect ) )
    PROTO_T ( TYPE t X TYPE s X int base X int *suspect )
{
    CV_SPEC qt, qs ;
    TYPE r = NULL_type ;
    unsigned tag = TAG_type ( t ) ;
    TYPE pt = DEREF_type ( type_ptr_etc_sub ( t ) ) ;
    TYPE ps = DEREF_type ( type_ptr_etc_sub ( s ) ) ;
    unsigned nt = TAG_type ( pt ) ;
    unsigned ns = TAG_type ( ps ) ;

    /* Find the common type */
    if ( nt == ns ) {
	if ( eq_type_unqual ( pt, ps ) ) {
	    /* Pointers to the same type */
	    r = pt ;
	} else if ( nt == type_compound_tag && base ) {
	    /* Check for base class conversions */
	    CLASS_TYPE ct = DEREF_ctype ( type_compound_defn ( pt ) ) ;
	    CLASS_TYPE cs = DEREF_ctype ( type_compound_defn ( ps ) ) ;
	    CLASS_TYPE cr = compare_base_class ( ct, cs, 1 ) ;
	    if ( EQ_ctype ( cr, ct ) ) {
		/* p is a base class of q */
		r = pt ;
	    } else if ( EQ_ctype ( cr, cs ) ) {
		/* q is a base class of p */
		r = ps ;
	    }
	}
    } else if ( nt == type_top_tag || nt == type_bottom_tag ) {
	/* One pointer is 'void *' */
	*suspect = 1 ;
	r = pt ;
    } else if ( ns == type_top_tag || ns == type_bottom_tag ) {
	/* One pointer is 'void *' */
	*suspect = 1 ;
	r = ps ;
    }
#if LANGUAGE_C
    if ( IS_NULL_type ( r ) ) {
	/* In C, compatible types are allowed */
	r = type_composite ( pt, ps, 1, 0, KILL_err, 1 ) ;
    }
#endif
    if ( IS_NULL_type ( r ) ) {
	/* Can't bring to common pointer type */
	if ( is_templ_type ( t ) || is_templ_type ( s ) ) {
	    *suspect = -1 ;
	} else {
	    *suspect = 2 ;
	}
	if ( tag == type_ref_tag ) {
	    /* There are no generic references */
	    return ( NULL_type ) ;
	}
	r = type_void ;
    }

    /* Qualify the common type appropriately */
    qt = find_cv_qual ( pt ) ;
    qs = find_cv_qual ( ps ) ;
    r = qualify_type ( r, ( qt | qs ), 0 ) ;

    /* Form the result type */
    if ( EQ_type ( r, pt ) ) return ( t ) ;
    if ( EQ_type ( r, ps ) ) return ( s ) ;
    MAKE_type_ptr_etc ( tag, cv_none, r, r ) ;
    return ( r ) ;
}


/*
    FIND THE TYPE FOR A POINTER MEMBER OPERATION

    This routine finds the common type for a pointer to member operation
    involving the pointer to member types t and s (as used, for example,
    in the equality operators).  If t and s cannot be brought to a common
    type then suspect is set to 2 and the error type is returned.  If
    the cv-qualifier of the common type is not equal to the cv-qualifier
    of either t or s then suspect is set to 1.
*/

TYPE ptr_mem_common_type
    PROTO_N ( ( t, s, suspect ) )
    PROTO_T ( TYPE t X TYPE s X int *suspect )
{
    /* Check for base class conversions */
    CLASS_TYPE ct = DEREF_ctype ( type_ptr_mem_of ( t ) ) ;
    CLASS_TYPE cs = DEREF_ctype ( type_ptr_mem_of ( s ) ) ;
    CLASS_TYPE cr = compare_base_class ( ct, cs, 1 ) ;
    if ( !IS_NULL_ctype ( cr ) ) {
	TYPE pr ;
	TYPE pt = DEREF_type ( type_ptr_mem_sub ( t ) ) ;
	TYPE ps = DEREF_type ( type_ptr_mem_sub ( s ) ) ;
	if ( EQ_ctype ( cr, ct ) ) {
	    cr = cs ;
	    pr = ps ;
	} else {
	    cr = ct ;
	    pr = pt ;
	}

	/* Check that underlying types are the same */
	if ( eq_type_unqual ( pt, ps ) ) {
	    /* Form the result type */
	    CV_SPEC qt = find_cv_qual ( pt ) ;
	    CV_SPEC qs = find_cv_qual ( ps ) ;
	    CV_SPEC qr = ( qt | qs ) ;
	    pr = qualify_type ( pr, qr, 0 ) ;
	    if ( qt != qs && qr != qs ) *suspect = 1 ;
	    if ( EQ_ctype ( cr, ct ) && EQ_type ( pr, pt ) ) return ( t ) ;
	    if ( EQ_ctype ( cr, cs ) && EQ_type ( pr, ps ) ) return ( s ) ;
	    MAKE_type_ptr_mem ( cv_none, cr, pr, pr ) ;
	    return ( pr ) ;
	}
    }

    /* Can't bring to common pointer member type */
    if ( is_templ_type ( t ) || is_templ_type ( s ) ) {
	*suspect = -1 ;
    } else {
	*suspect = 2 ;
    }
    return ( type_error ) ;
}


/*
    FIND A COMMON TYPE

    This routine finds the common type for the types t and s.  This is
    the other type if either type is null, the single type if they are
    equal, the arithmetic type if they are both arithmetic and the common
    pointer, reference or pointer-to-member type if these are appropriate.
    The null type is returned if the common type cannot be formed and
    suspect is set accordingly.  The rules are essentially the same as
    for the '?:' operation.
*/

TYPE common_type
    PROTO_N ( ( t, s, suspect ) )
    PROTO_T ( TYPE t X TYPE s X int *suspect )
{
    unsigned nt, ns ;
    TYPE r = NULL_type ;
    if ( IS_NULL_type ( t ) ) return ( s ) ;
    if ( IS_NULL_type ( s ) ) return ( t ) ;
    nt = TAG_type ( t ) ;
    ns = TAG_type ( s ) ;
    if ( nt == ns ) {
	switch ( nt ) {
	    case type_ptr_tag :
	    case type_ref_tag : {
		/* Common pointer or reference type */
		r = ptr_common_type ( t, s, 1, suspect ) ;
		if ( *suspect != 2 ) return ( r ) ;
		r = NULL_type ;
		break ;
	    }
	    case type_ptr_mem_tag : {
		/* Common pointer to member type */
		r = ptr_mem_common_type ( t, s, suspect ) ;
		if ( *suspect != 2 ) return ( r ) ;
		r = NULL_type ;
		break ;
	    }
	    default : {
		/* Other types */
		if ( eq_type_unqual ( t, s ) ) {
		    CV_SPEC qt = find_cv_qual ( t ) ;
		    CV_SPEC qs = find_cv_qual ( s ) ;
		    if ( qt != qs ) {
			*suspect = 1 ;
			t = qualify_type ( t, ( qt | qs ), 0 ) ;
		    }
		    return ( t ) ;
		}
		break ;
	    }
	}
    }
    switch ( nt ) {
	case type_integer_tag :
	case type_enumerate_tag :
	case type_bitfield_tag :
	case type_floating_tag : {
	    switch ( ns ) {
		case type_integer_tag :
		case type_enumerate_tag :
		case type_bitfield_tag :
		case type_floating_tag : {
		    /* Common arithmetic type */
		    r = arith_type ( t, s, NULL_exp, NULL_exp ) ;
		    return ( r ) ;
		}
	    }
	}
    }
#if LANGUAGE_C
    if ( IS_NULL_type ( r ) ) {
	r = type_composite ( t, s, 1, 0, KILL_err, 1 ) ;
	if ( !IS_NULL_type ( r ) ) return ( r ) ;
    }
#endif
    if ( nt == type_error_tag ) return ( s ) ;
    if ( ns == type_error_tag ) return ( t ) ;
    *suspect = 2 ;
    return ( r ) ;
}


/*
    CONVERT AN EXPRESSION TO ITS PROMOTED TYPE

    This routine converts the expression e to its promoted type, t
    (previously calculated using promote_type).  Note that there is no
    effect unless t is an integral type.
*/

EXP convert_promote
    PROTO_N ( ( t, e ) )
    PROTO_T ( TYPE t X EXP e )
{
    if ( IS_type_integer ( t ) ) {
	TYPE s = DEREF_type ( exp_type ( e ) ) ;
	if ( !EQ_type ( t, s ) ) {
	    /* Perform non-trivial integral promotions */
	    e = cast_int_int ( t, e, KILL_err, CAST_IMPLICIT, 0 ) ;
	}
    }
    return ( e ) ;
}


/*
    CONVERT AN EXPRESSION TO ITS ARITHMETIC TYPE

    This routine converts the expression e to an arithmetic result type, t,
    formed by arith_type using the type of e as its nth argument.  Note that
    there are three cases: integer->integer, integer->float and float->float.
*/

EXP convert_arith
    PROTO_N ( ( t, e, op, n ) )
    PROTO_T ( TYPE t X EXP e X int op X int n )
{
    TYPE s = DEREF_type ( exp_type ( e ) ) ;
    if ( !EQ_type ( t, s ) ) {
	ERROR err = NULL_err ;
	if ( IS_type_floating ( t ) ) {
	    unsigned tag = TAG_type ( s ) ;
	    if ( tag == type_floating_tag ) {
		e = cast_float_float ( t, e, &err, CAST_IMPLICIT ) ;
	    } else {
		if ( tag == type_bitfield_tag ) {
		    s = find_bitfield_type ( s ) ;
		    e = cast_int_int ( s, e, &err, CAST_IMPLICIT, -1 ) ;
		}
		e = cast_int_float ( t, e, &err, CAST_IMPLICIT ) ;
	    }
	} else {
	    e = cast_int_int ( t, e, &err, CAST_IMPLICIT, -1 ) ;
	}
	if ( !IS_NULL_err ( err ) ) {
	    unsigned m = ( unsigned ) n ;
	    err = concat_error ( err, ERR_expr_convert_op ( m, op ) ) ;
	    report ( crt_loc, err ) ;
	}
    }
    return ( e ) ;
}


/*
    CONVERT A POINTER TO A COMMON POINTER TYPE

    This routine converts the pointer expression e to a common pointer
    type, t, formed by ptr_common_type using the type of e as its nth
    argument.
*/

EXP convert_ptr_common
    PROTO_N ( ( t, e, op, n ) )
    PROTO_T ( TYPE t X EXP e X int op X int n )
{
    TYPE s = DEREF_type ( exp_type ( e ) ) ;
    if ( !EQ_type ( t, s ) ) {
	ERROR err = NULL_err ;
	e = cast_ptr_ptr ( t, e, &err, CAST_IMPLICIT, 1, 1 ) ;
	if ( !IS_NULL_err ( err ) ) {
	    unsigned m = ( unsigned ) n ;
	    err = concat_error ( err, ERR_expr_convert_op ( m, op ) ) ;
	    report ( crt_loc, err ) ;
	}
    }
    return ( e ) ;
}


/*
    CONVERT A POINTER MEMBER TO A COMMON POINTER MEMBER TYPE

    This routine converts the pointer member expression e to a common
    pointer to member type, t, formed by ptr_mem_common_type using the
    type of e as its nth argument.
*/

EXP convert_ptr_mem_common
    PROTO_N ( ( t, e, op, n ) )
    PROTO_T ( TYPE t X EXP e X int op X int n )
{
    TYPE s = DEREF_type ( exp_type ( e ) ) ;
    if ( !EQ_type ( t, s ) ) {
	ERROR err = NULL_err ;
	e = cast_ptr_mem_ptr_mem ( t, e, &err, CAST_IMPLICIT, 1, 1 ) ;
	if ( !IS_NULL_err ( err ) ) {
	    unsigned m = ( unsigned ) n ;
	    err = concat_error ( err, ERR_expr_convert_op ( m, op ) ) ;
	    report ( crt_loc, err ) ;
	}
    }
    return ( e ) ;
}


/*
    CHECK FOR ASSIGNMENT IN A BOOLEAN

    This routine checks whether the expression a, which is to be converted
    to a boolean, is an assignment.  A warning is issued for 'x = y' and
    'x /= y' because of possible confusion with 'x == y' and 'x != y'
    respectively.  If the original expression was enclosed in brackets
    (as indicated by tag) then no warning is issued.
*/

static void boolean_assign
    PROTO_N ( ( a, tag ) )
    PROTO_T ( EXP a X unsigned tag )
{
    if ( tag != exp_paren_tag && !suppress_quality ) {
	if ( IS_exp_assign ( a ) ) {
	    report ( crt_loc, ERR_conv_bool_assign () ) ;
	} else if ( IS_exp_preinc ( a ) ) {
	    int op = DEREF_int ( exp_preinc_becomes ( a ) ) ;
	    if ( op == lex_assign || op == lex_div_Heq ) {
		report ( crt_loc, ERR_conv_bool_assign () ) ;
	    }
	}
    }
    return ;
}


/*
    CONVERT AN EXPRESSION TO A BOOLEAN

    This routine converts the expression a to a boolean if this is possible,
    returning the corresponding boolean expression.  Any error arising are
    added to the position indicated by the err argument.  User-defined
    conversions are handled elsewhere.
*/

EXP convert_boolean
    PROTO_N ( ( a, tag, err ) )
    PROTO_T ( EXP a X unsigned tag X ERROR *err )
{
    EXP e ;
    TYPE t = DEREF_type ( exp_type ( a ) ) ;
    switch ( TAG_exp ( a ) ) {
	case exp_int_lit_tag : {
	    /* Check for integer literals */
	    e = make_test_nat ( a ) ;
	    return ( e ) ;
	}
	case exp_float_lit_tag : {
	    /* Check for floating-point literals */
	    FLOAT f = DEREF_flt ( exp_float_lit_flt ( a ) ) ;
	    NAT n = round_float_lit ( f, crt_round_mode ) ;
	    if ( !IS_NULL_nat ( n ) && IS_nat_small ( n ) ) {
		unsigned v = DEREF_unsigned ( nat_small_value ( n ) ) ;
		if ( v < 2 ) {
		    v = BOOL_VALUE ( v ) ;
		    e = make_bool_exp ( v, exp_float_lit_tag ) ;
		    return ( e ) ;
		}
	    }
	    MAKE_exp_test ( type_bool, ntest_not_eq, a, e ) ;
	    MAKE_nat_calc ( e, n ) ;
	    MAKE_exp_int_lit ( type_bool, n, exp_test_tag, e ) ;
	    return ( e ) ;
	}
	case exp_contents_tag : {
	    /* Check for assignment in boolean */
	    EXP b = DEREF_exp ( exp_contents_ptr ( a ) ) ;
	    switch ( TAG_exp ( b ) ) {
		case exp_assign_tag :
		case exp_preinc_tag :
		case exp_postinc_tag : {
		    boolean_assign ( b, tag ) ;
		    break ;
		}
	    }
	    break ;
	}
	case exp_assign_tag :
	case exp_preinc_tag :
	case exp_postinc_tag : {
	    /* Check for assignment in boolean */
	    boolean_assign ( a, tag ) ;
	    break ;
	}
    }

    /* Perform the conversion */
    switch ( TAG_type ( t ) ) {
	case type_integer_tag : {
	    /* Integral types are allowed */
	    if ( check_int_type ( t, btype_bool ) ) return ( a ) ;
	    break ;
	}
	case type_bitfield_tag : {
	    /* Convert bitfields to integers */
	    a = convert_bitfield ( a ) ;
	    break ;
	}
	case type_enumerate_tag :
	case type_floating_tag :
	case type_ptr_tag :
	case type_ptr_mem_tag : {
	    /* These types are allowed */
	    break ;
	}
	case type_error_tag : {
	    /* Allow for error propagation */
	    break ;
	}
	default : {
	    /* These types are not allowed */
	    add_error ( err, ERR_conv_bool_cast ( t ) ) ;
	    break ;
	}
    }
    MAKE_exp_test ( type_bool, ntest_not_eq, a, e ) ;
    return ( e ) ;
}


/*
    REPORT OVERLOADED FUNCTIONS

    This routine prints an error and returns true if e represents an
    overloaded function.  If it represents a non-overloaded function which
    has not already resolved using resolve_cast then the function is
    marked as used.
*/

static int is_overloaded
    PROTO_N ( ( e ) )
    PROTO_T ( EXP e )
{
    if ( !IS_NULL_exp ( e ) && IS_exp_identifier_etc ( e ) ) {
	IDENTIFIER id = DEREF_id ( exp_identifier_etc_id ( e ) ) ;
	if ( IS_id_function_etc ( id ) ) {
	    QUALIFIER q = DEREF_qual ( exp_identifier_etc_qual ( e ) ) ;
	    if ( !( q & qual_mark ) ) {
		/* Not already resolved */
		TYPE fn = DEREF_type ( id_function_etc_type ( id ) ) ;
		IDENTIFIER over = DEREF_id ( id_function_etc_over ( id ) ) ;
		if ( !IS_NULL_id ( over ) || IS_type_templ ( fn ) ) {
		    /* Overloaded function */
		    report ( crt_loc, ERR_over_over_context ( id ) ) ;
		    return ( 1 ) ;
		}
		use_id ( id, suppress_usage ) ;
	    }
	}
    }
    return ( 0 ) ;
}


/*
    PERFORM QUALIFICATION CONVERSIONS ON A TYPE

    This routine removes any type qualifiers from a rvalue, non-class
    type t.  Class types maintain their type qualifiers, lvalue types
    lose theirs in convert_lvalue.
*/

TYPE convert_qual_type
    PROTO_N ( ( t ) )
    PROTO_T ( TYPE t )
{
    CV_SPEC qual = DEREF_cv ( type_qual ( t ) ) ;
    if ( qual && !( qual & cv_lvalue ) ) {
#if LANGUAGE_CPP
	if ( IS_type_compound ( t ) ) return ( t ) ;
#endif
	t = qualify_type ( t, cv_none, 0 ) ;
    }
    return ( t ) ;
}


/*
    EVALUATE A CONST VARIABLE

    This routine evaluates the 'const' variable expression a, so that
    for example, if 'const int c = 5 ;' then 'c' is evaluated to '5'.
*/

EXP convert_const
    PROTO_N ( ( a ) )
    PROTO_T ( EXP a )
{
#if LANGUAGE_CPP
    IDENTIFIER id = DEREF_id ( exp_identifier_id ( a ) ) ;
    EXP e = DEREF_exp ( id_variable_etc_init ( id ) ) ;
    if ( !IS_NULL_exp ( e ) ) {
	switch ( TAG_exp ( e ) ) {
	    case exp_int_lit_tag : {
		/* Propagate simple constants */
		NAT n ;
		TYPE t ;
		unsigned tag ;
		DECONS_exp_int_lit ( t, n, tag, e ) ;
		MAKE_exp_int_lit ( t, n, tag, e ) ;
		return ( e ) ;
	    }
	    case exp_null_tag : {
		/* Propagate null constants */
		TYPE t ;
		DECONS_exp_null ( t, e ) ;
		MAKE_exp_null ( t, e ) ;
		return ( e ) ;
	    }
	}
    }
#endif
    return ( a ) ;
}


/*
    PERFORM ARRAY TO POINTER CONVERSION

    This routine performs array to pointer conversion on the array
    expression a.  If a is a string literal and str is true then the
    const qualifiers are removed from the string.  A warning is also
    added to err if str is 2.
*/

EXP convert_array
    PROTO_N ( ( a, str, err ) )
    PROTO_T ( EXP a X int str X ERROR *err )
{
    TYPE t = DEREF_type ( exp_type ( a ) ) ;
    TYPE s = DEREF_type ( type_array_sub ( t ) ) ;
    if ( str && IS_exp_string_lit ( a ) ) {
	/* Remove const from string literals */
	CV_SPEC cv = DEREF_cv ( type_qual ( s ) ) ;
	if ( cv & cv_const ) {
	    cv &= ~cv_const ;
	    s = qualify_type ( s, cv, 0 ) ;
	    if ( str == 2 ) add_error ( err, ERR_conv_array_string () ) ;
	}
    } else if ( option ( OPT_addr_register ) && used_register ) {
	/* Can't apply to a register variable in C */
	EXP b = NULL_exp ;
	DECL_SPEC ds = find_exp_linkage ( a, &b, 1 ) ;
	if ( ( ds & dspec_register ) && !( ds & dspec_temp ) ) {
	    if ( IS_exp_identifier ( b ) ) {
		IDENTIFIER id = DEREF_id ( exp_identifier_id ( b ) ) ;
		add_error ( err, ERR_expr_unary_op_ref_register ( id ) ) ;
	    }
	}
    }
    MAKE_type_ptr ( cv_none, s, t ) ;
    MAKE_exp_address ( t, a, a ) ;
    return ( a ) ;
}


/*
    PERFORM LVALUE CONVERSIONS

    This routine performs the lvalue conversions on the expression a.
    If e is an lvalue, the lvalue-to-rvalue, array-to-pointer and
    function-to-pointer conversions are applied to transform it into an
    rvalue.  Checks for overloaded functions are also applied at this
    stage to both lvalues and rvalues.
*/

EXP convert_lvalue
    PROTO_N ( ( a ) )
    PROTO_T ( EXP a )
{
    EXP e = a ;
    TYPE t = DEREF_type ( exp_type ( a ) ) ;
    CV_SPEC qual = DEREF_cv ( type_qual ( t ) ) ;
    if ( qual & cv_lvalue ) {
	CV_SPEC cv = cv_none ;
	switch ( TAG_type ( t ) ) {
	    case type_array_tag : {
		/* Array-to-pointer conversion */
		ERROR err = NULL_err ;
		e = convert_array ( a, 0, &err ) ;
		if ( !IS_NULL_err ( err ) ) report ( crt_loc, err ) ;
		break ;
	    }
	    case type_func_tag : {
		/* Function-to-pointer conversion */
		if ( is_overloaded ( a ) ) {
		    e = make_error_exp ( 0 ) ;
		    break ;
		}
		if ( IS_exp_member ( a ) ) goto default_lab ;
		MAKE_type_ptr ( cv_none, t, t ) ;
		MAKE_exp_address ( t, a, e ) ;
		break ;
	    }
#if LANGUAGE_CPP
	    case type_compound_tag : {
		/* Classes preserve qualifiers in lvalue conversion */
		cv = ( qual & cv_qual ) ;
		goto default_lab ;
	    }
#endif
	    case type_templ_tag : {
		/* Can't have template expressions */
		if ( !is_overloaded ( a ) ) {
		    report ( crt_loc, ERR_temp_local_not ( t ) ) ;
		}
		e = make_error_exp ( 0 ) ;
		break ;
	    }
	    default :
	    default_lab : {
		/* Lvalue-to-rvalue conversion */
		ERROR err ;
		if ( qual == ( cv_const | cv_lvalue ) ) {
		    /* Check for constants at this stage */
		    if ( IS_exp_identifier ( a ) ) {
			e = convert_const ( a ) ;
			if ( !EQ_exp ( e, a ) ) return ( e ) ;
		    }
		}
		t = qualify_type ( t, cv, 0 ) ;
		err = check_incomplete ( t ) ;
		if ( !IS_NULL_err ( err ) ) {
		    err = concat_error ( err, ERR_conv_lval_incompl () ) ;
		    report ( crt_loc, err ) ;
		}
		MAKE_exp_contents ( t, a, e ) ;
		break ;
	    }
	}

    } else {
	/* Check rvalues for overloaded functions */
	switch ( TAG_exp ( e ) ) {
	    case exp_address_tag : {
		/* Address of object or function */
		EXP b = DEREF_exp ( exp_address_arg ( a ) ) ;
		if ( is_overloaded ( b ) ) e = make_error_exp ( 0 ) ;
		break ;
	    }
	    case exp_address_mem_tag : {
		/* Address of member or member function */
		EXP b = DEREF_exp ( exp_address_mem_arg ( a ) ) ;
		if ( is_overloaded ( b ) ) e = make_error_exp ( 0 ) ;
		break ;
	    }
	    case exp_token_tag : {
		/* Check for tokenised arrays */
		if ( IS_type_array ( t ) ) {
		    ERROR err = NULL_err ;
		    e = convert_array ( a, 0, &err ) ;
		    if ( !IS_NULL_err ( err ) ) report ( crt_loc, err ) ;
		}
		break ;
	    }
	}
    }
    return ( e ) ;
}


/*
    CHECK AMBIGUOUS IDENTIFIERS

    This routine checks whether the identifier id represents a non-member
    function or an ambiguous set of such functions.  It is required because
    overload resolution is used to distinguish between the ambiguous cases
    for non-member functions, whereas it is an error otherwise.
*/

int is_ambiguous_func
    PROTO_N ( ( id ) )
    PROTO_T ( IDENTIFIER id )
{
    switch ( TAG_id ( id ) ) {
	case id_ambig_tag : {
	    /* Deal with ambiguous identifiers */
	    LIST ( IDENTIFIER ) p = DEREF_list ( id_ambig_ids ( id ) ) ;
	    while ( !IS_NULL_list ( p ) ) {
		id = DEREF_id ( HEAD_list ( p ) ) ;
		if ( !is_ambiguous_func ( id ) ) return ( 0 ) ;
		p = TAIL_list ( p ) ;
	    }
	    return ( 1 ) ;
	}
	case id_function_tag : {
	    /* These are functions */
	    return ( 1 ) ;
	}
    }
    return ( 0 ) ;
}


/*
    PERFORM REFERENCE CONVERSIONS

    This routine performs the reference conversions on the expression a.
    That is, if a has type reference to t, then it is transformed into an
    lvalue of type t.  Other checks are also applied to a - for example,
    parentheses are removed, undeclared variables are reported, and
    constants are evaluated.  The precise checks applied depend on context
    which can take one of the values from convert.h.
*/

EXP convert_reference
    PROTO_N ( ( a, context ) )
    PROTO_T ( EXP a X int context )
{
    /* Remove parentheses */
    TYPE t ;
    unsigned etag = TAG_exp ( a ) ;
    if ( etag == exp_paren_tag ) {
	do {
	    DESTROY_exp_paren ( destroy, t, a, a ) ;
	    etag = TAG_exp ( a ) ;
	} while ( etag == exp_paren_tag ) ;
    } else {
	t = DEREF_type ( exp_type ( a ) ) ;
    }

    /* Apply extra checks */
    switch ( etag ) {

	case exp_member_tag : {
	    /* Non-static data members and all function members */
	    if ( context == REF_ADDRESS ) {
		/* Suppress reference conversions */
		t = type_error ;
	    } else {
		IDENTIFIER id = DEREF_id ( exp_member_id ( a ) ) ;
		if ( context == REF_NORMAL || IS_id_member ( id ) ) {
		    EXP b = make_this_field ( id ) ;
		    if ( IS_NULL_exp ( b ) ) {
			report ( crt_loc, ERR_expr_prim_mem ( id ) ) ;
			a = make_error_exp ( 0 ) ;
		    } else {
			a = b ;
			if ( IS_exp_call ( a ) ) goto call_lab ;
		    }
		    t = DEREF_type ( exp_type ( a ) ) ;
		    etag = TAG_exp ( a ) ;
		}
	    }
	    break ;
	}

	case exp_ambiguous_tag : {
	    /* Ambiguous identifiers */
	    IDENTIFIER id = DEREF_id ( exp_ambiguous_id ( a ) ) ;
	    if ( context == REF_NORMAL || !is_ambiguous_func ( id ) ) {
		/* Report ambiguous identifier */
		IGNORE report_ambiguous ( id, 0, 1, 0 ) ;
		a = make_error_exp ( 0 ) ;
		t = DEREF_type ( exp_type ( a ) ) ;
	    } else {
		/* Allow ambiguous functions */
		t = type_func_void ;
		t = lvalue_type ( t ) ;
		COPY_type ( exp_type ( a ), t ) ;
	    }
	    break ;
	}

	case exp_undeclared_tag : {
	    /* Undeclared identifiers */
	    if ( context == REF_FUNCTION || context == REF_ADDRESS ) {
		/* Deal with undeclared functions later */
		t = type_func_void ;
		t = lvalue_type ( t ) ;
		COPY_type ( exp_type ( a ), t ) ;
	    } else {
		/* Report undeclared identifiers */
		IDENTIFIER id = DEREF_id ( exp_undeclared_id ( a ) ) ;
		crt_id_qualifier = DEREF_qual ( exp_undeclared_qual ( a ) ) ;
		a = implicit_id_exp ( id, 0 ) ;
		t = DEREF_type ( exp_type ( a ) ) ;
	    }
	    break ;
	}

	case exp_address_tag : {
	    /* Address of object */
	    EXP b = DEREF_exp ( exp_address_arg ( a ) ) ;
	    unsigned btag = TAG_exp ( b ) ;
	    if ( btag == exp_ambiguous_tag ) {
		if ( context != REF_FUNCTION && context != REF_ASSIGN ) {
		    /* Ambiguous function */
		    b = convert_reference ( b, REF_NORMAL ) ;
		    a = make_ref_exp ( b, 1 ) ;
		    t = DEREF_type ( exp_type ( a ) ) ;
		}
	    } else if ( btag == exp_undeclared_tag ) {
		if ( context != REF_FUNCTION ) {
		    /* Undeclared function */
		    b = convert_reference ( b, REF_NORMAL ) ;
		    a = make_ref_exp ( b, 1 ) ;
		    t = DEREF_type ( exp_type ( a ) ) ;
		}
	    } else if ( btag == exp_call_tag ) {
		if ( context != REF_ASSIGN ) {
		    b = DEREF_exp ( exp_call_ptr ( b ) ) ;
		    if ( IS_exp_member ( b ) ) {
			/* Member function selector */
			if ( !is_overloaded ( b ) ) {
			    report ( crt_loc, ERR_expr_ref_call () ) ;
			}
			a = make_error_exp ( 0 ) ;
			t = DEREF_type ( exp_type ( a ) ) ;
		    }
		}
	    }
	    break ;
	}

	case exp_call_tag :
	call_lab : {
	    /* All member function calls */
	    if ( context != REF_FUNCTION ) {
		EXP b = DEREF_exp ( exp_call_ptr ( a ) ) ;
		unsigned btag = TAG_exp ( b ) ;
		if ( btag == exp_identifier_tag ) {
		    /* Single static member function */
		    IDENTIFIER id = DEREF_id ( exp_identifier_id ( b ) ) ;
		    use_id ( id, suppress_usage ) ;
		    a = DEREF_exp ( exp_call_arg ( a ) ) ;
		    a = join_exp ( a, b ) ;
		    t = DEREF_type ( exp_type ( a ) ) ;
		    break ;
		}
		if ( btag == exp_member_tag ) {
		    /* Other member functions */
		    if ( context != REF_NORMAL ) break ;
		    if ( !is_overloaded ( b ) ) {
			report ( crt_loc, ERR_expr_ref_call () ) ;
		    }
		} else {
		    /* Pointer to member functions */
		    report ( crt_loc, ERR_expr_mptr_oper_call () ) ;
		}
		a = make_error_exp ( 0 ) ;
		t = DEREF_type ( exp_type ( a ) ) ;
	    }
	    break ;
	}
    }

    /* Check for reference conversions */
    if ( IS_type_ref ( t ) ) {
	/* Reference to t becomes lvalue t */
	if ( etag == exp_indir_tag ) {
	    /* Can't have two indirections in a row */
	    MAKE_exp_contents ( t, a, a ) ;
	}
	t = DEREF_type ( type_ref_sub ( t ) ) ;
	/* Note that t is already an lvalue */
	MAKE_exp_indir ( t, a, a ) ;
    }
    return ( a ) ;
}


/*
    PROMOTE BITFIELD EXPRESSIONS

    In certain expressions, even though an integral operand is not subject
    to integer promotion, bitfield expressions need to be converted to
    integral expressions by promotion.  This routine performs this conversion
    for the expression a.
*/

EXP convert_bitfield
    PROTO_N ( ( a ) )
    PROTO_T ( EXP a )
{
    TYPE t = DEREF_type ( exp_type ( a ) ) ;
    if ( IS_type_bitfield ( t ) ) {
	t = promote_type ( t ) ;
	a = convert_promote ( t, a ) ;
    }
    return ( a ) ;
}


/*
    CONVERT OPERAND WHERE NO CONTEXT IS GIVEN

    This routine performs conversions on the operand a in contexts where
    there is no information to resolve overloaded functions etc.  It also
    introduces temporary variables for constructor call expressions.
*/

EXP convert_none
    PROTO_N ( ( a ) )
    PROTO_T ( EXP a )
{
    if ( !IS_NULL_exp ( a ) ) {
	ERROR err = NULL_err ;
	if ( IS_exp_constr ( a ) ) {
	    TYPE t = DEREF_type ( exp_type ( a ) ) ;
	    a = make_temporary ( t, a, NULL_exp, 0, &err ) ;
	    a = convert_lvalue ( a ) ;
	} else {
	    LIST ( IDENTIFIER ) pids = NULL_list ( IDENTIFIER ) ;
	    a = resolve_cast ( type_void, a, &err, 1, 0, pids ) ;
	}
	if ( !IS_NULL_err ( err ) ) report ( crt_loc, err ) ;
    }
    return ( a ) ;
}


/*
    QUALIFICATION CONVERSIONS

    The values cv_const and cv_volatile are used to represent qualification
    conversions which add the corresponding qualifiers at a single level.
    cv_strlit is used to represent the removal of const from a string
    literal.  cv_multi is used to represent qualifications which add
    qualifiers at more than one level.
*/

#define cv_strlit	( ( CV_SPEC ) 0x10 )
#define cv_multi	( ( CV_SPEC ) 0x20 )


/*
    CHECK FOR OVERLOADED FUNCTION CONVERSION SEQUENCES

    This routine checks for conversion sequences between the overloaded
    function id and the pointer or pointer to member (of the correct class)
    type t.
*/

static unsigned overload_convert_seq
    PROTO_N ( ( t, id, p ) )
    PROTO_T ( TYPE t X IDENTIFIER id X CONVERSION *p )
{
    /* Check arguments */
    TYPE fn ;
    int eq = 0 ;
    CV_SPEC cv ;
    unsigned conv = CONV_EXACT ;
    unsigned tag = TAG_type ( t ) ;
    if ( tag == type_ptr_tag ) {
	fn = DEREF_type ( type_ptr_sub ( t ) ) ;
    } else {
	fn = DEREF_type ( type_ptr_mem_sub ( t ) ) ;
    }
    if ( !IS_type_func ( fn ) ) return ( CONV_NONE ) ;
    cv = DEREF_cv ( type_qual ( fn ) ) ;
    cv &= cv_qual ;
    if ( cv != cv_none ) conv = CONV_QUAL ;
    p->qual = cv ;

    /* Check for matching overload function */
    id = resolve_func ( id, fn, 1, 0, NULL_list ( IDENTIFIER ), &eq ) ;
    if ( !IS_NULL_id ( id ) && eq == 3 ) {
	switch ( TAG_id ( id ) ) {
	    case id_mem_func_tag : {
		/* A member function gives a pointer to member */
		if ( tag == type_ptr_mem_tag ) return ( conv ) ;
		break ;
	    }
	    case id_function_tag :
	    case id_stat_mem_func_tag : {
		/* Other functions give pointers */
		if ( tag == type_ptr_tag ) return ( conv ) ;
		break ;
	    }
	}
    }
    return ( CONV_NONE ) ;
}


/*
    CHECK FOR REFERENCE CONVERSION SEQUENCES

    This routine checks the conversion sequence p, the destination type
    of which is a reference type.  If std is true then only standard
    conversions will be applied.  bind describes the form of reference
    binding to take place.  The normal value is 0, implements the normal
    reference binding rules.  A value of 1 is used to suppress all
    rvalue reference bindings.  Values of 2 and 3 allow rvalues of
    related types to be bound to any reference (not just const references),
    with 2 further regarding any base class conversions as exact matches.
*/

static unsigned ref_convert_seq
    PROTO_N ( ( p, e, bind, std ) )
    PROTO_T ( CONVERSION *p X EXP e X int bind X int std )
{
    unsigned conv ;
    TYPE t = DEREF_type ( type_ref_sub ( p->to ) ) ;
    TYPE s = p->from ;
    unsigned nt = TAG_type ( t ) ;
    unsigned ns = TAG_type ( s ) ;
    CV_SPEC qs = DEREF_cv ( type_qual ( s ) ) ;
    if ( qs & cv_lvalue ) {
	CV_SPEC cv = cv_compare ( t, s ) ;
	if ( cv == cv_none ) {
	    /* Qualifiers are alright */
	    cv = cv_compare ( s, t ) ;
	    p->qual = cv ;
	    if ( eq_type_unqual ( s, t ) ) {
		if ( cv == cv_none ) {
		    conv = CONV_EXACT ;
		} else {
		    conv = CONV_QUAL ;
		}
		return ( conv ) ;
	    }
	    if ( ns == type_compound_tag && nt == type_compound_tag ) {
		CLASS_TYPE ct = DEREF_ctype ( type_compound_defn ( t ) ) ;
		CLASS_TYPE cs = DEREF_ctype ( type_compound_defn ( s ) ) ;
		if ( eq_ctype ( ct, cs ) ) {
		    /* Classes match */
		    if ( cv == cv_none ) {
			conv = CONV_EXACT ;
		    } else {
			conv = CONV_QUAL ;
		    }
		    return ( conv ) ;
		} else {
		    /* Check for base classes */
		    GRAPH gr = find_base_class ( cs, ct, 0 ) ;
		    if ( !IS_NULL_graph ( gr ) ) {
			/* Base class conversion */
			p->base = gr ;
			if ( bind == 2 ) {
			    /* Base class conversions match exactly */
			    if ( cv == cv_none ) {
				conv = CONV_EXACT ;
			    } else {
				conv = CONV_QUAL ;
			    }
			} else {
			    conv = CONV_BASE ;
			}
			return ( conv ) ;
		    }
		}
	    }
	}
    }
    if ( bind == 0 ) {
	/* Default - only const references allowed */
	CV_SPEC qt = find_cv_qual ( t ) ;
	if ( qt != ( cv_lvalue | cv_const ) ) return ( CONV_NONE ) ;
	qs = find_cv_qual ( s ) ;
	if ( qs & cv_volatile ) return ( CONV_NONE ) ;
    } else if ( bind == 1 ) {
	/* No references allowed */
	return ( CONV_NONE ) ;
    } else {
	/* All references allowed */
	std = 1 ;
    }
    p->to = t ;
    p->from = s ;
    if ( std ) {
	conv = std_convert_seq ( p, e, bind, 1 ) ;
    } else {
	conv = convert_seq ( p, e, bind, 1 ) ;
    }
    if ( bind == 2 ) {
	/* Base class conversions match exactly */
	if ( conv == CONV_BASE ) {
	    if ( p->qual == cv_none ) {
		conv = CONV_EXACT ;
	    } else {
		conv = CONV_QUAL ;
	    }
	}
    }
    return ( conv ) ;
}


/*
    CHECK FOR STANDARD CONVERSION SEQUENCES

    This routine checks whether there is a standard conversion sequence
    between the types given by p.  e gives the argument being converted
    (this is only used in identifying null pointer and null pointer member
    conversions).  The arguments bind and ref describe how reference bindings
    are to be treated (see above).  Note that conversion are applied in
    the canonical sequence, lvalue transformations, promotions, conversions
    and qualification adjustments.  The routine returns the value indicating
    the rank of this conversion.
*/

unsigned std_convert_seq
    PROTO_N ( ( p, e, bind, ref ) )
    PROTO_T ( CONVERSION *p X EXP e X int bind X int ref )
{
    CV_SPEC qs ;
    int str = 0 ;
    unsigned etag ;
    TYPE t = p->to ;
    TYPE s = p->from ;
    unsigned nt, ns ;
    unsigned conv = CONV_NONE ;

    /* Conversion to the null type counts as exact */
    if ( IS_NULL_type ( t ) ) return ( CONV_EXACT ) ;

    /* Conversion from the error type counts as ellipsis */
    ns = TAG_type ( s ) ;
    if ( ns == type_error_tag ) return ( CONV_ELLIPSIS ) ;
    qs = DEREF_cv ( type_qual ( s ) ) ;

    /* Reference conversion */
    if ( ns == type_ref_tag ) {
	s = DEREF_type ( type_ref_sub ( s ) ) ;
	p->from = s ;
	ns = TAG_type ( s ) ;
	if ( ns == type_error_tag ) return ( CONV_ELLIPSIS ) ;
	qs = DEREF_cv ( type_qual ( s ) ) ;
    }

    /* Deal with conversions to reference types */
    nt = TAG_type ( t ) ;
    if ( nt == type_ref_tag ) {
	conv = ref_convert_seq ( p, e, bind, 1 ) ;
	return ( conv ) ;
    }

    /* Examine expression */
    etag = ( IS_NULL_exp ( e ) ? null_tag : TAG_exp ( e ) ) ;

    /* Lvalue transformations */
    if ( qs & cv_lvalue ) {
	if ( ns == type_func_tag ) {
	    /* Function to pointer conversion */
	    if ( etag != exp_member_tag ) {
		TYPE ps = s ;
		s = type_temp_star ;
		COPY_type ( type_ptr_sub ( s ), ps ) ;
		ns = type_ptr_tag ;
	    }
	} else if ( ns == type_array_tag ) {
	    /* Array to pointer conversion */
	    TYPE ps = DEREF_type ( type_array_sub ( s ) ) ;
	    s = type_temp_star ;
	    COPY_type ( type_ptr_sub ( s ), ps ) ;
	    ns = type_ptr_tag ;
	} else {
	    /* lvalue to rvalue conversion */
	    if ( etag == exp_identifier_tag ) {
		if ( qs == ( cv_lvalue | cv_const ) ) {
		    IDENTIFIER id = DEREF_id ( exp_identifier_id ( e ) ) ;
		    EXP d = DEREF_exp ( id_variable_etc_init ( id ) ) ;
		    if ( is_zero_exp ( d ) ) {
			/* Propagate zero constants */
			e = d ;
		    }
		}
	    }
	}
    }

    /* Promotions and conversions */
    switch ( ns ) {

	case type_integer_tag :
	case type_enumerate_tag :
	integral_lab : {
	    /* Integral and similar arguments */
	    if ( nt == ns && eq_type_unqual ( t, s ) ) {
		/* Exact match */
		conv = CONV_EXACT ;
	    } else {
		TYPE ps = promote_type ( s ) ;
		if ( !EQ_type ( ps, s ) && eq_type_unqual ( t, ps ) ) {
		    /* Integral promotion */
		    conv = CONV_INT_PROM ;
		} else if ( nt == type_integer_tag ) {
		    /* Integral conversions (subsumes booleans) */
		    conv = CONV_INT_INT ;
		} else if ( nt == type_floating_tag ) {
		    /* Floating-integer conversions */
		    conv = CONV_INT_FLT ;
		} else if ( is_zero_exp ( e ) ) {
		    if ( nt == type_ptr_tag ) {
			/* Null pointers */
			conv = CONV_PTR_NULL ;
		    } else if ( nt == type_ptr_mem_tag ) {
			/* Null pointer members */
			conv = CONV_PTR_MEM_NULL ;
		    }
		}
	    }
	    break ;
	}

	case type_bitfield_tag : {
	    /* Ignore any bitfield qualifiers */
	    s = find_bitfield_type ( s ) ;
	    ns = TAG_type ( s ) ;
	    goto integral_lab ;
	}

	case type_floating_tag : {
	    /* Floating point arguments */
	    if ( nt == type_floating_tag ) {
		if ( eq_type_unqual ( t, s ) ) {
		    /* Exact match */
		    conv = CONV_EXACT ;
		} else {
		    TYPE ps = arg_promote_type ( s, KILL_err ) ;
		    if ( !EQ_type ( ps, s ) && eq_type_unqual ( t, ps ) ) {
			/* Floating point promotion */
			conv = CONV_FLT_PROM ;
		    } else {
			/* Floating point conversions */
			conv = CONV_FLT_FLT ;
		    }
		}
	    } else if ( nt == type_integer_tag ) {
		/* Floating-integer conversions (subsumes booleans) */
		conv = CONV_FLT_INT ;
	    }
	    break ;
	}

	case type_ptr_tag :
	pointer_lab : {
	    /* Pointer arguments */
	    if ( nt == type_ptr_tag ) {
		/* Check for qualifier conversions */
		unsigned qual = check_qualifier ( t, s, 0 ) ;
		if ( qualifier_depth <= 1 ) {
		    CV_SPEC cv = qualifier_diff ;
		    if ( str ) cv |= cv_strlit ;
		    p->qual = cv ;
		} else {
		    p->qual = cv_multi ;
		}
		if ( qual == QUAL_EQUAL || qual == QUAL_EQ_FUNC ) {
		    /* Exact match */
		    conv = CONV_EXACT ;
		    if ( str ) conv = CONV_STRING ;
		} else if ( qual == QUAL_OK ) {
		    /* Qualification conversion */
		    conv = CONV_QUAL ;
		    if ( str ) conv = CONV_STRING ;
		} else if ( qual == QUAL_CV ) {
		    /* Conversion preserves cv-qualifiers */
		    TYPE pt = DEREF_type ( type_ptr_sub ( t ) ) ;
		    TYPE ps = DEREF_type ( type_ptr_sub ( s ) ) ;
		    nt = TAG_type ( pt ) ;
		    ns = TAG_type ( ps ) ;
		    if ( nt == type_compound_tag && ns == nt ) {
			/* Pointer base class conversions */
			GRAPH gr ;
			CLASS_TYPE ct, cs ;
			ct = DEREF_ctype ( type_compound_defn ( pt ) ) ;
			cs = DEREF_ctype ( type_compound_defn ( ps ) ) ;
			gr = find_base_class ( cs, ct, 0 ) ;
			if ( !IS_NULL_graph ( gr ) ) {
			    /* Don't worry about ambiguity */
			    p->base = gr ;
			    conv = CONV_PTR_BASE ;
			}
		    } else if ( nt == type_top_tag ) {
			if ( ns != type_func_tag ) {
			    /* Pointer to 'void *' conversions */
			    conv = CONV_PTR_VOID ;
			}
		    } else if ( nt == type_bottom_tag ) {
			if ( ns != type_func_tag ) {
			    /* Pointer to 'void *' conversions */
			    conv = CONV_PTR_BOTTOM ;
			}
		    }
		}
		if ( conv == CONV_NONE ) {
		    /* Check for string literals */
		    if ( etag == exp_string_lit_tag && !str ) {
			if ( !( qual & QUAL_CONST ) ) {
			    TYPE ps = DEREF_type ( type_ptr_sub ( s ) ) ;
			    ps = qualify_type ( ps, cv_none, 0 ) ;
			    s = type_temp_star ;
			    COPY_type ( type_ptr_sub ( s ), ps ) ;
			    str = 1 ;
			    goto pointer_lab ;
			}
		    }

		    /* Check for overloaded functions */
		    if ( etag == exp_address_tag ) {
			e = DEREF_exp ( exp_address_arg ( e ) ) ;
			etag = TAG_exp ( e ) ;
		    }
		    if ( etag == exp_identifier_tag ) {
			IDENTIFIER id = DEREF_id ( exp_identifier_id ( e ) ) ;
			conv = overload_convert_seq ( t, id, p ) ;
		    } else if ( etag == exp_ambiguous_tag ) {
			IDENTIFIER id = DEREF_id ( exp_ambiguous_id ( e ) ) ;
			conv = overload_convert_seq ( t, id, p ) ;
		    }
		}
	    } else if ( nt == type_integer_tag ) {
		if ( check_int_type ( t, btype_bool ) ) {
		    /* Boolean conversions */
		    conv = CONV_BOOL ;
		}
	    }
	    break ;
	}

#if LANGUAGE_CPP
	case type_ptr_mem_tag : {
	    /* Pointer to member arguments */
	    if ( nt == type_ptr_mem_tag ) {
		unsigned qual ;
		int ctype_match = 0 ;
		CLASS_TYPE ct = DEREF_ctype ( type_ptr_mem_of ( t ) ) ;
		CLASS_TYPE cs = DEREF_ctype ( type_ptr_mem_of ( s ) ) ;
		if ( eq_ctype ( ct, cs ) ) {
		    ctype_match = 2 ;
		} else {
		    GRAPH gr = find_base_class ( ct, cs, 0 ) ;
		    if ( !IS_NULL_graph ( gr ) ) {
			ctype_match = 1 ;
			p->base = gr ;
		    }
		}
		if ( ctype_match ) {
		    if ( etag == exp_address_mem_tag ) {
			/* Check overloaded functions */
			IDENTIFIER id ;
			e = DEREF_exp ( exp_address_mem_arg ( e ) ) ;
			id = DEREF_id ( exp_member_id ( e ) ) ;
			if ( IS_id_function_etc ( id ) ) {
			    conv = overload_convert_seq ( t, id, p ) ;
			    if ( conv != CONV_NONE && ctype_match == 1 ) {
				conv = CONV_PTR_MEM_BASE ;
			    }
			    break ;
			}
		    }
		    /* Check other cases */
		    qual = check_qualifier ( t, s, 0 ) ;
		    if ( qualifier_depth <= 1 ) {
			p->qual = qualifier_diff ;
		    } else {
			p->qual = cv_multi ;
		    }
		    if ( qual == QUAL_EQUAL || qual == QUAL_EQ_FUNC ) {
			/* Exact match */
			if ( ctype_match == 2 ) {
			    conv = CONV_EXACT ;
			} else {
			    conv = CONV_PTR_MEM_BASE ;
			}
		    } else if ( qual == QUAL_OK ) {
			/* Qualification conversion */
			if ( ctype_match == 2 ) {
			    conv = CONV_QUAL ;
			} else {
			    conv = CONV_PTR_MEM_BASE ;
			}
		    }
		}
	    } else if ( nt == type_integer_tag ) {
		if ( check_int_type ( t, btype_bool ) ) {
		    /* Boolean conversions */
		    conv = CONV_BOOL ;
		}
	    } else if ( nt == type_ptr_tag ) {
		if ( etag == exp_address_mem_tag ) {
		    /* Check overloaded functions */
		    IDENTIFIER id ;
		    e = DEREF_exp ( exp_address_mem_arg ( e ) ) ;
		    id = DEREF_id ( exp_member_id ( e ) ) ;
		    conv = overload_convert_seq ( t, id, p ) ;
		}
	    }
	    break ;
	}
#endif

	case type_compound_tag : {
	    /* Class arguments */
	    if ( nt == type_compound_tag ) {
		CV_SPEC cv = cv_compare ( t, s ) ;
		if ( cv == cv_none || !ref ) {
		    CLASS_TYPE ct, cs ;
		    cv = cv_compare ( s, t ) ;
		    p->qual = cv ;
		    ct = DEREF_ctype ( type_compound_defn ( t ) ) ;
		    cs = DEREF_ctype ( type_compound_defn ( s ) ) ;
		    if ( eq_ctype ( ct, cs ) ) {
			/* Class types match */
			if ( cv == cv_none ) {
			    conv = CONV_EXACT ;
			} else {
			    conv = CONV_QUAL ;
			}
		    } else {
			/* Examine base classes */
			GRAPH gr = find_base_class ( cs, ct, 0 ) ;
			if ( !IS_NULL_graph ( gr ) ) {
			    /* Base class conversion */
			    p->base = gr ;
			    conv = CONV_BASE ;
			}
		    }
		}
	    }
	    break ;
	}

	case type_func_tag : {
	    /* Address of overloaded static member function */
	    if ( nt == type_ptr_tag && etag == exp_member_tag ) {
		IDENTIFIER id = DEREF_id ( exp_member_id ( e ) ) ;
		conv = overload_convert_seq ( t, id, p ) ;
	    }
	    break ;
	}

	case type_token_tag : {
	    /* Exact conversion on tokenised type */
	    if ( nt == ns && eq_type_unqual ( t, s ) ) {
		conv = CONV_EXACT ;
	    }
	    break ;
	}
    }
    return ( conv ) ;
}


/*
    CHECK FOR CONVERSION SEQUENCES

    This routine checks whether there is an implicit conversion sequence
    corresponding to p.  e gives the argument being converted.  It returns
    the value indicating the rank of this conversion.  This is used in
    overload resolution to determine the best viable function.
*/

unsigned convert_seq
    PROTO_N ( ( p, e, bind, ref ) )
    PROTO_T ( CONVERSION *p X EXP e X int bind X int ref )
{
    int match = 0 ;
    unsigned conv ;
    TYPE t = p->to ;
    TYPE s = p->from ;
    unsigned nt, ns ;
    CONVERSION user, best ;
    best.rank = CONV_NONE ;

    /* Conversion to the null type counts as exact */
    if ( IS_NULL_type ( t ) ) return ( CONV_EXACT ) ;
    nt = TAG_type ( t ) ;

    /* Conversion from the error type counts as ellipsis */
    ns = TAG_type ( s ) ;
    if ( ns == type_error_tag ) return ( CONV_ELLIPSIS ) ;

    /* Reference conversion */
    if ( ns == type_ref_tag ) {
	s = DEREF_type ( type_ref_sub ( s ) ) ;
	ns = TAG_type ( s ) ;
	if ( ns == type_error_tag ) return ( CONV_ELLIPSIS ) ;
    }

    /* Conversion to class type */
    if ( nt == type_compound_tag && bind != 1 ) {
	IDENTIFIER id ;
	CLASS_TYPE ct = DEREF_ctype ( type_compound_defn ( t ) ) ;
	complete_class ( ct, 1 ) ;
	id = DEREF_id ( ctype_constr ( ct ) ) ;
	if ( ns == type_compound_tag ) {
	    /* Check for base class conversion */
	    conv = std_convert_seq ( p, e, bind, ref ) ;
	    if ( conv != CONV_NONE ) return ( conv ) ;
	    p->from = s ;
	    p->to = t ;
	}
	user.from = s ;
	if ( IS_id_function_etc ( id ) ) {
	    while ( !IS_NULL_id ( id ) ) {
		DECL_SPEC ds = DEREF_dspec ( id_storage ( id ) ) ;
		if ( !( ds & dspec_explicit ) ) {
		    LIST ( TYPE ) q ;
		    TYPE fn = DEREF_type ( id_function_etc_type ( id ) ) ;
		    while ( IS_type_templ ( fn ) ) {
			fn = DEREF_type ( type_templ_defn ( fn ) ) ;
		    }
		    q = DEREF_list ( type_func_ptypes ( fn ) ) ;
		    if ( IS_NULL_list ( q ) ) {
			/* Match with ellipsis */
			int ell = DEREF_int ( type_func_ellipsis ( fn ) ) ;
			if ( ell ) {
			    conv = CONV_ELLIPSIS ;
			} else {
			    conv = CONV_NONE ;
			}
		    } else {
			/* Match with parameter */
			user.to = DEREF_type ( HEAD_list ( q ) ) ;
			if ( min_no_args ( fn ) <= 2 ) {
			    conv = std_convert_seq ( &user, e, bind, 0 ) ;
			} else {
			    conv = CONV_NONE ;
			}
		    }
		    if ( conv != CONV_NONE ) {
			/* Compare against previous conversion */
			if ( !match ) {
			    user.rank = conv ;
			    user.usr = id ;
			    user.std = conv ;
			    best = user ;
			}
			match++ ;
		    }
		}
		id = DEREF_id ( id_function_etc_over ( id ) ) ;
	    }
	}
    }

    /* Conversion from class type */
    if ( ns == type_compound_tag && bind != 1 ) {
	/* Check for user-defined conversions */
	LIST ( IDENTIFIER ) convs ;
	CLASS_TYPE cs = DEREF_ctype ( type_compound_defn ( s ) ) ;
	complete_class ( cs, 1 ) ;
	convs = DEREF_list ( ctype_conv ( cs ) ) ;
	if ( nt == type_ref_tag ) {
	    /* Check for base class conversion */
	    TYPE pt = DEREF_type ( type_ref_sub ( t ) ) ;
	    if ( IS_type_compound ( pt ) ) {
		conv = ref_convert_seq ( p, e, bind, 1 ) ;
		if ( conv != CONV_NONE ) return ( conv ) ;
		p->from = s ;
		p->to = t ;
	    }
	}
	user.to = t ;
	while ( !IS_NULL_list ( convs ) ) {
	    IDENTIFIER id = DEREF_id ( HEAD_list ( convs ) ) ;
	    DECL_SPEC ds = DEREF_dspec ( id_storage ( id ) ) ;
	    if ( !( ds & dspec_explicit ) ) {
		TYPE fn = DEREF_type ( id_function_etc_type ( id ) ) ;
		if ( IS_type_templ ( fn ) ) {
		    /* Allow for template functions */
		    fn = deduce_conv ( fn, t ) ;
		}
		if ( !IS_NULL_type ( fn ) ) {
		    TYPE r = DEREF_type ( type_func_ret ( fn ) ) ;
		    user.from = r ;
		    if ( eq_type ( r, t ) ) {
			conv = CONV_EXACT ;
		    } else {
			conv = std_convert_seq ( &user, e, bind, 0 ) ;
		    }
		    if ( conv != CONV_NONE ) {
			/* Compare against previous conversion */
			if ( !match ) {
			    user.rank = conv ;
			    user.usr = id ;
			    user.std = conv ;
			    best = user ;
			}
			match++ ;
		    }
		}
	    }
	    convs = TAIL_list ( convs ) ;
	}
    }

    /* User-defined conversion sequences */
    if ( match ) {
	*p = best ;
	if ( match == 1 ) return ( CONV_USER ) ;
	return ( CONV_USER_MULTI ) ;
    }

    /* Deal with conversions to reference types */
    if ( nt == type_ref_tag ) {
	conv = ref_convert_seq ( p, e, bind, 0 ) ;
	return ( conv ) ;
    }

    /* Standard conversion sequences */
    conv = std_convert_seq ( p, e, bind, ref ) ;
    return ( conv ) ;
}


/*
    COMPARE TWO BASE CLASS CONVERSIONS

    This routine compares the base classes given by p and q.  It returns 1
    if p is a proper subgraph of q, 2 if q is a proper subgraph of p and
    0 otherwise.
*/

static int base_compare_seq
    PROTO_N ( ( p, q ) )
    PROTO_T ( GRAPH p X GRAPH q )
{
    CLASS_TYPE ct ;
    CLASS_TYPE pa, pb ;
    CLASS_TYPE qa, qb ;

    /* Decompose p into pa > pb */
    pb = DEREF_ctype ( graph_head ( p ) ) ;
    p = DEREF_graph ( graph_top ( p ) ) ;
    pa = DEREF_ctype ( graph_head ( p ) ) ;

    /* Decompose q into qa > qb */
    qb = DEREF_ctype ( graph_head ( q ) ) ;
    q = DEREF_graph ( graph_top ( q ) ) ;
    qa = DEREF_ctype ( graph_head ( q ) ) ;

    if ( eq_ctype ( pa, qa ) ) {
	/* Graph tops are equal, pa = qa */
	if ( eq_ctype ( pb, qb ) ) {
	    /* Graphs are equal */
	    return ( 0 ) ;
	}
	ct = compare_base_class ( pb, qb, 0 ) ;
	if ( EQ_ctype ( ct, pb ) ) {
	    /* pa = qa > qb > pb */
	    return ( 2 ) ;
	}
	if ( EQ_ctype ( ct, qb ) ) {
	    /* pa = qa > pb > qb */
	    return ( 1 ) ;
	}
    } else if ( eq_ctype ( pb, qb ) ) {
	/* Graph bottoms are equal, pb = qb */
	ct = compare_base_class ( pa, qa, 0 ) ;
	if ( EQ_ctype ( ct, pa ) ) {
	    /* qa > pa > pb = qb */
	    return ( 1 ) ;
	}
	if ( EQ_ctype ( ct, qa ) ) {
	    /* pa > qa > pb = qb */
	    return ( 2 ) ;
	}
    }
    return ( 0 ) ;
}


/*
    COMPARE TWO QUALIFICATION CONVERSIONS

    This routine compares the qualification conversions given by p and q.
    It returns 3 if they are identical, 1 if p is better (in that every
    qualifier added by p is also added by q), 2 if q is better, and 0
    otherwise.  When qualifiers are added at only one level it is just
    a matter of comparing the added qualifiers.  If qualifiers are added
    at more than one level a trial conversion is carried out.
*/

static int qual_compare_seq
    PROTO_N ( ( p, q ) )
    PROTO_T ( CONVERSION *p X CONVERSION *q )
{
    CV_SPEC cp = p->qual ;
    CV_SPEC cq = q->qual ;
    if ( cp == cv_multi || cq == cv_multi ) {
	/* Qualifiers at more than one level */
	TYPE t ;
	unsigned cmp ;
	CONVERSION r ;
	if ( EQ_type ( p->from, q->from ) ) {
	    /* Compare to-types */
	    r.from = p->to ;
	    r.to = q->to ;
	} else if ( EQ_type ( p->to, q->to ) ) {
	    /* Compare from-types */
	    r.from = q->from ;
	    r.to = p->from ;
	} else {
	    /* This shouldn't happen */
	    return ( 0 ) ;
	}
	cmp = std_convert_seq ( &r, NULL_exp, 0, 0 ) ;
	if ( cmp == CONV_EXACT ) return ( 3 ) ;
	if ( cmp != CONV_NONE ) return ( 1 ) ;
	t = r.from ;
	r.from = r.to ;
	r.to = t ;
	cmp = std_convert_seq ( &r, NULL_exp, 0, 0 ) ;
	if ( cmp != CONV_NONE ) return ( 2 ) ;
    } else {
	/* Qualifiers at only one level */
	CV_SPEC cr ;
	if ( cp == cq ) return ( 3 ) ;
	cr = ( cp | cq ) ;
	if ( cr == cq ) return ( 1 ) ;
	if ( cr == cp ) return ( 2 ) ;
    }
    return ( 0 ) ;
}


/*
    COMPARE TWO CONVERSION SEQUENCES

    This routine compares the implicit conversion sequences given by
    p1 and p2.  In all cases either the from types of the two conversions
    or the to types will be equal.  The routine is used in determining
    the best viable function in overload resolution, it returns 1 if the
    first conversion is better, 2 if second is better, and some other
    value otherwise.
*/

int compare_seq
    PROTO_N ( ( p1, p2 ) )
    PROTO_T ( CONVERSION *p1 X CONVERSION *p2 )
{
    /* Compare the ranks of the conversions */
    int cmp = 0 ;
    unsigned a1 = p1->rank ;
    unsigned a2 = p2->rank ;
    unsigned b1 = CONV_RANK ( a1 ) ;
    unsigned b2 = CONV_RANK ( a2 ) ;
    if ( b1 > b2 ) return ( 1 ) ;
    if ( b1 < b2 ) return ( 2 ) ;

    /* Check user-defined conversions */
    if ( a1 == CONV_USER && a2 == CONV_USER ) {
	if ( !EQ_id ( p1->usr, p2->usr ) ) return ( 0 ) ;
	a1 = p1->std ;
	a2 = p2->std ;
	b1 = CONV_RANK ( a1 ) ;
	b2 = CONV_RANK ( a2 ) ;
	if ( b1 > b2 ) return ( 1 ) ;
	if ( b1 < b2 ) return ( 2 ) ;
    }

    /* Compare standard conversions */
    switch ( a1 ) {
	case CONV_PTR_BASE : {
	    /* Pointer conversions */
	    if ( a2 == a1 ) {
		/* Compare base pointer conversions */
		GRAPH g1 = p1->base ;
		GRAPH g2 = p2->base ;
		if ( eq_graph ( g1, g2 ) ) {
		    cmp = qual_compare_seq ( p1, p2 ) ;
		} else {
		    cmp = base_compare_seq ( g1, g2 ) ;
		}
	    } else if ( a2 == CONV_PTR_VOID || a2 == CONV_PTR_BOTTOM ) {
		/* Base pointer conversion is better than 'void *' */
		cmp = 1 ;
	    } else if ( a2 == CONV_BOOL ) {
		/* Base pointer conversion is better than 'bool' */
		cmp = 1 ;
	    }
	    break ;
	}
	case CONV_PTR_VOID :
	case CONV_PTR_BOTTOM : {
	    /* Pointer to 'void *' conversions */
	    if ( a2 == CONV_PTR_VOID || a2 == CONV_PTR_BOTTOM ) {
		/* Compare pointer conversions */
		cmp = qual_compare_seq ( p1, p2 ) ;
	    } else if ( a2 == CONV_PTR_BASE ) {
		/* Base pointer conversion is better than 'void *' */
		cmp = 2 ;
	    } else if ( a2 == CONV_BOOL ) {
		/* Pointer conversion is better than 'bool' */
		cmp = 1 ;
	    }
	    break ;
	}
	case CONV_PTR_MEM_BASE : {
	    /* Pointer member conversions */
	    if ( a2 == a1 ) {
		/* Compare base pointer member conversions */
		GRAPH g1 = p1->base ;
		GRAPH g2 = p2->base ;
		if ( eq_graph ( g1, g2 ) ) {
		    cmp = qual_compare_seq ( p1, p2 ) ;
		} else {
		    int bmp = base_compare_seq ( g1, g2 ) ;
		    if ( bmp ) {
			cmp = qual_compare_seq ( p1, p2 ) ;
			switch ( cmp ) {
			    case 1 : {
				if ( bmp != 2 ) cmp = 0 ;
				break ;
			    }
			    case 2 : {
				if ( bmp != 1 ) cmp = 0 ;
				break ;
			    }
			    case 3 : {
				cmp = bmp ;
				break ;
			    }
			}
		    }
		}
	    } else if ( a2 == CONV_BOOL ) {
		/* Pointer conversion is better than 'bool' */
		cmp = 1 ;
	    }
	    break ;
	}
	case CONV_BASE : {
	    /* Base class conversions */
	    if ( a2 == a1 ) {
		/* Compare base class conversions */
		GRAPH g1 = p1->base ;
		GRAPH g2 = p2->base ;
		if ( eq_graph ( g1, g2 ) ) {
		    cmp = qual_compare_seq ( p1, p2 ) ;
		} else {
		    cmp = base_compare_seq ( g1, g2 ) ;
		}
	    }
	    break ;
	}
	case CONV_BOOL : {
	    /* Boolean conversions */
	    if ( a2 == CONV_PTR_BASE || a2 == CONV_PTR_MEM_BASE ||
		 a2 == CONV_PTR_VOID || a2 == CONV_PTR_BOTTOM ) {
		/* Pointer conversion is better than 'bool' */
		cmp = 2 ;
	    }
	    break ;
	}
	case CONV_STRING : {
	    /* String literal conversions */
	    if ( a2 == a1 ) {
		cmp = qual_compare_seq ( p1, p2 ) ;
	    } else if ( a2 == CONV_QUAL ) {
		/* Qualification conversion is better than string */
		cmp = 2 ;
	    }
	    break ;
	}
	case CONV_QUAL : {
	    /* Qualification conversions */
	    if ( a2 == a1 ) {
		cmp = qual_compare_seq ( p1, p2 ) ;
	    } else if ( a2 == CONV_STRING ) {
		/* Qualification conversion is better than string */
		cmp = 1 ;
	    }
	    break ;
	}
    }
    return ( cmp ) ;
}
