/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/check.h>
#include <shared/error.h>

#include <utility/config.h>
#include "c_types.h"

#include <utility/error.h>
#include <utility/catalog.h>
#include <utility/option.h>
#include <utility/buffer.h>

#include <syntax/syntax.h>

#include <parse/constant.h>
#include <parse/literal.h>
#include <parse/predict.h>
#include <parse/preproc.h>

#include <output/bitstream.h>
#include <output/tok.h>

#include <construct/access.h>
#include <construct/basetype.h>
#include <construct/cast.h>
#include <construct/check.h>
#include <construct/chktype.h>
#include <construct/construct.h>
#include <construct/convert.h>
#include <construct/derive.h>
#include <construct/exception.h>
#include <construct/expression.h>
#include <construct/function.h>
#include <construct/identifier.h>
#include <construct/initialise.h>
#include <construct/inttype.h>
#include <construct/overload.h>
#include <construct/statement.h>
#include <construct/template.h>
#include <construct/tokdef.h>
#include <construct/token.h>
#include <construct/typeid.h>

#include "ctype_ops.h"
#include "err_ops.h"
#include "exp_ops.h"
#include "ftype_ops.h"
#include "graph_ops.h"
#include "id_ops.h"
#include "itype_ops.h"
#include "nat_ops.h"
#include "tok_ops.h"
#include "type_ops.h"


/*
    CREATE A CALCULATED INTEGER CONSTANT EXPRESSION
 */

EXP
make_lit_exp(EXP a)
{
	TYPE t = DEREF_type(exp_type(a));
	NAT n;
	EXP e;
	MAKE_nat_calc(a, n);
	MAKE_exp_int_lit(t, n, exp_cast_tag, e);
	return e;
}


/*
    This routine introduces a dummy cast expression which converts the
    expression a to its own type t.  This is needed in a couple of places
    where it is necessary to recognise cast expressions.
*/

static EXP
cast_exact(TYPE t, EXP a)
{
	EXP e;
	if (IS_exp_cast(a)) {
		/* Exact casts are idempotent */
		unsigned conv = DEREF_unsigned(exp_cast_conv(a));
		if (conv == CONV_EXACT) {
			a = DEREF_exp(exp_cast_arg(a));
		}
	}
	MAKE_exp_cast(t, CONV_EXACT, a, e);
	return e;
}


/*
    This routine finds the rank of a conversion to the integral type t
    from the integral type s.  For basic types this is given by the
    table builtin_casts.
*/

static int
rank_int_int(TYPE t, TYPE s)
{
	int ct = 100, cr = 100;
	INT_TYPE is = DEREF_itype(type_integer_sem(s));
	INT_TYPE it = DEREF_itype(type_integer_sem(t));
	INT_TYPE ir = DEREF_itype(type_integer_rep(t));

	/* Find the semantic conversion */
	if (!EQ_itype(it, ir)) {
		if (eq_itype(it, is)) {
			return 0;
		}
		if (IS_itype_basic(ir) && IS_itype_basic(is)) {
			BUILTIN_TYPE bt = DEREF_ntype(itype_basic_no(it));
			BUILTIN_TYPE bs = DEREF_ntype(itype_basic_no(is));
			ct = builtin_cast(bs, bt);
		}
	}

	/* Find the representational conversion */
	while (IS_itype_promote(ir)) {
		/* Allow for integer promotion conversions */
		ir = DEREF_itype(itype_promote_arg(ir));
	}
	if (eq_itype(ir, is)) {
		return 0;
	}
	if (IS_itype_basic(ir) && IS_itype_basic(is)) {
		BUILTIN_TYPE br = DEREF_ntype(itype_basic_no(ir));
		BUILTIN_TYPE bs = DEREF_ntype(itype_basic_no(is));
		cr = builtin_cast(bs, br);
	} else {
		TYPE ps = promote_type(s);
		if (eq_type(ps, t)) {
			return 0;
		}
	}

	/* Return the better conversion */
	return cr < ct ? cr : ct;
}


/*
    This routine finds the rank of a conversion to the floating-point
    type t from the floating-point type s.
*/

static int
rank_float_float(TYPE t, TYPE s)
{
	int ct = 0;
	FLOAT_TYPE fs = DEREF_ftype(type_floating_rep(s));
	FLOAT_TYPE ft = DEREF_ftype(type_floating_rep(t));
	while (IS_ftype_arg_promote(ft)) {
		/* Allow for floating promotion conversions */
		ft = DEREF_ftype(ftype_arg_promote_arg(ft));
	}
	if (!eq_ftype(ft, fs)) {
		if (IS_ftype_basic(ft) && IS_ftype_basic(fs)) {
			BUILTIN_TYPE nt = DEREF_ntype(ftype_basic_no(ft));
			BUILTIN_TYPE ns = DEREF_ntype(ftype_basic_no(fs));
			ct = builtin_cast(ns, nt);
		} else {
			TYPE ps = promote_type(s);
			if (eq_type(ps, t)) {
				return 0;
			}
		}
	}
	return ct;
}


/*
    This, and the following routines, are used to perform the basic type
    conversions allowed within the language.  Each takes a destination
    type t and an argument expression a.  In this case both t and the type
    of a are integral (including enumeration and bitfield) types.  The case
    where t is bool is dealt with separately by convert_boolean, however a
    may have type bool.  rank gives the rank of the conversion, or -1 if
    the rank needs to be calculated using rank_int_int.
*/

EXP
cast_int_int(TYPE t, EXP a, ERROR *err, unsigned cast, int rank)
{
	EXP e;
	int opt;
	TYPE s = DEREF_type(exp_type(a));
	unsigned nt = TAG_type(t);
	unsigned ns = TAG_type(s);

	/* Don't force unnecessary token definitions */
	if (force_tokdef) {
		TYPE t0 = t;
		TYPE s0 = s;
		t = expand_type(t0, 1);
		if (!EQ_type(t, t0)) {
			nt = TAG_type(t);
			if (nt == type_floating_tag || nt == type_ptr_tag) {
				t = t0;
				nt = TAG_type(t);
			}
		}
		s = expand_type(s0, 1);
		if (!EQ_type(s, s0)) {
			ns = TAG_type(s);
			if (ns == type_floating_tag || ns == type_ptr_tag) {
				s = s0;
				ns = TAG_type(s);
			}
		}
	}

	/* Deal with bitfields */
	if (ns == type_bitfield_tag) {
		TYPE r = find_bitfield_type(s);
		MAKE_exp_cast(r, CONV_BITFIELD, a, a);
		/* NOT YET IMPLEMENTED: find rank */
		rank = 0;
		e = cast_int_int(t, a, err, cast, rank);
		if (EQ_exp(e, a)) {
			MAKE_exp_cast(t, CONV_INT_INT, e, e);
		}
		return e;
	}
	if (nt == type_bitfield_tag) {
		TYPE r = find_bitfield_type(t);
		/* NOT YET IMPLEMENTED: find rank */
		rank = 0;
		e = cast_int_int(r, a, err, cast, rank);
		if (EQ_exp(e, a)) {
			MAKE_exp_cast(r, CONV_INT_INT, e, e);
		}
		MAKE_exp_cast(t,(CONV_BITFIELD | CONV_REVERSE), e, e);
		return e;
	}

	/* Deal with identity casts */
	if (nt == ns) {
		if (EQ_type(t, s)) {
			if (IS_exp_int_lit(a) && cast != CAST_IMPLICIT) {
				NAT n = DEREF_nat(exp_int_lit_nat(a));
				MAKE_exp_int_lit(t, n, exp_cast_tag, a);
			}
			return a;
		}
		if (eq_type(t, s)) {
			if (cast == CAST_IMPLICIT) {
				/* Preserve semantics for implicit casts */
				return a;
			}
			if (cast != CAST_REINTERP) {
				/* Override semantics for other casts */
				if (IS_exp_int_lit(a)) {
					NAT n = DEREF_nat(exp_int_lit_nat(a));
					MAKE_exp_int_lit(t, n, exp_cast_tag, e);
				} else {
					MAKE_exp_cast(t, CONV_INT_INT, a, e);
				}
				return e;
			}
		}
	}

	/* Find error severity level */
	if (cast == CAST_IMPLICIT) {
		opt = OPT_conv_int_int_impl;
	} else if (cast & CAST_STATIC) {
		opt = OPT_conv_int_int_expl;
	} else {
		opt = OPT_error;
	}

	/* Can't cast implicitly to enumeration type */
	if (nt == type_enumerate_tag) {
		ERROR err2;
#if LANGUAGE_C
		if (IS_exp_int_lit(a)) {
			/* Allow for C enumerators */
			unsigned tag = DEREF_unsigned(exp_int_lit_etag(a));
			if (tag == exp_identifier_tag) {
				e = make_cast_nat(t, a, err, cast);
				return e;
			}
		}
#endif
		if (cast == CAST_IMPLICIT) {
			if (option(OPT_conv_int_enum) > option(opt)) {
				opt = OPT_conv_int_enum;
			}
		}
		if (ns == type_enumerate_tag) {
			err2 = ERR_expr_cast_stat_enum_enum(s, t);
		} else {
			err2 = ERR_expr_cast_stat_int_enum(s, t);
		}
		err2 = set_severity(err2, opt, 0);
		if (!IS_NULL_err(err2)) {
			e = cast_token(t, a, err, err2, cast);
			if (!IS_NULL_exp(e)) {
				return e;
			}
		}
	} else if (opt == OPT_error) {
		ERROR err2 = ERR_conv_integral_cast(s, t);
		err2 = set_severity(err2, opt, 0);
		if (!IS_NULL_err(err2)) {
			e = cast_token(t, a, err, err2, cast);
			if (!IS_NULL_exp(e)) {
				return e;
			}
		}
		opt = OPT_none;
	}

	/* Deal with integral constants */
	if (IS_exp_int_lit(a)) {
		e = make_cast_nat(t, a, err, cast);
		return e;
	}

	/* Check integer to integer conversions */
	if (rank != 0 && option(opt)) {
		if (nt == type_integer_tag && ns == type_integer_tag) {
			if (rank < 0) {
				rank = rank_int_int(t, s);
			}
			if (rank >= max_builtin_cast) {
				ERROR err2 = ERR_conv_integral_cast(s, t);
				err2 = set_severity(err2, opt, 0);
				if (!IS_NULL_err(err2)) {
					e = cast_token(t, a, err, err2, cast);
					if (!IS_NULL_exp(e)) {
						return e;
					}
				}
			}
		}
	}

	/* Construct the result */
	MAKE_exp_cast(t, CONV_INT_INT, a, e);
	return e;
}


/*
    This routine converts the integral expression a to the floating point
    type t.
*/

EXP
cast_int_float(TYPE t, EXP a, ERROR *err, unsigned cast)
{
	EXP e;
	int opt;
	TYPE s = DEREF_type(exp_type(a));

	/* Find error severity level */
	if (cast == CAST_IMPLICIT) {
		opt = OPT_conv_int_int_impl;
	} else if (cast & CAST_STATIC) {
		opt = OPT_conv_int_int_expl;
	} else {
		opt = OPT_error;
	}
	if (option(opt)) {
		ERROR err2 = ERR_conv_fpint_float(s, t);
		err2 = set_severity(err2, opt, 0);
		if (!IS_NULL_err(err2)) {
			e = cast_token(t, a, err, err2, cast);
			if (!IS_NULL_exp(e)) {
				return e;
			}
		}
	}

	/* Construct the result */
	MAKE_exp_cast(t, CONV_INT_FLT, a, e);
	return e;
}


/*
    This routine converts the floating point expression a to the integral
    type t (which will not be bool).  Note that a floating point literal
    cast to an integral type is an integral constant expression.
*/

static EXP
cast_float_int(TYPE t, EXP a, ERROR *err, unsigned cast)
{
	EXP e;
	int opt;
	TYPE s = DEREF_type(exp_type(a));

	/* Find error severity level */
	if (cast == CAST_IMPLICIT) {
		opt = OPT_conv_int_int_impl;
		if (IS_type_enumerate(t)) {
			/* Can't have enumeration type */
			if (option(OPT_conv_int_enum) > option(opt)) {
				opt = OPT_conv_int_enum;
			}
		}
	} else if (cast & CAST_STATIC) {
		opt = OPT_conv_int_int_expl;
	} else {
		opt = OPT_error;
	}
	if (option(opt)) {
		ERROR err2 = ERR_conv_fpint_trunc(s, t);
		err2 = set_severity(err2, opt, 0);
		if (!IS_NULL_err(err2)) {
			e = cast_token(t, a, err, err2, cast);
			if (!IS_NULL_exp(e)) {
				return e;
			}
		}
	}

	/* Construct the result */
	MAKE_exp_cast(t, CONV_FLT_INT, a, e);

	/* Deal with floating point literals */
	if (IS_exp_float_lit(a)) {
		FLOAT f = DEREF_flt(exp_float_lit_flt(a));
		NAT n = round_float_lit(f, crt_round_mode);
		if (!IS_NULL_nat(n)) {
			EXP c = make_int_exp(t, exp_cast_tag, n);
			if (!IS_NULL_exp(c)) {
				return c;
			}
		}
		MAKE_nat_calc(e, n);
		MAKE_exp_int_lit(t, n, exp_cast_tag, e);
	}
	return e;
}


/*
    This routine converts the floating point expression a to the floating
    point type t.
*/

EXP
cast_float_float(TYPE t, EXP a, ERROR *err, unsigned cast)
{
	EXP e;
	int opt;
	TYPE s = DEREF_type(exp_type(a));

	/* Don't force unnecessary token definitions */
	if (force_tokdef) {
		TYPE t0 = t;
		TYPE s0 = s;
		t = expand_type(t0, 1);
		s = expand_type(s0, 1);
		if (!IS_type_floating(t)) {
			t = t0;
		}
		if (!IS_type_floating(s)) {
			s = s0;
		}
	}

	/* Deal with identity casts */
	if (eq_type(t, s)) {
		if (cast != CAST_REINTERP) {
			return a;
		}
	}

	/* Find error severity level */
	if (cast == CAST_IMPLICIT) {
		opt = OPT_conv_int_int_impl;
	} else if (cast & CAST_STATIC) {
		opt = OPT_conv_int_int_expl;
	} else {
		opt = OPT_error;
	}
	if (option(opt)) {
		int c = rank_float_float(t, s);
		if (c >= max_builtin_cast || opt == OPT_error) {
			ERROR err2 = ERR_conv_double_cast(s, t);
			err2 = set_severity(err2, opt, 0);
			if (!IS_NULL_err(err2)) {
				e = cast_token(t, a, err, err2, cast);
				if (!IS_NULL_exp(e)) {
					return e;
				}
			}
		}
	}

	/* Construct the result */
	MAKE_exp_cast(t, CONV_FLT_FLT, a, e);
	return e;
}


/*
    This routine creates an expression for casting the expression a to
    type t using cast where either t or the type of a depends on a
    template parameter type.
*/

EXP
cast_templ_type(TYPE t, EXP a, unsigned cast)
{
	EXP e;
	int op;
	switch (cast) {
	case CAST_IMPLICIT: op = lex_implicit;          break;
	case CAST_STATIC:   op = lex_static_Hcast;      break;
	case CAST_REINTERP: op = lex_reinterpret_Hcast; break;
	case CAST_CONST:    op = lex_const_Hcast;       break;
	default:            op = lex_cast;              break;
	}
	t = rvalue_type(t);
	MAKE_exp_op(t, op, a, NULL_exp, e);
	return e;
}


/*
    This routine adds an error to the end of err if the value qual returned
    by check_qualifier indicates that a particular conversion casts away
    const-ness (or volatile-ness).
*/

void
cast_away_const(unsigned qual, ERROR *err, unsigned cast)
{
	if (!(cast & CAST_CONST)) {
		CV_SPEC cv = cv_none;
		if (!(qual & QUAL_CONST)) {
			cv |= cv_const;
		}
		if (!(qual & QUAL_VOLATILE)) {
			cv |= cv_volatile;
		}
		if (cv == cv_none) {
			if (!(qual & QUAL_ALL_CONST)) {
				add_error(err, ERR_conv_qual_multi());
			}
		} else {
			add_error(err, ERR_conv_qual_cast(cv));
		}
	}
	return;
}


/*
    This routine creates a base cast expression for converting the
    expression a to type t using the offset off.  If off is a zero offset
    (indicating single inheritance) or the type of a can be statically
    determined then this is a simple add_ptr operation.  Otherwise a
    base_cast expression is used.  Note that a dummy expression is
    introduced to represent the argument.
*/

EXP
make_base_cast(TYPE t, EXP a, OFFSET off)
{
	EXP e;
	if (is_zero_offset(off) || know_type(a) == 1) {
		MAKE_exp_add_ptr(t, a, off, 0, e);
	} else {
		TYPE s = DEREF_type(exp_type(a));
		if (!IS_type_ptr(s)) {
			s = t;
		}
		MAKE_exp_dummy(s, a, LINK_NONE, NULL_off, 1, a);
		MAKE_exp_base_cast(t, CONV_PTR_BASE, a, off, e);
	}
	return e;
}


/*
    This routine converts the pointer expression a to the pointer type t.
    Pointers can be partitioned into pointer to object, pointer to function
    and void * for the purposes of pointer casts.  Note that even identity
    function casts are always performed.  This is to prevent further function
    overload resolution and to inherit any default arguments from t.  Also
    if force is true then an identity explicit cast is inserted after any
    base pointer cast.  This is to allow for TDF operations such as
    pointer_test which require exact equality of alignments.
*/

EXP
cast_ptr_ptr(TYPE t, EXP a, ERROR *err, unsigned cast, int safe, int force)
{
	EXP e;
	int opt;
	unsigned qual;
	OFFSET off = NULL_off;
	unsigned conv = CONV_NONE;
	TYPE s = DEREF_type(exp_type(a));
	TYPE pt = DEREF_type(type_ptr_sub(t));
	TYPE ps = DEREF_type(type_ptr_sub(s));
	unsigned nt = TAG_type(pt);
	unsigned ns = TAG_type(ps);

	/* Allow for tokenised types */
	if (nt == type_token_tag) {
		t = expand_type(t, 1);
		pt = DEREF_type(type_ptr_sub(t));
		nt = TAG_type(pt);
	}
	if (ns == type_token_tag) {
		s = expand_type(s, 1);
		ps = DEREF_type(type_ptr_sub(s));
		ns = TAG_type(ps);
	}

	/* Check for qualifier conversions */
	qual = check_qualifier(t, s, safe);
	if (qual == QUAL_EQUAL) {
		/* Allow for type equality */
		if (cast != CAST_IMPLICIT) {
			a = cast_exact(t, a);
		}
		return a;
	}
	if (qual == QUAL_EQ_FUNC) {
		/* Allow for equality of function types */
		if (!(cast & CAST_REINTERP) && !eq_except(ps, pt)) {
			add_error(err, ERR_except_spec_assign());
		}
		e = cast_exact(t, a);
		return e;
	}
	if (qual & QUAL_TEMPL) {
		/* Conversion depends on template parameter */
		e = cast_templ_type(t, a, cast);
		return e;
	}
	if (!(qual & QUAL_CONST)) {
		/* Check for string literal conversions */
		if (IS_exp_address(a) && ns == type_integer_tag) {
			EXP b = DEREF_exp(exp_address_arg(a));
			if (IS_exp_string_lit(b)) {
				/* Remove const and try again */
				int str = 1;
				if (!(cast & CAST_CONST)) {
					str = 2;
				}
				a = convert_array(b, str, err);
				e = cast_ptr_ptr(t, a, err, cast, safe, force);
				return e;
			}
		}
	}
	if (!(qual & QUAL_VOLATILE) && used_extern_volatile) {
		/* Check for implicitly volatile external objects */
		EXP pa = NULL_exp;
		DECL_SPEC ds = find_exp_linkage(a, &pa, 1);
		if (ds & dspec_implicit) {
			qual |= QUAL_VOLATILE;
		}
	}

	/* Check conversion */
	if (qual & QUAL_SIMILAR) {
		/* Simple qualification conversions */
		opt = OPT_none;
		conv = CONV_QUAL;
	} else {
		/* Other pointer conversions */
		ERROR ferr = NULL_err;
		switch (nt) {
		case type_top_tag:
		case type_bottom_tag:
generic_lab:
			if (ns == type_func_tag) {
				/* Conversion from 'function *' to 'void *' */
				ERROR err2 = ERR_expr_cast_reint_func_ptr(s, t);
				if (!IS_NULL_err(err2)) {
					e = cast_token(t, a, err, err2, cast);
					if (!IS_NULL_exp(e)) {
						return e;
					}
				}
			}
			if (ns == type_top_tag || ns == type_bottom_tag) {
				/* Conversion from 'void *' to 'void *' */
				opt = OPT_none;
				if (nt == type_integer_tag) {
					conv = (CONV_PTR_VOID | CONV_REVERSE);
				} else {
					conv = CONV_EXACT;
				}
			} else {
				/* Conversion from 'object *' to 'void *' */
				TYPE r = NULL_type;
				if (ns == type_integer_tag) {
					/* Check for generic pointers */
					r = type_void_star;
					r = type_composite(s, r, 1, 0, &ferr,
							   0);
				}
				if (!IS_NULL_type(r)) {
					opt = OPT_none;
				} else if (cast == CAST_IMPLICIT) {
					opt = OPT_conv_ptr_ptr_void;
				} else if (cast == CAST_CONST) {
					opt = OPT_error;
				} else {
					opt = OPT_none;
				}
				if (nt != type_integer_tag)conv = CONV_PTR_VOID;
			}
			break;
		case type_compound_tag: {
			if (cast == CAST_CONST || cast == CAST_REINTERP) {
				goto default_lab;
			}
			if (ns == type_compound_tag) {
				/* Conversion from 'class *' to 'class *' */
				GRAPH gr;
				CLASS_TYPE ct, cs;
				ct = DEREF_ctype(type_compound_defn(pt));
				cs = DEREF_ctype(type_compound_defn(ps));
				gr = find_base_class(cs, ct, 1);
				if (!IS_NULL_graph(gr)) {
					/* Base class conversion */
					ERROR err2 = check_ambig_base(gr);
					if (!IS_NULL_err(err2)) {
						/* Can't be ambiguous */
						e = cast_token(t, a, err, err2,
							       cast);
						if (!IS_NULL_exp(e)) {
							return e;
						}
						add_error(err, ERR_conv_ptr_ambiguous());
					}
					if (!(cast & CAST_BAD)) {
						/* Check base access */
						check_base_access(gr);
					}
					off = DEREF_off(graph_off(gr));
					conv = CONV_PTR_BASE;
					opt = OPT_none;
					break;
				}
				if (cast & CAST_STATIC) {
					gr = find_base_class(ct, cs, 1);
					if (!IS_NULL_graph(gr)) {
						/* Reverse base class
						 * conversion */
						ERROR err2 =
						    check_ambig_base(gr);
						if (!IS_NULL_err(err2)) {
							/* Can't be ambiguous */
							e = cast_token(t, a, err, err2, cast);
							if (!IS_NULL_exp(e)) {
								return e;
							}
							add_error(err, ERR_conv_ptr_ambiguous());
						}
						err2 = check_virt_base(gr);
						if (!IS_NULL_err(err2)) {
							/* Can't be virtual */
							e = cast_token(t, a, err, err2, cast);
							if (!IS_NULL_exp(e)) {
								return e;
							}
							add_error(err, ERR_expr_cast_stat_virt());
						}
						if (!(cast & CAST_BAD)) {
							/* Check base access */
							check_base_access(gr);
						}
						off = DEREF_off(graph_off(gr));
						conv = (CONV_PTR_BASE |
							CONV_REVERSE);
						opt = OPT_none;
						break;
					}
				}
			}
			goto default_lab;
		}
		case type_func_tag: {
			if (ns != type_func_tag) {
				/* Conversion from 'function *' to 'object *' */
				ERROR err2 = ERR_expr_cast_reint_func_ptr(t, s);
				if (!IS_NULL_err(err2)) {
					e = cast_token(t, a, err, err2, cast);
					if (!IS_NULL_exp(e)) {
						return e;
					}
				}
				goto object_lab;
			}
			/* Conversion from 'function *' to 'function *' */
			if (cast & CAST_REINTERP) {
				opt = OPT_conv_ptr_ptr_expl;
			} else {
				opt = OPT_conv_ptr_ptr_impl;
			}
			conv = CONV_FUNC;
			break;
		}
		case type_integer_tag: {
			/* Check for generic pointers */
			TYPE r = type_void_star;
			r = type_composite(t, r, 1, 0, &ferr, 0);
			if (!IS_NULL_type(r)) {
				goto generic_lab;
			}
			goto default_lab;
		}
		default:
default_lab:
			if (ns == type_func_tag) {
				/* Conversion from 'function *' to 'object *' */
				ERROR err2 = ERR_expr_cast_reint_func_ptr(s, t);
				if (!IS_NULL_err(err2)) {
					e = cast_token(t, a, err, err2, cast);
					if (!IS_NULL_exp(e)) {
						return e;
					}
				}
			}
			goto object_lab;
object_lab: {
			TYPE r = NULL_type;
			if (ns == type_integer_tag) {
				/* Check for generic pointers */
				r = type_void_star;
				r = type_composite(s, r, 1, 0, &ferr, 0);
			}
			if (IS_NULL_type(r)) {
				if (ns != type_top_tag &&
				    ns != type_bottom_tag) {
					/* Conversion from 'object *' to
					 * 'object *' */
					if (cast & CAST_REINTERP) {
						opt = OPT_conv_ptr_ptr_expl;
					} else {
						opt = OPT_conv_ptr_ptr_impl;
					}
					break;
				}
			}
			/* Conversion from 'void *' to 'object *' */
			if (cast == CAST_IMPLICIT) {
				opt = OPT_conv_ptr_void_ptr;
			} else if (cast == CAST_CONST) {
				opt = OPT_error;
			} else {
				opt = OPT_none;
			}
			if (IS_NULL_type(r)) {
				conv = (CONV_PTR_VOID | CONV_REVERSE);
			}
			break;
	    }
		}

		/* Add generic pointer errors */
		if (!IS_NULL_err(ferr)) {
			if (opt == OPT_none) {
				destroy_error(ferr, 1);
			} else {
				add_error(err, ferr);
			}
		}

		/* Check for function linkage conversions */
		if ((qual & QUAL_FUNC) && opt == OPT_conv_ptr_ptr_impl) {
			opt = OPT_func_linkage;
		}
	}

	/* Report any conversion errors */
	if (option(opt)) {
		ERROR err2;
		switch (opt) {
		case OPT_func_linkage: {
			err2 = ERR_dcl_link_conv();
			break;
		}
		case OPT_conv_ptr_ptr_expl:
		case OPT_conv_ptr_ptr_impl: {
			err2 = ERR_basic_link_incompat(ps, pt);
			err2 = concat_error(err2, ERR_conv_ptr_incompat());
			break;
		}
		default : {
			err2 = ERR_conv_ptr_cast(s, t);
			break;
		}
		}
		err2 = set_severity(err2, opt, 0);
		if (!IS_NULL_err(err2)) {
			e = cast_token(t, a, err, err2, cast);
			if (!IS_NULL_exp(e)) {
				return e;
			}
		}
	}
	if (qual != QUAL_OK) {
		cast_away_const(qual, err, cast);
	}

	/* Construct the result */
	if (IS_exp_null(a)) {
		/* Deal with null pointers */
		e = make_null_exp(t);
	} else if (conv == CONV_PTR_BASE) {
		/* Deal with base class conversions */
		e = make_base_cast(t, a, off);
		if (force) {
			/* Force pointer cast */
			conv = (CONV_PTR_PTR | CONV_REVERSE);
			MAKE_exp_cast(t, conv, e, e);
		}
	} else if (conv == (CONV_PTR_BASE | CONV_REVERSE)) {
		/* Deal with reverse base class conversions */
		MAKE_exp_cast(t, CONV_PTR_PTR, a, a);
		if (is_zero_offset(off)) {
			e = a;
		} else {
			MAKE_exp_dummy(t, a, LINK_NONE, NULL_off, 1, a);
			MAKE_exp_base_cast(t, conv, a, off, e);
			if (force) {
				/* Force pointer cast */
				conv = (CONV_PTR_PTR | CONV_REVERSE);
				MAKE_exp_cast(t, conv, e, e);
			}
		}
	} else {
		if (conv == CONV_NONE) {
			if (eq_type_offset(pt, ps)) {
				conv = CONV_PTR_PTR_ALIGN;
			} else {
				conv = CONV_PTR_PTR;
			}
		}
		MAKE_exp_cast(t, conv, a, e);
	}
	return e;
}


/*
    This routine converts the integral expression a to the pointer type t.
    There are two cases, depending on whether a represents a null pointer.
*/

static EXP
cast_int_ptr(TYPE t, EXP a, ERROR *err, unsigned cast, int nptr)
{
	EXP e;
	int opt;
	if (nptr && (cast == CAST_IMPLICIT || (cast & CAST_STATIC))) {
		/* Deal with null pointers */
		EXP b = make_null_ptr(a, t);
		if (!IS_NULL_exp(b)) {
			return b;
		}
	}
	if (cast & CAST_REINTERP) {
		opt = OPT_conv_int_ptr_expl;
	} else {
		opt = OPT_conv_int_ptr_impl;
	}
	if (option(opt)) {
		TYPE s = DEREF_type(exp_type(a));
		ERROR err2 = ERR_conv_ptr_nonzero(s, t);
		err2 = set_severity(err2, opt, 0);
		if (!IS_NULL_err(err2)) {
			e = cast_token(t, a, err, err2, cast);
			if (!IS_NULL_exp(e)) {
				return e;
			}
		}
	}
	MAKE_exp_cast(t, CONV_INT_PTR, a, e);
	return e;
}


/*
    This routine converts the pointer expression a to the integral type t
    (which will not be bool).
*/

static EXP
cast_ptr_int(TYPE t, EXP a, ERROR *err, unsigned cast)
{
	EXP e;
	int opt;
	if (IS_exp_null(a)) {
		if (cast & CAST_STATIC) {
			MAKE_exp_cast(t, CONV_NULL, a, e);
			return e;
		}
	}
	if (cast & CAST_REINTERP) {
		opt = OPT_conv_int_ptr_expl;
	} else {
		opt = OPT_conv_int_ptr_impl;
	}
	if (option(opt)) {
		TYPE s = DEREF_type(exp_type(a));
		ERROR err2 = ERR_expr_cast_reint_ptr_int(s, t);
		if (!IS_NULL_err(err2)) {
			e = cast_token(t, a, err, err2, cast);
			if (!IS_NULL_exp(e)) {
				return e;
			}
		}
	}
	MAKE_exp_cast(t, CONV_PTR_INT, a, e);
	return e;
}


/*
    This routine converts the pointer to member expression a to the pointer
    to member type t.  force is as in cast_ptr_ptr.
*/

EXP
cast_ptr_mem_ptr_mem(TYPE t, EXP a, ERROR *err, unsigned cast, int safe,
		     int force)
{
	EXP e;
	int ok = 2;
	unsigned conv = CONV_EXACT;
	TYPE s = DEREF_type(exp_type(a));

	if (cast != CAST_REINTERP) {
		/* Check for base class conversions */
		OFFSET off = NULL_off;
		CLASS_TYPE ct = DEREF_ctype(type_ptr_mem_of(t));
		CLASS_TYPE cs = DEREF_ctype(type_ptr_mem_of(s));
		if (!eq_ctype(ct, cs)) {
			GRAPH gr = find_base_class(ct, cs, 1);
			if (!IS_NULL_graph(gr)) {
				/* cs is a base class of ct */
				ERROR err2 = check_ambig_base(gr);
				if (!IS_NULL_err(err2)) {
					/* Can't be ambiguous */
					e = cast_token(t, a, err, err2, cast);
					if (!IS_NULL_exp(e)) {
						return e;
					}
					add_error(err, ERR_conv_mem_ambiguous());
				}
				err2 = check_virt_base(gr);
				if (!IS_NULL_err(err2)) {
					/* Can't be virtual */
					e = cast_token(t, a, err, err2, cast);
					if (!IS_NULL_exp(e)) {
						return e;
					}
					add_error(err, ERR_conv_mem_virtual());
				}
				if (!(cast & CAST_BAD)) {
					/* Check base access */
					check_base_access(gr);
				}
				off = DEREF_off(graph_off(gr));
				conv = CONV_PTR_MEM_BASE;
				ok = 1;
			} else {
				/* cs is not a base class of ct */
				if (cast & CAST_STATIC) {
					gr = find_base_class(cs, ct, 1);
					if (!IS_NULL_graph(gr)) {
						/* ct is a base class of cs */
						ERROR err2 = check_ambig_base(gr);
						if (!IS_NULL_err(err2)) {
							/* Can't be ambiguous */
							e = cast_token(t, a, err, err2, cast);
							if (!IS_NULL_exp(e)) {
								return e;
							}
							add_error(err, ERR_conv_mem_ambiguous());
						}
						err2 = check_virt_base(gr);
						if (!IS_NULL_err(err2)) {
							/* Can't be virtual */
							e = cast_token(t, a, err, err2, cast);
							if (!IS_NULL_exp(e)) {
								return e;
							}
							add_error(err, ERR_conv_mem_virtual());
						}
						if (!(cast & CAST_BAD)) {
							/* Check base access */
							check_base_access(gr);
						}
						off = DEREF_off(graph_off(gr));
						conv = (CONV_PTR_MEM_BASE | CONV_REVERSE);
						ok = 1;
					} else {
						ok = 0;
					}
				} else {
					ok = 0;
				}
			}

			if (ok == 0 && in_template_decl) {
				/* Allow for template parameter types */
				TYPE ft = DEREF_type(ctype_form(ct));
				TYPE fs = DEREF_type(ctype_form(cs));
				if (is_templ_depend(ft) ||
				    is_templ_depend(fs)) {
					/* Check further */
					ok = -1;
				}
			}
		}

		/* Check for qualification conversions */
		if (ok) {
			unsigned qual;
			TYPE pt = DEREF_type(type_ptr_mem_sub(t));
			TYPE ps = DEREF_type(type_ptr_mem_sub(s));
			if (IS_type_token(pt)) {
				t = expand_type(t, 1);
			}
			if (IS_type_token(ps)) {
				s = expand_type(s, 1);
			}
			qual = check_qualifier(t, s, safe);
			if (qual == QUAL_EQUAL) {
				/* Type equality */
				if (ok == 2) {
					if (cast != CAST_IMPLICIT) {
						a = cast_exact(t, a);
					}
					return a;
				}
				qual = QUAL_OK;
			} else if (qual == QUAL_EQ_FUNC) {
				/* Function type equality */
				if (!(cast & CAST_REINTERP) &&
				    !eq_except(ps, pt)) {
					/* Exception specifications don't
					 * match */
					add_error(err, ERR_except_spec_assign());
				}
				if (ok == 2) {
					e = cast_exact(t, a);
					return e;
				}
				qual = QUAL_OK;
			}
			if ((qual & QUAL_TEMPL) || ok == -1) {
				/* Conversion depends on template parameter */
				e = cast_templ_type(t, a, cast);
				return e;
			}
			if (qual & QUAL_SIMILAR) {
				/* Check for casting away const-ness */
				if (qual != QUAL_OK) {
					cast_away_const(qual, err, cast);
				}
				if (ok == 2) {
					MAKE_exp_cast(t, CONV_QUAL, a, e);
				} else {
					MAKE_exp_dummy(s, a, LINK_NONE, NULL_off, 1, a);
					MAKE_exp_base_cast(t, conv, a, off, e);
					UNUSED(force);
				}
				return e;
			}
			ok = 0;
		}
	}

	/* Check for reinterpret conversions */
	conv = CONV_NONE;
	if (cast & CAST_REINTERP) {
		unsigned nt = TAG_type(t);
		unsigned ns = TAG_type(s);
		if (nt == type_func_tag) {
			ok = (ns == type_func_tag ? 1 : 0);
		} else {
			ok = (ns == type_func_tag ? 0 : 1);
		}
		if (ok) {
			unsigned qual = check_qualifier(t, s, safe);
			if (qual != QUAL_OK) {
				cast_away_const(qual, err, cast);
			}
			conv = CONV_PTR_MEM_PTR_MEM;
		}
	}

	/* Invalid cast expression */
	if (!ok) {
		ERROR err2 = ERR_conv_mem_cast(s, t);
		if (!IS_NULL_err(err2)) {
			e = cast_token(t, a, err, err2, cast);
			if (!IS_NULL_exp(e)) {
				return e;
			}
		}
	}
	MAKE_exp_cast(t, conv, a, e);
	return e;
}


/*
    This routine converts the integral expression a to the pointer to
    member type t.  The only valid case is when a is zero.
*/

static EXP
cast_int_ptr_mem(TYPE t, EXP a, ERROR *err, unsigned cast, int nptr)
{
	EXP e;
	TYPE s;
	ERROR err2;
	if (nptr && (cast == CAST_IMPLICIT || (cast & CAST_STATIC))) {
		/* Deal with null pointers */
		EXP b = make_null_ptr(a, t);
		if (!IS_NULL_exp(b)) {
			return b;
		}
	}
	s = DEREF_type(exp_type(a));
	err2 = ERR_conv_mem_nonzero(s, t);
	if (!IS_NULL_err(err2)) {
		e = cast_token(t, a, err, err2, cast);
		if (!IS_NULL_exp(e)) {
			return e;
		}
	}
	MAKE_exp_cast(t, CONV_NONE, a, e);
	return e;
}


/*
    This routine converts the pointer to member expression a to the
    integral type t.  The only valid case is when a is a null pointer.
    In all other cases the null expression is returned.
*/

static EXP
cast_ptr_mem_int(TYPE t, EXP a, ERROR *err, unsigned cast)
{
	if (IS_exp_null(a)) {
		if (cast & CAST_STATIC) {
			EXP e;
			MAKE_exp_cast(t, CONV_NULL, a, e);
			return e;
		}
	}
	UNUSED(err);
	return NULL_exp;
}


/*
    This routine converts the pointer to member expression a to the
    pointer type t.  The only potentially valid case is casting a pointer
    to member function to a pointer to function.  In all other cases the
    null expression is returned.
*/

static EXP
cast_ptr_mem_ptr(TYPE t, EXP a, ERROR *err, unsigned cast)
{
	TYPE s = DEREF_type(exp_type(a));
	TYPE p = DEREF_type(type_ptr_mem_sub(s));
	TYPE q = DEREF_type(type_ptr_sub(t));
	if (IS_type_func(p) && IS_type_func(q)) {
		if (cast & CAST_REINTERP) {
			EXP e;
			ERROR err2 = ERR_expr_cast_reint_mem_func(s, t);
			if (!IS_NULL_err(err2)) {
				e = cast_token(t, a, err, err2, cast);
				if (!IS_NULL_exp(e)) {
					return e;
				}
			}
			MAKE_exp_cast(t, CONV_PTR_MEM_FUNC, a, e);
			return e;
		}
	}
	return NULL_exp;
}


/*
    This routine performs any base class conversion of the class object
    a to the class t.  ref is true if this is a reference binding.  The
    null expression is returned if no such conversion is possible.
*/

EXP
cast_class_class(TYPE t, EXP a, ERROR *err, unsigned cast, int ref)
{
	EXP e = NULL_exp;
	TYPE s = DEREF_type(exp_type(a));
	CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
	CLASS_TYPE cs = DEREF_ctype(type_compound_defn(s));
	if (eq_ctype(cs, ct)) {
		e = a;
	} else {
		GRAPH gr = find_base_class(cs, ct, 1);
		if (!IS_NULL_graph(gr)) {
			/* Allow for base class conversions */
			TYPE p;
			CV_SPEC cv = DEREF_cv(type_qual(s));
			OFFSET off = DEREF_off(graph_off(gr));
			ERROR err2 = check_ambig_base(gr);
			if (!IS_NULL_err(err2)) {
				e = cast_token(t, a, err, err2, cast);
				if (!IS_NULL_exp(e)) {
					return e;
				}
				add_error(err, ERR_dcl_init_ref_ambig());
			}
			check_base_access(gr);
			p = rvalue_type(t);
			MAKE_type_ptr(cv_none, p, p);
			if (!(cv & cv_lvalue)) {
				/* Introduce temporary if necessary */
				a = make_temporary(s, a, NULL_exp, 0, err);
			}
			MAKE_exp_address(p, a, e);
			e = make_base_cast(p, e, off);
			t = lvalue_type(t);
			MAKE_exp_indir(t, e, e);
		}
	}
	if (!IS_NULL_exp(e)) {
		if (ref) {
			/* Check cv-qualifiers */
			CV_SPEC cv = cv_compare(t, s);
			if (cv) {
				add_error(err, ERR_dcl_init_ref_qual(cv));
			}
		} else {
			e = convert_lvalue(e);
		}
		if (cast != CAST_IMPLICIT && err != KILL_err) {
			/* Can't have explicit cast in C */
			*err = concat_error(ERR_expr_cast_expl_scalar(t), *err);
		}
	}
	return e;
}


/*
    This routine constructs a cast expression for converting the expression
    a to the type t.  Any errors are added to the end of the position given
    by err.
*/

EXP
cast_exp(TYPE t, EXP a, ERROR *err, unsigned cast)
{
	TYPE s;
	CV_SPEC cv;
	unsigned ns;
	EXP e = NULL_exp;
	int usr = LANGUAGE_CPP;
	unsigned nt = TAG_type(t);

	/* Deal with tokenised types */
	if (nt == type_token_tag) {
		if (is_templ_type(t)) {
			e = cast_templ_type(t, a, cast);
			return e;
		}
		t = expand_type(t, 0);
		nt = TAG_type(t);
	}

	/* Deal with reference conversions */
	if (nt == type_ref_tag) {
		/* Transform 'cast <t&> (a)' to '*cast <t*> (&a)' */
		ERROR err2 = NULL_err;
		TYPE p = DEREF_type(type_ref_sub(t));
		if (is_templ_type(p)) {
			e = cast_templ_type(t, a, cast);
			return e;
		}
		p = rvalue_type(p);
		MAKE_type_ptr(cv_none, p, p);

		/* Construct the result */
		a = make_ref_object(a, &err2);
		s = DEREF_type(exp_type(a));
		if (IS_type_error(s)) {
			e = cast_exact(p, a);
		} else {
			e = cast_exp(p, a, &err2, cast);
		}
		if (!IS_NULL_err(err2)) {
			add_error(err, err2);
			add_error(err, ERR_expr_cast_ref(t, p));
		}
		e = cast_exact(t, e);
		return e;
	}

	/* Check user-defined conversion status */
	if (cast & CAST_STANDARD) {
		cast &= ~CAST_STANDARD;
		usr = 0;
	}

	/* Deal with function overloading */
	a = resolve_cast(t, a, err, 1, 0, NULL_list(IDENTIFIER));

	/* Deal with casting to void */
	if (nt == type_top_tag || nt == type_bottom_tag) {
		if (cast & CAST_STATIC) {
			a = make_discard_exp(a);
			MAKE_exp_cast(t, CONV_ELLIPSIS, a, e);
			return e;
		}
	}

	/* Find the operand type */
	s = DEREF_type(exp_type(a));
	ns = TAG_type(s);

	/* Check for template types */
	if (ns == type_token_tag && is_templ_type(s)) {
		e = cast_templ_type(t, a, cast);
		return e;
	}

	/* Deal with user-defined conversions */
	if (usr) {
		if (nt == type_compound_tag) {
			if (cast == CAST_IMPLICIT || (cast & CAST_STATIC)) {
				ERROR err2 = check_incomplete(t);
				if (!IS_NULL_err(err2)) {
					/* Can't have incomplete type */
					add_error(err, err2);
					add_error(err, ERR_expr_cast_invalid(s, t));
					e = make_null_exp(t);
					return e;
				}
				if (cast != CAST_IMPLICIT) {
					err2 = check_abstract(t);
					if (!IS_NULL_err(err2)) {
						/* Can't have abstract type */
						add_error(err, err2);
						add_error(err, ERR_class_abstract_cast());
					}
				}
				e = init_direct(t, a, err);
				return e;
			}
		}
		if (ns == type_compound_tag) {
			if (cast == CAST_IMPLICIT || (cast & CAST_STATIC)) {
				e = convert_conv(t, a, err, cast);
				return e;
			}
		}
	}

	/* Check for function casts */
#if LANGUAGE_CPP
	if (nt == type_func_tag && ns == type_func_tag) {
		if (cast & CAST_STATIC) {
			if (eq_type(t, s)) {
				add_error(err, ERR_expr_cast_stat_func(t));
				t = lvalue_type(t);
				MAKE_exp_cast(t, CONV_FUNC, a, e);
				return e;
			}
		}
	}
#endif

	/* Do lvalue conversion on conversion */
	a = convert_lvalue(a);
	s = DEREF_type(exp_type(a));
	ns = TAG_type(s);

	/* Deal with tokenised types */
	if (ns == type_token_tag) {
		s = expand_type(s, 0);
		ns = TAG_type(s);
	}

	/* Ignore any qualifiers for destination type */
	cv = DEREF_cv(type_qual(t));
	if (cv != cv_none) {
#if LANGUAGE_CPP
		if (nt != type_compound_tag) {
			cv = cv_none;
		}
		t = qualify_type(t, cv, 0);
#else
		t = qualify_type(t, cv_none, 0);
#endif
	}

	/* Deal with casting to bool */
	if (nt == type_integer_tag && check_int_type(t, btype_bool)) {
		if (ns == type_compound_tag) {
			/* User-defined conversions already handled */
			/* EMPTY */
		} else {
			if (cast == CAST_IMPLICIT || (cast & CAST_STATIC)) {
				e = convert_boolean(a, exp_paren_tag, err);
				return e;
			}
			if (cast == CAST_CONST && eq_type(s, t)) {
				return a;
			}
			ns = null_tag;
		}
	}

	/* Check simple conversions */
	switch (ns) {
	case type_integer_tag:
	case type_enumerate_tag:
integer_label:
		/* Conversion from integer */
		switch (nt) {
		case type_integer_tag:
		case type_bitfield_tag:
		case type_enumerate_tag: {
			e = cast_int_int(t, a, err, cast, -1);
			break;
		}
		case type_floating_tag: {
			e = cast_int_float(t, a, err, cast);
			break;
		}
		case type_ptr_tag: {
			e = cast_int_ptr(t, a, err, cast, 1);
			break;
		}
		case type_ptr_mem_tag: {
			e = cast_int_ptr_mem(t, a, err, cast, 1);
			break;
		}
		}
		break;
	case type_bitfield_tag: {
		/* Conversion from bitfield */
		switch (nt) {
		case type_integer_tag:
		case type_bitfield_tag:
		case type_enumerate_tag: {
			e = cast_int_int(t, a, err, cast, -1);
			break;
		}
		default : {
			TYPE r = find_bitfield_type(s);
			a = cast_int_int(r, a, err, cast, -1);
			goto integer_label;
		}
		}
		break;
	}
	case type_floating_tag: {
		/* Conversion from floating */
		switch (nt) {
		case type_integer_tag:
		case type_enumerate_tag: {
			e = cast_float_int(t, a, err, cast);
			break;
		}
		case type_bitfield_tag: {
			TYPE r = find_bitfield_type(t);
			a = cast_float_int(r, a, err, cast);
			e = cast_int_int(t, a, err, cast, -1);
			break;
		}
		case type_floating_tag: {
			e = cast_float_float(t, a, err, cast);
			break;
		}
		}
		break;
	}
	case type_ptr_tag: {
		/* Conversion from pointer */
		switch (nt) {
		case type_integer_tag:
		case type_enumerate_tag: {
			e = cast_ptr_int(t, a, err, cast);
			break;
		}
		case type_bitfield_tag: {
			TYPE r = find_bitfield_type(t);
			a = cast_ptr_int(r, a, err, cast);
			e = cast_int_int(t, a, err, cast, -1);
			break;
		}
		case type_ptr_tag: {
			e = cast_ptr_ptr(t, a, err, cast, 0, 0);
			break;
		}
		}
		break;
	}
	case type_ptr_mem_tag: {
		/* Conversion from pointer to member */
		switch (nt) {
		case type_integer_tag:
		case type_enumerate_tag: {
			e = cast_ptr_mem_int(t, a, err, cast);
			break;
		}
		case type_bitfield_tag: {
			TYPE r = find_bitfield_type(t);
			e = cast_ptr_mem_int(r, a, err, cast);
			a = cast_int_int(t, a, err, cast, -1);
			break;
		}
		case type_ptr_tag: {
			e = cast_ptr_mem_ptr(t, a, err, cast);
			break;
		}
		case type_ptr_mem_tag: {
			e = cast_ptr_mem_ptr_mem(t, a, err, cast, 0, 0);
			break;
		}
		}
		break;
	}
	case type_compound_tag: {
		if (nt == type_compound_tag && !usr) {
			e = cast_class_class(t, a, err, cast, 0);
		}
		break;
	}
	}

	if (IS_NULL_exp(e)) {
		if (cast != CAST_IMPLICIT) {
			switch (nt) {
			case type_func_tag:
			case type_array_tag:
			case type_token_tag:
			case type_compound_tag: {
				/* Cast to non-scalar type */
				add_error(err, ERR_expr_cast_expl_scalar(t));
				break;
			}
			}
		}
		if (ns == type_token_tag || nt == type_token_tag) {
			/* Allow for tokenised types */
			int ft = force_tokdef;
			int fs = force_template;
			if (cast != CAST_IMPLICIT) {
				force_tokdef = 0;
				force_template = 0;
			}
			if (eq_type_unqual(s, t)) {
				e = a;
			}
			force_template = fs;
			force_tokdef = ft;
		}
		if (IS_NULL_exp(e)) {
			/* No other conversions are allowed */
			if (ns == type_error_tag || nt == type_error_tag) {
				e = cast_exact(t, a);
			} else {
				ERROR err2 = check_incomplete(t);
				err2 = concat_error(err2, ERR_expr_cast_invalid(s, t));
				if (!IS_NULL_err(err2)) {
					e = cast_token(t, a, err, err2, cast);
					if (!IS_NULL_exp(e)) {
						return e;
					}
				}
				MAKE_exp_cast(t, CONV_NONE, a, e);
			}
		}
	}
	return e;
}


/*
    This routine constructs the simple cast expression '( t ) a'.  n gives
    the number of types defined in t.
*/

EXP
make_cast_exp(TYPE t, EXP a, int n)
{
	EXP e;
	ERROR err = NULL_err;
	unsigned conv = (unsigned)option_value(OPT_VAL_cast_explicit);
	report(crt_loc, ERR_expr_cast_expl_used());
	if (n) {
		report(crt_loc, ERR_expr_cast_expl_typedef());
	}
	a = convert_reference(a, REF_ASSIGN);
	e = cast_exp(t, a, &err, conv);
	if (!IS_NULL_err(err)) {
		err = concat_warning(err, ERR_expr_cast_expl_bad());
		report(crt_loc, err);
	}
	return e;
}


/*
    This routine constructs the static cast expression 'static_cast < t >
    ( a )'.  n gives the number of types defined in t.
*/

EXP
make_static_cast_exp(TYPE t, EXP a, int n)
{
	EXP e;
	ERROR err = NULL_err;
	if (n) {
		report(crt_loc, ERR_expr_cast_stat_typedef());
	}
	a = convert_reference(a, REF_ASSIGN);
	e = cast_exp(t, a, &err, CAST_STATIC);
	if (!IS_NULL_err(err)) {
		err = concat_warning(err, ERR_expr_cast_stat_bad());
		report(crt_loc, err);
	}
	return e;
}


/*
    This routine constructs the reinterpret cast expression 'reinterpret_cast
    < t > ( a )'.  n gives the number of types defined in t.
*/

EXP
make_reinterp_cast_exp(TYPE t, EXP a, int n)
{
	EXP e;
	ERROR err = NULL_err;
	if (n) {
		report(crt_loc, ERR_expr_cast_reint_typedef());
	}
	a = convert_reference(a, REF_ASSIGN);
	e = cast_exp(t, a, &err, CAST_REINTERP);
	if (!IS_NULL_err(err)) {
		err = concat_warning(err, ERR_expr_cast_reint_bad());
		report(crt_loc, err);
	}
	return e;
}


/*
    This routine constructs the const cast expression 'const_cast < t >
    ( a )'.  n gives the number of types defined in t.
*/

EXP
make_const_cast_exp(TYPE t, EXP a, int n)
{
	EXP e;
	ERROR err = NULL_err;
	if (n) {
		report(crt_loc, ERR_expr_cast_const_typedef());
	}
	a = convert_reference(a, REF_ASSIGN);
	e = cast_exp(t, a, &err, CAST_CONST);
	if (!IS_NULL_err(err)) {
		err = concat_warning(err, ERR_expr_cast_const_bad());
		report(crt_loc, err);
	}
	return e;
}


/*
    This routine constructs the new-style cast expression 'op < t > ( a )'.
    n gives the number of types defined in t.
*/

#if LANGUAGE_CPP

EXP
make_new_cast_exp(int op, TYPE t, EXP a, int n)
{
	EXP e;
	switch (op) {
	case lex_static_Hcast:      e = make_static_cast_exp  (t, a, n); break;
	case lex_reinterpret_Hcast: e = make_reinterp_cast_exp(t, a, n); break;
	case lex_const_Hcast:       e = make_const_cast_exp   (t, a, n); break;
	case lex_dynamic_Hcast:     e = make_dynamic_cast_exp (t, a, n); break;
	default:                    e = make_cast_exp         (t, a, n); break;
	}
	return e;
}

#endif


/*
    This routine constructs the function-style cast expression 't ( args )'.
    If args is a single argument, a, then this is identical to '( t ) a'.
    The expression 't ()' can be formed for any type, otherwise t must be
    a class type with a suitable constructor.
*/

EXP
make_func_cast_exp(TYPE t, LIST(EXP)args)
{
	EXP e;
	ERROR err = NULL_err;
	unsigned tag = TAG_type(t);
	unsigned len = LENGTH_list(args);

	/* Do reference conversions on arguments */
	args = convert_args(args);

	/* Check for template types */
	if (tag == type_token_tag && is_templ_type(t)) {
		MAKE_exp_opn(t, lex_cast, args, e);
		return e;
	}

	/* Check for class type with more than one argument */
	if (len > 1 && tag != type_compound_tag) {
		report(crt_loc, ERR_expr_type_conv_many(t));
		len = 1;
	}

	if (len == 1) {
		/* A single argument is the same as a normal cast */
		unsigned conv = (unsigned)option_value(OPT_VAL_cast_explicit);
		EXP a = DEREF_exp(HEAD_list(args));
		DESTROY_list(args, SIZE_exp);
		if (tag != type_compound_tag) {
			report(crt_loc, ERR_expr_cast_expl_used());
		}
		e = cast_exp(t, a, &err, conv);
		if (!IS_NULL_err(err)) {
			err = concat_warning(err, ERR_expr_type_conv_bad());
			report(crt_loc, err);
		}
		return e;
	}

	if (len == 0) {
		/* No arguments give a zero value */
		if (IS_type_top_etc(t)) {
			MAKE_exp_value(t, e);
		} else {
			err = check_complete(t);
			if (!IS_NULL_err(err)) {
				/* Can't cast to an incomplete type */
				err = concat_error(err, ERR_expr_type_conv_incompl());
				report(crt_loc, err);
			}
			if (IS_type_array(t)) {
				/* Can't use an array type */
				report(crt_loc, ERR_expr_type_conv_array(t));
			}
			err = check_abstract(t);
			if (!IS_NULL_err(err)) {
				/* Can't cast to an abstract type */
				err = concat_error(err, ERR_class_abstract_cast());
				report(crt_loc, err);
				err = NULL_err;
			}
			e = init_empty(t, cv_none, 1, &err);
			if (!IS_NULL_err(err)) {
				report(crt_loc, err);
			}
		}
		return e;
	}

	/* Now check constructor conversions */
	e = convert_constr(t, args, &err, CAST_STATIC);
	if (!IS_NULL_err(err)) {
		report(crt_loc, err);
	}
	return e;
}


/*
    Whenever a type conversion would raise an error this list of tokens
    is consulted to see if one of them could perform the conversion.
*/

static LIST(IDENTIFIER) conv_tokens = NULL_list(IDENTIFIER);


/*
    This routine enables the token id as a conversion token.
*/

void
allow_conversion(IDENTIFIER id)
{
	IDENTIFIER tid = resolve_token(id, "EE", 1);
	if (!IS_NULL_id(tid)) {
		CONS_id(tid, conv_tokens, conv_tokens);
	}
	return;
}


/*
    This routine checks whether the expression a can be converted to the
    type t using a conversion token.  If so it returns the appropriate
    token application.  Otherwise it returns the null expression.
*/

EXP
cast_token(TYPE t, EXP a, ERROR *err, ERROR err2, unsigned cast)
{
	EXP e = NULL_exp;
	int sev = ERR_NONE;
	if (!IS_NULL_err(err2)) {
		sev = DEREF_int(err_severity(err2));
	}
	if (sev == ERR_SERIOUS) {
		/* Only check illegal conversions */
		force_tokdef++;
		if (cast == CAST_IMPLICIT || (cast & CAST_STATIC)) {
			/* Scan through conversion tokens */
			TYPE s = DEREF_type(exp_type(a));
			LIST(IDENTIFIER)convs = conv_tokens;
			while (!IS_NULL_list(convs)) {
				IDENTIFIER id = DEREF_id(HEAD_list(convs));
				TOKEN tok = DEREF_tok(id_token_sort(id));
				if (IS_tok_func(tok)) {
					/* Function tokens */
					tok = func_proc_token(tok);
				}
				if (IS_tok_proc(tok)) {
					/* Procedure tokens */
					int d;
					TYPE p;
					TOKEN par;
					IDENTIFIER pid;
					LIST(IDENTIFIER)bids;
					LIST(IDENTIFIER)pids;

					/* Find result type */
					TOKEN res = DEREF_tok(tok_proc_res(tok));
					TYPE r = DEREF_type(tok_exp_type(res));

					/* Find parameter type */
					pids = DEREF_list(tok_proc_pids(tok));
					pid = DEREF_id(HEAD_list(pids));
					par = DEREF_tok(id_token_sort(pid));
					p = DEREF_type(tok_exp_type(par));

					/* Check conversion */
					bids = DEREF_list(tok_proc_bids(tok));
					d = save_token_args(bids, NULL_list(TOKEN));
					if (eq_type(s, p) && eq_type(t, r)) {
						LIST(TOKEN)args;
						ERROR err1 = ERR_token_conv(id, s, t);
						IGNORE define_exp_token(pid, a, 1);
						args = make_token_args(id, bids, &err1);
						e = apply_exp_token(id, args, 0);
						if (!IS_NULL_exp(e)) {
							IDENTIFIER fid;
							fid = DEREF_id(id_token_alt(id));
							use_func_id(fid, 0, 0);
							restore_token_args(bids, d);
							destroy_error(err2, 1);
							err2 = err1;
							break;
						}
						destroy_error(err1, 1);
					}
					restore_token_args(bids, d);
				}
				convs = TAIL_list(convs);
			}
		}
		force_tokdef--;
	}
	add_error(err, err2);
	return e;
}
