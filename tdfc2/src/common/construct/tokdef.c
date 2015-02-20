/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <limits.h>
#include <stdio.h>

#include <shared/check.h>

#include <utility/config.h>
#include "c_types.h"

#include <utility/error.h>
#include <utility/catalog.h>
#include <utility/option.h>

#include <syntax/syntax.h>

#include <parse/constant.h>
#include <parse/file.h>
#include <parse/hash.h>
#include <parse/lex.h>
#include <parse/macro.h>
#include <parse/parse.h>
#include <parse/predict.h>
#include <parse/preproc.h>

#include <construct/access.h>
#include <construct/basetype.h>
#include <construct/check.h>
#include <construct/chktype.h>
#include <construct/class.h>
#include <construct/convert.h>
#include <construct/derive.h>
#include <construct/exception.h>
#include <construct/expression.h>
#include <construct/function.h>
#include <construct/identifier.h>
#include <construct/initialise.h>
#include <construct/inttype.h>
#include <construct/member.h>
#include <construct/namespace.h>
#include <construct/overload.h>
#include <construct/redeclare.h>
#include <construct/statement.h>
#include <construct/template.h>
#include <construct/tokdef.h>
#include <construct/token.h>

#include <output/dump.h>

#include "ctype_ops.h"
#include "exp_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "member_ops.h"
#include "nat_ops.h"
#include "nspace_ops.h"
#include "off_ops.h"
#include "tok_ops.h"
#include "type_ops.h"


/*
    Tokens are defined by the equality routines if the flag force_tokdef
    is set.  This is only done if we are reasonably sure that the equality
    should hold.  Similarly template specialisation is only considered
    if force_template is true.
*/

int force_tokdef = 0;
int force_template = 0;
int expand_tokdef = 0;


/*
    This routine uses the values force_tokdef and force_template to
    determine whether the token id is available for token unification.
*/

int
defining_token(IDENTIFIER id)
{
	if (!IS_NULL_id(id) && IS_id_token(id)) {
		DECL_SPEC ds;
		if (force_tokdef) {
			return 1;
		}
		ds = DEREF_dspec(id_storage(id));
		if (ds & dspec_template) {
			return force_template;
		}
	}
	return 0;
}


/*
    This routine finds the result component of the token id.
*/

TOKEN
find_tokdef(IDENTIFIER id)
{
	TOKEN tok = NULL_tok;
	if (!IS_NULL_id(id) && IS_id_token(id)) {
		unsigned tag;
		tok = DEREF_tok(id_token_sort(id));
		tag = TAG_tok(tok);
		if (tag == tok_func_tag) {
			TOKEN ptok = DEREF_tok(tok_func_proc(tok));
			if (!IS_NULL_tok(ptok)) {
				tok = DEREF_tok(tok_proc_res(ptok));
			}
		} else if (tag == tok_proc_tag) {
			tok = DEREF_tok(tok_proc_res(tok));
		}
	}
	return tok;
}


/*
    These values are used to indicate that a token parameter has been
    redefined inconsistently.
*/

static NAT redef_nat = NULL_nat;
static EXP redef_exp = NULL_exp;
TYPE redef_type = NULL_type;
static IDENTIFIER redef_id = NULL_id;
static OFFSET redef_off = NULL_off;


/*
    This routine initialises the dummy token parameter values above.
    They are set to impossible values which could not arise naturally.
*/

void
init_token_args(void)
{
	HASHID nm = KEYWORD(lex_error);
	redef_id = DEREF_id(hashid_id(nm));
	MAKE_type_ref(cv_none, type_void, redef_type);
	MAKE_exp_value(redef_type, redef_exp);
	MAKE_nat_calc(redef_exp, redef_nat);
	MAKE_off_zero(redef_type, redef_off);
	return;
}


/*
    This routine defines the integer constant token id to be e.  It
    returns true if the token is assigned a value.
*/

int
define_nat_token(IDENTIFIER id, NAT n)
{
	if (!IS_NULL_nat(n)) {
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if (!(ds & dspec_pure)) {
			int ok = 1;
			TOKEN tok = find_tokdef(id);
			if (IS_NULL_tok(tok)) {
				return 0;
			}
			switch (TAG_tok(tok)) {
			case tok_nat_tag:
			case tok_snat_tag: {
				/* Integer constant tokens */
				NAT m = DEREF_nat(tok_nat_etc_value(tok));
				if (!IS_NULL_nat(m) && !eq_nat(n, m)) {
					if (ds & dspec_auto) {
						n = redef_nat;
					} else {
						PTR(LOCATION) loc = id_loc(id);
						report(crt_loc, ERR_token_redef(id, loc));
					}
					ok = 0;
				}
				COPY_nat(tok_nat_etc_value(tok), n);
				break;
			}
			case tok_exp_tag:
			case tok_stmt_tag: {
				/* Expression tokens */
				EXP e = calc_nat_value(n, type_sint);
				return define_exp_token(id, e, 1);
			}
			default:
				/* Other tokens */
				return 0;
			}

			if (!(ds & dspec_auto)) {
				no_token_defns++;
			}
			ds |= dspec_defn;
			COPY_dspec(id_storage(id), ds);
			COPY_loc(id_loc(id), crt_loc);
			return ok;
		}
	}
	return 0;
}


/*
    This routine defines the expression, statement or integer constant
    token id to be e.  It returns true if the token is assigned a value.
    expl is false for an enforcing external declaration, such as that
    arising from unify_id.
*/

int
define_exp_token(IDENTIFIER id, EXP e, int expl)
{
    if (!IS_NULL_exp(e)) {
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	if (!(ds & dspec_pure)) {
	    int ok = 1;
	    unsigned tt;
	    TOKEN tok = find_tokdef(id);
	    if (IS_NULL_tok(tok)) {
		    return 0;
	    }
	    tt = TAG_tok(tok);
	    switch (tt) {
		case tok_exp_tag: {
		    /* Expression tokens */
		    TYPE s;
		    ERROR err = NULL_err;
		    unsigned etag = TAG_exp(e);
		    EXP d = DEREF_exp(tok_exp_value(tok));
		    int c = DEREF_int(tok_exp_constant(tok));
		    TYPE t = DEREF_type(tok_exp_type(tok));
		    CV_SPEC cv = DEREF_cv(type_qual(t));
		    LIST(IDENTIFIER) pids = NULL_list(IDENTIFIER);
		    force_tokdef++;
		    e = convert_reference(e, REF_ASSIGN);
		    e = resolve_cast(t, e, &err, 1, 0, pids);
		    s = DEREF_type(exp_type(e));
		    if (cv & cv_lvalue) {
			/* lvalue tokens */
			cv = DEREF_cv(type_qual(s));
			if (cv & cv_lvalue) {
			    if (eq_type(s, t)) {
				if (!IS_exp_address(e)) {
				    MAKE_exp_address(t, e, e);
				}
			    } else {
				EXP a = init_ref_lvalue(t, e, &err);
				if (IS_NULL_exp(a)) {
				    err = ERR_basic_link_incompat(t, s);
				} else {
				    e = make_ref_init(t, a);
				}
			    }
			} else {
			    report(crt_loc, ERR_token_arg_lvalue(id));
			}
		    } else {
			/* rvalue tokens */
			if (IS_exp_aggregate(e)) {
			    /* Aggregate initialiser */
			    e = init_aggregate(t, e, id, &err);
			} else {
			    switch (TAG_type(t)) {
				case type_top_tag:
				case type_bottom_tag:
				    /* Void expressions */
				    e = convert_lvalue(e);
				    e = convert_none(e);
				    e = make_discard_exp(e);
				    if (!IS_type_top_etc(s)) {
					EXP a = make_null_exp(t);
					e = join_exp(e, a);
				    }
				    break;
				case type_ref_tag:
				    /* Reference initialiser */
				    e = init_assign(t, cv_none, e, &err);
				    break;
				case type_array_tag:
				    /* Array initialiser */
				    if (etag == exp_paren_tag) {
					e = make_paren_exp(e);
				    }
				    e = init_array(t, cv_none, e, 1, &err);
				    break;
				case type_error_tag:
				    e = convert_none(e);
				    break;
				default:
				    /* Simple initialiser */
				    e = convert_lvalue(e);
				    e = init_assign(t, cv_none, e, &err);
				    break;
			    }
			}
		    }
		    force_tokdef--;
		    if (!IS_NULL_err(err)) {
			/* Conversion error */
			err = init_error(err, 0);
			err = concat_error(err, ERR_token_arg_exp(id));
			report(crt_loc, err);
		    }
		    if (c == 1 && !is_const_exp(e, 1)) {
			report(crt_loc, ERR_token_arg_const(id));
		    }
		    if (!IS_NULL_exp(d) && !eq_exp(e, d, 0)) {
			int redef = 0;
			if (ds & dspec_auto) {
			    e = redef_exp;
			} else {
			    if (expl) {
				if (ds & dspec_main) {
				    redef = 1;
				} else {
				    ds |= dspec_main;
				}
			    } else {
				if (ds & dspec_main) {
				    e = d;
				} else {
				    redef = 1;
				}
			    }
			}
			if (redef) {
			    PTR(LOCATION) loc = id_loc(id);
			    report(crt_loc, ERR_token_redef(id, loc));
			    ok = 0;
			}
		    } else {
			if (expl && !(ds & dspec_auto)) {
			    /* Mark explicit definitions */
			    ds |= dspec_main;
			}
		    }
		    COPY_exp(tok_exp_value(tok), e);
		    break;
		}

		case tok_nat_tag:
		case tok_snat_tag: {
		    /* Constant tokens */
		    NAT n;
		    ERROR err = NULL_err;
		    e = convert_reference(e, REF_NORMAL);
		    e = convert_lvalue(e);
		    n = make_nat_exp(e, &err);
		    if (!IS_NULL_err(err)) {
			/* Not a constant expression */
			err = concat_error(err, ERR_token_arg_nat(id));
			report(crt_loc, err);
		    } else {
			if (tt == tok_nat_tag && is_negative_nat(n)) {
			    /* Negative constant */
			    report(crt_loc, ERR_token_arg_nat(id));
			    n = negate_nat(n);
			}
		    }
		    return define_nat_token(id, n);
		}

		case tok_stmt_tag: {
		    /* Statement tokens */
		    EXP d = DEREF_exp(tok_stmt_value(tok));
		    if (!IS_NULL_exp(d) && !eq_exp(e, d, 0)) {
			if (ds & dspec_auto) {
			    e = redef_exp;
			} else {
			    PTR(LOCATION) loc = id_loc(id);
			    report(crt_loc, ERR_token_redef(id, loc));
			}
			ok = 0;
		    }
		    COPY_exp(tok_stmt_value(tok), e);
		    break;
		}

		default:
		    /* Other tokens */
		    return 0;
	    }
	    if (!(ds & dspec_auto)) {
		    no_token_defns++;
	    }
	    ds |= dspec_defn;
	    COPY_dspec(id_storage(id), ds);
	    COPY_loc(id_loc(id), crt_loc);
	    return ok;
	}
    }
    return 0;
}


/*
    This routine is called when a tokenised structure or union id is defined
    by the compound type t.  It checks for any tokenised members of id
    which may also be defined as a result of this identification.  This
    should really be done by the class merging routines.
*/

static void
define_field_tokens(IDENTIFIER id, TYPE t)
{
    IDENTIFIER tid = DEREF_id(id_token_alt(id));
    unsigned tag = TAG_id(tid);
    if (tag == id_class_name_tag || tag == id_class_alias_tag) {
	TYPE s = DEREF_type(id_class_name_etc_defn(tid));
	if (IS_type_compound(s) && IS_type_compound(t)) {
	    MEMBER mem;
	    CLASS_TYPE cs = DEREF_ctype(type_compound_defn(s));
	    CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
	    NAMESPACE ns = DEREF_nspace(ctype_member(cs));
	    NAMESPACE nt = DEREF_nspace(ctype_member(ct));

	    /* Check that keys match for type aliases */
	    if (tag == id_class_alias_tag) {
		BASE_TYPE bs = find_class_key(cs);
		BASE_TYPE bt = find_class_key(ct);
		if (!equal_key(bs, bt)) {
		    PTR(LOCATION) loc = id_loc(id);
		    ERROR err = ERR_dcl_type_elab_bad(bt, bs, id, loc);
		    report(crt_loc, err);
		}
	    }

	    /* Scan through members of ns */
	    mem = DEREF_member(nspace_ctype_first(ns));
	    while (!IS_NULL_member(mem)) {
		IDENTIFIER mid = DEREF_id(member_id(mem));
		if (!IS_NULL_id(mid) && IS_id_member(mid)) {
		    DECL_SPEC ds = DEREF_dspec(id_storage(mid));
		    if (ds & dspec_token) {
			/* Tokenised member found */
			HASHID nm = DEREF_hashid(id_name(mid));
			IDENTIFIER nid = search_field(nt, nm, 0, 0);
			if (!IS_NULL_id(nid)) {
			    /* Token definition found */
			    IDENTIFIER tok = find_token(mid);
			    ds = DEREF_dspec(id_storage(tok));
			    if (ds & dspec_pure) {
				LOCATION loc;
				DEREF_loc(id_loc(nid), loc);
				report(loc, ERR_token_def_not(nid));
			    } else {
				OFFSET off;
				TYPE r = NULL_type;
				off = offset_member(t, nid, &r, nt, 0);
				IGNORE define_mem_token(tok, off, r, 1);
			    }
			} else {
			    /* Copy tokenised member */
			    MEMBER mem2 = search_member(nt, nm, 1);
			    mid = copy_id(mid, 0);
			    COPY_nspace(id_parent(mid), nt);
			    set_member(mem2, mid);
			}
		    }
		}
		mem = DEREF_member(member_next(mem));
	    }

	    /* Scan through members of nt */
	    mem = DEREF_member(nspace_ctype_first(nt));
	    while (!IS_NULL_member(mem)) {
		MEMBER mem2 = NULL_member;
		IDENTIFIER mid = DEREF_id(member_id(mem));
		IDENTIFIER nid = DEREF_id(member_alt(mem));
		if (!IS_NULL_id(mid)) {
		    IDENTIFIER pid;
		    HASHID nm = DEREF_hashid(id_name(mid));
		    mem2 = search_member(ns, nm, 1);
		    mid = copy_id(mid, 0);
		    COPY_nspace(id_parent(mid), ns);
		    pid = DEREF_id(member_id(mem2));
		    if (IS_NULL_id(pid)) {
			set_member(mem2, mid);
		    }
		}
		if (!IS_NULL_id(nid) && !EQ_id(mid, nid)) {
		    if (IS_NULL_member(mem2)) {
			HASHID nm = DEREF_hashid(id_name(nid));
			mem2 = search_member(ns, nm, 1);
		    }
		    nid = copy_id(nid, 0);
		    COPY_nspace(id_parent(nid), ns);
		    if (!IS_NULL_id(nid)) {
			set_type_member(mem2, mid);
		    }
		}
		mem = DEREF_member(member_next(mem));
	    }
	}
    }
    return;
}


/*
    This routine checks whether the type t of category ca can be used to
    define a token of kind bt.
*/

static int
match_type_token(BASE_TYPE bt, unsigned ca, TYPE t)
{
	int ok = 1;
	if (bt & btype_star) {
		/* Scalar types */
		if (!IS_TYPE_SCALAR(ca)) {
			ok = 0;
		}
	} else if (bt & btype_float) {
		/* Arithmetic types */
		if (bt & btype_int) {
			if (!IS_TYPE_ARITH(ca)) {
				ok = 0;
			}
		} else {
			if (!IS_TYPE_FLOAT(ca)) {
				ok = 0;
			}
		}
	} else if (bt & btype_int) {
		/* Integral types */
		if (IS_TYPE_INT(ca)) {
			if (bt & btype_signed) {
				if (check_int_type(t, btype_unsigned)) {
					ok = 0;
				}
			} else if (bt & btype_unsigned) {
				if (check_int_type(t, btype_signed)) {
					ok = 0;
				}
			}
		} else {
			ok = 0;
		}
	}
	return ok;
}


/*
    This routine defines the type token id to be t.  It returns true if
    the token is assigned a value.  qual is as in check_compatible.
*/

int
define_type_token(IDENTIFIER id, TYPE t, int qual)
{
    if (!IS_NULL_type(t)) {
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	if (!(ds & dspec_pure)) {
	    TYPE s;
	    int ok = 1;
	    int check_promote = 0;
	    TOKEN tok = find_tokdef(id);
	    if (IS_NULL_tok(tok) || !IS_tok_type(tok)) {
		    return 0;
	    }
	    s = DEREF_type(tok_type_value(tok));
	    if (!IS_NULL_type(s)) {
		ERROR err = NULL_err;
		t = check_compatible(s, t, qual, &err, 1);
		if (!IS_NULL_err(err)) {
		    if (ds & dspec_auto) {
			destroy_error(err, 1);
			t = redef_type;
		    } else {
			ERROR err2;
			err2 = ERR_token_redef(id, id_loc(id));
			err = concat_error(err, err2);
			report(crt_loc, err);
		    }
		    ok = 0;
		}
	    } else {
		unsigned ca = type_category(&t);
		BASE_TYPE bt = DEREF_btype(tok_type_kind(tok));
		if (!(bt & btype_template)) {
		    /* Tokens */
		    ERROR err = NULL_err;
		    switch (TAG_type(t)) {
			case type_ref_tag:
			case type_func_tag:
			case type_bitfield_tag:
			    /* These types can't be tokenised */
			    ok = 0;
			    break;
			case type_compound_tag:
			    /* Can only tokenise trivial classes */
			    if (bt != btype_none || !(ds & dspec_auto)) {
				CLASS_TYPE ct;
				ct = DEREF_ctype(type_compound_defn(t));
				err = check_trivial_class(ct);
				if (!IS_NULL_err(err))ok = 0;
			    }
			    break;
		    }
		    if (bt) {
			if (bt & btype_named) {
			    /* Structure and union types */
			    if (IS_type_compound(t)) {
				if (!(ds & dspec_auto)) {
				    /* Check structure fields */
				    define_field_tokens(id, t);
				}
			    } else {
				ok = 0;
			    }
			} else {
			    /* Check scalar types */
			    if (!match_type_token(bt, ca, t)) {
				    ok = 0;
			    }
			}
			if (bt & btype_int) {
				check_promote = ok;
			}
		    }
		    if (!ok) {
			/* Report any type mismatch errors */
			if (!IS_type_error(t)) {
			    int lex = type_token_key(bt);
			    ERROR err2 = ERR_token_arg_type(lex, id, t);
			    err = concat_error(err, err2);
			    report(crt_loc, err);
			    t = type_error;
			}
		    }
		}
		if (!IS_TYPE_INT(ca)) {
			check_promote = 0;
		}
	    }
	    COPY_type(tok_type_value(tok), t);
	    if (ds & dspec_auto) {
		check_promote = 0;
	    } else {
		no_token_defns++;
	    }
	    ds |= dspec_defn;
	    COPY_dspec(id_storage(id), ds);
	    COPY_loc(id_loc(id), crt_loc);
	    if (check_promote) {
		/* Check that promoted types are compatible */
		s = apply_itype_token(id, NULL_list(TOKEN));
		t = promote_type(t);
		set_promote_type(s, t, ntype_none);
	    }
	    return ok;
	}
    }
    return 0;
}


/*
    This routine defines the template template parameter id to be the
    class given by tid.  It returns true if the parameter is assigned a
    value.
*/

int
define_templ_token(IDENTIFIER id, IDENTIFIER tid)
{
    if (!IS_NULL_id(tid)) {
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	if (!(ds & dspec_pure)) {
	    TOKEN tok = DEREF_tok(id_token_sort(id));
	    if (IS_tok_class(tok)) {
		int ok = 0;
		IDENTIFIER sid = DEREF_id(tok_class_value(tok));
		if (EQ_id(sid, tid)) {
			return 1;
		}
		if (IS_id_class_name_etc(tid)) {
		    TYPE t = DEREF_type(tok_class_type(tok));
		    TYPE s = DEREF_type(id_class_name_etc_defn(tid));
		    if (IS_type_templ(t) && IS_type_templ(s)) {
			/* Check for equality of template parameters */
			LIST(IDENTIFIER) ps, pt;
			TOKEN as = DEREF_tok(type_templ_sort(s));
			TOKEN at = DEREF_tok(type_templ_sort(t));
			ps = DEREF_list(tok_templ_pids(as));
			pt = DEREF_list(tok_templ_pids(at));
			ok = eq_templ_params(ps, pt);
			restore_templ_params(ps);
		    }
		    if (!ok) {
			/* Report illegal definitions */
			ERROR err = ERR_temp_arg_templ_bad(id, s);
			report(crt_loc, err);
		    }
		    if (!IS_NULL_id(sid)) {
			/* Check for redefinitions */
			if (ds & dspec_auto) {
			    tid = redef_id;
			} else {
			    PTR(LOCATION) loc = id_loc(id);
			    report(crt_loc, ERR_token_redef(id, loc));
			}
			ok = 0;
		    }
		} else {
		    ok = 0;
		}
		COPY_id(tok_class_value(tok), tid);
		if (!(ds & dspec_auto)) {
			no_token_defns++;
		}
		ds |= dspec_defn;
		COPY_dspec(id_storage(id), ds);
		COPY_loc(id_loc(id), crt_loc);
		return ok;
	    }
	}
    }
    return 0;
}


/*
    This routine defines the member token id to be a member of offset off
    and type t.  It returns true if the token is assigned a value.  ext is
    true for an external token definition.
*/

int
define_mem_token(IDENTIFIER id, OFFSET off, TYPE t, int ext)
{
    if (!IS_NULL_off(off)) {
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	if ((ds & dspec_auto) && ext) {
	    ERROR err = ERR_class_mem_redecl(id, id_loc(id));
	    report(crt_loc, err);
	} else if (!(ds & dspec_pure)) {
	    TOKEN tok = find_tokdef(id);
	    if (!IS_NULL_tok(tok) && IS_tok_member(tok)) {
		TYPE u;
		ERROR err = NULL_err;
		TYPE s = DEREF_type(tok_member_type(tok));
		OFFSET d = DEREF_off(tok_member_value(tok));
		if (!IS_NULL_off(d) && !eq_offset(off, d, 0)) {
		    if (ds & dspec_auto) {
			off = redef_off;
		    } else {
			PTR(LOCATION) loc = id_loc(id);
			report(crt_loc, ERR_token_redef(id, loc));
		    }
		}
		u = check_compatible(s, t, 0, &err, 0);
		if (!IS_NULL_err(err)) {
		    /* Member type is wrong */
		    if (eq_type_offset(s, t)) {
			/* Types have same representation */
			err = set_severity(err, OPT_member_incompat, -1);
		    }
		    err = concat_error(err, ERR_token_arg_mem(id));
		    report(crt_loc, err);
		}
		COPY_off(tok_member_value(tok), off);
		if (!(ds & dspec_auto)) {
		    if (IS_type_error(s)) {
			/* Fill in type if not known */
			IDENTIFIER mid = DEREF_id(id_token_alt(id));
			COPY_type(tok_member_type(tok), u);
			u = lvalue_type(u);
			COPY_type(id_member_type(mid), u);
		    }
		    no_token_defns++;
		}
		ds |= dspec_defn;
		COPY_dspec(id_storage(id), ds);
		COPY_loc(id_loc(id), crt_loc);
		UNUSED(ext);
		return 1;
	    }
	}
    }
    return 0;
}


/*
    This routine defines the function token id to be the function fid.
*/

int
define_func_token(IDENTIFIER id, IDENTIFIER fid)
{
    if (!IS_NULL_id(fid)) {
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	if (!(ds & dspec_pure)) {
	    TOKEN tok = DEREF_tok(id_token_sort(id));
	    if (IS_tok_func(tok)) {
		int eq = 0;
		int redef = 0;
		LIST(IDENTIFIER) pids = NULL_list(IDENTIFIER);
		TYPE t = DEREF_type(tok_func_type(tok));
		TOKEN res = DEREF_tok(tok_func_proc(tok));
		IDENTIFIER pid = DEREF_id(tok_func_defn(tok));
		IDENTIFIER qid = resolve_func(fid, t, 1, 0, pids, &eq);
		if (!IS_NULL_id(qid)) {
		    switch (TAG_id(qid)) {
			case id_function_tag:
			case id_stat_mem_func_tag:
			    use_id(qid, 0);
			    break;
			default:
			    qid = NULL_id;
			    break;
		    }
		}
		if (IS_NULL_id(qid)) {
		    report(crt_loc, ERR_token_def_func(fid, t));
		    qid = fid;
		} else {
		    TYPE s = DEREF_type(id_function_etc_type(qid));
		    if (eq == 2) {
			report(crt_loc, ERR_dcl_link_conv());
		    }
		    if (eq_except(s, t)!= 2) {
			report(crt_loc, ERR_token_def_except());
		    }
		}
		if (!IS_NULL_tok(res)) {
		    /* Previously defined by macro */
		    redef = 1;
		}
		if (!IS_NULL_id(pid) && !EQ_id(pid, qid)) {
		    /* Previously defined by different function */
		    redef = 1;
		}
		if (redef) {
		    PTR(LOCATION) loc = id_loc(id);
		    report(crt_loc, ERR_token_redef(id, loc));
		}
		COPY_id(tok_func_defn(tok), qid);
		if (!(ds & dspec_auto)) {
			no_token_defns++;
		}
		ds |= dspec_defn;
		COPY_dspec(id_storage(id), ds);
		COPY_loc(id_loc(id), crt_loc);
		return 1;
	    }
	}
    }
    return 0;
}


/*
    This variable is used to keep track of the depth of procedure token
    arguments being read.
*/

int in_proc_token = 0;


/*
    If id represents a member token then this routine returns the type
    of which id is a member, suitably expanded.  Otherwise the null type
    is returned.  This represents the only barrier to doing argument
    deduction in procedure tokens independently for each argument - if
    a member parameter is a member of a previous structure parameter
    (as in offsetof), we need to know the value of the structure
    argument before we can decode the member argument.
*/

static TYPE
expand_member_type(IDENTIFIER id)
{
	TYPE t = NULL_type;
	TOKEN tok = find_tokdef(id);
	if (!IS_NULL_tok(tok) && IS_tok_member(tok)) {
		t = DEREF_type(tok_member_of(tok));
		t = expand_type(t, 1);
	}
	return t;
}


/*
    This routine reads the definition of the token id.  It returns true
    if a value is assigned to the token.  If mt is not null it is the
    class type for a member token.  fn is true for procedure tokens and
    mac is true is true for macro token definitions.
*/

static int
parse_token(IDENTIFIER id, TYPE t, int fn, int mac, LIST(IDENTIFIER) pids)
{
	int def;
	TOKEN tok = NULL_tok;
	unsigned tag = null_tag;
	if (IS_id_token(id)) {
		/* Find token sort */
		tok = DEREF_tok(id_token_sort(id));
		if (fn) {
			tok = find_tokdef(id);
		}
		tag = TAG_tok(tok);
	}
	switch (tag) {
	case tok_exp_tag:
	case tok_nat_tag:
	case tok_snat_tag: {
		/* Expression tokens */
		EXP e = NULL_exp;
		ERROR err = NULL_err;
		int tn = crt_lex_token;
		if (mac && tn == lex_newline && tag == tok_exp_tag) {
			/* Map empty definition to default value */
			TYPE s = DEREF_type(tok_exp_type(tok));
			e = init_empty(s, cv_none, 1, &err);
		} else if (mac && tn == lex_open_Hbrace_H1) {
			parse_init(id, &e);
		} else {
			parse_exp(&e);
		}
		if (!IS_NULL_exp(e) && tag == tok_exp_tag) {
			/* Deal with overloaded functions */
			TYPE s = DEREF_type(tok_exp_type(tok));
			force_tokdef++;
			e = resolve_cast(s, e, &err, 1, 0, pids);
			if (!IS_NULL_err(err)) {
				err = concat_error(err, ERR_token_arg_exp(id));
				report(crt_loc, err);
			}
			force_tokdef--;
		}
		def = define_exp_token(id, e, 1);
		break;
	}
	case tok_stmt_tag: {
		/* Statement tokens */
		EXP e;
		EXP a = NULL_exp;
		int ic = in_class_defn;
		int fd = in_function_defn;
		int uc = unreached_code;
		TYPE r = crt_func_return;
		NAMESPACE bns = block_namespace;
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		IDENTIFIER fid = DEREF_id(id_token_alt(id));
		unreached_code = 0;
		if (fd) {
			if (!(ds & dspec_auto)) {
				/* Force return errors */
				crt_func_return = NULL_type;
			}
		} else {
			/* Treat as dummy function definition */
			in_class_defn = 0;
			in_function_defn = fd + 1;
			really_in_function_defn++;
			begin_function(fid);
			crt_func_return = NULL_type;
		}
		block_namespace = NULL_nspace;
		e = begin_compound_stmt(1);
		parse_stmt(&a);
		e = add_compound_stmt(e, a);
		e = end_compound_stmt(e);
		if (fd) {
			if (ds & dspec_auto) {
				/* Set dummy parent statement */
				MAKE_exp_token(type_void, id,
					       NULL_list(TOKEN), a);
				set_parent_stmt(e, a);
			}
		} else {
			/* End dummy function definition */
			if (crt_access_list.pending) {
				IGNORE report_access(fid);
			}
			e = end_function(fid, e);
			really_in_function_defn--;
			in_function_defn = fd;
			in_class_defn = ic;
		}
		unreached_code = uc;
		block_namespace = bns;
		crt_func_return = r;
		def = define_exp_token(id, e, 1);
		break;
	}
	case tok_member_tag: {
		/* Member tokens */
		TYPE s = type_error;
		OFFSET off = NULL_off;
		if (IS_NULL_type(t)) {
			t = expand_member_type(id);
		}
		parse_offset(NULL_off, t, &off, &s);
		def = define_mem_token(id, off, s, 0);
		break;
	}
	case tok_func_tag: {
		/* Function tokens */
		IDENTIFIER fid = NULL_id;
		parse_id(&fid);
		def = define_func_token(id, fid);
		break;
	}
	default: {
		/* Type tokens */
		TYPE s = NULL_type;
		have_type_specifier = 0;
		parse_type(&s);
		if (tag == tok_type_tag) {
			/* Simple type token */
			def = define_type_token(id, s, 0);
		} else {
			/* Complex type value */
			TYPE r = DEREF_type(id_class_name_etc_defn(id));
			force_tokdef++;
			def = eq_type(r, s);
			if (!def && !IS_NULL_type(s)) {
				ERROR err =
				    ERR_token_arg_type(lex_type_Hcap, id, s);
				report(crt_loc, err);
			}
			force_tokdef--;
		}
		break;
	}
	}
	return def;
}


/*
    This routine sets the value of the token id to be arg.
*/

void
assign_token(IDENTIFIER id, TOKEN arg)
{
	if (!IS_NULL_tok(arg)) {
		TOKEN sort = DEREF_tok(id_token_sort(id));
		unsigned na = TAG_tok(arg);
		unsigned nb = TAG_tok(sort);
		if (nb == tok_proc_tag) {
			sort = DEREF_tok(tok_proc_res(sort));
			nb = TAG_tok(sort);
		}
		if (na == nb) {
			switch (na) {
			case tok_exp_tag: {
				EXP e = DEREF_exp(tok_exp_value(arg));
				COPY_exp(tok_exp_value(sort), e);
				break;
			}
			case tok_nat_tag:
			case tok_snat_tag: {
				NAT n = DEREF_nat(tok_nat_etc_value(arg));
				COPY_nat(tok_nat_etc_value(sort), n);
				break;
			}
			case tok_stmt_tag: {
				EXP e = DEREF_exp(tok_stmt_value(arg));
				COPY_exp(tok_stmt_value(sort), e);
				break;
			}
			case tok_member_tag: {
				OFFSET off = DEREF_off(tok_member_value(arg));
				COPY_off(tok_member_value(sort), off);
				break;
			}
			case tok_type_tag: {
				TYPE t = DEREF_type(tok_type_value(arg));
				COPY_type(tok_type_value(sort), t);
				break;
			}
			case tok_class_tag: {
				IDENTIFIER cid = DEREF_id(tok_class_value(arg));
				COPY_id(tok_class_value(sort), cid);
				break;
			}
			}
		}
	}
	return;
}


/*
    These stacks are used to store the values of the token arguments to
    allow for recursive token applications.
*/

static STACK(EXP) token_exp_stack = NULL_stack(EXP);
static STACK(NAT) token_nat_stack = NULL_stack(NAT);
static STACK(EXP) token_stmt_stack = NULL_stack(EXP);
static STACK(OFFSET) token_mem_stack = NULL_stack(OFFSET);
static STACK(TYPE) token_type_stack = NULL_stack(TYPE);
static STACK(IDENTIFIER) token_class_stack = NULL_stack(IDENTIFIER);


/*
    This routine saves the argument values for the token parameters pids
    by pushing them onto the stacks above.  The argument values set to those
    stored in args, or the null value when these are exhausted.  The routine
    also clears the pure field of the token, returning 0 if they were
    previously set.
*/

int
save_token_args(LIST(IDENTIFIER) pids, LIST(TOKEN) args)
{
	int depth = 1;
	LIST(IDENTIFIER) bids = pids;
	while (!IS_NULL_list(bids)) {
		IDENTIFIER bid = DEREF_id(HEAD_list(bids));

		/* Get argument token value */
		TOKEN atok = NULL_tok;
		unsigned at = null_tag;
		if (!IS_NULL_list(args)) {
			atok = DEREF_tok(HEAD_list(args));
			if (!IS_NULL_tok(atok)) {
				at = TAG_tok(atok);
			}
			args = TAIL_list(args);
		}

		/* Save previous token value */
		if (!IS_NULL_id(bid) && IS_id_token(bid)) {
			DECL_SPEC ds;
			TOKEN btok = DEREF_tok(id_token_sort(bid));
			unsigned bt = TAG_tok(btok);
			switch (bt) {
			case tok_exp_tag: {
				EXP e = DEREF_exp(tok_exp_value(btok));
				PUSH_exp(e, token_exp_stack);
				if (at == bt) {
					e = DEREF_exp(tok_exp_value(atok));
				} else {
					e = NULL_exp;
				}
				COPY_exp(tok_exp_value(btok), e);
				break;
			}
			case tok_nat_tag:
			case tok_snat_tag: {
				NAT n = DEREF_nat(tok_nat_etc_value(btok));
				PUSH_nat(n, token_nat_stack);
				if (at == bt) {
					n = DEREF_nat(tok_nat_etc_value(atok));
				} else {
					n = NULL_nat;
				}
				COPY_nat(tok_nat_etc_value(btok), n);
				break;
			}
			case tok_stmt_tag: {
				EXP e = DEREF_exp(tok_stmt_value(btok));
				PUSH_exp(e, token_stmt_stack);
				if (at == bt) {
					e = DEREF_exp(tok_stmt_value(atok));
				} else {
					e = NULL_exp;
				}
				COPY_exp(tok_stmt_value(btok), e);
				break;
			}
			case tok_member_tag: {
				OFFSET off = DEREF_off(tok_member_value(btok));
				PUSH_off(off, token_mem_stack);
				if (at == bt) {
					off = DEREF_off(tok_member_value(atok));
				} else {
					off = NULL_off;
				}
				COPY_off(tok_member_value(btok), off);
				break;
			}
			case tok_type_tag: {
				TYPE t = DEREF_type(tok_type_value(btok));
				PUSH_type(t, token_type_stack);
				if (at == bt) {
					t = DEREF_type(tok_type_value(atok));
				} else {
					t = NULL_type;
				}
				COPY_type(tok_type_value(btok), t);
				break;
			}
			case tok_class_tag: {
				IDENTIFIER cid = DEREF_id(tok_class_value(btok));
				PUSH_id(cid, token_class_stack);
				if (at == bt) {
					cid = DEREF_id(tok_class_value(atok));
				} else {
					cid = NULL_id;
				}
				COPY_id(tok_class_value(btok), cid);
				break;
			}
			default:
				/* Procedure arguments not allowed */
				break;
			}

			/* Allow definition of parameter */
			ds = DEREF_dspec(id_storage(bid));
			if (ds & dspec_pure) {
				ds &= ~dspec_pure;
				COPY_dspec(id_storage(bid), ds);
				depth = 0;
			}
		}
		bids = TAIL_list(bids);
	}
	in_proc_token++;
	return depth;
}


/*
    This routine restores the argument values for the token parameters
    pids by popping them from the stacks above.  The pure field of the
    tokens is set if depth is 0.
*/

void
restore_token_args(LIST(IDENTIFIER) pids, int depth)
{
	LIST(IDENTIFIER) bids = pids;
	if (!IS_NULL_list(bids)) {
		IDENTIFIER bid = DEREF_id(HEAD_list(bids));
		bids = TAIL_list(bids);
		if (!IS_NULL_list(bids)) {
			restore_token_args(bids, depth);
			in_proc_token++;
		}
		if (!IS_NULL_id(bid) && IS_id_token(bid)) {
			TOKEN btok = DEREF_tok(id_token_sort(bid));
			unsigned bt = TAG_tok(btok);
			switch (bt) {
			case tok_exp_tag: {
				EXP e;
				POP_exp(e, token_exp_stack);
				COPY_exp(tok_exp_value(btok), e);
				break;
			}
			case tok_nat_tag:
			case tok_snat_tag: {
				NAT n;
				POP_nat(n, token_nat_stack);
				COPY_nat(tok_nat_etc_value(btok), n);
				break;
			}
			case tok_stmt_tag: {
				EXP e;
				POP_exp(e, token_stmt_stack);
				COPY_exp(tok_stmt_value(btok), e);
				break;
			}
			case tok_member_tag: {
				OFFSET off;
				POP_off(off, token_mem_stack);
				COPY_off(tok_member_value(btok), off);
				break;
			}
			case tok_type_tag: {
				TYPE t;
				POP_type(t, token_type_stack);
				COPY_type(tok_type_value(btok), t);
				break;
			}
			case tok_class_tag: {
				IDENTIFIER cid;
				POP_id(cid, token_class_stack);
				COPY_id(tok_class_value(btok), cid);
				break;
			}
			default:
				/* Procedure arguments not allowed */
				break;
			}
			if (depth == 0) {
				/* Can't define parameter at outer level */
				DECL_SPEC ds = DEREF_dspec(id_storage(bid));
				ds |= dspec_pure;
				COPY_dspec(id_storage(bid), ds);
			}
		}
	}
	in_proc_token--;
	return;
}


/*
    This routine merges the argument values for the token parameters
    pids with the values popped off the stacks above.  It returns true
    if the merge was successful.  The pure field of the tokens is set
    if depth is 0.
*/

int
merge_token_args(LIST(IDENTIFIER) pids, int depth, int qual)
{
	int ok = 1;
	LIST(IDENTIFIER) bids = pids;
	if (!IS_NULL_list(bids)) {
		IDENTIFIER bid = DEREF_id(HEAD_list(bids));
		bids = TAIL_list(bids);
		if (!IS_NULL_list(bids)) {
			ok = merge_token_args(bids, depth, qual);
			in_proc_token++;
		}
		if (!IS_NULL_id(bid) && IS_id_token(bid)) {
			TOKEN btok = DEREF_tok(id_token_sort(bid));
			unsigned bt = TAG_tok(btok);
			switch (bt) {
			case tok_exp_tag: {
				EXP e;
				POP_exp(e, token_exp_stack);
				if (!IS_NULL_exp(e)) {
					if (!define_exp_token(bid, e, 1)) {
						ok = 0;
					}
				}
				break;
			}
			case tok_nat_tag:
			case tok_snat_tag: {
				NAT n;
				POP_nat(n, token_nat_stack);
				if (!IS_NULL_nat(n)) {
					if (!define_nat_token(bid, n)) {
						ok = 0;
					}
				}
				break;
			}
			case tok_stmt_tag: {
				EXP e;
				POP_exp(e, token_stmt_stack);
				if (!IS_NULL_exp(e)) {
					if (!define_exp_token(bid, e, 1)) {
						ok = 0;
					}
				}
				break;
			}
			case tok_member_tag: {
				OFFSET off;
				POP_off(off, token_mem_stack);
				if (!IS_NULL_off(off)) {
					TYPE t =
					    DEREF_type(tok_member_type(btok));
					if (!define_mem_token(bid, off, t, 0)) {
						ok = 0;
					}
				}
				break;
			}
			case tok_type_tag: {
				TYPE t;
				POP_type(t, token_type_stack);
				if (!IS_NULL_type(t)) {
					if (!define_type_token(bid, t, qual)) {
						ok = 0;
					}
				}
				break;
			}
			case tok_class_tag: {
				IDENTIFIER cid;
				POP_id(cid, token_class_stack);
				if (!IS_NULL_id(cid)) {
					if (!define_templ_token(bid, cid)) {
						ok = 0;
					}
				}
				break;
			}
			default:
				/* Procedure arguments not allowed */
				break;
			}
			if (depth == 0) {
				/* Can't define parameter at outer level */
				DECL_SPEC ds = DEREF_dspec(id_storage(bid));
				ds |= dspec_pure;
				COPY_dspec(id_storage(bid), ds);
			}
		}
	}
	in_proc_token--;
	return ok;
}


/*
    This routine checks whether a value has been bound to the token tok.
    If def is true then a dummy value is constructed for unbound values.
*/

int
is_bound_tok(TOKEN tok, int def)
{
	int bound = 1;
	if (!IS_NULL_tok(tok)) {
		switch (TAG_tok(tok)) {
		case tok_exp_tag: {
			/* Expression tokens */
			EXP e = DEREF_exp(tok_exp_value(tok));
			if (IS_NULL_exp(e) || EQ_exp(e, redef_exp)) {
				if (def) {
					TYPE t = DEREF_type(tok_exp_type(tok));
					MAKE_exp_value(t, e);
					COPY_exp(tok_exp_value(tok), e);
				}
				bound = 0;
			}
			break;
		}
		case tok_nat_tag:
		case tok_snat_tag: {
			/* Integer constant tokens */
			NAT n = DEREF_nat(tok_nat_etc_value(tok));
			if (IS_NULL_nat(n) || EQ_nat(n, redef_nat)) {
				if (def) {
					n = small_nat[1];
					COPY_nat(tok_nat_etc_value(tok), n);
				}
				bound = 0;
			}
			break;
		}
		case tok_stmt_tag: {
			/* Statement tokens */
			EXP e = DEREF_exp(tok_stmt_value(tok));
			if (IS_NULL_exp(e) || EQ_exp(e, redef_exp)) {
				if (def) {
					MAKE_exp_value(type_void, e);
					COPY_exp(tok_stmt_value(tok), e);
				}
				bound = 0;
			}
			break;
		}
		case tok_member_tag: {
			/* Member tokens */
			OFFSET off = DEREF_off(tok_member_value(tok));
			if (IS_NULL_off(off) || EQ_off(off, redef_off)) {
				if (def) {
					TYPE t =
					    DEREF_type(tok_member_type(tok));
					MAKE_off_zero(t, off);
					COPY_off(tok_member_value(tok), off);
				}
				bound = 0;
			}
			break;
		}
		case tok_type_tag: {
			/* Type tokens */
			TYPE t = DEREF_type(tok_type_value(tok));
			if (IS_NULL_type(t) || EQ_type(t, redef_type)) {
				if (def) {
					t = type_error;
					COPY_type(tok_type_value(tok), t);
				}
				bound = 0;
			}
			break;
		}
		case tok_class_tag: {
			/* Template class tokens */
			IDENTIFIER cid = DEREF_id(tok_class_value(tok));
			if (IS_NULL_id(cid) || EQ_id(cid, redef_id)) {
				if (def) {
					HASHID nm = KEYWORD(lex_zzzz);
					cid = DEREF_id(hashid_id(nm));
					COPY_id(tok_class_value(tok), cid);
				}
				bound = 0;
			}
			break;
		}
		}
	}
	return bound;
}


/*
    This routine constructs a list of token arguments for the token id
    from the token parameters pids.  Any errors arising from undefined
    parameters are added to err.
*/

LIST(TOKEN)
make_token_args(IDENTIFIER id, LIST(IDENTIFIER) pids, ERROR *err)
{
	LIST(TOKEN) args = NULL_list(TOKEN);
	while (!IS_NULL_list(pids)) {
		IDENTIFIER pid = DEREF_id(HEAD_list(pids));
		if (!IS_NULL_id(pid) && IS_id_token(pid)) {
			TOKEN tok = DEREF_tok(id_token_sort(pid));
			if (!is_bound_tok(tok, 1)) {
				/* Token parameter not defined */
				if (IS_id_token(id)) {
					add_error(err, ERR_token_arg_undef(pid, id));
				} else {
					add_error(err, ERR_temp_deduct_undef(pid, id));
				}
			}
			tok = expand_sort(tok, 2, 1);
			CONS_tok(tok, args, args);
		}
		pids = TAIL_list(pids);
	}
	args = REVERSE_list(args);
	return args;
}


/*
    This routine skips a set of token arguments for the token id.  It is
    entered with the current token pointing to the token name preceding
    the initial open bracket.
*/

PPTOKEN *
skip_token_args(IDENTIFIER id)
{
	PPTOKEN *q;
	LOCATION loc;
	int brackets = 0;
	PPTOKEN *p = crt_token;
	loc = crt_loc;
	for (;;) {
		int t = expand_preproc(EXPAND_AHEAD);
		if (t == lex_open_Hround) {
			brackets++;
		} else if (t == lex_close_Hround) {
			if (--brackets == 0) {
				break;
			}
		} else if (t == lex_eof) {
			HASHID nm = DEREF_hashid(id_name(id));
			report(loc, ERR_cpp_replace_arg_eof(nm));
			break;
		}
	}
	q = p->next;
	snip_tokens(q, crt_token);
	crt_token = p;
	return q;
}


/*
    This routine parses the preprocessing tokens p as a list of arguments
    for the procedure token id.
*/

static LIST(TOKEN)
parse_token_args(IDENTIFIER id, PPTOKEN *p)
{
	int t;
	int d = 0;
	int ok = 1;
	PARSE_STATE st;
	unsigned m = 0;
	int started = 0;
	LIST(TOKEN) args;
	ERROR err = NULL_err;
	TOKEN tok = DEREF_tok(id_token_sort(id));
	LIST(IDENTIFIER) pids = DEREF_list(tok_proc_pids(tok));
	LIST(IDENTIFIER) bids = DEREF_list(tok_proc_bids(tok));
	unsigned n = LENGTH_list(pids);

	/* Initialise parser */
	save_state(&st, 1);
	init_parser(p);
	ADVANCE_LEXER;
	t = crt_lex_token;
	if (t == lex_open_Hround || t == lex_open_Htemplate) {
		ADVANCE_LEXER;
	}
	if (IS_NULL_list(pids)) {
		/* Empty parameter list */
		t = crt_lex_token;
		if (t == lex_close_Hround || t == lex_close_Htemplate) {
			ADVANCE_LEXER;
		}
	} else {
		/* Non-empty parameter list */
		while (!IS_NULL_list(pids)) {
			IDENTIFIER pid = DEREF_id(HEAD_list(pids));
			if (!IS_NULL_id(pid)) {
				TYPE mt = NULL_type;
				t = crt_lex_token;
				if (t == lex_close_Hround ||
				    t == lex_close_Htemplate) {
					ADVANCE_LEXER;
					break;
				}
				if (started) {
					/* Each argument deduction is (nearly)
					 * independent */
					mt = expand_member_type(pid);
					d = save_token_args(bids,
							    NULL_list(TOKEN));
				}
				if (!parse_token(pid, mt, 1, 0, bids)) {
					ok = 0;
				}
				if (started) {
					/* Combine argument deductions */
					IGNORE merge_token_args(bids, d, 2);
				}
				started = 1;
				if (have_syntax_error) {
					ok = 0;
					break;
				}
			} else {
				ok = 0;
				break;
			}
			m++;
			t = crt_lex_token;
			if (t == lex_close_Hround ||
			    t == lex_close_Htemplate) {
				ADVANCE_LEXER;
				break;
			}
			pids = TAIL_list(pids);
			if (!IS_NULL_list(pids)) {
				if (t == lex_comma) {
					ADVANCE_LEXER;
				} else {
					report(crt_loc,
					       ERR_lex_expect(lex_comma));
				}
			}
		}
	}

	/* Check for end of arguments */
	if (ok) {
		t = crt_lex_token;
		if (t == lex_comma) {
			m = n + 1;
		} else if (t != lex_eof) {
			ERROR err2 = ERR_lex_parse(crt_token);
			report(crt_loc, err2);
			ok = 0;
		}
		if (ok && m != n) {
			HASHID nm = DEREF_hashid(id_name(id));
			ERROR err2 = ERR_cpp_replace_arg_number(nm, m, m, n);
			report(crt_loc, err2);
		}
		IGNORE check_value(OPT_VAL_macro_args,(ulong)m);
	}

	/* Restore state */
	restore_state(&st);
	p = restore_parser();
	free_tok_list(p);

	/* Construct token arguments */
	args = make_token_args(id, bids, &err);
	if (!IS_NULL_err(err)) {
		if (ok) {
			report(crt_loc, err);
		} else {
			destroy_error(err, 1);
		}
	}
	return args;
}


/*
    This routine applies the expression procedure token id to the
    arguments given by the preprocessing tokens p.
*/

EXP
parse_exp_token(IDENTIFIER id, PPTOKEN *p)
{
	EXP e;
	LIST(TOKEN) args;
	TOKEN tok = DEREF_tok(id_token_sort(id));
	LIST(IDENTIFIER) bids = DEREF_list(tok_proc_bids(tok));
	int d = save_token_args(bids, NULL_list(TOKEN));
	args = parse_token_args(id, p);
	e = apply_exp_token(id, args, 2);
	restore_token_args(bids, d);
	return e;
}


/*
    This routine applies the type procedure token id to the arguments
    given by the preprocessing tokens p.
*/

TYPE
parse_type_token(IDENTIFIER id, PPTOKEN *p)
{
	TYPE t;
	if (IS_id_token(id)) {
		/* Type token */
		LIST(TOKEN) args;
		TOKEN tok = DEREF_tok(id_token_sort(id));
		LIST(IDENTIFIER) bids = DEREF_list(tok_proc_bids(tok));
		int d = save_token_args(bids, NULL_list(TOKEN));
		args = parse_token_args(id, p);
		t = apply_type_token(id, args, NULL_id);
		restore_token_args(bids, d);
	} else {
		/* Typedef template */
		t = parse_typedef_templ(id, p);
	}
	return t;
}


/*
    This routine applies the member procedure token id to the arguments
    given by the preprocessing tokens p.
*/

OFFSET
parse_mem_token(IDENTIFIER id, PPTOKEN *p)
{
	OFFSET off;
	LIST(TOKEN) args;
	TOKEN tok = DEREF_tok(id_token_sort(id));
	LIST(IDENTIFIER) bids = DEREF_list(tok_proc_bids(tok));
	int d = save_token_args(bids, NULL_list(TOKEN));
	args = parse_token_args(id, p);
	off = apply_mem_token(id, args);
	restore_token_args(bids, d);
	return off;
}


/*
    This routine defines the tokenised object id by means of the macro
    mid.  It returns true if this is possible.
*/

int
define_token_macro(IDENTIFIER id, IDENTIFIER mid)
{
    DECL_SPEC fds = DEREF_dspec(id_storage(id));
    IDENTIFIER tid = find_token(id);
    if (IS_id_token(tid)) {
	int fn = 1;
	PPTOKEN *p;
	PPTOKEN *r;
	LOCATION loc;
	PARSE_STATE st;
	STACK(EXP) tries;
	LIST(IDENTIFIER) pids;
	LIST(TYPE) ex = univ_type_set;
	TOKEN tok = DEREF_tok(id_token_sort(tid));
	DECL_SPEC ds = DEREF_dspec(id_storage(tid));

	/* Find token definition */
	if (IS_id_obj_macro(mid)) {
	    switch (TAG_tok(tok)) {
		case tok_func_tag:
		    /* Function tokens read as identifiers */
		    IGNORE find_func_token(id,(unsigned)UINT_MAX);
		    COPY_dspec(id_storage(id), (fds & ~dspec_token));
		    fn = 0;
		    break;
		case tok_templ_tag:
		case tok_proc_tag:
		    /* Can't have procedure tokens */
		    report(preproc_loc, ERR_token_def_args(id));
		    return 1;
	    }
	    p = DEREF_pptok(id_obj_macro_defn(mid));
	} else {
	    unsigned n = DEREF_unsigned(id_func_macro_no_params(mid));
	    switch (TAG_tok(tok)) {
		case tok_func_tag: {
		    /* Find function token with n parameters */
		    TYPE t = DEREF_type(tok_func_type(tok));
		    tid = find_func_token(id, n);
		    if (IS_NULL_id(tid)) {
			report(preproc_loc, ERR_token_def_args(id));
			return 1;
		    }
		    tok = DEREF_tok(id_token_sort(tid));
		    tok = func_proc_token(tok);
		    id = DEREF_id(id_token_alt(tid));
		    fds = DEREF_dspec(id_storage(id));
		    COPY_dspec(id_storage(id), (fds & ~dspec_token));
		    ex = DEREF_list(type_func_except(t));
		    break;
		}
		case tok_proc_tag:
		    /* Procedure tokens */
		    pids = DEREF_list(tok_proc_pids(tok));
		    if (LENGTH_list(pids)!= n) {
			report(preproc_loc, ERR_token_def_args(id));
			return 1;
		    }
		    break;
		default:
		    /* Can't have simple tokens */
		    report(preproc_loc, ERR_token_def_args(id));
		    return 1;
	    }
	    p = DEREF_pptok(id_func_macro_defn(mid));
	}

	/* Expand token definition */
	p = expand_tok_list(p);
	r = new_pptok();
	r->tok = lex_newline;
	r->next = NULL;
	if (p == NULL) {
	    p = r;
	} else {
	    PPTOKEN *q = p;
	    while (q->next)q = q->next;
	    q->next = r;
	}

	/* Allow for procedure tokens */
	if (IS_tok_proc(tok)) {
	    NAMESPACE ns;
	    PPTOKEN *q = p;
	    pids = DEREF_list(tok_proc_pids(tok));
	    while (q != NULL) {
		if (q->tok == lex_macro_Harg) {
		    unsigned long pn = q->pp_data.par.no - 1;
		    LIST(IDENTIFIER)qids = pids;
		    while (pn && !IS_NULL_list(qids)) {
			qids = TAIL_list(qids);
			pn--;
		    }
		    if (!IS_NULL_list(qids)) {
			IDENTIFIER qid = DEREF_id(HEAD_list(qids));
			if (!IS_NULL_id(qid)) {
			    HASHID qnm = DEREF_hashid(id_name(qid));
			    q->tok = lex_identifier;
			    q->pp_data.id.hash = qnm;
			    q->pp_data.id.use = qid;
			}
		    }
		}
		q = q->next;
	    }
	    pids = DEREF_list(tok_proc_bids(tok));
	    while (!IS_NULL_list(pids)) {
		IDENTIFIER pid = DEREF_id(HEAD_list(pids));
		if (!IS_NULL_id(pid)) {
		    DECL_SPEC pds = DEREF_dspec(id_storage(pid));
		    pds |= dspec_pure;
		    COPY_dspec(id_storage(pid), pds);
		}
		pids = TAIL_list(pids);
	    }
	    ns = DEREF_nspace(tok_proc_pars(tok));
	    add_namespace(ns);
	}

	/* Parse token */
	loc = crt_loc;
	bad_crt_loc++;
	crt_loc = preproc_loc;
	tries = crt_try_blocks;
	start_try_check(ex);
	save_state(&st, 0);
	init_parser(p);
	ADVANCE_LEXER;
	pids = NULL_list(IDENTIFIER);
	IGNORE parse_token(tid, NULL_type, fn, 1, pids);
	if (!have_syntax_error && crt_lex_token != lex_newline) {
	    ERROR err = ERR_lex_parse(crt_token);
	    report(crt_loc, err);
	}
	if (ds & dspec_pure) {
	    report(preproc_loc, ERR_token_def_not(id));
	} else {
	    if (do_dump) {
		    dump_declare(id, &crt_loc, 1);
	    }
	}
	restore_state(&st);
	p = restore_parser();
	free_tok_list(p);
	IGNORE end_try_check(id, NULL_exp);
	crt_try_blocks = tries;
	crt_loc = loc;
	bad_crt_loc--;

	/* Allow for procedure tokens */
	if (IS_tok_proc(tok)) {
	    remove_namespace();
	    pids = DEREF_list(tok_proc_bids(tok));
	    while (!IS_NULL_list(pids)) {
		IDENTIFIER pid = DEREF_id(HEAD_list(pids));
		if (!IS_NULL_id(pid)) {
		    DECL_SPEC pds = DEREF_dspec(id_storage(pid));
		    pds &= ~dspec_pure;
		    COPY_dspec(id_storage(pid), pds);
		}
		pids = TAIL_list(pids);
	    }
	}
	COPY_dspec(id_storage(id), fds);
	return 1;
    }
    return 0;
}


/*
    This routine is used to define the tokenised member id of t by the
    list of immediately following preprocessing tokens.  This is used
    to implement the '#pragma TenDRA member definition' command.
*/

int
define_mem_macro(IDENTIFIER id, TYPE t)
{
	IDENTIFIER tid = tok_member(id, t, 0);
	if (!IS_NULL_id(tid)) {
		id = tid;
		tid = find_token(tid);
		if (!IS_NULL_id(tid) && IS_id_token(tid)) {
			TOKEN tok = DEREF_tok(id_token_sort(tid));
			if (IS_tok_member(tok)) {
				int def;
				LOCATION loc;
				DECL_SPEC ds = DEREF_dspec(id_storage(tid));
				LIST(IDENTIFIER) pids = NULL_list(IDENTIFIER);
				bad_crt_loc++;
				loc = crt_loc;
				crt_loc = preproc_loc;
				def = parse_token(tid, NULL_type, 1, 1, pids);
				if (ds & dspec_pure) {
					report(preproc_loc,
					       ERR_token_def_not(id));
				} else {
					if (do_dump) {
						dump_declare(id, &crt_loc, 1);
					}
				}
				crt_loc = loc;
				bad_crt_loc--;
				return def;
			}
		}
		report(preproc_loc, ERR_token_undecl(id));
	}
	if (in_preproc_dir) {
		IGNORE skip_to_end();
	}
	return 0;
}


/*
    The normal unification routine is called immediately after the
    declaration of an object.  However for 'const' objects it is more
    useful to postpone the unification until after the initialisation.
*/

IDENTIFIER unify_id_pending = NULL_id;


/*
    This routine is called whenever an identifier id hides an identifier
    pid from the same namespace.  Normally this is a redeclaration error
    which will have been caught by the declaration routines, however if
    pid is a token identifier it may be a token definition.  The routine
    returns true if this is the case.
*/

int unify_id
(IDENTIFIER pid, IDENTIFIER id, int def)
{
    int ok = 0;
    IDENTIFIER tid = DEREF_id(id_token_alt(pid));
    if (IS_id_token(tid)) {
	/* Previous definition was a token */
	TOKEN tok = DEREF_tok(id_token_sort(tid));
	switch (TAG_tok(tok)) {
	    case tok_exp_tag:
	    case tok_nat_tag:
	    case tok_snat_tag: {
		/* Expression tokens */
		EXP e;
		int expl = 0;
		switch (TAG_id(id)) {
		    case id_variable_tag: {
#if LANGUAGE_CPP
			TYPE t = DEREF_type(id_variable_type(id));
			CV_SPEC cv = DEREF_cv(type_qual(t));
			if (cv == (cv_lvalue | cv_const)) {
			    /* Allow for const objects */
			    e = DEREF_exp(id_variable_init(id));
			    if (IS_NULL_exp(e)) {
				if (IS_NULL_id(unify_id_pending)) {
				    unify_id_pending = pid;
				    return 1;
				}
			    }
			}
#endif
			unify_id_pending = NULL_id;
			goto variable_label;
		    }
		    case id_enumerator_tag:
			expl = 1;
			goto variable_label;
variable_label:
		    case id_parameter_tag:
		    case id_stat_member_tag: {
			e = make_id_exp(id);
			if (define_exp_token(tid, e, expl)) {
			    LOCATION loc;
			    DEREF_loc(id_loc(id), loc);
			    COPY_loc(id_loc(tid), loc);
			}
			ok = 1;
			break;
		    }
		}
		break;
	    }
	}
	if (ok) {
	    /* Set alternate look-up for token */
	    HASHID nm = DEREF_hashid(id_name(tid));
	    MEMBER mem = search_member(token_namespace, nm, 0);
	    if (!IS_NULL_member(mem)) {
		COPY_id(member_alt(mem), id);
	    }
	}
    }
    if (ok) {
	/* Token definition */
	DECL_SPEC ds = DEREF_dspec(id_storage(tid));
	if (ds & dspec_pure) {
	    report(crt_loc, ERR_token_def_not(pid));
	} else {
	    if (do_dump) {
		    dump_declare(pid, &crt_loc, 1);
	    }
	}
    } else {
	/* Illegal redeclaration */
	if (def) {
		id = pid;
	}
	report(crt_loc, ERR_basic_odr_diff(id, id_loc(id)));
    }
    return ok;
}
