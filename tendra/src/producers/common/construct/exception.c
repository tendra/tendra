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
#include "exp_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "tok_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "option.h"
#include "allocate.h"
#include "basetype.h"
#include "cast.h"
#include "chktype.h"
#include "class.h"
#include "construct.h"
#include "convert.h"
#include "declare.h"
#include "derive.h"
#include "destroy.h"
#include "exception.h"
#include "expression.h"
#include "file.h"
#include "function.h"
#include "hash.h"
#include "identifier.h"
#include "initialise.h"
#include "label.h"
#include "namespace.h"
#include "predict.h"
#include "redeclare.h"
#include "statement.h"
#include "syntax.h"
#include "template.h"
#include "tokdef.h"
#include "typeid.h"


/*
    THE SET OF ALL TYPES

    The dummy list univ_type_set is used to represent the set of all
    types.  These sets of types are used to represent exception
    specifications for functions.  The list empty_type_set is used to
    give the exception specification for a function when none is given,
    by default it equals univ_type_set.
*/

LIST ( TYPE ) univ_type_set = NULL_list ( TYPE ) ;
LIST ( TYPE ) empty_type_set = NULL_list ( TYPE ) ;


/*
    INITIALISE THE SET OF ALL TYPES

    This routine initialises the set of all types to a dummy unique list.
*/

void init_exception
    PROTO_Z ()
{
    LIST ( TYPE ) p ;
    CONS_type ( type_any, NULL_list ( TYPE ), p ) ;
    p = uniq_type_set ( p ) ;
    COPY_list ( type_func_except ( type_func_void ), p ) ;
    COPY_list ( type_func_except ( type_temp_func ), p ) ;
    empty_type_set = p ;
    univ_type_set = p ;
    return ;
}


/*
    IS A TYPE IN A SET OF TYPES?

    This routine checks whether the type t is an element of the set of
    types listed as p.
*/

int in_type_set
    PROTO_N ( ( p, t ) )
    PROTO_T ( LIST ( TYPE ) p X TYPE t )
{
    if ( EQ_list ( p, univ_type_set ) ) return ( 1 ) ;
    expand_tokdef++ ;
    while ( !IS_NULL_list ( p ) ) {
	TYPE s = DEREF_type ( HEAD_list ( p ) ) ;
	if ( EQ_type ( t, s ) || eq_type_unqual ( t, s ) ) {
	    expand_tokdef-- ;
	    return ( 1 ) ;
	}
	p = TAIL_list ( p ) ;
    }
    expand_tokdef-- ;
    return ( 0 ) ;
}


/*
    IS A TYPE DERIVABLE FROM A SET OF TYPES?

    This routine checks whether an exception of type t will be caught by
    an element of the set of types listed as p.  It returns the catching
    type, or the null type if no match is found.
*/

static TYPE from_type_set
    PROTO_N ( ( p, t ) )
    PROTO_T ( LIST ( TYPE ) p X TYPE t )
{
    if ( EQ_list ( p, univ_type_set ) ) {
	/* The universal set catches everything */
	return ( t ) ;
    }
    expand_tokdef++ ;
    if ( IS_type_ref ( t ) ) t = DEREF_type ( type_ref_sub ( t ) ) ;
    while ( !IS_NULL_list ( p ) ) {
	TYPE r = DEREF_type ( HEAD_list ( p ) ) ;
	if ( !IS_NULL_type ( r ) ) {
	    TYPE s = r ;
	    unsigned rank ;
	    CONVERSION conv ;
	    if ( IS_type_ref ( s ) ) s = DEREF_type ( type_ref_sub ( s ) ) ;
	    if ( eq_type_unqual ( t, s ) ) {
		/* Exact match is allowed */
		expand_tokdef-- ;
		return ( r ) ;
	    }
	    conv.from = t ;
	    conv.to = s ;
	    rank = std_convert_seq ( &conv, NULL_exp, 0, 0 ) ;
	    switch ( rank ) {
		case CONV_EXACT :
		case CONV_QUAL :
		case CONV_BASE :
		case CONV_PTR_BASE :
		case CONV_PTR_VOID :
		case CONV_PTR_BOTTOM : {
		    /* These conversions are allowed */
		    expand_tokdef-- ;
		    return ( r ) ;
		}
	    }
	}
	p = TAIL_list ( p ) ;
    }
    expand_tokdef-- ;
    return ( NULL_type ) ;
}


/*
    ARE TWO TYPE SETS EQUAL?

    This routine checks whether the sets of types listed as p and q are
    equal.  It returns 2 if they are equal, 1 if p is a subset of q, and
    0 otherwise.  Because p and q will have been constructed not to contain
    duplicate elements a fair amount can be deduced from the cardinalities
    of the sets, also the search is optimised if the types are given in
    the same order in each set.  If eq is true then only equality is
    checked for.
*/

int eq_type_set
    PROTO_N ( ( p, q, eq ) )
    PROTO_T ( LIST ( TYPE ) p X LIST ( TYPE ) q X int eq )
{
    unsigned n, m ;
    LIST ( TYPE ) r ;

    /* Deal with the set of all types */
    if ( EQ_list ( p, q ) ) return ( 2 ) ;
    if ( EQ_list ( q, univ_type_set ) && !eq ) return ( 1 ) ;
    if ( EQ_list ( p, univ_type_set ) ) return ( 0 ) ;

    /* Check whether p is larger than q */
    n = LENGTH_list ( p ) ;
    m = LENGTH_list ( q ) ;
    if ( n > m ) return ( 0 ) ;
    if ( n < m && eq ) return ( 0 ) ;

    /* Check whether p is a subset of q */
    r = q ;
    while ( !IS_NULL_list ( p ) ) {
	TYPE t = DEREF_type ( HEAD_list ( p ) ) ;
	TYPE s = DEREF_type ( HEAD_list ( r ) ) ;
	if ( !EQ_type ( t, s ) && !eq_type_unqual ( t, s ) ) {
	    if ( !in_type_set ( q, t ) ) return ( 0 ) ;
	}
	r = TAIL_list ( r ) ;
	p = TAIL_list ( p ) ;
    }

    /* Check for equality using set sizes */
    if ( n < m ) return ( 1 ) ;
    return ( 2 ) ;
}


/*
    ADD AN ELEMENT TO A TYPE SET

    This routine adds the type t to the type set p if it is not already
    a member.
*/

LIST ( TYPE ) cons_type_set
    PROTO_N ( ( p, t ) )
    PROTO_T ( LIST ( TYPE ) p X TYPE t )
{
    if ( !IS_NULL_type ( t ) && !in_type_set ( p, t ) ) {
	CONS_type ( t, p, p ) ;
    }
    return ( p ) ;
}


/*
    FIND THE UNION OF TWO TYPE SETS

    This routine adds the elements of the type set q to the type set p.
*/

LIST ( TYPE ) union_type_set
    PROTO_N ( ( p, q ) )
    PROTO_T ( LIST ( TYPE ) p X LIST ( TYPE ) q )
{
    if ( !EQ_list ( p, univ_type_set ) ) {
	if ( EQ_list ( q, univ_type_set ) ) {
	    DESTROY_list ( p, SIZE_type ) ;
	    p = q ;
	} else {
	    while ( !IS_NULL_list ( q ) ) {
		TYPE t = DEREF_type ( HEAD_list ( q ) ) ;
		if ( !IS_NULL_type ( t ) ) {
		    if ( !in_type_set ( p, t ) ) CONS_type ( t, p, p ) ;
		}
		q = TAIL_list ( q ) ;
	    }
	}
    }
    return ( p ) ;
}


/*
    MAKE A UNIQUE COPY OF A TYPE SET

    This routine maintains a list of type sets.  If p equals an element of
    this list then the copy is returned and p is destroyed.  Otherwise p
    is added to the list.
*/

LIST ( TYPE ) uniq_type_set
    PROTO_N ( ( p ) )
    PROTO_T ( LIST ( TYPE ) p )
{
    static LIST ( LIST ( TYPE ) ) sets = NULL_list ( LIST ( TYPE ) ) ;
    LIST ( LIST ( TYPE ) ) s = sets ;
    while ( !IS_NULL_list ( s ) ) {
	LIST ( TYPE ) q = DEREF_list ( HEAD_list ( s ) ) ;
	if ( eq_type_set ( p, q, 1 ) == 2 ) {
	    DESTROY_list ( p, SIZE_type ) ;
	    return ( q ) ;
	}
	s = TAIL_list ( s ) ;
    }
    CONS_list ( p, sets, sets ) ;
    return ( p ) ;
}


/*
    COMPARE THE EXCEPTION SPECIFIERS OF TWO TYPES

    This routine compares the exception specifiers of the similar types
    s and t.  It returns 2 if they are equal, 1 if s is more constrained
    than t, and 0 otherwise.
*/

int eq_except
    PROTO_N ( ( s, t ) )
    PROTO_T ( TYPE s X TYPE t )
{
    unsigned ns, nt ;
    if ( EQ_type ( s, t ) ) return ( 2 ) ;
    if ( IS_NULL_type ( s ) ) return ( 0 ) ;
    if ( IS_NULL_type ( t ) ) return ( 0 ) ;
    ns = TAG_type ( s ) ;
    nt = TAG_type ( t ) ;
    if ( ns != nt ) return ( 2 ) ;
    ASSERT ( ORDER_type == 18 ) ;
    switch ( ns ) {

	case type_func_tag : {
	    /* Function types */
	    LIST ( TYPE ) es = DEREF_list ( type_func_except ( s ) ) ;
	    LIST ( TYPE ) et = DEREF_list ( type_func_except ( t ) ) ;
	    int eq = eq_type_set ( es, et, 0 ) ;
	    if ( eq ) {
		TYPE rs, rt ;
		LIST ( TYPE ) ps = DEREF_list ( type_func_ptypes ( s ) ) ;
		LIST ( TYPE ) pt = DEREF_list ( type_func_ptypes ( t ) ) ;
		while ( !IS_NULL_list ( ps ) && !IS_NULL_list ( pt ) ) {
		    rs = DEREF_type ( HEAD_list ( ps ) ) ;
		    rt = DEREF_type ( HEAD_list ( pt ) ) ;
		    if ( eq_except ( rs, rt ) != 2 ) return ( 0 ) ;
		    pt = TAIL_list ( pt ) ;
		    ps = TAIL_list ( ps ) ;
		}
		rs = DEREF_type ( type_func_ret ( s ) ) ;
		rt = DEREF_type ( type_func_ret ( t ) ) ;
		if ( eq_except ( rs, rt ) != 2 ) return ( 0 ) ;
	    }
	    return ( eq ) ;
	}

	case type_ptr_tag :
	case type_ref_tag : {
	    /* Pointer and reference types */
	    TYPE ps = DEREF_type ( type_ptr_etc_sub ( s ) ) ;
	    TYPE pt = DEREF_type ( type_ptr_etc_sub ( t ) ) ;
	    return ( eq_except ( ps, pt ) ) ;
	}

	case type_ptr_mem_tag : {
	    /* Pointer to member types */
	    TYPE ps = DEREF_type ( type_ptr_mem_sub ( s ) ) ;
	    TYPE pt = DEREF_type ( type_ptr_mem_sub ( t ) ) ;
	    return ( eq_except ( ps, pt ) ) ;
	}

	case type_array_tag : {
	    /* Array types */
	    TYPE ps = DEREF_type ( type_array_sub ( s ) ) ;
	    TYPE pt = DEREF_type ( type_array_sub ( t ) ) ;
	    return ( eq_except ( ps, pt ) ) ;
	}

	case type_templ_tag : {
	    /* Template types */
	    TOKEN as = DEREF_tok ( type_templ_sort ( s ) ) ;
	    TOKEN at = DEREF_tok ( type_templ_sort ( t ) ) ;
	    LIST ( IDENTIFIER ) qs = DEREF_list ( tok_templ_pids ( as ) ) ;
	    LIST ( IDENTIFIER ) qt = DEREF_list ( tok_templ_pids ( at ) ) ;
	    int eq = eq_templ_params ( qs, qt ) ;
	    if ( eq ) {
		TYPE ps = DEREF_type ( type_templ_defn ( s ) ) ;
		TYPE pt = DEREF_type ( type_templ_defn ( t ) ) ;
		eq = eq_except ( ps, pt ) ;
	    }
	    restore_templ_params ( qs ) ;
	    return ( eq ) ;
	}
    }
    return ( 2 ) ;
}


/*
    CREATE AN EXCEPTION TYPE

    This routine converts the exception type t to its primary form.
    Reference types are replaced by the referenced type and any top level
    type qualifiers are removed.  chk gives the context for the conversion,
    1 for a throw expression, 2 for a catch statement, 3 for an exception
    specifier and 0 otherwise.
*/

TYPE exception_type
    PROTO_N ( ( t, chk ) )
    PROTO_T ( TYPE t X int chk )
{
    if ( !IS_NULL_type ( t ) ) {
	unsigned tag = TAG_type ( t ) ;
	if ( tag == type_ref_tag ) {
	    t = DEREF_type ( type_ref_sub ( t ) ) ;
	    tag = TAG_type ( t ) ;
	}
	t = qualify_type ( t, cv_none, 0 ) ;
	if ( chk ) {
	    /* Check exception type */
	    TYPE s = t ;
	    if ( tag == type_ptr_tag ) {
		s = DEREF_type ( type_ptr_sub ( s ) ) ;
		tag = TAG_type ( s ) ;
	    }
	    if ( tag == type_compound_tag ) {
		ERROR err = check_incomplete ( s ) ;
		if ( !IS_NULL_err ( err ) ) {
		    /* Can't have an incomplete class */
		    ERROR err2 = NULL_err ;
		    switch ( chk ) {
			case 1 : err2 = ERR_except_throw_incompl () ; break ;
			case 2 : err2 = ERR_except_handle_incompl () ; break ;
			case 3 : err2 = ERR_except_spec_incompl () ; break ;
		    }
		    err = concat_error ( err, err2 ) ;
		    report ( crt_loc, err ) ;
		}
		if ( chk == 1 ) {
		    /* Can't throw a type with an ambiguous base */
		    CLASS_TYPE cs = DEREF_ctype ( type_compound_defn ( s ) ) ;
		    err = class_info ( cs, cinfo_ambiguous, 1 ) ;
		    if ( !IS_NULL_err ( err ) ) {
			ERROR err2 = ERR_except_throw_ambig () ;
			err = concat_error ( err, err2 ) ;
			report ( crt_loc, err ) ;
		    }
		}
	    }
	}
    }
    return ( t ) ;
}


/*
    CHECK AN EXCEPTION SPECIFIER TYPE

    This routine checks the type t, which forms part of an exception
    specification for a function.  The argument n gives the number of types
    defined in t.
*/

TYPE check_except_type
    PROTO_N ( ( t, n ) )
    PROTO_T ( TYPE t X int n )
{
    if ( n ) report ( crt_loc, ERR_except_spec_typedef () ) ;
    IGNORE exception_type ( t, 3 ) ;
    return ( t ) ;
}


/*
    STACK OF CURRENTLY ACTIVE TRY BLOCKS

    The stack crt_try_block is used to hold all the currently active try
    blocks and exception handlers.  The flag in_func_handler is set to
    1 (or 2 for constructors and destructors) in the handler of a function
    try block.
*/

STACK ( EXP ) crt_try_blocks = NULL_stack ( EXP ) ;
static STACK ( STACK ( EXP ) ) past_try_blocks = NULL_stack ( STACK ( EXP ) ) ;
int in_func_handler = 0 ;


/*
    CHECK A THROWN TYPE

    This routine checks the type t thrown from an explicit throw expression
    (if expl is true) or a function call.  The null type is used to
    indicate an unknown type.  The routine returns true if the exception
    is caught by an enclosing handler.
*/

int check_throw
    PROTO_N ( ( t, expl ) )
    PROTO_T ( TYPE t X int expl )
{
    IDENTIFIER fn ;
    LIST ( EXP ) p = LIST_stack ( crt_try_blocks ) ;
    while ( !IS_NULL_list ( p ) ) {
	EXP e = DEREF_exp ( HEAD_list ( p ) ) ;
	if ( IS_exp_try_block ( e ) ) {
	    /* Add to list of thrown types */
	    LIST ( TYPE ) q ;
	    q = DEREF_list ( exp_try_block_ttypes ( e ) ) ;
	    if ( !EQ_list ( q, univ_type_set ) ) {
		LIST ( LOCATION ) ql ;
		ql = DEREF_list ( exp_try_block_tlocs ( e ) ) ;
		if ( IS_NULL_type ( t ) ) {
		    DESTROY_list ( q, SIZE_type ) ;
		    DESTROY_list ( ql, SIZE_loc ) ;
		    q = univ_type_set ;
		    ql = NULL_list ( LOCATION ) ;
		    CONS_loc ( crt_loc, ql, ql ) ;
		} else {
		    if ( !in_type_set ( q, t ) ) {
			CONS_type ( t, q, q ) ;
			CONS_loc ( crt_loc, ql, ql ) ;
		    }
		}
		COPY_list ( exp_try_block_ttypes ( e ), q ) ;
		COPY_list ( exp_try_block_tlocs ( e ), ql ) ;
	    }
	    return ( 1 ) ;
	}
	if ( IS_NULL_type ( t ) && expl && IS_exp_handler ( e ) ) {
	    /* Can deduce type of 'throw' inside a handler */
	    IDENTIFIER ex = DEREF_id ( exp_handler_except ( e ) ) ;
	    if ( !IS_NULL_id ( ex ) ) {
		t = DEREF_type ( id_variable_etc_type ( ex ) ) ;
		t = exception_type ( t, 0 ) ;
	    }
	}
	p = TAIL_list ( p ) ;
    }

    /* Exception not caught by any try block */
    fn = crt_func_id ;
    if ( IS_NULL_type ( t ) ) t = type_any ;
    if ( IS_NULL_id ( fn ) ) {
	report ( crt_loc, ERR_except_spec_throw ( t ) ) ;
    } else {
	report ( crt_loc, ERR_except_spec_call ( fn, t ) ) ;
    }
    return ( 0 ) ;
}


/*
    CHECK THE EXCEPTIONS THROWN IN A TRY BLOCK

    This routine checks the exceptions thrown in the try block e.  Any
    which are not caught by the handlers of e are passed to the enclosing
    block or reported if this is the outermost block.  The routine
    returns true if all the exceptions are handled by an enclosing block.
*/

int check_try_block
    PROTO_N ( ( e ) )
    PROTO_T ( EXP e )
{
    int res = 1 ;
    if ( IS_exp_try_block ( e ) ) {
	LOCATION loc ;
	LIST ( LOCATION ) ql ;
	LIST ( TYPE ) p = DEREF_list ( exp_try_block_htypes ( e ) ) ;
	LIST ( TYPE ) q = DEREF_list ( exp_try_block_ttypes ( e ) ) ;
	EXP a = DEREF_exp ( exp_try_block_ellipsis ( e ) ) ;
	if ( EQ_list ( p, univ_type_set ) ) {
	    /* Have handlers for any type */
	    return ( 1 ) ;
	}
	if ( !IS_NULL_exp ( a ) && IS_exp_handler ( a ) ) {
	    /* Have a ... handler */
	    return ( 1 ) ;
	}
	bad_crt_loc++ ;
	loc = crt_loc ;
	ql = DEREF_list ( exp_try_block_tlocs ( e ) ) ;
	if ( EQ_list ( q, univ_type_set ) ) {
	    /* Can throw any type */
	    DEREF_loc ( HEAD_list ( ql ), crt_loc ) ;
	    res = check_throw ( NULL_type, 0 ) ;
	} else {
	    /* Can throw a finite set of types */
	    q = REVERSE_list ( q ) ;
	    ql = REVERSE_list ( ql ) ;
	    COPY_list ( exp_try_block_ttypes ( e ), q ) ;
	    COPY_list ( exp_try_block_tlocs ( e ), ql ) ;
	    while ( !IS_NULL_list ( q ) ) {
		TYPE t = DEREF_type ( HEAD_list ( q ) ) ;
		TYPE u = from_type_set ( p, t ) ;
		if ( IS_NULL_type ( u ) ) {
		    /* Throw uncaught type to enclosing block */
		    DEREF_loc ( HEAD_list ( ql ), crt_loc ) ;
		    if ( !check_throw ( t, 0 ) ) res = 0 ;
		}
		ql = TAIL_list ( ql ) ;
		q = TAIL_list ( q ) ;
	    }
	}
	crt_loc = loc ;
	bad_crt_loc-- ;
    }
    return ( res ) ;
}


/*
    CHECK THE EXCEPTIONS THROWN BY A FUNCTION CALL

    This routine checks the possible exceptions thrown by a call to a
    function of type fn.  When known the function name is given by fid.
    The routine returns true if the exception is handled by an enclosing
    try-block.
*/

int check_func_throw
    PROTO_N ( ( fn, fid ) )
    PROTO_T ( TYPE fn X IDENTIFIER fid )
{
    int res = 1 ;
    if ( IS_type_func ( fn ) ) {
	LIST ( TYPE ) p = DEREF_list ( type_func_except ( fn ) ) ;
	if ( IS_NULL_list ( p ) ) return ( 1 ) ;
	if ( EQ_list ( p, univ_type_set ) ) {
	    /* Can throw any type */
	    res = check_throw ( NULL_type, 0 ) ;
	} else {
	    /* Can throw a finite set of types */
	    while ( !IS_NULL_list ( p ) ) {
		TYPE t = DEREF_type ( HEAD_list ( p ) ) ;
		if ( !IS_NULL_type ( t ) ) {
		    if ( !check_throw ( t, 0 ) ) res = 0 ;
		}
		p = TAIL_list ( p ) ;
	    }
	}
    } else {
	res = check_throw ( NULL_type, 0 ) ;
    }
    UNUSED ( fid ) ;
    return ( res ) ;
}


/*
    START THE EXCEPTION CHECKS FOR A FUNCTION DEFINITION

    This routine starts the exception specification checks for a function
    which throws the types p.
*/

void start_try_check
    PROTO_N ( ( p ) )
    PROTO_T ( LIST ( TYPE ) p )
{
    EXP e ;
    MAKE_exp_try_block ( type_void, NULL_exp, 0, e ) ;
    COPY_list ( exp_try_block_htypes ( e ), p ) ;
    PUSH_stack ( crt_try_blocks, past_try_blocks ) ;
    crt_try_blocks = NULL_stack ( EXP ) ;
    PUSH_exp ( e, crt_try_blocks ) ;
    return ;
}


/*
    END THE EXCEPTION CHECKS FOR A FUNCTION DEFINITION

    This routine ends the exception specification checks for the function
    id with definition a.
*/

EXP end_try_check
    PROTO_N ( ( id, a ) )
    PROTO_T ( IDENTIFIER id X EXP a )
{
    EXP e ;
    POP_exp ( e, crt_try_blocks ) ;
    POP_stack ( crt_try_blocks, past_try_blocks ) ;
    if ( !IS_NULL_exp ( e ) && IS_exp_try_block ( e ) ) {
	IDENTIFIER fid = crt_func_id ;
	crt_func_id = id ;
	IGNORE check_try_block ( e ) ;
	if ( EQ_id ( fid, id ) ) {
	    LIST ( TYPE ) p = DEREF_list ( exp_try_block_ttypes ( e ) ) ;
	    if ( IS_NULL_list ( p ) && !in_template_decl ) {
		/* Function can't throw an exception */
		DECL_SPEC ds = DEREF_dspec ( id_storage ( id ) ) ;
		ds |= dspec_friend ;
		COPY_dspec ( id_storage ( id ), ds ) ;
	    }
	}
	COPY_list ( exp_try_block_htypes ( e ), NULL_list ( TYPE ) ) ;
	free_exp ( e, 1 ) ;
	crt_func_id = fid ;
    }
    return ( a ) ;
}


/*
    EXCEPTION HANDLING ROUTINES

    The exception handling routines are only included in the C++ producer.
*/

#if LANGUAGE_CPP


/*
    BEGIN THE CONSTRUCTION OF A TRY STATEMENT

    This routine begins the construction of the statement 'try { body }
    handlers'.  It is called immediately after the 'try'.  func is true
    for a function-try-block.
*/

EXP begin_try_stmt
    PROTO_N ( ( func ) )
    PROTO_T ( int func )
{
    EXP e ;
    if ( func ) {
	/* Check function try blocks */
	IDENTIFIER fn = crt_func_id ;
	if ( !IS_NULL_id ( fn ) ) {
	    HASHID nm = DEREF_hashid ( id_name ( fn ) ) ;
	    unsigned tag = TAG_hashid ( nm ) ;
	    if ( tag == hashid_constr_tag || tag == hashid_destr_tag ) {
		/* Constructors and destructors are marked */
		func = 2 ;
	    }
	} else {
	    func = 0 ;
	}
    }
    MAKE_exp_try_block ( type_void, NULL_exp, func, e ) ;
    CONS_exp ( e, all_try_blocks, all_try_blocks ) ;
    PUSH_exp ( e, crt_try_blocks ) ;
    return ( e ) ;
}


/*
    INJECT FUNCTION PARAMETERS INTO A HANDLER

    It is not allowed to redeclare a function parameter in the body or
    the handler of a function-try-block.  This routine ensures this by
    injecting the function parameters into the current scope when prev
    is a function-try-block.
*/

void inject_try_stmt
    PROTO_N ( ( prev ) )
    PROTO_T ( EXP prev )
{
    int func = DEREF_int ( exp_try_block_func ( prev ) ) ;
    if ( func ) {
	IDENTIFIER id = crt_func_id ;
	if ( !IS_NULL_id ( id ) && IS_id_function_etc ( id ) ) {
	    LIST ( IDENTIFIER ) pids ;
	    NAMESPACE ns = crt_namespace ;
	    TYPE t = DEREF_type ( id_function_etc_type ( id ) ) ;
	    while ( IS_type_templ ( t ) ) {
		t = DEREF_type ( type_templ_defn ( t ) ) ;
	    }
	    pids = DEREF_list ( type_func_pids ( t ) ) ;
	    while ( !IS_NULL_list ( pids ) ) {
		IDENTIFIER pid = DEREF_id ( HEAD_list ( pids ) ) ;
		IGNORE redeclare_id ( ns, pid ) ;
		pids = TAIL_list ( pids ) ;
	    }
	}
    }
    return ;
}


/*
    CONTINUE THE CONSTRUCTION OF A TRY STATEMENT

    This routine continues the contruction of the try statement prev by
    filling in the given body statement.
*/

EXP cont_try_stmt
    PROTO_N ( ( prev, body ) )
    PROTO_T ( EXP prev X EXP body )
{
    EXP e ;
    int func = DEREF_int ( exp_try_block_func ( prev ) ) ;
    if ( func ) in_func_handler = func ;
    COPY_exp ( exp_try_block_body ( prev ), body ) ;
    set_parent_stmt ( body, prev ) ;
    POP_exp ( e, crt_try_blocks ) ;
    UNUSED ( e ) ;
    return ( prev ) ;
}


/*
    COMPLETE THE CONSTRUCTION OF A TRY STATEMENT

    This routine completes the contruction of the try statement prev.  It
    checks whether it contains at least one handler and determines the
    reachability of the following statement.
*/

EXP end_try_stmt
    PROTO_N ( ( prev, empty ) )
    PROTO_T ( EXP prev X int empty )
{
    EXP e ;
    TYPE t ;
    int all_bottom = 1 ;
    int func = DEREF_int ( exp_try_block_func ( prev ) ) ;

    /* Check handler list */
    EXP ell = DEREF_exp ( exp_try_block_ellipsis ( prev ) ) ;
    LIST ( EXP ) hs = DEREF_list ( exp_try_block_handlers ( prev ) ) ;
    LIST ( TYPE ) ps = DEREF_list ( exp_try_block_ttypes ( prev ) ) ;
    unsigned nh = LENGTH_list ( hs ) ;
    if ( IS_NULL_exp ( ell ) ) {
	/* Create default handler if necessary */
	if ( IS_NULL_list ( hs ) && !empty ) {
	    /* Check that there is at least one handler */
	    report ( crt_loc, ERR_except_handlers () ) ;
	}
	MAKE_exp_exception ( type_bottom, ell, NULL_exp, NULL_exp, 0, ell ) ;
	COPY_exp ( exp_try_block_ellipsis ( prev ), ell ) ;
    } else {
	nh++ ;
    }
    IGNORE check_value ( OPT_VAL_exception_handlers, ( ulong ) nh ) ;

    /* Do unreached code analysis */
    e = DEREF_exp ( exp_try_block_body ( prev ) ) ;
    t = DEREF_type ( exp_type ( e ) ) ;
    if ( IS_type_bottom ( t ) ) {
	/* Don't reach end of try block */
	t = DEREF_type ( exp_type ( ell ) ) ;
	if ( !IS_type_bottom ( t ) ) all_bottom = 0 ;
	while ( !IS_NULL_list ( hs ) && all_bottom ) {
	    /* Check the other handlers */
	    e = DEREF_exp ( HEAD_list ( hs ) ) ;
	    t = DEREF_type ( exp_type ( e ) ) ;
	    if ( !IS_type_bottom ( t ) ) all_bottom = 0 ;
	    hs = TAIL_list ( hs ) ;
	}
    } else {
	/* Reach end of try block */
	all_bottom = 0 ;
    }
    if ( all_bottom ) {
	COPY_type ( exp_type ( prev ), type_bottom ) ;
	unreached_code = 1 ;
	unreached_last = 0 ;
    } else {
	unreached_code = unreached_prev ;
    }
    if ( IS_NULL_list ( ps ) && !empty && !in_template_decl ) {
	report ( crt_loc, ERR_except_not () ) ;
    }
    if ( func ) in_func_handler = 0 ;
    IGNORE check_try_block ( prev ) ;
    return ( prev ) ;
}


/*
    MARK ALL VARIABLES ENCLOSING A TRY BLOCK

    This routine marks all the local variables of the function id which
    contain a try block within their scope.
*/

void end_try_blocks
    PROTO_N ( ( id ) )
    PROTO_T ( IDENTIFIER id )
{
    LIST ( EXP ) p = all_try_blocks ;
    if ( !IS_NULL_list ( p ) ) {
	if ( !IS_NULL_id ( id ) ) {
	    /* Mark function */
	    DECL_SPEC ds = DEREF_dspec ( id_storage ( id ) ) ;
	    ds |= dspec_mutable ;
	    COPY_dspec ( id_storage ( id ), ds ) ;
	}
	while ( !IS_NULL_list ( p ) ) {
	    EXP a = DEREF_exp ( HEAD_list ( p ) ) ;
	    while ( !IS_NULL_exp ( a ) ) {
		if ( IS_exp_decl_stmt ( a ) ) {
		    IDENTIFIER pid = DEREF_id ( exp_decl_stmt_id ( a ) ) ;
		    DECL_SPEC ds = DEREF_dspec ( id_storage ( pid ) ) ;
		    if ( ds & dspec_auto ) {
			/* Mark local variable */
			ds |= dspec_mutable ;
			COPY_dspec ( id_storage ( pid ), ds ) ;
		    }
		}
		a = get_parent_stmt ( a ) ;
	    }
	    p = TAIL_list ( p ) ;
	}
    }
    return ;
}


/*
    DECLARE AN EXCEPTION HANDLER

    This routine declares an exception handler named id with type t and
    declaration specifiers ds (which should always be empty).  n gives
    the number of types defined in t.
*/

IDENTIFIER make_except_decl
    PROTO_N ( ( ds, t, id, n ) )
    PROTO_T ( DECL_SPEC ds X TYPE t X IDENTIFIER id X int n )
{
    /* Declare id as a local variable */
    EXP e ;
    if ( crt_id_qualifier == qual_nested || crt_templ_qualifier ) {
	/* Other illegal identifiers are caught elsewhere */
	report ( crt_loc, ERR_dcl_meaning_id ( qual_nested, id ) ) ;
    }
    if ( n ) report ( crt_loc, ERR_except_handle_typedef () ) ;
    t = make_param_type ( t, CONTEXT_PARAMETER ) ;
    id = make_object_decl ( ds, t, id, 0 ) ;

    /* The initialising value is the current exception */
    if ( IS_type_ref ( t ) ) {
	t = DEREF_type ( type_ref_sub ( t ) ) ;
    }
    t = lvalue_type ( t ) ;
    MAKE_exp_thrown ( t, 0, e ) ;
    IGNORE init_object ( id, e ) ;
    return ( id ) ;
}


/*
    BEGIN THE CONSTRUCTION OF A CATCH STATEMENT

    This routine begins the construction of the handler 'catch ( ex )
    { body }' associated with the try block block.  It is called after the
    declaration of ex.  Note that ex can be the null identifier, indicating
    that the handler is '...'.
*/

EXP begin_catch_stmt
    PROTO_N ( ( block, ex ) )
    PROTO_T ( EXP block X IDENTIFIER ex )
{
    /* Construct the result */
    EXP e, d ;
    MAKE_exp_handler ( type_void, ex, NULL_exp, e ) ;
    COPY_exp ( exp_handler_parent ( e ), block ) ;
    unreached_code = 0 ;
    unreached_last = 0 ;

    /* Check for '...' handlers */
    d = DEREF_exp ( exp_try_block_ellipsis ( block ) ) ;
    if ( !IS_NULL_exp ( d ) ) {
	/* Already have a '...' handler */
	report ( crt_loc, ERR_except_handle_ellipsis () ) ;
	unreached_code = 1 ;
    } else if ( IS_NULL_id ( ex ) ) {
	/* Set the '...' handler if necessary */
	COPY_exp ( exp_try_block_ellipsis ( block ), e ) ;
    } else {
	/* Add to list of other handlers */
	TYPE t0 ;
	TYPE t, s ;
	LIST ( EXP ) p, q ;
	LIST ( TYPE ) u, v ;

	/* Check list of handler types */
	u = DEREF_list ( exp_try_block_htypes ( block ) ) ;
	t0 = DEREF_type ( id_variable_etc_type ( ex ) ) ;
	t = exception_type ( t0, 2 ) ;
	s = from_type_set ( u, t ) ;
	if ( !IS_NULL_type ( s ) ) {
	    report ( crt_loc, ERR_except_handle_unreach ( t0, s ) ) ;
	    unreached_code = 1 ;
	}
	CONS_type ( t, NULL_list ( TYPE ), v ) ;
	u = APPEND_list ( u, v ) ;
	COPY_list ( exp_try_block_htypes ( block ), u ) ;

	/* Add ex to list of handler expressions */
	p = DEREF_list ( exp_try_block_handlers ( block ) ) ;
	CONS_exp ( e, NULL_list ( EXP ), q ) ;
	p = APPEND_list ( p, q ) ;
	COPY_list ( exp_try_block_handlers ( block ), p ) ;
    }
    PUSH_exp ( e, crt_try_blocks ) ;
    return ( e ) ;
}


/*
    COMPLETE THE CONSTRUCTION OF A CATCH STATEMENT

    This routine completes the construction of the catch statement prev by
    filling in the given body statement.
*/

EXP end_catch_stmt
    PROTO_N ( ( prev, body ) )
    PROTO_T ( EXP prev X EXP body )
{
    EXP e ;
    if ( unreached_code ) {
	/* Mark unreached statements */
	COPY_type ( exp_type ( prev ), type_bottom ) ;
    } else {
	/* Control reaches end of handler */
	int func ;
	e = DEREF_exp ( exp_handler_parent ( prev ) ) ;
	func = DEREF_int ( exp_try_block_func ( e ) ) ;
	if ( func == 2 ) {
	    /* Re-throw current exception */
	    e = make_throw_exp ( NULL_exp, 0 ) ;
	    body = add_compound_stmt ( body, e ) ;
	    COPY_type ( exp_type ( prev ), type_bottom ) ;
	}
    }
    COPY_exp ( exp_handler_body ( prev ), body ) ;
    set_parent_stmt ( body, prev ) ;
    POP_exp ( e, crt_try_blocks ) ;
    UNUSED ( e ) ;
    return ( prev ) ;
}


/*
    CONSTRUCT A THROW ARGUMENT FROM A TYPE

    The syntax 'throw t' for a type t is exactly equivalent to 'throw t ()'.
    This routine constructs the argument 't ()'.  n gives the number of types
    defined in t.
*/

EXP make_throw_arg
    PROTO_N ( ( t, n ) )
    PROTO_T ( TYPE t X int n )
{
    EXP e ;
    report ( crt_loc, ERR_except_throw_type () ) ;
    if ( n ) report ( crt_loc, ERR_except_throw_typedef () ) ;
    e = make_func_cast_exp ( t, NULL_list ( EXP ) ) ;
    return ( e ) ;
}


/*
    CONSTRUCT A THROW EXPRESSION

    This routine constructs the expressions 'throw a' and 'throw' (if a is
    the null expression).  Note that a is assigned to a temporary variable
    of its own type.
*/

EXP make_throw_exp
    PROTO_N ( ( a, expl ) )
    PROTO_T ( EXP a X int expl )
{
    EXP e ;
    EXP b = NULL_exp ;
    EXP d = NULL_exp ;
    if ( !IS_NULL_exp ( a ) ) {
	/* Perform operand conversions on a */
	TYPE t ;
	ERROR err ;
	a = convert_reference ( a, REF_NORMAL ) ;
	t = DEREF_type ( exp_type ( a ) ) ;
	if ( !IS_type_compound ( t ) ) {
	    a = convert_lvalue ( a ) ;
	    t = DEREF_type ( exp_type ( a ) ) ;
	}
	t = exception_type ( t, 1 ) ;
	IGNORE check_throw ( t, 1 ) ;
	b = sizeof_exp ( t ) ;
	err = check_complete ( t ) ;
	if ( IS_NULL_err ( err ) ) {
	    /* Exception is assigned to temporary variable */
	    a = init_assign ( t, cv_none, a, &err ) ;
	    d = init_default ( t, &d, DEFAULT_DESTR, EXTRA_DESTR, &err ) ;
	    if ( !IS_NULL_err ( err ) ) err = init_error ( err, 0 ) ;
	}
	if ( !IS_NULL_err ( err ) ) {
	    /* Report type errors */
	    err = concat_error ( err, ERR_except_throw_copy () ) ;
	    report ( crt_loc, err ) ;
	}
	a = check_return_exp ( a, lex_throw ) ;
    } else {
	/* Check thrown type */
	IGNORE check_throw ( NULL_type, 1 ) ;
    }
    MAKE_exp_exception ( type_bottom, a, b, d, expl, e ) ;
    return ( e ) ;
}


#endif
