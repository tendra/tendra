/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>

#include "config.h"
#include "version.h"
#include "system.h"
#include "c_types.h"
#include "ctype_ops.h"
#include "etype_ops.h"
#include "exp_ops.h"
#include "ftype_ops.h"
#include "graph_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "itype_ops.h"
#include "member_ops.h"
#include "nspace_ops.h"
#include "tok_ops.h"
#include "type_ops.h"
#include "virt_ops.h"
#include "error.h"
#include "tdf.h"
#include "access.h"
#include "basetype.h"
#include "buffer.h"
#include "capsule.h"
#include "check.h"
#include "class.h"
#include "compile.h"
#include "constant.h"
#include "convert.h"
#include "destroy.h"
#include "diag.h"
#include "diag2.h"
#include "encode.h"
#include "exception.h"
#include "exp.h"
#include "file.h"
#include "function.h"
#include "hash.h"
#include "mangle.h"
#include "namespace.h"
#include "print.h"
#include "shape.h"
#include "stmt.h"
#include "struct.h"
#include "syntax.h"
#include "throw.h"
#include "tok.h"
#include "typeid.h"
#include "ustring.h"
#include "virtual.h"
#if (TDF_OUTPUT && TDF_DIAG4)


/*
    Certain values used within the diagnostic format are actually DWARF
    tag values.  These macros give the values used.
*/

#define DWARF_LANG_TRAD_C		1
#define DWARF_LANG_ANSI_C		2
#define DWARF_LANG_CPP			4

#if LANGUAGE_C
#define DWARF_LANG			DWARF_LANG_ANSI_C
#define DWARF_LANG_NOT			DWARF_LANG_CPP
#else
#define DWARF_LANG			DWARF_LANG_CPP
#define DWARF_LANG_NOT			DWARF_LANG_ANSI_C
#endif

#define DWARF_EXPLICIT			1
#define DWARF_IMPLICIT			2
#define DWARF_VIRT_EXPL			3
#define DWARF_VIRT_IMPL			4
#define DWARF_CONSTR			5
#define DWARF_VIRT_CONSTR		6
#define DWARF_DESTR			7
#define DWARF_VIRT_DESTR		8

#define DWARF_USING_DIR			3
#define DWARF_USING_DECL		5

#define DWARF_ORDINARY			1
#define DWARF_NO_CALL			2
#define DWARF_RUN_TIME			3

#define DWARF_CASE_SENSITIVE		0


/*
    This routine adds the diagnostic file name given by posn to the
    bitstream bs.
*/

static BITSTREAM *
enc_dg_filename(BITSTREAM *bs, PTR(POSITION)posn)
{
	ulong n = DEREF_ulong(posn_tok(posn));
	if (n == LINK_NONE) {
		BITSTREAM *ts;
		string bn = DEREF_string(posn_base(posn));
		string mn = ustrlit(find_machine());
		ulong date = DEREF_ulong(posn_datestamp(posn));
		n = capsule_no(NULL_string, VAR_token);
		COPY_ulong(posn_tok(posn), n);
		if (!output_date) {
			date = 0;
		}
		ts = enc_tokdef_start(n, "Q", NIL(ulong), 0);
		ENC_make_dg_filename(ts);
		ENC_make_nat(ts);
		ENC_INT(ts, date);
		ENC_make_string(ts);
		ts = enc_ustring(ts, mn);
		ENC_make_string(ts);
		if (is_full_pathname(bn)) {
			ts = enc_ustring(ts, ustrlit(""));
		} else {
			string dn = DEREF_string(posn_dir(posn));
			if (dn == NULL) {
				string en = ustrlit(find_cwd());
				ts = enc_ustring(ts, en);
			} else if (is_full_pathname(dn)) {
				ts = enc_ustring(ts, dn);
			} else {
				string en = ustrlit(find_cwd());
				BUFFER *bf = clear_buffer(&incl_buff, NIL(FILE));
				bfprintf(bf, "%s/%s", en, dn);
				ts = enc_ustring(ts, bf->start);
			}
		}
		ENC_make_string(ts);
		ts = enc_ustring(ts, bn);
		enc_tokdef_end(n, ts);
	}

	/* Encode token application */
	ENC_dg_filename_apply_token(bs);
	n = link_no(bs, n, VAR_token);
	ENC_make_tok(bs, n);
	ENC_LEN_SMALL(bs, 0);
	return bs;
}


/*
    This routine adds the source position given by the span from p to q
    to the bitstream bs.
*/

static BITSTREAM *
enc_dg_loc(BITSTREAM *bs, PTR(LOCATION)p, PTR(LOCATION)q)
{
	if (IS_NULL_ptr(p) || IS_NULL_ptr(q)) {
		ENC_dg_null_sourcepos(bs);
	} else {
		ulong lp = DEREF_ulong(loc_line(p));
		ulong lq = DEREF_ulong(loc_line(q));
		ulong cp = DEREF_ulong(loc_column(p));
		ulong cq = DEREF_ulong(loc_column(q));
		PTR(POSITION)fp = DEREF_ptr(loc_posn(p));
		PTR(POSITION)fq = DEREF_ptr(loc_posn(q));
		if (EQ_ptr(p, q)) {
			ENC_dg_mark_sourcepos(bs);
		} else if (lp == lq && cp == cq && EQ_ptr(fp, fq)) {
			ENC_dg_mark_sourcepos(bs);
			q = p;
		} else {
			ENC_dg_span_sourcepos(bs);
		}
		bs = enc_dg_filename(bs, fp);
		ENC_make_nat(bs);
		ENC_INT(bs, lp);
		ENC_make_nat(bs);
		ENC_INT(bs, cp);
		if (!EQ_ptr(p, q)) {
			if (EQ_ptr(fp, fq)) {
				ENC_OFF(bs);
			} else {
				ENC_ON(bs);
				bs = enc_dg_filename(bs, fq);
			}
			ENC_make_nat(bs);
			ENC_INT(bs, lq);
			ENC_make_nat(bs);
			ENC_INT(bs, cq);
		}
	}
	return bs;
}


/*
    This routine returns the location of the start or end of the block e.
*/

static
PTR(LOCATION)block_loc(EXP e, int end)
{
	PTR(LOCATION)loc = NULL_ptr(LOCATION);
	if (!IS_NULL_exp(e)) {
		if (IS_exp_solve_stmt(e)) {
			e = DEREF_exp(exp_solve_stmt_body(e));
		}
		if (IS_exp_sequence(e)) {
			EXP a;
			LIST(EXP)p;
			if (end) {
				p = DEREF_list(exp_sequence_last(e));
			} else {
				p = DEREF_list(exp_sequence_first(e));
			}
			a = DEREF_exp(HEAD_list(p));
			if (!IS_NULL_exp(a) && IS_exp_location(a)) {
				loc = exp_location_end(a);
			}
		}
	}
	return loc;
}


/*
    This routine adds the start of a list of names derived from the
    namespace ns to the bitstream bs.
*/

static BITSTREAM *
enc_dg_namelist(BITSTREAM *bs, NAMESPACE ns)
{
	ulong n = capsule_no(NULL_string, VAR_dgtag);
	IDENTIFIER id = DEREF_id(nspace_name(ns));
	if (!IS_NULL_id(id)) {
		COPY_ulong(id_no(id), n);
	}
	record_usage(n, VAR_dgtag, USAGE_DEFN);
	ENC_dg_tag_namelist(bs);
	n = link_no(bs, n, VAR_dgtag);
	ENC_make_dg_tag(bs, n);
	ENC_make_dg_namelist(bs);
	ENC_LIST_SMALL(bs, 0);
	return bs;
}


/*
    This routine adds the revelant command-line options as a list of
    strings to the bitstream bs.
*/

static BITSTREAM *
enc_dg_options(BITSTREAM *bs)
{
	unsigned n = 0;
	INCL_DIR *d = dir_path;
	while (d != NULL) {
		n++;
		d = d->next;
	}
	ENC_LIST(bs, n);
	d = dir_path;
	while (d != NULL) {
		BUFFER *bf = clear_buffer(&incl_buff, NIL(FILE));
		ENC_make_string(bs);
		bfprintf(bf, "-I%s", d->path);
		bs = enc_ustring(bs, bf->start);
		d = d->next;
	}
	return bs;
}


/*
    This routine adds the top-level compilation unit information to the
    bitstream bs.  The current location gives information about the
    primary source file.
*/

BITSTREAM *
enc_dg_compilation(BITSTREAM *bs)
{
	LOCATION loc;
	ulong date = crt_time;
	string vers = report_version(0);
	ENC_make_dg_compilation(bs);
	bs = enc_dg_filename(bs, crt_loc.posn);
	ENC_LIST_SMALL(bs, 0);
	ENC_LIST_SMALL(bs, 0);
	loc = crt_loc;
	IGNORE set_crt_loc(ustrlit(""), 0);
	bs = enc_dg_filename(bs, crt_loc.posn);
	crt_loc = loc;
	if (!output_date) {
		date = 0;
	}
	ENC_make_nat(bs);
	ENC_INT(bs, date);
	ENC_make_nat(bs);
	ENC_INT(bs, DWARF_LANG);
	ENC_make_nat(bs);
	ENC_INT(bs, DWARF_CASE_SENSITIVE);
	ENC_make_string(bs);
	bs = enc_ustring(bs, vers);
	bs = enc_dg_options(bs);
	bs = enc_dg_namelist(bs, global_namespace);

	/* Output basic type definitions */
	if (output_builtin) {
		CV_SPEC cv;
		BUILTIN_TYPE n;
		for (n = ntype_char; n < ntype_ellipsis; n++) {
			TYPE t = type_builtin[n];
			switch (TAG_type(t)) {
			case type_integer_tag:
			case type_floating_tag: {
				IGNORE enc_dg_basetype(t, 1);
				break;
			}
			}
		}
		for (cv = cv_none; cv <= cv_qual; cv++) {
			TYPE t = qualify_type(type_void, cv, 0);
			MAKE_type_ptr(cv_none, t, t);
			IGNORE enc_dg_basetype(t, 1);
		}
	}
	return bs;
}


/*
    This routine adds the access specifier component of ds to the bitstream
    bs.  All access specifiers are optional, the default being public.
*/

static BITSTREAM *
enc_dg_access(BITSTREAM *bs, DECL_SPEC ds)
{
	DECL_SPEC acc = (ds & dspec_access);
	if (acc == dspec_private) {
		ENC_ON(bs);
		ENC_dg_private_accessibility(bs);
	} else if (acc == dspec_protected) {
		ENC_ON(bs);
		ENC_dg_protected_accessibility(bs);
	} else {
		ENC_OFF(bs);
	}
	return bs;
}


/*
    This routine adds the virtual specifier component of ds to the bitstream
    bs.  All virtual specifiers are optional, the default being non-virtual.
*/

static BITSTREAM *
enc_dg_virtual(BITSTREAM *bs, DECL_SPEC ds)
{
	if (ds & dspec_virtual) {
		ENC_ON(bs);
		if (ds & dspec_pure) {
			ENC_dg_abstract_virtuality(bs);
		} else {
			ENC_dg_virtual_virtuality(bs);
		}
	} else {
		ENC_OFF(bs);
	}
	return bs;
}


/*
    Template arguments are encoded as dummy object or type names.
*/

static BITSTREAM *
enc_dg_token_arg(BITSTREAM *bs, TOKEN tok)
{
	int is_type = 0;
	EXP e = NULL_exp;
	TYPE t = NULL_type;
	if (!IS_NULL_tok(tok)) {
		switch (TAG_tok(tok)) {
		case tok_exp_tag: {
			int c = DEREF_int(tok_exp_constant(tok));
			if (c) {
				e = DEREF_exp(tok_exp_value(tok));
			}
			break;
		}
		case tok_nat_tag:
		case tok_snat_tag: {
			NAT n = DEREF_nat(tok_nat_etc_value(tok));
			e = calc_nat_value(n, type_sint);
			break;
		}
		case tok_type_tag: {
			t = DEREF_type(tok_type_value(tok));
			is_type = 1;
			break;
		}
		case tok_class_tag: {
			is_type = 1;
			break;
		}
		}
	}
	if (is_type) {
		/* Type name */
		ENC_dg_type_name(bs);
		ENC_OFF(bs);
		ENC_dg_null_sourcepos(bs);
		ENC_OFF(bs);
		if (!IS_NULL_type(t)) {
			ENC_ON(bs);
			bs = enc_dg_type(bs, t, 0);
		} else {
			ENC_OFF(bs);
		}
		ENC_false(bs);
		ENC_OFFS(bs, 2);
	} else {
		/* Object name */
		ENC_dg_object_name(bs);
		bs = enc_dg_name(bs, NULL_id, NULL_type);
		ENC_dg_null_sourcepos(bs);
		if (!IS_NULL_exp(e)) {
			t = DEREF_type(exp_type(e));
			bs = enc_dg_type(bs, t, 0);
			ENC_ON(bs);
			bs = enc_exp(bs, e);
		} else {
			bs = enc_dg_type(bs, t, 0);
			ENC_OFF(bs);
		}
		ENC_OFF(bs);
	}
	return bs;
}


/*
    This routine adds the artificial identifier name s to the bitstream bs.
*/

static BITSTREAM *
enc_dg_artificial(BITSTREAM *bs, const char *s)
{
	ENC_dg_artificial_idname(bs);
	ENC_ON(bs);
	ENC_make_string(bs);
	bs = enc_ustring(bs, ustrlit(s));
	return bs;
}


/*
    This routine adds the name of the identifier id to the bitstream bs.
*/

BITSTREAM *
enc_dg_name(BITSTREAM *bs, IDENTIFIER id, TYPE form)
{
	if (!IS_NULL_type(form) && IS_type_token(form)) {
		/* Template instance name */
		IDENTIFIER tid = DEREF_id(type_token_tok(form));
		LIST(TOKEN)args = DEREF_list(type_token_args(form));
		if (!IS_id_token(tid)) {
			ENC_dg_instance_idname(bs);
			ENC_OFF(bs);
			bs = enc_dg_name(bs, tid, NULL_type);
			bs = enc_dg_loc(bs, id_loc(tid), id_loc(tid));
			ENC_LIST(bs, LENGTH_list(args));
			while (!IS_NULL_list(args)) {
				TOKEN arg = DEREF_tok(HEAD_list(args));
				bs = enc_dg_token_arg(bs, arg);
				args = TAIL_list(args);
			}
			return bs;
		}
	}
	if (!IS_NULL_id(id)) {
		string s;
		HASHID nm = DEREF_hashid(id_name(id));
		switch (TAG_hashid(nm)) {
		case hashid_name_tag: {
			/* Simple case */
			s = DEREF_string(hashid_name_text(nm));
			break;
		}
		case hashid_ename_tag: {
			/* Extended case */
			if (EQ_KEYWORD(nm, lex_this_Hname)) {
				bs = enc_dg_artificial(bs, "this");
				return bs;
			}
			s = DEREF_string(hashid_ename_text(nm));
			break;
		}
		case hashid_anon_tag: {
			/* Anonymous case */
			ENC_dg_anonymous_idname(bs);
			ENC_OFF(bs);
			return bs;
		}
		default : {
			/* Other cases */
			BUFFER *bf;
			bf = clear_buffer(&mangle_buff, NIL(FILE));
			IGNORE print_hashid(nm, 0, 0, bf, 0);
			s = bf->start;
			break;
		}
		}
		if (has_linkage(id)) {
			ENC_dg_external_idname(bs);
		} else {
			ENC_dg_sourcestring_idname(bs);
		}
		ENC_make_string(bs);
		bs = enc_ustring(bs, s);
	} else {
		ENC_dg_anonymous_idname(bs);
		ENC_OFF(bs);
	}
	return bs;
}


/*
    This routine adds the diagnostics for the identifier id to the
    bitstream bs.  use indicates whether a declaration or a definition
    should be output.
*/

static BITSTREAM *
enc_dg_decl(BITSTREAM *bs, IDENTIFIER id, ulong n, unsigned use)
{
	int spec = 0;
	int force = 1;
	int tagged = 0;
	unsigned tag = TAG_id(id);
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	switch (tag) {
	case id_class_name_tag:
	case id_enum_name_tag: {
		/* Class and enumeration names */
		tagged = LANGUAGE_C;
		force = 2;
		break;
	}
	}
	if (n != LINK_NONE && !tagged) {
		/* Declare diagnostic tag if required */
		if (use & USAGE_DECL) {
			ulong m = link_no(bs, n, VAR_dgtag);
			if (use & USAGE_USE) {
				ENC_dg_spec_ref_name(bs);
			} else {
				ENC_dg_tag_name(bs);
			}
			ENC_make_dg_tag(bs, m);
			if (use & USAGE_DEFN) {
				record_usage(n, VAR_dgtag, USAGE_DEFN);
			} else {
				record_usage(n, VAR_dgtag, USAGE_DECL);
				ENC_dg_is_spec_name(bs);
				spec = 1;
			}
		}
	}
	switch (tag) {

	case id_variable_tag:
	case id_parameter_tag:
	case id_stat_member_tag: {
		/* Object names */
		TYPE t = DEREF_type(id_variable_etc_type(id));
		ENC_dg_object_name(bs);
		bs = enc_dg_name(bs, id, NULL_type);
		bs = enc_dg_loc(bs, id_loc(id), id_loc(id));
		bs = enc_dg_type(bs, t, 0);
		if (use & USAGE_DEFN) {
			EXP e;
			int et = error_threshold;
			error_threshold = ERR_SERIOUS;
			ENC_ON(bs);
			MAKE_exp_identifier(t, id, qual_none, e);
			e = convert_reference(e, REF_NORMAL);
			e = convert_lvalue(e);
			if (IS_type_array(t)) {
				/* Do really want contents of array */
				MAKE_exp_contents(t, e, e);
			}
			bs = enc_exp(bs, e);
			free_exp(e, 1);
			error_threshold = et;
		} else {
			ENC_OFF(bs);
		}
		bs = enc_dg_access(bs, ds);
		break;
	}

	case id_function_tag:
	case id_mem_func_tag:
	case id_stat_mem_func_tag: {
		/* Function names */
		PTR(LOCATION)end_loc = id_loc(id);
		TYPE t = DEREF_type(id_function_etc_type(id));
		TYPE form = DEREF_type(id_function_etc_form(id));
		if (use & USAGE_DEFN) {
			EXP e = DEREF_exp(id_function_etc_defn(id));
			end_loc = block_loc(e, 1);
			if (IS_NULL_ptr(end_loc)) {
				end_loc = id_loc(id);
			}
		}
		ENC_dg_proc_name(bs);
		bs = enc_dg_name(bs, id, form);
		if (ds & dspec_implicit) {
			/* Implicitly declared function */
			ENC_dg_null_sourcepos(bs);
		} else {
			bs = enc_dg_loc(bs, id_loc(id), end_loc);
		}
		bs = enc_dg_type(bs, t, 0);
		if (use & USAGE_DEFN) {
			ulong m = DEREF_ulong(id_no(id));
			ENC_ON(bs);
			if (m == LINK_NONE) {
				ENC_make_top(bs);
			} else {
				ENC_obtain_tag(bs);
				m = unit_no(bs, id, VAR_tag, 0);
				ENC_make_tag(bs, m);
			}
		} else {
			ENC_OFF(bs);
		}
		bs = enc_dg_access(bs, ds);
		bs = enc_dg_virtual(bs, ds);
		bs = enc_bool(bs,((ds & dspec_inline)? 1 : 0));
		if (IS_type_func(t)) {
			LIST(TYPE)ex = DEREF_list(type_func_except(t));
			if (EQ_list(ex, univ_type_set)) {
				ENC_OFF(bs);
			} else {
				ENC_ON(bs);
				ENC_LIST(bs, LENGTH_list(ex));
				while (!IS_NULL_list(ex)) {
					TYPE s = DEREF_type(HEAD_list(ex));
					bs = enc_dg_type(bs, s, 0);
					ex = TAIL_list(ex);
				}
			}
		} else {
			ENC_OFF(bs);
		}
		ENC_OFF(bs);
		break;
	}

	case id_class_name_tag:
	case id_enum_name_tag:
	case id_class_alias_tag:
	case id_enum_alias_tag:
	case id_type_alias_tag: {
		/* Type names */
		TYPE t = DEREF_type(id_class_name_etc_defn(id));
		ENC_dg_type_name(bs);
		if (tagged) {
			ENC_OFF(bs);
		} else {
			TYPE form = NULL_type;
			if (IS_type_compound(t)) {
				CLASS_TYPE ct;
				ct = DEREF_ctype(type_compound_defn(t));
				form = DEREF_type(ctype_form(ct));
			}
			ENC_ON(bs);
			bs = enc_dg_name(bs, id, form);
		}
		bs = enc_dg_loc(bs, id_loc(id), id_loc(id));
		bs = enc_dg_access(bs, ds);
		ENC_ON(bs);
		if (tagged) {
			ulong m = link_no(bs, n, VAR_dgtag);
			if (use & USAGE_USE) {
				ENC_dg_spec_ref_type(bs);
			} else {
				ENC_dg_tag_type(bs);
			}
			ENC_make_dg_tag(bs, m);
			if (use & USAGE_DEFN) {
				record_usage(n, VAR_dgtag, USAGE_DEFN);
			} else {
				record_usage(n, VAR_dgtag, USAGE_DECL);
			}
		}
		bs = enc_dg_type(bs, t, force);
		ENC_false(bs);
		ENC_OFFS(bs, 2);
		break;
	}

	case id_nspace_name_tag: {
		/* Namespace names */
		IDENTIFIER nid = id;
		NAMESPACE ns = DEREF_nspace(id_nspace_name_defn(id));
		if (IS_nspace_unnamed(ns)) {
			nid = NULL_id;
		}
		ENC_dg_namespace_name(bs);
		bs = enc_dg_name(bs, nid, NULL_type);
		bs = enc_dg_loc(bs, id_loc(id), id_loc(id));
		bs = enc_dg_namelist(bs, ns);
		break;
	}
	}
	if (spec) {
		ENC_OFF(bs);
	}
	return bs;
}


/*
    This routine outputs any diagnostic information for the token id
    to the appropriate diagnostic units.  It is only called if id is
    defined.  The type t may be used to override the type of id.
*/

void
enc_dg_token(IDENTIFIER id, TYPE t)
{
	UNUSED(id);
	UNUSED(t);
	return;
}


/*
    This list is used to hold all the classes which are used while they
    are incomplete.  A diagnostic tag is introduced for each such class
    which may be defined later if the class is completed.
*/

static LIST(IDENTIFIER)dg_classes = NULL_list(IDENTIFIER);


/*
    This routine defines the diagnostic tags for the incomplete classes
    in the list above.
*/

int
enc_dg_pending(void)
{
	int changed = 0;
	LIST(IDENTIFIER)p;
	while (p = dg_classes, !IS_NULL_list(p)) {
		dg_classes = NULL_list(IDENTIFIER);
		while (!IS_NULL_list(p)) {
			IDENTIFIER id;
			DESTROY_CONS_id(destroy, id, p, p);
			enc_dg_id(id, 2);
			changed = 1;
		}
	}
	return changed;
}


/*
    This routine determines the usage for the diagnostic tag associated
    with the identifier id in the context given by def (true for
    definitions, false for declarations).  The value returned indicates
    whether the diagnostic tag should be declared or defined.
*/

static unsigned
find_dg_usage(IDENTIFIER id, ulong *pn, int def)
{
	unsigned use = USAGE_NONE;
	switch (TAG_id(id)) {
	case id_class_name_tag:
	case id_enum_name_tag:
	case id_class_alias_tag:
	case id_enum_alias_tag:
	case id_type_alias_tag: {
		/* Type names */
		TYPE t;
		ulong n = DEREF_ulong(id_no(id));
		if (n == LINK_NONE) {
			/* Introduce diagnostic tag for type */
			NAMESPACE ns;
			string s = NULL;
			if (def == 0) {
				return USAGE_NONE;
			}
			t = DEREF_type(id_class_name_etc_defn(id));
			if (IS_type_top_etc(t)) {
				/* Ignore 'void' types */
				return USAGE_NONE;
			}
			ns = DEREF_nspace(id_parent(id));
			if (is_local_nspace(ns) == 2) {
				return USAGE_NONE;
			}
			if (output_all) {
				s = mangle_tname("__dg__", t);
			}
			n = capsule_no(s, VAR_dgtag);
			COPY_ulong(id_no(id), n);
		} else {
			use = USAGE_USE;
		}
		if (is_defined(id, &t, 0)) {
			/* Only define each type once */
			unsigned prev = find_usage(n, VAR_dgtag);
			if (prev & USAGE_DEFN) {
				use = USAGE_NONE;
			} else {
				use |= (USAGE_DECL | USAGE_DEFN);
			}
		} else {
			/* Only declare each type once */
			if (use == USAGE_USE) {
				use = USAGE_NONE;
			} else {
				CONS_id(id, dg_classes, dg_classes);
				use = USAGE_DECL;
			}
		}
		*pn = n;
		break;
	}
	case id_variable_tag:
	case id_stat_member_tag:
	case id_function_tag:
	case id_mem_func_tag:
	case id_stat_mem_func_tag: {
		/* Tag names */
		ulong n = get_diag_tag(id, VAR_tag);
		if (n == LINK_NONE) {
			/* Introduce diagnostic tag for tag */
			string s = NULL;
			if (output_all) {
				s = mangle_name(id, VAR_dgtag, 0);
			}
			n = capsule_no(s, VAR_dgtag);
			set_diag_tag(id, VAR_tag, n);
			use = USAGE_DECL;
			if (def) {
				use |= USAGE_DEFN;
			}
		} else {
			/* Only declare each tag once */
			if (def) {
				unsigned prev = find_usage(n, VAR_dgtag);
				if (prev & USAGE_DEFN) {
					use = USAGE_NONE;
				} else {
					use = (USAGE_USE | USAGE_DECL | USAGE_DEFN);
				}
			}
		}
		*pn = n;
		break;
	}
	case id_nspace_name_tag: {
		/* Namespace names */
		use = USAGE_DEFN;
		break;
	}
	}
	return use;
}


/*
    This routine adds the diagnostic information for the global identifier
    id to the diagnostic definition unit.  def is true for a definition.
*/

void
enc_dg_id(IDENTIFIER id, int def)
{
	ulong n;
	NAMESPACE ns;
	BITSTREAM *bs;
	IDENTIFIER pid;

	/* Check the identifier */
	ulong m = LINK_NONE;
	unsigned use = find_dg_usage(id, &m, def);
	if (use == USAGE_NONE) {
		return;
	}

	/* Find the parent namespace */
	ns = DEREF_nspace(id_parent(id));
	while (!IS_NULL_nspace(ns) && IS_nspace_ctype(ns)) {
		pid = DEREF_id(nspace_name(ns));
		enc_dg_id(pid, 1);
		if (m != LINK_NONE) {
			/* Check for inline definitions */
			unsigned prev = find_usage(m, VAR_dgtag);
			if (prev & USAGE_DEFN) {
				return;
			}
		}
		ns = DEREF_nspace(id_parent(pid));
	}
	if (IS_NULL_nspace(ns) || !IS_nspace_named_etc(ns)) {
		/* Ignore local identifiers */
		return;
	}
	pid = DEREF_id(nspace_name(ns));
	if (IS_NULL_id(pid)) {
		return;
	}
	n = DEREF_ulong(id_no(pid));
	if (n == LINK_NONE) {
		/* Allocate namespace list number */
		enc_dg_id(pid, 1);
		n = DEREF_ulong(id_no(pid));
		if (n == LINK_NONE) {
			return;
		}
	}

	/* Add the identifier to the namespace */
	bs = start_bitstream(NIL(FILE), diagcomp_unit->link);
	ENC_dg_name_append(bs);
	n = link_no(bs, n, VAR_dgtag);
	ENC_make_dg_tag(bs, n);
	bs = enc_dg_decl(bs, id, m, use);
	count_item(bs);
	diagcomp_unit = join_bitstreams(diagcomp_unit, bs);
	return;
}


/*
    This table gives the diagnostic tag numbers used to represent the types
    'cv void *'  for the various cv-qualifiers, cv.
*/

static ulong diag_ptr_void[4] = {
	LINK_NONE, LINK_NONE, LINK_NONE, LINK_NONE
};


/*
    This routine adds the diagnostics for the definition of the built-in
    type t to the diagnostic  bs.  This includes 'void *' as well as the
    more obvious integer and floating point types.
*/

ulong
enc_dg_basetype(TYPE t, int def)
{
	BITSTREAM *bs = NULL;
	CV_SPEC cv = cv_none;
	BASE_TYPE bt = btype_none;
	unsigned tag = TAG_type(t);
	string nm = mangle_tname("__dg__", t);
	ulong n = capsule_no(nm, VAR_dgtag);

	/* Introduce dummy type name */
	if (def) {
		IDENTIFIER gid = DEREF_id(nspace_name(global_namespace));
		ulong m = DEREF_ulong(id_no(gid));
		record_usage(n, VAR_dgtag, USAGE_DEFN);
		bs = start_bitstream(NIL(FILE), diagcomp_unit->link);
		ENC_dg_name_append(bs);
		m = link_no(bs, m, VAR_dgtag);
		ENC_make_dg_tag(bs, m);
		ENC_dg_type_name(bs);
		ENC_OFF(bs);
		ENC_dg_global_sourcepos(bs);
		ENC_OFF(bs);
		ENC_ON(bs);
		ENC_dg_tag_type(bs);
		m = link_no(bs, n, VAR_dgtag);
		ENC_make_dg_tag(bs, m);
	}

	/* Encode type definition */
	switch (tag) {
	case type_integer_tag: {
		INT_TYPE it = DEREF_itype(type_integer_rep(t));
		COPY_ulong(itype_diag(it), n);
		if (IS_itype_basic(it)) {
			bt = DEREF_btype(itype_basic_rep(it));
		}
		if (def) {
			if (bt & (btype_char | btype_wchar_t)) {
				ENC_dg_char_type(bs);
			} else if (bt & btype_bool) {
				ENC_dg_boolean_type(bs);
			} else {
				ENC_dg_integer_type(bs);
			}
		}
		break;
	}
	case type_floating_tag: {
		FLOAT_TYPE ft = DEREF_ftype(type_floating_rep(t));
		COPY_ulong(ftype_diag(ft), n);
		if (IS_ftype_basic(ft)) {
			bt = DEREF_btype(ftype_basic_rep(ft));
		}
		if (def) {
			ENC_dg_float_type(bs);
		}
		break;
	}
	case type_ptr_tag: {
		TYPE s = DEREF_type(type_ptr_sub(t));
		cv = DEREF_cv(type_qual(s));
		cv &= cv_qual;
		diag_ptr_void[cv] = n;
		bt = (btype_void | btype_star);
		if (def) {
			ENC_dg_address_type(bs);
		}
		break;
	}
	}
	if (def) {
		if (bt == btype_none) {
			bs = enc_dg_name(bs, NULL_id, NULL_type);
		} else {
			int sp = 0;
			BUFFER *bf = clear_buffer(&mangle_buff, NIL(FILE));
			ENC_dg_external_idname(bs);
			ENC_make_string(bs);
			if (cv) {
				sp = print_cv(cv, bf, sp);
			}
			IGNORE print_btype(bt, bf, sp);
			bs = enc_ustring(bs, bf->start);
		}
		switch (tag) {
		case type_integer_tag: {
			bs = enc_variety(bs, t);
			break;
		}
		case type_floating_tag: {
			bs = enc_flvar(bs, t);
			break;
		}
		case type_ptr_tag: {
			bs = enc_shape(bs, t);
			break;
		}
		}
		ENC_true(bs);
		ENC_OFFS(bs, 2);
		count_item(bs);
		diagcomp_unit = join_bitstreams(diagcomp_unit, bs);
	}
	return n;
}


/*
    This routine adds the diagnostic tag corresponding to the class ct
    to the bitstream bs.
*/

static BITSTREAM *
enc_dg_ctype(BITSTREAM *bs, CLASS_TYPE ct)
{
	ulong n;
	IDENTIFIER cid = DEREF_id(ctype_name(ct));
	cid = DEREF_id(id_alias(cid));
	n = DEREF_ulong(id_no(cid));
	if (n == LINK_NONE) {
		enc_dg_id(cid, 1);
		n = DEREF_ulong(id_no(cid));
	}
	n = link_no(bs, n, VAR_dgtag);
	ENC_make_dg_tag(bs, n);
	return bs;
}


/*
    This routine adds the offset off plus the offset token tok to the
    bitstream bs in the form of a token with one expression parameter
    which returns the parameter plus the offset (allowing for virtual
    indirections etc.).
*/

static BITSTREAM *
enc_dg_offset(BITSTREAM *bs, OFFSET off, ulong tok, int spec)
{
	BITSTREAM *ts, *us;
	ulong m = LINK_NONE;
	ulong n = capsule_no(NULL_string, VAR_token);
	ts = enc_tokdef_start(n, "EE", &m, 1);
	if (spec == -1) {
		us = ts;
	} else {
		ts = enc_special(ts, spec);
		us = start_bitstream(NIL(FILE), ts->link);
	}
	if (tok == LINK_NONE) {
		us = enc_add_ptr(us, NULL_exp, m, off, 1);
	} else {
		ENC_add_to_ptr(us);
		us = enc_add_ptr(us, NULL_exp, m, off, 1);
		tok = link_no(us, tok, VAR_token);
		ENC_exp_apply_token(us);
		ENC_make_tok(us, tok);
		ENC_LEN_SMALL(us, 0);
	}
	if (spec == -1) {
		ts = us;
	} else {
		ts = enc_bitstream(ts, us);
	}
	enc_tokdef_end(n, ts);
	n = link_no(bs, n, VAR_token);
	ENC_make_tok(bs, n);
	return bs;
}


/*
    This routine adds the list of diagnostic base classes given by br
    to the bitstream bs.
*/

static BITSTREAM *
enc_dg_bases(BITSTREAM *bs, LIST(GRAPH)br)
{
	ENC_LIST(bs, LENGTH_list(br));
	while (!IS_NULL_list(br)) {
		GRAPH gs = DEREF_graph(HEAD_list(br));
		OFFSET off = DEREF_off(graph_off(gs));
		CLASS_TYPE cs = DEREF_ctype(graph_head(gs));
		DECL_SPEC acc = DEREF_dspec(graph_access(gs));
		ENC_make_dg_class_base(bs);
		bs = enc_dg_ctype(bs, cs);
		ENC_OFF(bs);
		if (is_zero_offset(off)) {
			ENC_OFF(bs);
		} else {
			/* Base class offset */
			ENC_ON(bs);
			bs = enc_dg_offset(bs, off, LINK_NONE, -1);
		}
		bs = enc_dg_access(bs, acc);
		bs = enc_dg_virtual(bs, acc);
		br = TAIL_list(br);
	}
	return bs;
}


/*
    This routine adds the class member id to the bitstream bs as a
    DG_CLASSMEM if ct is not null, or as a DG_FIELD otherwise.  The
    number of members is recorded in pm.  The routine is also used to
    handle type members of blocks when blk is true.
*/

static BITSTREAM *
enc_dg_member(BITSTREAM *bs, IDENTIFIER id, unsigned *pm, CLASS_TYPE ct,
	      int blk)
{
	int def = 0;
	unsigned done = 0;
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	if (IS_id_function_etc(id)) {
		/* Allow for overloaded functions */
		IDENTIFIER fid = DEREF_id(id_function_etc_over(id));
		if (!IS_NULL_id(fid)) {
			bs = enc_dg_member(bs, fid, pm, ct, blk);
		}
	}
	if (ds & (dspec_alias | dspec_inherit | dspec_token)) {
		/* Ignore inherited members */
		return bs;
	}
	if (ds & dspec_defn) {
		def = 1;
	}
	switch (TAG_id(id)) {
	case id_member_tag: {
		/* Data members */
		HASHID nm = DEREF_hashid(id_name(id));
		if (!IS_hashid_anon(nm)) {
			TYPE t = DEREF_type(id_member_type(id));
			OFFSET off = DEREF_off(id_member_off(id));
			ENC_dg_field_classmem(bs);
			bs = enc_dg_name(bs, id, NULL_type);
			bs = enc_dg_loc(bs, id_loc(id), id_loc(id));
			bs = enc_offset(bs, off);
			bs = enc_dg_type(bs, t, 0);
			bs = enc_dg_access(bs, ds);
			ENC_OFFS(bs, 2);
			done = 1;
		}
		break;
	}
	case id_stat_member_tag: {
		/* Static data members */
		if (!IS_NULL_ctype(ct)) {
			ulong m = LINK_NONE;
			unsigned use = find_dg_usage(id, &m, def);
			ENC_dg_name_classmem(bs);
			bs = enc_dg_decl(bs, id, m,(use | USAGE_DECL));
			done = 1;
		}
		break;
	}
	case id_mem_func_tag: {
		/* Member functions */
		if (!IS_NULL_ctype(ct) && !(ds & dspec_trivial)) {
			ulong m = LINK_NONE;
			unsigned use = find_dg_usage(id, &m, def);
			ENC_dg_function_classmem(bs);
			bs = enc_dg_decl(bs, id, m,(use | USAGE_DECL));
			if (ds & dspec_virtual) {
				/* Offset from start of virtual function table */
				BITSTREAM *ts;
				VIRTUAL vt = DEREF_virt(ctype_virt(ct));
				ulong n = virtual_no(id, vt);
				ENC_ON(bs);
				ts = start_bitstream(NIL(FILE), bs->link);
				bs = enc_special(bs, TOK_vtab_off);
				ts = enc_make_snat(ts,(int)n);
				bs = enc_bitstream(bs, ts);
			} else {
				ENC_OFF(bs);
			}
			done = 1;
		}
		break;
	}
	case id_stat_mem_func_tag: {
		/* Static member functions */
		if (!IS_NULL_ctype(ct)) {
			ulong m = LINK_NONE;
			unsigned use = find_dg_usage(id, &m, def);
			ENC_dg_name_classmem(bs);
			bs = enc_dg_decl(bs, id, m,(use | USAGE_DECL));
			done = 1;
		}
		break;
	}
	case id_class_name_tag:
	case id_enum_name_tag:
	case id_class_alias_tag:
	case id_enum_alias_tag:
	case id_type_alias_tag: {
		/* Nested types */
		if (!IS_NULL_ctype(ct) || blk) {
			ulong m = LINK_NONE;
			unsigned use = find_dg_usage(id, &m, 1);
			if (blk) {
				use = ((use & USAGE_DEFN) | USAGE_DECL);
				ENC_name_decl_dg(bs);
			} else {
				ENC_dg_name_classmem(bs);
			}
			bs = enc_dg_decl(bs, id, m, use);
			done = 1;
		}
		break;
	}
	}
	*pm += done;
	return bs;
}


/*
    This routine calls enc_dg_member for all the members of the
    namespace ns.
*/

static BITSTREAM *
enc_dg_namespace(BITSTREAM *bs, NAMESPACE ns, unsigned *pm, CLASS_TYPE ct)
{
	MEMBER mem;
	int blk = 0;
	if (IS_nspace_ctype(ns)) {
		mem = DEREF_member(nspace_ctype_first(ns));
	} else {
		mem = DEREF_member(nspace_last(ns));
		blk = 1;
	}
	while (!IS_NULL_member(mem)) {
		/* Class members */
		IDENTIFIER mid = DEREF_id(member_id(mem));
		IDENTIFIER nid = DEREF_id(member_alt(mem));
		if (!IS_NULL_id(mid)) {
			bs = enc_dg_member(bs, mid, pm, ct, blk);
		}
		if (!IS_NULL_id(nid) && !EQ_id(nid, mid)) {
			bs = enc_dg_member(bs, nid, pm, ct, blk);
		}
		mem = DEREF_member(member_next(mem));
	}
	return bs;
}


/*
    This routine adds the information for the virtual function table
    and run-time type information associated with the polymorphic class
    t to the bitstream bs in the form of a number of dummy class members.
    Information on these members is returned via vtags.
*/

#if LANGUAGE_CPP

static BITSTREAM *
enc_dg_vtable(BITSTREAM *bs, TYPE t, ulong *vtags)
{
	ulong n, m;
	IDENTIFIER tid = dummy_type_name;
	TYPE ti = get_type_info(lex_typeid, t, 0);
	TYPE tv  = get_type_info(lex_vtable, t, 0);
	TYPE pv = DEREF_type(type_array_sub(tv));
	CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
	VIRTUAL vt = DEREF_virt(ctype_virt(ct));
	ulong tok = DEREF_ulong(virt_table_tok(vt));
	OFFSET off = DEREF_off(virt_table_off(vt));
	ulong tbl = DEREF_ulong(virt_table_tbl(vt));

	/* Make tag for slot type */
	m = capsule_no(NULL_string, VAR_dgtag);
	COPY_ulong(id_no(tid), m);
	COPY_id(type_name(pv), tid);
	record_usage(m, VAR_dgtag, USAGE_DEFN);

	/* Virtual function table pointer */
	n = capsule_no(NULL_string, VAR_dgtag);
	record_usage(n, VAR_dgtag, USAGE_DEFN);
	vtags[0] = n;
	ENC_dg_tag_classmem(bs);
	n = link_no(bs, n, VAR_dgtag);
	ENC_make_dg_tag(bs, n);
	ENC_dg_indirect_classmem(bs);
	bs = enc_dg_artificial(bs, "__vptr");
	ENC_dg_null_sourcepos(bs);
	bs = enc_dg_offset(bs, off, tok, -1);
	ENC_dg_pointer_type(bs);
	ENC_dg_tag_type(bs);
	m = link_no(bs, m, VAR_dgtag);
	ENC_make_dg_tag(bs, m);
	bs = enc_dg_type(bs, pv, 1);
	ENC_OFF(bs);

	/* Run-time type information pointer */
	if (output_rtti) {
		n = capsule_no(NULL_string, VAR_dgtag);
		record_usage(n, VAR_dgtag, USAGE_DEFN);
		vtags[1] = n;
		ENC_dg_tag_classmem(bs);
		n = link_no(bs, n, VAR_dgtag);
		ENC_make_dg_tag(bs, n);
		ENC_dg_indirect_classmem(bs);
		bs = enc_dg_artificial(bs, "__tptr");
		ENC_dg_null_sourcepos(bs);
		bs = enc_dg_offset(bs, off, tok, TOK_typeid_ref);
		ENC_dg_pointer_type(bs);
		bs = enc_dg_type(bs, ti, 0);
		ENC_OFF(bs);
	}

	/* Virtual function table */
	n = capsule_no(NULL_string, VAR_dgtag);
	record_usage(n, VAR_dgtag, USAGE_DEFN);
	vtags[2] = n;
	record_usage(tbl, VAR_tag, USAGE_USE);
	ENC_dg_name_classmem(bs);
	ENC_dg_tag_name(bs);
	n = link_no(bs, n, VAR_dgtag);
	ENC_make_dg_tag(bs, n);
	ENC_dg_object_name(bs);
	bs = enc_dg_artificial(bs, "__vtbl");
	ENC_dg_null_sourcepos(bs);
	bs = enc_dg_type(bs, tv, 0);
	ENC_ON(bs);
	ENC_contents(bs);
	bs = enc_shape(bs, tv);
	ENC_obtain_tag(bs);
	tbl = link_no(bs, tbl, VAR_tag);
	ENC_make_tag(bs, tbl);
	ENC_OFF(bs);

	/* Run-time type information structure */
	if (output_rtti) {
		n = capsule_no(NULL_string, VAR_dgtag);
		record_usage(n, VAR_dgtag, USAGE_DEFN);
		vtags[3] = n;
		ENC_dg_name_classmem(bs);
		ENC_dg_tag_name(bs);
		n = link_no(bs, n, VAR_dgtag);
		ENC_make_dg_tag(bs, n);
		ENC_dg_object_name(bs);
		bs = enc_dg_artificial(bs, "__typeid");
		ENC_dg_null_sourcepos(bs);
		bs = enc_dg_type(bs, ti, 0);
		ENC_ON(bs);
		ENC_contents(bs);
		bs = enc_shape(bs, ti);
		bs = enc_rtti_type(bs, t, lex_typeid);
		ENC_OFF(bs);
	}

	/* Clear slot type */
	COPY_ulong(id_no(tid), LINK_NONE);
	COPY_id(type_name(pv), NULL_id);
	return bs;
}

#endif


/*
    This routine adds the definition of the class type t to the bitstream
    bs.  force is 2 to indicate that a tag name should be output for this
    class.
*/

static BITSTREAM *
enc_dg_class(BITSTREAM *bs, TYPE t, int force)
{
	BITSTREAM *ts;
	unsigned m = 0;
	ulong vtags[4];
	CLASS_TYPE cs = NULL_ctype;
	CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
	CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
	NAMESPACE ns = DEREF_nspace(ctype_member(ct));
	if (force == 0) {
		ENC_dg_unknown_type(bs);
		bs = enc_shape(bs, t);
		return bs;
	}
	if ((ci & cinfo_complete) && (ci & cinfo_defined)) {
		/* Complete class */
		IGNORE compile_class(ct);
		if (ci & (cinfo_static | cinfo_function | cinfo_base)) {
			cs = ct;
		} else if ((ci & cinfo_trivial)!= cinfo_trivial) {
			cs = ct;
		} else {
			LIST(IDENTIFIER)ft;
			ft = DEREF_list(ctype_nest(ct));
			if (!IS_NULL_list(ft)) {
				cs = ct;
			}
			ft = DEREF_list(ctype_pals(ct));
			if (!IS_NULL_list(ft)) {
				cs = ct;
			}
		}
	} else {
		/* Incomplete class */
		ENC_dg_is_spec_type(bs);
		t = NULL_type;
	}
	if (!IS_NULL_ctype(cs)) {
		/* Class type */
		GRAPH gr = DEREF_graph(ctype_base(ct));
		LIST(GRAPH)br = DEREF_list(graph_tails(gr));
		ENC_dg_class_type(bs);
		bs = enc_dg_bases(bs, br);
	} else {
		/* Structure type */
		ENC_dg_struct_type(bs);
	}
	vtags[0] = LINK_NONE;
	vtags[1] = LINK_NONE;
	vtags[2] = LINK_NONE;
	vtags[3] = LINK_NONE;
	ts = start_bitstream(NIL(FILE), bs->link);
	ts = enc_dg_namespace(ts, ns, &m, cs);
#if LANGUAGE_CPP
	if (!IS_NULL_ctype(cs)) {
		if (ci & cinfo_polymorphic) {
			ts = enc_dg_vtable(ts, t, vtags);
			if (output_rtti) {
				m += 2;
			}
			m += 2;
		}
	}
#endif
	ENC_LIST(bs, m);
	bs = join_bitstreams(bs, ts);
	if (!IS_NULL_ctype(cs)) {
		/* Friends */
		ENC_OFF(bs);
		ENC_LIST_SMALL(bs, 0);
	}
	if (!IS_NULL_type(t)) {
		/* Class shape */
		ENC_ON(bs);
		bs = enc_shape(bs, t);
	} else {
		ENC_OFF(bs);
	}
	if (!IS_NULL_ctype(cs)) {
		/* Virtual function table information */
		if (vtags[0] == LINK_NONE) {
			ENC_OFFS(bs, 2);
		} else {
			ENC_ON(bs);
			vtags[2] = link_no(bs, vtags[2], VAR_dgtag);
			ENC_make_dg_tag(bs, vtags[2]);
			ENC_ON(bs);
			vtags[0] = link_no(bs, vtags[0], VAR_dgtag);
			ENC_make_dg_tag(bs, vtags[0]);
		}
	}
	if (force == 2) {
		/* Output tag name */
		IDENTIFIER cid = DEREF_id(ctype_name(ct));
		TYPE form = DEREF_type(ctype_form(ct));
		ENC_ON(bs);
		bs = enc_dg_name(bs, cid, form);
		ENC_ON(bs);
		bs = enc_dg_loc(bs, id_loc(cid), id_loc(cid));
	} else {
		ENC_OFFS(bs, 2);
	}
	if (IS_NULL_ctype(cs)) {
		ENC_OFF(bs);
	}
	bs = enc_bool(bs,((ci & cinfo_union)? 1 : 0));
	if (!IS_NULL_ctype(cs)) {
		/* Run-time type information */
		if (vtags[1] == LINK_NONE) {
			ENC_OFFS(bs, 2);
		} else {
			ENC_ON(bs);
			vtags[3] = link_no(bs, vtags[3], VAR_dgtag);
			ENC_make_dg_tag(bs, vtags[3]);
			ENC_ON(bs);
			vtags[1] = link_no(bs, vtags[1], VAR_dgtag);
			ENC_make_dg_tag(bs, vtags[1]);
		}
	}
	bs = enc_bool(bs, LANGUAGE_CPP);
	if (!IS_NULL_ctype(cs)) {
		ENC_OFF(bs);
	}
	return bs;
}


/*
    This routine adds the definition of the enumeration type t to the
    bitstream bs.  force is 2 to indicate that a tag name should be
    output for this enumeration type.
*/

static BITSTREAM *
enc_dg_etype(BITSTREAM *bs, TYPE t, int force)
{
	ENUM_TYPE et = DEREF_etype(type_enumerate_defn(t));
	LIST(IDENTIFIER)p = DEREF_list(etype_values(et));
	CLASS_INFO ei = DEREF_cinfo(etype_info(et));
	if (!(ei & cinfo_complete) || force == 0) {
		t = DEREF_type(etype_rep(et));
		bs = enc_dg_type(bs, t, 0);
		return bs;
	}
	ENC_dg_enum_type(bs);
	ENC_LIST(bs, LENGTH_list(p));
	while (!IS_NULL_list(p)) {
		IDENTIFIER pid = DEREF_id(HEAD_list(p));
		EXP e = DEREF_exp(id_enumerator_value(pid));
		ENC_make_dg_enum(bs);
		bs = enc_exp(bs, e);
		bs = enc_dg_name(bs, pid, NULL_type);
		bs = enc_dg_loc(bs, id_loc(pid), id_loc(pid));
		p = TAIL_list(p);
	}
	if (force == 2) {
		/* Output tag name */
		IDENTIFIER eid = DEREF_id(etype_name(et));
		ENC_ON(bs);
		bs = enc_dg_name(bs, eid, NULL_type);
		ENC_ON(bs);
		bs = enc_dg_loc(bs, id_loc(eid), id_loc(eid));
	} else {
		ENC_OFFS(bs, 2);
	}
	bs = enc_shape(bs, t);
	bs = enc_bool(bs, LANGUAGE_CPP);
	return bs;
}


/*
    This routine adds the diagnostic information for the type t to the
    bitstream bs.
*/

BITSTREAM *
enc_dg_type(BITSTREAM *bs, TYPE t, int force)
{
	ulong n;
	CV_SPEC cv;
	if (IS_NULL_type(t)) {
		ENC_dg_void_type(bs);
		return bs;
	}
	cv = DEREF_cv(type_qual(t));
	if (cv & cv_const) {
		/* Allow for const qualifier */
		ENC_dg_qualified_type(bs);
		ENC_dg_const_qualifier(bs);
	}
	if (cv & cv_volatile) {
		/* Allow for volatile qualifier */
		ENC_dg_qualified_type(bs);
		ENC_dg_volatile_qualifier(bs);
	}

	/* Check type name */
	if (!force) {
		IDENTIFIER tid = DEREF_id(type_name(t));
		if (!IS_NULL_id(tid)) {
			tid = DEREF_id(id_alias(tid));
			n = DEREF_ulong(id_no(tid));
			if (n == LINK_NONE) {
				enc_dg_id(tid, 1);
				n = DEREF_ulong(id_no(tid));
				if (n == LINK_NONE) {
					goto type_label;
				}
			}
			ENC_dg_named_type(bs);
			n = link_no(bs, n, VAR_dgtag);
			ENC_make_dg_tag(bs, n);
			return bs;
		}
	}

	/* Encode type definition */
type_label: {
		    assert(ORDER_type == 18);
		    switch (TAG_type(t)) {
		    case type_integer_tag: {
			    /* Integral types */
			    INT_TYPE it = DEREF_itype(type_integer_rep(t));
			    n = DEREF_ulong(itype_diag(it));
			    goto basetype_lab;
		    }
basetype_lab: {
		      if (n == LINK_NONE) {
			      if (cv & cv_qual) {
				      t = qualify_type(t, cv_none, 0);
			      }
			      n = enc_dg_basetype(t, 1);
		      }
		      ENC_dg_named_type(bs);
		      n = link_no(bs, n, VAR_dgtag);
		      ENC_make_dg_tag(bs, n);
		      break;
	      }
		    case type_floating_tag: {
			    /* Floating point types */
			    FLOAT_TYPE ft = DEREF_ftype(type_floating_rep(t));
			    n = DEREF_ulong(ftype_diag(ft));
			    goto basetype_lab;
		    }
		    case type_top_tag:
		    case type_bottom_tag: {
			    /* Void types */
			    ENC_dg_void_type(bs);
			    break;
		    }
		    case type_ptr_tag: {
			    /* Pointer types */
			    TYPE s = DEREF_type(type_ptr_sub(t));
			    if (IS_type_top_etc(s)) {
				    /* Pointer void types */
				    cv = DEREF_cv(type_qual(s));
				    cv &= cv_qual;
				    n = diag_ptr_void[cv];
				    goto basetype_lab;
			    }
			    ENC_dg_pointer_type(bs);
			    bs = enc_dg_type(bs, s, 0);
			    ENC_OFF(bs);
			    break;
		    }
		    case type_ref_tag: {
			    /* Reference types */
			    TYPE s = DEREF_type(type_ref_sub(t));
			    ENC_dg_reference_type(bs);
			    bs = enc_dg_type(bs, s, 0);
			    break;
		    }
		    case type_ptr_mem_tag: {
			    /* Pointer to member types */
			    CLASS_TYPE cs = DEREF_ctype(type_ptr_mem_of(t));
			    TYPE s = DEREF_type(type_ptr_mem_sub(t));
			    if (IS_type_func(s)) {
				    ENC_dg_ptr_memfn_type(bs);
			    } else {
				    ENC_dg_ptr_memdata_type(bs);
			    }
			    bs = enc_dg_ctype(bs, cs);
			    bs = enc_dg_type(bs, s, 0);
			    bs = enc_shape(bs, t);
			    ENC_OFF(bs);
			    break;
		    }
		    case type_func_tag: {
			    /* Function types */
			    TYPE r = DEREF_type(type_func_ret(t));
			    int ell = DEREF_int(type_func_ellipsis(t));
			    CV_SPEC mqual = DEREF_cv(type_func_mqual(t));
			    LIST(TYPE)p = DEREF_list(type_func_ptypes(t));
			    LIST(TYPE)q = DEREF_list(type_func_mtypes(t));
			    unsigned nq = LENGTH_list(q);
			    ENC_dg_proc_type(bs);
			    ENC_LIST(bs, nq);
			    if (!EQ_list(p, q) && !IS_NULL_list(q)) {
				    /* Allow for 'this' parameter */
				    TYPE s = DEREF_type(HEAD_list(q));
				    ENC_dg_object_param(bs);
				    ENC_ON(bs);
				    bs = enc_dg_artificial(bs, "this");
				    ENC_OFFS(bs, 2);
				    bs = enc_dg_type(bs, s, 0);
				    ENC_OFF(bs);
				    q = TAIL_list(q);
			    }
			    while (!IS_NULL_list(q)) {
				    /* Real function parameters */
				    TYPE s = DEREF_type(HEAD_list(q));
				    if (ell & FUNC_PARAMS) {
					    s = unpromote_type(s);
				    }
				    ENC_dg_object_param(bs);
				    ENC_OFFS(bs, 3);
				    bs = enc_dg_type(bs, s, 0);
				    ENC_OFF(bs);
				    q = TAIL_list(q);
			    }
			    bs = enc_dg_type(bs, r, 0);
			    if (ell & FUNC_NON_PROTO) {
				    /* Non-prototype function */
				    ENC_ON(bs);
				    ENC_false(bs);
			    } else {
				    /* Prototype function */
				    ENC_OFF(bs);
			    }
			    ENC_OFF(bs);
			    if (mqual & cv_lang) {
				    /* Default language linkage */
				    ENC_OFF(bs);
			    } else {
				    /* Non-default language linkage */
				    ENC_ON(bs);
				    ENC_make_nat(bs);
				    ENC_INT(bs, DWARF_LANG_NOT);
			    }
			    if (ell & FUNC_ELLIPSIS) {
				    /* Ellipsis function */
				    ENC_ON(bs);
				    ENC_var_callers(bs);
			    } else {
				    /* Non-ellipsis function */
				    ENC_OFF(bs);
			    }
			    break;
		    }
		    case type_array_tag: {
			    /* Array types */
			    TYPE s = DEREF_type(type_array_sub(t));
			    NAT m = DEREF_nat(type_array_size(t));
			    ENC_dg_array_type(bs);
			    bs = enc_dg_type(bs, s, 0);
			    bs = enc_shape_offset(bs, s);
			    ENC_OFF(bs);
			    ENC_LIST_SMALL(bs, 1);
			    if (IS_NULL_nat(m)) {
				    ENC_dg_unspecified_dim(bs);
			    } else {
				    TYPE i = type_sint;
				    unsigned long v = get_nat_value(m);
				    ENC_dg_bounds_dim(bs);
				    ENC_dg_static_bound(bs);
				    bs = enc_make_int(bs, i, 0);
				    ENC_dg_static_bound(bs);
				    if (v < SMALL_ARRAY_BOUND) {
					    /* Small value */
					    if (v) {
						    v--;
					    }
					    bs = enc_make_int(bs, i, (int)v);
				    } else {
					    ENC_minus(bs);
					    bs = enc_error_treatment(bs, i);
					    ENC_make_int(bs);
					    bs = enc_variety(bs, i);
					    bs = enc_snat(bs, m, 0, 1);
					    bs = enc_make_int(bs, i, 1);
				    }
				    bs = enc_dg_type(bs, i, 0);
			    }
			    break;
		    }
		    case type_bitfield_tag: {
			    /* Bitfield types */
			    INT_TYPE bf = DEREF_itype(type_bitfield_defn(t));
			    TYPE s = DEREF_type(itype_bitfield_sub(bf));
			    ENC_dg_bitfield_type(bs);
			    bs = enc_dg_type(bs, s, 0);
			    bs = enc_bfvar(bs, t);
			    bs = enc_shape(bs, s);
			    break;
		    }
		    case type_compound_tag: {
			    /* Class types */
			    bs = enc_dg_class(bs, t, force);
			    break;
		    }
		    case type_enumerate_tag: {
			    /* Enumeration types */
			    bs = enc_dg_etype(bs, t, force);
			    break;
		    }
		    default: {
			    /* Other types */
			    ENC_dg_unknown_type(bs);
			    bs = enc_shape(bs, t);
			    break;
		    }
		    }
	    }
	    return bs;
}


/*
    This routine adds the diagnostic information for the local identifier
    id to the bitstream bs.  ts gives the encoding of the scope of id.
*/

BITSTREAM *
enc_dg_local(BITSTREAM *bs, IDENTIFIER id, BITSTREAM *ts)
{
	bs = enc_diag_start(bs);
	ENC_name_decl_dg(ts);
	ts = enc_dg_decl(ts, id, LINK_NONE, USAGE_DEFN);
	bs = enc_bitstream(bs, ts);
	return bs;
}


/*
    This routine adds the diagnostic information for the list of function
    parameters p to the bitstream bs.  ts and e give the function body.
*/

BITSTREAM *
enc_dg_params(BITSTREAM *bs, LIST(IDENTIFIER)p, BITSTREAM *ts, EXP e)
{
	bs = enc_diag_start(bs);
	ENC_list_dg(ts);
	ENC_LIST_SMALL(ts, 2);
	ENC_params_dg(ts);
	ENC_LIST(ts, LENGTH_list(p));
	while (!IS_NULL_list(p)) {
		IDENTIFIER pid = DEREF_id(HEAD_list(p));
		ts = enc_dg_decl(ts, pid, LINK_NONE, USAGE_DEFN);
		p = TAIL_list(p);
	}
	ENC_OFF(ts);
	ts = enc_dg_stmt(ts, e, 1);
	bs = enc_bitstream(bs, ts);
	return bs;
}


/*
    This routine adds the diagnostic information associated with the
    statement e to the bitstream bs.
*/

BITSTREAM *
enc_dg_stmt(BITSTREAM *bs, EXP e, int stmt)
{
	PTR(LOCATION)loc = crt_enc_loc;
	if (!IS_NULL_exp(e)) {
		switch (TAG_exp(e)) {
		case exp_sequence_tag: {
			/* Lexical block */
			int blk = DEREF_int(exp_sequence_block(e));
			NAMESPACE ns = DEREF_nspace(exp_sequence_decl(e));
			if (blk) {
				BITSTREAM *ts;
				unsigned m = 0;
				PTR(LOCATION)start_loc = block_loc(e, 0);
				ts = start_bitstream(NIL(FILE), bs->link);
				ts = enc_dg_namespace(ts, ns, &m, NULL_ctype);
				if (blk > 1) {
					m++;
				}
				if (m != 1) {
					ENC_list_dg(bs);
					ENC_LIST(bs, m);
				}
				if (blk > 1) {
					ENC_lexical_block_dg(bs);
					ENC_OFF(bs);
					bs = enc_dg_loc(bs, start_loc, loc);
				}
				bs = join_bitstreams(bs, ts);
				return bs;
			}
			break;
		}
		case exp_solve_stmt_tag: {
			EXP a = DEREF_exp(exp_solve_stmt_body(e));
			bs = enc_dg_stmt(bs, a, stmt);
			return bs;
		}
		case exp_decl_stmt_tag: {
			IDENTIFIER id = DEREF_id(exp_decl_stmt_id(e));
			loc = id_loc(id);
			break;
		}
		case exp_label_stmt_tag: {
			IDENTIFIER id = DEREF_id(exp_label_stmt_label(e));
			HASHID nm = DEREF_hashid(id_name(id));
			loc = id_loc(id);
			if (!IS_hashid_anon(nm)) {
				/* Named label */
				ENC_label_dg(bs);
				bs = enc_dg_name(bs, id, NULL_type);
				bs = enc_dg_loc(bs, loc, loc);
				return bs;
			}
			break;
		}
#if LANGUAGE_CPP
		case exp_try_block_tag: {
			/* Try block */
			EXP a;
			unsigned np;
			LIST(EXP)p;
			a = DEREF_exp(exp_try_block_ellipsis(e));
			p = DEREF_list(exp_try_block_handlers(e));
			np = LENGTH_list(p);
			if (IS_exp_handler(a)) {
				np++;
			}
			ENC_list_dg(bs);
			ENC_LIST_SMALL(bs, 2);
			ENC_exception_scope_dg(bs);
			ENC_LIST(bs, np);
			while (!IS_NULL_list(p)) {
				EXP b = DEREF_exp(HEAD_list(p));
				ulong m = capsule_no(NULL_string, VAR_dgtag);
				COPY_ulong(exp_handler_diag(b), m);
				m = link_no(bs, m, VAR_dgtag);
				ENC_make_dg_tag(bs, m);
				p = TAIL_list(p);
			}
			if (IS_exp_handler(a)) {
				ulong m = capsule_no(NULL_string, VAR_dgtag);
				COPY_ulong(exp_handler_diag(a), m);
				m = link_no(bs, m, VAR_dgtag);
				ENC_make_dg_tag(bs, m);
			}
			e = DEREF_exp(exp_try_block_body(e));
			bs = enc_dg_stmt(bs, e, stmt);
			return bs;
		}
		case exp_handler_tag: {
			/* Exception handler */
			ulong m = DEREF_ulong(exp_handler_diag(e));
			IDENTIFIER id = DEREF_id(exp_handler_except(e));
			record_usage(m, VAR_dgtag, USAGE_DEFN);
			ENC_list_dg(bs);
			ENC_LIST_SMALL(bs, 2);
			ENC_make_tag_dg(bs);
			m = link_no(bs, m, VAR_dgtag);
			ENC_make_dg_tag(bs, m);
			ENC_exception_handler_dg(bs);
			if (!IS_NULL_id(id)) {
				ENC_ON(bs);
				bs = enc_dg_decl(bs, id, LINK_NONE, USAGE_DEFN);
			} else {
				ENC_OFF(bs);
			}
			e = DEREF_exp(exp_handler_body(e));
			bs = enc_dg_stmt(bs, e, stmt);
			return bs;
		}
#endif
		}
	}
	if (stmt == 2) {
		/* Used to mark conditionals */
		ENC_list_dg(bs);
		ENC_LIST_SMALL(bs, 2);
		ENC_branch_dg(bs);
		bs = enc_dg_loc(bs, loc, loc);
	}
	ENC_singlestep_dg(bs);
	bs = enc_dg_loc(bs, loc, loc);
	return bs;
}


#endif /* TDF_OUTPUT && TDF_DIAG4 */
