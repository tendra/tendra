/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>
#include <limits.h>

#include <shared/check.h>

#include <utility/config.h>
#include "c_types.h"

#include <utility/error.h>
#include <utility/catalog.h>
#include <utility/option.h>
#include <utility/ustring.h>

#include <parse/char.h>
#include <parse/literal.h>

#include <construct/basetype.h>
#include <construct/chktype.h>
#include <construct/convert.h>
#include <construct/printf.h>
#include <construct/typeid.h>

#include "id_ops.h"
#include "str_ops.h"
#include "type_ops.h"


/*
    These values are used to indicate the various flags, field widths and
    precision used to modify printf and scanf format strings.
*/

#define PRINTF_NONE		((unsigned)0x0000)
#define PRINTF_THOUSAND		((unsigned)0x0001)
#define PRINTF_LEFT		((unsigned)0x0002)
#define PRINTF_SIGN		((unsigned)0x0004)
#define PRINTF_SPACE		((unsigned)0x0008)
#define PRINTF_ALT		((unsigned)0x0010)
#define PRINTF_ZERO		((unsigned)0x0020)
#define PRINTF_WIDTH		((unsigned)0x0040)
#define PRINTF_PREC		((unsigned)0x0080)
#define PRINTF_ERROR		((unsigned)0x0100)
#define PRINTF_FLAGS		((unsigned)0x003f)
#define PRINTF_ARITH		((unsigned)0x003d)


/*
    This routine skips a number of decimal digits from the string str.
    The first character and its character type are given by c and pc.
    The routine returns the first non-digit character, assigning the
    value read (or UINT_MAX if an overflow occurs) into pn.
*/

static unsigned long
read_width(STRING str, unsigned long c, int *pc, unsigned *pn)
{
	unsigned n = 0;
	unsigned m = 0;
	int overflow = 0;
	while (*pc == CHAR_SIMPLE && (c >= char_zero && c <= char_nine)) {
		n = 10 * n + (unsigned)(c - char_zero);
		if (n < m) {
			overflow = 1;
		}
		m = n;
		c = get_string_char(str, pc);
	}
	if (overflow) {
		n = UINT_MAX;
	}
	*pn = n;
	return c;
}


/*
    In several places in a printf or scanf format string, a sequence of
    characters of the form 'n$' for a sequence of decimal digits n is
    used to indicate the nth, as opposed to the next, argument.  This
    routine checks for such sequences in the string str, returning n.
    margs gives the maximum value allowed for n, if n exceeds this value
    then it UINT_MAX is returned.  A value of 0 is returned if str does
    not have this form (note that the arguments are numbered from 1).
*/

static unsigned
read_arg_no(STRING str, unsigned margs)
{
	unsigned long tok = DEREF_ulong(str_simple_tok(str));
	int ch = CHAR_SIMPLE;
	unsigned long c = get_string_char(str, &ch);
	if (ch == CHAR_SIMPLE && (c >= char_zero && c <= char_nine)) {
		unsigned n = 0;
		c = read_width(str, c, &ch, &n);
		if (ch == CHAR_SIMPLE && c == char_dollar) {
			if (n > margs) {
				/* Argument number out of range */
				report(crt_loc, ERR_printf_arg_large(n));
				n = UINT_MAX;
			}
			if (n == 0) {
				/* Can't have argument zero */
				report(crt_loc, ERR_printf_arg_zero());
				n = 1;
			}
			return n;
		}
	}
	COPY_ulong(str_simple_tok(str), tok);
	return 0;
}


/*
    This routine combines a printf or scanf format string corresponding to
    the type n, modified by the type modifier m.  flags gives any invalid
    format flags.
*/

static BUILTIN_TYPE
check_format(string s, BUILTIN_TYPE n, BUILTIN_TYPE m, unsigned flags)
{
	switch (m) {
	case ntype_sshort:
		/* 'h' modifier */
		switch (n) {
		case ntype_sint: n = ntype_sshort; break;
		case ntype_uint: n = ntype_ushort; break;

		default:
			flags |= PRINTF_ERROR;
			break;
		}
		break;
	case ntype_slong:
		/* 'l' modifier */
		switch (n) {
		case ntype_char:  n = ntype_wchar_t; break;
		case ntype_uchar: n = ntype_none;    break;
		case ntype_sint:  n = ntype_slong;   break;
		case ntype_uint:  n = ntype_ulong;   break;
		case ntype_float: n = ntype_double;  break;

		default:
			flags |= PRINTF_ERROR;
			break;
		}
		break;
	case ntype_ldouble:
		/* 'L' modifier */
		switch (n) {
		case ntype_float:  n = ntype_ldouble; break;
		case ntype_double: n = ntype_ldouble; break;

		default:
			flags |= PRINTF_ERROR;
			break;
		}
		break;
	}

	if (flags) {
		if (flags & PRINTF_ERROR) {
			report(crt_loc, ERR_printf_invalid(s));
			s[1] = s[2];
			s[2] = 0;
		}
		if (flags & PRINTF_FLAGS) {
			character t[8];
			string r = t;
			if (flags & PRINTF_THOUSAND) {
				*(r++) = char_single_quote;
			}
			if (flags & PRINTF_LEFT) {
				*(r++) = char_minus;
			}
			if (flags & PRINTF_SIGN) {
				*(r++) = char_plus;
			}
			if (flags & PRINTF_SPACE) {
				*(r++) = char_space;
			}
			if (flags & PRINTF_ALT) {
				*(r++) = char_hash;
			}
			if (flags & PRINTF_ZERO) {
				*(r++) = char_zero;
			}
			*r = 0;
			report(crt_loc, ERR_printf_flags(t, s));
		}
		if (flags & PRINTF_WIDTH) {
			report(crt_loc, ERR_printf_width(s));
		}
		if (flags & PRINTF_PREC) {
			report(crt_loc, ERR_printf_precision(s));
		}
	}
	return n;
}


/*
    This routine sets the nth argument of the list p to be t.  The elements
    of p are in reverse order and numbered from 1.  A zero value for n is
    equivalent to 'LENGTH_list ( p ) + 1'.  The state flag is used to keep
    track of whether numbered and unnumbered arguments are mixed.
*/

static LIST(TYPE)
set_printf_arg(LIST(TYPE) p, unsigned n, TYPE t, int *state)
{
	if (n == 0) {
		/* Simple case */
		if (*state == 2) {
			report(crt_loc, ERR_printf_arg_mix());
			*state = 3;
		} else {
			*state = 1;
		}
		CONS_type(t, p, p);
	} else {
		unsigned m = UINT_MAX;
		if (*state == 1) {
			report(crt_loc, ERR_printf_arg_mix());
			*state = 3;
		} else {
			*state = 2;
		}
		if (n != m) {
			/* Valid argument number */
			TYPE s;
			LIST(TYPE) q;
			m = LENGTH_list(p);
			while (m < n) {
				/* Add extra arguments if necessary */
				CONS_type(NULL_type, p, p);
				m++;
			}
			q = p;
			while (m > n) {
				/* Scan to nth argument */
				q = TAIL_list(q);
				m--;
			}
			s = DEREF_type(HEAD_list(q));
			if (!IS_NULL_type(s) && !EQ_type(s, t)) {
				/* Check for compatibility with previous type */
				ERROR err = NULL_err;
				t = check_compatible(s, t, 1, &err, 1);
				if (!IS_NULL_err(err)) {
					err = set_severity(err, OPT_whatever, 0);
					err = concat_error(err, ERR_printf_arg_compat(n));
					report(crt_loc, err);
				}
			}
			COPY_type(HEAD_list(q), t);
		}
	}
	return p;
}


/*
    These variables give those printf and scanf argument types which are
    not built-in types or pointers to built-in types.
*/

static TYPE ptr_const_char = NULL_type;
static TYPE ptr_const_wchar_t = NULL_type;
static TYPE ptr_ptr_void = NULL_type;
static TYPE type_wint_t = NULL_type;


/*
    This routine reads a single printf argument type from the string
    str, adding it to the list p.  It is entered immediately after the
    '%' in the format string has been read.
*/

static LIST(TYPE)
add_printf_arg(STRING str, LIST(TYPE) p, unsigned margs, int *state)
{
	unsigned flag;
	character s[8];
	string r = s;
	unsigned long c;
	TYPE t = NULL_type;
	int ch = CHAR_SIMPLE;
	BUILTIN_TYPE n = ntype_none;
	unsigned flags = PRINTF_NONE;

	/* Read argument number */
	unsigned arg = read_arg_no(str, margs);

	/* Read flags */
	do {
		c = get_string_char(str, &ch);
		if (ch == CHAR_SIMPLE) {
			if (c == char_percent && flags == PRINTF_NONE &&
			    arg == 0) {
				/* Have precisely '%%' */
				return p;
			}
			switch (c) {
			case char_single_quote: flag = PRINTF_THOUSAND; break;
			case char_minus:        flag = PRINTF_LEFT;     break;
			case char_plus:         flag = PRINTF_SIGN;     break;
			case char_space:        flag = PRINTF_SPACE;    break;
			case char_hash:         flag = PRINTF_ALT;      break;
			case char_zero:         flag = PRINTF_ZERO;     break;
			default:                flag = PRINTF_NONE;     break;
			}
			flags |= flag;
		} else {
			flag = PRINTF_NONE;
		}
	} while (flag != PRINTF_NONE);

	/* Read field width */
	if (ch == CHAR_SIMPLE) {
		if (c == char_asterix) {
			unsigned arg2 = read_arg_no(str, margs);
			p = set_printf_arg(p, arg2, type_sint, state);
			c = get_string_char(str, &ch);
			flags |= PRINTF_WIDTH;
		} else if (c >= char_zero && c <= char_nine) {
			unsigned v = 0;
			c = read_width(str, c, &ch, &v);
			flags |= PRINTF_WIDTH;
		}
	}

	/* Read precision */
	if (ch == CHAR_SIMPLE && c == char_dot) {
		c = get_string_char(str, &ch);
		if (ch == CHAR_SIMPLE) {
			if (c == char_asterix) {
				unsigned arg2 = read_arg_no(str, margs);
				p = set_printf_arg(p, arg2, type_sint, state);
				c = get_string_char(str, &ch);
			} else if (c >= char_zero && c <= char_nine) {
				unsigned v = 0;
				c = read_width(str, c, &ch, &v);
			}
		}
		flags |= PRINTF_PREC;
	}

	/* Read type modifier */
	*(r++) = char_percent;
	if (ch == CHAR_SIMPLE) {
		switch (c) {
		case char_h:
			n = ntype_sshort;
			break;
		case char_l:
			n = ntype_slong;
			break;
		case char_L:
			n = ntype_ldouble;
			break;
		}
		if (n != ntype_none) {
			*(r++) = (character)c;
			c = get_string_char(str, &ch);
		}
	}

	/* Read type specifier */
	r[0] = (character)c;
	r[1] = 0;
	if (ch == CHAR_SIMPLE) {
		switch (c) {
		case char_c:
			flags &= (PRINTF_ARITH | PRINTF_PREC);
			n = check_format(s, ntype_uchar, n, flags);
			if (n == ntype_none) {
				goto wint_lab;
			}
			break;
		case char_C:
			flags &= PRINTF_ARITH;
			n = check_format(s, ntype_none, n, flags);
wint_lab:
			t = type_wint_t;
			if (IS_NULL_type(t)) {
				t = find_std_type("wint_t", 0, 0);
				if (!IS_NULL_type(t)) {
					type_wint_t = t;
				} else {
					t = type_error;
				}
			}
			break;
		case char_d:
		case char_i:
			flags &= PRINTF_ALT;
			n = check_format(s, ntype_sint, n, flags);
			break;
		case char_o:
			flags &= (PRINTF_ALT | PRINTF_THOUSAND);
			n = check_format(s, ntype_uint, n, flags);
			break;
		case char_u:
			flags &= PRINTF_ALT;
			n = check_format(s, ntype_uint, n, flags);
			break;
		case char_x:
		case char_X:
			flags &= PRINTF_THOUSAND;
			n = check_format(s, ntype_uint, n, flags);
			break;
		case char_e:
		case char_E:
			flags &= PRINTF_THOUSAND;
			n = check_format(s, ntype_double, n, flags);
			break;
		case char_f:
		case char_g:
		case char_G:
			n = check_format(s, ntype_double, n, PRINTF_NONE);
			break;
		case char_s:
			flags &= PRINTF_ARITH;
			n = check_format(s, ntype_char, n, flags);
			if (n == ntype_char) {
				t = ptr_const_char;
			} else {
				t = ptr_const_wchar_t;
			}
			n = ntype_none;
			break;
		case char_S:
			flags &= PRINTF_ARITH;
			n = check_format(s, ntype_none, n, flags);
			t = ptr_const_wchar_t;
			break;
		case char_p:
			flags &= (PRINTF_ARITH | PRINTF_PREC);
			n = check_format(s, ntype_none, n, flags);
			t = type_void_star;
			break;
		case char_n:
			n = check_format(s, ntype_sint, n, flags);
			t = ptr_type_builtin[n];
			n = ntype_none;
			break;
		default:
			report(crt_loc, ERR_printf_unknown(s));
			t = type_error;
			n = ntype_none;
			break;
		}
		if (n != ntype_none) {
			t = type_builtin[n];
		}
	} else {
		report(crt_loc, ERR_printf_unknown(s));
		t = type_error;
	}
	if (!IS_NULL_type(t)) {
		t = arg_promote_type(t, KILL_err);
		p = set_printf_arg(p, arg, t, state);
	}
	return p;
}


/*
    This routine reads a single scanf argument type from the string
    str, adding it to the list p.  It is entered immediately after the
    '%' in the format string has been read.
*/

static LIST(TYPE)
add_scanf_arg(STRING str, LIST(TYPE) p, unsigned margs, int *state)
{
	character s[8];
	string r = s;
	int ignore = 0;
	unsigned long c;
	TYPE t = NULL_type;
	int ch = CHAR_SIMPLE;
	BUILTIN_TYPE n = ntype_none;
	unsigned flags = PRINTF_NONE;

	/* Read argument number */
	unsigned arg = read_arg_no(str, margs);

	/* Check for initial '*' */
	c = get_string_char(str, &ch);
	if (ch == CHAR_SIMPLE) {
		if (c == char_percent && arg == 0) {
			/* Have precisely '%%' */
			return p;
		}
		if (c == char_asterix) {
			c = get_string_char(str, &ch);
			ignore = 1;
		}
	}

	/* Read field width */
	if (ch == CHAR_SIMPLE && (c >= char_zero && c <= char_nine)) {
		unsigned v = 0;
		c = read_width(str, c, &ch, &v);
		flags |= PRINTF_WIDTH;
	}

	/* Read type modifier */
	*(r++) = char_percent;
	if (ch == CHAR_SIMPLE) {
		switch (c) {
		case char_h:
			n = ntype_sshort;
			break;
		case char_l:
			n = ntype_slong;
			break;
		case char_L:
			n = ntype_ldouble;
			break;
		}
		if (n != ntype_none) {
			*(r++) = (character)c;
			c = get_string_char(str, &ch);
		}
	}

	/* Read type specifier */
	r[0] = (character)c;
	r[1] = 0;
	if (ch == CHAR_SIMPLE) {
		switch (c) {
		case char_c:
			n = check_format(s, ntype_char, n, PRINTF_NONE);
			break;
		case char_C:
			n = check_format(s, ntype_wchar_t, n, PRINTF_NONE);
			break;
		case char_d:
		case char_i:
			n = check_format(s, ntype_sint, n, PRINTF_NONE);
			break;
		case char_o:
		case char_u:
		case char_x:
		case char_X:
			n = check_format(s, ntype_uint, n, PRINTF_NONE);
			break;
		case char_e:
		case char_E:
		case char_f:
		case char_g:
		case char_G:
			n = check_format(s, ntype_float, n, PRINTF_NONE);
			break;
		case char_s:
			n = check_format(s, ntype_char, n, PRINTF_NONE);
			break;
		case char_open_square:
			c = get_string_char(str, &ch);
			if (ch == CHAR_SIMPLE && c == char_circum) {
				IGNORE get_string_char(str, &ch);
			}
			do {
				c = get_string_char(str, &ch);
				if (ch == CHAR_NONE) {
					report(crt_loc, ERR_printf_unterm(s));
					break;
				}
			} while (ch != CHAR_SIMPLE || c != char_close_square);
			r = ustrlit("%[...]");
			n = check_format(r, ntype_char, n, PRINTF_NONE);
			break;
		case char_S:
			n = check_format(s, ntype_wchar_t, n, PRINTF_NONE);
			break;
		case char_p:
			n = check_format(s, ntype_none, n, PRINTF_NONE);
			t = ptr_ptr_void;
			break;
		case char_n:
			if (ignore) {
				r = ustrlit("*");
				report(crt_loc, ERR_printf_flags(r, s));
			}
			n = check_format(s, ntype_sint, n, flags);
			break;
		default:
			report(crt_loc, ERR_printf_unknown(s));
			t = type_error;
			n = ntype_none;
			break;
		}
		if (n != ntype_none)t = ptr_type_builtin[n];
	} else {
		report(crt_loc, ERR_printf_unknown(s));
		t = type_error;
	}
	if (!IS_NULL_type(t) && !ignore) {
		p = set_printf_arg(p, arg, t, state);
	}
	return p;
}


/*
    This routine finds the list of arguments expected by a printf-like
    or scanf-like function with format string fmt.  margs gives the
    number argument number which may be specified using '%n$', and pf is
    the value returned by is_printf_type.
*/

LIST(TYPE)
find_printf_args(STRING str, unsigned margs, int pf)
{
	int state = 0;
	unsigned long c;
	int ch = CHAR_SIMPLE;
	LIST(TYPE) p = NULL_list(TYPE);
	ulong tok = DEREF_ulong(str_simple_tok(str));
	COPY_ulong(str_simple_tok(str), 0);
	while (c = get_string_char(str, &ch), ch != CHAR_NONE) {
		if (c == char_percent && ch == CHAR_SIMPLE) {
			if (pf & 1) {
				p = add_printf_arg(str, p, margs, &state);
			} else {
				p = add_scanf_arg(str, p, margs, &state);
			}
		}
	}
	if (state >= 2) {
		int reported = 0;
		LIST(TYPE) q = p;
		while (!IS_NULL_list(q)) {
			TYPE t = DEREF_type(HEAD_list(q));
			if (IS_NULL_type(t)) {
				/* No format string for given argument */
				if (!reported) {
					unsigned n = LENGTH_list(q);
					report(crt_loc, ERR_printf_arg_none(n));
					reported = 1;
				}
				COPY_type(HEAD_list(q), type_error);
			} else {
				reported = 0;
			}
			q = TAIL_list(q);
		}
	}
	COPY_ulong(str_simple_tok(str), tok);
	p = REVERSE_list(p);
	return p;
}


/*
    Functions like printf and scanf are indicated by an argument with one
    of the following types, which equal 'const char *' or 'const wchar_t *'.
*/

TYPE type_printf = NULL_type;
TYPE type_scanf = NULL_type;
TYPE type_wprintf = NULL_type;
TYPE type_wscanf = NULL_type;


/*
    This routine checks whether the type t is derived from one of the
    printf or scanf string types above.  It returns 1 for type_printf,
    2 for type_scanf, 3 for type_wprintf and 4 for type_wscanf.
*/

int
is_printf_type(TYPE t)
{
	IDENTIFIER tid = DEREF_id(type_name(t));
	if (!IS_NULL_id(tid)) {
		TYPE s = DEREF_type(id_class_name_etc_defn(tid));
		if (IS_type_ptr(s)) {
			if (EQ_type(s, type_printf)) {
				return 1;
			}
			if (EQ_type(s, type_scanf)) {
				return 2;
			}
			if (EQ_type(s, type_wprintf)) {
				return 3;
			}
			if (EQ_type(s, type_wscanf)) {
				return 4;
			}
		}
	}
	return 0;
}


/*
    This routine initialises the printf and scanf strings.
*/

void
init_printf(void)
{
	TYPE c = qualify_type(type_char, cv_const, 0);
	TYPE w = qualify_type(type_wchar_t, cv_const, 0);
	MAKE_type_ptr(cv_none, c, type_printf);
	MAKE_type_ptr(cv_none, c, type_scanf);
	MAKE_type_ptr(cv_none, w, type_wprintf);
	MAKE_type_ptr(cv_none, w, type_wscanf);
	MAKE_type_ptr(cv_none, c, ptr_const_char);
	MAKE_type_ptr(cv_none, w, ptr_const_wchar_t);
	MAKE_type_ptr(cv_none, type_void_star, ptr_ptr_void);
	return;
}
