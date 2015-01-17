/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "config.h"
#include "version.h"
#include "c_types.h"
#include "ctype_ops.h"
#include "etype_ops.h"
#include "exp_ops.h"
#include "flt_ops.h"
#include "ftype_ops.h"
#include "graph_ops.h"
#include "id_ops.h"
#include "itype_ops.h"
#include "nat_ops.h"
#include "off_ops.h"
#include "str_ops.h"
#include "type_ops.h"
#include "error.h"
#include "tdf.h"
#include "basetype.h"
#include "capsule.h"
#include "char.h"
#include "check.h"
#include "chktype.h"
#include "compile.h"
#include "constant.h"
#include "convert.h"
#include "copy.h"
#include "derive.h"
#include "encode.h"
#include "exp.h"
#include "init.h"
#include "interface.h"
#include "inttype.h"
#include "literal.h"
#include "mangle.h"
#include "shape.h"
#include "struct.h"
#include "tok.h"
#include "ustring.h"
#if TDF_OUTPUT


/*
    This routine adds the simple integer constant n to the bitstream bs
    as a TDF INT.  The argument e is true if this is the last sequence of
    digits in a value.
*/

static BITSTREAM *
enc_tdfint(BITSTREAM *bs, NAT n, int e)
{
	unsigned np;
	LIST(unsigned)p;
	if (IS_nat_small(n)) {
		p = NULL_list(unsigned);
		np = 1;
	} else {
		p = DEREF_list(nat_large_values(n));
		np = LENGTH_list(p);
	}
	if (np <= 2) {
		/* Small values */
		unsigned long v = get_nat_value(n);
		if (e) {
			bs = enc_int(bs, v);
		} else {
			bs = enc_int_aux(bs, v);
		}
	} else {
		/* Really large values */
		unsigned u = DEREF_unsigned(HEAD_list(p));
		n = binary_nat_op(exp_rshift_tag, n, small_nat[3]);
		bs = enc_tdfint(bs, n, 0);
		u &= 0x7;
		if (e) {
			u |= 0x8;
		}
		bs = enc_bits(bs,(unsigned)4, u);
	}
	return bs;
}


/*
    This routine adds the value n to the bitstream bs as a TDF BOOL,
    nonzero values map to true, zero to false.
*/

BITSTREAM *
enc_bool(BITSTREAM *bs, int n)
{
	if (n) {
		ENC_true(bs);
	} else {
		ENC_false(bs);
	}
	return bs;
}


/*
    This routine adds the calculated integral expression n to the
    bitstream bs.  The value is negated if sgn is true and a token is
    introduced to represent the value if intro is true.  The value is
    encoded as a NAT if sort is 0, a SIGNED NAT if sort is 1, an
    EXP if sort is 2 and a constant EXP if sort is 3.
*/

static BITSTREAM *
enc_calc(BITSTREAM *bs, NAT n, int sgn, int intro, int sort)
{
	static int suppress_calc = 0;
	NAT n1 = n;
	ulong m = DEREF_ulong(nat_calc_tok(n));
	EXP e = DEREF_exp(nat_calc_value(n));
	TYPE t = DEREF_type(exp_type(e));
	if (m == LINK_NONE && !suppress_calc) {
		EXP f = eval_exp(e, 1);
		if (!EQ_exp(f, e) && IS_exp_int_lit(f)) {
			e = f;
			t = DEREF_type(exp_type(e));
			n = DEREF_nat(exp_int_lit_nat(e));
			if (!IS_nat_calc(n)) {
				/* Value evaluates to a literal constant */
				if (sort == 0) {
					bs = enc_nat(bs, n, 0);
				} else {
					if (sort >= 2) {
						ENC_make_int(bs);
						bs = enc_variety(bs, t);
					}
					bs = enc_snat(bs, n, sgn, 0);
				}
				return bs;
			}
		}
	}

	/* Encode calculated value */
	suppress_calc++;
	if (sort == 0) {
		ENC_computed_nat(bs);
		sort = 2;
	} else if (sort == 1) {
		ENC_computed_signed_nat(bs);
		sort = 2;
	}
	if (sgn) {
		/* Negated value */
		ENC_negate(bs);
		bs = enc_error_treatment(bs, t);
		bs = enc_calc(bs, n, 0, intro, sort);
	} else {
		if (intro && m == LINK_NONE) {
			/* Introduce token for value */
			while (!IS_NULL_exp(e) && IS_exp_int_lit(e)) {
				NAT n2 = DEREF_nat(exp_int_lit_nat(e));
				if (!IS_nat_calc(n2)) {
					break;
				}
				m = DEREF_ulong(nat_calc_tok(n2));
				if (m != LINK_NONE) {
					break;
				}
				e = DEREF_exp(nat_calc_value(n2));
			}
			if (!IS_NULL_exp(e) && IS_exp_token(e)) {
				LIST(TOKEN)args;
				args = DEREF_list(exp_token_args(e));
				if (IS_NULL_list(args)) {
					/* Use existing token */
					IDENTIFIER tok =
					    DEREF_id(exp_token_tok(e));
					IGNORE capsule_id(tok, VAR_token);
					m = DEREF_ulong(id_no(tok));
				}
			}
			if (m == LINK_NONE) {
				/* Introduce token for value */
				BITSTREAM *ts;
				m = capsule_no(NULL_string, VAR_token);
				ts = enc_tokdef_start(m, "E", NIL(ulong), 1);
				if (sort == 3) {
					/* Force constant evaluation */
					ENC_make_int(ts);
					ts = enc_variety(ts, t);
					ENC_computed_signed_nat(ts);
				}
				ts = enc_exp(ts, e);
				enc_tokdef_end(m, ts);
			}
			COPY_ulong(nat_calc_tok(n1), m);
			COPY_ulong(nat_calc_tok(n), m);
		}
		if (m == LINK_NONE) {
			/* Calculated value */
			if (sort == 3) {
				/* Force constant evaluation */
				ENC_make_int(bs);
				bs = enc_variety(bs, t);
				ENC_computed_signed_nat(bs);
			}
			bs = enc_exp(bs, e);
		} else {
			/* Tokenised value */
			m = link_no(bs, m, VAR_token);
			ENC_exp_apply_token(bs);
			ENC_make_tok(bs, m);
			ENC_LEN_SMALL(bs, 0);
		}
	}
	suppress_calc--;
	return bs;
}


/*
    This routine adds the integer constant n to the bitstream bs as a
    TDF NAT.
*/

BITSTREAM *
enc_nat(BITSTREAM *bs, NAT n, int intro)
{
	if (IS_NULL_nat(n)) {
		/* Null constant maps to zero */
		ENC_make_nat(bs);
		ENC_INT_SMALL(bs, 0);
	} else {
		ASSERT(ORDER_nat == 5);
		switch (TAG_nat(n)) {
		case nat_small_tag: {
			unsigned v = DEREF_unsigned(nat_small_value(n));
			ENC_make_nat(bs);
			ENC_INT(bs, v);
			break;
		}
		case nat_large_tag: {
			ENC_make_nat(bs);
			bs = enc_tdfint(bs, n, 1);
			break;
		}
		case nat_calc_tag: {
			bs = enc_calc(bs, n, 0, intro, 0);
			break;
		}
		case nat_neg_tag: {
			/* This case shouldn't occur */
			ENC_make_nat(bs);
			ENC_INT_SMALL(bs, 0);
			break;
		}
		case nat_token_tag: {
			/* Token applications */
			IDENTIFIER tok = DEREF_id(nat_token_tok(n));
			LIST(TOKEN)args = DEREF_list(nat_token_args(n));
			TOKEN sort = DEREF_tok(id_token_sort(tok));
			int s = token_code(sort);
			if (s == 'Z') {
				/* Signed nat token */
				TYPE t = type_sint;
				ENC_computed_nat(bs);
				ENC_make_int(bs);
				bs = enc_variety(bs, t);
			}
			bs = enc_token(bs, tok, args);
			break;
		}
		}
	}
	return bs;
}


/*
    This routine adds the integer constant n to the bitstream bs as a
    TDF SIGNED NAT.  sgn is true if the value is to be negated and intro
    is true if a token is to be introduced for a calculated value.
*/

BITSTREAM *
enc_snat(BITSTREAM *bs, NAT n, int sgn, int intro)
{
	if (IS_NULL_nat(n)) {
		/* Null constant maps to zero */
		ENC_make_signed_nat(bs);
		ENC_OFF(bs);
		ENC_INT_SMALL(bs, 0);
	} else {
		ASSERT(ORDER_nat == 5);
		switch (TAG_nat(n)) {
		case nat_small_tag: {
			unsigned v = DEREF_unsigned(nat_small_value(n));
			if (v == 0) {
				sgn = 0;
			}
			ENC_make_signed_nat(bs);
			ENC_BOOL(bs, sgn);
			ENC_INT(bs, v);
			break;
		}
		case nat_large_tag: {
			ENC_make_signed_nat(bs);
			ENC_BOOL(bs, sgn);
			bs = enc_tdfint(bs, n, 1);
			break;
		}
		case nat_calc_tag: {
			bs = enc_calc(bs, n, sgn, intro, 1);
			break;
		}
		case nat_neg_tag: {
			NAT m = DEREF_nat(nat_neg_arg(n));
			bs = enc_snat(bs, m, !sgn, intro);
			break;
		}
		case nat_token_tag: {
			/* Token applications */
			IDENTIFIER tok = DEREF_id(nat_token_tok(n));
			LIST(TOKEN)args = DEREF_list(nat_token_args(n));
			TOKEN sort = DEREF_tok(id_token_sort(tok));
			int s = token_code(sort);
			if (s == 'Z') {
				/* Signed nat token */
				if (sgn) {
					/* Negate signed nat */
					TYPE t = type_sint;
					ENC_computed_signed_nat(bs);
					ENC_negate(bs);
					bs = enc_error_treatment(bs, t);
					ENC_make_int(bs);
					bs = enc_variety(bs, t);
				}
			} else {
				/* Nat token */
				ENC_snat_from_nat(bs);
				bs = enc_bool(bs, sgn);
			}
			bs = enc_token(bs, tok, args);
			break;
		}
		}
	}
	return bs;
}


/*
    This routine adds the integer constant expression n of type t to the
    bitstream bs.  etag gives the expression tag which is used to
    determine whether a token should be introduced for the value.
*/

BITSTREAM *
enc_int_lit(BITSTREAM *bs, NAT n, TYPE t, unsigned etag)
{
	if (IS_nat_calc(n)) {
		if (etag == exp_identifier_tag) {
			/* Enumerator value */
			bs = enc_calc(bs, n, 0, 1, 3);
		} else {
			/* Other calculated value */
			bs = enc_calc(bs, n, 0, 0, 2);
		}
	} else {
		/* Simple value */
		ENC_make_int(bs);
		bs = enc_variety(bs, t);
		bs = enc_snat(bs, n, 0, 0);
	}
	return bs;
}


/*
    This routine adds the floating literal flt of type t to the bitstream
    bs as a TDF EXP.
*/

BITSTREAM *
enc_float(BITSTREAM *bs, FLOAT flt, TYPE t)
{
	ulong n = DEREF_ulong(flt_tok(flt));
	if (n == LINK_NONE) {
		/* Decompose literal */
		BITSTREAM *ts;
		string i = DEREF_string(flt_simple_int_part(flt));
		string f = DEREF_string(flt_simple_frac_part(flt));
		unsigned long ni = (unsigned long)ustrlen(i);
		unsigned long nf = (unsigned long)ustrlen(f);
		unsigned long nt = ni + nf + 1;
		NAT e = DEREF_nat(flt_simple_exponent(flt));

		/* Map to canonical form */
		if (ni == 0) {
			/* Introduce leading zero */
			i = small_number[0];
			ni = 1;
			nt = nf + 2;
		}
		if (nf == 0) {
			/* No decimal part */
			nt = ni;
		}
		if (nf == 1 && f[0] == '0') {
			/* Ignore trivial decimal part */
			nf = 0;
			nt = ni;
		}

		/* Encode expression */
		n = capsule_no(NULL_string, VAR_token);
		ts = enc_tokdef_start(n, "E", NIL(ulong), 1);
		ENC_make_floating(ts);
		ts = enc_flvar(ts, t);
		ENC_to_nearest(ts);
		ENC_false(ts);
		ENC_make_string(ts);
		ENC_INT(ts, BYTE_SIZE);
		ENC_INT(ts, nt);
		ts = enc_ascii(ts, ni, i);
		if (nf) {
			ENC_BITS(ts, BYTE_SIZE, '.');
			ts = enc_ascii(ts, nf, f);
		}
		ENC_make_nat(ts);
		ENC_INT(ts, 10);
		ts = enc_snat(ts, e, 0, 0);
		enc_tokdef_end(n, ts);
		COPY_ulong(flt_tok(flt), n);
	}
	n = link_no(bs, n, VAR_token);
	ENC_exp_apply_token(bs);
	ENC_make_tok(bs, n);
	ENC_LEN_SMALL(bs, 0);
	return bs;
}


/*
    This routine adds the small floating literal given by the value v of
    type t to the bitstream bs as a TDF EXP.
*/

BITSTREAM *
enc_float_int(BITSTREAM *bs, int v, TYPE t)
{
	FLOAT flt = get_float(t, v);
	if (!IS_NULL_flt(flt)) {
		bs = enc_float(bs, flt, t);
	} else {
		char s[20];
		sprintf_v(s, "%d", v);
		ENC_make_floating(bs);
		bs = enc_flvar(bs, t);
		ENC_to_nearest(bs);
		ENC_false(bs);
		ENC_make_string(bs);
		bs = enc_ustring(bs, ustrlit(s));
		ENC_make_nat(bs);
		ENC_INT(bs, 10);
		bs = enc_snat(bs, NULL_nat, 0, 0);
	}
	return bs;
}


/*
    This routine adds the string literal str of type t to the bitstream
    bs.  Note that the type determines the string length - the string
    is truncated or padded with zeros as necessary (this includes the
    normal terminal zero for a string).
*/

BITSTREAM *
enc_string(BITSTREAM *bs, STRING str, TYPE t)
{
	unsigned long i, m;
	unsigned long d = 0;
	string s = DEREF_string(str_simple_text(str));
	unsigned long n = DEREF_ulong(str_simple_len(str));
	unsigned kind = DEREF_unsigned(str_simple_kind(str));
	if (n == 0) {
		/* Allow for empty strings */
		bs = enc_null_exp(bs, t);
		return bs;
	}
	if (IS_type_array(t)) {
		/* Find array size */
		NAT sz = DEREF_nat(type_array_size(t));
		m = get_nat_value(sz);
		if (m < n) {
			/* String truncation */
			n = m;
		} else {
			d = m - n;
			if (d <= STRING_PADDING) {
				/* Small padding */
				d = 0;
			} else {
				/* Large padding */
				ENC_concat_nof(bs);
				m = n;
			}
		}
		t = DEREF_type(type_array_sub(t));
	} else {
		m = n + 1;
	}
	if (kind & STRING_FAT) {
		/* Fat character strings */
		unsigned mbits = 0;
		unsigned long maxc = 1;
		BASE_TYPE sign = btype_none;
		unsigned bits = find_type_size(t, &mbits, &sign);
		if (sign != btype_unsigned) {
			bits--;
		}
		maxc <<= bits;
		ENC_make_nof(bs);
		ENC_LIST(bs, m);
		for (i = 0; i < n; i++) {
			TYPE u = t;
			int ch = CHAR_SIMPLE;
			unsigned long c = get_multi_char(s, &ch);
			if (ch == CHAR_SIMPLE) {
				c = to_ascii(c, &ch);
			}
			if (maxc && c >= maxc) {
				/* Character doesn't fit into type */
				ENC_change_variety(bs);
				bs = enc_error_treatment(bs, u);
				bs = enc_variety(bs, u);
				u = type_ulong;
			}
			ENC_make_int(bs);
			bs = enc_variety(bs, u);
			ENC_make_signed_nat(bs);
			ENC_OFF(bs);
			ENC_INT(bs, c);
			s += MULTI_WIDTH;
		}
		for (; i < m; i++) {
			/* Terminal zeros */
			bs = enc_make_int(bs, t, 0);
		}
	} else {
		ENC_make_nof_int(bs);
		bs = enc_variety(bs, t);
		ENC_make_string(bs);
		ENC_INT(bs, BYTE_SIZE);
		ENC_INT(bs, m);
		if (kind & STRING_MULTI) {
			for (i = 0; i < n; i++) {
				int ch = CHAR_SIMPLE;
				unsigned long c = get_multi_char(s, &ch);
				if (ch == CHAR_SIMPLE) {
					c = to_ascii(c, &ch);
				}
				ENC_BITS(bs, BYTE_SIZE, c);
				s += MULTI_WIDTH;
			}
		} else {
			/* Simple string */
			bs = enc_ascii(bs, n, s);
		}
		for (i = n; i < m; i++) {
			/* Terminal zeros */
			ENC_BITS(bs, BYTE_SIZE, 0);
		}
	}
	if (d) {
		/* Large padding */
		ENC_n_copies(bs);
		ENC_make_nat(bs);
		ENC_INT(bs, d);
		bs = enc_make_int(bs, t, 0);
	}
	return bs;
}


/*
    This routine adds the string literal str to the bitstream bs.
*/

BITSTREAM *
enc_strlit(BITSTREAM *bs, STRING str)
{
	string s = DEREF_string(str_simple_text(str));
	unsigned long n = DEREF_ulong(str_simple_len(str));
	unsigned kind = DEREF_unsigned(str_simple_kind(str));
	ENC_make_string(bs);
	ENC_INT(bs, BYTE_SIZE);
	ENC_INT(bs, n);
	if (kind & STRING_MULTI) {
		unsigned long i;
		for (i = 0; i < n; i++) {
			int ch = CHAR_SIMPLE;
			unsigned long c = get_multi_char(s, &ch);
			if (ch == CHAR_SIMPLE) {
				c = to_ascii(c, &ch);
			}
			ENC_BITS(bs, BYTE_SIZE, c);
			s += MULTI_WIDTH;
		}
	} else {
		bs = enc_ascii(bs, n, s);
	}
	return bs;
}


/*
    This routine adds the character literal str of type t to the bitstream
    bs.  u gives the actual literal type, from which it is cast to t.  Note
    that it is possible that str does not fit into u.
*/

BITSTREAM *
enc_char(BITSTREAM *bs, STRING str, TYPE t, TYPE u)
{
	NAT n;
	TYPE w;
	int convert_to_t;
	int convert_to_u;
	unsigned long v = DEREF_ulong(str_simple_tok(str));
	if (v == LINK_NONE) {
		/* Evaluate literal */
		n = eval_char_lit(str);
		v = DEREF_ulong(str_simple_tok(str));
		if (v < 128) {
			/* Small values are easy */
			bs = enc_make_int(bs, t,(int)v);
			return bs;
		}
	} else {
		if (v < 128) {
			/* Small values are easy */
			bs = enc_make_int(bs, t,(int)v);
			return bs;
		}
		n = make_nat_value(v);
	}
	if (check_nat_range(u, n) == 0) {
		if (EQ_type(t, u) || check_nat_range(t, n) == 0) {
			/* Fits into both t and u */
			w = t;
			convert_to_t = 0;
			convert_to_u = 0;
		} else {
			/* Fits into u but not t */
			w = u;
			convert_to_t = 1;
			convert_to_u = 0;
		}
	} else {
		/* Doesn't fit into u */
		w = find_char_type(n);
		convert_to_t = 1;
		convert_to_u = 1;
	}
	if (convert_to_t) {
		ENC_change_variety(bs);
		bs = enc_error_treatment(bs, t);
		bs = enc_variety(bs, t);
	}
	if (convert_to_u && !EQ_type(u, t)) {
		ENC_change_variety(bs);
		bs = enc_error_treatment(bs, u);
		bs = enc_variety(bs, u);
	}
	ENC_make_int(bs);
	bs = enc_variety(bs, w);
	ENC_make_signed_nat(bs);
	ENC_OFF(bs);
	bs = enc_tdfint(bs, n, 1);
	return bs;
}


/*
    This routine returns the integral type corresponding to the type t.
*/

static INT_TYPE
find_itype(TYPE t)
{
	INT_TYPE it;
	unsigned tag = TAG_type(t);
	if (tag == type_bitfield_tag) {
		it = DEREF_itype(type_bitfield_defn(t));
	} else {
		if (tag == type_enumerate_tag) {
			/* Allow for enumeration types */
			ENUM_TYPE et = DEREF_etype(type_enumerate_defn(t));
			t = DEREF_type(etype_rep(et));
			tag = TAG_type(t);
		}
		if (tag != type_integer_tag) {
			t = type_sint;
		}
		it = DEREF_itype(type_integer_rep(t));
	}
	return it;
}


/*
    This routine adds the code number of the integral type it to the
    bitstream bs as a TDF SIGNED NAT.
*/

static BITSTREAM *
enc_var_no(BITSTREAM *bs, INT_TYPE it, int alt)
{
	ulong tok;
	unsigned tag = TAG_itype(it);
	ASSERT(ORDER_itype == 6);
	switch (tag) {
	case itype_basic_tag: {
		/* Built-in integral types */
		BUILTIN_TYPE n = DEREF_ntype(itype_basic_no(it));
		unsigned m = base_token[n].no;
		if (alt) {
			m = base_token[n].alt;
		}
		if (m != ARITH_none) {
			/* Basic types are easy */
			bs = enc_make_snat(bs,(int)m);
			return bs;
		}
		break;
	}
	case itype_bitfield_tag: {
		/* Bitfield types */
		TYPE s = DEREF_type(itype_bitfield_sub(it));
		INT_TYPE is = find_itype(s);
		bs = enc_var_no(bs, is, alt);
		return bs;
	}
	case itype_token_tag: {
		/* Tokenised types */
		IDENTIFIER tk = DEREF_id(itype_token_tok(it));
		LIST(TOKEN)args = DEREF_list(itype_token_args(it));
		bs = enc_token(bs, tk, args);
		return bs;
	}
	}

	/* Find the token number */
	tok = DEREF_ulong(itype_ntok(it));
	if (tok == LINK_NONE) {
		if (tag == itype_basic_tag) {
			/* Look up special token number */
			BUILTIN_TYPE n = DEREF_ntype(itype_basic_no(it));
			int tn = base_token[n].tok;
			tok = special_no(tn);
			COPY_ulong(itype_ntok(it), tok);
		} else {
			/* Compound integral types */
			string s = NULL;
			BITSTREAM *ts, *us;
			if (output_all) {
				TYPE t = make_itype(it, it);
				s = mangle_tname("~cpp.itype_no.", t);
			}
			tok = capsule_no(s, VAR_token);
			COPY_ulong(itype_ntok(it), tok);
			ts = enc_tokdef_start(tok, "Z", NIL(ulong), 1);
			us = start_bitstream(NIL(FILE), ts->link);
			switch (tag) {
			case itype_promote_tag: {
				/* Promoted integral types */
				INT_TYPE is =
				    DEREF_itype(itype_promote_arg(it));
				ts = enc_special(ts, TOK_promote);
				us = enc_var_no(us, is, 0);
				break;
			}
			case itype_arith_tag: {
				/* Arithmetic integral types */
				INT_TYPE is = DEREF_itype(itype_arith_arg1(it));
				INT_TYPE ir = DEREF_itype(itype_arith_arg2(it));
				ts = enc_special(ts, TOK_arith_type);
				us = enc_var_no(us, is, 0);
				us = enc_var_no(us, ir, 0);
				break;
			}
			case itype_literal_tag: {
				/* Literal integral types */
				NAT n = DEREF_nat(itype_literal_nat(it));
				IDENTIFIER tid =
				    DEREF_id(itype_literal_tok(it));
				if (!IS_NULL_id(tid)) {
					ulong tn;
					IGNORE enc_tokdef(tid, 0);
					tn = unit_no(ts, tid, VAR_token, 0);
					ENC_signed_nat_apply_token(ts);
					ENC_make_tok(ts, tn);
				} else {
					int spec = DEREF_int(itype_literal_spec(it));
					ts = enc_special(ts, spec);
				}
				us = enc_snat(us, n, 0, 0);
				break;
			}
			}
			ts = enc_bitstream(ts, us);
			enc_tokdef_end(tok, ts);
		}
	}

	/* Encode the token application */
	tok = link_no(bs, tok, VAR_token);
	ENC_signed_nat_apply_token(bs);
	ENC_make_tok(bs, tok);
	ENC_LEN_SMALL(bs, 0);
	return bs;
}


/*
    This routine adds the integral type t to the bitstream bs as a
    TDF VARIETY.  Note that all integral types are tokenised.
*/

BITSTREAM *
enc_variety(BITSTREAM *bs, TYPE t)
{
	/* Find the token number */
	INT_TYPE it = find_itype(t);
	unsigned tag = TAG_itype(it);
	ulong tok = DEREF_ulong(itype_itok(it));
	if (tok == LINK_NONE) {
		ASSERT(ORDER_itype == 6);
		switch (tag) {
		case itype_basic_tag: {
			/* Built-in integral types */
			BUILTIN_TYPE n = DEREF_ntype(itype_basic_no(it));
			unsigned m = base_token[n].no;
			if (m != ARITH_none) {
				/* Look up special token number */
				int tn = base_token[n].tok;
				tok = special_no(tn);
				COPY_ulong(itype_itok(it), tok);
			}
			break;
		}
		case itype_token_tag: {
			/* Tokenised integral types */
			IDENTIFIER tk = DEREF_id(itype_token_tok(it));
			DECL_SPEC ds = DEREF_dspec(id_storage(tk));
			if (ds & dspec_auto) {
				/* Integral token parameters */
				BITSTREAM *ts;
				bs = enc_special(bs, TOK_convert);
				ts = start_bitstream(NIL(FILE), bs->link);
				ts = enc_var_no(ts, it, 0);
				bs = enc_bitstream(bs, ts);
				return bs;
			}
			break;
		}
		}
		if (tok == LINK_NONE) {
			/* Define the variety token */
			string s = NULL;
			if (output_all) {
				t = qualify_type(t, cv_none, 0);
				s = mangle_tname("~cpp.itype.", t);
			}
			tok = capsule_no(s, VAR_token);
			COPY_ulong(itype_itok(it), tok);
			if (tag == itype_bitfield_tag) {
				/* Bitfield types */
				BITSTREAM *ts;
				NAT n = DEREF_nat(itype_bitfield_size(it));
				BASE_TYPE bt =
				    DEREF_btype(itype_bitfield_rep(it));
				ts = enc_tokdef_start(tok, "U", NIL(ulong), 1);
				ENC_bfvar_bits(ts);
				if (bt & btype_signed) {
					ENC_true(ts);
				} else if (bt & btype_unsigned) {
					ENC_false(ts);
				} else {
					BITSTREAM *us;
					ts = enc_special(ts, TOK_bitf_sign);
					us = start_bitstream(NIL(FILE),
							     ts->link);
					us = enc_var_no(us, it, 0);
					ts = enc_bitstream(ts, us);
				}
				ts = enc_nat(ts, n, 1);
				enc_tokdef_end(tok, ts);
			} else {
				/* Integral types */
				BITSTREAM *ts, *us;
				ts = enc_tokdef_start(tok, "V", NIL(ulong), 1);
				ts = enc_special(ts, TOK_convert);
				us = start_bitstream(NIL(FILE), ts->link);
				us = enc_var_no(us, it, 0);
				ts = enc_bitstream(ts, us);
				enc_tokdef_end(tok, ts);
			}
		}
	}

	/* Encode the token application */
	tok = link_no(bs, tok, VAR_token);
	if (tag == itype_bitfield_tag) {
		ENC_bfvar_apply_token(bs);
	} else {
		ENC_var_apply_token(bs);
	}
	ENC_make_tok(bs, tok);
	ENC_LEN_SMALL(bs, 0);
	return bs;
}


/*
    This routine adds the code number of the floating point type ft to
    the bitstream bs as a TDF SIGNED NAT.
*/

static BITSTREAM *
enc_flvar_no(BITSTREAM *bs, FLOAT_TYPE ft)
{
	ulong tok;
	unsigned tag = TAG_ftype(ft);
	ASSERT(ORDER_ftype == 4);
	switch (tag) {
	case ftype_basic_tag: {
		/* Built-in floating types */
		BUILTIN_TYPE n = DEREF_ntype(ftype_basic_no(ft));
		unsigned m = base_token[n].no;
		if (m != ARITH_none) {
			/* Basic types are easy */
			bs = enc_make_snat(bs,(int)m);
			return bs;
		}
		break;
	}
	case ftype_token_tag: {
		/* Tokenised types */
		IDENTIFIER tk = DEREF_id(ftype_token_tok(ft));
		LIST(TOKEN)args = DEREF_list(ftype_token_args(ft));
		bs = enc_token(bs, tk, args);
		return bs;
	}
	}

	/* Find the token number */
	tok = DEREF_ulong(ftype_ntok(ft));
	if (tok == LINK_NONE) {
		if (tag == ftype_basic_tag) {
			/* Look up special token number */
			BUILTIN_TYPE n = DEREF_ntype(ftype_basic_no(ft));
			int tn = base_token[n].tok;
			tok = special_no(tn);
			COPY_ulong(ftype_ntok(ft), tok);
		} else {
			/* Compound floating types */
			string s = NULL;
			BITSTREAM *ts, *us;
			if (output_all) {
				TYPE t = make_ftype(ft, NULL_ftype);
				s = mangle_tname("~cpp.ftype_no.", t);
			}
			tok = capsule_no(s, VAR_token);
			COPY_ulong(ftype_ntok(ft), tok);
			ts = enc_tokdef_start(tok, "Z", NIL(ulong), 1);
			us = start_bitstream(NIL(FILE), ts->link);
			switch (tag) {
			case ftype_arg_promote_tag: {
				/* Promoted floating types */
				FLOAT_TYPE fs;
				fs = DEREF_ftype(ftype_arg_promote_arg(ft));
				ts = enc_special(ts, TOK_promote);
				us = enc_flvar_no(us, fs);
				break;
			}
			case ftype_arith_tag: {
				/* Arithmetic floating types */
				FLOAT_TYPE fs =
				    DEREF_ftype(ftype_arith_arg1(ft));
				FLOAT_TYPE fr =
				    DEREF_ftype(ftype_arith_arg2(ft));
				ts = enc_special(ts, TOK_arith_type);
				us = enc_flvar_no(us, fs);
				us = enc_flvar_no(us, fr);
				break;
			}
			}
			ts = enc_bitstream(ts, us);
			enc_tokdef_end(tok, ts);
		}
	}

	/* Encode the token application */
	tok = link_no(bs, tok, VAR_token);
	ENC_signed_nat_apply_token(bs);
	ENC_make_tok(bs, tok);
	ENC_LEN_SMALL(bs, 0);
	return bs;
}


/*
    This routine adds the floating point type t to the bitstream bs as
    a TDF FLOATING VARIETY.  Note that all floating point types are
    tokenised.
*/

BITSTREAM *
enc_flvar(BITSTREAM *bs, TYPE t)
{
	ulong tok;
	FLOAT_TYPE ft;
	if (!IS_type_floating(t)) {
		t = type_double;
	}
	ft = DEREF_ftype(type_floating_rep(t));

	/* Find the token number */
	tok = DEREF_ulong(ftype_ftok(ft));
	if (tok == LINK_NONE) {
		if (IS_ftype_basic(ft)) {
			/* Built-in floating point types */
			BUILTIN_TYPE n = DEREF_ntype(ftype_basic_no(ft));
			unsigned m = base_token[n].no;
			if (m != ARITH_none) {
				/* Look up special token number */
				int tn = base_token[n].tok;
				tok = special_no(tn);
				COPY_ulong(ftype_ftok(ft), tok);
			}
		} else if (IS_ftype_token(ft)) {
			/* Tokenised floating point types */
			IDENTIFIER tk = DEREF_id(ftype_token_tok(ft));
			DECL_SPEC ds = DEREF_dspec(id_storage(tk));
			if (ds & dspec_auto) {
				/* Floating point token parameters */
				BITSTREAM *ts;
				bs = enc_special(bs, TOK_convert);
				ts = start_bitstream(NIL(FILE), bs->link);
				ts = enc_flvar_no(ts, ft);
				bs = enc_bitstream(bs, ts);
				return bs;
			}
		}
		if (tok == LINK_NONE) {
			/* Define the variety token */
			string s = NULL;
			BITSTREAM *ts, *us;
			if (output_all) {
				t = qualify_type(t, cv_none, 0);
				s = mangle_tname("~cpp.ftype.", t);
			}
			tok = capsule_no(s, VAR_token);
			COPY_ulong(ftype_ftok(ft), tok);
			ts = enc_tokdef_start(tok, "F", NIL(ulong), 1);
			ts = enc_special(ts, TOK_convert);
			us = start_bitstream(NIL(FILE), ts->link);
			us = enc_flvar_no(us, ft);
			ts = enc_bitstream(ts, us);
			enc_tokdef_end(tok, ts);
		}
	}

	/* Encode the token application */
	tok = link_no(bs, tok, VAR_token);
	ENC_flvar_apply_token(bs);
	ENC_make_tok(bs, tok);
	ENC_LEN_SMALL(bs, 0);
	return bs;
}


/*
    This routine adds the bitfield type t to the bitstream bs as a TDF
    FLOATING BITFIELD.
*/

BITSTREAM *
enc_bfvar(BITSTREAM *bs, TYPE t)
{
	INT_TYPE it = DEREF_itype(type_bitfield_defn(t));
	ulong m = DEREF_ulong(itype_itok(it));
	if (m == LINK_NONE) {
		static LIST(INT_TYPE)bftypes = NULL_list(INT_TYPE);
		LIST(INT_TYPE)p = bftypes;
		while (!IS_NULL_list(p)) {
			INT_TYPE is = DEREF_itype(HEAD_list(p));
			if (eq_itype(it, is)) {
				m = DEREF_ulong(itype_itok(is));
				COPY_ulong(itype_itok(it), m);
				break;
			}
			p = TAIL_list(p);
		}
		if (IS_NULL_list(p)) {
			/* Add bitfield type to list */
			CONS_itype(it, bftypes, bftypes);
		}
	}
	bs = enc_variety(bs, t);
	return bs;
}


/*
    This routine adds the code number for the integral or floating point
    type t to the bitstream bs.
*/

BITSTREAM *
enc_arith(BITSTREAM *bs, TYPE t, int alt)
{
	unsigned n;
	BUILTIN_TYPE bt;
	if (!IS_NULL_type(t)) {
		switch (TAG_type(t)) {
		case type_integer_tag:
		case type_enumerate_tag: {
			/* Integral and enumeration types */
			INT_TYPE it = find_itype(t);
			bs = enc_var_no(bs, it, alt);
			return bs;
		}
		case type_floating_tag: {
			/* Floating point types */
			FLOAT_TYPE ft = DEREF_ftype(type_floating_rep(t));
			bs = enc_flvar_no(bs, ft);
			return bs;
		}
		case type_ptr_tag:
		case type_ref_tag: {
			/* Pointer types */
			bs = enc_special(bs, TOK_ptr_rep);
			return bs;
		}
		}
	}
	bt = is_builtin_type(t, 0);
	if (alt) {
		n = base_token[bt].alt;
	} else {
		n = base_token[bt].no;
	}
	bs = enc_make_snat(bs,(int)n);
	return bs;
}


/*
    This routine checks whether the class t represents a token application.
*/

int
is_tokenised_class(TYPE t)
{
	if (!IS_NULL_type(t) && IS_type_token(t)) {
		IDENTIFIER id = DEREF_id(type_token_tok(t));
		if (IS_id_token(id)) {
			return 1;
		}
	}
	return 0;
}


/*
    This routine adds the alignment of the type t to the bitstream bs
    as a TDF ALIGNMENT.
*/

BITSTREAM *
enc_alignment(BITSTREAM *bs, TYPE t)
{
	if (IS_NULL_type(t)) {
		/* This shouldn't happen */
		t = type_sint;
	}
	switch (TAG_type(t)) {
	case type_ptr_tag:
	case type_ref_tag: {
		/* Pointer alignment */
		TYPE s = DEREF_type(type_ptr_etc_sub(t));
		switch (TAG_type(s)) {
		case type_top_tag:
		case type_bottom_tag: {
			/* Generic pointer */
			ENC_alignment(bs);
			bs = enc_special(bs, TOK_ptr_void);
			break;
		}
		case type_func_tag: {
			/* Function pointer */
			ENC_alignment(bs);
			ENC_proc(bs);
			break;
		}
		default : {
			/* Simple pointers */
			ENC_alignment(bs);
			ENC_pointer(bs);
			ENC_alignment(bs);
			ENC_top(bs);
			break;
		}
		}
		break;
	}
	case type_array_tag: {
		/* Array types */
		TYPE s = DEREF_type(type_array_sub(t));
		bs = enc_alignment(bs, s);
		break;
	}
	case type_compound_tag: {
		/* Compound types */
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		TYPE s = DEREF_type(ctype_form(ct));
		if (is_tokenised_class(s)) {
			ENC_alignment(bs);
			bs = enc_shape(bs, s);
		} else {
			bs = enc_al_ctype(bs, ct);
		}
		break;
	}
	case type_token_tag: {
		/* Tokenised types */
		IDENTIFIER id = DEREF_id(type_token_tok(t));
		ulong n = DEREF_ulong(id_no(id));
		if (n == LINK_TOKDEF) {
			/* Allow for recursive tokenised types */
			bs = enc_special(bs, TOK_empty_align);
		} else {
			ENC_alignment(bs);
			bs = enc_shape(bs, t);
		}
		break;
	}
	default: {
		/* Other types are simple */
		ENC_alignment(bs);
		bs = enc_shape(bs, t);
		break;
	}
	}
	return bs;
}


/*
    This routine checks whether the alignment of the type t is of the
    simple form 'alignment ( t )'.
*/

static int
simple_alignment(TYPE t)
{
	if (!IS_NULL_type(t)) {
		switch (TAG_type(t)) {
		case type_array_tag: {
			/* Array types */
			TYPE s = DEREF_type(type_array_sub(t));
			return simple_alignment(s);
		}
		case type_compound_tag: {
			/* Compound types */
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
			TYPE s = DEREF_type(ctype_form(ct));
			if (!is_tokenised_class(s)) {
				CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
				if (!(ci & cinfo_complete)) {
					return 0;
				}
				if (!(ci & cinfo_defined)) {
					return 0;
				}
				if (ci & cinfo_recursive) {
					return 0;
				}
			}
			break;
		}
		case type_token_tag: {
			/* Tokenised types */
			IDENTIFIER id = DEREF_id(type_token_tok(t));
			ulong n = DEREF_ulong(id_no(id));
			if (n == LINK_TOKDEF) {
				return 0;
			}
			break;
		}
		}
	}
	return 1;
}


/*
    This routine adds the offset of the type t to the bitstream bs.
*/

BITSTREAM *
enc_shape_offset(BITSTREAM *bs, TYPE t)
{
	if (!IS_NULL_type(t) && IS_type_array(t)) {
		/* Allow for variable-sized arrays */
		NAT n = DEREF_nat(type_array_size(t));
		if (!IS_NULL_nat(n) && IS_nat_calc(n)) {
			EXP e = DEREF_exp(nat_calc_value(n));
			TYPE s = DEREF_type(type_array_sub(t));
			ENC_offset_mult(bs);
			bs = enc_shape_offset(bs, s);
			bs = enc_exp(bs, e);
			return bs;
		}
	}
	if (simple_alignment(t)) {
		/* Use token as shorthand */
		if (EQ_type(t, type_char)) {
			bs = enc_special(bs, TOK_char_offset);
		} else {
			BITSTREAM *ts = start_bitstream(NIL(FILE), bs->link);
			bs = enc_special(bs, TOK_shape_offset);
			ts = enc_shape(ts, t);
			bs = enc_bitstream(bs, ts);
		}
	} else {
		/* Output explicit instructions */
		ENC_offset_pad(bs);
		bs = enc_alignment(bs, t);
		ENC_shape_offset(bs);
		bs = enc_shape(bs, t);
	}
	return bs;
}


/*
    This routine adds the offset off to the bitstream bs as a TDF EXP.
*/

BITSTREAM *
enc_offset(BITSTREAM *bs, OFFSET off)
{
	if (IS_NULL_off(off)) {
		ENC_offset_zero(bs);
		bs = enc_alignment(bs, type_sint);
		return bs;
	}
	ASSERT(ORDER_off == 13);
	switch (TAG_off(off)) {
	case off_zero_tag: {
		/* Zero offsets */
		TYPE t = DEREF_type(off_zero_type(off));
		ENC_offset_zero(bs);
		bs = enc_alignment(bs, t);
		break;
	}
	case off_type_tag: {
		/* Type offsets */
		TYPE t = DEREF_type(off_type_type(off));
		bs = enc_shape_offset(bs, t);
		break;
	}
	case off_extra_tag: {
		/* Extra allocator offset */
		TYPE t = DEREF_type(off_extra_type(off));
		int n = DEREF_int(off_extra_scale(off));
		bs = enc_extra_offset(bs, t, off_size_t, n);
		break;
	}
	case off_array_tag: {
		/* Array offsets */
		TYPE t = DEREF_type(off_array_type(off));
		unsigned n = DEREF_unsigned(off_array_arg(off));
		if (n == 0) {
			ENC_offset_zero(bs);
			bs = enc_alignment(bs, t);
		} else if (n == 1) {
			bs = enc_shape_offset(bs, t);
		} else {
			ENC_offset_mult(bs);
			bs = enc_shape_offset(bs, t);
			ENC_make_int(bs);
			bs = enc_variety(bs, type_sint);
			ENC_make_signed_nat(bs);
			ENC_OFF(bs);
			ENC_INT(bs, n);
		}
		break;
	}
	case off_base_tag: {
		/* Base class offsets */
		GRAPH gr = DEREF_graph(off_base_graph(off));
		bs = enc_base(bs, gr, 0);
		break;
	}
	case off_deriv_tag: {
		/* Derived class offsets */
		GRAPH gr = DEREF_graph(off_deriv_graph(off));
		bs = enc_base(bs, gr, 0);
		break;
	}
	case off_member_tag: {
		/* Member offsets */
		IDENTIFIER id = DEREF_id(off_member_id(off));
		bs = enc_member(bs, id);
		break;
	}
	case off_ptr_mem_tag: {
		/* Pointer to member offsets */
		BITSTREAM *ts;
		EXP a = DEREF_exp(off_ptr_mem_arg(off));
		TYPE s = DEREF_type(exp_type(a));
		s = DEREF_type(type_ptr_mem_sub(s));
		bs = enc_special(bs, TOK_pm_offset);
		ts = start_bitstream(NIL(FILE), bs->link);
		ts = enc_exp(ts, a);
		ts = enc_alignment(ts, s);
		bs = enc_bitstream(bs, ts);
		break;
	}
	case off_negate_tag: {
		/* Offset negations */
		OFFSET off1 = DEREF_off(off_negate_arg(off));
		ENC_offset_negate(bs);
		bs = enc_offset(bs, off1);
		break;
	}
	case off_plus_tag: {
		/* Offset additions */
		OFFSET off1 = DEREF_off(off_plus_arg1(off));
		OFFSET off2 = DEREF_off(off_plus_arg2(off));
		if (!IS_NULL_off(off1)) {
			ENC_offset_add(bs);
			bs = enc_offset(bs, off1);
		}
		bs = enc_offset(bs, off2);
		break;
	}
	case off_mult_tag: {
		/* Offset multiplications */
		OFFSET off1 = DEREF_off(off_mult_arg1(off));
		EXP a = DEREF_exp(off_mult_arg2(off));
		ENC_offset_mult(bs);
		bs = enc_offset(bs, off1);
		bs = enc_exp(bs, a);
		break;
	}
	case off_ptr_diff_tag: {
		/* Difference of two pointers */
		EXP a = DEREF_exp(off_ptr_diff_ptr1(off));
		EXP b = DEREF_exp(off_ptr_diff_ptr2(off));
		ENC_subtract_ptrs(bs);
		bs = enc_exp(bs, a);
		bs = enc_exp(bs, b);
		break;
	}
	case off_token_tag: {
		/* Token applications */
		IDENTIFIER tok = DEREF_id(off_token_tok(off));
		LIST(TOKEN)args = DEREF_list(off_token_args(off));
		bs = enc_token(bs, tok, args);
		break;
	}
	default : {
		/* Illegal offset */
		ENC_offset_zero(bs);
		bs = enc_alignment(bs, type_sint);
		break;
	}
	}
	return bs;
}


/*
    This routine adds an expression representing n times the offset off
    rounded up to the alignment of t to the bitstream bs.
*/

BITSTREAM *
enc_extra_offset(BITSTREAM *bs, TYPE t, OFFSET off, int n)
{
	if (n == 0) {
		ENC_offset_zero(bs);
		bs = enc_alignment(bs, t);
	} else {
		if (n < 0) {
			ENC_offset_negate(bs);
			n = -n;
		}
		if (n == 1) {
			BITSTREAM *ts;
			bs = enc_special(bs, TOK_extra_offset);
			ts = start_bitstream(NIL(FILE), bs->link);
			ts = enc_alignment(ts, t);
			ts = enc_offset(ts, off);
			bs = enc_bitstream(bs, ts);
		} else {
			ENC_offset_mult(bs);
			bs = enc_extra_offset(bs, t, off, 1);
			bs = enc_make_int(bs, type_sint, n);
		}
	}
	return bs;
}


/*
    This routine adds the expression formed by adding the offset off
    to the pointer a to the bitstream bs.  virt is true for a virtual
    base offset.
*/

BITSTREAM *
enc_add_ptr(BITSTREAM *bs, EXP a, ulong n, OFFSET off, int virt)
{
	if (IS_NULL_off(off)) {
		if (n == LINK_NONE) {
			bs = enc_exp(bs, a);
		} else {
			ENC_exp_apply_token(bs);
			ENC_make_tok(bs, n);
			ENC_LEN_SMALL(bs, 0);
		}
		return bs;
	}
	ASSERT(ORDER_off == 13);
	switch (TAG_off(off)) {
	case off_base_tag: {
		/* Base class offsets */
		GRAPH gr = DEREF_graph(off_base_graph(off));
		DECL_SPEC acc = DEREF_dspec(graph_access(gr));
		if (virt && (acc & dspec_mutable)) {
			/* Virtual base offset */
			bs = enc_add_base(bs, off, NULL_off);
			bs = enc_add_ptr(bs, a, n, NULL_off, 0);
			bs = enc_end_base(bs, off, NULL_off);
			return bs;
		}
		if (acc & dspec_ignore) {
			/* Null base offset */
			bs = enc_add_ptr(bs, a, n, NULL_off, 0);
			return bs;
		}
		break;
	}
	case off_deriv_tag: {
		/* Derived class offsets */
		GRAPH gr = DEREF_graph(off_deriv_graph(off));
		DECL_SPEC acc = DEREF_dspec(graph_access(gr));
		if (virt && (acc & dspec_mutable)) {
			/* Virtual base offset */
			OFFSET off1, off2;
			gr = min_base_class(gr);
			off = DEREF_off(graph_off(gr));
			if (IS_off_deriv(off)) {
				off1 = DEREF_off(off_deriv_direct(off));
				off2 = DEREF_off(off_deriv_indirect(off));
			} else {
				off1 = off;
				off2 = NULL_off;
			}
			bs = enc_add_base(bs, off1, off2);
			bs = enc_add_ptr(bs, a, n, NULL_off, 0);
			bs = enc_end_base(bs, off1, off2);
			return bs;
		}
		if (acc & dspec_ignore) {
			/* Null base offset */
			bs = enc_add_ptr(bs, a, n, NULL_off, 0);
			return bs;
		}
		break;
	}
	case off_plus_tag: {
		/* Offset additions */
		OFFSET off1 = DEREF_off(off_plus_arg1(off));
		OFFSET off2 = DEREF_off(off_plus_arg2(off));
		if (is_zero_offset(off2)) {
			bs = enc_add_ptr(bs, a, n, off1, virt);
		} else {
			ENC_add_to_ptr(bs);
			bs = enc_add_ptr(bs, a, n, off1, virt);
			bs = enc_offset(bs, off2);
		}
		return bs;
	}
	}

	/* Other offsets */
	if (is_zero_offset(off)) {
		bs = enc_add_ptr(bs, a, n, NULL_off, 0);
	} else {
		ENC_add_to_ptr(bs);
		bs = enc_add_ptr(bs, a, n, NULL_off, 0);
		bs = enc_offset(bs, off);
	}
	return bs;
}


/*
    This routine adds the type t to the bitstream bs as a TDF SHAPE.
*/

BITSTREAM *
enc_shape(BITSTREAM *bs, TYPE t)
{
	if (IS_NULL_type(t)) {
		/* This shouldn't happen */
		t = type_sint;
	}
	ASSERT(ORDER_type == 18);
	switch (TAG_type(t)) {
	case type_integer_tag:
	case type_enumerate_tag: {
		/* Integral and enumeration types */
		ENC_integer(bs);
		bs = enc_variety(bs, t);
		break;
	}
	case type_floating_tag: {
		/* Floating point types */
		ENC_floating(bs);
		bs = enc_flvar(bs, t);
		break;
	}
	case type_top_tag: {
		/* The top type */
		ENC_top(bs);
		break;
	}
	case type_bottom_tag: {
		/* The bottom type */
		ENC_bottom(bs);
		break;
	}
	case type_ptr_tag:
	case type_ref_tag: {
		/* Pointer types */
		TYPE s = DEREF_type(type_ptr_etc_sub(t));
		switch (TAG_type(s)) {
		case type_top_tag:
		case type_bottom_tag: {
			/* Generic pointer */
			bs = enc_special(bs, TOK_ptr_void);
			break;
		}
		case type_func_tag: {
			/* Function pointer */
			ENC_proc(bs);
			break;
		}
		default : {
			/* Normal pointer */
			ENC_pointer(bs);
			bs = enc_alignment(bs, s);
			break;
		}
		}
		break;
	}
	case type_ptr_mem_tag: {
		/* Pointer to member types */
		TYPE s = DEREF_type(type_ptr_mem_sub(t));
		if (IS_type_func(s)) {
			bs = enc_special(bs, TOK_pmf_type);
		} else {
			bs = enc_special(bs, TOK_pm_type);
		}
		break;
	}
	case type_func_tag: {
		/* Function types */
		ENC_proc(bs);
		break;
	}
	case type_array_tag: {
		/* Array types */
		NAT n = DEREF_nat(type_array_size(t));
		TYPE s = DEREF_type(type_array_sub(t));
		ENC_nof(bs);
		bs = enc_nat(bs, n, 1);
		bs = enc_shape(bs, s);
		break;
	}
	case type_bitfield_tag: {
		/* Bitfield types */
		ENC_bitfield(bs);
		bs = enc_bfvar(bs, t);
		break;
	}
	case type_compound_tag: {
		/* Compound types */
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		TYPE s = DEREF_type(ctype_form(ct));
		if (is_tokenised_class(s)) {
			bs = enc_shape(bs, s);
		} else {
			bs = enc_ctype(bs, ct);
		}
		break;
	}
	case type_token_tag: {
		/* Tokenised types */
		IDENTIFIER tok = DEREF_id(type_token_tok(t));
		LIST(TOKEN)args = DEREF_list(type_token_args(t));
		if (IS_id_token(tok)) {
			bs = enc_token(bs, tok, args);
		} else {
			/* This case shouldn't occur */
			bs = enc_shape(bs, type_sint);
		}
		break;
	}
	case type_templ_tag: {
		/* Template types */
		TYPE s = DEREF_type(type_templ_defn(t));
		bs = enc_shape(bs, s);
		break;
	}
	case type_dummy_tag: {
		/* Dummy special token types */
		int tok = DEREF_int(type_dummy_tok(t));
#if LANGUAGE_CPP
		if (tok == TOK_vtab_type) {
			bs = enc_vtable_shape(bs, size_dummy_vtab);
			break;
		}
#endif
		bs = enc_special(bs, tok);
		break;
	}
	default: {
		/* This case shouldn't occur */
		bs = enc_shape(bs, type_sint);
		break;
	}
	}
	return bs;
}


/*
    This routine returns true if the types s and t have the same
    representation as shapes (or alignments if ptr is true) in TDF.
*/

int
eq_type_rep(TYPE s, TYPE t, int ptr)
{
	unsigned ns, nt;
	if (EQ_type(s, t)) {
		return 1;
	}
	if (IS_NULL_type(s) || IS_NULL_type(t)) {
		return 0;
	}
	ns = TAG_type(s);
	nt = TAG_type(t);

	/* Check the first type */
	switch (ns) {
	case type_top_tag:
	case type_bottom_tag: {
		/* Top and bottom types */
		if (nt == ns) {
			return 1;
		}
		if (nt == type_top_tag || nt == type_bottom_tag) {
			/* alignment ( top ) == alignment ( bottom ) */
			return ptr;
		}
		break;
	}
	case type_ptr_tag:
	case type_ref_tag: {
		/* Pointer and reference types */
		if (nt == type_ptr_tag || nt == type_ref_tag) {
			TYPE ps, pt;
			if (ptr) {
				/* alignment ( pointer ( s ) ) is constant */
				return 1;
			}
			ps = DEREF_type(type_ptr_etc_sub(s));
			pt = DEREF_type(type_ptr_etc_sub(t));
			return eq_type_rep(ps, pt, 1);
		}
		break;
	}
	case type_ptr_mem_tag: {
		/* Pointer to member types */
		if (nt == type_ptr_mem_tag) {
			TYPE ps = DEREF_type(type_ptr_mem_sub(s));
			TYPE pt = DEREF_type(type_ptr_mem_sub(t));
			if (IS_type_func(ps)) {
				if (IS_type_func(pt)) {
					/* Pointers to member functions */
					return 1;
				}
			} else {
				if (!IS_type_func(pt)) {
					/* Pointers to data members */
					return 1;
				}
			}
		}
		break;
	}
	case type_func_tag: {
		/* Function types */
		if (nt == type_func_tag) {
			/* All functions have the same representation */
			return 1;
		}
		break;
	}
	case type_array_tag: {
		/* Array types */
		if (ptr) {
			/* alignment ( nof ( n, s ) ) == alignment ( s ) */
			TYPE ps = DEREF_type(type_array_sub(s));
			return eq_type_rep(ps, t, 1);
		}
		if (nt == type_array_tag) {
			NAT ms = DEREF_nat(type_array_size(s));
			NAT mt = DEREF_nat(type_array_size(t));
			if (EQ_nat(ms, mt) || eq_nat(ms, mt)) {
				TYPE ps = DEREF_type(type_array_sub(s));
				TYPE pt = DEREF_type(type_array_sub(t));
				return eq_type_rep(ps, pt, 0);
			}
		}
		break;
	}
	case type_enumerate_tag: {
		/* Enumeration types */
		ENUM_TYPE es = DEREF_etype(type_enumerate_defn(s));
		TYPE ps = DEREF_type(etype_rep(es));
		return eq_type_rep(ps, t, ptr);
	}
	}

	/* Check the second type */
	switch (nt) {
	case type_array_tag: {
		/* Array types */
		if (ptr) {
			/* alignment ( nof ( n, t ) ) == alignment ( t ) */
			TYPE pt = DEREF_type(type_array_sub(t));
			return eq_type_rep(s, pt, 1);
		}
		break;
	}
	case type_enumerate_tag: {
		/* Enumeration types */
		ENUM_TYPE et = DEREF_etype(type_enumerate_defn(t));
		TYPE pt = DEREF_type(etype_rep(et));
		return eq_type_rep(s, pt, ptr);
	}
	}

	/* Compare the types */
	if (ns == nt) {
		if (ptr) {
			return eq_type_offset(s, t);
		}
		return eq_type_unqual(s, t);
	}
	return 0;
}


#endif /* TDF_OUTPUT */
