/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#include "config.h"
#include "version.h"
#include "system.h"
#include "c_types.h"
#include "ctype_ops.h"
#include "etype_ops.h"
#include "exp_ops.h"
#include "graph_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "itype_ops.h"
#include "member_ops.h"
#include "nat_ops.h"
#include "nspace_ops.h"
#include "tok_ops.h"
#include "type_ops.h"
#include "virt_ops.h"
#include "error.h"
#include "tdf.h"
#include "basetype.h"
#include "buffer.h"
#include "capsule.h"
#include "compile.h"
#include "constant.h"
#include "diag.h"
#include "diag2.h"
#include "encode.h"
#include "exp.h"
#include "expression.h"
#include "function.h"
#include "initialise.h"
#include "mangle.h"
#include "print.h"
#include "shape.h"
#include "stmt.h"
#include "struct.h"
#include "tok.h"
#include "ustring.h"
#if TDF_OUTPUT


/*
    These variables give the standard tokens used in the diagnostic
    output.
*/

static ulong diag_id_scope_tok = LINK_NONE;
static ulong exp_to_source_tok = LINK_NONE;


/*
    This routine adds the diagnostic file name given by posn to the
    bitstream bs.
*/

static BITSTREAM *
enc_diag_file(BITSTREAM *bs, PTR(POSITION)posn)
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
		ts = enc_tokdef_start(n, "P", NIL(ulong), 0);
		ENC_make_filename(ts);
		ENC_make_nat(ts);
		ENC_INT(ts, date);
		ts = enc_ustring(ts, mn);
		ts = enc_ustring(ts, bn);
		enc_tokdef_end(n, ts);
	}

	/* Encode token application */
	ENC_filename_apply_token(bs);
	n = link_no(bs, n, VAR_token);
	ENC_make_tok(bs, n);
	ENC_LEN_SMALL(bs, 0);
	return bs;
}


/*
    This routine adds the diagnostic source mark given by loc to the
    bitstream bs.
*/

static BITSTREAM *
enc_diag_loc(BITSTREAM *bs, PTR(LOCATION)loc)
{
	ulong ln, cn;
	PTR(POSITION)posn;
	if (IS_NULL_ptr(loc)) {
		ln = builtin_loc.line;
		cn = builtin_loc.line;
		posn = builtin_loc.posn;
	} else {
		ln = DEREF_ulong(loc_line(loc));
		cn = DEREF_ulong(loc_column(loc));
		posn = DEREF_ptr(loc_posn(loc));
	}
	ENC_make_sourcemark(bs);
	bs = enc_diag_file(bs, posn);
	ENC_make_nat(bs);
	ENC_INT(bs, ln);
	ENC_make_nat(bs);
	ENC_INT(bs, cn);
	return bs;
}


/*
    This routine adds the name of the identifier id to the bitstream bs
    as a TDF string.
*/

BITSTREAM *
enc_diag_name(BITSTREAM *bs, IDENTIFIER id, int q)
{
	string s = mangle_diag(id, q);
	bs = enc_ustring(bs, s);
	return bs;
}


/*
    This routine encodes the start of a diagnostic tag definition for
    diagnostic tag number n.  It returns a bitstream to which the
    diagnostic type definition needs to be added.
*/

static BITSTREAM *
enc_diag_tagdef_start(ulong n)
{
	BITSTREAM *bs = start_bitstream(NIL(FILE), diagtype_unit->link);
	record_usage(n, VAR_diagtag, USAGE_DEFN);
	ENC_make_diag_tagdef(bs);
	n = link_no(bs, n, VAR_diagtag);
	ENC_INT(bs, n);
	return bs;
}


/*
    This routine completes the definition of a diagnostic tag.  bs is the
    result of a previous call to enc_diag_tagdef_start.
*/

static void
enc_diag_tagdef_end(BITSTREAM *bs)
{
	count_item(bs);
	diagtype_unit = join_bitstreams(diagtype_unit, bs);
	return;
}


/*
    This routine adds the list of diagnostic base classes given by br
    to the bitstream bs in reverse order.  A count of the number of bases
    is maintained in pm.
*/

static BITSTREAM *
enc_diag_bases(BITSTREAM *bs, LIST(GRAPH)br, unsigned *pm)
{
	if (!IS_NULL_list(br)) {
		GRAPH gs = DEREF_graph(HEAD_list(br));
		CLASS_TYPE cs = DEREF_ctype(graph_head(gs));
		IDENTIFIER cid = DEREF_id(ctype_name(cs));
		DECL_SPEC acc = DEREF_dspec(graph_access(gs));
		bs = enc_diag_bases(bs, TAIL_list(br), pm);
		bs = enc_diag_name(bs, cid, 0);
		bs = enc_base(bs, gs, 1);
		if (acc & dspec_virtual) {
			ENC_diag_ptr(bs);
			bs = enc_diag_ctype(bs, cs);
			ENC_diag_tq_null(bs);
		} else {
			bs = enc_diag_ctype(bs, cs);
		}
		(*pm)++;
	}
	return bs;
}


/*
    This routine adds the list of diagnostic class members given by mem
    to the bitstream bs in reverse order.  A count of the number of members
    is maintained in pm.
*/

static BITSTREAM *
enc_diag_mems(BITSTREAM *bs, MEMBER mem, unsigned *pm)
{
	if (!IS_NULL_member(mem)) {
		IDENTIFIER mid = DEREF_id(member_id(mem));
		TYPE s = DEREF_type(id_member_type(mid));
		mem = DEREF_member(member_next(mem));
		mem = next_data_member(mem, 2);
		bs = enc_diag_mems(bs, mem, pm);
		bs = enc_diag_name(bs, mid, 0);
		bs = enc_member(bs, mid);
		bs = enc_diag_type(bs, s, 0);
		(*pm)++;
	}
	return bs;
}


/*
    This routine adds the diagnostic information for the virtual function
    table vt to the bitstream bs.  A count of the number of items is
    maintained in pm.
*/

static BITSTREAM *
enc_diag_vtable(BITSTREAM *bs, VIRTUAL vt, unsigned *pm)
{
	while (!IS_NULL_virt(vt)) {
		OFFSET off = DEREF_off(virt_table_off(vt));
		if (IS_NULL_off(off)) {
			/* New virtual function table */
			ulong n = DEREF_ulong(virt_table_tok(vt));
			bs = enc_ustring(bs, ustrlit("__vptr"));
			ENC_exp_apply_token(bs);
			n = link_no(bs, n, VAR_token);
			ENC_make_tok(bs, n);
			ENC_LEN_SMALL(bs, 0);
			ENC_diag_ptr(bs);
			bs = enc_diag_special(bs, TOK_vtab_diag, VAR_diagtag);
			ENC_diag_tq_null(bs);
			(*pm)++;
		}
		vt = DEREF_virt(virt_next(vt));
	}
	return bs;
}


/*
    This list is used to hold all the classes which are used while they
    are incomplete.  A diagnostic tag is introduced for each such class
    which may be defined later if the class is completed.
*/

static LIST(CLASS_TYPE)diag_classes = NULL_list(CLASS_TYPE);


/*
    This routine defines a diagnostic tag for the class ct if it is complete
    or def is true.
*/

static ulong
enc_diag_class(CLASS_TYPE ct, int def)
{
	ulong tok = LINK_NONE;
	CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
	IDENTIFIER id = DEREF_id(ctype_name(ct));
	ulong n = DEREF_ulong(id_no(id));
	if (n == LINK_NONE) {
		/* Create diagnostic tag information */
		n = capsule_no(NULL_string, VAR_diagtag);
		COPY_ulong(id_no(id), n);
	}
	if ((ci & cinfo_complete) && (ci & cinfo_defined)) {
		/* Complete class */
		tok = compile_class(ct);
		def = 1;
	} else {
		/* Incomplete class */
		if (def) {
			tok = special_no(TOK_empty_shape);
		}
	}
	if (def) {
		/* Define diagnostic tag */
		unsigned m = 0;
		BITSTREAM *bs, *ts;
		GRAPH gr = DEREF_graph(ctype_base(ct));
		LIST(GRAPH)br = DEREF_list(graph_tails(gr));
		NAMESPACE ns = DEREF_nspace(ctype_member(ct));
		MEMBER mem = DEREF_member(nspace_ctype_first(ns));

		/* Encode diagnostic tag definition */
		bs = enc_diag_tagdef_start(n);
		ts = start_bitstream(NIL(FILE), bs->link);
		if (ci & cinfo_union) {
			ENC_diag_union(bs);
		} else {
			ENC_diag_struct(bs);
		}
		ENC_shape_apply_token(bs);
		tok = link_no(bs, tok, VAR_token);
		ENC_make_tok(bs, tok);
		ENC_LEN_SMALL(bs, 0);
		bs = enc_diag_name(bs, id, 1);
		mem = next_data_member(mem, 2);
		if (ci & cinfo_polymorphic) {
			VIRTUAL vt = DEREF_virt(ctype_virt(ct));
			ts = enc_diag_vtable(ts, vt, &m);
		}
		ts = enc_diag_mems(ts, mem, &m);
		ts = enc_diag_bases(ts, br, &m);
		ENC_LIST(bs, m);
		bs = join_bitstreams(bs, ts);
		enc_diag_tagdef_end(bs);
	} else {
		CONS_ctype(ct, diag_classes, diag_classes);
	}
	return n;
}


/*
    This routine defines the diagnostic tags for the incomplete classes
    in the list above.
*/

int
enc_diag_pending(void)
{
	int changed = 0;
	if (output_diag) {
		LIST(CLASS_TYPE)p;
#if TDF_DIAG4
		if (output_new_diag) {
			changed = enc_dg_pending();
			return changed;
		}
#endif
		while (p = diag_classes, !IS_NULL_list(p)) {
			diag_classes = NULL_list(CLASS_TYPE);
			while (!IS_NULL_list(p)) {
				CLASS_TYPE ct;
				DESTROY_CONS_ctype(destroy, ct, p, p);
				IGNORE enc_diag_class(ct, 1);
				changed = 1;
			}
		}
	}
	return changed;
}


/*
    This routine encodes the diagnostic information for the class type ct
    to the bitstream bs.
*/

BITSTREAM *
enc_diag_ctype(BITSTREAM *bs, CLASS_TYPE ct)
{
	IDENTIFIER id = DEREF_id(ctype_name(ct));
	ulong n = DEREF_ulong(id_no(id));
	if (n == LINK_NONE) {
		CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
		if (ci & cinfo_token) {
			/* Allow for tokenised types */
			TYPE t = DEREF_type(ctype_form(ct));
			bs = enc_diag_type(bs, t, 0);
			return bs;
		}
		n = enc_diag_class(ct, 0);
	}
	n = link_no(bs, n, VAR_diagtag);
	ENC_use_diag_tag(bs);
	ENC_make_diag_tag(bs, n);
	return bs;
}


/*
    This routine encodes the diagnostic information for the enumeration
    type et to the bitstream bs.  This is represented by a diagnostic tag.
*/

static BITSTREAM *
enc_diag_etype(BITSTREAM *bs, ENUM_TYPE et)
{
	IDENTIFIER id = DEREF_id(etype_name(et));
	ulong n = DEREF_ulong(id_no(id));
	if (n == LINK_NONE) {
		/* Decompose enumeration type */
		BITSTREAM *ts;
		TYPE t = DEREF_type(etype_rep(et));
		LIST(IDENTIFIER)p = DEREF_list(etype_values(et));
		CLASS_INFO ei = DEREF_cinfo(etype_info(et));
		if (!(ei & cinfo_complete)) {
			bs = enc_diag_type(bs, t, 0);
			return bs;
		}

		/* Encode diagnostic tag definition */
		n = capsule_no(NULL_string, VAR_diagtag);
		COPY_ulong(id_no(id), n);
		ts = enc_diag_tagdef_start(n);
		ENC_diag_enum(ts);
		ts = enc_diag_type(ts, t, 0);
		ts = enc_diag_name(ts, id, 1);
		ENC_LIST(ts, LENGTH_list(p));
		while (!IS_NULL_list(p)) {
			/* Scan through enumerators */
			IDENTIFIER pid = DEREF_id(HEAD_list(p));
			EXP e = DEREF_exp(id_enumerator_value(pid));
			ts = enc_exp(ts, e);
			ts = enc_diag_name(ts, pid, 1);
			p = TAIL_list(p);
		}
		enc_diag_tagdef_end(ts);
	}

	/* Encode diagnostic tag use */
	n = link_no(bs, n, VAR_diagtag);
	ENC_use_diag_tag(bs);
	ENC_make_diag_tag(bs, n);
	return bs;
}


/*
    This routine adds the diagnostic information for the tokenised type
    id ( args ) to the bitstream bs.
*/

static BITSTREAM *
enc_diag_tok_type(BITSTREAM *bs, IDENTIFIER id, LIST(TOKEN)args)
{
	if (IS_NULL_list(args)) {
		ulong n = get_diag_tag(id, VAR_token);
		if (n == LINK_NONE) {
			/* Find external name */
			string s = mangle_name(id, VAR_diagtag, 0);
			n = capsule_no(s, VAR_diagtag);
			set_diag_tag(id, VAR_token, n);
		}
		n = link_no(bs, n, VAR_diagtag);
		ENC_use_diag_tag(bs);
		ENC_make_diag_tag(bs, n);
	} else {
		/* NOT YET IMPLEMENTED */
		ENC_diag_type_null(bs);
	}
	return bs;
}


/*
    This routine adds the diagnostic type qualifiers cv to the bitstream bs.
*/

static BITSTREAM *
enc_diag_type_qual(BITSTREAM *bs, CV_SPEC cv)
{
	if (cv & cv_const) {
		ENC_add_diag_const(bs);
	}
	if (cv & cv_volatile) {
		ENC_add_diag_volatile(bs);
	}
	ENC_diag_tq_null(bs);
	return bs;
}


/*
    This routine adds the diagnostic information for the type t to the
    bitstream bs.  The type qualifiers are only output if qual is true.
*/

BITSTREAM *
enc_diag_type(BITSTREAM *bs, TYPE t, int qual)
{
	if (IS_NULL_type(t)) {
		ENC_diag_type_null(bs);
		return bs;
	}
	if (qual) {
		/* Output type qualifier */
		CV_SPEC cv = DEREF_cv(type_qual(t));
		if (cv & cv_qual) {
			ENC_diag_loc(bs);
			bs = enc_diag_type(bs, t, 0);
			bs = enc_diag_type_qual(bs, cv);
			return bs;
		}
	}
	ASSERT(ORDER_type == 18);
	switch (TAG_type(t)) {
	case type_integer_tag: {
		/* Integral types */
		ENC_diag_variety(bs);
		bs = enc_variety(bs, t);
		break;
	}
	case type_floating_tag: {
		/* Floating point types */
		ENC_diag_floating_variety(bs);
		bs = enc_flvar(bs, t);
		break;
	}
	case type_ptr_tag:
	case type_ref_tag: {
		/* Pointer types */
		TYPE s = DEREF_type(type_ptr_etc_sub(t));
		CV_SPEC cv = DEREF_cv(type_qual(s));
		ENC_diag_ptr(bs);
		bs = enc_diag_type(bs, s, 0);
		bs = enc_diag_type_qual(bs, cv);
		break;
	}
	case type_ptr_mem_tag: {
		/* Pointer to member types */
		int tok = TOK_pm_type;
		TYPE s = DEREF_type(type_ptr_mem_sub(t));
		if (IS_type_func(s)) {
			tok = TOK_pmf_type;
		}
		bs = enc_diag_special(bs, tok, VAR_diagtag);
		break;
	}
	case type_func_tag: {
		/* Function types */
		TYPE r = DEREF_type(type_func_ret(t));
		LIST(TYPE)p = DEREF_list(type_func_mtypes(t));
		int ell = DEREF_int(type_func_ellipsis(t));
		ENC_diag_proc(bs);
		ENC_LIST(bs, LENGTH_list(p));
		while (!IS_NULL_list(p)) {
			TYPE s = DEREF_type(HEAD_list(p));
			bs = enc_diag_type(bs, s, 0);
			p = TAIL_list(p);
		}
		bs = enc_bool(bs,(ell & FUNC_ELLIPSIS));
		bs = enc_diag_type(bs, r, 0);
		break;
	}
	case type_array_tag: {
		/* Array types */
		TYPE i = type_sint;
		TYPE s = DEREF_type(type_array_sub(t));
		NAT n = DEREF_nat(type_array_size(t));
		ENC_diag_array(bs);
		bs = enc_diag_type(bs, s, 0);
		bs = enc_shape_offset(bs, s);
		bs = enc_make_int(bs, i, 0);
		if (IS_NULL_nat(n)) {
			/* Empty array bound */
			bs = enc_make_int(bs, i, 0);
		} else {
			/* Calculated array bound */
			unsigned long v = get_nat_value(n);
			if (v < SMALL_ARRAY_BOUND) {
				/* Small value */
				if (v) {
					v--;
				}
				bs = enc_make_int(bs, i,(int)v);
			} else {
				ENC_minus(bs);
				bs = enc_error_treatment(bs, i);
				ENC_make_int(bs);
				bs = enc_variety(bs, i);
				bs = enc_snat(bs, n, 0, 1);
				bs = enc_make_int(bs, i, 1);
			}
		}
		bs = enc_diag_type(bs, i, 0);
		break;
	}
	case type_bitfield_tag: {
		/* Bitfield types */
		INT_TYPE bf = DEREF_itype(type_bitfield_defn(t));
		TYPE s = DEREF_type(itype_bitfield_sub(bf));
		NAT n = DEREF_nat(itype_bitfield_size(bf));
		ENC_diag_bitfield(bs);
		bs = enc_diag_type(bs, s, 0);
		bs = enc_nat(bs, n, 1);
		break;
	}
	case type_compound_tag: {
		/* Class types */
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		bs = enc_diag_ctype(bs, ct);
		break;
	}
	case type_enumerate_tag: {
		/* Enumeration types */
		ENUM_TYPE et = DEREF_etype(type_enumerate_defn(t));
		bs = enc_diag_etype(bs, et);
		break;
	}
	case type_token_tag: {
		/* Tokenised types */
		IDENTIFIER tok = DEREF_id(type_token_tok(t));
		LIST(TOKEN)args = DEREF_list(type_token_args(t));
		bs = enc_diag_tok_type(bs, tok, args);
		break;
	}
	default : {
		/* Other types */
		ENC_diag_type_null(bs);
		break;
	}
	}
	return bs;
}


/*
    This routine outputs any diagnostic information for the token id
    to the appropriate diagnostic units.  It is only called if id is
    defined.  The type t may be used to override the type of id.
*/

void
enc_diag_token(IDENTIFIER id, TYPE t)
{
	TOKEN tok;
#if TDF_DIAG4
	if (output_new_diag) {
		enc_dg_token(id, t);
		return;
	}
#endif
	tok = DEREF_tok(id_token_sort(id));
	if (IS_tok_type(tok)) {
		BASE_TYPE bt = DEREF_btype(tok_type_kind(tok));
		if (bt & btype_scalar) {
			/* Tokenised arithmetic types */
			/* EMPTY */
		} else {
			/* Tokenised generic types */
			BITSTREAM *bs;
			IDENTIFIER alt = DEREF_id(id_token_alt(id));
			DECL_SPEC ds = DEREF_dspec(id_storage(alt));
			ulong n = get_diag_tag(id, VAR_token);
			if (n == LINK_NONE) {
				/* Find external name */
				string s = mangle_name(id, VAR_diagtag, 0);
				n = capsule_no(s, VAR_diagtag);
				set_diag_tag(id, VAR_token, n);
			}
			bs = enc_diag_tagdef_start(n);
			if (IS_NULL_type(t)) {
				/* Extract type if not given */
				t = DEREF_type(tok_type_value(tok));
			}
			bs = enc_diag_type(bs, t, 0);
			enc_diag_tagdef_end(bs);
			if (!(ds & dspec_done)) {
				/* Output internal name */
				ds |= dspec_done;
				COPY_dspec(id_storage(alt), ds);
				enc_diag_id(alt, 1);
			}
		}
	}
	return;
}


/*
    This routine adds the diagnostic information for the global identifier
    id to the diagnostic definition unit.  def is true for a definition.
*/

void
enc_diag_id(IDENTIFIER id, int def)
{
	TYPE t;
	ulong n;
	BITSTREAM *bs = NULL;
#if TDF_DIAG4
	if (output_new_diag) {
		enc_dg_id(id, def);
		return;
	}
#endif
	UNUSED(def);
	n = DEREF_ulong(id_no(id));
	switch (TAG_id(id)) {
	case id_class_alias_tag:
	case id_enum_alias_tag:
	case id_type_alias_tag: {
		/* Typedef names */
		t = DEREF_type(id_class_name_etc_defn(id));
		bs = start_bitstream(NIL(FILE), diagdef_unit->link);
		ENC_diag_desc_typedef(bs);
		bs = enc_diag_name(bs, id, 1);
		bs = enc_diag_loc(bs, id_loc(id));
		bs = enc_diag_type(bs, t, 1);
		break;
	}
	case id_variable_tag:
	case id_parameter_tag:
	case id_stat_member_tag: {
		/* Variable names */
		t = DEREF_type(id_variable_etc_type(id));
		goto diag_label;
	}
	case id_function_tag:
	case id_mem_func_tag:
	case id_stat_mem_func_tag: {
		/* Function names */
		t = DEREF_type(id_function_etc_type(id));
		goto diag_label;
	}
diag_label: {
		     bs = start_bitstream(NIL(FILE), diagdef_unit->link);
		     ENC_diag_desc_id(bs);
		     bs = enc_diag_name(bs, id, 1);
		     bs = enc_diag_loc(bs, id_loc(id));
		     ENC_obtain_tag(bs);
		     n = link_no(bs, n, VAR_tag);
		     ENC_make_tag(bs, n);
		     bs = enc_diag_type(bs, t, 1);
		     break;
	     }
	}
	if (bs) {
		count_item(bs);
		diagdef_unit = join_bitstreams(diagdef_unit, bs);
	}
	return;
}


/*
    This routine adds the diagnostic information for the initialisation
    or termination function named s with tag number n to the diagnostics
    definition unit.
*/

void
enc_diag_init(const char *s, ulong n, TYPE t)
{
	if (output_all) {
		string u = ustrlit(s);
		n = capsule_name(n, &u, VAR_tag);
		if (u) {
			n = capsule_name(n, &u, VAR_tag);
		}
	}
	if (output_diag && !output_new_diag) {
		BITSTREAM *bs = start_bitstream(NIL(FILE), diagdef_unit->link);
		ENC_diag_desc_id(bs);
		bs = enc_ustring(bs, ustrlit(s));
		bs = enc_diag_loc(bs, NULL_ptr(LOCATION));
		ENC_obtain_tag(bs);
		n = link_no(bs, n, VAR_tag);
		ENC_make_tag(bs, n);
		bs = enc_diag_type(bs, t, 0);
		count_item(bs);
		diagdef_unit = join_bitstreams(diagdef_unit, bs);
	}
	return;
}


/*
    This routine adds the diagnostic information for the local identifier
    id to the bitstream bs.  ts gives the encoding of the scope of id.
*/

BITSTREAM *
enc_diag_local(BITSTREAM *bs, IDENTIFIER id, BITSTREAM *ts)
{
	TYPE t;
	ulong n, m;
#if TDF_DIAG4
	if (output_new_diag) {
		bs = enc_dg_local(bs, id, ts);
		return bs;
	}
#endif
	n = diag_id_scope_tok;
	if (n == LINK_NONE) {
		/* Assign token number */
		n = capsule_no(ustrlit("~diag_id_scope"), VAR_token);
		diag_id_scope_tok = n;
	}

	/* Add identifier information to ts */
	t = DEREF_type(id_variable_etc_type(id));
	ts = enc_diag_name(ts, id, 0);
	ENC_obtain_tag(ts);
	m = unit_no(ts, id, VAR_tag, 0);
	ENC_make_tag(ts, m);
	ts = enc_diag_type(ts, t, 1);

	/* Create a token application */
	ENC_exp_apply_token(bs);
	n = link_no(bs, n, VAR_token);
	ENC_make_tok(bs, n);
	bs = enc_bitstream(bs, ts);
	return bs;
}


/*
    This routine adds the diagnostic information for the list of function
    parameters p to the bitstream bs.  ts and e give the function body.
*/

BITSTREAM *
enc_diag_params(BITSTREAM *bs, LIST(IDENTIFIER)p, BITSTREAM *ts, EXP e)
{
#if TDF_DIAG4
	if (output_new_diag) {
		bs = enc_dg_params(bs, p, ts, e);
		return bs;
	}
#endif
	if (IS_NULL_list(p)) {
		bs = join_bitstreams(bs, ts);
	} else {
		IDENTIFIER pid = DEREF_id(HEAD_list(p));
		BITSTREAM *us = start_bitstream(NIL(FILE), bs->link);
		us = enc_diag_params(us, TAIL_list(p), ts, e);
		bs = enc_diag_local(bs, pid, us);
	}
	return bs;
}


/*
    This routine adds the token used to associate diagnostic information
    with a statement to the bitstream bs.
*/

BITSTREAM *
enc_diag_start(BITSTREAM *bs)
{
	ulong n = exp_to_source_tok;
	if (n == LINK_NONE) {
		/* Assign token number */
		string tok = ustrlit("~exp_to_source");
#if TDF_DIAG4
		if (output_new_diag) {
			tok = ustrlit("~dg_exp");
		}
#endif
		n = capsule_no(tok, VAR_token);
		exp_to_source_tok = n;
	}
	n = link_no(bs, n, VAR_token);
	ENC_exp_apply_token(bs);
	ENC_make_tok(bs, n);
	return bs;
}



/*
    This routine adds the start of a diagnostic statement e to the
    bitstream pointed to by pbs.
*/

BITSTREAM *
enc_diag_begin(BITSTREAM **pbs)
{
	BITSTREAM *bs = *pbs;
	if (output_diag) {
		bs = enc_diag_start(bs);
		*pbs = bs;
		bs = start_bitstream(NIL(FILE), bs->link);
	}
	return bs;
}


/*
    Not all statements are marked with diagnostic locations because they
    are revelant when single stepping through the program.  This routine
    checks whether diagnostics should be output for the statement e.
*/

int
is_diag_stmt(EXP e)
{
	if (!IS_NULL_exp(e)) {
		switch (TAG_exp(e)) {
		case exp_sequence_tag: {
			/* Lexical blocks */
			if (output_new_diag) {
				int blk = DEREF_int(exp_sequence_block(e));
				return blk;
			}
			return 0;
		}
		case exp_label_stmt_tag: {
			/* Labelled statements */
			if (output_new_diag) {
				IDENTIFIER lab =
				    DEREF_id(exp_label_stmt_label(e));
				HASHID nm = DEREF_hashid(id_name(lab));
				if (!IS_hashid_anon(nm)) {
					return 1;
				}
			}
			return 0;
		}
		case exp_if_stmt_tag: {
			/* If statements and expressions */
			if (output_diag) {
				IDENTIFIER lab = DEREF_id(exp_if_stmt_label(e));
				if (IS_NULL_id(lab)) {
					return 1;
				}
			}
			return 0;
		}
		case exp_decl_stmt_tag:
		case exp_while_stmt_tag:
		case exp_do_stmt_tag:
		case exp_switch_stmt_tag:
		case exp_hash_if_tag:
		case exp_try_block_tag:
		case exp_handler_tag: {
			/* Control statements */
			return 0;
		}
		}
	}
	return output_diag;
}


/*
    This routine adds the diagnostic information associated with the
    statement e to the bitstream bs.
*/

BITSTREAM *
enc_diag_stmt(BITSTREAM *bs, EXP e, int stmt)
{
	PTR(LOCATION)loc;
#if TDF_DIAG4
	if (output_new_diag) {
		bs = enc_dg_stmt(bs, e, stmt);
		return bs;
	}
#endif
	loc = crt_enc_loc;
	if (!IS_NULL_exp(e)) {
		switch (TAG_exp(e)) {
		case exp_decl_stmt_tag: {
			IDENTIFIER id = DEREF_id(exp_decl_stmt_id(e));
			loc = id_loc(id);
			break;
		}
		case exp_label_stmt_tag: {
			IDENTIFIER id = DEREF_id(exp_label_stmt_label(e));
			loc = id_loc(id);
			break;
		}
		}
	}
	bs = enc_diag_loc(bs, loc);
	bs = enc_diag_loc(bs, loc);
	UNUSED(stmt);
	return bs;
}


/*
    This routine adds the end of the diagnostic statement e to the
    bitstream bs.  ts gives the encoding of e.
*/

BITSTREAM *
enc_diag_end(BITSTREAM *bs, BITSTREAM *ts, EXP e, int stmt)
{
	if (output_diag) {
		ts = enc_diag_stmt(ts, e, stmt);
		ts = enc_bitstream(bs, ts);
	}
	return ts;
}


#endif /* TDF_OUTPUT */
