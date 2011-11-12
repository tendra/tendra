/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "config.h"
#include "c_types.h"
#include "etype_ops.h"
#include "exp_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "loc_ext.h"
#include "member_ops.h"
#include "nspace_ops.h"
#include "str_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "option.h"
#include "assign.h"
#include "basetype.h"
#include "cast.h"
#include "check.h"
#include "chktype.h"
#include "class.h"
#include "constant.h"
#include "construct.h"
#include "convert.h"
#include "declare.h"
#include "destroy.h"
#include "dump.h"
#include "exception.h"
#include "expression.h"
#include "file.h"
#include "function.h"
#include "hash.h"
#include "identifier.h"
#include "initialise.h"
#include "label.h"
#include "lex.h"
#include "literal.h"
#include "member.h"
#include "namespace.h"
#include "overload.h"
#include "parse.h"
#include "predict.h"
#include "quality.h"
#include "redeclare.h"
#include "statement.h"
#include "symbols.h"
#include "syntax.h"
#include "template.h"
#include "ustring.h"
#include "variable.h"


/*
    UNREACHED CODE ANALYSIS

    The detection of unreachable code is primarily by means of the simple
    flag, which is true for unreported statements.  The flag unreached_last
    is set to equal unreached_code whenever a reachability check is applied.
    This is to ensure that only the first statement in an unreached block
    is reported.  At the end of a conditional, or other complex statement,
    unreached_prev is set to the value of unreached_code at the start of
    that statement.  The flag unreached_fall is set to false immediately
    following a 'case' or 'default' label, but set to true after a non-
    trivial statement (this is included in the grammar).
*/

int unreached_code = 0;
int unreached_last = 0;
int unreached_prev = 0;
int unreached_fall = 0;
int suppress_fall = 0;


/*
    DOES AN EXPRESSION NOT RETURN?

    This routine tests whether the expression e has type bottom, i.e. does
    not return a value.
*/

static int
is_bottom(EXP e)
{
	TYPE t;
	if (IS_NULL_exp(e)) {
		return 0;
	}
	t = DEREF_type(exp_type(e));
	return IS_type_bottom(t);
}


/*
    FIND THE PARENT OF A STATEMENT

    This routine returns a pointer to the parent of the statement e.  It
    returns the null pointer if e is a simple expression.
*/

static PTR(EXP)
parent_stmt(EXP e)
{
	PTR(EXP) ptr = NULL_ptr(EXP);
	if (!IS_NULL_exp(e)) {
		switch (TAG_exp(e)) {
		case exp_reach_tag:
			ptr = exp_reach_parent(e);
			break;
		case exp_unreach_tag:
			ptr = exp_unreach_parent(e);
			break;
		case exp_sequence_tag:
			ptr = exp_sequence_parent(e);
			break;
		case exp_solve_stmt_tag:
			ptr = exp_solve_stmt_parent(e);
			break;
		case exp_decl_stmt_tag:
			ptr = exp_decl_stmt_parent(e);
			break;
		case exp_if_stmt_tag:
			ptr = exp_if_stmt_parent(e);
			break;
		case exp_while_stmt_tag:
			ptr = exp_while_stmt_parent(e);
			break;
		case exp_do_stmt_tag:
			ptr = exp_do_stmt_parent(e);
			break;
		case exp_switch_stmt_tag:
			ptr = exp_switch_stmt_parent(e);
			break;
		case exp_hash_if_tag:
			ptr = exp_hash_if_parent(e);
			break;
		case exp_return_stmt_tag:
			ptr = exp_return_stmt_parent(e);
			break;
		case exp_goto_stmt_tag:
			ptr = exp_goto_stmt_parent(e);
			break;
		case exp_label_stmt_tag:
			ptr = exp_label_stmt_parent(e);
			break;
		case exp_try_block_tag:
			ptr = exp_try_block_parent(e);
			break;
		case exp_handler_tag:
			ptr = exp_handler_parent(e);
			break;
		case exp_token_tag:
			ptr = exp_token_parent(e);
			break;
		case exp_location_tag: {
			EXP a = DEREF_exp(exp_location_arg(e));
			ptr = parent_stmt(a);
			break;
		}
		case exp_paren_tag: {
			EXP a = DEREF_exp(exp_paren_arg(e));
			ptr = parent_stmt(a);
			break;
		}
		}
	}
	return ptr;
}


/*
    GET THE PARENT OF A STATEMENT

    This routine returns the parent statement of e.
*/

EXP
get_parent_stmt(EXP e)
{
	EXP p = NULL_exp;
	if (!IS_NULL_exp(e)) {
		PTR(EXP)ptr = parent_stmt(e);
		if (!IS_NULL_ptr(ptr)) {
			p = DEREF_exp(ptr);
		}
	}
	return p;
}


/*
    SET THE PARENT OF A STATEMENT

    This routine sets the parent of the statement e to be p.
*/

void
set_parent_stmt(EXP e, EXP p)
{
	if (!IS_NULL_exp(e)) {
		PTR(EXP)ptr = parent_stmt(e);
		if (!IS_NULL_ptr(ptr)) {
			COPY_exp(ptr, p);
		}
	}
	return;
}


/*
    STATEMENT LOCATION FLAG

    The flag record_location may be set to true to force extra expressions
    giving the location of each statement to be inserted into the output.
    The variable stmt_loc records the last such location.
*/

int record_location = 0;
LOCATION stmt_loc = NULL_loc;
static int adjusted_line = 0;


/*
    ADJUST COLUMN NUMBER

    This routine sets stmt_loc to point to the start of the preprocessing
    token p.
*/

static void
adjust_column(PPTOKEN *p)
{
	if (p) {
		int t = p->tok;
		if (t >= FIRST_SYMBOL && t <= LAST_SYMBOL) {
			/* Adjust to start of symbol */
			ulong len = (ulong)ustrlen(token_name(t));
			stmt_loc = crt_loc;
			stmt_loc.column -= (len - 1);
			return;
		}
		if (t >= FIRST_KEYWORD && t <= LAST_KEYWORD) {
			/* Map keywords to underlying identifier */
			t = lex_identifier;
		}
		if (t == lex_identifier) {
			IDENTIFIER id = p->pp_data.id.use;
			id = underlying_id(id);
			DEREF_loc(id_loc(id), stmt_loc);
			return;
		}
	}
	stmt_loc = crt_loc;
	return;
}


/*
    ADJUST LINE NUMBER

    This routine is called whenever the location of a statement is
    recorded.  It is intended to ensure that the current location points
    to the start of the next statement rather than the end of the current
    statement.
*/

static void
adjust_line(int next)
{
	if (!adjusted_line) {
		adjusted_line = 1;
		if (next) {
			switch (crt_lex_token) {
			case lex_open_Hbrace_H1:
			case lex_colon:
			case lex_semicolon:
			case lex_close_Hround:
			case lex_else:
			case lex_exhaustive: {
				/* Scan to next token */
				PPTOKEN *p = crt_token->next;
				if (p) {
					/* Set location from next token */
					p = read_loc_tokens(p);
					if (crt_state_depth == 0) {
						adjust_column(p);
						return;
					}
				} else {
					if (crt_state_depth == 0) {
						/* Skip white space from input
						 * file */
						unsigned long sp =
						    skip_white(1);
						update_column();
						stmt_loc = crt_loc;
						stmt_loc.column++;
						if (sp) {
							patch_white(sp);
						}
						return;
					}
				}
				break;
			}
			default:
				/* Use current token */
				if (crt_state_depth == 0) {
					adjust_column(crt_token);
					return;
				}
				break;
			}
		}
		stmt_loc = crt_loc;
	}
	return;
}


/*
    BLOCK NAMESPACE

    This variable can be set to make begin_compound_stmt use an existing
    namespace rather than creating a new one.
*/

NAMESPACE block_namespace = NULL_nspace;


/*
    BEGIN A COMPOUND STATEMENT

    These routine begins the construction of a compound statement.  If
    scope is true then this compound statement also establishes a scope.
    A compound statement consists of a list of statements (the first of
    which is always a dummy null expression) plus a pointer indicating
    where the next statement to be added to the compound statement is to
    go.  For simple statement lists this is the last element of the list,
    but if labels or declarations are introduced then any statements added
    subsequently will go at the end of the dummy block introduced by
    begin_label_stmt or make_decl_stmt.  The parent field of the main
    statement is used within the construction to point to the innermost
    block of this kind.  It is only set to its correct value at the end
    of the compound statement.
*/

EXP
begin_compound_stmt(int scope)
{
	TYPE t;
	NAMESPACE ns;
	EXP e = NULL_exp;
	LIST(EXP) stmts;
	NAMESPACE cns = NULL_nspace;

	/* Create block namespace */
	if (scope > 0) {
		ns = block_namespace;
		if (IS_NULL_nspace(ns)) {
			/* Create new namespace */
			unsigned tag = nspace_block_tag;
			if (scope == 2) {
				tag = nspace_dummy_tag;
			}
			cns = crt_namespace;
			ns = make_namespace(crt_func_id, tag, 0);
			push_namespace(ns);
		} else {
			/* Use existing namespace */
			MEMBER mem = DEREF_member(nspace_last(ns));
			COPY_member(nspace_prev(ns), mem);
			cns = ns;
			block_namespace = NULL_nspace;
		}
		IGNORE incr_value(OPT_VAL_statement_depth);
	} else {
		ns = NULL_nspace;
	}

	/* Create compound statement */
	t = (unreached_code ? type_bottom : type_void);
	if (record_location && scope >= 0) {
		/* Record start of block */
		adjust_line(scope);
		adjusted_line = 0;
		MAKE_exp_location(t, stmt_loc, e, e);
		if (do_scope) {
			dump_begin_scope(NULL_id, ns, cns, &crt_loc);
		}
	}
	CONS_exp(e, NULL_list(EXP), stmts);
	MAKE_exp_sequence(t, stmts, stmts, ns, 0, e);
	COPY_exp(exp_sequence_parent(e), e);
	return e;
}


/*
    MARK THE START OF A COMPOUND STATEMENT

    On occasions a compound statement may be created before the open brace
    which marks its start.  In this case this routine is called when the
    open brace is encountered to record the actual position of the start
    of the block.
*/

void
mark_compound_stmt(EXP prev)
{
	if (record_location) {
		LIST(EXP) stmts = DEREF_list(exp_sequence_first(prev));
		EXP stmt = DEREF_exp(HEAD_list(stmts));
		if (!IS_NULL_exp(stmt) && IS_exp_location(stmt)) {
			adjust_line(1);
			adjusted_line = 0;
			COPY_loc(exp_location_end(stmt), stmt_loc);
		}
	}
	return;
}


/*
    EXTEND A COMPOUND STATEMENT

    This routine adds the statement stmt to the end of the compound
    statement prev.  Note that this routine also decides where the
    statement after this one is to go on the basis of the rules above.
*/

static EXP
extend_compound_stmt(EXP prev, EXP stmt, int loc)
{
	EXP body;
	EXP parent;
	LIST(EXP) elem;
	LIST(EXP) elem0;
	LIST(EXP) stmts;

	/* Allow for null statements */
	if (IS_NULL_exp(stmt)) {
		return prev;
	}

	/* Add statement to list */
	stmts = DEREF_list(exp_sequence_last(prev));
	CONS_exp(stmt, NULL_list(EXP), elem);
	COPY_list(PTR_TAIL_list(stmts), elem);
	elem0 = elem;

	/* Set the parent of stmt */
	parent = DEREF_exp(exp_sequence_parent(prev));
	set_parent_stmt(stmt, parent);

	/* Find location of next statement */
	switch (TAG_exp(stmt)) {
	case exp_decl_stmt_tag: {
		/* Transfer to the body of a declaration */
		unsigned tag;
		body = stmt;
		do {
			body = DEREF_exp(exp_decl_stmt_body(body));
			tag = TAG_exp(body);
		} while (tag == exp_decl_stmt_tag);
		if (tag == exp_sequence_tag) {
			elem = DEREF_list(exp_sequence_last(body));
			COPY_exp(exp_sequence_parent(prev), body);
		}
		loc = 0;
		break;
	}
	case exp_label_stmt_tag:
		/* Transfer to the body of a labelled statement */
		body = DEREF_exp(exp_label_stmt_body(stmt));
		if (IS_exp_sequence(body)) {
			elem = DEREF_list(exp_sequence_last(body));
			COPY_exp(exp_sequence_parent(prev), body);
		}
		loc = 0;
		break;
	case exp_location_tag:
	case exp_thrown_tag:
		/* Don't record location in these cases */
		loc = 0;
		break;
	}
	COPY_list(exp_sequence_last(prev), elem);

	/* Record statement location */
	if (record_location) {
		adjust_line(1);
		if (loc) {
			TYPE t = DEREF_type(exp_type(stmt));
			MAKE_exp_location(t, stmt_loc, stmt, stmt);
			COPY_exp(HEAD_list(elem0), stmt);
		}
	}

	/* Unreached code analysis */
	if (is_bottom(stmt)) {
		COPY_type(exp_type(prev), type_bottom);
	}
	return prev;
}


/*
    ADD A STATEMENT TO A COMPOUND STATEMENT

    This routine adds the statement stmt to the compound statement prev,
    returning the resulting compound statement.  It differs from the
    previous routine in taking any declarations in stmt into account.
    This is done using the last field of the current namespace which keeps
    track of the last variable in the block for which a declaration
    statement has been introduced.  The treatment of labelled statements
    is tricky - the declarations need to be inserted between the label
    and its body.
*/

EXP
add_compound_stmt(EXP prev, EXP stmt)
{
    EXP parent = NULL_exp;
    LIST(EXP) last = NULL_list(EXP);
    NAMESPACE ns = DEREF_nspace(exp_sequence_decl(prev));
    if (!IS_NULL_nspace(ns)) {
	MEMBER p = DEREF_member(nspace_last(ns));
	MEMBER q = DEREF_member(nspace_prev(ns));
	if (!EQ_member(p, q)) {
	    /* Create declaration statement */
	    int vars = 0;
	    EXP decl = make_decl_stmt(p, q, &vars);
	    if (!IS_NULL_exp(stmt) && IS_exp_label_stmt(stmt)) {
		/* Labels come before declarations */
		EXP body = DEREF_exp(exp_label_stmt_body(stmt));
		if (IS_exp_sequence(body)) {
		    last = DEREF_list(exp_sequence_last(body));
		    body = DEREF_exp(HEAD_list(last));
		    if (!IS_NULL_exp(body)) {
			EXP b = body;
			if (IS_exp_location(b)) {
			    b = DEREF_exp(exp_location_arg(b));
			}
			if (!IS_NULL_exp(b)) {
			    COPY_exp(HEAD_list(last), NULL_exp);
			}
		    }
		    last = NULL_list(EXP);
		    prev = extend_compound_stmt(prev, stmt, 1);
		    stmt = body;
		}
	    }
	    if (!vars) {
		last = DEREF_list(exp_sequence_last(prev));
		parent = DEREF_exp(exp_sequence_parent(prev));
	    }
	    prev = extend_compound_stmt(prev, decl, 0);
	    COPY_member(nspace_prev(ns), p);
	}
    }
    if (!IS_NULL_exp(stmt)) {
	/* Add the new statement */
	prev = extend_compound_stmt(prev, stmt, 1);
    }
    if (!IS_NULL_list(last)) {
	/* Restrict scope of temporaries to stmt */
	last = END_list(last);
	COPY_list(exp_sequence_last(prev), last);
	COPY_exp(exp_sequence_parent(prev), parent);
    }
    adjusted_line = 0;
    return prev;
}


/*
    END A COMPOUND STATEMENT

    This routine ends the compound statement prev.
*/

EXP
end_compound_stmt(EXP prev)
{
	/* Take local declarations out of scope */
	int blk = DEREF_int(exp_sequence_block(prev));
	NAMESPACE ns = DEREF_nspace(exp_sequence_decl(prev));
	if (!IS_NULL_nspace(ns)) {
		if (check_namespace(ns, prev, ANON_NONE, 1)) {
			if (blk == 0) {
				COPY_int(exp_sequence_block(prev), 1);
			}
		}
		if (do_scope) {
			dump_end_scope(NULL_id, ns, &stmt_loc);
		}
		decr_value(OPT_VAL_statement_depth);
		IGNORE pop_namespace();
	}
	COPY_exp(exp_sequence_parent(prev), NULL_exp);
	return prev;
}


/*
    CONSTRUCT A TEMPORARY DECLARATION STATEMENT

    This routine binds any temporary variable declarations given by the
    namespace members p to q to the expression e.  This is part of the
    action of make_decl_stmt.
*/

EXP
make_temp_decl(MEMBER p, MEMBER q, EXP e)
{
	MEMBER r = p;
	while (!EQ_member(r, q)) {
		IDENTIFIER id = DEREF_id(member_id(r));
		if (!IS_NULL_id(id) && IS_id_variable(id)) {
			/* Construct declaration statement */
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			if (ds & dspec_temp) {
				/* Temporary variables */
				if (!(ds & dspec_ignore)) {
					EXP d;
					TYPE t =
					    DEREF_type(id_variable_type(id));
					EXP term =
					    DEREF_exp(id_variable_term(id));
					if (!IS_NULL_exp(term)) {
						have_destructor = 1;
					}
					MAKE_exp_decl_stmt(t, id, e, d);
					set_parent_stmt(e, d);
					e = d;
				}
			}
		}
		r = DEREF_member(member_next(r));
	}
	return e;
}


/*
    CONSTRUCT A DECLARATION STATEMENT

    This routine constructs a series of nested declaration statements
    corresponding to the given list of namespace members.  p gives the
    last member of the current block namespace defined, while q gives
    the last member defined before this declaration.  The body of a
    declaration statement consists of the rest of the statements in the
    enclosing block.  That is:

			{
			    stmt1 ;
			    ....
			    decl1 ;
			    decl2 ;
			    ....
			    body1 ;
			    ....
			}

    is transformed into:

			{
			    stmt1 ;
			    ....
			    decl1 ; {
				decl2 ; {
				    .... {
					body1 ;
					....
				    }
				}
			    }
			}

    except that the introduced blocks do not establish scopes.  Any
    temporary variables introduced are declared before the normal
    variables regardless of their actual order of declaration.
*/

EXP
make_decl_stmt(MEMBER p, MEMBER q, int *vars)
{
    MEMBER r = p;
    unsigned temps = 0;
    IDENTIFIER init = NULL_id;
    LIST(IDENTIFIER) destr = NULL_list(IDENTIFIER);
    EXP e = begin_compound_stmt(-1);

    /* Scan through members */
    while (!EQ_member(r, q)) {
	IDENTIFIER id = DEREF_id(member_id(r));
	if (!IS_NULL_id(id) && IS_id_variable(id)) {
	    /* Construct declaration statement */
	    DECL_SPEC ds = DEREF_dspec(id_storage(id));
	    if (ds & dspec_temp) {
		/* Temporary variables */
		if (!(ds & dspec_ignore)) {
		    if (ds & dspec_register) {
			EXP term = DEREF_exp(id_variable_term(id));
			if (!IS_NULL_exp(term)) {
			    CONS_id(id, destr, destr);
			}
		    }
		    temps++;
		}
	    } else if (ds & dspec_linkage) {
		/* External variables */
		/* EMPTY */
	    } else if ((ds & dspec_reserve) && !is_anon_member(id)) {
		/* Injected variables */
		/* EMPTY */
	    } else {
		EXP d;
		TYPE t = DEREF_type(id_variable_type(id));
		EXP def = DEREF_exp(id_variable_init(id));
		EXP term = DEREF_exp(id_variable_term(id));
		if (!IS_NULL_exp(term)) {
			have_destructor = 1;
		}
		if (!IS_NULL_exp(def) && !IS_exp_null(def)) {
		    /* Identifier is initialised */
		    init = id;
		}
		MAKE_exp_decl_stmt(t, id, e, d);
		set_parent_stmt(e, d);
		*vars = 1;
		e = d;
	    }
	}
	r = DEREF_member(member_next(r));
    }

    /* Scan through again for temporary variables */
    if (temps) {
	e = make_temp_decl(p, q, e);
	if (!IS_NULL_list(destr)) {
	    /* NOT YET IMPLEMENTED */
	    DESTROY_list(destr, SIZE_id);
	}
    }

    /* Only report unreached declarations if they are initialised */
    if (!IS_NULL_id(init) && unreached_code) {
	if (!unreached_last) {
	    LOCATION loc;
	    DEREF_loc(id_loc(init), loc);
	    report(loc, ERR_stmt_stmt_unreach());
	    unreached_last = 1;
	}
    }
    return e;
}


/*
    BIND TEMPORARY VARIABLES TO AN EXPRESSION

    This routine binds any temporary variables declared in e to the
    expression.  Reference conversions are also applied, but any
    parentheses are preserved for the benefit of the assignment in
    boolean check.
*/

EXP
bind_temporary(EXP e)
{
	if (!IS_NULL_exp(e)) {
		NAMESPACE ns = crt_namespace;
		unsigned tag = TAG_exp(e);
		e = convert_reference(e, REF_NORMAL);
		if (!IS_NULL_nspace(ns) && IS_nspace_block_etc(ns)) {
			MEMBER p = DEREF_member(nspace_last(ns));
			MEMBER q = DEREF_member(nspace_prev(ns));
			if (!EQ_member(p, q)) {
				e = make_temp_decl(p, q, e);
				COPY_member(nspace_prev(ns), p);
			}
		}
		if (tag == exp_paren_tag && option(OPT_bool_assign)) {
			e = make_paren_exp(e);
		}
	}
	return e;
}


/*
    DISCARD AN EXPRESSION

    This routine discards the expression e.  If e is an lvalue then the
    lvalue conversions are checked but not performed.
*/

EXP
make_discard_exp(EXP e)
{
	if (!IS_NULL_exp(e)) {
		unsigned tag = TAG_exp(e);
		TYPE t = DEREF_type(exp_type(e));
		switch (TAG_type(t)) {
		case type_top_tag:
		case type_bottom_tag:
			/* Void types */
			break;
		case type_bitfield_tag:
			/* Remove bitfield components */
			if (tag == exp_contents_tag) {
				e = DEREF_exp(exp_contents_ptr(e));
				tag = TAG_exp(e);
			}
			if (tag == exp_indir_tag) {
				e = DEREF_exp(exp_indir_ptr(e));
				tag = TAG_exp(e);
				if (tag == exp_add_ptr_tag) {
					e = DEREF_exp(exp_add_ptr_ptr(e));
					tag = TAG_exp(e);
					if (tag == exp_address_tag) {
						e = DEREF_exp(exp_address_arg(e));
						tag = TAG_exp(e);
					}
				}
			}
			break;
		case type_array_tag:
		case type_func_tag:
		case type_templ_tag:
			/* Check for overloaded functions */
			e = convert_lvalue(e);
			tag = TAG_exp(e);
			break;
		case type_token_tag:
			if (is_templ_type(t)) {
				/* Mark template parameters */
				MAKE_exp_op(t, lex_void, e, NULL_exp, e);
				tag = exp_op_tag;
				break;
			}
			goto default_lab;
		default:
default_lab: {
		     /* Check lvalue conversions */
		     ERROR err;
		     CV_SPEC qual = DEREF_cv(type_qual(t));
		     if (!(qual & cv_lvalue)) {
			     break;
		     }
		     if (qual == (cv_lvalue | cv_const)) {
			     if (tag == exp_identifier_tag) {
				     e = convert_const(e);
				     tag = TAG_exp(e);
				     break;
			     }
		     }
		     err = check_incomplete(t);
		     if (!IS_NULL_err(err)) {
			     err = concat_error(err, ERR_stmt_expr_incompl());
			     report(crt_loc, err);
		     }
		     break;
	     }
		}
		switch (tag) {
		case exp_postinc_tag:
			/* Discard postincrement expressions */
			COPY_exp(exp_postinc_value(e), NULL_exp);
			break;
		case exp_address_tag:
		case exp_address_mem_tag:
			/* Check for overloaded functions */
			e = convert_lvalue(e);
			break;
		case exp_constr_tag:
			/* Introduce temporary for constructor */
			e = convert_none(e);
			break;
		}
	}
	return e;
}


/*
    CHECK A DISCARDED EXPRESSION

    This routine checks whether discarding the expression e should be
    warned about.
*/

static int
check_discard_exp(EXP e)
{
	if (!IS_NULL_exp(e)) {
		switch (TAG_exp(e)) {
		case exp_indir_tag: {
			/* Ignore indirection expressions */
			EXP a = DEREF_exp(exp_indir_ptr(e));
			return check_discard_exp(a);
		}
		case exp_contents_tag: {
			/* Ignore contents expressions */
			EXP a = DEREF_exp(exp_contents_ptr(e));
			return check_discard_exp(a);
		}
		case exp_comma_tag: {
			/* Examine final component of comma expression */
			LIST(EXP) p = DEREF_list(exp_comma_args(e));
			EXP a = DEREF_exp(HEAD_list(END_list(p)));
			return check_discard_exp(a);
		}
		case exp_postinc_tag:
			/* Discard postincrement expressions */
			COPY_exp(exp_postinc_value(e), NULL_exp);
			goto assign_lab;
		case exp_assign_tag:
		case exp_init_tag:
		case exp_preinc_tag:
		case exp_decl_stmt_tag:
assign_lab:
			/* Assignments and declarations are allowed */
			if (!IS_NULL_id(made_temporary)) {
				report(crt_loc, ERR_stmt_expr_discard_val());
			}
			break;
		case exp_func_tag:
			/* Discarded function return */
			report(crt_loc, ERR_stmt_expr_discard_func());
			break;
		case exp_func_id_tag: {
			/* Discarded function return */
			DECL_SPEC ds;
			IDENTIFIER id = DEREF_id(exp_func_id_id(e));
			if (IS_id_token(id)) {
				id = DEREF_id(id_token_alt(id));
			}
			ds = DEREF_dspec(id_storage(id));
			if (!(ds & dspec_ignore)) {
				ERROR err = ERR_expr_call_func(id);
				ERROR err2 = ERR_stmt_expr_discard_func();
				err = concat_error(err, err2);
				report(crt_loc, err);
			}
			break;
		}
		default:
			/* Discarded value */
			report(crt_loc, ERR_stmt_expr_discard_val());
			return 1;
		}
	}
	return 0;
}


/*
    CONSTRUCT AN EXPRESSION STATEMENT

    This routine constructs an expression statement from the expression e.
    This is basically an identity operation, however various reachability
    and discarded value checks (which need to take account of certain
    special forms) are applied.
*/

EXP
make_exp_stmt(EXP e)
{
	TYPE t;

	/* Perform operand conversion */
	if (IS_NULL_exp(e)) {
		return e;
	}
	e = convert_reference(e, REF_NORMAL);
	made_temporary = NULL_id;
	e = make_discard_exp(e);

	/* Check the type of e */
	t = DEREF_type(exp_type(e));
	switch (TAG_type(t)) {
	case type_bottom_tag:
		/* Unreached code */
		unreached_code = 1;
		return e;
	case type_top_tag:
	case type_error_tag:
		/* No effect */
		return e;
	case type_token_tag:
		/* Check for template types */
		if (is_templ_type(t)) {
			MAKE_exp_op(t, lex_discard, e, NULL_exp, e);
			return e;
		}
		break;
	}

	/* Check discarded value */
	if (check_discard_exp(e)) {
		MAKE_exp_cast(type_void, CONV_ELLIPSIS, e, e);
	}
	return e;
}


/*
    CURRENT CONDITION

    This value is used to hold an indicating of the value of the condition
    in the current conditional or iteration statement.  There are four
    possible values corresponding to true, false and interminate constant
    conditions, plus non-constant conditions.
*/

unsigned crt_condition = BOOL_INVALID;


/*
    CHECK A CONDITION

    This routine converts the condition expression cond to a boolean,
    including setting the value of crt_condition.  Note that the condition
    can be a condition declaration or the null expression (indicating an
    absent condition in a for-statement).  In the former case the
    declaration is returned via pd.  op denotes the context for the
    condition (an if-statement etc.).
*/

EXP
check_cond(EXP cond, EXP *pd, int op)
{
	EXP c;
	TYPE tc;
	unsigned ca;
	unsigned cc;
	unsigned tag;
	EXP a = NULL_exp;
	ERROR err = NULL_err;

	/* Check for null expressions */
	if (IS_NULL_exp(cond)) {
		c = make_bool_exp(BOOL_TRUE, exp_int_lit_tag);
		crt_condition = BOOL_TRUE;
		if (record_location && op != lex_cond_Hop) {
			/* Mark position of condition */
			TYPE t = DEREF_type(exp_type(c));
			MAKE_exp_location(t, crt_loc, c, c);
		}
		return c;
	}

	/* Check for condition declarations */
	tag = TAG_exp(cond);
	if (tag == exp_paren_tag) {
		TYPE t;
		DESTROY_exp_paren(destroy, t, cond, cond);
		UNUSED(t);
	}
	if (IS_exp_decl_stmt(cond)) {
		DECL_SPEC ds;
		IDENTIFIER id;
		*pd = cond;
		do {
			/* Step over temporary variables */
			id = DEREF_id(exp_decl_stmt_id(cond));
			cond = DEREF_exp(exp_decl_stmt_body(cond));
		} while (IS_exp_decl_stmt(cond));
		ds = DEREF_dspec(id_storage(id));
		if (IS_id_variable(id) && !(ds & dspec_temp)) {
			/* This doesn't count as a use of id */
			EXP b = DEREF_exp(id_variable_init(id));
			TYPE t = DEREF_type(id_variable_type(id));
			if (!IS_NULL_exp(b)) {
				if (!IS_type_compound(t)) {
					/* Condition value is used in constant
					 * checks */
					a = convert_boolean(b, exp_paren_tag,
							    KILL_err);
				}
				if (op == lex_while || op == lex_for) {
					/* Move initialisation into loop
					 * condition */
					MAKE_exp_init(t, id, b, cond);
					COPY_exp(id_variable_init(id),
						 NULL_exp);
					ds |= dspec_explicit;
					COPY_dspec(id_storage(id), ds);
				} else {
					MAKE_exp_identifier(t, id, qual_none,
							    cond);
				}
			} else {
				MAKE_exp_identifier(t, id, qual_none, cond);
			}
		}
	}

	/* Convert the condition to a boolean */
	c = convert_reference(cond, REF_NORMAL);
	tc = DEREF_type(exp_type(c));
	ca = type_category(&tc);
	if (IS_TYPE_CLASS(ca)) {
		/* Allow for conversion functions */
		c = convert_conv(type_bool, c, &err, CAST_IMPLICIT);
	} else if (IS_TYPE_TEMPL(ca)) {
		/* Allow for template parameters */
		MAKE_exp_op(type_bool, op, c, NULL_exp, c);
	} else {
		/* Simple conversions */
		c = convert_lvalue(c);
		c = convert_boolean(c, tag, &err);
	}
	if (!IS_NULL_err(err)) {
		ERROR err2;
		switch (op) {
		case lex_if:
			err2 = ERR_stmt_if_cond();
			break;
		case lex_do:
			err2 = ERR_stmt_do_cond();
			break;
		case lex_for:
			err2 = ERR_stmt_for_cond();
			break;
		case lex_while:
			err2 = ERR_stmt_while_cond();
			break;
		case lex_cond_Hop:
			err2 = ERR_expr_cond_bool();
			break;
		default:
			err2 = NULL_err;
			break;
		}
		err = concat_error(err, err2);
		report(crt_loc, err);
	}

	/* Check for constant conditions */
	if (IS_NULL_exp(a)) {
		a = c;
	}
	cc = eval_const_cond(a);
	if (cc != BOOL_INVALID) {
		if (op == lex_if) {
			/* Report determinate constants in if statements */
			if (cc != BOOL_UNKNOWN) {
				report(crt_loc, ERR_stmt_if_const());
			}
		} else if (op == lex_cond_Hop) {
			/* Similarly for conditional expressions */
			if (cc != BOOL_UNKNOWN) {
				report(crt_loc, ERR_expr_cond_const());
			}
		} else {
			/* Report non-literal constants in iteration
			 * statements */
			if (!is_literal(a)) {
				ERROR err2;
				switch (op) {
				case lex_do:
					err2 = ERR_stmt_do_const();
					break;
				case lex_for:
					err2 = ERR_stmt_for_const();
					break;
				case lex_while:
					err2 = ERR_stmt_while_const();
					break;
				default:
					err2 = NULL_err;
					break;
				}
				report(crt_loc, err2);
			}
		}
	}
	crt_condition = cc;
	if (record_location && op != lex_cond_Hop) {
		/* Mark position of condition */
		TYPE t = DEREF_type(exp_type(c));
		MAKE_exp_location(t, crt_loc, c, c);
	}
	return c;
}


/*
    CHECK A CONDITIONAL BODY

    This routine is called following a conditional or loop statement
    (given by op) to check for suspicious empty bodies which may be
    due to a misplaced semicolon.
*/

void
check_empty_stmt(int op)
{
	if (!suppress_quality) {
		int t = crt_lex_token;
		if (t == lex_semicolon) {
			PPTOKEN *p = crt_token;
			NAMESPACE ns = crt_lookup;
			t = next_token();
			if (t == lex_open_Hbrace_H1) {
				/* Have 'op ; {', probably mean 'op {' */
				report(crt_loc, ERR_stmt_stmt_empty(op));
			}
			crt_lookup = ns;
			crt_token = p;
		}
	}
	return;
}


/*
    CREATE A CONDITION DECLARATION

    This routine combines the condition declaration d with its associated
    condition e.  If tmp is true a temporary variable is introduced for
    the value of e.
*/

static EXP
make_cond_decl(EXP d, EXP e, int tmp)
{
	EXP b;
	EXP c = d;
	if (tmp) {
		/* Introduce temporary variable */
		ERROR err = NULL_err;
		TYPE t = DEREF_type(exp_type(e));
		e = make_temporary(t, e, NULL_exp, 0, &err);
		if (!IS_NULL_err(err)) {
			report(crt_loc, err);
		}
	}
	for (;;) {
		b = DEREF_exp(exp_decl_stmt_body(c));
		if (!IS_exp_decl_stmt(b)) {
			break;
		}
		c = b;
	}
	if (IS_exp_sequence(b)) {
		free_exp(b, 0);
	}
	COPY_exp(exp_decl_stmt_body(c), e);
	set_parent_stmt(e, c);
	if (tmp) {
		/* Result is contents of temporary variable */
		e = make_id_exp(made_temporary);
		e = convert_reference(e, REF_NORMAL);
		e = convert_lvalue(e);
		d = join_exp(d, e);
	}
	return d;
}


/*
    FIND A CONDITIONAL STATEMENT

    This routine finds the conditional statement associated with e.
    e may contain an enclosing condition declaration.
*/

static EXP
find_cond_stmt(EXP e)
{
	unsigned tag = TAG_exp(e);
	while (tag == exp_decl_stmt_tag) {
		e = DEREF_exp(exp_decl_stmt_body(e));
		tag = TAG_exp(e);
	}
	while (tag == exp_sequence_tag) {
		LIST(EXP)p = DEREF_list(exp_sequence_first(e));
		p = TAIL_list(p);
		e = DEREF_exp(HEAD_list(p));
		tag = TAG_exp(e);
		if (tag == exp_location_tag) {
			e = DEREF_exp(exp_location_arg(e));
			tag = TAG_exp(e);
		}
	}
	return e;
}


/*
    BEGIN AN IF STATEMENT

    This routine begins the construction of an if statement with condition
    cond.  In this and all routines involving a condition, a constant true
    condition is replaced by the null expression.
*/

EXP
begin_if_stmt(EXP cond)
{
	EXP e;
	EXP d = NULL_exp;
	EXP b = begin_label_stmt(NULL_id, lex_if);
	IDENTIFIER lab = DEREF_id(exp_label_stmt_label(b));

	/* Check the condition */
	cond = check_cond(cond, &d, lex_if);
	if (crt_condition == BOOL_FALSE) {
		unreached_code = 1;
	}

	/* Construct the result */
	MAKE_exp_if_stmt(type_void, cond, NULL_exp, NULL_exp, lab, e);
	check_empty_stmt(lex_if);
	set_parent_stmt(b, e);
	if (!IS_NULL_exp(d)) {
		e = make_cond_decl(d, e, 0);
	}
	return e;
}


/*
    CONTINUE AN IF STATEMENT

    This routine continues the construction of an if statement by adding
    the statement, right, which is evaluated if the condition is true.
    This is called just before any else clause is processed.
*/

EXP
cont_if_stmt(EXP prev, EXP right)
{
	/* Do unreached code analysis */
	EXP e;
	if (crt_condition == BOOL_TRUE) {
		unreached_code = 1;
	} else {
		unreached_code = unreached_prev;
	}

	/* Copy the right code into the conditional */
	e = find_cond_stmt(prev);
	COPY_exp(exp_if_stmt_true_code(e), right);
	set_parent_stmt(right, e);
	return prev;
}


/*
    COMPLETE AN IF STATEMENT

    This routine completes the construction of an if statement by adding
    the statement, wrong, which is evaluated if the condition is false.
*/

EXP
end_if_stmt(EXP prev, EXP wrong)
{
	/* Do unreached code analysis */
	EXP e = find_cond_stmt(prev);
	EXP right = DEREF_exp(exp_if_stmt_true_code(e));
	if (is_bottom(wrong)) {
		if (is_bottom(right)) {
			/* Don't reach the end of either branch */
			COPY_type(exp_type(prev), type_bottom);
			COPY_type(exp_type(e), type_bottom);
			unreached_code = 1;
		} else if (crt_condition == BOOL_FALSE) {
			/* Don't reach the end of the taken branch */
			COPY_type(exp_type(e), type_bottom);
			unreached_code = 1;
		} else {
			/* Reach the end of one branch */
			unreached_code = unreached_prev;
		}
	} else if (is_bottom(right)) {
		if (crt_condition == BOOL_TRUE) {
			/* Don't reach the end of the taken branch */
			COPY_type(exp_type(prev), type_bottom);
			COPY_type(exp_type(e), type_bottom);
			unreached_code = 1;
		} else {
			/* Reach the end of one branch */
			unreached_code = unreached_prev;
		}
	} else {
		/* Reach the end of both branches */
		unreached_code = unreached_prev;
	}

	/* Copy the wrong code into the conditional */
	COPY_exp(exp_if_stmt_false_code(e), wrong);
	set_parent_stmt(wrong, e);
	return prev;
}


/*
    STACK OF CURRENTLY ACTIVE ITERATION AND SWITCH STATEMENTS

    This stack is used to record a nested list of iteration and switch
    statements in order to determine which statement a break, continue,
    case or default refers to.
*/

STACK(EXP) crt_loop_stack = NULL_stack(EXP);


/*
    BEGIN A DO STATEMENT

    This routine begins the construction of a do statement.
*/

EXP
begin_do_stmt(void)
{
	EXP e;

	/* Construct the break and continue destinations */
	EXP bk = begin_label_stmt(NULL_id, lex_break);
	EXP cn = begin_label_stmt(NULL_id, lex_continue);
	EXP lp = begin_label_stmt(NULL_id, lex_do);
	IDENTIFIER bk_lab = DEREF_id(exp_label_stmt_label(bk));
	IDENTIFIER cn_lab = DEREF_id(exp_label_stmt_label(cn));
	IDENTIFIER lp_lab = DEREF_id(exp_label_stmt_label(lp));

	/* Construct the do statement */
	MAKE_exp_do_stmt(type_void, NULL_exp, bk_lab, cn_lab, lp_lab, e);
	set_parent_stmt(bk, e);
	set_parent_stmt(cn, e);
	set_parent_stmt(lp, e);

	/* Add statement to loop stack */
	PUSH_exp(e, crt_loop_stack);
	return e;
}


/*
    COMPLETE A DO STATEMENT

    This routine completes the construction of the do statement prev
    using the statement body and the condition cond.
*/

EXP
end_do_stmt(EXP prev, EXP body, EXP cond)
{
	int uc;
	IDENTIFIER bk;
	EXP d = NULL_exp;

	/* Remove statement from loop stack */
	EXP e;
	POP_exp(e, crt_loop_stack);
	UNUSED(e);

	/* Convert the condition to a boolean */
	cond = check_cond(cond, &d, lex_do);
	if (!IS_NULL_exp(d)) {
		cond = make_cond_decl(d, cond, 1);
	}

	/* Find whether the condition is reached */
	uc = unreached_code;
	if (uc) {
		IDENTIFIER cn = DEREF_id(exp_do_stmt_cont_lab(prev));
		if (used_label(cn) == 1) {
			/* Reached using a continue */
			uc = unreached_prev;
		} else {
			/* Report unreached code */
			if (!unreached_last) {
				report(crt_loc, ERR_stmt_stmt_unreach());
				unreached_last = 1;
			}
		}
	}

	/* Find whether the following statement is reached */
	bk = DEREF_id(exp_do_stmt_break_lab(prev));
	COPY_loc(id_loc(bk), crt_loc);
	if (crt_condition == BOOL_TRUE) {
		uc = 1;
	}
	if (uc) {
		if (used_label(bk) == 1) {
			/* Can reach next statement using break */
			uc = unreached_prev;
		} else {
			COPY_type(exp_type(prev), type_bottom);
		}
	}
	unreached_code = uc;

	/* Fill in the gaps in the do statement */
	COPY_exp(exp_do_stmt_cond(prev), cond);
	COPY_exp(exp_do_stmt_body(prev), body);
	set_parent_stmt(body, prev);
	return prev;
}


/*
    BEGIN A FOR STATEMENT

    The construction of a for statement is in four stages, given by the
    following four routines.  A statement of the form:

		    for ( init ; cond ; step ) body ;

    is translated to:

		    {
			init ;
			while ( cond ) {
			    body ;
			    cn : step ;
			}
		    }

    where an absent cond is replaced by 'true', except that 'continue' is
    mapped to 'goto cn' (for the pre-ISO scoping rules the outer braces
    do not form a scope - or rather they don't until after the init).
    This routine, begin_for_stmt, creates the initial compound statement.
    The next, init_for_stmt, adds init to this compound.  The third,
    cond_for_stmt, creates the while loop from cond and body.  Finally
    end_for_stmt fills in the body and completes the construction.
*/

EXP
begin_for_stmt(void)
{
	EXP e;
	int scope = 0;
	if (option(OPT_for_scope) == OPTION_ON) {
		scope = 1;
	}
	e = begin_compound_stmt(scope);
	return e;
}


/*
    ADD AN INITIAL STATEMENT TO A FOR STATEMENT

    This routine adds the initial statement pointed to by init to the for
    statement prev (see above).  If the initial statement is a declaration
    then the declaration statement is only created during this routine
    (init is the null expression).  In this case init is set to point to
    the declaration statement created.
*/

EXP
init_for_stmt(EXP prev, EXP *init)
{
	EXP stmt = *init;
	NAMESPACE ns = DEREF_nspace(exp_sequence_decl(prev));
	if (!IS_NULL_nspace(ns)) {
		/* Add any declarations to the block */
		MEMBER p = DEREF_member(nspace_last(ns));
		MEMBER q = DEREF_member(nspace_prev(ns));
		if (!EQ_member(p, q)) {
			/* Create declaration statement */
			int vars = 0;
			EXP decl = make_decl_stmt(p, q, &vars);
			prev = extend_compound_stmt(prev, decl, 0);
			COPY_member(nspace_prev(ns), p);
			*init = decl;
		}
	} else {
		/* Defer declarations to enclosing block */
		NAMESPACE cns = crt_namespace;
		ns = make_namespace(crt_func_id, nspace_block_tag, 0);
		push_namespace(ns);
		if (do_scope) {
			dump_begin_scope(NULL_id, ns, cns, &crt_loc);
		}
		COPY_nspace(exp_sequence_decl(prev), ns);
		IGNORE incr_value(OPT_VAL_statement_depth);
	}
	if (!IS_NULL_exp(stmt)) {
		/* Add the new statement */
		prev = extend_compound_stmt(prev, stmt, 1);
	}
	adjusted_line = 0;
	return prev;
}


/*
    ADD A CONDITION TO A FOR STATEMENT

    This routine adds the condition and step statements, cond and step, to
    the for statement prev (see above).  Note that cond is wrapped in a
    location expression.
*/

EXP
cond_for_stmt(EXP prev, EXP cond, EXP step)
{
	EXP e;
	TYPE t;
	LOCATION loc;
	EXP d = NULL_exp;

	/* Construct the break and continue destinations */
	EXP bk = begin_label_stmt(NULL_id, lex_break);
	EXP cn = begin_label_stmt(NULL_id, lex_continue);
	EXP lp = begin_label_stmt(NULL_id, lex_for);
	IDENTIFIER bk_lab = DEREF_id(exp_label_stmt_label(bk));
	IDENTIFIER cn_lab = DEREF_id(exp_label_stmt_label(cn));
	IDENTIFIER lp_lab = DEREF_id(exp_label_stmt_label(lp));

	/* Convert condition to a boolean */
	bad_crt_loc++;
	loc = crt_loc;
	DESTROY_exp_location(destroy, t, crt_loc, cond, cond);
	cond = check_cond(cond, &d, lex_for);
	if (crt_condition == BOOL_FALSE) {
		unreached_code = 1;
	}
	crt_loc = loc;
	bad_crt_loc--;
	UNUSED(t);

	/* Deal with the step statement */
	if (!IS_NULL_exp(step)) {
		if (record_location) {
			t = DEREF_type(exp_type(step));
			MAKE_exp_location(t, stmt_loc, step, step);
		}
		IGNORE end_label_stmt(cn, step);
	}

	/* Construct the while statement */
	MAKE_exp_while_stmt(type_void, cond, bk_lab, cn_lab, lp_lab, e);
	set_parent_stmt(bk, e);
	set_parent_stmt(cn, e);
	set_parent_stmt(lp, e);
	check_empty_stmt(lex_for);

	/* Add statement to loop stack */
	PUSH_exp(e, crt_loop_stack);

	/* Add to for statement */
	if (!IS_NULL_exp(d)) {
		EXP c = d;
		LIST(IDENTIFIER) cids = NULL_list(IDENTIFIER);
		while (!IS_NULL_exp(c) && IS_exp_decl_stmt(c)) {
			IDENTIFIER cid = DEREF_id(exp_decl_stmt_id(c));
			CONS_id(cid, cids, cids);
			c = DEREF_exp(exp_decl_stmt_body(c));
		}
		COPY_list(exp_while_stmt_cond_id(e), cids);
		d = make_cond_decl(d, e, 0);
		e = d;
	}
	e = add_compound_stmt(prev, e);
	return e;
}


/*
    END A FOR STATEMENT

    This routine completes the construction of the for statement prev by
    adding the body statement, body (see above).
*/

EXP
end_for_stmt(EXP prev, EXP body)
{
	TYPE t;
	LIST(EXP) stmts = DEREF_list(exp_sequence_last(prev));
	EXP stmt = DEREF_exp(HEAD_list(stmts));
	if (IS_exp_location(stmt)) {
		EXP e = DEREF_exp(exp_location_arg(stmt));
		e = end_while_stmt(e, body);
		t = DEREF_type(exp_type(e));
		COPY_exp(exp_location_arg(stmt), e);
	} else {
		EXP e = end_while_stmt(stmt, body);
		t = DEREF_type(exp_type(e));
		COPY_exp(HEAD_list(stmts), e);
	}
	prev = end_compound_stmt(prev);
	COPY_type(exp_type(prev), t);

	/* Mark for-init variables as private */
	if (option(OPT_for_scope) == OPTION_WARN) {
		NAMESPACE ns = crt_namespace;
		MEMBER p = DEREF_member(nspace_last(ns));
		MEMBER q = DEREF_member(nspace_prev(ns));
		while (!EQ_member(p, q)) {
			IDENTIFIER id = DEREF_id(member_id(p));
			if (!IS_NULL_id(id) && IS_id_variable(id)) {
				DECL_SPEC ds = DEREF_dspec(id_storage(id));
				if (ds & dspec_auto) {
					ds |= dspec_private;
					COPY_dspec(id_storage(id), ds);
				}
			}
			p = DEREF_member(member_next(p));
		}
	}
	return prev;
}


/*
    BEGIN A WHILE STATEMENT

    This routine begins the construction of a while statement with
    condition cond.
*/

EXP
begin_while_stmt(EXP cond)
{
	EXP e;
	EXP d = NULL_exp;

	/* Construct the break and continue destinations */
	EXP bk = begin_label_stmt(NULL_id, lex_break);
	EXP cn = begin_label_stmt(NULL_id, lex_continue);
	EXP lp = begin_label_stmt(NULL_id, lex_while);
	IDENTIFIER bk_lab = DEREF_id(exp_label_stmt_label(bk));
	IDENTIFIER cn_lab = DEREF_id(exp_label_stmt_label(cn));
	IDENTIFIER lp_lab = DEREF_id(exp_label_stmt_label(lp));

	/* Convert the condition to a boolean */
	cond = check_cond(cond, &d, lex_while);
	if (crt_condition == BOOL_FALSE) {
		unreached_code = 1;
	}

	/* Construct the while statement */
	MAKE_exp_while_stmt(type_void, cond, bk_lab, cn_lab, lp_lab, e);
	set_parent_stmt(bk, e);
	set_parent_stmt(cn, e);
	set_parent_stmt(lp, e);
	check_empty_stmt(lex_while);

	/* Add statement to loop stack */
	PUSH_exp(e, crt_loop_stack);

	/* Allow for condition declarations */
	if (!IS_NULL_exp(d)) {
		EXP c = d;
		LIST(IDENTIFIER) cids = NULL_list(IDENTIFIER);
		while (!IS_NULL_exp(c) && IS_exp_decl_stmt(c)) {
			IDENTIFIER cid = DEREF_id(exp_decl_stmt_id(c));
			CONS_id(cid, cids, cids);
			c = DEREF_exp(exp_decl_stmt_body(c));
		}
		COPY_list(exp_while_stmt_cond_id(e), cids);
		d = make_cond_decl(d, e, 0);
		e = d;
	}
	return e;
}


/*
    COMPLETE A WHILE STATEMENT

    This routine completes the construction of the while statement prev
    using the statement body.
*/

EXP
end_while_stmt(EXP prev, EXP body)
{
	/* Remove statement from loop stack */
	EXP e;
	IDENTIFIER bk;
	POP_exp(e, crt_loop_stack);
	UNUSED(e);

	/* Find whether the end of the body is reached */
	e = find_cond_stmt(prev);
	if (unreached_code) {
		IDENTIFIER cn = DEREF_id(exp_while_stmt_cont_lab(e));
		if (used_label(cn) == 1) {
			/* Reached using a continue */
			unreached_code = unreached_prev;
		} else {
			/* Check for unreached continuation statement */
			LIST(EXP) step;
			EXP cont = DEREF_exp(id_label_stmt(cn));
			cont = DEREF_exp(exp_label_stmt_body(cont));
			step = DEREF_list(exp_sequence_first(cont));
			step = TAIL_list(step);
			if (!IS_NULL_list(step)) {
				LOCATION loc;
				DEREF_loc(id_loc(cn), loc);
				report(loc, ERR_stmt_stmt_unreach());
			}
		}
	}

	/* Find whether the following statement is reached */
	bk = DEREF_id(exp_while_stmt_break_lab(e));
	COPY_loc(id_loc(bk), crt_loc);
	unreached_code = unreached_prev;
	if (crt_condition == BOOL_TRUE) {
		if (used_label(bk) != 1) {
			/* Infinite loop and no breaks */
			COPY_type(exp_type(prev), type_bottom);
			COPY_type(exp_type(e), type_bottom);
			unreached_code = 1;
		}
	}

	/* Copy the body into the result */
	COPY_exp(exp_while_stmt_body(e), body);
	set_parent_stmt(body, e);
	return prev;
}


/*
    CONSTRUCT A BREAK STATEMENT

    This routine constructs a break statement.  Note that this must appear
    inside an iteration or a switch statement.  It is implemented as a jump
    to the break label.
*/

EXP
make_break_stmt(void)
{
	LIST(EXP) st = LIST_stack(crt_loop_stack);
	if (!IS_NULL_list(st)) {
		IDENTIFIER lab;
		EXP stmt = DEREF_exp(HEAD_list(st));
		unsigned tag = TAG_exp(stmt);
		if (tag == exp_while_stmt_tag) {
			lab = DEREF_id(exp_while_stmt_break_lab(stmt));
		} else if (tag == exp_do_stmt_tag) {
			lab = DEREF_id(exp_do_stmt_break_lab(stmt));
		} else {
			lab = DEREF_id(exp_switch_stmt_break_lab(stmt));
		}
		return make_jump_stmt(lab, stmt);
	}
	report(crt_loc, ERR_stmt_break_bad());
	return NULL_exp;
}


/*
    CONSTRUCT A CONTINUE STATEMENT

    This routine constructs a continue statement.  Note that this must
    appear inside an iteration statement.  It is implemented as a jump to
    the continue label.
*/

EXP
make_continue_stmt(void)
{
	LIST(EXP) st = LIST_stack(crt_loop_stack);
	while (!IS_NULL_list(st)) {
		EXP stmt = DEREF_exp(HEAD_list(st));
		unsigned tag = TAG_exp(stmt);
		if (tag == exp_switch_stmt_tag) {
			/* Switch statements don't count for continues */
			/* EMPTY */
		} else {
			/* Find continue destination label */
			IDENTIFIER lab;
			if (tag == exp_while_stmt_tag) {
				lab = DEREF_id(exp_while_stmt_cont_lab(stmt));
			} else {
				lab = DEREF_id(exp_do_stmt_cont_lab(stmt));
			}
			return make_jump_stmt(lab, stmt);
		}
		st = TAIL_list(st);
	}
	report(crt_loc, ERR_stmt_cont_bad());
	return NULL_exp;
}


/*
    CHECK A RETURN EXPRESSION

    This routine checks the return expression a.  In particular returning
    a reference to a local variable is detected.  It is also used to check
    a throw expression (as indicated by op).
*/

EXP
check_return_exp(EXP a, int op)
{
    if (option(OPT_ptr_operator)) {
	EXP b = NULL_exp;
	DECL_SPEC ds = find_exp_linkage(a, &b, 1);
	if (ds & dspec_auto) {
	    if (IS_exp_identifier(b)) {
		IDENTIFIER id = DEREF_id(exp_identifier_id(b));
		if (IS_id_variable(id)) {
		    TYPE t = DEREF_type(id_variable_type(id));
		    if (!IS_type_ref(t)) {
			report(crt_loc, ERR_stmt_return_auto(id, op));
		    }
		}
	    }
	}
    }
    return a;
}


/*
    CONSTRUCT A RETURN EXPRESSION

    This routine constructs the value for the statement 'return a'.  a can
    be the null expression to indicate a plain 'return'.  op is lex_return
    to indicate explicit returns rather than the implicit return at the
    end of the function.  If the return is via a jump then the label is
    assigned to lab.
*/

EXP
find_return_exp(EXP a, IDENTIFIER *lab, int op)
{
	TYPE r = crt_func_return;
	if (!IS_NULL_exp(a)) {
		/* Apply reference conversion */
		a = convert_reference(a, REF_NORMAL);
	}
	if (IS_NULL_type(r)) {
		/* Not in a function definition */
		IDENTIFIER id = crt_func_id;
		report(crt_loc, ERR_token_stmt_ret(id));
		if (IS_NULL_exp(a)) {
			r = type_void;
		} else {
			a = convert_lvalue(a);
			r = DEREF_type(exp_type(a));
		}
	}
	switch (TAG_type(r)) {
	case type_top_tag:
		/* Function returns no value */
		if (!IS_NULL_exp(a)) {
			IDENTIFIER id = crt_func_id;
			HASHID nm = DEREF_hashid(id_name(id));
			unsigned tag = TAG_hashid(nm);
			if (tag == hashid_constr_tag) {
				report(crt_loc, ERR_class_ctor_result(id));
			} else if (tag == hashid_destr_tag) {
				report(crt_loc, ERR_class_dtor_result(id));
				*lab = find_postlude_label();
			} else {
				report(crt_loc, ERR_stmt_return_none(id, r));
			}
		}
		if (in_func_handler == 2) {
			/* In function-try-block handler */
			IDENTIFIER id = crt_func_id;
			report(crt_loc, ERR_except_handle_return(id));
		}
		break;
	case type_bottom_tag: {
		/* Function should not return */
		IDENTIFIER id = crt_func_id;
		if (IS_NULL_exp(a)) {
			report(crt_loc, ERR_stmt_return_bottom(id, r));
		} else {
			report(crt_loc, ERR_stmt_return_none(id, r));
		}
		break;
	}
	case type_token_tag:
		/* Check for template types */
		if (is_templ_type(r)) {
			MAKE_exp_op(r, op, a, NULL_exp, a);
			break;
		}
		goto default_lab;
	default:
default_lab:
		/* Function returns a value */
		if (IS_NULL_exp(a)) {
			IDENTIFIER id = crt_func_id;
			if (op == lex_return) {
				/* Explicit return statement */
				report(crt_loc, ERR_stmt_return_void(id, r));
				MAKE_exp_value(r, a);
			} else {
				/* Implicit fall out of function */
				HASHID nm = DEREF_hashid(id_name(id));
				DECL_SPEC ds = DEREF_dspec(id_storage(id));
				if ((ds & dspec_main) && IS_hashid_name(nm)) {
					/* Implicit 'return 0' in main */
					ERROR err =
					    ERR_basic_start_main_fall(id, r);
					report(crt_loc, err);
					MAKE_exp_null(r, a);
				} else {
					report(crt_loc,
					       ERR_stmt_return_fall(id, r));
					MAKE_exp_value(r, a);
				}
			}
		} else {
			/* Convert to result type by initialisation */
			ERROR err = NULL_err;
			a = init_assign(r, cv_none, a, &err);
			if (!IS_NULL_err(err)) {
				/* Bad return type */
				err = init_error(err, 0);
				err = concat_error(err, ERR_stmt_return_conv());
				report(crt_loc, err);
			}
			if (crt_func_complex) {
				a = remove_temporary(a, NULL_exp);
			}
			a = check_return_exp(a, lex_return);
		}
	}
	return a;
}


/*
    CONSTRUCT A RETURN STATEMENT

    This routine constructs the return statement 'return a'.  op is as in
    find_return_exp.
*/

EXP
make_return_stmt(EXP a, int op)
{
	IDENTIFIER lab = NULL_id;
	EXP e = find_return_exp(a, &lab, op);
	if (IS_NULL_id(lab)) {
		/* Construct return statement */
		MAKE_exp_return_stmt(type_bottom, e, e);
	} else {
		/* Jump to postlude label */
		e = make_jump_stmt(lab, NULL_exp);
	}
	unreached_code = 1;
	unreached_last = 0;
	return e;
}


/*
    FALL OUT OF A FUNCTION DEFINITION

    This routine is called at the end of a function definition to check
    the implicit 'return' statement caused by falling out of the function.
*/

EXP
fall_return_stmt(void)
{
	EXP e = NULL_exp;
	if (!unreached_code) {
		TYPE ret = crt_func_return;
		if (!IS_NULL_type(ret) && !IS_type_top(ret)) {
			e = make_return_stmt(NULL_exp, lex_fall);
		}
	}
	return e;
}


/*
    CHECK A SWITCH CONTROL EXPRESSION

    This routine checks the switch control expression cont.  pd is as in
    check_cond and pb is used to return an enumeration or boolean control
    expression.
*/

EXP
check_control(EXP cont, EXP *pd, EXP *pb)
{
	TYPE t;
	int ok = 1;
	unsigned c;
	EXP a = NULL_exp;

	/* Check for condition declarations */
	if (IS_exp_decl_stmt(cont)) {
		IDENTIFIER id = DEREF_id(exp_decl_stmt_id(cont));
		if (IS_id_variable(id)) {
			*pd = cont;
			t = DEREF_type(id_variable_type(id));
			a = DEREF_exp(id_variable_init(id));
			/* This doesn't count as a use of id */
			MAKE_exp_identifier(t, id, qual_none, cont);
		}
	}

	/* Apply reference conversions to control */
	cont = convert_reference(cont, REF_NORMAL);
	t = DEREF_type(exp_type(cont));
	c = type_category(&t);
	if (IS_TYPE_INT(c)) {
		/* Integral types are allowed */
		/* EMPTY */
	} else if (IS_TYPE_TEMPL(c)) {
		/* Allow for template parameters */
		MAKE_exp_op(t, lex_switch, cont, NULL_exp, cont);
		ok = 0;
	} else {
		/* Allow for overloading */
		ok = 0;
		if (IS_TYPE_CLASS(c)) {
			ERROR err = NULL_err;
			a = convert_gen(CTYPE_INT, cont, &err);
			if (!IS_NULL_exp(a)) {
				if (!IS_NULL_err(err)) {
					err = concat_error(err, ERR_stmt_switch_conv());
					report(crt_loc, err);
				}
				cont = a;
				t = DEREF_type(exp_type(cont));
				c = type_category(&t);
				ok = 1;
			}
		}
		if (!ok && !IS_TYPE_ERROR(c)) {
			report(crt_loc, ERR_stmt_switch_control(t));
		}
	}

	/* Promote control construct */
	if (ok) {
		if (IS_TYPE_ADDRESS(c)) {
			cont = convert_lvalue(cont);
			t = DEREF_type(exp_type(cont));
		}
		if (IS_NULL_exp(a)) {
			a = cont;
		}
		if (is_const_exp(a, -1)) {
			/* Report constant control expressions */
			report(crt_loc, ERR_stmt_switch_const());
		}
		if (IS_type_enumerate(t) || check_int_type(t, btype_bool)) {
			/* Store enumeration control expression */
			*pb = cont;
		}
		t = promote_type(t);
		cont = convert_promote(t, cont);
		if (record_location) {
			/* Mark position of control expression */
			MAKE_exp_location(t, crt_loc, cont, cont);
		}
	}
	return cont;
}


/*
    BEGIN A SWITCH STATEMENT

    This routine begins the construction of a switch statement with
    controlling expression cont.  During construction an enumeration or
    boolean control expression is held in the body field.
*/

EXP
begin_switch_stmt(EXP cont)
{
	EXP e;
	EXP d = NULL_exp;
	EXP body = NULL_exp;
	EXP bk = begin_label_stmt(NULL_id, lex_break);
	IDENTIFIER bk_lab = DEREF_id(exp_label_stmt_label(bk));
	cont = check_control(cont, &d, &body);
	MAKE_exp_switch_stmt(type_void, cont, body, 0, bk_lab, e);
	check_empty_stmt(lex_switch);

	/* Add statement to loop stack */
	PUSH_exp(e, crt_loop_stack);

	/* Allow for condition declarations */
	if (!IS_NULL_exp(d)) {
		e = make_cond_decl(d, e, 0);
	}

	/* The following statement is never reached */
	unreached_code = 1;
	unreached_last = 0;
	unreached_fall = 1;
	return e;
}


/*
    DOES A VALUE APPEAR IN A CASE LIST?

    This routine checks whether the integer constant n appears in the list
    of cases p.  If so it returns the label corresponding to the case
    statement drawn from the list of labels q.
*/

IDENTIFIER
find_case(LIST(NAT) p, LIST(IDENTIFIER) q, NAT n)
{
	while (!IS_NULL_list(p)) {
		NAT m = DEREF_nat(HEAD_list(p));
		if (EQ_nat(n, m) || eq_nat(n, m)) {
			IDENTIFIER lab = DEREF_id(HEAD_list(q));
			return lab;
		}
		q = TAIL_list(q);
		p = TAIL_list(p);
	}
	return NULL_id;
}


/*
    COMPLETE A SWITCH STATEMENT

    This routine completes the construction of the switch statement prev
    using the statement body.  exhaust is true if the switch statement
    is declared to be exhaustive.
*/

EXP
end_switch_stmt(EXP prev, EXP body, int exhaust)
{
	EXP bk;
	EXP cont;
	EXP stmt;
	unsigned ncases;
	IDENTIFIER bk_lab;
	LIST(NAT) cases;
	IDENTIFIER default_lab;
	LIST(IDENTIFIER) case_labs;

	/* Remove statement from loop stack */
	EXP e;
	POP_exp(e, crt_loop_stack);
	UNUSED(e);

	/* Copy the body into the result */
	stmt = find_cond_stmt(prev);
	cont = DEREF_exp(exp_switch_stmt_body(stmt));
	bk_lab = DEREF_id(exp_switch_stmt_break_lab(stmt));
	bk = DEREF_exp(id_label_stmt(bk_lab));
	if (!unreached_code) {
		/* Add break statement to end if necessary */
		if (!IS_NULL_exp(body) && IS_exp_sequence(body)) {
			EXP b = make_jump_stmt(bk_lab, stmt);
			body = add_compound_stmt(body, b);
		}
	}
	MAKE_exp_solve_stmt(type_void, body, e);
	CONS_exp(e, all_solve_stmts, all_solve_stmts);
	COPY_exp(exp_solve_stmt_parent(e), stmt);
	COPY_exp(exp_switch_stmt_body(stmt), e);
	set_parent_stmt(body, e);
	set_parent_stmt(bk, e);

	/* Check lists of cases */
	cases = DEREF_list(exp_switch_stmt_cases(stmt));
	cases = REVERSE_list(cases);
	ncases = LENGTH_list(cases);
	if (ncases == 0) {
		ERROR err;
		if (exhaust) {
			err = ERR_stmt_switch_exhaust_none();
		} else {
			err = ERR_stmt_switch_case_none();
		}
		report(crt_loc, err);
	}
	IGNORE check_value(OPT_VAL_switch_cases,(ulong)ncases);
	COPY_list(exp_switch_stmt_cases(stmt), cases);
	case_labs = DEREF_list(exp_switch_stmt_case_labs(stmt));
	case_labs = REVERSE_list(case_labs);
	COPY_list(exp_switch_stmt_case_labs(stmt), case_labs);

	/* Check default label */
	default_lab = DEREF_id(exp_switch_stmt_default_lab(stmt));
	if (IS_NULL_id(default_lab)) {
		report(crt_loc, ERR_stmt_switch_no_default());
	} else {
		exhaust = 1;
	}

	/* Check switch jumps */
	stmt = solve_switch (stmt);

	/* Check switches on enumerations and booleans */
	if (!IS_NULL_exp(cont) && !exhaust) {
		TYPE t = DEREF_type(exp_type(cont));
		if (IS_type_enumerate(t)) {
			ENUM_TYPE et = DEREF_etype(type_enumerate_defn(t));
			LIST(IDENTIFIER) evals = DEREF_list(etype_values(et));
			exhaust = 1;
			while (!IS_NULL_list(evals)) {
				IDENTIFIER eid = DEREF_id(HEAD_list(evals));
				EXP en = DEREF_exp(id_enumerator_value(eid));
				NAT n = DEREF_nat(exp_int_lit_nat(en));
				IDENTIFIER lid = find_case(cases, case_labs, n);
				if (IS_NULL_id(lid)) {
					report(crt_loc,
					       ERR_stmt_switch_case_enum(eid));
					exhaust = 0;
				}
				evals = TAIL_list(evals);
			}
		} else {
			NAT n = small_nat[BOOL_FALSE];
			IDENTIFIER lid = find_case(cases, case_labs, n);
			if (!IS_NULL_id(lid)) {
				n = small_nat[BOOL_TRUE];
				lid = find_case(cases, case_labs, n);
				if (!IS_NULL_id(lid)) {
					exhaust = 1;
				}
			}
		}
	}

	/* Unreached code analysis */
	if (unreached_code) {
		if (used_label(bk_lab) == 1) {
			/* Can reach the end using break */
			unreached_code = unreached_prev;
		} else if (exhaust) {
			/* All cases covered by switch */
			COPY_type(exp_type(stmt), type_bottom);
			COPY_type(exp_type(prev), type_bottom);
		} else {
			/* Not all cases covered by switch */
			unreached_code = unreached_prev;
		}
	}
	COPY_int(exp_switch_stmt_exhaust(stmt), exhaust);
	return prev;
}


/*
    BEGIN A CASE STATEMENT

    This routine begins the construction of a case statement (or a jump
    to a case statement if jump is true) with labelling value val.  Note
    that a case statement must appear inside a switch statement.
*/

EXP
begin_case_stmt(EXP val, int jump)
{
	/* Search for enclosing switch statement */
	LIST(EXP) st = LIST_stack(crt_loop_stack);
	while (!IS_NULL_list(st)) {
		EXP stmt = DEREF_exp(HEAD_list(st));

		if (IS_exp_switch_stmt(stmt)) {
			/* Switch statement found */
			NAT n;
			EXP e;
			IDENTIFIER lab;
			IDENTIFIER old_lab;
			LIST(NAT) cases;
			ERROR err = NULL_err;
			int uc = unreached_code;
			LIST(IDENTIFIER) lbls;
			unsigned etag = null_tag;
			unsigned tag = TAG_exp(val);
			TYPE ta = DEREF_type(exp_type(val));
			EXP cont = DEREF_exp(exp_switch_stmt_control(stmt));
			TYPE tc = DEREF_type(exp_type(cont));

			/* Cast val to control type */
			while (tag == exp_paren_tag) {
				val = DEREF_exp(exp_paren_arg(val));
				tag = TAG_exp(val);
			}
			if (tag == exp_int_lit_tag) {
				TYPE tb = ta;
				if (IS_type_enumerate(ta)) {
					tb = promote_type(ta);
				}
				etag = DEREF_unsigned(exp_int_lit_etag(val));
				if (!eq_type(tb, tc)) {
					val = make_cast_nat(tc, val, &err,
							    CAST_IMPLICIT);
				}
			}

			/* Check that val is a constant */
			n = make_nat_exp(val, &err);
			if (!IS_NULL_err(err)) {
				err = concat_error(err, ERR_stmt_switch_case_const());
				report(crt_loc, err);
			}

			/* Check whether this value has been used previously */
			lbls = DEREF_list(exp_switch_stmt_case_labs(stmt));
			cases = DEREF_list(exp_switch_stmt_cases(stmt));
			old_lab = find_case(cases, lbls, n);
			if (!IS_NULL_id(old_lab) && !jump) {
				DECL_SPEC info =
				    DEREF_dspec(id_storage(old_lab));
				if ((info & dspec_defn) && !is_error_nat(n)) {
					/* Duplicate case */
					PTR(LOCATION) loc = id_loc(old_lab);
					report(crt_loc, ERR_stmt_switch_case_dup(n, loc));
					old_lab = NULL_id;
				}
			}

			/* Construct the case statement */
			if (jump) {
				e = make_goto_stmt(old_lab);
				lab = DEREF_id(exp_goto_stmt_label(e));
				COPY_int(id_label_op(lab), lex_case);
			} else {
				e = begin_label_stmt(old_lab, lex_case);
				lab = DEREF_id(exp_label_stmt_label(e));
			}
			COPY_exp(id_label_gotos(lab), stmt);
			if (IS_NULL_id(old_lab)) {
				CONS_id(lab, lbls, lbls);
				CONS_nat(n, cases, cases);
				COPY_list(exp_switch_stmt_case_labs(stmt), lbls);
				COPY_list(exp_switch_stmt_cases(stmt), cases);
			}
			if (jump) {
				return e;
			}

			/* Check enumeration switches */
			cont = DEREF_exp(exp_switch_stmt_body(stmt));
			if (!IS_NULL_exp(cont)) {
				int ok = 0;
				TYPE t = DEREF_type(exp_type(cont));
				if (IS_type_enumerate(t)) {
					/* Enumeration switch */
					if (etag == exp_identifier_tag &&
					    eq_type(t, ta)) {
						ok = 1;
					} else {
						ENUM_TYPE et;
						IDENTIFIER eid;
						et = DEREF_etype(type_enumerate_defn(t));
						eid = find_enumerator(et, n);
						if (!IS_NULL_id(eid)) {
							ok = 1;
						}
					}
				} else {
					/* Boolean switch */
					unsigned long v = get_nat_value(n);
					if (v == 0 || v == 1) {
						ok = 1;
					}
				}
				if (!ok && !is_error_nat(n)) {
					err = ERR_stmt_switch_case_extra(n, t);
					report(crt_loc, err);
				}
			}

			/* Check for falling into a case */
			if (!uc && unreached_fall && !suppress_fall) {
				report(crt_loc, ERR_stmt_label_fall(lex_case));
			}
			suppress_fall = 0;
			return e;
		}

		/* Iteration statements are ignored for cases */
		st = TAIL_list(st);
	}
	report(crt_loc, ERR_stmt_label_case());
	return NULL_exp;
}


/*
    COMPLETE A CASE STATEMENT

    This routine completes the construction of the case statement prev
    using the statement body.  This is just a call to end_label_stmt.
*/

EXP
end_case_stmt(EXP prev, EXP body)
{
	return end_label_stmt(prev, body);
}


/*
    BEGIN A DEFAULT STATEMENT

    This routine begins the construction of a default statement (or a jump
    to a default statement if jump is true).  Note that a default statement
    must appear inside a switch statement.
*/

EXP
begin_default_stmt(int jump)
{
	/* Search for enclosing switch statement */
	LIST(EXP) st = LIST_stack(crt_loop_stack);
	while (!IS_NULL_list(st)) {
		EXP stmt = DEREF_exp(HEAD_list(st));

		if (IS_exp_switch_stmt(stmt)) {
			/* Switch statement found */
			EXP e;
			IDENTIFIER lab;
			int uc = unreached_code;

			/* Check for previous default statements */
			lab = DEREF_id(exp_switch_stmt_default_lab(stmt));
			if (!IS_NULL_id(lab) && !jump) {
				DECL_SPEC info = DEREF_dspec(id_storage(lab));
				if (info & dspec_defn) {
					/* Duplicate default statement */
					PTR(LOCATION) loc = id_loc(lab);
					report(crt_loc, ERR_stmt_switch_default_dup(loc));
					lab = NULL_id;
				}
			}

			/* Construct the default statement */
			if (jump) {
				e = make_goto_stmt(lab);
				lab = DEREF_id(exp_goto_stmt_label(e));
				COPY_int(id_label_op(lab), lex_default);
			} else {
				int exhaust;
				exhaust =
				    DEREF_int(exp_switch_stmt_exhaust(stmt));
				if (exhaust) {
					report(crt_loc, ERR_stmt_switch_exhaust_default());
				}
				e = begin_label_stmt(lab, lex_default);
				lab = DEREF_id(exp_label_stmt_label(e));
			}
			COPY_exp(id_label_gotos(lab), stmt);
			COPY_id(exp_switch_stmt_default_lab(stmt), lab);

			/* Check for falling into default */
			if (!jump) {
				if (!uc && unreached_fall && !suppress_fall) {
					report(crt_loc, ERR_stmt_label_fall(lex_default));
				}
				suppress_fall = 0;
			}
			return e;
		}

		/* Iteration statements are ignored for defaults */
		st = TAIL_list(st);
	}
	report(crt_loc, ERR_stmt_label_default());
	return NULL_exp;
}


/*
    COMPLETE A DEFAULT STATEMENT

    This routine completes the construction of the default statement prev
    using the statement body.  This is just a call to end_label_stmt.
*/

EXP
end_default_stmt(EXP prev, EXP body)
{
	return end_label_stmt(prev, body);
}


/*
    CURRENT #IF CONDITION

    This variable is used to keep track of the cummulative target dependent
    condition at any point in the compilation.  It takes the form
    'c1 && c2 && ... && cn' where c1, c2, ..., cn are the target dependent
    conditions currently in scope.  The case n = 0 gives the null expression.
*/

EXP crt_hash_cond = NULL_exp;


/*
    ADD A CONDITION TO A LIST OF CONDITIONS

    This routine adds the condition a to the list of conditions b by
    forming 'b && a'.
*/

EXP
make_if_cond(EXP a, EXP b)
{
	if (!IS_NULL_exp(b)) {
		MAKE_exp_log_and(type_bool, b, a, a);
	}
	return a;
}


/*
    NEGATE THE LAST CONDITION IN A LIST

    This routine negates the last condition in the list of conditions a,
    that is, it maps 'a1 && a2 && ... && an' to 'a1 && a2 && ... && !an'.
*/

EXP
make_else_cond(EXP a)
{
	if (!IS_NULL_exp(a)) {
		if (IS_exp_log_and(a)) {
			EXP b = DEREF_exp(exp_log_and_arg1(a));
			EXP c = DEREF_exp(exp_log_and_arg2(a));
			MAKE_exp_not(type_bool, c, c);
			MAKE_exp_log_and(type_bool, b, c, a);
		} else {
			MAKE_exp_not(type_bool, a, a);
		}
	}
	return a;
}


/*
    BEGIN A #IF STATEMENT

    This routine begins the construction of a #if statement.  cond gives
    the condition, which is already a boolean value.  The case where cond
    is a target independent constant have already been handled by the
    preprocessor.  right gives the code which is evaluated if this condition
    is true.
*/

EXP
begin_hash_if_stmt(EXP cond, EXP right)
{
	/* Construct the result */
	EXP e;
	MAKE_exp_hash_if (type_void, cond, right, NULL_exp, e);
	COPY_exp(exp_hash_if_last(e), e);
	set_parent_stmt(right, e);

	/* Unreached code analysis */
	if (is_bottom(right)) {
		COPY_type(exp_type(e), type_bottom);
	}
	/* Next branch is reached */
	unreached_code = unreached_prev;
	return e;
}


/*
    CONTINUE A #IF STATEMENT

    This routine continues the construction of a #if statement, prev, by
    adding a #elif statement to the condition.  cond gives the condition,
    which is already a boolean value.  The case where cond is a target
    independent constant have already been handled by the preprocessor.
    right gives the code which is evaluated if this condition, and none of
    the previous conditions in prev, is true.
*/

EXP
cont_hash_if_stmt(EXP prev, EXP cond, EXP right)
{
	/* Map '#elif' to '#else #if' */
	EXP e;
	EXP last = DEREF_exp(exp_hash_if_last(prev));
	MAKE_exp_hash_if (type_void, cond, right, NULL_exp, e);
	COPY_exp(exp_hash_if_parent(e), last);
	COPY_exp(exp_hash_if_false_code(last), e);
	COPY_exp(exp_hash_if_last(prev), e);
	set_parent_stmt(right, e);

	/* Unreached code analysis */
	if (!is_bottom(right)) {
		/* Reaching the end of a condition */
		COPY_type(exp_type(prev), type_void);
	}
	/* Next branch is reached */
	unreached_code = unreached_prev;
	return prev;
}


/*
    COMPLETE A #IF STATEMENT

    This routine completes the construction of a #if statement, prev.
    wrong gives the code which is evaluated if none of the conditions in
    prev is true.
*/

EXP
end_hash_if_stmt(EXP prev, EXP wrong)
{
	/* Copy wrong expression into result */
	EXP last = DEREF_exp(exp_hash_if_last(prev));
	COPY_exp(exp_hash_if_false_code(last), wrong);
	set_parent_stmt(wrong, last);

	/* Unreached code analysis */
	if (is_bottom(wrong)) {
		/* Reachability is determined by the previous branches */
		if (is_bottom(prev)) {
			unreached_code = 1;
		} else {
			unreached_code = unreached_prev;
		}
	} else {
		/* End of statement is reached */
		COPY_type(exp_type(prev), type_void);
		unreached_code = unreached_prev;
	}
	return prev;
}


/*
    CREATE A FLOW CONTROL STATEMENT

    This routine creates a flow control statement indicating that the
    statement body is either reached or unreached, depending on the
    value of reach.
*/

EXP
make_reach_stmt(EXP body, int reach)
{
	EXP e;
	TYPE t;
	if (IS_NULL_exp(body)) {
		t = type_void;
	} else {
		unsigned tag = TAG_exp(body);
		if (tag == exp_decl_stmt_tag || tag == exp_label_stmt_tag) {
			/* Don't bother in these cases */
			return body;
		}
		t = DEREF_type(exp_type(body));
	}
	if (reach) {
		MAKE_exp_reach(t, body, e);
	} else {
		MAKE_exp_unreach(t, body, e);
	}
	set_parent_stmt(body, e);
	return e;
}


/*
    CHECK A CONDITION DECLARATION TYPE

    This routine checks the type t of a condition declaration.
*/

TYPE
make_cond_type(TYPE t)
{
	int td = have_type_declaration;
	if (td != TYPE_DECL_NONE) {
		/* Check for type declarations */
		if (td == TYPE_DECL_ELABORATE && found_elaborate_type) {
			/* This is allowed */
			/* EMPTY */
		} else {
			report(crt_loc, ERR_stmt_select_typedef());
		}
	}
	switch (TAG_type(t)) {
	case type_func_tag:
		member_func_type(NULL_ctype, id_variable_tag, t);
		check_weak_func(t, 0);
		report(crt_loc, ERR_stmt_select_type(t));
		MAKE_type_ptr(cv_none, t, t);
		break;
	case type_array_tag:
		report(crt_loc, ERR_stmt_select_type(t));
		t = DEREF_type(type_array_sub(t));
		MAKE_type_ptr(cv_none, t, t);
		break;
	}
	return t;
}


/*
    BEGIN A CONDITION DECLARATION

    Condition declarations are declared in their own local scope and
    brought into the outermost scope of the the statements they control
    using inject_cond.  This routine begins the construction of such a
    local scope.
*/

void
begin_cond(void)
{
	NAMESPACE ns = make_namespace(crt_func_id, nspace_dummy_tag, 0);
	push_namespace(ns);
	return;
}


/*
    END A CONDITION DECLARATION

    This routine ends the local scope for a condition declaration, returning
    a corresponding declaration statement.
*/

EXP
end_cond(void)
{
	int vars = 0;
	NAMESPACE ns = pop_namespace();
	MEMBER p = DEREF_member(nspace_last(ns));
	EXP cond = make_decl_stmt(p, NULL_member, &vars);
	return cond;
}


/*
    INJECT A CONDITION DECLARATION INTO THE CURRENT SCOPE

    This routine injects the condition declaration cond into the current
    scope, prev, returning the result.  It is also used to deal with
    declarations in for-init statements.
*/

EXP
inject_cond(EXP prev, EXP cond)
{
	if (!IS_NULL_exp(cond)) {
		NAMESPACE ns = crt_namespace;
		while (IS_exp_decl_stmt(cond)) {
			IDENTIFIER id = DEREF_id(exp_decl_stmt_id(cond));
			IGNORE redeclare_id(ns, id);
			cond = DEREF_exp(exp_decl_stmt_body(cond));
		}
	}
	return prev;
}


/*
    CONSTRUCT AN ASM STATEMENT

    This routine constructs an asm statement from the string literal
    expression e.  Note that the semantics of asm are totally implementation
    dependent, so anything goes.
*/

EXP
make_asm(EXP e, LIST(EXP) args)
{
	STRING s = DEREF_str(exp_string_lit_str(e));
	if (!IS_NULL_list(args)) {
		report(crt_loc, ERR_dcl_asm_args());
		args = convert_args(args);
	}
	MAKE_exp_assembler(type_void, s, args, e);
	report(crt_loc, ERR_dcl_asm_ti());
	return e;
}
