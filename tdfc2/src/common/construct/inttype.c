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

#include "config.h"
#include "c_types.h"
#include "exp_ops.h"
#include "etype_ops.h"
#include "ftype_ops.h"
#include "id_ops.h"
#include "itype_ops.h"
#include "tok_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "basetype.h"
#include "constant.h"
#include "convert.h"
#include "chktype.h"
#include "dump.h"
#include "exception.h"
#include "hash.h"
#include "interface.h"
#include "inttype.h"
#include "mangle.h"
#include "print.h"
#include "syntax.h"
#include "tok.h"
#include "tokdef.h"
#include "token.h"


/*
    These values give the fundamental information about the built-in
    types, the sizes of the various types, whether char is signed, and
    whether the signed ranges are full (for example [-128,127]) or
    symmetric (for example [-127,127]).
*/

BASE_INFO basetype_info[ORDER_ntype] = {
	{ btype_sint, 16, UINT_MAX, btype_signed, 1, NULL_type },
	{ btype_char, 8, UINT_MAX, btype_none, 1, NULL_type },
	{ btype_schar, 8, UINT_MAX, btype_signed, 1, NULL_type },
	{ btype_uchar, 8, UINT_MAX, btype_unsigned, 1, NULL_type },
	{ btype_sshort, 16, UINT_MAX, btype_signed, 1, NULL_type },
	{ btype_ushort, 16, UINT_MAX, btype_unsigned, 1, NULL_type },
	{ btype_sint, 16, UINT_MAX, btype_signed, 1, NULL_type },
	{ btype_uint, 16, UINT_MAX, btype_unsigned, 1, NULL_type },
	{ btype_slong, 32, UINT_MAX, btype_signed, 1, NULL_type },
	{ btype_ulong, 32, UINT_MAX, btype_unsigned, 1, NULL_type },
	{ btype_sllong, 32, UINT_MAX, btype_signed, 0, NULL_type },
	{ btype_ullong, 32, UINT_MAX, btype_unsigned, 0, NULL_type },
	{ btype_float, 0, 0, btype_none, 1, NULL_type },
	{ btype_double, 0, 0, btype_none, 1, NULL_type },
	{ btype_ldouble, 0, 0, btype_none, 1, NULL_type },
	{ btype_void, 0, 0, btype_none, 1, NULL_type },
	{ btype_bottom, 0, 0, btype_none, 1, NULL_type },
	{ btype_bool, 1, 1, btype_unsigned, LANGUAGE_CPP, NULL_type },
	{ btype_ptrdiff_t, 16, UINT_MAX, btype_signed, 0, NULL_type },
	{ btype_size_t, 16, UINT_MAX, btype_unsigned, 0, NULL_type },
	{ btype_wchar_t, 8, UINT_MAX, btype_none, LANGUAGE_CPP, NULL_type },
	{ btype_ellipsis, 0, UINT_MAX, btype_none, 0, NULL_type }
};


/*
    These variables give various standard lists of types.
*/

LIST(TYPE) all_int_types = NULL_list(TYPE);
LIST(TYPE) all_prom_types = NULL_list(TYPE);
LIST(TYPE) all_llong_types = NULL_list(TYPE);


/*
    This table gives the severity levels for conversions between the
    various built-in types (the source types are listed along the right
    hand side, and the destination types along the top).  The first row
    and column are just copies of the second.  The values are as follows
    (from safest to most unsafe):

	0 = always safe					SAFE
	1 = almost certainly safe			SAFE
	2 = safe on real machines			SAFE
	3 = safe on 32-bit machines			DEPENDS
	4 = safe on 64-bit machines			DEPENDS
	5 = same size, possibly different sign		UNSAFE
	6 = same size, different sign conversion	UNSAFE
	7 = signed to unsigned conversion		UNSAFE
	8 = always unsafe				UNSAFE
	9 = illegal type in conversion			UNSAFE

    min_builtin_cast determines the maximum value which is considered
    probably safe by the program.  safe_builtin_cast gives the maximum
    value which is considered possibly safe.  max_builtin_cast gives the
    minimum threshold value for error reporting.
*/

unsigned char builtin_casts[ORDER_ntype][ORDER_ntype] = {
	 /* CH CH SC UC SS US SI UI SL UL SX UX FL DB LD VD BT BL PD SZ WC EL */
 /* CH */ { 0, 0, 5, 5, 1, 7, 1, 7, 1, 7, 1, 7, 8, 8, 8, 9, 9, 8, 1, 7, 0, 0 },
 /* CH */ { 0, 0, 5, 5, 1, 7, 1, 7, 1, 7, 1, 7, 8, 8, 8, 9, 9, 8, 1, 7, 0, 0 },
 /* SC */ { 5, 5, 0, 6, 0, 7, 0, 7, 0, 7, 0, 7, 8, 8, 8, 9, 9, 8, 1, 7, 8, 0 },
 /* UC */ { 5, 5, 6, 0, 2, 0, 2, 0, 2, 0, 2, 0, 8, 8, 8, 9, 9, 8, 2, 1, 8, 0 },
 /* SS */ { 8, 8, 8, 8, 0, 6, 0, 7, 0, 7, 0, 7, 8, 8, 8, 9, 9, 8, 2, 7, 8, 0 },
 /* US */ { 8, 8, 8, 8, 6, 0, 3, 0, 2, 0, 2, 0, 8, 8, 8, 9, 9, 8, 3, 2, 8, 0 },
 /* SI */ { 8, 8, 8, 8, 8, 8, 0, 6, 0, 7, 0, 7, 8, 8, 8, 9, 9, 8, 2, 7, 8, 0 },
 /* UI */ { 8, 8, 8, 8, 8, 8, 6, 0, 4, 0, 4, 0, 8, 8, 8, 9, 9, 8, 7, 3, 8, 0 },
 /* SL */ { 8, 8, 8, 8, 8, 8, 8, 8, 0, 6, 0, 7, 8, 8, 8, 9, 9, 8, 4, 7, 8, 0 },
 /* UL */ { 8, 8, 8, 8, 8, 8, 8, 8, 6, 0, 4, 0, 8, 8, 8, 9, 9, 8, 8, 4, 8, 0 },
 /* SX */ { 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 6, 8, 8, 8, 9, 9, 8, 4, 7, 8, 0 },
 /* UX */ { 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 6, 0, 8, 8, 8, 9, 9, 8, 8, 4, 8, 0 },
 /* FL */ { 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 0, 0, 9, 9, 8, 8, 8, 8, 0 },
 /* DB */ { 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 0, 9, 9, 8, 8, 8, 8, 0 },
 /* LD */ { 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 9, 9, 8, 8, 8, 8, 0 },
 /* VD */ { 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 0 },
 /* BT */ { 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 0 },
 /* BL */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0 },
 /* PD */ { 8, 8, 8, 8, 8, 8, 3, 7, 0, 7, 0, 7, 8, 8, 8, 9, 9, 8, 0, 8, 8, 0 },
 /* SZ */ { 8, 8, 8, 8, 8, 8, 8, 3, 7, 0, 7, 0, 8, 8, 8, 9, 9, 8, 8, 0, 8, 0 },
 /* WC */ { 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 8, 8, 8, 0, 0 },
 /* EL */ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

int min_builtin_cast = 2;
int safe_builtin_cast = 4;
int max_builtin_cast = 3;


/*
    This routine copies the built-in cast values for type m into type n.
*/

static void
copy_builtin_cast(BUILTIN_TYPE n, BUILTIN_TYPE m)
{
	unsigned long i;
	for (i = 1; i < ORDER_ntype; i++) {
		builtin_casts[n][i] = builtin_casts[m][i];
		builtin_casts[i][n] = builtin_casts[i][m];
	}
	builtin_casts[n][n] = 0;
	builtin_casts[n][m] = 0;
	builtin_casts[m][n] = 0;
	builtin_casts[m][m] = 0;
	return;
}


/*
    This routine recalculates the table of built-in casts on the assumption
    that the type sizes given in basetype_info are exact.  The definition
    of what constitutes a safe conversion is adjusted accordingly.  Note
    that the conversions between char and signed/unsigned char are handled
    separately by set_char_type.
*/

void
set_exact_types(void)
{
	BUILTIN_TYPE n, m;
	BASE_INFO *p = basetype_info;
	for (n = ntype_char; n < ntype_ellipsis; n++) {
		for (m = ntype_char; m < ntype_ellipsis; m++) {
			unsigned char c = builtin_casts[n][m];
			if (c >= 1 && c <= 4) {
				unsigned bn = p[n].min_bits;
				unsigned bm = p[m].min_bits;
				BASE_TYPE sn = p[n].sign;
				BASE_TYPE sm = p[m].sign;
				if (sn == sm) {
					/* Same sign */
					if (bn <= bm) {
						c = 1;
					}
				} else if (sn & btype_unsigned) {
					/* n is unsigned */
					if (bn < bm) {
						c = 1;
					}
				} else if (sm & btype_signed) {
					/* m is signed */
					if (bn < bm) {
						c = 1;
					}
				}
				builtin_casts[n][m] = c;
			}
		}
	}
	min_builtin_cast = 1;
	safe_builtin_cast = 1;
	max_builtin_cast = 2;
	return;
}


/*
    This routine sets the type of char to be bt, which can be btype_signed,
    btype_unsigned, or btype_none.
*/

void
set_char_sign(BASE_TYPE bt)
{
	BASE_INFO *p = basetype_info;
	BUILTIN_TYPE nt = ntype_none;
	if (bt & btype_signed) {
		nt = ntype_schar;
		bt = p[nt].sign;
	} else if (bt & btype_unsigned) {
		nt = ntype_uchar;
		bt = p[nt].sign;
	}
	if (p[ntype_char].sign != bt) {
		p[ntype_char].sign = bt;
		builtin_casts[ntype_char][ntype_schar] = 5;
		builtin_casts[ntype_char][ntype_uchar] = 5;
		builtin_casts[ntype_schar][ntype_char] = 5;
		builtin_casts[ntype_uchar][ntype_char] = 5;
		builtin_casts[ntype_schar][ntype_wchar_t] = 8;
		builtin_casts[ntype_uchar][ntype_wchar_t] = 8;
		copy_builtin_cast(ntype_char, nt);
		builtin_casts[ntype_char][ntype_wchar_t] = 0;
		builtin_casts[nt][ntype_wchar_t] = 0;
	}
	return;
}


/*
    This routine defines the built-in type indicated by bt to be t.
*/

void
set_builtin_type(BASE_TYPE bt, TYPE t)
{
	/* Built-in integral types */
	INT_TYPE is, it;
	TYPE s = make_base_type(bt);
	if (!IS_type_integer(t)) {
		report(crt_loc, ERR_pragma_builtin_type(t));
		return;
	}
	is = DEREF_itype(type_integer_rep(s));
	it = DEREF_itype(type_integer_rep(t));
	if (!EQ_itype(is, it)) {
		TYPE r;
		int key;
		BUILTIN_TYPE ns = ntype_none;
		if (bt == btype_ptrdiff_t) {
			ns = ntype_ptrdiff_t;
		} else if (bt == btype_size_t) {
			ns = ntype_size_t;
		} else if (bt == btype_wchar_t) {
			ns = ntype_wchar_t;
		}
		key = basetype_info[ns].key;
		r = basetype_info[ns].set;
		basetype_info[ns].set = t;
		if (!IS_NULL_type(r)) {
			/* Check compatibility */
			ERROR err = NULL_err;
			IGNORE check_compatible(r, t, 0, &err, 0);
			if (!IS_NULL_err(err)) {
				report(crt_loc, err);
			}
		}
		if (!key) {
			/* Set integral type */
			TYPE p = DEREF_type(itype_prom(it));
			BUILTIN_TYPE nu = DEREF_ntype(itype_unprom(it));
			LIST(TYPE)cases = DEREF_list(itype_cases(it));
			COPY_type(itype_prom(is), p);
			COPY_ntype(itype_unprom(is), nu);
			COPY_list(itype_cases(is), cases);
			if (IS_itype_basic(it)) {
				BUILTIN_TYPE nt =
				    DEREF_ntype(itype_basic_no(it));
				copy_builtin_cast(ns, nt);
			}
		}
	}
	return;
}


/*
    This routine sets the implementation of 'long long' to be the
    real 'long long' type if big is true and 'long' otherwise.
*/

void
set_long_long_type(int big)
{
	if (big) {
		base_token[ntype_sllong].tok = TOK_signed_llong;;
		base_token[ntype_sllong].no = ARITH_sllong;;
		base_token[ntype_ullong].tok = TOK_unsigned_llong;;
		base_token[ntype_ullong].no = ARITH_ullong;;
	} else {
		base_token[ntype_sllong].tok = TOK_signed_long;;
		base_token[ntype_sllong].no = ARITH_slong;;
		base_token[ntype_ullong].tok = TOK_unsigned_long;;
		base_token[ntype_ullong].no = ARITH_ulong;;
	}
	return;
}


/*
    This routine checks whether the type t is a qualified version of a
    built-in type (including the semantic type if sem is true).  If so
    it returns the corresponding built-in type number.
*/

BUILTIN_TYPE
is_builtin_type(TYPE t, int sem)
{
	BUILTIN_TYPE nt = ntype_none;
	if (!IS_NULL_type(t)) {
		switch (TAG_type(t)) {
		case type_integer_tag: {
			INT_TYPE it = DEREF_itype(type_integer_rep(t));
			if (IS_itype_basic(it)) {
				nt = DEREF_ntype(itype_basic_no(it));
				if (sem) {
					/* Check semantic type */
					INT_TYPE is;
					is = DEREF_itype(type_integer_sem(t));
					if (IS_itype_basic(is)) {
						BUILTIN_TYPE ns;
						ns = DEREF_ntype(itype_basic_no(is));
						if (ns != nt)nt = ntype_none;
					} else {
						nt = ntype_none;
					}
				}
			}
			break;
		}
		case type_floating_tag: {
			FLOAT_TYPE ft = DEREF_ftype(type_floating_rep(t));
			if (IS_ftype_basic(ft)) {
				nt = DEREF_ntype(ftype_basic_no(ft));
			}
			break;
		}
		case type_top_tag:
			nt = ntype_void;
			break;
		case type_bottom_tag:
			nt = ntype_bottom;
			break;
		case type_pre_tag: {
			BASE_TYPE bt = DEREF_btype(type_pre_rep(t));
			if (bt == btype_ellipsis) {
				nt = ntype_ellipsis;
			}
			break;
		}
		}
	}
	return nt;
}


/*
    This routine expands the integral type it by replacing built-in types
    such as size_t by their definition.
*/

INT_TYPE
expand_itype(INT_TYPE it)
{
	if (!IS_NULL_itype(it) && IS_itype_basic(it)) {
		BUILTIN_TYPE nt = DEREF_ntype(itype_basic_no(it));
		TYPE t = basetype_info[nt].set;
		if (!IS_NULL_type(t) && !basetype_info[nt].key) {
			it = DEREF_itype(type_integer_rep(t));
		}
	}
	return it;
}


/*
    This routine defines any tokens for the built-in types from their
    set values.
*/

void
term_itypes(void)
{
	IDENTIFIER id = get_special(TOK_ptrdiff_t, 1);
	if (!IS_NULL_id(id)) {
		TYPE t = basetype_info[ntype_ptrdiff_t].set;
		if (!IS_NULL_type(t)) {
			IGNORE define_type_token(id, t, 0);
		}
	}
	id = get_special(TOK_size_t, 1);
	if (!IS_NULL_id(id)) {
		TYPE t = basetype_info[ntype_size_t].set;
		if (!IS_NULL_type(t)) {
			IGNORE define_type_token(id, t, 0);
		} else {
			TOKEN tok = DEREF_tok(id_token_sort(id));
			if (IS_tok_type(tok)) {
				/* Allow deduction of __size_t from size_t */
				t = DEREF_type(tok_type_value(tok));
				basetype_info[ntype_size_t].set = t;
			}
		}
	}
	id = get_special(TOK_size_t_2, 1);
	if (!IS_NULL_id(id)) {
		TYPE t = basetype_info[ntype_size_t].set;
		if (!IS_NULL_type(t)) {
			t = promote_type(t);
			IGNORE define_type_token(id, t, 0);
		}
	}
	id = get_special(TOK_wchar_t, 1);
	if (!IS_NULL_id(id)) {
		TYPE t = basetype_info[ntype_wchar_t].set;
		if (!IS_NULL_type(t)) {
			IGNORE define_type_token(id, t, 0);
		}
	}
	return;
}


/*
    This routine sets the promotion of type t to be s.  Note that this
    implies that s is its own promotion and that the conversion from t to
    s is deemed to be safe.
*/

void
set_promote_type(TYPE t, TYPE s, BUILTIN_TYPE ns)
{
	INT_TYPE it, is;
	BUILTIN_TYPE nt;
	if (!IS_type_integer(t)) {
		ENUM_TYPE et;
		if (!IS_type_enumerate(t)) {
			report(crt_loc, ERR_pragma_promote_type(t));
			return;
		}
		et = DEREF_etype(type_enumerate_defn(t));
		t = DEREF_type(etype_rep(et));
	}
	if (!IS_type_integer(s)) {
		ENUM_TYPE es;
		if (!IS_type_enumerate(s)) {
			report(crt_loc, ERR_pragma_promote_type(s));
			return;
		}
		es = DEREF_etype(type_enumerate_defn(s));
		s = DEREF_type(etype_rep(es));
	}

	/* Check previous definition */
	is = DEREF_itype(type_integer_rep(s));
	it = DEREF_itype(type_integer_rep(t));
	nt = DEREF_ntype(itype_unprom(it));
	if (nt != ntype_none) {
		ERROR err = NULL_err;
		TYPE p = DEREF_type(itype_prom(it));
		IGNORE check_compatible(p, s, 0, &err, 0);
		if (!IS_NULL_err(err)) {
			ERROR err2 = ERR_pragma_promote_compat(t);
			err = concat_error(err, err2);
			report(crt_loc, err);
		}
		if (nt != ntype_ellipsis) {
			ns = ntype_none;
		}
	}

	/* Set promoted type */
	if (ns != ntype_none) {
		LIST(TYPE) ps;
		TYPE p = make_itype(is, it);
		COPY_type(itype_prom(it), p);
		if (nt == ntype_none) {
			COPY_ntype(itype_unprom(it), ns);
		}
		ps = DEREF_list(itype_cases(is));
		if (EQ_list(ps, all_int_types)) {
			/* Restrict cases for is */
			COPY_list(itype_cases(is), all_prom_types);
		}
		if (IS_itype_basic(it)) {
			BUILTIN_TYPE n = DEREF_ntype(itype_basic_no(it));
			if (IS_itype_basic(is)) {
				/* Set conversion rank */
				BUILTIN_TYPE m =
				    DEREF_ntype(itype_basic_no(is));
				builtin_casts[n][m] = 0;
			}
			ns = n;
		}
		if (do_dump) {
			dump_promote(it, is);
		}
	}

	/* Set s to be its own promotion */
	if (!eq_itype(it, is)) {
		set_promote_type(s, s, ns);
	}
	return;
}


/*
    This routine sets the token used to calculate promoted types to be id.
*/

void
compute_promote_type(IDENTIFIER id)
{
	IDENTIFIER tid = resolve_token(id, "ZZ", 0);
	if (!IS_NULL_id(tid)) {
		set_special(TOK_promote, tid);
	}
	return;
}


/*
    This array is used to hold all the integral and floating point types,
    with all the cases of representation and semantics.
*/

static TYPE all_itypes[ORDER_ntype][ORDER_ntype];


/*
    This routine constructs an integral type with representation it and
    semantics is.  If the semantic type is the null type then the semantics
    are the same as the representation.
*/

TYPE
make_itype(INT_TYPE it, INT_TYPE is)
{
	TYPE r;
	if (IS_NULL_itype(is)) {
		is = it;
	}
	if (IS_itype_basic(it) && IS_itype_basic(is)) {
		BUILTIN_TYPE n = DEREF_ntype(itype_basic_no(it));
		BUILTIN_TYPE m = DEREF_ntype(itype_basic_no(is));
		r = all_itypes[n][m];
		if (IS_NULL_type(r)) {
			MAKE_type_integer(cv_none, it, is, r);
			all_itypes[n][m] = r;
		}
	} else {
		MAKE_type_integer(cv_none, it, is, r);
	}
	return r;
}


/*
    This routine constructs a floating point type with representation ft
    and semantics fs.
*/

TYPE
make_ftype(FLOAT_TYPE ft, FLOAT_TYPE fs)
{
	TYPE r;
	if (IS_NULL_ftype(fs)) {
		fs = ft;
	}
	if (IS_ftype_basic(ft)) {
		BUILTIN_TYPE n = DEREF_ntype(ftype_basic_no(ft));
		BUILTIN_TYPE m = DEREF_ntype(ftype_basic_no(fs));
		r = all_itypes[n][m];
		if (IS_NULL_type(r)) {
			MAKE_type_floating(cv_none, ft, fs, r);
			all_itypes[n][m] = r;
		}
	} else {
		MAKE_type_floating(cv_none, ft, fs, r);
	}
	return r;
}


/*
    This routine sets the promotion type of the integral type it to be
    ip.  If ip is the null type then a promotion type is created.  An
    integral type corresponding to it is returned.
*/

TYPE
promote_itype(INT_TYPE it, INT_TYPE ip)
{
	TYPE p;
	TYPE t = make_itype(it, it);
	if (IS_NULL_itype(ip)) {
		MAKE_itype_promote(NULL_type, all_prom_types, it, ip);
	} else {
		COPY_ntype(itype_unprom(ip), ntype_ellipsis);
		COPY_ntype(itype_unprom(it), ntype_ellipsis);
	}
	if (EQ_itype(it, ip)) {
		p = t;
	} else {
		p = make_itype(ip, it);
	}
	COPY_type(itype_prom(ip), p);
	COPY_type(itype_prom(it), p);
	return t;
}


/*
    The only difficult case in the basic arithmetic types is the combination
    of 'signed long' and 'unsigned int'.  The variable arith_slong_uint is
    used to hold this value.  If 'long long' is allowed then combining
    'signed long long' with 'unsigned long' or 'unsigned int' is also
    target dependent.
*/

static INT_TYPE arith_slong_uint;
static INT_TYPE arith_sllong_uint;
static INT_TYPE arith_sllong_ulong;


/*
    This routine finds the type to be used for arithmetic involving operands
    of promoted integral types t and s.  The operands a and b are passed
    in to enable the semantic type to be determined.  Note that for base
    integral types, because:

		ntype_sint < ntype_uint < ... < ntype_ullong

    the arithmetic type is, except in the cases listed above, the maximum
    of the two base type values.

		       | SI  UI  SL  UL  SX  UX
		    ---+-----------------------
		    SI | SI  UI  SL  UL  SX  UX
		    UI | UI  UI  ??  UL  ??  UX
		    SL | SL  ??  SL  UL  SX  UX
		    UL | UL  UL  UL  UL  ??  UX
		    SX | SX  ??  SX  ??  SX  UX
		    UX | UX  UX  UX  UX  UX  UX
*/

TYPE
arith_itype(TYPE t, TYPE s, EXP a, EXP b)
{
	TYPE r;
	if (IS_type_integer(t) && IS_type_integer(s)) {
		INT_TYPE ir;
		INT_TYPE it = DEREF_itype(type_integer_rep(t));
		INT_TYPE is = DEREF_itype(type_integer_rep(s));

		/* Find semantic type of result */
		INT_TYPE mr = NULL_itype;
		INT_TYPE mt = DEREF_itype(type_integer_sem(t));
		INT_TYPE ms = DEREF_itype(type_integer_sem(s));
		if (EQ_itype(mt, ms)) {
			/* Same semantic types */
			mr = mt;
		} else {
			/* Allow for variable semantics of constants */
			if (!IS_NULL_exp(a) && IS_exp_int_lit(a)) {
				if (!IS_NULL_exp(b) && IS_exp_int_lit(b)) {
					/* Leave to constant evaluation
					 * routines */
					/* EMPTY */
				} else {
					NAT n = DEREF_nat(exp_int_lit_nat(a));
					COPY_itype(type_integer_rep(s), ms);
					if (check_nat_range(s, n) == 0) {
						mr = ms;
					}
					COPY_itype(type_integer_rep(s), is);
				}
			} else if (!IS_NULL_exp(b) && IS_exp_int_lit(b)) {
				NAT n = DEREF_nat(exp_int_lit_nat(b));
				COPY_itype(type_integer_rep(t), mt);
				if (check_nat_range(t, n) == 0) {
					mr = mt;
				}
				COPY_itype(type_integer_rep(t), it);
			}
		}

		/* Find representation type of result */
		if (EQ_itype(it, is)) {
			r = make_itype(it, mr);
			return r;
		}
		if (IS_itype_basic(it)) {
			BUILTIN_TYPE nt = DEREF_ntype(itype_basic_no(it));
			if (IS_itype_basic(is)) {
				BUILTIN_TYPE bt = nt;
				BUILTIN_TYPE bs =
				    DEREF_ntype(itype_basic_no(is));
				if (bs > bt) {
					bt = bs;
					bs = nt;
					ir = is;
				} else {
					ir = it;
				}
				if (bt <= ntype_ullong) {
					if (bt == ntype_sllong) {
						if (bs == ntype_ulong) {
							ir = arith_sllong_ulong;
						}
						if (bs == ntype_uint) {
							ir = arith_sllong_uint;
						}
					} else if (bt == ntype_slong) {
						if (bs == ntype_uint) {
							ir = arith_slong_uint;
						}
					}
					r = make_itype(ir, mr);
					return r;
				}
			}
			if (nt == ntype_ullong) {
				r = make_itype(it, mr);
				return r;
			}
			if (nt == ntype_ulong &&
			    !basetype_info[ntype_sllong].key) {
				r = make_itype(it, mr);
				return r;
			}
			if (nt == ntype_sint) {
				r = make_itype(is, mr);
				return r;
			}
		}
		if (IS_itype_basic(is)) {
			BUILTIN_TYPE ns = DEREF_ntype(itype_basic_no(is));
			if (ns == ntype_ullong) {
				r = make_itype(is, mr);
				return r;
			}
			if (ns == ntype_ulong &&
			    !basetype_info[ntype_sllong].key) {
				r = make_itype(is, mr);
				return r;
			}
			if (ns == ntype_sint) {
				r = make_itype(it, mr);
				return r;
			}
		}

		/* Construct an arithmetic type */
		MAKE_itype_arith(NULL_type, all_prom_types, it, is, ir);
		r = promote_itype(ir, ir);
		if (!IS_NULL_itype(mr)) {
			r = make_itype(ir, mr);
		}
	} else {
		/* This shouldn't happen */
		r = t;
	}
	return r;
}


/*
    This routine sets the argument promotion type of the floating point
    type ft to be fp.  If fp is the null type then an argument promotion
    type is created.  A floating point type corresponding to ft is
    returned.
*/

TYPE
promote_ftype(FLOAT_TYPE ft, FLOAT_TYPE fp)
{
	TYPE t, p;
	init_float(ft);
	t = make_ftype(ft, ft);
	if (IS_NULL_ftype(fp)) {
		MAKE_ftype_arg_promote(NULL_type, ft, fp);
		init_float(fp);
	}
	if (EQ_ftype(ft, fp)) {
		p = t;
	} else {
		p = make_ftype(fp, ft);
	}
	COPY_type(ftype_arg_prom(ft), p);
	COPY_type(ftype_arg_prom(fp), p);
	return t;
}


/*
    This routine finds the type to be used for arithmetic involving operands
    of floating point types t and s.
*/

TYPE
arith_ftype(TYPE t, TYPE s)
{
	TYPE r;
	if (IS_type_floating(t) && IS_type_floating(s)) {
		FLOAT_TYPE fr;
		FLOAT_TYPE ft = DEREF_ftype(type_floating_rep(t));
		FLOAT_TYPE fs = DEREF_ftype(type_floating_rep(s));

		/* Find the arithmetic type */
		if (EQ_ftype(ft, fs)) {
			return t;
		} else if (IS_ftype_basic(ft)) {
			BUILTIN_TYPE nt = DEREF_ntype(ftype_basic_no(ft));
			if (IS_ftype_basic(fs)) {
				BUILTIN_TYPE ns =
				    DEREF_ntype(ftype_basic_no(fs));
				if (nt == ntype_ldouble) {
					return t;
				}
				if (ns == ntype_ldouble) {
					return s;
				}
				if (nt == ntype_double) {
					return t;
				}
				if (ns == ntype_double) {
					return s;
				}
				return t;
			}
			if (nt == ntype_ldouble) {
				return t;
			}
			if (nt == ntype_float) {
				return s;
			}
		} else if (IS_ftype_basic(fs)) {
			BUILTIN_TYPE ns = DEREF_ntype(ftype_basic_no(fs));
			if (ns == ntype_ldouble) {
				return s;
			}
			if (ns == ntype_float) {
				return t;
			}
		}

		/* Construct an arithmetic type */
		MAKE_ftype_arith(NULL_type, ft, fs, fr);
		r = promote_ftype(fr, NULL_ftype);
	} else {
		/* This shouldn't happen */
		r = t;
	}
	return r;
}


/*
    This routine finds the type corresponding to the keyword with lexical
    token number tok.
*/

BASE_TYPE
key_type(int tok)
{
	BASE_TYPE bs = btype_none;
	switch (tok) {
	case lex_bool:
		bs = btype_bool;
		break;
	case lex_ptrdiff_Ht:
		bs = btype_ptrdiff_t;
		break;
	case lex_size_Ht:
		bs = btype_size_t;
		break;
	case lex_wchar_Ht:
		bs = btype_wchar_t;
		break;
	}
	return bs;
}


/*
    This routine creates a tokenised integral type from the token id
    and the token arguments args.
*/

TYPE
apply_itype_token(IDENTIFIER id, LIST(TOKEN) args)
{
	TYPE t;
	INT_TYPE it;

	/* Check for previous instance */
	if (IS_NULL_list(args)) {
		if (IS_id_token(id)) {
			IDENTIFIER tid = DEREF_id(id_token_alt(id));
			if (IS_id_type_alias(tid)) {
				t = DEREF_type(id_type_alias_defn(tid));
				t = copy_typedef(tid, t, cv_none);
				COPY_id(type_name(t), tid);
				return t;
			}
		}
	}

	/* Create new instance */
	MAKE_itype_token(NULL_type, all_int_types, id, args, it);
	t = promote_itype(it, NULL_itype);

	/* Allow for special tokens */
	if (IS_id_token(id)) {
		int tok = builtin_token(id);
		switch (tok) {
		case TOK_ptrdiff_t:
			t = type_ptrdiff_t;
			break;
		case TOK_size_t:
			t = type_size_t;
			break;
		case TOK_size_t_2:
			t = promote_type(type_size_t);
			break;
		case TOK_wchar_t:
			t = type_wchar_t;
			break;
		}
	}
	return t;
}


/*
    This routine creates a tokenised floating point type from the token
    id and the token arguments args.
*/

TYPE
apply_ftype_token(IDENTIFIER id, LIST(TOKEN) args)
{
	TYPE t;
	FLOAT_TYPE ft;

	/* Check for previous instance */
	if (IS_NULL_list(args)) {
		if (IS_id_token(id)) {
			IDENTIFIER tid = DEREF_id(id_token_alt(id));
			if (IS_id_type_alias(tid)) {
				t = DEREF_type(id_type_alias_defn(tid));
				t = copy_typedef(tid, t, cv_none);
				COPY_id(type_name(t), tid);
				return t;
			}
		}
	}

	/* Create new instance */
	MAKE_ftype_token(NULL_type, id, args, ft);
	t = promote_ftype(ft, NULL_ftype);
	return t;
}


/*
    This routine returns the sign of the type specified by bt.
*/

static BASE_TYPE
find_itype_sign(BASE_TYPE bt)
{
	BASE_TYPE sign;
	if (bt & btype_unsigned) {
		sign = btype_unsigned;
	} else if (bt & btype_signed) {
		sign = basetype_info[ntype_sint].sign;
	} else {
		sign = btype_none;
	}
	return sign;
}


/*
    This routine determines the minimum number of bits in the integral
    type it.  It also returns information on the the maximum number of
    bits and the sign of the type in the given pointer arguments.
*/

static unsigned
find_itype_size(INT_TYPE it, unsigned *mbits, BASE_TYPE *sign)
{
	unsigned sz;
	it = expand_itype(it);
	switch (TAG_itype(it)) {
	case itype_basic_tag: {
		/* Built-in types */
		BUILTIN_TYPE n = DEREF_ntype(itype_basic_no(it));
		sz = basetype_info[n].min_bits;
		*mbits = basetype_info[n].max_bits;
		*sign = basetype_info[n].sign;
		break;
	}
	case itype_bitfield_tag: {
		/* Bitfield types */
		NAT n = DEREF_nat(itype_bitfield_size(it));
		BASE_TYPE rep = DEREF_btype(itype_bitfield_rep(it));
		sz = (unsigned)get_nat_value(n);
		*mbits = sz;
		*sign = find_itype_sign(rep);
		break;
	}
	case itype_promote_tag: {
		/* Promotion types */
		unsigned si;
		it = DEREF_itype(itype_promote_arg(it));
		sz = find_itype_size(it, mbits, sign);
		si = basetype_info[ntype_sint].min_bits;
		if (sz < si) {
			sz = si;
			*mbits = basetype_info[ntype_ellipsis].max_bits;
			*sign = btype_none;
		}
		break;
	}
	case itype_arith_tag: {
		/* Arithmetic types */
		INT_TYPE is = DEREF_itype(itype_arith_arg1(it));
		unsigned ssz = find_itype_size(is, mbits, sign);
		is = DEREF_itype(itype_arith_arg2(it));
		sz = find_itype_size(is, mbits, sign);
		if (sz < ssz) {
			sz = ssz;
		}
		*mbits = basetype_info[ntype_ellipsis].max_bits;
		*sign = btype_none;
		break;
	}
	case itype_literal_tag: {
		/* Literal types */
		sz = basetype_info[ntype_sint].min_bits;
		*mbits = basetype_info[ntype_ellipsis].max_bits;
		*sign = btype_none;
		break;
	}
	case itype_token_tag: {
		/* Tokenised types */
		BASE_TYPE bt = btype_none;
		IDENTIFIER tid = DEREF_id(itype_token_tok(it));
		TOKEN tok = DEREF_tok(id_token_sort(tid));
		if (IS_tok_proc(tok)) {
			tok = DEREF_tok(tok_proc_res(tok));
		}
		if (IS_tok_type(tok)) {
			bt = DEREF_btype(tok_type_kind(tok));
			bt = find_itype_sign(bt);
		}
		sz = basetype_info[ntype_ellipsis].min_bits;
		*mbits = basetype_info[ntype_ellipsis].max_bits;
		*sign = bt;
		break;
	}
	default:
		/* Other types */
		sz = basetype_info[ntype_ellipsis].min_bits;
		*mbits = basetype_info[ntype_ellipsis].max_bits;
		*sign = btype_none;
		break;
	}
	return sz;
}


/*
    This routine is identical to find_itype_size except that it works for
    all integer, enumeration and bitfield types.
*/

unsigned
find_type_size(TYPE t, unsigned *mbits, BASE_TYPE *sign)
{
	switch (TAG_type(t)) {
	case type_integer_tag: {
		/* Integral types */
		INT_TYPE it = DEREF_itype(type_integer_rep(t));
		return find_itype_size(it, mbits, sign);
	}
	case type_enumerate_tag: {
		/* Enumeration types */
		ENUM_TYPE et = DEREF_etype(type_enumerate_defn(t));
		t = DEREF_type(etype_rep(et));
		return find_type_size(t, mbits, sign);
	}
	case type_bitfield_tag: {
		/* Bitfield types */
		INT_TYPE it = DEREF_itype(type_bitfield_defn(t));
		return find_itype_size(it, mbits, sign);
	}
	}
	*mbits = basetype_info[ntype_ellipsis].max_bits;
	*sign = btype_none;
	return 0;
}


/*
    This routine constructs an non-trivial arithmetic integral type.
    nu gives the first type (for example, 'unsigned int'), ns gives the
    second type (for example, 'signed long'), and nt gives the default
    arithmetic type (for example, 'unsigned long').
*/

static INT_TYPE
make_arith(BUILTIN_TYPE nu, BUILTIN_TYPE ns, BUILTIN_TYPE nt)
{
	INT_TYPE it;
	int c = builtin_cast(nu, ns);
	if (c <= min_builtin_cast) {
		/* u definitely fits inside s */
		TYPE s = type_builtin[ns];
		it = DEREF_itype(type_integer_rep(s));
	} else if (c <= safe_builtin_cast) {
		/* u possibly fits inside s */
		TYPE u = type_builtin[nu];
		TYPE s = type_builtin[ns];
		TYPE t = type_builtin[nt];
		LIST(TYPE)pt = NULL_list(TYPE);
		INT_TYPE ir = DEREF_itype(type_integer_rep(u));
		INT_TYPE is = DEREF_itype(type_integer_rep(s));
		CONS_type(t, pt, pt);
		CONS_type(s, pt, pt);
		pt = uniq_type_set(pt);
		MAKE_itype_arith(NULL_type, pt, ir, is, it);
		IGNORE promote_itype(it, it);
	} else {
		/* u definitely does not fit inside s */
		TYPE t = type_builtin[nt];
		it = DEREF_itype(type_integer_rep(t));
	}
	return it;
}


/*
    This routine initialises the integral and floating-point types.
*/

void
init_itypes(int init)
{
	int c;
	INT_TYPE it;
	BUILTIN_TYPE n;
	LIST(TYPE) qt;
	unsigned long i, j;
	BUILTIN_TYPE ntype_max = ntype_ulong;

	/* Initialise type tables */
	if (init) {
		for (i = 0; i < ORDER_ntype; i++) {
			for (j = 0; j < ORDER_ntype; j++) {
				all_itypes[i][j] = NULL_type;
			}
		}
	}

	/* Initialise all the types */
	for (n = ntype_none; n <= ntype_ellipsis; n++) {
		TYPE t = NULL_type;
		BUILTIN_TYPE m = n;
		BASE_TYPE rep = basetype_info[n].rep;
		switch (n) {
		case ntype_none: {
			/* Allow for inferred types */
			m = ntype_sint;
			goto default_lab;
		}
		default:
default_lab: {
		     /* Create an integral type */
		     LIST(TYPE) pt = NULL_list(TYPE);
		     MAKE_itype_basic(t, pt, rep, m, it);
		     if (init) {
			     MAKE_type_integer(cv_none, it, it, t);
			     CONS_type(t, pt, pt);
			     COPY_list(itype_cases(it), pt);
			     all_itypes[n][n] = t;
			     type_builtin[n] = t;
		     } else {
			     t = type_builtin[n];
			     COPY_itype(type_integer_rep(t), it);
			     COPY_itype(type_integer_sem(t), it);
		     }
		     break;
	     }
		case ntype_float:
		case ntype_double:
		case ntype_ldouble: {
			/* Create a floating type */
			FLOAT_TYPE ft;
			MAKE_ftype_basic(NULL_type, rep, n, ft);
			init_float(ft);
			if (init) {
				MAKE_type_floating(cv_none, ft, ft, t);
				all_itypes[n][n] = t;
				type_builtin[n] = t;
			} else {
				t = type_builtin[n];
				COPY_ftype(type_floating_rep(t), ft);
				COPY_ftype(type_floating_sem(t), ft);
			}
			break;
		}
		case ntype_void:
			if (init) {
				MAKE_type_top(cv_none, t);
				type_builtin[n] = t;
			}
			break;
		case ntype_bottom:
			if (init) {
				MAKE_type_bottom(cv_none, t);
				type_builtin[n] = t;
			}
			break;
		case ntype_ellipsis:
			if (init) {
				MAKE_type_pre(cv_none, rep, qual_none, t);
				type_builtin[n] = t;
			}
			break;
		}
	}

	/* Set up list of all integral types */
	qt = NULL_list(TYPE);
	for (n = ntype_max; n >= ntype_char; n--) {
		CONS_type(type_builtin[n], qt, qt);
	}
	all_int_types = uniq_type_set(qt);

	/* Set up list of all promoted types */
	qt = NULL_list(TYPE);
	for (n = ntype_max; n >= ntype_sint; n--) {
		CONS_type(type_builtin[n], qt, qt);
	}
	all_prom_types = uniq_type_set(qt);

	/* Set up list of all promoted types (including long long) */
	qt = NULL_list(TYPE);
	for (n = ntype_ullong; n >= ntype_sint; n--) {
		CONS_type(type_builtin[n], qt, qt);
	}
	all_llong_types = uniq_type_set(qt);

	/* Set up non-built-in types (also see init_tok) */
	if (basetype_info[ntype_bool].key) {
		base_token[ntype_bool].alt = ARITH_bool;
	} else {
		/* 'bool' is equal to 'int' for most purposes */
		const char **nms = ntype_name ; /* SCO cc gets const wrong */
		it = DEREF_itype(type_integer_rep(type_bool));
		qt = NULL_list(TYPE);
		CONS_type(type_sint, qt, qt);
		COPY_list(itype_cases(it), qt);
		base_token[ntype_bool].alt = ARITH_none;
		nms[ntype_bool] = nms[ntype_sint];
		mangle_ntype[ntype_bool][0] = MANGLE_int;
	}
	if (basetype_info[ntype_ptrdiff_t].key) {
		base_token[ntype_ptrdiff_t].alt = ARITH_ptrdiff_t;
	} else {
		/* ptrdiff_t will be either 'int' or 'long' */
		it = DEREF_itype(type_integer_rep(type_ptrdiff_t));
		qt = NULL_list(TYPE);
		CONS_type(type_slong, qt, qt);
		CONS_type(type_sint, qt, qt);
		COPY_list(itype_cases(it), qt);
		base_token[ntype_ptrdiff_t].alt = ARITH_none;
	}
	if (basetype_info[ntype_size_t].key) {
		base_token[ntype_size_t].alt = ARITH_size_t;
	} else {
		/* size_t will be either 'unsigned' or 'unsigned long' */
		it = DEREF_itype(type_integer_rep(type_size_t));
		qt = NULL_list(TYPE);
		CONS_type(type_ulong, qt, qt);
		CONS_type(type_uint, qt, qt);
		COPY_list(itype_cases(it), qt);
		base_token[ntype_size_t].alt = ARITH_none;
	}
	if (basetype_info[ntype_wchar_t].key) {
		base_token[ntype_wchar_t].alt = ARITH_wchar_t;
	} else {
		/* wchar_t can be any type */
		it = DEREF_itype(type_integer_rep(type_wchar_t));
		qt = all_int_types;
		COPY_list(itype_cases(it), qt);
		base_token[ntype_wchar_t].alt = ARITH_none;
	}

	/* Calculate all promotion types */
	for (i = 0; i < ORDER_ntype; i++) {
		TYPE t = type_builtin[i];
		if (!IS_NULL_type(t)) {
			switch (TAG_type(t)) {
			case type_integer_tag: {
				/* Calculate promotion for integral type */
				INT_TYPE ip;
				BUILTIN_TYPE m;
				TYPE p = NULL_type;
				LIST(TYPE)pt = NULL_list(TYPE);
				it = DEREF_itype(type_integer_rep(t));
				n = DEREF_ntype(itype_basic_no(it));

				/* int, unsigned etc. promote to themselves */
				if (n >= ntype_sint && n <= ntype_ullong) {
					if (do_dump && i) {
						dump_promote(it, it);
					}
					COPY_type(itype_prom(it), t);
					COPY_ntype(itype_unprom(it), n);
					break;
				}

				/* ptrdiff_t and size_t promote to themselves */
				if (n == ntype_ptrdiff_t || n == ntype_size_t) {
					if (do_dump) {
						dump_promote(it, it);
					}
					COPY_type(itype_prom(it), t);
					break;
				}

				/* Construct promotion type for wchar_t */
				if (n == ntype_wchar_t) {
					IGNORE promote_itype(it, NULL_itype);
					break;
				}

				/* Find promotion type */
				for (m = ntype_sint; m <= ntype_ulong; m++) {
					c = builtin_cast(n, m);
					if (c <= safe_builtin_cast) {
						/* Possibly fits */
						p = type_builtin[m];
						CONS_type(p, pt, pt);
					}
					if (c <= min_builtin_cast) {
						/* Definitely fits */
						break;
					}
				}
				if (LENGTH_list(pt) == 1) {
					/* Unique promotion type */
					p = DEREF_type(HEAD_list(pt));
					ip = DEREF_itype(type_integer_rep(p));
					p = make_itype(ip, it);
					DESTROY_list(pt, SIZE_type);
					if (do_dump) {
						dump_promote(it, ip);
					}
				} else {
					/* Construct promotion type */
					pt = REVERSE_list(pt);
					pt = uniq_type_set(pt);
					MAKE_itype_promote(p, pt, it, ip);
					p = make_itype(ip, it);
					COPY_type(itype_prom(ip), p);
				}
				COPY_type(itype_prom(it), p);
				break;
			}

			case type_floating_tag: {
				/* Calculate promotion for floating-point
				 * type */
				FLOAT_TYPE ft;
				ft = DEREF_ftype(type_floating_rep(t));
				n = DEREF_ntype(ftype_basic_no(ft));
				if (n == ntype_float) {
					FLOAT_TYPE fp;
					TYPE p = type_double;
					fp = DEREF_ftype(type_floating_rep(p));
					p = make_ftype(fp, ft);
					COPY_type(ftype_arg_prom(ft), p);
				} else {
					COPY_type(ftype_arg_prom(ft), t);
				}
				break;
			}
			}
		}
	}

	/* Calculate the arithmetic types */
	it = make_arith(ntype_uint, ntype_slong, ntype_ulong);
	arith_slong_uint = it;
	it = make_arith(ntype_uint, ntype_sllong, ntype_ullong);
	arith_sllong_uint = it;
	it = make_arith(ntype_ulong, ntype_sllong, ntype_ullong);
	arith_sllong_ulong = it;
	return;
}
