/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <string.h>
#include <stdio.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include <tdf/capsule.h>

#include <utility/config.h>
#include <utility/version.h>
#include "c_types.h"

#include <utility/error.h>
#include <utility/catalog.h>
#include <utility/buffer.h>
#include <utility/ustring.h>
#include <utility/xalloc.h>

#include <parse/constant.h>
#include <parse/file.h>

#include <construct/basetype.h>
#include <construct/check.h>
#include <construct/class.h>
#include <construct/construct.h>
#include <construct/convert.h>
#include <construct/copy.h>
#include <construct/destroy.h>
#include <construct/exception.h>
#include <construct/function.h>
#include <construct/identifier.h>
#include <construct/initialise.h>
#include <construct/namespace.h>
#include <construct/redeclare.h>
#include <construct/statement.h>
#include <construct/token.h>
#include <construct/variable.h>

#include <output/tdf.h>
#include <output/capsule.h>
#include <output/compile.h>
#include <output/diag3.h>
#include <output/encode.h>
#include <output/exp.h>
#include <output/init.h>
#include <output/mangle.h>
#include <output/shape.h>
#include <output/stmt.h>
#include <output/struct.h>
#include <output/tok.h>
#include <output/throw.h>

#include "ctype_ops.h"
#include "exp_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "nspace_ops.h"
#include "tok_ops.h"
#include "type_ops.h"
#include "virt_ops.h"


/*
    This list contains all the inline and implicit functions and
    literal constants defined in the program.
*/

LIST(IDENTIFIER)pending_funcs = NULL_list(IDENTIFIER);


/*
    This routine checks whether the identifier id is used but not defined
    because, although it has external linkage, its mangled name is empty.
*/

static void
check_mangled(IDENTIFIER id)
{
	IDENTIFIER lid = DEREF_id(id_alias(id));
	DECL_SPEC ds = DEREF_dspec(id_storage(lid));
	if (!(ds & dspec_done)) {
		if ((ds & dspec_extern) && !(ds & dspec_defn)) {
			if (ds & (dspec_used | dspec_called)) {
				/* Should have an external name */
				string s = mangle_name(lid, VAR_tag, 0);
				if (s == NULL && has_linkage(lid)) {
					LOCATION loc;
					DEREF_loc(id_loc(lid), loc);
					report(loc, ERR_basic_odr_undef(lid));
				}
			}
		}
		ds |= dspec_done;
		COPY_dspec(id_storage(lid), ds);
	}
	return;
}


/*
    This variable is used to hold the declaration specifiers for the
    current function.
*/

DECL_SPEC crt_func_access = dspec_none;


/*
    This routine adds an optional TDF ACCESS corresponding to the
    declaration specifiers ds.
*/

BITSTREAM *
enc_access(BITSTREAM *bs, DECL_SPEC ds)
{
	if (ds & dspec_mutable) {
		ENC_ON(bs);
		if (output_bugs) {
			/* Needed for old installer bug */
			ENC_add_accesses(bs);
			ENC_visible(bs);
		}
		ENC_long_jump_access(bs);
	} else {
		ENC_OFF(bs);
	}
	return bs;
}


/*
    This routine adds an optional identifier signature corresponding to id
    to the bitstream bs.  Note that these signatures were only introduced
    in TDF version 4.0.
*/

static BITSTREAM *
enc_signature(BITSTREAM *bs, IDENTIFIER id)
{
#if (TDF_major >= 4)
	ENC_OFF(bs);
#endif
	UNUSED(id);
	return bs;
}


/*
    This routine checks whether the local static variable id should be
    made a common tag.  It returns 2 if it should and 1 otherwise (see
    enc_tagdec).  The prefix to be used for mangling the name is returned
    via ps.
*/

static int
is_common_tag(IDENTIFIER id, string *ps)
{
	NAMESPACE ns = DEREF_nspace(id_parent(id));
	IDENTIFIER pid = DEREF_id(nspace_name(ns));
	if (!IS_NULL_id(pid) && IS_id_function_etc(pid)) {
		DECL_SPEC ds = DEREF_dspec(id_storage(pid));
		if ((ds & dspec_inline) && (ds & dspec_extern)) {
			string s = mangle_name(pid, VAR_tag, 1);
			if (s) {
				*ps = s;
				return 2;
			}
		}
	}
	return 1;
}


/*
    This routine adds the tag declaration for the static variable id to
    the bitstream bs.  If id has a constant initialiser and no destructor
    then this is mapped to a simple tag definition, otherwise the
    initialisation and termination need to be done dynamically.
*/

static BITSTREAM *
enc_static_var(BITSTREAM *bs, IDENTIFIER id)
{
	ulong n;
	int ext = 0;
	BITSTREAM *ts;
	string s = NULL;
	int i = in_static_init;
	int uc = unreached_code;
	int var = is_common_tag(id, &s);
	TYPE t = DEREF_type(id_variable_type(id));
	EXP a = DEREF_exp(id_variable_init(id));
	EXP b = DEREF_exp(id_variable_term(id));

	/* Encode the tag declaration */
	if (var == 2 || output_all) {
		ext = 1;
	}
	IGNORE capsule_id(id, VAR_tag);
	n = DEREF_ulong(id_no(id));
	if (ext) {
		/* Make up external name for variable */
		string sn = mangle_common(s, id);
		n = capsule_name(n, &sn, VAR_tag);
	}
	enc_tagdec(id, n, t, var);

	/* Encode the tag definition */
	ts = enc_tagdef_start(id, n, t, var);
	in_static_init = 1;
	unreached_code = 0;
	if (!IS_NULL_exp(a) && IS_exp_dynamic(a)) {
		/* Dynamic initialiser */
		ts = enc_null_exp(ts, t);
	} else {
		/* Static initialiser */
		if (var == 2) {
			ts = enc_null_exp(ts, t);
			if (is_null_exp(a)) {
				a = NULL_exp;
			}
		} else {
			ts = enc_exp(ts, a);
			a = NULL_exp;
		}
	}
	unreached_code = uc;
	in_static_init = i;
	enc_tagdef_end(ts);

	/* Encode dynamic components */
	if (!IS_NULL_exp(a) || !IS_NULL_exp(b)) {
		/* Declare flag */
		ulong m1;
		int dummy = 0;
		EXP b1 = NULL_exp;
		TYPE si = type_sint;
		ulong m = capsule_no(NULL_string, VAR_tag);
		if (ext) {
			/* Make up external name for flag */
			string sm = mangle_common(s, NULL_id);
			m = capsule_name(m, &sm, VAR_tag);
		}
		enc_tagdec(NULL_id, m, si, var);
		ts = enc_tagdef_start(NULL_id, m, si, var);
		in_static_init = 1;
		ts = enc_make_int(ts, si, 0);
		in_static_init = i;
		enc_tagdef_end(ts);
		if (!IS_NULL_exp(b)) {
			if (!output_term) {
				/* Set up terminator if necessary */
				b1 = b;
				b = NULL_exp;
				make_term_global(t, &b1);
				if (IS_NULL_exp(a)) {
					a = make_dummy_init(t);
					dummy = 1;
				}
			}
			term_no++;
		}

		/* Encode initialiser */
		ENC_SEQ_SMALL(bs, 1);
		m1 = link_no(bs, m, VAR_tag);
		if (!IS_NULL_exp(a)) {
			unsigned seq = 2;
			ulong n1 = link_no(bs, n, VAR_tag);
			if (!IS_NULL_exp(b1)) {
				seq = 3;
			}
			bs = enc_flag_test(bs, m1, seq, 0, ntest_eq);
			bs = enc_init_tag(bs, n1, NULL_off, 0, t, a, b1, 2);
			if (dummy) {
				free_exp(a, 1);
			}
		}
		ENC_assign(bs);
		ENC_obtain_tag(bs);
		ENC_make_tag(bs, m1);
		bs = enc_make_int(bs, si, 1);
		if (!IS_NULL_exp(a)) {
			ENC_make_top(bs);
		}

		/* Encode destructor */
		if (!IS_NULL_exp(b)) {
			ts = term_static_func;
			ts = enc_term_global(ts, n, t, b, m);
			term_static_func = ts;
		}
	}
	return bs;
}


/*
    This routine adds the start of a local tag declaration for the variable
    id to the bitstream bs.  The definition body has to be added later.
    Any destructor for id is returned via d.  var is 1 to indicate that
    id is a variable as opposed to an identity.  A value of 2 or more for
    var indicates that the variable should be just declared rather than
    defined.  This is only used for automatic variables.  e gives the
    corresponding declaration statement for use with diagnostics.
*/

BITSTREAM *
enc_variable(BITSTREAM *bs, IDENTIFIER id, int var, EXP *d, EXP e)
{
	/* Check for previous definition */
	IDENTIFIER lid = DEREF_id(id_alias(id));
	DECL_SPEC ds = DEREF_dspec(id_storage(lid));
	if (ds & dspec_done) {
		return bs;
	}
	ds |= dspec_done;

	if (ds & dspec_auto) {
		/* Local variable definition */
		int dummy = 0;
		ulong n = unit_no(bs, id, VAR_tag, 1);
		EXP a = DEREF_exp(id_variable_init(id));
		EXP b = DEREF_exp(id_variable_term(id));
		EXP b1 = NULL_exp;
		TYPE t = DEREF_type(id_variable_type(id));
		COPY_dspec(id_storage(lid), ds);
		if (var) {
			if (!IS_NULL_exp(b)) {
				if (output_except || var == 4) {
					/* Set up terminator variable */
					bs = make_term_local(bs, t, &b, var);
					b1 = b;
					if (IS_NULL_exp(a) && var == 1) {
						a = make_dummy_init(t);
						dummy = 1;
					}
				}
			}
			ENC_variable(bs);
		} else {
			ENC_identify(bs);
		}
		bs = enc_access(bs, ds);
		ENC_make_tag(bs, n);
		if (IS_NULL_exp(a) || var >= 2) {
			ENC_make_value(bs);
			bs = enc_shape(bs, t);
		} else if (var) {
			bs = enc_init_local(bs, a, b1, n, t, e);
		} else {
			if (!IS_NULL_exp(e)) {
				BITSTREAM *ts = enc_diag_begin(&bs);
				ts = enc_addr_exp(ts, t, a);
				bs = enc_diag_end(bs, ts, e, 1);
			} else {
				bs = enc_addr_exp(bs, t, a);
			}
		}
		if (dummy) {
			free_exp(a, 1);
		}
		if (d)*d = b;
	} else if (!(ds & dspec_linkage)) {
		/* Static variable definition */
		if (IS_id_variable(id)) {
			COPY_dspec(id_storage(lid), ds);
			bs = enc_static_var(bs, id);
		}
	}
	return bs;
}


/*
    This routine encodes the definition of the function id with body e
    to the bitstream bs.
*/

static BITSTREAM *
enc_func_defn(BITSTREAM *bs, IDENTIFIER id, EXP e)
{
	unsigned n;
	unsigned npids;
	int is_main = 0;
	EXP r = NULL_exp;
	unsigned seq = 0;
	unsigned rpids = 0;
	unsigned epids = 0;
	BITSTREAM *ts = NULL;
	int diag = output_diag;
	LIST(IDENTIFIER)qids;
	IDENTIFIER eid = NULL_id;
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	TYPE fn = DEREF_type(id_function_etc_type(id));
	TYPE ret = DEREF_type(type_func_ret(fn));
	int ell = DEREF_int(type_func_ellipsis(fn));
	LIST(IDENTIFIER)pids = DEREF_list(type_func_pids(fn));
#if LANGUAGE_CPP
	EXP post = NULL_exp;
	int throws = output_except;
	LIST(TYPE)except = DEREF_list(type_func_except(fn));
#endif

	/* Check for main routine */
	if (ds & dspec_main) {
		HASHID nm = DEREF_hashid(id_name(id));
		if (IS_hashid_name(nm)) {
			ds &= ~dspec_friend;
			is_main = 1;
			seq++;
		}
	}

	/* Check exception specifier */
#if LANGUAGE_CPP
	if (throws) {
		if (output_partial) {
			post = except_postlude(id);
		}
		if (IS_NULL_exp(post)) {
			if (EQ_list(except, univ_type_set)) {
				throws = 0;
			} else if (ds & (dspec_friend | dspec_implicit)) {
				/* No exception specification required */
				throws = 0;
			}
		} else {
			ds |= dspec_mutable;
		}
	}
#endif

	/* Encode start of function */
	common_no = 0;
	crt_func_access = ds;
	clear_params();
	ENC_make_proc(bs);
	if (pass_complex_type(ret)) {
		ENC_top(bs);
		rpids = 1;
	} else {
		if (IS_type_top_etc(ret)) {
			last_params[DUMMY_return] = LINK_ZERO;
		} else if (is_main) {
			MAKE_exp_null(ret, r);
		} else {
			MAKE_exp_value(ret, r);
		}
		bs = enc_shape(bs, ret);
	}
	MAKE_exp_return_stmt(type_bottom, r, r);

	/* Encode 'this' parameter */
	if (IS_id_mem_func(id)) {
		CLASS_TYPE ct = parent_class(id);
		IDENTIFIER pid = this_param(id, 0);
		assert(!IS_NULL_id(pid));
		CONS_id(pid, pids, pids);
		epids = extra_constr_args(id, ct);
		last_class = ct;
	}

	/* Encode number of parameters */
	npids = LENGTH_list(pids);
	ENC_LIST(bs, rpids + npids + epids);
	qids = pids;

	/* Encode function return parameter */
	if (rpids) {
		ulong pn = unit_no(bs, NULL_id, VAR_tag, 1);
		ENC_pointer(bs);
		bs = enc_alignment(bs, ret);
		bs = enc_access(bs, ds);
		ENC_make_tag(bs, pn);
		last_params[DUMMY_return] = pn;
	}

	/* Encode normal function parameters */
	n = 0;
	while (!IS_NULL_list(pids)) {
		IDENTIFIER pid = DEREF_id(HEAD_list(pids));
		DECL_SPEC pds = DEREF_dspec(id_storage(pid));
		TYPE pt = DEREF_type(id_parameter_type(pid));
		ulong pn = unit_no(bs, pid, VAR_tag, 1);
		if (n < DUMMY_params) {
			last_params[n] = pn;
			n++;
		}
		if (pass_complex_type(pt)) {
			/* Introduce identity for complex parameters */
			ulong pm = unit_no(bs, NULL_id, VAR_tag, 1);
			ENC_pointer(bs);
			bs = enc_alignment(bs, pt);
			if (ts == NULL) {
				ts = start_bitstream(NIL(FILE), bs->link);
			}
			ENC_identify(ts);
			ts = enc_access(ts, ds);
			ENC_make_tag(ts, pn);
			ENC_contents(ts);
			ENC_pointer(ts);
			ts = enc_alignment(ts, pt);
			ENC_obtain_tag(ts);
			ENC_make_tag(ts, pm);
			pn = pm;
		} else if (pds & dspec_virtual) {
			/* Introduce variable for weak parameter types */
			ulong pm = unit_no(bs, NULL_id, VAR_tag, 1);
			TYPE pu = arg_promote_type(pt, KILL_err);
			bs = enc_shape(bs, pu);
			if (ts == NULL) {
				ts = start_bitstream(NIL(FILE), bs->link);
			}
			ENC_variable(ts);
			ts = enc_access(ts, ds);
			ENC_make_tag(ts, pn);
			if (IS_type_integer(pt)) {
				ENC_change_variety(ts);
				ts = enc_error_treatment(ts, pt);
				ts = enc_variety(ts, pt);
			} else {
				ENC_change_floating_variety(ts);
				ENC_impossible(ts);
				ts = enc_flvar(ts, pt);
			}
			ENC_contents(ts);
			ts = enc_shape(ts, pu);
			ENC_obtain_tag(ts);
			ENC_make_tag(ts, pm);
			pn = pm;
		} else {
			/* Simple parameter */
			bs = enc_shape(bs, pt);
		}
		bs = enc_access(bs, ds);
		ENC_make_tag(bs, pn);
		pids = TAIL_list(pids);
	}

	/* Encode extra function parameters */
	while (epids) {
		ulong pn = unit_no(bs, NULL_id, VAR_tag, 1);
		bs = enc_shape(bs, type_sint);
		bs = enc_access(bs, ds);
		ENC_make_tag(bs, pn);
		last_params[DUMMY_extra] = pn;
		epids--;
	}

	/* Encode ellipsis parameter */
	if (ell & FUNC_ELLIPSIS) {
		ulong pn;
		eid = ellipsis_param(id);
		assert(!IS_NULL_id(eid));
		pn = unit_no(bs, eid, VAR_tag, 1);
		ENC_ON(bs);
		ENC_make_tag(bs, pn);
		bs = enc_access(bs, ds);
		last_params[DUMMY_ellipsis] = pn;
	} else {
		ENC_OFF(bs);
	}

	/* Allow for reference parameters */
	if (ts) {
		bs = join_bitstreams(bs, ts);
	}
	ts = bs;

	/* Encode function body */
	seq += stmt_length(e);
	if (diag) {
		bs = start_bitstream(NIL(FILE), bs->link);
	}
#if LANGUAGE_CPP
	if (throws) {
		bs = enc_try_func(bs, post);
	}
#endif
	ENC_SEQUENCE(bs, seq);
	if (is_main) {
		bs = enc_special(bs, TOK_start);
	}
	bs = enc_compound_stmt(bs, e);
#if LANGUAGE_CPP
	if (throws) {
		bs = enc_catch_func(bs, except, post);
	}
#endif
	if (diag) {
		BITSTREAM *us = enc_diag_begin(&bs);
		us = enc_stmt(us, r);
		bs = enc_diag_end(bs, us, r, 1);
		bs = enc_diag_params(ts, qids, bs, e);
	} else {
		bs = enc_stmt(bs, r);
	}
	free_exp(r, 1);

	/* Clear parameter tag numbers */
	pids = qids;
	while (!IS_NULL_list(pids)) {
		IDENTIFIER pid = DEREF_id(HEAD_list(pids));
		clear_no(pid);
		pids = TAIL_list(pids);
	}
	if (!IS_NULL_id(eid)) {
		clear_no(eid);
	}
	crt_func_access = dspec_none;
	clear_params();
	return bs;
}


/*
    This routine adds the start of a declaration of the tag with identifier
    id, capsule number n and type t in the tag declaration unit.  var
    is 0 if the tag is an identity, 1 for a variable and 2 for a common tag.
    The actual tag type has to be added (t is only used for access checks).
*/

BITSTREAM *
enc_tagdec_start(IDENTIFIER id, ulong n, TYPE t, int var)
{
	unsigned use = USAGE_DECL;
	BITSTREAM *bs = start_bitstream(NIL(FILE), tagdec_unit->link);
	ulong m = link_no(bs, n, VAR_tag);
	if (var == 0) {
		ENC_make_id_tagdec(bs);
	} else if (var == 1) {
		ENC_make_var_tagdec(bs);
	} else {
		ENC_common_tagdec(bs);
		use |= USAGE_COMMON;
	}
	ENC_INT(bs, m);
	bs = enc_access(bs, dspec_none);
	bs = enc_signature(bs, id);
	record_usage(n, VAR_tag, use);
	UNUSED(t);
	return bs;
}


/*
    This routine ends the tag declaration started by enc_tagdec_start.
*/

void
enc_tagdec_end(BITSTREAM *bs)
{
	count_item(bs);
	tagdec_unit = join_bitstreams(tagdec_unit, bs);
	return;
}


/*
    This routine adds a complete tag declaration to the tag declaration
    unit if it has not already been declared.
*/

void
enc_tagdec(IDENTIFIER id, ulong n, TYPE t, int var)
{
	unsigned u = find_usage(n, VAR_tag);
	if (!(u & USAGE_DECL)) {
		BITSTREAM *bs = enc_tagdec_start(id, n, t, var);
		bs = enc_shape(bs, t);
		enc_tagdec_end(bs);
	}
	return;
}


/*
    This routine adds a definition of the tag with identifier id, capsule
    number n and type t to the tag definition unit.  var is as in
    enc_tagdec_start.  The routine returns a bitstream to allow the actual
    definition to be added.
*/

BITSTREAM *
enc_tagdef_start(IDENTIFIER id, ulong n, TYPE t, int var)
{
	unsigned use = USAGE_DEFN;
	BITSTREAM *bs = start_bitstream(NIL(FILE), tagdef_unit->link);
	ulong m = link_no(bs, n, VAR_tag);
	if (var == 0) {
		ENC_make_id_tagdef(bs);
	} else if (var == 1) {
		ENC_make_var_tagdef(bs);
	} else {
		ENC_common_tagdef(bs);
		use |= USAGE_COMMON;
	}
	ENC_INT(bs, m);
	if (var) {
		bs = enc_access(bs, dspec_none);
	}
	bs = enc_signature(bs, id);
	record_usage(n, VAR_tag, use);
	UNUSED(t);
	return bs;
}


/*
    This routine ends the tag definition started by enc_tagdef_start.
*/

void
enc_tagdef_end(BITSTREAM *bs)
{
	count_item(bs);
	tagdef_unit = join_bitstreams(tagdef_unit, bs);
	return;
}


/*
    This routine creates a tag declaration and definition for the tag
    id of type t and definition e.  var is true for a variable tag.
    The expression d gives any associated destructor.  id can be the
    null identifier, indicating a local tag, and e can be the null
    expression, indicating that the tag is only declared.  The routine
    returns the external (capsule) tag number.
*/

ulong
make_tagdef(IDENTIFIER id, TYPE t, EXP e, EXP d, int var)
{
	ulong n;
	int fn = 0;
	int def = 1;
	LOCATION loc;

	/* Find the tag number */
	bad_crt_loc++;
	loc = crt_loc;
	if (IS_NULL_id(id)) {
		n = capsule_no(NULL_string, VAR_tag);
	} else {
		PTR(LOCATION)ploc = id_loc(id);
		DEREF_loc(ploc, crt_loc);
		crt_enc_loc = ploc;
		IGNORE capsule_id(id, VAR_tag);
		n = DEREF_ulong(id_no(id));
		if (IS_id_function_etc(id)) {
			var = 0;
			fn = 1;
		}
	}

	/* Encode the declaration */
	enc_tagdec(id, n, t, var);

	/* Check for definition */
	if (!IS_NULL_exp(e)) {
		BITSTREAM *bs;
		EXP d1 = NULL_exp;
		int uc = unreached_code;
		if (!IS_NULL_exp(d)) {
			if (!output_term) {
				/* Set up terminator if necessary */
				d1 = d;
				d = NULL_exp;
				make_term_global(t, &d1);
			}
			term_no++;
		}
		bs = enc_tagdef_start(id, n, t, var);
		unreached_code = 0;
		if (fn) {
			/* Function definition */
			bs = enc_func_defn(bs, id, e);
		} else if (var) {
			/* Variable definition */
			bs = enc_init_global(bs, e, d1, n, t);
		} else {
			/* Identity definition */
			int i = in_static_init;
			in_static_init = 1;
			bs = enc_addr_exp(bs, t, e);
			in_static_init = i;
		}
		unreached_code = uc;
		enc_tagdef_end(bs);

		/* Check for destructor */
		if (!IS_NULL_exp(d)) {
			BITSTREAM *ts = term_func;
			ts = enc_term_global(ts, n, t, d, LINK_NONE);
			term_func = ts;
		}
	} else {
		/* Only declared */
		if (!IS_NULL_id(id)) {
			string s = NULL;
			IGNORE capsule_name(n, &s, VAR_tag);
			if (s == NULL) {
				if (has_linkage(id)) {
					/* Doesn't have external name */
					report(crt_loc,
					       ERR_basic_odr_undef(id));
				}
				s = mangle_anon();
			}
			IGNORE capsule_name(n, &s, VAR_tag);
			def = 0;
		}
	}
	if (!IS_NULL_id(id) && output_diag) {
		HASHID nm = DEREF_hashid(id_name(id));
		if (!IS_hashid_anon(nm)) {
			enc_diag_id(id, def);
		}
	}
	crt_loc = loc;
	bad_crt_loc--;
	return n;
}


/*
    This routine creates the dynamic initialisation and termination
    functions.
*/

void
enc_dynamic_init (void)
{
	BITSTREAM *bs;
	ulong m1 = LINK_NONE;
	ulong m2 = LINK_NONE;
	ulong init = init_no;
	ulong term = term_no;
	int diag = output_diag;
	if (output_all) {
		diag = 1;
	}

	/* Create the termination function */
	if (term) {
		if (output_term) {
			/* Define the termination function */
			TYPE t = dummy_func;
			m1 = capsule_no(NULL_string, VAR_tag);
			if (diag) {
				enc_diag_init("__term", m1, t);
			}
			enc_tagdec(NULL_id, m1, t, 0);
			bs = enc_tagdef_start(NULL_id, m1, t, 0);
			ENC_make_proc(bs);
			ENC_top(bs);
			ENC_LIST_SMALL(bs, 0);
			ENC_OFF(bs);
			ENC_SEQUENCE(bs, term);
			bs = join_bitstreams(bs, term_static_func);
			bs = join_bitstreams(bs, term_func);
			ENC_return(bs);
			ENC_make_top(bs);
			enc_tagdef_end(bs);

			/* Define the termination link */
			m2 = capsule_no(NULL_string, VAR_tag);
			bs = enc_tagdec_start(NULL_id, m2, NULL_type, 1);
			bs = enc_special(bs, TOK_destr_type);
			enc_tagdec_end(bs);
			bs = enc_tagdef_start(NULL_id, m2, NULL_type, 1);
			bs = enc_special(bs, TOK_destr_null);
			enc_tagdef_end(bs);
			init++;
		}
		init++;
	}

	/* Create the initialisation function */
	if (init) {
		int var = 1;
		TYPE t = type_sint;
		TYPE s = t;
		string nm = mangle_init();
		ulong n1 = capsule_no(nm, VAR_tag);
		if (output_init) {
			/* Initialisation function required */
			t = dummy_func;
			var = 0;
		}
		if (diag) {
			enc_diag_init("__init", n1, t);
		}
		enc_tagdec(NULL_id, n1, t, var);
		bs = enc_tagdef_start(NULL_id, n1, t, var);
		if (var == 0) {
			ENC_make_proc(bs);
			bs = enc_shape(bs, s);
			ENC_LIST_SMALL(bs, 0);
			ENC_OFF(bs);
		} else {
			ENC_initial_value(bs);
		}
		ENC_SEQUENCE(bs, init);
		if (term) {
			/* Initialise termination function */
			bs = enc_special(bs, TOK_destr_init);
		}
		bs = join_bitstreams(bs, init_func);
		if (m1 != LINK_NONE) {
			/* Set up termination function */
			ulong n;
			BITSTREAM *ts;
			bs = enc_special(bs, TOK_destr_global);
			ts = start_bitstream(NIL(FILE), bs->link);
			n = link_no(ts, m2, VAR_tag);
			ENC_obtain_tag(ts);
			ENC_make_tag(ts, n);
			ENC_make_null_ptr(ts);
			ts = enc_special(ts, TOK_empty_align);
			n = link_no(ts, m1, VAR_tag);
			ENC_obtain_tag(ts);
			ENC_make_tag(ts, n);
			bs = enc_bitstream(bs, ts);
		}
		if (var == 0) {
			ENC_return(bs);
		}
		bs = enc_make_int(bs, s, 1);
		enc_tagdef_end(bs);

		/* Set up initialisation variable */
		if (var == 0 && nm == NULL) {
			ulong n2 = capsule_no(NULL_string, VAR_tag);
			if (diag) {
				enc_diag_init("__init2", n2, s);
			}
			enc_tagdec(NULL_id, n2, s, 1);
			bs = enc_tagdef_start(NULL_id, n2, s, 1);
			ENC_initial_value(bs);
			ENC_apply_proc(bs);
			bs = enc_shape(bs, s);
			n1 = link_no(bs, n1, VAR_tag);
			ENC_obtain_tag(bs);
			ENC_make_tag(bs, n1);
			ENC_LIST_SMALL(bs, 0);
			ENC_OFF(bs);
			enc_tagdef_end(bs);
		}
	}
	return;
}


/*
    This routine creates a token declaration body bitstream for a token
    with external (capsule) number n and sort sorts.  This is only output
    for tokens with at least one parameter to aid in pretty-printing.
*/

void
enc_tokdec(ulong n, const char *sorts)
{
	BITSTREAM *bs = tokdec_unit;
	if (bs) {
		char res = *(sorts++);
		char arg = *sorts;
		if (arg) {
			ulong m = link_no(bs, n, VAR_token);
			record_usage(n, VAR_token, USAGE_DECL);
			ENC_make_tokdec(bs);
			ENC_INT(bs, m);
			bs = enc_signature(bs, NULL_id);
			ENC_token(bs);
#if (TDF_major >= 4)
			/* Result sort first after TDF 4.0 */
			bs = enc_sort(bs,(int)res);
#endif
			ENC_LIST(bs, strlen(sorts));
			while (arg = *(sorts++), arg != 0) {
				bs = enc_sort(bs,(int)arg);
			}
#if (TDF_major < 4)
			/* Result sort last before TDF 4.0 */
			bs = enc_sort(bs,(int)res);
#endif
			count_item(bs);
			tokdec_unit = bs;
		}
	}
	return;
}


/*
    This routine creates a token definition body bitstream for a token
    with external (capsule) number n and sort given by sorts.  This
    includes the allocation of any parameter token numbers, which are
    returned via pars.
*/

BITSTREAM *
enc_tokdef_start(ulong n, const char *sorts, ulong *pars, int d)
{
	char res;
	unsigned i, m;
	BITSTREAM *bs;
	if (d) {
		enc_tokdec(n, sorts);
	}
	record_usage(n, VAR_token, USAGE_DEFN);
	bs = start_bitstream(NIL(FILE), tokdef_unit->link);
	ENC_token_definition(bs);
	res = *(sorts++);
	bs = enc_sort(bs,(int)res);
	m = (unsigned)strlen(sorts);
	ENC_LIST(bs, m);
	for (i = 0; i < m; i++) {
		/* Encode token parameters */
		char arg = sorts[i];
		ulong r = unit_no(bs, NULL_id, VAR_token, 1);
		bs = enc_sort(bs,(int)arg);
		ENC_INT(bs, r);
		pars[i] = r;
	}
	return bs;
}


/*
    This routine adds the definition of the token with external (capsule)
    number n and token definition body ps to the main token definition unit.
*/

void
enc_tokdef_end(ulong n, BITSTREAM *ps)
{
	BITSTREAM *bs = tokdef_unit;
	ulong m = link_no(bs, n, VAR_token);
	ENC_make_tokdef(bs);
	ENC_INT(bs, m);
	bs = enc_signature(bs, NULL_id);
	bs = enc_bitstream(bs, ps);
	count_item(bs);
	tokdef_unit = bs;
	return;
}


/*
    This routine encodes the declaration and, if necessary, the definition
    of the token id.  If def is true then a dummy definition is output even
    if id is not defined. It returns the code letter of the return sort.
*/

int
enc_tokdef(IDENTIFIER id, int def)
{
	int dec;
	ulong n;
	BUFFER *bf;
	unsigned npars = 0;
	IDENTIFIER fid = NULL_id;
	TOKEN tok = DEREF_tok(id_token_sort(id));
	unsigned tag = TAG_tok(tok);
	int r = token_code(tok);

	/* Check for declaration and definition */
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	if (ds & dspec_auto) {
		/* Token parameter */
		LOCATION loc;
		if (ds & dspec_register) {
			return r;
		}
		DEREF_loc(id_loc(id), loc);
		report(loc, ERR_token_scope(id));
		ds |= dspec_register;
		COPY_dspec(id_storage(id), ds);
		clear_no(id);
	}
	if (ds & dspec_defn) {
		def = 1;
	}
	dec = capsule_id(id, VAR_token);
	if (def) {
		if (ds & dspec_done) {
			return r;
		}
	} else if (dec) {
		if (tokdec_unit == NULL) {
			return r;
		}
	} else {
		return r;
	}

	/* Construct token sort */
	bf = clear_buffer(&mangle_buff, NIL(FILE));
	bfputc(bf, r);
	if (tag == tok_func_tag) {
		/* Function token */
		fid = DEREF_id(tok_func_defn(tok));
		tok = func_proc_token(tok);
		tag = TAG_tok(tok);
		if (tag != tok_proc_tag) {
			/* Ellipsis function */
			return r;
		}
	}
	if (tag == tok_proc_tag) {
		/*  Parameters for procedure tokens */
		LIST(IDENTIFIER)p = DEREF_list(tok_proc_bids(tok));
		while (!IS_NULL_list(p)) {
			IDENTIFIER pid = DEREF_id(HEAD_list(p));
			if (!IS_NULL_id(pid) && IS_id_token(pid)) {
				TOKEN ptok = DEREF_tok(id_token_sort(pid));
				int s = token_code(ptok);
				npars++;
				bfputc(bf, s);
			}
			p = TAIL_list(p);
		}
	}
	bfputc(bf, 0);

	/* Output declaration and definition */
	n = DEREF_ulong(id_no(id));
	if (dec) {
		enc_tokdec(n, strlit(bf->start));
	}
	if (def) {
		BITSTREAM *bs;
		ulong std_pars[20];
		ulong *pars = std_pars;
		if (npars >= 20) {
			pars = xmalloc_nof(ulong, npars);
		}
		bs = enc_tokdef_start(n, strlit(bf->start), pars, 0);
		COPY_dspec(id_storage(id), (ds | dspec_done));
		COPY_ulong(id_no(id), LINK_TOKDEF);
		last_params[DUMMY_token] = n;
		if (tag == tok_proc_tag) {
			unsigned i = 0;
			if (IS_NULL_id(fid)) {
				/* Procedure tokens */
				LIST(IDENTIFIER)p, q;
				p = DEREF_list(tok_proc_bids(tok));
				q = p;
				while (!IS_NULL_list(q)) {
					IDENTIFIER pid = DEREF_id(HEAD_list(q));
					if (!IS_NULL_id(pid) && IS_id_token(pid)) {
						DECL_SPEC pds = DEREF_dspec(id_storage(pid));
						pds |= dspec_register;
						COPY_dspec(id_storage(pid), pds);
						COPY_ulong(id_no(pid), pars[i]);
						i++;
					}
					q = TAIL_list(q);
				}
				bs = enc_tokdef_body(bs, id, tok);
				set_proc_token(p);
			} else {
				/* Function tokens */
				ulong m;
				TOKEN res = DEREF_tok(tok_proc_res(tok));
				TYPE ret = DEREF_type(tok_exp_type(res));
				ENC_apply_proc(bs);
				bs = enc_shape(bs, ret);
				IGNORE capsule_id(fid, VAR_tag);
				m = unit_no(bs, fid, VAR_tag, 1);
				ENC_obtain_tag(bs);
				ENC_make_tag(bs, m);
				ENC_LIST(bs, npars);
				while (i < npars) {
					ENC_exp_apply_token(bs);
					ENC_make_tok(bs, pars[i]);
					ENC_LEN_SMALL(bs, 0);
					i++;
				}
				ENC_OFF(bs);
			}
		} else {
			/* Other tokens */
			bs = enc_tokdef_body(bs, id, tok);
		}
		COPY_ulong(id_no(id), n);
		enc_tokdef_end(n, bs);
		if (pars != std_pars) {
			xfree_nof(pars);
		}
	}
	return r;
}


/*
    This routine determines whether a variable declared with specifiers
    ds and type t should be output.  It returns 1 if it should be output
    immediately, 2 if the decision on whether to output should be deferred
    until later, and 0 otherwise.
*/

static int
need_variable(DECL_SPEC ds, TYPE t, EXP e, ulong n)
{
	if (ds & dspec_temp) {
		/* Temporary variables */
		if (ds & dspec_ignore) {
			return 0;
		}
		if (ds & dspec_explicit) {
			return 2;
		}
	}
	if (ds & dspec_defn) {
		/* Output defined variables */
		if (ds & dspec_extern) {
			return 1;
		}
		if (n == LINK_NONE) {
#if LANGUAGE_CPP
			CV_SPEC qual = DEREF_cv(type_qual(t));
			if (qual == (cv_lvalue | cv_const)) {
				/* Defer literal constants */
				return 2;
			}
#else
			UNUSED(t);
#endif
			if (!output_unused) {
				return 2;
			}
			if (!overflow_exp(e)) {
				return 2;
			}
		}
		return 1;
	}
	if (ds & dspec_used) {
		/* Defer used variables */
		return 2;
	}
	return 0;
}


/*
    This routine compiles the global variable or static data member id.
*/

void
compile_variable(IDENTIFIER id, int force)
{
	if (output_capsule) {
		IDENTIFIER lid = DEREF_id(id_alias(id));
		DECL_SPEC ds = DEREF_dspec(id_storage(lid));
		if (!(ds & dspec_done)) {
			TYPE t;
			EXP e, d;
			int output;
			switch (TAG_id(id)) {
			case id_variable_tag:
			case id_stat_member_tag: {
				/* Variables and static data members */
				t = DEREF_type(id_variable_etc_type(lid));
				e = DEREF_exp(id_variable_etc_init(lid));
				d = DEREF_exp(id_variable_etc_term(lid));
				if (!IS_NULL_exp(e) && IS_exp_zero(e)) {
					/* Ignore tentative definitions */
					ds &= ~dspec_defn;
				}
				break;
			}
			case id_enumerator_tag: {
				/* Dummy enumerator values */
				if (!output_unused) {
					return;
				}
				e = DEREF_exp(id_enumerator_value(lid));
				e = eval_exp(e, 1);
				if (!overflow_exp(e)) {
					return;
				}
				t = DEREF_type(exp_type(e));
				d = NULL_exp;
				force = 1;
				break;
			}
			default: {
				/* Shouldn't happen */
				return;
			}
			}
			if (!IS_NULL_exp(d) && IS_exp_paren(d)) {
				/* Ignore parenthesised type information */
				d = DEREF_exp(exp_paren_arg(d));
			}
			if (!(ds & dspec_defn)) {
				/* Object not defined */
				e = NULL_exp;
				d = NULL_exp;
			}
			if (ds & dspec_explicit) {
				/* Explicitly initialised object */
				d = NULL_exp;
			}
			if (force) {
				/* Force output */
				output = 1;
			} else if (!IS_NULL_exp(e) && IS_exp_dynamic(e)) {
				/* Dynamic initialiser */
				output = 1;
			} else if (!IS_NULL_exp(d)) {
				/* Dynamic destructor */
				output = 1;
			} else {
				/* Determine whether to output */
				ulong n = DEREF_ulong(id_no(lid));
				output = need_variable(ds, t, e, n);
				if (output == 2) {
					/* Defer variable until later */
					CONS_id(lid, pending_funcs, pending_funcs);
					output = 0;
				}
			}
			if (output) {
				/* Output variable definition */
				ds |= dspec_done;
				COPY_dspec(id_storage(lid), ds);
				crt_enc_loc = id_loc(lid);
				IGNORE make_tagdef(lid, t, e, d, 1);
				crt_enc_loc = NULL_ptr(LOCATION);
			}
		} else {
			/* Check for anonymous unions */
			if (!EQ_id(id, lid)) {
				if (output_diag && is_anon_member(id)) {
					enc_diag_id(id, 1);
				}
			}
		}
	} else {
		check_mangled(id);
	}
	return;
}


/*
    This routine compiles all the inline and implicit functions which
    have been used in the program.  The usage information comes from
    the fact that the function tag has actually been output rather than
    the function has been used (possibly in a function which is not
    itself used).
*/

void
compile_pending(void)
{
	int changed;
	do {
		LIST(IDENTIFIER)p = pending_funcs;
		if (!output_capsule)break;
		changed = 0;
		while (!IS_NULL_list(p)) {
			IDENTIFIER id = DEREF_id(HEAD_list(p));
			if (!IS_NULL_id(id)) {
				ulong n = DEREF_ulong(id_no(id));
				if (n != LINK_NONE) {
					DECL_SPEC ds = DEREF_dspec(id_storage(id));
					if (!(ds & dspec_done)) {
						if (IS_id_function_etc(id)) {
							if (ds & dspec_trivial) {
								/* It can happen ... */
								ds &= ~(dspec_defn | dspec_trivial);
								COPY_dspec(id_storage(id), ds);
							}
							if (!(ds & dspec_defn)) {
								/* Function not defined */
								if (ds & dspec_implicit) {
									/* Compile implicit functions */
									LOCATION loc;
									bad_crt_loc++;
									loc = crt_loc;
									DEREF_loc(id_loc(id), crt_loc);
									implicit_defn(id, DEFAULT_USR);
									crt_loc = loc;
									bad_crt_loc--;
								} else if (ds & dspec_extern) {
									/* External linkage */
									update_tag(id, 1);
								}
							}
							compile_function(id, 1);
						} else {
							compile_variable(id, 1);
						}
						changed = 1;
					}
					COPY_id(HEAD_list(p), NULL_id);
				}
			}
			p = TAIL_list(p);
		}
		if (!changed)changed = enc_diag_pending();
	} while (changed);
	compile_incompl();
	return;
}


/*
    This routine determines whether a function declared with specifiers
    ds should be output.  It returns 1 if it should be output immediately,
    2 if the decision on whether to output should be deferred until later,
    and 0 otherwise.  The algorithm is somewhat complex to avoid outputting
    inline and implicit function definitions unless absolutely necessary
    and to only declare virtual functions when explicitly called or when
    defining a virtual function table.
*/

static int
need_function(DECL_SPEC ds, ulong n)
{
	if (ds & (dspec_inline | dspec_implicit | dspec_token)) {
		/* Defer inline functions */
		if ((ds & dspec_defn) && n != LINK_NONE) {
			return 1;
		}
		return 2;
	}
	if (ds & dspec_defn) {
		/* Output defined functions */
		if ((ds & dspec_extern) || output_unused) {
			return 1;
		}
		if (n != LINK_NONE) {
			return 1;
		}
		return 2;
	}
	if (ds & (dspec_used | dspec_called | dspec_virtual)) {
		/* Defer called functions */
		return 2;
	}
	return 0;
}


/*
    This routine compiles the function or member function id.  If force
    is true then the definition of id is always output.
*/

void
compile_function(IDENTIFIER id, int force)
{
	/* Check for template functions */
	TYPE t;
	IDENTIFIER lid = DEREF_id(id_alias(id));
	if (IS_id_ambig(lid)) {
		return;
	}
	t = DEREF_type(id_function_etc_type(lid));
	if (IS_type_templ(t)) {
		return;
	}

	/* Simple functions */
	if (output_capsule) {
		DECL_SPEC ds = DEREF_dspec(id_storage(lid));
		if (!(ds & (dspec_done | dspec_trivial))) {
			int output;
			if (force) {
				/* Force output */
				output = 1;
			} else {
				/* Determine whether to output */
				ulong n = DEREF_ulong(id_no(lid));
				output = need_function(ds, n);
				if (output == 2) {
					/* Defer function until later */
					CONS_id(lid, pending_funcs, pending_funcs);
					output = 0;
				}
			}
			if (output == 1) {
				/* Output function definition */
				EXP e = DEREF_exp(id_function_etc_defn(lid));
				if (!(ds & dspec_defn)) {
					e = NULL_exp;
				}
				ds |= dspec_done;
				COPY_dspec(id_storage(lid), ds);
				crt_enc_loc = id_loc(lid);
				IGNORE make_tagdef(lid, t, e, NULL_exp, 0);
				crt_enc_loc = NULL_ptr(LOCATION);
				free_function(lid);
			}
		}
	} else {
		free_function(lid);
		check_mangled(lid);
	}
	return;
}


/*
    This value gives those virtual functions which are ignored when
    deciding whether to output a virtual function table.
*/

#define dspec_ignore_virtual\
   (dspec_inherit | dspec_implicit | dspec_inline | dspec_pure)


/*
    This routine compiles the virtual function table associated with
    the polymorphic class type ct.  anon is as in check_identifier.
    The criterion used to limit duplicate copies is putting the virtual
    function table definition in the same file as the definition of the
    first (in the sense of first in the virtual function table, rather
    than in the class definition) non-inline virtual function declared
    in the class.
*/

#if LANGUAGE_CPP

void
compile_virtual(CLASS_TYPE ct, int anon)
{
	if (output_capsule) {
		IDENTIFIER cid = DEREF_id(ctype_name(ct));
		crt_enc_loc = id_loc(cid);
		if (anon == ANON_NONE && !output_virtual) {
			LIST(VIRTUAL)pt;
			VIRTUAL vt = DEREF_virt(ctype_virt(ct));
			if (IS_NULL_virt(vt)) {
				return;
			}
			pt = DEREF_list(virt_table_entries(vt));
			while (!IS_NULL_list(pt)) {
				VIRTUAL at = DEREF_virt(HEAD_list(pt));
				unsigned tag = TAG_virt(at);
				while (tag == virt_link_tag) {
					/* Allow for symbolic links */
					at = DEREF_virt(DEREF_ptr(virt_link_to(at)));
					tag = TAG_virt(at);
				}
				if (tag == virt_simple_tag || tag == virt_override_tag) {
					/* Examine virtual functions */
					IDENTIFIER fn = DEREF_id(virt_func(at));
					DECL_SPEC ds = DEREF_dspec(id_storage(fn));
					if (!(ds & dspec_ignore_virtual)) {
						if (ds & dspec_defn) {
							/* Define the table externally */
							define_vtable(ct, 2, 1);
						} else {
							/* Declare the table externally */
							define_vtable(ct, 0, 1);
						}
						return;
					}
				}
				pt = TAIL_list(pt);
			}
		}
		/* Define the table internally */
		define_vtable(ct, 1, 0);
	}
	return;
}

#endif


/*
    This routine compiles the token id.  It is only called if id is defined
    (in which case def is true) or should be defined.
*/

void
compile_token(IDENTIFIER id, int def)
{
	if (!def) {
		report(crt_loc, ERR_token_undef(id));
	}
	if (output_capsule) {
		crt_enc_loc = id_loc(id);
		IGNORE enc_tokdef(id, 1);
		if (output_diag) {
			enc_diag_token(id, NULL_type);
		}
		crt_enc_loc = NULL_ptr(LOCATION);
	}
	return;
}


/*
    This routine compiles the type named id.  This only has an effect in
    diagnostics mode.
*/

void
compile_type(IDENTIFIER id)
{
	if (output_capsule && output_diag) {
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if ((ds & dspec_used) && !(ds & dspec_done)) {
			ds |= dspec_done;
			COPY_dspec(id_storage(id), ds);
			if (ds & dspec_token) {
				/* Tokenised type */
				/* EMPTY */
			} else {
				crt_enc_loc = id_loc(id);
				enc_diag_id(id, 0);
				crt_enc_loc = NULL_ptr(LOCATION);
			}
		}
	}
	return;
}


/*
    This routine compiles the asm definition e which is declared outside
    any function definition.
*/

void
compile_asm(EXP e)
{
	TYPE t = DEREF_type(exp_type(e));
	IGNORE make_tagdef(NULL_id, t, e, NULL_exp, 1);
	return;
}


/*
    This routine adds the comment string s of length n to the output
    capsule.  This is used in the implementation of the '#ident' directive.
*/

void
compile_comment(string s, unsigned long n)
{
	if (output_capsule) {
		BITSTREAM *bs = linkinfo_unit;
		ENC_make_comment(bs);
		bs = enc_tdfstring(bs, n, s);
		count_item(bs);
		linkinfo_unit = bs;
	}
	return;
}


/*
    This routine adds the preserved static identifier id to the output
    capsule.
*/

void
compile_preserve(IDENTIFIER id)
{
	if (output_capsule) {
		ulong n;
		BITSTREAM *bs = linkinfo_unit;
		ENC_static_name_def(bs);
		ENC_obtain_tag(bs);
		IGNORE capsule_id(id, VAR_tag);
		n = unit_no(bs, id, VAR_tag, 1);
		ENC_make_tag(bs, n);
		bs = enc_diag_name(bs, id, 1);
		count_item(bs);
		linkinfo_unit = bs;
	}
	return;
}


/*
    This routine adds a weak linkage directive '#pragma weak id = aid'
    to the output capsule.
*/

void
compile_weak(IDENTIFIER id, IDENTIFIER aid)
{
	if (output_capsule && !IS_NULL_id(id)) {
		ulong n;
		string s = NULL;
		BITSTREAM *bs = linkinfo_unit;

		/* Set up weak symbol name */
		id = DEREF_id(id_alias(id));
		IGNORE capsule_id(id, VAR_tag);
		n = DEREF_ulong(id_no(id));
		IGNORE capsule_name(n, &s, VAR_tag);
		if (s) {
			ENC_make_weak_symbol(bs);
			bs = enc_ustring(bs, s);
			ENC_obtain_tag(bs);
			n = unit_no(bs, id, VAR_tag, 1);
			ENC_make_tag(bs, n);
			count_item(bs);
		}

		/* Set up weak symbol definition */
		if (!IS_NULL_id(aid)) {
			aid = DEREF_id(id_alias(aid));
			ENC_make_weak_defn(bs);
			ENC_obtain_tag(bs);
			n = unit_no(bs, id, VAR_tag, 1);
			ENC_make_tag(bs, n);
			ENC_obtain_tag(bs);
			IGNORE capsule_id(aid, VAR_tag);
			n = unit_no(bs, aid, VAR_tag, 1);
			ENC_make_tag(bs, n);
			count_item(bs);
		}
		linkinfo_unit = bs;
	}
	return;
}


/*
    This routine updates the external name of the identifier id forcing
    it to become internal or external, depending on the value of ext.  It
    is used to handle inline functions with external linkage.
*/

void
update_tag(IDENTIFIER id, int ext)
{
	IDENTIFIER lid = DEREF_id(id_alias(id));
	ulong n = DEREF_ulong(id_no(lid));
	if (n != LINK_NONE && (n & LINK_EXTERN)) {
		string s = mangle_name(lid, VAR_tag, ext);
		n = capsule_name(n, &s, VAR_tag);
		COPY_ulong(id_no(lid), n);
		COPY_ulong(id_no(id), n);
	}
	return;
}

