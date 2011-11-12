/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <limits.h>

#include "config.h"

#include "system.h"
#include "version.h"
#include "c_types.h"
#include "err_ext.h"
#include "ctype_ops.h"
#include "etype_ops.h"
#include "exp_ops.h"
#include "ftype_ops.h"
#include "graph_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "itype_ops.h"
#include "nat_ops.h"
#include "nspace_ops.h"
#include "tok_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "basetype.h"
#include "buffer.h"
#include "char.h"
#include "constant.h"
#include "convert.h"
#include "dump.h"
#include "exception.h"
#include "file.h"
#include "function.h"
#include "lex.h"
#include "literal.h"
#include "macro.h"
#include "mangle.h"
#include "print.h"
#include "statement.h"
#include "token.h"
#include "ustring.h"
#include "xalloc.h"


/*
    DUMP FILE OPTIONS

    These variables give the various dump file options.
*/

int do_dump = 0;
int do_error = 0;
int do_header = 0;
int do_keyword = 0;
int do_local = 0;
int do_macro = 0;
int do_scope = 0;
int do_string = 0;
int do_usage = 0;


/*
    DUMP FILE VARIABLES

    These variables give the dump file and the associated dump buffer.
*/

static FILE *dump_file = NULL;
static BUFFER dump_buff_rep = NULL_buff;
static BUFFER *dump_buff = &dump_buff_rep;


/*
    DUMP BUFFER TO FILE

    This routine adds the contents of the dump buffer to the dump file.
*/

static void
dump_string(void)
{
	FILE *f = dump_file;
	BUFFER *bf = dump_buff;
	string s = bf->start;
	size_t n = (size_t)(bf->posn - s);
	fprintf_v(f, "&%lu<",(unsigned long)n);
	if (n) {
		IGNORE fwrite((gen_ptr)s, sizeof(character), n, f);
		bf->posn = s;
	}
	fputc_v('>', f);
	return;
}


/*
    FORWARD DECLARATIONS

    The dump routines defined in this module are defined recursively
    so a couple of forward declarations are required.
*/

static void dump_id(IDENTIFIER);
static void dump_type(TYPE);
static void dump_tok_appl(IDENTIFIER, LIST(TOKEN));
static void dump_nat(NAT, int);


/*
    DUMP FLAGS

    The flag dump_implicit can be set to true to indicate that the
    following declaration or definition is actually implicit.  The flag
    dump_anon_class can be set to inhibit type definitions which name
    anonymous classes being output twice.
*/

int dump_implicit = 0;
int dump_template = 0;
int dump_anon_class = 0;


/*
    FIND AN IDENTIFIER KEY

    This routine finds the key corresponding to the identifier id.
    This is a sequence of characters giving the type of identifier.
*/

static const char *
dump_key(IDENTIFIER id, int def)
{
	const char *key = NULL;
	if (do_dump && !IS_NULL_id(id)) {
		switch (TAG_id(id)) {
		case id_keyword_tag:
		case id_iso_keyword_tag: {
			/* Keywords */
			key = "K";
			break;
		}
		case id_obj_macro_tag: {
			/* Object-like macros */
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			if (ds & dspec_builtin) {
				key = "MB";
			} else {
				key = "MO";
			}
			break;
		}
		case id_func_macro_tag: {
			/* Function-like macros */
			key = "MF";
			break;
		}
		case id_builtin_tag: {
			/* Built-in functions */
			key = "FB";
			break;
		}
		case id_class_name_tag: {
			/* Classes, structures and unions */
			CLASS_TYPE ct;
			CLASS_INFO ci;
			TYPE t = DEREF_type(id_class_name_defn(id));
			while (IS_type_templ(t)) {
				t = DEREF_type(type_templ_defn(t));
			}
			ct = DEREF_ctype(type_compound_defn(t));
			ci = DEREF_cinfo(ctype_info(ct));
			if (ci & cinfo_union) {
				key = "TU";
			} else if (ci & cinfo_struct) {
				key = "TS";
			} else {
				key = "TC";
			}
			break;
		}
		case id_enum_name_tag: {
			/* Enumerations */
			key = "TE";
			break;
		}
		case id_class_alias_tag:
		case id_enum_alias_tag:
		case id_type_alias_tag: {
			/* Type aliases */
			if (dump_anon_class) {
				dump_anon_class = 0;
			} else {
				key = "TA";
			}
			break;
		}
		case id_nspace_name_tag: {
			/* Namespaces */
			key = "NN";
			break;
		}
		case id_nspace_alias_tag: {
			/* Namespace aliases */
			key = "NA";
			break;
		}
		case id_variable_tag: {
			/* Variables */
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			if (ds & dspec_auto) {
				if (do_local) {
					key = "VA";
				}
			} else if (ds & dspec_static) {
				key = "VS";
			} else {
				key = "VE";
			}
			break;
		}
		case id_parameter_tag:
		case id_weak_param_tag: {
			/* Function parameters */
			if (def && do_local) {
				key = "VP";
			}
			break;
		}
		case id_function_tag: {
			/* Functions */
			static char f[10];
			char *fp = f;
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			*(fp++) = 'F';
			if (ds & dspec_static) {
				*(fp++) = 'S';
			} else {
				*(fp++) = 'E';
			}
			if (ds & dspec_c) {
				*(fp++) = 'C';
			}
			if (ds & dspec_inline) {
				*(fp++) = 'I';
			}
			*fp = 0;
			key = f;
			break;
		}
		case id_mem_func_tag: {
			/* Member functions */
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			if (!(ds & dspec_trivial)) {
				if (ds & dspec_virtual) {
					key = "CV";
				} else {
					key = "CF";
				}
			}
			break;
		}
		case id_stat_mem_func_tag: {
			/* Static member functions */
			key = "CS";
			break;
		}
		case id_stat_member_tag: {
			/* Static data members */
			key = "CD";
			break;
		}
		case id_member_tag: {
			/* Data members */
			key = "CM";
			break;
		}
		case id_enumerator_tag: {
			/* Enumerators */
			key = "E";
			break;
		}
		case id_label_tag: {
			/* Labels */
			key = "L";
			break;
		}
		case id_token_tag: {
			/* Tokens */
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			if (ds & dspec_auto) {
				if (ds & dspec_template) {
					key = "XT";
				} else {
					key = "XP";
				}
			} else {
				TOKEN tok = DEREF_tok(id_token_sort(id));
				if (!IS_NULL_tok(tok) && IS_tok_proc(tok)) {
					key = "XF";
				} else {
					key = "XO";
				}
			}
			break;
		}
		}
	}
	return key;
}


/*
    DUMP A LEXICAL TOKEN

    This routine adds the lexical token t to the dump file.
*/

static void
dump_lex(int t)
{
	FILE *f = dump_file;
	string s = token_name(t);
	if (s) {
		unsigned n = (unsigned)ustrlen(s);
		if (n > 100 || ustrchr(s, '>')) {
			fprintf_v(f, "&%u", n);
		}
		fprintf_v(f, "<%s>", strlit(s));
	} else {
		fputs_v("<>", f);
	}
	return;
}


/*
    DUMP A HASH TABLE ENTRY

    This routine adds the hash table entry nm to the dump file.
*/

static void
dump_hashid(HASHID nm)
{
	FILE *f = dump_file;
	if (IS_NULL_hashid(nm)) {
		fputs_v("<>", f);
		return;
	}
	switch (TAG_hashid(nm)) {
	case hashid_name_tag:
	case hashid_ename_tag: {
		/* Simple identifiers */
		string s = DEREF_string(hashid_name_etc_text(nm));
		unsigned n = (unsigned)ustrlen(s);
		if (n > 100 || ustrchr(s, '>')) {
			fprintf_v(f, "&%u", n);
		}
		fprintf_v(f, "<%s>", strlit(s));
		break;
	}
	case hashid_constr_tag: {
		/* Constructor names */
		TYPE t = DEREF_type(hashid_constr_type(nm));
		fputc_v('C', f);
		dump_type(t);
		break;
	}
	case hashid_destr_tag: {
		/* Destructor names */
		TYPE t = DEREF_type(hashid_destr_type(nm));
		fputc_v('D', f);
		dump_type(t);
		break;
	}
	case hashid_conv_tag: {
		/* Conversion function names */
		TYPE t = DEREF_type(hashid_conv_type(nm));
		fputc_v('T', f);
		dump_type(t);
		break;
	}
	case hashid_op_tag: {
		/* Overloaded operator names */
		int t = DEREF_int(hashid_op_lex(nm));
		fputc_v('O', f);
		dump_lex(t);
		break;
	}
	default : {
		/* Other names */
		fputs_v("<>", f);
		break;
	}
	}
	return;
}


/*
    DUMP A NAMESPACE

    This routine adds the namespace ns to the dump file.  The current
    declaration block is taken into account in blk is true.
*/

static void
dump_nspace(NAMESPACE ns, int blk)
{
	if (!IS_NULL_nspace(ns)) {
		if (blk) {
			LIST(IDENTIFIER)s;
			s = LIST_stack(DEREF_stack(nspace_set(ns)));
			if (!IS_NULL_list(s)) {
				/* Allow for declaration blocks */
				IDENTIFIER id = DEREF_id(HEAD_list(s));
				dump_id(id);
				return;
			}
		}
		if (!IS_nspace_global(ns)) {
			ulong n = DEREF_ulong(nspace_dump(ns));
			if (n == LINK_NONE) {
				IDENTIFIER id = DEREF_id(nspace_name(ns));
				if (!IS_NULL_id(id)) {
					/* Use namespace name */
					dump_id(id);
					n = DEREF_ulong(id_dump(id));
					COPY_ulong(nspace_dump(ns), n);
					return;
				}
			} else {
				/* Already assigned value */
				fprintf_v(dump_file, "%lu", n);
				return;
			}
		}
	}
	fputs_v("*", dump_file);
	return;
}


/*
    DUMP AN ACCESS SPECIFIER

    This routine adds the access specifier acc to the dump file.
*/

static void
dump_access(DECL_SPEC acc)
{
	DECL_SPEC ds = (acc & dspec_access);
	if (ds == dspec_private) {
		fputc_v('P', dump_file);
	} else if (ds == dspec_protected) {
		fputc_v('B', dump_file);
	}
	return;
}


/*
    IDENTIFIER DUMP NUMBER

    Each identifier dumped is assigned a number in a sequence given
    by this variable.  The zero value stands for the null identifier.
*/

ulong dump_id_next = 1;


/*
    DUMP AN IDENTIFIER

    This routine adds the identifier id to the dump file.
*/

static void
dump_id(IDENTIFIER id)
{
	if (IS_NULL_id(id)) {
		fputs_v("0", dump_file);
	} else {
		ulong n = DEREF_ulong(id_dump(id));
		if (n == LINK_NONE || (n & LINK_EXTERN)) {
			FILE *f = dump_file;
			HASHID nm = DEREF_hashid(id_name(id));
			NAMESPACE ns = DEREF_nspace(id_parent(id));
			DECL_SPEC acc = DEREF_dspec(id_storage(id));
			if (n == LINK_NONE) {
				/* Allocate new number */
				n = dump_id_next++;
			} else {
				/* Use number from spec file */
				n &= ~LINK_EXTERN;
			}
			COPY_ulong(id_dump(id), n);
			fprintf_v(f, "%lu = ", n);
			dump_hashid(nm);
			fputc_v('\t', f);
			dump_access(acc);
			dump_nspace(ns, 1);
		} else {
			fprintf_v(dump_file, "%lu", n);
		}
	}
	return;
}


/*
    LAST DUMP LOCATION

    When dumping locations the previous location is stored in these
    variables and only items which have changed are output.
*/

static unsigned long last_ln = 0;
static unsigned long last_cn = 0;
static string last_file = NULL;
static string last_input = NULL;
static PTR(POSITION)last_posn = NULL_ptr(POSITION);


/*
    DUMP A LOCATION

    This routine adds the location loc to the dump file.
*/

static void
dump_loc(LOCATION *loc)
{
	FILE *f = dump_file;
	unsigned long ln = loc->line;
	unsigned long cn = loc->column;
	PTR(POSITION)posn = loc->posn;
	if (EQ_ptr(posn, last_posn)) {
		/* Same file information as previously */
		if (ln == last_ln) {
			if (cn == last_cn) {
				fputs_v("*", f);
			} else {
				fprintf_v(f, "%lu\t*", cn);
				last_cn = cn;
			}
		} else {
			fprintf_v(f, "%lu\t%lu\t*", cn, ln );
			last_cn = cn;
			last_ln = ln;
		}
	} else {
		/* Different file information */
		string file = DEREF_string(posn_file(posn));
		string input = DEREF_string(posn_input(posn));
		unsigned long off = DEREF_ulong(posn_offset(posn));
		fprintf_v(f, "%lu\t%lu\t%lu\t", cn, ln, ln - off );
		if (ustreq(file, last_file) && ustreq(input, last_input)) {
			/* File names unchanged */
			fputc_v('*', f);
		} else {
			unsigned n = (unsigned)ustrlen(file);
			fprintf_v(f, "&%u<%s>\t", n, strlit(file));
			if (ustreq(file, input)) {
				/* Current and actual files match */
				fputc_v('*', f);
			} else {
				/* Different current and actual files */
				n = (unsigned)ustrlen(input);
				fprintf_v(f, "&%u<%s>", n, strlit(input));
			}
			last_input = input;
			last_file = file;
		}
		last_posn = posn;
		last_cn = cn;
		last_ln = ln;
	}
	return;
}


/*
    DUMP AN EXPRESSION

    This routine adds the expression e to the dump file.
*/

static void
dump_exp(EXP e)
{
	if (!IS_NULL_exp(e)) {
		switch (TAG_exp(e)) {
		case exp_int_lit_tag: {
			/* Integer literals */
			NAT n = DEREF_nat(exp_int_lit_nat(e));
			dump_nat(n, 0);
			return;
		}
		case exp_token_tag: {
			/* Tokenised expressions */
			IDENTIFIER id = DEREF_id(exp_token_tok(e));
			LIST(TOKEN)args = DEREF_list(exp_token_args(e));
			dump_tok_appl(id, args);
			return;
		}
		}
	}
	IGNORE print_exp(e, 0, dump_buff, 0);
	dump_string();
	return;
}


/*
    DUMP AN OFFSET

    This routine adds the offset off to the dump file.
*/

static void
dump_off(OFFSET off)
{
	IGNORE print_offset(off, dump_buff, 0);
	dump_string();
	return;
}


/*
    DUMP AN INTEGER CONSTANT

    This routine adds the integer constant n to the dump file.
*/

static void
dump_nat(NAT n, int neg)
{
	if (!IS_NULL_nat(n)) {
		FILE *f = dump_file;
		ASSERT(ORDER_nat == 5);
		switch (TAG_nat(n)) {
		case nat_small_tag: {
			/* Small literals */
			unsigned v = DEREF_unsigned(nat_small_value(n));
			int s = (neg ? '-' : '+');
			fputc_v(s, f);
			fprintf_v(f, "%u", v);
			break;
		}
		case nat_large_tag: {
			/* Large literals */
			unsigned long v = get_nat_value(n);
			int s = (neg ? '-' : '+');
			fputc_v(s, f);
			fprintf_v(f, "%lu", v);
			break;
		}
		case nat_neg_tag: {
			/* Negated literals */
			NAT m = DEREF_nat(nat_neg_arg(n));
			dump_nat(m, !neg);
			break;
		}
		case nat_calc_tag: {
			/* Calculated literals */
			EXP e = DEREF_exp(nat_calc_value(n));
			dump_exp(e);
			break;
		}
		case nat_token_tag: {
			/* Tokenised literals */
			IDENTIFIER id = DEREF_id(nat_token_tok(n));
			LIST(TOKEN)args = DEREF_list(nat_token_args(n));
			dump_tok_appl(id, args);
			break;
		}
		}
	}
	return;
}


/*
    DUMP A LIST OF TOKEN PARAMETERS

    This routine adds the list of token parameters pids to the dump file.
*/

static void
dump_params(LIST(IDENTIFIER)pids)
{
	int started = 0;
	FILE *f = dump_file;
	while (!IS_NULL_list(pids)) {
		IDENTIFIER pid = DEREF_id(HEAD_list(pids));
		if (!IS_NULL_id(pid)) {
			if (IS_id_token(pid)) {
				pid = DEREF_id(id_token_alt(pid));
			}
			if (started) {
				fputc_v(MANGLE_comma, f);
			}
			dump_id(pid);
			started = 1;
		}
		pids = TAIL_list(pids);
	}
	return;
}


/*
    DUMP A TOKEN SORT

    This routine adds the token sort tok to the dump file.
*/

static void
dump_sort(TOKEN tok)
{
	FILE *f = dump_file;
	ASSERT(ORDER_tok == 10);
	switch (TAG_tok(tok)) {
	case tok_exp_tag: {
		/* Expression tokens */
		TYPE t = DEREF_type(tok_exp_type(tok));
		int c = DEREF_int(tok_exp_constant(tok));
		if (c) {
			fputs_v("ZEC", f);
		} else {
			CV_SPEC cv = DEREF_cv(type_qual(t));
			if (cv & cv_lvalue) {
				fputs_v("ZEL", f);
			} else {
				fputs_v("ZER", f);
			}
		}
		dump_type(t);
		break;
	}
	case tok_stmt_tag: {
		/* Statement tokens */
		fputs_v("ZS", f);
		break;
	}
	case tok_nat_tag: {
		/* Integer constant tokens */
		fputs_v("ZN", f);
		break;
	}
	case tok_snat_tag: {
		/* Integer constant tokens */
		fputs_v("ZI", f);
		break;
	}
	case tok_type_tag: {
		/* Type tokens */
		int c;
		BASE_TYPE bt = DEREF_btype(tok_type_kind(tok));
		if (bt & btype_float) {
			if (bt & btype_int) {
				c = 'A';
			} else {
				c = 'F';
			}
		} else if (bt & btype_int) {
			c = 'I';
		} else if (bt & btype_class) {
			c = 'S';
		} else if (bt & btype_struct) {
			c = 'S';
		} else if (bt & btype_union) {
			c = 'U';
		} else {
			c = 'O';
		}
		fputs_v("ZT", f);
		fputc_v(c, f);
		break;
	}
	case tok_func_tag: {
		/* Function tokens */
		TYPE t = DEREF_type(tok_func_type(tok));
		fputs_v("ZF", f);
		dump_type(t);
		break;
	}
	case tok_member_tag: {
		/* Member tokens */
		TYPE t = DEREF_type(tok_member_type(tok));
		TYPE s = DEREF_type(tok_member_of(tok));
		fputs_v("ZM", f);
		dump_type(t);
		fputc_v(MANGLE_colon, f);
		dump_type(s);
		break;
	}
	case tok_class_tag: {
		/* Template parameter tokens */
		TYPE t = DEREF_type(tok_class_type(tok));
		TOKEN sort = DEREF_tok(type_templ_sort(t));
		fputs_v("ZT", f);
		dump_sort(sort);
		break;
	}
	case tok_proc_tag: {
		/* Procedure tokens */
		TOKEN res = DEREF_tok(tok_proc_res(tok));
		LIST(IDENTIFIER)bids = DEREF_list(tok_proc_bids(tok));
		LIST(IDENTIFIER)pids = DEREF_list(tok_proc_pids(tok));
		if (EQ_list(bids, pids)) {
			fputs_v("ZPS", f);
			dump_params(bids);
		} else {
			fputs_v("ZPG", f);
			dump_params(bids);
			fputs_v(";", f);
			dump_params(pids);
		}
		fputc_v(MANGLE_colon, f);
		dump_sort(res);
		break;
	}
	case tok_templ_tag: {
		/* Template tokens */
		LIST(IDENTIFIER)pids = DEREF_list(tok_templ_pids(tok));
		fputc_v(MANGLE_template, f);
		dump_params(pids);
		fputc_v(MANGLE_colon, f);
		break;
	}
	}
	return;
}


/*
    DUMP AN INTEGRAL TYPE

    This routine adds the integral type it to the dump file.  Note that
    for this and the other type dumping routines the representation
    chosen bears a marked resemblance to the C++ name mangling scheme,
    and uses the same MANGLE_* macros.  This is primarily to avoid having
    to think up two different forms.
*/

static void
dump_itype(INT_TYPE it)
{
	FILE *f = dump_file;
	ASSERT(ORDER_itype == 6);
	switch (TAG_itype(it)) {
	case itype_basic_tag: {
		/* Basic integral types */
		BUILTIN_TYPE n = DEREF_ntype(itype_basic_no(it));
		fputs_v(mangle_ntype[n], f);
		break;
	}
	case itype_bitfield_tag: {
		/* Bitfield types */
		NAT n = DEREF_nat(itype_bitfield_size(it));
		TYPE s = DEREF_type(itype_bitfield_sub(it));
		fputc_v(MANGLE_bitfield, f);
		dump_nat(n, 0);
		fputc_v(MANGLE_colon, f);
		dump_type(s);
		break;
	}
	case itype_promote_tag: {
		/* Promotion types */
		INT_TYPE is = DEREF_itype(itype_promote_arg(it));
		fputc_v(MANGLE_promote, f);
		dump_itype(is);
		break;
	}
	case itype_arith_tag: {
		/* Arithmetic types */
		INT_TYPE is = DEREF_itype(itype_arith_arg1(it));
		INT_TYPE ir = DEREF_itype(itype_arith_arg2(it));
		fputc_v(MANGLE_arith, f);
		dump_itype(is);
		fputc_v(MANGLE_colon, f);
		dump_itype(ir);
		break;
	}
	case itype_literal_tag: {
		/* Literal types */
		NAT n = DEREF_nat(itype_literal_nat(it));
		string s = mangle_literal(it);
		fputs_v(strlit(s), f);
		dump_nat(n, 0);
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
			dump_tok_appl(id, args);
		} else {
			fputc_v(MANGLE_promote, f);
			fputs_v(mangle_ntype[n], f);
		}
		break;
	}
	}
	return;
}


/*
    DUMP A FLOATING POINT TYPE

    This routine adds the floating point type ft to the dump file.
*/

static void
dump_ftype(FLOAT_TYPE ft)
{
	FILE *f = dump_file;
	ASSERT(ORDER_ftype == 4);
	switch (TAG_ftype(ft)) {
	case ftype_basic_tag: {
		/* Basic floating types */
		BUILTIN_TYPE n = DEREF_ntype(ftype_basic_no(ft));
		fputs_v(mangle_ntype[n], f);
		break;
	}
	case ftype_arg_promote_tag: {
		/* Promotion types */
		FLOAT_TYPE fs = DEREF_ftype(ftype_arg_promote_arg(ft));
		fputc_v(MANGLE_promote, f);
		dump_ftype(fs);
		break;
	}
	case ftype_arith_tag: {
		/* Arithmetic types */
		FLOAT_TYPE fs = DEREF_ftype(ftype_arith_arg1(ft));
		FLOAT_TYPE fr = DEREF_ftype(ftype_arith_arg2(ft));
		fputc_v(MANGLE_arith, f);
		dump_ftype(fs);
		fputc_v(MANGLE_colon, f);
		dump_ftype(fr);
		break;
	}
	case ftype_token_tag: {
		/* Tokenised types */
		IDENTIFIER id = DEREF_id(ftype_token_tok(ft));
		LIST(TOKEN)args = DEREF_list(ftype_token_args(ft));
		dump_tok_appl(id, args);
		break;
	}
	}
	return;
}


/*
    DUMP A CLASS TYPE

    This routine adds the class type ct to the dump file.
*/

static void
dump_ctype(CLASS_TYPE ct)
{
	IDENTIFIER cid = DEREF_id(ctype_name(ct));
	dump_id(cid);
	return;
}


/*
    DUMP AN ENUMERATION TYPE

    This routine adds the enumeration type et to the dump file.
*/

static void
dump_etype(ENUM_TYPE et)
{
	IDENTIFIER eid = DEREF_id(etype_name(et));
	dump_id(eid);
	return;
}


/*
    DUMP A CONST-VOLATILE QUALIFIER

    This routine adds the const-volatile qualifier cv to the dump file.
*/

static void
dump_cv(CV_SPEC cv)
{
	if (cv & cv_const) {
		fputc_v(MANGLE_const, dump_file);
	}
	if (cv & cv_volatile) {
		fputc_v(MANGLE_volatile, dump_file);
	}
	return;
}


/*
    DUMP A LIST OF TYPES

    This routine adds the list of types p to the dump file.
*/

static void
dump_type_list(LIST(TYPE)p, int ell, int started)
{
	while (!IS_NULL_list(p)) {
		TYPE t = DEREF_type(HEAD_list(p));
		if (!IS_NULL_type(t)) {
			if (started) {
				fputc_v(MANGLE_comma, dump_file);
			}
			if (ell & FUNC_PARAMS) {
				t = unpromote_type(t);
			}
			dump_type(t);
			started = 1;
		}
		p = TAIL_list(p);
	}
	return;
}


/*
    DUMP A TYPE

    This routine adds the type t to the dump file.
*/

static void
dump_type(TYPE t)
{
	CV_SPEC qual = DEREF_cv(type_qual(t));
	IDENTIFIER tid = DEREF_id(type_name(t));
	dump_cv(qual);
	if (!IS_NULL_id(tid)) {
		switch (TAG_id(tid)) {
		case id_class_alias_tag:
		case id_enum_alias_tag:
		case id_type_alias_tag: {
			dump_id(tid);
			return;
		}
		}
	}
	ASSERT(ORDER_type == 18);
	switch (TAG_type(t)) {

	case type_pre_tag: {
		/* Pre-types */
		if (!IS_NULL_id(tid)) {
			dump_id(tid);
		} else {
			BASE_TYPE bt = DEREF_btype(type_pre_rep(t));
			if (bt == btype_ellipsis) {
				fputs_v("Q<...>", dump_file);
			} else {
				fputc_v(MANGLE_error, dump_file);
			}
		}
		break;
	}

	case type_integer_tag: {
		/* Integral types */
		INT_TYPE it = DEREF_itype(type_integer_rep(t));
		dump_itype(it);
		break;
	}

	case type_floating_tag: {
		/* Floating point types */
		FLOAT_TYPE ft = DEREF_ftype(type_floating_rep(t));
		dump_ftype(ft);
		break;
	}

	case type_top_tag: {
		/* Top type */
		fputc_v(MANGLE_void, dump_file);
		break;
	}

	case type_bottom_tag: {
		/* Bottom type */
		fputc_v(MANGLE_bottom, dump_file);
		break;
	}

	case type_ptr_tag: {
		/* Pointer types */
		TYPE s = DEREF_type(type_ptr_sub(t));
		fputc_v(MANGLE_ptr, dump_file);
		dump_type(s);
		break;
	}

	case type_ref_tag: {
		/* Reference types */
		TYPE s = DEREF_type(type_ref_sub(t));
		fputc_v(MANGLE_ref, dump_file);
		dump_type(s);
		break;
	}

	case type_ptr_mem_tag: {
		/* Pointer to member types */
		CLASS_TYPE ct = DEREF_ctype(type_ptr_mem_of(t));
		TYPE s = DEREF_type(type_ptr_mem_sub(t));
		fputc_v(MANGLE_ptr_mem, dump_file);
		dump_ctype(ct);
		fputc_v(MANGLE_colon, dump_file);
		dump_type(s);
		break;
	}

	case type_func_tag: {
		/* Function types */
		FILE *f = dump_file;
		TYPE r = DEREF_type(type_func_ret(t));
		LIST(TYPE)p = DEREF_list(type_func_ptypes(t));
		LIST(TYPE)e = DEREF_list(type_func_except(t));
		int ell = DEREF_int(type_func_ellipsis(t));
		CV_SPEC mqual = DEREF_cv(type_func_mqual(t));
		if (ell & FUNC_WEAK) {
			fputc_v(MANGLE_weak, f);
		} else {
			fputc_v(MANGLE_func, f);
		}
		dump_type(r);
		dump_type_list(p, ell, 1);
		if (ell & FUNC_VAR_PARAMS) {
			fputc_v(MANGLE_dot, f);
		} else {
			fputc_v(MANGLE_colon, f);
		}
		if (!EQ_list(e, univ_type_set)) {
			/* Output exception specifiers */
			fputc_v('(', f);
			dump_type_list(e, FUNC_NONE, 0);
			fputc_v(')', f);
		}
		dump_cv(mqual);
		if (ell & FUNC_NO_PARAMS) {
			fputc_v(MANGLE_dot, f);
		} else {
			fputc_v(MANGLE_colon, f);
		}
		break;
	}

	case type_array_tag: {
		/* Array types */
		TYPE s = DEREF_type(type_array_sub(t));
		NAT n = DEREF_nat(type_array_size(t));
		fputc_v(MANGLE_array, dump_file);
		if (!IS_NULL_nat(n)) {
			dump_nat(n, 0);
		}
		fputc_v(MANGLE_colon, dump_file);
		dump_type(s);
		break;
	}

	case type_bitfield_tag: {
		/* Bitfield types */
		INT_TYPE it = DEREF_itype(type_bitfield_defn(t));
		dump_itype(it);
		break;
	}

	case type_compound_tag: {
		/* Class types */
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		dump_ctype(ct);
		break;
	}

	case type_enumerate_tag: {
		/* Enumeration types */
		ENUM_TYPE et = DEREF_etype(type_enumerate_defn(t));
		dump_etype(et);
		break;
	}

	case type_token_tag: {
		/* Tokenised types */
		IDENTIFIER id = DEREF_id(type_token_tok(t));
		LIST(TOKEN)args = DEREF_list(type_token_args(t));
		dump_tok_appl(id, args);
		break;
	}

	case type_templ_tag: {
		/* Template types */
		TYPE s = DEREF_type(type_templ_defn(t));
		TOKEN sort = DEREF_tok(type_templ_sort(t));
		dump_sort(sort);
		dump_type(s);
		break;
	}

	case type_instance_tag: {
		/* Template instance types */
		IDENTIFIER id = DEREF_id(type_name(t));
		dump_id(id);
		break;
	}

	default : {
		/* Other types */
		fputc_v(MANGLE_error, dump_file);
		break;
	}
	}
	return;
}


/*
    DUMP A GRAPH

    This routine adds the graph gr and all its subgraphs to the dump file.
*/

static void
dump_graph(GRAPH gr)
{
	FILE *f = dump_file;
	unsigned n = DEREF_unsigned(graph_no(gr));
	DECL_SPEC ds = DEREF_dspec(graph_access(gr));
	if (ds & dspec_main) {
		/* First instance of base */
		DECL_SPEC acc = (ds & dspec_access);
		CLASS_TYPE ct = DEREF_ctype(graph_head(gr));
		LIST(GRAPH)br = DEREF_list(graph_tails(gr));
		fprintf_v(f, "%u=", n);

		/* Dump access */
		if (ds & dspec_virtual) {
			fputc_v('V', f);
		}
		if (acc != dspec_public) {
			gr = DEREF_graph(graph_equal(gr));
			while (!IS_NULL_graph(gr)) {
				ds = DEREF_dspec(graph_access(gr));
				ds &= dspec_access;
				if (ds < acc) {
					acc = ds;
				}
				if (acc == dspec_public) {
					break;
				}
				gr = DEREF_graph(graph_equal(gr));
			}
		}
		dump_access(acc);

		/* Dump base classes */
		dump_ctype(ct);
		if (!IS_NULL_list(br)) {
			fputs_v(" ( ", f);
			while (!IS_NULL_list(br)) {
				GRAPH gs = DEREF_graph(HEAD_list(br));
				dump_graph(gs);
				fputc_v(' ', f);
				br = TAIL_list(br);
			}
			fputc_v(')', f);
		}

	} else {
		/* Subsequent instances of base */
		fprintf_v(f, "%u:", n);
	}
	return;
}

/*
    DUMP A TOKEN APPLICATION

    This routine adds the token application id ( args ) to the dump file.
*/

static void
dump_tok_appl(IDENTIFIER id, LIST(TOKEN)args)
{
	if (IS_id_token(id)) {
		IDENTIFIER alt = DEREF_id(id_token_alt(id));
		if (!IS_NULL_id(alt)) {
			id = alt;
		}
	}
	if (IS_NULL_list(args)) {
		dump_id(id);
	} else {
		FILE *f = dump_file;
		fputc_v('T', f);
		dump_id(id);
		while (!IS_NULL_list(args)) {
			TOKEN arg = DEREF_tok(HEAD_list(args));
			fputc_v(MANGLE_comma, f);
			if (!IS_NULL_tok(arg)) {
				ASSERT(ORDER_tok == 10);
				switch (TAG_tok(arg)) {
				case tok_exp_tag: {
					EXP e = DEREF_exp(tok_exp_value(arg));
					fputc_v('E', f);
					if (!IS_NULL_exp(e)) {
						dump_exp(e);
					}
					break;
				}
				case tok_stmt_tag: {
					EXP e = DEREF_exp(tok_stmt_value(arg));
					fputc_v('S', f);
					if (!IS_NULL_exp(e)) {
						dump_exp(e);
					}
					break;
				}
				case tok_nat_tag: {
					NAT n = DEREF_nat(tok_nat_value(arg));
					fputc_v('N', f);
					if (!IS_NULL_nat(n)) {
						dump_nat(n, 0);
					}
					break;
				}
				case tok_snat_tag: {
					NAT n = DEREF_nat(tok_snat_value(arg));
					fputc_v('I', f);
					if (!IS_NULL_nat(n)) {
						dump_nat(n, 0);
					}
					break;
				}
				case tok_type_tag: {
					TYPE t =
					    DEREF_type(tok_type_value(arg));
					fputc_v('T', f);
					if (!IS_NULL_type(t)) {
						dump_type(t);
					}
					break;
				}
				case tok_func_tag: {
					IDENTIFIER fid =
					    DEREF_id(tok_func_defn(arg));
					fputc_v('F', f);
					if (!IS_NULL_id(fid)) {
						dump_id(fid);
					}
					break;
				}
				case tok_member_tag: {
					OFFSET off =
					    DEREF_off(tok_member_value(arg));
					fputc_v('M', f);
					if (!IS_NULL_off(off)) {
						dump_off(off);
					}
					break;
				}
				case tok_class_tag: {
					IDENTIFIER tid =
					    DEREF_id(tok_class_value(arg));
					fputc_v('C', f);
					if (!IS_NULL_id(tid)) {
						dump_id(tid);
					}
					break;
				}
				}
			}
			args = TAIL_list(args);
		}
		fputc_v(MANGLE_colon, f);
	}
	return;
}


/*
    DUMP A BASE CLASS GRAPH

    This routine adds the base class graph associated with the class type
    ct to the dump file.
*/

void
dump_base(CLASS_TYPE ct)
{
	unsigned n = DEREF_unsigned(ctype_no_bases(ct));
	if (n > 1) {
		FILE *f = dump_file;
		if (f) {
			const char *key;
			GRAPH gr = DEREF_graph(ctype_base(ct));
			CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
			if (ci & cinfo_union) {
				key = "TU";
			} else if (ci & cinfo_struct) {
				key = "TS";
			} else {
				key = "TC";
			}
			fprintf_v(f, "B%s\t%u\t", key, n);
			dump_graph(gr);
			fputc_v('\n', f);
		}
	}
	return;
}


/*
    DUMP AN OVERRIDING VIRTUAL FUNCTION

    This routine dumps the fact that the virtual function id overrides
    the virtual function fid.
*/

void
dump_override(IDENTIFIER id, IDENTIFIER fid)
{
	FILE *f = dump_file;
	if (f) {
		fputs_v("O\t", f);
		dump_id(id);
		fputc_v('\t', f);
		dump_id(fid);
		fputc_v('\n', f);
	}
	return;
}


/*
    DUMP A USING DECLARATION

    This routine dumps the fact that a using declaration has been used to
    set up the alias id for cid.
*/

void
dump_alias(IDENTIFIER id, IDENTIFIER cid, LOCATION *loc)
{
	ulong n = DEREF_ulong(id_dump(cid));
	COPY_ulong(id_dump(id), n);
	/* NOT YET IMPLEMENTED */
	UNUSED(loc);
	return;
}


/*
    DUMP A USING DIRECTIVE

    This routine dumps the fact that the namespace ns has been the subject
    of a using directive in the namespace cns.
*/

void
dump_using(NAMESPACE ns, NAMESPACE cns, LOCATION *loc)
{
	/* NOT YET IMPLEMENTED */
	UNUSED(ns);
	UNUSED(cns);
	UNUSED(loc);
	return;
}


/*
    TABLE OF ERROR NUMBERS

    This array contains a table of flags indicating whether each error
    has been output or not.
*/

static char *err_output = NULL;


/*
    DUMP AN ERROR

    This routine adds the error e of severity sev to the dump file.  It
    returns false if the dump has already been closed or e is an internal
    compiler error.
*/

int
dump_error(ERROR e, LOCATION *loc, int sev, int cnt)
{
	if (IS_err_simple(e)) {
		/* Simple error message */
		FILE *f = dump_file;
		int n = DEREF_int(err_simple_number(e));
		ERR_DATA *msg = ERR_CATALOG + n;
		const char *sig = msg->signature;
		ERR_PROPS props = msg->props;

		/* Dump start of error */
		if (f == NULL) {
			return 0;
		}
		if (props & ERR_PROP_compiler) {
			return 0;
		}
		if (loc) {
			/* First error component */
			const char *err;
			switch (sev) {
			case ERROR_FATAL:
				err = "EF";
				break;
			case ERROR_INTERNAL:
				err = "EI";
				break;
			case ERROR_WARNING:
				err = "EW";
				break;
			default:
				err = "ES";
				break;
			}
			fprintf_v(f, "%s\t", err);
			dump_loc(loc);
			fputc_v('\t', f);
		} else {
			/* Subsequent error component */
			fputs_v("EC\t", f);
		}

		/* Dump error number */
		if (err_output[n]) {
			fprintf_v(f, "%d", n);
		} else {
			const char *name = msg->name;
			fprintf_v(f, "%d = <%s.%s>", n, ERR_NAME, name);
			err_output[n] = 1;
		}

		/* Dump error arguments */
		if (sig == NULL) {
			fprintf_v(f, "\t0\t%d\n", cnt );
		} else {
			unsigned a;
			unsigned na = (unsigned)strlen(sig);
			fprintf_v(f, "\t%u\t%d\n", na, cnt );
			for (a = 0; a < na; a++) {
				switch (sig[a]) {
				case ERR_KEY_ACCESS: {
					ACCESS acc;
					acc =
					    DEREF_dspec(err_arg(e, a, ACCESS));
					IGNORE print_access(acc, dump_buff, 0);
					fputs_v("EAS\t", f);
					dump_string();
					break;
				}
				case ERR_KEY_BASE_TYPE: {
					BASE_TYPE bt;
					bt = DEREF_btype(err_arg(e, a, BASE_TYPE));
					IGNORE print_btype(bt, dump_buff, 0);
					fputs_v("EAS\t", f);
					dump_string();
					break;
				}
				case ERR_KEY_CLASS_TYPE: {
					CLASS_TYPE ct;
					ct = DEREF_ctype(err_arg(e, a, CLASS_TYPE));
					fputs_v("EAT\t", f);
					dump_ctype(ct);
					break;
				}
				case ERR_KEY_CV_SPEC: {
					CV_SPEC cv =
					    DEREF_cv(err_arg(e, a, CV_SPEC));
					IGNORE print_cv(cv, dump_buff, 0);
					fputs_v("EAS\t", f);
					dump_string();
					break;
				}
				case ERR_KEY_DECL_SPEC: {
					DECL_SPEC ds;
					ds = DEREF_dspec(err_arg(e, a, DECL_SPEC));
					IGNORE print_dspec(ds, dump_buff, 0);
					fputs_v("EAS\t", f);
					dump_string();
					break;
				}
				case ERR_KEY_FLOAT: {
					FLOAT flt =
					    DEREF_flt(err_arg(e, a, FLOAT));
					IGNORE print_flt(flt, dump_buff, 0);
					fputs_v("EAS\t", f);
					dump_string();
					break;
				}
				case ERR_KEY_HASHID: {
					HASHID nm;
					nm = DEREF_hashid(err_arg(e, a, HASHID));
					fputs_v("EAH\t", f);
					dump_hashid(nm);
					break;
				}
				case ERR_KEY_IDENTIFIER:
				case ERR_KEY_LONG_ID: {
					IDENTIFIER id;
					id = DEREF_id(err_arg(e, a, IDENTIFIER));
					fputs_v("EAI\t", f);
					dump_id(id);
					break;
				}
				case ERR_KEY_LEX: {
					LEX t = DEREF_int(err_arg(e, a, LEX));
					fputs_v("EAS\t", f);
					dump_lex(t);
					break;
				}
				case ERR_KEY_NAMESPACE: {
					NAMESPACE ns;
					ns = DEREF_nspace(err_arg(e, a, NAMESPACE));
					fputs_v("EAC\t", f);
					dump_nspace(ns, 0);
					break;
				}
				case ERR_KEY_NAT: {
					NAT nat = DEREF_nat(err_arg(e, a, NAT));
					fputs_v("EAN\t", f);
					dump_nat(nat, 0);
					break;
				}
				case ERR_KEY_PPTOKEN_P: {
					PPTOKEN_P tok;
					tok = DEREF_pptok(err_arg(e, a, PPTOKEN_P));
					IGNORE print_pptok(tok, dump_buff, 0);
					fputs_v("EAS\t", f);
					dump_string();
					break;
				}
				case ERR_KEY_PTR_LOC: {
					PTR_LOC ploc;
					LOCATION aloc;
					ploc =
					    DEREF_ptr(err_arg(e, a, PTR_LOC));
					DEREF_loc(ploc, aloc);
					fputs_v("EAL\t", f);
					dump_loc(&aloc);
					break;
				}
				case ERR_KEY_QUALIFIER: {
					const char *s;
					QUALIFIER qual;
					qual = DEREF_qual(err_arg(e, a, QUALIFIER));
					if (qual == qual_full ||
					    qual == qual_top) {
						s = "::";
					} else {
						s = "";
					}
					fprintf_v(f, "EAS\t<%s>", s);
					break;
				}
				case ERR_KEY_STRING: {
					STRING str =
					    DEREF_str(err_arg(e, a, STRING));
					IGNORE print_str(str, dump_buff, 0);
					fputs_v("EAS\t", f);
					dump_string();
					break;
				}
				case ERR_KEY_TYPE: {
					TYPE t =
					    DEREF_type(err_arg(e, a, TYPE));
					fputs_v("EAT\t", f);
					dump_type(t);
					break;
				}
				case ERR_KEY_cint: {
					cint i = DEREF_int(err_arg(e, a, cint));
					fprintf_v(f, "EAV\t%d", i);
					break;
				}
				case ERR_KEY_plural: {
					plural i;
					i = DEREF_unsigned(err_arg(e, a, plural));
					if (i == 1) {
						fputs_v("EAS\t<>", f);
					} else {
						fputs_v("EAS\t<s>", f);
					}
					break;
				}
				case ERR_KEY_cstring:
				case ERR_KEY_string: {
					string s;
					s = DEREF_string(err_arg(e, a, string));
					if (s) {
						unsigned d =
						    (unsigned)ustrlen(s);
						fprintf_v(f, "EAS\t&%u<%s>", d,
							  strlit(s));
					} else {
						fputs_v("EAS\t<>", f);
					}
					break;
				}
				case ERR_KEY_ulong:
				case ERR_KEY_ucint: {
					ulong u =
					    DEREF_ulong(err_arg(e, a, ulong));
					fprintf_v(f, "EAV\t%lu", u);
					break;
				}
				case ERR_KEY_unsigned: {
					unsigned u;
					u = DEREF_unsigned(err_arg(e, a,
								   unsigned));
					fprintf_v(f, "EAV\t%u", u);
					break;
				}
				default: {
					fputs_v("EAS\t<>", f);
					break;
				}
				}
				fputc_v('\n', f);
			}
		}

	} else {
		/* Composite error message */
		ERROR e1 = DEREF_err(err_compound_head(e));
		ERROR e2 = DEREF_err(err_compound_tail(e));
		if (!dump_error(e1, loc, sev, 1)) {
			return 0;
		}
		if (!dump_error(e2, NIL(LOCATION), sev, cnt)) {
			return 0;
		}
	}
	return 1;
}


/*
    DUMP A VARIABLE DESTRUCTOR CALL

    This routine adds the call of the destructor for the variable id to
    the dump file.
*/

void
dump_destr(IDENTIFIER id, LOCATION *loc)
{
	EXP d = DEREF_exp(id_variable_etc_term(id));
	if (!IS_NULL_exp(d)) {
		unsigned tag = TAG_exp(d);
		while (tag == exp_paren_tag) {
			d = DEREF_exp(exp_paren_arg(d));
			if (IS_NULL_exp(d)) {
				return;
			}
			tag = TAG_exp(d);
		}
		while (tag == exp_nof_tag) {
			d = DEREF_exp(exp_nof_pad(d));
			tag = TAG_exp(d);
		}
		while (tag == exp_destr_tag) {
			d = DEREF_exp(exp_destr_call(d));
			tag = TAG_exp(d);
		}
		if (tag == exp_func_id_tag) {
			IDENTIFIER fn = DEREF_id(exp_func_id_id(d));
			dump_use(id, loc, 0);
			dump_call(fn, loc, 0);
		}
	}
	return;
}


/*
    DUMP AN IDENTIFIER DECLARATION

    This routine adds the declaration of the identifier id to the dump
    file.  The parameter def is 1 for a definition, 2 for a tentative
    definition, and 0 for a declaration.
*/

void
dump_declare(IDENTIFIER id, LOCATION *loc, int def)
{
	FILE *f = dump_file;
	const char *key = dump_key(id, def);
	if (key && f) {
		/* Dump identifier key */
		char d = 'M';
		int destr = 0;
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if (dump_implicit || dump_template) {
			fputc_v('I', f);
		}
		switch (def) {
		case 1:
			d = 'D';
			break;
		case 2:
			d = 'T';
			break;
		}

		/* Dump location and identifier information */
		fprintf_v(f, "%c%s\t", d, key);
		dump_loc(loc);
		fputc_v('\t', f);
		dump_id(id);
		fputc_v('\t', f);

		/* Dump identifier specific information */
		switch (TAG_id(id)) {
		case id_obj_macro_tag: {
			/* Object-like macros */
			fputs_v("ZUO", f);
			break;
		}
		case id_func_macro_tag: {
			/* Function-like macros */
			unsigned n;
			n = DEREF_unsigned(id_func_macro_no_params(id));
			fprintf_v(f, "ZUF%u", n);
			break;
		}
		case id_builtin_tag: {
			/* Built-in operators */
			TYPE r = DEREF_type(id_builtin_ret(id));
			LIST(TYPE)p = DEREF_list(id_builtin_ptypes(id));
			fputc_v(MANGLE_func, f);
			dump_type(r);
			dump_type_list(p, FUNC_NONE, 1);
			fputc_v(MANGLE_colon, f);
			fputc_v(MANGLE_colon, f);
			break;
		}
		case id_class_name_tag:
		case id_enum_name_tag:
		case id_class_alias_tag:
		case id_enum_alias_tag:
		case id_type_alias_tag: {
			/* Type aliases */
			TYPE t = DEREF_type(id_class_name_etc_defn(id));
			if (ds & dspec_token) {
				/* Tokenised types */
				IDENTIFIER tid = find_token(id);
				if (IS_id_token(tid)) {
					TOKEN tok =
					    DEREF_tok(id_token_sort(tid));
					dump_sort(tok);
					break;
				}
			}
			dump_type(t);
			break;
		}
		case id_nspace_name_tag: {
			/* Namespace names */
			fputc_v('*', f);
			break;
		}
		case id_nspace_alias_tag: {
			/* Namespace aliases */
			NAMESPACE ns = DEREF_nspace(id_nspace_alias_defn(id));
			dump_nspace(ns, 0);
			break;
		}
		case id_variable_tag:
		case id_parameter_tag:
		case id_stat_member_tag: {
			/* Variables */
			TYPE t = DEREF_type(id_variable_etc_type(id));
			dump_type(t);
			if (!(ds & dspec_auto))destr = def;
			break;
		}
		case id_weak_param_tag: {
			/* Non-prototype function parameters */
			dump_type(type_sint);
			break;
		}
		case id_function_tag:
		case id_mem_func_tag:
		case id_stat_mem_func_tag: {
			/* Functions */
			TYPE t = DEREF_type(id_function_etc_type(id));
			IDENTIFIER over = DEREF_id(id_function_etc_over(id));
			dump_type(t);
			if (!IS_NULL_id(over)) {
				fputc_v('\t', f);
				dump_id(over);
			}
			break;
		}
		case id_member_tag: {
			/* Data members */
			TYPE t = DEREF_type(id_member_type(id));
			dump_type(t);
			break;
		}
		case id_enumerator_tag: {
			/* Enumerators */
			TYPE t = DEREF_type(id_enumerator_etype(id));
			dump_type(t);
			break;
		}
		case id_token_tag: {
			/* Tokens */
			TOKEN tok = DEREF_tok(id_token_sort(id));
			dump_sort(tok);
			break;
		}
		default : {
			/* Other identifiers */
			fputc_v('*', f);
			break;
		}
		}
		fputc_v('\n', f);

		/* Deal with destructors */
		if (destr && do_usage) {
			dump_destr(id, loc);
		}
	}
	dump_implicit = 0;
	return;
}


/*
    DUMP AN IDENTIFIER UNDEFINITION

    This routine adds the undefinition (indicating the end of a scope)
    of the identifier id to the dump file.
*/

void
dump_undefine(IDENTIFIER id, LOCATION *loc, int def)
{
	FILE *f = dump_file;
	const char *key = dump_key(id, def);
	if (key && f) {
		if (def) {
			fprintf_v(f, "U%s\t", key);
		} else {
			fprintf_v(f, "Q%s\t", key);
		}
		dump_loc(loc);
		fputc_v('\t', f);
		dump_id(id);
		fputc_v('\n', f);
	}
	return;
}


/*
    DUMP AN IDENTIFIER USE

    This routine adds the use of the identifier id to the dump file.
    expl is true for an explicit use.
*/

void
dump_use(IDENTIFIER id, LOCATION *loc, int expl)
{
	FILE *f = dump_file;
	const char *key = dump_key(id, 1);
	if (key && f) {
		if (!expl) {
			fputc_v('I', f);
		}
		fprintf_v(f, "L%s\t", key);
		dump_loc(loc);
		fputc_v('\t', f);
		dump_id(id);
		fputc_v('\n', f);
	}
	return;
}


/*
    DUMP AN IDENTIFIER CALL

    This routine adds the call of the identifier id to the dump file.
    expl is true for an explicit call.
*/

void
dump_call(IDENTIFIER id, LOCATION *loc, int expl)
{
	FILE *f = dump_file;
	const char *key = dump_key(id, 1);
	if (key && f) {
		if (!expl) {
			fputc_v('I', f);
		}
		fprintf_v(f, "C%s\t", key);
		dump_loc(loc);
		fputc_v('\t', f);
		dump_id(id);
		fputc_v('\n', f);
	}
	return;
}


/*
    DUMP A TEMPLATE INSTANCE

    This routine adds the association of the identifier id and the
    template instance form to the dump file.
*/

void
dump_instance(IDENTIFIER id, TYPE form, TYPE spec)
{
	FILE *f = dump_file;
	const char *key = dump_key(id, 1);
	if (key && f) {
		fprintf_v(f, "Z%s\t", key);
		dump_id(id);
		fputc_v('\t', f);
		dump_type(form);
		if (!EQ_type(form, spec)) {
			fputc_v('\t', f);
			dump_type(spec);
			fputc_v('\n', f);
		} else {
			fputs_v("\t*\n", f);
		}
	}
	return;
}


/*
    DUMP A TOKEN NAME

    This routine adds the association of the identifier id and the external
    token name tok to the dump file.
*/

void
dump_token(IDENTIFIER id, IDENTIFIER tok)
{
	FILE *f = dump_file;
	const char *key = dump_key(id, 1);
	if (key && f) {
		HASHID nm = DEREF_hashid(id_name(tok));
		if (IS_hashid_name_etc(nm)) {
			string s = DEREF_string(hashid_name_etc_text(nm));
			unsigned n = (unsigned)ustrlen(s);
			fprintf_v(f, "X%s\t", key);
			dump_id(id);
			fprintf_v(f, "\t&%u<%s>\n", n, strlit(s));
		}
	}
	return;
}


/*
    DUMP A TOKEN PARAMETER

    This routine adds the declaration of the token or template parameter
    id to the dump file.
*/

void
dump_token_param(IDENTIFIER id)
{
	dump_declare(id, &crt_loc, 0);
	if (IS_id_token(id)) {
		IDENTIFIER alt = DEREF_id(id_token_alt(id));
		ulong n = DEREF_ulong(id_dump(id));
		COPY_ulong(id_dump(alt), n);
	}
	return;
}


/*
    DUMP A BUILT-IN OPERATOR

    This routine adds the declaration of the built-in operator id to the
    dump file.
*/

void
dump_builtin(IDENTIFIER id)
{
	if (IS_id_builtin(id)) {
		dump_implicit = 1;
		dump_declare(id, &crt_loc, 0);
	}
	return;
}


/*
    DUMP A PROMOTION TYPE

    This routine adds the fact that the promotion of the integral type
    it is ip to the dump file.
*/

void
dump_promote(INT_TYPE it, INT_TYPE ip)
{
	FILE *f = dump_file;
	if (f) {
		fputs_v("P\t", f);
		dump_itype(it);
		fputc_v(MANGLE_colon, f);
		dump_itype(ip);
		fputc_v('\n', f);
	}
	return;
}


/*
    DUMP THE START OF A SCOPE

    This routine adds the start of the scope ns (which may have an associated
    name, id) to the dump file.  pns gives the enclosing scope, if known.
*/

void
dump_begin_scope(IDENTIFIER id, NAMESPACE ns, NAMESPACE pns, LOCATION *loc)
{
	FILE *f = dump_file;
	if (!IS_NULL_nspace(ns) && f) {
		ulong n;
		HASHID nm;
		if (!IS_NULL_id(id)) {
			/* Named scope */
			fputs_v("SSH\t", f);
			n = DEREF_ulong(id_dump(id));
			if (n != LINK_NONE) {
				/* Already used */
				dump_loc(loc);
				fprintf_v(f, "\t%lu\n", n);
				return;
			}
			n = dump_id_next++;
			COPY_ulong(id_dump(id), n);
			nm = DEREF_hashid(id_name(id));
		} else {
			/* Unnamed scope */
			fputs_v("SSB\t", f);
			n = dump_id_next++;
			nm = NULL_hashid;
		}
		dump_loc(loc);
		fprintf_v(f, "\t%lu = ", n);
		dump_hashid(nm);
		fputc_v('\t', f);
		dump_nspace(pns, 1);
		fputc_v('\n', f);
		COPY_ulong(nspace_dump(ns), n);
	}
	return;
}


/*
    DUMP THE END OF A SCOPE

    This routine adds the end of the scope ns (which may have an associated
    name, id) to the dump file.
*/

void
dump_end_scope(IDENTIFIER id, NAMESPACE ns, LOCATION *loc)
{
	FILE *f = dump_file;
	if (!IS_NULL_nspace(ns) && f) {
		ulong n = DEREF_ulong(nspace_dump(ns));
		if (!IS_NULL_id(id)) {
			fputs_v("SEH\t", f);
		} else {
			fputs_v("SEB\t", f);
		}
		dump_loc(loc);
		fprintf_v(f, "\t%lu\n", n);
	}
	return;
}


/*
    DUMP A STRING LITERAL

    This routine adds the string literal of type kind given by the start
    and end points s and e to the dump file.
*/

void
dump_string_lit(string s, string e, unsigned kind)
{
	FILE *f = dump_file;
	if (f) {
		unsigned long n = (unsigned long)(e - s);
		fputc_v('A', f);
		if (kind & STRING_CHAR) {
			fputc_v('C', f);
		}
		if (kind & STRING_WIDE) {
			fputc_v('L', f);
		}
		fputc_v('\t', f);
		dump_loc(&crt_loc);
		fprintf_v(f, "\t&%lu<", n);
		while (s != e) {
			int c = (int)*(s++);
			fputc_v(c, f);
		}
		fputs_v(">\n", f);
	}
	return;
}


/*
    DUMP THE START OF A FILE

    This routine adds the start of the file loc to the dump file.  dir
    gives the directory in which the file was found.
*/

void
dump_start(LOCATION *loc, INCL_DIR *dir)
{
	FILE *f = dump_file;
	if (f) {
		fputs_v("FS\t", f);
		dump_loc(loc);
		if (dir) {
			fprintf_v(f, "\t%lu\n", dir->no);
		} else {
			fputs_v("\t*\n", f);
		}
	}
	return;
}


/*
    DUMP THE END OF A FILE

    This routine adds the end of the file loc to the dump file.
*/

void
dump_end(LOCATION *loc)
{
	FILE *f = dump_file;
	if (f) {
		fputs_v("FE\t", f);
		dump_loc(loc);
		fputc_v('\n', f);
	}
	return;
}


/*
    DUMP A FILE INCLUSION

    This routine adds a file inclusion to the dump file.  loc gives the
    location of the '#include' directive, the following file start gives
    the file included.  st is as in start_include, plus 4 for the
    resumption of a file after a file has been included.  q is either '"',
    '>' or ']' depending on the type of inclusion.
*/

void
dump_include(LOCATION *loc, string nm, int st, int q)
{
	FILE *f = dump_file;
	if (f) {
		const char *incl;
		switch (st) {
		case 2:
			incl = "FIS";
			break;
		case 3:
			incl = "FIE";
			break;
		case 4:
			incl = "FIR";
			nm = NULL;
			break;
		default: {
			if (q == char_quote) {
				incl = "FIQ";
			} else if (q == char_close_square) {
				incl = "FIN";
			} else {
				incl = "FIA";
			}
			break;
		}
		}
		fprintf_v(f, "%s\t", incl);
		dump_loc(loc);
		if (nm) {
			/* Output included name */
			unsigned n = (unsigned)ustrlen(nm);
			fprintf_v(f, "\t&%u<%s>", n, strlit(nm));
		}
		fputc_v('\n', f);
	}
	return;
}


/*
    OPEN DUMP FILE

    This routine opens the dump file nm with dump options given by opt.
    This corresponds to the command-line option '-dopt=nm'.
*/

void
init_dump(string nm, string opt)
{
	if (nm) {
		/* Open dump file */
		FILE *f;
		char *p;
		character c;
		unsigned i, n;
		int do_all = 0;
		output_name[OUTPUT_DUMP] = nm;
		if (!open_output(OUTPUT_DUMP, text_mode)) {
			fail(ERR_fail_dump(nm));
			term_error(0);
			return;
		}
		f = output_file[OUTPUT_DUMP];
		fprintf_v(f, "# Dump file for %s %s\n", progname, progvers);
		fprintf_v(f, "V\t%lu\t%lu\t", DUMP_major, DUMP_minor );
		fprintf_v(f, "<%s>\n", LANGUAGE_NAME);
		dump_file = f;

		/* Set dump options */
		do_dump = 1;
		while (c = *(opt++), (c && c != '=')) {
			switch (c) {
			case 'a':
				do_all = 1;
				break;
			case 'c':
				do_string = 1;
				break;
			case 'e':
				do_error = 1;
				break;
			case 'h':
				do_header = 1;
				break;
			case 'k':
				do_keyword = 1;
				break;
			case 'l':
				do_local = 1;
				break;
			case 'm':
				do_macro = 1;
				break;
			case 'p':
				break;
			case 's':
				do_scope = 1;
				break;
			case 'u':
				do_usage = 1;
				break;
			default: {
				/* Unknown dump options */
				const char *err = "Unknown dump option, '%c'";
				error(ERROR_WARNING, err,(int)c);
				break;
			}
			}
		}
		if (do_all) {
			/* Enable all dump options */
			do_error = 1;
			do_header = 1;
			do_local = 1;
			do_macro = 1;
			do_usage = 1;
		}

		/* Allocate table of error numbers */
		n = catalog_size;
		p = xmalloc_nof(char, n);
		for (i = 0; i < n; i++) {
			p[i] = 0;
		}
		err_output = p;
		last_input = ustrlit("");
		last_file = ustrlit("");

		/* Output file inclusion directories */
		if (do_header) {
			ulong r = 0;
			INCL_DIR *d = dir_path;
			while (d != NULL) {
				string s = d->path;
				if (s) {
					unsigned m = (unsigned)ustrlen(s);
					fprintf_v(f, "FD\t%lu = &%u<%s>", r, m,
						  strlit(s));
					s = d->name;
					if (s) {
						m = (unsigned)ustrlen(s);
						fprintf_v(f, "\t&%u<%s>", m,
							  strlit(s));
					}
					fputc_v('\n', f);
				}
				d->no = r++;
				d = d->next;
			}
		}
		if (do_usage || do_scope) {
			record_location = 1;
		}
		if (do_error) {
			max_errors = ULONG_MAX;
		}
	}
	return;
}


/*
    CLOSE DUMP FILE

    This routine closes the dump file.
*/

void
term_dump(void)
{
	if (do_dump) {
		FILE *f = dump_file;
		if (f) {
			dump_file = NULL;
			fputs_v("# End of dump file\n", f);
			close_output(OUTPUT_DUMP);
		}
		do_dump = 0;
	}
	return;
}
