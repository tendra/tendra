/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include <shared/check.h>

#include <utility/config.h>
#include "c_types.h"

#include <utility/ustring.h>
#include <utility/system.h>
#include <utility/error.h>
#include <utility/buffer.h>
#include <utility/debug.h>
#include <utility/print.h>

#include <parse/char.h>
#include <parse/constant.h>
#include <parse/file.h>
#include <parse/hash.h>
#include <parse/lex.h>
#include <parse/literal.h>
#include <parse/symbols.h>

#include <output/tok.h>

#include "ctype_ops.h"
#include "etype_ops.h"
#include "exp_ops.h"
#include "flt_ops.h"
#include "ftype_ops.h"
#include "graph_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "itype_ops.h"
#include "member_ops.h"
#include "nat_ops.h"
#include "nspace_ops.h"
#include "off_ops.h"
#include "str_ops.h"
#include "tok_ops.h"
#include "type_ops.h"
#include "basetype.h"
#include "class.h"
#include "convert.h"
#include "exception.h"
#include "function.h"
#include "label.h"
#include "redeclare.h"
#include "syntax.h"
#include "token.h"


/*
    This buffer is used for the error output.
*/

BUFFER print_buff = NULL_buff;


/*
    A couple of forward function declarations are necessary.
*/

static int print_head(TYPE, int, BUFFER *, int);
static int print_tail(TYPE, BUFFER *, int);


/*
    These flags are used to control the form of the output.
*/

static int print_default_args = 0;
static int print_member_type = 0;
static int print_return_type = 1;
static int print_func_params = 0;
static int print_except = 0;
static int print_func_linkage = 0;
static int print_parent_namespace = 1;
static int print_bitfield_sep = ':';
int print_c_style = LANGUAGE_C;
int print_type_alias = 0;
int print_uniq_anon = 0;
int print_id_desc = 0;


/*
    This routine prints the name of the lexical token t to the buffer bf.
    With all the routines in this file the sp argument is true if a space
    should be printed before the actual text, and the return value is true
    if a space should be printed after it.
*/

int
print_lex(int t, BUFFER *bf, int sp)
{
	string s = token_name(t);
	if (s == NULL) {
		return sp;
	}
	if (sp) {
		bfputc(bf, ' ');
	}
	bfputs(bf, s);
	return 1;
}


/*
    This routine prints the access specifier n to the buffer bf.
*/

int
print_access(DECL_SPEC n, BUFFER *bf, int sp)
{
	int t;
	DECL_SPEC a = (n & dspec_access);
	if (a == dspec_private) {
		t = lex_private;
	} else if (a == dspec_protected) {
		t = lex_protected;
	} else {
		t = lex_public;
	}
	sp = print_lex(t, bf, sp);
	return sp;
}


/*
    This table gives the names of the built-in types.
*/

const char *ntype_name[ORDER_ntype] = {
	"<error>",		/* ntype_none */
	"char",			/* ntype_char */
	"signed char",		/* ntype_schar */
	"unsigned char",	/* ntype_uchar */
	"short",		/* ntype_sshort */
	"unsigned short",	/* ntype_ushort */
	"int",			/* ntype_sint */
	"unsigned int",		/* ntype_uint */
	"long",			/* ntype_slong */
	"unsigned long",	/* ntype_ulong */
	"long long",		/* ntype_sllong */
	"unsigned long long",	/* ntype_ullong */
	"float",		/* ntype_float */
	"double",		/* ntype_double */
	"long double",		/* ntype_ldouble */
	"void",			/* ntype_void */
	"<bottom>",		/* ntype_bottom */
	"bool",			/* ntype_bool */
	"ptrdiff_t",		/* ntype_ptrdiff_t */
	"size_t",		/* ntype_size_t */
	"wchar_t",		/* ntype_wchar_t */
	"..."			/* ntype_ellipsis */
};


/*
    This routine prints the built-in type n to the buffer bf.
*/

int
print_ntype(BUILTIN_TYPE n, BUFFER *bf, int sp)
{
	if (sp) {
		bfputc(bf, ' ');
	}
	bfputs(bf, ustrlit(ntype_name[n]));
	return 1;
}


/*
    This routine prints the base type n to the buffer bf.
*/

int
print_btype(BASE_TYPE n, BUFFER *bf, int sp)
{
	BASE_TYPE key = (n & btype_named);
	if (key) {
		switch (key) {
		case btype_class:  sp = print_lex(lex_class, bf, sp);    break;
		case btype_struct: sp = print_lex(lex_struct, bf, sp);   break;
		case btype_union:  sp = print_lex(lex_union, bf, sp);    break;
		case btype_enum:   sp = print_lex(lex_enum, bf, sp);     break;
		case btype_any:    sp = print_lex(lex_tag_Hcap, bf, sp); break;
		}
	} else {
		if (n & btype_signed) {
			sp = print_lex(lex_signed, bf, sp);
		}
		if (n & btype_unsigned) {
			sp = print_lex(lex_unsigned, bf, sp);
		}
		if (n & btype_short) {
			sp = print_lex(lex_short, bf, sp);
		}
		if (n & btype_long) {
			sp = print_lex(lex_long, bf, sp);
		}
		if (n & btype_long2) {
			sp = print_lex(lex_long, bf, sp);
		}
		if (n & btype_char) {
			sp = print_lex(lex_char, bf, sp);
		}
		if (n & btype_int) {
			sp = print_lex(lex_int, bf, sp);
		}
		if (n & btype_float) {
			sp = print_lex(lex_float, bf, sp);
		}
		if (n & btype_double) {
			sp = print_lex(lex_double, bf, sp);
		}
		if (n & btype_void) {
			sp = print_lex(lex_void, bf, sp);
		}
		if (n & btype_bottom) {
			sp = print_lex(lex_bottom, bf, sp);
		}
		if (n & btype_bool) {
			sp = print_lex(lex_bool, bf, sp);
		}
		if (n & btype_ptrdiff_t) {
			sp = print_lex(lex_ptrdiff_Ht, bf, sp);
		}
		if (n & btype_size_t) {
			sp = print_lex(lex_size_Ht, bf, sp);
		}
		if (n & btype_wchar_t) {
			sp = print_lex(lex_wchar_Ht, bf, sp);
		}
		if (n & btype_ellipsis) {
			sp = print_lex(lex_ellipsis, bf, sp);
		}
		if (n & btype_star) {
			sp = print_lex(lex_star, bf, sp);
		}
	}
	return sp;
}


/*
    This routine prints the const-volatile qualifier n to the buffer bf.
*/

int
print_cv(CV_SPEC n, BUFFER *bf, int sp)
{
	if (n) {
		if (n & cv_const) {
			sp = print_lex(lex_const, bf, sp);
		}
		if (n & cv_volatile) {
			sp = print_lex(lex_volatile, bf, sp);
		}
	}
	return sp;
}


/*
    This routine prints the declaration specifier n to the buffer bf.  The
    C and C++ linkage specifiers are not included.
*/

int
print_dspec(DECL_SPEC n, BUFFER *bf, int sp)
{
	if (n & dspec_typedef) {
		sp = print_lex(lex_typedef, bf, sp);
	}
	if (n & dspec_storage) {
		if (n & dspec_extern) {
			sp = print_lex(lex_extern, bf, sp);
		}
		if (n & dspec_static) {
			sp = print_lex(lex_static, bf, sp);
		}
		if (n & dspec_register) {
			sp = print_lex(lex_register, bf, sp);
		}
		if (n & dspec_auto) {
			sp = print_lex(lex_auto, bf, sp);
		}
		if (n & dspec_mutable) {
			sp = print_lex(lex_mutable, bf, sp);
		}
	}
	if (n & dspec_function) {
		if (n & dspec_explicit) {
			sp = print_lex(lex_explicit, bf, sp);
		}
		if (n & dspec_friend) {
			sp = print_lex(lex_friend, bf, sp);
		}
		if (n & dspec_inline) {
			sp = print_lex(lex_inline, bf, sp);
		}
		if (n & dspec_virtual) {
			sp = print_lex(lex_virtual, bf, sp);
		}
	}
	return sp;
}


/*
    This routine prints the linkage specifier n to the buffer bf.
*/

static int
print_linkage(CV_SPEC n, BUFFER *bf, int sp)
{
	CV_SPEC m = (n & cv_language);
	if (m) {
		if (m != cv_cpp && !print_c_style) {
			string s = linkage_string(dspec_none, m);
			if (sp) {
				bfputc(bf, ' ');
			}
			bfprintf(bf, "extern \"%s\"", s);
			sp = 1;
		}
	}
	return sp;
}


/*
    This routine prints the file location p to the buffer bf.  q gives
    the main location.  If the file names from p and q match then only
    the line number is printed.
*/

int
print_loc(LOCATION *p, LOCATION *q, BUFFER *bf, int sp)
{
	string fn;
	unsigned long ln;
	if (sp) {
		bfputc(bf, ' ');
	}
	if (p == NULL) {
		fn = ustrlit("<unknown>");
		ln = 0;
	} else {
		PTR(POSITION)pa = p->posn;
		if (IS_NULL_ptr(pa)) {
			fn = ustrlit("<unknown>");
		} else {
			fn = DEREF_string(posn_file(pa));
			if (q) {
				/* Check previous location */
				PTR(POSITION)qa = q->posn;
				if (EQ_ptr(qa, pa)) {
					fn = NULL;
				} else if (!IS_NULL_ptr(qa)) {
					string gn = DEREF_string(posn_file(qa));
					if (ustreq(gn, fn)) {
						fn = NULL;
					}
				}
			}
		}
		ln = p->line;
	}
	if (fn) {
		bfprintf(bf, "\"%s\"", fn);
		if (ln) {
			bfprintf(bf, ", line %lu", ln);
		}
	} else {
		bfprintf(bf, "line %lu", ln);
	}
	return 1;
}


/*
    This routine prints the identifier name corresponding to the hash
    table entry p to the buffer bf.
*/

int
print_hashid(HASHID p, int sep, int anon, BUFFER *bf, int sp)
{
	unsigned tag;
	if (IS_NULL_hashid(p)) {
		return sp;
	}
	tag = TAG_hashid(p);
	assert(ORDER_hashid == 7);
	switch (tag) {
	case hashid_name_tag:
	case hashid_ename_tag: {
		/* Simple name */
		string s = DEREF_string(hashid_name_etc_text(p));
		if (sp) {
			bfputc(bf, ' ');
		}
		bfputs(bf, s);
		sp = 1;
		break;
	}
	case hashid_constr_tag:
	case hashid_destr_tag: {
		/* Class destructor name */
		IDENTIFIER tid = DEREF_id(hashid_constr_etc_tid(p));
		if (IS_NULL_id(tid)) {
			/* Unnamed constructor or destructor */
			TYPE t = DEREF_type(hashid_constr_etc_type(p));
			if (sep) {
				IGNORE print_type(t, bf, sp);
				bfprintf(bf, "::");
			} else {
				if (sp)bfputc(bf, ' ');
			}
			if (tag == hashid_destr_tag) {
				bfputc(bf, '~');
			}
			sp = print_type(t, bf, 0);
		} else {
			/* Named constructor or destructor */
			static HASHID lastp = NULL_hashid;
			if (sep && !EQ_hashid(p, lastp)) {
				lastp = p;
				tid = DEREF_id(hashid_id(p));
				sp = print_id_short(tid, qual_none, bf, sp);
				lastp = NULL_hashid;
				break;
			}
			p = DEREF_hashid(id_name(tid));
			if (sp) {
				bfputc(bf, ' ');
			}
			if (sep) {
				IGNORE print_hashid(p, 0, 1, bf, 0);
				bfprintf(bf, "::");
			}
			if (tag == hashid_destr_tag) {
				bfputc(bf, '~');
			}
			sp = print_hashid(p, 0, 1, bf, 0);
		}
		break;
	}
	case hashid_conv_tag: {
		/* Overloaded conversion name */
		int prt = print_return_type;
		TYPE t = DEREF_type(hashid_conv_type(p));
		sp = print_lex(lex_operator, bf, sp);
		print_return_type = 1;
		sp = print_type(t, bf, sp);
		print_return_type = prt;
		break;
	}
	case hashid_op_tag: {
		/* Overloaded operator name */
		int op = DEREF_int(hashid_op_lex(p));
		string s = token_name(op);
		sp = print_lex(lex_operator, bf, sp);
		if (s) {
			int c = (int)*s;
			if (isalpha(c)) {
				bfputc(bf, ' ');
			}
			bfputs(bf, s);
		}
		break;
	}
	case hashid_anon_tag: {
		/* Anonymous identifier */
		if (anon) {
			unsigned long u = DEREF_ulong(hashid_anon_uniq(p));
			if (sp) {
				bfputc(bf, ' ');
			}
			if (print_uniq_anon) {
				bfprintf(bf, "<anon%x.%lu>", uniq_string, u);
			} else {
				bfprintf(bf, "<anon%lu>", u);
			}
			sp = 1;
		}
		break;
	}
	}
	return sp;
}


/*
    This routines prints the short form of the identifier id to the buffer bf.
*/

int
print_id_short(IDENTIFIER id, QUALIFIER qual, BUFFER *bf, int sp)
{
	if (!IS_NULL_id(id)) {
		int sep = 0;
		HASHID p = DEREF_hashid(id_name(id));

		/* Print enclosing namespace name */
		NAMESPACE ns = DEREF_nspace(id_parent(id));
		if (sp) {
			bfputc(bf, ' ');
		}
		if (print_parent_namespace && !print_c_style) {
			if (IS_NULL_nspace(ns)) {
				if (qual == qual_full || qual == qual_top) {
					bfprintf(bf, "::");
				}
				sep = 1;
			} else {
				IGNORE print_nspace(ns, qual, 1, bf, 0);
			}
		}

		/* Print identifier name */
		if (IS_hashid_anon(p)) {
			/* Print anonymous identifier names */
			IDENTIFIER alt = id;
			unsigned tag = TAG_id(id);
			if (tag == id_token_tag) {
				DECL_SPEC ds = DEREF_dspec(id_storage(id));
				if (ds & dspec_auto) {
					alt = DEREF_id(id_token_alt(id));
					tag = id_parameter_tag;
				}
			}
			if (tag == id_parameter_tag) {
				/* Parameter names */
				unsigned long n = 0;
				MEMBER mem = DEREF_member(nspace_last(ns));
				id = DEREF_id(id_alias(id));
				alt = DEREF_id(id_alias(alt));
				while (!IS_NULL_member(mem)) {
					IDENTIFIER mid =
					    DEREF_id(member_id(mem));
					if (!IS_NULL_id(mid)) {
						if (EQ_id(mid, id)) {
							n = 0;
						}
						if (EQ_id(mid, alt)) {
							n = 0;
						}
						n++;
					}
					mem = DEREF_member(member_next(mem));
				}
				bfprintf(bf, "<param%lu>", n);
			} else {
				/* Other identifiers */
				LOCATION loc;
				string fn, fs;
				DEREF_loc(id_loc(id), loc);
				fs = DEREF_string(posn_file(loc.posn));
				fn = ustrrchr(fs, '/');
				fn = (fn ? fn + 1 : fs);
				bfprintf(bf, "(\"%s\":%lu)", fn, loc.line );
			}
		} else {
			/* Print other identifier names */
			IGNORE print_hashid(p, sep, 0, bf, 0);
		}
		sp = 1;
	}
	return sp;
}


/*
    This routines prints the long form of the identifier id to the buffer bf.
*/

int
print_id_long(IDENTIFIER id, QUALIFIER qual, BUFFER *bf, int sp)
{
	if (!IS_NULL_id(id)) {
		int prt = 1;
		int key = 0;
		TYPE t = NULL_type;
		TYPE f = NULL_type;
		TOKEN tok = NULL_tok;
		GRAPH gr = NULL_graph;
		const char *desc = NULL;
		int full = print_id_desc;
		NAMESPACE pns = NULL_nspace;
		LIST(TYPE)p = NULL_list(TYPE);
		switch (TAG_id(id)) {
		case id_keyword_tag:
		case id_iso_keyword_tag: {
			/* Keywords */
			if (full) {
				desc = "keyword";
			}
			break;
		}
		case id_builtin_tag: {
			/* Built-in operators */
			t = DEREF_type(id_builtin_ret(id));
			p = DEREF_list(id_builtin_ptypes(id));
			if (full) {
				desc = "built-in";
			}
			break;
		}
		case id_obj_macro_tag:
		case id_func_macro_tag: {
			/* Macros */
			if (full) {
				desc = "macro";
			}
			break;
		}
		case id_predicate_tag: {
			/* Predicates */
			if (full) {
				desc = "predicate";
			}
			break;
		}
		case id_class_name_tag:
		case id_enum_name_tag: {
			/* Class and enumeration names */
			f = DEREF_type(id_class_name_etc_defn(id));
			key = (full || print_c_style);
			break;
		}
		case id_class_alias_tag:
		case id_enum_alias_tag:
		case id_type_alias_tag: {
			/* Typedef names */
			if (full) {
				t = DEREF_type(id_class_name_etc_defn(id));
				desc = "typedef";
			}
			break;
		}
		case id_nspace_name_tag: {
			/* Namespace names */
			if (full) {
				desc = "namespace";
			}
			break;
		}
		case id_nspace_alias_tag: {
			/* Namespace aliases */
			if (full) {
				desc = "namespace";
				pns = DEREF_nspace(id_nspace_alias_defn(id));
			}
			break;
		}
		case id_variable_tag:
		case id_parameter_tag: {
			/* Object names */
			if (full) {
				DECL_SPEC ds = DEREF_dspec(id_storage(id));
				if (ds & dspec_auto) {
					desc = "auto";
				}
				t = DEREF_type(id_variable_etc_type(id));
			}
			break;
		}
		case id_stat_member_tag: {
			/* Static members */
			if (full) {
				t = DEREF_type(id_stat_member_type(id));
				desc = "static";
			}
			break;
		}
		case id_weak_param_tag: {
			if (full) {
				desc = "auto";
				t = type_sint;
			}
			break;
		}
		case id_function_tag:
		case id_mem_func_tag: {
			/* Function names */
			HASHID nm = DEREF_hashid(id_name(id));
			switch (TAG_hashid(nm)) {
			case hashid_constr_tag:
			case hashid_destr_tag:
			case hashid_conv_tag: {
				/* Inhibit return type */
				prt = 0;
				break;
			}
			}
			t = DEREF_type(id_function_etc_type(id));
			f = DEREF_type(id_function_etc_form(id));
			if (!IS_NULL_type(f) && !IS_type_token(f)) {
				f = NULL_type;
			}
			if (full) {
				DECL_SPEC ds = DEREF_dspec(id_storage(id));
				if (ds & dspec_implicit) {
					desc = "implicit";
				}
			} else {
				if (print_c_style) {
					t = NULL_type;
				}
			}
			break;
		}
		case id_stat_mem_func_tag: {
			/* Static function member names */
			t = DEREF_type(id_stat_mem_func_type(id));
			f = DEREF_type(id_stat_mem_func_form(id));
			if (!IS_NULL_type(f) && !IS_type_token(f)) {
				f = NULL_type;
			}
			if (full) {
				desc = "static";
			} else {
				if (print_c_style) {
					t = NULL_type;
				}
			}
			break;
		}
		case id_member_tag: {
			/* Member names */
			gr = DEREF_graph(id_member_base(id));
			if (full) {
				t = DEREF_type(id_member_type(id));
			}
			break;
		}
		case id_enumerator_tag: {
			/* Enumerator names */
			if (full) {
				desc = "enumerator";
			}
			break;
		}
		case id_label_tag: {
			/* Label names */
			if (full) {
				int op = DEREF_int(id_label_op(id));
				if (op != lex_identifier) {
					/* Print kind of label */
					sp = print_lex(op, bf, sp);
					if (op == lex_case) {
						NAT n = find_case_nat(id);
						sp = print_nat(n, 0, bf, sp);
					}
					return sp;
				}
				desc = "label";
			}
			break;
		}
		case id_token_tag: {
			/* Token names */
			if (full) {
				tok = DEREF_tok(id_token_sort(id));
				desc = "token";
			}
			break;
		}
		}
		if (desc) {
			/* Print description */
			if (sp) {
				bfputc(bf, ' ');
			}
			bfprintf(bf, desc);
			sp = 1;
		}
		if (!IS_NULL_tok(tok)) {
			/* Print token sort */
			sp = print_sort(tok, 0, bf, sp);
		}
		if (!IS_NULL_type(t)) {
			/* Print start of identifier type */
			print_return_type = prt;
			sp = print_head(t, key, bf, sp);
			print_return_type = 1;
		}
		if (IS_NULL_type(f)) {
			if (!IS_NULL_graph(gr)) {
				sp = print_graph(gr, 1, bf, sp);
				print_parent_namespace = 0;
			}
			sp = print_id_short(id, qual, bf, sp);
			print_parent_namespace = 1;
		} else {
			sp = print_head(f, key, bf, sp);
			sp = print_tail(f, bf, sp);
		}
		if (!IS_NULL_type(t)) {
			/* Print end of identifier type */
			print_default_args = 1;
			sp = print_tail(t, bf, sp);
			print_default_args = 0;
		}
		if (!IS_NULL_list(p)) {
			/* Print parameter types */
			sp = print_type_list(p, bf, 1);
		}
		if (!IS_NULL_nspace(pns)) {
			/* Print namespace alias definition */
			sp = print_lex(lex_assign, bf, sp);
			sp = print_nspace(pns, qual_none, 0, bf, sp);
		}
	}
	return sp;
}


/*
    This routines prints the namespace ns to the buffer bf.  The argument
    pre is true if this a prefix to an identifier and false if the namespace
    itself is what is required.
*/

int
print_nspace(NAMESPACE ns, QUALIFIER qual, int pre, BUFFER *bf, int sp)
{
	if (!IS_NULL_nspace(ns)) {
		IDENTIFIER id = DEREF_id(nspace_name(ns));
		switch (TAG_nspace(ns)) {
		case nspace_named_tag:
		case nspace_ctype_tag: {
			/* Named and class namespaces */
			if (sp) {
				bfputc(bf, ' ');
			}
			if (IS_id_class_name(id)) {
				TYPE t = DEREF_type(id_class_name_defn(id));
				if (IS_type_compound(t)) {
					int key = 0;
					CLASS_TYPE ct;
					if (!pre) {
						key = print_c_style;
					}
					ct = DEREF_ctype(type_compound_defn(t));
					IGNORE print_ctype(ct, qual, key, bf,
							   0);
				} else {
					IGNORE print_id_short(id, qual, bf, 0);
				}
			} else {
				IGNORE print_id_short(id, qual, bf, 0);
			}
			if (pre) {
				bfprintf(bf, "::");
			}
			sp = 1;
			break;
		}
		case nspace_unnamed_tag: {
			/* Unnamed namespaces */
			if (sp) {
				bfputc(bf, ' ');
			}
			ns = DEREF_nspace(id_parent(id));
			IGNORE print_nspace(ns, qual, 1, bf, 0);
			if (print_uniq_anon) {
				bfprintf(bf, "<anon%x>", uniq_string);
			} else {
				bfprintf(bf, "<anon>");
			}
			if (pre) {
				bfprintf(bf, "::");
			}
			sp = 1;
			break;
		}
		case nspace_global_tag: {
			/* The global namespace */
			if (!pre || qual == qual_full || qual == qual_top) {
				if (sp) {
					bfputc(bf, ' ');
				}
				bfprintf(bf, "::");
				sp = 1;
			}
			break;
		}
		default : {
			/* Other namespaces */
			if (!pre) {
				sp = print_id_short(id, qual, bf, sp);
			}
			break;
		}
		}
	}
	return sp;
}


/*
    This routines prints the graph gr to the buffer bf.  The argument sep is
    true to indicate that a terminal '::' should be included.
*/

int
print_graph(GRAPH gr, int sep, BUFFER *bf, int sp)
{
	if (!IS_NULL_graph(gr)) {
		CLASS_TYPE ct = DEREF_ctype(graph_head(gr));
		GRAPH gs = DEREF_graph(graph_up(gr));
		if (sp) {
			bfputc(bf, ' ');
			sp = 0;
		}
		if (!IS_NULL_graph(gs)) {
			IGNORE print_graph(gs, 1, bf, 0);
			print_parent_namespace = 0;
		}
		IGNORE print_ctype(ct, qual_none, 0, bf, 0);
		print_parent_namespace = 1;
		if (sep) {
			bfprintf(bf, "::");
		}
	}
	return sp;
}


/*
    This routine prints the preprocessing token p to the buffer bf.  It
    is used not only in the error reporting routines, but also in the
    preprocessing action.
*/

int
print_pptok(PPTOKEN *p, BUFFER *bf, int sp)
{
	int q;
	int t = p->tok;
	if (sp) {
		bfputc(bf, ' ');
	}
	switch (t) {
	case lex_identifier:
	case lex_type_Hname:
	case lex_namespace_Hname:
	case lex_statement_Hname:
identifier_label: {
			  /* Identifiers */
			  HASHID nm = p->pp_data.id.hash;
			  string s = DEREF_string(hashid_name_etc_text(nm));
			  bfputs(bf, s);
			  break;
		  }
	case lex_destructor_Hname: {
		/* Destructor names */
		bfputc(bf, '~');
		goto identifier_label;
	}
	case lex_template_Hid:
	case lex_template_Htype: {
		/* Template names */
		IDENTIFIER id = p->pp_data.tok.id;
		IGNORE print_id_short(id, qual_none, bf, 0);
		break;
	}
	case lex_integer_Hlit: {
		/* Integer and floating point literals */
		string s = p->pp_data.text;
		bfputs(bf, s);
		break;
	}
	case lex_char_Hlit: {
		/* Character literals */
		q = '\'';
string_label: {
		      string s = p->pp_data.str.start;
		      string e = p->pp_data.str.end;
		      bfputc(bf, q);
		      while (s != e) {
			      bfputc(bf,(int)*s);
			      s++;
		      }
		      bfputc(bf, q);
	      }
	      break;
	}
	case lex_wchar_Hlit: {
		/* Wide character literals */
		bfputc(bf, 'L');
		q = '\'';
		goto string_label;
	}
	case lex_string_Hlit: {
		/* String literals */
		q = '"';
		goto string_label;
	}
	case lex_wstring_Hlit: {
		/* Wide string literals */
		bfputc(bf, 'L');
		q = '"';
		goto string_label;
	}
	case lex_integer_Hexp:
	case lex_floating_Hexp:
	case lex_char_Hexp:
	case lex_wchar_Hexp:
	case lex_string_Hexp:
	case lex_wstring_Hexp: {
		/* Literal expressions */
		IGNORE print_exp(p->pp_data.exp, 0, bf, 0);
		break;
	}
	case lex_unknown: {
		/* Unknown characters */
		unsigned long u;
		int ch = CHAR_SIMPLE;
		u = get_multi_char(p->pp_data.buff, &ch);
		if (ch == CHAR_SIMPLE) {
			bfputc(bf,(int)u);
		} else {
			print_char(u, ch, 0, bf);
		}
		break;
	}
	case lex_nested_Hname: {
		/* Nested name qualifier */
		NAMESPACE ns = p->pp_data.ns;
		IGNORE print_nspace(ns, qual_nested, 1, bf, 0);
		break;
	}
	case lex_full_Hname: {
		/* Nested name qualifier */
		NAMESPACE ns = p->pp_data.ns;
		IGNORE print_nspace(ns, qual_full, 1, bf, 0);
		break;
	}
	case lex_nested_Hname_Hstar: {
		/* Nested member qualifier */
		IDENTIFIER id = p->pp_data.id.use;
		IGNORE print_id_short(id, qual_nested, bf, 0);
		bfprintf(bf, "::*");
		break;
	}
	case lex_full_Hname_Hstar: {
		/* Nested member qualifier */
		IDENTIFIER id = p->pp_data.id.use;
		IGNORE print_id_short(id, qual_full, bf, 0);
		bfprintf(bf, "::*");
		break;
	}
	case lex_complex_Hexp:
	case lex_complex_Htype: {
		/* Token applications etc. */
		IDENTIFIER id = p->pp_data.tok.id;
		IGNORE print_id_short(id, qual_none, bf, 0);
		break;
	}
	case lex_macro_Harg: {
		/* Macro parameters */
		HASHID nm = p->pp_data.par.hash;
		string s = DEREF_string(hashid_name_etc_text(nm));
		bfputs(bf, s);
		break;
	}
	default : {
		/* Simple token */
		if (t >= 0) {
			string s = token_name(t);
			bfputs(bf, s);
		} else {
			bfprintf(bf, "<ignore>");
		}
		break;
	}
	}
	return 1;
}


/*
    This prints an integer literal to the buffer bf.  The only difficult case
    is when a large literal will not fit into an unsigned long.  The digits
    need to be printed in reverse order, and it is again quickest to reverse
    the order of the list twice.
*/

int
print_nat(NAT n, int paren, BUFFER *bf, int sp)
{
	if (!IS_NULL_nat(n)) {
		assert(ORDER_nat == 5);
		switch (TAG_nat(n)) {
		case nat_small_tag: {
			/* Small values */
			unsigned v = DEREF_unsigned(nat_small_value(n));
			if (sp) {
				bfputc(bf, ' ');
			}
			bfprintf(bf, "%u", v);
			sp = 1;
			break;
		}
		case nat_large_tag: {
			/* Large values */
			LIST(unsigned)p;
			p = DEREF_list(nat_large_values(n));
			if (sp) {
				bfputc(bf, ' ');
			}
			if (LENGTH_list(p) <= 2) {
				/* Two digit literals will fit into a unsigned
				 * long */
				unsigned long v = get_nat_value(n);
				bfprintf(bf, "%lu", v);
			} else {
				/* Print large literals by scanning through
				 * digits */
				char buff[50];
				const char *fmt = "0x%x";
				LIST(unsigned)q;
				p = REVERSE_list(p);
				q = p;
				while (!IS_NULL_list(q)) {
					unsigned v =
					    DEREF_unsigned(HEAD_list(q));
					sprintf_v(buff, fmt, v);
					bfputs(bf, ustrlit(buff));
					fmt = "%04x";
					q = TAIL_list(q);
				}
				IGNORE REVERSE_list(p);
			}
			sp = 1;
			break;
		}
		case nat_calc_tag: {
			/* Calculated values */
			EXP e = DEREF_exp(nat_calc_value(n));
			while (!IS_NULL_exp(e) && IS_exp_cast(e)) {
				e = DEREF_exp(exp_cast_arg(e));
			}
			sp = print_exp(e, paren, bf, sp);
			break;
		}
		case nat_neg_tag: {
			/* Negative values */
			NAT m = DEREF_nat(nat_neg_arg(n));
			if (sp) {
				bfputc(bf, ' ');
			}
			bfputc(bf, '-');
			IGNORE print_nat(m, 1, bf, 0);
			break;
		}
		case nat_token_tag: {
			IDENTIFIER id = DEREF_id(nat_token_tok(n));
			LIST(TOKEN)args = DEREF_list(nat_token_args(n));
			sp = print_token(id, qual_none, args, bf, sp);
			break;
		}
		}
	}
	return sp;
}


/*
    This routine prints a floating-point literal to the buffer bf.
*/

int
print_flt(FLOAT n, BUFFER *bf, int sp)
{
	if (!IS_NULL_flt(n)) {
		string i = DEREF_string(flt_simple_int_part(n));
		string d = DEREF_string(flt_simple_frac_part(n));
		NAT e = DEREF_nat(flt_simple_exponent(n));
		if (sp) {
			bfputc(bf, ' ');
		}
		bfprintf(bf, "%s.%s", i, d);
		if (!is_zero_nat(e)) {
			bfputc(bf, 'e');
			IGNORE print_nat(e, 0, bf, 0);
		}
		sp = 1;
	}
	return sp;
}


/*
    This routine prints the character c to the buffer bf as a string
    character of type ch enclosed by the quote character q.
*/

void
print_char(unsigned long c, int ch, int q, BUFFER *bf)
{
	char buff[20];
	if (ch == CHAR_SIMPLE) {
		switch (c) {
		case char_alert:     bfprintf(bf, "\\a"); break;
		case char_backspace: bfprintf(bf, "\\b"); break;
		case char_form_feed: bfprintf(bf, "\\f"); break;
		case char_newline:   bfprintf(bf, "\\n"); break;
		case char_return:    bfprintf(bf, "\\r"); break;
		case char_tab:       bfprintf(bf, "\\t"); break;
		case char_vert_tab:  bfprintf(bf, "\\v"); break;

		case char_backslash:
		case char_question: {
			if (q) {
				bfputc(bf, '\\');
			}
			bfputc(bf,(int)c);
			break;
		}

		case char_quote:
		case char_single_quote: {
			int a = (int)c;
			if (a == q) {
				bfputc(bf, '\\');
			}
			bfputc(bf, a);
			break;
		}

		default : {
			int a = (int)c;
			if (isprint(a)) {
				bfputc(bf, a);
			} else {
				sprintf_v(buff, "\\%03lo", c );
				bfputs(bf, ustrlit(buff));
			}
			break;
		}
		}
	} else {
		const char *fmt;
		switch (ch) {
		case CHAR_OCTAL: fmt = "\\%03lo";  break;
		case CHAR_UNI4:  fmt = "\\u%04lx"; break;
		case CHAR_UNI8:  fmt = "\\U%08lx"; break;
		default:         fmt = "\\x%lx";   break;
		}
		sprintf_v(buff, fmt, c);
		bfputs(bf, ustrlit(buff));
	}
	return;
}


/*
    This routine prints a string or character literal to the buffer bf.
*/

int
print_str(STRING s, BUFFER *bf, int sp)
{
	string text;
	int q = '"';
	unsigned kind;
	unsigned long i, len;

	if (IS_NULL_str(s)) {
		return sp;
	}

	/* Print the opening quote */
	if (sp) {
		bfputc(bf, ' ');
	}
	kind = DEREF_unsigned(str_simple_kind(s));
	if (kind & STRING_CHAR) {
		q = '\'';
	}
	if (kind & STRING_WIDE) {
		bfputc(bf, 'L');
	}

	/* Print the string text */
	text = DEREF_string(str_simple_text(s));
	len = DEREF_ulong(str_simple_len(s));
	bfputc(bf, q);
	if (kind & STRING_MULTI) {
		/* Multi-byte strings */
		for (i = 0; i < len; i++) {
			int ch = CHAR_SIMPLE;
			unsigned long c = get_multi_char(text, &ch);
			print_char(c, ch, q, bf);
			text += MULTI_WIDTH;
		}
	} else {
		/* Simple strings */
		for (i = 0; i < len; i++) {
			unsigned long c = (unsigned long)text[i];
			print_char(c, CHAR_SIMPLE, q, bf);
		}
	}
	bfputc(bf, q);
	return 1;
}


/*
    This routine prints an expression to the buffer bf.
*/

int
print_exp(EXP e, int paren, BUFFER *bf, int sp)
{
	if (!IS_NULL_exp(e)) {
		switch (TAG_exp(e)) {
		case exp_identifier_tag:
		case exp_member_tag:
		case exp_ambiguous_tag:
		case exp_undeclared_tag: {
			IDENTIFIER id = DEREF_id(exp_identifier_etc_id(e));
			QUALIFIER q = DEREF_qual(exp_identifier_etc_qual(e));
			q &= qual_explicit;
			sp = print_id_short(id, q, bf, sp);
			break;
		}
		case exp_int_lit_tag: {
			NAT n = DEREF_nat(exp_int_lit_nat(e));
			sp = print_nat(n, paren, bf, sp);
			break;
		}
		case exp_float_lit_tag: {
			FLOAT flt = DEREF_flt(exp_float_lit_flt(e));
			sp = print_flt(flt, bf, sp);
			break;
		}
		case exp_char_lit_tag: {
			STRING s = DEREF_str(exp_char_lit_str(e));
			sp = print_str(s, bf, sp);
			break;
		}
		case exp_string_lit_tag: {
			STRING s = DEREF_str(exp_string_lit_str(e));
			sp = print_str(s, bf, sp);
			break;
		}
		case exp_null_tag:
		case exp_zero_tag:
		case exp_value_tag: {
			if (sp) {
				bfputc(bf, ' ');
			}
			bfputc(bf, '0');
			break;
		}
		case exp_contents_tag: {
			EXP a = DEREF_exp(exp_contents_ptr(e));
			sp = print_exp(a, 0, bf, sp);
			break;
		}
		case exp_token_tag: {
			IDENTIFIER id = DEREF_id(exp_token_tok(e));
			LIST(TOKEN)args = DEREF_list(exp_token_args(e));
			sp = print_token(id, qual_none, args, bf, sp);
			break;
		}
		default: {
			static unsigned long exp_no = 0;
#ifndef NDEBUG
			if (debugging) {
				/* Debug expression printing routine */
				sp = print_exp_aux(e, paren, bf, sp);
				break;
			}
#endif
			if (sp) {
				bfputc(bf, ' ');
			}
			bfprintf(bf, "<exp%lu>", ++exp_no);
			sp = 1;
			break;
		}
		}
	}
	return sp;
}


/*
    This routine prints the value of the token tok to the buffer bf.
*/

int
print_tok_value(TOKEN tok, BUFFER *bf, int sp)
{
	if (!IS_NULL_tok(tok)) {
		assert(ORDER_tok == 10);
		switch (TAG_tok(tok)) {
		case tok_exp_tag: {
			EXP e = DEREF_exp(tok_exp_value(tok));
			sp = print_exp(e, 0, bf, sp);
			break;
		}
		case tok_stmt_tag: {
			EXP e = DEREF_exp(tok_stmt_value(tok));
			sp = print_exp(e, 0, bf, sp);
			break;
		}
		case tok_nat_tag:
		case tok_snat_tag: {
			NAT n = DEREF_nat(tok_nat_etc_value(tok));
			sp = print_nat(n, 0, bf, sp);
			break;
		}
		case tok_type_tag: {
			TYPE t = DEREF_type(tok_type_value(tok));
			sp = print_type(t, bf, sp);
			break;
		}
		case tok_member_tag: {
			OFFSET off = DEREF_off(tok_member_value(tok));
			sp = print_offset(off, bf, sp);
			break;
		}
		case tok_class_tag: {
			IDENTIFIER cid = DEREF_id(tok_class_value(tok));
			sp = print_id_short(cid, qual_none, bf, sp);
			break;
		}
		default : {
			if (sp)bfputc(bf, ' ');
			bfprintf(bf, "<arg>");
			sp = 1;
			break;
		}
		}
	}
	return sp;
}


/*
    This routine prints the token application 'id ( args )' or the template
    application 'id < args >' to the buffer bf.
*/

int
print_token(IDENTIFIER id, QUALIFIER qual, LIST(TOKEN)args, BUFFER *bf, int sp)
{
	int open_bracket = 0;
	int close_bracket = 0;
	if (IS_id_token(id)) {
		/* Token application */
		TOKEN tok = DEREF_tok(id_token_sort(id));
		unsigned tag = TAG_tok(tok);
		IDENTIFIER alt = DEREF_id(id_token_alt(id));
		if (!IS_NULL_id(alt)) {
			id = alt;
		}
		if (tag == tok_proc_tag || !IS_NULL_list(args)) {
			open_bracket = '(';
			close_bracket = ')';
		} else if (tag == tok_class_tag) {
			open_bracket = '<';
			close_bracket = '>';
		}
	} else {
		/* Template application */
		open_bracket = '<';
		close_bracket = '>';
	}
	sp = print_id_short(id, qual, bf, sp);
	if (open_bracket) {
		int first = 1;
		bfputc(bf, ' ');
		bfputc(bf, open_bracket);
		while (!IS_NULL_list(args)) {
			TOKEN ptok = DEREF_tok(HEAD_list(args));
			if (!IS_NULL_tok(ptok)) {
				if (!first) {
					bfputc(bf, ',');
				}
				IGNORE print_tok_value(ptok, bf, 1);
				first = 0;
			}
			args = TAIL_list(args);
		}
		if (!first) {
			bfputc(bf, ' ');
		}
		bfputc(bf, close_bracket);
		sp = 1;
	}
	return sp;
}


/*
    This routine prints the token sort tok to the buffer bf.
*/

int
print_sort(TOKEN tok, int arg, BUFFER *bf, int sp)
{
	unsigned tag;
	if (IS_NULL_tok(tok)) {
		return sp;
	}
	tag = TAG_tok(tok);
	assert(ORDER_tok == 10);
	switch (tag) {
	case tok_exp_tag: {
		/* Expression tokens */
		sp = print_lex(lex_exp_Hcap, bf, sp);
		if (!arg) {
			TYPE t = DEREF_type(tok_exp_type(tok));
			CV_SPEC cv = DEREF_cv(type_qual(t));
			if (cv & cv_lvalue) {
				IGNORE print_lex(lex_lvalue, bf, sp);
			} else {
				int c = DEREF_int(tok_exp_constant(tok));
				if (c) {
					IGNORE print_lex(lex_const, bf, sp);
				}
			}
			bfprintf(bf, " :");
			IGNORE print_type(t, bf, 1);
			bfprintf(bf, " :");
			sp = 1;
		}
		break;
	}

	case tok_nat_tag: {
		/* Integer constant tokens */
		if (arg) {
			sp = print_lex(lex_exp_Hcap, bf, sp);
		} else {
			sp = print_lex(lex_nat_Hcap, bf, sp);
		}
		break;
	}

	case tok_snat_tag: {
		/* Integer constant tokens */
		if (arg) {
			sp = print_lex(lex_exp_Hcap, bf, sp);
		} else {
			sp = print_lex(lex_int_Hcap, bf, sp);
		}
		break;
	}

	case tok_stmt_tag: {
		/* Statement tokens */
		sp = print_lex(lex_stmt_Hcap, bf, sp);
		break;
	}

	case tok_type_tag: {
		/* Type tokens */
		if (arg) {
			sp = print_lex(lex_type_Hcap, bf, sp);
		} else {
			BASE_TYPE bt = DEREF_btype(tok_type_kind(tok));
			int key = type_token_key(bt);
			if (key == lex_signed || key == lex_unsigned) {
				sp = print_lex(lex_variety_Hcap, bf, sp);
			}
			sp = print_lex(key, bf, sp);
		}
		break;
	}

	case tok_func_tag: {
		/* Function tokens */
		if (arg) {
			sp = print_lex(lex_proc_Hcap, bf, sp);
		} else {
			TYPE t = DEREF_type(tok_func_type(tok));
			IGNORE print_lex(lex_func_Hcap, bf, sp);
			IGNORE print_type(t, bf, 1);
			bfprintf(bf, " :");
			sp = 1;
		}
		break;
	}

	case tok_member_tag: {
		/* Member tokens */
		TYPE s = DEREF_type(tok_member_of(tok));
		IGNORE print_lex(lex_member_Hcap, bf, sp);
		if (!arg) {
			TYPE t = DEREF_type(tok_member_type(tok));
			print_bitfield_sep = '%';
			IGNORE print_type(t, bf, 1);
			print_bitfield_sep = ':';
			bfprintf(bf, " :");
		}
		IGNORE print_type(s, bf, 1);
		bfprintf(bf, " :");
		sp = 1;
		break;
	}

	case tok_class_tag: {
		/* Template class tokens */
		TYPE t = DEREF_type(tok_class_type(tok));
		while (!IS_NULL_type(t) && IS_type_templ(t)) {
			TOKEN sort = DEREF_tok(type_templ_sort(t));
			sp = print_sort(sort, 0, bf, sp);
			t = DEREF_type(type_templ_defn(t));
		}
		sp = print_lex(lex_class, bf, sp);
		break;
	}

	case tok_proc_tag: {
		/* Procedure tokens */
		TOKEN res;
		int simple = 0;
		LIST(IDENTIFIER)p, q;
		sp = print_lex(lex_proc_Hcap, bf, sp);
		if (arg) {
			break;
		}
		res = DEREF_tok(tok_proc_res(tok));
		p = DEREF_list(tok_proc_pids(tok));
		q = DEREF_list(tok_proc_bids(tok));
		if (EQ_list(p, q)) {
			simple = 1;
		}
		if (simple) {
			bfprintf(bf, " (");
		} else {
			bfprintf(bf, " {");
		}
		sp = 0;
		while (!IS_NULL_list(q)) {
			IDENTIFIER id = DEREF_id(HEAD_list(q));
			if (!IS_NULL_id(id)) {
				TOKEN par = DEREF_tok(id_token_sort(id));
				if (sp) {
					bfputc(bf, ',');
				}
				IGNORE print_sort(par, 0, bf, 1);
				if (!simple) {
					HASHID nm = DEREF_hashid(id_name(id));
					IGNORE print_hashid(nm, 0, 0, bf, 1);
				}
				sp = 1;
			}
			q = TAIL_list(q);
		}
		if (simple) {
			if (sp) {
				bfputc(bf, ' ');
			}
			bfputc(bf, ')');
		} else {
			bfprintf(bf, " |");
			sp = 0;
			while (!IS_NULL_list(p)) {
				IDENTIFIER id = DEREF_id(HEAD_list(p));
				if (!IS_NULL_id(id)) {
					if (sp) {
						bfputc(bf, ',');
					}
					if (IS_id_token(id)) {
						/* Simple token parameter */
						HASHID nm =
						    DEREF_hashid(id_name(id));
						TOKEN par = DEREF_tok(id_token_sort(id));
						IGNORE print_sort(par, 1, bf,
								  1);
						IGNORE print_hashid(nm, 0, 0,
								    bf, 1);
					} else {
						/* Complex type parameter */
						TYPE r;
						r = DEREF_type(id_class_name_etc_defn(id));
						IGNORE print_lex(lex_type_Hcap,
								 bf, 1);
						IGNORE print_type(r, bf, 1);
					}
					sp = 1;
				}
				p = TAIL_list(p);
			}
			bfprintf(bf, " }");
		}
		sp = print_sort(res, 0, bf, 1);
		break;
	}

	case tok_templ_tag: {
		/* Template tokens */
		LIST(TOKEN)q;
		LIST(IDENTIFIER)p;
		DECL_SPEC ex = DEREF_dspec(tok_templ_usage(tok));
		NAMESPACE ns = DEREF_nspace(tok_templ_pars(tok));
		if (ex & dspec_extern) {
			/* Exported templates */
			sp = print_lex(lex_export, bf, sp);
		}
		IGNORE print_lex(lex_template, bf, sp);
		if (IS_NULL_nspace(ns)) {
			sp = 1;
			break;
		}
		p = DEREF_list(tok_templ_pids(tok));
		q = DEREF_list(tok_templ_dargs(tok));
		bfprintf(bf, " <");
		sp = 0;
		while (!IS_NULL_list(p)) {
			TOKEN val = NULL_tok;
			IDENTIFIER id = DEREF_id(HEAD_list(p));
			HASHID nm = DEREF_hashid(id_name(id));
			if (!IS_NULL_list(q)) {
				val = DEREF_tok(HEAD_list(q));
				q = TAIL_list(q);
			}
			tok = DEREF_tok(id_token_sort(id));
			tag = TAG_tok(tok);
			if (tag == tok_exp_tag) {
				TYPE t = DEREF_type(tok_exp_type(tok));
				int sp2 = print_head(t, 0, bf, 1);
				sp2 = print_hashid(nm, 0, 0, bf, sp2);
				IGNORE print_tail(t, bf, sp2);
			} else if (tag == tok_type_tag) {
				IGNORE print_lex(lex_class, bf, 1);
				IGNORE print_hashid(nm, 0, 0, bf, 1);
			} else {
				IGNORE print_sort(tok, 0, bf, 1);
				IGNORE print_hashid(nm, 0, 0, bf, 1);
			}
			if (!IS_NULL_tok(val)) {
				bfprintf(bf, " =");
				IGNORE print_tok_value(val, bf, 1);
			}
			p = TAIL_list(p);
			if (!IS_NULL_list(p)) {
				bfputc(bf, ',');
			}
			sp = 1;
		}
		if (sp) {
			bfputc(bf, ' ');
		}
		bfputc(bf, '>');
		sp = 1;
		break;
	}
	}
	return sp;
}


/*
    This routine prints an integral type to the buffer bf.  Note that the
    standard full forms, such as 'signed short int', are translated into
    shorter forms, such as 'short'.
*/

int
print_itype(INT_TYPE t, BUFFER *bf, int sp)
{
	if (!IS_NULL_itype(t)) {
		assert(ORDER_itype == 6);
		switch (TAG_itype(t)) {
		case itype_basic_tag: {
			BUILTIN_TYPE n = DEREF_ntype(itype_basic_no(t));
			sp = print_ntype(n, bf, sp);
			break;
		}
		case itype_bitfield_tag: {
			BASE_TYPE bt = DEREF_btype(itype_bitfield_rep(t));
			if (bt & btype_named) {
				TYPE s = DEREF_type(itype_bitfield_sub(t));
				sp = print_type(s, bf, sp);
			} else {
				sp = print_btype(bt, bf, sp);
			}
			break;
		}
		case itype_promote_tag: {
			INT_TYPE s = DEREF_itype(itype_promote_arg(t));
			if (sp) {
				bfputc(bf, ' ');
			}
			bfprintf(bf, "%s ( ", special_name(TOK_promote));
			IGNORE print_itype(s, bf, 0);
			bfprintf(bf, " )");
			sp = 1;
			break;
		}
		case itype_arith_tag: {
			INT_TYPE s1 = DEREF_itype(itype_arith_arg1(t));
			INT_TYPE s2 = DEREF_itype(itype_arith_arg2(t));
			if (sp) {
				bfputc(bf, ' ');
			}
			bfprintf(bf, "%s ( ", special_name(TOK_arith_type));
			IGNORE print_itype(s1, bf, 0);
			bfprintf(bf, ", ");
			IGNORE print_itype(s2, bf, 0);
			bfprintf(bf, " )");
			sp = 1;
			break;
		}
		case itype_literal_tag: {
			NAT n = DEREF_nat(itype_literal_nat(t));
			int tok = DEREF_int(itype_literal_spec(t));
			if (sp) {
				bfputc(bf, ' ');
			}
			bfprintf(bf, "%s ( ", special_name(tok));
			IGNORE print_nat(n, 0, bf, 0);
			bfprintf(bf, " )");
			sp = 1;
			break;
		}
		case itype_token_tag: {
			BUILTIN_TYPE n = DEREF_ntype(itype_unprom(t));
			if (n == ntype_none || n == ntype_ellipsis) {
				IDENTIFIER id;
				LIST(TOKEN)args;
				id = DEREF_id(itype_token_tok(t));
				args = DEREF_list(itype_token_args(t));
				sp = print_token(id, qual_none, args, bf, sp);
			} else {
				if (sp)bfputc(bf, ' ');
				bfprintf(bf, "%s ( ",
					 special_name(TOK_promote));
				IGNORE print_ntype(n, bf, 0);
				bfprintf(bf, " )");
				sp = 1;
			}
			break;
		}
		}
	}
	return sp;
}


/*
    This routine prints a floating-point type to the buffer bf.
*/

int
print_ftype(FLOAT_TYPE t, BUFFER *bf, int sp)
{
	if (!IS_NULL_ftype(t)) {
		assert(ORDER_ftype == 4);
		switch (TAG_ftype(t)) {
		case ftype_basic_tag: {
			BUILTIN_TYPE n = DEREF_ntype(ftype_basic_no(t));
			sp = print_ntype(n, bf, sp);
			break;
		}
		case ftype_arg_promote_tag: {
			FLOAT_TYPE s = DEREF_ftype(ftype_arg_promote_arg(t));
			if (sp) {
				bfputc(bf, ' ');
			}
			bfprintf(bf, "%s ( ", special_name(TOK_promote));
			IGNORE print_ftype(s, bf, 0);
			bfprintf(bf, " )");
			sp = 1;
			break;
		}
		case ftype_arith_tag: {
			FLOAT_TYPE s1 = DEREF_ftype(ftype_arith_arg1(t));
			FLOAT_TYPE s2 = DEREF_ftype(ftype_arith_arg2(t));
			if (sp) {
				bfputc(bf, ' ');
			}
			bfprintf(bf, "%s ( ", special_name(TOK_arith_type));
			IGNORE print_ftype(s1, bf, 0);
			bfprintf(bf, ", ");
			IGNORE print_ftype(s2, bf, 0);
			bfprintf(bf, " )");
			sp = 1;
			break;
		}
		case ftype_token_tag: {
			IDENTIFIER id = DEREF_id(ftype_token_tok(t));
			LIST(TOKEN)args = DEREF_list(ftype_token_args(t));
			sp = print_token(id, qual_none, args, bf, sp);
			break;
		}
		}
	}
	return sp;
}


/*
    This routines prints the class type ct to the buffer bf.
*/

int
print_ctype(CLASS_TYPE ct, QUALIFIER qual, int key, BUFFER *bf, int sp)
{
	if (!IS_NULL_ctype(ct)) {
		TYPE t = DEREF_type(ctype_form(ct));
		IDENTIFIER id = DEREF_id(ctype_name(ct));
		if (key && IS_id_class_name(id)) {
			BASE_TYPE bt = find_class_key(ct);
			sp = print_btype(bt, bf, sp);
		}
		if (!IS_NULL_type(t) && IS_type_token(t)) {
			IDENTIFIER tid = DEREF_id(type_token_tok(t));
			LIST(TOKEN)args = DEREF_list(type_token_args(t));
			sp = print_token(tid, qual, args, bf, sp);
		} else {
			sp = print_id_short(id, qual, bf, sp);
		}
	}
	return sp;
}


/*
    This routines prints the enumeration type et to the buffer bf.
*/

int
print_etype(ENUM_TYPE et, int key, BUFFER *bf, int sp)
{
	if (!IS_NULL_etype(et)) {
		IDENTIFIER id = DEREF_id(etype_name(et));
		if (key && IS_id_enum_name(id)) {
			sp = print_lex(lex_enum, bf, sp);
		}
		sp = print_id_short(id, qual_none, bf, sp);
	}
	return sp;
}


/*
    This routine tested whether the type t is a tailed type, that is an
    array, bitfield, or function type.
*/

static int
is_tailed_type(TYPE t)
{
	if (!IS_NULL_type(t)) {
		IDENTIFIER tid = DEREF_id(type_name(t));
		if (IS_NULL_id(tid) || !print_type_alias) {
			switch (TAG_type(t)) {
			case type_func_tag:
			case type_array_tag:
			case type_bitfield_tag: {
				return 1;
			}
			case type_templ_tag: {
				TYPE s = DEREF_type(type_templ_defn(t));
				return is_tailed_type(s);
			}
			}
		}
	}
	return 0;
}


/*
    This routine prints the head of a type (i.e. the main part and any
    pointer or reference components) to the buffer bf.
*/

static int
print_head(TYPE t, int key, BUFFER *bf, int sp)
{
	if (IS_NULL_type(t)) {
		static unsigned long type_no = 0;
		if (sp) {
			bfputc(bf, ' ');
		}
		bfprintf(bf, "<type%lu>", ++type_no);
		sp = 1;
	} else {
		CV_SPEC qual = DEREF_cv(type_qual(t));
		IDENTIFIER tid = DEREF_id(type_name(t));
		qual &= cv_qual;
		if (!IS_NULL_id(tid) && print_type_alias) {
			switch (TAG_id(tid)) {
			case id_class_alias_tag:
			case id_enum_alias_tag:
			case id_type_alias_tag: {
				/* Print type aliases */
				if (!IS_type_pre(t)) {
					sp = print_cv(qual, bf, sp);
					sp = print_id_short(tid, qual_none, bf,
							    sp);
					return sp;
				}
				break;
			}
			}
		}
		assert(ORDER_type == 18);
		switch (TAG_type(t)) {
		case type_pre_tag: {
			/* Pre-types */
			BASE_TYPE bt = DEREF_btype(type_pre_rep(t));
			BASE_TYPE kt = (bt & btype_named);
			sp = print_cv(qual, bf, sp);
			if (kt) {
				if (kt == btype_alias) {
					sp = print_id_short(tid, qual_none, bf,
							    sp);
				} else {
					HASHID nm = DEREF_hashid(id_name(tid));
					sp = print_btype(kt, bf, sp);
					sp = print_hashid(nm, 0, 0, bf, sp);
				}
			} else {
				sp = print_btype(bt, bf, sp);
			}
			break;
		}
		case type_integer_tag: {
			/* Integral types */
			INT_TYPE it = DEREF_itype(type_integer_rep(t));
			sp = print_cv(qual, bf, sp);
			sp = print_itype(it, bf, sp);
			break;
		}
		case type_floating_tag: {
			/* Floating-point types */
			FLOAT_TYPE ft = DEREF_ftype(type_floating_rep(t));
			sp = print_cv(qual, bf, sp);
			sp = print_ftype(ft, bf, sp);
			break;
		}
		case type_top_tag: {
			/* Top type */
			sp = print_cv(qual, bf, sp);
			sp = print_ntype(ntype_void, bf, sp);
			break;
		}
		case type_bottom_tag: {
			/* Bottom type */
			sp = print_cv(qual, bf, sp);
			sp = print_ntype(ntype_bottom, bf, sp);
			break;
		}
		case type_ptr_tag: {
			/* Pointer type */
			TYPE s = DEREF_type(type_ptr_sub(t));
			sp = print_head(s, key, bf, sp);
			if (is_tailed_type(s)) {
				bfprintf(bf, " ( *");
			} else {
				if (sp) {
					bfputc(bf, ' ');
				}
				bfputc(bf, '*');
			}
			sp = (qual ? print_cv(qual, bf, 1) : 0);
			break;
		}
		case type_ref_tag: {
			/* Reference type */
			TYPE s = DEREF_type(type_ref_sub(t));
			sp = print_head(s, key, bf, sp);
			if (is_tailed_type(s)) {
				bfprintf(bf, " ( &");
			} else {
				if (sp) {
					bfputc(bf, ' ');
				}
				bfputc(bf, '&');
			}
			sp = (qual ? print_cv(qual, bf, 1) : 0);
			break;
		}
		case type_ptr_mem_tag: {
			/* Pointer to member type */
			TYPE s = DEREF_type(type_ptr_mem_sub(t));
			CLASS_TYPE ct = DEREF_ctype(type_ptr_mem_of(t));
			sp = print_head(s, key, bf, sp);
			if (is_tailed_type(s)) {
				bfprintf(bf, " ( ");
				sp = 0;
			}
			IGNORE print_ctype(ct, qual_none, 0, bf, sp);
			bfprintf(bf, "::*");
			sp = (qual ? print_cv(qual, bf, 1) : 0);
			break;
		}
		case type_func_tag: {
			/* Function type */
			qual = DEREF_cv(type_func_mqual(t));
			if (qual && print_func_linkage) {
				sp = print_linkage(qual, bf, sp);
			}
			if (print_return_type) {
				TYPE r = DEREF_type(type_func_ret(t));
				if (!IS_NULL_type(r)) {
					sp = print_head(r, 0, bf, sp);
				}
			}
			break;
		}
		case type_array_tag: {
			/* Array type */
			TYPE s = DEREF_type(type_array_sub(t));
			sp = print_head(s, key, bf, sp);
			break;
		}
		case type_bitfield_tag: {
			/* Bitfield type */
			INT_TYPE it = DEREF_itype(type_bitfield_defn(t));
			sp = print_cv(qual, bf, sp);
			sp = print_itype(it, bf, sp);
			break;
		}
		case type_compound_tag: {
			/* Class type */
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
			sp = print_cv(qual, bf, sp);
			sp = print_ctype(ct, qual_none, key, bf, sp);
			break;
		}
		case type_enumerate_tag: {
			/* Enumeration type */
			ENUM_TYPE et = DEREF_etype(type_enumerate_defn(t));
			sp = print_cv(qual, bf, sp);
			sp = print_etype(et, key, bf, sp);
			break;
		}
		case type_token_tag: {
			/* Tokenised type */
			IDENTIFIER id = DEREF_id(type_token_tok(t));
			LIST(TOKEN)args = DEREF_list(type_token_args(t));
			sp = print_cv(qual, bf, sp);
			sp = print_token(id, qual_none, args, bf, sp);
			break;
		}
		case type_templ_tag: {
			/* Template type */
			TYPE s = DEREF_type(type_templ_defn(t));
			TOKEN tok = DEREF_tok(type_templ_sort(t));
			sp = print_sort(tok, 0, bf, sp);
			sp = print_cv(qual, bf, sp);
			sp = print_head(s, 1, bf, sp);
			break;
		}
		case type_instance_tag: {
			/* Instance type */
			IDENTIFIER id = DEREF_id(type_name(t));
			sp = print_id_short(id, qual_none, bf, sp);
			break;
		}
		default : {
			/* Error type */
			sp = print_cv(qual, bf, sp);
			if (sp) {
				bfputc(bf, ' ');
			}
			bfprintf(bf, "<error_type>");
			sp = 1;
			break;
		}
		}
	}
	return sp;
}


/*
    This routine prints the tail of a type (i.e. any array, bitfield or
    function components) to the buffer bf.
*/

static int
print_tail(TYPE t, BUFFER *bf, int sp)
{
	if (!IS_NULL_type(t)) {
		IDENTIFIER tid = DEREF_id(type_name(t));
		if (!IS_NULL_id(tid) && print_type_alias) {
			return sp;
		}
		switch (TAG_type(t)) {
		case type_ptr_tag:
		case type_ref_tag: {
			/* Pointer and reference types */
			TYPE s = DEREF_type(type_ptr_etc_sub(t));
			if (is_tailed_type(s)) {
				bfprintf(bf, " )");
			}
			sp = print_tail(s, bf, sp);
			break;
		}
		case type_ptr_mem_tag: {
			/* Pointer to member type */
			TYPE s = DEREF_type(type_ptr_mem_sub(t));
			if (is_tailed_type(s)) {
				bfprintf(bf, " )");
			}
			sp = print_tail(s, bf, sp);
			break;
		}
		case type_func_tag: {
			/* Function type */
			int prt = print_return_type;
			int ell = DEREF_int(type_func_ellipsis(t));
			CV_SPEC qual = DEREF_cv(type_func_mqual(t));
			LIST(TYPE)p = DEREF_list(type_func_ptypes(t));
			LIST(IDENTIFIER)q = DEREF_list(type_func_pids(t));
			LIST(TYPE)ex = DEREF_list(type_func_except(t));
			sp = 0;
			if (print_member_type) {
				/* Print member parameter types */
				p = DEREF_list(type_func_mtypes(t));
			}
			if (ell & FUNC_WEAK) {
				/* Weak function prototype */
				bfprintf(bf, " WEAK");
			}
			bfprintf(bf, " (");
			if (IS_NULL_list(p) && !(ell & FUNC_ELLIPSIS)) {
				/* There are no parameters */
				if (!(ell & FUNC_NO_PARAMS) && print_c_style) {
					bfprintf(bf, " void");
					sp = 1;
				}
			} else {
				/* Print parameters */
				int pars = print_func_params;
				int dargs = print_default_args;
				if (LENGTH_list(p) != LENGTH_list(q)) {
					dargs = 0;
				}
				print_return_type = 1;
				while (!IS_NULL_list(p)) {
					TYPE s = DEREF_type(HEAD_list(p));
					if (ell & FUNC_PARAMS) {
						s = unpromote_type(s);
					}
					IGNORE print_type(s, bf, 1);
					if (dargs) {
						/* Print default argument */
						IDENTIFIER id =
						    DEREF_id(HEAD_list(q));
						EXP e = DEREF_exp(id_parameter_init(id));
						if (pars) {
							HASHID nm = DEREF_hashid(id_name(id));
							IGNORE print_hashid(nm, 0, 0, bf, 1);
						}
						if (!IS_NULL_exp(e)) {
							bfprintf(bf, " = ");
							IGNORE print_exp(e, 0, bf, 0);
						}
						q = TAIL_list(q);
					}
					p = TAIL_list(p);
					if (!IS_NULL_list(p)) {
						bfputc(bf, ',');
					} else if (ell & FUNC_ELLIPSIS) {
						bfputc(bf, ',');
					}
					sp = 1;
				}
				if (ell & FUNC_ELLIPSIS) {
					bfprintf(bf, " ...");
					sp = 1;
				}
				print_return_type = prt;
			}
			if (sp) {
				bfputc(bf, ' ');
			}
			bfputc(bf, ')');
			sp = print_cv(qual, bf, 1);
			if (prt) {
				TYPE r = DEREF_type(type_func_ret(t));
				if (!IS_NULL_type(r)) {
					sp = print_tail(r, bf, sp);
				}
			}
			if (!EQ_list(ex, univ_type_set) && print_except) {
				/* Print exception specifier */
				sp = print_lex(lex_throw, bf, sp);
				sp = print_type_list(ex, bf, sp);
			}
			break;
		}
		case type_array_tag: {
			/* Array type */
			TYPE s = DEREF_type(type_array_sub(t));
			NAT n = DEREF_nat(type_array_size(t));
			bfprintf(bf, " [");
			IGNORE print_nat(n, 0, bf, 0);
			bfprintf(bf, "]");
			sp = print_tail(s, bf, 1);
			break;
		}
		case type_bitfield_tag: {
			/* Bitfield type */
			INT_TYPE it = DEREF_itype(type_bitfield_defn(t));
			NAT n = DEREF_nat(itype_bitfield_size(it));
			bfputc(bf, ' ');
			bfputc(bf, print_bitfield_sep);
			IGNORE print_nat(n, 0, bf, 1);
			break;
		}
		case type_templ_tag: {
			/* Template type */
			TYPE s = DEREF_type(type_templ_defn(t));
			sp = print_tail(s, bf, sp);
			break;
		}
		}
	}
	return sp;
}


/*
    This routine prints the type t to the buffer bf.  Note that this is in
    two passes - the first prints the head of the type, comprising the
    base type and any pointer or reference qualifiers, while the second
    prints the tail of the type, comprising any array or function qualifiers.
*/

int
print_type(TYPE t, BUFFER *bf, int sp)
{
	sp = print_head(t, print_c_style, bf, sp);
	sp = print_tail(t, bf, sp);
	return sp;
}


/*
    This routine prints the list of types p, enclosed in brackets, to the
    buffer bf.
*/

int
print_type_list(LIST(TYPE)p, BUFFER *bf, int sp)
{
	if (sp)bfputc(bf, ' ');
	bfputc(bf, '(');
	if (!IS_NULL_list(p)) {
		for (;;) {
			TYPE t = DEREF_type(HEAD_list(p));
			IGNORE print_type(t, bf, 1);
			p = TAIL_list(p);
			if (IS_NULL_list(p)) {
				break;
			}
			bfputc(bf, ',');
		}
		bfputc(bf, ' ');
	}
	bfputc(bf, ')');
	return 1;
}


/*
    This routine prints an offset to the buffer bf.
*/

int
print_offset(OFFSET off, BUFFER *bf, int sp)
{
	if (!IS_NULL_off(off)) {
		switch (TAG_off(off)) {
		case off_base_tag: {
			GRAPH gr = DEREF_graph(off_base_graph(off));
			sp = print_graph(gr, 0, bf, sp);
			break;
		}
		case off_deriv_tag: {
			GRAPH gr = DEREF_graph(off_deriv_graph(off));
			sp = print_graph(gr, 0, bf, sp);
			break;
		}
		case off_member_tag: {
			IDENTIFIER id = DEREF_id(off_member_id(off));
			sp = print_id_short(id, qual_none, bf, sp);
			break;
		}
		case off_token_tag: {
			IDENTIFIER id = DEREF_id(off_token_tok(off));
			LIST(TOKEN)args = DEREF_list(off_token_args(off));
			sp = print_token(id, qual_none, args, bf, sp);
			break;
		}
		default: {
			static unsigned long off_no = 0;
#ifndef NDEBUG
			if (debugging) {
				/* Debug offset printing routine */
				sp = print_offset_aux(off, bf, sp);
				break;
			}
#endif
			if (sp) {
				bfputc(bf, ' ');
			}
			bfprintf(bf, "<off%lu>", ++off_no);
			sp = 1;
			break;
		}
		}
	}
	return sp;
}


/*
    This routine checks whether the start of line n lies within the
    current file buffer.  If so it returns a pointer to the start of
    the line.  m gives the line number of the current position.
*/

static string
find_buffer_line(unsigned long n, unsigned long m)
{
	string p = input_posn - 1;
	if (n <= m) {
		/* Scan backwards */
		while (p >= input_start) {
			character c = *(p--);
			if (c == char_newline) {
				if (n == m) {
					return p + 2;
				}
				m--;
			}
		}
		if (m == 1) {
			/* Allow falling off start */
			return input_start;
		}
	} else {
		while (p < input_end) {
			character c = *(p++);
			if (c == char_newline) {
				if (n == m) {
					return p;
				}
				m++;
			}
		}
		if (p == input_eof) {
			/* Allow falling off end */
			return p;
		}
	}
	return NULL;
}


/*
    This routine checks whether the n lines following line ln of file fn
    lie within the input buffer.  If so it returns the position of the
    first line within the buffer.
*/

static string
find_buffer_loc(string fn, unsigned long ln, unsigned long n)
{
	if (input_start && !bad_crt_loc) {
		PTR(POSITION)pm = crt_loc.posn;
		if (!IS_NULL_ptr(pm)) {
			string fm = DEREF_string(posn_input(pm));
			if (ustreq(fn, fm)) {
				unsigned long om = DEREF_ulong(posn_offset(pm));
				unsigned long lm = crt_loc.line - om;
				string p = find_buffer_line(ln, lm);
				if (p) {
					string q = find_buffer_line(ln + n, lm);
					if (q) {
						return p;
					}
				}
			}
		}
	}
	return NULL;
}


/*
    This routine prints a number of lines from the input buffer centred
    on the location loc to the file f.  If loc does not correspond to a
    position within the current buffer then no text is output.
*/

void
print_source(LOCATION *loc, int lines, int full, const char *pre, FILE *f)
{
	PTR(POSITION)pn = loc->posn;
	if (lines > 0 && !IS_NULL_ptr(pn)) {
		string p;
		int nl = 0;
		FILE *g = NULL;
		const char *mark = "!!!!";
		unsigned long n = (unsigned long)lines;
		unsigned long b = n / 2;
		string fn = DEREF_string(posn_input(pn));
		unsigned long on = DEREF_ulong(posn_offset(pn));
		unsigned long ln = loc->line - on;
		unsigned long cn = loc->column;
		unsigned long lc = ln;
		unsigned long cc = 0;
		if (ln <= b) {
			ln = 1;
		} else {
			ln -= b;
		}

		/* Find start of source */
		p = find_buffer_loc(fn, ln, n);
		if (p == NULL) {
			g = fopen(strlit(fn), "r");
			if (g) {
				/* Skip to correct line in file */
				unsigned long lm = 1;
				while (lm != ln) {
					int c = fgetc(g);
					if (c == EOF) {
						fclose_v(g);
						g = NULL;
						break;
					}
					if (c == '\n')lm++;
				}
			}
		}

		/* Print source */
		if (full) {
			if (pre) {
				fputs_v(pre, f);
			}
			fn = DEREF_string(posn_file(pn));
			fprintf_v(f, "FILE: %s\n", strlit(fn));
		}
		while (n) {
			int c;
			if (nl == 0) {
				if (pre) {
					fputs_v(pre, f);
				}
				if (full) {
					fprintf_v(f, "%lu:\t", ln + on);
				}
				nl = 1;
			}
			if (ln == lc && cn == cc) {
				fputs_v(mark, f);
				mark = NULL;
			}
			if (p) {
				/* Read from buffer */
				if (p >= input_end) {
					break;
				}
				c = (int)*(p++);
			} else if (g) {
				/* Read from file */
				c = fgetc(g);
				if (c == EOF) {
					break;
				}
			} else {
				break;
			}
			if (c == char_newline) {
				/* Newline characters */
				if (ln == lc && mark) {
					fputs_v(mark, f);
					mark = NULL;
				}
				if (--n == 0) {
					break;
				}
				nl = 0;
				ln++;
				cc = 0;
			} else {
				cc++;
			}
			fputc_v((int)c, f);
		}
		if (mark) {
			fputs_v(mark, f);
			nl = 1;
		}
		if (nl) {
			fputc_v('\n', f);
		}
		if (g) {
			fclose_v(g);
		}
	}
	return;
}
