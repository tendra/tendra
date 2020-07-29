/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include <utility/config.h>
#include <utility/version.h>
#include "c_types.h"
#include <utility/option.h>

#include <parse/preproc.h>

#include <utility/error.h>
#include <utility/catalog.h>
#include <utility/buffer.h>
#include <utility/print.h>
#include <utility/ustring.h>
#include <utility/xalloc.h>

#include <syntax/syntax.h>

#include <parse/char.h>
#include <parse/constant.h>
#include <parse/hash.h>
#include <parse/lex.h>
#include <parse/literal.h>

#include <construct/allocate.h>
#include <construct/basetype.h>
#include <construct/class.h>
#include <construct/convert.h>
#include <construct/declare.h>
#include <construct/exception.h>
#include <construct/function.h>
#include <construct/identifier.h>
#include <construct/initialise.h>
#include <construct/namespace.h>
#include <construct/link.h>

#include <output/tdf.h>
#include <output/mangle.h>
#include <output/unmangle.h>

#include "ctype_ops.h"
#include "exp_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "member_ops.h"
#include "nat_ops.h"
#include "nspace_ops.h"
#include "tok_ops.h"
#include "type_ops.h"


/*
    The unmangling routines are only included in the C++ producer; the
    C producer uses a dummy identity mapping.
*/

#if LANGUAGE_CPP


/*
    The following forward declarations are required in the name unmangling
    routines.
*/

static NAT unmangle_nat(string *);
static TYPE unmangle_type(string *, CV_SPEC, BASE_TYPE, int);
static IDENTIFIER unmangle_nspace(string *, NAMESPACE, int);
static LIST(TOKEN)unmangle_token_args(string *);
static TOKEN find_token_arg(string *);


/*
    This variable is a dummy used as a return type when none is given in
    a mangled form.  Its printed form is empty.
*/

static TYPE dummy_ret_type = NULL_type;


/*
    The following variables are used to hold certain information about the
    identifier being unmangled.
*/

static IDENTIFIER crt_unmangle_class = NULL_id;
static LIST(TOKEN)crt_unmangle_args = NULL_list(TOKEN);


/*
    This routine unmangles an operator name from the string pointed to
    by ps.
*/

static int
unmangle_op(string *ps)
{
	string s = *ps;
	int t = lex_unknown;
	character c = *(s++);
	switch (c) {
	case 'a': {
		c = *(s++);
		switch (c) {
		case 'a': {
			c = *(s++);
			if (c == 'd') {
				t = lex_and_Heq_H1;
			} else {
				s--;
				t = lex_logical_Hand_H1;
			}
			break;
		}
		case 'b': {
			t = lex_abs;
			break;
		}
		case 'd': {
			c = *(s++);
			if (c == 'v') {
				t = lex_div_Heq;
			} else {
				s--;
				t = lex_and_H1;
			}
			break;
		}
		case 'e': {
			c = *(s++);
			if (c == 'r') {
				t = lex_xor_Heq_H1;
			}
			break;
		}
		case 'l': {
			c = *(s++);
			if (c == 's') {
				t = lex_lshift_Heq;
			}
			break;
		}
		case 'm': {
			c = *(s++);
			switch (c) {
			case 'd': t = lex_rem_Heq;   break;
			case 'i': t = lex_minus_Heq; break;
			case 'l': t = lex_star_Heq;  break;
			}
			break;
		}
		case 'o': {
			c = *(s++);
			if (c == 'r') {
				t = lex_or_Heq_H1;
			}
			break;
		}
		case 'p': {
			c = *(s++);
			if (c == 'l') {
				t = lex_plus_Heq;
			}
			break;
		}
		case 'r': {
			c = *(s++);
			if (c == 's') {
				t = lex_rshift_Heq;
			}
			break;
		}
		case 's': {
			t = lex_assign;
			break;
		}
		}
		break;
	}
	case 'c': {
		c = *(s++);
		switch (c) {
		case 'c': t = lex_colon_Hcolon; break;
		case 'l': t = lex_func_Hop;     break;
		case 'm': t = lex_comma;        break;
		case 'n': t = lex_cond_Hop;     break;
		case 'o': t = lex_compl_H1;     break;
		case 's': t = lex_colon;        break;
		case 't': t = lex_type_Hname;   break;
		}
		break;
	}
	case 'd': {
		c = *(s++);
		switch (c) {
		case 'f': t = lex_dot;              break;
		case 'l': t = lex_delete;           break;
		case 'm': t = lex_dot_Hstar;        break;
		case 't': t = lex_destructor_Hname; break;
		case 'v': t = lex_div;              break;
		}
		break;
	}
	case 'e': {
		c = *(s++);
		switch (c) {
		case 'q': t = lex_eq;     break;
		case 'r': t = lex_xor_H1; break;
		}
		break;
	}
	case 'f': {
		t = lex_float;
		break;
	}
	case 'g': {
		c = *(s++);
		switch (c) {
		case 'e': t = lex_greater_Heq; break;
		case 't': t = lex_greater;     break;
		}
		break;
	}
	case 'l': {
		c = *(s++);
		switch (c) {
		case 'e': t = lex_less_Heq; break;
		case 's': t = lex_lshift;   break;
		case 't': t = lex_less;     break;
		}
		break;
	}
	case 'm': {
		c = *(s++);
		switch (c) {
		case 'd': t = lex_rem;          break;
		case 'i': t = lex_minus;        break;
		case 'l': t = lex_star;         break;
		case 'm': t = lex_minus_Hminus; break;
		case 'n': t = lex_min;          break;
		case 'x': t = lex_max;          break;
		}
		break;
	}
	case 'n': {
		c = *(s++);
		switch (c) {
		case 'e': t = lex_not_Heq_H1; break;
		case 't': t = lex_not_H1;     break;
		case 'w': t = lex_new;        break;
		}
		break;
	}
	case 'o': {
		c = *(s++);
		switch (c) {
		case 'o': t = lex_logical_Hor_H1; break;
		case 'p': t = lex_operator;       break;
		case 'r': t = lex_or_H1;          break;
		}
		break;
	}
	case 'p': {
		c = *(s++);
		switch (c) {
		case 'l': t = lex_plus;       break;
		case 'p': t = lex_plus_Hplus; break;
		}
		break;
	}
	case 'r': {
		c = *(s++);
		switch (c) {
		case 'f': t = lex_arrow;       break;
		case 'm': t = lex_arrow_Hstar; break;
		case 's': t = lex_rshift;      break;
		}
		break;
	}
	case 's': {
		c = *(s++);
		if (c == 'z') {
			t = lex_sizeof;
		}
		break;
	}
	case 't': {
		c = *(s++);
		switch (c) {
		case 'b': t = lex_vtable; break;
		case 'd': t = lex_typeid; break;

		case 'i': {
			if (s[0] == '_' && s[1] == '_') {
				t = lex_typeof;
				s += 2;
			}
			break;
		}
		}
		break;
	}
	case 'v': {
		c = *(s++);
		switch (c) {
		case 'c': t = lex_array_Hop;     break;
		case 'd': t = lex_delete_Harray; break;
		case 'n': t = lex_new_Harray;    break;
		case '_': t = lex_static;        break;

		case 't': {
			if (s[0] == '_' && s[1] == '_') {
				t = lex_virtual;
				s += 2;
			}
			break;
		}
		}
		break;
	}
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9': {
		t = lex_auto;
		break;
	}
	}
	if (t != lex_unknown) {
		*ps = s;
	}
	return t;
}


/*
    This routine unmangles a series of digits from the string pointed
    to by ps.  If e is true then the digits should be terminated by an
    underscore.
*/

static unsigned
unmangle_no(string *ps, int e)
{
	character c;
	unsigned n = 0;
	string s = *ps;
	while (c = *(s++), (c >= char_zero && c <= char_nine)) {
		unsigned d = (unsigned)(c - char_zero);
		n = 10 * n + d;
	}
	if (c != MANGLE_sep || e == 0) {
		s--;
	}
	*ps = s;
	return n;
}


/*
    This routine unmangles a small number from the string pointed to
    by ps.  This consists either of a single digit or a series of digits
    delimited by underscores.
*/

static unsigned
unmangle_digit(string *ps)
{
	unsigned n;
	string s = *ps;
	character c = *(s++);
	if (c >= char_zero && c <= char_nine) {
		n = (unsigned)(c - char_zero);
	} else if (c == MANGLE_sep) {
		n = unmangle_no(&s, 1);
	} else {
		n = 0;
		s--;
	}
	*ps = s;
	return n;
}


/*
    This routine unmangles an expression of type t from the string pointed
    to by ps.
*/

static EXP
unmangle_exp(string *ps, TYPE t)
{
	EXP e = NULL_exp;
	string s = *ps;
	character c = *s;
	if ((c >= char_zero && c <= char_nine) || c == MANGLE_neg) {
		/* Read an integer constant */
		NAT n = unmangle_nat(&s);
		if (!IS_NULL_nat(n)) {
			MAKE_exp_int_lit(t, n, exp_int_lit_tag, e);
		}

	} else if (c == MANGLE_op) {
		int op;
		s++;
		op = unmangle_op(&s);
		if (op == lex_float) {
			/* Floating point literals */
			string u = xustrcpy(s);
			string v = u;
			while (c = *(s++), c != 0) {
				if (c == MANGLE_sep) {
					*v = 0;
					s++;
					break;
				}
				if ((c >= char_zero && c <= char_nine) ||
				    c == 'e') {
					/* EMPTY */
				} else if (c == 'd') {
					*v = '.';
				} else if (c == MANGLE_neg) {
					*v = '-';
				} else {
					*v = 0;
					break;
				}
				v++;
			}
			s--;
			e = make_literal_exp(u, &op, 0);
		} else {
			int n = 0;
			c = *s;
			if (c >= char_zero && c <= char_nine) {
				n = (int)(c - char_zero);
				s++;
			}
			if (op == lex_sizeof) {
				TYPE r = unmangle_type(&s, cv_none, btype_none,
						       1);
				e = make_sizeof_exp(r, NULL_exp, 0, op);
			} else {
				LIST(EXP)p = NULL_list(EXP);
				while (n) {
					EXP a = unmangle_exp(&s, t);
					CONS_exp(a, p, p);
					n--;
				}
				p = REVERSE_list(p);
				MAKE_exp_opn(t, op, p, e);
			}
		}

	} else if (c == MANGLE_sep) {
		IDENTIFIER id;
		s++;
		id = unmangle_nspace(&s, global_namespace, 1);
		if (!IS_NULL_id(id)) {
			MAKE_exp_identifier(t, id, qual_nested, e);
		}

	} else if (c == MANGLE_templ_param) {
		/* Template parameter expressions */
		TOKEN tok;
		s++;
		tok = find_token_arg(&s);
		if (!IS_NULL_tok(tok) && IS_tok_exp(tok)) {
			e = DEREF_exp(tok_exp_value(tok));
		}
	}
	*ps = s;
	return e;
}


/*
    This routine unmangles an integer constant from the string pointed to
    by ps.
*/

static NAT
unmangle_nat(string *ps)
{
	NAT n = NULL_nat;
	string s = *ps;
	character c = *s;
	if (c >= char_zero && c <= char_nine) {
		/* Read a sequence of digits */
		s++;
		do {
			unsigned d = (unsigned)(c - char_zero);
			n = make_nat_literal(n,(unsigned)10, d);
		} while (c = *(s++), (c >= char_zero && c <= char_nine));
		if (c != MANGLE_sep) {
			s--;
		}
	} else if (c == MANGLE_sep) {
		/* Empty sequence of digits */
		s++;
	} else if (c == MANGLE_neg) {
		/* Negate an integer */
		s++;
		n = unmangle_nat(&s);
		n = negate_nat(n);
	} else {
		/* Read an expression */
		EXP e = unmangle_exp(&s, type_sint);
		if (!IS_NULL_exp(e)) {
			MAKE_nat_calc(e, n);
		}
	}
	*ps = s;
	return n;
}


/*
    This routine unmangles a namespace qualifier from the string pointed
    to by ps.  Note that all such namespaces are declared as classes even
    if they are not in reality.
*/

static IDENTIFIER
unmangle_nspace(string *ps, NAMESPACE ns, int var)
{
	string s = *ps;
	character c = *s;
	IDENTIFIER id = NULL_id;
	if (c >= char_zero && c <= char_nine) {
		unsigned n = unmangle_no(&s, 0);
		if (n) {
			HASHID nm;
			int ext = 0;
			TYPE t = NULL_type;
			string p = xmalloc(n + 1);
			string q = p;
			while (n) {
				c = *s;
				if (c) {
					if (c == MANGLE_sep && s[1] ==
					    MANGLE_sep) {
						/* Allow for unicode
						 * characters */
						if (s[2] == MANGLE_unicode4) {
							*(q++) = char_backslash;
							c = char_u;
							ext = 1;
							s += 2;
						} else if (s[2] ==
							   MANGLE_unicode8) {
							*(q++) = char_backslash;
							c = char_U;
							ext = 1;
							s += 2;
						}
					}
					*(q++) = c;
					s++;
				} else {
					*(q++) = char_question;
				}
				n--;
			}
			*q = 0;
			nm = lookup_name(p, hash(p), ext, lex_identifier);
			if (var) {
				t = type_sint;
				MAKE_id_variable(nm, dspec_extern, ns, crt_loc,
						 t, id);
			} else {
				id = make_class(ns, nm, btype_lang,
						dspec_extern, t, t);
			}
		}

	} else if (c == MANGLE_qual) {
		unsigned n;
		s++;
		n = unmangle_digit(&s);
		while (n) {
			NAMESPACE pns;
			id = unmangle_nspace(&s, ns, 0);
			pns = find_namespace(id);
			if (!IS_NULL_nspace(pns)) {
				ns = pns;
			}
			n--;
		}

	} else if (c == MANGLE_template) {
		s++;
		id = unmangle_nspace(&s, ns, 0);
		if (!IS_NULL_id(id)) {
			LIST(TOKEN)args = unmangle_token_args(&s);
			TYPE t = make_dummy_class(id, args, btype_lang);
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
			id = DEREF_id(ctype_name(ct));
		}

	} else if (c == MANGLE_templ_param) {
		TOKEN tok;
		s++;
		tok = find_token_arg(&s);
		if (!IS_NULL_tok(tok) && IS_tok_type(tok)) {
			TYPE t = DEREF_type(tok_type_value(tok));
			if (!IS_NULL_type(t) && IS_type_compound(t)) {
				CLASS_TYPE ct =
				    DEREF_ctype(type_compound_defn(t));
				id = DEREF_id(ctype_name(ct));
			}
		}
	}
	*ps = s;
	return id;
}


/*
    This routine unmangles a token or template argument from the string
    pointed to by ps.
*/

static TOKEN
unmangle_token_arg(string *ps)
{
	TOKEN tok = NULL_tok;
	string s = *ps;
	character c = *s;
	switch (c) {
	case MANGLE_nat: {
		/* Integer constant tokens */
		NAT n;
		s++;
		n = unmangle_nat(&s);
		if (!IS_NULL_nat(n)) {
			MAKE_tok_nat(n, tok);
		}
		break;
	}
	case MANGLE_stmt: {
		/* Statement tokens */
		EXP e;
		s++;
		e = unmangle_exp(&s, type_void);
		if (!IS_NULL_exp(e)) {
			MAKE_tok_stmt(e, tok);
		}
		break;
	}
	case MANGLE_type: {
		/* Type tokens */
		TYPE t;
		s++;
		t = unmangle_type(&s, cv_none, btype_none, 1);
		MAKE_tok_type(btype_none, t, tok);
		break;
	}
	default: {
		/* Expression tokens */
		TYPE t = unmangle_type(&s, cv_none, btype_none, 1);
		EXP e = unmangle_exp(&s, t);
		if (!IS_NULL_exp(e)) {
			MAKE_tok_exp(t, 0, e, tok);
		}
		break;
	}
	}
	*ps = s;
	return tok;
}


/*
    This routine unmangles a list of token or template arguments from the
    string pointed to by ps.
*/

static LIST(TOKEN)
unmangle_token_args(string *ps)
{
	string s = *ps;
	unsigned n = unmangle_digit(&s);
	LIST(TOKEN)args = NULL_list(TOKEN);
	while (n) {
		TOKEN tok = unmangle_token_arg(&s);
		if (!IS_NULL_tok(tok)) {
			CONS_tok(tok, args, args);
		}
		if (*s == 0) {
			break;
		}
		n--;
	}
	args = REVERSE_list(args);
	*ps = s;
	return args;
}


/*
    This routine returns the an argument from the current argument list.
    The arguments are numbered from zero.
*/

static TOKEN
find_token_arg(string *ps)
{
	unsigned n = unmangle_digit(ps);
	LIST(TOKEN)args = crt_unmangle_args;
	while (!IS_NULL_list(args)) {
		if (n == 0) {
			/* Token argument found */
			TOKEN arg = DEREF_tok(HEAD_list(args));
			return arg;
		}
		n--;
		args = TAIL_list(args);
	}
	return NULL_tok;
}


/*
    This routine returns the mth parameter type from the members mem.
    The parameters are numbered from one, with n giving the total number
    of parameters.
*/

static TYPE
unmangle_param(unsigned m, unsigned n, MEMBER mem)
{
	while (!IS_NULL_member(mem)) {
		IDENTIFIER id = DEREF_id(member_id(mem));
		if (!IS_NULL_id(id) && IS_id_parameter(id)) {
			if (m == n) {
				/* Parameter type found */
				TYPE t = DEREF_type(id_parameter_type(id));
				return t;
			}
			m++;
		}
		mem = DEREF_member(member_next(mem));
	}
	return type_error;
}


/*
    This routine unmangles a function type from the string pointed to
    by ps.
*/

static TYPE
unmangle_func(string *ps, CV_SPEC cv, int ret)
{
	TYPE t;
	string s = *ps;
	character c = *s;
	if (c == MANGLE_const) {
		/* Const member function type */
		s++;
		cv |= cv_const;
		t = unmangle_func(&s, cv, ret);
	} else if (c == MANGLE_volatile) {
		/* Volatile member function type */
		s++;
		cv |= cv_volatile;
		t = unmangle_func(&s, cv, ret);
	} else if (c == MANGLE_c_lang) {
		/* C linkage function type */
		s++;
		cv |= cv_c;
		t = unmangle_func(&s, cv, ret);
	} else {
		/* Read list of parameter types */
		TYPE t1;
		MEMBER mem;
		NAMESPACE ns;
		unsigned npars = 0;
		int ell = FUNC_NONE;
		begin_param(NULL_id);
		ns = crt_namespace;
		for (;;) {
			/* Read parameter types */
			unsigned m;
			unsigned n = 1;
			c = *s;
			if (c == 0) {
				break;
			} else if (c == MANGLE_ellipsis) {
				/* Ellipsis */
				s++;
				ell = FUNC_ELLIPSIS;
				break;
			} else if (c == MANGLE_repeat) {
				/* Repeated parameter */
				s++;
				m = unmangle_digit(&s);
				mem = DEREF_member(nspace_last(ns));
				t1 = unmangle_param(m, npars, mem);
			} else if (c == MANGLE_multi) {
				/* Multiply repeated parameter */
				s++;
				n = unmangle_digit(&s);
				m = unmangle_no(&s, 1);
				mem = DEREF_member(nspace_last(ns));
				t1 = unmangle_param(m, npars, mem);
			} else {
				/* Simple parameter type */
				t1 = unmangle_type(&s, cv_none, btype_none, 1);
				if (IS_type_error(t1))break;
			}
			while (n) {
				/* Declare parameters */
				DECL_SPEC ds = dspec_none;
				HASHID nm = lookup_anon();
				IDENTIFIER pid = DEREF_id(hashid_id(nm));
				pid = make_param_decl(ds, t1, pid,
						      CONTEXT_PARAMETER);
				init_param(pid, NULL_exp);
				npars++;
				n--;
			}
		}
		t = make_func_type(dummy_ret_type, ell, cv, empty_type_set);
		end_param();
		if (ret) {
			/* Read return type */
			c = *(s++);
			if (c == MANGLE_sep) {
				t1 = unmangle_type(&s, cv_none, btype_none, 1);
			} else {
				t1 = type_error;
				s--;
			}
			COPY_type(type_func_ret(t), NULL_type);
			t = inject_pre_type(t, t1, 0);
		}
	}
	*ps = s;
	return t;
}


/*
    This routine unmangles a type from the string pointed to by ps.
*/

static TYPE
unmangle_type(string *ps, CV_SPEC cv, BASE_TYPE bt, int ret)
{
	TYPE t;
	string s = *ps;
	character c = *(s++);
	switch (c) {

	case MANGLE_char:  t = make_base_type(bt | btype_char);  break;
	case MANGLE_short: t = make_base_type(bt | btype_short); break;
	case MANGLE_int:   t = make_base_type(bt | btype_int);   break;
	case MANGLE_long:  t = make_base_type(bt | btype_long);  break;
	case MANGLE_llong: t = make_base_type(bt | btype_llong); break;

	case MANGLE_float:     t = type_float;     break;
	case MANGLE_double:    t = type_double;    break;
	case MANGLE_ldouble:   t = type_ldouble;   break;
	case MANGLE_void:      t = type_void;      break;
	case MANGLE_bottom:    t = type_bottom;    break;
	case MANGLE_bool:      t = type_bool;      break;
	case MANGLE_ptrdiff_t: t = type_ptrdiff_t; break;
	case MANGLE_size_t:    t = type_size_t;    break;
	case MANGLE_wchar_t:   t = type_wchar_t;   break;

	case MANGLE_signed: {
		/* Signed types */
		bt |= btype_signed;
		t = unmangle_type(&s, cv_none, bt, ret);
		break;
	}
	case MANGLE_unsigned: {
		/* Unsigned types */
		bt |= btype_unsigned;
		t = unmangle_type(&s, cv_none, bt, ret);
		break;
	}
	case MANGLE_const: {
		/* Const types */
		cv |= cv_const;
		t = unmangle_type(&s, cv, bt, ret);
		cv = cv_none;
		break;
	}
	case MANGLE_volatile: {
		/* Volatile types */
		cv |= cv_volatile;
		t = unmangle_type(&s, cv, bt, ret);
		cv = cv_none;
		break;
	}
	case MANGLE_ptr: {
		/* Pointer types */
		TYPE t1 = unmangle_type(&s, cv_none, btype_none, 1);
		MAKE_type_ptr(cv, NULL_type, t);
		t = inject_pre_type(t, t1, 0);
		cv = cv_none;
		break;
	}
	case MANGLE_ref: {
		/* Reference types */
		TYPE t1 = unmangle_type(&s, cv, btype_none, 1);
		MAKE_type_ref(cv_none, NULL_type, t);
		t = inject_pre_type(t, t1, 0);
		cv = cv_none;
		break;
	}
	case MANGLE_ptr_mem: {
		/* Pointer to member types */
		TYPE t1 = unmangle_type(&s, cv_none, btype_none, 1);
		TYPE t2 = unmangle_type(&s, cv_none, btype_none, 1);
		if (IS_type_compound(t1)) {
			CLASS_TYPE c1 = DEREF_ctype(type_compound_defn(t1));
			MAKE_type_ptr_mem(cv, c1, NULL_type, t);
		} else {
			report(crt_loc, ERR_dcl_mptr_class(t1));
			MAKE_type_ptr(cv, NULL_type, t);
		}
		t = inject_pre_type(t, t2, 0);
		cv = cv_none;
		break;
	}
	case MANGLE_func: {
		/* Function types */
		t = unmangle_func(&s, cv, ret);
		cv = cv_none;
		break;
	}
	case MANGLE_array: {
		/* Array types */
		NAT n = unmangle_nat(&s);
		TYPE t1 = unmangle_type(&s, cv, btype_none, 1);
		n = check_array_dim(n);
		MAKE_type_array(cv_none, NULL_type, n, t);
		t = inject_pre_type(t, t1, 0);
		cv = cv_none;
		break;
	}
	case MANGLE_bitfield: {
		/* Bitfield types */
		TYPE t1;
		NAT n = unmangle_nat(&s);
		BASE_TYPE b1 = btype_named;
		if (*s == MANGLE_signed) {
			b1 |= btype_signed;
		}
		t1 = unmangle_type(&s, cv_none, btype_none, 1);
		b1 = get_bitfield_rep(t1, b1);
		t = check_bitfield_type(cv, t1, b1, n, 0);
		cv = cv_none;
		break;
	}
	case MANGLE_template: {
		/* Template class types */
		IDENTIFIER id = unmangle_nspace(&s, global_namespace, 0);
		if (IS_NULL_id(id)) {
			t = type_error;
		} else {
			LIST(TOKEN)args = unmangle_token_args(&s);
			MAKE_type_token(cv, id, args, t);
			cv = cv_none;
		}
		break;
	}
	case MANGLE_templ_param: {
		/* Template parameter types */
		TOKEN tok = find_token_arg(&s);
		if (!IS_NULL_tok(tok) && IS_tok_type(tok)) {
			t = DEREF_type(tok_type_value(tok));
		} else {
			t = type_error;
		}
		break;
	}
	case MANGLE_promote: {
		/* Promotion types */
		TYPE t1 = unmangle_type(&s, cv_none, btype_none, 1);
		t = promote_type(t1);
		break;
	}
	case MANGLE_arith: {
		/* Arithmetic types */
		TYPE t1 = unmangle_type(&s, cv_none, btype_none, 1);
		TYPE t2 = unmangle_type(&s, cv_none, btype_none, 1);
		t = arith_type(t1, t2, NULL_exp, NULL_exp);
		break;
	}
	case MANGLE_literal: {
		/* Literal types */
		NAT n;
		int fit = 0;
		int form = BASE_DECIMAL;
		int suff = SUFFIX_NONE;
		c = *s;
		if (c == MANGLE_octal) {
			form = BASE_OCTAL;
			c = *(++s);
		} else if (c == MANGLE_hex) {
			form = BASE_HEXADECIMAL;
			c = *(++s);
		}
		if (c == MANGLE_unsigned) {
			suff |= SUFFIX_U;
			c = *(++s);
		}
		if (c == MANGLE_long) {
			suff |= SUFFIX_L;
			c = *(++s);
		}
		if (c == MANGLE_llong) {
			suff |= SUFFIX_LL;
			s++;
		}
		n = unmangle_nat(&s);
		if (IS_NULL_nat(n)) {
			n = small_nat[0];
		}
		t = find_literal_type(n, form, suff, NULL_string, &fit);
		break;
	}
	case MANGLE_self: {
		/* Parent class type */
		IDENTIFIER self = crt_unmangle_class;
		if (IS_NULL_id(self)) {
			t = type_error;
		} else {
			t = DEREF_type(id_class_name_etc_defn(self));
		}
		break;
	}
	case char_zero:
	case char_one:
	case char_two:
	case char_three:
	case char_four:
	case char_five:
	case char_six:
	case char_seven:
	case char_eight:
	case char_nine:
	case MANGLE_qual: {
		/* Named types */
		IDENTIFIER id;
		s--;
		id = unmangle_nspace(&s, global_namespace, 0);
		if (IS_NULL_id(id)) {
			t = type_error;
		} else {
			t = DEREF_type(id_class_name_etc_defn(id));
		}
		break;
	}

	default: {
		/* Invalid mangled types */
		if (bt == btype_none && cv == cv_none) {
			t = type_error;
		} else {
			t = make_base_type(bt | btype_int);
		}
		s--;
		break;
	}
	}
	if (cv) {
		t = qualify_type(t, cv, 0);
	}
	*ps = s;
	return t;
}


/*
    This routine unmangles the identifier s into the buffer bf.
*/

static string
unmangle_name(string s, BUFFER *bf)
{
	int func = 0;
	int op = lex_identifier;
	IDENTIFIER id = NULL_id;
	HASHID nm = NULL_hashid;

	/* Check names beginning with '__' */
	if (s[0] == '_' && s[1] == '_') {
		string s0 = s + 2;
		op = unmangle_op(&s0);
		if (op == lex_unknown) {
#if (TDF_major < 4)
			if (ustrseq(s, "__MAIN__")) {
				s = ustrlit("main");
			}
#endif
			bfputs(bf, s);
			return NULL;
		}
		s = s0;
	}

	/* Read identifier name */
	switch (op) {
	case lex_identifier: {
		/* Identifier name */
		character c;
		int ext = 0;
		unsigned long h;
		BUFFER *tf = clear_buffer(&token_buff, NIL(FILE));
		while (c = *s, c != 0) {
			if (c == MANGLE_sep && s[1] == MANGLE_sep) {
				c = s[2];
				if (c == MANGLE_unicode4) {
					bfputc(tf, char_backslash);
					c = char_u;
					ext = 1;
					s += 2;
				} else if (c == MANGLE_unicode8) {
					bfputc(tf, char_backslash);
					c = char_U;
					ext = 1;
					s += 2;
				} else {
					break;
				}
			}
			bfputc(tf,(int)c);
			s++;
		}
		bfputc(tf, 0);
		h = hash(tf->start);
		nm = lookup_name(tf->start, h, ext, lex_unknown);
		id = DEREF_id(hashid_id(nm));
		break;
	}
	case lex_type_Hname:
	case lex_destructor_Hname: {
		/* Constructor and destructor names */
		func = 1;
		break;
	}
	case lex_operator: {
		/* Conversion function name */
		TYPE t = unmangle_type(&s, cv_none, btype_none, 1);
		nm = lookup_conv(t);
		id = DEREF_id(hashid_id(nm));
		func = 1;
		break;
	}
	case lex_auto: {
		/* Anonymous identifier */
		bfprintf(bf, "<anon>");
		return NULL;
	}
	case lex_static: {
		/* Local static variable */
		bfprintf(bf, "<static>");
		return NULL;
	}
	case lex_typeof: {
		/* Run-time type information */
		TYPE t = unmangle_type(&s, cv_none, btype_none, 1);
		bfprintf(bf, "typeid ( ");
		IGNORE print_type(t, bf, 0);
		bfprintf(bf, " )");
		return s;
	}
	case lex_virtual: {
		/* Virtual function table */
		int sep = 0;
		bfprintf(bf, "vtable ( ");
		for (;;) {
			id = unmangle_nspace(&s, global_namespace, 0);
			if (IS_NULL_id(id)) {
				break;
			}
			if (sep) {
				bfprintf(bf, "::");
			}
			IGNORE print_id_long(id, qual_none, bf, 0);
			sep = 1;
		}
		if (!sep) {
			bfprintf(bf, "<error>");
		}
		bfprintf(bf, " )");
		return s;
	}

	default: {
		/* Operator name */
		nm = lookup_op(op);
		if (!IS_NULL_hashid(nm)) {
			id = DEREF_id(hashid_id(nm));
			func = 1;
		}
		break;
	}
	}

	/* Unmangle identifier namespace and type */
	if (s[0] == MANGLE_sep && s[1] == MANGLE_sep) {
		TYPE t;
		string s0 = s + 2;
		NAMESPACE pns = global_namespace;
		IDENTIFIER pid = unmangle_nspace(&s0, pns, 0);
		character c = *s0;
		if (c == MANGLE_func_templ) {
			/* Allow for template functions */
			s0++;
			crt_unmangle_args = unmangle_token_args(&s0);
			if (*s0 == MANGLE_sep) {
				s0++;
			}
		}

		/* Unmangle identifier type */
		if (func) {
			crt_unmangle_class = pid;
			t = unmangle_func(&s0, cv_none, 0);
		} else {
			if (c == 0 && !IS_NULL_id(pid)) {
				t = DEREF_type(id_class_name_etc_defn(pid));
				pid = NULL_id;
			} else {
				crt_unmangle_class = pid;
				t = unmangle_type(&s0, cv_none, btype_none, 0);
			}
		}
		if (IS_NULL_id(pid)) {
			member_func_type(NULL_ctype, id_function_tag, t);
		}

		/* Look up constructor and destructor names */
		if (!IS_NULL_id(pid)) {
			TYPE p = DEREF_type(id_class_name_etc_defn(pid));
			if (IS_type_compound(p)) {
				CLASS_TYPE ct =
				    DEREF_ctype(type_compound_defn(p));
				pns = DEREF_nspace(ctype_member(ct));
				if (op == lex_type_Hname) {
					id = DEREF_id(ctype_constr(ct));
					nm = DEREF_hashid(id_name(id));
				} else if (op == lex_destructor_Hname) {
					id = DEREF_id(ctype_destr(ct));
					nm = DEREF_hashid(id_name(id));
				}
			}
		}
		if (IS_NULL_hashid(nm)) {
			nm = KEYWORD(lex_zzzz);
		}

		/* Create result identifier */
		MAKE_id_function(nm, dspec_extern, pns, crt_loc, t, NULL_id,
				 id);
		if (c == MANGLE_func_templ) {
			/* Set up template function arguments */
			TYPE form;
			DECL_SPEC ds = (dspec_extern | dspec_instance);
			MAKE_type_token(cv_none, id, crt_unmangle_args, form);
			MAKE_id_function(nm, ds, pns, crt_loc, t, NULL_id, id);
			COPY_type(id_function_form(id), form);
		}
		crt_unmangle_args = NULL_list(TOKEN);
		crt_unmangle_class = NULL_id;
		s = s0;
	}

	/* Print identifier to buffer */
	if (IS_NULL_id(id)) {
		bfprintf(bf, "<error>");
		s = NULL;
	} else {
		print_id_desc++;
		IGNORE print_id_long(id, qual_none, bf, 0);
		print_id_desc--;
	}
	return s;
}


/*
    This routine initialises the unmangling routines.
*/

static void
init_unmangle(void)
{
	static int done = 0;
	if (!done) {
		MAKE_type_pre(cv_none, btype_none, qual_none, dummy_ret_type);
		done = 1;
	}
	return;
}


/*
    The remaining routine is the only one included in the C producer.
*/

#endif


/*
    This routine unmangles the list of identifier names p to the file f.
*/

void
unmangle_list(LIST(string)p, FILE *f, int pre)
{
#if LANGUAGE_CPP
	init_unmangle();
#endif
	while (!IS_NULL_list(p)) {
		string s = DEREF_string(HEAD_list(p));
		if (s) {
			BUFFER *bf = clear_buffer(&mangle_buff, f);
			if (pre) {
				/* Print mapping information */
				bfprintf(bf, "%s -> ", s);
			}
#if LANGUAGE_CPP
			s = unmangle_name(s, bf);
			if (s && *s) {
				bfprintf(bf, " ?");
			}
#else
			bfputs(bf, s);
#endif
			bfputc(bf, '\n');
			output_buffer(bf, 1);
		}
		p = TAIL_list(p);
	}
	fflush_v(f);
	return;
}
