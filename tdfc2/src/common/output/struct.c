/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/check.h>

#include "config.h"
#include "version.h"
#include "c_types.h"
#include "ctype_ops.h"
#include "exp_ops.h"
#include "graph_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "itype_ops.h"
#include "member_ops.h"
#include "nspace_ops.h"
#include "off_ops.h"
#include "type_ops.h"
#include "virt_ops.h"
#include "error.h"
#include "tdf.h"
#include "allocate.h"
#include "basetype.h"
#include "buffer.h"
#include "capsule.h"
#include "check.h"
#include "chktype.h"
#include "class.h"
#include "compile.h"
#include "constant.h"
#include "construct.h"
#include "derive.h"
#include "destroy.h"
#include "encode.h"
#include "exp.h"
#include "function.h"
#include "hash.h"
#include "init.h"
#include "initialise.h"
#include "interface.h"
#include "mangle.h"
#include "member.h"
#include "namespace.h"
#include "print.h"
#include "shape.h"
#include "struct.h"
#include "syntax.h"
#include "tok.h"
#include "token.h"
#include "virtual.h"
#if TDF_OUTPUT


/*
    Each node of a base class graph has three associated token numbers.
    The use of these numbers varies depending on whether the node is
    the top node of a graph, a virtual base class, or a non-virtual base
    class.  These macros give mnemonic values for these uses.  Names are
    also given to the various class type token numbers.
*/

#define ctype_shape(A)		ctype_tok1((A))
#define ctype_null_exp(A)	ctype_tok2((A))
#define graph_al_tag(A)		graph_tok1((A))
#define graph_core_off(A)	graph_tok2((A))
#define graph_base_off(A)	graph_tok1((A))
#define graph_real_off(A)	graph_tok2((A))


/*
    These types are dummies used in the class layout routines.
*/

TYPE dummy_class = NULL_type;
TYPE dummy_vtab = NULL_type;
TYPE dummy_count = NULL_type;
TYPE ptr_dummy_class = NULL_type;
TYPE ptr_dummy_vtab = NULL_type;
TYPE dummy_func = NULL_type;
ulong size_dummy_vtab = 0;
OFFSET off_size_t = NULL_off;
IDENTIFIER dummy_type_name = NULL_id;


/*
    This routine adds an application of the simple expression token n to
    the bitstream bs.
*/

static BITSTREAM *
enc_exp_token(BITSTREAM *bs, ulong n)
{
	ulong m = link_no(bs, n, VAR_token);
	ENC_exp_apply_token(bs);
	ENC_make_tok(bs, m);
	ENC_LEN_SMALL(bs, 0);
	return bs;
}


/*
    This routine adds an application of the simple shape token n to the
    bitstream bs.
*/

static BITSTREAM *
enc_shape_token(BITSTREAM *bs, ulong n)
{
	ulong m = link_no(bs, n, VAR_token);
	ENC_shape_apply_token(bs);
	ENC_make_tok(bs, m);
	ENC_LEN_SMALL(bs, 0);
	return bs;
}


/*
    The virtual function table and run-time type information routines are
    only included in the C++ producer.
*/

#if LANGUAGE_CPP


/*
    This routine adds the contents of the buffer bf to the bitstream bs
    as a string literal.
*/

static BITSTREAM *
enc_buffer(BITSTREAM *bs, BUFFER *bf)
{
	string s = bf->start;
	unsigned long n = (unsigned long)(bf->posn - s);

	/* Declare the string literal */
	ulong m = capsule_no(NULL_string, VAR_tag);
	BITSTREAM *ts = enc_tagdec_start(NULL_id, m, NULL_type, 1);
	ENC_nof(ts);
	ENC_make_nat(ts);
	ENC_INT(ts, n);
	ts = enc_shape(ts, type_char);
	enc_tagdec_end(ts);

	/* Define the string literal */
	ts = enc_tagdef_start(NULL_id, m, NULL_type, 1);
	ENC_make_nof_int(ts);
	ts = enc_variety(ts, type_char);
	ENC_make_string(ts);
	ts = enc_tdfstring(ts, n, s);
	enc_tagdef_end(ts);

	/* Encode the result */
	m = link_no(bs, m, VAR_tag);
	ENC_obtain_tag(bs);
	ENC_make_tag(bs, m);
	return bs;
}


/*
    This routine defines the run-time base class information for the base
    classes br or the sub-types pt and adds the address of the first base
    to bs.
*/

static BITSTREAM *
enc_rtti_bases(BITSTREAM *bs, LIST(GRAPH)br, LIST(TYPE)pt, NAT sz)
{
	TYPE t;
	ulong n, m;
	BITSTREAM *ts, *us;
	int a = INFO_public;

	if (!IS_NULL_list(br)) {
		/* Get base class information */
		VIRTUAL vt;
		CLASS_TYPE ct;
		GRAPH gr = DEREF_graph(HEAD_list(br));
		DECL_SPEC acc = DEREF_dspec(graph_access(gr));
		br = TAIL_list(br);

		/* Find base class information */
		ct = DEREF_ctype(graph_head(gr));
		t = make_class_type(ct);
		vt = DEREF_virt(ctype_virt(ct));
		if (!IS_NULL_virt(vt)) {
			/* Make sure base class is declared */
			int used = DEREF_int(virt_table_rtti_used(vt));
			if (!used) {
				IDENTIFIER cid = DEREF_id(ctype_name(ct));
				COPY_int(virt_table_rtti_used(vt), 1);
				compile_virtual(ct, !has_linkage(cid));
			}
		}
		if (acc & dspec_virtual) {
			sz = small_nat[1];
		}
		acc &= dspec_access;
		if (acc == dspec_protected) {
			a = INFO_protected;
		} else if (acc == dspec_private) {
			a = INFO_private;
		}
		m = DEREF_ulong(graph_base_off(gr));

	} else if (!IS_NULL_list(pt)) {
		/* Get sub-type information */
		t = DEREF_type(HEAD_list(pt));
		pt = TAIL_list(pt);
		if (!IS_NULL_type(t)) {
			CV_SPEC cv = DEREF_cv(type_qual(t));
			if (IS_type_func(t)) {
				/* Allow for function qualifiers */
				cv = DEREF_cv(type_func_mqual(t));
			}
			if (cv) {
				if (cv & cv_const) {
					a |= INFO_const;
				}
				if (cv & cv_volatile) {
					a |= INFO_volatile;
				}
				t = qualify_type(t, cv_none, 0);
			}
		}
		m = LINK_NONE;

	} else {
		/* Output end of list */
		ENC_make_null_ptr(bs);
		ENC_alignment(bs);
		bs = enc_special(bs, TOK_baseid_type);
		return bs;
	}

	/* Declare base structure */
	n = capsule_no(NULL_string, VAR_tag);
	ts = enc_tagdec_start(NULL_id, n, NULL_type, 1);
	ts = enc_special(ts, TOK_baseid_type);
	enc_tagdec_end(ts);

	/* Define base structure */
	ts = enc_tagdef_start(NULL_id, n, NULL_type, 1);
	ts = enc_special(ts, TOK_baseid_make);
	us = start_bitstream(NIL(FILE), ts->link);
	us = enc_rtti_type(us, t, lex_typeid);
	if (m == LINK_NONE) {
		ENC_offset_zero(us);
		us = enc_alignment(us, type_sint);
	} else {
		us = enc_exp_token(us, m);
	}
	us = enc_rtti_bases(us, br, pt, NULL_nat);
	us = enc_make_snat(us, a);
	us = enc_snat(us, sz, 0, 0);
	ts = enc_bitstream(ts, us);
	enc_tagdef_end(ts);

	/* Encode the result */
	n = link_no(bs, n, VAR_tag);
	ENC_obtain_tag(bs);
	ENC_make_tag(bs, n);
	return bs;
}


/*
    This routine defines the tag n to be the run-time type information
    structure for the type t.  If def is false then only the declaration
    is output.
*/

static void
enc_rtti_struct(TYPE t, ulong n, int def)
{
	unsigned acc = find_usage(n, VAR_tag);
	if (!(acc & USAGE_DECL)) {
		BITSTREAM *bs = enc_tagdec_start(NULL_id, n, NULL_type, 1);
		bs = enc_special(bs, TOK_typeid_type);
		enc_tagdec_end(bs);
	}
	if (def && !(acc & USAGE_DEFN)) {
		int c = RTTI_void;
		NAT sz = NULL_nat;
		BITSTREAM *bs, *ts;
		LIST(TYPE)p = NULL_list(TYPE);
		LIST(GRAPH)br = NULL_list(GRAPH);
		BUFFER *bf = clear_buffer(&print_buff, NIL(FILE));
		print_uniq_anon++;
		IGNORE print_type(t, bf, 0);
		print_uniq_anon--;
		bfputc(bf, 0);
		switch (TAG_type(t)) {
		case type_integer_tag: {
			/* Integral types */
			c = RTTI_integer;
			break;
		}
		case type_floating_tag: {
			/* Floating-point types */
			c = RTTI_float;
			break;
		}
		case type_ptr_tag: {
			/* Pointer types */
			TYPE s = DEREF_type(type_ptr_sub(t));
			CONS_type(s, p, p);
			c = RTTI_ptr;
			break;
		}
		case type_ref_tag: {
			/* Reference types */
			TYPE s = DEREF_type(type_ref_sub(t));
			CONS_type(s, p, p);
			c = RTTI_ref;
			break;
		}
		case type_ptr_mem_tag: {
			/* Pointer to member types */
			TYPE s = DEREF_type(type_ptr_mem_sub(t));
			CLASS_TYPE cs = DEREF_ctype(type_ptr_mem_of(t));
			CONS_type(s, p, p);
			s = make_class_type(cs);
			CONS_type(s, p, p);
			c = RTTI_ptr_mem;
			break;
		}
		case type_func_tag: {
			/* Function types */
			TYPE s = DEREF_type(type_func_ret(t));
			CV_SPEC mq = DEREF_cv(type_func_mqual(t));
			int ell = DEREF_int(type_func_ellipsis(t));
			LIST(TYPE)q = DEREF_list(type_func_ptypes(t));
			CONS_type(s, p, p);
			while (!IS_NULL_list(q)) {
				s = DEREF_type(HEAD_list(q));
				CONS_type(s, p, p);
				q = TAIL_list(q);
			}
			if (ell & FUNC_ELLIPSIS) {
				CONS_type(type_any, p, p);
			}
			p = REVERSE_list(p);
			if (mq & cv_c) {
				c = RTTI_c_func;
			} else {
				c = RTTI_func;
			}
			break;
		}
		case type_array_tag: {
			/* Array types */
			TYPE s = DEREF_type(type_array_sub(t));
			CONS_type(s, p, p);
			sz = DEREF_nat(type_array_size(t));
			c = RTTI_array;
			break;
		}
		case type_bitfield_tag: {
			/* Bitfield types */
			INT_TYPE it = DEREF_itype(type_bitfield_defn(t));
			TYPE s = DEREF_type(itype_bitfield_sub(it));
			CONS_type(s, p, p);
			sz = DEREF_nat(itype_bitfield_size(it));
			c = RTTI_bitfield;
			break;
		}
		case type_compound_tag: {
			/* Class types */
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
			CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
			GRAPH gr = DEREF_graph(ctype_base(ct));
			br = DEREF_list(graph_tails(gr));
			if (ci & cinfo_union) {
				c = RTTI_union;
			} else {
				c = RTTI_class;
			}
			break;
		}
		case type_enumerate_tag: {
			/* Enumeration types */
			c = RTTI_enum;
			break;
		}
		}
		bs = enc_tagdef_start(NULL_id, n, NULL_type, 1);
		bs = enc_special(bs, TOK_typeid_make);
		ts = start_bitstream(NIL(FILE), bs->link);
		ts = enc_make_snat(ts, c);
		ts = enc_buffer(ts, bf);
		ts = enc_rtti_bases(ts, br, p, sz);
		DESTROY_list(p, SIZE_type);
		bs = enc_bitstream(bs, ts);
		enc_tagdef_end(bs);
	}
	return;
}


/*
    These lists gives the tag numbers for the various type information
    structures output.  Polymorphic classes, which form the most common
    such types, are dealt with separately as part of the virtual function
    table.
*/

static LIST(TYPE)rtti_types = NULL_list(TYPE);
static LIST(ulong)rtti_tags = NULL_list(ulong);


/*
    This routine adds a reference to the run-time type information
    structure for the type t to the bitstream bs, defining this if
    necessary.
*/

BITSTREAM *
enc_rtti_type(BITSTREAM *bs, TYPE t, int op)
{
	ulong n = LINK_NONE;
	if (IS_NULL_type(t)) {
		/* Map null type to null pointer */
		ENC_make_null_ptr(bs);
		ENC_alignment(bs);
		bs = enc_special(bs, TOK_typeid_type);
		return bs;
	}
	if (op == lex_typeid && !output_rtti) {
		/* Use dummy type if RTTI suppressed */
		t = type_error;
	}
	switch (TAG_type(t)) {
	case type_top_tag:
	case type_bottom_tag:
	case type_integer_tag:
	case type_floating_tag:
	case type_pre_tag:
	case type_error_tag: {
		/* Built-in types */
		BITSTREAM *ts;
		bs = enc_special(bs, TOK_typeid_basic);
		ts = start_bitstream(NIL(FILE), bs->link);
		ts = enc_arith(ts, t, 1);
		bs = enc_bitstream(bs, ts);
		return bs;
	}
	case type_compound_tag: {
		/* Class types */
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
		if (ci & cinfo_polymorphic) {
			/* Polymorphic class types */
			int used;
			VIRTUAL vt = DEREF_virt(ctype_virt(ct));
			n = DEREF_ulong(virt_table_rtti(vt));
			if (n == LINK_NONE) {
				IGNORE compile_class(ct);
				n = DEREF_ulong(virt_table_rtti(vt));
			}
			used = DEREF_int(virt_table_rtti_used(vt));
			if (!used) {
				IDENTIFIER cid = DEREF_id(ctype_name(ct));
				COPY_int(virt_table_rtti_used(vt), 1);
				compile_virtual(ct, !has_linkage(cid));
			}
			if (op == lex_vtable) {
				/* Deal with virtual function tables */
				/* NOT YET IMPLEMENTED */
				n = DEREF_ulong(virt_table_tbl(vt));
				n = link_no(bs, n, VAR_tag);
				ENC_obtain_tag(bs);
				ENC_make_tag(bs, n);
				return bs;
			}
		} else {
			IGNORE compile_class(ct);
		}
		break;
	}
	}
	if (n == LINK_NONE) {
		/* Check for previous definition */
		LIST(TYPE)p = rtti_types;
		LIST(ulong)q = rtti_tags;
		while (!IS_NULL_list(p)) {
			TYPE s = DEREF_type(HEAD_list(p));
			if (eq_type(s, t)) {
				n = DEREF_ulong(HEAD_list(q));
				break;
			}
			q = TAIL_list(q);
			p = TAIL_list(p);
		}
		if (n == LINK_NONE) {
			/* Define a new structure */
			string s = NULL;
			if (output_all) {
				s = mangle_tname("__ti__", t);
			}
			n = capsule_no(s, VAR_tag);
			CONS_type(t, rtti_types, rtti_types);
			CONS_ulong(n, rtti_tags, rtti_tags);
			enc_rtti_struct(t, n, 1);
		}
	}
	n = link_no(bs, n, VAR_tag);
	ENC_obtain_tag(bs);
	ENC_make_tag(bs, n);
	return bs;
}


/*
    This routine adds the run-time type information expression e to
    the bitstream bs.
*/

BITSTREAM *
enc_rtti_exp(BITSTREAM *bs, EXP e)
{
	EXP a = DEREF_exp(exp_rtti_arg(e));
	EXP b = DEREF_exp(exp_rtti_except(e));
	int op = DEREF_int(exp_rtti_op(e));
	TYPE t = DEREF_type(exp_type(a));
	if (IS_type_ptr_etc(t)) {
		TYPE s = DEREF_type(type_ptr_etc_sub(t));
		if (IS_type_compound(s)) {
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(s));
			VIRTUAL vt = DEREF_virt(ctype_virt(ct));
			if (!IS_NULL_virt(vt)) {
				/* Pointer to polymorphic class */
				EXP a1;
				int used;
				OFFSET off;
				ulong n, m;
				BITSTREAM *ts;
				IGNORE compile_class(ct);
				off = DEREF_off(virt_table_off(vt));
				n = DEREF_ulong(virt_table_tok(vt));

				/* Introduce variable for pointer */
				a1 = DEREF_exp(exp_dummy_value(a));
				m = unit_no(bs, NULL_id, VAR_tag, 1);
				ENC_variable(bs);
				bs = enc_access(bs, crt_func_access);
				ENC_make_tag(bs, m);
				bs = enc_exp(bs, a);
				COPY_ulong(exp_dummy_no(a), m);
				COPY_exp(exp_dummy_value(a), NULL_exp);

				/* Check for null pointers */
				if (!IS_NULL_exp(b)) {
					ulong lab = unit_no(bs, NULL_id,
							    VAR_label, 1);
					ENC_SEQ_SMALL(bs, 1);
					ENC_conditional(bs);
					ENC_make_label(bs, lab);
					ENC_SEQ_SMALL(bs, 1);
					ENC_pointer_test(bs);
					ENC_OFF(bs);
					ENC_equal(bs);
					ENC_make_label(bs, lab);
					bs = enc_exp(bs, a);
					bs = enc_null_exp(bs, t);
					bs = enc_exp(bs, b);
					ENC_make_top(bs);
				}

				/* Find the run-time type information */
				ts = start_bitstream(NIL(FILE), bs->link);
				if (op == lex_typeid) {
					bs = enc_special(bs, TOK_typeid_ref);
				} else {
					bs = enc_special(bs, TOK_vtab_func);
				}
				ENC_add_to_ptr(ts);
				ts = enc_add_ptr(ts, a, LINK_NONE, off, 0);
				ts = enc_exp_token(ts, n);
				if (op != lex_typeid) {
					ENC_make_signed_nat(ts);
					ENC_OFF(ts);
					ENC_INT_SMALL(ts, 0);
				}
				bs = enc_bitstream(bs, ts);
				used = DEREF_int(virt_table_rtti_used(vt));
				if (!used) {
					IDENTIFIER cid = DEREF_id(ctype_name(ct));
					COPY_int(virt_table_rtti_used(vt), 1);
					compile_virtual(ct, !has_linkage(cid));
				}
				COPY_exp(exp_dummy_value(a), a1);
				return bs;
			}
		}
	}
	bs = enc_rtti_type(bs, t, op);
	return bs;
}


/*
    This routine adds the dynamic cast expression e to the bitstream bs.
*/

BITSTREAM *
enc_dyn_cast(BITSTREAM *bs, EXP e)
{
	ulong m;
	int used;
	OFFSET off;
	VIRTUAL vt;
	CLASS_TYPE ct;
	BITSTREAM *ts, *us;
	ulong r = LINK_NONE;
	TYPE t = DEREF_type(exp_type(e));
	EXP a = DEREF_exp(exp_dyn_cast_arg(e));
	TYPE s = DEREF_type(exp_type(a));
	EXP a1 = DEREF_exp(exp_dummy_value(a));
	EXP b = DEREF_exp(exp_dyn_cast_except(e));

	/* Introduce identity for argument */
	ulong n = unit_no(bs, NULL_id, VAR_tag, 1);
	ENC_identify(bs);
	bs = enc_access(bs, dspec_none);
	ENC_make_tag(bs, n);
	bs = enc_exp(bs, a1);
	COPY_exp(exp_dummy_value(a), NULL_exp);
	COPY_ulong(exp_dummy_no(a), n);

	/* Convert to result type */
	bs = enc_special(bs, TOK_from_ptr_void);
	ts = start_bitstream(NIL(FILE), bs->link);
	t = DEREF_type(type_ptr_etc_sub(t));
	ts = enc_alignment(ts, t);

	/* Introduce variable in exception case */
	if (!IS_NULL_exp(b)) {
		r = unit_no(ts, NULL_id, VAR_tag, 1);
		ENC_variable(ts);
		ts = enc_access(ts, crt_func_access);
		ENC_make_tag(ts, r);
	}

	/* Encode main token */
	ts = enc_special(ts, TOK_dynam_cast);
	us = start_bitstream(NIL(FILE), ts->link);

	/* Encode address of virtual function table */
	s = DEREF_type(type_ptr_etc_sub(s));
	ct = DEREF_ctype(type_compound_defn(s));
	IGNORE compile_class(ct);
	vt = DEREF_virt(ctype_virt(ct));
	off = DEREF_off(virt_table_off(vt));
	m = DEREF_ulong(virt_table_tok(vt));
	ENC_add_to_ptr(us);
	us = enc_add_ptr(us, a, LINK_NONE, off, 0);
	us = enc_exp_token(us, m);
	used = DEREF_int(virt_table_rtti_used(vt));
	if (!used) {
		IDENTIFIER cid = DEREF_id(ctype_name(ct));
		COPY_int(virt_table_rtti_used(vt), 1);
		compile_virtual(ct, !has_linkage(cid));
	}

	/* Output run-time type information */
	us = enc_rtti_type(us, t, lex_typeid);
	ts = enc_bitstream(ts, us);

	/* Check for exceptions */
	if (!IS_NULL_exp(b)) {
		ulong lab = unit_no(ts, NULL_id, VAR_label, 1);
		ENC_SEQ_SMALL(ts, 1);
		ENC_conditional(ts);
		ENC_make_label(ts, lab);
		ENC_SEQ_SMALL(ts, 1);
		ts = enc_special(ts, TOK_pv_test);
		us = start_bitstream(NIL(FILE), ts->link);
		ENC_contents(us);
		us = enc_special(us, TOK_ptr_void);
		ENC_obtain_tag(us);
		ENC_make_tag(us, r);
		ENC_make_label(us, lab);
		ENC_equal(us);
		ts = enc_bitstream(ts, us);
		ts = enc_exp(ts, b);
		ENC_make_top(ts);
		ENC_contents(ts);
		ts = enc_special(ts, TOK_ptr_void);
		ENC_obtain_tag(ts);
		ENC_make_tag(ts, r);
	}

	/* End conversion expression */
	bs = enc_bitstream(bs, ts);
	COPY_exp(exp_dummy_value(a), a1);
	return bs;
}


/*
    A list of all previously defined thunks is maintained to avoid
    unnecessary duplication.
*/

static VIRTUAL all_thunks = NULL_virt;


/*
    This routine creates a dummy function of type f which calls fid with
    its given arguments and returns its result with the base class conversion
    given by ret applied.  The tag number of the dummy function is returned.
    This is used for overriding virtual functions in which the return
    type differs.
*/

static ulong
make_thunk(TYPE f, IDENTIFIER fid, GRAPH ret)
{
	ulong n;
	DECL_SPEC acc = DEREF_dspec(graph_access(ret));
	IGNORE capsule_id(fid, VAR_tag);
	if (acc & dspec_ignore) {
		/* Use fid for trivial conversions */
		n = DEREF_ulong(id_no(fid));

	} else {
		EXP e;
		int ell;
		TYPE f2;
		OFFSET off;
		unsigned np;
		TYPE r1, r2;
		ulong rn, pn;
		LIST(TYPE)p;
		BITSTREAM *bs, *ts;

		/* Check previously defined thunks */
		VIRTUAL vt = all_thunks;
		while (!IS_NULL_virt(vt)) {
			IDENTIFIER vn = DEREF_id(virt_func(vt));
			if (EQ_id(vn, fid)) {
				GRAPH gv = DEREF_graph(virt_base(vt));
				if (EQ_graph(gv, ret)) {
					n = DEREF_ulong(virt_no(vt));
					return n;
				}
			}
			vt = DEREF_virt(virt_next(vt));
		}

		/* Find type information */
		while (IS_type_templ(f)) {
			f = DEREF_type(type_templ_defn(f));
		}
		r1 = DEREF_type(type_func_ret(f));
		p = DEREF_list(type_func_mtypes(f));
		np = LENGTH_list(p);
		ell = DEREF_int(type_func_ellipsis(f));
		f2 = DEREF_type(id_function_etc_type(fid));
		while (IS_type_templ(f2)) {
			f2 = DEREF_type(type_templ_defn(f2));
		}
		r2 = DEREF_type(type_func_ret(f2));

		/* Declare the thunk function */
		n = capsule_no(NULL_string, VAR_tag);
		enc_tagdec(NULL_id, n, f, 0);
		bs = enc_tagdef_start(NULL_id, n, f, 0);
		ts = start_bitstream(NIL(FILE), bs->link);
		ENC_make_proc(bs);
		bs = enc_shape(bs, r1);
		ENC_LIST(bs, np);
		ENC_LIST(ts, np);
		while (!IS_NULL_list(p)) {
			/* Scan through parameter types */
			TYPE pt = DEREF_type(HEAD_list(p));
			ulong m = unit_no(bs, NULL_id, VAR_tag, 1);
			ENC_contents(ts);
			if (pass_complex_type(pt)) {
				ENC_pointer(bs);
				bs = enc_alignment(bs, pt);
				ENC_pointer(ts);
				ts = enc_alignment(ts, pt);
			} else {
				bs = enc_shape(bs, pt);
				ts = enc_shape(ts, pt);
			}
			bs = enc_access(bs, dspec_none);
			ENC_make_tag(bs, m);
			ENC_obtain_tag(ts);
			ENC_make_tag(ts, m);
			p = TAIL_list(p);
		}
		if (ell & FUNC_ELLIPSIS) {
			/* Check for ellipsis */
			ulong m = unit_no(bs, NULL_id, VAR_tag, 1);
			ENC_ON(bs);
			ENC_make_tag(bs, m);
			bs = enc_access(bs, dspec_none);
			/* NOT YET IMPLEMENTED: use same_callees? */
		} else {
			ENC_OFF(bs);
		}
		ENC_OFF(ts);

		/* Output the function body */
		rn = unit_no(bs, NULL_id, VAR_tag, 1);
		MAKE_exp_dummy(r2, NULL_exp, rn, NULL_off, 1, e);
		ENC_variable(bs);
		bs = enc_access(bs, dspec_none);
		ENC_make_tag(bs, rn);
		ENC_apply_proc(bs);
		bs = enc_shape(bs, r2);
		pn = unit_no(bs, fid, VAR_tag, 0);
		ENC_obtain_tag(bs);
		ENC_make_tag(bs, pn);
		bs = join_bitstreams(bs, ts);
		if (IS_type_ptr(r2)) {
			/* Test for null pointers */
			ulong lab = unit_no(bs, NULL_id, VAR_label, 1);
			ENC_conditional(bs);
			ENC_make_label(bs, lab);
			ENC_SEQ_SMALL(bs, 1);
			bs = enc_compare(bs, e, NULL_exp, ntest_eq, lab, LINK_NONE);
			ENC_return(bs);
			bs = enc_null_exp(bs, r1);
		}
		ENC_return(bs);
		off = DEREF_off(graph_off(ret));
		bs = enc_add_ptr(bs, e, LINK_NONE, off, 1);
		enc_tagdef_end(bs);
		free_exp(e, 1);

		/* Add to list of all thunks */
		MAKE_virt_simple(fid, n, ret, vt);
		COPY_virt(virt_next(vt), all_thunks);
		all_thunks = vt;
	}
	return n;
}


/*
    This routine adds the shape of a virtual function table containing
    n functions to the bitstream bs.
*/

BITSTREAM *
enc_vtable_shape(BITSTREAM *bs, ulong n)
{
	BITSTREAM *ts;
	bs = enc_special(bs, TOK_vtab_type);
	ts = start_bitstream(NIL(FILE), bs->link);
	ENC_make_nat(ts);
	ENC_INT(ts, n + VIRTUAL_EXTRA);
	bs = enc_bitstream(bs, ts);
	return bs;
}


/*
    This routine encodes the definition of the virtual function table vt.
    n gives the tag number for the table, gr is the table offset and the
    flag inherited is true for secondary tables.  rtti gives the tag
    number for the run-time type information.
*/

static void
enc_vtable_defn(VIRTUAL vt, ulong n, CLASS_TYPE ct, GRAPH gr, int inherited,
		ulong rtti)
{
	ulong r;
	BITSTREAM *bs, *ts, *us;
	ulong m = DEREF_ulong(virt_no(vt));
	ulong p = DEREF_ulong(virt_table_tok(vt));
	OFFSET off = DEREF_off(virt_table_off(vt));
	LIST(VIRTUAL)pt = DEREF_list(virt_table_entries(vt));

	/* Output start of table */
	bs = enc_tagdef_start(NULL_id, n, NULL_type, 1);
	bs = enc_special(bs, TOK_vtab_make);
	ts = start_bitstream(NIL(FILE), bs->link);
	ENC_obtain_tag(ts);
	r = link_no(ts, rtti, VAR_tag);
	ENC_make_tag(ts, r);
	if (inherited) {
		/* Add base class offset */
		OFFSET off2 = DEREF_off(graph_off(gr));
		if (!is_zero_offset(off2)) {
			ENC_offset_add(ts);
			ts = enc_offset(ts, off2);
		}
	}
	if (!is_zero_offset(off)) {
		/* Add inherited table offset */
		ENC_offset_add(ts);
		ts = enc_offset(ts, off);
	}
	ts = enc_exp_token(ts, p);
	ENC_make_nat(ts);
	ENC_INT(ts, m + VIRTUAL_EXTRA);

	/* Output virtual functions */
	ENC_make_nof(ts);
	ENC_LIST(ts, m);
	while (!IS_NULL_list(pt)) {
		GRAPH gs;
		DECL_SPEC ds;
		IDENTIFIER fid;
		GRAPH ret = NULL_graph;
		IDENTIFIER pid = NULL_id;
		VIRTUAL at = DEREF_virt(HEAD_list(pt));
		while (IS_virt_link(at)) {
			/* Allow for symbolic links */
			at = DEREF_virt(DEREF_ptr(virt_link_to(at)));
		}
		if (inherited) {
			/* Allow for inherited function tables */
			VIRTUAL as;
			pid = DEREF_id(virt_func(at));
			as = find_overrider(ct, pid, gr, &ret);
			if (!IS_NULL_virt(as)) {
				at = as;
			}
		}
		fid = DEREF_id(virt_func(at));
		ds = DEREF_dspec(id_storage(fid));
		gs = DEREF_graph(virt_base(at));

		/* Output pointer to member function */
		ts = enc_special(ts, TOK_pmf_make);
		us = start_bitstream(NIL(FILE), ts->link);
		if (ds & dspec_pure) {
			/* Pure virtual function */
			us = enc_special(us, TOK_vtab_pure);
		} else {
			if (IS_NULL_graph(ret)) {
				IGNORE capsule_id(fid, VAR_tag);
				r = unit_no(us, fid, VAR_tag, 0);
			} else {
				TYPE f = DEREF_type(id_function_etc_type(pid));
				r = make_thunk(f, fid, ret);
				r = link_no(us, r, VAR_tag);
			}
			ENC_obtain_tag(us);
			ENC_make_tag(us, r);
		}
		us = enc_base(us, gs, 0);
		us = enc_base(us, gr, 0);
		ts = enc_bitstream(ts, us);
		pt = TAIL_list(pt);
	}
	bs = enc_bitstream(bs, ts);
	enc_tagdef_end(bs);
	return;
}


/*
    This routine defines or declares the virtual function tables for
    the class ct depending on the value of def.  The tables are given
    external names only if ext is true.
*/

void
define_vtable(CLASS_TYPE ct, int def, int ext)
{
	ulong r;
	int used;
	int have_main_table = 0;
	VIRTUAL vt = DEREF_virt(ctype_virt(ct));
	if (IS_NULL_virt(vt)) {
		return;
	}
	if (output_all) {
		ext = 1;
	}
	if (def == 2) {
		/* Force definition in this case */
		IGNORE compile_class(ct);
	} else {
		ulong n = DEREF_ulong(ctype_shape(ct));
		if (n == LINK_NONE) {
			return;
		}
	}

	/* Output run-time type information */
	r = DEREF_ulong(virt_table_rtti(vt));
	used = DEREF_int(virt_table_rtti_used(vt));
	if (used || def) {
		TYPE t = dummy_class;
		if (ext) {
			/* Make up external name */
			string s = mangle_typeid("__ti__", ct);
			r = capsule_name(r, &s, VAR_tag);
		}
		record_usage(r, VAR_tag, USAGE_USE);
		COPY_int(virt_table_rtti_used(vt), 1);
		COPY_ctype(type_compound_defn(t), ct);
		enc_rtti_struct(t, r, def);
	}

	/* Output virtual function tables */
	while (!IS_NULL_virt(vt)) {
		ulong n;
		VIRTUAL vs;
		unsigned acc;
		CLASS_TYPE cs;
		int inherited = 1;
		GRAPH gr = DEREF_graph(virt_base(vt));
		DECL_SPEC gacc = DEREF_dspec(graph_access(gr));
		if ((gacc & dspec_ignore) && !have_main_table) {
			/* Main virtual function table */
			gr = DEREF_graph(graph_top(gr));
			have_main_table = 1;
			inherited = 0;
		}
		cs = DEREF_ctype(graph_head(gr));
		vs = DEREF_virt(ctype_virt(cs));
		n = DEREF_ulong(virt_table_tbl(vt));
		record_usage(n, VAR_tag, USAGE_USE);
		acc = find_usage(n, VAR_tag);
		if (ext) {
			/* Make up external name */
			string s = mangle_vtable("__vt__", gr);
			n = capsule_name(n, &s, VAR_tag);
		}
		if (!(acc & USAGE_DECL)) {
			/* Output table declaration */
			ulong m = DEREF_ulong(virt_no(vs));
			BITSTREAM *ts = enc_tagdec_start(NULL_id, n, NULL_type,
							 1);
			ts = enc_vtable_shape(ts, m);
			enc_tagdec_end(ts);
		}
		if (def && !(acc & USAGE_DEFN)) {
			/* Output table definition */
			enc_vtable_defn(vs, n, ct, gr, inherited, r);
		}
		vt = DEREF_virt(virt_next(vt));
	}
	return;
}


/*
    This routine allocates tag and token numbers for the virtual function
    tables of the polymorphic class ct and its base classes.
*/

static ulong
declare_vtable(CLASS_TYPE ct)
{
	ulong n = LINK_NONE;
	ulong r = LINK_NONE;
	VIRTUAL vt = DEREF_virt(ctype_virt(ct));
	while (!IS_NULL_virt(vt)) {
		ulong t;
		OFFSET off;
		ulong m = DEREF_ulong(virt_table_tok(vt));
		if (m != LINK_NONE) {
			/* Already declared */
			return m;
		}
		off = DEREF_off(virt_table_off(vt));
		if (IS_NULL_off(off)) {
			/* New virtual function table required */
			m = capsule_no(NULL_string, VAR_token);
		} else if (IS_off_base(off)) {
			/* Use existing virtual function table */
			GRAPH gs = DEREF_graph(off_base_graph(off));
			CLASS_TYPE cs = DEREF_ctype(graph_head(gs));
			m = declare_vtable(cs);
		} else {
			/* Use existing virtual function table */
			GRAPH gs = DEREF_graph(off_deriv_graph(off));
			CLASS_TYPE cs = DEREF_ctype(graph_head(gs));
			m = declare_vtable(cs);
		}
		if (n == LINK_NONE) {
			n = m;
		}

		/* Allocate (but not define) virtual table tags */
		t = capsule_no(NULL_string, VAR_tag);
		clear_usage(t, VAR_tag);
		if (r == LINK_NONE) {
			r = capsule_no(NULL_string, VAR_tag);
			clear_usage(r, VAR_tag);
		}
		COPY_ulong(virt_table_tbl(vt), t);
		COPY_ulong(virt_table_rtti(vt), r);
		COPY_ulong(virt_table_tok(vt), m);
		vt = DEREF_virt(virt_next(vt));
	}
	return n;
}


/*
    The remaining routines are common to both the C and C++ producers.
*/

#endif /* LANGUAGE_CPP */


/*
    This routine finds the position of the virtual function id in the
    virtual function table vt.
*/

ulong
virtual_no(IDENTIFIER id, VIRTUAL vt)
{
	LIST(VIRTUAL)pv = DEREF_list(virt_table_entries(vt));
	while (!IS_NULL_list(pv)) {
		VIRTUAL vs = DEREF_virt(HEAD_list(pv));
		IDENTIFIER vid = DEREF_id(virt_func(vs));
		if (EQ_id(vid, id)) {
			ulong m = DEREF_ulong(virt_no(vs));
			return m + VIRTUAL_EXTRA;
		}
		pv = TAIL_list(pv);
	}
	return VIRTUAL_EXTRA;
}


/*
    This routine checks whether the type t represents a zero sized
    bitfield.  These force an alignment in a class rather than being
    a proper class member.
*/

static int
is_zero_bitfield(TYPE t)
{
	if (!IS_NULL_type(t) && IS_type_bitfield(t)) {
		INT_TYPE bf = DEREF_itype(type_bitfield_defn(t));
		DECL_SPEC ds = DEREF_dspec(itype_bitfield_info(bf));
		if (ds & dspec_pure) {
			return 1;
		}
	}
	return 0;
}


/*
    This routine adds the offset of the type t to the bitstream bs,
    unless t is dummy_class, when the offset of the type excluding the
    virtual bases is added.
*/

static BITSTREAM *
enc_offset_add(BITSTREAM *bs, TYPE t)
{
	if (EQ_type(t, dummy_class)) {
		/* Class offset */
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		GRAPH gr = DEREF_graph(ctype_base(ct));
		ulong m = DEREF_ulong(graph_core_off(gr));
		if (m != LINK_NONE) {
			bs = enc_exp_token(bs, m);
			return bs;
		}
	}
	ENC_shape_offset(bs);
	bs = enc_shape(bs, t);
	return bs;
}


/*
    This routine adds the offset of a structure member of type s
    which follows a member of type t with offset given by the token n
    to the bitstream bs.  Note that bitfield types are awkward.
*/

static BITSTREAM *
enc_offset_pad(BITSTREAM *bs, ulong n, TYPE t, TYPE s)
{
	BITSTREAM *ts;
	unsigned tag = null_tag;
	int z = is_zero_bitfield(t);
	if (!IS_NULL_type(s)) {
		if (is_zero_bitfield(s)) {
			/* Force an alignment */
			s = find_bitfield_type(s);
		}
		ENC_offset_pad(bs);
		bs = enc_alignment(bs, s);
		tag = TAG_type(s);
	}
	if (tag == type_bitfield_tag) {
		/* Use token for bitfields */
		bs = enc_special(bs, TOK_pad);
		ts = start_bitstream(NIL(FILE), bs->link);
	} else {
		ts = bs;
	}

	/* Add offset (except for zero sized bitfields) */
	if (!z) {
		ENC_offset_add(ts);
	}
	ts = enc_exp_token(ts, n);
	if (!z) {
		ts = enc_offset_add(ts, t);
	}

	/* Encode extra bitfield arguments */
	if (tag == type_bitfield_tag) {
		TYPE r = find_bitfield_type(s);
		ts = enc_shape(ts, r);
		ts = enc_shape(ts, s);
		bs = enc_bitstream(bs, ts);
	} else {
		bs = ts;
	}
	return bs;
}


/*
    This routine defines the alignment tag m to be the token n.  The value
    LINK_NONE for n is used to indicate an incomplete structure.
*/

static void
enc_al_tagdef(ulong m, ulong n)
{
	unsigned acc = find_usage(m, VAR_alignment);
	if (!(acc & USAGE_DEFN)) {
		BITSTREAM *bs = aldef_unit;
		ulong r = link_no(bs, m, VAR_alignment);
		ENC_make_al_tagdef(bs);
		ENC_INT(bs, r);
		if (n == LINK_NONE) {
			bs = enc_special(bs, TOK_empty_align);
		} else {
			ENC_alignment(bs);
			bs = enc_shape_token(bs, n);
		}
		record_usage(m, VAR_alignment, USAGE_DEFN);
		count_item(bs);
		aldef_unit = bs;
	}
	return;
}


/*
    This routine defines all the shape and offset tokens associated with
    the compound type ct.  It returns the external (capsule) number of
    a token giving the overall shape of the result.
*/

ulong
compile_class(CLASS_TYPE ct)
{
	ulong n = DEREF_ulong(ctype_shape(ct));
	if (n == LINK_NONE) {
		ulong m;
		HASHID nm;
		NAMESPACE ns;
		BITSTREAM *bs;
		BITSTREAM *ts;
		LIST(GRAPH)br;
		TYPE pt = NULL_type;
		int ext = output_all;
		ulong pm = LINK_NONE;
		ulong vo = LINK_NONE;
		unsigned no_mems = 0;
		unsigned no_bases = 0;
		DECL_SPEC macc = dspec_none;
		GRAPH gr = DEREF_graph(ctype_base(ct));
		CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
		CLASS_TYPE cd = DEREF_ctype(type_compound_defn(dummy_class));
#if LANGUAGE_CPP
		VIRTUAL vt = DEREF_virt(ctype_virt(ct));
#endif

		/* Check for tokenised types */
		if (ci & cinfo_token) {
			IDENTIFIER id = DEREF_id(ctype_name(ct));
			id = find_token(id);
			IGNORE enc_tokdef(id, 0);
			n = DEREF_ulong(id_no(id));
			COPY_ulong(ctype_shape(ct), n);
			return n;
		}

		/* Assign token number */
		n = capsule_no(NULL_string, VAR_token);
		COPY_ulong(ctype_shape(ct), n);

		/* Allow for recursive types */
		if (ci & cinfo_recursive) {
			m = DEREF_ulong(graph_al_tag(gr));
			if (m == LINK_NONE) {
				m = capsule_no(NULL_string, VAR_alignment);
				if (ext) {
					string s = mangle_typeid("~cpp.al.",
								 ct);
					m = capsule_name(m, &s, VAR_alignment);
				}
				COPY_ulong(graph_al_tag(gr), m);
			}
		}

		/* Assign virtual function tokens */
#if LANGUAGE_CPP
		if (!IS_NULL_virt(vt)) {
			OFFSET off = DEREF_off(virt_table_off(vt));
			if (!IS_NULL_off(off)) {
				vt = NULL_virt;
			}
			IGNORE declare_vtable(ct);
		}
#endif

		/* Scan through direct base classes */
		br = DEREF_list(graph_tails(gr));
		while (!IS_NULL_list(br)) {
			int virt = 0;
			GRAPH gs = DEREF_graph(HEAD_list(br));
			DECL_SPEC acc = DEREF_dspec(graph_access(gs));
			CLASS_TYPE cs = DEREF_ctype(graph_head(gs));

			/* Define offset token */
			IGNORE compile_class(cs);
			m = capsule_no(NULL_string, VAR_token);
			if (ext) {
				string s = mangle_vtable("~cpp.base.", gs);
				m = capsule_name(m, &s, VAR_token);
			}
			COPY_ulong(graph_base_off(gs), m);
			bs = enc_tokdef_start(m, "E", NIL(ulong), 1);
			if (pm == LINK_NONE) {
				/* First base class */
				ENC_offset_zero(bs);
				if (acc & dspec_virtual) {
					ENC_alignment(bs);
					ENC_pointer(bs);
					ENC_alignment(bs);
					ENC_top(bs);
					virt = 1;
				} else {
					bs = enc_al_ctype(bs, cs);
				}
			} else {
				/* Subsequent base classes */
				ENC_offset_pad(bs);
				if (acc & dspec_virtual) {
					ENC_alignment(bs);
					ENC_pointer(bs);
					ENC_alignment(bs);
					ENC_top(bs);
					virt = 1;
				} else {
					bs = enc_al_ctype(bs, cs);
				}
				ENC_offset_add(bs);
				bs = enc_exp_token(bs, pm);
				bs = enc_offset_add(bs, pt);
			}
			enc_tokdef_end(m, bs);

			/* Find member type */
			pt = dummy_class;
			COPY_ctype(type_compound_defn(pt), cs);
			if (virt) {
				pt = ptr_dummy_class;
			} else {
				no_bases++;
			}
			pm = m;
			br = TAIL_list(br);
		}

		/* Scan through data members */
		ts = start_bitstream(NIL(FILE), tokdef_unit->link);
		ns = DEREF_nspace(ctype_member(ct));
		if (output_order) {
			macc = dspec_public;
		}
		do {
			DECL_SPEC nacc = dspec_none;
			MEMBER mem = DEREF_member(nspace_ctype_first(ns));
			mem = next_data_member(mem, 1);
			while (!IS_NULL_member(mem)) {
				unsigned real_mem = 1;
				IDENTIFIER mid = DEREF_id(member_id(mem));
				TYPE t = DEREF_type(id_member_type(mid));
				if (ci & cinfo_union) {
					/* Union types */
					m = LINK_ZERO;
					if (!IS_NULL_type(pt)) {
						ENC_offset_max(ts);
						ENC_shape_offset(ts);
						ts = enc_shape(ts, pt);
					}
					no_mems = 1;
				} else {
					/* Structure types */
					if (macc) {
						/* Check member access */
						DECL_SPEC acc = DEREF_dspec(id_storage(mid));
						acc &= dspec_access;
						if (acc != macc) {
							mem = DEREF_member(member_next(mem));
							mem = next_data_member(mem, 1);
							if (acc > macc) {
								/* Find next access to check */
								if (acc == dspec_protected) {
									nacc = dspec_protected;
								} else if (nacc == dspec_none) {
									nacc = dspec_private;
								}
							}
							continue;
						}
					}
					m = DEREF_ulong(id_no(mid));
					if (m == LINK_NONE) {
						m = capsule_no(NULL_string, VAR_token);
						if (ext) {
							string s = mangle_name(mid, VAR_token, 0);
							m = capsule_name(m, &s, VAR_token);
						}
						bs = enc_tokdef_start(m, "E", NIL(ulong), 1);
						if (pm == LINK_NONE) {
							/* First member */
							if (IS_type_bitfield(t)) {
								/* Bitfield members */
								TYPE r = find_bitfield_type(t);
								if (!is_zero_bitfield(t)) {
									ENC_offset_pad(bs);
									bs = enc_alignment(bs, t);
								}
								ENC_offset_zero(bs);
								bs = enc_alignment(bs, r);
								nm = DEREF_hashid(id_name(mid));
								if (IS_hashid_anon(nm))real_mem = 0;
							} else {
								/* Non-bitfield members */
								ENC_offset_zero(bs);
								bs = enc_alignment(bs, t);
							}
						} else {
							/* Subsequent members */
							bs = enc_offset_pad(bs, pm, pt, t);
							if (IS_type_bitfield(t)) {
								nm = DEREF_hashid(id_name(mid));
								if (IS_hashid_anon(nm))real_mem = 0;
							}
						}
						enc_tokdef_end(m, bs);
					}
					no_mems += real_mem;
					pm = m;
				}
				COPY_ulong(id_no(mid), m);
				pt = t;
				mem = DEREF_member(member_next(mem));
				mem = next_data_member(mem, 1);
			}
			macc = nacc;
		} while (macc);

		/* Allow for virtual function table */
#if LANGUAGE_CPP
		if (!IS_NULL_virt(vt)) {
			TYPE t = ptr_dummy_vtab;
			m = DEREF_ulong(virt_table_tok(vt));
			if (ext) {
				string s = mangle_typeid("~cpp.vptr.", ct);
				m = capsule_name(m, &s, VAR_token);
			}
			size_dummy_vtab = DEREF_ulong(virt_no(vt));
			bs = enc_tokdef_start(m, "E", NIL(ulong), 1);
			if (pm == LINK_NONE) {
				ENC_offset_zero(bs);
				bs = enc_alignment(bs, t);
			} else {
				bs = enc_offset_pad(bs, pm, pt, t);
			}
			enc_tokdef_end(m, bs);
			pt = t;
			pm = m;
			no_bases++;
		}
#endif

		/* Scan through virtual bases */
		br = DEREF_list(ctype_vbase(ct));
		while (!IS_NULL_list(br)) {
			GRAPH gs = DEREF_graph(HEAD_list(br));
			CLASS_TYPE cs = DEREF_ctype(graph_head(gs));

			/* Define offset token */
			IGNORE compile_class(cs);
			m = capsule_no(NULL_string, VAR_token);
			if (ext) {
				string s = mangle_vtable("~cpp.virt.", gs);
				m = capsule_name(m, &s, VAR_token);
			}
			bs = enc_tokdef_start(m, "E", NIL(ulong), 1);
			ENC_offset_pad(bs);
			bs = enc_al_ctype(bs, cs);
			ENC_offset_add(bs);
			bs = enc_exp_token(bs, pm);
			bs = enc_offset_add(bs, pt);
			enc_tokdef_end(m, bs);
			do {
				/* All copies have the same real offset */
				COPY_ulong(graph_real_off(gs), m);
				gs = DEREF_graph(graph_equal(gs));
			} while (!IS_NULL_graph(gs));
			if (vo == LINK_NONE) {
				vo = m;
			}
			pt = dummy_class;
			COPY_ctype(type_compound_defn(pt), cs);
			pm = m;
			no_bases++;
			br = TAIL_list(br);
		}

		/* Define the overall shape token */
		no_mems += no_bases;
		if (no_mems) {
			/* Non-empty structure offset definition */
			m = capsule_no(NULL_string, VAR_token);
			if (ext) {
				string s = mangle_typeid("~cpp.off.", ct);
				m = capsule_name(m, &s, VAR_token);
			}
			bs = enc_tokdef_start(m, "E", NIL(ulong), 1);
			bs = enc_special(bs, TOK_comp_off);
			if (ci & cinfo_union) {
				/* Complete union definition */
				ENC_shape_offset(ts);
				ts = enc_shape(ts, pt);
			} else {
				/* Complete structure definition */
				ts = enc_offset_pad(ts, pm, pt, NULL_type);
			}
			bs = enc_bitstream(bs, ts);
			enc_tokdef_end(m, bs);

			/* Record offset of non-virtual components */
			if (vo == LINK_NONE) {
				vo = m;
			}
			COPY_ulong(graph_core_off(gr), vo);

			/* Non-empty structure shape definition */
			if (ext) {
				string s = mangle_typeid("~cpp.sh.", ct);
				n = capsule_name(n, &s, VAR_token);
			}
			bs = enc_tokdef_start(n, "S", NIL(ulong), 1);
			ENC_compound(bs);
			bs = enc_exp_token(bs, m);
			enc_tokdef_end(n, bs);
			ci &= ~cinfo_empty;

		} else {
			/* Empty structure definition */
			clear_usage(n, VAR_token);
			n = special_no(TOK_empty_shape);
			COPY_ulong(ctype_shape(ct), n);
			vo = special_no(TOK_empty_offset);
			COPY_ulong(graph_core_off(gr), vo);
			ci |= cinfo_empty;
		}
		COPY_cinfo(ctype_info(ct), ci);

		/* Define associated alignment tag */
		m = DEREF_ulong(graph_al_tag(gr));
		if (m != LINK_NONE) {
			enc_al_tagdef(m, n);
		}
		COPY_ctype(type_compound_defn(dummy_class), cd);
	}
	return n;
}


/*
    This routine adds the class type ct to the bitstream bs as a TDF SHAPE.
*/

BITSTREAM *
enc_ctype(BITSTREAM *bs, CLASS_TYPE ct)
{
	ulong n = compile_class(ct);
	bs = enc_shape_token(bs, n);
	return bs;
}


/*
    This list is used to hold all the classes which are used while they
    are incomplete.  An alignment tag is introduced for each such class
    which may be defined later if the class is completed.
*/

static LIST(CLASS_TYPE)incompl_classes = NULL_list(CLASS_TYPE);


/*
    This routine defines the alignment tags for the incomplete classes
    in this list above.  Note that the class is not compiled if it has
    not already been so.
*/

void
compile_incompl(void)
{
	LIST(CLASS_TYPE)p = incompl_classes;
	while (!IS_NULL_list(p)) {
		CLASS_TYPE ct = DEREF_ctype(HEAD_list(p));
		ulong n = DEREF_ulong(ctype_shape(ct));
		if (n == LINK_NONE) {
			/* Uncompiled or incomplete class */
			GRAPH gr = DEREF_graph(ctype_base(ct));
			ulong m = DEREF_ulong(graph_al_tag(gr));
			enc_al_tagdef(m, n);
		}
		p = TAIL_list(p);
	}
	DESTROY_list(incompl_classes, SIZE_ctype);
	incompl_classes = NULL_list(CLASS_TYPE);
	return;
}


/*
    This routine adds the alignment of the class type ct to the bitstream
    bs.  Note that ct is not compiled by this routine.
*/

BITSTREAM *
enc_al_ctype(BITSTREAM *bs, CLASS_TYPE ct)
{
	GRAPH gr = DEREF_graph(ctype_base(ct));
	ulong m = DEREF_ulong(graph_al_tag(gr));
	if (m == LINK_NONE) {
		string s = NULL;
		ulong n = DEREF_ulong(ctype_shape(ct));
		if (n != LINK_NONE) {
			/* Class already compiled */
			ENC_alignment(bs);
			bs = enc_shape_token(bs, n);
			return bs;
		}
		if (output_all) {
			s = mangle_typeid("~cpp.al.", ct);
		}
		m = capsule_no(s, VAR_alignment);
		COPY_ulong(graph_al_tag(gr), m);
		CONS_ctype(ct, incompl_classes, incompl_classes);
	}
	m = link_no(bs, m, VAR_alignment);
	ENC_obtain_al_tag(bs);
	ENC_make_al_tag(bs, m);
	return bs;
}


/*
    This routine compiles the base class graph gr returning a token
    number representing the base class offset.  If gr is a virtual base
    and ptr is true then this is the offset of the pointer to the base,
    otherwise it is the actual base.
*/

static ulong
compile_base(GRAPH gr, int ptr)
{
	ulong n, m;
	GRAPH g1, g2;
	BITSTREAM *bs;
	string s = NULL;
	OFFSET off = DEREF_off(graph_off(gr));
	DECL_SPEC acc = DEREF_dspec(graph_access(gr));
	if ((acc & dspec_virtual) && !ptr) {
		/* Virtual base class */
		n = DEREF_ulong(graph_real_off(gr));
		return n;
	}
	if (IS_off_base(off)) {
		/* Direct base class */
		n = DEREF_ulong(graph_base_off(gr));
		return n;
	}

	/* Check for recorded values */
	if (ptr) {
		n = DEREF_ulong(graph_base_off(gr));
	} else {
		n = DEREF_ulong(graph_real_off(gr));
	}
	if (n != LINK_NONE) {
		return n;
	}
	if (output_all) {
		const char *pre = "~cpp.base.";
		if ((acc & dspec_mutable) && !ptr) {
			pre = "~cpp.virt.";
		}
		s = mangle_vtable(pre, gr);
	}
	n = capsule_no(s, VAR_token);

	/* Decompose base offset */
	if (acc & dspec_mutable) {
		/* Base of virtual base */
		CLASS_TYPE cs;
		g1 = DEREF_graph(graph_up(gr));
		cs = DEREF_ctype(graph_head(g1));
		g2 = DEREF_graph(ctype_base(cs));
		g2 = find_subgraph(g2, g1, gr);
		if (ptr) {
			COPY_ulong(graph_base_off(gr), n);
		} else {
			COPY_ulong(graph_real_off(gr), n);
		}
	} else {
		/* Indirect base */
		OFFSET off1 = DEREF_off(off_deriv_direct(off));
		OFFSET off2 = DEREF_off(off_deriv_indirect(off));
		g1 = DEREF_graph(off_base_graph(off1));
		if (IS_off_base(off2)) {
			g2 = DEREF_graph(off_base_graph(off2));
		} else {
			g2 = DEREF_graph(off_deriv_graph(off2));
		}
		COPY_ulong(graph_base_off(gr), n);
		COPY_ulong(graph_real_off(gr), n);
	}

	/* Define the token */
	bs = enc_tokdef_start(n, "E", NIL(ulong), 1);
	ENC_offset_add(bs);
	m = compile_base(g1, 0);
	bs = enc_exp_token(bs, m);
	m = compile_base(g2, ptr);
	bs = enc_exp_token(bs, m);
	enc_tokdef_end(n, bs);
	return n;
}


/*
    This routine adds an offset representing the base class graph gr
    to the bitstream bs.  For virtual bases this is the offset of the
    pointer to the base if ptr is true and the offset of the actual base
    otherwise.
*/

BITSTREAM *
enc_base(BITSTREAM *bs, GRAPH gr, int ptr)
{
	GRAPH gt = DEREF_graph(graph_top(gr));
	CLASS_TYPE ct = DEREF_ctype(graph_head(gt));
	if (EQ_graph(gr, gt)) {
		ENC_offset_zero(bs);
		bs = enc_al_ctype(bs, ct);
	} else {
		ulong n;
		IGNORE compile_class(ct);
		n = compile_base(gr, ptr);
		bs = enc_exp_token(bs, n);
	}
	return bs;
}


/*
    This routine adds the start of a virtual base class pointer expression
    to the bitstream bs.  off1 gives the direct component of the offset
    and off2 gives the indirect component.
*/

BITSTREAM *
enc_add_base(BITSTREAM *bs, OFFSET off1, OFFSET off2)
{
	GRAPH gr = DEREF_graph(off_base_graph(off1));
	DECL_SPEC acc = DEREF_dspec(graph_access(gr));
	if (!IS_NULL_off(off2)) {
		if (IS_off_deriv(off2)) {
			OFFSET off3 = DEREF_off(off_deriv_direct(off2));
			OFFSET off4 = DEREF_off(off_deriv_indirect(off2));
			bs = enc_add_base(bs, off3, off4);
		} else {
			bs = enc_add_base(bs, off2, NULL_off);
		}
	}
	if (acc & dspec_virtual) {
		/* Indirection for virtual bases */
		CLASS_TYPE ct = DEREF_ctype(graph_head(gr));
		ENC_contents(bs);
		ENC_pointer(bs);
		bs = enc_al_ctype(bs, ct);
	}
	if (!(acc & dspec_ignore)) {
		/* Add base class offset */
		ENC_add_to_ptr(bs);
	}
	return bs;
}


/*
    This routine adds the end of a virtual base class pointer expression
    to the bitstream bs.  off1 gives the direct component of the offset
    and off2 gives the indirect component.
*/

BITSTREAM *
enc_end_base(BITSTREAM *bs, OFFSET off1, OFFSET off2)
{
	GRAPH gr = DEREF_graph(off_base_graph(off1));
	DECL_SPEC acc = DEREF_dspec(graph_access(gr));
	if (!(acc & dspec_ignore)) {
		/* Output base class offset */
		ulong n = DEREF_ulong(graph_base_off(gr));
		if (n == LINK_NONE) {
			/* Compile class if necessary */
			GRAPH gt = DEREF_graph(graph_top(gr));
			CLASS_TYPE ct = DEREF_ctype(graph_head(gt));
			IGNORE compile_class(ct);
			n = DEREF_ulong(graph_base_off(gr));
		}
		bs = enc_exp_token(bs, n);
	}
	if (!IS_NULL_off(off2)) {
		if (IS_off_deriv(off2)) {
			OFFSET off3 = DEREF_off(off_deriv_direct(off2));
			OFFSET off4 = DEREF_off(off_deriv_indirect(off2));
			bs = enc_end_base(bs, off3, off4);
		} else {
			bs = enc_end_base(bs, off2, NULL_off);
		}
	}
	return bs;
}


/*
    This routine adds the offset of the member id to the bitstream bs.
    If id is a data member this is the offset of the member from the start
    of the structure.
*/

BITSTREAM *
enc_member(BITSTREAM *bs, IDENTIFIER id)
{
	ulong tok;
	unsigned tag = TAG_id(id);
	if (tag == id_member_tag) {
		/* Simple data member */
		OFFSET off = DEREF_off(id_member_off(id));
		if (IS_off_member(off)) {
			tok = DEREF_ulong(id_no(id));
			if (tok == LINK_NONE) {
				CLASS_TYPE ct = parent_class(id);
				IGNORE compile_class(ct);
				tok = DEREF_ulong(id_no(id));
			}
			if (tok == LINK_ZERO) {
				/* Union member */
				TYPE t = DEREF_type(id_member_type(id));
				ENC_offset_zero(bs);
				bs = enc_alignment(bs, t);
			} else {
				/* Structure member */
				bs = enc_exp_token(bs, tok);
			}
		} else {
			bs = enc_offset(bs, off);
		}
	} else {
		/* Static data members and member functions */
		IGNORE capsule_id(id, VAR_tag);
		tok = unit_no(bs, id, VAR_tag, 0);
		ENC_obtain_tag(bs);
		ENC_make_tag(bs, tok);
	}
	return bs;
}


/*
    This routine adds an expression representing a null value of type
    ct to the bitstream bs.  The virtual base components are only
    included if virt is true.  Note that the order of the components
    is not necessarily the same as that in compile_class, but the
    installers always sort make_compound expressions into the correct
    order.
*/

static BITSTREAM *
enc_null_class_aux(BITSTREAM *bs, CLASS_TYPE ct, int virt)
{
	CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
	if (ci & (cinfo_empty | cinfo_token)) {
		/* Tokenised and empty classes */
		ENC_make_value(bs);
		bs = enc_ctype(bs, ct);
	} else {
		/* Non-empty classes */
		MEMBER mem;
		unsigned no_mems = 0;
		GRAPH gr = DEREF_graph(ctype_base(ct));
		LIST(GRAPH)br = DEREF_list(graph_tails(gr));
		LIST(GRAPH)bv = DEREF_list(ctype_vbase(ct));
		NAMESPACE ns = DEREF_nspace(ctype_member(ct));
		BITSTREAM *ts = start_bitstream(NIL(FILE), bs->link);

		/* Scan through direct base classes */
		while (!IS_NULL_list(br)) {
			GRAPH gs = DEREF_graph(HEAD_list(br));
			DECL_SPEC acc = DEREF_dspec(graph_access(gs));
			CLASS_TYPE cs = DEREF_ctype(graph_head(gs));
			ulong m = DEREF_ulong(graph_base_off(gs));
			if (acc & dspec_virtual) {
				ts = enc_exp_token(ts, m);
				ENC_make_null_ptr(ts);
				ts = enc_al_ctype(ts, cs);
				no_mems++;
			} else {
				CLASS_INFO cj = DEREF_cinfo(ctype_info(cs));
				if (!(cj & cinfo_empty)) {
					ts = enc_exp_token(ts, m);
					ts = enc_null_class_aux(ts, cs, 0);
					no_mems++;
				}
			}
			br = TAIL_list(br);
		}

		/* Scan through data members */
		mem = DEREF_member(nspace_ctype_first(ns));
		mem = next_data_member(mem, 0);
		while (!IS_NULL_member(mem)) {
			IDENTIFIER mid = DEREF_id(member_id(mem));
			TYPE s = DEREF_type(id_member_type(mid));
			ts = enc_member(ts, mid);
			ts = enc_null_exp(ts, s);
			no_mems++;
			if (ci & cinfo_union) {
				break;
			}
			mem = DEREF_member(member_next(mem));
			mem = next_data_member(mem, 0);
		}

		/* Scan through virtual function tables */
#if LANGUAGE_CPP
		if (ci & cinfo_polymorphic) {
			VIRTUAL vt = DEREF_virt(ctype_virt(ct));
			while (!IS_NULL_virt(vt)) {
				OFFSET off = DEREF_off(virt_table_off(vt));
				if (IS_NULL_off(off)) {
					ulong m =
					    DEREF_ulong(virt_table_tok(vt));
					ts = enc_exp_token(ts, m);
					size_dummy_vtab =
					    DEREF_ulong(virt_no(vt));
					ts = enc_null_exp(ts, ptr_dummy_vtab);
					no_mems++;
				}
				vt = DEREF_virt(virt_next(vt));
			}
		}
#endif

		/* Scan through virtual bases */
		if (virt) {
			while (!IS_NULL_list(bv)) {
				GRAPH gs = DEREF_graph(HEAD_list(bv));
				CLASS_TYPE cs = DEREF_ctype(graph_head(gs));
				CLASS_INFO cj = DEREF_cinfo(ctype_info(cs));
				if (!(cj & cinfo_empty)) {
					ulong m =
					    DEREF_ulong(graph_real_off(gs));
					ts = enc_exp_token(ts, m);
					ts = enc_null_class_aux(ts, cs, 0);
					no_mems++;
				}
				bv = TAIL_list(bv);
			}
		} else {
			if (IS_NULL_list(bv)) {
				virt = 1;
			}
		}

		/* Encode complete construct */
		if (no_mems) {
			ENC_make_compound(bs);
			if (virt) {
				ENC_shape_offset(bs);
				bs = enc_ctype(bs, ct);
			} else {
				ulong m = DEREF_ulong(graph_core_off(gr));
				if (m == LINK_NONE) {
					ENC_shape_offset(bs);
					bs = enc_ctype(bs, ct);
				} else {
					bs = enc_exp_token(bs, m);
				}
			}
			ENC_LIST(bs, no_mems + no_mems);
			bs = join_bitstreams(bs, ts);
		} else {
			ENC_make_value(bs);
			bs = enc_ctype(bs, ct);
			end_bitstream(ts, 0);
		}
	}
	return bs;
}


/*
    This routine adds the default null value for the class type ct to the
    bitstream bs.  This is represented by a token which is defined the
    first time the routine is called.
*/

BITSTREAM *
enc_null_class(BITSTREAM *bs, CLASS_TYPE ct)
{
	ulong n = DEREF_ulong(ctype_null_exp(ct));
	if (n == LINK_NONE) {
		/* Define token for null value */
		BITSTREAM *ts;
		string s = NULL;
		IGNORE compile_class(ct);
		if (output_all) {
			s = mangle_typeid("~cpp.null.", ct);
		}
		n = capsule_no(s, VAR_token);
		COPY_ulong(ctype_null_exp(ct), n);
		ts = enc_tokdef_start(n, "E", NIL(ulong), 1);
		ts = enc_null_class_aux(ts, ct, 1);
		enc_tokdef_end(n, ts);
	}
	bs = enc_exp_token(bs, n);
	return bs;
}


/*
    The constructor initialiser routines are only included in the C++
    producer.
*/

#if LANGUAGE_CPP


/*
    This routine performs a construct initialisation using a at offset
    off from the tag m.  virt controls how m is accessed.  Note that a
    may be a dummy expression to indicate that m is initialised from
    the corresponding offset from the second argument in a copy
    constructor or assignment operator (see init_empty_base).
*/

static BITSTREAM *
enc_ctor_exp(BITSTREAM *bs, EXP a, OFFSET off, ulong m, int virt, unsigned seq)
{
	if (!IS_NULL_exp(a)) {
		int context = 0;
		EXP d = NULL_exp;
		TYPE s = DEREF_type(exp_type(a));
		if (IS_exp_paren(a)) {
			/* Used to mark destructors - see destr_init */
			if (seq > 1) {
				context = 5;
				d = a;
			}
			a = DEREF_exp(exp_paren_arg(a));
		}
		if (IS_NULL_exp(a)) {
			/* EMPTY */
		} else if (IS_exp_value(a)) {
			/* Copy assignment */
			int bf = 0;
			TYPE t = DEREF_type(exp_type(a));
			bs = enc_assign_op(bs, t, &bf);
			if (bf) {
				/* Bitfield assignment */
				OFFSET off1 = off;
				OFFSET off2 = decons_bitf_off(&off1);
				bs = enc_dummy_exp(bs, t, m, off1, 0, virt);
				bs = enc_offset(bs, off2);
			} else {
				/* Non-bitfield assignment */
				bs = enc_dummy_exp(bs, t, m, off, 0, virt);
			}
			last_conts[DUMMY_copy] = 1;
			bs = enc_dummy_exp(bs, t, LINK_NONE, off, DUMMY_copy, 1);
			last_conts[DUMMY_copy] = 0;
			seq--;
		} else {
			/* Constructor initialiser */
			bs = enc_init_tag(bs, m, off, 0, s, a, d, context);
			if (!IS_NULL_exp(d)) {
				d = NULL_exp;
				seq--;
			}
			seq--;
		}
		if (!IS_NULL_exp(d)) {
			/* Increase constructor count */
			bs = enc_destr_count(bs, s, 1);
			seq--;
		}
	}
	while (seq) {
		ENC_make_top(bs);
		seq--;
	}
	return bs;
}


/*
    This routine adds a list of virtual base pointer initialisations
    for an object with tag number m and class ct to the bitstream bs.
*/

static BITSTREAM *
enc_virt_init(BITSTREAM *bs, CLASS_TYPE ct, ulong m)
{
	LIST(GRAPH)bv = DEREF_list(ctype_vbase(ct));
	while (!IS_NULL_list(bv)) {
		GRAPH gr = DEREF_graph(HEAD_list(bv));
		ulong tv = DEREF_ulong(graph_real_off(gr));
		while (!IS_NULL_graph(gr)) {
			ulong tp = compile_base(gr, 1);
			ENC_assign(bs);
			ENC_add_to_ptr(bs);
			ENC_obtain_tag(bs);
			ENC_make_tag(bs, m);
			bs = enc_exp_token(bs, tp);
			ENC_add_to_ptr(bs);
			ENC_obtain_tag(bs);
			ENC_make_tag(bs, m);
			bs = enc_exp_token(bs, tv);
			gr = DEREF_graph(graph_equal(gr));
		}
		bv = TAIL_list(bv);
	}
	return bs;
}


/*
    This routine adds a list of virtual function table initialisations
    for an object with tag number m and class ct to the bitstream bs.
*/

static BITSTREAM *
enc_vtab_init(BITSTREAM *bs, CLASS_TYPE ct, ulong m, int virt)
{
	VIRTUAL vt = DEREF_virt(ctype_virt(ct));
	while (!IS_NULL_virt(vt)) {
		OFFSET off = DEREF_off(virt_table_off(vt));
		ulong tv = DEREF_ulong(virt_table_tok(vt));
		ulong tt = DEREF_ulong(virt_table_tbl(vt));
		record_usage(tt, VAR_tag, USAGE_USE);
		ENC_assign(bs);
		ENC_add_to_ptr(bs);
		if (is_zero_offset(off)) {
			ENC_obtain_tag(bs);
			ENC_make_tag(bs, m);
		} else {
			TYPE t = ptr_dummy_class;
			bs = enc_dummy_exp(bs, t, m, off, 0, virt);
		}
		bs = enc_exp_token(bs, tv);
		tt = link_no(bs, tt, VAR_tag);
		ENC_obtain_tag(bs);
		ENC_make_tag(bs, tt);
		vt = DEREF_virt(virt_next(vt));
	}
	return bs;
}


/*
    This routine adds the conditional deletion for an object with tag
    number m and class ct to the bitstream bs.
*/

static BITSTREAM *
enc_delete_obj(BITSTREAM *bs, CLASS_TYPE ct, ulong m)
{
	IDENTIFIER cid = DEREF_id(ctype_name(ct));
	TYPE t = DEREF_type(id_class_name_etc_defn(cid));
	IDENTIFIER fid = find_allocator(t, lex_delete, 0, NULL_id);
	if (IS_NULL_id(fid)) {
		/* This shouldn't happen */
		ENC_make_top(bs);
	} else {
		ulong d;
		BITSTREAM *ts;
		TYPE fn = DEREF_type(id_function_etc_type(fid));
		LIST(TYPE)ptypes = DEREF_list(type_func_ptypes(fn));
		unsigned npids = LENGTH_list(ptypes);

		/* Mark the function as to be compiled */
		IGNORE capsule_id(fid, VAR_tag);
		CONS_id(fid, pending_funcs, pending_funcs);

		/* Encode the function call */
		ENC_apply_proc(bs);
		ENC_top(bs);
		ENC_obtain_tag(bs);
		d = unit_no(bs, fid, VAR_tag, 0);
		ENC_make_tag(bs, d);
		if (npids > 2) {
			npids = 2;
		}
		ENC_LIST_SMALL(bs, npids);
		bs = enc_special(bs, TOK_to_ptr_void);
		ts = start_bitstream(NIL(FILE), bs->link);
		ts = enc_al_ctype(ts, ct);
		ENC_obtain_tag(ts);
		ENC_make_tag(ts, m);
		bs = enc_bitstream(bs, ts);
		if (npids == 2) {
			/* Allow for second argument */
			TYPE s;
			TYPE c = type_char;
			ptypes = TAIL_list(ptypes);
			s = DEREF_type(HEAD_list(ptypes));
			if (!IS_type_integer(s)) {
				s = type_size_t;
			}
			ENC_offset_div(bs);
			bs = enc_variety(bs, s);
			bs = enc_shape_offset(bs, t);
			bs = enc_shape_offset(bs, c);
		}
		ENC_OFF(bs);
	}
	return bs;
}


/*
    This routine adds the list of constructor initialisers given by e
    to the bitstream bs.
*/

BITSTREAM *
enc_ctor_init(BITSTREAM *bs, EXP e)
{
	ulong n, m;
	CLASS_TYPE ct = last_class;
	int kind = DEREF_int(exp_initialiser_kind(e));
	LIST(EXP)p = DEREF_list(exp_initialiser_args(e));
	LIST(OFFSET)q = DEREF_list(exp_initialiser_offs(e));

	/* Find number of items */
	unsigned np = LENGTH_list(p);
	unsigned nv = DEREF_unsigned(exp_initialiser_virt(e));
	unsigned nb = DEREF_unsigned(exp_initialiser_base(e));
	unsigned no = np - nv;

	/* Compile the class */
	IGNORE compile_class(ct);

	/* Find the 'this' pointer */
	n = last_params[DUMMY_this];
	m = unit_no(bs, NULL_id, VAR_tag, 1);
	ENC_identify(bs);
	bs = enc_access(bs, crt_func_access);
	ENC_make_tag(bs, m);
	ENC_contents(bs);
	ENC_pointer(bs);
	bs = enc_al_ctype(bs, ct);
	ENC_obtain_tag(bs);
	ENC_make_tag(bs, n);

	if (kind == DEFAULT_DESTR) {
		/* Deal with destructors */
		int context = 0;
		unsigned ns = no + 1;
		ulong m2 = last_params[DUMMY_extra];
		if (last_params[DUMMY_count] != LINK_NONE) {
			context = 5;
			ns--;
		}
		if (nv) {
			ns++;
		}
		if (ns > 1) {
			ENC_SEQUENCE(bs, ns - 1);
		} else {
			if (ns == 0) {
				ENC_make_top(bs);
			}
		}

		/* Destroy members and direct bases */
		while (no) {
			EXP a = DEREF_exp(HEAD_list(p));
			if (IS_NULL_exp(a)) {
				ENC_make_top(bs);
			} else {
				TYPE s = DEREF_type(exp_type(a));
				OFFSET off = DEREF_off(HEAD_list(q));
				bs = enc_term_local(bs, m, off, 0, s, a,
						    context);
			}
			q = TAIL_list(q);
			p = TAIL_list(p);
			no--;
		}

		/* Conditionally destroy virtual bases */
		if (nv) {
			int mask = 0;
			if (context == 0) {
				mask = EXTRA_DESTR;
			}
			bs = enc_flag_test(bs, m2, nv, mask, ntest_not_eq);
			while (!IS_NULL_list(p)) {
				EXP a = DEREF_exp(HEAD_list(p));
				if (IS_NULL_exp(a)) {
					ENC_make_top(bs);
				} else {
					TYPE s = DEREF_type(exp_type(a));
					OFFSET off = DEREF_off(HEAD_list(q));
					bs = enc_term_local(bs, m, off, 0, s,
							    a, context);
				}
				q = TAIL_list(q);
				p = TAIL_list(p);
			}
			ENC_make_top(bs);
		}

		/* Conditionally call 'operator delete' */
		if (context == 0) {
			ns = 1;
			bs = enc_flag_test(bs, m2, ns, EXTRA_DELETE,
					   ntest_not_eq);
			bs = enc_delete_obj(bs, ct, m);
			ENC_make_top(bs);
		}

	} else {
		/* Deal with constructors */
		int virt = 1;
		unsigned ns, nu;
		unsigned ni = 0;
		unsigned nt = 0;
		unsigned ne = 1;

		/* Allow for copy constructors */
		if (kind == DEFAULT_COPY || kind == DEFAULT_ASSIGN) {
			ulong n1 = last_params[DUMMY_second];
			ulong m1 = unit_no(bs, NULL_id, VAR_tag, 1);
			ENC_identify(bs);
			bs = enc_access(bs, crt_func_access);
			ENC_make_tag(bs, m1);
			ENC_contents(bs);
			ENC_pointer(bs);
			bs = enc_al_ctype(bs, ct);
			ENC_obtain_tag(bs);
			ENC_make_tag(bs, n1);
			last_params[DUMMY_copy] = m1;
		}

		/* Count number of items */
		if (kind != DEFAULT_ASSIGN) {
			VIRTUAL vt = DEREF_virt(ctype_virt(ct));
			if (kind != DEFAULT_PRELUDE) {
				LIST(GRAPH)bv = DEREF_list(ctype_vbase(ct));
				while (!IS_NULL_list(bv)) {
					/* Virtual base pointers */
					GRAPH gr = DEREF_graph(HEAD_list(bv));
					while (!IS_NULL_graph(gr)) {
						ni++;
						gr = DEREF_graph(graph_equal(gr));
					}
					bv = TAIL_list(bv);
				}
			}
			if (!IS_NULL_virt(vt)) {
				/* Virtual function tables */
				IDENTIFIER cid = DEREF_id(ctype_name(ct));
				compile_virtual(ct, !has_linkage(cid));
				while (!IS_NULL_virt(vt)) {
					nt++;
					vt = DEREF_virt(virt_next(vt));
				}
			}
			virt = 0;
		}
		if (last_params[DUMMY_count] != LINK_NONE) {
			ne = 2;
		}
		ns = ne * no + nt;
		nu = ne * nv + ni;
		if (nu) {
			ns++;
		}
		if (ns > 1) {
			ENC_SEQUENCE(bs, ns - 1);
		} else {
			if (ns == 0) {
				ENC_make_top(bs);
			}
		}

		/* Conditionally initialise virtual bases */
		if (nu) {
			int dv = 0;
			ulong m2 = last_params[DUMMY_extra];
			bs = enc_flag_test(bs, m2, nu, 0, ntest_not_eq);
			if (ni) {
				/* Initialise virtual base pointers */
				bs = enc_virt_init(bs, ct, m);
			}
			while (nv) {
				/* Virtual base initialisers */
				EXP a = DEREF_exp(HEAD_list(p));
				OFFSET off = DEREF_off(HEAD_list(q));
				bs = enc_ctor_exp(bs, a, off, m, virt, ne);
				if (!IS_NULL_exp(a) && IS_exp_paren(a)) {
					dv++;
				}
				q = TAIL_list(q);
				p = TAIL_list(p);
				nv--;
			}
			if (ne == 1 || dv == 0) {
				ENC_make_top(bs);
			} else {
				bs = enc_destr_count(bs, NULL_type, dv);
			}
		}

		/* Initialise direct bases */
		while (nb) {
			EXP a = DEREF_exp(HEAD_list(p));
			OFFSET off = DEREF_off(HEAD_list(q));
			bs = enc_ctor_exp(bs, a, off, m, virt, ne);
			q = TAIL_list(q);
			p = TAIL_list(p);
			nb--;
		}

		/* Initialise virtual function tables */
		if (nt) {
			bs = enc_vtab_init(bs, ct, m, 1);
		}

		/* Initialise members */
		while (!IS_NULL_list(p)) {
			EXP a = DEREF_exp(HEAD_list(p));
			OFFSET off = DEREF_off(HEAD_list(q));
			bs = enc_ctor_exp(bs, a, off, m, virt, ne);
			q = TAIL_list(q);
			p = TAIL_list(p);
		}
		last_params[DUMMY_copy] = LINK_NONE;
	}
	return bs;
}


#endif /* LANGUAGE_CPP */
#endif /* TDF_OUTPUT */
