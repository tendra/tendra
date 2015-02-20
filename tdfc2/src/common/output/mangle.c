/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>

#include <shared/check.h>

#include "config.h"
#include "version.h"

#include "ustring.h"
#include "system.h"
#include "c_types.h"
#include "ctype_ops.h"
#include "etype_ops.h"
#include "exp_ops.h"
#include "flt_ops.h"
#include "ftype_ops.h"
#include "graph_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "itype_ops.h"
#include "nat_ops.h"
#include "nspace_ops.h"
#include "off_ops.h"
#include "tok_ops.h"
#include "type_ops.h"
#include "error.h"
#include "option.h"
#include "tdf.h"
#include "basetype.h"
#include "buffer.h"
#include "capsule.h"
#include "char.h"
#include "chktype.h"
#include "class.h"
#include "constant.h"
#include "copy.h"
#include "hash.h"
#include "lex.h"
#include "literal.h"
#include "mangle.h"
#include "operator.h"
#include "print.h"
#include "shape.h"
#include "syntax.h"
#include "template.h"
#include "tok.h"
#include "variable.h"
#include "xalloc.h"


/*
    This table gives the mangled forms of the built-in types.
*/

char mangle_ntype[ORDER_ntype][3] = {
	{ MANGLE_error,     0,            0 },	/* ntype_none */
	{ MANGLE_char,      0,            0 },	/* ntype_char */
	{ MANGLE_signed,    MANGLE_char,  0 },	/* ntype_schar */
	{ MANGLE_unsigned,  MANGLE_char,  0 },	/* ntype_uchar */
	{ MANGLE_short,     0,            0 },	/* ntype_sshort */
	{ MANGLE_unsigned,  MANGLE_short, 0 },	/* ntype_ushort */
	{ MANGLE_int,       0,            0 },	/* ntype_sint */
	{ MANGLE_unsigned,  MANGLE_int,   0 },	/* ntype_uint */
	{ MANGLE_long,      0,            0 },	/* ntype_slong */
	{ MANGLE_unsigned,  MANGLE_long,  0 },	/* ntype_ulong */
	{ MANGLE_llong,     0,            0 },	/* ntype_sllong */
	{ MANGLE_unsigned,  MANGLE_llong, 0 },	/* ntype_ullong */
	{ MANGLE_float,     0,            0 },	/* ntype_float */
	{ MANGLE_double,    0,            0 },	/* ntype_double */
	{ MANGLE_ldouble,   0,            0 },	/* ntype_ldouble */
	{ MANGLE_void,      0,            0 },	/* ntype_void */
	{ MANGLE_bottom,    0,            0 },	/* ntype_bottom */
	{ MANGLE_bool,      0,            0 },	/* ntype_bool */
	{ MANGLE_ptrdiff_t, 0,            0 },	/* ntype_ptrdiff_t */
	{ MANGLE_size_t,    0,            0 },	/* ntype_size_t */
	{ MANGLE_wchar_t,   0,            0 },	/* ntype_wchar_t */
	{ MANGLE_ellipsis,  0,            0 }	/* ntype_ellipsis */
};


/*
    The following flags are used to control the form of the mangled names.
*/

int mangle_objects = 1;
int mangle_signature = 1;
unsigned long mangle_length = ULONG_MAX;


/*
    A couple of forward declarations are necessary because of the
    recursive nature of many of the routines.
*/

static int nspace_depth(NAMESPACE);
static string mangle_op(int);
static string mangle_hashid(HASHID, int *, int);
static void mangle_exp(BUFFER *, EXP, int);
static void mangle_nat(BUFFER *, NAT, int);
static void mangle_nspace(BUFFER *, NAMESPACE, int);
static void mangle_ctype(BUFFER *, CLASS_TYPE, int);
static void mangle_token(BUFFER *, IDENTIFIER, LIST(TOKEN), int, int);
static void mangle_type(BUFFER *, TYPE, int, int);


/*
    This variable is used to hold the parent class of an identifier during
    name mangling.
*/

static CLASS_TYPE crt_mangle_class = NULL_ctype;


/*
    This routine finds the depth of the identifier id.  This is one more
    than the depth of the enclosing namespace if id is a simple identifier
    and -1 otherwise.
*/

static int
ident_depth(IDENTIFIER id)
{
	if (!IS_NULL_id(id)) {
		HASHID nm = DEREF_hashid(id_name(id));
		if (!IS_hashid_anon(nm)) {
			/* Simple identifiers */
			NAMESPACE ns = DEREF_nspace(id_parent(id));
			int n = nspace_depth(ns);
			if (n >= 0) {
				return n + 1;
			}
		}
	}
	return -1;
}


/*
    This routine finds the depth of the namespace ns - that is the number
    of namespaces lying between it and its enclosing global namespace.
    The routine returns -1 if any intermediate namespace is unnamed.
*/

static int
nspace_depth(NAMESPACE ns)
{
	if (!IS_NULL_nspace(ns)) {
		switch (TAG_nspace(ns)) {
		case nspace_named_tag:
		case nspace_ctype_tag: {
			/* Named and class namespaces */
			IDENTIFIER id = DEREF_id(nspace_name(ns));
			int n = ident_depth(id);
			return n;
		}
		case nspace_global_tag: {
			/* The global namespace */
			return 0;
		}
		case nspace_unnamed_tag: {
			/* Unnamed namespaces */
			if (output_all) {
				IDENTIFIER id = DEREF_id(nspace_name(ns));
				NAMESPACE pns = DEREF_nspace(id_parent(id));
				int n = nspace_depth(pns);
				if (n >= 0) {
					return n + 1;
				}
			}
			break;
		}
		}
	}
	return -1;
}


/*
    This buffer is used to build up the mangled names.
*/

BUFFER mangle_buff = NULL_buff;
static BUFFER name_buff = NULL_buff;


/*
    This routine adds the number n to the buffer position given by bf.
*/

static void
mangle_number(BUFFER *bf, unsigned long n, int e)
{
	if (n < 10) {
		int d = '0' + (int)n;
		bfputc(bf, d);
	} else {
		if (e > 1) {
			bfputc(bf, MANGLE_sep);
		}
		bfprintf(bf, "%lu", n);
		if (e > 0) {
			bfputc(bf, MANGLE_sep);
		}
	}
	return;
}


/*
    This routine adds the mangled form of the identifier id to the buffer
    position given by bf.  d gives the associated identifier depth.
*/

static void
mangle_id(BUFFER *bf, IDENTIFIER id, int d)
{
	if (d >= 0) {
		int copy = 0;
		HASHID nm = DEREF_hashid(id_name(id));
		string s = mangle_hashid(nm, &copy, 1);
		if (s) {
			unsigned long n = (unsigned long)ustrlen(s);
			if (d > 1) {
				/* Output name qualifier */
				NAMESPACE ns = DEREF_nspace(id_parent(id));
				bfputc(bf, MANGLE_qual);
				mangle_number(bf,(unsigned long)d, 2);
				mangle_nspace(bf, ns, d - 1);
			}
			mangle_number(bf, n, 0);
			bfputs(bf, s);
		} else {
			/* Invalid identifier */
			bfputc(bf, MANGLE_error);
		}
	} else {
		/* Invalid identifier */
		bfputc(bf, MANGLE_error);
	}
	return;
}


/*
    This routine adds the mangled form of the name of the namespace ns
    to the buffer position given by bf.  d gives the associated namespace
    depth.
*/

static void
mangle_nspace(BUFFER *bf, NAMESPACE ns, int d)
{
	if (!IS_nspace_global(ns)) {
		IDENTIFIER id = DEREF_id(nspace_name(ns));
		if (IS_id_class_name(id)) {
			TYPE t = DEREF_type(id_class_name_defn(id));
			if (IS_type_compound(t)) {
				CLASS_TYPE ct =
				    DEREF_ctype(type_compound_defn(t));
				mangle_ctype(bf, ct, d);
				return;
			}
		}
		mangle_id(bf, id, d);
	}
	return;
}


/*
    This routine adds the binary expression operation 'a op b' to the
    buffer position given by bf.
*/

static void
mangle_exp_op(BUFFER *bf, int op, EXP a, EXP b, int n, int rec)
{
	string s = mangle_op(op);
	bfputc(bf, MANGLE_op);
	bfprintf(bf, "%s%d", s + 2, n);
	if (!IS_NULL_exp(a)) {
		mangle_exp(bf, a, rec);
	}
	if (!IS_NULL_exp(b)) {
		mangle_exp(bf, b, rec);
	}
	return;
}


/*
    This routine adds the expression e to the buffer position given by bf.
*/

static void
mangle_exp(BUFFER *bf, EXP e, int rec)
{
	if (!IS_NULL_exp(e)) {
		assert(ORDER_exp == 88);
		switch (TAG_exp(e)) {
		case exp_identifier_tag:
		case exp_member_tag:
		case exp_ambiguous_tag:
		case exp_undeclared_tag: {
			/* Identifier expressions */
			IDENTIFIER id = DEREF_id(exp_identifier_etc_id(e));
			int d = ident_depth(id);
			bfputc(bf, MANGLE_sep);
			mangle_id(bf, id, d);
			break;
		}
		case exp_int_lit_tag: {
			/* Integer literals */
			NAT n = DEREF_nat(exp_int_lit_nat(e));
			mangle_nat(bf, n, rec);
			break;
		}
		case exp_char_lit_tag: {
			/* Character literals */
			STRING s = DEREF_str(exp_char_lit_str(e));
			NAT n = eval_char_lit(s);
			mangle_nat(bf, n, rec);
			break;
		}
		case exp_float_lit_tag: {
			/* Floating-point literals */
			FLOAT flt = DEREF_flt(exp_float_lit_flt(e));
			string i = DEREF_string(flt_simple_int_part(flt));
			string d = DEREF_string(flt_simple_frac_part(flt));
			NAT n = DEREF_nat(flt_simple_exponent(flt));
			bfputc(bf, MANGLE_op);
			bfprintf(bf, "f%sd%s", i, d);
			if (is_zero_nat(n)) {
				bfputc(bf, MANGLE_sep);
			} else {
				bfputc(bf, 'e');
				mangle_nat(bf, n, 0);
			}
			break;
		}
		case exp_null_tag:
		case exp_zero_tag:
		case exp_value_tag: {
			/* Null pointers */
			mangle_nat(bf, small_nat[0], 0);
			break;
		}
		case exp_paren_tag:
		case exp_copy_tag: {
			/* Parenthesised expressions */
			EXP a = DEREF_exp(exp_paren_etc_arg(e));
			mangle_exp(bf, a, rec);
			break;
		}
		case exp_indir_tag: {
			/* Indirection expressions */
			EXP a = DEREF_exp(exp_indir_ptr(e));
			mangle_exp(bf, a, rec);
			break;
		}
		case exp_address_tag: {
			/* Address expressions */
			EXP a = DEREF_exp(exp_address_arg(e));
			mangle_exp(bf, a, rec);
			break;
		}
		case exp_address_mem_tag: {
			/* Address expressions */
			EXP a = DEREF_exp(exp_address_mem_arg(e));
			mangle_exp(bf, a, rec);
			break;
		}
		case exp_negate_tag:
		case exp_compl_tag:
		case exp_not_tag:
		case exp_abs_tag: {
			/* Unary expressions */
			int op = op_token(e, lex_unknown);
			EXP a = DEREF_exp(exp_negate_etc_arg(e));
			mangle_exp_op(bf, op, a, NULL_exp, 1, rec);
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
			/* Binary expressions */
			int op = op_token(e, lex_unknown);
			EXP a = DEREF_exp(exp_plus_etc_arg1(e));
			EXP b = DEREF_exp(exp_plus_etc_arg2(e));
			mangle_exp_op(bf, op, a, b, 2, rec);
			break;
		}
		case exp_test_tag: {
			/* Test expressions */
			int op = op_token(e, lex_unknown);
			EXP a = DEREF_exp(exp_test_arg(e));
			mangle_exp_op(bf, op, a, NULL_exp, 1, rec);
			break;
		}
		case exp_compare_tag: {
			/* Comparison expressions */
			int op = op_token(e, lex_unknown);
			EXP a = DEREF_exp(exp_compare_arg1(e));
			EXP b = DEREF_exp(exp_compare_arg2(e));
			mangle_exp_op(bf, op, a, b, 2, rec);
			break;
		}
		case exp_cast_tag: {
			/* Cast expressions */
			EXP a = DEREF_exp(exp_cast_arg(e));
			mangle_exp(bf, a, rec);
			break;
		}
		case exp_base_cast_tag: {
			/* Base cast expressions */
			EXP a = DEREF_exp(exp_base_cast_arg(e));
			mangle_exp(bf, a, rec);
			break;
		}
		case exp_add_ptr_tag: {
			/* Pointer addition */
			EXP a = DEREF_exp(exp_add_ptr_ptr(e));
			/* NOT YET IMPLEMENTED */
			mangle_exp(bf, a, rec);
			break;
		}
		case exp_offset_size_tag: {
			/* Offset size */
			OFFSET a = DEREF_off(exp_offset_size_off(e));
			if (IS_off_type(a)) {
				/* Allow for sizeof expressions */
				TYPE s = DEREF_type(exp_offset_size_step(e));
				if (EQ_type(s, type_char)) {
					int op = lex_sizeof;
					mangle_exp_op(bf, op, NULL_exp,
						      NULL_exp, 1, rec);
					s = DEREF_type(off_type_type(a));
					mangle_type(bf, s, 2, 1);
					break;
				}
			}
			/* NOT YET IMPLEMENTED */
			bfputc(bf, MANGLE_error);
			break;
		}
		case exp_comma_tag: {
			/* Comma expressions */
			LIST(EXP)p = DEREF_list(exp_comma_args(e));
			while (!IS_NULL_list(p)) {
				EXP a = DEREF_exp(HEAD_list(p));
				p = TAIL_list(p);
				if (IS_NULL_list(p)) {
					mangle_exp(bf, a, rec);
				} else {
					mangle_exp_op(bf, lex_comma, a,
						      NULL_exp, 2, rec);
				}
			}
			break;
		}
		case exp_if_stmt_tag: {
			/* Conditional expressions */
			EXP c = DEREF_exp(exp_if_stmt_cond(e));
			EXP a = DEREF_exp(exp_if_stmt_true_code(e));
			EXP b = DEREF_exp(exp_if_stmt_false_code(e));
			mangle_exp_op(bf, lex_cond_Hop, c, a, 3, rec);
			mangle_exp(bf, b, rec);
			break;
		}
		case exp_rtti_type_tag: {
			/* Run-time type information expressions */
			TYPE s = DEREF_type(exp_rtti_type_arg(e));
			int op = DEREF_int(exp_rtti_type_op(e));
			mangle_exp_op(bf, op, NULL_exp, NULL_exp, 1, rec);
			mangle_type(bf, s, 2, 1);
			break;
		}
		case exp_token_tag: {
			/* Tokenised expressions */
			IDENTIFIER id = DEREF_id(exp_token_tok(e));
			LIST(TOKEN)args = DEREF_list(exp_token_args(e));
			mangle_token(bf, id, args, -2, 1);
			break;
		}
		case exp_location_tag: {
			/* Location expressions */
			EXP a = DEREF_exp(exp_location_arg(e));
			mangle_exp(bf, a, rec);
			break;
		}
		case exp_dummy_tag: {
			/* Dummy expressions */
			EXP a = DEREF_exp(exp_dummy_value(e));
			mangle_exp(bf, a, rec);
			break;
		}
		default: {
			bfputc(bf, MANGLE_error);
			break;
		}
		}
	}
	return;
}


/*
    This routine adds the integer constant n to the buffer position given
    by bf.
*/

static void
mangle_nat(BUFFER *bf, NAT n, int rec)
{
	if (IS_NULL_nat(n)) {
		bfputc(bf, MANGLE_sep);
	} else {
		unsigned tag = TAG_nat(n);
		if (tag == nat_neg_tag) {
			/* Negative values */
			bfputc(bf, MANGLE_neg);
			n = DEREF_nat(nat_neg_arg(n));
			tag = TAG_nat(n);
		}
		switch (tag) {
		case nat_calc_tag: {
			/* Calculated values */
			EXP e = DEREF_exp(nat_calc_value(n));
			if (rec) {
				e = eval_exp(e, 1);
			}
			mangle_exp(bf, e, 0);
			break;
		}
		case nat_token_tag: {
			/* Tokenised values */
			IDENTIFIER id = DEREF_id(nat_token_tok(n));
			LIST(TOKEN)args = DEREF_list(nat_token_args(n));
			mangle_token(bf, id, args, -2, 1);
			break;
		}
		default: {
			/* Simple values */
			unsigned long v = get_nat_value(n);
			if (v == EXTENDED_MAX) {
				/* Really large values */
				IGNORE print_nat(n, 0, bf, 0);
			} else {
				mangle_number(bf, v, 0);
			}
			bfputc(bf, MANGLE_sep);
			break;
		}
		}
	}
	return;
}


/*
    This routine finds the mangled form of the integer literal type it.
*/

string
mangle_literal(INT_TYPE it)
{
	static character buff[20];
	string s = buff;
	int form = DEREF_int(itype_literal_form(it));
	int suff = DEREF_int(itype_literal_suff(it));
	*(s++) = MANGLE_literal;
	if (form == BASE_OCTAL) {
		*(s++) = MANGLE_octal;
	} else if (form == BASE_HEXADECIMAL) {
		*(s++) = MANGLE_hex;
	}
	if (suff & SUFFIX_U) {
		*(s++) = MANGLE_unsigned;
	}
	if (suff & SUFFIX_L) {
		*(s++) = MANGLE_long;
	}
	if (suff & SUFFIX_LL) {
		*(s++) = MANGLE_llong;
	}
	*s = 0;
	return buff;
}


/*
    This routine adds the mangled form of the integral type it to the
    buffer position given by bf.
*/

static void
mangle_itype(BUFFER *bf, INT_TYPE it)
{
	switch (TAG_itype(it)) {
	case itype_basic_tag: {
		/* Basic integral types */
		BUILTIN_TYPE n = DEREF_ntype(itype_basic_no(it));
		bfputs(bf, ustrlit(mangle_ntype[n]));
		break;
	}
	case itype_bitfield_tag: {
		/* Bitfield types */
		TYPE s = DEREF_type(itype_bitfield_sub(it));
		NAT n = DEREF_nat(itype_bitfield_size(it));
		BASE_TYPE rep = DEREF_btype(itype_bitfield_rep(it));
		bfputc(bf, MANGLE_bitfield);
		mangle_nat(bf, n, 1);
		if (rep & btype_signed) {
			bfputc(bf, MANGLE_signed);
			if (rep & btype_char) {
				s = type_char;
			}
		}
		mangle_type(bf, s, 2, 1);
		break;
	}
	case itype_promote_tag: {
		/* Promotion types */
		INT_TYPE is = DEREF_itype(itype_promote_arg(it));
		bfputc(bf, MANGLE_promote);
		mangle_itype(bf, is);
		break;
	}
	case itype_arith_tag: {
		/* Arithmetic types */
		INT_TYPE is = DEREF_itype(itype_arith_arg1(it));
		INT_TYPE ir = DEREF_itype(itype_arith_arg2(it));
		bfputc(bf, MANGLE_arith);
		mangle_itype(bf, is);
		mangle_itype(bf, ir);
		break;
	}
	case itype_literal_tag: {
		/* Literal types */
		NAT n = DEREF_nat(itype_literal_nat(it));
		string s = mangle_literal(it);
		bfputs(bf, s);
		mangle_nat(bf, n, 1);
		break;
	}
	case itype_token_tag: {
		/* Tokenised types */
		BUILTIN_TYPE n = DEREF_ntype(itype_unprom(it));
		if (n == ntype_none || n == ntype_ellipsis) {
			IDENTIFIER id;
			LIST(TOKEN)args;
			id = DEREF_id(itype_token_tok(it));
			args = DEREF_list(itype_token_args(it));
			mangle_token(bf, id, args, -2, 0);
		} else {
			bfputc(bf, MANGLE_promote);
			bfputs(bf, ustrlit(mangle_ntype[n]));
		}
		break;
	}
	}
	return;
}


/*
    This routine adds the mangled form of the floating-point type ft to
    the buffer position given by bf.
*/

static void
mangle_ftype(BUFFER *bf, FLOAT_TYPE ft)
{
	switch (TAG_ftype(ft)) {
	case ftype_basic_tag: {
		/* Basic floating types */
		BUILTIN_TYPE n = DEREF_ntype(ftype_basic_no(ft));
		bfputs(bf, ustrlit(mangle_ntype[n]));
		break;
	}
	case ftype_arg_promote_tag: {
		/* Promotion types */
		FLOAT_TYPE fs = DEREF_ftype(ftype_arg_promote_arg(ft));
		bfputc(bf, MANGLE_promote);
		mangle_ftype(bf, fs);
		break;
	}
	case ftype_arith_tag: {
		/* Arithmetic types */
		FLOAT_TYPE fs = DEREF_ftype(ftype_arith_arg1(ft));
		FLOAT_TYPE fr = DEREF_ftype(ftype_arith_arg2(ft));
		bfputc(bf, MANGLE_arith);
		mangle_ftype(bf, fs);
		mangle_ftype(bf, fr);
		break;
	}
	case ftype_token_tag: {
		/* Tokenised types */
		IDENTIFIER id = DEREF_id(ftype_token_tok(ft));
		LIST(TOKEN)args = DEREF_list(ftype_token_args(ft));
		mangle_token(bf, id, args, -2, 0);
		break;
	}
	}
	return;
}


/*
    This routine adds the mangled form of the cv-qualifiers cv to the
    buffer position given by bf.  Note that this mangling scheme maps
    'volatile unsigned char *' to 'PVUc' rather than the ARM's 'PUVc'.
*/

static void
mangle_cv(BUFFER *bf, CV_SPEC cv)
{
	if (cv & cv_const) {
		bfputc(bf, MANGLE_const);
	}
	if (cv & cv_volatile) {
		bfputc(bf, MANGLE_volatile);
	}
	if (cv & cv_c) {
		bfputc(bf, MANGLE_c_lang);
	}
	return;
}


/*
    This routine adds the mangled form of the name of the type t to the
    buffer position given by bf.  The printing of function types (for
    example whether the return type is included) is controlled by fn
    and that of array types by arr.
*/

static void
mangle_type(BUFFER *bf, TYPE t, int fn, int arr)
{
	/* Output cv-qualifier */
	CV_SPEC qual = DEREF_cv(type_qual(t));
	mangle_cv(bf, qual);

	/* Output main type information */
	switch (TAG_type(t)) {
	case type_integer_tag: {
		/* Integral types */
		INT_TYPE it = DEREF_itype(type_integer_rep(t));
		mangle_itype(bf, it);
		break;
	}
	case type_floating_tag: {
		/* Floating-point types */
		FLOAT_TYPE ft = DEREF_ftype(type_floating_rep(t));
		mangle_ftype(bf, ft);
		break;
	}
	case type_top_tag: {
		/* Top type */
		bfputc(bf, MANGLE_void);
		break;
	}
	case type_bottom_tag: {
		/* Bottom type */
		bfputc(bf, MANGLE_bottom);
		break;
	}
	case type_ptr_tag: {
		/* Pointer types */
		bfputc(bf, MANGLE_ptr);
		t = DEREF_type(type_ptr_sub(t));
		mangle_type(bf, t, 2, 1);
		break;
	}
	case type_ref_tag: {
		/* Reference types */
		bfputc(bf, MANGLE_ref);
		t = DEREF_type(type_ref_sub(t));
		mangle_type(bf, t, 2, 1);
		break;
	}
	case type_ptr_mem_tag: {
		/* Pointer to member types */
		CLASS_TYPE ct = DEREF_ctype(type_ptr_mem_of(t));
		bfputc(bf, MANGLE_ptr_mem);
		mangle_ctype(bf, ct, -2);
		t = DEREF_type(type_ptr_mem_sub(t));
		mangle_type(bf, t, 2, 1);
		break;
	}
	case type_func_tag: {
		/* Function types */
		LIST(TYPE)p = DEREF_list(type_func_ptypes(t));
		int ell = DEREF_int(type_func_ellipsis(t));

		/* Include any cv-qualifiers */
		qual = DEREF_cv(type_func_mqual(t));
		mangle_cv(bf, qual);

		/* Include parameter types */
		if (fn) {
			bfputc(bf, MANGLE_func);
		}
		if (IS_NULL_list(p)) {
			if (fn && !ell) {
				bfputc(bf, MANGLE_void);
			}
		} else {
			LIST(TYPE)q = p;
			unsigned left = LENGTH_list(q);
			while (!IS_NULL_list(q)) {
				int worth = 1;
				unsigned long n = 0;
				TYPE r = DEREF_type(HEAD_list(q));
				switch (TAG_type(r)) {
				case type_integer_tag:
				case type_floating_tag: {
					/* Only check for long runs */
					if (left > MANGLE_WORTH) {
						worth = 0;
						goto default_lab;
					}
					break;
				}
				case type_top_tag:
				case type_bottom_tag:
				case type_error_tag: {
					/* Don't bother in these cases */
					break;
				}
				default:
default_lab: {
		     /* Check previous parameter types */
		     unsigned long m = 1;
		     LIST(TYPE)q1 = p;
		     while (!EQ_list(q1, q)) {
			     TYPE r1 = DEREF_type(HEAD_list(q1));
			     if (eq_type(r1, r)) {
				     /* Match found */
				     n = m;
				     break;
			     }
			     q1 = TAIL_list(q1);
			     m++;
		     }
		     break;
	     }
				}
				if (n) {
					/* Previous match found */
					TYPE nr;
					unsigned long m = 0;
					do {
						/* Step over equal parameters */
						m++;
						left--;
						q = TAIL_list(q);
						if (IS_NULL_list(q)) {
							break;
						}
						nr = DEREF_type(HEAD_list(q));
					} while (eq_type(r, nr));
					if (m == 1) {
						/* Single equal parameter */
						if (worth) {
							bfputc(bf,
							       MANGLE_repeat);
							mangle_number(bf, n, 2);
						} else {
							mangle_type(bf, r, 2,
								    1);
						}
					} else {
						/* Multiple equal parameters */
						if (worth || m > MANGLE_WORTH) {
							bfputc(bf,
							       MANGLE_multi);
							mangle_number(bf, m, 2);
							mangle_number(bf, n, 1);
						} else {
							while (m) {
								mangle_type(bf, r, 2, 1);
								m--;
							}
						}
					}
				} else {
					/* No previous match found */
					mangle_type(bf, r, 2, 1);
					left--;
					q = TAIL_list(q);
				}
			}
		}
		if (ell) {
			bfputc(bf, MANGLE_ellipsis);
		}

		/* Include return type if necessary */
		if (fn == 2) {
			t = DEREF_type(type_func_ret(t));
			bfputc(bf, MANGLE_sep);
			mangle_type(bf, t, 2, 1);
		}
		break;
	}
	case type_array_tag: {
		/* Array types */
		NAT n = NULL_nat;
		if (arr) {
			n = DEREF_nat(type_array_size(t));
		}
		bfputc(bf, MANGLE_array);
		mangle_nat(bf, n, 1);
		t = DEREF_type(type_array_sub(t));
		mangle_type(bf, t, 2, 1);
		break;
	}
	case type_bitfield_tag: {
		/* Bitfield types */
		INT_TYPE it = DEREF_itype(type_bitfield_defn(t));
		mangle_itype(bf, it);
		break;
	}
	case type_compound_tag: {
		/* Class types */
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		mangle_ctype(bf, ct, -2);
		break;
	}
	case type_enumerate_tag: {
		/* Enumeration types */
		ENUM_TYPE et = DEREF_etype(type_enumerate_defn(t));
#if LANGUAGE_C
		t = DEREF_type(etype_rep(et));
		mangle_type(bf, t, fn, arr);
#else
		IDENTIFIER eid = DEREF_id(etype_name(et));
		int d = ident_depth(eid);
		mangle_id(bf, eid, d);
#endif
		break;
	}
	case type_token_tag: {
		/* Tokenised types */
		IDENTIFIER id = DEREF_id(type_token_tok(t));
		LIST(TOKEN)args = DEREF_list(type_token_args(t));
		mangle_token(bf, id, args, -2, 0);
		break;
	}
	case type_templ_tag: {
		/* Template types */
		t = DEREF_type(type_templ_defn(t));
		mangle_type(bf, t, fn, arr);
		break;
	}
	default: {
		/* Illegal types */
		bfputc(bf, MANGLE_error);
		break;
	}
	}
	return;
}


/*
    This routine adds the mangled form of the class type ct to the
    buffer position given by bf.
*/

static void
mangle_ctype(BUFFER *bf, CLASS_TYPE ct, int d)
{
	CLASS_TYPE cs = crt_mangle_class;
	if (!IS_NULL_ctype(cs) && eq_ctype(ct, cs)) {
		bfputc(bf, MANGLE_self);
	} else {
		TYPE t = DEREF_type(ctype_form(ct));
		if (!IS_NULL_type(t) && IS_type_token(t)) {
			IDENTIFIER tid = DEREF_id(type_token_tok(t));
			LIST(TOKEN)args = DEREF_list(type_token_args(t));
			mangle_token(bf, tid, args, d, 0);
		} else {
			IDENTIFIER cid = DEREF_id(ctype_name(ct));
			if (d == -2) {
				d = ident_depth(cid);
			}
			mangle_id(bf, cid, d);
		}
	}
	return;
}


/*
    This routine adds the mangled form of the base class graph gr to the
    buffer bf.  first is true for the top node.
*/

static void
mangle_graph(BUFFER *bf, GRAPH gr)
{
	int d = -2;
	GRAPH gu = DEREF_graph(graph_up(gr));
	CLASS_TYPE ct = DEREF_ctype(graph_head(gr));
	if (!IS_NULL_graph(gu)) {
		mangle_graph(bf, gu);
		d = 1;
	}
	mangle_ctype(bf, ct, d);
	return;
}


/*
    This routine adds the mangled form of the token argument tok to the
    buffer position given by bf.
*/

static void
mangle_token_arg(BUFFER *bf, TOKEN tok)
{
	if (!IS_NULL_tok(tok)) {
		switch (TAG_tok(tok)) {
		case tok_exp_tag: {
			EXP e = DEREF_exp(tok_exp_value(tok));
			TYPE t = DEREF_type(tok_exp_type(tok));
			mangle_type(bf, t, 2, 1);
			mangle_exp(bf, e, 1);
			break;
		}
		case tok_stmt_tag: {
			EXP e = DEREF_exp(tok_stmt_value(tok));
			bfputc(bf, MANGLE_stmt);
			mangle_exp(bf, e, 1);
			break;
		}
		case tok_nat_tag: {
			NAT n = DEREF_nat(tok_nat_value(tok));
			bfputc(bf, MANGLE_nat);
			mangle_nat(bf, n, 1);
			break;
		}
		case tok_snat_tag: {
			NAT n = DEREF_nat(tok_snat_value(tok));
			bfputc(bf, MANGLE_nat);
			mangle_nat(bf, n, 1);
			break;
		}
		case tok_type_tag: {
			TYPE t = DEREF_type(tok_type_value(tok));
			bfputc(bf, MANGLE_type);
			mangle_type(bf, t, 2, 1);
			break;
		}
		case tok_class_tag: {
			IDENTIFIER id = DEREF_id(tok_class_value(tok));
			int d = ident_depth(id);
			bfputc(bf, MANGLE_type);
			mangle_id(bf, id, d);
			break;
		}
		default: {
			/* NOT YET IMPLEMENTED */
			bfputc(bf, MANGLE_error);
			break;
		}
		}
	}
	return;
}


/*
    This routine adds the mangled form of the token arguments args to the
    buffer position given by bf.
*/

static void
mangle_token_args(BUFFER *bf, LIST(TOKEN)args)
{
	unsigned m = LENGTH_list(args);
	mangle_number(bf,(unsigned long)m, 2);
	while (!IS_NULL_list(args)) {
		TOKEN tok = DEREF_tok(HEAD_list(args));
		mangle_token_arg(bf, tok);
		args = TAIL_list(args);
	}
	return;
}


/*
    This routine adds the token application 'id ( args )' to the buffer
    position given by bf.
*/

static void
mangle_token(BUFFER *bf, IDENTIFIER id, LIST(TOKEN)args, int d, int force)
{
	IDENTIFIER alt;
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	if (IS_id_token(id)) {
		if (!IS_NULL_list(args)) {
			force = 1;
		}
		alt = DEREF_id(id_token_alt(id));
	} else {
		force = 1;
		alt = id;
	}
	if (d == -2) {
		if (ds & dspec_auto) {
			/* Template parameter */
			ulong n = DEREF_ulong(id_no(id));
			if (ds & dspec_register) {
				/* This shouldn't happen */
				n = 0;
			}
			if (ds & dspec_template) {
				/* Template template parameter */
				if (!IS_NULL_list(args)) {
					bfputc(bf, MANGLE_template);
					bfputc(bf, MANGLE_templ_param);
					mangle_number(bf, n, 2);
					mangle_token_args(bf, args);
					return;
				}
			}
			bfputc(bf, MANGLE_templ_param);
			mangle_number(bf, n, 2);
			return;
		}
		d = ident_depth(alt);
	}
	if (force) {
		bfputc(bf, MANGLE_template);
	}
	mangle_id(bf, alt, d);
	if (!IS_NULL_list(args)) {
		/* Token arguments */
		mangle_token_args(bf, args);
	}
	return;
}


/*
    This routine finds the mangled function name for 'operator op'.  Note
    that op will always be in its primary form.
*/

static string
mangle_op(int op)
{
	const char *s;
	switch (op) {

	/* Standard operator names */
	case lex_abs:             s = "__ab";  break;
	case lex_and_H1:          s = "__ad";  break;
	case lex_and_Heq_H1:      s = "__aad"; break;
	case lex_array_Hop:       s = "__vc";  break;
	case lex_arrow:           s = "__rf";  break;
	case lex_arrow_Hstar:     s = "__rm";  break;
	case lex_assign:          s = "__as";  break;
	case lex_comma:           s = "__cm";  break;
	case lex_compl_H1:        s = "__co";  break;
	case lex_delete:          s = "__dl";  break;
	case lex_delete_Harray:   s = "__vd";  break;
	case lex_div:             s = "__dv";  break;
	case lex_div_Heq:         s = "__adv"; break;
	case lex_eq:              s = "__eq";  break;
	case lex_func_Hop:        s = "__cl";  break;
	case lex_greater:         s = "__gt";  break;
	case lex_greater_Heq:     s = "__ge";  break;
	case lex_less:            s = "__lt";  break;
	case lex_less_Heq:        s = "__le";  break;
	case lex_logical_Hand_H1: s = "__aa";  break;
	case lex_logical_Hor_H1:  s = "__oo";  break;
	case lex_lshift:          s = "__ls";  break;
	case lex_lshift_Heq:      s = "__als"; break;
	case lex_max:             s = "__mx";  break;
	case lex_min:             s = "__mn";  break;
	case lex_minus:           s = "__mi";  break;
	case lex_minus_Heq:       s = "__ami"; break;
	case lex_minus_Hminus:    s = "__mm";  break;
	case lex_new:             s = "__nw";  break;
	case lex_new_Harray:      s = "__vn";  break;
	case lex_not_H1:          s = "__nt";  break;
	case lex_not_Heq_H1:      s = "__ne";  break;
	case lex_or_H1:           s = "__or";  break;
	case lex_or_Heq_H1:       s = "__aor"; break;
	case lex_plus:            s = "__pl";  break;
	case lex_plus_Heq:        s = "__apl"; break;
	case lex_plus_Hplus:      s = "__pp";  break;
	case lex_rem:             s = "__md";  break;
	case lex_rem_Heq:         s = "__amd"; break;
	case lex_rshift:          s = "__rs";  break;
	case lex_rshift_Heq:      s = "__ars"; break;
	case lex_star:            s = "__ml";  break;
	case lex_star_Heq:        s = "__aml"; break;
	case lex_xor_H1:          s = "__er";  break;
	case lex_xor_Heq_H1:      s = "__aer"; break;

	/* Invalid operator names */
	case lex_cond_Hop:        s = "__cn";  break;
	case lex_colon:           s = "__cs";  break;
	case lex_colon_Hcolon:    s = "__cc";  break;
	case lex_dot:             s = "__df";  break;
	case lex_dot_Hstar:       s = "__dm";  break;
	case lex_sizeof:          s = "__sz";  break;
	case lex_typeid:          s = "__td";  break;
	case lex_vtable:          s = "__tb";  break;

	default:
		s = mangle_ntype[0];
		break;
	}
	return ustrlit(s);
}


/*
    This routine mangles the extended identifier name s into the buffer
    bf.  It returns true if the result differs from s.
*/

static int
mangle_ename(BUFFER *bf, string s)
{
	int u = 0;
	character c;
	while (c = *(s++), c != 0) {
		if (c == char_backslash) {
			c = *(s++);
			bfputc(bf, MANGLE_sep);
			bfputc(bf, MANGLE_sep);
			if (c == char_U) {
				bfputc(bf, MANGLE_unicode8);
			} else {
				bfputc(bf, MANGLE_unicode4);
			}
			u = 1;
			if (c == 0) {
				break;
			}
		} else {
			bfputc(bf,(int)c);
		}
	}
	return u;
}


/*
    This routine returns the mangled form of the identifier name nm.
    For conversion functions and extended names the name is built into
    name_buff and pcopy is set to true.
*/

static string
mangle_hashid(HASHID nm, int *pcopy, int force)
{
	string s = NULL;
	switch (TAG_hashid(nm)) {
	case hashid_name_tag: {
		/* Simple identifiers */
		s = DEREF_string(hashid_name_text(nm));
		break;
	}
	case hashid_ename_tag: {
		/* Extended identifiers */
		BUFFER *bf = &name_buff;
		unsigned n = (unsigned)(bf->posn - bf->start);
		s = DEREF_string(hashid_ename_text(nm));
		if (mangle_ename(bf, s)) {
			bfputc(bf, 0);
			s = bf->start + n;
			*pcopy = 1;
		}
		break;
	}
	case hashid_constr_tag: {
		/* Constructor names */
		s = ustrlit("__ct");
		break;
	}
	case hashid_destr_tag: {
		/* Destructor names */
		s = ustrlit("__dt");
		break;
	}
	case hashid_conv_tag: {
		/* Conversion names */
		BUFFER *bf = &name_buff;
		unsigned n = (unsigned)(bf->posn - bf->start);
		TYPE t = DEREF_type(hashid_conv_type(nm));
		bfprintf(bf, "__op");
		mangle_type(bf, t, 2, 1);
		bfputc(bf, 0);
		s = bf->start + n;
		*pcopy = 1;
		break;
	}
	case hashid_op_tag: {
		/* Operator names */
		int op = DEREF_int(hashid_op_lex(nm));
		s = mangle_op(op);
		break;
	}
	case hashid_anon_tag: {
		/* Anonymous names */
		if (force && output_all) {
			s = ustrlit("");
		}
		break;
	}
	}
	return s;
}


/*
    This routine finds the external (mangled) name of the identifier id
    of type v returning the result.  ext determines the treatment of inline
    functions with external linkage.  The null string is returned for local
    identifiers.
*/

string
mangle_name(IDENTIFIER id, int v, int ext)
{
	int d;
	string s;
	HASHID nm;
	BUFFER *bf;
	int copy = 0;
	NAMESPACE ns;
	string pre = NULL;
	TYPE t = NULL_type;
	TYPE f = NULL_type;
	CLASS_TYPE cs = NULL_ctype;

	/* Check for internal linkage */
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	if (!(ds & dspec_extern)) {
		if (ds & dspec_static) {
			if (!output_all) {
				return NULL;
			}
		} else if (IS_id_enumerator(id)) {
			if (!output_all) {
				return NULL;
			}
		} else {
			return NULL;
		}
	}
	if ((ds & dspec_instance) && !is_exported(id)) {
		/* Non-exported templates */
		if (!output_all) {
			return NULL;
		}
	}
	if (output_all)ext = 1;

	/* Find the basic name */
	name_buff.posn = name_buff.start;
	nm = DEREF_hashid(id_name(id));
	s = mangle_hashid(nm, &copy, 0);
	if (s == NULL) {
		return NULL;
	}

	/* Find the namespace depth */
	ns = DEREF_nspace(id_parent(id));
	d = nspace_depth(ns);

	/* Find any type qualifier */
	switch (TAG_id(id)) {
	case id_variable_tag: {
		/* Simple variables */
		if (ds & dspec_c) {
			/* C linkage */
			if (d > 0 || !anon_c_linkage) {
				d = 0;
			}
		} else if (mangle_objects) {
			/* C++ linkage */
			t = DEREF_type(id_variable_type(id));
		}
		break;
	}
	case id_stat_member_tag: {
		/* Static data members */
		if (mangle_objects) {
			t = DEREF_type(id_stat_member_type(id));
			cs = parent_class(id);
		}
		break;
	}
	case id_function_tag: {
		/* Simple functions */
		if ((ds & dspec_inline) && !ext) {
			/* Inline functions */
			d = -1;
		} else if (ds & dspec_main) {
			/* The main function */
#if LANGUAGE_CPP && (TDF_major < 4)
			s = ustrlit("__MAIN__");
#endif
			d = 0;
		} else if (ds & dspec_c) {
			/* C linkage */
			if (d > 0 || !anon_c_linkage)d = 0;
		} else {
			/* C++ linkage */
			t = DEREF_type(id_function_type(id));
			f = DEREF_type(id_function_form(id));
		}
		break;
	}
	case id_mem_func_tag:
	case id_stat_mem_func_tag: {
		/* Member functions */
		if ((ds & dspec_implicit) && !output_all) {
			/* Implicitly defined functions */
			d = -1;
		} else if ((ds & dspec_inline) && !ext) {
			/* Inline functions */
			d = -1;
		} else {
			t = DEREF_type(id_function_etc_type(id));
			f = DEREF_type(id_function_etc_form(id));
			cs = parent_class(id);
		}
		break;
	}
	case id_member_tag: {
		/* Data members */
		pre = ustrlit("~cpp.mem.");
		t = DEREF_type(id_member_type(id));
		cs = parent_class(id);
		break;
	}
	case id_enumerator_tag: {
		/* Enumerators */
		t = DEREF_type(id_enumerator_etype(id));
		break;
	}
	}

	/* Check for the simple cases */
	if (d < 0) {
		return NULL;
	}
	if (d == 0 && IS_NULL_type(t) && pre == NULL) {
		if (copy) {
			if (ustrchr(s, MANGLE_error)) {
				return NULL;
			}
			s = xustrcpy(s);
		}
		return s;
	}

	/* Deal with the complex case */
	bf = clear_buffer(&mangle_buff, NIL(FILE));
	if (pre) {
		bfputs(bf, pre);
	}
	bfputs(bf, s);
	if (v == VAR_token) {
		bfputc(bf, MANGLE_dot);
	} else {
		bfputc(bf, MANGLE_sep);
		bfputc(bf, MANGLE_sep);
	}
	if (d) {
		mangle_nspace(bf, ns, d);
	}
	if (!IS_NULL_type(f) && IS_type_token(f)) {
		/* Check for template functions */
		if (mangle_signature) {
			IDENTIFIER fid = DEREF_id(type_token_tok(f));
			LIST(TOKEN)args = DEREF_list(type_token_args(f));
			if (!IS_id_token(fid)) {
				if (IS_id_function_etc(fid)) {
					/* Use template function type */
					t = DEREF_type(id_function_etc_type(fid));
				}
				bfputc(bf, MANGLE_func_templ);
				mangle_token_args(bf, args);
				bfputc(bf, MANGLE_sep);
			}
		}
	}
	if (!IS_NULL_type(t)) {
		/* Output function type */
		int fn = 1;
		if (!IS_hashid_name_etc(nm)) {
			fn = 0;
		}
		if (v == VAR_token) {
			bfputc(bf, MANGLE_dot);
		}
		crt_mangle_class = cs;
		mangle_type(bf, t, fn, 0);
		crt_mangle_class = NULL_ctype;
	}
	bfputc(bf, 0);

	/* Check for illegal names */
	s = bf->start;
	if (ustrchr(s, MANGLE_error)) {
		return NULL;
	}
	s = xustrcpy(s);
	return s;
}


/*
    This variable is used by mangle_common to ensure that each call
    generates a unique name.
*/

ulong common_no = 0;


/*
    This routine creates a mangled name for the local static variable id
    from the function with mangled name s.
*/

string
mangle_common(string s, IDENTIFIER id)
{
	string t = NULL;
	if (s) {
		BUFFER *bf = clear_buffer(&mangle_buff, NIL(FILE));
		bfprintf(bf, "__v_");
		if (!IS_NULL_id(id)) {
			int copy = 0;
			HASHID nm = DEREF_hashid(id_name(id));
			name_buff.posn = name_buff.start;
			t = mangle_hashid(nm, &copy, 0);
			bfputs(bf, t);
		}
		bfprintf(bf, "%lu", common_no++);
		bfputc(bf, MANGLE_sep);
		bfputc(bf, MANGLE_sep);
		bfputs(bf, s);
		t = bf->start;
		if (ustrchr(t, MANGLE_error)) {
			return NULL;
		}
		t = xustrcpy(t);
	}
	return t;
}


/*
    This routine creates a mangled name for the virtual function table
    associated with the base class graph gr.
*/

string
mangle_vtable(const char *pre, GRAPH gr)
{
	string s;
	BUFFER *bf = clear_buffer(&mangle_buff, NIL(FILE));
	name_buff.posn = name_buff.start;
	bfputs(bf, ustrlit(pre));
	mangle_graph(bf, gr);
	bfputc(bf, 0);
	s = bf->start;
	if (ustrchr(s, MANGLE_error)) {
		return NULL;
	}
	s = xustrcpy(s);
	return s;
}


/*
    This routine creates a mangled name for the type information structure
    associated with the polymorphic class type ct.
*/

string
mangle_typeid(const char *pre, CLASS_TYPE ct)
{
	string s;
	BUFFER *bf = clear_buffer(&mangle_buff, NIL(FILE));
	name_buff.posn = name_buff.start;
	bfputs(bf, ustrlit(pre));
	mangle_ctype(bf, ct, -2);
	bfputc(bf, 0);
	s = bf->start;
	if (ustrchr(s, MANGLE_error)) {
		return NULL;
	}
	s = xustrcpy(s);
	return s;
}


/*
    This routine creates a mangled name for the type token name associated
    with the type t.
*/

string
mangle_tname(const char *pre, TYPE t)
{
	string s;
	BUFFER *bf = clear_buffer(&mangle_buff, NIL(FILE));
	name_buff.posn = name_buff.start;
	bfputs(bf, ustrlit(pre));
	mangle_type(bf, t, 2, 1);
	bfputc(bf, 0);
	s = bf->start;
	if (ustrchr(s, MANGLE_error)) {
		return NULL;
	}
	s = xustrcpy(s);
	return s;
}


/*
    This routine creates a dynamic initialiser function name.  For TDF 4.0
    and later this can be the null string since there is direct support
    for dynamic initialisation.
*/

string
mangle_init(void)
{
#if (TDF_major >= 4)
	return NULL;
#else
	char buff[50];
	output_init = 1;
	sprintf_v(buff, "_GLOBAL_$I$%s", uniq_string);
	return xustrcpy(ustrlit(buff));
#endif
}


/*
    This routine creates a unique identifier name distinct from every other
    identifier name.
*/

string
mangle_anon(void)
{
	char buff[50];
	static unsigned long anon_no = 0;
	sprintf_v(buff, "__%lu_%s", anon_no++, uniq_string);
	return xustrcpy(ustrlit(buff));
}


/*
    This routine adds the name of the namespace ns to the buffer bf.
*/

static void
mangle_diag_nspace(BUFFER *bf, NAMESPACE ns)
{
	if (!IS_NULL_nspace(ns)) {
		switch (TAG_nspace(ns)) {
		case nspace_named_tag:
		case nspace_ctype_tag: {
			int copy = 0;
			IDENTIFIER id = DEREF_id(nspace_name(ns));
			HASHID nm = DEREF_hashid(id_name(id));
			string s = mangle_hashid(nm, &copy, 0);
			ns = DEREF_nspace(id_parent(id));
			mangle_diag_nspace(bf, ns);
			if (s) {
				bfputs(bf, s);
			}
			bfputc(bf, MANGLE_sep);
			bfputc(bf, MANGLE_sep);
			break;
		}
		case nspace_unnamed_tag: {
			IDENTIFIER id = DEREF_id(nspace_name(ns));
			ns = DEREF_nspace(id_parent(id));
			mangle_diag_nspace(bf, ns);
			break;
		}
		}
	}
	return;
}


/*
    This routine creates the name used for the identifier id in the
    diagnostic output.  If q is false then no qualifiers are output.
*/

string
mangle_diag(IDENTIFIER id, int q)
{
	int fn = 0;
	TYPE t = NULL_type;
	HASHID nm = DEREF_hashid(id_name(id));
	unsigned tag = TAG_hashid(nm);
	BUFFER *bf = clear_buffer(&mangle_buff, NIL(FILE));
	name_buff.posn = name_buff.start;
	if (q) {
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if (ds & dspec_c) {
			/* Ignore C linkage objects */
			/* EMPTY */
		} else if ((ds & dspec_main) && tag == hashid_name_tag) {
			/* Ignore main function */
			/* EMPTY */
		} else {
			/* Namespace qualifiers */
			NAMESPACE ns = DEREF_nspace(id_parent(id));
			mangle_diag_nspace(bf, ns);
			if (IS_id_function_etc(id)) {
				t = DEREF_type(id_function_etc_type(id));
			}
		}
	}
	switch (tag) {
	case hashid_name_tag: {
		string s = DEREF_string(hashid_name_text(nm));
		bfputs(bf, s);
		fn = 1;
		break;
	}
	case hashid_ename_tag: {
		if (EQ_KEYWORD(nm, lex_this_Hname)) {
			bfprintf(bf, "this");
		} else {
			string s = DEREF_string(hashid_ename_text(nm));
			IGNORE mangle_ename(bf, s);
		}
		fn = 1;
		break;
	}
	case hashid_constr_tag: {
		bfprintf(bf, "1");
		break;
	}
	case hashid_destr_tag: {
		bfprintf(bf, "0");
		break;
	}
	case hashid_conv_tag: {
		t = DEREF_type(hashid_conv_type(nm));
		bfprintf(bf, "operator__T");
		mangle_type(bf, t, 2, 1);
		t = NULL_type;
		break;
	}
	case hashid_op_tag: {
		int op = DEREF_int(hashid_op_lex(nm));
		string s = mangle_op(op);
		bfprintf(bf, "operator");
		if (s) {
			bfputs(bf, s);
		}
		break;
	}
	case hashid_anon_tag: {
		ulong u = DEREF_ulong(hashid_anon_uniq(nm));
		bfprintf(bf, "__anon%lu", u);
		fn = 1;
		break;
	}
	}
	if (!IS_NULL_type(t)) {
		/* Mangled function type */
		bfputc(bf, MANGLE_sep);
		bfputc(bf, MANGLE_sep);
		mangle_type(bf, t, fn, 0);
	}
	bfputc(bf, 0);
	return bf->start;
}
