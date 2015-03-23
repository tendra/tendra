/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>

#include <shared/check.h>

#include <utility/config.h>
#include "c_types.h"

#include <utility/error.h>
#include <utility/catalog.h>
#include <utility/option.h>
#include <utility/ustring.h>
#include <utility/xalloc.h>

#include <syntax/syntax.h>

#include <parse/charset.h>
#include <parse/char.h>
#include <parse/constant.h>
#include <parse/hash.h>
#include <parse/lex.h>
#include <parse/literal.h>
#include <parse/preproc.h>

#include <construct/basetype.h>
#include <construct/cast.h>
#include <construct/chktype.h>
#include <construct/convert.h>
#include <construct/exception.h>
#include <construct/expression.h>
#include <construct/inttype.h>
#include <construct/token.h>

#include <output/dump.h>
#include <output/tok.h>

#include "exp_ops.h"
#include "flt_ops.h"
#include "id_ops.h"
#include "itype_ops.h"
#include "nat_ops.h"
#include "str_ops.h"
#include "type_ops.h"


/*
    Execution character set mapping. Possibly this could be combined
    into the to/from_ascii_tab[] tables, but I'm keeping it seperate
    for the moment.

    This is indexed by execution character set value, and each element
    is the corresponding ASCII value.
*/

char map[256] = { 1 };


/*
    These macros are used in the tables of digits and escape sequences
    to indicate special values.
*/

#define NONE			0xff
#define OCTE			0xfe
#define HEXE			0xfd
#define UNI4			0xfc
#define UNI8			0xfb


/*
    This table gives the mapping of characters to digits.  The default
    table assumes the ASCII character set, for other codesets it needs
    to be rewritten.  The valid digits are 0-9, A-Z (which evaluate to
    10-35) and a-z (which evaluate to 10-35).  Invalid digits are
    indicated by NONE.
*/

unsigned char digit_values[NO_CHAR + 1] = {
#define CHAR_DATA(A, B, C, D)	(B),
#include <parse/char.h>
#undef CHAR_DATA
	NONE		/* dummy */
};


/*
    This table gives the mapping of characters to escape sequences.  The
    default table assumes the ASCII character set, for other codesets it
    needs to be rewritten.  The valid escape sequences are \', \", \?,
    \\, \a, \b, \f, \n, \r, \t and \v.  Octal escape sequences are
    indicated by OCTE, hexadecimal escape sequences by HEXE, universal
    character names by UNI4 or UNI8, and illegal escape sequences by
    NONE.
*/

unsigned char escape_sequences[NO_CHAR + 1] = {
#define CHAR_DATA(A, B, C, D)	(C),
#include <parse/char.h>
#undef CHAR_DATA
	NONE		/* dummy */
};


/*
    This routine sets the character escape value for the character
    literal expression a to be the character literal b, or an illegal
    escape if b is the null expression.
*/

void
set_escape(EXP a, EXP b)
{
	int c = get_char_value(a);
	int e = NONE;
	if (!IS_NULL_exp(b)) {
		e = get_char_value(b);
		if (e == char_illegal) {
			e = NONE;
		}
	}
	if (c >= 0 && c < NO_CHAR) {
		escape_sequences[c] = (unsigned char)e;
	}
	return;
}


/*
    This routine scans the string s for valid digits for the given base.
    It returns a pointer to the first character which is not a valid
    digit.
*/

static string
check_digits(string s, unsigned base)
{
	unsigned b;
	character c;
	while (c = *s, c != 0) {
		if (is_extended(c)) {
			break;
		}
		b = (unsigned)digit_values[c];;
		if (b >= base) {
			break;
		}
		s++;
	}
	return s;
}


/*
    This routine evaluates the string of digits starting with s and
    ending with t using the given base (which will be at most 16).  It
    is assumed that all of these digits are in the correct range.
*/

static NAT
eval_digits(string s, string t, unsigned base)
{
	NAT n;
	int m = 0;
	string r = s;
	unsigned long v = 0;
	unsigned long b = (unsigned long)base;
	while (r != t && m < 8) {
		/* Evaluate first few digits */
		unsigned long d = (unsigned long)digit_values[*r];
		v = b * v + d;
		m++;
		r++;
	}
	n = make_nat_value(v);
	while (r != t) {
		/* Evaluate further digits */
		unsigned d = (unsigned)digit_values[*r];
		n = make_nat_literal(n, base, d);
		r++;
	}
	return n;
}


/*
    This routine is the same as eval_digits except that it assumes that
    the result fits inside an unsigned long, and reports an error
    otherwise.
*/

static unsigned long
eval_char_digits(string s, string t, unsigned base)
{
	string r;
	int overflow = 0;
	unsigned long n = 0;
	unsigned long b = (unsigned long)base;
	for (r = s; r != t; r++) {
		unsigned long m = n;
		n = b * n + (unsigned long)digit_values[*r];
		if (n < m) {
			overflow = 1;
		}
	}
	if (overflow) {
		report(crt_loc, ERR_lex_ccon_large());
	}
	return n;
}


/*
    This routine evaluates the sequence of decimal digits s as a line
    number in a #line, or similar, preprocessing directive.  Any errors
    arising are indicated using err.  This is a bit pattern consisting
    of 2 if s is not a simple string of decimal digits, and 1 if its
    value exceeds 32767.
*/

unsigned long
eval_line_digits(string s, unsigned *err)
{
	string r;
	unsigned e = 0;
	unsigned long n = 0;
	string t = check_digits(s, (unsigned)10);
	if (*t) {
		e = 2;
	}
	for (r = s; r != t; r++) {
		n = 10 * n + (unsigned long)digit_values[*r];
		if (n > 0x7fff) {
			e |= 1;
		}
	}
	*err = e;
	return n;
}


/*
    This variable gives the hash table used in shared string literals.
*/

static STRING *string_hash_table = NULL;
#define HASH_STRING_SIZE	((unsigned long)256)


/*
    The type of a simple character literal is char in C++, but int in C.
    The variable type_char_lit is used to hold the appropriate result
    type.  Other string and character literals have fixed types, however
    for convenience variables are used to identify them.
*/

static TYPE type_char_lit;
static TYPE type_mchar_lit;
static TYPE type_wchar_lit;
static TYPE type_string_lit;
static TYPE type_wstring_lit;
CV_SPEC cv_string = cv_none;


/*
    This routine sets the type of a character literal to be t.  t must be
    an integral type.  Note that only the representation type is set to t,
    the semantic type is always char.
*/

void
set_char_lit(TYPE t)
{
	if (IS_type_integer(t)) {
		INT_TYPE r = DEREF_itype(type_integer_rep(t));
		INT_TYPE s = DEREF_itype(type_integer_rep(type_char));
		type_char_lit = make_itype(r, s);
	} else {
		report(preproc_loc, ERR_pragma_char_lit(t));
	}
	return;
}


/*
    The type LITERAL_INFO is used to represent an item in an integer
    literal type specification.  The table int_lit_spec holds the
    specifications for the various combinations of base and suffix.
*/

typedef struct lit_info_tag {
	int tag;
	TYPE type;
	NAT bound;
	IDENTIFIER tok;
	int tok_no;
	int opt;
	struct lit_info_tag *next;
} LITERAL_INFO;

static LITERAL_INFO *int_lit_spec[BASE_NO][SUFFIX_NO] = {
	{ NULL, NULL, NULL, NULL, NULL, NULL },
	{ NULL, NULL, NULL, NULL, NULL, NULL },
	{ NULL, NULL, NULL, NULL, NULL, NULL }
};

static LITERAL_INFO *crt_int_lit = NULL;
static LITERAL_INFO **ptr_int_lit = NULL;


/*
    This table gives the possible types and built-in tokens for the
    various base and suffix combinations.
*/

static struct {
	unsigned char type[6];
	int tok;
	LIST(TYPE)cases;
} int_lit_tok[BASE_NO][SUFFIX_NO] = {
	{
		{ { 2, 0, 2, 2, 1, 1 }, TOK_lit_int, NULL_list(TYPE)      },
		{ { 0, 2, 0, 2, 0, 1 }, TOK_lit_unsigned, NULL_list(TYPE) },
		{ { 0, 0, 2, 2, 1, 1 }, TOK_lit_long, NULL_list(TYPE)     },
		{ { 0, 0, 0, 2, 0, 1 }, TOK_lit_ulong, NULL_list(TYPE)    },
		{ { 0, 0, 0, 0, 2, 2 }, TOK_lit_llong, NULL_list(TYPE)    },
		{ { 0, 0, 0, 0, 0, 2 }, TOK_lit_ullong, NULL_list(TYPE)   }
	     },
	{
		{ { 2, 2, 2, 2, 1, 1 }, TOK_lit_hex, NULL_list(TYPE)      },
		{ { 0, 2, 0, 2, 0, 1 }, TOK_lit_unsigned, NULL_list(TYPE) },
		{ { 0, 0, 2, 2, 1, 1 }, TOK_lit_long, NULL_list(TYPE)     },
		{ { 0, 0, 0, 2, 0, 1 }, TOK_lit_ulong, NULL_list(TYPE)    },
		{ { 0, 0, 0, 0, 2, 2 }, TOK_lit_llong, NULL_list(TYPE)    },
		{ { 0, 0, 0, 0, 0, 2 }, TOK_lit_ullong, NULL_list(TYPE)   }
	     },
	{
		{ { 2, 2, 2, 2, 1, 1 }, TOK_lit_hex, NULL_list(TYPE)      },
		{ { 0, 2, 0, 2, 0, 1 }, TOK_lit_unsigned, NULL_list(TYPE) },
		{ { 0, 0, 2, 2, 1, 1 }, TOK_lit_long, NULL_list(TYPE)     },
		{ { 0, 0, 0, 2, 0, 1 }, TOK_lit_ulong, NULL_list(TYPE)    },
		{ { 0, 0, 0, 0, 2, 2 }, TOK_lit_llong, NULL_list(TYPE)    },
		{ { 0, 0, 0, 0, 0, 2 }, TOK_lit_ullong, NULL_list(TYPE)   }
	}
};


/*
    This routine initialises the string and character literal types and
    the table int_lit_info.  The initial values for the table are given
    by the following lists of types:

	decimal:	( int, long, unsigned long ),
	octal/hex:	( int, unsigned, long, unsigned long ),
	U suffix:	( unsigned, unsigned long ),
	L suffix:	( long, unsigned long ),
	UL suffix:	( unsigned long ),
	LL suffix:	( long long, unsigned long long ),
	ULL suffix:	( unsigned long long ).

    Each integer literal is checked against each type in the list
    indicated by the form of the literal.  If it fits into a type then
    that is the type of the literal.  If it does not fit into any type
    then an error is raised.  If whether it fits into a particular type
    is target dependent then a literal integer type, giving the literal
    value and a list of possible types, is constructed to express the
    result type.

    The string and character types are:

	character:		char,
	multi-character:	int,
	wide character:		wchar_t,
	string:			const char [n],
	wide string:		const wchar_t [n].

    Variants are that characters have type int in C and that string
    literals are not const in pre-ISO C++ and C.
*/

void
init_literal(void)
{
	int b, s;
	BUILTIN_TYPE n;
	OPTION opt = option(OPT_int_overflow);
	assert(!IS_NULL_type(type_char));

	/* String and character literal types */
	type_mchar_lit = type_sint;
	type_wchar_lit = type_wchar_t;
	type_string_lit = type_char;
	type_wstring_lit = type_wchar_t;
#if LANGUAGE_CPP
	set_char_lit(type_char);
	set_string_qual(cv_const);
#else
	set_char_lit(type_sint);
	set_string_qual(cv_none);
#endif

	/* Set up type lists */
	for (b = 0; b < BASE_NO; b++) {
		for (s = 0; s < SUFFIX_NO; s++) {
			LIST(TYPE)p = NULL_list(TYPE);
			begin_literal(b, s);
			for (n = 0; n < 6; n++) {
				if (int_lit_tok[b][s].type[n] == 2) {
					TYPE t = type_builtin[ntype_sint + n];
					add_range_literal(NULL_exp, 1);
					add_type_literal(t);
					CONS_type(t, p, p);
				}
			}
			add_range_literal(NULL_exp, 0);
			add_token_literal(NULL_id, (unsigned)opt);
			p = REVERSE_list(p);
			int_lit_tok[b][s].cases = uniq_type_set(p);
		}
	}

	/* Set up string hash table */
	if (string_hash_table == NULL) {
		unsigned long i;
		STRING *q = xmalloc_nof(STRING, HASH_STRING_SIZE);
		for (i = 0; i < HASH_STRING_SIZE; i++) {
			q[i] = NULL_str;
		}
		string_hash_table = q;
	}
}


/* TODO: this can be folded into init_literal() when it has fatal error reporting */
int
init_literal_map(const char *path)
{
	FILE *f;

	f = fopen(path, "r");
	if (f == NULL) {
		perror(path);
		return -1;
	}

	/* TODO: seed */
	if (-1 == charset_load(map, f, 210881)) {
		/* TODO: tdfc2 error reporting */
		perror("charset_load");
		return -1;
	}

	fclose(f);

	return 0;
}


/*
    This routine sets the string and wide string literal types to be
    cv-qualified.
*/

void
set_string_qual(CV_SPEC cv)
{
	type_string_lit = qualify_type(type_string_lit, cv, 0);
	type_wstring_lit = qualify_type(type_wstring_lit, cv, 0);
	cv_string = cv;
	return;
}


/*
    This routine is called to begin the specification of the integer
    literals of the given base and suffix.
*/

void
begin_literal(int base, int suff)
{
	LITERAL_INFO **p = &(int_lit_spec[base][suff]);
	*p = NULL;
	ptr_int_lit = p;
	crt_int_lit = NULL;
	return;
}


/*
    This routine is used to specify a bound in the current literal
    specification.  If n is 0 then the bound matches all values, if it
    is 1 then the bound matches all the values in the following type,
    and if it is 2 then the bound matches all values less than or equal
    to the integer literal expression e.
*/

void
add_range_literal(EXP e, int n)
{
	LITERAL_INFO *p = xmalloc_one(LITERAL_INFO);
	p->tag = n;
	if (!IS_NULL_exp(e) && IS_exp_int_lit(e)) {
		p->bound = DEREF_nat(exp_int_lit_nat(e));
	} else {
		p->bound = small_nat[0];
	}
	p->type = NULL_type;
	p->tok = NULL_id;
	p->tok_no = -1;
	p->opt = OPT_none;
	p->next = NULL;
	*ptr_int_lit = p;
	crt_int_lit = p;
	ptr_int_lit = & (p->next);
	return;
}


/*
    This routine specifies the type t for all values under the current
    bound in the current literal specification.
*/

void
add_type_literal(TYPE t)
{
	NAT n;
	LITERAL_INFO *p = crt_int_lit;
	if (IS_type_integer(t)) {
		if (!is_arg_promote(t)) {
			/* Type should promote to itself */
			report(preproc_loc, ERR_pragma_lit_type(t));
			t = promote_type(t);
		}
	} else {
		/* Type should be integral */
		if (!IS_type_error(t)) {
			report(preproc_loc, ERR_pragma_lit_type(t));
		}
		t = type_ulong;
	}
	p->type = qualify_type(t, cv_none, 0);
	n = p->bound;
	if (p->tag == 2) {
		if (check_nat_range(t, n)!= 0) {
			/* Given bound should fit into type */
			report(preproc_loc, ERR_pragma_lit_range(n, t));
			n = max_type_value(t, 0);
		}
	} else {
		n = max_type_value(t, 0);
	}
	p->bound = n;
	return;
}


/*
    This routine specifies that the token id should be used to calculate
    the type for all values under the current bound in the current
    literal specification.  An error with severity sev is reported.
*/

void
add_token_literal(IDENTIFIER id, unsigned sev)
{
	int n = -1;
	LITERAL_INFO *p = crt_int_lit;
	if (!IS_NULL_id(id)) {
		id = resolve_token(id, "ZZ", 0);
		if (!IS_NULL_id(id)) {
			n = builtin_token(id);
		}
	}
	if (p->tag == 1) {
		report(preproc_loc, ERR_pragma_lit_question());
		p->tag = 3;
	}
	p->tok = id;
	p->tok_no = n;
	switch (sev) {
	case OPTION_ON:
		p->opt = OPT_error;
		break;
	case OPTION_WARN:
		p->opt = OPT_warning;
		break;
	default:
		p->opt = OPT_none;
		break;
	}
	return;
}


/*
    This routine finds the type of the integer constant lit specified
    with base base and suffix suff.  num gives the text used to specify
    the constant for the purposes of error reporting.  fit is set to
    true if lit definitely fits into the result.
*/

TYPE
find_literal_type(NAT lit, int base, int suff, string num, int *fit)
{
	TYPE t;
	int tok;
	INT_TYPE it;
	int big = 0;
	int have_tok = 0;
	int opt = OPT_error;
	NAT n = small_nat[0];
	IDENTIFIER tid = NULL_id;
	LIST(TYPE)qt = NULL_list(TYPE);
	LITERAL_INFO *pt = int_lit_spec[base][suff];

	/* Deal with calculated literals */
	switch (TAG_nat(lit)) {
	case nat_neg_tag:
		lit = DEREF_nat(nat_neg_arg(lit));
		t = find_literal_type(lit, base, suff, num, fit);
		return t;
	case nat_token_tag:
		t = type_sint;
		*fit = 1;
		return t;
	case nat_calc_tag: {
		EXP e = DEREF_exp(nat_calc_value(lit));
		t = DEREF_type(exp_type(e));
		*fit = 1;
		return t;
	}
	}

	/* Deal with simple literals */
	while (pt != NULL) {
		int ch = 4;
		TYPE s = pt->type;
		switch (pt->tag) {
		case 0: {
			TYPE r = s;
			if (IS_NULL_type(r)) {
				r = type_ulong;
			}
			ch = check_nat_range(r, lit);
			if (ch == 0) {
				*fit = 1;
			}
			if (ch > 4) {
				big = ch;
			}
			if (big) {
				n = max_type_value(NULL_type, 0);
			}
			ch = big;
			break;
		}
		case 1:
			n = pt->bound;
			ch = check_nat_range(s, lit);
			if (ch == 0) {
				*fit = 1;
			}
			break;
		case 2:
			n = pt->bound;
			if (compare_nat(n, lit) >= 0) {
				if (!IS_NULL_type(s))*fit = 1;
				ch = 0;
			}
			break;
		}

		if (ch == 0) {
			/* lit definitely fits into bound */
			if (!IS_NULL_type(s) && IS_NULL_list(qt)) {
				/* No previous fit */
				return s;
			}
		}
		if (ch <= 2) {
			/* lit may fit into bound */
			if (!IS_NULL_type(s)) {
				if (have_tok == 0) {
					INT_TYPE is =
					    DEREF_itype(type_integer_rep(s));
					LIST(TYPE)st =
					    DEREF_list(itype_cases(is));
					qt = union_type_set(qt, st);
					if (ch == 0) {
						have_tok = 1;
					}
				}
			} else {
				if (have_tok == 0 && !IS_NULL_id(pt->tok)) {
					DESTROY_list(qt, SIZE_type);
					tok = int_lit_tok[base][suff].tok;
					if (pt->tok_no == tok) {
						qt = int_lit_tok[base][suff].cases;
					} else if (suff < SUFFIX_LL) {
						qt = all_prom_types;
					} else {
						qt = all_llong_types;
					}
					have_tok = 2;
				}
				break;
			}
		}
		if (ch > 4) {
			big = ch;
		}
		pt = pt->next;
	}

	/* Tokenised result */
	if (have_tok != 2) {
		/* Find list of possible types */
		if (IS_NULL_list(qt)) {
			qt = int_lit_tok[base][suff].cases;
		} else {
			qt = REVERSE_list(qt);
			qt = uniq_type_set(qt);
		}
	}
	if (pt) {
		/* Get token information from table */
		tid = pt->tok;
		opt = pt->opt;
	}
	if (num && !(*fit)) {
		/* Report error if necessary */
		ERROR err = ERR_lex_icon_large(num, n);
		err = set_severity(err, opt, 0);
		if (!IS_NULL_err(err)) {
			report(crt_loc, err);
		}
	}
	if (LENGTH_list(qt) == 1) {
		/* Only one possible case */
		t = DEREF_type(HEAD_list(qt));
		DESTROY_list(qt, SIZE_type);
		return t;
	}
	tok = int_lit_tok[base][suff].tok;
	MAKE_itype_literal(NULL_type, qt, lit, tok, base, suff, tid, it);
	t = promote_itype(it, it);
	return t;
}


/*
    This routine analyses the integer or floating literal given by the
    string str, constructing the corresponding expression.  The location
    given by ptok is assigned with lex_integer_Hexp or lex_floating_Hexp
    depending on the form of the literal.  Note that str can be an area
    of read-only memory for integer literals, but not for floating
    literals.
*/

EXP
make_literal_exp(string str, int *ptok, int force)
{
	EXP e;
	string r;
	int err = 0;
	int flt = 0;
	string s = str;
	unsigned base = 10;
	string dot_posn = NULL;
	string exp_posn = NULL;
	int form = BASE_DECIMAL;

	/* Check small literals */
	character c1 = s[0];
	character c2 = 0;
	if (c1) {
		c2 = s[1];
	}
	if (c2 == 0 && (c1 >= char_zero && c1 <= char_nine)) {
		unsigned etag = exp_int_lit_tag;
		int n = (int)digit_values[c1];
		NAT lit = small_nat[n];
		if (IS_NULL_nat(lit)) {
			lit = make_small_nat(n);
		}
		if (n == 0) {
			etag = exp_null_tag;
		}
		MAKE_exp_int_lit(type_sint, lit, etag, e);
		*ptok = lex_integer_Hexp;
		return e;
	}

	if (c1 == char_zero && (c2 == char_x || c2 == char_X)) {
		/* Hexadecimal integer */
		base = 16;
		form = BASE_HEXADECIMAL;
		r = s + 2;
		s = check_digits(r, base);
		if (s == r) {
			err = 1;
		}
	} else {
		if (c1 == char_dot) {
			/* Fractional component of floating literal */
			dot_posn = s;
			r = s + 1;
			s = check_digits(r, base);
			if (s == r) {
				err = 1;
			}
			flt = 1;
		} else {
			/* Sequence of decimal digits */
			r = s;
			s = check_digits(r, base);
			if (s == r) {
				if (c1 == char_plus || c1 == char_minus) {
					/* Extension to handle signs */
					e = make_literal_exp(str + 1, ptok,
							     force);
					if (c1 == char_minus) {
						e = make_uminus_exp(lex_minus,
								    e);
					}
					return e;
				}
				err = 1;
			}
			if (s[0] == char_dot) {
				/* Fractional component of floating literal */
				dot_posn = s;
				s = check_digits(s + 1, base);
				flt = 1;
			}
		}
		exp_posn = s;
		c2 = s[0];
		if (c2 == char_e || c2 == char_E) {
			/* Exponent component of floating literal */
			c2 = s[1];
			if (c2 == char_plus || c2 == char_minus) {
				s++;
			}
			r = s + 1;
			s = check_digits(r, base);
			if (s == r) {
				err = 1;
			}
			flt = 1;
		}
		if (c1 == char_zero && !flt) {
			/* Octal integer */
			base = 8;
			form = BASE_OCTAL;
			r = check_digits(str, base);
			if (r != s) {
				/* Digits contain 8 or 9 */
				report(crt_loc, ERR_lex_icon_octal(str));
			}
		}
	}

	if (flt) {
		/* Floating literals */
		int zero;
		NAT expon;
		character ep;
		string frac_part;
		string int_part = str;
		string suff_posn = s;
		unsigned trail_zero = 0;
		FLOAT lit = NULL_flt;
		TYPE t = type_double;

		/* Check float suffix */
		c1 = s[0];
		if (c1 == char_f || c1 == char_F) {
			/* Suffix F */
			t = type_float;
			s++;
			c1 = s[0];
		} else if (c1 == char_l || c1 == char_L) {
			/* Suffix L */
			t = type_ldouble;
			s++;
			c1 = s[0];
		}

		/* Check for end of number */
		if (c1 || err) {
			report(crt_loc, ERR_lex_literal_bad(str));
		}

		/* Find number components (involves writing to s)  */
		while (int_part[0] == char_zero) {
			/* Remove initial zeros */
			int_part++;
		}
		if (dot_posn) {
			dot_posn[0] = 0;
			if (int_part == dot_posn) {
				int_part = small_number[0];
			}
			frac_part = dot_posn + 1;
			if (frac_part == exp_posn) {
				frac_part = small_number[0];
			} else {
				/* Remove trailing zeros */
				string frac_zero = exp_posn - 1;
				while (frac_zero[0] == char_zero) {
					frac_zero[0] = 0;
					frac_zero--;
					trail_zero++;
				}
				if (frac_zero == dot_posn) {
					frac_part = small_number[0];
				}
			}
		} else {
			if (int_part == exp_posn) {
				int_part = small_number[0];
			}
			frac_part = small_number[0];
		}
		ep = exp_posn[0];
		exp_posn[0] = 0;
		if (ep == char_e || ep == char_E) {
			/* Evaluate exponent */
			r = exp_posn + 1;
			c2 = r[0];
			if (c2 == char_minus || c2 == char_plus) {
				r++;
			}
			expon = eval_digits(r, suff_posn, base);
			if (c2 == char_minus) {
				expon = negate_nat(expon);
			}
			zero = is_zero_nat(expon);
		} else {
			expon = small_nat[0];
			zero = 1;
		}
		if (zero && ustreq(frac_part, small_number[0])) {
			int i;
			for (i = 0; i < SMALL_FLT_SIZE; i++) {
				if (ustreq(int_part, small_number[i])) {
					lit = get_float(t, i);
					break;
				}
			}
		}
		if (IS_NULL_flt(lit)) {
			int_part = xustrcpy(int_part);
			frac_part = xustrcpy(frac_part);
		}
		if (trail_zero) {
			/* Restore trailing zeros */
			r = exp_posn - 1;
			do {
				r[0] = char_zero;
				r--;
				trail_zero--;
			} while (trail_zero);
		}
		if (dot_posn) {
			dot_posn[0] = char_dot;
		}
		exp_posn[0] = ep;

		/* Construct result - type is as per suffix */
		if (IS_NULL_flt(lit)) {
			MAKE_flt_simple(int_part, frac_part, expon, lit);
		}
		MAKE_exp_float_lit(t, lit, e);
		*ptok = lex_floating_Hexp;

	} else {
		/* Integer literals */
		TYPE t;
		NAT lit;
		int ls = 0;
		int us = 0;
		int fit = 0;

		/* Find integer value */
		r = str;
		if (form == BASE_HEXADECIMAL) {
			r += 2;
		}
		lit = eval_digits(r, s, base);

		/* Check integer suffix */
		c1 = s[0];
		if (c1 == char_u || c1 == char_U) {
			us = 1;
			s++;
			c1 = s[0];
		}
		if (c1 == char_l || c1 == char_L) {
			ls = 1;
			if (s[1] == c1 && basetype_info[ntype_sllong].key) {
				report(crt_loc, ERR_lex_icon_llong(str));
				ls = 2;
				s++;
			}
			s++;
			c1 = s[0];
		} else {
			/* Map 'int' to 'long' in '#if' expressions */
			if (in_hash_if_exp) {
				ls = 1;
			}
		}
		if (us == 0 && (c1 == char_u || c1 == char_U)) {
			us = 1;
			s++;
			c1 = s[0];
		}

		/* Check for end of number */
		if (c1 || err) {
			report(crt_loc, ERR_lex_literal_bad(str));
		}

		/* Find literal type */
		if (force) {
			t = type_ulong;
			fit = 1;
		} else {
			int suff = SUFFIX(us, ls);
			t = find_literal_type(lit, form, suff, str, &fit);
		}
		MAKE_exp_int_lit(t, lit, exp_int_lit_tag, e);
		if (!fit) {
			/* Force result to be a calculated value */
			MAKE_exp_cast(t, CONV_INT_INT, e, e);
			MAKE_nat_calc(e, lit);
			MAKE_exp_int_lit(t, lit, exp_int_lit_tag, e);
		}
		*ptok = lex_integer_Hexp;
	}
	return e;
}


/*
    This routine checks whether the floating point literal f is zero.
*/

int
is_zero_float(FLOAT f)
{
	string s;
	character c;
	s = DEREF_string(flt_simple_int_part(f));
	while (c = *(s++), c != 0) {
		if (c != char_zero) {
			return 0;
		}
	}
	s = DEREF_string(flt_simple_frac_part(f));
	while (c = *(s++), c != 0) {
		if (c != char_zero) {
			return 0;
		}
	}
	return 1;
}


/*
    This routine checks whether the floating point literals f and g are
    equal.  Note that this is equality of representation rather than
    equality of the underlying numbers.
*/

int
eq_float_lit(FLOAT f, FLOAT g)
{
	NAT ef, eg;
	ulong nf, ng;
	string af, ag;
	string bf, bg;
	if (EQ_flt(f, g)) {
		return 1;
	}
	DECONS_flt_simple(nf, af, bf, ef, f);
	DECONS_flt_simple(ng, ag, bg, eg, g);
	if (!ustreq(af, ag)) {
		return 0;
	}
	if (!ustreq(bf, bg)) {
		return 0;
	}
	if (compare_nat(ef, eg)!= 0) {
		return 0;
	}
	if (nf == LINK_NONE) {
		COPY_ulong(flt_tok(f), ng);
	}
	if (ng == LINK_NONE) {
		COPY_ulong(flt_tok(g), nf);
	}
	return 1;
}


/*
    This variable gives the default rounding mode used for converting
    floating point expressions to integers.
*/

RMODE crt_round_mode = rmode_to_zero;


/*
    This routine rounds the floating point literal f to an integer
    literal by the rounding mode corresponding to mode.  The null integer
    literal is returned to indicate a target dependent literal.  The
    range of values in which the result is target independent is actually
    rather small - it is given by FLT_DIG.
*/

NAT
round_float_lit(FLOAT f, RMODE mode)
{
	NAT res;
	unsigned base = 10;
	unsigned long i, j, n;
	unsigned long res_len;
	unsigned long pre_len;
	unsigned long exp_val;
	character result[100];

	/* Decompose simple literal */
	string int_part = DEREF_string(flt_simple_int_part(f));
	string frac_part = DEREF_string(flt_simple_frac_part(f));
	NAT expon = DEREF_nat(flt_simple_exponent(f));

	/* Find component lengths */
	unsigned long int_len = (unsigned long)ustrlen(int_part);
	unsigned long frac_len = (unsigned long)ustrlen(frac_part);

	/* Allow for initial zeros */
	while (int_part[0] == char_zero) {
		int_part++;
		int_len--;
	}

	/* Allow for exponent */
	if (IS_nat_neg(expon)) {
		expon = DEREF_nat(nat_neg_arg(expon));
		exp_val = get_nat_value(expon);
		if (exp_val > int_len) {
			res_len = 0;
			pre_len = exp_val - int_len;
		} else {
			res_len = int_len - exp_val;
			pre_len = 0;
		}
	} else {
		exp_val = get_nat_value(expon);
		res_len = int_len + exp_val;
		pre_len = 0;
	}

	/* Allow for initial zeros in fractional part */
	if (int_part[0] == 0) {
		while (frac_part[0] == char_zero) {
			frac_part++;
			frac_len--;
			if (res_len == 0) {
				pre_len++;
			} else {
				res_len--;
			}
		}
		if (frac_part[0] == 0) {
			/* Zero floating literal */
			res = small_nat[0];
			return res;
		}
	}

	/* Extreme values are target dependent */
	if (pre_len > 6) {
		return NULL_nat;
	}
	if (res_len > 6) {
		return NULL_nat;
	}
	if (exp_val == EXTENDED_MAX) {
		return NULL_nat;
	}

	/* Construct integer string */
	j = 0;
	n = res_len;
	for (i = 0; i < pre_len; i++) {
		if (j < n) {
			result[j] = char_zero;
			j++;
		}
	}
	for (i = 0; i < int_len; i++) {
		if (j < n) {
			result[j] = int_part[i];
			j++;
		}
	}
	for (i = 0; i < frac_len; i++) {
		if (j < n) {
			result[j] = frac_part[i];
			j++;
		}
	}
	for (; j < n; j++) {
		result[j] = char_zero;
	}
	result[n] = 0;

	/* Calculate the result */
	res = eval_digits(result, result + res_len, base);
	UNUSED(mode);
	return res;
}


/*
    This routine evaluates the unicode character with prefix c, consisting
    of n hex digits, given by ps.  ps is advanced to the position following
    the hex digits.
*/

unsigned long
eval_unicode(int c, unsigned n, int *pc, string *ps, ERROR *err)
{
	string r = *ps;
	unsigned long u;
	unsigned base = 16;
	string s = check_digits(r, base);
	unsigned m = (unsigned)(s - r);
	if (m < n) {
		add_error(err, ERR_lex_charset_len(c, n));
	} else {
		s = r + n;
	}
	*ps = s;
	u = eval_char_digits(r, s, base);
	add_error(err, ERR_lex_charset_replace(u));
	if (u < 0x20 || (u >= 0x7f && u <= 0x9f) || is_legal_char(u)) {
		add_error(err, ERR_lex_charset_bad(u));
		*pc = CHAR_SIMPLE;
	} else {
		if (u <= (unsigned long)0xffff) {
			*pc = CHAR_UNI4;
		}
	}
	return u;
}


/*
    This routine returns the multi-byte character pointed to by the
    string s.  It assigns the character type to pc.
*/

unsigned long
get_multi_char(string s, int *pc)
{
	int i;
	unsigned long n = 0;
	for (i = MULTI_WIDTH - 1; i >= 1; i--) {
		n = (n << 8) + (unsigned long)s[i];
	}
	*pc = (int)s[0];
	return n;
}


/*
    This routine adds the multi-byte character n of type ch to the
    string s.  A multi-byte character is represented by 5 characters.
    The first is a key describing how the character was described (a
    simple character, a hex or octal escape sequence, a unicode
    character etc.).  The next four characters give the character value.
*/

void
add_multi_char(string s, unsigned long n, int ch)
{
	int i;
	s[0] = (character)ch;
	for (i = 1; i < MULTI_WIDTH; i++) {
		s[i] = (character)(n & 0xff);
		n >>= 8;
	}
	if (n) {
		report(crt_loc, ERR_lex_ccon_large());
	}
	return;
}


/*
    This routine creates a multi-byte string of length n in s from the
    string t of kind k.
*/

static void
make_multi_string(string s, string t, unsigned long n, unsigned k)
{
	if (k & STRING_MULTI) {
		n *= MULTI_WIDTH;
		xumemcpy(s, t, n);
	} else {
		unsigned long i;
		for (i = 0; i < n; i++) {
			add_multi_char(s, (unsigned long)*t, CHAR_SIMPLE);
			s += MULTI_WIDTH;
			t++;
		}
	}
	return;
}


/*
    This routine reads a multibyte character from the string s (which
    ends at se).  The value (as a wide character) is assigned to pc with
    the new value of s being returned.  Note that this routine is not
    required in, for example, check_digits because the representation
    of a simple single byte character as a multibyte character comprises
    that single byte.
*/

static string
get_multibyte(string s, string se, unsigned long *pc)
{
	wchar_t c;
	int n = mbtowc(&c, s, (size_t)(se - s));
	if (n > 0) {
		/* Valid multibyte character */
		*pc = (unsigned long)c;
		s += n;
	} else if (n == 0) {
		/* Null character */
		*pc = 0;
		s++;
	} else {
		/* Invalid multibyte character */
		report(crt_loc, ERR_lex_ccon_multibyte());
		*pc = (unsigned long)*(s++);
	}
	return s;
}


/*
    This routine analyses the string or character literal given by the
    string s (which ends at se).  Only characters in the range [0, 0xff]
    are assumed to be valid. Note that this is the routine which should
    do the mapping from the source character set to the execution
    character set (translation phase 5), however this is deferred until
    the string output routines.
*/

STRING
new_string_lit(string s, string se, int lex)
{
	STRING res;
	STRING prev;
	int multi = 0;
	int overflow = 0;
	unsigned long len = 0;
	unsigned kind = STRING_NONE;
	int multibyte = allow_multibyte;
	size_t sz = (se - s) + 1;
	string str = xustr(sz);

	/* Find string type */
	switch (lex) {
	case lex_char_Hlit:
	case lex_char_Hexp:
		kind = STRING_CHAR;
		break;
	case lex_wchar_Hlit:
	case lex_wchar_Hexp:
		kind = (STRING_WIDE | STRING_CHAR);
		break;
	case lex_string_Hlit:
	case lex_string_Hexp:
		kind = STRING_NONE;
		break;
	case lex_wstring_Hlit:
	case lex_wstring_Hexp:
		kind = STRING_WIDE;
		break;
	}
	if (do_string) {
		dump_string_lit(s, se, kind);
	}

	/* Scan string replacing escape sequences */
	while (s != se) {
		unsigned long c;
		int ch = CHAR_SIMPLE;
		if (multibyte) {
			s = get_multibyte(s, se, &c);
		} else {
			c = (unsigned long)*(s++);
		}
		if (c == char_backslash) {
			if (s != se) {
				/* Unterminated string literals already
				 * reported */
				character e = NONE;
				if (multibyte) {
					s = get_multibyte(s, se, &c);
				} else {
					c = (unsigned long)*(s++);
				}
				if (c < NO_CHAR) {
					e = escape_sequences[c];
				}
				switch (e) {

				case OCTE: {
					/* Octal escape sequences */
					unsigned base = 8;
					string r = s - 1;
					s = check_digits(r, base);
					if (s > r + 3) {
						s = r + 3;
					}
					c = eval_char_digits(r, s, base);
					ch = CHAR_OCTAL;
					break;
				}

				case HEXE: {
					/* Hexadecimal escape sequences */
					unsigned base = 16;
					string r = s;
					s = check_digits(r, base);
					if (s == r) {
						int i = (int)c;
						report(crt_loc,
						       ERR_lex_ccon_hex(i));
					} else {
						c = eval_char_digits(r, s,
								     base);
					}
					ch = CHAR_HEX;
					break;
				}

				case UNI4: {
					/* Short unicode escape sequences */
					if (allow_unicodes) {
						string r = s;
						unsigned d = 4;
						ERROR err = NULL_err;
						c = eval_unicode(char_u, d, &ch,
								 &r, &err);
						if (!IS_NULL_err(err)) {
							report(crt_loc, err);
						}
						ch = CHAR_UNI4;
						s = r;
						break;
					}
					goto illegal_lab;
				}

				case UNI8: {
					/* Long unicode escape sequences */
					if (allow_unicodes) {
						string r = s;
						unsigned d = 8;
						ERROR err = NULL_err;
						c = eval_unicode(char_U, d, &ch,
								 &r, &err);
						if (!IS_NULL_err(err)) {
							report(crt_loc, err);
						}
						ch = CHAR_UNI8;
						s = r;
						break;
					}
					goto illegal_lab;
				}

				case NONE:
illegal_lab: {
					/* Illegal escape sequences */
		     			int i = (int)c;
					report(crt_loc, ERR_lex_ccon_escape(i));
					break;
	     }

				default:
					/* Simple escape sequences */
					c = (unsigned long)e;
					break;
				}
			}
		}
		if ((ch != CHAR_SIMPLE || c >= 256) && !multi) {
			/* Convert to multi-character format */
			string a;
			sz *= MULTI_WIDTH;
			a = xustr(sz);
			make_multi_string(a, str, len, kind);
			if (len) {
				len *= MULTI_WIDTH;
				if (len == 0) {
					overflow = 1;
				}
			}
			if (c >= 256) {
				/* Mark fat strings */
				if (!(kind & STRING_WIDE)) {
					if (ch == CHAR_UNI4 ||
					    ch == CHAR_UNI8) {
						/* EMPTY */
					} else {
						report(crt_loc,
						       ERR_lex_ccon_large());
					}
				}
				kind |= STRING_FAT;
			}
			kind |= STRING_MULTI;
			multi = 1;
			str = a;
		}

		if (map[0] == '\0') {
			c = map[c];
		}

		if (multi) {
			add_multi_char(str + len, c, ch);
			len += MULTI_WIDTH;
		} else {
			str[len++] = (character)c;
		}
		if (len == 0) {
			overflow = 1;
		}
	}
	if (multi) {
		add_multi_char(str + len, (unsigned long)0, CHAR_OCTAL);
		len /= MULTI_WIDTH;
	} else {
		str[len] = 0;
	}
	if (overflow) {
		len = ULONG_MAX;
	}
	if (!check_value(OPT_VAL_string_length, len)) {
		len = option_value(OPT_VAL_string_length);
		if (multi) {
			unsigned long n = MULTI_WIDTH * len;
			add_multi_char(str + n, (unsigned long)0, CHAR_OCTAL);
		} else {
			str[len] = 0;
		}
	}
	MAKE_str_simple(len, str, kind, res);
	prev = share_string_lit(res);
	if (!EQ_str(prev, res)) {
		/* Share string literals */
		unsigned long v;
		DESTROY_str_simple(destroy, res, len, str, kind, v, res);
		xufree(str, sz);
		UNUSED(res);
		UNUSED(len);
		UNUSED(kind);
		UNUSED(v);
		res = prev;
	}
	return res;
}


/*
    This routine checks whether the string literals s and t are equal.
*/

int
eq_string_lit(STRING s, STRING t)
{
	string as, at;
	unsigned ks, kt;
	unsigned long ns, nt;
	if (EQ_str(s, t)) {
		return 1;
	}
	ks = DEREF_unsigned(str_simple_kind(s));
	kt = DEREF_unsigned(str_simple_kind(t));
	ns = DEREF_ulong(str_simple_len(s));
	nt = DEREF_ulong(str_simple_len(t));
	if (ks == kt && ns == nt) {
		as = DEREF_string(str_simple_text(s));
		at = DEREF_string(str_simple_text(t));
		if (as == at) {
			return 1;
		}
		if (ks & STRING_MULTI) {
			ns *= MULTI_WIDTH;
		}
		if (xumemcmp(as, at, ns) == 0) {
			return 1;
		}
	}
	return 0;
}


/*
    This routine concatenates the string literals s and t.
*/

STRING
concat_string_lit(STRING s, STRING t)
{
	string c;
	STRING res;
	STRING prev;
	unsigned kc;
	size_t sz;
	unsigned long nc;
	string a = DEREF_string(str_simple_text(s));
	string b = DEREF_string(str_simple_text(t));
	unsigned ka = DEREF_unsigned(str_simple_kind(s));
	unsigned kb = DEREF_unsigned(str_simple_kind(t));
	unsigned long na = DEREF_ulong(str_simple_len(s));
	unsigned long nb = DEREF_ulong(str_simple_len(t));

	/* Form the result literal */
	if (na == 0) {
		return t;
	}
	if (nb == 0) {
		return s;
	}
	nc = na + nb;
	if (nc < na || nc < nb) {
		nc = ULONG_MAX;
	}
	if (!check_value(OPT_VAL_string_length, nc)) {
		nc = option_value(OPT_VAL_string_length);
		nb = nc - na;
	}
	kc = (ka | kb);
	if (kc & STRING_MULTI) {
		/* Multi-byte strings */
		unsigned long sa = MULTI_WIDTH * na;
		unsigned long sc = MULTI_WIDTH * nc;
		sz = sc + MULTI_WIDTH;
		c = xustr(sz);
		make_multi_string(c, a, na, ka);
		make_multi_string(c + sa, b, nb, kb);
		add_multi_char(c + sc, (unsigned long)0, CHAR_OCTAL);
	} else {
		/* Simple strings */
		sz = nc + 1;
		c = xustr(sz);
		xumemcpy(c, a, na);
		xumemcpy(c + na, b, nb);
		c[nc] = 0;
	}
	MAKE_str_simple(nc, c, kc, res);
	prev = share_string_lit(res);
	if (!EQ_str(prev, res)) {
		/* Share string literals */
		unsigned long v;
		DESTROY_str_simple(destroy, res, nc, c, kc, v, res);
		xufree(c, sz);
		UNUSED(res);
		UNUSED(nc);
		UNUSED(kc);
		UNUSED(v);
		res = prev;
	}
	return res;
}


/*
    This routine is used to implement shared string literals.  It returns
    the canonical copy of s (i.e. the first string equal to s for which
    the routine was called).
*/

STRING
share_string_lit(STRING s)
{
	string a = DEREF_string(str_simple_text(s));
	unsigned long h = (hash(a)% HASH_STRING_SIZE);
	STRING p = string_hash_table[h];
	STRING t = p;
	while (!IS_NULL_str(t)) {
		if (eq_string_lit(t, s)) {
			return t;
		}
		t = DEREF_str(str_next(t));
	}
	COPY_str(str_next(s), p);
	string_hash_table[h] = s;
	return s;
}


/*
    This routine returns the next character from the string s, using
    the tok field as a counter.  The character type is assigned to pc,
    including CHAR_NONE to indicate the end of the string.
*/

unsigned long
get_string_char(STRING s, int *pc)
{
	unsigned long c;
	unsigned long i = DEREF_ulong(str_simple_tok(s));
	unsigned long n = DEREF_ulong(str_simple_len(s));
	if (i < n) {
		string text = DEREF_string(str_simple_text(s));
		unsigned kind = DEREF_unsigned(str_simple_kind(s));
		if (kind & STRING_MULTI) {
			c = get_multi_char(text + MULTI_WIDTH * i, pc);
		} else {
			c = (unsigned long)text[i];
			*pc = CHAR_SIMPLE;
		}
	} else {
		c = 0;
		*pc = CHAR_NONE;
	}
	COPY_ulong(str_simple_tok(s), i + 1);
	return c;
}


/*
    This routine returns the character value corresponding to the character
    literal expression e.
*/

int
get_char_value(EXP e)
{
	int c = char_illegal;
	if (!IS_NULL_exp(e)) {
		if (IS_exp_int_lit(e)) {
			NAT n = DEREF_nat(exp_int_lit_nat(e));
			if (IS_nat_calc(n)) {
				e = DEREF_exp(nat_calc_value(n));
			}
		}
		if (IS_exp_cast(e)) {
			e = DEREF_exp(exp_cast_arg(e));
			if (IS_exp_int_lit(e)) {
				NAT n = DEREF_nat(exp_int_lit_nat(e));
				if (IS_nat_calc(n)) {
					e = DEREF_exp(nat_calc_value(n));
				}
			}
		}
		if (IS_exp_char_lit(e)) {
			STRING s = DEREF_str(exp_char_lit_str(e));
			unsigned kind = DEREF_unsigned(str_simple_kind(s));
			if (!(kind & STRING_MULTI)) {
				unsigned long len =
				    DEREF_ulong(str_simple_len(s));
				if (len == 1) {
					string t =
					    DEREF_string(str_simple_text(s));
					c = (int)*t;
				}
			}
		}
	}
	return c;
}


/*
    This routine evaluates the character literal str by mapping it to
    its ASCII representation.  The value is stored in the tok field
    (the fact that LINK_NONE equals EXTENDED_MAX is convenient, but not
    essential).
*/

NAT
eval_char_lit(STRING str)
{
	NAT n;
	unsigned long v = DEREF_ulong(str_simple_tok(str));
	if (v == LINK_NONE) {
		unsigned long i;
		string s = DEREF_string(str_simple_text(str));
		unsigned long len = DEREF_ulong(str_simple_len(str));
		unsigned kind = DEREF_unsigned(str_simple_kind(str));
		if (kind & STRING_MULTI) {
			NAT b = make_small_nat(256);
			n = small_nat[0];
			for (i = 0; i < len; i++) {
				NAT d;
				int ch = CHAR_SIMPLE;
				unsigned long c = get_multi_char(s, &ch);
				if (ch == CHAR_SIMPLE) {
					c = to_ascii(c, &ch);
				}
				d = make_nat_value(c);
				n = binary_nat_op(exp_mult_tag, n, b);
				n = binary_nat_op(exp_plus_tag, n, d);
				s += MULTI_WIDTH;
			}
		} else {
			n = small_nat[0];
			for (i = 0; i < len; i++) {
				int ch = CHAR_SIMPLE;
				unsigned long c = (unsigned long)*s;
				c = to_ascii(c, &ch);
				n = make_nat_literal(n, (unsigned)256,
						     (unsigned)c);
				s++;
			}
		}
		v = get_nat_value(n);
		if (v != EXTENDED_MAX) {
			/* Store calculated value */
			COPY_ulong(str_simple_tok(str), v);
		}
	} else {
		/* Use stored value */
		n = make_nat_value(v);
	}
	return n;
}


/*
    In the case where a character literal type doesn't fit into its type
    then this routine gives a type in which the literal value can be
    constructed and then converted into its underlying type.
*/

TYPE
find_char_type(NAT n)
{
	TYPE t;
	int fit = 0;
	string str = NULL_string;
	t = find_literal_type(n, BASE_OCTAL, SUFFIX_NONE, str, &fit);
	return t;
}


/*
    This routine turns a string or character literal into an expression.
    Note that the type of a normal character literal varies between C
    (where it is a char cast to an int) and C++ (where it stays as a
    char), and also that a string, or wide string, literal is an lvalue
    of array type.
*/

EXP
make_string_exp(STRING s)
{
	EXP e;
	string text = DEREF_string(str_simple_text(s));
	unsigned long len = DEREF_ulong(str_simple_len(s));
	unsigned kind = DEREF_unsigned(str_simple_kind(s));

	if (kind & STRING_CHAR) {
		int fits = 0;
		int digit = -1;
		TYPE t0, t1, t2;
		NAT n = NULL_nat;
		ERROR err = NULL_err;
		if (kind & STRING_WIDE) {
			t0 = type_wchar_lit;
			t1 = t0;
			t2 = t0;
		} else if (len <= 1) {
			t0 = type_char;
			t1 = t0;
			t2 = type_char_lit;
		} else {
			report(crt_loc, ERR_lex_ccon_multi(s));
			t0 = type_mchar_lit;
			t1 = t0;
			t2 = t0;
		}
		if (len == 0) {
			fits = 1;
			n = small_nat[0];
			COPY_ulong(str_simple_tok(s), 0);
		} else if (len == 1) {
			if (kind & STRING_MULTI) {
				if (!(kind & STRING_FAT)) {
					/* Simple octal or hex escape
					 * sequence */
					unsigned long v =
					    DEREF_ulong(str_simple_tok(s));
					if (v == LINK_NONE) {
						int ch = CHAR_SIMPLE;
						v = get_multi_char(text, &ch);
						if (ch == CHAR_OCTAL ||
						    ch == CHAR_HEX) {
							if (v < 128)fits = 1;
							n = make_nat_value(v);
							COPY_ulong(str_simple_tok(s), v);
						}
					} else {
						if (v < 128)fits = 1;
						n = make_nat_value(v);
					}
				}
			} else {
				/* Single character */
				character c = text[0];
				if (in_hash_if_exp) {
					/* Evaluate character value
					 * immediately */
					unsigned long v =
					    DEREF_ulong(str_simple_tok(s));
					if (v == LINK_NONE) {
						int ch = CHAR_SIMPLE;
						v = (unsigned long)c;
						v = to_ascii(v, &ch);
						COPY_ulong(str_simple_tok(s),
							   v);
					}
					if (v < 128) {
						fits = 1;
					}
					n = make_nat_value(v);
				} else {
					if (c >= char_zero && c <= char_nine) {
						/* Allow for digits */
						digit = (int)(c - char_zero);
					}
				}
			}
		}
		if (IS_NULL_nat(n)) {
			/* Make character literal expression */
			MAKE_exp_char_lit(t0, s, digit, e);
			MAKE_nat_calc(e, n);
		} else {
			if (!fits && check_nat_range(t0, n)!= 0) {
				/* Value doesn't fit into t0 */
				t0 = find_char_type(n);
			}
		}
		MAKE_exp_int_lit(t0, n, exp_char_lit_tag, e);
		if (!EQ_type(t0, t1)) {
			/* Convert from t0 to t1 */
			e = make_cast_nat(t1, e, &err, CAST_STATIC);
		}
		if (!EQ_type(t1, t2)) {
			/* Convert from t1 to t2 */
			e = make_cast_nat(t2, e, &err, CAST_IMPLICIT);
		}
		if (!IS_NULL_err(err)) {
			report(crt_loc, err);
		}
	} else {
		/* String literals */
		TYPE t;
		NAT n = make_nat_value(len + 1);
		if (kind & STRING_WIDE) {
			t = type_wstring_lit;
		} else {
			t = type_string_lit;
		}
		MAKE_type_array(cv_lvalue, t, n, t);
		MAKE_exp_string_lit(t, s, e);
	}
	return e;
}


/*
    This routine creates a boolean literal expression given by the boolean
    value b (which should be one of the values BOOL_FALSE and BOOL_TRUE
    defined in literal.h).
*/

EXP
make_bool_exp(unsigned b, unsigned tag)
{
	EXP e;
	NAT n = small_nat[b];
	MAKE_exp_int_lit(type_bool, n, tag, e);
	return e;
}


/*
    This routine is the reverse of the one above.  It returns the boolean
    value (BOOL_FALSE, BOOL_TRUE or BOOL_UNKNOWN) corresponding to the
    expression e.
*/

unsigned
test_bool_exp(EXP e)
{
	NAT n = DEREF_nat(exp_int_lit_nat(e));
	if (IS_nat_small(n)) {
		unsigned b = DEREF_unsigned(nat_small_value(n));
		if (b == BOOL_FALSE) {
			return BOOL_FALSE;
		}
		if (b == BOOL_TRUE) {
			return BOOL_TRUE;
		}
	}
	return BOOL_UNKNOWN;
}
