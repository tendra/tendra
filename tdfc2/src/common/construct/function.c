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

#include <parse/constant.h>
#include <parse/file.h>
#include <parse/hash.h>
#include <parse/predict.h>

#include <construct/access.h>
#include <construct/basetype.h>
#include <construct/cast.h>
#include <construct/check.h>
#include <construct/chktype.h>
#include <construct/class.h>
#include <construct/construct.h>
#include <construct/convert.h>
#include <construct/copy.h>
#include <construct/declare.h>
#include <construct/derive.h>
#include <construct/destroy.h>
#include <construct/exception.h>
#include <construct/expression.h>
#include <construct/function.h>
#include <construct/identifier.h>
#include <construct/initialise.h>
#include <construct/instance.h>
#include <construct/label.h>
#include <construct/member.h>
#include <construct/namespace.h>
#include <construct/operator.h>
#include <construct/overload.h>
#include <construct/printf.h>
#include <construct/redeclare.h>
#include <construct/rewrite.h>
#include <construct/statement.h>
#include <construct/template.h>
#include <construct/tokdef.h>
#include <construct/token.h>
#include <construct/variable.h>

#include <output/compile.h>
#include <output/dump.h>

#include "ctype_ops.h"
#include "exp_ops.h"
#include "graph_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "member_ops.h"
#include "nspace_ops.h"
#include "tok_ops.h"
#include "type_ops.h"
#include "syntax.h"


/*
    This routine checks whether the type t is a suitable function return
    type.  This can be void (unqualified) or a complete type.  def is
    true for a function definition or call, but false otherwise.
*/

TYPE
check_ret_type(TYPE t, ERROR *err, int def)
{
	CV_SPEC cv = DEREF_cv(type_qual(t));
	cv &= cv_qual;
	if (IS_type_top_etc(t)) {
		if (cv != cv_none && !def) {
			/* Can't return 'cv void' */
			add_error(err, ERR_dcl_fct_ret_void(t));
			if ((cv & cv_volatile) && IS_type_top(t)) {
				/* Map 'volatile void' to 'bottom' */
				t = type_bottom;
				cv &= ~cv_volatile;
				t = qualify_type(t, cv, 0);
			}
		}
	} else {
		if (def) {
			add_error(err, check_incomplete(t));
		}
	}
	if (cv != cv_none && !def) {
		/* Check for cv-qualified return types */
		add_error(err, ERR_dcl_fct_cv_ret(cv));
	}
	return t;
}


/*
    This routine applies reference conversions to each element of the
    argument list args.
*/

LIST(EXP)
convert_args(LIST(EXP) args)
{
	LIST(EXP)p = args;
	while (!IS_NULL_list(p)) {
		EXP e = DEREF_exp(HEAD_list(p));
		if (!IS_NULL_exp(e)) {
			e = convert_reference(e, REF_ASSIGN);
			COPY_exp(HEAD_list(p), e);
		}
		p = TAIL_list(p);
	}
	return args;
}


/*
    This routine calculates the minimum number of arguments for the function
    type fn, taking default arguments and weak prototypes into account.
    The extra argument for member functions is included.
*/

unsigned
min_no_args(TYPE fn)
{
	unsigned n = 0;
	LIST(TYPE)ptypes;
	LIST(TYPE)mtypes;
	LIST(IDENTIFIER)p;
	while (IS_type_templ(fn)) {
		fn = DEREF_type(type_templ_defn(fn));
	}
	p = DEREF_list(type_func_pids(fn));
	ptypes = DEREF_list(type_func_ptypes(fn));
	mtypes = DEREF_list(type_func_mtypes(fn));
	if (!EQ_list(mtypes, ptypes)) {
		/* Add one for member functions */
		if (!IS_NULL_list(mtypes)) {
			mtypes = TAIL_list(mtypes);
			if (EQ_list(mtypes, ptypes)) {
				n = 1;
			}
		}
	}
	while (!IS_NULL_list(p)) {
		/* Scan for default arguments */
		IDENTIFIER id = DEREF_id(HEAD_list(p));
		EXP e = DEREF_exp(id_parameter_init(id));
		if (!IS_NULL_exp(e)) {
			break;
		}
		n++;
		p = TAIL_list(p);
	}
	return n;
}


/*
    This routine checks the default arguments for the function type fn,
    returning true if there is a default argument.  Missing default
    arguments are checked if chk is true.
*/

int
check_func_dargs(TYPE fn, int chk, int clr)
{
	int started = 0;
	unsigned tag = TAG_type(fn);
	while (tag == type_templ_tag) {
		fn = DEREF_type(type_templ_defn(fn));
		tag = TAG_type(fn);
	}
	if (tag == type_func_tag) {
		LIST(IDENTIFIER)pids = DEREF_list(type_func_pids(fn));
		while (!IS_NULL_list(pids)) {
			IDENTIFIER pid = DEREF_id(HEAD_list(pids));
			EXP a = DEREF_exp(id_parameter_init(pid));
			if (IS_NULL_exp(a)) {
				if (started && !clr) {
					/* Missing default arguments */
					TYPE s;
					LOCATION loc;
					DEREF_loc(id_loc(pid), loc);
					report(loc, ERR_dcl_fct_default_missing(pid));
					s = DEREF_type(id_parameter_type(pid));
					MAKE_exp_value(s, a);
					COPY_exp(id_parameter_init(pid), a);
				}
			} else {
				started = 1;
				if (clr) {
					/* Clear default argument */
					COPY_exp(id_parameter_init(pid),
						 NULL_exp);
				} else {
					if (!chk) {
						break;
					}
				}
			}
			pids = TAIL_list(pids);
		}
	}
	return started;
}


/*
    This routine checks the expression a passed as an argument to a weak
    function parameter of type t.  It returns the composite of t and the
    type of a, adding any errors to err.
*/

static TYPE
check_weak_arg(TYPE t, EXP a, ERROR *err)
{
	ERROR err2 = NULL_err;
	TYPE s = DEREF_type(exp_type(a));
	if (IS_exp_int_lit(a) && eq_type_offset(s, t)) {
		/* Allow for integer literals */
		NAT n = DEREF_nat(exp_int_lit_nat(a));
		if (check_nat_range(t, n) == 0) {
			return t;
		}
	}
	t = check_compatible(t, s, 2, &err2, 1);
	if (!IS_NULL_err(err2)) {
		err2 = set_severity(err2, OPT_whatever, 0);
		add_error(err, err2);
	}
	return t;
}


/*
    This routine performs weak prototype analysis for a call to the
    function id with the arguments args.  It is only called when the
    number of arguments matches the function type.
*/

static void
check_weak_args(IDENTIFIER id, LIST(EXP) args, unsigned n)
{
	TYPE fn = DEREF_type(id_function_etc_type(id));
	if (IS_type_func(fn)) {
		int changed = 0;
		int ell = DEREF_int(type_func_ellipsis(fn));
		LIST(TYPE) p = DEREF_list(type_func_ptypes(fn));
		LIST(TYPE) q = NULL_list(TYPE);
		LIST(IDENTIFIER) pids = NULL_list(IDENTIFIER);
		if (ell == FUNC_WEAK_ARGS) {
			changed = 1;
		}
		while (!IS_NULL_list(p)) {
			/* Check parameter types */
			TYPE s = DEREF_type(HEAD_list(p));
			if (!IS_NULL_list(args)) {
				ERROR err = NULL_err;
				EXP a = DEREF_exp(HEAD_list(args));
				TYPE t = check_weak_arg(s, a, &err);
				if (!IS_NULL_err(err)) {
					/* Report incompatible argument types */
					PTR(LOCATION)loc = id_loc(id);
					ERROR err2 =
					    ERR_expr_call_weak_arg(n, loc);
					err = concat_error(ERR_expr_call_func(id), err);
					err = concat_error(err, err2);
					report(crt_loc, err);
				}
				if (!EQ_type(t, s)) {
					if (changed) {
						changed = 1;
					}
					s = t;
				}
				args = TAIL_list(args);
				n++;
			}
			if (changed) {
				CONS_type(s, q, q);
			}
			p = TAIL_list(p);
		}
		if (ell == FUNC_NO_PARAMS) {
			/* Previous declaration was 'id()' */
			LOCATION loc;
			int par = CONTEXT_PARAMETER;
			NAMESPACE ns = DEREF_nspace(type_func_pars(fn));
			loc = decl_loc;
			decl_loc = crt_loc;
			push_namespace(ns);
			while (!IS_NULL_list(args)) {
				HASHID nm = lookup_anon();
				EXP a = DEREF_exp(HEAD_list(args));
				TYPE t = DEREF_type(exp_type(a));
				IDENTIFIER pid = DEREF_id(hashid_id(nm));
				pid = make_param_decl(dspec_none, t, pid, par);
				init_param(pid, NULL_exp);
				CONS_id(pid, pids, pids);
				CONS_type(t, q, q);
				args = TAIL_list(args);
			}
			IGNORE pop_namespace();
			ell = FUNC_WEAK_ARGS;
			decl_loc = loc;
			changed = 2;
		}
		if (changed == 2) {
			q = REVERSE_list(q);
			fn = copy_typedef(id, fn, cv_none);
			COPY_list(type_func_ptypes(fn), q);
			COPY_list(type_func_mtypes(fn), q);
			if (!IS_NULL_list(pids)) {
				pids = REVERSE_list(pids);
				COPY_list(type_func_pids(fn), pids);
			}
			COPY_int(type_func_ellipsis(fn), ell);
			COPY_type(id_function_etc_type(id), fn);
			COPY_loc(id_loc(id), crt_loc);
			decl_func_type(id, fn, 0);
		} else {
			DESTROY_list(q, SIZE_type);
		}
	}
	return;
}


/*
    This routine performs weak prototype analysis for a call to the
    printf-like or scanf-like function id with the arguments args.  p gives
    the parameter types deduced from the format string.
*/

static void
check_printf_args(IDENTIFIER id, LIST(TYPE) p, LIST(EXP) args, unsigned n,
		  int pf)
{
	unsigned np = LENGTH_list(p) + (n - 1);
	unsigned na = LENGTH_list(args) + (n - 1);
	if (np != na) {
		/* Check number of parameters */
		ERROR err = ERR_expr_call_args_exact(na, na, np);
		err = set_severity(err, OPT_weak, -1);
		if (!IS_NULL_id(id)) {
			err = concat_error(ERR_expr_call_func(id), err);
		}
		report(crt_loc, err);
	}
	while (!IS_NULL_list(p) && !IS_NULL_list(args)) {
		/* Check parameter types */
		ERROR err = NULL_err;
		TYPE s = DEREF_type(HEAD_list(p));
		EXP a = DEREF_exp(HEAD_list(args));
		TYPE t = check_weak_arg(s, a, &err);
		if (!IS_NULL_err(err)) {
			/* Report incompatible argument types */
			PTR(LOCATION)loc = NULL_ptr(LOCATION);
			if (!IS_NULL_id(id)) {
				loc = id_loc(id);
			}
			err = concat_error(err, ERR_expr_call_weak_arg(n, loc));
		} else {
			/* Check that scanf arguments aren't const */
			if (!(pf & 1) && IS_type_ptr(t)) {
				CV_SPEC cv;
				t = DEREF_type(type_ptr_sub(t));
				cv = DEREF_cv(type_qual(t));
				if (cv & cv_const) {
					err = ERR_conv_qual_cast(cv_const);
					err = set_severity(err, OPT_weak, -1);
				}
			}
		}
		if (!IS_NULL_err(err)) {
			if (!IS_NULL_id(id)) {
				err = concat_error(ERR_expr_call_func(id), err);
			}
			report(crt_loc, err);
		}
		args = TAIL_list(args);
		p = TAIL_list(p);
		n++;
	}
	return;
}


/*
    This routine applies the argument conversions indicated by the function
    type fn to the argument list args.  gr gives information on how member
    functions are inherited.  The function return type is returned via pr.
    The identifier id is used in error reporting only, it is the function
    being called for named functions and the null identifier otherwise.
*/

static LIST(EXP)
cast_args(IDENTIFIER id, TYPE fn, GRAPH gr, LIST(EXP) args, TYPE *pr, int mem)
{
    int ell;
    TYPE ret;
    int extra = 0;
    unsigned n = 1;
    LIST(EXP)q;
    LIST(TYPE)p;
    LIST(TYPE)ptypes;
    LIST(TYPE)mtypes;
    ERROR err = NULL_err;
    int printf_function = 0;
    LIST(IDENTIFIER)pids;
    OPTION weak = OPTION_OFF;
    LIST(TYPE)ftypes = NULL_list(TYPE);

    /* Allow for template types */
    if (IS_type_templ(fn)) {
	int d;
	TOKEN sort = DEREF_tok(type_templ_sort(fn));
	pids = DEREF_list(tok_templ_pids(sort));
	force_template++;
	d = save_token_args(pids, NULL_list(TOKEN));
	fn = DEREF_type(type_templ_defn(fn));
	args = cast_args(id, fn, gr, args, &ret, mem);
	*pr = expand_type(ret, 2);
	restore_token_args(pids, d);
	force_template--;
	return args;
    }

    /* Check function return type */
    ret = DEREF_type(type_func_ret(fn));
    ret = check_ret_type(ret, &err, 1);
    if (!IS_NULL_err(err)) {
	err = concat_error(err, ERR_expr_call_ret());
	if (!IS_NULL_id(id)) {
	    err = concat_error(ERR_expr_call_func(id), err);
	}
	report(crt_loc, err);
    }
    ret = convert_qual_type(ret);
    *pr = ret;

    /* Check number of arguments */
    ell = DEREF_int(type_func_ellipsis(fn));
    ptypes = DEREF_list(type_func_ptypes(fn));
    mtypes = DEREF_list(type_func_mtypes(fn));
    if (!EQ_list(mtypes, ptypes)) {
	if (mem) {
	    /* Member function */
	    extra = 1;
	} else {
	    fn = copy_typedef(NULL_id, fn, cv_none);
	    mtypes = ptypes;
	    COPY_list(type_func_mtypes(fn), mtypes);
	}
    }
    if (match_no_args == 0) {
	/* Weren't checked in overload resolution */
	unsigned na = LENGTH_list(args);
	unsigned npars = LENGTH_list(mtypes);
	if (na != npars) {
	    int more = 0;
	    unsigned margs = min_no_args(fn);
	    if (ell & FUNC_VAR_PARAMS) {
		    more = 1;
	    }
	    if (na < margs || (na > npars && !more)) {
		/* Illegal number of arguments */
		if (extra) {
		    /* Report actual numbers of passed arguments */
		    na--;
		    npars--;
		    margs--;
		}
		if (more) {
		    err = ERR_expr_call_args_min(na, na, margs);
		} else if (npars == margs) {
		    err = ERR_expr_call_args_exact(na, na, npars);
		} else {
		    err = ERR_expr_call_args_range(na, na, margs, npars);
		}
		if (ell & FUNC_NON_PROTO) {
		    /* Allowed for non-prototype functions */
		    err = set_severity(err, OPT_weak, -1);
		}
		if (!IS_NULL_err(err)) {
		    if (!IS_NULL_id(id)) {
			ERROR err2 = ERR_expr_call_func(id);
			err = concat_error(err2, err);
		    }
		    report(crt_loc, err);
		}
	    }
	}
    }

    /* Check function argument types */
    p = mtypes;
    q = args;
    pids = DEREF_list(type_func_pids(fn));

    /* Extra implicit argument */
    if (extra && !IS_NULL_list(p) && !IS_NULL_list(q)) {
	EXP b = DEREF_exp(HEAD_list(q));
	TYPE t = DEREF_type(HEAD_list(p));
	if (!IS_NULL_exp(b) && !IS_NULL_type(t)) {
	    /* Non-static member function called with object */
	    TYPE u = t;
	    int temp = 1;
	    CLASS_TYPE cs, ct;
	    TYPE s = DEREF_type(exp_type(b));
	    CV_SPEC qs = DEREF_cv(type_qual(s));
	    CV_SPEC qt = DEREF_cv(type_func_mqual(fn));

	    /* Check for temporary object */
	    while (IS_type_array(s)) {
		s = DEREF_type(type_array_sub(s));
		temp = 0;
	    }
	    while (IS_type_ptr_etc(s)) {
		s = DEREF_type(type_ptr_etc_sub(s));
		temp = 0;
	    }
	    if (temp) {
		TYPE ps;
		if (!(qs & cv_lvalue)) {
		    ERROR ferr = NULL_err;
		    b = make_temporary(s, b, NULL_exp, 0, &ferr);
		    if (!IS_NULL_err(ferr)) {
			    report(crt_loc, ferr);
		    }
		}
		MAKE_type_ptr(cv_none, s, ps);
		MAKE_exp_address(ps, b, b);
	    }

	    /* Check types for base class conversion */
	    while (IS_type_ptr_etc(t)) {
		t = DEREF_type(type_ptr_etc_sub(t));
	    }
	    cs = DEREF_ctype(type_compound_defn(s));
	    ct = DEREF_ctype(type_compound_defn(t));
	    if (!eq_ctype(cs, ct)) {
		GRAPH gs = find_base_class(cs, ct, 1);
		if (IS_NULL_graph(gs)) {
		    err = ERR_expr_ref_func_type(cs);
		} else {
		    OFFSET off;
		    err = check_ambig_base(gs);
		    if (!IS_NULL_graph(gr)) {
			CLASS_TYPE cr = DEREF_ctype(graph_head(gr));
			if (!eq_ctype(cs, cr) && !eq_ctype(cr, ct)) {
			    /* Inherited via intermediate base */
			    GRAPH g1 = find_base_class(cs, cr, 1);
			    if (!IS_NULL_graph(g1)) {
				GRAPH g2 = find_base_class(cr, ct, 1);
				if (!IS_NULL_graph(g2)) {
				    if (!IS_NULL_err(err)) {
					ERROR err2;
					destroy_error(err, 1);
					err = check_ambig_base(g1);
					err2 = check_ambig_base(g2);
					err = concat_error(err, err2);
				    }
				    gs = DEREF_graph(graph_top(g2));
				    gs = find_subgraph(g1, gs, g2);
				}
			    }
			}
		    }
		    if (!IS_NULL_err(err)) {
			/* Report ambiguous bases */
			ERROR err2 = ERR_class_member_lookup_func();
			err = concat_error(err, err2);
		    }
		    off = DEREF_off(graph_off(gs));
		    b = make_base_cast(u, b, off);
		    /* Access should have been checked */
		}
		if (!IS_NULL_err(err)) {
		    if (!IS_NULL_id(id)) {
			ERROR err2 = ERR_expr_call_func(id);
			err = concat_error(err2, err);
		    }
		    report(crt_loc, err);
		}
	    }

	    /* Check type qualifiers */
	    qs &= cv_qual;
	    qt &= cv_qual;
	    if (qs != qt) {
		    MAKE_exp_cast(u, CONV_QUAL, b, b);
	    }
	    qs = (qs & ~qt);
	    if (qs != cv_none) {
		if (IS_NULL_id(id)) {
		    err = ERR_class_this_qual(qs);
		    report(crt_loc, err);
		} else {
		    HASHID nm = DEREF_hashid(id_name(id));
		    if (!IS_hashid_destr(nm)) {
			/* Allowed for destructors */
			ERROR err2;
			err = ERR_class_this_qual(qs);
			err2 = ERR_expr_call_func(id);
			err = concat_error(err2, err);
			report(crt_loc, err);
		    }
		}
	    }
	    COPY_exp(HEAD_list(q), b);
	}
	p = TAIL_list(p);
	q = TAIL_list(q);
    }

    /* Normal arguments */
    if (ell & FUNC_NON_PROTO) {
	weak = option(OPT_weak);
	goto ellipsis_lab;
    }
    while (!IS_NULL_list(p) && !IS_NULL_list(q)) {
	EXP b = DEREF_exp(HEAD_list(q));
	TYPE t = DEREF_type(HEAD_list(p));
	OPTION opt = option(OPT_conv_int_int_impl);
	if (IS_NULL_exp(b)) {
		b = make_error_exp(0);
	}
	if (IS_exp_paren(b)) {
	    /* Parentheses suppress conversion warnings */
	    b = DEREF_exp(exp_paren_arg(b));
	    option(OPT_conv_int_int_impl) = OPTION_ALLOW;
	}
	if (IS_exp_string_lit(b)) {
	    if (option(OPT_printf_string)) {
		/* Check for printf and scanf strings */
		int pf = is_printf_type(t);
		if (pf) {
		    unsigned na = LENGTH_list(q) + 100;
		    STRING fmt = DEREF_str(exp_string_lit_str(b));
		    ftypes = find_printf_args(fmt, na, pf);
		    printf_function = pf;
		}
	    }
	}
	err = NULL_err;
	b = init_assign(t, cv_none, b, &err);
	if (pass_complex_type(t)) {
	    /* Create temporary variable */
	    b = remove_temporary(b, NULL_exp);
	    b = make_temporary(t, b, NULL_exp, 0, &err);
	    MAKE_type_ptr(cv_none, t, t);
	    MAKE_exp_address(t, b, b);
	}
	if (!IS_NULL_err(err)) {
	    err = init_error(err, 0);
	    err = concat_error(err, ERR_expr_call_arg(n));
	    if (!IS_NULL_id(id)) {
		err = concat_error(ERR_expr_call_func(id), err);
	    }
	    report(crt_loc, err);
	}
	option(OPT_conv_int_int_impl) = opt;
	n++;
	COPY_exp(HEAD_list(q), b);
	pids = TAIL_list(pids);
	p = TAIL_list(p);
	q = TAIL_list(q);
    }

    /* Default arguments */
    if (!IS_NULL_list(p)) {
	LIST(EXP)dargs = NULL_list(EXP);
	while (!IS_NULL_list(pids)) {
	    IDENTIFIER pid = DEREF_id(HEAD_list(pids));
	    EXP e = DEREF_exp(id_parameter_init(pid));
	    if (!IS_NULL_exp(e)) {
		TYPE t = DEREF_type(exp_type(e));
		if (pass_complex_type(t)) {
		    /* Create temporary variable */
		    EXP d = DEREF_exp(id_parameter_term(pid));
		    if (!IS_NULL_exp(d)) {
			d = copy_exp(d, NULL_type, NULL_type);
		    }
		    err = NULL_err;
		    e = remove_temporary(e, NULL_exp);
		    MAKE_exp_copy(t, e, e);
		    e = make_temporary(t, e, d, 0, &err);
		    if (!IS_NULL_err(err)) {
			err = concat_error(err, ERR_expr_call_arg(n));
			if (!IS_NULL_id(id)) {
			    ERROR err2 = ERR_expr_call_func(id);
			    err = concat_error(err2, err);
			}
			report(crt_loc, err);
		    }
		    MAKE_type_ptr(cv_none, t, t);
		    MAKE_exp_address(t, e, e);
		} else {
		    MAKE_exp_copy(t, e, e);
		}
		CONS_exp(e, dargs, dargs);
		n++;
	    }
	    pids = TAIL_list(pids);
	}
	if (!IS_NULL_list(dargs)) {
	    dargs = REVERSE_list(dargs);
	    args = APPEND_list(args, dargs);
	}
    }

    /* Ellipsis arguments */
    ellipsis_lab: {
	unsigned wn = n;
	LIST(EXP)wq = q;
	while (!IS_NULL_list(q)) {
	    TYPE t, s;
	    EXP b = DEREF_exp(HEAD_list(q));
	    if (IS_NULL_exp(b)) {
		    b = make_error_exp(0);
	    }
	    b = convert_lvalue(b);
	    b = convert_none(b);
	    t = DEREF_type(exp_type(b));
	    err = NULL_err;
	    s = arg_promote_type(t, &err);
	    if (!EQ_type(s, t)) {
		b = init_assign(s, cv_none, b, &err);
	    }
	    if (!IS_NULL_err(err)) {
		err = init_error(err, 0);
		err = concat_error(err, ERR_expr_call_ellipsis(n));
		if (!IS_NULL_id(id)) {
		    err = concat_error(ERR_expr_call_func(id), err);
		}
		report(crt_loc, err);
	    }
	    COPY_exp(HEAD_list(q), b);
	    n++;
	    q = TAIL_list(q);
	}
	if (weak && !IS_NULL_id(id)) {
	    /* Perform weak prototype analysis */
	    check_weak_args(id, wq, wn);
	}
	if (printf_function) {
	    /* Check printf arguments */
	    if (option(OPT_weak)) {
		check_printf_args(id, ftypes, wq, wn, printf_function);
	    }
	    DESTROY_list(ftypes, SIZE_type);
	}
    }
    IGNORE check_value(OPT_VAL_func_args,(unsigned long)(n - 1));
    return args;
}


/*
    This routine applies the function id to the list of arguments args.
    Any qualifiers used to express id are passed in as qual, since these
    may suppress the virtual call mechanism.  gr gives the base class
    from which a member function is inherited.
*/

EXP
apply_func_id(IDENTIFIER id, QUALIFIER qual, GRAPH gr, LIST(EXP)args)
{
	EXP e;
	TYPE fn;
	TYPE ret;
	DECL_SPEC ds;
	int throws = 1;
	EXP virt = NULL_exp;
	IDENTIFIER fid = id;

	/* Check for non-functions */
	if (!IS_id_function_etc(id)) {
		e = make_error_exp(0);
		return e;
	}

	/* Check for inherited functions */
	ds = DEREF_dspec(id_storage(id));
	if (ds & dspec_inherit) {
		id = DEREF_id(id_alias(id));
		ds = DEREF_dspec(id_storage(id));
	}

	/* Check for trivial functions */
	if (ds & dspec_trivial) {
		e = apply_trivial_func(id, args);
		if (!IS_NULL_exp(e)) {
			DESTROY_list(args, SIZE_exp);
			return e;
		}
	}

	/* Convert the arguments */
	fn = DEREF_type(id_function_etc_type(id));
	args = cast_args(id, fn, gr, args, &ret, 1);

	/* Check for virtual function calls */
	if (ds & dspec_virtual) {
		if (!(qual & qual_explicit)) {
			EXP a = DEREF_exp(HEAD_list(args));
			int know = know_type(a);
			if (know == 0) {
				if (!IS_NULL_exp(a)) {
					TYPE ta = DEREF_type(exp_type(a));
					MAKE_exp_dummy(ta, a, LINK_NONE,
						       NULL_off, 1, virt);
					COPY_exp(HEAD_list(args), virt);
				}
			} else if (know == 2) {
				/* Non-obvious case */
				report(crt_loc, ERR_class_virtual_not(id));
			}
		}
		if (IS_NULL_exp(virt)) {
			/* Explicit call of virtual function */
			if (ds & dspec_pure) {
				/* Call of pure virtual function */
				HASHID nm = DEREF_hashid(id_name(id));
				if (IS_hashid_destr(nm)) {
					/* Calling pure destructor is alright */
					/* EMPTY */
				} else {
					report(crt_loc,
					       ERR_class_abstract_call(id));
				}
			}
			if (!(ds & dspec_used)) {
				/* Mark explicit use */
				reuse_id(id, suppress_usage);
				ds = DEREF_dspec(id_storage(id));
			}
		}
	}
	if ((ds & dspec_friend) && IS_NULL_exp(virt)) {
		/* Call can't throw an exception */
		throws = 0;
	}

	/* Check for token applications */
	if (ds & dspec_token) {
		if ((qual & qual_mark) && !(ds & dspec_reserve)) {
			/* Parenthesised - use function proper */
			/* EMPTY */
		} else {
			TYPE form = DEREF_type(id_function_etc_form(id));
			if (!IS_NULL_type(form) && IS_type_token(form)) {
				IDENTIFIER ext = DEREF_id(type_token_tok(form));
				if (!IS_NULL_id(ext) && IS_id_token(ext)) {
					id = ext;
				}
			}
		}
	}

	/* A function call is a side effect */
	no_side_effects++;

	/* Form the result */
	MAKE_exp_func_id(ret, id, args, virt, e);
	if (pass_complex_type(ret)) {
		/* Allow for complex return types */
		EXP a;
		MAKE_exp_dummy(ret, NULL_exp, LINK_NONE, NULL_off, 0, a);
		if (IS_id_stat_mem_func(id)) {
			/* Insert as second parameter for static member functions */
			EXP b = DEREF_exp(HEAD_list(args));
			COPY_exp(HEAD_list(args), a);
			CONS_exp(b, args, args);
		} else {
			/* Insert as first parameter for other functions */
			CONS_exp(a, args, args);
		}
		COPY_list(exp_func_id_args(e), args);
		COPY_unsigned(exp_func_id_extra(e), 1);
		COPY_type(exp_type(e), type_void);
		MAKE_exp_constr(ret, e, a, a, DEFAULT_USR, e);
	}

	/* Check for exception violations */
	if (throws) {
		IGNORE check_func_throw(fn, fid);
	}
	return e;
}


/*
    This routine applies the function expression a to the list of arguments
    args.
*/

static EXP
apply_func_exp(EXP a, LIST(EXP)args)
{
	/* Find function type */
	EXP e;
	TYPE ret;
	int mem = 0;
	TYPE fn = DEREF_type(exp_type(a));
	CV_SPEC cv = DEREF_cv(type_qual(fn));
	if (cv & cv_lvalue) {
		a = convert_lvalue(a);
		fn = DEREF_type(exp_type(a));
	}
	switch (TAG_type(fn)) {
	case type_ptr_tag:
		fn = DEREF_type(type_ptr_sub(fn));
		break;
	case type_ptr_mem_tag:
		fn = DEREF_type(type_ptr_mem_sub(fn));
		break;
	}

	/* Convert the arguments */
	match_no_args = 0;
	if (IS_exp_call(a)) {
		mem = 1;
	}
	args = cast_args(NULL_id, fn, NULL_graph, args, &ret, mem);
	if (mem) {
		/* Record pointer to function member argument */
		EXP c = DEREF_exp(HEAD_list(args));
		TYPE t = DEREF_type(exp_type(c));
		MAKE_exp_dummy(t, c, LINK_NONE, NULL_off, 1, c);
		COPY_exp(exp_call_arg(a), c);
		COPY_exp(HEAD_list(args), c);
	}

	/* A function call is a side effect */
	no_side_effects++;

	/* Form the result */
	MAKE_exp_func(ret, a, args, e);
	if (pass_complex_type(ret)) {
		/* Allow for complex return types */
		EXP b;
		MAKE_exp_dummy(ret, NULL_exp, LINK_NONE, NULL_off, 0, b);
		CONS_exp(b, args, args);
		COPY_list(exp_func_args(e), args);
		COPY_unsigned(exp_func_extra(e), 1);
		COPY_type(exp_type(e), type_void);
		MAKE_exp_constr(ret, e, b, b, DEFAULT_USR, e);
	}

	/* Check for exception violations */
	IGNORE check_func_throw(fn, NULL_id);
	return e;
}


/*
    This routine constructs the template dependent function call
    'a ( args )', or '( a ) ( args )' if is_paren is true.
*/

static EXP
call_func_templ(EXP a, LIST(EXP) args, int is_paren)
{
	EXP e;
	TYPE ret = type_templ_param;
	if (is_paren) {
		a = make_paren_exp(a);
	}
	CONS_exp(a, args, args);
	MAKE_exp_opn(ret, lex_func_Hop, args, e);
	return e;
}


/*
    This routine constructs the function call expression 'a ( args )'.
*/

EXP
make_func_exp(EXP a, LIST(EXP)args, int rescan)
{
	EXP e;
	TYPE fn;
	unsigned tag;
	unsigned ftag;
	int is_ptr = 0;
	int is_ptr_mem = 0;
	int is_paren = IS_exp_paren(a);

	/* Do reference conversions */
	a = convert_reference(a, REF_FUNCTION);
	args = convert_args(args);

	/* Map '&f' to 'f' */
	tag = TAG_exp(a);
	if (tag == exp_address_tag) {
		/* Non-member function */
		EXP b = DEREF_exp(exp_address_arg(a));
		if (IS_exp_identifier_etc(b)) {
			a = b;
			tag = TAG_exp(a);
			is_paren = 1;
		}
	} else if (tag == exp_address_mem_tag) {
		/* Member function (which better eventually be static) */
		EXP b = DEREF_exp(exp_address_mem_arg(a));
		IDENTIFIER id = DEREF_id(exp_member_id(b));
		if (IS_id_function_etc(id)) {
			while (!IS_NULL_id(id)) {
				if (IS_id_mem_func(id)) {
					report(crt_loc,
					       ERR_over_match_call_mem(id));
					break;
				}
				id = DEREF_id(id_function_etc_over(id));
			}
			a = b;
			tag = TAG_exp(a);
			is_paren = 1;
			is_ptr_mem = 1;
		}
	}

	/* Check function type */
	fn = DEREF_type(exp_type(a));
	ftag = TAG_type(fn);
#if LANGUAGE_CPP
	if (ftag == type_compound_tag) {
		/* Allow for overloading using 'operator ()' */
		if (overload_depth == 0) {
			e = function_overload(a, args);
			return e;
		}
	}
#endif
	if (ftag == type_ptr_tag) {
		/* Allow for pointers to functions */
		fn = DEREF_type(type_ptr_sub(fn));
		ftag = TAG_type(fn);
		is_ptr = 1;
	}
	while (ftag == type_templ_tag) {
		fn = DEREF_type(type_templ_defn(fn));
		ftag = TAG_type(fn);
	}
	if (ftag != type_func_tag) {
		if (ftag == type_token_tag && is_templ_type(fn)) {
			/* Allow for template types */
			e = call_func_templ(a, args, is_paren);
			return e;
		}
		if (ftag != type_error_tag) {
			/* Type should now be a function type */
			ERROR err;
			if (IS_exp_member(a)) {
				IDENTIFIER id = DEREF_id(exp_member_id(a));
				err = ERR_expr_prim_mem(id);
			} else {
				err = ERR_expr_call_op(fn);
			}
			if (ftag == type_ptr_mem_tag && in_ptr_mem_selector) {
				err = concat_error(err,
						   ERR_expr_mptr_oper_paren());
			}
			report(crt_loc, err);
		}
		e = make_error_exp(0);
		return e;
	}

	/* Deal with named functions */
	if (!is_ptr) {
		switch (tag) {
		case exp_identifier_tag:
		case exp_member_tag:
		case exp_ambiguous_tag:
		case exp_undeclared_tag: {
			/* Normal functions, 'f' */
			int dep = 1;
			DECL_SPEC ds;
			IDENTIFIER id;
			QUALIFIER qual;
			EXP extra = NULL_exp;
			NAMESPACE ns = NULL_nspace;
			int acc = crt_access_list.inherit;
			id = DEREF_id(exp_identifier_etc_id(a));
			qual = DEREF_qual(exp_identifier_etc_qual(a));
			if (rescan) {
				id = rescan_func_id(id, qual);
			}
			if (dependent_call(id, args)) {
				/* Call depends on template argument */
				e = call_func_templ(a, args, is_paren);
				return e;
			}
			ds = DEREF_dspec(id_storage(id));
			if (ds & dspec_instance) {
				dep = 0;
			}
			if (qual & qual_explicit) {
				dep = 0;
			}
			if (is_paren) {
				qual |= qual_mark;
			}
			switch (TAG_id(id)) {
			case id_mem_func_tag:
			case id_stat_mem_func_tag:
mem_func_label:
				/* Add argument for member functions */
				extra = make_this_ref(&ns);
				CONS_exp(extra, args, args);
				dep = 0;
				break;
			case id_ambig_tag: {
				/* Check for ambiguous member functions */
				CLASS_TYPE ct = parent_class(id);
				if (!IS_NULL_ctype(ct)) {
					goto mem_func_label;
				}
				break;
			}
			}

			id = resolve_call(id, args, qual, dep);
			switch (TAG_id(id)) {
			case id_function_tag:
				/* Normal function call */
				break;
			case id_mem_func_tag:
				/* Member function call */
				if (is_ptr_mem) {
					fn = DEREF_type(id_mem_func_type(id));
					COPY_type(exp_type(a), fn);
					a = make_ref_exp(a, 1);
					fn = DEREF_type(exp_type(a));
					report(crt_loc, ERR_expr_call_op(fn));
				}
				if (IS_NULL_exp(extra)) {
					/* No associated object */
					report(crt_loc, ERR_expr_call_mem(id));
				} else {
					/* Indicate inherited member function */
					crt_access_list.inherit++;
				}
				break;
			case id_stat_mem_func_tag:
				/* Static member function call */
				if (!IS_NULL_exp(extra)) {
					COPY_exp(HEAD_list(args), NULL_exp);
				}
				break;
			default:
				/* Non-function called */
				if (in_template_decl) {
					e = call_func_templ(a, args, is_paren);
				} else {
					e = make_id_exp(id);
					if (eq_exp(e, a, 0)) {
						e = make_error_exp(0);
					} else {
						e = make_func_exp(e, args, 0);
					}
				}
				return e;
			}
			use_func_id(id, 1, suppress_usage);
			crt_access_list.inherit = acc;
			if (resolved_kind == KIND_CONSTR) {
				e = apply_constr(id, args);
			} else {
				e = apply_func_id(id, qual, NULL_graph, args);
			}
			return e;
		}

		case exp_call_tag: {
			/* Member function selectors */
			EXP b = DEREF_exp(exp_call_ptr(a));
			EXP c = DEREF_exp(exp_call_arg(a));
			tag = TAG_exp(b);
			if (tag == exp_identifier_tag ||
			    tag == exp_member_tag) {
				/* Named function selector, 'c->f' */
				IDENTIFIER id;
				QUALIFIER qual;
				id = DEREF_id(exp_identifier_etc_id(b));
				qual = DEREF_qual(exp_identifier_etc_qual(b));
				if (rescan)id = rescan_func_id(id, qual_nested);
				if (dependent_call(id, args)) {
					e = call_func_templ(a, args, is_paren);
				} else {
					GRAPH gr = DEREF_graph(exp_call_base(a));
					if (is_paren) {
						qual |= qual_mark;
					}
					CONS_exp(c, args, args);
					id = resolve_call(id, args, qual, 0);
					use_func_id(id, 1, suppress_usage);
					if (resolved_kind == KIND_CONSTR) {
						e = apply_constr(id, args);
					} else {
						HASHID nm =
						    DEREF_hashid(id_name(id));
						e = apply_func_id(id, qual, gr,
								  args);
						if (!IS_hashid_name_etc(nm)) {
							/* Check for extra
							 * arguments */
							int v = EXTRA_CONSTR;
							CLASS_TYPE ct =
							    parent_class(id);
							if (IS_hashid_destr(nm)) {
								v = EXTRA_DESTR;
							}
							e = add_constr_args(e, ct, v);
						}
					}
				}
				return e;
			}
			if (tag == exp_undeclared_tag) {
				/* Pseudo-destructor call, 'c->C::~C' */
				IDENTIFIER id = DEREF_id(exp_undeclared_id(b));
				HASHID nm = DEREF_hashid(id_name(id));
				if (!IS_NULL_list(args)) {
					report(crt_loc, ERR_expr_pseudo_args(nm));
				}
				e = trivial_destr(c);
				return e;
			}
			/* Pointer to member function selector, 'a.*f' */
			CONS_exp(c, args, args);
			break;
		}
		}
	}

	/* Form the result for function expressions */
	e = apply_func_exp(a, args);
	return e;
}


/*
    This routine checks whether a function consisting of 'return e ;'
    should be inlined.
*/

static EXP
check_inline_return(EXP e, TYPE ret)
{
	if (IS_NULL_exp(e)) {
		/* No value returned */
		MAKE_exp_value(ret, e);
		return e;
	}
	if (is_const_exp(e, -1)) {
		/* Constant expression returned */
		MAKE_exp_copy(ret, e, e);
		return e;
	}
	return NULL_exp;
}


/*
    Function inlining is generally left to the installers which have a
    far better idea of whether a function should be inlined than the
    producer.  This routine checks whether the function call 'id ( args )'
    should be inlined by the producer.  This is generally done on the
    basis of code size rather than efficiency.  If so it returns the result
    expression.  Otherwise the null expression is returned.
*/

EXP
check_inline(IDENTIFIER id, LIST(EXP)args, TYPE ret)
{
	while (!IS_NULL_list(args)) {
		/* Check argument list */
		EXP a = DEREF_exp(HEAD_list(args));
		if (!IS_NULL_exp(a)) {
			return NULL_exp;
		}
		args = TAIL_list(args);
	}
	if (IS_id_function_etc(id)) {
		/* Check function definition */
		EXP e = DEREF_exp(id_function_etc_defn(id));
		if (!IS_NULL_exp(e) && IS_exp_sequence(e)) {
			LIST(EXP)p = DEREF_list(exp_sequence_first(e));
			p = TAIL_list(p);
			if (IS_NULL_list(p)) {
				/* Empty function definition */
				e = check_inline_return(NULL_exp, ret);
				return e;
			}
			e = DEREF_exp(HEAD_list(p));
			p = TAIL_list(p);
			if (IS_NULL_list(p)) {
				if (!IS_NULL_exp(e) && IS_exp_location(e)) {
					/* Step over location marker */
					e = DEREF_exp(exp_location_arg(e));
				}
				if (!IS_NULL_exp(e) && IS_exp_return_stmt(e)) {
					/* Single return statement */
					e = DEREF_exp(exp_return_stmt_value(e));
					e = check_inline_return(e, ret);
					return e;
				}
			}
		}
	}
	return NULL_exp;
}


/*
    This routine checks whether t is a complex function return or argument
    type, that is to say a class type with a non-trivial constructor,
    destructor, or assignment operator.  The calling convention implemented
    is that such values are returned by means of a reference which is
    passed to the function as the first argument, and that such values
    are passed as arguments as a reference to a copy.
*/

int
pass_complex_type(TYPE t)
{
	if (!IS_NULL_type(t) && IS_type_compound(t)) {
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
		CLASS_INFO cj = (ci & cinfo_trivial);
		if (cj != cinfo_trivial) {
			return 1;
		}
	}
	return 0;
}


/*
    This routine checks whether the type just constructed by the parser
    contains type definitions and so is not suitable for use as a function
    return or parameter type (as indicated by par).  The necessary
    information is stored in the global variable have_type_declaration.
*/

void
func_type_defn(int par)
{
	int td = have_type_declaration;
	if (td == TYPE_DECL_NORMAL || td == TYPE_DECL_ANON) {
		if (par) {
			report(crt_loc, ERR_dcl_fct_typedef_par());
		} else {
			report(crt_loc, ERR_dcl_fct_typedef_ret());
		}
	}
	return;
}


/*
    This routine creates the parameter type for a function or template
    parameter (as indicated by loc) declared with type t.  Thus functions
    and, for function parameters, arrays are converted to pointers.
*/

TYPE
make_param_type(TYPE t, int loc)
{
	switch (TAG_type(t)) {
	case type_func_tag: {
		/* Function parameters are adjusted to pointers */
		member_func_type(NULL_ctype, id_parameter_tag, t);
		check_weak_func(t, 0);
		MAKE_type_ptr(cv_none, t, t);
		break;
	}
	case type_array_tag: {
		/* Array parameters are adjusted to pointers */
		if (loc == CONTEXT_PARAMETER || loc == CONTEXT_WEAK_PARAM) {
			t = DEREF_type(type_array_sub(t));
			MAKE_type_ptr(cv_none, t, t);
		}
		break;
	}
	}
	return t;
}


/*
    A parameter cannot include a type of the form pointer to unbound array
    or reference to unbound array.  This routine returns an error if the type
    t includes a type of this form.  Strictly the parameters of any function
    components should also be checked, but these will have already been
    handled by a previous check.
*/

ERROR
check_param_type(IDENTIFIER id, TYPE t)
{
	TYPE s = t;
	int state = 0;
	while (!IS_NULL_type(s)) {
		switch (TAG_type(s)) {
		case type_top_tag:
		case type_bottom_tag: {
			/* Void types */
			if (state) {
				return NULL_err;
			}
			return ERR_dcl_fct_par_void(id, t);
		}
		case type_ptr_tag:
		case type_ref_tag: {
			/* Pointer and reference types */
			s = DEREF_type(type_ptr_etc_sub(s));
			state = 1;
			break;
		}
		case type_array_tag: {
			/* Array types */
			if (state) {
				NAT n = DEREF_nat(type_array_size(s));
				if (IS_NULL_nat(n)) {
					return ERR_dcl_fct_par_array(id, t);
				}
			}
			s = DEREF_type(type_array_sub(s));
			state = 0;
			break;
		}
		default:
			/* Other types */
			return NULL_err;
		}
	}
	return NULL_err;
}


/*
    This routine adjusts the function linkage specifier cv to include
    the current linkage specifier.
*/

CV_SPEC
func_linkage(CV_SPEC cv)
{
	DECL_SPEC ln = crt_linkage;
	if (ln) {
		if (ln & dspec_c) {
			cv |= cv_c;
		}
		if (ln & dspec_cpp) {
			cv |= cv_cpp;
		}
	}
	return cv;
}


/*
    This routine constructs the function type with parameter declarations
    given by the current namespace and const-volatile qualifiers cv.  The
    kind of function is given by ell, which is a combination of the
    FUNC_* values defined in function.h.  The function return type is
    usually filled in later (by inject_pre_type) but may be specified
    by r.  Note that function and array parameters have already been
    adjusted to pointers by make_param_decl.
*/

TYPE
make_func_type(TYPE r, int ell, CV_SPEC cv, LIST(TYPE) ex)
{
	int no_param = 0;
	TYPE t = NULL_type;
	LIST(IDENTIFIER) p1;
	IDENTIFIER id = NULL_id;
	LIST(TYPE) q = NULL_list(TYPE);
	LIST(IDENTIFIER) p = NULL_list(IDENTIFIER);

	/* Get parameter declarations */
	NAMESPACE ns = crt_namespace;
	MEMBER mem = DEREF_member(nspace_last(ns));

	/* Build up parameter type list (deleting cv-qualifiers) */
	while (!IS_NULL_member(mem)) {
		id = DEREF_id(member_id(mem));
		if (!IS_NULL_id(id) && IS_id_parameter(id)) {
			t = DEREF_type(id_parameter_type(id));
			if ((ell & FUNC_WEAK) && !is_arg_promote(t)) {
				DECL_SPEC ds;
				t = arg_promote_type(t, KILL_err);
				ds = DEREF_dspec(id_storage(id));
				ds |= dspec_virtual;
				COPY_dspec(id_storage(id), ds);
			}
			t = qualify_type(t, cv_none, 0);
			CONS_type(t, q, q);
			CONS_id(id, p, p);
			no_param++;
		}
		mem = DEREF_member(member_next(mem));
	}

	/* Check for non-prototype functions */
	if (IS_NULL_type(r)) {
		if (ell & FUNC_NON_PROTO) {
			report(crt_loc, ERR_dcl_fct_nonproto());
			if (ell == FUNC_WEAK && no_param == 0) {
				/* Can't have 't weak ()' */
				report(crt_loc, ERR_dcl_fct_par_weak());
			}
#if LANGUAGE_CPP
			ell &= FUNC_ELLIPSIS;
#endif
		} else {
			report(crt_loc, ERR_dcl_fct_proto());
		}
	}

	/* Check for '( ... )' */
	if (no_param == 0 && (ell & FUNC_ELLIPSIS)) {
		report(crt_loc, ERR_dcl_fct_par_ellipsis());
	}

	/* Check for '( void )' */
	if (no_param == 1 && !(ell & FUNC_ELLIPSIS)) {
		/* Precisely one parameter (in t and id) */
		if (IS_type_top(t)) {
			HASHID nm = DEREF_hashid(id_name(id));
			if (!IS_hashid_anon(nm)) {
				report(crt_loc, ERR_dcl_fct_par_empty());
			}
			DESTROY_list(q, SIZE_type);
			DESTROY_list(p, SIZE_id);
			q = NULL_list(TYPE);
			p = NULL_list(IDENTIFIER);
		}
	}

	/* Check for other void parameters */
	p1 = p;
	while (!IS_NULL_list(p1)) {
		ERROR err;
		id = DEREF_id(HEAD_list(p1));
		t = DEREF_type(id_parameter_type(id));
		err = check_param_type(id, t);
		if (!IS_NULL_err(err)) {
			/* Void or other illegal parameter type */
			report(crt_loc, err);
		}
		p1 = TAIL_list(p1);
	}

	/* Construct the function type */
	MAKE_type_func(cv_none, r, q, ell, cv, q, ns, p, ex, t);
	return t;
}


/*
    Each function type has two lists of parameter types, ptypes, which
    gives the actual declared parameters, and mtypes, which has an extra
    reference to class parameter for non-static member functions, or an
    extra null parameter for static member functions.  This routine sets
    the mtypes field of t from the ptypes field according to whether or not
    ct is the null class and the tag of an associated declaration, itag.
    Note that member function types always have C++ linkage.
*/

void
member_func_type(CLASS_TYPE ct, unsigned itag, TYPE t)
{
	unsigned tag = TAG_type(t);
	while (tag == type_templ_tag) {
		t = DEREF_type(type_templ_defn(t));
		tag = TAG_type(t);
	}
	if (tag == type_func_tag) {
		CV_SPEC cv = DEREF_cv(type_func_mqual(t));
		CV_SPEC qual = (cv & cv_qual);
		LIST(TYPE) ptypes = DEREF_list(type_func_ptypes(t));
		LIST(TYPE) mtypes = DEREF_list(type_func_mtypes(t));
		if (IS_NULL_ctype(ct)) {
			/* Non-member functions */
			if (qual && itag != id_type_alias_tag) {
				/* Can't have cv-qualifiers */
				report(crt_loc, ERR_dcl_fct_cv(qual));
				cv &= ~cv_qual;
				COPY_cv(type_func_mqual(t), cv);
			}
			if (!EQ_list(ptypes, mtypes)) {
				/* Set mtypes equal to ptypes */
				COPY_list(type_func_mtypes(t), ptypes);
			}
		} else {
			/* Member functions */
			if (EQ_list(ptypes, mtypes)) {
				/* Add extra argument to mtypes */
				TYPE r;
				if (itag == id_mem_func_tag) {
					IDENTIFIER cid =
					    DEREF_id(ctype_name(ct));
					cv = (qual | cv_cpp);
					qual |= cv_lvalue;
					MAKE_type_compound(qual, ct, r);
					COPY_id(type_name(r), cid);
					MAKE_type_ref(cv_none, r, r);
				} else {
					if (qual) {
						/* Can't have cv-qualifiers */
						report(crt_loc,
						       ERR_dcl_fct_cv(qual));
					}
					r = NULL_type;
					cv = cv_cpp;
				}
				CONS_type(r, ptypes, mtypes);
				COPY_list(type_func_mtypes(t), mtypes);
				COPY_cv(type_func_mqual(t), cv);
			} else {
				/* Don't check existing extra argument */
				/* EMPTY */
			}
		}
	}
	return;
}


/*
    A parameter list can only be used in a function definition.  This
    routine checks the function type t with def being true for a function
    definition.
*/

void
check_weak_func(TYPE t, int def)
{
	int ell = DEREF_int(type_func_ellipsis(t));
	if (ell == FUNC_PARAMS) {
		/* Have parameter list '( a1, a2, ..., an )' */
		if (def) {
			LOCATION loc;
			LIST(TYPE) q = NULL_list(TYPE);
			LIST(IDENTIFIER) p = DEREF_list(type_func_pids(t));
			NAMESPACE ns = DEREF_nspace(type_func_pars(t));
			MEMBER mem = DEREF_member(nspace_last(ns));
			loc = decl_loc;
			bad_crt_loc++;
			while (!IS_NULL_member(mem)) {
				IDENTIFIER id = DEREF_id(member_id(mem));
				if (!IS_NULL_id(id)) {
					if (IS_id_weak_param(id)) {
						/* Implicitly declare
						 * parameter */
						ERROR err;
						TYPE s = type_sint;
						int par = CONTEXT_WEAK_PARAM;
						DEREF_loc(id_loc(id), decl_loc);
						id = make_param_decl(dspec_none, s, id, par);
						init_param(id, NULL_exp);
						err = ERR_dcl_fct_par_impl(id);
						if (!IS_NULL_err(err)) {
							ERROR err2 = ERR_dcl_type_infer(s);
							err = concat_error(err, err2);
							report(decl_loc, err);
						}
						CONS_id(id, p, p);
						CONS_type(s, q, q);
					} else if (IS_id_parameter(id)) {
						/* Add parameter to list */
						TYPE s = DEREF_type(id_parameter_type(id));
						if (!is_arg_promote(s)) {
							DECL_SPEC ds;
							s = arg_promote_type(s, KILL_err);
							ds = DEREF_dspec(id_storage(id));
							ds |= dspec_virtual;
							COPY_dspec(id_storage(id), ds);
						}
						s = qualify_type(s, cv_none, 0);
						CONS_id(id, p, p);
						CONS_type(s, q, q);
					}
				}
				mem = DEREF_member(member_next(mem));
			}
			COPY_list(type_func_ptypes(t), q);
			COPY_list(type_func_mtypes(t), q);
			COPY_list(type_func_pids(t), p);
			bad_crt_loc--;
			decl_loc = loc;
			ell = FUNC_WEAK_PARAMS;
		} else {
			report(crt_loc, ERR_dcl_fct_weak());
			ell = FUNC_NO_PARAMS;
		}
	} else if (ell == FUNC_NO_PARAMS) {
		/* Have empty parameter list '()' */
		if (def) {
			ell = FUNC_WEAK_PARAMS;
		}
	}
	COPY_int(type_func_ellipsis(t), ell);
	return;
}


/*
    This routine checks the function components of an object with the
    given identifier tag and type t.
*/

void
object_type(TYPE t, unsigned tag)
{
	int depth = 0;
	if (tag == id_type_alias_tag || tag == null_tag) {
		/* Force errors in these cases */
		depth = 2;
	}
	while (!IS_NULL_type(t)) {
		assert(ORDER_type == 18);
		switch (TAG_type(t)) {
		case type_func_tag: {
			/* Function types */
			LIST(TYPE) ex;
			CV_SPEC cv = DEREF_cv(type_func_mqual(t));

			/* Check function qualifiers */
			CV_SPEC mq = (cv & cv_qual);
			CV_SPEC lq = (cv & cv_language);
			if (depth == 0) {
				if (tag == id_mem_func_tag) {
					/* Member functions have C++ linkage */
					lq = cv_cpp;
				} else {
					if (mq) {
						/* Can't have cv-qualifiers */
						report(crt_loc,
						       ERR_dcl_fct_cv_decl(mq));
						mq = cv_none;
					}
					if (tag == id_stat_mem_func_tag) {
						/* Member functions have C++
						 * linkage */
						lq = cv_cpp;
					}
				}
			}
			if (lq == cv_none) {
				lq = cv_lang;
			}
			COPY_cv(type_func_mqual(t), (mq | lq));

			/* Check default arguments */
			if (depth && check_func_dargs(t, 0, 0)) {
				report(crt_loc, ERR_dcl_fct_default_bad());
			}

			/* Check exception specifiers */
			ex = DEREF_list(type_func_except(t));
			if (!EQ_list(ex, empty_type_set)) {
				if (!EQ_list(ex, univ_type_set)) {
					ulong n = (ulong)LENGTH_list(ex);
					IGNORE check_value(OPT_VAL_exception_specs, n);
				}
				if (depth > 1) {
					report(crt_loc, ERR_except_spec_bad());
				}
			}

			/* Recheck parameter types */
			if (depth > 1) {
				LIST(TYPE)p;
				p = DEREF_list(type_func_ptypes(t));
				while (!IS_NULL_list(p)) {
					TYPE s = DEREF_type(HEAD_list(p));
					s = find_func_type(s);
					if (!IS_NULL_type(s)) {
						ex = DEREF_list(type_func_except(s));
						if (!EQ_list(ex, empty_type_set)) {
							report(crt_loc, ERR_except_spec_bad());
						}
					}
					p = TAIL_list(p);
				}
			}
			return;
		}
		case type_ptr_tag: {
			t = DEREF_type(type_ptr_sub(t));
			depth++;
			break;
		}
		case type_ref_tag: {
			t = DEREF_type(type_ref_sub(t));
			break;
		}
		case type_ptr_mem_tag: {
			t = DEREF_type(type_ptr_mem_sub(t));
			depth++;
			break;
		}
		case type_array_tag: {
			t = DEREF_type(type_array_sub(t));
			depth++;
			break;
		}
		case type_templ_tag: {
			t = DEREF_type(type_templ_defn(t));
			break;
		}
		default:
			/* Other types */
			return;
		}
	}
	return;
}


/*
    This routine checks the function or function typedef id of type t,
    including checking that if a default argument is given for a
    particular parameter one is also given for all subsequent parameters.
    The redeclaration case, where default arguments can be inherited
    from the previous declaration is dealt with by redecl_func_type.
*/

void
decl_func_type(IDENTIFIER id, TYPE t, int def)
{
	NAMESPACE pns;
	int is_templ = 0;
	unsigned tag = TAG_id(id);

	/* Step over template components */
	if (IS_type_templ(t)) {
		t = check_templ_params(t, id);
		is_templ = 1;
	}
	pns = DEREF_nspace(type_func_pars(t));
	COPY_id(nspace_name(pns), id);

	/* Check default arguments */
	IGNORE check_func_dargs(t, 1, 0);

	/* Check cv-qualifiers */
	switch (tag) {
	case id_function_tag:
	case id_mem_func_tag:
	case id_stat_mem_func_tag: {
		/* Allow for member functions */
		CLASS_TYPE ct = parent_class(id);
		member_func_type(ct, tag, t);

		/* Allow for overloading of template functions */
		if (is_templ) {
			templ_func_decl(id);
		} else {
			IDENTIFIER over = DEREF_id(id_function_etc_over(id));
			if (!IS_NULL_id(over)) {
				/* Overloads a template function */
				DECL_SPEC ds = DEREF_dspec(id_storage(over));
				if (ds & dspec_template) {
					templ_func_decl(id);
				}
			}
		}
		break;
	}
	default:
		/* Allow for function typedefs */
		member_func_type(NULL_ctype, tag, t);
		break;
	}
	UNUSED(def);
	return;
}


/*
    This routine checks and unifies the default arguments for the equal
    function types s and t.  It returns the number of default arguments
    added by this unification.
*/

static unsigned
redecl_func_dargs(TYPE s, TYPE t)
{
    unsigned nargs = 0;
    if (IS_type_func(s) && IS_type_func(t)) {
	int started = 0;
	LIST(IDENTIFIER) ps = DEREF_list(type_func_pids(s));
	LIST(IDENTIFIER) pt = DEREF_list(type_func_pids(t));
	while (!IS_NULL_list(ps) && !IS_NULL_list(pt)) {
	    ERROR err = NULL_err;
	    IDENTIFIER as = DEREF_id(HEAD_list(ps));
	    IDENTIFIER at = DEREF_id(HEAD_list(pt));
	    EXP ds = DEREF_exp(id_parameter_init(as));
	    EXP dt = DEREF_exp(id_parameter_init(at));
	    if (IS_NULL_exp(ds)) {
		/* No existing default argument */
		if (IS_NULL_exp(dt)) {
		    if (started) {
			/* Missing default arguments */
			TYPE r = DEREF_type(id_parameter_type(at));
			err = ERR_dcl_fct_default_missing(at);
			MAKE_exp_value(r, dt);
			COPY_exp(id_parameter_init(at), dt);
			COPY_exp(id_parameter_init(as), dt);
		    }
		} else {
		    /* New default argument */
		    COPY_exp(id_parameter_init(as), dt);
		    dt = DEREF_exp(id_parameter_term(at));
		    COPY_exp(id_parameter_term(as), dt);
		    nargs++;
		    started = 1;
		}
	    } else {
		/* Existing default argument */
		if (IS_NULL_exp(dt)) {
		    /* Inherited default argument */
		    COPY_exp(id_parameter_init(at), ds);
		    ds = DEREF_exp(id_parameter_term(as));
		    COPY_exp(id_parameter_term(at), ds);
		} else {
		    /* Redefined default argument */
		    PTR(LOCATION)sloc = id_loc(as);
		    if (eq_exp(ds, dt, 0)) {
			err = ERR_dcl_fct_default_dup(at, sloc);
		    } else {
			/* NOT YET IMPLEMENTED: dt uncompiled */
			err = ERR_dcl_fct_default_redef(at, sloc);
		    }
		    COPY_exp(id_parameter_init(as), dt);
		    dt = DEREF_exp(id_parameter_term(at));
		    COPY_exp(id_parameter_term(as), dt);
		}
		started = 1;
	    }
	    if (!IS_NULL_err(err)) {
		/* Report any errors */
		LOCATION loc;
		DEREF_loc(id_loc(at), loc);
		report(loc, err);
	    }
	    ps = TAIL_list(ps);
	    pt = TAIL_list(pt);
	}
    }
    return nargs;
}


/*
    This routine deals with the compatible redeclaration of the function
    id of type s to have type t.  It unifies the parameter types, checking
    default arguments etc.  It also checks any exception specifications
    for the two declarations.  The parameter names in the returned type
    are those from t if def is true, and those from s otherwise.
*/

TYPE
redecl_func_type(IDENTIFIER id, TYPE s, TYPE t, int def, int dargs)
{
	TYPE fs = s;
	TYPE ft = t;
	CV_SPEC qs, qt;
	NAMESPACE ns, nt;
	unsigned tag = TAG_id(id);

	/* Check template components */
	redecl_template(&fs, &ft, id);
	ns = DEREF_nspace(type_func_pars(fs));
	nt = DEREF_nspace(type_func_pars(ft));
	COPY_id(nspace_name(ns), id);
	COPY_id(nspace_name(nt), id);

#if LANGUAGE_C
	/* Copy composite type information */
	if (def) {
		TYPE ret = DEREF_type(type_func_ret(fs));
		int ell = DEREF_int(type_func_ellipsis(fs));
		LIST(TYPE)ptypes = DEREF_list(type_func_ptypes(fs));
		COPY_list(type_func_ptypes(ft), ptypes);
		COPY_int(type_func_ellipsis(ft), ell);
		COPY_type(type_func_ret(ft), ret);
	}
#endif

	/* Check default arguments */
	if (dargs && redecl_func_dargs(fs, ft)) {
		if (IS_type_templ(t)) {
			report(decl_loc, ERR_dcl_fct_default_templ());
		}
	}

	/* Check exception specifications */
	if (eq_except(s, t) != 2) {
		PTR(LOCATION)loc = id_loc(id);
		report(decl_loc, ERR_except_spec_wrong(id, loc));
	}

	/* Check cv-qualifiers */
	switch (tag) {
	case id_mem_func_tag:
	case id_stat_mem_func_tag: {
		/* Allow for member functions */
		CLASS_TYPE ct = parent_class(id);
		member_func_type(ct, tag, ft);
		break;
	}
	default:
		/* Allow for function typedefs */
		member_func_type(NULL_ctype, tag, ft);
		break;
	}

	/* Check function qualifiers */
	qs = DEREF_cv(type_func_mqual(fs));
	qt = DEREF_cv(type_func_mqual(ft));
	if (qs != qt) {
		qs &= cv_language;
		qt &= cv_language;
		if (qs != qt) {
			/* Language specifiers don't match */
			string ln = linkage_string(dspec_none, qs);
			report(decl_loc, ERR_dcl_link_func(ln));
		}
	}

	/* Select type to continue with */
	if (def) {
		LIST(IDENTIFIER) sids = DEREF_list(type_func_pids(fs));
		LIST(IDENTIFIER) tids = DEREF_list(type_func_pids(ft));
		if (!EQ_list(sids, tids)) {
			while (!IS_NULL_list(sids) && !IS_NULL_list(tids)) {
				/* Identify parameters */
				IDENTIFIER sid = DEREF_id(HEAD_list(sids));
				IDENTIFIER tid = DEREF_id(HEAD_list(tids));
				tid = chase_alias(tid);
				sid = chase_alias(sid);
				COPY_id(id_alias(sid), tid);
				tids = TAIL_list(tids);
				sids = TAIL_list(sids);
			}
		}
		if (IS_type_templ(t)) {
			/* Reset primary function template */
			reset_primary_templ(s, t);
		}
		s = t;
	}
	return s;
}


/*
    This routine returns the function component of a function, pointer to
    function, or pointer to member function type.
*/

TYPE
find_func_type(TYPE t)
{
	if (!IS_NULL_type(t)) {
		unsigned tag = TAG_type(t);
		if (tag == type_ref_tag) {
			t = DEREF_type(type_ref_sub(t));
			tag = TAG_type(t);
		}
		if (tag == type_ptr_tag) {
			t = DEREF_type(type_ptr_sub(t));
			tag = TAG_type(t);
		} else if (tag == type_ptr_mem_tag) {
			t = DEREF_type(type_ptr_mem_sub(t));
			tag = TAG_type(t);
		}
		if (tag == type_func_tag) {
			return t;
		}
	}
	return NULL_type;
}


/*
    The location decl_loc refers to the current declarator.  This value
    needs to be stored during parameter declarations and this stack is
    used for this purpose.
*/

static STACK(LOCATION) decl_locs = NULL_stack(LOCATION);


/*
    This routine is called at the start of a list of function parameters to
    initialise the parameter namespace.  id gives the associated function
    name (or the null identifier).
*/

void
begin_param(IDENTIFIER id)
{
	NAMESPACE ns = make_namespace(id, nspace_param_tag, 0);
	push_namespace(ns);
	PUSH_loc(decl_loc, decl_locs);
	return;
}


/*
    This routine is called at the end of a list of function parameters.
*/

void
end_param(void)
{
	IGNORE pop_namespace();
	POP_loc(decl_loc, decl_locs);
	return;
}


/*
    This routine adjusts the parameter namespace of the dfunction type
    t used in a function definition.
*/

void
adjust_param(TYPE t)
{
	NAMESPACE ns;
	while (IS_type_templ(t)) {
		t = DEREF_type(type_templ_defn(t));
	}
	ns = DEREF_nspace(type_func_pars(t));
	MODIFY_nspace_block_etc(nspace_block_tag, ns);
	report(crt_loc, ERR_dcl_fct_typedef());
	return;
}


/*
    This routine reads a list of function parameters, returning true for
    a function definition.
*/

int
function_params(TYPE t)
{
	int def = 0;
	if (IS_type_func(t)) {
		int func = have_func_declarator;
		int ell = DEREF_int(type_func_ellipsis(t));
		NAMESPACE ns = DEREF_nspace(type_func_pars(t));
		in_weak_param++;
		push_namespace(ns);
		while (predict_dspec(0)) {
			if (!func) {
				adjust_param(t);
				func = 1;
			}
			if (ell != FUNC_NO_PARAMS && ell != FUNC_PARAMS) {
				/* Can't have parameters with prototype */
				report(crt_loc, ERR_dcl_fct_par_proto());
				ell = FUNC_PARAMS;
			}
			parse_decl(NULL_type, dspec_none);
			def = 1;
		}
		if (predict_func_defn()) {
			if (!func)adjust_param(t);
			def = 1;
		}
		check_weak_func(t, def);
		IGNORE pop_namespace();
		in_weak_param--;
	}
	return def;
}


/*
    This variable is used to hold the main function.
*/

IDENTIFIER main_function = NULL_id;


/*
    This routine checks the type t of the main function nm.  The return
    type must always be 'int', but the parameter types are implementation
    dependent.  Basically, anything other than:

	    int main ( void ) ;
	    int main ( int, char **, [extra parameters] ) ;

    is deemed to be unorthodox.
*/

TYPE
check_main(TYPE t, HASHID nm)
{
    int ok = 0;
    if (IS_type_func(t)) {
	TYPE r = DEREF_type(type_func_ret(t));
	LIST(TYPE) p = DEREF_list(type_func_ptypes(t));
	int ell = DEREF_int(type_func_ellipsis(t));
	if (!eq_type_unqual(r, type_sint)) {
	    /* Return type is wrong */
	    ERROR err = ERR_basic_start_main_ret(r, nm);
	    report(crt_loc, err);
	}
	if (IS_NULL_list(p)) {
	    /* Check for no parameter case */
	    if (!(ell & FUNC_ELLIPSIS)) {
		    ok = 2;
	    }
	} else {
	    /* Check for two parameter case */
	    TYPE s = DEREF_type(HEAD_list(p));
	    if (eq_type_unqual(s, type_sint)) {
		p = TAIL_list(p);
		if (!IS_NULL_list(p)) {
		    s = DEREF_type(HEAD_list(p));
		    if (IS_type_ptr(s)) {
			s = DEREF_type(type_ptr_sub(s));
			if (IS_type_ptr(s)) {
			    s = DEREF_type(type_ptr_sub(s));
			    if (eq_type_unqual(s, type_char)) {
				p = TAIL_list(p);
				if (IS_NULL_list(p)) {
				    if (!(ell & FUNC_ELLIPSIS)) {
					ok = 2;
				    } else {
					ok = 1;
				    }
				} else {
				    ok = 1;
				}
			    }
			}
		    }
		}
	    }
	}
    }
    if (!ok) {
	/* Warn about unorthodox parameter types */
	ERROR err = ERR_basic_start_main_proto(t, nm);
	report(crt_loc, err);
    }
    return t;
}


/*
    This routine rechecks the main function id.  In particular 'main' can't
    be overloaded.
*/

void
recheck_main(IDENTIFIER id)
{
	TYPE fn = DEREF_type(id_function_etc_type(id));
	IDENTIFIER over = DEREF_id(id_function_etc_over(id));
	if (!IS_NULL_id(over) || IS_type_templ(fn)) {
		/* Can't overload 'main' */
		report(decl_loc, ERR_basic_start_main_over(id));
	}
	main_function = id;
	return;
}


/*
    These variables are used to hold information concerning the current
    function, including its name, return type and exception specification.
*/

IDENTIFIER crt_func_id = NULL_id;
TYPE crt_func_return = NULL_type;
int crt_func_complex = 0;


/*
    Note that it is indirectly possible to have nested function definitions
    (a function definition can include a class definition which can include
    a member function definition).  These stacks are used to preserve
    information across nested functions.
*/

static struct {
	STACK(IDENTIFIER)id;
	STACK(TYPE)ret;
	STACK(int)unreached;
	STACK(int)declaration;
	STACK(int)destructor;
	STACK(int)handler;
	STACK(STACK(EXP))loops;
	STACK(NAMESPACE)labels;
	STACK(LIST(EXP))solves;
	STACK(LIST(EXP))tries;
	STACK(unsigned long)opts;
} func_stack = {
	NULL_stack(IDENTIFIER),
	NULL_stack(TYPE),
	NULL_stack(int),
	NULL_stack(int),
	NULL_stack(int),
	NULL_stack(int),
	NULL_stack(STACK(EXP)),
	NULL_stack(NAMESPACE),
	NULL_stack(LIST(EXP)),
	NULL_stack(LIST(EXP)),
	NULL_stack(unsigned long)
};


/*
    This routine is called at the start of a function definition.  t gives
    the function type.
*/

void
begin_function(IDENTIFIER id)
{
	TYPE t;
	int ell;
	TYPE ret;
	NAMESPACE ns;
	NAMESPACE bns;
	unsigned long n;
	LIST(TYPE) ex;
	ERROR err = NULL_err;
	LIST(IDENTIFIER) p;
	unsigned long npars = 0;

	/* Check for previous definition */
	if (IS_id_function_etc(id)) {
		EXP e = DEREF_exp(id_function_etc_defn(id));
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		t = DEREF_type(id_function_etc_type(id));
		if (IS_NULL_exp(e)) {
			/* Mark with dummy definition */
			MAKE_exp_value(t, e);
			COPY_exp(id_function_etc_defn(id), e);
		} else {
			/* Already defined */
			PTR(LOCATION) loc = id_loc(id);
			report(decl_loc, ERR_basic_odr_def_func(id, loc));
		}
		if ((ds & dspec_inline) && (ds & dspec_called)) {
			report(decl_loc, ERR_dcl_fct_spec_inline_call(id));
		}
	} else {
		t = type_func_void;
	}
	COPY_loc(id_loc(id), decl_loc);
	stmt_loc = crt_loc;

	/* Decompose function type */
	while (IS_type_templ(t)) {
		t = DEREF_type(type_templ_defn(t));
	}
	ell = DEREF_int(type_func_ellipsis(t));
	p = DEREF_list(type_func_pids(t));
	ex = DEREF_list(type_func_except(t));
	ns = DEREF_nspace(type_func_pars(t));
	if (IS_NULL_nspace(ns)) {
		ns = make_namespace(id, nspace_param_tag, 0);
	}
	bns = ns;

	/* Check return type */
	ret = DEREF_type(type_func_ret(t));
	ret = check_ret_type(ret, &err, 1);
	if (!IS_NULL_err(err)) {
		err = concat_error(err, ERR_dcl_fct_ret());
		report(decl_loc, err);
	}

	/* Save old function data */
	PUSH_id(crt_func_id, func_stack.id);
	PUSH_type(crt_func_return, func_stack.ret);
	PUSH_int(unreached_code, func_stack.unreached);
	PUSH_int(in_declaration, func_stack.declaration);
	PUSH_int(have_destructor, func_stack.destructor);
	PUSH_int(in_func_handler, func_stack.handler);
	PUSH_stack(crt_loop_stack, func_stack.loops);
	PUSH_nspace(label_namespace, func_stack.labels);
	PUSH_list(all_solve_stmts, func_stack.solves);
	PUSH_list(all_try_blocks, func_stack.tries);
	n = crt_option_value(OPT_VAL_statement_depth);
	PUSH_ulong(n, func_stack.opts);
	n = crt_option_value(OPT_VAL_nested_class);
	PUSH_ulong(n, func_stack.opts);
	n = number_errors;
	PUSH_ulong(n, func_stack.opts);

	/* Set up new function data */
	commentary(id);
	crt_func_id = id;
	crt_func_return = ret;
	crt_func_complex = pass_complex_type(ret);
	unreached_code = 0;
	unreached_last = 0;
	unreached_fall = 1;
	in_declaration = 0;
	have_destructor = 0;
	in_func_handler = 0;
	crt_loop_stack = NULL_stack(EXP);
	all_solve_stmts = NULL_list(EXP);
	all_try_blocks = NULL_list(EXP);
	crt_option_value(OPT_VAL_statement_depth) = 0;
	crt_option_value(OPT_VAL_nested_class) = 0;
	if (option(OPT_variable)) {
		record_location++;
	}
	label_namespace = make_namespace(id, nspace_label_tag, 0);
	if (do_dump) {
		dump_declare(id, &decl_loc, 1);
	}

	/* Modify function parameter namespace */
	if (IS_nspace_block(bns)) {
		bns = NULL_nspace;
	}
	MODIFY_nspace_block_etc(nspace_block_tag, ns);
	COPY_id(nspace_name(ns), id);

	/* Check function parameters */
	crt_id_qualifier = qual_none;
	while (!IS_NULL_list(p)) {
		IDENTIFIER par = DEREF_id(HEAD_list(p));
		IDENTIFIER par2 = DEREF_id(id_alias(par));
		HASHID pnm = DEREF_hashid(id_name(par));
		TYPE pt = DEREF_type(id_parameter_type(par));
		unsigned ptag = TAG_type(pt);
		if (!EQ_id(par2, par)) {
			/* Rename parameter if necessary */
			par2 = chase_alias(par2);
			pnm = DEREF_hashid(id_name(par2));
			COPY_hashid(id_name(par), pnm);
			COPY_id(id_alias(par), par2);
		}
		if (do_local) {
			LOCATION loc;
			DEREF_loc(id_loc(par), loc);
			dump_declare(par, &loc, 1);
		}
		if (IS_hashid_anon(pnm)) {
			/* Report anonymous parameters */
			LOCATION loc;
			DEREF_loc(id_loc(par), loc);
			report(loc, ERR_dcl_fct_par_anon());
		}
		switch (ptag) {
		case type_top_tag:
		case type_bottom_tag:
			/* Void parameters have already been reported */
			break;
		case type_ref_tag:
			/* References don't need checking */
			break;
		default:
			/* Check for incomplete types */
			err = check_complete(pt);
			if (!IS_NULL_err(err)) {
				LOCATION loc;
				ERROR err2 = ERR_basic_types_par_incompl(par);
				err = concat_error(err, err2);
				DEREF_loc(id_loc(par), loc);
				report(loc, err);
			}
			break;
		}
		if (option(OPT_decl_hide)) {
			check_hiding(par);
		}
		npars++;
		p = TAIL_list(p);
	}

	/* Declare parameters */
	push_namespace(ns);
	block_namespace = bns;
	IGNORE check_value(OPT_VAL_func_pars, npars);

	/* Deal with the this pointer */
	if (IS_id_mem_func(id)) {
		IGNORE make_this_decl(id);
	}

	/* Deal with the ellipsis parameter */
	if (ell & FUNC_ELLIPSIS) {
		make_ellipsis_decl();
	}

	/* Create dummy try block */
	start_try_check(ex);
	return;
}


/*
    This routine is called at the end of a function definition.  The
    expression body gives the compound statement comprising the definition.
    Note that the parameters are in the outermost scope of body and so
    have already been taken out of scope.
*/

EXP
end_function(IDENTIFIER id, EXP body)
{
	/* Check for errors in function */
	TYPE ret;
	int flow = 0;
	unsigned long n;
	POP_ulong(n, func_stack.opts);
	if (option(OPT_variable)) {
		if (n == number_errors) {
			flow = 1;
		}
		record_location--;
	}

	/* Check function body */
	if (!IS_NULL_exp(body)) {
		if (!unreached_code) {
			/* Check for falling out of function */
			EXP e = fall_return_stmt();
			body = add_compound_stmt(body, e);
		}
		unreached_code = 0;
		set_parent_stmt(body, NULL_exp);
		if (IS_exp_solve_stmt(body)) {
			/* Analyse enclosing solve statement */
			body = solve_labels(body);
		} else if (check_labels()) {
			/* Construct enclosing solve statement */
			EXP a;
			MAKE_exp_solve_stmt(type_void, body, a);
			CONS_exp(a, all_solve_stmts, all_solve_stmts);
			set_parent_stmt(body, a);
			body = solve_labels(a);
		}
		end_solve_stmts();
#if LANGUAGE_CPP
		if (!IS_NULL_list(all_try_blocks)) {
			/* Check all try blocks */
			end_try_blocks(id);
		}
#endif
		body = end_try_check(id, body);
		if (flow || (have_destructor && do_usage)) {
			/* Variable flow analysis */
			check_flow(id, body, flow);
		}
	}

	/* Define the function */
	if (IS_id_function_etc(id)) {
		COPY_exp(id_function_etc_defn(id), body);
		define_id(id);
		if (!in_template_decl) {
			compile_function(id, 0);
			free_nspace(label_namespace);
		}
		if (do_dump) {
			dump_undefine(id, &crt_loc, 0);
		}
	}

	/* Restore old function data */
	POP_id(crt_func_id, func_stack.id);
	POP_type(ret, func_stack.ret);
	POP_int(unreached_code, func_stack.unreached);
	POP_int(in_declaration, func_stack.declaration);
	POP_int(have_destructor, func_stack.destructor);
	POP_int(in_func_handler, func_stack.handler);
	POP_stack(crt_loop_stack, func_stack.loops);
	POP_nspace(label_namespace, func_stack.labels);
	POP_list(all_solve_stmts, func_stack.solves);
	POP_list(all_try_blocks, func_stack.tries);
	POP_ulong(n, func_stack.opts);
	crt_option_value(OPT_VAL_nested_class) = n;
	POP_ulong(n, func_stack.opts);
	crt_option_value(OPT_VAL_statement_depth) = n;
	crt_func_complex = pass_complex_type(ret);
	crt_func_return = ret;
	block_namespace = NULL_nspace;
	suppress_variable = 0;
	unreached_last = 0;
	return body;
}
