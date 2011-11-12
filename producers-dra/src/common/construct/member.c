/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#include "config.h"
#include "c_types.h"
#include "ctype_ops.h"
#include "exp_ops.h"
#include "hashid_ops.h"
#include "graph_ops.h"
#include "id_ops.h"
#include "member_ops.h"
#include "nspace_ops.h"
#include "off_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "access.h"
#include "basetype.h"
#include "cast.h"
#include "check.h"
#include "chktype.h"
#include "class.h"
#include "constant.h"
#include "convert.h"
#include "copy.h"
#include "derive.h"
#include "expression.h"
#include "function.h"
#include "hash.h"
#include "identifier.h"
#include "initialise.h"
#include "instance.h"
#include "member.h"
#include "namespace.h"
#include "operator.h"
#include "parse.h"
#include "predict.h"
#include "statement.h"
#include "syntax.h"
#include "template.h"
#include "token.h"


/*
    FORM THE ADDRESS OF AN EXPRESSION

    This routine forms the address of the expression e.  If e is not an
    lvalue then a temporary is introduced and its address is returned.
*/

static EXP
member_address(EXP e)
{
	TYPE t = DEREF_type(exp_type(e));
	CV_SPEC qual = DEREF_cv(type_qual(t));
	if (qual & cv_lvalue) {
		t = rvalue_type(t);
	} else {
		ERROR err = NULL_err;
		e = make_temporary(t, e, NULL_exp, 0, &err);
		if (!IS_NULL_err(err)) {
			report(crt_loc, err);
		}
	}
	MAKE_type_ptr(cv_none, t, t);
	MAKE_exp_address(t, e, e);
	return e;
}


/*
    BEGIN A FIELD SELECTOR EXPRESSION

    This routine begins the construction of the field selector expressions
    'a.b' and 'a->b' (as indicated by op).  The base type of a (after
    removing pointers in the '->' case) is returned via pt.  Note that
    it is not checked that this is a class type at this stage because the
    explicit destructor notation can apply to any type.  Note that '->'
    can be overloaded (albeit in a different way to most other operations)
    but '.' can't.
*/

EXP
begin_field_exp(int op, EXP a, TYPE *pt, NAMESPACE *pns)
{
	TYPE t, s;
	unsigned c;
	int ptr = 0;
	unsigned tag;

	/* Do operand conversion */
	if (op == lex_arrow) {
		/* Check for overloading with '->' */
#if LANGUAGE_CPP
		int go = 1;
		LIST(TYPE) prev = NULL_list(TYPE);
		do {
			/* Perform reference conversions */
			a = convert_reference(a, REF_NORMAL);
			t = DEREF_type(exp_type(a));
			c = type_category(&t);
			if (overload_depth) {
				break;
			}
			if (IS_TYPE_TEMPL(c)) {
				/* Template parameter type */
				EXP e;
				MAKE_exp_op(t, op, a, a, e);
				cache_lookup = 0;
				*pns = NULL_nspace;
				*pt = t;
				return e;
			}
			if (IS_TYPE_OVERLOAD(c)) {
				EXP e = unary_overload(lex_arrow, a);
				if (IS_NULL_exp(e)) {
					/* '->' isn't overloaded */
					go = 0;
				} else {
					/* '->' is overloaded, try again */
					LIST(TYPE) p = prev;
					while (!IS_NULL_list(p)) {
						/* Check for cycles */
						s = DEREF_type(HEAD_list(p));
						if (eq_type(s, t)) {
							ERROR err = ERR_over_match_oper_arrow();
							report(crt_loc, err);
							go = 0;
							break;
						}
						p = TAIL_list(p);
					}
					CONS_type(t, prev, prev);
					a = e;
				}
			} else {
				/* '->' can't be overloaded */
				go = 0;
			}
		} while (go);
		DESTROY_list(prev, SIZE_type);
#else
		/* Perform reference conversions */
		a = convert_reference(a, REF_NORMAL);
		t = DEREF_type(exp_type(a));
		c = type_category(&t);
#endif

		/* Do lvalue conversions if necessary */
		if (IS_TYPE_ADDRESS(c)) {
			a = convert_lvalue(a);
			t = DEREF_type(exp_type(a));
		}
	} else {
		/* For '.' just do reference conversions */
		a = convert_reference(a, REF_NORMAL);
		t = DEREF_type(exp_type(a));
#if LANGUAGE_CPP
		c = type_category(&t);
		if (IS_TYPE_TEMPL(c)) {
			/* Template parameter type */
			EXP e;
			MAKE_exp_op(t, op, a, a, e);
			cache_lookup = 0;
			*pns = NULL_nspace;
			*pt = t;
			return e;
		}
#endif
	}

	/* Check operand type */
	tag = TAG_type(t);
	if (tag == type_token_tag) {
		t = expand_type(t, 0);
		tag = TAG_type(t);
	}
	if (tag == type_ptr_tag) {
		s = DEREF_type(type_ptr_sub(t));
		tag = TAG_type(s);
		if (tag == type_token_tag) {
			if (op == lex_arrow && is_templ_type(s)) {
				/* Template parameter type */
				EXP e;
				MAKE_exp_op(s, op, a, a, e);
				cache_lookup = 0;
				*pns = NULL_nspace;
				*pt = s;
				return e;
			}
			s = expand_type(s, 0);
			tag = TAG_type(s);
		}
		ptr = 1;
	} else {
		s = t;
	}
	if (tag == type_compound_tag) {
		/* Operand is a class or a pointer to a class */
		ERROR err;
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(s));
		NAMESPACE ns = DEREF_nspace(ctype_member(ct));

		/* Check that the correct operator has been used */
		if (op == lex_arrow) {
			if (!ptr) {
				report(crt_loc, ERR_expr_ref_arrow_dot(t));
			}
		} else {
			if (ptr) {
				report(crt_loc, ERR_expr_ref_dot_arrow(t));
			}
		}

		/* Check that the class is complete */
		err = check_incomplete(s);
		cache_lookup = 0;
		if (!IS_NULL_err(err)) {
			/* Incomplete class */
			BASE_TYPE key = find_class_key(ct);
			err = concat_error(err, ERR_expr_ref_incompl(op, key));
			report(crt_loc, err);
			ns = NULL_nspace;
			s = type_error;
		} else {
			/* Complete class */
			add_namespace(ns);
		}
		*pns = ns;
		*pt = s;

		/* Check for null pointers */
		if (IS_exp_null(a) && ptr) {
			report(crt_loc, ERR_expr_unary_op_indir_null(op));
		}
	} else {
		/* Bad operand type */
		if (!IS_type_error(s)) {
			if (op == lex_arrow) {
				if (!ptr) {
					string key = find_vocab(lex_class);
					report(crt_loc,
					       ERR_expr_ref_arrow_op(t, key));
					s = type_error;
				}
			} else {
				s = t;
			}
		}
		cache_lookup = 0;
		*pns = NULL_nspace;
		*pt = s;
	}
	return a;
}


/*
    CREATE A FIELD SELECTOR EXPRESSION

    This routine completes the field selector expression constructed by
    begin_field_exp.  The a arguments is the outputs of this routine,
    ns represents the class namespace of the type of a, op indicated which
    selector is being used, and fld indicates the field being selected.
*/

static EXP
apply_field_op(int op, EXP a, NAMESPACE ns, IDENTIFIER fld, int templ)
{
	EXP e;
	GRAPH gr;
	HASHID nm;
	TYPE t, s;
	string key;
	CV_SPEC qual;
	ERROR err = NULL_err;
	LIST(TOKEN) args = NULL_list(TOKEN);

	/* Find the type of a */
	s = DEREF_type(exp_type(a));
	qual = find_cv_qual(s);

	/* Check for template members */
	if (templ && IS_id_undef(fld)) {
		TYPE form = DEREF_type(id_undef_form(fld));
		if (!IS_NULL_type(form) && IS_type_token(form)) {
			fld = DEREF_id(type_token_tok(form));
			args = DEREF_list(type_token_args(form));
			templ = 2;
		}
	}

	/* Check that fld is a member of ns */
	gr = is_subfield(ns, fld);
	if (!IS_NULL_graph(gr)) {
		IDENTIFIER orig = fld;
		fld = search_subfield(ns, gr, orig);
		if (templ == 2) {
			/* Apply template arguments */
			fld = apply_template(fld, args, 0, 0);
		}
		switch (TAG_id(fld)) {
		case id_stat_member_tag:
			/* Static data members */
			e = make_id_exp(fld);
			e = join_exp(a, e);
			return e;
		case id_mem_func_tag:
		case id_stat_mem_func_tag:
			/* Member functions */
			if (!templ) {
				IDENTIFIER tid = find_template(fld, 0);
				if (!IS_NULL_id(tid)) {
					/* Should have 'template' prefix */
					report(crt_loc,
					       ERR_temp_names_mem(fld));
				}
			}

			/* Form '*a' for pointers */
			if (IS_type_ptr(s)) {
				s = DEREF_type(type_ptr_sub(s));
				s = lvalue_type(s);
				MAKE_exp_indir(s, a, a);
			}

			/* Construct the result */
			e = make_id_exp(fld);
			t = DEREF_type(exp_type(e));
			MAKE_exp_call(t, e, a, gr, e);
			return e;
		case id_member_tag: {
			/* Non-static data members */
			TYPE p;
			OFFSET off;
			int virt = 0;

			/* Allow for pointer types */
			if (IS_type_ptr(s)) {
				/* Form '*a' for pointers */
				s = DEREF_type(type_ptr_sub(s));
				qual = DEREF_cv(type_qual(s));
				qual |= cv_lvalue;
			} else {
				/* Form '&a' for non-pointers */
				a = member_address(a);
			}

			/* Find result type */
			use_id(fld, 0);
			t = DEREF_type(id_member_type(fld));
			if (!IS_type_ref(t)) {
				CV_SPEC cv = find_cv_qual(t);
				cv &= cv_qual;
				if (qual & cv_const) {
					DECL_SPEC ds =
					    DEREF_dspec(id_storage(fld));
					if (!(ds & dspec_mutable)) {
						/* 'mutable' cancels out
						 * 'const' */
						cv |= cv_const;
					}
				}
				if (qual & cv_volatile) {
					cv |= cv_volatile;
				}
				t = qualify_type(t, cv, 0);
			}

			/* Check for virtual base members */
			gr = DEREF_graph(id_member_base(fld));
			if (!IS_NULL_graph(gr)) {
				DECL_SPEC acc = DEREF_dspec(graph_access(gr));
				if (acc & dspec_mutable) {
					/* Contained in virtual base */
					if (know_type(a) != 1) {
						virt = 1;
					}
				}
			}

			/* Form the result */
			off = DEREF_off(id_member_off(fld));
			MAKE_type_ptr(cv_none, t, p);
			MAKE_exp_add_ptr(p, a, off, virt, e);
			if (qual & cv_lvalue) {
				/* The result is an lvalue if s is */
				t = lvalue_type(t);
				MAKE_exp_indir(t, e, e);
			} else {
				MAKE_exp_contents(t, e, e);
			}
			return e;
		}
		case id_enumerator_tag: {
			/* Enumerator members */
			NAT n;
			unsigned etag;
			use_id(fld, 0);
			e = DEREF_exp(id_enumerator_value(fld));
			DECONS_exp_int_lit(t, n, etag, e);
			MAKE_exp_int_lit(t, n, etag, e);
			e = join_exp(a, e);
			return e;
		}
		case id_ambig_tag:
			/* Ambiguous members */
			IGNORE report_ambiguous(fld, 0, 1, 0);
			e = make_error_exp(1);
			e = join_exp(a, e);
			return e;
		case id_class_name_tag:
		case id_class_alias_tag:
		case id_enum_name_tag:
		case id_enum_alias_tag:
		case id_type_alias_tag:
			/* Type members */
			err = ERR_expr_ref_type(fld);
			break;
		case id_undef_tag:
			/* Undefined members */
			nm = DEREF_hashid(id_name(fld));
			err = ERR_lookup_qual_undef(nm, ns);
			break;
		}
	}

	/* Report any errors */
	nm = DEREF_hashid(id_name(fld));
	if (IS_hashid_destr(nm)) {
		/* Pseudo-destructor call */
		destroy_error(err, 1);
		return NULL_exp;
	}
	key = find_vocab(lex_class);
	if (IS_NULL_err(err)) {
		err = ERR_lookup_qual_bad(fld, ns);
	}
	err = concat_error(err, ERR_expr_ref_select(op, key));
	report(crt_loc, err);
	e = make_error_exp(1);
	e = join_exp(a, e);
	return e;
}


/*
    COMPLETE A FIELD SELECTOR EXPRESSION

    This routine gives the main interface to apply_field_op, allowing for
    the error case and adjusting the name look-up stack.  a is the return
    value from begin_field_exp, while t is the returned base type.  The
    field identifier is given by fld, this being prefixed by template if
    templ is true.
*/

EXP
end_field_exp(int op, EXP a, TYPE t, NAMESPACE ns, IDENTIFIER fld, int templ)
{
	EXP e;
	QUALIFIER cq = crt_id_qualifier;
	if (cq == qual_full || cq == qual_top) {
		/* Bad field selector */
		report(crt_loc, ERR_expr_ref_qual(cq, fld));
	}
	if (!IS_NULL_nspace(ns)) {
		/* Class types */
		remove_namespace();
		cache_lookup = old_cache_lookup;
		if (cq != qual_none) {
			templ = 1;
		}
		e = apply_field_op(op, a, ns, fld, templ);
		if (!IS_NULL_exp(e)) {
			return e;
		}
	} else {
		cache_lookup = old_cache_lookup;
	}

	if (IS_exp_op(a)) {
		/* Template parameter types */
		EXP b;
		if (cq == qual_none) {
			fld = underlying_id(fld);
		}
		MAKE_exp_member(t, fld, qual_nested, b);
		COPY_exp(exp_op_arg2(a), b);
		e = a;
	} else {
		/* Other types */
		if (!IS_type_error(t)) {
			HASHID nm = DEREF_hashid(id_name(fld));
			if (IS_hashid_destr(nm)) {
				/* Allow for pseudo-destructor call */
				TYPE fn = type_func_void;
				TYPE r = DEREF_type(hashid_destr_type(nm));
				TYPE s = expand_type(r, 2);
				if (!EQ_type(s, r)) {
					nm = lookup_destr(s, NULL_id);
					fld = DEREF_id(hashid_id(nm));
					t = expand_type(t, 2);
					r = s;
				}
				/* NOT YET IMPLEMENTED - scalar type */
				if (!eq_type_unqual(t, r) &&
				    !IS_type_error(r)) {
					/* Destructor types should match */
					report(crt_loc,
					       ERR_expr_pseudo_obj(nm, t));
				}
				MAKE_exp_undeclared(fn, fld, cq, e);
				MAKE_exp_call(fn, e, a, NULL_graph, e);
			} else {
				/* Anything else is illegal */
				string key = find_vocab(lex_class);
				TYPE s = DEREF_type(exp_type(a));
				if (op == lex_arrow) {
					report(crt_loc,
					       ERR_expr_ref_arrow_op(s, key));
				} else {
					report(crt_loc,
					       ERR_expr_ref_dot_op(s, key));
				}
				e = make_error_exp(1);
			}
		} else {
			e = make_error_exp(1);
		}
	}
	return e;
}


/*
    CONSTRUCT A FIELD SELECTOR EXPRESSION

    This routine is an alternative interface to the field selector
    expression routines used in the instantiation of template functions.
    It constructs 'a.b' or 'a->b' depending on op, where b is an
    identifier expression giving the member name.
*/

EXP
make_field_exp(int op, EXP a, EXP b)
{
	TYPE t = NULL_type;
	NAMESPACE ns = NULL_nspace;
	QUALIFIER cq = crt_id_qualifier;
	EXP e = begin_field_exp(op, a, &t, &ns);
	IDENTIFIER fld = DEREF_id(exp_member_id(b));
	QUALIFIER qual = DEREF_qual(exp_member_qual(b));
	crt_id_qualifier = qual;
	if (!IS_NULL_nspace(ns)) {
		/* Rescan field for class namespaces */
		fld = rescan_id(fld, qual, 0);
	}
	e = end_field_exp(op, e, t, ns, fld, 1);
	crt_id_qualifier = cq;
	return e;
}


/*
    CONSTRUCT A MEMBER SELECTOR EXPRESSION

    This routine constructs the member selector expressions 'a.*b' and
    'a->*b' (as indicated by op).  Note that '->*' can be overloaded but
    '.*' can't.
*/

#if LANGUAGE_CPP

EXP
make_member_exp(int op, EXP a, EXP b)
{
	EXP e;
	int is_ptr;
	CV_SPEC qual;
	TYPE ta, tap;
	unsigned sa, sb;
	TYPE tb, tbr, tbp;
	CLASS_TYPE ca, cb;

	/* Do reference conversions */
	a = convert_reference(a, REF_NORMAL);
	b = convert_reference(b, REF_NORMAL);

	/* Find operand types */
	ta = DEREF_type(exp_type(a));
	sa = type_category(&ta);
	tb = DEREF_type(exp_type(b));
	sb = type_category(&tb);

	/* Check for overloading */
	if (op == lex_arrow_Hstar) {
		if (IS_TYPE_OVERLOAD(sa) || IS_TYPE_OVERLOAD(sb)) {
			if (overload_depth == 0) {
				e = binary_overload(op, a, b);
				return e;
			}
		}
	} else {
		if (IS_TYPE_TEMPL(sa) || IS_TYPE_TEMPL(sb)) {
			if (overload_depth == 0) {
				e = binary_overload(op, a, b);
				return e;
			}
		}
	}

	/* Do lvalue conversion */
	if (IS_TYPE_ADDRESS(sb)) {
		b = convert_lvalue(b);
		tb = DEREF_type(exp_type(b));
	}

	/* Second operand must be pointer to member */
	if (!IS_TYPE_PTR_MEM(sb)) {
		if (!IS_TYPE_ERROR(sa) && !IS_TYPE_ERROR(sb)) {
			report(crt_loc, ERR_expr_mptr_oper_op2(op, tb));
		}
		e = make_error_exp(1);
		return e;
	}
	cb = DEREF_ctype(type_ptr_mem_of(tb));
	tbr = DEREF_type(type_ptr_mem_sub(tb));
	if (in_template_decl) {
		/* Allow for template parameters */
		TYPE fb = DEREF_type(ctype_form(cb));
		if (is_templ_type(fb)) {
			MAKE_exp_op(fb, op, a, b, e);
			return e;
		}
	}

	/* Check first operand type */
	if (IS_type_ptr(ta)) {
		a = convert_lvalue(a);
		ta = DEREF_type(exp_type(a));
		tap = DEREF_type(type_ptr_sub(ta));
		qual = DEREF_cv(type_qual(tap));
		qual |= cv_lvalue;
		is_ptr = 1;
	} else {
		tap = ta;
		qual = DEREF_cv(type_qual(ta));
		is_ptr = 0;
	}
	if (IS_type_compound(tap)) {
		ERROR err;
		ca = DEREF_ctype(type_compound_defn(tap));
		if (eq_ctype(ca, cb)) {
			/* Equal base types */
			/* EMPTY */
		} else {
			GRAPH gr = find_base_class(ca, cb, 1);
			if (!IS_NULL_graph(gr)) {
				/* cb is a base class of ca */
				OFFSET off;
				err = check_ambig_base(gr);
				if (!IS_NULL_err(err)) {
					ERROR err2 =
					    ERR_expr_mptr_oper_ambig(op);
					err = concat_error(err, err2);
					report(crt_loc, err);
				}
				check_base_access(gr);
				off = DEREF_off(graph_off(gr));
				tap = make_class_type(cb);
				MAKE_type_ptr(cv_none, tap, ta);
				if (is_ptr) {
					a = make_base_cast(ta, a, off);
				} else {
					a = member_address(a);
					a = make_base_cast(ta, a, off);
					ta = lvalue_type(tap);
					MAKE_exp_indir(ta, a, a);
				}
			} else {
				/* cb is not a base class of ca */
				goto error_lab;
			}
		}
		err = check_incomplete(tap);
		if (!IS_NULL_err(err)) {
			/* Class should be complete */
			err = concat_error(err, ERR_expr_mptr_oper_compl(op));
			report(crt_loc, err);
		}
	} else {
		/* Invalid base type */
		if (!IS_type_error(tap)) {
error_lab: {
		   ERROR err;
		   IDENTIFIER cid = DEREF_id(ctype_name(cb));
		   if (op == lex_arrow_Hstar) {
			   err = ERR_expr_mptr_oper_arrow_op(cid, ta);
		   } else {
			   err = ERR_expr_mptr_oper_dot_op(cid, ta);
		   }
		   report(crt_loc, err);
	   }
		}
		e = make_error_exp(1);
		return e;
	}

	/* Correct base type */
	if (op == lex_arrow_Hstar) {
		if (!is_ptr) {
			report(crt_loc, ERR_expr_mptr_oper_arrow_dot(ta));
		}
	} else {
		if (is_ptr) {
			report(crt_loc, ERR_expr_mptr_oper_dot_arrow(ta));
		}
	}

	/* Check for null pointers */
	if (IS_exp_null(a) && is_ptr) {
		report(crt_loc, ERR_expr_unary_op_indir_null(op));
	}
	if (IS_exp_null(b)) {
		report(crt_loc, ERR_expr_mptr_oper_null(op));
	}

	/* Construct the result */
	if (IS_type_func(tbr)) {
		/* Member functions */
		if (is_ptr) {
			ta = lvalue_type(ta);
			MAKE_exp_indir(ta, a, a);
		}
		MAKE_exp_call(tbr, b, a, NULL_graph, e);
	} else {
		/* Data members */
		OFFSET off;
		CV_SPEC cv1 = (qual & cv_qual);
		if (cv1) {
			/* The result type inherits both qualifiers */
			CV_SPEC cv2 = DEREF_cv(type_qual(tbr));
			tbr = qualify_type(tbr,(cv1 | cv2), 0);
		}
		if (!is_ptr) {
			/* For non-pointers construct '&a' */
			a = member_address(a);
		}
		MAKE_off_ptr_mem(b, off);
		MAKE_type_ptr(cv_none, tbr, tbp);
		MAKE_exp_add_ptr(tbp, a, off, 0, e);
		if (qual & cv_lvalue) {
			/* The result is an lvalue if tap is */
			tbr = lvalue_type(tbr);
			MAKE_exp_indir(tbr, e, e);
		} else {
			MAKE_exp_contents(tbr, e, e);
		}
	}
	return e;
}

#endif


/*
    LOOK UP A MEMBER IN A MEMBER FUNCTION DEFINITION

    This routine looks up the member fld.  In a member function definition
    the routine returns 'this->fld' for non-static data members and the
    parameter corresponding to 'this' for non-static function members,
    otherwise the null expression is returned.
*/

EXP
make_this_field(IDENTIFIER fld)
{
	IDENTIFIER fn = crt_func_id;
	if (in_function_defn && IS_id_mem_func(fn)) {
		NAMESPACE ns = DEREF_nspace(id_parent(fn));
		GRAPH gr = is_subfield(ns, fld);
		if (!IS_NULL_graph(gr)) {
			switch (TAG_id(fld)) {
			case id_member_tag:
			case id_mem_func_tag: {
				EXP e;
				TYPE t;
				IDENTIFIER id = this_param(fn, 1);
				if (in_default_arg) {
					/* Can't use in default argument */
					ERROR err =
					    ERR_dcl_fct_default_param(fld);
					report(crt_loc, err);
				}
				e = DEREF_exp(id_parameter_init(id));
				t = DEREF_type(exp_type(e));
				MAKE_exp_copy(t, e, e);
				e = apply_field_op(lex_arrow, e, ns, fld, 1);
				return e;
			}
			}
		}
	}
	return NULL_exp;
}


/*
    DECOMPOSE A BITFIELD OFFSET

    This routine decomposes the bitfield member offset off into its member
    component, which is returned, and its base class component, which is
    assigned to off.
*/

OFFSET
decons_bitf_off(OFFSET *off)
{
	OFFSET off1 = *off;
	if (!IS_NULL_off(off1) && IS_off_plus(off1)) {
		*off = DEREF_off(off_plus_arg1(off1));
		off1 = DEREF_off(off_plus_arg2(off1));
	} else {
		*off = NULL_off;
	}
	return off1;
}


/*
    DECOMPOSE A BITFIELD EXPRESSION

    This routine decomposes the lvalue bitfield expression e into its
    bitfield member offset, which is returned, and its class pointer
    component, which is assigned to e.
*/

OFFSET
decons_bitf_exp(EXP *e)
{
	EXP a = *e;
	OFFSET off = NULL_off;

	switch (TAG_exp(a)) {
	case exp_indir_tag: {
		/* Simple field access */
		a = DEREF_exp(exp_indir_ptr(a));
		if (IS_exp_add_ptr(a)) {
			TYPE t;
			int virt;
			OFFSET off1;
			DECONS_exp_add_ptr(t, a, off1, virt, a);
			UNUSED(t);
			t = DEREF_type(exp_type(a));
			off = decons_bitf_off(&off1);
			if (!IS_NULL_off(off1)) {
				MAKE_exp_add_ptr(t, a, off1, virt, a);
			}
			if (IS_exp_address(a)) {
				a = DEREF_exp(exp_address_arg(a));
			} else {
				if (IS_type_ptr(t)) {
					t = DEREF_type(type_ptr_sub(t));
				}
				t = lvalue_type(t);
				MAKE_exp_indir(t, a, a);
			}
			*e = a;
		}
		break;
	}
	case exp_comma_tag: {
		/* Comma expression */
		TYPE t = DEREF_type(exp_type(a));
		LIST(EXP) p = DEREF_list(exp_comma_args(a));
		LIST(EXP) q = NULL_list(EXP);
		while (!IS_NULL_list(p)) {
			EXP b = DEREF_exp(HEAD_list(p));
			p = TAIL_list(p);
			if (IS_NULL_list(p)) {
				off = decons_bitf_exp(&b);
				t = DEREF_type(exp_type(b));
			}
			CONS_exp(b, q, q);
		}
		q = REVERSE_list(q);
		MAKE_exp_comma(t, q, a);
		*e = a;
		break;
	}
	case exp_if_stmt_tag: {
		/* Conditional expression */
		TYPE t;
		EXP c = DEREF_exp(exp_if_stmt_cond(a));
		EXP b1 = DEREF_exp(exp_if_stmt_true_code(a));
		EXP b2 = DEREF_exp(exp_if_stmt_false_code(a));
		OFFSET off1 = decons_bitf_exp(&b1);
		OFFSET off2 = decons_bitf_exp(&b2);
		if (eq_offset(off1, off2, 0)) {
			off = off1;
		} else {
			/* NOT YET IMPLEMENTED */
			off = off1;
		}
		t = DEREF_type(exp_type(b1));
		MAKE_exp_if_stmt(t, c, b1, b2, NULL_id, a);
		*e = a;
		break;
	}
	}
	return off;
}


/*
    SET MEMBER OFFSET LOOK-UP NAMESPACE

    This routine sets the look-up namespace to that for the class type t.
    If t is not a class type then the null namespace is returned.
*/

NAMESPACE
offset_nspace(TYPE t)
{
	NAMESPACE ns;
	if (IS_type_compound(t)) {
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		complete_class(ct, 1);
		ns = DEREF_nspace(ctype_member(ct));
		cache_lookup = 0;
		add_namespace(ns);
	} else {
		ns = NULL_nspace;
		cache_lookup = 0;
	}
	return ns;
}


/*
    FIND A MEMBER OFFSET

    This routine finds the offset of the member id of the class type t.
    ns gives the namespace associated with t.  The member type is
    returned via pt.  id must denote a simple, non-virtual data member.
*/

OFFSET
offset_member(TYPE t, IDENTIFIER id, TYPE *pt, NAMESPACE ns, int adjust)
{
	if (!IS_NULL_nspace(ns)) {
		GRAPH gr;
		if (adjust) {
			remove_namespace();
			cache_lookup = old_cache_lookup;
		}
		gr = is_subfield(ns, id);
		if (!IS_NULL_graph(gr)) {
			IDENTIFIER fld = search_subfield(ns, gr, id);
			switch (TAG_id(fld)) {
			case id_member_tag: {
				/* Data members */
				TYPE s = DEREF_type(id_member_type(fld));
				OFFSET off = DEREF_off(id_member_off(fld));
				gr = DEREF_graph(id_member_base(fld));
				if (!IS_NULL_graph(gr)) {
					/* Check for virtual bases */
					DECL_SPEC acc =
					    DEREF_dspec(graph_access(gr));
					if (acc & dspec_mutable) {
						goto default_lab;
					}
				}
				use_id(fld, 0);
				*pt = s;
				return off;
			}
			case id_ambig_tag:
				/* Ambiguous members */
				IGNORE report_ambiguous(fld, 0, 1, 0);
				break;
			case id_undef_tag: {
				/* Undefined members */
				HASHID nm = DEREF_hashid(id_name(fld));
				report(crt_loc, ERR_lookup_qual_undef(nm, ns));
				break;
			}
			default:
default_lab: {
		     /* Other members */
		     ERROR err = ERR_expr_const_off_mem(fld);
		     err = concat_error(err, ERR_token_mem_off());
		     report(crt_loc, err);
		     break;
	     }
			}
		} else {
			/* id is not a member of ns */
			report(crt_loc, ERR_lookup_qual_bad(id, ns));
		}
	} else {
		if (!IS_type_error(t)) {
			/* t is not a class type */
			string key = find_vocab(lex_class);
			report(crt_loc, ERR_expr_ref_dot_op(t, key));
		}
		cache_lookup = old_cache_lookup;
	}
	*pt = type_error;
	return NULL_off;
}


/*
    FIND AN INDEX OFFSET

    This routine finds the offset of the eth member of the array type t.
    The member type is returned via pt.  e must denote an integer constant
    expression.
*/

OFFSET
offset_index(TYPE t, EXP e, TYPE *pt)
{
	if (IS_type_array(t)) {
		OFFSET off;
		ERROR err = NULL_err;
		TYPE s = DEREF_type(type_array_sub(t));
		IGNORE make_nat_exp(e, &err);
		if (!IS_NULL_err(err)) {
			err = concat_error(err, ERR_expr_const_off_dim());
			err = concat_error(err, ERR_token_mem_off());
			report(crt_loc, err);
		}
		check_bounds(lex_array_Hop, t, e);
		off = make_off_mult(s, e, 0);
		*pt = s;
		return off;
	}
	if (!IS_type_error(t)) {
		ERROR err = ERR_expr_const_off_array(t);
		err = concat_error(err, ERR_token_mem_off());
		report(crt_loc, err);
	}
	*pt = type_error;
	return NULL_off;
}


/*
    ADD TWO OFFSETS

    This routine adds the two offsets a and b, either of which may be
    null.
*/

OFFSET
offset_add(OFFSET a, OFFSET b)
{
	OFFSET off;
	if (is_zero_offset(a)) {
		return b;
	}
	if (is_zero_offset(b)) {
		return a;
	}
	MAKE_off_plus(a, b, off);
	return off;
}
