/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>

#include <shared/check.h>

#include "config.h"
#include "version.h"
#include "c_types.h"
#include "ctype_ops.h"
#include "exp_ops.h"
#include "id_ops.h"
#include "member_ops.h"
#include "nat_ops.h"
#include "nspace_ops.h"
#include "off_ops.h"
#include "type_ops.h"
#include "error.h"
#include "tdf.h"
#include "allocate.h"
#include "basetype.h"
#include "capsule.h"
#include "check.h"
#include "chktype.h"
#include "compile.h"
#include "constant.h"
#include "copy.h"
#include "destroy.h"
#include "diag.h"
#include "encode.h"
#include "exp.h"
#include "init.h"
#include "initialise.h"
#include "member.h"
#include "shape.h"
#include "statement.h"
#include "stmt.h"
#include "struct.h"
#include "syntax.h"
#include "throw.h"
#include "tok.h"
#if TDF_OUTPUT


/*
    The flag in_static_init is set to true when encoding a static
    initialiser.  The flag in_dynamic_init is set to true when encoding
    a dynamic initialiser.
*/

int in_static_init = 0;
int in_dynamic_init = 0;


/*
    This routine adds the aggregate initialiser for an array of type t,
    given by the aggregate expression e followed by n zeros, to the
    bitstream bs.  n may be null to indicate the absence of padding.
*/

BITSTREAM *
enc_init_array(BITSTREAM *bs, EXP e, NAT n, TYPE t)
{
	LIST(EXP)p = DEREF_list(exp_aggregate_args(e));
	TYPE s = DEREF_type(type_array_sub(t));
	unsigned tag = TAG_type(s);
	if (tag == type_integer_tag || tag == type_enumerate_tag) {
		unsigned mask = 0;
		unsigned long len = 0;
		LIST(EXP)q = p;
		LIST(unsigned)vs = NULL_list(unsigned);
		while (!IS_NULL_list(q)) {
			/* Check for arrays of integers */
			unsigned v = 0;
			EXP a = DEREF_exp(HEAD_list(q));
			if (!IS_NULL_exp(a)) {
				NAT m;
				unsigned tm;
				if (!IS_exp_int_lit(a)) {
					break;
				}
				m = DEREF_nat(exp_int_lit_nat(a));
				tm = TAG_nat(m);
				if (tm == nat_calc_tag) {
					/* Allow for character literals */
					a = eval_exp(a, 1);
					if (!IS_exp_int_lit(a)) {
						break;
					}
					m = DEREF_nat(exp_int_lit_nat(a));
					tm = TAG_nat(m);
				}
				if (tm != nat_small_tag) {
					break;
				}
				v = DEREF_unsigned(nat_small_value(m));
			}
			CONS_unsigned(v, vs, vs);
			mask |= v;
			len++;
			q = TAIL_list(q);
		}
		if (IS_NULL_list(q)) {
			/* Array of small integers */
			if (mask == 0) {
				/* All zeros */
				bs = enc_null_exp(bs, t);
			} else {
				/* Encode as a string */
				LIST(unsigned)us;
				unsigned bits = no_bits(mask);
				if (!IS_NULL_nat(n)) {
					/* Check for padding */
					unsigned long pad = get_nat_value(n);
					if (pad <= STRING_PADDING) {
						len += pad;
						n = NULL_nat;
					} else {
						ENC_concat_nof(bs);
					}
				}
				ENC_make_nof_int(bs);
				bs = enc_variety(bs, s);
				ENC_make_string(bs);
				ENC_INT(bs, bits);
				ENC_INT(bs, len);
				vs = REVERSE_list(vs);
				us = vs;
				while (!IS_NULL_list(us)) {
					/* Encode each element */
					unsigned v =
					    DEREF_unsigned(HEAD_list(us));
					ENC_BITS(bs, bits, v);
					len--;
					us = TAIL_list(us);
				}
				while (len) {
					/* Encode explicit padding */
					ENC_BITS(bs, bits, 0);
					len--;
				}
				if (!IS_NULL_nat(n)) {
					/* Encode remaining padding */
					ENC_n_copies(bs);
					bs = enc_nat(bs, n, 1);
					bs = enc_null_exp(bs, s);
				}
			}
			DESTROY_list(vs, SIZE_unsigned);
			return bs;
		}
		DESTROY_list(vs, SIZE_unsigned);
	}

	/* Simple list */
	if (!IS_NULL_nat(n)) {
		ENC_concat_nof(bs);
	}
	ENC_make_nof(bs);
	bs = enc_exp_list(bs, p);
	if (!IS_NULL_nat(n)) {
		ENC_n_copies(bs);
		bs = enc_nat(bs, n, 1);
		bs = enc_null_exp(bs, s);
	}
	return bs;
}


/*
    This routine adds the aggregate initialiser for an object of class
    type t given by the aggregate expression p to the bitstream bs.  Note
    that t cannot have any base classes.
*/

BITSTREAM *
enc_init_class(BITSTREAM *bs, EXP e, CLASS_TYPE ct)
{
	LIST(EXP)p = DEREF_list(exp_aggregate_args(e));
	LIST(OFFSET)q = DEREF_list(exp_aggregate_offs(e));
	unsigned m = LENGTH_list(p);
	IGNORE compile_class(ct);
	if (m == 0) {
		/* Deal with empty classes */
		ENC_make_value(bs);
		bs = enc_ctype(bs, ct);
	} else {
		ENC_make_compound(bs);
		ENC_shape_offset(bs);
		bs = enc_ctype(bs, ct);
		ENC_LIST(bs, m + m);
		while (!IS_NULL_list(p)) {
			/* Scan aggregate initialiser */
			EXP a = DEREF_exp(HEAD_list(p));
			OFFSET off = DEREF_off(HEAD_list(q));
			bs = enc_offset(bs, off);
			bs = enc_exp(bs, a);
			q = TAIL_list(q);
			p = TAIL_list(p);
		}
	}
	return bs;
}


/*
    This variable is used to hold the tag of the loop counter variable
    which is used in new-initialiser expressions.
*/

static ulong alloc_counter = LINK_NONE;


/*
    This routine declares the pointer to s variable n to be the pointer
    variable m plus the offset off and the offset of the type t.
*/

static BITSTREAM *
enc_loop_decl(BITSTREAM *bs, ulong n, ulong m, TYPE s, int cnt, OFFSET off,
	      TYPE t)
{
	DECL_SPEC ds = dspec_none;
	if (n == alloc_counter) {
		ds = dspec_mutable;
	}
	if (cnt) {
		cnt = 2;
	}
	ENC_variable(bs);
	bs = enc_access(bs, ds);
	ENC_make_tag(bs, n);
	if (IS_NULL_type(t)) {
		bs = enc_dummy_exp(bs, s, m, off, cnt, 0);
	} else {
		ENC_add_to_ptr(bs);
		bs = enc_dummy_exp(bs, s, m, off, cnt, 0);
		bs = enc_shape_offset(bs, t);
	}
	return bs;
}


/*
    This routine compares the pointer to t variables n and m using test
    tst, jumping to label lab if appropriate.
*/

static BITSTREAM *
enc_loop_test(BITSTREAM *bs, ulong n, ulong m, TYPE t, ulong lab, NTEST tst)
{
	ENC_pointer_test(bs);
	ENC_OFF(bs);
	bs = enc_ntest(bs, tst);
	ENC_make_label(bs, lab);
	ENC_contents(bs);
	ENC_pointer(bs);
	bs = enc_alignment(bs, t);
	ENC_obtain_tag(bs);
	ENC_make_tag(bs, n);
	if (m == LINK_NONE) {
		ENC_make_null_ptr(bs);
		bs = enc_alignment(bs, t);
	} else {
		ENC_contents(bs);
		ENC_pointer(bs);
		bs = enc_alignment(bs, t);
		ENC_obtain_tag(bs);
		ENC_make_tag(bs, m);
	}
	return bs;
}


/*
    This routine tests the flag given by the tag n, and-ed with a if this
    is not zero, against zero.  A further s expressions to be evaluated
    if tst is true must be added together with the terminating expression
    of the conditional.
*/

BITSTREAM *
enc_flag_test(BITSTREAM *bs, ulong n, unsigned s, int a, NTEST tst)
{
	ulong lab = unit_no(bs, NULL_id, VAR_label, 1);
	ENC_conditional(bs);
	ENC_make_label(bs, lab);
	if (s) {
		ENC_SEQUENCE(bs, s);
	}
	ENC_integer_test(bs);
	ENC_OFF(bs);
	bs = enc_ntest(bs, tst);
	ENC_make_label(bs, lab);
	if (a) {
		ENC_and(bs);
	}
	ENC_contents(bs);
	bs = enc_shape(bs, type_sint);
	ENC_obtain_tag(bs);
	ENC_make_tag(bs, n);
	if (a) {
		bs = enc_make_int(bs, type_sint, a);
	}
	bs = enc_make_int(bs, type_sint, 0);
	return bs;
}


/*
    This routine increments (or decrements if neg is true) the pointer
    variable n by the offset of the type t.
*/

static BITSTREAM *
enc_loop_incr(BITSTREAM *bs, ulong n, TYPE t, int neg)
{
	ENC_assign(bs);
	ENC_obtain_tag(bs);
	ENC_make_tag(bs, n);
	ENC_add_to_ptr(bs);
	ENC_contents(bs);
	ENC_pointer(bs);
	bs = enc_alignment(bs, t);
	ENC_obtain_tag(bs);
	ENC_make_tag(bs, n);
	if (neg) {
		ENC_offset_negate(bs);
	}
	bs = enc_shape_offset(bs, t);
	return bs;
}


/*
    This routine returns the type for a terminator for a value of type t.
*/

static TYPE
find_count_type(TYPE t)
{
	if (!IS_NULL_type(t)) {
		if (IS_type_array(t)) {
			/* Handle arrays */
			NAT n = DEREF_nat(type_array_size(t));
			TYPE s = DEREF_type(type_array_sub(t));
			s = find_count_type(s);
			MAKE_type_array(cv_none, s, n, t);
		} else {
			t = dummy_count;
		}
	}
	return t;
}


/*
    This routine introduces a local variable for the terminator count
    variable given by d.
*/

static BITSTREAM *
enc_count_decl(BITSTREAM *bs, EXP d, TYPE s, ulong *pm)
{
	if (IS_exp_destr(d)) {
		EXP c = DEREF_exp(exp_destr_count(d));
		if (!IS_NULL_exp(c)) {
			int cnt = DEREF_int(exp_dummy_cont(c));
			if (cnt == 0) {
				/* Variable not yet introduced */
				TYPE t = dummy_count;
				ulong n = unit_no(bs, NULL_id, VAR_tag, 1);
				ulong m = DEREF_ulong(exp_dummy_no(c));
				s = find_count_type(s);
				bs = enc_loop_decl(bs, n, m, t, 0, NULL_off, s);
				COPY_int(exp_dummy_cont(c), 2);
				COPY_ulong(exp_dummy_no(c), n);
				*pm = m;
			}
		}
	}
	return bs;
}


/*
    This routine ends the terminator count given by d.
*/

static void
enc_count_end(EXP d, ulong m)
{
	if (IS_exp_destr(d)) {
		EXP c = DEREF_exp(exp_destr_count(d));
		if (!IS_NULL_exp(c) && m != LINK_NONE) {
			COPY_int(exp_dummy_cont(c), 0);
			COPY_ulong(exp_dummy_no(c), m);
		}
	}
	return;
}


/*
    This routine increments the terminator count variable given by d.
    Note that this is only done at the innermost level, i.e. when the
    associated type t is not an array.
*/

static BITSTREAM *
enc_count_incr(BITSTREAM *bs, EXP d, int neg, TYPE t)
{
	if (IS_exp_destr(d) && !IS_type_array(t)) {
		EXP c = DEREF_exp(exp_destr_count(d));
		if (!IS_NULL_exp(c)) {
			ulong n = DEREF_ulong(exp_dummy_no(c));
			bs = enc_loop_incr(bs, n, dummy_count, neg);
			return bs;
		}
	}
	ENC_make_top(bs);
	return bs;
}


/*
    This routine adds the type of the terminator object corresponding to
    type t to the bitstream bs.
*/

BITSTREAM *
enc_term_type(BITSTREAM *bs, TYPE t)
{
	while (IS_type_array(t)) {
		/* Allow for arrays */
		NAT n = DEREF_nat(type_array_size(t));
		ENC_nof(bs);
		bs = enc_nat(bs, n, 1);
		t = DEREF_type(type_array_sub(t));
	}
	bs = enc_special(bs, TOK_destr_type);
	return bs;
}


/*
    This routine defines a global terminator object corresponding to an
    object of type t and destructor pd.
*/

void
make_term_global(TYPE t, EXP *pd)
{
	EXP d = *pd;
	if (!IS_NULL_exp(d)) {
		EXP a;
		while (IS_exp_nof(d)) {
			d = DEREF_exp(exp_nof_pad(d));
		}
		a = DEREF_exp(exp_destr_count(d));
		if (IS_NULL_exp(a)) {
			/* Not already defined */
			TYPE s = dummy_count;
			ulong n = capsule_no(NULL_string, VAR_tag);
			BITSTREAM *bs = enc_tagdec_start(NULL_id, n, t, 1);
			bs = enc_term_type(bs, t);
			enc_tagdec_end(bs);
			bs = enc_tagdef_start(NULL_id, n, t, 1);
			while (IS_type_array(t)) {
				NAT m = DEREF_nat(type_array_size(t));
				ENC_n_copies(bs);
				bs = enc_nat(bs, m, 1);
				t = DEREF_type(type_array_sub(t));
			}
			bs = enc_special(bs, TOK_destr_null);
			enc_tagdef_end(bs);
			MAKE_exp_dummy(s, NULL_exp, n, NULL_off, 0, a);
			COPY_exp(exp_destr_count(d), a);
		}
		*pd = d;
	}
	return;
}


/*
    This routine defines a local terminator object corresponding to an
    object of type t and destructor pd.
*/

BITSTREAM *
make_term_local(BITSTREAM *bs, TYPE t, EXP *pd, int var)
{
	EXP d = *pd;
	if (!IS_NULL_exp(d)) {
		EXP a;
		TYPE s = dummy_count;
		ulong n = unit_no(bs, NULL_id, VAR_tag, 1);
		ENC_variable(bs);
		bs = enc_access(bs, dspec_none);
		ENC_make_tag(bs, n);
		if (var == 4) {
			/* Initialise to zero for temporaries */
			while (IS_type_array(t)) {
				NAT m = DEREF_nat(type_array_size(t));
				ENC_n_copies(bs);
				bs = enc_nat(bs, m, 1);
				t = DEREF_type(type_array_sub(t));
			}
			bs = enc_special(bs, TOK_destr_null);
		} else {
			ENC_make_value(bs);
			bs = enc_term_type(bs, t);
		}
		while (IS_exp_nof(d)) {
			d = DEREF_exp(exp_nof_pad(d));
		}
		MAKE_exp_dummy(s, NULL_exp, n, NULL_off, 0, a);
		COPY_exp(exp_destr_count(d), a);
		*pd = d;
	}
	return bs;
}


/*
    This routine decreases the partial destructor count by the value given
    in t and n.
*/

BITSTREAM *
enc_destr_count(BITSTREAM *bs, TYPE t, int n)
{
	TYPE s = type_sint;
	ulong m = last_params[DUMMY_count];
	ENC_assign(bs);
	ENC_obtain_tag(bs);
	ENC_make_tag(bs, m);
	ENC_minus(bs);
	bs = enc_error_treatment(bs, s);
	ENC_contents(bs);
	bs = enc_shape(bs, s);
	ENC_obtain_tag(bs);
	ENC_make_tag(bs, m);
	if (!IS_NULL_type(t) && IS_type_array(t)) {
		EXP a = sizeof_array(&t, s);
		bs = enc_exp(bs, a);
		free_exp(a, 1);
	} else {
		bs = enc_make_int(bs, s, n);
	}
	return bs;
}


/*
    This routine adds a terminator expression for the destructor d to the
    bitstream bs.  The other arguments are as in enc_init_tag.  The effect
    of the terminator expression is to add the destructor call to a list
    of destructors to be called at a later stage.
*/

static BITSTREAM *
enc_term_start(BITSTREAM *bs, ulong n, OFFSET off, int cnt, TYPE t, EXP d,
	       int context)
{
	int tok = TOK_destr_local;
	switch (context) {
	case 1:
destr_lab: {
		   /* Destroy local variable */
		   BITSTREAM *ts, *us;
		   EXP c = DEREF_exp(exp_destr_count(d));
		   assert(!IS_NULL_exp(c));
		   bs = enc_special(bs, tok);
		   ts = start_bitstream(NIL(FILE), bs->link);
		   ts = enc_exp(ts, c);
		   ts = enc_special(ts, TOK_destr_cast);
		   us = start_bitstream(NIL(FILE), ts->link);
		   us = enc_alignment(us, t);
		   us = enc_dummy_exp(us, t, n, off, 2 * cnt, 0);
		   ts = enc_bitstream(ts, us);
		   ts = enc_destr_func(ts, d);
		   bs = enc_bitstream(bs, ts);
		   break;
	   }
	case 2: {
		/* Destroy global variable */
		tok = TOK_destr_global;
		goto destr_lab;
	}
	case 5: {
		/* Partial constructor count */
		bs = enc_destr_count(bs, t, 1);
		break;
	}
	default: {
		ENC_make_top(bs);
		break;
	}
	}
	return bs;
}


/*
    This routine adds an assignment of the value e to the tag n plus offset
    off of type t (or the contents of tag n plus offset off if cnt is true)
    to the bitstream bs.  context is 2 for the initialisation of a global
    variable, 1 for the initialisation of a local variable and 0 otherwise.
    If the destructor expression d is not null then the terminator
    expressions for tag n are also initialised.  In this the case the
    output comprises two TDF expressions, otherwise it is a single
    expression.
*/

BITSTREAM *
enc_init_tag(BITSTREAM *bs, ulong n, OFFSET off, int cnt, TYPE t, EXP e, EXP d,
	     int context)
{
	/* Step over parenthesised expressions */
	int paren;
	unsigned tag;
	int temp = 0;
	int array = 0;
	int constant = 1;
	do {
		tag = TAG_exp(e);
		paren = 0;
		switch (tag) {
		case exp_dynamic_tag: {
			e = DEREF_exp(exp_dynamic_arg(e));
			constant = 0;
			paren = 1;
			break;
		}
		case exp_paren_tag:
		case exp_copy_tag: {
			e = DEREF_exp(exp_paren_etc_arg(e));
			paren = 1;
			break;
		}
		}
	} while (paren);

	/* Encode initialiser */
	switch (tag) {

	case exp_constr_tag: {
		/* Constructor calls */
		EXP a = DEREF_exp(exp_constr_obj(e));
		EXP b = DEREF_exp(exp_constr_alt(e));
		COPY_ulong(exp_dummy_no(a), n);
		COPY_off(exp_dummy_off(a), off);
		COPY_off(exp_dummy_off(b), off);
		COPY_int(exp_dummy_cont(a), 2 * cnt);
		e = DEREF_exp(exp_constr_call(e));
		bs = enc_exp(bs, e);
		COPY_off(exp_dummy_off(b), NULL_off);
		COPY_off(exp_dummy_off(a), NULL_off);
		break;
	}

	case exp_aggregate_tag: {
		/* Aggregate initialisers */
		unsigned tt = TAG_type(t);
		LIST(EXP)p = DEREF_list(exp_aggregate_args(e));
		LIST(OFFSET)q = DEREF_list(exp_aggregate_offs(e));
		unsigned i, m = LENGTH_list(p);
		if (tt == type_array_tag) {
			/* Array initialisers */
			OFFSET off1;
			ulong dn = LINK_NONE;
			TYPE s1 = DEREF_type(type_array_sub(t));
			if (constant) {
				/* Perform constant initialisation */
				if (IS_NULL_exp(d) && is_const_exp(e, -1)) {
					goto default_lab;
				}
			}
			if (!IS_NULL_exp(d)) {
				/* Declare terminator count */
				bs = enc_count_decl(bs, d, NULL_type, &dn);
				ENC_SEQUENCE(bs, 3 * m - 1);
			} else {
				if (m > 1)ENC_SEQUENCE(bs, m - 1);
			}
			MAKE_off_array(s1, 0, off1);
			MAKE_off_plus(off, off1, off);
			for (i = 0; i < m; i++) {
				/* Scan through elements */
				EXP a = DEREF_exp(HEAD_list(p));
				COPY_unsigned(off_array_arg(off1), i);
				bs = enc_init_tag(bs, n, off, cnt, s1, a, d,
						  context);
				if (!IS_NULL_exp(d)) {
					/* Increase terminator count */
					bs = enc_count_incr(bs, d, 0, s1);
				}
				p = TAIL_list(p);
			}
			DESTROY_off_plus(destroy, off, off1, off);
			DESTROY_off_array(destroy, s1, i, off1);
			UNUSED(s1);
			UNUSED(i);
			array = 1;

		} else if (tt == type_compound_tag) {
			/* Class initialisers */
			OFFSET off1 = NULL_off;
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
			IGNORE compile_class(ct);
			if (m == 0) {
				goto default_lab;
			}
			if (constant && m >= SMALL_COMPOUND_INIT) {
				if (is_const_exp(e, -1)) {
					/* Perform constant initialisation */
					temp = 1;
					goto default_lab;
				}
			}
			MAKE_off_plus(off, off1, off);
			if (m > 1) {
				ENC_SEQUENCE(bs, m - 1);
			}
			for (i = 0; i < m; i++) {
				/* Scan through data members */
				EXP a = DEREF_exp(HEAD_list(p));
				TYPE s = DEREF_type(exp_type(a));
				off1 = DEREF_off(HEAD_list(q));
				COPY_off(off_plus_arg2(off), off1);
				bs = enc_init_tag(bs, n, off, cnt, s, a,
						  NULL_exp, 0);
				p = TAIL_list(p);
				q = TAIL_list(q);
			}
			DESTROY_off_plus(destroy, off, off1, off);
			UNUSED(off1);
		}
		break;
	}

	case exp_nof_tag: {
		/* Array initialisers */
		OFFSET off1 = off;
		EXP a = DEREF_exp(exp_nof_start(e));
		EXP b = DEREF_exp(exp_nof_pad(e));
		NAT m = DEREF_nat(exp_nof_size(e));
		if (constant) {
			/* Perform constant initialisation */
			if (IS_NULL_exp(d) && is_const_exp(e, -1)) {
				goto default_lab;
			}
		}

		/* Allow for zero sized arrays */
		if (is_zero_nat(m)) {
			b = NULL_exp;
		} else {
			if (context == 2 && is_null_exp(b)) {
				/* Global already default initialised */
				if (IS_NULL_exp(d)) {
					b = NULL_exp;
				} else {
					MAKE_exp_value(t, b);
				}
			}
		}

		/* Encode initial component */
		if (IS_NULL_exp(a)) {
			if (IS_NULL_exp(b)) {
				/* Both components empty */
				ENC_make_top(bs);
			}
		} else {
			TYPE s = DEREF_type(exp_type(a));
			if (!IS_NULL_exp(b)) {
				unsigned seq = 1;
				if (!IS_NULL_exp(d))seq = 2;
				ENC_SEQ_SMALL(bs, seq);
				MAKE_off_type(s, off1);
				MAKE_off_plus(off, off1, off1);
			}
			bs = enc_init_tag(bs, n, off, cnt, s, a, d, context);
		}

		/* Encode padding component */
		if (!IS_NULL_exp(b)) {
			ulong ptr, end;
			unsigned seq = 2;
			ulong dn = LINK_NONE;
			int c = last_conts[DUMMY_copy];
			ulong s = last_params[DUMMY_copy];
			ulong cpy = s;

			TYPE r1 = DEREF_type(exp_type(b));
			ulong lab = unit_no(bs, NULL_id, VAR_label, 1);
			ptr = alloc_counter;
			if (ptr == LINK_NONE) {
				TYPE t0 = NULL_type;
				ptr = unit_no(bs, NULL_id, VAR_tag, 1);
				bs = enc_loop_decl(bs, ptr, n, r1, cnt, off1,
						   t0);
			}
			end = unit_no(bs, NULL_id, VAR_tag, 1);
			bs = enc_loop_decl(bs, end, n, r1, cnt, off, t);
			if (s != LINK_NONE) {
				/* Allow for copy constructors */
				cpy = unit_no(bs, NULL_id, VAR_tag, 1);
				bs = enc_loop_decl(bs, cpy, s, r1, c, off1,
						   NULL_type);
				last_params[DUMMY_copy] = cpy;
				last_conts[DUMMY_copy] = 2;
				seq++;
			}
			if (IS_nat_calc(m)) {
				/* Check for calculated bounds */
				ulong lab2 = unit_no(bs, NULL_id, VAR_label, 1);
				ENC_conditional(bs);
				ENC_make_label(bs, lab2);
				ENC_SEQ_SMALL(bs, 1);
				bs = enc_loop_test(bs, ptr, end, r1, lab2,
						   ntest_less);
			}
			if (!IS_NULL_exp(d)) {
				/* Declare terminator count */
				bs = enc_count_decl(bs, d, NULL_type, &dn);
				seq += 2;
			}
			ENC_repeat(bs);
			ENC_make_label(bs, lab);
			ENC_make_top(bs);
			ENC_SEQUENCE(bs, seq);
			bs = enc_init_tag(bs, ptr, NULL_off, 1, r1, b, d,
					  context);
			if (!IS_NULL_exp(d)) {
				/* Increase terminator count */
				bs = enc_count_incr(bs, d, 0, r1);
			}
			if (cpy != LINK_NONE) {
				bs = enc_loop_incr(bs, cpy, r1, 0);
			}
			bs = enc_loop_incr(bs, ptr, r1, 0);
			bs = enc_loop_test(bs, ptr, end, r1, lab, ntest_eq);
			if (IS_nat_calc(m)) {
				/* End check for calculated bounds */
				ENC_make_top(bs);
			}
			if (!IS_NULL_exp(d)) {
				enc_count_end(d, dn);
			}
			last_params[DUMMY_copy] = s;
			last_conts[DUMMY_copy] = c;
			if (!EQ_off(off1, off)) {
				DESTROY_off_plus(destroy, off, off1, off1);
				DESTROY_off_type(destroy, r1, off1);
				UNUSED(r1);
			}
		}
		/* NOT YET IMPLEMENTED - end component */
		array = 1;
		break;
	}

	case exp_preinc_tag: {
		/* Array initialisers */
		int op = DEREF_int(exp_preinc_becomes(e));
		if (op == lex_array) {
			int c = last_conts[DUMMY_copy];
			ulong s = last_params[DUMMY_copy];
			EXP a = DEREF_exp(exp_preinc_ref(e));
			EXP a1 = DEREF_exp(exp_dummy_value(a));
			ulong m = unit_no(bs, NULL_id, VAR_tag, 1);
			ENC_variable(bs);
			bs = enc_access(bs, dspec_none);
			ENC_make_tag(bs, m);
			bs = enc_exp(bs, a1);
			last_params[DUMMY_copy] = m;
			last_conts[DUMMY_copy] = 2;
			COPY_exp(exp_dummy_value(a), NULL_exp);
			e = DEREF_exp(exp_preinc_op(e));
			if (!IS_NULL_exp(d)) {
				ENC_SEQ_SMALL(bs, 1);
			}
			bs = enc_init_tag(bs, n, off, cnt, t, e, d, context);
			COPY_exp(exp_dummy_value(a), a1);
			last_params[DUMMY_copy] = s;
			last_conts[DUMMY_copy] = c;
			array = 1;
			break;
		}
		goto default_lab;
	}

	case exp_int_lit_tag:
	case exp_float_lit_tag:
	case exp_null_tag:
	case exp_zero_tag: {
		/* Null expressions */
		if (context == 2 && is_null_exp(e)) {
			/* Global already default initialised */
			ENC_make_top(bs);
			break;
		}
		goto default_lab;
	}

	case exp_value_tag: {
		/* Undefined expressions */
		ENC_make_top(bs);
		break;
	}

	default:
default_lab: {
		     /* Simple assignments */
		     int bf = 0;
		     if (cnt) {
			     cnt = 2;
		     }
		     bs = enc_assign_op(bs, t, &bf);
		     if (bf) {
			     /* Bitfield assignment */
			     OFFSET off1 = off;
			     OFFSET off2 = decons_bitf_off(&off1);
			     bs = enc_dummy_exp(bs, t, n, off1, cnt, 0);
			     bs = enc_offset(bs, off2);
		     } else {
			     /* Non-bitfield assignment */
			     bs = enc_dummy_exp(bs, t, n, off, cnt, 0);
		     }
		     if (temp) {
			     /* Introduce temporary variable */
			     ulong m = make_tagdef(NULL_id, t, e, NULL_exp, 1);
			     bs = enc_dummy_exp(bs, t, m, NULL_off, 1, 0);
		     } else {
			     bs = enc_exp(bs, e);
		     }
		     break;
	     }
	}

	/* Encode terminator expression */
	if (!IS_NULL_exp(d)) {
		if (array) {
			/* Array elements already handled */
			ENC_make_top(bs);
		} else {
			bs = enc_term_start(bs, n, off, cnt, t, d, context);
		}
	}
	return bs;
}


/*
    This routine creates a dummy initialiser expression of type t.
*/

EXP
make_dummy_init(TYPE t)
{
	EXP a;
	if (IS_type_array(t)) {
		NAT n = DEREF_nat(type_array_size(t));
		TYPE s = DEREF_type(type_array_sub(t));
		EXP b = make_dummy_init(s);
		MAKE_exp_nof(t, NULL_exp, n, b, NULL_exp, a);
		return a;
	}
	MAKE_exp_value(t, a);
	return a;
}


/*
    This routine adds the initialiser expression e for the global variable
    with capsule tag number n and type t to the bitstream bs.  If d is
    not the null expression then the terminator expressions for tag n
    are also initialised.
*/

BITSTREAM *
enc_init_global(BITSTREAM *bs, EXP e, EXP d, ulong n, TYPE t)
{
	int i = in_static_init;
	int j = in_dynamic_init;
	int uc = unreached_code;
	unreached_code = 0;
	in_static_init = 1;
	if (IS_exp_dynamic(e) && n != LINK_NONE) {
		/* Dynamic initialisers */
		BITSTREAM *ts;
		EXP a = DEREF_exp(exp_dynamic_arg(e));
		bs = enc_null_exp(bs, t);
		in_static_init = 0;
		in_dynamic_init = 1;
		ts = start_bitstream(NIL(FILE), init_func->link);
		n = link_no(ts, n, VAR_tag);
		ts = enc_init_tag(ts, n, NULL_off, 0, t, a, d, 2);
		init_func = join_bitstreams(init_func, ts);
		if (!IS_NULL_exp(d)) {
			init_no++;
		}
		init_no++;
	} else {
		/* Static initialisers */
		bs = enc_exp(bs, e);
		if (!IS_NULL_exp(d) && n != LINK_NONE) {
			/* Dynamic destructors */
			BITSTREAM *ts;
			EXP a = make_dummy_init(t);
			in_static_init = 0;
			in_dynamic_init = 1;
			ts = start_bitstream(NIL(FILE), init_func->link);
			n = link_no(ts, n, VAR_tag);
			ts = enc_init_tag(ts, n, NULL_off, 0, t, a, d, 2);
			init_func = join_bitstreams(init_func, ts);
			init_no += 2;
			free_exp(a, 1);
		}
	}
	unreached_code = uc;
	in_dynamic_init = j;
	in_static_init = i;
	return bs;
}


/*
    This routine is similar to enc_init_local, but handles assignment
    rather than initialisation.
*/

BITSTREAM *
enc_assign_local(BITSTREAM *bs, EXP a, EXP d, ulong n, TYPE t, EXP e)
{
	if (!IS_NULL_exp(e)) {
		BITSTREAM *ts;
		ENC_SEQ_SMALL(bs, 1);
		ts = enc_diag_begin(&bs);
		if (!IS_NULL_exp(d)) {
			ENC_SEQ_SMALL(ts, 1);
		}
		ts = enc_init_tag(ts, n, NULL_off, 0, t, a, d, 1);
		bs = enc_diag_end(bs, ts, e, 1);
	} else {
		unsigned seq = 1;
		if (!IS_NULL_exp(d)) {
			seq++;
		}
		ENC_SEQ_SMALL(bs, seq);
		bs = enc_init_tag(bs, n, NULL_off, 0, t, a, d, 1);
	}
	return bs;
}


/*
    This routine adds the initialiser expression a for the local
    variable with tag number n (in the current unit) and type t to the
    bitstream bs.  e gives the corresponding declaration statement for
    use with diagnostics.
*/

BITSTREAM *
enc_init_local(BITSTREAM *bs, EXP a, EXP d, ulong n, TYPE t, EXP e)
{
	if (n != LINK_NONE) {
		switch (TAG_exp(a)) {
		case exp_constr_tag:
		case exp_dynamic_tag:
dynamic_label: {
		       /* Explicit initialisation */
		       ENC_make_value(bs);
		       bs = enc_shape(bs, t);
		       bs = enc_assign_local(bs, a, d, n, t, e);
		       return bs;
	       }
		case exp_aggregate_tag:
		case exp_nof_tag: {
			/* Explicitly initialise in non-constant cases */
			if (!is_const_exp(a, -1)) {
				goto dynamic_label;
			}
			break;
		}
		case exp_paren_tag:
		case exp_copy_tag: {
			/* Parenthesised expressions */
			a = DEREF_exp(exp_paren_etc_arg(a));
			bs = enc_init_local(bs, a, d, n, t, e);
			return bs;
		}
		default : {
			if (!IS_NULL_exp(d)) {
				goto dynamic_label;
			}
			break;
		}
		}
	}
	if (!IS_NULL_exp(e)) {
		BITSTREAM *ts = enc_diag_begin(&bs);
		ts = enc_exp(ts, a);
		bs = enc_diag_end(bs, ts, e, 1);
	} else {
		bs = enc_exp(bs, a);
	}
	return bs;
}


/*
    This routine checks whether the expression a, which forms the right hand
    side of an assignment, requires the use of enc_init_tag rather than a
    simple assignment operation.
*/

int
is_init_complex(EXP a)
{
	switch (TAG_exp(a)) {
	case exp_constr_tag:
	case exp_dynamic_tag:
	case exp_aggregate_tag:
	case exp_string_lit_tag:
	case exp_nof_tag: {
		/* These are the complex cases */
		return 1;
	}
	case exp_paren_tag:
	case exp_copy_tag: {
		a = DEREF_exp(exp_paren_etc_arg(a));
		return is_init_complex(a);
	}
	}
	return 0;
}


/*
    This routine adds a termination expression e for the object with
    capsule tag number n and type t to the termination function ts.  If m
    is not LINK_NONE then it is the capsule tag number of a flag which
    needs to be checked before the termination expression is called.
    Note that the terminations are done in the reverse order to the
    initialisations.
*/

BITSTREAM *
enc_term_global(BITSTREAM *ts, ulong n, TYPE t, EXP e, ulong m)
{
	if (!IS_NULL_exp(e)) {
		BITSTREAM *bs;
		int uc = unreached_code;
		unreached_code = 0;
		bs = start_bitstream(NIL(FILE), ts->link);
		n = link_no(bs, n, VAR_tag);
		if (m == LINK_NONE) {
			/* Simple case */
			bs = enc_term_local(bs, n, NULL_off, 0, t, e, 2);
		} else {
			/* Check flag before call */
			m = link_no(bs, m, VAR_tag);
			bs = enc_flag_test(bs, m,(unsigned)1, 0, ntest_not_eq);
			bs = enc_term_local(bs, n, NULL_off, 0, t, e, 2);
			ENC_make_top(bs);
		}
		ts = join_bitstreams(bs, ts);
		unreached_code = uc;
	}
	return ts;
}


/*
    This routine adds a termination expression e for the object with local
    tag number n and type t to the bitstream bs.  context is 2 for global
    variables, 1, 3 or 4 for local variables, and 0 in destructors and
    deallocation expressions.  For local variables the result consists
    of two TDF expressions (including terminator variable adjustment).
    Otherwise the result is a single expression.
*/

BITSTREAM *
enc_term_local(BITSTREAM *bs, ulong n, OFFSET off, int cnt, TYPE t, EXP e,
	       int context)
{
	/* Allow for parenthesised expressions */
	EXP a = NULL_exp;
	EXP c = NULL_exp;
	unsigned tops = 0;
	while (IS_exp_paren_etc(e)) {
		e = DEREF_exp(exp_paren_etc_arg(e));
	}

	/* Check for array destructors */
	if (IS_type_array(t)) {
		TYPE r = t;
		EXP d = sizeof_array(&r, type_sint);
		switch (context) {
		case 1:
		case 3:
		case 4: {
			/* Local variables */
			tops = 1;
			break;
		}
		}
		if (IS_NULL_exp(d) || is_zero_exp(d)) {
			/* Zero sized arrays */
			tops++;
		} else {
			/* Non-trivial arrays */
			int calc = 1;
			ulong dn = LINK_NONE;
			unsigned seq = tops + 2;
			ulong ptr = unit_no(bs, NULL_id, VAR_tag, 1);
			ulong end = unit_no(bs, NULL_id, VAR_tag, 1);
			ulong lab = unit_no(bs, NULL_id, VAR_label, 1);
			bs = enc_loop_decl(bs, ptr, n, r, cnt, off, t);
			bs = enc_loop_decl(bs, end, n, r, cnt, off, NULL_type);
			while (IS_exp_nof(e)) {
				/* Step over array destructors */
				e = DEREF_exp(exp_nof_pad(e));
			}
			if (context != 2) {
				/* Declare counter */
				bs = enc_count_decl(bs, e, t, &dn);
				seq++;
			}
			if (IS_exp_int_lit(d)) {
				/* Check whether dimensions are constant */
				NAT m = DEREF_nat(exp_int_lit_nat(d));
				if (!IS_nat_calc(m)) {
					calc = 0;
				}
			}
			if (calc) {
				/* Check for calculated bounds */
				ulong lab2 = unit_no(bs, NULL_id, VAR_label, 1);
				ENC_conditional(bs);
				ENC_make_label(bs, lab2);
				ENC_SEQ_SMALL(bs, 1);
				bs = enc_loop_test(bs, ptr, end, r, lab2,
						   ntest_greater);
				tops++;
			}
			ENC_repeat(bs);
			ENC_make_label(bs, lab);
			ENC_make_top(bs);
			ENC_SEQ_SMALL(bs, seq);
			bs = enc_loop_incr(bs, ptr, r, 1);
			if (context != 2) {
				/* Decrease counter */
				bs = enc_count_incr(bs, e, 1, r);
			}
			bs = enc_term_local(bs, ptr, NULL_off, 1, r, e,
					    context);
			bs = enc_loop_test(bs, ptr, end, r, lab, ntest_eq);
			enc_count_end(e, dn);
		}
		while (tops) {
			ENC_make_top(bs);
			tops--;
		}
		return bs;
	}

	/* Simple destructor calls */
	if (IS_exp_destr(e)) {
		a = DEREF_exp(exp_destr_obj(e));
		COPY_ulong(exp_dummy_no(a), n);
		COPY_off(exp_dummy_off(a), off);
		COPY_int(exp_dummy_cont(a), 2 * cnt);
		c = DEREF_exp(exp_destr_count(e));
		e = DEREF_exp(exp_destr_call(e));
	}
	switch (context) {
	case 1:
	case 3: {
		/* Local variable */
		if (!IS_NULL_exp(c)) {
			BITSTREAM *ts;
			bs = enc_special(bs, TOK_destr_end);
			ts = start_bitstream(NIL(FILE), bs->link);
			ts = enc_exp(ts, c);
			bs = enc_bitstream(bs, ts);
		} else {
			tops = 1;
		}
		break;
	}
	case 4: {
		/* Explicitly initialised local variable */
		if (!IS_NULL_exp(c)) {
			/* Check for initialisation */
			BITSTREAM *ts;
			ulong lab = unit_no(bs, NULL_id, VAR_label, 1);
			ENC_conditional(bs);
			ENC_make_label(bs, lab);
			ENC_SEQ_SMALL(bs, 2);
			bs = enc_special(bs, TOK_destr_test);
			ts = start_bitstream(NIL(FILE), bs->link);
			ts = enc_exp(ts, c);
			ENC_make_label(ts, lab);
			bs = enc_bitstream(bs, ts);
			bs = enc_special(bs, TOK_destr_end);
			ts = start_bitstream(NIL(FILE), bs->link);
			ts = enc_exp(ts, c);
			bs = enc_bitstream(bs, ts);
			tops = 2;
		} else {
			tops = 1;
		}
		break;
	}
	case 5: {
		/* Partial destructor count */
		ulong m = last_params[DUMMY_count];
		bs = enc_flag_test(bs, m,(unsigned)1, 0, ntest_not_eq);
		bs = enc_destr_count(bs, t, 1);
		break;
	}
	}
	bs = enc_exp(bs, e);
	if (!IS_NULL_exp(a)) {
		/* Reset dummy expression */
		COPY_off(exp_dummy_off(a), NULL_off);
	}
	while (tops) {
		/* End any conditionals */
		ENC_make_top(bs);
		tops--;
	}
	return bs;
}


/*
    The memory allocation routines are only included in the C++ producer.
*/

#if LANGUAGE_CPP


/*
    This routine adds the initialisation of the tag n, obtained from a
    call to an allocation function, with the expression a to the bitstream
    bs.  If d is not the null expression then any exceptions thrown by a
    must be caught and the allocated memory freed using d.
*/

static BITSTREAM *
enc_init_new(BITSTREAM *bs, ulong n, EXP a, EXP d)
{
	EXP a0 = new_try_body(a);
	EXP a1 = DEREF_exp(exp_assign_ref(a0));
	EXP a2 = DEREF_exp(exp_assign_arg(a0));
	COPY_ulong(exp_dummy_no(a1), n);
	if (IS_NULL_exp(d)) {
		/* Simple initialisation */
		a = DEREF_exp(exp_try_block_body(a));
		bs = enc_stmt(bs, a);
	} else {
		/* Initialisation with deletion */
		int uc;
		ulong ex;
		TYPE s = NULL_type;
		ulong ptr = LINK_NONE;
		ulong prev = alloc_counter;
		TYPE t = DEREF_type(exp_type(a2));
		EXP b = DEREF_exp(exp_dealloc_term(d));
		if (IS_exp_nof(a2) && !IS_NULL_exp(b)) {
			/* Declare array initialisation counter */
			s = DEREF_type(type_array_sub(t));
			ptr = unit_no(bs, NULL_id, VAR_tag, 1);
			alloc_counter = ptr;
			bs = enc_loop_decl(bs, ptr, n, s, 1, NULL_off,
					   NULL_type);
		} else {
			alloc_counter = LINK_NONE;
		}
		bs = enc_try_start(bs, &ex,(unsigned)2);
		COPY_ulong(exp_try_block_no(a), ex);
		a = DEREF_exp(exp_try_block_body(a));
		bs = enc_stmt(bs, a);
		bs = enc_try_end(bs, ex);
		uc = unreached_code;
		if (ptr == LINK_NONE) {
			ENC_SEQ_SMALL(bs, 1);
		} else {
			/* Destroy a partially constructed array */
			EXP b1 = b;
			ulong lab1 = unit_no(bs, NULL_id, VAR_label, 1);
			ulong lab2 = unit_no(bs, NULL_id, VAR_label, 1);
			ENC_SEQ_SMALL(bs, 2);
			ENC_conditional(bs);
			ENC_make_label(bs, lab1);
			ENC_SEQ_SMALL(bs, 1);
			bs = enc_loop_test(bs, ptr, n, s, lab1, ntest_not_eq);
			ENC_repeat(bs);
			ENC_make_label(bs, lab2);
			ENC_make_top(bs);
			ENC_SEQ_SMALL(bs, 2);
			bs = enc_loop_incr(bs, ptr, s, 1);
			if (IS_exp_nof(b1)) {
				b1 = DEREF_exp(exp_nof_pad(b1));
			}
			bs = enc_term_local(bs, ptr, NULL_off, 1, s, b1, 0);
			bs = enc_loop_test(bs, ptr, n, s, lab2, ntest_eq);
			ENC_make_top(bs);
		}
		COPY_exp(exp_dealloc_term(d), NULL_exp);
		bs = enc_dealloc(bs, d, n);
		COPY_exp(exp_dealloc_term(d), b);
		bs = enc_rethrow(bs);
		alloc_counter = prev;
		unreached_code = uc;
	}
	return bs;
}


/*
    This routine adds the allocation expression e to the bitstream bs.
*/

BITSTREAM *
enc_alloc(BITSTREAM *bs, EXP e)
{
	EXP a = DEREF_exp(exp_alloc_call(e));
	EXP b = DEREF_exp(exp_alloc_init(e));
	EXP c = DEREF_exp(exp_alloc_size(e));
	EXP d = DEREF_exp(exp_alloc_garbage(e));
	if (IS_NULL_exp(b) && IS_NULL_exp(c)) {
		/* Simple case */
		bs = enc_exp(bs, a);
	} else {
		/* Complex case */
		ulong n;
		ulong lab;
		int bf = 0;
		unsigned seq = 0;
		EXP c1 = NULL_exp;
		DECL_SPEC ds = dspec_none;
		TYPE t = DEREF_type(exp_type(a));
		TYPE s = DEREF_type(type_ptr_sub(t));
		LIST(TYPE)throws = NULL_list(TYPE);

		/* Check exception deallocator */
		if (!IS_NULL_exp(b)) {
			throws = DEREF_list(exp_try_block_ttypes(b));
			seq = 1;
		}
		if (!IS_NULL_exp(d)) {
			EXP d1 = DEREF_exp(exp_dealloc_call(d));
			EXP d2 = DEREF_exp(exp_dealloc_size(d));
			if (IS_NULL_exp(d1) && IS_NULL_exp(d2)) {
				d = NULL_exp;
			} else if (output_except && output_partial) {
				if (!IS_NULL_list(throws)) {
					ds = dspec_mutable;
				} else {
					d = NULL_exp;
				}
			} else {
				d = NULL_exp;
			}
		}

		/* Introduce identity for non-constant array size */
		if (!IS_NULL_exp(c)) {
			c1 = DEREF_exp(exp_dummy_value(c));
			if (!IS_exp_int_lit(c1)) {
				n = unit_no(bs, NULL_id, VAR_tag, 1);
				COPY_exp(exp_dummy_value(c), NULL_exp);
				COPY_ulong(exp_dummy_no(c), n);
				ENC_identify(bs);
				bs = enc_access(bs, dspec_none);
				ENC_make_tag(bs, n);
				bs = enc_exp(bs, c1);
			}
			seq += 2;
		}

		/* Introduce variable for call to allocation function */
		n = unit_no(bs, NULL_id, VAR_tag, 1);
		ENC_variable(bs);
		bs = enc_access(bs, ds);
		ENC_make_tag(bs, n);
		bs = enc_exp(bs, a);
		ENC_SEQ_SMALL(bs, 1);

		/* Check for null pointers */
		lab = unit_no(bs, NULL_id, VAR_label, 1);
		ENC_conditional(bs);
		ENC_make_label(bs, lab);
		if (seq) {
			ENC_SEQUENCE(bs, seq);
		}
		bs = enc_loop_test(bs, n, LINK_NONE, s, lab, ntest_not_eq);

		/* Deal with array dimensions */
		if (!IS_NULL_exp(c)) {
			/* Assign array size */
			BITSTREAM *ts;
			TYPE tz = type_size_t;
			TYPE tc = DEREF_type(exp_type(c));
			ENC_assign(bs);
			bs = enc_special(bs, TOK_ptr_to_ptr);
			ts = start_bitstream(NIL(FILE), bs->link);
			ts = enc_alignment(ts, s);
			ts = enc_alignment(ts, tz);
			ts = enc_cont_op(ts, t, &bf);
			ts = enc_shape(ts, t);
			ENC_obtain_tag(ts);
			ENC_make_tag(ts, n);
			bs = enc_bitstream(bs, ts);
			if (!eq_type_rep(tc, tz, 0)) {
				/* Cast array size to size_t */
				ENC_change_variety(bs);
				bs = enc_error_treatment(bs, tz);
				bs = enc_variety(bs, tz);
			}
			bs = enc_exp(bs, c);

			/* Increase pointer */
			bs = enc_assign_op(bs, t, &bf);
			ENC_obtain_tag(bs);
			ENC_make_tag(bs, n);
			ENC_add_to_ptr(bs);
			bs = enc_cont_op(bs, t, &bf);
			bs = enc_shape(bs, t);
			ENC_obtain_tag(bs);
			ENC_make_tag(bs, n);
			bs = enc_extra_offset(bs, s, off_size_t, 1);
		}

		/* Call initialiser */
		if (!IS_NULL_exp(b)) {
			bs = enc_init_new(bs, n, b, d);
		}
		ENC_make_top(bs);

		/* Evaluate result */
		bs = enc_cont_op(bs, t, &bf);
		bs = enc_shape(bs, t);
		ENC_obtain_tag(bs);
		ENC_make_tag(bs, n);
		if (!IS_NULL_exp(c1)) {
			/* Restore size value */
			COPY_exp(exp_dummy_value(c), c1);
		}
		assert(bf == 0);
	}
	return bs;
}


/*
    This routine adds the deallocation expression e to the bitstream bs.
    If the argument is already stored in a tag then this is given by n.
*/

BITSTREAM *
enc_dealloc(BITSTREAM *bs, EXP e, ulong n)
{
	EXP a = DEREF_exp(exp_dealloc_call(e));
	EXP b = DEREF_exp(exp_dealloc_term(e));
	EXP c = DEREF_exp(exp_dealloc_size(e));
	EXP d = DEREF_exp(exp_dealloc_arg(e));
	EXP d1 = DEREF_exp(exp_dummy_value(d));

	/* Use given tag if necessary */
	int var = 1;
	if (n != LINK_NONE) {
		COPY_exp(exp_dummy_value(d), NULL_exp);
		COPY_ulong(exp_dummy_no(d), n);
		var = 0;
	}

	if (IS_NULL_exp(b) && IS_NULL_exp(c)) {
		/* Simple case */
		bs = enc_exp(bs, a);

	} else {
		/* Complex case */
		NAT i;
		TYPE t = DEREF_type(exp_type(d));
		TYPE s = DEREF_type(type_ptr_sub(t));

		/* Check for virtual deallocators (see make_delete_exp) */
		if (!IS_NULL_exp(a) && IS_exp_paren(a)) {
			if (!IS_NULL_exp(b)) {
				a = NULL_exp;
			}
		}

		/* Introduce variable for deallocation argument */
		if (var) {
			unsigned seq = 2;
			ulong lab = unit_no(bs, NULL_id, VAR_label, 1);
			n = unit_no(bs, NULL_id, VAR_tag, 1);
			COPY_exp(exp_dummy_value(d), NULL_exp);
			COPY_ulong(exp_dummy_no(d), n);
			ENC_variable(bs);
			bs = enc_access(bs, dspec_none);
			ENC_make_tag(bs, n);
			bs = enc_exp(bs, d1);

			/* Check for null pointers */
			if (!IS_NULL_exp(c)) {
				seq = 1;
			}
			ENC_conditional(bs);
			ENC_make_label(bs, lab);
			ENC_SEQ_SMALL(bs, seq);
			bs = enc_loop_test(bs, n, LINK_NONE, s, lab,
					   ntest_not_eq);
		} else {
			if (IS_NULL_exp(c))ENC_SEQ_SMALL(bs, 1);
		}

		/* Introduce identity for array size */
		if (!IS_NULL_exp(c)) {
			if (IS_exp_dummy(c)) {
				int bf = 0;
				BITSTREAM *ts;
				TYPE tz = type_size_t;
				ulong m = unit_no(bs, NULL_id, VAR_tag, 1);
				COPY_ulong(exp_dummy_no(c), m);

				/* Find array size */
				ENC_identify(bs);
				bs = enc_access(bs, dspec_none);
				ENC_make_tag(bs, m);
				ENC_contents(bs);
				bs = enc_shape(bs, tz);
				bs = enc_special(bs, TOK_ptr_to_ptr);
				ts = start_bitstream(NIL(FILE), bs->link);
				ts = enc_alignment(ts, s);
				ts = enc_alignment(ts, tz);
				ENC_add_to_ptr(ts);
				ts = enc_cont_op(ts, t, &bf);
				ts = enc_shape(ts, t);
				ENC_obtain_tag(ts);
				ENC_make_tag(ts, n);
				ts = enc_extra_offset(ts, s, off_size_t, -1);
				bs = enc_bitstream(bs, ts);
				assert(bf == 0);
			}

			/* Construct dummy array type */
			if (!IS_NULL_exp(b)) {
				MAKE_nat_calc(c, i);
				MAKE_type_array(cv_none, s, i, s);
				ENC_SEQ_SMALL(bs, 1);
			}
		}

		/* Encode destructors */
		if (!IS_NULL_exp(b)) {
			bs = enc_term_local(bs, n, NULL_off, 1, s, b, 0);
			if (!IS_NULL_exp(c)) {
				/* Destroy dummy array type */
				ulong tok;
				CV_SPEC cv;
				IDENTIFIER tid;
				DESTROY_type_array(destroy, cv, tid, s, i, s);
				DESTROY_nat_calc(destroy, c, tok, i);
				UNUSED(tok);
				UNUSED(tid);
				UNUSED(cv);
				UNUSED(c);
				UNUSED(s);
			}
		}

		/* Encode deallocation function call */
		bs = enc_exp(bs, a);
		if (var) {
			/* End conditional */
			ENC_make_top(bs);
		}
	}
	COPY_exp(exp_dummy_value(d), d1);
	return bs;
}


#endif /* LANGUAGE_CPP */
#endif /* TDF_OUTPUT */
