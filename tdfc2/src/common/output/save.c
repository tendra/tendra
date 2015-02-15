/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
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
#include "loc_ext.h"
#include "nat_ops.h"
#include "nspace_ops.h"
#include "off_ops.h"
#include "tok_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "basetype.h"
#include "bits.h"
#include "char.h"
#include "chktype.h"
#include "dump.h"
#include "encode.h"
#include "exception.h"
#include "file.h"
#include "inttype.h"
#include "save.h"
#include "syntax.h"
#include "ustring.h"


/*
    The following forward declarations are required in the spec output
    routines.
*/

static BITSTREAM *save_exp(BITSTREAM *, EXP, TYPE);
static BITSTREAM *save_type(BITSTREAM *, TYPE, IDENTIFIER);
static BITSTREAM *save_ctype(BITSTREAM *, CLASS_TYPE, IDENTIFIER);
static BITSTREAM *save_type_list(BITSTREAM *, LIST(TYPE));
static BITSTREAM *save_tok(BITSTREAM *, TOKEN, int);


/*
    These macros give the simple writing routines for the enumeration
    types etc.  Note that ENC_BITS_2 is used when the values occupy more
    than 16 bits.
*/

#define save_btype(A, B)	ENC_BITS_2((A), BITS_btype,(B))
#define save_cinfo(A, B)	ENC_BITS_2((A), BITS_cinfo,(B))
#define save_cusage(A, B)	ENC_BITS((A), BITS_cusage,(B))
#define save_cv(A, B)		ENC_BITS((A), BITS_cv_qual,(B))
#define save_dspec(A, B)	ENC_BITS_2((A), BITS_dspec,(B))
#define save_lex(A, B)		ENC_BITS((A), BITS_lex,(B))
#define save_mqual(A, B)	ENC_BITS((A), BITS_cv,(B))
#define save_ntype(A, B)	ENC_BITS((A), BITS_ntype,(B))
#define save_qual(A, B)		ENC_BITS((A), BITS_qual,(B))


/*
    This routine writes the list of preprocessing tokens p to the
    bitstream bs.
*/

static BITSTREAM *
save_pptoks(BITSTREAM *bs, PPTOKEN *p)
{
	/* NOT YET IMPLEMENTED */
	UNUSED(p);
	return bs;
}


/*
    This routine writes the location ploc to the bitstream bs.
*/

static BITSTREAM *
save_loc(BITSTREAM *bs, PTR(LOCATION)ploc)
{
	static LOCATION last_loc = NULL_loc;
	if (!IS_NULL_ptr(ploc)) {
		unsigned long ln = DEREF_ulong(loc_line(ploc));
		PTR(POSITION)posn = DEREF_ptr(loc_posn(ploc));
		if (EQ_ptr(posn, last_loc.posn) || IS_NULL_ptr(posn)) {
			if (ln == last_loc.line) {
				/* Same position */
				ENC_OFF(bs);
			} else {
				/* Different line */
				ENC_ON(bs);
				ENC_INT(bs, ln);
				ENC_OFF(bs);
				last_loc.line = ln;
			}
		} else {
			int eq =0;
			unsigned long off = DEREF_ulong(posn_offset(posn));
			string a1 = DEREF_string(posn_file(posn));
			string b1 = DEREF_string(posn_input(posn));
			if (!IS_NULL_ptr(last_loc.posn)) {
				string a2 =
				    DEREF_string(posn_file(last_loc.posn));
				string b2 =
				    DEREF_string(posn_input(last_loc.posn));
				if (ustreq(a1, a2) && ustreq(b1, b2)) {
					eq = 1;
				}
			}
			ENC_ON(bs);
			ENC_INT(bs, ln);
			ENC_ON(bs);
			ENC_INT(bs, off);
			if (eq) {
				/* Same file */
				ENC_OFF(bs);
			} else {
				ulong date;
				ENC_ON(bs);
				bs = enc_ustring(bs, a1);
				if (ustreq(a1, b1)) {
					/* Same file names */
					ENC_OFF(bs);
				} else {
					/* Different file names */
					ENC_ON(bs);
					bs = enc_ustring(bs, b1);
				}
				date = DEREF_ulong(posn_datestamp(posn));
				ENC_INT(bs, date);
			}
			last_loc.line = ln;
			last_loc.posn = posn;
		}
	} else {
		ENC_OFF(bs);
	}
	return bs;
}


/*
    This routine writes the identifier name nm to the bitstream bs.
    ns gives the current namespace.
*/

static BITSTREAM *
save_hashid(BITSTREAM *bs, HASHID nm, NAMESPACE ns)
{
	if (IS_NULL_hashid(nm)) {
		ENC_BITS(bs, BITS_hashid, 0);
	} else {
		unsigned tag = TAG_hashid(nm);
		ENC_BITS(bs, BITS_hashid, tag + 1);
		assert(ORDER_hashid == 7);
		switch (tag) {
		case hashid_name_tag:
		case hashid_ename_tag: {
			string s = DEREF_string(hashid_name_etc_text(nm));
			bs = enc_ustring(bs, s);
			break;
		}
		case hashid_constr_tag: {
			UNUSED(ns);
			break;
		}
		case hashid_destr_tag: {
			UNUSED(ns);
			break;
		}
		case hashid_conv_tag: {
			TYPE t = DEREF_type(hashid_conv_type(nm));
			bs = save_type(bs, t, NULL_id);
			break;
		}
		case hashid_op_tag: {
			int op = DEREF_int(hashid_op_lex(nm));
			save_lex(bs, op);
			break;
		}
		case hashid_anon_tag: {
			break;
		}
		}
	}
	return bs;
}


/*
    This routine saves a list of identifier names to the bitstream bs.
*/

static BITSTREAM *
save_hashid_list(BITSTREAM *bs, LIST(HASHID)p, NAMESPACE ns)
{
	while (!IS_NULL_list(p)) {
		HASHID nm = DEREF_hashid(HEAD_list(p));
		ENC_ON(bs);
		bs = save_hashid(bs, nm, ns);
		p = TAIL_list(p);
	}
	ENC_OFF(bs);
	return bs;
}


/*
    This routine writes the identifier number for the identifier id to
    the bitstream bs.  The spec and dump output formats share the same
    identifier numbers, with zero representing the null identifier.
*/

static BITSTREAM *
save_use(BITSTREAM *bs, IDENTIFIER id)
{
	ulong d = 0;
	if (!IS_NULL_id(id)) {
		d = DEREF_ulong(id_dump(id));
		if (d == LINK_NONE) {
			d = dump_id_next++;
			d |= LINK_EXTERN;
			COPY_ulong(id_dump(id), d);
		}
		d &= ~LINK_EXTERN;
	}
	ENC_INT(bs, d);
	return bs;
}


/*
    This routine saves a list of identifier numbers to the bitstream bs.
*/

static BITSTREAM *
save_use_list(BITSTREAM *bs, LIST(IDENTIFIER)p)
{
	while (!IS_NULL_list(p)) {
		IDENTIFIER id = DEREF_id(HEAD_list(p));
		ENC_ON(bs);
		bs = save_use(bs, id);
		p = TAIL_list(p);
	}
	ENC_OFF(bs);
	return bs;
}


/*
    This routine saves a list of identifiers to the bitstream bs.
*/

static BITSTREAM *
save_id_list(BITSTREAM *bs, LIST(IDENTIFIER)p, NAMESPACE ns)
{
	while (!IS_NULL_list(p)) {
		IDENTIFIER id = DEREF_id(HEAD_list(p));
		ENC_ON(bs);
		bs = save_id(bs, id, ns);
		p = TAIL_list(p);
	}
	ENC_OFF(bs);
	return bs;
}


/*
    This routine writes the list of tokens p to the bitstream bs.  def
    is as in save_tok.
*/

static BITSTREAM *
save_tok_list(BITSTREAM *bs, LIST(TOKEN)p, int def)
{
	while (!IS_NULL_list(p)) {
		TOKEN tok = DEREF_tok(HEAD_list(p));
		ENC_ON(bs);
		bs = save_tok(bs, tok, def);
		p = TAIL_list(p);
	}
	ENC_OFF(bs);
	return bs;
}


/*
    This routine writes the integer constant n to the bitstream bs.
*/

static BITSTREAM *
save_nat(BITSTREAM *bs, NAT n)
{
	unsigned tag;
	if (IS_NULL_nat(n)) {
		ENC_BITS(bs, BITS_nat, 0);
		return bs;
	}
	tag = TAG_nat(n);
	ENC_BITS(bs, BITS_nat, tag + 1);
	assert(ORDER_nat == 5);
	switch (tag) {
	case nat_small_tag: {
		unsigned v = DEREF_unsigned(nat_small_value(n));
		ENC_INT(bs, v);
		break;
	}
	case nat_large_tag: {
		LIST(unsigned)p = DEREF_list(nat_large_values(n));
		while (!IS_NULL_list(p)) {
			unsigned v = DEREF_unsigned(HEAD_list(p));
			ENC_ON(bs);
			ENC_INT(bs, v);
			p = TAIL_list(p);
		}
		ENC_OFF(bs);
		break;
	}
	case nat_calc_tag: {
		EXP e = DEREF_exp(nat_calc_value(n));
		bs = save_exp(bs, e, type_sint);
		break;
	}
	case nat_neg_tag: {
		NAT m = DEREF_nat(nat_neg_arg(n));
		bs = save_nat(bs, m);
		break;
	}
	case nat_token_tag: {
		IDENTIFIER tok = DEREF_id(nat_token_tok(n));
		LIST(TOKEN)args = DEREF_list(nat_token_args(n));
		bs = save_use(bs, tok);
		bs = save_tok_list(bs, args, 1);
		break;
	}
	}
	return bs;
}


/*
    This routine writes the offset off to the bitstream bs.
*/

static BITSTREAM *
save_off(BITSTREAM *bs, OFFSET off)
{
	/* NOT YET IMPLEMENTED */
	UNUSED(off);
	return bs;
}


/*
    This routine writes the expression e to the bitstream bs.
*/

static BITSTREAM *
save_exp(BITSTREAM *bs, EXP e, TYPE t)
{
	unsigned tag;
	if (IS_NULL_exp(e)) {
		ENC_BITS(bs, BITS_exp, 0);
		return bs;
	}
	tag = TAG_exp(e);
	ENC_BITS(bs, BITS_exp, tag + 1);
	switch (tag) {
	case exp_int_lit_tag: {
		NAT m = DEREF_nat(exp_int_lit_nat(e));
		unsigned etag = DEREF_unsigned(exp_int_lit_etag(e));
		bs = save_nat(bs, m);
		ENC_BITS(bs, BITS_exp, etag);
		break;
	}
	case exp_token_tag: {
		IDENTIFIER tok = DEREF_id(exp_token_tok(e));
		LIST(TOKEN)args = DEREF_list(exp_token_args(e));
		bs = save_use(bs, tok);
		bs = save_tok_list(bs, args, 1);
		break;
	}
	default: {
		/* NOT YET IMPLEMENTED */
		break;
	}
	}
	UNUSED(t);
	return bs;
}


/*
    This routine writes the integral type it to the bitstream bs.
*/

static BITSTREAM *
save_itype(BITSTREAM *bs, INT_TYPE it)
{
	unsigned tag;
	if (IS_NULL_itype(it)) {
		ENC_BITS(bs, BITS_itype, 0);
		return bs;
	}
	tag = TAG_itype(it);
	ENC_BITS(bs, BITS_itype, tag + 1);
	assert(ORDER_itype == 6);
	switch (tag) {
	case itype_basic_tag: {
		BUILTIN_TYPE nt = DEREF_ntype(itype_basic_no(it));
		save_ntype(bs, nt);
		break;
	}
	case itype_bitfield_tag: {
		NAT m = DEREF_nat(itype_bitfield_size(it));
		TYPE s = DEREF_type(itype_bitfield_sub(it));
		BASE_TYPE bt = DEREF_btype(itype_bitfield_rep(it));
		bs = save_type(bs, s, NULL_id);
		save_btype(bs, bt);
		bs = save_nat(bs, m);
		break;
	}
	case itype_promote_tag: {
		INT_TYPE is = DEREF_itype(itype_promote_arg(it));
		bs = save_itype(bs, is);
		break;
	}
	case itype_arith_tag: {
		INT_TYPE is = DEREF_itype(itype_arith_arg1(it));
		INT_TYPE ir = DEREF_itype(itype_arith_arg2(it));
		bs = save_itype(bs, is);
		bs = save_itype(bs, ir);
		break;
	}
	case itype_literal_tag: {
		NAT m = DEREF_nat(itype_literal_nat(it));
		int form = DEREF_int(itype_literal_form(it));
		int suff = DEREF_int(itype_literal_suff(it));
		bs = save_nat(bs, m);
		ENC_BITS(bs, 2, form);
		ENC_BITS(bs, 3, suff);
		break;
	}
	case itype_token_tag: {
		IDENTIFIER tok = DEREF_id(itype_token_tok(it));
		LIST(TOKEN)args = DEREF_list(itype_token_args(it));
		bs = save_use(bs, tok);
		bs = save_tok_list(bs, args, 1);
		break;
	}
	}
	return bs;
}


/*
    This routine writes the floating point type ft to the bitstream bs.
*/

static BITSTREAM *
save_ftype(BITSTREAM *bs, FLOAT_TYPE ft)
{
	unsigned tag;
	if (IS_NULL_ftype(ft)) {
		ENC_BITS(bs, BITS_ftype, 0);
		return bs;
	}
	tag = TAG_ftype(ft);
	ENC_BITS(bs, BITS_ftype, tag + 1);
	switch (tag) {
	case ftype_basic_tag: {
		BUILTIN_TYPE no = DEREF_ntype(ftype_basic_no(ft));
		save_ntype(bs, no);
		break;
	}
	case ftype_arg_promote_tag: {
		FLOAT_TYPE fs = DEREF_ftype(ftype_arg_promote_arg(ft));
		bs = save_ftype(bs, fs);
		break;
	}
	case ftype_arith_tag: {
		FLOAT_TYPE fs = DEREF_ftype(ftype_arith_arg1(ft));
		FLOAT_TYPE fr = DEREF_ftype(ftype_arith_arg2(ft));
		bs = save_ftype(bs, fs);
		bs = save_ftype(bs, fr);
		break;
	}
	case ftype_token_tag: {
		IDENTIFIER tok = DEREF_id(ftype_token_tok(ft));
		LIST(TOKEN)args = DEREF_list(ftype_token_args(ft));
		bs = save_use(bs, tok);
		bs = save_tok_list(bs, args, 1);
		break;
	}
	}
	return bs;
}


/*
    This routine writes the base class graph gr to the bitstream bs.
    The graph gt gives the top of the graph which is not output.
*/

static BITSTREAM *
save_graph(BITSTREAM *bs, GRAPH gr, GRAPH gt)
{
	LIST(GRAPH)br = DEREF_list(graph_tails(gr));
	if (!EQ_graph(gr, gt)) {
		CLASS_TYPE ct = DEREF_ctype(graph_head(gr));
		DECL_SPEC acc = DEREF_dspec(graph_access(gr));
		bs = save_ctype(bs, ct, NULL_id);
		save_dspec(bs, acc);
	}
	while (!IS_NULL_list(br)) {
		GRAPH gs = DEREF_graph(HEAD_list(br));
		ENC_ON(bs);
		bs = save_graph(bs, gs, gt);
		br = TAIL_list(br);
	}
	ENC_OFF(bs);
	return bs;
}


/*
    This routine writes the class type ct to the bitstream bs.  If def
    is not null then the full definition is written, otherwise just a use
    is written.
*/

static BITSTREAM *
save_ctype(BITSTREAM *bs, CLASS_TYPE ct, IDENTIFIER def)
{
	if (!IS_NULL_id(def)) {
		CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
		CLASS_USAGE cu = DEREF_cusage(ctype_usage(ct));
		GRAPH gr = DEREF_graph(ctype_base(ct));
		TYPE form = DEREF_type(ctype_form(ct));
		save_cinfo(bs, ci);
		save_cusage(bs, cu);
		bs = save_graph(bs, gr, gr);
		if (!IS_NULL_type(form)) {
			ENC_ON(bs);
			bs = save_type(bs, form, NULL_id);
		} else {
			ENC_OFF(bs);
		}
	} else {
		IDENTIFIER cid = DEREF_id(ctype_name(ct));
		bs = save_use(bs, cid);
	}
	return bs;
}


/*
    This routine writes the enumeration type et to the bitstream bs.  If
    def is not null then the full definition is written, otherwise just a
    use is written.
*/

static BITSTREAM *
save_etype(BITSTREAM *bs, ENUM_TYPE et, IDENTIFIER def)
{
	if (!IS_NULL_id(def)) {
		CLASS_INFO ei = DEREF_cinfo(etype_info(et));
		TYPE t = DEREF_type(etype_rep(et));
		TYPE form = DEREF_type(etype_form(et));
		save_cinfo(bs, ei);
		bs = save_type(bs, t, NULL_id);
		if (!IS_NULL_type(form)) {
			ENC_ON(bs);
			bs = save_type(bs, form, NULL_id);
		} else {
			ENC_OFF(bs);
		}
	} else {
		IDENTIFIER eid = DEREF_id(etype_name(et));
		bs = save_use(bs, eid);
	}
	return bs;
}


/*
    This routine writes the type t to the bitstream bs.  def is passed to
    save_ctype and save_etype.
*/

static BITSTREAM *
save_type(BITSTREAM *bs, TYPE t, IDENTIFIER def)
{
	CV_SPEC cv;
	unsigned tag;
	BUILTIN_TYPE nt = is_builtin_type(t, 1);
	if (nt != ntype_none) {
		/* Built-in types */
		ENC_ON(bs);
		cv = DEREF_cv(type_qual(t));
		save_cv(bs, cv);
		save_ntype(bs, nt);
		return bs;
	}
	ENC_OFF(bs);
	if (IS_NULL_type(t)) {
		/* Null types */
		ENC_BITS(bs, BITS_type, 0);
		return bs;
	}

	/* Save type independent fields */
	tag = TAG_type(t);
	ENC_BITS(bs, BITS_type, tag + 1);
	cv = DEREF_cv(type_qual(t));
	save_cv(bs, cv);

	/* Save type dependent fields */
	assert(ORDER_type == 18);
	switch (TAG_type(t)) {
	case type_pre_tag: {
		IDENTIFIER tid = DEREF_id(type_name(t));
		QUALIFIER qual = DEREF_qual(type_pre_nqual(t));
		BASE_TYPE bt = DEREF_btype(type_pre_rep(t));
		bs = save_use(bs, tid);
		save_qual(bs, qual);
		save_btype(bs, bt);
		break;
	}
	case type_integer_tag: {
		INT_TYPE it = DEREF_itype(type_integer_rep(t));
		INT_TYPE is = DEREF_itype(type_integer_sem(t));
		INT_TYPE ir = it;
		bs = save_itype(bs, it);
		if (IS_itype_promote(ir)) {
			/* Find default semantic type for it */
			ir = DEREF_itype(itype_promote_arg(ir));
		}
		if (EQ_itype(ir, is) || eq_itype(ir, is)) {
			/* Default semantics */
			ENC_OFF(bs);
		} else {
			/* Non-standard semantic type */
			ENC_ON(bs);
			bs = save_itype(bs, is);
		}
		break;
	}
	case type_floating_tag: {
		FLOAT_TYPE ft = DEREF_ftype(type_floating_rep(t));
		bs = save_ftype(bs, ft);
		break;
	}
	case type_top_tag:
	case type_bottom_tag: {
		/* Already handled */
		break;
	}
	case type_ptr_tag:
	case type_ref_tag: {
		TYPE s = DEREF_type(type_ptr_etc_sub(t));
		bs = save_type(bs, s, NULL_id);
		break;
	}
	case type_ptr_mem_tag: {
		CLASS_TYPE cs = DEREF_ctype(type_ptr_mem_of(t));
		TYPE s = DEREF_type(type_ptr_mem_sub(t));
		bs = save_ctype(bs, cs, NULL_id);
		bs = save_type(bs, s, NULL_id);
		break;
	}
	case type_func_tag: {
		TYPE r = DEREF_type(type_func_ret(t));
		LIST(IDENTIFIER)pids = DEREF_list(type_func_pids(t));
		int ell = DEREF_int(type_func_ellipsis(t));
		LIST(TYPE)p = DEREF_list(type_func_ptypes(t));
		LIST(TYPE)m = DEREF_list(type_func_mtypes(t));
		LIST(TYPE)ex = DEREF_list(type_func_except(t));
		CV_SPEC mqual = DEREF_cv(type_func_mqual(t));
		bs = save_type(bs, r, NULL_id);
		bs = save_id_list(bs, pids, NULL_nspace);
		ENC_BITS(bs, BITS_ellipsis, ell);
		save_mqual(bs, mqual);
		if (EQ_list(p, m)) {
			ENC_OFF(bs);
		} else {
			CLASS_TYPE cs;
			TYPE s = DEREF_type(HEAD_list(m));
			s = DEREF_type(type_ref_sub(s));
			cs = DEREF_ctype(type_compound_defn(s));
			ENC_ON(bs);
			bs = save_ctype(bs, cs, NULL_id);
		}
		if (EQ_list(ex, univ_type_set)) {
			ENC_OFF(bs);
		} else {
			ENC_ON(bs);
			bs = save_type_list(bs, ex);
		}
		break;
	}
	case type_array_tag: {
		TYPE s = DEREF_type(type_array_sub(t));
		NAT m = DEREF_nat(type_array_size(t));
		bs = save_type(bs, s, NULL_id);
		bs = save_nat(bs, m);
		break;
	}
	case type_bitfield_tag: {
		INT_TYPE it = DEREF_itype(type_bitfield_defn(t));
		bs = save_itype(bs, it);
		break;
	}
	case type_compound_tag: {
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		bs = save_ctype(bs, ct, def);
		break;
	}
	case type_enumerate_tag: {
		ENUM_TYPE et = DEREF_etype(type_enumerate_defn(t));
		bs = save_etype(bs, et, def);
		break;
	}
	case type_token_tag: {
		IDENTIFIER tok = DEREF_id(type_token_tok(t));
		LIST(TOKEN)args = DEREF_list(type_token_args(t));
		bs = save_use(bs, tok);
		bs = save_tok_list(bs, args, 1);
		break;
	}
	case type_templ_tag: {
		TOKEN tok = DEREF_tok(type_templ_sort(t));
		TYPE s = DEREF_type(type_templ_defn(t));
		int fix = DEREF_int(type_templ_fix(t));
		bs = save_tok(bs, tok, 0);
		bs = save_type(bs, s, def);
		ENC_BOOL(bs, fix);
		break;
	}
	case type_instance_tag: {
		IDENTIFIER tid = DEREF_id(type_name(t));
		IDENTIFIER id = DEREF_id(type_instance_id(t));
		DECL_SPEC acc = DEREF_dspec(type_instance_access(t));
		bs = save_use(bs, tid);
		bs = save_use(bs, id);
		save_dspec(bs, acc);
		break;
	}
	case type_dummy_tag: {
		int tok = DEREF_int(type_dummy_tok(t));
		ENC_INT(bs, tok);
		break;
	}
	case type_error_tag: {
		break;
	}
	}
	return bs;
}


/*
    This routine saves a list of types to the bitstream bs.
*/

static BITSTREAM *
save_type_list(BITSTREAM *bs, LIST(TYPE)p)
{
	while (!IS_NULL_list(p)) {
		TYPE t = DEREF_type(HEAD_list(p));
		ENC_ON(bs);
		bs = save_type(bs, t, NULL_id);
		p = TAIL_list(p);
	}
	ENC_OFF(bs);
	return bs;
}


/*
    This routine writes the token tok to the bitstream bs.  If def is
    true then the token value is included.
*/

static BITSTREAM *
save_tok(BITSTREAM *bs, TOKEN tok, int def)
{
	unsigned tag;
	if (IS_NULL_tok(tok)) {
		ENC_BITS(bs, BITS_tok, 0);
		return bs;
	}
	tag = TAG_tok(tok);
	ENC_BITS(bs, BITS_tok, tag + 1);
	assert(ORDER_tok == 10);
	switch (tag) {
	case tok_exp_tag: {
		TYPE t = DEREF_type(tok_exp_type(tok));
		int c = DEREF_int(tok_exp_constant(tok));
		bs = save_type(bs, t, NULL_id);
		ENC_BOOL(bs, c);
		if (def) {
			EXP e = DEREF_exp(tok_exp_value(tok));
			bs = save_exp(bs, e, t);
		}
		break;
	}
	case tok_stmt_tag: {
		if (def) {
			EXP e = DEREF_exp(tok_stmt_value(tok));
			bs = save_exp(bs, e, type_void);
		}
		break;
	}
	case tok_nat_tag:
	case tok_snat_tag: {
		if (def) {
			NAT m = DEREF_nat(tok_nat_etc_value(tok));
			bs = save_nat(bs, m);
		}
		break;
	}
	case tok_type_tag: {
		BASE_TYPE kind = DEREF_btype(tok_type_kind(tok));
		TYPE s = DEREF_type(tok_type_alt(tok));
		save_btype(bs, kind);
		bs = save_type(bs, s, NULL_id);
		if (def) {
			TYPE t = DEREF_type(tok_type_value(tok));
			bs = save_type(bs, t, NULL_id);
		}
		break;
	}
	case tok_func_tag: {
		TYPE t = DEREF_type(tok_func_type(tok));
		TOKEN proc = DEREF_tok(tok_func_proc(tok));
		bs = save_type(bs, t, NULL_id);
		bs = save_tok(bs, proc, 0);
		if (def) {
			IDENTIFIER id = DEREF_id(tok_func_defn(tok));
			bs = save_use(bs, id);
		}
		break;
	}
	case tok_member_tag: {
		TYPE s = DEREF_type(tok_member_of(tok));
		TYPE t = DEREF_type(tok_member_type(tok));
		bs = save_type(bs, s, NULL_id);
		bs = save_type(bs, t, NULL_id);
		if (def) {
			OFFSET off = DEREF_off(tok_member_value(tok));
			bs = save_off(bs, off);
		}
		break;
	}
	case tok_class_tag: {
		TYPE t = DEREF_type(tok_class_type(tok));
		TYPE s = DEREF_type(tok_class_alt(tok));
		bs = save_type(bs, t, NULL_id);
		bs = save_type(bs, s, NULL_id);
		if (def) {
			IDENTIFIER id = DEREF_id(tok_class_value(tok));
			bs = save_use(bs, id);
		}
		break;
	}
	case tok_proc_tag: {
		LIST(IDENTIFIER)bids;
		LIST(IDENTIFIER)pids;
		int key = DEREF_int(tok_proc_key(tok));
		TOKEN res = DEREF_tok(tok_proc_res(tok));
		bids = DEREF_list(tok_proc_bids(tok));
		pids = DEREF_list(tok_proc_pids(tok));
		bs = save_id_list(bs, bids, NULL_nspace);
		if (EQ_list(pids, bids)) {
			ENC_ON(bs);
		} else {
			ENC_OFF(bs);
			bs = save_use_list(bs, pids);
		}
		bs = save_tok(bs, res, def);
		if (key == lex_identifier) {
			ENC_OFF(bs);
		} else {
			ENC_ON(bs);
			save_lex(bs, key);
		}
		break;
	}
	case tok_templ_tag: {
		DECL_SPEC ex = DEREF_dspec(tok_templ_usage(tok));
		NAMESPACE pns = DEREF_nspace(tok_templ_pars(tok));
		save_dspec(bs, ex);
		if (!IS_NULL_nspace(pns)) {
			LIST(TOKEN)dargs;
			LIST(IDENTIFIER)pids;
			pids = DEREF_list(tok_templ_pids(tok));
			dargs = DEREF_list(tok_templ_dargs(tok));
			ENC_ON(bs);
			bs = save_id_list(bs, pids, NULL_nspace);
			bs = save_tok_list(bs, dargs, 1);
		} else {
			ENC_OFF(bs);
		}
		break;
	}
	}
	return bs;
}


/*
    This bitstream is used to write the spec output file.
*/

BITSTREAM *spec_unit = NULL;
static int written_spec = 0;
int output_spec = 0;


/*
    This routine writes the spec of the identifier id from the namespace ns
    to the bitstream bs.
*/

BITSTREAM *
save_id(BITSTREAM *bs, IDENTIFIER id, NAMESPACE ns)
{
	if (bs && output_spec) {
		bs = save_use(bs, id);
		if (!IS_NULL_id(id)) {
			/* Save identifier independent fields */
			unsigned tag = TAG_id(id);
			HASHID nm = DEREF_hashid(id_name(id));
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			IDENTIFIER lid = DEREF_id(id_alias(id));
			ENC_BITS(bs, BITS_id, tag + 1);
			bs = save_hashid(bs, nm, ns);
			save_dspec(bs, ds);
			bs = save_loc(bs, id_loc(id));
			if (EQ_id(id, lid)) {
				ENC_OFF(bs);
			} else {
				ENC_ON(bs);
				bs = save_use(bs, lid);
			}

			/* Save identifier dependent fields */
			assert(ORDER_id == 29);
			switch (tag) {
			case id_dummy_tag: {
				break;
			}
			case id_keyword_tag:
			case id_iso_keyword_tag:
			case id_reserved_tag: {
				int key = (int)DEREF_ulong(id_no(id));
				save_lex(bs, key);
				break;
			}
			case id_builtin_tag: {
				LIST(TYPE)p;
				TYPE r = DEREF_type(id_builtin_ret(id));
				p = DEREF_list(id_builtin_ptypes(id));
				bs = save_type(bs, r, NULL_id);
				bs = save_type_list(bs, p);
				break;
			}
			case id_obj_macro_tag: {
				PPTOKEN *def;
				def = DEREF_pptok(id_obj_macro_defn(id));
				bs = save_pptoks(bs, def);
				break;
			}
			case id_func_macro_tag: {
				PPTOKEN *def;
				LIST(HASHID)pars;
				def = DEREF_pptok(id_func_macro_defn(id));
				pars = DEREF_list(id_func_macro_params(id));
				bs = save_hashid_list(bs, pars, NULL_nspace);
				bs = save_pptoks(bs, def);
				break;
			}
			case id_predicate_tag: {
				/* NOT YET IMPLEMENTED */
				break;
			}
			case id_class_name_tag:
			case id_enum_name_tag: {
				TYPE t = DEREF_type(id_class_name_etc_defn(id));
				if (!(ds & dspec_implicit)) {
					bs = save_type(bs, t, id);
				}
				break;
			}
			case id_class_alias_tag:
			case id_enum_alias_tag:
			case id_type_alias_tag: {
				TYPE t = DEREF_type(id_class_name_etc_defn(id));
				bs = save_type(bs, t, NULL_id);
				break;
			}
			case id_nspace_name_tag: {
				break;
			}
			case id_nspace_alias_tag: {
				NAMESPACE pns;
				IDENTIFIER pid;
				pns = DEREF_nspace(id_nspace_alias_defn(id));
				pid = DEREF_id(nspace_name(pns));
				bs = save_use(bs, pid);
				break;
			}
			case id_variable_tag:
			case id_parameter_tag:
			case id_stat_member_tag: {
				TYPE t = DEREF_type(id_variable_etc_type(id));
				bs = save_type(bs, t, NULL_id);
				/* NOT YET IMPLEMENTED */
				break;
			}
			case id_function_tag:
			case id_mem_func_tag:
			case id_stat_mem_func_tag: {
				TYPE t = DEREF_type(id_function_etc_type(id));
				TYPE form = DEREF_type(id_function_etc_form(id));
				bs = save_type(bs, t, NULL_id);
				if (!IS_NULL_type(form)) {
					ENC_ON(bs);
					bs = save_type(bs, form, NULL_id);
				} else {
					ENC_OFF(bs);
				}
				/* NOT YET IMPLEMENTED */
				break;
			}
			case id_member_tag: {
				TYPE t = DEREF_type(id_member_type(id));
				bs = save_type(bs, t, NULL_id);
				/* NOT YET IMPLEMENTED */
				break;
			}
			case id_enumerator_tag: {
				EXP e;
				TYPE t;
				t = DEREF_type(id_enumerator_etype(id));
				e = DEREF_exp(id_enumerator_value(id));
				bs = save_type(bs, t, NULL_id);
				bs = save_exp(bs, e, t);
				break;
			}
			case id_label_tag:
			case id_weak_param_tag: {
				/* NOT YET IMPLEMENTED */
				break;
			}
			case id_token_tag: {
				TOKEN tok = DEREF_tok(id_token_sort(id));
				bs = save_tok(bs, tok, 0);
				break;
			}
			case id_ambig_tag: {
				LIST(IDENTIFIER)ids;
				int over = DEREF_int(id_ambig_over(id));
				ids = DEREF_list(id_ambig_ids(id));
				bs = save_use_list(bs, ids);
				ENC_BOOL(bs, over);
				break;
			}
			case id_undef_tag: {
				TYPE form = DEREF_type(id_undef_form(id));
				if (!IS_NULL_type(form)) {
					ENC_ON(bs);
					bs = save_type(bs, form, NULL_id);
				} else {
					ENC_OFF(bs);
				}
				break;
			}
			case id_pending_tag: {
				/* This shouldn't happen */
				break;
			}
			}
		}
	}
	return bs;
}


/*
    This routine marks the end of the namespace ns by writing the null
    identifier to the bitstream bs.
*/

BITSTREAM *
save_end(BITSTREAM *bs, NAMESPACE ns)
{
	bs = save_id(bs, NULL_id, ns);
	return bs;
}


/*
    This routine begins the writing of a spec file to the second output
    file.
*/

void
begin_spec(void)
{
	string nm = output_name[OUTPUT_SPEC];
	if (nm && !written_spec) {
		/* Open output file */
		FILE *f;
		BITSTREAM *bs;
		written_spec = 1;
		if (!open_output(OUTPUT_SPEC, binary_mode)) {
			fail(ERR_fail_spec(nm));
			spec_unit = NULL;
			term_error(0);
			return;
		}
		f = output_file[OUTPUT_SPEC];
		bs = start_bitstream(f, NULL_gen_ptr);

		/* Write file identifier */
		ENC_BITS(bs, BYTE_SIZE, ascii_T);
		ENC_BITS(bs, BYTE_SIZE, ascii_D);
		ENC_BITS(bs, BYTE_SIZE, ascii_F);
		ENC_BITS(bs, BYTE_SIZE, ascii_K);
		ENC_INT(bs, SPEC_major);
		ENC_INT(bs, SPEC_minor);
		ENC_INT(bs, LANGUAGE_CPP);
		ENC_ALIGN(bs);
		spec_unit = bs;
	}
	return;
}


/*
    This routine completes the output of a spec file.
*/

void
end_spec(void)
{
	BITSTREAM *bs = spec_unit;
	if (bs) {
		if (!output_spec)ENC_INT(bs, 0);
		end_bitstream(bs, 1);
		close_output(OUTPUT_SPEC);
		spec_unit = NULL;
	}
	return;
}
