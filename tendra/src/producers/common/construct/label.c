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
#include "member_ops.h"
#include "nspace_ops.h"
#include "error.h"
#include "catalog.h"
#include "basetype.h"
#include "dump.h"
#include "function.h"
#include "hash.h"
#include "label.h"
#include "namespace.h"
#include "statement.h"
#include "syntax.h"


/*
    LABEL NAMESPACE

    The labels in a function occupy a distinct namespace.  This is given by
    the following variable.
*/

NAMESPACE label_namespace = NULL_nspace ;


/*
    LABEL USAGE VALUES

    The storage field of a label is used primarily to indicate whether that
    label has been used or defined.  However addition information is recorded
    using the following values, namely, whether the label is jumped to in
    an accessible portion of the program or reached by falling into it from
    the previous statement, and whether or not it is an unnamed label.
*/

#define dspec_goto		dspec_static
#define dspec_reached		dspec_extern
#define dspec_fall_thru		dspec_auto
#define dspec_anon		dspec_register
#define dspec_solve		dspec_mutable
#define dspec_scope		dspec_inline


/*
    CREATE A LABEL

    This routine creates a label named nm with usage information info.
*/

static IDENTIFIER make_label
    PROTO_N ( ( nm, info, op ) )
    PROTO_T ( HASHID nm X DECL_SPEC info X int op )
{
    IDENTIFIER lab ;
    NAMESPACE ns = label_namespace ;
    MAKE_id_label ( nm, info, ns, crt_loc, op, lab ) ;
    return ( lab ) ;
}


/*
    BEGIN A LABELLED STATEMENT

    This routine begins the construction of a statement labelled by the
    label lab.  If lab is the null identifier then a unique identifier
    name is created.  op gives the type of label being defined (for example
    a break label, a case label or a normal identifier label).  If the
    label has already been defined then the null expression is returned.
    Although from the syntax a label is associated with a single body
    statement, the body of a labelled statement is actually all the
    remaining statements in the block.  That is:

			{
			    stmt1 ;
			    ...
			    label : body1 ;
			    body2 ;
			    ....
			}

    is transformed into:

			{
			    stmt1 ;
			    ...
			    label : {
				body1 ;
				body2 ;
				....
			    }
			}

    except that the introduced block does not establish a scope.
*/

EXP begin_label_stmt
    PROTO_N ( ( lab, op ) )
    PROTO_T ( IDENTIFIER lab X int op )
{
    EXP e ;
    EXP seq ;
    HASHID nm ;
    MEMBER mem ;
    DECL_SPEC def_info = ( dspec_defn | dspec_scope ) ;

    /* Make up label name if necessary */
    if ( IS_NULL_id ( lab ) ) {
	nm = lookup_anon () ;
	def_info |= dspec_anon ;
	if ( op == lex_case || op == lex_default ) {
	    /* Mark case and default labels */
	    def_info |= ( dspec_used | dspec_goto ) ;
	}
    } else {
	nm = DEREF_hashid ( id_name ( lab ) ) ;
    }

    /* Check for fall through */
    if ( !unreached_code ) def_info |= dspec_fall_thru ;

    /* Check if label has already been defined */
    mem = search_member ( label_namespace, nm, 1 ) ;
    lab = DEREF_id ( member_id ( mem ) ) ;
    if ( !IS_NULL_id ( lab ) ) {
	DECL_SPEC info = DEREF_dspec ( id_storage ( lab ) ) ;
	if ( info & dspec_defn ) {
	    /* Already defined */
	    IDENTIFIER fn = crt_func_id ;
	    PTR ( LOCATION ) loc = id_loc ( lab ) ;
	    report ( crt_loc, ERR_stmt_label_redef ( lab, fn, loc ) ) ;
	    return ( NULL_exp ) ;
	}
	/* Already used */
	info |= def_info ;
	COPY_dspec ( id_storage ( lab ), info ) ;
	COPY_loc ( id_loc ( lab ), crt_loc ) ;
    } else {
	/* Not used or defined previously */
	lab = make_label ( nm, def_info, op ) ;
	COPY_id ( member_id ( mem ), lab ) ;
    }
    if ( do_local && !IS_hashid_anon ( nm ) ) {
	dump_declare ( lab, &crt_loc, 1 ) ;
    }

    /* Create a labelled statement */
    seq = begin_compound_stmt ( 0 ) ;
    MAKE_exp_label_stmt ( type_void, lab, seq, e ) ;
    COPY_exp ( exp_sequence_parent ( seq ), e ) ;
    COPY_exp ( id_label_stmt ( lab ), e ) ;
    unreached_code = 0 ;
    unreached_last = 0 ;
    return ( e ) ;
}


/*
    COMPLETE A LABELLED STATEMENT

    This routine completes the construction of the labelled statement prev
    using the statement body.  It is also used to handle case and default
    statements.  If prev is the null expression, indicating any illegal
    label of some kind, then body is returned.  Otherwise body is added
    to the compound statement which is labelled.
*/

EXP end_label_stmt
    PROTO_N ( ( prev, body ) )
    PROTO_T ( EXP prev X EXP body )
{
    EXP seq ;
    IDENTIFIER lab ;
    DECL_SPEC info ;
    if ( IS_NULL_exp ( prev ) ) return ( body ) ;

    /* Mark end of label scope */
    lab = DEREF_id ( exp_label_stmt_label ( prev ) ) ;
    info = DEREF_dspec ( id_storage ( lab ) ) ;
    info &= ~dspec_scope ;
    COPY_dspec ( id_storage ( lab ), info ) ;

    /* Check for consecutive labels */
    if ( !IS_NULL_exp ( body ) && IS_exp_label_stmt ( body ) ) {
	/* Two consecutive labels */
	IDENTIFIER blab = DEREF_id ( exp_label_stmt_label ( body ) ) ;
	blab = DEREF_id ( id_alias ( blab ) ) ;
	COPY_id ( id_alias ( lab ), blab ) ;
    }

    /* Assign to label body */
    seq = DEREF_exp ( exp_label_stmt_body ( prev ) ) ;
    seq = add_compound_stmt ( seq, body ) ;
    COPY_exp ( exp_label_stmt_body ( prev ), seq ) ;
    return ( prev ) ;
}


/*
    CONSTRUCT A JUMP TO A LABEL

    This routine constructs a jump to the label lab (including break and
    continue statements).  join gives the smallest statement containing
    both the label and the jump.  This can only be filled in later for
    named labels.
*/

EXP make_jump_stmt
    PROTO_N ( ( lab, join ) )
    PROTO_T ( IDENTIFIER lab X EXP join )
{
    DECL_SPEC info ;
    EXP e = DEREF_exp ( id_label_gotos ( lab ) ) ;

    /* Mark the label as used */
    info = DEREF_dspec ( id_storage ( lab ) ) ;
    info |= ( dspec_used | dspec_goto ) ;
    if ( !unreached_code ) info |= dspec_reached ;
    COPY_dspec ( id_storage ( lab ), info ) ;

    /* Construct the jump statement */
    if ( IS_NULL_exp ( join ) && ( info & dspec_scope ) ) {
	join = DEREF_exp ( id_label_stmt ( lab ) ) ;
    }
    MAKE_exp_goto_stmt ( type_bottom, lab, join, e, e ) ;
    COPY_exp ( id_label_gotos ( lab ), e ) ;
    unreached_code = 1 ;
    unreached_last = 0 ;
    return ( e ) ;
}


/*
    CONSTRUCT A GOTO STATEMENT

    This routine constructs a goto statement where the destination label
    is given by lab.  Note that it is possible to use a label before it
    is defined.
*/

EXP make_goto_stmt
    PROTO_N ( ( lab ) )
    PROTO_T ( IDENTIFIER lab )
{
    /* Look up existing label */
    EXP e ;
    HASHID nm ;
    MEMBER mem ;
    if ( IS_NULL_id ( lab ) ) {
	nm = lookup_anon () ;
    } else {
	nm = DEREF_hashid ( id_name ( lab ) ) ;
    }
    mem = search_member ( label_namespace, nm, 1 ) ;
    lab = DEREF_id ( member_id ( mem ) ) ;
    if ( IS_NULL_id ( lab ) ) {
	/* Create new label */
	DECL_SPEC info = ( dspec_used | dspec_goto ) ;
	lab = make_label ( nm, info, lex_identifier ) ;
	COPY_id ( member_id ( mem ), lab ) ;
    } else {
	DECL_SPEC info = DEREF_dspec ( id_storage ( lab ) ) ;
	if ( info & dspec_defn ) {
	    /* Backward jump */
	    info |= dspec_reserve ;
	    COPY_dspec ( id_storage ( lab ), info ) ;
	}
    }
    if ( do_local && do_usage && !IS_hashid_anon ( nm ) ) {
	dump_use ( lab, &crt_loc, 1 ) ;
    }
    e = make_jump_stmt ( lab, NULL_exp ) ;
    return ( e ) ;
}


/*
    POSTLUDE LABEL NAME

    This value gives the name associated with all postlude labels.  It is
    assigned when the first postlude label is created.
*/

static HASHID postlude_name = NULL_hashid ;


/*
    CREATE A POSTLUDE LABEL

    This routine creates a label name for a postlude expression, that is
    to say an expression which will be called at the end of a function.
    At present this is only used in functions which do not return a value.
    A return statement within such a function is mapped onto a jump to
    the postlude label.
*/

IDENTIFIER postlude_label
    PROTO_Z ()
{
    IDENTIFIER lab ;
    HASHID nm = postlude_name ;
    if ( IS_NULL_hashid ( nm ) ) {
	/* Assign postlude label name */
	nm = lookup_anon () ;
	postlude_name = nm ;
    }
    lab = DEREF_id ( hashid_id ( nm ) ) ;
    return ( lab ) ;
}


/*
    FIND A POSTLUDE LABEL

    This routine returns the postlude label associated with the current
    function or the null identifier if the function has no postlude.
*/

IDENTIFIER find_postlude_label
    PROTO_Z ()
{
    HASHID nm = postlude_name ;
    if ( !IS_NULL_hashid ( nm ) ) {
	MEMBER mem = search_member ( label_namespace, nm, 0 ) ;
	if ( !IS_NULL_member ( mem ) ) {
	    IDENTIFIER lab = DEREF_id ( member_id ( mem ) ) ;
	    return ( lab ) ;
	}
    }
    return ( NULL_id ) ;
}


/*
    HAS A LABELLED STATEMENT BEEN REACHED?

    This routine checks whether the label label has been reached using
    an explicit goto, break or continue statement in a reached portion of
    the program (when it returns 1) or by fall through from the previous
    statement (when it returns 2).
*/

int used_label
    PROTO_N ( ( lab ) )
    PROTO_T ( IDENTIFIER lab )
{
    DECL_SPEC info = DEREF_dspec ( id_storage ( lab ) ) ;
    if ( info & dspec_reached ) return ( 1 ) ;
    if ( info & dspec_fall_thru ) return ( 2 ) ;
    return ( 0 ) ;
}


/*
    CHECK ALL LABELS IN A FUNCTION

    This routine scans through all the labels defined in the current
    function searching for any which have been used but not defined.
    It returns the number of named labels defined.
*/

unsigned check_labels
    PROTO_Z ()
{
    /* Scan through all labels */
    unsigned no_labs = 0 ;
    NAMESPACE ns = label_namespace ;
    MEMBER mem = DEREF_member ( nspace_last ( ns ) ) ;
    while ( !IS_NULL_member ( mem ) ) {
	LOCATION loc ;
	IDENTIFIER lab = DEREF_id ( member_id ( mem ) ) ;
	if ( !IS_NULL_id ( lab ) ) {
	    /* Check label information */
	    DECL_SPEC info = DEREF_dspec ( id_storage ( lab ) ) ;
	    IDENTIFIER flab = DEREF_id ( id_alias ( lab ) ) ;
	    if ( !EQ_id ( lab, flab ) ) {
		/* Deal with label aliases */
		DECL_SPEC finfo = DEREF_dspec ( id_storage ( flab ) ) ;
		finfo |= ( info & dspec_used ) ;
		COPY_dspec ( id_storage ( flab ), finfo ) ;
	    }
	    if ( info & dspec_anon ) {
		/* Unnamed labels are ignored */
		/* EMPTY */
	    } else if ( info & dspec_defn ) {
		/* Defined labels */
		HASHID nm = DEREF_hashid ( id_name ( lab ) ) ;
		if ( !IS_hashid_anon ( nm ) ) {
		    if ( info & dspec_goto ) {
			/* Label used and defined */
			/* EMPTY */
		    } else {
			/* Label defined but not used */
			IDENTIFIER fn = crt_func_id ;
			DEREF_loc ( id_loc ( lab ), loc ) ;
			report ( loc, ERR_stmt_label_unused ( lab, fn ) ) ;
		    }
		    if ( info & ( dspec_reached | dspec_fall_thru ) ) {
			/* Label reached */
			/* EMPTY */
		    } else {
			/* Label unreached */
			DEREF_loc ( id_loc ( lab ), loc ) ;
			report ( loc, ERR_stmt_stmt_unreach () ) ;
		    }
		}
		no_labs++ ;
	    } else {
		/* Undefined labels */
		HASHID nm = DEREF_hashid ( id_name ( lab ) ) ;
		if ( !IS_hashid_anon ( nm ) ) {
		    IDENTIFIER fn = crt_func_id ;
		    DEREF_loc ( id_loc ( lab ), loc ) ;
		    report ( loc, ERR_stmt_goto_undef ( lab, fn ) ) ;
		}
	    }
	}

	/* Check next label */
	mem = DEREF_member ( member_next ( mem ) ) ;
    }
    return ( no_labs ) ;
}


/*
    FIND THE VALUE OF A CASE LABEL

    This routine determines the value associated with the case label lab.
*/

NAT find_case_nat
    PROTO_N ( ( lab ) )
    PROTO_T ( IDENTIFIER lab )
{
    EXP e = DEREF_exp ( id_label_gotos ( lab ) ) ;
    if ( !IS_NULL_exp ( e ) && IS_exp_switch_stmt ( e ) ) {
	LIST ( NAT ) p ;
	LIST ( IDENTIFIER ) q ;
	p = DEREF_list ( exp_switch_stmt_cases ( e ) ) ;
	q = DEREF_list ( exp_switch_stmt_case_labs ( e ) ) ;
	while ( !IS_NULL_list ( q ) ) {
	    IDENTIFIER id = DEREF_id ( HEAD_list ( q ) ) ;
	    if ( EQ_id ( id, lab ) ) {
		NAT n = DEREF_nat ( HEAD_list ( p ) ) ;
		return ( n ) ;
	    }
	    p = TAIL_list ( p ) ;
	    q = TAIL_list ( q ) ;
	}
    }
    return ( NULL_nat ) ;
}


/*
    LISTS OF ALL SOLVE STATEMENTS AND TRY BLOCKS

    The list all_solve_stmts keeps track of all the solve statements in
    the current function.  Similarly all_try_blocks keeps track of all the
    try blocks.
*/

LIST ( EXP ) all_solve_stmts = NULL_list ( EXP ) ;
LIST ( EXP ) all_try_blocks = NULL_list ( EXP ) ;


/*
    CHECK JUMPED OVER STATEMENTS

    This routine checks whether a jump over the statement e to the label
    lab causes the initialisation of a variable to be bypassed or control
    to be transferred into an exception handler or another label body.
    The variable force is used to indicate whether an error should be
    reported.  It is 2 for a jump into the statement, 1 for a jump from
    one branch of a statement to another (for example, a handler to the
    body of a try block), and 0 otherwise.  The routine adds any variable
    or label which is jumped over, whether initialised or not, to the
    list ids.
*/

static LIST ( IDENTIFIER ) jump_over_stmt
    PROTO_N ( ( ids, e, lab, force ) )
    PROTO_T ( LIST ( IDENTIFIER ) ids X EXP e X IDENTIFIER lab X int force )
{
    switch ( TAG_exp ( e ) ) {

	case exp_decl_stmt_tag : {
	    /* Jump into declaration body */
	    IDENTIFIER id = DEREF_id ( exp_decl_stmt_id ( e ) ) ;
	    DECL_SPEC ds = DEREF_dspec ( id_storage ( id ) ) ;
	    if ( ds & dspec_auto ) {
		if ( force == 2 ) {
		    int init = 1 ;
		    EXP d = DEREF_exp ( id_variable_init ( id ) ) ;
		    if ( IS_NULL_exp ( d ) || IS_exp_null ( d ) ) {
			if ( ds & dspec_reserve ) {
			    /* Initialised in conditional */
			    /* EMPTY */
			} else {
			    /* No initialiser */
			    init = 0 ;
			}
		    }
		    if ( init ) {
			/* Jump over initialiser */
			ERROR err ;
			LOCATION loc ;
			int op = DEREF_int ( id_label_op ( lab ) ) ;
			if ( op == lex_identifier ) {
			    err = ERR_stmt_dcl_bypass_lab ( lab, id ) ;
			} else if ( op == lex_case ) {
			    NAT n = find_case_nat ( lab ) ;
			    err = ERR_stmt_dcl_bypass_case ( n, id ) ;
			} else {
			    err = ERR_stmt_dcl_bypass_default ( id ) ;
			}
			DEREF_loc ( id_loc ( id ), loc ) ;
			report ( loc, err ) ;
		    }
		}
		CONS_id ( id, ids, ids ) ;
	    }
	    break ;
	}

	case exp_if_stmt_tag : {
	    /* Jump into if statement */
	    IDENTIFIER lb = DEREF_id ( exp_if_stmt_label ( e ) ) ;
	    if ( !IS_NULL_id ( lb ) ) CONS_id ( lb, ids, ids ) ;
	    break ;
	}

	case exp_while_stmt_tag : {
	    /* Jump into while loop */
	    IDENTIFIER bk = DEREF_id ( exp_while_stmt_break_lab ( e ) ) ;
	    IDENTIFIER cn = DEREF_id ( exp_while_stmt_cont_lab ( e ) ) ;
	    IDENTIFIER lp = DEREF_id ( exp_while_stmt_loop_lab ( e ) ) ;
	    CONS_id ( bk, ids, ids ) ;
	    CONS_id ( cn, ids, ids ) ;
	    CONS_id ( lp, ids, ids ) ;
	    break ;
	}

	case exp_do_stmt_tag : {
	    /* Jump into do loop */
	    IDENTIFIER bk = DEREF_id ( exp_do_stmt_break_lab ( e ) ) ;
	    IDENTIFIER cn = DEREF_id ( exp_do_stmt_cont_lab ( e ) ) ;
	    IDENTIFIER lp = DEREF_id ( exp_do_stmt_loop_lab ( e ) ) ;
	    CONS_id ( bk, ids, ids ) ;
	    CONS_id ( cn, ids, ids ) ;
	    CONS_id ( lp, ids, ids ) ;
	    break ;
	}

	case exp_switch_stmt_tag : {
	    /* Jump into switch statement */
	    IDENTIFIER bk = DEREF_id ( exp_switch_stmt_break_lab ( e ) ) ;
	    CONS_id ( bk, ids, ids ) ;
	    break ;
	}

	case exp_solve_stmt_tag : {
	    /* Jump into solve statement */
	    LIST ( IDENTIFIER ) lbs ;
	    LIST ( IDENTIFIER ) vars ;
	    lbs = DEREF_list ( exp_solve_stmt_labels ( e ) ) ;
	    while ( !IS_NULL_list ( lbs ) ) {
		IDENTIFIER lb = DEREF_id ( HEAD_list ( lbs ) ) ;
		CONS_id ( lb, ids, ids ) ;
		lbs = TAIL_list ( lbs ) ;
	    }
	    vars = DEREF_list ( exp_solve_stmt_vars ( e ) ) ;
	    while ( !IS_NULL_list ( vars ) ) {
		IDENTIFIER var = DEREF_id ( HEAD_list ( vars ) ) ;
		CONS_id ( var, ids, ids ) ;
		vars = TAIL_list ( vars ) ;
	    }
	    break ;
	}

	case exp_label_stmt_tag : {
	    /* Jump into labelled block */
	    IDENTIFIER lb = DEREF_id ( exp_label_stmt_label ( e ) ) ;
	    CONS_id ( lb, ids, ids ) ;
	    break ;
	}

	case exp_try_block_tag : {
	    /* Jump into try block */
	    if ( force != 0 ) {
		LOCATION loc ;
		DEREF_loc ( id_loc ( lab ), loc ) ;
		report ( loc, ERR_except_jump_into () ) ;
	    }
	    break ;
	}

	case exp_hash_if_tag : {
	    /* Jump into target dependent '#if' */
	    if ( force != 0 ) {
		LOCATION loc ;
		DEREF_loc ( id_loc ( lab ), loc ) ;
		report ( loc, ERR_cpp_cond_if_jump_into () ) ;
	    }
	    break ;
	}

	case exp_token_tag : {
	    /* Jump into statement token */
	    if ( force != 0 ) {
		LOCATION loc ;
		DEREF_loc ( id_loc ( lab ), loc ) ;
		report ( loc, ERR_token_stmt_jump () ) ;
	    }
	    break ;
	}
    }
    return ( ids ) ;
}


/*
    ADD AN IDENTIFIER TO A LIST

    This routine adds the identifier id to the start of the list p if it
    is not already a member.
*/

static LIST ( IDENTIFIER ) add_id
    PROTO_N ( ( id, p ) )
    PROTO_T ( IDENTIFIER id X LIST ( IDENTIFIER ) p )
{
    LIST ( IDENTIFIER ) q = p ;
    while ( !IS_NULL_list ( q ) ) {
	IDENTIFIER qid = DEREF_id ( HEAD_list ( q ) ) ;
	if ( EQ_id ( id, qid ) ) return ( p ) ;
	q = TAIL_list ( q ) ;
    }
    CONS_id ( id, p, p ) ;
    return ( p ) ;
}


/*
    EXTEND A SOLVE STATEMENT

    This routine extends the solve statement a by adding the label lab
    and the variables ids.
*/

static void extend_solve_stmt
    PROTO_N ( ( a, lab, ids ) )
    PROTO_T ( EXP a X IDENTIFIER lab X LIST ( IDENTIFIER ) ids )
{
    LIST ( IDENTIFIER ) vars = DEREF_list ( exp_solve_stmt_vars ( a ) ) ;
    LIST ( IDENTIFIER ) labels = DEREF_list ( exp_solve_stmt_labels ( a ) ) ;
    labels = add_id ( lab, labels ) ;
    while ( !IS_NULL_list ( ids ) ) {
	IDENTIFIER id = DEREF_id ( HEAD_list ( ids ) ) ;
	if ( IS_id_label ( id ) ) {
	    labels = add_id ( id, labels ) ;
	} else {
	    vars = add_id ( id, vars ) ;
	}
	ids = TAIL_list ( ids ) ;
    }
    COPY_list ( exp_solve_stmt_labels ( a ), labels ) ;
    COPY_list ( exp_solve_stmt_vars ( a ), vars ) ;
    return ;
}


/*
    CHECK FOR UNSTRUCTURED JUMPS

    The only instance where the mapping of a statement onto the
    corresponding TDF construct is non-trivial is for unstructured
    labels and gotos.  This routine scans the body of the current
    function, e, for such unstructured jumps and imposes some semblance
    of order on them.  The idea is to start with a labelled statement
    and to gradually expand the statement outwards until it contains all
    the goto statements for that label as substatements.  If this is the
    original labelled statement then no further action is required,
    otherwise the enclosing statement is further expanded to the
    enclosing block and the labelled statement is referenced from there.
    Jumps which bypass the initialisation of a variable or transfer
    control into an exception handler can also be detected during this
    process.
*/

EXP solve_labels
    PROTO_N ( ( e ) )
    PROTO_T ( EXP e )
{
    MEMBER mem = DEREF_member ( nspace_last ( label_namespace ) ) ;
    while ( !IS_NULL_member ( mem ) ) {
	IDENTIFIER lab = DEREF_id ( member_id ( mem ) ) ;
	if ( !IS_NULL_id ( lab ) ) {
	    DECL_SPEC info = DEREF_dspec ( id_storage ( lab ) ) ;
	    if ( info & dspec_anon ) {
		/* Unnamed labels are ignored */
		/* EMPTY */
	    } else if ( info & dspec_defn ) {
		/* Only check defined labels */
		int solve = 0 ;
		EXP a = DEREF_exp ( id_label_stmt ( lab ) ) ;
		EXP p = DEREF_exp ( id_label_gotos ( lab ) ) ;
		LIST ( IDENTIFIER ) ids = NULL_list ( IDENTIFIER ) ;
		for ( ; ; ) {
		    /* Scan for enclosing statement */
		    EXP q = p ;
		    int ok = 1 ;
		    while ( !IS_NULL_exp ( q ) && IS_exp_goto_stmt ( q ) ) {
			/* Check each goto statement */
			EXP b = q ;
			PTR ( EXP ) pb = exp_goto_stmt_join ( b ) ;
			if ( IS_NULL_exp ( DEREF_exp ( pb ) ) ) {
			    /* Join statement not yet assigned */
			    for ( ; ; ) {
				if ( EQ_exp ( a, b ) ) {
				    /* b is a sub-statement of a */
				    COPY_exp ( pb, a ) ;
				    break ;
				}
				b = get_parent_stmt ( b ) ;
				if ( IS_NULL_exp ( b ) ) {
				    /* b is not a sub-statement of a */
				    ok = 0 ;
				    break ;
				}
			    }
			}
			q = DEREF_exp ( exp_goto_stmt_next ( q ) ) ;
		    }

		    /* Check whether a encloses all the jumps to lab */
		    if ( ok ) {
			int force = 1 ;
			while ( !IS_exp_solve_stmt ( a ) ) {
			    /* Scan to enclosing solve statement */
			    ids = jump_over_stmt ( ids, a, lab, force ) ;
			    a = get_parent_stmt ( a ) ;
			    if ( IS_NULL_exp ( a ) ) break ;
			    force = 0 ;
			}
			break ;
		    }

		    /* Some jump to lab is from outside a */
		    ids = jump_over_stmt ( ids, a, lab, 2 ) ;
		    solve = 1 ;

		    /* Expand a to enclosing statement */
		    a = get_parent_stmt ( a ) ;
		    if ( IS_NULL_exp ( a ) ) {
			/* Can happen with statement tokens */
			a = e ;
			break ;
		    }
		}

		/* Deal with unstructured labels */
		if ( solve ) {
		    info |= dspec_solve ;
		    COPY_dspec ( id_storage ( lab ), info ) ;
		    extend_solve_stmt ( a, lab, ids ) ;
		}
		DESTROY_list ( ids, SIZE_id ) ;
	    }
	}
	mem = DEREF_member ( member_next ( mem ) ) ;
    }
    return ( e ) ;
}


/*
    CHECK A JUMP TO A CASE OR DEFAULT STATEMENT

    This routine checks whether the jump from the switch statement e to
    the case or default label lab bypasses the initialisation of a variable
    or jumps into an exception handler.  The previous labelled statement
    checked is passed in as prev.  If e is a sub-statement of prev then
    there is no need to check further.  The routine returns the labelled
    statement corresponding to lab.
*/

static EXP solve_case
    PROTO_N ( ( e, lab, prev ) )
    PROTO_T ( EXP e X IDENTIFIER lab X EXP prev )
{
    DECL_SPEC info = DEREF_dspec ( id_storage ( lab ) ) ;
    if ( info & dspec_defn ) {
	EXP b = DEREF_exp ( id_label_stmt ( lab ) ) ;
	EXP a = b ;
	LIST ( IDENTIFIER ) ids = NULL_list ( IDENTIFIER ) ;
	while ( !EQ_exp ( a, e ) && !EQ_exp ( a, prev ) ) {
	    ids = jump_over_stmt ( ids, a, lab, 2 ) ;
	    a = get_parent_stmt ( a ) ;
	    if ( IS_NULL_exp ( a ) ) break ;
	}
	if ( !IS_NULL_list ( ids ) ) {
	    EXP s = DEREF_exp ( exp_switch_stmt_body ( e ) ) ;
	    extend_solve_stmt ( s, lab, ids ) ;
	    DESTROY_list ( ids, SIZE_id ) ;
	}
	prev = b ;
    } else {
	/* Case not defined */
	EXP a, b ;
	LOCATION loc ;
	int uc = unreached_code ;
	IDENTIFIER flab = NULL_id ;
	int op = DEREF_int ( id_label_op ( lab ) ) ;
	DEREF_loc ( id_loc ( lab ), loc ) ;
	if ( op == lex_case ) {
	    NAT n = find_case_nat ( lab ) ;
	    report ( loc, ERR_stmt_switch_case_not ( n ) ) ;
	    flab = DEREF_id ( exp_switch_stmt_default_lab ( e ) ) ;
	} else {
	    report ( loc, ERR_stmt_switch_default_not () ) ;
	}
	if ( IS_NULL_id ( flab ) ) {
	    flab = DEREF_id ( exp_switch_stmt_break_lab ( e ) ) ;
	}
	a = begin_label_stmt ( lab, op ) ;
	b = make_jump_stmt ( flab, e ) ;
	IGNORE end_label_stmt ( a, b ) ;
	unreached_code = uc ;
    }
    return ( prev ) ;
}


/*
    CHECK A SWITCH STATEMENT

    This routine scans through the switch statement e for jumps which
    bypass the initialisation of a variable.
*/

EXP solve_switch
    PROTO_N ( ( e ) )
    PROTO_T ( EXP e )
{
    IDENTIFIER lab ;
    EXP prev = NULL_exp ;
    LIST ( IDENTIFIER ) cases ;
    cases = DEREF_list ( exp_switch_stmt_case_labs ( e ) ) ;
    while ( !IS_NULL_list ( cases ) ) {
	/* Check each case statement */
	lab = DEREF_id ( HEAD_list ( cases ) ) ;
	prev = solve_case ( e, lab, prev ) ;
	cases = TAIL_list ( cases ) ;
    }
    lab = DEREF_id ( exp_switch_stmt_default_lab ( e ) ) ;
    if ( !IS_NULL_id ( lab ) ) {
	/* Check any default statement */
	IGNORE solve_case ( e, lab, prev ) ;
    }
    return ( e ) ;
}


/*
    CONSTRUCT A LABEL FOR THE FOLLOWING STATEMENT

    This routine turns the list of statements following the position p
    in the block statement e into a labelled statement, returning the
    label created.  If p is the last statement in the block then the
    null identifier is returned.
*/

static IDENTIFIER follow_label
    PROTO_N ( ( e, p ) )
    PROTO_T ( EXP e X LIST ( EXP ) p )
{
    EXP a, b, c ;
    DECL_SPEC ds ;
    IDENTIFIER lab ;
    LIST ( EXP ) r ;
    LIST ( EXP ) q = TAIL_list ( p ) ;
    if ( IS_NULL_list ( q ) ) return ( NULL_id ) ;

    /* Examine following statement */
    a = DEREF_exp ( HEAD_list ( q ) ) ;
    if ( !IS_NULL_exp ( a ) ) {
	unsigned tag = TAG_exp ( a ) ;
	if ( tag == exp_location_tag ) {
	    a = DEREF_exp ( exp_location_arg ( a ) ) ;
	    if ( !IS_NULL_exp ( a ) ) tag = TAG_exp ( a ) ;
	    if ( tag == exp_label_stmt_tag ) {
		/* Statement is already labelled */
		lab = DEREF_id ( exp_label_stmt_label ( a ) ) ;
		return ( lab ) ;
	    }
	}
    }

    /* Create new labelled statement */
    b = begin_label_stmt ( NULL_id, lex_end ) ;
    b = end_label_stmt ( b, NULL_exp ) ;
    set_parent_stmt ( b, e ) ;
    c = DEREF_exp ( exp_label_stmt_body ( b ) ) ;
    r = DEREF_list ( exp_sequence_first ( c ) ) ;
    IGNORE APPEND_list ( r, q ) ;
    while ( !IS_NULL_list ( q ) ) {
	a = DEREF_exp ( HEAD_list ( q ) ) ;
	set_parent_stmt ( a, b ) ;
	q = TAIL_list ( q ) ;
    }
    COPY_list ( PTR_TAIL_list ( p ), NULL_list ( EXP ) ) ;
    CONS_exp ( b, NULL_list ( EXP ), q ) ;
    IGNORE APPEND_list ( p, q ) ;
    lab = DEREF_id ( exp_label_stmt_label ( b ) ) ;
    ds = DEREF_dspec ( id_storage ( lab ) ) ;
    ds |= ( dspec_goto | dspec_used ) ;
    COPY_dspec ( id_storage ( lab ), ds ) ;
    return ( lab ) ;
}


/*
    FIND THE END OF A BRANCH OF A SOLVE STATEMENT

    This routine finds the end of the branch of the solve statement e
    given by the label lab.  This is a label which gives any immediately
    following code.
*/

static IDENTIFIER end_solve_branch
    PROTO_N ( ( lab, e ) )
    PROTO_T ( IDENTIFIER lab X EXP e )
{
    EXP a ;
    IDENTIFIER nlab ;
    int op = DEREF_int ( id_label_op ( lab ) ) ;
    switch ( op ) {
	case lex_continue :
	case lex_while :
	case lex_for :
	case lex_do : {
	    /* Don't bother in these cases */
	    return ( NULL_id ) ;
	}
    }
    a = DEREF_exp ( id_label_stmt ( lab ) ) ;
    if ( IS_NULL_exp ( a ) ) {
	/* Ignore undefined labels */
	return ( NULL_id ) ;
    }
    nlab = DEREF_id ( exp_label_stmt_next ( a ) ) ;
    if ( IS_NULL_id ( nlab ) ) {
	/* Scan up to enclosing block */
	EXP b = a ;
	EXP c = DEREF_exp ( exp_label_stmt_parent ( b ) ) ;
	while ( !EQ_exp ( c, e ) && !IS_NULL_exp ( c ) ) {
	    int again ;
	    EXP d = c ;
	    do {
		again = 0 ;
		switch ( TAG_exp ( d ) ) {
		    case exp_sequence_tag : {
			/* Found enclosing block */
			LIST ( EXP ) q ;
			q = DEREF_list ( exp_sequence_first ( d ) ) ;
			q = TAIL_list ( q ) ;
			while ( !IS_NULL_list ( q ) ) {
			    EXP f = DEREF_exp ( HEAD_list ( q ) ) ;
			    if ( !IS_NULL_exp ( f ) ) {
				if ( IS_exp_location ( f ) ) {
				    /* Allow for location statements */
				    f = DEREF_exp ( exp_location_arg ( f ) ) ;
				}
				if ( EQ_exp ( f, b ) ) {
				    /* Found labelled statement in block */
				    nlab = follow_label ( d, q ) ;
				    break ;
				}
			    }
			    q = TAIL_list ( q ) ;
			}
			break ;
		    }
		    case exp_while_stmt_tag : {
			/* Found enclosing while statement */
			IDENTIFIER blab ;
			blab = DEREF_id ( exp_while_stmt_break_lab ( d ) ) ;
			if ( !EQ_id ( blab, lab ) ) {
			    nlab = DEREF_id ( exp_while_stmt_cont_lab ( d ) ) ;
			}
			break ;
		    }
		    case exp_do_stmt_tag : {
			/* Found enclosing do statement */
			IDENTIFIER blab ;
			blab = DEREF_id ( exp_do_stmt_break_lab ( d ) ) ;
			if ( !EQ_id ( blab, lab ) ) {
			    nlab = DEREF_id ( exp_do_stmt_cont_lab ( d ) ) ;
			}
			break ;
		    }
		    case exp_switch_stmt_tag : {
			/* Found enclosing switch statement */
			nlab = DEREF_id ( exp_switch_stmt_break_lab ( d ) ) ;
			if ( EQ_id ( nlab, lab ) ) nlab = NULL_id ;
			break ;
		    }
		    case exp_decl_stmt_tag : {
			/* Found enclosing declaration */
			d = DEREF_exp ( exp_decl_stmt_body ( d ) ) ;
			if ( !EQ_exp ( d, b ) ) again = 1 ;
			break ;
		    }
		    case exp_label_stmt_tag : {
			/* Found enclosing label statement */
			d = DEREF_exp ( exp_label_stmt_body ( d ) ) ;
			if ( !EQ_exp ( d, b ) ) again = 1 ;
			break ;
		    }
		}
	    } while ( again ) ;
	    if ( !IS_NULL_id ( nlab ) ) {
		/* Label for next statement found */
		nlab = DEREF_id ( id_alias ( nlab ) ) ;
		if ( op == lex_break ) {
		    /* Alias break labels */
		    COPY_id ( id_alias ( lab ), nlab ) ;
		}
		break ;
	    }
	    b = c ;
	    c = get_parent_stmt ( b ) ;
	}
    }
    COPY_id ( exp_label_stmt_next ( a ), nlab ) ;
    return ( nlab ) ;
}


/*
    END ALL SOLVE STATEMENTS

    This routine calls end_solve_branch for all the branches of all the
    solve statements in the current function.
*/

void end_solve_stmts
    PROTO_Z ()
{
    LIST ( EXP ) p = all_solve_stmts ;
    if ( !IS_NULL_list ( p ) ) {
	while ( !IS_NULL_list ( p ) ) {
	    int changed ;
	    LIST ( IDENTIFIER ) q0 ;
	    EXP e = DEREF_exp ( HEAD_list ( p ) ) ;
	    q0 = DEREF_list ( exp_solve_stmt_labels ( e ) ) ;
	    do {
		LIST ( IDENTIFIER ) q = q0 ;
		changed = 0 ;
		while ( !IS_NULL_list ( q ) ) {
		    IDENTIFIER lab = DEREF_id ( HEAD_list ( q ) ) ;
		    IDENTIFIER nlab = end_solve_branch ( lab, e ) ;
		    if ( !IS_NULL_id ( nlab ) ) {
			/* Add new label to list */
			LIST ( IDENTIFIER ) q1 = add_id ( nlab, q0 ) ;
			if ( !EQ_list ( q1, q0 ) ) {
			    q0 = q1 ;
			    changed = 1 ;
			}
		    }
		    q = TAIL_list ( q ) ;
		}
	    } while ( changed ) ;
	    COPY_list ( exp_solve_stmt_labels ( e ), q0 ) ;
	    p = TAIL_list ( p ) ;
	}
	DESTROY_list ( all_solve_stmts, SIZE_exp ) ;
	all_solve_stmts = NULL_list ( EXP ) ;
    }
    return ;
}
