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
#include "exp_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "member_ops.h"
#include "str_ops.h"
#include "tok_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "option.h"
#include "tdf.h"
#include "basetype.h"
#include "capsule.h"
#include "compile.h"
#include "diag.h"
#include "encode.h"
#include "exp.h"
#include "hash.h"
#include "interface.h"
#include "namespace.h"
#include "preproc.h"
#include "shape.h"
#include "statement.h"
#include "stmt.h"
#include "struct.h"
#include "syntax.h"
#include "tok.h"
#include "token.h"
#include "ustring.h"


/*
    This table gives the name, the parameter and result sorts, and external
    (capsule) number for the various special tokens used in the output.
    Each special token may have an associated externally declared token
    identifier.  The entries in this table correspond to the TOK values
    defined in tok.h.
*/

static struct {
	const char *name;
	const char *sorts;
	ulong no;
	ulong diag;
	IDENTIFIER tok;
	int builtin;
} special_token[TOK_no] = {
	/* Built-in integral types */
	{ "~char", "V", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~signed_char", "V", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~unsigned_char", "V", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~signed_short", "V", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~unsigned_short", "V", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~signed_int", "V", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~unsigned_int", "V", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~signed_long", "V", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~unsigned_long", "V", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~signed_longlong", "V", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~unsigned_longlong", "V", LINK_NONE, LINK_NONE, NULL_id, 0 },

	/* Built-in floating-point types */
	{ "~float", "F", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~double", "F", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~long_double", "F", LINK_NONE, LINK_NONE, NULL_id, 0 },

	/* Standard integral types */
	{ "~cpp.bool", "Z", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "ptrdiff_t", "Z", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "size_t", "Z", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "__size_t", "Z", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "wchar_t", "Z", LINK_NONE, LINK_NONE, NULL_id, 0 },

	/* Integral type conversions */
	{ "~convert", "VZ", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~arith_type", "ZZZ", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~promote", "ZZ", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~sign_promote", "ZZ", LINK_NONE, LINK_NONE, NULL_id, 0 },

	/* Integer literal types */
	{ "~lit_int", "ZZ", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~lit_hex", "ZZ", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~lit_unsigned", "ZZ", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~lit_long", "ZZ", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~lit_ulong", "ZZ", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~lit_longlong", "ZZ", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~lit_ulonglong", "ZZ", LINK_NONE, LINK_NONE, NULL_id, 0 },

	/* Bitfield types */
	{ "~cpp.bitf_sign", "BZ", LINK_NONE, LINK_NONE, NULL_id, 0 },

	/* Generic pointers */
	{ "~ptr_void", "S", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~null_pv", "E", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~to_ptr_void", "EAE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~from_ptr_void", "EAE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~pv_test", "EELT", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.pv_compare", "EEELT", LINK_NONE, LINK_NONE, NULL_id, 0 },

	/* Undefined conversions */
	{ "~ptr_to_ptr", "EAAE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~f_to_pv", "EE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~pv_to_f", "EE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~i_to_p", "EVAE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~p_to_i", "EAVE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~i_to_pv", "EVE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~pv_to_i", "EVE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.ptr_rep", "Z", LINK_NONE, LINK_NONE, NULL_id, 0 },

	/* Integer division */
	{ "~div", "EEE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~rem", "EEE", LINK_NONE, LINK_NONE, NULL_id, 0 },

	/* Ellipsis functions */
	{ "~__va_t", "S", LINK_NONE, LINK_NONE, NULL_id, 0 },

	/* Pointers to data members */
	{ "~cpp.pm.type", "S", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.pm.make", "EE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.pm.null", "E", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.pm.offset", "EEA", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.pm.cast", "EEE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.pm.uncast", "EEE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.pm.test", "EELT", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.pm.compare", "EEELT", LINK_NONE, LINK_NONE, NULL_id, 0 },

	/* Pointers to function members */
	{ "~cpp.pmf.type", "S", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.pmf.make", "EEEE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.pmf.vmake", "EZEEE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.pmf.null", "E", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.pmf.null2", "E", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.pmf.delta", "EAE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.pmf.func", "EE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.pmf.virt", "EEEA", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.pmf.cast", "EEEEE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.pmf.uncast", "EEEEE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.pmf.test", "EELT", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.pmf.compare", "EEELT", LINK_NONE, LINK_NONE, NULL_id, 0 },

	/* Class layout */
	{ "~comp_off", "EE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~pad", "EESS", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.empty.align", "A", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.empty.shape", "S", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.empty.offset", "E", LINK_NONE, LINK_NONE, NULL_id, 0 },

	/* Virtual function tables */
	{ "~cpp.vtab.type", "SN", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.vtab.diag", "S", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.vtab.make", "EEENE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.vtab.pure", "E", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.vtab.func", "EEZ", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.vtab.off", "EZ", LINK_NONE, LINK_NONE, NULL_id, 0 },

	/* Run-time type information */
	{ "~cpp.typeid.type", "S", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.typeid.make", "EZEE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.typeid.basic", "EZ", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.typeid.ref", "EE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.baseid.type", "S", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.baseid.make", "EEEEZZ", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.dynam.cast", "EEE", LINK_NONE, LINK_NONE, NULL_id, 0 },

	/* Dynamic initialisation */
	{ "~cpp.destr.type", "S", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.destr.global", "EEEE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.destr.local", "EEEE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.destr.end", "EE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.destr.init", "E", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.destr.null", "E", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.destr.ptr", "EE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.start", "E", LINK_NONE, LINK_NONE, NULL_id, 0 },

	/* Exception handling */
	{ "~cpp.try.type", "S", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.try.begin", "EEEE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.try.end", "EE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.except.alloc", "EE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.except.throw", "EEEE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.except.rethrow", "E", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.except.catch", "EE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.except.value", "E", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.except.caught", "E", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.except.end", "E", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.except.bad", "EZ", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~cpp.except.jump", "EEE", LINK_NONE, LINK_NONE, NULL_id, 1 },
	{ "~cpp.ptr.code", "S", LINK_NONE, LINK_NONE, NULL_id, 1 },
	{ "~cpp.ptr.frame", "S", LINK_NONE, LINK_NONE, NULL_id, 1 },

	/* Assembler inserts */
	{ "~asm_sequence", "EE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~asm", "EC", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~asm_exp_input", "EE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~asm_exp_output", "EE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	{ "~asm_exp_address", "EE", LINK_NONE, LINK_NONE, NULL_id, 0 },

	/* Built-in shorthands */
	{ "~cpp.char_offset", "E", LINK_NONE, LINK_NONE, NULL_id, 2 },
	{ "~cpp.shape_offset", "ES", LINK_NONE, LINK_NONE, NULL_id, 2 },
	{ "~cpp.extra_offset", "EAE", LINK_NONE, LINK_NONE, NULL_id, 2 },
	{ "~cpp.down_cast", "EAEE", LINK_NONE, LINK_NONE, NULL_id, 2 },
	{ "~cpp.destr_cast", "EAE", LINK_NONE, LINK_NONE, NULL_id, 2 },
	{ "~cpp.destr_test", "EEL", LINK_NONE, LINK_NONE, NULL_id, 2 }

#if 0
	/* Unused standard C tokens */
	{ "~assign", "EEES", LINK_NONE, LINK_NONE, NULL_id, 0 },
	    { "~assign_vol", "EEES", LINK_NONE, LINK_NONE, NULL_id, 0 },
	    { "~char_lit", "EEZV", LINK_NONE, LINK_NONE, NULL_id, 0 },
	    { "~checked_plus", "EEE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	    { "~debug_exp", "ENE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	    { "~debug_scope", "ENNE", LINK_NONE, LINK_NONE, NULL_id, 0 },
	    { "~fn_scope", "EENN", LINK_NONE, LINK_NONE, NULL_id, 0 },
	    { "~int_promot", "Z", LINK_NONE, LINK_NONE, NULL_id, 0 },
	    { "~little_endian", "E", LINK_NONE, LINK_NONE, NULL_id, 0 },
	    { "~ptr_add", "EEES", LINK_NONE, LINK_NONE, NULL_id, 0 },
	    { "~ptr_sub", "EEES", LINK_NONE, LINK_NONE, NULL_id, 0 },
	    { "~sizeof", "ES", LINK_NONE, LINK_NONE, NULL_id, 0 },
	    { "~string_lit", "EEZV", LINK_NONE, LINK_NONE, NULL_id, 0 },
	    { "~wchar_lit", "EEZV", LINK_NONE, LINK_NONE, NULL_id, 0 },
#endif
};


/*
    This table gives the mapping from built-in type numbers to external
    token names.
*/

BASE_TOKEN base_token[ORDER_ntype] = {
    { 0, ARITH_error, ARITH_error },			/* ntype_none */
    { TOK_char, ARITH_char, ARITH_char },		/* ntype_char */
    { TOK_signed_char, ARITH_schar, ARITH_schar },	/* ntype_schar */
    { TOK_unsigned_char, ARITH_uchar, ARITH_uchar },	/* ntype_uchar */
    { TOK_signed_short, ARITH_sshort, ARITH_sshort },	/* ntype_sshort */
    { TOK_unsigned_short, ARITH_ushort, ARITH_ushort },	/* ntype_ushort */
    { TOK_signed_int, ARITH_sint, ARITH_sint },		/* ntype_sint */
    { TOK_unsigned_int, ARITH_uint, ARITH_uint },	/* ntype_uint */
    { TOK_signed_long, ARITH_slong, ARITH_slong },	/* ntype_slong */
    { TOK_unsigned_long, ARITH_ulong, ARITH_ulong },	/* ntype_ulong */
    { TOK_signed_llong, ARITH_sllong, ARITH_sllong },	/* ntype_sllong */
    { TOK_unsigned_llong, ARITH_ullong, ARITH_ullong },	/* ntype_ullong */
    { TOK_float, ARITH_float, ARITH_float },		/* ntype_float */
    { TOK_double, ARITH_double, ARITH_double },		/* ntype_double */
    { TOK_long_double, ARITH_ldouble, ARITH_ldouble },	/* ntype_ldouble */
    { 0, ARITH_void, ARITH_void },			/* ntype_void */
    { 0, ARITH_bottom, ARITH_void },			/* ntype_bottom */
    { TOK_bool, ARITH_none, ARITH_bool },		/* ntype_bool */
    { TOK_ptrdiff_t, ARITH_none, ARITH_ptrdiff_t },	/* ntype_ptrdiff_t */
    { TOK_size_t, ARITH_none, ARITH_size_t },		/* ntype_size_t */
    { TOK_wchar_t, ARITH_none, ARITH_wchar_t },		/* ntype_wchar_t */
    { 0, ARITH_ellipsis, ARITH_ellipsis }		/* ntype_ellipsis */
};


/*
    This routine initialises the special tokens.  This consists of
    marking certain tokens which are used but not defined in C as being
    built-in.
*/

void
init_tok(int c)
{
	if (output_std) {
		/* Backwards compatibility */
		if (c) {
			special_token[TOK_bitf_sign].builtin = 2;
			special_token[TOK_pv_compare].builtin = 2;
			special_token[TOK_empty_align].builtin = 2;
			special_token[TOK_empty_offset].builtin = 2;
			special_token[TOK_empty_shape].builtin = 2;
		}
		special_token[TOK_ptr_rep].builtin = 2;
	}
	if (c) {
		special_token[TOK_start].builtin = 2;
		base_token[ntype_bool].tok = TOK_signed_int;
		base_token[ntype_bool].no = ARITH_sint;
	}
	return;
}


/*
    This routine sets the special token t to be id.
*/

void
set_special(int t, IDENTIFIER id)
{
	if (!IS_NULL_id(id)) {
		ulong n = DEREF_ulong(id_no(id));
		ulong m = special_token[t].no;
		if (n == LINK_NONE) {
			COPY_ulong(id_no(id), m);
			special_token[t].tok = id;
		} else if (m == LINK_NONE) {
			special_token[t].no = n;
			special_token[t].tok = id;
		} else {
			/* Should not happen */
			/* EMPTY */
		}
	}
	return;
}


/*
    This routine returns the token identifier associated with special
    token t.  If force is true then this involves looking up the name
    in the token namespace.  The null identifier is returned if there
    is no associated identifier.
*/

IDENTIFIER
get_special(int t, int force)
{
	IDENTIFIER id = special_token[t].tok;
	if (IS_NULL_id(id) && force) {
		if (special_token[t].builtin != 2) {
			string s = ustrlit(special_token[t].name);
			unsigned long h = hash(s);
			HASHID nm = lookup_name(s, h, 0, lex_identifier);
			NAMESPACE ns = token_namespace;
			MEMBER mem = search_member(ns, nm, 0);
			if (!IS_NULL_member(mem)) {
				id = DEREF_id(member_id(mem));
				set_special(t, id);
			}
		}
	}
	return id;
}


/*
    This routine returns the name of the special token t.
*/

string
special_name(int t)
{
	return ustrlit(special_token[t].name);
}


/*
    This routine returns the token code letter corresponding to the token
    tok.
*/

int
token_code(TOKEN tok)
{
	if (!IS_NULL_tok(tok)) {
		switch (TAG_tok(tok)) {
		case tok_exp_tag:
		case tok_stmt_tag:
		case tok_func_tag:
		case tok_member_tag: {
			return 'E';
		}
		case tok_nat_tag: {
			return 'N';
		}
		case tok_snat_tag: {
			return 'Z';
		}
		case tok_type_tag: {
			BASE_TYPE bt = DEREF_btype(tok_type_kind(tok));
			if (bt & btype_scalar) {
				return 'Z';
			}
			return 'S';
		}
		case tok_proc_tag: {
			TOKEN res = DEREF_tok(tok_proc_res(tok));
			return token_code(res);
		}
		}
	}
	return '?';
}


/*
    This routine creates a token sort corresponding (more or less) to the
    string s.  If proc is true then the result is a procedure token.
*/

TOKEN
make_sort(const char *s, int proc)
{
	TOKEN tok;
	if (proc) {
		unsigned i;
		TOKEN ptok;
		unsigned n = (unsigned)strlen(s);
		LIST(IDENTIFIER)pids = NULL_list(IDENTIFIER);
		tok = begin_proc_token();
		for (i = 1; i < n; i++) {
			IDENTIFIER pid;
			ptok = make_sort(s + i, 0);
			pid = make_tok_param(ptok, 0, NULL_id);
			CONS_id(pid, pids, pids);
		}
		pids = REVERSE_list(pids);
		tok = cont_proc_token(tok, pids, pids);
		ptok = make_sort(s, 0);
		tok = end_proc_token(tok, ptok);
	} else {
		switch (*s) {
		case 'E': {
			tok = make_exp_token(type_error, 0, 0);
			break;
		}
		case 'N': {
			MAKE_tok_nat(NULL_nat, tok);
			break;
		}
		case 'S': {
			tok = make_type_token(btype_none);
			break;
		}
		case 'Z': {
			tok = make_type_token(btype_int);
			break;
		}
		default : {
			FAIL(Unknown sort);
			tok = NULL_tok;
			break;
		}
		}
	}
	return tok;
}


/*
    This routine checks whether the sort of the token tok (either the
    program sort or the bound sort, depending on the value of prog)
    corresponds to the string s.
*/

static int
check_sort(TOKEN tok, const char *s, int prog)
{
	char r = *(s++);
	unsigned tag = TAG_tok(tok);
	if (tag == tok_func_tag) {
		/* Function tokens */
		tok = func_proc_token(tok);
		tag = TAG_tok(tok);
	}
	if (tag == tok_proc_tag) {
		/* Procedure tokens */
		LIST(IDENTIFIER)bids;
		TOKEN res = DEREF_tok(tok_proc_res(tok));
		char c = (char)token_code(res);
		if (c != r) {
			return 0;
		}
		r = *(s++);
		if (prog) {
			bids = DEREF_list(tok_proc_pids(tok));
		} else {
			bids = DEREF_list(tok_proc_bids(tok));
		}
		while (!IS_NULL_list(bids)) {
			IDENTIFIER bid = DEREF_id(HEAD_list(bids));
			if (!IS_NULL_id(bid) && IS_id_token(bid)) {
				res = DEREF_tok(id_token_sort(bid));
				c = (char)token_code(res);
			} else {
				c = '?';
			}
			if (c != r) {
				return 0;
			}
			c = *s;
			if (c == '*') {
				/* Don't advance after '*' */
				c = 0;
			} else {
				r = c;
				s++;
			}
			bids = TAIL_list(bids);
		}
		r = c;
	} else {
		/* Other tokens */
		char c = (char)token_code(tok);
		if (c != r) {
			return 0;
		}
		r = *s;
	}
	if (r) {
		return 0;
	}
	return 1;
}


/*
    This routine checks whether id is a token with the given sort, giving
    an error if id is not a token or has the wrong sort.
*/

IDENTIFIER
resolve_token(IDENTIFIER id, const char *s, int prog)
{
	int ok = 0;
	IDENTIFIER rid = NULL_id;
	IDENTIFIER pid = id;
	while (!IS_NULL_id(pid)) {
		IDENTIFIER tid = find_token(pid);
		if (IS_id_token(tid)) {
			TOKEN tok = DEREF_tok(id_token_sort(tid));
			if (check_sort(tok, s, prog)) {
				if (!IS_NULL_id(rid)) {
					report(preproc_loc,
					       ERR_lookup_ambig_id(pid));
					break;
				}
				rid = tid;
			} else {
				report(preproc_loc, ERR_pragma_token_sort(pid));
			}
			ok = 1;
		}
		if (!IS_id_function_etc(pid)) {
			break;
		}
		pid = DEREF_id(id_function_etc_over(pid));
	}
	if (!ok) {
		/* Token not found */
		report(preproc_loc, ERR_token_undecl(id));
	}
	return rid;
}


/*
    This routine checks whether the token id is one of the built-in tokens
    listed above.  If so this definition is output, provided TDF output is
    enabled, and the routine returns the corresponding special token number.
    Otherwise the routine returns -1.
*/

int
builtin_token(IDENTIFIER id)
{
	int t = 0;
	string s;
	HASHID nm = DEREF_hashid(id_name(id));
	if (!IS_hashid_name_etc(nm)) {
		return -1;
	}
	s = DEREF_string(hashid_name_etc_text(nm));
	if (s[0]!= '~') {
		/* Only built-in types don't begin with '~' */
		switch (find_hashid(nm)) {
		case lex_ptrdiff_Ht:
			t = TOK_ptrdiff_t;
			break;
		case lex_size_Ht:
			t = TOK_size_t;
			break;
		case lex_size_Ht_H2:
			t = TOK_size_t_2;
			break;
		case lex_wchar_Ht:
			t = TOK_wchar_t;
			break;
		default:
			return -1;
		}
	}
	while (t < TOK_no) {
		int b = special_token[t].builtin;
		if (b != 2) {
			string n = ustrlit(special_token[t].name);
			if (ustreq(s, n)) {
				const char *p = special_token[t].sorts;
				TOKEN sort = DEREF_tok(id_token_sort(id));
				if (!check_sort(sort, p, 0)) {
					/* Check that token sort matches */
					IDENTIFIER tid =
					    DEREF_id(id_token_alt(id));
					report(crt_loc,
					       ERR_pragma_token_sort(tid));
					return -1;
				}
				set_special(t, id);
				if (b) {
					/* Define token if possible */
					DECL_SPEC ds =
					    DEREF_dspec(id_storage(id));
					define_special(t);
					ds |= (dspec_defn | dspec_done);
					COPY_dspec(id_storage(id), ds);
				}
				return t;
			}
		}
		t++;
	}
	return -1;
}


/*
    The remaining routines in this module are only included if TDF output
    is enabled.
*/

#if TDF_OUTPUT


/*
    This routine adds the foreign sort named s to the bitstream bs.
*/

static BITSTREAM *
enc_foreign_sort(BITSTREAM *bs, const char *s)
{
	ENC_foreign_sort(bs);
	ENC_make_string(bs);
	bs = enc_ustring(bs, ustrlit(s));
	return bs;
}


/*
    This routine adds the TDF SORTNAME corresponding to the code letter s
    to the bitstream bs.
*/

BITSTREAM *
enc_sort(BITSTREAM *bs, int s)
{
	switch (s) {
	case 'A':
		ENC_alignment_sort(bs);
		break;
	case 'B':
		ENC_bool(bs);
		break;
	case 'C':
		ENC_string(bs);
		break;
	case 'E':
		ENC_exp(bs);
		break;
	case 'F':
		ENC_floating_variety(bs);
		break;
	case 'L':
		ENC_label(bs);
		break;
	case 'N':
		ENC_nat(bs);
		break;
	case 'S':
		ENC_shape(bs);
		break;
	case 'T':
		ENC_ntest(bs);
		break;
	case 'U':
		ENC_bitfield_variety(bs);
		break;
	case 'V':
		ENC_variety(bs);
		break;
	case 'Z':
		ENC_signed_nat(bs);
		break;
	case 'P': {
		bs = enc_foreign_sort(bs, LINK_filename);
		break;
	}
#ifdef ENC_dg_filename_apply_token
	case 'Q': {
		bs = enc_foreign_sort(bs, LINK_dg_filename);
		break;
	}
#endif
	default: {
		FAIL(Unknown sort);
		break;
	}
	}
	return bs;
}


/*
    This routine adds a token application construct for the sort with
    code letter s to the bitstream bs.
*/

static BITSTREAM *
enc_apply_token(BITSTREAM *bs, int s)
{
	switch (s) {
	case 'A':
		ENC_alignment_apply_token(bs);
		break;
	case 'B':
		ENC_bool_apply_token(bs);
		break;
	case 'C':
		ENC_string_apply_token(bs);
		break;
	case 'E':
		ENC_exp_apply_token(bs);
		break;
	case 'F':
		ENC_flvar_apply_token(bs);
		break;
	case 'L':
		ENC_label_apply_token(bs);
		break;
	case 'N':
		ENC_nat_apply_token(bs);
		break;
	case 'S':
		ENC_shape_apply_token(bs);
		break;
	case 'T':
		ENC_ntest_apply_token(bs);
		break;
	case 'U':
		ENC_bfvar_apply_token(bs);
		break;
	case 'V':
		ENC_var_apply_token(bs);
		break;
	case 'Z':
		ENC_signed_nat_apply_token(bs);
		break;
	case 'P':
		ENC_filename_apply_token(bs);
		break;
#ifdef ENC_dg_filename_apply_token
	case 'Q':
		ENC_dg_filename_apply_token(bs);
		break;
#endif
	default:
		FAIL(Unknown sort);
		break;
	}
	return bs;
}


/*
    This routine returns the external (capsule) token number of the
    special token given by t.
*/

ulong
special_no(int t)
{
	ulong n = special_token[t].no;
	if (n == LINK_NONE) {
		/* Declare token */
		int def = 0;
		IDENTIFIER id = special_token[t].tok;
		if (!IS_NULL_id(id)) {
			n = DEREF_ulong(id_no(id));
			if (n != LINK_NONE) {
				special_token[t].no = n;
				return n;
			}
			IGNORE capsule_id(id, VAR_token);
			n = DEREF_ulong(id_no(id));
		} else {
			string s = ustrlit(special_token[t].name);
			if (special_token[t].builtin == 2) {
				s = NULL;
				def = 1;
			}
			n = capsule_no(s, VAR_token);
		}
		special_token[t].no = n;
		if (tokdec_unit) {
			/* Declare token */
			const char *sorts = special_token[t].sorts;
			enc_tokdec(n, sorts);
		}
		if (def) {
			/* Define token if necessary */
			define_special(t);
		}
	}
	return n;
}


/*
    This routine adds an application of the special token given by t to
    the bitstream bs.  If the token takes no arguments the zero value
    representing these arguments is added, otherwise the arguments must
    be encoded by hand.
*/

BITSTREAM *
enc_special(BITSTREAM *bs, int t)
{
	ulong n;
	const char *sorts = special_token[t].sorts;
	bs = enc_apply_token(bs,(int)sorts[0]);
	n = special_no(t);
	n = link_no(bs, n, VAR_token);
	ENC_make_tok(bs, n);
	if (sorts[1]) {
		/* Arguments must be encoded separately */
		/* EMPTY */
	} else {
		ENC_LEN_SMALL(bs, 0);
	}
	return bs;
}


/*
    Certain of the special tokens which represent types also have diagnostic
    tag forms.  This routine adds a diagnostic tag for the special token t
    to the bitstream bs.
*/

BITSTREAM *
enc_diag_special(BITSTREAM *bs, int t, int v)
{
	ulong n = special_token[t].diag;
	if (n == LINK_NONE) {
		string s = ustrlit(special_token[t].name);
		n = capsule_no(s, v);
		special_token[t].diag = n;
	}
	n = link_no(bs, n, v);
#if TDF_DIAG4
	if (v == VAR_dgtag) {
		ENC_dg_named_type(bs);
		ENC_make_dg_tag(bs, n);
		return bs;
	}
#endif
	ENC_use_diag_tag(bs);
	ENC_make_diag_tag(bs, n);
	return bs;
}


/*
    This routine adds the nth parameter for a token with sort string sort
    and parameters pars to the bitstream bs.
*/

static BITSTREAM *
enc_param(BITSTREAM *bs, int n, const char *sorts, ulong *pars)
{
	bs = enc_apply_token(bs,(int)sorts[n + 1]);
	ENC_make_tok(bs, pars[n]);
	ENC_LEN_SMALL(bs, 0);
	return bs;
}


/*
    Certain of the special tokens have built-in definitions.  This routine
    outputs such a definition for the special token t.
*/

void
define_special(int t)
{
	BITSTREAM *bs;
	ulong pars[10];
	const char *sorts;
	TYPE s = NULL_type;
	ulong n = special_no(t);
	unsigned acc = find_usage(n, VAR_token);
	if (acc & USAGE_DEFN) {
		return;
	}
	sorts = special_token[t].sorts;
	bs = enc_tokdef_start(n, sorts, pars, 0);
	switch (t) {
	case TOK_bitf_sign: {
		/* Bitfield sign (C version) */
		BITSTREAM *ts;
		TYPE c = type_sint;
		ENC_bool_cond(bs);
		ENC_and(bs);
		ENC_make_int(bs);
		bs = enc_variety(bs, c);
		bs = enc_param(bs, 0, sorts, pars);
		bs = enc_make_int(bs, c, ARITH_uchar);
		ts = start_bitstream(NIL(FILE), bs->link);
		ENC_false(ts);
		bs = enc_bitstream(bs, ts);
		ts = start_bitstream(NIL(FILE), bs->link);
		ENC_true(ts);
		bs = enc_bitstream(bs, ts);
		break;
	}
	case TOK_pv_compare: {
		/* Comparison of pointer to void (C version) */
		ENC_pointer_test(bs);
		ENC_OFF(bs);
		bs = enc_param(bs, 3, sorts, pars);
		bs = enc_param(bs, 2, sorts, pars);
		bs = enc_param(bs, 0, sorts, pars);
		bs = enc_param(bs, 1, sorts, pars);
		break;
	}
	case TOK_ptr_rep: {
		/* Integral type the same size as a pointer */
		bs = enc_make_snat(bs, ARITH_ulong);
		break;
	}
	case TOK_empty_align: {
		/* Alignment of empty class (C version) */
		bs = enc_alignment(bs, type_ldouble);
		break;
	}
	case TOK_empty_offset: {
		/* Offset of empty class (C version) */
		BITSTREAM *ts;
		TYPE c = type_char;
		bs = enc_special(bs, TOK_comp_off);
		ts = start_bitstream(NIL(FILE), bs->link);
		ENC_offset_add(ts);
		ENC_offset_zero(ts);
		ts = enc_alignment(ts, c);
		ENC_shape_offset(ts);
		ts = enc_shape(ts, c);
		bs = enc_bitstream(bs, ts);
		break;
	}
	case TOK_empty_shape: {
		/* Shape of empty class (C version) */
		ENC_compound(bs);
		bs = enc_special(bs, TOK_empty_offset);
		break;
	}
	case TOK_start: {
		/* Start of main routine (C version) */
		ENC_make_top(bs);
		break;
	}
	case TOK_char_offset: {
		/* Character offset */
		TYPE c = type_char;
		ENC_offset_pad(bs);
		ENC_alignment(bs);
		bs = enc_shape(bs, c);
		ENC_shape_offset(bs);
		bs = enc_shape(bs, c);
		break;
	}
	case TOK_shape_offset: {
		/* Shape offset */
		ENC_offset_pad(bs);
		ENC_alignment(bs);
		bs = enc_param(bs, 0, sorts, pars);
		ENC_shape_offset(bs);
		bs = enc_param(bs, 0, sorts, pars);
		break;
	}
	case TOK_extra_offset: {
		/* Offset padding */
		ENC_offset_subtract(bs);
		ENC_offset_pad(bs);
		bs = enc_param(bs, 0, sorts, pars);
		bs = enc_param(bs, 1, sorts, pars);
		ENC_offset_zero(bs);
		bs = enc_param(bs, 0, sorts, pars);
		break;
	}
	case TOK_down_cast: {
		/* Down cast from non-trivial base */
		BITSTREAM *ts, *us;
		TYPE c = type_char;
		bs = enc_special(bs, TOK_ptr_to_ptr);
		ts = start_bitstream(NIL(FILE), bs->link);
		ts = enc_alignment(ts, c);
		ts = enc_param(ts, 0, sorts, pars);
		ENC_add_to_ptr(ts);
		ts = enc_special(ts, TOK_ptr_to_ptr);
		us = start_bitstream(NIL(FILE), ts->link);
		us = enc_param(us, 0, sorts, pars);
		us = enc_alignment(us, c);
		us = enc_param(us, 1, sorts, pars);
		ts = enc_bitstream(ts, us);
		ENC_offset_negate(ts);
		ts = enc_special(ts, TOK_extra_offset);
		us = start_bitstream(NIL(FILE), ts->link);
		us = enc_alignment(us, c);
		us = enc_param(us, 2, sorts, pars);
		ts = enc_bitstream(ts, us);
		bs = enc_bitstream(bs, ts);
		break;
	}
	case TOK_destr_cast: {
		BITSTREAM *ts;
		bs = enc_special(bs, TOK_ptr_to_ptr);
		ts = start_bitstream(NIL(FILE), bs->link);
		ts = enc_param(ts, 0, sorts, pars);
		ts = enc_special(ts, TOK_empty_align);
		ts = enc_param(ts, 1, sorts, pars);
		bs = enc_bitstream(bs, ts);
		break;
	}
	case TOK_destr_test: {
		BITSTREAM *ts;
		ENC_pointer_test(bs);
		ENC_OFF(bs);
		bs = enc_ntest(bs, ntest_not_eq);
		bs = enc_param(bs, 1, sorts, pars);
		bs = enc_special(bs, TOK_destr_ptr);
		ts = start_bitstream(NIL(FILE), bs->link);
		ts = enc_param(ts, 0, sorts, pars);
		bs = enc_bitstream(bs, ts);
		ENC_make_null_ptr(bs);
		bs = enc_special(bs, TOK_empty_align);
		break;
	}
	case TOK_except_jump: {
		/* Long jump */
		ENC_long_jump(bs);
		bs = enc_param(bs, 0, sorts, pars);
		bs = enc_param(bs, 1, sorts, pars);
		break;
	}
	case TOK_ptr_code: {
		/* Local label value pointer */
		ENC_pointer(bs);
		ENC_code_alignment(bs);
		s = type_void_star;
		break;
	}
	case TOK_ptr_frame: {
		/* Procedure environment pointer */
		ENC_pointer(bs);
#if (TDF_major >= 4)
		ENC_unite_alignments(bs);
		ENC_locals_alignment(bs);
		ENC_callers_alignment(bs);
		ENC_false(bs);
#else
		ENC_frame_alignment(bs);
#endif
		s = type_void_star;
		break;
	}
	default: {
		FAIL(Unknown special token);
		break;
	}
	}
	enc_tokdef_end(n, bs);
	if (output_all && special_token[t].builtin == 2) {
		string e = ustrlit(special_token[t].name);
		IGNORE capsule_name(n, &e, VAR_token);
	}
	if (output_diag) {
		/* Output token diagnostics */
		IDENTIFIER id = special_token[t].tok;
		if (!IS_NULL_id(id)) {
			enc_diag_token(id, s);
		}
	}
	return;
}


/*
    This routine adds the definition of the token tok to the bitstream bs.
*/

BITSTREAM *
enc_tokdef_body(BITSTREAM *bs, IDENTIFIER id, TOKEN tok)
{
	if (!IS_NULL_tok(tok)) {
		int uc = unreached_code;
		unreached_code = 0;
		switch (TAG_tok(tok)) {
		case tok_exp_tag: {
			EXP e = DEREF_exp(tok_exp_value(tok));
			if (IS_NULL_exp(e)) {
				goto undefined_token;
			}
			bs = enc_exp(bs, e);
			break;
		}
		case tok_stmt_tag: {
			EXP e = DEREF_exp(tok_stmt_value(tok));
			if (IS_NULL_exp(e)) {
				goto undefined_token;
			}
			bs = enc_stmt(bs, e);
			break;
		}
		case tok_nat_tag: {
			NAT n = DEREF_nat(tok_nat_value(tok));
			if (IS_NULL_nat(n)) {
				ENC_computed_nat(bs);
				goto undefined_token;
			}
			bs = enc_nat(bs, n, 0);
			break;
		}
		case tok_snat_tag: {
			NAT n = DEREF_nat(tok_snat_value(tok));
			if (IS_NULL_nat(n)) {
				ENC_computed_signed_nat(bs);
				goto undefined_token;
			}
			bs = enc_snat(bs, n, 0, 0);
			break;
		}
		case tok_type_tag: {
			TYPE t = DEREF_type(tok_type_value(tok));
			BASE_TYPE bt = DEREF_btype(tok_type_kind(tok));
			if (bt & btype_scalar) {
				if (IS_NULL_type(t)) {
					ENC_computed_signed_nat(bs);
					goto undefined_token;
				}
				bs = enc_arith(bs, t, 0);
			} else {
				if (IS_NULL_type(t)) {
					ENC_compound(bs);
					goto undefined_token;
				}
				bs = enc_shape(bs, t);
			}
			break;
		}
		case tok_member_tag: {
			OFFSET off = DEREF_off(tok_member_value(tok));
			if (IS_NULL_off(off)) {
				goto undefined_token;
			}
			bs = enc_offset(bs, off);
			break;
		}
		case tok_proc_tag: {
			TOKEN res = DEREF_tok(tok_proc_res(tok));
			bs = enc_tokdef_body(bs, id, res);
			break;
		}
undefined_token: {
			 /* Output install-time error */
			 EXP e;
			 ERROR err;
			 OPTION opt = option(OPT_token_undef);
			 option(OPT_token_undef) = OPTION_ON;
			 err = ERR_token_undef(id);
			 e = install_error(NIL(LOCATION), err);
			 option(OPT_token_undef) = opt;
			 bs = enc_exp(bs, e);
			 break;
		 }
		default: {
			FAIL(Bad token sort);
			break;
		}
		}
		unreached_code = uc;
	}
	return bs;
}


/*
    This routine adds the application of the token id with arguments
    args to the bitstream bs.
*/

BITSTREAM *
enc_token(BITSTREAM *bs, IDENTIFIER id, LIST(TOKEN)args)
{
	int s = enc_tokdef(id, 0);
	ulong n = unit_no(bs, id, VAR_token, 0);
	bs = enc_apply_token(bs, s);
	ENC_make_tok(bs, n);
	if (IS_NULL_list(args)) {
		ENC_LEN_SMALL(bs, 0);
	} else {
		BITSTREAM *ts = start_bitstream(NIL(FILE), bs->link);
		while (!IS_NULL_list(args)) {
			TOKEN tok = DEREF_tok(HEAD_list(args));
			ts = enc_tokdef_body(ts, id, tok);
			args = TAIL_list(args);
		}
		bs = enc_bitstream(bs, ts);
	}
	return bs;
}


/*
    This routine adds the assembler directive e to the bitstream bs.
*/

BITSTREAM *
enc_asm(BITSTREAM *bs, EXP e)
{
	STRING op = DEREF_str(exp_assembler_op(e));
	unsigned long len = DEREF_ulong(str_simple_len(op));
	if (len) {
		BITSTREAM *ts, *us;
		bs = enc_special(bs, TOK_asm_sequence);
		ts = start_bitstream(NIL(FILE), bs->link);
		ts = enc_special(ts, TOK_asm);
		us = start_bitstream(NIL(FILE), ts->link);
		us = enc_strlit(us, op);
		ts = enc_bitstream(ts, us);
		bs = enc_bitstream(bs, ts);
	} else {
		ENC_make_top(bs);
	}
	return bs;
}


#else /* TDF_OUTPUT */


/*
    This routine is a dummy version of define_special used when TDF
    output is disabled.
*/

void
define_special(int t)
{
	UNUSED(t);
	return;
}


#endif /* TDF_OUTPUT */
