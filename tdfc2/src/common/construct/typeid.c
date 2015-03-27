/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/check.h>

#include <utility/config.h>
#include "c_types.h"

#include <utility/error.h>
#include <utility/catalog.h>
#include <utility/buffer.h>
#include <utility/ustring.h>
#include <utility/option.h>

#include <syntax/syntax.h>

#include <parse/preproc.h>
#include <parse/constant.h>
#include <parse/hash.h>
#include <parse/literal.h>

#include <output/bitstream.h>
#include <output/interface.h>
#include <output/tok.h>

#include <construct/access.h>
#include <construct/basetype.h>
#include <construct/cast.h>
#include <construct/check.h>
#include <construct/chktype.h>
#include <construct/class.h>
#include <construct/convert.h>
#include <construct/derive.h>
#include <construct/destroy.h>
#include <construct/exception.h>
#include <construct/expression.h>
#include <construct/identifier.h>
#include <construct/initialise.h>
#include <construct/namespace.h>
#include <construct/overload.h>
#include <construct/template.h>
#include <construct/token.h>
#include <construct/typeid.h>
#include <construct/link.h>

#include "ctype_ops.h"
#include "exp_ops.h"
#include "graph_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "type_ops.h"
#include "virt_ops.h"


/*
    These variables are used to hold the names of the various built-in
    class types.  They are defined here as the majority are concerned
    with run-time type information.
*/

static const char *std_name = "std";
static NAMESPACE std_namespace = NULL_nspace;


/*
    This routine returns the std namespace if this has been declared.
*/

static NAMESPACE
find_std_namespace(void)
{
	NAMESPACE ns = std_namespace;
	if (IS_NULL_nspace(ns)) {
		string s = ustrlit(std_name);
		if (s == NULL) {
			/* Use global namespace if std_name is not given */
			ns = global_namespace;
		} else {
			/* Look up 'std' in the global namespace */
			unsigned long h = hash(s);
			HASHID nm = lookup_name(s, h, 0, lex_identifier);
			MEMBER mem = search_member(global_namespace, nm, 0);
			IDENTIFIER id = type_member(mem, 2);
			if (!IS_NULL_id(id) && IS_id_nspace_name_etc(id)) {
				ns = DEREF_nspace(id_nspace_name_etc_defn(id));
			}
		}
		std_namespace = ns;
	}
	return ns;
}


/*
    This routine sets the std namespace according to the identifier id.
    The null identifier is used to indicate the global namespace.
*/

void
set_std_namespace(IDENTIFIER id)
{
	std_name = NULL;
	std_namespace = NULL_nspace;
	if (!IS_NULL_id(id)) {
		HASHID nm = DEREF_hashid(id_name(id));
		if (IS_hashid_name_etc(nm)) {
			string s = DEREF_string(hashid_name_etc_text(nm));
			std_name = strlit(s);
		}
	}
	IGNORE find_std_namespace();
	return;
}


/*
    This routine looks up the standard class named s in the std namespace.
    The null type is returned if the type has not been declared and, in
    addition, an error is reported if err is true.
*/

TYPE
find_std_type(const char *s, int type, int err)
{
	string us = ustrlit(s);
	unsigned long h = hash(us);
	HASHID nm = lookup_name(us, h, 0, lex_identifier);
	NAMESPACE ns = find_std_namespace();
	if (!IS_NULL_nspace(ns)) {
		IDENTIFIER id = search_id(ns, nm, 0, type);
		if (!IS_NULL_id(id) && IS_id_class_name_etc(id)) {
			TYPE t = DEREF_type(id_class_name_etc_defn(id));
			return t;
		}
	}
	if (err) {
		us = ustrlit(std_name);
		report(crt_loc, ERR_lib_builtin(us, nm));
	}
	return NULL_type;
}


/*
    The run-time type information routines are only included in the
    C++ producer.
*/

#if LANGUAGE_CPP


/*
    The variable type_info_ref represents the type 'const type_info &'
    returned by the typeid operation.  The variables type_bad_cast and
    type_bad_typeid represent the types 'bad_cast' and 'bad_typeid'
    thrown by the dynamic_cast and typeid operators.
*/

static TYPE type_info_ref = NULL_type;
static TYPE type_bad_cast = NULL_type;
static TYPE type_bad_typeid = NULL_type;


/*
    This routine returns the type of the typeid operator.  An internal
    error is reported if this has not been initialised.
*/

TYPE
get_type_info(int op, TYPE t, int err)
{
	TYPE r = NULL_type;
	if (op == lex_typeid) {
		r = type_info_ref;
		if (IS_NULL_type(r)) {
			r = find_std_type("type_info", 1, err);
			if (IS_NULL_type(r)) {
				if (err) {
					r = type_error;
				} else {
					CV_SPEC cv = (cv_lvalue | cv_const);
					MAKE_type_dummy(cv, TOK_typeid_type, r);
				}
			} else {
				/* Form 'lvalue const type_info' */
				r = qualify_type(r,(cv_lvalue | cv_const), 0);
				type_info_ref = r;
			}
		}
	} else {
		if (IS_type_compound(t)) {
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
			VIRTUAL vt = DEREF_virt(ctype_virt(ct));
			if (!IS_NULL_virt(vt)) {
				/* Form array of pointers to members */
				unsigned long m = DEREF_ulong(virt_no(vt));
				NAT n = make_nat_value(m + VIRTUAL_EXTRA);
				r = copy_typedef(NULL_id, type_func_void,
						 cv_none);
				MAKE_type_ptr_mem(cv_const, ct, r, r);
				MAKE_type_array(cv_lvalue, r, n, r);
			}
		} else {
			if (is_templ_type(t)) {
				r = t;
			}
		}
		if (IS_NULL_type(r)) {
			/* No virtual function table */
			report(crt_loc, ERR_expr_typeid_vtable(op));
		}
	}
	return r;
}


/*
    This routine returns an expression corresponding to throwing the
    'bad_cast' or 'bad_typeid' types (as indicated by s and pr).  An
    error is reported if this type has not been declared.
*/

static EXP
throw_bad_op(const char *s, TYPE *pr)
{
	EXP e;
	TYPE r = *pr;
	if (IS_NULL_type(r)) {
		r = find_std_type(s, 1, 1);
		if (IS_NULL_type(r)) {
			return NULL_exp;
		}
		*pr = r;
	}
	e = make_func_cast_exp(r, NULL_list(EXP));
	e = make_throw_exp(e, 0);
	return e;
}


/*
    This routine simplifies the typeid argument expression a according to
    the rule 'p [i]' -> '*p'.  Unfortunately '*( p + i )' which is otherwise
    identical to 'p [i]' is not treated in the same manner.  The result
    is the address of a.
*/

static EXP
typeid_arg(int op, EXP a)
{
	while (IS_exp_paren(a)) {
		/* Remove any brackets */
		a = DEREF_exp(exp_paren_arg(a));
	}
	if (IS_exp_indir(a)) {
		int i = DEREF_int(exp_indir_index(a));
		a = DEREF_exp(exp_indir_ptr(a));
		if (i && IS_exp_add_ptr(a)) {
			OFFSET off = DEREF_off(exp_add_ptr_off(a));
			if (!is_const_offset(off, 2, 0)) {
				report(crt_loc, ERR_expr_typeid_index(op));
			}
			a = DEREF_exp(exp_add_ptr_ptr(a));
		}
	} else {
		TYPE t = DEREF_type(exp_type(a));
		MAKE_type_ptr(cv_none, t, t);
		MAKE_exp_address(t, a, a);
	}
	return a;
}


/*
    This routine constructs the type identification expression 'op ( a )'
    for an expression a.  n gives the number of side effects in a.  Note
    that suppress_usage is true during the evaluation of a and in this
    routine.  If it turns out that the expression is used (because it is
    an lvalue of polymorphic type) then mark_used needs to be called
    to mark any variable uses which have been missed.
*/

EXP
make_typeid_exp(int op, EXP a, int n)
{
	EXP e;
	TYPE t;
	CV_SPEC cv;
	a = convert_reference(a, REF_NORMAL);
	a = convert_none(a);
	a = convert_bitfield(a);
	t = DEREF_type(exp_type(a));
	if (is_templ_type(t)) {
		/* Allow for template types */
		TYPE r = get_type_info(op, t, 1);
		MAKE_exp_op(r, op, a, NULL_exp, e);
		return e;
	}
	cv = DEREF_cv(type_qual(t));
	if ((cv & cv_lvalue) && IS_type_compound(t)) {
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
		if (ci & cinfo_polymorphic) {
			/* lvalue of polymorphic type */
			TYPE r = get_type_info(op, t, 1);
			int use = suppress_usage;
			if (use) {
				suppress_usage--;
			}
			a = typeid_arg(op, a);
			mark_used(a);
			if (know_type(a)!= 1) {
				/* Can throw 'bad_typeid' */
				EXP b = throw_bad_op("bad_typeid",
						     &type_bad_typeid);
				t = DEREF_type(exp_type(a));
				MAKE_exp_dummy(t, a, LINK_NONE, NULL_off, 1, a);
				MAKE_exp_rtti(r, a, b, op, e);
				suppress_usage = use;
				return e;
			}
			suppress_usage = use;
		}
	}
	if (n) {
		report(crt_loc, ERR_expr_typeid_side(op));
	}
	free_exp(a, 2);
	e = make_typeid_type(op, t, 0);
	return e;
}


/*
    This routine constructs the type identification expression 'op ( t )'
    for a type t.  The argument n gives the number of types defined in t.
*/

EXP
make_typeid_type(int op, TYPE t, int n)
{
	EXP e;
	TYPE r;
	if (n) {
		report(crt_loc, ERR_expr_typeid_typedef(op));
	}
	if (IS_type_ref(t)) {
		/* Remove reference component */
		t = DEREF_type(type_ref_sub(t));
	}
	if (IS_type_compound(t)) {
		/* Check for incomplete class types */
		ERROR err = check_incomplete(t);
		if (!IS_NULL_err(err)) {
			err = concat_error(err, ERR_expr_typeid_incompl(op));
			report(crt_loc, err);
		}
	}
	t = qualify_type(t, cv_none, 0);
	r = get_type_info(op, t, 1);
	MAKE_exp_rtti_type(r, t, op, e);
	return e;
}


/*
    This routine constructs a template dependent dynamic cast of the
    expression a to the type t.
*/

static EXP
dynamic_cast_templ(TYPE t, EXP a)
{
	EXP e;
	MAKE_exp_op(t, lex_dynamic_Hcast, a, NULL_exp, e);
	return e;
}


/*
    This routine constructs the expression 'dynamic_cast < t > ( a )'.
    The argument n gives the number of types defined in t.
*/

EXP
make_dynamic_cast_exp(TYPE t, EXP a, int n)
{
	TYPE s;
	CV_SPEC cv;
	int ok = 1;
	int ptr = 0;
	unsigned qual;
	EXP e = NULL_exp;
	TYPE p = NULL_type;
	ERROR err = NULL_err;
	CLASS_TYPE ct = NULL_ctype;
	CLASS_TYPE cs = NULL_ctype;

	/* Can't define types */
	if (n) {
		report(crt_loc, ERR_expr_cast_dynam_typedef());
	}

	/* Do reference conversion */
	a = convert_reference(a, REF_NORMAL);
	s = DEREF_type(exp_type(a));
	cv = DEREF_cv(type_qual(s));

	/* Check target type */
	if (IS_type_token(t)) {
		if (is_templ_type(t)) {
			e = dynamic_cast_templ(t, a);
			return e;
		}
		t = expand_type(t, 1);
	}
	if (IS_type_ptr(t)) {
		/* Pointer types */
		p = DEREF_type(type_ptr_sub(t));
		if (IS_type_token(p)) {
			if (is_templ_type(p)) {
				e = dynamic_cast_templ(t, a);
				return e;
			}
			p = expand_type(p, 1);
		}
		if (IS_type_top_etc(p)) {
			/* 'void *' allowed */
			ptr = 2;
		} else if (IS_type_compound(p)) {
			ct = DEREF_ctype(type_compound_defn(p));
			err = check_incomplete(p);
			if (!IS_NULL_err(err)) {
				ok = 0;
			}
			ptr = 1;
		} else {
			ok = 0;
		}
	} else if (IS_type_ref(t)) {
		p = DEREF_type(type_ref_sub(t));
		if (IS_type_token(p)) {
			if (is_templ_type(p)) {
				e = dynamic_cast_templ(t, a);
				return e;
			}
			p = expand_type(p, 1);
		}
		if (IS_type_compound(p)) {
			ct = DEREF_ctype(type_compound_defn(p));
			err = check_incomplete(p);
			if (!IS_NULL_err(err)) {
				ok = 0;
			}
		} else {
			ok = 0;
		}
	} else {
		ok = 0;
	}
	if (!ok) {
		/* Invalid target type */
		IGNORE convert_lvalue(e);
		err = concat_error(err, ERR_expr_cast_dynam_type(t));
		report(crt_loc, err);
		e = make_error_exp(0);
		return e;
	}

	/* Check operand type */
	if (is_templ_type(s)) {
		e = dynamic_cast_templ(t, a);
		return e;
	}
	if (ptr) {
		if (cv & cv_lvalue) {
			a = convert_lvalue(a);
		}
		if (IS_type_token(s)) {
			s = expand_type(s, 1);
		}
		if (IS_type_ptr(s)) {
			/* Argument must be a pointer */
			TYPE q = DEREF_type(type_ptr_sub(s));
			if (IS_type_token(q)) {
				if (is_templ_type(q)) {
					e = dynamic_cast_templ(t, a);
					return e;
				}
				q = expand_type(q, 1);
			}
			if (IS_type_compound(q)) {
				cs = DEREF_ctype(type_compound_defn(q));
				err = check_incomplete(q);
				if (!IS_NULL_err(err)) {
					ok = 0;
				}
			} else {
				ok = 0;
			}
		} else {
			ok = 0;
		}
		if (!ok) {
			err = concat_error(err, ERR_expr_cast_dynam_ptr(s));
			report(crt_loc, err);
			e = make_error_exp(0);
			return e;
		}
	} else {
		/* Reference types */
		if (cv & cv_lvalue) {
			/* Argument must be an lvalue */
			if (IS_type_token(s)) {
				s = expand_type(s, 1);
			}
			if (IS_type_compound(s)) {
				cs = DEREF_ctype(type_compound_defn(s));
				err = check_incomplete(s);
				if (!IS_NULL_err(err)) {
					ok = 0;
				}
			} else {
				ok = 0;
			}
		} else {
			err = ERR_basic_lval_not();
			ok = 0;
		}
		if (!ok) {
			err = concat_error(err, ERR_expr_cast_dynam_ref(s));
			report(crt_loc, err);
			e = make_error_exp(1);
			return e;
		}

		/* Convert to pointers */
		t = rvalue_type(p);
		MAKE_type_ptr(cv_none, t, t);
		s = rvalue_type(s);
		MAKE_type_ptr(cv_none, s, s);
		MAKE_exp_address(s, a, a);
	}

	/* Check for qualification conversions */
	qual = check_qualifier(t, s, 0);
	if (qual == QUAL_OK) {
		/* Exact match */
		e = a;
	} else {
		if (IS_exp_null(a)) {
			/* Null pointer conversion */
			e = make_null_exp(t);
		} else if (qual & QUAL_SIMILAR) {
			/* Qualification conversion */
			MAKE_exp_cast(t, CONV_QUAL, a, e);
		} else {
			/* Check for base class conversions */
			if (ptr != 2) {
				GRAPH gr = find_base_class(cs, ct, 1);
				if (!IS_NULL_graph(gr)) {
					/* Base class conversion */
					OFFSET off;
					err = check_ambig_base(gr);
					if (!IS_NULL_err(err)) {
						ERROR err2 =
						    ERR_conv_ptr_ambiguous();
						err = concat_error(err, err2);
						err2 = ERR_expr_cast_dynam_bad();
						err = concat_error(err, err2);
						report(crt_loc, err);
					}
					check_base_access(gr);
					off = DEREF_off(graph_off(gr));
					e = make_base_cast(t, a, off);
				}
			}

			/* Otherwise cs must be polymorphic */
			if (IS_NULL_exp(e)) {
				CLASS_INFO ci = DEREF_cinfo(ctype_info(cs));
				if (ci & cinfo_polymorphic) {
					if (ptr == 2) {
						/* Conversion to 'void *' */
						MAKE_exp_cast(t, CONV_PTR_VOID,
							      a, e);
					} else {
						/* Dynamic cast */
						EXP b = NULL_exp;
						if (ptr == 0) {
							/* Can throw 'bad_cast'
							 * for references */
							b = throw_bad_op("bad_cast", &type_bad_cast);
						}
						MAKE_exp_dummy(s, a, LINK_NONE,
							       NULL_off, 0, a);
						MAKE_exp_dyn_cast(t, a, b, e);
					}
				} else {
					err = ERR_expr_cast_dynam_poly(cs);
					report(crt_loc, err);
					e = make_error_exp(0);
					return e;
				}
			}
		}

		/* Check for casting away const-ness */
		if (qual != QUAL_OK) {
			err = NULL_err;
			cast_away_const(qual, &err, CAST_DYNAMIC);
			if (!IS_NULL_err(err)) {
				err = concat_error(err,
						   ERR_expr_cast_dynam_bad());
				report(crt_loc, err);
			}
		}
	}
	if (ptr == 0) {
		/* Take indirection for references */
		MAKE_exp_indir(p, e, e);
	}
	return e;
}


#endif /* LANGUAGE_CPP */
