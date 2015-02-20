/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
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

#include <syntax/syntax.h>

#include <parse/constant.h>
#include <parse/lex.h>
#include <parse/predict.h>
#include <parse/preproc.h>

#include <construct/basetype.h>
#include <construct/class.h>
#include <construct/convert.h>
#include <construct/chktype.h>
#include <construct/function.h>
#include <construct/identifier.h>
#include <construct/inttype.h>
#include <construct/redeclare.h>
#include <construct/template.h>
#include <construct/token.h>

#include "exp_ops.h"
#include "ftype_ops.h"
#include "id_ops.h"
#include "itype_ops.h"
#include "nat_ops.h"
#include "tok_ops.h"
#include "type_ops.h"


/*
    This routine creates a type consisting of t qualified by the const-
    volatile qualifiers cv.  Note that the existing qualifiers for t are
    not taken into account in the result.  If t already has qualifier cv
    and force is false then t itself is returned, otherwise a copy of t
    with the appropriate qualifier is constructed.
*/

TYPE
qualify_type(TYPE t, CV_SPEC cv, int force)
{
	TYPE r;
	unsigned tag;
	IDENTIFIER tid;

	/* Just return t if it is correctly qualified */
	CV_SPEC qual = DEREF_cv(type_qual(t));
	if (qual == cv && !force) {
		return t;
	}

	/* Copy the type otherwise */
	tag = TAG_type(t);
	assert(ORDER_type == 18);
	switch (tag) {
	case type_pre_tag: {
		BASE_TYPE rep;
		QUALIFIER idtype;
		DECONS_type_pre(qual, tid, rep, idtype, t);
		MAKE_type_pre(cv, rep, idtype, r);
		break;
	}
	case type_integer_tag: {
		INT_TYPE rep;
		INT_TYPE sem;
		DECONS_type_integer(qual, tid, rep, sem, t);
		if (cv == cv_none && IS_NULL_id(tid) && !force) {
			r = make_itype(rep, sem);
			break;
		}
		MAKE_type_integer(cv, rep, sem, r);
		break;
	}
	case type_floating_tag: {
		FLOAT_TYPE rep;
		FLOAT_TYPE sem;
		DECONS_type_floating(qual, tid, rep, sem, t);
		if (cv == cv_none && IS_NULL_id(tid) && !force) {
			if (IS_ftype_basic(rep)) {
				BUILTIN_TYPE n =
				    DEREF_ntype(ftype_basic_no(rep));
				r = type_builtin[n];
				break;
			}
		}
		MAKE_type_floating(cv, rep, sem, r);
		break;
	}
	case type_top_tag: {
		tid = DEREF_id(type_name(t));
		if (cv == cv_none && IS_NULL_id(tid) && !force) {
			r = type_void;
			break;
		}
		MAKE_type_top(cv, r);
		break;
	}
	case type_bottom_tag: {
		tid = DEREF_id(type_name(t));
		if (cv == cv_none && IS_NULL_id(tid) && !force) {
			r = type_bottom;
			break;
		}
		MAKE_type_bottom(cv, r);
		break;
	}
	case type_ptr_tag: {
		TYPE sub;
		DECONS_type_ptr(qual, tid, sub, t);
		MAKE_type_ptr(cv, sub, r);
		break;
	}
	case type_ref_tag: {
		TYPE sub;
		CV_SPEC cv1 = (cv & cv_qual);
		DECONS_type_ref(qual, tid, sub, t);
		if (cv1) {
			/* Pass cv-qualifiers to base type */
			CV_SPEC cv2 = DEREF_cv(type_qual(sub));
			sub = qualify_type(sub,(cv1 | cv2), force);
			cv &= ~cv_qual;
		}
		MAKE_type_ref(cv, sub, r);
		break;
	}
#if LANGUAGE_CPP
	case type_ptr_mem_tag: {
		CLASS_TYPE of;
		TYPE sub;
		DECONS_type_ptr_mem(qual, tid, of, sub, t);
		MAKE_type_ptr_mem(cv, of, sub, r);
		break;
	}
#endif
	case type_func_tag: {
		int ell;
		TYPE ret;
		CV_SPEC mqual;
		NAMESPACE pars;
		LIST(TYPE)ptypes;
		LIST(TYPE)mtypes;
		LIST(TYPE)except;
		LIST(IDENTIFIER)pids;
		DECONS_type_func(qual, tid, ret, ptypes, ell, mqual, mtypes,
				 pars, pids, except, t);
		cv &= ~cv_qual;
		MAKE_type_func(cv, ret, ptypes, ell, mqual, mtypes, pars, pids,
			       except, r);
		break;
	}
	case type_array_tag: {
		TYPE sub;
		NAT size;
		CV_SPEC cv1 = (cv & cv_qual);
		DECONS_type_array(qual, tid, sub, size, t);
		if (cv1) {
			/* Pass cv-qualifiers to base type */
			CV_SPEC cv2 = DEREF_cv(type_qual(sub));
			sub = qualify_type(sub,(cv1 | cv2), force);
			cv &= ~cv_qual;
		}
		MAKE_type_array(cv, sub, size, r);
		break;
	}
	case type_bitfield_tag: {
		INT_TYPE defn;
		DECONS_type_bitfield(qual, tid, defn, t);
		MAKE_type_bitfield(cv, defn, r);
		break;
	}
	case type_compound_tag: {
		CLASS_TYPE defn;
		DECONS_type_compound(qual, tid, defn, t);
		MAKE_type_compound(cv, defn, r);
		break;
	}
	case type_enumerate_tag: {
		ENUM_TYPE defn;
		DECONS_type_enumerate(qual, tid, defn, t);
		MAKE_type_enumerate(cv, defn, r);
		break;
	}
	case type_token_tag: {
		INSTANCE app;
		IDENTIFIER tok;
		LIST(TOKEN)args;
		DECONS_type_token(qual, tid, tok, args, app, t);
		MAKE_type_token(cv, tok, args, r);
		COPY_inst(type_token_app(r), app);
		break;
	}
	case type_templ_tag: {
		int fix;
		TYPE defn;
		TOKEN sort;
		DECONS_type_templ(qual, tid, sort, defn, fix, t);
		MAKE_type_templ(cv, sort, defn, fix, r);
		break;
	}
	case type_instance_tag: {
		IDENTIFIER id;
		DECL_SPEC acc;
		DECONS_type_instance(qual, tid, id, acc, t);
		MAKE_type_instance(cv, id, acc, r);
		break;
	}
	case type_dummy_tag: {
		int tok;
		DECONS_type_dummy(qual, tid, tok, t);
		MAKE_type_dummy(cv, tok, r);
		break;
	}
	case type_error_tag: {
		tid = DEREF_id(type_name(t));
		cv &= cv_lvalue;
		MAKE_type_error(cv, r);
		break;
	}
	default : {
		error(ERR_INTERNAL, "Invalid type");
		tid = NULL_id;
		r = t;
		break;
	}
	}
	COPY_id(type_name(r), tid);
	UNUSED(qual);
	return r;
}


/*
    This routine copies the typedef definition type t (corresponding to the
    typedef-name id) qualified by the const-volatile qualifiers cv.  Note
    that the qualifiers apply to the base type of an array rather than the
    array itself.  For example, in:

		typedef int array [3] ;
		const array var ;

    the type of var is 'const int [3]'.  Also any qualifiers applied to
    reference and function types are ignored.
*/

TYPE
copy_typedef(IDENTIFIER id, TYPE t, CV_SPEC cv)
{
	CV_SPEC qual = DEREF_cv(type_qual(t));
	CV_SPEC qual_new = (qual | cv);
	CV_SPEC qual_join = (qual & cv);
	if (qual_join && !IS_NULL_id(id)) {
		/* Warn about duplicate qualifiers */
		report(crt_loc, ERR_dcl_type_type_cv(id, qual_join));
	}

	/* Check types */
	switch (TAG_type(t)) {
	case type_ptr_tag: {
		/* Copy pointer types */
		TYPE s = DEREF_type(type_ptr_sub(t));
		TYPE r = copy_typedef(id, s, cv_none);
		if (!EQ_type(r, s) || qual_new != qual) {
			IDENTIFIER tid = DEREF_id(type_name(t));
			MAKE_type_ptr(qual_new, r, t);
			COPY_id(type_name(t), tid);
		}
		break;
	}
	case type_ref_tag: {
		/* Ignore qualifiers for references */
		TYPE s, r;
		if (cv && !IS_NULL_id(id)) {
			report(crt_loc, ERR_dcl_ref_cv_type(cv, id));
		}
		s = DEREF_type(type_ref_sub(t));
		r = copy_typedef(id, s, cv_none);
		if (!EQ_type(r, s)) {
			IDENTIFIER tid = DEREF_id(type_name(t));
			MAKE_type_ref(qual, r, t);
			COPY_id(type_name(t), tid);
		}
		break;
	}
#if LANGUAGE_CPP
	case type_ptr_mem_tag: {
		/* Copy pointer member types */
		TYPE s = DEREF_type(type_ptr_mem_sub(t));
		TYPE r = copy_typedef(id, s, cv_none);
		if (!EQ_type(r, s) || qual_new != qual) {
			IDENTIFIER tid = DEREF_id(type_name(t));
			CLASS_TYPE of = DEREF_ctype(type_ptr_mem_of(t));
			MAKE_type_ptr_mem(qual_new, of, r, t);
			COPY_id(type_name(t), tid);
		}
		break;
	}
#endif
	case type_func_tag: {
		/* Ignore qualifiers for functions */
		int ell;
		TYPE ret;
		CV_SPEC mqual;
		IDENTIFIER tid;
		NAMESPACE pars;
		LIST(TYPE)except;
		LIST(TYPE)ptypes;
		LIST(TYPE)mtypes;
		LIST(IDENTIFIER)pids;
		LIST(TYPE)mtypes_new;
		LIST(TYPE)ptypes_new = NULL_list(TYPE);
		LIST(IDENTIFIER)pids_new = NULL_list(IDENTIFIER);

		/* Warn about qualifiers */
		if (cv && !IS_NULL_id(id)) {
			report(crt_loc, ERR_dcl_fct_qual(cv, id));
		}

		/* Decompose old function type */
		DECONS_type_func(qual, tid, ret, ptypes, ell, mqual,
				 mtypes, pars, pids, except, t);

		/* Copy appropriate components */
		ret = copy_typedef(id, ret, cv_none);
		while (!IS_NULL_list(pids)) {
			/* Redeclare each parameter */
			TYPE s;
			IDENTIFIER pid = DEREF_id(HEAD_list(pids));
			pid = copy_id(pid, 1);
			CONS_id(pid, pids_new, pids_new);
			s = DEREF_type(id_parameter_type(pid));
			s = qualify_type(s, cv_none, 0);
			CONS_type(s, ptypes_new, ptypes_new);
			pids = TAIL_list(pids);
		}
		pids_new = REVERSE_list(pids_new);
		ptypes_new = REVERSE_list(ptypes_new);
		if (EQ_list(ptypes, mtypes)) {
			mtypes_new = ptypes_new;
		} else {
			TYPE r = DEREF_type(HEAD_list(mtypes));
			CONS_type(r, ptypes_new, mtypes_new);
		}

		/* Construct new function type */
		MAKE_type_func(qual, ret, ptypes_new, ell, mqual,
			       mtypes_new, pars, pids_new, except, t);
		COPY_id(type_name(t), tid);
		break;
	}
	case type_array_tag: {
		/* Qualify the base type of an array */
		NAT n = DEREF_nat(type_array_size(t));
		TYPE s = DEREF_type(type_array_sub(t));
		TYPE r = copy_typedef(id, s, cv);
		IDENTIFIER tid = DEREF_id(type_name(t));
		MAKE_type_array(qual, r, n, t);
		COPY_id(type_name(t), tid);
		break;
	}
	case type_token_tag: {
		/* Tokenised types */
		IDENTIFIER tok = DEREF_id(type_token_tok(t));
		DECL_SPEC ds = DEREF_dspec(id_storage(tok));
		if (!(ds & dspec_defn))goto default_lab;
		t = expand_type(t, 0);
		t = qualify_type(t, qual_new, 0);
		break;
	}
	case type_templ_tag: {
		/* Template types */
		TYPE s = DEREF_type(type_templ_defn(t));
		TOKEN tok = DEREF_tok(type_templ_sort(t));
		IDENTIFIER tid = DEREF_id(type_name(t));
		MAKE_type_templ(qual_new, tok, s, 1, t);
		COPY_id(type_name(t), tid);
		break;
	}
	default:
default_lab:
		/* Other types */
		if (qual_new != qual) {
			t = qualify_type(t, qual_new, 0);
		}
		break;
	}
	return t;
}


/*
    This routine creates a type which is an lvalue qualified version of t
    (also preserving any other type qualifiers).
*/

TYPE
lvalue_type(TYPE t)
{
	CV_SPEC qual = DEREF_cv(type_qual(t));
	if (qual & cv_lvalue) {
		return t;
	}
	qual |= cv_lvalue;
	return qualify_type(t, qual, 0);
}


/*
    This routine creates a type which is identical to t except that it
    is an rvalue rather than an lvalue.
*/

TYPE
rvalue_type(TYPE t)
{
	CV_SPEC qual = DEREF_cv(type_qual(t));
	if (!(qual & cv_lvalue)) {
		return t;
	}
	qual &= ~cv_lvalue;
	return qualify_type(t, qual, 0);
}


/*
    The pre-types are a construction mechanism for allowing built-in types
    such as 'unsigned long int' to be built up.  Each pre-type is associated
    with a bitmask giving the basic keywords used in defining the type.
    This routine is the main constructor function, which combines two
    pre-types and returns the result.
*/

BASE_TYPE
join_pre_types(BASE_TYPE b1, BASE_TYPE b2)
{
	BASE_TYPE bt = (b1 | b2);
	BASE_TYPE bs = (b1 & b2);
	if (bs) {
		if (bs == btype_long) {
			if (!(bt & btype_long2)) {
				/* Allow 'long long' */
				bt |= btype_long2;
				return bt;
			}
		}
		report(crt_loc, ERR_dcl_type_simple_dup(bs));
	}
	return bt;
}


/*
    This routine injects the type t into the pre-type p, returning the
    result.  p will be built up of pointers, arrays etc. but its base
    type will be null.  The routine injects t into the base type position.
    It also checks for illegal type constructions.  Note that p itself
    is built up using inject_pre_type, so all such illegal constructions
    will be detected.  Some of the error recovery for such constructions
    is mildly interesting.  Also note that bitfields are handled by a
    separate routine, make_bitfield_type.
*/

TYPE
inject_pre_type(TYPE p, TYPE t, int chk)
{
	TYPE q = p;
	unsigned long n = 0;
	if (IS_NULL_type(q)) {
		return t;
	}
	if (IS_NULL_type(t)) {
		return q;
	}

	/* Map 'ptr template' to 'template ptr' etc */
	if (IS_type_templ(t) && !IS_type_templ(q)) {
		TYPE s;
		int fix;
		TOKEN tok;
		CV_SPEC cv;
		IDENTIFIER tid;
		DECONS_type_templ(cv, tid, tok, s, fix, t);
		if (!fix) {
			s = inject_pre_type(q, s, chk);
			MAKE_type_templ(cv, tok, s, fix, t);
			COPY_id(type_name(t), tid);
			return t;
		}
	}

	/* Scan down to incomplete component */
	do {
		switch (TAG_type(q)) {
		case type_ptr_tag: {
			/* Pointer types, t * */
			TYPE s = DEREF_type(type_ptr_sub(q));
			if (IS_NULL_type(s)) {
				switch (TAG_type(t)) {
				case type_ref_tag: {
					/* Can't have pointer to reference */
					report(crt_loc, ERR_dcl_ref_ptr());
					t = DEREF_type(type_ref_sub(t));
					if (!IS_NULL_type(t)) {
						t = rvalue_type(t);
					}
					break;
				}
				case type_bitfield_tag: {
					/* Can't have pointer to bitfield */
					report(crt_loc, ERR_class_bit_ptr());
					t = find_bitfield_type(t);
					break;
				}
				case type_func_tag: {
					/* Adjust function type */
					member_func_type(NULL_ctype, null_tag,
							 t);
					check_weak_func(t, 0);
					break;
				}
				}
				COPY_type(type_ptr_sub(q), t);
				if (chk) {
					s = t;
				}
			}
			q = s;
			break;
		}
		case type_ref_tag: {
			/* Reference types, t & */
			TYPE s = DEREF_type(type_ref_sub(q));
			if (IS_NULL_type(s)) {
				switch (TAG_type(t)) {
				case type_top_tag:
				case type_bottom_tag: {
					/* Can't have reference to void */
					report(crt_loc, ERR_dcl_ref_void(t));
					MODIFY_type_ptr_etc(type_ptr_tag, q);
					break;
				}
				case type_ref_tag: {
					/* Can't have reference to reference */
					report(crt_loc, ERR_dcl_ref_ref());
					t = DEREF_type(type_ref_sub(t));
					break;
				}
				case type_bitfield_tag: {
					/* Can't have reference to bitfield */
					report(crt_loc, ERR_class_bit_ref());
					t = find_bitfield_type(t);
					break;
				}
				case type_func_tag: {
					/* Adjust function type */
					member_func_type(NULL_ctype, null_tag,
							 t);
					check_weak_func(t, 0);
					break;
				}
				}
				/* All references are 'lvalue t &' */
				if (!IS_NULL_type(t)) {
					t = lvalue_type(t);
				}
				COPY_type(type_ptr_etc_sub(q), t);
				if (chk) {
					s = t;
				}
			}
			q = s;
			break;
		}
#if LANGUAGE_CPP
		case type_ptr_mem_tag: {
			/* Pointer to member types, t c::* */
			TYPE s = DEREF_type(type_ptr_mem_sub(q));
			if (IS_NULL_type(s)) {
				switch (TAG_type(t)) {
				case type_top_tag:
				case type_bottom_tag: {
					/* Can't have pointer to void member */
					report(crt_loc, ERR_dcl_mptr_void(t));
					break;
				}
				case type_ref_tag: {
					/* Can't have pointer to reference
					 * member */
					report(crt_loc, ERR_dcl_mptr_ref());
					t = DEREF_type(type_ref_sub(t));
					if (!IS_NULL_type(t))t = rvalue_type(t);
					break;
				}
				case type_bitfield_tag: {
					/* Can't have pointer to bitfield
					 * member */
					report(crt_loc, ERR_class_bit_mptr());
					t = find_bitfield_type(t);
					break;
				}
				case type_func_tag: {
					/* Adjust function type */
					CLASS_TYPE ct;
					ct = DEREF_ctype(type_ptr_mem_of(q));
					member_func_type(ct, id_mem_func_tag, t);
					check_weak_func(t, 0);
					break;
				}
				}
				COPY_type(type_ptr_mem_sub(q), t);
				if (chk) {
					s = t;
				}
			}
			q = s;
			break;
		}
#endif
		case type_func_tag: {
			/* Function types, t ( args ) */
			TYPE s = DEREF_type(type_func_ret(q));
			if (IS_NULL_type(s)) {
				ERROR err = NULL_err;
				switch (TAG_type(t)) {
				case type_array_tag: {
					/* Can't have function returning
					 * array */
					report(crt_loc, ERR_dcl_fct_array());
					t = DEREF_type(type_array_sub(t));
					MAKE_type_ptr(cv_none, t, t);
					break;
				}
				case type_bitfield_tag: {
					/* Can't have function returning
					 * bitfield */
					report(crt_loc, ERR_dcl_fct_bitf());
					t = find_bitfield_type(t);
					break;
				}
				case type_func_tag: {
					/* Can't have function returning
					 * function */
					report(crt_loc, ERR_dcl_fct_func());
					member_func_type(NULL_ctype, null_tag,
							 t);
					check_weak_func(t, 0);
					MAKE_type_ptr(cv_none, t, t);
					break;
				}
				case type_compound_tag: {
					/* Can't have function returning
					 * abstract */
					ERROR err1 = check_abstract(t);
					if (!IS_NULL_err(err1)) {
						ERROR err2 =
						    ERR_class_abstract_ret();
						err1 = concat_error(err1, err2);
						report(crt_loc, err1);
					}
					break;
				}
				}
				t = check_ret_type(t, &err, 0);
				if (!IS_NULL_err(err)) {
					err = concat_error(err,
							   ERR_dcl_fct_ret());
					report(crt_loc, err);
				}
				object_type(t, null_tag);
				COPY_type(type_func_ret(q), t);
				if (chk) {
					s = t;
				}
			}
			q = s;
			break;
		}

		case type_array_tag: {
			/* Array types, t [n] */
			TYPE s = DEREF_type(type_array_sub(q));
			if (IS_NULL_type(s)) {
				switch (TAG_type(t)) {
				case type_top_tag:
				case type_bottom_tag: {
					/* Can't have array of void */
					report(crt_loc, ERR_dcl_array_void(t));
					break;
				}
				case type_ref_tag: {
					/* Can't have array of references */
					report(crt_loc, ERR_dcl_ref_array());
					t = DEREF_type(type_ref_sub(t));
					if (!IS_NULL_type(t))t = rvalue_type(t);
					break;
				}
				case type_func_tag: {
					/* Can't have array of functions */
					report(crt_loc, ERR_dcl_array_func());
					member_func_type(NULL_ctype, null_tag,
							 t);
					check_weak_func(t, 0);
					MAKE_type_ptr(cv_none, t, t);
					break;
				}
				case type_bitfield_tag: {
					/* Can't have array of bitfields */
					report(crt_loc, ERR_dcl_array_bitf());
					t = find_bitfield_type(t);
					break;
				}
				case type_array_tag: {
					/* Check arrays of arrays */
					NAT m = DEREF_nat(type_array_size(t));
					if (IS_NULL_nat(m)) {
						ERROR err =
						    ERR_dcl_array_array();
						report(crt_loc, err);
					}
					break;
				}
				case type_compound_tag:
				case type_enumerate_tag: {
					ERROR err = check_complete(t);
					if (!IS_NULL_err(err)) {
						/* Can't have array of
						 * incomplete */
						ERROR err2 =
						    ERR_dcl_array_incompl();
						err = concat_error(err, err2);
						report(crt_loc, err);
					}
					err = check_abstract(t);
					if (!IS_NULL_err(err)) {
						/* Can't have array of
						 * abstract */
						ERROR err2 =
						    ERR_dcl_array_abstract();
						err = concat_error(err, err2);
						report(crt_loc, err);
					}
					break;
				}
				}
				COPY_type(type_array_sub(q), t);
				if (chk) {
					s = t;
				}
			}
			q = s;
			break;
		}

		case type_templ_tag: {
			/* Template types, template < ... > t */
			TYPE s = DEREF_type(type_templ_defn(q));
			if (IS_NULL_type(s)) {
				COPY_type(type_templ_defn(q), t);
				if (chk) {
					s = t;
				}
			}
			q = s;
			n--;
			break;
		}

		default: {
			/* Only the types above should appear */
			q = NULL_type;
			n--;
			break;
		}
		}
		n++;
	} while (!IS_NULL_type(q));
	if (chk) {
		IGNORE check_value(OPT_VAL_declarator_max, n);
	}
	return p;
}


/*
    This routine checks whether the type t is formed from the inferred
    type type_inferred.  It returns INFERRED_EMPTY if there were no
    specifiers or qualifiers in the description of p,  INFERRED_QUAL if
    the only type specifiers were const or volatile, INFERRED_SPEC for
    other inferred types, and INFERRED_NOT for non-inferred types.
*/

int
is_type_inferred(TYPE t)
{
	if (EQ_type(t, type_inferred)) {
		return INFERRED_EMPTY;
	}
	while (!IS_NULL_type(t)) {
		switch (TAG_type(t)) {
		case type_integer_tag: {
			/* Check integer types */
			if (EQ_type(t, type_inferred)) {
				return INFERRED_SPEC;
			} else {
				INT_TYPE it = DEREF_itype(type_integer_rep(t));
				t = DEREF_type(itype_prom(it));
				if (EQ_type(t, type_inferred)) {
					/* Qualified inferred type */
					return INFERRED_QUAL;
				}
			}
			return INFERRED_NOT;
		}
		case type_ptr_tag:
		case type_ref_tag: {
			/* Check pointer and reference types */
			t = DEREF_type(type_ptr_etc_sub(t));
			break;
		}
#if LANGUAGE_CPP
		case type_ptr_mem_tag: {
			/* Check pointer to member types */
			t = DEREF_type(type_ptr_mem_sub(t));
			break;
		}
#endif
		case type_func_tag: {
			/* Check function return types only */
			t = DEREF_type(type_func_ret(t));
			break;
		}
		case type_array_tag: {
			/* Check array types */
			t = DEREF_type(type_array_sub(t));
			break;
		}
		case type_bitfield_tag: {
			/* Check bitfield types */
			t = find_bitfield_type(t);
			break;
		}
		case type_templ_tag: {
			/* Check template types */
			t = DEREF_type(type_templ_defn(t));
			break;
		}
		default : {
			/* Other types are not inferred */
			return INFERRED_NOT;
		}
		}
	}
	return INFERRED_QUAL;
}


/*
    This routine returns an equivalent type to the inferred type t, but
    with any inferred components replaced by 'signed int'.
*/

TYPE
clean_inferred_type(TYPE t)
{
	TYPE sub;
	CV_SPEC qual;
	IDENTIFIER tid;
	switch (TAG_type(t)) {
	case type_integer_tag: {
		if (EQ_type(t, type_inferred)) {
			/* Simple inferred type */
			t = type_sint;
		} else {
			INT_TYPE it = DEREF_itype(type_integer_rep(t));
			TYPE pt = DEREF_type(itype_prom(it));
			if (EQ_type(pt, type_inferred)) {
				/* Qualified inferred type */
				qual = DEREF_cv(type_qual(t));
				t = qualify_type(type_sint, qual, 0);
			}
		}
		break;
	}
	case type_ptr_tag: {
		DECONS_type_ptr(qual, tid, sub, t);
		sub = clean_inferred_type(sub);
		MAKE_type_ptr(qual, sub, t);
		COPY_id(type_name(t), tid);
		break;
	}
	case type_ref_tag: {
		DECONS_type_ref(qual, tid, sub, t);
		sub = clean_inferred_type(sub);
		MAKE_type_ref(qual, sub, t);
		COPY_id(type_name(t), tid);
		break;
	}
#if LANGUAGE_CPP
	case type_ptr_mem_tag: {
		CLASS_TYPE of;
		DECONS_type_ptr_mem(qual, tid, of, sub, t);
		sub = clean_inferred_type(sub);
		MAKE_type_ptr_mem(qual, of, sub, t);
		COPY_id(type_name(t), tid);
		break;
	}
#endif
	case type_func_tag: {
		int ell;
		CV_SPEC mqual;
		NAMESPACE pars;
		LIST(TYPE)ptypes;
		LIST(TYPE)mtypes;
		LIST(TYPE)except;
		LIST(IDENTIFIER)pids;
		DECONS_type_func(qual, tid, sub, ptypes, ell, mqual,
				 mtypes, pars, pids, except, t);
		sub = clean_inferred_type(sub);
		MAKE_type_func(qual, sub, ptypes, ell, mqual,
			       mtypes, pars, pids, except, t);
		COPY_id(type_name(t), tid);
		break;
	}
	case type_array_tag: {
		NAT size;
		DECONS_type_array(qual, tid, sub, size, t);
		sub = clean_inferred_type(sub);
		MAKE_type_array(qual, sub, size, t);
		COPY_id(type_name(t), tid);
		break;
	}
	case type_bitfield_tag: {
		INT_TYPE bf;
		DECONS_type_bitfield(qual, tid, bf, t);
		sub = DEREF_type(itype_bitfield_sub(bf));
		sub = clean_inferred_type(sub);
		COPY_type(itype_bitfield_sub(bf), sub);
		MAKE_type_bitfield(qual, bf, t);
		COPY_id(type_name(t), tid);
		break;
	}
	case type_templ_tag: {
		int fix;
		TOKEN sort;
		DECONS_type_templ(qual, tid, sort, sub, fix, t);
		sub = clean_inferred_type(sub);
		MAKE_type_templ(qual, sort, sub, fix, t);
		COPY_id(type_name(t), tid);
		break;
	}
	}
	return t;
}


/*
    This routine returns an error suitable for the inferred type t.
    infer gives the value of is_type_inferred on t.
*/

ERROR
report_inferred_type(TYPE t, int infer)
{
	ERROR err = NULL_err;
	switch (infer) {
	case INFERRED_EMPTY:
	case INFERRED_SPEC:
		err = ERR_dcl_type_none();
		break;
	case INFERRED_QUAL:
		err = ERR_dcl_type_qual();
		break;
	}
	err = concat_error(err, ERR_dcl_type_infer(t));
	return err;
}


/*
    This macro is used to shift a base type specifier into a more sensible
    range for use in a switch statement.
*/

#define BTYPE(B)	((B) >> 3)


/*
    This routine determines the type given by the base type specifiers bt.
*/

TYPE
make_base_type(BASE_TYPE bt)
{
	TYPE t;
	BASE_TYPE bm = bt;
	BASE_TYPE bo = btype_none;

	if (bm & btype_other) {
		/* Deal with non-integral cases */
		if (bm & btype_void) {
			t = type_void;
			bm = btype_void;
		} else if (bm & btype_double) {
			if (bm & btype_long) {
				t = type_ldouble;
				bm = btype_ldouble;
			} else {
				t = type_double;
				bm = btype_double;
			}
		} else if (bm & btype_float) {
			if (bm & btype_long) {
				if (bm & btype_long2) {
					/* Map 'long long float' to 'long
					 * double' */
					bm = (btype_llong | btype_float);
					bo = btype_ldouble;
					t = type_ldouble;
				} else {
					/* Map 'long float' to 'double' */
					bm = (btype_long | btype_float);
					bo = btype_double;
					t = type_double;
				}
			} else {
				t = type_float;
				bm = btype_float;
			}
		} else if (bm & btype_bool) {
			t = type_bool;
			bm = btype_bool;
		} else if (bm & btype_wchar_t) {
			t = type_wchar_t;
			bm = btype_wchar_t;
		} else if (bm & btype_bottom) {
			t = type_bottom;
			bm = btype_bottom;
		} else if (bm & btype_size_t) {
			t = type_size_t;
			bm = btype_size_t;
		} else if (bm & btype_ptrdiff_t) {
			t = type_ptrdiff_t;
			bm = btype_ptrdiff_t;
		} else {
			error(ERR_INTERNAL, "Unknown type specifier");
			bm = btype_sint;
			t = type_sint;
		}
	} else {
		do {
			/* Deal with obvious integral cases */
			switch (BTYPE(bm)) {
			case BTYPE(btype_char): {
				bm = btype_char;
				t = type_char;
				break;
			}
			case BTYPE(btype_signed | btype_char): {
				bm = btype_schar;
				t = type_schar;
				break;
			}
			case BTYPE(btype_unsigned | btype_char): {
				bm = btype_uchar;
				t = type_uchar;
				break;
			}
			case BTYPE(btype_short):
			case BTYPE(btype_short | btype_int):
			case BTYPE(btype_signed | btype_short):
			case BTYPE(btype_signed | btype_short | btype_int): {
				bm = btype_sshort;
				t = type_sshort;
				break;
			}
			case BTYPE(btype_unsigned | btype_short):
			case BTYPE(btype_unsigned | btype_short | btype_int): {
				bm = btype_ushort;
				t = type_ushort;
				break;
			}
			case BTYPE(btype_int):
			case BTYPE(btype_none):
			case BTYPE(btype_signed):
			case BTYPE(btype_signed | btype_int): {
				bm = btype_sint;
				t = type_sint;
				break;
			}
			case BTYPE(btype_unsigned):
			case BTYPE(btype_unsigned | btype_int): {
				bm = btype_uint;
				t = type_uint;
				break;
			}
			case BTYPE(btype_long):
			case BTYPE(btype_long | btype_int):
			case BTYPE(btype_signed | btype_long):
			case BTYPE(btype_signed | btype_long | btype_int): {
				bm = btype_slong;
				t = type_slong;
				break;
			}
			case BTYPE(btype_unsigned | btype_long):
			case BTYPE(btype_unsigned | btype_long | btype_int): {
				bm = btype_ulong;
				t = type_ulong;
				break;
			}
			case BTYPE(btype_llong):
			case BTYPE(btype_llong | btype_int):
			case BTYPE(btype_signed | btype_llong):
			case BTYPE(btype_signed | btype_llong | btype_int): {
				/* Allow for 'signed long long' */
				if (basetype_info[ntype_sllong].key) {
					report(crt_loc,
					       ERR_dcl_type_simple_llong(bm));
					bm = btype_sllong;
					t = type_sllong;
				} else {
					bm = btype_slong;
					t = type_slong;
				}
				break;
			}
			case BTYPE(btype_unsigned | btype_llong):
			case BTYPE(btype_unsigned | btype_llong | btype_int): {
				/* Allow for 'unsigned long long' */
				if (basetype_info[ntype_sllong].key) {
					report(crt_loc,
					       ERR_dcl_type_simple_llong(bm));
					bm = btype_ullong;
					t = type_ullong;
				} else {
					bm = btype_ulong;
					t = type_ulong;
				}
				break;
			}
			case BTYPE(btype_long | btype_char): {
				/* Map 'long char' to 'wchar_t' */
				bm = (btype_long | btype_char);
				bo = btype_wchar_t;
				t = type_wchar_t;
				break;
			}
			default : {
				/* Invalid type specifier */
				bm = btype_none;
				if (bt & btype_signed) {
					bm |= btype_signed;
				} else if (bt & btype_unsigned) {
					bm |= btype_unsigned;
				}
				if (bt & btype_char) {
					bm |= btype_char;
				} else if (bt & btype_short) {
					bm |= btype_short;
				} else if (bt & btype_long2) {
					bm |= btype_llong;
				} else if (bt & btype_long) {
					bm |= btype_long;
				}
				t = NULL_type;
				break;
			}
			}
		} while (IS_NULL_type(t));
	}

	/* Check result */
	if (bt & ~bm) {
		/* Report excess type specifiers */
		if (bo == btype_none) {
			bo = (bt & bm);
		}
		report(crt_loc, ERR_dcl_type_simple_bad(bt));
	} else if (bo) {
		/* Report non-standard type specifiers */
		report(crt_loc, ERR_dcl_type_simple_bad(bt));
	}
	return t;
}


/*
    This flag is used by complete_pre_type to decide whether a type
    name should be marked as having been used.  This is not the case,
    for example, in a class definition.
*/

static int use_type_name = 1;


/*
    This routine turns a pre-type comprising the base type qualifiers bt
    and the type specifier t, used during the type construction routines,
    into a genuine type.  The original type is destroyed.  The routine
    also assigns the const-volatile qualifier cv to the output type.
*/

TYPE
complete_pre_type(BASE_TYPE bt, TYPE t, CV_SPEC cv, int infer)
{
	/* Deal with named types */
	if (!IS_NULL_type(t)) {
		if (bt) {
			report(crt_loc, ERR_dcl_type_simple_undecl(bt, t));
		}
		if (IS_type_pre(t)) {
			CV_SPEC qual;
			QUALIFIER it;
			IDENTIFIER id;
			DESTROY_type_pre(destroy, qual, id, bt, it, t);
			qual |= cv;
			switch (bt) {
			case btype_class:
			case btype_struct:
			case btype_union:
			case btype_enum: {
				/* Deal with elaborated types */
				DECL_SPEC mode = dspec_used;
				if (it != qual_none) {
					mode = dspec_alias;
				}
				id = find_elaborate_type(id, bt, NULL_type,
							 mode);
				break;
			}
			}
			if (IS_id_class_name_etc(id)) {
				t = DEREF_type(id_class_name_etc_defn(id));
				if (IS_type_templ(t)) {
					t = deduce_type_template(id,
								 use_type_name);
				}
				t = copy_typedef(id, t, qual);
				COPY_id(type_name(t), id);
				if (use_type_name) {
					use_id(id, 0);
				}
			} else {
				report(crt_loc, ERR_dcl_type_simple_undef(id));
				t = type_error;
			}
		} else {
			t = copy_typedef(NULL_id, t, cv);
		}
		return t;
	}

	/* Deal with type specifiers */
	if (bt == btype_none) {
		t = type_inferred;
	} else {
		t = make_base_type(bt);
	}
	if (cv) {
		t = qualify_type(t, cv, 0);
	}
	if (infer) {
		/* Check for inferred types */
		int i = is_type_inferred(t);
		if (i != INFERRED_NOT) {
			ERROR err;
			t = clean_inferred_type(t);
			err = report_inferred_type(t, i);
			report(crt_loc, err);
		}
	}
	return t;
}


/*
    This routine is equivalent to complete_pre_type except that it leaves
    elaborated type declarations (such as 'struct s') as pre-types.  It is
    used in declarations without declarators where such declarations
    resolve differently than in the main case.
*/

TYPE
empty_complete_pre_type(BASE_TYPE bt, TYPE t, CV_SPEC cv, int infer)
{
	/* Check for elaborated type declarations */
	if (!IS_NULL_type(t) && IS_type_pre(t)) {
		BASE_TYPE key = DEREF_btype(type_pre_rep(t));
		switch (key) {
		case btype_class:
		case btype_struct:
		case btype_union:
		case btype_enum: {
			if (bt) {
				ERROR err = ERR_dcl_type_simple_undecl(bt, t);
				report(crt_loc, err);
			}
			COPY_cv(type_qual(t), cv);
			COPY_btype(type_pre_rep(t), key);
			return t;
		}
		}
	}

	/* Otherwise obtain the completed type */
	use_type_name = 0;
	t = complete_pre_type(bt, t, cv, infer);
	use_type_name = 1;
	return t;
}


/*
    This routine returns the type underlying the bitfield type t.
*/

TYPE
find_bitfield_type(TYPE t)
{
	INT_TYPE it = DEREF_itype(type_bitfield_defn(t));
	t = DEREF_type(itype_bitfield_sub(it));
	return t;
}


/*
    This routine finds the bitfield representation for a bitfield originally
    declared with representation bt which expands to the type t.
*/

BASE_TYPE
get_bitfield_rep(TYPE t, BASE_TYPE bt)
{
	int depth = 0;
	IDENTIFIER id = DEREF_id(type_name(t));
	while (!IS_NULL_id(id) && depth < 100) {
		/* Scan down to original typedef definition */
		bt = DEREF_btype(id_class_name_etc_rep(id));
		t = DEREF_type(id_class_name_etc_defn(id));
		id = DEREF_id(type_name(t));
		depth++;
	}
	if (IS_type_integer(t)) {
		INT_TYPE it = DEREF_itype(type_integer_rep(t));
		if (IS_itype_basic(it)) {
			BASE_TYPE br = DEREF_btype(itype_basic_rep(it));
			if (bt & br) {
				if (!(br & btype_char)) {
					br &= ~btype_signed;
				}
				if (bt & btype_signed) {
					br |= btype_signed;
				}
			}
			bt = br;
		}
	}
	return bt;
}


/*
    This routine creates a bitfield type with base type t and width n.
    Note that in 'int : 3', t will be 'signed int' whereas the sign of
    the bitfield itself is implementation dependent.  For this reason
    the pre-type which gave rise to t, bt (in this case 'int'), is also
    given.  The zero argument is true if zero sized bitfields are
    allowed.
*/

TYPE
check_bitfield_type(CV_SPEC cv, TYPE t, BASE_TYPE bt, NAT n, int zero)
{
	INT_TYPE bf;
	TYPE p = NULL_type;
	DECL_SPEC info = dspec_none;
	CV_SPEC qual = DEREF_cv(type_qual(t));
	if (qual) {
		/* Move any cv-qualifiers to top level */
		t = qualify_type(t, cv_none, 0);
		cv |= qual;
	}
	switch (TAG_type(t)) {
	case type_integer_tag:
	case type_enumerate_tag: {
		/* Integral types are allowed */
		int ok = 1;
		bt = get_bitfield_rep(t, bt);
		if (bt & btype_int) {
			if (bt & (btype_short | btype_long)) {
				ok = 0;
			}
		} else {
			ok = 0;
		}
		if (!ok) {
			/* Only 'int' types allowed in C */
			report(crt_loc, ERR_class_bit_base_int(t));
		}
		if (!(bt & (btype_signed | btype_unsigned))) {
			/* No sign given in type specifier */
			report(crt_loc, ERR_class_bit_sign(bt));
		}
		break;
	}
	case type_token_tag: {
		/* Allow template parameter types */
		if (is_templ_type(t)) {
			IDENTIFIER id = DEREF_id(type_token_tok(t));
			LIST(TOKEN)args = DEREF_list(type_token_args(t));
			t = apply_itype_token(id, args);
			bt = (btype_named | btype_template);
			break;
		}
		report(crt_loc, ERR_class_bit_base(t));
		return t;
	}
	case type_error_tag: {
		/* Ignore error types */
		return t;
	}
	default: {
		/* Other types are not allowed */
		report(crt_loc, ERR_class_bit_base(t));
		return t;
	}
	}

	/* Check the range of n */
	if (IS_NULL_nat(n) || is_zero_nat(n)) {
		/* Only anonymous bitfields can have size zero */
		if (!zero) {
			report(crt_loc, ERR_class_bit_dim_zero());
		}
		info |= dspec_pure;
		n = small_nat[0];
		p = type_sint;
	} else {
		if (is_negative_nat(n)) {
			/* Bitfield size cannot be negative */
			report(crt_loc, ERR_class_bit_dim_neg(n));
			n = negate_nat(n);
		}
		if (check_type_size(t, n) > 0) {
			report(crt_loc, ERR_class_bit_dim_big(n, t));
		}
		if (IS_nat_small(n)) {
			unsigned sz = DEREF_unsigned(nat_small_value(n));
			unsigned si = basetype_info[ntype_sint].min_bits;
			if (sz < si) {
				/* Fits into 'signed int' */
				p = type_sint;
			} else if (sz == si && (bt & btype_unsigned)) {
				/* Fits into 'unsigned int' */
				p = type_uint;
			}
		}
	}
	if (IS_NULL_type(p)) {
		/* NOT YET IMPLEMENTED */
		p = promote_type(t);
	}

	/* Construct bitfield type */
	if (zero) {
		info |= dspec_ignore;
	}
	MAKE_itype_bitfield(p, NULL_list(TYPE), t, bt, n, info, bf);
	MAKE_type_bitfield(cv, bf, t);
	return t;
}


/*
    This routine is identical to check_bitfield_type except that it
    takes a constant-expression e rather than the integer constant n.
*/

TYPE
make_bitfield_type(TYPE t, BASE_TYPE bt, EXP e, int zero)
{
	ERROR err = NULL_err;
	NAT n = make_nat_exp(e, &err);
	if (!IS_NULL_err(err)) {
		err = concat_error(err, ERR_class_bit_dim_const());
		report(crt_loc, err);
	}
	t = check_bitfield_type(cv_none, t, bt, n, zero);
	return t;
}


/*
    This routine checks the array bound n.  n can be null, indicating an
    unbounded array, or a positive constant.
*/

NAT
check_array_dim(NAT n)
{
	if (!IS_NULL_nat(n)) {
		if (is_zero_nat(n)) {
			report(crt_loc, ERR_dcl_array_dim_zero());
		} else if (is_negative_nat(n)) {
			report(crt_loc, ERR_dcl_array_dim_neg(n));
			n = negate_nat(n);
		}
	}
	return n;
}


/*
    This routine turns the integer constant expression e into an array
    bound.  e may also be the null expression, indicating an unbounded
    array.
*/

NAT
make_array_dim(EXP e)
{
	if (!IS_NULL_exp(e)) {
		ERROR err = NULL_err;
		NAT n = make_nat_exp(e, &err);
		if (!IS_NULL_err(err)) {
			err = concat_error(err, ERR_dcl_array_dim_const());
			report(crt_loc, err);
		}
		n = check_array_dim(n);
		return n;
	}
	return NULL_nat;
}


/*
    This routine checks whether t is an integral type containing the base
    type specifiers m.  It is used to spot signed types, unsigned types,
    character types and so on.
*/

int
check_int_type(TYPE t, BASE_TYPE m)
{
	if (IS_type_integer(t)) {
		INT_TYPE it = DEREF_itype(type_integer_rep(t));
		switch (TAG_itype(it)) {
		case itype_basic_tag: {
			BASE_TYPE bt = DEREF_btype(itype_basic_rep(it));
			if ((bt & m) == m) {
				return 1;
			}
			break;
		}
		case itype_token_tag: {
			/* Tokenised types */
			IDENTIFIER tid = DEREF_id(itype_token_tok(it));
			TOKEN tok = DEREF_tok(id_token_sort(tid));
			if (IS_tok_proc(tok)) {
				tok = DEREF_tok(tok_proc_res(tok));
			}
			if (IS_tok_type(tok)) {
				BASE_TYPE bt = DEREF_btype(tok_type_kind(tok));
				if ((bt & m) == m) {
					return 1;
				}
			}
			break;
		}
		}
	}
	return 0;
}


/*
    These lists are used to record the compatible types set by the
    routines below.
*/

static LIST(TYPE) arg1_types = NULL_list(TYPE);
static LIST(TYPE) arg2_types = NULL_list(TYPE);
static LIST(TYPE) ell_types = NULL_list(TYPE);


/*
    This routine sets the types t and s to be compatible with option
    level opt.
*/

void
set_compatible_type(TYPE t, TYPE s, unsigned opt)
{
	TYPE pt = type_char_star;
	TYPE ps = type_void_star;
	if (eq_type(t, pt) && eq_type(s, ps)) {
		set_option(OPT_gen_ptr_char, opt);
	} else {
		report(preproc_loc, ERR_pragma_compat_type());
	}
	return;
}


/*
    This routine finds the canonical argument type for the type t by
    chasing down the lists of compatible argument types.  It returns
    the null type if t is not compatible with a type from this list.
*/

static
TYPE find_arg_type(TYPE t)
{
	LIST(TYPE)p = arg1_types;
	LIST(TYPE)q = arg2_types;
	while (!IS_NULL_list(p)) {
		TYPE r = DEREF_type(HEAD_list(p));
		r = type_composite(t, r, 0, 1, KILL_err, 0);
		if (!IS_NULL_type(r)) {
			r = DEREF_type(HEAD_list(q));
			return r;
		}
		q = TAIL_list(q);
		p = TAIL_list(p);
	}
	return NULL_type;
}


/*
    This routine sets the types t and s to be compatible as function
    parameters.
*/

void
accept_argument(TYPE t, TYPE s)
{
	TYPE pt, ps;
	LIST(TYPE)p;
	t = qualify_type(t, cv_none, 0);
	t = make_param_type(t, CONTEXT_PARAMETER);
	s = qualify_type(s, cv_none, 0);
	s = make_param_type(s, CONTEXT_PARAMETER);
	pt = find_arg_type(t);
	ps = find_arg_type(s);
	if (IS_NULL_type(ps)) {
		ps = s;
	}
	if (!IS_NULL_type(pt)) {
		/* Already have entry for t */
		if (!eq_type(ps, pt)) {
			report(preproc_loc, ERR_pragma_arg_dup(t));
		}
		return;
	}
	pt = type_composite(ps, t, 0, 1, KILL_err, 0);
	if (!IS_NULL_type(pt)) {
		report(preproc_loc, ERR_pragma_arg_cycle());
		return;
	}
	p = arg2_types;
	CONS_type(t, arg1_types, arg1_types);
	CONS_type(ps, p, arg2_types);
	while (!IS_NULL_list(p)) {
		pt = DEREF_type(HEAD_list(p));
		pt = type_composite(pt, t, 0, 1, KILL_err, 0);
		if (!IS_NULL_type(pt)) {
			COPY_type(HEAD_list(p), ps);
		}
		p = TAIL_list(p);
	}
	return;
}


/*
    This routine sets the type t to be compatible with an ellipsis in
    function parameters.
*/

void
accept_ellipsis(TYPE t)
{
	TYPE r;
	t = qualify_type(t, cv_none, 0);
	t = make_param_type(t, CONTEXT_PARAMETER);
	r = eq_ellipsis(t);
	if (IS_NULL_type(r)) {
		CONS_type(t, ell_types, ell_types);
	}
	return;
}


/*
    This routine checks whether the types t and s are compatible as
    function parameters.  If eq is true then compatibility is only
    checked if one of the types appears in the list of types.  The
    routine returns the composite type.
*/

TYPE
eq_argument(TYPE t, TYPE s, int eq)
{
	TYPE pt = find_arg_type(t);
	TYPE ps = find_arg_type(s);
	if (EQ_type(pt, ps)) {
		if (!IS_NULL_type(pt)) {
			return pt;
		}
		if (eq) {
			return NULL_type;
		}
	}
	if (IS_NULL_type(pt)) {
		pt = t;
	}
	if (IS_NULL_type(ps)) {
		ps = s;
	}
	pt = type_composite(pt, ps, 0, 1, KILL_err, 1);
	return pt;
}


/*
    This routine checks whether the type t is compatible with an ellipsis
    in function parameters.
*/

TYPE
eq_ellipsis(TYPE t)
{
	LIST(TYPE)p = ell_types;
	while (!IS_NULL_list(p)) {
		TYPE r = DEREF_type(HEAD_list(p));
		TYPE s = eq_argument(t, r, 0);
		if (!IS_NULL_type(s)) {
			return s;
		}
		p = TAIL_list(p);
	}
	return NULL_type;
}


/*
    These variables stand for the basic types which arise naturally in
    C and C++.  This includes the basic integer and floating-point types,
    bool, size_t and related construct types, void and bottom (the type
    of an expression which does not return), plus a few useful composite
    types.
*/

TYPE type_builtin[ORDER_ntype];
TYPE ptr_type_builtin[ORDER_ntype];
TYPE type_func_void;
TYPE type_temp_func;
TYPE type_ellipsis;
TYPE type_error;


/*
    This routine initialises the basic types above.
*/

void
init_types(void)
{
	unsigned long n;
	init_itypes(1);
	for (n = 0; n < ORDER_ntype; n++) {
		MAKE_type_ptr(cv_none, type_builtin[n], ptr_type_builtin[n]);
	}
	MAKE_type_func(cv_lvalue, type_void, NULL_list(TYPE), 0, cv_lang,
		       NULL_list(TYPE), NULL_nspace, NULL_list(IDENTIFIER),
		       NULL_list(TYPE), type_func_void);
	MAKE_type_func(cv_none, type_void, NULL_list(TYPE), 0, cv_lang,
		       NULL_list(TYPE), NULL_nspace, NULL_list(IDENTIFIER),
		       NULL_list(TYPE), type_temp_func);
	MAKE_type_error(cv_none, type_error);
	type_ellipsis = NULL_type;
	return;
}
