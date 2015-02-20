/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdio.h>

#include "config.h"
#include "c_types.h"

#include "ctype_ops.h"
#include "etype_ops.h"
#include "ftype_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "inst_ops.h"
#include "itype_ops.h"
#include "tok_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "option.h"
#include "basetype.h"
#include "check.h"
#include "chktype.h"
#include "class.h"
#include "constant.h"
#include "convert.h"
#include "function.h"
#include "instance.h"
#include "inttype.h"
#include "literal.h"
#include "merge.h"
#include "namespace.h"
#include "predict.h"
#include "printf.h"
#include "template.h"
#include "tok.h"
#include "tokdef.h"
#include "token.h"


/*
    This routine finds the tag of the type t, ignoring any template
    qualifiers.
*/

unsigned
type_tag(TYPE t)
{
	if (!IS_NULL_type(t)) {
		unsigned tag = TAG_type(t);
		if (tag == type_templ_tag) {
			TYPE s = DEREF_type(type_templ_defn(t));
			tag = type_tag(s);
		}
		return tag;
	}
	return null_tag;
}


/*
    This routine returns the type category associated with the type pointed
    to by pt.  If this is a reference type then the result is the category
    of the referenced type (which is always an lvalue).  If it is a tokenised
    type then the token is expanded and returned via pt.
*/

unsigned
type_category(TYPE *pt)
{
	TYPE t = *pt;
	unsigned res = CTYPE_NONE;
	if (!IS_NULL_type(t)) {
		CV_SPEC qual = DEREF_cv(type_qual(t));
		switch (TAG_type(t)) {
		case type_integer_tag:   res = CTYPE_INTEGER; break;
		case type_floating_tag:  res = CTYPE_FLOAT;   break;
		case type_top_tag:       res = CTYPE_VOID;    break;
		case type_bottom_tag:    res = CTYPE_VOID;    break;
		case type_ptr_tag:       res = CTYPE_PTR;     break;
		case type_ptr_mem_tag:   res = CTYPE_PTR_MEM; break;
		case type_bitfield_tag:  res = CTYPE_BITF;    break;
		case type_compound_tag:  res = CTYPE_CLASS;   break;
		case type_enumerate_tag: res = CTYPE_ENUM;    break;
		case type_error_tag:     res = CTYPE_ERROR;   break;

		case type_func_tag:
		case type_array_tag: {
			/* Allow for lvalue conversions */
			if (qual & cv_lvalue) {
				res = CTYPE_PTR;
			}
			break;
		}

		case type_ref_tag: {
			/* Deal with reference types */
			TYPE r = DEREF_type(type_ref_sub(t));
			TYPE s = r;
			res = type_category(&r);
			if (!EQ_type(r, s)) {
				MAKE_type_ref(qual, r, r);
				*pt = r;
			}
			break;
		}

		case type_token_tag: {
			/* Deal with tokenised types */
			IDENTIFIER id = DEREF_id(type_token_tok(t));
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			if (ds & dspec_temp) {
				/* Check for recursive tokens */
				report(crt_loc, ERR_token_recursive(id));
			} else {
				/* Expand token definition */
				TYPE r = expand_type(t, 0);
				if (!EQ_type(r, t)) {
					COPY_dspec(id_storage(id),
						   (ds | dspec_temp));
					res = type_category(&r);
					COPY_dspec(id_storage(id), ds);
					*pt = r;
				} else {
					if (is_templ_param(id) &&
					    in_template_decl) {
						res |= CTYPE_TEMPL;
					}
				}
			}
			res |= CTYPE_TOKEN;
			break;
		}
		}
		if (qual & cv_lvalue) {
			res |= CTYPE_LVALUE;
		}
	}
	return res;
}


/*
    This routine checks whether the integral types s and t are equal.
*/

int
eq_itype(INT_TYPE s, INT_TYPE t)
{
	int eq = 0;
	unsigned ns, nt;
	if (EQ_itype(s, t)) {
		return 1;
	}
	if (IS_NULL_itype(s)) {
		return 0;
	}
	if (IS_NULL_itype(t)) {
		return 0;
	}
	s = expand_itype(s);
	t = expand_itype(t);
	if (EQ_itype(s, t)) {
		return 1;
	}
	ns = TAG_itype(s);
	nt = TAG_itype(t);
	if (ns == nt) {
		assert(ORDER_itype == 6);
		switch (ns) {
		case itype_basic_tag: {
			/* Built-in types */
			BUILTIN_TYPE bs = DEREF_ntype(itype_basic_no(s));
			BUILTIN_TYPE bt = DEREF_ntype(itype_basic_no(t));
			if (bs == bt) {
				eq = 1;
			}
			break;
		}
		case itype_bitfield_tag: {
			/* Bitfield types */
			BASE_TYPE bs = DEREF_btype(itype_bitfield_rep(s));
			BASE_TYPE bt = DEREF_btype(itype_bitfield_rep(t));
			if (bs == bt) {
				NAT ms = DEREF_nat(itype_bitfield_size(s));
				NAT mt = DEREF_nat(itype_bitfield_size(t));
				if (EQ_nat(ms, mt) || eq_nat(ms, mt)) {
					TYPE ps =
					    DEREF_type(itype_bitfield_sub(s));
					TYPE pt =
					    DEREF_type(itype_bitfield_sub(t));
					eq = eq_type(ps, pt);
				}
			}
			break;
		}
		case itype_promote_tag: {
			/* Promotion types */
			s = DEREF_itype(itype_promote_arg(s));
			t = DEREF_itype(itype_promote_arg(t));
			eq = eq_itype(s, t);
			break;
		}
		case itype_arith_tag: {
			/* Arithmetic types */
			INT_TYPE s1 = DEREF_itype(itype_arith_arg1(s));
			INT_TYPE s2 = DEREF_itype(itype_arith_arg2(s));
			INT_TYPE t1 = DEREF_itype(itype_arith_arg1(t));
			INT_TYPE t2 = DEREF_itype(itype_arith_arg2(t));
			if (eq_itype(s1, t1)) {
				eq = eq_itype(s2, t2);
			} else if (eq_itype(s1, t2)) {
				eq = eq_itype(s2, t1);
			}
			break;
		}
		case itype_literal_tag: {
			/* Literal types */
			int bs = DEREF_int(itype_literal_spec(s));
			int bt = DEREF_int(itype_literal_spec(t));
			IDENTIFIER is = DEREF_id(itype_literal_tok(s));
			IDENTIFIER it = DEREF_id(itype_literal_tok(t));
			NAT ms = DEREF_nat(itype_literal_nat(s));
			NAT mt = DEREF_nat(itype_literal_nat(t));
			if (bs == bt && EQ_id(is, it) && eq_nat(ms, mt)) {
				eq = 1;
			}
			break;
		}
		case itype_token_tag: {
			/* Token applications */
			IDENTIFIER is = DEREF_id(itype_token_tok(s));
			IDENTIFIER it = DEREF_id(itype_token_tok(t));
			LIST(TOKEN)ps = DEREF_list(itype_token_args(s));
			LIST(TOKEN)pt = DEREF_list(itype_token_args(t));
			eq = eq_token_args(is, it, ps, pt);
			break;
		}
		}
	}
	return eq;
}


/*
    This routine checks whether the floating point types s and t are equal.
*/

int
eq_ftype(FLOAT_TYPE s, FLOAT_TYPE t)
{
	int eq = 0;
	unsigned ns, nt;
	if (EQ_ftype(s, t)) {
		return 1;
	}
	if (IS_NULL_ftype(s)) {
		return 0;
	}
	if (IS_NULL_ftype(t)) {
		return 0;
	}
	ns = TAG_ftype(s);
	nt = TAG_ftype(t);
	if (ns == nt) {
		assert(ORDER_ftype == 4);
		switch (ns) {
		case ftype_basic_tag: {
			/* Built-in types */
			BUILTIN_TYPE bs = DEREF_ntype(ftype_basic_no(s));
			BUILTIN_TYPE bt = DEREF_ntype(ftype_basic_no(t));
			if (bs == bt) {
				eq = 1;
			}
			break;
		}
		case ftype_arg_promote_tag: {
			/* Argument promotion types */
			FLOAT_TYPE s1 = DEREF_ftype(ftype_arg_promote_arg(s));
			FLOAT_TYPE t1 = DEREF_ftype(ftype_arg_promote_arg(t));
			eq = eq_ftype(s1, t1);
			break;
		}
		case ftype_arith_tag: {
			/* Arithmetic types */
			FLOAT_TYPE s1 = DEREF_ftype(ftype_arith_arg1(s));
			FLOAT_TYPE s2 = DEREF_ftype(ftype_arith_arg2(s));
			FLOAT_TYPE t1 = DEREF_ftype(ftype_arith_arg1(t));
			FLOAT_TYPE t2 = DEREF_ftype(ftype_arith_arg2(t));
			if (eq_ftype(s1, t1)) {
				eq = eq_ftype(s2, t2);
			} else if (eq_ftype(s1, t2)) {
				eq = eq_ftype(s2, t1);
			}
			break;
		}
		case ftype_token_tag: {
			/* Token applications */
			IDENTIFIER is = DEREF_id(ftype_token_tok(s));
			IDENTIFIER it = DEREF_id(ftype_token_tok(t));
			LIST(TOKEN)ps = DEREF_list(ftype_token_args(s));
			LIST(TOKEN)pt = DEREF_list(ftype_token_args(t));
			eq = eq_token_args(is, it, ps, pt);
			break;
		}
		}
	}
	return eq;
}


/*
    This routine finds the cv-qualifier for the type t.  In most cases this
    is trivial, but for arrays the qualifier is that of the subtype.
*/

CV_SPEC
find_cv_qual(TYPE t)
{
	CV_SPEC qt = DEREF_cv(type_qual(t));
	while (IS_type_array(t)) {
		CV_SPEC qs;
		t = DEREF_type(type_array_sub(t));
		qs = DEREF_cv(type_qual(t));
		qt |= qs;
	}
	return qt;
}


/*
    This routine returns cv_none if the type s is more cv-qualified than the
    type t.  That is to say, if t is const then so is s, and if t is volatile
    then so is s.  Otherwise it returns those cv-qualifiers for which s
    fails to be more qualified than t.
*/

CV_SPEC
cv_compare(TYPE s, TYPE t)
{
	CV_SPEC qs = find_cv_qual(s);
	CV_SPEC qt = find_cv_qual(t);
	qs &= cv_qual;
	qt &= cv_qual;
	return qt & ~qs;
}


/*
    This routine compares the function linkage specifiers for the function
    types s and t.
*/

static int
eq_func_lang(TYPE s, TYPE t)
{
	CV_SPEC qs = DEREF_cv(type_func_mqual(s));
	CV_SPEC qt = DEREF_cv(type_func_mqual(t));
	if (qs != qt) {
		CV_SPEC ps = (qs & cv_language);
		CV_SPEC pt = (qt & cv_language);
		if (ps != pt) {
			if (ps == cv_none) {
				if (force_tokdef) {
					ps = pt;
					COPY_cv(type_func_mqual(s), (qs | ps));
				} else {
					ps = cv_lang;
				}
			}
			if (pt == cv_none) {
				if (force_tokdef) {
					pt = ps;
					COPY_cv(type_func_mqual(t), (qt | pt));
				} else {
					pt = cv_lang;
				}
			}
			if (ps != pt) {
				return 0;
			}
		}
	}
	return 1;
}


/*
    This routine checks whether the function types s and t are equal.
    Member function qualifiers are only considered if mq is true.
    If rf is true then any parameter of type 'X' is considered to match
    one of type 'X &'.  The routine returns 3 if the types are precisely
    equal, 2 if they differ only in the linkage specifier, 1 if they
    differ only in the return type or in one of these reference
    equalities, and 0 otherwise.
*/

int
eq_func_type(TYPE s, TYPE t, int mq, int rf)
{
	int eq = 3;
	int es, et;
	unsigned ns, nt;
	LIST(TYPE)ls, lt;

	/* Check for obvious equality */
	if (EQ_type(s, t)) {
		return 3;
	}
	ns = TAG_type(s);
	nt = TAG_type(t);
	if (ns != type_func_tag || nt != type_func_tag) {
		if (ns == type_templ_tag && nt == type_templ_tag) {
			/* Allow for template functions */
			eq = eq_template(s, t, 1, mq, rf);
			return eq;
		} else {
			/* Otherwise just check type equality */
			eq = eq_type(s, t);
			if (eq == 1) {
				return 3;
			}
			return 0;
		}
	}

	/* Check number of parameters */
	es = DEREF_int(type_func_ellipsis(s));
	et = DEREF_int(type_func_ellipsis(t));
	ls = DEREF_list(type_func_ptypes(s));
	lt = DEREF_list(type_func_ptypes(t));
	if (es != et || LENGTH_list(ls)!= LENGTH_list(lt)) {
		return 0;
	}

	/* Check parameter types */
	while (!IS_NULL_list(ls)) {
		/* Check next parameter */
		TYPE as = DEREF_type(HEAD_list(ls));
		TYPE at = DEREF_type(HEAD_list(lt));
		if (es & FUNC_PARAMS) {
			/* Compare unpromoted types */
			as = unpromote_type(as);
			at = unpromote_type(at);
		}
		if (rf) {
			/* Allow for references */
			if (IS_type_ref(as)) {
				if (!IS_type_ref(at)) {
					as = DEREF_type(type_ref_sub(as));
					eq = 1;
				}
			} else if (IS_type_ref(at)) {
				at = DEREF_type(type_ref_sub(at));
				eq = 1;
			}
		}
		if (eq_type(as, at) != 1) {
			return 0;
		}
		if (force_tokdef) {
			/* Preserve printf and scanf types */
			if (is_printf_type(as)) {
				IDENTIFIER id = DEREF_id(type_name(as));
				COPY_id(type_name(at), id);
			} else if (is_printf_type(at)) {
				IDENTIFIER id = DEREF_id(type_name(at));
				COPY_id(type_name(as), id);
			}
		}
		ls = TAIL_list(ls);
		lt = TAIL_list(lt);
	}

	/* Check return type */
	if (eq == 3) {
		TYPE rs = DEREF_type(type_func_ret(s));
		TYPE rt = DEREF_type(type_func_ret(t));
		if (eq_type(rt, rs)!= 1) {
			if (IS_type_top_etc(rs)) {
				/* Check for 'void' and 'bottom' */
				TYPE r = type_composite(rs, rt, 0, 1, KILL_err,
							0);
				if (IS_NULL_type(r)) {
					eq = 1;
				}
			} else {
				eq = 1;
			}
		}
	}

	/* Check member qualifiers */
	if (eq) {
		CV_SPEC qs = DEREF_cv(type_func_mqual(s));
		CV_SPEC qt = DEREF_cv(type_func_mqual(t));
		if (qs != qt) {
			if (mq && (qs & cv_qual)!= (qt & cv_qual)) {
				eq = 0;
			} else if (!eq_func_lang(s, t)) {
				/* Linkage specifiers don't match */
				if (eq == 3 && option(OPT_func_linkage)) {
					eq = 2;
				}
			}
		}
	}
	return eq;
}


/*
    This routine checks whether the instance s of a nested class or
    enumeration type of a template class equals the type tid.
*/

static int
eq_instance(TYPE s, IDENTIFIER tid)
{
	if (IS_type_instance(s)) {
		IDENTIFIER sid = DEREF_id(type_instance_id(s));
		if (EQ_id(sid, tid)) {
			CLASS_TYPE cs, ct;
			sid = DEREF_id(type_name(s));
			if (EQ_id(sid, tid)) {
				return 1;
			}
			cs = parent_class(sid);
			ct = parent_class(tid);
			if (IS_NULL_ctype(cs)) {
				return 0;
			}
			if (IS_NULL_ctype(ct)) {
				return 0;
			}
			return eq_ctype(cs, ct);
		}
	}
	return 0;
}


/*
    This routine checks for equality of the class types cs and ct.
*/

int
eq_ctype(CLASS_TYPE cs, CLASS_TYPE ct)
{
	if (EQ_ctype(cs, ct)) {
		/* Simple class equality */
		return 1;
	}
	if (!IS_NULL_ctype(cs) && !IS_NULL_ctype(ct)) {
		TYPE s = DEREF_type(ctype_form(cs));
		TYPE t = DEREF_type(ctype_form(ct));
		if (!IS_NULL_type(s) || !IS_NULL_type(t)) {
			/* Allow for template classes */
			unsigned ns, nt;
			if (IS_NULL_type(s)) {
				s = make_class_type(cs);
			}
			if (IS_NULL_type(t)) {
				t = make_class_type(ct);
			}
			ns = TAG_type(s);
			nt = TAG_type(t);
			if (ns != nt) {
				if (ns == type_instance_tag) {
					IDENTIFIER tid =
					    DEREF_id(ctype_name(ct));
					if (eq_instance(s, tid)) {
						return 1;
					}
				}
				if (nt == type_instance_tag) {
					IDENTIFIER sid =
					    DEREF_id(ctype_name(cs));
					if (eq_instance(t, sid)) {
						return 1;
					}
				}
			}
			return eq_type(s, t);
		}
		if (force_merge) {
			/* Allow for merging of type names */
			IDENTIFIER sid = DEREF_id(ctype_name(cs));
			IDENTIFIER tid = DEREF_id(ctype_name(ct));
			return merge_type(sid, tid);
		}
	}
	return 0;
}


/*
    This routine checks for equality of the enumeration types es and et.
*/

int
eq_etype(ENUM_TYPE es, ENUM_TYPE et)
{
	if (EQ_etype(es, et)) {
		/* Simple equality */
		return 1;
	}
	if (!IS_NULL_etype(es) && !IS_NULL_etype(et)) {
		TYPE s = DEREF_type(etype_form(es));
		TYPE t = DEREF_type(etype_form(et));
		if (!IS_NULL_type(s) && !IS_NULL_type(t)) {
			return eq_type(s, t);
		}
		if (!IS_NULL_type(s)) {
			IDENTIFIER tid = DEREF_id(etype_name(et));
			return eq_instance(s, tid);
		}
		if (!IS_NULL_type(t)) {
			IDENTIFIER sid = DEREF_id(etype_name(es));
			return eq_instance(t, sid);
		}
		if (force_merge) {
			/* Allow for merging of type names */
			IDENTIFIER sid = DEREF_id(etype_name(es));
			IDENTIFIER tid = DEREF_id(etype_name(et));
			return merge_type(sid, tid);
		}
	}
	return 0;
}


/*
    This is an auxiliary routine used by eq_type_qual which checks the
    types s and t for equality ignoring qualifiers according to the
    value of qu.  If either s or t is a template type and force_template
    is true then 1 is returned if the types are precisely equal, 2 is
    returned if t is a specialisation of s, 3 if s is a specialisation
    of t, 4 if each is a specialisation of the other (but they are not
    equal) and 0 otherwise.
*/

static int
eq_type_aux(TYPE s, TYPE t, int qu)
{
	/* Check for obvious equality */
	unsigned ns, nt;
	if (EQ_type(s, t)) {
		return 1;
	}
	if (IS_NULL_type(s)) {
		return 0;
	}
	if (IS_NULL_type(t)) {
		return 0;
	}

	/* Tags should be equal */
	ns = TAG_type(s);
	nt = TAG_type(t);
	if (ns != nt) {
		if (ns == type_templ_tag && force_template) {
			/* Allow for template types */
			if (deduce_template(s, t, qu)) {
				return 2;
			}
		}
		if (nt == type_templ_tag && force_template) {
			/* Allow for template types */
			if (deduce_template(t, s, qu)) {
				return 3;
			}
		}
		return 0;
	}

	/* Qualifiers should be equal */
	if (qu == 0) {
		CV_SPEC qs = DEREF_cv(type_qual(s));
		CV_SPEC qt = DEREF_cv(type_qual(t));
		if (qs != qt) {
			/* Try again allowing for lvalues */
			qs &= cv_qual;
			qt &= cv_qual;
			if (qs != qt) {
				return 0;
			}
		}
	}

	/* Check on type components */
	assert(ORDER_type == 18);
	switch (ns) {

	case type_integer_tag: {
		/* Check integer types */
		INT_TYPE is = DEREF_itype(type_integer_rep(s));
		INT_TYPE it = DEREF_itype(type_integer_rep(t));
		if (EQ_itype(is, it)) {
			return 1;
		}
		return eq_itype(is, it);
	}

	case type_floating_tag: {
		/* Check floating types */
		FLOAT_TYPE fs = DEREF_ftype(type_floating_rep(s));
		FLOAT_TYPE ft = DEREF_ftype(type_floating_rep(t));
		if (EQ_ftype(fs, ft)) {
			return 1;
		}
		return eq_ftype(fs, ft);
	}

	case type_ptr_tag: {
		/* Check pointer sub-types */
		s = DEREF_type(type_ptr_sub(s));
		t = DEREF_type(type_ptr_sub(t));
		if (qu == 1) {
			qu = 0;
		}
		return eq_type_qual(s, t, qu);
	}

	case type_ref_tag: {
		/* Check reference sub-types */
		s = DEREF_type(type_ref_sub(s));
		t = DEREF_type(type_ref_sub(t));
		return eq_type_qual(s, t, qu);
	}

#if LANGUAGE_CPP
	case type_ptr_mem_tag: {
		/* Check pointer to member class types */
		CLASS_TYPE cs = DEREF_ctype(type_ptr_mem_of(s));
		CLASS_TYPE ct = DEREF_ctype(type_ptr_mem_of(t));
		if (!eq_ctype(cs, ct)) {
			return 0;
		}

		/* Check pointer to member sub-types */
		s = DEREF_type(type_ptr_mem_sub(s));
		t = DEREF_type(type_ptr_mem_sub(t));
		if (qu == 1) {
			qu = 0;
		}
		return eq_type_qual(s, t, qu);
	}
#endif

	case type_func_tag: {
		/* Check function types */
		int ret = eq_func_type(s, t, 1, 0);
		if (ret == 3) {
			return 1;
		}
		return 0;
	}

	case type_array_tag: {
		/* Check array bounds */
		NAT ms = DEREF_nat(type_array_size(s));
		NAT mt = DEREF_nat(type_array_size(t));
		if (!EQ_nat(ms, mt) && !eq_nat(ms, mt)) {
			return 0;
		}

		/* Check array sub-types */
		s = DEREF_type(type_array_sub(s));
		t = DEREF_type(type_array_sub(t));
		return eq_type_qual(s, t, qu);
	}

	case type_bitfield_tag: {
		/* Check bitfield types */
		INT_TYPE bs = DEREF_itype(type_bitfield_defn(s));
		INT_TYPE bt = DEREF_itype(type_bitfield_defn(t));
		return eq_itype(bs, bt);
	}

	case type_compound_tag: {
		/* Check class definitions */
		CLASS_TYPE cs = DEREF_ctype(type_compound_defn(s));
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		return eq_ctype(cs, ct);
	}

	case type_enumerate_tag: {
		/* Check enumeration definitions */
		ENUM_TYPE es = DEREF_etype(type_enumerate_defn(s));
		ENUM_TYPE et = DEREF_etype(type_enumerate_defn(t));
		return eq_etype(es, et);
	}

	case type_token_tag: {
		/* Check token applications */
		IDENTIFIER is, it;
		LIST(TOKEN)ps, pt;
		INSTANCE as = DEREF_inst(type_token_app(s));
		INSTANCE at = DEREF_inst(type_token_app(t));
		if (!IS_NULL_inst(as) && !IS_NULL_inst(at)) {
			/* Check for equality of template instances */
			if (EQ_inst(as, at)) {
				return 1;
			}
			as = DEREF_inst(inst_alias(as));
			at = DEREF_inst(inst_alias(at));
			if (EQ_inst(as, at)) {
				return 1;
			}
		}
		is = DEREF_id(type_token_tok(s));
		it = DEREF_id(type_token_tok(t));
		ps = DEREF_list(type_token_args(s));
		pt = DEREF_list(type_token_args(t));
		return eq_token_args(is, it, ps, pt);
	}

	case type_templ_tag: {
		int ret = eq_template(s, t, 1, 1, 0);
		if (ret == 3) {
			/* Precise template equality */
			return 1;
		}
		if (force_template) {
			/* Check for template specialisations */
			int ds, dt;
			TYPE ps = DEREF_type(type_templ_defn(s));
			TYPE pt = DEREF_type(type_templ_defn(t));
			if (qu == 1) {
				qu = 0;
			}
			ds = deduce_template(s, pt, qu);
			dt = deduce_template(t, ps, qu);
			if (ds) {
				return dt ? 4 : 2;
			}
			if (dt) {
				return 3;
			}
		}
		return 0;
	}

	case type_pre_tag: {
		/* Check pre-types */
		BASE_TYPE bs = DEREF_btype(type_pre_rep(s));
		BASE_TYPE bt = DEREF_btype(type_pre_rep(t));
		IDENTIFIER is = DEREF_id(type_name(s));
		IDENTIFIER it = DEREF_id(type_name(t));
		if (!IS_NULL_id(is)) {
			is = DEREF_id(id_alias(is));
		}
		if (!IS_NULL_id(it)) {
			it = DEREF_id(id_alias(it));
		}
		return bs == bt && EQ_id(is, it);
	}

	case type_instance_tag: {
		/* Check instance types */
		IDENTIFIER is = DEREF_id(type_instance_id(s));
		IDENTIFIER it = DEREF_id(type_instance_id(t));
		if (EQ_id(is, it)) {
			/* Derived from same member */
			CLASS_TYPE cs, ct;
			is = DEREF_id(type_name(s));
			it = DEREF_id(type_name(t));
			if (EQ_id(is, it)) {
				return 1;
			}
			cs = parent_class(is);
			ct = parent_class(it);
			if (IS_NULL_ctype(cs)) {
				return 0;
			}
			if (IS_NULL_ctype(ct)) {
				return 0;
			}
			return eq_ctype(cs, ct);
		}
		return 0;
	}

	case type_dummy_tag: {
		/* Check dummy types */
		int is = DEREF_int(type_dummy_tok(s));
		int it = DEREF_int(type_dummy_tok(t));
		return is == it;
	}
	}
	/* Simple types compare equal */
	return 1;
}


/*
    This routine unifies the types s and t by defining tokens if necessary.
    cv gives the type qualifiers which are in t but not in s.  It returns
    true if a value is assigned to a token.
*/

int
unify_type(TYPE s, TYPE t, CV_SPEC cv, int qual)
{
	IDENTIFIER id;
	LIST(TOKEN)args;
	unsigned tag = TAG_type(s);
	switch (tag) {
	case type_integer_tag: {
		/* Integral types */
		INT_TYPE is = DEREF_itype(type_integer_rep(s));
		switch (TAG_itype(is)) {
		case itype_basic_tag: {
			/* Built-in integral types */
			BUILTIN_TYPE n = DEREF_ntype(itype_basic_no(is));
			id = get_special(base_token[n].tok, 0);
			if (IS_NULL_id(id)) {
				return 0;
			}
			args = NULL_list(TOKEN);
			break;
		}
		case itype_token_tag: {
			/* Tokenised integral types */
			id = DEREF_id(itype_token_tok(is));
			args = DEREF_list(itype_token_args(is));
			break;
		}
		default:
			/* Other integral types */
			return 0;
		}
		break;
	}
	case type_floating_tag: {
		/* Floating types */
		FLOAT_TYPE fs = DEREF_ftype(type_floating_rep(s));
		if (IS_ftype_token(fs)) {
			id = DEREF_id(ftype_token_tok(fs));
			args = DEREF_list(ftype_token_args(fs));
			break;
		}
		return 0;
	}
	case type_compound_tag: {
		/* Class types */
		CLASS_TYPE cs = DEREF_ctype(type_compound_defn(s));
		CLASS_INFO ci = DEREF_cinfo(ctype_info(cs));
		if (ci & cinfo_token) {
			TYPE r = DEREF_type(ctype_form(cs));
			if (!IS_NULL_type(r) && IS_type_token(r)) {
				id = DEREF_id(type_token_tok(r));
				args = DEREF_list(type_token_args(r));
				break;
			}
		}
		return 0;
	}
	case type_token_tag: {
		/* Tokenised types */
		id = DEREF_id(type_token_tok(s));
		args = DEREF_list(type_token_args(s));
		break;
	}
	default:
		/* Other types */
		return 0;
	}
	if (defining_token(id)) {
		TOKEN sort;
		if (IS_NULL_list(args)) {
			t = qualify_type(t, cv, 0);
			return define_type_token(id, t, qual);
		}
		sort = DEREF_tok(id_token_sort(id));
		if (IS_tok_class(sort) && IS_type_compound(t)) {
			/* Check for template template parameters */
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
			TYPE r = DEREF_type(ctype_form(ct));
			if (!IS_NULL_type(r) && IS_type_token(r)) {
				IDENTIFIER tid = DEREF_id(type_token_tok(r));
				if (IS_id_class_name(tid)) {
					LIST(TOKEN)targs;
					targs = DEREF_list(type_token_args(r));
					if (eq_token_args(tid, tid, args, targs)) {
						return define_templ_token(id, tid);
					}
				}
			}
		}
	}
	if (expand_tokdef) {
		/* Expand token definitions */
		TOKEN sort = find_tokdef(id);
		if (!IS_NULL_tok(sort) && IS_tok_type(sort)) {
			TYPE r = DEREF_type(tok_type_value(sort));
			if (!IS_NULL_type(r) && eq_type(r, t)) {
				return 1;
			}
		}
	}
	return 0;
}


/*
    This routine checks whether the type s can be unified with t or vice
    versa using token definitions.
*/

static int
unify_types(TYPE s, TYPE t, int qu)
{
	if (force_tokdef || force_template || expand_tokdef) {
		CV_SPEC qs, qt;
		CV_SPEC rs, rt;
		if (IS_NULL_type(s)) {
			return 0;
		}
		if (IS_NULL_type(t)) {
			return 0;
		}
		qs = DEREF_cv(type_qual(s));
		qt = DEREF_cv(type_qual(t));
		qs &= cv_qual;
		qt &= cv_qual;
		rs = (qs & ~qt);
		rt = (qt & ~qs);
		if (rs == cv_none || qu) {
			if (unify_type(s, t, rt, 0)) {
				return 1;
			}
		}
		if (rt == cv_none || qu) {
			if (unify_type(t, s, rs, 0)) {
				return 1;
			}
		}
	}
	return 0;
}


/*
    This routine checks whether the types s and t are equal (excluding
    lvalue qualifiers).  If qu is 1 then the top level qualifiers
    are completely ignored, if it is 2 all qualifiers are ignored.
    The return values are as in eq_type_aux.  The routine is usually
    accessed through the macros eq_type and eq_type_unqual.
*/

int
eq_type_qual(TYPE s, TYPE t, int qu)
{
	int eq;
	if (EQ_type(s, t)) {
		return 1;
	}
	eq = eq_type_aux(s, t, qu);
	if (eq == 0) {
		eq = unify_types(s, t, qu);
	}
	return eq;
}


/*
    This routine checks whether the types s and t are offset equivalent.
    For example, 'int' is offset equivalent to 'unsigned int' because it
    has the same size and alignment requirements.  Note that the value 6
    is used in the builtin_casts table to indicate integral types which
    are equivalent in this way.
*/

int
eq_type_offset(TYPE s, TYPE t)
{
	unsigned ns = TAG_type(s);
	unsigned nt = TAG_type(t);
	if (ns != nt) {
		return 0;
	}
	if (ns == type_integer_tag) {
		INT_TYPE is = DEREF_itype(type_integer_rep(s));
		INT_TYPE it = DEREF_itype(type_integer_rep(t));
		if (IS_itype_basic(is) && IS_itype_basic(it)) {
			BUILTIN_TYPE bs = DEREF_ntype(itype_basic_no(is));
			BUILTIN_TYPE bt = DEREF_ntype(itype_basic_no(it));
			if (bs == bt) {
				return 1;
			}
			if (builtin_cast(bs, bt) == 6) {
				return 1;
			}
			return 0;
		}
	}
	return eq_type_unqual(s, t);
}


/*
    This routine finds the composite type (in the C sense) of the function
    types s and t.  eq gives the result of a previous call to eq_func_type.
    If the types are compatible then a new composite function type, based
    on s, is returned.  Otherwise the null type is returned.
*/

#if LANGUAGE_C

static TYPE
func_composite(TYPE s, TYPE t, int eq, ERROR *err, int mk)
{
	TYPE rs, rt;
	CV_SPEC qs, qt;
	TYPE mt = NULL_type;
	int es = DEREF_int(type_func_ellipsis(s));
	NAMESPACE ns = DEREF_nspace(type_func_pars(s));
	LIST(TYPE)ps = DEREF_list(type_func_ptypes(s));
	LIST(TYPE)pt = DEREF_list(type_func_mtypes(s));
	LIST(IDENTIFIER)pids = DEREF_list(type_func_pids(s));

	/* Check parameter types */
	if (!EQ_list(ps, pt)) {
		mt = DEREF_type(HEAD_list(pt));
	}
	if (eq == 0) {
		int et = DEREF_int(type_func_ellipsis(t));
		if (es & FUNC_NO_PARAMS) {
			/* s has no parameter information - swap types */
			if (et != FUNC_NO_PARAMS) {
				ps = DEREF_list(type_func_ptypes(t));
				ns = DEREF_nspace(type_func_pars(t));
				pids = DEREF_list(type_func_pids(t));
				es = et;
				et = FUNC_NO_PARAMS;
			}
		}
		if (et & FUNC_NO_PARAMS) {
			/* One type has no parameter information */
			if (es & FUNC_ELLIPSIS) {
				OPTION opt = option(OPT_ellipsis_extra);
				add_error(err, ERR_dcl_fct_compat_ellipsis());
				if (opt == OPTION_DISALLOW) {
					return NULL_type;
				}
			}
			if (!(es & FUNC_WEAK)) {
				pt = ps;
				while (!IS_NULL_list(pt)) {
					TYPE at = DEREF_type(HEAD_list(pt));
					if (!is_arg_promote(at)) {
						OPTION opt = option(OPT_func_incompat);
						add_error(err, ERR_dcl_fct_compat_prom(at));
						if (opt == OPTION_DISALLOW) {
							return NULL_type;
						}
					}
					pt = TAIL_list(pt);
				}
			}

		} else {
			/* Both types have parameter information */
			int prom = 0;
			int force = force_tokdef;
			LIST(TYPE)pr = NULL_list(TYPE);
			pt = DEREF_list(type_func_ptypes(t));
			if (es & FUNC_ELLIPSIS) {
				if (et & FUNC_ELLIPSIS) {
					/* Both functions have ellipsis */
					/* EMPTY */
				} else {
					/* One function has ellipsis */
					OPTION opt = option(OPT_ellipsis_extra);
					add_error(err, ERR_dcl_fct_compat_ellipsis());
					if (opt == OPTION_DISALLOW) {
						return NULL_type;
					}
					et |= FUNC_ELLIPSIS;
				}
			} else {
				if (et & FUNC_ELLIPSIS) {
					/* One function has ellipsis */
					OPTION opt = option(OPT_ellipsis_extra);
					add_error(err, ERR_dcl_fct_compat_ellipsis());
					if (opt == OPTION_DISALLOW) {
						return NULL_type;
					}
					es |= FUNC_ELLIPSIS;
				} else {
					/* Neither function has ellipsis */
					if (LENGTH_list(ps)!= LENGTH_list(pt)) {
						return NULL_type;
					}
				}
			}
			if (es & FUNC_PARAMS) {
				prom++;
			}
			if (et & FUNC_PARAMS) {
				prom++;
			}
			while (!IS_NULL_list(ps) && !IS_NULL_list(pt)) {
				TYPE ar;
				TYPE as = DEREF_type(HEAD_list(ps));
				TYPE at = DEREF_type(HEAD_list(pt));
				if (prom == 2) {
					/* Compare unpromoted types */
					as = unpromote_type(as);
					at = unpromote_type(at);
				}
				ar = type_composite(as, at, 0, 1, err, mk);
				if (IS_NULL_type(ar)) {
					/* Check for specified compatible types */
					ar = eq_argument(as, at, 1);
					if (IS_NULL_type(ar) && prom == 1) {
						if (es & FUNC_PARAMS) {
							as = unpromote_type(as);
						}
						if (et & FUNC_PARAMS) {
							at = unpromote_type(at);
						}
						ar = eq_argument(as, at, 0);
						if (!IS_NULL_type(ar)) {
							OPTION opt = option(OPT_func_incompat);
							ERROR err2 = ERR_dcl_fct_compat_prom(as);
							add_error(err, err2);
							if (opt == OPTION_DISALLOW) {
								ar = NULL_type;
							}
						}
					}
					if (IS_NULL_type(ar)) {
						DESTROY_list(pr, SIZE_type);
						return NULL_type;
					}
				}
				if (mk) {
					if (force) {
						/* Preserve printf and scanf types */
						if (is_printf_type(as)) {
							IDENTIFIER id = DEREF_id(type_name(as));
							COPY_id(type_name(ar), id);
						} else if (is_printf_type(at)) {
							IDENTIFIER id = DEREF_id(type_name(at));
							COPY_id(type_name(ar), id);
						}
					}
					if (prom == 2 && !is_arg_promote(ar)) {
						/* Promote type */
						ar = arg_promote_type(ar, err);
					}
					CONS_type(ar, pr, pr);
				}
				pt = TAIL_list(pt);
				ps = TAIL_list(ps);
			}
			if (!EQ_list(ps, pt)) {
				if (IS_NULL_list(ps)) {
					ps = pt;
				}
				while (!IS_NULL_list(ps)) {
					TYPE as = DEREF_type(HEAD_list(ps));
					as = eq_ellipsis(as);
					if (IS_NULL_type(as)) {
						DESTROY_list(pr, SIZE_type);
						return NULL_type;
					}
					if (mk) {
						CONS_type(as, pr, pr);
					}
					ps = TAIL_list(ps);
				}
			}
			if (es == et) {
				/* Same kinds of function */
				ps = REVERSE_list(pr);
			} else {
				/* Different kinds of function */
				int use_s = 1;
				if (et & FUNC_WEAK) {
					if (es & FUNC_WEAK) {
						if (et & FUNC_PARAMS) {
							use_s = 0;
						}
					}
				} else {
					if (es & FUNC_WEAK)use_s = 0;
				}
				if (use_s) {
					ps = DEREF_list(type_func_ptypes(s));
				} else {
					ps = DEREF_list(type_func_ptypes(t));
					es = et;
				}
				DESTROY_list(pr, SIZE_type);
			}
		}
	}

	/* Check return type */
	rs = DEREF_type(type_func_ret(s));
	rt = DEREF_type(type_func_ret(t));
	rs = type_composite(rs, rt, 0, 1, err, mk);
	if (IS_NULL_type(rs)) {
		return NULL_type;
	}

	/* Check member qualifiers */
	qs = DEREF_cv(type_func_mqual(s));
	qt = DEREF_cv(type_func_mqual(t));
	if (qs != qt) {
		qs &= cv_qual;
		qt &= cv_qual;
		if (qs != qt) {
			return NULL_type;
		}
		if (!eq_func_lang(s, t)) {
			return NULL_type;
		}
		qs = DEREF_cv(type_func_mqual(s));
	}

	/* Construct composite type */
	if (mk) {
		CV_SPEC cs = DEREF_cv(type_qual(s));
		CV_SPEC ct = DEREF_cv(type_qual(t));
		LIST(TYPE)ex = DEREF_list(type_func_except(s));
		cs |= ct;
		pt = ps;
		if (!IS_NULL_type(mt)) {
			CONS_type(mt, pt, pt);
		}
		MAKE_type_func(cs, rs, ps, es, qs, pt, ns, pids, ex, s);
	}
	return s;
}

#endif


/*
    This routine finds the composite type (in the C sense) of s and t.
    In C++ we only need to worry about compatible bound and unbound array
    types, since all functions will be declared with prototypes.  The
    routine returns the null type if s and t are not compatible.  Otherwise
    it tries to returns either s or, as a second choice, t, whenever
    possible to avoid new types having to be created.  Indeed if mk is
    false a new type is never created - this can be used whenever
    compatibility is being checked but the composite type is not used.
    The result is an lvalue if either s or t is.  If qual is nonzero to
    indicate that differing qualifiers are allowed.  In C++ the qualifiers
    are allowed at any level; in C qual gives the maximum depth.  Type
    qualifiers at the top level are handled by adding an error to err.
*/

TYPE
type_composite(TYPE s, TYPE t, int qual, int depth, ERROR *err, int mk)
{
	TYPE r = s;
	int eq = 1;
	int checked = 0;
	unsigned ns, nt;
	CV_SPEC qr, qs, qt;

	/* Check for obvious equality */
	if (EQ_type(s, t)) {
		return s;
	}
	if (IS_NULL_type(s)) {
		return NULL_type;
	}
	if (IS_NULL_type(t)) {
		return NULL_type;
	}

	/* Compare type qualifiers */
	ns = TAG_type(s);
	nt = TAG_type(t);
	qs = DEREF_cv(type_qual(s));
	qt = DEREF_cv(type_qual(t));
	qr = (qs | qt);
	if (qs != qt && qual <= 0) {
		/* Qualifiers should be equal up to lvalues */
		CV_SPEC rs = (qs & cv_qual);
		CV_SPEC rt = (qt & cv_qual);
		if (rs != rt) {
			OPTION opt;
			if (unify_types(s, t, 0)) {
				/* Can happen with token definitions */
				if (mk) {
					r = qualify_type(r, qr, 0);
				}
				return r;
			}
			opt = option(OPT_type_qual_incompat);
			if (opt == OPTION_DISALLOW) {
				goto return_lab;
			}
			add_error(err, ERR_basic_link_qual(rs, rt));
		}
	}
#if LANGUAGE_C
	qual--;
#endif

	/* Check on type components */
	if (ns == nt) {
		switch (ns) {
		case type_ptr_tag:
		case type_ref_tag: {
			/* Check pointer sub-types */
			TYPE pr;
			TYPE ps = DEREF_type(type_ptr_etc_sub(s));
			TYPE pt = DEREF_type(type_ptr_etc_sub(t));
			pr = type_composite(ps, pt, qual, depth + 1, err, mk);
			if (IS_NULL_type(pr)) {
				/* Check for generic pointer types */
				OPTION opt = option(OPT_gen_ptr_char);
				if (opt == OPTION_DISALLOW) {
					return NULL_type;
				}
				if (IS_type_top_etc(ps)) {
					if (eq_type_unqual(pt, type_char)) {
						CV_SPEC cv = DEREF_cv(type_qual(pt));
						pt = qualify_type(ps, cv, 0);
						add_error(err, ERR_conv_ptr_gen(t));
					} else {
						return NULL_type;
					}
				} else if (IS_type_top_etc(pt)) {
					if (eq_type_unqual(ps, type_char)) {
						CV_SPEC cv = DEREF_cv(type_qual(ps));
						ps = qualify_type(pt, cv, 0);
						add_error(err, ERR_conv_ptr_gen(s));
					} else {
						return NULL_type;
					}
				} else {
					return NULL_type;
				}
				pr = type_composite(ps, pt, qual, depth + 1, err, mk);
				if (IS_NULL_type(pr)) {
					return NULL_type;
				}
			}
			if (mk) {
				if (EQ_type(pr, ps) && qr == qs) {
					return s;
				}
				if (EQ_type(pr, pt) && qr == qt) {
					return t;
				}
				MAKE_type_ptr_etc(ns, qr, pr, r);
			}
			return r;
		}

#if LANGUAGE_CPP
		case type_ptr_mem_tag: {
			/* Check pointer to member class types */
			TYPE ps, pt, pr;
			CLASS_TYPE cs = DEREF_ctype(type_ptr_mem_of(s));
			CLASS_TYPE ct = DEREF_ctype(type_ptr_mem_of(t));
			if (!eq_ctype(cs, ct)) {
				return NULL_type;
			}

			/* Check pointer to member sub-types */
			ps = DEREF_type(type_ptr_mem_sub(s));
			pt = DEREF_type(type_ptr_mem_sub(t));
			pr = type_composite(ps, pt, qual, depth + 1, err, mk);
			if (IS_NULL_type(pr)) {
				return NULL_type;
			}
			if (mk) {
				if (EQ_type(pr, ps) && qr == qt) {
					return s;
				}
				if (EQ_type(pr, pt) && qr == qs) {
					return t;
				}
				MAKE_type_ptr_mem(qr, cs, pr, r);
			}
			return r;
		}
#endif

		case type_array_tag: {
			/* Check array sub-types */
			TYPE pr;
			NAT ms, mt, mr;
			TYPE ps = DEREF_type(type_array_sub(s));
			TYPE pt = DEREF_type(type_array_sub(t));
			pr = type_composite(ps, pt, qual, depth + 1, err, mk);
			if (IS_NULL_type(pr)) {
				return NULL_type;
			}

			/* Check array bounds */
			ms = DEREF_nat(type_array_size(s));
			mt = DEREF_nat(type_array_size(t));
			if (EQ_nat(ms, mt) || eq_nat(ms, mt)) {
				/* Equal bounds */
				if (EQ_type(pr, ps) && qr == qs) {
					return s;
				}
				if (EQ_type(pr, pt) && qr == qt) {
					return t;
				}
				mr = ms;
			} else if (IS_NULL_nat(ms)) {
				/* s unbounded, t bounded */
#if LANGUAGE_CPP
				if (depth) {
					return NULL_type;
				}
#endif
				if (EQ_type(pr, pt) && qr == qt) {
					return t;
				}
				mr = mt;
			} else if (IS_NULL_nat(mt)) {
				/* s bounded, t unbounded */
#if LANGUAGE_CPP
				if (depth) {
					return NULL_type;
				}
#endif
				if (EQ_type(pr, ps) && qr == qs) {
					return s;
				}
				mr = ms;
			} else {
				/* Unequal bounds - check for error
				 * propagation */
				if (is_error_nat(ms)) {
					mr = mt;
				} else if (is_error_nat(mt)) {
					mr = ms;
				} else {
					return NULL_type;
				}
			}
			if (mk) {
				MAKE_type_array(qr, pr, mr, r);
			}
			return r;
		}

		case type_func_tag: {
			/* Check function types */
			int ret = eq_func_type(s, t, 1, 0);
#if LANGUAGE_C
			if (ret < 2) {
				r = func_composite(s, t, ret, err, mk);
				return r;
			}
#else
			if (ret < 2) {
				eq = 0;
			} else if (depth && ret == 2) {
				/* Differ in language specifiers */
				eq = 0;
			}
#endif
			checked = 1;
			break;
		}

#if LANGUAGE_C
		case type_enumerate_tag: {
			/* Check C enumeration types */
			ENUM_TYPE es = DEREF_etype(type_enumerate_defn(s));
			ENUM_TYPE et = DEREF_etype(type_enumerate_defn(t));
			TYPE ps = DEREF_type(etype_rep(es));
			TYPE pt = DEREF_type(etype_rep(et));
			eq = eq_type_unqual(ps, pt);
			checked = 1;
			break;
		}
#endif
		}
	} else {
		switch (ns) {
		case type_top_tag: {
			/* Allow for 'void' and 'bottom' */
			if (nt == type_bottom_tag) {
				checked = 1;
				r = t;
			}
			break;
		}
		case type_bottom_tag: {
			/* Allow for 'void' and 'bottom' */
			if (nt == type_top_tag) {
				checked = 1;
			}
			break;
		}
#if LANGUAGE_C
		case type_integer_tag: {
			if (nt == type_enumerate_tag) {
				/* Check C enumeration types */
				TYPE pt;
				ENUM_TYPE et;
				et = DEREF_etype(type_enumerate_defn(t));
				pt = DEREF_type(etype_rep(et));
				eq = eq_type_unqual(s, pt);
				checked = 1;
				r = t;
			}
			break;
		}
		case type_enumerate_tag: {
			if (nt == type_integer_tag) {
				/* Check C enumeration types */
				TYPE ps;
				ENUM_TYPE es;
				es = DEREF_etype(type_enumerate_defn(s));
				ps = DEREF_type(etype_rep(es));
				eq = eq_type_unqual(ps, t);
				checked = 1;
			}
			break;
		}
#endif
		}
	}

	/* In other cases compatibility is equality */
	if (eq) {
		if (!checked) {
			eq = eq_type_unqual(s, t);
		}
		if (eq == 1) {
			if (mk) {
				if (ns == nt) {
					if (qr == qs) {
						return s;
					}
					if (qr == qt) {
						return t;
					}
				}
				r = qualify_type(r, qr, 0);
			}
			return r;
		}
	}
return_lab:
	if (ns == type_error_tag) {
		return t;
	}
	if (nt == type_error_tag) {
		return s;
	}
	return NULL_type;
}


/*
    This routine checks whether the types s and t are compatible, returning
    the composite type if they are (or either s or t if mk is false).  If
    the types are not compatible s is returned and an error is added to the
    end of err.  qual is as in type_composite.
*/

TYPE
check_compatible(TYPE s, TYPE t, int qual, ERROR *err, int mk)
{
	TYPE r;
	force_tokdef++;
	r = type_composite(s, t, qual, 0, err, mk);
	if (IS_NULL_type(r)) {
		add_error(err, ERR_basic_link_incompat(s, t));
		r = s;
	}
	force_tokdef--;
	return r;
}


/*
    C++ types are partitioned into object types, reference types and
    function types.  Object types are further partitioned into complete
    and incomplete types.  This routine checks whether the type t is
    an object type.  It returns an error if it isn't.
*/

ERROR
check_object(TYPE t)
{
	ERROR err = NULL_err;
	switch (TAG_type(t)) {
	case type_func_tag: {
		/* Function types are not object types */
		err = ERR_basic_types_obj_func(t);
		break;
	}
	case type_ref_tag: {
		/* Reference types are not object types */
		err = ERR_basic_types_obj_ref(t);
		break;
	}
	case type_templ_tag: {
		/* Check template types */
		TYPE s = DEREF_type(type_templ_defn(t));
		err = check_object(s);
		break;
	}
	}
	return err;
}


/*
    This routine checks whether the type t is an abstract class type.
    It returns an error if it is.  It also checks for arrays of abstract
    types, although it shouldn't be possible to construct these.
*/

ERROR
check_abstract(TYPE t)
{
	ERROR err = NULL_err;
	switch (TAG_type(t)) {
	case type_compound_tag: {
		/* Check for abstract classes */
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
		if (ci & cinfo_abstract) {
			err = class_info(ct, cinfo_abstract, 1);
		}
		break;
	}
	case type_array_tag: {
		/* Check for abstract arrays */
		TYPE s = DEREF_type(type_array_sub(t));
		err = check_abstract(s);
		break;
	}
	case type_templ_tag: {
		/* Check template types */
		TYPE s = DEREF_type(type_templ_defn(t));
		err = check_abstract(s);
		break;
	}
	}
	return err;
}


/*
    This routine checks whether the type t is an incomplete object type.
    It returns an error if it is.
*/

ERROR
check_incomplete(TYPE t)
{
	ERROR err = NULL_err;
	switch (TAG_type(t)) {
	case type_top_tag:
	case type_bottom_tag: {
		/* void and bottom are incomplete */
		err = ERR_basic_types_incompl(t);
		break;
	}
	case type_array_tag: {
		/* Check for incomplete arrays */
		NAT n = DEREF_nat(type_array_size(t));
		if (IS_NULL_nat(n)) {
			err = ERR_basic_types_incompl(t);
		} else {
			TYPE s = DEREF_type(type_array_sub(t));
			err = check_incomplete(s);
		}
		break;
	}
	case type_compound_tag: {
		/* Check for incomplete classes */
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
		if (!(ci & cinfo_defined)) {
			complete_class(ct, 1);
			ci = DEREF_cinfo(ctype_info(ct));
		}
		if (!(ci & cinfo_complete)) {
			err = ERR_basic_types_incompl(t);
		}
		break;
	}
	case type_enumerate_tag: {
		/* Check for incomplete enumerations */
		ENUM_TYPE et = DEREF_etype(type_enumerate_defn(t));
		CLASS_INFO ei = DEREF_cinfo(etype_info(et));
		if (!(ei & cinfo_complete)) {
			err = ERR_basic_types_incompl(t);
		}
		break;
	}
	case type_templ_tag: {
		/* Check template types */
		TYPE s = DEREF_type(type_templ_defn(t));
		err = check_incomplete(s);
		break;
	}
	}
	return err;
}


/*
    This routine checks whether the type t is a complete object type.  It
    returns an error if it isn't.
*/

ERROR
check_complete(TYPE t)
{
	ERROR err = check_object(t);
	if (IS_NULL_err(err)) {
		err = check_incomplete(t);
		if (!IS_NULL_err(err)) {
			err = concat_error(err, ERR_basic_types_obj_incompl());
		}
	}
	return err;
}


/*
    This routine checks whether the type t is a pointer to a complete
    object type, adding an error to err.  It returns the type pointed to.
*/

TYPE
check_pointer(TYPE t, ERROR *err)
{
	TYPE s;
	switch (TAG_type(t)) {
	case type_ptr_tag: {
		/* Pointer type */
		s = DEREF_type(type_ptr_sub(t));
		break;
	}
	case type_array_tag: {
		/* Allow for array-to-pointer conversion */
		s = DEREF_type(type_array_sub(t));
		break;
	}
	case type_func_tag: {
		/* Allow for function-to-pointer conversion */
		s = t;
		break;
	}
	case type_ref_tag: {
		/* Reference type */
		t = DEREF_type(type_ref_sub(t));
		s = check_pointer(t, err);
		return s;
	}
	default:
		/* Shouldn't happen */
		return t;
	}
	if (err != KILL_err) {
		switch (TAG_type(s)) {
		case type_top_tag:
		case type_bottom_tag: {
			add_error(err, ERR_basic_types_obj_void(t));
			break;
		}
		default:
			add_error(err, check_complete(s));
			break;
		}
	}
	return s;
}


/*
    This routine checks whether the expression a of type t represents a
    modifiable lvalue.  If it is then the null error is returned, otherwise
    a sequence of errors giving the reasons why t is not modifiable is
    returned.
*/

ERROR
check_modifiable(TYPE t, EXP a)
{
	ERROR err;
	unsigned tag = TAG_type(t);
	CV_SPEC qual = DEREF_cv(type_qual(t));
	if (qual & cv_lvalue) {
		while (tag == type_templ_tag) {
			t = DEREF_type(type_templ_defn(t));
			tag = TAG_type(t);
		}
		if (tag == type_func_tag) {
			/* Function types are not modifiable */
			err = ERR_basic_lval_mod_func();
		} else if (tag == type_array_tag) {
			/* Array types are not modifiable */
			err = ERR_basic_lval_mod_array();
		} else {
			err = check_complete(t);
			if (!IS_NULL_err(err)) {
				/* Incomplete types are not modifiable */
				err = concat_error(err, ERR_basic_lval_mod_incompl());
			} else if (qual & cv_const) {
				/* const objects are not modifiable */
				err = ERR_basic_lval_mod_const();
			} else if (tag == type_compound_tag) {
				CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
				CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
				if (ci & cinfo_const) {
					/* Objects with const members are not modifiable */
					err = ERR_basic_lval_mod_member(t);
				}
			} else if (tag == type_integer_tag) {
				if (option(OPT_const_string) && cv_string == cv_none) {
					EXP b = NULL_exp;
					DECL_SPEC ds = find_exp_linkage(a, &b, 1);
					if (ds & dspec_pure) {
						/* String literals are not modifiable */
						err = ERR_conv_array_str_mod();
					}
				}
			}
		}
	} else {
		/* rvalues are not modifiable */
		if (tag == type_error_tag) {
			err = NULL_err;
		} else {
			err = ERR_basic_lval_not();
			err = concat_error(err, ERR_basic_lval_mod_rvalue());
		}
	}
	return err;
}


/*
    This routine returns true if the type t has external linkage and is
    not an anonymous type.  Not all the cases are fully checked yet.
*/

int
is_global_type(TYPE t)
{
	if (!IS_NULL_type(t)) {
		assert(ORDER_type == 18);
		switch (TAG_type(t)) {
		case type_ptr_tag: {
			TYPE s = DEREF_type(type_ptr_sub(t));
			return is_global_type(s);
		}
		case type_ref_tag: {
			TYPE s = DEREF_type(type_ref_sub(t));
			return is_global_type(s);
		}
#if LANGUAGE_CPP
		case type_ptr_mem_tag: {
			TYPE s = DEREF_type(type_ptr_mem_sub(t));
			CLASS_TYPE ct = DEREF_ctype(type_ptr_mem_of(t));
			IDENTIFIER id = DEREF_id(ctype_name(ct));
			HASHID nm = DEREF_hashid(id_name(id));
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			if (!(ds & dspec_extern)) {
				return 0;
			}
			if (IS_hashid_anon(nm)) {
				return 0;
			}
			return is_global_type(s);
		}
#endif
		case type_func_tag: {
			TYPE r = DEREF_type(type_func_ret(t));
			LIST(TYPE)p = DEREF_list(type_func_ptypes(t));
			if (!is_global_type(r)) {
				return 0;
			}
			while (!IS_NULL_list(p)) {
				TYPE s = DEREF_type(HEAD_list(p));
				if (!is_global_type(s)) {
					return 0;
				}
				p = TAIL_list(p);
			}
			break;
		}
		case type_array_tag: {
			TYPE s = DEREF_type(type_array_sub(t));
			return is_global_type(s);
		}
		case type_compound_tag: {
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
			IDENTIFIER id = DEREF_id(ctype_name(ct));
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			HASHID nm = DEREF_hashid(id_name(id));
			if (!(ds & dspec_extern)) {
				return 0;
			}
			if (IS_hashid_anon(nm)) {
				return 0;
			}
			break;
		}
		case type_enumerate_tag: {
			ENUM_TYPE et = DEREF_etype(type_enumerate_defn(t));
			IDENTIFIER id = DEREF_id(etype_name(et));
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			HASHID nm = DEREF_hashid(id_name(id));
			if (!(ds & dspec_extern)) {
				return 0;
			}
			if (IS_hashid_anon(nm)) {
				return 0;
			}
			break;
		}
		case type_templ_tag: {
			TYPE s = DEREF_type(type_templ_defn(t));
			return is_global_type(s);
		}
		}
	}
	return 1;
}
