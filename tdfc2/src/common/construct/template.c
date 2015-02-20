/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdio.h>

#include <shared/check.h>

#include <utility/config.h>
#include "c_types.h"

#include <utility/error.h>
#include <utility/catalog.h>
#include <utility/option.h>
#include <utility/ustring.h>

#include <parse/hash.h>
#include <parse/macro.h>
#include <parse/parse.h>
#include <parse/predict.h>

#include <construct/basetype.h>
#include <construct/check.h>
#include <construct/chktype.h>
#include <construct/class.h>
#include <construct/convert.h>
#include <construct/copy.h>
#include <construct/declare.h>
#include <construct/derive.h>
#include <construct/expression.h>
#include <construct/identifier.h>
#include <construct/initialise.h>
#include <construct/instance.h>
#include <construct/namespace.h>
#include <construct/overload.h>
#include <construct/statement.h>
#include <construct/template.h>
#include <construct/tokdef.h>
#include <construct/token.h>

#include <output/compile.h>
#include <output/dump.h>

#include "ctype_ops.h"
#include "etype_ops.h"
#include "exp_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "inst_ops.h"
#include "itype_ops.h"
#include "member_ops.h"
#include "nat_ops.h"
#include "nspace_ops.h"
#include "off_ops.h"
#include "tok_ops.h"
#include "type_ops.h"
#include "syntax.h"


/*
    This flag can be set to true to indicate that the template argument
    hack, namely mapping '>>' to '> >' at the end of a set of template
    arguments, should be applied.
*/

static int apply_rshift_hack = 0;


/*
    This routine skips a set of template arguments or parameters.  It
    returns the sequence of preprocessing tokens enclosed between the
    initial '<' and the matching closing '>'.
*/

static PPTOKEN *
skip_template(IDENTIFIER id)
{
	PPTOKEN *q;
	LOCATION loc;
	int templ = 0;
	int angles = 1;
	int brackets = 0;
	int t = crt_lex_token;
	PPTOKEN *p = crt_token;
	loc = crt_loc;
	do {
		switch (t) {
		case lex_less:
			/* Open angle brackets */
			if (!brackets && templ) {
				angles++;
			}
			templ = 0;
			break;
		case lex_greater:
			/* Close angle brackets */
			if (!brackets) {
				angles--;
			}
			templ = 0;
			break;
		case lex_rshift:
			/* Map '>>' to '> >' */
			if (!brackets && apply_rshift_hack) {
				PPTOKEN *r = new_pptok();
				r->tok = lex_greater;
				r->next = crt_token->next;
				crt_token->tok = lex_greater;
				crt_token->next = r;
				angles--;
				report(crt_loc, ERR_temp_names_hack());
			}
			templ = 0;
			break;
		case lex_open_Hround:
		case lex_open_Hbrace_H1:
		case lex_open_Hbrace_H2:
		case lex_open_Hsquare_H1:
		case lex_open_Hsquare_H2:
			/* Open brackets */
			brackets++;
			templ = 0;
			break;
		case lex_close_Hround:
		case lex_close_Hbrace_H1:
		case lex_close_Hbrace_H2:
		case lex_close_Hsquare_H1:
		case lex_close_Hsquare_H2:
			/* Close brackets */
			if (brackets) {
				brackets--;
			}
			templ = 0;
			break;
		case lex_identifier:
		case lex_template:
		case lex_const_Hcast:
		case lex_static_Hcast:
		case lex_dynamic_Hcast:
		case lex_reinterpret_Hcast:
			/* These may be followed by '<' */
			/* NOT YET IMPLEMENTED - but are they? */
			templ = 1;
			break;
		case lex_eof:
			/* End of file */
			if (IS_NULL_id(id)) {
				report(loc, ERR_temp_param_eof());
			} else {
				report(loc, ERR_temp_names_eof(id));
			}
			angles = 0;
			break;
		default:
			/* Other tokens */
			templ = 0;
			break;
		}
		q = crt_token;
		t = expand_preproc(EXPAND_AHEAD);
	} while (angles);
	q->tok = lex_close_Htemplate;
	snip_tokens(p, q);
	return p;
}


/*
    This routine skips a set of arguments for the template id.  It is
    entered with the current token equal to the template name preceeding
    the initial '<' if started is false, and equal to the initial '<'
    otherwise.  After skipping the current token is either still the
    template name or the token following the template arguments, depending
    on the value of started.
*/

PPTOKEN *
skip_template_args(IDENTIFIER id, int started)
{
	PPTOKEN *q;
	PPTOKEN *p = crt_token;
	int t = crt_lex_token;
	if (started) {
		/* Patch in dummy preprocessing token */
		q = patch_tokens(1);
		q->tok = t;
		t = lex_ignore_token;
		p->tok = t;
	}
	IGNORE expand_preproc(EXPAND_AHEAD);
	crt_lex_token = lex_open_Htemplate;
	crt_token->tok = lex_open_Htemplate;
	q = skip_template(id);
	crt_lex_token = t;
	crt_token = p;
	if (started) {
		/* Advance to following token */
		ADVANCE_LEXER;
	}
	return q;
}


/*
    This routine parses the template arguments p.  Note that unlike token
    arguments the template argument sorts are deduced by look-ahead rather
    than from the template sort.
*/

static LIST(TOKEN)
parse_template_args(PPTOKEN *p)
{
	int t;
	PARSE_STATE st;
	LIST(TOKEN) args = NULL_list(TOKEN);
	if (p == NULL) {
		return args;
	}

	/* Initialise parser */
	save_state(&st, 1);
	init_parser(p);
	ADVANCE_LEXER;
	t = crt_lex_token;
	if (t == lex_open_Htemplate) {
		/* Step over open bracket */
		ADVANCE_LEXER;
		t = crt_lex_token;
	}

	/* Scan through arguments */
	if (t != lex_close_Htemplate) {
		for (;;) {
			TOKEN arg;
			if (predict_typeid(2)) {
				TYPE r = NULL_type;
				have_type_specifier = 0;
				if (predict_typename()) {
					/* Template argument */
					IDENTIFIER rid = NULL_id;
					parse_id(&rid);
					MAKE_tok_class(r, rid, arg);
				} else {
					/* Type argument */
					parse_type(&r);
					MAKE_tok_type(btype_lang, r, arg);
				}
			} else {
				/* Expression argument */
				EXP e = NULL_exp;
				TYPE r = NULL_type;
				parse_exp(&e);
				if (!IS_NULL_exp(e)) {
					r = DEREF_type(exp_type(e));
				}
				MAKE_tok_exp(r, 1, e, arg);
			}
			if (have_syntax_error) {
				break;
			}
			CONS_tok(arg, args, args);
			t = crt_lex_token;
			if (t == lex_close_Htemplate) {
				break;
			} else if (t == lex_comma) {
				ADVANCE_LEXER;
			} else {
				t = lex_close_Htemplate;
				report(crt_loc, ERR_lex_expect(t));
				break;
			}
		}
	}

	/* Restore state */
	restore_state(&st);
	p = restore_parser();
	free_tok_list(p);

	/* Return result */
	args = REVERSE_list(args);
	return args;
}


/*
    This routine checks the type t of the template parameter id.
*/

static void
templ_param_type(IDENTIFIER id, TYPE t)
{
	switch (TAG_type(t)) {
	case type_floating_tag:
	case type_top_tag:
	case type_bottom_tag:
		/* Illegal parameter types */
		report(crt_loc, ERR_temp_param_type(id, t));
		break;
	}
	return;
}


/*
    This routine defines the template parameter id to be arg.
*/

static int
define_templ_param(IDENTIFIER id, TOKEN arg, IDENTIFIER tid, int def)
{
    int ok = 1;
    TOKEN sort = DEREF_tok(id_token_sort(id));
    unsigned tag = TAG_tok(sort);
    if (tag == tok_type_tag) {
	/* Type parameter */
	TYPE t;
	if (IS_tok_type(arg)) {
	    t = DEREF_type(tok_type_value(arg));
	    if (def) {
		    t = expand_type(t, 2);
	    }
	    if (!is_global_type(t)) {
		/* Type must have external linkage */
		ERROR err = ERR_temp_arg_local(t);
		err = concat_error(ERR_temp_arg_init(id, tid), err);
		report(crt_loc, err);
	    }
	    COPY_type(tok_type_value(arg), t);
	} else {
	    /* Non-type argument supplied */
	    t = type_error;
	    report(crt_loc, ERR_temp_arg_type(id, tid));
	    ok = 0;
	}
	COPY_type(tok_type_value(sort), t);

    } else if (tag == tok_exp_tag) {
	/* Expression parameter */
	EXP e;
	if (IS_tok_exp(arg)) {
	    int over = 0;
	    ERROR err = NULL_err;
	    TYPE s1 = DEREF_type(tok_exp_type(sort));
	    TYPE s2 = expand_type(s1, 2);
	    if (!EQ_type(s1, s2)) {
		    templ_param_type(id, s2);
	    }
	    e = DEREF_exp(tok_exp_value(arg));
	    if (def) {
		/* Perform conversion if necessary */
		unsigned etag = TAG_exp(e);
		e = convert_reference(e, REF_ASSIGN);
		e = expand_exp(e, 2, 0);
		if (IS_exp_address_mem(e)) {
		    /* Check for overloaded pointer to members */
		    EXP a = DEREF_exp(exp_address_mem_arg(e));
		    if (IS_exp_member(a)) {
			IDENTIFIER mid = DEREF_id(exp_member_id(a));
			if (IS_id_function_etc(mid)) {
			    mid = DEREF_id(id_function_etc_over(mid));
			    if (!IS_NULL_id(mid)) {
				    over = 1;
			    }
			}
		    }
		}
		if (IS_type_array(s2)) {
		    if (etag == exp_paren_tag) {
			    e = make_paren_exp(e);
		    }
		    e = init_array(s2, cv_none, e, 1, &err);
		} else {
		    e = init_assign(s2, cv_none, e, &err);
		}
		if (!IS_NULL_err(err)) {
			err = init_error(err, 0);
		}
	    }
	    if (is_const_exp(e, 1)) {
		switch (TAG_type(s2)) {
		    case type_integer_tag:
		    case type_floating_tag:
		    case type_top_tag:
		    case type_bottom_tag:
		    case type_enumerate_tag:
		    case type_token_tag:
		    case type_error_tag:
			/* Constants of these types are alright */
			break;
		    default: {
			/* Check linkage in other cases */
			EXP pa = NULL_exp;
			DECL_SPEC ln = find_exp_linkage(e, &pa, 0);
			if (ln & dspec_extern) {
			    /* External linkage */
			    /* EMPTY */
			} else if (ln & dspec_static) {
			    /* Internal linkage */
			    ERROR err2 = ERR_temp_arg_internal();
			    err = concat_error(err, err2);
			} else {
			    /* No linkage */
			    ERROR err2 = ERR_temp_arg_bad();
			    err = concat_error(err, err2);
			}
			if (over) {
			    /* Overloaded pointer to member */
			    ERROR err2 = ERR_temp_arg_over();
			    err = concat_error(err, err2);
			}
			break;
		    }
		}
	    } else {
		err = concat_error(err, ERR_temp_arg_const());
	    }
	    if (!IS_NULL_err(err)) {
		err = concat_error(ERR_temp_arg_init(id, tid), err);
		report(crt_loc, err);
	    }
	    COPY_type(tok_exp_type(arg), s2);
	    COPY_exp(tok_exp_value(arg), e);
	} else {
	    /* Non-expression argument supplied */
	    e = make_error_exp(0);
	    report(crt_loc, ERR_temp_arg_exp(id, tid));
	    ok = 0;
	}
	COPY_exp(tok_exp_value(sort), e);

    } else {
	/* Template class parameter */
	IDENTIFIER sid;
	if (IS_tok_class(arg)) {
	    sid = DEREF_id(tok_class_value(arg));
	    if (!IS_NULL_id(sid) && IS_id_class_name_etc(sid)) {
		TYPE s = DEREF_type(id_class_name_etc_defn(sid));
		if (!is_global_type(s)) {
		    /* Type must have external linkage */
		    ERROR err = ERR_temp_arg_local(s);
		    err = concat_error(ERR_temp_arg_init(id, tid), err);
		    report(crt_loc, err);
		}
	    }
	    init_template_param(id, sid);
	} else {
	    /* Non-template argument supplied */
	    HASHID nm = KEYWORD(lex_zzzz);
	    sid = DEREF_id(hashid_id(nm));
	    report(crt_loc, ERR_temp_arg_templ(id, tid));
	    ok = 0;
	}
	COPY_id(tok_class_value(sort), sid);

    }
    return ok;
}


/*
    This flag may be set to false to suppress template default arguments.
*/

int allow_templ_dargs = 1;


/*
    This routine checks the set of template arguments args for the template
    tid of sort tok.  Note that if tid is a function then there may be
    less arguments than parameters, in this case in_template_decl is set
    to indicate that certain template parameters remain unbound.
*/

static LIST(TOKEN)
check_templ_args(TOKEN tok, LIST(TOKEN) args, IDENTIFIER tid)
{
	int s;
	int reported = 0;
	LIST(TOKEN) a = args;
	LIST(TOKEN) b = NULL_list(TOKEN);
	LIST(TOKEN) d = DEREF_list(tok_templ_dargs(tok));
	LIST(IDENTIFIER) pids = DEREF_list(tok_templ_pids(tok));
	LIST(IDENTIFIER) qids = pids;
	if (in_template_decl && depends_on_args(args, pids, 0, 1)) {
		/* Be extra careful in this case */
		tok = expand_sort(tok, 1, 1);
		args = check_templ_args(tok, args, tid);
		return args;
	}
	s = save_token_args(qids, NULL_list(TOKEN));
	if (!allow_templ_dargs)d = NULL_list(TOKEN);
	while (!IS_NULL_list(pids)) {
		TOKEN arg = NULL_tok;
		IDENTIFIER pid = DEREF_id(HEAD_list(pids));
		if (!IS_NULL_list(a)) {
			/* Use argument from list */
			arg = DEREF_tok(HEAD_list(a));
		} else if (!IS_NULL_list(d)) {
			/* Use default argument */
			arg = DEREF_tok(HEAD_list(d));
			if (!IS_NULL_tok(arg)) {
				/* Add copy to list of arguments */
				arg = expand_sort(arg, -1, 1);
				CONS_tok(arg, b, b);
			}
		}
		if (IS_NULL_tok(arg)) {
			/* Not enough arguments */
			if (!reported) {
				if (IS_id_function_etc(tid)) {
					/* Allow for argument deduction */
					a = NULL_list(TOKEN);
					in_template_decl++;
					break;
				}
				report(crt_loc, ERR_temp_arg_less(tid));
				reported = 1;
			}
			arg = DEREF_tok(id_token_sort(pid));
			IGNORE is_bound_tok(arg, 1);
			arg = expand_sort(arg, 2, 1);
			CONS_tok(arg, b, b);
		}
		IGNORE define_templ_param(pid, arg, tid, 1);
		if (!IS_NULL_list(d)) {
			d = TAIL_list(d);
		}
		if (!IS_NULL_list(a)) {
			a = TAIL_list(a);
		}
		pids = TAIL_list(pids);
	}
	if (!IS_NULL_list(a)) {
		/* Too many arguments */
		report(crt_loc, ERR_temp_arg_more(tid));
	}
	if (!IS_NULL_list(b)) {
		/* Add default arguments to list */
		b = REVERSE_list(b);
		args = APPEND_list(args, b);
	}
	restore_token_args(qids, s);
	return args;
}


/*
    This routine checks the deduced template arguments args for the
    template tid with parameters pids.
*/

void
check_deduced_args(IDENTIFIER tid, LIST(IDENTIFIER) pids, LIST(TOKEN) args)
{
	while (!IS_NULL_list(pids) && !IS_NULL_list(args)) {
		IDENTIFIER pid = DEREF_id(HEAD_list(pids));
		TOKEN arg = DEREF_tok(HEAD_list(args));
		IGNORE define_templ_param(pid, arg, tid, 0);
		args = TAIL_list(args);
		pids = TAIL_list(pids);
	}
	return;
}


/*
    This routine checks whether the template arguments args form a match
    for an initial segment of the template sort tok.
*/

static int
match_template_args(TOKEN tok, LIST(TOKEN) args)
{
	LIST(IDENTIFIER) pids = DEREF_list(tok_templ_pids(tok));
	while (!IS_NULL_list(pids) && !IS_NULL_list(args)) {
		IDENTIFIER pid = DEREF_id(HEAD_list(pids));
		TOKEN sort = DEREF_tok(id_token_sort(pid));
		TOKEN arg = DEREF_tok(HEAD_list(args));
		if (TAG_tok(arg)!= TAG_tok(sort)) {
			/* Argument sorts do not match */
			return 0;
		}
		args = TAIL_list(args);
		pids = TAIL_list(pids);
	}
	if (!IS_NULL_list(args)) {
		/* Too many arguments */
		return 0;
	}
	return 1;
}


/*
    This routine applies the function template id to the arguments args.
    Because id may comprise several overloaded template functions it is
    necessary to check each to determine whether the template parameter
    sorts match the argument sorts.  If more than one match is found the
    result is an overloaded function.
*/

static IDENTIFIER
apply_func_templ(IDENTIFIER id, LIST(TOKEN) args, int def)
{
	int force = 0;
	IDENTIFIER tid = NULL_id;
	do {
		/* Build up result */
		IDENTIFIER fid = id;
		while (!IS_NULL_id(fid)) {
			TYPE t = DEREF_type(id_function_etc_type(fid));
			if (IS_type_templ(t)) {
				TOKEN sort = DEREF_tok(type_templ_sort(t));
				if (force || match_template_args(sort, args)) {
					/* Argument sorts match */
					IDENTIFIER sid = tid;
					int td = in_template_decl;
					args =
					    check_templ_args(sort, args, fid);
					tid = instance_func(fid, args, 0, def);
					COPY_id(id_function_etc_over(tid), sid);
					in_template_decl = td;
				}
			}
			fid = DEREF_id(id_function_etc_over(fid));
		}
		if (force) {
			/* Should have bound arguments by now */
			if (IS_NULL_id(tid)) {
				tid = id;
			}
		} else {
			/* Try again allowing for mismatches */
			force = 1;
		}
	} while (IS_NULL_id(tid));
	return tid;
}


/*
    This routine applies the typedef template id to the arguments args.
*/

static TYPE
apply_typedef_templ(IDENTIFIER id, LIST(TOKEN) args)
{
	TYPE t = DEREF_type(id_class_name_etc_defn(id));
	if (IS_type_templ(t)) {
		int td = in_template_decl;
		TOKEN sort = DEREF_tok(type_templ_sort(t));
		LIST(IDENTIFIER) pids = DEREF_list(tok_templ_pids(sort));
		args = check_templ_args(sort, args, id);
		t = DEREF_type(type_templ_defn(t));
		if (is_templ_type(t)) {
			/* Template template parameter */
			IDENTIFIER tid = DEREF_id(type_token_tok(t));
			MAKE_type_token(cv_none, tid, args, t);
		} else {
			/* Expand type definition */
			int d = save_token_args(pids, args);
			TYPE s = expand_type(t, 1);
			if (EQ_type(s, t)) {
				s = copy_typedef(id, t, cv_none);
			}
			restore_token_args(pids, d);
			t = s;
		}
		in_template_decl = td;
	} else {
		report(crt_loc, ERR_temp_names_not(id));
		t = copy_typedef(id, t, cv_none);
	}
	return t;
}


/*
    This routine applies the class template id to the arguments args.
*/

static IDENTIFIER
apply_type_templ(IDENTIFIER id, LIST(TOKEN) args, int def)
{
	if (IS_id_class_name(id)) {
		/* Class template */
		TYPE t;
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if (ds & dspec_implicit) {
			/* Allow for nested calls */
			IDENTIFIER tid = find_template(id, 0);
			if (!IS_NULL_id(tid)) {
				id = tid;
			}
		}
		t = DEREF_type(id_class_name_etc_defn(id));
		if (IS_type_templ(t)) {
			int td = in_template_decl;
			TOKEN sort = DEREF_tok(type_templ_sort(t));
			args = check_templ_args(sort, args, id);
			id = instance_type(id, args, 0, def);
			in_template_decl = td;
		} else {
			report(crt_loc, ERR_temp_names_not(id));
		}
	} else {
		/* Type alias template */
		TYPE t = apply_typedef_templ(id, args);
		if (IS_type_compound(t)) {
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
			complete_class(ct, def);
			id = DEREF_id(ctype_name(ct));
		} else {
			HASHID nm = DEREF_hashid(id_name(id));
			NAMESPACE ns = DEREF_nspace(id_parent(id));
			decl_loc = crt_loc;
			id = make_typedef(ns, nm, t, dspec_none);
		}
	}
	return id;
}


/*
    This routine applies the template id to the arguments args.
*/

IDENTIFIER
apply_template(IDENTIFIER id, LIST(TOKEN) args, int def, int force)
{
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	if (ds & dspec_template) {
		if (IS_id_function_etc(id)) {
			id = apply_func_templ(id, args, def);
		} else {
			id = apply_type_templ(id, args, def);
		}
	} else {
		TYPE form;
		MAKE_type_token(cv_none, id, args, form);
		if (force || is_templ_depend(form)) {
			/* Dummy template identifier */
			HASHID nm = DEREF_hashid(id_name(id));
			NAMESPACE ns = DEREF_nspace(id_parent(id));
			MAKE_id_undef(nm, dspec_none, ns, crt_loc, id);
			COPY_type(id_undef_form(id), form);
		} else {
			report(crt_loc, ERR_temp_names_not(id));
		}
	}
	return id;
}


/*
    This routine parses the template arguments p for the non-class template
    id.  This includes both template functions and dummy template identifiers
    such as in 'ptr->template id < ... >'.
*/

IDENTIFIER
parse_id_template(IDENTIFIER id, PPTOKEN *p, int def)
{
	LIST(TOKEN) args = parse_template_args(p);
	id = apply_template(id, args, def, 1);
	return id;
}


/*
    This routine parses the template arguments p for the class template
    id.  def is passed to instance_type.
*/

IDENTIFIER
parse_type_template(IDENTIFIER id, PPTOKEN *p, int def)
{
	LIST(TOKEN) args = parse_template_args(p);
	id = apply_type_templ(id, args, def);
	return id;
}


/*
    This routine parses the template arguments p for the typedef
    template id.
*/

TYPE
parse_typedef_templ(IDENTIFIER id, PPTOKEN *p)
{
	LIST(TOKEN) args = parse_template_args(p);
	TYPE t = apply_typedef_templ(id, args);
	return t;
}


/*
    This routine deduces the arguments for the template type id called
    without arguments.  Within a template class definition the template
    name gives the the template applied to the current arguments.
    Otherwise template declarations and definitions (for which used is
    false) are allowed but other instances are not.
*/

TYPE
deduce_type_template(IDENTIFIER id, int used)
{
	TYPE t = DEREF_type(id_class_name_etc_defn(id));
	if (used) {
		TYPE s = t;
		while (IS_type_templ(s)) {
			s = DEREF_type(type_templ_defn(s));
		}
		if (IS_type_compound(s)) {
			CLASS_TYPE cs = DEREF_ctype(type_compound_defn(s));
			if (defining_class(cs)) {
				/* In class definition */
				return s;
			}
		}
		report(crt_loc, ERR_temp_local_not(t));
	}
	return t;
}


/*
    This variable is used within a template declaration to hold the
    namespace in which the template parameters are declared.
*/

NAMESPACE templ_namespace = NULL_nspace;


/*
    These lists are dummy values representing the lists of all template
    parameters and all template or token parameters.
*/

LIST(IDENTIFIER) any_templ_param = NULL_list(IDENTIFIER);
LIST(IDENTIFIER) any_token_param = NULL_list(IDENTIFIER);


/*
    This routine parses a set of template parameters.  It is entered after
    the initial 'template' has been read.  ex is true if this was preceded
    by 'export'.
*/

TOKEN
template_params(int ex)
{
	int t;
	TOKEN tok;
	PPTOKEN *p;
	NAMESPACE ns;
	LOCATION loc;
	PARSE_STATE s;
	int have_darg = 0;
	unsigned long npars = 0;
	DECL_SPEC use = dspec_none;
	LIST(TOKEN) dargs = NULL_list(TOKEN);
	LIST(IDENTIFIER) pids = NULL_list(IDENTIFIER);

	/* Can't have template declarations inside blocks */
	if (in_function_defn) {
		report(crt_loc, ERR_temp_decl_scope());
	} else if (in_class_defn && really_in_function_defn) {
		report(crt_loc, ERR_temp_mem_local());
	}

	/* Mark exported templates */
	if (ex || option(OPT_templ_export))use |= dspec_extern;

	/* Check for initial '<' */
	if (crt_lex_token != lex_less) {
		/* Explicit instantiation */
		MAKE_tok_templ(use, NULL_nspace, tok);
		return tok;
	}

	/* Start template parameter namespace */
	ns = make_namespace(NULL_id, nspace_templ_tag, 0);
	push_namespace(ns);
	in_template_decl++;
	record_location++;

	/* Prepare to parse template parameters */
	ADVANCE_LEXER;
	loc = crt_loc;
	p = skip_template(NULL_id);
	save_state(&s, 1);
	crt_loc = loc;
	init_parser(p);
	ADVANCE_LEXER;
	t = crt_lex_token;

	/* Parse template parameters */
	if (t != lex_close_Htemplate) {
		for (;;) {
			/* Declare parameter */
			IDENTIFIER pid = NULL_id;
			decl_loc = crt_loc;
			if (predict_template()) {
				/* Type parameter */
				parse_type_param(&pid);
			} else {
				/* Expression parameter */
				if (crt_lex_token == lex_typename) {
					/* Replace 'typename' by 'class' */
					crt_lex_token = lex_class;
				}
				parse_param(NULL_type, CONTEXT_TEMPL_PARAM,
					    &pid);
			}

			/* Add parameter to list */
			if (!IS_NULL_id(pid)) {
				DECL_SPEC ds = DEREF_dspec(id_storage(pid));
				ds |= dspec_template;
				COPY_dspec(id_storage(pid), ds);
				if (do_dump) {
					dump_token_param(pid);
				}
				tok = DEREF_tok(id_token_sort(pid));
				switch (TAG_tok(tok)) {
				case tok_exp_tag: {
					/* Expression parameter */
					int c;
					EXP e;
					TYPE r;
					DECONS_tok_exp(r, c, e, tok);
					templ_param_type(pid, r);
					if (IS_NULL_exp(e)) {
						if (have_darg) {
							have_darg = 2;
						}
						tok = NULL_tok;
					} else {
						COPY_exp(tok_exp_value(tok),
							 NULL_exp);
						MAKE_tok_exp(r, c, e, tok);
						have_darg = 1;
					}
					break;
				}
				case tok_type_tag: {
					/* Type parameter */
					TYPE r = DEREF_type(tok_type_value(tok));
					if (IS_NULL_type(r)) {
						if (have_darg) {
							have_darg = 2;
						}
						tok = NULL_tok;
					} else {
						COPY_type(tok_type_value(tok),
							  NULL_type);
						MAKE_tok_type(btype_lang, r,
							      tok);
						have_darg = 1;
					}
					break;
				}
				case tok_class_tag: {
					/* Template class parameter */
					TYPE r =
					    DEREF_type(tok_class_type(tok));
					IDENTIFIER cid =
					    DEREF_id(tok_class_value(tok));
					if (IS_NULL_id(cid)) {
						if (have_darg) {
							have_darg = 2;
						}
						tok = NULL_tok;
					} else {
						COPY_id(tok_class_value(tok),
							NULL_id);
						MAKE_tok_class(r, cid, tok);
						have_darg = 1;
					}
					break;
				}
				default:
					/* Shouldn't occur */
					tok = NULL_tok;
					break;
				}
				if (have_darg == 2) {
					/* Missing default argument */
					report(crt_loc,
					       ERR_temp_param_default(pid));
				}
				CONS_tok(tok, dargs, dargs);
				CONS_id(pid, pids, pids);
				npars++;
			}

			/* Check for next parameter */
			t = crt_lex_token;
			if (t == lex_close_Htemplate) {
				/* End of parameter list */
				break;
			} else if (t == lex_comma) {
				/* Move on to next parameter */
				ADVANCE_LEXER;
			} else {
				/* Syntax error */
				if (!have_syntax_error) {
					ERROR err = ERR_lex_parse(crt_token);
					report(crt_loc, err);
				}
				break;
			}
		}
	}

	/* Restore parser */
	restore_state(&s);
	p = restore_parser();
	free_tok_list(p);

	/* Construct the result */
	MAKE_tok_templ(use, crt_namespace, tok);
	if (IS_NULL_list(pids)) {
		/* Explicit specialisation */
		IGNORE pop_namespace();
		in_template_decl--;
		record_location--;
	} else {
		IGNORE check_value(OPT_VAL_template_pars, npars);
		pids = REVERSE_list(pids);
		dargs = REVERSE_list(dargs);
		COPY_list(tok_templ_pids(tok), pids);
		COPY_list(tok_templ_dargs(tok), dargs);
		set_proc_token(pids);
		templ_namespace = ns;
	}
	return tok;
}


/*
    This routine creates a template type qualifier from the template
    parameters tok and the type t.  It also terminates the template
    parameter namespace while leaving its names in scope.
*/

TYPE
make_template_type(TOKEN tok, TYPE t)
{
	TYPE s;
	LIST(IDENTIFIER) pids = DEREF_list(tok_templ_pids(tok));
	if (!IS_NULL_list(pids)) {
		/* Remove template parameters */
		IGNORE restore_namespace();
	}
	MAKE_type_templ(cv_none, tok, NULL_type, 0, s);
	if (!IS_NULL_type(t)) {
		unsigned tag = TAG_type(t);
		NAMESPACE ns = DEREF_nspace(tok_templ_pars(tok));
		if (IS_NULL_nspace(ns)) {
			/* Can't have 'template template < ... >' */
			report(crt_loc, ERR_temp_explicit_templ());
			s = NULL_type;
		} else {
			if (tag == type_templ_tag) {
				tok = DEREF_tok(type_templ_sort(t));
				ns = DEREF_nspace(tok_templ_pars(tok));
				if (IS_NULL_nspace(ns)) {
					/* Can't have 'template < ... >
					 * template' */
					report(crt_loc,
					       ERR_temp_explicit_templ());
					t = DEREF_type(type_templ_defn(t));
					tag = TAG_type(t);
				}
			}
		}
		if (tag == type_func_tag) {
			/* Ignore linkage specifiers */
			CV_SPEC cv = DEREF_cv(type_func_mqual(t));
			cv &= ~cv_language;
			cv |= cv_cpp;
			COPY_cv(type_func_mqual(t), cv);
		}
		s = inject_pre_type(t, s, 0);
	}
	return s;
}


/*
    This routine ends a template declaration.  It removes the names from
    the template parameter namespace from scope.
*/

void
end_template(TOKEN tok)
{
	LIST(IDENTIFIER) pids = DEREF_list(tok_templ_pids(tok));
	if (!IS_NULL_list(pids)) {
		remove_namespace();
		templ_namespace = NULL_nspace;
		in_template_decl--;
		record_location--;
		if (in_template_decl) {
			/* Find enclosing template namespace */
			LIST(NAMESPACE) lns = LIST_stack(namespace_stack);
			while (!IS_NULL_list(lns)) {
				NAMESPACE ns = DEREF_nspace(HEAD_list(lns));
				if (IS_nspace_templ(ns)) {
					templ_namespace = ns;
					break;
				}
				lns = TAIL_list(lns);
			}
		}
	}
	if (!in_template_decl) {
		clear_templates(1);
	}
	return;
}


/*
    This routine is called whenever the template type t is used to qualify
    a class definition or a function declarator.
*/

void
template_decl(TYPE t)
{
	while (!IS_NULL_type(t) && IS_type_templ(t)) {
		TOKEN sort = DEREF_tok(type_templ_sort(t));
		DECL_SPEC ds = DEREF_dspec(tok_templ_usage(sort));
		if (ds & dspec_used) {
			/* Already used */
			report(crt_loc, ERR_temp_decl_one());
		}
		ds |= dspec_used;
		COPY_dspec(tok_templ_usage(sort), ds);
		t = DEREF_type(type_templ_defn(t));
	}
	return;
}


/*
    This routine exports the instances associated with the template type t.
    It returns the non-template component of t.
*/

static TYPE
export_instances(TYPE t, int def)
{
	while (IS_type_templ(t)) {
		TOKEN sort = DEREF_tok(type_templ_sort(t));
		INSTANCE apps = DEREF_inst(tok_templ_apps(sort));
		while (!IS_NULL_inst(apps)) {
			DECL_SPEC acc = DEREF_dspec(inst_templ_access(apps));
			if (!(acc & (dspec_alias | dspec_main))) {
				IDENTIFIER id = DEREF_id(inst_templ_id(apps));
				export_template(id, def);
			}
			acc |= dspec_typedef;
			COPY_dspec(inst_templ_access(apps), acc);
			apps = DEREF_inst(inst_next(apps));
		}
		t = DEREF_type(type_templ_defn(t));
	}
	return t;
}


/*
    This routine marks the template identifier id as having been exported.
    def is 2 for the first explicit declaration of a template, 1 for a
    redeclaration and 0 otherwise.
*/

void export_template(IDENTIFIER id, int def)
{
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	if (ds & (dspec_inherit | dspec_implicit)) {
		return;
	}
	if (ds & (dspec_inline | dspec_static)) {
		return;
	}
	if (def == 0 && (ds & dspec_typedef)) {
		/* Already exported */
		return;
	}
	ds |= dspec_typedef;
	COPY_dspec(id_storage(id), ds);
	if (def == 2 && !has_linkage(id)) {
		/* Can't export anonymous identifiers */
		report(crt_loc, ERR_temp_decl_export(id));
	}
	switch (TAG_id(id)) {
	case id_class_name_tag:
	case id_class_alias_tag: {
		/* Template classes */
		TYPE t = DEREF_type(id_class_name_etc_defn(id));
		t = export_instances(t, def);
		if (IS_type_compound(t)) {
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
			IDENTIFIER cid = DEREF_id(ctype_name(ct));
			if (EQ_id(id, cid)) {
				NAMESPACE ns = DEREF_nspace(ctype_member(ct));
				MEMBER mem =
				    DEREF_member(nspace_ctype_first(ns));
				while (!IS_NULL_member(mem)) {
					/* Scan through class members */
					IDENTIFIER pid =
					    DEREF_id(member_id(mem));
					IDENTIFIER qid =
					    DEREF_id(member_alt(mem));
					if (!IS_NULL_id(pid)) {
						export_template(pid, def);
					}
					if (!IS_NULL_id(qid) &&
					    !EQ_id(qid, pid)) {
						export_template(qid, def);
					}
					mem = DEREF_member(member_next(mem));
				}
			}
		}
		break;
	}
	case id_function_tag:
	case id_mem_func_tag:
	case id_stat_mem_func_tag: {
		/* Template functions */
		TYPE t = DEREF_type(id_function_etc_type(id));
		IGNORE export_instances(t, def);
		update_tag(id, 0);
		break;
	}
	case id_stat_member_tag:
		/* Static data members */
		update_tag(id, 0);
		break;
	}
	return;
}


/*
    This routine checks whether the template instance id has been exported.
*/

int
is_exported(IDENTIFIER id)
{
	TYPE form;
	int def = 0;
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	if (ds & dspec_typedef) {
		return 1;
	}
	form = find_form(id, &def);
	if (!IS_NULL_type(form) && IS_type_instance(form)) {
		IDENTIFIER tid = DEREF_id(type_instance_id(form));
		ds = DEREF_dspec(id_storage(tid));
		if (ds & dspec_typedef) {
			export_template(id, 0);
			return 1;
		}
	}
	return 0;
}


/*
    This routine creates a list of primary template arguments corresponding
    to the template parameters pids.
*/

LIST(TOKEN)
make_primary_args(LIST(IDENTIFIER) pids)
{
	LIST(TOKEN) args = NULL_list(TOKEN);
	while (!IS_NULL_list(pids)) {
		IDENTIFIER pid = DEREF_id(HEAD_list(pids));
		TOKEN arg = apply_token(pid, NULL_list(TOKEN));
		CONS_tok(arg, args, args);
		pids = TAIL_list(pids);
	}
	return REVERSE_list(args);
}


/*
    This routine checks the template parameters given by the type t for
    the declaration of the primary template class or function id.  It
    returns the non-template component of t.
*/

TYPE
check_templ_params(TYPE t, IDENTIFIER id)
{
	int depth = 0;
	unsigned tag = TAG_type(t);
	while (tag == type_templ_tag) {
		TOKEN sort = DEREF_tok(type_templ_sort(t));
		NAMESPACE ns = DEREF_nspace(tok_templ_pars(sort));
		DECL_SPEC use = DEREF_dspec(tok_templ_usage(sort));
		LIST(IDENTIFIER) pids = DEREF_list(tok_templ_pids(sort));
		TYPE s = DEREF_type(type_templ_defn(t));
		tag = TAG_type(s);
		if (IS_NULL_list(pids)) {
			/* No template parameters */
			if (IS_NULL_nspace(ns)) {
				/* Explicit instantiation */
				report(decl_loc, ERR_temp_explicit_bad(id));
			} else {
				/* Specialisation */
				report(decl_loc, ERR_temp_param_none(id));
				COPY_id(nspace_name(ns), id);
			}
		} else {
			/* Create primary specialisation */
			TYPE form;
			TYPE prim;
			INSTANCE apps;
			DECL_SPEC ds = (dspec_template | dspec_extern |
					dspec_main);
			LIST(TOKEN) args = make_primary_args(pids);
			MAKE_type_token(cv_none, id, args, form);
			MAKE_type_templ(cv_none, sort, form, 1, prim);
			apps = DEREF_inst(tok_templ_apps(sort));
			MAKE_inst_templ(prim, apps, id, ds, all_instances,
					apps);
			COPY_inst(type_token_app(form), apps);
			COPY_inst(tok_templ_apps(sort), apps);
			all_instances = apps;
			if (tag == type_compound_tag) {
				CLASS_TYPE cs =
				    DEREF_ctype(type_compound_defn(s));
				COPY_type(ctype_form(cs), form);
			} else if (tag == type_func_tag) {
				/* Can't have default arguments with function */
				if (check_templ_dargs(t)) {
					report(decl_loc, ERR_temp_param_func());
				}
			}
			COPY_id(nspace_name(ns), id);
		}
		if (use & dspec_extern) {
			export_template(id, 2);
		}
		depth++;
		t = s;
	}
	if (depth > 1) {
		/* More than one level of templates */
		report(decl_loc, ERR_temp_decl_bad());
	}
	return t;
}


/*
    This routine returns true if the template type t has default arguments.
*/

int
check_templ_dargs(TYPE t)
{
	if (IS_type_templ(t)) {
		TOKEN sort = DEREF_tok(type_templ_sort(t));
		LIST(TOKEN) dargs = DEREF_list(tok_templ_dargs(sort));
		while (!IS_NULL_list(dargs)) {
			TOKEN darg = DEREF_tok(HEAD_list(dargs));
			if (!IS_NULL_tok(darg)) {
				return 1;
			}
			dargs = TAIL_list(dargs);
		}
	}
	return 0;
}


/*
    This routine checks whether the identifier id results from the
    application of a template.  If so it returns the underlying template.
*/

IDENTIFIER
find_template(IDENTIFIER id, int force)
{
	if (!IS_NULL_id(id)) {
		switch (TAG_id(id)) {
		case id_class_name_tag: {
			/* Template classes */
			CLASS_TYPE ct;
			int templ = 0;
			TYPE t = DEREF_type(id_class_name_defn(id));
			while (IS_type_templ(t)) {
				t = DEREF_type(type_templ_defn(t));
				templ = 1;
			}
			ct = DEREF_ctype(type_compound_defn(t));
			t = DEREF_type(ctype_form(ct));
			if (!IS_NULL_type(t) && IS_type_token(t)) {
				IDENTIFIER tid = DEREF_id(type_token_tok(t));
				if (!IS_id_token(tid)) {
					return tid;
				}
			}
			if (templ && force) {
				/* Primary template class */
				return id;
			}
			break;
		}
		case id_function_tag:
		case id_mem_func_tag:
		case id_stat_mem_func_tag: {
			/* Template functions */
			TYPE t = DEREF_type(id_function_etc_form(id));
			if (!IS_NULL_type(t) && IS_type_token(t)) {
				IDENTIFIER tid = DEREF_id(type_token_tok(t));
				if (!IS_id_token(tid)) {
					return tid;
				}
			}
			if (force) {
				t = DEREF_type(id_function_etc_type(id));
				if (IS_type_templ(t)) {
					/* Primary template function */
					return id;
				}
			}
			break;
		}
		case id_ambig_tag: {
			/* Ambiguous identifiers */
			LIST(IDENTIFIER) pids;
			pids = DEREF_list(id_ambig_ids(id));
			if (!IS_NULL_list(pids)) {
				IDENTIFIER pid = DEREF_id(HEAD_list(pids));
				IDENTIFIER tid = find_template(pid, force);
				if (!IS_NULL_id(tid)) {
					pids = TAIL_list(pids);
					while (!IS_NULL_list(pids)) {
						IDENTIFIER sid;
						pid = DEREF_id(HEAD_list(pids));
						sid = find_template(pid, force);
						if (!EQ_id(sid, tid)) {
							return NULL_id;
						}
						pids = TAIL_list(pids);
					}
					return tid;
				}
			}
			break;
		}
		}
	}
	return NULL_id;
}


/*
    This routine checks the template parameter id for redeclarations.
*/

static IDENTIFIER
redecl_templ_param(IDENTIFIER id)
{
	HASHID nm = DEREF_hashid(id_name(id));
	MEMBER mem = search_member(crt_namespace, nm, 1);
	IDENTIFIER pid = DEREF_id(member_id(mem));
	if (!IS_NULL_id(pid)) {
		/* Parameter already defined */
		report(crt_loc, ERR_temp_param_dup(nm));
		nm = lookup_anon();
		id = DEREF_id(hashid_id(nm));
	}
	return id;
}


/*
    This routine declares a template type parameter named id.
*/

IDENTIFIER
make_type_param(IDENTIFIER id)
{
	TOKEN tok;
	MAKE_tok_type(btype_template, NULL_type, tok);
	id = redecl_templ_param(id);
	id = make_token_decl(tok, 0, id, NULL_id);
	return id;
}


/*
    This routine sets the default value for the template type parameter id
    to be t.
*/

void
init_type_param(IDENTIFIER id, TYPE t)
{
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	COPY_dspec(id_storage(id), (ds & ~dspec_pure));
	IGNORE define_type_token(id, t, 0);
	COPY_dspec(id_storage(id), ds);
	return;
}


/*
    This routine declares a template expression parameter named id of
    type t.
*/

IDENTIFIER
make_exp_param(TYPE t, IDENTIFIER id)
{
	TOKEN tok;
	t = rvalue_type(t);
	MAKE_tok_exp(t, 1, NULL_exp, tok);
	id = make_token_decl(tok, 0, id, NULL_id);
	return id;
}


/*
    This routine sets the default value for the template expression
    parameter id to be e.
*/

void
init_exp_param(IDENTIFIER id, EXP e)
{
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	COPY_dspec(id_storage(id), (ds & ~dspec_pure));
	IGNORE define_exp_token(id, e, 1);
	COPY_dspec(id_storage(id), ds);
	return;
}


/*
    This routine declares a template template parameter named id of type t.
*/

IDENTIFIER
make_template_param(TYPE t, IDENTIFIER id)
{
	TOKEN tok;
	MAKE_tok_class(t, NULL_id, tok);
	id = redecl_templ_param(id);
	id = make_token_decl(tok, 0, id, NULL_id);
	return id;
}


/*
    This routine sets the value for the template template parameter id to
    be tid.  This is used both to set a default argument value and to
    define a template template parameter.
*/

void
init_template_param(IDENTIFIER id, IDENTIFIER tid)
{
	if (!IS_NULL_id(tid)) {
		if (IS_id_class_name_etc(tid)) {
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			COPY_dspec(id_storage(id), (ds & ~dspec_pure));
			IGNORE define_templ_token(id, tid);
			COPY_dspec(id_storage(id), ds);
		} else {
			report(crt_loc, ERR_temp_arg_templ_not(id, tid));
		}
	}
	return;
}


/*
    This list is used to store all the dummy type parameters created by
    make_dummy_type to avoid duplicates.
*/

static LIST(IDENTIFIER) dummy_types = NULL_list(IDENTIFIER);


/*
    This routine creates a dummy type parameter named id in the namespace
    ns.  bt gives the token type kind.
*/

static TYPE
make_dummy_type(NAMESPACE ns, IDENTIFIER id, BASE_TYPE bt, LIST(TOKEN) args)
{
	TYPE t;
	HASHID nm = DEREF_hashid(id_name(id));
	LIST(IDENTIFIER) p = dummy_types;
	while (!IS_NULL_list(p)) {
		IDENTIFIER pid = DEREF_id(HEAD_list(p));
		HASHID pnm = DEREF_hashid(id_name(pid));
		NAMESPACE pns = DEREF_nspace(id_parent(pid));
		if (EQ_hashid(nm, pnm) && EQ_nspace(ns, pns)) {
			TOKEN tok = DEREF_tok(id_token_sort(pid));
			BASE_TYPE pt = DEREF_btype(tok_type_kind(tok));
			if (bt == pt) {
				id = pid;
				break;
			}
		}
		p = TAIL_list(p);
	}
	if (IS_NULL_list(p)) {
		/* Create new parameter */
		TOKEN tok;
		DECL_SPEC ds = (dspec_template | dspec_token | dspec_auto |
				dspec_pure | dspec_implicit);
		MAKE_tok_type(bt, NULL_type, tok);
		MAKE_id_token(nm, ds, ns, crt_loc, tok, NULL_id, id);
		COPY_id(id_token_alt(id), id);
		CONS_id(id, dummy_types, dummy_types);
	}
	MAKE_type_token(cv_none, id, args, t);
	return t;
}


/*
    This routine checks whether the type t represents an explicit template
    specialisation or instantiation.
*/

int
is_templ_spec(TYPE t)
{
	while (!IS_NULL_type(t) && IS_type_templ(t)) {
		LIST(IDENTIFIER) pids;
		TOKEN sort = DEREF_tok(type_templ_sort(t));
		pids = DEREF_list(tok_templ_pids(sort));
		if (IS_NULL_list(pids)) {
			return 1;
		}
		t = DEREF_type(type_templ_defn(t));
	}
	return 0;
}


/*
    This routine checks whether the type t represents a template parameter
    and a template declaration is currently being processed.
*/

int
is_templ_type(TYPE t)
{
	if (!IS_NULL_type(t) && IS_type_token(t)) {
		IDENTIFIER id = DEREF_id(type_token_tok(t));
		if (is_templ_param(id)) {
			return in_template_decl;
		}
	}
	return 0;
}


/*
    This routine checks whether the type t is dependent on any template
    parameter.
*/

int
is_templ_depend(TYPE t)
{
	if (in_template_decl) {
		/* Only need to check in a template declaration */
		return depends_on(t, any_templ_param);
	}
	return 0;
}


/*
    This routine checks whether the token identifier id represents a
    template type parameter.
*/

int
is_templ_param(IDENTIFIER id)
{
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	if ((ds & dspec_template) && (ds & dspec_auto)) {
		return 1;
	}
	return 0;
}


/*
    This routine checks whether the identifier id is the internal name
    for a template type parameter.
*/

int
is_templ_alias(IDENTIFIER id)
{
	unsigned tag = TAG_id(id);
	if (tag == id_type_alias_tag) {
		TYPE t = DEREF_type(id_type_alias_defn(id));
		if (IS_type_token(t)) {
			id = DEREF_id(type_token_tok(t));
			tag = TAG_id(id);
		}
	} else if (tag == id_token_tag) {
		id = DEREF_id(id_token_alt(id));
		tag = TAG_id(id);
	}
	if (tag == id_token_tag && is_templ_param(id)) {
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if (!(ds & dspec_implicit)) {
			return 1;
		}
	}
	return 0;
}


/*
    This routine checks whether the declarator id represents a template
    instance.  If id is a function declaration then t gives the function
    type.
*/

int
is_templ_decl(IDENTIFIER id, TYPE t)
{
	if (crt_templ_qualifier) {
		/* Declaration is a template-id */
		IDENTIFIER tid = find_template(id, 0);
		if (!IS_NULL_id(tid)) {
			return 1;
		}
	}
	if (!IS_NULL_type(t) && crt_id_qualifier != qual_none) {
		/* Function declarator is a qualified-id */
		int eq = 0;
		LIST(IDENTIFIER) pids = NULL_list(IDENTIFIER);
		IDENTIFIER pid = resolve_func(id, t, 1, 1, pids, &eq);
		if (!IS_NULL_id(pid)) {
			IDENTIFIER tid = find_template(pid, 0);
			if (!IS_NULL_id(tid)) {
				return 1;
			}
		}
	}
	return 0;
}


/*
    This routine checks whether the namespace ns represents a template
    class or a nested class of a template class or a block of a template
    function.
*/

int
is_templ_nspace(NAMESPACE ns)
{
	while (!IS_NULL_nspace(ns)) {
		IDENTIFIER tid;
		IDENTIFIER id = DEREF_id(nspace_name(ns));
		if (IS_NULL_id(id)) {
			break;
		}
		tid = find_template(id, 1);
		if (!IS_NULL_id(tid)) {
			return 1;
		}
		ns = DEREF_nspace(id_parent(id));
	}
	return 0;
}


/*
    This routine checks whether 'typename ns::id' can be used to declare
    a type.  If so this type is returned, otherwise the null type is
    returned.  Any following template arguments are dealt with in this
    routine.
*/

TYPE
check_typename(NAMESPACE ns, IDENTIFIER id, BASE_TYPE key)
{
	TYPE s = NULL_type;
	if (in_template_decl) {
		if (!IS_NULL_nspace(ns) && IS_nspace_ctype(ns)) {
			IDENTIFIER tid = DEREF_id(nspace_name(ns));
			TYPE t = DEREF_type(id_class_name_etc_defn(tid));
			while (IS_type_templ(t)) {
				/* Step over any template qualifiers */
				t = DEREF_type(type_templ_defn(t));
			}
			if (is_templ_depend(t)) {
				/* Qualifier depends on a template parameter */
				int templ = 0;
				LIST(TOKEN) args = NULL_list(TOKEN);
				if (crt_lex_token == lex_less) {
					/* Step over template arguments */
					PPTOKEN *p =
					    skip_template_args(NULL_id, 1);
					args = parse_template_args(p);
					templ = 1;
				}
				if (IS_id_class_name_etc(id)) {
					if (templ) {
						/* Apply template arguments */
						id = apply_template(id, args,
								    0, 0);
					}
					s = DEREF_type(id_class_name_etc_defn(id));
					if (IS_type_templ(s)) {
						s = deduce_type_template(id, 1);
					}
					s = copy_typedef(id, s, cv_none);
					COPY_id(type_name(s), id);
					use_id(id, 0);
				} else {
					BASE_TYPE bt = (btype_template |
							btype_typename);
					if (templ) {
						bt |= btype_args;
					}
					s = make_dummy_type(ns, id, bt, args);
					if (key != btype_none) {
						/* Result should be a class */
						id = DEREF_id(type_token_tok(s));
						args = NULL_list(TOKEN);
						s = make_dummy_class(id, args,
								     key);
					}
				}
			}
		}
	}
	return s;
}


/*
    This routine handles a type declared using typename.  ns gives the
    name qualifiers used in the declaration and id gives the actual member
    name.  Any following template arguments are dealt with in this
    routine.
*/

TYPE
make_typename(NAMESPACE ns, IDENTIFIER id)
{
	TYPE s = check_typename(ns, id, btype_none);
	if (IS_NULL_type(s)) {
		int templ = 0;
		LIST(TOKEN) args = NULL_list(TOKEN);
		report(crt_loc, ERR_temp_res_qual());
		if (crt_lex_token == lex_less) {
			/* Step over template arguments */
			PPTOKEN *p = skip_template_args(NULL_id, 1);
			args = parse_template_args(p);
			templ = 1;
		}
		if (IS_id_class_name_etc(id)) {
			/* Name denotes a type - return that */
			if (templ) {
				/* Apply template arguments */
				id = apply_template(id, args, 0, 0);
			}
			s = DEREF_type(id_class_name_etc_defn(id));
			if (IS_type_templ(s)) {
				s = deduce_type_template(id, 1);
			}
			s = copy_typedef(id, s, cv_none);
			COPY_id(type_name(s), id);
			use_id(id, 0);
		} else {
			/* Return the error type */
			s = type_error;
		}
	}
	return s;
}


/*
    Without some action, an illegal typename can be reported many times.
    A list of all bad typename look-ups is maintained so that the error is
    only reported once.
*/

static LIST(IDENTIFIER) non_typenames = NULL_list(IDENTIFIER);


/*
    This routine expands the type name id.  If no expansion is possible
    then the null type is returned.  type indicates whether the look-up
    should be for a type name or an object name (the latter is used when
    searching for a type previously declared using typename).
*/

TYPE
find_typename(IDENTIFIER id, LIST(TOKEN) args, BASE_TYPE bt, int type)
{
	TYPE t = NULL_type;
	NAMESPACE ns = DEREF_nspace(id_parent(id));
	NAMESPACE cns = rescan_nspace(ns);
	if (!EQ_nspace(cns, ns)) {
		/* Rescan type name */
		LIST(IDENTIFIER) p;
		HASHID nm = DEREF_hashid(id_name(id));
		IDENTIFIER tid = search_field(cns, nm, 0, type);
		if (!IS_NULL_id(tid) && IS_id_class_name_etc(tid)) {
			/* Type name */
			if (bt & btype_args) {
				/* Apply template arguments */
				tid = apply_template(tid, args, 0, 0);
			}
			t = DEREF_type(id_class_name_etc_defn(tid));
			if (IS_type_templ(t)) {
				t = deduce_type_template(tid, 1);
			}
			t = copy_typedef(tid, t, cv_none);
			COPY_id(type_name(t), tid);
			use_id(tid, 0);
			return t;
		}

		/* Check for template parameters */
		if (in_template_decl) {
			if (!IS_NULL_nspace(cns) && IS_nspace_ctype(cns)) {
				tid = DEREF_id(nspace_name(cns));
				t = DEREF_type(id_class_name_etc_defn(tid));
				while (IS_type_templ(t)) {
					t = DEREF_type(type_templ_defn(t));
				}
				if (is_templ_depend(t)) {
					t = make_dummy_type(cns, id, bt, args);
					return t;
				}
			}
		}

		/* Report error */
		p = non_typenames;
		t = type_error;
		while (!IS_NULL_list(p)) {
			IDENTIFIER pid = DEREF_id(HEAD_list(p));
			HASHID pnm = DEREF_hashid(id_name(pid));
			NAMESPACE pns = DEREF_nspace(id_parent(pid));
			if (EQ_hashid(pnm, nm) && EQ_nspace(pns, cns)) {
				/* Already reported */
				break;
			}
		}
		if (IS_NULL_list(p)) {
			/* Report undefined type */
			MAKE_id_type_alias(nm, dspec_none, cns, crt_loc, t,
					   tid);
			CONS_id(tid, non_typenames, non_typenames);
			report(crt_loc, ERR_temp_res_type(cns, nm));
		}
	}
	return t;
}


/*
    This routine identifies the list of template parameters ps with those
    in pt, returning true if this is possible.
*/

int
eq_templ_params(LIST(IDENTIFIER) ps, LIST(IDENTIFIER) pt)
{
	int ok = 1;
	while (!IS_NULL_list(ps) && !IS_NULL_list(pt)) {
		IDENTIFIER is = DEREF_id(HEAD_list(ps));
		IDENTIFIER it = DEREF_id(HEAD_list(pt));
		if (!EQ_id(is, it)) {
			TOKEN ns, nt;
			unsigned vs, vt;
			if (IS_NULL_id(is)) {
				return 0;
			}
			if (IS_NULL_id(it)) {
				return 0;
			}
			ns = DEREF_tok(id_token_sort(is));
			nt = DEREF_tok(id_token_sort(it));
			vs = TAG_tok(ns);
			vt = TAG_tok(nt);
			if (vs != vt) {
				/* Parameter sorts should be equal */
				ok = 0;
				break;
			}
			if (vs == tok_exp_tag) {
				/* Check expression parameter types */
				TYPE rs = DEREF_type(tok_exp_type(ns));
				TYPE rt = DEREF_type(tok_exp_type(nt));
				rs = expand_type(rs, 2);
				if (eq_type(rs, rt)!= 1) {
					ok = 0;
					break;
				}
			}
			if (vs == tok_class_tag) {
				/* Check template class parameter types */
				TYPE rs = DEREF_type(tok_class_type(ns));
				TYPE rt = DEREF_type(tok_class_type(nt));
				rs = expand_type(rs, 2);
				if (eq_template(rs, rt, 0, 1, 0) != 3) {
					ok = 0;
					break;
				}
			}
			it = DEREF_id(id_alias(it));
			COPY_id(id_alias(is), it);
		}
		pt = TAIL_list(pt);
		ps = TAIL_list(ps);
	}
	if (!EQ_list(ps, pt)) {
		ok = 0;
	}
	return ok;
}


/*
    This routine clears the aliases set up by eq_templ_param from the
    list of template parameters ps.
*/

void
restore_templ_params(LIST(IDENTIFIER)ps)
{
	while (!IS_NULL_list(ps)) {
		IDENTIFIER is = DEREF_id(HEAD_list(ps));
		COPY_id(id_alias(is), is);
		ps = TAIL_list(ps);
	}
	return;
}


/*
    This routine checks whether the template types s and t are equal
    under a simple renaming of template parameters.  If def is false
    only the template parameters (and not the underlying type) are checked.
    mq and rf are as in eq_func_type, as is the return value.
*/

int
eq_template(TYPE s, TYPE t, int def, int mq, int rf)
{
	TOKEN as = DEREF_tok(type_templ_sort(s));
	TOKEN at = DEREF_tok(type_templ_sort(t));
	LIST(IDENTIFIER) ps = DEREF_list(tok_templ_pids(as));
	LIST(IDENTIFIER) pt = DEREF_list(tok_templ_pids(at));
	int eq = eq_templ_params(ps, pt);
	if (eq && def) {
		/* Check for equality of definitions */
		int ft = force_template;
		TYPE ds = DEREF_type(type_templ_defn(s));
		TYPE dt = DEREF_type(type_templ_defn(t));
		force_template = 0;
		eq = eq_func_type(ds, dt, mq, rf);
		force_template = ft;
	}
	restore_templ_params(ps);
	return eq;
}


/*
    This routine renames the parameters in the given template sort,
    returning the template type formed by applying this renaming to t.
*/

static TYPE
rename_templ_params(TOKEN sort, TYPE t, int rec)
{
	if (rec) {
		int d;
		LIST(TOKEN) args;
		LIST(IDENTIFIER) pids;
		LIST(IDENTIFIER) qids;
		pids = DEREF_list(tok_templ_pids(sort));
		sort = expand_sort(sort, 1, 1);
		qids = DEREF_list(tok_templ_pids(sort));
		args = make_primary_args(qids);
		d = save_token_args(pids, args);
		t = expand_type(t, 1);
		restore_token_args(pids, d);
	}
	MAKE_type_templ(cv_none, sort, t, 1, t);
	return t;
}


/*
    This routine checks whether the type t is a specialisation of the
    template type s.  Type qualifiers are ignored if qu is false.
*/

int
deduce_template(TYPE s, TYPE t, int qu)
{
	int eq;
	TYPE r = DEREF_type(type_templ_defn(s));
	TOKEN sort = DEREF_tok(type_templ_sort(s));
	LIST(IDENTIFIER) pids = DEREF_list(tok_templ_pids(sort));
	if (in_template_decl && depends_on(t, pids)) {
		/* Rename parameters if necessary */
		CV_SPEC cv = DEREF_cv(type_qual(s));
		s = rename_templ_params(sort, r, 1);
		COPY_cv(type_qual(s), cv);
		eq = deduce_template(s, t, qu);
	} else {
		/* Perform argument deduction */
		int d;
		force_template++;
		d = save_token_args(pids, NULL_list(TOKEN));
		eq = eq_type_qual(r, t, qu);
		if (eq == 3) {
			eq = 0;
		}
		restore_token_args(pids, d);
		force_template--;
	}
	return eq;
}


/*
    This routine checks the redeclaration of the template id of type ps to
    have type pt.  The primary purpose of this is to check for default
    arguments in the redeclaration.  The non-template components are
    returned via ps and pt.
*/

void
redecl_template(TYPE *ps, TYPE *pt, IDENTIFIER id)
{
	TYPE s = *ps;
	TYPE t = *pt;
	while (IS_type_templ(s)) {
		s = DEREF_type(type_templ_defn(s));
	}
	while (IS_type_templ(t)) {
		TOKEN sort = DEREF_tok(type_templ_sort(t));
		DECL_SPEC use = DEREF_dspec(tok_templ_usage(sort));
		if (use & dspec_extern) {
			export_template(id, 1);
		}
		if (check_templ_dargs(t)) {
			/* Can't have default arguments in redeclaration */
			report(decl_loc, ERR_temp_param_redecl());
		}
		t = DEREF_type(type_templ_defn(t));
	}
	*pt = t;
	*ps = s;
	return;
}


/*
    This routine changes the primary representation of a template from
    s to t.  This is done when, for example, the latter is a definition
    while the former is only a declaration.
*/

void
reset_primary_templ(TYPE s, TYPE t)
{
	unsigned ns = TAG_type(s);
	unsigned nt = TAG_type(t);
	while (ns == type_templ_tag && nt == type_templ_tag) {
		TOKEN as = DEREF_tok(type_templ_sort(s));
		TOKEN at = DEREF_tok(type_templ_sort(t));
		LIST(IDENTIFIER) ps = DEREF_list(tok_templ_pids(as));
		LIST(IDENTIFIER) pt = DEREF_list(tok_templ_pids(at));
		INSTANCE apps = DEREF_inst(tok_templ_apps(as));
		INSTANCE app = apps;
		LIST(TOKEN) dargs = DEREF_list(tok_templ_dargs(as));
		while (!IS_NULL_inst(app)) {
			DECL_SPEC ds = DEREF_dspec(inst_templ_access(app));
			if (ds & dspec_main) {
				/* Replace primary template instance */
				TYPE form = DEREF_type(inst_form(app));
				LIST(TOKEN) args = make_primary_args(pt);
				COPY_tok(type_templ_sort(form), at);
				form = DEREF_type(type_templ_defn(form));
				COPY_list(type_token_args(form), args);
			}
			app = DEREF_inst(inst_next(app));
		}
		if (check_templ_dargs(s)) {
			/* Expand default arguments */
			LIST(TOKEN) args = make_primary_args(pt);
			int d = save_token_args(ps, args);
			dargs = expand_args(dargs, 1, 1);
			restore_token_args(ps, d);
		}
		COPY_list(tok_templ_dargs(at), dargs);
		COPY_inst(tok_templ_apps(at), apps);
		s = DEREF_type(type_templ_defn(s));
		t = DEREF_type(type_templ_defn(t));
		ns = TAG_type(s);
		nt = TAG_type(t);
	}
	return;
}


/*
    This routine checks whether the token identifier id is one of the
    template or token parameters given by pids.
*/

int
depends_on_param(IDENTIFIER id, LIST(IDENTIFIER) pids)
{
	if (IS_id_token(id)) {
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if (!(ds & dspec_ignore)) {
			if (EQ_list(pids, any_templ_param)) {
				/* Short-cut for list of all template
				 * parameters */
				if ((ds & dspec_template) &&
				    (ds & dspec_auto)) {
					return 1;
				}
				return 0;
			}
			if (EQ_list(pids, any_token_param)) {
				/* Short-cut for list of all token parameters */
				if (ds & dspec_auto) {
					return 1;
				}
				return 0;
			}
			while (!IS_NULL_list(pids)) {
				IDENTIFIER pid = DEREF_id(HEAD_list(pids));
				if (EQ_id(pid, id)) {
					return 1;
				}
				pids = TAIL_list(pids);
			}
		}
	}
	return 0;
}


/*
    This routine checks whether the identifier id is one of the template
    parameters pids or is a template function with an argument depending
    on pids.  If use is true then any other identifiers found are marked
    as used.
*/

static int
depends_on_id(IDENTIFIER id, LIST(IDENTIFIER) pids, int use)
{
	if (!IS_NULL_id(id)) {
		NAMESPACE ns;
		switch (TAG_id(id)) {
		case id_class_name_tag: {
			/* Check for template classes */
			TYPE form;
			CLASS_TYPE ct;
			TYPE t = DEREF_type(id_class_name_defn(id));
			while (IS_type_templ(t)) {
				t = DEREF_type(type_templ_defn(t));
			}
			ct = DEREF_ctype(type_compound_defn(t));
			form = DEREF_type(ctype_form(ct));
			if (!IS_NULL_type(form)) {
				if (depends_on(form, pids)) {
					return 1;
				}
			}
			break;
		}
		case id_function_tag:
		case id_mem_func_tag:
		case id_stat_mem_func_tag: {
			/* Check for template functions */
			TYPE form = DEREF_type(id_function_etc_form(id));
			if (!IS_NULL_type(form)) {
				/* Check function form */
				if (depends_on(form, pids)) {
					return 1;
				}
			}
			if (use) {
				reuse_id(id, 0);
			}
			break;
		}
		case id_token_tag: {
			/* Check for template parameters */
			if (depends_on_param(id, pids)) {
				return 1;
			}
			break;
		}
		case id_ambig_tag: {
			/* Check ambiguous identifiers */
			LIST(IDENTIFIER) qids;
			qids = DEREF_list(id_ambig_ids(id));
			while (!IS_NULL_list(qids)) {
				IDENTIFIER qid = DEREF_id(HEAD_list(qids));
				if (depends_on_id(qid, pids, use)) {
					return 1;
				}
				qids = TAIL_list(qids);
			}
			break;
		}
		case id_stat_member_tag: {
			/* Mark static data members */
			if (use) {
				reuse_id(id, 0);
			}
			break;
		}
		}
		ns = DEREF_nspace(id_parent(id));
		if (!IS_NULL_nspace(ns)) {
			/* Check enclosing namespace */
			IDENTIFIER cid = DEREF_id(nspace_name(ns));
			return depends_on_id(cid, pids, 0);
		}
	}
	return 0;
}


/*
    This routine checks whether the list of token arguments args depends
    on one of the template parameters pids.  If next is true then the
    algorithm is modified to check whether any token argument depends
    on a later template parameter (e.g. does the first element of args
    depend on the second, third, etc. element of pids).
*/

int
depends_on_args(LIST(TOKEN) args, LIST(IDENTIFIER) pids, int use, int next)
{
	while (!IS_NULL_list(args)) {
		TOKEN tok = DEREF_tok(HEAD_list(args));
		if (next) {
			/* Move on to next parameter */
			if (IS_NULL_list(pids)) {
				break;
			}
			pids = TAIL_list(pids);
		}
		if (!IS_NULL_tok(tok)) {
			switch (TAG_tok(tok)) {
			case tok_exp_tag: {
				EXP e = DEREF_exp(tok_exp_value(tok));
				if (depends_on_exp(e, pids, use)) {
					return 1;
				}
				break;
			}
			case tok_stmt_tag: {
				EXP e = DEREF_exp(tok_stmt_value(tok));
				if (depends_on_exp(e, pids, use)) {
					return 1;
				}
				break;
			}
			case tok_nat_tag:
			case tok_snat_tag: {
				NAT n = DEREF_nat(tok_nat_etc_value(tok));
				if (depends_on_nat(n, pids, use)) {
					return 1;
				}
				break;
			}
			case tok_type_tag: {
				TYPE t = DEREF_type(tok_type_value(tok));
				if (depends_on(t, pids)) {
					return 1;
				}
				break;
			}
			case tok_member_tag: {
				OFFSET off = DEREF_off(tok_member_value(tok));
				if (depends_on_off(off, pids, use)) {
					return 1;
				}
				break;
			}
			case tok_class_tag:
				/* NOT YET IMPLEMENTED */
				break;
			}
		}
		args = TAIL_list(args);
	}
	return 0;
}


/*
    This routine checks whether the integral constant n depends on one
    of the template parameters pids.
*/

int
depends_on_nat(NAT n, LIST(IDENTIFIER) pids, int use)
{
	if (!IS_NULL_nat(n)) {
		switch (TAG_nat(n)) {
		case nat_calc_tag: {
			EXP e = DEREF_exp(nat_calc_value(n));
			return depends_on_exp(e, pids, use);
		}
		case nat_token_tag: {
			IDENTIFIER tid = DEREF_id(nat_token_tok(n));
			LIST(TOKEN) args = DEREF_list(nat_token_args(n));
			if (depends_on_param(tid, pids)) {
				return 2;
			}
			if (depends_on_args(args, pids, use, 0)) {
				return 1;
			}
			break;
		}
		}
	}
	return 0;
}


/*
    This routine checks whether the list of expressions p depends on one
    of the template parameters pids.
*/

static int
depends_on_exp_list(LIST(EXP) p, LIST(IDENTIFIER) pids, int use)
{
	while (!IS_NULL_list(p)) {
		EXP a = DEREF_exp(HEAD_list(p));
		if (depends_on_exp(a, pids, use)) {
			return 1;
		}
		p = TAIL_list(p);
	}
	return 0;
}


/*
    This routine checks whether the expression e depends on one of the
    template parameters pids.  If e is actually a template parameter
    then 2 is returned.
*/

int
depends_on_exp(EXP e, LIST(IDENTIFIER) pids, int use)
{
	if (!IS_NULL_exp(e)) {
		unsigned tag = TAG_exp(e);
		TYPE t = DEREF_type(exp_type(e));
		if (tag == exp_token_tag) {
			/* Check for template parameters */
			IDENTIFIER tid = DEREF_id(exp_token_tok(e));
			LIST(TOKEN) args = DEREF_list(exp_token_args(e));
			if (depends_on_param(tid, pids)) {
				return 2;
			}
			if (depends_on_args(args, pids, use, 0)) {
				return 1;
			}
		}
		if (depends_on(t, pids)) {
			return 1;
		}
		assert(ORDER_exp == 88);
		switch (tag) {
		case exp_identifier_tag:
		case exp_member_tag:
		case exp_ambiguous_tag:
		case exp_undeclared_tag: {
			IDENTIFIER id = DEREF_id(exp_identifier_etc_id(e));
			if (depends_on_id(id, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_int_lit_tag: {
			NAT n = DEREF_nat(exp_int_lit_nat(e));
			return depends_on_nat(n, pids, use);
		}
		case exp_paren_tag:
		case exp_copy_tag: {
			EXP a = DEREF_exp(exp_paren_etc_arg(e));
			return depends_on_exp(a, pids, use);
		}
		case exp_assign_tag: {
			EXP a = DEREF_exp(exp_assign_ref(e));
			EXP b = DEREF_exp(exp_assign_arg(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			if (depends_on_exp(b, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_init_tag: {
			IDENTIFIER id = DEREF_id(exp_init_id(e));
			EXP a = DEREF_exp(exp_init_arg(e));
			if (depends_on_id(id, pids, use)) {
				return 1;
			}
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_preinc_tag: {
			EXP a = DEREF_exp(exp_preinc_op(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_postinc_tag: {
			EXP a = DEREF_exp(exp_postinc_op(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_indir_tag: {
			EXP a = DEREF_exp(exp_indir_ptr(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_contents_tag: {
			EXP a = DEREF_exp(exp_contents_ptr(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_address_tag: {
			EXP a = DEREF_exp(exp_address_arg(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_address_mem_tag: {
			EXP a = DEREF_exp(exp_address_mem_arg(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_func_tag: {
			EXP a = DEREF_exp(exp_func_fn(e));
			LIST(EXP) p = DEREF_list(exp_func_args(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			if (depends_on_exp_list(p, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_func_id_tag: {
			IDENTIFIER id = DEREF_id(exp_func_id_id(e));
			LIST(EXP) p = DEREF_list(exp_func_id_args(e));
			if (depends_on_id(id, pids, use)) {
				return 1;
			}
			if (depends_on_exp_list(p, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_call_tag: {
			EXP a = DEREF_exp(exp_call_ptr(e));
			EXP b = DEREF_exp(exp_call_arg(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			if (depends_on_exp(b, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_negate_tag:
		case exp_compl_tag:
		case exp_not_tag:
		case exp_abs_tag: {
			EXP a = DEREF_exp(exp_negate_etc_arg(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_plus_tag:
		case exp_minus_tag:
		case exp_mult_tag:
		case exp_div_tag:
		case exp_rem_tag:
		case exp_and_tag:
		case exp_or_tag:
		case exp_xor_tag:
		case exp_log_and_tag:
		case exp_log_or_tag:
		case exp_lshift_tag:
		case exp_rshift_tag:
		case exp_max_tag:
		case exp_min_tag: {
			EXP a = DEREF_exp(exp_plus_etc_arg1(e));
			EXP b = DEREF_exp(exp_plus_etc_arg2(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			if (depends_on_exp(b, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_test_tag: {
			EXP a = DEREF_exp(exp_test_arg(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_compare_tag: {
			EXP a = DEREF_exp(exp_compare_arg1(e));
			EXP b = DEREF_exp(exp_compare_arg2(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			if (depends_on_exp(b, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_cast_tag: {
			EXP a = DEREF_exp(exp_cast_arg(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_base_cast_tag: {
			EXP a = DEREF_exp(exp_base_cast_arg(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_dyn_cast_tag: {
			EXP a = DEREF_exp(exp_dyn_cast_arg(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_add_ptr_tag: {
			EXP a = DEREF_exp(exp_add_ptr_ptr(e));
			OFFSET off = DEREF_off(exp_add_ptr_off(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			if (depends_on_off(off, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_offset_size_tag: {
			OFFSET off = DEREF_off(exp_offset_size_off(e));
			TYPE s = DEREF_type(exp_offset_size_step(e));
			if (depends_on_off(off, pids, use)) {
				return 1;
			}
			if (depends_on(s, pids)) {
				return 1;
			}
			break;
		}
		case exp_constr_tag: {
			EXP a = DEREF_exp(exp_constr_call(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_destr_tag: {
			EXP a = DEREF_exp(exp_destr_call(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_alloc_tag: {
			EXP a = DEREF_exp(exp_alloc_call(e));
			EXP b = DEREF_exp(exp_alloc_init(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			if (depends_on_exp(b, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_dealloc_tag: {
			EXP a = DEREF_exp(exp_dealloc_term(e));
			EXP b = DEREF_exp(exp_dealloc_call(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			if (depends_on_exp(b, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_rtti_tag: {
			EXP a = DEREF_exp(exp_rtti_arg(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_rtti_type_tag: {
			TYPE s = DEREF_type(exp_rtti_type_arg(e));
			if (depends_on(s, pids)) {
				return 1;
			}
			break;
		}
		case exp_rtti_no_tag: {
			TYPE s = DEREF_type(exp_rtti_no_arg(e));
			if (depends_on(s, pids)) {
				return 1;
			}
			break;
		}
		case exp_dynamic_tag: {
			EXP a = DEREF_exp(exp_dynamic_arg(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_aggregate_tag: {
			LIST(EXP)p = DEREF_list(exp_aggregate_args(e));
			if (depends_on_exp_list(p, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_initialiser_tag: {
			LIST(EXP)p = DEREF_list(exp_initialiser_args(e));
			if (depends_on_exp_list(p, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_nof_tag: {
			EXP a = DEREF_exp(exp_nof_start(e));
			EXP b = DEREF_exp(exp_nof_pad(e));
			EXP c = DEREF_exp(exp_nof_end(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			if (depends_on_exp(b, pids, use)) {
				return 1;
			}
			if (depends_on_exp(c, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_comma_tag: {
			LIST(EXP) p = DEREF_list(exp_comma_args(e));
			if (depends_on_exp_list(p, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_set_tag: {
			EXP a = DEREF_exp(exp_set_arg(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_unused_tag: {
			EXP a = DEREF_exp(exp_unused_arg(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_sequence_tag: {
			LIST(EXP)p = DEREF_list(exp_sequence_first(e));
			if (depends_on_exp_list(p, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_if_stmt_tag: {
			EXP c = DEREF_exp(exp_if_stmt_cond(e));
			EXP a = DEREF_exp(exp_if_stmt_true_code(e));
			EXP b = DEREF_exp(exp_if_stmt_false_code(e));
			if (depends_on_exp(c, pids, use)) {
				return 1;
			}
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			if (depends_on_exp(b, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_try_block_tag: {
			EXP a = DEREF_exp(exp_try_block_body(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_exception_tag: {
			EXP a = DEREF_exp(exp_exception_arg(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_op_tag: {
			EXP a = DEREF_exp(exp_op_arg1(e));
			EXP b = DEREF_exp(exp_op_arg2(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			if (depends_on_exp(b, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_opn_tag: {
			LIST(EXP) p = DEREF_list(exp_opn_args(e));
			if (depends_on_exp_list(p, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_location_tag: {
			EXP a = DEREF_exp(exp_location_arg(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			break;
		}
		case exp_dummy_tag: {
			EXP a = DEREF_exp(exp_dummy_value(e));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			break;
		}
		}
	}
	return 0;
}


/*
    This routine checks whether the offset off depends on one of the
    template parameters pids.
*/

int
depends_on_off(OFFSET off, LIST(IDENTIFIER) pids, int use)
{
	if (!IS_NULL_off(off)) {
		assert(ORDER_off == 13);
		switch (TAG_off(off)) {
		case off_zero_tag: {
			TYPE t = DEREF_type(off_zero_type(off));
			if (depends_on(t, pids)) {
				return 1;
			}
			break;
		}
		case off_type_tag: {
			TYPE t = DEREF_type(off_type_type(off));
			if (depends_on(t, pids)) {
				return 1;
			}
			break;
		}
		case off_array_tag: {
			TYPE t = DEREF_type(off_array_type(off));
			if (depends_on(t, pids)) {
				return 1;
			}
			break;
		}
		case off_extra_tag: {
			TYPE t = DEREF_type(off_extra_type(off));
			if (depends_on(t, pids)) {
				return 1;
			}
			break;
		}
#if 0
		case off_base_tag: {
			GRAPH graph = DEREF_graph(off_base_graph(off));
			break;
		}
		case off_deriv_tag: {
			GRAPH graph = DEREF_graph(off_deriv_graph(off));
			OFFSET direct = DEREF_off(off_deriv_direct(off));
			OFFSET indirect = DEREF_off(off_deriv_indirect(off));
			break;
		}
		case off_member_tag: {
			IDENTIFIER id = DEREF_id(off_member_id(off));
			break;
		}
#endif
		case off_ptr_mem_tag: {
			EXP a = DEREF_exp(off_ptr_mem_arg(off));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			break;
		}
		case off_negate_tag: {
			OFFSET a = DEREF_off(off_negate_arg(off));
			if (depends_on_off(a, pids, use)) {
				return 1;
			}
			break;
		}
		case off_plus_tag: {
			OFFSET a = DEREF_off(off_plus_arg1(off));
			OFFSET b = DEREF_off(off_plus_arg2(off));
			if (depends_on_off(a, pids, use)) {
				return 1;
			}
			if (depends_on_off(b, pids, use)) {
				return 1;
			}
			break;
		}
		case off_mult_tag: {
			OFFSET a = DEREF_off(off_mult_arg1(off));
			EXP b = DEREF_exp(off_mult_arg2(off));
			if (depends_on_off(a, pids, use)) {
				return 1;
			}
			if (depends_on_exp(b, pids, use)) {
				return 1;
			}
			break;
		}
		case off_ptr_diff_tag: {
			EXP a = DEREF_exp(off_ptr_diff_ptr1(off));
			EXP b = DEREF_exp(off_ptr_diff_ptr2(off));
			if (depends_on_exp(a, pids, use)) {
				return 1;
			}
			if (depends_on_exp(b, pids, use)) {
				return 1;
			}
			break;
		}
		case off_token_tag: {
			IDENTIFIER tid = DEREF_id(off_token_tok(off));
			LIST(TOKEN) args = DEREF_list(off_token_args(off));
			if (depends_on_param(tid, pids)) {
				return 2;
			}
			if (depends_on_args(args, pids, use, 0)) {
				return 1;
			}
			break;
		}
		}
	}
	return 0;
}


/*
    This routine checks whether the type t depends on one of the template
    parameters pids.
*/

int
depends_on(TYPE t, LIST(IDENTIFIER) pids)
{
	if (!IS_NULL_type(t)) {
		assert(ORDER_type == 18);
		switch (TAG_type(t)) {
		case type_ptr_tag:
		case type_ref_tag: {
			TYPE s = DEREF_type(type_ptr_etc_sub(t));
			return depends_on(s, pids);
		}
		case type_ptr_mem_tag: {
			TYPE s = DEREF_type(type_ptr_mem_sub(t));
			CLASS_TYPE cr = DEREF_ctype(type_ptr_mem_of(t));
			TYPE r = DEREF_type(ctype_form(cr));
			if (depends_on(s, pids)) {
				return 1;
			}
			return depends_on(r, pids);
		}
		case type_func_tag: {
			TYPE r = DEREF_type(type_func_ret(t));
			LIST(TYPE) p = DEREF_list(type_func_mtypes(t));
			if (depends_on(r, pids)) {
				return 1;
			}
			while (!IS_NULL_list(p)) {
				TYPE s = DEREF_type(HEAD_list(p));
				if (depends_on(s, pids)) {
					return 1;
				}
				p = TAIL_list(p);
			}
			break;
		}
		case type_array_tag: {
			TYPE s = DEREF_type(type_array_sub(t));
			NAT n = DEREF_nat(type_array_size(t));
			if (depends_on(s, pids)) {
				return 1;
			}
			return depends_on_nat(n, pids, 0);
		}
		case type_bitfield_tag: {
			INT_TYPE it = DEREF_itype(type_bitfield_defn(t));
			TYPE s = DEREF_type(itype_bitfield_sub(it));
			NAT n = DEREF_nat(itype_bitfield_size(it));
			if (depends_on(s, pids)) {
				return 1;
			}
			return depends_on_nat(n, pids, 0);
		}
		case type_compound_tag: {
			CLASS_TYPE cs = DEREF_ctype(type_compound_defn(t));
			IDENTIFIER cid = DEREF_id(ctype_name(cs));
			return depends_on_id(cid, pids, 0);
		}
		case type_enumerate_tag: {
			ENUM_TYPE et = DEREF_etype(type_enumerate_defn(t));
			IDENTIFIER eid = DEREF_id(etype_name(et));
			return depends_on_id(eid, pids, 0);
		}
		case type_token_tag: {
			IDENTIFIER tid = DEREF_id(type_token_tok(t));
			LIST(TOKEN) args = DEREF_list(type_token_args(t));
			if (depends_on_param(tid, pids)) {
				return 1;
			}
			if (depends_on_args(args, pids, 0, 0)) {
				return 1;
			}
			if (IS_id_token(tid)) {
				TOKEN sort = DEREF_tok(id_token_sort(tid));
				if (IS_tok_type(sort)) {
					BASE_TYPE bt;
					bt = DEREF_btype(tok_type_kind(sort));
					if (bt & btype_typename) {
						/* Allow for typename */
						return depends_on_id(tid, pids, 0);
					}
				}
			}
			break;
		}
		case type_templ_tag: {
			int dep;
			LIST(IDENTIFIER) qids;
			TYPE s = DEREF_type(type_templ_defn(t));
			TOKEN sort = DEREF_tok(type_templ_sort(t));
			qids = DEREF_list(tok_templ_pids(sort));
			while (!IS_NULL_list(qids)) {
				/* Suppress template parameters */
				IDENTIFIER qid = DEREF_id(HEAD_list(qids));
				DECL_SPEC ds = DEREF_dspec(id_storage(qid));
				ds |= dspec_ignore;
				COPY_dspec(id_storage(qid), ds);
				qids = TAIL_list(qids);
			}
			dep = depends_on(s, pids);
			qids = DEREF_list(tok_templ_pids(sort));
			while (!IS_NULL_list(qids)) {
				/* Restore template parameters */
				IDENTIFIER qid = DEREF_id(HEAD_list(qids));
				DECL_SPEC ds = DEREF_dspec(id_storage(qid));
				ds &= ~dspec_ignore;
				COPY_dspec(id_storage(qid), ds);
				qids = TAIL_list(qids);
			}
			return dep;
		}
		}
	}
	return 0;
}


/*
    This routine checks whether the function call 'id ( args )' depends
    on a template parameter.
*/

int
dependent_call(IDENTIFIER id, LIST(EXP) args)
{
	if (in_template_decl) {
		/* Only check in a template declaration */
		LIST(IDENTIFIER) pids = any_templ_param;
		if (depends_on_id(id, pids, 0)) {
			return 1;
		}
		if (IS_id_function_etc(id)) {
			while (!IS_NULL_id(id)) {
				TYPE t = DEREF_type(id_function_etc_type(id));
				if (depends_on(t, pids)) {
					return 1;
				}
				id = DEREF_id(id_function_etc_over(id));
			}
		}
		while (!IS_NULL_list(args)) {
			EXP a = DEREF_exp(HEAD_list(args));
			if (!IS_NULL_exp(a)) {
				/* Check argument type */
				TYPE t = DEREF_type(exp_type(a));
				if (depends_on(t, pids)) {
					return 1;
				}
			}
			args = TAIL_list(args);
		}
	}
	return 0;
}


/*
    This routine checks whether the resolution of the overloaded function
    id to the type t depends on a template parameter.
*/

int
dependent_cast(IDENTIFIER id, TYPE t)
{
	if (in_template_decl) {
		/* Only check in a template declaration */
		LIST(IDENTIFIER) pids = any_templ_param;
		if (depends_on_id(id, pids, 0)) {
			return 1;
		}
		if (depends_on(t, pids)) {
			return 1;
		}
	}
	return 0;
}


/*
    This routine checks whether the conversion 't ( args )' depends
    on a template parameter.
*/

int
dependent_conv(TYPE t, LIST(EXP) args)
{
	if (in_template_decl) {
		/* Only check in a template declaration */
		LIST(IDENTIFIER) pids = any_templ_param;
		if (depends_on(t, pids)) {
			return 1;
		}
		while (!IS_NULL_list(args)) {
			EXP a = DEREF_exp(HEAD_list(args));
			if (!IS_NULL_exp(a)) {
				/* Check argument type */
				TYPE s = DEREF_type(exp_type(a));
				if (depends_on(s, pids)) {
					return 1;
				}
			}
			args = TAIL_list(args);
		}
	}
	return 0;
}


/*
    This routine checks whether the identifier id depends on a template
    parameter.
*/

int
dependent_id(IDENTIFIER id)
{
	if (in_template_decl) {
		/* Only check in a template declaration */
		LIST(IDENTIFIER) pids = any_templ_param;
		if (depends_on_id(id, pids, 0)) {
			return 1;
		}
	}
	return 0;
}


/*
    This routine marks all the identifiers in the expression e as having
    been used.  This routine is combined with the depends_on functions
    only because they happen to give a convenient tree-walking skeleton.
*/

void
mark_used(EXP e)
{
	if (!suppress_usage) {
		IGNORE depends_on_exp(e, NULL_list(IDENTIFIER), 1);
	}
	return;
}


/*
    This routine modifies the type t which is injected from a template
    into an enclosing scope (for example, a friend of a template class)
    by qualifying it by copies of any unbound template qualifiers.
*/

TYPE
injected_type(TYPE t, int rec)
{
	IDENTIFIER pid = NULL_id;
	LIST(NAMESPACE)lns = LIST_stack(namespace_stack);
	while (!IS_NULL_list(lns)) {
		NAMESPACE ns = DEREF_nspace(HEAD_list(lns));
		IDENTIFIER id = DEREF_id(nspace_name(ns));
		if (!IS_NULL_id(id)) {
			if (!EQ_id(id, pid)) {
				TYPE s = NULL_type;
				switch (TAG_id(id)) {
				case id_class_name_tag:
				case id_class_alias_tag:
					s = DEREF_type(id_class_name_etc_defn(id));
					break;
				case id_function_tag:
				case id_mem_func_tag:
				case id_stat_mem_func_tag:
					s = DEREF_type(id_function_etc_type(id));
					break;
				}

				if (!IS_NULL_type(s) && IS_type_templ(s)) {
					LIST(IDENTIFIER)pids;
					TOKEN sort =
					    DEREF_tok(type_templ_sort(s));
					pids = DEREF_list(tok_templ_pids(sort));
					if (depends_on(t, pids)) {
						t = rename_templ_params(sort, t,
									rec);
					}
				}
				pid = id;
			}
		}
		lns = TAIL_list(lns);
	}
	return t;
}


/*
    This variable gives a dummy template parameter type which allows the
    propagation of types dependent in some non-obvious fashion on some
    template parameter.
*/

TYPE type_templ_param;


/*
    This routine initialises the template routines.  In particular it
    initialises the dummy template parameter type.
*/

void
init_templates(void)
{
	string s = ustrlit("<type>");
	unsigned long h = hash(s);
	HASHID nm = lookup_name(s, h, 0, lex_identifier);
	IDENTIFIER id = DEREF_id(hashid_id(nm));
	LIST(TOKEN) args = NULL_list(TOKEN);
	TYPE t = make_dummy_type(crt_namespace, id, btype_template, args);
	type_templ_param = t;
	CONS_id(NULL_id, NULL_list(IDENTIFIER), any_templ_param);
	CONS_id(NULL_id, NULL_list(IDENTIFIER), any_token_param);
	return;
}
